// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

class string
{
public:
    template <typename ... Args>
    static auto va(const std::string& format, Args ... args) -> std::string
    {
        size_t size = snprintf(nullptr, 0, format.data(), args ...) + 1;
        std::vector<char> buf;
        buf.resize(size);
        snprintf(buf.data(), size, format.data(), args ...);
        return std::string(buf.data(), buf.data() + size - 1);
    }

    static auto oct_to_dec(const char* str) -> std::string;
    static auto bin_to_dec(const char* str) -> std::string;
    static auto hex_to_dec(const char* str) -> std::string;
    static auto iequals(const std::string& a, const std::string& b) -> bool;
    static auto is_number(const std::string& s) -> bool;
    static auto is_hex_number(const std::string& s) -> bool;
    static auto to_lower(const std::string& input) -> std::string;
    static auto to_code(const std::string& input) -> std::string;
    static auto to_literal(const std::string& input) -> std::string;
    static auto fordslash(const std::string& s) -> std::string;
    static auto backslash(const std::string& s) -> std::string;
    static auto quote(const std::string& s, bool single = true) -> std::string;
    static auto unquote(const std::string& s) -> std::string;
    static auto split(std::string& str, char delimiter) -> std::vector<std::string>;
    static auto clean_buffer_lines(std::vector<std::uint8_t>& buffer) -> std::vector<std::string>;
    static auto parse_code(std::string& line) -> std::vector<std::string>;
    static auto float_string(float value) -> std::string;
};

} // namespace xsk::utils
