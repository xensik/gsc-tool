// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/gsc/common/types.hpp"
#include "xsk/gsc/source.hpp"
#include "xsk/gsc/assembler.hpp"
#include "xsk/gsc/disassembler.hpp"
#include "xsk/gsc/compiler.hpp"
#include "xsk/gsc/decompiler.hpp"

namespace xsk::gsc
{

struct context
{
public:
    using fs_callback = std::function<std::pair<buffer, std::vector<u8>>(context const*, std::string const&)>;

    context(props props, engine engine, endian endian, system system, instance inst, u32 str_count);

    auto props() const -> props { return props_; }

    auto build() const -> build { return build_; }

    auto engine() const -> engine { return engine_; }

    auto endian() const -> endian { return endian_; }

    auto system() const -> system { return system_; }

    auto instance() const -> instance { return instance_; }

    auto str_count() const -> u32 { return str_count_; }

    auto source() -> source& { return source_; }

    auto assembler() -> assembler& { return assembler_; }

    auto disassembler() -> disassembler& { return disassembler_; }

    auto compiler() -> compiler& { return compiler_; }

    auto decompiler() -> decompiler& { return decompiler_; }

    auto func_map() const -> std::unordered_map<std::string_view, u16> const& { return func_map_rev_; }
    auto meth_map() const -> std::unordered_map<std::string_view, u16> const& { return meth_map_rev_; }

    auto init(gsc::build build, fs_callback callback) -> void;

    auto cleanup() -> void;

    auto engine_name() const -> std::string_view;

    auto opcode_size(opcode op) const -> usize;

    auto opcode_id(opcode op) const -> u8;

    auto opcode_name(opcode op) const -> std::string;

    auto opcode_enum(std::string const& name) const -> opcode;

    auto opcode_enum(u8 id) const -> opcode;

    auto func_id(std::string const& name) const -> u16;

    auto func_name(u16 id) const -> std::string;

    auto func2_id(std::string const& name) const -> u64;

    auto func2_name(u64 id) const -> std::string;

    auto func_exists(std::string const& name) const -> bool;

    auto func_add(std::string const& name, u16 id) -> void;

    auto meth_id(std::string const& name) const -> u16;

    auto meth_name(u16 id) const -> std::string;

    auto meth2_id(std::string const& name) const -> u64;

    auto meth2_name(u64 id) const -> std::string;

    auto meth_exists(std::string const& name) const -> bool;

    auto meth_add(std::string const& name, u16 id) -> void;

    auto token_id(std::string const& name) const -> u32;

    auto token_name(u32 id) const -> std::string;

    auto path_id(std::string const& name) const -> u64;

    auto path_name(u64 id) const -> std::string;

    auto hash_id(std::string const& name) const -> u64;

    auto hash_name(u64 id) const -> std::string;

    auto make_token(std::string_view str) const -> std::string;

    auto load_header(std::string const& name) -> std::tuple<std::string const*, char const*, usize>;

    auto load_include(std::string const& name) -> bool;

    auto init_includes() -> void;

    auto is_includecall(std::string const& name, std::string& path) -> bool;

protected:
    gsc::props props_;
    gsc::build build_;
    gsc::engine engine_;
    gsc::endian endian_;
    gsc::system system_;
    gsc::instance instance_;
    u32 str_count_;
    gsc::source source_;
    gsc::assembler assembler_;
    gsc::disassembler disassembler_;
    gsc::compiler compiler_;
    gsc::decompiler decompiler_;
    fs_callback fs_callback_;
    std::unordered_map<opcode, std::string_view> opcode_map_;
    std::unordered_map<std::string_view, opcode> opcode_map_rev_;
    std::unordered_map<u8, opcode> code_map_;
    std::unordered_map<opcode, u8> code_map_rev_;
    std::unordered_map<u16, std::string_view> func_map_;
    std::unordered_map<std::string_view, u16> func_map_rev_;
    std::unordered_map<u16, std::string_view> meth_map_;
    std::unordered_map<std::string_view, u16> meth_map_rev_;
    std::unordered_map<u32, std::string_view> token_map_;
    std::unordered_map<std::string_view, u32> token_map_rev_;
    std::unordered_map<u64, std::string_view> func_map2_;
    std::unordered_map<u64, std::string_view> meth_map2_;
    std::unordered_map<u64, std::string_view> path_map_;
    std::unordered_map<u64, std::string_view> hash_map_;
    std::unordered_map<std::string, std::vector<u8>> header_files_;
    std::unordered_set<std::string_view> includes_;
    std::unordered_map<std::string, std::vector<std::string>> include_cache_;
    std::unordered_set<std::string> new_func_map_;
    std::unordered_set<std::string> new_meth_map_;
};

} // namespace xsk::gsc
