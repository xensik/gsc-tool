// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/gsc/parser.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc
{

namespace
{

std::unordered_map<std::string_view, token::kind> const keyword_map
{{
    { "endon", token::ENDON },
    { "notify", token::NOTIFY },
    { "wait", token::WAIT },
    { "waittill", token::WAITTILL },
    { "waittillmatch", token::WAITTILLMATCH },
    { "waittillframeend", token::WAITTILLFRAMEEND },
    { "waitframe", token::WAITFRAME },
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
    { "breakpoint", token::BREAKPOINT },
    { "prof_begin", token::PROFBEGIN },
    { "prof_end", token::PROFEND },
    { "assert", token::ASSERT },
    { "assertex", token::ASSERTEX },
    { "assertmsg", token::ASSERTMSG },
    { "thread", token::THREAD },
    { "childthread", token::CHILDTHREAD },
    { "thisthread", token::THISTHREAD },
    { "call", token::CALL },
    { "true", token::TRUE },
    { "false", token::FALSE },
    { "undefined", token::UNDEFINED },
    { "size", token::SIZE },
    { "game", token::GAME },
    { "self", token::SELF },
    { "anim", token::ANIM },
    { "level", token::LEVEL },
    { "isdefined", token::ISDEFINED },
    { "istrue", token::ISTRUE },
}};

} // anonymous namespace

parser::parser(context* ctx) : ctx_{ ctx },
    ppr_{ preprocessor{ ctx, "", nullptr, 0 } },
    tok_{ token::EOS, spacing::null, location{} },
    next_{ token::EOS, spacing::null, location{} },
    has_next_{ false }, index_{ 0 }
{
}

auto parser::parse_assembly(buffer const& data) -> assembly::ptr
{
    return parse_assembly(data.data, data.size);
}

auto parser::parse_assembly(std::vector<u8> const& data) -> assembly::ptr
{
    return parse_assembly(data.data(), data.size());
}

auto parser::parse_assembly(u8 const* data, usize size) -> assembly::ptr
{
    auto lines = utils::string::clean_buffer_lines(data, size);
    auto assembly = assembly::make();
    auto func = function::ptr{ nullptr };
    auto index = usize{ 1 };
    auto count = u16{ 0 };

    for (auto& line : lines)
    {
        if (line == "" || line.starts_with("//"))
            continue;

        if (line.starts_with("sub:"))
        {
            func = function::make();
            func->index = index;
            func->name = line.substr(4);
            func->id = ctx_->token_id(func->name);
            continue;
        }

        if (line.starts_with("end:") && func != nullptr)
        {
            func->size = index - func->index;
            assembly->functions.push_back(std::move(func));
            continue;
        }

        if (line.starts_with("loc_"))
        {
            func->labels[index] = line;
            continue;
        }

        auto opdata = utils::string::parse_code(line);

        if (count)
        {
            if (opdata[0] != "case" && opdata[0] != "default")
                throw asm_error("invalid instruction inside endswitch \""s + line + "\"");

            for (auto const& entry : opdata)
                func->instructions.back()->data.push_back(entry);

            count--;
            continue;
        }

        auto inst = instruction::make();
        inst->index = index;
        inst->opcode = ctx_->opcode_enum(opdata[0]);
        inst->size = ctx_->opcode_size(inst->opcode);
        opdata.erase(opdata.begin());
        inst->data = std::move(opdata);

        switch (inst->opcode)
        {
            case opcode::OP_GetVector:
                if (ctx_->endian() == endian::big)
                    inst->size += ((inst->index + 4) & ~3) - (inst->index + 1);
                break;
            case opcode::OP_endswitch:
                count = static_cast<u16>(std::stoul(inst->data[0]));
                inst->size += 7 * count;
                break;
            case opcode::OP_FormalParams:
                count = static_cast<u8>(std::stoul(inst->data[0]));
                inst->size += (ctx_->features() & feature::hash) ? count * 8 : count;
                break;
            default:
                break;
        }

        index += inst->size;
        func->instructions.push_back(std::move(inst));
    }

    return assembly;
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

    // decl_constant: NAME ASSIGN expr SEMICOLON
    if (check(token::NAME) && peek().type == token::ASSIGN)
    {
        return parse_decl_constant();
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

auto parser::parse_decl_constant() -> decl::ptr
{
    auto loc = tok_.pos;
    auto name = parse_expr_identifier();
    expect(token::ASSIGN);
    auto value = parse_expr();
    expect(token::SEMICOLON);
    ppr_.ban_header(loc);
    printf("%s", std::format("{}: constants deprecated, use #define instead\n", loc.print()).data());
    return decl_constant::make(loc, std::move(name), std::move(value));
}

auto parser::parse_decl_function() -> decl::ptr
{
    auto loc = tok_.pos;
    auto name = parse_expr_identifier();
    expect(token::LPAREN);
    auto params = parse_expr_parameters();
    expect(token::RPAREN);
    auto body = parse_stmt_comp();
    ppr_.ban_header(loc);
    return decl_function::make(loc, std::move(name), std::move(params), std::move(body));
}

auto parser::parse_stmt() -> stmt::ptr
{
    switch (tok_.type)
    {
        case token::LBRACE:           return parse_stmt_comp();
        case token::WAIT:             return parse_stmt_wait();
        case token::WAITTILLFRAMEEND: return parse_stmt_waittillframeend();
        case token::WAITFRAME:        return parse_stmt_waitframe();
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
        case token::BREAKPOINT:       return parse_stmt_breakpoint();
        case token::PROFBEGIN:        return parse_stmt_prof_begin();
        case token::PROFEND:          return parse_stmt_prof_end();
        case token::ASSERT:           return parse_stmt_assert();
        case token::ASSERTEX:         return parse_stmt_assertex();
        case token::ASSERTMSG:        return parse_stmt_assertmsg();
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

    // tuple assign
    if (check(token::LBRACKET) && peek().type != token::LBRACKET)
    {
        auto tup = parse_expr_tuple();
        expect(token::ASSIGN);
        auto rhs = parse_expr();
        return stmt_expr::make(loc, expr_assign::make(loc, std::move(tup), std::move(rhs), expr_assign::op::eq));
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

    // tuple assign
    if (check(token::LBRACKET) && peek().type != token::LBRACKET)
    {
        auto tup = parse_expr_tuple();
        expect(token::ASSIGN);
        auto rhs = parse_expr();
        return stmt_expr::make(loc, expr_assign::make(loc, std::move(tup), std::move(rhs), expr_assign::op::eq));
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

    // tuple assign
    if (check(token::LBRACKET) && peek().type != token::LBRACKET)
    {
        auto tup = parse_expr_tuple();
        expect(token::ASSIGN);
        auto rhs = parse_expr();
        expect(token::SEMICOLON);
        return stmt_expr::make(loc, expr_assign::make(loc, std::move(tup), std::move(rhs), expr_assign::op::eq));
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

    // call/method expression statement (Fix 7)
    if (!is_call_or_method(*obj))
        error(obj->loc(), "expected call, method, or assignment");
    expect(token::SEMICOLON);
    return stmt_expr::make(loc, std::move(obj));
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

auto parser::parse_stmt_waittill(expr::ptr obj) -> stmt::ptr
{
    auto loc = obj->loc();
    expect(token::WAITTILL);
    expect(token::LPAREN);
    auto event = parse_expr();

    if (match(token::COMMA))
    {
        auto args = parse_expr_arguments_waittill();
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

    if (match(token::LPAREN))
        expect(token::RPAREN);

    expect(token::SEMICOLON);
    return stmt_waittillframeend::make(loc);
}

auto parser::parse_stmt_waitframe() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::WAITFRAME);

    if (match(token::LPAREN))
        expect(token::RPAREN);

    expect(token::SEMICOLON);
    return stmt_waitframe::make(loc);
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
        auto array = expr_identifier::make(loc, std::format("_temp_{}", ++index_));
        expr::ptr key = (ctx_->features() & feature::foreach) ? expr_identifier::make(loc, std::format("_temp_{}", ++index_)) : std::move(ident1);
        return stmt_foreach::make(loc, std::move(container), std::move(ident2),
            (ctx_->features() & feature::foreach) ? std::move(ident1) : (expr::ptr)expr_empty::make(loc),
            std::move(array), std::move(key), std::move(body), true);
    }

    expect(token::IN);
    auto container = parse_expr();
    expect(token::RPAREN);
    auto body = parse_stmt();
    auto array = expr_identifier::make(loc, std::format("_temp_{}", ++index_));
    auto key = expr_identifier::make(loc, std::format("_temp_{}", ++index_));
    return stmt_foreach::make(loc, std::move(container), std::move(ident1), expr_empty::make(loc),
        std::move(array), std::move(key), std::move(body), false);
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

auto parser::parse_stmt_breakpoint() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::BREAKPOINT);
    expect(token::SEMICOLON);
    return stmt_breakpoint::make(loc);
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

auto parser::parse_stmt_assert() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::ASSERT);
    expect(token::LPAREN);
    auto args = parse_expr_arguments();
    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_assert::make(loc, std::move(args));
}

auto parser::parse_stmt_assertex() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::ASSERTEX);
    expect(token::LPAREN);
    auto args = parse_expr_arguments();
    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_assertex::make(loc, std::move(args));
}

auto parser::parse_stmt_assertmsg() -> stmt::ptr
{
    auto loc = tok_.pos;
    expect(token::ASSERTMSG);
    expect(token::LPAREN);
    auto args = parse_expr_arguments();
    expect(token::RPAREN);
    expect(token::SEMICOLON);
    return stmt_assertmsg::make(loc, std::move(args));
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
        case token::CHILDTHREAD:
        case token::CALL:
        {
            auto mode = call::mode::normal;

            switch (tok_.type)
            {
                case token::THREAD:      mode = call::mode::thread; break;
                case token::CHILDTHREAD: mode = call::mode::childthread; break;
                case token::CALL:        mode = call::mode::builtin; break;
                default: break;
            }

            advance();
            auto c = parse_expr_call(mode);
            return parse_expr_postfix(expr_call::make(loc, std::move(c)));
        }

        case token::DOUBLECOLON:
        {
            // ::name or ::name(args) — reference or unqualified call with path
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

        case token::ISTRUE:
            return parse_expr_istrue();

        case token::LBRACKET:
        {
            // [] empty array
            if (peek().type == token::RBRACKET)
            {
                advance();
                advance();
                return expr_empty_array::make(loc);
            }

            // always parse as add_array: [expr, expr, ...]
            auto node = parse_expr_add_array();

            // reinterpret [ [expr] ] followed by ( as [[expr]](args) pointer call
            if (check(token::LPAREN) && node->is<expr_add_array>())
            {
                auto& outer = node->as<expr_add_array>();

                if (outer.args->list.size() == 1 && outer.args->list[0]->is<expr_add_array>())
                {
                    auto& inner = outer.args->list[0]->as<expr_add_array>();

                    if (inner.args->list.size() == 1)
                    {
                        auto func = std::move(inner.args->list[0]);
                        advance(); // consume (
                        auto args = parse_expr_arguments();
                        expect(token::RPAREN);
                        auto ptr = expr_pointer::make(loc, std::move(func), std::move(args), call::mode::normal);
                        return parse_expr_postfix(expr_call::make(loc, std::move(ptr)));
                    }
                }
            }

            return node;
        }

        case token::LPAREN:
            return parse_expr_paren_or_vector();

        case token::THISTHREAD:
            advance();
            return expr_thisthread::make(loc);

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
            auto node = expr_istring::make(loc, val);
            if (check(token::DOT) && peek().type == token::SIZE)
            {
                auto dloc = tok_.pos;
                advance();
                advance();
                return expr_size::make(dloc, std::move(node));
            }
            return node;
        }

        case token::HASHSTR_DVAR:
        {
            auto val = tok_.data;
            advance();
            return expr_hash::make(loc, expr_hash::kind::dvar, val, false);
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

    // NAME or PATH — could be identifier, function call, or qualified reference/call
    if (check(token::NAME))
    {
        if (peek().type == token::DOUBLECOLON)
        {
            // path::name or path::name(args)
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
            // unqualified function call: name(args)
            auto name_tok = advance();
            advance(); // consume (
            auto args = parse_expr_arguments();
            expect(token::RPAREN);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(name_tok.pos, name_tok.data);
            auto func = expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal);
            return parse_expr_postfix(expr_call::make(loc, std::move(func)));
        }

        // just an identifier
        auto name_tok = advance();
        auto base = expr_identifier::make(name_tok.pos, name_tok.data);
        return parse_expr_postfix(std::move(base));
    }

    if (check(token::PATH))
    {
        if (peek().type == token::DOUBLECOLON)
        {
            // path::name or path::name(args)
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

        // standalone PATH as identifier
        auto path_tok = advance();
        auto base = expr_identifier::make(path_tok.pos, path_tok.data);
        return parse_expr_postfix(std::move(base));
    }

    // keywords that can start object chains
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

    // thread/childthread/call as method prefix on currently parsed object
    if (check(token::THREAD) || check(token::CHILDTHREAD) || check(token::CALL))
    {
        auto mode = call::mode::normal;

        switch (tok_.type)
        {
            case token::THREAD:      mode = call::mode::thread; break;
            case token::CHILDTHREAD: mode = call::mode::childthread; break;
            case token::CALL:        mode = call::mode::builtin; break;
            default: break;
        }

        advance();
        auto c = parse_expr_call(mode);
        return parse_expr_postfix(expr_call::make(loc, std::move(c)));
    }

    // [[ptr]](args) at object level
    if (check(token::LBRACKET) && peek().type == token::LBRACKET)
    {
        auto c = parse_expr_pointer(call::mode::normal);
        return parse_expr_postfix(expr_call::make(loc, std::move(c)));
    }

    // all other cases delegate to primary
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
                // pointer method call: obj [[func]](args)
                auto loc = tok_.pos;
                auto c = parse_expr_pointer(call::mode::normal);
                base = expr_method::make(loc, std::move(base), std::move(c));
            }
            else
            {
                // array access: obj[key]
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
            // method call: obj function(args)
            auto loc = tok_.pos;
            auto mode = call::mode::normal;

            if (check(token::THREAD))
            {
                mode = call::mode::thread;
                advance();
            }
            else if (check(token::CHILDTHREAD))
            {
                mode = call::mode::childthread;
                advance();
            }
            else if (check(token::CALL))
            {
                mode = call::mode::builtin;
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
        // path::name(args)
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
        // path::name(args)
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

    // name(args) — unqualified
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

auto parser::parse_expr_arguments_waittill() -> expr_arguments::ptr
{
    auto loc = tok_.pos;
    auto args = expr_arguments::make(loc);

    auto parse_waittill_arg = [&]() -> expr::ptr
    {
        if (check(token::NAME) || check(token::SIZE))
            return parse_expr_identifier();
        if (check(token::UNDEFINED))
        {
            auto uloc = tok_.pos;
            advance();
            return expr_undefined::make(uloc);
        }
        error("expected identifier or 'undefined' in waittill arguments");
    };

    args->list.push_back(parse_waittill_arg());

    while (match(token::COMMA))
    {
        args->list.push_back(parse_waittill_arg());
    }

    return args;
}

auto parser::parse_expr_parameters() -> expr_parameters::ptr
{
    auto loc = tok_.pos;
    auto params = expr_parameters::make(loc);

    if (check(token::RPAREN))
        return params;

    params->list.push_back(parse_expr_identifier());

    while (match(token::COMMA))
    {
        params->list.push_back(parse_expr_identifier());
    }

    return params;
}

auto parser::parse_expr_add_array() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::LBRACKET);
    auto args = parse_expr_arguments_no_empty();
    expect(token::RBRACKET);
    return expr_add_array::make(loc, std::move(args));
}

auto parser::parse_expr_reference() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::DOUBLECOLON);
    auto name = parse_expr_identifier();
    return expr_reference::make(loc, expr_path::make(loc), std::move(name));
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

auto parser::parse_expr_istrue() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::ISTRUE);
    expect(token::LPAREN);
    auto value = parse_expr();
    expect(token::RPAREN);
    return expr_istrue::make(loc, std::move(value));
}

auto parser::parse_expr_paren_or_vector() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::LPAREN);
    auto first = parse_expr();

    if (match(token::COMMA))
    {
        // vector: (x, y, z)
        auto second = parse_expr();
        expect(token::COMMA);
        auto third = parse_expr();
        expect(token::RPAREN);
        return expr_vector::make(loc, std::move(first), std::move(second), std::move(third));
    }

    expect(token::RPAREN);
    return expr_paren::make(loc, std::move(first));
}

auto parser::parse_expr_tuple() -> expr::ptr
{
    auto loc = tok_.pos;
    expect(token::LBRACKET);
    auto tup = expr_tuple::make(loc);

    // first element
    tup->list.push_back(parse_expr_object());
    if (!is_lvalue(*tup->list.back()))
        error(tup->list.back()->loc(), "expected lvalue in tuple");

    while (match(token::COMMA))
    {
        tup->list.push_back(parse_expr_object());
        if (!is_lvalue(*tup->list.back()))
            error(tup->list.back()->loc(), "expected lvalue in tuple");
    }

    expect(token::RBRACKET);
    tup->temp = expr_identifier::make(loc, std::format("_temp_{}", ++index_));
    return tup;
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
    return expr_animation::make(loc, val);
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
        case token::CHILDTHREAD:
        case token::CALL:
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
            if (it->second == token::WAITFRAME)
            {
                if (ctx_->features() & feature::waitframe)
                    tok.type = it->second;
            }
            else if (it->second == token::ISDEFINED || it->second == token::ISTRUE)
            {
                if (ctx_->features() & feature::boolfuncs)
                    tok.type = it->second;
            }
            else
            {
                tok.type = it->second;
            }
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

} // namespace xsk::gsc
