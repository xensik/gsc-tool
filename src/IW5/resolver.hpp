// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW5_RESOLVER_H_
#define _GSC_IW5_RESOLVER_H_

namespace IW5
{

enum class opcode : std::uint8_t;

class resolver
{
    static std::unordered_map<std::string, opcode> opcode_map;
    static std::unordered_map<std::string, std::uint16_t> builtin_function_map;
    static std::unordered_map<std::string, std::uint16_t> builtin_method_map;
    static std::unordered_map<std::string, std::uint16_t> file_map;
    static std::unordered_map<std::string, std::uint16_t> token_map;

public:
    static auto opcode_id(const std::string& name)->opcode;
    static auto opcode_name(opcode id)->std::string;

    static auto builtin_func_id(const std::string& name)->std::uint16_t;
    static auto builtin_func_name(std::uint16_t id)->std::string;

    static auto builtin_method_id(const std::string& name)->std::uint16_t;
    static auto builtin_method_name(std::uint16_t id)->std::string;

    static auto file_id(const std::string& name)->std::uint16_t;
    static auto file_name(std::uint16_t id)->std::string;

    static auto token_id(const std::string& name)->std::uint16_t;
    static auto token_name(std::uint16_t id)->std::string;
};

} // namespace IW5

#endif _GSC_IW5_RESOLVER_H_
