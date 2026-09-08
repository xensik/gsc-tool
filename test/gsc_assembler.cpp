// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/engine/iw5_xb.hpp"
#include <catch_amalgamated.hpp>

namespace xsk::test
{

using namespace xsk::gsc;

TEST_CASE("IW5 XB assembler: vector alignment marker", "[gsc][assembler][iw5][xb2]")
{
    iw5_xb::context context(instance::server);
    auto program = assembly::make();
    auto function = function::make();
    function->id = 1;

    for (auto i = 0; i < 3; ++i)
    {
        auto instruction = instruction::make();
        instruction->opcode = opcode::OP_GetZero;
        function->instructions.push_back(std::move(instruction));
    }

    auto vector = instruction::make();
    vector->opcode = opcode::OP_GetVector;
    vector->data = { "0", "0", "0" };
    function->instructions.push_back(std::move(vector));
    program->functions.push_back(std::move(function));

    auto const [script, stack, devmap] = context.assembler().assemble(*program);
    auto const vector_opcode = context.opcode_id(opcode::OP_GetVector);

    REQUIRE(script.size == 20);
    REQUIRE(script.data[4] == vector_opcode);
    REQUIRE(script.data[5] == 0);
    REQUIRE(script.data[6] == 0);
    REQUIRE(script.data[7] == vector_opcode);

    for (usize i = 8; i < 20; ++i)
    {
        REQUIRE(script.data[i] == 0);
    }
}

} // namespace xsk::test
