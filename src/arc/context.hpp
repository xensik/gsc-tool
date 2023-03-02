// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "misc/types.hpp"
#include "source.hpp"
#include "disassembler.hpp"
#include "decompiler.hpp"

namespace xsk::arc
{

class context
{
public:
    using fs_callback = std::function<std::vector<u8>(std::string const&)>;

    context(props props, engine engine, endian endian, system system, u64 magic);

    auto props() const -> props { return props_; }
    auto build() const -> build { return build_; }
    auto engine() const -> engine { return engine_; }
    auto endian() const -> endian { return endian_; }
    auto system() const -> system { return system_; }
    auto instance() const -> instance { return instance_; }
    auto magic() const -> u64 { return magic_; }
    auto source() -> source& { return source_; }
    auto disassembler() -> disassembler& { return disassembler_; }
    auto decompiler() -> decompiler& { return decompiler_; }

    auto init(arc::build build, fs_callback callback) -> void;
    auto cleanup() -> void;
    auto engine_name() const -> std::string_view;

    auto opcode_size(opcode op) const -> u32;
    auto opcode_id(opcode op) const -> u8;
    auto opcode_name(opcode op) const -> std::string;
    auto opcode_enum(std::string const& name) const -> opcode;
    auto opcode_enum(u16 id) const -> opcode;
    auto dvar_id(std::string const& name) const -> u32;
    auto dvar_name(u32 id) const -> std::string;
    auto hash_id(std::string const& name) const -> u32;
    auto hash_name(u32 id) const -> std::string;

protected:
    arc::props props_;
    arc::build build_;
    arc::engine engine_;
    arc::endian endian_;
    arc::system system_;
    arc::instance instance_;
    u64 magic_;
    arc::source source_;
    arc::disassembler disassembler_;
    arc::decompiler decompiler_;

    fs_callback fs_callback_;
    std::unordered_map<opcode, std::string_view> opcode_map_;
    std::unordered_map<std::string_view, opcode> opcode_map_rev_;
    std::unordered_map<u16, opcode> code_map_;
    std::unordered_map<opcode, u8> code_map_rev_;
    std::unordered_map<u32, std::string_view> dvar_map_;
    std::unordered_map<u32, std::string_view> hash_map_;
};

} // namespace xsk::arc
