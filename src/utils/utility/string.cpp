// Copyright 2021 xensik. All rights reserved.
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

auto string::to_lower(const std::string& input) -> std::string
{
    std::string data(input.begin(), input.end());

    for (std::size_t i = 0; i < data.size(); i++)
    {
        data[i] = std::tolower(input[i]);
    }

    return data;
}

auto string::to_code(const std::string& input) -> std::string
{
    std::string data = input.substr(1, input.size() - 2);
    std::size_t pos;

    while ((pos = data.find("\\n")) != std::string::npos)
    {
        data.erase(data.begin() + pos);
        data = data.replace(pos, 1, "\n");
    }
    while ((pos = data.find("\\t")) != std::string::npos)
    {
        data.erase(data.begin() + pos);
        data = data.replace(pos, 1, "\t");
    }
    while ((pos = data.find("\\r")) != std::string::npos)
    {
        data.erase(data.begin() + pos);
        data = data.replace(pos, 1, "\r");
    }
    while ((pos = data.find("\\\"")) != std::string::npos)
    {
        data.erase(data.begin() + pos);
    }

    return data;
}

auto string::to_literal(const std::string& input) -> std::string
{
    std::string data(input.begin(), input.end());
    std::size_t pos;

    while ((pos = data.find('\n')) != std::string::npos)
    {
        data = data.replace(pos, 1, "n");
        data.insert(data.begin() + pos, '\\');
    }
    while ((pos = data.find('\t')) != std::string::npos)
    {
        data = data.replace(pos, 1, "t");
        data.insert(data.begin() + pos, '\\');
    }
    while ((pos = data.find('\r')) != std::string::npos)
    {
        data = data.replace(pos, 1, "r");
        data.insert(data.begin() + pos, '\\');
    }
    for(pos = 0; pos < data.size(); pos++)
    {
        if(data.at(pos) == '\"')
        {
            data.insert(data.begin() + pos, '\\');
            pos++;
        }
    }

    data.insert(data.begin(), '\"');
    data.insert(data.end(), '\"');

    return data;
}

auto string::quote(const std::string& s, bool single) -> std::string
{
    std::string data(s.begin(), s.end());

    if(single)
    {
        data.insert(data.begin(), '\'');
        data.insert(data.end(), '\'');
    }
    else
    {
        data.insert(data.begin(), '\"');
        data.insert(data.end(), '\"');
    }

    return data;
}

auto string::unquote(const std::string& s) -> std::string
{
    if(s.at(0) == '\'' || s.at(0) == '\"')
        return s.substr(1, s.size() - 2);
    
    return s;
}

auto string::split(std::string& str, char delimiter) -> std::vector<std::string>
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string tok;

    while (std::getline(ss, tok, delimiter))
    {
        tokens.push_back(tok);
    }

    return tokens;
}

auto string::clean_buffer_lines(std::vector<std::uint8_t>& buffer) -> std::vector<std::string>
{
    std::string data = std::string(reinterpret_cast<char*>(buffer.data()), buffer.size());
    std::size_t pos;

    while ((pos = data.find("\t")) != std::string::npos)
    {
        data = data.replace(pos, 1, "");
    }
    while ((pos = data.find("\r")) != std::string::npos)
    {
        data = data.replace(pos, 1, "");
    }

    std::vector<std::string> lines;
    std::stringstream ss(data);
    std::string tok;

    while (std::getline(ss, tok, '\n'))
    {
        lines.push_back(tok);
    }

    return lines;
}

auto string::parse_code(std::string& line) -> std::vector<std::string>
{
    std::vector<std::string> data;
    std::regex exp(R"(([_A-Za-z0-9\-]+|\"(?:\\.|[^\"])*?\"|\'(?:\\.|[^\'])*?\')(?:\s+|$))");

    for(auto i = std::sregex_iterator(line.begin(), line.end(), exp); i != std::sregex_iterator(); ++i)
    {
        data.push_back(i->format("$1"));
    }

    return data;
}

} // namespace utils
