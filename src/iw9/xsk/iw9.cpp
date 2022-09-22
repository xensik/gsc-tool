// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "iw9.hpp"

namespace xsk::gsc::iw9
{

auto opcode_size(std::uint8_t id) -> std::uint32_t
{
    switch (static_cast<opcode>(id))
    {

        default:
            throw error("couldn't resolve instruction size for " + std::to_string(id));
    }
}

} // namespace xsk::gsc::iw9
