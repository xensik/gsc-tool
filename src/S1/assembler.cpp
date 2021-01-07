// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "S1.hpp"

namespace S1
{

auto assembler::output_script() -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> script;

    if(script_ == nullptr) return script;

    script.resize(script_->pos());
    memcpy(script.data(), script_->buffer().data(), script.size());

    return script;
}

auto assembler::output_stack() -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> stack;

    if(stack_ == nullptr) return stack;

    stack.resize(stack_->pos());
    memcpy(stack.data(), stack_->buffer().data(), stack.size());

    return stack;
}

void assembler::assemble(std::vector<std::uint8_t>& data)
{
    std::vector<std::string> assembly = utils::string::clean_buffer_lines(data);
    std::vector<gsc::function_ptr> functions;
    gsc::function_ptr func = nullptr;
    std::uint32_t index = 1;
    std::uint16_t switchnum = 0;

    for (auto& line : assembly)
    {
        if (line == "" || line.substr(0, 2) == "//")
        {
            continue;
        }
        else if (line.substr(0, 4) == "sub_")
        {
            func = std::make_unique<gsc::function>();
            func->index = index;
            func->name = line.substr(4);
        }
        else if (line.substr(0, 4) == "end_")
        {
            if (func != nullptr)
            {
                func->size = index - func->index;
                functions.push_back(std::move(func));
            }
        }
        else if (line.substr(0, 4) == "loc_")
        {
            func->labels[index] = line;
        }
        else
        {
            std::vector<std::string> data = utils::string::split(line, ' ');

            if (switchnum)
            {
                if (line.substr(0, 4) == "case" || line.substr(0, 7) == "default")
                {
                    for (auto& entry : data)
                    {
                        func->instructions.back()->data.push_back(entry);
                    }
                    switchnum--;
                    continue;
                }

                GSC_LOG_ERROR("invalid instruction inside endswitch \"%s\"!", line.data());
                return;
            }
            else
            {
                auto inst = std::make_unique<gsc::instruction>();
                inst->index = index;
                inst->opcode = static_cast<std::uint8_t>(resolver::opcode_id(utils::string::to_lower(data[0])));
                inst->size = opcode_size(opcode(inst->opcode));
                data.erase(data.begin());
                inst->data = data;

                if (opcode(inst->opcode) == opcode::OP_endswitch)
                {
                    switchnum = static_cast<std::uint16_t>(std::stoul(inst->data[0]));
                    inst->size += 7 * switchnum;
                }

                index += inst->size;
                func->instructions.push_back(std::move(inst));
            }
        }
    }

    this->assemble(functions);
}

void assembler::assemble(std::vector<gsc::function_ptr>& functions)
{
    script_ = std::make_unique<utils::byte_buffer>(0x100000);
    stack_ = std::make_unique<utils::byte_buffer>(0x100000);

    functions_ = std::move(functions);

    script_->write<std::uint8_t>(0x34);
    stack_->write<std::uint32_t>(0x69773630);

    for (const auto& func : functions_)
    {
        this->assemble_function(func);
    }
}

void assembler::assemble_function(const gsc::function_ptr& func)
{
    labels_ = func->labels;

    stack_->write<std::uint32_t>(func->size);

    func->id = func->name.substr(0, 3) == "_ID" ? std::stoul(func->name.substr(3)) : resolver::token_id(func->name);
    stack_->write<std::uint16_t>(func->id);

    if (func->id == 0)
    {
        stack_->write_c_string(func->name);
    }

    for (const auto& inst : func->instructions)
    {
        this->assemble_instruction(inst);
    }
}

void assembler::assemble_instruction(const gsc::instruction_ptr& inst)
{
    switch (opcode(inst->opcode))
    {
    case opcode::OP_Return:
    case opcode::OP_BoolNot:
    case opcode::OP_CastBool:
    case opcode::OP_inequality:
    case opcode::OP_GetThisthread:
    case opcode::OP_ClearLocalVariableFieldCached0:
    case opcode::OP_checkclearparams:
    case opcode::OP_CastFieldObject:
    case opcode::OP_End:
    case opcode::OP_size:
    case opcode::OP_EmptyArray:
    case opcode::OP_bit_and:
    case opcode::OP_less_equal:
    case opcode::OP_voidCodepos:
    case opcode::OP_ClearVariableField:
    case opcode::OP_divide:
    case opcode::OP_GetSelf:
    case opcode::OP_SetLocalVariableFieldCached0:
    case opcode::OP_plus:
    case opcode::OP_BoolComplement:
    case opcode::OP_ScriptMethodCallPointer:
    case opcode::OP_inc:
    case opcode::OP_clearparams:
    case opcode::OP_EvalLocalVariableRefCached0:
    case opcode::OP_ScriptFunctionCallPointer:
    case opcode::OP_endon:
    case opcode::OP_greater_equal:
    case opcode::OP_GetSelfObject:
    case opcode::OP_SetVariableField:
    case opcode::OP_EvalLocalArrayRefCached0:
    case opcode::OP_less:
    case opcode::OP_GetGameRef:
    case opcode::OP_waitFrame:
    case opcode::OP_waittillFrameEnd:
    case opcode::OP_SafeSetVariableFieldCached0:
    case opcode::OP_GetLevel:
    case opcode::OP_notify:
    case opcode::OP_DecTop:
    case opcode::OP_shift_left:
    case opcode::OP_greater:
    case opcode::OP_EvalLocalVariableCached0:
    case opcode::OP_EvalLocalVariableCached1:
    case opcode::OP_EvalLocalVariableCached2:
    case opcode::OP_EvalLocalVariableCached3:
    case opcode::OP_EvalLocalVariableCached4:
    case opcode::OP_EvalLocalVariableCached5:
    case opcode::OP_GetZero:
    case opcode::OP_wait:
    case opcode::OP_minus:
    case opcode::OP_EvalNewLocalVariableRefCached0:
    case opcode::OP_multiply:
    case opcode::OP_mod:
    case opcode::OP_GetGame:
    case opcode::OP_waittill:
    case opcode::OP_dec:
    case opcode::OP_PreScriptCall:
    case opcode::OP_GetAnim:
    case opcode::OP_GetUndefined:
    case opcode::OP_GetAnimObject:
    case opcode::OP_GetLevelObject:
    case opcode::OP_bit_ex_or:
    case opcode::OP_equality:
    case opcode::OP_ClearArray:
    case opcode::OP_EvalArrayRef:
    case opcode::OP_EvalArray:
    case opcode::OP_vector:
    case opcode::OP_bit_or:
    case opcode::OP_AddArray:
    case opcode::OP_waittillmatch2:
    case opcode::OP_shift_right:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        break;
    case opcode::OP_GetByte:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stol(inst->data[0])));
        break;
    case opcode::OP_GetNegByte:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::int8_t>(static_cast<std::int8_t>(std::stol(inst->data[0])));
        break;
    case opcode::OP_GetUnsignedShort:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::uint16_t>(static_cast<std::uint16_t>(std::stol(inst->data[0])));
        break;
    case opcode::OP_GetNegUnsignedShort:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::int16_t>(static_cast<std::int16_t>(std::stol(inst->data[0])));
    case opcode::OP_GetInteger:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::int32_t>(std::stol(inst->data[0]));
        break;
    case opcode::OP_GetFloat:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<float>(std::stof(inst->data[0]));
        break;
    case opcode::OP_GetVector:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<float>(std::stof(inst->data[0]));
        script_->write<float>(std::stof(inst->data[1]));
        script_->write<float>(std::stof(inst->data[2]));
        break;
    case opcode::OP_GetString:
    case opcode::OP_GetIString:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::uint32_t>(0);
        stack_->write_c_string(utils::string::to_code(inst->data[0]));
        break;
    case opcode::OP_GetAnimation:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::uint32_t>(0);
        script_->write<std::uint32_t>(0);
        stack_->write_c_string(inst->data[0]);
        stack_->write_c_string(inst->data[1]);
        break;
    case opcode::OP_GetAnimTree:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::uint8_t>(0);
        stack_->write_c_string(inst->data[0]);
        break;
    case opcode::OP_waittillmatch:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::uint16_t>(0);
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
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stol(inst->data[0])));
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
        this->assemble_field_variable(inst);
        break;
    case opcode::OP_CallBuiltinPointer:
    case opcode::OP_CallBuiltinMethodPointer:
    case opcode::OP_ScriptThreadCallPointer:
    case opcode::OP_ScriptChildThreadCallPointer:
    case opcode::OP_ScriptMethodThreadCallPointer:
    case opcode::OP_ScriptMethodChildThreadCallPointer:
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stol(inst->data[0])));
        break;
    case opcode::OP_GetLocalFunction:
    case opcode::OP_ScriptLocalFunctionCall2:
    case opcode::OP_ScriptLocalFunctionCall:
    case opcode::OP_ScriptLocalMethodCall:
        this->assemble_local_call(inst, false);
        break;
    case opcode::OP_ScriptLocalThreadCall:
    case opcode::OP_ScriptLocalChildThreadCall:
    case opcode::OP_ScriptLocalMethodThreadCall:
    case opcode::OP_ScriptLocalMethodChildThreadCall:
        this->assemble_local_call(inst, true);
        break;
    case opcode::OP_GetFarFunction:
    case opcode::OP_ScriptFarFunctionCall2:
    case opcode::OP_ScriptFarFunctionCall:
    case opcode::OP_ScriptFarMethodCall:    
        this->assemble_far_call(inst, false);
        break;
    case opcode::OP_ScriptFarThreadCall:
    case opcode::OP_ScriptFarChildThreadCall:
    case opcode::OP_ScriptFarMethodThreadCall:
    case opcode::OP_ScriptFarMethodChildThreadCall:
        this->assemble_far_call(inst, true);
        break;
    case opcode::OP_CallBuiltin:
        this->assemble_builtin_call(inst, false, true);
        break;
    case opcode::OP_CallBuiltinMethod:
        this->assemble_builtin_call(inst, true, true);
        break;
    case opcode::OP_GetBuiltinFunction:
    case opcode::OP_CallBuiltin0:
    case opcode::OP_CallBuiltin1:
    case opcode::OP_CallBuiltin2:
    case opcode::OP_CallBuiltin3:
    case opcode::OP_CallBuiltin4:
    case opcode::OP_CallBuiltin5:
        this->assemble_builtin_call(inst, false, false);
        break;
    case opcode::OP_GetBuiltinMethod:
    case opcode::OP_CallBuiltinMethod0:
    case opcode::OP_CallBuiltinMethod1:
    case opcode::OP_CallBuiltinMethod2:
    case opcode::OP_CallBuiltinMethod3:
    case opcode::OP_CallBuiltinMethod4:
    case opcode::OP_CallBuiltinMethod5:
        this->assemble_builtin_call(inst, true, false);
        break;
    case opcode::OP_JumpOnFalseExpr:
    case opcode::OP_JumpOnTrueExpr:
    case opcode::OP_JumpOnFalse:
    case opcode::OP_JumpOnTrue:
        this->assemble_jump(inst, true, false);
        break;
    case opcode::OP_jumpback:
        this->assemble_jump(inst, false, true);
        break;
    case opcode::OP_jump:
        this->assemble_jump(inst, false, false);
        break;
    case opcode::OP_switch:
        this->assemble_switch(inst);
        break;
    case opcode::OP_endswitch:
        this->assemble_end_switch(inst);
        break;
    default:
        GSC_ASM_ERROR("Unhandled opcode (0x%hhX) at index '%04X'!", inst->opcode, inst->index);
        break;
    }
}

void assembler::assemble_builtin_call(const gsc::instruction_ptr& inst, bool method, bool arg_num)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    std::uint16_t id = 0;

    if (arg_num)
    {
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stol(inst->data[0])));

        if (method)
            id = inst->data[1].substr(0, 3) == "_ID" ? std::stol(inst->data[1].substr(3)) : resolver::builtin_method_id(inst->data[1]);
        else
            id = inst->data[1].substr(0, 3) == "_ID" ? std::stol(inst->data[1].substr(3)) : resolver::builtin_func_id(inst->data[1]);
    }
    else
    {
        if (method)
            id = inst->data[0].substr(0, 3) == "_ID" ? std::stol(inst->data[0].substr(3)) : resolver::builtin_method_id(inst->data[0]);
        else
            id = inst->data[0].substr(0, 3) == "_ID" ? std::stol(inst->data[0].substr(3)) : resolver::builtin_func_id(inst->data[0]);
    }

    script_->write<std::uint16_t>(id);
}

void assembler::assemble_local_call(const gsc::instruction_ptr& inst, bool thread)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    std::int32_t addr = this->resolve_function(inst->data[0]);

    std::int32_t offset = addr - inst->index - 1;

    this->assemble_offset(offset);

    if (thread)
    {
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stol(inst->data[1])));
    }
}

void assembler::assemble_far_call(const gsc::instruction_ptr& inst, bool thread)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
    script_->write<std::uint8_t>(0);
    script_->write<std::uint16_t>(0);

    std::uint16_t file_id = 0;
    std::uint16_t func_id = 0;

    if (thread)
    {
        script_->write<std::uint8_t>(static_cast<std::uint8_t>(std::stol(inst->data[0])));

        file_id = inst->data[1].substr(0, 3) == "_ID" ? std::stol(inst->data[1].substr(3)) : resolver::file_id(inst->data[1]);
        func_id = inst->data[2].substr(0, 3) == "_ID" ? std::stol(inst->data[2].substr(3)) : resolver::token_id(inst->data[2]);
    }
    else
    {
        file_id = inst->data[0].substr(0, 3) == "_ID" ? std::stol(inst->data[0].substr(3)) : resolver::file_id(inst->data[0]);
        func_id = inst->data[1].substr(0, 3) == "_ID" ? std::stol(inst->data[1].substr(3)) : resolver::token_id(inst->data[1]);
    }

    stack_->write<std::uint16_t>(file_id);
    if (file_id == 0) stack_->write_c_string(thread ? inst->data[1] : inst->data[0]);
    stack_->write<std::uint16_t>(func_id);
    if (func_id == 0) stack_->write_c_string(thread ? inst->data[2] : inst->data[1]);
}

void assembler::assemble_switch(const gsc::instruction_ptr& inst)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    std::int32_t addr = this->resolve_label(inst, inst->data[0]);

    script_->write<std::int32_t>(addr - inst->index - 4);
}

void assembler::assemble_end_switch(const gsc::instruction_ptr& inst)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    std::uint16_t casenum = 0;

    if (utils::string::is_number(inst->data[0]))
    {
        casenum = std::stol(inst->data[0]);
    }
    else
    {
        GSC_ASM_ERROR("invalid endswitch number!");
    }

    script_->write<std::uint16_t>(casenum);

    std::uint32_t internal_index = inst->index + 3;

    for (std::uint16_t i = 0; i < casenum; i++)
    {
        if (inst->data[1 + (3 * i)] == "case")
        {
            script_->write<uint32_t>(i + 1);
            stack_->write_c_string(utils::string::to_code(inst->data[1 + (3 * i) + 1]));

            internal_index += 4;

            std::int32_t addr = this->resolve_label(inst, inst->data[1 + (3 * i) + 2]);

            this->assemble_offset(addr - internal_index);

            internal_index += 3;
        }
        else if (inst->data[1 + (3 * i)] == "default")
        {
            script_->write<uint32_t>(0);
            stack_->write_c_string("\x01");

            internal_index += 4;
            std::int32_t addr = this->resolve_label(inst, inst->data[1 + (3 * i) + 1]);

            this->assemble_offset(addr - internal_index);

            internal_index += 3;
        }
    }
}

void assembler::assemble_field_variable(const gsc::instruction_ptr& inst)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    std::uint16_t field_id = 0;

    if (inst->data[0].substr(0, 3) == "_ID")
    {
        field_id = (std::uint16_t)std::stol(inst->data[0].substr(3));
    }
    else
    {
        field_id = resolver::token_id(inst->data[0]);

        if (field_id == 0)
        {
            field_id = 0xFFFF;
        }
    }

    script_->write<std::uint16_t>(field_id);

    if (field_id > 0xA7DC)
    {
        stack_->write<std::uint16_t>(0);
        stack_->write_c_string(inst->data[0]);
    }
}

void assembler::assemble_jump(const gsc::instruction_ptr& inst, bool expr, bool back)
{
    script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

    std::int32_t addr = this->resolve_label(inst, inst->data[0]);

    if (expr)
    {
        script_->write<std::int16_t>(addr - inst->index - 3);
    }
    else if (back)
    {
        script_->write<std::int16_t>((inst->index + 3) - addr);
    }
    else
    {
        script_->write<std::int32_t>(addr - inst->index - 5);
    }
}

void assembler::assemble_offset(std::int32_t offset)
{
    offset = (offset << 10) >> 8;

    std::vector<std::uint8_t> bytes;
    bytes.resize(4);

    std::fill(bytes.begin(), bytes.end(), 0);
    *reinterpret_cast<std::int32_t*>(bytes.data()) = offset;

    script_->write<std::uint8_t>(bytes[0]);
    script_->write<std::uint8_t>(bytes[1]);
    script_->write<std::uint8_t>(bytes[2]);
}

auto assembler::resolve_function(const std::string& name) -> std::uint32_t
{
    auto temp = name.substr(0, 4) == "sub_" ? name.substr(4) : name;
    
    for (const auto& func : functions_)
    {
        if (func->name == temp)
        {
            return func->index;
        }
    }

    GSC_ASM_ERROR("Couldn't resolve local function address of '%s'!", name.data());
    return 0;
}

auto assembler::resolve_label(const gsc::instruction_ptr& inst, const std::string& name) -> std::uint32_t
{
    for (auto& func : labels_)
    {
        if (func.second == name)
        {
            return func.first;
        }
    }

    GSC_ASM_ERROR("Couldn't resolve label address of '%s'!", name.data());
    return 0;
}

}  // namespace S1
