// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_UTILS_BYTE_BUFFER_HPP_
#define _GSC_UTILS_BYTE_BUFFER_HPP_

namespace utils
{

class byte_buffer
{
    std::vector<std::uint8_t> data_;
    std::size_t size_;
    std::size_t pos_;

public:
    byte_buffer();
    byte_buffer(std::size_t size);
    byte_buffer(std::vector<std::uint8_t> data);
    byte_buffer(std::string filename);
    ~byte_buffer();

    template <typename T>
    auto read() -> T
    {
        auto ret = *reinterpret_cast<T*>(data_.data() + pos_);
        pos_ += sizeof(T);
        return ret;
    }

    template <typename T>
    auto write(T data) -> T*
    {
        T* mem = reinterpret_cast<T*>(data_.data() + pos_);
        memcpy(mem, &data, sizeof(T));

        pos_ += sizeof(T);

        return mem;
    }

    void clear();
    auto is_avail() -> bool;
    void seek(std::size_t pos);
    void seek_neg(std::size_t pos);
    void write_string(const std::string& data);
    void write_c_string(const std::string& data);
    void write_opaque_string(std::uint16_t id, const std::string& data = nullptr);
    auto read_string() -> std::string;
    auto read_opaque_string() -> std::string;
    auto print_bytes(std::size_t pos, std::size_t count) -> std::string;
    auto pos() -> std::size_t;
    auto buffer() -> std::vector<std::uint8_t>&;
};

using byte_buffer_ptr = std::unique_ptr<utils::byte_buffer>;

} // namespace utils

#endif // _GSC_UTILS_BYTE_BUFFER_HPP_
