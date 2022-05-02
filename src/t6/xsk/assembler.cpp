// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "t6.hpp"

namespace xsk::arc::t6
{

auto assembler::output() -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> output;

    if (script_ == nullptr) return output;

    output.resize(script_->pos());
    std::memcpy(output.data(), script_->buffer().data(), output.size());

    return output;
}

void assembler::assemble(const std::string&, std::vector<std::uint8_t>&)
{
    throw error("assemble from source unimplemented!");
}

void assembler::assemble(const std::string& file, assembly::ptr& data)
{
    script_ = std::make_unique<utils::byte_buffer>(0x100000);
    filename_ = file;
    assembly_ = std::move(data);
    stringlist_.clear();
    exports_.clear();
    imports_.clear();
    animtrees_.clear();
    stringtables_.clear();
    std::memset(&header_, 0, sizeof(header_));

    // skip header
    script_->pos(64);

    // assemble strings
    process_string(filename_);

    for (const auto& func : assembly_->functions)
    {
        process_function(func);
    }

    for (const auto& entry : assembly_->includes)
    {
        process_string(entry);
    }

    // assemble includes
    header_.include_offset = script_->pos();
    header_.include_count = static_cast<std::uint8_t>(assembly_->includes.size());

    for (const auto& entry : assembly_->includes)
    {
        script_->write<std::uint32_t>(string_offset(entry));
    }

    // assemble functions
    header_.cseg_offset = script_->pos();

    for (const auto& func : assembly_->functions)
    {
        script_->align(4);
        script_->write<std::uint32_t>(0);
        assemble_function(func);
    }

    header_.cseg_size = script_->pos() - header_.cseg_offset;

    header_.source_crc = 0; // calcule_crc();

    // assemble exports
    header_.exports_offset = script_->pos();
    header_.exports_count = static_cast<std::uint16_t>(exports_.size());

    for (const auto& entry : exports_)
    {
        script_->write<std::uint32_t>(entry.checksum);
        script_->write<std::uint32_t>(entry.offset);
        script_->write<std::uint16_t>(string_offset(entry.name));
        script_->write<std::uint8_t>(entry.params);
        script_->write<std::uint8_t>(entry.flags);
    }

    // assemble imports
    header_.imports_offset = script_->pos();
    header_.imports_count = static_cast<std::uint16_t>(imports_.size());

    for (const auto& entry : imports_)
    {
        script_->write<std::uint16_t>(string_offset(entry.name));
        script_->write<std::uint16_t>(string_offset(entry.space));
        script_->write<std::uint16_t>(static_cast<std::uint16_t>(entry.refs.size()));
        script_->write<std::uint8_t>(entry.params);
        script_->write<std::uint8_t>(entry.flags);

        for (const auto& ref : entry.refs)
        {
            script_->write<std::uint32_t>(ref);
        }
    }

    // assemble animtrees
    header_.animtree_offset = script_->pos();
    header_.animtree_count = static_cast<std::uint8_t>(animtrees_.size());

    for (const auto& entry : animtrees_)
    {
        script_->write<std::uint16_t>(string_offset(entry.name));
        script_->write<std::uint16_t>(static_cast<std::uint16_t>(entry.refs.size()));
        script_->write<std::uint16_t>(static_cast<std::uint16_t>(entry.anims.size()));
        script_->seek(2);

        for (const auto& ref : entry.refs)
        {
            script_->write<std::uint32_t>(ref);
        }

        for (const auto& anim : entry.anims)
        {
            script_->write<std::uint32_t>(string_offset(anim.name));
            script_->write<std::uint32_t>(anim.ref);
        }
    }

    // assemble stringtable
    header_.stringtablefixup_offset = script_->pos();
    header_.stringtablefixup_count = static_cast<std::uint16_t>(stringtables_.size());

    for (const auto& entry : stringtables_)
    {
        script_->write<std::uint16_t>(string_offset(entry.name));
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(entry.refs.size()));
        script_->write<std::uint8_t>(entry.type);

        for (const auto& ref : entry.refs)
        {
            script_->write<std::uint32_t>(ref);
        }
    }

    // assemble fixup
    header_.fixup_offset = script_->pos();
    header_.fixup_count = 0;

    // assemble profile
    header_.profile_offset = script_->pos();
    header_.profile_count = 0;

    header_.flags = 0;
    header_.name = string_offset(filename_);

    auto endpos = script_->pos();

    // assemble header
    script_->pos(0);
    script_->write<std::uint64_t>(magic);
    script_->write<std::uint32_t>(header_.source_crc);
    script_->write<std::uint32_t>(header_.include_offset);
    script_->write<std::uint32_t>(header_.animtree_offset);
    script_->write<std::uint32_t>(header_.cseg_offset);
    script_->write<std::uint32_t>(header_.stringtablefixup_offset);
    script_->write<std::uint32_t>(header_.exports_offset);
    script_->write<std::uint32_t>(header_.imports_offset);
    script_->write<std::uint32_t>(header_.fixup_offset);
    script_->write<std::uint32_t>(header_.profile_offset);
    script_->write<std::uint32_t>(header_.cseg_size);
    script_->write<std::uint16_t>(header_.name);
    script_->write<std::uint16_t>(header_.stringtablefixup_count);
    script_->write<std::uint16_t>(header_.exports_count);
    script_->write<std::uint16_t>(header_.imports_count);
    script_->write<std::uint16_t>(header_.fixup_count);
    script_->write<std::uint16_t>(header_.profile_count);
    script_->write<std::uint8_t>(header_.include_count);
    script_->write<std::uint8_t>(header_.animtree_count);
    script_->write<std::uint8_t>(header_.flags);
    script_->pos(endpos);
}

void assembler::assemble_function(const function::ptr& func)
{
    func->index = script_->pos();
    func->size = 0;
    labels_.clear();

    for (const auto& inst : func->instructions)
    {
        auto old_idx = inst->index;
        inst->index = func->index + func->size;

        align_instruction(inst);

        func->size += inst->size;

        const auto& itr = func->labels.find(old_idx);

        if (itr != func->labels.end())
        {
            labels_.insert({ inst->index, itr->second });
        }
    }

    script_->pos(func->index);

    for (const auto& inst : func->instructions)
    {
        assemble_instruction(inst);
    }

    export_ref obj;
    obj.checksum = 0; // calculate_checksum();
    obj.offset = func->index;
    obj.name = func->name;
    obj.params = func->params;
    obj.flags = func->flags;
    exports_.push_back(obj);
}

void assembler::assemble_instruction(const instruction::ptr& inst)
{
    switch (opcode(inst->opcode))
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
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            break;
        case opcode::OP_GetByte:
        case opcode::OP_GetNegByte:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stoi(inst->data[0])));
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->align(2);
            script_->write<std::uint16_t>(static_cast<std::uint16_t>(std::stoi(inst->data[0])));
            break;
        case opcode::OP_GetInteger:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->align(4);
            script_->write<std::int32_t>(std::stoi(inst->data[0]));
            break;
        case opcode::OP_GetFloat:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->align(4);
            script_->write<float>(std::stof(inst->data[0]));
            break;
        case opcode::OP_GetVector:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->align(4);
            script_->write<float>(std::stof(inst->data[0]));
            script_->write<float>(std::stof(inst->data[1]));
            script_->write<float>(std::stof(inst->data[2]));
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->align(2);
            script_->write<std::uint16_t>(0);
            break;
        case opcode::OP_GetAnimation:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->align(4);
            script_->write<std::uint32_t>(0);
            break;
        case opcode::OP_WaitTillMatch:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stoi(inst->data[0])));
            break;
        case opcode::OP_VectorConstant:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stoi(inst->data[0])));
            break;
        case opcode::OP_GetHash:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->align(4);
            script_->write<std::uint32_t>(static_cast<std::uint32_t>(std::stoul(inst->data[0], 0, 16)));
            break;
        case opcode::OP_SafeCreateLocalVariables:
            assemble_localvars(inst);
            break;
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_EvalLocalArrayRefCached:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_EvalLocalVariableRefCached:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stoi(inst->data[0])));
            break;
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_ClearFieldVariable:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->align(2);
            script_->write<std::uint16_t>(0);
            break;
        case opcode::OP_ScriptFunctionCallPointer:
        case opcode::OP_ScriptMethodCallPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stoi(inst->data[0])));
            break;
        case opcode::OP_GetFunction:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->align(4);
            script_->write<std::uint32_t>(0);
            break;
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
            script_->write<std::uint8_t>(0);
            script_->align(4);
            script_->write<std::uint32_t>(0);
            break;
        case opcode::OP_JumpOnFalse:
        case opcode::OP_JumpOnTrue:
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_JumpOnTrueExpr:
        case opcode::OP_Jump:
        case opcode::OP_JumpBack:
            assemble_jump(inst);
            break;
        case opcode::OP_Switch:
            assemble_switch(inst);
            break;
        case opcode::OP_EndSwitch:
            assemble_end_switch(inst);
            break;
        case opcode::OP_DevblockBegin:
        case opcode::OP_DevblockEnd:
            assemble_devblock(inst);
            break;
        default:
            throw asm_error(utils::string::va("Unhandled opcode 0x%X at index '%04X'!", inst->opcode, inst->index));
    }
}

void assembler::assemble_localvars(const instruction::ptr& inst)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->data.size()));

    for (auto i = 0u; i < inst->data.size(); i++)
    {
        script_->align(2);
        script_->write<std::uint16_t>(0);
    }
}

void assembler::assemble_jump(const instruction::ptr& inst)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    const auto addr = static_cast<std::int16_t>(resolve_label(inst->data[0]) - inst->index - inst->size);

    script_->align(2);
    script_->write<std::int16_t>(addr);
}

void assembler::assemble_switch(const instruction::ptr& inst)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    const std::int32_t addr = ((resolve_label(inst->data[0]) + 4) & 0xFFFFFFFC) - inst->index - inst->size;

    script_->align(4);
    script_->write<std::int32_t>(addr);
}

void assembler::assemble_end_switch(const instruction::ptr& inst)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    const auto count = std::stoul(inst->data[0]);
    const auto numerical = inst->data.back() == "i";

    script_->align(4);
    script_->write<std::uint32_t>(count);

    for (auto i = 0u; i < count; i++)
    {
        if (inst->data[1 + (3 * i)] == "case")
        {
            if (numerical /*&& utils::string::is_number(inst->data[1 + (3 * i) + 1])*/)
            {
                script_->write<uint32_t>((std::stoi(inst->data[1 + (3 * i) + 1]) & 0xFFFFFF) + 0x800000);
            }
            else
            {
                script_->write<uint32_t>(i + 1);
            }

            const std::int32_t addr = resolve_label(inst->data[1 + (3 * i) + 2]) - script_->pos() - 4;

            script_->write<int32_t>(addr);
        }
        else if (inst->data[1 + (3 * i)] == "default")
        {
            script_->write<uint32_t>(0);

            const std::int32_t addr = resolve_label(inst->data[1 + (3 * i) + 1]) - script_->pos() - 4;

            script_->write<int32_t>(addr);
        }
    }
}

void assembler::assemble_devblock(const instruction::ptr& inst)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    const auto addr = static_cast<std::int16_t>(resolve_label(inst->data[0]) - inst->index - inst->size);

    script_->align(2);
    script_->write<std::int16_t>(addr);
}

void assembler::align_instruction(const instruction::ptr& inst)
{
    inst->size = opcode_size(inst->opcode);
    script_->seek(1);

    switch (opcode(inst->opcode))
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
            script_->seek(1);
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            inst->size += script_->align(2);
            script_->seek(2);
            break;
        case opcode::OP_GetInteger:
            inst->size += script_->align(4);
            script_->seek(4);
            break;
        case opcode::OP_GetFloat:
            inst->size += script_->align(4);
            script_->seek(4);
            break;
        case opcode::OP_GetVector:
            inst->size += script_->align(4);
            script_->seek(12);
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            inst->size += script_->align(2);
            add_string_reference(inst->data[0], string_type::literal, script_->pos());
            script_->seek(2);
            break;
        case opcode::OP_GetAnimation:
            inst->size += script_->align(4);
            add_anim_reference(inst->data, script_->pos());
            script_->seek(4);
            break;
        case opcode::OP_WaitTillMatch:
            script_->seek(1);
            break;
        case opcode::OP_VectorConstant:
            script_->seek(1);
            break;
        case opcode::OP_GetHash:
            inst->size += script_->align(4);
            script_->seek(4);
            break;
        case opcode::OP_SafeCreateLocalVariables:
            script_->seek(1);
            {
                for (auto i = 0u; i < inst->data.size(); i++)
                {
                    inst->size += script_->align(2) + 2;
                    add_string_reference(inst->data[i], string_type::canonical, script_->pos());
                    script_->seek(2);
                }
            }
            break;
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_EvalLocalArrayRefCached:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_EvalLocalVariableRefCached:
            script_->seek(1);
            break;
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_ClearFieldVariable:
            inst->size += script_->align(2);
            add_string_reference(inst->data[0], string_type::canonical, script_->pos());
            script_->seek(2);
            break;
        case opcode::OP_ScriptFunctionCallPointer:
        case opcode::OP_ScriptMethodCallPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
            script_->seek(1);
            break;
        case opcode::OP_GetFunction:
            inst->size += script_->align(4);
            script_->seek(4);
            add_import_reference(inst->data, inst->index);
            break;
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            script_->seek(1);
            inst->size += script_->align(4);
            script_->seek(4);
            add_import_reference(inst->data, inst->index);
            break;
        case opcode::OP_JumpOnFalse:
        case opcode::OP_JumpOnTrue:
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_JumpOnTrueExpr:
        case opcode::OP_Jump:
        case opcode::OP_JumpBack:
            inst->size += script_->align(2);
            script_->seek(2);
            break;
        case opcode::OP_Switch:
            inst->size += script_->align(4);
            script_->seek(4);
            break;
        case opcode::OP_EndSwitch:
        {
            inst->size += script_->align(4);
            script_->seek(4);

            const auto count = std::stoul(inst->data[0]);
            const auto numerical = inst->data.back() == "i";

            for (auto i = 0u; i < count; i++)
            {
                if (inst->data[1 + (3 * i)] == "case")
                {
                    if (!numerical /*|| !utils::string::is_number(inst->data[1 + (3 * i) + 1])*/)
                    {
                        add_string_reference(inst->data[1 + (3 * i) + 1], string_type::literal, script_->pos() + 2);
                    }
                }

                inst->size += 8;
                script_->seek(8);
            }
        }
            break;
        case opcode::OP_DevblockBegin:
        case opcode::OP_DevblockEnd:
            inst->size += script_->align(2);
            script_->seek(2);
            break;
        default:
            throw asm_error(utils::string::va("Unhandled opcode 0x%X at index '%04X'!", inst->opcode, inst->index));
    }
}

void assembler::process_string(const std::string& data)
{
    if (!stringlist_.contains(data))
    {
        auto pos = static_cast<std::uint16_t>(script_->pos());
        script_->write_c_string(data);
        stringlist_.insert({ data, pos });
    }
}

void assembler::process_function(const function::ptr& func)
{
    process_string(func->name);

    for (const auto& inst : func->instructions)
    {
        process_instruction(inst);
    }
}

void assembler::process_instruction(const instruction::ptr& inst)
{
    switch (opcode(inst->opcode))
    {
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            process_string(inst->data[0]);
            break;
        case opcode::OP_GetAnimation:
            process_string(inst->data[0]);
            process_string(inst->data[1]);
            break;
        case opcode::OP_SafeCreateLocalVariables:
        {
            for (const auto& entry : inst->data)
            {
                process_string(entry);
            }
        }
            break;
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_ClearFieldVariable:
            process_string(inst->data[0]);
            break;
        case opcode::OP_GetFunction:
            process_string(inst->data[0]);
            process_string(inst->data[1]);
            break;
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            process_string(inst->data[0]);
            process_string(inst->data[1]);
            break;
        case opcode::OP_EndSwitch:
        {
            const auto count = std::stoul(inst->data[0]);
            const auto numerical = inst->data.back() == "i";

            for (auto i = 0u; i < count; i++)
            {
                if (inst->data[1 + (3 * i)] == "case")
                {
                    if (!numerical /*|| !utils::string::is_number(inst->data[1 + (3 * i) + 1])*/)
                    {
                        process_string(inst->data[1 + (3 * i) + 1]);
                    }
                }
            }
        }
            break;
        default:
            break;
    }
}

auto assembler::resolve_label(const std::string& name) -> std::int32_t
{
    for (const auto& func : labels_)
    {
        if (func.second == name)
        {
            return func.first;
        }
    }

    throw asm_error("Couldn't resolve label address of '" + name + "'!");
}

auto assembler::string_offset(const std::string& name) -> std::uint16_t
{
    const auto& itr = stringlist_.find(name);

    if (itr != stringlist_.end())
    {
        return itr->second;
    }

    throw asm_error("couldn't resolve string assembly address of '" + name + "'!");
}

void assembler::add_string_reference(const std::string& str, string_type type, std::uint32_t ref)
{
    for (auto& entry : stringtables_)
    {
        if (entry.name == str && entry.type == std::uint8_t(type))
        {
            entry.refs.push_back(ref);
            return;
        }
    }

    stringtables_.push_back({ str, std::uint8_t(type), { ref } });
}

void assembler::add_import_reference(const std::vector<std::string>& data, std::uint32_t ref)
{
    for (auto& entry : imports_)
    {
        if (entry.space == data[0] && entry.name == data[1] && entry.params == std::stoi(data[2]) && entry.flags == std::stoi(data[3]))
        {
            entry.refs.push_back(ref);
            return;
        }
    }

    import_ref n;
    n.space = data[0];
    n.name = data[1];
    n.params = static_cast<std::uint8_t>(std::stoi(data[2]));
    n.flags = static_cast<std::uint8_t>(std::stoi(data[3]));
    n.refs.push_back(ref);
    imports_.push_back(std::move(n));
}

void assembler::add_anim_reference(const std::vector<std::string>& data, std::uint32_t ref)
{
    for (auto& entry : animtrees_)
    {
        if (entry.name == data[0])
        {
            entry.anims.push_back({ data[1], ref });
            return;
        }
    }

    animtree_ref n;
    n.name = data[0];
    n.anims.push_back({ data[1], ref });
    animtrees_.push_back(std::move(n));
}

} // namespace xsk::arc::t6
