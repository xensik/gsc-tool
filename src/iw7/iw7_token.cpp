// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "iw7.hpp"

namespace xsk::gsc::iw7
{

extern std::array<std::pair<u32, char const*>, token_count> const token_list
{{
    { 0x0000, "" },
    { 0x0001, "pl#" },
    { 0x0002, "-" },
    { 0x0003, "radius`" },
    { 0x0004, "note:" },
}};

} // namespace xsk::gsc::iw7
