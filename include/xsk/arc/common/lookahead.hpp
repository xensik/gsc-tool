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
    auto advance() -> void;
    auto ended() const { return available == 0; };
};

} // namespace xsk::arc
