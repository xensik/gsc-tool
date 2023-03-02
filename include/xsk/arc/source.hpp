// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "common/types.hpp"

namespace xsk::arc
{

class source
{
    context* ctx_;
    std::vector<u8> buf_;
    u32 indent_;

public:
    source(context* ctx);
    auto dump(assembly const& data) -> std::vector<u8>;
    auto dump(program const& data) -> std::vector<u8>;

private:
    auto dump_assembly(assembly const& data) -> void;
    auto dump_function(function const& func) -> void;
    auto dump_instruction(instruction const& inst) -> void;
    auto dump_program(program const& data) -> void;
    auto dump_include(include const& inc) -> void;
    auto dump_decl(decl const& dec) -> void;
    auto dump_decl_dev_begin(decl_dev_begin const& dec) -> void;
    auto dump_decl_dev_end(decl_dev_end const& dec) -> void;
    auto dump_decl_namespace(decl_namespace const& dec) -> void;
    auto dump_decl_usingtree(decl_usingtree const& dec) -> void;
    auto dump_decl_function(decl_function const& dec) -> void;
    auto dump_stmt(stmt const& stm) -> void;
    auto dump_stmt_list(stmt_list const& stm) -> void;
    auto dump_stmt_comp(stmt_comp const& stm) -> void;
    auto dump_stmt_dev(stmt_dev const& stm) -> void;
    auto dump_stmt_expr(stmt_expr const& stm) -> void;
    auto dump_stmt_call(stmt_call const& stm) -> void;
    auto dump_stmt_const(stmt_const const& stm) -> void;
    auto dump_stmt_assign(stmt_assign const& stm) -> void;
    auto dump_stmt_endon(stmt_endon const& stm) -> void;
    auto dump_stmt_notify(stmt_notify const& stm) -> void;
    auto dump_stmt_realwait(stmt_realwait const& stm) -> void;
    auto dump_stmt_wait(stmt_wait const& stm) -> void;
    auto dump_stmt_waittill(stmt_waittill const& stm) -> void;
    auto dump_stmt_waittillmatch(stmt_waittillmatch const& stm) -> void;
    auto dump_stmt_waittillframeend(stmt_waittillframeend const& stm) -> void;
    auto dump_stmt_if(stmt_if const& stm) -> void;
    auto dump_stmt_ifelse(stmt_ifelse const& stm) -> void;
    auto dump_stmt_while(stmt_while const& stm) -> void;
    auto dump_stmt_dowhile(stmt_dowhile const& stm) -> void;
    auto dump_stmt_for(stmt_for const& stm) -> void;
    auto dump_stmt_foreach(stmt_foreach const& stm) -> void;
    auto dump_stmt_switch(stmt_switch const& stm) -> void;
    auto dump_stmt_case(stmt_case const& stm) -> void;
    auto dump_stmt_default(stmt_default const& stm) -> void;
    auto dump_stmt_break(stmt_break const& stm) -> void;
    auto dump_stmt_continue(stmt_continue const& stm) -> void;
    auto dump_stmt_return(stmt_return const& stm) -> void;
    auto dump_stmt_breakpoint(stmt_breakpoint const& stm) -> void;
    auto dump_stmt_prof_begin(stmt_prof_begin const& stm) -> void;
    auto dump_stmt_prof_end(stmt_prof_end const& stm) -> void;
    auto dump_expr(expr const& exp) -> void;
    auto dump_expr_increment(expr_increment const& exp) -> void;
    auto dump_expr_decrement(expr_decrement const& exp) -> void;
    auto dump_expr_assign_equal(expr_assign_equal const& exp) -> void;
    auto dump_expr_assign_add(expr_assign_add const& exp) -> void;
    auto dump_expr_assign_sub(expr_assign_sub const& exp) -> void;
    auto dump_expr_assign_mul(expr_assign_mul const& exp) -> void;
    auto dump_expr_assign_div(expr_assign_div const& exp) -> void;
    auto dump_expr_assign_mod(expr_assign_mod const& exp) -> void;
    auto dump_expr_assign_shift_left(expr_assign_shift_left const& exp) -> void;
    auto dump_expr_assign_shift_right(expr_assign_shift_right const& exp) -> void;
    auto dump_expr_assign_bitwise_or(expr_assign_bitwise_or const& exp) -> void;
    auto dump_expr_assign_bitwise_and(expr_assign_bitwise_and const& exp) -> void;
    auto dump_expr_assign_bitwise_exor(expr_assign_bitwise_exor const& exp) -> void;
    auto dump_expr_ternary(expr_ternary const& exp) -> void;
    auto dump_expr_or(expr_or const& exp) -> void;
    auto dump_expr_and(expr_and const& exp) -> void;
    auto dump_expr_super_equal(expr_super_equal const& exp) -> void;
    auto dump_expr_super_not_equal(expr_super_not_equal const& exp) -> void;
    auto dump_expr_equality(expr_equality const& exp) -> void;
    auto dump_expr_inequality(expr_inequality const& exp) -> void;
    auto dump_expr_less_equal(expr_less_equal const& exp) -> void;
    auto dump_expr_greater_equal(expr_greater_equal const& exp) -> void;
    auto dump_expr_less(expr_less const& exp) -> void;
    auto dump_expr_greater(expr_greater const& exp) -> void;
    auto dump_expr_add(expr_add const& exp) -> void;
    auto dump_expr_sub(expr_sub const& exp) -> void;
    auto dump_expr_mul(expr_mul const& exp) -> void;
    auto dump_expr_div(expr_div const& exp) -> void;
    auto dump_expr_mod(expr_mod const& exp) -> void;
    auto dump_expr_shift_left(expr_shift_left const& exp) -> void;
    auto dump_expr_shift_right(expr_shift_right const& exp) -> void;
    auto dump_expr_bitwise_or(expr_bitwise_or const& exp) -> void;
    auto dump_expr_bitwise_and(expr_bitwise_and const& exp) -> void;
    auto dump_expr_bitwise_exor(expr_bitwise_exor const& exp) -> void;
    auto dump_expr_not(expr_not const& exp) -> void;
    auto dump_expr_negate(expr_negate const& exp) -> void;
    auto dump_expr_complement(expr_complement const& exp) -> void;
    auto dump_expr_new(expr_new const& exp) -> void;
    auto dump_expr_call(expr_call const& exp) -> void;
    auto dump_expr_method(expr_method const& exp) -> void;
    auto dump_call(call const& exp) -> void;
    auto dump_expr_function(expr_function const& exp) -> void;
    auto dump_expr_pointer(expr_pointer const& exp) -> void;
    auto dump_expr_member(expr_member const& exp) -> void;
    auto dump_expr_parameters(expr_parameters const& exp) -> void;
    auto dump_expr_arguments(expr_arguments const& exp) -> void;
    auto dump_expr_isdefined(expr_isdefined const& exp) -> void;
    auto dump_expr_vectorscale(expr_vectorscale const& exp) -> void;
    auto dump_expr_anglestoup(expr_anglestoup const& exp) -> void;
    auto dump_expr_anglestoright(expr_anglestoright const& exp) -> void;
    auto dump_expr_anglestoforward(expr_anglestoforward const& exp) -> void;
    auto dump_expr_angleclamp180(expr_angleclamp180 const& exp) -> void;
    auto dump_expr_vectortoangles(expr_vectortoangles const& exp) -> void;
    auto dump_expr_abs(expr_abs const& exp) -> void;
    auto dump_expr_gettime(expr_gettime const& exp) -> void;
    auto dump_expr_getdvar(expr_getdvar const& exp) -> void;
    auto dump_expr_getdvarint(expr_getdvarint const& exp) -> void;
    auto dump_expr_getdvarfloat(expr_getdvarfloat const& exp) -> void;
    auto dump_expr_getdvarvector(expr_getdvarvector const& exp) -> void;
    auto dump_expr_getdvarcolorred(expr_getdvarcolorred const& exp) -> void;
    auto dump_expr_getdvarcolorgreen(expr_getdvarcolorgreen const& exp) -> void;
    auto dump_expr_getdvarcolorblue(expr_getdvarcolorblue const& exp) -> void;
    auto dump_expr_getdvarcoloralpha(expr_getdvarcoloralpha const& exp) -> void;
    auto dump_expr_getfirstarraykey(expr_getfirstarraykey const& exp) -> void;
    auto dump_expr_getnextarraykey(expr_getnextarraykey const& exp) -> void;
    auto dump_expr_reference(expr_reference const& exp) -> void;
    auto dump_expr_array(expr_array const& exp) -> void;
    auto dump_expr_field(expr_field const& exp) -> void;
    auto dump_expr_size(expr_size const& exp) -> void;
    auto dump_expr_paren(expr_paren const& exp) -> void;
    auto dump_expr_empty_array(expr_empty_array const& exp) -> void;
    auto dump_expr_undefined(expr_undefined const& exp) -> void;
    auto dump_expr_game(expr_game const& exp) -> void;
    auto dump_expr_self(expr_self const& exp) -> void;
    auto dump_expr_anim(expr_anim const& exp) -> void;
    auto dump_expr_level(expr_level const& exp) -> void;
    auto dump_expr_world(expr_world const& exp) -> void;
    auto dump_expr_classes(expr_classes const& exp) -> void;
    auto dump_expr_animation(expr_animation const& exp) -> void;
    auto dump_expr_animtree(expr_animtree const& exp) -> void;
    auto dump_expr_identifier(expr_identifier const& exp) -> void;
    auto dump_expr_path(expr_path const& exp) -> void;
    auto dump_expr_istring(expr_istring const& exp) -> void;
    auto dump_expr_string(expr_string const& exp) -> void;
    auto dump_expr_hash(expr_hash const& exp) -> void;
    auto dump_expr_vector(expr_vector const& exp) -> void;
    auto dump_expr_float(expr_float const& exp) -> void;
    auto dump_expr_integer(expr_integer const& exp) -> void;
    auto dump_expr_false(expr_false const& exp) -> void;
    auto dump_expr_true(expr_true const& exp) -> void;
    auto dump_asm_loc(asm_loc const& exp) -> void;
    auto dump_asm_jmp(asm_jmp const& exp) -> void;
    auto dump_asm_jmp_back(asm_jmp_back const& exp) -> void;
    auto dump_asm_jmp_cond(asm_jmp_cond const& exp) -> void;
    auto dump_asm_jmp_true(asm_jmp_true const& exp) -> void;
    auto dump_asm_jmp_false(asm_jmp_false const& exp) -> void;
    auto dump_asm_switch(asm_switch const& exp) -> void;
    auto dump_asm_endswitch(asm_endswitch const& exp) -> void;
    auto dump_asm_prescriptcall(asm_prescriptcall const& exp) -> void;
    auto dump_asm_voidcodepos(asm_voidcodepos const& exp) -> void;
    auto dump_asm_dev(asm_dev const& exp) -> void;
};

} // namespace xsk::arc
