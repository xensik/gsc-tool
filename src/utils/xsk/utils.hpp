// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

// Utility
#include "utils/file.hpp"
#include "utils/string.hpp"
#include "utils/byte_buffer.hpp"
#include "utils/compression.hpp"

// GSC Types
#include "gsc/location.hpp"
#include "gsc/types.hpp"
#include "gsc/asset.hpp"
#include "gsc/block.hpp"
#include "gsc/nodetree.hpp"

// GSC Interfaces
#include "gsc/interfaces/exception.hpp"
#include "gsc/interfaces/assembler.hpp"
#include "gsc/interfaces/disassembler.hpp"
#include "gsc/interfaces/compiler.hpp"
#include "gsc/interfaces/decompiler.hpp"

// ARC Types
#include "arc/location.hpp"
#include "arc/types.hpp"
#include "arc/block.hpp"
#include "arc/nodetree.hpp"

// ARC Interfaces
#include "arc/interfaces/exception.hpp"
#include "arc/interfaces/assembler.hpp"
#include "arc/interfaces/disassembler.hpp"
#include "arc/interfaces/compiler.hpp"
#include "arc/interfaces/decompiler.hpp"
#include "arc/interfaces/context.hpp"
