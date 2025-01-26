// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/gsc/engine/iw6_xb.hpp"

namespace xsk::gsc::iw6_xb
{

extern std::array<std::pair<u16, char const*>, func_count> const func_list
{{
    { 0x12, "isdefined" },
    { 0xB7, "getfirstarraykey" },
    { 0xB8, "getnextarraykey" },
}};

} // namespace xsk::gsc::iw6_xb
