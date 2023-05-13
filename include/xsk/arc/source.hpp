// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/arc/common/types.hpp"

namespace xsk::arc
{

class source
{
    context* ctx_;
    std::vector<u8> buf_;
    u32 indent_;

public:
    source(context* ctx);
    auto parse_assembly(buffer const& data) -> assembly::ptr;
    auto parse_assembly(std::vector<u8> const& data) -> assembly::ptr;
    auto parse_assembly(u8 const* data, usize size) -> assembly::ptr;
    auto parse_program(std::string const& name, buffer const& data) -> program::ptr;
    auto parse_program(std::string const& name, std::vector<u8> const& data) -> program::ptr;
    auto parse_program(std::string const& name, u8 const* data, usize size) -> program::ptr;
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
    auto dump_decl_empty(decl_empty const& dec) -> void;
    auto dump_stmt(stmt const& stm) -> void;
    auto dump_stmt_empty(stmt_empty const& stm) -> void;
    auto dump_stmt_list(stmt_list const& stm) -> void;
    auto dump_stmt_comp(stmt_comp const& stm) -> void;
    auto dump_stmt_dev(stmt_dev const& stm) -> void;
    auto dump_stmt_expr(stmt_expr const& stm) -> void;
    auto dump_stmt_endon(stmt_endon const& stm) -> void;
    auto dump_stmt_notify(stmt_notify const& stm) -> void;
    auto dump_stmt_wait(stmt_wait const& stm) -> void;
    auto dump_stmt_waittill(stmt_waittill const& stm) -> void;
    auto dump_stmt_waittillmatch(stmt_waittillmatch const& stm) -> void;
    auto dump_stmt_waittillframeend(stmt_waittillframeend const& stm) -> void;
    auto dump_stmt_waitrealtime(stmt_waitrealtime const& stm) -> void;
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
    auto dump_stmt_jmp(stmt_jmp const& stm) -> void;
    auto dump_stmt_jmp_back(stmt_jmp_back const& stm) -> void;
    auto dump_stmt_jmp_cond(stmt_jmp_cond const& stm) -> void;
    auto dump_stmt_jmp_true(stmt_jmp_true const& stm) -> void;
    auto dump_stmt_jmp_false(stmt_jmp_false const& stm) -> void;
    auto dump_stmt_jmp_switch(stmt_jmp_switch const& stm) -> void;
    auto dump_stmt_jmp_endswitch(stmt_jmp_endswitch const& stm) -> void;
    auto dump_stmt_jmp_dev(stmt_jmp_dev const& stm) -> void;
    auto dump_expr(expr const& exp) -> void;
    auto dump_expr_increment(expr_increment const& exp) -> void;
    auto dump_expr_decrement(expr_decrement const& exp) -> void;
    auto dump_expr_assign(expr_assign const& exp) -> void;
    auto dump_expr_const(expr_const const& exp) -> void;
    auto dump_expr_ternary(expr_ternary const& exp) -> void;
    auto dump_expr_binary(expr_binary const& exp) -> void;
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
    auto dump_expr_ellipsis(expr_ellipsis const& exp) -> void;
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
};

} // namespace xsk::arc
