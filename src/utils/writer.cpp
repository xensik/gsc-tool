// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/writer.hpp"

namespace xsk::utils
{

namespace
{

template <typename T>
auto write_scalar(u8* output, const usize size, usize& pos, T value, const bool swap) -> void
{
    if (pos > size || sizeof(T) > size - pos)
        throw writer::error("writer: out of bounds");

    // Copy through bytes so packed fields do not rely on typed pointer alignment or aliasing.
    auto bytes = std::array<u8, sizeof(T)>{};
    std::memcpy(bytes.data(), &value, sizeof(T));

    if (swap)
        std::reverse(bytes.begin(), bytes.end());

    std::memcpy(output + pos, bytes.data(), sizeof(T));
    pos += sizeof(T);
}

} // namespace

writer::writer(const bool swap) : size_{ default_size }, swap_{ swap }
{
    data_ = new u8[size_]();
}

writer::writer(const usize size, const bool swap) : size_{ size }, swap_{ swap }
{
    data_ = new u8[size_]();
}

writer::~writer()
{
    delete[] data_;
}

auto writer::clear() -> void
{
    std::memset(data_, 0, size_);
    pos_ = 0;
}

template <>
auto writer::write(const i8 data) -> void
{
    write_scalar(data_, size_, pos_, data, false);
}

template <>
auto writer::write(const u8 data) -> void
{
    write_scalar(data_, size_, pos_, data, false);
}

template <>
auto writer::write(i16 data) -> void
{
    write_scalar(data_, size_, pos_, data, swap_);
}

template <>
auto writer::write(u16 data) -> void
{
    write_scalar(data_, size_, pos_, data, swap_);
}

template <>
auto writer::write(i32 data) -> void
{
    write_scalar(data_, size_, pos_, data, swap_);
}

template <>
auto writer::write(u32 data) -> void
{
    write_scalar(data_, size_, pos_, data, swap_);
}

template <>
auto writer::write(i64 data) -> void
{
    write_scalar(data_, size_, pos_, data, swap_);
}

template <>
auto writer::write(u64 data) -> void
{
    write_scalar(data_, size_, pos_, data, swap_);
}

template <>
auto writer::write(f32 data) -> void
{
    write_scalar(data_, size_, pos_, data, swap_);
}

auto writer::write_i24(i32 data) -> void
{
    if (pos_ > size_ || 3 > size_ - pos_)
        throw error("writer: out of bounds");

    auto const value = static_cast<u32>(data) & 0xFFFFFF;
    data_[pos_] = static_cast<u8>(swap_ ? value >> 16 : value);
    data_[pos_ + 1] = static_cast<u8>(value >> 8);
    data_[pos_ + 2] = static_cast<u8>(swap_ ? value : value >> 16);

    pos_ += 3;
}

auto writer::write_string(std::string const& data) -> void
{
    if (pos_ > size_ || data.size() > size_ - pos_)
        throw error("writer: out of bounds");

    std::memcpy(reinterpret_cast<void*>(data_ + pos_), data.data(), data.size());
    pos_ += data.size();
}

auto writer::write_cstr(std::string const& data) -> void
{
    if (pos_ > size_ || data.size() >= size_ - pos_)
        throw error("writer: out of bounds");

    std::memcpy(reinterpret_cast<void*>(data_ + pos_), data.data(), data.size());
    data_[pos_ + data.size()] = 0;
    pos_ += data.size() + 1;
}

auto writer::is_avail() const -> bool
{
    return pos_ < size_;
}

auto writer::seek(const usize size) -> void
{
    if (pos_ <= size_ && size <= size_ - pos_) pos_ += size;
}

auto writer::seek_neg(const usize size) -> void
{
    if (pos_ >= size) pos_ -= size;
}

auto writer::align(const usize size) -> usize
{
    if (size == 0 || (size & (size - 1)) != 0)
        throw error("writer: invalid alignment");

    auto const pos = pos_;
    auto const remainder = pos_ & (size - 1);
    auto const advance = remainder == 0 ? 0 : size - remainder;

    if (pos_ > size_ || advance > size_ - pos_)
        throw error("writer: out of bounds");

    pos_ += advance;

    return pos_ - pos;
}

auto writer::data() const -> const u8*
{
    return data_;
}

auto writer::size() const -> usize
{
    return size_;
}

auto writer::pos() const -> usize
{
    return pos_;
}

auto writer::pos(const usize pos) -> void
{
    if (pos <= size_) pos_ = pos;
}

} // namespace xsk::utils
