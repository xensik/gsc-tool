// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "s4.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4244)
#endif

namespace xsk::gsc::s4
{

std::unordered_map<std::uint8_t, std::string_view> opcode_map;
std::unordered_map<std::uint16_t, std::string_view> function_map;
std::unordered_map<std::uint16_t, std::string_view> method_map;
std::unordered_map<std::uint32_t, std::string_view> file_map;
std::unordered_map<std::uint32_t, std::string_view> token_map;
std::unordered_map<std::string_view, std::uint8_t> opcode_map_rev;
std::unordered_map<std::string_view, std::uint16_t> function_map_rev;
std::unordered_map<std::string_view, std::uint16_t> method_map_rev;
std::unordered_map<std::string_view, std::uint32_t> file_map_rev;
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

    throw error(utils::string::va("Couldn't resolve opcode id for name '%s'!", name.data()));
}

auto resolver::opcode_name(std::uint8_t id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return std::string(itr->second);
    }

    throw error(utils::string::va("Couldn't resolve opcode name for id '0x%hhX'!", id));
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

    throw error(utils::string::va("Couldn't resolve builtin function id for name '%s'!", name.data()));
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

    throw error(utils::string::va("Couldn't resolve builtin method id for name '%s'!", name.data()));
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

auto resolver::file_id(const std::string& name) -> std::uint32_t
{
    if (name.starts_with("_id_"))
    {
        return static_cast<std::uint32_t>(std::stoul(name.substr(4), nullptr, 16));
    }

    const auto itr = file_map_rev.find(name);

    if (itr != file_map_rev.end())
    {
        return itr->second;
    }

    return 0;
}

auto resolver::file_name(std::uint32_t id) -> std::string
{
    const auto itr = file_map.find(id);

    if (itr != file_map.end())
    {
        return std::string(itr->second);
    }

    return utils::string::va("_id_%04X", id);
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

auto resolver::file_data(const std::string& name) -> std::tuple<const std::string*, char*, size_t>
{
    const auto& itr = files.find(name);

    if (itr != files.end())
    {
        return { &itr->first ,reinterpret_cast<char*>(itr->second.data()), itr->second.size() };
    }

    auto data = read_callback(name);

    const auto& res = files.insert({ name, std::move(data)});

    if (res.second)
    {
        return { &res.first->first, reinterpret_cast<char*>(res.first->second.data()), res.first->second.size() };
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

const std::array<std::pair<std::uint8_t, const char*>, 190> opcode_list
{{
    { 0x00, "CAST_FIELD_OBJECT" },
    { 0x01, "SET_LOCAL_VARIABLE_FIELD_CACHED" },
    { 0x02, "PLUS" },
    { 0x03, "REMOVE_LOCAL_VARIABLES" },
    { 0x04, "EVAL_SELF_FIELD_VARIABLE_REF" },
    { 0x05, "SCRIPT_FAR_METHOD_CHILD_THREAD_CALL" },
    { 0x06, "GET_GAME_REF" },
    { 0x07, "EVAL_ANIM_FIELD_VARIABLE" },
    { 0x08, "EVAL_LEVEL_FIELD_VARIABLE_REF" },
    { 0x09, "GET_THISTHREAD" },
    { 0x0A, "GREATER" },
    { 0x0B, "WAITTILLMATCH" },
    { 0x0C, "SHIFT_RIGHT" },
    { 0x0D, "DECREMENT" },
    { 0x0E, "JUMP_ON_TRUE" },
    { 0x0F, "BIT_OR" },
    { 0x10, "EQUALITY" },
    { 0x11, "CLEAR_LOCAL_VARIABLE_FIELD_CACHED_0" },
    { 0x12, "NOTIFY" },
    { 0x13, "GET_VECTOR" },
    { 0x14, "SCRIPT_METHOD_CHILD_THREAD_CALL_POINTER" },
    { 0x15, "PRE_SCRIPT_CALL" },
    { 0x16, "GET_BYTE" },
    { 0x17, "SCRIPT_FAR_THREAD_CALL" },
    { 0x18, "SET_SELF_FIELD_VARIABLE_FIELD" },
    { 0x19, "JUMP_ON_FALSE_EXPR" },
    { 0x1A, "GET_UNDEFINED" },
    { 0x1B, "JUMP_BACK" },
    { 0x1C, "JUMP_ON_TRUE_EXPR" },
    { 0x1D, "CALL_BUILTIN_FUNC_0" },
    { 0x1E, "CALL_BUILTIN_FUNC_1" },
    { 0x1F, "CALL_BUILTIN_FUNC_2" },
    { 0x20, "CALL_BUILTIN_FUNC_3" },
    { 0x21, "CALL_BUILTIN_FUNC_4" },
    { 0x22, "CALL_BUILTIN_FUNC_5" },
    { 0x23, "CALL_BUILTIN_FUNC" },
    { 0x24, "SET_LOCAL_VARIABLE_FIELD_CACHED_0" },
    { 0x25, "CLEAR_FIELD_VARIABLE" },
    { 0x26, "GET_LEVEL" },
    { 0x27, "SIZE" },
    { 0x28, "SAFE_SET_WAITTILL_VARIABLE_FIELD_CACHED" },
    { 0x29, "SCRIPT_LOCAL_METHOD_THREAD_CALL" },
    { 0x2A, "ADD_ARRAY" },
    { 0x2B, "ENDON" },
    { 0x2C, "EVAL_FIELD_VARIABLE" },
    { 0x2D, "SHIFT_LEFT" },
    { 0x2E, "EVAL_LOCAL_ARRAY_REF_CACHED_0" },
    { 0x2F, "RETURN" },
    { 0x30, "CREATE_LOCAL_VARIABLE" },
    { 0x31, "SAFE_SET_VARIABLE_FIELD_CACHED_0" },
    { 0x32, "GET_BUILTIN_FUNCTION" },
    { 0x33, "SCRIPT_LOCAL_METHOD_CALL" },
    { 0x34, "CALL_BUILTIN_METHOD_POINTER" },
    { 0x35, "SCRIPT_LOCAL_CHILD_THREAD_CALL" },
    { 0x36, "GET_SELF_OBJECT" },
    { 0x37, "GET_GAME" },
    { 0x38, "SET_LEVEL_FIELD_VARIABLE_FIELD" },
    { 0x39, "EVAL_ARRAY" },
    { 0x3A, "GET_SELF" },
    { 0x3B, "END" },
    { 0x3C, "EVAL_SELF_FIELD_VARIABLE" },
    { 0x3D, "LESS_EQUAL" },
    { 0x3E, "EVAL_LOCAL_VARIABLE_CACHED_0" },
    { 0x3F, "EVAL_LOCAL_VARIABLE_CACHED_1" },
    { 0x40, "EVAL_LOCAL_VARIABLE_CACHED_2" },
    { 0x41, "EVAL_LOCAL_VARIABLE_CACHED_3" },
    { 0x42, "EVAL_LOCAL_VARIABLE_CACHED_4" },
    { 0x43, "EVAL_LOCAL_VARIABLE_CACHED_5" },
    { 0x44, "EVAL_LOCAL_VARIABLE_CACHED" },
    { 0x45, "EVAL_NEW_LOCAL_ARRAY_REF_CACHED_0" },
    { 0x46, "SCRIPT_CHILD_THREAD_CALL_POINTER" },
    { 0x47, "EVAL_LOCAL_VARIABLE_OBJECT_CACHED" },
    { 0x48, "SCRIPT_LOCAL_THREAD_CALL" },
    { 0x49, "GET_INTEGER" },
    { 0x4A, "SCRIPT_METHOD_CALL_POINTER" },
    { 0x4B, "CHECK_CLEAR_PARAMS" },
    { 0x4C, "SET_ANIM_FIELD_VARIABLE_FIELD" },
    { 0x4D, "WAITTILLMATCH2" },
    { 0x4E, "MINUS" },
    { 0x4F, "SCRIPT_LOCAL_FUNCTION_CALL2" },
    { 0x50, "GET_NEG_USHORT" },
    { 0x51, "GET_NEG_BYTE" },
    { 0x52, "SAFE_CREATE_VARIABLE_FIELD_CACHED" },
    { 0x53, "GREATER_EQUAL" },
    { 0x54, "VECTOR" },
    { 0x55, "GET_BUILTIN_METHOD" },
    { 0x56, "END_SWITCH" },
    { 0x57, "CLEAR_ARRAY" },
    { 0x58, "DECREMENT_TOP" },
    { 0x59, "CAST_BOOL" },
    { 0x5A, "EVAL_ARRAY_REF" },
    { 0x5B, "SET_NEW_LOCAL_VARIABLE_FIELD_CACHED_0" },
    { 0x5C, "GET_ZERO" },
    { 0x5D, "WAIT" },
    { 0x5E, "WAITTILL" },
    { 0x5F, "GET_ISTRING" },
    { 0x60, "SCRIPT_FAR_FUNCTION_CALL" },
    { 0x61, "GET_ANIM_OBJECT" },
    { 0x62, "GET_ANIMTREE" },
    { 0x63, "EVAL_LOCAL_ARRAY_CACHED" },
    { 0x64, "MOD" },
    { 0x65, "SCRIPT_FAR_METHOD_THREAD_CALL" },
    { 0x66, "GET_USHORT" },
    { 0x67, "CLEAR_PARAMS" },
    { 0x68, "SCRIPT_METHOD_THREAD_CALL_POINTER" },
    { 0x69, "SCRIPT_FUNCTION_CALL_POINTER" },
    { 0x6A, "EMPTY_ARRAY" },
    { 0x6B, "SAFE_SET_VARIABLE_FIELD_CACHED" },
    { 0x6C, "CLEAR_VARIABLE_FIELD" },
    { 0x6D, "EVAL_FIELD_VARIABLE_REF" },
    { 0x6E, "SCRIPT_LOCAL_METHOD_CHILD_THREAD_CALL" },
    { 0x6F, "EVAL_NEW_LOCAL_VARIABLE_REF_CACHED_0" },
    { 0x70, "GET_FLOAT" },
    { 0x71, "EVAL_LOCAL_VARIABLE_REF_CACHED" },
    { 0x72, "JUMP_ON_FALSE" },
    { 0x73, "BOOL_COMPLEMENT" },
    { 0x74, "SCRIPT_THREAD_CALL_POINTER" },
    { 0x75, "SCRIPT_FAR_FUNCTION_CALL2" },
    { 0x76, "LESS" },
    { 0x77, "BOOL_NOT" },
    { 0x78, "WAITTILLFRAMEEND" },
    { 0x79, "WAITFRAME" },
    { 0x7A, "GET_STRING" },
    { 0x7B, "EVAL_LEVEL_FIELD_VARIABLE" },
    { 0x7C, "GET_LEVEL_OBJECT" },
    { 0x7D, "INCREMENT" },
    { 0x7E, "CALL_BUILTIN_METHOD_0" },
    { 0x7F, "CALL_BUILTIN_METHOD_1" },
    { 0x80, "CALL_BUILTIN_METHOD_2" },
    { 0x81, "CALL_BUILTIN_METHOD_3" },
    { 0x82, "CALL_BUILTIN_METHOD_4" },
    { 0x83, "CALL_BUILTIN_METHOD_5" },
    { 0x84, "CALL_BUILTIN_METHOD" },
    { 0x85, "GET_ANIM" },
    { 0x86, "SWITCH" },
    { 0x87, "SET_VARIABLE_FIELD" },
    { 0x88, "DIV" },
    { 0x89, "GET_LOCAL_FUNCTION" },
    { 0x8A, "SCRIPT_FAR_CHILD_THREAD_CALL" },
    { 0x8B, "MUL" },
    { 0x8C, "CLEAR_LOCAL_VARIABLE_FIELD_CACHED" },
    { 0x8D, "EVAL_ANIM_FIELD_VARIABLE_REF" },
    { 0x8E, "EVAL_LOCAL_ARRAY_REF_CACHED" },
    { 0x8F, "EVAL_LOCAL_VARIABLE_REF_CACHED_0" },
    { 0x90, "BIT_AND" },
    { 0x91, "GET_ANIMATION" },
    { 0x92, "GET_FAR_FUNCTION" },
    { 0x93, "CALL_BUILTIN_POINTER" },
    { 0x94, "JUMP" },
    { 0x95, "VOIDCODEPOS" },
    { 0x96, "SCRIPT_FAR_METHOD_CALL" },
    { 0x97, "INEQUALITY" },
    { 0x98, "SCRIPT_LOCAL_FUNCTION_CALL" },
    { 0x99, "BIT_EXOR" },
    { 0x9A, "NOP" },
    { 0x9B, "ABORT" },
    { 0x9C, "OBJECT" },
    { 0x9D, "THREAD_OBJECT" },
    { 0x9E, "EVAL_LOCAL_VARIABLE" },
    { 0x9F, "EVAL_LOCAL_VARIABLE_REF" },
    { 0xA0, "PROF_BEGIN" },
    { 0xA1, "PROF_END" },
    { 0xA2, "BREAKPOINT" },
    { 0xA3, "ASSIGN_BREAKPOINT" },
    { 0xA4, "MANUAL_AND_ASSIGN_BREAKPOINT" },
    { 0xA5, "BOOL_NOT_AFTER_AND" },
    { 0xA6, "FORMAL_PARAMS" },
    { 0xA7, "IS_DEFINED" },
    { 0xA8, "IS_TRUE" },
    { 0xA9, "NATIVE_GET_LOCAL_FUNCTION" },
    { 0xAA, "NATIVE_LOCAL_FUNCTION_CALL" },
    { 0xAB, "NATIVE_LOCAL_FUNCTION_CALL2" },
    { 0xAC, "NATIVE_LOCAL_METHOD_CALL" },
    { 0xAD, "NATIVE_LOCAL_FUNCTION_THREAD_CALL" },
    { 0xAE, "NATIVE_LOCAL_METHOD_THREAD_CALL" },
    { 0xAF, "NATIVE_LOCAL_FUNCTION_CHILD_THREAD_CALL" },
    { 0xB0, "NATIVE_LOCAL_METHOD_CHILD_THREAD_CALL" },
    { 0xB1, "NATIVE_GET_FAR_FUNCTION" },
    { 0xB2, "NATIVE_FAR_FUNCTION_CALL" },
    { 0xB3, "NATIVE_FAR_FUNCTION_CALL2" },
    { 0xB4, "NATIVE_FAR_METHOD_CALL" },
    { 0xB5, "NATIVE_FAR_FUNCTION_THREAD_CALL" },
    { 0xB6, "NATIVE_FAR_METHOD_THREAD_CALL" },
    { 0xB7, "NATIVE_FAR_FUNCTION_CHILD_THREAD_CALL" },
    { 0xB8, "NATIVE_FAR_METHOD_CHILD_THREAD_CALL" },
    { 0xB9, "EVAL_NEW_LOCAL_ARRAY_REF_CACHED_0_PRECOMPILED" },
    { 0xBA, "SET_NEW_LOCAL_VARIABLE_FIELD_CACHED_0_PRECOMPILED" },
    { 0xBB, "CREATE_LOCAL_VARIABLE_PRECOMPILED" },
    { 0xBC, "SAFE_CREATE_VARIABLE_FIELD_CACHED_PRECOMPILED" },
    { 0xBD, "FORMAL_PARAMS_PRECOMPILED" },
}};

const std::array<std::pair<std::uint16_t, const char*>, 4> function_list
{{
    { 0x08F, "getdvar" },
    { 0x09B, "getfirstarraykey" },
    { 0x0B1, "getnextarraykey" },
    { 0x126, "isusingmatchrulesdata" },
}};
const std::array<std::pair<std::uint16_t, const char*>, 1> method_list
{{
    { 0x0, "null" },
}};

const std::array<std::pair<std::uint32_t, const char*>, 1> file_list
{{
    { 0x0, "null" },
}};

const std::array<std::pair<std::uint32_t, const char*>, 5> token_list
{{
    { 0x00, "" },
    { 0x01, "pl#" },
    { 0x02, "-" },
    { 0x03, "radius`" },
    { 0x04, "note:" },
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
        file_map.reserve(file_list.size());
        file_map_rev.reserve(file_list.size());
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

        for (const auto& entry : file_list)
        {
            file_map.insert({ entry.first, entry.second });
            file_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : token_list)
        {
            token_map.insert({ entry.first, entry.second });
            token_map_rev.insert({ entry.second, entry.first });
        }
    }
};

__init__ _;

} // namespace xsk::gsc::s4

#ifdef _MSC_VER
#pragma warning(pop)
#endif
