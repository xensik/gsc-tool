// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::s1_pc
{

constexpr usize code_count = 154;
constexpr usize func_count = 735;
constexpr usize meth_count = 1389;
constexpr usize token_count = 42942;
constexpr u32 max_string_id = 0xA7DC;

struct context : public gsc::context
{
public:
    context(gsc::instance inst);
};

} // namespace xsk::gsc::s1_pc
