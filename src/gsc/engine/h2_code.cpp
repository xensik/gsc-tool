// Copyright 2024 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/gsc/engine/h2.hpp"

namespace xsk::gsc::h2
{

extern std::array<std::pair<u8, opcode>, code_count> const code_list
{{
    { 0x17, opcode::OP_SetNewLocalVariableFieldCached0 },
    { 0x18, opcode::OP_EvalSelfFieldVariable },
    { 0x19, opcode::OP_Return },
    { 0x1A, opcode::OP_CallBuiltin0 },
    { 0x1B, opcode::OP_CallBuiltin1 },
    { 0x1C, opcode::OP_CallBuiltin2 },
    { 0x1D, opcode::OP_CallBuiltin3 },
    { 0x1E, opcode::OP_CallBuiltin4 },
    { 0x1F, opcode::OP_CallBuiltin5 },
    { 0x20, opcode::OP_CallBuiltin },
    { 0x21, opcode::OP_BoolNot },
    { 0x22, opcode::OP_ScriptFarMethodThreadCall },
    { 0x23, opcode::OP_JumpOnTrueExpr },
    { 0x24, opcode::OP_SetLevelFieldVariableField },
    { 0x25, opcode::OP_CastBool },
    { 0x26, opcode::OP_EvalNewLocalArrayRefCached0 },
    { 0x27, opcode::OP_CallBuiltinPointer },
    { 0x28, opcode::OP_inequality },
    { 0x29, opcode::OP_GetThisthread },
    { 0x2A, opcode::OP_ClearFieldVariable },
    { 0x2B, opcode::OP_GetFloat },
    { 0x2C, opcode::OP_SafeCreateVariableFieldCached },
    { 0x2D, opcode::OP_ScriptFarFunctionCall2 },
    { 0x2E, opcode::OP_ScriptFarFunctionCall },
    { 0x2F, opcode::OP_ScriptFarChildThreadCall },
    { 0x30, opcode::OP_ClearLocalVariableFieldCached0 },
    { 0x31, opcode::OP_ClearLocalVariableFieldCached },
    { 0x32, opcode::OP_checkclearparams },
    { 0x33, opcode::OP_CastFieldObject },
    { 0x34, opcode::OP_End },
    { 0x35, opcode::OP_size },
    { 0x36, opcode::OP_EmptyArray },
    { 0x37, opcode::OP_bit_and },
    { 0x38, opcode::OP_less_equal },
    { 0x39, opcode::OP_voidCodepos },
    { 0x3A, opcode::OP_ScriptMethodThreadCallPointer },
    { 0x3B, opcode::OP_endswitch },
    { 0x3C, opcode::OP_ClearVariableField },
    { 0x3D, opcode::OP_divide },
    { 0x3E, opcode::OP_ScriptFarMethodChildThreadCall },
    { 0x3F, opcode::OP_GetUnsignedShort },
    { 0x40, opcode::OP_JumpOnTrue },
    { 0x41, opcode::OP_GetSelf },
    { 0x42, opcode::OP_ScriptFarThreadCall },
    { 0x43, opcode::OP_ScriptLocalThreadCall },
    { 0x44, opcode::OP_SetLocalVariableFieldCached0 },
    { 0x45, opcode::OP_SetLocalVariableFieldCached },
    { 0x46, opcode::OP_plus },
    { 0x47, opcode::OP_BoolComplement },
    { 0x48, opcode::OP_ScriptMethodCallPointer },
    { 0x49, opcode::OP_inc },
    { 0x4A, opcode::OP_RemoveLocalVariables },
    { 0x4B, opcode::OP_JumpOnFalseExpr },
    { 0x4C, opcode::OP_switch },
    { 0x4D, opcode::OP_clearparams },
    { 0x4E, opcode::OP_EvalLocalVariableRefCached0 },
    { 0x4F, opcode::OP_EvalLocalVariableRefCached },
    { 0x50, opcode::OP_ScriptLocalMethodCall },
    { 0x51, opcode::OP_EvalFieldVariable },
    { 0x52, opcode::OP_EvalFieldVariableRef },
    { 0x53, opcode::OP_GetString },
    { 0x54, opcode::OP_ScriptFunctionCallPointer },
    { 0x55, opcode::OP_EvalLevelFieldVariable },
    { 0x56, opcode::OP_GetVector },
    { 0x57, opcode::OP_endon },
    { 0x58, opcode::OP_greater_equal },
    { 0x59, opcode::OP_GetSelfObject },
    { 0x5A, opcode::OP_SetAnimFieldVariableField },
    { 0x5B, opcode::OP_SetVariableField },
    { 0x5C, opcode::OP_ScriptLocalFunctionCall2 },
    { 0x5D, opcode::OP_ScriptLocalFunctionCall },
    { 0x5E, opcode::OP_EvalLocalArrayRefCached0 },
    { 0x5F, opcode::OP_EvalLocalArrayRefCached },
    { 0x60, opcode::OP_GetFarFunction },
    { 0x61, opcode::OP_less },
    { 0x62, opcode::OP_GetGameRef },
    { 0x63, opcode::OP_waittillFrameEnd },
    { 0x64, opcode::OP_waitframe },
    { 0x65, opcode::OP_SafeSetVariableFieldCached0 },
    { 0x66, opcode::OP_SafeSetVariableFieldCached },
    { 0x67, opcode::OP_ScriptMethodChildThreadCallPointer },
    { 0x68, opcode::OP_GetLevel },
    { 0x69, opcode::OP_notify },
    { 0x6A, opcode::OP_DecTop },
    { 0x6B, opcode::OP_shift_left },
    { 0x6C, opcode::OP_ScriptLocalMethodThreadCall },
    { 0x6D, opcode::OP_ScriptLocalMethodChildThreadCall },
    { 0x6E, opcode::OP_greater },
    { 0x6F, opcode::OP_EvalLocalVariableCached0 },
    { 0x70, opcode::OP_EvalLocalVariableCached1 },
    { 0x71, opcode::OP_EvalLocalVariableCached2 },
    { 0x72, opcode::OP_EvalLocalVariableCached3 },
    { 0x73, opcode::OP_EvalLocalVariableCached4 },
    { 0x74, opcode::OP_EvalLocalVariableCached5 },
    { 0x75, opcode::OP_EvalLocalVariableCached },
    { 0x76, opcode::OP_SafeSetWaittillVariableFieldCached },
    { 0x77, opcode::OP_jump },
    { 0x78, opcode::OP_ScriptThreadCallPointer },
    { 0x79, opcode::OP_GetZero },
    { 0x7A, opcode::OP_wait },
    { 0x7B, opcode::OP_minus },
    { 0x7C, opcode::OP_SetSelfFieldVariableField },
    { 0x7D, opcode::OP_EvalNewLocalVariableRefCached0 },
    { 0x7E, opcode::OP_multiply },
    { 0x7F, opcode::OP_CreateLocalVariable },
    { 0x80, opcode::OP_ScriptLocalChildThreadCall },
    { 0x81, opcode::OP_GetInteger },
    { 0x82, opcode::OP_mod },
    { 0x83, opcode::OP_EvalAnimFieldVariableRef },
    { 0x84, opcode::OP_GetBuiltinFunction },
    { 0x85, opcode::OP_GetGame },
    { 0x86, opcode::OP_waittill },
    { 0x87, opcode::OP_dec },
    { 0x88, opcode::OP_EvalLocalVariableObjectCached },
    { 0x89, opcode::OP_PreScriptCall },
    { 0x8A, opcode::OP_GetAnim },
    { 0x8B, opcode::OP_GetUndefined },
    { 0x8C, opcode::OP_EvalLevelFieldVariableRef },
    { 0x8D, opcode::OP_GetAnimObject },
    { 0x8E, opcode::OP_GetLevelObject },
    { 0x8F, opcode::OP_bit_ex_or },
    { 0x90, opcode::OP_equality },
    { 0x91, opcode::OP_ClearArray },
    { 0x92, opcode::OP_jumpback },
    { 0x93, opcode::OP_GetAnimation },
    { 0x94, opcode::OP_EvalAnimFieldVariable },
    { 0x95, opcode::OP_GetAnimTree },
    { 0x96, opcode::OP_GetIString },
    { 0x97, opcode::OP_EvalArrayRef },
    { 0x98, opcode::OP_EvalSelfFieldVariableRef },
    { 0x99, opcode::OP_GetNegByte },
    { 0x9A, opcode::OP_GetBuiltinMethod },
    { 0x9B, opcode::OP_CallBuiltinMethodPointer },
    { 0x9C, opcode::OP_EvalArray },
    { 0x9D, opcode::OP_vector },
    { 0x9E, opcode::OP_ScriptFarMethodCall },
    { 0x9F, opcode::OP_EvalLocalArrayCached },
    { 0xA0, opcode::OP_GetByte },
    { 0xA1, opcode::OP_ScriptChildThreadCallPointer },
    { 0xA2, opcode::OP_bit_or },
    { 0xA3, opcode::OP_AddArray },
    { 0xA4, opcode::OP_waittillmatch2 },
    { 0xA5, opcode::OP_waittillmatch },
    { 0xA6, opcode::OP_GetLocalFunction },
    { 0xA7, opcode::OP_GetNegUnsignedShort },
    { 0xA8, opcode::OP_shift_right },
    { 0xA9, opcode::OP_CallBuiltinMethod0 },
    { 0xAA, opcode::OP_CallBuiltinMethod1 },
    { 0xAB, opcode::OP_CallBuiltinMethod2 },
    { 0xAC, opcode::OP_CallBuiltinMethod3 },
    { 0xAD, opcode::OP_CallBuiltinMethod4 },
    { 0xAE, opcode::OP_CallBuiltinMethod5 },
    { 0xAF, opcode::OP_CallBuiltinMethod },
    { 0xB0, opcode::OP_JumpOnFalse },
}};

} // namespace xsk::gsc::h2
