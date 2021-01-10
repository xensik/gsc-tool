// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "H2.hpp"

namespace H2
{

std::unordered_map<std::uint8_t, std::string> opcode_map;
std::unordered_map<std::uint16_t, std::string> function_map;
std::unordered_map<std::uint16_t, std::string> method_map;
std::unordered_map<std::uint16_t, std::string> file_map;
std::unordered_map<std::uint16_t, std::string> token_map;

auto resolver::opcode_id(const std::string& name) -> std::uint8_t
{
    for (auto& opcode : opcode_map)
    {
        if (opcode.second == name)
        {
            return opcode.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve opcode id for name '%s'!", name.data());
    return 0xFF;
}

auto resolver::opcode_name(std::uint8_t id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve opcode name for id '0x%hhX'!", id);
    return "";
}

auto resolver::function_id(const std::string& name) -> std::uint16_t
{
    for (auto& func : function_map)
    {
        if (func.second == name)
        {
            return func.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve builtin function id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::function_name(std::uint16_t id) -> std::string
{
    const auto itr = function_map.find(id);

    if (itr != function_map.end())
    {
        return itr->second;
    }

    GSC_LOG_ERROR("Couldn't resolve builtin function name for id '%i'!", id);
    return utils::string::va("_ID%i", id);
}

auto resolver::method_id(const std::string& name) -> std::uint16_t
{
    for (auto& method : method_map)
    {
        if (method.second == name)
        {
            return method.first;
        }
    }

    GSC_LOG_ERROR("Couldn't resolve builtin method id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::method_name(std::uint16_t id) -> std::string
{
    const auto itr = method_map.find(id);

    if (itr != method_map.end())
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

    return utils::string::va("_ID%i", id);
}

auto resolver::find_function(const std::string& name) -> bool
{
    for (auto& func : function_map)
    {
        if (func.second == name)
        {
            return true;
        }
    }

    return false;
}

auto resolver::find_method(const std::string& name) -> bool
{
    for (auto& method : method_map)
    {
        if (method.second == name)
        {
            return true;
        }
    }

    return false;
}

const std::array<gsc::pair_8C, 154> opcode_list
{{
    { std::uint8_t(opcode::OP_End),"END" },
    { std::uint8_t(opcode::OP_Return),"RETN" },
    { std::uint8_t(opcode::OP_GetByte),"GET_BYTE" },
    { std::uint8_t(opcode::OP_GetNegByte),"GET_NBYTE" },
    { std::uint8_t(opcode::OP_GetUnsignedShort),"GET_USHORT" },
    { std::uint8_t(opcode::OP_GetNegUnsignedShort),"GET_NUSHORT" },
    { std::uint8_t(opcode::OP_GetInteger),"GET_INT" },
    { std::uint8_t(opcode::OP_GetBuiltinFunction),"GET_BUILTIN_FUNC" },
    { std::uint8_t(opcode::OP_GetBuiltinMethod),"GET_BUILTIN_METHOD" },
    { std::uint8_t(opcode::OP_GetFloat),"GET_FLOAT" },
    { std::uint8_t(opcode::OP_GetString),"GET_STRING" },
    { std::uint8_t(opcode::OP_GetUndefined),"GET_UNDEFINED" },
    { std::uint8_t(opcode::OP_GetZero),"GET_ZERO" },
    { std::uint8_t(opcode::OP_waittillFrameEnd),"WAITTILLFRAMEEND" },
    { std::uint8_t(opcode::OP_CreateLocalVariable),"CREATE_LOCAL_VARIABLE" },
    { std::uint8_t(opcode::OP_RemoveLocalVariables),"REMOVE_LOCAL_VARIABLES" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached0),"EVAL_LOCAL_VARIABLE_CACHED0" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached1),"EVAL_LOCAL_VARIABLE_CACHED1" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached2),"EVAL_LOCAL_VARIABLE_CACHED2" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached3),"EVAL_LOCAL_VARIABLE_CACHED3" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached4),"EVAL_LOCAL_VARIABLE_CACHED4" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached5),"EVAL_LOCAL_VARIABLE_CACHED5" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached),"EVAL_LOCAL_VARIABLE_CACHED" },
    { std::uint8_t(opcode::OP_EvalLocalArrayCached),"EVAL_LOCAL_ARRAY_CACHED" },
    { std::uint8_t(opcode::OP_EvalArray),"EVAL_ARRAY" },
    { std::uint8_t(opcode::OP_EvalNewLocalArrayRefCached0),"EVAL_NEW_LOCAL_ARRAY_REF_CACHED0" },
    { std::uint8_t(opcode::OP_EvalLocalArrayRefCached0),"EVAL_LOCAL_ARRAY_REF_CACHED0" },
    { std::uint8_t(opcode::OP_EvalLocalArrayRefCached),"EVAL_LOCAL_ARRAY_REF_CACHED" },
    { std::uint8_t(opcode::OP_EvalArrayRef),"EVAL_ARRAY_REF" },
    { std::uint8_t(opcode::OP_ClearArray),"CLEAR_ARRAY" },
    { std::uint8_t(opcode::OP_EmptyArray),"EMPTY_ARRAY" },
    { std::uint8_t(opcode::OP_AddArray),"ADD_ARRAY" },
    { std::uint8_t(opcode::OP_PreScriptCall),"PRE_CALL" },
    { std::uint8_t(opcode::OP_ScriptLocalFunctionCall2),"CALL_LOCAL_FUNC2" },
    { std::uint8_t(opcode::OP_ScriptLocalFunctionCall),"CALL_LOCAL_FUNC" },
    { std::uint8_t(opcode::OP_ScriptLocalMethodCall),"CALL_LOCAL_METHOD" },
    { std::uint8_t(opcode::OP_ScriptLocalThreadCall),"CALL_LOCAL_FUNC_THREAD" },
    { std::uint8_t(opcode::OP_ScriptLocalChildThreadCall),"CALL_LOCAL_FUNC_CHILD_THREAD" },
    { std::uint8_t(opcode::OP_ScriptLocalMethodThreadCall),"CALL_LOCAL_METHOD_THREAD" },
    { std::uint8_t(opcode::OP_ScriptLocalMethodChildThreadCall),"CALL_LOCAL_METHOD_CHILD_THREAD" },
    { std::uint8_t(opcode::OP_ScriptFarFunctionCall2),"CALL_FAR_FUNC2" },
    { std::uint8_t(opcode::OP_ScriptFarFunctionCall),"CALL_FAR_FUNC" },
    { std::uint8_t(opcode::OP_ScriptFarMethodCall),"CALL_FAR_METHOD" },
    { std::uint8_t(opcode::OP_ScriptFarThreadCall),"CALL_FAR_FUNC_THREAD" },
    { std::uint8_t(opcode::OP_ScriptFarChildThreadCall),"CALL_FAR_FUNC_CHILD_THREAD"},
    { std::uint8_t(opcode::OP_ScriptFarMethodThreadCall),"CALL_FAR_METHOD_THEAD" },
    { std::uint8_t(opcode::OP_ScriptFarMethodChildThreadCall),"CALL_FAR_METHOD_CHILD_THEAD" },
    { std::uint8_t(opcode::OP_ScriptFunctionCallPointer),"CALL_FUNC_POINTER" },
    { std::uint8_t(opcode::OP_ScriptMethodCallPointer),"CALL_METHOD_POINTER" },
    { std::uint8_t(opcode::OP_ScriptThreadCallPointer),"CALL_FUNC_THREAD_POINTER" },
    { std::uint8_t(opcode::OP_ScriptChildThreadCallPointer),"CALL_FUNC_CHILD_THREAD_POINTER" },
    { std::uint8_t(opcode::OP_ScriptMethodThreadCallPointer),"CALL_METHOD_THREAD_POINTER" },
    { std::uint8_t(opcode::OP_ScriptMethodChildThreadCallPointer),"CALL_METHOD_CHILD_THREAD_POINTER" },
    { std::uint8_t(opcode::OP_CallBuiltinPointer),"CALL_BUILTIN_FUNC_POINTER" },
    { std::uint8_t(opcode::OP_CallBuiltinMethodPointer),"CALL_BUILTIN_METHOD_POINTER" },
    { std::uint8_t(opcode::OP_GetIString),"GET_ISTRING" },
    { std::uint8_t(opcode::OP_GetVector),"GET_VECTOR" },
    { std::uint8_t(opcode::OP_GetLevelObject),"GET_LEVEL_OBJ" },
    { std::uint8_t(opcode::OP_GetAnimObject),"GET_ANIM_OBJ" },
    { std::uint8_t(opcode::OP_GetSelf),"GET_SELF" },
    { std::uint8_t(opcode::OP_GetThisthread),"GET_THISTHREAD" },
    { std::uint8_t(opcode::OP_GetLevel),"GET_LEVEL" },
    { std::uint8_t(opcode::OP_GetGame),"GET_GAME" },
    { std::uint8_t(opcode::OP_GetAnim),"GET_ANIM" },
    { std::uint8_t(opcode::OP_GetAnimation),"GET_ANIMATION" },
    { std::uint8_t(opcode::OP_GetGameRef),"GET_GAME_REF" },
    { std::uint8_t(opcode::OP_inc),"INC" },
    { std::uint8_t(opcode::OP_dec),"DEC" },
    { std::uint8_t(opcode::OP_bit_or),"BIT_OR" },
    { std::uint8_t(opcode::OP_JumpOnFalseExpr),"JMP_EXPR_FALSE" },
    { std::uint8_t(opcode::OP_bit_ex_or),"BIT_EXOR" },
    { std::uint8_t(opcode::OP_bit_and),"BIT_AND" },
    { std::uint8_t(opcode::OP_equality),"EQUALITY" },
    { std::uint8_t(opcode::OP_inequality),"INEQUALITY" },
    { std::uint8_t(opcode::OP_less),"LESS" },
    { std::uint8_t(opcode::OP_greater),"GREATER" },
    { std::uint8_t(opcode::OP_JumpOnTrueExpr),"JMP_EXPR_TRUE" },
    { std::uint8_t(opcode::OP_less_equal),"LESSEQUAL" },
    { std::uint8_t(opcode::OP_jumpback),"JMP_BACK" },
    { std::uint8_t(opcode::OP_waittillmatch2),"WAITTILLMATCH2" },
    { std::uint8_t(opcode::OP_waittill),"WAITTILL" },
    { std::uint8_t(opcode::OP_notify),"NOTIFY" },
    { std::uint8_t(opcode::OP_endon),"ENDON" },
    { std::uint8_t(opcode::OP_voidCodepos),"VOIDCODEPOS" },
    { std::uint8_t(opcode::OP_switch),"SWITCH" },
    { std::uint8_t(opcode::OP_endswitch),"ENDSWITCH" },
    { std::uint8_t(opcode::OP_vector),"VECTOR" },
    { std::uint8_t(opcode::OP_JumpOnFalse),"JMP_FALSE" },
    { std::uint8_t(opcode::OP_greater_equal),"GREATEREQUAL" },
    { std::uint8_t(opcode::OP_shift_left),"SHIFT_LEFT" },
    { std::uint8_t(opcode::OP_shift_right),"SHIFT_RIGHT" },
    { std::uint8_t(opcode::OP_plus),"PLUS" },
    { std::uint8_t(opcode::OP_jump),"JMP" },
    { std::uint8_t(opcode::OP_minus),"MINUS" },
    { std::uint8_t(opcode::OP_multiply),"MULT" },
    { std::uint8_t(opcode::OP_divide),"DIV" },
    { std::uint8_t(opcode::OP_mod),"MOD" },
    { std::uint8_t(opcode::OP_JumpOnTrue),"JMP_TRUE" },
    { std::uint8_t(opcode::OP_size),"SIZE" },
    { std::uint8_t(opcode::OP_waittillmatch),"WAITTILLMATCH" },
    { std::uint8_t(opcode::OP_GetLocalFunction),"GET_LOCAL_FUNC" },
    { std::uint8_t(opcode::OP_GetFarFunction),"GET_FAR_FUNC" },
    { std::uint8_t(opcode::OP_GetSelfObject),"GET_SELF_OBJ" },
    { std::uint8_t(opcode::OP_EvalLevelFieldVariable),"EVAL_LEVEL_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_EvalAnimFieldVariable),"EVAL_ANIM_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_EvalSelfFieldVariable),"EVAL_SELF_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_EvalFieldVariable),"EVAL_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_EvalLevelFieldVariableRef),"EVAL_LEVEL_FIELD_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_EvalAnimFieldVariableRef),"EVAL_ANIM_FIELD_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_EvalSelfFieldVariableRef),"EVAL_SELF_FIELD_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_EvalFieldVariableRef),"EVAL_FIELD_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_ClearFieldVariable),"CLEAR_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_SafeCreateVariableFieldCached),"SAFE_CREATE_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_SafeSetVariableFieldCached0),"SAFE_SET_VARIABLE_FIELD_CACHED0" },
    { std::uint8_t(opcode::OP_SafeSetVariableFieldCached),"SAFE_SET_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_SafeSetWaittillVariableFieldCached),"SAFE_SET_WAITTILL_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_GetAnimTree),"GET_ANIMTREE" },
    { std::uint8_t(opcode::OP_clearparams),"CLEAR_PARAMS" },
    { std::uint8_t(opcode::OP_checkclearparams),"CHECK_CLEAR_PARAMS" },
    { std::uint8_t(opcode::OP_EvalLocalVariableRefCached0),"EVAL_LOCAL_VARIABLE_REF_CACHED0" },
    { std::uint8_t(opcode::OP_EvalNewLocalVariableRefCached0),"EVAL_NEW_LOCAL_VARIABLE_REF_CACHED0" },
    { std::uint8_t(opcode::OP_EvalLocalVariableRefCached),"EVAL_LOCAL_VARIABLE_REF_CACHED" },
    { std::uint8_t(opcode::OP_SetLevelFieldVariableField),"SET_LEVEL_FIELD_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_SetVariableField),"SET_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_ClearVariableField),"CLEAR_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_SetAnimFieldVariableField),"SET_ANIM_FIELD_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_SetSelfFieldVariableField),"SET_SELF_FIELD_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_SetLocalVariableFieldCached0),"SET_LOCAL_VARIABLE_FIELD_CACHED0" },
    { std::uint8_t(opcode::OP_SetNewLocalVariableFieldCached0),"SET_NEW_LOCAL_VARIABLE_FIELD_CACHED0" },
    { std::uint8_t(opcode::OP_SetLocalVariableFieldCached),"SET_LOCAL_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_ClearLocalVariableFieldCached),"CLEAR_LOCAL_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_ClearLocalVariableFieldCached0),"CLEAR_LOCAL_VARIABLE_FIELD_CACHED0" },
    { std::uint8_t(opcode::OP_CallBuiltin0),"CALL_BUILTIN_FUNC_0" },
    { std::uint8_t(opcode::OP_CallBuiltin1),"CALL_BUILTIN_FUNC_1" },
    { std::uint8_t(opcode::OP_CallBuiltin2),"CALL_BUILTIN_FUNC_2" },
    { std::uint8_t(opcode::OP_CallBuiltin3),"CALL_BUILTIN_FUNC_3" },
    { std::uint8_t(opcode::OP_CallBuiltin4),"CALL_BUILTIN_FUNC_4" },
    { std::uint8_t(opcode::OP_CallBuiltin5),"CALL_BUILTIN_FUNC_5" },
    { std::uint8_t(opcode::OP_CallBuiltin),"CALL_BUILTIN_FUNC" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod0),"CALL_BUILTIN_METHOD_0" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod1),"CALL_BUILTIN_METHOD_1" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod2),"CALL_BUILTIN_METHOD_2" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod3),"CALL_BUILTIN_METHOD_3" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod4),"CALL_BUILTIN_METHOD_4" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod5),"CALL_BUILTIN_METHOD_5" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod),"CALL_BUILTIN_METHOD" },
    { std::uint8_t(opcode::OP_wait),"WAIT" },
    { std::uint8_t(opcode::OP_DecTop),"DEC_TOP" },
    { std::uint8_t(opcode::OP_CastFieldObject),"CAST_FIELD_OBJ" },
    { std::uint8_t(opcode::OP_EvalLocalVariableObjectCached),"EVAL_LOCAL_VARIABLE_OBJECT_CACHED" },
    { std::uint8_t(opcode::OP_CastBool),"CAST_BOOL" },
    { std::uint8_t(opcode::OP_BoolNot),"BOOL_NOT" },
    { std::uint8_t(opcode::OP_BoolComplement),"BOOL_COMPLEMENT" },
    { std::uint8_t(opcode::OP_waitFrame), "WAITFRAME" },
}};

const std::array<gsc::pair_16C, 1> function_list
{{
    { 0, "DUMMY" },
}};

const std::array<gsc::pair_16C, 1> method_list
{{
    { 0, "DUMMY" },
}};

const std::array<gsc::pair_16C, 1> file_list
{{
    { 0, "DUMMY" },
}};

const std::array<gsc::pair_16C, 1> token_list
{{
    { 0, "DUMMY" },
}};

struct __init__
{
    __init__()
    {
        static bool init = false;
        if(init) return;
        init = true;

        for(const auto& entry : opcode_list)
        {
            opcode_map.insert({ entry.key, entry.value });
        }

        for(const auto& entry : function_list)
        {
            function_map.insert({ entry.key, entry.value });
        }

        for(const auto& entry : method_list)
        {
            method_map.insert({ entry.key, entry.value });
        }

        for(const auto& entry : file_list)
        {
            file_map.insert({ entry.key, entry.value });
        }

        for(const auto& entry : token_list)
        {
            token_map.insert({ entry.key, entry.value });
        }
    }
};

__init__ _;

} // namespace H2
