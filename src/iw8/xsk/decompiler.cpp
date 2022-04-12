// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "iw8.hpp"

namespace xsk::gsc::iw8
{

auto decompiler::output() -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> output;

    auto data = std::make_unique<utils::byte_buffer>(0x100000);
    data->write_string("// IW8 GSC SOURCE\n");
    data->write_string("// Decompiled by https://github.com/xensik/gsc-tool\n");
    data->write_string(program_->print());

    output.resize(data->pos());
    std::memcpy(output.data(), data->buffer().data(), output.size());

    return output;
}

void decompiler::decompile(const std::string& file, std::vector<function::ptr>& funcs)
{
    filename_ = file;
    program_ = std::make_unique<ast::program>();

    for (const auto& func : funcs)
    {
        auto name = std::make_unique<ast::expr_identifier>(func->name);
        auto params = std::make_unique<ast::expr_parameters>();
        auto block = std::make_unique<ast::stmt_list>();
        func_ = std::make_unique<ast::decl_thread>(std::move(name), std::move(params), std::move(block));

        stack_ = std::stack<ast::node::ptr>();
        labels_ = func->labels;
        expr_labels_.clear();
        tern_labels_.clear();
        blocks_.clear();

        decompile_function(func);

        process_stack(func_);

        program_->declarations.push_back(ast::decl(std::move(func_)));
    }
}

void decompiler::decompile_function(const function::ptr& func)
{
    in_waittill_ = false;

    for (const auto& inst : func->instructions)
    {
        decompile_instruction(inst);
    }

    if (stack_.size() > 0)
    {
        throw decomp_error("stack isn't emty at function end");
    }

    const auto& stmt = func_->stmt;

    block blk;
    blk.loc_end = utils::string::va("loc_%X", stmt->list.back().as_node->loc().begin.line);

    // remove last return
    stmt->list.pop_back();

    // hotfix empty else block at func end
    if (stmt->list.size() > 0 && stmt->list.back() == ast::kind::asm_jump)
    {
        if (stmt->list.back().as_jump->value == blk.loc_end)
            stmt->list.pop_back();
    }

    blocks_.push_back(blk);

    decompile_statements(stmt);

    blocks_.pop_back();
}

void decompiler::decompile_instruction(const instruction::ptr& inst)
{
    decompile_expressions(inst);

    auto loc = location(&filename_, inst->index);

    switch (opcode(inst->opcode))
    {
        case opcode::OP_End:
        {
            auto expr = ast::expr(std::make_unique<ast::node>());
            auto stmt = ast::stmt(std::make_unique<ast::stmt_return>(loc, std::move(expr)));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_Return:
        {
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            auto stmt = ast::stmt(std::make_unique<ast::stmt_return>(expr.loc(), std::move(expr)));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_GetZero:
        {
            auto node = std::make_unique<ast::expr_integer>(loc, "0");
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetByte:
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetInteger:
        {
            auto node = std::make_unique<ast::expr_integer>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetNegByte:
        case opcode::OP_GetNegUnsignedShort:
        {
            auto node = std::make_unique<ast::expr_integer>(loc, "-" + inst->data[0]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetFloat:
        {
            auto node = std::make_unique<ast::expr_float>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetVector:
        {
            auto x = ast::expr(std::make_unique<ast::expr_float>(loc, inst->data[0]));
            auto y = ast::expr(std::make_unique<ast::expr_float>(loc, inst->data[1]));
            auto z = ast::expr(std::make_unique<ast::expr_float>(loc, inst->data[2]));
            auto node = std::make_unique<ast::expr_vector>(loc, std::move(x), std::move(y), std::move(z));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetString:
        {
            auto node = std::make_unique<ast::expr_string>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetIString:
        {
            auto node = std::make_unique<ast::expr_istring>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetUndefined:
        {
            auto node = std::make_unique<ast::expr_undefined>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EmptyArray:
        {
            auto node = std::make_unique<ast::expr_empty_array>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetLevel:
        case opcode::OP_GetLevelObject:
        {
            auto node = std::make_unique<ast::expr_level>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetAnim:
        case opcode::OP_GetAnimObject:
        {
            auto node = std::make_unique<ast::expr_anim>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetSelf:
        case opcode::OP_GetSelfObject:
        {
            auto node = std::make_unique<ast::expr_self>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetGame:
        case opcode::OP_GetGameRef:
        {
            auto node = std::make_unique<ast::expr_game>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetAnimation:
        {
            auto value = utils::string::unquote(inst->data[0]);

            if (value != "")
            {
                auto tree = std::make_unique<ast::expr_string>(loc, inst->data[0]);
                auto decl = std::make_unique<ast::decl_usingtree>(loc, std::move(tree));
                program_->declarations.push_back(ast::decl(std::move(decl)));
            }

            auto node = std::make_unique<ast::expr_animation>(loc, utils::string::unquote(inst->data[1]));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetAnimTree:
        {
            auto value = utils::string::unquote(inst->data[0]);

            if (value != "")
            {
                auto tree = std::make_unique<ast::expr_string>(loc, inst->data[0]);
                auto decl = std::make_unique<ast::decl_usingtree>(loc, std::move(tree));
                program_->declarations.push_back(ast::decl(std::move(decl)));
            }

            auto node = std::make_unique<ast::expr_animtree>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetThisthread:
        {
            auto node = std::make_unique<ast::expr_thisthread>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetBuiltinFunction:
        case opcode::OP_GetBuiltinMethod:
        {
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto node = std::make_unique<ast::expr_reference>(loc, std::move(path), std::move(name));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetLocalFunction:
        {
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto node = std::make_unique<ast::expr_reference>(loc, std::move(path), std::move(name));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetFarFunction:
        {
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);
            auto node = std::make_unique<ast::expr_reference>(loc, std::move(path), std::move(name));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CreateLocalVariable:
        {
            if (in_waittill_)
            {
                auto node = std::make_unique<ast::asm_create>(loc, inst->data[0]);
                stack_.push(std::move(node));
            }
            else
            {
                auto stmt = std::make_unique<ast::asm_create>(loc, inst->data[0]);
                func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
            }
        }
            break;
        case opcode::OP_RemoveLocalVariables:
        {
            auto stmt = std::make_unique<ast::asm_remove>(loc, inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_EvalLocalVariableCached0:
        {
            auto node = std::make_unique<ast::asm_access>(loc, "0");
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalVariableCached1:
        {
            auto node = std::make_unique<ast::asm_access>(loc, "1");
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalVariableCached2:
        {
            auto node = std::make_unique<ast::asm_access>(loc, "2");
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalVariableCached3:
        {
            auto node = std::make_unique<ast::asm_access>(loc, "3");
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalVariableCached4:
        {
            auto node = std::make_unique<ast::asm_access>(loc, "4");
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalVariableCached5:
        {
            auto node = std::make_unique<ast::asm_access>(loc, "5");
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalVariableCached:
        {
            auto node = std::make_unique<ast::asm_access>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalArrayCached:
        {
            auto key = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::make_unique<ast::asm_access>(loc, inst->data[0]));
            auto node = std::make_unique<ast::expr_array>(key.loc(), std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalArray:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto key = ast::expr(std::move(stack_.top())); stack_.pop();
            auto node = std::make_unique<ast::expr_array>(key.loc(), std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalNewLocalArrayRefCached0:
        {
            auto key = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::make_unique<ast::asm_create>(loc, inst->data[0]));
            auto node = std::make_unique<ast::expr_array>(key.loc(), std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalArrayRefCached0:
        {
            auto key = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::make_unique<ast::asm_access>(loc, "0"));
            auto node = std::make_unique<ast::expr_array>(key.loc(), std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalArrayRefCached:
        {
            auto key = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::make_unique<ast::asm_access>(loc, inst->data[0]));
            auto node = std::make_unique<ast::expr_array>(key.loc(), std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalArrayRef:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto key = ast::expr(std::move(stack_.top())); stack_.pop();
            auto node = std::make_unique<ast::expr_array>(key.loc(), std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ClearArray:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto key = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = key.loc();
            auto lvalue = ast::expr(std::make_unique<ast::expr_array>(loc, std::move(obj), std::move(key)));
            auto rvalue = ast::expr(std::make_unique<ast::expr_undefined>(loc));
            auto expr = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue)));
            auto stmt = ast::stmt(std::make_unique<ast::stmt_assign>(loc, std::move(expr)));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_AddArray:
        {
            auto value = ast::expr(std::move(stack_.top())); stack_.pop();
            auto array = std::move(stack_.top()); stack_.pop();

            if (array->kind() == ast::kind::expr_empty_array)
            {
                auto args = std::make_unique<ast::expr_arguments>(loc);
                args->list.push_back(std::move(value));
                auto expr = std::make_unique<ast::expr_add_array>(array->loc(), std::move(args));
                stack_.push(std::move(expr));
            }
            else if (array->kind() == ast::kind::expr_add_array)
            {
                (*(ast::expr_add_array::ptr*)&array)->args->list.push_back(std::move(value));
                stack_.push(std::move(array));
            }
            else
            {
                throw decomp_error("unknown add array type (could be an array variable name?)");
            }
        }
            break;
        case opcode::OP_PreScriptCall:
        {
            auto node = std::make_unique<ast::asm_prescriptcall>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptLocalFunctionCall2:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptLocalFunctionCall:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            auto var = std::move(stack_.top());
            stack_.pop();
            loc = var->loc();

            while (var->kind() != ast::kind::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc();
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptLocalMethodCall:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.loc();

            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ast::kind::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj) ,std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptLocalThreadCall:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = std::stoul(inst->data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::thread));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptLocalChildThreadCall:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = std::stoul(inst->data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::childthread));
            auto expr = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(expr));
        }
            break;
        case opcode::OP_ScriptLocalMethodThreadCall:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.loc();

            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = std::stoul(inst->data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::thread));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptLocalMethodChildThreadCall:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.loc();

            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = std::stoul(inst->data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::childthread));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptFarFunctionCall2:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);
            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptFarFunctionCall:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ast::kind::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptFarMethodCall:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ast::kind::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptFarThreadCall:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);

            for (auto i = std::stoul(inst->data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::thread));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptFarChildThreadCall:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);

            for (auto i = std::stoul(inst->data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::childthread));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptFarMethodThreadCall:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);

            for (auto i = std::stoul(inst->data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::thread));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptFarMethodChildThreadCall:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);

            for (auto i = std::stoul(inst->data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::childthread));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptFunctionCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ast::kind::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptMethodCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ast::kind::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptThreadCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = func.as_node->loc();

            for (auto i = std::stoul(inst->data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::thread));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptChildThreadCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = func.as_node->loc();

            for (auto i = std::stoul(inst->data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::childthread));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptMethodThreadCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

            for (auto i = std::stoul(inst->data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::thread));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptMethodChildThreadCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

            for (auto i = std::stoul(inst->data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::childthread));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = func.as_node->loc();

            for (auto i = std::stoul(inst->data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinMethodPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

            for (auto i = std::stoul(inst->data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltin0:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltin1:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 1u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltin2:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 2u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltin3:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 3u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltin4:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 4u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltin5:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 5u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltin:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = std::stoul(inst->data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto func = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(func));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinMethod0:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinMethod1:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 1u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj) ,std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinMethod2:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 2u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinMethod3:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 3u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj) ,std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinMethod4:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 4u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinMethod5:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);

            for (auto i = 5u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinMethod:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

            for (auto i = std::stoul(inst->data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::builtin));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj), std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_DecTop:
        {
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            auto stmt = std::make_unique<ast::stmt_call>(expr.loc(), std::move(expr));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_inc:
        {
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_increment>(loc, std::move(lvalue), false);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_dec:
        {
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_decrement>(loc, std::move(lvalue), false);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_bit_or:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_bitwise_or>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_bit_ex_or:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_bitwise_exor>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_bit_and:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_bitwise_and>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_equality:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_equality>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_inequality:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_inequality>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_less:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_less>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_greater:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_greater>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_less_equal:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_less_equal>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_greater_equal:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_greater_equal>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_shift_left:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_shift_left>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_shift_right:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_shift_right>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_plus:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_add>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_minus:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_sub>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_multiply:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_mul>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_divide:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_div>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_mod:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_mod>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_wait:
        {
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = expr.loc();
            auto stmt = ast::stmt(std::make_unique<ast::stmt_wait>(loc, std::move(expr)));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_waittillFrameEnd:
        {
            auto stmt = ast::stmt(std::make_unique<ast::stmt_waittillframeend>(loc));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_waitframe:
        {
            auto stmt = ast::stmt(std::make_unique<ast::stmt_waitframe>(loc));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_waittill:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto event = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = event.as_node->loc();
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto stmt = std::make_unique<ast::stmt_waittill>(loc, std::move(obj) , std::move(event), std::move(args));
            stack_.push(std::move(stmt));
            in_waittill_ = true;
        }
            break;
        case opcode::OP_waittillmatch:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = expr.as_node->loc();

            for (auto i = std::stoul(inst->data[0]); i > 0; i++)
            {
                auto node = std::move(stack_.top()); stack_.pop();
                loc = node->loc();
                args->list.push_back(std::move(node));
            }

            auto stmt = std::make_unique<ast::stmt_waittillmatch>(loc, std::move(obj), std::move(expr), std::move(args));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_clearparams:
        {
            if (in_waittill_)
            {
                auto args = std::make_unique<ast::expr_arguments>(loc);
                auto var = std::move(stack_.top());
                stack_.pop();

                while (var->kind() != ast::kind::stmt_waittill)
                {
                    args->list.push_back(std::move(var));
                    var = std::move(stack_.top()); stack_.pop();
                }

                if (var->kind() == ast::kind::stmt_waittill)
                {
                    std::reverse(args->list.begin(), args->list.end());
                    (*(ast::stmt_waittill::ptr*)&var)->args = std::move(args);
                    in_waittill_ = false;
                }

                func_->stmt->list.push_back(ast::stmt(std::move(var)));
            }
        }
            break;
        case opcode::OP_notify:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto event = ast::expr(std::move(stack_.top())); stack_.pop();
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ast::kind::asm_voidcodepos)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            auto stmt = std::make_unique<ast::stmt_notify>(loc, std::move(obj), std::move(event), std::move(args));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_endon:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto event = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = event.as_node->loc();
            auto stmt = std::make_unique<ast::stmt_endon>(loc, std::move(obj) , std::move(event));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_voidCodepos:
        {
            auto node = std::make_unique<ast::asm_voidcodepos>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_vector:
        {
            auto x = ast::expr(std::move(stack_.top())); stack_.pop();
            auto y = ast::expr(std::move(stack_.top())); stack_.pop();
            auto z = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = z.as_node->loc();
            auto node = std::make_unique<ast::expr_vector>(loc, std::move(x), std::move(y), std::move(z));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_size:
        {
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_size>(loc, std::move(lvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLevelFieldVariable:
        {
            auto obj = ast::expr(std::make_unique<ast::expr_level>(loc));
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto stmt = std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
            break;
        case opcode::OP_EvalAnimFieldVariable:
        {
            auto obj = ast::expr(std::make_unique<ast::expr_anim>(loc));
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto stmt = std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
            break;
        case opcode::OP_EvalSelfFieldVariable:
        {
            auto obj = ast::expr(std::make_unique<ast::expr_self>(loc));
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto stmt = std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
            break;
        case opcode::OP_EvalFieldVariable:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto stmt = std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
            break;
        case opcode::OP_EvalLevelFieldVariableRef:
        {
            auto obj = ast::expr(std::make_unique<ast::expr_level>(loc));
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto stmt = std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
            break;
        case opcode::OP_EvalAnimFieldVariableRef:
        {
            auto obj = ast::expr(std::make_unique<ast::expr_anim>(loc));
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto stmt = std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
            break;
        case opcode::OP_EvalSelfFieldVariableRef:
        {
            auto obj = ast::expr(std::make_unique<ast::expr_self>(loc));
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto stmt = std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
            break;
        case opcode::OP_EvalFieldVariableRef:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto stmt = std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
            break;
        case opcode::OP_ClearFieldVariable:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto expr = ast::expr(std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field)));
            auto undef = ast::expr(std::make_unique<ast::expr_undefined>(loc));
            auto e = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(expr), std::move(undef)));
            func_->stmt->list.push_back(ast::stmt(std::make_unique<ast::stmt_assign>(loc, std::move(e))));
        }
            break;
        case opcode::OP_SafeCreateVariableFieldCached:
        {
            func_->params->list.push_back(std::make_unique<ast::expr_identifier>(loc, "var_" + inst->data[0]));
        }
            break;
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        {
            if (stack_.top()->kind() != ast::kind::asm_create)
            {
                auto node = std::make_unique<ast::asm_access>(loc, inst->data[0]);
                stack_.push(std::move(node));
            }
        }
            break;
        case opcode::OP_SafeSetVariableFieldCached0:
        {
            func_->params->list.push_back(std::make_unique<ast::expr_identifier>(loc, "var_0"));
        }
            break;
        case opcode::OP_SafeSetVariableFieldCached:
        {
            func_->params->list.push_back(std::make_unique<ast::expr_identifier>(loc, "var_" + inst->data[0]));
        }
            break;
        case opcode::OP_EvalLocalVariableRefCached0:
        {
            auto node = std::make_unique<ast::asm_access>(loc, "0");
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_EvalLocalVariableRefCached:
        {
            auto node = std::make_unique<ast::asm_access>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_SetLevelFieldVariableField:
        {
            auto obj = ast::expr(std::make_unique<ast::expr_level>(loc));
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto lvalue = ast::expr(std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field)));
            auto rvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc();
            auto e = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue)));
            auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(e));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_SetVariableField:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();

            if (lvalue.as_node->kind() == ast::kind::expr_increment)
            {
                auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(lvalue));
                func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
            }
            else if (lvalue.as_node->kind() == ast::kind::expr_decrement)
            {
                auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(lvalue));
                func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
            }
            else
            {
                auto rvalue = ast::expr(std::move(stack_.top()));
                stack_.pop();
                loc = rvalue.as_node->loc();
                auto e = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue)));
                auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(e));
                func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
            }
        }
            break;
        case opcode::OP_SetAnimFieldVariableField:
        {
            auto obj = ast::expr(std::make_unique<ast::expr_anim>(loc));
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto lvalue = ast::expr(std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field)));
            auto rvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc();
            auto e = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue)));
            auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(e));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_SetSelfFieldVariableField:
        {
            auto obj = ast::expr(std::make_unique<ast::expr_self>(loc));
            auto field = std::make_unique<ast::expr_identifier>(loc, inst->data[0]);
            auto lvalue = ast::expr(std::make_unique<ast::expr_field>(loc, std::move(obj), std::move(field)));
            auto rvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc();
            auto e = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue)));
            auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(e));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_SetLocalVariableFieldCached0:
        {
            auto lvalue = ast::expr(std::make_unique<ast::asm_access>(loc, "0"));
            auto rvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc();
            auto e = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue)));
            auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(e));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_SetNewLocalVariableFieldCached0:
        {
            auto lvalue = ast::expr(std::make_unique<ast::asm_create>(loc, inst->data[0]));
            auto rvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc();

            if (func_->stmt->list.size() > 0)
            {
                std::vector<std::string> creates;

                while (func_->stmt->list.back().as_node->kind() == ast::kind::asm_create)
                {
                    auto& entry = func_->stmt->list.back();
                    if (loc.begin.line < entry.as_node->loc().begin.line)
                    {
                        creates.push_back(entry.as_asm_create->index);
                        func_->stmt->list.pop_back();
                        continue;
                    }
                    break;
                }

                std::reverse(creates.begin(), creates.end());
                lvalue.as_asm_create->vars = creates;
            }

            auto e = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue)));
            auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(e));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_SetLocalVariableFieldCached:
        {
            auto lvalue = ast::expr(std::make_unique<ast::asm_access>(loc, inst->data[0]));
            auto rvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc();
            auto e = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue)));
            auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(e));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_ClearLocalVariableFieldCached:
        {
            auto stmt = std::make_unique<ast::asm_clear>(loc, inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_ClearLocalVariableFieldCached0:
        {
            auto stmt = std::make_unique<ast::asm_clear>(loc,"0");
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_EvalLocalVariableObjectCached:
        {
            auto node = std::make_unique<ast::asm_access>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_BoolNot:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();
            auto expr = std::make_unique<ast::expr_not>(loc, std::move(lvalue));
            stack_.push(std::move(expr));
        }
            break;
        case opcode::OP_BoolComplement:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();
            auto expr = std::make_unique<ast::expr_complement>(loc, std::move(lvalue));
            stack_.push(std::move(expr));
        }
            break;
        case opcode::OP_switch:
        {
            auto expr = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = expr.as_node->loc();
            auto sw = std::make_unique<ast::asm_switch>(loc, std::move(expr), inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(sw)));
        }
            break;
        case opcode::OP_endswitch:
        {
            auto count = inst->data[0];
            inst->data.erase(inst->data.begin());
            auto data = inst->data;
            auto end = std::make_unique<ast::asm_endswitch>(loc, data, count);
            func_->stmt->list.push_back(ast::stmt(std::move(end)));
        }
            break;
        case opcode::OP_jump:
        {
            auto expr = std::make_unique<ast::asm_jump>(loc, inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(expr)));
            if (stack_.size() != 0) tern_labels_.push_back(inst->data[0]);
        }
            break;
        case opcode::OP_jumpback:
        {
            auto expr = std::make_unique<ast::asm_jump_back>(loc, inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(expr)));
        }
            break;
        case opcode::OP_JumpOnTrue:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();
            auto e_not = ast::expr(std::make_unique<ast::expr_not>(loc, std::move(lvalue)));
            auto expr = std::make_unique<ast::asm_jump_cond>(loc, std::move(e_not), inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(expr)));
        }
            break;
        case opcode::OP_JumpOnFalse:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();
            auto expr = std::make_unique<ast::asm_jump_cond>(loc, std::move(lvalue), inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(expr)));
        }
            break;
        case opcode::OP_JumpOnTrueExpr:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();
            auto expr = std::make_unique<ast::asm_jump_true_expr>(loc, std::move(lvalue), inst->data[0]);
            stack_.push(std::move(expr));
            expr_labels_.push_back(inst->data[0]);
        }
            break;
        case opcode::OP_JumpOnFalseExpr:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();
            auto expr = std::make_unique<ast::asm_jump_false_expr>(loc, std::move(lvalue), inst->data[0]);
            stack_.push(std::move(expr));
            expr_labels_.push_back(inst->data[0]);
        }
            break;
        case opcode::OP_FormalParams:
        {
            auto count = std::stoi(inst->data[0]);

            for (auto i = 1; i <= count; i++)
            {
                func_->params->list.push_back(std::make_unique<ast::expr_identifier>(loc, "var_" + inst->data[i]));
            }
        }
            break;
        case opcode::OP_IsDefined:
        {
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            auto node = std::make_unique<ast::expr_isdefined>(expr.loc(), std::move(expr));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_IsTrue:
        {
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            auto node = std::make_unique<ast::expr_istrue>(expr.loc(), std::move(expr));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_BoolNotAfterAnd:
        {
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            auto node = std::make_unique<ast::expr_not>(expr.loc(), std::move(expr));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_waittillmatch2:
        case opcode::OP_checkclearparams:
        case opcode::OP_CastFieldObject:
        case opcode::OP_CastBool:
            break;
     // case opcode::OP_ClearVariableField
     // case opcode::OP_EvalNewLocalVariableRefCached0
        default:
            throw decomp_error("unhandled opcode " + resolver::opcode_name(inst->opcode));
    }
}

void decompiler::decompile_expressions(const instruction::ptr& inst)
{
    const auto itr = labels_.find(inst->index);

    if (itr == labels_.end())
        return;

    for (auto& expr : expr_labels_)
    {
        if (expr == itr->second)
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto jump = std::move(stack_.top()); stack_.pop();
            auto loc = jump->loc();

            if (jump->kind() == ast::kind::asm_jump_true_expr)
            {
                auto lvalue = std::move((*(ast::asm_jump_true_expr::ptr*)&jump)->expr);
                auto node = std::make_unique<ast::expr_or>(loc, std::move(lvalue), std::move(rvalue));
                stack_.push(std::move(node));
            }
            else if (jump->kind() == ast::kind::asm_jump_false_expr)
            {
                auto lvalue = std::move((*(ast::asm_jump_false_expr::ptr*)&jump)->expr);
                auto node = std::make_unique<ast::expr_and>(loc, std::move(lvalue), std::move(rvalue));
                stack_.push(std::move(node));
            }
            else
            {
                throw decomp_error("TRIED TO DECOMPILE INVALID JUMP EXPR!");
            }
        }
    }

    for (auto& tern : tern_labels_)
    {
        if (tern == itr->second)
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();

            func_->stmt->list.pop_back();
            auto stmt = std::move(func_->stmt->list.back());
            func_->stmt->list.pop_back();

            if (stmt == ast::kind::asm_jump_cond)
            {
                auto loc = stmt.as_cond->loc();
                auto node = std::make_unique<ast::expr_ternary>(loc, std::move(stmt.as_cond->expr), std::move(lvalue), std::move(rvalue));
                stack_.push(std::move(node));
            }
            else
            {
                throw decomp_error("TRIED TO DECOMPILE INVALID TERNARY EXPR!");
            }
        }
    }
}

void decompiler::decompile_statements(const ast::stmt_list::ptr& stmt)
{
    decompile_infinites(stmt);
    decompile_loops(stmt);
    decompile_switches(stmt);
    decompile_ifelses(stmt);
    decompile_aborts(stmt);
}

void decompiler::decompile_infinites(const ast::stmt_list::ptr& stmt)
{
    for (auto i = stmt->list.size() - 1; i > 0; i--)
    {
        if (stmt->list.at(i) == ast::kind::asm_jump_back)
        {
            auto break_loc = last_location_index(stmt, i) ? blocks_.back().loc_end : stmt->list.at(i + 1).loc().label();
            auto start = find_location_index(stmt, stmt->list.at(i).as_jump_back->value);

            if (i > 0 && stmt->list.at(i - 1).as_node->kind() == ast::kind::asm_jump_cond)
            {
                continue;
            }
            else if (stmt->list.at(start).as_node->kind() != ast::kind::asm_jump_cond)
            {
                decompile_infinite(stmt, start, i);
                i = start;
            }
            else if (stmt->list.at(start).as_cond->value != break_loc)
            {
                decompile_infinite(stmt, start, i);
                i = start;
            }
        }
    }
}

void decompiler::decompile_loops(const ast::stmt_list::ptr& stmt)
{
    for (auto i = 0u; i < stmt->list.size(); i++)
    {
        auto& entry = stmt->list.at(i);

        if (entry == ast::kind::asm_jump_cond)
        {
            auto j = (entry.as_cond->value == blocks_.back().loc_end) ? (stmt->list.size() - 1) : (find_location_index(stmt, entry.as_cond->value) - 1);

            if (stmt->list.at(j) == ast::kind::asm_jump_back)
            {
                if (j == i + 1)
                {
                    decompile_dowhile(stmt, i, j);
                    i = 0;
                }
                else if (stmt->list.at(i).loc().label() == stmt->list.at(j).as_jump_back->value)
                {
                    decompile_loop(stmt, i, j);
                    i = 0;
                }
            }
        }
    }
}

void decompiler::decompile_switches(const ast::stmt_list::ptr& stmt)
{
    for (auto i = 0u; i < stmt->list.size(); i++)
    {
        if (stmt->list.at(i) == ast::kind::asm_switch)
        {
            decompile_switch(stmt, i);
        }
    }
}

void decompiler::decompile_ifelses(const ast::stmt_list::ptr& stmt)
{
    for (auto i = 0u; i < stmt->list.size(); i++)
    {
        auto& entry = stmt->list.at(i);

        if (entry == ast::kind::asm_jump_cond)
        {
            auto j = (entry.as_cond->value == blocks_.back().loc_end) ? (stmt->list.size() - 1) : (find_location_index(stmt, entry.as_cond->value) - 1);
            auto last_loc = blocks_.back().loc_end;

            if (stmt->list.at(j) == ast::kind::asm_jump)
            {
                // if block is a loop check break, continue
                if (stmt->list.at(j).as_jump->value == blocks_.back().loc_continue)
                {
                    // last if/else inside a loop still trigger this :(
                    decompile_if(stmt, i, j);
                }
                else if (stmt->list.at(j).as_jump->value == blocks_.back().loc_break)
                {
                    decompile_if(stmt, i, j);
                }
                else if (stmt->list.at(j).as_jump->value == blocks_.back().loc_end)
                {
                    decompile_ifelse(stmt, i, j);
                }
                else if (stmt->list.at(j).as_jump->value == entry.as_cond->value)
                {
                    decompile_if(stmt, i, j); // if block, have a last empty else inside
                }
                else
                {
                    decompile_ifelse(stmt, i, j); // TODO: if else block is empty, convert it to only if!
                }
            }
            else if (stmt->list.at(j) == ast::kind::stmt_return && stmt->list.at(j).as_return->expr == ast::kind::null)
            {
                if (blocks_.back().loc_break != "" || blocks_.back().loc_continue != "")
                {
                    decompile_if(stmt, i, j); // inside a loop cant be last
                }
                else if (j - i  == 1)
                {
                    decompile_if(stmt, i, j); // only one explicit return
                }
                else if (stmt->list.back().as_node->kind() != ast::kind::stmt_return)
                {
                    decompile_if(stmt, i, j); // block end is not a last return
                }
                else if (blocks_.back().is_last && stmt->list.back().as_node->kind() != ast::kind::stmt_return)
                {
                    decompile_if(stmt, i, j); // inside a last block but is not and inner last
                }
                else if (find_location_reference(stmt, j, stmt->list.size(), last_loc))
                {
                    decompile_if(stmt, i, j); // reference to func end after the if
                }
                else if (blocks_.size() > 1 && !blocks_.back().is_last)
                {
                    decompile_if(stmt, i, j); // fake last ifelse
                }
                else
                {
                    decompile_last_ifelse(stmt, i, j); // special case
                }
            }
            else
            {
                decompile_if(stmt, i, j);
            }
        }
    }
}

void decompiler::decompile_aborts(const ast::stmt_list::ptr& block)
{
    for (auto i = 0u; i < block->list.size(); i++)
    {
        if (block->list.at(i) == ast::kind::asm_jump)
        {
            auto loc = block->list.at(i).loc();
            auto jump_loc = block->list.at(i).as_jump->value;

            if (jump_loc == blocks_.back().loc_continue)
            {
                block->list.erase(block->list.begin() + i);
                auto stmt = ast::stmt(std::make_unique<ast::stmt_continue>(loc));
                block->list.insert(block->list.begin() + i, std::move(stmt));
            }
            else if (jump_loc == blocks_.back().loc_break)
            {
                block->list.erase(block->list.begin() + i);
                auto stmt = ast::stmt(std::make_unique<ast::stmt_break>(loc));
                block->list.insert(block->list.begin() + i, std::move(stmt));
            }
        }
    }
}

void decompiler::decompile_if(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block blk;
    blk.loc_end = stmt->list.at(begin).as_cond->value;
    blk.loc_break = blocks_.back().loc_break;
    blk.loc_continue = blocks_.back().loc_continue;

    auto loc = stmt->list.at(begin).loc();
    auto test = std::move(stmt->list.at(begin).as_cond->expr);

    stmt->list.erase(stmt->list.begin() + begin); // remove 'test'

    auto if_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end; i++)
    {
        if_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    blocks_.push_back(blk);
    decompile_statements(if_stmt);
    blocks_.pop_back();

    auto new_stmt = ast::stmt(std::make_unique<ast::stmt_if>(loc, std::move(test), ast::stmt(std::move(if_stmt))));
    stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
}

void decompiler::decompile_ifelse(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block if_blk;
    if_blk.loc_end = stmt->list.at(end).loc().label();
    if_blk.loc_break = blocks_.back().loc_break;
    if_blk.loc_continue = blocks_.back().loc_continue;

    auto loc = stmt->list.at(begin).loc();
    auto test = std::move(stmt->list.at(begin).as_cond->expr);

    stmt->list.erase(stmt->list.begin() + begin); // remove 'test'
    end--;

    auto if_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end; i++)
    {
        if_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    blocks_.push_back(if_blk);
    decompile_statements(if_stmt);
    blocks_.pop_back();

    auto end_loc = stmt->list.at(begin).as_jump->value;
    stmt->list.erase(stmt->list.begin() + begin); // remove 'jump'

    auto end_idx = (end_loc == blocks_.back().loc_end) ? stmt->list.size() : find_location_index(stmt, end_loc);

    block else_blk;
    else_blk.loc_end = end_loc;
    else_blk.loc_break = blocks_.back().loc_break;
    else_blk.loc_continue = blocks_.back().loc_continue;

    auto else_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end_idx; i++)
    {
        else_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    blocks_.push_back(else_blk);
    decompile_statements(else_stmt);
    blocks_.pop_back();

    auto new_stmt = ast::stmt(std::make_unique<ast::stmt_ifelse>(loc, std::move(test), ast::stmt(std::move(if_stmt)), ast::stmt(std::move(else_stmt))));
    stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
}

void decompiler::decompile_last_ifelse(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block if_blk;
    if_blk.is_last = true;

    auto if_end = find_location_index(stmt, stmt->list.at(begin).as_cond->value) - 1;
    if_blk.loc_end = stmt->list.at(if_end).loc().label();

    auto loc = stmt->list.at(begin).loc();
    auto test = std::move(stmt->list.at(begin).as_cond->expr);

    stmt->list.erase(stmt->list.begin() + begin); // remove 'test'
    end--;

    auto if_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end; i++)
    {
        if_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    stmt->list.erase(stmt->list.begin() + begin); // remove 'return'

    blocks_.push_back(if_blk);
    decompile_statements(if_stmt);
    blocks_.pop_back();

    if (begin == stmt->list.size())
    {
        auto new_stmt = ast::stmt(std::make_unique<ast::stmt_if>(loc, std::move(test), ast::stmt(std::move(if_stmt))));
        stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
    }
    else
    {
        block else_blk;
        else_blk.is_last = true;

        end = stmt->list.size() - 1;
        else_blk.loc_end = stmt->list.at(end).loc().label();

        auto else_stmt = std::make_unique<ast::stmt_list>(loc);

        for (auto i = begin; i < end; i++)
        {
            else_stmt->list.push_back(std::move(stmt->list[begin]));
            stmt->list.erase(stmt->list.begin() + begin);
        }

        stmt->list.erase(stmt->list.begin() + begin); // remove 'return'

        blocks_.push_back(else_blk);
        decompile_statements(else_stmt);
        blocks_.pop_back();

        auto new_stmt = ast::stmt(std::make_unique<ast::stmt_ifelse>(loc, std::move(test), ast::stmt(std::move(if_stmt)), ast::stmt(std::move(else_stmt))));
        stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
    }
}

void decompiler::decompile_infinite(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block blk;
    blk.loc_break = last_location_index(stmt, end) ? blocks_.back().loc_end : stmt->list.at(end + 1).loc().label();
    blk.loc_end = stmt->list.at(end).loc().label();
    blk.loc_continue = stmt->list.at(end).loc().label();

    auto loc = stmt->list.at(begin).loc();

    stmt->list.erase(stmt->list.begin() + end); // remove 'jumpback'

    auto for_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end; i++)
    {
        for_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    blocks_.push_back(blk);
    decompile_statements(for_stmt);
    blocks_.pop_back();

    auto init = ast::stmt(std::make_unique<ast::node>());
    auto test = ast::expr(std::make_unique<ast::node>());
    auto iter = ast::stmt(std::make_unique<ast::node>());
    auto new_stmt = ast::stmt(std::make_unique<ast::stmt_for>(loc, std::move(init), std::move(test), std::move(iter), ast::stmt(std::move(for_stmt))));
    stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
}

void decompiler::decompile_loop(const ast::stmt_list::ptr& block, std::size_t start, std::size_t end)
{
    auto& last = block->list.at(end - 1);

    if (last == ast::kind::stmt_assign)
    {
        if (last.as_assign->expr == ast::kind::expr_assign_equal)
        {
            auto& call = last.as_assign->expr.as_assign_equal->rvalue;

            if (call == ast::kind::expr_call && call.as_call->call == ast::kind::expr_function)
            {
                if (utils::string::to_lower(call.as_call->call.as_function->name->value) == "getnextarraykey")
                {
                    auto ref = block->list.at(start).loc().label();

                    if (!find_location_reference(block, 0, start, ref))
                    {
                        decompile_foreach(block, start, end);
                        return;
                    }
                }
            }
        }

        if (start > 0) // while at func start
        {
            auto index = 1;
            while (block->list.at(start - index) == ast::kind::asm_create)
            {
                if (start - index > 0)
                    index++;
                else
                    break;
            }

            if (block->list.at(start - index) == ast::kind::stmt_assign)
            {
                auto ref = block->list.at(end).loc().label();
                auto ref2 = block->list.at(start).loc().label();

                if (find_location_reference(block, start, end, ref))
                {
                    // continue is at jumpback, not post-expr
                    decompile_while(block, start, end);
                    return;
                }
                else if (find_location_reference(block, 0, start, ref2))
                {
                    // begin is at condition, not pre-expr
                    decompile_while(block, start, end);
                    return;
                }
                else
                {
                    decompile_for(block, start, end);
                    return;
                }
            }
        }
    }

    decompile_while(block, start, end);
}

void decompiler::decompile_while(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block blk;
    blk.loc_break = stmt->list.at(begin).as_cond->value;
    blk.loc_end = stmt->list.at(end).loc().label();
    blk.loc_continue = stmt->list.at(end).loc().label();

    auto loc = stmt->list.at(begin).loc();
    auto test = std::move(stmt->list.at(begin).as_cond->expr);

    stmt->list.erase(stmt->list.begin() + end); // remove 'jumpback'
    stmt->list.erase(stmt->list.begin() + begin); // remove 'test'
    end--;

    auto while_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end; i++)
    {
        while_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    blocks_.push_back(blk);
    decompile_statements(while_stmt);
    blocks_.pop_back();

    auto new_stmt = ast::stmt(std::make_unique<ast::stmt_while>(loc, std::move(test), ast::stmt(std::move(while_stmt))));
    stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
}

void decompiler::decompile_dowhile(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block blk;
    blk.loc_break = stmt->list.at(begin).as_cond->value;
    blk.loc_end = stmt->list.at(begin).loc().label();
    blk.loc_continue = stmt->list.at(begin).loc().label();

    auto test = std::move(stmt->list.at(begin).as_cond->expr);
    begin = find_location_index(stmt, stmt->list.at(end).as_jump_back->value);
    auto loc = stmt->list.at(begin).loc();

    end--;
    stmt->list.erase(stmt->list.begin() + end); // remove 'test'
    stmt->list.erase(stmt->list.begin() + end); // remove 'jumpback'

    auto while_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end; i++)
    {
        while_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    blocks_.push_back(blk);
    decompile_statements(while_stmt);
    blocks_.pop_back();

    auto new_stmt = ast::stmt(std::make_unique<ast::stmt_dowhile>(loc, std::move(test), ast::stmt(std::move(while_stmt))));
    stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
}

void decompiler::decompile_for(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block blk;
    blk.loc_break = stmt->list.at(begin).as_cond->value;
    blk.loc_end = stmt->list.at(end - 1).loc().label();
    blk.loc_continue = stmt->list.at(end - 1).loc().label();

    // remove var_create instructions
    std::vector<std::string> creates;
    while (stmt->list.at(begin - 1) == ast::kind::asm_create)
    {
        creates.push_back(stmt->list.at(begin - 1).as_asm_create->index);
        stmt->list.erase(stmt->list.begin() + begin - 1);
        begin--;
        end--;
    }

    std::reverse(creates.begin(), creates.end());

    auto loc = stmt->list.at(begin - 1).loc();
    auto test = std::move(stmt->list.at(begin).as_cond->expr);

    auto init = ast::stmt(std::make_unique<ast::stmt_list>());
    init.as_list->list.push_back(std::move(stmt->list.at(begin - 1)));
    init.as_list->is_expr = true;

    auto iter = ast::stmt(std::make_unique<ast::stmt_list>());
    iter.as_list->list.push_back(std::move(stmt->list.at(end - 1)));
    iter.as_list->is_expr = true;

    begin--; // move begin from 'test' to 'init'
    stmt->list.erase(stmt->list.begin() + begin); // remove 'init'
    stmt->list.erase(stmt->list.begin() + begin); // remove 'test'
    end -= 3; // move end to 'iter' ( minus 'init' & 'test' )
    stmt->list.erase(stmt->list.begin() + end); // remove 'iter'
    stmt->list.erase(stmt->list.begin() + end); // remove 'jumpback'

    auto for_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end; i++)
    {
        for_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    blocks_.push_back(blk);
    decompile_statements(for_stmt);
    blocks_.pop_back();

    auto new_stmt = ast::stmt(std::make_unique<ast::stmt_for>(loc, std::move(init), std::move(test), std::move(iter), ast::stmt(std::move(for_stmt))));
    new_stmt.as_for->vars = creates;
    stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
}

void decompiler::decompile_foreach(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block blk;
    blk.loc_break = stmt->list.at(begin).as_cond->value;
    blk.loc_end = stmt->list.at(end - 1).loc().label();
    blk.loc_continue = stmt->list.at(end - 1).loc().label();

    // remove var_create instructions
    std::vector<std::string> creates;
    while (stmt->list.at(begin - 1) == ast::kind::asm_create)
    {
        creates.push_back(stmt->list.at(begin - 1).as_asm_create->index);
        stmt->list.erase(stmt->list.begin() + begin - 1);
        begin--;
        end--;
    }

    std::reverse(creates.begin(), creates.end());

    auto loc = stmt->list.at(begin - 2).loc();

    auto init = ast::stmt(std::make_unique<ast::stmt_list>());
    init.as_list->list.push_back(std::move(stmt->list[begin-2]));
    init.as_list->list.push_back(std::move(stmt->list[begin-1]));
    auto stmt0 = std::move(stmt->list[begin+1]);

    begin -= 2; // move begin from 'test' to 'array'
    stmt->list.erase(stmt->list.begin() + begin); // remove 'array'
    stmt->list.erase(stmt->list.begin() + begin); // remove 'elem'
    stmt->list.erase(stmt->list.begin() + begin); // remove 'test'
    stmt->list.erase(stmt->list.begin() + begin); // remove 'set'
    end -= 5; // move end to 'iter' ( minus 'array', 'elem', 'test' & 'set' )
    stmt->list.erase(stmt->list.begin() + end); // remove 'iter'
    stmt->list.erase(stmt->list.begin() + end); // remove 'jumpback

    if (stmt->list.size() > end && stmt->list.at(end) == ast::kind::asm_clear)
    {
        stmt->list.erase(stmt->list.begin() + end); // remove temp var 'array'
    }

    auto use_key = true;

    if (stmt->list.size() > end && stmt->list.at(end) == ast::kind::asm_clear)
    {
        stmt->list.erase(stmt->list.begin() + end); // remove temp var 'key'
        use_key = false;
    }

    auto foreach_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end; i++)
    {
        foreach_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    blocks_.push_back(blk);
    decompile_statements(foreach_stmt);
    blocks_.pop_back();

    auto new_stmt = ast::stmt(std::make_unique<ast::stmt_foreach>(loc, ast::stmt(std::move(foreach_stmt)), use_key));
    new_stmt.as_foreach->vars = creates;
    new_stmt.as_foreach->pre_expr = std::move(init);
    new_stmt.as_foreach->stmt0 = std::move(stmt0);
    stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
}

void decompiler::decompile_switch(const ast::stmt_list::ptr& stmt, std::size_t start)
{
    block blk;
    blk.loc_continue = blocks_.back().loc_continue;
    blk.loc_end = stmt->list.at(start).as_asm_switch->value;

    auto loc = stmt->list.at(start).loc();
    auto test = std::move(stmt->list.at(start).as_asm_switch->expr);
    auto end_loc = stmt->list.at(start).as_asm_switch->value;
    auto end = find_location_index(stmt, end_loc);

    blk.loc_break = (end == stmt->list.size() - 1) ? blocks_.back().loc_end : stmt->list.at(end + 1).loc().label();

    // collect cases
    auto casenum = std::atol(stmt->list.at(end).as_asm_endswitch->count.data());
    auto data = stmt->list.at(end).as_asm_endswitch->data;
    auto idx = 0;

    for (auto i = 0; i < casenum; i++)
    {
        if (data.at(idx) == "case")
        {
            auto loc_str = data.at(idx + 2);
            auto loc_idx = find_location_index(stmt, loc_str);
            auto loc_pos = location(&filename_, std::stol(loc_str.substr(4), 0, 16));
            auto value = ast::expr(std::make_unique<ast::expr_string>(loc_pos, data.at(idx + 1)));
            auto list = std::make_unique<ast::stmt_list>(loc);
            list->is_case = true;
            auto case_stmt = ast::stmt(std::make_unique<ast::stmt_case>(loc_pos, std::move(value), std::move(list)));
            stmt->list.insert(stmt->list.begin() + loc_idx, std::move(case_stmt));
            idx += 3;
        }
        else if (data.at(idx) == "default")
        {
            auto loc_str = data.at(idx + 1);
            auto loc_idx = find_location_index(stmt, loc_str);
            auto loc_pos = location(&filename_, std::stol(loc_str.substr(4), 0, 16));
            auto list = std::make_unique<ast::stmt_list>(loc);
            list->is_case = true;
            auto def_stmt = ast::stmt(std::make_unique<ast::stmt_default>(loc_pos, std::move(list)));
            while (stmt->list.at(loc_idx) == ast::kind::stmt_case)
                loc_idx++;
            stmt->list.insert(stmt->list.begin() + loc_idx, std::move(def_stmt));
            idx += 2;
        }
    }

    end = find_location_index(stmt, end_loc) - 1; // update end;
    stmt->list.erase(stmt->list.begin() + start); // remove 'switch'
    stmt->list.erase(stmt->list.begin() + end); // remove 'endswitch'

    //decompile block
    auto sw_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = start; i < end; i++)
    {
        sw_stmt->list.push_back(std::move(stmt->list[start]));
        stmt->list.erase(stmt->list.begin() + start);
    }

    blocks_.push_back(blk);
    decompile_statements(sw_stmt);
    blocks_.pop_back();

    auto stmt_list = std::make_unique<ast::stmt_list>(loc);
    auto current_case = ast::stmt(std::make_unique<ast::node>());

    auto num = sw_stmt->list.size();
    for (auto i = 0u; i < num; i++)
    {
        auto& entry = sw_stmt->list[0];

        if (entry == ast::kind::stmt_case || entry == ast::kind::stmt_default)
        {
            if (current_case.kind() != ast::kind::null)
            {
                stmt_list->list.push_back(std::move(current_case));
            }

            current_case = std::move(sw_stmt->list[0]);
            sw_stmt->list.erase(sw_stmt->list.begin());
        }
        else
        {
            if (current_case.kind() != ast::kind::null)
            {
                if (current_case == ast::kind::stmt_case)
                {
                    current_case.as_case->stmt->list.push_back(std::move(sw_stmt->list[0]));
                    sw_stmt->list.erase(sw_stmt->list.begin());
                }
                else
                {
                    current_case.as_default->stmt->list.push_back(std::move(sw_stmt->list[0]));
                    sw_stmt->list.erase(sw_stmt->list.begin());
                }
            }
            else
            {
                decomp_error("missing case before stmt inside switch!");
            }
        }
    }

    if (current_case.kind() != ast::kind::null)
    {
        stmt_list->list.push_back(std::move(current_case));
    }

    auto new_stmt = ast::stmt(std::make_unique<ast::stmt_switch>(loc, std::move(test), std::move(stmt_list)));
    stmt->list.insert(stmt->list.begin() + start, std::move(new_stmt));
}

auto decompiler::find_location_reference(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end, const std::string& location) -> bool
{
    for (auto i = begin; i < end; i++)
    {
        const auto& entry = stmt->list.at(i);

        if (entry == ast::kind::asm_jump_cond && entry.as_cond->value == location)
        {
            return true;
        }
        else if (entry == ast::kind::asm_jump && entry.as_jump->value == location)
        {
            return true;
        }
    }

    return false;
}

auto decompiler::find_location_index(const ast::stmt_list::ptr& stmt, const std::string& location) -> std::size_t
{
    auto index = 0u;

    if (location == blocks_.back().loc_end)
        return stmt->list.size();

    for (auto& entry : stmt->list)
    {
        if (entry.loc().label() == location)
            return index;

        index++;
    }

    throw decomp_error("LOCATION NOT FOUND! (" + location + ")");
}

auto decompiler::last_location_index(const ast::stmt_list::ptr& stmt, std::size_t index) -> bool
{
    if (index == stmt->list.size() - 1)
        return true;

    return false;
}

void decompiler::process_stack(const ast::decl_thread::ptr& thread)
{
    auto blk = std::make_unique<block>();

    process_parameters(thread->params, blk);
    process_stmt_list(thread->stmt, blk);
}

void decompiler::process_parameters(const ast::expr_parameters::ptr& params, const block::ptr& blk)
{
    for (const auto& entry : params->list)
    {
        blk->local_vars.push_back({ entry->value, static_cast<uint8_t>(std::stoi(entry->value.substr(4))), true });
        blk->local_vars_create_count++;
    }
}

void decompiler::process_stmt(const ast::stmt& stmt, const block::ptr& blk)
{
    switch (stmt.kind())
    {
        case ast::kind::stmt_list:
            process_stmt_list(stmt.as_list, blk);
            break;
        case ast::kind::stmt_expr:
            process_stmt_expr(stmt.as_expr, blk);
            break;
        case ast::kind::stmt_call:
            process_stmt_call(stmt.as_call, blk);
            break;
        case ast::kind::stmt_assign:
            process_stmt_assign(stmt.as_assign, blk);
            break;
        case ast::kind::stmt_endon:
            process_stmt_endon(stmt.as_endon, blk);
            break;
        case ast::kind::stmt_notify:
            process_stmt_notify(stmt.as_notify, blk);
            break;
        case ast::kind::stmt_wait:
            process_stmt_wait(stmt.as_wait, blk);
            break;
        case ast::kind::stmt_waittill:
            process_stmt_waittill(stmt.as_waittill, blk);
            break;
        case ast::kind::stmt_waittillmatch:
            process_stmt_waittillmatch(stmt.as_waittillmatch, blk);
            break;
        case ast::kind::stmt_if:
            process_stmt_if(stmt.as_if, blk);
            break;
        case ast::kind::stmt_ifelse:
            process_stmt_ifelse(stmt.as_ifelse, blk);
            break;
        case ast::kind::stmt_while:
            process_stmt_while(stmt.as_while, blk);
            break;
        case ast::kind::stmt_dowhile:
            process_stmt_dowhile(stmt.as_dowhile, blk);
            break;
        case ast::kind::stmt_for:
            process_stmt_for(stmt.as_for, blk);
            break;
        case ast::kind::stmt_foreach:
            process_stmt_foreach(stmt.as_foreach, blk);
            break;
        case ast::kind::stmt_switch:
            process_stmt_switch(stmt.as_switch, blk);
            break;
        case ast::kind::stmt_break:
            process_stmt_break(stmt.as_break, blk);
            break;
        case ast::kind::stmt_continue:
            process_stmt_continue(stmt.as_continue, blk);
            break;
        case ast::kind::stmt_return:
            process_stmt_return(stmt.as_return, blk);
            break;
        case ast::kind::asm_remove:
            process_var_remove(stmt.as_asm_remove, blk);
            break;
        case ast::kind::asm_create:
        {
            auto expr = ast::expr(std::make_unique<ast::asm_create>(stmt.as_asm_create->index));
            process_var_create(expr, blk, true);
        }
            break;
        default:
            break;
    }
}

void decompiler::process_stmt_list(const ast::stmt_list::ptr& stmt, const block::ptr& blk)
{
    for (const auto& entry : stmt->list)
    {
        process_stmt(entry, blk);
    }

    auto i = 0u;

    while (i < stmt->list.size())
    {
        auto type = stmt->list.at(i).kind();

        if (type == ast::kind::asm_create || type == ast::kind::asm_remove)
        {
            stmt->list.erase(stmt->list.begin() + i);
            continue;
        }

        i++;
    }
}

void decompiler::process_stmt_expr(const ast::stmt_expr::ptr& stmt, const block::ptr& blk)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            process_expr_increment(stmt->expr.as_increment, blk);
            break;
        case ast::kind::expr_decrement:
            process_expr_decrement(stmt->expr.as_decrement, blk);
            break;
        case ast::kind::expr_assign_equal:
        case ast::kind::expr_assign_add:
        case ast::kind::expr_assign_sub:
        case ast::kind::expr_assign_mul:
        case ast::kind::expr_assign_div:
        case ast::kind::expr_assign_mod:
        case ast::kind::expr_assign_shift_left:
        case ast::kind::expr_assign_shift_right:
        case ast::kind::expr_assign_bitwise_or:
        case ast::kind::expr_assign_bitwise_and:
        case ast::kind::expr_assign_bitwise_exor:
            process_expr_assign(stmt->expr.as_assign, blk);
            break;
        default:
            break;
    }
}

void decompiler::process_stmt_call(const ast::stmt_call::ptr& stmt, const block::ptr& blk)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_call:
            process_expr_call(stmt->expr.as_call, blk);
            break;
        case ast::kind::expr_method:
            process_expr_method(stmt->expr.as_method, blk);
            break;
        default:
            break;
    }
}

void decompiler::process_stmt_assign(const ast::stmt_assign::ptr& stmt, const block::ptr& blk)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            process_expr_increment(stmt->expr.as_increment, blk);
            break;
        case ast::kind::expr_decrement:
            process_expr_decrement(stmt->expr.as_decrement, blk);
            break;
        case ast::kind::expr_assign_equal:
        case ast::kind::expr_assign_add:
        case ast::kind::expr_assign_sub:
        case ast::kind::expr_assign_mul:
        case ast::kind::expr_assign_div:
        case ast::kind::expr_assign_mod:
        case ast::kind::expr_assign_shift_left:
        case ast::kind::expr_assign_shift_right:
        case ast::kind::expr_assign_bitwise_or:
        case ast::kind::expr_assign_bitwise_and:
        case ast::kind::expr_assign_bitwise_exor:
            process_expr_assign(stmt->expr.as_assign, blk);
            break;
        default:
            break;
    }
}

void decompiler::process_stmt_endon(const ast::stmt_endon::ptr& stmt, const block::ptr& blk)
{
    process_expr(stmt->event, blk);
    process_expr(stmt->obj, blk);
}

void decompiler::process_stmt_notify(const ast::stmt_notify::ptr& stmt, const block::ptr& blk)
{
    process_expr_arguments(stmt->args, blk);
    process_expr(stmt->event, blk);
    process_expr(stmt->obj, blk);
}

void decompiler::process_stmt_wait(const ast::stmt_wait::ptr& stmt, const block::ptr& blk)
{
    process_expr(stmt->time, blk);
}

void decompiler::process_stmt_waittill(const ast::stmt_waittill::ptr& stmt, const block::ptr& blk)
{
    process_expr(stmt->event ,blk);
    process_expr(stmt->obj, blk);

    for (auto& entry : stmt->args->list)
    {
        process_expr(entry, blk);
    }
}

void decompiler::process_stmt_waittillmatch(const ast::stmt_waittillmatch::ptr& stmt, const block::ptr& blk)
{
    process_expr_arguments(stmt->args, blk);
    process_expr(stmt->event, blk);
    process_expr(stmt->obj, blk);
}

void decompiler::process_stmt_if(const ast::stmt_if::ptr& stmt, const block::ptr& blk)
{
    process_expr(stmt->test, blk);

    stmt->blk = std::make_unique<block>();
    blk->transfer_decompiler(stmt->blk);

    process_stmt(stmt->stmt, stmt->blk);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list.at(0).as_node->is_special_stmt())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }
}

void decompiler::process_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt, const block::ptr& blk)
{
    std::vector<block*> childs;
    auto abort = abort_t::abort_return;

    process_expr(stmt->test, blk);

    stmt->blk_if = std::make_unique<block>();
    blk->transfer_decompiler(stmt->blk_if);

    process_stmt(stmt->stmt_if, stmt->blk_if);

    if (stmt->blk_if->abort <= abort_t::abort_return)
    {
        abort = stmt->blk_if->abort;

        if (abort == abort_t::abort_none)
            childs.push_back(stmt->blk_if.get());
    }

    stmt->blk_else = std::make_unique<block>();
    blk->transfer_decompiler(stmt->blk_else);

    process_stmt(stmt->stmt_else, stmt->blk_else);

    if (stmt->blk_else->abort <= abort)
    {
        abort = stmt->blk_else->abort;

        if (abort == abort_t::abort_none)
            childs.push_back(stmt->blk_else.get());
    }

    if (blk->abort == abort_t::abort_none)
        blk->abort = abort;

    blk->append(childs);

    if (stmt->stmt_if.as_list->list.size() == 1 && !stmt->stmt_if.as_list->list.at(0).as_node->is_special_stmt())
    {
        stmt->stmt_if = std::move(stmt->stmt_if.as_list->list.back());
    }

    if (stmt->stmt_else.as_list->list.size() == 1 && !stmt->stmt_else.as_list->list.at(0).as_node->is_special_stmt_noif())
    {
        stmt->stmt_else = std::move(stmt->stmt_else.as_list->list.back());
    }
}

void decompiler::process_stmt_while(const ast::stmt_while::ptr& stmt, const block::ptr& blk)
{
    process_expr(stmt->test, blk);

    stmt->blk = std::make_unique<block>();
    blk->transfer_decompiler(stmt->blk);

    process_stmt(stmt->stmt, stmt->blk);

    std::vector<block*> childs({ stmt->blk.get() });

    if (stmt->test.as_node->kind() == ast::kind::null)
        blk->append_decompiler(stmt->blk);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list.at(0).as_node->is_special_stmt())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }
}

void decompiler::process_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt, const block::ptr& blk)
{
    process_expr(stmt->test, blk);

    stmt->blk = std::make_unique<block>();
    blk->transfer_decompiler(stmt->blk);

    process_stmt(stmt->stmt, stmt->blk);

    std::vector<block*> childs({ stmt->blk.get() });

    if (stmt->test.as_node->kind() == ast::kind::null)
        blk->append_decompiler(stmt->blk);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list.at(0).as_node->is_special_stmt())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }
}

void decompiler::process_stmt_for(const ast::stmt_for::ptr& stmt, const block::ptr& blk)
{
    process_stmt(stmt->init, blk);

    for (auto& index : stmt->vars)
    {
        auto var = utils::string::va("var_%d", std::stoi(index));
        blk->local_vars.push_back({ var, static_cast<uint8_t>(std::stoi(index)), true });
        blk->local_vars_create_count++;
    }

    stmt->blk = std::make_unique<block>();
    blk->transfer_decompiler(stmt->blk);

    process_expr(stmt->test, blk);

    process_stmt(stmt->stmt, stmt->blk);

    process_stmt(stmt->iter, blk);

    if (stmt->test == ast::kind::null)
        blk->append_decompiler(stmt->blk);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list.at(0).as_node->is_special_stmt())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }
}

void decompiler::process_stmt_foreach(const ast::stmt_foreach::ptr& stmt, const block::ptr& blk)
{
    process_stmt(stmt->pre_expr, blk);

    for (auto& index : stmt->vars)
    {
        auto var1 = utils::string::va("var_%d", std::stoi(index));
        blk->local_vars.push_back({ var1, static_cast<uint8_t>(std::stoi(index)), true });
        blk->local_vars_create_count++;
    }

    stmt->ctx = std::make_unique<block>();
    blk->transfer_decompiler(stmt->ctx);

    process_stmt(stmt->stmt0, stmt->ctx);
    process_stmt(stmt->stmt, stmt->ctx);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list.at(0).as_node->is_special_stmt())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }

    stmt->array_expr = std::move(stmt->pre_expr.as_list->list[0].as_assign->expr.as_assign->rvalue);
    stmt->value_expr = std::move(stmt->stmt0.as_assign->expr.as_assign->lvalue);
    stmt->key_expr = std::move(stmt->pre_expr.as_list->list[1].as_assign->expr.as_assign->lvalue);
}

void decompiler::process_stmt_switch(const ast::stmt_switch::ptr& stmt, const block::ptr& blk)
{
    process_expr(stmt->test, blk);

    stmt->ctx = std::make_unique<block>();
    blk->transfer_decompiler(stmt->ctx);

    process_stmt_cases(stmt->stmt, stmt->ctx);

    blk->append_decompiler(stmt->ctx, true);
}

void decompiler::process_stmt_cases(const ast::stmt_list::ptr& stmt, const block::ptr& blk)
{
    std::vector<block*> childs;
    bool has_default = false;

    for (auto& entry : stmt->list)
    {
        if (entry == ast::kind::stmt_case)
        {
            entry.as_case->blk = std::make_unique<block>();
            blk->transfer_decompiler(entry.as_case->blk);

            process_stmt_list(entry.as_case->stmt, entry.as_case->blk);

            if (entry.as_case->blk->abort == abort_t::abort_break)
            {
                childs.push_back(entry.as_case->blk.get());
            }
        }
        else if (entry == ast::kind::stmt_default)
        {
            has_default = true;
            entry.as_default->blk = std::make_unique<block>();
            blk->transfer_decompiler(entry.as_default->blk);

            process_stmt_list(entry.as_default->stmt, entry.as_default->blk);

            if (entry.as_default->blk->abort == abort_t::abort_break)
            {
                childs.push_back(entry.as_default->blk.get());
            }
        }
    }

    if (has_default)
    {
        blk->append(childs);
    }
}

void decompiler::process_stmt_break(const ast::stmt_break::ptr&, const block::ptr& blk)
{
    if (blk->abort == abort_t::abort_none)
    {
        blk->abort = abort_t::abort_break;
    }
}

void decompiler::process_stmt_continue(const ast::stmt_continue::ptr&, const block::ptr& blk)
{
    if (blk->abort == abort_t::abort_none)
    {
        blk->abort = abort_t::abort_continue;
    }
}

void decompiler::process_stmt_return(const ast::stmt_return::ptr& stmt, const block::ptr& blk)
{
    if (blk->abort == abort_t::abort_none)
    {
        blk->abort = abort_t::abort_return;
    }

    if (stmt->expr != ast::kind::null)
    {
        process_expr(stmt->expr, blk);
    }
}

void decompiler::process_expr(ast::expr& expr, const block::ptr& blk)
{
    switch (expr.kind())
    {
        case ast::kind::expr_ternary:
            process_expr_ternary(expr.as_ternary, blk);
            break;
        case ast::kind::expr_and:
            process_expr_and(expr.as_and, blk);
            break;
        case ast::kind::expr_or:
            process_expr_or(expr.as_or, blk);
            break;
        case ast::kind::expr_equality:
        case ast::kind::expr_inequality:
        case ast::kind::expr_less:
        case ast::kind::expr_greater:
        case ast::kind::expr_less_equal:
        case ast::kind::expr_greater_equal:
        case ast::kind::expr_bitwise_or:
        case ast::kind::expr_bitwise_and:
        case ast::kind::expr_bitwise_exor:
        case ast::kind::expr_shift_left:
        case ast::kind::expr_shift_right:
        case ast::kind::expr_add:
        case ast::kind::expr_sub:
        case ast::kind::expr_mul:
        case ast::kind::expr_div:
        case ast::kind::expr_mod:
            process_expr_binary(expr.as_binary, blk);
            break;
        case ast::kind::expr_complement:
            process_expr_complement(expr.as_complement, blk);
            break;
        case ast::kind::expr_not:
            process_expr_not(expr.as_not, blk);
            break;
        case ast::kind::expr_call:
            process_expr_call(expr.as_call, blk);
            break;
        case ast::kind::expr_method:
            process_expr_method(expr.as_method, blk);
            break;
        case ast::kind::expr_isdefined:
            process_expr(expr.as_isdefined->expr, blk);
            break;
        case ast::kind::expr_istrue:
            process_expr(expr.as_istrue->expr, blk);
            break;
        case ast::kind::expr_add_array:
            process_expr_add_array(expr.as_add_array, blk);
            break;
        case ast::kind::expr_array:
            process_array_variable(expr.as_array, blk);
            break;
        case ast::kind::expr_field:
            process_field_variable(expr.as_field, blk);
            break;
        case ast::kind::expr_size:
            process_expr_size(expr.as_size, blk);
            break;
        case ast::kind::expr_identifier:
            process_local_variable(expr.as_identifier, blk);
            break;
        case ast::kind::expr_vector:
            process_expr_vector(expr.as_vector, blk);
            break;
        case ast::kind::asm_create:
            process_var_create(expr, blk);
            break;
        case ast::kind::asm_access:
            process_var_access(expr, blk);
            break;
        default:
            break;
    }
}

void decompiler::process_expr_assign(ast::expr_assign::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->rvalue, blk);
    process_expr(expr->lvalue, blk);

    if (expr->kind() == ast::kind::expr_assign_equal)
    {
        switch (expr->rvalue.kind())
        {
            case ast::kind::expr_bitwise_or:
                if (expr->lvalue == expr->rvalue.as_bitwise_or->lvalue)
                    expr = std::make_unique<ast::expr_assign_bitwise_or>(std::move(expr->lvalue), std::move(expr->rvalue.as_bitwise_or->rvalue));
                break;
            case ast::kind::expr_bitwise_and:
                if (expr->lvalue == expr->rvalue.as_bitwise_and->lvalue)
                    expr = std::make_unique<ast::expr_assign_bitwise_and>(std::move(expr->lvalue), std::move(expr->rvalue.as_bitwise_and->rvalue));
                break;
            case ast::kind::expr_bitwise_exor:
                if (expr->lvalue == expr->rvalue.as_bitwise_exor->lvalue)
                    expr = std::make_unique<ast::expr_assign_bitwise_exor>(std::move(expr->lvalue), std::move(expr->rvalue.as_bitwise_exor->rvalue));
                break;
            case ast::kind::expr_shift_left:
                if (expr->lvalue == expr->rvalue.as_shift_left->lvalue)
                    expr = std::make_unique<ast::expr_assign_shift_left>(std::move(expr->lvalue), std::move(expr->rvalue.as_shift_left->rvalue));
                break;
            case ast::kind::expr_shift_right:
                if (expr->lvalue == expr->rvalue.as_shift_right->lvalue)
                    expr = std::make_unique<ast::expr_assign_shift_right>(std::move(expr->lvalue), std::move(expr->rvalue.as_shift_right->rvalue));
                break;
            case ast::kind::expr_add:
                if (expr->lvalue == expr->rvalue.as_add->lvalue)
                    expr = std::make_unique<ast::expr_assign_add>(std::move(expr->lvalue), std::move(expr->rvalue.as_add->rvalue));
                break;
            case ast::kind::expr_sub:
                if (expr->lvalue == expr->rvalue.as_sub->lvalue)
                    expr = std::make_unique<ast::expr_assign_sub>(std::move(expr->lvalue), std::move(expr->rvalue.as_sub->rvalue));
                break;
            case ast::kind::expr_mul:
                if (expr->lvalue == expr->rvalue.as_mul->lvalue)
                    expr = std::make_unique<ast::expr_assign_mul>(std::move(expr->lvalue), std::move(expr->rvalue.as_mul->rvalue));
                break;
            case ast::kind::expr_div:
                if (expr->lvalue == expr->rvalue.as_div->lvalue)
                    expr = std::make_unique<ast::expr_assign_div>(std::move(expr->lvalue), std::move(expr->rvalue.as_div->rvalue));
                break;
            case ast::kind::expr_mod:
                if (expr->lvalue == expr->rvalue.as_mod->lvalue)
                    expr = std::make_unique<ast::expr_assign_mod>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                break;
            default:
                break;
        }
    }
}

void decompiler::process_expr_increment(const ast::expr_increment::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->lvalue, blk);
}

void decompiler::process_expr_decrement(const ast::expr_decrement::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->lvalue, blk);
}

void decompiler::process_expr_ternary(const ast::expr_ternary::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->test, blk);
    process_expr(expr->true_expr, blk);
    process_expr(expr->false_expr, blk);
}

void decompiler::process_expr_binary(const ast::expr_binary::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->lvalue, blk);
    process_expr(expr->rvalue, blk);

    auto prec = expr->lvalue.as_node->precedence();

    if (prec && prec < expr->precedence())
    {
        expr->lvalue = ast::expr(std::make_unique<ast::expr_paren>(std::move(expr->lvalue)));
    }

    prec = expr->rvalue.as_node->precedence();

    if ((prec && prec < expr->precedence()) || (prec == expr->precedence() && expr->kind() == expr->rvalue.as_node->kind()))
    {
        expr->rvalue = ast::expr(std::make_unique<ast::expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_and(const ast::expr_and::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->lvalue, blk);
    process_expr(expr->rvalue, blk);

    auto prec = expr->lvalue.as_node->precedence();

    if (prec && prec < expr->precedence())
    {
        expr->lvalue = ast::expr(std::make_unique<ast::expr_paren>(std::move(expr->lvalue)));
    }

    prec = expr->rvalue.as_node->precedence();

    if ((prec && prec < expr->precedence()) || (prec == expr->precedence() && expr->kind() == expr->rvalue.kind()))
    {
        expr->rvalue = ast::expr(std::make_unique<ast::expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_or(const ast::expr_or::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->lvalue, blk);
    process_expr(expr->rvalue, blk);
}

void decompiler::process_expr_complement(const ast::expr_complement::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->rvalue, blk);

    if (expr->rvalue.as_node->is_binary())
    {
        expr->rvalue = ast::expr(std::make_unique<ast::expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_not(const ast::expr_not::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->rvalue, blk);

    if (expr->rvalue.as_node->is_binary())
    {
        expr->rvalue = ast::expr(std::make_unique<ast::expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_call(const ast::expr_call::ptr& expr, const block::ptr& blk)
{
    switch (expr->call.kind())
    {
        case ast::kind::expr_pointer:
            process_expr_call_pointer(expr->call.as_pointer, blk);
            break;
        case ast::kind::expr_function:
            process_expr_call_function(expr->call.as_function, blk);
            break;
        default:
            break;
    }
}

void decompiler::process_expr_method(const ast::expr_method::ptr& expr, const block::ptr& blk)
{
    switch (expr->call.kind())
    {
        case ast::kind::expr_pointer:
            process_expr_method_pointer(expr->call.as_pointer, expr->obj, blk);
            break;
        case ast::kind::expr_function:
            process_expr_method_function(expr->call.as_function, expr->obj, blk);
            break;
        default:
            break;
    }
}

void decompiler::process_expr_call_pointer(const ast::expr_pointer::ptr& expr, const block::ptr& blk)
{
    process_expr_arguments(expr->args, blk);
    process_expr(expr->func, blk);
}

void decompiler::process_expr_call_function(const ast::expr_function::ptr& expr, const block::ptr& blk)
{
    process_expr_arguments(expr->args, blk);
}

void decompiler::process_expr_method_pointer(const ast::expr_pointer::ptr& expr, ast::expr& obj, const block::ptr& blk)
{
    process_expr_arguments(expr->args, blk);
    process_expr(obj, blk);
    process_expr(expr->func, blk);
}

void decompiler::process_expr_method_function(const ast::expr_function::ptr& expr, ast::expr& obj, const block::ptr& blk)
{
    process_expr_arguments(expr->args, blk);
    process_expr(obj, blk);
}

void decompiler::process_expr_arguments(const ast::expr_arguments::ptr& expr, const block::ptr& blk)
{
    for (auto i = expr->list.size(); i > 0; i--)
    {
        process_expr(expr->list.at(i - 1), blk);
    }
}

void decompiler::process_expr_add_array(const ast::expr_add_array::ptr& expr, const block::ptr& blk)
{
    for (auto& entry : expr->args->list)
    {
        process_expr(entry, blk);
    }
}

void decompiler::process_expr_size(const ast::expr_size::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->obj, blk);
}

void decompiler::process_array_variable(const ast::expr_array::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->key, blk);
    process_expr(expr->obj, blk);
}

void decompiler::process_field_variable(const ast::expr_field::ptr& expr, const block::ptr& blk)
{
    process_expr(expr->obj, blk);
}

void decompiler::process_local_variable(const ast::expr_identifier::ptr&, const block::ptr&)
{
    return;
}

void decompiler::process_expr_vector(const ast::expr_vector::ptr& vec, const block::ptr& blk)
{
    process_expr(vec->z, blk);
    process_expr(vec->y, blk);
    process_expr(vec->x, blk);
}

void decompiler::process_var_create(ast::expr& expr, const block::ptr& blk, bool fromstmt)
{
    if (fromstmt)
    {
        auto var = utils::string::va("var_%d", std::stoi(expr.as_asm_create->index));
        blk->local_vars.push_back({ var, static_cast<uint8_t>(std::stoi(expr.as_asm_create->index)), true });
        blk->local_vars_create_count++;
    }
    else
    {
        for (auto& entry : expr.as_asm_create->vars)
        {
            blk->local_vars.push_back({ utils::string::va("var_%d", std::stoi(entry)), static_cast<uint8_t>(std::stoi(entry)), true });
            blk->local_vars_create_count++;
        }

        auto var = utils::string::va("var_%d", std::stoi(expr.as_asm_create->index));
        blk->local_vars.push_back({ var, static_cast<uint8_t>(std::stoi(expr.as_asm_create->index)), true });
        blk->local_vars_create_count++;

        expr = ast::expr(std::make_unique<ast::expr_identifier>(var));
    }
}

void decompiler::process_var_access(ast::expr& expr, const block::ptr& blk)
{
    if (blk->local_vars.size() <= std::stoul(expr.as_asm_access->index))
    {
        printf("WARNING: bad local var access\n");
    }
    else
    {
        auto var = blk->local_vars.at(blk->local_vars.size() - 1 - std::stoi(expr.as_asm_access->index)).name;
        expr = ast::expr(std::make_unique<ast::expr_identifier>(var));
    }
}

void decompiler::process_var_remove(const ast::asm_remove::ptr& expr, const block::ptr& blk)
{
    blk->local_vars_public_count = static_cast<std::uint32_t>(blk->local_vars.size() - std::stoi(expr->index));
}

} // namespace xsk::gsc::iw8
