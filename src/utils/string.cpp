// Copyright 2025 xensik. All rights reserved.
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

auto string::is_number(std::string const& str) -> bool
{
    return !str.empty() && std::all_of(str.begin(), str.end(), isdigit);
}

auto string::is_hex_number(std::string const& str) -> bool
{
    return !str.empty() && std::all_of(str.begin(), str.end(), isxdigit);
}

auto string::to_lower(std::string const& str) -> std::string
{
    auto data = std::string{ str.begin(), str.end() };

    for (auto i = 0u; i < data.size(); i++)
    {
        data[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
    }

    return data;
}

auto string::to_code(std::string const& str) -> std::string
{
    auto data = str.substr(1, str.size() - 2);
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

auto string::to_literal(std::string const& str) -> std::string
{
    std::ostringstream oss;
    oss << '\"';

    for (char ch : str)
    {
        switch (ch)
        {
            case '\n': oss << "\\n"; break;
            case '\t': oss << "\\t"; break;
            case '\r': oss << "\\r"; break;
            case '\"': oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            default: oss << ch; break;
        }
    }

    oss << '\"';
    return oss.str();
}

auto string::fordslash(std::string const& str) -> std::string
{
    auto data = std::string{ str.begin(), str.end() };

    for (auto i = 0u; i < data.size(); i++)
    {
        if (data[i] == '\\') data[i] = '/';
    }

    return data;
}

auto string::backslash(std::string const& str) -> std::string
{
    auto data = std::string{ str.begin(), str.end() };

    for (auto i = 0u; i < data.size(); i++)
    {
        if (data[i] ==  '/') data[i] = '\\';
    }

    return data;
}

auto string::quote(std::string const& str, bool single) -> std::string
{
    auto data = std::string{ str.begin(), str.end() };

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

auto string::unquote(std::string const& str) -> std::string
{
    if (str.at(0) == '\'' || str.at(0) == '\"')
        return str.substr(1, str.size() - 2);

    return str;
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

auto string::clean_buffer_lines(u8 const* data, usize size) -> std::vector<std::string>
{
    auto lines = std::vector<std::string>{};
    auto current = std::string{};

    for (auto i = 0u; i < size; ++i)
    {
        auto c = data[i];
        if (c == '\n')
        {
            lines.push_back(current);
            current.clear();
        }
        else if (c != '\t' && c != '\r')
            current += c;
    }

    if (!current.empty())
        lines.push_back(current);

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

    auto str = std::format("{:g}", value);

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
