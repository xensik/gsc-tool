// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/arc/parser.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc
{

namespace
{

std::unordered_map<std::string_view, token::kind> const keyword_map
{{
    { "endon", token::ENDON },
    { "notify", token::NOTIFY },
    { "wait", token::WAIT },
    { "waitrealtime", token::WAITREALTIME },
    { "waittill", token::WAITTILL },
    { "waittillmatch", token::WAITTILLMATCH },
    { "waittillframeend", token::WAITTILLFRAMEEND },
    { "if", token::IF },
    { "else", token::ELSE },
    { "do", token::DO },
    { "while", token::WHILE },
    { "for", token::FOR },
    { "foreach", token::FOREACH },
    { "in", token::IN },
    { "switch", token::SWITCH },
    { "case", token::CASE },
    { "default", token::DEFAULT },
    { "break", token::BREAK },
    { "continue", token::CONTINUE },
    { "return", token::RETURN },
    { "autoexec", token::AUTOEXEC },
    { "codecall", token::CODECALL },
    { "private", token::PRIVATE },
    { "prof_begin", token::PROFBEGIN },
    { "prof_end", token::PROFEND },
    { "thread", token::THREAD },
    { "const", token::CONST },
    { "true", token::TRUE },
    { "false", token::FALSE },
    { "undefined", token::UNDEFINED },
    { "size", token::SIZE },
    { "game", token::GAME },
    { "self", token::SELF },
    { "anim", token::ANIM },
    { "level", token::LEVEL },
    { "isdefined", token::ISDEFINED },
    { "vectorscale", token::VECTORSCALE },
    { "anglestoup", token::ANGLESTOUP },
    { "anglestoright", token::ANGLESTORIGHT },
    { "anglestoforward", token::ANGLESTOFORWARD },
    { "angleclamp180", token::ANGLECLAMP180 },
    { "vectortoangles", token::VECTORTOANGLES },
    { "abs", token::ABS },
    { "gettime", token::GETTIME },
    { "getdvar", token::GETDVAR },
    { "getdvarint", token::GETDVARINT },
    { "getdvarfloat", token::GETDVARFLOAT },
    { "getdvarvector", token::GETDVARVECTOR },
    { "getdvarcolorred", token::GETDVARCOLORRED },
    { "getdvarcolorgreen", token::GETDVARCOLORGREEN },
    { "getdvarcolorblue", token::GETDVARCOLORBLUE },
    { "getdvarcoloralpha", token::GETDVARCOLORALPHA },
    { "getfirstarraykey", token::GETFIRSTARRAYKEY },
    { "getnextarraykey", token::GETNEXTARRAYKEY },
}};

} // anonymous namespace

parser::parser(context* ctx)
    : ctx_{ ctx }, ppr_{ preprocessor{ ctx, "", nullptr, 0 } },
      tok_{ token::EOS, spacing::null, location{} },
      next_{ token::EOS, spacing::null, location{} },
      has_next_{ false }, index_{ 0 }
{
    advance();
}

auto parser::parse_assembly(buffer const& data) -> assembly::ptr
{
    return parse_assembly(data.data, data.size);
}

auto parser::parse_assembly(std::vector<u8> const& data) -> assembly::ptr
{
    return parse_assembly(data.data(), data.size());
}

auto parser::parse_assembly(u8 const* /*data*/, usize /*size*/) -> assembly::ptr
{
    return assembly::make();
}


auto parser::parse_source(std::string const& name, buffer const& data) -> program::ptr
{
    return parse_source(name, data.data, data.size);
}

auto parser::parse_source(std::string const& name, std::vector<u8> const& data) -> program::ptr
{
    return parse_source(name, data.data(), data.size());
}

auto parser::parse_source(std::string const& name, u8 const* data, usize size) -> program::ptr
{
    ppr_ = preprocessor{ ctx_, name, data, size };
    tok_ = token{ token::EOS, spacing::null, location{} };
    next_ = token{ token::EOS, spacing::null, location{} };
    has_next_ = false;
    index_ = 0;

    advance();

    return parse_program();

    error(std::format("an unknown error ocurred while parsing script {}", name));
}

auto parser::parse_program() -> program::ptr
{
    auto prog = program::make();

    while (!check(token::EOS))
    {
        if (check(token::INCLUDE))
        {
            prog->includes.push_back(parse_include());
        }
        else if (check(token::INLINE))
        {
            parse_inline();
        }
        else if (check(token::SEMICOLON))
        {
            advance();
        }
        else
        {
            prog->declarations.push_back(parse_declaration());
        }
    }

    return prog;
}

auto parser::parse_include() -> include::ptr
{
    auto loc = tok_.pos;
    expect(token::INCLUDE);
    auto path = parse_expr_path();
    expect(token::SEMICOLON);
    return include::make(loc, std::move(path));
}

auto parser::parse_inline() -> void
{
    auto loc = tok_.pos;
    expect(token::INLINE);
    auto path = parse_expr_path();
    expect(token::SEMICOLON);
    ppr_.push_header(loc, path->value);
}

auto parser::parse_declaration() -> decl::ptr
{
    auto loc = tok_.pos;

    if (check(token::DEVBEGIN))
    {
        advance();
        return decl_dev_begin::make(loc);
    }

    if (check(token::DEVEND))
    {
        advance();
        return decl_dev_end::make(loc);
    }

    if (check(token::USINGTREE))
    {
        return parse_decl_usingtree();
    }

    return parse_decl_function();
}

auto parser::parse_decl_usingtree() -> decl::ptr
{
    auto loc = tok_.pos;
    expect(token::USINGTREE);
    expect(token::LPAREN);
    auto name = parse_expr_string();
    expect(token::RPAREN);
    expect(token::SEMICOLON);
    ppr_.ban_header(loc);
    return decl_usingtree::make(loc, std::move(name));
}

auto parser::parse_decl_function() -> decl::ptr
{
    auto loc = tok_.pos;
    auto flags = export_flags::export_none;

    if (check(token::AUTOEXEC))
    {
        flags = export_flags::export_autoexec;
        advance();
    }
    else if (check(token::CODECALL))
    {
        flags = export_flags::export_codecall;
        advance();
    }
    else if (check(token::PRIVATE))
    {
        flags = export_flags::export_private2;
        advance();
    }

    auto name = parse_expr_identifier();
    expect(token::LPAREN);
    auto params = parse_expr_parameters();
    expect(token::RPAREN);
    auto body = parse_stmt_comp();
    ppr_.ban_header(loc);
    return decl_function::make(loc, expr_identifier::make(loc, ""), std::move(name), std::move(params), std::move(body), flags);
}

auto parser::parse_stmt() -> stmt::ptr
{
    switch (tok_.type)
    {
        case token::LBRACE:           return parse_stmt_comp();
        case token::WAIT:             return parse_stmt_wait();
        case token::WAITREALTIME:     return parse_stmt_waitrealtime();
        case token::WAITTILLFRAMEEND: return parse_stmt_waittillframeend();
        case token::IF:               return parse_stmt_if();
        case token::WHILE:            return parse_stmt_while();
        case token::DO:               return parse_stmt_dowhile();
        case token::FOR:              return parse_stmt_for();
        case token::FOREACH:          return parse_stmt_foreach();
        case token::SWITCH:           return parse_stmt_switch();
        case token::CASE:             return parse_stmt_case();
        case token::DEFAULT:          return parse_stmt_default();
        case token::BREAK:            return parse_stmt_break();
        case token::CONTINUE:         return parse_stmt_continue();
        case token::RETURN:           return parse_stmt_return();
        case token::PROFBEGIN:        return parse_stmt_prof_begin();
        case token::PROFEND:          return parse_stmt_prof_end();
        case token::CONST:            return parse_stmt_const();
        default:
            return parse_stmt_call_or_assign();
    }
}

auto parser::parse_stmt_or_dev() -> stmt::ptr
{
    if (check(token::DEVBEGIN))
        return parse_stmt_dev();

    return parse_stmt();
}

auto parser::parse_stmt_or_dev_list() -> stmt_list::ptr
{
    auto loc = tok_.pos;
    auto list = stmt_list::make(loc);

    while (!check(token::RBRACE) && !check(token::EOS))
    {
        if (check(token::SEMICOLON))
        {
            advance();
            continue;
        }

        list->list.push_back(parse_stmt_or_dev());
    }

    return list;
}

auto parser::parse_stmt_list() -> stmt_list::ptr
{
    auto loc = tok_.pos;
    auto list = stmt_list::make(loc);

    while (!check(token::DEVEND) && !check(token::EOS))
    {
        if (check(token::SEMICOLON))
        {
            advance();
            continue;
        }

        list->list.push_back(parse_stmt());
    }

    return list;
}

auto parser::parse_stmt_comp() -> stmt_comp::ptr
{
    auto loc = tok_.pos;
    expect(token::LBRACE);

    if (check(token::RBRACE))
    {
        advance();
        return stmt_comp::make(loc, stmt_list::make(loc));
    }

    auto list = parse_stmt_or_dev_list();
    expect(token::RBRACE);
    return stmt_comp::make(loc, std::move(list));
}

auto parser::parse_stmt_dev() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::DEVBEGIN);

    if (check(token::DEVEND))
    {
        advance();
        return stmt_dev::make(loc, stmt_list::make(loc));
    }

    auto list = parse_stmt_list();
    expect(token::DEVEND);
    return stmt_dev::make(loc, std::move(list));
}

auto parser::parse_stmt_expr() -> stmt_expr::ptr
{
    auto loc = tok_.pos;

    // empty expression (used in for-loop init/iter)
    if (check(token::SEMICOLON) || check(token::RPAREN))
    {
        return stmt_expr::make(loc, expr_empty::make(loc));
    }

    // prefix increment
    if (check(token::INC))
    {
        advance();
        auto obj = parse_expr_object();
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for increment");
        return stmt_expr::make(loc, expr_increment::make(loc, std::move(obj), true));
    }

    // prefix decrement
    if (check(token::DEC))
    {
        advance();
        auto obj = parse_expr_object();
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for decrement");
        return stmt_expr::make(loc, expr_decrement::make(loc, std::move(obj), true));
    }

    // parse object expression then check for assign/increment/decrement
    auto obj = parse_expr_object();

    if (is_assign_op())
    {
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for assignment");
        auto op = parse_assign_op();
        auto rhs = parse_expr();
        return stmt_expr::make(loc, expr_assign::make(loc, std::move(obj), std::move(rhs), op));
    }

    if (check(token::INC))
    {
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for increment");
        advance();
        return stmt_expr::make(loc, expr_increment::make(loc, std::move(obj), false));
    }

    if (check(token::DEC))
    {
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for decrement");
        advance();
        return stmt_expr::make(loc, expr_decrement::make(loc, std::move(obj), false));
    }

    // plain call/method expression
    return stmt_expr::make(loc, std::move(obj));
}

auto parser::parse_stmt_for_expr() -> stmt_expr::ptr
{
    auto loc = tok_.pos;

    // empty expression
    if (check(token::SEMICOLON) || check(token::RPAREN))
    {
        return stmt_expr::make(loc, expr_empty::make(loc));
    }

    // prefix increment
    if (check(token::INC))
    {
        advance();
        auto obj = parse_expr_object();
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for increment");
        return stmt_expr::make(loc, expr_increment::make(loc, std::move(obj), true));
    }

    // prefix decrement
    if (check(token::DEC))
    {
        advance();
        auto obj = parse_expr_object();
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for decrement");
        return stmt_expr::make(loc, expr_decrement::make(loc, std::move(obj), true));
    }

    auto obj = parse_expr_object();

    if (is_assign_op())
    {
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for assignment");
        auto op = parse_assign_op();
        auto rhs = parse_expr();
        return stmt_expr::make(loc, expr_assign::make(loc, std::move(obj), std::move(rhs), op));
    }

    if (check(token::INC))
    {
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for increment");
        advance();
        return stmt_expr::make(loc, expr_increment::make(loc, std::move(obj), false));
    }

    if (check(token::DEC))
    {
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for decrement");
        advance();
        return stmt_expr::make(loc, expr_decrement::make(loc, std::move(obj), false));
    }

    error("expected assignment or increment/decrement in for-loop");
}

auto parser::parse_stmt_call_or_assign() -> stmt::ptr
{
    auto loc = tok_.pos;

    // empty statement
    if (check(token::SEMICOLON))
    {
        advance();
        return stmt_expr::make(loc, expr_empty::make(loc));
    }

    // prefix increment
    if (check(token::INC))
    {
        advance();
        auto obj = parse_expr_object();
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for increment");
        expect(token::SEMICOLON);
        return stmt_expr::make(loc, expr_increment::make(loc, std::move(obj), true));
    }

    // prefix decrement
    if (check(token::DEC))
    {
        advance();
        auto obj = parse_expr_object();
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for decrement");
        expect(token::SEMICOLON);
        return stmt_expr::make(loc, expr_decrement::make(loc, std::move(obj), true));
    }

    // parse object expression
    auto obj = parse_expr_object();

    // event statements
    if (check(token::ENDON))
        return parse_stmt_endon(std::move(obj));
    if (check(token::NOTIFY))
        return parse_stmt_notify(std::move(obj));
    if (check(token::WAITTILL))
        return parse_stmt_waittill(std::move(obj));
    if (check(token::WAITTILLMATCH))
        return parse_stmt_waittillmatch(std::move(obj));

    // assignment
    if (is_assign_op())
    {
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for assignment");
        auto op = parse_assign_op();
        auto rhs = parse_expr();
        expect(token::SEMICOLON);
        return stmt_expr::make(loc, expr_assign::make(loc, std::move(obj), std::move(rhs), op));
    }

    // postfix increment
    if (check(token::INC))
    {
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for increment");
        advance();
        expect(token::SEMICOLON);
        return stmt_expr::make(loc, expr_increment::make(loc, std::move(obj), false));
    }

    // postfix decrement
    if (check(token::DEC))
    {
        if (!is_lvalue(*obj))
            error(obj->loc(), "expected lvalue for decrement");
        advance();
        expect(token::SEMICOLON);
        return stmt_expr::make(loc, expr_decrement::make(loc, std::move(obj), false));
    }

    // call/method expression statement
    if (!is_call_or_method(*obj))
        error(obj->loc(), "expected call, method, or assignment");
    expect(token::SEMICOLON);
    return stmt_expr::make(loc, std::move(obj));
}

auto parser::parse_stmt_const() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::CONST);
    auto name = parse_expr_identifier();
    expect(token::ASSIGN);
    auto value = parse_expr();
    expect(token::SEMICOLON);
    return stmt_expr::make(loc, expr_const::make(loc, std::move(name), std::move(value)));
}

auto parser::parse_stmt_endon(expr::ptr obj) -> stmt::ptr
{
    auto loc = obj->loc();
    expect(token::ENDON);
    expect(token::LPAREN);
    auto event = parse_expr();
    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_endon::make(loc, std::move(obj), std::move(event));
}

auto parser::parse_stmt_notify(expr::ptr obj) -> stmt::ptr
{
    auto loc = obj->loc();
    expect(token::NOTIFY);
    expect(token::LPAREN);
    auto event = parse_expr();

    if (match(token::COMMA))
    {
        auto args = parse_expr_arguments_no_empty();
        expect(token::RPAREN);
        expect(token::SEMICOLON);
        return stmt_notify::make(loc, std::move(obj), std::move(event), std::move(args));
    }

    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_notify::make(loc, std::move(obj), std::move(event), expr_arguments::make(loc));
}

auto parser::parse_stmt_wait() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::WAIT);
    auto time = parse_expr();
    expect(token::SEMICOLON);
    return stmt_wait::make(loc, std::move(time));
}

auto parser::parse_stmt_waitrealtime() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::WAITREALTIME);
    auto time = parse_expr();
    expect(token::SEMICOLON);
    return stmt_waitrealtime::make(loc, std::move(time));
}

auto parser::parse_stmt_waittill(expr::ptr obj) -> stmt::ptr
{
    auto loc = obj->loc();
    expect(token::WAITTILL);
    expect(token::LPAREN);
    auto event = parse_expr();

    if (match(token::COMMA))
    {
        auto args = parse_expr_arguments_no_empty();
        expect(token::RPAREN);
        expect(token::SEMICOLON);
        return stmt_waittill::make(loc, std::move(obj), std::move(event), std::move(args));
    }

    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_waittill::make(loc, std::move(obj), std::move(event), expr_arguments::make(loc));
}

auto parser::parse_stmt_waittillmatch(expr::ptr obj) -> stmt::ptr
{
    auto loc = obj->loc();
    expect(token::WAITTILLMATCH);
    expect(token::LPAREN);
    auto event = parse_expr();

    if (match(token::COMMA))
    {
        auto args = parse_expr_arguments_no_empty();
        expect(token::RPAREN);
        expect(token::SEMICOLON);
        return stmt_waittillmatch::make(loc, std::move(obj), std::move(event), std::move(args));
    }

    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_waittillmatch::make(loc, std::move(obj), std::move(event), expr_arguments::make(loc));
}

auto parser::parse_stmt_waittillframeend() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::WAITTILLFRAMEEND);
    expect(token::SEMICOLON);
    return stmt_waittillframeend::make(loc);
}

auto parser::parse_stmt_if() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::IF);
    expect(token::LPAREN);
    auto test = parse_expr();
    expect(token::RPAREN);
    auto body = parse_stmt();

    if (match(token::ELSE))
    {
        auto els = parse_stmt();
        return stmt_ifelse::make(loc, std::move(test), std::move(body), std::move(els));
    }

    return stmt_if::make(loc, std::move(test), std::move(body));
}

auto parser::parse_stmt_while() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::WHILE);
    expect(token::LPAREN);
    auto test = parse_expr();
    expect(token::RPAREN);
    auto body = parse_stmt();
    return stmt_while::make(loc, std::move(test), std::move(body));
}

auto parser::parse_stmt_dowhile() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::DO);
    auto body = parse_stmt();
    expect(token::WHILE);
    expect(token::LPAREN);
    auto test = parse_expr();
    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_dowhile::make(loc, std::move(test), std::move(body));
}

auto parser::parse_stmt_for() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::FOR);
    expect(token::LPAREN);
    auto init = parse_stmt_for_expr();
    expect(token::SEMICOLON);

    auto test = check(token::SEMICOLON) ? expr_empty::make(tok_.pos) : parse_expr();
    expect(token::SEMICOLON);

    auto iter = parse_stmt_for_expr();
    expect(token::RPAREN);
    auto body = parse_stmt();
    return stmt_for::make(loc, std::move(init), std::move(test), std::move(iter), std::move(body));
}

auto parser::parse_stmt_foreach() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::FOREACH);
    expect(token::LPAREN);
    auto ident1 = parse_expr_identifier();

    if (match(token::COMMA))
    {
        auto ident2 = parse_expr_identifier();
        expect(token::IN);
        auto container = parse_expr();
        expect(token::RPAREN);
        auto body = parse_stmt();
        auto array = expr_identifier::make(loc, std::format("_a{}", ++index_));
        return stmt_foreach::make(loc, std::move(container), std::move(ident2), std::move(array), std::move(ident1), std::move(body), true);
    }

    expect(token::IN);
    auto container = parse_expr();
    expect(token::RPAREN);
    auto body = parse_stmt();
    auto array = expr_identifier::make(loc, std::format("_a{}", ++index_));
    auto key = expr_identifier::make(loc, std::format("_k{}", ++index_));
    return stmt_foreach::make(loc, std::move(container), std::move(ident1), std::move(array), std::move(key), std::move(body), false);
}

auto parser::parse_stmt_switch() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::SWITCH);
    expect(token::LPAREN);
    auto test = parse_expr();
    expect(token::RPAREN);
    auto body = parse_stmt_comp();
    auto stm = stmt_switch::make(loc, std::move(test), std::move(body));
    parse_switch(*stm);
    return stm;
}

auto parser::parse_stmt_case() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::CASE);

    expr::ptr value;

    if (check(token::INT))
    {
        value = expr_integer::make(tok_.pos, tok_.data);
        advance();
    }
    else if (check(token::STRING))
    {
        value = expr_string::make(tok_.pos, tok_.data);
        advance();
    }
    else if (check(token::MINUS))
    {
        advance();
        value = expr_integer::make(tok_.pos, "-" + tok_.data);
        expect(token::INT);
    }
    else
    {
        error("expected integer or string for case label");
    }

    expect(token::COLON);
    return stmt_case::make(loc, std::move(value), stmt_list::make(loc));
}

auto parser::parse_stmt_default() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::DEFAULT);
    expect(token::COLON);
    return stmt_default::make(loc, stmt_list::make(loc));
}

auto parser::parse_stmt_break() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::BREAK);
    expect(token::SEMICOLON);
    return stmt_break::make(loc);
}

auto parser::parse_stmt_continue() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::CONTINUE);
    expect(token::SEMICOLON);
    return stmt_continue::make(loc);
}

auto parser::parse_stmt_return() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::RETURN);

    if (check(token::SEMICOLON))
    {
        advance();
        return stmt_return::make(loc, expr_empty::make(loc));
    }

    auto value = parse_expr();
    expect(token::SEMICOLON);
    return stmt_return::make(loc, std::move(value));
}

auto parser::parse_stmt_prof_begin() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::PROFBEGIN);
    expect(token::LPAREN);
    auto args = parse_expr_arguments();
    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_prof_begin::make(loc, std::move(args));
}

auto parser::parse_stmt_prof_end() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::PROFEND);
    expect(token::LPAREN);
    auto args = parse_expr_arguments();
    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_prof_end::make(loc, std::move(args));
}

auto parser::parse_expr() -> expr::ptr
{
    return parse_expr_ternary();
}

auto parser::parse_expr_ternary() -> expr::ptr
{
    auto loc = tok_.pos;
    auto lhs = parse_expr_or();

    if (match(token::QMARK))
    {
        auto true_expr = parse_expr();
        expect(token::COLON);
        auto false_expr = parse_expr_ternary();
        return expr_ternary::make(loc, std::move(lhs), std::move(true_expr), std::move(false_expr));
    }

    return lhs;
}

auto parser::parse_expr_or() -> expr::ptr
{
    auto lhs = parse_expr_and();

    while (check(token::OR))
    {
        auto loc = tok_.pos;
        advance();
        auto rhs = parse_expr_and();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), expr_binary::op::bool_or);
    }

    return lhs;
}

auto parser::parse_expr_and() -> expr::ptr
{
    auto lhs = parse_expr_bw_or();

    while (check(token::AND))
    {
        auto loc = tok_.pos;
        advance();
        auto rhs = parse_expr_bw_or();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), expr_binary::op::bool_and);
    }

    return lhs;
}

auto parser::parse_expr_bw_or() -> expr::ptr
{
    auto lhs = parse_expr_bw_xor();

    while (check(token::BITOR))
    {
        auto loc = tok_.pos;
        advance();
        auto rhs = parse_expr_bw_xor();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), expr_binary::op::bwor);
    }

    return lhs;
}

auto parser::parse_expr_bw_xor() -> expr::ptr
{
    auto lhs = parse_expr_bw_and();

    while (check(token::BITEXOR))
    {
        auto loc = tok_.pos;
        advance();
        auto rhs = parse_expr_bw_and();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), expr_binary::op::bwexor);
    }

    return lhs;
}

auto parser::parse_expr_bw_and() -> expr::ptr
{
    auto lhs = parse_expr_equality();

    while (check(token::BITAND))
    {
        auto loc = tok_.pos;
        advance();
        auto rhs = parse_expr_equality();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), expr_binary::op::bwand);
    }

    return lhs;
}

auto parser::parse_expr_equality() -> expr::ptr
{
    auto lhs = parse_expr_relational();

    while (check(token::EQ) || check(token::NE))
    {
        auto loc = tok_.pos;
        auto op = check(token::EQ) ? expr_binary::op::eq : expr_binary::op::ne;
        advance();
        auto rhs = parse_expr_relational();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), op);
    }

    return lhs;
}

auto parser::parse_expr_relational() -> expr::ptr
{
    auto lhs = parse_expr_shift();

    while (check(token::LT) || check(token::LE) || check(token::GT) || check(token::GE))
    {
        auto loc = tok_.pos;
        expr_binary::op op;

        switch (tok_.type)
        {
            case token::LT: op = expr_binary::op::lt; break;
            case token::LE: op = expr_binary::op::le; break;
            case token::GT: op = expr_binary::op::gt; break;
            case token::GE: op = expr_binary::op::ge; break;
            default: break;
        }

        advance();
        auto rhs = parse_expr_shift();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), op);
    }

    return lhs;
}

auto parser::parse_expr_shift() -> expr::ptr
{
    auto lhs = parse_expr_additive();

    while (check(token::SHL) || check(token::SHR))
    {
        auto loc = tok_.pos;
        auto op = check(token::SHL) ? expr_binary::op::shl : expr_binary::op::shr;
        advance();
        auto rhs = parse_expr_additive();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), op);
    }

    return lhs;
}

auto parser::parse_expr_additive() -> expr::ptr
{
    auto lhs = parse_expr_multiplicative();

    while (check(token::PLUS) || check(token::MINUS))
    {
        auto loc = tok_.pos;
        auto op = check(token::PLUS) ? expr_binary::op::add : expr_binary::op::sub;
        advance();
        auto rhs = parse_expr_multiplicative();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), op);
    }

    return lhs;
}

auto parser::parse_expr_multiplicative() -> expr::ptr
{
    auto lhs = parse_expr_unary();

    while (check(token::STAR) || check(token::DIV) || check(token::MOD))
    {
        auto loc = tok_.pos;
        expr_binary::op op;

        switch (tok_.type)
        {
            case token::STAR: op = expr_binary::op::mul; break;
            case token::DIV:  op = expr_binary::op::div; break;
            case token::MOD:  op = expr_binary::op::mod; break;
            default: break;
        }

        advance();
        auto rhs = parse_expr_unary();
        lhs = expr_binary::make(loc, std::move(lhs), std::move(rhs), op);
    }

    return lhs;
}

auto parser::parse_expr_unary() -> expr::ptr
{
    auto loc = tok_.pos;

    if (check(token::TILDE))
    {
        advance();
        return expr_complement::make(loc, parse_expr_unary());
    }

    if (check(token::BANG))
    {
        advance();
        return expr_not::make(loc, parse_expr_unary());
    }

    if (check(token::MINUS))
    {
        advance();

        if (check(token::FLT))
        {
            auto val = "-" + tok_.data;
            auto floc = tok_.pos;
            advance();
            return expr_float::make(floc, val);
        }

        if (check(token::INT))
        {
            auto val = "-" + tok_.data;
            auto iloc = tok_.pos;
            advance();
            return expr_integer::make(iloc, val);
        }

        // negate restricted to identifier, paren, array, field per ANTLR4
        if (check(token::NAME))
        {
            auto rhs = parse_expr_object();
            return expr_negate::make(loc, std::move(rhs));
        }

        if (check(token::GAME) || check(token::SELF) || check(token::ANIM) || check(token::LEVEL))
        {
            auto rhs = parse_expr_object();
            return expr_negate::make(loc, std::move(rhs));
        }

        if (check(token::LPAREN))
        {
            auto rhs = parse_expr_paren_or_vector();
            return expr_negate::make(loc, std::move(rhs));
        }

        error("expected expression after '-'");
    }

    if (check(token::MOD))
    {
        return parse_expr_animation();
    }

    return parse_expr_primary();
}

auto parser::parse_expr_primary() -> expr::ptr
{
    auto loc = tok_.pos;

    switch (tok_.type)
    {
        case token::THREAD:
        {
            advance();
            auto c = parse_expr_call(call::mode::thread);
            return parse_expr_postfix(expr_call::make(loc, std::move(c)));
        }

        case token::DOUBLECOLON:
        {
            advance();
            auto name_tok = expect(token::NAME);
            auto name = expr_identifier::make(name_tok.pos, name_tok.data);
            auto path = expr_path::make(loc);

            if (check(token::LPAREN))
            {
                advance();
                auto args = parse_expr_arguments();
                expect(token::RPAREN);
                auto func = expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal);
                return parse_expr_postfix(expr_call::make(loc, std::move(func)));
            }

            return expr_reference::make(loc, std::move(path), std::move(name));
        }

        case token::ISDEFINED:
            return parse_expr_isdefined();

        // 19 built-in function keywords
        case token::ABS:               return parse_expr_abs();
        case token::GETTIME:           return parse_expr_gettime();
        case token::GETDVAR:           return parse_expr_getdvar();
        case token::GETDVARINT:        return parse_expr_getdvarint();
        case token::GETDVARFLOAT:      return parse_expr_getdvarfloat();
        case token::GETDVARVECTOR:     return parse_expr_getdvarvector();
        case token::GETDVARCOLORRED:   return parse_expr_getdvarcolorred();
        case token::GETDVARCOLORGREEN: return parse_expr_getdvarcolorgreen();
        case token::GETDVARCOLORBLUE:  return parse_expr_getdvarcolorblue();
        case token::GETDVARCOLORALPHA: return parse_expr_getdvarcoloralpha();
        case token::GETFIRSTARRAYKEY:  return parse_expr_getfirstarraykey();
        case token::GETNEXTARRAYKEY:   return parse_expr_getnextarraykey();
        case token::VECTORSCALE:       return parse_expr_vectorscale();
        case token::ANGLESTOUP:        return parse_expr_anglestoup();
        case token::ANGLESTORIGHT:     return parse_expr_anglestoright();
        case token::ANGLESTOFORWARD:   return parse_expr_anglestoforward();
        case token::ANGLECLAMP180:     return parse_expr_angleclamp180();
        case token::VECTORTOANGLES:    return parse_expr_vectortoangles();

        case token::LBRACKET:
        {
            // [] empty array
            if (peek().type == token::RBRACKET)
            {
                advance();
                advance();
                return expr_empty_array::make(loc);
            }

            // [[expr]](args) pointer call
            if (peek().type == token::LBRACKET)
            {
                auto c = parse_expr_pointer(call::mode::normal);
                return parse_expr_postfix(expr_call::make(loc, std::move(c)));
            }

            error("unexpected '['");
        }

        case token::LPAREN:
            return parse_expr_paren_or_vector();

        case token::UNDEFINED:
            advance();
            return expr_undefined::make(loc);

        case token::ANIMTREE:
            advance();
            return expr_animtree::make(loc);

        case token::TRUE:
            advance();
            return expr_true::make(loc);

        case token::FALSE:
            advance();
            return expr_false::make(loc);

        case token::INT:
        {
            auto val = tok_.data;
            advance();
            return expr_integer::make(loc, val);
        }

        case token::FLT:
        {
            auto val = tok_.data;
            advance();
            return expr_float::make(loc, val);
        }

        case token::STRING:
        {
            auto val = tok_.data;
            advance();
            auto node = expr_string::make(loc, val);
            if (check(token::DOT) && peek().type == token::SIZE)
            {
                auto dloc = tok_.pos;
                advance();
                advance();
                return expr_size::make(dloc, std::move(node));
            }
            return node;
        }

        case token::ISTRING:
        {
            auto val = tok_.data;
            advance();
            return expr_istring::make(loc, val);
        }

        case token::HASHSTR:
        {
            auto val = tok_.data;
            advance();
            return expr_hash::make(loc, val);
        }

        case token::NAME:
        case token::PATH:
        {
            return parse_expr_object();
        }

        case token::GAME:
        {
            advance();
            auto base = expr_game::make(loc);
            return parse_expr_postfix(std::move(base));
        }

        case token::SELF:
        {
            advance();
            auto base = expr_self::make(loc);
            return parse_expr_postfix(std::move(base));
        }

        case token::ANIM:
        {
            advance();
            auto base = expr_anim::make(loc);
            return parse_expr_postfix(std::move(base));
        }

        case token::LEVEL:
        {
            advance();
            auto base = expr_level::make(loc);
            return parse_expr_postfix(std::move(base));
        }

        case token::SIZE:
        {
            advance();
            return expr_identifier::make(loc, "size");
        }

        default:
            error(std::format("unexpected token '{}'", tok_.to_string()));
    }
}

auto parser::parse_expr_object() -> expr::ptr
{
    auto loc = tok_.pos;

    if (check(token::NAME))
    {
        if (peek().type == token::DOUBLECOLON)
        {
            auto path_tok = advance();
            advance(); // consume ::
            auto name_tok = expect(token::NAME);
            auto path = expr_path::make(path_tok.pos, path_tok.data);
            auto name = expr_identifier::make(name_tok.pos, name_tok.data);

            if (check(token::LPAREN))
            {
                advance();
                auto args = parse_expr_arguments();
                expect(token::RPAREN);
                auto func = expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal);
                return parse_expr_postfix(expr_call::make(loc, std::move(func)));
            }

            return expr_reference::make(loc, std::move(path), std::move(name));
        }

        if (peek().type == token::LPAREN)
        {
            auto name_tok = advance();
            advance(); // consume (
            auto args = parse_expr_arguments();
            expect(token::RPAREN);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(name_tok.pos, name_tok.data);
            auto func = expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal);
            return parse_expr_postfix(expr_call::make(loc, std::move(func)));
        }

        auto name_tok = advance();
        auto base = expr_identifier::make(name_tok.pos, name_tok.data);
        return parse_expr_postfix(std::move(base));
    }

    if (check(token::PATH))
    {
        if (peek().type == token::DOUBLECOLON)
        {
            auto path_tok = advance();
            advance(); // consume ::
            auto name_tok = expect(token::NAME);
            auto path = expr_path::make(path_tok.pos, path_tok.data);
            auto name = expr_identifier::make(name_tok.pos, name_tok.data);

            if (check(token::LPAREN))
            {
                advance();
                auto args = parse_expr_arguments();
                expect(token::RPAREN);
                auto func = expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal);
                return parse_expr_postfix(expr_call::make(loc, std::move(func)));
            }

            return expr_reference::make(loc, std::move(path), std::move(name));
        }

        auto path_tok = advance();
        auto base = expr_identifier::make(path_tok.pos, path_tok.data);
        return parse_expr_postfix(std::move(base));
    }

    if (check(token::GAME))
    {
        advance();
        return parse_expr_postfix(expr_game::make(loc));
    }

    if (check(token::SELF))
    {
        advance();
        return parse_expr_postfix(expr_self::make(loc));
    }

    if (check(token::ANIM))
    {
        advance();
        return parse_expr_postfix(expr_anim::make(loc));
    }

    if (check(token::LEVEL))
    {
        advance();
        return parse_expr_postfix(expr_level::make(loc));
    }

    if (check(token::THREAD))
    {
        advance();
        auto c = parse_expr_call(call::mode::thread);
        return parse_expr_postfix(expr_call::make(loc, std::move(c)));
    }

    // [[ptr]](args) at object level
    if (check(token::LBRACKET) && peek().type == token::LBRACKET)
    {
        auto c = parse_expr_pointer(call::mode::normal);
        return parse_expr_postfix(expr_call::make(loc, std::move(c)));
    }

    return parse_expr_primary();
}

auto parser::parse_expr_postfix(expr::ptr base) -> expr::ptr
{
    auto first = true;

    while (true)
    {
        if (check(token::LBRACKET))
        {
            if (peek().type == token::LBRACKET && tok_.pos.begin.line == base->loc().begin.line)
            {
                auto loc = tok_.pos;
                auto c = parse_expr_pointer(call::mode::normal);
                base = expr_method::make(loc, std::move(base), std::move(c));
            }
            else
            {
                if (first && (base->is<expr_anim>() || base->is<expr_level>()))
                    error(tok_.pos, std::format("expected '.' after '{}'", base->is<expr_anim>() ? "anim" : "level"));

                auto loc = tok_.pos;
                advance();
                auto key = parse_expr();
                expect(token::RBRACKET);
                base = expr_array::make(loc, std::move(base), std::move(key));
            }
        }
        else if (check(token::DOT))
        {
            if (first && base->is<expr_game>())
                error(tok_.pos, "expected '[' after 'game'");

            auto loc = tok_.pos;
            advance();

            if (check(token::SIZE))
            {
                advance();
                base = expr_size::make(loc, std::move(base));
            }
            else
            {
                auto field = parse_expr_identifier_nosize();
                base = expr_field::make(loc, std::move(base), std::move(field));
            }
        }
        else if (is_call_start() && tok_.pos.begin.line == base->loc().begin.line)
        {
            auto loc = tok_.pos;
            auto mode = call::mode::normal;

            if (check(token::THREAD))
            {
                mode = call::mode::thread;
                advance();
            }

            auto c = parse_expr_call(mode);
            base = expr_method::make(loc, std::move(base), std::move(c));
        }
        else
        {
            break;
        }

        first = false;
    }

    return base;
}

auto parser::parse_expr_call(call::mode mode) -> call::ptr
{
    if (check(token::LBRACKET) && peek().type == token::LBRACKET)
    {
        return parse_expr_pointer(mode);
    }

    return parse_expr_function(mode);
}

auto parser::parse_expr_function(call::mode mode) -> call::ptr
{
    auto loc = tok_.pos;

    if (check(token::NAME) && peek().type == token::DOUBLECOLON)
    {
        auto path_tok = advance();
        advance(); // consume ::
        auto name_tok = expect(token::NAME);
        expect(token::LPAREN);
        auto args = parse_expr_arguments();
        expect(token::RPAREN);
        return expr_function::make(loc,
            expr_path::make(path_tok.pos, path_tok.data),
            expr_identifier::make(name_tok.pos, name_tok.data),
            std::move(args), mode);
    }

    if (check(token::PATH) && peek().type == token::DOUBLECOLON)
    {
        auto path_tok = advance();
        advance(); // consume ::
        auto name_tok = expect(token::NAME);
        expect(token::LPAREN);
        auto args = parse_expr_arguments();
        expect(token::RPAREN);
        return expr_function::make(loc,
            expr_path::make(path_tok.pos, path_tok.data),
            expr_identifier::make(name_tok.pos, name_tok.data),
            std::move(args), mode);
    }

    auto name_tok = expect(token::NAME);
    expect(token::LPAREN);
    auto args = parse_expr_arguments();
    expect(token::RPAREN);
    return expr_function::make(loc,
        expr_path::make(loc),
        expr_identifier::make(name_tok.pos, name_tok.data),
        std::move(args), mode);
}

auto parser::parse_expr_pointer(call::mode mode) -> call::ptr
{
    auto loc = tok_.pos;
    expect(token::LBRACKET);
    expect(token::LBRACKET);
    auto func = parse_expr();
    expect(token::RBRACKET);
    expect(token::RBRACKET);
    expect(token::LPAREN);
    auto args = parse_expr_arguments();
    expect(token::RPAREN);
    return expr_pointer::make(loc, std::move(func), std::move(args), mode);
}

auto parser::parse_expr_arguments() -> expr_arguments::ptr
{
    auto loc = tok_.pos;
    auto args = expr_arguments::make(loc);

    if (check(token::RPAREN))
        return args;

    args->list.push_back(parse_expr());

    while (match(token::COMMA))
    {
        args->list.push_back(parse_expr());
    }

    return args;
}

auto parser::parse_expr_arguments_no_empty() -> expr_arguments::ptr
{
    auto loc = tok_.pos;
    auto args = expr_arguments::make(loc);

    args->list.push_back(parse_expr());

    while (match(token::COMMA))
    {
        args->list.push_back(parse_expr());
    }

    return args;
}

auto parser::parse_expr_parameters() -> expr_parameters::ptr
{
    auto loc = tok_.pos;
    auto params = expr_parameters::make(loc);

    if (check(token::RPAREN))
        return params;

    auto parse_param = [&]() -> expr::ptr
    {
        auto id = parse_expr_identifier();

        if (match(token::ASSIGN))
        {
            auto val = parse_expr();
            return expr_assign::make(id->loc(), std::move(id), std::move(val), expr_assign::op::eq);
        }

        return id;
    };

    params->list.push_back(parse_param());

    while (match(token::COMMA))
    {
        params->list.push_back(parse_param());
    }

    return params;
}

auto parser::parse_expr_isdefined() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::ISDEFINED);
    expect(token::LPAREN);
    auto value = parse_expr();
    expect(token::RPAREN);
    return expr_isdefined::make(loc, std::move(value));
}

auto parser::parse_expr_abs() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::ABS);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    return expr_abs::make(loc, std::move(arg));
}

auto parser::parse_expr_gettime() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETTIME);
    expect(token::LPAREN);
    expect(token::RPAREN);
    return expr_gettime::make(loc);
}

auto parser::parse_expr_getdvar() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETDVAR);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    return expr_getdvar::make(loc, std::move(arg));
}

auto parser::parse_expr_getdvarint() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETDVARINT);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    return expr_getdvarint::make(loc, std::move(arg));
}

auto parser::parse_expr_getdvarfloat() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETDVARFLOAT);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    return expr_getdvarfloat::make(loc, std::move(arg));
}

auto parser::parse_expr_getdvarvector() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETDVARVECTOR);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    auto node = expr_getdvarvector::make(loc, std::move(arg));

    if (check(token::LBRACKET))
    {
        auto aloc = tok_.pos;
        advance();
        auto key = parse_expr();
        expect(token::RBRACKET);
        return expr_array::make(aloc, std::move(node), std::move(key));
    }

    return node;
}

auto parser::parse_expr_getdvarcolorred() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETDVARCOLORRED);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    return expr_getdvarcolorred::make(loc, std::move(arg));
}

auto parser::parse_expr_getdvarcolorgreen() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETDVARCOLORGREEN);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    return expr_getdvarcolorgreen::make(loc, std::move(arg));
}

auto parser::parse_expr_getdvarcolorblue() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETDVARCOLORBLUE);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    return expr_getdvarcolorblue::make(loc, std::move(arg));
}

auto parser::parse_expr_getdvarcoloralpha() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETDVARCOLORALPHA);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    return expr_getdvarcoloralpha::make(loc, std::move(arg));
}

auto parser::parse_expr_getfirstarraykey() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETFIRSTARRAYKEY);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);
    return expr_getfirstarraykey::make(loc, std::move(arg));
}

auto parser::parse_expr_getnextarraykey() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::GETNEXTARRAYKEY);
    expect(token::LPAREN);
    auto arg1 = parse_expr();
    expect(token::COMMA);
    auto arg2 = parse_expr();
    expect(token::RPAREN);
    return expr_getnextarraykey::make(loc, std::move(arg1), std::move(arg2));
}

auto parser::parse_expr_vectorscale() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::VECTORSCALE);
    expect(token::LPAREN);
    auto arg1 = parse_expr();
    expect(token::COMMA);
    auto arg2 = parse_expr();
    expect(token::RPAREN);

    auto node = expr_vectorscale::make(loc, std::move(arg1), std::move(arg2));

    if (check(token::LBRACKET))
    {
        auto aloc = tok_.pos;
        advance();
        auto key = parse_expr();
        expect(token::RBRACKET);
        return expr_array::make(aloc, std::move(node), std::move(key));
    }

    return node;
}

auto parser::parse_expr_anglestoup() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::ANGLESTOUP);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);

    auto node = expr_anglestoup::make(loc, std::move(arg));

    if (check(token::LBRACKET))
    {
        auto aloc = tok_.pos;
        advance();
        auto key = parse_expr();
        expect(token::RBRACKET);
        return expr_array::make(aloc, std::move(node), std::move(key));
    }

    return node;
}

auto parser::parse_expr_anglestoright() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::ANGLESTORIGHT);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);

    auto node = expr_anglestoright::make(loc, std::move(arg));

    if (check(token::LBRACKET))
    {
        auto aloc = tok_.pos;
        advance();
        auto key = parse_expr();
        expect(token::RBRACKET);
        return expr_array::make(aloc, std::move(node), std::move(key));
    }

    return node;
}

auto parser::parse_expr_anglestoforward() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::ANGLESTOFORWARD);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);

    auto node = expr_anglestoforward::make(loc, std::move(arg));

    if (check(token::LBRACKET))
    {
        auto aloc = tok_.pos;
        advance();
        auto key = parse_expr();
        expect(token::RBRACKET);
        return expr_array::make(aloc, std::move(node), std::move(key));
    }

    return node;
}

auto parser::parse_expr_angleclamp180() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::ANGLECLAMP180);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);

    auto node = expr_angleclamp180::make(loc, std::move(arg));

    if (check(token::LBRACKET))
    {
        auto aloc = tok_.pos;
        advance();
        auto key = parse_expr();
        expect(token::RBRACKET);
        return expr_array::make(aloc, std::move(node), std::move(key));
    }

    return node;
}

auto parser::parse_expr_vectortoangles() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::VECTORTOANGLES);
    expect(token::LPAREN);
    auto arg = parse_expr();
    expect(token::RPAREN);

    auto node = expr_vectortoangles::make(loc, std::move(arg));

    if (check(token::LBRACKET))
    {
        auto aloc = tok_.pos;
        advance();
        auto key = parse_expr();
        expect(token::RBRACKET);
        return expr_array::make(aloc, std::move(node), std::move(key));
    }

    return node;
}

auto parser::parse_expr_paren_or_vector() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::LPAREN);
    auto first = parse_expr();

    if (match(token::COMMA))
    {
        auto second = parse_expr();
        expect(token::COMMA);
        auto third = parse_expr();
        expect(token::RPAREN);
        return expr_vector::make(loc, std::move(first), std::move(second), std::move(third));
    }

    expect(token::RPAREN);
    return expr_paren::make(loc, std::move(first));
}

auto parser::parse_expr_reference() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::DOUBLECOLON);
    auto name = parse_expr_identifier();
    return expr_reference::make(loc, expr_path::make(loc), std::move(name));
}

auto parser::parse_expr_identifier() -> expr_identifier::ptr
{
    auto loc = tok_.pos;

    if (check(token::NAME))
    {
        auto val = tok_.data;
        advance();
        return expr_identifier::make(loc, val);
    }

    if (check(token::SIZE))
    {
        advance();
        return expr_identifier::make(loc, "size");
    }

    error(std::format("expected identifier, got '{}'", tok_.to_string()));
}

auto parser::parse_expr_identifier_nosize() -> expr_identifier::ptr
{
    auto loc = tok_.pos;

    if (check(token::NAME))
    {
        auto val = tok_.data;
        advance();
        return expr_identifier::make(loc, val);
    }

    if (check(token::WAIT))
    {
        advance();
        return expr_identifier::make(loc, "wait");
    }

    error(std::format("expected identifier, got '{}'", tok_.to_string()));
}

auto parser::parse_expr_path() -> expr_path::ptr
{
    auto loc = tok_.pos;

    if (check(token::NAME))
    {
        auto val = tok_.data;
        advance();
        return expr_path::make(loc, val);
    }

    if (check(token::PATH))
    {
        auto val = tok_.data;
        advance();
        return expr_path::make(loc, val);
    }

    error(std::format("expected path, got '{}'", tok_.to_string()));
}

auto parser::parse_expr_string() -> expr_string::ptr
{
    auto loc = tok_.pos;
    auto val = tok_.data;
    expect(token::STRING);
    return expr_string::make(loc, val);
}

auto parser::parse_expr_animation() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::MOD);

    if (!check(token::NAME))
        error(std::format("expected animation identifier, got '{}'", tok_.to_string()));

    auto val = tok_.data;
    advance();

    if (match(token::DOUBLECOLON))
    {
        if (!check(token::NAME))
            error(std::format("expected animation identifier, got '{}'", tok_.to_string()));

        auto val2 = tok_.data;
        advance();
        return expr_animation::make(loc, val, val2);
    }

    return expr_animation::make(loc, "", val);
}

auto parser::parse_switch(stmt_switch& stm) -> void
{
    auto body = stmt_list::make(stm.body->block->loc());
    auto curr = stmt::ptr{ nullptr };
    auto num = stm.body->block->list.size();

    for (auto i = 0u; i < num; i++)
    {
        auto& entry = stm.body->block->list[0];

        if (entry->is<stmt_case>() || entry->is<stmt_default>())
        {
            if (curr != nullptr)
            {
                body->list.push_back(std::move(curr));
            }

            curr = std::move(stm.body->block->list[0]);
            stm.body->block->list.erase(stm.body->block->list.begin());
        }
        else
        {
            if (curr != nullptr)
            {
                if (curr->is<stmt_case>())
                {
                    curr->as<stmt_case>().body->list.push_back(std::move(entry));
                    stm.body->block->list.erase(stm.body->block->list.begin());
                }
                else
                {
                    curr->as<stmt_default>().body->list.push_back(std::move(entry));
                    stm.body->block->list.erase(stm.body->block->list.begin());
                }
            }
            else
            {
                throw comp_error(entry->loc(), "missing case statement");
            }
        }
    }

    if (curr != nullptr)
    {
        body->list.push_back(std::move(curr));
    }

    stm.body->block = std::move(body);
}

auto parser::parse_assign_op() -> expr_assign::op
{
    auto k = tok_.type;
    advance();

    switch (k)
    {
        case token::ASSIGN:   return expr_assign::op::eq;
        case token::BITOREQ:  return expr_assign::op::bwor;
        case token::BITANDEQ: return expr_assign::op::bwand;
        case token::BITEXOREQ:return expr_assign::op::bwexor;
        case token::SHLEQ:    return expr_assign::op::shl;
        case token::SHREQ:    return expr_assign::op::shr;
        case token::PLUSEQ:   return expr_assign::op::add;
        case token::MINUSEQ:  return expr_assign::op::sub;
        case token::STAREQ:   return expr_assign::op::mul;
        case token::DIVEQ:    return expr_assign::op::div;
        case token::MODEQ:    return expr_assign::op::mod;
        default:
            error("expected assignment operator");
    }
}

auto parser::is_assign_op() -> bool
{
    switch (tok_.type)
    {
        case token::ASSIGN:
        case token::BITOREQ:
        case token::BITANDEQ:
        case token::BITEXOREQ:
        case token::SHLEQ:
        case token::SHREQ:
        case token::PLUSEQ:
        case token::MINUSEQ:
        case token::STAREQ:
        case token::DIVEQ:
        case token::MODEQ:
            return true;
        default:
            return false;
    }
}

auto parser::is_call_start() -> bool
{
    switch (tok_.type)
    {
        case token::THREAD:
            return true;
        case token::NAME:
            return peek().type == token::LPAREN || peek().type == token::DOUBLECOLON;
        case token::PATH:
            return peek().type == token::DOUBLECOLON;
        case token::LBRACKET:
            return peek().type == token::LBRACKET;
        default:
            return false;
    }
}

auto parser::is_lvalue(expr const& e) -> bool
{
    if (e.is<expr_identifier>())
        return true;

    if (e.is<expr_field>())
        return true;

    if (e.is<expr_array>())
        return is_no_call_chain(e);

    return false;
}

auto parser::is_no_call_chain(expr const& e) -> bool
{
    if (e.is<expr_call>() || e.is<expr_method>())
        return false;

    if (e.is<expr_array>())
        return is_no_call_chain(*e.as<expr_array>().obj);

    if (e.is<expr_field>())
        return is_no_call_chain(*e.as<expr_field>().obj);

    return true;
}

auto parser::is_call_or_method(expr const& e) -> bool
{
    return e.is<expr_call>() || e.is<expr_method>();
}

auto parser::check(token::kind k) -> bool
{
    return tok_.type == k;
}

auto parser::match(token::kind k) -> bool
{
    if (tok_.type == k)
    {
        advance();
        return true;
    }

    return false;
}

auto parser::expect(token::kind k) -> token
{
    if (tok_.type != k)
    {
        throw comp_error(tok_.pos, std::format("expected '{}', got '{}'",
            token(k, spacing::null, location{}).to_string(), tok_.to_string()));
    }

    return advance();
}

auto parser::peek() -> token&
{
    if (!has_next_)
    {
        next_ = read_token();
        has_next_ = true;
    }

    return next_;
}

auto parser::advance() -> token
{
    auto prev = std::move(tok_);

    if (has_next_)
    {
        tok_ = std::move(next_);
        has_next_ = false;
    }
    else
    {
        tok_ = read_token();
    }

    return prev;
}

auto parser::read_token() -> token
{
    auto tok = ppr_.process();

    if (tok.type == token::NAME)
    {
        tok.data = ctx_->make_token(tok.data);

        auto const it = keyword_map.find(tok.data);

        if (it != keyword_map.end())
        {
            tok.type = it->second;
        }
    }

    return tok;
}

auto parser::error(location const& loc, std::string const& msg) -> void
{
    throw comp_error(loc, msg);
}

auto parser::error(std::string const& msg) -> void
{
    throw comp_error(tok_.pos, msg);
}

} // namespace xsk::arc
