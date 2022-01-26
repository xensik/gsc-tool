// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::s2
{

class assembler : public gsc::assembler
{
    std::string filename_;
    utils::byte_buffer::ptr script_;
    utils::byte_buffer::ptr stack_;
    std::vector<function::ptr> functions_;
    std::unordered_map<std::uint32_t, std::string> labels_;

public:
    auto output_script() -> std::vector<std::uint8_t>;
    auto output_stack() -> std::vector<std::uint8_t>;
    void assemble(const std::string& file, std::vector<std::uint8_t>& data);
    void assemble(const std::string& file, std::vector<function::ptr>& funcs);

private:
    void assemble_function(const function::ptr& func);
    void assemble_instruction(const instruction::ptr& inst);
    void assemble_builtin_call(const instruction::ptr& inst, bool method, bool args);
    void assemble_local_call(const instruction::ptr& inst, bool thread);
    void assemble_far_call(const instruction::ptr& inst, bool thread);
    void assemble_switch(const instruction::ptr& inst);
    void assemble_end_switch(const instruction::ptr& inst);
    void assemble_field_variable(const instruction::ptr& inst);
    void assemble_jump(const instruction::ptr& inst, bool expr, bool back);
    void assemble_offset(std::int32_t offset);
    auto resolve_function(const std::string& name) -> std::int32_t;
    auto resolve_label(const std::string& name) -> std::int32_t;
};

} // namespace xsk::gsc::s2
