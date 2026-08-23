// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/common/lookahead.hpp"

namespace xsk::arc
{

lookahead::lookahead(char const* data, usize size)
{
    if (data && size)
    {
        position = data;
        available = size;
        last_byte = 0;
        curr_byte = *data;
    }
}

} // namespace xsk::arc
