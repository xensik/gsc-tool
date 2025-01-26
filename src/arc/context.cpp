// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc
{

extern std::array<std::pair<opcode, std::string_view>, opcode_count> const opcode_list;

context::context(arc::props props, arc::engine engine, arc::endian endian, arc::system system, arc::instance inst, u64 magic)
    : props_{ props }, engine_{ engine }, endian_{ endian }, system_{ system }, instance_{ inst }, magic_{ magic },
      source_{ this }, assembler_{ this }, disassembler_{ this }, compiler_{ this }, decompiler_{ this }
{
    opcode_map_.reserve(opcode_list.size());
    opcode_map_rev_.reserve(opcode_list.size());

    for (auto const& entry : opcode_list)
    {
        opcode_map_.insert({ entry.first, entry.second });
        opcode_map_rev_.insert({ entry.second, entry.first });
    }
}

auto context::init(arc::build build, fs_callback callback) -> void
{
    build_ = build;
    fs_callback_ = callback;
}

auto context::cleanup() -> void
{
}

auto context::engine_name() const -> std::string_view
{
    switch (engine_)
    {
        case engine::t6: return "T6";
        case engine::t7: return "T7";
        case engine::t8: return "T8";
        case engine::t9: return "T9";
        default: return "";
    }
}

auto context::opcode_size(opcode op) const -> u32
{
    switch (op)
    {
        case opcode::OP_End:
        case opcode::OP_Return:
        case opcode::OP_GetUndefined:
        case opcode::OP_GetZero:
        case opcode::OP_GetLevelObject:
        case opcode::OP_GetAnimObject:
        case opcode::OP_GetSelf:
        case opcode::OP_GetLevel:
        case opcode::OP_GetGame:
        case opcode::OP_GetAnim:
        case opcode::OP_GetGameRef:
        case opcode::OP_CreateLocalVariable:
        case opcode::OP_EvalArray:
        case opcode::OP_EvalArrayRef:
        case opcode::OP_ClearArray:
        case opcode::OP_EmptyArray:
        case opcode::OP_GetSelfObject:
        case opcode::OP_ClearParams:
        case opcode::OP_CheckClearParams:
        case opcode::OP_SetVariableField:
        case opcode::OP_Wait:
        case opcode::OP_WaitTillFrameEnd:
        case opcode::OP_PreScriptCall:
        case opcode::OP_DecTop:
        case opcode::OP_CastFieldObject:
        case opcode::OP_CastBool:
        case opcode::OP_BoolNot:
        case opcode::OP_BoolComplement:
        case opcode::OP_Inc:
        case opcode::OP_Dec:
        case opcode::OP_Bit_Or:
        case opcode::OP_Bit_Xor:
        case opcode::OP_Bit_And:
        case opcode::OP_Equal:
        case opcode::OP_NotEqual:
        case opcode::OP_LessThan:
        case opcode::OP_GreaterThan:
        case opcode::OP_LessThanOrEqualTo:
        case opcode::OP_GreaterThanOrEqualTo:
        case opcode::OP_ShiftLeft:
        case opcode::OP_ShiftRight:
        case opcode::OP_Plus:
        case opcode::OP_Minus:
        case opcode::OP_Multiply:
        case opcode::OP_Divide:
        case opcode::OP_Modulus:
        case opcode::OP_SizeOf:
        case opcode::OP_WaitTill:
        case opcode::OP_Notify:
        case opcode::OP_EndOn:
        case opcode::OP_VoidCodePos:
        case opcode::OP_Vector:
        case opcode::OP_RealWait:
        case opcode::OP_IsDefined:
        case opcode::OP_VectorScale:
        case opcode::OP_AnglesToUp:
        case opcode::OP_AnglesToRight:
        case opcode::OP_AnglesToForward:
        case opcode::OP_AngleClamp180:
        case opcode::OP_VectorToAngles:
        case opcode::OP_Abs:
        case opcode::OP_GetTime:
        case opcode::OP_GetDvar:
        case opcode::OP_GetDvarInt:
        case opcode::OP_GetDvarFloat:
        case opcode::OP_GetDvarVector:
        case opcode::OP_GetDvarColorRed:
        case opcode::OP_GetDvarColorGreen:
        case opcode::OP_GetDvarColorBlue:
        case opcode::OP_GetDvarColorAlpha:
        case opcode::OP_FirstArrayKey:
        case opcode::OP_NextArrayKey:
        case opcode::OP_ProfileStop:
        case opcode::OP_SafeDecTop:
        case opcode::OP_Nop:
        case opcode::OP_Abort:
        case opcode::OP_Object:
        case opcode::OP_ThreadObject:
        case opcode::OP_EvalLocalVariable:
        case opcode::OP_EvalLocalVariableRef:
        case opcode::OP_GetWorldObject:
        case opcode::OP_GetWorld:
        case opcode::OP_GetClassesObject:
        case opcode::OP_GetClasses:
        case opcode::OP_SuperEqual:
        case opcode::OP_SuperNotEqual:
            return (props_ & props::size64) ? 2 : 1;
        case opcode::OP_SafeSetVariableFieldCached:
            return (props_ & props::size64) ? 3 : 1;
        case opcode::OP_GetByte:
        case opcode::OP_GetNegByte:
        case opcode::OP_SafeCreateLocalVariables:
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_EvalLocalArrayRefCached:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_EvalLocalVariableRefCached:
        case opcode::OP_ScriptFunctionCallPointer:
        case opcode::OP_ScriptMethodCallPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
        case opcode::OP_WaitTillMatch:
        case opcode::OP_VectorConstant:
            return (props_ & props::size64) ? 3 : 2;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
        case opcode::OP_JumpOnFalse:
        case opcode::OP_JumpOnTrue:
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_JumpOnTrueExpr:
        case opcode::OP_Jump:
        case opcode::OP_JumpBack:
        case opcode::OP_DevblockBegin:
        case opcode::OP_DevblockEnd:
            return (props_ & props::size64) ? 4 : 3;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_ClearFieldVariable:
            return (props_ & props::size64) ? 6 : 3;
        case opcode::OP_EvalLocalVariableCachedDebug:
        case opcode::OP_EvalLocalVariableRefCachedDebug:
        case opcode::OP_LevelEvalFieldVariableRef:
        case opcode::OP_LevelEvalFieldVariable:
        case opcode::OP_New:
        case opcode::OP_SelfEvalFieldVariableRef:
        case opcode::OP_SelfEvalFieldVariable:
            return 6;
        case opcode::OP_GetInteger:
        case opcode::OP_GetFloat:
        case opcode::OP_Switch:
        case opcode::OP_EndSwitch:
        case opcode::OP_GetHash:
            return (props_ & props::size64) ? 6 : 5;
        case opcode::OP_ScriptFunctionCallClass:
        case opcode::OP_ScriptThreadCallClass:
            return 7;
        case opcode::OP_GetAPIFunction:
            return 10;
        case opcode::OP_ProfileStart:
            return (props_ & props::size64) ? 10 : 1;
        case opcode::OP_GetAnimation:
        case opcode::OP_GetFunction:
            return (props_ & props::size64) ? 10 : 5;
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            return (props_ & props::size64) ? 11 : 6;
        case opcode::OP_GetVector:
            return (props_ & props::size64) ? 14 : 13;
        default:
            throw error(std::format("couldn't resolve instruction size for '{}'", opcode_name(op)));
    }
}

auto context::opcode_id(opcode op) const -> u16
{
    auto const itr = code_map_rev_.find(op);

    if (itr != code_map_rev_.end())
    {
        return itr->second;
    }

    throw error(std::format("couldn't resolve opcode id for '{}'", opcode_name(op)));
}

auto context::opcode_name(opcode op) const -> std::string
{
    auto const itr = opcode_map_.find(op);

    if (itr != opcode_map_.end())
    {
        return std::string{ itr->second };
    }

    throw std::runtime_error(std::format("couldn't resolve opcode string for enum '{}'", static_cast<std::underlying_type_t<opcode>>(op)));
}

auto context::opcode_enum(std::string const& name) const -> opcode
{
    auto const itr = opcode_map_rev_.find(name);

    if (itr != opcode_map_rev_.end())
    {
        return itr->second;
    }

    throw std::runtime_error(std::format("couldn't resolve opcode enum for name '{}'", name));
}

auto context::opcode_enum(u16 id) const -> opcode
{
    auto const itr = code_map_.find(id);

    if (itr != code_map_.end())
    {
        return itr->second;
    }

    return opcode::OP_Invalid;
}

auto context::hash_id(std::string const& name) const -> u32
{
    if (name.starts_with("_id_"))
    {
        return static_cast<u32>(std::stoul(name.substr(4), nullptr, 16));
    }

    if (props_ & props::hashids)
    {
        auto* str = name.data();
        auto hash = 16777619u * (std::tolower(static_cast<u8>(*str)) ^ 1268436527u);

        while (*str++)
        {
            hash = 16777619u * (std::tolower(static_cast<u8>(*str)) ^ hash);
        }

        return hash;
    }
    else
    {
        if (name.empty())
            return 0;

        auto hash = 5381u;

        for (auto i = 0u; i < name.size(); i++)
        {
            hash = std::tolower(static_cast<u8>(name[i])) + 33 * hash;
        }

        return hash;
    }
}

auto context::hash_name(u32 id) const -> std::string
{
    auto const itr = hash_map_.find(id);

    if (itr != hash_map_.end())
    {
        return std::string(itr->second);
    }

    return std::format("_id_{:08X}", id);
}

auto context::make_token(std::string_view str) const -> std::string
{
    if (str.starts_with("_id_") || str.starts_with("_func_") || str.starts_with("_meth_"))
    {
        return std::string{ str };
    }

    auto data = std::string{ str.begin(), str.end() };

    for (auto i = 0u; i < data.size(); i++)
    {
        data[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
        if (data[i] == '\\') data[i] = '/';
    }

    return data;
}

auto context::load_header(std::string const& name) -> std::tuple<std::string const*, char const*, usize>
{
    auto const itr = header_files_.find(name);

    if (itr != header_files_.end())
    {
        return { &itr->first, reinterpret_cast<char const*>(itr->second.data()), itr->second.size() };
    }

    auto data = fs_callback_(name);

    if (!data.empty())
    {
        auto const res = header_files_.insert({ name, std::move(data) });

        if (res.second)
        {
            return { &res.first->first, reinterpret_cast<char const*>(res.first->second.data()), res.first->second.size() };
        }
    }

    throw error(std::format("couldn't open gsh file '{}'", name));
}

extern std::array<std::pair<opcode, std::string_view>, opcode_count> const opcode_list
{{
    { opcode::OP_Invalid, "OP_Invalid"  },
    { opcode::OP_End, "OP_End"  },
    { opcode::OP_Return, "OP_Return"  },
    { opcode::OP_GetUndefined, "OP_GetUndefined"  },
    { opcode::OP_GetZero, "OP_GetZero"  },
    { opcode::OP_GetByte, "OP_GetByte"  },
    { opcode::OP_GetNegByte, "OP_GetNegByte"  },
    { opcode::OP_GetUnsignedShort, "OP_GetUnsignedShort"  },
    { opcode::OP_GetNegUnsignedShort, "OP_GetNegUnsignedShort"  },
    { opcode::OP_GetInteger, "OP_GetInteger"  },
    { opcode::OP_GetFloat, "OP_GetFloat"  },
    { opcode::OP_GetString, "OP_GetString"  },
    { opcode::OP_GetIString, "OP_GetIString"  },
    { opcode::OP_GetVector, "OP_GetVector"  },
    { opcode::OP_GetLevelObject, "OP_GetLevelObject"  },
    { opcode::OP_GetAnimObject, "OP_GetAnimObject"  },
    { opcode::OP_GetSelf, "OP_GetSelf"  },
    { opcode::OP_GetLevel, "OP_GetLevel"  },
    { opcode::OP_GetGame, "OP_GetGame"  },
    { opcode::OP_GetAnim, "OP_GetAnim"  },
    { opcode::OP_GetAnimation, "OP_GetAnimation"  },
    { opcode::OP_GetGameRef, "OP_GetGameRef"  },
    { opcode::OP_GetFunction, "OP_GetFunction"  },
    { opcode::OP_CreateLocalVariable, "OP_CreateLocalVariable"  },
    { opcode::OP_SafeCreateLocalVariables, "OP_SafeCreateLocalVariables"  },
    { opcode::OP_RemoveLocalVariables, "OP_RemoveLocalVariables"  },
    { opcode::OP_EvalLocalVariableCached, "OP_EvalLocalVariableCached"  },
    { opcode::OP_EvalArray, "OP_EvalArray"  },
    { opcode::OP_EvalLocalArrayRefCached, "OP_EvalLocalArrayRefCached"  },
    { opcode::OP_EvalArrayRef, "OP_EvalArrayRef"  },
    { opcode::OP_ClearArray, "OP_ClearArray"  },
    { opcode::OP_EmptyArray, "OP_EmptyArray"  },
    { opcode::OP_GetSelfObject, "OP_GetSelfObject"  },
    { opcode::OP_EvalFieldVariable, "OP_EvalFieldVariable"  },
    { opcode::OP_EvalFieldVariableRef, "OP_EvalFieldVariableRef"  },
    { opcode::OP_ClearFieldVariable, "OP_ClearFieldVariable"  },
    { opcode::OP_SafeSetVariableFieldCached, "OP_SafeSetVariableFieldCached"  },
    { opcode::OP_SafeSetWaittillVariableFieldCached, "OP_SafeSetWaittillVariableFieldCached"  },
    { opcode::OP_ClearParams, "OP_ClearParams"  },
    { opcode::OP_CheckClearParams, "OP_CheckClearParams"  },
    { opcode::OP_EvalLocalVariableRefCached, "OP_EvalLocalVariableRefCached"  },
    { opcode::OP_SetVariableField, "OP_SetVariableField"  },
    { opcode::OP_CallBuiltin, "OP_CallBuiltin"  },
    { opcode::OP_CallBuiltinMethod, "OP_CallBuiltinMethod"  },
    { opcode::OP_Wait, "OP_Wait"  },
    { opcode::OP_WaitTillFrameEnd, "OP_WaitTillFrameEnd"  },
    { opcode::OP_PreScriptCall, "OP_PreScriptCall"  },
    { opcode::OP_ScriptFunctionCall, "OP_ScriptFunctionCall"  },
    { opcode::OP_ScriptFunctionCallPointer, "OP_ScriptFunctionCallPointer"  },
    { opcode::OP_ScriptMethodCall, "OP_ScriptMethodCall"  },
    { opcode::OP_ScriptMethodCallPointer, "OP_ScriptMethodCallPointer"  },
    { opcode::OP_ScriptThreadCall, "OP_ScriptThreadCall"  },
    { opcode::OP_ScriptThreadCallPointer, "OP_ScriptThreadCallPointer"  },
    { opcode::OP_ScriptMethodThreadCall, "OP_ScriptMethodThreadCall"  },
    { opcode::OP_ScriptMethodThreadCallPointer, "OP_ScriptMethodThreadCallPointer"  },
    { opcode::OP_DecTop, "OP_DecTop"  },
    { opcode::OP_CastFieldObject, "OP_CastFieldObject"  },
    { opcode::OP_CastBool, "OP_CastBool"  },
    { opcode::OP_BoolNot, "OP_BoolNot"  },
    { opcode::OP_BoolComplement, "OP_BoolComplement"  },
    { opcode::OP_JumpOnFalse, "OP_JumpOnFalse"  },
    { opcode::OP_JumpOnTrue, "OP_JumpOnTrue"  },
    { opcode::OP_JumpOnFalseExpr, "OP_JumpOnFalseExpr"  },
    { opcode::OP_JumpOnTrueExpr, "OP_JumpOnTrueExpr"  },
    { opcode::OP_Jump, "OP_Jump"  },
    { opcode::OP_JumpBack, "OP_JumpBack"  },
    { opcode::OP_Inc, "OP_Inc"  },
    { opcode::OP_Dec, "OP_Dec"  },
    { opcode::OP_Bit_Or, "OP_Bit_Or"  },
    { opcode::OP_Bit_Xor, "OP_Bit_Xor"  },
    { opcode::OP_Bit_And, "OP_Bit_And"  },
    { opcode::OP_Equal, "OP_Equal"  },
    { opcode::OP_NotEqual, "OP_NotEqual"  },
    { opcode::OP_LessThan, "OP_LessThan"  },
    { opcode::OP_GreaterThan, "OP_GreaterThan"  },
    { opcode::OP_LessThanOrEqualTo, "OP_LessThanOrEqualTo"  },
    { opcode::OP_GreaterThanOrEqualTo, "OP_GreaterThanOrEqualTo"  },
    { opcode::OP_ShiftLeft, "OP_ShiftLeft"  },
    { opcode::OP_ShiftRight, "OP_ShiftRight"  },
    { opcode::OP_Plus, "OP_Plus"  },
    { opcode::OP_Minus, "OP_Minus"  },
    { opcode::OP_Multiply, "OP_Multiply"  },
    { opcode::OP_Divide, "OP_Divide"  },
    { opcode::OP_Modulus, "OP_Modulus"  },
    { opcode::OP_SizeOf, "OP_SizeOf"  },
    { opcode::OP_WaitTillMatch, "OP_WaitTillMatch"  },
    { opcode::OP_WaitTill, "OP_WaitTill"  },
    { opcode::OP_Notify, "OP_Notify"  },
    { opcode::OP_EndOn, "OP_EndOn"  },
    { opcode::OP_VoidCodePos, "OP_VoidCodePos"  },
    { opcode::OP_Switch, "OP_Switch"  },
    { opcode::OP_EndSwitch, "OP_EndSwitch"  },
    { opcode::OP_Vector, "OP_Vector"  },
    { opcode::OP_GetHash, "OP_GetHash"  },
    { opcode::OP_RealWait, "OP_RealWait"  },
    { opcode::OP_VectorConstant, "OP_VectorConstant"  },
    { opcode::OP_IsDefined, "OP_IsDefined"  },
    { opcode::OP_VectorScale, "OP_VectorScale"  },
    { opcode::OP_AnglesToUp, "OP_AnglesToUp"  },
    { opcode::OP_AnglesToRight, "OP_AnglesToRight"  },
    { opcode::OP_AnglesToForward, "OP_AnglesToForward"  },
    { opcode::OP_AngleClamp180, "OP_AngleClamp180"  },
    { opcode::OP_VectorToAngles, "OP_VectorToAngles"  },
    { opcode::OP_Abs, "OP_Abs"  },
    { opcode::OP_GetTime, "OP_GetTime"  },
    { opcode::OP_GetDvar, "OP_GetDvar"  },
    { opcode::OP_GetDvarInt, "OP_GetDvarInt"  },
    { opcode::OP_GetDvarFloat, "OP_GetDvarFloat"  },
    { opcode::OP_GetDvarVector, "OP_GetDvarVector"  },
    { opcode::OP_GetDvarColorRed, "OP_GetDvarColorRed"  },
    { opcode::OP_GetDvarColorGreen, "OP_GetDvarColorGreen"  },
    { opcode::OP_GetDvarColorBlue, "OP_GetDvarColorBlue"  },
    { opcode::OP_GetDvarColorAlpha, "OP_GetDvarColorAlpha"  },
    { opcode::OP_FirstArrayKey, "OP_FirstArrayKey"  },
    { opcode::OP_NextArrayKey, "OP_NextArrayKey"  },
    { opcode::OP_ProfileStart, "OP_ProfileStart"  },
    { opcode::OP_ProfileStop, "OP_ProfileStop"  },
    { opcode::OP_SafeDecTop, "OP_SafeDecTop"  },
    { opcode::OP_Nop, "OP_Nop"  },
    { opcode::OP_Abort, "OP_Abort"  },
    { opcode::OP_Object, "OP_Object"  },
    { opcode::OP_ThreadObject, "OP_ThreadObject"  },
    { opcode::OP_EvalLocalVariable, "OP_EvalLocalVariable"  },
    { opcode::OP_EvalLocalVariableRef, "OP_EvalLocalVariableRef"  },
    { opcode::OP_DevblockBegin, "OP_DevblockBegin"  },
    { opcode::OP_DevblockEnd, "OP_DevblockEnd"  },
    { opcode::OP_EvalLocalVariableCachedDebug, "OP_EvalLocalVariableCachedDebug"  },
    { opcode::OP_EvalLocalVariableRefCachedDebug, "OP_EvalLocalVariableRefCachedDebug"  },
    { opcode::OP_LevelEvalFieldVariable, "OP_LevelEvalFieldVariable"  },
    { opcode::OP_LevelEvalFieldVariableRef, "OP_LevelEvalFieldVariableRef"  },
    { opcode::OP_SelfEvalFieldVariable, "OP_SelfEvalFieldVariable"  },
    { opcode::OP_SelfEvalFieldVariableRef, "OP_SelfEvalFieldVariableRef"  },
    { opcode::OP_GetWorld, "OP_GetWorld"  },
    { opcode::OP_GetWorldObject, "OP_GetWorldObject"  },
    { opcode::OP_GetClasses, "OP_GetClasses"  },
    { opcode::OP_GetClassesObject, "OP_GetClassesObject"  },
    { opcode::OP_New, "OP_New"  },
    { opcode::OP_ScriptFunctionCallClass, "OP_ScriptFunctionCallClass"  },
    { opcode::OP_ScriptThreadCallClass, "OP_ScriptThreadCallClass"  },
    { opcode::OP_GetUintptr, "OP_GetUintptr"  },
    { opcode::OP_SuperEqual, "OP_SuperEqual"  },
    { opcode::OP_SuperNotEqual, "OP_SuperNotEqual"  },
    { opcode::OP_GetAPIFunction, "OP_GetAPIFunction"  },
}};

} // namespace xsk::arc
