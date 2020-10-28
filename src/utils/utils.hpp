// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_UTILS_H_
#define _GSC_UTILS_H_

// Warnings
#define _CRT_SECURE_NO_WARNINGS

// C/C++
#include <stack>
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

// Ext
using namespace std::literals;

// Utility
#include "utility/log.hpp"
#include "utility/string.hpp"
#include "utility/file.hpp"
#include "utility/byte_buffer.hpp"

// GSC Types
#include "types/statement.hpp"
#include "types/function.hpp"
#include "types/instruction.hpp"

// GSC Interfaces
#include "interfaces/assembler.hpp"
#include "interfaces/disassembler.hpp"
#include "interfaces/compiler.hpp"
#include "interfaces/decompiler.hpp"


#include "types/nodes/node.hpp"

#endif // _GSC_UTILS_H_
