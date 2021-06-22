// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "t6.hpp"

namespace xsk::gsc::t6
{

auto opcode_size(std::uint8_t id) -> std::uint32_t
{
    switch (opcode(id))
    {
    case opcode::OP_End:
    case opcode::OP_Return:
    case opcode::OP_GetUndefined:
    case opcode::OP_GetZero:
    case opcode::OP_GetLevelObject:
    case opcode::OP_GetAnimObject:
    case opcode::OP_GetSelf:
    case opcode::OP_GetLevel:
    case opcode::OP_GetGame:
    case opcode::OP_GetAnim:
    case opcode::OP_GetGameRef:
    case opcode::OP_CreateLocalVariable:
    case opcode::OP_RemoveLocalVariables:
    case opcode::OP_EvalArray:
    case opcode::OP_EvalLocalArrayRefCached:
    case opcode::OP_EvalArrayRef:
    case opcode::OP_ClearArray:
    case opcode::OP_EmptyArray:
    case opcode::OP_GetSelfObject:
    case opcode::OP_SafeSetVariableFieldCached:
    case opcode::OP_ClearParams:
    case opcode::OP_CheckClearParams:
    case opcode::OP_SetVariableField:
    case opcode::OP_Wait:
    case opcode::OP_WaitTillFrameEnd:
    case opcode::OP_PreScriptCall:
    case opcode::OP_DecTop:
    case opcode::OP_CastFieldObject:
    case opcode::OP_CastBool:
    case opcode::OP_BoolNot:
    case opcode::OP_BoolComplement:
    case opcode::OP_Inc:
    case opcode::OP_Dec:
    case opcode::OP_Bit_Or:
    case opcode::OP_Bit_Xor:
    case opcode::OP_Bit_And:
    case opcode::OP_Equal:
    case opcode::OP_NotEqual:
    case opcode::OP_LessThan:
    case opcode::OP_GreaterThan:
    case opcode::OP_LessThanOrEqualTo:
    case opcode::OP_GreaterThanOrEqualTo:
    case opcode::OP_ShiftLeft:
    case opcode::OP_ShiftRight:
    case opcode::OP_Plus:
    case opcode::OP_Minus:
    case opcode::OP_Multiply:
    case opcode::OP_Divide:
    case opcode::OP_Modulus:
    case opcode::OP_SizeOf:
    case opcode::OP_WaitTill:
    case opcode::OP_Notify:
    case opcode::OP_EndOn:
    case opcode::OP_VoidCodePos:
    case opcode::OP_Vector:
    case opcode::OP_RealWait:
    case opcode::OP_IsDefined:
    case opcode::OP_VectorScale:
    case opcode::OP_AnglesToUp:
    case opcode::OP_AnglesToRight:
    case opcode::OP_AnglesToForward:
    case opcode::OP_AngleClamp180:
    case opcode::OP_VectorToAngles:
    case opcode::OP_Abs:
    case opcode::OP_GetTime:
    case opcode::OP_GetDvar:
    case opcode::OP_GetDvarInt:
    case opcode::OP_GetDvarFloat:
    case opcode::OP_GetDvarVector:
    case opcode::OP_GetDvarColorRed:
    case opcode::OP_GetDvarColorGreen:
    case opcode::OP_GetDvarColorBlue:
    case opcode::OP_GetDvarColorAlpha:
    case opcode::OP_FirstArrayKey:
    case opcode::OP_NextArrayKey:
    case opcode::OP_ProfileStart:
    case opcode::OP_ProfileStop:
    case opcode::OP_SafeDecTop:
    case opcode::OP_Nop:
    case opcode::OP_Abort:
    case opcode::OP_Object:
    case opcode::OP_ThreadObject:
    case opcode::OP_EvalLocalVariable:
    case opcode::OP_EvalLocalVariableRef:
    case opcode::OP_Breakpoint:
        return 1;
    case opcode::OP_GetByte:
    case opcode::OP_GetNegByte:
    case opcode::OP_SafeCreateLocalVariables:
    case opcode::OP_EvalLocalVariableCached:
    case opcode::OP_SafeSetWaittillVariableFieldCached:
    case opcode::OP_EvalLocalVariableRefCached:
    case opcode::OP_ScriptFunctionCallPointer:
    case opcode::OP_ScriptMethodCallPointer:
    case opcode::OP_ScriptThreadCallPointer:
    case opcode::OP_ScriptMethodThreadCallPointer:
    case opcode::OP_WaitTillMatch:
    case opcode::OP_VectorConstant:
        return 2;
    case opcode::OP_GetUnsignedShort:
    case opcode::OP_GetNegUnsignedShort:
    case opcode::OP_GetString:
    case opcode::OP_GetIString:
    case opcode::OP_EvalFieldVariable:
    case opcode::OP_EvalFieldVariableRef:
    case opcode::OP_ClearFieldVariable:
    case opcode::OP_JumpOnFalse:
    case opcode::OP_JumpOnTrue:
    case opcode::OP_JumpOnFalseExpr:
    case opcode::OP_JumpOnTrueExpr:
    case opcode::OP_Jump:
    case opcode::OP_JumpBack:
    case opcode::OP_DevblockBegin:
    case opcode::OP_DevblockEnd:
        return 3;
    case opcode::OP_GetInteger:
    case opcode::OP_GetFloat:
    case opcode::OP_GetAnimation:
    case opcode::OP_GetFunction:
    case opcode::OP_Switch:
    case opcode::OP_EndSwitch:
    case opcode::OP_GetHash:
        return 5;
    case opcode::OP_CallBuiltin:
    case opcode::OP_CallBuiltinMethod:
    case opcode::OP_ScriptFunctionCall:
    case opcode::OP_ScriptMethodCall:
    case opcode::OP_ScriptThreadCall:
    case opcode::OP_ScriptMethodThreadCall:
        return 6;
    case opcode::OP_GetVector:
        return 13;
    default:
        throw std::runtime_error("Couldn't resolve instruction size for " + std::to_string(id));
    }
}

} // namespace xsk::gsc::t6
