#pragma once

namespace gsc
{
	class disassembler
	{
	public:
		disassembler(bool ida_output);

		void disassemble(std::shared_ptr<byte_buffer> script, std::shared_ptr<byte_buffer> stack);
		auto output() -> std::vector<std::shared_ptr<function>>;
		auto output_buffer() -> std::vector<std::uint8_t>;

	private:
		std::shared_ptr<byte_buffer> m_script;
		std::shared_ptr<byte_buffer> m_stack;
		std::unique_ptr<byte_buffer> m_output;
		std::vector<std::shared_ptr<function>> m_functions;
		bool m_ida_output;

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
		auto resolve_function(const std::string& index) -> std::string;
		void print_script_name(const std::string& name);
		void print_opcodes(std::uint32_t index, std::uint32_t size);
		void print_function(std::shared_ptr<function> func);
		void print_instruction(std::shared_ptr<instruction> inst);
		void print_label(const std::string& label);
	};
}
