// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "S2.hpp"

namespace S2
{

auto opcode_size(opcode id) -> std::uint32_t
{
    switch (id)
    {
    default:
        LOG_ERROR("Couldn't resolve instruction size for 0x%hhX!", id);
        return 0;
    }
}

} // namespace S2
