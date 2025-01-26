// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

struct scope
{
    using ptr = std::unique_ptr<scope>;

    enum abort_type
    {
        abort_none = 0,
        abort_continue = 1,
        abort_break = 2,
        abort_return = 3,
    };

    std::string end;
    std::string cnt;
    std::string brk;
    abort_type abort;
    bool is_dev;

    scope() : abort(abort_type::abort_none), is_dev(false) {}
    scope(std::string const& brk, std::string const& cnt) : cnt{ cnt }, brk{ brk }, abort(abort_type::abort_none), is_dev(false) {}
};

} // namespace xsk::arc
