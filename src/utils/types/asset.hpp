// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_ASSET_HPP_
#define _GSC_ASSET_HPP_

namespace gsc
{

struct asset
{
    std::string name;
    std::uint32_t compressedLen;
    std::uint32_t len;
    std::uint32_t bytecodeLen;
    std::vector<std::uint8_t> buffer;
    std::vector<std::uint8_t> bytecode;

    auto serialize() -> std::vector<std::uint8_t>
    {
        std::vector<std::uint8_t> data;

        data.resize(name.size() + 1 + compressedLen + bytecodeLen + 12);
        std::memset(data.data(), 0, data.size());

        auto pos = 0u;
        
        std::memcpy(&data[pos], name.data(), name.size() + 1);
        pos += name.size() + 1;

        *reinterpret_cast<std::uint32_t*>(&data[pos]) = compressedLen;
        pos += 4;

        *reinterpret_cast<std::uint32_t*>(&data[pos]) = len;
        pos += 4;

        *reinterpret_cast<std::uint32_t*>(&data[pos]) = bytecodeLen;
        pos += 4;

        std::memcpy(&data[pos], buffer.data(), buffer.size());
        pos += buffer.size();

        std::memcpy(&data[pos], bytecode.data(), bytecode.size());

        return data;
    }

    auto deserialize(std::vector<std::uint8_t> data)
    {
        auto pos = 0u;

        name = std::string(reinterpret_cast<const char*>(data.data()));
        pos += name.size() + 1;

        compressedLen = *reinterpret_cast<std::uint32_t*>(data.data() + pos);
        pos += 4;

        len = *reinterpret_cast<std::uint32_t*>(data.data() + pos);
        pos += 4;

        bytecodeLen = *reinterpret_cast<std::uint32_t*>(data.data() + pos);
        pos += 4;

        buffer.resize(compressedLen);
        std::memcpy(buffer.data(), data.data() + pos, compressedLen);
        pos += buffer.size();

        bytecode.resize(bytecodeLen);
        std::memcpy(bytecode.data(), data.data() + pos, bytecodeLen);
    }
};

using asset_ptr = std::unique_ptr<asset>;

} // namespace gsc

#endif // _GSC_ASSET_HPP_
