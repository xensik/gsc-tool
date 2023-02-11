// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"
#include "compiler.hpp"
#include "context.hpp"

namespace xsk::gsc
{

compiler::compiler(context* ctx) : ctx_{ ctx }
{
}

auto compiler::compile(program const& data) -> assembly::ptr
{
    emit_program(data);
    return std::move(assembly_);
}

auto compiler::compile(std::string const& file, std::vector<u8>& data) -> assembly::ptr
{
    auto prog = ctx_->source().parse_program(file, data);
    return compile(*prog);
}

auto compiler::emit_program(program const& prog) -> void
{
    assembly_ = make_assembly();
    localfuncs_.clear();
    constants_.clear();
    developer_thread_ = false;
    animload_ = false;
    animname_ = {};
    index_ = 1;

    ctx_->init_includes();

    for (auto const& inc : prog.includes)
    {
        auto const& path = inc->path->value;

        if (!ctx_->load_include(path))
        {
            throw error(fmt::format("duplicated include file {}", path));
        }
    }

    for (auto const& dec : prog.declarations)
    {
        if (dec == node::decl_function)
        {
            auto const& name = dec.as_function->name->value;

            if (ctx_->func_exists(name) || ctx_->meth_exists(name))
            {
                throw comp_error(dec.loc(), fmt::format("function name '{}' already defined as builtin", name));
            }

            for (auto const& entry : localfuncs_)
            {
                if (entry == name)
                    throw comp_error(dec.loc(), fmt::format("function name '{}' already defined as local function", name));
            }

            localfuncs_.push_back(dec.as_function->name->value);
        }
    }

    for (auto const& dec : prog.declarations)
    {
        emit_decl(dec);
    }
}

auto compiler::emit_decl(decl const& dec) -> void
{
    switch (dec.kind())
    {
        case node::decl_dev_begin:
            developer_thread_ = true;
            break;
        case node::decl_dev_end:
            developer_thread_ = false;
            break;
        case node::decl_usingtree:
            emit_decl_usingtree(*dec.as_usingtree);
            break;
        case node::decl_constant:
            emit_decl_constant(*dec.as_constant);
            break;
        case node::decl_function:
            emit_decl_function(*dec.as_function);
            break;
        default:
            throw comp_error(dec.loc(), "unknown declaration");
    }
}

auto compiler::emit_decl_usingtree(decl_usingtree const& animtree) -> void
{
    if (developer_thread_)
        throw comp_error(animtree.loc(), "cannot put #using_animtree inside developer comment");

    animname_ = animtree.name->value;
    animload_ = false;
}

auto compiler::emit_decl_constant(decl_constant const& constant) -> void
{
    auto const it = constants_.find(constant.name->value);

    if (it != constants_.end())
        throw comp_error(constant.loc(), fmt::format("duplicated constant '{}'", constant.name->value));

    constants_.insert({ constant.name->value, &constant.value });
}

auto compiler::emit_decl_function(decl_function const& func) -> void
{
    label_idx_ = 0;
    can_break_ = false;
    can_continue_ = false;
    scopes_.clear();
    stackframe_.clear();
    break_blks_.clear();
    continue_blks_.clear();

    function_ = make_function();
    function_->index = index_;
    function_->name = func.name->value;
    function_->id = ctx_->token_id(function_->name);

    process_function(func);

    auto& scp = scopes_.at(func.body.get());

    emit_expr_parameters(*func.params, *scp);
    emit_stmt_comp(*func.body, *scp, true);
    emit_opcode(opcode::OP_End);

    function_->size = index_ - function_->index;
    assembly_->functions.push_back(std::move(function_));
}

auto compiler::emit_stmt(stmt const& stm, scope& scp, bool last) -> void
{
    switch (stm.kind())
    {
        case node::stmt_list:
            emit_stmt_list(*stm.as_list, scp, last);
            break;
        case node::stmt_comp:
            emit_stmt_comp(*stm.as_comp, scp, last);
            break;
        case node::stmt_dev:
            emit_stmt_dev(*stm.as_dev, scp, last);
            break;
        case node::stmt_expr:
            emit_stmt_expr(*stm.as_expr, scp);
            break;
        case node::stmt_call:
            emit_stmt_call(*stm.as_call, scp);
            break;
        case node::stmt_assign:
            emit_stmt_assign(*stm.as_assign, scp);
            break;
        case node::stmt_endon:
            emit_stmt_endon(*stm.as_endon, scp);
            break;
        case node::stmt_notify:
            emit_stmt_notify(*stm.as_notify, scp);
            break;
        case node::stmt_wait:
            emit_stmt_wait(*stm.as_wait, scp);
            break;
        case node::stmt_waittill:
            emit_stmt_waittill(*stm.as_waittill, scp);
            break;
        case node::stmt_waittillmatch:
            emit_stmt_waittillmatch(*stm.as_waittillmatch, scp);
            break;
        case node::stmt_waittillframeend:
            emit_stmt_waittillframeend(*stm.as_waittillframeend, scp);
            break;
        case node::stmt_waitframe:
            emit_stmt_waitframe(*stm.as_waitframe, scp);
            break;
        case node::stmt_if:
            emit_stmt_if(*stm.as_if, scp, last);
            break;
        case node::stmt_ifelse:
            emit_stmt_ifelse(*stm.as_ifelse, scp, last);
            break;
        case node::stmt_while:
            emit_stmt_while(*stm.as_while, scp);
            break;
        case node::stmt_dowhile:
            emit_stmt_dowhile(*stm.as_dowhile, scp);
            break;
        case node::stmt_for:
            emit_stmt_for(*stm.as_for, scp);
            break;
        case node::stmt_foreach:
            emit_stmt_foreach(*stm.as_foreach, scp);
            break;
        case node::stmt_switch:
            emit_stmt_switch(*stm.as_switch, scp);
            break;
        case node::stmt_case:
            emit_stmt_case(*stm.as_case, scp);
            break;
        case node::stmt_default:
            emit_stmt_default(*stm.as_default, scp);
            break;
        case node::stmt_break:
            emit_stmt_break(*stm.as_break, scp);
            break;
        case node::stmt_continue:
            emit_stmt_continue(*stm.as_continue, scp);
            break;
        case node::stmt_return:
            emit_stmt_return(*stm.as_return, scp);
            break;
        case node::stmt_breakpoint:
            emit_stmt_breakpoint(*stm.as_breakpoint, scp);
            break;
        case node::stmt_prof_begin:
            emit_stmt_prof_begin(*stm.as_prof_begin, scp);
            break;
        case node::stmt_prof_end:
            emit_stmt_prof_end(*stm.as_prof_end, scp);
            break;
        case node::stmt_assert:
            emit_stmt_assert(*stm.as_assert, scp);
            break;
        case node::stmt_assertex:
            emit_stmt_assertex(*stm.as_assertex, scp);
            break;
        case node::stmt_assertmsg:
            emit_stmt_assertmsg(*stm.as_assertmsg, scp);
            break;
        default:
            throw comp_error(stm.loc(), "unknown statement");
    }
}

auto compiler::emit_stmt_list(stmt_list const& stm, scope& scp, bool last) -> void
{
    for (auto const& entry : stm.list)
    {
        emit_stmt(entry, scp, (&entry == &stm.list.back() && last) ? true : false);
    }
}

auto compiler::emit_stmt_comp(stmt_comp const& stm, scope& scp, bool last) -> void
{
    emit_stmt_list(*stm.block, scp, last);
}

auto compiler::emit_stmt_dev(stmt_dev const& stm, scope& scp, bool last) -> void
{
    emit_stmt_list(*stm.block, scp, last);
}

auto compiler::emit_stmt_expr(stmt_expr const& stm, scope& scp) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_increment:
            emit_expr_increment(*stm.value.as_increment, scp, true);
            break;
        case node::expr_decrement:
            emit_expr_decrement(*stm.value.as_decrement, scp, true);
            break;
        case node::expr_assign_equal:
        case node::expr_assign_add:
        case node::expr_assign_sub:
        case node::expr_assign_mul:
        case node::expr_assign_div:
        case node::expr_assign_mod:
        case node::expr_assign_shift_left:
        case node::expr_assign_shift_right:
        case node::expr_assign_bitwise_or:
        case node::expr_assign_bitwise_and:
        case node::expr_assign_bitwise_exor:
            emit_expr_assign(*stm.value.as_assign, scp);
            break;
        case node::null:
            break;
        default:
            throw comp_error(stm.loc(), "unknown expr statement expression");
    }
}

auto compiler::emit_stmt_call(stmt_call const& stm, scope& scp) -> void
{
    if (stm.value == node::expr_call)
        emit_expr_call(*stm.value.as_call, scp, true);
    else if (stm.value == node::expr_method)
        emit_expr_method(*stm.value.as_method, scp, true);
    else
        throw comp_error(stm.loc(), "unknown call statement expression");
}

auto compiler::emit_stmt_assign(stmt_assign const& stm, scope& scp) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_increment:
            emit_expr_increment(*stm.value.as_increment, scp, true);
            break;
        case node::expr_decrement:
            emit_expr_decrement(*stm.value.as_decrement, scp, true);
            break;
        case node::expr_assign_equal:
        case node::expr_assign_add:
        case node::expr_assign_sub:
        case node::expr_assign_mul:
        case node::expr_assign_div:
        case node::expr_assign_mod:
        case node::expr_assign_shift_left:
        case node::expr_assign_shift_right:
        case node::expr_assign_bitwise_or:
        case node::expr_assign_bitwise_and:
        case node::expr_assign_bitwise_exor:
            emit_expr_assign(*stm.value.as_assign, scp);
            break;
        default:
            throw comp_error(stm.loc(), "unknown assign statement expression");
    }
}

auto compiler::emit_stmt_endon(stmt_endon const& stm, scope& scp) -> void
{
    emit_expr(stm.event, scp);
    emit_expr(stm.obj, scp);
    emit_opcode(opcode::OP_endon);
}

auto compiler::emit_stmt_notify(stmt_notify const& stm, scope& scp) -> void
{
    emit_opcode(opcode::OP_voidCodepos);

    // std::reverse(stm.args->list.begin(), stm.args->list.end());

    // for (auto const& arg : stm.args->list) // use reverse range later!!
    // {
    //     emit_expr(arg, scp);
    // }

    for (auto it = stm.args->list.rbegin(); it != stm.args->list.rend(); ++it)
    {
        emit_expr(*it, scp);
    }

    emit_expr(stm.event, scp);
    emit_expr(stm.obj, scp);
    emit_opcode(opcode::OP_notify);
}

auto compiler::emit_stmt_wait(stmt_wait const& stm, scope& scp) -> void
{
    emit_expr(stm.time, scp);
    emit_opcode(opcode::OP_wait);
}

auto compiler::emit_stmt_waittill(stmt_waittill const& stm, scope& scp) -> void
{
    emit_expr(stm.event, scp);
    emit_expr(stm.obj, scp);
    emit_opcode(opcode::OP_waittill);

    for (auto const& entry : stm.args->list)
    {
        emit_opcode(opcode::OP_SafeSetWaittillVariableFieldCached, fmt::format("{}", variable_create(*entry.as_identifier, scp)));
    }

    emit_opcode(opcode::OP_clearparams);
}

auto compiler::emit_stmt_waittillmatch(stmt_waittillmatch const& stm, scope& scp) -> void
{
    emit_expr_arguments(*stm.args, scp);
    emit_expr(stm.event, scp);
    emit_expr(stm.obj, scp);
    emit_opcode(opcode::OP_waittillmatch, fmt::format("{}", stm.args->list.size()));
    emit_opcode(opcode::OP_waittillmatch2);
    emit_opcode(opcode::OP_clearparams);
}

auto compiler::emit_stmt_waittillframeend(stmt_waittillframeend const&, scope&) -> void
{
    emit_opcode(opcode::OP_waittillFrameEnd);
}

auto compiler::emit_stmt_waitframe(stmt_waitframe const&, scope&) -> void
{
    emit_opcode(opcode::OP_waitframe);
}

auto compiler::emit_stmt_if(stmt_if const& stm, scope& scp, bool last) -> void
{
    auto end_loc = create_label();

    if (stm.test == node::expr_not)
    {
        emit_expr(stm.test.as_not->rvalue, scp);
        emit_opcode(opcode::OP_JumpOnTrue, end_loc);
    }
    else
    {
        emit_expr(stm.test, scp);
        emit_opcode(opcode::OP_JumpOnFalse, end_loc);
    }

    auto& scp_body = scopes_.at(stm.body.as_node.get());

    scp.transfer(scp_body);

    emit_stmt(stm.body, *scp_body, last);

    last ? emit_opcode(opcode::OP_End) : emit_remove_local_vars(*scp_body);

    insert_label(end_loc);
}

auto compiler::emit_stmt_ifelse(stmt_ifelse const& stm, scope& scp, bool last) -> void
{
    auto childs = std::vector<scope*>{};
    auto else_loc = create_label();
    auto end_loc = create_label();

    if (stm.test == node::expr_not)
    {
        emit_expr(stm.test.as_not->rvalue, scp);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(stm.test, scp);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    auto& scp_then = scopes_.at(stm.stmt_if.as_node.get());

    scp.transfer(scp_then);

    emit_stmt(stm.stmt_if, *scp_then, last);

    emit_remove_local_vars(*scp_then);

    if (scp_then->abort == scope::abort_none)
        childs.push_back(scp_then.get());

    last ? emit_opcode(opcode::OP_End) : emit_opcode(opcode::OP_jump, end_loc);

    insert_label(else_loc);

    auto& scp_else = scopes_.at(stm.stmt_else.as_node.get());

    scp.transfer(scp_else);

    emit_stmt(stm.stmt_else, *scp_else, last);

    last ? emit_opcode(opcode::OP_End) : emit_remove_local_vars(*scp_else);

    if (scp_else->abort == scope::abort_none)
        childs.push_back(scp_else.get());

    insert_label(end_loc);

    scp.init(childs);
}

auto compiler::emit_stmt_while(stmt_while const& stm, scope& scp) -> void
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

    auto& scp_body = scopes_.at(stm.body.as_node.get());

    scp.transfer(scp_body);
    scp_body->loc_break = break_loc;
    scp_body->loc_cont = continue_loc;

    emit_create_local_vars(*scp_body);

    scp.init(scp_body);

    auto begin_loc = insert_label();

    bool const_cond = is_constant_condition(stm.test);

    if (!const_cond)
    {
        if (stm.test == node::expr_not)
        {
            emit_expr(stm.test.as_not->rvalue, scp);
            emit_opcode(opcode::OP_JumpOnTrue, break_loc);
        }
        else
        {
            emit_expr(stm.test, scp);
            emit_opcode(opcode::OP_JumpOnFalse, break_loc);
        }
    }

    emit_stmt(stm.body, *scp_body, false);

    insert_label(continue_loc);
    emit_opcode(opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);

    if (const_cond)
        scp.init(break_blks_);

    can_break_ = old_break;
    can_continue_ = old_continue;
    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

auto compiler::emit_stmt_dowhile(stmt_dowhile const& stm, scope& scp) -> void
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

    auto& scp_body = scopes_.at(stm.body.as_node.get());

    scp.transfer(scp_body);
    scp_body->loc_break = break_loc;
    scp_body->loc_cont = continue_loc;

    emit_create_local_vars(*scp_body);

    scp.init(scp_body);

    auto begin_loc = insert_label();

    emit_stmt(stm.body, *scp_body, false);

    insert_label(continue_loc);

    bool const_cond = is_constant_condition(stm.test);

    if (!const_cond)
    {
        if (stm.test == node::expr_not)
        {
            emit_expr(stm.test.as_not->rvalue, scp);
            emit_opcode(opcode::OP_JumpOnTrue, break_loc);
        }
        else
        {
            emit_expr(stm.test, scp);
            emit_opcode(opcode::OP_JumpOnFalse, break_loc);
        }
    }

    emit_opcode(opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);

    if (const_cond)
        scp.init(break_blks_);

    can_break_ = old_break;
    can_continue_ = old_continue;
    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

auto compiler::emit_stmt_for(stmt_for const& stm, scope& scp) -> void
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

    emit_stmt(stm.init, scp, false);

    auto& scp_body = scopes_.at(stm.body.as_node.get());

    scp.transfer(scp_body);
    scp_body->loc_break = break_loc;
    scp_body->loc_cont = continue_loc;

    emit_create_local_vars(*scp_body);

    scp.init(scp_body);

    auto& scp_iter = scopes_.at(stm.iter.as_node.get());

    scp.transfer(scp_iter);

    auto begin_loc = insert_label();

    bool const_cond = is_constant_condition(stm.test);

    if (!const_cond)
    {
        if (stm.test == node::expr_not)
        {
            emit_expr(stm.test.as_not->rvalue, scp);
            emit_opcode(opcode::OP_JumpOnTrue, break_loc);
        }
        else
        {
            emit_expr(stm.test, scp);
            emit_opcode(opcode::OP_JumpOnFalse, break_loc);
        }
    }

    can_break_ = true;
    can_continue_ = true;

    emit_stmt(stm.body, *scp_body, false);

    if (scp_body->abort == scope::abort_none)
        continue_blks_.push_back(scp_body.get());

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);

    scp_iter->init(continue_blks_);

    emit_stmt(stm.iter, *scp_iter, false);
    emit_opcode(opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);

    if (const_cond)
        scp.init(break_blks_);

    can_break_ = old_break;
    can_continue_ = old_continue;
    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

auto compiler::emit_stmt_foreach(stmt_foreach const& stm, scope& scp) -> void
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

    emit_expr(stm.container, scp);
    emit_expr_variable_ref(stm.array, scp, true);
    emit_expr_variable(stm.array, scp);

    if (ctx_->props() & props::farcall)
        emit_opcode(opcode::OP_CallBuiltin, { "getfirstarraykey"s, "1"s });
    else
        emit_opcode(opcode::OP_CallBuiltin1, "getfirstarraykey");
    
    emit_expr_variable_ref(stm.key, scp, true);

    if (ctx_->props() & props::foreach && stm.use_key)
    {
        emit_opcode(opcode::OP_GetUndefined);
        emit_expr_variable_ref(stm.index, scp, true);
    }

    auto& scp_body = scopes_.at(stm.body.as_node.get());
    auto& scp_iter = scopes_.at(stm.key.as_node.get());

    scp.transfer(scp_body);
    scp_body->loc_break = break_loc;
    scp_body->loc_cont = continue_loc;

    emit_create_local_vars(*scp_body);

    scp.init(scp_body);

    scp.transfer(scp_iter);

    auto begin_loc = insert_label();

    emit_expr_variable(stm.key, scp);

    if (ctx_->props() & props::boolfuncs)
        emit_opcode(opcode::OP_IsDefined);
    else
        emit_opcode(opcode::OP_CallBuiltin1, "isdefined");

    emit_opcode(opcode::OP_JumpOnFalse, break_loc);

    can_break_ = true;
    can_continue_ = true;

    emit_expr_variable(stm.key, *scp_body);
    emit_opcode(opcode::OP_EvalLocalArrayCached, fmt::format("{}", variable_access(*stm.array.as_identifier, *scp_body)));
    emit_expr_variable_ref(stm.value, *scp_body, true);

    if (ctx_->props() & props::foreach && stm.use_key)
    {
        emit_expr_variable(stm.key, *scp_body);
        emit_expr_variable_ref(stm.index, *scp_body, true);
    }

    emit_stmt(stm.body, *scp_body, false);

    if (scp_body->abort == scope::abort_none)
        continue_blks_.push_back(scp_body.get());

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);

    scp_iter->init(continue_blks_);

    emit_expr_variable(stm.key, *scp_iter);
    emit_expr_variable(stm.array, *scp_iter);

    if (ctx_->props() & props::farcall)
        emit_opcode(opcode::OP_CallBuiltin, { "getnextarraykey"s, "2"s });
    else
        emit_opcode(opcode::OP_CallBuiltin2, "getnextarraykey");

    emit_expr_variable_ref(stm.key, *scp_iter, true);
    emit_opcode(opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);
    emit_expr_clear_local(*stm.array.as_identifier, scp);
    if (ctx_->props() & props::foreach || !stm.use_key) emit_expr_clear_local(*stm.key.as_identifier, scp);

    can_break_ = old_break;
    can_continue_ = old_continue;
    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

auto compiler::emit_stmt_switch(stmt_switch const& stm, scope& scp) -> void
{
    auto old_breaks = break_blks_;
    auto old_break = can_break_;
    break_blks_.clear();
    can_break_ = false;

    auto table_loc = create_label();
    auto break_loc = create_label();

    emit_expr(stm.test, scp);
    emit_opcode(opcode::OP_switch, table_loc);

    can_break_ = true;

    auto data = std::vector<std::string>{};
    data.push_back(fmt::format("{}", stm.body->block->list.size()));

    auto type = switch_type::none;
    auto loc_default = std::string{};
    auto has_default = false;
    scope* default_ctx = nullptr;

    for (auto i = 0u; i < stm.body->block->list.size(); i++)
    {
        auto const& entry = stm.body->block->list[i];

        if (entry == node::stmt_case)
        {
            data.push_back("case");

            if (entry.as_case->value == node::expr_integer)
            {
                if (ctx_->engine() == engine::iw9)
                {
                    data.push_back(fmt::format("{}", static_cast<std::underlying_type_t<switch_type>>(switch_type::integer)));
                }
                else
                {
                    if (type == switch_type::string)
                    {
                        throw comp_error(entry.loc(), "switch cases with different types");
                    }

                    type = switch_type::integer;
                }
                
                data.push_back(entry.as_case->value.as_integer->value);
                data.push_back(insert_label());
            }
            else if (entry.as_case->value == node::expr_string)
            {
                if (ctx_->engine() == engine::iw9)
                {
                    data.push_back(fmt::format("{}", static_cast<std::underlying_type_t<switch_type>>(switch_type::string)));
                }
                else
                {
                    if (type == switch_type::integer)
                    {
                        throw comp_error(entry.loc(), "switch cases with different types");
                    }

                    type = switch_type::string;
                }

                data.push_back(entry.as_case->value.as_string->value);
                data.push_back(insert_label());
            }
            else
            {
                throw comp_error(entry.loc(), "case type must be int or string");
            }

            auto& scp_body = scopes_.at(entry.as_case->body.get());

            scp.transfer(scp_body);
            scp_body->loc_break = break_loc;
            emit_stmt_list(*entry.as_case->body, *scp_body, false);

            if (entry.as_case->body->list.size() > 0)
                emit_remove_local_vars(*scp_body);
        }
        else if (entry == node::stmt_default)
        {
            loc_default = insert_label();
            has_default = true;

            auto& scp_body = scopes_.at(entry.as_default->body.get());

            default_ctx = scp_body.get();

            scp.transfer(scp_body);
            scp_body->loc_break = break_loc;
            emit_stmt_list(*entry.as_default->body, *scp_body, false);

            if (entry.as_default->body->list.size() > 0)
                emit_remove_local_vars(*scp_body);
        }
        else
        {
            throw comp_error(entry.loc(), "missing case statement");
        }
    }

    if (has_default)
    {
        data.push_back("default");
        data.push_back(loc_default);

        if (default_ctx->abort == scope::abort_none)
            break_blks_.push_back(default_ctx);

        scp.init(break_blks_);
    }

    data.push_back(fmt::format("{}", static_cast<std::underlying_type_t<switch_type>>(type)));

    insert_label(table_loc);

    emit_opcode(opcode::OP_endswitch, data);

    auto offset = static_cast<u32>(((ctx_->engine() == engine::iw9) ? 8 : 7) * stm.body->block->list.size());
    function_->instructions.back()->size += offset;
    index_ += offset;

    insert_label(break_loc);

    can_break_ = old_break;
    break_blks_ = old_breaks;
}

auto compiler::emit_stmt_case(stmt_case const& stm, scope&) -> void
{
    throw comp_error(stm.loc(), "illegal case statement");
}

auto compiler::emit_stmt_default(stmt_default const& stm, scope&) -> void
{
    throw comp_error(stm.loc(), "illegal default statement");
}

auto compiler::emit_stmt_break(stmt_break const& stm, scope& scp) -> void
{
    if (!can_break_ || scp.abort != scope::abort_none || scp.loc_break == "")
        throw comp_error(stm.loc(), "illegal break statement");

    break_blks_.push_back(&scp);
    emit_remove_local_vars(scp);
    scp.abort = scope::abort_break;
    emit_opcode(opcode::OP_jump, scp.loc_break);
}

auto compiler::emit_stmt_continue(stmt_continue const& stm, scope& scp) -> void
{
    if (!can_continue_ || scp.abort != scope::abort_none || scp.loc_cont == "")
        throw comp_error(stm.loc(), "illegal continue statement");

    continue_blks_.push_back(&scp);
    emit_remove_local_vars(scp);
    scp.abort = scope::abort_continue;
    emit_opcode(opcode::OP_jump, scp.loc_cont);
}

auto compiler::emit_stmt_return(stmt_return const& stm, scope& scp) -> void
{
    if (scp.abort == scope::abort_none)
        scp.abort = scope::abort_return;

    if (stm.value != node::null)
    {
        emit_expr(stm.value, scp);
        emit_opcode(opcode::OP_Return);
    }
    else
        emit_opcode(opcode::OP_End);
}

auto compiler::emit_stmt_breakpoint(stmt_breakpoint const&, scope&) -> void
{
    // TODO:
}

auto compiler::emit_stmt_prof_begin(stmt_prof_begin const&, scope&) -> void
{
    // TODO:
}

auto compiler::emit_stmt_prof_end(stmt_prof_end const&, scope&) -> void
{
    // TODO:
}

auto compiler::emit_stmt_assert(stmt_assert const&, scope&) -> void
{
    // TODO:
}

auto compiler::emit_stmt_assertex(stmt_assertex const&, scope&) -> void
{
    // TODO:
}

auto compiler::emit_stmt_assertmsg(stmt_assertmsg const&, scope&) -> void
{
    // TODO:
}

auto compiler::emit_expr(expr const& exp, scope& scp) -> void
{
    switch (exp.kind())
    {
        case node::expr_paren:
            emit_expr(exp.as_paren->value, scp);
            break;
        case node::expr_ternary:
            emit_expr_ternary(*exp.as_ternary, scp);
            break;
        case node::expr_and:
            emit_expr_and(*exp.as_and, scp);
            break;
        case node::expr_or:
            emit_expr_or(*exp.as_or, scp);
            break;
        case node::expr_equality:
        case node::expr_inequality:
        case node::expr_less:
        case node::expr_greater:
        case node::expr_less_equal:
        case node::expr_greater_equal:
        case node::expr_bitwise_or:
        case node::expr_bitwise_and:
        case node::expr_bitwise_exor:
        case node::expr_shift_left:
        case node::expr_shift_right:
        case node::expr_add:
        case node::expr_sub:
        case node::expr_mul:
        case node::expr_div:
        case node::expr_mod:
            emit_expr_binary(*exp.as_binary, scp);
            break;
        case node::expr_complement:
            emit_expr_complement(*exp.as_complement, scp);
            break;
        case node::expr_negate:
            emit_expr_negate(*exp.as_negate, scp);
            break;
        case node::expr_not:
            emit_expr_not(*exp.as_not, scp);
            break;
        case node::expr_call:
            emit_expr_call(*exp.as_call, scp, false);
            break;
        case node::expr_method:
            emit_expr_method(*exp.as_method, scp, false);
            break;
        case node::expr_isdefined:
            emit_expr_isdefined(*exp.as_isdefined, scp);
            break;
        case node::expr_istrue:
            emit_expr_istrue(*exp.as_istrue, scp);
            break;
        case node::expr_reference:
            emit_expr_reference(*exp.as_reference, scp);
            break;
        case node::expr_add_array:
            emit_expr_add_array(*exp.as_add_array, scp);
            break;
        case node::expr_array:
            emit_expr_array(*exp.as_array, scp);
            break;
        case node::expr_field:
            emit_expr_field(*exp.as_field, scp);
            break;
        case node::expr_size:
            emit_expr_size(*exp.as_size, scp);
            break;
        case node::expr_thisthread:
            emit_opcode(opcode::OP_GetThisthread);
            break;
        case node::expr_empty_array:
            emit_opcode(opcode::OP_EmptyArray);
            break;
        case node::expr_undefined:
            emit_opcode(opcode::OP_GetUndefined);
            break;
        case node::expr_game:
            emit_opcode(opcode::OP_GetGame);
            break;
        case node::expr_self:
            emit_opcode(opcode::OP_GetSelf);
            break;
        case node::expr_anim:
            emit_opcode(opcode::OP_GetAnim);
            break;
        case node::expr_level:
            emit_opcode(opcode::OP_GetLevel);
            break;
        case node::expr_animation:
            emit_expr_animation(*exp.as_animation);
            break;
        case node::expr_animtree:
            emit_expr_animtree(*exp.as_animtree);
            break;
        case node::expr_identifier:
            emit_expr_local(*exp.as_identifier, scp);
            break;
        case node::expr_istring:
            emit_expr_istring(*exp.as_istring);
            break;
        case node::expr_string:
            emit_expr_string(*exp.as_string);
            break;
        case node::expr_vector:
            emit_expr_vector(*exp.as_vector, scp);
            break;
        case node::expr_float:
            emit_expr_float(*exp.as_float);
            break;
        case node::expr_integer:
            emit_expr_integer(*exp.as_integer);
            break;
        case node::expr_false:
            emit_expr_false(*exp.as_false);
            break;
        case node::expr_true:
            emit_expr_true(*exp.as_true);
            break;
        case node::null:
            break;
        default:
            throw comp_error(exp.loc(), "unknown expression");
    }
}

auto compiler::emit_expr_assign(expr_assign const& exp, scope& scp) -> void
{
    if (exp.kind() == node::expr_assign_equal)
    {
        if (exp.rvalue == node::expr_undefined)
        {
            emit_expr_clear(exp.lvalue, scp);
        }
        else if (exp.lvalue == node::expr_tuple)
        {
            emit_expr(exp.rvalue, scp);
            emit_expr_tuple(*exp.lvalue.as_tuple, scp);
        }
        else
        {
            emit_expr(exp.rvalue, scp);
            emit_expr_variable_ref(exp.lvalue, scp, true);
        }

        return;
    }

    emit_expr(exp.lvalue, scp);
    emit_expr(exp.rvalue, scp);

    switch (exp.kind())
    {
        case node::expr_assign_add:
            emit_opcode(opcode::OP_plus);
            break;
        case node::expr_assign_sub:
            emit_opcode(opcode::OP_minus);
            break;
        case node::expr_assign_mul:
            emit_opcode(opcode::OP_multiply);
            break;
        case node::expr_assign_div:
            emit_opcode(opcode::OP_divide);
            break;
        case node::expr_assign_mod:
            emit_opcode(opcode::OP_mod);
            break;
        case node::expr_assign_shift_left:
            emit_opcode(opcode::OP_shift_left);
            break;
        case node::expr_assign_shift_right:
            emit_opcode(opcode::OP_shift_right);
            break;
        case node::expr_assign_bitwise_or:
            emit_opcode(opcode::OP_bit_or);
            break;
        case node::expr_assign_bitwise_and:
            emit_opcode(opcode::OP_bit_and);
            break;
        case node::expr_assign_bitwise_exor:
            emit_opcode(opcode::OP_bit_ex_or);
            break;
        default:
            throw comp_error(exp.loc(), "unknown assign operation");
    }

    emit_expr_variable_ref(exp.lvalue, scp, true);
}

auto compiler::emit_expr_clear(expr const& exp, scope& scp) -> void
{
    switch (exp.kind())
    {
        case node::expr_array:
            emit_expr(exp.as_array->key, scp);
            exp.as_array->obj == node::expr_game ? emit_opcode(opcode::OP_GetGameRef) : emit_expr_variable_ref(exp.as_array->obj, scp, false);
            emit_opcode(opcode::OP_ClearArray);
            break;
        case node::expr_field:
            emit_expr_object(exp.as_field->obj, scp);
            emit_opcode(opcode::OP_ClearFieldVariable, exp.as_field->field->value);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_GetUndefined);
            emit_expr_local_ref(*exp.as_identifier, scp, true);
            break;
        default:
            throw comp_error(exp.loc(), "unknown clear variable lvalue");
    }
}

auto compiler::emit_expr_clear_local(expr_identifier const& exp, scope& scp) -> void
{
    auto index = variable_access(exp, scp);

    if (index == 0)
        emit_opcode(opcode::OP_ClearLocalVariableFieldCached0);
    else
        emit_opcode(opcode::OP_ClearLocalVariableFieldCached, fmt::format("{}", index));
}

auto compiler::emit_expr_increment(expr_increment const& exp, scope& scp, bool is_stmt) -> void
{
    if (is_stmt)
    {
        emit_expr_variable_ref(exp.lvalue, scp, false);
        emit_opcode(opcode::OP_inc);
        emit_opcode(opcode::OP_SetVariableField);
    }
    else
    {
        // TODO:
    }
}

auto compiler::emit_expr_decrement(expr_decrement const& exp, scope& scp, bool is_stmt) -> void
{
    if (is_stmt)
    {
        emit_expr_variable_ref(exp.lvalue, scp, false);
        emit_opcode(opcode::OP_dec);
        emit_opcode(opcode::OP_SetVariableField);
    }
    else
    {
        // TODO:
    }
}

auto compiler::emit_expr_ternary(expr_ternary const& exp, scope& scp) -> void
{
    auto else_loc = create_label();
    auto end_loc = create_label();

    if (exp.test == node::expr_not)
    {
        emit_expr(exp.test.as_not->rvalue, scp);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(exp.test, scp);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    emit_expr(exp.true_expr, scp);
    emit_opcode(opcode::OP_jump, end_loc);

    insert_label(else_loc);
    emit_expr(exp.false_expr, scp);
    insert_label(end_loc);
}

auto compiler::emit_expr_binary(expr_binary const& exp, scope& scp) -> void
{
    emit_expr(exp.lvalue, scp);
    emit_expr(exp.rvalue, scp);

    switch (exp.kind())
    {
        case node::expr_equality:
            emit_opcode(opcode::OP_equality);
            break;
        case node::expr_inequality:
            emit_opcode(opcode::OP_inequality);
            break;
        case node::expr_less:
            emit_opcode(opcode::OP_less);
            break;
        case node::expr_greater:
            emit_opcode(opcode::OP_greater);
            break;
        case node::expr_less_equal:
            emit_opcode(opcode::OP_less_equal);
            break;
        case node::expr_greater_equal:
            emit_opcode(opcode::OP_greater_equal);
            break;
        case node::expr_bitwise_or:
            emit_opcode(opcode::OP_bit_or);
            break;
        case node::expr_bitwise_and:
            emit_opcode(opcode::OP_bit_and);
            break;
        case node::expr_bitwise_exor:
            emit_opcode(opcode::OP_bit_ex_or);
            break;
        case node::expr_shift_left:
            emit_opcode(opcode::OP_shift_left);
            break;
        case node::expr_shift_right:
            emit_opcode(opcode::OP_shift_right);
            break;
        case node::expr_add:
            emit_opcode(opcode::OP_plus);
            break;
        case node::expr_sub:
            emit_opcode(opcode::OP_minus);
            break;
        case node::expr_mul:
            emit_opcode(opcode::OP_multiply);
            break;
        case node::expr_div:
            emit_opcode(opcode::OP_divide);
            break;
        case node::expr_mod:
            emit_opcode(opcode::OP_mod);
            break;
        default:
            throw comp_error(exp.loc(), "unknown binary expression");
    }
}

auto compiler::emit_expr_and(expr_and const& exp, scope& scp) -> void
{
    auto label = create_label();

    emit_expr(exp.lvalue, scp);
    emit_opcode(opcode::OP_JumpOnFalseExpr, label);

    if (exp.rvalue == node::expr_not && (ctx_->props() & props::boolnotand))
    {
        emit_expr(exp.rvalue.as_not->rvalue, scp);
        emit_opcode(opcode::OP_BoolNotAfterAnd);
    }
    else
    {
        emit_expr(exp.rvalue, scp);
        emit_opcode(opcode::OP_CastBool);
    }

    insert_label(label);
}

auto compiler::emit_expr_or(expr_or const& exp, scope& scp) -> void
{
    auto label = create_label();

    emit_expr(exp.lvalue, scp);
    emit_opcode(opcode::OP_JumpOnTrueExpr, label);

    if (exp.rvalue == node::expr_not && (ctx_->props() & props::boolnotand))
    {
        emit_expr(exp.rvalue.as_not->rvalue, scp);
        emit_opcode(opcode::OP_BoolNotAfterAnd);
    }
    else
    {
        emit_expr(exp.rvalue, scp);
        emit_opcode(opcode::OP_CastBool);
    }

    insert_label(label);
}

auto compiler::emit_expr_complement(expr_complement const& exp, scope& scp) -> void
{
    emit_expr(exp.rvalue, scp);
    emit_opcode(opcode::OP_BoolComplement);
}

auto compiler::emit_expr_negate(expr_negate const& exp, scope& scp) -> void
{
    emit_opcode(opcode::OP_GetZero);
    emit_expr(exp.rvalue, scp);
    emit_opcode(opcode::OP_minus);
}

auto compiler::emit_expr_not(expr_not const& exp, scope& scp) -> void
{
    emit_expr(exp.rvalue, scp);
    emit_opcode(opcode::OP_BoolNot);
}

auto compiler::emit_expr_call(expr_call const& exp, scope& scp, bool is_stmt) -> void
{
    if (exp.value == node::expr_pointer)
        emit_expr_call_pointer(*exp.value.as_pointer, scp, is_stmt);
    else if (exp.value == node::expr_function)
        emit_expr_call_function(*exp.value.as_function, scp, is_stmt);
    else
        throw comp_error(exp.loc(), "unknown function call expression");
}

auto compiler::emit_expr_call_pointer(expr_pointer const& exp, scope& scp, bool is_stmt) -> void
{
    if (exp.mode == call::mode::normal)
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(*exp.args, scp);
    emit_expr(exp.func, scp);

    auto argcount = fmt::format("{}", exp.args->list.size());

    switch (exp.mode)
    {
        case call::mode::normal:
            emit_opcode(opcode::OP_ScriptFunctionCallPointer);
            break;
        case call::mode::thread:
            emit_opcode(opcode::OP_ScriptThreadCallPointer, argcount);
            break;
        case call::mode::childthread:
            emit_opcode(opcode::OP_ScriptChildThreadCallPointer, argcount);
            break;
        case call::mode::builtin:
            emit_opcode(opcode::OP_CallBuiltinPointer, argcount);
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

auto compiler::emit_expr_call_function(expr_function const& exp, scope& scp, bool is_stmt) -> void
{
    auto path = std::string{};
    auto type = resolve_function_type(exp, path);

    if (ctx_->props() & props::farcall && type == call::type::local)
    {
        type = call::type::far;
    }

    if (type != call::type::builtin && exp.mode == call::mode::normal && (ctx_->props() & props::farcall || exp.args->list.size() > 0))
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(*exp.args, scp);

    auto argcount = fmt::format("{}", exp.args->list.size());

    if (type == call::type::local)
    {
        switch (exp.mode)
        {
            case call::mode::normal:
                if (exp.args->list.size() > 0)
                    emit_opcode(opcode::OP_ScriptLocalFunctionCall, exp.name->value);
                else
                    emit_opcode(opcode::OP_ScriptLocalFunctionCall2, exp.name->value);
                break;
            case call::mode::thread:
                emit_opcode(opcode::OP_ScriptLocalThreadCall, { exp.name->value, argcount });
                break;
            case call::mode::childthread:
                emit_opcode(opcode::OP_ScriptLocalChildThreadCall, { exp.name->value, argcount });
                break;
            case call::mode::builtin:
                // no local builtins
                break;
        }
    }
    else if (type == call::type::far)
    {
        switch (exp.mode)
        {
            case call::mode::normal:
                if (!(ctx_->props() & props::farcall) && exp.args->list.size() == 0)
                    emit_opcode(opcode::OP_ScriptFarFunctionCall2, { path, exp.name->value });
                else
                    emit_opcode(opcode::OP_ScriptFarFunctionCall, { path, exp.name->value });
                break;
            case call::mode::thread:
                emit_opcode(opcode::OP_ScriptFarThreadCall, { path, exp.name->value, argcount });
                break;
            case call::mode::childthread:
                emit_opcode(opcode::OP_ScriptFarChildThreadCall, { path, exp.name->value, argcount });
                break;
            case call::mode::builtin:
                // no far builtins
                break;
        }
    }
    else if (type == call::type::builtin)
    {
        if (exp.mode != call::mode::normal)
            throw comp_error(exp.loc(), "builtin calls can't be threaded");

        if (ctx_->props() & props::farcall)
        {
            emit_opcode(opcode::OP_CallBuiltin, { exp.name->value, argcount });
        }
        else
        {
            switch (exp.args->list.size())
            {
                case 0:
                    emit_opcode(opcode::OP_CallBuiltin0, exp.name->value);
                    break;
                case 1:
                    emit_opcode(opcode::OP_CallBuiltin1, exp.name->value);
                    break;
                case 2:
                    emit_opcode(opcode::OP_CallBuiltin2, exp.name->value);
                    break;
                case 3:
                    emit_opcode(opcode::OP_CallBuiltin3, exp.name->value);
                    break;
                case 4:
                    emit_opcode(opcode::OP_CallBuiltin4, exp.name->value);
                    break;
                case 5:
                    emit_opcode(opcode::OP_CallBuiltin5, exp.name->value);
                    break;
                default:
                    emit_opcode(opcode::OP_CallBuiltin, { exp.name->value, argcount });
                    break;
            }        
        }
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

auto compiler::emit_expr_method(expr_method const& exp, scope& scp, bool is_stmt) -> void
{
    if (exp.value == node::expr_pointer)
        emit_expr_method_pointer(*exp.value.as_pointer, exp.obj, scp, is_stmt);
    else if (exp.value == node::expr_function)
        emit_expr_method_function(*exp.value.as_function, exp.obj, scp, is_stmt);
    else
        throw comp_error(exp.loc(), "unknown method call expression");
}

auto compiler::emit_expr_method_pointer(expr_pointer const& exp, expr const& obj, scope& scp, bool is_stmt) -> void
{
    if (exp.mode == call::mode::normal)
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(*exp.args, scp);
    emit_expr(obj, scp);
    emit_expr(exp.func, scp);

    auto argcount = fmt::format("{}", exp.args->list.size());

    switch (exp.mode)
    {
        case call::mode::normal:
            emit_opcode(opcode::OP_ScriptMethodCallPointer);
            break;
        case call::mode::thread:
            emit_opcode(opcode::OP_ScriptMethodThreadCallPointer, argcount);
            break;
        case call::mode::childthread:
            emit_opcode(opcode::OP_ScriptMethodChildThreadCallPointer, argcount);
            break;
        case call::mode::builtin:
            emit_opcode(opcode::OP_CallBuiltinMethodPointer, argcount);
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

auto compiler::emit_expr_method_function(expr_function const& exp, expr const& obj, scope& scp, bool is_stmt) -> void
{
    auto path = std::string{};
    auto type = resolve_function_type(exp, path);

    if (ctx_->props() & props::farcall && type == call::type::local)
    {
        type = call::type::far;
    }

    if (type != call::type::builtin && exp.mode == call::mode::normal)
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(*exp.args, scp);
    emit_expr(obj, scp);

    auto argcount = fmt::format("{}", exp.args->list.size());

    if (type == call::type::local)
    {
        switch (exp.mode)
        {
            case call::mode::normal:
                emit_opcode(opcode::OP_ScriptLocalMethodCall, exp.name->value);
                break;
            case call::mode::thread:
                emit_opcode(opcode::OP_ScriptLocalMethodThreadCall, { exp.name->value, argcount });
                break;
            case call::mode::childthread:
                emit_opcode(opcode::OP_ScriptLocalMethodChildThreadCall, { exp.name->value, argcount });
                break;
            case call::mode::builtin:
                // no local builtins
                break;
        }
    }
    else if (type == call::type::far)
    {
        switch (exp.mode)
        {
            case call::mode::normal:
                emit_opcode(opcode::OP_ScriptFarMethodCall, { path, exp.name->value });
                break;
            case call::mode::thread:
                emit_opcode(opcode::OP_ScriptFarMethodThreadCall, { path, exp.name->value, argcount });
                break;
            case call::mode::childthread:
                emit_opcode(opcode::OP_ScriptFarMethodChildThreadCall, { path, exp.name->value, argcount });
                break;
            case call::mode::builtin:
                // no far builtins
                break;
        }
    }
    else if (type == call::type::builtin)
    {
        if (exp.mode != call::mode::normal)
            throw comp_error(exp.loc(), "builtin calls can't be threaded");

        if (ctx_->props() & props::farcall)
        {
            emit_opcode(opcode::OP_CallBuiltinMethod, { exp.name->value, argcount });
        }
        else
        {
            switch (exp.args->list.size())
            {
                case 0:
                    emit_opcode(opcode::OP_CallBuiltinMethod0, exp.name->value);
                    break;
                case 1:
                    emit_opcode(opcode::OP_CallBuiltinMethod1, exp.name->value);
                    break;
                case 2:
                    emit_opcode(opcode::OP_CallBuiltinMethod2, exp.name->value);
                    break;
                case 3:
                    emit_opcode(opcode::OP_CallBuiltinMethod3, exp.name->value);
                    break;
                case 4:
                    emit_opcode(opcode::OP_CallBuiltinMethod4, exp.name->value);
                    break;
                case 5:
                    emit_opcode(opcode::OP_CallBuiltinMethod5, exp.name->value);
                    break;
                default:
                    emit_opcode(opcode::OP_CallBuiltinMethod, { exp.name->value, argcount });
                    break;
            }
        }
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

auto compiler::emit_expr_add_array(expr_add_array const& exp, scope& scp) -> void
{
    emit_opcode(opcode::OP_EmptyArray);

    for (auto const& arg : exp.args->list)
    {
        emit_expr(arg, scp);
        emit_opcode(opcode::OP_AddArray);
    }
}

auto compiler::emit_expr_parameters(expr_parameters const& exp, scope& scp) -> void
{
    if (ctx_->props() & props::params)
    {
        auto num = static_cast<u32>(exp.list.size());

        if (num)
        {
            auto data = std::vector<std::string>{};
            auto size = (ctx_->props() & props::hash) ? num * 8 : num;

            data.push_back(fmt::format("{}", num));

            for (auto const& entry : exp.list)
            {
                auto index = variable_initialize(*entry, scp);
                data.push_back((ctx_->props() & props::hash) ? entry->value : fmt::format("{}", index));
            }

            emit_opcode(opcode::OP_FormalParams, data);
            function_->instructions.back()->size += size;
            index_ += size;
        }
        else
        {
            emit_opcode( opcode::OP_checkclearparams);
        }
    }
    else
    {
        for (auto const& entry : exp.list)
        {
            emit_opcode(opcode::OP_SafeCreateVariableFieldCached, fmt::format("{}", variable_initialize(*entry, scp)));
        }

        emit_opcode(opcode::OP_checkclearparams);
    }
}

auto compiler::emit_expr_arguments(expr_arguments const& exp, scope& scp) -> void
{
    //std::reverse(exp.list.begin(), exp.list.end()); // use reverse range

    // for (auto const& entry : exp.list)
    // {
    //     emit_expr(entry, scp);
    // }

    for (auto it = exp.list.rbegin(); it != exp.list.rend(); ++it)
    {
        emit_expr(*it, scp);
    }
}

auto compiler::emit_expr_isdefined(expr_isdefined const& exp, scope& scp) -> void
{
    emit_expr(exp.value, scp);
    emit_opcode(opcode::OP_IsDefined);
}

auto compiler::emit_expr_istrue(expr_istrue const& exp, scope& scp) -> void
{
    emit_expr(exp.value, scp);
    emit_opcode(opcode::OP_IsTrue);
}

auto compiler::emit_expr_reference(expr_reference const& exp, scope&) -> void
{
    bool method = false;
    auto path = std::string{};
    auto type = resolve_reference_type(exp, path, method);

    if (ctx_->props() & props::farcall && type == call::type::local)
    {
        type = call::type::far;
    }

    switch (type)
    {
        case call::type::local:
            emit_opcode(opcode::OP_GetLocalFunction, exp.name->value);
            break;
        case call::type::far:
            emit_opcode(opcode::OP_GetFarFunction, { path, exp.name->value });
            break;
        case call::type::builtin:
            if (method)
                emit_opcode(opcode::OP_GetBuiltinMethod, exp.name->value);
            else
                emit_opcode(opcode::OP_GetBuiltinFunction, exp.name->value);
            break;
    }
}

auto compiler::emit_expr_size(expr_size const& exp, scope& scp) -> void
{
    emit_expr(exp.obj, scp);
    emit_opcode(opcode::OP_size);
}

auto compiler::emit_expr_tuple(expr_tuple const& exp, scope& scp) -> void
{
    emit_expr_variable_ref(exp.temp, scp, true);

    auto index = 0u;

    for (auto const& entry : exp.list)
    {
        if (index == 0)
            emit_opcode(opcode::OP_GetZero);
        else
            emit_opcode(opcode::OP_GetByte, fmt::format("{}", index));

        index++;

        emit_opcode(opcode::OP_EvalLocalArrayCached, fmt::format("{}", variable_access(*exp.temp.as_identifier, scp)));

        emit_expr_variable_ref(entry, scp, true);
    }

    emit_expr_clear_local(*exp.temp.as_identifier, scp);
}

auto compiler::emit_expr_variable_ref(expr const& exp, scope& scp, bool set) -> void
{
    switch (exp.kind())
    {
        case node::expr_array:
            emit_expr_array_ref(*exp.as_array, scp, set);
            break;
        case node::expr_field:
            emit_expr_field_ref(*exp.as_field, scp, set);
            break;
        case node::expr_identifier:
            emit_expr_local_ref(*exp.as_identifier, scp, set);
            break;
        default:
            throw comp_error(exp.loc(), "invalid lvalue");
    }
}

auto compiler::emit_expr_array_ref(expr_array const& exp, scope& scp, bool set) -> void
{
    emit_expr(exp.key, scp);

    switch (exp.obj.kind())
    {
        case node::expr_game:
            emit_opcode(opcode::OP_GetGameRef);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_array:
        case node::expr_field:
            emit_expr_variable_ref(exp.obj, scp, false);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_identifier:
        {
            if (!variable_initialized(*exp.obj.as_identifier, scp))
            {
                auto index = variable_initialize(*exp.obj.as_identifier, scp);
                emit_opcode(opcode::OP_EvalNewLocalArrayRefCached0, (ctx_->props() & props::hash) ? exp.obj.as_identifier->value : fmt::format("{}", index));

                if (!set) throw comp_error(exp.loc(), "INTERNAL: VAR CREATED BUT NOT SET");
            }
            else
            {
                auto index = variable_access(*exp.obj.as_identifier, scp);

                if (index == 0)
                    emit_opcode(opcode::OP_EvalLocalArrayRefCached0);
                else
                    emit_opcode(opcode::OP_EvalLocalArrayRefCached, fmt::format("{}", index));
            }

            if (set) emit_opcode(opcode::OP_SetVariableField);
        }
            break;
        case node::expr_call:
        case node::expr_method:
        default:
            throw comp_error(exp.loc(), "invalid array lvalue");
    }
}

auto compiler::emit_expr_field_ref(expr_field const& exp, scope& scp, bool set) -> void
{
    auto const& field = exp.field->value;

    switch (exp.obj.kind())
    {
        case node::expr_level:
            set ? emit_opcode(opcode::OP_SetLevelFieldVariableField, field) : emit_opcode(opcode::OP_EvalLevelFieldVariableRef, field);
            break;
        case node::expr_anim:
            set ? emit_opcode(opcode::OP_SetAnimFieldVariableField, field) : emit_opcode(opcode::OP_EvalAnimFieldVariableRef, field);
            break;
        case node::expr_self:
            set ? emit_opcode(opcode::OP_SetSelfFieldVariableField, field) : emit_opcode(opcode::OP_EvalSelfFieldVariableRef, field);
            break;
        case node::expr_array:
            emit_expr_array(*exp.obj.as_array, scp);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_field:
            emit_expr_field(*exp.obj.as_field, scp);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableObjectCached, fmt::format("{}", variable_access(*exp.obj.as_identifier, scp)));
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_call:
            emit_expr_call(*exp.obj.as_call, scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_method:
            emit_expr_method(*exp.obj.as_method, scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        default:
            throw comp_error(exp.obj.loc(), "not an object");
    }
}

auto compiler::emit_expr_local_ref(expr_identifier const& exp, scope& scp, bool set) -> void
{
    auto const it = constants_.find(exp.value);

    if (it != constants_.end())
    {
        throw comp_error(exp.loc(), fmt::format("variable name already defined as constant '{}'", exp.value));
    }

    if (set)
    {
        if (!variable_initialized(exp, scp))
        {
            auto index = variable_initialize(exp, scp);
            emit_opcode(opcode::OP_SetNewLocalVariableFieldCached0, (ctx_->props() & props::hash) ? exp.value : fmt::format("{}", index));
        }
        else
        {
            auto index = variable_access(exp, scp);

            if (index == 0)
                emit_opcode(opcode::OP_SetLocalVariableFieldCached0);
            else
                emit_opcode(opcode::OP_SetLocalVariableFieldCached, fmt::format("{}", index));
        }
    }
    else
    {
        auto index = variable_access(exp, scp);

        if (index == 0)
            emit_opcode(opcode::OP_EvalLocalVariableRefCached0);
        else
            emit_opcode(opcode::OP_EvalLocalVariableRefCached, fmt::format("{}", index));
    }
}

auto compiler::emit_expr_variable(expr const& exp, scope& scp) -> void
{
    switch (exp.kind())
    {
        case node::expr_array:
            emit_expr_array(*exp.as_array, scp);
            break;
        case node::expr_field:
            emit_expr_field(*exp.as_field, scp);
            break;
        case node::expr_identifier:
            emit_expr_local(*exp.as_identifier, scp);
            break;
        default:
            throw comp_error(exp.loc(), "invalid variable type.");
    }
}

auto compiler::emit_expr_array(expr_array const& exp, scope& scp) -> void
{
    emit_expr(exp.key, scp);

    if (exp.obj == node::expr_identifier)
    {
        emit_opcode(opcode::OP_EvalLocalArrayCached, fmt::format("{}", variable_access(*exp.obj.as_identifier, scp)));
    }
    else
    {
        emit_expr(exp.obj, scp);
        emit_opcode(opcode::OP_EvalArray);
    }
}

auto compiler::emit_expr_field(expr_field const& exp, scope& scp) -> void
{
    auto const& field = exp.field->value;

    switch (exp.obj.kind())
    {
        case node::expr_level:
            emit_opcode(opcode::OP_EvalLevelFieldVariable, field);
            break;
        case node::expr_anim:
            emit_opcode(opcode::OP_EvalAnimFieldVariable, field);
            break;
        case node::expr_self:
            emit_opcode(opcode::OP_EvalSelfFieldVariable, field);
            break;
        case node::expr_array:
            emit_expr_array(*exp.obj.as_array, scp);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_field:
            emit_expr_field(*exp.obj.as_field, scp);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_call:
            emit_expr_call(*exp.obj.as_call, scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_method:
            emit_expr_method(*exp.obj.as_method, scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableObjectCached, fmt::format("{}", variable_access(*exp.obj.as_identifier, scp)));
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        default:
            throw comp_error(exp.loc(), "unknown field variable object type");
    }
}

auto compiler::emit_expr_local(expr_identifier const& exp, scope& scp) -> void
{
    auto const it = constants_.find(exp.value);

    if (it != constants_.end())
    {
        // should only allow: string, loc string, number, vector
        emit_expr(*it->second, scp);
        return;
    }

    auto index = variable_access(exp, scp);

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
            emit_opcode(opcode::OP_EvalLocalVariableCached, fmt::format("{}", index));
            break;
    }
}

auto compiler::emit_expr_object(expr const& exp, scope& scp) -> void
{
    switch (exp.kind())
    {
        case node::expr_level:
            emit_opcode(opcode::OP_GetLevelObject);
            break;
        case node::expr_anim:
            emit_opcode(opcode::OP_GetAnimObject);
            break;
        case node::expr_self:
            emit_opcode(opcode::OP_GetSelfObject);
            break;
        case node::expr_array:
            emit_expr_array(*exp.as_array, scp);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_field:
            emit_expr_field(*exp.as_field, scp);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_call:
            emit_expr_call(*exp.as_call, scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_method:
            emit_expr_method(*exp.as_method, scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableObjectCached, fmt::format("{}", variable_access(*exp.as_identifier, scp)));
            break;
        default:
            throw comp_error(exp.loc(), "not an object");
    }
}

auto compiler::emit_expr_vector(expr_vector const& exp, scope& scp) -> void
{
    auto data = std::vector<std::string>{};
    auto isexpr = false;

    if (exp.x == node::expr_integer)
        data.push_back(exp.x.as_integer->value);
    else if (exp.x == node::expr_float)
        data.push_back(exp.x.as_float->value);
    else isexpr = true;

    if (exp.y == node::expr_integer)
        data.push_back(exp.y.as_integer->value);
    else if (exp.y == node::expr_float)
        data.push_back(exp.y.as_float->value);
    else isexpr = true;

    if (exp.z == node::expr_integer)
        data.push_back(exp.z.as_integer->value);
    else if (exp.z == node::expr_float)
        data.push_back(exp.z.as_float->value);
    else isexpr = true;

    if (!isexpr)
    {
        if (ctx_->endian() == endian::little)
            emit_opcode(opcode::OP_GetVector, data);
        else
        {
            auto base = index_ + 1;
            auto algn = (base + 3) & ~3;
            emit_opcode(opcode::OP_GetVector, data);
            index_ += (algn - base);
            function_->instructions.back()->size += (algn - base);
        }           
    }
    else
    {
        emit_expr(exp.z, scp);
        emit_expr(exp.y, scp);
        emit_expr(exp.x, scp);
        emit_opcode(opcode::OP_vector);
    }
}

auto compiler::emit_expr_animation(expr_animation const& exp) -> void
{
    if (animname_.empty())
    {
        throw comp_error(exp.loc(), "trying to use animation without specified using animtree");
    }

    if (animload_)
    {
        emit_opcode(opcode::OP_GetAnimation, { "", exp.value });
    }
    else
    {
        animload_ = true;
        emit_opcode(opcode::OP_GetAnimation, { animname_, exp.value });
    }
}

auto compiler::emit_expr_animtree(expr_animtree const& exp) -> void
{
    if (animname_.empty())
    {
        throw comp_error(exp.loc(), "trying to use animtree without specified using animtree");
    }

    if (animload_)
    {
        emit_opcode(opcode::OP_GetAnimTree, "");
    }
    else
    {
        animload_ = true;
        emit_opcode(opcode::OP_GetAnimTree, animname_);
    }
}

auto compiler::emit_expr_istring(expr_istring const& exp) -> void
{
    emit_opcode(opcode::OP_GetIString, exp.value);
}

auto compiler::emit_expr_string(expr_string const& exp) -> void
{
    emit_opcode(opcode::OP_GetString, exp.value);
}

auto compiler::emit_expr_float(expr_float const& exp) -> void
{
    emit_opcode(opcode::OP_GetFloat, exp.value);
}

auto compiler::emit_expr_integer(expr_integer const& exp) -> void
{
    auto value = std::atoll(exp.value.data());

    if (value == 0)
    {
        emit_opcode(opcode::OP_GetZero);
    }
    else if (value > 0 && value < 256)
    {
        emit_opcode(opcode::OP_GetByte, exp.value);
    }
    else if (value < 0 && value > -256)
    {
        emit_opcode(opcode::OP_GetNegByte, exp.value.substr(1));
    }
    else if (value > 0 && value < 65536)
    {
        emit_opcode(opcode::OP_GetUnsignedShort, exp.value);
    }
    else if (value < 0 && value > -65536)
    {
        emit_opcode(opcode::OP_GetNegUnsignedShort, exp.value.substr(1));
    }
    else
    {
        if (ctx_->engine() == engine::iw9)
        {
            if (value > 0 && value < 4294967296)
            {
                emit_opcode(opcode::OP_GetUnsignedInt, exp.value);
            }
            else if  (value < 0 && value > -4294967296)
            {
                emit_opcode(opcode::OP_GetNegUnsignedInt, exp.value.substr(1));
            }
            else
            {
                emit_opcode(opcode::OP_GetInteger64, exp.value);
            }
        }
        else
        {
             emit_opcode(opcode::OP_GetInteger, exp.value);
        }
    }
}

auto compiler::emit_expr_false(expr_false const&) -> void
{
    emit_opcode(opcode::OP_GetZero);
}

auto compiler::emit_expr_true(expr_true const&) -> void
{
    emit_opcode(opcode::OP_GetByte, "1");
}

auto compiler::emit_create_local_vars(scope& scp) -> void
{
    if (scp.create_count != scp.public_count)
    {
        for (auto i = scp.create_count; i < scp.public_count; i++)
        {
            emit_opcode(opcode::OP_CreateLocalVariable, (ctx_->props() & props::hash) ? scp.vars[i].name : fmt::format("{}", scp.vars[i].create));
            scp.vars[i].init = true;
        }

        scp.create_count = scp.public_count;
    }
}

auto compiler::emit_remove_local_vars(scope& scp) -> void
{
    if (scp.abort == scope::abort_none)
    {
        auto count = scp.create_count - scp.public_count;

        if (count > 0)
        {
            emit_opcode(opcode::OP_RemoveLocalVariables, fmt::format("{}", count));
        }
    }
}

auto compiler::emit_opcode(opcode op) -> void
{
    function_->instructions.push_back(make_instruction());

    auto& inst = function_->instructions.back();
    inst->opcode = op;
    inst->size = ctx_->opcode_size(op);
    inst->index = index_;

    index_ += inst->size;
}

auto compiler::emit_opcode(opcode op, std::string const& data) -> void
{
    function_->instructions.push_back(make_instruction());

    auto& inst = function_->instructions.back();
    inst->opcode = op;
    inst->size = ctx_->opcode_size(op);
    inst->index = index_;
    inst->data.push_back(data);

    index_ += inst->size;
}

auto compiler::emit_opcode(opcode op, std::vector<std::string> const& data) -> void
{
    function_->instructions.push_back(make_instruction());

    auto& inst = function_->instructions.back();
    inst->opcode = op;
    inst->size = ctx_->opcode_size(op);
    inst->index = index_;
    inst->data = data;

    index_ += inst->size;
}

auto compiler::process_function(decl_function const& func) -> void
{
    auto ins = scopes_.insert({ func.body.get(), make_scope() });
    auto& scp_body = ins.first->second;

    process_expr_parameters(*func.params, *scp_body);
    process_stmt_comp(*func.body, *scp_body);
}

auto compiler::process_stmt(stmt const& stm, scope& scp) -> void
{
    switch (stm.kind())
    {
        case node::stmt_list:
            process_stmt_list(*stm.as_list, scp);
            break;
        case node::stmt_comp:
            process_stmt_comp(*stm.as_comp, scp);
            break;
        case node::stmt_dev:
            process_stmt_dev(*stm.as_dev, scp);
            break;
        case node::stmt_expr:
            process_stmt_expr(*stm.as_expr, scp);
            break;
        case node::stmt_assign:
            process_stmt_assign(*stm.as_assign, scp);
            break;
        case node::stmt_waittill:
            process_stmt_waittill(*stm.as_waittill, scp);
            break;
        case node::stmt_if:
            process_stmt_if(*stm.as_if, scp);
            break;
        case node::stmt_ifelse:
            process_stmt_ifelse(*stm.as_ifelse, scp);
            break;
        case node::stmt_while:
            process_stmt_while(*stm.as_while, scp);
            break;
        case node::stmt_dowhile:
            process_stmt_dowhile(*stm.as_dowhile, scp);
            break;
        case node::stmt_for:
            process_stmt_for(*stm.as_for, scp);
            break;
        case node::stmt_foreach:
            process_stmt_foreach(*stm.as_foreach, scp);
            break;
        case node::stmt_switch:
            process_stmt_switch(*stm.as_switch, scp);
            break;
        case node::stmt_break:
            process_stmt_break(*stm.as_break, scp);
            break;
        case node::stmt_continue:
            process_stmt_continue(*stm.as_continue, scp);
            break;
        case node::stmt_return:
            process_stmt_return(*stm.as_return, scp);
            break;
        case node::stmt_call:
        case node::stmt_endon:
        case node::stmt_notify:
        case node::stmt_wait:
        case node::stmt_waittillmatch:
        case node::stmt_waittillframeend:
        case node::stmt_waitframe:
        case node::stmt_case:
        case node::stmt_default:
        case node::stmt_breakpoint:
        case node::stmt_prof_begin:
        case node::stmt_prof_end:
        case node::stmt_assert:
        case node::stmt_assertex:
        case node::stmt_assertmsg:
            break;
        default:
            throw comp_error(stm.loc(), "unknown statement");
    }
}

auto compiler::process_stmt_list(stmt_list const& stm, scope& scp) -> void
{
    for (auto const& entry : stm.list)
    {
        process_stmt(entry, scp);
    }
}

auto compiler::process_stmt_comp(stmt_comp const& stm, scope& scp) -> void
{
    process_stmt_list(*stm.block, scp);
}

auto compiler::process_stmt_dev(stmt_dev const& stm, scope& scp) -> void
{
    process_stmt_list(*stm.block, scp);
}

auto compiler::process_stmt_expr(stmt_expr const& stm, scope& scp) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_increment:
            process_expr(stm.value.as_increment->lvalue, scp);
            break;
        case node::expr_decrement:
            process_expr(stm.value.as_decrement->lvalue, scp);
            break;
        case node::expr_assign_equal:
        case node::expr_assign_add:
        case node::expr_assign_sub:
        case node::expr_assign_mul:
        case node::expr_assign_div:
        case node::expr_assign_mod:
        case node::expr_assign_shift_left:
        case node::expr_assign_shift_right:
        case node::expr_assign_bitwise_or:
        case node::expr_assign_bitwise_and:
        case node::expr_assign_bitwise_exor:
            process_expr(stm.value.as_assign->lvalue, scp);
            break;
        case node::null:
            break;
        default:
            throw comp_error(stm.loc(), "unknown expr statement expression");
    }
}

auto compiler::process_stmt_assign(stmt_assign const& stm, scope& scp) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_increment:
            process_expr(stm.value.as_increment->lvalue, scp);
            break;
        case node::expr_decrement:
            process_expr(stm.value.as_decrement->lvalue, scp);
            break;
        case node::expr_assign_equal:
        case node::expr_assign_add:
        case node::expr_assign_sub:
        case node::expr_assign_mul:
        case node::expr_assign_div:
        case node::expr_assign_mod:
        case node::expr_assign_shift_left:
        case node::expr_assign_shift_right:
        case node::expr_assign_bitwise_or:
        case node::expr_assign_bitwise_and:
        case node::expr_assign_bitwise_exor:
            process_expr(stm.value.as_assign->lvalue, scp);
            break;
        default:
            throw comp_error(stm.loc(), "unknown assign statement expression");
    }
}

auto compiler::process_stmt_waittill(stmt_waittill const& stm, scope& scp) -> void
{
    for (auto const& entry : stm.args->list)
    {
        if (entry != node::expr_identifier)
        {
            throw comp_error(entry.loc(), "illegal waittill param, must be a local variable");
        }

        variable_register(*entry.as_identifier, scp);
    }
}

auto compiler::process_stmt_if(stmt_if const& stm, scope& scp) -> void
{
    auto ins = scopes_.insert({ stm.body.as_node.get(), make_scope() });
    auto& scp_then = ins.first->second;

    scp.copy(scp_then);
    process_stmt(stm.body, *scp_then);

    std::vector<scope*> childs({ scp_then.get() });
    scp.merge(childs);
}

auto compiler::process_stmt_ifelse(stmt_ifelse const& stm, scope& scp) -> void
{
    auto childs = std::vector<scope*>{};
    auto abort = scope::abort_return;

    auto ins1 = scopes_.insert({ stm.stmt_if.as_node.get(), make_scope() });
    auto ins2 = scopes_.insert({ stm.stmt_else.as_node.get(), make_scope() });
    auto& scp_then = ins1.first->second;
    auto& scp_else = ins2.first->second;

    scp.copy(scp_then);
    process_stmt(stm.stmt_if, *scp_then);

    if (scp_then->abort <= scope::abort_return)
    {
        abort = scp_then->abort;
        if (abort == scope::abort_none)
            childs.push_back(scp_then.get());
    }

    scp.copy(scp_else);
    process_stmt(stm.stmt_else, *scp_else);

    if (scp_else->abort <= abort)
    {
        abort = scp_else->abort;
        if (abort == scope::abort_none)
            childs.push_back(scp_else.get());
    }

    if (scp.abort == scope::abort_none)
        scp.abort = abort;

    scp.append(childs);
    scp.merge(childs);
}

auto compiler::process_stmt_while(stmt_while const& stm, scope& scp) -> void
{
    bool const_cond = is_constant_condition(stm.test);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    auto ins = scopes_.insert({ stm.body.as_node.get(), make_scope() });
    auto& scp_body = ins.first->second;

    scp.copy(scp_body);
    process_stmt(stm.body, *scp_body);

    continue_blks_.push_back(scp_body.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        scp.append({ continue_blks_.at(i) });

    if (const_cond) scp.append(break_blks_);

    scp.merge({ scp_body.get() });

    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

auto compiler::process_stmt_dowhile(stmt_dowhile const& stm, scope& scp) -> void
{
    bool const_cond = is_constant_condition(stm.test);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    auto ins = scopes_.insert({ stm.body.as_node.get(), make_scope() });
    auto& scp_body = ins.first->second;

    scp.copy(scp_body);
    process_stmt(stm.body, *scp_body);

    continue_blks_.push_back(scp_body.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        scp.append({ continue_blks_.at(i) });

    if (const_cond) scp.append(break_blks_);

    scp.merge({ scp_body.get() });

    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

auto compiler::process_stmt_for(stmt_for const& stm, scope& scp) -> void
{
    bool const_cond = is_constant_condition(stm.test);

    auto ins1 = scopes_.insert({ stm.body.as_node.get(), make_scope() });
    auto ins2 = scopes_.insert({ stm.iter.as_node.get(), make_scope() });
    auto& scp_body = ins1.first->second;
    auto& scp_iter = ins2.first->second;

    process_stmt(stm.init, scp);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    scp.copy(scp_body);
    scp.copy(scp_iter);

    process_stmt(stm.body, *scp_body);

    continue_blks_.push_back(scp_body.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        scp.append({ continue_blks_.at(i) });

    process_stmt(stm.iter, *scp_iter);

    scp.append({ scp_iter.get() });
    scp.merge({ scp_iter.get() });

    if (const_cond) scp.append(break_blks_);

    scp.merge({ scp_body.get() });

    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

auto compiler::process_stmt_foreach(stmt_foreach const& stm, scope& scp) -> void
{
    auto ins1 = scopes_.insert({ stm.body.as_node.get(), make_scope() });
    auto ins2 = scopes_.insert({ stm.key.as_node.get(), make_scope() });
    auto& scp_body = ins1.first->second;
    auto& scp_iter = ins2.first->second;

    process_expr(stm.array, scp);

    if (ctx_->props() & props::foreach)
        process_expr(stm.key, scp);

    if (ctx_->props() & props::foreach && stm.use_key)
        process_expr(stm.index, scp);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    scp.copy(scp_body);
    scp.copy(scp_iter);

    process_expr(stm.value, *scp_body);
    process_stmt(stm.body, *scp_body);

    continue_blks_.push_back(scp_body.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        scp.append({ continue_blks_.at(i) });

    if (!(ctx_->props() & props::foreach))
        process_expr(stm.key, *scp_iter);

    scp.append({ scp_iter.get() });
    scp.merge({ scp_iter.get() });
    scp.merge({ scp_body.get() });

    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

auto compiler::process_stmt_switch(stmt_switch const& stm, scope& scp) -> void
{
    auto childs = std::vector<scope*>{};
    auto abort = scope::abort_return;
    auto has_default = false;
    scope* default_ctx = nullptr;
    auto old_breaks = break_blks_;
    break_blks_.clear();

    for (auto i = 0u; i < stm.body->block->list.size(); i++)
    {
        auto& entry = stm.body->block->list[i];

        if (entry == node::stmt_case)
        {
            auto ins = scopes_.insert({ entry.as_case->body.get(), make_scope() });
            auto& scp_body = ins.first->second;

            scp.copy(scp_body);
            process_stmt_list(*entry.as_case->body, *scp_body);

            if (scp_body->abort != scope::abort_none)
            {
                if (scp_body->abort == scope::abort_break )
                {
                    scp_body->abort = scope::abort_none;
                    abort = scope::abort_none;
                    childs.push_back(scp_body.get());
                }
                else if (scp_body->abort <= abort )
                {
                    abort = scp_body->abort;
                }
            }
        }
        else if (entry == node::stmt_default)
        {
            auto ins = scopes_.insert({ entry.as_default->body.get(), make_scope() });
            auto& scp_body = ins.first->second;
    
            scp.copy(scp_body);
            process_stmt_list(*entry.as_default->body, *scp_body);
            has_default = true;
            default_ctx = scp_body.get();

            if (scp_body->abort != scope::abort_none)
            {
                if (scp_body->abort == scope::abort_break )
                {
                    scp_body->abort = scope::abort_none;
                    abort = scope::abort_none;
                    childs.push_back(scp_body.get());
                }
                else if (scp_body->abort <= abort )
                {
                    abort = scp_body->abort;
                }
            }
        }
    }

    if (has_default)
    {
        if (default_ctx->abort == scope::abort_none)
        {
            break_blks_.push_back(default_ctx);

            if (scp.abort == scope::abort_none)
                scp.abort = abort;
        }

        scp.append(break_blks_);
        scp.merge(childs);
    }

    break_blks_ = old_breaks;
}

auto compiler::process_stmt_break(stmt_break const&, scope& scp) -> void
{
    if (scp.abort == scope::abort_none)
    {
        break_blks_.push_back(&scp);
        scp.abort = scope::abort_break;
    }
}

auto compiler::process_stmt_continue(stmt_continue const&, scope& scp) -> void
{
    if (scp.abort == scope::abort_none)
    {
        continue_blks_.push_back(&scp);
        scp.abort = scope::abort_continue;
    }
}

auto compiler::process_stmt_return(stmt_return const&, scope& scp) -> void
{
    if (scp.abort == scope::abort_none)
    {
        scp.abort = scope::abort_return;
    }
}

auto compiler::process_expr(expr const& exp, scope& scp) -> void
{
    if (exp == node::expr_identifier)
    {
        variable_register(*exp.as_identifier, scp);
    }
    else if (exp == node::expr_array)
    {
        process_expr(exp.as_array->obj, scp);
    }
    else if (exp == node::expr_tuple)
    {
        process_expr_tuple(*exp.as_tuple, scp);
    }
}

auto compiler::process_expr_tuple(expr_tuple const& exp, scope& scp) -> void
{
    process_expr(exp.temp, scp);

    for (auto const& entry : exp.list)
    {
        process_expr(entry, scp);
    }
}

auto compiler::process_expr_parameters(expr_parameters const& exp, scope& scp) -> void
{
    for (auto const& entry : exp.list)
    {
        variable_register(*entry, scp);
    }
}

auto compiler::variable_register(expr_identifier const& exp, scope& scp) -> void
{
    auto it = std::find_if(scp.vars.begin(), scp.vars.end(), [&](scope::var const& v) { return v.name == exp.value; });

    if (it == scp.vars.end())
    {
        auto found = false;

        for (auto i = 0u; i < stackframe_.size(); i++)
        {
            if (stackframe_[i] == exp.value)
            {
                scp.vars.push_back({ exp.value, static_cast<u8>(i), false });
                found = true;
                break;
            }
        }

        if (!found)
        {
            scp.vars.push_back({ exp.value, static_cast<u8>(stackframe_.size()), false });
            stackframe_.push_back(exp.value);
        }
    }
}

auto compiler::variable_initialized(expr_identifier const& exp, scope& scp) -> bool
{
    for (auto i = 0u; i < scp.vars.size(); i++)
    {
        if (scp.vars[i].name == exp.value)
        {
            return scp.vars[i].init;
        }
    }

   throw comp_error(exp.loc(), fmt::format("local variable '{}' not found", exp.value));
}

auto compiler::variable_initialize(expr_identifier const& exp, scope& scp) -> u8
{
    for (auto i = 0u; i < scp.vars.size(); i++)
    {
        if (scp.vars[i].name == exp.value)
        {
            if (!scp.vars[i].init)
            {
                for (auto j = 0u; j < i; j++)
                {
                    if (!scp.vars[j].init)
                    {
                        scp.vars[j].init = true;
                        emit_opcode(opcode::OP_CreateLocalVariable, (ctx_->props() & props::hash) ? scp.vars[j].name : fmt::format("{}", scp.vars[j].create));
                    }
                }

                scp.vars[i].init = true;
                scp.create_count = i + 1;
                return scp.vars[i].create;
            }
        }
    }

    throw comp_error(exp.loc(), fmt::format("local variable '{}' not found", exp.value));
}

auto compiler::variable_create(expr_identifier const& exp, scope& scp) -> u8
{
    for (auto i = 0u; i < scp.vars.size(); i++)
    {
        auto& var = scp.vars[i];

        if (var.name == exp.value)
        {
            if (!var.init)
            {
                emit_opcode(opcode::OP_CreateLocalVariable, (ctx_->props() & props::hash) ? var.name : fmt::format("{}", var.create));
                var.init = true;
                scp.create_count++;
            }

            return static_cast<u8>(scp.create_count - 1 - i);
        }
    }

    throw comp_error(exp.loc(), fmt::format("local variable '{}' not found", exp.value));
}

auto compiler::variable_access(expr_identifier const& exp, scope& scp) -> u8
{
    for (auto i = 0u; i < scp.vars.size(); i++)
    {
        if (scp.vars[i].name == exp.value)
        {
            if (scp.vars[i].init)
            {
                return static_cast<u8>(scp.create_count - 1 - i);
            }

            throw comp_error(exp.loc(), fmt::format("local variable '{}' not initialized", exp.value));
        }
    }

    throw comp_error(exp.loc(), fmt::format("local variable '{}' not found", exp.value));
}

auto compiler::resolve_function_type(expr_function const& exp, std::string& path) -> call::type
{
    if (!exp.path->value.empty())
    {
        path = exp.path->value;
        return call::type::far;
    }

    auto& name = exp.name->value;

    if (ctx_->func_exists(name) || ctx_->meth_exists(name))
        return call::type::builtin;

    for (auto const& entry : localfuncs_)
    {
        if (entry == name)
            return call::type::local;
    }

    if (ctx_->is_includecall(name, path))
        return call::type::far;

    throw comp_error(exp.loc(), "couldn't determine function call type");
}

auto compiler::resolve_reference_type(expr_reference const& exp, std::string& path, bool& method) -> call::type
{
    if (!exp.path->value.empty())
    {
        path = exp.path->value;
        return call::type::far;
    }

    auto& name = exp.name->value;

    if (ctx_->func_exists(name))
    {
        method = false;
        return call::type::builtin;
    }

    if (ctx_->meth_exists(name))
    {
        method = true;
        return call::type::builtin;
    }

    for (auto const& entry : localfuncs_)
    {
        if (entry == name)
            return call::type::local;
    }

    if (ctx_->is_includecall(name, path))
        return call::type::far;

    throw comp_error(exp.loc(), "couldn't determine function reference type");
}

auto compiler::is_constant_condition(expr const& exp) -> bool
{
    switch (exp.kind())
    {
        case node::null:
        case node::expr_true:
            return true;
        case node::expr_false:
            throw comp_error(exp.loc(), "condition can't be always false");
        case node::expr_integer:
        {
            auto num = std::stoi(exp.as_integer->value);
            if (num != 0)
                return true;
            else
                throw comp_error(exp.loc(), "condition can't be always false");
        }
        default:
            break;
    }

    return false;
}

auto compiler::insert_label(std::string const& name) -> void
{
    auto const itr = function_->labels.find(index_);

    if (itr != function_->labels.end())
    {
       for (auto& inst : function_->instructions)
       {
           switch (inst->opcode)
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

auto compiler::insert_label() -> std::string
{
    auto const itr = function_->labels.find(index_);

    if (itr != function_->labels.end())
    {
       return itr->second;
    }
    else
    {
        label_idx_++;
        auto name = fmt::format("loc_{}", label_idx_);
        function_->labels.insert({ index_, name });
        return name;
    }
}

auto compiler::create_label() -> std::string
{
    label_idx_++;
    return fmt::format("loc_{}", label_idx_);
}

} // namespace xsk::gsc
