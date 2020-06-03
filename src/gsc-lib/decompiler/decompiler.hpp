#pragma once

namespace gsc
{
	class decompiler_function
	{
	public:
		std::string name_;
		std::size_t params_;
		std::vector<std::string> local_vars_;

		std::unordered_map<std::uint32_t, std::string> labels_;
		std::vector<std::shared_ptr<instruction>> instructions_;
	};

	class decompiler
	{
	public:
		decompiler();
		void decompile(std::vector<std::shared_ptr<function>>& functions);
		auto output() -> std::vector<std::uint8_t>;

	private:
		std::unique_ptr<byte_buffer> output_;
		std::vector<std::shared_ptr<decompiler_function>> functions_;

		void decompile_function(std::shared_ptr<decompiler_function> func);


		void print_function(std::shared_ptr<decompiler_function> func);
		void print_instruction(std::shared_ptr<instruction> inst);
		void print_label(const std::string& label);
	};
}
