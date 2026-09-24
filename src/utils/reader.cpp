// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/reader.hpp"

#include <bit>

namespace xsk::utils
{

namespace
{

template <typename T>
auto read_scalar(u8 const* data, const usize size, usize& pos, const bool swap) -> T
{
    if (pos > size || sizeof(T) > size - pos)
        throw reader::error("reader: out of bounds");

    // Copy through bytes so packed fields do not rely on typed pointer alignment or aliasing.
    auto bytes = std::array<u8, sizeof(T)>{};
    std::memcpy(bytes.data(), data + pos, sizeof(T));

    if (swap)
        std::ranges::reverse(bytes);

    auto value = T{};
    std::memcpy(&value, bytes.data(), sizeof(T));
    pos += sizeof(T);
    return value;
}

} // namespace

reader::reader(const bool swap) : data_{ nullptr }, size_{ 0 }, swap_{ swap }
{
}

reader::reader(std::vector<u8> const& data, const bool swap) : data_{ data.data() }, size_{ static_cast<u32>(data.size()) }, swap_{ swap }
{
}

reader::reader(u8 const* data, const usize size, const bool swap) : data_{ data }, size_{ size }, swap_{ swap }
{
}

template <>
auto reader::read() -> i8
{
    return read_scalar<i8>(data_, size_, pos_, false);
}

template <>
auto reader::read() -> u8
{
    return read_scalar<u8>(data_, size_, pos_, false);
}

template <>
auto reader::read() -> i16
{
    return read_scalar<i16>(data_, size_, pos_, swap_);
}

template <>
auto reader::read() -> u16
{
    return read_scalar<u16>(data_, size_, pos_, swap_);
}

template <>
auto reader::read() -> i32
{
    return read_scalar<i32>(data_, size_, pos_, swap_);
}

template <>
auto reader::read() -> u32
{
    return read_scalar<u32>(data_, size_, pos_, swap_);
}

template <>
auto reader::read() -> i64
{
    return read_scalar<i64>(data_, size_, pos_, swap_);
}

template <>
auto reader::read() -> u64
{
    return read_scalar<u64>(data_, size_, pos_, swap_);
}

template <>
auto reader::read() -> f32
{
    return read_scalar<f32>(data_, size_, pos_, swap_);
}

auto reader::read_i24() -> i32
{
    if (pos_ > size_ || 3 > size_ - pos_)
        throw error("reader: out of bounds");

    auto const value = !swap_
                           ? static_cast<u32>(data_[pos_]) | (static_cast<u32>(data_[pos_ + 1]) << 8) | (static_cast<u32>(data_[pos_ + 2]) << 16)
                           : static_cast<u32>(data_[pos_ + 2]) | (static_cast<u32>(data_[pos_ + 1]) << 8) | (static_cast<u32>(data_[pos_]) << 16);
    pos_ += 3;
    return static_cast<i32>(value);
}

auto reader::read_cstr() -> std::string
{
    if (pos_ > size_)
        throw error("reader: out of bounds");

    auto const begin = data_ + pos_;
    auto const end = data_ + size_;
    auto const terminator = std::find(begin, end, 0);

    if (terminator == end)
        throw error("reader: out of bounds");

    auto ret = std::string(reinterpret_cast<char const*>(begin), static_cast<usize>(terminator - begin));
    pos_ += ret.size() + 1;
    return ret;
}

auto reader::read_bytes(const usize pos, const usize count) const -> std::string
{
    if (pos > size_ || count > size_ - pos)
        throw error("reader: out of bounds");

    if (count == 0)
        return {};

    auto data = std::string{};

    data.reserve(count * 3);

    for (auto i = usize{}; i < count; i++)
    {
        std::format_to(std::back_insert_iterator(data), "{:02X} ", data_[pos + i]);
    }

    data.pop_back();

    return data;
}

auto reader::is_avail() const -> bool
{
    return pos_ < size_;
}

auto reader::seek(const usize size) -> void
{
    if (pos_ <= size_ && size <= size_ - pos_) pos_ += size;
}

auto reader::seek_neg(const usize size) -> void
{
    if (pos_ >= size) pos_ -= size;
}

auto reader::align(const usize size) -> usize
{
    if (!std::has_single_bit(size))
        throw error("reader: invalid alignment");

    auto const pos = pos_;
    auto const remainder = pos_ & (size - 1);
    auto const advance = remainder == 0 ? 0 : size - remainder;

    if (pos_ > size_ || advance > size_ - pos_)
        throw error("reader: out of bounds");

    pos_ += advance;

    return pos_ - pos;
}

auto reader::data() const -> u8 const*
{
    return data_;
}

auto reader::size() const -> usize
{
    return size_;
}

auto reader::pos() const -> usize
{
    return pos_;
}

auto reader::pos(const usize pos) -> void
{
    if (pos <= size_) pos_ = pos;
}

} // namespace xsk::utils
