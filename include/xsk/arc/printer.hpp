// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/arc/common/types.hpp"

namespace xsk::arc
{

struct printer
{
private:
    context* ctx_;
    std::vector<u8> buf_;
    u32 indent_ = 0;

public:
    explicit printer(context* ctx);
    auto print(assembly const& data) -> std::vector<u8>;
    auto print(program const& data) -> std::vector<u8>;

private:
    auto print_assembly(assembly const& data) -> void;
    auto print_function(function const& func) -> void;
    auto print_instruction(instruction const& inst) -> void;
    auto print_program(program const& data) -> void;
    auto print_include(include const& inc) -> void;
    auto print_decl(decl const& dec) -> void;
    auto print_decl_dev_begin(decl_dev_begin const& dec) -> void;
    auto print_decl_dev_end(decl_dev_end const& dec) -> void;
    auto print_decl_namespace(decl_namespace const& dec) -> void;
    auto print_decl_usingtree(decl_usingtree const& dec) -> void;
    auto print_decl_function(decl_function const& dec) -> void;
    auto print_decl_empty(decl_empty const& dec) -> void;
    auto print_stmt(stmt const& stm) -> void;
    auto print_stmt_empty(stmt_empty const& stm) -> void;
    auto print_stmt_list(stmt_list const& stm) -> void;
    auto print_stmt_comp(stmt_comp const& stm) -> void;
    auto print_stmt_dev(stmt_dev const& stm) -> void;
    auto print_stmt_expr(stmt_expr const& stm) -> void;
    auto print_stmt_endon(stmt_endon const& stm) -> void;
    auto print_stmt_notify(stmt_notify const& stm) -> void;
    auto print_stmt_wait(stmt_wait const& stm) -> void;
    auto print_stmt_waitrealtime(stmt_waitrealtime const& stm) -> void;
    auto print_stmt_waittill(stmt_waittill const& stm) -> void;
    auto print_stmt_waittillmatch(stmt_waittillmatch const& stm) -> void;
    auto print_stmt_waittillframeend(stmt_waittillframeend const& stm) -> void;
    auto print_stmt_if(stmt_if const& stm) -> void;
    auto print_stmt_ifelse(stmt_ifelse const& stm) -> void;
    auto print_stmt_while(stmt_while const& stm) -> void;
    auto print_stmt_dowhile(stmt_dowhile const& stm) -> void;
    auto print_stmt_for(stmt_for const& stm) -> void;
    auto print_stmt_foreach(stmt_foreach const& stm) -> void;
    auto print_stmt_switch(stmt_switch const& stm) -> void;
    auto print_stmt_case(stmt_case const& stm) -> void;
    auto print_stmt_default(stmt_default const& stm) -> void;
    auto print_stmt_break(stmt_break const& stm) -> void;
    auto print_stmt_continue(stmt_continue const& stm) -> void;
    auto print_stmt_return(stmt_return const& stm) -> void;
    auto print_stmt_breakpoint(stmt_breakpoint const& stm) -> void;
    auto print_stmt_prof_begin(stmt_prof_begin const& stm) -> void;
    auto print_stmt_prof_end(stmt_prof_end const& stm) -> void;
    auto print_stmt_jmp(stmt_jmp const& stm) -> void;
    auto print_stmt_jmp_back(stmt_jmp_back const& stm) -> void;
    auto print_stmt_jmp_cond(stmt_jmp_cond const& stm) -> void;
    auto print_stmt_jmp_true(stmt_jmp_true const& stm) -> void;
    auto print_stmt_jmp_false(stmt_jmp_false const& stm) -> void;
    auto print_stmt_jmp_switch(stmt_jmp_switch const& stm) -> void;
    auto print_stmt_jmp_endswitch(stmt_jmp_endswitch const& stm) -> void;
    auto print_stmt_jmp_dev(stmt_jmp_dev const& stm) -> void;
    auto print_expr(expr const& exp) -> void;
    auto print_expr_increment(expr_increment const& exp) -> void;
    auto print_expr_decrement(expr_decrement const& exp) -> void;
    auto print_expr_assign(expr_assign const& exp) -> void;
    auto print_expr_const(expr_const const& exp) -> void;
    auto print_expr_ternary(expr_ternary const& exp) -> void;
    auto print_expr_binary(expr_binary const& exp) -> void;
    auto print_expr_not(expr_not const& exp) -> void;
    auto print_expr_negate(expr_negate const& exp) -> void;
    auto print_expr_complement(expr_complement const& exp) -> void;
    auto print_expr_new(expr_new const& exp) -> void;
    auto print_expr_call(expr_call const& exp) -> void;
    auto print_expr_method(expr_method const& exp) -> void;
    auto print_call(call const& exp) -> void;
    auto print_expr_function(expr_function const& exp) -> void;
    auto print_expr_pointer(expr_pointer const& exp) -> void;
    auto print_expr_member(expr_member const& exp) -> void;
    auto print_expr_parameters(expr_parameters const& exp) -> void;
    auto print_expr_arguments(expr_arguments const& exp) -> void;
    auto print_expr_isdefined(expr_isdefined const& exp) -> void;
    auto print_expr_vectorscale(expr_vectorscale const& exp) -> void;
    auto print_expr_anglestoup(expr_anglestoup const& exp) -> void;
    auto print_expr_anglestoright(expr_anglestoright const& exp) -> void;
    auto print_expr_anglestoforward(expr_anglestoforward const& exp) -> void;
    auto print_expr_angleclamp180(expr_angleclamp180 const& exp) -> void;
    auto print_expr_vectortoangles(expr_vectortoangles const& exp) -> void;
    auto print_expr_abs(expr_abs const& exp) -> void;
    auto print_expr_gettime(expr_gettime const& exp) -> void;
    auto print_expr_getdvar(expr_getdvar const& exp) -> void;
    auto print_expr_getdvarint(expr_getdvarint const& exp) -> void;
    auto print_expr_getdvarfloat(expr_getdvarfloat const& exp) -> void;
    auto print_expr_getdvarvector(expr_getdvarvector const& exp) -> void;
    auto print_expr_getdvarcolorred(expr_getdvarcolorred const& exp) -> void;
    auto print_expr_getdvarcolorgreen(expr_getdvarcolorgreen const& exp) -> void;
    auto print_expr_getdvarcolorblue(expr_getdvarcolorblue const& exp) -> void;
    auto print_expr_getdvarcoloralpha(expr_getdvarcoloralpha const& exp) -> void;
    auto print_expr_getfirstarraykey(expr_getfirstarraykey const& exp) -> void;
    auto print_expr_getnextarraykey(expr_getnextarraykey const& exp) -> void;
    auto print_expr_reference(expr_reference const& exp) -> void;
    auto print_expr_array(expr_array const& exp) -> void;
    auto print_expr_field(expr_field const& exp) -> void;
    auto print_expr_size(expr_size const& exp) -> void;
    auto print_expr_paren(expr_paren const& exp) -> void;
    auto print_expr_ellipsis(expr_ellipsis const& exp) -> void;
    auto print_expr_empty_array(expr_empty_array const& exp) -> void;
    auto print_expr_undefined(expr_undefined const& exp) -> void;
    auto print_expr_game(expr_game const& exp) -> void;
    auto print_expr_self(expr_self const& exp) -> void;
    auto print_expr_anim(expr_anim const& exp) -> void;
    auto print_expr_level(expr_level const& exp) -> void;
    auto print_expr_world(expr_world const& exp) -> void;
    auto print_expr_classes(expr_classes const& exp) -> void;
    auto print_expr_animation(expr_animation const& exp) -> void;
    auto print_expr_animtree(expr_animtree const& exp) -> void;
    auto print_expr_identifier(expr_identifier const& exp) -> void;
    auto print_expr_path(expr_path const& exp) -> void;
    auto print_expr_istring(expr_istring const& exp) -> void;
    auto print_expr_string(expr_string const& exp) -> void;
    auto print_expr_hash(expr_hash const& exp) -> void;
    auto print_expr_vector(expr_vector const& exp) -> void;
    auto print_expr_float(expr_float const& exp) -> void;
    auto print_expr_integer(expr_integer const& exp) -> void;
    auto print_expr_false(expr_false const& exp) -> void;
    auto print_expr_true(expr_true const& exp) -> void;
};

} // namespace xsk::arc
