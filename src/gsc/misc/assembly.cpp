// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"
#include "assembly.hpp"

namespace xsk::gsc
{

std::array<std::pair<opcode, std::string_view>, opcode_count> const opcode_list
{{
    { opcode::vm_invalid, "vm_invalid" },
    { opcode::OP_CastFieldObject, "OP_CastFieldObject" },
    { opcode::OP_SetLocalVariableFieldCached, "OP_SetLocalVariableFieldCached" },
    { opcode::OP_plus, "OP_plus" },
    { opcode::OP_RemoveLocalVariables, "OP_RemoveLocalVariables" },
    { opcode::OP_EvalSelfFieldVariableRef, "OP_EvalSelfFieldVariableRef" },
    { opcode::OP_ScriptFarMethodChildThreadCall, "OP_ScriptFarMethodChildThreadCall" },
    { opcode::OP_GetGameRef, "OP_GetGameRef" },
    { opcode::OP_EvalAnimFieldVariable, "OP_EvalAnimFieldVariable" },
    { opcode::OP_EvalLevelFieldVariableRef, "OP_EvalLevelFieldVariableRef" },
    { opcode::OP_GetThisthread, "OP_GetThisthread" },
    { opcode::OP_greater, "OP_greater" },
    { opcode::OP_waittillmatch, "OP_waittillmatch" },
    { opcode::OP_shift_right, "OP_shift_right" },
    { opcode::OP_dec, "OP_dec" },
    { opcode::OP_JumpOnTrue, "OP_JumpOnTrue" },
    { opcode::OP_bit_or, "OP_bit_or" },
    { opcode::OP_equality, "OP_equality" },
    { opcode::OP_ClearLocalVariableFieldCached0, "OP_ClearLocalVariableFieldCached0" },
    { opcode::OP_notify, "OP_notify" },
    { opcode::OP_GetVector, "OP_GetVector" },
    { opcode::OP_ScriptMethodChildThreadCallPointer, "OP_ScriptMethodChildThreadCallPointer" },
    { opcode::OP_PreScriptCall, "OP_PreScriptCall" },
    { opcode::OP_GetByte, "OP_GetByte" },
    { opcode::OP_ScriptFarThreadCall, "OP_ScriptFarThreadCall" },
    { opcode::OP_SetSelfFieldVariableField, "OP_SetSelfFieldVariableField" },
    { opcode::OP_JumpOnFalseExpr, "OP_JumpOnFalseExpr" },
    { opcode::OP_GetUndefined, "OP_GetUndefined" },
    { opcode::OP_jumpback, "OP_jumpback" },
    { opcode::OP_JumpOnTrueExpr, "OP_JumpOnTrueExpr" },
    { opcode::OP_CallBuiltin0, "OP_CallBuiltin0" },
    { opcode::OP_CallBuiltin1, "OP_CallBuiltin1" },
    { opcode::OP_CallBuiltin2, "OP_CallBuiltin2" },
    { opcode::OP_CallBuiltin3, "OP_CallBuiltin3" },
    { opcode::OP_CallBuiltin4, "OP_CallBuiltin4" },
    { opcode::OP_CallBuiltin5, "OP_CallBuiltin5" },
    { opcode::OP_CallBuiltin, "OP_CallBuiltin" },
    { opcode::OP_SetLocalVariableFieldCached0, "OP_SetLocalVariableFieldCached0" },
    { opcode::OP_ClearFieldVariable, "OP_ClearFieldVariable" },
    { opcode::OP_GetLevel, "OP_GetLevel" },
    { opcode::OP_size, "OP_size" },
    { opcode::OP_SafeSetWaittillVariableFieldCached, "OP_SafeSetWaittillVariableFieldCached" },
    { opcode::OP_ScriptLocalMethodThreadCall, "OP_ScriptLocalMethodThreadCall" },
    { opcode::OP_AddArray, "OP_AddArray" },
    { opcode::OP_endon, "OP_endon" },
    { opcode::OP_EvalFieldVariable, "OP_EvalFieldVariable" },
    { opcode::OP_shift_left, "OP_shift_left" },
    { opcode::OP_EvalLocalArrayRefCached0, "OP_EvalLocalArrayRefCached0" },
    { opcode::OP_Return, "OP_Return" },
    { opcode::OP_CreateLocalVariable, "OP_CreateLocalVariable" },
    { opcode::OP_SafeSetVariableFieldCached0, "OP_SafeSetVariableFieldCached0" },
    { opcode::OP_GetBuiltinFunction, "OP_GetBuiltinFunction" },
    { opcode::OP_ScriptLocalMethodCall, "OP_ScriptLocalMethodCall" },
    { opcode::OP_CallBuiltinMethodPointer, "OP_CallBuiltinMethodPointer" },
    { opcode::OP_ScriptLocalChildThreadCall, "OP_ScriptLocalChildThreadCall" },
    { opcode::OP_GetSelfObject, "OP_GetSelfObject" },
    { opcode::OP_GetGame, "OP_GetGame" },
    { opcode::OP_SetLevelFieldVariableField, "OP_SetLevelFieldVariableField" },
    { opcode::OP_EvalArray, "OP_EvalArray" },
    { opcode::OP_GetSelf, "OP_GetSelf" },
    { opcode::OP_End, "OP_End" },
    { opcode::OP_EvalSelfFieldVariable, "OP_EvalSelfFieldVariable" },
    { opcode::OP_less_equal, "OP_less_equal" },
    { opcode::OP_EvalLocalVariableCached0, "OP_EvalLocalVariableCached0" },
    { opcode::OP_EvalLocalVariableCached1, "OP_EvalLocalVariableCached1" },
    { opcode::OP_EvalLocalVariableCached2, "OP_EvalLocalVariableCached2" },
    { opcode::OP_EvalLocalVariableCached3, "OP_EvalLocalVariableCached3" },
    { opcode::OP_EvalLocalVariableCached4, "OP_EvalLocalVariableCached4" },
    { opcode::OP_EvalLocalVariableCached5, "OP_EvalLocalVariableCached5" },
    { opcode::OP_EvalLocalVariableCached, "OP_EvalLocalVariableCached" },
    { opcode::OP_EvalNewLocalArrayRefCached0, "OP_EvalNewLocalArrayRefCached0" },
    { opcode::OP_ScriptChildThreadCallPointer, "OP_ScriptChildThreadCallPointer" },
    { opcode::OP_EvalLocalVariableObjectCached, "OP_EvalLocalVariableObjectCached" },
    { opcode::OP_ScriptLocalThreadCall, "OP_ScriptLocalThreadCall" },
    { opcode::OP_GetInteger, "OP_GetInteger" },
    { opcode::OP_ScriptMethodCallPointer, "OP_ScriptMethodCallPointer" },
    { opcode::OP_checkclearparams, "OP_checkclearparams" },
    { opcode::OP_SetAnimFieldVariableField, "OP_SetAnimFieldVariableField" },
    { opcode::OP_waittillmatch2, "OP_waittillmatch2" },
    { opcode::OP_minus, "OP_minus" },
    { opcode::OP_ScriptLocalFunctionCall2, "OP_ScriptLocalFunctionCall2" },
    { opcode::OP_GetNegUnsignedShort, "OP_GetNegUnsignedShort" },
    { opcode::OP_GetNegByte, "OP_GetNegByte" },
    { opcode::OP_SafeCreateVariableFieldCached, "OP_SafeCreateVariableFieldCached" },
    { opcode::OP_greater_equal, "OP_greater_equal" },
    { opcode::OP_vector, "OP_vector" },
    { opcode::OP_GetBuiltinMethod, "OP_GetBuiltinMethod" },
    { opcode::OP_endswitch, "OP_endswitch" },
    { opcode::OP_ClearArray, "OP_ClearArray" },
    { opcode::OP_DecTop, "OP_DecTop" },
    { opcode::OP_CastBool, "OP_CastBool" },
    { opcode::OP_EvalArrayRef, "OP_EvalArrayRef" },
    { opcode::OP_SetNewLocalVariableFieldCached0, "OP_SetNewLocalVariableFieldCached0" },
    { opcode::OP_GetZero, "OP_GetZero" },
    { opcode::OP_wait, "OP_wait" },
    { opcode::OP_waittill, "OP_waittill" },
    { opcode::OP_GetIString, "OP_GetIString" },
    { opcode::OP_ScriptFarFunctionCall, "OP_ScriptFarFunctionCall" },
    { opcode::OP_GetAnimObject, "OP_GetAnimObject" },
    { opcode::OP_GetAnimTree, "OP_GetAnimTree" },
    { opcode::OP_EvalLocalArrayCached, "OP_EvalLocalArrayCached" },
    { opcode::OP_mod, "OP_mod" },
    { opcode::OP_ScriptFarMethodThreadCall, "OP_ScriptFarMethodThreadCall" },
    { opcode::OP_GetUnsignedShort, "OP_GetUnsignedShort" },
    { opcode::OP_clearparams, "OP_clearparams" },
    { opcode::OP_ScriptMethodThreadCallPointer, "OP_ScriptMethodThreadCallPointer" },
    { opcode::OP_ScriptFunctionCallPointer, "OP_ScriptFunctionCallPointer" },
    { opcode::OP_EmptyArray, "OP_EmptyArray" },
    { opcode::OP_SafeSetVariableFieldCached, "OP_SafeSetVariableFieldCached" },
    { opcode::OP_ClearVariableField, "OP_ClearVariableField" },
    { opcode::OP_EvalFieldVariableRef, "OP_EvalFieldVariableRef" },
    { opcode::OP_ScriptLocalMethodChildThreadCall, "OP_ScriptLocalMethodChildThreadCall" },
    { opcode::OP_EvalNewLocalVariableRefCached0, "OP_EvalNewLocalVariableRefCached0" },
    { opcode::OP_GetFloat, "OP_GetFloat" },
    { opcode::OP_EvalLocalVariableRefCached, "OP_EvalLocalVariableRefCached" },
    { opcode::OP_JumpOnFalse, "OP_JumpOnFalse" },
    { opcode::OP_BoolComplement, "OP_BoolComplement" },
    { opcode::OP_ScriptThreadCallPointer, "OP_ScriptThreadCallPointer" },
    { opcode::OP_ScriptFarFunctionCall2, "OP_ScriptFarFunctionCall2" },
    { opcode::OP_less, "OP_less" },
    { opcode::OP_BoolNot, "OP_BoolNot" },
    { opcode::OP_waittillFrameEnd, "OP_waittillFrameEnd" },
    { opcode::OP_waitframe, "OP_waitframe" },
    { opcode::OP_GetString, "OP_GetString" },
    { opcode::OP_EvalLevelFieldVariable, "OP_EvalLevelFieldVariable" },
    { opcode::OP_GetLevelObject, "OP_GetLevelObject" },
    { opcode::OP_inc, "OP_inc" },
    { opcode::OP_CallBuiltinMethod0, "OP_CallBuiltinMethod0" },
    { opcode::OP_CallBuiltinMethod1, "OP_CallBuiltinMethod1" },
    { opcode::OP_CallBuiltinMethod2, "OP_CallBuiltinMethod2" },
    { opcode::OP_CallBuiltinMethod3, "OP_CallBuiltinMethod3" },
    { opcode::OP_CallBuiltinMethod4, "OP_CallBuiltinMethod4" },
    { opcode::OP_CallBuiltinMethod5, "OP_CallBuiltinMethod5" },
    { opcode::OP_CallBuiltinMethod, "OP_CallBuiltinMethod" },
    { opcode::OP_GetAnim, "OP_GetAnim" },
    { opcode::OP_switch, "OP_switch" },
    { opcode::OP_SetVariableField, "OP_SetVariableField" },
    { opcode::OP_divide, "OP_divide" },
    { opcode::OP_GetLocalFunction, "OP_GetLocalFunction" },
    { opcode::OP_ScriptFarChildThreadCall, "OP_ScriptFarChildThreadCall" },
    { opcode::OP_multiply, "OP_multiply" },
    { opcode::OP_ClearLocalVariableFieldCached, "OP_ClearLocalVariableFieldCached" },
    { opcode::OP_EvalAnimFieldVariableRef, "OP_EvalAnimFieldVariableRef" },
    { opcode::OP_EvalLocalArrayRefCached, "OP_EvalLocalArrayRefCached" },
    { opcode::OP_EvalLocalVariableRefCached0, "OP_EvalLocalVariableRefCached0" },
    { opcode::OP_bit_and, "OP_bit_and" },
    { opcode::OP_GetAnimation, "OP_GetAnimation" },
    { opcode::OP_GetFarFunction, "OP_GetFarFunction" },
    { opcode::OP_CallBuiltinPointer, "OP_CallBuiltinPointer" },
    { opcode::OP_jump, "OP_jump" },
    { opcode::OP_voidCodepos, "OP_voidCodepos" },
    { opcode::OP_ScriptFarMethodCall, "OP_ScriptFarMethodCall" },
    { opcode::OP_inequality, "OP_inequality" },
    { opcode::OP_ScriptLocalFunctionCall, "OP_ScriptLocalFunctionCall" },
    { opcode::OP_bit_ex_or, "OP_bit_ex_or" },
    { opcode::OP_NOP, "OP_NOP" },
    { opcode::OP_abort, "OP_abort" },
    { opcode::OP_object, "OP_object" },
    { opcode::OP_thread_object, "OP_thread_object" },
    { opcode::OP_EvalLocalVariable, "OP_EvalLocalVariable" },
    { opcode::OP_EvalLocalVariableRef, "OP_EvalLocalVariableRef" },
    { opcode::OP_prof_begin, "OP_prof_begin" },
    { opcode::OP_prof_end, "OP_prof_end" },
    { opcode::OP_breakpoint, "OP_breakpoint" },
    { opcode::OP_assignmentBreakpoint, "OP_assignmentBreakpoint" },
    { opcode::OP_manualAndAssignmentBreakpoint, "OP_manualAndAssignmentBreakpoint" },
    { opcode::OP_BoolNotAfterAnd, "OP_BoolNotAfterAnd" },
    { opcode::OP_FormalParams, "OP_FormalParams" },
    { opcode::OP_IsDefined, "OP_IsDefined" },
    { opcode::OP_IsTrue, "OP_IsTrue" },
    { opcode::OP_NativeGetLocalFunction, "OP_NativeGetLocalFunction" },
    { opcode::OP_NativeLocalFunctionCall, "OP_NativeLocalFunctionCall" },
    { opcode::OP_NativeLocalFunctionCall2, "OP_NativeLocalFunctionCall2" },
    { opcode::OP_NativeLocalMethodCall, "OP_NativeLocalMethodCall" },
    { opcode::OP_NativeLocalFunctionThreadCall, "OP_NativeLocalFunctionThreadCall" },
    { opcode::OP_NativeLocalMethodThreadCall, "OP_NativeLocalMethodThreadCall" },
    { opcode::OP_NativeLocalFunctionChildThreadCall, "OP_NativeLocalFunctionChildThreadCall" },
    { opcode::OP_NativeLocalMethodChildThreadCall, "OP_NativeLocalMethodChildThreadCall" },
    { opcode::OP_NativeGetFarFunction, "OP_NativeGetFarFunction" },
    { opcode::OP_NativeFarFunctionCall, "OP_NativeFarFunctionCall" },
    { opcode::OP_NativeFarFunctionCall2, "OP_NativeFarFunctionCall2" },
    { opcode::OP_NativeFarMethodCall, "OP_NativeFarMethodCall" },
    { opcode::OP_NativeFarFunctionThreadCall, "OP_NativeFarFunctionThreadCall" },
    { opcode::OP_NativeFarMethodThreadCall, "OP_NativeFarMethodThreadCall" },
    { opcode::OP_NativeFarFunctionChildThreadCall, "OP_NativeFarFunctionChildThreadCall" },
    { opcode::OP_NativeFarMethodChildThreadCall, "OP_NativeFarMethodChildThreadCall" },
    { opcode::OP_EvalNewLocalArrayRefCached0_Precompiled, "OP_EvalNewLocalArrayRefCached0_Precompiled" },
    { opcode::OP_SetNewLocalVariableFieldCached0_Precompiled, "OP_SetNewLocalVariableFieldCached0_Precompiled" },
    { opcode::OP_CreateLocalVariable_Precompiled, "OP_CreateLocalVariable_Precompiled" },
    { opcode::OP_SafeCreateVariableFieldCached_Precompiled, "OP_SafeCreateVariableFieldCached_Precompiled" },
    { opcode::OP_FormalParams_Precompiled, "OP_FormalParams_Precompiled" },
    { opcode::OP_GetStatHash, "OP_GetStatHash" },
    { opcode::OP_GetUnkxHash, "OP_GetUnkxHash" },
    { opcode::OP_GetEnumHash, "OP_GetEnumHash" },
    { opcode::OP_GetDvarHash, "OP_GetDvarHash" },
    { opcode::OP_GetUnsignedInt, "OP_GetUnsignedInt" },
    { opcode::OP_GetNegUnsignedInt, "OP_GetNegUnsignedInt" },
    { opcode::OP_GetInteger64, "OP_GetInteger64" },
    { opcode::OP_iw9_139, "OP_iw9_139" },
    { opcode::OP_iw9_140, "OP_iw9_140" },
    { opcode::OP_iw9_141, "OP_iw9_141" },
    { opcode::OP_iw9_142, "OP_iw9_142" },
    { opcode::OP_iw9_143, "OP_iw9_143" },
    { opcode::OP_iw9_144, "OP_iw9_144" },
    { opcode::OP_iw9_166, "OP_iw9_166" },
}};

std::unordered_map<opcode, std::string_view> opcode_map;
std::unordered_map<std::string_view, opcode> opcode_map_rev;

auto opcode_name(opcode op) -> std::string
{
    auto const itr = opcode_map.find(op);

    if (itr != opcode_map.end())
    {
        return std::string{ itr->second };
    }

    throw std::runtime_error(fmt::format("couldn't resolve opcode string for enum '{}'", static_cast<std::underlying_type_t<opcode>>(op)));
}

auto opcode_enum(std::string const& name) -> opcode
{
    auto const itr = opcode_map_rev.find(name);

    if (itr != opcode_map_rev.end())
    {
        return itr->second;
    }

    throw std::runtime_error(fmt::format("couldn't resolve opcode enum for name '{}'", name));
}

struct __init__
{
    __init__()
    {
        static bool init = false;
        if (init) return;
        init = true;

        opcode_map.reserve(opcode_list.size());
        opcode_map_rev.reserve(opcode_list.size());

        for (auto const& entry : opcode_list)
        {
            opcode_map.insert({ entry.first, entry.second });
            opcode_map_rev.insert({ entry.second, entry.first });
        }
    }
} _;

} // namespace xsk::gsc
