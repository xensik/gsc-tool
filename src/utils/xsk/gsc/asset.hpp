// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct asset
{
    using ptr = std::unique_ptr<asset>;

    std::string name;
    std::uint32_t compressedLen;
    std::uint32_t len;
    std::uint32_t bytecodeLen;
    std::vector<std::uint8_t> buffer;
    std::vector<std::uint8_t> bytecode;

    auto serialize() -> std::vector<std::uint8_t>;
    void deserialize(std::vector<std::uint8_t> data);
};

} // namespace xsk::gsc
