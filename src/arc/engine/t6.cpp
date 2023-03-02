// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/arc/engine/t6.hpp"

namespace xsk::arc::t6
{

extern std::array<std::pair<u8, opcode>, code_count> const code_list;
extern std::array<std::pair<u32, char const*>, dvar_count> const dvar_list;

context::context() : arc::context(props::none, engine::t6, endian::little, system::pc, header_magic)
{
    code_map_.reserve(code_list.size());
    code_map_rev_.reserve(code_list.size());
    dvar_map_.reserve(dvar_list.size());

    for (auto const& entry : code_list)
    {
        code_map_.insert({ entry.first, entry.second });
        code_map_rev_.insert({ entry.second, entry.first });
    }

    for (auto const& entry : dvar_list)
    {
        dvar_map_.insert({ entry.first, entry.second });
    }
}

} // namespace xsk::arc::t6
