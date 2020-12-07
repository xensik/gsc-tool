// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "utils.hpp"
#include <zlib.h>

namespace utils
{

auto zlib::compress(const std::vector<std::uint8_t>& data) -> std::vector<std::uint8_t>
{
    auto length = compressBound(static_cast<uLong>(data.size()));

    std::vector<std::uint8_t> output;
    output.resize(length);

    auto result = compress2(reinterpret_cast<Bytef*>(output.data()), &length, reinterpret_cast<const Bytef*>(data.data()), static_cast<uLong>(data.size()), Z_BEST_COMPRESSION);
    
    if(result != Z_OK) return {};

    output.resize(length);
    
    return output;
}

auto zlib::decompress(const std::vector<std::uint8_t>& data, std::uint32_t length) -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> output;
    output.resize(length);

    auto result = uncompress(output.data(), (uLongf*)&length, (Bytef*)data.data(), data.size());

    if(result != Z_OK) return {};

    return output;
}

} // namespace uitls
