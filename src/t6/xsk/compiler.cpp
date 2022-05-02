// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "t6.hpp"
#include "parser.hpp"
#include "lexer.hpp"

namespace xsk::arc::t6
{

auto compiler::output() -> assembly::ptr
{
    return std::move(assembly_);
}

auto compiler::output_raw() -> std::vector<std::uint8_t>
{
    output_ = std::make_unique<utils::byte_buffer>(0x100000);

    output_->write_string("// T6 GSC ASSEMBLY\n");
    output_->write_string("// Compiled by https://github.com/xensik/gsc-tool\n");

    for (const auto& func : assembly_->functions)
    {
        this->print_function(func);
    }

    std::vector<std::uint8_t> output;

    output.resize(output_->pos());
    std::memcpy(output.data(), output_->buffer().data(), output.size());

    return output;
}

void compiler::compile(const std::string& file, std::vector<std::uint8_t>& data)
{
    filename_ = file;

    auto prog = parse_buffer(filename_, reinterpret_cast<char*>(data.data()), data.size());

    compile_program(prog);
}

void compiler::mode(build mode)
{
    mode_ = mode;
}

auto compiler::parse_buffer(const std::string& file, char* data, size_t size) -> ast::program::ptr
{
    ast::program::ptr result(nullptr);

    lexer lexer(mode_, file, data, size);

    parser parser(lexer, result);

    if (parser.parse() || result == nullptr)
    {
        throw comp_error(location(&file), "An unknown error ocurred while parsing gsc file.");
    }

    return result;
}

auto compiler::parse_file(const std::string& file) -> ast::program::ptr
{
    auto data = resolver::file_data(file);
    auto result = parse_buffer(file, std::get<1>(data), std::get<2>(data));

    return result;
}

void compiler::compile_program(const ast::program::ptr& program)
{
    assembly_ = std::make_unique<assembly>();
    includes_.clear();
    animtrees_.clear();
    constants_.clear();
    local_functions_.clear();
    index_ = 0;
    developer_thread_ = false;

    for (const auto& entry : program->declarations)
    {
        if (entry == ast::kind::decl_thread)
        {
            local_functions_.push_back(entry.as_thread->name->value);
        }
    }

    for (const auto& include : program->includes)
    {
        emit_include(include);
    }

    for (const auto& declaration : program->declarations)
    {
        emit_declaration(declaration);
    }

    std::reverse(assembly_->includes.begin(), assembly_->includes.end());
}

void compiler::emit_include(const ast::include::ptr& include)
{
    const auto& path = include->path->value;

    for (const auto& entry : assembly_->includes)
    {
        if (entry == path)
        {
            throw comp_error(include->loc(), "duplicated include file '" + path + "'.");
        }
    }

    assembly_->includes.push_back(path);
}

void compiler::emit_declaration(const ast::decl& decl)
{
    switch (decl.kind())
    {
        case ast::kind::decl_dev_begin:
            developer_thread_ = true;
            break;
        case ast::kind::decl_dev_end:
            developer_thread_ = false;
            break;
        case ast::kind::decl_usingtree:
            emit_decl_usingtree(decl.as_usingtree);
            break;
        case ast::kind::decl_constant:
            emit_decl_constant(decl.as_constant);
            break;
        case ast::kind::decl_thread:
            emit_decl_thread(decl.as_thread);
            break;
        default:
            throw comp_error(decl.loc(), "unknown declaration");
    }
}

void compiler::emit_decl_usingtree(const ast::decl_usingtree::ptr& animtree)
{
    if (developer_thread_)
    {
        throw comp_error(animtree->loc(), "cannot put #using_animtree inside /# ... #/ comment");
    }

    animtrees_.push_back({ animtree->name->value, false });
}

void compiler::emit_decl_constant(const ast::decl_constant::ptr& constant)
{
    if (constants_.contains(constant->name->value))
    {
        throw comp_error(constant->loc(), "duplicated constant definition");
    }

    constants_.insert({ constant->name->value, std::move(constant->value) });
}

void compiler::emit_decl_thread(const ast::decl_thread::ptr& thread)
{
    function_ = std::make_unique<function>();
    function_->index = index_;
    function_->name = thread->name->value;
    function_->params = static_cast<std::uint8_t>(thread->params->list.size());
    function_->flags = 0;

    stack_idx_ = 0;
    label_idx_ = 0;
    can_break_ = false;
    can_continue_ = false;
    local_stack_.clear();
    blocks_.clear();

    process_thread(thread);

    blocks_.push_back(block());

    emit_expr_parameters(thread->params);
    emit_stmt_list(thread->stmt);

    if (blocks_.back().abort == abort_t::abort_none)
        emit_opcode(opcode::OP_End);

    blocks_.pop_back();

    function_->size = index_ - function_->index;
    assembly_->functions.push_back(std::move(function_));
}

void compiler::emit_stmt(const ast::stmt& stmt)
{
    switch (stmt.kind())
    {
        case ast::kind::stmt_list:
            emit_stmt_list(stmt.as_list);
            break;
        case ast::kind::stmt_dev:
            emit_stmt_dev(stmt.as_dev);
            break;
        case ast::kind::stmt_expr:
            emit_stmt_expr(stmt.as_expr);
            break;
        case ast::kind::stmt_call:
            emit_stmt_call(stmt.as_call);
            break;
        case ast::kind::stmt_assign:
            emit_stmt_assign(stmt.as_assign);
            break;
        case ast::kind::stmt_endon:
            emit_stmt_endon(stmt.as_endon);
            break;
        case ast::kind::stmt_notify:
            emit_stmt_notify(stmt.as_notify);
            break;
        case ast::kind::stmt_wait:
            emit_stmt_wait(stmt.as_wait);
            break;
        case ast::kind::stmt_waittill:
            emit_stmt_waittill(stmt.as_waittill);
            break;
        case ast::kind::stmt_waittillmatch:
            emit_stmt_waittillmatch(stmt.as_waittillmatch);
            break;
        case ast::kind::stmt_waittillframeend:
            emit_stmt_waittillframeend(stmt.as_waittillframeend);
            break;
        case ast::kind::stmt_if:
            emit_stmt_if(stmt.as_if);
            break;
        case ast::kind::stmt_ifelse:
            emit_stmt_ifelse(stmt.as_ifelse);
            break;
        case ast::kind::stmt_while:
            emit_stmt_while(stmt.as_while);
            break;
        case ast::kind::stmt_dowhile:
            emit_stmt_dowhile(stmt.as_dowhile);
            break;
        case ast::kind::stmt_for:
            emit_stmt_for(stmt.as_for);
            break;
        case ast::kind::stmt_foreach:
            emit_stmt_foreach(stmt.as_foreach);
            break;
        case ast::kind::stmt_switch:
            emit_stmt_switch(stmt.as_switch);
            break;
        case ast::kind::stmt_case:
            emit_stmt_case(stmt.as_case);;
            break;
        case ast::kind::stmt_default:
            emit_stmt_default(stmt.as_default);
            break;
        case ast::kind::stmt_break:
            emit_stmt_break(stmt.as_break);
            break;
        case ast::kind::stmt_continue:
            emit_stmt_continue(stmt.as_continue);
            break;
        case ast::kind::stmt_return:
            emit_stmt_return(stmt.as_return);
            break;
        case ast::kind::stmt_prof_begin:
            emit_stmt_prof_begin(stmt.as_prof_begin);
            break;
        case ast::kind::stmt_prof_end:
            emit_stmt_prof_end(stmt.as_prof_end);
            break;
        default:
            throw comp_error(stmt.loc(), "unknown statement");
    }
}

void compiler::emit_stmt_list(const ast::stmt_list::ptr& stmt)
{
    for (const auto& entry : stmt->list)
    {
        emit_stmt(entry);
    }
}

void compiler::emit_stmt_dev(const ast::stmt_dev::ptr& stmt)
{
    developer_thread_ = true;

    auto end = create_label();
    emit_opcode(opcode::OP_DevblockBegin, end);
    emit_stmt_list(stmt->list);
    insert_label(end);

    developer_thread_ = false;
}

void compiler::emit_stmt_expr(const ast::stmt_expr::ptr& stmt)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            emit_expr_increment(stmt->expr.as_increment, true);
            break;
        case ast::kind::expr_decrement:
            emit_expr_decrement(stmt->expr.as_decrement, true);
            break;
        case ast::kind::expr_assign_equal:
        case ast::kind::expr_assign_add:
        case ast::kind::expr_assign_sub:
        case ast::kind::expr_assign_mul:
        case ast::kind::expr_assign_div:
        case ast::kind::expr_assign_mod:
        case ast::kind::expr_assign_shift_left:
        case ast::kind::expr_assign_shift_right:
        case ast::kind::expr_assign_bitwise_or:
        case ast::kind::expr_assign_bitwise_and:
        case ast::kind::expr_assign_bitwise_exor:
            emit_expr_assign(stmt->expr.as_assign);
            break;
        case ast::kind::null:
            break;
        default:
            throw comp_error(stmt->loc(), "unknown expr statement expression");
    }
}

void compiler::emit_stmt_call(const ast::stmt_call::ptr& stmt)
{
    if (stmt->expr == ast::kind::expr_call)
        emit_expr_call(stmt->expr.as_call, true);
    else if (stmt->expr == ast::kind::expr_method)
        emit_expr_method(stmt->expr.as_method, true);
    else
        throw comp_error(stmt->loc(), "unknown call statement expression");
}

void compiler::emit_stmt_assign(const ast::stmt_assign::ptr& stmt)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            emit_expr_increment(stmt->expr.as_increment, true);
            break;
        case ast::kind::expr_decrement:
            emit_expr_decrement(stmt->expr.as_decrement, true);
            break;
        case ast::kind::expr_assign_equal:
        case ast::kind::expr_assign_add:
        case ast::kind::expr_assign_sub:
        case ast::kind::expr_assign_mul:
        case ast::kind::expr_assign_div:
        case ast::kind::expr_assign_mod:
        case ast::kind::expr_assign_shift_left:
        case ast::kind::expr_assign_shift_right:
        case ast::kind::expr_assign_bitwise_or:
        case ast::kind::expr_assign_bitwise_and:
        case ast::kind::expr_assign_bitwise_exor:
            emit_expr_assign(stmt->expr.as_assign);
            break;
        default:
            throw comp_error(stmt->loc(), "unknown assign statement expression");
    }
}

void compiler::emit_stmt_endon(const ast::stmt_endon::ptr& stmt)
{
    emit_expr(stmt->event);
    emit_expr(stmt->obj);
    emit_opcode(opcode::OP_EndOn);
}

void compiler::emit_stmt_notify(const ast::stmt_notify::ptr& stmt)
{
    emit_opcode(opcode::OP_VoidCodePos);

    std::reverse(stmt->args->list.begin(), stmt->args->list.end());

    for (const auto& arg : stmt->args->list)
    {
        emit_expr(arg);
    }

    emit_expr(stmt->event);
    emit_expr(stmt->obj);
    emit_opcode(opcode::OP_Notify);
}

void compiler::emit_stmt_wait(const ast::stmt_wait::ptr& stmt)
{
    emit_expr(stmt->time);
    emit_opcode(opcode::OP_Wait);
}

void compiler::emit_stmt_waittill(const ast::stmt_waittill::ptr& stmt)
{
    emit_expr(stmt->event);
    emit_expr(stmt->obj);
    emit_opcode(opcode::OP_WaitTill);

    for (const auto& entry : stmt->args->list)
    {
        emit_opcode(opcode::OP_SafeSetWaittillVariableFieldCached, variable_access(entry.as_identifier));
    }

    emit_opcode(opcode::OP_ClearParams);
}

void compiler::emit_stmt_waittillmatch(const ast::stmt_waittillmatch::ptr& stmt)
{
    emit_expr_arguments(stmt->args);
    emit_expr(stmt->event);
    emit_expr(stmt->obj);
    emit_opcode(opcode::OP_WaitTillMatch, utils::string::va("%d", stmt->args->list.size()));
    emit_opcode(opcode::OP_ClearParams);
}

void compiler::emit_stmt_waittillframeend(const ast::stmt_waittillframeend::ptr&)
{
    emit_opcode(opcode::OP_WaitTillFrameEnd);
}

void compiler::emit_stmt_if(const ast::stmt_if::ptr& stmt)
{
    auto end_loc = create_label();

    if (stmt->test == ast::kind::expr_not)
    {
        emit_expr(stmt->test.as_not->rvalue);
        emit_opcode(opcode::OP_JumpOnTrue, end_loc);
    }
    else
    {
        emit_expr(stmt->test);
        emit_opcode(opcode::OP_JumpOnFalse, end_loc);
    }

    auto& paren = blocks_.back();
    blocks_.push_back(block(paren.loc_break, paren.loc_continue));

    emit_stmt(stmt->stmt);

    blocks_.pop_back();

    insert_label(end_loc);
}

void compiler::emit_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt)
{
    auto else_loc = create_label();
    auto end_loc = create_label();

    if (stmt->test == ast::kind::expr_not)
    {
        emit_expr(stmt->test.as_not->rvalue);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(stmt->test);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    auto& paren = blocks_.back();
    blocks_.push_back(block(paren.loc_break, paren.loc_continue));
    emit_stmt(stmt->stmt_if);
    blocks_.pop_back();

    emit_opcode(opcode::OP_Jump, end_loc);

    insert_label(else_loc);

    auto& root = blocks_.back();
    blocks_.push_back(block(root.loc_break, root.loc_continue));
    emit_stmt(stmt->stmt_else);
    blocks_.pop_back();

    insert_label(end_loc);
}

void compiler::emit_stmt_while(const ast::stmt_while::ptr& stmt)
{
    auto old_break = can_break_;
    auto old_continue = can_continue_;

    can_break_ = true;
    can_continue_ = true;
    auto break_loc = create_label();
    auto continue_loc = insert_label();

    if (stmt->test == ast::kind::expr_not)
    {
        emit_expr(stmt->test.as_not->rvalue);
        emit_opcode(opcode::OP_JumpOnTrue, break_loc);
    }
    else
    {
        emit_expr(stmt->test);
        emit_opcode(opcode::OP_JumpOnFalse, break_loc);
    }

    blocks_.push_back(block(break_loc, continue_loc));
    emit_stmt(stmt->stmt);
    blocks_.pop_back();

    emit_opcode(opcode::OP_Jump, continue_loc);
    insert_label(break_loc);

    can_break_ = old_break;
    can_continue_ = old_continue;
}

void compiler::emit_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt)
{
    auto old_break = can_break_;
    auto old_continue = can_continue_;

    can_break_ = true;
    can_continue_ = true;
    auto break_loc = create_label();
    auto continue_loc = create_label();

    auto begin_loc = insert_label();

    blocks_.push_back(block(break_loc, continue_loc));
    emit_stmt(stmt->stmt);
    blocks_.pop_back();

    insert_label(continue_loc);

    if (stmt->test == ast::kind::expr_not)
    {
        emit_expr(stmt->test.as_not->rvalue);
        emit_opcode(opcode::OP_JumpOnFalse, begin_loc);
    }
    else
    {
        emit_expr(stmt->test);
        emit_opcode(opcode::OP_JumpOnTrue, begin_loc);
    }

    insert_label(break_loc);

    can_break_ = old_break;
    can_continue_ = old_continue;
}

void compiler::emit_stmt_for(const ast::stmt_for::ptr& stmt)
{
    auto old_break = can_break_;
    auto old_continue = can_continue_;

    emit_stmt(stmt->init);

    auto break_loc = create_label();
    auto continue_loc = create_label();

    auto begin_loc = insert_label();

    bool const_cond = is_constant_condition(stmt->test);

    if (!const_cond)
    {
        emit_expr(stmt->test);
        emit_opcode(opcode::OP_JumpOnFalse, break_loc);
    }

    can_break_ = true;
    can_continue_ = true;

    blocks_.push_back(block(break_loc, continue_loc));
    emit_stmt(stmt->stmt);
    blocks_.pop_back();

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);
    emit_stmt(stmt->iter);
    emit_opcode(opcode::OP_Jump, begin_loc);
    insert_label(break_loc);

    can_break_ = old_break;
    can_continue_ = old_continue;
}

void compiler::emit_stmt_foreach(const ast::stmt_foreach::ptr& stmt)
{
    auto old_break = can_break_;
    auto old_continue = can_continue_;

    emit_expr(stmt->array_expr);
    emit_expr_variable_ref(stmt->array, true);
    emit_expr_variable(stmt->array);
    emit_opcode(opcode::OP_FirstArrayKey);
    emit_expr_variable_ref(stmt->key_expr, true);

    auto break_loc = create_label();
    auto continue_loc = create_label();

    auto begin_loc = insert_label();

    emit_expr_variable(stmt->key_expr);
    emit_opcode(opcode::OP_IsDefined);
    emit_opcode(opcode::OP_JumpOnFalse, break_loc);

    can_break_ = true;
    can_continue_ = true;

    emit_expr_variable(stmt->key_expr);
    emit_opcode(opcode::OP_EvalLocalVariableCached, variable_access(stmt->array.as_identifier));
    emit_opcode(opcode::OP_EvalArray);
    emit_expr_variable_ref(stmt->value_expr, true);

    blocks_.push_back(block(break_loc, continue_loc));
    emit_stmt(stmt->stmt);
    blocks_.pop_back();

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);

    emit_expr_variable(stmt->key_expr);
    emit_expr_variable(stmt->array);
    emit_opcode(opcode::OP_NextArrayKey);
    emit_expr_variable_ref(stmt->key_expr, true);
    emit_opcode(opcode::OP_Jump, begin_loc);
    insert_label(break_loc);

    can_break_ = old_break;
    can_continue_ = old_continue;
}

void compiler::emit_stmt_switch(const ast::stmt_switch::ptr& stmt)
{
    auto old_break = can_break_;

    can_break_ = false;

    auto jmptable_loc = create_label();

    auto break_loc = create_label();

    emit_expr(stmt->test);
    emit_opcode(opcode::OP_Switch, jmptable_loc);

    can_break_ = true;

    blocks_.push_back(block(break_loc, blocks_.back().loc_continue));

    std::vector<std::string> data;
    data.push_back(utils::string::va("%d", stmt->stmt->list.size()));

    bool numerical = false;
    bool has_default = false;

    for (auto i = 0u; i < stmt->stmt->list.size(); i++)
    {
        auto& entry = stmt->stmt->list[i];

        if (entry == ast::kind::stmt_case)
        {
            if (has_default)
            {
                comp_error(stmt->loc(), "default must be last case");
            }

            auto& case_ = entry.as_case;
            if (case_->label == ast::kind::expr_integer)
            {
                numerical = true;
                auto loc = insert_label();
                data.push_back("case");
                data.push_back(case_->label.as_integer->value);
                data.push_back(loc);
            }
            else if (case_->label == ast::kind::expr_string)
            {
                auto loc = insert_label();
                data.push_back("case");
                data.push_back(case_->label.as_string->value);
                data.push_back(loc);
            }
            else
            {
                throw comp_error(stmt->loc(), "case type must be int or string");
            }

            auto& paren = blocks_.back();
            blocks_.push_back(block(paren.loc_break, paren.loc_continue));
            emit_stmt_list(case_->stmt);
            blocks_.pop_back();
        }
        else if (entry == ast::kind::stmt_default)
        {
            auto loc = insert_label();
            data.push_back("default");
            data.push_back(loc);
            has_default = true;

            auto& paren = blocks_.back();
            blocks_.push_back(block(paren.loc_break, paren.loc_continue));
            emit_stmt_list(entry.as_default->stmt);
            blocks_.pop_back();
        }
        else
        {
            throw comp_error(entry.loc(), "missing case statement");
        }
    }

    blocks_.pop_back();
    data.push_back(numerical ? "i" : "s");

    insert_label(jmptable_loc);
    emit_opcode(opcode::OP_EndSwitch, data);
    insert_label(break_loc);

    can_break_ = old_break;
}

void compiler::emit_stmt_case(const ast::stmt_case::ptr& stmt)
{
    throw comp_error(stmt->loc(), "illegal case statement");
}

void compiler::emit_stmt_default(const ast::stmt_default::ptr& stmt)
{
    throw comp_error(stmt->loc(), "illegal default statement");
}

void compiler::emit_stmt_break(const ast::stmt_break::ptr& stmt)
{
    if (!can_break_ || blocks_.back().abort != abort_t::abort_none || blocks_.back().loc_break == "")
        throw comp_error(stmt->loc(), "illegal break statement");

    blocks_.back().abort = abort_t::abort_break;
    emit_opcode(opcode::OP_Jump, blocks_.back().loc_break);
}

void compiler::emit_stmt_continue(const ast::stmt_continue::ptr& stmt)
{
    if (!can_continue_ || blocks_.back().abort != abort_t::abort_none || blocks_.back().loc_continue == "")
        throw comp_error(stmt->loc(), "illegal continue statement");

    blocks_.back().abort = abort_t::abort_continue;
    emit_opcode(opcode::OP_Jump, blocks_.back().loc_continue);
}

void compiler::emit_stmt_return(const ast::stmt_return::ptr& stmt)
{
    if (blocks_.back().abort == abort_t::abort_none)
        blocks_.back().abort = abort_t::abort_return;

    if (stmt->expr != ast::kind::null)
    {
        emit_expr(stmt->expr);
        emit_opcode(opcode::OP_Return);
    }
    else
        emit_opcode(opcode::OP_End);
}

void compiler::emit_stmt_prof_begin(const ast::stmt_prof_begin::ptr&)
{
    // TODO:
}

void compiler::emit_stmt_prof_end(const ast::stmt_prof_end::ptr&)
{
    // TODO:
}

void compiler::emit_expr(const ast::expr& expr)
{
    switch (expr.kind())
    {
        case ast::kind::expr_paren:
            emit_expr(expr.as_paren->child);
            break;
        case ast::kind::expr_ternary:
            emit_expr_ternary(expr.as_ternary);
            break;
        case ast::kind::expr_and:
            emit_expr_and(expr.as_and);
            break;
        case ast::kind::expr_or:
            emit_expr_or(expr.as_or);
            break;
        case ast::kind::expr_equality:
        case ast::kind::expr_inequality:
        case ast::kind::expr_less:
        case ast::kind::expr_greater:
        case ast::kind::expr_less_equal:
        case ast::kind::expr_greater_equal:
        case ast::kind::expr_bitwise_or:
        case ast::kind::expr_bitwise_and:
        case ast::kind::expr_bitwise_exor:
        case ast::kind::expr_shift_left:
        case ast::kind::expr_shift_right:
        case ast::kind::expr_add:
        case ast::kind::expr_sub:
        case ast::kind::expr_mul:
        case ast::kind::expr_div:
        case ast::kind::expr_mod:
            emit_expr_binary(expr.as_binary);
            break;
        case ast::kind::expr_complement:
            emit_expr_complement(expr.as_complement);
            break;
        case ast::kind::expr_not:
            emit_expr_not(expr.as_not);
            break;
        case ast::kind::expr_call:
            emit_expr_call(expr.as_call, false);
            break;
        case ast::kind::expr_method:
            emit_expr_method(expr.as_method, false);
            break;
        case ast::kind::expr_isdefined:
            emit_expr_isdefined(expr.as_isdefined);
            break;
        case ast::kind::expr_vectorscale:
            emit_expr_vectorscale(expr.as_vectorscale);
            break;
        case ast::kind::expr_anglestoup:
            emit_expr_anglestoup(expr.as_anglestoup);
            break;
        case ast::kind::expr_anglestoright:
            emit_expr_anglestoright(expr.as_anglestoright);
            break;
        case ast::kind::expr_anglestoforward:
            emit_expr_anglestoforward(expr.as_anglestoforward);
            break;
        case ast::kind::expr_angleclamp180:
            emit_expr_angleclamp180(expr.as_angleclamp180);
            break;
        case ast::kind::expr_vectortoangles:
            emit_expr_vectortoangles(expr.as_vectortoangles);
            break;
        case ast::kind::expr_abs:
            emit_expr_abs(expr.as_abs);
            break;
        case ast::kind::expr_gettime:
            emit_expr_gettime(expr.as_gettime);
            break;
        case ast::kind::expr_getdvar:
            emit_expr_getdvar(expr.as_getdvar);
            break;
        case ast::kind::expr_getdvarint:
            emit_expr_getdvarint(expr.as_getdvarint);
            break;
        case ast::kind::expr_getdvarfloat:
            emit_expr_getdvarfloat(expr.as_getdvarfloat);
            break;
        case ast::kind::expr_getdvarvector:
            emit_expr_getdvarvector(expr.as_getdvarvector);
            break;
        case ast::kind::expr_getdvarcolorred:
            emit_expr_getdvarcolorred(expr.as_getdvarcolorred);
            break;
        case ast::kind::expr_getdvarcolorgreen:
            emit_expr_getdvarcolorgreen(expr.as_getdvarcolorgreen);
            break;
        case ast::kind::expr_getdvarcolorblue:
            emit_expr_getdvarcolorblue(expr.as_getdvarcolorblue);
            break;
        case ast::kind::expr_getdvarcoloralpha:
            emit_expr_getdvarcoloralpha(expr.as_getdvarcoloralpha);
            break;
        case ast::kind::expr_getfirstarraykey:
            emit_expr_getfirstarraykey(expr.as_getfirstarraykey);
            break;
        case ast::kind::expr_getnextarraykey:
            emit_expr_getnextarraykey(expr.as_getnextarraykey);
            break;
        case ast::kind::expr_reference:
            emit_expr_reference(expr.as_reference);
            break;
        case ast::kind::expr_array:
            emit_expr_array(expr.as_array);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr.as_field);
            break;
        case ast::kind::expr_size:
            emit_expr_size(expr.as_size);
            break;
        case ast::kind::expr_empty_array:
            emit_opcode(opcode::OP_EmptyArray);
            break;
        case ast::kind::expr_undefined:
            emit_opcode(opcode::OP_GetUndefined);
            break;
        case ast::kind::expr_game:
            emit_opcode(opcode::OP_GetGame);
            break;
        case ast::kind::expr_self:
            emit_opcode(opcode::OP_GetSelf);
            break;
        case ast::kind::expr_anim:
            emit_opcode(opcode::OP_GetAnim);
            break;
        case ast::kind::expr_level:
            emit_opcode(opcode::OP_GetLevel);
            break;
        case ast::kind::expr_animation:
            emit_expr_animation(expr.as_animation);
            break;
        case ast::kind::expr_identifier:
            emit_expr_local(expr.as_identifier);
            break;
        case ast::kind::expr_istring:
            emit_expr_istring(expr.as_istring);
            break;
        case ast::kind::expr_string:
            emit_expr_string(expr.as_string);
            break;
        case ast::kind::expr_vector:
            emit_expr_vector(expr.as_vector);
            break;
        case ast::kind::expr_hash:
            emit_expr_hash(expr.as_hash);
            break;
        case ast::kind::expr_float:
            emit_expr_float(expr.as_float);
            break;
        case ast::kind::expr_integer:
            emit_expr_integer(expr.as_integer);
            break;
        case ast::kind::expr_false:
            emit_expr_false(expr.as_false);
            break;
        case ast::kind::expr_true:
            emit_expr_true(expr.as_true);
            break;
        case ast::kind::null:
            break;
        default:
            throw comp_error(expr.loc(), "unknown expression");
    }
}

void compiler::emit_expr_assign(const ast::expr_assign::ptr& expr)
{
    if (expr->kind() == ast::kind::expr_assign_equal)
    {
        if (expr->rvalue == ast::kind::expr_undefined)
        {
            emit_expr_clear(expr->lvalue);
            return;
        }

        emit_expr(expr->rvalue);
        emit_expr_variable_ref(expr->lvalue, true);
        return;
    }

    emit_expr(expr->lvalue);
    emit_expr(expr->rvalue);

    switch (expr->kind())
    {
        case ast::kind::expr_assign_add:
            emit_opcode(opcode::OP_Plus);
            break;
        case ast::kind::expr_assign_sub:
            emit_opcode(opcode::OP_Minus);
            break;
        case ast::kind::expr_assign_mul:
            emit_opcode(opcode::OP_Multiply);
            break;
        case ast::kind::expr_assign_div:
            emit_opcode(opcode::OP_Divide);
            break;
        case ast::kind::expr_assign_mod:
            emit_opcode(opcode::OP_Modulus);
            break;
        case ast::kind::expr_assign_shift_left:
            emit_opcode(opcode::OP_ShiftLeft);
            break;
        case ast::kind::expr_assign_shift_right:
            emit_opcode(opcode::OP_ShiftRight);
            break;
        case ast::kind::expr_assign_bitwise_or:
            emit_opcode(opcode::OP_Bit_Or);
            break;
        case ast::kind::expr_assign_bitwise_and:
            emit_opcode(opcode::OP_Bit_And);
            break;
        case ast::kind::expr_assign_bitwise_exor:
            emit_opcode(opcode::OP_Bit_Xor);
            break;
        default:
            throw comp_error(expr->loc(), "unknown assign operation");
    }

    emit_expr_variable_ref(expr->lvalue, true);
}

void compiler::emit_expr_clear(const ast::expr& expr)
{
    switch (expr.kind())
    {
        case ast::kind::expr_array:
            emit_expr(expr.as_array->key);
            expr.as_array->obj == ast::kind::expr_game ? emit_opcode(opcode::OP_GetGameRef) : emit_expr_variable_ref(expr.as_array->obj, false);
            emit_opcode(opcode::OP_ClearArray);
            break;
        case ast::kind::expr_field:
            emit_expr_object(expr.as_field->obj);
            emit_opcode(opcode::OP_ClearFieldVariable, expr.as_field->field->value);
            break;
        case ast::kind::expr_identifier:
            emit_opcode(opcode::OP_GetUndefined);
            emit_expr_local_ref(expr.as_identifier, true);
            break;
        default:
            throw comp_error(expr.loc(), "unknown clear variable lvalue");
    }
}

void compiler::emit_expr_increment(const ast::expr_increment::ptr& expr, bool is_stmt)
{
    if (is_stmt)
    {
        emit_expr_variable_ref(expr->lvalue, false);
        emit_opcode(opcode::OP_Inc);
    }
    else
    {
        // TODO:
    }
}

void compiler::emit_expr_decrement(const ast::expr_decrement::ptr& expr, bool is_stmt)
{
    if (is_stmt)
    {
        emit_expr_variable_ref(expr->lvalue, false);
        emit_opcode(opcode::OP_Dec);
    }
    else
    {
        // TODO:
    }
}

void compiler::emit_expr_ternary(const ast::expr_ternary::ptr& expr)
{
    auto else_loc = create_label();
    auto end_loc = create_label();

    if (expr->test == ast::kind::expr_not)
    {
        emit_expr(expr->test.as_not->rvalue);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(expr->test);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    emit_expr(expr->true_expr);
    emit_opcode(opcode::OP_Jump, end_loc);

    insert_label(else_loc);
    emit_expr(expr->false_expr);
    insert_label(end_loc);
}

void compiler::emit_expr_binary(const ast::expr_binary::ptr& expr)
{
    emit_expr(expr->lvalue);
    emit_expr(expr->rvalue);

    switch (expr->kind())
    {
        case ast::kind::expr_equality:
            emit_opcode(opcode::OP_Equal);
            break;
        case ast::kind::expr_inequality:
            emit_opcode(opcode::OP_NotEqual);
            break;
        case ast::kind::expr_less:
            emit_opcode(opcode::OP_LessThan);
            break;
        case ast::kind::expr_greater:
            emit_opcode(opcode::OP_GreaterThan);
            break;
        case ast::kind::expr_less_equal:
            emit_opcode(opcode::OP_LessThanOrEqualTo);
            break;
        case ast::kind::expr_greater_equal:
            emit_opcode(opcode::OP_GreaterThanOrEqualTo);
            break;
        case ast::kind::expr_bitwise_or:
            emit_opcode(opcode::OP_Bit_Or);
            break;
        case ast::kind::expr_bitwise_and:
            emit_opcode(opcode::OP_Bit_And);
            break;
        case ast::kind::expr_bitwise_exor:
            emit_opcode(opcode::OP_Bit_Xor);
            break;
        case ast::kind::expr_shift_left:
            emit_opcode(opcode::OP_ShiftLeft);
            break;
        case ast::kind::expr_shift_right:
            emit_opcode(opcode::OP_ShiftRight);
            break;
        case ast::kind::expr_add:
            emit_opcode(opcode::OP_Plus);
            break;
        case ast::kind::expr_sub:
            emit_opcode(opcode::OP_Minus);
            break;
        case ast::kind::expr_mul:
            emit_opcode(opcode::OP_Multiply);
            break;
        case ast::kind::expr_div:
            emit_opcode(opcode::OP_Divide);
            break;
        case ast::kind::expr_mod:
            emit_opcode(opcode::OP_Modulus);
            break;
        default:
            throw comp_error(expr->loc(), "unknown binary expression");
    }
}

void compiler::emit_expr_and(const ast::expr_and::ptr& expr)
{
    auto label = create_label();

    emit_expr(expr->lvalue);
    emit_opcode(opcode::OP_JumpOnFalseExpr, label);
    emit_expr(expr->rvalue);

    insert_label(label);
}

void compiler::emit_expr_or(const ast::expr_or::ptr& expr)
{
    auto label = create_label();

    emit_expr(expr->lvalue);
    emit_opcode(opcode::OP_JumpOnTrueExpr, label);
    emit_expr(expr->rvalue);

    insert_label(label);
}

void compiler::emit_expr_complement(const ast::expr_complement::ptr& expr)
{
    emit_expr(expr->rvalue);
    emit_opcode(opcode::OP_BoolComplement);
}

void compiler::emit_expr_not(const ast::expr_not::ptr& expr)
{
    emit_expr(expr->rvalue);
    emit_opcode(opcode::OP_BoolNot);
}

void compiler::emit_expr_call(const ast::expr_call::ptr& expr, bool is_stmt)
{
    if (expr->call == ast::kind::expr_pointer)
        emit_expr_call_pointer(expr->call.as_pointer, is_stmt);
    else if (expr->call == ast::kind::expr_function)
        emit_expr_call_function(expr->call.as_function, is_stmt);
    else
        throw comp_error(expr->loc(), "unknown function call expression");
}

void compiler::emit_expr_call_pointer(const ast::expr_pointer::ptr& expr, bool is_stmt)
{
    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(expr->args);
    emit_expr(expr->func);

    auto argcount = utils::string::va("%d", expr->args->list.size());

    switch (expr->mode)
    {
        case ast::call::mode::normal:
            emit_opcode(opcode::OP_ScriptFunctionCallPointer, argcount);
            break;
        case ast::call::mode::thread:
            emit_opcode(opcode::OP_ScriptThreadCallPointer, argcount);
            break;
        default:
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

void compiler::emit_expr_call_function(const ast::expr_function::ptr& expr, bool is_stmt)
{
    if (expr->path->value != "")
    {
        bool found = false;

        for (const auto& entry : assembly_->includes)
        {
            if (entry == expr->path->value)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            assembly_->includes.push_back(expr->path->value);
        }
    }

    // TODO: resolve import calls path
    bool as_dev = false;
    std::string end;

    if (!developer_thread_ && is_stmt && expr->name->value == "assert")
    {
        as_dev = true;
        developer_thread_ = true;
        end = create_label();
        emit_opcode(opcode::OP_DevblockBegin, end);
    }

    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(expr->args);

    auto argcount = utils::string::va("%d", expr->args->list.size());
    auto flags = developer_thread_ ? std::uint8_t(import_flags::developer) : 0;

    switch (expr->mode)
    {
        case ast::call::mode::normal:
            flags |= std::uint8_t(import_flags::func_call);
            emit_opcode(opcode::OP_ScriptFunctionCall, { expr->path->value, expr->name->value, argcount, utils::string::va("%d", flags) });
            break;
        case ast::call::mode::thread:
            flags |= std::uint8_t(import_flags::func_call_thread);
            emit_opcode(opcode::OP_ScriptThreadCall, { expr->path->value, expr->name->value, argcount, utils::string::va("%d", flags) });
            break;
        default:
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);

    if (as_dev)
    {
        insert_label(end);
        developer_thread_ = false;
    }
}

void compiler::emit_expr_method(const ast::expr_method::ptr& expr, bool is_stmt)
{
    if (expr->call == ast::kind::expr_pointer)
        emit_expr_method_pointer(expr->call.as_pointer, expr->obj, is_stmt);
    else if (expr->call == ast::kind::expr_function)
        emit_expr_method_function(expr->call.as_function, expr->obj, is_stmt);
    else
        throw comp_error(expr->loc(), "unknown method call expression");
}

void compiler::emit_expr_method_pointer(const ast::expr_pointer::ptr& expr, const ast::expr& obj, bool is_stmt)
{
    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(expr->args);
    emit_expr(obj);
    emit_expr(expr->func);

    auto argcount = utils::string::va("%d", expr->args->list.size());

    switch (expr->mode)
    {
        case ast::call::mode::normal:
            emit_opcode(opcode::OP_ScriptMethodCallPointer, argcount);
            break;
        case ast::call::mode::thread:
            emit_opcode(opcode::OP_ScriptMethodThreadCallPointer, argcount);
            break;
        default:
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

void compiler::emit_expr_method_function(const ast::expr_function::ptr& expr, const ast::expr& obj, bool is_stmt)
{
    if (expr->path->value != "")
    {
        bool found = false;

        for (const auto& entry : assembly_->includes)
        {
            if (entry == expr->path->value)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            assembly_->includes.push_back(expr->path->value);
        }
    }

    // TODO: resolve import calls path

    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(expr->args);
    emit_expr(obj);

    auto argcount = utils::string::va("%d", expr->args->list.size());
    auto flags = developer_thread_ ? std::uint8_t(import_flags::developer) : 0;

    switch (expr->mode)
    {
        case ast::call::mode::normal:
            flags |= std::uint8_t(import_flags::meth_call);
            emit_opcode(opcode::OP_ScriptMethodCall, { expr->path->value, expr->name->value, argcount, utils::string::va("%d", flags) });
            break;
        case ast::call::mode::thread:
            flags |= std::uint8_t(import_flags::meth_call_thread);
            emit_opcode(opcode::OP_ScriptMethodThreadCall, { expr->path->value, expr->name->value, argcount, utils::string::va("%d", flags) });
            break;
        default:
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

void compiler::emit_expr_parameters(const ast::expr_parameters::ptr&)
{
    if (local_stack_.size() == 0)
    {
        emit_opcode(opcode::OP_CheckClearParams);
    }
    else
    {
        emit_opcode(opcode::OP_SafeCreateLocalVariables, local_stack_);
    }
}

void compiler::emit_expr_arguments(const ast::expr_arguments::ptr& expr)
{
    std::reverse(expr->list.begin(), expr->list.end());

    for (auto& entry : expr->list)
    {
        emit_expr(entry);
    }
}

void compiler::emit_expr_isdefined(const ast::expr_isdefined::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_IsDefined);
}

void compiler::emit_expr_vectorscale(const ast::expr_vectorscale::ptr& expr)
{
    emit_expr(expr->arg2);
    emit_expr(expr->arg1);
    emit_opcode(opcode::OP_VectorScale);
}

void compiler::emit_expr_anglestoup(const ast::expr_anglestoup::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_AnglesToUp);
}

void compiler::emit_expr_anglestoright(const ast::expr_anglestoright::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_AnglesToRight);
}

void compiler::emit_expr_anglestoforward(const ast::expr_anglestoforward::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_AnglesToForward);
}

void compiler::emit_expr_angleclamp180(const ast::expr_angleclamp180::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_AngleClamp180);
}

void compiler::emit_expr_vectortoangles(const ast::expr_vectortoangles::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_VectorToAngles);
}

void compiler::emit_expr_abs(const ast::expr_abs::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_Abs);
}

void compiler::emit_expr_gettime(const ast::expr_gettime::ptr&)
{
    emit_opcode(opcode::OP_GetTime);
}

void compiler::emit_expr_getdvar(const ast::expr_getdvar::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_GetDvar);
}

void compiler::emit_expr_getdvarint(const ast::expr_getdvarint::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_GetDvarInt);
}

void compiler::emit_expr_getdvarfloat(const ast::expr_getdvarfloat::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_GetDvarFloat);
}

void compiler::emit_expr_getdvarvector(const ast::expr_getdvarvector::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_GetDvarVector);
}

void compiler::emit_expr_getdvarcolorred(const ast::expr_getdvarcolorred::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_GetDvarColorRed);
}

void compiler::emit_expr_getdvarcolorgreen(const ast::expr_getdvarcolorgreen::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_GetDvarColorGreen);
}

void compiler::emit_expr_getdvarcolorblue(const ast::expr_getdvarcolorblue::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_GetDvarColorBlue);
}

void compiler::emit_expr_getdvarcoloralpha(const ast::expr_getdvarcoloralpha::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_GetDvarColorAlpha);
}

void compiler::emit_expr_getfirstarraykey(const ast::expr_getfirstarraykey::ptr& expr)
{
    emit_expr(expr->arg);
    emit_opcode(opcode::OP_FirstArrayKey);
}

void compiler::emit_expr_getnextarraykey(const ast::expr_getnextarraykey::ptr& expr)
{
    emit_expr(expr->arg2);
    emit_expr(expr->arg1);
    emit_opcode(opcode::OP_NextArrayKey);
}

void compiler::emit_expr_reference(const ast::expr_reference::ptr& expr)
{
    if (expr->path->value != "")
    {
        bool found = false;

        for (const auto& entry : assembly_->includes)
        {
            if (entry == expr->path->value)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            assembly_->includes.push_back(expr->path->value);
        }
    }

    // TODO: resolve import calls path

    auto flags = developer_thread_ ? std::uint8_t(import_flags::developer) : 0;

    flags |= std::uint8_t(import_flags::func_reference);

    emit_opcode(opcode::OP_GetFunction, { expr->path->value, expr->name->value, "0", utils::string::va("%d", flags) });
}

void compiler::emit_expr_size(const ast::expr_size::ptr& expr)
{
    emit_expr(expr->obj);
    emit_opcode(opcode::OP_SizeOf);
}

void compiler::emit_expr_variable_ref(const ast::expr& expr, bool set)
{
    switch (expr.kind())
    {
        case ast::kind::expr_array:
            emit_expr_array_ref(expr.as_array, set);
            break;
        case ast::kind::expr_field:
            emit_expr_field_ref(expr.as_field, set);
            break;
        case ast::kind::expr_identifier:
            emit_expr_local_ref(expr.as_identifier, set);
            break;
        default:
            throw comp_error(expr.loc(), "invalid lvalue");
    }
}

void compiler::emit_expr_array_ref(const ast::expr_array::ptr& expr, bool set)
{
    emit_expr(expr->key);

    switch (expr->obj.kind())
    {
        case ast::kind::expr_game:
            emit_opcode(opcode::OP_GetGameRef);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_array:
        case ast::kind::expr_field:
        case ast::kind::expr_identifier:
            emit_expr_variable_ref(expr->obj, false);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_call:
        case ast::kind::expr_method:
        default:
            throw comp_error(expr->loc(), "invalid array lvalue");
    }
}

void compiler::emit_expr_field_ref(const ast::expr_field::ptr& expr, bool set)
{
    const auto& field = expr->field->value;

    switch (expr->obj.kind())
    {
        case ast::kind::expr_level:
            emit_opcode(opcode::OP_GetLevelObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_anim:
            emit_opcode(opcode::OP_GetAnimObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_self:
            emit_opcode(opcode::OP_GetSelfObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_array:
            emit_expr_array(expr->obj.as_array);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr->obj.as_field);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableCached, variable_access(expr->obj.as_identifier));
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_call:
            emit_expr_call(expr->obj.as_call, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_method:
            emit_expr_method(expr->obj.as_method, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        default:
            throw comp_error(expr->obj.loc(), "not an object");
    }
}

void compiler::emit_expr_local_ref(const ast::expr_identifier::ptr& expr, bool set)
{
    const auto itr = constants_.find(expr->value);

    if (itr != constants_.end())
    {
        throw comp_error(expr->loc(), "variable name already defined as constant '" + expr->value + "'");
    }

    emit_opcode(opcode::OP_EvalLocalVariableRefCached, variable_access(expr));

    if (set)
    {
        emit_opcode(opcode::OP_SetVariableField);
    }
}

void compiler::emit_expr_variable(const ast::expr& expr)
{
    switch (expr.kind())
    {
        case ast::kind::expr_array:
            emit_expr_array(expr.as_array);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr.as_field);
            break;
        case ast::kind::expr_identifier:
            emit_expr_local(expr.as_identifier);
            break;
        default:
            throw comp_error(expr.loc(), "invalid variable type.");
    }
}

void compiler::emit_expr_array(const ast::expr_array::ptr& expr)
{
    emit_expr(expr->key);
    emit_expr(expr->obj);
    emit_opcode(opcode::OP_EvalArray);
}

void compiler::emit_expr_field(const ast::expr_field::ptr& expr)
{
    const auto& field = expr->field->value;

    switch (expr->obj.kind())
    {
        case ast::kind::expr_level:
            emit_opcode(opcode::OP_GetLevelObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_anim:
            emit_opcode(opcode::OP_GetAnimObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_self:
            emit_opcode(opcode::OP_GetSelfObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_array:
            emit_expr_array(expr->obj.as_array);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr->obj.as_field);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_call:
            emit_expr_call(expr->obj.as_call, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_method:
            emit_expr_method(expr->obj.as_method, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableCached, variable_access(expr->obj.as_identifier));
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        default:
            throw comp_error(expr->loc(), "unknown field variable object type");
    }
}

void compiler::emit_expr_local(const ast::expr_identifier::ptr& expr)
{
    // is constant ( should only allow: string, loc string, number, vector)
    const auto itr = constants_.find(expr->value);

    if (itr != constants_.end())
    {
        const auto& value = itr->second;
        emit_expr(value);
        return;
    }

    // is local var
    emit_opcode(opcode::OP_EvalLocalVariableCached, variable_access(expr));
}

void compiler::emit_expr_object(const ast::expr& expr)
{
    switch (expr.kind())
    {
        case ast::kind::expr_level:
            emit_opcode(opcode::OP_GetLevelObject);
            break;
        case ast::kind::expr_anim:
            emit_opcode(opcode::OP_GetAnimObject);
            break;
        case ast::kind::expr_self:
            emit_opcode(opcode::OP_GetSelfObject);
            break;
        case ast::kind::expr_array:
            emit_expr_array(expr.as_array);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr.as_field);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case ast::kind::expr_call:
            emit_expr_call(expr.as_call, false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case ast::kind::expr_method:
            emit_expr_method(expr.as_method, false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case ast::kind::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableCached, variable_access(expr.as_identifier));
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        default:
            throw comp_error(expr.loc(), "not an object");
    }
}

void compiler::emit_expr_vector(const ast::expr_vector::ptr& expr)
{
    std::vector<std::string> data;
    bool isexpr = false;
    bool isconst = true;
    auto flags = 0;

    if (expr->x == ast::kind::expr_integer)
    {
        auto value = std::atoi(expr->x.as_integer->value.data());
        data.push_back(expr->x.as_integer->value);

        if (value != 1 && value != -1 && value != 0)
            isconst = false;
        else
            flags |= (value == 1) ? 0x20 : (value == -1) ? 0x10 : 0;
    }
    else if (expr->x == ast::kind::expr_float)
    {
        auto value = std::stof(expr->x.as_float->value.data());
        data.push_back(expr->x.as_float->value);

        if (value != 1.0 && value != -1.0 && value != 0.0)        
            isconst = false;
        else
            flags |= (value == 1.0) ? 0x20 : (value == -1.0) ? 0x10 : 0;
    }
    else
    {
        isexpr = true;
        isconst = false;
    }

    if (expr->y == ast::kind::expr_integer)
    {
        auto value = std::atoi(expr->y.as_integer->value.data());
        data.push_back(expr->y.as_integer->value);

        if (value != 1 && value != -1 && value != 0)
            isconst = false;
        else
            flags |= (value == 1) ? 0x08 : (value == -1) ? 0x04 : 0;
    }
    else if (expr->y == ast::kind::expr_float)
    {
        auto value = std::stof(expr->y.as_float->value.data());
        data.push_back(expr->y.as_float->value);

        if (value != 1.0 && value != -1.0 && value != 0.0)
            isconst = false;
        else
            flags |= (value == 1.0) ? 0x08 : (value == -1.0) ? 0x04 : 0;
    }
    else
    {
        isexpr = true;
        isconst = false;
    }

    if (expr->z == ast::kind::expr_integer)
    {
        auto value = std::atoi(expr->z.as_integer->value.data());
        data.push_back(expr->z.as_integer->value);

        if (value != 1 && value != -1 && value != 0)
            isconst = false;
        else
            flags |= (value == 1) ? 0x02 : (value == -1) ? 0x01 : 0;
    }
    else if (expr->z == ast::kind::expr_float)
    {
        auto value = std::stof(expr->z.as_float->value.data());
        data.push_back(expr->z.as_float->value);

        if (value != 1.0 && value != -1.0 && value != 0.0)
            isconst = false;
        else
            flags |= (value == 1.0) ? 0x02 : (value == -1.0) ? 0x01 : 0;
    }
    else
    {
        isexpr = true;
        isconst = false;
    }

    if (isconst)
    {
        emit_opcode(opcode::OP_VectorConstant, utils::string::va("%d", flags));
    }
    else if (isexpr)
    {
        emit_expr(expr->z);
        emit_expr(expr->y);
        emit_expr(expr->x);
        emit_opcode(opcode::OP_Vector);
    }
    else
    {
        emit_opcode(opcode::OP_GetVector, data);
    }
}

void compiler::emit_expr_animation(const ast::expr_animation::ptr& expr)
{
    if (animtrees_.size() == 0)
    {
        throw comp_error(expr->loc(), "trying to use animation without specified using animtree");
    }

    emit_opcode(opcode::OP_GetAnimation, { animtrees_.back(), expr->value });
}

void compiler::emit_expr_istring(const ast::expr_istring::ptr& expr)
{
    emit_opcode(opcode::OP_GetIString, expr->value);
}

void compiler::emit_expr_string(const ast::expr_string::ptr& expr)
{
    emit_opcode(opcode::OP_GetString, expr->value);
}

void compiler::emit_expr_hash(const ast::expr_hash::ptr& expr)
{
    emit_opcode(opcode::OP_GetHash, expr->value);
}

void compiler::emit_expr_float(const ast::expr_float::ptr& expr)
{
    emit_opcode(opcode::OP_GetFloat, expr->value);
}

void compiler::emit_expr_integer(const ast::expr_integer::ptr& expr)
{
    auto value = std::atoi(expr->value.data());

    if (value == 0)
    {
        emit_opcode(opcode::OP_GetZero);
    }
    else if (value > 0 && value < 256)
    {
        emit_opcode(opcode::OP_GetByte, expr->value);
    }
    else if (value < 0 && value > -256)
    {
        emit_opcode(opcode::OP_GetNegByte, expr->value.substr(1));
    }
    else if (value > 0 && value < 65536)
    {
        emit_opcode(opcode::OP_GetUnsignedShort, expr->value);
    }
    else if (value < 0 && value > -65536)
    {
        emit_opcode(opcode::OP_GetNegUnsignedShort, expr->value.substr(1));
    }
    else
    {
        emit_opcode(opcode::OP_GetInteger, expr->value);
    }
}

void compiler::emit_expr_false(const ast::expr_false::ptr&)
{
    emit_opcode(opcode::OP_GetZero);
}

void compiler::emit_expr_true(const ast::expr_true::ptr&)
{
    emit_opcode(opcode::OP_GetByte, "1");
}

void compiler::emit_opcode(opcode op)
{
    function_->instructions.push_back(std::make_unique<instruction>());

    auto& inst = function_->instructions.back();
    inst->opcode = static_cast<std::uint8_t>(op);
    inst->size = opcode_size(std::uint8_t(op));
    inst->index = index_;

    index_ += inst->size;
}

void compiler::emit_opcode(opcode op, const std::string& data)
{
    function_->instructions.push_back(std::make_unique<instruction>());

    auto& inst = function_->instructions.back();
    inst->opcode = static_cast<std::uint8_t>(op);
    inst->size = opcode_size(std::uint8_t(op));
    inst->index = index_;
    inst->data.push_back(data);

    index_ += inst->size;
}

void compiler::emit_opcode(opcode op, const std::vector<std::string>& data)
{
    function_->instructions.push_back(std::make_unique<instruction>());

    auto& inst = function_->instructions.back();
    inst->opcode = static_cast<std::uint8_t>(op);
    inst->size = opcode_size(std::uint8_t(op));
    inst->index = index_;
    inst->data = data;

    index_ += inst->size;
}

void compiler::process_thread(const ast::decl_thread::ptr& decl)
{
    process_expr_parameters(decl->params);
    process_stmt_list(decl->stmt);
}

void compiler::process_stmt(const ast::stmt& stmt)
{
    switch (stmt.kind())
    {
        case ast::kind::stmt_list:
            process_stmt_list(stmt.as_list);
            break;
        case ast::kind::stmt_dev:
            process_stmt_dev(stmt.as_dev);
            break;
        case ast::kind::stmt_expr:
            process_stmt_expr(stmt.as_expr);
            break;
        case ast::kind::stmt_assign:
            process_stmt_assign(stmt.as_assign);
            break;
        case ast::kind::stmt_waittill:
            process_stmt_waittill(stmt.as_waittill);
            break;
        case ast::kind::stmt_if:
            process_stmt_if(stmt.as_if);
            break;
        case ast::kind::stmt_ifelse:
            process_stmt_ifelse(stmt.as_ifelse);
            break;
        case ast::kind::stmt_while:
            process_stmt_while(stmt.as_while);
            break;
        case ast::kind::stmt_dowhile:
            process_stmt_dowhile(stmt.as_dowhile);
            break;
        case ast::kind::stmt_for:
            process_stmt_for(stmt.as_for);
            break;
        case ast::kind::stmt_foreach:
            process_stmt_foreach(stmt.as_foreach);
            break;
        case ast::kind::stmt_switch:
            process_stmt_switch(stmt.as_switch);
            break;
        case ast::kind::stmt_call:
        case ast::kind::stmt_endon:
        case ast::kind::stmt_notify:
        case ast::kind::stmt_wait:
        case ast::kind::stmt_waittillmatch:
        case ast::kind::stmt_waittillframeend:
        case ast::kind::stmt_case:
        case ast::kind::stmt_default:
        case ast::kind::stmt_break:
        case ast::kind::stmt_continue:
        case ast::kind::stmt_return:
        case ast::kind::stmt_prof_begin:
        case ast::kind::stmt_prof_end:
            break;
        default:
            throw comp_error(stmt.loc(), "unknown statement");
    }
}

void compiler::process_stmt_list(const ast::stmt_list::ptr& stmt)
{
    for (const auto& entry : stmt->list)
    {
        process_stmt(entry);
    }
}

void compiler::process_stmt_dev(const ast::stmt_dev::ptr& stmt)
{
    process_stmt_list(stmt->list);
}

void compiler::process_stmt_expr(const ast::stmt_expr::ptr& stmt)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            process_expr(stmt->expr.as_increment->lvalue);
            break;
        case ast::kind::expr_decrement:
            process_expr(stmt->expr.as_decrement->lvalue);
            break;
        case ast::kind::expr_assign_equal:
        case ast::kind::expr_assign_add:
        case ast::kind::expr_assign_sub:
        case ast::kind::expr_assign_mul:
        case ast::kind::expr_assign_div:
        case ast::kind::expr_assign_mod:
        case ast::kind::expr_assign_shift_left:
        case ast::kind::expr_assign_shift_right:
        case ast::kind::expr_assign_bitwise_or:
        case ast::kind::expr_assign_bitwise_and:
        case ast::kind::expr_assign_bitwise_exor:
            process_expr(stmt->expr.as_assign->lvalue);
            break;
        case ast::kind::null:
            break;
        default:
            throw comp_error(stmt->loc(), "unknown expr statement expression");
    }
}

void compiler::process_stmt_assign(const ast::stmt_assign::ptr& stmt)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            process_expr(stmt->expr.as_increment->lvalue);
            break;
        case ast::kind::expr_decrement:
            process_expr(stmt->expr.as_decrement->lvalue);
            break;
        case ast::kind::expr_assign_equal:
        case ast::kind::expr_assign_add:
        case ast::kind::expr_assign_sub:
        case ast::kind::expr_assign_mul:
        case ast::kind::expr_assign_div:
        case ast::kind::expr_assign_mod:
        case ast::kind::expr_assign_shift_left:
        case ast::kind::expr_assign_shift_right:
        case ast::kind::expr_assign_bitwise_or:
        case ast::kind::expr_assign_bitwise_and:
        case ast::kind::expr_assign_bitwise_exor:
            process_expr(stmt->expr.as_assign->lvalue);
            break;
        default:
            throw comp_error(stmt->loc(), "unknown assign statement expression");
    }
}

void compiler::process_stmt_waittill(const ast::stmt_waittill::ptr& stmt)
{
    for (const auto& entry : stmt->args->list)
    {
        if (entry != ast::kind::expr_identifier)
        {
            throw comp_error(entry.loc(), "illegal waittill param, must be a local variable");
        }

        variable_register(entry.as_identifier->value);
    }
}

void compiler::process_stmt_if(const ast::stmt_if::ptr& stmt)
{
    process_stmt(stmt->stmt);
}

void compiler::process_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt)
{
    process_stmt(stmt->stmt_if);
    process_stmt(stmt->stmt_else);
}

void compiler::process_stmt_while(const ast::stmt_while::ptr& stmt)
{
    process_stmt(stmt->stmt);
}

void compiler::process_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt)
{
    process_stmt(stmt->stmt);
}

void compiler::process_stmt_for(const ast::stmt_for::ptr& stmt)
{
    process_stmt(stmt->init);
    process_stmt(stmt->stmt);
    process_stmt(stmt->iter);
}

void compiler::process_stmt_foreach(const ast::stmt_foreach::ptr& stmt)
{
    auto array_name = utils::string::va("_a%d", ++label_idx_);
    auto key_name = utils::string::va("_k%d", label_idx_);

    stmt->array = ast::expr(std::make_unique<ast::expr_identifier>(stmt->loc(), array_name));

    if (!stmt->use_key)
        stmt->key_expr = ast::expr(std::make_unique<ast::expr_identifier>(stmt->loc(), key_name));

    key_name = stmt->key_expr.as_identifier->value;

    if (stmt->use_key)
    {
        variable_register(key_name);
        process_expr(stmt->value_expr);
    }
    else
    {
        process_expr(stmt->value_expr);
        variable_register(key_name);
    }

    variable_register(array_name);
    process_stmt(stmt->stmt);
}

void compiler::process_stmt_switch(const ast::stmt_switch::ptr& stmt)
{
    auto stmt_list = std::make_unique<ast::stmt_list>(stmt->stmt->loc());
    auto current_case = ast::stmt(nullptr);

    auto num = stmt->stmt->list.size();

    for (auto i = 0u; i < num; i++)
    {
        auto& entry = stmt->stmt->list[0];

        if (entry == ast::kind::stmt_case || entry == ast::kind::stmt_default)
        {
            if (current_case.as_node != nullptr)
            {
                stmt_list->list.push_back(std::move(current_case));
            }

            current_case = std::move(stmt->stmt->list[0]);
            stmt->stmt->list.erase(stmt->stmt->list.begin());
        }
        else
        {
            if (current_case.as_node != nullptr)
            {
                if (current_case == ast::kind::stmt_case)
                {
                    current_case.as_case->stmt->list.push_back(std::move(entry));
                    stmt->stmt->list.erase(stmt->stmt->list.begin());
                }
                else
                {
                    current_case.as_default->stmt->list.push_back(std::move(entry));
                    stmt->stmt->list.erase(stmt->stmt->list.begin());
                }
            }
            else
            {
                throw comp_error(entry.loc(), "missing case statement");
            }
        }
    }

    if (current_case.as_node != nullptr)
    {
        stmt_list->list.push_back(std::move(current_case));
    }

    for (auto i = 0u; i < stmt_list->list.size(); i++)
    {
        auto& entry = stmt_list->list[i];

        if (entry == ast::kind::stmt_case)
        {
            process_stmt_list(entry.as_case->stmt);
        }
        else if (entry == ast::kind::stmt_default)
        {
            process_stmt_list(entry.as_default->stmt);
        }
    }

    stmt->stmt =std::move(stmt_list);
}

void compiler::process_expr(const ast::expr& expr)
{
    if (expr == ast::kind::expr_identifier)
    {
        variable_register(expr.as_identifier->value);
    }
    else if (expr == ast::kind::expr_array)
    {
        process_expr(expr.as_array->obj);
    }
}

void compiler::process_expr_parameters(const ast::expr_parameters::ptr& expr)
{
    for (const auto& entry : expr->list)
    {
        variable_register(entry->value);
    }
}

void compiler::variable_register(const std::string& name)
{
    auto found = false;
    for (std::size_t i = 0; i < local_stack_.size(); i++)
    {
        if (local_stack_[i] == name)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        local_stack_.push_back(name);
    }
}

auto compiler::variable_access(const ast::expr_identifier::ptr& name) -> std::string
{
    for (std::size_t i = 0; i < local_stack_.size(); i++)
    {
        if (local_stack_[i] == name->value)
        {
            return utils::string::va("%d", local_stack_.size() - 1 - i);
        }
    }

    throw comp_error(name->loc(), "local variable '" + name->value + "' not found.");
}

auto compiler::is_constant_condition(const ast::expr& expr) -> bool
{
    switch (expr.kind())
    {
        case ast::kind::null:
        case ast::kind::expr_true:
            return true;
        case ast::kind::expr_false:
            throw comp_error(expr.loc(), "condition can't be always false!");
        case ast::kind::expr_integer:
        {
            auto num = std::stoi(expr.as_integer->value);
            if (num != 0)
                return true;
            else
                throw comp_error(expr.loc(), "condition can't be always false!");
        }
        default:
            break;
    }

    return false;
}

auto compiler::create_label() -> std::string
{
    label_idx_++;
    auto name = utils::string::va("loc_%d", label_idx_);
    return name;
}

auto compiler::insert_label() -> std::string
{
    const auto itr = function_->labels.find(index_);

    if (itr != function_->labels.end())
    {
       return itr->second;
    }
    else
    {
        label_idx_++;
        auto name = utils::string::va("loc_%d", label_idx_);
        function_->labels.insert({index_, name});
        return name;
    }
}

void compiler::insert_label(const std::string& name)
{
    const auto itr = function_->labels.find(index_);

    if (itr != function_->labels.end())
    {
       for (auto& inst : function_->instructions)
       {
           switch (opcode(inst->opcode))
           {
                case opcode::OP_JumpOnFalse:
                case opcode::OP_JumpOnTrue:
                case opcode::OP_JumpOnFalseExpr:
                case opcode::OP_JumpOnTrueExpr:
                case opcode::OP_Jump:
                case opcode::OP_JumpBack:
                case opcode::OP_Switch:
                case opcode::OP_DevblockBegin:
                    if (inst->data[0] == name)
                        inst->data[0] = itr->second;
                    break;
                case opcode::OP_EndSwitch:
                default:
                    break;
           }
       }
    }
    else
    {
        function_->labels.insert({ index_, name });
    }
}

auto compiler::map_known_includes(const std::string&) -> bool
{
    return false;
}

void compiler::print_function(const function::ptr& func)
{
    output_->write_string("\n");
    output_->write_string(utils::string::va("sub_%s %i %i\n", func->name.data(), func->params, func->flags));

    for (auto& inst : func->instructions)
    {
        const auto itr = func->labels.find(inst->index);

        if (itr != func->labels.end())
        {
            output_->write_string(utils::string::va("\t%s\n", itr->second.data()));
        }

        this->print_instruction(inst);
    }

    output_->write_string(utils::string::va("end_%s\n", func->name.data()));
}

void compiler::print_instruction(const instruction::ptr& inst)
{
    output_->write_string(utils::string::va("\t\t%s(", resolver::opcode_name(inst->opcode).data()));

    switch (opcode(inst->opcode))
    {
        case opcode::OP_GetHash:
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
        case opcode::OP_ClearFieldVariable:
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
            output_->write_string(utils::string::va("\"%s\"", inst->data[0].data()));
            break;
        case opcode::OP_GetAnimation:
        case opcode::OP_GetFunction:
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            output_->write_string(utils::string::va("\"%s\", \"%s\"", inst->data[0].data(), inst->data[1].data()));
            break;
        case opcode::OP_SafeCreateLocalVariables:
            for (const auto& d : inst->data)
            {
                output_->write_string(utils::string::va("\"%s\"%s", d.data(), &d == &inst->data.back() ? "" : ", "));
            }
            break;
        case opcode::OP_EndSwitch:
            output_->write_string(utils::string::va("%s", inst->data[0].data()));
            {
                std::uint32_t totalcase = std::stoul(inst->data[0]);
                auto numerical = inst->data.back() == "i";
                auto index = 0;
                for (auto casenum = 0u; casenum < totalcase; casenum++)
                {
                    if (inst->data[1 + index] == "case")
                    {
                        auto fmt = numerical ? ", %s, %s, %s"s : ", %s, \"%s\", %s"s;
                        output_->write_string(utils::string::va(fmt, inst->data[1 + index].data(), inst->data[1 + index + 1].data(), inst->data[1 + index + 2].data()));
                        index += 3;
                    }
                    else if (inst->data[1 + index] == "default")
                    {
                        output_->write_string(utils::string::va(", %s, %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data()));
                        index += 2;
                    }
                }
            }
            break;
        default:
            for (const auto& d : inst->data)
            {
                output_->write_string(utils::string::va("%s%s", d.data(), &d == &inst->data.back() ? "" : ", "));
            }
            break;
    }

    output_->write_string(");\n");
}

} // namespace xsk::arc::t6
