// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "s4.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4244)
#endif

namespace xsk::gsc::s4
{

std::unordered_map<std::uint8_t, std::string_view> opcode_map;
std::unordered_map<std::uint16_t, std::string_view> function_map;
std::unordered_map<std::uint16_t, std::string_view> method_map;
std::unordered_map<std::uint32_t, std::string_view> token_map;
std::unordered_map<std::string_view, std::uint8_t> opcode_map_rev;
std::unordered_map<std::string_view, std::uint16_t> function_map_rev;
std::unordered_map<std::string_view, std::uint16_t> method_map_rev;
std::unordered_map<std::string_view, std::uint32_t> token_map_rev;
std::unordered_map<std::string, std::vector<std::uint8_t>> files;
read_cb_type read_callback = nullptr;
std::set<std::string> string_map;

void resolver::init(read_cb_type callback)
{
    read_callback = callback;
}

void resolver::cleanup()
{
    files.clear();
}

auto resolver::opcode_id(const std::string& name) -> std::uint8_t
{
    const auto itr = opcode_map_rev.find(name);

    if (itr != opcode_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("couldn't resolve opcode id for name '%s'!", name.data()));
}

auto resolver::opcode_name(std::uint8_t id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return std::string(itr->second);
    }

    throw error(utils::string::va("couldn't resolve opcode name for id '0x%hhX'!", id));
}

auto resolver::function_id(const std::string& name) -> std::uint16_t
{
    if (name.starts_with("_func_"))
    {
        return static_cast<std::uint16_t>(std::stoul(name.substr(6), nullptr, 16));
    }

    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("couldn't resolve builtin function id for name '%s'!", name.data()));
}

auto resolver::function_name(std::uint16_t id) -> std::string
{
    const auto itr = function_map.find(id);

    if (itr != function_map.end())
    {
        return std::string(itr->second);
    }

    return utils::string::va("_func_%04X", id);
}

auto resolver::method_id(const std::string& name) -> std::uint16_t
{
    if (name.starts_with("_meth_"))
    {
        return static_cast<std::uint16_t>(std::stoul(name.substr(6), nullptr, 16));
    }

    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("couldn't resolve builtin method id for name '%s'!", name.data()));
}

auto resolver::method_name(std::uint16_t id) -> std::string
{
    const auto itr = method_map.find(id);

    if (itr != method_map.end())
    {
        return std::string(itr->second);
    }

    return utils::string::va("_meth_%04X", id);
}

auto resolver::token_id(const std::string& name) -> std::uint32_t
{
    if (name.starts_with("_id_"))
    {
        return static_cast<std::uint32_t>(std::stoul(name.substr(4), nullptr, 16));
    }

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
        return std::string(itr->second);
    }

    return utils::string::va("_id_%04X", id);
}

auto resolver::find_function(const std::string& name) -> bool
{
    if (name.starts_with("_func_")) return true;

    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        return true;
    }

    return false;
}

auto resolver::find_method(const std::string& name) -> bool
{
    if (name.starts_with("_meth_")) return true;

    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        return true;
    }

    return false;
}

void resolver::add_function(const std::string& name, std::uint16_t id)
{
    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        throw error(utils::string::va("builtin function '%s' already defined.", name.data()));
    }

    const auto str = string_map.find(name);

    if (str != string_map.end())
    {
        function_map.insert({ id, *str });
        function_map_rev.insert({ *str, id });
    }
    else
    {
        auto ins = string_map.insert(name);

        if (ins.second)
        {
            function_map.insert({ id, *ins.first });
            function_map_rev.insert({ *ins.first, id });
        }
    }
}

void resolver::add_method(const std::string& name, std::uint16_t id)
{
    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        throw error(utils::string::va("builtin method '%s' already defined.", name.data()));
    }

    const auto str = string_map.find(name);

    if (str != string_map.end())
    {
        method_map.insert({ id, *str });
        method_map_rev.insert({ *str, id });
    }
    else
    {
        auto ins = string_map.insert(name);

        if (ins.second)
        {
            method_map.insert({ id, *ins.first });
            method_map_rev.insert({ *ins.first, id });
        }
    }
}

auto resolver::make_token(std::string_view str) -> std::string
{
    if (str.starts_with("_id_") || str.starts_with("_func_") || str.starts_with("_meth_"))
    {
        return std::string(str);
    }

    auto data = std::string(str.begin(), str.end());

    for (std::size_t i = 0; i < data.size(); i++)
    {
        data[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
        if (data[i] == '\\') data[i] = '/';
    }

    return data;
}

auto resolver::file_data(const std::string& name) -> std::tuple<const std::string*, const char*, size_t>
{
    const auto itr = files.find(name);

    if (itr != files.end())
    {
        return { &itr->first ,reinterpret_cast<const char*>(itr->second.data()), itr->second.size() };
    }

    auto data = read_callback(name);

    const auto res = files.insert({ name, std::move(data)});

    if (res.second)
    {
        return { &res.first->first, reinterpret_cast<const char*>(res.first->second.data()), res.first->second.size() };
    }

    throw error("couldn't open gsc file '" + name + "'");
}

std::set<std::string_view> paths
{
};

auto resolver::fs_to_game_path(const std::filesystem::path& file) -> std::filesystem::path
{
    auto result = std::filesystem::path();
    auto root = false;

    for (auto& entry : file)
    {
        if (!root && paths.contains(entry.string()))
        {
            result = entry;
            root = true;
        }
        else if (paths.contains(result.string()))
        {
            result /= entry;
        }
    }

    return result.empty() ? file : result;
}

const std::array<std::pair<std::uint8_t, const char*>, 190> opcode_list
{{
    { 0x0, "OP_CastFieldObject" },
    { 0x1, "OP_SetLocalVariableFieldCached" },
    { 0x2, "OP_plus" },
    { 0x3, "OP_RemoveLocalVariables" },
    { 0x4, "OP_EvalSelfFieldVariableRef" },
    { 0x5, "OP_ScriptFarMethodChildThreadCall" },
    { 0x6, "OP_GetGameRef" },
    { 0x7, "OP_EvalAnimFieldVariable" },
    { 0x8, "OP_EvalLevelFieldVariableRef" },
    { 0x9, "OP_GetThisthread" },
    { 0xA, "OP_greater" },
    { 0xB, "OP_waittillmatch" },
    { 0xC, "OP_shift_right" },
    { 0xD, "OP_dec" },
    { 0xE, "OP_JumpOnTrue" },
    { 0xF, "OP_bit_or" },
    { 0x10, "OP_equality" },
    { 0x11, "OP_ClearLocalVariableFieldCached0" },
    { 0x12, "OP_notify" },
    { 0x13, "OP_GetVector" },
    { 0x14, "OP_ScriptMethodChildThreadCallPointer" },
    { 0x15, "OP_PreScriptCall" },
    { 0x16, "OP_GetByte" },
    { 0x17, "OP_ScriptFarThreadCall" },
    { 0x18, "OP_SetSelfFieldVariableField" },
    { 0x19, "OP_JumpOnFalseExpr" },
    { 0x1A, "OP_GetUndefined" },
    { 0x1B, "OP_jumpback" },
    { 0x1C, "OP_JumpOnTrueExpr" },
    { 0x1D, "OP_CallBuiltin0" },
    { 0x1E, "OP_CallBuiltin1" },
    { 0x1F, "OP_CallBuiltin2" },
    { 0x20, "OP_CallBuiltin3" },
    { 0x21, "OP_CallBuiltin4" },
    { 0x22, "OP_CallBuiltin5" },
    { 0x23, "OP_CallBuiltin" },
    { 0x24, "OP_SetLocalVariableFieldCached0" },
    { 0x25, "OP_ClearFieldVariable" },
    { 0x26, "OP_GetLevel" },
    { 0x27, "OP_size" },
    { 0x28, "OP_SafeSetWaittillVariableFieldCached" },
    { 0x29, "OP_ScriptLocalMethodThreadCall" },
    { 0x2A, "OP_AddArray" },
    { 0x2B, "OP_endon" },
    { 0x2C, "OP_EvalFieldVariable" },
    { 0x2D, "OP_shift_left" },
    { 0x2E, "OP_EvalLocalArrayRefCached0" },
    { 0x2F, "OP_Return" },
    { 0x30, "OP_CreateLocalVariable" },
    { 0x31, "OP_SafeSetVariableFieldCached0" },
    { 0x32, "OP_GetBuiltinFunction" },
    { 0x33, "OP_ScriptLocalMethodCall" },
    { 0x34, "OP_CallBuiltinMethodPointer" },
    { 0x35, "OP_ScriptLocalChildThreadCall" },
    { 0x36, "OP_GetSelfObject" },
    { 0x37, "OP_GetGame" },
    { 0x38, "OP_SetLevelFieldVariableField" },
    { 0x39, "OP_EvalArray" },
    { 0x3A, "OP_GetSelf" },
    { 0x3B, "OP_End" },
    { 0x3C, "OP_EvalSelfFieldVariable" },
    { 0x3D, "OP_less_equal" },
    { 0x3E, "OP_EvalLocalVariableCached0" },
    { 0x3F, "OP_EvalLocalVariableCached1" },
    { 0x40, "OP_EvalLocalVariableCached2" },
    { 0x41, "OP_EvalLocalVariableCached3" },
    { 0x42, "OP_EvalLocalVariableCached4" },
    { 0x43, "OP_EvalLocalVariableCached5" },
    { 0x44, "OP_EvalLocalVariableCached" },
    { 0x45, "OP_EvalNewLocalArrayRefCached0" },
    { 0x46, "OP_ScriptChildThreadCallPointer" },
    { 0x47, "OP_EvalLocalVariableObjectCached" },
    { 0x48, "OP_ScriptLocalThreadCall" },
    { 0x49, "OP_GetInteger" },
    { 0x4A, "OP_ScriptMethodCallPointer" },
    { 0x4B, "OP_checkclearparams" },
    { 0x4C, "OP_SetAnimFieldVariableField" },
    { 0x4D, "OP_waittillmatch2" },
    { 0x4E, "OP_minus" },
    { 0x4F, "OP_ScriptLocalFunctionCall2" },
    { 0x50, "OP_GetNegUnsignedShort" },
    { 0x51, "OP_GetNegByte" },
    { 0x52, "OP_SafeCreateVariableFieldCached" },
    { 0x53, "OP_greater_equal" },
    { 0x54, "OP_vector" },
    { 0x55, "OP_GetBuiltinMethod" },
    { 0x56, "OP_endswitch" },
    { 0x57, "OP_ClearArray" },
    { 0x58, "OP_DecTop" },
    { 0x59, "OP_CastBool" },
    { 0x5A, "OP_EvalArrayRef" },
    { 0x5B, "OP_SetNewLocalVariableFieldCached0" },
    { 0x5C, "OP_GetZero" },
    { 0x5D, "OP_wait" },
    { 0x5E, "OP_waittill" },
    { 0x5F, "OP_GetIString" },
    { 0x60, "OP_ScriptFarFunctionCall" },
    { 0x61, "OP_GetAnimObject" },
    { 0x62, "OP_GetAnimTree" },
    { 0x63, "OP_EvalLocalArrayCached" },
    { 0x64, "OP_mod" },
    { 0x65, "OP_ScriptFarMethodThreadCall" },
    { 0x66, "OP_GetUnsignedShort" },
    { 0x67, "OP_clearparams" },
    { 0x68, "OP_ScriptMethodThreadCallPointer" },
    { 0x69, "OP_ScriptFunctionCallPointer" },
    { 0x6A, "OP_EmptyArray" },
    { 0x6B, "OP_SafeSetVariableFieldCached" },
    { 0x6C, "OP_ClearVariableField" },
    { 0x6D, "OP_EvalFieldVariableRef" },
    { 0x6E, "OP_ScriptLocalMethodChildThreadCall" },
    { 0x6F, "OP_EvalNewLocalVariableRefCached0" },
    { 0x70, "OP_GetFloat" },
    { 0x71, "OP_EvalLocalVariableRefCached" },
    { 0x72, "OP_JumpOnFalse" },
    { 0x73, "OP_BoolComplement" },
    { 0x74, "OP_ScriptThreadCallPointer" },
    { 0x75, "OP_ScriptFarFunctionCall2" },
    { 0x76, "OP_less" },
    { 0x77, "OP_BoolNot" },
    { 0x78, "OP_waittillFrameEnd" },
    { 0x79, "OP_waitframe" },
    { 0x7A, "OP_GetString" },
    { 0x7B, "OP_EvalLevelFieldVariable" },
    { 0x7C, "OP_GetLevelObject" },
    { 0x7D, "OP_inc" },
    { 0x7E, "OP_CallBuiltinMethod0" },
    { 0x7F, "OP_CallBuiltinMethod1" },
    { 0x80, "OP_CallBuiltinMethod2" },
    { 0x81, "OP_CallBuiltinMethod3" },
    { 0x82, "OP_CallBuiltinMethod4" },
    { 0x83, "OP_CallBuiltinMethod5" },
    { 0x84, "OP_CallBuiltinMethod" },
    { 0x85, "OP_GetAnim" },
    { 0x86, "OP_switch" },
    { 0x87, "OP_SetVariableField" },
    { 0x88, "OP_divide" },
    { 0x89, "OP_GetLocalFunction" },
    { 0x8A, "OP_ScriptFarChildThreadCall" },
    { 0x8B, "OP_multiply" },
    { 0x8C, "OP_ClearLocalVariableFieldCached" },
    { 0x8D, "OP_EvalAnimFieldVariableRef" },
    { 0x8E, "OP_EvalLocalArrayRefCached" },
    { 0x8F, "OP_EvalLocalVariableRefCached0" },
    { 0x90, "OP_bit_and" },
    { 0x91, "OP_GetAnimation" },
    { 0x92, "OP_GetFarFunction" },
    { 0x93, "OP_CallBuiltinPointer" },
    { 0x94, "OP_jump" },
    { 0x95, "OP_voidCodepos" },
    { 0x96, "OP_ScriptFarMethodCall" },
    { 0x97, "OP_inequality" },
    { 0x98, "OP_ScriptLocalFunctionCall" },
    { 0x99, "OP_bit_ex_or" },
    { 0x9A, "OP_NOP" },
    { 0x9B, "OP_abort" },
    { 0x9C, "OP_object" },
    { 0x9D, "OP_thread_object" },
    { 0x9E, "OP_EvalLocalVariable" },
    { 0x9F, "OP_EvalLocalVariableRef" },
    { 0xA0, "OP_prof_begin" },
    { 0xA1, "OP_prof_end" },
    { 0xA2, "OP_breakpoint" },
    { 0xA3, "OP_assignmentBreakpoint" },
    { 0xA4, "OP_manualAndAssignmentBreakpoint" },
    { 0xA5, "OP_BoolNotAfterAnd" },
    { 0xA6, "OP_FormalParams" },
    { 0xA7, "OP_IsDefined" },
    { 0xA8, "OP_IsTrue" },
    { 0xA9, "OP_NativeGetLocalFunction" },
    { 0xAA, "OP_NativeLocalFunctionCall" },
    { 0xAB, "OP_NativeLocalFunctionCall2" },
    { 0xAC, "OP_NativeLocalMethodCall" },
    { 0xAD, "OP_NativeLocalFunctionThreadCall" },
    { 0xAE, "OP_NativeLocalMethodThreadCall" },
    { 0xAF, "OP_NativeLocalFunctionChildThreadCall" },
    { 0xB0, "OP_NativeLocalMethodChildThreadCall" },
    { 0xB1, "OP_NativeGetFarFunction" },
    { 0xB2, "OP_NativeFarFunctionCall" },
    { 0xB3, "OP_NativeFarFunctionCall2" },
    { 0xB4, "OP_NativeFarMethodCall" },
    { 0xB5, "OP_NativeFarFunctionThreadCall" },
    { 0xB6, "OP_NativeFarMethodThreadCall" },
    { 0xB7, "OP_NativeFarFunctionChildThreadCall" },
    { 0xB8, "OP_NativeFarMethodChildThreadCall" },
    { 0xB9, "OP_EvalNewLocalArrayRefCached0_Precompiled" },
    { 0xBA, "OP_SetNewLocalVariableFieldCached0_Precompiled" },
    { 0xBB, "OP_CreateLocalVariable_Precompiled" },
    { 0xBC, "OP_SafeCreateVariableFieldCached_Precompiled" },
    { 0xBD, "OP_FormalParams_Precompiled" },
}};

const std::array<std::pair<std::uint16_t, const char*>, 4> function_list
{{
    { 0x08F, "getdvar" },
    { 0x09B, "getfirstarraykey" },
    { 0x0B1, "getnextarraykey" },
    { 0x126, "isusingmatchrulesdata" },
}};
const std::array<std::pair<std::uint16_t, const char*>, 1> method_list
{{
    { 0x0, "null" },
}};

const std::array<std::pair<std::uint32_t, const char*>, 5> token_list
{{
    { 0x00, "" },
    { 0x01, "pl#" },
    { 0x02, "-" },
    { 0x03, "radius`" },
    { 0x04, "note:" },
}};

struct __init__
{
    __init__()
    {
        static bool init = false;
        if (init) return;
        init = true;

        opcode_map.reserve(opcode_list.size());
        opcode_map_rev.reserve(opcode_list.size());
        function_map.reserve(function_list.size());
        function_map_rev.reserve(function_list.size());
        method_map.reserve(method_list.size());
        method_map_rev.reserve(method_list.size());
        token_map.reserve(token_list.size());
        token_map_rev.reserve(token_list.size());

        for (const auto& entry : opcode_list)
        {
            opcode_map.insert({ entry.first, entry.second });
            opcode_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : function_list)
        {
            function_map.insert({ entry.first, entry.second });
            function_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : method_list)
        {
            method_map.insert({ entry.first, entry.second });
            method_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : token_list)
        {
            token_map.insert({ entry.first, entry.second });
            token_map_rev.insert({ entry.second, entry.first });
        }
    }
};

__init__ _;

} // namespace xsk::gsc::s4

#ifdef _MSC_VER
#pragma warning(pop)
#endif
