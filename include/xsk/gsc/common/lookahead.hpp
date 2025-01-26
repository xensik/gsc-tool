// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct lookahead
{
    char const* buffer_pos;
    usize available;
    char last_byte;
    char curr_byte;

    lookahead(char const* data, usize size);
    auto advance() -> void;
    auto ended() const { return available == 0; };
};

} // namespace xsk::gsc
