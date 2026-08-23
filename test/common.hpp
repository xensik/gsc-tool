// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/engine/iw5_pc.hpp"
#include "xsk/arc/engine/t6_pc.hpp"
#include "xsk/arc/engine/t7.hpp"

namespace xsk::test
{

// The lexer and the preprocessor are the same code in gsc and arc apart from the
// feature flags, so generic cases are written once and instantiated for both
// families with TEMPLATE_TEST_CASE. fam<Ctx> is the bridge: it hands out the types
// of the family a context belongs to.

struct gsc_family
{
    using asset = gsc::asset;
    using buffer = gsc::buffer;
    using token = gsc::token;
    using lexer = gsc::lexer;
    using preprocessor = gsc::preprocessor;
    using comp_error = gsc::comp_error;
    using ppr_error = gsc::ppr_error;
    using instance = gsc::instance;
    using build = gsc::build;
    using spacing = gsc::spacing;
    using assembly = gsc::assembly;
    using function = gsc::function;
    using instruction = gsc::instruction;
    using opcode = gsc::opcode;
};

struct arc_family
{
    using buffer = arc::buffer;
    using token = arc::token;
    using lexer = arc::lexer;
    using preprocessor = arc::preprocessor;
    using comp_error = arc::comp_error;
    using ppr_error = arc::ppr_error;
    using instance = arc::instance;
    using build = arc::build;
    using spacing = arc::spacing;
    using assembly = arc::assembly;
    using function = arc::function;
    using instruction = arc::instruction;
    using opcode = arc::opcode;
};

template <typename Ctx>
struct fam;

template <>
struct fam<gsc::iw5_pc::context> : gsc_family
{
};

template <>
struct fam<arc::t6::pc::context> : arc_family
{
};

template <>
struct fam<arc::t7::context> : arc_family
{
};

// ponytail: deliberate leak, in both helpers below. Building a context costs
// between 1 and 19 ms depending on the engine (t7 loads 180k hashes) and there is
// nothing worth releasing at exit; a static with a destructor would also trip
// -Wexit-time-destructors, which debug builds warn about.
template <typename Ctx>
auto ctx() -> Ctx*
{
    static Ctx* instance = [] {
        auto* c = new Ctx(fam<Ctx>::instance::server);
        c->init(fam<Ctx>::build::prod, nullptr);
        return c;
    }();

    return instance;
}

// Context with dev blocks enabled: '/#' and '#/' are only tokens under build::dev.
template <typename Ctx>
auto ctx_dev() -> Ctx*
{
    static Ctx* instance = [] {
        auto* c = new Ctx(fam<Ctx>::instance::server);
        c->init(fam<Ctx>::build::dev, nullptr);
        return c;
    }();

    return instance;
}

// The lexer keeps a pointer to the file name and tokens dereference it when
// printing their location, so it must outlive every token. A function-local
// static, not a namespace-scope one: the latter needs a global constructor,
// which debug builds warn about.
inline auto test_file() -> std::string const&
{
    static auto const* name = new std::string{ "test.gsc" };
    return *name;
}

template <typename Ctx>
auto lex_all(std::string_view src, Ctx* c = ctx<Ctx>()) -> std::vector<typename fam<Ctx>::token>
{
    using token = typename fam<Ctx>::token;

    auto lex = typename fam<Ctx>::lexer{ c, test_file(), src.data(), src.size() };
    auto out = std::vector<token>{};

    while (true)
    {
        auto tok = lex.lex();
        auto const end = tok.type == token::EOS;
        out.push_back(std::move(tok));

        if (end)
            return out;
    }
}

// The kinds in order and by name, without the NEWLINEs or the trailing EOS.
// Compared as text so a failure reads "expected '+' got 'integer'" instead of
// dumping two vectors of integers.
template <typename Ctx>
auto lex_names(std::string_view src, Ctx* c = ctx<Ctx>()) -> std::string
{
    using token = typename fam<Ctx>::token;

    auto out = std::string{};

    for (auto const& tok : lex_all<Ctx>(src, c))
    {
        if (tok.type == token::NEWLINE || tok.type == token::EOS)
            continue;

        if (!out.empty())
            out.append(" ");

        out.append(token::name(tok.type));
    }

    return out;
}

template <typename Ctx>
auto ppr_all(std::string_view src, Ctx* c = ctx<Ctx>()) -> std::vector<typename fam<Ctx>::token>
{
    using token = typename fam<Ctx>::token;

    auto ppr = typename fam<Ctx>::preprocessor{ c, test_file(), reinterpret_cast<u8 const*>(src.data()), src.size() };
    auto out = std::vector<token>{};

    while (true)
    {
        auto tok = ppr.process();

        if (tok.type == token::EOS)
            return out;

        out.push_back(std::move(tok));
    }
}

// The expansion as text, one space between tokens. This is the convenient way to
// compare against what a C preprocessor produces.
template <typename Ctx>
auto ppr_text(std::string_view src, Ctx* c = ctx<Ctx>()) -> std::string
{
    auto out = std::string{};

    for (auto const& tok : ppr_all<Ctx>(src, c))
    {
        if (!out.empty())
            out.append(" ");

        out.append(tok.to_string());
    }

    return out;
}

// Parse a source string and print the AST back out. The two generated header
// lines are dropped so cases can spell out just the code they expect.
template <typename Ctx>
auto print_src(std::string_view src, Ctx* c = ctx<Ctx>()) -> std::string
{
    auto prog = c->parser().parse_source(test_file(), reinterpret_cast<u8 const*>(src.data()), src.size());
    auto out = c->printer().print(*prog);
    auto str = std::string{ reinterpret_cast<char const*>(out.data()), out.size() };

    return str.substr(str.find('\n', str.find('\n') + 1) + 1);
}

// Same for the assembly printer, but the assembly comes in already built: only
// gsc parses text assembly back, arc::parser::parse_assembly is still a stub.
template <typename Ctx>
auto print_asm(typename fam<Ctx>::assembly const& data, Ctx* c = ctx<Ctx>()) -> std::string
{
    auto out = c->printer().print(data);
    auto str = std::string{ reinterpret_cast<char const*>(out.data()), out.size() };

    return str.substr(str.find('\n', str.find('\n') + 1) + 1);
}

} // namespace xsk::test
