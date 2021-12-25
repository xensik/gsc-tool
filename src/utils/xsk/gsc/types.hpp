// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

enum class build
{
	dev,
	prod,
};

enum class abort_t
{
    abort_none = 0,
    abort_continue = 1,
    abort_break = 2,
    abort_return = 3,
};

struct source
{
    std::string name;
    std::vector<std::uint8_t> buf;
};

struct context
{
    using ptr = std::unique_ptr<context>;

    void* scanner;
    std::uint32_t header_top;
    xsk::gsc::build mode;
    xsk::gsc::location loc;
    std::stack<xsk::gsc::location> locs;
    std::vector<xsk::gsc::source>* sources;
    std::function<std::vector<std::uint8_t>(const std::string&)> read_callback;

    void restrict_header(const xsk::gsc::location& loc);
};

struct include_t
{
    std::string name;
    std::vector<std::string> funcs;

    include_t(const std::string& name, const std::vector<std::string>& funcs) : name(name), funcs(funcs) {}
};

struct animtree_t
{
    std::string name;
    bool loaded;
};

struct instruction
{
    using ptr = std::unique_ptr<instruction>;

    std::uint32_t index;
    std::uint32_t size;
    std::uint8_t opcode;
    std::vector<std::string> data;

    instruction() : index(0), size(0), opcode(0xFF) {}
};

struct function
{
    using ptr = std::unique_ptr<function>;

    std::uint32_t index;
    std::uint32_t size;
    std::uint32_t id;
    std::string name;
    std::vector<instruction::ptr> instructions;
    std::unordered_map<std::uint32_t, std::string> labels;

    function() : index(0), size(0), id(0) {}
};

struct pair_8C
{
    std::uint8_t key;
    const char* value;
};

struct pair_16C
{
    std::uint16_t key;
    const char* value;
};

struct pair_32C
{
    std::uint32_t key;
    const char* value;
};

} // namespace xsk::gsc
