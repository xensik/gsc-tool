// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/utils/reader.hpp"
#include "xsk/arc/common/types.hpp"

namespace xsk::arc
{

struct disassembler
{
private:
    context const* ctx_;
    function::ptr func_;
    assembly::ptr assembly_;
    utils::reader script_;
    std::map<usize, import_ref::ptr> import_refs_;
    std::map<usize, string_ref::ptr> string_refs_;
    std::map<usize, animtree_ref::ptr> anim_refs_;

public:
    explicit disassembler(context const* ctx);
    auto disassemble(buffer const& data) -> assembly::ptr;
    auto disassemble(std::vector<u8> const& data) -> assembly::ptr;
    auto disassemble(u8 const* data, usize data_size) -> assembly::ptr;

private:
    auto disassemble_function(function& func) -> void;
    auto disassemble_instruction(instruction& inst) -> void;
    auto disassemble_name(instruction& inst) -> void;
    auto disassemble_params(instruction& inst) -> void;
    auto disassemble_import(instruction& inst) -> void;
    auto disassemble_string(instruction& inst) -> void;
    auto disassemble_animtree(instruction& inst) -> void;
    auto disassemble_animation(instruction& inst) -> void;
    auto disassemble_jump(instruction& inst) -> void;
    auto disassemble_switch(instruction& inst) -> void;
    auto disassemble_end_switch(instruction& inst) -> void;
};

} // namespace xsk::arc
