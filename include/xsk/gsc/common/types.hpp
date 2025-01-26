// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/gsc/common/asset.hpp"
#include "xsk/gsc/common/scope.hpp"
#include "xsk/gsc/common/buffer.hpp"
#include "xsk/gsc/common/assembly.hpp"
#include "xsk/gsc/common/location.hpp"
#include "xsk/gsc/common/exception.hpp"
#include "xsk/gsc/common/lookahead.hpp"
#include "xsk/gsc/common/directive.hpp"
#include "xsk/gsc/common/space.hpp"
#include "xsk/gsc/common/token.hpp"
#include "xsk/gsc/common/define.hpp"
#include "xsk/gsc/common/ast.hpp"

namespace xsk::gsc
{

enum class instance : u8
{
    server,
    client,
};

enum class build : u8
{
    prod       = 0,
    dev_blocks = 1 << 0,
    dev_maps   = 1 << 1,
    dev        = dev_blocks | dev_maps,
};

inline build operator&(build lhs, build rhs)
{
    return static_cast<build>(static_cast<std::underlying_type<build>::type>(lhs) & static_cast<std::underlying_type<build>::type>(rhs));
}

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
        none       = 0,
        str4       = 1 << 0,  // strings size 4
        tok4       = 1 << 1,  // tokenid size 4
        waitframe  = 1 << 2,  // waitframe opcode
        params     = 1 << 3,  // packed func params
        boolfuncs  = 1 << 4,  // isdefined, istrue
        boolnotand = 1 << 5,  // !&& expr opcode
        offs8      = 1 << 6,  // offset shift by 8
        offs9      = 1 << 7,  // offset shift by 9
        extension  = 1 << 8,  // s4 extension
        hash       = 1 << 9,  // iw9 identifiers
        farcall    = 1 << 10, // iw9 new call system
        foreach    = 1 << 11, // iw9 foreach
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

struct context;

} // namespace xsk::gsc
