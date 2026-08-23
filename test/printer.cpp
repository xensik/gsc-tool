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

// The printer is checked through the parser: source in, canonical source out.
// The two families print the same syntax the same way, so the generic cases run
// on both and the family specific ones sit at the bottom.

TEMPLATE_TEST_CASE("printer: declarations", "[printer]", BOTH)
{
    SECTION("includes come first, one declaration per blank line")
    {
        auto const out = print_src<TestType>("#include maps\\mp\\_utility;\nmain(){ x = 1; }\nfoo(a, b){ return a; }\n");

        REQUIRE(out == R"(#include maps\mp\_utility;

main()
{
    x = 1;
}

foo( a, b )
{
    return a;
}
)");
    }

    SECTION("using_animtree")
    {
        auto const out = print_src<TestType>("#using_animtree(\"generic_human\");\nmain(){ x = 1; }\n");

        REQUIRE(out == R"(
#using_animtree("generic_human");

main()
{
    x = 1;
}
)");
    }
}

TEMPLATE_TEST_CASE("printer: statements", "[printer]", BOTH)
{
    SECTION("if / else if / else, single statements unbraced")
    {
        auto const out = print_src<TestType>("main(){ if (a) x = 1; else if (b) x = 2; else x = 3; }");

        REQUIRE(out == R"(
main()
{
    if ( a )
        x = 1;
    else if ( b )
        x = 2;
    else
        x = 3;
}
)");
    }

    SECTION("loops")
    {
        auto const out = print_src<TestType>("main(){ for (i = 0; i < 10; i++) { foo(); } while (1) { wait 0.05; } do { x--; } while (x > 0); foreach (k, v in arr) { v = k; } }");

        REQUIRE(out == R"(
main()
{
    for ( i = 0; i < 10; i++ )
    {
        foo();
    }

    while ( 1 )
    {
        wait 0.05;
    }

    do
    {
        x--;
    }
    while ( x > 0 );

    foreach ( k, v in arr )
    {
        v = k;
    }
}
)");
    }

    SECTION("switch")
    {
        auto const out = print_src<TestType>("main(){ switch (a) { case 1: case 2: break; default: return; } }");

        REQUIRE(out == R"(
main()
{
    switch ( a )
    {
        case 1:
        case 2:
            break;
        default:
            return;
    }
}
)");
    }

    SECTION("thread control")
    {
        auto const out = print_src<TestType>("main(){ self endon(\"death\"); self notify(\"x\", 1); self waittill(\"x\", a, b); waittillframeend; }");

        REQUIRE(out == R"(
main()
{
    self endon( "death" );
    self notify( "x", 1 );
    self waittill( "x", a, b );
    waittillframeend;
}
)");
    }
}

TEMPLATE_TEST_CASE("printer: for loop clauses", "[printer]", BOTH)
{
    SECTION("the init and iteration slots take calls and waits, not just assignments")
    {
        auto const out = print_src<TestType>("main(){ for (;; wait 0.05) x = 1; for (; a; foo()) y = 2; for (; b; self bar()) z = 3; for (;;) w = 4; }");

        REQUIRE(out == R"(
main()
{
    for ( ; ; wait 0.05 )
        x = 1;

    for ( ; a; foo() )
        y = 2;

    for ( ; b; self bar() )
        z = 3;

    for (;;)
        w = 4;
}
)");
    }
}

TEMPLATE_TEST_CASE("printer: expressions", "[printer]", BOTH)
{
    SECTION("parentheses are kept only where they were written")
    {
        auto const out = print_src<TestType>("main(){ f = (a + b) * c; g = a + b * c; h = (a && b) || (c == d); }");

        REQUIRE(out == R"(
main()
{
    f = ( a + b ) * c;
    g = a + b * c;
    h = ( a && b ) || ( c == d );
}
)");
    }

    SECTION("parentheses around the base of a postfix chain are grouping only")
    {
        // '( X ).f', '( X )[ i ]' and '( X ) m()' build the chain on X itself, so they
        // print — and compile — exactly like the unparenthesised form.
        auto const out = print_src<TestType>("main(){ a = (foo()).size; b = (self getangles())[1]; c = (self make_ent()) spawn_tag(); d = (1, 2, 3)[0]; }");

        REQUIRE(out == R"(
main()
{
    a = foo().size;
    b = self getangles()[1];
    c = self make_ent() spawn_tag();
    d = ( 1, 2, 3 )[0];
}
)");
    }

    SECTION("an operator base keeps its parentheses")
    {
        // The other half of the rule above: a postfix base binds tighter than any
        // operator, so dropping these parens would reparse as 'b + ( c.size )'.
        auto const out = print_src<TestType>("main(){ a = (b + c).size; d = (e + f)[1]; g = (h ? i : j).size; k = (-l)[0]; }");

        REQUIRE(out == R"(
main()
{
    a = ( b + c ).size;
    d = ( e + f )[1];
    g = ( h ? i : j ).size;
    k = ( -l )[0];
}
)");
    }

    SECTION("calls, pointers and references")
    {
        auto const out = print_src<TestType>("main(){ n = [[ p ]](1, 2); self thread [[ p ]](); p = ::main; a = &\"loc\"; }");

        REQUIRE(out == R"(
main()
{
    n = [[ p ]]( 1, 2 );
    self thread [[ p ]]();
    p = ::main;
    a = &"loc";
}
)");
    }

    SECTION("unary, subscript, field and vector")
    {
        auto const out = print_src<TestType>("main(){ z = !a; y = -b; w = ~c; b = a[1][2].c; v = (1, 2, 3); e = []; }");

        REQUIRE(out == R"(
main()
{
    z = !a;
    y = -b;
    w = ~c;
    b = a[1][2].c;
    v = ( 1, 2, 3 );
    e = [];
}
)");
    }

    SECTION("ternary")
    {
        auto const out = print_src<TestType>("main(){ x = a ? b : c; }");

        REQUIRE(out == R"(
main()
{
    x = a ? b : c;
}
)");
    }
}

TEMPLATE_TEST_CASE("printer: output reparses to itself", "[printer]", BOTH)
{
    auto const src = "main(){ if (a > 3) { for (i = 0; i < 10; i++) self thread foo(i, 1.5); } else switch (a) { case 1: break; } }";
    auto const once = print_src<TestType>(src);

    REQUIRE(print_src<TestType>(once) == once);
}

TEMPLATE_TEST_CASE("printer: dev blocks", "[printer][feature]", BOTH)
{
    // '/#' and '#/' print flush left, the way the decompiler emits them.
    auto const out = print_src<TestType>("main(){ x = 1; /# println(\"dev\"); #/ x = 2; }", ctx_dev<TestType>());

    REQUIRE(out == R"(
main()
{
    x = 1;
/#
    println( "dev" );
#/
    x = 2;
}
)");
}

TEST_CASE("printer: gsc technical statements are contextual keywords", "[printer][gsc]")
{
    // 'assert' and friends are keywords only when they are being called. maps/_spawner.gsc
    // has both spellings in the same file, so they have to coexist.
    auto const out = print_src<gsc_ctx>("main(){ assert = false; assert(1 == 1); if (assert) assert = true; prof_end = assert; }");

    REQUIRE(out == R"(
main()
{
    assert = false;
    assert( 1 == 1 );

    if ( assert )
        assert = true;

    prof_end = assert;
}
)");
}

TEST_CASE("printer: gsc only syntax", "[printer][gsc]")
{
    SECTION("far call and animation")
    {
        auto const out = print_src<gsc_ctx>("main(){ self.x = self maps\\mp\\_utility::func(1); m = %idle; }");

        REQUIRE(out == R"(
main()
{
    self.x = self maps\mp\_utility::func( 1 );
    m = %idle;
}
)");
    }
}

TEST_CASE("printer: arc only syntax", "[printer][arc][feature]")
{
    SECTION("t7 headers, modifiers and operators")
    {
        auto const out = print_src<arc::t7::context>("#using scripts\\shared\\util_shared;\n#namespace mytest;\n#precache(\"model\", \"foo\");\nfunction private init(a, b) { x = a === b; y = a !== b; self.z = level thread [[ p ]]->func(1); n = a[#\"hash\"]; }");

        REQUIRE(out == R"(#using scripts\shared\util_shared;

#namespace mytest;

#precache( "model", "foo" );

function private init( a, b )
{
    x = a === b;
    y = a !== b;
    self.z = level thread [[ p ]]->func( 1 );
    n = a[#"hash"];
}
)");
    }
}

TEMPLATE_TEST_CASE("printer: assembly", "[printer]", BOTH)
{
    using assembly = typename fam<TestType>::assembly;
    using function = typename fam<TestType>::function;
    using instruction = typename fam<TestType>::instruction;
    using opcode = typename fam<TestType>::opcode;

    auto index = usize{ 0 };

    auto make_inst = [&index](opcode op, std::vector<std::string> data)
    {
        auto inst = instruction::make();
        inst->index = index++;
        inst->opcode = op;
        inst->data = std::move(data);
        return inst;
    };

    auto func = function::make();
    func->name = "main";
    func->labels[0] = "loc_1";
    func->instructions.push_back(make_inst(opcode::OP_GetByte, { "1" }));
    func->instructions.push_back(make_inst(opcode::OP_GetString, { "a" }));
    func->instructions.push_back(make_inst(opcode::OP_End, {}));

    auto data = assembly::make();
    data->functions.push_back(std::move(func));

    REQUIRE(print_asm<TestType>(*data) == R"(
sub:main
	loc_1
		OP_GetByte 1
		OP_GetString "a"
		OP_End
end:main
)");
}

} // namespace xsk::test
