// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/common/location.hpp"
#include "xsk/arc/common/exception.hpp"

namespace xsk::arc
{

error::error(std::string const& what) : std::runtime_error(std::format("[ERROR]: {}", what))
{
}

asm_error::asm_error(std::string const& what) : std::runtime_error(std::format("[ERROR]:assembler: {}", what))
{
}

disasm_error::disasm_error(std::string const& what) : std::runtime_error(std::format("[ERROR]:disassembler: {}", what))
{
}

ppr_error::ppr_error(location const& loc, std::string const& what) : std::runtime_error(std::format("[ERROR]:preprocessor:{}: {}", loc.print(), what))
{
}

comp_error::comp_error(location const& loc, std::string const& what) : std::runtime_error(std::format("[ERROR]:compiler:{}: {}", loc.print(), what))
{
}

decomp_error::decomp_error(std::string const& what) : std::runtime_error(std::format("[ERROR]:decompiler: {}", what))
{
}

} // namespace xsk::arc
