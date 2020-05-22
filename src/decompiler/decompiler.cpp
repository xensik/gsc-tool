#include "stdinc.hpp"
#include "decompiler.hpp"

_GSC_BEGIN

void decompiler::decompile(std::vector<std::shared_ptr<function>>& functions)
{
	m_functions = functions;
}

std::vector<std::uint8_t> decompiler::output()
{
	return std::vector<std::uint8_t>();
}

_GSC_END
