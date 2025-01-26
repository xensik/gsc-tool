// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/gsc/engine/s2.hpp"

namespace xsk::gsc::s2
{

extern std::array<std::pair<u32, char const*>, token_count> const token_list
{{
    { 0x00, "" },
    { 0x01, "pl#" },
    { 0x02, "-" },
    { 0x03, "radius`" },
    { 0x04, "note:" },
}};

} // namespace xsk::gsc::s2
