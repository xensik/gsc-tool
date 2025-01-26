// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::iw9
{

constexpr usize code_count = 167;
constexpr usize func_count = 905;
constexpr usize meth_count = 1469;
constexpr usize path_count = 1467;
constexpr usize hash_count = 73500;

struct context : public gsc::context
{
public:
    context(gsc::instance inst);
};

} // namespace xsk::gsc::iw9
