// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _XSK_GSC_TOOL_H_
#define _XSK_GSC_TOOL_H_

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

using namespace std::literals;

// Utility
#include "../src/lib/utils/string.hpp"
#include "../src/lib/utils/file.hpp"
#include "../src/lib/utils/byte_buffer.hpp"

#define IW5
#include "../src/lib/game/iw5.hpp"
using namespace iw5;

#include "../src/lib/assembly/asm_data.hpp"
#include "../src/lib/assembly/assembler.hpp"
#include "../src/lib/assembly/disassembler.hpp"
#include "../src/lib/decompiler/decompiler.hpp"

#ifdef DEBUG

#define XSK_DEBUG(__FMT__, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); \
								printf("[D][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__); \
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

#define XSK_ERROR(__FMT__, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); \
								printf("[E][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__); \
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

#define XSK_WARN(__FMT__, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); \
								printf("[W][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__); \
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

#define XSK_INFO(__FMT__, ...) printf("[I][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__);

#else

#define XSK_DEBUG(__FMT__, ...)

#define XSK_ERROR(__FMT__, ...) printf("[E]: " __FMT__ "\n", __VA_ARGS__);

#define XSK_WARN(__FMT__, ...)// printf("[W]: " __FMT__ "\n", __VA_ARGS__);

#define XSK_INFO(__FMT__, ...)// printf("[I]: " __FMT__ "\n", __VA_ARGS__);

#endif // DEBUG

#endif // _XSK_GSC_TOOL_H_