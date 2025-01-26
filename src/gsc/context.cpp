// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc
{

extern std::array<std::pair<opcode, std::string_view>, opcode_count> const opcode_list;

context::context(gsc::props props, gsc::engine engine, gsc::endian endian, gsc::system system, gsc::instance inst, u32 str_count)
    : props_{ props }, engine_{ engine }, endian_{ endian }, system_{ system }, instance_{ inst }, str_count_{ str_count },
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

auto context::init(gsc::build build, fs_callback callback) -> void
{
    build_ = build;
    fs_callback_ = callback;
}

auto context::cleanup() -> void
{
    header_files_.clear();
    include_cache_.clear();
    includes_.clear();
}

auto context::engine_name() const -> std::string_view
{
    switch (engine_)
    {
        case engine::iw5: return "IW5";
        case engine::iw6: return "IW6";
        case engine::iw7: return "IW7";
        case engine::iw8: return "IW8";
        case engine::iw9: return "IW9";
        case engine::s1: return "S1";
        case engine::s2: return "S2";
        case engine::s4: return "S4";
        case engine::h1: return "H1";
        case engine::h2: return "H2";
    }

    return "";
}

auto context::opcode_size(opcode op) const -> usize
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
            throw error(std::format("couldn't resolve instruction size for '{}'", opcode_name(op)));
    }
}

auto context::opcode_id(opcode op) const -> u8
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

auto context::opcode_enum(u8 id) const -> opcode
{
    auto const itr = code_map_.find(id);

    if (itr != code_map_.end())
    {
        return itr->second;
    }

    throw error(std::format("couldn't resolve opcode enum for '{:02X}'", id));
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

    throw error(std::format("couldn't resolve builtin function id for {}", name));
}

auto context::func_name(u16 id) const -> std::string
{
    auto const itr = func_map_.find(id);

    if (itr != func_map_.end())
    {
        return std::string{ itr->second };
    }

    return std::format("_func_{:04X}", id);
}

auto context::func2_id(std::string const& name) const -> u64
{
    if (name.starts_with("_func_"))
    {
        return static_cast<u64>(std::stoull(name.substr(6), nullptr, 16));
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

auto context::func2_name(u64 id) const -> std::string
{
    auto const itr = func_map2_.find(id);

    if (itr != func_map2_.end())
    {
        return std::string{ itr->second };
    }

    return std::format("_func_{:16X}", id);
}

auto context::func_exists(std::string const& name) const -> bool
{
    if (name.starts_with("_func_")) return true;

    if (props_ & props::hash)
    {
        return func_map2_.contains(func2_id(name));
    }
    else
    {
        return func_map_rev_.contains(name);
    }
}

auto context::func_add(std::string const& name, u16 id) -> void
{
    auto const itr = func_map_rev_.find(name);

    if (itr != func_map_rev_.end())
    {
        throw error(std::format("builtin function '{}' already defined", name));
    }

    auto const str = new_func_map_.find(name);

    if (str != new_func_map_.end())
    {
        func_map_.insert({ id, *str });
        func_map_rev_.insert({ *str, id });
    }
    else
    {
        auto ins = new_func_map_.insert(name);

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

    throw error(std::format("couldn't resolve builtin method id for {}", name));
}

auto context::meth_name(u16 id) const -> std::string
{
    auto const itr = meth_map_.find(id);

    if (itr != meth_map_.end())
    {
        return std::string{ itr->second };
    }

    return std::format("_meth_{:04X}", id);
}

auto context::meth2_id(std::string const& name) const -> u64
{
    if (name.starts_with("_meth_"))
    {
        return static_cast<u64>(std::stoull(name.substr(6), nullptr, 16));
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

auto context::meth2_name(u64 id) const -> std::string
{
    auto const itr = meth_map2_.find(id);

    if (itr != meth_map2_.end())
    {
        return std::string{ itr->second };
    }

    return std::format("_meth_{:16X}", id);
}


auto context::meth_exists(std::string const& name) const -> bool
{
    if (name.starts_with("_meth_")) return true;

    if (props_ & props::hash)
    {
        return meth_map2_.contains(meth2_id(name));
    }
    else
    {
        return meth_map_rev_.contains(name);
    }
}

auto context::meth_add(std::string const& name, u16 id) -> void
{
    auto const itr = meth_map_rev_.find(name);

    if (itr != meth_map_rev_.end())
    {
        throw error(std::format("builtin method '{}' already defined", name));
    }

    auto const str = new_meth_map_.find(name);

    if (str != new_meth_map_.end())
    {
        meth_map_.insert({ id, *str });
        meth_map_rev_.insert({ *str, id });
    }
    else
    {
        auto ins = new_meth_map_.insert(name);

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

    return std::format("_id_{:04X}", id);
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

    return std::format("_id_{:016X}", id);
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

    return std::format("_id_{:016X}", id);
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

    auto data = fs_callback_(this, name);

    if (data.first.data == nullptr && data.first.size == 0 && !data.second.empty())
    {
        auto const res = header_files_.insert({ name, std::move(data.second) });

        if (res.second)
        {
            return { &res.first->first, reinterpret_cast<char const*>(res.first->second.data()), res.first->second.size() };
        }
    }

    throw error(std::format("couldn't open gsh file '{}'", name));
}

auto context::load_include(std::string const& name) -> bool
{
    try
    {
        if (includes_.contains(name))
        {
            return false;
        }

        includes_.insert(name);

        if (include_cache_.contains(name))
            return true;

        auto filename = name;
        filename += (instance_ == gsc::instance::server) ? ".gsc" : ".csc";

        auto file = fs_callback_(this, filename);

        if ((file.first.data == nullptr || file.first.size == 0) && file.second.empty())
            throw std::runtime_error("empty file");

        if (file.first.data == nullptr && file.first.size == 0 && !file.second.empty())
        {
            // process RawFile
            auto prog = source_.parse_program(name, file.second);

            auto funcs = std::vector<std::string>{};

            for (auto const& dec : prog->declarations)
            {
                if (dec->is<decl_function>())
                {
                    funcs.push_back(dec->as<decl_function>().name->value);
                }
            }

            include_cache_.insert({ name, std::move(funcs) });
        }
        else
        {
            // process ScriptFile
            auto data = disassembler_.disassemble(file.first, buffer{ file.second.data(), file.second.size() });

            auto funcs = std::vector<std::string>{};

            for (auto const& fun : data->functions)
            {
                funcs.push_back(fun->name);
            }

            include_cache_.insert({ name, std::move(funcs) });
        }

        return true;
    }
    catch (std::exception const& e)
    {
        throw error(std::format("parsing include file '{}': {}", name, e.what()));
    }
}

auto context::init_includes() -> void
{
    includes_.clear();
}

auto context::is_includecall(std::string const& name, std::string& path) -> bool
{
    for (auto const& inc : includes_)
    {
        for (auto const& fun : include_cache_.at(std::string{ inc }))
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

extern std::array<std::pair<opcode, std::string_view>, opcode_count> const opcode_list
{{
    { opcode::vm_invalid, "vm_invalid" },
    { opcode::OP_CastFieldObject, "OP_CastFieldObject" },
    { opcode::OP_SetLocalVariableFieldCached, "OP_SetLocalVariableFieldCached" },
    { opcode::OP_plus, "OP_plus" },
    { opcode::OP_RemoveLocalVariables, "OP_RemoveLocalVariables" },
    { opcode::OP_EvalSelfFieldVariableRef, "OP_EvalSelfFieldVariableRef" },
    { opcode::OP_ScriptFarMethodChildThreadCall, "OP_ScriptFarMethodChildThreadCall" },
    { opcode::OP_GetGameRef, "OP_GetGameRef" },
    { opcode::OP_EvalAnimFieldVariable, "OP_EvalAnimFieldVariable" },
    { opcode::OP_EvalLevelFieldVariableRef, "OP_EvalLevelFieldVariableRef" },
    { opcode::OP_GetThisthread, "OP_GetThisthread" },
    { opcode::OP_greater, "OP_greater" },
    { opcode::OP_waittillmatch, "OP_waittillmatch" },
    { opcode::OP_shift_right, "OP_shift_right" },
    { opcode::OP_dec, "OP_dec" },
    { opcode::OP_JumpOnTrue, "OP_JumpOnTrue" },
    { opcode::OP_bit_or, "OP_bit_or" },
    { opcode::OP_equality, "OP_equality" },
    { opcode::OP_ClearLocalVariableFieldCached0, "OP_ClearLocalVariableFieldCached0" },
    { opcode::OP_notify, "OP_notify" },
    { opcode::OP_GetVector, "OP_GetVector" },
    { opcode::OP_ScriptMethodChildThreadCallPointer, "OP_ScriptMethodChildThreadCallPointer" },
    { opcode::OP_PreScriptCall, "OP_PreScriptCall" },
    { opcode::OP_GetByte, "OP_GetByte" },
    { opcode::OP_ScriptFarThreadCall, "OP_ScriptFarThreadCall" },
    { opcode::OP_SetSelfFieldVariableField, "OP_SetSelfFieldVariableField" },
    { opcode::OP_JumpOnFalseExpr, "OP_JumpOnFalseExpr" },
    { opcode::OP_GetUndefined, "OP_GetUndefined" },
    { opcode::OP_jumpback, "OP_jumpback" },
    { opcode::OP_JumpOnTrueExpr, "OP_JumpOnTrueExpr" },
    { opcode::OP_CallBuiltin0, "OP_CallBuiltin0" },
    { opcode::OP_CallBuiltin1, "OP_CallBuiltin1" },
    { opcode::OP_CallBuiltin2, "OP_CallBuiltin2" },
    { opcode::OP_CallBuiltin3, "OP_CallBuiltin3" },
    { opcode::OP_CallBuiltin4, "OP_CallBuiltin4" },
    { opcode::OP_CallBuiltin5, "OP_CallBuiltin5" },
    { opcode::OP_CallBuiltin, "OP_CallBuiltin" },
    { opcode::OP_SetLocalVariableFieldCached0, "OP_SetLocalVariableFieldCached0" },
    { opcode::OP_ClearFieldVariable, "OP_ClearFieldVariable" },
    { opcode::OP_GetLevel, "OP_GetLevel" },
    { opcode::OP_size, "OP_size" },
    { opcode::OP_SafeSetWaittillVariableFieldCached, "OP_SafeSetWaittillVariableFieldCached" },
    { opcode::OP_ScriptLocalMethodThreadCall, "OP_ScriptLocalMethodThreadCall" },
    { opcode::OP_AddArray, "OP_AddArray" },
    { opcode::OP_endon, "OP_endon" },
    { opcode::OP_EvalFieldVariable, "OP_EvalFieldVariable" },
    { opcode::OP_shift_left, "OP_shift_left" },
    { opcode::OP_EvalLocalArrayRefCached0, "OP_EvalLocalArrayRefCached0" },
    { opcode::OP_Return, "OP_Return" },
    { opcode::OP_CreateLocalVariable, "OP_CreateLocalVariable" },
    { opcode::OP_SafeSetVariableFieldCached0, "OP_SafeSetVariableFieldCached0" },
    { opcode::OP_GetBuiltinFunction, "OP_GetBuiltinFunction" },
    { opcode::OP_ScriptLocalMethodCall, "OP_ScriptLocalMethodCall" },
    { opcode::OP_CallBuiltinMethodPointer, "OP_CallBuiltinMethodPointer" },
    { opcode::OP_ScriptLocalChildThreadCall, "OP_ScriptLocalChildThreadCall" },
    { opcode::OP_GetSelfObject, "OP_GetSelfObject" },
    { opcode::OP_GetGame, "OP_GetGame" },
    { opcode::OP_SetLevelFieldVariableField, "OP_SetLevelFieldVariableField" },
    { opcode::OP_EvalArray, "OP_EvalArray" },
    { opcode::OP_GetSelf, "OP_GetSelf" },
    { opcode::OP_End, "OP_End" },
    { opcode::OP_EvalSelfFieldVariable, "OP_EvalSelfFieldVariable" },
    { opcode::OP_less_equal, "OP_less_equal" },
    { opcode::OP_EvalLocalVariableCached0, "OP_EvalLocalVariableCached0" },
    { opcode::OP_EvalLocalVariableCached1, "OP_EvalLocalVariableCached1" },
    { opcode::OP_EvalLocalVariableCached2, "OP_EvalLocalVariableCached2" },
    { opcode::OP_EvalLocalVariableCached3, "OP_EvalLocalVariableCached3" },
    { opcode::OP_EvalLocalVariableCached4, "OP_EvalLocalVariableCached4" },
    { opcode::OP_EvalLocalVariableCached5, "OP_EvalLocalVariableCached5" },
    { opcode::OP_EvalLocalVariableCached, "OP_EvalLocalVariableCached" },
    { opcode::OP_EvalNewLocalArrayRefCached0, "OP_EvalNewLocalArrayRefCached0" },
    { opcode::OP_ScriptChildThreadCallPointer, "OP_ScriptChildThreadCallPointer" },
    { opcode::OP_EvalLocalVariableObjectCached, "OP_EvalLocalVariableObjectCached" },
    { opcode::OP_ScriptLocalThreadCall, "OP_ScriptLocalThreadCall" },
    { opcode::OP_GetInteger, "OP_GetInteger" },
    { opcode::OP_ScriptMethodCallPointer, "OP_ScriptMethodCallPointer" },
    { opcode::OP_checkclearparams, "OP_checkclearparams" },
    { opcode::OP_SetAnimFieldVariableField, "OP_SetAnimFieldVariableField" },
    { opcode::OP_waittillmatch2, "OP_waittillmatch2" },
    { opcode::OP_minus, "OP_minus" },
    { opcode::OP_ScriptLocalFunctionCall2, "OP_ScriptLocalFunctionCall2" },
    { opcode::OP_GetNegUnsignedShort, "OP_GetNegUnsignedShort" },
    { opcode::OP_GetNegByte, "OP_GetNegByte" },
    { opcode::OP_SafeCreateVariableFieldCached, "OP_SafeCreateVariableFieldCached" },
    { opcode::OP_greater_equal, "OP_greater_equal" },
    { opcode::OP_vector, "OP_vector" },
    { opcode::OP_GetBuiltinMethod, "OP_GetBuiltinMethod" },
    { opcode::OP_endswitch, "OP_endswitch" },
    { opcode::OP_ClearArray, "OP_ClearArray" },
    { opcode::OP_DecTop, "OP_DecTop" },
    { opcode::OP_CastBool, "OP_CastBool" },
    { opcode::OP_EvalArrayRef, "OP_EvalArrayRef" },
    { opcode::OP_SetNewLocalVariableFieldCached0, "OP_SetNewLocalVariableFieldCached0" },
    { opcode::OP_GetZero, "OP_GetZero" },
    { opcode::OP_wait, "OP_wait" },
    { opcode::OP_waittill, "OP_waittill" },
    { opcode::OP_GetIString, "OP_GetIString" },
    { opcode::OP_ScriptFarFunctionCall, "OP_ScriptFarFunctionCall" },
    { opcode::OP_GetAnimObject, "OP_GetAnimObject" },
    { opcode::OP_GetAnimTree, "OP_GetAnimTree" },
    { opcode::OP_EvalLocalArrayCached, "OP_EvalLocalArrayCached" },
    { opcode::OP_mod, "OP_mod" },
    { opcode::OP_ScriptFarMethodThreadCall, "OP_ScriptFarMethodThreadCall" },
    { opcode::OP_GetUnsignedShort, "OP_GetUnsignedShort" },
    { opcode::OP_clearparams, "OP_clearparams" },
    { opcode::OP_ScriptMethodThreadCallPointer, "OP_ScriptMethodThreadCallPointer" },
    { opcode::OP_ScriptFunctionCallPointer, "OP_ScriptFunctionCallPointer" },
    { opcode::OP_EmptyArray, "OP_EmptyArray" },
    { opcode::OP_SafeSetVariableFieldCached, "OP_SafeSetVariableFieldCached" },
    { opcode::OP_ClearVariableField, "OP_ClearVariableField" },
    { opcode::OP_EvalFieldVariableRef, "OP_EvalFieldVariableRef" },
    { opcode::OP_ScriptLocalMethodChildThreadCall, "OP_ScriptLocalMethodChildThreadCall" },
    { opcode::OP_EvalNewLocalVariableRefCached0, "OP_EvalNewLocalVariableRefCached0" },
    { opcode::OP_GetFloat, "OP_GetFloat" },
    { opcode::OP_EvalLocalVariableRefCached, "OP_EvalLocalVariableRefCached" },
    { opcode::OP_JumpOnFalse, "OP_JumpOnFalse" },
    { opcode::OP_BoolComplement, "OP_BoolComplement" },
    { opcode::OP_ScriptThreadCallPointer, "OP_ScriptThreadCallPointer" },
    { opcode::OP_ScriptFarFunctionCall2, "OP_ScriptFarFunctionCall2" },
    { opcode::OP_less, "OP_less" },
    { opcode::OP_BoolNot, "OP_BoolNot" },
    { opcode::OP_waittillFrameEnd, "OP_waittillFrameEnd" },
    { opcode::OP_waitframe, "OP_waitframe" },
    { opcode::OP_GetString, "OP_GetString" },
    { opcode::OP_EvalLevelFieldVariable, "OP_EvalLevelFieldVariable" },
    { opcode::OP_GetLevelObject, "OP_GetLevelObject" },
    { opcode::OP_inc, "OP_inc" },
    { opcode::OP_CallBuiltinMethod0, "OP_CallBuiltinMethod0" },
    { opcode::OP_CallBuiltinMethod1, "OP_CallBuiltinMethod1" },
    { opcode::OP_CallBuiltinMethod2, "OP_CallBuiltinMethod2" },
    { opcode::OP_CallBuiltinMethod3, "OP_CallBuiltinMethod3" },
    { opcode::OP_CallBuiltinMethod4, "OP_CallBuiltinMethod4" },
    { opcode::OP_CallBuiltinMethod5, "OP_CallBuiltinMethod5" },
    { opcode::OP_CallBuiltinMethod, "OP_CallBuiltinMethod" },
    { opcode::OP_GetAnim, "OP_GetAnim" },
    { opcode::OP_switch, "OP_switch" },
    { opcode::OP_SetVariableField, "OP_SetVariableField" },
    { opcode::OP_divide, "OP_divide" },
    { opcode::OP_GetLocalFunction, "OP_GetLocalFunction" },
    { opcode::OP_ScriptFarChildThreadCall, "OP_ScriptFarChildThreadCall" },
    { opcode::OP_multiply, "OP_multiply" },
    { opcode::OP_ClearLocalVariableFieldCached, "OP_ClearLocalVariableFieldCached" },
    { opcode::OP_EvalAnimFieldVariableRef, "OP_EvalAnimFieldVariableRef" },
    { opcode::OP_EvalLocalArrayRefCached, "OP_EvalLocalArrayRefCached" },
    { opcode::OP_EvalLocalVariableRefCached0, "OP_EvalLocalVariableRefCached0" },
    { opcode::OP_bit_and, "OP_bit_and" },
    { opcode::OP_GetAnimation, "OP_GetAnimation" },
    { opcode::OP_GetFarFunction, "OP_GetFarFunction" },
    { opcode::OP_CallBuiltinPointer, "OP_CallBuiltinPointer" },
    { opcode::OP_jump, "OP_jump" },
    { opcode::OP_voidCodepos, "OP_voidCodepos" },
    { opcode::OP_ScriptFarMethodCall, "OP_ScriptFarMethodCall" },
    { opcode::OP_inequality, "OP_inequality" },
    { opcode::OP_ScriptLocalFunctionCall, "OP_ScriptLocalFunctionCall" },
    { opcode::OP_bit_ex_or, "OP_bit_ex_or" },
    { opcode::OP_NOP, "OP_NOP" },
    { opcode::OP_abort, "OP_abort" },
    { opcode::OP_object, "OP_object" },
    { opcode::OP_thread_object, "OP_thread_object" },
    { opcode::OP_EvalLocalVariable, "OP_EvalLocalVariable" },
    { opcode::OP_EvalLocalVariableRef, "OP_EvalLocalVariableRef" },
    { opcode::OP_prof_begin, "OP_prof_begin" },
    { opcode::OP_prof_end, "OP_prof_end" },
    { opcode::OP_breakpoint, "OP_breakpoint" },
    { opcode::OP_assignmentBreakpoint, "OP_assignmentBreakpoint" },
    { opcode::OP_manualAndAssignmentBreakpoint, "OP_manualAndAssignmentBreakpoint" },
    { opcode::OP_BoolNotAfterAnd, "OP_BoolNotAfterAnd" },
    { opcode::OP_FormalParams, "OP_FormalParams" },
    { opcode::OP_IsDefined, "OP_IsDefined" },
    { opcode::OP_IsTrue, "OP_IsTrue" },
    { opcode::OP_NativeGetLocalFunction, "OP_NativeGetLocalFunction" },
    { opcode::OP_NativeLocalFunctionCall, "OP_NativeLocalFunctionCall" },
    { opcode::OP_NativeLocalFunctionCall2, "OP_NativeLocalFunctionCall2" },
    { opcode::OP_NativeLocalMethodCall, "OP_NativeLocalMethodCall" },
    { opcode::OP_NativeLocalFunctionThreadCall, "OP_NativeLocalFunctionThreadCall" },
    { opcode::OP_NativeLocalMethodThreadCall, "OP_NativeLocalMethodThreadCall" },
    { opcode::OP_NativeLocalFunctionChildThreadCall, "OP_NativeLocalFunctionChildThreadCall" },
    { opcode::OP_NativeLocalMethodChildThreadCall, "OP_NativeLocalMethodChildThreadCall" },
    { opcode::OP_NativeGetFarFunction, "OP_NativeGetFarFunction" },
    { opcode::OP_NativeFarFunctionCall, "OP_NativeFarFunctionCall" },
    { opcode::OP_NativeFarFunctionCall2, "OP_NativeFarFunctionCall2" },
    { opcode::OP_NativeFarMethodCall, "OP_NativeFarMethodCall" },
    { opcode::OP_NativeFarFunctionThreadCall, "OP_NativeFarFunctionThreadCall" },
    { opcode::OP_NativeFarMethodThreadCall, "OP_NativeFarMethodThreadCall" },
    { opcode::OP_NativeFarFunctionChildThreadCall, "OP_NativeFarFunctionChildThreadCall" },
    { opcode::OP_NativeFarMethodChildThreadCall, "OP_NativeFarMethodChildThreadCall" },
    { opcode::OP_EvalNewLocalArrayRefCached0_Precompiled, "OP_EvalNewLocalArrayRefCached0_Precompiled" },
    { opcode::OP_SetNewLocalVariableFieldCached0_Precompiled, "OP_SetNewLocalVariableFieldCached0_Precompiled" },
    { opcode::OP_CreateLocalVariable_Precompiled, "OP_CreateLocalVariable_Precompiled" },
    { opcode::OP_SafeCreateVariableFieldCached_Precompiled, "OP_SafeCreateVariableFieldCached_Precompiled" },
    { opcode::OP_FormalParams_Precompiled, "OP_FormalParams_Precompiled" },
    { opcode::OP_GetStatHash, "OP_GetStatHash" },
    { opcode::OP_GetUnkxHash, "OP_GetUnkxHash" },
    { opcode::OP_GetEnumHash, "OP_GetEnumHash" },
    { opcode::OP_GetDvarHash, "OP_GetDvarHash" },
    { opcode::OP_GetUnsignedInt, "OP_GetUnsignedInt" },
    { opcode::OP_GetNegUnsignedInt, "OP_GetNegUnsignedInt" },
    { opcode::OP_GetInteger64, "OP_GetInteger64" },
    { opcode::OP_iw9_139, "OP_iw9_139" },
    { opcode::OP_iw9_140, "OP_iw9_140" },
    { opcode::OP_iw9_141, "OP_iw9_141" },
    { opcode::OP_iw9_142, "OP_iw9_142" },
    { opcode::OP_iw9_143, "OP_iw9_143" },
    { opcode::OP_iw9_144, "OP_iw9_144" },
    { opcode::OP_iw9_166, "OP_iw9_166" },
}};

} // namespace xsk::gsc
