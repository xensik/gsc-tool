// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"
#include "preprocessor.hpp"
#include "context.hpp"
#include "parser.hpp"

namespace xsk::gsc
{

preprocessor::preprocessor(context const* ctx, std::string const& name, char const* data, usize size) : ctx_{ ctx }, curr_expr_{ 0 }, expand_{ 0 }, skip_{ false }
{
    lexer_.push(lexer{ ctx, name, data, size });
    defines_.reserve(4);
    defines_.insert({ "__FILE__", { define::BUILTIN, {}, {} }});
    defines_.insert({ "__LINE__", { define::BUILTIN, {}, {} }});
    defines_.insert({ "__DATE__", { define::BUILTIN, {}, {} }});
    defines_.insert({ "__TIME__", { define::BUILTIN, {}, {} }});
    directives_.reserve(15);
    directives_.insert({ "if", directive::IF });
    directives_.insert({ "ifdef", directive::IFDEF });
    directives_.insert({ "ifndef", directive::IFNDEF });
    directives_.insert({ "elif", directive::ELIF });
    directives_.insert({ "elifdef", directive::ELIFDEF });
    directives_.insert({ "elifndef", directive::ELIFNDEF });
    directives_.insert({ "else", directive::ELSE });
    directives_.insert({ "endif", directive::ENDIF });
    directives_.insert({ "define", directive::DEFINE });
    directives_.insert({ "undef", directive::UNDEF });
    directives_.insert({ "pragma", directive::PRAGMA });
    directives_.insert({ "warning", directive::WARNING });
    directives_.insert({ "error", directive::ERROR });
    directives_.insert({ "line", directive::LINE });
    directives_.insert({ "include", directive::INCLUDE });
    directives_.insert({ "inline", directive::INLINE });
    directives_.insert({ "using_animtree", directive::USINGTREE });
}

auto preprocessor::process() -> token
{
    while (true)
    {
        auto tok = next_token();

        if (tok.type == token::MACROBEGIN)
        {
            reject_.insert(tok.data);
            expand_++;
            continue;
        }

        if (tok.type == token::MACROEND)
        {
            reject_.erase(tok.data);
            expand_--;
            continue;
        }

        if (tok.type == token::SHARP)
        {
            if (!expand_ && (tok.space == spacing::null || tok.space == spacing::empty))
                read_directive(tok);
            else
                read_hashtoken(tok);
            continue;
        }

        if (skip_) continue;

        if (tok.type == token::NAME)
        {
            auto const it = defines_.find(tok.data);

            if (it != defines_.end() && (!expand_ || !reject_.contains(tok.data)))
            {
                expand(tok, it->second);
                continue;
            }
        }

        if (tok.type == token::NEWLINE)
            continue;

        return tok;
    }
}

auto preprocessor::push_header(std::string const& file) -> void
{
    try
    {
        auto name = fmt::format("{}.gsh", file);

        for (auto& inc : includes_)
        {
            if (inc == name)
                throw ppr_error(location{}, fmt::format("recursive header inclusion {} at {}", name, includes_.back()));
        }

        auto data = ctx_->header_file_data(name);

        includes_.push_back(*std::get<0>(data));
        lexer_.push(lexer{ ctx_, *std::get<0>(data), std::get<1>(data), std::get<2>(data) });
    }
    catch (std::exception const& e)
    {
        throw error(fmt::format("parsing header file '{}': {}", file, e.what()));
    }
}

auto preprocessor::pop_header() -> void
{
    if (lexer_.size() > 1)
    {
        lexer_.pop();
        includes_.erase(includes_.end() - 1);
    }
    else
    {
        throw error("no headers to pop");
    }
}

auto preprocessor::ban_header(location const& loc) -> void
{
    if (lexer_.size() > 1)
    {
        throw comp_error(loc, "not allowed inside a gsh file");
    }
}

auto preprocessor::skip_line() -> void
{
    auto tok = read_token();

    while (tok.type != token::NEWLINE)
        tok = read_token();
}

auto preprocessor::next_token() -> token
{
    if (!tokens_.empty())
    {
        auto tok = tokens_.front();
        tokens_.pop_front();

        return tok;
    }

    return read_token();
}

auto preprocessor::read_token() -> token
{
    auto tok = lexer_.top().lex();

    if (tok.type == token::EOS)
    {
        if (!indents_.empty())
        {
            skip_ = 0;
            // clear indents
            throw ppr_error(tok.pos, "missing #endif");
        }
        
        if (lexer_.size() > 1)
        {
            pop_header();
            return read_token();
        }
    }

    return tok;
}

auto preprocessor::read_directive(token& tok) -> void
{
    auto next = read_token();

    if (next.type == token::NEWLINE)
        return;

    expect(next, token::NAME);

    auto const it = directives_.find(next.data);

    if (it != directives_.end())
    {
        switch (it->second)
        {
            case directive::IF:
                read_directive_if(next);
                return;
            case directive::IFDEF:
                read_directive_ifdef(next);
                return;
            case directive::IFNDEF:
                read_directive_ifndef(next);
                return;
            case directive::ELIF:
                read_directive_elif(next);
                return;
            case directive::ELIFDEF:
                read_directive_elifdef(next);
                return;
            case directive::ELIFNDEF:
                read_directive_elifndef(next);
                return;
            case directive::ELSE:
                read_directive_else(next);
                return;
            case directive::ENDIF:
                read_directive_endif(next);
                return;
            case directive::PRAGMA:
                read_directive_pragma(next);
                return;
            case directive::WARNING:
                read_directive_warning(next);
                return;
            case directive::ERROR:
                read_directive_error(next);
                return;
            case directive::LINE:
                read_directive_line(next);
                return;
            case directive::DEFINE:
                read_directive_define(next);
                return;
            case directive::UNDEF:
                read_directive_undef(next);
                return;
            case directive::INCLUDE:
                read_directive_include(tok, next);
                return;
            case directive::INLINE:
                read_directive_inline(tok, next);
                return;
            case directive::USINGTREE:
                read_directive_usingtree(tok, next);
                return;
            default:
                break;
        }
    }

    throw ppr_error(next.pos, fmt::format("invalid preprocessing directive '{}'", next.data));
}

auto preprocessor::read_directive_if(token&) -> void
{
    auto skip = !evaluate();
    indents_.push({ directive::IF, skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_ifdef(token&) -> void
{
    auto skip = false;

    if (skip_)
    {
        skip_line();
    }
    else
    {
        auto tok = read_token();
        expect(tok, token::NAME);

        auto name = std::move(tok.data);

        tok = read_token();
        expect(tok, token::NEWLINE);

        skip = !defines_.contains(name);
    }

    indents_.push({ directive::IFDEF, skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_ifndef(token&) -> void
{
    auto skip = false;

    if (skip_)
    {
        skip_line();
    }
    else
    {
        auto tok = read_token();
        expect(tok, token::NAME);

        auto name = std::move(tok.data);

        tok = read_token();
        expect(tok, token::NEWLINE);

        skip = defines_.contains(name);
    }

    indents_.push({ directive::IFNDEF, skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_elif(token& tok) -> void
{
    if (indents_.empty())
    {
        throw ppr_error(tok.pos, "#elif without #if");
    }

    auto dir = indents_.top();
    indents_.pop();
    skip_ -= dir.skip ? 1 : 0;

    if (dir.type == directive::ELSE)
    {
        throw ppr_error(tok.pos, "#elif after #else");
    }

    auto skip = !evaluate();
    indents_.push({ directive::ELIF, skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_elifdef(token& tok) -> void
{
    if (indents_.empty())
    {
        throw ppr_error(tok.pos, "#elifdef without #if");
    }

    auto dir = indents_.top();
    indents_.pop();
    skip_ -= dir.skip ? 1 : 0;

    if (dir.type == directive::ELSE)
    {
        throw ppr_error(tok.pos, "#elifdef after #else");
    }

    auto skip = false;

    if (skip_)
    {
        skip_line();
    }
    else
    {
        auto next = read_token();
        expect(next, token::NAME);

        auto name = std::move(next.data);

        next = read_token();
        expect(next, token::NEWLINE);

        skip = !defines_.contains(name);
    }

    indents_.push({ directive::ELIFDEF, skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_elifndef(token& tok) -> void
{
    if (indents_.empty())
    {
        throw ppr_error(tok.pos, "#elifdef without #if");
    }

    auto dir = indents_.top();
    indents_.pop();
    skip_ -= dir.skip ? 1 : 0;

    if (dir.type == directive::ELSE)
    {
        throw ppr_error(tok.pos, "#elifdef after #else");
    }

    auto skip = false;

    if (skip_)
    {
        skip_line();
    }
    else
    {
        auto next = read_token();
        expect(next, token::NAME);

        auto name = std::move(next.data);

        next = read_token();
        expect(next, token::NEWLINE);

        skip = defines_.contains(name);
    }

    indents_.push({ directive::ELIFNDEF, skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_else(token& tok) -> void
{
    auto next = read_token();
    expect(next, token::NEWLINE);

    if (indents_.empty())
    {
        throw ppr_error(tok.pos, "#else without #if");
    }

    auto dir = indents_.top();
    indents_.pop();
    skip_ -= dir.skip ? 1 : 0;

    if (dir.type == directive::ELSE)
    {
        throw ppr_error(tok.pos, "#else after #else");
    }

    auto skip = !dir.skip;
    indents_.push({ directive::ELSE, skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_endif(token& tok) -> void
{
    auto next = read_token();
    expect(next, token::NEWLINE);

    if (indents_.empty())
    {
        throw ppr_error(tok.pos, "#endif without #if");
    }

    auto dir = indents_.top();
    indents_.pop();
    skip_ -= dir.skip ? 1 : 0;
}

auto preprocessor::read_directive_define(token&) -> void
{
    if (skip_) return skip_line();

    auto next = read_token();
    expect(next, token::NAME);

    auto name = std::move(next.data);

    if (defines_.contains(name))
    {
        throw ppr_error(next.pos, "macro redefinition");
    }

    next = read_token();

    switch (next.type)
    {
        case token::NEWLINE:
            defines_.insert({ name, define{ define::PLAIN, {}, {} }});
            break;
        case token::LPAREN:
            if (next.space == spacing::none)
            {
                throw ppr_error(next.pos, "function-like macros not supported");
                break;
            }
        default:
            if (next.space == spacing::back)
            {
                auto exp = std::vector<token>{};
                exp.push_back(std::move(next));
                next = read_token();

                while (next.type != token::NEWLINE)
                {
                    exp.push_back(std::move(next));
                    next = read_token();
                }

                expect(next, token::NEWLINE);

                defines_.insert({ name, define{ define::OBJECT, {}, exp }});
            }
            else
            {
                throw ppr_error(next.pos, "invalid macro definition");
            }
            break;
    }
}

auto preprocessor::read_directive_undef(token& tok) -> void
{
    if (skip_) return skip_line();

    auto next = read_token();
    expect(next, token::NAME);

    auto name = std::move(next.data);

    next = read_token();
    expect(next, token::NEWLINE);

    auto const it = defines_.find(name);

    if (it != defines_.end())
    {
        if (it->second.type == define::BUILTIN)
            throw ppr_error(tok.pos, "can't undefine builtin macro");

        defines_.erase(it);
    }
}

auto preprocessor::read_directive_pragma(token& tok) -> void
{
    throw ppr_error(tok.pos, "#pragma directive not supported");
}

auto preprocessor::read_directive_warning(token& tok) -> void
{
    throw ppr_error(tok.pos, "#warning directive not supported");
}

auto preprocessor::read_directive_error(token& tok) -> void
{
    throw ppr_error(tok.pos, "#error directive not supported");
}

auto preprocessor::read_directive_line(token& tok) -> void
{
    throw ppr_error(tok.pos, "#line directive not supported");
}

auto preprocessor::read_directive_include(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.push_front(token{ token::INCLUDE, spacing::none, name.pos });
}

auto preprocessor::read_directive_inline(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.push_front(token{ token::INLINE, spacing::none, name.pos });
}

auto preprocessor::read_directive_usingtree(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.push_front(token{ token::USINGTREE, spacing::none, name.pos });
}

auto preprocessor::read_hashtoken(token& tok) -> void
{
    if (skip_) return;

    auto next = read_token();

    if (next.type == token::NAME)
    {
        if (next.data == "animtree")
        {
            return read_hashtoken_animtree(tok, next);
        }
    }

    // TODO: iw9 hash literals #d"src_game"

    // if nothing match return '#'
    tokens_.push_front(std::move(next));
    tokens_.push_front(token{ token::HASH, tok.space, tok.pos });
}

auto preprocessor::read_hashtoken_animtree(token& hash, token& name) -> void
{
    if (name.space == spacing::none)
    {
        name.pos.begin = hash.pos.begin;
        tokens_.push_front(token{ token::ANIMTREE, spacing::none, name.pos });
    }
    else
    {
        // if '#   animtree' return 2 tokens
        tokens_.push_front(std::move(name));
        tokens_.push_front(token{ token::HASH, hash.space, hash.pos });
    }
}

auto preprocessor::expand(token& tok, define& def) -> void
{
    if (def.type == define::PLAIN)
        return;
    
    if (def.type == define::BUILTIN)
    {
        if (tok.data == "__FILE__")
        {
            tokens_.push_front(token{ token::STRING, tok.space, tok.pos, *tok.pos.begin.filename });
        }
        else if (tok.data == "__LINE__")
        {
            tokens_.push_front(token{ token::STRING, tok.space, tok.pos, fmt::format("{}", tok.pos.begin.line) });
        }
        else if (tok.data == "__DATE__")
        {
             tokens_.push_front(token{ token::STRING, tok.space, tok.pos, tok.data }); // TODO!
        }
        else if (tok.data == "__TIME__")
        {
            tokens_.push_front(token{ token::STRING, tok.space, tok.pos, tok.data }); // TODO!
        }
    }
    else if (def.type == define::OBJECT)
    {
        tokens_.push_front(token{ token::MACROEND, tok.space, tok.pos, tok.data });

        for (auto it = def.exp.rbegin(); it != def.exp.rend(); ++it)
        {
            tokens_.push_front(*it);
        }

        tokens_.push_front(token{ token::MACROBEGIN, tok.space, tok.pos, tok.data });
    }
    else if (def.type == define::FUNCTION)
    {
        // TODO!
    }
}

auto preprocessor::expect(token& tok, token::kind expected, spacing) -> void
{
    if (tok.type != expected)
    {
        throw ppr_error(tok.pos, fmt::format("expected {} found {}", (u8)expected, (u8)tok.type));
    }
}

auto preprocessor::evaluate() -> bool
{
    if (skip_)
    {
        skip_line();
        return 0;
    }

    // get expression tokens
    auto tok = read_token();
    while (tok.type != token::NEWLINE)
    {
        tokens_.push_back(tok);
        tok = read_token();
    }

    expect(tok, token::NEWLINE);
    tokens_.push_back(tok);

    // expand expression and add tokens to expr_ list
    bool last_def = false, last_paren = false;
    tok = next_token();
    while (tok.type != token::NEWLINE)
    {
        if (tok.type == token::MACROBEGIN)
        {
            reject_.insert(tok.data);
            expand_++;
        }
        else if (tok.type == token::MACROEND)
        {
            reject_.erase(tok.data);
            expand_--;
        }
        else if (tok.type == token::LPAREN && last_def && !last_paren)
        {
            last_paren = true;
            expr_.push_back(std::move(tok));
        }
        else if (tok.type == token::NAME)
        {
            if (tok.data == "defined")
            {
                last_def = true;
                tok.type = token::DEFINED;
                expr_.push_back(std::move(tok));
            }
            else if (last_def || (last_paren && last_def))
            {
                expr_.push_back(std::move(tok));
            }
            else
            {
                last_def = false;
                last_paren = false;

                auto const it = defines_.find(tok.data);

                if (it != defines_.end() && (!expand_ || !reject_.contains(tok.data)))
                {
                    expand(tok, it->second);
                }
                else // macro not defined
                {
                    expr_.push_back(token{ token::FALSE, tok.space, tok.pos });
                }
            }   
        }
        else
        {
            last_def = false;
            last_paren = false;
            expr_.push_back(std::move(tok));
        }

        tok = next_token();
    }

    expr_.push_back(std::move(tok));
    curr_expr_ = 0;

    auto result = static_cast<bool>(eval_expr());

    if (eval_peek().type != token::NEWLINE)
    {
        throw ppr_error(eval_peek().pos, "expected end of line in preprocessor expression");
    }

    expr_.clear();

    return result;
}

auto preprocessor::eval_next() -> token&
{
    if (!eval_atend()) curr_expr_++;
    return eval_prev();
}

auto preprocessor::eval_peek() -> token&
{
    return expr_.at(curr_expr_);
}

auto preprocessor::eval_prev() -> token&
{
    return expr_.at(curr_expr_ - 1);
}

auto preprocessor::eval_atend() -> bool
{
    return eval_peek().type == token::NEWLINE;
}

auto preprocessor::eval_check(token::kind type) -> bool
{
    if (eval_atend()) return false;
    return eval_peek().type == type;
}

auto preprocessor::eval_match(token::kind type) -> bool
{
    if (eval_check(type))
    {
        eval_next();
        return true;
    }

    return false;
}

auto preprocessor::eval_consume(token::kind type, std::string_view msg)
{
    if (eval_check(type)) return eval_next();

    throw ppr_error(eval_peek().pos, fmt::format("{}", msg));
}

auto preprocessor::eval_expr() -> i32
{
    auto cond = eval_expr_or();

    while (eval_match(token::QMARK))
    {
        auto lval = eval_expr();
        eval_consume(token::COLON, "expected ':' to match '?' ");
        auto rval = eval_expr();
        cond = cond ? lval : rval;
    }

    return cond;
}

auto preprocessor::eval_expr_or() -> i32
{
    auto lval = eval_expr_and();

    while (eval_match(token::OR))
    {
        auto rval = eval_expr_and();
        lval = lval || rval;
    }

    return lval;
}

auto preprocessor::eval_expr_and() -> i32
{
    auto lval = eval_expr_bwor();

    while (eval_match(token::AND))
    {
        auto rval = eval_expr_bwor();
        lval = lval && rval;
    }

    return lval;
}

auto preprocessor::eval_expr_bwor() -> i32
{
    auto lval = eval_expr_bwexor();

    while (eval_match(token::BITOR))
    {
        auto rval = eval_expr_bwexor();
        lval = lval | rval;
    }

    return lval;
}

auto preprocessor::eval_expr_bwexor() -> i32
{
    auto lval = eval_expr_bwand();

    while (eval_match(token::BITEXOR))
    {
        auto rval = eval_expr_bwand();
        lval = lval ^ rval;
    }

    return lval;
}

auto preprocessor::eval_expr_bwand() -> i32
{
    auto lval = eval_expr_eq();

    while (eval_match(token::BITAND))
    {
        auto rval = eval_expr_eq();
        lval = lval & rval;
    }

    return lval;
}

auto preprocessor::eval_expr_eq() -> i32
{
    auto lval = eval_expr_lge();

    while (eval_match(token::EQ) || eval_match(token::NE))
    {
        auto oper = eval_prev();
        auto rval = eval_expr_lge();

        switch (oper.type)
        {
            case token::EQ:
                lval = lval == rval;
                break;
            case token::NE:
                lval = lval != rval;
                break;
            default:
                break;
        }
    }

    return lval;
}

auto preprocessor::eval_expr_lge() -> i32
{
    auto lval = eval_expr_shift();

    while (eval_match(token::GT) || eval_match(token::GE) || eval_match(token::LT) || eval_match(token::LE))
    {
        auto oper = eval_prev();
        auto rval = eval_expr_shift();

        switch (oper.type)
        {
            case token::GT:
                lval = lval > rval;
                break;
            case token::GE:
                lval = lval >= rval;
                break;
            case token::LT:
                lval = lval < rval;
                break;
            case token::LE:
                lval = lval <= rval;
                break;
            default:
                break;
        }
    }

    return lval;
}

auto preprocessor::eval_expr_shift() -> i32
{
    auto lval = eval_expr_add();

    while (eval_match(token::SHL) || eval_match(token::SHR))
    {
        auto oper = eval_prev();
        auto rval = eval_expr_add();

        switch (oper.type)
        {
            case token::SHL:
                lval = lval << rval;
                break;
            case token::SHR:
                lval = lval >> rval;
                break;
            default:
                break;
        }
    }

    return lval;
}

auto preprocessor::eval_expr_add() -> i32
{
    auto lval = eval_expr_factor();

    while (eval_match(token::PLUS) || eval_match(token::MINUS))
    {
        auto oper = eval_prev();
        auto rval = eval_expr_factor();

        switch (oper.type)
        {
            case token::PLUS:
                lval = lval + rval;
                break;
            case token::MINUS:
                lval = lval - rval;
                break;
            default:
                break;
        }
    }

    return lval;
}

auto preprocessor::eval_expr_factor() -> i32
{
    auto lval = eval_expr_unary();

    while (eval_match(token::STAR) || eval_match(token::DIV) || eval_match(token::MOD))
    {
        auto oper = eval_prev();
        auto rval = eval_expr_unary();

        switch (oper.type)
        {
            case token::STAR:
                lval = lval * rval;
                break;
            case token::DIV:
                if (rval == 0)
                    throw ppr_error(oper.pos, "division by 0");
                lval = lval / rval;
                break;
            case token::MOD:
                if (rval == 0)
                    throw ppr_error(oper.pos, "division by 0");
                lval = lval % rval;
                break;
            default:
                break;
        }
    }

    return lval;
}

auto preprocessor::eval_expr_unary() -> i32
{
    if (eval_match(token::BANG) || eval_match(token::TILDE) || eval_match(token::PLUS) || eval_match(token::MINUS))
    {
        auto oper = eval_prev();
        auto rval = eval_expr_unary();

        switch (oper.type)
        {
            case token::BANG:
                return !rval;
            case token::TILDE:
                return ~rval;
            case token::PLUS:
                return rval;
            case token::MINUS:
                return -rval;
            default:
                break;
        }
    }

    return eval_expr_primary();
}

auto preprocessor::eval_expr_primary() -> i32
{
    if (eval_match(token::TRUE))
        return 1;
    
    if (eval_match(token::FALSE))
        return 0;
    
    if (eval_match(token::FLT))
        return static_cast<i32>(std::stof(eval_prev().data));
    
    if (eval_match(token::INT))
        return static_cast<i32>(std::stoi(eval_prev().data));
    
    if  (eval_match(token::LPAREN))
    {
        auto val = eval_expr();
        eval_consume(token::RPAREN, "expect ')' after expression.");
        return val;
    }

    if (eval_match(token::DEFINED))
    {
        if (eval_match(token::NAME) || eval_match(token::LPAREN))
        {
            auto val = eval_prev();

            if (val.type == token::NAME)
            {
                return defines_.contains(val.data);
            }
            else if (eval_match(token::NAME))
            {
                val = eval_prev();
                eval_consume(token::RPAREN, "expect ')' after defined( identifier.");
                return defines_.contains(val.data); 
            }

            throw ppr_error(eval_peek().pos, "expect identifier after defined(.");
        }

        throw ppr_error(eval_peek().pos, "expect identifier or '(' after defined.");
    }

    throw ppr_error(eval_peek().pos, "invalid preprocessor expression");
}

} // namespace xsk::gsc
