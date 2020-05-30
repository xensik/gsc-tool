#pragma once

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
#include "utils/string.hpp"
#include "utils/file.hpp"
#include "utils/byte_buffer.hpp"

#define IW5
#include "game/iw5.hpp"
using namespace iw5;

#include "assembly/instruction.hpp"
#include "assembly/function.hpp"
#include "assembly/assembler.hpp"
#include "assembly/disassembler.hpp"

#ifdef DEBUG

#define LOG_DEBUG(__FMT__, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); \
								printf("[D][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__); \
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

#define LOG_ERROR(__FMT__, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); \
								printf("[E][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__); \
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

#define LOG_WARN(__FMT__, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); \
								printf("[W][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__); \
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

#define LOG_INFO(__FMT__, ...) printf("[I][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__);

#else

#define LOG_DEBUG(__FMT__, ...)

#define LOG_ERROR(__FMT__, ...) printf("[E]: " __FMT__ "\n", __VA_ARGS__);

#define LOG_WARN(__FMT__, ...) printf("[W]: " __FMT__ "\n", __VA_ARGS__);

#define LOG_INFO(__FMT__, ...) printf("[I]: " __FMT__ "\n", __VA_ARGS__);

#endif