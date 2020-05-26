#pragma once

namespace utils::string
{
	template <typename ... Args>
	auto va(const std::string& format, Args ... args) -> std::string
	{
		size_t size = _snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		std::vector<char> buf;
		buf.resize(size);
		_snprintf(buf.data(), size, format.c_str(), args ...);
		return std::string(buf.data(), buf.data() + size - 1);
	}

	auto is_hex_number(const std::string& s) -> bool;
	auto to_lower(std::string input) -> std::string;
	auto split(std::string& str, char delimiter) -> std::vector<std::string>;
	auto clean_buffer_lines(std::string& buffer) -> std::vector<std::string>;
	auto get_string_literal(std::string str) -> std::string;
}
