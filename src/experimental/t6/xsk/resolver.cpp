// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "t6.hpp"

namespace xsk::gsc::t6
{

std::unordered_map<std::uint8_t, std::string> opcode_map;
std::unordered_map<std::string, std::uint8_t> opcode_map_rev;

auto resolver::opcode_id(const std::string& name) -> std::uint8_t
{
    const auto itr = opcode_map_rev.find(name);

    if (itr != opcode_map_rev.end())
    {
        return itr->second;
    }

    throw gsc::error(utils::string::va("Couldn't resolve opcode id for name '%s'!", name.data()));
}

auto resolver::opcode_name(std::uint8_t id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return itr->second;
    }

    throw gsc::error(utils::string::va("Couldn't resolve opcode name for id '0x%hhX'!", id));
}

const std::array<gsc::pair_8C, 126> opcode_list
{{
    { std::uint8_t(opcode::OP_End),"END" },
    { std::uint8_t(opcode::OP_Return),"RETN" },
    { std::uint8_t(opcode::OP_GetUndefined),"GET_UNDEFINED" },
    { std::uint8_t(opcode::OP_GetZero),"GET_ZERO" },
    { std::uint8_t(opcode::OP_GetByte),"GET_BYTE" },
    { std::uint8_t(opcode::OP_GetNegByte),"GET_NBYTE" },
    { std::uint8_t(opcode::OP_GetUnsignedShort),"GET_USHORT" },
    { std::uint8_t(opcode::OP_GetNegUnsignedShort),"GET_NUSHORT" },
    { std::uint8_t(opcode::OP_GetInteger),"GET_INT" },
    { std::uint8_t(opcode::OP_GetFloat),"GET_FLOAT" },
    { std::uint8_t(opcode::OP_GetString),"GET_STRING" },
    { std::uint8_t(opcode::OP_GetIString),"GET_ISTRING" },
    { std::uint8_t(opcode::OP_GetVector),"GET_VECTOR" },
    { std::uint8_t(opcode::OP_GetLevelObject),"GET_LEVEL_OBJ" },
    { std::uint8_t(opcode::OP_GetAnimObject),"GET_ANIM_OBJ" },
    { std::uint8_t(opcode::OP_GetSelf),"GET_SELF" },
    { std::uint8_t(opcode::OP_GetLevel),"GET_LEVEL" },
    { std::uint8_t(opcode::OP_GetGame),"GET_GAME" },
    { std::uint8_t(opcode::OP_GetAnim),"GET_ANIM" },
    { std::uint8_t(opcode::OP_GetAnimation),"GET_ANIMATION" },
    { std::uint8_t(opcode::OP_GetGameRef),"GET_GAME_REF" },
    { std::uint8_t(opcode::OP_GetFunction),"GET_FUNCTION" },
    { std::uint8_t(opcode::OP_CreateLocalVariable),"CREATE_LOCAL_VARIABLE" },
    { std::uint8_t(opcode::OP_SafeCreateLocalVariables),"SAFE_CREATE_LOCAL_VARIABLES" },
    { std::uint8_t(opcode::OP_RemoveLocalVariables),"REMOVE_LOCAL_VARIABLES" },
    { std::uint8_t(opcode::OP_EvalLocalVariableCached),"EVAL_LOCAL_VARIABLE_CACHED" },
    { std::uint8_t(opcode::OP_EvalArray),"EVAL_ARRAY" },
    { std::uint8_t(opcode::OP_EvalLocalArrayRefCached),"EVAL_LOCAL_ARRAY_REF_CACHED" },
    { std::uint8_t(opcode::OP_EvalArrayRef),"EVAL_ARRAY_REF" },
    { std::uint8_t(opcode::OP_ClearArray),"CLEAR_ARRAY" },
    { std::uint8_t(opcode::OP_EmptyArray),"EMPTY_ARRAY" },
    { std::uint8_t(opcode::OP_GetSelfObject),"GET_SELF_OBJECT" },
    { std::uint8_t(opcode::OP_EvalFieldVariable),"EVAL_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_EvalFieldVariableRef),"EVAL_FIELD_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_ClearFieldVariable),"CLEAR_FIELD_VARIABLE" },
    { std::uint8_t(opcode::OP_SafeSetVariableFieldCached),"SAFE_SET_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_SafeSetWaittillVariableFieldCached),"SAFE_SET_WAITTILL_VARIABLE_FIELD_CACHED" },
    { std::uint8_t(opcode::OP_ClearParams),"CLEAR_PARAMS" },
    { std::uint8_t(opcode::OP_CheckClearParams),"CHECK_CLEAR_PARAMS" },
    { std::uint8_t(opcode::OP_EvalLocalVariableRefCached),"EVAL_LOCAL_VARIABLE_REF_CACHED" },
    { std::uint8_t(opcode::OP_SetVariableField),"SET_VARIABLE_FIELD" },
    { std::uint8_t(opcode::OP_CallBuiltin),"CALL_BUILTIN_FUNC" },
    { std::uint8_t(opcode::OP_CallBuiltinMethod),"CALL_BUILTIN_METHOD" },
    { std::uint8_t(opcode::OP_Wait),"WAIT" },
    { std::uint8_t(opcode::OP_WaitTillFrameEnd),"WAITTILLFRAMEEND" },
    { std::uint8_t(opcode::OP_PreScriptCall),"PRE_CALL" },
    { std::uint8_t(opcode::OP_ScriptFunctionCall),"SCRIPT_FUNC_CALL" },
    { std::uint8_t(opcode::OP_ScriptFunctionCallPointer),"SCRIPT_FUNC_CALL_POINTER" },
    { std::uint8_t(opcode::OP_ScriptMethodCall),"SCRIPT_METHOD_CALL" },
    { std::uint8_t(opcode::OP_ScriptMethodCallPointer),"SCRIPT_METHOD_CALL_POINTER" },
    { std::uint8_t(opcode::OP_ScriptThreadCall),"SCRIPT_THREAD_CALL" },
    { std::uint8_t(opcode::OP_ScriptThreadCallPointer),"SCRIPT_THREAD_CALL_POINTER" },
    { std::uint8_t(opcode::OP_ScriptMethodThreadCall),"SCRIPT_METHOD_THREAD_CALL" },
    { std::uint8_t(opcode::OP_ScriptMethodThreadCallPointer),"SCRIPT_METHOD_THREAD_CALL_POINTER" },
    { std::uint8_t(opcode::OP_DecTop),"DEC_TOP" },
    { std::uint8_t(opcode::OP_CastFieldObject),"CAST_FIELD_OBJECT" },
    { std::uint8_t(opcode::OP_CastBool),"CAST_BOOL" },
    { std::uint8_t(opcode::OP_BoolNot),"BOOL_NOT" },
    { std::uint8_t(opcode::OP_BoolComplement),"BOOL_COMPLEMENT" },
    { std::uint8_t(opcode::OP_JumpOnFalse),"JMP_FALSE" },
    { std::uint8_t(opcode::OP_JumpOnTrue),"JMP_TRUE" },
    { std::uint8_t(opcode::OP_JumpOnFalseExpr),"JMP_EXPR_FALSE" },
    { std::uint8_t(opcode::OP_JumpOnTrueExpr),"JMP_EXPR_TRUE" },
    { std::uint8_t(opcode::OP_Jump),"JMP" },
    { std::uint8_t(opcode::OP_JumpBack),"JMP_BACK" },
    { std::uint8_t(opcode::OP_Inc),"INC" },
    { std::uint8_t(opcode::OP_Dec),"DEC" },
    { std::uint8_t(opcode::OP_Bit_Or),"BIT_OR" },
    { std::uint8_t(opcode::OP_Bit_Xor),"BIT_XOR" },
    { std::uint8_t(opcode::OP_Bit_And),"BIT_AND" },
    { std::uint8_t(opcode::OP_Equal),"EQUAL" },
    { std::uint8_t(opcode::OP_NotEqual),"NOT_EQUAL" },
    { std::uint8_t(opcode::OP_LessThan),"LESS" },
    { std::uint8_t(opcode::OP_GreaterThan),"GREATER" },
    { std::uint8_t(opcode::OP_LessThanOrEqualTo),"LESS_EQUAL" },
    { std::uint8_t(opcode::OP_GreaterThanOrEqualTo),"GREATER_EQUAL" },
    { std::uint8_t(opcode::OP_ShiftLeft),"SHIFT_LEFT" },
    { std::uint8_t(opcode::OP_ShiftRight),"SHIFT_RIGHT" },
    { std::uint8_t(opcode::OP_Plus),"PLUS" },
    { std::uint8_t(opcode::OP_Minus),"MINUS" },
    { std::uint8_t(opcode::OP_Multiply),"MULT" },
    { std::uint8_t(opcode::OP_Divide),"DIV" },
    { std::uint8_t(opcode::OP_Modulus),"MOD" },
    { std::uint8_t(opcode::OP_SizeOf),"SIZE" },
    { std::uint8_t(opcode::OP_WaitTillMatch),"WAITTILLMATCH" },
    { std::uint8_t(opcode::OP_WaitTill),"WAITTILL" },
    { std::uint8_t(opcode::OP_Notify),"NOTIFY" },
    { std::uint8_t(opcode::OP_EndOn),"ENDON" },
    { std::uint8_t(opcode::OP_VoidCodePos),"VOIDCODEPOS" },
    { std::uint8_t(opcode::OP_Switch),"SWITCH" },
    { std::uint8_t(opcode::OP_EndSwitch),"ENDSWITCH" },
    { std::uint8_t(opcode::OP_Vector),"VECTOR" },
    { std::uint8_t(opcode::OP_GetHash),"GET_HASH" },
    { std::uint8_t(opcode::OP_RealWait),"REAL_WAIT" },
    { std::uint8_t(opcode::OP_VectorConstant),"VECTOR_CONSTANT" },
    { std::uint8_t(opcode::OP_IsDefined),"IS_DEFINED" },
    { std::uint8_t(opcode::OP_VectorScale),"VECTOR_SCALE" },
    { std::uint8_t(opcode::OP_AnglesToUp),"ANGLES_TO_UP" },
    { std::uint8_t(opcode::OP_AnglesToRight),"ANGLES_TO_RIGHT" },
    { std::uint8_t(opcode::OP_AnglesToForward),"ANGLES_TO_FORDWARD" },
    { std::uint8_t(opcode::OP_AngleClamp180),"ANGLE_CLAMP_180" },
    { std::uint8_t(opcode::OP_VectorToAngles),"VECTOR_TO_ANGLES" },
    { std::uint8_t(opcode::OP_Abs),"ABS" },
    { std::uint8_t(opcode::OP_GetTime),"GET_TIME" },
    { std::uint8_t(opcode::OP_GetDvar),"GET_DVAR" },
    { std::uint8_t(opcode::OP_GetDvarInt),"GET_DVAR_INT" },
    { std::uint8_t(opcode::OP_GetDvarFloat),"GET_DVAR_FLOAT" },
    { std::uint8_t(opcode::OP_GetDvarVector),"GET_DVAR_VECTOR" },
    { std::uint8_t(opcode::OP_GetDvarColorRed),"GET_DVAR_COLOR_RED" },
    { std::uint8_t(opcode::OP_GetDvarColorGreen),"GET_DVAR_COLOR_GREEN" },
    { std::uint8_t(opcode::OP_GetDvarColorBlue),"GET_DVAR_COLOR_BLUE" },
    { std::uint8_t(opcode::OP_GetDvarColorAlpha),"GET_DVAR_COLOR_ALPHA" },
    { std::uint8_t(opcode::OP_FirstArrayKey),"FIRST_ARRAY_KEY" },
    { std::uint8_t(opcode::OP_NextArrayKey),"NEXT_ARRAY_KEY" },
    { std::uint8_t(opcode::OP_ProfileStart),"PROFILE_START" },
    { std::uint8_t(opcode::OP_ProfileStop),"PROFILE_STOP" },
    { std::uint8_t(opcode::OP_SafeDecTop),"SAFE_DEC_TOP" },
    { std::uint8_t(opcode::OP_Nop),"NOP" },
    { std::uint8_t(opcode::OP_Abort),"ABORT" },
    { std::uint8_t(opcode::OP_Object),"OBJECT" },
    { std::uint8_t(opcode::OP_ThreadObject),"THREAD_OBJECT" },
    { std::uint8_t(opcode::OP_EvalLocalVariable),"EVAL_LOCAL_VARIABLE" },
    { std::uint8_t(opcode::OP_EvalLocalVariableRef),"EVAL_LOCAL_VARIABLE_REF" },
    { std::uint8_t(opcode::OP_DevblockBegin),"DEVBLOCK_BEGIN" },
    { std::uint8_t(opcode::OP_DevblockEnd),"DEVBLOCK_END" },
    { std::uint8_t(opcode::OP_Breakpoint),"BREAKPOINT" },
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
        
        for(const auto& entry : opcode_list)
        {
            opcode_map.insert({ entry.key, entry.value });
            opcode_map_rev.insert({ entry.value, entry.key });
        }
    }
};

__init__ _;

} // namespace xsk::gsc::t6
