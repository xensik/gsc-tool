// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "SH1.hpp"

namespace SH1
{

auto decompiler::output() -> std::vector<std::uint8_t>
{
	std::vector<std::uint8_t> output;

	return output;
}

void decompiler::decompile(std::vector<gsc::function_ptr>& functions)
{
	LOG_ERROR("SH1 decompiler not implemented!");
}

} // namespace SH1
