// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/common/asset.hpp"

namespace xsk::gsc
{

auto asset::serialize() -> std::vector<u8>
{
    auto data = std::vector<u8>{};

    if ((compressed_length != buffer.size() || (compressed_length == 0 && length != buffer.size())) || bytecode_length != bytecode.size())
    {
        throw std::runtime_error("script file serialize error");
    }

    data.resize(name.size() + (compressed_length ? compressed_length : length) + bytecode_length + 13, 0);

    auto pos = usize{ 0 };

    std::memcpy(&data[pos], name.data(), name.size() + 1);
    pos += name.size() + 1;

    *reinterpret_cast<u32*>(&data[pos]) = compressed_length;
    pos += 4;

    *reinterpret_cast<u32*>(&data[pos]) = length;
    pos += 4;

    *reinterpret_cast<u32*>(&data[pos]) = bytecode_length;
    pos += 4;

    std::memcpy(&data[pos], buffer.data(), buffer.size());
    pos += buffer.size();

    std::memcpy(&data[pos], bytecode.data(), bytecode.size());

    return data;
}

auto asset::deserialize(std::vector<std::uint8_t> const& data) -> void
{
    auto pos = usize{ 0 };

    name = std::string{ reinterpret_cast<char const*>(data.data()) };
    pos += name.size() + 1;

    compressed_length = *reinterpret_cast<u32 const*>(data.data() + pos);
    pos += 4;

    length = *reinterpret_cast<u32 const*>(data.data() + pos);
    pos += 4;

    bytecode_length = *reinterpret_cast<u32 const*>(data.data() + pos);
    pos += 4;

    if ((compressed_length + bytecode_length + name.size() + 13) != data.size())
    {
        throw std::runtime_error("script file deserialize error");
    }

    buffer.resize(compressed_length);
    std::memcpy(buffer.data(), data.data() + pos, compressed_length);
    pos += buffer.size();

    bytecode.resize(bytecode_length);
    std::memcpy(bytecode.data(), data.data() + pos, bytecode_length);
}

} // namespace xsk::gsc
