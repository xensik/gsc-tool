// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "asset.hpp"
#include "scope.hpp"
#include "buffer.hpp"
#include "assembly.hpp"
#include "location.hpp"
#include "exception.hpp"
#include "lookahead.hpp"
#include "directive.hpp"
#include "space.hpp"
#include "token.hpp"
#include "define.hpp"
#include "ast.hpp"

namespace xsk::gsc
{

enum class build : u8
{
    dev,
    prod,
};

enum class endian : u8
{
    little,
    big,
};

enum class system : u8
{
    pc,
    ps3,
    xb2,
};

enum class engine : u8
{
    iw5,
    iw6,
    iw7,
    iw8,
    iw9,
    s1,
    s2,
    s4,
    h1,
    h2,
};

struct props
{
    enum values : u32
    {
        none       = 0 << 0,
        str4       = 1 << 0,  // strings size 4
        tok4       = 1 << 1,  // tokenid size 4
        waitframe  = 1 << 2,  // waitframe opcode
        params     = 1 << 3,  // packed func params
        boolfuncs  = 1 << 4,  // isdefined, istrue
        boolnotand = 1 << 5,  // !&& expr opcode
        offs8      = 1 << 6,  // offset shift by 8
        offs9      = 1 << 7,  // offset shift by 9
        hash       = 1 << 9,  // iw9 identifiers
        farcall    = 1 << 9,  // iw9 new call system
        foreach    = 1 << 10, // iw9 foreach
    };

    props(values value) : value_(value) {}
    operator values() { return value_; }
    operator bool() { return value_ != values::none; }
    props::values operator|(props::values rhs) const { return static_cast<props::values>(value_ | rhs); }
    props::values operator&(props::values rhs) const { return static_cast<props::values>(value_ & rhs); }

    friend props::values operator|(props::values lhs, props::values rhs)
    {
        return static_cast<props::values>(static_cast<std::underlying_type<props::values>::type>(lhs) | static_cast<std::underlying_type<props::values>::type>(rhs));
    }

    friend props::values operator&(props::values lhs, props::values rhs)
    {
        return static_cast<props::values>(static_cast<std::underlying_type<props::values>::type>(lhs) & static_cast<std::underlying_type<props::values>::type>(rhs));
    }

private:
    values value_;
};

enum class switch_type
{
    none,
    integer,
    string,
};

// fordward decl for modules ref
class context;

} // namespace xsk::gsc
