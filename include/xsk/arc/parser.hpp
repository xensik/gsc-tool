// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/arc/common/types.hpp"
#include "xsk/arc/preprocessor.hpp"

namespace xsk::arc
{

struct parser
{
private:
    context* ctx_;
    preprocessor ppr_;
    token tok_;
    token next_;
    bool has_next_;
    u32 index_;

public:
    parser(context* ctx);
    auto parse_assembly(buffer const& data) -> assembly::ptr;
    auto parse_assembly(std::vector<u8> const& data) -> assembly::ptr;
    auto parse_assembly(u8 const* data, usize size) -> assembly::ptr;
    auto parse_source(std::string const& name, buffer const& data) -> program::ptr;
    auto parse_source(std::string const& name, std::vector<u8> const& data) -> program::ptr;
    auto parse_source(std::string const& name, u8 const* data, usize size) -> program::ptr;

private:
    auto parse_program() -> program::ptr;
    auto parse_include() -> include::ptr;
    auto parse_inline() -> void;
    auto parse_declaration() -> decl::ptr;
    auto parse_decl_usingtree() -> decl::ptr;
    auto parse_decl_function() -> decl::ptr;
    auto parse_stmt() -> stmt::ptr;
    auto parse_stmt_or_dev() -> stmt::ptr;
    auto parse_stmt_or_dev_list() -> stmt_list::ptr;
    auto parse_stmt_list() -> stmt_list::ptr;
    auto parse_stmt_comp() -> stmt_comp::ptr;
    auto parse_stmt_dev() -> stmt::ptr;
    auto parse_stmt_expr() -> stmt_expr::ptr;
    auto parse_stmt_for_expr() -> stmt_expr::ptr;
    auto parse_stmt_call_or_assign() -> stmt::ptr;
    auto parse_stmt_const() -> stmt::ptr;
    auto parse_stmt_endon(expr::ptr obj) -> stmt::ptr;
    auto parse_stmt_notify(expr::ptr obj) -> stmt::ptr;
    auto parse_stmt_wait() -> stmt::ptr;
    auto parse_stmt_waitrealtime() -> stmt::ptr;
    auto parse_stmt_waittill(expr::ptr obj) -> stmt::ptr;
    auto parse_stmt_waittillmatch(expr::ptr obj) -> stmt::ptr;
    auto parse_stmt_waittillframeend() -> stmt::ptr;
    auto parse_stmt_if() -> stmt::ptr;
    auto parse_stmt_while() -> stmt::ptr;
    auto parse_stmt_dowhile() -> stmt::ptr;
    auto parse_stmt_for() -> stmt::ptr;
    auto parse_stmt_foreach() -> stmt::ptr;
    auto parse_stmt_switch() -> stmt::ptr;
    auto parse_stmt_case() -> stmt::ptr;
    auto parse_stmt_default() -> stmt::ptr;
    auto parse_stmt_break() -> stmt::ptr;
    auto parse_stmt_continue() -> stmt::ptr;
    auto parse_stmt_return() -> stmt::ptr;
    auto parse_stmt_prof_begin() -> stmt::ptr;
    auto parse_stmt_prof_end() -> stmt::ptr;
    auto parse_expr() -> expr::ptr;
    auto parse_expr_ternary() -> expr::ptr;
    auto parse_expr_or() -> expr::ptr;
    auto parse_expr_and() -> expr::ptr;
    auto parse_expr_bw_or() -> expr::ptr;
    auto parse_expr_bw_xor() -> expr::ptr;
    auto parse_expr_bw_and() -> expr::ptr;
    auto parse_expr_equality() -> expr::ptr;
    auto parse_expr_relational() -> expr::ptr;
    auto parse_expr_shift() -> expr::ptr;
    auto parse_expr_additive() -> expr::ptr;
    auto parse_expr_multiplicative() -> expr::ptr;
    auto parse_expr_unary() -> expr::ptr;
    auto parse_expr_primary() -> expr::ptr;
    auto parse_expr_object() -> expr::ptr;
    auto parse_expr_postfix(expr::ptr base) -> expr::ptr;
    auto parse_expr_call(call::mode mode) -> call::ptr;
    auto parse_expr_function(call::mode mode) -> call::ptr;
    auto parse_expr_pointer(call::mode mode) -> call::ptr;
    auto parse_expr_arguments() -> expr_arguments::ptr;
    auto parse_expr_arguments_no_empty() -> expr_arguments::ptr;
    auto parse_expr_parameters() -> expr_parameters::ptr;
    auto parse_expr_reference() -> expr::ptr;
    auto parse_expr_isdefined() -> expr::ptr;
    auto parse_expr_abs() -> expr::ptr;
    auto parse_expr_gettime() -> expr::ptr;
    auto parse_expr_getdvar() -> expr::ptr;
    auto parse_expr_getdvarint() -> expr::ptr;
    auto parse_expr_getdvarfloat() -> expr::ptr;
    auto parse_expr_getdvarvector() -> expr::ptr;
    auto parse_expr_getdvarcolorred() -> expr::ptr;
    auto parse_expr_getdvarcolorgreen() -> expr::ptr;
    auto parse_expr_getdvarcolorblue() -> expr::ptr;
    auto parse_expr_getdvarcoloralpha() -> expr::ptr;
    auto parse_expr_getfirstarraykey() -> expr::ptr;
    auto parse_expr_getnextarraykey() -> expr::ptr;
    auto parse_expr_vectorscale() -> expr::ptr;
    auto parse_expr_anglestoup() -> expr::ptr;
    auto parse_expr_anglestoright() -> expr::ptr;
    auto parse_expr_anglestoforward() -> expr::ptr;
    auto parse_expr_angleclamp180() -> expr::ptr;
    auto parse_expr_vectortoangles() -> expr::ptr;
    auto parse_expr_paren_or_vector() -> expr::ptr;
    auto parse_expr_identifier() -> expr_identifier::ptr;
    auto parse_expr_identifier_nosize() -> expr_identifier::ptr;
    auto parse_expr_path() -> expr_path::ptr;
    auto parse_expr_string() -> expr_string::ptr;
    auto parse_expr_animation() -> expr::ptr;
    auto parse_switch(stmt_switch& stm) -> void;
    auto parse_assign_op() -> expr_assign::op;
    auto is_assign_op() -> bool;
    auto is_call_start() -> bool;
    auto is_lvalue(expr const& e) -> bool;
    auto is_no_call_chain(expr const& e) -> bool;
    auto is_call_or_method(expr const& e) -> bool;
    auto check(token::kind k) -> bool;
    auto match(token::kind k) -> bool;
    auto expect(token::kind k) -> token;
    auto peek() -> token&;
    auto advance() -> token;
    auto read_token() -> token;
    [[noreturn]] auto error(location const& loc, std::string const& msg) -> void;
    [[noreturn]] auto error(std::string const& msg) -> void;
};

} // namespace xsk::arc
