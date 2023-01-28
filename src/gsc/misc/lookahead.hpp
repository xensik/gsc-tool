// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct lookahead
{
    enum state_type : u8 { end, ok };

    char const* buffer_pos;
    usize available;
    char last_byte;
    char curr_byte;
    state_type state;

    lookahead(char const* data, usize size);
    auto advance() -> void;
    auto ended() { return state == end; };
};

} // namespace xsk::gsc
