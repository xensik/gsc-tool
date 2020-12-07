// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "utils.hpp"

namespace utils
{

auto string::iequals(const std::string& a, const std::string& b) -> bool
{
    return (a.size() == b.size()) && std::equal(a.begin(), a.end(), b.begin(), b.end(),
        [](char a, char b)
        {
            return std::tolower(a) == std::tolower(b);
        });
}

auto string::is_number(const std::string& s) -> bool
{
    return !s.empty() && std::all_of(s.begin(), s.end(), isdigit);
}

auto string::is_hex_number(const std::string& s) -> bool
{
    return !s.empty() && std::all_of(s.begin(), s.end(), isxdigit);
}

auto string::to_lower(std::string input) -> std::string
{
    std::string output(input.begin(), input.end());

    for (std::size_t i = 0; i < output.size(); i++)
    {
        output[i] = std::tolower(input[i]);
    }

    return output;
}

auto string::split(std::string& str, char delimiter) -> std::vector<std::string>
{
    std::vector<std::string> internal;
    std::stringstream ss(str);
    std::string tok;

    if(str.find(delimiter) == std::string::npos)
    {
        internal.push_back(str);
        return internal;
    }

    // fix literals  ("hello there"), ("ok \n next")
    while (std::getline(ss, tok, delimiter))
    {
        internal.push_back(tok);
    }

    return internal;
}

auto string::clean_buffer_lines(std::vector<std::uint8_t>& buffer) -> std::vector<std::string>
{
    std::size_t pos;
    // TODO: optimize
    std::string data = std::string(reinterpret_cast<char*>(buffer.data()), buffer.size());

    while ((pos = data.find("\t")) != std::string::npos)
    {
        data = data.replace(pos, 1, "");
    }
    while ((pos = data.find("\r")) != std::string::npos)
    {
        data = data.replace(pos, 1, "");
    }

    return string::split(data, '\n');
}

auto string::get_string_literal(std::string str) -> std::string
{
    return str.substr(1, str.size() - 2);
}

} // namespace utils
