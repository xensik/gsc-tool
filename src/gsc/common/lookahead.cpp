// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/common/lookahead.hpp"

namespace xsk::gsc
{

lookahead::lookahead(char const* data, usize size) : buffer_pos{ 0 }, available{ 0 }, last_byte{ 0 }, curr_byte{ 0 }
{
    if (data && size)
    {
        buffer_pos = data;
        available = size;
        last_byte = 0;
        curr_byte = *data;
    }
}

auto lookahead::advance() -> void
{
    ++buffer_pos;

    if (available-- == 1)
    {
        available = 0;
        last_byte = curr_byte;
        curr_byte = 0;
    }
    else
    {
        last_byte = curr_byte;
        curr_byte = *buffer_pos;
    }
}

} // namespace xsk::gsc
