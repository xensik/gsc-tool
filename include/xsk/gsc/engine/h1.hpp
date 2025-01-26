// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::h1
{
// H1 PC 1.15.1251288
constexpr usize code_count = 154;
constexpr usize func_count = 778;
constexpr usize meth_count = 1415;
constexpr usize token_count = 42947;
constexpr u32 max_string_id = 42989;

struct context : public gsc::context
{
public:
    context(gsc::instance inst);
};

} // namespace xsk::gsc::h1
