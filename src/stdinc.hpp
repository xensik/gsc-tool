// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _XSK_STDINC_H_
#define _XSK_STDINC_H_

#define IW5

// Warnings
#define _CRT_SECURE_NO_WARNINGS

// Windows
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// C/C++
#include <array>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <stdio.h>
#include <tchar.h>

// Ext
using namespace std::literals;

// Utility
#include "utils/log.hpp"
#include "utils/string.hpp"
#include "utils/file.hpp"
#include "utils/byte_buffer.hpp"

// Engine
#ifdef IW5
#include "iw5/iw5.hpp"
using namespace iw5;

#elif defined IW6
#include "iw6/iw6.hpp"
using namespace iw6;

#else
#error "no game specified"
#endif

// GSC
#include "gsc/common/function.hpp"
#include "gsc/common/instruction.hpp"
#include "gsc/common/statement.hpp"
#include "gsc/assembler.hpp"
#include "gsc/disassembler.hpp"
#include "gsc/compiler.hpp"
#include "gsc/decompiler.hpp"

#endif // _XSK_STDINC_H_
