// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

struct token
{
    enum kind : u8
    {
        PLUS, MINUS, STAR, DIV, MOD, BITOR, BITAND, BITEXOR, SHL, SHR,
        ASSIGN, PLUSEQ, MINUSEQ, STAREQ, DIVEQ, MODEQ, BITOREQ, BITANDEQ, BITEXOREQ, SHLEQ, SHREQ,
        INC, DEC, GT, LT, GE, LE, NE, EQ, OR, AND, TILDE, BANG, QMARK, COLON, SHARP, COMMA, DOT,
        DOUBLEDOT, ELLIPSIS, SEMICOLON, DOUBLECOLON, LBRACKET, RBRACKET, LBRACE, RBRACE, LPAREN, RPAREN,

        NAME, PATH, STRING, ISTRING, HASHSTR, INT, FLT,

        DEVBEGIN, DEVEND, INLINE, INCLUDE, USINGTREE, ANIMTREE, AUTOEXEC, CODECALL, PRIVATE,
        ENDON, NOTIFY, WAIT, WAITREALTIME, WAITTILL, WAITTILLMATCH, WAITTILLFRAMEEND, IF, ELSE,
        DO, WHILE, FOR, FOREACH, IN, SWITCH, CASE, DEFAULT, BREAK, CONTINUE, RETURN, PROFBEGIN,
        PROFEND, THREAD, TRUE, FALSE, UNDEFINED, SIZE, GAME, SELF, ANIM, LEVEL,
        CONST, ISDEFINED, VECTORSCALE, ANGLESTOUP, ANGLESTORIGHT, ANGLESTOFORWARD, ANGLECLAMP180,
        VECTORTOANGLES, ABS, GETTIME, GETDVAR, GETDVARINT, GETDVARFLOAT, GETDVARVECTOR, GETDVARCOLORRED,
        GETDVARCOLORGREEN, GETDVARCOLORBLUE, GETDVARCOLORALPHA, GETFIRSTARRAYKEY, GETNEXTARRAYKEY,

        HASH, NEWLINE, EOS, DEFINED, MACROBEGIN, MACROEND, MACROARG, MACROVAOPT, MACROVAARGS, STRINGIZE, PASTE
    };

    kind type;
    spacing space;
    location pos;
    std::string data;

    token(kind type, spacing space, location pos) : type{ type }, space{ space },  pos{ pos }, data{} {}
    token(kind type, spacing space, location pos, std::string data) : type{ type }, space{ space },  pos{ pos }, data{ std::move(data) } {}
    auto to_string() -> std::string;
};

} // namespace xsk::arc
