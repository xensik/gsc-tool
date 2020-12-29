// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW6_HPP_
#define _GSC_IW6_HPP_

#include <utils.hpp>

#include "assembler.hpp"
#include "disassembler.hpp"
#include "compiler.hpp"
#include "decompiler.hpp"
#include "resolver.hpp"

namespace IW6
{

enum class opcode : std::uint8_t
{
    OP_SetNewLocalVariableFieldCached0 = 0x17,
    OP_EvalSelfFieldVariable = 0x18,
    OP_Return = 0x19,
    OP_CallBuiltin0 = 0x1A,
    OP_CallBuiltin1 = 0x1B,
    OP_CallBuiltin2 = 0x1C,
    OP_CallBuiltin3 = 0x1D,
    OP_CallBuiltin4 = 0x1E,
    OP_CallBuiltin5 = 0x1F,
    OP_CallBuiltin = 0x20,
    OP_BoolNot = 0x21,
    OP_ScriptFarMethodThreadCall = 0x22,
    OP_JumpOnTrueExpr = 0x23,
    OP_SetLevelFieldVariableField = 0x24,
    OP_CastBool = 0x25,
    OP_EvalNewLocalArrayRefCached0 = 0x26,
    OP_CallBuiltinPointer = 0x27,
    OP_inequality = 0x28,
    OP_GetThisthread = 0x29, // NOT USED size 1
    OP_ClearFieldVariable = 0x2A,
    OP_GetFloat = 0x2B,
    OP_SafeCreateVariableFieldCached = 0x2C,
    OP_ScriptFarFunctionCall2 = 0x2D,
    OP_ScriptFarFunctionCall = 0x2E,
    OP_ScriptFarChildThreadCall = 0x2F, // NOT USED size 5
    OP_ClearLocalVariableFieldCached0 = 0x30,
    OP_ClearLocalVariableFieldCached = 0x31,
    OP_checkclearparams = 0x32,
    OP_CastFieldObject = 0x33,
    OP_End = 0x34,
    OP_size = 0x35,
    OP_EmptyArray = 0x36,
    OP_bit_and = 0x37,
    OP_less_equal = 0x38,
    OP_voidCodepos = 0x39,
    OP_ScriptMethodThreadCallPointer = 0x3A,
    OP_endswitch = 0x3B,
    OP_ClearVariableField = 0x3C, // NOP // NOT USED size 1
    OP_divide = 0x3D,
    OP_ScriptFarMethodChildThreadCall = 0x3E, // NOT USED size 5
    OP_GetUnsignedShort = 0x3F,
    OP_JumpOnTrue = 0x40,
    OP_GetSelf = 0x41,
    OP_ScriptFarThreadCall = 0x42,
    OP_ScriptLocalThreadCall = 0x43,
    OP_SetLocalVariableFieldCached0 = 0x44,
    OP_SetLocalVariableFieldCached = 0x45,
    OP_plus = 0x46,
    OP_BoolComplement = 0x47,
    OP_ScriptMethodCallPointer = 0x48,
    OP_inc = 0x49,
    OP_RemoveLocalVariables = 0x4A,
    OP_JumpOnFalseExpr = 0x4B,
    OP_switch = 0x4C,
    OP_clearparams = 0x4D,
    OP_EvalLocalVariableRefCached0 = 0x4E,
    OP_EvalLocalVariableRefCached = 0x4F,
    OP_ScriptLocalMethodCall = 0x50,
    OP_EvalFieldVariable = 0x51,
    OP_EvalFieldVariableRef = 0x52,
    OP_GetString = 0x53,
    OP_ScriptFunctionCallPointer = 0x54,
    OP_EvalLevelFieldVariable = 0x55,
    OP_GetVector = 0x56,
    OP_endon = 0x57,
    OP_greater_equal = 0x58,
    OP_GetSelfObject = 0x59,
    OP_SetAnimFieldVariableField = 0x5A,
    OP_SetVariableField = 0x5B,
    OP_ScriptLocalFunctionCall2 = 0x5C,
    OP_ScriptLocalFunctionCall = 0x5D,
    OP_EvalLocalArrayRefCached0 = 0x5E,
    OP_EvalLocalArrayRefCached = 0x5F,
    OP_GetFarFunction = 0x60,
    OP_less = 0x61,
    OP_GetGameRef = 0x62,
    OP_waittillFrameEnd = 0x63,
    OP_SafeSetVariableFieldCached0 = 0x64, // NOT USED size 1
    OP_SafeSetVariableFieldCached = 0x65, // NOT USED size 2
    OP_ScriptMethodChildThreadCallPointer = 0x66, // NOT USED size 2
    OP_GetLevel = 0x67,
    OP_notify = 0x68,
    OP_DecTop = 0x69,
    OP_shift_left = 0x6A,
    OP_ScriptLocalMethodThreadCall = 0x6B,
    OP_ScriptLocalMethodChildThreadCall = 0x6C,
    OP_greater = 0x6D,
    OP_EvalLocalVariableCached0 = 0x6E,
    OP_EvalLocalVariableCached1 = 0x6F,
    OP_EvalLocalVariableCached2 = 0x70,
    OP_EvalLocalVariableCached3 = 0x71,
    OP_EvalLocalVariableCached4 = 0x72,
    OP_EvalLocalVariableCached5 = 0x73,
    OP_EvalLocalVariableCached = 0x74,
    OP_SafeSetWaittillVariableFieldCached = 0x75,
    OP_jump = 0x76,
    OP_ScriptThreadCallPointer = 0x77,
    OP_GetZero = 0x78,
    OP_wait = 0x79,
    OP_minus = 0x7A,
    OP_SetSelfFieldVariableField = 0x7B,
    OP_EvalNewLocalVariableRefCached0 = 0x7C, // NOP // NOT USED size 2
    OP_multiply = 0x7D,
    OP_CreateLocalVariable = 0x7E,
    OP_ScriptLocalChildThreadCall = 0x7F,
    OP_GetInteger = 0x80,
    OP_mod = 0x81,
    OP_EvalAnimFieldVariableRef = 0x82,
    OP_GetBuiltinFunction = 0x83,
    OP_GetGame = 0x84,
    OP_waittill = 0x85,
    OP_dec = 0x86,
    OP_EvalLocalVariableObjectCached = 0x87,
    OP_PreScriptCall = 0x88,
    OP_GetAnim = 0x89,
    OP_GetUndefined = 0x8A,
    OP_EvalLevelFieldVariableRef = 0x8B,
    OP_GetAnimObject = 0x8C,
    OP_GetLevelObject = 0x8D,
    OP_bit_ex_or = 0x8E,
    OP_equality = 0x8F,
    OP_ClearArray = 0x90,
    OP_jumpback = 0x91,
    OP_GetAnimation = 0x92,
    OP_EvalAnimFieldVariable = 0x93,
    OP_GetAnimTree = 0x94,
    OP_GetIString = 0x95,
    OP_EvalArrayRef = 0x96,
    OP_EvalSelfFieldVariableRef = 0x97,
    OP_GetNegByte = 0x98,
    OP_GetBuiltinMethod = 0x99,
    OP_CallBuiltinMethodPointer = 0x9A,
    OP_EvalArray = 0x9B,
    OP_vector = 0x9C,
    OP_ScriptFarMethodCall = 0x9D,
    OP_EvalLocalArrayCached = 0x9E,
    OP_GetByte = 0x9F,
    OP_ScriptChildThreadCallPointer = 0xA0, // NOT USED size 2
    OP_bit_or = 0xA1,
    OP_AddArray = 0xA2,
    OP_waittillmatch2 = 0xA3, // NOP // NOT USED size 1
    OP_waittillmatch = 0xA4,
    OP_GetLocalFunction = 0xA5,
    OP_GetNegUnsignedShort = 0xA6,
    OP_shift_right = 0xA7,
    OP_CallBuiltinMethod0 = 0xA8,
    OP_CallBuiltinMethod1 = 0xA9,
    OP_CallBuiltinMethod2 = 0xAA,
    OP_CallBuiltinMethod3 = 0xAB,
    OP_CallBuiltinMethod4 = 0xAC,
    OP_CallBuiltinMethod5 = 0xAD,
    OP_CallBuiltinMethod = 0xAE,
    OP_JumpOnFalse = 0xAF,
    OP_Count = 0xB0,
};

auto opcode_size(opcode op) -> std::uint32_t;

} // namespace IW6

#endif // _GSC_IW6_HPP_
