// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW7_RESOLVER_HPP_
#define _GSC_IW7_RESOLVER_HPP_

namespace IW7
{

enum class opcode : std::uint8_t;

class resolver
{
    static std::unordered_map<opcode, std::string> opcode_map;
    static std::unordered_map<std::uint16_t, std::string> builtin_function_map;
    static std::unordered_map<std::uint16_t, std::string> builtin_method_map;
    static std::unordered_map<std::uint32_t, std::string> file_map;
    static std::unordered_map<std::uint32_t, std::string> token_map;

public:
    static auto opcode_id(const std::string& name) -> opcode;
    static auto opcode_name(opcode id) -> std::string;

    static auto builtin_func_id(const std::string& name) -> std::uint16_t;
    static auto builtin_func_name(std::uint16_t id) -> std::string;

    static auto builtin_method_id(const std::string& name) -> std::uint16_t;
    static auto builtin_method_name(std::uint16_t id) -> std::string;

    static auto file_id(const std::string& name) -> std::uint32_t;
    static auto file_name(std::uint32_t id) -> std::string;

    static auto token_id(const std::string& name) -> std::uint32_t;
    static auto token_name(std::uint32_t id) -> std::string;

    static auto find_builtin_func(const std::string& name) -> bool;
    static auto find_builtin_meth(const std::string& name) -> bool;
};

} // namespace IW7

#endif // _GSC_IW7_RESOLVER_HPP_
