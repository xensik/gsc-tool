// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/assembler.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc
{

assembler::assembler(context const* ctx) : ctx_{ ctx }, script_{ ctx->endian() == endian::big }, stack_{ ctx->endian() == endian::big }
{
}

auto assembler::assemble(assembly const& data) -> std::tuple<buffer, buffer, buffer>
{
    assembly_ = &data;
    script_.clear();
    stack_.clear();
    devmap_.clear();
    devmap_count_ = 0;

    devmap_.pos(sizeof(u32));
    script_.write<u8>(ctx_->opcode_id(opcode::OP_End));

    for (auto const& func : data.functions)
    {
        assemble_function(*func);
    }

    auto save = devmap_.pos();
    devmap_.pos(0);
    devmap_.write<u32>(devmap_count_);
    devmap_.pos(save);

    return { buffer{ script_.data(), script_.pos() }, buffer{ stack_.data(), stack_.pos() }, buffer{ devmap_.data(), devmap_.pos() } };
}

auto assembler::assemble_function(function const& func) -> void
{
    func_ = &func;

    stack_.write<u32>(static_cast<u32>(func.size));

    if (ctx_->props() & props::hash)
    {
        stack_.write<u64>(ctx_->hash_id(func.name));
    }
    else
    {
        if (ctx_->props() & props::tok4)
            stack_.write<u32>(func.id);
        else
            stack_.write<u16>(static_cast<u16>(func.id));

        if (func.id == 0)
        {
            stack_.write_cstr(encrypt_string(func.name));
        }
    }

    for (auto const& inst : func.instructions)
    {
        assemble_instruction(*inst);
    }
}

auto assembler::assemble_instruction(instruction const& inst) -> void
{
    script_.write<u8>(ctx_->opcode_id(inst.opcode));

    if ((ctx_->build() & build::dev_maps) != build::prod)
    {
        devmap_.write<u32>(static_cast<u32>(script_.pos()));
        devmap_.write<u16>(static_cast<u16>(inst.pos.line));
        devmap_.write<u16>(static_cast<u16>(inst.pos.column));
        devmap_count_++;
    }

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
            script_.write<u8>(static_cast<u8>(std::stoul(inst.data[0])));
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            script_.write<u16>(static_cast<u16>(std::stoul(inst.data[0])));
            break;
        case opcode::OP_GetUnsignedInt:
        case opcode::OP_GetNegUnsignedInt:
            script_.write<u32>(static_cast<u32>(std::stoul(inst.data[0])));
            break;
        case opcode::OP_GetInteger:
            script_.write<i32>(std::stoi(inst.data[0]));
            break;
        case opcode::OP_GetInteger64:
            script_.write<i64>(std::stoll(inst.data[0]));
            break;
        case opcode::OP_GetFloat:
            script_.write<f32>(std::stof(inst.data[0]));
            break;
        case opcode::OP_GetVector:
            script_.align((ctx_->endian() == endian::little) ? 1 : 4);
            script_.write<f32>(std::stof(inst.data[0]));
            script_.write<f32>(std::stof(inst.data[1]));
            script_.write<f32>(std::stof(inst.data[2]));
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            if (ctx_->props() & props::str4)
                script_.write<u32>(0);
            else
                script_.write<u16>(0);
            stack_.write_cstr(encrypt_string(inst.data[0]));
            break;
        case opcode::OP_GetAnimation:
            if (ctx_->props() & props::str4)
                script_.write<u64>(0);
            else
                script_.write<u32>(0);
            stack_.write_cstr(encrypt_string(inst.data[0]));
            stack_.write_cstr(encrypt_string(inst.data[1]));
            break;
        case opcode::OP_GetAnimTree:
            script_.write<u8>(0);
            stack_.write_cstr(encrypt_string(inst.data[0]));
            break;
        case opcode::OP_GetUnkxHash:
            script_.write<u32>(std::stoul(inst.data[0], nullptr, 16));
            break;
        case opcode::OP_GetStatHash:
        case opcode::OP_GetEnumHash:
        case opcode::OP_GetDvarHash:
            script_.write<u64>(std::stoull(inst.data[0], nullptr, 16));
            break;
        case opcode::OP_waittillmatch:
            script_.write<u8>(static_cast<u8>(std::stoul(inst.data[0])));
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
            script_.write<u8>(static_cast<u8>(std::stoul(inst.data[0])));
            break;
        case opcode::OP_CreateLocalVariable:
        case opcode::OP_EvalNewLocalArrayRefCached0:
        case opcode::OP_SafeCreateVariableFieldCached:
        case opcode::OP_SetNewLocalVariableFieldCached0:
            if (ctx_->props() & props::hash)
                script_.write<u64>(ctx_->hash_id(inst.data[0]));
            else
                script_.write<u8>(static_cast<u8>(std::stoul(inst.data[0])));
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
            assemble_field(inst);
            break;
        case opcode::OP_CallBuiltinPointer:
        case opcode::OP_CallBuiltinMethodPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptChildThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
        case opcode::OP_ScriptMethodChildThreadCallPointer:
            script_.write<u8>(static_cast<u8>(std::stoul(inst.data[0])));
            break;
        case opcode::OP_GetLocalFunction:
        case opcode::OP_ScriptLocalFunctionCall2:
        case opcode::OP_ScriptLocalFunctionCall:
        case opcode::OP_ScriptLocalMethodCall:
            assemble_call_local(inst, false);
            break;
        case opcode::OP_ScriptLocalThreadCall:
        case opcode::OP_ScriptLocalChildThreadCall:
        case opcode::OP_ScriptLocalMethodThreadCall:
        case opcode::OP_ScriptLocalMethodChildThreadCall:
            assemble_call_local(inst, true);
            break;
        case opcode::OP_GetFarFunction:
        case opcode::OP_ScriptFarFunctionCall2:
        case opcode::OP_ScriptFarFunctionCall:
        case opcode::OP_ScriptFarMethodCall:
            assemble_call_far(inst, false);
            break;
        case opcode::OP_ScriptFarThreadCall:
        case opcode::OP_ScriptFarChildThreadCall:
        case opcode::OP_ScriptFarMethodThreadCall:
        case opcode::OP_ScriptFarMethodChildThreadCall:
            assemble_call_far(inst, true);
            break;
        case opcode::OP_CallBuiltin:
            assemble_call_builtin(inst, false, true);
            break;
        case opcode::OP_CallBuiltinMethod:
            assemble_call_builtin(inst, true, true);
            break;
        case opcode::OP_GetBuiltinFunction:
        case opcode::OP_CallBuiltin0:
        case opcode::OP_CallBuiltin1:
        case opcode::OP_CallBuiltin2:
        case opcode::OP_CallBuiltin3:
        case opcode::OP_CallBuiltin4:
        case opcode::OP_CallBuiltin5:
            assemble_call_builtin(inst, false, false);
            break;
        case opcode::OP_GetBuiltinMethod:
        case opcode::OP_CallBuiltinMethod0:
        case opcode::OP_CallBuiltinMethod1:
        case opcode::OP_CallBuiltinMethod2:
        case opcode::OP_CallBuiltinMethod3:
        case opcode::OP_CallBuiltinMethod4:
        case opcode::OP_CallBuiltinMethod5:
            assemble_call_builtin(inst, true, false);
            break;
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_JumpOnTrueExpr:
        case opcode::OP_JumpOnFalse:
        case opcode::OP_JumpOnTrue:
            assemble_jump(inst, true, false);
            break;
        case opcode::OP_jumpback:
            assemble_jump(inst, false, true);
            break;
        case opcode::OP_jump:
            assemble_jump(inst, false, false);
            break;
        case opcode::OP_switch:
            assemble_switch(inst);
            break;
        case opcode::OP_endswitch:
            assemble_switch_table(inst);
            break;
        case opcode::OP_FormalParams:
            assemble_params(inst);
            break;
        default:
            throw asm_error(std::format("unhandled opcode {} at index {:04X}", ctx_->opcode_name(inst.opcode), inst.index));
    }
}

auto assembler::assemble_field(instruction const& inst) -> void
{
    if (ctx_->props() & props::hash)
    {
        return script_.write<u64>(ctx_->hash_id(inst.data[0]));
    }

    auto id = ctx_->token_id(inst.data[0]);

    if (id == 0) id = 0xFFFFFFFF;

    if (ctx_->props() & props::tok4)
        script_.write<u32>(id);
    else
        script_.write<u16>(static_cast<u16>(id));

    if (id > ctx_->str_count())
    {
        if (ctx_->props() & props::tok4)
            stack_.write<u32>(0);
        else
            stack_.write<u16>(0);

        stack_.write_cstr(encrypt_string(inst.data[0]));
    }
}

auto assembler::assemble_params(instruction const& inst) -> void
{
    auto count = std::stoul(inst.data[0]);

    script_.write<u8>(static_cast<u8>(count));

    for (auto i = 1u; i <= count; i++)
    {
        if (ctx_->props() & props::hash)
            script_.write<u64>(ctx_->hash_id(inst.data[i]));
        else
            script_.write<u8>(static_cast<u8>(std::stoi(inst.data[i])));
    }
}

auto assembler::assemble_call_far(instruction const& inst, bool thread) -> void
{
    if (ctx_->props() & props::farcall)
    {
        return assemble_call_far2(inst, thread);
    }

    auto file_id = ctx_->token_id(inst.data[0]);
    auto func_id = ctx_->token_id(inst.data[1]);

    if (ctx_->props() & props::tok4)
        stack_.write<u32>(file_id);
    else
        stack_.write<u16>(static_cast<u16>(file_id));

    if (file_id == 0)
    {
        if (ctx_->props() & props::extension)
            stack_.write_cstr(encrypt_string(inst.data[0] + (ctx_->instance() == instance::server ? ".gsc" : ".csc")));
        else
            stack_.write_cstr(encrypt_string(inst.data[0]));
    }

    if (ctx_->props() & props::tok4)
        stack_.write<u32>(func_id);
    else
        stack_.write<u16>(static_cast<u16>(func_id));

    if (func_id == 0)
        stack_.write_cstr(encrypt_string(inst.data[1]));

    script_.write<u8>(0);
    script_.write<u16>(0);

    if (thread)
    {
        script_.write<u8>(static_cast<u8>(std::stoi(inst.data[2])));
    }
}

auto assembler::assemble_call_far2(instruction const& inst, bool thread) -> void
{
    if (inst.data[0].empty())
    {
        script_.write<i32>(static_cast<i32>(resolve_function(inst.data[1]) - inst.index - 1));
        stack_.write<u64>(0);
        stack_.write<u64>(0);
    }
    else
    {
        auto path = inst.data[0];

        if (!path.starts_with("_id_"))
            path.append(ctx_->instance() == instance::server ? ".gsc" : ".csc");

        script_.write<u32>(0);
        stack_.write<u64>(ctx_->path_id(path));
        stack_.write<u64>(ctx_->hash_id(inst.data[1]));
    }

    if (thread)
    {
        script_.write<u8>(static_cast<u8>(std::stoi(inst.data[2])));
    }
}

auto assembler::assemble_call_local(instruction const& inst, bool thread) -> void
{
    assemble_offset(static_cast<i32>(resolve_function(inst.data[0]) - inst.index - 1));

    if (thread)
    {
        script_.write<u8>(static_cast<u8>(std::stoi(inst.data[1])));
    }
}

auto assembler::assemble_call_builtin(instruction const& inst, bool method, bool args) -> void
{
    if (args)
    {
        script_.write<u8>(static_cast<u8>(std::stoi(inst.data[1])));
    }

    if (ctx_->props() & props::hash)
    {
        stack_.write_cstr(std::format("#xS{:x}", ctx_->hash_id(inst.data[0])));
        script_.write<u16>(0);
    }
    else
    {
        script_.write<u16>(method ? ctx_->meth_id(inst.data[0]) : ctx_->func_id(inst.data[0]));
    }
}

auto assembler::assemble_jump(instruction const& inst, bool expr, bool back) -> void
{
    if (expr)
    {
        script_.write<i16>(static_cast<i16>(resolve_label(inst.data[0]) - inst.index - 3));
    }
    else if (back)
    {
        script_.write<i16>(static_cast<i16>((inst.index + 3) - resolve_label(inst.data[0])));
    }
    else
    {
        script_.write<i32>(static_cast<i32>(resolve_label(inst.data[0]) - inst.index - 5));
    }
}

auto assembler::assemble_switch(instruction const& inst) -> void
{
    script_.write<i32>(static_cast<i32>(resolve_label(inst.data[0]) - inst.index - 4));
}

auto assembler::assemble_switch_table(instruction const& inst) -> void
{
    auto count = std::stoul(inst.data[0]);
    auto index = inst.index + 3u;

    script_.write<u16>(static_cast<u16>(count));

    for (auto i = 0u; i < count; i++)
    {
        if (inst.data[1 + (4 * i)] == "case")
        {
            auto type = static_cast<switch_type>(std::stoul(inst.data[1 + (4 * i) + 1]));

            if (type == switch_type::integer)
            {
                if (ctx_->engine() == engine::iw9)
                    script_.write<u32>(std::stoi(inst.data[1 + (4 * i) + 2])); //signed?
                else
                    script_.write<u32>((std::stoi(inst.data[1 + (4 * i) + 2]) & 0xFFFFFF) + 0x800000);
            }
            else
            {
                // TODO: Sledgehammer's shenanigans (string id == 0)
                script_.write<u32>((ctx_->engine() == engine::iw9) ? 0 : i + 1);
                stack_.write_cstr(encrypt_string(inst.data[1 + (4 * i) + 2]));
            }

            auto addr = resolve_label(inst.data[1 + (4 * i) + 3]);

            if (ctx_->engine() == engine::iw9)
            {
                script_.write<i16>(static_cast<i16>(addr - index - 4));
                script_.write<u8>(0xFF);
                script_.write<u8>(static_cast<u8>(type));
                index += 8;
            }
            else
            {
                assemble_offset(static_cast<i32>(addr - index - 4));
                index += 7;
            }
        }
        else if (inst.data[1 + (4 * i)] == "default")
        {
            auto addr = resolve_label(inst.data[1 + (4 * i) + 1]);

            if (ctx_->engine() == engine::iw9)
            {
                script_.write<u32>(0);
                script_.write<i16>(static_cast<i16>(addr - index - 4));
                script_.write<u8>(0xFF);
                script_.write<u8>(0);
                index += 8;
            }
            else
            {
                script_.write<u32>(0);
                stack_.write_cstr("\x01");
                assemble_offset(static_cast<i32>(addr - index - 4));
                index += 7;
            }
        }
        else
        {
            throw asm_error("malformed switch table");
        }
    }
}

auto assembler::assemble_offset(i32 offs) -> void
{
    script_.write_i24((offs << ((ctx_->props() & props::offs8) ? 8 : (ctx_->props() & props::offs9) ? 9 : 10)) >> 8);
}

auto assembler::resolve_function(std::string const& name) const -> usize
{
    for (auto const& entry : assembly_->functions)
    {
        if (entry->name == name)
        {
            return entry->index;
        }
    }

    throw asm_error(std::format("couldn't resolve local function address of {}", name));
}

auto assembler::resolve_label(std::string const& name) const -> usize
{
    for (auto const& entry : func_->labels)
    {
        if (entry.second == name)
        {
            return entry.first;
        }
    }

    throw asm_error(std::format("couldn't resolve label address of {}", name));
}

auto assembler::encrypt_string(std::string const& str) -> std::string
{
    if (!str.starts_with("_encstr_") || str.size() % 2 != 0)
    {
        return str;
    }

    auto data = ""s;

    data.reserve(str.size() / 2);

    for (auto i = 8u; i < str.size(); i += 2)
    {
        data += static_cast<char>(std::stoul(str.substr(i, 2), 0, 16));
    }

    return data;
}

} // namespace xsk::gsc
