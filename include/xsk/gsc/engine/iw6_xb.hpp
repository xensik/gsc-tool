// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::iw6_xb
{

constexpr usize code_count = 153;
constexpr usize func_count = 591;
constexpr usize meth_count = 1066;
constexpr usize token_count = 36604;
constexpr u32 max_string_id = 0x95A1;

struct context : public gsc::context
{
public:
    explicit context(gsc::instance inst);
};

} // namespace xsk::gsc::iw6_xb
