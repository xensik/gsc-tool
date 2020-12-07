// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW6.hpp"

namespace IW6
{

auto disassembler::output() -> std::vector<gsc::function_ptr>
{
    return std::move(functions_);
}

auto disassembler::output_data() -> std::vector<std::uint8_t>
{
    output_ = std::make_unique<utils::byte_buffer>(0x100000);

    output_->write_string("// IW6 PC GSCASM\n");
    output_->write_string("// Disassembled by https://github.com/xensik/gsc-tool\n");

    for (auto& func : functions_)
    {
        this->print_function(func);

        for (auto& inst : func->instructions)
        {
            const auto itr = func->labels.find(inst->index);

            if (itr != func->labels.end())
            {
                this->print_label(itr->second);
            }

            this->print_instruction(inst);
        }
    }

    std::vector<std::uint8_t> output;

    output.resize(output_->pos());
    memcpy(output.data(), output_->buffer().data(), output.size());

    return output;
}

void disassembler::disassemble(std::vector<std::uint8_t>& script, std::vector<std::uint8_t>& stack)
{
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
        func->id = stack_->read<std::uint16_t>();
        func->name = "sub_"s + (func->id == 0 ? stack_->read_string() : resolver::token_name(func->id));

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
        inst->size = opcode_size(opcode(inst->opcode));
        
        this->dissasemble_instruction(inst);
        
        size -= inst->size;
    }
}

void disassembler::dissasemble_instruction(const gsc::instruction_ptr& inst)
{
    switch (opcode(inst->opcode))
    {
    case opcode::OP_GetUndefined:
    case opcode::OP_GetLevel:
    case opcode::OP_GetSelf:
    case opcode::OP_GetGame:
    case opcode::OP_GetAnim:
    case opcode::OP_GetGameRef:
    case opcode::OP_GetLevelObject:
    case opcode::OP_GetAnimObject:
    case opcode::OP_GetSelfObject:
    case opcode::OP_GetZero:
    case opcode::OP_inc:
    case opcode::OP_dec:
    case opcode::OP_bit_or:
    case opcode::OP_bit_ex_or:
    case opcode::OP_bit_and:
    case opcode::OP_equality:
    case opcode::OP_inequality:
    case opcode::OP_less:
    case opcode::OP_greater:
    case opcode::OP_less_equal:
    case opcode::OP_greater_equal:
    case opcode::OP_shift_left:
    case opcode::OP_shift_right:
    case opcode::OP_plus:
    case opcode::OP_minus:
    case opcode::OP_multiply:
    case opcode::OP_divide:
    case opcode::OP_mod:
    case opcode::OP_BoolNot:
    case opcode::OP_BoolComplement:
    case opcode::OP_CastBool:
    case opcode::OP_CastFieldObject:
    case opcode::OP_vector:
    case opcode::OP_size:
    case opcode::OP_End:
    case opcode::OP_Return:
    case opcode::OP_waittill:
    case opcode::OP_notify:
    case opcode::OP_endon:
    case opcode::OP_voidCodepos:
    case opcode::OP_waittillFrameEnd:
    case opcode::OP_PreScriptCall:
    case opcode::OP_clearparams:
    case opcode::OP_checkclearparams:
    case opcode::OP_wait:
    case opcode::OP_DecTop:
    case opcode::OP_EvalArray:
    case opcode::OP_EvalArrayRef:
    case opcode::OP_ClearArray:
    case opcode::OP_EmptyArray:
    case opcode::OP_AddArray:
        break;
// DATA
    case opcode::OP_GetByte:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        break;
    case opcode::OP_GetNegByte:
        inst->data.push_back(utils::string::va("%i", script_->read<std::int8_t>()));
        break;
    case opcode::OP_GetUnsignedShort:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint16_t>()));
        break;
    case opcode::OP_GetNegUnsignedShort:
        inst->data.push_back(utils::string::va("%i", script_->read<std::int16_t>()));
        break;
    case opcode::OP_GetInteger:
        inst->data.push_back(utils::string::va("%i", script_->read<std::int32_t>()));
        break;
    case opcode::OP_GetFloat:
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        break;
    case opcode::OP_GetVector:
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        inst->data.push_back(utils::string::va("%g", script_->read<float>()));
        break;
    case opcode::OP_GetString:
    case opcode::OP_GetIString:
        script_->seek(4);
        inst->data.push_back(utils::string::va("\"%s\"", stack_->read_string().data()));
        break;
    case opcode::OP_GetAnimation:
        script_->seek(8);
        inst->data.push_back(utils::string::va("\"%s\"", stack_->read_string().data()));
        inst->data.push_back(utils::string::va("\"%s\"", stack_->read_string().data()));
        break;
    case opcode::OP_GetAnimTree:
        script_->seek(1);
        inst->data.push_back(utils::string::va("\"%s\"", stack_->read_string().data()));
        break;
// WAITTILLMATCH
    case opcode::OP_waittillmatch:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint16_t>()));
        break;
// VARIABLE
    case opcode::OP_EvalLocalVariableCached0:
    case opcode::OP_EvalLocalVariableCached1:
    case opcode::OP_EvalLocalVariableCached2:
    case opcode::OP_EvalLocalVariableCached3:
    case opcode::OP_EvalLocalVariableCached4:
    case opcode::OP_EvalLocalVariableCached5:
    case opcode::OP_EvalLocalVariableRefCached0:
    case opcode::OP_EvalLocalArrayRefCached0:
    case opcode::OP_SetLocalVariableFieldCached0:
    case opcode::OP_ClearLocalVariableFieldCached0:
    case opcode::OP_SetVariableField:
        break;
    case opcode::OP_EvalNewLocalArrayRefCached0:
    case opcode::OP_CreateLocalVariable:
    case opcode::OP_RemoveLocalVariables:
    case opcode::OP_EvalLocalVariableCached:
    case opcode::OP_EvalLocalArrayCached:
    case opcode::OP_EvalLocalArrayRefCached:
    case opcode::OP_SafeCreateVariableFieldCached:
    case opcode::OP_SafeSetWaittillVariableFieldCached:
    case opcode::OP_EvalLocalVariableRefCached:
    case opcode::OP_SetNewLocalVariableFieldCached0:
    case opcode::OP_SetLocalVariableFieldCached:
    case opcode::OP_ClearLocalVariableFieldCached:
    case opcode::OP_EvalLocalVariableObjectCached:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        break;
// VARIABLE FIELD
    case opcode::OP_EvalLevelFieldVariable:
    case opcode::OP_EvalAnimFieldVariable:
    case opcode::OP_EvalSelfFieldVariable:
    case opcode::OP_EvalFieldVariable:
    case opcode::OP_EvalLevelFieldVariableRef:
    case opcode::OP_EvalAnimFieldVariableRef:
    case opcode::OP_EvalSelfFieldVariableRef:
    case opcode::OP_EvalFieldVariableRef:
    case opcode::OP_ClearFieldVariable:
    case opcode::OP_SetLevelFieldVariableField:
    case opcode::OP_SetAnimFieldVariableField:
    case opcode::OP_SetSelfFieldVariableField:
        this->disassemble_field_variable(inst);
        break;
// POINTER
    case opcode::OP_ScriptFunctionCallPointer:
    case opcode::OP_ScriptMethodCallPointer:
        break;
    case opcode::OP_CallBuiltinPointer:
    case opcode::OP_CallBuiltinMethodPointer:
    case opcode::OP_ScriptThreadCallPointer:
    case opcode::OP_ScriptMethodThreadCallPointer:
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
        break;
// FAR CALL
    case opcode::OP_GetFarFunction:
    case opcode::OP_ScriptFarFunctionCall2:
    case opcode::OP_ScriptFarFunctionCall:
    case opcode::OP_ScriptFarMethodCall:
        this->disassemble_far_call(inst, false);
        break;
    case opcode::OP_ScriptFarThreadCall:
    case opcode::OP_ScriptFarMethodThreadCall:
        this->disassemble_far_call(inst, true);
        break;
// LOCAL CALL
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
// BUILTIN
    case opcode::OP_GetBuiltinFunction:
        this->disassemble_builtin_call(inst, false, false);
        break;
    case opcode::OP_GetBuiltinMethod:
        this->disassemble_builtin_call(inst, true, false);
        break;
    case opcode::OP_CallBuiltin:
        this->disassemble_builtin_call(inst, false, true);
        break;
    case opcode::OP_CallBuiltinMethod:
        this->disassemble_builtin_call(inst, true, true);
        break;
    case opcode::OP_CallBuiltin0:
    case opcode::OP_CallBuiltin1:
    case opcode::OP_CallBuiltin2:
    case opcode::OP_CallBuiltin3:
    case opcode::OP_CallBuiltin4:
    case opcode::OP_CallBuiltin5:
        this->disassemble_builtin_call(inst, false, false);
        break;
    case opcode::OP_CallBuiltinMethod0:
    case opcode::OP_CallBuiltinMethod1:
    case opcode::OP_CallBuiltinMethod2:
    case opcode::OP_CallBuiltinMethod3:
    case opcode::OP_CallBuiltinMethod4:
    case opcode::OP_CallBuiltinMethod5:
        this->disassemble_builtin_call(inst, true, false);
        break;
// JUMP
    case opcode::OP_jump:
        this->disassemble_jump(inst, false, false);
        break;
    case opcode::OP_jumpback:
        this->disassemble_jump(inst, false, true);
        break;
    case opcode::OP_JumpOnFalse:
    case opcode::OP_JumpOnTrue:
    case opcode::OP_JumpOnFalseExpr:
    case opcode::OP_JumpOnTrueExpr:
        this->disassemble_jump(inst, true, false);
        break;
// SWITCH
    case opcode::OP_switch:
        this->disassemble_switch(inst);
        break;
    case opcode::OP_endswitch:
        this->disassemble_end_switch(inst);
        break;
    default:
        DISASSEMBLER_ERROR("Unhandled opcode 0x%hhX at index '%04X'!", inst->opcode, inst->index);
        break;
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
        inst->data.push_back(resolver::builtin_method_name(script_->read<std::uint16_t>()));
    }
    else
    {
        inst->data.push_back(resolver::builtin_func_name(script_->read<std::uint16_t>()));
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

    auto file_id = stack_->read<std::uint16_t>();
    auto file_name = file_id == 0 ? stack_->read_string() : resolver::file_name(file_id);
    auto func_id = stack_->read<std::uint16_t>();
    auto func_name = func_id == 0 ? stack_->read_string() : resolver::token_name(func_id);

    inst->data.push_back(file_name != "" ? file_name : utils::string::va("id#%i", file_id));
    inst->data.push_back(func_name != "" ? func_name : utils::string::va("id#%i", func_id));
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
    std::uint16_t field_id = script_->read<std::uint16_t>();
    std::string field_name = field_id > 38305 ? stack_->read_opaque_string() : resolver::token_name(field_id);

    inst->data.push_back(field_name != "" ? field_name : utils::string::va("id#%i", field_id));
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

            if (case_label < 0x10000 && case_label > 0)
            {
                inst->data.push_back("case");
                inst->data.push_back(utils::string::va("\"%s\"", stack_->read_string().data()));
            }
            else if (case_label < 0x40000)
            {
                inst->data.push_back("default");
                stack_->read<std::uint16_t>(); // should always be 01 00
            }
            else
            {
                inst->data.push_back("case");
                inst->data.push_back(utils::string::va("%i", case_label & 0xFFFF));
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
    std::vector<std::uint8_t> bytes;

    bytes.resize(4);
    std::fill(bytes.begin(), bytes.end(), 0);

    for (int i = 0; i < 3; i++)
    {
        bytes[i] = script_->read<std::uint8_t>();
    }

    std::int32_t offset = *reinterpret_cast<std::int32_t*>(bytes.data());

    offset = (offset << 8) >> 10;

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

        DISASSEMBLER_ERROR("Couldn't resolve function name at index '0x%04X'!", idx);
        return index;
    }
    else
    {
        DISASSEMBLER_ERROR("\"%s\" is not valid function address!", index.data());
        return index;
    }
}

void disassembler::print_opcodes(std::uint32_t index, std::uint32_t size)
{
    output_->write_string("\t\t");
}

void disassembler::print_function(const gsc::function_ptr& func)
{
    output_->write_string("\n");
    output_->write_string(utils::string::va("%s\n", func->name.data()));
}

void disassembler::print_instruction(const gsc::instruction_ptr& inst)
{
    switch (opcode(inst->opcode))
    {
    case opcode::OP_endswitch:
        this->print_opcodes(inst->index, 3);
        output_->write_string(utils::string::va("%s", resolver::opcode_name(opcode(inst->opcode)).data()));
        output_->write_string(utils::string::va(" %s\n", inst->data[0].data()));
        {
            std::uint32_t totalcase = std::stoul(inst->data[0]);
            auto index = 0;
            for (auto casenum = 0u; casenum < totalcase; casenum++)
            {
                this->print_opcodes(inst->index, 7);
                if (inst->data[1 + index] == "case")
                {
                    output_->write_string(utils::string::va("%s %s %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data(), inst->data[1 + index + 2].data()));
                    index += 3;
                }
                else if (inst->data[1 + index] == "default")
                {
                    output_->write_string(utils::string::va("%s %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data()));
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
        this->print_opcodes(inst->index, inst->size);
        output_->write_string(utils::string::va("%s", resolver::opcode_name(opcode(inst->opcode)).data()));
        for (auto& d : inst->data)
        {
            output_->write_string(utils::string::va(" %s", d.data()));
        }
        break;
    }

    output_->write_string("\n");
}

void disassembler::print_label(const std::string& label)
{
    output_->write_string(utils::string::va("\t%s\n", label.data()));
}

} // namespace IW6
