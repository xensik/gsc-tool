// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::s1
{

class resolver
{
public:
    static void init(read_cb_type callback);
    static void cleanup();

    static auto opcode_id(const std::string& name) -> std::uint8_t;
    static auto opcode_name(std::uint8_t id) -> std::string;

    static auto function_id(const std::string& name) -> std::uint16_t;
    static auto function_name(std::uint16_t id) -> std::string;

    static auto method_id(const std::string& name) -> std::uint16_t;
    static auto method_name(std::uint16_t id) -> std::string;

    static auto token_id(const std::string& name) -> std::uint16_t;
    static auto token_name(std::uint16_t id) -> std::string;

    static auto find_function(const std::string& name) -> bool;
    static auto find_method(const std::string& name) -> bool;

    static void add_function(const std::string& name, std::uint16_t id);
    static void add_method(const std::string& name, std::uint16_t id);

    static auto get_functions() -> std::unordered_map<std::string_view, std::uint16_t>&;
    static auto get_methods() -> std::unordered_map<std::string_view, std::uint16_t>&;

    static auto make_token(std::string_view str) -> std::string;
    static auto file_data(const std::string& name) -> std::tuple<const std::string*, const char*, size_t>;
    static auto fs_to_game_path(const std::filesystem::path& file) -> std::filesystem::path;
};

} // namespace xsk::gsc::s1
