// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

class file
{
public:
    static auto read(const std::string& file) -> std::vector<std::uint8_t>;
    static void save(const std::string& file, const std::vector<std::uint8_t>& data);
    static auto length(const std::string& file) -> size_t;
    static auto exists(const std::string& file) -> bool;
};

} // namespace xsk::utils
