// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _XSK_UTILS_BYTE_BUFFER_H_
#define _XSK_UTILS_BYTE_BUFFER_H_

namespace xsk
{

class byte_buffer
{
	std::vector<std::uint8_t> data_;
	std::size_t size_;
	std::size_t pos_;

public:
	byte_buffer();
	byte_buffer(std::size_t size);
	byte_buffer(std::string filename);
	byte_buffer(std::shared_ptr<std::vector <std::uint8_t>> buffer);
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
	void write_cpp_string(const std::string& data);
	void write_string(const std::string& data);
	void write_opaque_string(std::uint16_t id, const std::string& data = nullptr);
	auto read_string() -> std::string;
	auto read_opaque_string() -> std::string;
	auto get_bytes_print(std::size_t index, std::size_t count) -> std::string;
	auto get_pos() -> std::size_t;
	auto get_buffer() -> std::vector<std::uint8_t>&;
};

} // namespace xsk

#endif // _XSK_UTILS_BYTE_BUFFER_H_