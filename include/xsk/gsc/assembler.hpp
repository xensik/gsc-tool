// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/utils/writer.hpp"
#include "xsk/gsc/common/types.hpp"

namespace xsk::gsc
{

class assembler
{
    context const* ctx_;
    function const* func_;
    assembly const* assembly_;
    utils::writer script_;
    utils::writer stack_;

public:
    assembler(context const* ctx);
    auto assemble(assembly const& data) -> std::pair<buffer, buffer>;

private:
    auto assemble_function(function const& func) -> void;
    auto assemble_instruction(instruction const& inst) -> void;
    auto assemble_builtin_call(instruction const& inst, bool method, bool args) -> void;
    auto assemble_local_call(instruction const& inst, bool thread) -> void;
    auto assemble_far_call(instruction const& inst, bool thread) -> void;
    auto assemble_switch(instruction const& inst) -> void;
    auto assemble_end_switch(instruction const& inst) -> void;
    auto assemble_field_variable(instruction const& inst) -> void;
    auto assemble_formal_params(instruction const& inst) -> void;
    auto assemble_jump(instruction const& inst, bool expr, bool back) -> void;
    auto assemble_offset(i32 offs) -> void;
    auto resolve_function(std::string const& name) -> i32;
    auto resolve_label(std::string const& name) -> i32;
    auto encrypt_string(std::string const& str) -> std::string;
};

} // namespace xsk::gsc
