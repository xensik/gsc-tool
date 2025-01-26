// Copyright 2025 xensik. All rights reserved.
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
    stack_ = utils::reader{ stack, stack_size, ctx_->endian() == endian::big };
    script_ = utils::reader{ script, script_size, ctx_->endian() == endian::big };
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
    auto size = func.size;

    while (size > 0)
    {
        auto inst = instruction::make();
        inst->index = script_.pos();
        inst->opcode = ctx_->opcode_enum(script_.read<u8>());
        inst->size = ctx_->opcode_size(inst->opcode);

        dissasemble_instruction(*inst);

        if (inst->size > size || inst->index + inst->size != script_.pos())
            throw disasm_error("bad instruction size");

        size -= inst->size;

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
            inst.data.push_back(std::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            inst.data.push_back(std::format("{}", script_.read<u16>()));
            break;
        case opcode::OP_GetUnsignedInt:
        case opcode::OP_GetNegUnsignedInt:
            inst.data.push_back(std::format("{}", script_.read<u32>()));
            break;
        case opcode::OP_GetInteger:
            inst.data.push_back(std::format("{}", script_.read<i32>()));
            break;
        case opcode::OP_GetInteger64:
            inst.data.push_back(std::format("{}", script_.read<i64>()));
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
            inst.data.push_back(std::format("{:08X}", script_.read<u32>()));
            break;
        case opcode::OP_GetStatHash: // xhash : "kill" -> 0xEF9582D72160F199
        case opcode::OP_GetEnumHash: // xhash : "WEAPON/AMMO_SLUGS" -> 0x6AA606A18241AD16  c++ enum ??
        case opcode::OP_GetDvarHash: // xhash : #d"mapname" -> 0x687FB8F9B7A23245
            inst.data.push_back(std::format("{:016X}", script_.read<u64>()));
            break;
        case opcode::OP_waittillmatch:
            inst.data.push_back(std::format("{}", script_.read<u8>()));
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
            inst.data.push_back(std::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_CreateLocalVariable:
        case opcode::OP_EvalNewLocalArrayRefCached0:
        case opcode::OP_SafeCreateVariableFieldCached:
        case opcode::OP_SetNewLocalVariableFieldCached0:
            inst.data.push_back((ctx_->props() & props::hash) ? ctx_->hash_name(script_.read<u64>()) : std::format("{}", script_.read<u8>()));
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
            disassemble_field(inst);
            break;
        case opcode::OP_CallBuiltinPointer:
        case opcode::OP_CallBuiltinMethodPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptChildThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
        case opcode::OP_ScriptMethodChildThreadCallPointer:
            inst.data.push_back(std::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_GetLocalFunction:
        case opcode::OP_ScriptLocalFunctionCall2:
        case opcode::OP_ScriptLocalFunctionCall:
        case opcode::OP_ScriptLocalMethodCall:
            disassemble_call_local(inst, false);
            break;
        case opcode::OP_ScriptLocalThreadCall:
        case opcode::OP_ScriptLocalChildThreadCall:
        case opcode::OP_ScriptLocalMethodThreadCall:
        case opcode::OP_ScriptLocalMethodChildThreadCall:
            disassemble_call_local(inst, true);
            break;
        case opcode::OP_GetFarFunction:
        case opcode::OP_ScriptFarFunctionCall2:
        case opcode::OP_ScriptFarFunctionCall:
        case opcode::OP_ScriptFarMethodCall:
            disassemble_call_far(inst, false);
            break;
        case opcode::OP_ScriptFarThreadCall:
        case opcode::OP_ScriptFarChildThreadCall:
        case opcode::OP_ScriptFarMethodThreadCall:
        case opcode::OP_ScriptFarMethodChildThreadCall:
            disassemble_call_far(inst, true);
            break;
        case opcode::OP_CallBuiltin:
            disassemble_call_builtin(inst, false, true);
            break;
        case opcode::OP_CallBuiltinMethod:
            disassemble_call_builtin(inst, true, true);
            break;
        case opcode::OP_GetBuiltinFunction:
        case opcode::OP_CallBuiltin0:
        case opcode::OP_CallBuiltin1:
        case opcode::OP_CallBuiltin2:
        case opcode::OP_CallBuiltin3:
        case opcode::OP_CallBuiltin4:
        case opcode::OP_CallBuiltin5:
            disassemble_call_builtin(inst, false, false);
            break;
        case opcode::OP_GetBuiltinMethod:
        case opcode::OP_CallBuiltinMethod0:
        case opcode::OP_CallBuiltinMethod1:
        case opcode::OP_CallBuiltinMethod2:
        case opcode::OP_CallBuiltinMethod3:
        case opcode::OP_CallBuiltinMethod4:
        case opcode::OP_CallBuiltinMethod5:
            disassemble_call_builtin(inst, true, false);
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
            disassemble_switch_table(inst);
            break;
        case opcode::OP_FormalParams:
            disassemble_params(inst);
            break;
        default:
            throw disasm_error(std::format("unhandled opcode {} at index {:04X}", ctx_->opcode_name(inst.opcode), inst.index));
    }
}

auto disassembler::disassemble_field(instruction& inst) -> void
{
    if (ctx_->props() & props::hash)
    {
        return inst.data.push_back(ctx_->hash_name(script_.read<u64>()));
    }

    if (auto id = (ctx_->props() & props::tok4) ? script_.read<u32>() : script_.read<u16>(); id <= ctx_->str_count())
    {
        return inst.data.push_back(ctx_->token_name(id));
    }

    auto temp = (ctx_->props() & props::tok4) ? stack_.read<u32>() : stack_.read<u16>();
    inst.data.push_back(temp == 0 ? decrypt_string(stack_.read_cstr()) : std::format("{}", temp));
}

auto disassembler::disassemble_params(instruction& inst) -> void
{
    auto count = script_.read<u8>();

    inst.size += (ctx_->props() & props::hash) ? count * 8 : count;
    inst.data.push_back(std::format("{}", count));

    for (auto i = 0u; i < count; i++)
    {
        inst.data.push_back((ctx_->props() & props::hash) ? ctx_->hash_name(script_.read<u64>()) : std::format("{}", script_.read<u8>()));
    }
}

auto disassembler::disassemble_call_far(instruction& inst, bool thread) -> void
{
    if (ctx_->props() & props::farcall)
    {
        return disassemble_call_far2(inst, thread);
    }

    auto file_id = (ctx_->props() & props::tok4) ? stack_.read<u32>() : stack_.read<u16>();
    auto file_name = file_id == 0 ? decrypt_string(stack_.read_cstr()) : ctx_->token_name(file_id);
    auto func_id = (ctx_->props() & props::tok4) ? stack_.read<u32>() : stack_.read<u16>();
    auto func_name = func_id == 0 ? decrypt_string(stack_.read_cstr()) : ctx_->token_name(func_id);

    if (ctx_->props() & props::extension && func_id == 0)
    {
        file_name.resize(file_name.size() - 4);
    }

    inst.data.push_back(std::move(file_name));
    inst.data.push_back(std::move(func_name));

    script_.seek(3);

    if (thread)
    {
        inst.data.push_back(std::format("{}", script_.read<u8>()));
    }
}

auto disassembler::disassemble_call_far2(instruction& inst, bool thread) -> void
{
    auto offs = script_.read<i32>();
    auto file = stack_.read<u64>();
    auto name = stack_.read<u64>();

    if (file == 0)
    {
        inst.data.push_back(""s);
        inst.data.push_back(std::format("{}", inst.index + 1 + offs));
    }
    else
    {
        auto path = ctx_->path_name(file);

        if (!path.starts_with("_id_"s))
        {
            path.resize(path.size() - 4);
        }

        inst.data.push_back(std::move(path));
        inst.data.push_back(ctx_->hash_name(name));
    }

    if (thread)
    {
        inst.data.push_back(std::format("{}", script_.read<u8>()));
    }
}

auto disassembler::disassemble_call_local(instruction& inst, bool thread) -> void
{
    auto offset = disassemble_offset();

    inst.data.push_back(std::format("{}", inst.index + 1 + offset));

    if (thread)
    {
        inst.data.push_back(std::format("{}", script_.read<u8>()));
    }
}

auto disassembler::disassemble_call_builtin(instruction& inst, bool method, bool args) -> void
{
    if (ctx_->props() & props::hash)
    {
        return disassemble_call_builtin2(inst, method, args);
    }

    auto count = args ? script_.read<u8>() : 0;
    auto id = script_.read<u16>();
    auto name = method ? ctx_->meth_name(id) : ctx_->func_name(id);

    inst.data.push_back(std::move(name));

    if (args)
    {
        inst.data.push_back(std::format("{}", count));
    }
}

auto disassembler::disassemble_call_builtin2(instruction& inst, bool method, bool args) -> void
{
    auto name = stack_.read_cstr();

    if (name.starts_with("#xS"s))
    {
        auto id = std::stoull(name.substr(3), nullptr, 16);
        name = method ? ctx_->meth2_name(id) : ctx_->func2_name(id);
    }

    inst.data.push_back(std::move(name));

    if (args)
    {
        inst.data.push_back(std::format("{}", script_.read<u8>()));
    }

    script_.seek(2);
}

auto disassembler::disassemble_jump(instruction& inst, bool expr, bool back) -> void
{
    auto addr = inst.index + (expr ? 3 + script_.read<i16>() : back ? 3 - script_.read<u16>() : 5 + script_.read<i32>());
    auto label = std::format("loc_{:X}", addr);

    inst.data.emplace_back(label);
    func_->labels.insert({ addr, label });
}

auto disassembler::disassemble_switch(instruction& inst) -> void
{
    auto addr = inst.index + 4 + script_.read<i32>();
    auto label = std::format("loc_{:X}", addr);

    inst.data.emplace_back(label);
    func_->labels.insert({ addr, label });
}

auto disassembler::disassemble_switch_table(instruction& inst) -> void
{
    auto count = script_.read<u16>();
    auto index = inst.index + 3u;

    inst.data.push_back(std::format("{}", count));

    for (auto i = 0u; i < count; i++)
    {
        auto data = script_.read<u32>();
        auto offs = (ctx_->engine() == engine::iw9) ? script_.read<i16>() : disassemble_offset();
        auto size = (ctx_->engine() == engine::iw9) ? 8 : 7;

        if (ctx_->engine() == engine::iw9)
        {
            script_.seek(1); // skip byte 0xFF
            auto type = script_.read<u8>();

            if (type == 0)
            {
                inst.data.push_back("default"s); // data:0 type:0 i:1
            }
            else if (type == 1)
            {
                inst.data.push_back("case");
                inst.data.push_back(std::format("{}", static_cast<int>(switch_type::integer)));
                inst.data.push_back(std::format("{}", data));
            }
            else if (type == 2)
            {
                inst.data.push_back("case");
                inst.data.push_back(std::format("{}", static_cast<int>(switch_type::string)));
                inst.data.push_back(stack_.read_cstr());
            }
        }
        else
        {
            if (data == 0)
            {
                auto str = stack_.read_cstr(); // [0x01 0x00] unencrypted

                // Sledgehammer's shenanigans
                if (ctx_->engine() == engine::s2 && str != "\x01")
                {
                    inst.data.push_back("case");
                    inst.data.push_back(std::format("{}", static_cast<int>(switch_type::string)));
                    inst.data.push_back(decrypt_string(str));
                }
                else
                {
                    inst.data.push_back("default");
                }
            }
            else if (data < 0x100000)
            {
                inst.data.push_back("case");
                inst.data.push_back(std::format("{}", static_cast<int>(switch_type::string)));
                inst.data.push_back(decrypt_string(stack_.read_cstr()));
            }
            else
            {
                inst.data.push_back("case");
                inst.data.push_back(std::format("{}", static_cast<int>(switch_type::integer)));
                inst.data.push_back(std::format("{}", (data - 0x800000) & 0xFFFFFF));
            }
        }

        auto addr = index + 4 + offs;
        auto label = std::format("loc_{:X}", addr);

        inst.data.emplace_back(label);
        func_->labels.insert({ addr, label });

        index += size;
        inst.size += size;
    }
}

auto disassembler::disassemble_offset() -> i32
{
    return (script_.read_i24() << 8) >> ((ctx_->props() & props::offs8) ? 8 : (ctx_->props() & props::offs9) ? 9 : 10);
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
    auto addr = static_cast<usize>(std::stoul(index));

    for (auto const& func : assembly_->functions)
    {
        if (func->index == addr)
        {
            return func->name;
        }
    }

    throw disasm_error(std::format("couldn't resolve function name at index 0x{}", index));
}

auto disassembler::decrypt_string(std::string const& str) -> std::string
{
    if (str.empty() || ((static_cast<u8>(str[0]) & 0xC0) != 0x80))
    {
        return str;
    }

    auto data = "_encstr_"s;

    data.reserve(str.size() * 2);

    for (auto i = 0u; i < str.size(); i++)
    {
        data += std::format("{:02X}", static_cast<u8>(str[i]));
    }

    return data;
}

} // namespace xsk::gsc
