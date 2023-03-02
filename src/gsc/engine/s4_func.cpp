// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/gsc/engine/s4.hpp"

namespace xsk::gsc::s4
{

extern std::array<std::pair<u16, char const*>, func_count> const func_list
{{
    { 0x08F, "getdvar" },
    { 0x09B, "getfirstarraykey" },
    { 0x0B1, "getnextarraykey" },
    { 0x126, "isusingmatchrulesdata" },
}};

} // namespace xsk::gsc::s4
