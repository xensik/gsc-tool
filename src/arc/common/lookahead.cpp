// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/common/lookahead.hpp"

namespace xsk::arc
{

lookahead::lookahead(char const* data, usize size) : position{ 0 }, available{ 0 }, last_byte{ 0 }, curr_byte{ 0 }
{
    if (data && size)
    {
        position = data;
        available = size;
        last_byte = 0;
        curr_byte = *data;
    }
}

auto lookahead::advance() -> void
{
    ++position;

    if (available-- == 1)
    {
        available = 0;
        last_byte = curr_byte;
        curr_byte = 0;
    }
    else
    {
        last_byte = curr_byte;
        curr_byte = *position;
    }
}

} // namespace xsk::arc
