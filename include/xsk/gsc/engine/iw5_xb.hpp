// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::iw5_xb
{
// IW5 XB 1.8.388110
constexpr usize code_count = 153;
constexpr usize func_count = 455;
constexpr usize meth_count = 779;
constexpr usize token_count = 14221;
constexpr u32 max_string_id = 33386;

struct context : public gsc::context
{
public:
    context(gsc::instance inst);
};

} // namespace xsk::gsc::iw5_xb
