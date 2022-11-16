// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "iw9.hpp"

namespace xsk::gsc::iw9
{

auto disassembler::output() -> std::vector<function::ptr>
{
    return std::move(functions_);
}

auto disassembler::output_data() -> std::vector<std::uint8_t>
{
    output_ = std::make_unique<utils::byte_buffer>(0x100000);

    output_->write_string("// IW9 GSC ASSEMBLY\n");
    output_->write_string("// Disassembled by https://github.com/xensik/gsc-tool\n");

    for (const auto& func : functions_)
    {
        print_function(func);
    }

    std::vector<std::uint8_t> output;

    output.resize(output_->pos());
    std::memcpy(output.data(), output_->buffer().data(), output.size());

    return output;
}

void disassembler::disassemble(const std::string& file, std::vector<std::uint8_t>& script, std::vector<std::uint8_t>& stack)
{
    filename_ = file;
    script_ = std::make_unique<utils::byte_buffer>(script);
    stack_ = std::make_unique<utils::byte_buffer>(stack);
    functions_.clear();

    script_->seek(1);

    while (stack_->is_avail() && script_->is_avail())
    {
        functions_.push_back(std::make_unique<function>());
        const auto& func = functions_.back();

        func->index = static_cast<std::uint32_t>(script_->pos());
        func->size = stack_->read<std::uint32_t>();
        func->name = utils::string::va("id_%016llX", stack_->read<std::uint64_t>());

        dissasemble_function(func);

        func->labels = labels_;
        labels_.clear();
    }

    resolve_local_functions();
}

void disassembler::dissasemble_function(const function::ptr& func)
{
    auto size = static_cast<int32_t>(func->size);

    while (size > 0)
    {
        func->instructions.push_back(std::make_unique<instruction>());

        const auto& inst = func->instructions.back();
        inst->index = static_cast<std::uint32_t>(script_->pos());
        inst->opcode = script_->read<std::uint8_t>();
        inst->size = opcode_size(inst->opcode);

        dissasemble_instruction(inst);

        size -= inst->size;

        if (inst->index + inst->size != script_->pos())
        {
            throw error("wrong inst size");
        }
    
        if (size < 0)
        {
            throw error("wrong func size");
        }
    }
}

void disassembler::dissasemble_instruction(const instruction::ptr& inst)
{
    switch (static_cast<opcode>(inst->opcode))
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
        case opcode::OP_unk_139:
        case opcode::OP_BoolNotAfterAnd:
        case opcode::OP_IsDefined:
        case opcode::OP_IsTrue:
            break;
        case opcode::OP_GetByte:
        case opcode::OP_GetNegByte:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            break;
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetNegUnsignedShort:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint16_t>()));
            break;
        case opcode::OP_GetInteger:
            inst->data.push_back(utils::string::va("%i", script_->read<std::int32_t>()));
            break;
        case opcode::OP_GetFloat:
            inst->data.push_back(utils::string::float_string(script_->read<float>()));
            break;
        case opcode::OP_GetVector:
            inst->data.push_back(utils::string::float_string(script_->read<float>()));
            inst->data.push_back(utils::string::float_string(script_->read<float>()));
            inst->data.push_back(utils::string::float_string(script_->read<float>()));
            break;
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
            script_->seek(4);
            inst->data.push_back(utils::string::quote(stack_->read_c_string(), false));
            break;
        case opcode::OP_GetAnimTree:
            script_->seek(1);
            inst->data.push_back(utils::string::quote(stack_->read_c_string(), false));
            break;
        case opcode::OP_GetAnimation:
            script_->seek(8);
            inst->data.push_back(utils::string::quote(stack_->read_c_string(), false));
            inst->data.push_back(utils::string::quote(stack_->read_c_string(), false));
            break;
        case opcode::OP_waittillmatch:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            break;
        case opcode::OP_EvalSelfFieldVariableRef:
        case opcode::OP_EvalAnimFieldVariable:
        case opcode::OP_EvalLevelFieldVariableRef:
        case opcode::OP_SetSelfFieldVariableField:
        case opcode::OP_ClearFieldVariable:
        case opcode::OP_EvalFieldVariable:
        case opcode::OP_SetLevelFieldVariableField:
        case opcode::OP_EvalSelfFieldVariable:
        case opcode::OP_SetAnimFieldVariableField:
        case opcode::OP_EvalFieldVariableRef:
        case opcode::OP_EvalLevelFieldVariable:
        case opcode::OP_EvalAnimFieldVariableRef:
            inst->data.push_back(utils::string::va("id_%016llX", script_->read<std::uint64_t>()));
            break;
        case opcode::OP_CreateLocalVariable:
        case opcode::OP_EvalNewLocalArrayRefCached0:
        case opcode::OP_SafeCreateVariableFieldCached:
        case opcode::OP_SetNewLocalVariableFieldCached0:
            inst->data.push_back(utils::string::va("%016llX", script_->read<std::uint64_t>()));
            break;
        case opcode::OP_SetLocalVariableFieldCached:
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        case opcode::OP_EvalLocalVariableCached:
        case opcode::OP_EvalLocalVariableObjectCached:
        case opcode::OP_EvalLocalArrayCached:
        case opcode::OP_SafeSetVariableFieldCached:
        case opcode::OP_EvalLocalVariableRefCached:
        case opcode::OP_ClearLocalVariableFieldCached:
        case opcode::OP_EvalLocalArrayRefCached:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            break;
        case opcode::OP_ScriptMethodChildThreadCallPointer:
        case opcode::OP_CallBuiltinMethodPointer:
        case opcode::OP_ScriptChildThreadCallPointer:
        case opcode::OP_ScriptMethodThreadCallPointer:
        case opcode::OP_ScriptThreadCallPointer:
        case opcode::OP_CallBuiltinPointer:
            inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
            break;
        case opcode::OP_GetFarFunction:
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
            disassemble_builtin_call(inst, false, false);
            break;
        case opcode::OP_GetBuiltinMethod:
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
/*      case opcode::OP_prof_begin:
            script_->seek(5); // TODO: skipped data
            break;
        case opcode::OP_prof_end:
            script_->seek(1); // TODO: skipped data
            break;
        case opcode::OP_EvalNewLocalArrayRefCached0_Precompiled:
        case opcode::OP_SetNewLocalVariableFieldCached0_Precompiled:
        case opcode::OP_CreateLocalVariable_Precompiled:
        case opcode::OP_SafeCreateVariableFieldCached_Precompiled:
            script_->seek(8); // TODO: skipped data
            break;*/
        case opcode::OP_NativeGetFarFunction:
        case opcode::OP_NativeFarFunctionCall:
        case opcode::OP_NativeFarMethodCall:
            disassemble_native_call(inst, false);
            break;
        case opcode::OP_NativeFarFunctionThreadCall:
        case opcode::OP_NativeFarMethodThreadCall:
        case opcode::OP_NativeFarFunctionChildThreadCall:
        case opcode::OP_NativeFarMethodChildThreadCall:
            disassemble_native_call(inst, true);
            break;
        case opcode::OP_FormalParams:
        case opcode::OP_FormalParams_Precompiled:
            disassemble_formal_params(inst);
            break;
        default:
            throw disasm_error(utils::string::va("unhandled opcode 0x%X at index '%04X'!", inst->opcode, inst->index));
    }
}

void disassembler::disassemble_builtin_call(const instruction::ptr& inst, bool method, bool args)
{
    if (args)
    {
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
    }

    if (method) // TODO
    {
        auto str = stack_->read_c_string();
        script_->seek(2);
        inst->data.emplace(inst->data.begin(), str);
    }
    else
    {
        auto str = stack_->read_c_string();
        script_->seek(2);
        inst->data.emplace(inst->data.begin(), str);
    }
}

void disassembler::disassemble_native_call(const instruction::ptr& inst, bool thread)
{
    script_->seek(4);

    if (thread)
    {
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
    }

    inst->data.emplace(inst->data.begin(), utils::string::va("%08X", stack_->read<std::uint32_t>()));
}

void disassembler::disassemble_far_call(const instruction::ptr& inst, bool thread)
{
    auto offs = script_->read<std::uint32_t>();

    if (thread)
    {
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
    }

    auto file = stack_->read<std::uint64_t>();
    auto name = stack_->read<std::uint64_t>();

    if (file == 0)
    {

        inst->data.emplace(inst->data.begin(), "");
        inst->data.push_back(utils::string::va("%X", offs + inst->index + 1));
    }
    else
    {
        inst->data.emplace(inst->data.begin(), utils::string::va("id_%016llX", file));
        inst->data.emplace(inst->data.begin(), utils::string::va("id_%016llX", name));
    }
}

void disassembler::disassemble_switch(const instruction::ptr& inst)
{
    const auto addr = inst->index + 4 + script_->read<std::int32_t>();
    const auto label = utils::string::va("loc_%X", addr);

    inst->data.push_back(label);
    labels_.insert({ addr, label });
}

void disassembler::disassemble_end_switch(const instruction::ptr& inst)
{
    const auto count = script_->read<std::uint16_t>();
    inst->data.push_back(utils::string::va("%i", count));

    std::uint32_t index = inst->index + 3;

    if (count)
    {
        for (auto i = count; i > 0; i--)
        {
            const auto value = script_->read<std::uint32_t>();
            const auto offs = script_->read<std::int16_t>();
            script_->seek(1);
            const auto byte = script_->read<std::uint8_t>();
            
            if (byte == 2)
            {
                auto str = stack_->read_c_string();

                if (str[0] == 1)
                {
                    inst->data.push_back("default");
                }
                else
                {
                    inst->data.push_back("case");
                    inst->data.push_back(utils::string::quote(str, false));
                }
            }
            else
            {
                inst->data.push_back("case");
                inst->data.push_back(utils::string::va("%i", value));
            }

            const auto addr = index + 4 + offs;
            const auto label = utils::string::va("loc_%X", addr);

            inst->data.push_back(label);
            labels_.insert({ addr, label });

            index += 8;
            inst->size += 8;
        }
    }
}

void disassembler::disassemble_field_variable(const instruction::ptr& inst)
{
    inst->data.push_back(utils::string::va("id_%016llX", script_->read<std::uint64_t>()));
}

void disassembler::disassemble_formal_params(const instruction::ptr& inst)
{
    const auto count = script_->read<std::uint8_t>();

    inst->size += count * 8;
    inst->data.push_back(utils::string::va("%i", count));

    for (auto i = 0u; i < count; i++)
    {
        inst->data.push_back(utils::string::va("%016llX", script_->read<std::uint64_t>()));
    }
}

void disassembler::disassemble_jump(const instruction::ptr& inst, bool expr, bool back)
{
    std::int32_t addr;

    if (expr)
    {
        addr = inst->index + 3 + script_->read<std::uint16_t>();
    }
    else if (back)
    {
        addr = inst->index + 3 - script_->read<std::uint16_t>();
    }
    else
    {
        addr = inst->index + 5 + script_->read<std::int32_t>();
    }

    const auto label = utils::string::va("loc_%X", addr);

    inst->data.push_back(label);
    labels_.insert({ addr, label });
}

void disassembler::resolve_local_functions()
{
    for (const auto& func : functions_)
    {
        for (const auto& inst : func->instructions)
        {
            switch (static_cast<opcode>(inst->opcode))
            {
                case opcode::OP_GetFarFunction:
                case opcode::OP_ScriptFarFunctionCall:
                case opcode::OP_ScriptFarMethodCall:
                case opcode::OP_ScriptFarThreadCall:
                case opcode::OP_ScriptFarChildThreadCall:
                case opcode::OP_ScriptFarMethodThreadCall:
                case opcode::OP_ScriptFarMethodChildThreadCall:
                    if (inst->data[0].empty())
                        inst->data[1] = resolve_function(inst->data[1]);
                    break;
                default:
                    break;
            }
        }
    }
}

auto disassembler::resolve_function(const std::string& index) -> std::string
{
    if (utils::string::is_hex_number(index))
    {
        std::uint32_t idx = std::stoul(index, nullptr, 16);

        for (const auto& func : functions_)
        {
            if (func->index == idx)
            {
                return func->name;
            }
        }

        throw disasm_error(utils::string::va("couldn't resolve function name at index '0x%04X'!", idx));
    }

    throw disasm_error(utils::string::va("\"%s\" is not valid function address!", index.data()));
}

void disassembler::print_function(const function::ptr& func)
{
    output_->write_string("\n");
    output_->write_string(utils::string::va("sub_%s %i\n", func->name.data(), func->size));

    for (const auto& inst : func->instructions)
    {
        const auto itr = func->labels.find(inst->index);

        if (itr != func->labels.end())
        {
            output_->write_string(utils::string::va("\t%s\n", itr->second.data()));
        }

        print_instruction(inst);
    }

    output_->write_string(utils::string::va("end_%s\n", func->name.data()));
}

void disassembler::print_instruction(const instruction::ptr& inst)
{
    output_->write_string(utils::string::va("%i\t%i\t%s", inst->index, inst->size, resolver::opcode_name(inst->opcode).data()));

    /*switch (static_cast<opcode>(inst->opcode))
    {
        case opcode::OP_GetLocalFunction:
        case opcode::OP_ScriptLocalFunctionCall:
        case opcode::OP_ScriptLocalFunctionCall2:
        case opcode::OP_ScriptLocalMethodCall:
            output_->write_string(utils::string::va(" sub_%s", inst->data[0].data()));
            break;
        case opcode::OP_ScriptLocalThreadCall:
        case opcode::OP_ScriptLocalChildThreadCall:
        case opcode::OP_ScriptLocalMethodThreadCall:
        case opcode::OP_ScriptLocalMethodChildThreadCall:
            output_->write_string(utils::string::va(" sub_%s %s\n", inst->data[0].data(), inst->data[1].data()));
            break;
        case opcode::OP_endswitch:
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
                    if (casenum != totalcase - 1)
                    {
                        output_->write_string("\n");
                    }
                }
            }
            break;
        default:*/
            for (auto& data : inst->data)
            {
                output_->write_string(utils::string::va(" %s", data.data()));
            }
    //        break;
    //}

    output_->write_string("\n");
}

} // namespace xsk::gsc::iw9
