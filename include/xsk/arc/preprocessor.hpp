// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/arc/common/types.hpp"
#include "xsk/arc/lexer.hpp"

namespace xsk::arc
{

struct preprocessor
{
private:
    context* ctx_;
    std::stack<lexer> lexer_;
    std::vector<std::string> includes_;
    std::stack<std::stack<directive>> indents_;
    std::unordered_map<std::string_view, directive::kind> directives_;
    std::unordered_map<std::string, define> defines_;
    std::set<std::string> reject_;
    std::deque<token> tokens_;
    std::vector<token> expr_;
    std::string date_;
    std::string time_;
    usize curr_expr_;
    u32 expand_;
    u32 skip_;

public:
    preprocessor(context* ctx, std::string const& name, u8 const* data, usize size);
    auto process() -> token;
    auto push_header(std::string const& file) -> void;
    auto pop_header() -> void;
    auto ban_header(location const& loc) -> void;

private:
    auto skip_line() -> void;
    auto next_token() -> token;
    auto read_token() -> token;
    auto read_directive(token& tok) -> void;
    auto read_directive_if(token& tok) -> void;
    auto read_directive_ifdef(token& tok) -> void;
    auto read_directive_ifndef(token& tok) -> void;
    auto read_directive_elif(token& tok) -> void;
    auto read_directive_elifdef(token& tok) -> void;
    auto read_directive_elifndef(token& tok) -> void;
    auto read_directive_else(token& tok) -> void;
    auto read_directive_endif(token& tok) -> void;
    auto read_directive_define(token& tok) -> void;
    auto read_directive_undef(token& tok) -> void;
    auto read_directive_pragma(token& tok) -> void;
    auto read_directive_warning(token& tok) -> void;
    auto read_directive_error(token& tok) -> void;
    auto read_directive_line(token& tok) -> void;
    auto read_directive_include(token& hash, token& name) -> void;
    auto read_directive_inline(token& hash, token& name) -> void;
    auto read_directive_usingtree(token& hash, token& name) -> void;
    auto read_hashtoken(token& hash) -> void;
    auto read_hashtoken_animtree(token& hash, token& name) -> void;
    auto read_hashtoken_hashstr(token& hash, token& name) -> void;
    auto expand(token& tok, define& def) -> void;
    auto expand_params(token& tok, define& def) -> std::vector<std::vector<token>>;
    auto expect(token& tok, token::kind expected, spacing space = spacing::none) -> void;
    auto evaluate() -> bool;
    auto eval_next() -> token&;
    auto eval_peek() -> token&;
    auto eval_prev() -> token&;
    auto eval_atend() -> bool;
    auto eval_check(token::kind type) -> bool;
    auto eval_match(token::kind type) -> bool;
    auto eval_consume(token::kind type, std::string_view msg);
    auto eval_expr() -> i32;
    auto eval_expr_or() -> i32;
    auto eval_expr_and() -> i32;
    auto eval_expr_bwor() -> i32;
    auto eval_expr_bwexor() -> i32;
    auto eval_expr_bwand() -> i32;
    auto eval_expr_eq() -> i32;
    auto eval_expr_lge() -> i32;
    auto eval_expr_shift() -> i32;
    auto eval_expr_add() -> i32;
    auto eval_expr_factor() -> i32;
    auto eval_expr_unary() -> i32;
    auto eval_expr_primary() -> i32;
    auto get_local_time(std::tm& ltime) -> void;
    auto get_date_define(std::tm* time_p) -> void;
    auto get_time_define(std::tm* time_p) -> void;
};

} // namespace xsk::arc
