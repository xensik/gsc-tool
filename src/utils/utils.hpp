// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_UTILS_HPP_
#define _GSC_UTILS_HPP_

// Warnings
#ifdef _WIN32
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4005)
#pragma warning(disable:4065)
#define _CRT_SECURE_NO_WARNINGS
#endif

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
#include <filesystem>
#include <stdio.h>

// Ext
using namespace std::literals;

// Utility
#include "utility/log.hpp"
#include "utility/string.hpp"
#include "utility/file.hpp"
#include "utility/byte_buffer.hpp"

// GSC Types
#include "types/assembly.hpp"
#include "types/nodetree.hpp"
#include "types/context.hpp"

// GSC Interfaces
#include "interfaces/assembler.hpp"
#include "interfaces/disassembler.hpp"
#include "interfaces/compiler.hpp"
#include "interfaces/decompiler.hpp"

#endif // _GSC_UTILS_HPP_
