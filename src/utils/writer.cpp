// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/writer.hpp"

namespace xsk::utils
{

writer::writer(bool swap) : size_{ 0x100000 }, pos_{ 0 }, swap_{ swap }
{
    data_ = reinterpret_cast<u8*>(std::malloc(size_));
    std::memset(data_, 0, size_);
}

writer::writer(u32 size, bool swap) : size_{ size }, pos_{ 0 }, swap_{ swap }
{
    data_ = reinterpret_cast<u8*>(std::malloc(size_));
    std::memset(data_, 0, size_);
}

writer::~writer()
{
    std::free(reinterpret_cast<void*>(data_));
}

auto writer::clear() -> void
{
    std::memset(data_, 0, size_);
    pos_ = 0;
}

template<> auto writer::write(i8 data) -> void
{
    if (pos_ + 1 > size_)
        throw std::runtime_error("writer: out of bounds");

    *reinterpret_cast<i8*>(data_ + pos_) = data;
    pos_ += 1;
}

template<> auto writer::write(u8 data) -> void
{
    if (pos_ + 1 > size_)
        throw std::runtime_error("writer: out of bounds");

    *reinterpret_cast<u8*>(data_ + pos_) = data;
    pos_ += 1;
}

template<> auto writer::write(i16 data) -> void
{
    if (pos_ + 2 > size_)
        throw std::runtime_error("writer: out of bounds");

    if (!swap_)
    {
        *reinterpret_cast<i16*>(data_ + pos_) = data;
    }
    else
    {
        (data_ + pos_)[0] = reinterpret_cast<u8*>(&data)[1];
        (data_ + pos_)[1] = reinterpret_cast<u8*>(&data)[0];
    }

    pos_ += 2;
}

template<> auto writer::write(u16 data) -> void
{
    if (pos_ + 2 > size_)
        throw std::runtime_error("writer: out of bounds");

    if (!swap_)
    {
        *reinterpret_cast<u16*>(data_ + pos_) = data;
    }
    else
    {
        (data_ + pos_)[0] = reinterpret_cast<u8*>(&data)[1];
        (data_ + pos_)[1] = reinterpret_cast<u8*>(&data)[0];
    }

    pos_ += 2;
}

template<> auto writer::write(i32 data) -> void
{
    if (pos_ + 4 > size_)
        throw std::runtime_error("writer: out of bounds");

    if (!swap_)
    {
        *reinterpret_cast<i32*>(data_ + pos_) = data;
    }
    else
    {
        (data_ + pos_)[0] = reinterpret_cast<u8*>(&data)[3];
        (data_ + pos_)[1] = reinterpret_cast<u8*>(&data)[2];
        (data_ + pos_)[2] = reinterpret_cast<u8*>(&data)[1];
        (data_ + pos_)[3] = reinterpret_cast<u8*>(&data)[0];
    }

    pos_ += 4;
}

template<> auto writer::write(u32 data) -> void
{
    if (pos_ + 4 > size_)
        throw std::runtime_error("writer: out of bounds");

    if (!swap_)
    {
        *reinterpret_cast<u32*>(data_ + pos_) = data;
    }
    else
    {
        (data_ + pos_)[0] = reinterpret_cast<u8*>(&data)[3];
        (data_ + pos_)[1] = reinterpret_cast<u8*>(&data)[2];
        (data_ + pos_)[2] = reinterpret_cast<u8*>(&data)[1];
        (data_ + pos_)[3] = reinterpret_cast<u8*>(&data)[0];
    }

    pos_ += 4;
}

template<> auto writer::write(i64 data) -> void
{
    if (pos_ + 8 > size_)
        throw std::runtime_error("writer: out of bounds");

    if (!swap_)
    {
        *reinterpret_cast<i64*>(data_ + pos_) = data;
    }
    else
    {
        (data_ + pos_)[0] = reinterpret_cast<u8*>(&data)[7];
        (data_ + pos_)[1] = reinterpret_cast<u8*>(&data)[6];
        (data_ + pos_)[2] = reinterpret_cast<u8*>(&data)[5];
        (data_ + pos_)[3] = reinterpret_cast<u8*>(&data)[4];
        (data_ + pos_)[4] = reinterpret_cast<u8*>(&data)[3];
        (data_ + pos_)[5] = reinterpret_cast<u8*>(&data)[2];
        (data_ + pos_)[6] = reinterpret_cast<u8*>(&data)[1];
        (data_ + pos_)[7] = reinterpret_cast<u8*>(&data)[0];
    }

    pos_ += 8;
}

template<> auto writer::write(u64 data) -> void
{
    if (pos_ + 8 > size_)
        throw std::runtime_error("writer: out of bounds");

    if (!swap_)
    {
        *reinterpret_cast<u64*>(data_ + pos_) = data;
    }
    else
    {
        (data_ + pos_)[0] = reinterpret_cast<u8*>(&data)[7];
        (data_ + pos_)[1] = reinterpret_cast<u8*>(&data)[6];
        (data_ + pos_)[2] = reinterpret_cast<u8*>(&data)[5];
        (data_ + pos_)[3] = reinterpret_cast<u8*>(&data)[4];
        (data_ + pos_)[4] = reinterpret_cast<u8*>(&data)[3];
        (data_ + pos_)[5] = reinterpret_cast<u8*>(&data)[2];
        (data_ + pos_)[6] = reinterpret_cast<u8*>(&data)[1];
        (data_ + pos_)[7] = reinterpret_cast<u8*>(&data)[0];
    }

    pos_ += 8;
}

template<> auto writer::write(f32 data) -> void
{
    if (pos_ + 4 > size_)
        throw std::runtime_error("writer: out of bounds");

    if (!swap_)
    {
        *reinterpret_cast<f32*>(data_ + pos_) = data;
    }
    else
    {
        (data_ + pos_)[0] = reinterpret_cast<u8*>(&data)[3];
        (data_ + pos_)[1] = reinterpret_cast<u8*>(&data)[2];
        (data_ + pos_)[2] = reinterpret_cast<u8*>(&data)[1];
        (data_ + pos_)[3] = reinterpret_cast<u8*>(&data)[0];
    }

    pos_ += 4;
}

auto writer::write_string(std::string const& data) -> void
{
    if (pos_ + data.size() > size_)
        throw std::runtime_error("writer: out of bounds");

    std::memcpy(reinterpret_cast<void*>(data_ + pos_), data.data(), data.size());
    pos_ += static_cast<u32>(data.size());
}

auto writer::write_cstr(std::string const& data) -> void
{
    if (pos_ + data.size() >= size_)
        throw std::runtime_error("writer: out of bounds");

    std::memcpy(reinterpret_cast<void*>(data_ + pos_), data.data(), data.size());
    pos_ += static_cast<u32>(data.size() + 1);
}

auto writer::is_avail() -> bool
{
    return (pos_ < size_) ? true : false;
}

auto writer::seek(u32 size) -> void
{
    if (pos_ + size <= size_) pos_ += size;
}

auto writer::seek_neg(u32 size) -> void
{
    if (pos_ - size >= 0) pos_ -= size;
}

auto writer::align(u32 size) -> u32
{
    auto pos = pos_;

    pos_ = (pos_ + (size - 1)) & ~(size - 1);

    return pos_ - pos;
}

auto writer::data() -> const u8*
{
    return data_;
}

auto writer::size() -> u32
{
    return size_;
}

auto writer::pos() -> u32
{
    return pos_;
}

auto writer::pos(u32 pos) -> void
{
    if (pos >= 0 && pos <= size_)
    {
        pos_ = pos;
    }
}

} // namespace xsk::utils
