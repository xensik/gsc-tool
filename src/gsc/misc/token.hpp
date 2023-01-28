// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct token
{
    enum type : u8
    {
        tok_identifier,
        tok_path,
        tok_string,
        tok_istring,
        tok_integer,
        tok_float,
        tok_add,
        tok_sub,
        tok_mul,
        tok_div,
        tok_mod,
        tok_bwor,
        tok_bwand,
        tok_bwexor,
        tok_assign,
        tok_assign_add,
        tok_assign_sub,
        tok_assign_mul,
        tok_assign_div,
        tok_assign_mod,
        tok_assign_bwor,
        tok_assign_bwand,
        tok_assign_bwexor,
        tok_assign_lshift,
        tok_assign_rshift,
        tok_complement,
        tok_not,
        tok_greater,
        tok_less,
        tok_greater_equal,
        tok_less_equal,
        tok_inequality,
        tok_equality,
        tok_or,
        tok_and,
        tok_lshift,
        tok_rshift,
        tok_increment,
        tok_decrement,
        tok_qmark,
        tok_dot,
        tok_comma,
        tok_colon,
        tok_semicolon,
        tok_doublecolon,
        tok_lbracket,
        tok_rbracket,
        tok_lbrace,
        tok_rbrace,
        tok_lparen,
        tok_rparen,
        tok_hash,
        tok_devbegin,
        tok_devend,
        tok_inline,
        tok_include,
        tok_usingtree,
        tok_animtree,
        tok_endon,
        tok_notify,
        tok_wait,
        tok_waittill,
        tok_waittillmatch,
        tok_waittillframeend,
        tok_waitframe,
        tok_if,
        tok_else,
        tok_do,
        tok_while,
        tok_for,
        tok_foreach,
        tok_in,
        tok_switch,
        tok_case,
        tok_default,
        tok_break,
        tok_continue,
        tok_return,
        tok_breakpoint,
        tok_prof_begin,
        tok_prof_end,
        tok_thread,
        tok_childthread,
        tok_thisthread,
        tok_call,
        tok_true,
        tok_false,
        tok_undefined,
        tok_size,
        tok_game,
        tok_self,
        tok_anim,
        tok_level,
        tok_isdefined,
        tok_istrue,
        tok_newline,
        tok_eof,
        tok_cleanhash,
        tok_defined,
        tok_macrobegin,
        tok_macroend,
    };

    type kind;
    spacing space;
    location pos;
    std::string data;

    token(type kind, spacing space, location pos) : kind{ kind }, space{ space },  pos{ pos }, data{} {}
    token(type kind, spacing space, location pos, std::string data) : kind{ kind }, space{ space },  pos{ pos }, data{ std::move(data) } {}
};

} // namespace xsk::gsc
