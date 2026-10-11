// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/arc/compiler.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc
{

compiler::compiler(context* ctx) : ctx_{ ctx }
{
}

auto compiler::compile(program const& data) -> assembly::ptr
{
    namespace_ = {};
    extension_ = (ctx_->instance() == instance::server) ? ".gsc" : ".csc";
    emit_program(data);
    return std::move(assembly_);
}

auto compiler::compile(std::string const& file, std::vector<u8>& data) -> assembly::ptr
{
    auto prog = ctx_->parser().parse_source(file, data);

    // where functions have a namespace, a script without '#namespace' gets one named after its file
    namespace_ = (ctx_->features() & feature::spaces) ? std::filesystem::path{ file }.stem().string() : std::string{};
    extension_ = std::filesystem::path{ file }.extension().string();

    emit_program(*prog);
    return std::move(assembly_);
}

auto compiler::emit_program(program const& prog) -> void
{
    assembly_ = assembly::make();
    localfuncs_.clear();
    classes_.clear();
    class_ = nullptr;
    developer_thread_ = false;
    animtree_ = {};
    index_ = 0;
    debug_pos_ = { .line = 0, .column = 0 };

    for (auto const& include : prog.includes)
    {
        emit_include(*include);
    }

    // a name is taken per namespace, and a script can switch namespace as it goes
    auto space = namespace_;

    for (auto const& dec : prog.declarations)
    {
        if (dec->is<decl_namespace>())
        {
            space = dec->as<decl_namespace>().name->value;
        }
        else if (dec->is<decl_function>())
        {
            auto const name = space + "::" + dec->as<decl_function>().name->value;

            for (auto const& entry : localfuncs_)
            {
                if (entry == name)
                    throw comp_error(dec->loc(), std::format("function name '{}' already defined as local function", dec->as<decl_function>().name->value));
            }

            localfuncs_.push_back(name);
        }
    }

    // a class can extend one declared further down
    for (auto const& dec : prog.declarations)
    {
        if (dec->is<decl_class>())
            register_class(dec->as<decl_class>(), false);
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
            // original t7 source repeats a '#using' now and then
            if (ctx_->features() & feature::size64)
                return;

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
        case node::decl_namespace:
            namespace_ = dec.as<decl_namespace>().name->value;
            break;
        case node::decl_precache:
            break;
        case node::decl_class:
            emit_decl_class(dec.as<decl_class>());
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

auto compiler::emit_decl_class(decl_class const& cls) -> void
{
    auto const& name = cls.name->value;
    auto& info = classes_.at(name);

    // the whole chain has to be known before a method is compiled
    for (auto const* entry = &info; !entry->base.empty();)
        entry = &find_class(entry->base, cls.loc());

    // inside a class its name is the namespace
    auto const space = std::exchange(namespace_, name);
    class_ = &info;

    for (auto const& entry : cls.body->list)
    {
        if (entry->is<decl_function>())
            emit_decl_function(entry->as<decl_function>());
    }

    // stock generates whichever of the two was not written, after the written methods
    for (auto const* special : { "__constructor", "__destructor" })
    {
        auto const written = std::any_of(cls.body->list.begin(), cls.body->list.end(), [special](auto const& entry) {
            return entry->template is<decl_function>() && entry->template as<decl_function>().name->value == special;
        });

        if (written)
            continue;

        auto const& loc = cls.loc();
        auto const func = decl_function::make(loc, expr_identifier::make(loc, ""), expr_identifier::make(loc, special), expr_parameters::make(loc), stmt_comp::make(loc, stmt_list::make(loc)), export_flags::export_none);
        emit_decl_function(*func);
        info.methods.emplace_back(special);
    }

    class_ = nullptr;
    namespace_ = space;

    emit_decl_class_vtable(name);
}

// The function stock generates next to every class and runs on load:
//
//   classes.<name>[0] = spawnstruct();
//   classes.<name>[0].__vtable[<hash of method>] = &<class>::<method>;
//
// with one line per method, inherited ones first, each list last declared first.
auto compiler::emit_decl_class_vtable(std::string const& name) -> void
{
    function_ = function::make();
    function_->index = index_;
    function_->name = name;
    function_->space = namespace_;
    function_->flags = static_cast<u8>(export_flags::export_autoexec) | static_cast<u8>(export_flags::export_private);

    emit_opcode(opcode::OP_CheckClearParams);
    emit_opcode(opcode::OP_PreScriptCall);
    emit_import(opcode::OP_ScriptFunctionCall, "", "spawnstruct", 0, import_flags::func_call);
    emit_opcode(opcode::OP_GetZero);
    emit_opcode(opcode::OP_GetClassesObject);
    emit_opcode(opcode::OP_EvalFieldVariableRef, name);
    emit_opcode(opcode::OP_EvalArrayRef);
    emit_opcode(opcode::OP_SetVariableField);

    auto const bind = [&](std::string const& space, std::string const& method) {
        emit_import(opcode::OP_GetFunction, space, method, 0, import_flags::func_reference);
        emit_opcode(opcode::OP_GetInteger, std::format("{}", static_cast<i32>(ctx_->hash_id(method))));
        emit_opcode(opcode::OP_GetZero);
        emit_opcode(opcode::OP_GetClassesObject);
        emit_opcode(opcode::OP_EvalFieldVariable, name);
        emit_opcode(opcode::OP_EvalArray);
        emit_opcode(opcode::OP_CastFieldObject);
        emit_opcode(opcode::OP_EvalFieldVariableRef, "__vtable");
        emit_opcode(opcode::OP_EvalArrayRef);
        emit_opcode(opcode::OP_SetVariableField);
    };

    // root class first, so a method that is overridden gets bound last
    auto chain = std::vector<std::string const*>{};

    for (auto base = &classes_.at(name).base; !base->empty(); base = &classes_.at(*base).base)
        chain.push_back(base);

    for (auto it = chain.rbegin(); it != chain.rend(); it++)
    {
        auto const& methods = classes_.at(**it).methods;

        for (auto method = methods.rbegin(); method != methods.rend(); method++)
            bind(**it, *method);
    }

    // The class's own list is every function exported under its name so far. That takes in
    // a script level function when class and '#namespace' are named alike, as stock does.
    auto own = std::vector<std::string>{};

    for (auto const& func : assembly_->functions)
    {
        if (func->space == name)
            own.push_back(func->name);
    }

    for (auto method = own.rbegin(); method != own.rend(); method++)
        bind(name, *method);

    emit_opcode(opcode::OP_End);

    function_->size = index_ - function_->index;
    assembly_->functions.push_back(std::move(function_));
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
    function_->space = namespace_;
    function_->params = static_cast<u8>(func.params->list.size());
    function_->flags = static_cast<u8>(func.flags);

    if (!func.params->list.empty() && func.params->list.back()->is<expr_ellipsis>())
        function_->flags |= static_cast<u8>(export_flags::export_varargs);

    process_function(func);

    scopes_.emplace_back();

    // a function declared inside '/# #/' runs as one devblock, default parameters included
    auto const dev = developer_thread_ && (ctx_->features() & feature::devstr);
    end_label_ = dev ? create_label() : std::string{};

    emit_expr_parameters(*func.params, dev ? end_label_ : std::string{});

    // A derived class runs the base constructor before its own. The destructor call is put
    // last: every derived destructor in the stock scripts is empty, so its place is a guess.
    auto const base_call = [&]() {
        emit_opcode(opcode::OP_PreScriptCall);
        emit_import(opcode::OP_ScriptFunctionCall, class_->base, func.name->value, 0, import_flags::func_call);
        emit_opcode(opcode::OP_DecTop);
    };

    auto const derived = class_ != nullptr && !class_->base.empty();

    if (derived && func.name->value == "__constructor")
        base_call();

    emit_stmt_comp(*func.body);

    if (derived && func.name->value == "__destructor")
        base_call();

    // the target of a devblock, or of a break outside of a loop
    if (!end_label_.empty())
        insert_label(end_label_);

    // t6 leaves the OP_End out once the body has returned, t7 only when a return is its last statement
    auto const& list = func.body->block->list;
    auto const open = (ctx_->features() & feature::size64) ? (list.empty() || !list.back()->is<stmt_return>()) : (scopes_.back().abort == scope::abort_none);

    if (open || function_->labels.contains(index_))
        emit_opcode(opcode::OP_End);

    scopes_.pop_back();

    function_->size = index_ - function_->index;
    assembly_->functions.push_back(std::move(function_));
}

auto compiler::emit_stmt(stmt const& stm) -> void
{
    debug_pos_ = { .line = stm.loc().begin.line, .column = stm.loc().begin.column };

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
    auto const was_dev = developer_thread_;
    developer_thread_ = true;
    emit_opcode(opcode::OP_DevblockBegin, end);

    auto& paren = scopes_.back();
    scopes_.emplace_back(paren.brk, paren.cnt);
    emit_stmt_list(*stm.block);
    scopes_.pop_back();

    insert_label(end);
    developer_thread_ = was_dev;
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
    emit_expr_event(*stm.event);
    emit_expr(*stm.obj);
    emit_opcode(opcode::OP_EndOn);
}

auto compiler::emit_stmt_notify(stmt_notify const& stm) -> void
{
    emit_opcode((ctx_->features() & feature::size64) ? opcode::OP_PreScriptCall : opcode::OP_VoidCodePos);

    for (auto it = stm.args->list.rbegin(); it != stm.args->list.rend(); it++)
    {
        emit_expr(**it);
    }

    emit_expr_event(*stm.event);
    emit_expr(*stm.obj);
    emit_opcode(opcode::OP_Notify);
}

auto compiler::emit_expr_event(expr const& exp) -> void
{
    // Engines with hashed names take an event name as a name hash, not a string. The
    // decompiler prints one as '#"death"', which here means that same name hash.
    if ((ctx_->features() & feature::hashids) && exp.is<expr_string>())
        emit_opcode(opcode::OP_GetHash, exp.as<expr_string>().value);
    else if ((ctx_->features() & feature::hashids) && exp.is<expr_hash>())
        emit_opcode(opcode::OP_GetHash, exp.as<expr_hash>().value);
    else
        emit_expr(exp);
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
    emit_expr_event(*stm.event);
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
    emit_expr_event(*stm.event);
    emit_expr(*stm.obj);
    emit_opcode(opcode::OP_WaitTillMatch, std::format("{}", stm.args->list.size()));
    emit_opcode(opcode::OP_ClearParams);
}

auto compiler::emit_stmt_waittillframeend(stmt_waittillframeend const& /*unused*/) -> void
{
    emit_opcode(opcode::OP_WaitTillFrameEnd);
}

// Jumps to 'loc' when the test fails. A negated test jumps on true instead of
// evaluating the '!'; stock t7 does that through parentheses too.
auto compiler::emit_expr_test(expr const& exp, std::string const& loc) -> void
{
    auto const* test = &exp;

    while ((ctx_->features() & feature::size64) && test->is<expr_paren>())
        test = test->as<expr_paren>().value.get();

    if (test->is<expr_not>())
    {
        emit_expr(*test->as<expr_not>().rvalue);
        emit_opcode(opcode::OP_JumpOnTrue, loc);
    }
    else
    {
        emit_expr(exp);
        emit_opcode(opcode::OP_JumpOnFalse, loc);
    }
}

auto compiler::emit_stmt_if(stmt_if const& stm) -> void
{
    auto end_loc = create_label();

    emit_expr_test(*stm.test, end_loc);

    auto& paren = scopes_.back();
    scopes_.emplace_back(paren.brk, paren.cnt);

    emit_stmt(*stm.body);

    scopes_.pop_back();

    insert_label(end_loc);
}

auto compiler::emit_stmt_ifelse(stmt_ifelse const& stm) -> void
{
    auto else_loc = create_label();
    auto end_loc = create_label();

    emit_expr_test(*stm.test, else_loc);

    auto& paren = scopes_.back();
    scopes_.emplace_back(paren.brk, paren.cnt);
    emit_stmt(*stm.stmt_if);
    scopes_.pop_back();

    emit_opcode(opcode::OP_Jump, end_loc);

    insert_label(else_loc);

    auto& paren2 = scopes_.back();
    scopes_.emplace_back(paren2.brk, paren2.cnt);
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

    emit_expr_test(*stm.test, break_loc);

    scopes_.emplace_back(break_loc, continue_loc);
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

    scopes_.emplace_back(break_loc, continue_loc);
    emit_stmt(*stm.body);
    scopes_.pop_back();

    insert_label(continue_loc);

    // stock t7 does not drop the '!' of a do-while test
    if (stm.test->is<expr_not>() && !(ctx_->features() & feature::size64))
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

    // t7 only leaves the test out when there is none: 'for ( ;; )' loops, 'for ( ; 1; )' still tests
    bool const_cond = (ctx_->features() & feature::size64) ? stm.test->is<expr_empty>() : is_constant_condition(*stm.test);

    if (!const_cond && (ctx_->features() & feature::size64))
    {
        emit_expr_test(*stm.test, break_loc);
    }
    else if (!const_cond)
    {
        emit_expr(*stm.test);
        emit_opcode(opcode::OP_JumpOnFalse, break_loc);
    }

    can_break_ = true;
    can_continue_ = true;

    scopes_.emplace_back(break_loc, continue_loc);
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

    // t7 reads the next key before the body runs and keeps it in a local of its own
    auto const next = expr_identifier{ stm.loc(), "__new_" + stm.key->as<expr_identifier>().value };

    if (ctx_->features() & feature::foreach)
    {
        emit_expr_variable(*stm.key);
        emit_expr_variable(*stm.array);
        emit_opcode(opcode::OP_NextArrayKey);
        emit_expr_local_ref(next, true);
    }

    scopes_.emplace_back(break_loc, continue_loc);
    emit_stmt(*stm.body);
    scopes_.pop_back();

    can_break_ = false;
    can_continue_ = false;

    insert_label(continue_loc);

    if (ctx_->features() & feature::foreach)
    {
        emit_expr_local(next);
    }
    else
    {
        emit_expr_variable(*stm.key);
        emit_expr_variable(*stm.array);
        emit_opcode(opcode::OP_NextArrayKey);
    }

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

    // Treyarch's compiler sorts the table -- integers ascending by value, strings
    // ascending by text, default last. Every one of the 583 tables in data/bin/t6 agrees.
    // The case bodies stay in source order, only the table is sorted, so each entry keeps
    // its own label.
    auto cases = std::vector<std::array<std::string, 3>>{};

    auto loc_default = std::string{};
    auto has_default = false;

    for (const auto& entry : stm.body->block->list)
    {
        if (entry->is<stmt_case>())
        {
            if (entry->as<stmt_case>().value->is<expr_integer>())
            {
                cases.push_back({ std::format("{}", static_cast<i32>(switch_type::integer)), entry->as<stmt_case>().value->as<expr_integer>().value, insert_label() });
            }
            else if (entry->as<stmt_case>().value->is<expr_string>())
            {
                cases.push_back({ std::format("{}", static_cast<i32>(switch_type::string)), entry->as<stmt_case>().value->as<expr_string>().value, insert_label() });
            }
            else
            {
                throw comp_error(entry->loc(), "case type must be int or string");
            }

            auto& paren = scopes_.back();
            scopes_.emplace_back(break_loc, paren.cnt);
            emit_stmt_list(*entry->as<stmt_case>().body);
            scopes_.pop_back();
        }
        else if (entry->is<stmt_default>())
        {
            loc_default = insert_label();
            has_default = true;

            auto& paren = scopes_.back();
            scopes_.emplace_back(break_loc, paren.cnt);
            emit_stmt_list(*entry->as<stmt_default>().body);
            scopes_.pop_back();
        }
        else
        {
            throw comp_error(entry->loc(), "missing case statement");
        }
    }

    auto const integer = std::format("{}", static_cast<i32>(switch_type::integer));

    std::stable_sort(cases.begin(), cases.end(), [&integer](auto const& a, auto const& b) {
        if (a[0] != b[0])
            return a[0] < b[0];

        return (a[0] == integer) ? std::stoi(a[1]) < std::stoi(b[1]) : a[1] < b[1];
    });

    auto data = std::vector<std::string>{};
    data.push_back(std::format("{}", stm.body->block->list.size()));

    for (auto const& entry : cases)
    {
        data.emplace_back("case");
        data.push_back(entry[0]);
        data.push_back(entry[1]);
        data.push_back(entry[2]);
    }

    if (has_default)
    {
        data.emplace_back("default");
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
    if (!can_break_ /*|| scopes_.back().abort != scope::abort_none*/ || scopes_.back().brk.empty())
    {
        if (!(ctx_->features() & feature::size64))
            throw comp_error(stm.loc(), "illegal break statement");

        // stock t7 accepts a break outside of a loop and jumps to the end of the function
        if (end_label_.empty())
            end_label_ = create_label();

        return emit_opcode(opcode::OP_Jump, end_label_);
    }

    if (scopes_.back().abort == scope::abort_none)
        scopes_.back().abort = scope::abort_break;

    emit_opcode(opcode::OP_Jump, scopes_.back().brk);
}

auto compiler::emit_stmt_continue(stmt_continue const& stm) -> void
{
    if (!can_continue_ /*|| scopes_.back().abort != scope::abort_none*/ || scopes_.back().cnt.empty())
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

auto compiler::emit_stmt_breakpoint(stmt_breakpoint const& /*unused*/) -> void
{
    // TODO:
}

auto compiler::emit_stmt_prof_begin(stmt_prof_begin const& /*unused*/) -> void
{
    // TODO:
}

auto compiler::emit_stmt_prof_end(stmt_prof_end const& /*unused*/) -> void
{
    // TODO:
}

auto compiler::emit_expr(expr const& exp) -> void
{
    debug_pos_ = { .line = exp.loc().begin.line, .column = exp.loc().begin.column };

    // constant arithmetic is done here, the stock compilers ship '15 * 1000' as 15000
    if (exp.is<expr_binary>() || exp.is<expr_not>() || exp.is<expr_negate>() || exp.is<expr_complement>())
    {
        if (auto const value = fold_expr(exp); value.has_value())
        {
            if (std::holds_alternative<i32>(*value))
                return emit_expr_integer(expr_integer{ exp.loc(), std::format("{}", std::get<i32>(*value)) });

            return emit_expr_float(expr_float{ exp.loc(), utils::string::float_string(std::get<f32>(*value)) });
        }
    }

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
        case node::expr_world:
            emit_opcode(opcode::OP_GetWorld);
            break;
        case node::expr_classes:
            emit_opcode(opcode::OP_GetClasses);
            break;
        case node::expr_new:
            emit_expr_new(exp.as<expr_new>());
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

auto compiler::fold_expr(expr const& exp) const -> std::optional<std::variant<i32, f32>>
{
    using value = std::variant<i32, f32>;

    auto const as_float = [](value const& v) { return std::holds_alternative<i32>(v) ? static_cast<f32>(std::get<i32>(v)) : std::get<f32>(v); };

    switch (exp.kind())
    {
        // no expr_paren: stock folds '15 * 1000' and leaves '( 240 ) * ( 240 )' alone
        case node::expr_integer:
            return value{ static_cast<i32>(std::strtoll(exp.as<expr_integer>().value.data(), nullptr, 0)) };
        case node::expr_float:
            return value{ std::stof(exp.as<expr_float>().value) };
        case node::expr_true:
            return value{ 1 };
        case node::expr_false:
            return value{ 0 };
        case node::expr_not:
        {
            auto const rhs = fold_expr(*exp.as<expr_not>().rvalue);

            if (!rhs.has_value())
                return std::nullopt;

            return value{ as_float(*rhs) == 0.0f ? 1 : 0 };
        }
        case node::expr_complement:
        {
            auto const rhs = fold_expr(*exp.as<expr_complement>().rvalue);

            if (!rhs.has_value() || !std::holds_alternative<i32>(*rhs))
                return std::nullopt;

            return value{ ~std::get<i32>(*rhs) };
        }
        case node::expr_negate:
        {
            auto const rhs = fold_expr(*exp.as<expr_negate>().rvalue);

            if (!rhs.has_value())
                return std::nullopt;

            if (std::holds_alternative<i32>(*rhs))
                return value{ -std::get<i32>(*rhs) };

            return value{ -std::get<f32>(*rhs) };
        }
        case node::expr_binary:
        {
            auto const& bin = exp.as<expr_binary>();
            auto const lhs = fold_expr(*bin.lvalue);
            auto const rhs = fold_expr(*bin.rvalue);

            if (!lhs.has_value() || !rhs.has_value())
                return std::nullopt;

            if (std::holds_alternative<i32>(*lhs) && std::holds_alternative<i32>(*rhs))
            {
                // unsigned so that overflow wraps the way the engine's 32 bit integers do
                auto const a = static_cast<u32>(std::get<i32>(*lhs));
                auto const b = static_cast<u32>(std::get<i32>(*rhs));

                switch (bin.oper)
                {
                    case expr_binary::op::add: return value{ static_cast<i32>(a + b) };
                    case expr_binary::op::sub: return value{ static_cast<i32>(a - b) };
                    case expr_binary::op::mul: return value{ static_cast<i32>(a * b) };
                    case expr_binary::op::shl: return value{ static_cast<i32>(a << (b & 31)) };
                    case expr_binary::op::shr: return value{ static_cast<i32>(a) >> (b & 31) };
                    case expr_binary::op::bwor: return value{ static_cast<i32>(a | b) };
                    case expr_binary::op::bwand: return value{ static_cast<i32>(a & b) };
                    case expr_binary::op::bwexor: return value{ static_cast<i32>(a ^ b) };
                    case expr_binary::op::mod:
                        if (b == 0) return std::nullopt;
                        return value{ std::get<i32>(*lhs) % std::get<i32>(*rhs) };
                    case expr_binary::op::div:
                        // dividing two integers gives a float: '250 / 1000' is 0.25 and '4000 / 1000' is 4.0
                        break;
                    default:
                        return std::nullopt;
                }
            }

            auto const a = as_float(*lhs);
            auto const b = as_float(*rhs);

            switch (bin.oper)
            {
                case expr_binary::op::add: return value{ a + b };
                case expr_binary::op::sub: return value{ a - b };
                case expr_binary::op::mul: return value{ a * b };
                case expr_binary::op::div: return (b == 0.0f) ? std::nullopt : std::optional{ value{ a / b } };
                default: return std::nullopt;
            }
        }
        default:
            return std::nullopt;
    }
}

auto compiler::emit_expr_const(expr_const const& exp) -> void
{
    auto const itr = constants_.find(exp.lvalue->value);

    if (itr != constants_.end())
        throw comp_error(exp.loc(), std::format("duplicated constant '{}'", exp.lvalue->value));

    if (!(ctx_->features() & feature::size64) && std::find(stackframe_.begin(), stackframe_.end(), exp.lvalue->value) != stackframe_.end())
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

    emit_expr_test(*exp.test, else_loc);

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
            case expr_binary::op::seq:
                emit_opcode(opcode::OP_SuperEqual);
                break;
            case expr_binary::op::sne:
                emit_opcode(opcode::OP_SuperNotEqual);
                break;
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
    // stock t7 multiplies by -1 where t6 subtracts from 0
    if (ctx_->features() & feature::size64)
    {
        emit_expr(*exp.rvalue);
        emit_opcode(opcode::OP_GetNegByte, "1");
        return emit_opcode(opcode::OP_Multiply);
    }

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
    else if (exp.value->is<expr_member>())
        emit_expr_call_member(exp.value->as<expr_member>(), is_stmt);
    else
        throw comp_error(exp.loc(), "unknown function call expression");
}

auto compiler::emit_expr_call_member(expr_member const& exp, bool is_stmt) -> void
{
    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(*exp.args);
    emit_expr(*exp.obj);

    auto const op = (exp.mode == call::mode::thread) ? opcode::OP_ScriptThreadCallClass : opcode::OP_ScriptFunctionCallClass;
    emit_opcode(op, { exp.name->value, std::format("{}", exp.args->list.size()) });

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

auto compiler::emit_expr_new(expr_new const& exp) -> void
{
    // the constructor takes no arguments and its result is dropped, the object stays
    emit_opcode(opcode::OP_New, exp.name->value);
    emit_opcode(opcode::OP_ScriptFunctionCallClass, std::vector<std::string>{ "__constructor", "0" });
    emit_opcode(opcode::OP_DecTop);
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
    bool as_dev = false;
    auto const was_dev = developer_thread_;
    std::string end;

    // an assert gets a devblock of its own, also when it already sits inside one
    if (is_stmt && (exp.name->value == "assert" || exp.name->value == "assertmsg"))
    {
        as_dev = true;
        developer_thread_ = true;
        end = create_label();
        emit_opcode(opcode::OP_DevblockBegin, end);
    }

    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(*exp.args);

    switch (exp.mode)
    {
        case call::mode::normal:
            emit_import(opcode::OP_ScriptFunctionCall, exp.path->value, exp.name->value, exp.args->list.size(), import_flags::func_call);
            break;
        case call::mode::thread:
            emit_import(opcode::OP_ScriptThreadCall, exp.path->value, exp.name->value, exp.args->list.size(), import_flags::func_call_thread);
            break;
        default:
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);

    if (as_dev)
    {
        insert_label(end);
        developer_thread_ = was_dev;
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
    emit_opcode(opcode::OP_PreScriptCall);
    emit_expr_arguments(*exp.args);
    emit_expr(obj);

    switch (exp.mode)
    {
        case call::mode::normal:
            emit_import(opcode::OP_ScriptMethodCall, exp.path->value, exp.name->value, exp.args->list.size(), import_flags::meth_call);
            break;
        case call::mode::thread:
            emit_import(opcode::OP_ScriptMethodThreadCall, exp.path->value, exp.name->value, exp.args->list.size(), import_flags::meth_call_thread);
            break;
        default:
            break;
    }

    if (is_stmt)
        emit_opcode(opcode::OP_DecTop);
}

auto compiler::emit_expr_parameters(expr_parameters const& exp, std::string const& devblock) -> void
{
    if (stackframe_.empty())
    {
        emit_opcode(opcode::OP_CheckClearParams);
    }
    else if (ctx_->features() & feature::refvarg)
    {
        auto data = std::vector<std::string>{};

        for (auto i = 0u; i < stackframe_.size(); i++)
        {
            auto type = param_type::value;

            if (i < exp.list.size() && exp.list[i]->is<expr_reference>())
                type = param_type::reference;
            else if (i < exp.list.size() && exp.list[i]->is<expr_ellipsis>())
                type = param_type::vararg;

            data.push_back(stackframe_[i]);
            data.push_back(std::format("{}", static_cast<u8>(type)));
        }

        emit_opcode(opcode::OP_SafeCreateLocalVariables, data);
    }
    else
    {
        emit_opcode(opcode::OP_SafeCreateLocalVariables, stackframe_);
    }

    if (!devblock.empty())
        emit_opcode(opcode::OP_DevblockBegin, devblock);

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

auto compiler::emit_expr_gettime(expr_gettime const& /*unused*/) -> void
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
    emit_import(opcode::OP_GetFunction, exp.path->value, exp.name->value, 0, import_flags::func_reference);
}

auto compiler::emit_import(opcode op, std::string const& path, std::string const& name, usize args, import_flags type) -> void
{
    auto flags = static_cast<u8>(type);

    if (developer_thread_)
        flags |= static_cast<u8>(import_flags::developer);

    if (ctx_->features() & feature::spaces)
    {
        // inside a class an inherited method is reached through the class that declares it
        if (auto const* owner = path.empty() ? method_owner(name) : nullptr; owner != nullptr)
            return emit_opcode(op, { *owner, name, std::format("{}", args), std::format("{}", flags) });

        // a name with no namespace is looked up from the script's own, 'assert' from none at all
        if (path.empty())
            flags |= static_cast<u8>(import_flags::unscoped);

        auto const& space = (path.empty() && name != "assert" && name != "assertmsg") ? namespace_ : path;

        return emit_opcode(op, { space, name, std::format("{}", args), std::format("{}", flags) });
    }

    if (!path.empty() && std::find(assembly_->includes.begin(), assembly_->includes.end(), path) == assembly_->includes.end())
    {
        assembly_->includes.push_back(path);
    }

    emit_opcode(op, { path, name, std::format("{}", args), std::format("{}", flags) });
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

    if ((ctx_->features() & feature::size64) && (exp.obj->is<expr_level>() || exp.obj->is<expr_self>()))
    {
        emit_opcode(exp.obj->is<expr_level>() ? opcode::OP_LevelEvalFieldVariableRef : opcode::OP_SelfEvalFieldVariableRef, field);
        if (set) emit_opcode(opcode::OP_SetVariableField);
        return;
    }

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
        case node::expr_world:
        case node::expr_classes:
            emit_opcode(exp.obj->is<expr_world>() ? opcode::OP_GetWorldObject : opcode::OP_GetClassesObject);
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
            emit_expr_local(exp.obj->as<expr_identifier>());
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

    if (is_member(exp.value))
        emit_opcode(opcode::OP_SelfEvalFieldVariableRef, exp.value);
    else
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

    if ((ctx_->features() & feature::size64) && (exp.obj->is<expr_level>() || exp.obj->is<expr_self>()))
    {
        return emit_opcode(exp.obj->is<expr_level>() ? opcode::OP_LevelEvalFieldVariable : opcode::OP_SelfEvalFieldVariable, field);
    }

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
        case node::expr_world:
        case node::expr_classes:
            emit_opcode(exp.obj->is<expr_world>() ? opcode::OP_GetWorldObject : opcode::OP_GetClassesObject);
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
            emit_expr_local(exp.obj->as<expr_identifier>());
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
    else if (is_member(exp.value))
        emit_opcode(opcode::OP_SelfEvalFieldVariable, exp.value);
    else if ((ctx_->features() & feature::size64) && exp.value == "__function__")
        emit_opcode(opcode::OP_GetString, std::format("{}::{}", function_->space, function_->name));
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
        case node::expr_world:
            emit_opcode(opcode::OP_GetWorldObject);
            break;
        case node::expr_classes:
            emit_opcode(opcode::OP_GetClassesObject);
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
            emit_expr_local(exp.as<expr_identifier>());
            emit_opcode(opcode::OP_CastFieldObject);
            break;
        default:
            throw comp_error(exp.loc(), "not an object");
    }
}

auto compiler::emit_expr_vector(expr_vector const& exp) -> void
{
    // A vector of literals whose non zero components share one magnitude is a unit
    // vector, one flag pair per axis, scaled when that magnitude is not 1.
    auto const axes = std::array<expr const*, 3>{ exp.x.get(), exp.y.get(), exp.z.get() };
    auto isconst = true;
    auto scale = 0.0f;
    auto flags = 0;

    for (auto i = 0u; i < axes.size() && isconst; i++)
    {
        // folded first: stock ships ( 0, 0, 72 / 2 ) as a scaled unit vector too
        auto const folded = fold_expr(*axes[i]);
        auto value = 0.0f;

        if (!folded.has_value())
            isconst = false;
        else if (std::holds_alternative<i32>(*folded))
            value = static_cast<f32>(std::get<i32>(*folded));
        else
            value = std::get<f32>(*folded);

        if (value == 0.0f)
            continue;

        if (scale == 0.0f)
            scale = std::abs(value);
        else if (std::abs(value) != scale)
            isconst = false;

        flags |= ((value > 0.0f) ? 0x20 : 0x10) >> (i * 2);
    }

    if (!(ctx_->features() & feature::size64))
    {
        // t6 only knows the unit vector itself
        isconst = isconst && (scale == 0.0f || scale == 1.0f);
    }
    else if (!(flags & 0x30) && (flags & 0x0C) && (flags & 0x03))
    {
        // stock t7 never does this for ( 0, y, z ): all 25 shipped ( 0, 1, 1 ) are built in full
        isconst = false;
    }

    if (!isconst)
    {
        // OP_GetVector seems to be broken, always use OP_Vector
        emit_expr(*exp.z);
        emit_expr(*exp.y);
        emit_expr(*exp.x);
        return emit_opcode(opcode::OP_Vector);
    }

    auto const scaled = scale != 0.0f && scale != 1.0f;

    if (scaled)
        emit_opcode(opcode::OP_GetFloat, utils::string::float_string(scale));

    emit_opcode(opcode::OP_VectorConstant, std::format("{}", flags));

    if (scaled)
        emit_opcode(opcode::OP_VectorScale);
}

auto compiler::emit_expr_animation(expr_animation const& exp) -> void
{
    if (exp.space.empty() && animtree_.empty())
    {
        throw comp_error(exp.loc(), "trying to use animation without specified using animtree");
    }

    if (!exp.space.empty())
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
    // On engines with hashed names '#"name"' is still the older djb2 hash, not the one
    // names are stored under. '_id_' spells out a value and passes through.
    if ((ctx_->features() & feature::hashids) && !exp.value.starts_with("_id_"))
    {
        auto hash = 5381u;

        for (auto const c : exp.value)
            hash = static_cast<u32>(std::tolower(static_cast<u8>(c))) + 33 * hash;

        return emit_opcode(opcode::OP_GetHash, std::format("_id_{:08X}", hash));
    }

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
    else if (value > 0 && value < 32768)
    {
        // the stock compilers stop at 32767 despite the opcode name, on t6 and t7 alike
        emit_opcode(opcode::OP_GetUnsignedShort, exp.value);
    }
    else if (value < 0 && value > -32768)
    {
        emit_opcode(opcode::OP_GetNegUnsignedShort, exp.value.substr(1));
    }
    else
    {
        emit_opcode(opcode::OP_GetInteger, exp.value);
    }
}

auto compiler::emit_expr_false(expr_false const& /*unused*/) -> void
{
    emit_opcode(opcode::OP_GetZero);
}

auto compiler::emit_expr_true(expr_true const& /*unused*/) -> void
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
        case node::expr_const:
            // stock t7 reserves a frame slot for a constant even though every use is inlined
            if (ctx_->features() & feature::size64)
                variable_register(*stm.value->as<expr_const>().lvalue);
            break;
        case node::expr_call:
        case node::expr_method:
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
    if (ctx_->features() & feature::foreach)
    {
        // stock t7 frame order: 'key, value, next, array' when the key is written out,
        // 'value, key, array, next' when it is hidden
        auto const next = expr_identifier{ stm.loc(), "__new_" + stm.key->as<expr_identifier>().value };

        if (stm.use_key)
        {
            process_expr(*stm.key);
            process_expr(*stm.value);
            variable_register(next);
            process_expr(*stm.array);
        }
        else
        {
            process_expr(*stm.value);
            process_expr(*stm.key);
            process_expr(*stm.array);
            variable_register(next);
        }

        return process_stmt(*stm.body);
    }

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
    for (auto& entry : stm.body->block->list)
    {
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
    else if (exp.is<expr_field>() && (ctx_->features() & feature::size64))
    {
        // stock t7 makes a local out of 'name.field = value' even when nothing assigns 'name'
        process_expr(*exp.as<expr_field>().obj);
    }
}

auto compiler::process_expr_parameters(expr_parameters const& exp) -> void
{
    for (auto const& entry : exp.list)
    {
        if (entry->is<expr_identifier>())
        {
            variable_register(entry->as<expr_identifier>(), true);
        }
        else if (entry->is<expr_assign>())
        {
            variable_register(entry->as<expr_assign>().lvalue->as<expr_identifier>(), true);
        }
        else if (entry->is<expr_reference>())
        {
            variable_register(*entry->as<expr_reference>().name, true);
        }
        else if (entry->is<expr_ellipsis>())
        {
            stackframe_.emplace_back("vararg");
        }
    }
}

auto compiler::register_class(decl_class const& cls, bool compiled) -> void
{
    auto info = class_info{ .base = cls.base->value, .vars = {}, .methods = {} };

    for (auto const& entry : cls.body->list)
    {
        if (entry->is<decl_variable>())
            info.vars.push_back(entry->as<decl_variable>().name->value);
        else if (entry->is<decl_function>())
            info.methods.push_back(entry->as<decl_function>().name->value);
    }

    // A class always ends up with both, see emit_decl_class. One of this script only gets the
    // missing one once it is compiled: stock leaves it out of the vtable of a class that
    // extends a base declared further down.
    for (auto const* special : { "__constructor", "__destructor" })
    {
        if (compiled && std::find(info.methods.begin(), info.methods.end(), special) == info.methods.end())
            info.methods.emplace_back(special);
    }

    // first one wins: the script's own classes are registered before any it pulls in
    classes_.try_emplace(cls.name->value, std::move(info));
}

// A base class can live in another script. Its members and methods decide what the derived
// class compiles to, so the scripts named by '#using' are parsed until one declares it.
auto compiler::find_class(std::string const& name, location const& loc) -> class_info const&
{
    for (auto i = 0u; i < assembly_->includes.size() && !classes_.contains(name); i++)
    {
        try
        {
            auto const [file, data, size] = ctx_->load_header(assembly_->includes[i] + extension_);

            if (std::string_view{ data, size }.find("class") == std::string_view::npos)
                continue;

            auto const prog = ctx_->parser().parse_source(*file, reinterpret_cast<u8 const*>(data), size);

            for (auto const& dec : prog->declarations)
            {
                if (dec->is<decl_class>())
                    register_class(dec->as<decl_class>(), true);
            }
        }
        catch (std::exception const&)
        {
            // a script that is missing or does not parse cannot be the one, the error below covers it
        }
    }

    if (auto const itr = classes_.find(name); itr != classes_.end())
        return itr->second;

    throw comp_error(loc, std::format("class '{}' not found in this script or in the ones it is #using", name));
}

// the base class that declares 'name', when the class being compiled inherits it
auto compiler::method_owner(std::string const& name) const -> std::string const*
{
    if (class_ == nullptr || std::find(class_->methods.begin(), class_->methods.end(), name) != class_->methods.end())
        return nullptr;

    for (auto const* base = &class_->base; !base->empty();)
    {
        auto const itr = classes_.find(*base);

        if (itr == classes_.end())
            return nullptr;

        if (std::find(itr->second.methods.begin(), itr->second.methods.end(), name) != itr->second.methods.end())
            return &itr->first;

        base = &itr->second.base;
    }

    return nullptr;
}

// a name that is not a local reads as a field of self when the class or a base declares it
auto compiler::is_member(std::string const& name) const -> bool
{
    if (class_ == nullptr || std::find(stackframe_.begin(), stackframe_.end(), name) != stackframe_.end())
        return false;

    for (auto const* entry = class_; entry != nullptr;)
    {
        if (std::find(entry->vars.begin(), entry->vars.end(), name) != entry->vars.end())
            return true;

        auto const itr = classes_.find(entry->base);
        entry = (itr != classes_.end()) ? &itr->second : nullptr;
    }

    return false;
}

auto compiler::variable_register(expr_identifier const& exp, bool param) -> void
{
    // assigning to a member does not make a local, a parameter of that name still hides it
    if (!param && is_member(exp.value))
        return;

    auto found = false;

    for (const auto& i : stackframe_)
    {
        if (i == exp.value)
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
            // Only whether the literal is non-zero matters, and a literal can be wider
            // than int, so it must not be parsed as one: 'while ( 4294967295 )' is a
            // perfectly good always-true condition. strtoull saturates instead of
            // throwing, and a saturated value is non-zero either way.
            auto const& val = exp.as<expr_integer>().value;

            if (std::strtoull(val.data(), nullptr, 0) != 0)
                return true;

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
