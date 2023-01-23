// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"
#include "location.hpp"
#include "exception.hpp"

namespace xsk::gsc
{

error::error(std::string const& what) : std::runtime_error(fmt::format("[ERROR]: {}", what))
{
}

asm_error::asm_error(std::string const& what) : std::runtime_error(fmt::format("[ERROR]:assembler: {}", what))
{
}

disasm_error::disasm_error(std::string const& what) : std::runtime_error(fmt::format("[ERROR]:disassembler: {}", what))
{
}

comp_error::comp_error(location const& loc, std::string const& what) : std::runtime_error(fmt::format("[ERROR]:compiler:{}: {}", loc.print(), what))
{
}

decomp_error::decomp_error(std::string const& what) : std::runtime_error(fmt::format("[ERROR]:decompiler: {}", what))
{
}

} // namespace xsk::gsc
