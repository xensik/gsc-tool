// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/writer.hpp"

namespace xsk::utils
{

writer::writer(bool swap) : size_{ default_size }, swap_{ swap }
{
    data_ = new u8[size_]();
}

writer::writer(usize size, bool swap) : size_{ size }, swap_{ swap }
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

template<> auto writer::write(i8 data) -> void
{
    if (pos_ + 1 > size_)
        throw error("writer: out of bounds");

    *reinterpret_cast<i8*>(data_ + pos_) = data;
    pos_ += 1;
}

template<> auto writer::write(u8 data) -> void
{
    if (pos_ + 1 > size_)
        throw error("writer: out of bounds");

    *reinterpret_cast<u8*>(data_ + pos_) = data;
    pos_ += 1;
}

template<> auto writer::write(i16 data) -> void
{
    if (pos_ + 2 > size_)
        throw error("writer: out of bounds");

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
        throw error("writer: out of bounds");

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
        throw error("writer: out of bounds");

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
        throw error("writer: out of bounds");

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
        throw error("writer: out of bounds");

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
        throw error("writer: out of bounds");

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
        throw error("writer: out of bounds");

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

auto writer::write_i24(i32 data) -> void
{
    if (pos_ + 3 > size_)
        throw error("writer: out of bounds");

    if (!swap_)
    {
        *reinterpret_cast<i32*>(data_ + pos_) = data & 0xFFFFFF;
    }
    else
    {
        (data_ + pos_)[0] = reinterpret_cast<u8*>(&data)[2];
        (data_ + pos_)[1] = reinterpret_cast<u8*>(&data)[1];
        (data_ + pos_)[2] = reinterpret_cast<u8*>(&data)[0];
    }

    pos_ += 3;
}

auto writer::write_string(std::string const& data) -> void
{
    if (pos_ + data.size() > size_)
        throw error("writer: out of bounds");

    std::memcpy(reinterpret_cast<void*>(data_ + pos_), data.data(), data.size());
    pos_ += data.size();
}

auto writer::write_cstr(std::string const& data) -> void
{
    if (pos_ + data.size() >= size_)
        throw error("writer: out of bounds");

    std::memcpy(reinterpret_cast<void*>(data_ + pos_), data.data(), data.size());
    pos_ += data.size() + 1;
}

auto writer::is_avail() const -> bool
{
    return pos_ < size_;
}

auto writer::seek(usize size) -> void
{
    if (pos_ + size <= size_) pos_ += size;
}

auto writer::seek_neg(usize size) -> void
{
    if (pos_ >= size) pos_ -= size;
}

auto writer::align(usize size) -> usize
{
    auto pos = pos_;

    pos_ = (pos_ + (size - 1)) & ~(size - 1);

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

auto writer::pos(usize pos) -> void
{
    if (pos <= size_) pos_ = pos;
}

} // namespace xsk::utils
