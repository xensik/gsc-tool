// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::arc
{

struct asm_instruction
{
    std::uint32_t index;
    std::uint32_t size;
    std::uint8_t opcode;
    std::vector<std::string> data;

    asm_instruction() : index(0), size(0), opcode(0xFF) { }
};

using asm_instruction_ptr = std::unique_ptr<asm_instruction>;

struct asm_function
{
    std::uint32_t index;
    std::uint32_t size;
    std::uint8_t params;
    std::uint8_t flags;
    std::string name;
    std::vector<asm_instruction_ptr> instructions;
    std::unordered_map<std::uint32_t, std::string> labels;

    asm_function() : index(0), size(0), params(0), flags(0) { }
};

using asm_function_ptr = std::unique_ptr<asm_function>;

struct asm_data
{
    std::vector<std::string> includes;
    std::vector<asm_function_ptr> functions;
};

using asm_data_ptr = std::unique_ptr<asm_data>;

struct asm_animation
{
    std::string name;
    std::uint32_t ref;
};

struct asm_animtree
{
    std::string name;
    std::vector<std::uint32_t> refs;
    std::vector<asm_animation> anims;
};

using asm_animtree_ptr = std::shared_ptr<asm_animtree>;

struct asm_string
{
    std::string name;
    std::vector<std::uint32_t> refs;
};

struct asm_export
{
    std::uint32_t checksum;
    std::uint32_t offset;
    std::string name;
    std::string space;
    std::uint8_t params;
    std::uint8_t flags;
    std::uint32_t size;
};

struct asm_import
{
    std::string name;
    std::string space;
    std::uint8_t params;
    std::vector<std::uint32_t> refs;
};

using asm_import_ptr = std::shared_ptr<asm_import>;

struct asm_header
{
    std::uint64_t magic;
    std::uint32_t source_crc;
    std::uint32_t include_offset;
    std::uint32_t animtree_offset;
    std::uint32_t cseg_offset;
    std::uint32_t stringtablefixup_offset;
    std::uint32_t exports_offset;
    std::uint32_t imports_offset;
    std::uint32_t fixup_offset;
    std::uint32_t profile_offset;
    std::uint32_t cseg_size;
    std::uint16_t name;
    std::uint16_t stringtablefixup_count;
    std::uint16_t exports_count;
    std::uint16_t imports_count;
    std::uint16_t fixup_count;
    std::uint16_t profile_count;
    std::uint8_t include_count;
    std::uint8_t animtree_count;
    std::uint8_t flags;
};

} // namespace xsk::gsc::arc
