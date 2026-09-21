// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/engine/iw5_xb.hpp"
#include "xsk/gsc/engine/s1_ps.hpp"
#include <catch_amalgamated.hpp>

namespace xsk::test
{

using namespace xsk::gsc;

// Big endian engines align the vector payload to 4 bytes, and stock bytecode
// repeats the opcode in the last padding byte. Three OP_GetZero push the vector
// off the boundary so the assembler has to pad: '<op> 00 00 <op>' then the floats.
template <typename Ctx>
auto assemble_padded_vector() -> void
{
    auto ctx = Ctx{ instance::server };
    auto prog = assembly::make();
    auto func = function::make();
    func->id = 1;

    for (auto i = 0; i < 3; ++i)
    {
        auto zero = instruction::make();
        zero->opcode = opcode::OP_GetZero;
        func->instructions.push_back(std::move(zero));
    }

    auto vector = instruction::make();
    vector->opcode = opcode::OP_GetVector;
    vector->data = { "0", "0", "0" };
    func->instructions.push_back(std::move(vector));
    prog->functions.push_back(std::move(func));

    auto const [script, stack, devmap] = ctx.assembler().assemble(*prog);
    auto const id = ctx.opcode_id(opcode::OP_GetVector);
    auto const payload = script.size - 12;

    REQUIRE(payload % 4 == 0);
    REQUIRE(script.data[payload - 4] == id);
    REQUIRE(script.data[payload - 3] == 0);
    REQUIRE(script.data[payload - 2] == 0);
    REQUIRE(script.data[payload - 1] == id);

    for (auto i = payload; i < script.size; ++i)
    {
        REQUIRE(script.data[i] == 0);
    }
}

TEST_CASE("assembler: big endian vector alignment", "[gsc][assembler]")
{
    SECTION("iw5 xb2")
    {
        assemble_padded_vector<iw5_xb::context>();
    }

    SECTION("s1 ps3")
    {
        assemble_padded_vector<s1_ps::context>();
    }
}

} // namespace xsk::test
