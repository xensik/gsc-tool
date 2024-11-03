// Copyright 2024 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

struct writer
{
    using ptr = std::unique_ptr<writer>;
    using error = std::runtime_error;

private:
    static constexpr u32 default_size = 0x100000;
    u8* data_;
    u32 size_;
    u32 pos_ = 0;
    bool swap_;

public:
    writer(writer const&) = delete;
    writer(writer&&) = delete;
    auto operator=(writer const&) -> writer& = delete;
    auto operator=(writer&&) -> writer& = delete;
    explicit writer(bool swap = false);
    writer(u32 size, bool swap = false);
    ~writer();
    auto clear() -> void;
    template <typename T>
    auto write(T data) -> void;
    auto write_string(std::string const& data) -> void;
    auto write_cstr(std::string const& data) -> void;
    auto is_avail() const -> bool;
    auto seek(u32 size) -> void;
    auto seek_neg(u32 size) -> void;
    auto align(u32 size) -> u32;
    auto data() const -> u8 const*;
    auto size() const -> u32;
    auto pos() const -> u32;
    auto pos(u32 pos) -> void;
};

} // namespace xsk::utils
