// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/assembler.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc
{

assembler::assembler(context const* ctx) : ctx_{ ctx }, script_{ ctx->endian() == endian::big }
{
}

auto assembler::assemble(assembly const& data, std::string const& name) -> std::pair<buffer, buffer>
{
    assembly_ = &data;
    script_.clear();
    devmap_.clear();
    strpool_.clear();
    exports_.clear();
    imports_.clear();
    strings_.clear();
    anims_.clear();
    devmap_count_ = 0;
    auto head = header{};

    devmap_.pos(sizeof(u32));
    script_.pos((ctx_->props() & props::headerxx) ? 0 : (ctx_->props() & props::header72) ? 72 : 64);
    process_string(name);

    for (auto const& func : assembly_->functions)
    {
        process_function(*func);
    }

    for (auto const& incl : assembly_->includes)
    {
        process_string(incl);
    }

    head.include_offset = static_cast<u32>(script_.pos());
    head.include_count = static_cast<u8>(assembly_->includes.size());

    for (auto const& entry : assembly_->includes)
    {
        script_.write<u32>(resolve_string(entry));
    }

    head.cseg_offset = static_cast<u32>(script_.pos());

    for (auto const& func : assembly_->functions)
    {
        script_.align((ctx_->props() & props::size64) ? 8 : 4);
        script_.seek((ctx_->props() & props::size64) ? 8 : 4);
        assemble_function(*func);
    }

    head.cseg_size = static_cast<u32>(script_.pos() - head.cseg_offset);
    head.source_crc = 0;

    head.exports_offset = static_cast<u32>(script_.pos());
    head.exports_count = static_cast<u16>(exports_.size());

    for (auto const& entry : exports_)
    {
        script_.write<u32>(entry.checksum);
        script_.write<u32>(entry.offset);

        if (ctx_->props() & props::hashids)
        {
            script_.write<u32>(ctx_->hash_id(entry.name));
            script_.write<u32>(ctx_->hash_id(entry.space));
        }
        else
        {
            script_.write<u16>(resolve_string(entry.name));
        }

        script_.write<u8>(entry.params);
        script_.write<u8>(entry.flags);

        if (ctx_->props() & props::hashids)
            script_.seek(2);
    }

    head.imports_offset = static_cast<u32>(script_.pos());
    head.imports_count = static_cast<u16>(imports_.size());

    for (auto const& entry : imports_)
    {
        if (ctx_->props() & props::hashids)
        {
            script_.write<u32>(ctx_->hash_id(entry.name));
            script_.write<u32>(ctx_->hash_id(entry.space));
        }
        else
        {
            script_.write<u16>(resolve_string(entry.name));
            script_.write<u16>(resolve_string(entry.space));
        }

        script_.write<u16>(static_cast<u16>(entry.refs.size()));
        script_.write<u8>(entry.params);
        script_.write<u8>(entry.flags);

        for (auto ref : entry.refs)
        {
            script_.write<u32>(ref);
        }
    }

    head.animtree_offset = static_cast<u32>(script_.pos());
    head.animtree_count = static_cast<u8>(anims_.size());

    for (auto const& entry : anims_)
    {
        if (ctx_->props() & props::size64)
        {
            script_.write<u32>(resolve_string(entry.name));
            script_.write<u16>(static_cast<u16>(entry.refs.size()));
            script_.write<u16>(static_cast<u16>(entry.anims.size()));
        }
        else
        {
            script_.write<u16>(resolve_string(entry.name));
            script_.write<u16>(static_cast<u16>(entry.refs.size()));
            script_.write<u16>(static_cast<u16>(entry.anims.size()));
            script_.seek(2);
        }

        for (auto ref : entry.refs)
        {
            script_.write<u32>(ref);
        }

        for (auto const& anim : entry.anims)
        {
            if (ctx_->props() & props::size64)
            {
                script_.write<u64>(resolve_string(anim.name));
                script_.write<u64>(anim.ref);
            }
            else
            {
                script_.write<u32>(resolve_string(anim.name));
                script_.write<u32>(anim.ref);
            }
        }
    }

    head.stringtablefixup_offset = static_cast<u32>(script_.pos());
    //head.stringtablefixup_count = static_cast<u16>(strings_.size());

    auto stringtablecount = 0u;

    for (auto const& entry : strings_)
    {
        if (entry.refs.size() > 0xFF)
        {
            auto count = static_cast<i32>(entry.refs.size());

            for (auto i = 0; i < count; i++)
            {
                if (i % 0xFF == 0)
                {
                    stringtablecount++;
                    if (ctx_->props() & props::size64)
                        script_.write<u32>(resolve_string(entry.name));
                    else
                        script_.write<u16>(resolve_string(entry.name));

                    script_.write<u8>(static_cast<u8>(std::min(0xFF, count - i)));
                    script_.write<u8>(entry.type);

                    if (ctx_->props() & props::size64)
                        script_.seek(2);
                }

                script_.write<u32>(entry.refs[i]);
            }
        }
        else
        {
            stringtablecount++;
            if (ctx_->props() & props::size64)
                script_.write<u32>(resolve_string(entry.name));
            else
                script_.write<u16>(resolve_string(entry.name));

            script_.write<u8>(static_cast<u8>(entry.refs.size()));
            script_.write<u8>(entry.type);

            if (ctx_->props() & props::size64)
                script_.seek(2);

            for (auto ref : entry.refs)
            {
                script_.write<u32>(ref);
            }
        }
    }

    head.stringtablefixup_count = static_cast<u16>(stringtablecount);

    if (ctx_->props() & props::devstr)
    {
        head.stringtablefixup_offset = static_cast<u32>(script_.pos());
        head.stringtablefixup_count = 0;
    }

    head.fixup_offset = static_cast<u32>(script_.pos());
    head.fixup_count = 0;

    head.profile_offset = static_cast<u32>(script_.pos());
    head.profile_count = 0;

    head.flags = 0;
    head.name = resolve_string(name); // hash id!

    auto endpos = script_.pos();

    script_.pos(0);
    script_.write<u64>(ctx_->magic());
    script_.write<u32>(head.source_crc);
    script_.write<u32>(head.include_offset);
    script_.write<u32>(head.animtree_offset);
    script_.write<u32>(head.cseg_offset);
    script_.write<u32>(head.stringtablefixup_offset);

    if (ctx_->props() & props::devstr)
        script_.write<u32>(head.devblock_stringtablefixup_offset);

    script_.write<u32>(head.exports_offset);
    script_.write<u32>(head.imports_offset);
    script_.write<u32>(head.fixup_offset);
    script_.write<u32>(head.profile_offset);
    script_.write<u32>(head.cseg_size);

    if (ctx_->props() & props::size64)
        script_.write<u32>(head.name);
    else
        script_.write<u16>(static_cast<u16>(head.name));

    script_.write<u16>(head.stringtablefixup_count);
    script_.write<u16>(head.exports_count);
    script_.write<u16>(head.imports_count);
    script_.write<u16>(head.fixup_count);
    script_.write<u16>(head.profile_count);

    if (ctx_->props() & props::devstr)
        script_.write<u16>(head.devblock_stringtablefixup_count);

    script_.write<u8>(head.include_count);
    script_.write<u8>(head.animtree_count);
    script_.write<u8>(head.flags);
    script_.pos(endpos);

    auto dev_endpos = devmap_.pos();
    devmap_.pos(0);
    devmap_.write<u32>(devmap_count_);
    devmap_.pos(dev_endpos);

    return { buffer{ script_.data(), script_.pos() }, buffer{ devmap_.data(), devmap_.pos() } };
}

auto assembler::assemble_function(function& func) -> void
{
    auto labels = std::unordered_map<usize, std::string>{};
    func.index = script_.pos();
    func.size = 0;
    func_ = &func;

    for (auto& inst : func.instructions)
    {
        auto old_idx = inst->index;
        inst->index = func.index + func.size;

        align_instruction(*inst);

        func.size += inst->size;

        if (auto const itr = func.labels.find(old_idx); itr != func.labels.end())
        {
            labels.insert({ inst->index, itr->second });
        }
    }

    func.labels = std::move(labels);

    script_.pos(func.index);

    for (auto const& inst : func.instructions)
    {
        assemble_instruction(*inst);
    }

    export_ref entry;
    entry.checksum = 0;
    entry.offset = static_cast<u32>(func.index);
    entry.name = func.name;
    entry.params = func.params;
    entry.flags = func.flags;
    exports_.push_back(entry);
}

auto assembler::assemble_instruction(instruction const& inst) -> void
{
    script_.write<u8>(static_cast<u8>(ctx_->opcode_id(inst.opcode)));

    if ((ctx_->build() & build::dev_maps) != build::prod)
    {
        devmap_.write<u32>(static_cast<u32>(script_.pos()));
        devmap_.write<u16>(static_cast<u16>(inst.pos.line));
        devmap_.write<u16>(static_cast<u16>(inst.pos.column));
        devmap_count_++;
    }

    switch (inst.opcode)
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
        case opcode::OP_SafeSetVariableFieldCached:
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
        case opcode::OP_ProfileStart:
        case opcode::OP_ProfileStop:
        case opcode::OP_SafeDecTop:
        case opcode::OP_Nop:
        case opcode::OP_Abort:
        case opcode::OP_Object:
        case opcode::OP_ThreadObject:
        case opcode::OP_EvalLocalVariable:
        case opcode::OP_EvalLocalVariableRef:
            break;
        case opcode::OP_GetByte:
        case opcode::OP_GetNegByte:
            script_.write<u8>(static_cast<u8>(std::stoi(inst.data[0])));
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            script_.align(2);
            script_.write<u16>(static_cast<u16>(std::stoi(inst.data[0])));
            break;
        case opcode::OP_GetInteger:
            script_.align(4);
            script_.write<i32>((inst.data.size() == 2) ? -1 : std::stoi(inst.data[0]));
            break;
        case opcode::OP_GetFloat:
            script_.align(4);
            script_.write<f32>(std::stof(inst.data[0]));
            break;
        case opcode::OP_GetVector:
            script_.align(4);
            script_.write<f32>(std::stof(inst.data[0]));
            script_.write<f32>(std::stof(inst.data[1]));
            script_.write<f32>(std::stof(inst.data[2]));
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            script_.align(2);
            script_.write<u16>(0);
            break;
        case opcode::OP_GetAnimation:
            script_.align(4);
            script_.write<u32>(0);
            break;
        case opcode::OP_WaitTillMatch:
            script_.write<u8>(static_cast<u8>(std::stoi(inst.data[0])));
            break;
        case opcode::OP_VectorConstant:
            script_.write<u8>(static_cast<u8>(std::stoi(inst.data[0])));
            break;
        case opcode::OP_GetHash:
            script_.align(4);
            script_.write<u32>(ctx_->hash_id(inst.data[0]));
            break;
        case opcode::OP_SafeCreateLocalVariables:
            assemble_localvars(inst);
            break;
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_EvalLocalArrayRefCached:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_EvalLocalVariableRefCached:
            script_.write<u8>(static_cast<u8>(std::stoi(inst.data[0])));
            break;
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_ClearFieldVariable:
            script_.align(2);
            script_.write<u16>(0);
            break;
        case opcode::OP_ScriptFunctionCallPointer:
        case opcode::OP_ScriptMethodCallPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
            script_.write<u8>(static_cast<u8>(std::stoi(inst.data[0])));
            break;
        case opcode::OP_GetFunction:
            script_.align(4);
            script_.write<u32>(0);
            break;
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            script_.write<u8>(0);
            script_.align(4);
            script_.write<u32>(0);
            break;
        case opcode::OP_JumpOnFalse:
        case opcode::OP_JumpOnTrue:
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_JumpOnTrueExpr:
        case opcode::OP_Jump:
        case opcode::OP_JumpBack:
        case opcode::OP_DevblockBegin:
            assemble_jump(inst);
            break;
        case opcode::OP_Switch:
            assemble_switch(inst);
            break;
        case opcode::OP_EndSwitch:
            assemble_switch_table(inst);
            break;
        default:
            throw asm_error(std::format("unhandled opcode {} at index {:04X}", ctx_->opcode_name(inst.opcode), inst.index));
    }
}

auto assembler::assemble_localvars(instruction const& inst) -> void
{
    script_.write<u8>(static_cast<u8>(inst.data.size()));

    for (auto i = 0u; i < inst.data.size(); i++)
    {
        script_.align(2);
        script_.write<u16>(0);
    }
}

auto assembler::assemble_jump(instruction const& inst) -> void
{
    script_.align(2);
    script_.write<i16>(static_cast<i16>(resolve_label(inst.data[0]) - inst.index - inst.size));
}

auto assembler::assemble_switch(instruction const& inst) -> void
{
    script_.align(4);
    script_.write<i32>(static_cast<i32>(((resolve_label(inst.data[0]) + 4) & 0xFFFFFFFC) - inst.index - inst.size));
}

auto assembler::assemble_switch_table(instruction const& inst) -> void
{
    auto count = std::stoul(inst.data[0]);

    script_.align(4);
    script_.write<u32>(count);

    for (auto i = 0u; i < count; i++)
    {
        if (inst.data[1 + (4 * i)] == "case")
        {
            auto type = static_cast<switch_type>(std::stoul(inst.data[1 + (4 * i) + 1]));

            script_.write<u32>((type == switch_type::integer) ? ((std::stoi(inst.data[1 + (4 * i) + 2]) & 0xFFFFFF) + 0x800000) : i + 1);
            script_.write<i32>(static_cast<i32>(resolve_label(inst.data[1 + (4 * i) + 3]) - script_.pos() - 4));
        }
        else if (inst.data[1 + (4 * i)] == "default")
        {
            script_.write<u32>(0);
            script_.write<i32>(static_cast<i32>(resolve_label(inst.data[1 + (4 * i) + 1]) - script_.pos() - 4));
        }
        else
        {
            throw asm_error(std::format("invalid switch case {}", inst.data[1 + (4 * i)]));
        }
    }
}

auto assembler::process_string(std::string const& data) -> void
{
    if (!strpool_.contains(data))
    {
        auto pos = static_cast<u16>(script_.pos());
        script_.write_cstr(data);
        strpool_.insert({ data, pos });
    }
}

auto assembler::process_function(function const& func) -> void
{
    process_string(func.name);

    for (auto const& inst : func.instructions)
    {
        process_instruction(*inst);
    }
}

auto assembler::process_instruction(instruction const& inst) -> void
{
    switch (inst.opcode)
    {
        case opcode::OP_GetInteger:
            if (inst.data.size() == 2)
                process_string(inst.data[0]);
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            process_string(inst.data[0]);
            break;
        case opcode::OP_GetAnimation:
            process_string(inst.data[0]);
            process_string(inst.data[1]);
            break;
        case opcode::OP_SafeCreateLocalVariables:
        {
            for (auto const& entry : inst.data)
            {
                process_string(entry);
            }

            break;
        }
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_ClearFieldVariable:
            process_string(inst.data[0]);
            break;
        case opcode::OP_GetFunction:
            process_string(inst.data[0]);
            process_string(inst.data[1]);
            break;
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            process_string(inst.data[0]);
            process_string(inst.data[1]);
            break;
        case opcode::OP_EndSwitch:
        {
            auto count = std::stoul(inst.data[0]);

            for (auto i = 0u; i < count; i++)
            {
                if (inst.data[1 + (4 * i)] == "case")
                {
                    auto type = static_cast<switch_type>(std::stoul(inst.data[1 + (4 * i) + 1]));

                    if (type == switch_type::string)
                        process_string(inst.data[1 + (4 * i) + 2]);
                }
            }

            break;
        }
        default:
            break;
    }
}

auto assembler::align_instruction(instruction& inst) -> void
{
    inst.size = ctx_->opcode_size(inst.opcode);
    script_.seek(1);

    switch (inst.opcode)
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
        case opcode::OP_SafeSetVariableFieldCached:
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
        case opcode::OP_ProfileStart:
        case opcode::OP_ProfileStop:
        case opcode::OP_SafeDecTop:
        case opcode::OP_Nop:
        case opcode::OP_Abort:
        case opcode::OP_Object:
        case opcode::OP_ThreadObject:
        case opcode::OP_EvalLocalVariable:
        case opcode::OP_EvalLocalVariableRef:
            break;
        case opcode::OP_GetByte:
        case opcode::OP_GetNegByte:
            script_.seek(1);
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            inst.size += script_.align(2);
            script_.seek(2);
            break;
        case opcode::OP_GetInteger:
            inst.size += script_.align(4);
            if (inst.data.size() == 2)
                add_animref(inst.data, static_cast<u32>(script_.pos()));
            script_.seek(4);
            break;
        case opcode::OP_GetFloat:
            inst.size += script_.align(4);
            script_.seek(4);
            break;
        case opcode::OP_GetVector:
            inst.size += script_.align(4);
            script_.seek(12);
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            inst.size += script_.align(2);
            add_stringref(inst.data[0], string_type::literal, static_cast<u32>(script_.pos()));
            script_.seek(2);
            break;
        case opcode::OP_GetAnimation:
            inst.size += script_.align(4);
            add_animref(inst.data, static_cast<u32>(script_.pos()));
            script_.seek(4);
            break;
        case opcode::OP_WaitTillMatch:
            script_.seek(1);
            break;
        case opcode::OP_VectorConstant:
            script_.seek(1);
            break;
        case opcode::OP_GetHash:
            inst.size += script_.align(4);
            script_.seek(4);
            break;
        case opcode::OP_SafeCreateLocalVariables:
        {
            script_.seek(1);

            for (auto i = 0u; i < inst.data.size(); i++)
            {
                inst.size += script_.align(2) + 2;
                add_stringref(inst.data[i], string_type::canonical, static_cast<u32>(script_.pos()));
                script_.seek(2);
            }

            break;
        }
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_EvalLocalArrayRefCached:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_EvalLocalVariableRefCached:
            script_.seek(1);
            break;
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_ClearFieldVariable:
            inst.size += script_.align(2);
            add_stringref(inst.data[0], string_type::canonical, static_cast<u32>(script_.pos()));
            script_.seek(2);
            break;
        case opcode::OP_ScriptFunctionCallPointer:
        case opcode::OP_ScriptMethodCallPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
            script_.seek(1);
            break;
        case opcode::OP_GetFunction:
            inst.size += script_.align(4);
            script_.seek(4);
            add_importref(inst.data, static_cast<u32>(inst.index));
            break;
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            script_.seek(1);
            inst.size += script_.align(4);
            script_.seek(4);
            add_importref(inst.data, static_cast<u32>(inst.index));
            break;
        case opcode::OP_JumpOnFalse:
        case opcode::OP_JumpOnTrue:
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_JumpOnTrueExpr:
        case opcode::OP_Jump:
        case opcode::OP_JumpBack:
        case opcode::OP_DevblockBegin:
            inst.size += script_.align(2);
            script_.seek(2);
            break;
        case opcode::OP_Switch:
            inst.size += script_.align(4);
            script_.seek(4);
            break;
        case opcode::OP_EndSwitch:
        {
            inst.size += script_.align(4);
            script_.seek(4);

            auto count = std::stoul(inst.data[0]);

            for (auto i = 0u; i < count; i++)
            {
                if (inst.data[1 + (4 * i)] == "case" && static_cast<switch_type>(std::stoul(inst.data[1 + (4 * i) + 1])) == switch_type::string)
                {
                    add_stringref(inst.data[1 + (4 * i) + 2], string_type::literal, static_cast<u32>(script_.pos() + 2));
                }

                inst.size += 8;
                script_.seek(8);
            }

            break;
        }
        default:
            throw asm_error(std::format("unhandled opcode {} at index {:04X}", ctx_->opcode_name(inst.opcode), inst.index));
    }
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

auto assembler::resolve_string(std::string const& name) -> u16
{
    if (auto const itr = strpool_.find(name); itr != strpool_.end())
    {
        return itr->second;
    }

    throw asm_error(std::format("couldn't resolve string address of {}", name));
}

auto assembler::add_stringref(std::string const& str, string_type type, u32 ref) -> void
{
    for (auto& entry : strings_)
    {
        if (entry.name == str && entry.type == static_cast<u8>(type))
        {
            return entry.refs.push_back(ref);
        }
    }

    strings_.push_back({ str, u8(type), { ref } });
}

auto assembler::add_importref(std::vector<std::string> const& data, u32 ref) -> void
{
    for (auto& entry : imports_)
    {
        if (entry.space == data[0] && entry.name == data[1] && entry.params == std::stoi(data[2]) && entry.flags == std::stoi(data[3]))
        {
            return entry.refs.push_back(ref);
        }
    }

    import_ref new_entry;
    new_entry.space = data[0];
    new_entry.name = data[1];
    new_entry.params = static_cast<u8>(std::stoi(data[2]));
    new_entry.flags = static_cast<u8>(std::stoi(data[3]));
    new_entry.refs.push_back(ref);
    imports_.push_back(std::move(new_entry));
}

auto assembler::add_animref(std::vector<std::string> const& data, u32 ref) -> void
{
    for (auto& entry : anims_)
    {
        if (entry.name != data[0])
            continue;

        return (data[1] == "-1") ? entry.refs.push_back(ref) : entry.anims.push_back({ data[1], ref });
    }

    animtree_ref new_entry;
    new_entry.name = data[0];

    if (data[1] == "-1")
        new_entry.refs.push_back(ref);
    else
        new_entry.anims.push_back({ data[1], ref });

    anims_.push_back(std::move(new_entry));
}

} // namespace xsk::arc
