// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::iw8
{

class disassembler : public gsc::disassembler
{
    std::string filename_;
    utils::byte_buffer_ptr script_;
    utils::byte_buffer_ptr stack_;
    utils::byte_buffer_ptr output_;
    std::vector<gsc::function_ptr> functions_;
    std::unordered_map<std::uint32_t, std::string> labels_;

public:
    auto output() -> std::vector<gsc::function_ptr>;
    auto output_data() -> std::vector<std::uint8_t>;
    void disassemble(const std::string& file, std::vector<std::uint8_t>& script, std::vector<std::uint8_t>& stack);

private:
    void dissasemble_function(const gsc::function_ptr& func);
    void dissasemble_instruction(const gsc::instruction_ptr& inst);
    void disassemble_builtin_call(const gsc::instruction_ptr& inst, bool method, bool arg_num);
    void disassemble_local_call(const gsc::instruction_ptr& inst, bool thread);
    void disassemble_far_call(const gsc::instruction_ptr& inst, bool thread);
    void disassemble_jump(const gsc::instruction_ptr& inst, bool expr, bool back);
    void disassemble_field_variable(const gsc::instruction_ptr& inst);
    void disassemble_formal_params(const gsc::instruction_ptr& inst);
    void disassemble_switch(const gsc::instruction_ptr& inst);
    void disassemble_end_switch(const gsc::instruction_ptr& inst);
    auto disassemble_offset() -> std::int32_t;
    void resolve_local_functions();
    auto resolve_function(const std::string& index) -> std::string;
    void print_function(const gsc::function_ptr& func);
    void print_instruction(const gsc::instruction_ptr& inst);
};

} // namespace xsk::gsc::iw8
