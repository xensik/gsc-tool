// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/decompiler.hpp"
#include "xsk/gsc/decompiler.hpp"
#include <catch_amalgamated.hpp>

namespace xsk::test
{

TEST_CASE("gsc decompiler: reject stack underflow", "[decompiler]")
{
    auto data = gsc::assembly::make();
    auto func = gsc::function::make();
    func->name = "test";

    auto inst = gsc::instruction::make();
    inst->opcode = gsc::opcode::OP_ScriptFarThreadCall;
    inst->data = { "script", "function", "1" };
    func->instructions.push_back(std::move(inst));
    data->functions.push_back(std::move(func));

    auto decomp = gsc::decompiler{ nullptr };
    REQUIRE_THROWS_AS(decomp.decompile(*data), gsc::decomp_error);
}

TEST_CASE("gsc decompiler: reject empty stack peek", "[decompiler]")
{
    auto data = gsc::assembly::make();
    auto func = gsc::function::make();
    func->name = "test";

    auto inst = gsc::instruction::make();
    inst->opcode = gsc::opcode::OP_SafeSetWaittillVariableFieldCached;
    inst->data = { "0" };
    func->instructions.push_back(std::move(inst));
    data->functions.push_back(std::move(func));

    auto decomp = gsc::decompiler{ nullptr };
    REQUIRE_THROWS_AS(decomp.decompile(*data), gsc::decomp_error);
}

TEST_CASE("arc decompiler: reject stack underflow", "[decompiler]")
{
    auto data = arc::assembly::make();
    auto func = arc::function::make();
    func->name = "test";

    auto inst = arc::instruction::make();
    inst->opcode = arc::opcode::OP_Return;
    func->instructions.push_back(std::move(inst));
    data->functions.push_back(std::move(func));

    auto decomp = arc::decompiler{ nullptr };
    REQUIRE_THROWS_AS(decomp.decompile(*data), arc::decomp_error);
}

TEST_CASE("arc decompiler: reject empty stack peeks", "[decompiler]")
{
    for (auto opcode : { arc::opcode::OP_DecTop, arc::opcode::OP_ScriptFunctionCallClass, arc::opcode::OP_ScriptThreadCallClass })
    {
        auto data = arc::assembly::make();
        auto func = arc::function::make();
        func->name = "test";

        auto inst = arc::instruction::make();
        inst->opcode = opcode;
        inst->data = { "function" };
        func->instructions.push_back(std::move(inst));
        data->functions.push_back(std::move(func));

        auto decomp = arc::decompiler{ nullptr };
        CAPTURE(static_cast<int>(opcode));
        REQUIRE_THROWS_AS(decomp.decompile(*data), arc::decomp_error);
    }
}

} // namespace xsk::test
