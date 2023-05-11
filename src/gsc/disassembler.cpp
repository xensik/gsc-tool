// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/gsc/disassembler.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc
{

disassembler::disassembler(context const* ctx) : ctx_{ ctx }
{
}

auto disassembler::disassemble(buffer const& script, buffer const& stack) -> assembly::ptr
{
    return disassemble(script.data, script.size, stack.data, stack.size);
}

auto disassembler::disassemble(std::vector<u8> const& script, std::vector<u8> const& stack) -> assembly::ptr
{
    return disassemble(script.data(), script.size(), stack.data(), stack.size());
}

auto disassembler::disassemble(u8 const* script, usize script_size, u8 const* stack, usize stack_size) -> assembly::ptr
{
    stack_ = utils::reader{ stack, static_cast<u32>(stack_size), ctx_->endian() == endian::big };
    script_ = utils::reader{ script, static_cast<u32>(script_size), ctx_->endian() == endian::big };
    assembly_ = assembly::make();

    script_.seek(1);

    while (script_.is_avail() && stack_.is_avail())
    {
        func_ = function::make();
        func_->index = script_.pos();
        func_->size = stack_.read<u32>();
        func_->id = (ctx_->props() & props::hash) ? 0 : (ctx_->props() & props::tok4) ? stack_.read<u32>() : stack_.read<u16>();
        func_->name = (ctx_->props() & props::hash) ? ctx_->hash_name(stack_.read<u64>()) : func_->id == 0 ? decrypt_string(stack_.read_cstr()) : ctx_->token_name(func_->id);

        dissasemble_function(*func_);

        assembly_->functions.push_back(std::move(func_));
    }

    resolve_functions();

    return std::move(assembly_);
}

auto disassembler::dissasemble_function(function& func) -> void
{
    auto size = static_cast<i32>(func.size);

    while (size > 0)
    {
        auto inst = instruction::make();
        inst->index = script_.pos();
        inst->opcode = ctx_->opcode_enum(script_.read<u8>());
        inst->size = ctx_->opcode_size(inst->opcode);

        dissasemble_instruction(*inst);

        size -= inst->size;

        if (size < 0 || inst->index + inst->size != script_.pos())
            throw disasm_error("bad instruction size");

        func.instructions.push_back(std::move(inst));
    }
}

auto disassembler::dissasemble_instruction(instruction& inst) -> void
{
    switch (inst.opcode)
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
        case opcode::OP_ClearVariableField:
        case opcode::OP_EvalNewLocalVariableRefCached0:
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
            break;
        case opcode::OP_GetByte:
        case opcode::OP_GetNegByte:
            inst.data.push_back(fmt::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            inst.data.push_back(fmt::format("{}", script_.read<u16>()));
            break;
        case opcode::OP_GetUnsignedInt:
        case opcode::OP_GetNegUnsignedInt:
            inst.data.push_back(fmt::format("{}", script_.read<u32>()));
            break;
        case opcode::OP_GetInteger:
            inst.data.push_back(fmt::format("{}", script_.read<i32>()));
            break;
        case opcode::OP_GetInteger64:
            inst.data.push_back(fmt::format("{}", script_.read<i64>()));
            break;
        case opcode::OP_GetFloat:
            inst.data.push_back(utils::string::float_string(script_.read<f32>()));
            break;
        case opcode::OP_GetVector:
            inst.size += script_.align((ctx_->endian() == endian::little) ? 1 : 4);
            inst.data.push_back(utils::string::float_string(script_.read<f32>(), true));
            inst.data.push_back(utils::string::float_string(script_.read<f32>(), true));
            inst.data.push_back(utils::string::float_string(script_.read<f32>(), true));
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            script_.seek((ctx_->props() & props::str4) ? 4 : 2);
            inst.data.push_back(decrypt_string(stack_.read_cstr()));
            break;
        case opcode::OP_GetAnimation:
            script_.seek((ctx_->props() & props::str4) ? 8 : 4);
            inst.data.push_back(decrypt_string(stack_.read_cstr()));
            inst.data.push_back(decrypt_string(stack_.read_cstr()));
            break;
        case opcode::OP_GetAnimTree:
            script_.seek(1);
            inst.data.push_back(decrypt_string(stack_.read_cstr()));
            break;
        case opcode::OP_GetUnkxHash: // xhash : only used on unittests
            inst.data.push_back(fmt::format("{:08X}", script_.read<u32>()));
            break;
        case opcode::OP_GetStatHash: // xhash : "kill" -> 0xEF9582D72160F199
        case opcode::OP_GetEnumHash: // xhash : "WEAPON/AMMO_SLUGS" -> 0x6AA606A18241AD16  c++ enum ??
        case opcode::OP_GetDvarHash: // xhash : #d"mapname" -> 0x687FB8F9B7A23245
            inst.data.push_back(fmt::format("{:016X}", script_.read<u64>()));
            break;
        case opcode::OP_waittillmatch:
            inst.data.push_back(fmt::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_ClearLocalVariableFieldCached:
        case opcode::OP_SetLocalVariableFieldCached:
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_EvalLocalVariableRefCached:
        case opcode::OP_EvalLocalArrayRefCached:
        case opcode::OP_SafeSetVariableFieldCached:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_EvalLocalVariableObjectCached:
        case opcode::OP_EvalLocalArrayCached:
            inst.data.push_back(fmt::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_CreateLocalVariable:
        case opcode::OP_EvalNewLocalArrayRefCached0:
        case opcode::OP_SafeCreateVariableFieldCached:
        case opcode::OP_SetNewLocalVariableFieldCached0:
            inst.data.push_back((ctx_->props() & props::hash) ? ctx_->hash_name(script_.read<u64>()) : fmt::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_EvalSelfFieldVariable:
        case opcode::OP_SetLevelFieldVariableField:
        case opcode::OP_ClearFieldVariable:
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_EvalLevelFieldVariable:
        case opcode::OP_SetAnimFieldVariableField:
        case opcode::OP_SetSelfFieldVariableField:
        case opcode::OP_EvalAnimFieldVariableRef:
        case opcode::OP_EvalLevelFieldVariableRef:
        case opcode::OP_EvalAnimFieldVariable:
        case opcode::OP_EvalSelfFieldVariableRef:
            disassemble_field_variable(inst);
            break;
        case opcode::OP_CallBuiltinPointer:
        case opcode::OP_CallBuiltinMethodPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptChildThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
        case opcode::OP_ScriptMethodChildThreadCallPointer:
            inst.data.push_back(fmt::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_GetLocalFunction:
        case opcode::OP_ScriptLocalFunctionCall2:
        case opcode::OP_ScriptLocalFunctionCall:
        case opcode::OP_ScriptLocalMethodCall:
            disassemble_local_call(inst, false);
            break;
        case opcode::OP_ScriptLocalThreadCall:
        case opcode::OP_ScriptLocalChildThreadCall:
        case opcode::OP_ScriptLocalMethodThreadCall:
        case opcode::OP_ScriptLocalMethodChildThreadCall:
            disassemble_local_call(inst, true);
            break;
        case opcode::OP_GetFarFunction:
        case opcode::OP_ScriptFarFunctionCall2:
        case opcode::OP_ScriptFarFunctionCall:
        case opcode::OP_ScriptFarMethodCall:
            disassemble_far_call(inst, false);
            break;
        case opcode::OP_ScriptFarThreadCall:
        case opcode::OP_ScriptFarChildThreadCall:
        case opcode::OP_ScriptFarMethodThreadCall:
        case opcode::OP_ScriptFarMethodChildThreadCall:
            disassemble_far_call(inst, true);
            break;
        case opcode::OP_CallBuiltin:
            disassemble_builtin_call(inst, false, true);
            break;
        case opcode::OP_CallBuiltinMethod:
            disassemble_builtin_call(inst, true, true);
            break;
        case opcode::OP_GetBuiltinFunction:
        case opcode::OP_CallBuiltin0:
        case opcode::OP_CallBuiltin1:
        case opcode::OP_CallBuiltin2:
        case opcode::OP_CallBuiltin3:
        case opcode::OP_CallBuiltin4:
        case opcode::OP_CallBuiltin5:
            disassemble_builtin_call(inst, false, false);
            break;
        case opcode::OP_GetBuiltinMethod:
        case opcode::OP_CallBuiltinMethod0:
        case opcode::OP_CallBuiltinMethod1:
        case opcode::OP_CallBuiltinMethod2:
        case opcode::OP_CallBuiltinMethod3:
        case opcode::OP_CallBuiltinMethod4:
        case opcode::OP_CallBuiltinMethod5:
            disassemble_builtin_call(inst, true, false);
            break;
        case opcode::OP_JumpOnFalse:
        case opcode::OP_JumpOnTrue:
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_JumpOnTrueExpr:
            disassemble_jump(inst, true, false);
            break;
        case opcode::OP_jumpback:
            disassemble_jump(inst, false, true);
            break;
        case opcode::OP_jump:
            disassemble_jump(inst, false, false);
            break;
        case opcode::OP_switch:
            disassemble_switch(inst);
            break;
        case opcode::OP_endswitch:
            disassemble_end_switch(inst);
            break;
        case opcode::OP_FormalParams:
            disassemble_formal_params(inst);
            break;
        default:
            throw disasm_error(fmt::format("unhandled opcode {} at index {:04X}", ctx_->opcode_name(inst.opcode), inst.index));
    }
}

auto disassembler::disassemble_builtin_call(instruction& inst, bool method, bool args) -> void
{
    if (args)
    {
        inst.data.push_back(fmt::format("{}", script_.read<u8>()));
    }

    if (ctx_->props() & props::hash)
    {
        auto name = stack_.read_cstr();

        if (name.starts_with("#xS"))
        {
            auto const id = std::stoull(name.substr(3), 0, 16);
            name = method ? ctx_->meth2_name(id) : ctx_->func2_name(id);
        }

        script_.seek(2);
        inst.data.emplace(inst.data.begin(), name);
    }
    else
    {
        auto const id = script_.read<u16>();
        auto const name = method ? ctx_->meth_name(id) : ctx_->func_name(id);

        inst.data.emplace(inst.data.begin(), name);
    }
}

auto disassembler::disassemble_local_call(instruction& inst, bool thread) -> void
{
    auto const offs = disassemble_offset();

    inst.data.push_back(fmt::format("{}", inst.index + 1 + offs));

    if (thread)
    {
        inst.data.push_back(fmt::format("{}", script_.read<u8>()));
    }
}

auto disassembler::disassemble_far_call(instruction& inst, bool thread) -> void
{
    if (ctx_->props() & props::farcall)
    {
        auto offs = script_.read<u32>();

        if (thread)
        {
            inst.data.push_back(fmt::format("{}", script_.read<u8>()));
        }

        auto file = stack_.read<u64>();
        auto name = stack_.read<u64>();

        if (file == 0)
        {
            inst.data.emplace(inst.data.begin(), fmt::format("{}", inst.index + 1 + offs));
            inst.data.emplace(inst.data.begin(), "");
        }
        else
        {
            auto path = ctx_->path_name(file);

            if (!path.starts_with("_id_"))
            {
                path.resize(path.size() - 4);
            }

            inst.data.emplace(inst.data.begin(), ctx_->hash_name(name));
            inst.data.emplace(inst.data.begin(), path);
        }
    }
    else
    {
        script_.seek(3);

        if (thread)
        {
            inst.data.push_back(fmt::format("{}", script_.read<u8>()));
        }

        auto const file_id = (ctx_->props() & props::tok4) ? stack_.read<u32>() : stack_.read<u16>();
        auto const file_name = file_id == 0 ? decrypt_string(stack_.read_cstr()) : ctx_->token_name(file_id);
        auto const func_id = (ctx_->props() & props::tok4) ? stack_.read<u32>() : stack_.read<u16>();
        auto const func_name = func_id == 0 ? decrypt_string(stack_.read_cstr()) : ctx_->token_name(func_id);

        inst.data.emplace(inst.data.begin(), func_name);
        inst.data.emplace(inst.data.begin(), file_name);
    }
}

auto disassembler::disassemble_switch(instruction& inst) -> void
{
    auto const addr = inst.index + 4 + script_.read<i32>();
    auto const label = fmt::format("loc_{:X}", addr);

    inst.data.push_back(label);
    func_->labels.insert({ addr, label });
}

auto disassembler::disassemble_end_switch(instruction& inst) -> void
{
    auto const count = script_.read<u16>();

    inst.data.push_back(fmt::format("{}", count));

    auto type = switch_type::none;
    auto index = inst.index + 3u;

    for (auto i = count; i > 0; i--)
    {
        if (ctx_->engine() == engine::iw9)
        {
            auto const data = script_.read<u32>();
            auto const offs = script_.read<i16>();
            script_.seek(1);
            auto const byte = script_.read<u8>();

            if (byte == 1)
            {
                inst.data.push_back("case");
                inst.data.push_back(fmt::format("{}", static_cast<std::underlying_type_t<switch_type>>(switch_type::integer)));
                inst.data.push_back(fmt::format("{}", data));
            }
            else if (byte == 2)
            {
                inst.data.push_back("case");
                inst.data.push_back(fmt::format("{}", static_cast<std::underlying_type_t<switch_type>>(switch_type::string)));
                inst.data.push_back(stack_.read_cstr());
            }
            else // byte == 0
            {
                // default -> data = 0, byte = 0, i = 1 
                inst.data.push_back("default");
            }

            auto const addr = index + 4 + offs;
            auto const label = fmt::format("loc_{:X}", addr);

            inst.data.push_back(label);
            func_->labels.insert({ addr, label });

            index += 8;
            inst.size += 8;
        }
        else
        {
            auto const value = script_.read<u32>();

            if (value == 0)
            {
                inst.data.push_back("default");
                stack_.read_cstr(); // this should be always [0x01 0x00] unencrypted
            }
            else if (value < 0x100000)
            {
                if (type == switch_type::integer)
                    throw disasm_error("endswitch type mismatch");

                type = switch_type::string;
                inst.data.push_back("case");
                inst.data.push_back(decrypt_string(stack_.read_cstr()));
            } 
            else
            {
                if (type == switch_type::string)
                    throw disasm_error("endswitch type mismatch");

                type = switch_type::integer;
                inst.data.push_back("case");
                inst.data.push_back(fmt::format("{}", (value - 0x800000) & 0xFFFFFF));
            }

            auto const addr = index + 4 + disassemble_offset();
            auto const label = fmt::format("loc_{:X}", addr);

            inst.data.push_back(label);
            func_->labels.insert({ addr, label });

            index += 7;
            inst.size += 7;
        }
    }

    inst.data.push_back(fmt::format("{}", static_cast<std::underlying_type_t<switch_type>>(type)));
}

auto disassembler::disassemble_field_variable(instruction& inst) -> void
{
    if (ctx_->props() & props::hash)
    {
        inst.data.push_back(ctx_->hash_name(script_.read<u64>()));
    }
    else
    {
        auto const id = (ctx_->props() & props::tok4) ? script_.read<u32>() : script_.read<u16>();
        auto name = std::string{};

        if (id > ctx_->str_count())
        {
            auto const temp = (ctx_->props() & props::tok4) ? stack_.read<u32>() : stack_.read<u16>();
            name = (temp == 0) ? decrypt_string(stack_.read_cstr()) : fmt::format("{}", temp);
        }
        else
        {
            name = ctx_->token_name(id);
        }

        inst.data.push_back(name);
    }
}

auto disassembler::disassemble_formal_params(instruction& inst) -> void
{
    auto const count = script_.read<u8>();

    inst.size += (ctx_->props() & props::hash) ? count * 8 : count;
    inst.data.push_back(fmt::format("{}", count));

    for (auto i = 0u; i < count; i++)
    {
        inst.data.push_back((ctx_->props() & props::hash) ? ctx_->hash_name(script_.read<u64>()) : fmt::format("{}", script_.read<u8>()));
    }
}

auto disassembler::disassemble_jump(instruction& inst, bool expr, bool back) -> void
{
    auto addr = i32{};

    if (expr)
    {
        addr = inst.index + 3 + script_.read<i16>();
    }
    else if (back)
    {
        addr = inst.index + 3 - script_.read<u16>();
    }
    else
    {
        addr = inst.index + 5 + script_.read<i32>();
    }

    auto const label = fmt::format("loc_{:X}", addr);

    inst.data.push_back(label);
    func_->labels.insert({ addr, label });
}

auto disassembler::disassemble_offset() -> i32
{
    auto bytes = std::array<u8, 4>{};

    if (ctx_->endian() == endian::little)
    {
        bytes[0] = script_.read<u8>();
        bytes[1] = script_.read<u8>();
        bytes[2] = script_.read<u8>();
    }
    else
    {
        bytes[2] = script_.read<u8>();
        bytes[1] = script_.read<u8>();
        bytes[0] = script_.read<u8>();
    }

    auto offs = *reinterpret_cast<i32*>(bytes.data());

    auto shift = (ctx_->props() & props::offs8) ? 8 : (ctx_->props() & props::offs9) ? 9 : 10;

    offs = (offs << 8) >> shift;

    return offs;
}

auto disassembler::resolve_functions() -> void
{
    for (auto const& func : assembly_->functions)
    {
        for (auto const& inst : func->instructions)
        {
            switch (inst->opcode)
            {
                case opcode::OP_GetLocalFunction:
                case opcode::OP_ScriptLocalFunctionCall:
                case opcode::OP_ScriptLocalFunctionCall2:
                case opcode::OP_ScriptLocalMethodCall:
                case opcode::OP_ScriptLocalThreadCall:
                case opcode::OP_ScriptLocalChildThreadCall:
                case opcode::OP_ScriptLocalMethodThreadCall:
                case opcode::OP_ScriptLocalMethodChildThreadCall:
                    inst->data[0] = resolve_function(inst->data[0]);
                    break;
                case opcode::OP_GetFarFunction:
                case opcode::OP_ScriptFarFunctionCall:
                case opcode::OP_ScriptFarMethodCall:
                case opcode::OP_ScriptFarThreadCall:
                case opcode::OP_ScriptFarChildThreadCall:
                case opcode::OP_ScriptFarMethodThreadCall:
                case opcode::OP_ScriptFarMethodChildThreadCall:
                    if ((ctx_->props() & props::farcall) && inst->data[0].empty())
                        inst->data[1] = resolve_function(inst->data[1]);
                    break;
                default:
                    break;
            }
        }
    }
}

auto disassembler::resolve_function(std::string const& index) -> std::string
{
    auto addr = static_cast<u32>(std::stoul(index));

    for (auto const& entry : assembly_->functions)
    {
        if (entry->index == addr)
        {
            return entry->name;
        }
    }

    throw disasm_error(fmt::format("couldn't resolve function name at index 0x{}", index));
}

auto disassembler::decrypt_string(std::string const& str) -> std::string
{
    if (str.size() > 0 && ((static_cast<u8>(str[0]) & 0xC0) == 0x80))
    {
        auto data = std::string{ "_encstr_" };

        data.reserve(str.size() * 2);

        for (auto i = 0u; i < str.size(); i++)
        {
            data += fmt::format("{:02X}", static_cast<u8>(str[i]));
        }

        return data;
    }

    return std::move(str);
}

} // namespace xsk::gsc
