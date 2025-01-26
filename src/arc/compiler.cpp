// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/compiler.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc
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
    developer_thread_ = false;
    animtree_ = {};
    index_ = 0;
    debug_pos_ = { 0, 0 };

    for (auto const& include : prog.includes)
    {
        emit_include(*include);
    }

    for (auto const& dec : prog.declarations)
    {
        if (dec->is<decl_function>())
        {
            auto const& name = dec->as<decl_function>().name->value;

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

auto compiler::emit_include(include const& inc) -> void
{
    auto const& path = inc.path->value;

    for (auto const& entry : assembly_->includes)
    {
        if (entry == path)
        {
            throw comp_error(inc.loc(), std::format("duplicated include file {}", path));
        }
    }

    assembly_->includes.push_back(path);
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

    animtree_ = animtree.name->value;
}

auto compiler::emit_decl_function(decl_function const& func) -> void
{
    label_idx_ = 0;
    can_break_ = false;
    can_continue_ = false;
    scopes_.clear();
    constants_.clear();
    stackframe_.clear();

    function_ = function::make();
    function_->index = index_;
    function_->name = func.name->value;
    function_->params = static_cast<u8>(func.params->list.size());
    function_->flags = static_cast<u8>(func.flags);

    process_function(func);

    scopes_.push_back(scope());

    emit_expr_parameters(*func.params);
    emit_stmt_comp(*func.body);

    if (scopes_.back().abort == scope::abort_none || function_->labels.find(index_) != function_->labels.end())
        emit_opcode(opcode::OP_End);

    scopes_.pop_back();

    function_->size = index_ - function_->index;
    assembly_->functions.push_back(std::move(function_));
}

auto compiler::emit_stmt(stmt const& stm) -> void
{
    debug_pos_ = { stm.loc().begin.line, stm.loc().begin.column };

    switch (stm.kind())
    {
        case node::stmt_list:
            emit_stmt_list(stm.as<stmt_list>());
            break;
        case node::stmt_comp:
            emit_stmt_comp(stm.as<stmt_comp>());
            break;
        case node::stmt_dev:
            emit_stmt_dev(stm.as<stmt_dev>());
            break;
        case node::stmt_expr:
            emit_stmt_expr(stm.as<stmt_expr>());
            break;
        case node::stmt_endon:
            emit_stmt_endon(stm.as<stmt_endon>());
            break;
        case node::stmt_notify:
            emit_stmt_notify(stm.as<stmt_notify>());
            break;
        case node::stmt_wait:
            emit_stmt_wait(stm.as<stmt_wait>());
            break;
        case node::stmt_waitrealtime:
            emit_stmt_waitrealtime(stm.as<stmt_waitrealtime>());
            break;
        case node::stmt_waittill:
            emit_stmt_waittill(stm.as<stmt_waittill>());
            break;
        case node::stmt_waittillmatch:
            emit_stmt_waittillmatch(stm.as<stmt_waittillmatch>());
            break;
        case node::stmt_waittillframeend:
            emit_stmt_waittillframeend(stm.as<stmt_waittillframeend>());
            break;
        case node::stmt_if:
            emit_stmt_if(stm.as<stmt_if>());
            break;
        case node::stmt_ifelse:
            emit_stmt_ifelse(stm.as<stmt_ifelse>());
            break;
        case node::stmt_while:
            emit_stmt_while(stm.as<stmt_while>());
            break;
        case node::stmt_dowhile:
            emit_stmt_dowhile(stm.as<stmt_dowhile>());
            break;
        case node::stmt_for:
            emit_stmt_for(stm.as<stmt_for>());
            break;
        case node::stmt_foreach:
            emit_stmt_foreach(stm.as<stmt_foreach>());
            break;
        case node::stmt_switch:
            emit_stmt_switch(stm.as<stmt_switch>());
            break;
        case node::stmt_case:
            emit_stmt_case(stm.as<stmt_case>());
            break;
        case node::stmt_default:
            emit_stmt_default(stm.as<stmt_default>());
            break;
        case node::stmt_break:
            emit_stmt_break(stm.as<stmt_break>());
            break;
        case node::stmt_continue:
            emit_stmt_continue(stm.as<stmt_continue>());
            break;
        case node::stmt_return:
            emit_stmt_return(stm.as<stmt_return>());
            break;
        case node::stmt_breakpoint:
            emit_stmt_breakpoint(stm.as<stmt_breakpoint>());
            break;
        case node::stmt_prof_begin:
            emit_stmt_prof_begin(stm.as<stmt_prof_begin>());
            break;
        case node::stmt_prof_end:
            emit_stmt_prof_end(stm.as<stmt_prof_end>());
            break;
        default:
            throw comp_error(stm.loc(), "unknown statement");
    }
}

auto compiler::emit_stmt_list(stmt_list const& stm) -> void
{
    for (auto const& entry : stm.list)
    {
        emit_stmt(*entry);
    }
}

auto compiler::emit_stmt_comp(stmt_comp const& stm) -> void
{
    emit_stmt_list(*stm.block);
}

auto compiler::emit_stmt_dev(stmt_dev const& stm) -> void
{
    auto end = create_label();
    developer_thread_ = true;
    emit_opcode(opcode::OP_DevblockBegin, end);

    auto& paren = scopes_.back();
    scopes_.push_back(scope(paren.brk, paren.cnt));
    emit_stmt_list(*stm.block);
    scopes_.pop_back();

    insert_label(end);
    developer_thread_ = false;
}

auto compiler::emit_stmt_expr(stmt_expr const& stm) -> void
{
    switch (stm.value->kind())
    {
        case node::expr_increment:
            emit_expr_increment(stm.value->as<expr_increment>(), true);
            break;
        case node::expr_decrement:
            emit_expr_decrement(stm.value->as<expr_decrement>(), true);
            break;
        case node::expr_assign:
            emit_expr_assign(stm.value->as<expr_assign>());
            break;
        case node::expr_call:
            emit_expr_call(stm.value->as<expr_call>(), true);
            break;
        case node::expr_method:
            emit_expr_method(stm.value->as<expr_method>(), true);
            break;
        case node::expr_const:
            emit_expr_const(stm.value->as<expr_const>());
            break;
        case node::expr_empty:
            break;
        default:
            throw comp_error(stm.loc(), "unknown expr statement expression");
    }
}

auto compiler::emit_stmt_endon(stmt_endon const& stm) -> void
{
    emit_expr(*stm.event);
    emit_expr(*stm.obj);
    emit_opcode(opcode::OP_EndOn);
}

auto compiler::emit_stmt_notify(stmt_notify const& stm) -> void
{
    emit_opcode(opcode::OP_VoidCodePos);

    for (auto it = stm.args->list.rbegin(); it != stm.args->list.rend(); it++)
    {
        emit_expr(**it);
    }

    emit_expr(*stm.event);
    emit_expr(*stm.obj);
    emit_opcode(opcode::OP_Notify);
}

auto compiler::emit_stmt_wait(stmt_wait const& stm) -> void
{
    emit_expr(*stm.time);
    emit_opcode(opcode::OP_Wait);
}

auto compiler::emit_stmt_waitrealtime(stmt_waitrealtime const& stm) -> void
{
    emit_expr(*stm.time);
    emit_opcode(opcode::OP_RealWait);
}

auto compiler::emit_stmt_waittill(stmt_waittill const& stm) -> void
{
    emit_expr(*stm.event);
    emit_expr(*stm.obj);
    emit_opcode(opcode::OP_WaitTill);

    for (auto const& entry : stm.args->list)
    {
        if (entry->is<expr_undefined>())
            emit_opcode(opcode::OP_SafeDecTop);
        else
            emit_opcode(opcode::OP_SafeSetWaittillVariableFieldCached, std::format("{}", variable_access(entry->as<expr_identifier>())));
    }

    emit_opcode(opcode::OP_ClearParams);
}

auto compiler::emit_stmt_waittillmatch(stmt_waittillmatch const& stm) -> void
{
    emit_expr_arguments(*stm.args);
    emit_expr(*stm.event);
    emit_expr(*stm.obj);
    emit_opcode(opcode::OP_WaitTillMatch, std::format("{}", stm.args->list.size()));
    emit_opcode(opcode::OP_ClearParams);
}

auto compiler::emit_stmt_waittillframeend(stmt_waittillframeend const&) -> void
{
    emit_opcode(opcode::OP_WaitTillFrameEnd);
}

auto compiler::emit_stmt_if(stmt_if const& stm) -> void
{
    auto end_loc = create_label();

    if (stm.test->is<expr_not>())
    {
        emit_expr(*stm.test->as<expr_not>().rvalue);
        emit_opcode(opcode::OP_JumpOnTrue, end_loc);
    }
    else
    {
        emit_expr(*stm.test);
        emit_opcode(opcode::OP_JumpOnFalse, end_loc);
    }

    auto& paren = scopes_.back();
    scopes_.push_back(scope(paren.brk, paren.cnt));

    emit_stmt(*stm.body);

    scopes_.pop_back();

    insert_label(end_loc);
}

auto compiler::emit_stmt_ifelse(stmt_ifelse const& stm) -> void
{
    auto else_loc = create_label();
    auto end_loc = create_label();

    if (stm.test->is<expr_not>())
    {
        emit_expr(*stm.test->as<expr_not>().rvalue);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(*stm.test);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    auto& paren = scopes_.back();
    scopes_.push_back(scope(paren.brk, paren.cnt));
    emit_stmt(*stm.stmt_if);
    scopes_.pop_back();

    emit_opcode(opcode::OP_Jump, end_loc);

    insert_label(else_loc);

    auto& paren2 = scopes_.back();
    scopes_.push_back(scope(paren2.brk, paren2.cnt));
    emit_stmt(*stm.stmt_else);
    scopes_.pop_back();

    insert_label(end_loc);
}

auto compiler::emit_stmt_while(stmt_while const& stm) -> void
{
    auto break_loc = create_label();
    auto continue_loc = insert_label();
    auto old_break = can_break_;
    auto old_continue = can_continue_;
    can_break_ = true;
    can_continue_ = true;

    if (stm.test->is<expr_not>())
    {
        emit_expr(*stm.test->as<expr_not>().rvalue);
        emit_opcode(opcode::OP_JumpOnTrue, break_loc);
    }
    else
    {
        emit_expr(*stm.test);
        emit_opcode(opcode::OP_JumpOnFalse, break_loc);
    }

    scopes_.push_back(scope(break_loc, continue_loc));
    emit_stmt(*stm.body);
    scopes_.pop_back();

    emit_opcode(opcode::OP_Jump, continue_loc);
    insert_label(break_loc);

    can_break_ = old_break;
    can_continue_ = old_continue;
}

auto compiler::emit_stmt_dowhile(stmt_dowhile const& stm) -> void
{
    auto old_break = can_break_;
    auto old_continue = can_continue_;
    can_break_ = true;
    can_continue_ = true;

    auto break_loc = create_label();
    auto continue_loc = create_label();
    auto begin_loc = insert_label();

    scopes_.push_back(scope(break_loc, continue_loc));
    emit_stmt(*stm.body);
    scopes_.pop_back();

    insert_label(continue_loc);

    if (stm.test->is<expr_not>())
    {
        emit_expr(*stm.test->as<expr_not>().rvalue);
        emit_opcode(opcode::OP_JumpOnFalse, begin_loc);
    }
    else
    {
        emit_expr(*stm.test);
        emit_opcode(opcode::OP_JumpOnTrue, begin_loc);
    }

    insert_label(break_loc);

    can_break_ = old_break;
    can_continue_ = old_continue;
}

auto compiler::emit_stmt_for(stmt_for const& stm) -> void
{
    auto old_break = can_break_;
    auto old_continue = can_continue_;

    emit_stmt(*stm.init);

    auto break_loc = create_label();
    auto continue_loc = create_label();

    auto begin_loc = insert_label();

    bool const_cond = is_constant_condition(*stm.test);

    if (!const_cond)
    {
        emit_expr(*stm.test);
        emit_opcode(opcode::OP_JumpOnFalse, break_loc);
    }

    can_break_ = true;
    can_continue_ = true;

    scopes_.push_back(scope(break_loc, continue_loc));
    emit_stmt(*stm.body);
    scopes_.pop_back();

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);
    emit_stmt(*stm.iter);
    emit_opcode(opcode::OP_Jump, begin_loc);
    insert_label(break_loc);

    can_break_ = old_break;
    can_continue_ = old_continue;
}

auto compiler::emit_stmt_foreach(stmt_foreach const& stm) -> void
{
    auto old_break = can_break_;
    auto old_continue = can_continue_;

    emit_expr(*stm.container);
    emit_expr_variable_ref(*stm.array, true);
    emit_expr_variable(*stm.array);
    emit_opcode(opcode::OP_FirstArrayKey);
    emit_expr_variable_ref(*stm.key, true);

    auto break_loc = create_label();
    auto continue_loc = create_label();
    auto begin_loc = insert_label();

    emit_expr_variable(*stm.key);
    emit_opcode(opcode::OP_IsDefined);
    emit_opcode(opcode::OP_JumpOnFalse, break_loc);

    can_break_ = true;
    can_continue_ = true;

    emit_expr_variable(*stm.key);
    emit_opcode(opcode::OP_EvalLocalVariableCached, std::format("{}", variable_access(stm.array->as<expr_identifier>())));
    emit_opcode(opcode::OP_EvalArray);
    emit_expr_variable_ref(*stm.value, true);

    scopes_.push_back(scope(break_loc, continue_loc));
    emit_stmt(*stm.body);
    scopes_.pop_back();

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);

    emit_expr_variable(*stm.key);
    emit_expr_variable(*stm.array);
    emit_opcode(opcode::OP_NextArrayKey);
    emit_expr_variable_ref(*stm.key, true);
    emit_opcode(opcode::OP_Jump, begin_loc);
    insert_label(break_loc);

    can_break_ = old_break;
    can_continue_ = old_continue;
}

auto compiler::emit_stmt_switch(stmt_switch const& stm) -> void
{
    auto old_break = can_break_;
    can_break_ = false;

    auto table_loc = create_label();
    auto break_loc = create_label();

    emit_expr(*stm.test);
    emit_opcode(opcode::OP_Switch, table_loc);

    can_break_ = true;

    auto data = std::vector<std::string>{};
    data.push_back(std::format("{}", stm.body->block->list.size()));

    auto loc_default = std::string{};
    auto has_default = false;

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
                data.push_back(std::format("{}", static_cast<i32>(switch_type::string)));
                data.push_back(entry->as<stmt_case>().value->as<expr_string>().value);
                data.push_back(insert_label());
            }
            else
            {
                throw comp_error(entry->loc(), "case type must be int or string");
            }

            auto& paren = scopes_.back();
            scopes_.push_back(scope(break_loc, paren.cnt));
            emit_stmt_list(*entry->as<stmt_case>().body);
            scopes_.pop_back();
        }
        else if (entry->is<stmt_default>())
        {
            loc_default = insert_label();
            has_default = true;

            auto& paren = scopes_.back();
            scopes_.push_back(scope(break_loc, paren.cnt));
            emit_stmt_list(*entry->as<stmt_default>().body);
            scopes_.pop_back();
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
    }

    insert_label(table_loc);
    emit_opcode(opcode::OP_EndSwitch, data);
    insert_label(break_loc);

    can_break_ = old_break;
}

auto compiler::emit_stmt_case(stmt_case const& stm) -> void
{
    throw comp_error(stm.loc(), "illegal case statement");
}

auto compiler::emit_stmt_default(stmt_default const& stm) -> void
{
    throw comp_error(stm.loc(), "illegal default statement");
}

auto compiler::emit_stmt_break(stmt_break const& stm) -> void
{
    if (!can_break_ /*|| scopes_.back().abort != scope::abort_none*/ || scopes_.back().brk == "")
        throw comp_error(stm.loc(), "illegal break statement");

    if (scopes_.back().abort == scope::abort_none)
        scopes_.back().abort = scope::abort_break;

    emit_opcode(opcode::OP_Jump, scopes_.back().brk);
}

auto compiler::emit_stmt_continue(stmt_continue const& stm) -> void
{
    if (!can_continue_ /*|| scopes_.back().abort != scope::abort_none*/ || scopes_.back().cnt == "")
        throw comp_error(stm.loc(), "illegal continue statement");

    if (scopes_.back().abort == scope::abort_none)
        scopes_.back().abort = scope::abort_continue;

    emit_opcode(opcode::OP_Jump, scopes_.back().cnt);
}

auto compiler::emit_stmt_return(stmt_return const& stm) -> void
{
    if (scopes_.back().abort == scope::abort_none)
        scopes_.back().abort = scope::abort_return;

    if (!stm.value->is<expr_empty>())
    {
        emit_expr(*stm.value);
        emit_opcode(opcode::OP_Return);
    }
    else
        emit_opcode(opcode::OP_End);
}

auto compiler::emit_stmt_breakpoint(stmt_breakpoint const&) -> void
{
    // TODO:
}

auto compiler::emit_stmt_prof_begin(stmt_prof_begin const&) -> void
{
    // TODO:
}

auto compiler::emit_stmt_prof_end(stmt_prof_end const&) -> void
{
    // TODO:
}

auto compiler::emit_expr(expr const& exp) -> void
{
    debug_pos_ = { exp.loc().begin.line, exp.loc().begin.column };

    switch (exp.kind())
    {
        case node::expr_paren:
            emit_expr(*exp.as<expr_paren>().value);
            break;
        case node::expr_ternary:
            emit_expr_ternary(exp.as<expr_ternary>());
            break;
        case node::expr_binary:
            emit_expr_binary(exp.as<expr_binary>());
            break;
        case node::expr_complement:
            emit_expr_complement(exp.as<expr_complement>());
            break;
        case node::expr_negate:
            emit_expr_negate(exp.as<expr_negate>());
            break;
        case node::expr_not:
            emit_expr_not(exp.as<expr_not>());
            break;
        case node::expr_call:
            emit_expr_call(exp.as<expr_call>(), false);
            break;
        case node::expr_method:
            emit_expr_method(exp.as<expr_method>(), false);
            break;
        case node::expr_isdefined:
            emit_expr_isdefined(exp.as<expr_isdefined>());
            break;
        case node::expr_vectorscale:
            emit_expr_vectorscale(exp.as<expr_vectorscale>());
            break;
        case node::expr_anglestoup:
            emit_expr_anglestoup(exp.as<expr_anglestoup>());
            break;
        case node::expr_anglestoright:
            emit_expr_anglestoright(exp.as<expr_anglestoright>());
            break;
        case node::expr_anglestoforward:
            emit_expr_anglestoforward(exp.as<expr_anglestoforward>());
            break;
        case node::expr_angleclamp180:
            emit_expr_angleclamp180(exp.as<expr_angleclamp180>());
            break;
        case node::expr_vectortoangles:
            emit_expr_vectortoangles(exp.as<expr_vectortoangles>());
            break;
        case node::expr_abs:
            emit_expr_abs(exp.as<expr_abs>());
            break;
        case node::expr_gettime:
            emit_expr_gettime(exp.as<expr_gettime>());
            break;
        case node::expr_getdvar:
            emit_expr_getdvar(exp.as<expr_getdvar>());
            break;
        case node::expr_getdvarint:
            emit_expr_getdvarint(exp.as<expr_getdvarint>());
            break;
        case node::expr_getdvarfloat:
            emit_expr_getdvarfloat(exp.as<expr_getdvarfloat>());
            break;
        case node::expr_getdvarvector:
            emit_expr_getdvarvector(exp.as<expr_getdvarvector>());
            break;
        case node::expr_getdvarcolorred:
            emit_expr_getdvarcolorred(exp.as<expr_getdvarcolorred>());
            break;
        case node::expr_getdvarcolorgreen:
            emit_expr_getdvarcolorgreen(exp.as<expr_getdvarcolorgreen>());
            break;
        case node::expr_getdvarcolorblue:
            emit_expr_getdvarcolorblue(exp.as<expr_getdvarcolorblue>());
            break;
        case node::expr_getdvarcoloralpha:
            emit_expr_getdvarcoloralpha(exp.as<expr_getdvarcoloralpha>());
            break;
        case node::expr_getfirstarraykey:
            emit_expr_getfirstarraykey(exp.as<expr_getfirstarraykey>());
            break;
        case node::expr_getnextarraykey:
            emit_expr_getnextarraykey(exp.as<expr_getnextarraykey>());
            break;
        case node::expr_reference:
            emit_expr_reference(exp.as<expr_reference>());
            break;
        case node::expr_array:
            emit_expr_array(exp.as<expr_array>());
            break;
        case node::expr_field:
            emit_expr_field(exp.as<expr_field>());
            break;
        case node::expr_size:
            emit_expr_size(exp.as<expr_size>());
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
            emit_expr_local(exp.as<expr_identifier>());
            break;
        case node::expr_istring:
            emit_expr_istring(exp.as<expr_istring>());
            break;
        case node::expr_string:
            emit_expr_string(exp.as<expr_string>());
            break;
        case node::expr_vector:
            emit_expr_vector(exp.as<expr_vector>());
            break;
        case node::expr_hash:
            emit_expr_hash(exp.as<expr_hash>());
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

auto compiler::emit_expr_const(expr_const const& exp) -> void
{
    auto const itr = constants_.find(exp.lvalue->value);

    if (itr != constants_.end())
        throw comp_error(exp.loc(), std::format("duplicated constant '{}'", exp.lvalue->value));

    if (std::find(stackframe_.begin(), stackframe_.end(), exp.lvalue->value) != stackframe_.end())
        throw comp_error(exp.loc(), std::format("constant already defined as local variable '{}'", exp.lvalue->value));

    constants_.insert({ exp.lvalue->value, exp.rvalue.get() });
}

auto compiler::emit_expr_assign(expr_assign const& exp) -> void
{
    if (exp.oper == expr_assign::op::eq)
    {
        if (exp.rvalue->is<expr_undefined>())
        {
            emit_expr_clear(*exp.lvalue);
        }
        else
        {
            emit_expr(*exp.rvalue);
            emit_expr_variable_ref(*exp.lvalue, true);
        }

        return;
    }

    emit_expr(*exp.lvalue);
    emit_expr(*exp.rvalue);

    switch (exp.oper)
    {
        case expr_assign::op::add:
            emit_opcode(opcode::OP_Plus);
            break;
        case expr_assign::op::sub:
            emit_opcode(opcode::OP_Minus);
            break;
        case expr_assign::op::mul:
            emit_opcode(opcode::OP_Multiply);
            break;
        case expr_assign::op::div:
            emit_opcode(opcode::OP_Divide);
            break;
        case expr_assign::op::mod:
            emit_opcode(opcode::OP_Modulus);
            break;
        case expr_assign::op::shl:
            emit_opcode(opcode::OP_ShiftLeft);
            break;
        case expr_assign::op::shr:
            emit_opcode(opcode::OP_ShiftRight);
            break;
        case expr_assign::op::bwor:
            emit_opcode(opcode::OP_Bit_Or);
            break;
        case expr_assign::op::bwand:
            emit_opcode(opcode::OP_Bit_And);
            break;
        case expr_assign::op::bwexor:
            emit_opcode(opcode::OP_Bit_Xor);
            break;
        default:
            throw comp_error(exp.loc(), "unknown assign operation");
    }

    emit_expr_variable_ref(*exp.lvalue, true);
}

auto compiler::emit_expr_clear(expr const& exp) -> void
{
    switch (exp.kind())
    {
        case node::expr_array:
            emit_expr(*exp.as<expr_array>().key);
            exp.as<expr_array>().obj->is<expr_game>() ? emit_opcode(opcode::OP_GetGameRef) : emit_expr_variable_ref(*exp.as<expr_array>().obj, false);
            emit_opcode(opcode::OP_ClearArray);
            break;
        case node::expr_field:
            emit_expr_object(*exp.as<expr_field>().obj);
            emit_opcode(opcode::OP_ClearFieldVariable, exp.as<expr_field>().field->value);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_GetUndefined);
            emit_expr_local_ref(exp.as<expr_identifier>(), true);
            break;
        default:
            throw comp_error(exp.loc(), "unknown clear variable lvalue");
    }
}

auto compiler::emit_expr_increment(expr_increment const& exp, bool is_stmt) -> void
{
    if (is_stmt)
    {
        emit_expr_variable_ref(*exp.lvalue, false);
        emit_opcode(opcode::OP_Inc);
    }
    else
    {
        // TODO:
    }
}

auto compiler::emit_expr_decrement(expr_decrement const& exp, bool is_stmt) -> void
{
    if (is_stmt)
    {
        emit_expr_variable_ref(*exp.lvalue, false);
        emit_opcode(opcode::OP_Dec);
    }
    else
    {
        // TODO:
    }
}

auto compiler::emit_expr_ternary(expr_ternary const& exp) -> void
{
    auto else_loc = create_label();
    auto end_loc = create_label();

    if (exp.test->is<expr_not>())
    {
        emit_expr(*exp.test->as<expr_not>().rvalue);
        emit_opcode(opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(*exp.test);
        emit_opcode(opcode::OP_JumpOnFalse, else_loc);
    }

    emit_expr(*exp.true_expr);
    emit_opcode(opcode::OP_Jump, end_loc);

    insert_label(else_loc);
    emit_expr(*exp.false_expr);
    insert_label(end_loc);
}

auto compiler::emit_expr_binary(expr_binary const& exp) -> void
{
    if (exp.oper == expr_binary::op::bool_and)
    {
        auto label = create_label();

        emit_expr(*exp.lvalue);
        emit_opcode(opcode::OP_JumpOnFalseExpr, label);
        emit_expr(*exp.rvalue);

        insert_label(label);
    }
    else if (exp.oper == expr_binary::op::bool_or)
    {
        auto label = create_label();

        emit_expr(*exp.lvalue);
        emit_opcode(opcode::OP_JumpOnTrueExpr, label);
        emit_expr(*exp.rvalue);

        insert_label(label);
    }
    else
    {
        emit_expr(*exp.lvalue);
        emit_expr(*exp.rvalue);

        switch (exp.oper)
        {
            case expr_binary::op::eq:
                emit_opcode(opcode::OP_Equal);
                break;
            case expr_binary::op::ne:
                emit_opcode(opcode::OP_NotEqual);
                break;
            case expr_binary::op::lt:
                emit_opcode(opcode::OP_LessThan);
                break;
            case expr_binary::op::gt:
                emit_opcode(opcode::OP_GreaterThan);
                break;
            case expr_binary::op::le:
                emit_opcode(opcode::OP_LessThanOrEqualTo);
                break;
            case expr_binary::op::ge:
                emit_opcode(opcode::OP_GreaterThanOrEqualTo);
                break;
            case expr_binary::op::bwor:
                emit_opcode(opcode::OP_Bit_Or);
                break;
            case expr_binary::op::bwand:
                emit_opcode(opcode::OP_Bit_And);
                break;
            case expr_binary::op::bwexor:
                emit_opcode(opcode::OP_Bit_Xor);
                break;
            case expr_binary::op::shl:
                emit_opcode(opcode::OP_ShiftLeft);
                break;
            case expr_binary::op::shr:
                emit_opcode(opcode::OP_ShiftRight);
                break;
            case expr_binary::op::add:
                emit_opcode(opcode::OP_Plus);
                break;
            case expr_binary::op::sub:
                emit_opcode(opcode::OP_Minus);
                break;
            case expr_binary::op::mul:
                emit_opcode(opcode::OP_Multiply);
                break;
            case expr_binary::op::div:
                emit_opcode(opcode::OP_Divide);
                break;
            case expr_binary::op::mod:
                emit_opcode(opcode::OP_Modulus);
                break;
            default:
                throw comp_error(exp.loc(), "unknown binary expression");
        }
    }
}

auto compiler::emit_expr_complement(expr_complement const& exp) -> void
{
    emit_expr(*exp.rvalue);
    emit_opcode(opcode::OP_BoolComplement);
}

auto compiler::emit_expr_negate(expr_negate const& exp) -> void
{
    emit_opcode(opcode::OP_GetZero);
    emit_expr(*exp.rvalue);
    emit_opcode(opcode::OP_Minus);
}

auto compiler::emit_expr_not(expr_not const& exp) -> void
{
    emit_expr(*exp.rvalue);
    emit_opcode(opcode::OP_BoolNot);
}

auto compiler::emit_expr_call(expr_call const& exp, bool is_stmt) -> void
{
    if (exp.value->is<expr_pointer>())
        emit_expr_call_pointer(exp.value->as<expr_pointer>(), is_stmt);
    else if (exp.value->is<expr_function>())
        emit_expr_call_function(exp.value->as<expr_function>(), is_stmt);
    else
        throw comp_error(exp.loc(), "unknown function call expression");
}

auto compiler::emit_expr_call_pointer(expr_pointer const& exp, bool is_stmt) -> void
{
    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(*exp.args);
    emit_expr(*exp.func);

    auto argcount = std::format("{}", exp.args->list.size());

    switch (exp.mode)
    {
        case call::mode::normal:
            emit_opcode(opcode::OP_ScriptFunctionCallPointer, argcount);
            break;
        case call::mode::thread:
            emit_opcode(opcode::OP_ScriptThreadCallPointer, argcount);
            break;
        default:
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

auto compiler::emit_expr_call_function(expr_function const& exp, bool is_stmt) -> void
{
    if (exp.path->value != "")
    {
        bool found = false;

        for (const auto& entry : assembly_->includes)
        {
            if (entry == exp.path->value)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            assembly_->includes.push_back(exp.path->value);
        }
    }

    bool as_dev = false;
    std::string end;

    if (!developer_thread_ && is_stmt && (exp.name->value == "assert" || exp.name->value == "assertmsg"))
    {
        as_dev = true;
        developer_thread_ = true;
        end = create_label();
        emit_opcode(opcode::OP_DevblockBegin, end);
    }

    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(*exp.args);

    auto argcount = std::format("{}", exp.args->list.size());
    auto flags = developer_thread_ ? static_cast<u8>(import_flags::developer) : 0;

    switch (exp.mode)
    {
        case call::mode::normal:
            flags |= static_cast<u8>(import_flags::func_call);
            emit_opcode(opcode::OP_ScriptFunctionCall, { exp.path->value, exp.name->value, argcount, std::format("{}", flags) });
            break;
        case call::mode::thread:
            flags |= static_cast<u8>(import_flags::func_call_thread);
            emit_opcode(opcode::OP_ScriptThreadCall, { exp.path->value, exp.name->value, argcount, std::format("{}", flags) });
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

auto compiler::emit_expr_method(expr_method const& exp, bool is_stmt) -> void
{
    if (exp.value->is<expr_pointer>())
        emit_expr_method_pointer(exp.value->as<expr_pointer>(), *exp.obj, is_stmt);
    else if (exp.value->is<expr_function>())
        emit_expr_method_function(exp.value->as<expr_function>(), *exp.obj, is_stmt);
    else
        throw comp_error(exp.loc(), "unknown method call expression");
}

auto compiler::emit_expr_method_pointer(expr_pointer const& exp, expr const& obj, bool is_stmt) -> void
{
    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(*exp.args);
    emit_expr(obj);
    emit_expr(*exp.func);

    auto argcount = std::format("{}", exp.args->list.size());

    switch (exp.mode)
    {
        case call::mode::normal:
            emit_opcode(opcode::OP_ScriptMethodCallPointer, argcount);
            break;
        case call::mode::thread:
            emit_opcode(opcode::OP_ScriptMethodThreadCallPointer, argcount);
            break;
        default:
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

auto compiler::emit_expr_method_function(expr_function const& exp, expr const& obj, bool is_stmt) -> void
{
    if (exp.path->value != "")
    {
        bool found = false;

        for (const auto& entry : assembly_->includes)
        {
            if (entry == exp.path->value)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            assembly_->includes.push_back(exp.path->value);
        }
    }

    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(*exp.args);
    emit_expr(obj);

    auto argcount = std::format("{}", exp.args->list.size());
    auto flags = developer_thread_ ? static_cast<u8>(import_flags::developer) : 0;

    switch (exp.mode)
    {
        case call::mode::normal:
            flags |= static_cast<u8>(import_flags::meth_call);
            emit_opcode(opcode::OP_ScriptMethodCall, { exp.path->value, exp.name->value, argcount, std::format("{}", flags) });
            break;
        case call::mode::thread:
            flags |= static_cast<u8>(import_flags::meth_call_thread);
            emit_opcode(opcode::OP_ScriptMethodThreadCall, { exp.path->value, exp.name->value, argcount, std::format("{}", flags) });
            break;
        default:
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

auto compiler::emit_expr_parameters(expr_parameters const& exp) -> void
{
    if (stackframe_.size() == 0)
    {
        emit_opcode(opcode::OP_CheckClearParams);
    }
    else
    {
        emit_opcode(opcode::OP_SafeCreateLocalVariables, stackframe_);
    }

    for (auto const& entry : exp.list)
    {
        if (entry->is<expr_assign>())
        {
            auto end_loc = create_label();
            emit_expr_variable(*(entry->as<expr_assign>().lvalue));
            emit_opcode(opcode::OP_IsDefined);
            emit_opcode(opcode::OP_JumpOnTrue, end_loc);
            emit_expr(*(entry->as<expr_assign>().rvalue));
            emit_expr_variable_ref(*(entry->as<expr_assign>().lvalue), true);
            insert_label(end_loc);
        }
    }
}

auto compiler::emit_expr_arguments(expr_arguments const& exp) -> void
{
    for (auto it = exp.list.rbegin(); it != exp.list.rend(); ++it)
    {
        emit_expr(**it);
    }
}

auto compiler::emit_expr_isdefined(expr_isdefined const& exp) -> void
{
    emit_expr(*exp.value);
    emit_opcode(opcode::OP_IsDefined);
}

auto compiler::emit_expr_vectorscale(expr_vectorscale const& exp) -> void
{
    emit_expr(*exp.arg2);
    emit_expr(*exp.arg1);
    emit_opcode(opcode::OP_VectorScale);
}

auto compiler::emit_expr_anglestoup(expr_anglestoup const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_AnglesToUp);
}

auto compiler::emit_expr_anglestoright(expr_anglestoright const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_AnglesToRight);
}

auto compiler::emit_expr_anglestoforward(expr_anglestoforward const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_AnglesToForward);
}

auto compiler::emit_expr_angleclamp180(expr_angleclamp180 const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_AngleClamp180);
}

auto compiler::emit_expr_vectortoangles(expr_vectortoangles const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_VectorToAngles);
}

auto compiler::emit_expr_abs(expr_abs const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_Abs);
}

auto compiler::emit_expr_gettime(expr_gettime const&) -> void
{
    emit_opcode(opcode::OP_GetTime);
}

auto compiler::emit_expr_getdvar(expr_getdvar const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_GetDvar);
}

auto compiler::emit_expr_getdvarint(expr_getdvarint const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_GetDvarInt);
}

auto compiler::emit_expr_getdvarfloat(expr_getdvarfloat const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_GetDvarFloat);
}

auto compiler::emit_expr_getdvarvector(expr_getdvarvector const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_GetDvarVector);
}

auto compiler::emit_expr_getdvarcolorred(expr_getdvarcolorred const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_GetDvarColorRed);
}

auto compiler::emit_expr_getdvarcolorgreen(expr_getdvarcolorgreen const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_GetDvarColorGreen);
}

auto compiler::emit_expr_getdvarcolorblue(expr_getdvarcolorblue const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_GetDvarColorBlue);
}

auto compiler::emit_expr_getdvarcoloralpha(expr_getdvarcoloralpha const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_GetDvarColorAlpha);
}

auto compiler::emit_expr_getfirstarraykey(expr_getfirstarraykey const& exp) -> void
{
    emit_expr(*exp.arg);
    emit_opcode(opcode::OP_FirstArrayKey);
}

auto compiler::emit_expr_getnextarraykey(expr_getnextarraykey const& exp) -> void
{
    emit_expr(*exp.arg2);
    emit_expr(*exp.arg1);
    emit_opcode(opcode::OP_NextArrayKey);
}

auto compiler::emit_expr_reference(expr_reference const& exp) -> void
{
    if (exp.path->value != "")
    {
        bool found = false;

        for (const auto& entry : assembly_->includes)
        {
            if (entry == exp.path->value)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            assembly_->includes.push_back(exp.path->value);
        }
    }

    // TODO: resolve import calls path

    auto flags = developer_thread_ ? static_cast<u8>(import_flags::developer) : 0;
    flags |= static_cast<u8>(import_flags::func_reference);

    emit_opcode(opcode::OP_GetFunction, { exp.path->value, exp.name->value, "0", std::format("{}", flags) });
}

auto compiler::emit_expr_size(expr_size const& exp) -> void
{
    emit_expr(*exp.obj);
    emit_opcode(opcode::OP_SizeOf);
}

auto compiler::emit_expr_variable_ref(expr const& exp, bool set) -> void
{
    switch (exp.kind())
    {
        case node::expr_array:
            emit_expr_array_ref(exp.as<expr_array>(), set);
            break;
        case node::expr_field:
            emit_expr_field_ref(exp.as<expr_field>(), set);
            break;
        case node::expr_identifier:
            emit_expr_local_ref(exp.as<expr_identifier>(), set);
            break;
        default:
            throw comp_error(exp.loc(), "invalid lvalue");
    }
}

auto compiler::emit_expr_array_ref(expr_array const& exp, bool set) -> void
{
    emit_expr(*exp.key);

    switch (exp.obj->kind())
    {
        case node::expr_game:
            emit_opcode(opcode::OP_GetGameRef);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_array:
        case node::expr_field:
        case node::expr_identifier:
            emit_expr_variable_ref(*exp.obj, false);
            emit_opcode(opcode::OP_EvalArrayRef);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_call:
        case node::expr_method:
        default:
            throw comp_error(exp.loc(), "invalid array lvalue");
    }
}

auto compiler::emit_expr_field_ref(expr_field const& exp, bool set) -> void
{
    auto const& field = exp.field->value;

    switch (exp.obj->kind())
    {
        case node::expr_level:
            emit_opcode(opcode::OP_GetLevelObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_anim:
            emit_opcode(opcode::OP_GetAnimObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_self:
            emit_opcode(opcode::OP_GetSelfObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_array:
            emit_expr_array(exp.obj->as<expr_array>());
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_field:
            emit_expr_field(exp.obj->as<expr_field>());
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableCached, std::format("{}", variable_access(exp.obj->as<expr_identifier>())));
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_call:
            emit_expr_call(exp.obj->as<expr_call>(), false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        case node::expr_method:
            emit_expr_method(exp.obj->as<expr_method>(), false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariableRef, field);
            if (set) emit_opcode(opcode::OP_SetVariableField);
            break;
        default:
            throw comp_error(exp.obj->loc(), "not an object");
    }
}

auto compiler::emit_expr_local_ref(expr_identifier const& exp, bool set) -> void
{
    auto const it = constants_.find(exp.value);

    if (it != constants_.end())
    {
        throw comp_error(exp.loc(), std::format("variable name already defined as constant '{}'", exp.value));
    }

    emit_opcode(opcode::OP_EvalLocalVariableRefCached, std::format("{}", variable_access(exp)));

    if (set)
    {
        emit_opcode(opcode::OP_SetVariableField);
    }
}

auto compiler::emit_expr_variable(expr const& exp) -> void
{
    switch (exp.kind())
    {
        case node::expr_array:
            emit_expr_array(exp.as<expr_array>());
            break;
        case node::expr_field:
            emit_expr_field(exp.as<expr_field>());
            break;
        case node::expr_identifier:
            emit_expr_local(exp.as<expr_identifier>());
            break;
        default:
            throw comp_error(exp.loc(), "invalid variable type.");
    }
}

auto compiler::emit_expr_array(expr_array const& exp) -> void
{
    emit_expr(*exp.key);
    emit_expr(*exp.obj);
    emit_opcode(opcode::OP_EvalArray);
}

auto compiler::emit_expr_field(expr_field const& exp) -> void
{
    auto const& field = exp.field->value;

    switch (exp.obj->kind())
    {
        case node::expr_level:
            emit_opcode(opcode::OP_GetLevelObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_anim:
            emit_opcode(opcode::OP_GetAnimObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_self:
            emit_opcode(opcode::OP_GetSelfObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_array:
            emit_expr_array(exp.obj->as<expr_array>());
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_field:
            emit_expr_field(exp.obj->as<expr_field>());
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_call:
            emit_expr_call(exp.obj->as<expr_call>(), false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_method:
            emit_expr_method(exp.obj->as<expr_method>(), false);
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableCached, std::format("{}", variable_access(exp.obj->as<expr_identifier>())));
            emit_opcode(opcode::OP_CastFieldObject);
            emit_opcode(opcode::OP_EvalFieldVariable, field);
            break;
        default:
            throw comp_error(exp.loc(), "unknown field variable object type");
    }
}

auto compiler::emit_expr_local(expr_identifier const& exp) -> void
{
    auto const it = constants_.find(exp.value);

    if (it != constants_.end())
        emit_expr(*it->second);
    else
        emit_opcode(opcode::OP_EvalLocalVariableCached, std::format("{}", variable_access(exp)));
}

auto compiler::emit_expr_object(expr const& exp) -> void
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
            emit_expr_array(exp.as<expr_array>());
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_field:
            emit_expr_field(exp.as<expr_field>());
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_call:
            emit_expr_call(exp.as<expr_call>(), false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_method:
            emit_expr_method(exp.as<expr_method>(), false);
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        case node::expr_identifier:
            emit_opcode(opcode::OP_EvalLocalVariableCached, std::format("{}", variable_access(exp.as<expr_identifier>())));
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        default:
            throw comp_error(exp.loc(), "not an object");
    }
}

auto compiler::emit_expr_vector(expr_vector const& exp) -> void
{
    auto data = std::vector<std::string>{};
    auto isconst = true;
    auto flags = 0;

    if (exp.x->is<expr_integer>())
    {
        auto value = std::atoi(exp.x->as<expr_integer>().value.data());
        data.push_back(exp.x->as<expr_integer>().value);

        if (value != 1 && value != -1 && value != 0)
            isconst = false;
        else
            flags |= (value == 1) ? 0x20 : (value == -1) ? 0x10 : 0;
    }
    else if (exp.x->is<expr_float>())
    {
        auto value = std::stof(exp.x->as<expr_float>().value.data());
        data.push_back(exp.x->as<expr_float>().value);

        if (value != 1.0 && value != -1.0 && value != 0.0)
            isconst = false;
        else
            flags |= (value == 1.0) ? 0x20 : (value == -1.0) ? 0x10 : 0;
    }
    else
    {
        isconst = false;
    }

    if (exp.y->is<expr_integer>())
    {
        auto value = std::atoi(exp.y->as<expr_integer>().value.data());
        data.push_back(exp.y->as<expr_integer>().value);

        if (value != 1 && value != -1 && value != 0)
            isconst = false;
        else
            flags |= (value == 1) ? 0x08 : (value == -1) ? 0x04 : 0;
    }
    else if (exp.y->is<expr_float>())
    {
        auto value = std::stof(exp.y->as<expr_float>().value.data());
        data.push_back(exp.y->as<expr_float>().value);

        if (value != 1.0 && value != -1.0 && value != 0.0)
            isconst = false;
        else
            flags |= (value == 1.0) ? 0x08 : (value == -1.0) ? 0x04 : 0;
    }
    else
    {
        isconst = false;
    }

    if (exp.z->is<expr_integer>())
    {
        auto value = std::atoi(exp.z->as<expr_integer>().value.data());
        data.push_back(exp.z->as<expr_integer>().value);

        if (value != 1 && value != -1 && value != 0)
            isconst = false;
        else
            flags |= (value == 1) ? 0x02 : (value == -1) ? 0x01 : 0;
    }
    else if (exp.z->is<expr_float>())
    {
        auto value = std::stof(exp.z->as<expr_float>().value.data());
        data.push_back(exp.z->as<expr_float>().value);

        if (value != 1.0 && value != -1.0 && value != 0.0)
            isconst = false;
        else
            flags |= (value == 1.0) ? 0x02 : (value == -1.0) ? 0x01 : 0;
    }
    else
    {
        isconst = false;
    }

    if (isconst)
    {
        emit_opcode(opcode::OP_VectorConstant, std::format("{}", flags));
    }
    else
    {
        // OP_GetVector seems to be broken, always use OP_Vector
        emit_expr(*exp.z);
        emit_expr(*exp.y);
        emit_expr(*exp.x);
        emit_opcode(opcode::OP_Vector);
    }
}

auto compiler::emit_expr_animation(expr_animation const& exp) -> void
{
    if (exp.space == "" && animtree_.empty())
    {
        throw comp_error(exp.loc(), "trying to use animation without specified using animtree");
    }

    if (exp.space != "")
        emit_opcode(opcode::OP_GetAnimation, { exp.space, exp.value });
    else
        emit_opcode(opcode::OP_GetAnimation, { animtree_, exp.value });
}

auto compiler::emit_expr_animtree(expr_animtree const& exp) -> void
{
    if (animtree_.empty())
    {
        throw comp_error(exp.loc(), "trying to use animtree without specified using animtree");
    }

    emit_opcode(opcode::OP_GetInteger, { animtree_, "-1" });
}

auto compiler::emit_expr_istring(expr_istring const& exp) -> void
{
    emit_opcode(opcode::OP_GetIString, exp.value);
}

auto compiler::emit_expr_string(expr_string const& exp) -> void
{
    emit_opcode(opcode::OP_GetString, exp.value);
}

auto compiler::emit_expr_hash(expr_hash const& exp) -> void
{
    emit_opcode(opcode::OP_GetHash, exp.value);
}

auto compiler::emit_expr_float(expr_float const& exp) -> void
{
    emit_opcode(opcode::OP_GetFloat, exp.value);
}

auto compiler::emit_expr_integer(expr_integer const& exp) -> void
{
    auto value = std::atoi(exp.value.data());

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
        emit_opcode(opcode::OP_GetInteger, exp.value);
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
    process_expr_parameters(*func.params);
    process_stmt_comp(*func.body);
}

auto compiler::process_stmt(stmt const& stm) -> void
{
    switch (stm.kind())
    {
        case node::stmt_list:
            process_stmt_list(stm.as<stmt_list>());
            break;
        case node::stmt_comp:
            process_stmt_comp(stm.as<stmt_comp>());
            break;
        case node::stmt_dev:
            process_stmt_dev(stm.as<stmt_dev>());
            break;
        case node::stmt_expr:
            process_stmt_expr(stm.as<stmt_expr>());
            break;
        case node::stmt_waittill:
            process_stmt_waittill(stm.as<stmt_waittill>());
            break;
        case node::stmt_if:
            process_stmt_if(stm.as<stmt_if>());
            break;
        case node::stmt_ifelse:
            process_stmt_ifelse(stm.as<stmt_ifelse>());
            break;
        case node::stmt_while:
            process_stmt_while(stm.as<stmt_while>());
            break;
        case node::stmt_dowhile:
            process_stmt_dowhile(stm.as<stmt_dowhile>());
            break;
        case node::stmt_for:
            process_stmt_for(stm.as<stmt_for>());
            break;
        case node::stmt_foreach:
            process_stmt_foreach(stm.as<stmt_foreach>());
            break;
        case node::stmt_switch:
            process_stmt_switch(stm.as<stmt_switch>());
            break;
        case node::stmt_endon:
        case node::stmt_notify:
        case node::stmt_wait:
        case node::stmt_waitrealtime:
        case node::stmt_waittillmatch:
        case node::stmt_waittillframeend:
        case node::stmt_case:
        case node::stmt_default:
        case node::stmt_break:
        case node::stmt_continue:
        case node::stmt_return:
        case node::stmt_breakpoint:
        case node::stmt_prof_begin:
        case node::stmt_prof_end:
            break;
        default:
            throw comp_error(stm.loc(), "unknown statement");
    }
}

auto compiler::process_stmt_list(stmt_list const& stm) -> void
{
    for (auto const& entry : stm.list)
    {
        process_stmt(*entry);
    }
}

auto compiler::process_stmt_comp(stmt_comp const& stm) -> void
{
    process_stmt_list(*stm.block);
}

auto compiler::process_stmt_dev(stmt_dev const& stm) -> void
{
    process_stmt_list(*stm.block);
}

auto compiler::process_stmt_expr(stmt_expr const& stm) -> void
{
    switch (stm.value->kind())
    {
        case node::expr_increment:
            process_expr(*stm.value->as<expr_increment>().lvalue);
            break;
        case node::expr_decrement:
            process_expr(*stm.value->as<expr_decrement>().lvalue);
            break;
        case node::expr_assign:
            process_expr(*stm.value->as<expr_assign>().lvalue);
            break;
        case node::expr_call:
        case node::expr_method:
        case node::expr_const:
        case node::expr_empty:
            break;
        default:
            throw comp_error(stm.loc(), "unknown expr statement expression");
    }
}

auto compiler::process_stmt_waittill(stmt_waittill const& stm) -> void
{
    for (auto const& entry : stm.args->list)
    {
        if (!entry->is<expr_identifier>() && !entry->is<expr_undefined>())
        {
            throw comp_error(entry->loc(), "illegal waittill param, must be a local variable or undefined");
        }

        if (entry->is<expr_identifier>())
        {
            variable_register(entry->as<expr_identifier>());
        }
    }
}

auto compiler::process_stmt_if(stmt_if const& stm) -> void
{
    process_stmt(*stm.body);
}

auto compiler::process_stmt_ifelse(stmt_ifelse const& stm) -> void
{
    process_stmt(*stm.stmt_if);
    process_stmt(*stm.stmt_else);
}

auto compiler::process_stmt_while(stmt_while const& stm) -> void
{
    process_stmt(*stm.body);
}

auto compiler::process_stmt_dowhile(stmt_dowhile const& stm) -> void
{
    process_stmt(*stm.body);
}

auto compiler::process_stmt_for(stmt_for const& stm) -> void
{
    process_stmt(*stm.init);
    process_stmt(*stm.body);
    process_stmt(*stm.iter);
}

auto compiler::process_stmt_foreach(stmt_foreach const& stm) -> void
{
    if (stm.use_key)
    {
        process_expr(*stm.key);
        process_expr(*stm.value);
    }
    else
    {
        process_expr(*stm.value);
        process_expr(*stm.key);
    }

    process_expr(*stm.array);
    process_stmt(*stm.body);
}

auto compiler::process_stmt_switch(stmt_switch const& stm) -> void
{
    for (auto i = 0u; i < stm.body->block->list.size(); i++)
    {
        auto& entry = stm.body->block->list[i];

        if (entry->is<stmt_case>())
        {
            process_stmt_list(*entry->as<stmt_case>().body);
        }
        else if (entry->is<stmt_default>())
        {
            process_stmt_list(*entry->as<stmt_default>().body);
        }
    }
}

auto compiler::process_expr(expr const& exp) -> void
{
    if (exp.is<expr_identifier>())
    {
        variable_register(exp.as<expr_identifier>());
    }
    else if (exp.is<expr_array>())
    {
        process_expr(*exp.as<expr_array>().obj);
    }
}

auto compiler::process_expr_parameters(expr_parameters const& exp) -> void
{
    for (auto const& entry : exp.list)
    {
        if (entry->is<expr_identifier>())
        {
            variable_register(entry->as<expr_identifier>());
        }
        else if (entry->is<expr_assign>())
        {
            process_expr(*entry->as<expr_assign>().lvalue);
        }
    }
}

auto compiler::variable_register(expr_identifier const& exp) -> void
{
    auto found = false;

    for (auto i = 0u; i < stackframe_.size(); i++)
    {
        if (stackframe_[i] == exp.value)
        {
            found = true;
            break;
        }
    }

    if (!found) stackframe_.push_back(exp.value);
}

auto compiler::variable_access(expr_identifier const& exp) -> u8
{
    for (auto i = 0u; i < stackframe_.size(); i++)
    {
        if (stackframe_[i] == exp.value)
        {
            return static_cast<u8>(stackframe_.size() - 1 - i);
        }
    }

    throw comp_error(exp.loc(), std::format("local variable '{}' not found", exp.value));
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

} // namespace xsk::arc
