// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/compiler.hpp"
#include "xsk/gsc/context.hpp"

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
    assembly_ = assembly::make();
    localfuncs_.clear();
    constants_.clear();
    developer_thread_ = false;
    animload_ = false;
    animname_ = {};
    index_ = 1;
    debug_pos_ = { 0, 0 };

    ctx_->init_includes();

    for (auto const& inc : prog.includes)
    {
        auto const& path = inc->path->value;

        if (!ctx_->load_include(path))
        {
            throw error(std::format("duplicated include file {}", path));
        }
    }

    for (auto const& dec : prog.declarations)
    {
        if (dec->is<decl_function>())
        {
            auto const& name = dec->as<decl_function>().name->value;

            if (ctx_->func_exists(name) || ctx_->meth_exists(name))
            {
                throw comp_error(dec->loc(), std::format("function name '{}' already defined as builtin", name));
            }

            for (auto const& entry : localfuncs_)
            {
                if (entry == name)
                    throw comp_error(dec->loc(), std::format("function name '{}' already defined as local function", name));
            }

            localfuncs_.push_back(dec->as<decl_function>().name->value);
        }
    }

    for (auto const& dec : prog.declarations)
    {
        emit_decl(*dec);
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
            emit_decl_usingtree(dec.as<decl_usingtree>());
            break;
        case node::decl_constant:
            emit_decl_constant(dec.as<decl_constant>());
            break;
        case node::decl_function:
            emit_decl_function(dec.as<decl_function>());
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
        throw comp_error(constant.loc(), std::format("duplicated constant '{}'", constant.name->value));

    constants_.insert({ constant.name->value, constant.value.get() });
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

    function_ = function::make();
    function_->index = index_;
    function_->name = func.name->value;
    function_->id = (ctx_->props() & props::hash) ? 0 : ctx_->token_id(function_->name);

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
    debug_pos_ = { stm.loc().begin.line, stm.loc().begin.column };

    switch (stm.kind())
    {
        case node::stmt_list:
            emit_stmt_list(stm.as<stmt_list>(), scp, last);
            break;
        case node::stmt_comp:
            emit_stmt_comp(stm.as<stmt_comp>(), scp, last);
            break;
        case node::stmt_dev:
            emit_stmt_dev(stm.as<stmt_dev>(), scp, last);
            break;
        case node::stmt_expr:
            emit_stmt_expr(stm.as<stmt_expr>(), scp);
            break;
        case node::stmt_endon:
            emit_stmt_endon(stm.as<stmt_endon>(), scp);
            break;
        case node::stmt_notify:
            emit_stmt_notify(stm.as<stmt_notify>(), scp);
            break;
        case node::stmt_wait:
            emit_stmt_wait(stm.as<stmt_wait>(), scp);
            break;
        case node::stmt_waittill:
            emit_stmt_waittill(stm.as<stmt_waittill>(), scp);
            break;
        case node::stmt_waittillmatch:
            emit_stmt_waittillmatch(stm.as<stmt_waittillmatch>(), scp);
            break;
        case node::stmt_waittillframeend:
            emit_stmt_waittillframeend(stm.as<stmt_waittillframeend>(), scp);
            break;
        case node::stmt_waitframe:
            emit_stmt_waitframe(stm.as<stmt_waitframe>(), scp);
            break;
        case node::stmt_if:
            emit_stmt_if(stm.as<stmt_if>(), scp, last);
            break;
        case node::stmt_ifelse:
            emit_stmt_ifelse(stm.as<stmt_ifelse>(), scp, last);
            break;
        case node::stmt_while:
            emit_stmt_while(stm.as<stmt_while>(), scp);
            break;
        case node::stmt_dowhile:
            emit_stmt_dowhile(stm.as<stmt_dowhile>(), scp);
            break;
        case node::stmt_for:
            emit_stmt_for(stm.as<stmt_for>(), scp);
            break;
        case node::stmt_foreach:
            emit_stmt_foreach(stm.as<stmt_foreach>(), scp);
            break;
        case node::stmt_switch:
            emit_stmt_switch(stm.as<stmt_switch>(), scp);
            break;
        case node::stmt_case:
            emit_stmt_case(stm.as<stmt_case>(), scp);
            break;
        case node::stmt_default:
            emit_stmt_default(stm.as<stmt_default>(), scp);
            break;
        case node::stmt_break:
            emit_stmt_break(stm.as<stmt_break>(), scp);
            break;
        case node::stmt_continue:
            emit_stmt_continue(stm.as<stmt_continue>(), scp);
            break;
        case node::stmt_return:
            emit_stmt_return(stm.as<stmt_return>(), scp);
            break;
        case node::stmt_breakpoint:
            emit_stmt_breakpoint(stm.as<stmt_breakpoint>(), scp);
            break;
        case node::stmt_prof_begin:
            emit_stmt_prof_begin(stm.as<stmt_prof_begin>(), scp);
            break;
        case node::stmt_prof_end:
            emit_stmt_prof_end(stm.as<stmt_prof_end>(), scp);
            break;
        case node::stmt_assert:
            emit_stmt_assert(stm.as<stmt_assert>(), scp);
            break;
        case node::stmt_assertex:
            emit_stmt_assertex(stm.as<stmt_assertex>(), scp);
            break;
        case node::stmt_assertmsg:
            emit_stmt_assertmsg(stm.as<stmt_assertmsg>(), scp);
            break;
        default:
            throw comp_error(stm.loc(), "unknown statement");
    }
}

auto compiler::emit_stmt_list(stmt_list const& stm, scope& scp, bool last) -> void
{
    for (auto const& entry : stm.list)
    {
        emit_stmt(*entry, scp, (&entry == &stm.list.back() && last) ? true : false);
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
    switch (stm.value->kind())
    {
        case node::expr_increment:
            emit_expr_increment(stm.value->as<expr_increment>(), scp, true);
            break;
        case node::expr_decrement:
            emit_expr_decrement(stm.value->as<expr_decrement>(), scp, true);
            break;
        case node::expr_assign:
            emit_expr_assign(stm.value->as<expr_assign>(), scp);
            break;
        case node::expr_call:
            emit_expr_call(stm.value->as<expr_call>(), scp, true);
            break;
        case node::expr_method:
            emit_expr_method(stm.value->as<expr_method>(), scp, true);
            break;
        case node::expr_empty:
            break;
        default:
            throw comp_error(stm.loc(), "unknown expr statement expression");
    }
}

auto compiler::emit_stmt_endon(stmt_endon const& stm, scope& scp) -> void
{
    emit_expr(*stm.event, scp);
    emit_expr(*stm.obj, scp);
    emit_opcode(opcode::OP_endon);
}

auto compiler::emit_stmt_notify(stmt_notify const& stm, scope& scp) -> void
{
    emit_opcode(opcode::OP_voidCodepos);

    for (auto it = stm.args->list.rbegin(); it != stm.args->list.rend(); it++)
    {
        emit_expr(**it, scp);
    }

    emit_expr(*stm.event, scp);
    emit_expr(*stm.obj, scp);
    emit_opcode(opcode::OP_notify);
}

auto compiler::emit_stmt_wait(stmt_wait const& stm, scope& scp) -> void
{
    emit_expr(*stm.time, scp);
    emit_opcode(opcode::OP_wait);
}

auto compiler::emit_stmt_waittill(stmt_waittill const& stm, scope& scp) -> void
{
    emit_expr(*stm.event, scp);
    emit_expr(*stm.obj, scp);
    emit_opcode(opcode::OP_waittill);

    for (auto const& entry : stm.args->list)
    {
        emit_opcode(opcode::OP_SafeSetWaittillVariableFieldCached, std::format("{}", variable_create(entry->as<expr_identifier>(), scp)));
    }

    emit_opcode(opcode::OP_clearparams);
}

auto compiler::emit_stmt_waittillmatch(stmt_waittillmatch const& stm, scope& scp) -> void
{
    emit_expr_arguments(*stm.args, scp);
    emit_expr(*stm.event, scp);
    emit_expr(*stm.obj, scp);
    emit_opcode(opcode::OP_waittillmatch, std::format("{}", stm.args->list.size()));
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

    if (stm.test->is<expr_not>())
    {
        emit_expr(*stm.test->as<expr_not>().rvalue, scp);
        emit_opcode(opcode::OP_JumpOnTrue, end_loc);
    }
    else
    {
        emit_expr(*stm.test, scp);
        emit_opcode(opcode::OP_JumpOnFalse, end_loc);
    }

    auto& scp_body = scopes_.at(stm.body.get());

    scp.transfer(scp_body);

    emit_stmt(*stm.body, *scp_body, last);

    last ? emit_opcode(opcode::OP_End) : emit_remove_local_vars(*scp_body);

    insert_label(end_loc);
}

auto compiler::emit_stmt_ifelse(stmt_ifelse const& stm, scope& scp, bool last) -> void
{
    auto childs = std::vector<scope*>{};
    auto else_loc = create_label();
    auto end_loc = create_label();

    if (stm.test->is<expr_not>())
    {
        emit_expr(*stm.test->as<expr_not>().rvalue, scp);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(*stm.test, scp);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    auto& scp_then = scopes_.at(stm.stmt_if.get());

    scp.transfer(scp_then);

    emit_stmt(*stm.stmt_if, *scp_then, last);

    emit_remove_local_vars(*scp_then);

    if (scp_then->abort == scope::abort_none)
        childs.push_back(scp_then.get());

    last ? emit_opcode(opcode::OP_End) : emit_opcode(opcode::OP_jump, end_loc);

    insert_label(else_loc);

    auto& scp_else = scopes_.at(stm.stmt_else.get());

    scp.transfer(scp_else);

    emit_stmt(*stm.stmt_else, *scp_else, last);

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

    auto& scp_body = scopes_.at(stm.body.get());

    scp.transfer(scp_body);
    scp_body->loc_break = break_loc;
    scp_body->loc_cont = continue_loc;

    emit_create_local_vars(*scp_body);

    scp.init(scp_body);

    auto begin_loc = insert_label();

    bool const_cond = is_constant_condition(*stm.test);

    if (!const_cond)
    {
        if (stm.test->is<expr_not>())
        {
            emit_expr(*stm.test->as<expr_not>().rvalue, scp);
            emit_opcode(opcode::OP_JumpOnTrue, break_loc);
        }
        else
        {
            emit_expr(*stm.test, scp);
            emit_opcode(opcode::OP_JumpOnFalse, break_loc);
        }
    }

    emit_stmt(*stm.body, *scp_body, false);

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

    auto& scp_body = scopes_.at(stm.body.get());

    scp.transfer(scp_body);
    scp_body->loc_break = break_loc;
    scp_body->loc_cont = continue_loc;

    emit_create_local_vars(*scp_body);

    scp.init(scp_body);

    auto begin_loc = insert_label();

    emit_stmt(*stm.body, *scp_body, false);

    insert_label(continue_loc);

    bool const_cond = is_constant_condition(*stm.test);

    if (!const_cond)
    {
        if (stm.test->is<expr_not>())
        {
            emit_expr(*stm.test->as<expr_not>().rvalue, scp);
            emit_opcode(opcode::OP_JumpOnTrue, break_loc);
        }
        else
        {
            emit_expr(*stm.test, scp);
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

    emit_stmt(*stm.init, scp, false);

    auto& scp_body = scopes_.at(stm.body.get());

    scp.transfer(scp_body);
    scp_body->loc_break = break_loc;
    scp_body->loc_cont = continue_loc;

    emit_create_local_vars(*scp_body);

    scp.init(scp_body);

    auto& scp_iter = scopes_.at(stm.iter.get());

    scp.transfer(scp_iter);

    auto begin_loc = insert_label();

    bool const_cond = is_constant_condition(*stm.test);

    if (!const_cond)
    {
        if (stm.test->is<expr_not>())
        {
            emit_expr(*stm.test->as<expr_not>().rvalue, scp);
            emit_opcode(opcode::OP_JumpOnTrue, break_loc);
        }
        else
        {
            emit_expr(*stm.test, scp);
            emit_opcode(opcode::OP_JumpOnFalse, break_loc);
        }
    }

    can_break_ = true;
    can_continue_ = true;

    emit_stmt(*stm.body, *scp_body, false);

    if (scp_body->abort == scope::abort_none)
        continue_blks_.push_back(scp_body.get());

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);

    scp_iter->init(continue_blks_);

    emit_stmt(*stm.iter, *scp_iter, false);
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

    emit_expr(*stm.container, scp);
    emit_expr_variable_ref(*stm.array, scp, true);
    emit_expr_variable(*stm.array, scp);

    if (ctx_->props() & props::farcall)
        emit_opcode(opcode::OP_CallBuiltin, { "getfirstarraykey"s, "1"s });
    else
        emit_opcode(opcode::OP_CallBuiltin1, "getfirstarraykey");

    emit_expr_variable_ref(*stm.key, scp, true);

    if (ctx_->props() & props::foreach && stm.use_key)
    {
        emit_opcode(opcode::OP_GetUndefined);
        emit_expr_variable_ref(*stm.index, scp, true);
    }

    auto& scp_body = scopes_.at(stm.body.get());
    auto& scp_iter = scopes_.at(stm.key.get());

    scp.transfer(scp_body);
    scp_body->loc_break = break_loc;
    scp_body->loc_cont = continue_loc;

    emit_create_local_vars(*scp_body);

    scp.init(scp_body);

    scp.transfer(scp_iter);

    auto begin_loc = insert_label();

    emit_expr_variable(*stm.key, scp);

    if (ctx_->props() & props::boolfuncs)
        emit_opcode(opcode::OP_IsDefined);
    else
        emit_opcode(opcode::OP_CallBuiltin1, "isdefined");

    emit_opcode(opcode::OP_JumpOnFalse, break_loc);

    can_break_ = true;
    can_continue_ = true;

    emit_expr_variable(*stm.key, *scp_body);
    emit_opcode(opcode::OP_EvalLocalArrayCached, std::format("{}", variable_access(stm.array->as<expr_identifier>(), *scp_body)));
    emit_expr_variable_ref(*stm.value, *scp_body, true);

    if (ctx_->props() & props::foreach && stm.use_key)
    {
        emit_expr_variable(*stm.key, *scp_body);
        emit_expr_variable_ref(*stm.index, *scp_body, true);
    }

    emit_stmt(*stm.body, *scp_body, false);

    if (scp_body->abort == scope::abort_none)
        continue_blks_.push_back(scp_body.get());

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);

    scp_iter->init(continue_blks_);

    emit_expr_variable(*stm.key, *scp_iter);
    emit_expr_variable(*stm.array, *scp_iter);

    if (ctx_->props() & props::farcall)
        emit_opcode(opcode::OP_CallBuiltin, { "getnextarraykey"s, "2"s });
    else
        emit_opcode(opcode::OP_CallBuiltin2, "getnextarraykey");

    emit_expr_variable_ref(*stm.key, *scp_iter, true);
    emit_opcode(opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);
    emit_expr_clear_local(stm.array->as<expr_identifier>(), scp);
    if (ctx_->props() & props::foreach || !stm.use_key) emit_expr_clear_local(stm.key->as<expr_identifier>(), scp);

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

    emit_expr(*stm.test, scp);
    emit_opcode(opcode::OP_switch, table_loc);

    can_break_ = true;

    auto data = std::vector<std::string>{};
    data.push_back(std::format("{}", stm.body->block->list.size()));

    auto loc_default = std::string{};
    auto has_default = false;
    scope* default_ctx = nullptr;

    for (auto i = 0u; i < stm.body->block->list.size(); i++)
    {
        auto const& entry = stm.body->block->list[i];

        if (entry->is<stmt_case>())
        {
            data.push_back("case");

            if (entry->as<stmt_case>().value->is<expr_integer>())
            {
                data.push_back(std::format("{}", static_cast<i32>(switch_type::integer)));
                data.push_back(entry->as<stmt_case>().value->as<expr_integer>().value);
                data.push_back(insert_label());
            }
            else if (entry->as<stmt_case>().value->is<expr_string>())
            {
                data.push_back(std::format("{}", static_cast<std::underlying_type_t<switch_type>>(switch_type::string)));
                data.push_back(entry->as<stmt_case>().value->as<expr_string>().value);
                data.push_back(insert_label());
            }
            else
            {
                throw comp_error(entry->loc(), "case type must be int or string");
            }

            auto& scp_body = scopes_.at(entry->as<stmt_case>().body.get());

            scp.transfer(scp_body);
            scp_body->loc_break = break_loc;
            emit_stmt_list(*entry->as<stmt_case>().body, *scp_body, false);

            if (entry->as<stmt_case>().body->list.size() > 0)
                emit_remove_local_vars(*scp_body);
        }
        else if (entry->is<stmt_default>())
        {
            loc_default = insert_label();
            has_default = true;

            auto& scp_body = scopes_.at(entry->as<stmt_default>().body.get());

            default_ctx = scp_body.get();

            scp.transfer(scp_body);
            scp_body->loc_break = break_loc;
            emit_stmt_list(*entry->as<stmt_default>().body, *scp_body, false);

            if (entry->as<stmt_default>().body->list.size() > 0)
                emit_remove_local_vars(*scp_body);
        }
        else
        {
            throw comp_error(entry->loc(), "missing case statement");
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
    if (!can_break_ /*|| scp.abort != scope::abort_none*/ || scp.loc_break == "")
        throw comp_error(stm.loc(), "illegal break statement");

    if (scp.abort == scope::abort_none)
    {
        break_blks_.push_back(&scp);
        emit_remove_local_vars(scp);
        scp.abort = scope::abort_break;
    }

    emit_opcode(opcode::OP_jump, scp.loc_break);
}

auto compiler::emit_stmt_continue(stmt_continue const& stm, scope& scp) -> void
{
    if (!can_continue_ /*|| scp.abort != scope::abort_none*/ || scp.loc_cont == "")
        throw comp_error(stm.loc(), "illegal continue statement");

    if (scp.abort == scope::abort_none)
    {
        continue_blks_.push_back(&scp);
        emit_remove_local_vars(scp);
        scp.abort = scope::abort_continue;
    }

    emit_opcode(opcode::OP_jump, scp.loc_cont);
}

auto compiler::emit_stmt_return(stmt_return const& stm, scope& scp) -> void
{
    if (scp.abort == scope::abort_none)
        scp.abort = scope::abort_return;

    if (!stm.value->is<expr_empty>())
    {
        emit_expr(*stm.value, scp);
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
    debug_pos_ = { exp.loc().begin.line, exp.loc().begin.column };

    switch (exp.kind())
    {
        case node::expr_paren:
            emit_expr(*exp.as<expr_paren>().value, scp);
            break;
        case node::expr_ternary:
            emit_expr_ternary(exp.as<expr_ternary>(), scp);
            break;
        case node::expr_binary:
            emit_expr_binary(exp.as<expr_binary>(), scp);
            break;
        case node::expr_complement:
            emit_expr_complement(exp.as<expr_complement>(), scp);
            break;
        case node::expr_negate:
            emit_expr_negate(exp.as<expr_negate>(), scp);
            break;
        case node::expr_not:
            emit_expr_not(exp.as<expr_not>(), scp);
            break;
        case node::expr_call:
            emit_expr_call(exp.as<expr_call>(), scp, false);
            break;
        case node::expr_method:
            emit_expr_method(exp.as<expr_method>(), scp, false);
            break;
        case node::expr_isdefined:
            emit_expr_isdefined(exp.as<expr_isdefined>(), scp);
            break;
        case node::expr_istrue:
            emit_expr_istrue(exp.as<expr_istrue>(), scp);
            break;
        case node::expr_reference:
            emit_expr_reference(exp.as<expr_reference>(), scp);
            break;
        case node::expr_add_array:
            emit_expr_add_array(exp.as<expr_add_array>(), scp);
            break;
        case node::expr_array:
            emit_expr_array(exp.as<expr_array>(), scp);
            break;
        case node::expr_field:
            emit_expr_field(exp.as<expr_field>(), scp);
            break;
        case node::expr_size:
            emit_expr_size(exp.as<expr_size>(), scp);
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
            emit_expr_animation(exp.as<expr_animation>());
            break;
        case node::expr_animtree:
            emit_expr_animtree(exp.as<expr_animtree>());
            break;
        case node::expr_identifier:
            emit_expr_local(exp.as<expr_identifier>(), scp);
            break;
        case node::expr_istring:
            emit_expr_istring(exp.as<expr_istring>());
            break;
        case node::expr_string:
            emit_expr_string(exp.as<expr_string>());
            break;
        case node::expr_vector:
            emit_expr_vector(exp.as<expr_vector>(), scp);
            break;
        case node::expr_float:
            emit_expr_float(exp.as<expr_float>());
            break;
        case node::expr_integer:
            emit_expr_integer(exp.as<expr_integer>());
            break;
        case node::expr_false:
            emit_expr_false(exp.as<expr_false>());
            break;
        case node::expr_true:
            emit_expr_true(exp.as<expr_true>());
            break;
        case node::expr_empty:
            break;
        default:
            throw comp_error(exp.loc(), "unknown expression");
    }
}

auto compiler::emit_expr_assign(expr_assign const& exp, scope& scp) -> void
{
    if (exp.oper == expr_assign::op::eq)
    {
        if (exp.rvalue->is<expr_undefined>())
        {
            emit_expr_clear(*exp.lvalue, scp);
        }
        else if (exp.lvalue->is<expr_tuple>())
        {
            emit_expr(*exp.rvalue, scp);
            emit_expr_tuple(exp.lvalue->as<expr_tuple>(), scp);
        }
        else
        {
            emit_expr(*exp.rvalue, scp);
            emit_expr_variable_ref(*exp.lvalue, scp, true);
        }

        return;
    }

    emit_expr(*exp.lvalue, scp);
    emit_expr(*exp.rvalue, scp);

    switch (exp.oper)
    {
        case expr_assign::op::add:
            emit_opcode(opcode::OP_plus);
            break;
        case expr_assign::op::sub:
            emit_opcode(opcode::OP_minus);
            break;
        case expr_assign::op::mul:
            emit_opcode(opcode::OP_multiply);
            break;
        case expr_assign::op::div:
            emit_opcode(opcode::OP_divide);
            break;
        case expr_assign::op::mod:
            emit_opcode(opcode::OP_mod);
            break;
        case expr_assign::op::shl:
            emit_opcode(opcode::OP_shift_left);
            break;
        case expr_assign::op::shr:
            emit_opcode(opcode::OP_shift_right);
            break;
        case expr_assign::op::bwor:
            emit_opcode(opcode::OP_bit_or);
            break;
        case expr_assign::op::bwand:
            emit_opcode(opcode::OP_bit_and);
            break;
        case expr_assign::op::bwexor:
            emit_opcode(opcode::OP_bit_ex_or);
            break;
        default:
            throw comp_error(exp.loc(), "unknown assign operation");
    }

    emit_expr_variable_ref(*exp.lvalue, scp, true);
}

auto compiler::emit_expr_clear(expr const& exp, scope& scp) -> void
{
    switch (exp.kind())
    {
        case node::expr_array:
            emit_expr(*exp.as<expr_array>().key, scp);
            exp.as<expr_array>().obj->is<expr_game>() ? emit_opcode(opcode::OP_GetGameRef) : emit_expr_variable_ref(*exp.as<expr_array>().obj, scp, false);
            emit_opcode(opcode::OP_ClearArray);
            break;
        case node::expr_field:
            emit_expr_object(*exp.as<expr_field>().obj, scp);
            emit_opcode(opcode::OP_ClearFieldVariable, exp.as<expr_field>().field->value);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_GetUndefined);
            emit_expr_local_ref(exp.as<expr_identifier>(), scp, true);
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
        emit_opcode(opcode::OP_ClearLocalVariableFieldCached, std::format("{}", index));
}

auto compiler::emit_expr_increment(expr_increment const& exp, scope& scp, bool is_stmt) -> void
{
    if (is_stmt)
    {
        emit_expr_variable_ref(*exp.lvalue, scp, false);
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
        emit_expr_variable_ref(*exp.lvalue, scp, false);
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

    if (exp.test->is<expr_not>())
    {
        emit_expr(*exp.test->as<expr_not>().rvalue, scp);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(*exp.test, scp);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    emit_expr(*exp.true_expr, scp);
    emit_opcode(opcode::OP_jump, end_loc);

    insert_label(else_loc);
    emit_expr(*exp.false_expr, scp);
    insert_label(end_loc);
}

auto compiler::emit_expr_binary(expr_binary const& exp, scope& scp) -> void
{
    if (exp.oper == expr_binary::op::bool_and)
    {
        auto label = create_label();

        emit_expr(*exp.lvalue, scp);
        emit_opcode(opcode::OP_JumpOnFalseExpr, label);

        if (exp.rvalue->is<expr_not>() && (ctx_->props() & props::boolnotand))
        {
            emit_expr(*exp.rvalue->as<expr_not>().rvalue, scp);
            emit_opcode(opcode::OP_BoolNotAfterAnd);
        }
        else
        {
            emit_expr(*exp.rvalue, scp);
            emit_opcode(opcode::OP_CastBool);
        }

        insert_label(label);
    }
    else if (exp.oper == expr_binary::op::bool_or)
    {
        auto label = create_label();

        emit_expr(*exp.lvalue, scp);
        emit_opcode(opcode::OP_JumpOnTrueExpr, label);

        if (exp.rvalue->is<expr_not>() && (ctx_->props() & props::boolnotand))
        {
            emit_expr(*exp.rvalue->as<expr_not>().rvalue, scp);
            emit_opcode(opcode::OP_BoolNotAfterAnd);
        }
        else
        {
            emit_expr(*exp.rvalue, scp);
            emit_opcode(opcode::OP_CastBool);
        }

        insert_label(label);
    }
    else
    {
        emit_expr(*exp.lvalue, scp);
        emit_expr(*exp.rvalue, scp);

        switch (exp.oper)
        {
            case expr_binary::op::eq:
                emit_opcode(opcode::OP_equality);
                break;
            case expr_binary::op::ne:
                emit_opcode(opcode::OP_inequality);
                break;
            case expr_binary::op::lt:
                emit_opcode(opcode::OP_less);
                break;
            case expr_binary::op::gt:
                emit_opcode(opcode::OP_greater);
                break;
            case expr_binary::op::le:
                emit_opcode(opcode::OP_less_equal);
                break;
            case expr_binary::op::ge:
                emit_opcode(opcode::OP_greater_equal);
                break;
            case expr_binary::op::bwor:
                emit_opcode(opcode::OP_bit_or);
                break;
            case expr_binary::op::bwand:
                emit_opcode(opcode::OP_bit_and);
                break;
            case expr_binary::op::bwexor:
                emit_opcode(opcode::OP_bit_ex_or);
                break;
            case expr_binary::op::shl:
                emit_opcode(opcode::OP_shift_left);
                break;
            case expr_binary::op::shr:
                emit_opcode(opcode::OP_shift_right);
                break;
            case expr_binary::op::add:
                emit_opcode(opcode::OP_plus);
                break;
            case expr_binary::op::sub:
                emit_opcode(opcode::OP_minus);
                break;
            case expr_binary::op::mul:
                emit_opcode(opcode::OP_multiply);
                break;
            case expr_binary::op::div:
                emit_opcode(opcode::OP_divide);
                break;
            case expr_binary::op::mod:
                emit_opcode(opcode::OP_mod);
                break;
            default:
                throw comp_error(exp.loc(), "unknown binary expression");
        }
    }
}

auto compiler::emit_expr_complement(expr_complement const& exp, scope& scp) -> void
{
    emit_expr(*exp.rvalue, scp);
    emit_opcode(opcode::OP_BoolComplement);
}

auto compiler::emit_expr_negate(expr_negate const& exp, scope& scp) -> void
{
    emit_opcode(opcode::OP_GetZero);
    emit_expr(*exp.rvalue, scp);
    emit_opcode(opcode::OP_minus);
}

auto compiler::emit_expr_not(expr_not const& exp, scope& scp) -> void
{
    emit_expr(*exp.rvalue, scp);
    emit_opcode(opcode::OP_BoolNot);
}

auto compiler::emit_expr_call(expr_call const& exp, scope& scp, bool is_stmt) -> void
{
    if (exp.value->is<expr_pointer>())
        emit_expr_call_pointer(exp.value->as<expr_pointer>(), scp, is_stmt);
    else if (exp.value->is<expr_function>())
        emit_expr_call_function(exp.value->as<expr_function>(), scp, is_stmt);
    else
        throw comp_error(exp.loc(), "unknown function call expression");
}

auto compiler::emit_expr_call_pointer(expr_pointer const& exp, scope& scp, bool is_stmt) -> void
{
    if (exp.mode == call::mode::normal)
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(*exp.args, scp);
    emit_expr(*exp.func, scp);

    auto argcount = std::format("{}", exp.args->list.size());

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

    auto argcount = std::format("{}", exp.args->list.size());

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
    if (exp.value->is<expr_pointer>())
        emit_expr_method_pointer(exp.value->as<expr_pointer>(), *exp.obj, scp, is_stmt);
    else if (exp.value->is<expr_function>())
        emit_expr_method_function(exp.value->as<expr_function>(), *exp.obj, scp, is_stmt);
    else
        throw comp_error(exp.loc(), "unknown method call expression");
}

auto compiler::emit_expr_method_pointer(expr_pointer const& exp, expr const& obj, scope& scp, bool is_stmt) -> void
{
    if (exp.mode == call::mode::normal)
        emit_opcode(opcode::OP_PreScriptCall);

    emit_expr_arguments(*exp.args, scp);
    emit_expr(obj, scp);
    emit_expr(*exp.func, scp);

    auto argcount = std::format("{}", exp.args->list.size());

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

    auto argcount = std::format("{}", exp.args->list.size());

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
        emit_expr(*arg, scp);
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

            data.push_back(std::format("{}", num));

            for (auto const& entry : exp.list)
            {
                auto index = variable_initialize(*entry, scp);
                data.push_back((ctx_->props() & props::hash) ? entry->value : std::format("{}", index));
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
            if (!variable_initialized(*entry, scp))
            {
                emit_opcode(opcode::OP_SafeCreateVariableFieldCached, std::format("{}", variable_initialize(*entry, scp)));
            }
            else
            {
                auto index = variable_access(*entry, scp);

                if (index == 0)
                    emit_opcode(opcode::OP_SafeSetVariableFieldCached0);
                else
                    emit_opcode(opcode::OP_SafeSetVariableFieldCached, std::format("{}", index));
            }
        }

        emit_opcode(opcode::OP_checkclearparams);
    }
}

auto compiler::emit_expr_arguments(expr_arguments const& exp, scope& scp) -> void
{
    for (auto it = exp.list.rbegin(); it != exp.list.rend(); ++it)
    {
        emit_expr(**it, scp);
    }
}

auto compiler::emit_expr_isdefined(expr_isdefined const& exp, scope& scp) -> void
{
    emit_expr(*exp.value, scp);
    emit_opcode(opcode::OP_IsDefined);
}

auto compiler::emit_expr_istrue(expr_istrue const& exp, scope& scp) -> void
{
    emit_expr(*exp.value, scp);
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
    emit_expr(*exp.obj, scp);
    emit_opcode(opcode::OP_size);
}

auto compiler::emit_expr_tuple(expr_tuple const& exp, scope& scp) -> void
{
    emit_expr_variable_ref(*exp.temp, scp, true);

    auto index = 0u;

    for (auto const& entry : exp.list)
    {
        if (index == 0)
            emit_opcode(opcode::OP_GetZero);
        else
            emit_opcode(opcode::OP_GetByte, std::format("{}", index));

        index++;

        emit_opcode(opcode::OP_EvalLocalArrayCached, std::format("{}", variable_access(exp.temp->as<expr_identifier>(), scp)));

        emit_expr_variable_ref(*entry, scp, true);
    }

    emit_expr_clear_local(exp.temp->as<expr_identifier>(), scp);
}

auto compiler::emit_expr_variable_ref(expr const& exp, scope& scp, bool set) -> void
{
    switch (exp.kind())
    {
        case node::expr_array:
            emit_expr_array_ref(exp.as<expr_array>(), scp, set);
            break;
        case node::expr_field:
            emit_expr_field_ref(exp.as<expr_field>(), scp, set);
            break;
        case node::expr_identifier:
            emit_expr_local_ref(exp.as<expr_identifier>(), scp, set);
            break;
        default:
            throw comp_error(exp.loc(), "invalid lvalue");
    }
}

auto compiler::emit_expr_array_ref(expr_array const& exp, scope& scp, bool set) -> void
{
    emit_expr(*exp.key, scp);

    switch (exp.obj->kind())
    {
        case node::expr_game:
            emit_opcode(opcode::OP_GetGameRef);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_array:
        case node::expr_field:
            emit_expr_variable_ref(*exp.obj, scp, false);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_identifier:
        {
            if (!variable_initialized(exp.obj->as<expr_identifier>(), scp))
            {
                auto index = variable_initialize(exp.obj->as<expr_identifier>(), scp);
                emit_opcode(opcode::OP_EvalNewLocalArrayRefCached0, (ctx_->props() & props::hash) ? exp.obj->as<expr_identifier>().value : std::format("{}", index));

                // trigger if nested array for lvalue 'var[1][2] = 3;' set is in outer array
                //if (!set) throw comp_error(exp.loc(), "INTERNAL: VAR CREATED BUT NOT SET");
            }
            else
            {
                auto index = variable_access(exp.obj->as<expr_identifier>(), scp);

                if (index == 0)
                    emit_opcode(opcode::OP_EvalLocalArrayRefCached0);
                else
                    emit_opcode(opcode::OP_EvalLocalArrayRefCached, std::format("{}", index));
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

    switch (exp.obj->kind())
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
            emit_expr_array(exp.obj->as<expr_array>(), scp);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_field:
            emit_expr_field(exp.obj->as<expr_field>(), scp);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableObjectCached, std::format("{}", variable_access(exp.obj->as<expr_identifier>(), scp)));
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_call:
            emit_expr_call(exp.obj->as<expr_call>(), scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_method:
            emit_expr_method(exp.obj->as<expr_method>(), scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        default:
            throw comp_error(exp.obj->loc(), "not an object");
    }
}

auto compiler::emit_expr_local_ref(expr_identifier const& exp, scope& scp, bool set) -> void
{
    auto const it = constants_.find(exp.value);

    if (it != constants_.end())
    {
        throw comp_error(exp.loc(), std::format("variable name already defined as constant '{}'", exp.value));
    }

    if (set)
    {
        if (!variable_initialized(exp, scp))
        {
            auto index = variable_initialize(exp, scp);
            emit_opcode(opcode::OP_SetNewLocalVariableFieldCached0, (ctx_->props() & props::hash) ? exp.value : std::format("{}", index));
        }
        else
        {
            auto index = variable_access(exp, scp);

            if (index == 0)
                emit_opcode(opcode::OP_SetLocalVariableFieldCached0);
            else
                emit_opcode(opcode::OP_SetLocalVariableFieldCached, std::format("{}", index));
        }
    }
    else
    {
        auto index = variable_access(exp, scp);

        if (index == 0)
            emit_opcode(opcode::OP_EvalLocalVariableRefCached0);
        else
            emit_opcode(opcode::OP_EvalLocalVariableRefCached, std::format("{}", index));
    }
}

auto compiler::emit_expr_variable(expr const& exp, scope& scp) -> void
{
    switch (exp.kind())
    {
        case node::expr_array:
            emit_expr_array(exp.as<expr_array>(), scp);
            break;
        case node::expr_field:
            emit_expr_field(exp.as<expr_field>(), scp);
            break;
        case node::expr_identifier:
            emit_expr_local(exp.as<expr_identifier>(), scp);
            break;
        default:
            throw comp_error(exp.loc(), "invalid variable type.");
    }
}

auto compiler::emit_expr_array(expr_array const& exp, scope& scp) -> void
{
    emit_expr(*exp.key, scp);

    if (exp.obj->is<expr_identifier>())
    {
        emit_opcode(opcode::OP_EvalLocalArrayCached, std::format("{}", variable_access(exp.obj->as<expr_identifier>(), scp)));
    }
    else
    {
        emit_expr(*exp.obj, scp);
        emit_opcode(opcode::OP_EvalArray);
    }
}

auto compiler::emit_expr_field(expr_field const& exp, scope& scp) -> void
{
    auto const& field = exp.field->value;

    switch (exp.obj->kind())
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
            emit_expr_array(exp.obj->as<expr_array>(), scp);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_field:
            emit_expr_field(exp.obj->as<expr_field>(), scp);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_call:
            emit_expr_call(exp.obj->as<expr_call>(), scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_method:
            emit_expr_method(exp.obj->as<expr_method>(), scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableObjectCached, std::format("{}", variable_access(exp.obj->as<expr_identifier>(), scp)));
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
            emit_opcode(opcode::OP_EvalLocalVariableCached, std::format("{}", index));
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
            emit_expr_array(exp.as<expr_array>(), scp);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_field:
            emit_expr_field(exp.as<expr_field>(), scp);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_call:
            emit_expr_call(exp.as<expr_call>(), scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_method:
            emit_expr_method(exp.as<expr_method>(), scp, false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableObjectCached, std::format("{}", variable_access(exp.as<expr_identifier>(), scp)));
            break;
        default:
            throw comp_error(exp.loc(), "not an object");
    }
}

auto compiler::emit_expr_vector(expr_vector const& exp, scope& scp) -> void
{
    auto data = std::vector<std::string>{};
    auto isexpr = false;

    if (exp.x->is<expr_integer>())
        data.push_back(exp.x->as<expr_integer>().value);
    else if (exp.x->is<expr_float>())
        data.push_back(exp.x->as<expr_float>().value);
    else isexpr = true;

    if (exp.y->is<expr_integer>())
        data.push_back(exp.y->as<expr_integer>().value);
    else if (exp.y->is<expr_float>())
        data.push_back(exp.y->as<expr_float>().value);
    else isexpr = true;

    if (exp.z->is<expr_integer>())
        data.push_back(exp.z->as<expr_integer>().value);
    else if (exp.z->is<expr_float>())
        data.push_back(exp.z->as<expr_float>().value);
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
        emit_expr(*exp.z, scp);
        emit_expr(*exp.y, scp);
        emit_expr(*exp.x, scp);
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
            emit_opcode(opcode::OP_CreateLocalVariable, (ctx_->props() & props::hash) ? scp.vars[i].name : std::format("{}", scp.vars[i].create));
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
            emit_opcode(opcode::OP_RemoveLocalVariables, std::format("{}", count));
        }
    }
}

auto compiler::emit_opcode(opcode op) -> void
{
    function_->instructions.push_back(instruction::make());

    auto& inst = function_->instructions.back();
    inst->opcode = op;
    inst->size = ctx_->opcode_size(op);
    inst->index = index_;
    inst->pos = debug_pos_;

    index_ += inst->size;
}

auto compiler::emit_opcode(opcode op, std::string const& data) -> void
{
    function_->instructions.push_back(instruction::make());

    auto& inst = function_->instructions.back();
    inst->opcode = op;
    inst->size = ctx_->opcode_size(op);
    inst->index = index_;
    inst->data.push_back(data);
    inst->pos = debug_pos_;

    index_ += inst->size;
}

auto compiler::emit_opcode(opcode op, std::vector<std::string> const& data) -> void
{
    function_->instructions.push_back(instruction::make());

    auto& inst = function_->instructions.back();
    inst->opcode = op;
    inst->size = ctx_->opcode_size(op);
    inst->index = index_;
    inst->data = data;
    inst->pos = debug_pos_;

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
            process_stmt_list(stm.as<stmt_list>(), scp);
            break;
        case node::stmt_comp:
            process_stmt_comp(stm.as<stmt_comp>(), scp);
            break;
        case node::stmt_dev:
            process_stmt_dev(stm.as<stmt_dev>(), scp);
            break;
        case node::stmt_expr:
            process_stmt_expr(stm.as<stmt_expr>(), scp);
            break;
        case node::stmt_waittill:
            process_stmt_waittill(stm.as<stmt_waittill>(), scp);
            break;
        case node::stmt_if:
            process_stmt_if(stm.as<stmt_if>(), scp);
            break;
        case node::stmt_ifelse:
            process_stmt_ifelse(stm.as<stmt_ifelse>(), scp);
            break;
        case node::stmt_while:
            process_stmt_while(stm.as<stmt_while>(), scp);
            break;
        case node::stmt_dowhile:
            process_stmt_dowhile(stm.as<stmt_dowhile>(), scp);
            break;
        case node::stmt_for:
            process_stmt_for(stm.as<stmt_for>(), scp);
            break;
        case node::stmt_foreach:
            process_stmt_foreach(stm.as<stmt_foreach>(), scp);
            break;
        case node::stmt_switch:
            process_stmt_switch(stm.as<stmt_switch>(), scp);
            break;
        case node::stmt_break:
            process_stmt_break(stm.as<stmt_break>(), scp);
            break;
        case node::stmt_continue:
            process_stmt_continue(stm.as<stmt_continue>(), scp);
            break;
        case node::stmt_return:
            process_stmt_return(stm.as<stmt_return>(), scp);
            break;
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
        process_stmt(*entry, scp);
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
    switch (stm.value->kind())
    {
        case node::expr_increment:
            process_expr(*stm.value->as<expr_increment>().lvalue, scp);
            break;
        case node::expr_decrement:
            process_expr(*stm.value->as<expr_decrement>().lvalue, scp);
            break;
        case node::expr_assign:
            process_expr(*stm.value->as<expr_assign>().lvalue, scp);
            break;
        case node::expr_call:
        case node::expr_method:
        case node::expr_empty:
            break;
        default:
            throw comp_error(stm.loc(), "unknown expr statement expression");
    }
}

auto compiler::process_stmt_waittill(stmt_waittill const& stm, scope& scp) -> void
{
    for (auto const& entry : stm.args->list)
    {
        if (!entry->is<expr_identifier>())
        {
            throw comp_error(entry->loc(), "illegal waittill param, must be a local variable");
        }

        variable_register(entry->as<expr_identifier>(), scp);
    }
}

auto compiler::process_stmt_if(stmt_if const& stm, scope& scp) -> void
{
    auto ins = scopes_.insert({ stm.body.get(), make_scope() });
    auto& scp_then = ins.first->second;

    scp.copy(scp_then);
    process_stmt(*stm.body, *scp_then);

    std::vector<scope*> childs({ scp_then.get() });
    scp.merge(childs);
}

auto compiler::process_stmt_ifelse(stmt_ifelse const& stm, scope& scp) -> void
{
    auto childs = std::vector<scope*>{};
    auto abort = scope::abort_return;

    auto ins1 = scopes_.insert({ stm.stmt_if.get(), make_scope() });
    auto ins2 = scopes_.insert({ stm.stmt_else.get(), make_scope() });
    auto& scp_then = ins1.first->second;
    auto& scp_else = ins2.first->second;

    scp.copy(scp_then);
    process_stmt(*stm.stmt_if, *scp_then);

    if (scp_then->abort <= scope::abort_return)
    {
        abort = scp_then->abort;
        if (abort == scope::abort_none)
            childs.push_back(scp_then.get());
    }

    scp.copy(scp_else);
    process_stmt(*stm.stmt_else, *scp_else);

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
    bool const_cond = is_constant_condition(*stm.test);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    auto ins = scopes_.insert({ stm.body.get(), make_scope() });
    auto& scp_body = ins.first->second;

    scp.copy(scp_body);
    process_stmt(*stm.body, *scp_body);

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
    bool const_cond = is_constant_condition(*stm.test);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    auto ins = scopes_.insert({ stm.body.get(), make_scope() });
    auto& scp_body = ins.first->second;

    scp.copy(scp_body);
    process_stmt(*stm.body, *scp_body);

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
    bool const_cond = is_constant_condition(*stm.test);

    auto ins1 = scopes_.insert({ stm.body.get(), make_scope() });
    auto ins2 = scopes_.insert({ stm.iter.get(), make_scope() });
    auto& scp_body = ins1.first->second;
    auto& scp_iter = ins2.first->second;

    process_stmt(*stm.init, scp);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    scp.copy(scp_body);
    scp.copy(scp_iter);

    process_stmt(*stm.body, *scp_body);

    continue_blks_.push_back(scp_body.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        scp.append({ continue_blks_.at(i) });

    process_stmt(*stm.iter, *scp_iter);

    scp.append({ scp_iter.get() });
    scp.merge({ scp_iter.get() });

    if (const_cond) scp.append(break_blks_);

    scp.merge({ scp_body.get() });

    break_blks_ = old_breaks;
    continue_blks_ = old_continues;
}

auto compiler::process_stmt_foreach(stmt_foreach const& stm, scope& scp) -> void
{
    auto ins1 = scopes_.insert({ stm.body.get(), make_scope() });
    auto ins2 = scopes_.insert({ stm.key.get(), make_scope() });
    auto& scp_body = ins1.first->second;
    auto& scp_iter = ins2.first->second;

    process_expr(*stm.array, scp);

    if (ctx_->props() & props::foreach)
        process_expr(*stm.key, scp);

    if (ctx_->props() & props::foreach && stm.use_key)
        process_expr(*stm.index, scp);

    auto old_breaks = break_blks_;
    auto old_continues = continue_blks_;
    break_blks_.clear();
    continue_blks_.clear();

    scp.copy(scp_body);
    scp.copy(scp_iter);

    process_expr(*stm.value, *scp_body);
    process_stmt(*stm.body, *scp_body);

    continue_blks_.push_back(scp_body.get());

    for (auto i = 0u; i < continue_blks_.size(); i++)
        scp.append({ continue_blks_.at(i) });

    if (!(ctx_->props() & props::foreach))
        process_expr(*stm.key, *scp_iter);

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

        if (entry->is<stmt_case>())
        {
            auto ins = scopes_.insert({ entry->as<stmt_case>().body.get(), make_scope() });
            auto& scp_body = ins.first->second;

            scp.copy(scp_body);
            process_stmt_list(*entry->as<stmt_case>().body, *scp_body);

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
        else if (entry->is<stmt_default>())
        {
            auto ins = scopes_.insert({ entry->as<stmt_default>().body.get(), make_scope() });
            auto& scp_body = ins.first->second;

            scp.copy(scp_body);
            process_stmt_list(*entry->as<stmt_default>().body, *scp_body);
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
            childs.push_back(default_ctx);

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
    if (exp.is<expr_identifier>())
    {
        variable_register(exp.as<expr_identifier>(), scp);
    }
    else if (exp.is<expr_array>())
    {
        process_expr(*exp.as<expr_array>().obj, scp);
    }
    else if (exp.is<expr_tuple>())
    {
        process_expr_tuple(exp.as<expr_tuple>(), scp);
    }
}

auto compiler::process_expr_tuple(expr_tuple const& exp, scope& scp) -> void
{
    process_expr(*exp.temp, scp);

    for (auto const& entry : exp.list)
    {
        process_expr(*entry, scp);
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

   throw comp_error(exp.loc(), std::format("local variable '{}' not found", exp.value));
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
                        emit_opcode(opcode::OP_CreateLocalVariable, (ctx_->props() & props::hash) ? scp.vars[j].name : std::format("{}", scp.vars[j].create));
                    }
                }

                scp.vars[i].init = true;
                scp.create_count = i + 1;
                return scp.vars[i].create;
            }

            throw comp_error(exp.loc(), std::format("local variable '{}' already initialized", exp.value));
        }
    }

    throw comp_error(exp.loc(), std::format("local variable '{}' not found", exp.value));
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
                emit_opcode(opcode::OP_CreateLocalVariable, (ctx_->props() & props::hash) ? var.name : std::format("{}", var.create));
                var.init = true;
                scp.create_count++;
            }

            return static_cast<u8>(scp.create_count - 1 - i);
        }
    }

    throw comp_error(exp.loc(), std::format("local variable '{}' not found", exp.value));
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

            throw comp_error(exp.loc(), std::format("local variable '{}' not initialized", exp.value));
        }
    }

    throw comp_error(exp.loc(), std::format("local variable '{}' not found", exp.value));
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
        case node::expr_empty:
        case node::expr_true:
            return true;
        case node::expr_false:
            throw comp_error(exp.loc(), "condition can't be always false");
        case node::expr_integer:
        {
            auto num = std::stoi(exp.as<expr_integer>().value);
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
        auto name = std::format("loc_{}", label_idx_);
        function_->labels.insert({ index_, name });
        return name;
    }
}

auto compiler::create_label() -> std::string
{
    label_idx_++;
    return std::format("loc_{}", label_idx_);
}

} // namespace xsk::gsc
