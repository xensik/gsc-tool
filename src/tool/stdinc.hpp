// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_TOOL_STDINC_HPP_
#define _GSC_TOOL_STDINC_HPP_

#include <utils.hpp>
#include <IW5.hpp>
#include <IW6.hpp>
#include <S1.hpp>
#include <S2.hpp>
#include <H1.hpp>
#include <H2.hpp>

enum class mode
{
    __,
    ASM,
    DISASM,
    COMP,
    DECOMP,
};

enum class game
{
    __,
    IW5,
    IW6,
    S1,
    S2,
    H1,
    H2,

};

#endif // _GSC_TOOL_STDINC_HPP_
