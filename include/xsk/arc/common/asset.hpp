// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

constexpr usize header_size_v1 = 64;
constexpr usize header_size_v2 = 72;
constexpr usize header_size_v3 = 0;

enum class string_type : u8
{
    literal = 0,
    canonical = 1,
};

enum class param_type : u8
{
    value = 0,
    reference = 1,
    vararg = 2,
};

enum class export_flags : u8
{
    export_none     = 0x00,
    export_public   = 0x01,
    export_autoexec = 0x02,
    export_private  = 0x04,
    export_codecall = 0x08,
    export_private2 = 0x10,
    export_varargs  = 0x20,
};

enum class import_flags : u8
{
    none             = 0,
    func_reference   = 1,
    func_call        = 2,
    func_call_thread = 3,
    meth_call        = 4,
    meth_call_thread = 5,
    developer        = 0x10,
    unk              = 0x20, // T7, T8, T9
};

struct header
{
    u64 magic;
    u32 source_crc;
    u32 include_offset;
    u32 animtree_offset;
    u32 cseg_offset;
    u32 stringtablefixup_offset;
    u32 devblock_stringtablefixup_offset;
    u32 exports_offset;
    u32 imports_offset;
    u32 fixup_offset;
    u32 globalvar_offset;
    u32 profile_offset;
    u32 cseg_size;
    u32 name;
    u16 stringtablefixup_count;
    u16 exports_count;
    u16 imports_count;
    u16 fixup_count;
    u16 globalvar_count;
    u16 profile_count;
    u16 devblock_stringtablefixup_count;
    u8 include_count;
    u8 animtree_count;
    u8 flags;
};

struct animation_ref
{
    std::string name;
    u32 ref;
};

struct animtree_ref
{
    using ptr = std::shared_ptr<animtree_ref>;

    std::string name;
    std::vector<u32> refs;
    std::vector<animation_ref> anims;
};

struct string_ref
{
    using ptr = std::shared_ptr<string_ref>;

    std::string name;
    u8 type;
    std::vector<u32> refs;
};

struct import_ref
{
    using ptr = std::shared_ptr<import_ref>;

    std::string space;
    std::string name;
    u8 params;
    u8 flags;
    std::vector<u32> refs;
};

struct export_ref
{
    using ptr = std::shared_ptr<export_ref>;

    std::string space;
    std::string name;
    u32 checksum;
    u32 offset;
    u32 size;
    u8 params;
    u8 flags;
};

} // namespace xsk::arc
