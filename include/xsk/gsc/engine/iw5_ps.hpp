// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::iw5_ps
{
// IW5 PS
constexpr usize code_count = 153;
constexpr usize func_count = 452;
constexpr usize meth_count = 777;
constexpr usize token_count = 14221;
constexpr u32 max_string_id = 33360;

struct context : public gsc::context
{
public:
    context(gsc::instance inst);
};

} // namespace xsk::gsc::iw5_ps
