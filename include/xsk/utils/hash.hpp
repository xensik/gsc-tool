// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils::hash
{

constexpr auto fnv1a_64(std::string_view str, u64 start, u64 prime) -> u64
{
    auto h = start;

    for (auto c : str)
    {
        if (c >= 'A' && c <= 'Z')
            h ^= u8('a' + (c - u8('A')));
        else if (c == '\\')
            h ^= '/';
        else
            h ^= u8(c);

        h *= prime;
    }

    return h;
}

constexpr auto scr_dvar_hash(std::string_view str) -> u64
{
    if (str.empty())
        return 0;

    constexpr u64 iv = 0x10000000233ULL;

    switch (str.front())
    {
        case 'a': case 'A': return fnv1a_64(str, 0xE4A68FF7D4912FD2ULL, iv);
        case 'b': case 'B': return fnv1a_64(str, 0x35EC9BBDCBCE1C0EULL, iv);
        case 'c': case 'C': return fnv1a_64(str, 0x0DA27710BE4CE51AULL, iv);
        case 'd': case 'D': return fnv1a_64(str, 0x7238A5E2001AEB8EULL, iv);
        case 'f': case 'F': return fnv1a_64(str, 0xAF25952FD142C84EULL, iv);
        case 'g': case 'G': return fnv1a_64(str, 0xDF9B64790A1B6DB2ULL, iv);
        case 'h': case 'H': return fnv1a_64(str, 0xF74A6B45EC63764EULL, iv);
        case 'l': case 'L': return fnv1a_64(str, 0xBFF2A0737EB2B2BEULL, iv);
        case 'm': case 'M': return fnv1a_64(str, 0xFBE5EB20A0DF848AULL, iv);
        case 'o': case 'O': return fnv1a_64(str, 0xE81A3159054FF1F2ULL, iv);
        case 'p': case 'P': return fnv1a_64(str, 0xA3BF3E5BFC4CB65EULL, iv);
        case 'r': case 'R': return fnv1a_64(str, 0x0251C962D8AB28AEULL, iv);
        case 's': case 'S': return fnv1a_64(str, 0x8913204B4A9FE29AULL, iv);
        case 'u': case 'U': return fnv1a_64(str, 0x5221A5281FDEAC5AULL, iv);
        case 'w': case 'W': return fnv1a_64(str, 0x62C0087A686DCC32ULL, iv);
        case 'x': case 'X': return fnv1a_64(str, 0x220FCCF375CE78EEULL, iv);
        case 'y': case 'Y': return fnv1a_64(str, 0xD368BF96F49C16B2ULL, iv);
        case 'z': case 'Z': return fnv1a_64(str, 0x3070CCD75C99C51EULL, iv);
        default: return 0;
    }
}

} // namespace xsk::utils::hash
