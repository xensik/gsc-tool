// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "t6.hpp"

namespace xsk::gsc::t6
{

auto disassembler::output() -> arc::asm_data_ptr
{
    return std::move(data_);
}

auto disassembler::output_raw() -> std::vector<std::uint8_t>
{
    output_ = std::make_unique<utils::byte_buffer>(0x100000);

    output_->write_string("// T6 PC GSCASM\n");
    output_->write_string("// Disassembled by https://github.com/xensik/gsc-tool\n");

    for (auto& func : data_->functions)
    {
        this->print_function(func);
    }

    std::vector<std::uint8_t> output;

    output.resize(output_->pos());
    memcpy(output.data(), output_->buffer().data(), output.size());

    return output;
}

void disassembler::disassemble(const std::string& file, std::vector<std::uint8_t>& data)
{
    filename_ = file;
    script_ = std::make_unique<utils::byte_buffer>(data);
    data_ = std::make_unique<arc::asm_data>();

    this->disassemble_header();
    this->disassemble_strings();
    this->disassemble_includes();
    this->disassemble_animtrees();
    this->disassemble_stringtable();
    this->disassemble_imports();
    this->disassemble_exports();
}

void disassembler::disassemble_header()
{
    header_.magic = script_->read<std::uint64_t>();
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
}

void disassembler::disassemble_strings()
{
    script_->pos(0x40);

    while(script_->pos() < header_.include_offset)
    {
        std::uint16_t pos = script_->pos();
        string_refs_.insert({pos, script_->read_c_string() });
    }
}

void disassembler::disassemble_includes()
{
    script_->pos(header_.include_offset);

    for(auto i = 0; i < header_.include_count; i++)
    {
        includes_.push_back(string_refs_.at(script_->read<std::uint32_t>()));
    }

    for(auto entry : includes_)
    {
        printf("%s\n", entry.data());
    }
}

void disassembler::disassemble_animtrees()
{
    script_->pos(header_.animtree_offset);

    for(auto i = 0; i < header_.animtree_count; i++)
    {
        auto tree = std::make_shared<arc::asm_animtree>();
        tree->name = string_refs_.at(script_->read<std::uint16_t>());
        auto ref_count = script_->read<std::uint16_t>();
        auto anim_count = script_->read<std::uint16_t>();
        script_->seek(2);

        for(auto j = 0; j < ref_count; j++)
        {
            auto ref = script_->read<std::uint32_t>();
            tree->refs.push_back(ref);
            // anim_refs_.insert({ ref,  tree });
        }

        for(auto k = 0; k < anim_count; k++)
        {
            arc::asm_animation anim;
            anim.name = resolve_string(script_->read<std::uint32_t>());
            anim.ref = script_->read<std::uint32_t>();
            animtree_refs_.insert({ anim.ref,  tree->name });

            tree->anims.push_back(anim);
        }

        animtrees_.push_back(tree);
    }
}

void disassembler::disassemble_stringtable()
{
    script_->pos(header_.stringtablefixup_offset);

    for(auto i = 0; i < header_.stringtablefixup_count; i++)
    {
        arc::asm_string str;
        str.name = string_refs_.at(script_->read<std::uint16_t>());
        auto ref_count = script_->read<std::uint8_t>();
        script_->seek(1);

        for(auto j = 0; j < ref_count; j++)
        {
            str.refs.push_back(script_->read<std::uint32_t>());
        }

        stringtable_.push_back(str);
    }
/*
    std::cout << "\nSTRINGTABLE: \n";

    for(auto entry : stringtable_)
    {
        std::cout << "    " << entry.name << "\n";
        std::cout << "        refs:";
        
        for(auto ref : entry.refs)
        {
            std::cout << " " << utils::string::va("%X", ref);
        }

        std::cout << "\n";
    }
*/
}

void disassembler::disassemble_imports()
{
    script_->pos(header_.imports_offset);

    for(auto i = 0; i < header_.imports_count; i++)
    {
        auto entry = std::make_shared<arc::asm_import>();
        entry->name = string_refs_.at(script_->read<std::uint16_t>());
        auto num = script_->read<std::uint16_t>();
        entry->space = string_refs_.at(num);
        auto ref_count = script_->read<std::uint16_t>();
        entry->params = script_->read<std::uint8_t>();
        script_->seek(1);

        for(auto j = 0; j < ref_count; j++)
        {
            auto ref = script_->read<std::uint32_t>();
            entry->refs.push_back(ref);
            import_refs_.insert({ ref, entry });
        }

        imports_.push_back(entry);
    }
}

void disassembler::disassemble_exports()
{
    script_->pos(header_.exports_offset);

    for(auto i = 0; i < header_.exports_count; i++)
    {
        arc::asm_export entry;
        entry.checksum = script_->read<std::uint32_t>();
        entry.offset = script_->read<std::uint32_t>();
        entry.name = string_refs_.at(script_->read<std::uint16_t>());
        entry.space = "";
        entry.params = script_->read<std::uint8_t>();
        entry.flags = script_->read<std::uint8_t>();

        exports_.push_back(entry);
    }

    for(auto i = 0; i < exports_.size(); i++)
    {
        auto& entry = exports_[i];
        auto size = 0;

        if(i < exports_.size() - 1)
        {
            entry.size = (exports_[i+1].offset - entry.offset) - 4;

            auto end_pos = entry.offset + entry.size;

            for(auto j = 1; j < 4; j++)
            {
                script_->pos(end_pos - j);
                auto op = script_->read<std::uint8_t>();

                if(op == '\x00' || op == '\x01')
                    break;
                else
                    entry.size--;
            }
        }
        else
        {
            entry.size = (header_.cseg_offset + header_.cseg_size) - entry.offset;
        }

        script_->pos(entry.offset);

        data_->functions.push_back(std::make_unique<arc::asm_function>());
        auto& func = data_->functions.back();

        func->index = static_cast<std::uint32_t>(script_->pos());
        func->size = entry.size;
        func->params = entry.params;
        func->flags = entry.flags;
        func->name = entry.name;

        this->disassemble_function(func);

        func->labels = labels_;
        labels_.clear();
    }
}

void disassembler::disassemble_function(const arc::asm_function_ptr& func)
{
    auto size = func->size;

    while (size > 0)
    {
        func->instructions.push_back(std::make_unique<arc::asm_instruction>());
        auto& inst = func->instructions.back();
        inst->index = static_cast<std::uint32_t>(script_->pos());
        inst->opcode = script_->read<std::uint8_t>();
        inst->size = opcode_size(inst->opcode);

        this->disassemble_instruction(inst);
        size -= inst->size;
    }
}

void disassembler::disassemble_instruction(const arc::asm_instruction_ptr& inst)
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
    case opcode::OP_RemoveLocalVariables:
    case opcode::OP_EvalArray:
    case opcode::OP_EvalLocalArrayRefCached:
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
    {
        inst->size += script_->align(4);
        auto val = script_->read<float>();
        inst->data.push_back(utils::string::va("%g%s", val, val == int(val) ? ".0" : ""));
    }
        break;
    case opcode::OP_GetVector:
        inst->size += script_->align(4);
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        break;
    case opcode::OP_GetString:
    case opcode::OP_GetIString:
        inst->size += script_->align(2);
        inst->data.push_back(utils::string::to_literal(string_refs_.at(script_->read<std::uint16_t>())));
        break;
    case opcode::OP_GetAnimation:
        {
            inst->size += script_->align(4);
            auto ref = script_->pos();
            inst->data.push_back(utils::string::quote(string_refs_.at(script_->read<std::uint32_t>())));           
            inst->data.insert(inst->data.begin(), animtree_refs_.at(ref));
        }
        break;
    case opcode::OP_WaitTillMatch:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        break;
    case opcode::OP_VectorConstant:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        break;
    case opcode::OP_GetHash:
        inst->size += script_->align(4);
        inst->data.push_back(utils::string::va("%X", script_->read<std::uint32_t>()));
        break;
    case opcode::OP_SafeCreateLocalVariables:
        {
            auto count = script_->read<std::uint8_t>();

            for(auto i = 0; i < count; i++)
            {
                inst->size += script_->align(2) + 2;
                inst->data.push_back(string_refs_.at(script_->read<std::uint16_t>()));
            }
        }
        break;
    case opcode::OP_EvalLocalVariableCached:
    case opcode::OP_SafeSetWaittillVariableFieldCached:
    case opcode::OP_EvalLocalVariableRefCached:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        break;
    case opcode::OP_EvalFieldVariable:
    case opcode::OP_EvalFieldVariableRef:
    case opcode::OP_ClearFieldVariable:
        inst->size += script_->align(2);
        inst->data.push_back(string_refs_.at(script_->read<std::uint16_t>()));
        break;
    case opcode::OP_ScriptFunctionCallPointer:
    case opcode::OP_ScriptMethodCallPointer:
    case opcode::OP_ScriptThreadCallPointer:
    case opcode::OP_ScriptMethodThreadCallPointer:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        break;
    case opcode::OP_GetFunction:
        {
            inst->size += script_->align(4);
            inst->data.push_back(string_refs_.at(script_->read<std::uint32_t>()));

            const auto& import = import_refs_.at(inst->index);

            if(import->space != "")
            {
                inst->data.insert(inst->data.begin(), import->space);
            }
        }
        break;
    case opcode::OP_CallBuiltin:
    case opcode::OP_CallBuiltinMethod:
    case opcode::OP_ScriptFunctionCall:
    case opcode::OP_ScriptMethodCall:
    case opcode::OP_ScriptThreadCall:
    case opcode::OP_ScriptMethodThreadCall:
        {
            script_->seek(1);
            inst->size += script_->align(4);
            inst->data.push_back(string_refs_.at(script_->read<std::uint32_t>()));

            const auto& import = import_refs_.at(inst->index);

            if(import->space != "")
            {
                inst->data.insert(inst->data.begin(), import->space);
            }
        }
        break;
    case opcode::OP_JumpOnFalse:
    case opcode::OP_JumpOnTrue:
    case opcode::OP_JumpOnFalseExpr:
    case opcode::OP_JumpOnTrueExpr:
    case opcode::OP_Jump:
    case opcode::OP_JumpBack:
        {
            inst->size += script_->align(2);
            auto addr = inst->index + inst->size + script_->read<std::int16_t>();
            auto label = utils::string::va("loc_%X", addr);
            inst->data.push_back(label);
            labels_.insert({addr, label});
        }  
        break;
    case opcode::OP_Switch:
        {
            inst->size += script_->align(4);
            auto addr = inst->index + inst->size + script_->read<std::int32_t>();
            auto label = utils::string::va("loc_%X", addr);
            inst->data.push_back(label);
            labels_.insert({addr, label});
        } 
        break;
    case opcode::OP_EndSwitch:
    {
        inst->size += script_->align(4);
        auto count = script_->read<std::uint32_t>();

        for(auto i = 0; i < count; i++)
        {
            inst->size += 8;
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint32_t>()));
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint32_t>()));
        }
    }
        break;
    case opcode::OP_DevblockBegin:
    case opcode::OP_DevblockEnd:
        {
            inst->size += script_->align(2);
            auto addr = inst->index + inst->size + script_->read<std::int16_t>();
            auto label = utils::string::va("loc_%X", addr);
            inst->data.push_back(label);
            labels_.insert({addr, label});
        }   
        break;
    default:
        throw disasm_error(utils::string::va("Unhandled opcode 0x%X at index '%04X'!", inst->opcode, inst->index));
    }
}

auto disassembler::resolve_string(std::uint32_t ref) -> std::string
{
    try
    {
        return string_refs_.at(ref);
    }
    catch(const std::exception& e)
    {
        return "";
    }
}

void disassembler::print_function(const arc::asm_function_ptr& func)
{
    output_->write_string("\n");
    output_->write_string(utils::string::va("sub_%s %i %i\n", func->name.data(), func->params, func->flags));

    for (auto& inst : func->instructions)
    {
        const auto itr = func->labels.find(inst->index);

        if (itr != func->labels.end())
        {
            output_->write_string(utils::string::va("\t%s\n", itr->second.data()));
        }

        this->print_instruction(inst);
    }

    output_->write_string(utils::string::va("end_%s\n", func->name.data()));
}

void disassembler::print_instruction(const arc::asm_instruction_ptr& inst)
{
    switch (opcode(inst->opcode))
    {
    /*case opcode::OP_endswitch:
        output_->write_string(utils::string::va("\t\t%s", resolver::opcode_name(inst->opcode).data()));
        output_->write_string(utils::string::va(" %s\n", inst->data[0].data()));
        {
            std::uint32_t totalcase = std::stoul(inst->data[0]);
            auto index = 0;
            for (auto casenum = 0u; casenum < totalcase; casenum++)
            {
                if (inst->data[1 + index] == "case")
                {
                    output_->write_string(utils::string::va("\t\t\t%s %s %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data(), inst->data[1 + index + 2].data()));
                    index += 3;
                }
                else if (inst->data[1 + index] == "default")
                {
                    output_->write_string(utils::string::va("\t\t\t%s %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data()));
                    index += 2;
                }

                output_->write_string("\n");
            }
        }
        break;*/
    default:
        output_->write_string(utils::string::va("\t\t%s", resolver::opcode_name(inst->opcode).data()));

        for (auto& d : inst->data)
        {
            output_->write_string(utils::string::va(" %s", d.data()));
        }

        output_->write_string("\n");
        break;
    }
}

} // namespace xsk::gsc::t6
