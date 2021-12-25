// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "s4.hpp"

namespace xsk::gsc::s4
{

std::unordered_map<std::uint8_t, std::string> opcode_map;
std::unordered_map<std::uint16_t, std::string> function_map;
std::unordered_map<std::uint16_t, std::string> method_map;
std::unordered_map<std::uint32_t, std::string> file_map;
std::unordered_map<std::uint32_t, std::string> token_map;
std::unordered_map<std::string, std::uint8_t> opcode_map_rev;
std::unordered_map<std::string, std::uint16_t> function_map_rev;
std::unordered_map<std::string, std::uint16_t> method_map_rev;
std::unordered_map<std::string, std::uint32_t> file_map_rev;
std::unordered_map<std::string, std::uint32_t> token_map_rev;

auto resolver::opcode_id(const std::string& name) -> std::uint8_t
{
    const auto itr = opcode_map_rev.find(name);

    if (itr != opcode_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("Couldn't resolve opcode id for name '%s'!", name.data()));
}

auto resolver::opcode_name(std::uint8_t id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("Couldn't resolve opcode name for id '0x%hhX'!", id));
}

auto resolver::function_id(const std::string& name) -> std::uint16_t
{
    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("Couldn't resolve builtin function id for name '%s'!", name.data()));
}

auto resolver::function_name(std::uint16_t id) -> std::string
{
    const auto itr = function_map.find(id);

    if (itr != function_map.end())
    {
        return itr->second;
    }

    return utils::string::va("_func_%04X", id);
//  throw error(utils::string::va("Couldn't resolve builtin function name for id '%i'!", id));
}

auto resolver::method_id(const std::string& name) -> std::uint16_t
{
    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("Couldn't resolve builtin method id for name '%s'!", name.data()));
}

auto resolver::method_name(std::uint16_t id) -> std::string
{
    const auto itr = method_map.find(id);

    if (itr != method_map.end())
    {
        return itr->second;
    }

    return utils::string::va("_meth_%04X", id);
//  throw error(utils::string::va("Couldn't resolve builtin method name for id '%i'!", id));
}

auto resolver::file_id(const std::string& name) -> std::uint32_t
{
    const auto itr = file_map_rev.find(name);

    if (itr != file_map_rev.end())
    {
        return itr->second;
    }

    return 0;
}

auto resolver::file_name(std::uint32_t id) -> std::string
{
    const auto itr = file_map.find(id);

    if (itr != file_map.end())
    {
        return itr->second;
    }

    return utils::string::va("_ID%i", id);
}

auto resolver::token_id(const std::string& name) -> std::uint32_t
{
    const auto itr = token_map_rev.find(name);

    if (itr != token_map_rev.end())
    {
        return itr->second;
    }

    return 0;
}

auto resolver::token_name(std::uint32_t id) -> std::string
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
    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        return true;
    }

    return false;
}

auto resolver::find_method(const std::string& name) -> bool
{
    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        return true;
    }

    return false;
}

const std::array<pair_8C, 190> opcode_list
{{
    { std::uint8_t(opcode::OP_CastFieldObject), "CAST_FIELD_OBJECT" },
    { std::uint8_t(opcode::OP_SetLocalVariableFieldCached), "SET_LOCAL_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_plus), "PLUS" },
    { std::uint8_t(opcode::OP_RemoveLocalVariables), "REMOVE_LOCAL_VARIABLES" },
    { std::uint8_t(opcode::OP_EvalSelfFieldVariableRef), "EVAL_SELF_FIELD_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_ScriptFarMethodChildThreadCall), "SCRIPT_FAR_METHOD_CHILD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_GetGameRef), "GET_GAME_REF" },
    { std::uint8_t(opcode::OP_EvalAnimFieldVariable), "EVAL_ANIM_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_EvalLevelFieldVariableRef), "EVAL_LEVEL_FIELD_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_GetThisthread), "GET_THISTHREAD" },
    { std::uint8_t(opcode::OP_greater), "GREATER" },
    { std::uint8_t(opcode::OP_waittillmatch), "WAITTILLMATCH" },
    { std::uint8_t(opcode::OP_shift_right), "SHIFT_RIGHT" },
    { std::uint8_t(opcode::OP_dec), "DECREMENT" },
    { std::uint8_t(opcode::OP_JumpOnTrue), "JUMP_ON_TRUE" },
    { std::uint8_t(opcode::OP_bit_or), "BIT_OR" },
    { std::uint8_t(opcode::OP_equality), "EQUALITY" },
    { std::uint8_t(opcode::OP_ClearLocalVariableFieldCached0), "CLEAR_LOCAL_VARIABLE_FIELD_CACHED_0" },
    { std::uint8_t(opcode::OP_notify), "NOTIFY" },
    { std::uint8_t(opcode::OP_GetVector), "GET_VECTOR" },
    { std::uint8_t(opcode::OP_ScriptMethodChildThreadCallPointer), "SCRIPT_METHOD_CHILD_THREAD_CALL_POINTER" },
    { std::uint8_t(opcode::OP_PreScriptCall), "PRE_SCRIPT_CALL" },
    { std::uint8_t(opcode::OP_GetByte), "GET_BYTE" },
    { std::uint8_t(opcode::OP_ScriptFarThreadCall), "SCRIPT_FAR_THREAD_CALL" },
    { std::uint8_t(opcode::OP_SetSelfFieldVariableField), "SET_SELF_FIELD_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_JumpOnFalseExpr), "JUMP_ON_FALSE_EXPR" },
    { std::uint8_t(opcode::OP_GetUndefined), "GET_UNDEFINED" },
    { std::uint8_t(opcode::OP_jumpback), "JUMP_BACK" },
    { std::uint8_t(opcode::OP_JumpOnTrueExpr), "JUMP_ON_TRUE_EXPR" },
    { std::uint8_t(opcode::OP_CallBuiltin0),"CALL_BUILTIN_FUNC_0" },
    { std::uint8_t(opcode::OP_CallBuiltin1),"CALL_BUILTIN_FUNC_1" },
    { std::uint8_t(opcode::OP_CallBuiltin2),"CALL_BUILTIN_FUNC_2" },
    { std::uint8_t(opcode::OP_CallBuiltin3),"CALL_BUILTIN_FUNC_3" },
    { std::uint8_t(opcode::OP_CallBuiltin4),"CALL_BUILTIN_FUNC_4" },
    { std::uint8_t(opcode::OP_CallBuiltin5),"CALL_BUILTIN_FUNC_5" },
    { std::uint8_t(opcode::OP_CallBuiltin),"CALL_BUILTIN_FUNC" },
    { std::uint8_t(opcode::OP_SetLocalVariableFieldCached0), "SET_LOCAL_VARIABLE_FIELD_CACHED_0" },
    { std::uint8_t(opcode::OP_ClearFieldVariable), "CLEAR_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_GetLevel), "GET_LEVEL" },
    { std::uint8_t(opcode::OP_size), "SIZE" },
    { std::uint8_t(opcode::OP_SafeSetWaittillVariableFieldCached), "SAFE_SET_WAITTILL_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_ScriptLocalMethodThreadCall), "SCRIPT_LOCAL_METHOD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_AddArray), "ADD_ARRAY" },
    { std::uint8_t(opcode::OP_endon), "ENDON" },
    { std::uint8_t(opcode::OP_EvalFieldVariable), "EVAL_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_shift_left), "SHIFT_LEFT" },
    { std::uint8_t(opcode::OP_EvalLocalArrayRefCached0), "EVAL_LOCAL_ARRAY_REF_CACHED_0" },
    { std::uint8_t(opcode::OP_Return), "RETURN" },
    { std::uint8_t(opcode::OP_CreateLocalVariable), "CREATE_LOCAL_VARIABLE" },
    { std::uint8_t(opcode::OP_SafeSetVariableFieldCached0), "SAFE_SET_VARIABLE_FIELD_CACHED_0" },
    { std::uint8_t(opcode::OP_GetBuiltinFunction), "GET_BUILTIN_FUNCTION" },
    { std::uint8_t(opcode::OP_ScriptLocalMethodCall), "SCRIPT_LOCAL_METHOD_CALL" },
    { std::uint8_t(opcode::OP_CallBuiltinMethodPointer), "CALL_BUILTIN_METHOD_POINTER" },
    { std::uint8_t(opcode::OP_ScriptLocalChildThreadCall), "SCRIPT_LOCAL_CHILD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_GetSelfObject), "GET_SELF_OBJECT" },
    { std::uint8_t(opcode::OP_GetGame), "GET_GAME" },
    { std::uint8_t(opcode::OP_SetLevelFieldVariableField), "SET_LEVEL_FIELD_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_EvalArray), "EVAL_ARRAY" },
    { std::uint8_t(opcode::OP_GetSelf), "GET_SELF" },
    { std::uint8_t(opcode::OP_End), "END" },
    { std::uint8_t(opcode::OP_EvalSelfFieldVariable), "EVAL_SELF_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_less_equal), "LESS_EQUAL" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached0), "EVAL_LOCAL_VARIABLE_CACHED_0" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached1), "EVAL_LOCAL_VARIABLE_CACHED_1" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached2), "EVAL_LOCAL_VARIABLE_CACHED_2" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached3), "EVAL_LOCAL_VARIABLE_CACHED_3" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached4), "EVAL_LOCAL_VARIABLE_CACHED_4" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached5), "EVAL_LOCAL_VARIABLE_CACHED_5" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached), "EVAL_LOCAL_VARIABLE_CACHED" },
    { std::uint8_t(opcode::OP_EvalNewLocalArrayRefCached0), "EVAL_NEW_LOCAL_ARRAY_REF_CACHED_0" },
    { std::uint8_t(opcode::OP_ScriptChildThreadCallPointer), "SCRIPT_CHILD_THREAD_CALL_POINTER" },
    { std::uint8_t(opcode::OP_EvalLocalVariableObjectCached), "EVAL_LOCAL_VARIABLE_OBJECT_CACHED" },
    { std::uint8_t(opcode::OP_ScriptLocalThreadCall), "SCRIPT_LOCAL_THREAD_CALL" },
    { std::uint8_t(opcode::OP_GetInteger), "GET_INTEGER" },
    { std::uint8_t(opcode::OP_ScriptMethodCallPointer), "SCRIPT_METHOD_CALL_POINTER" },
    { std::uint8_t(opcode::OP_checkclearparams), "CHECK_CLEAR_PARAMS" },
    { std::uint8_t(opcode::OP_SetAnimFieldVariableField), "SET_ANIM_FIELD_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_waittillmatch2), "WAITTILLMATCH2" },
    { std::uint8_t(opcode::OP_minus), "MINUS" },
    { std::uint8_t(opcode::OP_ScriptLocalFunctionCall2), "SCRIPT_LOCAL_FUNCTION_CALL2" },
    { std::uint8_t(opcode::OP_GetNegUnsignedShort), "GET_NEG_USHORT" },
    { std::uint8_t(opcode::OP_GetNegByte), "GET_NEG_BYTE" },
    { std::uint8_t(opcode::OP_SafeCreateVariableFieldCached), "SAFE_CREATE_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_greater_equal), "GREATER_EQUAL" },
    { std::uint8_t(opcode::OP_vector), "VECTOR" },
    { std::uint8_t(opcode::OP_GetBuiltinMethod), "GET_BUILTIN_METHOD" },
    { std::uint8_t(opcode::OP_endswitch), "END_SWITCH" },
    { std::uint8_t(opcode::OP_ClearArray), "CLEAR_ARRAY" },
    { std::uint8_t(opcode::OP_DecTop), "DECREMENT_TOP" },
    { std::uint8_t(opcode::OP_CastBool), "CAST_BOOL" },
    { std::uint8_t(opcode::OP_EvalArrayRef), "EVAL_ARRAY_REF" },
    { std::uint8_t(opcode::OP_SetNewLocalVariableFieldCached0), "SET_NEW_LOCAL_VARIABLE_FIELD_CACHED_0" },
    { std::uint8_t(opcode::OP_GetZero), "GET_ZERO" },
    { std::uint8_t(opcode::OP_wait), "WAIT" },
    { std::uint8_t(opcode::OP_waittill), "WAITTILL" },
    { std::uint8_t(opcode::OP_GetIString), "GET_ISTRING" },
    { std::uint8_t(opcode::OP_ScriptFarFunctionCall), "SCRIPT_FAR_FUNCTION_CALL" },
    { std::uint8_t(opcode::OP_GetAnimObject), "GET_ANIM_OBJECT" },
    { std::uint8_t(opcode::OP_GetAnimTree), "GET_ANIMTREE" },
    { std::uint8_t(opcode::OP_EvalLocalArrayCached), "EVAL_LOCAL_ARRAY_CACHED" },
    { std::uint8_t(opcode::OP_mod), "MOD" },
    { std::uint8_t(opcode::OP_ScriptFarMethodThreadCall), "SCRIPT_FAR_METHOD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_GetUnsignedShort), "GET_USHORT" },
    { std::uint8_t(opcode::OP_clearparams), "CLEAR_PARAMS" },
    { std::uint8_t(opcode::OP_ScriptMethodThreadCallPointer), "SCRIPT_METHOD_THREAD_CALL_POINTER" },
    { std::uint8_t(opcode::OP_ScriptFunctionCallPointer), "SCRIPT_FUNCTION_CALL_POINTER" },
    { std::uint8_t(opcode::OP_EmptyArray), "EMPTY_ARRAY" },
    { std::uint8_t(opcode::OP_SafeSetVariableFieldCached), "SAFE_SET_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_ClearVariableField), "CLEAR_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_EvalFieldVariableRef), "EVAL_FIELD_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_ScriptLocalMethodChildThreadCall), "SCRIPT_LOCAL_METHOD_CHILD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_EvalNewLocalVariableRefCached0), "EVAL_NEW_LOCAL_VARIABLE_REF_CACHED_0" },
    { std::uint8_t(opcode::OP_GetFloat), "GET_FLOAT" },
    { std::uint8_t(opcode::OP_EvalLocalVariableRefCached), "EVAL_LOCAL_VARIABLE_REF_CACHED" },
    { std::uint8_t(opcode::OP_JumpOnFalse), "JUMP_ON_FALSE" },
    { std::uint8_t(opcode::OP_BoolComplement), "BOOL_COMPLEMENT" },
    { std::uint8_t(opcode::OP_ScriptThreadCallPointer), "SCRIPT_THREAD_CALL_POINTER" },
    { std::uint8_t(opcode::OP_ScriptFarFunctionCall2), "SCRIPT_FAR_FUNCTION_CALL2" },
    { std::uint8_t(opcode::OP_less), "LESS" },
    { std::uint8_t(opcode::OP_BoolNot), "BOOL_NOT" },
    { std::uint8_t(opcode::OP_waittillFrameEnd), "WAITTILLFRAMEEND" },
    { std::uint8_t(opcode::OP_waitframe), "WAITFRAME" },
    { std::uint8_t(opcode::OP_GetString), "GET_STRING" },
    { std::uint8_t(opcode::OP_EvalLevelFieldVariable), "EVAL_LEVEL_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_GetLevelObject), "GET_LEVEL_OBJECT" },
    { std::uint8_t(opcode::OP_inc), "INCREMENT" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod0),"CALL_BUILTIN_METHOD_0" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod1),"CALL_BUILTIN_METHOD_1" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod2),"CALL_BUILTIN_METHOD_2" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod3),"CALL_BUILTIN_METHOD_3" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod4),"CALL_BUILTIN_METHOD_4" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod5),"CALL_BUILTIN_METHOD_5" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod),"CALL_BUILTIN_METHOD" },
    { std::uint8_t(opcode::OP_GetAnim), "GET_ANIM" },
    { std::uint8_t(opcode::OP_switch), "SWITCH" },
    { std::uint8_t(opcode::OP_SetVariableField), "SET_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_divide), "DIV" },
    { std::uint8_t(opcode::OP_GetLocalFunction), "GET_LOCAL_FUNCTION" },
    { std::uint8_t(opcode::OP_ScriptFarChildThreadCall), "SCRIPT_FAR_CHILD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_multiply), "MUL" },
    { std::uint8_t(opcode::OP_ClearLocalVariableFieldCached), "CLEAR_LOCAL_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_EvalAnimFieldVariableRef), "EVAL_ANIM_FIELD_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_EvalLocalArrayRefCached), "EVAL_LOCAL_ARRAY_REF_CACHED" },
    { std::uint8_t(opcode::OP_EvalLocalVariableRefCached0), "EVAL_LOCAL_VARIABLE_REF_CACHED_0" },
    { std::uint8_t(opcode::OP_bit_and), "BIT_AND" },
    { std::uint8_t(opcode::OP_GetAnimation), "GET_ANIMATION" },
    { std::uint8_t(opcode::OP_GetFarFunction), "GET_FAR_FUNCTION" },
    { std::uint8_t(opcode::OP_CallBuiltinPointer), "CALL_BUILTIN_POINTER" },
    { std::uint8_t(opcode::OP_jump), "JUMP" },
    { std::uint8_t(opcode::OP_voidCodepos), "VOIDCODEPOS" },
    { std::uint8_t(opcode::OP_ScriptFarMethodCall), "SCRIPT_FAR_METHOD_CALL" },
    { std::uint8_t(opcode::OP_inequality), "INEQUALITY" },
    { std::uint8_t(opcode::OP_ScriptLocalFunctionCall), "SCRIPT_LOCAL_FUNCTION_CALL" },
    { std::uint8_t(opcode::OP_bit_ex_or), "BIT_EXOR" },
    { std::uint8_t(opcode::OP_NOP), "NOP" },
    { std::uint8_t(opcode::OP_abort), "ABORT" },
    { std::uint8_t(opcode::OP_object), "OBJECT" },
    { std::uint8_t(opcode::OP_thread_object), "THREAD_OBJECT" },
    { std::uint8_t(opcode::OP_EvalLocalVariable), "EVAL_LOCAL_VARIABLE" },
    { std::uint8_t(opcode::OP_EvalLocalVariableRef), "EVAL_LOCAL_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_prof_begin), "PROF_BEGIN" },
    { std::uint8_t(opcode::OP_prof_end), "PROF_END" },
    { std::uint8_t(opcode::OP_breakpoint), "BREAKPOINT" },
    { std::uint8_t(opcode::OP_assignmentBreakpoint), "ASSIGN_BREAKPOINT" },
    { std::uint8_t(opcode::OP_manualAndAssignmentBreakpoint), "MANUAL_AND_ASSIGN_BREAKPOINT" },
    { std::uint8_t(opcode::OP_BoolNotAfterAnd), "BOOL_NOT_AFTER_AND" },
    { std::uint8_t(opcode::OP_FormalParams), "FORMAL_PARAMS" },
    { std::uint8_t(opcode::OP_IsDefined), "IS_DEFINED" },
    { std::uint8_t(opcode::OP_IsTrue), "IS_TRUE" },
    { std::uint8_t(opcode::OP_NativeGetLocalFunction), "NATIVE_GET_LOCAL_FUNCTION" },
    { std::uint8_t(opcode::OP_NativeLocalFunctionCall), "NATIVE_LOCAL_FUNCTION_CALL" },
    { std::uint8_t(opcode::OP_NativeLocalFunctionCall2), "NATIVE_LOCAL_FUNCTION_CALL2" },
    { std::uint8_t(opcode::OP_NativeLocalMethodCall), "NATIVE_LOCAL_METHOD_CALL" },
    { std::uint8_t(opcode::OP_NativeLocalFunctionThreadCall), "NATIVE_LOCAL_FUNCTION_THREAD_CALL" },
    { std::uint8_t(opcode::OP_NativeLocalMethodThreadCall), "NATIVE_LOCAL_METHOD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_NativeLocalFunctionChildThreadCall), "NATIVE_LOCAL_FUNCTION_CHILD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_NativeLocalMethodChildThreadCall), "NATIVE_LOCAL_METHOD_CHILD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_NativeGetFarFunction), "NATIVE_GET_FAR_FUNCTION" },
    { std::uint8_t(opcode::OP_NativeFarFunctionCall), "NATIVE_FAR_FUNCTION_CALL" },
    { std::uint8_t(opcode::OP_NativeFarFunctionCall2), "NATIVE_FAR_FUNCTION_CALL2" },
    { std::uint8_t(opcode::OP_NativeFarMethodCall), "NATIVE_FAR_METHOD_CALL" },
    { std::uint8_t(opcode::OP_NativeFarFunctionThreadCall), "NATIVE_FAR_FUNCTION_THREAD_CALL" },
    { std::uint8_t(opcode::OP_NativeFarMethodThreadCall), "NATIVE_FAR_METHOD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_NativeFarFunctionChildThreadCall), "NATIVE_FAR_FUNCTION_CHILD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_NativeFarMethodChildThreadCall), "NATIVE_FAR_METHOD_CHILD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_EvalNewLocalArrayRefCached0_Precompiled), "EVAL_NEW_LOCAL_ARRAY_REF_CACHED_0_PRECOMPILED" },
    { std::uint8_t(opcode::OP_SetNewLocalVariableFieldCached0_Precompiled), "SET_NEW_LOCAL_VARIABLE_FIELD_CACHED_0_PRECOMPILED" },
    { std::uint8_t(opcode::OP_CreateLocalVariable_Precompiled), "CREATE_LOCAL_VARIABLE_PRECOMPILED" },
    { std::uint8_t(opcode::OP_SafeCreateVariableFieldCached_Precompiled), "SAFE_CREATE_VARIABLE_FIELD_CACHED_PRECOMPILED" },
    { std::uint8_t(opcode::OP_FormalParams_Precompiled), "FORMAL_PARAMS_PRECOMPILED" },
}};

const std::array<pair_16C, 4> function_list
{{
    { 0x08F, "getdvar" },
    { 0x09B, "getfirstarraykey" },
    { 0x0B1, "getnextarraykey" },
    { 0x126, "isusingmatchrulesdata" },
}};
const std::array<pair_16C, 1> method_list
{{
    { 0x0, "null" },
}};

const std::array<pair_32C, 1> file_list
{{
    { 0x0, "null" },
}};

const std::array<pair_32C, 4> token_list
{{
    { 0x00, "" },    // VOID
    { 0x01, "pl#" }, // PL
    { 0x02, "-" },   // MINUS
//  { 0x03, "" },    // RADIUS_TYPO
    { 0x04, ":" },   // NOTE_COLON
}};

struct __init__
{
    __init__()
    {
        static bool init = false;
        if(init) return;
        init = true;

        opcode_map.reserve(opcode_list.size());
        opcode_map_rev.reserve(opcode_list.size());
        function_map.reserve(function_list.size());
        function_map_rev.reserve(function_list.size());
        method_map.reserve(method_list.size());
        method_map_rev.reserve(method_list.size());
        file_map.reserve(file_list.size());
        file_map_rev.reserve(file_list.size());
        token_map.reserve(token_list.size());
        token_map_rev.reserve(token_list.size());

        for(const auto& entry : opcode_list)
        {
            opcode_map.insert({ entry.key, entry.value });
            opcode_map_rev.insert({ entry.value, entry.key });
        }

        for(const auto& entry : function_list)
        {
            function_map.insert({ entry.key, entry.value });
            function_map_rev.insert({ utils::string::to_lower(entry.value), entry.key });
        }

        for(const auto& entry : method_list)
        {
            method_map.insert({ entry.key, entry.value });
            method_map_rev.insert({ utils::string::to_lower(entry.value), entry.key });
        }

        for(const auto& entry : file_list)
        {
            file_map.insert({ entry.key, entry.value });
            file_map_rev.insert({ utils::string::to_lower(entry.value), entry.key });
        }

        for(const auto& entry : token_list)
        {
            token_map.insert({ entry.key, entry.value });
            token_map_rev.insert({ utils::string::to_lower(entry.value), entry.key });
        }
    }
};

__init__ _;

} // namespace xsk::gsc::s4
