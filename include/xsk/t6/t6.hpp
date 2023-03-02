// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/utils/reader.hpp"
#include "xsk/utils/writer.hpp"
#include "common/arc.hpp"
#include "assembler.hpp"
#include "disassembler.hpp"
#include "compiler.hpp"
#include "decompiler.hpp"
#include "resolver.hpp"
#include "context.hpp"

namespace xsk::arc::t6
{

constexpr std::uint64_t magic = 0x06000A0D43534780;

enum class opcode : std::uint8_t
{
    OP_End = 0x0,
    OP_Return = 0x1,
    OP_GetUndefined = 0x2,
    OP_GetZero = 0x3,
    OP_GetByte = 0x4,
    OP_GetNegByte = 0x5,
    OP_GetUnsignedShort = 0x6,
    OP_GetNegUnsignedShort = 0x7,
    OP_GetInteger = 0x8,
    OP_GetFloat = 0x9,
    OP_GetString = 0xA,
    OP_GetIString = 0xB,
    OP_GetVector = 0xC,
    OP_GetLevelObject = 0xD,
    OP_GetAnimObject = 0xE,
    OP_GetSelf = 0xF,
    OP_GetLevel = 0x10,
    OP_GetGame = 0x11,
    OP_GetAnim = 0x12,
    OP_GetAnimation = 0x13,
    OP_GetGameRef = 0x14,
    OP_GetFunction = 0x15,
    OP_CreateLocalVariable = 0x16,
    OP_SafeCreateLocalVariables = 0x17,
    OP_RemoveLocalVariables = 0x18,
    OP_EvalLocalVariableCached = 0x19,
    OP_EvalArray = 0x1A,
    OP_EvalLocalArrayRefCached = 0x1B,
    OP_EvalArrayRef = 0x1C,
    OP_ClearArray = 0x1D,
    OP_EmptyArray = 0x1E,
    OP_GetSelfObject = 0x1F,
    OP_EvalFieldVariable = 0x20,
    OP_EvalFieldVariableRef = 0x21,
    OP_ClearFieldVariable = 0x22,
    OP_SafeSetVariableFieldCached = 0x23,
    OP_SafeSetWaittillVariableFieldCached = 0x24,
    OP_ClearParams = 0x25,
    OP_CheckClearParams = 0x26,
    OP_EvalLocalVariableRefCached = 0x27,
    OP_SetVariableField = 0x28,
    OP_CallBuiltin = 0x29,
    OP_CallBuiltinMethod = 0x2A,
    OP_Wait = 0x2B,
    OP_WaitTillFrameEnd = 0x2C,
    OP_PreScriptCall = 0x2D,
    OP_ScriptFunctionCall = 0x2E,
    OP_ScriptFunctionCallPointer = 0x2F,
    OP_ScriptMethodCall = 0x30,
    OP_ScriptMethodCallPointer = 0x31,
    OP_ScriptThreadCall = 0x32,
    OP_ScriptThreadCallPointer = 0x33,
    OP_ScriptMethodThreadCall = 0x34,
    OP_ScriptMethodThreadCallPointer = 0x35,
    OP_DecTop = 0x36,
    OP_CastFieldObject = 0x37,
    OP_CastBool = 0x38,
    OP_BoolNot = 0x39,
    OP_BoolComplement = 0x3A,
    OP_JumpOnFalse = 0x3B,
    OP_JumpOnTrue = 0x3C,
    OP_JumpOnFalseExpr = 0x3D,
    OP_JumpOnTrueExpr = 0x3E,
    OP_Jump = 0x3F,
    OP_JumpBack = 0x40,
    OP_Inc = 0x41,
    OP_Dec = 0x42,
    OP_Bit_Or = 0x43,
    OP_Bit_Xor = 0x44,
    OP_Bit_And = 0x45,
    OP_Equal = 0x46,
    OP_NotEqual = 0x47,
    OP_LessThan = 0x48,
    OP_GreaterThan = 0x49,
    OP_LessThanOrEqualTo = 0x4A,
    OP_GreaterThanOrEqualTo = 0x4B,
    OP_ShiftLeft = 0x4C,
    OP_ShiftRight = 0x4D,
    OP_Plus = 0x4E,
    OP_Minus = 0x4F,
    OP_Multiply = 0x50,
    OP_Divide = 0x51,
    OP_Modulus = 0x52,
    OP_SizeOf = 0x53,
    OP_WaitTillMatch = 0x54,
    OP_WaitTill = 0x55,
    OP_Notify = 0x56,
    OP_EndOn = 0x57,
    OP_VoidCodePos = 0x58,
    OP_Switch = 0x59,
    OP_EndSwitch = 0x5A,
    OP_Vector = 0x5B,
    OP_GetHash = 0x5C,
    OP_RealWait = 0x5D,
    OP_VectorConstant = 0x5E,
    OP_IsDefined = 0x5F,
    OP_VectorScale = 0x60,
    OP_AnglesToUp = 0x61,
    OP_AnglesToRight = 0x62,
    OP_AnglesToForward = 0x63,
    OP_AngleClamp180 = 0x64,
    OP_VectorToAngles = 0x65,
    OP_Abs = 0x66,
    OP_GetTime = 0x67,
    OP_GetDvar = 0x68,
    OP_GetDvarInt = 0x69,
    OP_GetDvarFloat = 0x6A,
    OP_GetDvarVector = 0x6B,
    OP_GetDvarColorRed = 0x6C,
    OP_GetDvarColorGreen = 0x6D,
    OP_GetDvarColorBlue = 0x6E,
    OP_GetDvarColorAlpha = 0x6F,
    OP_FirstArrayKey = 0x70,
    OP_NextArrayKey = 0x71,
    OP_ProfileStart = 0x72,
    OP_ProfileStop = 0x73,
    OP_SafeDecTop = 0x74,
    OP_Nop = 0x75,
    OP_Abort = 0x76,
    OP_Object = 0x77,
    OP_ThreadObject = 0x78,
    OP_EvalLocalVariable = 0x79,
    OP_EvalLocalVariableRef = 0x7A,
    OP_DevblockBegin = 0x7B,
    OP_DevblockEnd = 0x7C,
    OP_Count = 0x7D,
};

auto opcode_size(std::uint8_t id) -> std::uint32_t;

} // namespace xsk::arc::t6
