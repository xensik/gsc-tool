// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/zlib.hpp"
#include "zlib.h"

namespace xsk::utils
{

auto zlib::compress(std::vector<u8> const& data) -> std::vector<u8>
{
    auto length = compressBound(static_cast<uLong>(data.size()));

    auto output = std::vector<u8>{};
    output.resize(length);

    auto result = compress2(reinterpret_cast<Bytef*>(output.data()), &length, reinterpret_cast<const Bytef*>(data.data()), static_cast<uLong>(data.size()), Z_BEST_COMPRESSION);

    if (result == Z_OK)
    {
        output.resize(length);
        return output;
    }

    throw error(std::format("zlib compress error {}", result));
}

auto zlib::decompress(std::vector<u8> const& data, u32 length) -> std::vector<u8>
{
    auto output = std::vector<u8>{};
    output.resize(length);

    auto result = uncompress(reinterpret_cast<Bytef*>(output.data()), reinterpret_cast<uLongf*>(&length), reinterpret_cast<const Bytef*>(data.data()), static_cast<uLong>(data.size()));

    if (result == Z_OK)
        return output;

    throw error(std::format("zlib decompress error {}", result));
}

} // namespace xsk::uitls
