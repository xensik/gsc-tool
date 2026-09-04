// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

#include <catch_amalgamated.hpp>

using namespace xsk;

TEST_CASE("iw5 pc: animation reference width", "[gsc][iw5]")
{
    gsc::context legacy(gsc::feature::none, gsc::engine::iw5, gsc::endian::little,
        gsc::system::pc, gsc::instance::server, 0);
    gsc::context x64(gsc::feature::anim4, gsc::engine::iw5, gsc::endian::little,
        gsc::system::pc, gsc::instance::server, 0);

    CHECK(legacy.opcode_size(gsc::opcode::OP_GetAnimation) == 5);
    CHECK(x64.opcode_size(gsc::opcode::OP_GetAnimation) == 9);
}
