// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/common/asset.hpp"

namespace xsk::gsc
{

auto asset::serialize() const -> std::vector<u8>
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

    std::memcpy(data.data() + pos, &compressed_length, sizeof(compressed_length));
    pos += 4;

    std::memcpy(data.data() + pos, &length, sizeof(length));
    pos += 4;

    std::memcpy(data.data() + pos, &bytecode_length, sizeof(bytecode_length));
    pos += 4;

    std::memcpy(&data[pos], buffer.data(), buffer.size());
    pos += buffer.size();

    std::memcpy(&data[pos], bytecode.data(), bytecode.size());

    return data;
}

auto asset::deserialize(std::vector<std::uint8_t> const& data) -> void
{
    constexpr auto metadata_size = usize{ 12 };

    if (data.size() < metadata_size + 1)
    {
        throw std::runtime_error("script file deserialize error");
    }

    auto pos = usize{ 0 };

    auto const terminator = std::find(data.begin(), data.end(), u8{ 0 });

    if (terminator == data.end() || static_cast<usize>(std::distance(data.begin(), terminator)) > data.size() - metadata_size - 1)
    {
        throw std::runtime_error("script file deserialize error");
    }

    name.assign(reinterpret_cast<char const*>(data.data()), static_cast<usize>(std::distance(data.begin(), terminator)));
    pos += name.size() + 1;

    std::memcpy(&compressed_length, data.data() + pos, sizeof(compressed_length));
    pos += 4;

    std::memcpy(&length, data.data() + pos, sizeof(length));
    pos += 4;

    std::memcpy(&bytecode_length, data.data() + pos, sizeof(bytecode_length));
    pos += 4;

    auto const payload_size = data.size() - pos;

    if (compressed_length > payload_size || bytecode_length != payload_size - compressed_length)
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
