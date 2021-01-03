// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW8.hpp"

namespace IW8
{

auto resolver::opcode_id(const std::string& name) -> opcode
{
    for (auto& opcode : opcode_map)
    {
        if (opcode.second == name)
        {
            return opcode.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve opcode id for name '%s'!", name.data());
    return opcode::OP_Count;
}

auto resolver::opcode_name(opcode id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve opcode name for id '0x%hhX'!", id);
    return "";
}

auto resolver::builtin_func_id(const std::string& name) -> std::uint16_t
{
    for (auto& func : builtin_function_map)
    {
        if (func.second == name)
        {
            return func.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve builtin function id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::builtin_func_name(std::uint16_t id) -> std::string
{
    const auto itr = builtin_function_map.find(id);

    if (itr != builtin_function_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve builtin function name for id '%i'!", id);
    return utils::string::va("_ID%i", id);
}

auto resolver::builtin_method_id(const std::string& name) -> std::uint16_t
{
    for (auto& method : builtin_method_map)
    {
        if (method.second == name)
        {
            return method.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve builtin method id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::builtin_method_name(std::uint16_t id) -> std::string
{
    const auto itr = builtin_method_map.find(id);

    if (itr != builtin_method_map.end())
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

auto resolver::find_builtin_func(const std::string& name) -> bool
{
    for (auto& func : builtin_function_map)
    {
        if (func.second == name)
        {
            return true;
        }
    }

    return false;
}

auto resolver::find_builtin_meth(const std::string& name) -> bool
{
    for (auto& method : builtin_method_map)
    {
        if (method.second == name)
        {
            return true;
        }
    }

    return false;
}

std::unordered_map<opcode, std::string> resolver::opcode_map
{

};

std::unordered_map<std::uint16_t, std::string> resolver::builtin_function_map
{

};

std::unordered_map<std::uint16_t, std::string> resolver::builtin_method_map
{

};

std::unordered_map<std::uint32_t, std::string> resolver::file_map
{

};

std::unordered_map<std::uint32_t, std::string> resolver::token_map
{

};

} // namespace IW8
