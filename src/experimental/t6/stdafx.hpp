// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

// Warnings
#ifdef _WIN32
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4005)
#pragma warning(disable:4065)
#define _CRT_SECURE_NO_WARNINGS
#endif

// C/C++
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <filesystem>
#include <functional>
#include <stdexcept>
#include <map>
#include <stack>
#include <array>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <stdio.h>

// Ext
using namespace std::literals;

#include "xsk/t6.hpp"
