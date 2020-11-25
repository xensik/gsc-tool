// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "utils.hpp"

namespace utils
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

byte_buffer::byte_buffer(std::string filename)
{
	size_ = 0;
	pos_ = 0;

	FILE* fp = fopen(filename.c_str(), "rb");
	if (fp)
	{
		long len = utils::file::length(fp);
		data_.resize(len);
		fread(data_.data(), len, 1, fp);
		fclose(fp);
		size_ = len;
	}
	else
	{
		printf("Couldn't open file %s!\n", filename.data());
		std::exit(-1);
	}
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

void byte_buffer::write_opaque_string(std::uint16_t id, const std::string& data)
{
	// TODO
}

auto byte_buffer::read_string() -> std::string
{
	auto ret = std::string(reinterpret_cast<const char*>(data_.data() + pos_));
	pos_ += ret.size() + 1;
	return ret;
}

auto byte_buffer::read_opaque_string() -> std::string
{
	auto temp = this->read<std::uint16_t>();

	if (!temp)
	{
		return this->read_string();
	}

	return std::to_string(temp);
}

auto byte_buffer::print_bytes(std::size_t pos, std::size_t count) -> std::string
{
	std::string shit;
	
	for (auto i = pos; i < pos + count; i++)
	{
		shit += utils::string::va("%s %02X", shit.data(), (*reinterpret_cast<std::uint8_t*>(data_.data() + i)));
	}

	return shit;
}

auto byte_buffer::pos() -> std::size_t
{
	return pos_;
}

auto byte_buffer::buffer() -> std::vector<std::uint8_t>&
{
	return data_;
}

} // namespace utils
