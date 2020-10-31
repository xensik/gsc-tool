// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW5_DISASSEMBLER_H_
#define _GSC_IW5_DISASSEMBLER_H_

namespace IW5
{

class disassembler : public gsc::disassembler
{
	std::shared_ptr<utils::byte_buffer> script_;
	std::shared_ptr<utils::byte_buffer> stack_;
	std::unique_ptr<utils::byte_buffer> output_;
	std::vector<std::shared_ptr<function>> functions_;
	bool ida_output_;

public:
	disassembler(bool ida_output);

	void disassemble(std::string& script, std::string& stack);
	auto output() -> std::vector<std::shared_ptr<function>>;
	auto output_asm() -> std::string;

private:
	void dissasemble_function(std::shared_ptr<function> func);
	void dissasemble_instruction(std::shared_ptr<instruction> inst);
	void disassemble_builtin_call(std::shared_ptr<instruction> inst, bool method, bool arg_num);
	void disassemble_local_call(std::shared_ptr<instruction> inst, bool thread);
	void disassemble_far_call(std::shared_ptr<instruction> inst, bool thread);
	void disassemble_jump(std::shared_ptr<instruction> inst, bool expr, bool back);
	void disassemble_field_variable(std::shared_ptr<instruction> inst);
	void disassemble_switch(std::shared_ptr<instruction> inst);
	void disassemble_end_switch(std::shared_ptr<instruction> inst);
	auto disassemble_offset() -> std::int32_t;
	void resolve_local_functions();
	auto resolve_function(const std::string& index) -> std::string;
	void print_script_name(const std::string& name);
	void print_opcodes(std::uint32_t index, std::uint32_t size);
	void print_function(std::shared_ptr<function> func);
	void print_instruction(std::shared_ptr<instruction> inst);
	void print_label(const std::string& label);
};

} // namespace IW5

#endif // _GSC_IW5_DISASSEMBLER_H_
