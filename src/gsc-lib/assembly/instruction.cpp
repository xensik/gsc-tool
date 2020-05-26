#include "stdinc.hpp"

namespace gsc
{
	instruction::instruction() : m_index(0), m_opcode(opcode::OP_Count), m_size(0)
	{
	}
}