// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

class reader
{
public:
    using ptr = std::unique_ptr<reader>;

private:
    u8 const* data_;
    u32 size_;
    u32 pos_;
    bool swap_;

public:
    reader(bool swap = false);
    reader(std::vector<u8> const& data, bool swap = false);
    reader(u8 const* data, u32 size, bool swap = false);
    template <typename T>
    auto read() -> T;
    auto read_cstr() -> std::string;
    auto read_bytes(u32 pos, u32 count) -> std::string;
    auto is_avail() -> bool;
    auto seek(u32 size) -> void;
    auto seek_neg(u32 size) -> void;
    auto align(u32 size) -> u32;
    auto data() -> u8 const*;
    auto size() -> u32;
    auto pos() -> u32;
    auto pos(u32 pos) -> void;
};

} // namespace xsk::utils
