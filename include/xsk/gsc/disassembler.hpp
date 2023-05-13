// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/utils/reader.hpp"
#include "xsk/gsc/common/types.hpp"

namespace xsk::gsc
{

class disassembler
{
    context const* ctx_;
    function::ptr func_;
    assembly::ptr assembly_;
    utils::reader script_;
    utils::reader stack_;

public:
    disassembler(context const* ctx);
    auto disassemble(buffer const& script, buffer const& stack) -> assembly::ptr;
    auto disassemble(std::vector<u8> const& script, std::vector<u8> const& stack) -> assembly::ptr;
    auto disassemble(u8 const* script, usize script_size, u8 const* stack, usize stack_size) -> assembly::ptr;

private:
    auto dissasemble_function(function& func) -> void;
    auto dissasemble_instruction(instruction& inst) -> void;
    auto disassemble_builtin_call(instruction& inst, bool method, bool args) -> void;
    auto disassemble_local_call(instruction& inst, bool thread) -> void;
    auto disassemble_far_call(instruction& inst, bool thread) -> void;
    auto disassemble_switch(instruction& inst) -> void;
    auto disassemble_end_switch(instruction& inst) -> void;
    auto disassemble_field_variable(instruction& inst) -> void;
    auto disassemble_formal_params(instruction& inst) -> void;
    auto disassemble_jump(instruction& inst, bool expr, bool back) -> void;
    auto disassemble_offset() -> i32;
    auto resolve_functions() -> void;
    auto resolve_function(std::string const& index) -> std::string;
    auto decrypt_string(std::string const& str) -> std::string;
};

} // namespace xsk::gsc
