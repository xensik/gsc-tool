// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct local_var
{
    std::string name;
    std::uint8_t create;
    bool init;
};

struct block
{
    using ptr = std::unique_ptr<block>;

    std::string loc_end;
    std::string loc_break;
    std::string loc_continue;
    std::vector<local_var> local_vars;
    std::uint32_t local_vars_create_count;
    std::uint32_t local_vars_public_count;
    abort_t abort;
    bool is_last;

    block();
    void transfer(const block::ptr& child);
    void copy(const block::ptr& child);
    void append(const std::vector<block*>& childs);
    void merge(const std::vector<block*>& childs);
    void init_from_child(const std::vector<block*>& childs);
    auto find_variable(std::size_t start, const std::string& name) -> std::int32_t;
    void transfer_decompiler(const block::ptr& child);
    void append_decompiler(const block::ptr& child, bool all = false);
};

} // namespace xsk::gsc
