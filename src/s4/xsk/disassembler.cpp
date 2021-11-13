// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "s4.hpp"

namespace xsk::gsc::s4
{

auto disassembler::output() -> std::vector<gsc::function_ptr>
{
    return std::move(functions_);
}

auto disassembler::output_data() -> std::vector<std::uint8_t>
{
    output_ = std::make_unique<utils::byte_buffer>(0x100000);

    output_->write_string("// S4 PC GSCASM\n");
    output_->write_string("// Disassembled by https://github.com/xensik/gsc-tool\n");

    for (auto& func : functions_)
    {
        this->print_function(func);
    }

    std::vector<std::uint8_t> output;

    output.resize(output_->pos());
    memcpy(output.data(), output_->buffer().data(), output.size());

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
        functions_.push_back(std::make_unique<gsc::function>());
        auto& func = functions_.back();

        func->index = static_cast<std::uint32_t>(script_->pos());
        func->size = stack_->read<std::uint32_t>();
        func->id = stack_->read<std::uint32_t>();
        func->name = "sub_"s + (func->id == 0 ? stack_->read_c_string() : resolver::token_name(func->id));

        this->dissasemble_function(func);

        func->labels = labels_;
        labels_.clear();
    }

    this->resolve_local_functions();
}

void disassembler::dissasemble_function(const gsc::function_ptr& func)
{
    auto size = func->size;

    while (size > 0)
    {
        func->instructions.push_back(std::make_unique<gsc::instruction>());
        
        auto& inst = func->instructions.back();
        inst->index = static_cast<std::uint32_t>(script_->pos());
        inst->opcode = script_->read<std::uint8_t>();
        inst->size = opcode_size(inst->opcode);
        
        this->dissasemble_instruction(inst);
        
        size -= inst->size;
    }
}

void disassembler::dissasemble_instruction(const gsc::instruction_ptr& inst)
{
    switch (opcode(inst->opcode))
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
//  case opcode::OP_NOP:
//  case opcode::OP_abort:
//  case opcode::OP_object:
//  case opcode::OP_thread_object:
    case opcode::OP_EvalLocalVariable:
    case opcode::OP_EvalLocalVariableRef:
//  case opcode::OP_breakpoint:
//  case opcode::OP_assignmentBreakpoint:
//  case opcode::OP_manualAndAssignmentBreakpoint:
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
    {
        auto val = script_->read<float>();
        inst->data.push_back(utils::string::va("%g%s", val, val == int(val) ? ".0" : ""));
    }
        break;
    case opcode::OP_GetVector:
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        break;
    case opcode::OP_GetString:
    case opcode::OP_GetIString:
        script_->seek(4);
        inst->data.push_back(utils::string::to_literal(stack_->read_c_string()));
        break;
    case opcode::OP_GetAnimation:
        script_->seek(8);
        inst->data.push_back(utils::string::quote(stack_->read_c_string().data(), false));
        inst->data.push_back(utils::string::quote(stack_->read_c_string().data(), false));
        break;
    case opcode::OP_GetAnimTree:
        script_->seek(1);
        inst->data.push_back(utils::string::quote(stack_->read_c_string().data(), false));
        break;
    case opcode::OP_waittillmatch:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        script_->seek(1);
        break;
    case opcode::OP_SetNewLocalVariableFieldCached0:
    case opcode::OP_EvalNewLocalArrayRefCached0:
    case opcode::OP_SafeCreateVariableFieldCached:
    case opcode::OP_ClearLocalVariableFieldCached:
    case opcode::OP_SetLocalVariableFieldCached:
    case opcode::OP_RemoveLocalVariables:
    case opcode::OP_EvalLocalVariableRefCached:
    case opcode::OP_EvalLocalArrayRefCached:
    case opcode::OP_SafeSetVariableFieldCached:
    case opcode::OP_EvalLocalVariableCached:
    case opcode::OP_SafeSetWaittillVariableFieldCached:
    case opcode::OP_CreateLocalVariable:
    case opcode::OP_EvalLocalVariableObjectCached:
    case opcode::OP_EvalLocalArrayCached:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
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
        this->disassemble_field_variable(inst);
        break;
    case opcode::OP_CallBuiltinPointer:
    case opcode::OP_CallBuiltinMethodPointer:
    case opcode::OP_ScriptThreadCallPointer:
    case opcode::OP_ScriptChildThreadCallPointer:
    case opcode::OP_ScriptMethodThreadCallPointer:
    case opcode::OP_ScriptMethodChildThreadCallPointer:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        break;
    case opcode::OP_GetLocalFunction:
    case opcode::OP_ScriptLocalFunctionCall2:
    case opcode::OP_ScriptLocalFunctionCall:
    case opcode::OP_ScriptLocalMethodCall:
        this->disassemble_local_call(inst, false);
        break;
    case opcode::OP_ScriptLocalThreadCall:
    case opcode::OP_ScriptLocalChildThreadCall:
    case opcode::OP_ScriptLocalMethodThreadCall:
    case opcode::OP_ScriptLocalMethodChildThreadCall:
        this->disassemble_local_call(inst, true);
        break;
    case opcode::OP_GetFarFunction:
    case opcode::OP_ScriptFarFunctionCall2:
    case opcode::OP_ScriptFarFunctionCall:
    case opcode::OP_ScriptFarMethodCall:
        this->disassemble_far_call(inst, false);
        break;
    case opcode::OP_ScriptFarThreadCall:
    case opcode::OP_ScriptFarChildThreadCall:
    case opcode::OP_ScriptFarMethodThreadCall:
    case opcode::OP_ScriptFarMethodChildThreadCall:
        this->disassemble_far_call(inst, true);
        break;
    case opcode::OP_CallBuiltin:
        this->disassemble_builtin_call(inst, false, true);
        break;
    case opcode::OP_CallBuiltinMethod:
        this->disassemble_builtin_call(inst, true, true);
        break;
    case opcode::OP_GetBuiltinFunction:
    case opcode::OP_CallBuiltin0:
    case opcode::OP_CallBuiltin1:
    case opcode::OP_CallBuiltin2:
    case opcode::OP_CallBuiltin3:
    case opcode::OP_CallBuiltin4:
    case opcode::OP_CallBuiltin5:
        this->disassemble_builtin_call(inst, false, false);
        break;
    case opcode::OP_GetBuiltinMethod:
    case opcode::OP_CallBuiltinMethod0:
    case opcode::OP_CallBuiltinMethod1:
    case opcode::OP_CallBuiltinMethod2:
    case opcode::OP_CallBuiltinMethod3:
    case opcode::OP_CallBuiltinMethod4:
    case opcode::OP_CallBuiltinMethod5:
        this->disassemble_builtin_call(inst, true, false);
        break;
    case opcode::OP_JumpOnFalse:
    case opcode::OP_JumpOnTrue:
    case opcode::OP_JumpOnFalseExpr:
    case opcode::OP_JumpOnTrueExpr:
        this->disassemble_jump(inst, true, false);
        break;
    case opcode::OP_jumpback:
        this->disassemble_jump(inst, false, true);
        break;
    case opcode::OP_jump:
        this->disassemble_jump(inst, false, false);
        break;
    case opcode::OP_switch:
        this->disassemble_switch(inst);
        break;
    case opcode::OP_endswitch:
        this->disassemble_end_switch(inst);
        break;
/*
    case opcode::OP_prof_begin:
        script_->seek(5); // TODO: skipped data
        break;
    case opcode::OP_prof_end:
        script_->seek(1); // TODO: skipped data
        break;
    case opcode::OP_EvalNewLocalArrayRefCached0_Precompiled:
    case opcode::OP_SetNewLocalVariableFieldCached0_Precompiled:
    case opcode::OP_CreateLocalVariable_Precompiled:
    case opcode::OP_SafeCreateVariableFieldCached_Precompiled:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        break;
*/
    case opcode::OP_FormalParams:
    case opcode::OP_FormalParams_Precompiled:
        this->disassemble_formal_params(inst);
        break;
/*  case opcode::OP_NativeGetLocalFunction:
    case opcode::OP_NativeLocalFunctionCall:
    case opcode::OP_NativeLocalFunctionCall2:
    case opcode::OP_NativeLocalMethodCall:
        this->disassemble_local_call(inst, false);
        break;
    case opcode::OP_NativeGetFarFunction:
    case opcode::OP_NativeFarFunctionCall:
    case opcode::OP_NativeFarFunctionCall2:
    case opcode::OP_NativeFarMethodCall:
        this->disassemble_far_call(inst, false);
        break;
    case opcode::OP_NativeLocalFunctionThreadCall:
    case opcode::OP_NativeLocalMethodThreadCall:
    case opcode::OP_NativeLocalFunctionChildThreadCall:
    case opcode::OP_NativeLocalMethodChildThreadCall:
        this->disassemble_local_call(inst, true);
        break;
    case opcode::OP_NativeFarFunctionThreadCall:
    case opcode::OP_NativeFarMethodThreadCall:
    case opcode::OP_NativeFarFunctionChildThreadCall:
    case opcode::OP_NativeFarMethodChildThreadCall:
        this->disassemble_far_call(inst, true);
        break;
*/
    default:
        throw gsc::disasm_error(utils::string::va("Unhandled opcode 0x%X at index '%04X'!", inst->opcode, inst->index));
    }
}

void disassembler::disassemble_builtin_call(const gsc::instruction_ptr& inst, bool method, bool arg_num)
{
    if (arg_num)
    {
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
    }

    if (method)
    {
        inst->data.push_back(resolver::method_name(script_->read<std::uint16_t>()));
    }
    else
    {
        inst->data.push_back(resolver::function_name(script_->read<std::uint16_t>()));
    }
}

void disassembler::disassemble_local_call(const gsc::instruction_ptr& inst, bool thread)
{
    std::int32_t offset = this->disassemble_offset();

    inst->data.push_back(utils::string::va("%X", offset + inst->index + 1));

    if (thread)
    {
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
    }
}

void disassembler::disassemble_far_call(const gsc::instruction_ptr& inst, bool thread)
{
    script_->seek(3);

    if (thread)
    {
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
    }

    auto file_id = stack_->read<std::uint32_t>();
    auto file_name = file_id == 0 ? stack_->read_c_string() : resolver::file_name(file_id);
    auto func_id = stack_->read<std::uint32_t>();
    auto func_name = func_id == 0 ? stack_->read_c_string() : resolver::token_name(func_id);

    inst->data.push_back(file_name != "" ? file_name : utils::string::va("_ID%i", file_id));
    inst->data.push_back(func_name != "" ? func_name : utils::string::va("_ID%i", func_id));
}

void disassembler::disassemble_jump(const gsc::instruction_ptr& inst, bool expr, bool back)
{
    std::int32_t addr;
    std::string label;

    if (expr)
    {
        addr = inst->index + 3 + script_->read<std::int16_t>();
        label = utils::string::va("loc_%X", addr);
        inst->data.push_back(label);
    }
    else if (back)
    {
        addr = inst->index + 3 - script_->read<std::uint16_t>();
        label = utils::string::va("loc_%X", addr);
        inst->data.push_back(label);
    }
    else
    {
        addr = inst->index + 5 + script_->read<std::int32_t>();
        label = utils::string::va("loc_%X", addr);
        inst->data.push_back(label);
    }

    labels_.insert({addr, label});
}

void disassembler::disassemble_field_variable(const gsc::instruction_ptr& inst)
{
    std::uint32_t field_id = script_->read<std::uint32_t>();
    std::string field_name;

    if(field_id > 0x110F3)
    {   
        auto temp = stack_->read<std::uint32_t>();
        field_name = temp == 0 ? stack_->read_c_string() : std::to_string(temp);
    }
    else
    {
        field_name = resolver::token_name(field_id);
    }

    inst->data.push_back(field_name != "" ? field_name : utils::string::va("_ID%i", field_id));
}

void disassembler::disassemble_formal_params(const gsc::instruction_ptr& inst)
{
    auto size = script_->read<std::uint8_t>();

    inst->size += size;
    inst->data.push_back(utils::string::va("%i", size));

    while(size > 0)
    {
        inst->data.push_back(utils::string::va("%d", script_->read<std::uint8_t>()));
        size--;
    }
}

void disassembler::disassemble_switch(const gsc::instruction_ptr& inst)
{
    std::int32_t addr = inst->index + 4 + script_->read<std::int32_t>();
    std::string label = utils::string::va("loc_%X", addr);

    inst->data.push_back(label);
    labels_.insert({addr, label});
}

void disassembler::disassemble_end_switch(const gsc::instruction_ptr& inst)
{
    std::uint16_t case_num = script_->read<std::uint16_t>();
    inst->data.push_back(utils::string::va("%i", case_num));

    std::uint32_t internal_index = inst->index + 3;

    if (case_num)
    {
        for (auto i = case_num; i > 0; i--)
        {
            std::uint32_t case_label = script_->read<std::uint32_t>();

            if (case_label < 0x80000 && case_label > 0)
            {
                inst->data.push_back("case");
                inst->data.push_back(utils::string::quote(stack_->read_c_string(), false));
            }
            else if (case_label == 0)
            {
                inst->data.push_back("default");
                stack_->read<std::uint16_t>();
            }
            else
            {
                inst->data.push_back("case");
                inst->data.push_back(utils::string::va("%i", (case_label - 0x800000) & 0xFFFFFF));
            }

            inst->size += 4;
            internal_index += 4;

            auto addr = this->disassemble_offset() + internal_index;
            std::string label = utils::string::va("loc_%X", addr);
            inst->data.push_back(label);

            labels_.insert({addr, label});

            inst->size += 3;
            internal_index += 3;
        }
    }
}

auto disassembler::disassemble_offset() -> std::int32_t
{
    std::array<std::uint8_t, 4> bytes = {};

    for (auto i = 0; i < 3; i++)
    {
        bytes[i] = script_->read<std::uint8_t>();
    }

    std::int32_t offset = *reinterpret_cast<std::int32_t*>(bytes.data());

    offset = (offset << 8) >> 8;

    return offset;
}

void disassembler::resolve_local_functions()
{
    for (auto& func : functions_)
    {
        for (auto& inst : func->instructions)
        {
            switch (opcode(inst->opcode))
            {
            case opcode::OP_GetLocalFunction:
            case opcode::OP_ScriptLocalFunctionCall:
            case opcode::OP_ScriptLocalFunctionCall2:
            case opcode::OP_ScriptLocalMethodCall:
            case opcode::OP_ScriptLocalThreadCall:
            case opcode::OP_ScriptLocalChildThreadCall:
            case opcode::OP_ScriptLocalMethodThreadCall:
            case opcode::OP_ScriptLocalMethodChildThreadCall:
                inst->data.at(0) = this->resolve_function(inst->data[0]);
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

        for (auto& func : functions_)
        {
            if (func->index == idx)
            {
                return func->name;
            }
        }

        throw gsc::disasm_error(utils::string::va("Couldn't resolve function name at index '0x%04X'!", idx));
    }

    throw gsc::disasm_error(utils::string::va("\"%s\" is not valid function address!", index.data()));
}

void disassembler::print_function(const gsc::function_ptr& func)
{
    output_->write_string("\n");
    output_->write_string(utils::string::va("%s\n", func->name.data()));

    for (auto& inst : func->instructions)
    {
        const auto itr = func->labels.find(inst->index);

        if (itr != func->labels.end())
        {
            output_->write_string(utils::string::va("\t%s\n", itr->second.data()));
        }

        this->print_instruction(inst);
    }

    output_->write_string("\n");
    output_->write_string(utils::string::va("end_%s\n", func->name.substr(4).data()));
}

void disassembler::print_instruction(const gsc::instruction_ptr& inst)
{
    switch (opcode(inst->opcode))
    {
    case opcode::OP_endswitch:
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
                if (casenum != totalcase - 1)
                {
                    output_->write_string("\n");
                }
            }
        }
        break;
    default:
        output_->write_string(utils::string::va("\t\t%s", resolver::opcode_name(inst->opcode).data()));
        for (auto& d : inst->data)
        {
            output_->write_string(utils::string::va(" %s", d.data()));
        }
        break;
    }

    output_->write_string("\n");
}

} // namespace xsk::gsc::s4
