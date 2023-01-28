// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"
#include "context.hpp"

namespace xsk::gsc
{

read_cb_type read_callback = nullptr;
std::unordered_map<std::string, buffer> header_files;
std::set<std::string_view> includes;
std::unordered_map<std::string, std::vector<std::string>> include_cache;
std::set<std::string> new_func_map;
std::set<std::string> new_meth_map;

context::context(gsc::props props, gsc::engine engine, gsc::endian endian, gsc::system system, u32 str_count)
    : props_{ props }, engine_{ engine }, endian_{ endian }, system_{ system }, str_count_{ str_count },
      source_{ this }, assembler_{ this }, disassembler_{ this }, compiler_{ this }, decompiler_{ this }
{
}

auto context::init(gsc::build build, read_cb_type callback) -> void
{
    build_ = build;
    read_callback = callback;
}

auto context::cleanup() -> void
{
    header_files.clear();
    include_cache.clear();
    includes.clear();
}

auto context::opcode_size(opcode op) const -> u32
{
    switch (op)
    {
        case opcode::OP_CastFieldObject:
        case opcode::OP_plus:
        case opcode::OP_GetGameRef:
        case opcode::OP_GetThisthread:
        case opcode::OP_greater:
        case opcode::OP_shift_right:
        case opcode::OP_dec:
        case opcode::OP_bit_or:
        case opcode::OP_equality:
        case opcode::OP_ClearLocalVariableFieldCached0:
        case opcode::OP_notify:
        case opcode::OP_PreScriptCall:
        case opcode::OP_GetUndefined:
        case opcode::OP_SetLocalVariableFieldCached0:
        case opcode::OP_GetLevel:
        case opcode::OP_size:
        case opcode::OP_AddArray:
        case opcode::OP_endon:
        case opcode::OP_shift_left:
        case opcode::OP_EvalLocalArrayRefCached0:
        case opcode::OP_Return:
        case opcode::OP_SafeSetVariableFieldCached0:
        case opcode::OP_GetSelfObject:
        case opcode::OP_GetGame:
        case opcode::OP_EvalArray:
        case opcode::OP_GetSelf:
        case opcode::OP_End:
        case opcode::OP_less_equal:
        case opcode::OP_EvalLocalVariableCached0:
        case opcode::OP_EvalLocalVariableCached1:
        case opcode::OP_EvalLocalVariableCached2:
        case opcode::OP_EvalLocalVariableCached3:
        case opcode::OP_EvalLocalVariableCached4:
        case opcode::OP_EvalLocalVariableCached5:
        case opcode::OP_ScriptMethodCallPointer:
        case opcode::OP_checkclearparams:
        case opcode::OP_waittillmatch2:
        case opcode::OP_minus:
        case opcode::OP_greater_equal:
        case opcode::OP_vector:
        case opcode::OP_ClearArray:
        case opcode::OP_DecTop:
        case opcode::OP_CastBool:
        case opcode::OP_EvalArrayRef:
        case opcode::OP_GetZero:
        case opcode::OP_wait:
        case opcode::OP_waittill:
        case opcode::OP_GetAnimObject:
        case opcode::OP_mod:
        case opcode::OP_clearparams:
        case opcode::OP_ScriptFunctionCallPointer:
        case opcode::OP_EmptyArray:
        case opcode::OP_BoolComplement:
        case opcode::OP_less:
        case opcode::OP_BoolNot:
        case opcode::OP_waittillFrameEnd:
        case opcode::OP_waitframe:
        case opcode::OP_GetLevelObject:
        case opcode::OP_inc:
        case opcode::OP_GetAnim:
        case opcode::OP_SetVariableField:
        case opcode::OP_divide:
        case opcode::OP_multiply:
        case opcode::OP_EvalLocalVariableRefCached0:
        case opcode::OP_bit_and:
        case opcode::OP_voidCodepos:
        case opcode::OP_inequality:
        case opcode::OP_bit_ex_or:
        case opcode::OP_BoolNotAfterAnd:
        case opcode::OP_IsDefined:
        case opcode::OP_IsTrue:
            return 1;
        case opcode::OP_SetLocalVariableFieldCached:
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_waittillmatch:
        case opcode::OP_ScriptMethodChildThreadCallPointer:
        case opcode::OP_GetByte:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_CallBuiltinMethodPointer:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_ScriptChildThreadCallPointer:
        case opcode::OP_EvalLocalVariableObjectCached:
        case opcode::OP_GetNegByte:
        case opcode::OP_GetAnimTree:
        case opcode::OP_EvalLocalArrayCached:
        case opcode::OP_ScriptMethodThreadCallPointer:
        case opcode::OP_SafeSetVariableFieldCached:
        case opcode::OP_EvalLocalVariableRefCached:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ClearLocalVariableFieldCached:
        case opcode::OP_EvalLocalArrayRefCached:
        case opcode::OP_CallBuiltinPointer:
        case opcode::OP_FormalParams:
            return 2;
        case opcode::OP_JumpOnTrue:
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_jumpback:
        case opcode::OP_JumpOnTrueExpr:
        case opcode::OP_CallBuiltin0:
        case opcode::OP_CallBuiltin1:
        case opcode::OP_CallBuiltin2:
        case opcode::OP_CallBuiltin3:
        case opcode::OP_CallBuiltin4:
        case opcode::OP_CallBuiltin5:
        case opcode::OP_GetBuiltinFunction:
        case opcode::OP_GetNegUnsignedShort:
        case opcode::OP_GetBuiltinMethod:
        case opcode::OP_endswitch:
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_JumpOnFalse:
        case opcode::OP_CallBuiltinMethod0:
        case opcode::OP_CallBuiltinMethod1:
        case opcode::OP_CallBuiltinMethod2:
        case opcode::OP_CallBuiltinMethod3:
        case opcode::OP_CallBuiltinMethod4:
        case opcode::OP_CallBuiltinMethod5:
            return 3;
        case opcode::OP_CallBuiltin:
        case opcode::OP_ScriptLocalMethodCall:
        case opcode::OP_ScriptLocalFunctionCall2:
        case opcode::OP_ScriptFarFunctionCall2:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_GetLocalFunction:
        case opcode::OP_ScriptLocalFunctionCall:
            return 4;
        case opcode::OP_ScriptLocalMethodThreadCall:
        case opcode::OP_ScriptLocalChildThreadCall:
        case opcode::OP_ScriptLocalThreadCall:
        case opcode::OP_GetInteger:
        case opcode::OP_ScriptLocalMethodChildThreadCall:
        case opcode::OP_GetFloat:
        case opcode::OP_switch:
        case opcode::OP_jump:
        case opcode::OP_GetUnkxHash:
        case opcode::OP_GetUnsignedInt:
        case opcode::OP_GetNegUnsignedInt:
            return 5;
        case opcode::OP_GetStatHash:
        case opcode::OP_GetEnumHash:
        case opcode::OP_GetDvarHash:
        case opcode::OP_GetInteger64:
            return 9;
        case opcode::OP_GetFarFunction:
        case opcode::OP_ScriptFarFunctionCall:
        case opcode::OP_ScriptFarMethodCall:
            return (props_ & props::farcall) ? 5 : 4;
        case opcode::OP_ScriptFarThreadCall:
        case opcode::OP_ScriptFarChildThreadCall:
        case opcode::OP_ScriptFarMethodThreadCall:
        case opcode::OP_ScriptFarMethodChildThreadCall:
            return (props_ & props::farcall) ? 6 : 5;
        case opcode::OP_CreateLocalVariable:
        case opcode::OP_EvalNewLocalArrayRefCached0:
        case opcode::OP_SafeCreateVariableFieldCached:
        case opcode::OP_SetNewLocalVariableFieldCached0:
            return (props_ & props::hash) ? 9 : 2;
        case opcode::OP_EvalSelfFieldVariableRef:
        case opcode::OP_EvalAnimFieldVariable:
        case opcode::OP_EvalLevelFieldVariableRef:
        case opcode::OP_SetSelfFieldVariableField:
        case opcode::OP_ClearFieldVariable:
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_SetAnimFieldVariableField:
        case opcode::OP_SetLevelFieldVariableField:
        case opcode::OP_EvalSelfFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_EvalLevelFieldVariable:
        case opcode::OP_EvalAnimFieldVariableRef:
            return (props_ & props::hash) ? 9 : (props_ & props::tok4) ? 5 : 3;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            return (props_ & props::str4) ? 5 : 3;
        case opcode::OP_GetAnimation:
            return (props_ & props::str4) ? 9 : 5;
        case opcode::OP_GetVector:
            return 13;
        case opcode::OP_ClearVariableField:
        case opcode::OP_EvalNewLocalVariableRefCached0:
        case opcode::OP_NOP:
        case opcode::OP_abort:
        case opcode::OP_object:
        case opcode::OP_thread_object:
        case opcode::OP_EvalLocalVariable:
        case opcode::OP_EvalLocalVariableRef:
        case opcode::OP_breakpoint:
        case opcode::OP_assignmentBreakpoint:
        case opcode::OP_manualAndAssignmentBreakpoint:
        case opcode::OP_prof_begin:
        case opcode::OP_prof_end:
        case opcode::OP_NativeGetLocalFunction:
        case opcode::OP_NativeLocalFunctionCall:
        case opcode::OP_NativeLocalFunctionCall2:
        case opcode::OP_NativeLocalMethodCall:
        case opcode::OP_NativeGetFarFunction:
        case opcode::OP_NativeFarFunctionCall:
        case opcode::OP_NativeFarFunctionCall2:
        case opcode::OP_NativeFarMethodCall:
        case opcode::OP_NativeLocalFunctionThreadCall:
        case opcode::OP_NativeLocalMethodThreadCall:
        case opcode::OP_NativeLocalFunctionChildThreadCall:
        case opcode::OP_NativeLocalMethodChildThreadCall:
        case opcode::OP_NativeFarFunctionThreadCall:
        case opcode::OP_NativeFarMethodThreadCall:
        case opcode::OP_NativeFarFunctionChildThreadCall:
        case opcode::OP_NativeFarMethodChildThreadCall:
        case opcode::OP_EvalNewLocalArrayRefCached0_Precompiled:
        case opcode::OP_SetNewLocalVariableFieldCached0_Precompiled:
        case opcode::OP_CreateLocalVariable_Precompiled:
        case opcode::OP_SafeCreateVariableFieldCached_Precompiled:
        case opcode::OP_FormalParams_Precompiled:
        case opcode::OP_iw9_139:
        case opcode::OP_iw9_140:
        case opcode::OP_iw9_141:
        case opcode::OP_iw9_142:
        case opcode::OP_iw9_143:
        case opcode::OP_iw9_144:
        case opcode::OP_iw9_166:
        default:
            throw error(fmt::format("couldn't resolve instruction size for '{}'", opcode_name(op)));
    }
}

auto context::opcode_id(opcode op) const -> u8
{
    auto const itr = code_map_rev_.find(op);

    if (itr != code_map_rev_.end())
    {
        return itr->second;
    }

    throw error(fmt::format("couldn't resolve opcode id for '{}'", opcode_name(op)));
}

auto context::opcode_enum(u8 id) const -> opcode
{
    auto const itr = code_map_.find(id);

    if (itr != code_map_.end())
    {
        return itr->second;
    }

    throw error(fmt::format("couldn't resolve opcode enum for '{:02X}'", id));
}

auto context::func_id(std::string const& name) const -> u16
{
    if (name.starts_with("_func_"))
    {
        return static_cast<u16>(std::stoul(name.substr(6), nullptr, 16));
    }

    auto const itr = func_map_rev_.find(name);

    if (itr != func_map_rev_.end())
    {
        return itr->second;
    }

    throw error(fmt::format("couldn't resolve builtin function id for {}", name));
}

auto context::func_name(u16 id) const -> std::string
{
    auto const itr = func_map_.find(id);

    if (itr != func_map_.end())
    {
        return std::string{ itr->second };
    }

    return fmt::format("_func_{:04X}", id);
}

auto context::func_exists(std::string const& name) const -> bool
{
    if (name.starts_with("_func_")) return true;

    auto const itr = func_map_rev_.find(name);

    if (itr != func_map_rev_.end())
    {
        return true;
    }

    return false;
}

auto context::func_add(std::string const& name, u16 id) -> void
{
    auto const itr = func_map_rev_.find(name);

    if (itr != func_map_rev_.end())
    {
        throw error(fmt::format("builtin function '{}' already defined", name));
    }

    auto const str = new_func_map.find(name);

    if (str != new_func_map.end())
    {
        func_map_.insert({ id, *str });
        func_map_rev_.insert({ *str, id });
    }
    else
    {
        auto ins = new_func_map.insert(name);

        if (ins.second)
        {
            func_map_.insert({ id, *ins.first });
            func_map_rev_.insert({ *ins.first, id });
        }
    }
}

auto context::meth_id(std::string const& name) const -> u16
{
    if (name.starts_with("_meth_"))
    {
        return static_cast<u16>(std::stoul(name.substr(6), nullptr, 16));
    }

    auto const itr = meth_map_rev_.find(name);

    if (itr != meth_map_rev_.end())
    {
        return itr->second;
    }

    throw error(fmt::format("couldn't resolve builtin method id for {}", name));
}

auto context::meth_name(u16 id) const -> std::string
{
    auto const itr = meth_map_.find(id);

    if (itr != meth_map_.end())
    {
        return std::string{ itr->second };
    }

    return fmt::format("_meth_{:04X}", id);
}

auto context::meth_exists(std::string const& name) const -> bool
{
    if (name.starts_with("_meth_")) return true;

    auto const itr = meth_map_rev_.find(name);

    if (itr != meth_map_rev_.end())
    {
        return true;
    }

    return false;
}

auto context::meth_add(std::string const& name, u16 id) -> void
{
    auto const itr = meth_map_rev_.find(name);

    if (itr != meth_map_rev_.end())
    {
        throw error(fmt::format("builtin method '{}' already defined", name));
    }

    auto const str = new_meth_map.find(name);

    if (str != new_meth_map.end())
    {
        meth_map_.insert({ id, *str });
        meth_map_rev_.insert({ *str, id });
    }
    else
    {
        auto ins = new_meth_map.insert(name);

        if (ins.second)
        {
            meth_map_.insert({ id, *ins.first });
            meth_map_rev_.insert({ *ins.first, id });
        }
    }
}

auto context::token_id(std::string const& name) const -> u32
{
    if (name.starts_with("_id_"))
    {
        return static_cast<u32>(std::stoul(name.substr(4), nullptr, 16));
    }

    auto const itr = token_map_rev_.find(name);

    if (itr != token_map_rev_.end())
    {
        return itr->second;
    }

    return 0;
}

auto context::token_name(u32 id) const -> std::string
{
    auto const itr = token_map_.find(id);

    if (itr != token_map_.end())
    {
        return std::string{ itr->second };
    }

    return fmt::format("_id_{:04X}", id);
}

auto context::path_id(std::string const& name) const -> u64
{
    if (name.starts_with("_id_"))
    {
        return static_cast<u64>(std::stoull(name.substr(4), nullptr, 16));
    }

    char const* str = name.data();
    u64 hash = 0x47F5817A5EF961BA;

    while ( *str )
    {
        u8 byte = *str++;

        if (byte == '\\')
        {
            byte = '/';
        }
        else if (static_cast<u8>(byte - 65) <= 25)
        {
            byte += 32;
        }

        hash = (u64)0x100000001B3 * ((u64)byte ^ hash);
    }

    return hash & 0x7FFFFFFFFFFFFFFF;
}

auto context::path_name(u64 id) const -> std::string
{
    auto const itr = path_map_.find(id);

    if (itr != path_map_.end())
    {
        return std::string{ itr->second };
    }

    return fmt::format("_id_{:016X}", id);
}

auto context::hash_id(std::string const& name) const -> u64
{
    if (name.starts_with("_id_"))
    {
        return static_cast<u64>(std::stoull(name.substr(4), nullptr, 16));
    }

    char const* str = name.data();
    u64 hash = 0x79D6530B0BB9B5D1;
    
    while ( *str )
    {
        u8 byte = *str++;

        if (static_cast<u8>(byte - 65) <= 25)
        {
            byte += 32;
        }

        hash = (u64)0x10000000233 * ((u64)byte ^ hash);
    }

    return hash;
}

auto context::hash_name(u64 id) const -> std::string
{
   auto const itr = hash_map_.find(id);

    if (itr != hash_map_.end())
    {
        return std::string{ itr->second };
    }

    return fmt::format("_id_{:016X}", id);
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

auto context::header_file_data(std::string const& name) const -> std::tuple<std::string const*, char const*, usize>
{
    auto const itr = header_files.find(name);

    if (itr != header_files.end())
    {
        return { &itr->first, reinterpret_cast<char const*>(itr->second.data), itr->second.size };
    }

    auto data = read_callback(name);

    if (data.first.data != nullptr && data.first.size != 0 && data.second.data == nullptr && data.second.size == 0)
    {
        auto const res = header_files.insert({ name, data.first });

        if (res.second)
        {
            return { &res.first->first, reinterpret_cast<char const*>(res.first->second.data), res.first->second.size };
        }
    }

    throw error(fmt::format("couldn't open gsh file '{}'", name));
}

auto context::load_include(std::string const& name) -> bool
{
    try
    { 
        if (includes.contains(name))
        {
            return false;
        }

        includes.insert(name);

        if (include_cache.contains(name))
            return true;

        auto file = read_callback(name);

        if (file.first.data == nullptr && file.first.size == 0)
            throw std::runtime_error("empty file");

        if (file.second.data == nullptr && file.second.size == 0)
        {
            // process RawFile
            auto prog = source_.parse_program(name, file.first);

            auto funcs = std::vector<std::string>{};

            for (auto const& dec : prog->declarations)
            {
                if (dec == node::decl_function)
                {
                    funcs.push_back(dec.as_function->name->value);
                }
            }

            include_cache.insert({ name, std::move(funcs) });
        }
        else
        {
            // process ScriptFile
            auto data = disassembler_.disassemble(file.first, file.second);

            auto funcs = std::vector<std::string>{};

            for (auto const& fun : data->functions)
            {
                funcs.push_back(fun->name);
            }

            include_cache.insert({ name, std::move(funcs) });
        }

        return true;
    }
    catch (std::exception const& e)
    {
        throw error(fmt::format("parsing include file '{}': {}", name, e.what()));
    }
}

auto context::init_includes() -> void
{
    includes.clear();
}

auto context::is_includecall(std::string const& name, std::string& path) -> bool
{
    for (auto const& inc : includes)
    {
        for (auto const& fun : include_cache.at(std::string{ inc }))
        {
            if (name == fun)
            {
                path = inc;
                return true;
            }
        }
    }

    return false;
}

} // namespace xsk::gsc
