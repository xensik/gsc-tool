// Copyright 2020 xensik. All Rights Reserved.

#ifndef XSK_GSC_IW5_H_
#define XSK_GSC_IW5_H_

namespace iw5
{

enum class opcode : std::uint8_t
{
	OP_End = 0x0,
	OP_Return = 0x1,
	OP_GetByte = 0x2,
	OP_GetNegByte = 0x3,
	OP_GetUnsignedShort = 0x4,
	OP_GetNegUnsignedShort = 0x5,
	OP_GetInteger = 0x6,
	OP_GetBuiltinFunction = 0x7,
	OP_GetBuiltinMethod = 0x8,
	OP_GetFloat = 0x9,
	OP_GetString = 0xA,
	OP_GetUndefined = 0xB,
	OP_GetZero = 0xC,
	OP_waittillFrameEnd = 0xD,
	OP_CreateLocalVariable = 0xE,
	OP_RemoveLocalVariables = 0xF,
	OP_EvalLocalVariableCached0 = 0x10,
	OP_EvalLocalVariableCached1 = 0x11,
	OP_EvalLocalVariableCached2 = 0x12,
	OP_EvalLocalVariableCached3 = 0x13,
	OP_EvalLocalVariableCached4 = 0x14,
	OP_EvalLocalVariableCached5 = 0x15,
	OP_EvalLocalVariableCached = 0x16,
	OP_EvalLocalArrayCached = 0x17,
	OP_EvalArray = 0x18,
	OP_EvalNewLocalArrayRefCached0 = 0x19,
	OP_EvalLocalArrayRefCached0 = 0x1A,
	OP_EvalLocalArrayRefCached = 0x1B,
	OP_EvalArrayRef = 0x1C,
	OP_ClearArray = 0x1D,
	OP_EmptyArray = 0x1E,
	OP_AddArray = 0x1F,
	OP_PreScriptCall = 0x20,
	OP_ScriptLocalFunctionCall2 = 0x21,
	OP_ScriptLocalFunctionCall = 0x22,
	OP_ScriptLocalMethodCall = 0x23,
	OP_ScriptLocalThreadCall = 0x24,
	OP_ScriptLocalChildThreadCall = 0x25,
	OP_ScriptLocalMethodThreadCall = 0x26,
	OP_ScriptLocalMethodChildThreadCall = 0x27,
	OP_ScriptFarFunctionCall2 = 0x28,
	OP_ScriptFarFunctionCall = 0x29,
	OP_ScriptFarMethodCall = 0x2A,
	OP_ScriptFarThreadCall = 0x2B,
	OP_ScriptFarChildThreadCall = 0x2C,
	OP_ScriptFarMethodThreadCall = 0x2D,
	OP_ScriptFarMethodChildThreadCall = 0x2E,
	OP_ScriptFunctionCallPointer = 0x2F,
	OP_ScriptMethodCallPointer = 0x30,
	OP_ScriptThreadCallPointer = 0x31,
	OP_ScriptMethodChildThreadCallPointer_0 = 0x32,
	OP_ScriptMethodThreadCallPointer = 0x33,
	OP_ScriptMethodChildThreadCallPointer = 0x34,
	OP_CallBuiltinPointer = 0x35,
	OP_CallBuiltinMethodPointer = 0x36,
	OP_GetIString = 0x37,
	OP_GetVector = 0x38,
	OP_GetLevelObject = 0x39,
	OP_GetAnimObject = 0x3A,
	OP_GetSelf = 0x3B,
	OP_GetThisthread = 0x3C,
	OP_GetLevel = 0x3D,
	OP_GetGame = 0x3E,
	OP_GetAnim = 0x3F,
	OP_GetAnimation = 0x40,
	OP_GetGameRef = 0x41,
	OP_inc = 0x42,
	OP_dec = 0x43,
	OP_bit_or = 0x44,
	OP_JumpOnFalseExpr = 0x45,
	OP_bit_ex_or = 0x46,
	OP_bit_and = 0x47,
	OP_equality = 0x48,
	OP_inequality = 0x49,
	OP_less = 0x4A,
	OP_greater = 0x4B,
	OP_JumpOnTrueExpr = 0x4C,
	OP_less_equal = 0x4D,
	OP_jumpback = 0x4E,
	OP_waittillmatch2 = 0x4F, // nop
	OP_waittill = 0x50,
	OP_notify = 0x51,
	OP_endon = 0x52,
	OP_voidCodepos = 0x53,
	OP_switch = 0x54,
	OP_endswitch = 0x55,
	OP_vector = 0x56,
	OP_JumpOnFalse = 0x57,
	OP_greater_equal = 0x58,
	OP_shift_left = 0x59,
	OP_shift_right = 0x5A,
	OP_plus = 0x5B,
	OP_jump = 0x5C,
	OP_minus = 0x5D,
	OP_multiply = 0x5E,
	OP_divide = 0x5F,
	OP_mod = 0x60,
	OP_JumpOnTrue = 0x61,
	OP_size = 0x62,
	OP_waittillmatch = 0x63,
	OP_GetLocalFunction = 0x64,
	OP_GetFarFunction = 0x65,
	OP_GetSelfObject = 0x66,
	OP_EvalLevelFieldVariable = 0x67,
	OP_EvalAnimFieldVariable = 0x68,
	OP_EvalSelfFieldVariable = 0x69,
	OP_EvalFieldVariable = 0x6A,
	OP_EvalLevelFieldVariableRef = 0x6B,
	OP_EvalAnimFieldVariableRef = 0x6C,
	OP_EvalSelfFieldVariableRef = 0x6D,
	OP_EvalFieldVariableRef = 0x6E,
	OP_ClearFieldVariable = 0x6F,
	OP_SafeCreateVariableFieldCached = 0x70,
	OP_SafeSetVariableFieldCached0 = 0x71,
	OP_SafeSetVariableFieldCached = 0x72,
	OP_SafeSetWaittillVariableFieldCached = 0x73,
	OP_GetAnimTree = 0x74,
	OP_clearparams = 0x75,
	OP_checkclearparams = 0x76,
	OP_EvalLocalVariableRefCached0 = 0x77,
	OP_EvalNewLocalVariableRefCached0 = 0x78,// nop
	OP_EvalLocalVariableRefCached = 0x79,
	OP_SetLevelFieldVariableField = 0x7A,
	OP_SetVariableField = 0x7B,
	OP_ClearVariableField = 0x7C,// nop
	OP_SetAnimFieldVariableField = 0x7D,
	OP_SetSelfFieldVariableField = 0x7E,
	OP_SetLocalVariableFieldCached0 = 0x7F,
	OP_SetNewLocalVariableFieldCached0 = 0x80,
	OP_SetLocalVariableFieldCached = 0x81,
	OP_ClearLocalVariableFieldCached = 0x82,
	OP_ClearLocalVariableFieldCached0 = 0x83,
	OP_CallBuiltin0 = 0x84,
	OP_CallBuiltin1 = 0x85,
	OP_CallBuiltin2 = 0x86,
	OP_CallBuiltin3 = 0x87,
	OP_CallBuiltin4 = 0x88,
	OP_CallBuiltin5 = 0x89,
	OP_CallBuiltin = 0x8A,
	OP_CallBuiltinMethod0 = 0x8B,
	OP_CallBuiltinMethod1 = 0x8C,
	OP_CallBuiltinMethod2 = 0x8D,
	OP_CallBuiltinMethod3 = 0x8E,
	OP_CallBuiltinMethod4 = 0x8F,
	OP_CallBuiltinMethod5 = 0x90,
	OP_CallBuiltinMethod = 0x91,
	OP_wait = 0x92,
	OP_DecTop = 0x93,
	OP_CastFieldObject = 0x94,
	OP_EvalLocalVariableObjectCached = 0x95,
	OP_CastBool = 0x96,
	OP_BoolNot = 0x97,
	OP_BoolComplement = 0x98,
	OP_Count = 0x99,
};

// opcodes
auto get_opcode_id(const std::string& name) -> opcode;
auto get_opcode_name(opcode id) -> std::string;
auto get_opcode_size(opcode op) -> std::size_t;

// builtins
auto get_builtin_func_id(const std::string& name) -> std::uint16_t;
auto get_builtin_func_name(std::uint16_t id) -> std::string;

auto get_builtin_method_id(const std::string& name) -> std::uint16_t;
auto get_builtin_method_name(std::uint16_t id)->std::string;

//files
auto get_file_id(std::string name) -> std::uint16_t;
auto get_file_name(std::uint16_t id) -> std::string;

// functions & fields
auto get_token_id(std::string name) -> std::uint16_t;
auto get_token_name(std::uint16_t id) -> std::string;

} // namespace iw5

#endif // XSK_GSC_IW5_H_