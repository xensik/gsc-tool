// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::iw6_pc
{
// IW6 PC 3.15.146
constexpr usize code_count = 153;
constexpr usize func_count = 605;
constexpr usize meth_count = 1066;
constexpr usize token_count = 17657;
constexpr u32 max_string_id = 38305;

class context : public gsc::context
{
public:
    context();
};

} // namespace xsk::gsc::iw6_pc
