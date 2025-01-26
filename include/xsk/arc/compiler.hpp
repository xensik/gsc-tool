// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/arc/common/types.hpp"

namespace xsk::arc
{

struct compiler
{
private:
    context* ctx_;
    assembly::ptr assembly_;
    function::ptr function_;
    std::vector<std::string> localfuncs_;
    std::vector<std::string> stackframe_;
    std::vector<scope> scopes_;
    std::unordered_map<std::string, expr const*> constants_;
    std::string animtree_;
    sourcepos debug_pos_;
    usize index_;
    usize label_idx_;
    bool can_break_;
    bool can_continue_;
    bool developer_thread_;

public:
    explicit compiler(context* ctx);
    auto compile(program const& data) -> assembly::ptr;
    auto compile(std::string const& file, std::vector<u8>& data) -> assembly::ptr;

private:
    auto emit_program(program const& prog) -> void;
    auto emit_include(include const& inc) -> void;
    auto emit_decl(decl const& dec) -> void;
    auto emit_decl_usingtree(decl_usingtree const& animtree) -> void;
    auto emit_decl_function(decl_function const& func) -> void;
    auto emit_stmt(stmt const& stm) -> void;
    auto emit_stmt_list(stmt_list const& stm) -> void;
    auto emit_stmt_comp(stmt_comp const& stm) -> void;
    auto emit_stmt_dev(stmt_dev const& stm) -> void;
    auto emit_stmt_expr(stmt_expr const& stm) -> void;
    auto emit_stmt_endon(stmt_endon const& stm) -> void;
    auto emit_stmt_notify(stmt_notify const& stm) -> void;
    auto emit_stmt_wait(stmt_wait const& stm) -> void;
    auto emit_stmt_waitrealtime(stmt_waitrealtime const& stm) -> void;
    auto emit_stmt_waittill(stmt_waittill const& stm) -> void;
    auto emit_stmt_waittillmatch(stmt_waittillmatch const& stm) -> void;
    auto emit_stmt_waittillframeend(stmt_waittillframeend const& stm) -> void;
    auto emit_stmt_if(stmt_if const& stm) -> void;
    auto emit_stmt_ifelse(stmt_ifelse const& stm) -> void;
    auto emit_stmt_while(stmt_while const& stm) -> void;
    auto emit_stmt_dowhile(stmt_dowhile const& stm) -> void;
    auto emit_stmt_for(stmt_for const& stm) -> void;
    auto emit_stmt_foreach(stmt_foreach const& stm) -> void;
    auto emit_stmt_switch(stmt_switch const& stm) -> void;
    auto emit_stmt_case(stmt_case const& stm) -> void;
    auto emit_stmt_default(stmt_default const& stm) -> void;
    auto emit_stmt_break(stmt_break const& stm) -> void;
    auto emit_stmt_continue(stmt_continue const& stm) -> void;
    auto emit_stmt_return(stmt_return const& stm) -> void;
    auto emit_stmt_breakpoint(stmt_breakpoint const& stm) -> void;
    auto emit_stmt_prof_begin(stmt_prof_begin const& stm) -> void;
    auto emit_stmt_prof_end(stmt_prof_end const& stm) -> void;
    auto emit_expr(expr const& exp) -> void;
    auto emit_expr_const(expr_const const& exp) -> void;
    auto emit_expr_assign(expr_assign const& exp) -> void;
    auto emit_expr_clear(expr const& exp) -> void;
    auto emit_expr_increment(expr_increment const& exp, bool is_stmt) -> void;
    auto emit_expr_decrement(expr_decrement const& exp, bool is_stmt) -> void;
    auto emit_expr_ternary(expr_ternary const& exp) -> void;
    auto emit_expr_binary(expr_binary const& exp) -> void;
    auto emit_expr_complement(expr_complement const& exp) -> void;
    auto emit_expr_negate(expr_negate const& exp) -> void;
    auto emit_expr_not(expr_not const& exp) -> void;
    auto emit_expr_call(expr_call const& exp, bool is_stmt) -> void;
    auto emit_expr_call_pointer(expr_pointer const& exp, bool is_stmt) -> void;
    auto emit_expr_call_function(expr_function const& exp, bool is_stmt) -> void;
    auto emit_expr_method(expr_method const& exp, bool is_stmt) -> void;
    auto emit_expr_method_pointer(expr_pointer const& exp, expr const& obj, bool is_stmt) -> void;
    auto emit_expr_method_function(expr_function const& exp, expr const& obj, bool is_stmt) -> void;
    auto emit_expr_parameters(expr_parameters const& exp) -> void;
    auto emit_expr_arguments(expr_arguments const& exp) -> void;
    auto emit_expr_isdefined(expr_isdefined const& exp) -> void;
    auto emit_expr_vectorscale(expr_vectorscale const& exp) -> void;
    auto emit_expr_anglestoup(expr_anglestoup const& exp) -> void;
    auto emit_expr_anglestoright(expr_anglestoright const& exp) -> void;
    auto emit_expr_anglestoforward(expr_anglestoforward const& exp) -> void;
    auto emit_expr_angleclamp180(expr_angleclamp180 const& exp) -> void;
    auto emit_expr_vectortoangles(expr_vectortoangles const& exp) -> void;
    auto emit_expr_abs(expr_abs const& exp) -> void;
    auto emit_expr_gettime(expr_gettime const& exp) -> void;
    auto emit_expr_getdvar(expr_getdvar const& exp) -> void;
    auto emit_expr_getdvarint(expr_getdvarint const& exp) -> void;
    auto emit_expr_getdvarfloat(expr_getdvarfloat const& exp) -> void;
    auto emit_expr_getdvarvector(expr_getdvarvector const& exp) -> void;
    auto emit_expr_getdvarcolorred(expr_getdvarcolorred const& exp) -> void;
    auto emit_expr_getdvarcolorgreen(expr_getdvarcolorgreen const& exp) -> void;
    auto emit_expr_getdvarcolorblue(expr_getdvarcolorblue const& exp) -> void;
    auto emit_expr_getdvarcoloralpha(expr_getdvarcoloralpha const& exp) -> void;
    auto emit_expr_getfirstarraykey(expr_getfirstarraykey const& exp) -> void;
    auto emit_expr_getnextarraykey(expr_getnextarraykey const& exp) -> void;
    auto emit_expr_reference(expr_reference const& exp) -> void;
    auto emit_expr_size(expr_size const& exp) -> void;
    auto emit_expr_variable_ref(expr const& exp, bool set) -> void;
    auto emit_expr_array_ref(expr_array const& exp, bool set) -> void;
    auto emit_expr_field_ref(expr_field const& exp, bool set) -> void;
    auto emit_expr_local_ref(expr_identifier const& exp, bool set) -> void;
    auto emit_expr_variable(expr const& exp) -> void;
    auto emit_expr_array(expr_array const& exp) -> void;
    auto emit_expr_field(expr_field const& exp) -> void;
    auto emit_expr_local(expr_identifier const& exp) -> void;
    auto emit_expr_object(expr const& exp) -> void;
    auto emit_expr_vector(expr_vector const& exp) -> void;
    auto emit_expr_animation(expr_animation const& exp) -> void;
    auto emit_expr_animtree(expr_animtree const& exp) -> void;
    auto emit_expr_istring(expr_istring const& exp) -> void;
    auto emit_expr_string(expr_string const& exp) -> void;
    auto emit_expr_hash(expr_hash const& exp) -> void;
    auto emit_expr_float(expr_float const& exp) -> void;
    auto emit_expr_integer(expr_integer const& exp) -> void;
    auto emit_expr_false(expr_false const& exp) -> void;
    auto emit_expr_true(expr_true const& exp) -> void;
    auto emit_opcode(opcode op) -> void;
    auto emit_opcode(opcode op, std::string const& data) -> void;
    auto emit_opcode(opcode op, std::vector<std::string> const& data) -> void;
    auto process_function(decl_function const& func) -> void;
    auto process_stmt(stmt const& stm) -> void;
    auto process_stmt_list(stmt_list const& stm) -> void;
    auto process_stmt_comp(stmt_comp const& stm) -> void;
    auto process_stmt_dev(stmt_dev const& stm) -> void;
    auto process_stmt_expr(stmt_expr const& stm) -> void;
    auto process_stmt_waittill(stmt_waittill const& stm) -> void;
    auto process_stmt_if(stmt_if const& stm) -> void;
    auto process_stmt_ifelse(stmt_ifelse const& stm) -> void;
    auto process_stmt_while(stmt_while const& stm) -> void;
    auto process_stmt_dowhile(stmt_dowhile const& stm) -> void;
    auto process_stmt_for(stmt_for const& stm) -> void;
    auto process_stmt_foreach(stmt_foreach const& stm) -> void;
    auto process_stmt_switch(stmt_switch const& stm) -> void;
    auto process_expr(expr const& exp) -> void;
    auto process_expr_parameters(expr_parameters const& exp) -> void;
    auto variable_register(expr_identifier const& exp) -> void;
    auto variable_access(expr_identifier const& exp) -> u8;
    auto is_constant_condition(expr const& exp) -> bool;
    auto insert_label(std::string const& label) -> void;
    auto insert_label() -> std::string;
    auto create_label() -> std::string;
};

} // namespace xsk::arc
