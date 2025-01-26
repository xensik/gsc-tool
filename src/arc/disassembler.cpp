// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/arc/disassembler.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc
{

disassembler::disassembler(context const* ctx) : ctx_{ ctx }
{
}

auto disassembler::disassemble(buffer const& data) -> assembly::ptr
{
    return disassemble(data.data, data.size);
}

auto disassembler::disassemble(std::vector<u8> const& data) -> assembly::ptr
{
    return disassemble(data.data(), data.size());
}

auto disassembler::disassemble(u8 const* data, usize data_size) -> assembly::ptr
{
    script_ = utils::reader{ data, data_size, ctx_->endian() == endian::big };
    assembly_ = assembly::make();
    import_refs_.clear();
    string_refs_.clear();
    anim_refs_.clear();

    auto header_ = header{};
    header_.magic = script_.read<u64>();

    if (header_.magic != ctx_->magic())
        throw disasm_error("invalid script file or unsupported game version");

    header_.source_crc = script_.read<u32>();
    header_.include_offset = script_.read<u32>();
    header_.animtree_offset = script_.read<u32>();
    header_.cseg_offset = script_.read<u32>();
    header_.stringtablefixup_offset = script_.read<u32>();

    if (ctx_->props() & props::devstr)
        header_.devblock_stringtablefixup_offset = script_.read<u32>();

    header_.exports_offset = script_.read<u32>();
    header_.imports_offset = script_.read<u32>();
    header_.fixup_offset = script_.read<u32>();

    if (ctx_->props() & props::globals)
        header_.globalvar_offset = script_.read<u32>();

    header_.profile_offset = script_.read<u32>();
    header_.cseg_size = script_.read<u32>();

    if (ctx_->props() & props::size64)
        header_.name = script_.read<u32>();
    else
        header_.name = script_.read<u16>();

    header_.stringtablefixup_count = script_.read<u16>();
    header_.exports_count = script_.read<u16>();
    header_.imports_count = script_.read<u16>();
    header_.fixup_count = script_.read<u16>();

    if (ctx_->props() & props::globals)
        header_.globalvar_count = script_.read<u16>();

    header_.profile_count = script_.read<u16>();

    if (ctx_->props() & props::devstr)
        header_.devblock_stringtablefixup_count = script_.read<u16>();

    header_.include_count = script_.read<u8>();
    header_.animtree_count = script_.read<u8>();
    header_.flags = script_.read<u8>();

    auto string_pool = std::map<usize, std::string>{};

    // fix old compiler bug
    if (ctx_->fixup())
    {
        string_pool.insert({ 0x3E, "" });
    }

    script_.pos((ctx_->props() & props::headerxx) ? header_size_v3 : (ctx_->props() & props::header72) ? header_size_v2 : header_size_v1);

    while (script_.pos() < header_.include_offset)
    {
        auto pos = script_.pos();
        string_pool.insert({ pos, script_.read_cstr() });
    }

    script_.pos(header_.include_offset);

    for (auto i = 0u; i < header_.include_count; i++)
    {
        assembly_->includes.push_back(string_pool.at(script_.read<u32>()));
    }

    script_.pos(header_.animtree_offset);

    for (auto i = 0u; i < header_.animtree_count; i++)
    {
        auto entry = std::make_shared<animtree_ref>();
        auto ref_count = 0u;
        auto anim_count = 0u;

        if (ctx_->props() & props::size64)
        {
            entry->name = string_pool.at(script_.read<u32>());
            ref_count = script_.read<u16>();
            anim_count = script_.read<u16>();
        }
        else
        {
            entry->name = string_pool.at(script_.read<u16>());
            ref_count = script_.read<u16>();
            anim_count = script_.read<u16>();
            script_.seek(2);
        }

        for (auto j = 0u; j < ref_count; j++)
        {
            auto ref = script_.read<u32>();
            entry->refs.push_back(ref);
            anim_refs_.insert({ ref, entry });
        }

        for (auto j = 0u; j < anim_count; j++)
        {
            if (ctx_->props() & props::size64)
            {
                auto name = string_pool.at(static_cast<u32>(script_.read<u64>()));
                auto ref = static_cast<u32>(script_.read<u64>());
                entry->anims.push_back({ name, ref });
                anim_refs_.insert({ ref, entry });
            }
            else
            {
                auto name = string_pool.at(script_.read<u32>());
                auto ref = script_.read<u32>();
                entry->anims.push_back({ name, ref });
                anim_refs_.insert({ ref, entry });
            }
        }
    }

    script_.pos(header_.stringtablefixup_offset);

    for (auto i = 0u; i < header_.stringtablefixup_count; i++)
    {
        auto entry = std::make_shared<string_ref>();
        entry->name = string_pool.at((ctx_->props() & props::size64) ? script_.read<u32>() : script_.read<u16>());
        auto count = script_.read<u8>();
        entry->type = script_.read<u8>();

        if (ctx_->props() & props::size64)
            script_.seek(2);

        for (auto j = 0u; j < count; j++)
        {
            auto ref = script_.read<u32>();
            string_refs_.insert({ ref, entry });
        }
    }

    if (ctx_->props() & props::devstr)
    {
        script_.pos(header_.devblock_stringtablefixup_offset);

        for (auto i = 0u; i < header_.devblock_stringtablefixup_count; i++)
        {
            auto entry = std::make_shared<string_ref>();
            entry->name = "__devstr__";
            script_.seek(4);
            auto count = script_.read<u8>();
            entry->type = script_.read<u8>();
            script_.seek(2);

            for (auto j = 0; j < count; j++)
            {
                auto ref = script_.read<u32>();
                string_refs_.insert({ ref, entry });
            }
        }
    }

    if (ctx_->props() & props::globals)
    {
        script_.pos(header_.globalvar_offset);

        for (auto i = 0u; i < header_.globalvar_count; i++)
        {
            auto name = ctx_->hash_name(script_.read<u32>());
            auto refs = script_.read<u32>();

            for (auto j = 0u; j < refs; j++)
            {
                // todo t8 vars
            }
        }
    }

    script_.pos(header_.imports_offset);

    for (auto i = 0u; i < header_.imports_count; i++)
    {
        auto entry = std::make_shared<import_ref>();

        if (ctx_->props() & props::hashids)
        {
            entry->name = ctx_->hash_name(script_.read<u32>());
            entry->space = ctx_->hash_name(script_.read<u32>());
        }
        else
        {
            entry->name = string_pool.at(script_.read<u16>());
            entry->space = string_pool.at(script_.read<u16>());
        }

        auto count = script_.read<u16>();
        entry->params = script_.read<u8>();
        entry->flags = script_.read<u8>();

        for (auto j = 0; j < count; j++)
        {
            import_refs_.insert({ script_.read<u32>(), entry });
        }
    }

    auto exports_ = std::vector<export_ref::ptr>{};
    script_.pos(header_.exports_offset);

    for (auto i = 0u; i < header_.exports_count; i++)
    {
        auto entry = std::make_shared<export_ref>();
        entry->checksum = script_.read<u32>();
        entry->offset = script_.read<u32>();

        if (ctx_->props() & props::hashids)
        {
            entry->name = ctx_->hash_name(script_.read<u32>());
            entry->space = ctx_->hash_name(script_.read<u32>());
        }
        else
        {
            entry->name = string_pool.at(script_.read<u16>());
            entry->space = "";
        }

        entry->params = script_.read<u8>();
        entry->flags = script_.read<u8>();

        if (ctx_->props() & props::hashids)
            script_.seek(2);

        exports_.push_back(entry);
    }

    for (auto i = 0u; i < exports_.size(); i++)
    {
        auto& entry = exports_[i];

        if (i < exports_.size() - 1)
        {
            entry->size = (exports_[i + 1]->offset - entry->offset);

            auto pad_size = (ctx_->props() & props::size64) ? 8 : 4;
            auto end_pos = entry->offset + entry->size - pad_size;

            script_.pos(end_pos);

            if ((ctx_->props() & props::size64) && script_.read<u64>() == 0)
            {
                 entry->size -= pad_size;

                script_.pos(end_pos - 2);
                script_.align(2);
                for (auto j = 0; j < 4; j++)
                {
                    auto op = ctx_->opcode_enum(script_.read<u16>());
                    if (op == opcode::OP_End || op == opcode::OP_Return) break;
                    script_.seek_neg(4);
                }

                entry->size -= static_cast<u32>(end_pos - script_.pos());
            }
            else if (script_.read<u32>() == 0)
            {
                entry->size -= pad_size;

                for (auto j = 1; j < 4; j++)
                {
                    script_.pos(end_pos - j);
                    if (script_.read<u8>() <= 0x01) break;
                    entry->size--;
                }
            }
        }
        else if (ctx_->fixup() && header_.cseg_size == 0) // fix old compiler bug
        {
            entry->size = (header_.imports_offset) - entry->offset;
        }
        else
        {
            entry->size = (header_.cseg_offset + header_.cseg_size) - entry->offset;
        }

        script_.pos(entry->offset);

        func_ = function::make();
        func_->index = entry->offset;
        func_->size = entry->size;
        func_->params = entry->params;
        func_->flags = entry->flags;
        func_->name = entry->name;
        func_->space = entry->space;

        disassemble_function(*func_);

        assembly_->functions.push_back(std::move(func_));
    }

    return std::move(assembly_);
}

auto disassembler::disassemble_function(function& func) -> void
{
    auto size = func.size;

    while (size > 0)
    {
        auto inst = instruction::make();
        inst->index = script_.pos();

        if (ctx_->props() & props::size64)
        {
            auto index = script_.read<u16>();

            if (size < 8 && (index >= 0x4000 || ctx_->opcode_enum(index) == opcode::OP_Invalid))
                break;

            if ((index & 0x4000) == 0)
                inst->opcode = ctx_->opcode_enum(index);
            else
                throw disasm_error(std::format("invalid opcode index 0x{:X} at pos '{:04X}'!", index, inst->index));
        }
        else
        {
            auto index = script_.read<u8>();

            if (size < 4 && ctx_->opcode_enum(index) == opcode::OP_Invalid)
                break;

            inst->opcode = ctx_->opcode_enum(index);
        }

        inst->size = ctx_->opcode_size(inst->opcode);

        disassemble_instruction(*inst);

        if (ctx_->props() & props::size64)
            inst->size += script_.align(2);

        if (inst->size > size || inst->index + inst->size != script_.pos())
            throw disasm_error("bad instruction size");

        size -= inst->size;

        func.instructions.push_back(std::move(inst));
    }

    // remove padding garbage ops
    auto last_idx = 0;
    for (auto i = 1; i <= 4; i++)
    {
        if (func.instructions.size() - i <= 0)
            break;

        auto const& inst = func.instructions.at(func.instructions.size() - i);

        if (inst->opcode == opcode::OP_End ||  inst->opcode == opcode::OP_Return)
            last_idx = i;

        if (func.labels.contains(inst->index))
            break;
    }

    while (last_idx-- > 1) func.instructions.pop_back();
}

auto disassembler::disassemble_instruction(instruction& inst) -> void
{
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
        //case opcode::OP_ProfileStart:
        case opcode::OP_ProfileStop:
        case opcode::OP_SafeDecTop:
        case opcode::OP_Nop:
        case opcode::OP_Abort:
        case opcode::OP_Object:
        case opcode::OP_ThreadObject:
        case opcode::OP_EvalLocalVariable:
        case opcode::OP_EvalLocalVariableRef:
        case opcode::OP_GetClassesObject:
        case opcode::OP_GetClasses:
        case opcode::OP_GetWorldObject:
        case opcode::OP_GetWorld:
        case opcode::OP_SuperEqual:
        case opcode::OP_SuperNotEqual:
            break;
        case opcode::OP_GetByte:
        case opcode::OP_GetNegByte:
            inst.data.push_back(std::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            inst.size += script_.align(2);
            inst.data.push_back(std::format("{}", script_.read<u16>()));
            break;
        case opcode::OP_GetInteger:
            inst.size += script_.align(4);
            disassemble_animtree(inst);
            inst.data.push_back(std::format("{}", script_.read<i32>()));
            break;
        case opcode::OP_GetFloat:
            inst.size += script_.align(4);
            inst.data.push_back(utils::string::float_string(script_.read<f32>()));
            break;
        case opcode::OP_GetUintptr:
        //case opcode::OP_ProfileStart:
        case opcode::OP_GetAPIFunction:
            inst.size += script_.align(8);
            inst.data.push_back(std::format("0x{:016X}", script_.read<u64>()));
            break;
        case opcode::OP_GetVector:
            inst.size += script_.align(4);
            inst.data.push_back(utils::string::float_string(script_.read<f32>()));
            inst.data.push_back(utils::string::float_string(script_.read<f32>()));
            inst.data.push_back(utils::string::float_string(script_.read<f32>()));
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            disassemble_string(inst);
            break;
        case opcode::OP_GetAnimation:
            disassemble_animation(inst);
            break;
        case opcode::OP_WaitTillMatch:
            inst.data.push_back(std::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_VectorConstant:
            inst.data.push_back(std::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_GetHash:
            inst.size += script_.align(4);
            inst.data.push_back(ctx_->hash_name(script_.read<u32>()));
            break;
        case opcode::OP_ScriptFunctionCallClass:
        case opcode::OP_ScriptThreadCallClass:
            script_.seek(1);
            inst.size += script_.align(4);
            inst.data.push_back(ctx_->hash_name(script_.read<u32>()));
            break;
        case opcode::OP_SafeCreateLocalVariables:
            disassemble_params(inst);
            break;
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_EvalLocalArrayRefCached:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_EvalLocalVariableRefCached:
            inst.data.push_back(std::format("{}", script_.read<u8>()));
            break;
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_ClearFieldVariable:
        case opcode::OP_EvalLocalVariableCachedDebug:
        case opcode::OP_EvalLocalVariableRefCachedDebug:
        case opcode::OP_LevelEvalFieldVariableRef:
        case opcode::OP_LevelEvalFieldVariable:
        case opcode::OP_SelfEvalFieldVariableRef:
        case opcode::OP_SelfEvalFieldVariable:
        case opcode::OP_New:
            disassemble_name(inst);
            break;
        case opcode::OP_ScriptFunctionCallPointer:
        case opcode::OP_ScriptMethodCallPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
            inst.data.push_back(std::format("{}", script_.read<u8>()));
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
            script_.seek(1);
            disassemble_import(inst);
            break;
        case opcode::OP_JumpOnFalse:
        case opcode::OP_JumpOnTrue:
        case opcode::OP_JumpOnFalseExpr:
        case opcode::OP_JumpOnTrueExpr:
        case opcode::OP_Jump:
        case opcode::OP_JumpBack:
        case opcode::OP_DevblockBegin:
            disassemble_jump(inst);
            break;
        case opcode::OP_Switch:
            disassemble_switch(inst);
            break;
        case opcode::OP_EndSwitch:
            disassemble_end_switch(inst);
            break;
        default:
            throw disasm_error(std::format("unhandled opcode {} at index {:04X}", ctx_->opcode_name(inst.opcode), inst.index));
    }
}

auto disassembler::disassemble_name(instruction& inst) -> void
{
    inst.size += script_.align((ctx_->props() & props::hashids) ? 4 : 2);

    if (ctx_->props() & props::hashids)
    {
        return inst.data.push_back(ctx_->hash_name(script_.read<u32>()));
    }

    if (auto const itr = string_refs_.find(script_.pos()); itr != string_refs_.end())
    {
        inst.data.push_back(itr->second->name);
        return script_.seek(2);
    }

    throw disasm_error(std::format("string reference not found at index {:04X}", inst.index));
}

auto disassembler::disassemble_params(instruction& inst) -> void
{
    auto count = script_.read<u8>();

    for (auto i = 0u; i < count; i++)
    {
        if (ctx_->props() & props::hashids)
        {
            inst.size += script_.align(4) + 5;
            inst.data.push_back(ctx_->hash_name(script_.read<u32>()));
            inst.data.push_back(std::format("{}", script_.read<u8>()));
        }
        else
        {
            inst.size += 2;
            disassemble_string(inst);
        }
    }
}

auto disassembler::disassemble_import(instruction& inst) -> void
{
    inst.size += script_.align((ctx_->props() & props::size64) ? 8 : 4);

    if (auto const itr = import_refs_.find(inst.index); itr != import_refs_.end())
    {
        inst.data.push_back(itr->second->space);
        inst.data.push_back(itr->second->name);
        return script_.seek((ctx_->props() & props::size64) ? 8 : 4);
    }

    throw disasm_error(std::format("import reference not found at index {:04X}", inst.index));
}

auto disassembler::disassemble_string(instruction& inst) -> void
{
    inst.size += script_.align((ctx_->props() & props::size64) ? 4 : 2);

    if (auto const itr = string_refs_.find(script_.pos()); itr != string_refs_.end())
    {
        inst.data.push_back(itr->second->name);
        return script_.seek((ctx_->props() & props::size64) ? 4 : 2);
    }

    throw disasm_error(std::format("string reference not found at index {:04X}", inst.index));
}

auto disassembler::disassemble_animtree(instruction& inst) -> void
{
    if (auto const itr = anim_refs_.find(script_.pos()); itr != anim_refs_.end())
    {
        inst.data.push_back(itr->second->name);
    }
}

auto disassembler::disassemble_animation(instruction& inst) -> void
{
    inst.size += script_.align((ctx_->props() & props::size64) ? 8 : 4);

    auto ref = script_.pos();

    if (auto const itr = anim_refs_.find(ref); itr != anim_refs_.end())
    {
        inst.data.push_back(itr->second->name);

        for (auto const& anim : itr->second->anims)
        {
            if (anim.ref != ref)
                continue;

            inst.data.push_back(anim.name);
            return script_.seek((ctx_->props() & props::size64) ? 8 : 4);
        }
    }

    throw disasm_error(std::format("animation reference not found at index {:04X}", inst.index));
}

auto disassembler::disassemble_jump(instruction& inst) -> void
{
    inst.size += script_.align(2);

    auto addr = ((ctx_->props() & props::size64) ? ((script_.read<i16>() + 1) & ~1) : script_.read<i16>()) + script_.pos();
    auto label = std::format("loc_{:X}", addr);

    inst.data.emplace_back(label);
    func_->labels.insert({ addr, label });
}

auto disassembler::disassemble_switch(instruction& inst) -> void
{
    inst.size += script_.align(4);

    auto addr = script_.read<i32>() + script_.pos();
    auto label = std::format("loc_{:X}", addr);

    inst.data.emplace_back(label);
    func_->labels.insert({ addr, label });
}

auto disassembler::disassemble_end_switch(instruction& inst) -> void
{
    inst.size += script_.align(4);

    if (auto const itr = func_->labels.find(script_.pos()); itr != func_->labels.end())
    {
        for (auto const& entry : func_->instructions)
        {
            if (entry->opcode != opcode::OP_Switch || entry->data[0] != itr->second)
                continue;

            entry->data[0] = std::format("loc_{:X}", inst.index);

            if (func_->labels.erase(script_.pos()); !func_->labels.contains(inst.index))
            {
                func_->labels.try_emplace(inst.index, std::string{ entry->data[0] });
            }

            break;
        }
    }

    auto count = script_.read<u32>();
    inst.data.push_back(std::format("{}", count));

    for (auto i = 0u; i < count; i++)
    {
        auto value = script_.read<u32>();

        if (ctx_->props() & props::size64)
        {
            if (auto const str = string_refs_.find(script_.pos() - 4); str != string_refs_.end())
            {
                inst.data.push_back("case");
                inst.data.push_back(std::format("{}", static_cast<i32>(switch_type::string)));
                inst.data.push_back(str->second->name);
            }
            else if (value != 0 || i != count - 1)
            {
                inst.data.push_back("case");
                inst.data.push_back(std::format("{}", static_cast<i32>(switch_type::integer)));
                inst.data.push_back(std::format("{}", value));
            }
            else
            {
                inst.data.push_back("default");
            }
        }
        else
        {
            if (value == 0)
            {
                inst.data.push_back("default");
            }
            else if (value < 0x40000)
            {
                inst.data.push_back("case");
                inst.data.push_back(std::format("{}", static_cast<i32>(switch_type::string)));
                inst.data.push_back(string_refs_.at(script_.pos() - 2)->name);
            }
            else
            {
                inst.data.push_back("case");
                inst.data.push_back(std::format("{}", static_cast<i32>(switch_type::integer)));
                inst.data.push_back(std::format("{}", (value - 0x800000) & 0xFFFFFF));
            }
        }

        auto addr = script_.read<i32>() + script_.pos();
        auto label = std::format("loc_{:X}", addr);

        inst.size += 8;
        inst.data.emplace_back(label);
        func_->labels.insert({ addr, label });
    }
}

} // namespace xsk::arc
