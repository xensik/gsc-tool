// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"

namespace xsk::gsc::utils
{

byte_buffer::byte_buffer()
{
    data_.resize(0x1000000);
    std::fill(data_.begin(), data_.end(), 0);
    size_ = data_.size();
    pos_ = 0;
}

byte_buffer::byte_buffer(std::size_t size)
{
    data_.resize(size);
    std::fill(data_.begin(), data_.end(), 0);
    size_ = size;
    pos_ = 0;
}

byte_buffer::byte_buffer(const std::vector<std::uint8_t>& data)
{
    data_ = data;
    size_ = data.size();
    pos_ = 0;
}

byte_buffer::~byte_buffer()
{
    data_.clear();
    pos_ = 0;
}

void byte_buffer::clear()
{
    std::fill(data_.begin(), data_.end(), 0);
}

auto byte_buffer::is_avail() -> bool
{
    if (pos_ < data_.size()) return true;
    return false;
}

void byte_buffer::seek(std::size_t pos)
{
    pos_ += pos;
}
void byte_buffer::seek_neg(std::size_t pos)
{
    pos_ -= pos;
}

void byte_buffer::write_string(const std::string& data)
{
    strcpy(reinterpret_cast<char*>(data_.data() + pos_), data.data());
    pos_ += data.size();
}

void byte_buffer::write_c_string(const std::string& data)
{
    strcpy(reinterpret_cast<char*>(data_.data() + pos_), data.data());
    pos_ += data.size() + 1;
}

auto byte_buffer::read_c_string() -> std::string
{
    auto ret = std::string(reinterpret_cast<const char*>(data_.data() + pos_));
    pos_ += ret.size() + 1;
    return ret;
}

auto byte_buffer::print_bytes(std::size_t pos, std::size_t count) -> std::string
{
    std::string shit = "";
    
    for (auto i = pos; i < pos + count; i++)
    {
        shit = utils::string::va("%s %02X", shit.data(), (*reinterpret_cast<std::uint8_t*>(data_.data() + i)));
    }

    return shit;
}

auto byte_buffer::pos() -> std::size_t
{
    return pos_;
}

void byte_buffer::pos(std::size_t pos)
{
    if(pos >= 0 && pos <= size_)
    {
        pos_ = pos;
    }
}

auto byte_buffer::align(std::size_t size) -> std::size_t
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
