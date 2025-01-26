// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

constexpr usize opcode_count = 205;

enum class opcode : u8
{
    vm_invalid,
    OP_CastFieldObject,
    OP_SetLocalVariableFieldCached,
    OP_plus,
    OP_RemoveLocalVariables,
    OP_EvalSelfFieldVariableRef,
    OP_ScriptFarMethodChildThreadCall,
    OP_GetGameRef,
    OP_EvalAnimFieldVariable,
    OP_EvalLevelFieldVariableRef,
    OP_GetThisthread,
    OP_greater,
    OP_waittillmatch,
    OP_shift_right,
    OP_dec,
    OP_JumpOnTrue,
    OP_bit_or,
    OP_equality,
    OP_ClearLocalVariableFieldCached0,
    OP_notify,
    OP_GetVector,
    OP_ScriptMethodChildThreadCallPointer,
    OP_PreScriptCall,
    OP_GetByte,
    OP_ScriptFarThreadCall,
    OP_SetSelfFieldVariableField,
    OP_JumpOnFalseExpr,
    OP_GetUndefined,
    OP_jumpback,
    OP_JumpOnTrueExpr,
    OP_CallBuiltin0,
    OP_CallBuiltin1,
    OP_CallBuiltin2,
    OP_CallBuiltin3,
    OP_CallBuiltin4,
    OP_CallBuiltin5,
    OP_CallBuiltin,
    OP_SetLocalVariableFieldCached0,
    OP_ClearFieldVariable,
    OP_GetLevel,
    OP_size,
    OP_SafeSetWaittillVariableFieldCached,
    OP_ScriptLocalMethodThreadCall,
    OP_AddArray,
    OP_endon,
    OP_EvalFieldVariable,
    OP_shift_left,
    OP_EvalLocalArrayRefCached0,
    OP_Return,
    OP_CreateLocalVariable,
    OP_SafeSetVariableFieldCached0,
    OP_GetBuiltinFunction,
    OP_ScriptLocalMethodCall,
    OP_CallBuiltinMethodPointer,
    OP_ScriptLocalChildThreadCall,
    OP_GetSelfObject,
    OP_GetGame,
    OP_SetLevelFieldVariableField,
    OP_EvalArray,
    OP_GetSelf,
    OP_End,
    OP_EvalSelfFieldVariable,
    OP_less_equal,
    OP_EvalLocalVariableCached0,
    OP_EvalLocalVariableCached1,
    OP_EvalLocalVariableCached2,
    OP_EvalLocalVariableCached3,
    OP_EvalLocalVariableCached4,
    OP_EvalLocalVariableCached5,
    OP_EvalLocalVariableCached,
    OP_EvalNewLocalArrayRefCached0,
    OP_ScriptChildThreadCallPointer,
    OP_EvalLocalVariableObjectCached,
    OP_ScriptLocalThreadCall,
    OP_GetInteger,
    OP_ScriptMethodCallPointer,
    OP_checkclearparams,
    OP_SetAnimFieldVariableField,
    OP_waittillmatch2,
    OP_minus,
    OP_ScriptLocalFunctionCall2,
    OP_GetNegUnsignedShort,
    OP_GetNegByte,
    OP_SafeCreateVariableFieldCached,
    OP_greater_equal,
    OP_vector,
    OP_GetBuiltinMethod,
    OP_endswitch,
    OP_ClearArray,
    OP_DecTop,
    OP_CastBool,
    OP_EvalArrayRef,
    OP_SetNewLocalVariableFieldCached0,
    OP_GetZero,
    OP_wait,
    OP_waittill,
    OP_GetIString,
    OP_ScriptFarFunctionCall,
    OP_GetAnimObject,
    OP_GetAnimTree,
    OP_EvalLocalArrayCached,
    OP_mod,
    OP_ScriptFarMethodThreadCall,
    OP_GetUnsignedShort,
    OP_clearparams,
    OP_ScriptMethodThreadCallPointer,
    OP_ScriptFunctionCallPointer,
    OP_EmptyArray,
    OP_SafeSetVariableFieldCached,
    OP_ClearVariableField,
    OP_EvalFieldVariableRef,
    OP_ScriptLocalMethodChildThreadCall,
    OP_EvalNewLocalVariableRefCached0,
    OP_GetFloat,
    OP_EvalLocalVariableRefCached,
    OP_JumpOnFalse,
    OP_BoolComplement,
    OP_ScriptThreadCallPointer,
    OP_ScriptFarFunctionCall2,
    OP_less,
    OP_BoolNot,
    OP_waittillFrameEnd,
    OP_waitframe,
    OP_GetString,
    OP_EvalLevelFieldVariable,
    OP_GetLevelObject,
    OP_inc,
    OP_CallBuiltinMethod0,
    OP_CallBuiltinMethod1,
    OP_CallBuiltinMethod2,
    OP_CallBuiltinMethod3,
    OP_CallBuiltinMethod4,
    OP_CallBuiltinMethod5,
    OP_CallBuiltinMethod,
    OP_GetAnim,
    OP_switch,
    OP_SetVariableField,
    OP_divide,
    OP_GetLocalFunction,
    OP_ScriptFarChildThreadCall,
    OP_multiply,
    OP_ClearLocalVariableFieldCached,
    OP_EvalAnimFieldVariableRef,
    OP_EvalLocalArrayRefCached,
    OP_EvalLocalVariableRefCached0,
    OP_bit_and,
    OP_GetAnimation,
    OP_GetFarFunction,
    OP_CallBuiltinPointer,
    OP_jump,
    OP_voidCodepos,
    OP_ScriptFarMethodCall,
    OP_inequality,
    OP_ScriptLocalFunctionCall,
    OP_bit_ex_or,
    OP_NOP,
    OP_abort,
    OP_object,
    OP_thread_object,
    OP_EvalLocalVariable,
    OP_EvalLocalVariableRef,
    OP_prof_begin,
    OP_prof_end,
    OP_breakpoint,
    OP_assignmentBreakpoint,
    OP_manualAndAssignmentBreakpoint,
    OP_BoolNotAfterAnd,
    OP_FormalParams,
    OP_IsDefined,
    OP_IsTrue,
    OP_NativeGetLocalFunction,
    OP_NativeLocalFunctionCall,
    OP_NativeLocalFunctionCall2,
    OP_NativeLocalMethodCall,
    OP_NativeLocalFunctionThreadCall,
    OP_NativeLocalMethodThreadCall,
    OP_NativeLocalFunctionChildThreadCall,
    OP_NativeLocalMethodChildThreadCall,
    OP_NativeGetFarFunction,
    OP_NativeFarFunctionCall,
    OP_NativeFarFunctionCall2,
    OP_NativeFarMethodCall,
    OP_NativeFarFunctionThreadCall,
    OP_NativeFarMethodThreadCall,
    OP_NativeFarFunctionChildThreadCall,
    OP_NativeFarMethodChildThreadCall,
    OP_EvalNewLocalArrayRefCached0_Precompiled,
    OP_SetNewLocalVariableFieldCached0_Precompiled,
    OP_CreateLocalVariable_Precompiled,
    OP_SafeCreateVariableFieldCached_Precompiled,
    OP_FormalParams_Precompiled,
    OP_GetStatHash,
    OP_GetUnkxHash,
    OP_GetEnumHash,
    OP_GetDvarHash,
    OP_GetUnsignedInt,
    OP_GetNegUnsignedInt,
    OP_GetInteger64,
    OP_iw9_139,
    OP_iw9_140,
    OP_iw9_141,
    OP_iw9_142,
    OP_iw9_143,
    OP_iw9_144,
    OP_iw9_166,
    OP_count,
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
    u32 id;
    std::string name;
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

    std::vector<function::ptr> functions;

    static auto make() -> assembly::ptr
    {
        return std::unique_ptr<assembly>(new assembly);
    }
};

} // namespace xsk::gsc
