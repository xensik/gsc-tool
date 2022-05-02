// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "t6.hpp"

namespace xsk::arc::t6
{

auto disassembler::output() -> assembly::ptr
{
    return std::move(assembly_);
}

auto disassembler::output_raw() -> std::vector<std::uint8_t>
{
    output_ = std::make_unique<utils::byte_buffer>(0x100000);

    output_->write_string("// T6 GSC ASSEMBLY\n");
    output_->write_string("// Disassembled by https://github.com/xensik/gsc-tool\n");

    for (const auto& func : assembly_->functions)
    {
        this->print_function(func);
    }

    std::vector<std::uint8_t> output;

    output.resize(output_->pos());
    std::memcpy(output.data(), output_->buffer().data(), output.size());

    return output;
}

void disassembler::disassemble(const std::string& file, std::vector<std::uint8_t>& data)
{
    filename_ = file;
    script_ = std::make_unique<utils::byte_buffer>(data);
    assembly_ = std::make_unique<assembly>();
    exports_.clear();
    imports_.clear();
    strings_.clear();
    animtrees_.clear();
    stringlist_.clear();
    string_refs_.clear();
    anim_refs_.clear();
    import_refs_.clear();
    labels_.clear();
    std::memset(&header_, 0, sizeof(header_));

    // header
    header_.magic = script_->read<std::uint64_t>();

    if (header_.magic != magic)
    {
        throw error("invalid binary gsc file '" + filename_ + "'!");
    }

    header_.source_crc = script_->read<std::uint32_t>();
    header_.include_offset = script_->read<std::uint32_t>();
    header_.animtree_offset = script_->read<std::uint32_t>();
    header_.cseg_offset = script_->read<std::uint32_t>();
    header_.stringtablefixup_offset = script_->read<std::uint32_t>();
    header_.exports_offset = script_->read<std::uint32_t>();
    header_.imports_offset = script_->read<std::uint32_t>();
    header_.fixup_offset = script_->read<std::uint32_t>();
    header_.profile_offset = script_->read<std::uint32_t>();
    header_.cseg_size = script_->read<std::uint32_t>();
    header_.name = script_->read<std::uint16_t>();
    header_.stringtablefixup_count = script_->read<std::uint16_t>();
    header_.exports_count = script_->read<std::uint16_t>();
    header_.imports_count = script_->read<std::uint16_t>();
    header_.fixup_count = script_->read<std::uint16_t>();
    header_.profile_count = script_->read<std::uint16_t>();
    header_.include_count = script_->read<std::uint8_t>();
    header_.animtree_count = script_->read<std::uint8_t>();
    header_.flags = script_->read<std::uint8_t>();

    // string list
    script_->pos(64);

    while (script_->pos() < header_.include_offset)
    {
        auto pos = script_->pos();
        stringlist_.insert({ pos, script_->read_c_string() });
    }

    // include list
    script_->pos(header_.include_offset);

    for (auto i = 0; i < header_.include_count; i++)
    {
        assembly_->includes.push_back(stringlist_.at(script_->read<std::uint32_t>()));
    }

    // animtree list
    script_->pos(header_.animtree_offset);

    for (auto i = 0; i < header_.animtree_count; i++)
    {
        auto entry = std::make_shared<animtree_ref>();
        entry->name = stringlist_.at(script_->read<std::uint16_t>());
        auto ref_count = script_->read<std::uint16_t>();
        auto anim_count = script_->read<std::uint16_t>();
        script_->seek(2);

        for (auto j = 0; j < ref_count; j++)
        {
            entry->refs.push_back(script_->read<std::uint32_t>());
        }

        for (auto k = 0; k < anim_count; k++)
        {
            auto name = stringlist_.at(script_->read<std::uint32_t>());
            auto ref = script_->read<std::uint32_t>();
            entry->anims.push_back({ name, ref });
        }

        for (auto& anim : entry->anims)
        {
            anim_refs_.insert({ anim.ref, entry });
        }

        animtrees_.push_back(entry);
    }

    // stringtable list
    script_->pos(header_.stringtablefixup_offset);

    for (auto i = 0; i < header_.stringtablefixup_count; i++)
    {
        auto entry = std::make_shared<string_ref>();
        entry->name = stringlist_.at(script_->read<std::uint16_t>());
        auto ref_count = script_->read<std::uint8_t>();
        entry->type = script_->read<std::uint8_t>();

        for (auto j = 0; j < ref_count; j++)
        {
            auto ref = script_->read<std::uint32_t>();
            entry->refs.push_back(ref);
            string_refs_.insert({ ref, entry });
        }

        strings_.push_back(entry);
    }

    // import list
    script_->pos(header_.imports_offset);

    for (auto i = 0; i < header_.imports_count; i++)
    {
        auto entry = std::make_shared<import_ref>();
        entry->name = stringlist_.at(script_->read<std::uint16_t>());
        entry->space = stringlist_.at(script_->read<std::uint16_t>());
        auto ref_count = script_->read<std::uint16_t>();
        entry->params = script_->read<std::uint8_t>();
        entry->flags = script_->read<std::uint8_t>();

        for (auto j = 0; j < ref_count; j++)
        {
            auto ref = script_->read<std::uint32_t>();
            entry->refs.push_back(ref);
            import_refs_.insert({ ref, entry });
        }

        imports_.push_back(entry);
    }

    // export list
    script_->pos(header_.exports_offset);

    for (auto i = 0; i < header_.exports_count; i++)
    {
        auto entry = std::make_shared<export_ref>();
        entry->checksum = script_->read<std::uint32_t>();
        entry->offset = script_->read<std::uint32_t>();
        entry->name = stringlist_.at(script_->read<std::uint16_t>());
        entry->space = "";
        entry->params = script_->read<std::uint8_t>();
        entry->flags = script_->read<std::uint8_t>();
        exports_.push_back(entry);
    }

    for (auto i = 0u; i < exports_.size(); i++)
    {
        auto& entry = exports_[i];

        if (i < exports_.size() - 1)
        {
            entry->size = (exports_[i+1]->offset - entry->offset);

            auto end_pos = entry->offset + entry->size - 4;

            script_->pos(end_pos);

            if (script_->read<std::uint32_t>() == 0)
            {
                entry->size -= 4;

                for (auto j = 1; j < 4; j++)
                {
                    script_->pos(end_pos - j);
                    auto op = script_->read<std::uint8_t>();

                    if (op <= 0x01) break;

                    entry->size--;
                }
            }
        }
        else
        {
            entry->size = (header_.cseg_offset + header_.cseg_size) - entry->offset;
        }

        script_->pos(entry->offset);

        assembly_->functions.push_back(std::make_unique<function>());
        auto& func = assembly_->functions.back();
        func->index = static_cast<std::uint32_t>(script_->pos());
        func->size = entry->size;
        func->params = entry->params;
        func->flags = entry->flags;
        func->name = entry->name;

        this->disassemble_function(func);

        func->labels = labels_;
        labels_.clear();
    }

    // fixup list ...
    // profile list ...
}

void disassembler::disassemble_function(const function::ptr& func)
{
    auto size = func->size;

    while (size > 0)
    {
        func->instructions.push_back(std::make_unique<instruction>());
        auto& inst = func->instructions.back();
        inst->index = static_cast<std::uint32_t>(script_->pos());
        inst->opcode = script_->read<std::uint8_t>();
        inst->size = opcode_size(inst->opcode);

        if (size < 4 && inst->opcode >= std::uint8_t(opcode::OP_Count))
        {
            func->instructions.pop_back();
            break;
        }

        this->disassemble_instruction(inst);
        size -= inst->size;
    }

    for (auto i = func->instructions.size() - 1; i >= 1; i--)
    {
        auto& inst = func->instructions.at(i);
        auto& last = func->instructions.at(i-1);

        if (labels_.contains(inst->index))
            break;

        if (inst->opcode <= 0x01 && (last->opcode > 0x01))
            break;

        func->instructions.pop_back();
    }
}

void disassembler::disassemble_instruction(const instruction::ptr& inst)
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
            break;
        case opcode::OP_GetByte:
        case opcode::OP_GetNegByte:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            inst->size += script_->align(2);
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint16_t>()));
            break;
        case opcode::OP_GetInteger:
            inst->size += script_->align(4);
            inst->data.push_back(utils::string::va("%i", script_->read<std::int32_t>()));
            break;
        case opcode::OP_GetFloat:
            inst->size += script_->align(4);
            inst->data.push_back(utils::string::float_string(script_->read<float>()));
            break;
        case opcode::OP_GetVector:
            inst->size += script_->align(4);
            inst->data.push_back(utils::string::float_string(script_->read<float>()));
            inst->data.push_back(utils::string::float_string(script_->read<float>()));
            inst->data.push_back(utils::string::float_string(script_->read<float>()));
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            disassemble_string(inst);
            break;
        case opcode::OP_GetAnimation:
            disassemble_animation(inst);
            break;
        case opcode::OP_WaitTillMatch:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            break;
        case opcode::OP_VectorConstant:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            break;
        case opcode::OP_GetHash:
            inst->size += script_->align(4);
            inst->data.push_back(resolver::dvar_name(script_->read<std::uint32_t>()));
            break;
        case opcode::OP_SafeCreateLocalVariables:
            disassemble_localvars(inst);
            break;
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_EvalLocalArrayRefCached:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_EvalLocalVariableRefCached:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            break;
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_ClearFieldVariable:
            disassemble_string(inst);
            break;
        case opcode::OP_ScriptFunctionCallPointer:
        case opcode::OP_ScriptMethodCallPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            break;
        case opcode::OP_GetFunction:
            disassemble_import(inst);
            break;
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            script_->seek(1);
            disassemble_import(inst);
            break;
        case opcode::OP_JumpOnFalse:
        case opcode::OP_JumpOnTrue:
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_JumpOnTrueExpr:
        case opcode::OP_Jump:
        case opcode::OP_JumpBack:
            disassemble_jump(inst);
            break;
        case opcode::OP_Switch:
            disassemble_switch(inst);
            break;
        case opcode::OP_EndSwitch:
            disassemble_end_switch(inst);
            break;
        case opcode::OP_DevblockBegin:
            disassemble_devblock(inst);
            break;
        default:
            throw disasm_error(utils::string::va("Unhandled opcode 0x%X at index '%04X'!", inst->opcode, inst->index));
    }
}

void disassembler::disassemble_string(const instruction::ptr& inst)
{
    inst->size += script_->align(2);

    const auto& entry = string_refs_.at(script_->pos());

    inst->data.push_back(entry->name);
    script_->seek(2);
}

void disassembler::disassemble_animation(const instruction::ptr& inst)
{
    inst->size += script_->align(4);

    const auto ref = script_->pos();
    const auto& entry = anim_refs_.at(ref);

    inst->data.push_back(entry->name);

    for (const auto& anim : entry->anims)
    {
        if (anim.ref == ref)
        {
            inst->data.push_back(anim.name);
            break;
        }
    }

    script_->seek(4);
}

void disassembler::disassemble_localvars(const instruction::ptr& inst)
{
    const auto count = script_->read<std::uint8_t>();

    for (auto i = 0u; i < count; i++)
    {
        disassemble_string(inst);
        inst->size += 2;
    }
}

void disassembler::disassemble_import(const instruction::ptr& inst)
{
    inst->size += script_->align(4);
    script_->seek(4);

    const auto& entry = import_refs_.at(inst->index);

    inst->data.push_back(entry->space);
    inst->data.push_back(entry->name);
}

void disassembler::disassemble_jump(const instruction::ptr& inst)
{
    inst->size += script_->align(2);

    const auto addr = inst->index + inst->size + script_->read<std::int16_t>();
    const auto label = utils::string::va("loc_%X", addr);

    inst->data.push_back(label);
    labels_.insert({ addr, label });
}

void disassembler::disassemble_switch(const instruction::ptr& inst)
{
    inst->size += script_->align(4);

    const auto addr = script_->read<std::int32_t>() + script_->pos();
    const auto label = utils::string::va("loc_%X", addr);

    inst->data.push_back(label);
    labels_.insert({ addr, label });
}

void disassembler::disassemble_end_switch(const instruction::ptr& inst)
{
    inst->size += script_->align(4);

    const auto& itr = labels_.find(script_->pos());

    if (itr != labels_.end())
    {
        for (const auto& entry : assembly_->functions.back()->instructions)
        {
            if (opcode(entry->opcode) == opcode::OP_Switch)
            {
                if (entry->data[0] == itr->second)
                {
                    labels_.erase(script_->pos());

                    const auto label = utils::string::va("loc_%X", inst->index);
                    const auto& itr2 = labels_.find(inst->index);

                    if (itr2 == labels_.end())
                    {
                        labels_.insert({ inst->index, label });
                    }

                    entry->data[0] = label;
                    break;
                }
            }
        }
    }

    auto numerical = false;
    const auto count = script_->read<std::uint32_t>();
    inst->data.push_back(utils::string::va("%i", count));

    for (auto i = 0u; i < count; i++)
    {
        const auto value = script_->read<std::uint32_t>();

        if (value < 0x40000 && value > 0)
        {
            inst->data.push_back("case");
            const auto& entry = string_refs_.at(script_->pos() - 2);
            inst->data.push_back(entry->name);
        }
        else if (value == 0)
        {
            inst->data.push_back("default");
        }
        else
        {
            numerical = true;
            inst->data.push_back("case");
            inst->data.push_back(utils::string::va("%i", (value - 0x800000) & 0xFFFFFF));
        }

        const auto addr = script_->read<std::int32_t>() + script_->pos();
        const auto label = utils::string::va("loc_%X", addr);

        inst->data.push_back(label);
        labels_.insert({ addr, label });

        inst->size += 8;
    }

    inst->data.push_back((numerical) ? "i" : "s");
}

void disassembler::disassemble_devblock(const instruction::ptr& inst)
{
    inst->size += script_->align(2);

    const auto addr = inst->index + inst->size + script_->read<std::int16_t>();
    const auto label = utils::string::va("loc_%X", addr);

    inst->data.push_back(label);
    labels_.insert({ addr, label });
}

void disassembler::print_function(const function::ptr& func)
{
    output_->write_string("\n");
    output_->write_string(utils::string::va("sub_%s %i %i\n", func->name.data(), func->params, func->flags));

    for (const auto& inst : func->instructions)
    {
        const auto& itr = func->labels.find(inst->index);

        if (itr != func->labels.end())
        {
            output_->write_string(utils::string::va("\t%s\n", itr->second.data()));
        }

        this->print_instruction(inst);
    }

    output_->write_string(utils::string::va("end_%s\n", func->name.data()));
}

void disassembler::print_instruction(const instruction::ptr& inst)
{
    output_->write_string(utils::string::va("\t\t%s(", resolver::opcode_name(inst->opcode).data()));

    switch (opcode(inst->opcode))
    {
        case opcode::OP_GetHash:
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
        case opcode::OP_ClearFieldVariable:
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
            output_->write_string(utils::string::va("\"%s\"", inst->data[0].data()));
            break;
        case opcode::OP_GetAnimation:
        case opcode::OP_GetFunction:
        case opcode::OP_CallBuiltin:
        case opcode::OP_CallBuiltinMethod:
        case opcode::OP_ScriptFunctionCall:
        case opcode::OP_ScriptMethodCall:
        case opcode::OP_ScriptThreadCall:
        case opcode::OP_ScriptMethodThreadCall:
            output_->write_string(utils::string::va("\"%s\", \"%s\"", inst->data[0].data(), inst->data[1].data()));
            break;
        case opcode::OP_SafeCreateLocalVariables:
            for (const auto& d : inst->data)
            {
                output_->write_string(utils::string::va("\"%s\"%s", d.data(), &d == &inst->data.back() ? "" : ", "));
            }
            break;
        case opcode::OP_EndSwitch:
            output_->write_string(utils::string::va("%s", inst->data[0].data()));
            {
                std::uint32_t totalcase = std::stoul(inst->data[0]);
                auto numerical = inst->data.back() == "i";
                auto index = 0;
                for (auto casenum = 0u; casenum < totalcase; casenum++)
                {
                    if (inst->data[1 + index] == "case")
                    {
                        auto fmt = numerical ? ", %s, %s, %s"s : ", %s, \"%s\", %s"s;
                        output_->write_string(utils::string::va(fmt, inst->data[1 + index].data(), inst->data[1 + index + 1].data(), inst->data[1 + index + 2].data()));
                        index += 3;
                    }
                    else if (inst->data[1 + index] == "default")
                    {
                        output_->write_string(utils::string::va(", %s, %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data()));
                        index += 2;
                    }
                }
            }
            break;
        default:
            for (const auto& d : inst->data)
            {
                output_->write_string(utils::string::va("%s%s", d.data(), &d == &inst->data.back() ? "" : ", "));
            }
            break;
    }

    output_->write_string(");\n");
}

} // namespace xsk::arc::t6
