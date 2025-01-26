// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct define
{
    enum kind : u8 { PLAIN, BUILTIN, OBJECT, FUNCTION };

    kind type;
//  bool vararg;
    std::vector<token> args;
    std::vector<token> exp;
};

} // namespace xsk::gsc
