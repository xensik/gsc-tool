// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct pair_8C
{
    std::uint8_t key;
    const char* value;
};

struct pair_16C
{
    std::uint16_t key;
    const char* value;
};

struct pair_32C
{
    std::uint32_t key;
    const char* value;
};

} // namespace xsk::gsc
