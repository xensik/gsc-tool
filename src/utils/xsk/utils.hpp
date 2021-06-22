// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

// Utility
#include "file.hpp"
#include "string.hpp"
#include "byte_buffer.hpp"
#include "compression.hpp"

// GSC Types
#include "gsc/pair.hpp"
#include "gsc/asset.hpp"
#include "gsc/assembly.hpp"
#include "gsc/context.hpp"
#include "gsc/location.hpp"
#include "gsc/nodetree.hpp"

// GSC Interfaces
#include "gsc/interfaces/exception.hpp"
#include "gsc/interfaces/assembler.hpp"
#include "gsc/interfaces/disassembler.hpp"
#include "gsc/interfaces/compiler.hpp"
#include "gsc/interfaces/decompiler.hpp"

// Treyarch GSC Types
#include "arc/arc_asset.hpp"
#include "arc/arc_assembly.hpp"

// Treyarch GSC Interfaces
#include "arc/interfaces/arc_exception.hpp"
#include "arc/interfaces/arc_assembler.hpp"
#include "arc/interfaces/arc_disassembler.hpp"
#include "arc/interfaces/arc_compiler.hpp"
#include "arc/interfaces/arc_decompiler.hpp"
