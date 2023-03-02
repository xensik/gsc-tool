// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/gsc/engine/iw8.hpp"

namespace xsk::gsc::iw8
{

extern std::array<std::pair<u8, opcode>, code_count> const code_list;
extern std::array<std::pair<u16, char const*>, func_count> const func_list;
extern std::array<std::pair<u16, char const*>, meth_count> const meth_list;
extern std::array<std::pair<u32, char const*>, token_count> const token_list;

context::context() : gsc::context(props::str4 | props::tok4 | props::waitframe | props::params | props::boolfuncs | props::boolnotand | props::offs8,
    engine::iw8, endian::little, system::pc, max_string_id)
{
    code_map_.reserve(code_list.size());
    code_map_rev_.reserve(code_list.size());
    func_map_.reserve(func_list.size());
    func_map_rev_.reserve(func_list.size());
    meth_map_.reserve(meth_list.size());
    meth_map_rev_.reserve(meth_list.size());
    token_map_.reserve(token_list.size());
    token_map_rev_.reserve(token_list.size());

    for (auto const& entry : code_list)
    {
        code_map_.insert({ entry.first, entry.second });
        code_map_rev_.insert({ entry.second, entry.first });
    }

    for (auto const& entry : func_list)
    {
        func_map_.insert({ entry.first, entry.second });
        func_map_rev_.insert({ entry.second, entry.first });
    }

    for (auto const& entry : meth_list)
    {
        meth_map_.insert({ entry.first, entry.second });
        meth_map_rev_.insert({ entry.second, entry.first });
    }

    for (auto const& entry : token_list)
    {
        token_map_.insert({ entry.first, entry.second });
        token_map_rev_.insert({ entry.second, entry.first });
    }
}

} // namespace xsk::gsc::iw8
