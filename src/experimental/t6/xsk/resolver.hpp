// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::t6
{

class resolver
{
public:
    static auto opcode_id(const std::string& name) -> std::uint8_t;
    static auto opcode_name(std::uint8_t id) -> std::string;
};

} // namespace xsk::gsc::t6
