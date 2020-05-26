#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <array>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <stdio.h>
#include <tchar.h>

#include "utils/string.hpp"
#include "utils/file.hpp"
#include "utils/byte_buffer.hpp"

#define IW5
#include "game/IW5_PC.hpp"
using namespace iw5;

#include "assembly/instruction.hpp"
#include "assembly/function.hpp"
#include "assembly/assembler.hpp"
#include "assembly/disassembler.hpp"
