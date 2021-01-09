// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_PAIR_HPP_
#define _GSC_PAIR_HPP_

namespace gsc
{

struct pair_8_str
{
    std::uint8_t key;
    const char* value;
};

struct pair_16_str
{
    std::uint16_t key;
    const char* value;
};

struct pair_32_str
{
    std::uint32_t key;
    const char* value;
};

} // namespace gsc

#endif // _GSC_PAIR_HPP_
