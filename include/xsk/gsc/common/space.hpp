// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

enum class spacing : u8
{
    none = 0, // no space between tokens
    null = 1, // token just after new line
    back = 2, // token after space
    empty = 4, // token after new line + space
};

} // namespace xsk::gsc
