// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/utils/reader.hpp"
#include "xsk/gsc/common/types.hpp"

namespace xsk::gsc
{

struct disassembler
{
private:
    context const* ctx_;
    function::ptr func_;
    assembly::ptr assembly_;
    utils::reader script_;
    utils::reader stack_;

public:
    explicit disassembler(context const* ctx);
    auto disassemble(buffer const& script, buffer const& stack) -> assembly::ptr;
    auto disassemble(std::vector<u8> const& script, std::vector<u8> const& stack) -> assembly::ptr;
    auto disassemble(u8 const* script, usize script_size, u8 const* stack, usize stack_size) -> assembly::ptr;

private:
    auto dissasemble_function(function& func) -> void;
    auto dissasemble_instruction(instruction& inst) -> void;
    auto disassemble_field(instruction& inst) -> void;
    auto disassemble_params(instruction& inst) -> void;
    auto disassemble_call_far(instruction& inst, bool thread) -> void;
    auto disassemble_call_far2(instruction& inst, bool thread) -> void;
    auto disassemble_call_local(instruction& inst, bool thread) -> void;
    auto disassemble_call_builtin(instruction& inst, bool method, bool args) -> void;
    auto disassemble_call_builtin2(instruction& inst, bool method, bool args) -> void;
    auto disassemble_jump(instruction& inst, bool expr, bool back) -> void;
    auto disassemble_switch(instruction& inst) -> void;
    auto disassemble_switch_table(instruction& inst) -> void;
    auto disassemble_offset() -> i32;
    auto resolve_functions() -> void;
    auto resolve_function(std::string const& index) -> std::string;
    auto decrypt_string(std::string const& str) -> std::string;
};

} // namespace xsk::gsc
