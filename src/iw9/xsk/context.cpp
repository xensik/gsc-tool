// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "iw9.hpp"

namespace xsk::gsc::iw9
{

void context::init(build, read_cb_type callback)
{
    resolver::init(callback);
}

void context::cleanup()
{
    resolver::cleanup();
}

} // namespace xsk::gsc::iw9
