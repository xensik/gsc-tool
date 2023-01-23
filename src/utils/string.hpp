// Copyright 2023 xensik. All rights reserved.
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
    static auto va(std::string const& format, Args ... args) -> std::string
    {
        usize size = snprintf(nullptr, 0, format.data(), args ...) + 1;
        std::vector<char> buf;
        buf.resize(size);
        snprintf(buf.data(), size, format.data(), args ...);
        return std::string(buf.data(), buf.data() + size - 1);
    }

    static auto oct_to_dec(char const* str) -> std::string;
    static auto bin_to_dec(char const* str) -> std::string;
    static auto hex_to_dec(char const* str) -> std::string;
    static auto iequals(std::string const& a, std::string const& b) -> bool;
    static auto is_number(std::string const& s) -> bool;
    static auto is_hex_number(std::string const& s) -> bool;
    static auto to_lower(std::string const& input) -> std::string;
    static auto to_code(std::string const& input) -> std::string;
    static auto to_literal(std::string const& input) -> std::string;
    static auto fordslash(std::string const& s) -> std::string;
    static auto backslash(std::string const& s) -> std::string;
    static auto quote(std::string const& s, bool single = true) -> std::string;
    static auto unquote(std::string const& s) -> std::string;
    static auto split(std::string& str, char delimiter) -> std::vector<std::string>;
    static auto clean_buffer_lines(std::vector<u8>& buffer) -> std::vector<std::string>;
    static auto parse_code(std::string& line) -> std::vector<std::string>;
    static auto float_string(float value, bool toint = false) -> std::string;
};

} // namespace xsk::utils
