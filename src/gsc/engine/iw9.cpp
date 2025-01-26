// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/gsc/engine/iw9.hpp"

namespace xsk::gsc::iw9
{

extern std::array<std::pair<u8, opcode>, code_count> const code_list;
extern std::array<std::pair<u64, char const*>, func_count> const func_list;
extern std::array<std::pair<u64, char const*>, meth_count> const meth_list;
extern std::array<std::pair<u64, char const*>, path_count> const path_list;
extern std::array<std::pair<u64, char const*>, hash_count> const hash_list;

context::context(gsc::instance inst) : gsc::context(props::str4| props::waitframe | props::params | props::boolfuncs | props::boolnotand | props::hash | props::farcall | props::foreach,
    engine::iw9, endian::little, system::pc, inst, 0)
{
    code_map_.reserve(code_list.size());
    code_map_rev_.reserve(code_list.size());
    func_map2_.reserve(func_list.size());
    meth_map2_.reserve(meth_list.size());
    path_map_.reserve(path_list.size());
    hash_map_.reserve(hash_list.size());

    for (auto const& entry : code_list)
    {
        code_map_.insert({ entry.first, entry.second });
        code_map_rev_.insert({ entry.second, entry.first });
    }

    for (auto const& entry : func_list)
    {
        func_map2_.insert({ entry.first, entry.second });
    }

    for (auto const& entry : meth_list)
    {
        meth_map2_.insert({ entry.first, entry.second });
    }

    for (auto const& entry : path_list)
    {
        path_map_.insert({ entry.first, entry.second });
    }

    for (auto const& entry : hash_list)
    {
        hash_map_.insert({ entry.first, entry.second });
    }
}

} // namespace xsk::gsc::iw9
