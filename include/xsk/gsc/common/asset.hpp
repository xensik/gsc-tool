// Copyright 2025 xensik. All rights reserved.
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
    u32 compressedLen;
    u32 len;
    u32 bytecodeLen;
    std::vector<u8> buffer;
    std::vector<u8> bytecode;

    auto serialize() -> std::vector<u8>;
    auto deserialize(std::vector<u8> const& data) -> void;
};

} // namespace xsk::gsc
