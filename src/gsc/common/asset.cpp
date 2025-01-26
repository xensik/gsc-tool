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

    if ((compressedLen != buffer.size() || (compressedLen == 0 && len != buffer.size())) || bytecodeLen != bytecode.size())
    {
        throw std::runtime_error("script file serialize error");
    }

    data.resize(name.size() + (compressedLen ? compressedLen : len) + bytecodeLen + 13, 0);

    auto pos = usize{ 0 };

    std::memcpy(&data[pos], name.data(), name.size() + 1);
    pos += name.size() + 1;

    *reinterpret_cast<u32*>(&data[pos]) = compressedLen;
    pos += 4;

    *reinterpret_cast<u32*>(&data[pos]) = len;
    pos += 4;

    *reinterpret_cast<u32*>(&data[pos]) = bytecodeLen;
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

    compressedLen = *reinterpret_cast<u32 const*>(data.data() + pos);
    pos += 4;

    len = *reinterpret_cast<u32 const*>(data.data() + pos);
    pos += 4;

    bytecodeLen = *reinterpret_cast<u32 const*>(data.data() + pos);
    pos += 4;

    if ((compressedLen + bytecodeLen + name.size() + 13) != data.size())
    {
        throw std::runtime_error("script file deserialize error");
    }

    buffer.resize(compressedLen);
    std::memcpy(buffer.data(), data.data() + pos, compressedLen);
    pos += buffer.size();

    bytecode.resize(bytecodeLen);
    std::memcpy(bytecode.data(), data.data() + pos, bytecodeLen);
}

} // namespace xsk::gsc
