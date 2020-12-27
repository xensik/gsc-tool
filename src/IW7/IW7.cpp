// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW7.hpp"

namespace IW7
{

auto opcode_size(opcode id) -> std::uint32_t
{
    switch (id)
    {
    case opcode::OP_End:
    case opcode::OP_Return:
    case opcode::OP_GetUndefined:
    case opcode::OP_GetSelf:
    case opcode::OP_GetLevel:
    case opcode::OP_GetAnim:
    case opcode::OP_GetGame:
    case opcode::OP_GetGameRef:
    case opcode::OP_GetSelfObject:
    case opcode::OP_GetAnimObject:
    case opcode::OP_GetLevelObject:
    case opcode::OP_GetZero:
    case opcode::OP_inc:
    case opcode::OP_dec:
    case opcode::OP_bit_or:
    case opcode::OP_bit_ex_or:
    case opcode::OP_bit_and:
    case opcode::OP_equality:
    case opcode::OP_inequality:
    case opcode::OP_less:
    case opcode::OP_greater:
    case opcode::OP_less_equal:
    case opcode::OP_greater_equal:
    case opcode::OP_shift_left:
    case opcode::OP_shift_right:
    case opcode::OP_plus:
    case opcode::OP_minus:
    case opcode::OP_multiply:
    case opcode::OP_divide:
    case opcode::OP_mod:
    case opcode::OP_size:
    case opcode::OP_CastFieldObject:
    case opcode::OP_CastBool:
    case opcode::OP_BoolNot:
    case opcode::OP_BoolComplement:
    case opcode::OP_waittillFrameEnd:
    case opcode::OP_waittill:
    case opcode::OP_notify:
    case opcode::OP_endon:
    case opcode::OP_voidCodepos:
    case opcode::OP_vector:
    case opcode::OP_clearparams:
    case opcode::OP_checkclearparams:
    case opcode::OP_wait:
    case opcode::OP_DecTop:
    case opcode::OP_EvalLocalVariableCached0:
    case opcode::OP_EvalLocalVariableCached1:
    case opcode::OP_EvalLocalVariableCached2:
    case opcode::OP_EvalLocalVariableCached3:
    case opcode::OP_EvalLocalVariableCached4:
    case opcode::OP_EvalLocalVariableCached5:
    case opcode::OP_EvalArray:
    case opcode::OP_EvalArrayRef:
    case opcode::OP_ClearArray:
    case opcode::OP_EmptyArray:
    case opcode::OP_AddArray:
    case opcode::OP_PreScriptCall:
    case opcode::OP_ScriptFunctionCallPointer:
    case opcode::OP_ScriptMethodCallPointer:
    case opcode::OP_EvalLocalVariableRefCached0:
    case opcode::OP_SetVariableField:
    case opcode::OP_SetLocalVariableFieldCached0:
    case opcode::OP_ClearLocalVariableFieldCached0:
    case opcode::OP_EvalLocalArrayRefCached0:
        return 1;
    case opcode::OP_GetByte:
    case opcode::OP_GetNegByte:
    case opcode::OP_GetAnimTree:
    case opcode::OP_CallBuiltinPointer:
    case opcode::OP_CallBuiltinMethodPointer:
    case opcode::OP_ScriptThreadCallPointer:
    case opcode::OP_ScriptMethodThreadCallPointer:
    case opcode::OP_CreateLocalVariable:
    case opcode::OP_RemoveLocalVariables:
    case opcode::OP_EvalLocalVariableCached:
    case opcode::OP_EvalLocalArrayCached:
    case opcode::OP_EvalLocalArrayRefCached:
    case opcode::OP_SafeCreateVariableFieldCached:
    case opcode::OP_SafeSetWaittillVariableFieldCached:
    case opcode::OP_EvalLocalVariableRefCached:
    case opcode::OP_SetNewLocalVariableFieldCached0:
    case opcode::OP_SetLocalVariableFieldCached:
    case opcode::OP_ClearLocalVariableFieldCached:
    case opcode::OP_EvalLocalVariableObjectCached:
    case opcode::OP_EvalNewLocalArrayRefCached0:
        return 2;
    case opcode::OP_GetUnsignedShort:
    case opcode::OP_GetNegUnsignedShort:
    case opcode::OP_endswitch:
    case opcode::OP_waittillmatch:
    case opcode::OP_jumpback:
    case opcode::OP_JumpOnFalseExpr:
    case opcode::OP_JumpOnTrueExpr:
    case opcode::OP_JumpOnFalse:
    case opcode::OP_JumpOnTrue:
    case opcode::OP_GetBuiltinFunction:
    case opcode::OP_GetBuiltinMethod:
    case opcode::OP_CallBuiltin0:
    case opcode::OP_CallBuiltin1:
    case opcode::OP_CallBuiltin2:
    case opcode::OP_CallBuiltin3:
    case opcode::OP_CallBuiltin4:
    case opcode::OP_CallBuiltin5:
    case opcode::OP_CallBuiltinMethod0:
    case opcode::OP_CallBuiltinMethod1:
    case opcode::OP_CallBuiltinMethod2:
    case opcode::OP_CallBuiltinMethod3:
    case opcode::OP_CallBuiltinMethod4:
    case opcode::OP_CallBuiltinMethod5:
        return 3;
    case opcode::OP_GetLocalFunction:
    case opcode::OP_GetFarFunction:
    case opcode::OP_CallBuiltin:
    case opcode::OP_CallBuiltinMethod:
    case opcode::OP_ScriptLocalFunctionCall2:
    case opcode::OP_ScriptLocalFunctionCall:
    case opcode::OP_ScriptLocalMethodCall:
    case opcode::OP_ScriptFarFunctionCall2:
    case opcode::OP_ScriptFarFunctionCall:
    case opcode::OP_ScriptFarMethodCall:
        return 4;
    case opcode::OP_GetInteger:
    case opcode::OP_GetFloat:
    case opcode::OP_GetString:
    case opcode::OP_GetIString:
    case opcode::OP_switch:
    case opcode::OP_jump:
    case opcode::OP_ScriptLocalThreadCall:
    case opcode::OP_ScriptLocalChildThreadCall:
    case opcode::OP_ScriptLocalMethodThreadCall:
    case opcode::OP_ScriptLocalMethodChildThreadCall:
    case opcode::OP_ScriptFarThreadCall:
    case opcode::OP_ScriptFarMethodThreadCall:
    case opcode::OP_EvalLevelFieldVariable:
    case opcode::OP_EvalAnimFieldVariable:
    case opcode::OP_EvalSelfFieldVariable:
    case opcode::OP_EvalFieldVariable:
    case opcode::OP_EvalLevelFieldVariableRef:
    case opcode::OP_EvalAnimFieldVariableRef:
    case opcode::OP_EvalSelfFieldVariableRef:
    case opcode::OP_EvalFieldVariableRef:
    case opcode::OP_ClearFieldVariable:
    case opcode::OP_SetLevelFieldVariableField:
    case opcode::OP_SetAnimFieldVariableField:
    case opcode::OP_SetSelfFieldVariableField:
        return 5;
    case opcode::OP_GetAnimation:
        return 9;
    case opcode::OP_GetVector:
        return 13;
    default:
        LOG_ERROR("Couldn't resolve instruction size for 0x%hhX!", id);
        return 0;
    }
}

} // namespace IW7
