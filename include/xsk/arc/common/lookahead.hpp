// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

struct lookahead
{
    char const* position{ nullptr };
    usize available{ 0 };
    char last_byte{ 0 };
    char curr_byte{ 0 };

    lookahead(char const* data, usize size);
    // one call per source character: defined here so it inlines without LTO
    auto advance() -> void
    {
        ++position;
        last_byte = curr_byte;

        // the available == 0 arm matters: advancing a spent reader used to wrap the
        // counter around, so ended() never fired again and the loop read past the end
        if (available == 0 || --available == 0) [[unlikely]]
        {
            available = 0;
            curr_byte = 0;
        }
        else
        {
            curr_byte = *position;
        }
    }
    auto ended() const { return available == 0; };
};

} // namespace xsk::arc
