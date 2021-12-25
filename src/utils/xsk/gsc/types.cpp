// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"

namespace xsk::gsc
{

void context::restrict_header(const xsk::gsc::location& loc)
{
    if (header_top > 0)
    {
        throw comp_error(loc, "not allowed inside a gsh file");
    }
}

} // namespace xsk::gsc
