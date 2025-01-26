// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

struct string
{
    static auto oct_to_dec(char const* str) -> std::string;
    static auto bin_to_dec(char const* str) -> std::string;
    static auto hex_to_dec(char const* str) -> std::string;
    static auto iequals(std::string const& a, std::string const& b) -> bool;
    static auto is_number(std::string const& str) -> bool;
    static auto is_hex_number(std::string const& str) -> bool;
    static auto to_lower(std::string const& str) -> std::string;
    static auto to_code(std::string const& str) -> std::string;
    static auto to_literal(std::string const& str) -> std::string;
    static auto fordslash(std::string const& str) -> std::string;
    static auto backslash(std::string const& str) -> std::string;
    static auto quote(std::string const& str, bool single = true) -> std::string;
    static auto unquote(std::string const& str) -> std::string;
    static auto split(std::string& str, char delimiter) -> std::vector<std::string>;
    static auto clean_buffer_lines(u8 const* data, usize size) -> std::vector<std::string>;
    static auto parse_code(std::string& line) -> std::vector<std::string>;
    static auto float_string(float value, bool toint = false) -> std::string;
};

} // namespace xsk::utils
