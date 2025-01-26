// Copyright 2025 xensik. All rights reserved.
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
    static constexpr usize default_size = 0x100000;
    u8* data_;
    usize size_;
    usize pos_ = 0;
    bool swap_;

public:
    writer(writer const&) = delete;
    writer(writer&&) = delete;
    auto operator=(writer const&) -> writer& = delete;
    auto operator=(writer&&) -> writer& = delete;
    explicit writer(bool swap = false);
    writer(usize size, bool swap = false);
    ~writer();
    auto clear() -> void;
    template <typename T>
    auto write(T data) -> void;
    auto write_i24(i32 data) -> void;
    auto write_string(std::string const& data) -> void;
    auto write_cstr(std::string const& data) -> void;
    auto is_avail() const -> bool;
    auto seek(usize size) -> void;
    auto seek_neg(usize size) -> void;
    auto align(usize size) -> usize;
    auto data() const -> u8 const*;
    auto size() const -> usize;
    auto pos() const -> usize;
    auto pos(usize pos) -> void;
};

} // namespace xsk::utils
