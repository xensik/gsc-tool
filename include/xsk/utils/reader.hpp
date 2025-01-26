// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

struct reader
{
    using ptr = std::unique_ptr<reader>;
    using error = std::runtime_error;

private:
    u8 const* data_;
    usize size_;
    usize pos_ = 0;
    bool swap_;

public:
    explicit reader(bool swap = false);
    reader(std::vector<u8> const& data, bool swap = false);
    reader(u8 const* data, usize size, bool swap = false);
    template <typename T>
    auto read() -> T;
    auto read_i24() -> i32;
    auto read_cstr() -> std::string;
    auto read_bytes(usize pos, usize count) const -> std::string;
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
