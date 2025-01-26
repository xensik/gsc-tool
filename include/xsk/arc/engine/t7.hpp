// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc::t7
{

constexpr usize code_count = 16384;
constexpr usize hash_count = 178806;
constexpr u64 header_magic = 0x1C000A0D43534780;

struct context : public arc::context
{
public:
    context(arc::instance inst);
};

} // namespace xsk::arc::t7
