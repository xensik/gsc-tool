// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW5_ASSEMBLER_HPP_
#define _GSC_IW5_ASSEMBLER_HPP_

namespace IW5
{

class assembler : public gsc::assembler
{
    utils::byte_buffer_ptr script_;
    utils::byte_buffer_ptr stack_;
    std::vector<gsc::function_ptr> functions_;
    std::unordered_map<std::uint32_t, std::string> labels_;

public:
    auto output_script() -> std::vector<std::uint8_t>;
    auto output_stack() -> std::vector<std::uint8_t>;
    void assemble(std::vector<std::uint8_t>& data);
    void assemble(std::vector<gsc::function_ptr>& functions);

private:
    void assemble_function(const gsc::function_ptr& func);
    void assemble_instruction(const gsc::instruction_ptr& inst);
    void assemble_builtin_call(const gsc::instruction_ptr& inst, bool method, bool arg_num);
    void assemble_local_call(const gsc::instruction_ptr& inst, bool thread);
    void assemble_far_call(const gsc::instruction_ptr& inst, bool thread);
    void assemble_switch(const gsc::instruction_ptr& inst);
    void assemble_end_switch(const gsc::instruction_ptr& inst);
    void assemble_field_variable(const gsc::instruction_ptr& inst);
    void assemble_jump(const gsc::instruction_ptr& inst, bool expr, bool back);
    void assemble_offset(std::int32_t offset);
    auto resolve_function(const std::string& name) -> std::uint32_t;
    auto resolve_label(const gsc::instruction_ptr& inst, const std::string& name) -> std::uint32_t;
};

} // namespace IW5

#endif // _GSC_IW5_ASSEMBLER_HPP_
