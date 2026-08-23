// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/gsc/common/location.hpp"
#include "xsk/gsc/common/space.hpp"
#include "xsk/gsc/common/token.hpp"

namespace xsk::gsc
{

auto token::name(const kind k) -> std::string_view
{
    switch (k)
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
        case token::NAME: return "identifier";
        case token::PATH: return "path";
        case token::STRING: return "string";
        case token::ISTRING: return "localized string";
        case token::INT: return "integer";
        case token::FLT: return "float";
        case token::DEVBEGIN: return "/#";
        case token::DEVEND: return "#/";
        case token::INLINE: return "#inline";
        case token::INCLUDE: return "#include";
        case token::USINGTREE: return "#using_animtree";
        case token::ANIMTREE: return "#animtree";
        case token::ENDON: return "endon";
        case token::NOTIFY: return "notify";
        case token::WAIT: return "wait";
        case token::WAITTILL: return "waittill";
        case token::WAITTILLMATCH: return "waittillmatch";
        case token::WAITTILLFRAMEEND: return "waittillframeend";
        case token::WAITFRAME: return "waitframe";
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
        case token::BREAKPOINT: return "breakpoint";
        case token::PROFBEGIN: return "prof_begin";
        case token::PROFEND: return "prof_end";
        case token::ASSERT: return "assert";
        case token::ASSERTEX: return "assertex";
        case token::ASSERTMSG: return "assertmsg";
        case token::THREAD: return "thread";
        case token::CHILDTHREAD: return "childthread";
        case token::THISTHREAD: return "thisthread";
        case token::CALL: return "call";
        case token::TRUE: return "true";
        case token::FALSE: return "false";
        case token::UNDEFINED: return "undefined";
        case token::SIZE: return "size";
        case token::GAME: return "game";
        case token::SELF: return "self";
        case token::ANIM: return "anim";
        case token::LEVEL: return "level";
        case token::ISDEFINED: return "isdefined";
        case token::ISTRUE: return "istrue";
        case token::HASH: return "#";
        case token::NEWLINE: return "end of line";
        case token::EOS: return "end of file";
        case token::DEFINED: return "defined";
        case token::MACROBEGIN: return "macro begin";
        case token::MACROEND: return "macro end";
        case token::MACROARG: return "macro argument";
        case token::MACROVAOPT: return "__VA_OPT__";
        case token::MACROVAOPTEND: return "__VA_OPT__ end";
        case token::MACROVAARGS: return "__VA_ARGS__";
        case token::STRINGIZE: return "#";
        case token::PASTE: return "##";
        default: return "*INTERNAL*";
    }
}

auto token::to_string() const -> std::string
{
    switch (type)
    {
        case token::NAME:
        case token::PATH:
        case token::STRING:
        case token::ISTRING:
        case token::INT:
        case token::FLT:
            return data;
        default:
            return std::string{ name(type) };
    }
}

namespace
{

// Re-escapes what the lexer already decoded, so the text can be read back as a
// source literal. The original spelling is not kept anywhere, so a character
// written literally comes back as an escape; that is equivalent, not identical.
auto escaped(std::string_view str) -> std::string
{
    auto out = std::string{};
    out.reserve(str.size());

    for (auto const c : str)
    {
        switch (c)
        {
            case '"': out.append("\\\""); break;
            case '\\': out.append("\\\\"); break;
            case '\t': out.append("\\t"); break;
            case '\r': out.append("\\r"); break;
            case '\n': out.append("\\n"); break;
            default: out.push_back(c); break;
        }
    }

    return out;
}

} // namespace

// How the token would be written in source. to_string() gives the value, which
// for a string drops its quotes; '#' and '##' need the literal spelling instead.
auto token::spelling() const -> std::string
{
    switch (type)
    {
        case token::STRING: return std::format("\"{}\"", escaped(data));
        case token::ISTRING: return std::format("&\"{}\"", escaped(data));
        default: return to_string();
    }
}

} // namespace xsk::gsc
