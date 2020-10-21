// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _XSK_UTILS_STRING_H_
#define _XSK_UTILS_STRING_H_

namespace utils
{

class string
{
public:
	template <typename ... Args>
	static auto va(const std::string& format, Args ... args) -> std::string
	{
		size_t size = _snprintf(nullptr, 0, format.data(), args ...) + 1;
		std::vector<char> buf;
		buf.resize(size);
		_snprintf(buf.data(), size, format.data(), args ...);
		return std::string(buf.data(), buf.data() + size - 1);
	}

	static auto iequals(const std::string& a, const std::string& b) -> bool;
	static auto is_number(const std::string& s) -> bool;
	static auto is_hex_number(const std::string& s) -> bool;
	static auto to_lower(std::string input)->std::string;
	static auto split(std::string& str, char delimiter) -> std::vector<std::string>;
	static auto clean_buffer_lines(std::string& buffer) -> std::vector<std::string>;
	static auto get_string_literal(std::string str) -> std::string;
};

} // namespace utils

#endif // _XSK_UTILS_STRING_H_
