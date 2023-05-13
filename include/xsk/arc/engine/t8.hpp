// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc::t8
{

constexpr usize code_count = 0;
constexpr usize hash_count = 0;
constexpr u64 header_magic = 0x36000A0D43534780;

class context : public arc::context
{
public:
    context();
};

} // namespace xsk::arc::t8
