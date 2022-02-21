// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

using read_cb_type = std::function<std::vector<std::uint8_t>(const std::string&)>;

enum class build
{
    prod,
    dev,
};

enum class abort_t
{
    abort_none = 0,
    abort_continue = 1,
    abort_break = 2,
    abort_return = 3,
};

struct include_t
{
    std::string name;
    std::vector<std::string> funcs;

    include_t(const std::string& name, const std::vector<std::string>& funcs) : name(name), funcs(funcs) {}
};

struct animtree_t
{
    std::string name;
    bool loaded;
};

struct instruction
{
    using ptr = std::unique_ptr<instruction>;

    std::uint32_t index;
    std::uint32_t size;
    std::uint8_t opcode;
    std::vector<std::string> data;

    instruction() : index(0), size(0), opcode(0xFF) {}
};

struct function
{
    using ptr = std::unique_ptr<function>;

    std::uint32_t index;
    std::uint32_t size;
    std::uint8_t params;
    std::uint8_t flags;
    std::string name;
    std::vector<instruction::ptr> instructions;
    std::unordered_map<std::uint32_t, std::string> labels;

    function() : index(0), size(0), params(0), flags(0) {}
};

struct animation_ref
{
    using ptr = std::shared_ptr<animation_ref>;

    std::string name;
    std::uint32_t ref;
};

struct animtree_ref
{
    using ptr = std::shared_ptr<animtree_ref>;

    std::string name;
    std::vector<std::uint32_t> refs;
    std::vector<animation_ref> anims;
};

enum class string_type : std::uint8_t
{
    literal = 0,
    canonical = 1,
};

struct string_ref
{
    using ptr = std::shared_ptr<string_ref>;

    std::string name;
    std::uint8_t type;
    std::vector<std::uint32_t> refs;
};

enum class export_flags : std::uint8_t
{
    none         = 0x00,
    vis_public   = 0x01,
    vis_autoexec = 0x02,
    vis_private  = 0x04,
    unk1         = 0x08, // never seen
    unk2         = 0x10, // inside dev /##/ ?
    varargs_may  = 0x20, // T7, T8, T9
};

struct export_ref
{
    using ptr = std::shared_ptr<export_ref>;

    std::uint32_t checksum;
    std::uint32_t offset;
    std::string name;
    std::string space;
    std::uint8_t params;
    std::uint8_t flags;
    std::uint32_t size;
};

enum class import_flags : std::uint8_t
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

struct import_ref
{
    using ptr = std::shared_ptr<import_ref>;

    std::string space;
    std::string name;
    std::uint8_t params;
    std::uint8_t flags;
    std::vector<std::uint32_t> refs;
};

struct header
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
    // char[1] pad;
};

struct assembly
{
    using ptr = std::unique_ptr<assembly>;

    std::vector<function::ptr> functions;
    std::vector<std::string> includes;
    std::vector<animtree_ref> animtrees;
};

} // namespace xsk::arc
