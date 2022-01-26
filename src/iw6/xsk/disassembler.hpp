// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::iw6
{

class disassembler : public gsc::disassembler
{
    std::string filename_;
    utils::byte_buffer::ptr script_;
    utils::byte_buffer::ptr stack_;
    utils::byte_buffer::ptr output_;
    std::vector<function::ptr> functions_;
    std::unordered_map<std::uint32_t, std::string> labels_;

public:
    auto output() -> std::vector<function::ptr>;
    auto output_data() -> std::vector<std::uint8_t>;
    void disassemble(const std::string& file, std::vector<std::uint8_t>& script, std::vector<std::uint8_t>& stack);

private:
    void dissasemble_function(const function::ptr& func);
    void dissasemble_instruction(const instruction::ptr& inst);
    void disassemble_builtin_call(const instruction::ptr& inst, bool method, bool args);
    void disassemble_local_call(const instruction::ptr& inst, bool thread);
    void disassemble_far_call(const instruction::ptr& inst, bool thread);
    void disassemble_switch(const instruction::ptr& inst);
    void disassemble_end_switch(const instruction::ptr& inst);
    void disassemble_field_variable(const instruction::ptr& inst);
    void disassemble_jump(const instruction::ptr& inst, bool expr, bool back);
    auto disassemble_offset() -> std::int32_t;
    void resolve_local_functions();
    auto resolve_function(const std::string& index) -> std::string;
    void print_function(const function::ptr& func);
    void print_instruction(const instruction::ptr& inst);
};

} // namespace xsk::gsc::iw6
