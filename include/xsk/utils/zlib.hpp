// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

struct zlib
{
    using error = std::runtime_error;

    static auto compress(std::vector<u8> const& data) -> std::vector<u8>;
    static auto decompress(std::vector<u8> const& data, u32 length) -> std::vector<u8>;
};

} // namespace xsk::utils
