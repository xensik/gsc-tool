#pragma once

_GSC_BEGIN

class function;

class instruction
{
public:
	std::uint32_t m_index;
	std::uint32_t m_size;
	std::uint8_t m_opcode;
	std::vector<std::string> m_data;
	std::shared_ptr<function> m_parent;
	instruction();
};

class function
{
public:
	std::uint32_t m_index;
	std::uint32_t m_size;
	std::uint16_t m_id;
	std::string m_name;
	std::vector<std::shared_ptr<instruction>> m_instructions;
	std::unordered_map<std::uint32_t, std::string> m_labels;

	function();
};

_GSC_END
