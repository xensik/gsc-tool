// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "SH1.hpp"

namespace SH1
{

auto compiler::output() -> std::vector<gsc::function_ptr>
{
    return std::vector<gsc::function_ptr>();
}

void compiler::compile(std::vector<std::uint8_t>& data)
{
    LOG_ERROR("SH1 compiler not implemented!");
}

} // namespace SH1
