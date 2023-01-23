// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "iw5_xb.hpp"

namespace xsk::gsc::iw5_xb
{

extern std::array<std::pair<u8, opcode>, code_count> const code_list
{{
    { 0x00, opcode::OP_End },
    { 0x01, opcode::OP_Return },
    { 0x02, opcode::OP_GetUndefined },
    { 0x03, opcode::OP_GetZero },
    { 0x04, opcode::OP_GetByte },
    { 0x05, opcode::OP_GetAnimTree },
    { 0x06, opcode::OP_GetNegByte },
    { 0x07, opcode::OP_GetUnsignedShort },
    { 0x08, opcode::OP_GetNegUnsignedShort },
    { 0x09, opcode::OP_GetInteger },
    { 0x0A, opcode::OP_GetBuiltinFunction },
    { 0x0B, opcode::OP_GetBuiltinMethod },
    { 0x0C, opcode::OP_GetFloat },
    { 0x0D, opcode::OP_GetString },
    { 0x0E, opcode::OP_GetIString },
    { 0x0F, opcode::OP_GetVector },
    { 0x10, opcode::OP_GetLevelObject },
    { 0x11, opcode::OP_GetAnimObject },
    { 0x12, opcode::OP_GetSelf },
    { 0x13, opcode::OP_GetThisthread },
    { 0x14, opcode::OP_GetLevel },
    { 0x15, opcode::OP_GetGame },
    { 0x16, opcode::OP_GetAnim },
    { 0x17, opcode::OP_GetAnimation },
    { 0x18, opcode::OP_GetGameRef },
    { 0x1A, opcode::OP_GetLocalFunction },
    { 0x19, opcode::OP_GetFarFunction },
    { 0x1B, opcode::OP_CreateLocalVariable },
    { 0x1C, opcode::OP_RemoveLocalVariables },
    { 0x1D, opcode::OP_EvalLocalVariableCached0 },
    { 0x1E, opcode::OP_EvalLocalVariableCached1 },
    { 0x1F, opcode::OP_EvalLocalVariableCached2 },
    { 0x20, opcode::OP_EvalLocalVariableCached3 },
    { 0x21, opcode::OP_EvalLocalVariableCached4 },
    { 0x22, opcode::OP_EvalLocalVariableCached5 },
    { 0x23, opcode::OP_EvalLocalVariableCached },
    { 0x24, opcode::OP_EvalLocalArrayCached },
    { 0x25, opcode::OP_EvalArray },
    { 0x26, opcode::OP_EvalLocalArrayRefCached0 },
    { 0x27, opcode::OP_EvalNewLocalArrayRefCached0 },
    { 0x28, opcode::OP_EvalLocalArrayRefCached },
    { 0x29, opcode::OP_EvalArrayRef },
    { 0x2A, opcode::OP_ClearArray },
    { 0x2B, opcode::OP_EmptyArray },
    { 0x2C, opcode::OP_AddArray },
    { 0x2D, opcode::OP_GetSelfObject },
    { 0x2E, opcode::OP_EvalLevelFieldVariable },
    { 0x2F, opcode::OP_EvalAnimFieldVariable },
    { 0x30, opcode::OP_EvalSelfFieldVariable },
    { 0x31, opcode::OP_EvalFieldVariable },
    { 0x32, opcode::OP_EvalLevelFieldVariableRef },
    { 0x33, opcode::OP_EvalAnimFieldVariableRef },
    { 0x34, opcode::OP_EvalSelfFieldVariableRef },
    { 0x35, opcode::OP_EvalFieldVariableRef },
    { 0x36, opcode::OP_ClearFieldVariable },
    { 0x37, opcode::OP_SafeCreateVariableFieldCached },
    { 0x38, opcode::OP_SafeSetVariableFieldCached0 },
    { 0x39, opcode::OP_SafeSetVariableFieldCached },
    { 0x3A, opcode::OP_SafeSetWaittillVariableFieldCached },
    { 0x3B, opcode::OP_clearparams },
    { 0x3C, opcode::OP_checkclearparams },
    { 0x3D, opcode::OP_EvalLocalVariableRefCached0 },
    { 0x3E, opcode::OP_EvalNewLocalVariableRefCached0 },
    { 0x3F, opcode::OP_EvalLocalVariableRefCached },
    { 0x40, opcode::OP_SetLevelFieldVariableField },
    { 0x41, opcode::OP_SetVariableField },
    { 0x42, opcode::OP_ClearVariableField },
    { 0x43, opcode::OP_SetAnimFieldVariableField },
    { 0x44, opcode::OP_SetSelfFieldVariableField },
    { 0x45, opcode::OP_SetLocalVariableFieldCached0 },
    { 0x46, opcode::OP_SetNewLocalVariableFieldCached0 },
    { 0x47, opcode::OP_SetLocalVariableFieldCached },
    { 0x48, opcode::OP_ClearLocalVariableFieldCached },
    { 0x49, opcode::OP_ClearLocalVariableFieldCached0 },
    { 0x4A, opcode::OP_CallBuiltin0 },
    { 0x4B, opcode::OP_CallBuiltin1 },
    { 0x4C, opcode::OP_CallBuiltin2 },
    { 0x4D, opcode::OP_CallBuiltin3 },
    { 0x4E, opcode::OP_CallBuiltin4 },
    { 0x4F, opcode::OP_CallBuiltin5 },
    { 0x50, opcode::OP_CallBuiltin },
    { 0x51, opcode::OP_CallBuiltinMethod0 },
    { 0x52, opcode::OP_CallBuiltinMethod1 },
    { 0x53, opcode::OP_CallBuiltinMethod2 },
    { 0x54, opcode::OP_CallBuiltinMethod3 },
    { 0x55, opcode::OP_CallBuiltinMethod4 },
    { 0x56, opcode::OP_CallBuiltinMethod5 },
    { 0x57, opcode::OP_CallBuiltinMethod },
    { 0x58, opcode::OP_wait },
    { 0x59, opcode::OP_waittillFrameEnd },
    { 0x5A, opcode::OP_PreScriptCall },
    { 0x5B, opcode::OP_ScriptLocalFunctionCall2 },
    { 0x5C, opcode::OP_ScriptLocalFunctionCall },
    { 0x5D, opcode::OP_ScriptLocalMethodCall },
    { 0x5E, opcode::OP_ScriptLocalThreadCall },
    { 0x5F, opcode::OP_ScriptLocalChildThreadCall },
    { 0x60, opcode::OP_ScriptLocalMethodThreadCall },
    { 0x61, opcode::OP_ScriptLocalMethodChildThreadCall },
    { 0x62, opcode::OP_ScriptFarFunctionCall2 },
    { 0x63, opcode::OP_ScriptFarFunctionCall },
    { 0x64, opcode::OP_ScriptFarMethodCall },
    { 0x65, opcode::OP_ScriptFarThreadCall },
    { 0x66, opcode::OP_ScriptFarChildThreadCall },
    { 0x67, opcode::OP_ScriptFarMethodThreadCall },
    { 0x68, opcode::OP_ScriptFarMethodChildThreadCall },
    { 0x69, opcode::OP_ScriptFunctionCallPointer },
    { 0x6A, opcode::OP_ScriptMethodCallPointer },
    { 0x6B, opcode::OP_ScriptThreadCallPointer },
    { 0x6C, opcode::OP_ScriptChildThreadCallPointer },
    { 0x6D, opcode::OP_ScriptMethodThreadCallPointer },
    { 0x6E, opcode::OP_ScriptMethodChildThreadCallPointer },
    { 0x6F, opcode::OP_CallBuiltinPointer },
    { 0x70, opcode::OP_CallBuiltinMethodPointer },
    { 0x71, opcode::OP_DecTop },
    { 0x72, opcode::OP_CastFieldObject },
    { 0x73, opcode::OP_EvalLocalVariableObjectCached },
    { 0x74, opcode::OP_CastBool },
    { 0x75, opcode::OP_BoolNot },
    { 0x76, opcode::OP_BoolComplement },
    { 0x77, opcode::OP_JumpOnFalse },
    { 0x78, opcode::OP_JumpOnTrue },
    { 0x79, opcode::OP_JumpOnFalseExpr },
    { 0x7A, opcode::OP_JumpOnTrueExpr },
    { 0x7B, opcode::OP_jump },
    { 0x7C, opcode::OP_jumpback },
    { 0x7D, opcode::OP_inc },
    { 0x7E, opcode::OP_dec },
    { 0x7F, opcode::OP_bit_or },
    { 0x80, opcode::OP_bit_ex_or },
    { 0x81, opcode::OP_bit_and },
    { 0x82, opcode::OP_equality },
    { 0x83, opcode::OP_inequality },
    { 0x84, opcode::OP_less },
    { 0x85, opcode::OP_greater },
    { 0x86, opcode::OP_less_equal },
    { 0x87, opcode::OP_greater_equal },
    { 0x88, opcode::OP_shift_left },
    { 0x89, opcode::OP_shift_right },
    { 0x8A, opcode::OP_plus },
    { 0x8B, opcode::OP_minus },
    { 0x8C, opcode::OP_multiply },
    { 0x8D, opcode::OP_divide },
    { 0x8E, opcode::OP_mod },
    { 0x8F, opcode::OP_size },
    { 0x90, opcode::OP_waittillmatch },
    { 0x91, opcode::OP_waittillmatch2 },
    { 0x92, opcode::OP_waittill },
    { 0x93, opcode::OP_notify },
    { 0x94, opcode::OP_endon },
    { 0x95, opcode::OP_voidCodepos },
    { 0x96, opcode::OP_switch },
    { 0x97, opcode::OP_endswitch },
    { 0x98, opcode::OP_vector },
}};

} // namespace xsk::gsc::iw5_xb
