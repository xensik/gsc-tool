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
        case 'a': case 'A': return fnv1a_64(str, 0xFC9B930CF7416D64ULL, iv);
        case 'b': case 'B': return fnv1a_64(str, 0x9A88BEE10E2FB71CULL, iv);
        case 'c': case 'C': return fnv1a_64(str, 0x193B2D4166F1E474ULL, iv);
        case 'd': case 'D': return fnv1a_64(str, 0x90BBD97D817C3BB4ULL, iv);
        case 'e': case 'E': return fnv1a_64(str, 0x4BF68A19BDA2F7BCULL, iv);
        case 'f': case 'F': return fnv1a_64(str, 0x220E8473FBFE04E4ULL, iv);
        case 'g': case 'G': return fnv1a_64(str, 0x85B013A4E70EDCACULL, iv);
        case 'h': case 'H': return fnv1a_64(str, 0x35359AD030F0CECCULL, iv);
        case 'i': case 'I': return fnv1a_64(str, 0xB742F8B10AE9E1F4ULL, iv);
        case 'j': case 'J': return fnv1a_64(str, 0x629C7AB30DDD511CULL, iv);
        case 'k': case 'K': return fnv1a_64(str, 0x7B50CE4016A19064ULL, iv);
        case 'l': case 'L': return fnv1a_64(str, 0x827CCF83792891C4ULL, iv);
        case 'm': case 'M': return fnv1a_64(str, 0xBDDB2ACB28358A7CULL, iv);
        case 'n': case 'N': return fnv1a_64(str, 0x772E559AE9E22494ULL, iv);
        case 'o': case 'O': return fnv1a_64(str, 0x0F579F12D8AF33CCULL, iv);
        case 'p': case 'P': return fnv1a_64(str, 0x4EFF8082D8DFCB2CULL, iv);
        case 'r': case 'R': return fnv1a_64(str, 0x68E7F378CBD4275CULL, iv);
        case 's': case 'S': return fnv1a_64(str, 0x9EACF1B19DED9334ULL, iv);
        case 't': case 'T': return fnv1a_64(str, 0xBD0C7686C08A04F4ULL, iv);
        case 'u': case 'U': return fnv1a_64(str, 0x5219561CA516433CULL, iv);
        case 'v': case 'V': return fnv1a_64(str, 0xBC6AD2D970767A44ULL, iv);
        case 'w': case 'W': return fnv1a_64(str, 0x8355B5EA1EC0C1CCULL, iv);
        case 'x': case 'X': return fnv1a_64(str, 0xF2C1E13850ECCEACULL, iv);
        default: return 0;
    }
}

} // namespace xsk::utils::hash
