#pragma once
#include "disassembler/disassembler.hpp"

_GSC_BEGIN

class decompiler
{
public:
	void decompile(std::vector<std::shared_ptr<function>>& functions);
	std::vector<std::uint8_t> output();

private:
	std::vector<std::shared_ptr<function>> m_functions;
};

_GSC_END
