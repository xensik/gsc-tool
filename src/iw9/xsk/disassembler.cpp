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
        func->id = stack_->read<std::uint32_t>();
        func->name = func->id == 0 ? decrypt_string(stack_->read_c_string()) : resolver::token_name(func->id);

        dissasemble_function(func);

        func->labels = labels_;
        labels_.clear();
    }

    resolve_local_functions();
}

void disassembler::dissasemble_function(const function::ptr& func)
{
    auto size = func->size;

    while (size > 0)
    {
        func->instructions.push_back(std::make_unique<instruction>());

        const auto& inst = func->instructions.back();
        inst->index = static_cast<std::uint32_t>(script_->pos());
        inst->opcode = script_->read<std::uint8_t>();
        inst->size = opcode_size(inst->opcode);

        dissasemble_instruction(inst);

        size -= inst->size;
    }
}

void disassembler::dissasemble_instruction(const instruction::ptr& inst)
{
    /*switch (static_cast<opcode>(inst->opcode))
    {

        default:
            throw disasm_error(utils::string::va("unhandled opcode 0x%X at index '%04X'!", inst->opcode, inst->index));
    }*/
}

void disassembler::disassemble_builtin_call(const instruction::ptr& inst, bool method, bool args)
{
    if (args)
    {
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
    }

    const auto id = script_->read<std::uint16_t>();
    const auto name = method ? resolver::method_name(id) : resolver::function_name(id);
    inst->data.emplace(inst->data.begin(), name);
}

void disassembler::disassemble_local_call(const instruction::ptr& inst, bool thread)
{
    const auto offset = disassemble_offset();

    inst->data.push_back(utils::string::va("%X", offset + inst->index + 1));

    if (thread)
    {
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
    }
}

void disassembler::disassemble_far_call(const instruction::ptr& inst, bool thread)
{
    script_->seek(3);

    if (thread)
    {
        inst->data.push_back(utils::string::va("%i", script_->read<std::uint8_t>()));
    }

    const auto file_id = stack_->read<std::uint32_t>();
    const auto file_name = file_id == 0 ? decrypt_string(stack_->read_c_string()) : resolver::token_name(file_id);
    const auto func_id = stack_->read<std::uint32_t>();
    const auto func_name = func_id == 0 ? decrypt_string(stack_->read_c_string()) : resolver::token_name(func_id);

    inst->data.emplace(inst->data.begin(), func_name);
    inst->data.emplace(inst->data.begin(), file_name);
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

            if (value < 0x100000 && value > 0)
            {
                inst->data.push_back("case");
                inst->data.push_back(utils::string::quote(decrypt_string(stack_->read_c_string()), false));
            }
            else if (value == 0)
            {
                inst->data.push_back("default");
                stack_->read_c_string(); // this should be always [0x01 0x00] unencrypted
            }
            else
            {
                inst->data.push_back("case");
                inst->data.push_back(utils::string::va("%i", (value - 0x800000) & 0xFFFFFF));
            }

            index += 4;

            const auto addr = disassemble_offset() + index;
            const auto label = utils::string::va("loc_%X", addr);

            inst->data.push_back(label);
            labels_.insert({ addr, label });

            index += 3;
            inst->size += 7;
        }
    }
}

void disassembler::disassemble_field_variable(const instruction::ptr& inst)
{
    const auto id = script_->read<std::uint32_t>();
    std::string name;

    if (id > max_string_id)
    {
        auto temp = stack_->read<std::uint32_t>();
        name = temp == 0 ? decrypt_string(stack_->read_c_string()) : std::to_string(temp);
    }
    else
    {
        name = resolver::token_name(id);
    }

    inst->data.push_back(name);
}

void disassembler::disassemble_formal_params(const instruction::ptr& inst)
{
    const auto count = script_->read<std::uint8_t>();

    inst->size += count;
    inst->data.push_back(utils::string::va("%i", count));

    for (auto i = 0u; i < count; i++)
    {
        inst->data.push_back(utils::string::va("%d", script_->read<std::uint8_t>()));
    }
}

void disassembler::disassemble_jump(const instruction::ptr& inst, bool expr, bool back)
{
    std::int32_t addr;

    if (expr)
    {
        addr = inst->index + 3 + script_->read<std::int16_t>();
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

auto disassembler::disassemble_offset() -> std::int32_t
{
    std::array<std::uint8_t, 4> bytes = {};

    for (auto i = 0; i < 3; i++)
    {
        bytes[i] = script_->read<std::uint8_t>();
    }

    auto offset = *reinterpret_cast<std::int32_t*>(bytes.data());

    offset = (offset << 8) >> 8;

    return offset;
}

void disassembler::resolve_local_functions()
{
    for (const auto& func : functions_)
    {
        for (const auto& inst : func->instructions)
        {
            /*switch (static_cast<opcode>(inst->opcode))
            {
            case opcode::OP_GetLocalFunction:
            case opcode::OP_ScriptLocalFunctionCall:
            case opcode::OP_ScriptLocalFunctionCall2:
            case opcode::OP_ScriptLocalMethodCall:
            case opcode::OP_ScriptLocalThreadCall:
            case opcode::OP_ScriptLocalChildThreadCall:
            case opcode::OP_ScriptLocalMethodThreadCall:
            case opcode::OP_ScriptLocalMethodChildThreadCall:
                inst->data[0] = resolve_function(inst->data[0]);
                break;
            default:
                break;
            }*/
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

auto disassembler::decrypt_string(const std::string& str) -> std::string
{
    if (str.size() > 0 && ((static_cast<std::uint8_t>(str[0]) & 0xC0) == 0x80))
    {
        std::string data = "_encstr_";

        for (auto i = 0u; i < str.size(); i++)
        {
            data = utils::string::va("%s%02X", data.data(), static_cast<std::uint8_t>(str[i]));
        }

        return data;
    }

    return str;
}

void disassembler::print_function(const function::ptr& func)
{
    output_->write_string("\n");
    output_->write_string(utils::string::va("sub_%s\n", func->name.data()));

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
    output_->write_string(utils::string::va("\t\t%s", resolver::opcode_name(inst->opcode).data()));

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
