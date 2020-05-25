#pragma once

template <typename ... Args> std::string va(const std::string& format, Args ... args)
{
	size_t size = _snprintf(nullptr, 0, format.c_str(), args ...) + 1;
	std::vector<char> buf;
	buf.resize(size);
	_snprintf(buf.data(), size, format.c_str(), args ...);
	return std::string(buf.data(), buf.data() + size - 1);
}

bool is_hex_number(const std::string& s);
std::string to_lower(std::string input);
std::vector<std::string> split(std::string& str, char delimiter);
std::vector<std::string> clean_buffer_lines(std::string& buffer);
std::string get_string_literal(std::string str);
