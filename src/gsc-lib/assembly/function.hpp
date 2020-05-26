#pragma once

namespace gsc
{
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
}
