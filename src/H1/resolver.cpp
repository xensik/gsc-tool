// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "H1.hpp"

namespace H1
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

    LOG_ERROR("Couldn't resolve opcode id for name '%s'!", name.data());
    return opcode::OP_Count;
}

auto resolver::opcode_name(opcode id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return itr->second;
    }

    LOG_ERROR("Couldn't resolve opcode name for id '0x%hhX'!", id);
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

    LOG_ERROR("Couldn't resolve builtin function id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::builtin_func_name(std::uint16_t id) -> std::string
{
    const auto itr = builtin_function_map.find(id);

    if (itr != builtin_function_map.end())
    {
        return itr->second;
    }

    LOG_ERROR("Couldn't resolve builtin function name for id '%i'!", id);
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

    LOG_ERROR("Couldn't resolve builtin method id for name '%s'!", name.data());
    return 0xFFFF;
}

auto resolver::builtin_method_name(std::uint16_t id) -> std::string
{
    const auto itr = builtin_method_map.find(id);

    if (itr != builtin_method_map.end())
    {
        return itr->second;
    }

    LOG_ERROR("Couldn't resolve builtin method name for id '%i'!", id);
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

    LOG_DEBUG("missing file name for id '%i'!", id);
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

    //LOG_DEBUG("missing token name for id '%i'!", id);
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
    { opcode::OP_End, "end" },
    { opcode::OP_Return, "retn" },
    { opcode::OP_GetByte, "get_byte" },
    { opcode::OP_GetNegByte, "get_neg_byte" },
    { opcode::OP_GetUnsignedShort, "get_ushort" },
    { opcode::OP_GetNegUnsignedShort, "get_neg_ushort" },
    { opcode::OP_GetInteger, "get_int" },
    { opcode::OP_GetBuiltinFunction, "get_builtin_func" },
    { opcode::OP_GetBuiltinMethod, "get_builtin_method" },
    { opcode::OP_GetFloat, "get_float" },
    { opcode::OP_GetString, "get_string" },
    { opcode::OP_GetUndefined, "get_undefined" },
    { opcode::OP_GetZero, "get_zero" },
    { opcode::OP_waittillFrameEnd, "waittill_frame_end" },
    { opcode::OP_CreateLocalVariable, "create_local_variable" },
    { opcode::OP_RemoveLocalVariables, "remove_local_variables" },
    { opcode::OP_EvalLocalVariableCached0, "eval_local_variable_cached0" },
    { opcode::OP_EvalLocalVariableCached1, "eval_local_variable_cached1" },
    { opcode::OP_EvalLocalVariableCached2, "eval_local_variable_cached2" },
    { opcode::OP_EvalLocalVariableCached3, "eval_local_variable_cached3" },
    { opcode::OP_EvalLocalVariableCached4, "eval_local_variable_cached4" },
    { opcode::OP_EvalLocalVariableCached5, "eval_local_variable_cached5" },
    { opcode::OP_EvalLocalVariableCached, "eval_local_variable_cached" },
    { opcode::OP_EvalLocalArrayCached, "eval_local_array_cached" },
    { opcode::OP_EvalArray, "eval_array" },
    { opcode::OP_EvalNewLocalArrayRefCached0, "eval_new_local_array_ref_cached0" },
    { opcode::OP_EvalLocalArrayRefCached0, "eval_local_array_ref_cached0" },
    { opcode::OP_EvalLocalArrayRefCached, "eval_local_array_ref_cached" },
    { opcode::OP_EvalArrayRef, "eval_array_ref" },
    { opcode::OP_ClearArray, "clear_array" },
    { opcode::OP_EmptyArray, "empty_array" },
    { opcode::OP_AddArray, "add_array" },
    { opcode::OP_PreScriptCall, "pre_script_call" },
    { opcode::OP_ScriptLocalFunctionCall2, "script_local_func_call2" },
    { opcode::OP_ScriptLocalFunctionCall, "script_local_func_call" },
    { opcode::OP_ScriptLocalMethodCall, "script_local_method_call" },
    { opcode::OP_ScriptLocalThreadCall, "script_local_thread_call" },
    { opcode::OP_ScriptLocalChildThreadCall, "script_local_child_thread_call" },
    { opcode::OP_ScriptLocalMethodThreadCall, "script_local_method_thread_call" },
    { opcode::OP_ScriptLocalMethodChildThreadCall, "script_local_method_child_thread_call" },
    { opcode::OP_ScriptFarFunctionCall2, "script_far_func_call2" },
    { opcode::OP_ScriptFarFunctionCall, "script_far_func_call" },
    { opcode::OP_ScriptFarMethodCall, "script_far_method_call" },
    { opcode::OP_ScriptFarThreadCall, "script_far_thread_call" },
    { opcode::OP_ScriptFarMethodThreadCall, "script_far_method_thread_call" },
    { opcode::OP_ScriptFunctionCallPointer, "script_func_call_pointer" },
    { opcode::OP_ScriptMethodCallPointer, "script_method_call_pointer" },
    { opcode::OP_ScriptThreadCallPointer, "script_thread_call_pointer" },
    { opcode::OP_ScriptMethodThreadCallPointer, "script_method_thread_call_pointer" },
    { opcode::OP_CallBuiltinPointer, "call_builtin_pointer" },
    { opcode::OP_CallBuiltinMethodPointer, "call_builtin_method_pointer" },
    { opcode::OP_GetIString, "get_istring" },
    { opcode::OP_GetVector, "get_vector" },
    { opcode::OP_GetLevelObject, "get_level_obj" },
    { opcode::OP_GetAnimObject, "get_anim_obj" },
    { opcode::OP_GetSelf, "get_self" },
    { opcode::OP_GetLevel, "get_level" },
    { opcode::OP_GetGame, "get_game" },
    { opcode::OP_GetAnim, "get_anim" },
    { opcode::OP_GetAnimation, "get_animation" },
    { opcode::OP_GetGameRef, "get_game_ref" },
    { opcode::OP_inc, "increment" },
    { opcode::OP_dec, "decrement" },
    { opcode::OP_bit_or, "bit_or" },
    { opcode::OP_JumpOnFalseExpr, "jump_expr<false>" },
    { opcode::OP_bit_ex_or, "bit_ex_or" },
    { opcode::OP_bit_and, "bit_and" },
    { opcode::OP_equality, "equality" },
    { opcode::OP_inequality, "inequality" },
    { opcode::OP_less, "less" },
    { opcode::OP_greater, "greater" },
    { opcode::OP_JumpOnTrueExpr, "jump_expr<true>" },
    { opcode::OP_less_equal, "less_equal" },
    { opcode::OP_jumpback, "jump_back" },
    { opcode::OP_waittill, "waittill" },
    { opcode::OP_notify, "notify" },
    { opcode::OP_endon, "endon" },
    { opcode::OP_voidCodepos, "void_codepos" },
    { opcode::OP_switch, "switch" },
    { opcode::OP_endswitch, "endswitch" },
    { opcode::OP_vector, "vector" },
    { opcode::OP_JumpOnFalse, "jump<false>" },
    { opcode::OP_greater_equal, "greater_equal" },
    { opcode::OP_shift_left, "shift_left" },
    { opcode::OP_shift_right, "shift_right" },
    { opcode::OP_plus, "plus" },
    { opcode::OP_jump, "jump" },
    { opcode::OP_minus, "minus" },
    { opcode::OP_multiply, "multiply" },
    { opcode::OP_divide, "divide" },
    { opcode::OP_mod, "mod" },
    { opcode::OP_JumpOnTrue, "jump<true>" },
    { opcode::OP_size, "size" },
    { opcode::OP_waittillmatch, "waittillmatch" },
    { opcode::OP_GetLocalFunction, "get_local_func" },
    { opcode::OP_GetFarFunction, "get_far_func" },
    { opcode::OP_GetSelfObject, "get_self_obj" },
    { opcode::OP_EvalLevelFieldVariable, "eval_level_field_variable" },
    { opcode::OP_EvalAnimFieldVariable, "eval_anim_field_variable" },
    { opcode::OP_EvalSelfFieldVariable, "eval_self_field_variable" },
    { opcode::OP_EvalFieldVariable, "eval_field_variable" },
    { opcode::OP_EvalLevelFieldVariableRef, "eval_level_field_variable_ref" },
    { opcode::OP_EvalAnimFieldVariableRef, "eval_anim_field_variable_ref" },
    { opcode::OP_EvalSelfFieldVariableRef, "eval_self_field_variable_ref" },
    { opcode::OP_EvalFieldVariableRef, "eval_field_variable_ref" },
    { opcode::OP_ClearFieldVariable, "clear_field_variable" },
    { opcode::OP_SafeCreateVariableFieldCached, "safe_create_variable_field_cached" },
    { opcode::OP_SafeSetWaittillVariableFieldCached, "safe_set_waittill_variable_field_cached" },
    { opcode::OP_GetAnimTree, "get_animtree" },
    { opcode::OP_clearparams, "clearparams" },
    { opcode::OP_checkclearparams, "checkclearparams" },
    { opcode::OP_EvalLocalVariableRefCached0, "eval_local_variable_ref_cached0" },
    { opcode::OP_EvalLocalVariableRefCached, "eval_local_variable_ref_cached" },
    { opcode::OP_SetLevelFieldVariableField, "set_level_field_variable_field" },
    { opcode::OP_SetVariableField, "set_variable_field" },
    { opcode::OP_SetAnimFieldVariableField, "set_anim_field_variable_field" },
    { opcode::OP_SetSelfFieldVariableField, "set_self_field_variable_field" },
    { opcode::OP_SetLocalVariableFieldCached0, "set_local_variable_field_cached0" },
    { opcode::OP_SetNewLocalVariableFieldCached0, "set_new_local_variable_field_cached0" },
    { opcode::OP_SetLocalVariableFieldCached, "set_local_variable_field_cached" },
    { opcode::OP_ClearLocalVariableFieldCached, "clear_local_variable_field_cached" },
    { opcode::OP_ClearLocalVariableFieldCached0, "clear_local_variable_field_cached0" },
    { opcode::OP_CallBuiltin0, "call<0>" },
    { opcode::OP_CallBuiltin1, "call<1>" },
    { opcode::OP_CallBuiltin2, "call<2>" },
    { opcode::OP_CallBuiltin3, "call<3>" },
    { opcode::OP_CallBuiltin4, "call<4>" },
    { opcode::OP_CallBuiltin5, "call<5>" },
    { opcode::OP_CallBuiltin, "call" },
    { opcode::OP_CallBuiltinMethod0, "method<0>" },
    { opcode::OP_CallBuiltinMethod1, "method<1>" },
    { opcode::OP_CallBuiltinMethod2, "method<2>" },
    { opcode::OP_CallBuiltinMethod3, "method<3>" },
    { opcode::OP_CallBuiltinMethod4, "method<4>" },
    { opcode::OP_CallBuiltinMethod5, "method<5>" },
    { opcode::OP_CallBuiltinMethod, "method" },
    { opcode::OP_wait, "wait" },
    { opcode::OP_DecTop, "decrement_top" },
    { opcode::OP_CastFieldObject, "cast_field_obj" },
    { opcode::OP_EvalLocalVariableObjectCached, "eval_local_variable_obj_cached" },
    { opcode::OP_CastBool, "cast_bool" },
    { opcode::OP_BoolNot, "bool_not" },
    { opcode::OP_BoolComplement, "bool_complement" },
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

} // namespace H1
