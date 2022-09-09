// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc::t6
{

class assembler : public arc::assembler
{
    std::string filename_;
    utils::byte_buffer::ptr script_;
    assembly::ptr assembly_;
    std::unordered_map<std::uint32_t, std::string> labels_;
    std::unordered_map<std::string, std::uint16_t> stringlist_;
    std::vector<export_ref> exports_;
    std::vector<import_ref> imports_;
    std::vector<animtree_ref> animtrees_;
    std::vector<string_ref> stringtables_;
    header header_;

public:
    auto output() -> std::vector<std::uint8_t>;
    void assemble(const std::string& file, std::vector<std::uint8_t>& data);
    void assemble(const std::string& file, assembly::ptr& data);

private:
    void assemble_function(const function::ptr& func);
    void assemble_instruction(const instruction::ptr& inst);
    void assemble_localvars(const instruction::ptr& inst);
    void assemble_jump(const instruction::ptr& inst);
    void assemble_switch(const instruction::ptr& inst);
    void assemble_end_switch(const instruction::ptr& inst);
    void process_string(const std::string& data);
    void process_function(const function::ptr& func);
    void process_instruction(const instruction::ptr& inst);
    void align_instruction(const instruction::ptr& inst);
    auto resolve_label(const std::string& name) -> std::int32_t;
    auto string_offset(const std::string& data) -> std::uint16_t;
    void add_string_reference(const std::string& str, string_type type, std::uint32_t ref);
    void add_import_reference(const std::vector<std::string>& data, std::uint32_t ref);
    void add_anim_reference(const std::vector<std::string>& data, std::uint32_t ref);
};

} // namespace xsk::arc::t6
