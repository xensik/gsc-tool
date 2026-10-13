// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "common.hpp"
#include <catch_amalgamated.hpp>

namespace xsk::test
{

namespace
{

// The T7 rules below were read off shipped bytecode next to its original source, one
// pattern at a time. Each case pins one of them on the compiler's own output, where
// names are still text: hashing only happens in the assembler.

using lines = std::vector<std::string>;

// one function as 'OP_Name operand operand', labels left as the compiler numbers them
auto listing(arc::function const& func) -> lines
{
    auto out = lines{};

    for (auto const& inst : func.instructions)
    {
        auto line = ctx<arc::t7::context>()->opcode_name(inst->opcode);

        for (auto const& entry : inst->data)
            line += " " + entry;

        out.push_back(std::move(line));
    }

    return out;
}

auto compile(std::string_view src, arc::t7::context* c = ctx<arc::t7::context>()) -> arc::assembly::ptr
{
    auto data = std::vector<u8>{ src.begin(), src.end() };
    return c->compiler().compile("scripts/shared/demo.gsc", data);
}

auto find(arc::assembly const& data, std::string_view space, std::string_view name) -> arc::function const&
{
    for (auto const& func : data.functions)
    {
        if (func->space == space && func->name == name)
            return *func;
    }

    FAIL("no function " << space << "::" << name);
    return *data.functions.front();
}

} // anonymous namespace

// Stock bytecode of every IW engine has no operator left between two constants and no
// vector built from three of them. Original source keeps its numbers in named constants,
// so folding has to see through those and through parentheses.

TEST_CASE("compiler: gsc folds constant arithmetic", "[compiler][gsc]")
{
    auto* c = ctx<gsc::iw5_pc::context>();
    auto const src = std::string_view{ R"(
sqr8 = 8 * 8;
ratio = 60 / 130;

main( x )
{
    a = 1000 * 1000;
    b = sqr8;
    c = ratio;
    d = 360 / 1;
    e = ( 30, 15, 1000 * 12 );
    f = ( sqr8, 0, -0 );
    g = ( 2 + 3 ) * -4;
    h = x * 2;
}
)" };

    auto data = std::vector<u8>{ src.begin(), src.end() };
    auto const out = c->compiler().compile("maps/demo", data);
    auto code = lines{};

    for (auto const& inst : out->functions.at(0)->instructions)
    {
        auto line = c->opcode_name(inst->opcode);

        for (auto const& entry : inst->data)
            line += " " + entry;

        code.push_back(std::move(line));
    }

    auto const has = [&](std::string_view line) { return std::find(code.begin(), code.end(), line) != code.end(); };

    REQUIRE(has("OP_GetInteger 1000000"));
    REQUIRE(has("OP_GetByte 64"));
    // dividing two integers gives a float, also when it divides evenly
    REQUIRE(has("OP_GetFloat 0.46153846"));
    REQUIRE(has("OP_GetFloat 360.0"));
    REQUIRE(has("OP_GetVector 30 15 12000"));
    REQUIRE(has("OP_GetVector 64 0 0"));
    REQUIRE(has("OP_GetNegByte 20"));
    // the one operator that has a variable on a side is the one that is left
    REQUIRE(std::count(code.begin(), code.end(), "OP_multiply") == 1);
    REQUIRE(std::count(code.begin(), code.end(), "OP_divide") == 0);
    REQUIRE(std::count(code.begin(), code.end(), "OP_vector") == 0);
}

// T6 has an opcode for each of these where later engines make an ordinary call, so each
// one takes exactly one expression and leaves its own opcode behind it.

TEST_CASE("compiler: t6 builtin opcodes", "[compiler][arc]")
{
    auto* c = ctx<arc::t6::pc::context>();
    auto const src = std::string_view{ R"(
main( x )
{
    a = getdvar( "d" );
    b = getdvarint( "d" );
    c = getdvarfloat( #"d" );
    d = getdvarvector( "d" );
    e = getdvarcolorred( "d" );
    f = getdvarcolorgreen( "d" );
    g = getdvarcolorblue( "d" );
    h = getdvarcoloralpha( "d" );
    i = abs( x );
    j = anglestoup( x );
    k = anglestoright( x );
    l = anglestoforward( x );
    m = angleclamp180( x );
    n = vectortoangles( x );
}
)" };

    auto data = std::vector<u8>{ src.begin(), src.end() };
    auto const out = c->compiler().compile("maps/demo.gsc", data);
    auto code = lines{};

    for (auto const& inst : out->functions.at(0)->instructions)
        code.push_back(c->opcode_name(inst->opcode));

    for (auto const* name : { "OP_GetDvar", "OP_GetDvarInt", "OP_GetDvarFloat", "OP_GetDvarVector", "OP_GetDvarColorRed", "OP_GetDvarColorGreen", "OP_GetDvarColorBlue", "OP_GetDvarColorAlpha", "OP_Abs", "OP_AnglesToUp", "OP_AnglesToRight", "OP_AnglesToForward", "OP_AngleClamp180", "OP_VectorToAngles" })
    {
        CAPTURE(name);
        REQUIRE(std::count(code.begin(), code.end(), name) == 1);
    }

    auto const two = std::string_view{ "main() { a = getdvarint( \"d\", 1 ); }" };
    data.assign(two.begin(), two.end());
    REQUIRE_THROWS_AS(c->compiler().compile("maps/demo.gsc", data), arc::comp_error);
}

TEST_CASE("compiler: t7 namespaces and imports", "[compiler][arc]")
{
    SECTION("a script without '#namespace' is named after its file")
    {
        auto const out = compile("function main() { }");

        REQUIRE(out->functions.at(0)->space == "demo");
    }

    SECTION("an unqualified call imports under the script's namespace with the unscoped flag")
    {
        auto const out = compile("#namespace foo;\nfunction main() { bar(); other::baz( 1 ); self thread bar(); x = &bar; }");

        REQUIRE(listing(find(*out, "foo", "main")) == lines{
            "OP_SafeCreateLocalVariables x 0",
            "OP_PreScriptCall",
            "OP_ScriptFunctionCall foo bar 0 34",
            "OP_DecTop",
            "OP_PreScriptCall",
            "OP_GetByte 1",
            "OP_ScriptFunctionCall other baz 1 2",
            "OP_DecTop",
            "OP_PreScriptCall",
            "OP_GetSelf",
            "OP_ScriptMethodThreadCall foo bar 0 37",
            "OP_DecTop",
            "OP_GetFunction foo bar 0 33",
            "OP_EvalLocalVariableRefCached 0",
            "OP_SetVariableField",
            "OP_End",
        });
    }

    SECTION("assert gets a devblock of its own and no namespace")
    {
        auto const out = compile("#namespace foo;\nfunction main() { assert( 1 ); }");

        REQUIRE(listing(find(*out, "foo", "main")) == lines{
            "OP_CheckClearParams",
            "OP_DevblockBegin loc_1",
            "OP_PreScriptCall",
            "OP_GetByte 1",
            "OP_ScriptFunctionCall  assert 1 50",
            "OP_DecTop",
            "OP_End",
        });
    }

    SECTION("parameter kinds and export flags")
    {
        auto const out = compile("#namespace foo;\nfunction private main( a, &b, ... ) { }\nfunction autoexec init() { }");
        auto const& main = find(*out, "foo", "main");

        REQUIRE(main.params == 3);
        REQUIRE(main.flags == 0x24);
        REQUIRE(listing(main).at(0) == "OP_SafeCreateLocalVariables a 0 b 1 vararg 2");
        REQUIRE(find(*out, "foo", "init").flags == 0x02);
    }
}

TEST_CASE("compiler: t7 expressions", "[compiler][arc]")
{
    SECTION("self and level fields have opcodes of their own")
    {
        auto const out = compile("function main() { self.a = level.b; }");

        REQUIRE(listing(*out->functions.at(0)) == lines{
            "OP_CheckClearParams",
            "OP_LevelEvalFieldVariable b",
            "OP_SelfEvalFieldVariableRef a",
            "OP_SetVariableField",
            "OP_End",
        });
    }

    SECTION("an event name is a name hash, a hash literal is djb2")
    {
        auto const out = compile("function main() { self endon( \"death\" ); x = #\"on_player_spawned\"; }");
        auto const code = listing(*out->functions.at(0));

        REQUIRE(code.at(1) == "OP_GetHash death");
        REQUIRE(code.at(4) == "OP_GetHash _id_BC12B61F");
    }

    SECTION("arithmetic on literals is folded, parenthesised literals are not")
    {
        auto const out = compile("function main( x ) { a = 15 * 1000; b = ( 240 ) * ( 240 ); c = 4000 / 1000; d = 1 << 13; e = 40000; f = -x; }");
        auto const code = listing(*out->functions.at(0));

        REQUIRE(code.at(1) == "OP_GetUnsignedShort 15000");
        REQUIRE(code.at(4) == "OP_GetByte 240");
        REQUIRE(code.at(5) == "OP_GetByte 240");
        REQUIRE(code.at(6) == "OP_Multiply");
        REQUIRE(code.at(9) == "OP_GetFloat 4.0");
        REQUIRE(code.at(12) == "OP_GetUnsignedShort 8192");
        REQUIRE(code.at(15) == "OP_GetInteger 40000");
        REQUIRE(code.at(19) == "OP_GetNegByte 1");
        REQUIRE(code.at(20) == "OP_Multiply");
    }

    SECTION("a constant vector is a unit vector, scaled when it has to be")
    {
        auto const out = compile("function main() { a = ( 0, 0, 1 ); b = ( 0, 0, 72 / 2 ); c = ( 0, 1, 1 ); d = ( 1, 2, 3 ); }");
        auto const code = listing(*out->functions.at(0));

        REQUIRE(code.at(1) == "OP_VectorConstant 2");
        REQUIRE(code.at(4) == "OP_GetFloat 36.0");
        REQUIRE(code.at(5) == "OP_VectorConstant 2");
        REQUIRE(code.at(6) == "OP_VectorScale");
        // ( 0, y, z ) is never folded by the stock compiler
        REQUIRE(code.at(12) == "OP_Vector");
        REQUIRE(code.at(18) == "OP_Vector");
    }
}

TEST_CASE("compiler: t7 statements", "[compiler][arc]")
{
    SECTION("foreach names its hidden locals after the line and reads the next key early")
    {
        auto const out = compile("function main( arr )\n{\n    foreach ( v in arr )\n    {\n    }\n}");

        REQUIRE(listing(*out->functions.at(0)) == lines{
            "OP_SafeCreateLocalVariables arr 0 v 0 __k3 0 __a3 0 __new___k3 0",
            "OP_EvalLocalVariableCached 4",
            "OP_EvalLocalVariableRefCached 1",
            "OP_SetVariableField",
            "OP_EvalLocalVariableCached 1",
            "OP_FirstArrayKey",
            "OP_EvalLocalVariableRefCached 2",
            "OP_SetVariableField",
            "OP_EvalLocalVariableCached 2",
            "OP_IsDefined",
            "OP_JumpOnFalse loc_1",
            "OP_EvalLocalVariableCached 2",
            "OP_EvalLocalVariableCached 1",
            "OP_EvalArray",
            "OP_EvalLocalVariableRefCached 3",
            "OP_SetVariableField",
            "OP_EvalLocalVariableCached 2",
            "OP_EvalLocalVariableCached 1",
            "OP_NextArrayKey",
            "OP_EvalLocalVariableRefCached 0",
            "OP_SetVariableField",
            "OP_EvalLocalVariableCached 0",
            "OP_EvalLocalVariableRefCached 2",
            "OP_SetVariableField",
            "OP_Jump loc_3",
            "OP_End",
        });
    }

    SECTION("a keyed foreach orders its frame 'key, value, next, array'")
    {
        auto const out = compile("function main( arr )\n{\n    foreach ( k, v in arr )\n    {\n    }\n}");

        REQUIRE(listing(*out->functions.at(0)).at(0) == "OP_SafeCreateLocalVariables arr 0 k 0 v 0 __new_k 0 __a3 0");
    }

    SECTION("a constant takes a frame slot and is inlined")
    {
        auto const out = compile("function main() { const limit = 6; return limit; }");

        REQUIRE(listing(*out->functions.at(0)) == lines{
            "OP_SafeCreateLocalVariables limit 0",
            "OP_GetByte 6",
            "OP_Return",
        });
    }

    SECTION("a function declared in a dev block runs as one")
    {
        auto const out = compile("/#\nfunction main( a = 1 ) { }\n#/", ctx_dev<arc::t7::context>());
        auto const code = listing(*out->functions.at(0));

        REQUIRE(code.at(0) == "OP_SafeCreateLocalVariables a 0");
        REQUIRE(code.at(1).starts_with("OP_DevblockBegin "));
        REQUIRE(code.back() == "OP_End");
    }
}

TEST_CASE("compiler: t7 classes", "[compiler][arc]")
{
    auto const out = compile(R"(
#namespace demo;

class cbase
{
    var count;

    constructor()
    {
        count = 0;
    }

    function bump()
    {
        count++;
    }
}

class cchild : cbase
{
    function twice()
    {
        bump();
        bump();
    }
}

function make()
{
    o = new cchild();
    [[ o ]]->twice();
}
)");

    SECTION("methods are exported under the class name, a member is a field of self")
    {
        REQUIRE(listing(find(*out, "cbase", "__constructor")) == lines{
            "OP_CheckClearParams",
            "OP_GetZero",
            "OP_SelfEvalFieldVariableRef count",
            "OP_SetVariableField",
            "OP_End",
        });

        REQUIRE(listing(find(*out, "cbase", "bump")).at(1) == "OP_SelfEvalFieldVariableRef count");
    }

    SECTION("the missing constructor and destructor are generated and call the base")
    {
        REQUIRE(listing(find(*out, "cbase", "__destructor")) == lines{ "OP_CheckClearParams", "OP_End" });

        REQUIRE(listing(find(*out, "cchild", "__constructor")) == lines{
            "OP_CheckClearParams",
            "OP_PreScriptCall",
            "OP_ScriptFunctionCall cbase __constructor 0 2",
            "OP_DecTop",
            "OP_End",
        });
    }

    SECTION("an inherited method is called through the class that declares it")
    {
        REQUIRE(listing(find(*out, "cchild", "twice")).at(2) == "OP_ScriptFunctionCall cbase bump 0 2");
    }

    SECTION("each class gets a private autoexec function that fills its vtable, base first")
    {
        auto const& init = find(*out, "demo", "cchild");
        auto bound = lines{};

        for (auto const& line : listing(init))
        {
            if (line.starts_with("OP_GetFunction "))
                bound.push_back(line);
        }

        REQUIRE(init.flags == 0x06);
        REQUIRE(bound == lines{
            "OP_GetFunction cbase __destructor 0 1",
            "OP_GetFunction cbase bump 0 1",
            "OP_GetFunction cbase __constructor 0 1",
            "OP_GetFunction cchild __destructor 0 1",
            "OP_GetFunction cchild __constructor 0 1",
            "OP_GetFunction cchild twice 0 1",
        });
    }

    SECTION("new builds the object and runs its constructor, '->' calls through the vtable")
    {
        REQUIRE(listing(find(*out, "demo", "make")) == lines{
            "OP_SafeCreateLocalVariables o 0",
            "OP_New cchild",
            "OP_ScriptFunctionCallClass __constructor 0",
            "OP_DecTop",
            "OP_EvalLocalVariableRefCached 0",
            "OP_SetVariableField",
            "OP_PreScriptCall",
            "OP_EvalLocalVariableCached 0",
            "OP_ScriptFunctionCallClass twice 0",
            "OP_DecTop",
            "OP_End",
        });
    }

    SECTION("the whole script assembles and disassembles")
    {
        auto* c = ctx<arc::t7::context>();
        auto const bin = c->assembler().assemble(*out, "scripts/shared/demo.gsc").first;
        auto const back = c->disassembler().disassemble(std::vector<u8>{ bin.data, bin.data + bin.size });

        REQUIRE(back->functions.size() == out->functions.size());
        REQUIRE(back->name == "scripts/shared/demo.gsc");
    }
}

// What the decompiler rebuilds has to compile back into the bytecode it came from. Each
// construct here is one the bytecode does not spell out: classes and their members, a
// constant's frame slot, a function declared in a dev block, an assert in a block of its
// own, and literals the compiler would fold if their parentheses were lost.

TEST_CASE("decompiler: t7 source compiles back to the same bytecode", "[decompiler][compiler][arc]")
{
    auto* c = ctx_dev<arc::t7::context>();
    auto const name = std::string{ "scripts/shared/demo.gsc" };

    auto const build = [&](std::string_view src) {
        auto const out = compile(src, c);
        auto const bin = c->assembler().assemble(*out, name).first;
        return std::vector<u8>{ bin.data, bin.data + bin.size };
    };

    auto const first = build(R"(
#namespace demo;

class cobjective
{
    var count;
    var owner;

    constructor()
    {
        count = 0;
    }

    function bump( owner )
    {
        count++;
        self.owner = owner;
        count = undefined;
    }
}

class cbreadcrumbobjective : cobjective
{
    function twice()
    {
        bump( 1 );
    }
}

function make( a, b )
{
    const limit = 6;
    o = new cbreadcrumbobjective();
    [[ o ]]->twice();
    c = "a" + ( isdefined( b ) ? b : "" );
    d = ( 240 ) * ( 240 );
    e = ( 0, 0, ( 44 ) );
    f = ~( 256 );
    /# assert( a ); #/

    for ( i = 0; 1; i++ )
    {
        if ( i > limit )
            break;
    }

    return c;
}

/#
function debug( a )
{
    /#
    if ( a )
        make( a, a );
    #/
}
#/
)");

    auto const source = c->printer().print(*c->decompiler().decompile(*c->disassembler().disassemble(first)));
    auto const text = std::string_view{ reinterpret_cast<char const*>(source.data()), source.size() };

    INFO(text);

    SECTION("the class comes back as a class")
    {
        REQUIRE(text.find("class cobjective\n") != std::string_view::npos);
        REQUIRE(text.find("class cbreadcrumbobjective : cobjective\n") != std::string_view::npos);
        REQUIRE(text.find("    var count;\n") != std::string_view::npos);
        REQUIRE(text.find("    constructor()\n") != std::string_view::npos);
        REQUIRE(text.find("        count++;\n") != std::string_view::npos);
        // the parameter hides the member of that name, so the field keeps its 'self'
        REQUIRE(text.find("        self.owner = owner;\n") != std::string_view::npos);
        // nothing of what the compiler generates is printed
        REQUIRE(text.find("__vtable") == std::string_view::npos);
        REQUIRE(text.find("destructor") == std::string_view::npos);
        REQUIRE(text.find("cobjective::__constructor") == std::string_view::npos);
    }

    SECTION("the constant gets its declaration back")
    {
        REQUIRE(text.find("    const limit = undefined;\n") != std::string_view::npos);
    }

    SECTION("and it all compiles to the same bytes")
    {
        REQUIRE(build(text) == first);
    }
}

// Treyarch's compiler loses a break in two ways, and shipped scripts carry both (#259).
// Outside a loop or switch a break is a jump to the function end. Inside one, it lands on
// the end of a switch nested further down instead of the end of its own. Our compiler does
// not make the second mistake, so the shapes are spelled out as assembly.

TEST_CASE("decompiler: t7 breaks the original compiler misplaced", "[decompiler][arc]")
{
    auto* c = ctx<arc::t7::context>();
    auto const name = std::string{ "scripts/shared/demo.gsc" };

    auto const decompile = [&](std::string_view text) {
        auto const data = std::vector<u8>{ text.begin(), text.end() };
        auto const out = c->parser().parse_assembly(data);
        auto const bin = c->assembler().assemble(*out, name).first;
        auto const src = c->printer().print(*c->decompiler().decompile(*c->disassembler().disassemble(bin.data, bin.size)));
        return std::string{ reinterpret_cast<char const*>(src.data()), src.size() };
    };

    SECTION("a stray break under nested ifs is not an else")
    {
        auto const text = decompile(R"(
sub:demo think 2 0
		OP_SafeCreateLocalVariables a 0 b 0
		OP_EvalLocalVariableCached 1
		OP_JumpOnFalse loc_1
		OP_EvalLocalVariableCached 0
		OP_JumpOnFalse loc_1
		OP_GetByte 1
		OP_SelfEvalFieldVariableRef done
		OP_SetVariableField
		OP_Jump loc_2
	loc_1
		OP_GetZero
		OP_SelfEvalFieldVariableRef done
		OP_SetVariableField
	loc_2
		OP_End
end:think
)");

        INFO(text);
        REQUIRE(text.find(R"(
    if ( a )
    {
        if ( b )
        {
            self.done = 1;
            break;
        }
    }

    self.done = 0;
}
)") != std::string::npos);
    }

    SECTION("a case that breaks to the end of a switch nested in a later case")
    {
        // 'case 1' jumps to loc_3, where the inner switch ends, and not to loc_6
        auto const text = decompile(R"(
sub:demo think 2 0
		OP_SafeCreateLocalVariables a 0 b 0
		OP_EvalLocalVariableCached 1
		OP_Switch loc_5
	loc_0
		OP_Jump loc_3
	loc_1
		OP_EvalLocalVariableCached 0
		OP_IsDefined
		OP_JumpOnFalse loc_4
		OP_EvalLocalVariableCached 0
		OP_Switch loc_22
	loc_21
		OP_Jump loc_3
	loc_22
		OP_EndSwitch 1
			case 3 loc_21
	loc_3
		OP_Jump loc_41
	loc_4
		OP_GetZero
		OP_SelfEvalFieldVariableRef done
		OP_SetVariableField
	loc_41
		OP_Jump loc_6
	loc_5
		OP_EndSwitch 2
			case 1 loc_0
			case 2 loc_1
	loc_6
		OP_End
end:think
)");

        INFO(text);
        REQUIRE(text.find(R"(
    switch ( a )
    {
        case 1:
            break;
        case 2:
            if ( isdefined( b ) )
            {
                switch ( b )
                {
                    case 3:
                        break;
                }
            }
            else
                self.done = 0;

            break;
    }
}
)") != std::string::npos);
    }

    SECTION("a loop break that lands on the end of a switch in the else beside it")
    {
        // the first jump is the break: it goes to loc_3 like the one that skips the else
        auto const text = decompile(R"(
sub:demo think 3 0
		OP_SafeCreateLocalVariables a 0 b 0 c 0
	loc_0
		OP_GetByte 1
		OP_JumpOnFalse loc_6
		OP_EvalLocalVariableCached 2
		OP_JumpOnFalse loc_4
		OP_EvalLocalVariableCached 1
		OP_JumpOnFalse loc_1
		OP_Jump loc_3
		OP_Jump loc_3
	loc_1
		OP_EvalLocalVariableCached 0
		OP_Switch loc_22
	loc_21
		OP_Jump loc_3
	loc_22
		OP_EndSwitch 1
			case 3 loc_21
	loc_3
		OP_Jump loc_5
	loc_4
		OP_GetZero
		OP_SelfEvalFieldVariableRef done
		OP_SetVariableField
	loc_5
		OP_Jump loc_0
	loc_6
		OP_End
end:think
)");

        INFO(text);
        REQUIRE(text.find(R"(
    while ( true )
    {
        if ( a )
        {
            if ( b )
                break;
            else
            {
                switch ( c )
                {
                    case 3:
                        break;
                }
            }
        }
        else
            self.done = 0;
    }
}
)") != std::string::npos);
    }
}

} // namespace xsk::test
