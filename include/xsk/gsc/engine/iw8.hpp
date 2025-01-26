// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::iw8
{

constexpr usize code_count = 190;
constexpr usize func_count = 1065;
constexpr usize meth_count = 2032;
constexpr usize token_count = 72014;
constexpr u32 max_string_id = 0x1472F;

struct context : public gsc::context
{
public:
    context(gsc::instance inst);
};

} // namespace xsk::gsc::iw8
