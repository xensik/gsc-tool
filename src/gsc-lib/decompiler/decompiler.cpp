#include "stdinc.hpp"
#include "decompiler.hpp"

namespace gsc
{
	void decompiler::decompile(std::vector<std::shared_ptr<function>>& functions)
	{
		m_functions = functions;
	}

	auto decompiler::output() -> std::vector<std::uint8_t>
	{
		return std::vector<std::uint8_t>();
	}
}
