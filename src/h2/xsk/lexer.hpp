// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::h2
{

enum class keyword;

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
    build mode_;
    std::stack<location> locs_;
    std::stack<reader> readers_;
    std::uint32_t header_top_;
    state state_;
    bool indev_;

public:
    lexer(const std::string& name, const char* data, size_t size);
    auto lex() -> xsk::gsc::h2::parser::symbol_type;
    void push_header(const std::string& file);
    void pop_header();
    void restrict_header(const xsk::gsc::location& loc);

private:
    auto keyword_token(keyword k) -> xsk::gsc::h2::parser::symbol_type;
    static auto keyword_is_token(keyword k) -> bool;
    static auto get_keyword(std::string_view str) -> keyword;

    static std::unordered_map<std::string_view, keyword> keywords;
};

} // namespace xsk::gsc::h2
