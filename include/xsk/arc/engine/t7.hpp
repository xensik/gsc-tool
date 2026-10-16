// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc::t7
{

constexpr usize code_count = 16384;
constexpr usize code_count_1b = 105;
constexpr usize hash_count = 197859;
constexpr u64 header_magic = 0x1C000A0D43534780;
constexpr u64 header_magic_1b = 0x1B000A0D43534780;

// The game ships two bytecode versions side by side. 0x1B is the older one: the same
// instruction set behind one byte opcodes, where 0x1C scrambles them over two.
enum class version : u8
{
    v1b,
    v1c,
};

struct context : public arc::context
{
public:
    explicit context(arc::instance inst, version ver = version::v1c);
};

} // namespace xsk::arc::t7
