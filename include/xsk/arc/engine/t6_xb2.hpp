// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/arc/engine/t6.hpp"

namespace xsk::arc::t6::xb2
{

constexpr u64 header_magic = 0x804753430D0A0006;

class context : public arc::context
{
public:
    context();
};

} // namespace xsk::arc::t6::xb2
