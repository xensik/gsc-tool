// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct locjmp
{
    std::string end;
    std::string cnt;
    std::string brk;
    bool last;
};

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

    struct var
    {
        std::string name;
        u8 create;
        bool init;
    };

    abort_type abort;
    std::string loc_end;
    std::string loc_cont;
    std::string loc_break;
    u32 create_count;
    u32 public_count;
    std::vector<var> vars;
    bool is_last;

    scope();
    auto transfer_dec(scope::ptr const& child) -> void;
    auto transfer(scope::ptr const& child) -> void;
    auto copy(scope::ptr const& child) -> void;
    auto append_dec(scope::ptr const& child) -> void;
    auto append(std::vector<scope*> const& childs) -> void;
    auto merge(std::vector<scope*> const& childs) -> void;
    auto init(scope::ptr const& child) -> void;
    auto init(std::vector<scope*> const& childs) -> void;
    auto find(usize start, std::string const& name) -> i32;
};

inline auto make_scope() -> std::unique_ptr<scope>
{
    return std::unique_ptr<scope>(new scope);
}

} // namespace xsk::gsc
