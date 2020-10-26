// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_TOOL_STDINC_H_
#define _GSC_TOOL_STDINC_H_

#include <utils.hpp>
#include <IW5.hpp>
#include <IW6.hpp>
#include <SH1.hpp>

#include <filesystem>

#ifdef DEV_DEBUG
#define IDAOUT true
#else
#define IDAOUT false
#endif

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
    SH1,

};

#endif // _GSC_TOOL_STDINC_H_
