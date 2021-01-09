// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW8.hpp"

namespace IW8
{

std::unordered_map<std::uint8_t, std::string> opcode_map;
std::unordered_map<std::uint16_t, std::string> function_map;
std::unordered_map<std::uint16_t, std::string> method_map;
std::unordered_map<std::uint16_t, std::string> file_map;
std::unordered_map<std::uint16_t, std::string> token_map;

auto resolver::opcode_id(const std::string& name) -> std::uint8_t
{
    for (auto& opcode : opcode_map)
    {
        if (opcode.second == name)
        {
            return opcode.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve opcode id for name '%s'!", name.data());
    return 0xFF;
}

auto resolver::opcode_name(std::uint8_t id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve opcode name for id '0x%hhX'!", id);
    return "";
}

auto resolver::function_id(const std::string& name) -> std::uint16_t
{
    for (auto& func : function_map)
    {
        if (func.second == name)
        {
            return func.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve builtin function id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::function_name(std::uint16_t id) -> std::string
{
    const auto itr = function_map.find(id);

    if (itr != function_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve builtin function name for id '%i'!", id);
    return utils::string::va("_ID%i", id);
}

auto resolver::method_id(const std::string& name) -> std::uint16_t
{
    for (auto& method : method_map)
    {
        if (method.second == name)
        {
            return method.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve builtin method id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::method_name(std::uint16_t id) -> std::string
{
    const auto itr = method_map.find(id);

    if (itr != method_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve builtin method name for id '%i'!", id);
    return utils::string::va("_ID%i", id);
}

auto resolver::file_id(const std::string& name) -> std::uint32_t
{
    for (auto& file : file_map)
    {
        if (file.second == name)
        {
            return file.first;
        }
    }

    return 0;
}

auto resolver::file_name(std::uint32_t id) -> std::string
{
    const auto itr = file_map.find(id);

    if (itr != file_map.end())
    {
        return itr->second;
    }

    GSC_LOG_DEBUG("missing file name for id '%i'!", id);
    return utils::string::va("_ID%i", id);
}

auto resolver::token_id(const std::string& name) -> std::uint32_t
{
    for (auto& token : token_map)
    {
        if (utils::string::to_lower(token.second) == name)
        {
            return token.first;
        }
    }

    return 0;
}

auto resolver::token_name(std::uint32_t id) -> std::string
{
    const auto itr = token_map.find(id);

    if (itr != token_map.end())
    {
        return itr->second;
    }

    return utils::string::va("_ID%i", id);
}

auto resolver::find_function(const std::string& name) -> bool
{
    for (auto& func : function_map)
    {
        if (func.second == name)
        {
            return true;
        }
    }

    return false;
}

auto resolver::find_method(const std::string& name) -> bool
{
    for (auto& method : method_map)
    {
        if (method.second == name)
        {
            return true;
        }
    }

    return false;
}

#define CODE_LIST_SIZE 153
#define FUNC_LIST_SIZE 0
#define METH_LIST_SIZE 0
#define FILE_LIST_SIZE 0
#define TOKN_LIST_SIZE 0

const gsc::pair_8_str opcode_list[]
{
    { 0, "DUMMY" },
};

const gsc::pair_16_str function_list[]
{
    { 0, "DUMMY" },
};

const gsc::pair_16_str method_list[]
{
    { 0, "DUMMY" },
};

const gsc::pair_32_str file_list[]
{
    { 0, "DUMMY" },
};

const gsc::pair_32_str token_list[]
{
    { 0, "DUMMY" },
};

struct __init__
{
    __init__()
    {
        static bool init = false;
        if(init) return;
        init = true;

        for(auto i = 0; i < CODE_LIST_SIZE; i++)
        {
            opcode_map.insert({ opcode_list[i].key, opcode_list[i].value });
        }

        for(auto i = 0; i < FUNC_LIST_SIZE; i++)
        {
            function_map.insert({ function_list[i].key, function_list[i].value });
        }

        for(auto i = 0; i < METH_LIST_SIZE; i++)
        {
            method_map.insert({ method_list[i].key, method_list[i].value });
        }

        for(auto i = 0; i < FILE_LIST_SIZE; i++)
        {
            file_map.insert({ file_list[i].key, file_list[i].value });
        }

        for(auto i = 0; i < TOKN_LIST_SIZE; i++)
        {
            token_map.insert({ token_list[i].key,  token_list[i].value });
        }
    }
};

static __init__ _;

} // namespace IW8
