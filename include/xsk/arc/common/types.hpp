// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/arc/common/asset.hpp"
#include "xsk/arc/common/assembly.hpp"
#include "xsk/arc/common/buffer.hpp"
#include "xsk/arc/common/location.hpp"
#include "xsk/arc/common/exception.hpp"
#include "xsk/arc/common/lookahead.hpp"
#include "xsk/arc/common/directive.hpp"
#include "xsk/arc/common/scope.hpp"
#include "xsk/arc/common/space.hpp"
#include "xsk/arc/common/token.hpp"
#include "xsk/arc/common/define.hpp"
#include "xsk/arc/common/ast.hpp"

namespace xsk::arc
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

inline auto operator&(build lhs, build rhs) -> build
{
    return static_cast<build>(static_cast<std::underlying_type_t<build>>(lhs) & static_cast<std::underlying_type_t<build>>(rhs));
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
    ps4,
    ps5,
    xb2,
    xb3,
    xb4,
    wiiu,
};

enum class engine : u8
{
    t6,
    t7,
    t8,
    t9,
    jup
};

struct feature
{
    enum values : u32
    {
        none     = 0,
        v2       = 1 << 0,
        v3       = 1 << 1,
        header64 = 1 << 2,
        header72 = 1 << 3,
        headerxx = 1 << 4,
        size64   = 1 << 5,
        hashids  = 1 << 6,
        devstr   = 1 << 7,
        spaces   = 1 << 8,
        globals  = 1 << 9,
        refvarg  = 1 << 10,
        foreach  = 1 << 11,
    };

    feature(values value) : value_(value) {}
    operator values() { return value_; }
    operator bool() { return value_ != values::none; }
    auto operator|(feature::values rhs) const -> feature::values { return (value_ | rhs); }
    auto operator&(feature::values rhs) const -> feature::values { return (value_ & rhs); }

    friend auto operator|(feature::values lhs, feature::values rhs) -> feature::values
    {
        return static_cast<feature::values>(static_cast<std::underlying_type_t<feature::values>>(lhs) | static_cast<std::underlying_type_t<feature::values>>(rhs));
    }

    friend auto operator&(feature::values lhs, feature::values rhs) -> feature::values
    {
        return static_cast<feature::values>(static_cast<std::underlying_type_t<feature::values>>(lhs) & static_cast<std::underlying_type_t<feature::values>>(rhs));
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

struct locjmp
{
    std::string end;
    std::string cnt;
    std::string brk;
    bool is_dev{};
    bool is_switch{};
};

// fordward decl for modules ref
struct context;

} // namespace xsk::arc
