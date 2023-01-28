// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "misc/types.hpp"

namespace xsk::gsc
{

class lexer
{
    enum class state : u8 { start, string, localize };

    context const* ctx_;
    lookahead reader_;
    location loc_;
    usize buflen_;
    spacing spacing_;
    state state_;
    bool indev_;
    std::array<char, 0x1000> buffer_;

public:
    lexer(context const* ctx, std::string const& name, char const* data, usize size);
    auto lex() -> token;

private:
    auto push(char c) -> void;
    auto advance() -> void;
    auto linewrap() -> void;
};

} // namespace xsk::gsc
