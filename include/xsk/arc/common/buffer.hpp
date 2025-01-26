// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

struct buffer
{
    u8 const* data;
    usize const size;

    buffer() : data{ nullptr }, size{ 0 } {}
    buffer(u8 const* data, usize size) : data{ data }, size{ size } {}
};

} // namespace xsk::arc
