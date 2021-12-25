// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "s1.hpp"

namespace xsk::gsc::s1
{

std::unordered_map<std::uint8_t, std::string> opcode_map;
std::unordered_map<std::uint16_t, std::string> function_map;
std::unordered_map<std::uint16_t, std::string> method_map;
std::unordered_map<std::uint16_t, std::string> file_map;
std::unordered_map<std::uint16_t, std::string> token_map;
std::unordered_map<std::string, std::uint8_t> opcode_map_rev;
std::unordered_map<std::string, std::uint16_t> function_map_rev;
std::unordered_map<std::string, std::uint16_t> method_map_rev;
std::unordered_map<std::string, std::uint16_t> file_map_rev;
std::unordered_map<std::string, std::uint16_t> token_map_rev;

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

    throw error(utils::string::va("Couldn't resolve builtin function name for id '%i'!", id));
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

    throw error(utils::string::va("Couldn't resolve builtin method name for id '%i'!", id));
}

auto resolver::file_id(const std::string& name) -> std::uint16_t
{
    const auto itr = file_map_rev.find(name);

    if (itr != file_map_rev.end())
    {
        return itr->second;
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

    return utils::string::va("_ID%i", id);
}

auto resolver::token_id(const std::string& name) -> std::uint16_t
{
    const auto itr = token_map_rev.find(name);

    if (itr != token_map_rev.end())
    {
        return itr->second;
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

const std::array<pair_8C, 154> opcode_list
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

const std::array<pair_16C, 735> function_list
{{
    { 0x001, "precacheturret" },
    { 0x002, "getweaponarray" },
    { 0x003, "createprintchannel" },
    { 0x004, "updategamerprofileall" },
    { 0x005, "clearlocalizedstrings" },
    { 0x006, "setphysicsgravitydir" },
    { 0x007, "gettimescale" },
    { 0x008, "settimescale" },
    { 0x009, "setslowmotionview" },
    { 0x00A, "teleportscene" },
    { 0x00B, "forcesharedammo" },
    { 0x00C, "refreshhudcompass" },
    { 0x00D, "refreshhudammocounter" },
    { 0x00E, "notifyoncommand" },
    { 0x00F, "setprintchannel" },
    { 0x010, "print" },
    { 0x011, "println" },
    { 0x012, "print3d" },
    { 0x013, "line" },
    { 0x014, "box" },
    { 0x015, "orientedbox" },
    { 0x016, "sphere" },
    { 0x017, "cylinder" },
    { 0x018, "spawnturret" },
    { 0x019, "canspawnturret" },
    { 0x01A, "assert" },
    { 0x01B, "pausecinematicingame" },
    { 0x01C, "drawcompassfriendlies" },
    { 0x01D, "bulletspread" },
    { 0x01E, "bullettracer" },
    { 0x01F, "badplace_delete" },
    { 0x020, "badplace_cylinder" },
    { 0x021, "badplace_arc" },
    { 0x022, "badplace_brush" },
    { 0x023, "_func_023" }, // SP 0x140261020
    { 0x024, "_func_024" }, // SP 0x14027EA80
    { 0x025, "_func_025" }, // SP 0x14027EB20
    { 0x026, "_func_026" }, // SP 0x14027E9B0
    { 0x027, "_func_027" }, // SP 0x14027E870
    { 0x028, "_func_028" }, // empty
    { 0x029, "_func_029" }, // empty
    { 0x02A, "_func_02A" }, // empty
    { 0x02B, "_func_02B" }, // empty
    { 0x02C, "updategamerprofile" },
    { 0x02D, "assertex" },
    { 0x02E, "assertmsg" },
    { 0x02F, "isdefined" },
    { 0x030, "isvalidmissile" },
    { 0x031, "isstring" },
    { 0x032, "setomnvar" },
    { 0x033, "getomnvar" },
    { 0x034, "setdvar" },
    { 0x035, "setdynamicdvar" },
    { 0x036, "setdvarifuninitialized" },
    { 0x037, "setdevdvar" },
    { 0x038, "setdevdvarifuninitialized" },
    { 0x039, "getdvar" },
    { 0x03A, "getdvarint" },
    { 0x03B, "getdvarfloat" },
    { 0x03C, "getdvarvector" },
    { 0x03D, "gettime" },
    { 0x03E, "gettimeutc" },
    { 0x03F, "_func_03F" }, // SP 0x14024B9C0, MP 0x1403156A0
    { 0x040, "getentbynum" },
    { 0x041, "getweaponmodel" },
    { 0x042, "getculldist" },
    { 0x043, "sethalfresparticles" },
    { 0x044, "getmapsunlight" },
    { 0x045, "setsunlight" },
    { 0x046, "resetsunlight" },
    { 0x047, "getmapsundirection" },
    { 0x048, "getmapsunangles" },
    { 0x049, "setsundirection" },
    { 0x04A, "lerpsundirection" },
    { 0x04B, "lerpsunangles" },
    { 0x04C, "resetsundirection" },
    { 0x04D, "enableforcedsunshadows" },
    { 0x04E, "enableforcednosunshadows" },
    { 0x04F, "disableforcedsunshadows" },
    { 0x050, "enableouterspacemodellighting" },
    { 0x051, "disableouterspacemodellighting" },
    { 0x052, "remapstage" },
    { 0x053, "_func_053" }, // SP 0x14025F6B0
    { 0x054, "_func_054" }, // SP 0x14025F800
    { 0x055, "_func_055" }, // SP 0x14025F830
    { 0x056, "_func_056" }, // SP 0x14025F850
    { 0x057, "_func_057" }, // SP 0x14025F920
    { 0x058, "_func_058" }, // SP 0x14025FA20
    { 0x059, "_func_059" }, // SP 0x14025FB80
    { 0x05A, "_func_05A" }, // SP 0x14025FC00
    { 0x05B, "_func_05B" }, // SP 0x14025FC80
    { 0x05C, "_func_05C" }, // SP 0x14025FE00
    { 0x05D, "getweapondisplayname" },
    { 0x05E, "getweaponbasename" },
    { 0x05F, "getweaponattachments" },
    { 0x060, "getweaponattachmentdisplaynames" },
    { 0x061, "getweaponcamoname" },
    { 0x062, "getweaponreticlename" },
    { 0x063, "getanimlength" },
    { 0x064, "animhasnotetrack" },
    { 0x065, "getnotetracktimes" },
    { 0x066, "spawn" },
    { 0x067, "spawnloopsound" },
    { 0x068, "spawnloopingsound" },
    { 0x069, "bullettrace" },
    { 0x06A, "target_setmaxsize" },
    { 0x06B, "target_setcolor" },
    { 0x06C, "target_setdelay" },
    { 0x06D, "getstartorigin" },
    { 0x06E, "getstartangles" },
    { 0x06F, "_func_06F" }, // SP 0x14020DCB0
    { 0x070, "_func_070" }, // SP 0x14025FCB0
    { 0x071, "_func_071" }, // SP 0x140243B90, MP 0x1403104D0
    { 0x072, "_func_072" }, // SP 0x14025BCC0
    { 0x073, "_func_073" }, // SP 0x14025BD60
    { 0x074, "_func_074" }, // SP 0x14025BFA0
    { 0x075, "_func_075" }, // SP 0x14025C150
    { 0x076, "_func_076" }, // SP 0x140246C90, MP 0x140311AD0
    { 0x077, "_func_077" }, // SP 0x140246D70, MP 0x140311D80
    { 0x078, "_func_078" }, // SP 0x140246DA0, MP 0x140311D90
    { 0x079, "_func_079" }, // SP 0x140246F10, MP 0x140311DF0
    { 0x07A, "_func_07A" }, // SP 0x140247010, MP 0x140311EF0
    { 0x07B, "_func_07B" }, // SP 0x140247060, MP 0x140311F50
    { 0x07C, "_func_07C" }, // SP 0x14025C320
    { 0x07D, "_func_07D" }, // SP 0x14025D3E0
    { 0x07E, "_func_07E" }, // SP 0x14025C220
    { 0x07F, "_func_07F" }, // SP 0x14025F620
    { 0x080, "_func_080" }, // SP 0x140241480, MP 0x14031FB60
    { 0x081, "_func_081" }, // SP 0x14025F640
    { 0x082, "_func_082" }, // SP 0x14025F690
    { 0x083, "_func_083" }, // SP 0x14025D480
    { 0x084, "_func_084" }, // SP 0x14025E160
    { 0x085, "_func_085" }, // SP 0x14025E180
    { 0x086, "_func_086" }, // SP 0x14025D8D0
    { 0x087, "_func_087" }, // SP 0x14025E1A0
    { 0x088, "_func_088" }, // SP 0x14025E270
    { 0x089, "_func_089" }, // SP 0x14025FE70
    { 0x08A, "_func_08A" }, // SP 0x140260370
    { 0x08B, "bullettracepassed" },
    { 0x08C, "sighttracepassed" },
    { 0x08D, "physicstrace" },
    { 0x08E, "playerphysicstrace" },
    { 0x08F, "getgroundposition" },
    { 0x090, "getmovedelta" },
    { 0x091, "getangledelta" },
    { 0x092, "getnorthyaw" },
    { 0x093, "_func_093" }, // SP 0x14025C1F0
    { 0x094, "_func_094" }, // SP 0x14025C2F0
    { 0x095, "_func_095" }, // SP 0x14025E330
    { 0x096, "_func_096" }, // SP 0x14025E380
    { 0x097, "_func_097" }, // SP 0x14025E2F0
    { 0x098, "_func_098" }, // SP 0x14026C770
    { 0x099, "_func_099" }, // SP 0x14026CB40
    { 0x09A, "_func_09A" }, // SP 0x14026CE30
    { 0x09B, "_func_09B" }, // SP 0x14026CDF0
    { 0x09C, "_func_09C" }, // SP 0x14026D9F0
    { 0x09D, "_func_09D" }, // SP 0x14026D670
    { 0x09E, "_func_09E" }, // SP 0x14026CCC0
    { 0x09F, "_func_09F" }, // SP 0x14026CC50
    { 0x0A0, "_func_0A0" }, // SP 0x14026DB20
    { 0x0A1, "_func_0A1" }, // SP 0x14026C790
    { 0x0A2, "_func_0A2" }, // SP 0x14026CBD0
    { 0x0A3, "_func_0A3" }, // SP 0x14026CD60
    { 0x0A4, "_func_0A4" }, // SP 0x14026CE50
    { 0x0A5, "_func_0A5" }, // SP 0x14026D2E0
    { 0x0A6, "_func_0A6" }, // SP 0x14026CC40
    { 0x0A7, "_func_0A7" }, // SP 0x14026DB10
    { 0x0A8, "_func_0A8" }, // SP 0x14026D8C0
    { 0x0A9, "_func_0A9" }, // SP 0x14026C7C0
    { 0x0AA, "_func_0AA" }, // SP 0x14026C9F0
    { 0x0AB, "_func_0AB" }, // SP 0x14026C8F0
    { 0x0AC, "_func_0AC" }, // SP 0x14026D520
    { 0x0AD, "setnorthyaw" },
    { 0x0AE, "setslowmotion" },
    { 0x0AF, "randomint" },
    { 0x0B0, "randomfloat" },
    { 0x0B1, "randomintrange" },
    { 0x0B2, "randomfloatrange" },
    { 0x0B3, "sin" },
    { 0x0B4, "cos" },
    { 0x0B5, "tan" },
    { 0x0B6, "asin" },
    { 0x0B7, "acos" },
    { 0x0B8, "atan" },
    { 0x0B9, "int" },
    { 0x0BA, "float" },
    { 0x0BB, "abs" },
    { 0x0BC, "min" }, // check!
    { 0x0BD, "objective_additionalcurrent" },
    { 0x0BE, "objective_ring" },
    { 0x0BF, "objective_setpointertextoverride" },
    { 0x0C0, "getnode" },
    { 0x0C1, "getnodearray" },
    { 0x0C2, "getallnodes" },
    { 0x0C3, "getnodesinradius" },
    { 0x0C4, "getnodesinradiussorted" },
    { 0x0C5, "getclosestnodeinsight" },
    { 0x0C6, "getreflectionlocs" },
    { 0x0C7, "getreflectionreferencelocs" },
    { 0x0C8, "getvehicletracksegment" },
    { 0x0C9, "getvehicletracksegmentarray" },
    { 0x0CA, "getallvehicletracksegments" },
    { 0x0CB, "isarray" },
    { 0x0CC, "isai" },
    { 0x0CD, "getindexforluincstring" },
    { 0x0CE, "issentient" },
    { 0x0CF, "_func_0CF" }, // SP 0x140259F30
    { 0x0D0, "_func_0D0" }, // SP 0x14025A0E0
    { 0x0D1, "_func_0D1" }, // SP 0x14025A170
    { 0x0D2, "_func_0D2" }, // SP 0x14025A1F0
    { 0x0D3, "_func_0D3" }, // SP 0x14025A220
    { 0x0D4, "_func_0D4" }, // SP 0x14025A620
    { 0x0D5, "_func_0D5" }, // SP 0x14025B700
    { 0x0D6, "_func_0D6" }, // SP 0x14025B8F0
    { 0x0D7, "_func_0D7" }, // SP 0x14025BA10
    { 0x0D8, "_func_0D8" }, // SP 0x14025BC40
    { 0x0D9, "_func_0D9" }, // SP 0x14025BB90
    { 0x0DA, "_func_0DA" }, // SP 0x14025BE80
    { 0x0DB, "_func_0DB" }, // SP 0x14025BF20
    { 0x0DC, "_func_0DC" }, // empty
    { 0x0DD, "_func_0DD" }, // SP 0x14025C0E0
    { 0x0DE, "max" }, // check!
    { 0x0DF, "floor" },
    { 0x0E0, "ceil" },
    { 0x0E1, "exp" },
    { 0x0E2, "log" },
    { 0x0E3, "sqrt" },
    { 0x0E4, "squared" },
    { 0x0E5, "clamp" },
    { 0x0E6, "angleclamp" },
    { 0x0E7, "angleclamp180" },
    { 0x0E8, "vectorfromlinetopoint" },
    { 0x0E9, "pointonsegmentnearesttopoint" },
    { 0x0EA, "distance" },
    { 0x0EB, "distance2d" },
    { 0x0EC, "distancesquared" },
    { 0x0ED, "length" },
    { 0x0EE, "length2d" },
    { 0x0EF, "lengthsquared" },
    { 0x0F0, "length2dsquared" },
    { 0x0F1, "closer" },
    { 0x0F2, "vectordot" },
    { 0x0F3, "vectorcross" },
    { 0x0F4, "axistoangles" },
    { 0x0F5, "visionsetthermal" },
    { 0x0F6, "visionsetpain" },
    { 0x0F7, "endlobby" },
    { 0x0F8, "setac130ambience" },
    { 0x0F9, "getmapcustom" },
    { 0x0FA, "spawnsighttrace" },
    { 0x0FB, "incrementcounter" },
    { 0x0FC, "getcountertotal" },
    { 0x0FD, "getlevelticks" },
    { 0x0FE, "perlinnoise2d" },
    { 0x0FF, "calcrockingangles" },
    { 0x100, "reconevent" },
    { 0x101, "reconspatialevent" },
    { 0x102, "setsunflareposition" },
    { 0x103, "createthreatbiasgroup" },
    { 0x104, "threatbiasgroupexists" },
    { 0x105, "getthreatbias" },
    { 0x106, "setthreatbias" },
    { 0x107, "setthreatbiasagainstall" },
    { 0x108, "setignoremegroup" },
    { 0x109, "isenemyteam" },
    { 0x10A, "objective_additionalentity" },
    { 0x10B, "objective_state_nomessage" },
    { 0x10C, "objective_string" },
    { 0x10D, "objective_string_nomessage" },
    { 0x10E, "objective_additionalposition" },
    { 0x10F, "objective_current_nomessage" },
    { 0x110, "vectornormalize" },
    { 0x111, "vectortoangles" },
    { 0x112, "vectortoyaw" },
    { 0x113, "vectorlerp" },
    { 0x114, "anglestoup" },
    { 0x115, "anglestoright" },
    { 0x116, "anglestoforward" },
    { 0x117, "anglesdelta" },
    { 0x118, "combineangles" },
    { 0x119, "transformmove" },
    { 0x11A, "rotatevector" },
    { 0x11B, "rotatepointaroundvector" },
    { 0x11C, "issubstr" },
    { 0x11D, "isendstr" },
    { 0x11E, "getsubstr" },
    { 0x11F, "tolower" },
    { 0x120, "strtok" },
    { 0x121, "stricmp" },
    { 0x122, "ambientplay" },
    { 0x123, "getuavstrengthmax" },
    { 0x124, "getuavstrengthlevelneutral" },
    { 0x125, "getuavstrengthlevelshowenemyfastsweep" },
    { 0x126, "getuavstrengthlevelshowenemydirectional" },
    { 0x127, "blockteamradar" },
    { 0x128, "unblockteamradar" },
    { 0x129, "isteamradarblocked" },
    { 0x12A, "getassignedteam" },
    { 0x12B, "setmatchdata" },
    { 0x12C, "getmatchdata" },
    { 0x12D, "sendmatchdata" },
    { 0x12E, "clearmatchdata" },
    { 0x12F, "setmatchdatadef" },
    { 0x130, "setmatchclientip" },
    { 0x131, "setmatchdataid" },
    { 0x132, "setclientmatchdata" },
    { 0x133, "getclientmatchdata" },
    { 0x134, "setclientmatchdatadef" },
    { 0x135, "sendclientmatchdata" },
    { 0x136, "getbuildversion" },
    { 0x137, "getbuildnumber" },
    { 0x138, "getsystemtime" },
    { 0x139, "getmatchrulesdata" },
    { 0x13A, "isusingmatchrulesdata" },
    { 0x13B, "kick" },
    { 0x13C, "issplitscreen" },
    { 0x13D, "setmapcenter" },
    { 0x13E, "setgameendtime" },
    { 0x13F, "visionsetnaked" },
    { 0x140, "visionsetnight" },
    { 0x141, "visionsetmissilecam" },
    { 0x142, "ambientstop" },
    { 0x143, "precachemodel" },
    { 0x144, "precacheshellshock" },
    { 0x145, "precacheitem" },
    { 0x146, "precacheshader" },
    { 0x147, "precachestring" },
    { 0x148, "precachemenu" },
    { 0x149, "precacherumble" },
    { 0x14A, "precachelocationselector" },
    { 0x14B, "precacheleaderboards" },
    { 0x14C, "loadfx" },
    { 0x14D, "playfx" },
    { 0x14E, "playfxontag" },
    { 0x14F, "stopfxontag" },
    { 0x150, "killfxontag" },
    { 0x151, "playloopedfx" },
    { 0x152, "spawnfx" },
    { 0x153, "triggerfx" },
    { 0x154, "playfxontagforclients" },
    { 0x155, "setwinningteam" },
    { 0x156, "announcement" },
    { 0x157, "clientannouncement" },
    { 0x158, "setteammode" },
    { 0x159, "getteamscore" },
    { 0x15A, "setteamscore" },
    { 0x15B, "setclientnamemode" },
    { 0x15C, "updateclientnames" },
    { 0x15D, "getteamplayersalive" },
    { 0x15E, "logprint" },
    { 0x15F, "worldentnumber" },
    { 0x160, "obituary" },
    { 0x161, "positionwouldtelefrag" },
    { 0x162, "canspawn" },
    { 0x163, "getstarttime" },
    { 0x164, "precachestatusicon" },
    { 0x165, "precacheheadicon" },
    { 0x166, "precacheminimapicon" },
    { 0x167, "precachempanim" },
    { 0x168, "map_restart" },
    { 0x169, "_func_169" }, // MP 0x14032E320
    { 0x16A, "exitlevel" },
    { 0x16B, "_func_16B" }, // MP 0x14032E4E0
    { 0x16C, "_func_16C" }, // MP 0x14032EA90
    { 0x16D, "_func_16D" }, // MP 0x140328560
    { 0x16E, "_func_16E" }, // MP 0x14032EB80
    { 0x16F, "_func_16F" }, // MP 0x14032EEF0
    { 0x170, "_func_170" }, // MP 0x14032EBC0
    { 0x171, "_func_171" }, // MP 0x14032EC00
    { 0x172, "_func_172" }, // MP 0x140328580
    { 0x173, "_func_173" }, // MP 0x140328590
    { 0x174, "_func_174" }, // MP 0x140328700
    { 0x175, "_func_175" }, // MP 0x14032CBB0
    { 0x176, "_func_176" }, // MP 0x14032CC20
    { 0x177, "_func_177" }, // MP 0x14032CCE0
    { 0x178, "_func_178" }, // MP 0x14032CDC0
    { 0x179, "_func_179" }, // MP 0x14032CE20
    { 0x17A, "physicsexplosionsphere" },
    { 0x17B, "physicsexplosioncylinder" },
    { 0x17C, "physicsjolt" },
    { 0x17D, "physicsjitter" },
    { 0x17E, "setexpfog" },
    { 0x17F, "setexpfogext" },
    { 0x180, "setexpfogdvarsonly" },
    { 0x181, "setexpfogextdvarsonly" },
    { 0x182, "setatmosfog" },
    { 0x183, "setatmosfogdvarsonly" },
    { 0x184, "isexplosivedamagemod" },
    { 0x185, "radiusdamage" },
    { 0x186, "setplayerignoreradiusdamage" },
    { 0x187, "glassradiusdamage" },
    { 0x188, "earthquake" },
    { 0x189, "getnumparts" },
    { 0x18A, "objective_onentity" },
    { 0x18B, "objective_onentitywithrotation" },
    { 0x18C, "objective_team" },
    { 0x18D, "objective_player" },
    { 0x18E, "objective_playerteam" },
    { 0x18F, "objective_playerenemyteam" },
    { 0x190, "objective_playermask_hidefromall" },
    { 0x191, "objective_playermask_hidefrom" },
    { 0x192, "objective_playermask_showtoall" },
    { 0x193, "objective_playermask_showto" },
    { 0x194, "iprintln" },
    { 0x195, "iprintlnbold" },
    { 0x196, "logstring" },
    { 0x197, "getent" },
    { 0x198, "getentarray" },
    { 0x199, "getspawnarray" },
    { 0x19A, "spawnplane" },
    { 0x19B, "spawnstruct" },
    { 0x19C, "spawnhelicopter" },
    { 0x19D, "isalive" },
    { 0x19E, "isspawner" },
    { 0x19F, "missile_createattractorent" },
    { 0x1A0, "missile_createattractororigin" },
    { 0x1A1, "missile_createrepulsorent" },
    { 0x1A2, "missile_createrepulsororigin" },
    { 0x1A3, "missile_deleteattractor" },
    { 0x1A4, "playsoundatpos" },
    { 0x1A5, "newhudelem" },
    { 0x1A6, "newclienthudelem" },
    { 0x1A7, "newteamhudelem" },
    { 0x1A8, "resettimeout" },
    { 0x1A9, "isplayer" },
    { 0x1AA, "isplayernumber" },
    { 0x1AB, "getpartname" },
    { 0x1AC, "weaponfiretime" },
    { 0x1AD, "weaponclipsize" },
    { 0x1AE, "weaponisauto" },
    { 0x1AF, "weaponissemiauto" },
    { 0x1B0, "weaponisboltaction" },
    { 0x1B1, "weaponinheritsperks" },
    { 0x1B2, "weaponburstcount" },
    { 0x1B3, "weapontype" },
    { 0x1B4, "weaponclass" },
    { 0x1B5, "getnextarraykey" },
    { 0x1B6, "sortbydistance" },
    { 0x1B7, "tablelookup" },
    { 0x1B8, "tablelookupbyrow" },
    { 0x1B9, "tablelookupistring" },
    { 0x1BA, "tablelookupistringbyrow" },
    { 0x1BB, "tablelookuprownum" },
    { 0x1BC, "tableexists" },
    { 0x1BD, "getmissileowner" },
    { 0x1BE, "magicbullet" },
    { 0x1BF, "getweaponflashtagname" },
    { 0x1C0, "averagepoint" },
    { 0x1C1, "averagenormal" },
    { 0x1C2, "vehicle_getspawnerarray" },
    { 0x1C3, "playrumbleonposition" },
    { 0x1C4, "playrumblelooponposition" },
    { 0x1C5, "stopallrumbles" },
    { 0x1C6, "soundexists" },
    { 0x1C7, "openfile" },
    { 0x1C8, "closefile" },
    { 0x1C9, "fprintln" },
    { 0x1CA, "fprintfields" },
    { 0x1CB, "freadln" },
    { 0x1CC, "fgetarg" },
    { 0x1CD, "setminimap" },
    { 0x1CE, "setthermalbodymaterial" },
    { 0x1CF, "getarraykeys" },
    { 0x1D0, "getfirstarraykey" },
    { 0x1D1, "getglass" },
    { 0x1D2, "getglassarray" },
    { 0x1D3, "getglassorigin" },
    { 0x1D4, "isglassdestroyed" },
    { 0x1D5, "destroyglass" },
    { 0x1D6, "deleteglass" },
    { 0x1D7, "getentchannelscount" },
    { 0x1D8, "getentchannelname" },
    { 0x1D9, "objective_add" },
    { 0x1DA, "objective_delete" },
    { 0x1DB, "objective_state" },
    { 0x1DC, "objective_icon" },
    { 0x1DD, "objective_position" },
    { 0x1DE, "objective_current" },
    { 0x1DF, "_func_1DF" }, // SP 0x140245580, MP 0x14030C5F0 // weap
    { 0x1E0, "_func_1E0" }, // SP 0x140245870, MP 0x14030C960
    { 0x1E1, "_func_1E1" }, // SP 0x140245A90, MP 0x14030CAD0
    { 0x1E2, "_func_1E2" }, // SP 0x140245D00, MP 0x14030D110
    { 0x1E3, "_func_1E3" }, // SP 0x140246230, MP 0x14030D980
    { 0x1E4, "_func_1E4" }, // SP 0x1402464C0, MP 0x14030DFC0
    { 0x1E5, "_func_1E5" }, // SP 0x1402468A0, MP 0x14030E400
    { 0x1E6, "_func_1E6" }, // SP 0x140246E40, MP 0x14030E970
    { 0x1E7, "getvehiclenode" },
    { 0x1E8, "getvehiclenodearray" },
    { 0x1E9, "getallvehiclenodes" },
    { 0x1EA, "getnumvehicles" },
    { 0x1EB, "precachevehicle" },
    { 0x1EC, "spawnvehicle" },
    { 0x1ED, "vehicle_getarray" },
    { 0x1EE, "pow" },
    { 0x1EF, "angleclamp360" },
    { 0x1F0, "botgetmemoryevents" },
    { 0x1F1, "botautoconnectenabled" },
    { 0x1F2, "botzonegetcount" },
    { 0x1F3, "botzonesetteam" },
    { 0x1F4, "botzonenearestcount" },
    { 0x1F5, "botmemoryflags" },
    { 0x1F6, "botflagmemoryevents" },
    { 0x1F7, "botzonegetindoorpercent" },
    { 0x1F8, "botsentientswap" },
    { 0x1F9, "isbot" },
    { 0x1FA, "isagent" },
    { 0x1FB, "_func_1FB" }, // MP 0x140406E40
    { 0x1FC, "_func_1FC" }, // MP 0x140432CD0
    { 0x1FD, "_func_1FD" }, // MP 0x140432EE0
    { 0x1FE, "_func_1FE" }, // MP 0x1402D2430
    { 0x1FF, "_func_1FF" }, // SP 0x14027E8E0, MP 0x1402D3710
    { 0x200, "_func_200" }, // SP 0x14027E550, MP 0x1402D2530
    { 0x201, "_func_201" }, // MP 0x1402D28C0
    { 0x202, "_func_202" }, // MP 0x1402D28D0
    { 0x203, "_func_203" }, // MP 0x1402D2A40
    { 0x204, "_func_204" }, // MP 0x1402D30E0
    { 0x205, "_func_205" }, // MP 0x1402D3060
    { 0x206, "_func_206" }, // MP 0x1402D2370
    { 0x207, "_func_207" }, // MP 0x1402D2D20
    { 0x208, "_func_208" }, // MP 0x1402D29D0
    { 0x209, "_func_209" }, // SP 0x14025C070, MP 0x14032AF60
    { 0x20A, "_func_20A" }, // empty
    { 0x20B, "_func_20B" }, // empty
    { 0x20C, "_func_20C" }, // MP 0x1402D3310
    { 0x20D, "_func_20D" }, // MP 0x1402D1E20
    { 0x20E, "badplace_global" },
    { 0x20F, "getpathdist" },
    { 0x210, "getlinkednodes" },
    { 0x211, "disconnectnodepair" },
    { 0x212, "connectnodepair" },
    { 0x213, "_func_213" }, // SP 0x140259F80
    { 0x214, "_func_214" }, // empty
    { 0x215, "_func_215" }, // empty
    { 0x216, "_func_216" }, // MP 0x140330030
    { 0x217, "_func_217" }, // MP 0x14032E430
    { 0x218, "_func_218" }, // SP 0x140321E90
    { 0x219, "_func_219" }, // SP 0x1403220D0
    { 0x21A, "_func_21A" }, // SP 0x140322010
    { 0x21B, "_func_21B" }, // SP 0x140321FB0
    { 0x21C, "_func_21C" }, // SP 0x140321B90
    { 0x21D, "_func_21D" }, // SP 0x140321C10
    { 0x21E, "_func_21E" }, // SP 0x140321BC0
    { 0x21F, "_func_21F" }, // SP 0x140321C50
    { 0x220, "_func_220" }, // SP 0x1402509E0, MP 0x1403176D0
    { 0x221, "_func_221" }, // SP 0x14024FD80, MP 0x1403175D0
    { 0x222, "_func_222" }, // SP 0x140253430, MP 0x14031FB30
    { 0x223, "_func_223" }, // SP 0x1402538E0, MP 0x140320C40
    { 0x224, "_func_224" }, // SP 0x140253AE0, MP 0x140320E00
    { 0x225, "_func_225" }, // SP 0x140254010, MP 0x1403210C0
    { 0x226, "_func_226" }, // SP 0x140254670, MP 0x140321250
    { 0x227, "_func_227" }, // SP 0x14023DF60, MP 0x140321520
    { 0x228, "_func_228" }, // SP 0x14023E450, MP 0x1403217F0
    { 0x229, "_func_229" }, // MP 0x14030FA10
    { 0x22A, "_func_22A" }, // SP 0x140250490, MP 0x1403172F0
    { 0x22B, "_func_22B" }, // SP 0x14025FDE0
    { 0x22C, "_func_22C" }, // SP 0x14025FDC0
    { 0x22D, "_func_22D" }, // SP 0x14025FDA0
    { 0x22E, "_func_22E" }, // empty
    { 0x22F, "_func_22F" }, // MP 0x14030B9E0
    { 0x230, "_func_230" }, // empty
    { 0x231, "_func_231" }, // SP 0x1402403A0, MP 0x14030BB90
    { 0x232, "_func_232" }, // SP 0x140240810, MP 0x140320F60
    { 0x233, "_func_233" }, // SP 0x14025CF00, MP 0x14032BE10
    { 0x234, "_func_234" }, // SP 0x14025EA90
    { 0x235, "_func_235" }, // SP 0x14024CB60, MP 0x140321C30
    { 0x236, "_func_236" }, // MP 0x140321C40
    { 0x237, "_func_237" }, // empty
    { 0x238, "_func_238" }, // SP 0x14024A020, MP 0x140311A40
    { 0x239, "_func_239" }, // SP 0x140247090, MP 0x14030EC50
    { 0x23A, "_func_23A" }, // SP 0x140247300, MP 0x14030F050
    { 0x23B, "_func_23B" }, // SP 0x1402474E0, MP 0x14030F340
    { 0x23C, "_func_23C" }, // SP 0x1402477E0, MP 0x14030F550
    { 0x23D, "_func_23D" }, // SP 0x140247A40, MP 0x14030F710
    { 0x23E, "_func_23E" }, // MP 0x1403295E0
    { 0x23F, "_func_23F" }, // SP 0x14023FCB0, MP 0x140322690
    { 0x240, "_func_240" }, // MP 0x140329600
    { 0x241, "_func_241" }, // MP 0x140329950
    { 0x242, "_func_242" }, // MP 0x1403299C0
    { 0x243, "_func_243" }, // MP 0x1403299D0
    { 0x244, "_func_244" }, // SP 0x14025D7C0
    { 0x245, "_func_245" }, // SP 0x140253C30, MP 0x14031A690
    { 0x246, "_func_246" }, // SP 0x14024F1E0, MP 0x1403163C0
    { 0x247, "_func_247" }, // SP 0x140252280, MP 0x140319020
    { 0x248, "_func_248" }, // SP 0x140260360
    { 0x249, "_func_249" }, // MP 0x14030B680
    { 0x24A, "_func_24A" }, // MP 0x14030B870
    { 0x24B, "_func_24B" }, // MP 0x14030B9D0
    { 0x24C, "_func_24C" }, // SP 0x1402531C0, MP 0x140319F60
    { 0x24D, "_func_24D" }, // SP 0x140253500, MP 0x140319FC0
    { 0x24E, "_func_24E" }, // SP 0x1402539F0, MP 0x14031A250
    { 0x24F, "_func_24F" }, // MP 0x140338900
    { 0x250, "_func_250" }, // SP 0x140259FA0
    { 0x251, "_func_251" }, // SP 0x140249700, MP 0x140310B20
    { 0x252, "_func_252" }, // SP 0x140240DE0, MP 0x14030CBF0
    { 0x253, "_func_253" }, // SP 0x140240E00, MP 0x14030CE90
    { 0x254, "_func_254" }, // SP 0x140241180, MP 0x14030D000
    { 0x255, "_func_255" }, // SP 0x140241330, MP 0x14030D2A0
    { 0x256, "_func_256" }, // SP 0x140241560, MP 0x14030D650
    { 0x257, "_func_257" }, // SP 0x140241970, MP 0x14030D8E0
    { 0x258, "_func_258" }, // SP 0x140241A70, MP 0x14030E070
    { 0x259, "_func_259" }, // SP 0x140241E30, MP 0x14030E4C0
    { 0x25A, "_func_25A" }, // SP 0x140241F40, MP 0x14030E7B0
    { 0x25B, "_func_25B" }, // SP 0x140242270, MP 0x14030EAC0
    { 0x25C, "_func_25C" }, // SP 0x1402425F0, MP 0x14030EED0
    { 0x25D, "_func_25D" }, // SP 0x140242960, MP 0x14030F280
    { 0x25E, "_func_25E" }, // SP 0x140242C80, MP 0x14030F640
    { 0x25F, "_func_25F" }, // SP 0x1402430E0, MP 0x14030F990
    { 0x260, "_func_260" }, // MP 0x14030FA20
    { 0x261, "_func_261" }, // MP 0x14032BC00
    { 0x262, "_func_262" }, // MP 0x14030FD60
    { 0x263, "_func_263" }, // MP 0x14030FDB0
    { 0x264, "_func_264" }, // MP 0x14030FF50
    { 0x265, "_func_265" }, // MP 0x140310030
    { 0x266, "_func_266" }, // MP 0x140310040
    { 0x267, "_func_267" }, // MP 0x1403101C0
    { 0x268, "_func_268" }, // MP 0x140328750
    { 0x269, "_func_269" }, // empty
    { 0x26A, "_func_26A" }, // empty
    { 0x26B, "_func_26B" }, // MP 0x140310250
    { 0x26C, "_func_26C" }, // MP 0x140310260
    { 0x26D, "_func_26D" }, // MP 0x140310360
    { 0x26E, "_func_26E" }, // MP 0x140310480
    { 0x26F, "_func_26F" }, // MP 0x14032C3B0
    { 0x270, "_func_270" }, // empty
    { 0x271, "_func_271" }, // MP 0x140433260
    { 0x272, "_func_272" }, // MP 0x1403328E0
    { 0x273, "_func_273" }, // MP 0x140433220
    { 0x274, "_func_274" }, // MP 0x14030F630
    { 0x275, "_func_275" }, // MP 0x1402F05B0
    { 0x276, "_func_276" }, // MP 0x14030C470
    { 0x277, "_func_277" }, // MP 0x14030C480
    { 0x278, "_func_278" }, // MP 0x14030BA90
    { 0x279, "_func_279" }, // SP 0x1402476E0, MP 0x140310920
    { 0x27A, "_func_27A" }, // MP 0x14032C4A0
    { 0x27B, "_func_27B" }, // MP 0x14032C4B0
    { 0x27C, "_func_27C" }, // MP 0x14032C4D0
    { 0x27D, "_func_27D" }, // MP 0x14032C840
    { 0x27E, "_func_27E" }, // MP 0x14032CAB0
    { 0x27F, "_func_27F" }, // MP 0x14030BB00
    { 0x280, "_func_280" }, // MP 0x14032F7E0
    { 0x281, "_func_281" }, // MP 0x14032E600
    { 0x282, "_func_282" }, // MP 0x140310EC0
    { 0x283, "_func_283" }, // SP 0x14023EC00, MP 0x14031BAE0
    { 0x284, "_func_284" }, // SP 0x14023F300, MP 0x14031C2B0
    { 0x285, "_func_285" }, // MP 0x140043610
    { 0x286, "istestclient" },
    { 0x287, "_func_287" }, // MP 0x1402D2850
    { 0x288, "_func_288" }, // MP 0x14032F0C0
    { 0x289, "_func_289" }, // SP 0x1402471A0, MP 0x140311FF0
    { 0x28A, "_func_28A" }, // SP 0x1402471E0, MP 0x140312040
    { 0x28B, "_func_28B" }, // SP 0x140259CC0
    { 0x28C, "_func_28C" }, // SP 0x140244780, MP 0x140311100
    { 0x28D, "_func_28D" }, // SP 0x140247F80, MP 0x140314C70
    { 0x28E, "_func_28E" }, // SP 0x140244530, MP 0x14030D340
    { 0x28F, "_func_28F" }, // SP 0x1402453C0, MP 0x14030DA60
    { 0x290, "_func_290" }, // SP 0x140245780, MP 0x14030E5C0
    { 0x291, "_func_291" }, // SP 0x1402601E0
    { 0x292, "_func_292" }, // MP 0x14031FDA0
    { 0x293, "_func_293" }, // SP 0x1402503F0, MP 0x140317140
    { 0x294, "_func_294" }, // SP 0x140246AD0, MP 0x14030FD70
    { 0x295, "_func_295" }, // SP 0x140246F20, MP 0x140310210
    { 0x296, "_func_296" }, // SP 0x140247200, MP 0x140310370
    { 0x297, "_func_297" }, // MP 0x14032FBA0
    { 0x298, "_func_298" }, // MP 0x14032FCA0
    { 0x299, "_func_299" }, // SP 0x140246B10, MP 0x14030E700
    { 0x29A, "_func_29A" }, // SP 0x1402603C0
    { 0x29B, "_func_29B" }, // SP 0x14024CE40, MP 0x140316070
    { 0x29C, "_func_29C" }, // MP 0x14031FC20
    { 0x29D, "_func_29D" }, // SP 0x14024A520, MP 0x140318030
    { 0x29E, "_func_29E" }, // MP 0x140318A90
    { 0x29F, "_func_29F" }, // MP 0x140318560
    { 0x2A0, "_func_2A0" }, // MP 0x140328F10
    { 0x2A1, "_func_2A1" }, // SP 0x14025A630
    { 0x2A2, "_func_2A2" }, // SP 0x140243B50, MP 0x14030CA90
    { 0x2A3, "_func_2A3" }, // SP 0x14024B760, MP 0x1403199C0
    { 0x2A4, "_func_2A4" }, // SP 0x14024AB20, MP 0x140319680
    { 0x2A5, "_func_2A5" }, // SP 0x14024B670, MP 0x1403199A0
    { 0x2A6, "_func_2A6" }, // SP 0x14024B710, MP 0x1403199B0
    { 0x2A7, "_func_2A7" }, // SP 0x14024B850, MP 0x140319A20
    { 0x2A8, "_func_2A8" }, // MP 0x14032D2A0
    { 0x2A9, "_func_2A9" }, // MP 0x14032D300
    { 0x2AA, "_func_2AA" }, // MP 0x14032D340
    { 0x2AB, "_func_2AB" }, // MP 0x14032D780
    { 0x2AC, "_func_2AC" }, // MP 0x14031CA40
    { 0x2AD, "_func_2AD" }, // MP 0x14031E1F0
    { 0x2AE, "_func_2AE" }, // SP 0x14023E7F0, MP 0x140321880
    { 0x2AF, "_func_2AF" }, // SP 0x14025CCA0
    { 0x2B0, "_func_2B0" }, // MP 0x140329610
    { 0x2B1, "_func_2B1" }, // MP 0x1403297B0
    { 0x2B2, "_func_2B2" }, // MP 0x1403298D0
    { 0x2B3, "_func_2B3" }, // MP 0x14032ACF0
    { 0x2B4, "_func_2B4" }, // SP 0x14024EAD0, MP 0x140317DF0
    { 0x2B5, "_func_2B5" }, // SP 0x14025CCF0
    { 0x2B6, "_func_2B6" }, // SP 0x140245730, MP 0x14030E570
    { 0x2B7, "_func_2B7" }, // MP 0x140337920
    { 0x2B8, "_func_2B8" }, // SP 0x14024BB40, MP 0x140319B40
    { 0x2B9, "_func_2B9" }, // SP 0x14024BC90, MP 0x140319B50
    { 0x2BA, "_func_2BA" }, // SP 0x14023ED90, MP 0x140321AE0
    { 0x2BB, "_func_2BB" }, // SP 0x14024B7C0, MP 0x140314A40
    { 0x2BC, "_func_2BC" }, // MP 0x140314C30
    { 0x2BD, "_func_2BD" }, // SP 0x14025CF50
    { 0x2BE, "_func_2BE" }, // MP 0x14032AEA0
    { 0x2BF, "_func_2BF" }, // MP 0x1402D3540
    { 0x2C0, "_func_2C0" }, // MP 0x1402D35B0
    { 0x2C1, "_func_2C1" }, // MP 0x140332A70
    { 0x2C2, "_func_2C2" }, // MP 0x140332AE0
    { 0x2C3, "_func_2C3" }, // MP 0x14032C580
    { 0x2C4, "_func_2C4" }, // MP 0x14032C650
    { 0x2C5, "_func_2C5" }, // MP 0x14032C820
    { 0x2C6, "_func_2C6" }, // SP 0x14025C2C0
    { 0x2C7, "_func_2C7" }, // MP 0x14032C2A0
    { 0x2C8, "_func_2C8" }, // MP 0x1402D34D0
    { 0x2C9, "_func_2C9" }, // MP 0x1402D33F0
    { 0x2CA, "_func_2CA" }, // MP 0x14032DAD0
    { 0x2CB, "_func_2CB" }, // MP 0x14032DC40
    { 0x2CC, "_func_2CC" }, // SP 0x14025C4B0
    { 0x2CD, "_func_2CD" }, // SP 0x14024A6B0, MP 0x140318270
    { 0x2CE, "_func_2CE" }, // MP 0x14032C6B0
    { 0x2CF, "_func_2CF" }, // MP 0x140318AD0
    { 0x2D0, "_func_2D0" }, // SP 0x140260350
    { 0x2D1, "_func_2D1" }, // MP 0x1402D3460
    { 0x2D2, "_func_2D2" }, // SP 0x14025CFA0
    { 0x2D3, "_func_2D3" }, // MP 0x14032C2D0
    { 0x2D4, "_func_2D4" }, // MP 0x140332620
    { 0x2D5, "_func_2D5" }, // MP 0x140332610
    { 0x2D6, "_func_2D6" }, // MP 0x1402D3630
    { 0x2D7, "_func_2D7" }, // MP 0x14031AA80
    { 0x2D8, "_func_2D8" }, // SP 0x140240AD0, MP 0x14031EAD0
    { 0x2D9, "_func_2D9" }, // MP 0x140328010
    { 0x2DA, "_func_2DA" }, // MP 0x14031B670
    { 0x2DB, "_func_2DB" }, // MP 0x14031D3F0
    { 0x2DC, "_func_2DC" }, // MP 0x14031E670
    { 0x2DD, "_func_2DD" }, // MP 0x140339100
    { 0x2DE, "_func_2DE" }, // MP 0x140319200
    { 0x2DF, "_func_2DF" }, // MP 0x140331E00
}};

const std::array<pair_16C, 1389> method_list
{{
    { 0x8000, "_meth_8000" }, // SP 0x140243FC0, MP 0x140321BF0
    { 0x8001, "_meth_8001" }, // SP 0x14025D290
    { 0x8002, "_meth_8002" }, // MP 0x140522DA0
    { 0x8003, "_meth_8003" }, // MP 0x140327D90
    { 0x8004, "_meth_8004" }, // MP 0x140328150
    { 0x8005, "_meth_8005" }, // MP 0x14032AC70
    { 0x8006, "_meth_8006" }, // MP 0x14032ACB0
    { 0x8007, "_meth_8007" }, // MP 0x14032ADA0
    { 0x8008, "_meth_8008" }, // MP 0x14032AE00
    { 0x8009, "_meth_8009" }, // MP 0x14032AE60
    { 0x800A, "_meth_800A" }, // MP 0x14032CAF0
    { 0x800B, "_meth_800B" }, // MP 0x14032CB50
    { 0x800C, "_meth_800C" }, // MP 0x14032CD60
    { 0x800D, "_meth_800D" }, // MP 0x14032CC80
    { 0x800E, "_meth_800E" }, // MP 0x14032C2F0
    { 0x800F, "_meth_800F" }, // MP 0x14032C370
    { 0x8010, "_meth_8010" }, // MP 0x14032C350
    { 0x8011, "_meth_8011" }, // MP 0x14032C390
    { 0x8012, "_meth_8012" }, // MP 0x14032E080
    { 0x8013, "_meth_8013" }, // MP 0x14032C7A0
    { 0x8014, "_meth_8014" }, // MP 0x14032C870
    { 0x8015, "_meth_8015" }, // MP 0x14032C960
    { 0x8016, "_meth_8016" }, // MP 0x14032CA40
    { 0x8017, "_meth_8017" }, // MP 0x14032C310
    { 0x8018, "_meth_8018" }, // MP 0x14032C460
    { 0x8019, "_meth_8019" }, // MP 0x140328CD0
    { 0x801A, "_meth_801A" }, // SP 0x14024E140, MP 0x1403167C0
    { 0x801B, "_meth_801B" }, // MP 0x14032D4E0
    { 0x801C, "_meth_801C" }, // MP 0x14032DA10
    { 0x801D, "_meth_801D" }, // SP 0x140247610, MP 0x140311030
    { 0x801E, "_meth_801E" }, // SP 0x1402617C0
    { 0x801F, "_meth_801F" }, // SP 0x1402617F0
    { 0x8020, "_meth_8020" }, // SP 0x140261910
    { 0x8021, "_meth_8021" }, // SP 0x140259710
    { 0x8022, "_meth_8022" }, // SP 0x140259730
    { 0x8023, "_meth_8023" }, // SP 0x1402598B0, MP 0x14032D110
    { 0x8024, "_meth_8024" }, // SP 0x1402598D0
    { 0x8025, "_meth_8025" }, // SP 0x140243780, MP 0x14031D9D0
    { 0x8026, "_meth_8026" }, // MP 0x14032F8A0
    { 0x8027, "_meth_8027" }, // empty
    { 0x8028, "_meth_8028" }, // SP 0x140259D50
    { 0x8029, "_meth_8029" }, // SP 0x140243D30, MP 0x140321AA0
    { 0x802A, "_meth_802A" }, // SP 0x140248580, MP 0x140311FB0
    { 0x802B, "_meth_802B" }, // SP 0x140248980, MP 0x140312130
    { 0x802C, "_meth_802C" }, // SP 0x14024A5E0, MP 0x1403144E0
    { 0x802D, "_meth_802D" }, // SP 0x14024A7F0, MP 0x1403146A0
    { 0x802E, "_meth_802E" }, // SP 0x14024AAB0, MP 0x140314840
    { 0x802F, "_meth_802F" }, // SP 0x14025A350
    { 0x8030, "_meth_8030" }, // SP 0x14025A3E0
    { 0x8031, "_meth_8031" }, // SP 0x14025A560
    { 0x8032, "_meth_8032" }, // SP 0x14025B7E0
    { 0x8033, "_meth_8033" }, // SP 0x14027DFE0
    { 0x8034, "_meth_8034" }, // SP 0x14027DF70, MP 0x1402D1D80
    { 0x8035, "_meth_8035" }, // SP 0x14027DED0, MP 0x1402D1CE0
    { 0x8036, "_meth_8036" }, // SP 0x14025F9C0
    { 0x8037, "_meth_8037" }, // SP 0x14025FA80
    { 0x8038, "_meth_8038" }, // SP 0x14025FEB0
    { 0x8039, "_meth_8039" }, // SP 0x140261030
    { 0x803A, "_meth_803A" }, // SP 0x140261050
    { 0x803B, "_meth_803B" }, // SP 0x140261170
    { 0x803C, "_meth_803C" }, // SP 0x14025B970
    { 0x803D, "_meth_803D" }, // SP 0x14025B9B0
    { 0x803E, "_meth_803E" }, // SP 0x14025BB00
    { 0x803F, "_meth_803F" }, // SP 0x14025BB40
    { 0x8040, "_meth_8040" }, // SP 0x14025BC00
    { 0x8041, "_meth_8041" }, // SP 0x14025D150
    { 0x8042, "_meth_8042" }, // SP 0x14025D240
    { 0x8043, "_meth_8043" }, // SP 0x14024D860, MP 0x140316310
    { 0x8044, "_meth_8044" }, // SP 0x14024DAA0, MP 0x140316590
    { 0x8045, "_meth_8045" }, // SP 0x140261430
    { 0x8046, "_meth_8046" }, // SP 0x140261450
    { 0x8047, "_meth_8047" }, // SP 0x14024ACA0, MP 0x140314A80
    { 0x8048, "_meth_8048" }, // SP 0x14024B060, MP 0x140315570
    { 0x8049, "_meth_8049" }, // SP 0x14024B570, MP 0x1403159E0
    { 0x804A, "_meth_804A" }, // SP 0x14024BAB0, MP 0x140315BE0
    { 0x804B, "_meth_804B" }, // SP 0x14024BE00, MP 0x140315F10
    { 0x804C, "_meth_804C" }, // SP 0x14024C3A0, MP 0x140316280
    { 0x804D, "_meth_804D" }, // SP 0x14024D310, MP 0x140317A90
    { 0x804E, "_meth_804E" }, // SP 0x14024D720, MP 0x140318250
    { 0x804F, "_meth_804F" }, // SP 0x14024D790, MP 0x140318390
    { 0x8050, "_meth_8050" }, // SP 0x140261820, MP 0x140329690
    { 0x8051, "_meth_8051" }, // SP 0x14024C410, MP 0x140313E60
    { 0x8052, "_meth_8052" }, // SP 0x1402594E0
    { 0x8053, "_meth_8053" }, // SP 0x140259840, MP 0x14032ABA0
    { 0x8054, "_meth_8054" }, // SP 0x140259860, MP 0x14032ABF0
    { 0x8055, "_meth_8055" }, // SP 0x140259880
    { 0x8056, "_meth_8056" }, // SP 0x140259960
    { 0x8057, "_meth_8057" }, // SP 0x140250700, MP 0x14031AD40
    { 0x8058, "_meth_8058" }, // SP 0x140250960, MP 0x14031B050
    { 0x8059, "_meth_8059" }, // SP 0x140250BD0, MP 0x14031B2C0
    { 0x805A, "_meth_805A" }, // SP 0x140250CD0, MP 0x14031B350
    { 0x805B, "_meth_805B" }, // SP 0x14025CC40
    { 0x805C, "_meth_805C" }, // SP 0x14025CC60
    { 0x805D, "_meth_805D" }, // SP 0x14025CC80
    { 0x805E, "_meth_805E" }, // SP 0x14025CCD0
    { 0x805F, "_meth_805F" }, // SP 0x14025DA20
    { 0x8060, "_meth_8060" }, // SP 0x14025DAA0
    { 0x8061, "_meth_8061" }, // SP 0x14025E3D0
    { 0x8062, "_meth_8062" }, // SP 0x14025F390
    { 0x8063, "_meth_8063" }, // SP 0x14025F400
    { 0x8064, "_meth_8064" }, // SP 0x140241600, MP 0x14031FC50
    { 0x8065, "_meth_8065" }, // SP 0x140259B30, MP 0x14032CE60
    { 0x8066, "_meth_8066" }, // SP 0x140259E80, MP 0x14032D070
    { 0x8067, "_meth_8067" }, // SP 0x14025A120
    { 0x8068, "_meth_8068" }, // SP 0x14024D9F0, MP 0x1403183D0
    { 0x8069, "_meth_8069" }, // SP 0x14024ED20, MP 0x1403198B0
    { 0x806A, "_meth_806A" }, // SP 0x140261290
    { 0x806B, "_meth_806B" }, // empty
    { 0x806C, "_meth_806C" }, // SP 0x14024F1B0, MP 0x14031DEE0
    { 0x806D, "_meth_806D" }, // SP 0x14024F180, MP 0x14031D9A0
    { 0x806E, "_meth_806E" }, // SP 0x14024F580, MP 0x14031E390
    { 0x806F, "_meth_806F" }, // SP 0x14024F550, MP 0x14031E1C0
    { 0x8070, "_meth_8070" }, // SP 0x14023EE50
    { 0x8071, "_meth_8071" }, // empty
    { 0x8072, "_meth_8072" }, // empty
    { 0x8073, "_meth_8073" }, // empty
    { 0x8074, "_meth_8074" }, // SP 0x140261310, MP 0x140329200
    { 0x8075, "_meth_8075" }, // SP 0x140261390, MP 0x1403292F0
    { 0x8076, "_meth_8076" }, // SP 0x140261400
    { 0x8077, "_meth_8077" }, // SP 0x140261500
    { 0x8078, "_meth_8078" }, // SP 0x140261530
    { 0x8079, "_meth_8079" }, // SP 0x1402615C0
    { 0x807A, "_meth_807A" }, // SP 0x1402615E0
    { 0x807B, "_meth_807B" }, // SP 0x140261740, MP 0x140329410
    { 0x807C, "_meth_807C" }, // SP 0x14024F8B0, MP 0x14031AA90
    { 0x807D, "_meth_807D" }, // SP 0x14024FA90, MP 0x14031AD20
    { 0x807E, "_meth_807E" }, // SP 0x14024FB10, MP 0x14031AED0
    { 0x807F, "_meth_807F" }, // SP 0x14024FC00, MP 0x14031AF00
    { 0x8080, "_meth_8080" }, // SP 0x1402535F0, MP 0x14031D010
    { 0x8081, "_meth_8081" }, // SP 0x140250380, MP 0x14031B520
    { 0x8082, "_meth_8082" }, // SP 0x14021EA10, MP 0x1402EF1F0
    { 0x8083, "_meth_8083" }, // SP 0x14021EA60, MP 0x1402EF240
    { 0x8084, "_meth_8084" }, // SP 0x14021EE30, MP 0x1402EF5E0
    { 0x8085, "_meth_8085" }, // SP 0x14021EF70, MP 0x1402EF720
    { 0x8086, "_meth_8086" }, // SP 0x14021F050, MP 0x1402EF800
    { 0x8087, "_meth_8087" }, // SP 0x14021F190, MP 0x1402EF8B0
    { 0x8088, "_meth_8088" }, // SP 0x14021F1D0, MP 0x1402EF980
    { 0x8089, "_meth_8089" }, // SP 0x14021F300, MP 0x1402EFA60
    { 0x808A, "_meth_808A" }, // SP 0x14021F240, MP 0x1402EF9D0
    { 0x808B, "_meth_808B" }, // SP 0x14021EED0, MP 0x1402EF680
    { 0x808C, "_meth_808C" }, // SP 0x14025CC00
    { 0x808D, "_meth_808D" }, // SP 0x14025CC20
    { 0x808E, "_meth_808E" }, // SP 0x14025D300
    { 0x808F, "_meth_808F" }, // SP 0x14025D340
    { 0x8090, "_meth_8090" }, // SP 0x1402599B0
    { 0x8091, "_meth_8091" }, // SP 0x14025D840, MP 0x14032E720
    { 0x8092, "_meth_8092" }, // SP 0x14024CFF0, MP 0x14031B370
    { 0x8093, "_meth_8093" }, // SP 0x14025F470
    { 0x8094, "_meth_8094" }, // SP 0x14025F510
    { 0x8095, "_meth_8095" }, // SP 0x14025F5B0, MP 0x14032F8B0
    { 0x8096, "_meth_8096" }, // SP 0x14025F660
    { 0x8097, "_meth_8097" }, // SP 0x14025F750
    { 0x8098, "_meth_8098" }, // SP 0x1402608B0
    { 0x8099, "_meth_8099" }, // SP 0x1402608F0, MP 0x14032FA40
    { 0x809A, "_meth_809A" }, // SP 0x140261150, MP 0x14032FDA0
    { 0x809B, "_meth_809B" }, // empty
    { 0x809C, "_meth_809C" }, // empty
    { 0x809D, "_meth_809D" }, // empty
    { 0x809E, "_meth_809E" }, // empty
    { 0x809F, "_meth_809F" }, // SP 0x140250780, MP 0x14031BA70
    { 0x80A0, "_meth_80A0" }, // SP 0x140250BF0, MP 0x14031C050
    { 0x80A1, "_meth_80A1" }, // SP 0x140251060, MP 0x14031C510
    { 0x80A2, "_meth_80A2" }, // SP 0x14023E070, MP 0x14031DF10
    { 0x80A3, "_meth_80A3" }, // SP 0x14023E810, MP 0x14031E4E0
    { 0x80A4, "_meth_80A4" }, // SP 0x14023EEC0
    { 0x80A5, "_meth_80A5" }, // SP 0x14023F740
    { 0x80A6, "_meth_80A6" }, // SP 0x1402404F0
    { 0x80A7, "_meth_80A7" }, // SP 0x140240D80
    { 0x80A8, "_meth_80A8" }, // SP 0x140247240, MP 0x14030ED30
    { 0x80A9, "_meth_80A9" }, // SP 0x1402505C0, MP 0x1403199D0
    { 0x80AA, "_meth_80AA" }, // SP 0x140250830, MP 0x140319CB0
    { 0x80AB, "_meth_80AB" }, // SP 0x140241D60, MP 0x1403209F0
    { 0x80AC, "_meth_80AC" }, // SP 0x140251210, MP 0x14031AA20
    { 0x80AD, "_meth_80AD" }, // SP 0x1402421E0, MP 0x140320FB0
    { 0x80AE, "_meth_80AE" }, // SP 0x140242250, MP 0x1403210A0
    { 0x80AF, "_meth_80AF" }, // SP 0x140242AE0, MP 0x1403216E0
    { 0x80B0, "delete" },
    { 0x80B1, "_meth_80B1" }, // SP 0x140245F70, MP 0x14030F8D0
    { 0x80B2, "_meth_80B2" }, // SP 0x140242F40, MP 0x140320CF0
    { 0x80B3, "_meth_80B3" }, // SP 0x140243250, MP 0x1403211B0
    { 0x80B4, "_meth_80B4" }, // empty
    { 0x80B5, "_meth_80B5" }, // empty
    { 0x80B6, "_meth_80B6" }, // SP 0x1402434E0, MP 0x1403213B0
    { 0x80B7, "_meth_80B7" }, // SP 0x140243990, MP 0x1403218A0
    { 0x80B8, "_meth_80B8" }, // SP 0x140245650, MP 0x14030C6E0
    { 0x80B9, "_meth_80B9" }, // SP 0x140245A30, MP 0x14030CA30
    { 0x80BA, "_meth_80BA" }, // MP 0x14030CE40
    { 0x80BB, "_meth_80BB" }, // MP 0x14030CFB0
    { 0x80BC, "_meth_80BC" }, // MP 0x14030D220
    { 0x80BD, "_meth_80BD" }, // empty
    { 0x80BE, "_meth_80BE" }, // SP 0x140240E60, MP 0x14031E770
    { 0x80BF, "_meth_80BF" }, // SP 0x140240F70, MP 0x14031E9D0
    { 0x80C0, "_meth_80C0" }, // SP 0x140241270, MP 0x14031EBA0
    { 0x80C1, "_meth_80C1" }, // SP 0x14024E190, MP 0x14031C420
    { 0x80C2, "_meth_80C2" }, // SP 0x14024E8E0, MP 0x14031C9C0
    { 0x80C3, "_meth_80C3" }, // SP 0x140213270
    { 0x80C4, "_meth_80C4" }, // SP 0x140218180
    { 0x80C5, "_meth_80C5" }, // SP 0x140415BF0
    { 0x80C6, "_meth_80C6" }, // SP 0x140413E10
    { 0x80C7, "_meth_80C7" }, // SP 0x140415A50
    { 0x80C8, "_meth_80C8" }, // SP 0x140415AE0
    { 0x80C9, "_meth_80C9" }, // SP 0x140415390
    { 0x80CA, "_meth_80CA" }, // SP 0x14021DE70, MP 0x1402EE7C0
    { 0x80CB, "_meth_80CB" }, // MP 0x1402EE880
    { 0x80CC, "_meth_80CC" }, // SP 0x14021DF30, MP 0x1402EE890
    { 0x80CD, "_meth_80CD" }, // SP 0x14021E050, MP 0x1402EE990
    { 0x80CE, "_meth_80CE" }, // SP 0x14021E1D0, MP 0x1402EEB10
    { 0x80CF, "_meth_80CF" }, // SP 0x14021E2B0, MP 0x1402EEBE0
    { 0x80D0, "_meth_80D0" }, // SP 0x14021E380, MP 0x1402EEC90
    { 0x80D1, "_meth_80D1" }, // SP 0x14021E450, MP 0x1402EED30
    { 0x80D2, "_meth_80D2" }, // SP 0x14021E510, MP 0x1402EEDE0
    { 0x80D3, "_meth_80D3" }, // SP 0x14021E5E0, MP 0x1402EEE90
    { 0x80D4, "_meth_80D4" }, // SP 0x14021E6B0, MP 0x1402EEF30
    { 0x80D5, "_meth_80D5" }, // SP 0x14021E770, MP 0x1402EEFE0
    { 0x80D6, "_meth_80D6" }, // SP 0x14021E790, MP 0x1402EF000
    { 0x80D7, "_meth_80D7" }, // SP 0x14021E7B0, MP 0x1402EF020
    { 0x80D8, "_meth_80D8" }, // SP 0x14021E850, MP 0x1402EF0A0
    { 0x80D9, "_meth_80D9" }, // SP 0x14021E9C0, MP 0x1402EF1A0
    { 0x80DA, "_meth_80DA" }, // SP 0x140241840, MP 0x14031F3A0
    { 0x80DB, "_meth_80DB" }, // SP 0x140241FF0, MP 0x140320400
    { 0x80DC, "_meth_80DC" }, // MP 0x140328620
    { 0x80DD, "_meth_80DD" }, // SP 0x140242550, MP 0x140320750
    { 0x80DE, "_meth_80DE" }, // SP 0x1402428C0, MP 0x1403208F0
    { 0x80DF, "_meth_80DF" }, // SP 0x1402413D0, MP 0x14031ED80
    { 0x80E0, "_meth_80E0" }, // SP 0x1402414A0, MP 0x14031EE50
    { 0x80E1, "_meth_80E1" }, // MP 0x14031EFA0
    { 0x80E2, "_meth_80E2" }, // SP 0x140251410, MP 0x14031B620
    { 0x80E3, "_meth_80E3" }, // SP 0x1402514F0, MP 0x14031B800
    { 0x80E4, "_meth_80E4" }, // SP 0x1402517C0, MP 0x14031B980
    { 0x80E5, "_meth_80E5" }, // SP 0x140251950, MP 0x14031BC70
    { 0x80E6, "_meth_80E6" }, // SP 0x140251A60, MP 0x14031BDC0
    { 0x80E7, "_meth_80E7" }, // SP 0x140251C20, MP 0x14031C0E0
    { 0x80E8, "_meth_80E8" }, // MP 0x14031AAA0
    { 0x80E9, "_meth_80E9" }, // MP 0x14031B2E0
    { 0x80EA, "_meth_80EA" }, // SP 0x140253FC0, MP 0x14031D3A0
    { 0x80EB, "_meth_80EB" }, // SP 0x1402540B0, MP 0x14031D4F0
    { 0x80EC, "_meth_80EC" }, // SP 0x140219C40
    { 0x80ED, "_meth_80ED" }, // SP 0x140219CA0
    { 0x80EE, "_meth_80EE" }, // SP 0x140219CF0
    { 0x80EF, "_meth_80EF" }, // SP 0x140219D40
    { 0x80F0, "_meth_80F0" }, // SP 0x140219DA0
    { 0x80F1, "_meth_80F1" }, // SP 0x140219E00
    { 0x80F2, "_meth_80F2" }, // SP 0x140219E50
    { 0x80F3, "_meth_80F3" }, // SP 0x14021A1A0
    { 0x80F4, "_meth_80F4" }, // SP 0x14021A370
    { 0x80F5, "_meth_80F5" }, // SP 0x14021A3D0
    { 0x80F6, "_meth_80F6" }, // SP 0x14021A430
    { 0x80F7, "_meth_80F7" }, // SP 0x14021A4C0
    { 0x80F8, "_meth_80F8" }, // SP 0x14021A570
    { 0x80F9, "_meth_80F9" }, // SP 0x140217650, MP 0x1402DF4D0
    { 0x80FA, "_meth_80FA" }, // SP 0x140219F40
    { 0x80FB, "_meth_80FB" }, // SP 0x140219F90
    { 0x80FC, "_meth_80FC" }, // SP 0x14021A060
    { 0x80FD, "_meth_80FD" }, // SP 0x14021A0F0
    { 0x80FE, "_meth_80FE" }, // SP 0x140215C90, MP 0x1402DDB00
    { 0x80FF, "_meth_80FF" }, // SP 0x140215F00, MP 0x1402DDCC0
    { 0x8100, "_meth_8100" }, // SP 0x140219FE0
    { 0x8101, "_meth_8101" }, // SP 0x140215910
    { 0x8102, "_meth_8102" }, // SP 0x140212F60
    { 0x8103, "_meth_8103" }, // SP 0x140254700, MP 0x14031D800
    { 0x8104, "_meth_8104" }, // SP 0x14023DFE0, MP 0x14031DAD0
    { 0x8105, "_meth_8105" }, // SP 0x14023E530, MP 0x14031E310
    { 0x8106, "_meth_8106" }, // SP 0x14023E6A0, MP 0x14031E440
    { 0x8107, "_meth_8107" }, // SP 0x14023EAF0, MP 0x14031E4F0
    { 0x8108, "_meth_8108" }, // SP 0x14023EDF0, MP 0x14031EA50
    { 0x8109, "_meth_8109" }, // SP 0x14023F010, MP 0x14031EB10
    { 0x810A, "_meth_810A" }, // SP 0x14023FD90, MP 0x1403202F0
    { 0x810B, "_meth_810B" }, // SP 0x14023FF60, MP 0x140320350
    { 0x810C, "_meth_810C" }, // SP 0x14023FFC0, MP 0x1403204D0
    { 0x810D, "_meth_810D" }, // SP 0x14023B180
    { 0x810E, "_meth_810E" }, // SP 0x14023B1A0
    { 0x810F, "_meth_810F" }, // SP 0x14023B1C0
    { 0x8110, "_meth_8110" }, // SP 0x14023B1E0
    { 0x8111, "_meth_8111" }, // SP 0x14023B200
    { 0x8112, "_meth_8112" }, // SP 0x14023B220
    { 0x8113, "_meth_8113" }, // SP 0x14023B230
    { 0x8114, "_meth_8114" }, // SP 0x14023B250
    { 0x8115, "_meth_8115" }, // SP 0x14023B270
    { 0x8116, "_meth_8116" }, // SP 0x14023B340
    { 0x8117, "_meth_8117" }, // SP 0x14023B3C0
    { 0x8118, "_meth_8118" }, // SP 0x1402160E0, MP 0x1402DD450
    { 0x8119, "_meth_8119" }, // SP 0x1402161D0, MP 0x1402DD5C0
    { 0x811A, "_meth_811A" }, // SP 0x140216340, MP 0x1402DD8C0
    { 0x811B, "_meth_811B" }, // SP 0x1402163A0, MP 0x1402DD9E0
    { 0x811C, "_meth_811C" }, // SP 0x140219080
    { 0x811D, "_meth_811D" }, // SP 0x140219500
    { 0x811E, "_meth_811E" }, // empty
    { 0x811F, "_meth_811F" }, // SP 0x1402192C0
    { 0x8120, "_meth_8120" }, // SP 0x140219340
    { 0x8121, "_meth_8121" }, // SP 0x140219670
    { 0x8122, "_meth_8122" }, // empty
    { 0x8123, "_meth_8123" }, // empty
    { 0x8124, "_meth_8124" }, // empty
    { 0x8125, "_meth_8125" }, // empty
    { 0x8126, "_meth_8126" }, // empty
    { 0x8127, "_meth_8127" }, // SP 0x140219360
    { 0x8128, "_meth_8128" }, // SP 0x1402196C0
    { 0x8129, "_meth_8129" }, // SP 0x1402197F0
    { 0x812A, "_meth_812A" }, // SP 0x1402191E0
    { 0x812B, "_meth_812B" }, // SP 0x1402198A0
    { 0x812C, "_meth_812C" }, // SP 0x140213E10, MP 0x1402E3B60
    { 0x812D, "_meth_812D" }, // SP 0x1402140A0, MP 0x1402E3EE0
    { 0x812E, "_meth_812E" }, // SP 0x140217B90, MP 0x1402DFB80
    { 0x812F, "_meth_812F" }, // SP 0x140219B70
    { 0x8130, "_meth_8130" }, // SP 0x140215F20, MP 0x1402DD080
    { 0x8131, "_meth_8131" }, // SP 0x140216000, MP 0x1402DD240
    { 0x8132, "_meth_8132" }, // SP 0x140219BE0
    { 0x8133, "_meth_8133" }, // SP 0x140240030, MP 0x1403205E0
    { 0x8134, "_meth_8134" }, // SP 0x140240460, MP 0x140320960
    { 0x8135, "_meth_8135" }, // SP 0x1402406F0, MP 0x140320BB0
    { 0x8136, "_meth_8136" }, // SP 0x140240B10, MP 0x140320DB0
    { 0x8137, "_meth_8137" }, // SP 0x140240BE0, MP 0x140321050
    { 0x8138, "_meth_8138" }, // SP 0x140240C90, MP 0x140321160
    { 0x8139, "_meth_8139" }, // SP 0x14028A2E0, MP 0x140043790
    { 0x813A, "_meth_813A" }, // SP 0x14028A3F0, MP 0x1400438C0
    { 0x813B, "_meth_813B" }, // SP 0x14028A4F0
    { 0x813C, "_meth_813C" }, // SP 0x14028A550
    { 0x813D, "_meth_813D" }, // SP 0x14028A5F0
    { 0x813E, "_meth_813E" }, // SP 0x14023AE00
    { 0x813F, "_meth_813F" }, // empty
    { 0x8140, "_meth_8140" }, // SP 0x14023AE40
    { 0x8141, "_meth_8141" }, // SP 0x14023ADE0
    { 0x8142, "_meth_8142" }, // SP 0x14023AE80
    { 0x8143, "_meth_8143" }, // SP 0x14023AF00
    { 0x8144, "_meth_8144" }, // SP 0x14023AF20
    { 0x8145, "_meth_8145" }, // SP 0x14023AF30
    { 0x8146, "_meth_8146" }, // SP 0x14023AF50
    { 0x8147, "_meth_8147" }, // SP 0x14023AF70
    { 0x8148, "_meth_8148" }, // SP 0x14023AF90
    { 0x8149, "_meth_8149" }, // SP 0x14023AFA0
    { 0x814A, "_meth_814A" }, // SP 0x14023AFC0
    { 0x814B, "_meth_814B" }, // SP 0x14023AFE0
    { 0x814C, "_meth_814C" }, // SP 0x14023B000
    { 0x814D, "_meth_814D" }, // SP 0x14023B010
    { 0x814E, "_meth_814E" }, // SP 0x14023B030
    { 0x814F, "_meth_814F" }, // SP 0x14023B050
    { 0x8150, "_meth_8150" }, // SP 0x14023B0C0
    { 0x8151, "_meth_8151" }, // SP 0x14023B100
    { 0x8152, "_meth_8152" }, // SP 0x14023B150
    { 0x8153, "_meth_8153" }, // SP 0x14023B170
    { 0x8154, "_meth_8154" }, // MP 0x140321240
    { 0x8155, "_meth_8155" }, // SP 0x140240EC0, MP 0x140321340
    { 0x8156, "_meth_8156" }, // SP 0x140241210, MP 0x1403214C0
    { 0x8157, "_meth_8157" }, // SP 0x1402414F0, MP 0x140321810
    { 0x8158, "_meth_8158" }, // SP 0x140241A10, MP 0x140321B90
    { 0x8159, "_meth_8159" }, // SP 0x140241B20, MP 0x140321D30
    { 0x815A, "_meth_815A" }, // SP 0x140241DB0, MP 0x140321F10
    { 0x815B, "_meth_815B" }, // SP 0x140241EE0, MP 0x140322220
    { 0x815C, "_meth_815C" }, // SP 0x140242100, MP 0x140322280
    { 0x815D, "_meth_815D" }, // SP 0x1401FA0E0
    { 0x815E, "_meth_815E" }, // SP 0x1401FA140
    { 0x815F, "_meth_815F" }, // SP 0x1401FA1D0
    { 0x8160, "_meth_8160" }, // SP 0x1401FA2C0
    { 0x8161, "_meth_8161" }, // SP 0x1401FA410
    { 0x8162, "_meth_8162" }, // SP 0x1401FA4E0
    { 0x8163, "_meth_8163" }, // SP 0x1401FA520
    { 0x8164, "_meth_8164" }, // SP 0x1401FA5E0
    { 0x8165, "_meth_8165" }, // SP 0x140216A60, MP 0x1402DE3C0
    { 0x8166, "_meth_8166" }, // SP 0x1401FA6B0
    { 0x8167, "_meth_8167" }, // SP 0x1401FA800
    { 0x8168, "_meth_8168" }, // SP 0x1401FAA20
    { 0x8169, "_meth_8169" }, // SP 0x1401FAB60
    { 0x816A, "_meth_816A" }, // SP 0x1401FAC30
    { 0x816B, "_meth_816B" }, // SP 0x1401FACF0
    { 0x816C, "_meth_816C" }, // SP 0x1401FADB0
    { 0x816D, "_meth_816D" }, // SP 0x1401FAE90
    { 0x816E, "_meth_816E" }, // SP 0x1401FAF60
    { 0x816F, "_meth_816F" }, // SP 0x1401FB040
    { 0x8170, "_meth_8170" }, // SP 0x1401FB1C0
    { 0x8171, "_meth_8171" }, // SP 0x1401FB3F0
    { 0x8172, "_meth_8172" }, // SP 0x1401FB450
    { 0x8173, "_meth_8173" }, // SP 0x1401FB4B0
    { 0x8174, "_meth_8174" }, // SP 0x1401FB6A0
    { 0x8175, "_meth_8175" }, // SP 0x140289C60, MP 0x140043A30
    { 0x8176, "_meth_8176" }, // SP 0x140289CA0, MP 0x140043A70
    { 0x8177, "_meth_8177" }, // SP 0x14028A070, MP 0x140043530
    { 0x8178, "_meth_8178" }, // SP 0x14028A0E0, MP 0x1400435A0
    { 0x8179, "_meth_8179" }, // SP 0x140242200, MP 0x1403223F0
    { 0x817A, "_meth_817A" }, // SP 0x140242770, MP 0x14030B350
    { 0x817B, "_meth_817B" }, // SP 0x140240C30, MP 0x14031ED20
    { 0x817C, "_meth_817C" }, // SP 0x1402463F0, MP 0x14030D7B0
    { 0x817D, "_meth_817D" }, // SP 0x140246590, MP 0x14030DBC0
    { 0x817E, "_meth_817E" }, // SP 0x140243390, MP 0x140321DC0
    { 0x817F, "_meth_817F" }, // SP 0x140243890, MP 0x1403222E0
    { 0x8180, "_meth_8180" }, // SP 0x140247970, MP 0x140310980
    { 0x8181, "_meth_8181" }, // SP 0x140247B80, MP 0x140310DF0
    { 0x8182, "_meth_8182" }, // SP 0x14024E6A0, MP 0x140315CD0
    { 0x8183, "_meth_8183" }, // SP 0x14024EC90, MP 0x1403166C0
    { 0x8184, "_meth_8184" }, // SP 0x1402456B0, MP 0x14030EA40
    { 0x8185, "_meth_8185" }, // SP 0x140245940, MP 0x14030EDE0
    { 0x8186, "_meth_8186" }, // SP 0x1402485C0, MP 0x140311860
    { 0x8187, "_meth_8187" }, // SP 0x140249170, MP 0x140312070
    { 0x8188, "_meth_8188" }, // SP 0x14024A6A0, MP 0x140313930
    { 0x8189, "_meth_8189" }, // SP 0x1401F88F0
    { 0x818A, "_meth_818A" }, // SP 0x1401F8940
    { 0x818B, "_meth_818B" }, // SP 0x1401F89B0
    { 0x818C, "_meth_818C" }, // SP 0x1401F89F0
    { 0x818D, "_meth_818D" }, // SP 0x1401F8A60
    { 0x818E, "_meth_818E" }, // SP 0x1401F8AF0
    { 0x818F, "_meth_818F" }, // SP 0x1401F8CC0
    { 0x8190, "_meth_8190" }, // SP 0x1401F9000
    { 0x8191, "_meth_8191" }, // SP 0x1401F90F0
    { 0x8192, "_meth_8192" }, // SP 0x1401F9140
    { 0x8193, "_meth_8193" }, // SP 0x1401F9190
    { 0x8194, "_meth_8194" }, // SP 0x1401F91F0
    { 0x8195, "_meth_8195" }, // SP 0x1401F9240
    { 0x8196, "_meth_8196" }, // empty
    { 0x8197, "_meth_8197" }, // empty
    { 0x8198, "_meth_8198" }, // empty
    { 0x8199, "_meth_8199" }, // empty
    { 0x819A, "_meth_819A" }, // SP 0x1401F93F0
    { 0x819B, "_meth_819B" }, // SP 0x1401F94A0
    { 0x819C, "_meth_819C" }, // SP 0x1401F94F0
    { 0x819D, "_meth_819D" }, // SP 0x1401F95A0, MP 0x140405900
    { 0x819E, "_meth_819E" }, // SP 0x1401F9610, MP 0x1404057C0
    { 0x819F, "_meth_819F" }, // SP 0x1401F9680, MP 0x140405860
    { 0x81A0, "_meth_81A0" }, // SP 0x1401F9700
    { 0x81A1, "_meth_81A1" }, // SP 0x1401F97A0
    { 0x81A2, "_meth_81A2" }, // SP 0x1401F9890
    { 0x81A3, "_meth_81A3" }, // SP 0x1401F99A0
    { 0x81A4, "_meth_81A4" }, // SP 0x1401F8320
    { 0x81A5, "_meth_81A5" }, // SP 0x1401F9A60
    { 0x81A6, "_meth_81A6" }, // SP 0x1401F9AD0
    { 0x81A7, "_meth_81A7" }, // SP 0x1401F9B30
    { 0x81A8, "_meth_81A8" }, // SP 0x1401F9BD0
    { 0x81A9, "_meth_81A9" }, // SP 0x1401F9CE0
    { 0x81AA, "_meth_81AA" }, // SP 0x1401F9E40
    { 0x81AB, "_meth_81AB" }, // SP 0x1401F9EF0
    { 0x81AC, "_meth_81AC" }, // SP 0x1401FA030
    { 0x81AD, "_meth_81AD" }, // MP 0x1403139F0
    { 0x81AE, "_meth_81AE" }, // MP 0x140313A00
    { 0x81AF, "_meth_81AF" }, // SP 0x14024A700, MP 0x140313A40
    { 0x81B0, "_meth_81B0" }, // SP 0x140245090, MP 0x14030DE80
    { 0x81B1, "_meth_81B1" }, // SP 0x140243090, MP 0x14030BDA0
    { 0x81B2, "_meth_81B2" }, // SP 0x1402431F0, MP 0x14030C0D0
    { 0x81B3, "_meth_81B3" }, // SP 0x140243540, MP 0x14030C490
    { 0x81B4, "_meth_81B4" }, // SP 0x140243630, MP 0x14030C690
    { 0x81B5, "_meth_81B5" }, // SP 0x140244720, MP 0x14030D830
    { 0x81B6, "_meth_81B6" }, // SP 0x1401FBB30
    { 0x81B7, "_meth_81B7" }, // SP 0x1401FBC20
    { 0x81B8, "_meth_81B8" }, // SP 0x1401FBDD0
    { 0x81B9, "_meth_81B9" }, // SP 0x1401FBE40
    { 0x81BA, "_meth_81BA" }, // SP 0x1401FBFA0
    { 0x81BB, "_meth_81BB" }, // SP 0x1401FC260
    { 0x81BC, "_meth_81BC" }, // SP 0x1401FC390
    { 0x81BD, "_meth_81BD" }, // SP 0x1401FC470
    { 0x81BE, "_meth_81BE" }, // SP 0x1401FC4E0
    { 0x81BF, "_meth_81BF" }, // SP 0x1401FC590
    { 0x81C0, "_meth_81C0" }, // SP 0x14028A440, MP 0x140043920
    { 0x81C1, "_meth_81C1" }, // SP 0x14028A4A0, MP 0x140043980
    { 0x81C2, "_meth_81C2" }, // SP 0x1401FC6E0
    { 0x81C3, "_meth_81C3" }, // SP 0x1401FC960
    { 0x81C4, "_meth_81C4" }, // SP 0x1401FCA70
    { 0x81C5, "_meth_81C5" }, // SP 0x1401F7D80
    { 0x81C6, "_meth_81C6" }, // SP 0x1401F7D90
    { 0x81C7, "_meth_81C7" }, // SP 0x1401F7DB0
    { 0x81C8, "_meth_81C8" }, // SP 0x1401F7DD0
    { 0x81C9, "_meth_81C9" }, // SP 0x1401F7E30
    { 0x81CA, "_meth_81CA" }, // SP 0x1401F7EA0
    { 0x81CB, "_meth_81CB" }, // SP 0x1401F7F70
    { 0x81CC, "_meth_81CC" }, // SP 0x1401F8060
    { 0x81CD, "_meth_81CD" }, // SP 0x1401F80A0
    { 0x81CE, "_meth_81CE" }, // SP 0x1401F80E0
    { 0x81CF, "_meth_81CF" }, // SP 0x1401F8120
    { 0x81D0, "_meth_81D0" }, // SP 0x1401F81B0
    { 0x81D1, "_meth_81D1" }, // SP 0x1401F8760
    { 0x81D2, "_meth_81D2" }, // SP 0x1401F8840
    { 0x81D3, "_meth_81D3" }, // SP 0x1401F84A0
    { 0x81D4, "_meth_81D4" }, // SP 0x140244FB0, MP 0x14030D9F0
    { 0x81D5, "_meth_81D5" }, // SP 0x14024D100, MP 0x140314A00
    { 0x81D6, "_meth_81D6" }, // SP 0x14024D910, MP 0x140315900
    { 0x81D7, "_meth_81D7" }, // SP 0x14024E310, MP 0x140315C70
    { 0x81D8, "_meth_81D8" }, // SP 0x14024E5F0, MP 0x140315CB0
    { 0x81D9, "_meth_81D9" }, // SP 0x140243A40, MP 0x14030CC10
    { 0x81DA, "_meth_81DA" }, // SP 0x140243D70, MP 0x14030CEF0
    { 0x81DB, "_meth_81DB" }, // SP 0x140244000, MP 0x14030D060
    { 0x81DC, "_meth_81DC" }, // SP 0x1402441D0, MP 0x14030D460
    { 0x81DD, "_meth_81DD" }, // SP 0x1402443E0, MP 0x14030D4E0
    { 0x81DE, "_meth_81DE" }, // SP 0x14024D440, MP 0x140316020
    { 0x81DF, "_meth_81DF" }, // SP 0x14024D640, MP 0x140316100
    { 0x81E0, "_meth_81E0" }, // SP 0x14024DFF0, MP 0x140316750
    { 0x81E1, "_meth_81E1" }, // SP 0x14024CA40, MP 0x140316610
    { 0x81E2, "_meth_81E2" }, // SP 0x14024EA40, MP 0x140317330
    { 0x81E3, "_meth_81E3" }, // SP 0x14024ED90, MP 0x140317710
    { 0x81E4, "_meth_81E4" }, // SP 0x1401F9DC0
    { 0x81E5, "_meth_81E5" }, // SP 0x1401F9E00
    { 0x81E6, "_meth_81E6" }, // SP 0x1401F9E90
    { 0x81E7, "_meth_81E7" }, // SP 0x1401F9F40
    { 0x81E8, "_meth_81E8" }, // SP 0x1401FA250
    { 0x81E9, "_meth_81E9" }, // SP 0x1401FA390
    { 0x81EA, "_meth_81EA" }, // SP 0x1401FA560
    { 0x81EB, "_meth_81EB" }, // SP 0x1401FA660
    { 0x81EC, "_meth_81EC" }, // SP 0x1401FA7A0
    { 0x81ED, "_meth_81ED" }, // SP 0x1401FA940
    { 0x81EE, "_meth_81EE" }, // SP 0x1401FA980
    { 0x81EF, "_meth_81EF" }, // SP 0x1401FA9D0
    { 0x81F0, "_meth_81F0" }, // SP 0x1401FAAD0
    { 0x81F1, "_meth_81F1" }, // SP 0x1401FABC0
    { 0x81F2, "_meth_81F2" }, // SP 0x1401FAC90
    { 0x81F3, "_meth_81F3" }, // SP 0x1401FAD40
    { 0x81F4, "_meth_81F4" }, // SP 0x1401FAF00
    { 0x81F5, "_meth_81F5" }, // SP 0x1401FAFE0
    { 0x81F6, "_meth_81F6" }, // SP 0x1401FAE20
    { 0x81F7, "_meth_81F7" }, // SP 0x1401FB0B0
    { 0x81F8, "_meth_81F8" }, // SP 0x1401FB0F0
    { 0x81F9, "_meth_81F9" }, // SP 0x1401FB290
    { 0x81FA, "_meth_81FA" }, // SP 0x1401FB2F0
    { 0x81FB, "_meth_81FB" }, // SP 0x1401FB520
    { 0x81FC, "_meth_81FC" }, // SP 0x1401FB800
    { 0x81FD, "_meth_81FD" }, // SP 0x1401FBA00
    { 0x81FE, "_meth_81FE" }, // SP 0x1401FBAA0
    { 0x81FF, "_meth_81FF" }, // SP 0x1401FBC90
    { 0x8200, "_meth_8200" }, // SP 0x14024F360, MP 0x140317BF0
    { 0x8201, "_meth_8201" }, // SP 0x14024F730, MP 0x1403180F0
    { 0x8202, "_meth_8202" }, // MP 0x140319E80
    { 0x8203, "_meth_8203" }, // SP 0x14025EDF0
    { 0x8204, "_meth_8204" }, // MP 0x14031A0D0
    { 0x8205, "_meth_8205" }, // empty
    { 0x8206, "_meth_8206" }, // MP 0x14031A490
    { 0x8207, "_meth_8207" }, // MP 0x14031AB60
    { 0x8208, "_meth_8208" }, // MP 0x14031BCC0
    { 0x8209, "_meth_8209" }, // MP 0x14031B170
    { 0x820A, "_meth_820A" }, // MP 0x14031B590
    { 0x820B, "_meth_820B" }, // SP 0x140250DB0, MP 0x14031CEA0
    { 0x820C, "_meth_820C" }, // SP 0x140251290, MP 0x14031D310
    { 0x820D, "_meth_820D" }, // SP 0x1402516C0, MP 0x14031D770
    { 0x820E, "_meth_820E" }, // SP 0x140252870, MP 0x14031DD50
    { 0x820F, "_meth_820F" }, // SP 0x140253220, MP 0x14031E830
    { 0x8210, "_meth_8210" }, // SP 0x14023F0A0, MP 0x1403208A0
    { 0x8211, "_meth_8211" }, // SP 0x14023F1E0, MP 0x140320A40
    { 0x8212, "_meth_8212" }, // SP 0x14023F6D0, MP 0x140320CE0
    { 0x8213, "_meth_8213" }, // SP 0x14023F800, MP 0x140320DA0
    { 0x8214, "_meth_8214" }, // SP 0x1402416F0, MP 0x14030B690
    { 0x8215, "_meth_8215" }, // SP 0x140241BB0, MP 0x14030BDF0
    { 0x8216, "_meth_8216" }, // SP 0x140242150, MP 0x14030C520
    { 0x8217, "_meth_8217" }, // SP 0x140242810, MP 0x14030CD20
    { 0x8218, "_meth_8218" }, // SP 0x14024EDE0, MP 0x140317890
    { 0x8219, "_meth_8219" }, // SP 0x14024B390
    { 0x821A, "_meth_821A" }, // SP 0x14024B900
    { 0x821B, "_meth_821B" }, // SP 0x14023FA90, MP 0x140320E80
    { 0x821C, "_meth_821C" }, // SP 0x140240100, MP 0x1403215A0
    { 0x821D, "_meth_821D" }, // SP 0x140240590, MP 0x140321B00
    { 0x821E, "_meth_821E" }, // SP 0x140242D40, MP 0x14030BB10
    { 0x821F, "_meth_821F" }, // SP 0x140242B70, MP 0x14030B880
    { 0x8220, "_meth_8220" }, // SP 0x1402432C0, MP 0x14030C370
    { 0x8221, "_meth_8221" }, // SP 0x140247E60, MP 0x14030FA70
    { 0x8222, "_meth_8222" }, // SP 0x14024B550, MP 0x140315C90
    { 0x8223, "_meth_8223" }, // SP 0x14024B740, MP 0x140316000
    { 0x8224, "_meth_8224" }, // SP 0x14024BDE0, MP 0x1403166A0
    { 0x8225, "_meth_8225" }, // SP 0x14024C1B0, MP 0x140316920
    { 0x8226, "_meth_8226" }, // SP 0x14024CCD0, MP 0x140317120
    { 0x8227, "_meth_8227" }, // SP 0x1404146A0, MP 0x140528A90
    { 0x8228, "_meth_8228" }, // SP 0x140414780, MP 0x140528B10
    { 0x8229, "_meth_8229" }, // SP 0x1404149B0, MP 0x140528D80
    { 0x822A, "_meth_822A" }, // SP 0x140414B10, MP 0x140528EA0
    { 0x822B, "_meth_822B" }, // SP 0x140414BE0, MP 0x140528F90
    { 0x822C, "_meth_822C" }, // SP 0x140414C80, MP 0x140529090
    { 0x822D, "_meth_822D" }, // SP 0x140414DC0, MP 0x1405291B0
    { 0x822E, "_meth_822E" }, // SP 0x140414F60, MP 0x1405292C0
    { 0x822F, "_meth_822F" }, // SP 0x140414FF0, MP 0x1405293B0
    { 0x8230, "_meth_8230" }, // SP 0x1404150D0, MP 0x140529470
    { 0x8231, "_meth_8231" }, // SP 0x140415290, MP 0x1405296E0
    { 0x8232, "_meth_8232" }, // MP 0x14052B310
    { 0x8233, "_meth_8233" }, // SP 0x1402513B0
    { 0x8234, "_meth_8234" }, // SP 0x140251610
    { 0x8235, "_meth_8235" }, // SP 0x140252020
    { 0x8236, "_meth_8236" }, // SP 0x1402523C0
    { 0x8237, "_meth_8237" }, // SP 0x140252B10
    { 0x8238, "_meth_8238" }, // SP 0x140252DA0
    { 0x8239, "_meth_8239" }, // SP 0x140245BB0
    { 0x823A, "_meth_823A" }, // SP 0x140245CB0
    { 0x823B, "_meth_823B" }, // SP 0x140245F20
    { 0x823C, "_meth_823C" }, // SP 0x1402461E0
    { 0x823D, "_meth_823D" }, // SP 0x140252090
    { 0x823E, "_meth_823E" }, // SP 0x140252500
    { 0x823F, "_meth_823F" }, // empty
    { 0x8240, "_meth_8240" }, // SP 0x14024F7E0
    { 0x8241, "_meth_8241" }, // SP 0x1401F9A00
    { 0x8242, "_meth_8242" }, // SP 0x1401F9C50
    { 0x8243, "_meth_8243" }, // SP 0x14024B6A0, MP 0x140315EF0
    { 0x8244, "_meth_8244" }, // SP 0x14024B980, MP 0x140316260
    { 0x8245, "_meth_8245" }, // SP 0x14024BFF0, MP 0x1403167A0
    { 0x8246, "_meth_8246" }, // SP 0x14024C710, MP 0x140316CC0
    { 0x8247, "_meth_8247" }, // SP 0x14024CE90, MP 0x140317520
    { 0x8248, "_meth_8248" }, // SP 0x14024DE10, MP 0x140318420
    { 0x8249, "_meth_8249" }, // SP 0x14024E3A0, MP 0x140318D50
    { 0x824A, "_meth_824A" }, // SP 0x1402501D0, MP 0x14031A3F0
    { 0x824B, "_meth_824B" }, // MP 0x1402E6DB0
    { 0x824C, "_meth_824C" }, // SP 0x140218FD0, MP 0x1402E6DA0
    { 0x824D, "_meth_824D" }, // MP 0x1402E84D0
    { 0x824E, "_meth_824E" }, // MP 0x1402E8560
    { 0x824F, "_meth_824F" }, // MP 0x1402E6E20
    { 0x8250, "_meth_8250" }, // SP 0x140211A10, MP 0x1402E1160
    { 0x8251, "_meth_8251" }, // MP 0x1402E7190
    { 0x8252, "_meth_8252" }, // SP 0x140416B50, MP 0x14052AFB0
    { 0x8253, "_meth_8253" }, // SP 0x140416C20, MP 0x14052B080
    { 0x8254, "_meth_8254" }, // SP 0x140416D40, MP 0x14052B120
    { 0x8255, "_meth_8255" }, // SP 0x140416F20
    { 0x8256, "_meth_8256" }, // SP 0x140416FD0, MP 0x14052B380
    { 0x8257, "_meth_8257" }, // SP 0x140417220, MP 0x14052B5D0
    { 0x8258, "_meth_8258" }, // SP 0x1404172A0, MP 0x14052B650
    { 0x8259, "_meth_8259" }, // SP 0x140417330, MP 0x14052B6E0
    { 0x825A, "_meth_825A" }, // SP 0x1404173B0, MP 0x14052B850
    { 0x825B, "_meth_825B" }, // SP 0x140417420, MP 0x14052B8C0
    { 0x825C, "_meth_825C" }, // SP 0x140417510, MP 0x14052B9C0
    { 0x825D, "_meth_825D" }, // SP 0x1404175A0, MP 0x14052BA50
    { 0x825E, "_meth_825E" }, // SP 0x140417620, MP 0x14052BAD0
    { 0x825F, "_meth_825F" }, // SP 0x1404176B0, MP 0x14052BB60
    { 0x8260, "_meth_8260" }, // SP 0x140417730, MP 0x14052BBE0
    { 0x8261, "_meth_8261" }, // SP 0x140413720, MP 0x140527C80
    { 0x8262, "_meth_8262" }, // SP 0x140413810, MP 0x140527D70
    { 0x8263, "_meth_8263" }, // SP 0x140413910, MP 0x140527E70
    { 0x8264, "_meth_8264" }, // SP 0x1404139A0, MP 0x140527F00
    { 0x8265, "_meth_8265" }, // SP 0x140413C80, MP 0x1405281E0
    { 0x8266, "_meth_8266" }, // SP 0x140413D30, MP 0x140528290
    { 0x8267, "_meth_8267" }, // SP 0x140413E90, MP 0x140528370
    { 0x8268, "_meth_8268" }, // SP 0x140413F00, MP 0x1405283E0
    { 0x8269, "_meth_8269" }, // SP 0x140414610, MP 0x140528A20
    { 0x826A, "_meth_826A" }, // MP 0x1402E7660
    { 0x826B, "_meth_826B" }, // MP 0x1402E7CC0
    { 0x826C, "_meth_826C" }, // MP 0x1402E7EB0
    { 0x826D, "_meth_826D" }, // MP 0x1402E7F20
    { 0x826E, "_meth_826E" }, // MP 0x1402E7F90
    { 0x826F, "_meth_826F" }, // MP 0x1402E8000
    { 0x8270, "_meth_8270" }, // MP 0x1402E8070
    { 0x8271, "_meth_8271" }, // MP 0x1402E80D0
    { 0x8272, "_meth_8272" }, // MP 0x1402E8450
    { 0x8273, "_meth_8273" }, // MP 0x1402E85F0
    { 0x8274, "_meth_8274" }, // MP 0x1402E86C0
    { 0x8275, "_meth_8275" }, // MP 0x1402E8860
    { 0x8276, "_meth_8276" }, // SP 0x140265280, MP 0x140333DC0
    { 0x8277, "_meth_8277" }, // SP 0x1402654A0, MP 0x140334000
    { 0x8278, "_meth_8278" }, // SP 0x140265AE0, MP 0x140334660
    { 0x8279, "_meth_8279" }, // MP 0x140334730
    { 0x827A, "_meth_827A" }, // MP 0x140334B20
    { 0x827B, "_meth_827B" }, // MP 0x140334960
    { 0x827C, "_meth_827C" }, // SP 0x1404154A0, MP 0x1405298C0
    { 0x827D, "_meth_827D" }, // SP 0x140415620, MP 0x140529A40
    { 0x827E, "_meth_827E" }, // SP 0x140415720, MP 0x140529B40
    { 0x827F, "_meth_827F" }, // SP 0x1404158C0, MP 0x140529CE0
    { 0x8280, "_meth_8280" }, // SP 0x140415B60, MP 0x140529E70
    { 0x8281, "_meth_8281" }, // SP 0x140415C60, MP 0x140529F00
    { 0x8282, "vehicle_finishdamage" },
    { 0x8283, "_meth_8283" }, // SP 0x140415CE0, MP 0x14052A1D0
    { 0x8284, "_meth_8284" }, // SP 0x140415D50, MP 0x14052A240
    { 0x8285, "_meth_8285" }, // SP 0x140415EE0, MP 0x14052A3D0
    { 0x8286, "_meth_8286" }, // SP 0x140416000, MP 0x14052A4F0
    { 0x8287, "_meth_8287" }, // SP 0x1404160F0, MP 0x14052A5E0
    { 0x8288, "_meth_8288" }, // SP 0x140416160, MP 0x14052A650
    { 0x8289, "_meth_8289" }, // SP 0x1404161D0, MP 0x14052A6C0
    { 0x828A, "_meth_828A" }, // SP 0x140416250, MP 0x14052A750
    { 0x828B, "_meth_828B" }, // SP 0x1404162C0, MP 0x14052A7C0
    { 0x828C, "_meth_828C" }, // SP 0x140416320, MP 0x14052A830
    { 0x828D, "_meth_828D" }, // SP 0x140416380
    { 0x828E, "_meth_828E" }, // SP 0x140416440, MP 0x14052A8A0
    { 0x828F, "_meth_828F" }, // SP 0x1404164B0, MP 0x14052A910
    { 0x8290, "_meth_8290" }, // SP 0x140416520, MP 0x14052A980
    { 0x8291, "_meth_8291" }, // SP 0x140416590, MP 0x14052A9F0
    { 0x8292, "_meth_8292" }, // SP 0x140416620, MP 0x14052AA80
    { 0x8293, "_meth_8293" }, // SP 0x140416780, MP 0x14052ABE0
    { 0x8294, "_meth_8294" }, // SP 0x140416990, MP 0x14052ADF0
    { 0x8295, "_meth_8295" }, // SP 0x140416A50, MP 0x14052AEB0
    { 0x8296, "_meth_8296" }, // SP 0x140416AE0, MP 0x14052AF40
    { 0x8297, "_meth_8297" }, // SP 0x140215990, MP 0x1402E88D0
    { 0x8298, "_meth_8298" }, // MP 0x1402E8AB0
    { 0x8299, "_meth_8299" }, // MP 0x1402E8B10
    { 0x829A, "_meth_829A" }, // MP 0x1402E8B70
    { 0x829B, "_meth_829B" }, // MP 0x1402E8BD0
    { 0x829C, "_meth_829C" }, // MP 0x1402E8C30
    { 0x829D, "_meth_829D" }, // MP 0x1402E8CC0
    { 0x829E, "_meth_829E" }, // MP 0x1402E8D40
    { 0x829F, "_meth_829F" }, // MP 0x1402E8E10
    { 0x82A0, "_meth_82A0" }, // MP 0x1402E8E20
    { 0x82A1, "_meth_82A1" }, // MP 0x1402E8E30
    { 0x82A2, "_meth_82A2" }, // MP 0x1402E8EC0
    { 0x82A3, "_meth_82A3" }, // SP 0x140215250, MP 0x1402DD010
    { 0x82A4, "_meth_82A4" }, // MP 0x1402DF3E0
    { 0x82A5, "_meth_82A5" }, // SP 0x140217F10, MP 0x1402DFF00
    { 0x82A6, "_meth_82A6" }, // SP 0x1402128A0, MP 0x1402E2220
    { 0x82A7, "_meth_82A7" }, // SP 0x140212E30, MP 0x1402E28A0
    { 0x82A8, "_meth_82A8" }, // SP 0x140213680, MP 0x1402E3160
    { 0x82A9, "_meth_82A9" }, // SP 0x140213140, MP 0x1402E2B50
    { 0x82AA, "_meth_82AA" }, // MP 0x1402E63D0
    { 0x82AB, "_meth_82AB" }, // MP 0x1402E64E0
    { 0x82AC, "_meth_82AC" }, // MP 0x1402E3540
    { 0x82AD, "_meth_82AD" }, // MP 0x1402E3550
    { 0x82AE, "_meth_82AE" }, // SP 0x140265FB0, MP 0x1403350C0
    { 0x82AF, "_meth_82AF" }, // SP 0x1402645A0, MP 0x140333110
    { 0x82B0, "_meth_82B0" }, // SP 0x1402645B0, MP 0x140333120
    { 0x82B1, "_meth_82B1" }, // SP 0x1402645D0, MP 0x140333140
    { 0x82B2, "_meth_82B2" }, // SP 0x1402661A0, MP 0x140332DA0
    { 0x82B3, "_meth_82B3" }, // SP 0x1402643B0, MP 0x140332F00
    { 0x82B4, "_meth_82B4" }, // SP 0x140264520, MP 0x140333080
    { 0x82B5, "_meth_82B5" }, // SP 0x1402645F0, MP 0x140333160
    { 0x82B6, "_meth_82B6" }, // SP 0x140264A20, MP 0x1403332B0
    { 0x82B7, "_meth_82B7" }, // SP 0x140264A30, MP 0x1403332C0
    { 0x82B8, "_meth_82B8" }, // SP 0x140264A50, MP 0x1403332E0
    { 0x82B9, "_meth_82B9" }, // SP 0x1402649D0, MP 0x140333260
    { 0x82BA, "_meth_82BA" }, // SP 0x1402649F0, MP 0x140333280
    { 0x82BB, "_meth_82BB" }, // SP 0x140264A10, MP 0x1403332A0
    { 0x82BC, "_meth_82BC" }, // SP 0x140264A70, MP 0x140333300
    { 0x82BD, "_meth_82BD" }, // SP 0x140264CC0, MP 0x1403337B0
    { 0x82BE, "_meth_82BE" }, // SP 0x140265BC0, MP 0x140334CD0
    { 0x82BF, "_meth_82BF" }, // SP 0x140265C70, MP 0x140334D80
    { 0x82C0, "_meth_82C0" }, // SP 0x140264E40, MP 0x140333970
    { 0x82C1, "_meth_82C1" }, // SP 0x140264EA0, MP 0x1403339D0
    { 0x82C2, "_meth_82C2" }, // SP 0x140264F20, MP 0x140333A50
    { 0x82C3, "_meth_82C3" }, // MP 0x1402E5980
    { 0x82C4, "_meth_82C4" }, // MP 0x1402E5990
    { 0x82C5, "_meth_82C5" }, // MP 0x1402E59A0
    { 0x82C6, "_meth_82C6" }, // MP 0x1402E5A60
    { 0x82C7, "_meth_82C7" }, // MP 0x1402E5AC0
    { 0x82C8, "_meth_82C8" }, // MP 0x1402E5B30
    { 0x82C9, "_meth_82C9" }, // MP 0x1402E5BA0
    { 0x82CA, "_meth_82CA" }, // MP 0x1402E5EF0
    { 0x82CB, "_meth_82CB" }, // SP 0x140217770, MP 0x1402DF6A0
    { 0x82CC, "_meth_82CC" }, // SP 0x1402177D0, MP 0x1402DF7C0
    { 0x82CD, "_meth_82CD" }, // MP 0x1402E5F60
    { 0x82CE, "_meth_82CE" }, // SP 0x140216D40, MP 0x1402DEC00
    { 0x82CF, "_meth_82CF" }, // SP 0x140216E90, MP 0x1402DED60
    { 0x82D0, "_meth_82D0" }, // SP 0x140216FE0, MP 0x1402DEEC0
    { 0x82D1, "_meth_82D1" }, // SP 0x140217130, MP 0x1402DF020
    { 0x82D2, "_meth_82D2" }, // SP 0x140212160, MP 0x1402E1A30
    { 0x82D3, "_meth_82D3" }, // SP 0x140212490, MP 0x1402E1DF0
    { 0x82D4, "_meth_82D4" }, // SP 0x140218160, MP 0x1402E0170
    { 0x82D5, "_meth_82D5" }, // SP 0x140210920, MP 0x1402E0180
    { 0x82D6, "_meth_82D6" }, // SP 0x1402109A0, MP 0x1402E0210
    { 0x82D7, "_meth_82D7" }, // SP 0x1402109C0, MP 0x1402E02B0
    { 0x82D8, "_meth_82D8" }, // SP 0x1402109E0, MP 0x1402E02D0
    { 0x82D9, "_meth_82D9" }, // SP 0x140211B40, MP 0x1402E12B0
    { 0x82DA, "_meth_82DA" }, // SP 0x14025D320, MP 0x1402E18D0
    { 0x82DB, "_meth_82DB" }, // MP 0x1402E18F0
    { 0x82DC, "_meth_82DC" }, // SP 0x1402605B0
    { 0x82DD, "_meth_82DD" }, // SP 0x1402138F0, MP 0x1402E3560
    { 0x82DE, "_meth_82DE" }, // SP 0x140213C10, MP 0x1402E3B30
    { 0x82DF, "_meth_82DF" }, // SP 0x140213EA0, MP 0x1402E3CD0
    { 0x82E0, "_meth_82E0" }, // SP 0x140213FD0, MP 0x1402E3E60
    { 0x82E1, "_meth_82E1" }, // SP 0x140214610, MP 0x1402E4770
    { 0x82E2, "_meth_82E2" }, // SP 0x140214830, MP 0x1402E49D0
    { 0x82E3, "_meth_82E3" }, // SP 0x1402149C0, MP 0x1402E4B20
    { 0x82E4, "_meth_82E4" }, // SP 0x140214B20, MP 0x1402E4D50
    { 0x82E5, "_meth_82E5" }, // SP 0x140214C80, MP 0x1402DC9C0
    { 0x82E6, "_meth_82E6" }, // SP 0x140214F70, MP 0x1402DCD00
    { 0x82E7, "_meth_82E7" }, // SP 0x1402150D0, MP 0x1402DCE80
    { 0x82E8, "_meth_82E8" }, // MP 0x1402E5FA0
    { 0x82E9, "_meth_82E9" }, // MP 0x1402E6020
    { 0x82EA, "_meth_82EA" }, // MP 0x1402E60A0
    { 0x82EB, "_meth_82EB" }, // MP 0x1402E6270
    { 0x82EC, "_meth_82EC" }, // MP 0x1402E6170
    { 0x82ED, "_meth_82ED" }, // SP 0x1402168F0, MP 0x1402DE5A0
    { 0x82EE, "_meth_82EE" }, // SP 0x140215E00, MP 0x1402DD3B0
    { 0x82EF, "_meth_82EF" }, // SP 0x140215E80, MP 0x1402DD4C0
    { 0x82F0, "_meth_82F0" }, // SP 0x140217FF0, MP 0x1402DFCA0
    { 0x82F1, "_meth_82F1" }, // SP 0x1402144C0, MP 0x1402E4330
    { 0x82F2, "_meth_82F2" }, // SP 0x140214C30, MP 0x1402E4AC0
    { 0x82F3, "_meth_82F3" }, // SP 0x140214FC0, MP 0x1402E4C80
    { 0x82F4, "_meth_82F4" }, // SP 0x140214080, MP 0x1402E3E40
    { 0x82F5, "_meth_82F5" }, // SP 0x140214150, MP 0x1402E3FD0
    { 0x82F6, "_meth_82F6" }, // SP 0x1402113C0, MP 0x1402E0FA0
    { 0x82F7, "_meth_82F7" }, // SP 0x1402117B0, MP 0x1402E1530
    { 0x82F8, "_meth_82F8" }, // SP 0x140211D60, MP 0x1402E1910
    { 0x82F9, "_meth_82F9" }, // SP 0x140211F00, MP 0x1402E1C10
    { 0x82FA, "_meth_82FA" }, // SP 0x1402122B0, MP 0x1402E2070
    { 0x82FB, "_meth_82FB" }, // SP 0x140212540, MP 0x1402E24C0
    { 0x82FC, "_meth_82FC" }, // SP 0x1402129E0, MP 0x1402E2CE0
    { 0x82FD, "_meth_82FD" }, // SP 0x140212BC0, MP 0x1402E3320
    { 0x82FE, "_meth_82FE" }, // MP 0x1402E30F0
    { 0x82FF, "_meth_82FF" }, // MP 0x1402E3230
    { 0x8300, "_meth_8300" }, // SP 0x1402151D0, MP 0x1402E48E0
    { 0x8301, "_meth_8301" }, // SP 0x140215440, MP 0x1402E4A50
    { 0x8302, "_meth_8302" }, // SP 0x140216460, MP 0x1402DDC20
    { 0x8303, "_meth_8303" }, // SP 0x140216530, MP 0x1402DDE30
    { 0x8304, "_meth_8304" }, // SP 0x140216600, MP 0x1402DE000
    { 0x8305, "_meth_8305" }, // SP 0x140216CB0, MP 0x1402DF1A0
    { 0x8306, "_meth_8306" }, // SP 0x1402172B0, MP 0x1402DF230
    { 0x8307, "_meth_8307" }, // SP 0x140217330, MP 0x1402DF2B0
    { 0x8308, "_meth_8308" }, // SP 0x140216710, MP 0x1402DE210
    { 0x8309, "_meth_8309" }, // SP 0x1402153C0, MP 0x1402DD1B0
    { 0x830A, "_meth_830A" }, // SP 0x140215500, MP 0x1402DD350
    { 0x830B, "_meth_830B" }, // SP 0x140216AE0, MP 0x1402DE9E0
    { 0x830C, "_meth_830C" }, // SP 0x140216B60, MP 0x1402DEA00
    { 0x830D, "_meth_830D" }, // SP 0x140215130, MP 0x1402DC8B0
    { 0x830E, "_meth_830E" }, // SP 0x1402173C0, MP 0x1402DE6A0
    { 0x830F, "_meth_830F" }, // SP 0x1402178D0, MP 0x1402DF340
    { 0x8310, "_meth_8310" }, // SP 0x140217A70, MP 0x1402DF610
    { 0x8311, "_meth_8311" }, // SP 0x140217BE0, MP 0x1402DF820
    { 0x8312, "_meth_8312" }, // SP 0x140217E30, MP 0x1402DF9B0
    { 0x8313, "_meth_8313" }, // SP 0x140218260, MP 0x1402DFE50
    { 0x8314, "_meth_8314" }, // SP 0x140210F70, MP 0x1402E07C0
    { 0x8315, "_meth_8315" }, // SP 0x1402116F0, MP 0x1402E0E00
    { 0x8316, "_meth_8316" }, // SP 0x140211750, MP 0x1402E0F30
    { 0x8317, "_meth_8317" }, // SP 0x140212410, MP 0x1402E1D60
    { 0x8318, "_meth_8318" }, // SP 0x1402125C0, MP 0x1402E1F60
    { 0x8319, "_meth_8319" }, // SP 0x140210C20, MP 0x1402E0450
    { 0x831A, "_meth_831A" }, // SP 0x140210DD0, MP 0x1402E0610
    { 0x831B, "_meth_831B" }, // SP 0x140214DA0, MP 0x1402E4470
    { 0x831C, "_meth_831C" }, // SP 0x140215060, MP 0x1402E4700
    { 0x831D, "_meth_831D" }, // SP 0x140210940, MP 0x1402E0520
    { 0x831E, "_meth_831E" }, // SP 0x140210A00, MP 0x1402E0680
    { 0x831F, "_meth_831F" }, // SP 0x140210BC0, MP 0x1402E08C0
    { 0x8320, "_meth_8320" }, // SP 0x140210CE0, MP 0x1402E0920
    { 0x8321, "_meth_8321" }, // SP 0x1402110C0, MP 0x1402E0C90
    { 0x8322, "_meth_8322" }, // SP 0x1402111D0, MP 0x1402E0DA0
    { 0x8323, "_meth_8323" }, // SP 0x1402176D0, MP 0x1402DF550
    { 0x8324, "_meth_8324" }, // SP 0x140217830, MP 0x1402DF700
    { 0x8325, "_meth_8325" }, // SP 0x1402179C0, MP 0x1402DF940
    { 0x8326, "_meth_8326" }, // SP 0x140217AF0, MP 0x1402DFAC0
    { 0x8327, "_meth_8327" }, // SP 0x140217D90, MP 0x1402DFBE0
    { 0x8328, "_meth_8328" }, // empty
    { 0x8329, "_meth_8329" }, // SP 0x1402180F0, MP 0x1402E00C0
    { 0x832A, "_meth_832A" }, // SP 0x1402182E0, MP 0x1402E0230
    { 0x832B, "_meth_832B" }, // SP 0x140210810, MP 0x1402E0310
    { 0x832C, "_meth_832C" }, // SP 0x140213350, MP 0x1402E37B0
    { 0x832D, "_meth_832D" }, // SP 0x1402136E0, MP 0x1402E38A0
    { 0x832E, "_meth_832E" }, // SP 0x1402137B0, MP 0x1402E3A10
    { 0x832F, "_meth_832F" }, // SP 0x140213A50, MP 0x1402E3A20
    { 0x8330, "_meth_8330" }, // SP 0x140213C40, MP 0x1402E3A30
    { 0x8331, "_meth_8331" }, // SP 0x140212AD0, MP 0x1402E23C0
    { 0x8332, "_meth_8332" }, // SP 0x140212CA0, MP 0x1402E2570
    { 0x8333, "_meth_8333" }, // SP 0x140212FE0, MP 0x1402E29E0
    { 0x8334, "_meth_8334" }, // SP 0x140213440, MP 0x1402E2EA0
    { 0x8335, "_meth_8335" }, // SP 0x1402139C0, MP 0x1402E35E0
    { 0x8336, "_meth_8336" }, // SP 0x140213B20, MP 0x1402E36D0
    { 0x8337, "_meth_8337" }, // SP 0x140213B90, MP 0x1402E3980
    { 0x8338, "_meth_8338" }, // SP 0x140214250, MP 0x1402E4100
    { 0x8339, "_meth_8339" }, // SP 0x1402145A0, MP 0x1402E45C0
    { 0x833A, "_meth_833A" }, // SP 0x140214A20, MP 0x1402E4850
    { 0x833B, "_meth_833B" }, // SP 0x140214BE0, MP 0x1402E4970
    { 0x833C, "_meth_833C" }, // SP 0x140215610, MP 0x1402DCDE0
    { 0x833D, "_meth_833D" }, // SP 0x140215770, MP 0x1402DCF70
    { 0x833E, "_meth_833E" }, // SP 0x140215B00, MP 0x1402DD0F0
    { 0x833F, "_meth_833F" }, // SP 0x140215C10, MP 0x1402DD2B0
    { 0x8340, "_meth_8340" }, // SP 0x140216410, MP 0x1402DDD10
    { 0x8341, "_meth_8341" }, // SP 0x1402164C0, MP 0x1402DDED0
    { 0x8342, "_meth_8342" }, // SP 0x140216660, MP 0x1402DE1A0
    { 0x8343, "_meth_8343" }, // SP 0x140216870, MP 0x1402DE440
    { 0x8344, "_meth_8344" }, // SP 0x140210860, MP 0x1402DFFF0
    { 0x8345, "_meth_8345" }, // SP 0x140210A80, MP 0x1402E01A0
    { 0x8346, "_meth_8346" }, // SP 0x140214330
    { 0x8347, "_meth_8347" }, // SP 0x140214740
    { 0x8348, "_meth_8348" }, // SP 0x1402148A0
    { 0x8349, "_meth_8349" }, // SP 0x140214A80
    { 0x834A, "_meth_834A" }, // MP 0x14032DFF0
    { 0x834B, "_meth_834B" }, // MP 0x14032E040
    { 0x834C, "_meth_834C" }, // SP 0x140214EF0, MP 0x1402E4C70
    { 0x834D, "_meth_834D" }, // MP 0x14032BEB0
    { 0x834E, "_meth_834E" }, // SP 0x140216150, MP 0x1402DD960
    { 0x834F, "_meth_834F" }, // MP 0x14032DD30
    { 0x8350, "_meth_8350" }, // MP 0x14032DE40
    { 0x8351, "_meth_8351" }, // MP 0x140432330
    { 0x8352, "_meth_8352" }, // MP 0x140432AB0
    { 0x8353, "_meth_8353" }, // MP 0x140432930
    { 0x8354, "_meth_8354" }, // MP 0x140432610
    { 0x8355, "_meth_8355" }, // MP 0x1404327B0
    { 0x8356, "_meth_8356" }, // MP 0x1404308A0
    { 0x8357, "_meth_8357" }, // MP 0x140432550
    { 0x8358, "_meth_8358" }, // MP 0x140430820
    { 0x8359, "_meth_8359" }, // MP 0x1404320F0
    { 0x835A, "_meth_835A" }, // MP 0x140431010
    { 0x835B, "_meth_835B" }, // MP 0x140431140
    { 0x835C, "_meth_835C" }, // MP 0x140431240
    { 0x835D, "_meth_835D" }, // MP 0x1404311C0
    { 0x835E, "_meth_835E" }, // empty
    { 0x835F, "_meth_835F" }, // MP 0x140431380
    { 0x8360, "_meth_8360" }, // MP 0x1404318D0
    { 0x8361, "_meth_8361" }, // MP 0x140430920
    { 0x8362, "_meth_8362" }, // MP 0x140431670
    { 0x8363, "_meth_8363" }, // empty
    { 0x8364, "_meth_8364" }, // MP 0x140431970
    { 0x8365, "_meth_8365" }, // MP 0x1404313A0
    { 0x8366, "_meth_8366" }, // MP 0x140430F90
    { 0x8367, "_meth_8367" }, // MP 0x140432B80
    { 0x8368, "_meth_8368" }, // empty
    { 0x8369, "_meth_8369" }, // MP 0x1404324C0
    { 0x836A, "_meth_836A" }, // MP 0x140432200
    { 0x836B, "_meth_836B" }, // MP 0x140430AB0
    { 0x836C, "_meth_836C" }, // MP 0x1404312C0
    { 0x836D, "_meth_836D" }, // MP 0x1404314A0
    { 0x836E, "_meth_836E" }, // MP 0x140431EA0
    { 0x836F, "_meth_836F" }, // MP 0x1404306B0
    { 0x8370, "_meth_8370" }, // MP 0x140430DA0
    { 0x8371, "_meth_8371" }, // MP 0x140431AC0
    { 0x8372, "_meth_8372" }, // empty
    { 0x8373, "_meth_8373" }, // MP 0x140430BF0
    { 0x8374, "_meth_8374" }, // MP 0x140432170
    { 0x8375, "_meth_8375" }, // MP 0x140432060
    { 0x8376, "_meth_8376" }, // MP 0x1404310B0
    { 0x8377, "_meth_8377" }, // MP 0x140430C70
    { 0x8378, "_meth_8378" }, // empty
    { 0x8379, "_meth_8379" }, // MP 0x1404323F0
    { 0x837A, "_meth_837A" }, // MP 0x140432290
    { 0x837B, "_meth_837B" }, // MP 0x140430B40
    { 0x837C, "_meth_837C" }, // MP 0x140430E60
    { 0x837D, "_meth_837D" }, // MP 0x140431420
    { 0x837E, "_meth_837E" }, // MP 0x140431F60
    { 0x837F, "_meth_837F" }, // MP 0x140430790
    { 0x8380, "_meth_8380" }, // MP 0x140431C70
    { 0x8381, "_meth_8381" }, // MP 0x1402DE550
    { 0x8382, "_meth_8382" }, // MP 0x14032AEF0
    { 0x8383, "_meth_8383" }, // MP 0x1403299E0
    { 0x8384, "_meth_8384" }, // MP 0x14031BD40
    { 0x8385, "_meth_8385" }, // MP 0x14032AB40
    { 0x8386, "_meth_8386" }, // MP 0x1402DE580
    { 0x8387, "_meth_8387" }, // SP 0x140216B00, MP 0x1402DE4F0
    { 0x8388, "_meth_8388" }, // MP 0x14032BDF0
    { 0x8389, "_meth_8389" }, // empty
    { 0x838A, "_meth_838A" }, // MP 0x140404FA0
    { 0x838B, "_meth_838B" }, // MP 0x140404640
    { 0x838C, "_meth_838C" }, // MP 0x140404E80
    { 0x838D, "_meth_838D" }, // MP 0x140404040
    { 0x838E, "_meth_838E" }, // MP 0x140403E60
    { 0x838F, "_meth_838F" }, // MP 0x140406A80
    { 0x8390, "_meth_8390" }, // MP 0x140406090
    { 0x8391, "_meth_8391" }, // MP 0x140405610
    { 0x8392, "_meth_8392" }, // MP 0x140406000
    { 0x8393, "_meth_8393" }, // MP 0x140405F70
    { 0x8394, "_meth_8394" }, // MP 0x1404061B0
    { 0x8395, "_meth_8395" }, // MP 0x140405E10
    { 0x8396, "_meth_8396" }, // MP 0x140406490
    { 0x8397, "_meth_8397" }, // MP 0x140405CF0
    { 0x8398, "_meth_8398" }, // MP 0x1404066E0
    { 0x8399, "_meth_8399" }, // MP 0x140405ED0
    { 0x839A, "_meth_839A" }, // MP 0x1404062C0
    { 0x839B, "_meth_839B" }, // MP 0x140405730
    { 0x839C, "_meth_839C" }, // MP 0x140405290
    { 0x839D, "_meth_839D" }, // MP 0x1404067A0
    { 0x839E, "_meth_839E" }, // MP 0x140405580
    { 0x839F, "_meth_839F" }, // MP 0x140405470
    { 0x83A0, "_meth_83A0" }, // MP 0x140406A00
    { 0x83A1, "_meth_83A1" }, // MP 0x140405360
    { 0x83A2, "_meth_83A2" }, // MP 0x140405BE0
    { 0x83A3, "_meth_83A3" }, // SP 0x14021EB90, MP 0x1402EF370
    { 0x83A4, "_meth_83A4" }, // SP 0x14021EC40, MP 0x1402EF420
    { 0x83A5, "_meth_83A5" }, // SP 0x14021ECB0, MP 0x1402EF480
    { 0x83A6, "_meth_83A6" }, // SP 0x14021ED20, MP 0x1402EF4E0
    { 0x83A7, "_meth_83A7" }, // SP 0x14025CD90
    { 0x83A8, "_meth_83A8" }, // SP 0x1402156E0, MP 0x1402DD560
    { 0x83A9, "_meth_83A9" }, // SP 0x140215860, MP 0x1402DD590
    { 0x83AA, "_meth_83AA" }, // SP 0x140219A90
    { 0x83AB, "_meth_83AB" }, // SP 0x14025D090
    { 0x83AC, "_meth_83AC" }, // SP 0x14025D100
    { 0x83AD, "_meth_83AD" }, // SP 0x140219940
    { 0x83AE, "_meth_83AE" }, // SP 0x140219A20
    { 0x83AF, "_meth_83AF" }, // SP 0x1402199B0
    { 0x83B0, "_meth_83B0" }, // empty
    { 0x83B1, "_meth_83B1" }, // empty
    { 0x83B2, "_meth_83B2" }, // SP 0x140215550, MP 0x1402E4B80
    { 0x83B3, "_meth_83B3" }, // SP 0x140214020, MP 0x1402E4090
    { 0x83B4, "_meth_83B4" }, // SP 0x1402141E0, MP 0x1402E42B0
    { 0x83B5, "_meth_83B5" }, // SP 0x1404155F0, MP 0x140529A10
    { 0x83B6, "_meth_83B6" }, // SP 0x140415600, MP 0x140529A20
    { 0x83B7, "_meth_83B7" }, // MP 0x14032D4B0
    { 0x83B8, "_meth_83B8" }, // SP 0x140245EC0, MP 0x14030F7E0
    { 0x83B9, "_meth_83B9" }, // SP 0x140242A20, MP 0x14030B590
    { 0x83BA, "_meth_83BA" }, // SP 0x140242DC0, MP 0x14030BAA0
    { 0x83BB, "_meth_83BB" }, // SP 0x140216060, MP 0x1402DD820
    { 0x83BC, "_meth_83BC" }, // SP 0x140417980, MP 0x14052BE00
    { 0x83BD, "_meth_83BD" }, // SP 0x140417A30, MP 0x14052BEB0
    { 0x83BE, "_meth_83BE" }, // SP 0x140417AB0, MP 0x14052BF30
    { 0x83BF, "_meth_83BF" }, // SP 0x14023B560
    { 0x83C0, "_meth_83C0" }, // SP 0x140210D40, MP 0x1402E0580
    { 0x83C1, "_meth_83C1" }, // SP 0x140210E90, MP 0x1402E06E0
    { 0x83C2, "_meth_83C2" }, // SP 0x140211120, MP 0x1402E0980
    { 0x83C3, "_meth_83C3" }, // SP 0x1402650D0, MP 0x140333C10
    { 0x83C4, "_meth_83C4" }, // SP 0x14028A260, MP 0x140043710
    { 0x83C5, "_meth_83C5" }, // SP 0x140417070, MP 0x14052B420
    { 0x83C6, "_meth_83C6" }, // MP 0x1402DDD70
    { 0x83C7, "_meth_83C7" }, // SP 0x14023B4F0
    { 0x83C8, "_meth_83C8" }, // SP 0x1401FB770
    { 0x83C9, "_meth_83C9" }, // SP 0x1401FB8A0
    { 0x83CA, "_meth_83CA" }, // SP 0x1401FBBB0
    { 0x83CB, "_meth_83CB" }, // SP 0x1401FBD00
    { 0x83CC, "_meth_83CC" }, // SP 0x1401FBF30
    { 0x83CD, "_meth_83CD" }, // SP 0x1401FBEC0
    { 0x83CE, "_meth_83CE" }, // SP 0x1401FC090
    { 0x83CF, "_meth_83CF" }, // SP 0x1401FC0F0
    { 0x83D0, "_meth_83D0" }, // MP 0x140044400
    { 0x83D1, "_meth_83D1" }, // MP 0x140043EE0
    { 0x83D2, "_meth_83D2" }, // MP 0x140044470
    { 0x83D3, "_meth_83D3" }, // MP 0x140044010
    { 0x83D4, "_meth_83D4" }, // MP 0x1400441C0
    { 0x83D5, "_meth_83D5" }, // MP 0x1400440A0
    { 0x83D6, "_meth_83D6" }, // MP 0x140044100
    { 0x83D7, "_meth_83D7" }, // SP 0x14025A000
    { 0x83D8, "_meth_83D8" }, // SP 0x1402154A0, MP 0x1402DCC90
    { 0x83D9, "_meth_83D9" }, // SP 0x1402519A0
    { 0x83DA, "_meth_83DA" }, // SP 0x1401FA190
    { 0x83DB, "_meth_83DB" }, // MP 0x14031AEF0
    { 0x83DC, "_meth_83DC" }, // empty
    { 0x83DD, "_meth_83DD" }, // empty
    { 0x83DE, "_meth_83DE" }, // SP 0x140215F80, MP 0x1402DD780
    { 0x83DF, "_meth_83DF" }, // SP 0x1402647C0, MP 0x1403331E0
    { 0x83E0, "_meth_83E0" }, // MP 0x1404056A0
    { 0x83E1, "_meth_83E1" }, // MP 0x140405A50
    { 0x83E2, "_meth_83E2" }, // MP 0x140316940
    { 0x83E3, "_meth_83E3" }, // MP 0x14032D710
    { 0x83E4, "_meth_83E4" }, // SP 0x14024CD60, MP 0x14031B0D0
    { 0x83E5, "_meth_83E5" }, // SP 0x14024A200, MP 0x140311B20
    { 0x83E6, "_meth_83E6" }, // SP 0x14024AB80, MP 0x140312A70
    { 0x83E7, "_meth_83E7" }, // MP 0x1402EE870
    { 0x83E8, "_meth_83E8" }, // SP 0x14025C3C0
    { 0x83E9, "_meth_83E9" }, // SP 0x14025CBE0
    { 0x83EA, "_meth_83EA" }, // SP 0x140217CE0, MP 0x1402DFDA0
    { 0x83EB, "_meth_83EB" }, // SP 0x14021E100, MP 0x1402EEA40
    { 0x83EC, "_meth_83EC" }, // SP 0x14024DB10, MP 0x1403185B0
    { 0x83ED, "_meth_83ED" }, // SP 0x14024E830, MP 0x140319350
    { 0x83EE, "_meth_83EE" }, // MP 0x1402DD660
    { 0x83EF, "_meth_83EF" }, // SP 0x140259E40
    { 0x83F0, "_meth_83F0" }, // empty
    { 0x83F1, "_meth_83F1" }, // SP 0x140249730, MP 0x140313D20
    { 0x83F2, "_meth_83F2" }, // SP 0x140247DC0, MP 0x1403131D0
    { 0x83F3, "_meth_83F3" }, // SP 0x1402504D0, MP 0x14031C1F0
    { 0x83F4, "_meth_83F4" }, // SP 0x140219120
    { 0x83F5, "_meth_83F5" }, // SP 0x140219180
    { 0x83F6, "_meth_83F6" }, // SP 0x14024D350, MP 0x14031B8D0
    { 0x83F7, "_meth_83F7" }, // SP 0x14024DA40, MP 0x14031BE10
    { 0x83F8, "_meth_83F8" }, // MP 0x140316A60
    { 0x83F9, "_meth_83F9" }, // SP 0x140415460, MP 0x14052B750
    { 0x83FA, "_meth_83FA" }, // SP 0x1402443F0, MP 0x14030B9F0
    { 0x83FB, "_meth_83FB" }, // SP 0x140244F00, MP 0x14030BD20
    { 0x83FC, "_meth_83FC" }, // SP 0x140245540, MP 0x14030C510
    { 0x83FD, "_meth_83FD" }, // SP 0x140245610, MP 0x14030C680
    { 0x83FE, "_meth_83FE" }, // SP 0x14025F060
    { 0x83FF, "_meth_83FF" }, // SP 0x1401FB850
    { 0x8400, "_meth_8400" }, // SP 0x1402408E0, MP 0x140321F90
    { 0x8401, "_meth_8401" }, // SP 0x140240620
    { 0x8402, "_meth_8402" }, // SP 0x1401FA470
    { 0x8403, "_meth_8403" }, // MP 0x1404309B0
    { 0x8404, "_meth_8404" }, // SP 0x140210AE0
    { 0x8405, "_meth_8405" }, // SP 0x14021A5C0
    { 0x8406, "_meth_8406" }, // SP 0x140240860
    { 0x8407, "_meth_8407" }, // SP 0x140240B60
    { 0x8408, "_meth_8408" }, // SP 0x140243680
    { 0x8409, "_meth_8409" }, // MP 0x140328200
    { 0x840A, "_meth_840A" }, // SP 0x140219EA0
    { 0x840B, "_meth_840B" }, // SP 0x140219EF0
    { 0x840C, "_meth_840C" }, // MP 0x1402E66D0
    { 0x840D, "_meth_840D" }, // MP 0x1402E66E0
    { 0x840E, "_meth_840E" }, // MP 0x1402E66F0
    { 0x840F, "_meth_840F" }, // SP 0x14025B8A0
    { 0x8410, "_meth_8410" }, // SP 0x14025A4D0
    { 0x8411, "_meth_8411" }, // SP 0x14025A510
    { 0x8412, "_meth_8412" }, // SP 0x1402655E0, MP 0x140334160
    { 0x8413, "_meth_8413" }, // SP 0x140265690, MP 0x140334210
    { 0x8414, "_meth_8414" }, // SP 0x140265740, MP 0x1403342C0
    { 0x8415, "_meth_8415" }, // SP 0x1402657D0, MP 0x140334350
    { 0x8416, "_meth_8416" }, // SP 0x140265890, MP 0x140334410
    { 0x8417, "_meth_8417" }, // SP 0x140265920, MP 0x1403344A0
    { 0x8418, "_meth_8418" }, // MP 0x140319270
    { 0x8419, "_meth_8419" }, // MP 0x1403193D0
    { 0x841A, "_meth_841A" }, // MP 0x14032E6E0
    { 0x841B, "_meth_841B" }, // MP 0x14032E700
    { 0x841C, "_meth_841C" }, // MP 0x1402E6700
    { 0x841D, "_meth_841D" }, // MP 0x140316950
    { 0x841E, "_meth_841E" }, // MP 0x140316D50
    { 0x841F, "_meth_841F" }, // MP 0x14032E7B0
    { 0x8420, "_meth_8420" }, // MP 0x140321C50
    { 0x8421, "_meth_8421" }, // MP 0x140322190
    { 0x8422, "_meth_8422" }, // MP 0x14030B3C0
    { 0x8423, "_meth_8423" }, // MP 0x14030B800
    { 0x8424, "_meth_8424" }, // SP 0x1402424C0, MP 0x140322600
    { 0x8425, "_meth_8425" }, // MP 0x1402E6900
    { 0x8426, "_meth_8426" }, // SP 0x140248A10, MP 0x140313420
    { 0x8427, "_meth_8427" }, // SP 0x140248EF0, MP 0x1403136F0
    { 0x8428, "_meth_8428" }, // MP 0x1404054F0
    { 0x8429, "_meth_8429" }, // SP 0x140264670
    { 0x842A, "_meth_842A" }, // SP 0x140264840
    { 0x842B, "_meth_842B" }, // SP 0x1402648E0
    { 0x842C, "_meth_842C" }, // MP 0x14032D980
    { 0x842D, "_meth_842D" }, // SP 0x140260510
    { 0x842E, "_meth_842E" }, // MP 0x14032A3B0
    { 0x842F, "_meth_842F" }, // MP 0x14032AFD0
    { 0x8430, "_meth_8430" }, // MP 0x1403283A0
    { 0x8431, "_meth_8431" }, // MP 0x1402E5E50
    { 0x8432, "_meth_8432" }, // MP 0x1402E87A0
    { 0x8433, "_meth_8433" }, // SP 0x140217960, MP 0x1402DF8E0
    { 0x8434, "_meth_8434" }, // SP 0x140217A10, MP 0x1402DFA60
    { 0x8435, "_meth_8435" }, // SP 0x140219B00
    { 0x8436, "_meth_8436" }, // SP 0x14024E610, MP 0x1403190C0
    { 0x8437, "_meth_8437" }, // MP 0x140431DA0
    { 0x8438, "_meth_8438" }, // MP 0x14032FE50
    { 0x8439, "_meth_8439" }, // SP 0x140213F30, MP 0x1402E3D80
    { 0x843A, "_meth_843A" }, // MP 0x1402E6BC0
    { 0x843B, "_meth_843B" }, // MP 0x1402E6BB0
    { 0x843C, "_meth_843C" }, // SP 0x14024D160, MP 0x14031B6F0
    { 0x843D, "_meth_843D" }, // MP 0x1403291E0
    { 0x843E, "_meth_843E" }, // SP 0x1401FC160
    { 0x843F, "_meth_843F" }, // SP 0x1401FC200
    { 0x8440, "_meth_8440" }, // SP 0x140212390, MP 0x1402E1B80
    { 0x8441, "_meth_8441" }, // SP 0x1401FC630
    { 0x8442, "_meth_8442" }, // SP 0x140247D40, MP 0x140310FB0
    { 0x8443, "_meth_8443" }, // MP 0x1402DDF40
    { 0x8444, "_meth_8444" }, // SP 0x140413DA0, MP 0x140528300
    { 0x8445, "_meth_8445" }, // SP 0x140417B70, MP 0x14052BFF0
    { 0x8446, "_meth_8446" }, // SP 0x14024D420, MP 0x140317AF0
    { 0x8447, "_meth_8447" }, // SP 0x1402126D0, MP 0x1402E2710
    { 0x8448, "_meth_8448" }, // SP 0x14025D360
    { 0x8449, "_meth_8449" }, // SP 0x14025D3A0
    { 0x844A, "_meth_844A" }, // SP 0x14024EF50, MP 0x140319B60
    { 0x844B, "_meth_844B" }, // MP 0x14030C040
    { 0x844C, "_meth_844C" }, // MP 0x14030C190
    { 0x844D, "_meth_844D" }, // SP 0x1402152B0, MP 0x1402DC8F0
    { 0x844E, "_meth_844E" }, // SP 0x14023F230, MP 0x14031EDF0
    { 0x844F, "_meth_844F" }, // SP 0x14023FC50, MP 0x14031FD30
    { 0x8450, "_meth_8450" }, // SP 0x140413420, MP 0x14052C170
    { 0x8451, "_meth_8451" }, // SP 0x140413440, MP 0x14052C190
    { 0x8452, "_meth_8452" }, // SP 0x140413460, MP 0x14052C1B0
    { 0x8453, "_meth_8453" }, // SP 0x140413480, MP 0x14052C1D0
    { 0x8454, "_meth_8454" }, // SP 0x140261210
    { 0x8455, "_meth_8455" }, // SP 0x140261250
    { 0x8456, "_meth_8456" }, // SP 0x140417C30, MP 0x14052C0B0
    { 0x8457, "_meth_8457" }, // SP 0x1402166C0, MP 0x1402DE140
    { 0x8458, "_meth_8458" }, // SP 0x1402152F0
    { 0x8459, "_meth_8459" }, // SP 0x1402616F0
    { 0x845A, "_meth_845A" }, // empty
    { 0x845B, "_meth_845B" }, // empty
    { 0x845C, "_meth_845C" }, // SP 0x140247440, MP 0x14030F1E0
    { 0x845D, "_meth_845D" }, // SP 0x1402127F0, MP 0x1402E2160
    { 0x845E, "_meth_845E" }, // MP 0x140318810
    { 0x845F, "_meth_845F" }, // MP 0x140318F70
    { 0x8460, "_meth_8460" }, // empty
    { 0x8461, "_meth_8461" }, // SP 0x14024E9D0, MP 0x140319600
    { 0x8462, "_meth_8462" }, // MP 0x140328E70
    { 0x8463, "_meth_8463" }, // MP 0x140328EC0
    { 0x8464, "_meth_8464" }, // MP 0x1402FB470
    { 0x8465, "_meth_8465" }, // SP 0x140213F70, MP 0x1402E3DD0
    { 0x8466, "_meth_8466" }, // empty
    { 0x8467, "_meth_8467" }, // SP 0x140250AC0, MP 0x14031C920
    { 0x8468, "_meth_8468" }, // SP 0x140216230
    { 0x8469, "_meth_8469" }, // MP 0x1402E02F0
    { 0x846A, "_meth_846A" }, // SP 0x140265D80, MP 0x140334E90
    { 0x846B, "_meth_846B" }, // SP 0x140265F30, MP 0x140335040
    { 0x846C, "_meth_846C" }, // SP 0x14024F690
    { 0x846D, "_meth_846D" }, // SP 0x14024FAB0
    { 0x846E, "_meth_846E" }, // SP 0x140250060
    { 0x846F, "_meth_846F" }, // SP 0x140250270
    { 0x8470, "_meth_8470" }, // SP 0x140250A20
    { 0x8471, "_meth_8471" }, // SP 0x1402155C0
    { 0x8472, "_meth_8472" }, // SP 0x14025CE20
    { 0x8473, "_meth_8473" }, // SP 0x140413500, MP 0x14052C250
    { 0x8474, "_meth_8474" }, // SP 0x140413540, MP 0x14052C290
    { 0x8475, "_meth_8475" }, // SP 0x1404135A0, MP 0x14052C2F0
    { 0x8476, "_meth_8476" }, // SP 0x1404135F0, MP 0x14052C340
    { 0x8477, "_meth_8477" }, // SP 0x140413610, MP 0x14052C360
    { 0x8478, "_meth_8478" }, // SP 0x140252200, MP 0x14031C170
    { 0x8479, "_meth_8479" }, // SP 0x140252430, MP 0x14031C590
    { 0x847A, "_meth_847A" }, // SP 0x140210B00, MP 0x1402E0390
    { 0x847B, "_meth_847B" }, // SP 0x14025CEA0
    { 0x847C, "_meth_847C" }, // SP 0x14025D040
    { 0x847D, "_meth_847D" }, // MP 0x1402E41C0
    { 0x847E, "_meth_847E" }, // MP 0x1402E43B0
    { 0x847F, "_meth_847F" }, // SP 0x140417120, MP 0x14052B4D0
    { 0x8480, "_meth_8480" }, // SP 0x1404171A0, MP 0x14052B550
    { 0x8481, "_meth_8481" }, // SP 0x140216950, MP 0x1402DE630
    { 0x8482, "_meth_8482" }, // SP 0x1402169A0, MP 0x1402DEB60
    { 0x8483, "_meth_8483" }, // SP 0x1402462A0, MP 0x14030FBD0
    { 0x8484, "_meth_8484" }, // SP 0x140252730
    { 0x8485, "_meth_8485" }, // SP 0x140215D90, MP 0x1402DCEF0
    { 0x8486, "_meth_8486" }, // SP 0x140215BA0, MP 0x1402DCD60
    { 0x8487, "_meth_8487" }, // MP 0x1404045E0
    { 0x8488, "_meth_8488" }, // SP 0x1404153F0, MP 0x1405297E0
    { 0x8489, "_meth_8489" }, // SP 0x1404134B0, MP 0x14052C200
    { 0x848A, "_meth_848A" }, // MP 0x140403EF0
    { 0x848B, "_meth_848B" }, // MP 0x140334A40
    { 0x848C, "_meth_848C" }, // SP 0x140264710
    { 0x848D, "_meth_848D" }, // SP 0x140215A90, MP 0x1402DCC10
    { 0x848E, "_meth_848E" }, // SP 0x140415470, MP 0x140529860
    { 0x848F, "_meth_848F" }, // MP 0x1405297F0
    { 0x8490, "_meth_8490" }, // SP 0x140211290, MP 0x1402E0A90
    { 0x8491, "_meth_8491" }, // SP 0x140211570, MP 0x1402E0BC0
    { 0x8492, "_meth_8492" }, // SP 0x140211640, MP 0x1402E0CF0
    { 0x8493, "_meth_8493" }, // SP 0x140219490
    { 0x8494, "_meth_8494" }, // SP 0x140252620, MP 0x14031C840
    { 0x8495, "_meth_8495" }, // MP 0x140329C80
    { 0x8496, "finishentitydamage" },
    { 0x8497, "_meth_8497" }, // SP 0x140261570
    { 0x8498, "_meth_8498" }, // SP 0x140261690
    { 0x8499, "_meth_8499" }, // SP 0x14021A310
    { 0x849A, "_meth_849A" }, // MP 0x14032E850
    { 0x849B, "_meth_849B" }, // MP 0x140328DD0
    { 0x849C, "_meth_849C" }, // SP 0x140213960, MP 0x1402E3680
    { 0x849D, "_meth_849D" }, // SP 0x140213D30, MP 0x1402E3BF0
    { 0x849E, "_meth_849E" }, // SP 0x1402157F0, MP 0x1402DCB40
    { 0x849F, "_meth_849F" }, // MP 0x14032E8C0
    { 0x84A0, "_meth_84A0" }, // MP 0x14032EAB0
    { 0x84A1, "_meth_84A1" }, // MP 0x14032EC40
    { 0x84A2, "_meth_84A2" }, // MP 0x14032EF70
    { 0x84A3, "_meth_84A3" }, // MP 0x14032F290
    { 0x84A4, "_meth_84A4" }, // MP 0x14032F960
    { 0x84A5, "_meth_84A5" }, // MP 0x14032F4C0
    { 0x84A6, "_meth_84A6" }, // MP 0x140327B20
    { 0x84A7, "_meth_84A7" }, // MP 0x140327F80
    { 0x84A8, "_meth_84A8" }, // MP 0x14032FEF0
    { 0x84A9, "_meth_84A9" }, // SP 0x140249520, MP 0x140312340
    { 0x84AA, "_meth_84AA" }, // SP 0x140249910, MP 0x140312C40
    { 0x84AB, "_meth_84AB" }, // SP 0x140249CE0, MP 0x140312E80
    { 0x84AC, "_meth_84AC" }, // SP 0x14024A4A0, MP 0x140313860
    { 0x84AD, "_meth_84AD" }, // SP 0x140416070, MP 0x14052A560
    { 0x84AE, "_meth_84AE" }, // SP 0x140241420, MP 0x140321790
    { 0x84AF, "_meth_84AF" }, // SP 0x140241920, MP 0x140321A50
    { 0x84B0, "_meth_84B0" }, // SP 0x1402162A0, MP 0x1402DDA50
    { 0x84B1, "_meth_84B1" }, // SP 0x1404167F0, MP 0x14052AC50
    { 0x84B2, "_meth_84B2" }, // SP 0x1404168F0, MP 0x14052AD50
    { 0x84B3, "_meth_84B3" }, // MP 0x1402E6C20
    { 0x84B4, "_meth_84B4" }, // MP 0x140310840
    { 0x84B5, "_meth_84B5" }, // SP 0x140252CA0, MP 0x14031CBF0
    { 0x84B6, "_meth_84B6" }, // SP 0x140252F80, MP 0x14031CF20
    { 0x84B7, "_meth_84B7" }, // SP 0x140253980, MP 0x14031D2F0
    { 0x84B8, "_meth_84B8" }, // SP 0x140253B60, MP 0x14031D300
    { 0x84B9, "_meth_84B9" }, // MP 0x1403104C0
    { 0x84BA, "_meth_84BA" }, // MP 0x140317430
    { 0x84BB, "_meth_84BB" }, // SP 0x1404159E0, MP 0x140529E00
    { 0x84BC, "_meth_84BC" }, // SP 0x14024A130, MP 0x140313510
    { 0x84BD, "_meth_84BD" }, // MP 0x140334BE0
    { 0x84BE, "_meth_84BE" }, // MP 0x1403204E0
    { 0x84BF, "_meth_84BF" }, // SP 0x140210E30, MP 0x1402E0A30
    { 0x84C0, "_meth_84C0" }, // SP 0x140211060, MP 0x1402E0B60
    { 0x84C1, "_meth_84C1" }, // MP 0x1402E6CA0
    { 0x84C2, "_meth_84C2" }, // MP 0x1402E7060
    { 0x84C3, "_meth_84C3" }, // SP 0x140211C20, MP 0x1402E13F0
    { 0x84C4, "_meth_84C4" }, // SP 0x140212040, MP 0x1402E17A0
    { 0x84C5, "_meth_84C5" }, // MP 0x1403290C0
    { 0x84C6, "_meth_84C6" }, // SP 0x140248BE0, MP 0x140312710
    { 0x84C7, "_meth_84C7" }, // SP 0x140413650, MP 0x14052C3A0
    { 0x84C8, "_meth_84C8" }, // MP 0x140406E30
    { 0x84C9, "_meth_84C9" }, // MP 0x140406A70
    { 0x84CA, "_meth_84CA" }, // SP 0x140214970, MP 0x1402E46B0
    { 0x84CB, "_meth_84CB" }, // SP 0x1402146F0
    { 0x84CC, "_meth_84CC" }, // SP 0x1402147E0
    { 0x84CD, "_meth_84CD" }, // SP 0x140415170, MP 0x140529560
    { 0x84CE, "_meth_84CE" }, // SP 0x140415200, MP 0x140529650
    { 0x84CF, "_meth_84CF" }, // SP 0x14024D040, MP 0x140317580
    { 0x84D0, "_meth_84D0" }, // SP 0x14024B7E0, MP 0x1403160C0
    { 0x84D1, "_meth_84D1" }, // SP 0x14024B9E0, MP 0x140316540
    { 0x84D2, "_meth_84D2" }, // SP 0x14024CE00, MP 0x1403172B0
    { 0x84D3, "_meth_84D3" }, // MP 0x1402E8A20
    { 0x84D4, "_meth_84D4" }, // SP 0x140413670, MP 0x14052C3C0
    { 0x84D5, "_meth_84D5" }, // SP 0x140249F30, MP 0x1403143D0
    { 0x84D6, "_meth_84D6" }, // SP 0x140249FC0, MP 0x1403145C0
    { 0x84D7, "_meth_84D7" }, // SP 0x140247490, MP 0x1403122F0
    { 0x84D8, "_meth_84D8" }, // SP 0x1402475C0, MP 0x1403123D0
    { 0x84D9, "_meth_84D9" }, // SP 0x140247740, MP 0x140312520
    { 0x84DA, "_meth_84DA" }, // SP 0x1402478B0, MP 0x140312BA0
    { 0x84DB, "_meth_84DB" }, // SP 0x140247900, MP 0x140312BF0
    { 0x84DC, "_meth_84DC" }, // SP 0x140247B10, MP 0x140312CB0
    { 0x84DD, "_meth_84DD" }, // SP 0x140247C60, MP 0x140312DF0
    { 0x84DE, "_meth_84DE" }, // SP 0x140247CE0, MP 0x140312FF0
    { 0x84DF, "_meth_84DF" }, // SP 0x14028A150
    { 0x84E0, "_meth_84E0" }, // SP 0x140213EE0, MP 0x1402E3D20
    { 0x84E1, "_meth_84E1" }, // SP 0x1402659E0, MP 0x140334560
    { 0x84E2, "_meth_84E2" }, // MP 0x14031B9E0
    { 0x84E3, "_meth_84E3" }, // SP 0x1401F92C0
    { 0x84E4, "_meth_84E4" }, // SP 0x140416CC0
    { 0x84E5, "_meth_84E5" }, // SP 0x1401F9310
    { 0x84E6, "_meth_84E6" }, // SP 0x1401F9380
    { 0x84E7, "_meth_84E7" }, // SP 0x140250FA0, MP 0x14031E3C0
    { 0x84E8, "_meth_84E8" }, // SP 0x14021F100, MP 0x1402EF8A0
    { 0x84E9, "_meth_84E9" }, // SP 0x1404136B0, MP 0x14052C400
    { 0x84EA, "_meth_84EA" }, // MP 0x14031A1A0
    { 0x84EB, "_meth_84EB" }, // SP 0x140211E70, MP 0x1402E1700
    { 0x84EC, "_meth_84EC" }, // SP 0x14023F470, MP 0x14031F000
    { 0x84ED, "_meth_84ED" }, // SP 0x14025D190
    { 0x84EE, "_meth_84EE" }, // MP 0x1400439D0
    { 0x84EF, "_meth_84EF" }, // MP 0x140317940
    { 0x84F0, "_meth_84F0" }, // empty
    { 0x84F1, "_meth_84F1" }, // SP 0x140211230, MP 0x1402E0E70
    { 0x84F2, "_meth_84F2" }, // SP 0x140211360, MP 0x1402E0F20
    { 0x84F3, "_meth_84F3" }, // SP 0x14023B610
    { 0x84F4, "_meth_84F4" }, // SP 0x140243E30, MP 0x14030CD90
    { 0x84F5, "_meth_84F5" }, // SP 0x14024DF20, MP 0x14031C2A0
    { 0x84F6, "_meth_84F6" }, // SP 0x14023FDF0, MP 0x14030B1C0
    { 0x84F7, "_meth_84F7" }, // SP 0x140240FD0, MP 0x140322450
    { 0x84F8, "_meth_84F8" }, // SP 0x1402453B0, MP 0x14030C2F0
    { 0x84F9, "_meth_84F9" }, // SP 0x140414810, MP 0x140528BC0
    { 0x84FA, "_meth_84FA" }, // SP 0x140414920, MP 0x140528CF0
    { 0x84FB, "_meth_84FB" }, // SP 0x140251B50, MP 0x14031FB80
    { 0x84FC, "_meth_84FC" }, // SP 0x140252320, MP 0x140320180
    { 0x84FD, "_meth_84FD" }, // SP 0x140251270, MP 0x14031E7D0
    { 0x84FE, "_meth_84FE" }, // MP 0x14031EAB0
    { 0x84FF, "_meth_84FF" }, // MP 0x14031EBF0
    { 0x8500, "_meth_8500" }, // SP 0x1402516B0, MP 0x14031EDE0
    { 0x8501, "_meth_8501" }, // MP 0x14031EEB0
    { 0x8502, "_meth_8502" }, // MP 0x14031F190
    { 0x8503, "_meth_8503" }, // MP 0x14031F830
    { 0x8504, "_meth_8504" }, // SP 0x14024BF00, MP 0x140319DE0
    { 0x8505, "_meth_8505" }, // SP 0x14024FB30, MP 0x140319580
    { 0x8506, "_meth_8506" }, // MP 0x1402E8800
    { 0x8507, "_meth_8507" }, // MP 0x140329180
    { 0x8508, "_meth_8508" }, // MP 0x140329240
    { 0x8509, "_meth_8509" }, // SP 0x14024F410, MP 0x140318610
    { 0x850A, "_meth_850A" }, // SP 0x14024E920, MP 0x140317760
    { 0x850B, "_meth_850B" }, // MP 0x14032E9A0
    { 0x850C, "_meth_850C" }, // SP 0x140252E00, MP 0x140320830
    { 0x850D, "_meth_850D" }, // MP 0x140329BC0
    { 0x850E, "_meth_850E" }, // MP 0x14032E370
    { 0x850F, "_meth_850F" }, // MP 0x14032C510
    { 0x8510, "_meth_8510" }, // MP 0x14032AC40
    { 0x8511, "_meth_8511" }, // MP 0x1402E6A80
    { 0x8512, "_meth_8512" }, // SP 0x140261130
    { 0x8513, "_meth_8513" }, // SP 0x140211970, MP 0x1402E0E80
    { 0x8514, "_meth_8514" }, // SP 0x14021EAB0, MP 0x1402EF290
    { 0x8515, "_meth_8515" }, // MP 0x140328D20
    { 0x8516, "_meth_8516" }, // MP 0x14032DBF0
    { 0x8517, "_meth_8517" }, // MP 0x14032DCE0
    { 0x8518, "_meth_8518" }, // SP 0x1402472A0, MP 0x140312210
    { 0x8519, "_meth_8519" }, // SP 0x1402473E0, MP 0x140312280
    { 0x851A, "_meth_851A" }, // SP 0x140243700, MP 0x140321660
    { 0x851B, "_meth_851B" }, // SP 0x140214130, MP 0x1402E3EC0
    { 0x851C, "_meth_851C" }, // SP 0x140250160, MP 0x140319690
    { 0x851D, "_meth_851D" }, // SP 0x1404136E0, MP 0x140527C40
    { 0x851E, "_meth_851E" }, // SP 0x140413700, MP 0x140527C60
    { 0x851F, "_meth_851F" }, // SP 0x1402142D0, MP 0x1402E4400
    { 0x8520, "_meth_8520" }, // SP 0x140214540, MP 0x1402E4640
    { 0x8521, "_meth_8521" }, // SP 0x140242BF0, MP 0x140320AB0
    { 0x8522, "_meth_8522" }, // MP 0x14032C720
    { 0x8523, "_meth_8523" }, // SP 0x14021E220, MP 0x1402EEB60
    { 0x8524, "_meth_8524" }, // MP 0x140329390
    { 0x8525, "_meth_8525" }, // SP 0x14024CC20, MP 0x140317000
    { 0x8526, "_meth_8526" }, // SP 0x14024CC40, MP 0x140317020
    { 0x8527, "_meth_8527" }, // SP 0x140215370, MP 0x1402DCBC0
    { 0x8528, "_meth_8528" }, // SP 0x14024C260, MP 0x14031A0B0
    { 0x8529, "_meth_8529" }, // SP 0x14024AD20, MP 0x1403198A0
    { 0x852A, "_meth_852A" }, // SP 0x140265A60, MP 0x1403345E0
    { 0x852B, "_meth_852B" }, // SP 0x14023B310
    { 0x852C, "_meth_852C" }, // MP 0x1402E7D80
    { 0x852D, "_meth_852D" }, // MP 0x140404F00
    { 0x852E, "_meth_852E" }, // SP 0x140210A60
    { 0x852F, "_meth_852F" }, // MP 0x1402E5FE0
    { 0x8530, "_meth_8530" }, // MP 0x140317B50
    { 0x8531, "_meth_8531" }, // SP 0x14024E060, MP 0x140318C60
    { 0x8532, "_meth_8532" }, // MP 0x14032DE80
    { 0x8533, "_meth_8533" }, // MP 0x14032DFB0
    { 0x8534, "_meth_8534" }, // SP 0x14021EB20, MP 0x1402EF300
    { 0x8535, "_meth_8535" }, // MP 0x1402E6B00
    { 0x8536, "_meth_8536" }, // SP 0x140253150, MP 0x140320AA0
    { 0x8537, "_meth_8537" }, // SP 0x140240CE0, MP 0x14031EF00
    { 0x8538, "_meth_8538" }, // MP 0x1402E6A10
    { 0x8539, "_meth_8539" }, // MP 0x1402E5C10
    { 0x853A, "_meth_853A" }, // MP 0x14031F870
    { 0x853B, "_meth_853B" }, // MP 0x140329750
    { 0x853C, "_meth_853C" }, // MP 0x140406810
    { 0x853D, "_meth_853D" }, // MP 0x1404051D0
    { 0x853E, "_meth_853E" }, // MP 0x140406340
    { 0x853F, "_meth_853F" }, // MP 0x1402E72A0
    { 0x8540, "_meth_8540" }, // MP 0x140404C70
    { 0x8541, "_meth_8541" }, // MP 0x1404065C0
    { 0x8542, "_meth_8542" }, // MP 0x140405C60
    { 0x8543, "_meth_8543" }, // MP 0x140406400
    { 0x8544, "_meth_8544" }, // MP 0x140406230
    { 0x8545, "_meth_8545" }, // MP 0x140406650
    { 0x8546, "_meth_8546" }, // MP 0x1402E7DE0
    { 0x8547, "_meth_8547" }, // MP 0x140333550
    { 0x8548, "_meth_8548" }, // MP 0x140403FE0
    { 0x8549, "_meth_8549" }, // SP 0x1402527A0, MP 0x140320360
    { 0x854A, "_meth_854A" }, // SP 0x140215690, MP 0x1402DC850
    { 0x854B, "_meth_854B" }, // MP 0x140329830
    { 0x854C, "_meth_854C" }, // MP 0x140403F50
    { 0x854D, "_meth_854D" }, // SP 0x140242310, MP 0x14030C7B0
    { 0x854E, "_meth_854E" }, // SP 0x140252B90, MP 0x1403206B0
    { 0x854F, "_meth_854F" }, // MP 0x140329960
    { 0x8550, "_meth_8550" }, // MP 0x140328100
    { 0x8551, "_meth_8551" }, // MP 0x140405990
    { 0x8552, "_meth_8552" }, // MP 0x1402E70C0
    { 0x8553, "_meth_8553" }, // MP 0x1403335F0
    { 0x8554, "_meth_8554" }, // SP 0x14024C220, MP 0x140316A20
    { 0x8555, "_meth_8555" }, // SP 0x14024C9C0, MP 0x140316DB0
    { 0x8556, "_meth_8556" }, // MP 0x140406B50
    { 0x8557, "_meth_8557" }, // SP 0x140216590, MP 0x1402DE070
    { 0x8558, "_meth_8558" }, // MP 0x1402E7E40
    { 0x8559, "_meth_8559" }, // MP 0x140329BA0
    { 0x855A, "_meth_855A" }, // MP 0x140405AF0
    { 0x855B, "_meth_855B" }, // MP 0x1402E7240
    { 0x855C, "_meth_855C" }, // MP 0x14031A370
    { 0x855D, "_meth_855D" }, // MP 0x140406970
    { 0x855E, "_meth_855E" }, // MP 0x140405B60
    { 0x855F, "_meth_855F" }, // SP 0x140265D00, MP 0x140334E10
    { 0x8560, "_meth_8560" }, // MP 0x140320A90
    { 0x8561, "_meth_8561" }, // MP 0x140406C00
    { 0x8562, "_meth_8562" }, // MP 0x140328BF0
    { 0x8563, "_meth_8563" }, // MP 0x1404053E0
    { 0x8564, "_meth_8564" }, // MP 0x140406D20
    { 0x8565, "_meth_8565" }, // MP 0x14032C900
    { 0x8566, "_meth_8566" }, // MP 0x14032C9E0
    { 0x8567, "_meth_8567" }, // MP 0x140044360
    { 0x8568, "_meth_8568" }, // MP 0x140333680
    { 0x8569, "_meth_8569" }, // MP 0x1402E7130
    { 0x856A, "_meth_856A" }, // MP 0x1403294B0
    { 0x856B, "_meth_856B" }, // SP 0x14023F290, MP 0x140320B40
    { 0x856C, "_meth_856C" }, // MP 0x140333710
}};

const std::array<pair_16C, 13> file_list
{{
    { 0x053D, "codescripts/delete" },
    { 0x053E, "codescripts/struct" },
    { 0x0540, "maps/mp/gametypes/_callbacksetup" },
    { 0xA4E5, "codescripts/character" },
    { 42214, "common_scripts/_artcommon" },
    { 42215, "common_scripts/_bcs_location_trigs" },
    { 42216, "common_scripts/_createfx" },
    { 42217, "common_scripts/_createfxmenu" },
    { 42218, "common_scripts/_destructible" },
    { 42219, "common_scripts/_dynamic_world" },
    { 42735, "maps/createart/mp_vlobby_room_art" },
    { 42736, "maps/createart/mp_vlobby_room_fog" },
    { 42737, "maps/createart/mp_vlobby_room_fog_hdr" },
    
}};

const std::array<pair_16C, 25> token_list
{{
    { 180, "CodeCallback_BulletHitEntity" },
    { 181, "CodeCallback_CodeEndGame" },
    { 182, "CodeCallback_EntityDamage" },
    { 183, "CodeCallback_EntityOutOfWorld" },
    { 185, "CodeCallback_HostMigration" },
    { 187, "CodeCallback_PartyMembers" },
    { 188, "CodeCallback_PlayerConnect" },
    { 189, "CodeCallback_PlayerDamage" },
    { 190, "CodeCallback_PlayerDisconnect" },
    { 191, "CodeCallback_PlayerGrenadeSuicide" },
    { 192, "CodeCallback_PlayerKilled" },
    { 193, "CodeCallback_PlayerLastStand" },
    { 194, "CodeCallback_PlayerMigrated" },
    { 195, "CodeCallback_StartGameType" },
    { 196, "CodeCallback_VehicleDamage" },
    { 221, "CreateStruct" },
    { 522, "InitStructs" },
    { 619, "main" },

    { 1727, "AbortLevel" },
    { 6662, "callbackVoid" },

    { 8192, "CodeCallback_GiveKillstreak" },
    { 32577, "SetDefaultCallbacks" },
    { 33531, "SetupCallbacks" },
    { 33542, "SetupDamageFlags" },
    { 36698, "struct" },
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

} // namespace xsk::gsc::s1
