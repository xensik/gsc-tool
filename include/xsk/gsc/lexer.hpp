// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/gsc/common/types.hpp"

namespace xsk::gsc
{

struct lexer
{
private:
    context const* ctx_;
    lookahead reader_;
    location loc_;
    usize buflen_;
    spacing spacing_;
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
