// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/arc/engine/t7.hpp"

namespace xsk::arc::t7
{

extern std::array<std::pair<u16, opcode>, code_count> const code_list;
extern std::array<std::pair<u16, opcode>, code_count_1b> const code_list_1b;
extern std::array<std::pair<u32, char const*>, hash_count> const hash_list;

context::context(arc::instance inst, version ver) : arc::context(feature::header72 | feature::size64 | feature::hashids | feature::devstr | feature::spaces | feature::refvarg | feature::foreach | (ver == version::v1c ? feature::code16 : feature::none), engine::t7, endian::little, system::pc64, inst, ver == version::v1c ? header_magic : header_magic_1b)
{
    auto const fill = [this](auto const& list) {
        code_map_.reserve(list.size());
        code_map_rev_.reserve(list.size());

        for (auto const& entry : list)
        {
            code_map_.insert({ entry.first, entry.second });
            code_map_rev_.insert({ entry.second, entry.first });
        }
    };

    if (ver == version::v1c)
        fill(code_list);
    else
        fill(code_list_1b);

    hash_map_.reserve(hash_list.size());

    for (auto const& entry : hash_list)
    {
        hash_map_.insert({ entry.first, entry.second });
    }

    // ponytail: msvc (19.44) emits "spinpropkey" as "ghostindemo" when both literals
    // share a translation unit (#260), so this one lives outside t7_hash.cpp. Upgrade
    // path if more collisions turn up: store the names as one blob plus offsets.
    hash_map_.insert({ 0xA5236ECF, "spinpropkey" });
}

} // namespace xsk::arc::t7
