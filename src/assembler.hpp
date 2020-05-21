#pragma once
#include "common.hpp"

_GSC_BEGIN

class assembler
{
public:
	assembler();
	void assemble(std::string& buffer);
	std::vector<std::uint8_t> output_script();
	std::vector<std::uint8_t> output_stack();

private:
	std::unique_ptr<byte_buffer> m_script;
	std::unique_ptr<byte_buffer> m_stack;
	std::vector<std::shared_ptr<function>> m_functions;
	std::unordered_map<std::uint32_t, std::string> m_labels;

	void assemble_function(std::shared_ptr<function> func);
	void assemble_instruction(std::shared_ptr<instruction> inst);
	void assemble_builtin_call(std::shared_ptr<instruction> inst, bool method, bool arg_num);
	void assemble_local_call(std::shared_ptr<instruction> inst, bool thread);
	void assemble_far_call(std::shared_ptr<instruction> inst, bool thread);
	void assemble_end_switch(std::shared_ptr<instruction> inst);
	void assemble_field_variable(std::shared_ptr<instruction> inst);
	void assemble_jump(std::shared_ptr<instruction> inst, bool expr, bool back);
	void assemble_offset(std::int32_t offset);
	std::uint32_t resolve_function(const std::string& name);
	std::uint32_t resolve_label(const std::string& name);
};

_GSC_END
