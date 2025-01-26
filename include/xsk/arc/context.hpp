// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/arc/common/types.hpp"
#include "xsk/arc/source.hpp"
#include "xsk/arc/assembler.hpp"
#include "xsk/arc/disassembler.hpp"
#include "xsk/arc/compiler.hpp"
#include "xsk/arc/decompiler.hpp"

namespace xsk::arc
{

struct context
{
public:
    using fs_callback = std::function<std::vector<u8>(std::string const&)>;

    context(props props, engine engine, endian endian, system system, instance inst, u64 magic);

    auto props() const -> props { return props_; }
    auto build() const -> build { return build_; }
    auto engine() const -> engine { return engine_; }
    auto endian() const -> endian { return endian_; }
    auto system() const -> system { return system_; }
    auto instance() const -> instance { return instance_; }
    auto magic() const -> u64 { return magic_; }
    auto source() -> source& { return source_; }
    auto assembler() -> assembler& { return assembler_; }
    auto disassembler() -> disassembler& { return disassembler_; }
    auto compiler() -> compiler& { return compiler_; }
    auto decompiler() -> decompiler& { return decompiler_; }

    auto fixup(bool value) -> void { fixup_ = value; }
    auto fixup() const -> bool { return fixup_; }

    auto init(arc::build build, fs_callback callback) -> void;
    auto cleanup() -> void;
    auto engine_name() const -> std::string_view;

    auto opcode_size(opcode op) const -> u32;
    auto opcode_id(opcode op) const -> u16;
    auto opcode_name(opcode op) const -> std::string;
    auto opcode_enum(std::string const& name) const -> opcode;
    auto opcode_enum(u16 id) const -> opcode;
    auto hash_id(std::string const& name) const -> u32;
    auto hash_name(u32 id) const -> std::string;
    auto make_token(std::string_view str) const -> std::string;
    auto load_header(std::string const& name) -> std::tuple<std::string const*, char const*, usize>;

protected:
    arc::props props_;
    arc::build build_;
    arc::engine engine_;
    arc::endian endian_;
    arc::system system_;
    arc::instance instance_;
    u64 magic_;
    arc::source source_;
    arc::assembler assembler_;
    arc::disassembler disassembler_;
    arc::compiler compiler_;
    arc::decompiler decompiler_;
    bool fixup_{ false };

    fs_callback fs_callback_;
    std::unordered_map<opcode, std::string_view> opcode_map_;
    std::unordered_map<std::string_view, opcode> opcode_map_rev_;
    std::unordered_map<u16, opcode> code_map_;
    std::unordered_map<opcode, u16> code_map_rev_;
    std::unordered_map<u32, std::string_view> hash_map_;
    std::unordered_map<std::string, std::vector<u8>> header_files_;
};

} // namespace xsk::arc
