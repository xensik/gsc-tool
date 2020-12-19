// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "S1.hpp"

namespace S1
{

auto decompiler::output() -> std::vector<std::uint8_t>
{
	std::vector<std::uint8_t> output;

	return output;
}

void decompiler::decompile(std::vector<gsc::function_ptr>& functions)
{
	LOG_ERROR("S1 decompiler not implemented!");
}

} // namespace S1
