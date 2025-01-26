// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/arc/engine/t9.hpp"

namespace xsk::arc::t9
{

extern std::array<std::pair<u16, opcode>, code_count> const code_list;
// extern std::array<std::pair<u32, char const*>, hash_count> const hash_list;

context::context(arc::instance inst) : arc::context(props::v3, engine::t9, endian::little, system::pc, inst, header_magic)
{
    code_map_.reserve(code_list.size());
    code_map_rev_.reserve(code_list.size());
    // hash_map_.reserve(hash_list.size());

    for (auto const& entry : code_list)
    {
        code_map_.insert({ entry.first, entry.second });
        code_map_rev_.insert({ entry.second, entry.first });
    }

    // for (auto const& entry : hash_list)
    // {
    //     hash_map_.insert({ entry.first, entry.second });
    // }
}

} // namespace xsk::arc::t9
