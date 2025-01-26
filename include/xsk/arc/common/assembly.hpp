// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

constexpr usize opcode_count = 143;

enum class opcode : u8
{
    OP_Invalid,
    OP_End,
    OP_Return,
    OP_GetUndefined,
    OP_GetZero,
    OP_GetByte,
    OP_GetNegByte,
    OP_GetUnsignedShort,
    OP_GetNegUnsignedShort,
    OP_GetInteger,
    OP_GetFloat,
    OP_GetString,
    OP_GetIString,
    OP_GetVector,
    OP_GetLevelObject,
    OP_GetAnimObject,
    OP_GetSelf,
    OP_GetLevel,
    OP_GetGame,
    OP_GetAnim,
    OP_GetAnimation,
    OP_GetGameRef,
    OP_GetFunction,
    OP_CreateLocalVariable,
    OP_SafeCreateLocalVariables,
    OP_RemoveLocalVariables,
    OP_EvalLocalVariableCached,
    OP_EvalArray,
    OP_EvalLocalArrayRefCached,
    OP_EvalArrayRef,
    OP_ClearArray,
    OP_EmptyArray,
    OP_GetSelfObject,
    OP_EvalFieldVariable,
    OP_EvalFieldVariableRef,
    OP_ClearFieldVariable,
    OP_SafeSetVariableFieldCached,
    OP_SafeSetWaittillVariableFieldCached,
    OP_ClearParams,
    OP_CheckClearParams,
    OP_EvalLocalVariableRefCached,
    OP_SetVariableField,
    OP_CallBuiltin,
    OP_CallBuiltinMethod,
    OP_Wait,
    OP_WaitTillFrameEnd,
    OP_PreScriptCall,
    OP_ScriptFunctionCall,
    OP_ScriptFunctionCallPointer,
    OP_ScriptMethodCall,
    OP_ScriptMethodCallPointer,
    OP_ScriptThreadCall,
    OP_ScriptThreadCallPointer,
    OP_ScriptMethodThreadCall,
    OP_ScriptMethodThreadCallPointer,
    OP_DecTop,
    OP_CastFieldObject,
    OP_CastBool,
    OP_BoolNot,
    OP_BoolComplement,
    OP_JumpOnFalse,
    OP_JumpOnTrue,
    OP_JumpOnFalseExpr,
    OP_JumpOnTrueExpr,
    OP_Jump,
    OP_JumpBack,
    OP_Inc,
    OP_Dec,
    OP_Bit_Or,
    OP_Bit_Xor,
    OP_Bit_And,
    OP_Equal,
    OP_NotEqual,
    OP_LessThan,
    OP_GreaterThan,
    OP_LessThanOrEqualTo,
    OP_GreaterThanOrEqualTo,
    OP_ShiftLeft,
    OP_ShiftRight,
    OP_Plus,
    OP_Minus,
    OP_Multiply,
    OP_Divide,
    OP_Modulus,
    OP_SizeOf,
    OP_WaitTillMatch,
    OP_WaitTill,
    OP_Notify,
    OP_EndOn,
    OP_VoidCodePos,
    OP_Switch,
    OP_EndSwitch,
    OP_Vector,
    OP_GetHash,
    OP_RealWait,
    OP_VectorConstant,
    OP_IsDefined,
    OP_VectorScale,
    OP_AnglesToUp,
    OP_AnglesToRight,
    OP_AnglesToForward,
    OP_AngleClamp180,
    OP_VectorToAngles,
    OP_Abs,
    OP_GetTime,
    OP_GetDvar,
    OP_GetDvarInt,
    OP_GetDvarFloat,
    OP_GetDvarVector,
    OP_GetDvarColorRed,
    OP_GetDvarColorGreen,
    OP_GetDvarColorBlue,
    OP_GetDvarColorAlpha,
    OP_FirstArrayKey,
    OP_NextArrayKey,
    OP_ProfileStart,
    OP_ProfileStop,
    OP_SafeDecTop,
    OP_Nop,
    OP_Abort,
    OP_Object,
    OP_ThreadObject,
    OP_EvalLocalVariable,
    OP_EvalLocalVariableRef,
    OP_DevblockBegin,
    OP_DevblockEnd,
    OP_EvalLocalVariableCachedDebug,
    OP_EvalLocalVariableRefCachedDebug,
    OP_LevelEvalFieldVariable,
    OP_LevelEvalFieldVariableRef,
    OP_SelfEvalFieldVariable,
    OP_SelfEvalFieldVariableRef,
    OP_GetWorld,
    OP_GetWorldObject,
    OP_GetClasses,
    OP_GetClassesObject,
    OP_New,
    OP_ScriptFunctionCallClass,
    OP_ScriptThreadCallClass,
    OP_GetUintptr,
    OP_SuperEqual,
    OP_SuperNotEqual,
    OP_GetAPIFunction,
    OP_Count,
};

struct sourcepos
{
    i32 line;
    i32 column;
};

struct instruction
{
    using ptr = std::unique_ptr<instruction>;

    usize index;
    usize size;
    sourcepos pos;
    opcode opcode;
    std::vector<std::string> data;

    static auto make() -> instruction::ptr
    {
        return std::unique_ptr<instruction>(new instruction);
    }
};

struct function
{
    using ptr = std::unique_ptr<function>;

    usize index;
    usize size;
    u8 params;
    u8 flags;
    std::string name;
    std::string space;
    std::vector<instruction::ptr> instructions;
    std::unordered_map<usize, std::string> labels;

    static auto make() -> function::ptr
    {
        return std::unique_ptr<function>(new function);
    }
};

struct assembly
{
    using ptr = std::unique_ptr<assembly>;

    std::vector<std::string> includes;
    std::vector<function::ptr> functions;

    static auto make() -> assembly::ptr
    {
        return std::unique_ptr<assembly>(new assembly);
    }
};

} // namespace xsk::arc
