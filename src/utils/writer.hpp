// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

class writer
{
public:
    using ptr = std::unique_ptr<writer>;

private:
    u8* data_;
    u32 size_;
    u32 pos_;
    bool swap_;

public:
    writer(bool swap = false);
    writer(u32 size, bool swap = false);
    ~writer();
    auto clear() -> void;
    template <typename T>
    auto write(T data) -> void;
    auto write_string(std::string const& data) -> void;
    auto write_cstr(std::string const& data) -> void;
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
