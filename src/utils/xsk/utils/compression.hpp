// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

class zlib
{
public:
    static auto compress(const std::vector<std::uint8_t>& data) -> std::vector<std::uint8_t>;
    static auto decompress(const std::vector<std::uint8_t>& data, std::uint32_t length) -> std::vector<std::uint8_t>;
};

} // namespace xsk::utils
