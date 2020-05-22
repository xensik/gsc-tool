#include "stdinc.hpp"
#include "common.hpp"

_GSC_BEGIN

instruction::instruction() : m_index(0), m_opcode(0), m_size(0)
{
}

function::function() : m_index(0), m_name(""), m_size(0), m_id(0)
{
}

_GSC_END
