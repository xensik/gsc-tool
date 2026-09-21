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

} // namespace xsk::test
