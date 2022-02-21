// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

struct block
{
    using ptr = std::unique_ptr<block>;

    std::string loc_end;
    std::string loc_break;
    std::string loc_continue;
    abort_t abort;
    bool is_dev;

    block() : is_dev(false), abort(abort_t::abort_none) {}
    block(const std::string& lbreak, const std::string& lcont)
        : is_dev(false), abort(abort_t::abort_none), loc_break(lbreak), loc_continue(lcont) {}
};

} // namespace xsk::arc
