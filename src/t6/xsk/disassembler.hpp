// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc::t6
{

class disassembler : public arc::disassembler
{
    std::string filename_;
    utils::byte_buffer::ptr script_;
    utils::byte_buffer::ptr output_;
    assembly::ptr assembly_;
    std::vector<export_ref::ptr> exports_;
    std::vector<import_ref::ptr> imports_;
    std::vector<string_ref::ptr> strings_;
    std::vector<animtree_ref::ptr> animtrees_;
    std::map<std::uint32_t, std::string> stringlist_;
    std::map<std::uint32_t, import_ref::ptr> import_refs_;
    std::map<std::uint32_t, string_ref::ptr> string_refs_;
    std::map<std::uint32_t, animtree_ref::ptr> anim_refs_;
    std::unordered_map<std::uint32_t, std::string> labels_;
    header header_;

public:
    auto output() -> assembly::ptr;
    auto output_raw() -> std::vector<std::uint8_t>;
    void disassemble(const std::string& file, std::vector<std::uint8_t>& data);

private:
    void disassemble_function(const function::ptr& func);
    void disassemble_instruction(const instruction::ptr& inst);
    void disassemble_string(const instruction::ptr& inst);
    void disassemble_animation(const instruction::ptr& inst);
    void disassemble_localvars(const instruction::ptr& inst);
    void disassemble_import(const instruction::ptr& inst);
    void disassemble_jump(const instruction::ptr& inst);
    void disassemble_switch(const instruction::ptr& inst);
    void disassemble_end_switch(const instruction::ptr& inst);
    void disassemble_devblock(const instruction::ptr& inst);
    void print_function(const function::ptr& func);
    void print_instruction(const instruction::ptr& inst);
};

} // namespace xsk::arc::t6
