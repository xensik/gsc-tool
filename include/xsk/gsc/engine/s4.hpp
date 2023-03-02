// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::s4
{

constexpr usize code_count = 190;
constexpr usize func_count = 4;
constexpr usize meth_count = 0;
constexpr usize token_count = 0;
constexpr u32 max_string_id = 0x110F3;

class context : public gsc::context
{
public:
    context();
};

} // namespace xsk::gsc::s4
