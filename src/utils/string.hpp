#pragma once

bool is_hex_number(const std::string& s);
std::string to_lower(std::string input);
std::vector<std::string> split(std::string& str, char delimiter);
std::vector<std::string> clean_buffer_lines(std::string& buffer);
std::string get_string_literal(std::string str);
