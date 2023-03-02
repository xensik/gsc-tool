// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"

namespace xsk::utils
{

auto string::oct_to_dec(char const* str) -> std::string
{
    return std::to_string(std::stoi(str, nullptr, 8));
}

auto string::bin_to_dec(char const* str) -> std::string
{
    return std::to_string(std::stoi(&str[2], nullptr, 2)); // str must prefix 0[bB]
}

auto string::hex_to_dec(char const* str) -> std::string
{
    return std::to_string(std::stoi(&str[2], nullptr, 16)); // str must prefix 0[xX]
}

auto string::iequals(std::string const& a, std::string const& b) -> bool
{
    return (a.size() == b.size()) && std::equal(a.begin(), a.end(), b.begin(), b.end(),
        [](char a, char b)
        {
            return std::tolower(a) == std::tolower(b);
        });
}

auto string::is_number(std::string const& s) -> bool
{
    return !s.empty() && std::all_of(s.begin(), s.end(), isdigit);
}

auto string::is_hex_number(std::string const& s) -> bool
{
    return !s.empty() && std::all_of(s.begin(), s.end(), isxdigit);
}

auto string::to_lower(std::string const& input) -> std::string
{
    auto data = std::string{ input.begin(), input.end() };

    for (auto i = 0u; i < data.size(); i++)
    {
        data[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(input[i])));
    }

    return data;
}

auto string::to_code(std::string const& input) -> std::string
{
    auto data = input.substr(1, input.size() - 2);
    auto pos = usize{ 0 };

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

    while ((pos = data.find("\\\\")) != std::string::npos)
    {
        data.erase(data.begin() + pos);
    }

    return data;
}

auto string::to_literal(std::string const& input) -> std::string
{
    auto data = std::string{ input.begin(), input.end() };
    auto pos = usize{ 0 };

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

    for (pos = 0; pos < data.size(); pos++)
    {
        if (data.at(pos) == '\\')
        {
            data.insert(data.begin() + pos, '\\');
            pos += 2;
        }
        else if (data.at(pos) == '\"')
        {
            data.insert(data.begin() + pos, '\\');
            pos += 2;
        }
    }

    data.insert(data.begin(), '\"');
    data.insert(data.end(), '\"');

    return data;
}

auto string::fordslash(std::string const& s) -> std::string
{
    auto data = std::string{ s.begin(), s.end() };

    for (auto i = 0u; i < data.size(); i++)
    {
        if (data[i] == '\\') data[i] = '/';
    }

    return data;
}

auto string::backslash(std::string const& s) -> std::string
{
    auto data = std::string{ s.begin(), s.end() };

    for (auto i = 0u; i < data.size(); i++)
    {
        if (data[i] ==  '/') data[i] = '\\';
    }

    return data;
}

auto string::quote(std::string const& s, bool single) -> std::string
{
    auto data = std::string{ s.begin(), s.end() };

    if (single)
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

auto string::unquote(std::string const& s) -> std::string
{
    if (s.at(0) == '\'' || s.at(0) == '\"')
        return s.substr(1, s.size() - 2);

    return s;
}

auto string::split(std::string& str, char delimiter) -> std::vector<std::string>
{
    auto tokens = std::vector<std::string>{};
    auto ss = std::stringstream{ str };
    auto tok = std::string{};

    while (std::getline(ss, tok, delimiter))
    {
        tokens.push_back(tok);
    }

    return tokens;
}

auto string::clean_buffer_lines(std::vector<u8>& buffer) -> std::vector<std::string>
{
    auto data = std::string{ reinterpret_cast<char*>(buffer.data()), buffer.size() };
    auto pos = usize{ 0 };

    while ((pos = data.find("\t")) != std::string::npos)
    {
        data = data.replace(pos, 1, "");
    }

    while ((pos = data.find("\r")) != std::string::npos)
    {
        data = data.replace(pos, 1, "");
    }

    auto lines = std::vector<std::string>{};
    auto ss = std::stringstream{ data };
    auto tok = std::string{};

    while (std::getline(ss, tok, '\n'))
    {
        lines.push_back(tok);
    }

    return lines;
}

auto string::parse_code(std::string& line) -> std::vector<std::string>
{
    auto data = std::vector<std::string>{};
    auto exp = std::regex{ R"(([_A-Za-z0-9\-]+|\"(?:\\.|[^\"])*?\"|\'(?:\\.|[^\'])*?\')(?:\s+|$))" };

    for (auto i = std::sregex_iterator{ line.begin(), line.end(), exp }; i != std::sregex_iterator{}; ++i)
    {
        data.push_back(i->format("$1"));
    }

    return data;
}

auto string::float_string(float value, bool toint) -> std::string
{
    enum flags_t : u8 { none = 0, negative = 1, integer = 2, has_exp = 4, exp_neg = 8 };

    auto str = utils::string::va("%g", value);

    auto flags = integer | (str[0] == '-' ? negative : none);

    for (auto i = 1u; i < str.size(); i++)
    {
        if (str[i] == '-') flags |= exp_neg;
        else if (str[i] == 'e') flags |= has_exp;
        else if ( str[i] == '.') flags &= ~integer;
    }

    if (!(flags & has_exp))
        return str += ((flags & integer) && !toint) ? ".0" : "";

    std::string p_int;
    std::string p_dec;
    std::string p_exp;

    if (flags & integer)
    {
        auto i = (flags & negative) ? 1u : 0u;

        while (str[i] != 'e')
            p_int.push_back(str[i++]);

        i += 2;

        while (i < str.size())
            p_exp.push_back(str[i++]);

        auto offset = usize{ std::stoul(p_exp) };

        if ((flags & exp_neg))
            offset -= p_int.size();

        while (offset--)
        {
            if ((flags & exp_neg))
                p_int.insert(p_int.begin(), '0');
            else
                p_int.push_back('0');
        }

        return ((flags & negative) ? "-" : "") + ((flags & exp_neg) ? "0." + p_int : p_int + ".0");
    }
    else
    {
        auto i = (flags & negative) ? 1u : 0u;

        while (str[i] != '.')
            p_int.push_back(str[i++]);

        i++;

        while (str[i] != 'e')
            p_dec.push_back(str[i++]);

        i += 2;

        while (i < str.size())
            p_exp.push_back(str[i++]);

        auto offset = usize{ std::stoul(p_exp) };

        offset -= (flags & exp_neg) ? p_int.size() : p_dec.size();

        while (offset--)
        {
            if (flags & exp_neg)
                p_int.insert(p_int.begin(), '0');
            else
                p_dec.push_back('0');
        }

        return ((flags & negative) ? "-" : "") + ((flags & exp_neg) ? "0." + p_int + p_dec : p_int + p_dec + ".0");
    }
}

} // namespace xsk::utils
