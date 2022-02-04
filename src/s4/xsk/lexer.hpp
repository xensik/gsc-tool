// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::s4
{

constexpr size_t max_buf_size = 0x2000;

struct buffer
{
    char* data;
    int length;

    buffer();
    ~buffer();
    bool push(char c);
};

struct reader
{
    enum state_type : std::uint8_t { end, ok };

    const char* buffer_pos;
    std::uint32_t bytes_remaining;
    char last_byte;
    char current_byte;
    state_type state;

    reader();

    reader& operator=(const reader& r)
    {
        std::memcpy(this, &r, sizeof(reader));
        return *this;
    }

    void init(const char* data, size_t size);
    void advance();
};

class lexer
{
    enum class state : std::uint8_t { start, string, localize, field, preprocessor };

    reader reader_;
    buffer buffer_;
    location loc_;
    std::stack<location> locs_;
    std::stack<reader> readers_;
    std::uint32_t header_top_;
    state state_;
    build mode_;
    bool indev_;
    bool clean_;

public:
    lexer(const std::string& name, const char* data, size_t size);
    auto lex() -> parser::symbol_type;
    void push_header(const std::string& file);
    void pop_header();
    void ban_header(const location& loc);

private:
    void advance();
    void preprocessor(parser::token::token_kind_type token);
};

} // namespace xsk::gsc::s4
