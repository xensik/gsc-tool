// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct instruction
{
    std::uint32_t index;
    std::uint32_t size;
    std::uint8_t opcode;
    std::vector<std::string> data;

    instruction() : index(0), size(0), opcode(0xFF) { }
};

using instruction_ptr = std::unique_ptr<instruction>;

struct function
{
    std::uint32_t index;
    std::uint32_t size;
    std::uint32_t id;
    std::string name;
    std::vector<instruction_ptr> instructions;
    std::unordered_map<std::uint32_t, std::string> labels;

    function() : index(0), size(0), id(0) { }
};

using function_ptr = std::unique_ptr<function>;

} // namespace xsk::gsc
