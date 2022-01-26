// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "iw6.hpp"

namespace xsk::gsc::iw6
{

enum class keyword;

struct buffer
{
    int size;
    int length;
    char* data;

    buffer();
    ~buffer();
    bool push(char c);
};

struct reader
{
    enum states { end, ok };

    states state;
    int bytes_remaining;
    const char* buffer_pos;
    char last_byte;
    char current_byte;

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
private:
    reader reader_;
    buffer buffer_;
    location loc_;
    build mode_;
    bool in_dev_state_;
    std::stack<location> locs_;
    std::stack<reader> readers_;
    std::uint32_t header_top_;

public:
    lexer(const std::string& name, const char* data, size_t size);
    auto lex() -> xsk::gsc::iw6::parser::symbol_type;
    void push_header(const std::string& file);
    void pop_header();
    void restrict_header(const xsk::gsc::location& loc);

private:
    auto read_string(char quote, bool localize) -> xsk::gsc::iw6::parser::symbol_type;
    auto read_number(char first) -> xsk::gsc::iw6::parser::symbol_type;
    auto read_word(char first) -> xsk::gsc::iw6::parser::symbol_type;
    auto read_dotsize() -> xsk::gsc::iw6::parser::symbol_type;
    auto keyword_token(keyword k) -> xsk::gsc::iw6::parser::symbol_type;
    static auto keyword_is_token(keyword k) -> bool;
    static auto get_keyword(std::string_view str) -> keyword;

    static std::unordered_map<std::string_view, keyword> keywords;
};

} // namespace xsk::gsc::iw6
