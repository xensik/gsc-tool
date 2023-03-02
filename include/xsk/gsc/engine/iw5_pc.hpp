// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc::iw5_pc
{
// IW5 PC 1.9.388110
constexpr usize code_count = 153;
constexpr usize func_count = 455;
constexpr usize meth_count = 780;
constexpr usize token_count = 6306;
constexpr u32 max_string_id = 33386;

class context : public gsc::context
{
public:
    context();
};

} // namespace xsk::gsc::iw5_pc
