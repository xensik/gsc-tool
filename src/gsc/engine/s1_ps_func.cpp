// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/gsc/engine/s1_ps.hpp"

namespace xsk::gsc::s1_ps
{

extern std::array<std::pair<u16, char const*>, func_count> const func_list
{{
    { 0x12, "isdefined" },
    { 0xC0, "getfirstarraykey" },
    { 0xC1, "getnextarraykey" },
}};

} // namespace xsk::gsc::s1_ps
