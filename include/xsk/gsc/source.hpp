// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/gsc/common/types.hpp"

namespace xsk::gsc
{

struct source
{
private:
    context* ctx_;
    std::vector<u8> buf_;
    u32 indent_ = 0;

public:
    explicit source(context* ctx);
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
    auto dump_decl_usingtree(decl_usingtree const& dec) -> void;
    auto dump_decl_constant(decl_constant const& dec) -> void;
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
    auto dump_stmt_waitframe(stmt_waitframe const& stm) -> void;
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
    auto dump_stmt_assert(stmt_assert const& stm) -> void;
    auto dump_stmt_assertex(stmt_assertex const& stm) -> void;
    auto dump_stmt_assertmsg(stmt_assertmsg const& stm) -> void;
    auto dump_stmt_create(stmt_create const& stm) -> void;
    auto dump_stmt_remove(stmt_remove const& stm) -> void;
    auto dump_stmt_clear(stmt_clear const& stm) -> void;
    auto dump_stmt_jmp(stmt_jmp const& stm) -> void;
    auto dump_stmt_jmp_back(stmt_jmp_back const& stm) -> void;
    auto dump_stmt_jmp_cond(stmt_jmp_cond const& stm) -> void;
    auto dump_stmt_jmp_true(stmt_jmp_true const& stm) -> void;
    auto dump_stmt_jmp_false(stmt_jmp_false const& stm) -> void;
    auto dump_stmt_jmp_switch(stmt_jmp_switch const& stm) -> void;
    auto dump_stmt_jmp_endswitch(stmt_jmp_endswitch const& stm) -> void;
    auto dump_expr(expr const& exp) -> void;
    auto dump_expr_increment(expr_increment const& exp) -> void;
    auto dump_expr_decrement(expr_decrement const& exp) -> void;
    auto dump_expr_assign(expr_assign const& exp) -> void;
    auto dump_expr_ternary(expr_ternary const& exp) -> void;
    auto dump_expr_binary(expr_binary const& exp) -> void;
    auto dump_expr_not(expr_not const& exp) -> void;
    auto dump_expr_negate(expr_negate const& exp) -> void;
    auto dump_expr_complement(expr_complement const& exp) -> void;
    auto dump_expr_call(expr_call const& exp) -> void;
    auto dump_expr_method(expr_method const& exp) -> void;
    auto dump_call(call const& exp) -> void;
    auto dump_expr_function(expr_function const& exp) -> void;
    auto dump_expr_pointer(expr_pointer const& exp) -> void;
    auto dump_expr_add_array(expr_add_array const& exp) -> void;
    auto dump_expr_parameters(expr_parameters const& exp) -> void;
    auto dump_expr_arguments(expr_arguments const& exp) -> void;
    auto dump_expr_isdefined(expr_isdefined const& exp) -> void;
    auto dump_expr_istrue(expr_istrue const& exp) -> void;
    auto dump_expr_reference(expr_reference const& exp) -> void;
    auto dump_expr_tuple(expr_tuple const& exp) -> void;
    auto dump_expr_array(expr_array const& exp) -> void;
    auto dump_expr_field(expr_field const& exp) -> void;
    auto dump_expr_size(expr_size const& exp) -> void;
    auto dump_expr_paren(expr_paren const& exp) -> void;
    auto dump_expr_thisthread(expr_thisthread const& exp) -> void;
    auto dump_expr_empty_array(expr_empty_array const& exp) -> void;
    auto dump_expr_undefined(expr_undefined const& exp) -> void;
    auto dump_expr_game(expr_game const& exp) -> void;
    auto dump_expr_self(expr_self const& exp) -> void;
    auto dump_expr_anim(expr_anim const& exp) -> void;
    auto dump_expr_level(expr_level const& exp) -> void;
    auto dump_expr_animation(expr_animation const& exp) -> void;
    auto dump_expr_animtree(expr_animtree const& exp) -> void;
    auto dump_expr_identifier(expr_identifier const& exp) -> void;
    auto dump_expr_path(expr_path const& exp) -> void;
    auto dump_expr_istring(expr_istring const& exp) -> void;
    auto dump_expr_string(expr_string const& exp) -> void;
    auto dump_expr_vector(expr_vector const& exp) -> void;
    auto dump_expr_float(expr_float const& exp) -> void;
    auto dump_expr_integer(expr_integer const& exp) -> void;
    auto dump_expr_false(expr_false const& exp) -> void;
    auto dump_expr_true(expr_true const& exp) -> void;
    auto dump_expr_var_create(expr_var_create const& exp) -> void;
    auto dump_expr_var_access(expr_var_access const& exp) -> void;
};

} // namespace xsk::gsc
