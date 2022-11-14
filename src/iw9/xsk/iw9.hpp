// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "utils/xsk/utils.hpp"

#include "disassembler.hpp"
#include "resolver.hpp"
#include "context.hpp"

namespace xsk::gsc::iw9
{

constexpr std::uint32_t max_string_id = 0;

enum class opcode : std::uint8_t
{
    unk_000 = 0x00, // size 1                               OP_CastFieldObject
    unk_001 = 0x01, // size 2                               OP_SetLocalVariableFieldCached
    unk_002 = 0x02, // size 1                               OP_plus
    unk_003 = 0x03, // size 2                               OP_RemoveLocalVariables
    unk_004 = 0x04, // size 9, script 8 (hash?)             OP_EvalSelfFieldVariableRef
    unk_005 = 0x05, // size 6, stack 8 + 8                  OP_ScriptFarMethodChildThreadCall
    unk_006 = 0x06, // size 1                               OP_GetGameRef
    unk_007 = 0x07, // size 9, script 8 (hash?)             OP_EvalAnimFieldVariable
    unk_008 = 0x08, // size 9, script 8 (hash?)             OP_EvalLevelFieldVariableRef
    unk_009 = 0x09, // size 1                               OP_GetThisthread
    unk_010 = 0x0A, // size 1                               OP_greater
    unk_011 = 0x0B, // size 3                               OP_waittillmatch
    unk_012 = 0x0C, // size 1                               OP_shift_right
    unk_013 = 0x0D, // size 1                               OP_dec
    unk_014 = 0x0E, // size 3                               OP_JumpOnTrue
    unk_015 = 0x0F, // size 1                               OP_bit_or
    unk_016 = 0x10, // size 1                               OP_equality
    unk_017 = 0x11, // size 1                               OP_ClearLocalVariableFieldCached0
    unk_018 = 0x12, // size 1                               OP_notify
    unk_019 = 0x13, // size 13                              OP_GetVector
    unk_020 = 0x14, // size 2                               OP_ScriptMethodChildThreadCallPointer
    unk_021 = 0x15, // size 1                               OP_PreScriptCall
    unk_022 = 0x16, // size 2                               OP_GetByte
    unk_023 = 0x17, // size 6, stack 8 + 8                  OP_ScriptFarThreadCall
    unk_024 = 0x18, // size 9, script 8 (hash?)             OP_SetSelfFieldVariableField
    unk_025 = 0x19, // size 3                               OP_JumpOnFalseExpr
    unk_026 = 0x1A, // size 1                               OP_GetUndefined
    unk_027 = 0x1B, // size 3                               OP_jumpback
    unk_028 = 0x1C, // size 3                               OP_JumpOnTrueExpr
    unk_029 = 0x1D, // size 4, stack string                 OP_CallBuiltin
    unk_030 = 0x1E, // size 1                               OP_SetLocalVariableFieldCached0
    unk_031 = 0x1F, // size 9, script 8 (hash?)             OP_ClearFieldVariable
    unk_032 = 0x20, // size 1                               OP_GetLevel
    unk_033 = 0x21, // size 1                               OP_size
    unk_034 = 0x22, // size 2                               OP_SafeSetWaittillVariableFieldCached
    unk_035 = 0x23, // size 1                               OP_AddArray
    unk_036 = 0x24, // size 1                               OP_endon
    unk_037 = 0x25, // size 9, script 8 (hash?)             OP_EvalFieldVariable
    unk_038 = 0x26, // size 1                               OP_shift_left
    unk_039 = 0x27, // size 1                               OP_EvalLocalArrayRefCached0
    unk_040 = 0x28, // size 1                               OP_Return
    unk_041 = 0x29, // size 9                               OP_CreateLocalVariable
    unk_042 = 0x2A, // size 1                               OP_SafeSetVariableFieldCached0
    unk_043 = 0x2B, // size 3, stack string                 OP_GetBuiltinFunction
    unk_044 = 0x2C, // size 2                               OP_CallBuiltinMethodPointer
    unk_045 = 0x2D, // size 1                               OP_GetSelfObject
    unk_046 = 0x2E, // size 1                               OP_GetGame
    unk_047 = 0x2F, // size 9, script 8 (hash?)             OP_SetLevelFieldVariableField
    unk_048 = 0x30, // size 1                               OP_EvalArray
    unk_049 = 0x31, // size 1                               OP_GetSelf
    unk_050 = 0x32, // size 1                               OP_End
    unk_051 = 0x33, // size 9, script 8 (hash?)             OP_EvalSelfFieldVariable
    unk_052 = 0x34, // size 1                               OP_less_equal
    unk_053 = 0x35, // size 1                               OP_EvalLocalVariableCached0
    unk_054 = 0x36, // size 1                               OP_EvalLocalVariableCached1
    unk_055 = 0x37, // size 1                               OP_EvalLocalVariableCached2
    unk_056 = 0x38, // size 1                               OP_EvalLocalVariableCached3
    unk_057 = 0x39, // size 1                               OP_EvalLocalVariableCached4
    unk_058 = 0x3A, // size 1                               OP_EvalLocalVariableCached5
    unk_059 = 0x3B, // size 2                               OP_EvalLocalVariableCached
    unk_060 = 0x3C, // size 9                               OP_EvalNewLocalArrayRefCached0
    unk_061 = 0x3D, // size 2                               OP_ScriptChildThreadCallPointer
    unk_062 = 0x3E, // size 2                               OP_EvalLocalVariableObjectCached
    unk_063 = 0x3F, // size 5                               OP_GetInteger
    unk_064 = 0x40, // size 1                               OP_ScriptMethodCallPointer
    unk_065 = 0x41, // size 1                               OP_checkclearparams
    unk_066 = 0x42, // size 9, script 8 (hash?)             OP_SetAnimFieldVariableField
    unk_067 = 0x43, // missing                              OP_waittillmatch2
    unk_068 = 0x44, // size 1                               OP_minus
    unk_069 = 0x45, // size 3                               OP_GetNegUnsignedShort
    unk_070 = 0x46, // size 2                               OP_GetNegByte
    unk_071 = 0x47, // size 9                               OP_SafeCreateVariableFieldCached
    unk_072 = 0x48, // size 1                               OP_greater_equal
    unk_073 = 0x49, // size 1                               OP_vector
    unk_074 = 0x4A, // size 3, stack string                 OP_GetBuiltinMethod
    unk_075 = 0x4B, // size 3 + 8 * count, stack strings    OP_endswitch
    unk_076 = 0x4C, // size 1                               OP_ClearArray
    unk_077 = 0x4D, // size 1                               OP_DecTop
    unk_078 = 0x4E, // size 1                               OP_CastBool
    unk_079 = 0x4F, // size 1                               OP_EvalArrayRef
    unk_080 = 0x50, // size 9                               OP_SetNewLocalVariableFieldCached0
    unk_081 = 0x51, // size 1                               OP_GetZero
    unk_082 = 0x52, // size 1                               OP_wait
    unk_083 = 0x53, // size 1                               OP_waittill
    unk_084 = 0x54, // size 5, stack string                 OP_GetIString
    unk_085 = 0x55, // size 5, stack 8 + 8                  OP_ScriptFarFunctionCall
    unk_086 = 0x56, // size 1                               OP_GetAnimObject
    unk_087 = 0x57, // size 2, stack string                 OP_GetAnimTree
    unk_088 = 0x58, // size 2                               OP_EvalLocalArrayCached
    unk_089 = 0x59, // size 1                               OP_mod
    unk_090 = 0x5A, // size 6, stack 8 + 8                  OP_ScriptFarMethodThreadCall
    unk_091 = 0x5B, // size 3                               OP_GetUnsignedShort
    unk_092 = 0x5C, // size 1                               OP_clearparams
    unk_093 = 0x5D, // size 2                               OP_ScriptMethodThreadCallPointer
    unk_094 = 0x5E, // size 1                               OP_ScriptFunctionCallPointer
    unk_095 = 0x5F, // size 1                               OP_EmptyArray
    unk_096 = 0x60, // size 2                               OP_SafeSetVariableFieldCached
    unk_097 = 0x61, // missing                              OP_ClearVariableField
    unk_098 = 0x62, // size 9, script 8 (hash?)             OP_EvalFieldVariableRef
    unk_099 = 0x63, // missing                              OP_EvalNewLocalVariableRefCached0
    unk_100 = 0x64, // size 5                               OP_GetFloat
    unk_101 = 0x65, // size 2                               OP_EvalLocalVariableRefCached
    unk_102 = 0x66, // size 3                               OP_JumpOnFalse
    unk_103 = 0x67, // size 1                               OP_BoolComplement
    unk_104 = 0x68, // size 2                               OP_ScriptThreadCallPointer
    unk_105 = 0x69, // size 1                               OP_less
    unk_106 = 0x6A, // size 1                               OP_BoolNot
    unk_107 = 0x6B, // size 1                               OP_waittillFrameEnd
    unk_108 = 0x6C, // size 1                               OP_waitframe
    unk_109 = 0x6D, // size 5, stack string                 OP_GetString
    unk_110 = 0x6E, // size 9, script 8 (hash?)             OP_EvalLevelFieldVariable
    unk_111 = 0x6F, // size 1                               OP_GetLevelObject
    unk_112 = 0x70, // size 1                               OP_inc
    unk_113 = 0x71, // size 4, stack string (hash)          OP_CallBuiltinMethod
    unk_114 = 0x72, // size 1                               OP_GetAnim
    unk_115 = 0x73, // size 5                               OP_switch
    unk_116 = 0x74, // size 1                               OP_SetVariableField
    unk_117 = 0x75, // size 1                               OP_divide
    unk_118 = 0x76, // size 6, stack 8 + 8                  OP_ScriptFarChildThreadCall
    unk_119 = 0x77, // size 1                               OP_multiply
    unk_120 = 0x78, // size 2                               OP_ClearLocalVariableFieldCached
    unk_121 = 0x79, // size 9, script 8 (hash?)             OP_EvalAnimFieldVariableRef
    unk_122 = 0x7A, // size 2                               OP_EvalLocalArrayRefCached
    unk_123 = 0x7B, // size 1                               OP_EvalLocalVariableRefCached0
    unk_124 = 0x7C, // size 1                               OP_bit_and
    unk_125 = 0x7D, // size ?, stack string * 2             OP_GetAnimation
    unk_126 = 0x7E, // size 5, stack 8 + 8                  OP_GetFarFunction
    unk_127 = 0x7F, // size 2                               OP_CallBuiltinPointer
    unk_128 = 0x80, // size 5                               OP_jump
    unk_129 = 0x81, // size 1                               OP_voidCodepos
    unk_130 = 0x82, // size 5, stack 8 + 8                  OP_ScriptFarMethodCall
    unk_131 = 0x83, // size 1                               OP_inequality
    unk_132 = 0x84, // size 1                               OP_bit_ex_or
    unk_133 = 0x85, // size 9
    unk_134 = 0x86, // size 5
    unk_135 = 0x87, // size 9
    unk_136 = 0x88, // size 9
    unk_137 = 0x89, // size 5
    unk_138 = 0x8A, // size 9
    unk_139 = 0x8B,
    unk_140 = 0x8C,
    unk_141 = 0x8D,
    unk_142 = 0x8E,
    unk_143 = 0x8F,
    unk_144 = 0x90,
    unk_145 = 0x91, // size 6                               OP_prof_begin
    unk_146 = 0x92, // size 2                               OP_prof_end
    unk_147 = 0x93, //                                      OP_breakpoint
    unk_148 = 0x94, //                                      OP_assignmentBreakpoint
    unk_149 = 0x95, //                                      OP_manualAndAssignmentBreakpoint
    unk_150 = 0x96, // size 1                               OP_BoolNotAfterAnd
    unk_151 = 0x97, // size 2 + 8 * count (params?)         OP_FormalParams
    unk_152 = 0x98, // size 1                               OP_IsDefined
    unk_153 = 0x99, // size 1                               OP_IsTrue
    unk_154 = 0x9A, // size 5, stack 4                      OP_NativeGetFarFunction
    unk_155 = 0x9B, // size 5, stack 4                      OP_NativeFarFunctionCall
    unk_156 = 0x9C, // size 5, stack 4                      OP_NativeFarMethodCall
    unk_157 = 0x9D, // size 6, stack 4                      OP_NativeFarFunctionThreadCall
    unk_158 = 0x9E, // size 6, stack 4                      OP_NativeFarMethodThreadCall
    unk_159 = 0x9F, // size 6, stack 4                      OP_NativeFarFunctionChildThreadCall
    unk_160 = 0xA0, // size 6, stack 4                      OP_NativeFarMethodChildThreadCall
    unk_161 = 0xA1, // size 9                               OP_EvalNewLocalArrayRefCached0_Precompiled
    unk_162 = 0xA2, // size 9                               OP_SetNewLocalVariableFieldCached0_Precompiled
    unk_163 = 0xA3, // size 9                               OP_CreateLocalVariable_Precompiled
    unk_164 = 0xA4, // size 9                               OP_SafeCreateVariableFieldCached_Precompiled
    unk_165 = 0xA5, // size 2 + 8 * count (params?)         OP_FormalParams_Precompiled
    unk_166 = 0xA6, // size 9, stack 8
    OP_count = 0xA7,
};

auto opcode_size(std::uint8_t op) -> std::uint32_t;

} // namespace xsk::gsc::iw9
