// Copyright 2026 xensik. All rights reserved.
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

auto zlib::decompress(std::vector<u8> const& data, const u32 length) -> std::vector<u8>
{
    constexpr auto chunk_size = usize{ 64 * 1024 };
    constexpr auto max_output_size = usize{ 256 * 1024 * 1024 };

    if (length > max_output_size || data.size() > std::numeric_limits<uInt>::max())
        throw error("zlib decompress error: size limit exceeded");

    auto stream = z_stream{};
    stream.next_in = const_cast<Bytef*>(reinterpret_cast<Bytef const*>(data.data()));
    stream.avail_in = static_cast<uInt>(data.size());

    auto result = inflateInit(&stream);
    if (result != Z_OK)
        throw error(std::format("zlib decompress init error {}", result));

    auto output = std::vector<u8>{};
    output.reserve(std::min<usize>(length, chunk_size));
    auto chunk = std::array<u8, chunk_size>{};

    while (true)
    {
        stream.next_out = reinterpret_cast<Bytef*>(chunk.data());
        stream.avail_out = static_cast<uInt>(chunk.size());
        result = inflate(&stream, Z_NO_FLUSH);

        auto const produced = chunk.size() - stream.avail_out;
        if (produced > static_cast<usize>(length) - output.size())
        {
            inflateEnd(&stream);
            throw error("zlib decompress error: output exceeds expected length");
        }

        output.insert(output.end(), chunk.begin(), chunk.begin() + produced);

        if (result == Z_STREAM_END)
            break;

        if (result != Z_OK || (produced == 0 && stream.avail_in == 0))
        {
            inflateEnd(&stream);
            throw error(std::format("zlib decompress error {}", result));
        }
    }

    inflateEnd(&stream);

    if (output.size() != length)
        throw error("zlib decompress error: output length mismatch");

    return output;
}

} // namespace xsk::utils
