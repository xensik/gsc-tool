// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "misc/types.hpp"
#include "parser.hpp"

namespace xsk::gsc
{

constexpr usize max_buf_size = 0x2000;

struct charbuf
{
    char* data;
    usize length;

    charbuf();
    ~charbuf();
    auto push(char c) -> bool;
};

struct reader
{
    enum state_type : u8 { end, ok };

    char const* buffer_pos;
    u32 bytes_remaining;
    char last_byte;
    char current_byte;
    state_type state;

    reader();

    reader(reader const& obj)
    {
        std::memcpy(this, &obj, sizeof(reader));
    }

    reader& operator=(reader const& obj)
    {
        std::memcpy(this, &obj, sizeof(reader));
        return *this;
    }

    auto init(char const* data, usize size) -> void;
    auto advance() -> void;
};

class lexer
{
    enum class state : u8 { start, string, localize, preprocessor };

    context const* ctx_;
    reader reader_;
    charbuf buffer_;
    location loc_;
    std::stack<location> locs_;
    std::stack<reader> readers_;
    u32 header_top_;
    state state_;
    bool indev_;
    bool clean_;

public:
    lexer(context const* ctx, std::string const& name, char const* data, usize size);
    auto lex() -> parser::symbol_type;
    auto push_header(std::string const& file) -> void;
    auto pop_header() -> void;
    auto ban_header(location const& loc) -> void;

private:
    auto advance() -> void;
    auto preprocessor_wrap() -> void;
    auto preprocessor_run(parser::token::token_kind_type token) -> void;
};

} // namespace xsk::gsc
