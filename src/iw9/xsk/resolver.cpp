// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "iw9.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4244)
#endif

namespace xsk::gsc::iw9
{

std::unordered_map<std::uint8_t, std::string_view> opcode_map;
std::unordered_map<std::uint16_t, std::string_view> function_map;
std::unordered_map<std::uint16_t, std::string_view> method_map;
std::unordered_map<std::uint32_t, std::string_view> token_map;
std::unordered_map<std::string_view, std::uint8_t> opcode_map_rev;
std::unordered_map<std::string_view, std::uint16_t> function_map_rev;
std::unordered_map<std::string_view, std::uint16_t> method_map_rev;
std::unordered_map<std::string_view, std::uint32_t> token_map_rev;
std::unordered_map<std::string, std::vector<std::uint8_t>> files;
read_cb_type read_callback = nullptr;
std::set<std::string> string_map;

void resolver::init(read_cb_type callback)
{
    read_callback = callback;
}

void resolver::cleanup()
{
    files.clear();
}

auto resolver::opcode_id(const std::string& name) -> std::uint8_t
{
    const auto itr = opcode_map_rev.find(name);

    if (itr != opcode_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("couldn't resolve opcode id for name '%s'!", name.data()));
}

auto resolver::opcode_name(std::uint8_t id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return std::string(itr->second);
    }

    throw error(utils::string::va("couldn't resolve opcode name for id '0x%hhX'!", id));
}

auto resolver::function_id(const std::string& name) -> std::uint16_t
{
    if (name.starts_with("_func_"))
    {
        return static_cast<std::uint16_t>(std::stoul(name.substr(6), nullptr, 16));
    }

    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("couldn't resolve builtin function id for name '%s'!", name.data()));
}

auto resolver::function_name(std::uint16_t id) -> std::string
{
    const auto itr = function_map.find(id);

    if (itr != function_map.end())
    {
        return std::string(itr->second);
    }

    return utils::string::va("_func_%04X", id);
}

auto resolver::method_id(const std::string& name) -> std::uint16_t
{
    if (name.starts_with("_meth_"))
    {
        return static_cast<std::uint16_t>(std::stoul(name.substr(6), nullptr, 16));
    }

    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("couldn't resolve builtin method id for name '%s'!", name.data()));
}

auto resolver::method_name(std::uint16_t id) -> std::string
{
    const auto itr = method_map.find(id);

    if (itr != method_map.end())
    {
        return std::string(itr->second);
    }

    return utils::string::va("_meth_%04X", id);
}

auto resolver::token_id(const std::string& name) -> std::uint32_t
{
    if (name.starts_with("_id_"))
    {
        return static_cast<std::uint32_t>(std::stoul(name.substr(4), nullptr, 16));
    }

    const auto itr = token_map_rev.find(name);

    if (itr != token_map_rev.end())
    {
        return itr->second;
    }

    return 0;
}

auto resolver::token_name(std::uint32_t id) -> std::string
{
    const auto itr = token_map.find(id);

    if (itr != token_map.end())
    {
        return std::string(itr->second);
    }

    return utils::string::va("_id_%04X", id);
}

auto resolver::find_function(const std::string& name) -> bool
{
    if (name.starts_with("_func_")) return true;

    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        return true;
    }

    return false;
}

auto resolver::find_method(const std::string& name) -> bool
{
    if (name.starts_with("_meth_")) return true;

    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        return true;
    }

    return false;
}

void resolver::add_function(const std::string& name, std::uint16_t id)
{
    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        throw error(utils::string::va("builtin function '%s' already defined.", name.data()));
    }

    const auto str = string_map.find(name);

    if (str != string_map.end())
    {
        function_map.insert({ id, *str });
        function_map_rev.insert({ *str, id });
    }
    else
    {
        auto ins = string_map.insert(name);

        if (ins.second)
        {
            function_map.insert({ id, *ins.first });
            function_map_rev.insert({ *ins.first, id });
        }
    }
}

void resolver::add_method(const std::string& name, std::uint16_t id)
{
    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        throw error(utils::string::va("builtin method '%s' already defined.", name.data()));
    }

    const auto str = string_map.find(name);

    if (str != string_map.end())
    {
        method_map.insert({ id, *str });
        method_map_rev.insert({ *str, id });
    }
    else
    {
        auto ins = string_map.insert(name);

        if (ins.second)
        {
            method_map.insert({ id, *ins.first });
            method_map_rev.insert({ *ins.first, id });
        }
    }
}

auto resolver::make_token(std::string_view str) -> std::string
{
    if (str.starts_with("_id_") || str.starts_with("_func_") || str.starts_with("_meth_"))
    {
        return std::string(str);
    }

    auto data = std::string(str.begin(), str.end());

    for (std::size_t i = 0; i < data.size(); i++)
    {
        data[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
        if (data[i] == '\\') data[i] = '/';
    }

    return data;
}

auto resolver::file_data(const std::string& name) -> std::tuple<const std::string*, const char*, size_t>
{
    const auto itr = files.find(name);

    if (itr != files.end())
    {
        return { &itr->first ,reinterpret_cast<const char*>(itr->second.data()), itr->second.size() };
    }

    auto data = read_callback(name);

    const auto res = files.insert({ name, std::move(data)});

    if (res.second)
    {
        return { &res.first->first, reinterpret_cast<const char*>(res.first->second.data()), res.first->second.size() };
    }

    throw error("couldn't open gsc file '" + name + "'");
}

std::set<std::string_view> paths
{
};

auto resolver::fs_to_game_path(const std::filesystem::path& file) -> std::filesystem::path
{
    auto result = std::filesystem::path();
    auto root = false;

    for (auto& entry : file)
    {
        if (!root && paths.contains(entry.string()))
        {
            result = entry;
            root = true;
        }
        else if (paths.contains(result.string()))
        {
            result /= entry;
        }
    }

    return result.empty() ? file : result;
}

const std::array<std::pair<std::uint8_t, const char*>, 167> opcode_list
{{
    { 0x00, "unk_000" },
    { 0x01, "unk_001" },
    { 0x02, "unk_002" },
    { 0x03, "unk_003" },
    { 0x04, "unk_004" },
    { 0x05, "unk_005" },
    { 0x06, "unk_006" },
    { 0x07, "unk_007" },
    { 0x08, "unk_008" },
    { 0x09, "unk_009" },
    { 0x0A, "unk_010" },
    { 0x0B, "unk_011" },
    { 0x0C, "unk_012" },
    { 0x0D, "unk_013" },
    { 0x0E, "unk_014" },
    { 0x0F, "unk_015" },
    { 0x10, "unk_016" },
    { 0x11, "unk_017" },
    { 0x12, "unk_018" },
    { 0x13, "unk_019" },
    { 0x14, "unk_020" },
    { 0x15, "unk_021" },
    { 0x16, "unk_022" },
    { 0x17, "unk_023" },
    { 0x18, "unk_024" },
    { 0x19, "unk_025" },
    { 0x1A, "unk_026" },
    { 0x1B, "unk_027" },
    { 0x1C, "unk_028" },
    { 0x1D, "unk_029" },
    { 0x1E, "unk_030" },
    { 0x1F, "unk_031" },
    { 0x20, "unk_032" },
    { 0x21, "unk_033" },
    { 0x22, "unk_034" },
    { 0x23, "unk_035" },
    { 0x24, "unk_036" },
    { 0x25, "unk_037" },
    { 0x26, "unk_038" },
    { 0x27, "unk_039" },
    { 0x28, "unk_040" },
    { 0x29, "unk_041" },
    { 0x2A, "unk_042" },
    { 0x2B, "unk_043" },
    { 0x2C, "unk_044" },
    { 0x2D, "unk_045" },
    { 0x2E, "unk_046" },
    { 0x2F, "unk_047" },
    { 0x30, "unk_048" },
    { 0x31, "unk_049" },
    { 0x32, "unk_050" },
    { 0x33, "unk_051" },
    { 0x34, "unk_052" },
    { 0x35, "unk_053" },
    { 0x36, "unk_054" },
    { 0x37, "unk_055" },
    { 0x38, "unk_056" },
    { 0x39, "unk_057" },
    { 0x3A, "unk_058" },
    { 0x3B, "unk_059" },
    { 0x3C, "unk_060" },
    { 0x3D, "unk_061" },
    { 0x3E, "unk_062" },
    { 0x3F, "unk_063" },
    { 0x40, "unk_064" },
    { 0x41, "unk_065" },
    { 0x42, "unk_066" },
    { 0x43, "unk_067" },
    { 0x44, "unk_068" },
    { 0x45, "unk_069" },
    { 0x46, "unk_070" },
    { 0x47, "unk_071" },
    { 0x48, "unk_072" },
    { 0x49, "unk_073" },
    { 0x4A, "unk_074" },
    { 0x4B, "unk_075" },
    { 0x4C, "unk_076" },
    { 0x4D, "unk_077" },
    { 0x4E, "unk_078" },
    { 0x4F, "unk_079" },
    { 0x50, "unk_080" },
    { 0x51, "unk_081" },
    { 0x52, "unk_082" },
    { 0x53, "unk_083" },
    { 0x54, "unk_084" },
    { 0x55, "unk_085" },
    { 0x56, "unk_086" },
    { 0x57, "unk_087" },
    { 0x58, "unk_088" },
    { 0x59, "unk_089" },
    { 0x5A, "unk_090" },
    { 0x5B, "unk_091" },
    { 0x5C, "unk_092" },
    { 0x5D, "unk_093" },
    { 0x5E, "unk_094" },
    { 0x5F, "unk_095" },
    { 0x60, "unk_096" },
    { 0x61, "unk_097" },
    { 0x62, "unk_098" },
    { 0x63, "unk_099" },
    { 0x64, "unk_100" },
    { 0x65, "unk_101" },
    { 0x66, "unk_102" },
    { 0x67, "unk_103" },
    { 0x68, "unk_104" },
    { 0x69, "unk_105" },
    { 0x6A, "unk_106" },
    { 0x6B, "unk_107" },
    { 0x6C, "unk_108" },
    { 0x6D, "unk_109" },
    { 0x6E, "unk_110" },
    { 0x6F, "unk_111" },
    { 0x70, "unk_112" },
    { 0x71, "unk_113" },
    { 0x72, "unk_114" },
    { 0x73, "unk_115" },
    { 0x74, "unk_116" },
    { 0x75, "unk_117" },
    { 0x76, "unk_118" },
    { 0x77, "unk_119" },
    { 0x78, "unk_120" },
    { 0x79, "unk_121" },
    { 0x7A, "unk_122" },
    { 0x7B, "unk_123" },
    { 0x7C, "unk_124" },
    { 0x7D, "unk_125" },
    { 0x7E, "unk_126" },
    { 0x7F, "unk_127" },
    { 0x80, "unk_128" },
    { 0x81, "unk_129" },
    { 0x82, "unk_130" },
    { 0x83, "unk_131" },
    { 0x84, "unk_132" },
    { 0x85, "unk_133" },
    { 0x86, "unk_134" },
    { 0x87, "unk_135" },
    { 0x88, "unk_136" },
    { 0x89, "unk_137" },
    { 0x8A, "unk_138" },
    { 0x8B, "unk_139" },
    { 0x8C, "unk_140" },
    { 0x8D, "unk_141" },
    { 0x8E, "unk_142" },
    { 0x8F, "unk_143" },
    { 0x90, "unk_144" },
    { 0x91, "unk_145" },
    { 0x92, "unk_146" },
    { 0x93, "unk_147" },
    { 0x94, "unk_148" },
    { 0x95, "unk_149" },
    { 0x96, "unk_150" },
    { 0x97, "unk_151" },
    { 0x98, "unk_152" },
    { 0x99, "unk_153" },
    { 0x9A, "unk_154" },
    { 0x9B, "unk_155" },
    { 0x9C, "unk_156" },
    { 0x9D, "unk_157" },
    { 0x9E, "unk_158" },
    { 0x9F, "unk_159" },
    { 0xA0, "unk_160" },
    { 0xA1, "unk_161" },
    { 0xA2, "unk_162" },
    { 0xA3, "unk_163" },
    { 0xA4, "unk_164" },
    { 0xA5, "unk_165" },
    { 0xA6, "unk_166" },
}};

const std::array<std::pair<std::uint16_t, const char*>, 0> function_list
{{
}};

const std::array<std::pair<std::uint16_t, const char*>, 0> method_list
{{
}};

const std::array<std::pair<std::uint32_t, const char*>, 0> token_list
{{
}};

struct __init__
{
    __init__()
    {
        static bool init = false;
        if (init) return;
        init = true;

        opcode_map.reserve(opcode_list.size());
        opcode_map_rev.reserve(opcode_list.size());
        function_map.reserve(function_list.size());
        function_map_rev.reserve(function_list.size());
        method_map.reserve(method_list.size());
        method_map_rev.reserve(method_list.size());
        token_map.reserve(token_list.size());
        token_map_rev.reserve(token_list.size());

        for (const auto& entry : opcode_list)
        {
            opcode_map.insert({ entry.first, entry.second });
            opcode_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : function_list)
        {
            function_map.insert({ entry.first, entry.second });
            function_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : method_list)
        {
            method_map.insert({ entry.first, entry.second });
            method_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : token_list)
        {
            token_map.insert({ entry.first, entry.second });
            token_map_rev.insert({ entry.second, entry.first });
        }
    }
};

__init__ _;

} // namespace xsk::gsc::iw8

#ifdef _MSC_VER
#pragma warning(pop)
#endif
