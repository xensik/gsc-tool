// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::h2
{
// H2 PC 1.0.1280159
constexpr usize code_count = 154;
constexpr usize func_count = 800;
constexpr usize meth_count = 1491;
constexpr usize token_count = 42524;
constexpr u32 max_string_id = 54743;

struct context : public gsc::context
{
public:
    context(gsc::instance inst);
};

} // namespace xsk::gsc::h2
