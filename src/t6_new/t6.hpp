// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "stdinc.hpp"
#include "arc/context.hpp"

namespace xsk::arc::t6
{

constexpr usize code_count = 125;
constexpr usize dvar_count = 3326;
constexpr u64 header_magic = 0x06000A0D43534780;

class context : public arc::context
{
public:
    context();
};

} // namespace xsk::gsc::t6
