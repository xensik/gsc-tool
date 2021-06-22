// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "cstdint"

namespace xsk::gsc::arc
{

// T6

// Header 0x40
// string_section
// include_section
// code_section
// export_section
// import_section
// animtree_section
// stringtablefixup_section
// fixup_section empty
// profile_section empty

constexpr std::uint64_t T6_MAGIC = 0x06000A0D43534780;

struct /*__declspec(align(2))*/ T6_GSC_OBJ
{
    char magic[8];
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

struct T6_GSC_STRINGTABLE_ITEM
{
    std::uint16_t string;
    std::uint8_t num_address;
    std::uint8_t type;
};

struct T6_GSC_IMPORT_ITEM
{
    std::uint16_t name;
    std::uint16_t name_space;
    std::uint16_t num_address;
    std::uint8_t param_count;
    std::uint8_t flags;
};

struct T6_GSC_ANIMTREE_ITEM
{
  std::uint16_t name;
  std::uint16_t num_tree_address;
  std::uint16_t num_node_address;
  char pad[2];
};

struct T6_GSC_ANIMNODE_ITEM
{
    std::uint32_t name;
    std::uint32_t address;
};

struct T6_GSC_EXPORT_ITEM
{
    std::uint32_t checksum;
    std::uint32_t address;
    std::uint16_t name;
    std::uint8_t param_count;
    std::uint8_t flags;
};

struct T6_GSC_FIXUP_ITEM
{
    std::uint32_t offset;
    std::uint32_t address;
};

// T7

// T8

struct /*__declspec(align(4))*/ T9_GSC_OBJ
{
    std::uint8_t magic[8];
    std::uint32_t source_crc;
    std::uint32_t include_offset;
    std::uint32_t animtree_offset;
    std::uint32_t cseg_offset;
    std::uint32_t stringtablefixup_offset;
    std::uint32_t devblock_stringtablefixup_offset;
    std::uint32_t exports_offset;
    std::uint32_t imports_offset;
    std::uint32_t fixup_offset;
    std::uint32_t globalvar_offset;
    std::uint32_t profile_offset;
    std::uint32_t cseg_size;
    std::uint16_t name;
    std::uint16_t stringtablefixup_count;
    std::uint16_t exports_count;
    std::uint16_t imports_count;
    std::uint16_t fixup_count;
    std::uint16_t globalvar_count;
    std::uint16_t profile_count;
    std::uint16_t devblock_stringtablefixup_count;
    std::uint8_t include_count;
    std::uint8_t animtree_count;
    std::uint8_t flags;
};

struct T9_GSC_IMPORT_ITEM
{
    uint32_t name;
    uint32_t name_space;
    uint16_t num_address;
    uint8_t param_count;
    uint8_t flags;
};

} // namespace xsk::gsc::arc
