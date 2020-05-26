#pragma once

namespace gsc
{
	class function;

	class instruction
	{
	public:
		std::uint32_t m_index;
		std::uint32_t m_size;
		opcode m_opcode;
		std::vector<std::string> m_data;
		std::shared_ptr<function> m_parent;
		instruction();
	};
}
