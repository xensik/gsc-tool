// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_SH1_ASSEMBLER_H_
#define _GSC_SH1_ASSEMBLER_H_

namespace SH1
{

class assembler : public gsc::assembler
{
	std::unique_ptr<utils::byte_buffer> script_;
	std::unique_ptr<utils::byte_buffer> stack_;
	std::vector<std::shared_ptr<function>> functions_;

public:
	assembler();

	void assemble(std::string& buffer);
	void assemble(std::vector<std::shared_ptr<function>>& functions);
	auto output_script() -> std::string;
	auto output_stack() -> std::string;

private:
	void assemble_function(std::shared_ptr<function> func);
	void assemble_instruction(std::shared_ptr<instruction> inst);
	void assemble_builtin_call(std::shared_ptr<instruction> inst, bool method, bool arg_num);
	void assemble_local_call(std::shared_ptr<instruction> inst, bool thread);
	void assemble_far_call(std::shared_ptr<instruction> inst, bool thread);
	void assemble_switch(std::shared_ptr<instruction> inst);
	void assemble_end_switch(std::shared_ptr<instruction> inst);
	void assemble_field_variable(std::shared_ptr<instruction> inst);
	void assemble_jump(std::shared_ptr<instruction> inst, bool expr, bool back);
	void assemble_offset(std::int32_t offset);
	auto resolve_function(const std::string& name) -> std::uint32_t;
	auto resolve_label(std::shared_ptr<instruction> inst, const std::string& name) -> std::uint32_t;
};

} // namespace SH1

#endif // _GSC_SH1_ASSEMBLER_H_
