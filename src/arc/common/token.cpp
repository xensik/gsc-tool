// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/arc/common/location.hpp"
#include "xsk/arc/common/space.hpp"
#include "xsk/arc/common/token.hpp"

namespace xsk::arc
{

auto token::to_string() -> std::string
{
    switch (type)
    {
        case token::PLUS: return "+";
        case token::MINUS: return "-";
        case token::STAR: return "*";
        case token::DIV: return "/";
        case token::MOD: return "%";
        case token::BITOR: return "|";
        case token::BITAND: return "&";
        case token::BITEXOR: return "^";
        case token::SHL: return "<<";
        case token::SHR: return ">>";
        case token::ASSIGN: return "=";
        case token::PLUSEQ: return "+=";
        case token::MINUSEQ: return "-=";
        case token::STAREQ: return "*=";
        case token::DIVEQ: return "/=";
        case token::MODEQ: return "%=";
        case token::BITOREQ: return "|=";
        case token::BITANDEQ: return "&=";
        case token::BITEXOREQ: return "^=";
        case token::SHLEQ: return "<<=";
        case token::SHREQ: return ">>=";
        case token::INC: return "++";
        case token::DEC: return "--";
        case token::GT: return ">";
        case token::LT: return "<";
        case token::GE: return ">=";
        case token::LE: return "<=";
        case token::NE: return "!=";
        case token::EQ: return "==";
        case token::OR: return "||";
        case token::AND: return "&&";
        case token::TILDE: return "~";
        case token::BANG: return "!";
        case token::QMARK: return "?";
        case token::COLON: return ":";
        case token::SHARP: return "#";
        case token::COMMA: return ",";
        case token::DOT: return ".";
        case token::DOUBLEDOT: return "..";
        case token::ELLIPSIS: return "...";
        case token::SEMICOLON: return ";";
        case token::DOUBLECOLON: return "::";
        case token::LBRACKET: return "[";
        case token::RBRACKET: return "]";
        case token::LBRACE: return "{";
        case token::RBRACE: return "}";
        case token::LPAREN: return "(";
        case token::RPAREN: return ")";
        case token::NAME: return data;
        case token::PATH: return data;
        case token::STRING: return data;
        case token::ISTRING: return data;
        case token::HASHSTR: return data;
        case token::INT: return data;
        case token::FLT: return data;
        case token::DEVBEGIN: return "/#";
        case token::DEVEND: return "#/";
        case token::INLINE: return "#inline";
        case token::INCLUDE: return "#include";
        case token::USINGTREE: return "#using_animtree";
        case token::ANIMTREE: return "#animtree";
        case token::AUTOEXEC: return "autoexec";
        case token::CODECALL: return "codecall";
        case token::PRIVATE: return "private";
        case token::ENDON: return "endon";
        case token::NOTIFY: return "notify";
        case token::WAIT: return "wait";
        case token::WAITREALTIME: return "waitrealtime";
        case token::WAITTILL: return "waittill";
        case token::WAITTILLMATCH: return "waittillmatch";
        case token::WAITTILLFRAMEEND: return "waittillframeend";
        case token::IF: return "if";
        case token::ELSE: return "else";
        case token::DO: return "do";
        case token::WHILE: return "while";
        case token::FOR: return "for";
        case token::FOREACH: return "foreach";
        case token::IN: return "in";
        case token::SWITCH: return "switch";
        case token::CASE: return "case";
        case token::DEFAULT: return "default";
        case token::BREAK: return "break";
        case token::CONTINUE: return "continue";
        case token::RETURN: return "return";
        case token::PROFBEGIN: return "prof_begin";
        case token::PROFEND: return "prof_end";
        case token::THREAD: return "thread";
        case token::TRUE: return "true";
        case token::FALSE: return "false";
        case token::UNDEFINED: return "undefined";
        case token::SIZE: return "size";
        case token::GAME: return "game";
        case token::SELF: return "self";
        case token::ANIM: return "anim";
        case token::LEVEL: return "level";
        case token::CONST: return "const";
        case token::ISDEFINED: return "isdefined";
        case token::VECTORSCALE: return "vectorscale";
        case token::ANGLESTOUP: return "anglestoup";
        case token::ANGLESTORIGHT: return "anglestoright";
        case token::ANGLESTOFORWARD: return "anglestoforward";
        case token::ANGLECLAMP180: return "angleclamp180";
        case token::VECTORTOANGLES: return "vectorangles";
        case token::ABS: return "abs";
        case token::GETTIME: return "gettime";
        case token::GETDVAR: return "getdvar";
        case token::GETDVARINT: return "getdvarint";
        case token::GETDVARFLOAT: return "getdvarfloat";
        case token::GETDVARVECTOR: return "getdvarvector";
        case token::GETDVARCOLORRED: return "getdvarcolorred";
        case token::GETDVARCOLORGREEN: return "getdvarcolorgreen";
        case token::GETDVARCOLORBLUE: return "getdvarcolorblue";
        case token::GETDVARCOLORALPHA: return "getdvarcoloralpha";
        case token::GETFIRSTARRAYKEY: return "getfirstarraykey";
        case token::GETNEXTARRAYKEY: return "getnextarraykey";
        default: return "*INTERNAL*";
    }
}

} // namespace xsk::arc
