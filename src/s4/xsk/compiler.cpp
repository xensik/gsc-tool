// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "s4.hpp"
#include "parser.hpp"
#include "lexer.hpp"

namespace xsk::gsc::s4
{

auto compiler::output() -> std::vector<function::ptr>
{
    return std::move(assembly_);
}

void compiler::compile(const std::string& file, std::vector<std::uint8_t>& data)
{
    filename_ = file;

    auto prog = parse_buffer(filename_, reinterpret_cast<const char*>(data.data()), data.size());

    compile_program(prog);
}

void compiler::mode(build mode)
{
    mode_ = mode;
}

auto compiler::parse_buffer(const std::string& file, const char* data, size_t size) -> ast::program::ptr
{
    ast::program::ptr result(nullptr);

    lexer lexer(mode_, file, data, size);

    parser parser(lexer, result);

    if (parser.parse() || result == nullptr)
    {
        throw comp_error(location(&file), "an unknown error ocurred while parsing gsc file");
    }

    return result;
}

auto compiler::parse_file(const std::string& file) -> ast::program::ptr
{
    auto data = resolver::file_data(file);

    return parse_buffer(file, std::get<1>(data), std::get<2>(data));
}

void compiler::compile_program(const ast::program::ptr& program)
{
    assembly_.clear();
    includes_.clear();
    animtrees_.clear();
    constants_.clear();
    local_functions_.clear();
    index_ = 1;
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
}

void compiler::emit_include(const ast::include::ptr& include)
{
    const auto& path = include->path->value;

    for (const auto& inc : includes_)
    {
        if (inc.name == path)
        {
            throw comp_error(include->loc(), "duplicated include file '" + path + "'");
        }
    }

    if (map_known_includes(path)) return;

    try
    {
        auto program = parse_file(path);

        std::vector<std::string> funcs;

        for (const auto& decl : program->declarations)
        {
            if (decl == ast::kind::decl_thread)
            {
                funcs.push_back(decl.as_thread->name->value);
            }
        }

        if (funcs.size() == 0)
        {
            throw comp_error(include->loc(), "empty include file '" + path + "'");
        }

        includes_.push_back(include_t(path, funcs));
    }
    catch(const std::exception& e)
    {
        throw comp_error(include->loc(), "error parsing include file '" + path + "': " + e.what());
    }
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
        throw comp_error(animtree->loc(), "cannot put #using_animtree inside developer block comment");

    animtrees_.push_back({ animtree->name->value, false });
}

void compiler::emit_decl_constant(const ast::decl_constant::ptr& constant)
{
    const auto itr = constants_.find(constant->name->value);

    if (itr != constants_.end())
        throw comp_error(constant->loc(), "duplicated constant '" + constant->name->value + "'");

    constants_.insert({ constant->name->value, std::move(constant->value) });
}

void compiler::emit_decl_thread(const ast::decl_thread::ptr& thread)
{
    function_ = std::make_unique<function>();
    function_->index = index_;
    function_->name = thread->name->value;

    auto blk = std::make_unique<block>();
    stack_idx_ = 0;
    label_idx_ = 0;
    can_break_ = false;
    can_continue_ = false;
    local_stack_.clear();
    break_blks_.clear();
    continue_blks_.clear();

    process_thread(thread, blk);

    emit_expr_parameters(thread->params, blk);
    emit_stmt_list(thread->stmt, blk, true);
    emit_opcode(opcode::OP_End);

    function_->size = index_ - function_->index;
    assembly_.push_back(std::move(function_));
}

void compiler::emit_stmt(const ast::stmt& stmt, const block::ptr& blk, bool last)
{
    switch (stmt.kind())
    {
        case ast::kind::stmt_list:
            emit_stmt_list(stmt.as_list, blk, last);
            break;
        case ast::kind::stmt_dev:
            emit_stmt_dev(stmt.as_dev, blk, last);
            break;
        case ast::kind::stmt_expr:
            emit_stmt_expr(stmt.as_expr, blk);
            break;
        case ast::kind::stmt_call:
            emit_stmt_call(stmt.as_call, blk);
            break;
        case ast::kind::stmt_assign:
            emit_stmt_assign(stmt.as_assign, blk);
            break;
        case ast::kind::stmt_endon:
            emit_stmt_endon(stmt.as_endon, blk);
            break;
        case ast::kind::stmt_notify:
            emit_stmt_notify(stmt.as_notify, blk);
            break;
        case ast::kind::stmt_wait:
            emit_stmt_wait(stmt.as_wait, blk);
            break;
        case ast::kind::stmt_waittill:
            emit_stmt_waittill(stmt.as_waittill, blk);
            break;
        case ast::kind::stmt_waittillmatch:
            emit_stmt_waittillmatch(stmt.as_waittillmatch, blk);
            break;
        case ast::kind::stmt_waittillframeend:
            emit_stmt_waittillframeend(stmt.as_waittillframeend, blk);
            break;
        case ast::kind::stmt_waitframe:
            emit_stmt_waitframe(stmt.as_waitframe, blk);
            break;
        case ast::kind::stmt_if:
            emit_stmt_if(stmt.as_if, blk, last);
            break;
        case ast::kind::stmt_ifelse:
            emit_stmt_ifelse(stmt.as_ifelse, blk, last);
            break;
        case ast::kind::stmt_while:
            emit_stmt_while(stmt.as_while, blk);
            break;
        case ast::kind::stmt_dowhile:
            emit_stmt_dowhile(stmt.as_dowhile, blk);
            break;
        case ast::kind::stmt_for:
            emit_stmt_for(stmt.as_for, blk);
            break;
        case ast::kind::stmt_foreach:
            emit_stmt_foreach(stmt.as_foreach, blk);
            break;
        case ast::kind::stmt_switch:
            emit_stmt_switch(stmt.as_switch, blk);
            break;
        case ast::kind::stmt_case:
            emit_stmt_case(stmt.as_case, blk);
            break;
        case ast::kind::stmt_default:
            emit_stmt_default(stmt.as_default, blk);
            break;
        case ast::kind::stmt_break:
            emit_stmt_break(stmt.as_break, blk);
            break;
        case ast::kind::stmt_continue:
            emit_stmt_continue(stmt.as_continue, blk);
            break;
        case ast::kind::stmt_return:
            emit_stmt_return(stmt.as_return, blk);
            break;
        case ast::kind::stmt_breakpoint:
            emit_stmt_breakpoint(stmt.as_breakpoint, blk);
            break;
        case ast::kind::stmt_prof_begin:
            emit_stmt_prof_begin(stmt.as_prof_begin, blk);
            break;
        case ast::kind::stmt_prof_end:
            emit_stmt_prof_end(stmt.as_prof_end, blk);
            break;
        default:
            throw comp_error(stmt.loc(), "unknown statement");
    }
}

void compiler::emit_stmt_list(const ast::stmt_list::ptr& stmt, const block::ptr& blk, bool last)
{
    for (const auto& entry : stmt->list)
    {
        bool last_ = (&entry == &stmt->list.back() && last) ? true : false;
        emit_stmt(entry, blk, last_);
    }
}

void compiler::emit_stmt_dev(const ast::stmt_dev::ptr& stmt, const block::ptr& blk, bool last)
{
    emit_stmt_list(stmt->list, blk, last);
}

void compiler::emit_stmt_expr(const ast::stmt_expr::ptr& stmt, const block::ptr& blk)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            emit_expr_increment(stmt->expr.as_increment, blk, true);
            break;
        case ast::kind::expr_decrement:
            emit_expr_decrement(stmt->expr.as_decrement, blk, true);
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
            emit_expr_assign(stmt->expr.as_assign, blk);
            break;
        case ast::kind::null:
            break;
        default:
            throw comp_error(stmt->loc(), "unknown expr statement expression");
    }
}

void compiler::emit_stmt_call(const ast::stmt_call::ptr& stmt, const block::ptr& blk)
{
    if (stmt->expr == ast::kind::expr_call)
        emit_expr_call(stmt->expr.as_call, blk, true);
    else if (stmt->expr == ast::kind::expr_method)
        emit_expr_method(stmt->expr.as_method, blk, true);
    else
        throw comp_error(stmt->loc(), "unknown call statement expression");
}

void compiler::emit_stmt_assign(const ast::stmt_assign::ptr& stmt, const block::ptr& blk)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            emit_expr_increment(stmt->expr.as_increment, blk, true);
            break;
        case ast::kind::expr_decrement:
            emit_expr_decrement(stmt->expr.as_decrement, blk, true);
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
            emit_expr_assign(stmt->expr.as_assign, blk);
            break;
        default:
            throw comp_error(stmt->loc(), "unknown assign statement expression");
    }
}

void compiler::emit_stmt_endon(const ast::stmt_endon::ptr& stmt, const block::ptr& blk)
{
    emit_expr(stmt->event, blk);
    emit_expr(stmt->obj, blk);
    emit_opcode(opcode::OP_endon);
}

void compiler::emit_stmt_notify(const ast::stmt_notify::ptr& stmt, const block::ptr& blk)
{
    emit_opcode(opcode::OP_voidCodepos);

    std::reverse(stmt->args->list.begin(), stmt->args->list.end());

    for (const auto& arg : stmt->args->list)
    {
        emit_expr(arg, blk);
    }

    emit_expr(stmt->event, blk);
    emit_expr(stmt->obj, blk);
    emit_opcode(opcode::OP_notify);
}

void compiler::emit_stmt_wait(const ast::stmt_wait::ptr& stmt, const block::ptr& blk)
{
    emit_expr(stmt->time, blk);
    emit_opcode(opcode::OP_wait);
}

void compiler::emit_stmt_waittill(const ast::stmt_waittill::ptr& stmt, const block::ptr& blk)
{
    emit_expr(stmt->event, blk);
    emit_expr(stmt->obj, blk);
    emit_opcode(opcode::OP_waittill);

    for (const auto& entry : stmt->args->list)
    {
        variable_create(entry.as_identifier, blk);
        emit_opcode(opcode::OP_SafeSetWaittillVariableFieldCached, variable_access_index(entry.as_identifier, blk));
    }

    emit_opcode(opcode::OP_clearparams);
}

void compiler::emit_stmt_waittillmatch(const ast::stmt_waittillmatch::ptr& stmt, const block::ptr& blk)
{
    emit_expr_arguments(stmt->args, blk);
    emit_expr(stmt->event, blk);
    emit_expr(stmt->obj, blk);
    emit_opcode(opcode::OP_waittillmatch, utils::string::va("%d", stmt->args->list.size()));
    emit_opcode(opcode::OP_waittillmatch2);
    emit_opcode(opcode::OP_clearparams);
}

void compiler::emit_stmt_waittillframeend(const ast::stmt_waittillframeend::ptr&, const block::ptr&)
{
    emit_opcode(opcode::OP_waittillFrameEnd);
}

void compiler::emit_stmt_waitframe(const ast::stmt_waitframe::ptr&, const block::ptr&)
{
    emit_opcode(opcode::OP_waitframe);
}

void compiler::emit_stmt_if(const ast::stmt_if::ptr& stmt, const block::ptr& blk, bool last)
{
    auto end_loc = create_label();

    if (stmt->test == ast::kind::expr_not)
    {
        emit_expr(stmt->test.as_not->rvalue, blk);
        emit_opcode(opcode::OP_JumpOnTrue, end_loc);
    }
    else
    {
        emit_expr(stmt->test, blk);
        emit_opcode(opcode::OP_JumpOnFalse, end_loc);
    }

    blk->transfer(stmt->blk);

    emit_stmt(stmt->stmt, stmt->blk, last);

    last ? emit_opcode(opcode::OP_End) : emit_remove_local_vars(stmt->blk);

    insert_label(end_loc);
}

void compiler::emit_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt, const block::ptr& blk, bool last)
{
    std::vector<block*> childs;
    auto else_loc = create_label();
    auto end_loc = create_label();

    if (stmt->test == ast::kind::expr_not)
    {
        emit_expr(stmt->test.as_not->rvalue, blk);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(stmt->test, blk);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    blk->transfer(stmt->blk_if);

    emit_stmt(stmt->stmt_if, stmt->blk_if, last);

    emit_remove_local_vars(stmt->blk_if);

    if (stmt->blk_if->abort == abort_t::abort_none)
        childs.push_back(stmt->blk_if.get());

    last ? emit_opcode(opcode::OP_End) : emit_opcode(opcode::OP_jump, end_loc);

    insert_label(else_loc);

    blk->transfer(stmt->blk_else);

    emit_stmt(stmt->stmt_else, stmt->blk_else, last);

    last ? emit_opcode(opcode::OP_End) : emit_remove_local_vars(stmt->blk_else);

    if (stmt->blk_else->abort == abort_t::abort_none)
        childs.push_back(stmt->blk_else.get());

    insert_label(end_loc);

    blk->init_from_child(childs);
}

void compiler::emit_stmt_while(const ast::stmt_while::ptr& stmt, const block::ptr& blk)
{
    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    auto old_break = can_break_;
    auto old_continue = can_continue_;
    break_blks_.clear();
    continue_blks_.clear();
    can_break_ = true;
    can_continue_ = true;

    auto break_loc = create_label();
    auto continue_loc = create_label();

    blk->transfer(stmt->blk);
    stmt->blk->loc_break = break_loc;
    stmt->blk->loc_continue = continue_loc;

    emit_create_local_vars(stmt->blk);

    blk->local_vars_create_count = stmt->blk->local_vars_create_count;

    for (auto i = 0u; i < blk->local_vars_create_count; i++)
    {
        if (!blk->local_vars.at(i).init)
            blk->local_vars.at(i).init = true;
    }

    auto begin_loc = insert_label();

    bool const_cond = is_constant_condition(stmt->test);

    if (!const_cond)
    {
        if (stmt->test == ast::kind::expr_not)
        {
            emit_expr(stmt->test.as_not->rvalue, blk);
            emit_opcode(opcode::OP_JumpOnTrue, break_loc);
        }
        else
        {
            emit_expr(stmt->test, blk);
            emit_opcode(opcode::OP_JumpOnFalse, break_loc);
        }
    }

    emit_stmt(stmt->stmt, stmt->blk, false);

    insert_label(continue_loc);
    emit_opcode(opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);

    if (const_cond)
        blk->init_from_child(break_blks_);

    can_break_ = old_break;
    can_continue_ = old_continue;
    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

void compiler::emit_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt, const block::ptr& blk)
{
    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    auto old_break = can_break_;
    auto old_continue = can_continue_;
    break_blks_.clear();
    continue_blks_.clear();
    can_break_ = true;
    can_continue_ = true;

    auto break_loc = create_label();
    auto continue_loc = create_label();

    blk->transfer(stmt->blk);
    stmt->blk->loc_break = break_loc;
    stmt->blk->loc_continue = continue_loc;

    emit_create_local_vars(stmt->blk);

    blk->local_vars_create_count = stmt->blk->local_vars_create_count;

    for (auto i = 0u; i < blk->local_vars_create_count; i++)
    {
        if (!blk->local_vars.at(i).init)
            blk->local_vars.at(i).init = true;
    }

    auto begin_loc = insert_label();

    emit_stmt(stmt->stmt, stmt->blk, false);

    insert_label(continue_loc);

    bool const_cond = is_constant_condition(stmt->test);

    if (!const_cond)
    {
        if (stmt->test == ast::kind::expr_not)
        {
            emit_expr(stmt->test.as_not->rvalue, blk);
            emit_opcode(opcode::OP_JumpOnTrue, break_loc);
        }
        else
        {
            emit_expr(stmt->test, blk);
            emit_opcode(opcode::OP_JumpOnFalse, break_loc);
        }
    }

    emit_opcode(opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);

    if (const_cond)
        blk->init_from_child(break_blks_);

    can_break_ = old_break;
    can_continue_ = old_continue;
    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

void compiler::emit_stmt_for(const ast::stmt_for::ptr& stmt, const block::ptr& blk)
{
    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    auto old_break = can_break_;
    auto old_continue = can_continue_;
    break_blks_.clear();
    continue_blks_.clear();
    can_break_ = false;
    can_continue_ = false;

    auto break_loc = create_label();
    auto continue_loc = create_label();

    emit_stmt(stmt->init, blk, false);

    blk->transfer(stmt->blk);
    stmt->blk->loc_break = break_loc;
    stmt->blk->loc_continue = continue_loc;

    emit_create_local_vars(stmt->blk);

    blk->local_vars_create_count = stmt->blk->local_vars_create_count;

    for (auto i = 0u; i < blk->local_vars_create_count; i++)
    {
        if (!blk->local_vars.at(i).init)
            blk->local_vars.at(i).init = true;
    }

    blk->transfer(stmt->blk_iter);

    auto begin_loc = insert_label();

    bool const_cond = is_constant_condition(stmt->test);

    if (!const_cond)
    {
        if (stmt->test == ast::kind::expr_not)
        {
            emit_expr(stmt->test.as_not->rvalue, blk);
            emit_opcode(opcode::OP_JumpOnTrue, break_loc);
        }
        else
        {
            emit_expr(stmt->test, blk);
            emit_opcode(opcode::OP_JumpOnFalse, break_loc);
        }
    }

    can_break_ = true;
    can_continue_ = true;

    emit_stmt(stmt->stmt, stmt->blk, false);

    if (stmt->blk->abort == abort_t::abort_none)
        continue_blks_.push_back(stmt->blk.get());

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);

    stmt->blk_iter->init_from_child(continue_blks_);

    emit_stmt(stmt->iter, stmt->blk_iter, false);
    emit_opcode(opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);

    if (const_cond)
        blk->init_from_child(break_blks_);

    can_break_ = old_break;
    can_continue_ = old_continue;
    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

void compiler::emit_stmt_foreach(const ast::stmt_foreach::ptr& stmt, const block::ptr& blk)
{
    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    auto old_break = can_break_;
    auto old_continue = can_continue_;
    break_blks_.clear();
    continue_blks_.clear();
    can_break_ = false;
    can_continue_ = false;

    auto break_loc = create_label();
    auto continue_loc = create_label();

    emit_expr(stmt->array_expr, blk);
    emit_expr_variable_ref(stmt->array, blk, true);
    emit_expr_variable(stmt->array, blk);
    emit_opcode(opcode::OP_CallBuiltin1, "getfirstarraykey");
    emit_expr_variable_ref(stmt->key_expr, blk, true);

    blk->transfer(stmt->ctx);
    stmt->ctx->loc_break = break_loc;
    stmt->ctx->loc_continue = continue_loc;

    emit_create_local_vars(stmt->ctx);

    blk->local_vars_create_count = stmt->ctx->local_vars_create_count;

    for (auto i = 0u; i < blk->local_vars_create_count; i++)
    {
        if (!blk->local_vars.at(i).init)
            blk->local_vars.at(i).init = true;
    }

    blk->transfer(stmt->ctx_post);

    auto begin_loc = insert_label();

    emit_expr_variable(stmt->key_expr, blk);
    emit_opcode(opcode::OP_IsDefined);
    emit_opcode(opcode::OP_JumpOnFalse, break_loc);

    can_break_ = true;
    can_continue_ = true;

    emit_expr_variable(stmt->key_expr, stmt->ctx);
    emit_opcode(opcode::OP_EvalLocalArrayCached, variable_access_index(stmt->array.as_identifier, stmt->ctx));
    emit_expr_variable_ref(stmt->value_expr, stmt->ctx, true);
    emit_stmt(stmt->stmt, stmt->ctx, false);

    if (stmt->ctx->abort == abort_t::abort_none)
        continue_blks_.push_back(stmt->ctx.get());

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);

    stmt->ctx_post->init_from_child(continue_blks_);

    emit_expr_variable(stmt->key_expr, stmt->ctx_post);
    emit_expr_variable(stmt->array, stmt->ctx_post);
    emit_opcode(opcode::OP_CallBuiltin2, "getnextarraykey");
    emit_expr_variable_ref(stmt->key_expr, stmt->ctx_post, true);
    emit_opcode(opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);
    emit_expr_clear_local(stmt->array.as_identifier, blk);
    if (!stmt->use_key) emit_expr_clear_local(stmt->key_expr.as_identifier, blk);

    can_break_ = old_break;
    can_continue_ = old_continue;
    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

void compiler::emit_stmt_switch(const ast::stmt_switch::ptr& stmt, const block::ptr& blk)
{
    auto old_breaks = break_blks_;
    auto old_break = can_break_;
    break_blks_.clear();
    can_break_ = false;

    auto jmptable_loc = create_label();
    auto break_loc = create_label();

    emit_expr(stmt->test, blk);
    emit_opcode(opcode::OP_switch, jmptable_loc);

    can_break_ = true;

    std::vector<std::string> data;
    data.push_back(utils::string::va("%d", stmt->stmt->list.size()));

    bool has_default = false;
    block* default_ctx = nullptr;

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

            blk->transfer(case_->blk);
            case_->blk->loc_break = break_loc;
            emit_stmt_list(case_->stmt, case_->blk, false);
            if (case_->stmt->list.size() > 0)
                emit_remove_local_vars(case_->blk);
        }
        else if (entry == ast::kind::stmt_default)
        {
            auto loc = insert_label();
            data.push_back("default");
            data.push_back(loc);

            has_default = true;
            default_ctx = entry.as_default->blk.get();

            blk->transfer(entry.as_default->blk);
            entry.as_default->blk->loc_break = break_loc;
            emit_stmt_list(entry.as_default->stmt, entry.as_default->blk, false);
            if (entry.as_default->stmt->list.size() > 0)
                emit_remove_local_vars(entry.as_default->blk);
        }
        else
        {
            throw comp_error(entry.loc(), "missing case statement");
        }
    }

    if (has_default)
    {
        if (default_ctx->abort == abort_t::abort_none)
        {
            break_blks_.push_back(default_ctx);
        }
        blk->init_from_child(break_blks_);
    }

    insert_label(jmptable_loc);

    emit_opcode(opcode::OP_endswitch, data);

    auto offset = static_cast<std::uint32_t>(7 * stmt->stmt->list.size());
    function_->instructions.back()->size += offset;
    index_ += offset;

    insert_label(break_loc);

    can_break_ = old_break;
    break_blks_ = old_breaks;
}

void compiler::emit_stmt_case(const ast::stmt_case::ptr& stmt, const block::ptr&)
{
    throw comp_error(stmt->loc(), "illegal case statement");
}

void compiler::emit_stmt_default(const ast::stmt_default::ptr& stmt, const block::ptr&)
{
    throw comp_error(stmt->loc(), "illegal default statement");
}

void compiler::emit_stmt_break(const ast::stmt_break::ptr& stmt, const block::ptr& blk)
{
    if (!can_break_ || blk->abort != abort_t::abort_none || blk->loc_break == "")
        throw comp_error(stmt->loc(), "illegal break statement");

    break_blks_.push_back(blk.get());
    emit_remove_local_vars(blk);
    blk->abort = abort_t::abort_break;
    emit_opcode(opcode::OP_jump, blk->loc_break);
}

void compiler::emit_stmt_continue(const ast::stmt_continue::ptr& stmt, const block::ptr& blk)
{
    if (!can_continue_ || blk->abort != abort_t::abort_none || blk->loc_continue == "")
        throw comp_error(stmt->loc(), "illegal continue statement");

    continue_blks_.push_back(blk.get());
    emit_remove_local_vars(blk);
    blk->abort = abort_t::abort_continue;
    emit_opcode(opcode::OP_jump, blk->loc_continue);
}

void compiler::emit_stmt_return(const ast::stmt_return::ptr& stmt, const block::ptr& blk)
{
    if (blk->abort == abort_t::abort_none)
        blk->abort = abort_t::abort_return;

    if (stmt->expr != ast::kind::null)
    {
        emit_expr(stmt->expr, blk);
        emit_opcode(opcode::OP_Return);
    }
    else
        emit_opcode(opcode::OP_End);
}

void compiler::emit_stmt_breakpoint(const ast::stmt_breakpoint::ptr&, const block::ptr&)
{
    // TODO:
}

void compiler::emit_stmt_prof_begin(const ast::stmt_prof_begin::ptr&, const block::ptr&)
{
    // TODO:
}

void compiler::emit_stmt_prof_end(const ast::stmt_prof_end::ptr&, const block::ptr&)
{
    // TODO:
}

void compiler::emit_expr(const ast::expr& expr, const block::ptr& blk)
{
    switch (expr.kind())
    {
        case ast::kind::expr_paren:
            emit_expr(expr.as_paren->child, blk);
            break;
        case ast::kind::expr_ternary:
            emit_expr_ternary(expr.as_ternary, blk);
            break;
        case ast::kind::expr_and:
            emit_expr_and(expr.as_and, blk);
            break;
        case ast::kind::expr_or:
            emit_expr_or(expr.as_or, blk);
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
            emit_expr_binary(expr.as_binary, blk);
            break;
        case ast::kind::expr_complement:
            emit_expr_complement(expr.as_complement, blk);
            break;
        case ast::kind::expr_negate:
            emit_expr_negate(expr.as_negate, blk);
            break;
        case ast::kind::expr_not:
            emit_expr_not(expr.as_not, blk);
            break;
        case ast::kind::expr_call:
            emit_expr_call(expr.as_call, blk, false);
            break;
        case ast::kind::expr_method:
            emit_expr_method(expr.as_method, blk, false);
            break;
        case ast::kind::expr_isdefined:
            emit_expr_isdefined(expr.as_isdefined, blk);
            break;
        case ast::kind::expr_istrue:
            emit_expr_istrue(expr.as_istrue, blk);
            break;
        case ast::kind::expr_reference:
            emit_expr_reference(expr.as_reference, blk);
            break;
        case ast::kind::expr_add_array:
            emit_expr_add_array(expr.as_add_array, blk);
            break;
        case ast::kind::expr_array:
            emit_expr_array(expr.as_array, blk);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr.as_field, blk);
            break;
        case ast::kind::expr_size:
            emit_expr_size(expr.as_size, blk);
            break;
        case ast::kind::expr_thisthread:
            emit_opcode(opcode::OP_GetThisthread);
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
        case ast::kind::expr_animtree:
            emit_expr_animtree(expr.as_animtree);
            break;
        case ast::kind::expr_identifier:
            emit_expr_local(expr.as_identifier, blk);
            break;
        case ast::kind::expr_istring:
            emit_expr_istring(expr.as_istring);
            break;
        case ast::kind::expr_string:
            emit_expr_string(expr.as_string);
            break;
        case ast::kind::expr_vector:
            emit_expr_vector(expr.as_vector, blk);
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

void compiler::emit_expr_assign(const ast::expr_assign::ptr& expr, const block::ptr& blk)
{
    if (expr->kind() == ast::kind::expr_assign_equal)
    {
        if (expr->rvalue == ast::kind::expr_undefined)
        {
            emit_expr_clear(expr->lvalue, blk);
        }
        else if (expr->lvalue == ast::kind::expr_tuple)
        {
            emit_expr(expr->rvalue, blk);
            emit_expr_tuple(expr->lvalue.as_tuple, blk);
        }
        else
        {
            emit_expr(expr->rvalue, blk);
            emit_expr_variable_ref(expr->lvalue, blk, true);
        }

        return;
    }

    emit_expr(expr->lvalue, blk);
    emit_expr(expr->rvalue, blk);

    switch (expr->kind())
    {
        case ast::kind::expr_assign_add:
            emit_opcode(opcode::OP_plus);
            break;
        case ast::kind::expr_assign_sub:
            emit_opcode(opcode::OP_minus);
            break;
        case ast::kind::expr_assign_mul:
            emit_opcode(opcode::OP_multiply);
            break;
        case ast::kind::expr_assign_div:
            emit_opcode(opcode::OP_divide);
            break;
        case ast::kind::expr_assign_mod:
            emit_opcode(opcode::OP_mod);
            break;
        case ast::kind::expr_assign_shift_left:
            emit_opcode(opcode::OP_shift_left);
            break;
        case ast::kind::expr_assign_shift_right:
            emit_opcode(opcode::OP_shift_right);
            break;
        case ast::kind::expr_assign_bitwise_or:
            emit_opcode(opcode::OP_bit_or);
            break;
        case ast::kind::expr_assign_bitwise_and:
            emit_opcode(opcode::OP_bit_and);
            break;
        case ast::kind::expr_assign_bitwise_exor:
            emit_opcode(opcode::OP_bit_ex_or);
            break;
        default:
            throw comp_error(expr->loc(), "unknown assign operation");
    }

    emit_expr_variable_ref(expr->lvalue, blk, true);
}

void compiler::emit_expr_clear(const ast::expr& expr, const block::ptr& blk)
{
    switch (expr.kind())
    {
        case ast::kind::expr_array:
            emit_expr(expr.as_array->key, blk);
            expr.as_array->obj == ast::kind::expr_game ? emit_opcode(opcode::OP_GetGameRef) : emit_expr_variable_ref(expr.as_array->obj, blk, false);
            emit_opcode(opcode::OP_ClearArray);
            break;
        case ast::kind::expr_field:
            emit_expr_object(expr.as_field->obj, blk);
            emit_opcode(opcode::OP_ClearFieldVariable, expr.as_field->field->value);
            break;
        case ast::kind::expr_identifier:
            emit_opcode(opcode::OP_GetUndefined);
            emit_expr_local_ref(expr.as_identifier, blk, true);
            break;
        default:
            throw comp_error(expr.loc(), "unknown clear variable lvalue");
    }
}

void compiler::emit_expr_clear_local(const ast::expr_identifier::ptr& expr, const block::ptr& blk)
{
    auto index = variable_stack_index(expr, blk);

    if (index == 0)
        emit_opcode(opcode::OP_ClearLocalVariableFieldCached0);
    else
        emit_opcode(opcode::OP_ClearLocalVariableFieldCached, variable_access_index(expr, blk));
}

void compiler::emit_expr_increment(const ast::expr_increment::ptr& expr, const block::ptr& blk, bool is_stmt)
{
    if (is_stmt)
    {
        emit_expr_variable_ref(expr->lvalue, blk, false);
        emit_opcode(opcode::OP_inc);
        emit_opcode(opcode::OP_SetVariableField);
    }
    else
    {
        // TODO:
    }
}

void compiler::emit_expr_decrement(const ast::expr_decrement::ptr& expr, const block::ptr& blk, bool is_stmt)
{
    if (is_stmt)
    {
        emit_expr_variable_ref(expr->lvalue, blk, false);
        emit_opcode(opcode::OP_dec);
        emit_opcode(opcode::OP_SetVariableField);
    }
    else
    {
        // TODO:
    }
}

void compiler::emit_expr_ternary(const ast::expr_ternary::ptr& expr, const block::ptr& blk)
{
    auto else_loc = create_label();
    auto end_loc = create_label();

    if (expr->test == ast::kind::expr_not)
    {
        emit_expr(expr->test.as_not->rvalue, blk);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(expr->test, blk);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    emit_expr(expr->true_expr, blk);
    emit_opcode(opcode::OP_jump, end_loc);

    insert_label(else_loc);
    emit_expr(expr->false_expr, blk);
    insert_label(end_loc);
}

void compiler::emit_expr_binary(const ast::expr_binary::ptr& expr, const block::ptr& blk)
{
    emit_expr(expr->lvalue, blk);
    emit_expr(expr->rvalue, blk);

    switch (expr->kind())
    {
        case ast::kind::expr_equality:
            emit_opcode(opcode::OP_equality);
            break;
        case ast::kind::expr_inequality:
            emit_opcode(opcode::OP_inequality);
            break;
        case ast::kind::expr_less:
            emit_opcode(opcode::OP_less);
            break;
        case ast::kind::expr_greater:
            emit_opcode(opcode::OP_greater);
            break;
        case ast::kind::expr_less_equal:
            emit_opcode(opcode::OP_less_equal);
            break;
        case ast::kind::expr_greater_equal:
            emit_opcode(opcode::OP_greater_equal);
            break;
        case ast::kind::expr_bitwise_or:
            emit_opcode(opcode::OP_bit_or);
            break;
        case ast::kind::expr_bitwise_and:
            emit_opcode(opcode::OP_bit_and);
            break;
        case ast::kind::expr_bitwise_exor:
            emit_opcode(opcode::OP_bit_ex_or);
            break;
        case ast::kind::expr_shift_left:
            emit_opcode(opcode::OP_shift_left);
            break;
        case ast::kind::expr_shift_right:
            emit_opcode(opcode::OP_shift_right);
            break;
        case ast::kind::expr_add:
            emit_opcode(opcode::OP_plus);
            break;
        case ast::kind::expr_sub:
            emit_opcode(opcode::OP_minus);
            break;
        case ast::kind::expr_mul:
            emit_opcode(opcode::OP_multiply);
            break;
        case ast::kind::expr_div:
            emit_opcode(opcode::OP_divide);
            break;
        case ast::kind::expr_mod:
            emit_opcode(opcode::OP_mod);
            break;
        default:
            throw comp_error(expr->loc(), "unknown binary expression");
    }
}

void compiler::emit_expr_and(const ast::expr_and::ptr& expr, const block::ptr& blk)
{
    auto label = create_label();

    emit_expr(expr->lvalue, blk);
    emit_opcode(opcode::OP_JumpOnFalseExpr, label);

    if (expr->rvalue == ast::kind::expr_not)
    {
        emit_expr(expr->rvalue.as_not->rvalue, blk);
        emit_opcode(opcode::OP_BoolNotAfterAnd);
    }
    else
    {
        emit_expr(expr->rvalue, blk);
        emit_opcode(opcode::OP_CastBool);
    }

    insert_label(label);
}

void compiler::emit_expr_or(const ast::expr_or::ptr& expr, const block::ptr& blk)
{
    auto label = create_label();

    emit_expr(expr->lvalue, blk);
    emit_opcode(opcode::OP_JumpOnTrueExpr, label);

    if (expr->rvalue == ast::kind::expr_not)
    {
        emit_expr(expr->rvalue.as_not->rvalue, blk);
        emit_opcode(opcode::OP_BoolNotAfterAnd);
    }
    else
    {
        emit_expr(expr->rvalue, blk);
        emit_opcode(opcode::OP_CastBool);
    }

    insert_label(label);
}

void compiler::emit_expr_complement(const ast::expr_complement::ptr& expr, const block::ptr& blk)
{
    emit_expr(expr->rvalue, blk);
    emit_opcode(opcode::OP_BoolComplement);
}

void compiler::emit_expr_negate(const ast::expr_negate::ptr& expr, const block::ptr& blk)
{
    emit_opcode(opcode::OP_GetZero);
    emit_expr(expr->rvalue, blk);
    emit_opcode(opcode::OP_minus);
}

void compiler::emit_expr_not(const ast::expr_not::ptr& expr, const block::ptr& blk)
{
    emit_expr(expr->rvalue, blk);
    emit_opcode(opcode::OP_BoolNot);
}

void compiler::emit_expr_call(const ast::expr_call::ptr& expr, const block::ptr& blk, bool is_stmt)
{
    if (expr->call == ast::kind::expr_pointer)
        emit_expr_call_pointer(expr->call.as_pointer, blk, is_stmt);
    else if (expr->call == ast::kind::expr_function)
        emit_expr_call_function(expr->call.as_function, blk, is_stmt);
    else
        throw comp_error(expr->loc(), "unknown function call expression");
}

void compiler::emit_expr_call_pointer(const ast::expr_pointer::ptr& expr, const block::ptr& blk, bool is_stmt)
{
    if (expr->mode == ast::call::mode::normal)
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(expr->args, blk);
    emit_expr(expr->func, blk);

    auto argcount = utils::string::va("%d", expr->args->list.size());

    switch (expr->mode)
    {
        case ast::call::mode::normal:
            emit_opcode(opcode::OP_ScriptFunctionCallPointer);
            break;
        case ast::call::mode::thread:
            emit_opcode(opcode::OP_ScriptThreadCallPointer, argcount);
            break;
        case ast::call::mode::childthread:
            emit_opcode(opcode::OP_ScriptChildThreadCallPointer, argcount);
            break;
        case ast::call::mode::builtin:
            emit_opcode(opcode::OP_CallBuiltinPointer, argcount);
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

void compiler::emit_expr_call_function(const ast::expr_function::ptr& expr, const block::ptr& blk, bool is_stmt)
{
    if (is_stmt && mode_ == gsc::build::prod)
    {
        const auto& name = expr->name->value;
        if (name == "assert" || name == "assertex" || name == "assertmsg") return;
    }

    auto type = resolve_function_type(expr);

    if (type != ast::call::type::builtin && expr->mode == ast::call::mode::normal && expr->args->list.size() > 0)
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(expr->args, blk);

    auto argcount = utils::string::va("%d", expr->args->list.size());

    if (type == ast::call::type::local)
    {
        switch (expr->mode)
        {
            case ast::call::mode::normal:
                if (expr->args->list.size() > 0)
                    emit_opcode(opcode::OP_ScriptLocalFunctionCall, expr->name->value);
                else
                    emit_opcode(opcode::OP_ScriptLocalFunctionCall2, expr->name->value);
                break;
            case ast::call::mode::thread:
                emit_opcode(opcode::OP_ScriptLocalThreadCall, { expr->name->value, argcount });
                break;
            case ast::call::mode::childthread:
                emit_opcode(opcode::OP_ScriptLocalChildThreadCall, { expr->name->value, argcount });
                break;
            case ast::call::mode::builtin:
                // no local builtins
                break;
        }
    }
    else if (type == ast::call::type::far)
    {
        switch (expr->mode)
        {
            case ast::call::mode::normal:
                if (expr->args->list.size() > 0)
                    emit_opcode(opcode::OP_ScriptFarFunctionCall, { expr->path->value, expr->name->value });
                else
                    emit_opcode(opcode::OP_ScriptFarFunctionCall2, { expr->path->value, expr->name->value });
                break;
            case ast::call::mode::thread:
                emit_opcode(opcode::OP_ScriptFarThreadCall, { expr->path->value, expr->name->value, argcount });
                break;
            case ast::call::mode::childthread:
                emit_opcode(opcode::OP_ScriptFarChildThreadCall, { expr->path->value, expr->name->value, argcount });
                break;
            case ast::call::mode::builtin:
                // no far builtins
                break;
        }
    }
    else if (type == ast::call::type::builtin)
    {
        if (expr->mode != ast::call::mode::normal)
            throw comp_error(expr->loc(), "builtin calls can't be threaded");

        switch (expr->args->list.size())
        {
            case 0:
                emit_opcode(opcode::OP_CallBuiltin0, expr->name->value);
                break;
            case 1:
                emit_opcode(opcode::OP_CallBuiltin1, expr->name->value);
                break;
            case 2:
                emit_opcode(opcode::OP_CallBuiltin2, expr->name->value);
                break;
            case 3:
                emit_opcode(opcode::OP_CallBuiltin3, expr->name->value);
                break;
            case 4:
                emit_opcode(opcode::OP_CallBuiltin4, expr->name->value);
                break;
            case 5:
                emit_opcode(opcode::OP_CallBuiltin5, expr->name->value);
                break;
            default:
                emit_opcode(opcode::OP_CallBuiltin, { expr->name->value, argcount });
                break;
        }
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

void compiler::emit_expr_method(const ast::expr_method::ptr& expr, const block::ptr& blk, bool is_stmt)
{
    if (expr->call == ast::kind::expr_pointer)
        emit_expr_method_pointer(expr->call.as_pointer, expr->obj, blk, is_stmt);
    else if (expr->call == ast::kind::expr_function)
        emit_expr_method_function(expr->call.as_function, expr->obj, blk, is_stmt);
    else
        throw comp_error(expr->loc(), "unknown method call expression");
}

void compiler::emit_expr_method_pointer(const ast::expr_pointer::ptr& expr, const ast::expr& obj, const block::ptr& blk, bool is_stmt)
{
    if (expr->mode == ast::call::mode::normal)
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(expr->args, blk);
    emit_expr(obj, blk);
    emit_expr(expr->func, blk);

    auto argcount = utils::string::va("%d", expr->args->list.size());

    switch (expr->mode)
    {
        case ast::call::mode::normal:
            emit_opcode(opcode::OP_ScriptMethodCallPointer);
            break;
        case ast::call::mode::thread:
            emit_opcode(opcode::OP_ScriptMethodThreadCallPointer, argcount);
            break;
        case ast::call::mode::childthread:
            emit_opcode(opcode::OP_ScriptMethodChildThreadCallPointer, argcount);
            break;
        case ast::call::mode::builtin:
            emit_opcode(opcode::OP_CallBuiltinMethodPointer, argcount);
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

void compiler::emit_expr_method_function(const ast::expr_function::ptr& expr, const ast::expr& obj, const block::ptr& blk, bool is_stmt)
{
    auto type = resolve_function_type(expr);

    if (type != ast::call::type::builtin && expr->mode == ast::call::mode::normal)
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(expr->args, blk);
    emit_expr(obj, blk);

    auto argcount = utils::string::va("%d", expr->args->list.size());

    if (type == ast::call::type::local)
    {
        switch (expr->mode)
        {
            case ast::call::mode::normal:
                emit_opcode(opcode::OP_ScriptLocalMethodCall, expr->name->value);
                break;
            case ast::call::mode::thread:
                emit_opcode(opcode::OP_ScriptLocalMethodThreadCall, { expr->name->value, argcount });
                break;
            case ast::call::mode::childthread:
                emit_opcode(opcode::OP_ScriptLocalMethodChildThreadCall, { expr->name->value, argcount });
                break;
            case ast::call::mode::builtin:
                // no local builtins
                break;
        }
    }
    else if (type == ast::call::type::far)
    {
        switch (expr->mode)
        {
            case ast::call::mode::normal:
                emit_opcode(opcode::OP_ScriptFarMethodCall, { expr->path->value, expr->name->value });
                break;
            case ast::call::mode::thread:
                emit_opcode(opcode::OP_ScriptFarMethodThreadCall, { expr->path->value, expr->name->value, argcount });
                break;
            case ast::call::mode::childthread:
                emit_opcode(opcode::OP_ScriptFarMethodChildThreadCall, { expr->path->value, expr->name->value, argcount });
                break;
            case ast::call::mode::builtin:
                // no far builtins
                break;
        }
    }
    else if (type == ast::call::type::builtin)
    {
        if (expr->mode != ast::call::mode::normal)
            throw comp_error(expr->loc(), "builtin calls can't be threaded");

        switch (expr->args->list.size())
        {
            case 0:
                emit_opcode(opcode::OP_CallBuiltinMethod0, expr->name->value);
                break;
            case 1:
                emit_opcode(opcode::OP_CallBuiltinMethod1, expr->name->value);
                break;
            case 2:
                emit_opcode(opcode::OP_CallBuiltinMethod2, expr->name->value);
                break;
            case 3:
                emit_opcode(opcode::OP_CallBuiltinMethod3, expr->name->value);
                break;
            case 4:
                emit_opcode(opcode::OP_CallBuiltinMethod4, expr->name->value);
                break;
            case 5:
                emit_opcode(opcode::OP_CallBuiltinMethod5, expr->name->value);
                break;
            default:
                emit_opcode(opcode::OP_CallBuiltinMethod, { expr->name->value, argcount });
                break;
        }
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

void compiler::emit_expr_add_array(const ast::expr_add_array::ptr& expr, const block::ptr& blk)
{
    emit_opcode(opcode::OP_EmptyArray);

    for (const auto& arg : expr->args->list)
    {
        emit_expr(arg, blk);
        emit_opcode(opcode::OP_AddArray);
    }
}

void compiler::emit_expr_parameters(const ast::expr_parameters::ptr& expr, const block::ptr& blk)
{
    auto num = static_cast<std::uint32_t>(expr->list.size());

    if (num)
    {
        std::vector<std::string> data;

        data.push_back(utils::string::va("%d", num));

        for (const auto& entry : expr->list)
        {
            variable_initialize(entry, blk);
            data.push_back(variable_create_index(entry, blk));
        }

        emit_opcode(opcode::OP_FormalParams, data);
        function_->instructions.back()->size += num;
        index_ += num;
    }
    else
    {
        emit_opcode( opcode::OP_checkclearparams);
    }
}

void compiler::emit_expr_arguments(const ast::expr_arguments::ptr& expr, const block::ptr& blk)
{
    std::reverse(expr->list.begin(), expr->list.end());

    for (auto& entry : expr->list)
    {
        emit_expr(entry, blk);
    }
}

void compiler::emit_expr_isdefined(const ast::expr_isdefined::ptr& expr, const block::ptr& blk)
{
    emit_expr(expr->expr, blk);
    emit_opcode(opcode::OP_IsDefined);
}

void compiler::emit_expr_istrue(const ast::expr_istrue::ptr& expr, const block::ptr& blk)
{
    emit_expr(expr->expr, blk);
    emit_opcode(opcode::OP_IsTrue);
}

void compiler::emit_expr_reference(const ast::expr_reference::ptr& expr, const block::ptr&)
{
    bool method = false;
    auto type = resolve_reference_type(expr, method);

    switch (type)
    {
        case ast::call::type::local:
            emit_opcode(opcode::OP_GetLocalFunction, expr->name->value);
            break;
        case ast::call::type::far:
            emit_opcode(opcode::OP_GetFarFunction, { expr->path->value, expr->name->value });
            break;
        case ast::call::type::builtin:
            if (method)
                emit_opcode(opcode::OP_GetBuiltinMethod, expr->name->value);
            else
                emit_opcode(opcode::OP_GetBuiltinFunction, expr->name->value);
            break;
    }
}

void compiler::emit_expr_size(const ast::expr_size::ptr& expr, const block::ptr& blk)
{
    emit_expr(expr->obj, blk);
    emit_opcode(opcode::OP_size);
}

void compiler::emit_expr_tuple(const ast::expr_tuple::ptr& expr, const block::ptr& blk)
{
    emit_expr_variable_ref(expr->temp, blk, true);

    auto index = 0;

    for (const auto& entry : expr->list)
    {
        if (index == 0)
            emit_opcode(opcode::OP_GetZero);
        else
            emit_opcode(opcode::OP_GetByte, utils::string::va("%d", index));

        index++;

        emit_opcode(opcode::OP_EvalLocalArrayCached, variable_access_index(expr->temp.as_identifier, blk));

        emit_expr_variable_ref(entry, blk, true);
    }

    emit_expr_clear_local(expr->temp.as_identifier, blk);
}

void compiler::emit_expr_variable_ref(const ast::expr& expr, const block::ptr& blk, bool set)
{
    switch (expr.kind())
    {
        case ast::kind::expr_array:
            emit_expr_array_ref(expr.as_array, blk, set);
            break;
        case ast::kind::expr_field:
            emit_expr_field_ref(expr.as_field, blk, set);
            break;
        case ast::kind::expr_identifier:
            emit_expr_local_ref(expr.as_identifier, blk, set);
            break;
        default:
            throw comp_error(expr.loc(), "invalid lvalue");
    }
}

void compiler::emit_expr_array_ref(const ast::expr_array::ptr& expr, const block::ptr& blk, bool set)
{
    emit_expr(expr->key, blk);

    switch (expr->obj.kind())
    {
        case ast::kind::expr_game:
            emit_opcode(opcode::OP_GetGameRef);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_array:
        case ast::kind::expr_field:
            emit_expr_variable_ref(expr->obj, blk, false);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_identifier:
        {
            if (!variable_initialized(expr->obj.as_identifier, blk))
            {
                variable_initialize(expr->obj.as_identifier, blk);
                emit_opcode(opcode::OP_EvalNewLocalArrayRefCached0, variable_create_index(expr->obj.as_identifier, blk));

                if (!set) throw comp_error(expr->loc(), "INTERNAL: VAR CREATED BUT NOT SET!");
            }
            else if (variable_stack_index(expr->obj.as_identifier, blk) == 0)
            {
                emit_opcode(opcode::OP_EvalLocalArrayRefCached0);
            }
            else
            {
                emit_opcode(opcode::OP_EvalLocalArrayRefCached, variable_access_index(expr->obj.as_identifier, blk));
            }

            if (set) emit_opcode(opcode::OP_SetVariableField);
        }
            break;
        case ast::kind::expr_call:
        case ast::kind::expr_method:
        default:
            throw comp_error(expr->loc(), "invalid array lvalue");
    }
}

void compiler::emit_expr_field_ref(const ast::expr_field::ptr& expr, const block::ptr& blk, bool set)
{
    const auto& field = expr->field->value;

    switch (expr->obj.kind())
    {
        case ast::kind::expr_level:
            set ? emit_opcode(opcode::OP_SetLevelFieldVariableField, field) : emit_opcode(opcode::OP_EvalLevelFieldVariableRef, field);
            break;
        case ast::kind::expr_anim:
            set ? emit_opcode(opcode::OP_SetAnimFieldVariableField, field) : emit_opcode(opcode::OP_EvalAnimFieldVariableRef, field);
            break;
        case ast::kind::expr_self:
            set ? emit_opcode(opcode::OP_SetSelfFieldVariableField, field) : emit_opcode(opcode::OP_EvalSelfFieldVariableRef, field);
            break;
        case ast::kind::expr_array:
            emit_expr_array(expr->obj.as_array, blk);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr->obj.as_field, blk);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableObjectCached, variable_access_index(expr->obj.as_identifier, blk));
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_call:
            emit_expr_call(expr->obj.as_call, blk, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case ast::kind::expr_method:
            emit_expr_method(expr->obj.as_method, blk, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        default:
            throw comp_error(expr->obj.loc(), "not an object");
    }
}

void compiler::emit_expr_local_ref(const ast::expr_identifier::ptr& expr, const block::ptr& blk, bool set)
{
    const auto itr = constants_.find(expr->value);

    if (itr != constants_.end())
    {
        throw comp_error(expr->loc(), "variable name already defined as constant '" + expr->value + "'");
    }

    if (set)
    {
        if (!variable_initialized(expr, blk))
        {
            variable_initialize(expr, blk);
            emit_opcode(opcode::OP_SetNewLocalVariableFieldCached0, variable_create_index(expr, blk));
        }
        else if (variable_stack_index(expr, blk) == 0)
        {
            emit_opcode(opcode::OP_SetLocalVariableFieldCached0);
        }
        else
        {
            emit_opcode(opcode::OP_SetLocalVariableFieldCached, variable_access_index(expr, blk));
        }
    }
    else
    {
        auto index = variable_stack_index(expr, blk);

        if (index == 0)
            emit_opcode(opcode::OP_EvalLocalVariableRefCached0);
        else
            emit_opcode(opcode::OP_EvalLocalVariableRefCached, variable_access_index(expr, blk));
    }
}

void compiler::emit_expr_variable(const ast::expr& expr, const block::ptr& blk)
{
    switch (expr.kind())
    {
        case ast::kind::expr_array:
            emit_expr_array(expr.as_array, blk);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr.as_field, blk);
            break;
        case ast::kind::expr_identifier:
            emit_expr_local(expr.as_identifier, blk);
            break;
        default:
            throw comp_error(expr.loc(), "invalid variable type.");
    }
}

void compiler::emit_expr_array(const ast::expr_array::ptr& expr, const block::ptr& blk)
{
    emit_expr(expr->key, blk);

    if (expr->obj == ast::kind::expr_identifier)
    {
        emit_opcode(opcode::OP_EvalLocalArrayCached, variable_access_index(expr->obj.as_identifier, blk));
    }
    else
    {
        emit_expr(expr->obj, blk);
        emit_opcode(opcode::OP_EvalArray);
    }
}

void compiler::emit_expr_field(const ast::expr_field::ptr& expr, const block::ptr& blk)
{
    const auto& field = expr->field->value;

    switch (expr->obj.kind())
    {
        case ast::kind::expr_level:
            emit_opcode(opcode::OP_EvalLevelFieldVariable, field);
            break;
        case ast::kind::expr_anim:
            emit_opcode(opcode::OP_EvalAnimFieldVariable, field);
            break;
        case ast::kind::expr_self:
            emit_opcode(opcode::OP_EvalSelfFieldVariable, field);
            break;
        case ast::kind::expr_array:
            emit_expr_array(expr->obj.as_array, blk);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr->obj.as_field, blk);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_call:
            emit_expr_call(expr->obj.as_call, blk, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_method:
            emit_expr_method(expr->obj.as_method, blk, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case ast::kind::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableObjectCached, variable_access_index(expr->obj.as_identifier, blk));
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        default:
            throw comp_error(expr->loc(), "unknown field variable object type");
    }
}

void compiler::emit_expr_local(const ast::expr_identifier::ptr& expr, const block::ptr& blk)
{
    // is constant ( should only allow: string, loc string, number, vector)
    const auto itr = constants_.find(expr->value);

    if (itr != constants_.end())
    {
        emit_expr(itr->second, blk);
        return;
    }

    // is local var
    auto index = variable_stack_index(expr, blk);

    switch (index)
    {
        case 0:
            emit_opcode(opcode::OP_EvalLocalVariableCached0);
            break;
        case 1:
            emit_opcode(opcode::OP_EvalLocalVariableCached1);
            break;
        case 2:
            emit_opcode(opcode::OP_EvalLocalVariableCached2);
            break;
        case 3:
            emit_opcode(opcode::OP_EvalLocalVariableCached3);
            break;
        case 4:
            emit_opcode(opcode::OP_EvalLocalVariableCached4);
            break;
        case 5:
            emit_opcode(opcode::OP_EvalLocalVariableCached5);
            break;
        default:
            emit_opcode(opcode::OP_EvalLocalVariableCached, variable_access_index(expr, blk));
            break;
    }
}

void compiler::emit_expr_object(const ast::expr& expr, const block::ptr& blk)
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
            emit_expr_array(expr.as_array, blk);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case ast::kind::expr_field:
            emit_expr_field(expr.as_field, blk);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case ast::kind::expr_call:
            emit_expr_call(expr.as_call, blk, false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case ast::kind::expr_method:
            emit_expr_method(expr.as_method, blk, false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case ast::kind::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableObjectCached, variable_access_index(expr.as_identifier, blk));
            break;
        default:
            throw comp_error(expr.loc(), "not an object");
    }
}

void compiler::emit_expr_vector(const ast::expr_vector::ptr& expr, const block::ptr& blk)
{
    std::vector<std::string> data;

    bool isexpr = false;

    if (expr->x == ast::kind::expr_integer)
        data.push_back(expr->x.as_integer->value);
    else if (expr->x == ast::kind::expr_float)
        data.push_back(expr->x.as_float->value);
    else isexpr = true;

    if (expr->y == ast::kind::expr_integer)
        data.push_back(expr->y.as_integer->value);
    else if (expr->y == ast::kind::expr_float)
        data.push_back(expr->y.as_float->value);
    else isexpr = true;

    if (expr->z == ast::kind::expr_integer)
        data.push_back(expr->z.as_integer->value);
    else if (expr->z == ast::kind::expr_float)
        data.push_back(expr->z.as_float->value);
    else isexpr = true;

    if (!isexpr)
    {
        emit_opcode(opcode::OP_GetVector, data);
    }
    else
    {
        emit_expr(expr->z, blk);
        emit_expr(expr->y, blk);
        emit_expr(expr->x, blk);
        emit_opcode(opcode::OP_vector);
    }
}

void compiler::emit_expr_animation(const ast::expr_animation::ptr& expr)
{
    if (animtrees_.size() == 0)
    {
        throw comp_error(expr->loc(), "trying to use animation without specified using animtree");
    }

    auto& tree = animtrees_.back();

    if (tree.loaded)
    {
        emit_opcode(opcode::OP_GetAnimation, { "", expr->value });
    }
    else
    {
        emit_opcode(opcode::OP_GetAnimation, { tree.name, expr->value });
        tree.loaded = true;
    }
}

void compiler::emit_expr_animtree(const ast::expr_animtree::ptr& expr)
{
    if (animtrees_.size() == 0)
    {
        throw comp_error( expr->loc(), "trying to use animtree without specified using animtree");
    }

    auto& tree = animtrees_.back();

    if (tree.loaded)
    {
        emit_opcode(opcode::OP_GetAnimTree, "");
    }
    else
    {
        emit_opcode(opcode::OP_GetAnimTree, tree.name);
        tree.loaded = true;
    }
}

void compiler::emit_expr_istring(const ast::expr_istring::ptr& expr)
{
    emit_opcode(opcode::OP_GetIString, expr->value);
}

void compiler::emit_expr_string(const ast::expr_string::ptr& expr)
{
    emit_opcode(opcode::OP_GetString, expr->value);
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

void compiler::emit_create_local_vars(const block::ptr& blk)
{
    if (blk->local_vars_create_count != blk->local_vars_public_count)
    {
        for (auto i = blk->local_vars_create_count; i < blk->local_vars_public_count; i++)
        {
            auto data = utils::string::va("%d", blk->local_vars.at(i).create);
            emit_opcode(opcode::OP_CreateLocalVariable, data);
            blk->local_vars.at(i).init = true;
        }
        blk->local_vars_create_count = blk->local_vars_public_count;
    }
}

void compiler::emit_remove_local_vars(const block::ptr& blk)
{
    if (blk->abort == abort_t::abort_none)
    {
        auto count = blk->local_vars_create_count - blk->local_vars_public_count;

        if (count > 0)
        {
            auto data = utils::string::va("%d", count);
            emit_opcode(opcode::OP_RemoveLocalVariables, data);
        }
    }
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

void compiler::process_thread(const ast::decl_thread::ptr& decl, const block::ptr& blk)
{
    process_expr_parameters(decl->params, blk);
    process_stmt_list(decl->stmt, blk);
}

void compiler::process_stmt(const ast::stmt& stmt, const block::ptr& blk)
{
    switch (stmt.kind())
    {
        case ast::kind::stmt_list:
            process_stmt_list(stmt.as_list, blk);
            break;
        case ast::kind::stmt_dev:
            process_stmt_dev(stmt.as_dev, blk);
            break;
        case ast::kind::stmt_expr:
            process_stmt_expr(stmt.as_expr, blk);
            break;
        case ast::kind::stmt_assign:
            process_stmt_assign(stmt.as_assign, blk);
            break;
        case ast::kind::stmt_waittill:
            process_stmt_waittill(stmt.as_waittill, blk);
            break;
        case ast::kind::stmt_if:
            process_stmt_if(stmt.as_if, blk);
            break;
        case ast::kind::stmt_ifelse:
            process_stmt_ifelse(stmt.as_ifelse, blk);
            break;
        case ast::kind::stmt_while:
            process_stmt_while(stmt.as_while, blk);
            break;
        case ast::kind::stmt_dowhile:
            process_stmt_dowhile(stmt.as_dowhile, blk);
            break;
        case ast::kind::stmt_for:
            process_stmt_for(stmt.as_for, blk);
            break;
        case ast::kind::stmt_foreach:
            process_stmt_foreach(stmt.as_foreach, blk);
            break;
        case ast::kind::stmt_switch:
            process_stmt_switch(stmt.as_switch, blk);
            break;
        case ast::kind::stmt_break:
            process_stmt_break(stmt.as_break, blk);
            break;
        case ast::kind::stmt_continue:
            process_stmt_continue(stmt.as_continue, blk);
            break;
        case ast::kind::stmt_return:
            process_stmt_return(stmt.as_return, blk);
            break;
        case ast::kind::stmt_call:
        case ast::kind::stmt_endon:
        case ast::kind::stmt_notify:
        case ast::kind::stmt_wait:
        case ast::kind::stmt_waittillmatch:
        case ast::kind::stmt_waittillframeend:
        case ast::kind::stmt_waitframe:
        case ast::kind::stmt_case:
        case ast::kind::stmt_default:
        case ast::kind::stmt_breakpoint:
        case ast::kind::stmt_prof_begin:
        case ast::kind::stmt_prof_end:
            break;
        default:
            throw comp_error(stmt.loc(), "unknown statement");
    }
}

void compiler::process_stmt_list(const ast::stmt_list::ptr& stmt, const block::ptr& blk)
{
    for (const auto& entry : stmt->list)
    {
        process_stmt(entry, blk);
    }
}

void compiler::process_stmt_dev(const ast::stmt_dev::ptr& stmt, const block::ptr& blk)
{
    process_stmt_list(stmt->list, blk);
}

void compiler::process_stmt_expr(const ast::stmt_expr::ptr& stmt, const block::ptr& blk)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            process_expr(stmt->expr.as_increment->lvalue, blk);
            break;
        case ast::kind::expr_decrement:
            process_expr(stmt->expr.as_decrement->lvalue, blk);
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
            process_expr(stmt->expr.as_assign->lvalue, blk);
            break;
        case ast::kind::null:
            break;
        default:
            throw comp_error(stmt->loc(), "unknown expr statement expression");
    }
}

void compiler::process_stmt_assign(const ast::stmt_assign::ptr& stmt, const block::ptr& blk)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            process_expr(stmt->expr.as_increment->lvalue, blk);
            break;
        case ast::kind::expr_decrement:
            process_expr(stmt->expr.as_decrement->lvalue, blk);
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
            process_expr(stmt->expr.as_assign->lvalue, blk);
            break;
        default:
            throw comp_error(stmt->loc(), "unknown assign statement expression");
    }
}

void compiler::process_stmt_waittill(const ast::stmt_waittill::ptr& stmt, const block::ptr& blk)
{
    for (const auto& entry : stmt->args->list)
    {
        if (entry != ast::kind::expr_identifier)
        {
            throw comp_error(entry.loc(), "illegal waittill param, must be a local variable");
        }

        variable_register(entry.as_identifier->value, blk);
    }
}

void compiler::process_stmt_if(const ast::stmt_if::ptr& stmt, const block::ptr& blk)
{
    stmt->blk = std::make_unique<block>();

    blk->copy(stmt->blk);
    process_stmt(stmt->stmt, stmt->blk);

    std::vector<block*> childs({ stmt->blk.get() });
    blk->merge(childs);
}

void compiler::process_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt, const block::ptr& blk)
{
    std::vector<block*> childs;
    auto abort = abort_t::abort_return;

    stmt->blk_if = std::make_unique<block>();
    stmt->blk_else = std::make_unique<block>();

    blk->copy(stmt->blk_if);
    process_stmt(stmt->stmt_if, stmt->blk_if);

    if (stmt->blk_if->abort <= abort_t::abort_return)
    {
        abort = stmt->blk_if->abort;
        if (abort == abort_t::abort_none)
            childs.push_back(stmt->blk_if.get());
    }

    blk->copy(stmt->blk_else);
    process_stmt(stmt->stmt_else, stmt->blk_else);

    if (stmt->blk_else->abort <= abort)
    {
        abort = stmt->blk_else->abort;
        if (abort == abort_t::abort_none)
            childs.push_back(stmt->blk_else.get());
    }

    if (blk->abort == abort_t::abort_none)
        blk->abort = abort;

    blk->append(childs);
    blk->merge(childs);
}

void compiler::process_stmt_while(const ast::stmt_while::ptr& stmt, const block::ptr& blk)
{
    bool const_cond = is_constant_condition(stmt->test);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    stmt->blk = std::make_unique<block>();

    blk->copy(stmt->blk);
    process_stmt(stmt->stmt, stmt->blk);

    continue_blks_.push_back(stmt->blk.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        blk->append({ continue_blks_.at(i) });

    if (const_cond) blk->append(break_blks_);

    blk->merge({ stmt->blk.get() });

    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

void compiler::process_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt, const block::ptr& blk)
{
    bool const_cond = is_constant_condition(stmt->test);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    stmt->blk = std::make_unique<block>();

    blk->copy(stmt->blk);
    process_stmt(stmt->stmt, stmt->blk);

    continue_blks_.push_back(stmt->blk.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        blk->append({ continue_blks_.at(i) });

    if (const_cond) blk->append(break_blks_);

    blk->merge({ stmt->blk.get() });

    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

void compiler::process_stmt_for(const ast::stmt_for::ptr& stmt, const block::ptr& blk)
{
    bool const_cond = is_constant_condition(stmt->test);

    stmt->blk = std::make_unique<block>();
    stmt->blk_iter = std::make_unique<block>();

    process_stmt(stmt->init, blk);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    blk->copy(stmt->blk);
    blk->copy(stmt->blk_iter);

    process_stmt(stmt->stmt, stmt->blk);

    continue_blks_.push_back(stmt->blk.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        blk->append({ continue_blks_.at(i) });

    process_stmt(stmt->iter, stmt->blk_iter);

    blk->append({ stmt->blk_iter.get() });
    blk->merge({ stmt->blk_iter.get() });

    if (const_cond) blk->append(break_blks_);

    blk->merge({ stmt->blk.get() });

    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

void compiler::process_stmt_foreach(const ast::stmt_foreach::ptr& stmt, const block::ptr& blk)
{
    auto array_name = utils::string::va("_temp_%d", ++label_idx_);
    auto key_name = utils::string::va("_temp_%d", ++label_idx_);

    stmt->array = ast::expr(std::make_unique<ast::expr_identifier>(stmt->loc(), array_name));

    if (!stmt->use_key)
        stmt->key_expr = ast::expr(std::make_unique<ast::expr_identifier>(stmt->loc(), key_name));

    key_name = stmt->key_expr.as_identifier->value;

    // calculate variables

    stmt->ctx = std::make_unique<block>();
    stmt->ctx_post = std::make_unique<block>();

    // calculate pre_expr variables
    process_expr(stmt->array, blk);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    blk->copy(stmt->ctx);
    blk->copy(stmt->ctx_post);

    // calculate stmt variables & add missing array access as first stmt
    process_expr(stmt->value_expr, stmt->ctx);
    process_stmt(stmt->stmt, stmt->ctx);

    continue_blks_.push_back(stmt->ctx.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        blk->append({ continue_blks_.at(i) });

    process_expr(stmt->key_expr, stmt->ctx_post);

    blk->append({ stmt->ctx_post.get() });
    blk->merge({ stmt->ctx_post.get() });
    blk->merge({ stmt->ctx.get() });

    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

void compiler::process_stmt_switch(const ast::stmt_switch::ptr& stmt, const block::ptr& blk)
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

    // calculate variables
    stmt->ctx = std::make_unique<block>();
    std::vector<block*> childs;
    auto abort = abort_t::abort_return;
    bool has_default = false;
    block* default_ctx = nullptr;
    auto old_breaks = break_blks_;
    break_blks_.clear();

    for (auto i = 0u; i < stmt_list->list.size(); i++)
    {
        auto& entry = stmt_list->list[i];

        if (entry == ast::kind::stmt_case)
        {
            entry.as_case->blk = std::make_unique<block>();
            blk->copy(entry.as_case->blk);
            process_stmt_list(entry.as_case->stmt, entry.as_case->blk);

            if (entry.as_case->blk->abort != abort_t::abort_none)
            {
                if (entry.as_case->blk->abort == abort_t::abort_break )
                {
                    entry.as_case->blk->abort = abort_t::abort_none;
                    abort = abort_t::abort_none;
                    childs.push_back(entry.as_case->blk.get());
                }
                else if (entry.as_case->blk->abort <= abort )
                {
                    abort = entry.as_case->blk->abort;
                }
            }
        }
        else if (entry == ast::kind::stmt_default)
        {
            entry.as_default->blk = std::make_unique<block>();
            blk->copy(entry.as_default->blk);
            process_stmt_list(entry.as_default->stmt, entry.as_default->blk);
            has_default = true;
            default_ctx = entry.as_default->blk.get();

            if (entry.as_default->blk->abort != abort_t::abort_none)
            {
                if (entry.as_default->blk->abort == abort_t::abort_break )
                {
                    entry.as_default->blk->abort = abort_t::abort_none;
                    abort = abort_t::abort_none;
                    childs.push_back(entry.as_default->blk.get());
                }
                else if (entry.as_default->blk->abort <= abort )
                {
                    abort = entry.as_default->blk->abort;
                }
            }
        }
    }

    stmt->stmt =std::move(stmt_list);

    if (has_default)
    {
        if (default_ctx->abort == abort_t::abort_none)
        {
            break_blks_.push_back(default_ctx);

            if (blk->abort == abort_t::abort_none)
                blk->abort = abort;
        }

        blk->append(break_blks_);
        blk->merge(childs);
    }

    break_blks_ = old_breaks;
}

void compiler::process_stmt_break(const ast::stmt_break::ptr&, const block::ptr& blk)
{
    if (blk->abort == abort_t::abort_none)
    {
        break_blks_.push_back(blk.get());
        blk->abort = abort_t::abort_break;
    }
}

void compiler::process_stmt_continue(const ast::stmt_continue::ptr&, const block::ptr& blk)
{
    if (blk->abort == abort_t::abort_none)
    {
        continue_blks_.push_back(blk.get());
        blk->abort = abort_t::abort_continue;
    }
}

void compiler::process_stmt_return(const ast::stmt_return::ptr&, const block::ptr& blk)
{
    if (blk->abort == abort_t::abort_none)
    {
        blk->abort = abort_t::abort_return;
    }
}

void compiler::process_expr(const ast::expr& expr, const block::ptr& blk)
{
    if (expr == ast::kind::expr_identifier)
    {
        variable_register(expr.as_identifier->value, blk);
    }
    else if (expr == ast::kind::expr_array)
    {
        process_expr(expr.as_array->obj, blk);
    }
    else if (expr == ast::kind::expr_tuple)
    {
        process_expr_tuple(expr.as_tuple, blk);
    }
}

void compiler::process_expr_tuple(const ast::expr_tuple::ptr& expr, const block::ptr& blk)
{
    auto array = utils::string::va("_temp_%d", ++label_idx_);
    expr->temp = ast::expr(std::make_unique<ast::expr_identifier>(expr->loc(), array));

    process_expr(expr->temp, blk);

    for (const auto& entry : expr->list)
    {
        process_expr(entry, blk);
    }
}

void compiler::process_expr_parameters(const ast::expr_parameters::ptr& decl, const block::ptr& blk)
{
    for (const auto& entry : decl->list)
    {
        variable_register(entry->value, blk);
    }
}

void compiler::variable_register(const std::string& name, const block::ptr& blk)
{
    auto it = std::find_if (blk->local_vars.begin(), blk->local_vars.end(),
            [&](const gsc::local_var& v) { return v.name == name; });

    if (it == blk->local_vars.end())
    {
        auto found = false;
        for (std::size_t i = 0; i < local_stack_.size(); i++)
        {
            if (local_stack_[i] == name)
            {
                blk->local_vars.push_back({ name, static_cast<uint8_t>(i), false });
                found = true;
                break;
            }
        }

        if (!found)
        {
            blk->local_vars.push_back({ name, stack_idx_, false });
            local_stack_.push_back(name);
            stack_idx_++;
        }
    }
}

void compiler::variable_initialize(const ast::expr_identifier::ptr& name, const block::ptr& blk)
{
    for (std::uint32_t i = 0; i < blk->local_vars.size(); i++)
    {
        if (blk->local_vars[i].name == name->value)
        {
            if (!blk->local_vars[i].init)
            {
                for (std::uint32_t j = 0; j < i; j++)
                {
                    if (!blk->local_vars[j].init)
                    {
                        emit_opcode(opcode::OP_CreateLocalVariable, utils::string::va("%d", blk->local_vars[j].create));
                        blk->local_vars[j].init = true;
                    }
                }
                blk->local_vars[i].init = true;
                blk->local_vars_create_count = i + 1;
                return;
            }
        }
    }

    throw comp_error(name->loc(), "local variable '" + name->value + "' not found.");
}

void compiler::variable_create(const ast::expr_identifier::ptr& name, const block::ptr& blk)
{
    for (std::size_t i = 0; i < blk->local_vars.size(); i++)
    {
        auto& var = blk->local_vars.at(i);
        if (var.name == name->value)
        {
            if (!var.init)
            {
                emit_opcode(opcode::OP_CreateLocalVariable, utils::string::va("%d", var.create));
                var.init = true;
                blk->local_vars_create_count++;
            }
            return;
        }
    }

    throw comp_error(name->loc(), "local variable '" + name->value + "' not found.");
}

auto compiler::variable_stack_index(const ast::expr_identifier::ptr& name, const block::ptr& blk) -> std::uint8_t
{
    for (std::size_t i = 0; i < blk->local_vars.size(); i++)
    {
        if (blk->local_vars[i].name == name->value)
        {
            if (blk->local_vars.at(i).init)
            {
                return static_cast<std::uint8_t>(blk->local_vars_create_count - 1 - i);
            }

            throw comp_error(name->loc(), "local variable '" + name->value + "' not initialized.");
        }
    }

    throw comp_error(name->loc(), "local variable '" + name->value + "' not found.");
}

auto compiler::variable_create_index(const ast::expr_identifier::ptr& name, const block::ptr& blk) -> std::string
{
    for (std::size_t i = 0; i < blk->local_vars.size(); i++)
    {
        if (blk->local_vars[i].name == name->value)
            return utils::string::va("%d", blk->local_vars[i].create);
    }

    throw comp_error(name->loc(), "local variable '" + name->value + "' not found.");
}

auto compiler::variable_access_index(const ast::expr_identifier::ptr& name, const block::ptr& blk) -> std::string
{
    for (std::size_t i = 0; i < blk->local_vars.size(); i++)
    {
        if (blk->local_vars[i].name == name->value)
        {
            if (blk->local_vars.at(i).init)
            {
                return utils::string::va("%d", blk->local_vars_create_count - 1 - i);
            }

            throw comp_error(name->loc(), "local variable '" + name->value + "' not initialized.");
        }
    }

    throw comp_error(name->loc(), "local variable '" + name->value + "' not found.");
}

auto compiler::variable_initialized(const ast::expr_identifier::ptr& name, const block::ptr& blk) -> bool
{
    for (std::size_t i = 0; i < blk->local_vars.size(); i++)
    {
        if (blk->local_vars[i].name == name->value)
        {
            return blk->local_vars.at(i).init;
        }
    }

    throw comp_error(name->loc(), "local variable '" + name->value + "' not found.");
}

auto compiler::resolve_function_type(const ast::expr_function::ptr& expr) -> ast::call::type
{
    if (expr->path->value != "")
        return ast::call::type::far;

    auto& name = expr->name->value;

    if (resolver::find_function(name) || resolver::find_method(name))
        return ast::call::type::builtin;

    for (const auto& entry : local_functions_)
    {
        if (entry == name)
            return ast::call::type::local;
    }

    for (const auto& inc : includes_)
    {
        for (const auto& fun : inc.funcs)
        {
            if (name == fun)
            {
                expr->path->value = inc.name;
                return ast::call::type::far;
            }
        }
    }

    throw comp_error(expr->loc(), "couldn't determine function type");
}

auto compiler::resolve_reference_type(const ast::expr_reference::ptr& expr, bool& method) -> ast::call::type
{
    if (expr->path->value != "")
        return ast::call::type::far;

    auto& name = expr->name->value;

    if (resolver::find_function(name))
    {
        method = false;
        return ast::call::type::builtin;
    }

    if (resolver::find_method(name))
    {
        method = true;
        return ast::call::type::builtin;
    }

    for (const auto& entry : local_functions_)
    {
        if (entry == name)
            return ast::call::type::local;
    }

    for (const auto& inc : includes_)
    {
        for (const auto& fun : inc.funcs)
        {
            if (name == fun)
            {
                expr->path->value = inc.name;
                return ast::call::type::far;
            }
        }
    }

    throw comp_error(expr->loc(), "couldn't determine function reference type");
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
    return utils::string::va("loc_%d", label_idx_);
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
        function_->labels.insert({ index_, name });
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
           switch (static_cast<opcode>(inst->opcode))
           {
                case opcode::OP_JumpOnFalse:
                case opcode::OP_JumpOnTrue:
                case opcode::OP_JumpOnFalseExpr:
                case opcode::OP_JumpOnTrueExpr:
                case opcode::OP_jump:
                case opcode::OP_jumpback:
                case opcode::OP_switch:
                    if (inst->data[0] == name)
                        inst->data[0] = itr->second;
                    break;
                case opcode::OP_endswitch:
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

} // namespace xsk::gsc::s4
