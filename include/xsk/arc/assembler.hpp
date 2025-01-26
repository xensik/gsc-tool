// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/utils/writer.hpp"
#include "xsk/arc/common/types.hpp"

namespace xsk::arc
{

struct assembler
{
private:
    context const* ctx_;
    function const* func_;
    assembly const* assembly_;
    utils::writer script_;
    utils::writer devmap_;
    std::unordered_map<std::string, u16> strpool_;
    std::vector<export_ref> exports_;
    std::vector<import_ref> imports_;
    std::vector<string_ref> strings_;
    std::vector<animtree_ref> anims_;
    u32 devmap_count_;

public:
    explicit assembler(context const* ctx);
    auto assemble(assembly const& data, std::string const& name = {}) -> std::pair<buffer, buffer>;

private:
    auto assemble_function(function& func) -> void;
    auto assemble_instruction(instruction const& inst) -> void;
    auto assemble_localvars(instruction const& inst) -> void;
    auto assemble_jump(instruction const& inst) -> void;
    auto assemble_switch(instruction const& inst) -> void;
    auto assemble_switch_table(instruction const& inst) -> void;
    auto process_string(std::string const& data) -> void;
    auto process_function(function const& func) -> void;
    auto process_instruction(instruction const& inst) -> void;
    auto align_instruction(instruction& inst) -> void;
    auto resolve_label(std::string const& name) const -> usize;
    auto resolve_string(std::string const& name) -> u16;
    auto add_stringref(std::string const& str, string_type type, u32 ref) -> void;
    auto add_importref(std::vector<std::string> const& data, u32 ref) -> void;
    auto add_animref(std::vector<std::string> const& data, u32 ref) -> void;
};

} // namespace xsk::arc
