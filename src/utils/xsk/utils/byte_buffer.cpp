// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"

namespace xsk::utils
{

byte_buffer::byte_buffer()
{
    data_.resize(0x100000);
    std::fill(data_.begin(), data_.end(), '\0');
    size_ = static_cast<std::uint32_t>(data_.size());
    pos_ = 0;
}

byte_buffer::byte_buffer(std::uint32_t size)
{
    data_.resize(size);
    std::fill(data_.begin(), data_.end(), '\0');
    size_ = size;
    pos_ = 0;
}

byte_buffer::byte_buffer(const std::vector<std::uint8_t>& data)
{
    data_ = data;
    size_ = static_cast<std::uint32_t>(data_.size());
    pos_ = 0;
}

byte_buffer::~byte_buffer()
{
    data_.clear();
    size_ = 0;
    pos_ = 0;
}

void byte_buffer::clear()
{
    std::fill(data_.begin(), data_.end(), '\0');
}

auto byte_buffer::is_avail() -> bool
{
    return (pos_ < size_) ? true : false;
}

void byte_buffer::seek(std::uint32_t count)
{
    pos_ += count;
}

void byte_buffer::seek_neg(std::uint32_t count)
{
    pos_ -= count;
}

void byte_buffer::write_string(const std::string& data)
{
    if (pos_ + data.size() > size_) return;

    std::memcpy(reinterpret_cast<void*>(data_.data() + pos_), data.data(), data.size());
    pos_ += static_cast<std::uint32_t>(data.size());
}

void byte_buffer::write_c_string(const std::string& data)
{
    if (pos_ + data.size() >= size_) return;

    std::memcpy(reinterpret_cast<void*>(data_.data() + pos_), data.data(), data.size());
    pos_ += static_cast<std::uint32_t>(data.size() + 1);
}

auto byte_buffer::read_c_string() -> std::string
{
    auto ret = std::string(reinterpret_cast<const char*>(data_.data() + pos_));
    pos_ += static_cast<std::uint32_t>(ret.size() + 1);
    return ret;
}

auto byte_buffer::print_bytes(std::uint32_t pos, std::uint32_t count) -> std::string
{
    std::string data {};

    for (auto i = pos; i < pos + count; i++)
    {
        data = utils::string::va("%s %02X", data.data(), (*reinterpret_cast<std::uint8_t*>(data_.data() + i)));
    }

    return data;
}

auto byte_buffer::pos() -> std::uint32_t
{
    return pos_;
}

void byte_buffer::pos(std::uint32_t pos)
{
    if (pos >= 0 && pos <= size_)
    {
        pos_ = pos;
    }
}

auto byte_buffer::align(std::uint32_t size) -> std::uint32_t
{
    auto pos = pos_;

    pos_ = (pos_ + (size - 1)) & ~(size - 1);

    return pos_ - pos;
}

auto byte_buffer::buffer() -> std::vector<std::uint8_t>&
{
    return data_;
}

} // namespace xsk::utils
