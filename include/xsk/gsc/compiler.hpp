// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/gsc/common/types.hpp"

namespace xsk::gsc
{

struct compiler
{
private:
    context* ctx_;
    assembly::ptr assembly_;
    function::ptr function_;
    std::vector<std::string> localfuncs_;
    std::vector<std::string> stackframe_;
    std::unordered_map<std::string, expr const*> constants_;
    std::unordered_map<node*, scope::ptr> scopes_;
    std::vector<scope*> break_blks_;
    std::vector<scope*> continue_blks_;
    std::string animname_;
    sourcepos debug_pos_;
    usize index_;
    usize label_idx_;
    bool can_break_;
    bool can_continue_;
    bool developer_thread_;
    bool animload_;

public:
    explicit compiler(context* ctx);
    auto compile(program const& data) -> assembly::ptr;
    auto compile(std::string const& file, std::vector<u8>& data) -> assembly::ptr;

private:
    auto emit_program(program const& prog) -> void;
    auto emit_decl(decl const& dec) -> void;
    auto emit_decl_usingtree(decl_usingtree const& animtree) -> void;
    auto emit_decl_constant(decl_constant const& constant) -> void;
    auto emit_decl_function(decl_function const& func) -> void;
    auto emit_stmt(stmt const& stm, scope& scp, bool last) -> void;
    auto emit_stmt_list(stmt_list const& stm, scope& scp, bool last) -> void;
    auto emit_stmt_comp(stmt_comp const& stm, scope& scp, bool last) -> void;
    auto emit_stmt_dev(stmt_dev const& stm, scope& scp, bool last) -> void;
    auto emit_stmt_expr(stmt_expr const& stm, scope& scp) -> void;
    auto emit_stmt_endon(stmt_endon const& stm, scope& scp) -> void;
    auto emit_stmt_notify(stmt_notify const& stm, scope& scp) -> void;
    auto emit_stmt_wait(stmt_wait const& stm, scope& scp) -> void;
    auto emit_stmt_waittill(stmt_waittill const& stm, scope& scp) -> void;
    auto emit_stmt_waittillmatch(stmt_waittillmatch const& stm, scope& scp) -> void;
    auto emit_stmt_waittillframeend(stmt_waittillframeend const& stm, scope& scp) -> void;
    auto emit_stmt_waitframe(stmt_waitframe const& stm, scope& scp) -> void;
    auto emit_stmt_if(stmt_if const& stm, scope& scp, bool last) -> void;
    auto emit_stmt_ifelse(stmt_ifelse const& stm, scope& scp, bool last) -> void;
    auto emit_stmt_while(stmt_while const& stm, scope& scp) -> void;
    auto emit_stmt_dowhile(stmt_dowhile const& stm, scope& scp) -> void;
    auto emit_stmt_for(stmt_for const& stm, scope& scp) -> void;
    auto emit_stmt_foreach(stmt_foreach const& stm, scope& scp) -> void;
    auto emit_stmt_switch(stmt_switch const& stm, scope& scp) -> void;
    auto emit_stmt_case(stmt_case const& stm, scope& scp) -> void;
    auto emit_stmt_default(stmt_default const& stm, scope& scp) -> void;
    auto emit_stmt_break(stmt_break const& stm, scope& scp) -> void;
    auto emit_stmt_continue(stmt_continue const& stm, scope& scp) -> void;
    auto emit_stmt_return(stmt_return const& stm, scope& scp) -> void;
    auto emit_stmt_breakpoint(stmt_breakpoint const& stm, scope& scp) -> void;
    auto emit_stmt_prof_begin(stmt_prof_begin const& stm, scope& scp) -> void;
    auto emit_stmt_prof_end(stmt_prof_end const& stm, scope& scp) -> void;
    auto emit_stmt_assert(stmt_assert const& stm, scope& scp) -> void;
    auto emit_stmt_assertex(stmt_assertex const& stm, scope& scp) -> void;
    auto emit_stmt_assertmsg(stmt_assertmsg const& stm, scope& scp) -> void;
    auto emit_expr(expr const& exp, scope& scp) -> void;
    auto emit_expr_assign(expr_assign const& exp, scope& scp) -> void;
    auto emit_expr_clear(expr const& exp, scope& scp) -> void;
    auto emit_expr_clear_local(expr_identifier const& exp, scope& scp) -> void;
    auto emit_expr_increment(expr_increment const& exp, scope& scp, bool is_stmt) -> void;
    auto emit_expr_decrement(expr_decrement const& exp, scope& scp, bool is_stmt) -> void;
    auto emit_expr_ternary(expr_ternary const& exp, scope& scp) -> void;
    auto emit_expr_binary(expr_binary const& exp, scope& scp) -> void;
    auto emit_expr_complement(expr_complement const& exp, scope& scp) -> void;
    auto emit_expr_negate(expr_negate const& exp, scope& scp) -> void;
    auto emit_expr_not(expr_not const& exp, scope& scp) -> void;
    auto emit_expr_call(expr_call const& exp, scope& scp, bool is_stmt) -> void;
    auto emit_expr_call_pointer(expr_pointer const& exp, scope& scp, bool is_stmt) -> void;
    auto emit_expr_call_function(expr_function const& exp, scope& scp, bool is_stmt) -> void;
    auto emit_expr_method(expr_method const& exp, scope& scp, bool is_stmt) -> void;
    auto emit_expr_method_pointer(expr_pointer const& exp, expr const& obj, scope& scp, bool is_stmt) -> void;
    auto emit_expr_method_function(expr_function const& exp, expr const& obj, scope& scp, bool is_stmt) -> void;
    auto emit_expr_add_array(expr_add_array const& exp, scope& scp) -> void;
    auto emit_expr_parameters(expr_parameters const& exp, scope& scp) -> void;
    auto emit_expr_arguments(expr_arguments const& exp, scope& scp) -> void;
    auto emit_expr_isdefined(expr_isdefined const& exp, scope& scp) -> void;
    auto emit_expr_istrue(expr_istrue const& exp, scope& scp) -> void;
    auto emit_expr_reference(expr_reference const& exp, scope& scp) -> void;
    auto emit_expr_size(expr_size const& exp, scope& scp) -> void;
    auto emit_expr_tuple(expr_tuple const& exp, scope& scp) -> void;
    auto emit_expr_variable_ref(expr const& exp, scope& scp, bool set) -> void;
    auto emit_expr_array_ref(expr_array const& exp, scope& scp, bool set) -> void;
    auto emit_expr_field_ref(expr_field const& exp, scope& scp, bool set) -> void;
    auto emit_expr_local_ref(expr_identifier const& exp, scope& scp, bool set) -> void;
    auto emit_expr_variable(expr const& exp, scope& scp) -> void;
    auto emit_expr_array(expr_array const& exp, scope& scp) -> void;
    auto emit_expr_field(expr_field const& exp, scope& scp) -> void;
    auto emit_expr_local(expr_identifier const& exp, scope& scp) -> void;
    auto emit_expr_object(expr const& exp, scope& scp) -> void;
    auto emit_expr_vector(expr_vector const& exp, scope& scp) -> void;
    auto emit_expr_animation(expr_animation const& exp) -> void;
    auto emit_expr_animtree(expr_animtree const& exp) -> void;
    auto emit_expr_istring(expr_istring const& exp) -> void;
    auto emit_expr_string(expr_string const& exp) -> void;
    auto emit_expr_float(expr_float const& exp) -> void;
    auto emit_expr_integer(expr_integer const& exp) -> void;
    auto emit_expr_false(expr_false const& exp) -> void;
    auto emit_expr_true(expr_true const& exp) -> void;
    auto emit_create_local_vars(scope& scp) -> void;
    auto emit_remove_local_vars(scope& scp) -> void;
    auto emit_opcode(opcode op) -> void;
    auto emit_opcode(opcode op, std::string const& data) -> void;
    auto emit_opcode(opcode op, std::vector<std::string> const& data) -> void;
    auto process_function(decl_function const& func) -> void;
    auto process_stmt(stmt const& stm, scope& scp) -> void;
    auto process_stmt_list(stmt_list const& stm, scope& scp) -> void;
    auto process_stmt_comp(stmt_comp const& stm, scope& scp) -> void;
    auto process_stmt_dev(stmt_dev const& stm, scope& scp) -> void;
    auto process_stmt_expr(stmt_expr const& stm, scope& scp) -> void;
    auto process_stmt_waittill(stmt_waittill const& stm, scope& scp) -> void;
    auto process_stmt_if(stmt_if const& stm, scope& scp) -> void;
    auto process_stmt_ifelse(stmt_ifelse const& stm, scope& scp) -> void;
    auto process_stmt_while(stmt_while const& stm, scope& scp) -> void;
    auto process_stmt_dowhile(stmt_dowhile const& stm, scope& scp) -> void;
    auto process_stmt_for(stmt_for const& stm, scope& scp) -> void;
    auto process_stmt_foreach(stmt_foreach const& stm, scope& scp) -> void;
    auto process_stmt_switch(stmt_switch const& stm, scope& scp) -> void;
    auto process_stmt_break(stmt_break const& stm, scope& scp) -> void;
    auto process_stmt_continue(stmt_continue const& stm, scope& scp) -> void;
    auto process_stmt_return(stmt_return const& stm, scope& scp) -> void;
    auto process_expr(expr const& exp, scope& scp) -> void;
    auto process_expr_tuple(expr_tuple const& exp, scope& scp) -> void;
    auto process_expr_parameters(expr_parameters const& exp, scope& scp) -> void;
    auto variable_register(expr_identifier const& exp, scope& scp) -> void;
    auto variable_initialized(expr_identifier const& exp, scope& scp) -> bool;
    auto variable_initialize(expr_identifier const& exp, scope& scp) -> u8;
    auto variable_create(expr_identifier const& exp, scope& scp) -> u8;
    auto variable_access(expr_identifier const& exp, scope& scp) -> u8;
    auto resolve_function_type(expr_function const& exp, std::string& path) -> call::type;
    auto resolve_reference_type(expr_reference const& exp, std::string& path, bool& method) -> call::type;
    auto is_constant_condition(expr const& exp) -> bool;
    auto insert_label(std::string const& label) -> void;
    auto create_label() -> std::string;
    auto insert_label() -> std::string;
};

} // namespace xsk::gsc
