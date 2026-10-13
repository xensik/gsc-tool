// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "common.hpp"
#include <catch_amalgamated.hpp>

namespace xsk::test
{

using xb_ctx = gsc::iw5_xb::context;
using ps_ctx = gsc::s1_ps::context;

#define BIGENDIAN xb_ctx, ps_ctx

// Big endian engines align the vector payload to 4 bytes and stock bytecode repeats
// the opcode in the last padding byte. Three OP_GetZero push the vector off the
// boundary, so the assembler has to pad: '<op> 00 00 <op>' and then the floats.

TEMPLATE_TEST_CASE("assembler: big endian vector alignment", "[assembler][gsc]", BIGENDIAN)
{
    using assembly = typename fam<TestType>::assembly;
    using function = typename fam<TestType>::function;
    using instruction = typename fam<TestType>::instruction;
    using opcode = typename fam<TestType>::opcode;

    auto make_inst = [](opcode op, std::vector<std::string> data)
    {
        auto inst = instruction::make();
        inst->opcode = op;
        inst->data = std::move(data);
        return inst;
    };

    auto func = function::make();
    func->id = 1;
    func->instructions.push_back(make_inst(opcode::OP_GetZero, {}));
    func->instructions.push_back(make_inst(opcode::OP_GetZero, {}));
    func->instructions.push_back(make_inst(opcode::OP_GetZero, {}));
    func->instructions.push_back(make_inst(opcode::OP_GetVector, { "0", "0", "0" }));

    auto data = assembly::make();
    data->functions.push_back(std::move(func));

    auto* c = ctx<TestType>();
    auto const [script, stack, devmap] = c->assembler().assemble(*data);
    auto const id = c->opcode_id(opcode::OP_GetVector);
    auto const payload = script.size - 12;

    REQUIRE(payload % 4 == 0);
    REQUIRE(script.data[payload - 4] == id);
    REQUIRE(script.data[payload - 3] == 0);
    REQUIRE(script.data[payload - 2] == 0);
    REQUIRE(script.data[payload - 1] == id);
    REQUIRE(std::all_of(script.data + payload, script.data + script.size, [](u8 byte) { return byte == 0; }));
}

TEST_CASE("assembler: t7 wait and waitrealtime opcodes", "[assembler][arc]")
{
    // #282: the compiler reads the same table, so a round trip can't catch a swap.
    // These ids are pinned against stock bytecode decompiled next to its source.
    auto const* c = ctx<arc::t7::context>();

    REQUIRE(c->opcode_enum(u16{ 0x00D5 }) == arc::opcode::OP_Wait);
    REQUIRE(c->opcode_enum(u16{ 0x0104 }) == arc::opcode::OP_RealWait);
}

// Text assembly is the disassembler's listing read back in. The listing is not the
// in-memory form: floats and far call paths hold characters a bare word has to keep,
// literals come quoted, and a switch table prints without its case types and can carry
// its default anywhere. The assembler writes offsets straight from the parsed indexes,
// so a listing that reassembles into the same listing proves all of it.

TEST_CASE("assembler: gsc text assembly round trip", "[assembler][gsc]")
{
    auto* c = ctx<gsc::iw5_pc::context>();

    auto assemble = [c](std::string const& text)
    {
        auto const data = c->parser().parse_assembly(reinterpret_cast<u8 const*>(text.data()), text.size());
        auto const [script, stack, devmap] = c->assembler().assemble(*data);

        return std::pair{ std::vector<u8>{ script.data, script.data + script.size }, std::vector<u8>{ stack.data, stack.data + stack.size } };
    };

    auto list = [c](std::pair<std::vector<u8>, std::vector<u8>> const& bin)
    {
        return print_asm<gsc::iw5_pc::context>(*c->disassembler().disassemble(bin.first, bin.second));
    };

    // labels are named after their address, so these are renamed by the first pass
    auto const typed = std::string{ R"(
sub:main
		OP_GetFloat 0.5
		OP_GetVector 0 0.25 -1024
		OP_GetString "say \"hi\" twice"
		OP_ScriptFarFunctionCall2 maps/mp/_utility func
		OP_ScriptLocalFunctionCall2 helper
		OP_GetByte 3
		OP_switch loc_c
	loc_a
		OP_jump loc_d
	loc_b
		OP_jump loc_d
	loc_c
		OP_endswitch 3
			case "mi 28" loc_a
			default loc_b
			case 7 loc_a
	loc_d
		OP_End
end:main

sub:helper
		OP_End
end:helper
)" };

    auto const first = assemble(typed);
    auto const listing = list(first);

    REQUIRE(listing.find("OP_GetFloat 0.5\n") != std::string::npos);
    REQUIRE(listing.find("OP_GetVector 0 0.25 -1024\n") != std::string::npos);
    REQUIRE(listing.find("OP_GetString \"say \\\"hi\\\" twice\"\n") != std::string::npos);
    REQUIRE(listing.find("OP_ScriptFarFunctionCall2 maps/mp/_utility func\n") != std::string::npos);
    REQUIRE(listing.find("OP_ScriptLocalFunctionCall2 helper\n") != std::string::npos);
    REQUIRE(listing.find("case \"mi 28\" loc_") != std::string::npos);
    REQUIRE(listing.find("case 7 loc_") != std::string::npos);
    REQUIRE(listing.find("default loc_") < listing.find("case 7 loc_"));

    auto const second = assemble(listing);

    REQUIRE(second == first);
    REQUIRE(list(second) == listing);
}

// T7 writes 16 bit opcodes, hashed names, 8 byte import operands and a second string
// table for devblock strings. The assembler has to read its own disassembly back, so
// the script goes through assemble -> disassemble -> assemble and must not change. The
// same holds through text: printed assembly parses back into the same bytes, including
// the operands that need quoting, an empty namespace and a hashed name with a space.

TEST_CASE("assembler: t7 reassembles its own disassembly", "[assembler][arc]")
{
    auto func = arc::function::make();
    func->name = "main";
    func->space = "delete";
    func->params = 1;

    auto add = [&func](arc::opcode op, std::vector<std::string> data = {})
    {
        auto inst = arc::instruction::make();
        inst->index = func->instructions.size();
        inst->opcode = op;
        inst->data = std::move(data);
        func->instructions.push_back(std::move(inst));
    };

    auto label = [&func](std::string const& name)
    {
        func->labels.insert({ func->instructions.size(), name });
    };

    add(arc::opcode::OP_SafeCreateLocalVariables, { "str_filename", "0" });
    add(arc::opcode::OP_DevblockBegin, { "loc_1" });
    add(arc::opcode::OP_PreScriptCall);
    add(arc::opcode::OP_GetString, { "__devstr__" });
    add(arc::opcode::OP_ScriptFunctionCall, { "delete", "println", "1", "50" });
    add(arc::opcode::OP_DecTop);
    add(arc::opcode::OP_PreScriptCall);
    add(arc::opcode::OP_GetHash, { "abort forfeit" });
    add(arc::opcode::OP_ScriptFunctionCall, { "", "assert", "1", "50" });
    add(arc::opcode::OP_DecTop);
    label("loc_1");
    add(arc::opcode::OP_EvalLocalVariableCached, { "0" });
    add(arc::opcode::OP_Switch, { "loc_3" });
    label("loc_2");
    add(arc::opcode::OP_GetString, { "table_end" });
    add(arc::opcode::OP_SelfEvalFieldVariableRef, { "classname" });
    add(arc::opcode::OP_SetVariableField);
    label("loc_3");
    add(arc::opcode::OP_EndSwitch, { "3", "case", "1", "4294967295", "loc_2", "case", "2", "table_end", "loc_2", "default", "loc_2" });
    add(arc::opcode::OP_End);

    auto data = arc::assembly::make();
    data->includes.emplace_back("scripts/shared/util_shared");
    data->functions.push_back(std::move(func));

    auto* c = ctx<arc::t7::context>();
    auto const name = std::string{ "scripts/codescripts/delete.gsc" };

    // the buffer points into the assembler, copy it before assembling again
    auto const out = c->assembler().assemble(*data, name).first;
    auto const first = std::vector<u8>{ out.data, out.data + out.size };

    auto const back = c->disassembler().disassemble(first);
    auto const& main = *back->functions.at(0);

    REQUIRE(back->includes == data->includes);
    REQUIRE(main.name == "main");
    REQUIRE(main.space == "delete");
    REQUIRE(main.params == 1);
    REQUIRE(main.index % 8 == 0);
    REQUIRE(main.instructions.size() == 17);
    REQUIRE(main.instructions[0]->data == std::vector<std::string>{ "str_filename", "0" });
    REQUIRE(main.instructions[3]->data == std::vector<std::string>{ "__devstr__" });
    REQUIRE(main.instructions[4]->data == std::vector<std::string>{ "delete", "println", "1", "50" });
    REQUIRE(main.instructions[4]->index % 2 == 0);
    REQUIRE(main.instructions[7]->data == std::vector<std::string>{ "abort forfeit" });
    REQUIRE(main.instructions[8]->data == std::vector<std::string>{ "", "assert", "1", "50" });
    REQUIRE(main.instructions[12]->data == std::vector<std::string>{ "table_end" });
    REQUIRE(main.instructions[13]->data == std::vector<std::string>{ "classname" });
    REQUIRE(main.instructions[15]->data.at(3) == "4294967295");
    REQUIRE(main.instructions[15]->data.at(7) == "table_end");
    REQUIRE(main.instructions[15]->data.at(9) == "default");

    auto const text = c->printer().print(*back);
    auto const parsed = c->parser().parse_assembly(text);

    REQUIRE(parsed->name == name);
    REQUIRE(parsed->includes == data->includes);

    auto const typed = c->assembler().assemble(*parsed, parsed->name).first;

    REQUIRE(typed.size == first.size());
    REQUIRE(std::equal(first.begin(), first.end(), typed.data));

    auto const again = c->assembler().assemble(*back, name).first;

    REQUIRE(again.size == first.size());
    REQUIRE(std::equal(first.begin(), first.end(), again.data));
}

// T7 shipped two bytecode versions. 0x1B has the instruction set of 0x1C behind one byte
// opcodes: nothing pads an instruction to an even address, operands still align to their
// own size, and a jump offset is the plain distance. The same script has to come back
// out of both, and a script that is empty but for its prologue pins the encoding.

TEST_CASE("assembler: t7 0x1B one byte opcodes", "[assembler][arc][feature]")
{
    // ponytail: leaked like every test context, see ctx() in common.hpp
    static auto* const old = [] {
        auto* c = new arc::t7::context(arc::instance::server, arc::t7::version::v1b);
        c->init(arc::build::prod, nullptr);
        return c;
    }();

    auto* cur = ctx<arc::t7::context>();
    auto const name = std::string{ "scripts/shared/demo.gsc" };

    REQUIRE(static_cast<bool>(cur->features() & arc::feature::code16));
    REQUIRE_FALSE(static_cast<bool>(old->features() & arc::feature::code16));
    REQUIRE(old->opcode_size(arc::opcode::OP_End) == 1);
    REQUIRE(old->opcode_size(arc::opcode::OP_GetString) == 5);
    REQUIRE(cur->opcode_size(arc::opcode::OP_GetString) == 6);

    auto const build = [&](arc::context* c, std::string_view src) {
        auto data = std::vector<u8>{ src.begin(), src.end() };
        auto const out = c->compiler().compile(name, data);
        auto const bin = c->assembler().assemble(*out, name).first;
        return std::vector<u8>{ bin.data, bin.data + bin.size };
    };

    auto const listing = [](arc::context* c, std::vector<u8> const& bin) {
        auto out = std::vector<std::string>{};

        for (auto const& func : c->disassembler().disassemble(bin)->functions)
        {
            for (auto const& inst : func->instructions)
            {
                // a label is named after its address, which is what differs between the two
                auto line = c->opcode_name(inst->opcode);

                for (auto const& entry : inst->data)
                    line += entry.starts_with("loc_") ? " loc" : " " + entry;

                out.push_back(std::move(line));
            }
        }

        return out;
    };

    SECTION("prologue")
    {
        auto const bin = build(old, "#namespace demo;\n\nfunction main()\n{\n}\n");
        auto const back = old->disassembler().disassemble(bin);
        auto const at = back->functions.at(0)->index;

        REQUIRE(bin[7] == 0x1B);
        REQUIRE(bin[at] == 0x0D);
        REQUIRE(bin[at + 1] == 0x10);
        REQUIRE(back->functions.at(0)->size == 2);
    }

    SECTION("same script out of both versions")
    {
        auto const src = std::string_view{ R"(
#namespace demo;

function main( a, b )
{
    level.count = 0;

    foreach ( item in a )
    {
        if ( !isdefined( item ) )
            continue;

        level.count += item.size >> 1;
    }

    switch ( b )
    {
        case "one":
            self thread watch( #"done", 1.5 );
            break;
        case 2:
            wait 0.05;
            break;
        default:
            return ( 0, 0, 1 );
    }

    return level.count;
}

function watch( event, time )
{
    self endon( #"death" );
    self waittill( event, who );
    return who;
}
)" };

        auto const first = build(old, src);
        auto const wide = build(cur, src);

        REQUIRE(first[7] == 0x1B);
        REQUIRE(wide[7] == 0x1C);
        REQUIRE(listing(old, first) == listing(cur, wide));

        auto const back = old->disassembler().disassemble(first);
        auto const again = old->assembler().assemble(*back, name).first;

        REQUIRE(again.size == first.size());
        REQUIRE(std::equal(first.begin(), first.end(), again.data));

        // one version's context does not read the other's file
        REQUIRE_THROWS_AS(cur->disassembler().disassemble(first), arc::disasm_error);
        REQUIRE_THROWS_AS(old->disassembler().disassemble(wide), arc::disasm_error);
    }
}

} // namespace xsk::test
