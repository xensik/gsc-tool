// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/utils/writer.hpp"
#include "xsk/gsc/common/types.hpp"

namespace xsk::gsc
{

struct assembler
{
private:
    context const* ctx_;
    function const* func_;
    assembly const* assembly_;
    utils::writer script_;
    utils::writer stack_;
    utils::writer devmap_;
    u32 devmap_count_;

public:
    explicit assembler(context const* ctx);
    auto assemble(assembly const& data) -> std::tuple<buffer, buffer, buffer>;

private:
    auto assemble_function(function const& func) -> void;
    auto assemble_instruction(instruction const& inst) -> void;
    auto assemble_field(instruction const& inst) -> void;
    auto assemble_params(instruction const& inst) -> void;
    auto assemble_call_far(instruction const& inst, bool thread) -> void;
    auto assemble_call_far2(instruction const& inst, bool thread) -> void;
    auto assemble_call_local(instruction const& inst, bool thread) -> void;
    auto assemble_call_builtin(instruction const& inst, bool method, bool args) -> void;
    auto assemble_jump(instruction const& inst, bool expr, bool back) -> void;
    auto assemble_switch(instruction const& inst) -> void;
    auto assemble_switch_table(instruction const& inst) -> void;
    auto assemble_offset(i32 offs) -> void;
    auto resolve_function(std::string const& name) const -> usize;
    auto resolve_label(std::string const& name) const -> usize;
    auto encrypt_string(std::string const& str) -> std::string;
};

} // namespace xsk::gsc
