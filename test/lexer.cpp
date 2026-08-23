// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "common.hpp"
#include <catch_amalgamated.hpp>

namespace xsk::test
{

using gsc_ctx = gsc::iw5_pc::context;
using arc_ctx = arc::t6::pc::context;

#define BOTH gsc_ctx, arc_ctx

TEMPLATE_TEST_CASE("lexer: end of input", "[lexer]", BOTH)
{
    using token = typename fam<TestType>::token;

    SECTION("empty input")
    {
        auto const toks = lex_all<TestType>("");
        REQUIRE(toks.size() == 2);
        REQUIRE(toks[0].type == token::NEWLINE);
        REQUIRE(toks[1].type == token::EOS);
    }

    SECTION("a missing trailing newline is synthesized")
    {
        auto const toks = lex_all<TestType>("a");
        REQUIRE(toks.size() == 3);
        REQUIRE(toks[0].type == token::NAME);
        REQUIRE(toks[1].type == token::NEWLINE);
        REQUIRE(toks[2].type == token::EOS);
    }

    SECTION("a present trailing newline is not duplicated")
    {
        auto const toks = lex_all<TestType>("a\n");
        REQUIRE(toks.size() == 3);
        REQUIRE(toks[1].type == token::NEWLINE);
        REQUIRE(toks[2].type == token::EOS);
    }
}

TEMPLATE_TEST_CASE("lexer: operators and punctuation", "[lexer]", BOTH)
{
    REQUIRE(lex_names<TestType>("+ - * / %") == "+ - * / %");
    REQUIRE(lex_names<TestType>("++ -- += -= *= /= %=") == "++ -- += -= *= /= %=");
    REQUIRE(lex_names<TestType>("| & ^ << >>") == "| & ^ << >>");
    REQUIRE(lex_names<TestType>("|= &= ^= <<= >>=") == "|= &= ^= <<= >>=");
    REQUIRE(lex_names<TestType>("< > <= >= != ==") == "< > <= >= != ==");
    REQUIRE(lex_names<TestType>("|| && ! ~ ?") == "|| && ! ~ ?");
    REQUIRE(lex_names<TestType>("( ) [ ] { }") == "( ) [ ] { }");
    REQUIRE(lex_names<TestType>(", ; : :: . .. ...") == ", ; : :: . .. ...");
    REQUIRE(lex_names<TestType>("=") == "=");
    REQUIRE(lex_names<TestType>("#") == "#");

    SECTION("maximal munch, no spaces")
    {
        REQUIRE(lex_names<TestType>("a+=b") == "identifier += identifier");
        REQUIRE(lex_names<TestType>("a<<=b") == "identifier <<= identifier");
        REQUIRE(lex_names<TestType>("a>>b") == "identifier >> identifier");
    }
}

TEMPLATE_TEST_CASE("lexer: identifiers", "[lexer]", BOTH)
{
    using token = typename fam<TestType>::token;

    SECTION("keywords come out as identifiers")
    {
        // turning NAME into IF/WHILE/... is the parser's job, not the lexer's
        REQUIRE(lex_names<TestType>("if while for return") == "identifier identifier identifier identifier");
    }

    SECTION("underscore and digits")
    {
        auto const toks = lex_all<TestType>("_a1 b_2");
        REQUIRE(toks[0].type == token::NAME);
        REQUIRE(toks[0].data == "_a1");
        REQUIRE(toks[1].data == "b_2");
    }

    SECTION("the lexer does not lowercase, the parser does")
    {
        auto const toks = lex_all<TestType>("FooBar");
        REQUIRE(toks[0].data == "FooBar");
    }
}

TEMPLATE_TEST_CASE("lexer: backslash paths", "[lexer]", BOTH)
{
    using token = typename fam<TestType>::token;

    SECTION("normalized to forward slash and run through make_token")
    {
        auto const toks = lex_all<TestType>("maps\\mp\\Gametypes");
        REQUIRE(toks[0].type == token::PATH);
        REQUIRE(toks[0].data == "maps/mp/gametypes");
    }

    SECTION("double backslash and trailing backslash are errors")
    {
        REQUIRE_THROWS_AS(lex_all<TestType>("a\\\\b"), typename fam<TestType>::comp_error);
        REQUIRE_THROWS_AS(lex_all<TestType>("a\\ "), typename fam<TestType>::comp_error);
    }
}

TEMPLATE_TEST_CASE("lexer: numbers", "[lexer]", BOTH)
{
    using token = typename fam<TestType>::token;

    auto data = [](auto const& toks, usize i) { return toks[i].data; };

    SECTION("non-decimal bases are converted to decimal")
    {
        auto const toks = lex_all<TestType>("0x1F 0b101 0o17");
        REQUIRE(toks[0].type == token::INT);
        REQUIRE(data(toks, 0) == "31");
        REQUIRE(data(toks, 1) == "5");
        REQUIRE(data(toks, 2) == "15");
    }

    SECTION("single quote as digit separator")
    {
        auto const toks = lex_all<TestType>("1'000'000");
        REQUIRE(toks[0].type == token::INT);
        REQUIRE(data(toks, 0) == "1000000");
    }

    SECTION("floats")
    {
        auto const toks = lex_all<TestType>("1.5 1.5f .5 1. 1e3 1E-3");
        for (auto i = 0u; i < 6; i++)
            REQUIRE(toks[i].type == token::FLT);

        REQUIRE(data(toks, 0) == "1.5");
        REQUIRE(data(toks, 2) == ".5");
        // an exponent always yields FLT, even when the value is integral
        REQUIRE(data(toks, 4) == "1e3");
    }

    SECTION("exponents")
    {
        for (auto const* src : { "1e5", "1E-3", "1e5f", "1.10272e-005", ".5e2" })
        {
            auto const toks = lex_all<TestType>(src);
            REQUIRE(toks[0].type == token::FLT);
            REQUIRE(toks[0].data == src);
        }

        // an exponent with no digits used to be accepted and produce a float
        // whose data could not be parsed back
        for (auto const* src : { "1e", "1e+", "1e-", "1e+f", "1E" })
            REQUIRE_THROWS_AS(lex_all<TestType>(src), typename fam<TestType>::comp_error);
    }

    SECTION("invalid literals")
    {
        REQUIRE_THROWS_AS(lex_all<TestType>("0x"), typename fam<TestType>::comp_error);
        REQUIRE_THROWS_AS(lex_all<TestType>("0b"), typename fam<TestType>::comp_error);
        REQUIRE_THROWS_AS(lex_all<TestType>("1.2.3"), typename fam<TestType>::comp_error);
        REQUIRE_THROWS_AS(lex_all<TestType>("1''0"), typename fam<TestType>::comp_error);
    }
}

TEMPLATE_TEST_CASE("lexer: strings", "[lexer]", BOTH)
{
    using token = typename fam<TestType>::token;

    SECTION("quotes and escapes")
    {
        auto const toks = lex_all<TestType>("\"a\\tb\\nc\\\"d\\\\e\"");
        REQUIRE(toks[0].type == token::STRING);
        REQUIRE(toks[0].data == "a\tb\nc\"d\\e");
    }

    SECTION("an unknown escape keeps the character as-is")
    {
        auto const toks = lex_all<TestType>("\"a\\qb\"");
        REQUIRE(toks[0].data == "aqb");
    }

    SECTION("localized string with &")
    {
        auto const toks = lex_all<TestType>("&\"MENU_OK\"");
        REQUIRE(toks[0].type == token::ISTRING);
        REQUIRE(toks[0].data == "MENU_OK");
    }

    SECTION("unterminated")
    {
        REQUIRE_THROWS_AS(lex_all<TestType>("\"abc"), typename fam<TestType>::comp_error);
        REQUIRE_THROWS_AS(lex_all<TestType>("\"abc\ndef\""), typename fam<TestType>::comp_error);
    }
}

TEMPLATE_TEST_CASE("lexer: comments", "[lexer]", BOTH)
{
    SECTION("line comment")
    {
        REQUIRE(lex_names<TestType>("a // b c\nd") == "identifier identifier");
    }

    SECTION("block comment, multiline included")
    {
        REQUIRE(lex_names<TestType>("a /* b\nc */ d") == "identifier identifier");
        REQUIRE(lex_names<TestType>("a/**/b") == "identifier identifier");
    }

    SECTION("doc comment /@ @/")
    {
        REQUIRE(lex_names<TestType>("a /@ doc @/ b") == "identifier identifier");
    }

    SECTION("unterminated, and a stray closer")
    {
        REQUIRE_THROWS_AS(lex_all<TestType>("a /* b"), typename fam<TestType>::comp_error);
        REQUIRE_THROWS_AS(lex_all<TestType>("a /@ b"), typename fam<TestType>::comp_error);
        REQUIRE_THROWS_AS(lex_all<TestType>("a */ b"), typename fam<TestType>::comp_error);
    }
}

TEMPLATE_TEST_CASE("lexer: spacing between tokens", "[lexer]", BOTH)
{
    using token = typename fam<TestType>::token;
    using spacing = typename fam<TestType>::spacing;

    // the preprocessor relies on this: '#' only opens a directive at the start of a
    // line, and '#' glued to a parameter is stringize
    SECTION("first of line, glued, and after a space")
    {
        auto const toks = lex_all<TestType>("a+b c");
        REQUIRE(toks[0].space == spacing::null);
        REQUIRE(toks[1].space == spacing::none);
        REQUIRE(toks[2].space == spacing::none);
        REQUIRE(toks[3].space == spacing::back);
    }

    SECTION("new line with indentation, whatever its width")
    {
        // the preprocessor checks null/empty to decide whether a '#' opens a
        // directive, so indentation must not degrade 'empty' into 'back'
        for (auto const* src : { "a\n b", "a\n  b", "a\n\t b", "a\n    b" })
        {
            auto const toks = lex_all<TestType>(src);
            auto const it = std::find_if(toks.begin(), toks.end(), [](auto const& t) { return t.type == token::NAME && t.data == "b"; });
            REQUIRE(it != toks.end());
            REQUIRE(it->space == spacing::empty);
        }
    }
}

TEMPLATE_TEST_CASE("lexer: location", "[lexer]", BOTH)
{
    using token = typename fam<TestType>::token;

    SECTION("line and column")
    {
        auto const toks = lex_all<TestType>("ab cd\n  ef");
        REQUIRE(toks[0].pos.begin.line == 1);
        REQUIRE(toks[0].pos.begin.column == 1);
        REQUIRE(toks[1].pos.begin.line == 1);
        REQUIRE(toks[1].pos.begin.column == 4);

        auto const it = std::find_if(toks.begin(), toks.end(), [](auto const& t) { return t.type == token::NAME && t.data == "ef"; });
        REQUIRE(it != toks.end());
        REQUIRE(it->pos.begin.line == 2);
        REQUIRE(it->pos.begin.column == 3);
    }

    SECTION("a block comment counts the lines it spans")
    {
        auto const toks = lex_all<TestType>("/*\n\n*/ a");
        REQUIRE(toks[0].pos.begin.line == 3);
    }

    SECTION("the file name reaches the token")
    {
        auto const toks = lex_all<TestType>("a");
        REQUIRE(toks[0].pos.begin.filename == &test_file());
    }
}

TEMPLATE_TEST_CASE("lexer: line continuation", "[lexer]", BOTH)
{
    using token = typename fam<TestType>::token;

    SECTION("a backslash before the newline joins both sides into one token")
    {
        auto const toks = lex_all<TestType>("a\\\nb");
        REQUIRE(toks[0].type == token::NAME);
        REQUIRE(toks[0].data == "ab");
    }

    SECTION("with a space after the newline they stay two tokens")
    {
        REQUIRE(lex_names<TestType>("a\\\n b") == "identifier identifier");
    }

    SECTION("a stray backslash is an error")
    {
        REQUIRE_THROWS_AS(lex_all<TestType>("a \\ b"), typename fam<TestType>::comp_error);
    }
}

TEMPLATE_TEST_CASE("lexer: unknown token", "[lexer]", BOTH)
{
    REQUIRE_THROWS_AS(lex_all<TestType>("@"), typename fam<TestType>::comp_error);
    REQUIRE_THROWS_AS(lex_all<TestType>("$"), typename fam<TestType>::comp_error);
}

// --- family specific ---

TEST_CASE("lexer gsc: dev blocks", "[lexer][gsc]")
{
    using token = gsc::token;

    // The lexer tokenises '/#' and '#/' in both builds and what is inside them is lexed
    // as ordinary code; dropping the block in a prod build is the compiler's job. Skipping
    // the text here instead used to end a block at a '#/' written inside a comment.
    SECTION("they are tokens under either build")
    {
        for (auto* c : { ctx<gsc_ctx>(), ctx_dev<gsc_ctx>() })
        {
            auto const toks = lex_all<gsc_ctx>("/# a #/", c);
            REQUIRE(toks[0].type == token::DEVBEGIN);
            REQUIRE(toks[1].type == token::NAME);
            REQUIRE(toks[2].type == token::DEVEND);
        }
    }

    SECTION("a '#/' inside a comment does not end the block")
    {
        REQUIRE(lex_names<gsc_ctx>("/# a // ends with #/ here\n b #/") == "/# identifier identifier #/");
    }

    SECTION("they cannot nest nor be left open")
    {
        REQUIRE_THROWS_AS(lex_all<gsc_ctx>("/# /# #/", ctx_dev<gsc_ctx>()), gsc::comp_error);
        REQUIRE_THROWS_AS(lex_all<gsc_ctx>("/# a", ctx_dev<gsc_ctx>()), gsc::comp_error);
        REQUIRE_THROWS_AS(lex_all<gsc_ctx>("a #/", ctx_dev<gsc_ctx>()), gsc::comp_error);
    }
}

TEST_CASE("lexer arc: operators gated by feature::size64", "[lexer][arc][feature]")
{
    using token = arc::token;

    // t6 does not carry size64; t7 does
    SECTION("t7 recognizes ===, !== and ->")
    {
        auto const toks = lex_all<arc::t7::context>("a === b !== c -> d", ctx<arc::t7::context>());
        REQUIRE(toks[1].type == token::SEQ);
        REQUIRE(toks[3].type == token::SNE);
        REQUIRE(toks[5].type == token::ARROW);
    }

    SECTION("t6 splits them into the ordinary operators")
    {
        auto const toks = lex_all<arc_ctx>("a === b");
        REQUIRE(toks[1].type == token::EQ);
        REQUIRE(toks[2].type == token::ASSIGN);
    }
}

} // namespace xsk::test
