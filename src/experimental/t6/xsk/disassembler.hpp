// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::t6
{

class disassembler : public arc::disassembler
{
    std::string filename_;
    utils::byte_buffer_ptr script_;
    utils::byte_buffer_ptr output_;
    arc::asm_data_ptr data_;
    arc::asm_header header_;
    std::vector<std::string> includes_;
    std::vector<arc::asm_animtree_ptr> animtrees_;
    std::vector<arc::asm_string> stringtable_;
    std::vector<arc::asm_export> exports_;
    std::vector<arc::asm_import_ptr> imports_;
    std::map<std::uint32_t, std::string> string_refs_;
    std::map<std::uint32_t, std::string> animtree_refs_;
    std::map<std::uint32_t, arc::asm_import_ptr> import_refs_;
    std::unordered_map<std::uint32_t, std::string> labels_;

public:
    auto output() -> arc::asm_data_ptr;
    auto output_raw() -> std::vector<std::uint8_t>;
    void disassemble(const std::string& file, std::vector<std::uint8_t>& data);

private:
    void disassemble_header();
    void disassemble_strings();
    void disassemble_includes();
    void disassemble_animtrees();
    void disassemble_stringtable();
    void disassemble_imports();
    void disassemble_exports();
    void disassemble_function(const arc::asm_function_ptr& func);
    void disassemble_instruction(const arc::asm_instruction_ptr& inst);
    auto resolve_string(std::uint32_t ref) -> std::string;
    void print_function(const arc::asm_function_ptr& func);
    void print_instruction(const arc::asm_instruction_ptr& inst);
};

} // namespace xsk::gsc::t6
