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

// The expansions compared here are contrasted against `clang -E -P`.

TEMPLATE_TEST_CASE("ppr: object-like define", "[ppr]", BOTH)
{
    REQUIRE(ppr_text<TestType>("#define X 1\nX\n") == "1");
    REQUIRE(ppr_text<TestType>("#define X 1 + 2\nX\n") == "1 + 2");
    REQUIRE(ppr_text<TestType>("#define X\nX\n").empty());
    REQUIRE(ppr_text<TestType>("#define X 1\nX X\n") == "1 1");

    SECTION("only the exact identifier expands")
    {
        REQUIRE(ppr_text<TestType>("#define X 1\nXY\n") == "XY");
    }

    SECTION("a macro can use another one, via rescan")
    {
        REQUIRE(ppr_text<TestType>("#define A 1\n#define B A\nB\n") == "1");
    }
}

TEMPLATE_TEST_CASE("ppr: function-like define", "[ppr]", BOTH)
{
    REQUIRE(ppr_text<TestType>("#define F(x) x\nF(1)\n") == "1");
    REQUIRE(ppr_text<TestType>("#define ADD(a, b) a + b\nADD(1, 2)\n") == "1 + 2");
    REQUIRE(ppr_text<TestType>("#define F() 9\nF()\n") == "9");

    SECTION("nested parentheses do not split arguments")
    {
        REQUIRE(ppr_text<TestType>("#define F(a, b) a - b\nF(g(1, 2), 3)\n") == "g ( 1 , 2 ) - 3");
    }

    SECTION("a repeated parameter is substituted at every use")
    {
        REQUIRE(ppr_text<TestType>("#define TWICE(x) x x\nTWICE(7)\n") == "7 7");
    }

    SECTION("with no parenthesis behind it, the name stays as-is")
    {
        REQUIRE(ppr_text<TestType>("#define F(x) x\nF\n") == "F");
    }

    SECTION("argument count")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(a, b) a\nF(1)\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(a) a\nF(1, 2)\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(a) a\nF(1\n"), typename fam<TestType>::ppr_error);
    }

    SECTION("invalid parameter list")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(a, a) a\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(a,) a\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(1) a\n"), typename fam<TestType>::ppr_error);
    }
}

TEMPLATE_TEST_CASE("ppr: pre-expanded arguments", "[ppr]", BOTH)
{
    // C11 6.10.3.1: the argument is expanded before substitution, except with # or ##
    SECTION("the double stringize sees the value, the single one sees the name")
    {
        auto const src = "#define V 42\n#define STR(x) #x\n#define XSTR(x) STR(x)\nSTR(V) XSTR(V)\n";
        REQUIRE(ppr_text<TestType>(src) == "V 42");
    }

    SECTION("a macro passed as an argument to another variadic one expands")
    {
        auto const src = "#define V 9\n#define P(...) q(__VA_ARGS__)\n#define X(...) P(__VA_ARGS__)\nX(V, V)\n";
        REQUIRE(ppr_text<TestType>(src) == "q ( 9 , 9 )");
    }
}

TEMPLATE_TEST_CASE("ppr: blue paint", "[ppr]", BOTH)
{
    // C11 6.10.3.4p2: an unreplaced name stops being a candidate for good
    SECTION("direct self-reference")
    {
        REQUIRE(ppr_text<TestType>("#define A A\nA\n") == "A");
        REQUIRE(ppr_text<TestType>("#define G (G)\nG\n") == "( G )");
    }

    SECTION("self-reference passed as an argument")
    {
        REQUIRE(ppr_text<TestType>("#define G (G)\n#define F(x) x\nF(G)\n") == "( G )");
    }

    SECTION("mutual recursion")
    {
        REQUIRE(ppr_text<TestType>("#define A B\n#define B A\nA\n") == "A");
        REQUIRE(ppr_text<TestType>("#define A B\n#define B A\n#define F(x) x\nF(A)\n") == "A");
    }
}

TEMPLATE_TEST_CASE("ppr: stringize", "[ppr]", BOTH)
{
    REQUIRE(ppr_text<TestType>("#define S(x) #x\nS(a)\n") == "a");
    REQUIRE(ppr_text<TestType>("#define S(x) #x\nS(a b)\n") == "a b");
    REQUIRE(ppr_text<TestType>("#define S(x) #x\nS(1 + 2)\n") == "1 + 2");

    SECTION("the result is a string")
    {
        auto const toks = ppr_all<TestType>("#define S(x) #x\nS(a)\n");
        REQUIRE(toks.size() == 1);
        REQUIRE(toks[0].type == fam<TestType>::token::STRING);
    }

    SECTION("string arguments keep their quotes, escaped")
    {
        // the token's data carries the quotes; escaping them again is the
        // printer's job when it writes the literal back out
        REQUIRE(ppr_text<TestType>("#define S(x) #x\nS(\"hi\")\n") == "\"hi\"");
        REQUIRE(ppr_text<TestType>("#define S(x) #x\nS(a \"q\" b)\n") == "a \"q\" b");
    }

    SECTION("'#' must be followed by a parameter")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define S(x) #y\n"), typename fam<TestType>::ppr_error);
    }
}

TEMPLATE_TEST_CASE("ppr: paste", "[ppr]", BOTH)
{
    REQUIRE(ppr_text<TestType>("#define CAT(a, b) a##b\nCAT(foo, bar)\n") == "foobar");

    SECTION("## operands are not pre-expanded, but the result is rescanned")
    {
        auto const src = "#define P pre\n#define CAT(a, b) a##b\n#define XCAT(a, b) CAT(a, b)\nCAT(P, X) XCAT(P, X)\n";
        REQUIRE(ppr_text<TestType>(src) == "PX preX");
    }

    SECTION("operands need not be identifiers, the result is lexed again")
    {
        REQUIRE(ppr_text<TestType>("#define C(a, b) a##b\nC(1, 2)\n") == "12");
        REQUIRE(ppr_text<TestType>("#define C(a, b) a##b\nC(foo, 3)\n") == "foo3");
        REQUIRE(ppr_text<TestType>("#define C(a, b) a##b\nC(1, 5e2)\n") == "15e2");
    }

    SECTION("an empty left operand leaves the right one alone")
    {
        REQUIRE(ppr_text<TestType>("#define C(a, b) a##b\nC(, y)\n") == "y");
        REQUIRE(ppr_text<TestType>("#define C(a, b) a##b\nC(x, )\n") == "x");
    }

    SECTION("a paste that does not form one token is an error")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define C(a, b) a##b\nC(1, +)\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define C(a, b) a##b\nC(x, ;)\n"), typename fam<TestType>::ppr_error);
    }

    SECTION("it can neither open nor close the expansion")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define C(a) ##a\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define C(a) a##\n"), typename fam<TestType>::ppr_error);
    }
}

TEMPLATE_TEST_CASE("ppr: variadic macros", "[ppr]", BOTH)
{
    SECTION("__VA_ARGS__ keeps the commas")
    {
        REQUIRE(ppr_text<TestType>("#define F(a, ...) g(a, __VA_ARGS__)\nF(1, 2, 3)\n") == "g ( 1 , 2 , 3 )");
        REQUIRE(ppr_text<TestType>("#define F(...) g(__VA_ARGS__)\nF(1, 2)\n") == "g ( 1 , 2 )");
    }

    SECTION("with no variadic arguments it comes out empty")
    {
        REQUIRE(ppr_text<TestType>("#define F(...) g(__VA_ARGS__)\nF()\n") == "g ( )");
        REQUIRE(ppr_text<TestType>("#define F(a, ...) g(a __VA_ARGS__)\nF(1)\n") == "g ( 1 )");
    }

    SECTION("__VA_OPT__ depends on whether there are variadic arguments")
    {
        auto const src = "#define L(f, ...) p(f __VA_OPT__(,) __VA_ARGS__)\nL(1) L(1, 2)\n";
        REQUIRE(ppr_text<TestType>(src) == "p ( 1 ) p ( 1 , 2 )");
    }

    SECTION("__VA_OPT__ accepts content with parentheses and parameters")
    {
        auto const src = "#define W(a, ...) h(a __VA_OPT__(+ f(__VA_ARGS__) + a))\nW(1) W(1, 2)\n";
        REQUIRE(ppr_text<TestType>(src) == "h ( 1 ) h ( 1 + f ( 2 ) + 1 )");
    }

    SECTION("#__VA_ARGS__ stringizes the whole set")
    {
        REQUIRE(ppr_text<TestType>("#define S(...) #__VA_ARGS__\nS(a, b)\n") == "a, b");
    }

    SECTION("they are only valid inside a variadic macro")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(x) __VA_ARGS__\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(x) __VA_OPT__(1)\n"), typename fam<TestType>::ppr_error);
    }

    SECTION("the ellipsis must come last, and __VA_OPT__ needs parentheses")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(..., a) a\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(...) __VA_OPT__ x\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define F(...) __VA_OPT__(__VA_OPT__(1))\n"), typename fam<TestType>::ppr_error);
    }
}

TEMPLATE_TEST_CASE("ppr: undef and redefinition", "[ppr]", BOTH)
{
    REQUIRE(ppr_text<TestType>("#define X 1\n#undef X\nX\n") == "X");
    REQUIRE(ppr_text<TestType>("#undef NOPE\nok\n") == "ok");

    SECTION("redefining without undef first is an error")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#define X 1\n#define X 2\n"), typename fam<TestType>::ppr_error);
    }

    SECTION("after #undef it can be defined again")
    {
        REQUIRE(ppr_text<TestType>("#define X 1\n#undef X\n#define X 2\nX\n") == "2");
    }

    SECTION("predefined macros cannot be undefined")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#undef __FILE__\n"), typename fam<TestType>::ppr_error);
    }
}

TEMPLATE_TEST_CASE("ppr: conditionals", "[ppr]", BOTH)
{
    REQUIRE(ppr_text<TestType>("#if 1\na\n#endif\n") == "a");
    REQUIRE(ppr_text<TestType>("#if 0\na\n#endif\n").empty());
    REQUIRE(ppr_text<TestType>("#if 0\na\n#else\nb\n#endif\n") == "b");
    REQUIRE(ppr_text<TestType>("#if 0\na\n#elif 1\nb\n#else\nc\n#endif\n") == "b");
    REQUIRE(ppr_text<TestType>("#if 0\na\n#elif 0\nb\n#else\nc\n#endif\n") == "c");

    SECTION("only the first true branch is taken")
    {
        REQUIRE(ppr_text<TestType>("#if 1\na\n#elif 1\nb\n#endif\n") == "a");
    }

    SECTION("nested")
    {
        REQUIRE(ppr_text<TestType>("#if 1\n#if 0\na\n#else\nb\n#endif\n#endif\n") == "b");
        REQUIRE(ppr_text<TestType>("#if 0\n#if 1\na\n#endif\n#endif\n").empty());
    }

    SECTION("ifdef, ifndef and their elif forms")
    {
        REQUIRE(ppr_text<TestType>("#define X 1\n#ifdef X\na\n#endif\n") == "a");
        REQUIRE(ppr_text<TestType>("#ifdef X\na\n#endif\n").empty());
        REQUIRE(ppr_text<TestType>("#ifndef X\na\n#endif\n") == "a");
        REQUIRE(ppr_text<TestType>("#define X 1\n#ifndef X\na\n#else\nb\n#endif\n") == "b");
        REQUIRE(ppr_text<TestType>("#ifdef X\na\n#elifdef Y\nb\n#else\nc\n#endif\n") == "c");
        REQUIRE(ppr_text<TestType>("#ifdef X\na\n#elifndef Y\nb\n#endif\n") == "b");
    }

    SECTION("unbalanced")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#if 1\na\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#endif\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#else\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#if 1\n#else\na\n#else\nb\n#endif\n"), typename fam<TestType>::ppr_error);
    }
}

TEMPLATE_TEST_CASE("ppr: #if expressions", "[ppr]", BOTH)
{
    auto yes = [](std::string_view expr) {
        return ppr_text<TestType>(std::format("#if {}\ny\n#endif\n", expr)) == "y";
    };

    SECTION("arithmetic and precedence")
    {
        REQUIRE(yes("1 + 2 * 3 == 7"));
        REQUIRE(yes("(1 + 2) * 3 == 9"));
        REQUIRE(yes("7 / 2 == 3"));
        REQUIRE(yes("7 % 2 == 1"));
        REQUIRE(yes("-1 + 2 == 1"));
        REQUIRE(yes("!0"));
        REQUIRE(yes("~0 == -1"));
    }

    SECTION("comparison, logical and bitwise")
    {
        REQUIRE(yes("2 > 1 && 1 < 2"));
        REQUIRE(yes("0 || 1"));
        REQUIRE(yes("(6 & 3) == 2"));
        REQUIRE(yes("(6 | 1) == 7"));
        REQUIRE(yes("(6 ^ 3) == 5"));
        REQUIRE(yes("(1 << 3) == 8"));
        REQUIRE(yes("(8 >> 3) == 1"));
    }

    SECTION("arithmetic is done in 64 bits")
    {
        // C11 6.10.1p4 asks for intmax_t; these all overflow a 32 bit evaluator
        REQUIRE(yes("2147483647 + 1 == 2147483648"));
        REQUIRE(yes("4294967296 / 2 == 2147483648"));
        REQUIRE(yes("(1 << 40) == 1099511627776"));
        REQUIRE(yes("-9223372036854775807 - 1 < 0"));
    }

    SECTION("a literal that does not fit is a clean error")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#if 99999999999999999999999 == 1\ny\n#endif\n"), typename fam<TestType>::ppr_error);
    }

    SECTION("ternary")
    {
        REQUIRE(yes("1 ? 1 : 0"));
        REQUIRE(yes("0 ? 0 : 1"));
    }

    SECTION("true, false and defined")
    {
        REQUIRE(yes("true"));
        REQUIRE(yes("!false"));
        REQUIRE(ppr_text<TestType>("#define X 1\n#if defined X\ny\n#endif\n") == "y");
        REQUIRE(ppr_text<TestType>("#define X 1\n#if defined(X)\ny\n#endif\n") == "y");
        REQUIRE(ppr_text<TestType>("#if defined(X)\ny\n#endif\n").empty());
        REQUIRE(ppr_text<TestType>("#if !defined(X)\ny\n#endif\n") == "y");
    }

    SECTION("an undefined identifier evaluates to false")
    {
        REQUIRE(ppr_text<TestType>("#if NOPE\ny\n#endif\n").empty());
        REQUIRE(ppr_text<TestType>("#if !NOPE\ny\n#endif\n") == "y");
    }

    SECTION("macros expand inside the expression")
    {
        REQUIRE(ppr_text<TestType>("#define N 3\n#if N == 3\ny\n#endif\n") == "y");
        REQUIRE(ppr_text<TestType>("#define N 3\n#define M N + 1\n#if M == 4\ny\n#endif\n") == "y");
    }

    SECTION("errors")
    {
        REQUIRE_THROWS_AS(ppr_all<TestType>("#if 1 / 0\ny\n#endif\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#if 1 % 0\ny\n#endif\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#if (1\ny\n#endif\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#if 1 1\ny\n#endif\n"), typename fam<TestType>::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<TestType>("#if\ny\n#endif\n"), typename fam<TestType>::ppr_error);
    }

    SECTION("what is skipped is not evaluated")
    {
        REQUIRE(ppr_text<TestType>("#if 0\n#if 1 / 0\n#endif\n#endif\nok\n") == "ok");
    }
}

TEMPLATE_TEST_CASE("ppr: predefined macros", "[ppr]", BOTH)
{
    using token = typename fam<TestType>::token;

    SECTION("__FILE__ and __LINE__ are strings")
    {
        auto const toks = ppr_all<TestType>("__FILE__\n");
        REQUIRE(toks.size() == 1);
        REQUIRE(toks[0].type == token::STRING);
        REQUIRE(toks[0].data == test_file());
    }

    SECTION("__LINE__ follows the line where it is used")
    {
        REQUIRE(ppr_text<TestType>("\n\n__LINE__\n") == "3");
    }

    SECTION("__DATE__ and __TIME__ are defined")
    {
        REQUIRE(ppr_text<TestType>("#ifdef __DATE__\ny\n#endif\n") == "y");
        REQUIRE(ppr_text<TestType>("#ifdef __TIME__\ny\n#endif\n") == "y");
    }
}

TEMPLATE_TEST_CASE("ppr: unsupported and unknown directives", "[ppr]", BOTH)
{
    REQUIRE_THROWS_AS(ppr_all<TestType>("#nope\n"), typename fam<TestType>::ppr_error);

    SECTION("declared but not implemented")
    {
        for (auto const* d : { "#pragma once\n", "#warning hey\n", "#error boom\n", "#line 5\n" })
            REQUIRE_THROWS_AS(ppr_all<TestType>(d), typename fam<TestType>::ppr_error);
    }

    SECTION("inside a discarded branch they are not looked at")
    {
        REQUIRE(ppr_text<TestType>("#if 0\n#error boom\n#endif\nok\n") == "ok");
        REQUIRE(ppr_text<TestType>("#if 0\n#nope\n#endif\nok\n") == "ok");
    }

    SECTION("a stray hash is not a directive")
    {
        REQUIRE(ppr_text<TestType>("a # b\n") == "a # b");
    }
}

// --- especificos ---

TEST_CASE("ppr gsc: the engine name is predefined", "[ppr][gsc][feature]")
{
    // the preprocessor defines engine_name(), which is uppercase; lowercasing the
    // identifier is the parser's job, so case matters here
    REQUIRE(ppr_text<gsc_ctx>("#ifdef IW5\ny\n#endif\n") == "y");
    REQUIRE(ppr_text<gsc_ctx>("#ifdef iw5\ny\n#endif\n").empty());
    REQUIRE(ppr_text<gsc_ctx>("#ifdef T6\ny\n#endif\n").empty());
}

TEST_CASE("ppr arc: the engine name is predefined", "[ppr][arc][feature]")
{
    REQUIRE(ppr_text<arc_ctx>("#ifdef T6\ny\n#endif\n") == "y");
    REQUIRE(ppr_text<arc_ctx>("#ifdef IW5\ny\n#endif\n").empty());
    REQUIRE(ppr_text<arc::t7::context>("#ifdef T7\ny\n#endif\n", ctx<arc::t7::context>()) == "y");
}

TEST_CASE("ppr arc: directives gated by feature::size64", "[ppr][arc][feature]")
{
    using token = arc::token;

    // #using, #insert, #precache and #namespace only exist from t7 onwards
    SECTION("t7 recognizes them")
    {
        auto const toks = ppr_all<arc::t7::context>("#using scripts\\shared\\foo;\n", ctx<arc::t7::context>());
        REQUIRE(toks[0].type == token::USING);

        auto const ins = ppr_all<arc::t7::context>("#insert scripts\\shared\\foo;\n", ctx<arc::t7::context>());
        REQUIRE(ins[0].type == token::INSERT);
    }

    SECTION("t6 does not, and rejects them as an unknown directive")
    {
        REQUIRE_THROWS_AS(ppr_all<arc_ctx>("#using foo;\n"), arc::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<arc_ctx>("#insert foo;\n"), arc::ppr_error);
        REQUIRE_THROWS_AS(ppr_all<arc_ctx>("#precache(\"x\", \"y\");\n"), arc::ppr_error);
    }
}

} // namespace xsk::test
