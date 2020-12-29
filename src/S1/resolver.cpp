// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "S1.hpp"

namespace S1
{

auto resolver::opcode_id(const std::string& name) -> opcode
{
    for (auto& opcode : opcode_map)
    {
        if (opcode.second == name)
        {
            return opcode.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve opcode id for name '%s'!", name.data());
    return opcode::OP_Count;
}

auto resolver::opcode_name(opcode id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve opcode name for id '0x%hhX'!", id);
    return "";
}

auto resolver::builtin_func_id(const std::string& name) -> std::uint16_t
{
    for (auto& func : builtin_function_map)
    {
        if (utils::string::to_lower(func.second) == utils::string::to_lower(name))
        {
            return func.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve builtin function id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::builtin_func_name(std::uint16_t id) -> std::string
{
    const auto itr = builtin_function_map.find(id);

    if (itr != builtin_function_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve builtin function name for id '%i'!", id);
    return utils::string::va("_ID%i", id);
}

auto resolver::builtin_method_id(const std::string& name) -> std::uint16_t
{
    for (auto& method : builtin_method_map)
    {
        if (utils::string::to_lower(method.second) == utils::string::to_lower(name))
        {
            return method.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve builtin method id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::builtin_method_name(std::uint16_t id) -> std::string
{
    const auto itr = builtin_method_map.find(id);

    if (itr != builtin_method_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve builtin method name for id '%i'!", id);
    return utils::string::va("_ID%i", id);
}

auto resolver::file_id(const std::string& name) -> std::uint16_t
{
    for (auto& file : file_map)
    {
        if (file.second == name)
        {
            return file.first;
        }
    }

    return 0;
}

auto resolver::file_name(std::uint16_t id) -> std::string
{
    const auto itr = file_map.find(id);

    if (itr != file_map.end())
    {
        return itr->second;
    }

    GSC_LOG_DEBUG("missing file name for id '%i'!", id);
    return utils::string::va("_ID%i", id);
}

auto resolver::token_id(const std::string& name) -> std::uint16_t
{
    for (auto& token : token_map)
    {
        if (utils::string::to_lower(token.second) == name)
        {
            return token.first;
        }
    }

    return 0;
}

auto resolver::token_name(std::uint16_t id) -> std::string
{
    const auto itr = token_map.find(id);

    if (itr != token_map.end())
    {
        return itr->second;
    }

    //GSC_LOG_DEBUG("missing token name for id '%i'!", id);
    return utils::string::va("_ID%i", id);
}

auto resolver::find_builtin_func(const std::string& name) -> bool
{
    for (auto& func : builtin_function_map)
    {
        if (utils::string::to_lower(func.second) == utils::string::to_lower(name))
        {
            return true;
        }
    }

    return false;
}

auto resolver::find_builtin_meth(const std::string& name) -> bool
{
    for (auto& method : builtin_method_map)
    {
        if (utils::string::to_lower(method.second) == utils::string::to_lower(name))
        {
            return true;
        }
    }

    return false;
}

std::unordered_map<opcode, std::string> resolver::opcode_map
{
    { opcode::OP_End, "END" },
    { opcode::OP_Return, "RETN" },
    { opcode::OP_GetByte, "GET_BYTE" },
    { opcode::OP_GetNegByte, "GET_NBYTE" },
    { opcode::OP_GetUnsignedShort, "GET_USHORT" },
    { opcode::OP_GetNegUnsignedShort, "GET_NUSHORT" },
    { opcode::OP_GetInteger, "GET_INT" },
    { opcode::OP_GetBuiltinFunction, "GET_BUILTIN_FUNC" },
    { opcode::OP_GetBuiltinMethod, "GET_BUILTIN_METHOD" },
    { opcode::OP_GetFloat, "GET_FLOAT" },
    { opcode::OP_GetString, "GET_STRING" },
    { opcode::OP_GetUndefined, "GET_UNDEFINED" },
    { opcode::OP_GetZero, "GET_ZERO" },
    { opcode::OP_waittillFrameEnd, "WAITTILLFRAMEEND" },
    { opcode::OP_CreateLocalVariable, "CREATE_LOCAL_VARIABLE" },
    { opcode::OP_RemoveLocalVariables, "REMOVE_LOCAL_VARIABLES" },
    { opcode::OP_EvalLocalVariableCached0, "EVAL_LOCAL_VARIABLE_CACHED0" },
    { opcode::OP_EvalLocalVariableCached1, "EVAL_LOCAL_VARIABLE_CACHED1" },
    { opcode::OP_EvalLocalVariableCached2, "EVAL_LOCAL_VARIABLE_CACHED2" },
    { opcode::OP_EvalLocalVariableCached3, "EVAL_LOCAL_VARIABLE_CACHED3" },
    { opcode::OP_EvalLocalVariableCached4, "EVAL_LOCAL_VARIABLE_CACHED4" },
    { opcode::OP_EvalLocalVariableCached5, "EVAL_LOCAL_VARIABLE_CACHED5" },
    { opcode::OP_EvalLocalVariableCached, "EVAL_LOCAL_VARIABLE_CACHED" },
    { opcode::OP_EvalLocalArrayCached, "EVAL_LOCAL_ARRAY_CACHED" },
    { opcode::OP_EvalArray, "EVAL_ARRAY" },
    { opcode::OP_EvalNewLocalArrayRefCached0, "EVAL_NEW_LOCAL_ARRAY_REF_CACHED0" },
    { opcode::OP_EvalLocalArrayRefCached0, "EVAL_LOCAL_ARRAY_REF_CACHED0" },
    { opcode::OP_EvalLocalArrayRefCached, "EVAL_LOCAL_ARRAY_REF_CACHED" },
    { opcode::OP_EvalArrayRef, "EVAL_ARRAY_REF" },
    { opcode::OP_ClearArray, "CLEAR_ARRAY" },
    { opcode::OP_EmptyArray, "EMPTY_ARRAY" },
    { opcode::OP_AddArray, "ADD_ARRAY" },
    { opcode::OP_PreScriptCall, "PRE_CALL" },
    { opcode::OP_ScriptLocalFunctionCall2, "CALL_LOCAL_FUNC2" },
    { opcode::OP_ScriptLocalFunctionCall, "CALL_LOCAL_FUNC" },
    { opcode::OP_ScriptLocalMethodCall, "CALL_LOCAL_METHOD" },
    { opcode::OP_ScriptLocalThreadCall, "CALL_LOCAL_FUNC_THREAD" },
    { opcode::OP_ScriptLocalChildThreadCall, "CALL_LOCAL_FUNC_CHILD_THREAD" },
    { opcode::OP_ScriptLocalMethodThreadCall, "CALL_LOCAL_METHOD_THREAD" },
    { opcode::OP_ScriptLocalMethodChildThreadCall, "CALL_LOCAL_METHOD_CHILD_THREAD" },
    { opcode::OP_ScriptFarFunctionCall2, "CALL_FAR_FUNC2" },
    { opcode::OP_ScriptFarFunctionCall, "CALL_FAR_FUNC" },
    { opcode::OP_ScriptFarMethodCall, "CALL_FAR_METHOD" },
    { opcode::OP_ScriptFarThreadCall, "CALL_FAR_FUNC_THREAD" },
    { opcode::OP_ScriptFarChildThreadCall, "CALL_FAR_FUNC_CHILD_THREAD"},
    { opcode::OP_ScriptFarMethodThreadCall, "CALL_FAR_METHOD_THEAD" },
    { opcode::OP_ScriptFarMethodChildThreadCall, "CALL_FAR_METHOD_CHILD_THEAD" },
    { opcode::OP_ScriptFunctionCallPointer, "CALL_FUNC_POINTER" },
    { opcode::OP_ScriptMethodCallPointer, "CALL_METHOD_POINTER" },
    { opcode::OP_ScriptThreadCallPointer, "CALL_FUNC_THREAD_POINTER" },
    { opcode::OP_ScriptChildThreadCallPointer, "CALL_FUNC_CHILD_THREAD_POINTER" },
    { opcode::OP_ScriptMethodThreadCallPointer, "CALL_METHOD_THREAD_POINTER" },
    { opcode::OP_ScriptMethodChildThreadCallPointer, "CALL_METHOD_CHILD_THREAD_POINTER" },
    { opcode::OP_CallBuiltinPointer, "CALL_BUILTIN_FUNC_POINTER" },
    { opcode::OP_CallBuiltinMethodPointer, "CALL_BUILTIN_METHOD_POINTER" },
    { opcode::OP_GetIString, "GET_ISTRING" },
    { opcode::OP_GetVector, "GET_VECTOR" },
    { opcode::OP_GetLevelObject, "GET_LEVEL_OBJ" },
    { opcode::OP_GetAnimObject, "GET_ANIM_OBJ" },
    { opcode::OP_GetSelf, "GET_SELF" },
    { opcode::OP_GetThisthread, "GET_THISTHREAD" },
    { opcode::OP_GetLevel, "GET_LEVEL" },
    { opcode::OP_GetGame, "GET_GAME" },
    { opcode::OP_GetAnim, "GET_ANIM" },
    { opcode::OP_GetAnimation, "GET_ANIMATION" },
    { opcode::OP_GetGameRef, "GET_GAME_REF" },
    { opcode::OP_inc, "INC" },
    { opcode::OP_dec, "DEC" },
    { opcode::OP_bit_or, "BIT_OR" },
    { opcode::OP_JumpOnFalseExpr, "JMP_EXPR_FALSE" },
    { opcode::OP_bit_ex_or, "BIT_EXOR" },
    { opcode::OP_bit_and, "BIT_AND" },
    { opcode::OP_equality, "EQUALITY" },
    { opcode::OP_inequality, "INEQUALITY" },
    { opcode::OP_less, "LESS" },
    { opcode::OP_greater, "GREATER" },
    { opcode::OP_JumpOnTrueExpr, "JMP_EXPR_TRUE" },
    { opcode::OP_less_equal, "LESSEQUAL" },
    { opcode::OP_jumpback, "JMP_BACK" },
    { opcode::OP_waittillmatch2, "WAITTILLMATCH2" },
    { opcode::OP_waittill, "WAITTILL" },
    { opcode::OP_notify, "NOTIFY" },
    { opcode::OP_endon, "ENDON" },
    { opcode::OP_voidCodepos, "VOIDCODEPOS" },
    { opcode::OP_switch, "SWITCH" },
    { opcode::OP_endswitch, "ENDSWITCH" },
    { opcode::OP_vector, "VECTOR" },
    { opcode::OP_JumpOnFalse, "JMP_FALSE" },
    { opcode::OP_greater_equal, "GREATEREQUAL" },
    { opcode::OP_shift_left, "SHIFT_LEFT" },
    { opcode::OP_shift_right, "SHIFT_RIGHT" },
    { opcode::OP_plus, "PLUS" },
    { opcode::OP_jump, "JMP" },
    { opcode::OP_minus, "MINUS" },
    { opcode::OP_multiply, "MULT" },
    { opcode::OP_divide, "DIV" },
    { opcode::OP_mod, "MOD" },
    { opcode::OP_JumpOnTrue, "JMP_TRUE" },
    { opcode::OP_size, "SIZE" },
    { opcode::OP_waittillmatch, "WAITTILLMATCH" },
    { opcode::OP_GetLocalFunction, "GET_LOCAL_FUNC" },
    { opcode::OP_GetFarFunction, "GET_FAR_FUNC" },
    { opcode::OP_GetSelfObject, "GET_SELF_OBJ" },
    { opcode::OP_EvalLevelFieldVariable, "EVAL_LEVEL_FIELD_VARIABLE" },
    { opcode::OP_EvalAnimFieldVariable, "EVAL_ANIM_FIELD_VARIABLE" },
    { opcode::OP_EvalSelfFieldVariable, "EVAL_SELF_FIELD_VARIABLE" },
    { opcode::OP_EvalFieldVariable, "EVAL_FIELD_VARIABLE" },
    { opcode::OP_EvalLevelFieldVariableRef, "EVAL_LEVEL_FIELD_VARIABLE_REF" },
    { opcode::OP_EvalAnimFieldVariableRef, "EVAL_ANIM_FIELD_VARIABLE_REF" },
    { opcode::OP_EvalSelfFieldVariableRef, "EVAL_SELF_FIELD_VARIABLE_REF" },
    { opcode::OP_EvalFieldVariableRef, "EVAL_FIELD_VARIABLE_REF" },
    { opcode::OP_ClearFieldVariable, "CLEAR_FIELD_VARIABLE" },
    { opcode::OP_SafeCreateVariableFieldCached, "SAFE_CREATE_VARIABLE_FIELD_CACHED" },
    { opcode::OP_SafeSetVariableFieldCached0, "SAFE_SET_VARIABLE_FIELD_CACHED0" },
    { opcode::OP_SafeSetVariableFieldCached, "SAFE_SET_VARIABLE_FIELD_CACHED" },
    { opcode::OP_SafeSetWaittillVariableFieldCached, "SAFE_SET_WAITTILL_VARIABLE_FIELD_CACHED" },
    { opcode::OP_GetAnimTree, "GET_ANIMTREE" },
    { opcode::OP_clearparams, "CLEAR_PARAMS" },
    { opcode::OP_checkclearparams, "CHECK_CLEAR_PARAMS" },
    { opcode::OP_EvalLocalVariableRefCached0, "EVAL_LOCAL_VARIABLE_REF_CACHED0" },
    { opcode::OP_EvalNewLocalVariableRefCached0, "EVAL_NEW_LOCAL_VARIABLE_REF_CACHED0" },
    { opcode::OP_EvalLocalVariableRefCached, "EVAL_LOCAL_VARIABLE_REF_CACHED" },
    { opcode::OP_SetLevelFieldVariableField, "SET_LEVEL_FIELD_VARIABLE_FIELD" },
    { opcode::OP_SetVariableField, "SET_VARIABLE_FIELD" },
    { opcode::OP_ClearVariableField, "CLEAR_VARIABLE_FIELD" },
    { opcode::OP_SetAnimFieldVariableField, "SET_ANIM_FIELD_VARIABLE_FIELD" },
    { opcode::OP_SetSelfFieldVariableField, "SET_SELF_FIELD_VARIABLE_FIELD" },
    { opcode::OP_SetLocalVariableFieldCached0, "SET_LOCAL_VARIABLE_FIELD_CACHED0" },
    { opcode::OP_SetNewLocalVariableFieldCached0, "SET_NEW_LOCAL_VARIABLE_FIELD_CACHED0" },
    { opcode::OP_SetLocalVariableFieldCached, "SET_LOCAL_VARIABLE_FIELD_CACHED" },
    { opcode::OP_ClearLocalVariableFieldCached, "CLEAR_LOCAL_VARIABLE_FIELD_CACHED" },
    { opcode::OP_ClearLocalVariableFieldCached0, "CLEAR_LOCAL_VARIABLE_FIELD_CACHED0" },
    { opcode::OP_CallBuiltin0, "CALL_BUILTIN_FUNC_0" },
    { opcode::OP_CallBuiltin1, "CALL_BUILTIN_FUNC_1" },
    { opcode::OP_CallBuiltin2, "CALL_BUILTIN_FUNC_2" },
    { opcode::OP_CallBuiltin3, "CALL_BUILTIN_FUNC_3" },
    { opcode::OP_CallBuiltin4, "CALL_BUILTIN_FUNC_4" },
    { opcode::OP_CallBuiltin5, "CALL_BUILTIN_FUNC_5" },
    { opcode::OP_CallBuiltin, "CALL_BUILTIN_FUNC" },
    { opcode::OP_CallBuiltinMethod0, "CALL_BUILTIN_METHOD_0" },
    { opcode::OP_CallBuiltinMethod1, "CALL_BUILTIN_METHOD_1" },
    { opcode::OP_CallBuiltinMethod2, "CALL_BUILTIN_METHOD_2" },
    { opcode::OP_CallBuiltinMethod3, "CALL_BUILTIN_METHOD_3" },
    { opcode::OP_CallBuiltinMethod4, "CALL_BUILTIN_METHOD_4" },
    { opcode::OP_CallBuiltinMethod5, "CALL_BUILTIN_METHOD_5" },
    { opcode::OP_CallBuiltinMethod, "CALL_BUILTIN_METHOD" },
    { opcode::OP_wait, "WAIT" },
    { opcode::OP_DecTop, "DEC_TOP" },
    { opcode::OP_CastFieldObject, "CAST_FIELD_OBJ" },
    { opcode::OP_EvalLocalVariableObjectCached, "EVAL_LOCAL_VARIABLE_OBJECT_CACHED" },
    { opcode::OP_CastBool, "CAST_BOOL" },
    { opcode::OP_BoolNot, "BOOL_NOT" },
    { opcode::OP_BoolComplement, "BOOL_COMPLEMENT" },
    { opcode::OP_waitFrame, "WAITFRAME" },
};

std::unordered_map<std::uint16_t, std::string> resolver::builtin_function_map
{

};

std::unordered_map<std::uint16_t, std::string> resolver::builtin_method_map
{

};

std::unordered_map<std::uint16_t, std::string> resolver::file_map
{

};

std::unordered_map<std::uint16_t, std::string> resolver::token_map
{

};

} // namespace S1
