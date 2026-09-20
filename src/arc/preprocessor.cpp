// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/preprocessor.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc
{

preprocessor::preprocessor(context* ctx, std::string const& name, u8 const* data, usize size) : ctx_{ ctx }
{
    lexer_.emplace(ctx, name, reinterpret_cast<char const*>(data), size);
    indents_.emplace();
    defines_.reserve(5);
    defines_.insert({ "__FILE__", { .type = define::BUILTIN, .vararg = false, .args = {}, .exp = {} } });
    defines_.insert({ "__LINE__", { .type = define::BUILTIN, .vararg = false, .args = {}, .exp = {} } });
    defines_.insert({ "__DATE__", { .type = define::BUILTIN, .vararg = false, .args = {}, .exp = {} } });
    defines_.insert({ "__TIME__", { .type = define::BUILTIN, .vararg = false, .args = {}, .exp = {} } });
    defines_.insert({ std::string(ctx->engine_name()), { .type = define::BUILTIN, .vararg = false, .args = {}, .exp = {} } });
    directives_.reserve(19);
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

    if (ctx_->features() & feature::size64)
    {
        directives_.insert({ "using", directive::USING });
        directives_.insert({ "insert", directive::INSERT });
        directives_.insert({ "precache", directive::PRECACHE });
        directives_.insert({ "namespace", directive::NAMESPACE });
    }

    std::tm l_time = {};
    get_local_time(l_time);
    get_date_define(&l_time);
    get_time_define(&l_time);
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

        if (auto* def = expandable(tok); def != nullptr)
        {
            expand(tok, *def);
            continue;
        }

        if (tok.type == token::NEWLINE)
            continue;

        return tok;
    }
}

auto preprocessor::push_header(location const& loc, std::string const& file) -> void
{
    try
    {
        auto name = std::format("{}.gsh", file);

        for (auto& inc : includes_)
        {
            if (inc == name)
                throw ppr_error(loc, std::format("recursive header inclusion {} at {}", name, includes_.back()));
        }

        auto data = ctx_->load_header(name);

        includes_.push_back(*std::get<0>(data));
        indents_.emplace();
        lexer_.emplace(ctx_, *std::get<0>(data), std::get<1>(data), std::get<2>(data));
    }
    catch (std::exception const& e)
    {
        throw error(std::format("parsing header file '{}': {}", file, e.what()));
    }
}

auto preprocessor::pop_header() -> void
{
    if (lexer_.size() > 1)
    {
        lexer_.pop();
        indents_.pop();
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
        if (!indents_.top().empty())
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
            case directive::INSERT:
                read_directive_insert(tok, next);
                return;
            case directive::USING:
                read_directive_using(tok, next);
                return;
            case directive::PRECACHE:
                read_directive_precache(tok, next);
                return;
            case directive::USINGTREE:
                read_directive_usingtree(tok, next);
                return;
            case directive::NAMESPACE:
                read_directive_namespace(tok, next);
                return;
            default:
                break;
        }
    }

    // C11 6.10.1p6: inside a skipped group only the nesting directives matter;
    // the rest does not even have to be a recognized directive name.
    if (skip_)
        return skip_line();

    throw ppr_error(next.pos, std::format("invalid preprocessing directive '{}'", next.data));
}

auto preprocessor::read_directive_if(token& /*unused*/) -> void
{
    auto skip = !evaluate();
    indents_.top().push({ directive::IF, skip, !skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_ifdef(token& /*unused*/) -> void
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

    indents_.top().push({ directive::IFDEF, skip, !skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_ifndef(token& /*unused*/) -> void
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

    indents_.top().push({ directive::IFNDEF, skip, !skip });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_elif(token& tok) -> void
{
    if (indents_.top().empty())
    {
        throw ppr_error(tok.pos, "#elif without #if");
    }

    auto dir = indents_.top().top();
    indents_.top().pop();
    skip_ -= dir.skip ? 1 : 0;

    if (dir.type == directive::ELSE)
    {
        throw ppr_error(tok.pos, "#elif after #else");
    }

    auto skip = !evaluate() || dir.exec;
    indents_.top().push({ directive::ELIF, skip, !skip || dir.exec });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_elifdef(token& tok) -> void
{
    if (indents_.top().empty())
    {
        throw ppr_error(tok.pos, "#elifdef without #if");
    }

    auto dir = indents_.top().top();
    indents_.top().pop();
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

        skip = !defines_.contains(name) || dir.exec;
    }

    indents_.top().push({ directive::ELIFDEF, skip, !skip || dir.exec });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_elifndef(token& tok) -> void
{
    if (indents_.top().empty())
    {
        throw ppr_error(tok.pos, "#elifdef without #if");
    }

    auto dir = indents_.top().top();
    indents_.top().pop();
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

        skip = defines_.contains(name) || dir.exec;
    }

    indents_.top().push({ directive::ELIFNDEF, skip, !skip || dir.exec });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_else(token& tok) -> void
{
    auto next = read_token();
    expect(next, token::NEWLINE);

    if (indents_.top().empty())
    {
        throw ppr_error(tok.pos, "#else without #if");
    }

    auto dir = indents_.top().top();
    indents_.top().pop();
    skip_ -= dir.skip ? 1 : 0;

    if (dir.type == directive::ELSE)
    {
        throw ppr_error(tok.pos, "#else after #else");
    }

    auto skip = dir.exec;
    indents_.top().push({ directive::ELSE, skip, dir.exec });
    skip_ += skip ? 1 : 0;
}

auto preprocessor::read_directive_endif(token& tok) -> void
{
    auto next = read_token();
    expect(next, token::NEWLINE);

    if (indents_.top().empty())
    {
        throw ppr_error(tok.pos, "#endif without #if");
    }

    auto dir = indents_.top().top();
    indents_.top().pop();
    skip_ -= dir.skip ? 1 : 0;
}

auto preprocessor::read_directive_define(token& /*unused*/) -> void
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
            defines_.insert({ name, define{ .type = define::PLAIN, .vararg = false, .args = {}, .exp = {} } });
            break;
        case token::LPAREN:
            if (next.space == spacing::none)
            {
                auto params = std::vector<token>{};
                auto last_comma = true;
                auto last_elips = false;

                while (true)
                {
                    next = read_token();

                    if (next.type == token::RPAREN)
                    {
                        if (last_comma && !params.empty() && !last_elips)
                            throw ppr_error(next.pos, "misplaced comma in macro param list");

                        break;
                    }
                    else if (next.type == token::NAME)
                    {
                        if (last_elips)
                            throw ppr_error(next.pos, "elipsis must be last in macro param list");
                        else if (!last_comma)
                            throw ppr_error(next.pos, "misplaced name in macro param list");
                        else
                        {
                            auto it = std::find_if(params.begin(), params.end(), [&next](token const& v) { return v.data == next.data; });

                            if (it != params.end())
                            {
                                throw ppr_error(next.pos, "duplicate macro parameter name");
                            }

                            params.push_back(next);
                            last_comma = false;
                        }
                    }
                    else if (next.type == token::ELLIPSIS)
                    {
                        if (!last_comma || last_elips)
                            throw ppr_error(next.pos, "misplaced elipsis in macro param list");

                        last_elips = true;
                        last_comma = false;
                    }
                    else if (next.type == token::COMMA)
                    {
                        if (last_elips)
                            throw ppr_error(next.pos, "elipsis must be last in macro param list");
                        if (last_comma)
                            throw ppr_error(next.pos, "misplaced comma in macro param list");
                        else
                            last_comma = true;
                    }
                    else
                        throw ppr_error(next.pos, "unexpected token in macro param list");
                }

                auto exp = std::vector<token>{};
                auto last_sharp = false;
                auto vaopt = 0u;
                next = read_token();

                while (next.type != token::NEWLINE)
                {
                    if (next.type == token::NAME)
                    {
                        auto it = std::find_if(params.begin(), params.end(), [&next](token const& v) { return v.data == next.data; });

                        if (it != params.end())
                        {
                            if (last_sharp)
                                exp.back().type = token::STRINGIZE;

                            next.type = token::MACROARG;
                            exp.push_back(std::move(next));
                        }
                        else if (next.data == "__VA_ARGS__")
                        {
                            if (!last_elips)
                                throw ppr_error(next.pos, "__VA_ARGS__ can only appear in the expansion of a variadic macro");

                            if (last_sharp)
                                exp.back().type = token::STRINGIZE;

                            next.type = token::MACROVAARGS;
                            exp.push_back(std::move(next));
                        }
                        else if (next.data == "__VA_OPT__")
                        {
                            if (!last_elips)
                                throw ppr_error(next.pos, "__VA_OPT__ can only appear in the expansion of a variadic macro");

                            if (last_sharp)
                                throw ppr_error(next.pos, "'#' is not followed by a macro parameter");

                            if (vaopt)
                                throw ppr_error(next.pos, "__VA_OPT__ cannot be nested");

                            auto const pos = next.pos;
                            next = read_token();
                            expect(next, token::LPAREN);

                            // the content accumulates into exp under the normal
                            // body rules, between MACROVAOPT and its end marker;
                            // expand() skips the whole span when __VA_ARGS__ is empty.
                            vaopt = 1;
                            exp.emplace_back(token::MACROVAOPT, spacing::none, pos);
                        }
                        else
                        {
                            // check for #animtree ??
                            if (last_sharp)
                                throw ppr_error(next.pos, "'#' is not followed by a macro parameter");

                            exp.push_back(std::move(next));
                        }
                    }
                    else if (vaopt && next.type == token::LPAREN)
                    {
                        vaopt++;
                        exp.push_back(std::move(next));
                    }
                    else if (vaopt && next.type == token::RPAREN)
                    {
                        if (--vaopt == 0)
                            exp.emplace_back(token::MACROVAOPTEND, next.space, next.pos);
                        else
                            exp.push_back(std::move(next));
                    }
                    else if (next.type == token::SHARP)
                    {
                        if (!last_sharp)
                        {
                            last_sharp = true;
                            exp.push_back(std::move(next));
                        }
                        else if (next.space == spacing::none)
                        {
                            exp.back().type = token::PASTE;
                        }
                        else
                        {
                            throw ppr_error(next.pos, "'#' is not followed by a macro parameter");
                        }
                    }
                    else
                    {
                        exp.push_back(std::move(next));
                    }

                    if (exp.back().type != token::SHARP)
                        last_sharp = false;

                    next = read_token();
                }

                expect(next, token::NEWLINE);

                if (vaopt)
                    throw ppr_error(next.pos, "unterminated __VA_OPT__");

                if (!exp.empty())
                {
                    if (exp.front().type == token::PASTE)
                        throw ppr_error(next.pos, "'##' cannot appear at start of macro expansion");

                    if (exp.back().type == token::PASTE)
                        throw ppr_error(next.pos, "'##' cannot appear at end of macro expansion");

                    if (exp.back().type == token::SHARP)
                        throw ppr_error(next.pos, "'#' is not followed by a macro parameter");
                }

                defines_.insert({ name, define{ .type = define::FUNCTION, .vararg = last_elips, .args = params, .exp = exp } });
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

                defines_.insert({ name, define{ .type = define::OBJECT, .vararg = false, .args = {}, .exp = exp } });
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
    if (skip_) return skip_line();

    throw ppr_error(tok.pos, "#pragma directive not supported");
}

auto preprocessor::read_directive_warning(token& tok) -> void
{
    if (skip_) return skip_line();

    throw ppr_error(tok.pos, "#warning directive not supported");
}

auto preprocessor::read_directive_error(token& tok) -> void
{
    if (skip_) return skip_line();

    throw ppr_error(tok.pos, "#error directive not supported");
}

auto preprocessor::read_directive_line(token& tok) -> void
{
    if (skip_) return skip_line();

    throw ppr_error(tok.pos, "#line directive not supported");
}

auto preprocessor::read_directive_include(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.emplace_front(token::INCLUDE, spacing::none, name.pos);
}

auto preprocessor::read_directive_inline(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.emplace_front(token::INLINE, spacing::none, name.pos);
}

auto preprocessor::read_directive_insert(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.push_front(token{ token::INSERT, spacing::none, name.pos });
}

auto preprocessor::read_directive_using(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.push_front(token{ token::USING, spacing::none, name.pos });
}

auto preprocessor::read_directive_precache(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.push_front(token{ token::PRECACHE, spacing::none, name.pos });
}

auto preprocessor::read_directive_usingtree(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.emplace_front(token::USINGTREE, spacing::none, name.pos);
}

auto preprocessor::read_directive_namespace(token& hash, token& name) -> void
{
    if (skip_) return;

    name.pos.begin = hash.pos.begin;
    tokens_.push_front(token{ token::NAMESPACE, spacing::none, name.pos });
}

auto preprocessor::read_hashtoken(token& hash) -> void
{
    if (skip_) return;

    auto next = read_token();

    if (next.type == token::NAME)
    {
        if (next.data == "animtree")
        {
            return read_hashtoken_animtree(hash, next);
        }
    }
    else if (next.type == token::STRING)
    {
        return read_hashtoken_hashstr(hash, next);
    }

    // if nothing match return '#'
    tokens_.push_front(std::move(next));
    tokens_.emplace_front(token::HASH, hash.space, hash.pos);
}

auto preprocessor::read_hashtoken_animtree(token& hash, token& name) -> void
{
    if (name.space == spacing::none)
    {
        name.pos.begin = hash.pos.begin;
        tokens_.emplace_front(token::ANIMTREE, spacing::none, name.pos);
    }
    else
    {
        // if '#   animtree' return 2 tokens
        tokens_.push_front(std::move(name));
        tokens_.emplace_front(token::HASH, hash.space, hash.pos);
    }
}

auto preprocessor::read_hashtoken_hashstr(token& hash, token& name) -> void
{
    if (name.space == spacing::none)
    {
        name.pos.begin = hash.pos.begin;
        tokens_.emplace_front(token::HASHSTR, spacing::none, name.pos, name.data);
    }
    else
    {
        // if '#  ""' return 2 tokens
        tokens_.push_front(std::move(name));
        tokens_.emplace_front(token::HASH, hash.space, hash.pos);
    }
}

auto preprocessor::expandable(token& tok) -> define*
{
    if (tok.type != token::NAME || tok.no_expand)
        return nullptr;

    auto const it = defines_.find(tok.data);

    if (it == defines_.end())
        return nullptr;

    if (expand_ && reject_.contains(tok.data))
    {
        // rejected by the blue paint: paint the token so no later rescan considers
        // it again, even once it leaves the protected scope.
        tok.no_expand = true;
        return nullptr;
    }

    return &it->second;
}

auto preprocessor::paste(token const& lhs, token const& rhs) -> token
{
    // C11 6.10.3.3: the two spellings are concatenated and the result is lexed
    // again; it has to come out as exactly one token.
    auto const text = lhs.spelling() + rhs.spelling();

    try
    {
        auto lex = lexer{ ctx_, *lhs.pos.begin.filename, text.data(), text.size() };
        auto res = lex.lex();

        if (res.type != token::EOS && res.type != token::NEWLINE)
        {
            if (auto const rest = lex.lex(); rest.type == token::NEWLINE || rest.type == token::EOS)
            {
                res.pos = lhs.pos;
                res.space = lhs.space;
                return res;
            }
        }
    }
    catch (comp_error const&)
    {
        // falls through to the error below
    }

    throw ppr_error(lhs.pos, std::format("pasting '{}' and '{}' does not give a valid token", lhs.spelling(), rhs.spelling()));
}

auto preprocessor::expand(token& tok, define& def) -> void
{
    if (def.type == define::PLAIN)
        return;

    if (def.type == define::BUILTIN)
    {
        if (tok.data == "__FILE__")
        {
            tokens_.emplace_front(token::STRING, tok.space, tok.pos, *tok.pos.begin.filename);
        }
        else if (tok.data == "__LINE__")
        {
            tokens_.emplace_front(token::STRING, tok.space, tok.pos, std::format("{}", tok.pos.begin.line));
        }
        else if (tok.data == "__DATE__")
        {
            tokens_.emplace_front(token::STRING, tok.space, tok.pos, date_);
        }
        else if (tok.data == "__TIME__")
        {
            tokens_.emplace_front(token::STRING, tok.space, tok.pos, time_);
        }
    }
    else if (def.type == define::OBJECT)
    {
        tokens_.emplace_front(token::MACROEND, tok.space, tok.pos, tok.data);

        for (auto it = def.exp.rbegin(); it != def.exp.rend(); ++it)
            tokens_.push_front(*it);

        tokens_.emplace_front(token::MACROBEGIN, tok.space, tok.pos, tok.data);
    }
    else if (def.type == define::FUNCTION)
    {
        auto next = next_token();

        if (next.type != token::LPAREN)
        {
            tokens_.push_front(next);
            tokens_.emplace_front(token::MACROEND, tok.space, tok.pos, tok.data);
            tokens_.push_front(tok);
            tokens_.emplace_front(token::MACROBEGIN, tok.space, tok.pos, tok.data);
            return;
        }

        auto args = expand_params(tok, def);

        // C11 6.10.3.1: a parameter is replaced by the fully expanded argument,
        // except as an operand of '#' or '##', where it goes in raw. Cached per
        // index because a body may use the same parameter more than once.
        auto args_exp = std::vector<std::vector<token>>(args.size());
        auto args_ready = std::vector<bool>(args.size(), false);

        // args.back() is __VA_ARGS__ when the macro is variadic
        auto const va_index = def.args.size();
        auto const va_empty = def.vararg && args[va_index].empty();

        // out of range either way, so it never collides with va_index
        auto const index_of = [&](std::string const& name) -> usize {
            for (auto n = 0u; n < def.args.size(); n++)
            {
                if (def.args[n].data == name)
                    return n;
            }

            return args.size();
        };

        auto exp = std::vector<token>{};
        exp.reserve(def.exp.size());

        // whether the token just substituted was a parameter that contributed
        // nothing, which is what decides how a following '##' behaves
        auto empty_arg = false;

        for (auto i = 0u; i < def.exp.size(); i++)
        {
            auto const before = exp.size();
            auto const was_arg = def.exp[i].type == token::MACROARG || def.exp[i].type == token::MACROVAARGS;

            if (def.exp[i].type == token::MACROARG)
            {
                auto const n = index_of(def.exp[i].data);

                if (n < args.size())
                {

                    // left operand of '##': the argument goes in unexpanded
                    auto const raw = (i + 1 < def.exp.size() && def.exp[i + 1].type == token::PASTE);

                    if (!raw && !args_ready[n])
                    {
                        args_exp[n] = expand_arg(args[n]);
                        args_ready[n] = true;
                    }

                    for (auto const& t : (raw ? args[n] : args_exp[n]))
                    {
                        exp.emplace_back(t.type, t.space, def.exp[i].pos, t.data);
                        exp.back().no_expand = t.no_expand;
                    }
                }
            }
            else if (def.exp[i].type == token::MACROVAARGS)
            {
                auto const raw = (i + 1 < def.exp.size() && def.exp[i + 1].type == token::PASTE);

                if (!raw && !args_ready[va_index])
                {
                    args_exp[va_index] = expand_arg(args[va_index]);
                    args_ready[va_index] = true;
                }

                for (auto const& t : (raw ? args[va_index] : args_exp[va_index]))
                {
                    exp.emplace_back(t.type, t.space, def.exp[i].pos, t.data);
                    exp.back().no_expand = t.no_expand;
                }
            }
            else if (def.exp[i].type == token::MACROVAOPT)
            {
                // with __VA_ARGS__ empty the whole content is dropped; otherwise
                // the following iterations process it as a normal body
                if (va_empty)
                {
                    while (i < def.exp.size() && def.exp[i].type != token::MACROVAOPTEND)
                        i++;
                }
            }
            else if (def.exp[i].type == token::MACROVAOPTEND)
            {
                // closes the block, nothing to emit
            }
            else if (def.exp[i].type == token::STRINGIZE)
            {
                auto const n = (def.exp[i + 1].type == token::MACROVAARGS) ? va_index : index_of(def.exp[i + 1].data);
                auto str = std::string{};

                if (n < args.size())
                {
                    for (usize idx = 0; auto const& t : args[n])
                    {
                        if (idx != 0 && t.space == spacing::back)
                            str.append(" ");
                        str.append(t.spelling());
                        idx++;
                    }
                }

                exp.emplace_back(token::STRING, def.exp[i].space, def.exp[i].pos, str);
                i++;
            }
            else if (def.exp[i].type == token::PASTE)
            {
                // the right operand goes in raw too, and may be several tokens
                auto const& rhs = def.exp[i + 1];
                auto rhs_toks = std::vector<token>{};

                if (rhs.type == token::MACROARG || rhs.type == token::MACROVAARGS)
                {
                    if (auto const n = (rhs.type == token::MACROVAARGS) ? va_index : index_of(rhs.data); n < args.size())
                        rhs_toks = args[n];
                }
                else
                {
                    rhs_toks.push_back(rhs);
                }

                if (!rhs_toks.empty())
                {
                    // only the last token of the left operand and the first of the
                    // right are pasted; the rest of the right side is appended as is
                    if (empty_arg || exp.empty())
                    {
                        // the left operand was an empty argument, nothing to paste to
                        for (auto const& t : rhs_toks)
                            exp.push_back(t);
                    }
                    else
                    {
                        auto const lhs = exp.back();
                        exp.pop_back();
                        exp.push_back(paste(lhs, rhs_toks.front()));

                        for (auto it = rhs_toks.begin() + 1; it != rhs_toks.end(); ++it)
                            exp.push_back(*it);
                    }
                }

                i++;
            }
            else
            {
                exp.push_back(def.exp[i]);
            }

            empty_arg = was_arg && exp.size() == before;
        }

        tokens_.emplace_front(token::MACROEND, tok.space, tok.pos, tok.data);

        for (auto it = exp.rbegin(); it != exp.rend(); ++it)
            tokens_.push_front(*it);

        tokens_.emplace_front(token::MACROBEGIN, tok.space, tok.pos, tok.data);
    }
}

auto preprocessor::expand_arg(std::vector<token> const& arg) -> std::vector<token>
{
    if (arg.empty())
        return {};

    // The argument is expanded in isolation, on its own queue and behind an EOS
    // guard: expand() can push tokens back as it does in the normal flow, and a
    // function-like macro at the end of the argument will not look for its '('
    // outside of it.
    auto saved = std::exchange(tokens_, std::deque<token>{ arg.begin(), arg.end() });
    tokens_.emplace_back(token::EOS, spacing::none, arg.back().pos);

    auto out = std::vector<token>{};
    out.reserve(arg.size());

    while (true)
    {
        auto tok = next_token();

        if (tok.type == token::EOS)
            break;

        // The markers are consumed here instead of travelling in the result: they
        // are scope delimiters for process(), and any other consumer (expand_params,
        // '#', '##') would take them for text. The argument comes out clean, and the
        // protection they carried is preserved by token::no_expand, which
        // expandable() paints token by token.
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

        if (auto* def = expandable(tok); def != nullptr)
        {
            expand(tok, *def);
            continue;
        }

        out.push_back(std::move(tok));
    }

    tokens_ = std::move(saved);

    return out;
}

auto preprocessor::expand_params(token& tok, define& def) -> std::vector<std::vector<token>>
{
    auto nest_paren = 0;
    auto args = std::vector<std::vector<token>>{};
    args.emplace_back();

    while (true)
    {
        auto next = next_token();

        if (next.type == token::EOS)
        {
            throw ppr_error(tok.pos, "unterminated function-like macro invocation");
        }
        else if (next.type == token::LPAREN)
        {
            nest_paren++;
            args.back().push_back(next);
        }
        else if (next.type == token::RPAREN)
        {
            if (nest_paren == 0)
                break;
            else
            {
                nest_paren--;
                args.back().push_back(next);
            }
        }
        else if (next.type == token::COMMA && nest_paren == 0 && !(def.vararg && args.size() > def.args.size()))
        {
            args.emplace_back();
        }
        else
        {
            args.back().push_back(next);
        }
    }

    if (def.args.empty() && !def.vararg && args.size() == 1 && args[0].empty())
    {
        args.pop_back();
    }

    if (args.size() < def.args.size())
    {
        throw ppr_error(tok.pos, "too few arguments provided to function-like macro invocation");
    }

    if (def.vararg)
    {
        // args.back() is always __VA_ARGS__, empty when nothing was passed
        if (args.size() == def.args.size())
            args.emplace_back();
    }
    else if (args.size() > def.args.size())
    {
        throw ppr_error(tok.pos, "too many arguments provided to function-like macro invocation");
    }

    return args;
}

auto preprocessor::expect(token& tok, token::kind expected, spacing /*unused*/) -> void
{
    if (tok.type != expected)
    {
        throw ppr_error(tok.pos, std::format("expected '{}', got '{}'", token::name(expected), tok.to_string()));
    }
}

auto preprocessor::evaluate() -> bool
{
    if (skip_)
    {
        skip_line();
        return false;
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
    bool last_def = false;
    bool last_paren = false;
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
            if (tok.data == "true")
            {
                last_def = false;
                last_paren = false;
                tok.type = token::TRUE;
                expr_.push_back(std::move(tok));
            }
            else if (tok.data == "false")
            {
                last_def = false;
                last_paren = false;
                tok.type = token::FALSE;
                expr_.push_back(std::move(tok));
            }
            else if (tok.data == "defined")
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

                if (auto* def = expandable(tok); def != nullptr)
                {
                    expand(tok, *def);
                }
                else // macro not defined, or painted by the blue paint
                {
                    expr_.emplace_back(token::FALSE, tok.space, tok.pos);
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

    throw ppr_error(eval_peek().pos, std::format("{}", msg));
}

auto preprocessor::eval_expr() -> i64
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

auto preprocessor::eval_expr_or() -> i64
{
    auto lval = eval_expr_and();

    while (eval_match(token::OR))
    {
        auto rval = eval_expr_and();
        lval = lval || rval;
    }

    return lval;
}

auto preprocessor::eval_expr_and() -> i64
{
    auto lval = eval_expr_bwor();

    while (eval_match(token::AND))
    {
        auto rval = eval_expr_bwor();
        lval = lval && rval;
    }

    return lval;
}

auto preprocessor::eval_expr_bwor() -> i64
{
    auto lval = eval_expr_bwexor();

    while (eval_match(token::BITOR))
    {
        auto rval = eval_expr_bwexor();
        lval = lval | rval;
    }

    return lval;
}

auto preprocessor::eval_expr_bwexor() -> i64
{
    auto lval = eval_expr_bwand();

    while (eval_match(token::BITEXOR))
    {
        auto rval = eval_expr_bwand();
        lval = lval ^ rval;
    }

    return lval;
}

auto preprocessor::eval_expr_bwand() -> i64
{
    auto lval = eval_expr_eq();

    while (eval_match(token::BITAND))
    {
        auto rval = eval_expr_eq();
        lval = lval & rval;
    }

    return lval;
}

auto preprocessor::eval_expr_eq() -> i64
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

auto preprocessor::eval_expr_lge() -> i64
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

auto preprocessor::eval_expr_shift() -> i64
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

auto preprocessor::eval_expr_add() -> i64
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

auto preprocessor::eval_expr_factor() -> i64
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

auto preprocessor::eval_expr_unary() -> i64
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

auto preprocessor::eval_expr_primary() -> i64
{
    if (eval_match(token::TRUE))
        return 1;

    if (eval_match(token::FALSE))
        return 0;

    // C11 6.10.1p4: #if arithmetic is done in intmax_t
    if (eval_match(token::FLT))
        return static_cast<i64>(std::stod(eval_prev().data));

    if (eval_match(token::INT))
    {
        auto const& val = eval_prev();

        try
        {
            return std::stoll(val.data);
        }
        catch (std::exception const&)
        {
            throw ppr_error(val.pos, std::format("integer literal '{}' is out of range", val.data));
        }
    }

    if (eval_match(token::LPAREN))
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

auto preprocessor::get_local_time(std::tm& l_time) -> void
{
    std::time_t t = 0;
    time(&t);
#ifndef _WIN32
    localtime_r(&t, &l_time);
#else
    localtime_s(&l_time, &t);
#endif
}

auto preprocessor::get_date_define(std::tm* time_p) -> void
{
    char buf[] = "??? ?? ????";
    std::strftime(buf, sizeof(buf), "%b %d %Y", time_p);
    date_ = std::string("\"").append(buf).append("\"");
}

auto preprocessor::get_time_define(std::tm* time_p) -> void
{
    char buf[] = "??:??:??";
    std::strftime(buf, sizeof(buf), "%T", time_p);
    time_ = std::string("\"").append(buf).append("\"");
}

} // namespace xsk::arc
