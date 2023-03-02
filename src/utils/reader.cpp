// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/reader.hpp"

namespace xsk::utils
{

reader::reader(bool swap) : data_{ nullptr }, size_ { 0 }, pos_{ 0 }, swap_{ swap }
{
}

reader::reader(std::vector<u8> const& data, bool swap) : data_{ data.data() }, size_{ static_cast<u32>(data.size()) }, pos_{ 0 }, swap_{ swap }
{
}

reader::reader(u8 const* data, u32 size, bool swap) : data_{ data }, size_{ size }, pos_{ 0 }, swap_{ swap }
{
}

template<> auto reader::read() -> i8
{
    if (pos_ + 1 > size_)
        throw std::runtime_error("reader: out of bounds");

    auto value = *reinterpret_cast<i8 const*>(data_ + pos_);
    pos_ += 1;
    return value;
}

template<> auto reader::read() -> u8
{
    if (pos_ + 1 > size_)
        throw std::runtime_error("reader: out of bounds");

    auto value = *reinterpret_cast<u8 const*>(data_ + pos_);
    pos_ += 1;
    return value;
}

template<> auto reader::read() -> i16
{
    if (pos_ + 2 > size_)
        throw std::runtime_error("reader: out of bounds");

    if (!swap_)
    {
        auto value = *reinterpret_cast<i16 const*>(data_ + pos_);
        pos_ += 2;
        return value;
    }

    auto bytes = std::array<u8, 2>{};
    bytes[0] = (data_ + pos_)[1];
    bytes[1] = (data_ + pos_)[0];
    pos_ += 2;
    return *reinterpret_cast<i16*>(bytes.data());    
}

template<> auto reader::read() -> u16
{
    if (pos_ + 2 > size_)
        throw std::runtime_error("reader: out of bounds");

    if (!swap_)
    {
        auto value = *reinterpret_cast<u16 const*>(data_ + pos_);
        pos_ += 2;
        return value;
    }

    auto bytes = std::array<u8, 2>{};
    bytes[0] = (data_ + pos_)[1];
    bytes[1] = (data_ + pos_)[0];
    pos_ += 2;
    return *reinterpret_cast<u16*>(bytes.data());    
}

template<> auto reader::read() -> i32
{
    if (pos_ + 4 > size_)
        throw std::runtime_error("reader: out of bounds");

    if (!swap_)
    {
        auto value = *reinterpret_cast<i32 const*>(data_ + pos_);
        pos_ += 4;
        return value;
    }

    auto bytes = std::array<u8, 4>{};
    bytes[0] = (data_ + pos_)[3];
    bytes[1] = (data_ + pos_)[2];
    bytes[2] = (data_ + pos_)[1];
    bytes[3] = (data_ + pos_)[0];
    pos_ += 4;
    return *reinterpret_cast<i32*>(bytes.data());    
}

template<> auto reader::read() -> u32
{
    if (pos_ + 4 > size_)
        throw std::runtime_error("reader: out of bounds");

    if (!swap_)
    {
        auto value = *reinterpret_cast<u32 const*>(data_ + pos_);
        pos_ += 4;
        return value;
    }

    auto bytes = std::array<u8, 4>{};
    bytes[0] = (data_ + pos_)[3];
    bytes[1] = (data_ + pos_)[2];
    bytes[2] = (data_ + pos_)[1];
    bytes[3] = (data_ + pos_)[0];
    pos_ += 4;
    return *reinterpret_cast<u32*>(bytes.data());    
}

template<> auto reader::read() -> i64
{
    if (pos_ + 8 > size_)
        throw std::runtime_error("reader: out of bounds");

    if (!swap_)
    {
        auto value = *reinterpret_cast<i64 const*>(data_ + pos_);
        pos_ += 8;
        return value;
    }

    auto bytes = std::array<u8, 8>{};
    bytes[0] = (data_ + pos_)[7];
    bytes[1] = (data_ + pos_)[6];
    bytes[2] = (data_ + pos_)[5];
    bytes[3] = (data_ + pos_)[4];
    bytes[4] = (data_ + pos_)[3];
    bytes[5] = (data_ + pos_)[2];
    bytes[6] = (data_ + pos_)[1];
    bytes[7] = (data_ + pos_)[0];
    pos_ += 8;
    return *reinterpret_cast<i64*>(bytes.data());    
}

template<> auto reader::read() -> u64
{
    if (pos_ + 8 > size_)
        throw std::runtime_error("reader: out of bounds");

    if (!swap_)
    {
        auto value = *reinterpret_cast<u64 const*>(data_ + pos_);
        pos_ += 8;
        return value;
    }

    auto bytes = std::array<u8, 8>{};
    bytes[0] = (data_ + pos_)[7];
    bytes[1] = (data_ + pos_)[6];
    bytes[2] = (data_ + pos_)[5];
    bytes[3] = (data_ + pos_)[4];
    bytes[4] = (data_ + pos_)[3];
    bytes[5] = (data_ + pos_)[2];
    bytes[6] = (data_ + pos_)[1];
    bytes[7] = (data_ + pos_)[0];
    pos_ += 8;
    return *reinterpret_cast<u64*>(bytes.data());    
}

template<> auto reader::read() -> f32
{
    if (pos_ + 4 > size_)
        throw std::runtime_error("reader: out of bounds");

    if (!swap_)
    {
        auto value = *reinterpret_cast<f32 const*>(data_ + pos_);
        pos_ += 4;
        return value;
    }

    auto bytes = std::array<u8, 4>{};
    bytes[0] = (data_ + pos_)[3];
    bytes[1] = (data_ + pos_)[2];
    bytes[2] = (data_ + pos_)[1];
    bytes[3] = (data_ + pos_)[0];
    pos_ += 4;
    return *reinterpret_cast<f32*>(bytes.data());    
}

auto reader::read_cstr() -> std::string
{
    auto ret = std::string{ reinterpret_cast<char const*>(data_ + pos_) };
    pos_ += static_cast<u32>(ret.size() + 1);
    return ret;
}

auto reader::read_bytes(u32 pos, u32 count) -> std::string
{
    auto data = std::string{};

    data.reserve(count * 3);

    for (auto i = pos; i < pos + count; i++)
    {
        fmt::format_to(std::back_insert_iterator(data), "{:02X} ", *reinterpret_cast<u8 const*>(data_ + i));
    }

    data.pop_back();

    return data;
}

auto reader::is_avail() -> bool
{
    return (pos_ < size_) ? true : false;
}

auto reader::seek(u32 size) -> void
{
    if (pos_ + size <= size_) pos_ += size;
}

auto reader::seek_neg(u32 size) -> void
{
    if (pos_ - size >= 0) pos_ -= size;
}

auto reader::align(u32 size) -> u32
{
    auto pos = pos_;

    pos_ = (pos_ + (size - 1)) & ~(size - 1);

    return pos_ - pos;
}

auto reader::data() -> u8 const*
{
    return data_;
}

auto reader::size() -> u32
{
    return size_;
}

auto reader::pos() -> u32
{
    return pos_;
}

auto reader::pos(u32 pos) -> void
{
    if (pos >= 0 && pos <= size_)
    {
        pos_ = pos;
    }
}

} // namespace xsk::utils
