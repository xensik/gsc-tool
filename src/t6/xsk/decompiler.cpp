// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "t6.hpp"

namespace xsk::arc::t6
{

auto decompiler::output() -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> output;

    auto data = std::make_unique<utils::byte_buffer>(0x100000);
    data->write_string("// T6 GSC SOURCE\n");
    data->write_string("// Decompiled by https://github.com/xensik/gsc-tool\n");
    data->write_string(program_->print());

    output.resize(data->pos());
    std::memcpy(output.data(), data->buffer().data(), output.size());

    return output;
}

void decompiler::decompile(const std::string& file, const assembly::ptr& data)
{
    filename_ = file;
    program_ = std::make_unique<ast::program>();

    std::reverse(data->includes.begin(), data->includes.end());

    for (const auto& inc : data->includes)
    {
        auto include = std::make_unique<ast::include>(std::make_unique<ast::expr_path>(inc));
        program_->includes.push_back(std::move(include));
    }

    for (const auto& func : data->functions)
    {
        auto name = std::make_unique<ast::expr_identifier>(func->name);
        auto params = std::make_unique<ast::expr_parameters>();
        auto block = std::make_unique<ast::stmt_list>();
        func_ = std::make_unique<ast::decl_thread>(std::move(name), std::move(params), std::move(block));

        stack_ = std::stack<ast::node::ptr>();
        labels_ = func->labels;
        expr_labels_.clear();
        tern_labels_.clear();
        locals_.clear();
        blocks_.clear();

        decompile_function(func);

        for (auto i = 0; i < func->params; i++)
        {
            func_->params->list.push_back(std::make_unique<ast::expr_identifier>(locals_.at(locals_.size() - 1 - i)));
        }

        process_thread(func_);

        program_->declarations.push_back(ast::decl(std::move(func_)));
    }
}

void decompiler::decompile_function(const function::ptr& func)
{
    in_waittill_ = false;
    retbool_ = true;
    retnum_ = 0;

    for (const auto& inst : func->instructions)
    {
        decompile_instruction(inst, &inst == &func->instructions.back());
    }

    if (stack_.size() > 0)
    {
        throw decomp_error("stack isn't emty at function end " + func->name);
    }

    const auto& stmt = func_->stmt;

    block blk;
    blk.loc_end = utils::string::va("loc_%X", stmt->list.back().as_node->loc().begin.line + 1);

    blocks_.push_back(blk);
    decompile_statements(stmt);
    blocks_.pop_back();

    if (stmt->list.size() > 0 && stmt->list.back() == ast::kind::stmt_return)
    {
        if (stmt->list.back().as_return->expr == ast::kind::null)
            stmt->list.pop_back();
    }
}

void decompiler::decompile_instruction(const instruction::ptr& inst, bool last)
{
    decompile_expressions(inst);

    auto loc = location(&filename_, inst->index);

    switch (opcode(inst->opcode))
    {
        case opcode::OP_End:
        {
            if (!last)
            {
                retnum_++;
                retbool_ = false;
            }

            auto expr = ast::expr(std::make_unique<ast::node>());
            auto stmt = ast::stmt(std::make_unique<ast::stmt_return>(loc, std::move(expr)));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_Return:
        {
            retnum_++;
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();

            if (expr != ast::kind::expr_integer || (expr.as_integer->value != "1" && expr.as_integer->value != "0"))
            {
                retbool_ = false;
            }

            auto stmt = ast::stmt(std::make_unique<ast::stmt_return>(expr.loc(), std::move(expr)));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_GetUndefined:
        {
            auto node = std::make_unique<ast::expr_undefined>(loc);
            stack_.push(std::move(node));
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
        case opcode::OP_GetVector:
        {
            auto x = ast::expr(std::make_unique<ast::expr_float>(loc, inst->data[0]));
            auto y = ast::expr(std::make_unique<ast::expr_float>(loc, inst->data[1]));
            auto z = ast::expr(std::make_unique<ast::expr_float>(loc, inst->data[2]));
            auto node = std::make_unique<ast::expr_vector>(loc, std::move(x), std::move(y), std::move(z));
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
            bool found = false;

            for (const auto& entry : program_->declarations)
            {
                if (entry == ast::kind::decl_usingtree)
                {
                    if (entry.as_usingtree->name->value == inst->data[0])
                        found = true;
                    else
                        found = false;
                }
            }

            if (!found)
            {
                auto tree = std::make_unique<ast::expr_string>(loc, inst->data[0]);
                auto decl = std::make_unique<ast::decl_usingtree>(loc, std::move(tree));
                program_->declarations.push_back(ast::decl(std::move(decl)));
            }

            auto node = std::make_unique<ast::expr_animation>(loc, inst->data[1]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetFunction:
        {
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);
            auto node = std::make_unique<ast::expr_reference>(loc, std::move(path), std::move(name));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CreateLocalVariable:
            throw decomp_error("unhandled opcode " + resolver::opcode_name(inst->opcode));
            break;
        case opcode::OP_SafeCreateLocalVariables:
        {
            for (const auto& entry : inst->data)
            {
                locals_.insert(locals_.begin(), entry);
            }
        }
            break;
        case opcode::OP_RemoveLocalVariables:
            throw decomp_error("unhandled opcode " + resolver::opcode_name(inst->opcode));
            break;
        case opcode::OP_EvalLocalVariableCached:
        {
            auto node = std::make_unique<ast::expr_identifier>(loc, locals_.at(std::stoi(inst->data[0])));
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
        case opcode::OP_EvalLocalArrayRefCached:
        {
            auto key = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::make_unique<ast::expr_identifier>(loc, locals_.at(std::stoi(inst->data[0]))));
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
        case opcode::OP_EmptyArray:
        {
            auto node = std::make_unique<ast::expr_empty_array>(loc);
            stack_.push(std::move(node));
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
        case opcode::OP_SafeSetVariableFieldCached:
            throw decomp_error("unhandled opcode " + resolver::opcode_name(inst->opcode));
            break;
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        {
            auto node = std::make_unique<ast::expr_identifier>(loc, locals_.at(std::stoi(inst->data[0])));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ClearParams:
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
        case opcode::OP_CheckClearParams:
            break;
        case opcode::OP_EvalLocalVariableRefCached:
        {
            auto node = std::make_unique<ast::expr_identifier>(loc, locals_.at(std::stoi(inst->data[0])));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_SetVariableField:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();

            auto rvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc();
            auto e = ast::expr(std::make_unique<ast::expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue)));
            auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(e));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_CallBuiltin:
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

            auto func = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(func));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_CallBuiltinMethod:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
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
        case opcode::OP_Wait:
        {
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = expr.loc();
            auto stmt = ast::stmt(std::make_unique<ast::stmt_wait>(loc, std::move(expr)));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_WaitTillFrameEnd:
        {
            auto stmt = ast::stmt(std::make_unique<ast::stmt_waittillframeend>(loc));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_PreScriptCall:
        {
            auto node = std::make_unique<ast::asm_prescriptcall>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptFunctionCall:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);

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
        case opcode::OP_ScriptFunctionCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = func.as_node->loc();

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
        case opcode::OP_ScriptMethodCall:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.loc();

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
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj) ,std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptMethodCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

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
        case opcode::OP_ScriptThreadCall:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc, inst->data[0]);
            auto name = std::make_unique<ast::expr_identifier>(loc, inst->data[1]);

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

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::thread));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptThreadCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = func.as_node->loc();

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ast::kind::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::thread));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptMethodThreadCall:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.loc();

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

            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::thread));
            auto node = std::make_unique<ast::expr_method>(loc, std::move(obj) ,std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ScriptMethodThreadCallPointer:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto func = ast::expr(std::move(stack_.top())); stack_.pop();
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = obj.as_node->loc();

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ast::kind::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            auto call = ast::call(std::make_unique<ast::expr_pointer>(loc, std::move(func), std::move(args), ast::call::mode::thread));
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
        case opcode::OP_CastFieldObject:
        case opcode::OP_CastBool:
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
        case opcode::OP_JumpOnTrue:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();

            if (inst->index > resolve_label(inst->data[0]))
            {
                auto expr = std::make_unique<ast::asm_jump_cond>(loc, std::move(lvalue), inst->data[0]);
                func_->stmt->list.push_back(ast::stmt(std::move(expr)));
            }
            else
            {
                auto e_not = ast::expr(std::make_unique<ast::expr_not>(loc, std::move(lvalue)));
                auto expr = std::make_unique<ast::asm_jump_cond>(loc, std::move(e_not), inst->data[0]);
                func_->stmt->list.push_back(ast::stmt(std::move(expr)));
            }
        }
            break;
        case opcode::OP_JumpOnFalse:
        {
            auto lvalue = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc();

            if (inst->index > resolve_label(inst->data[0]))
            {
                auto e_not = ast::expr(std::make_unique<ast::expr_not>(loc, std::move(lvalue)));
                auto expr = std::make_unique<ast::asm_jump_cond>(loc, std::move(e_not), inst->data[0]);
                func_->stmt->list.push_back(ast::stmt(std::move(expr)));
            }
            else
            {
                auto expr = std::make_unique<ast::asm_jump_cond>(loc, std::move(lvalue), inst->data[0]);
                func_->stmt->list.push_back(ast::stmt(std::move(expr)));
            }
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
        case opcode::OP_Jump:
        {
            auto expr = std::make_unique<ast::asm_jump>(loc, inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(expr)));
            if (stack_.size() != 0) tern_labels_.push_back(inst->data[0]);
        }
            break;
        case opcode::OP_JumpBack:
        {
            auto expr = std::make_unique<ast::asm_jump_back>(loc, inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(expr)));
        }
            break;
        case opcode::OP_Inc:
        {
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = ast::expr(std::make_unique<ast::expr_increment>(loc, std::move(lvalue), false));
            auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(node));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_Dec:
        {
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = ast::expr(std::make_unique<ast::expr_decrement>(loc, std::move(lvalue), false));
            auto stmt = std::make_unique<ast::stmt_assign>(loc, std::move(node));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_Bit_Or:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_bitwise_or>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Bit_Xor:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_bitwise_exor>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Bit_And:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_bitwise_and>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Equal:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_equality>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_NotEqual:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_inequality>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_LessThan:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_less>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GreaterThan:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_greater>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_LessThanOrEqualTo:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_less_equal>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GreaterThanOrEqualTo:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_greater_equal>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ShiftLeft:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_shift_left>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ShiftRight:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_shift_right>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Plus:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_add>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Minus:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_sub>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Multiply:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_mul>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Divide:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_div>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Modulus:
        {
            auto rvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_mod>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_SizeOf:
        {
            auto lvalue = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = lvalue.as_node->loc();
            auto node = std::make_unique<ast::expr_size>(loc, std::move(lvalue));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_WaitTillMatch:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = expr.as_node->loc();

            for (auto i = std::stoul(inst->data[0]); i > 0; i--)
            {
                auto node = std::move(stack_.top()); stack_.pop();
                loc = node->loc();
                args->list.push_back(std::move(node));
            }

            auto stmt = std::make_unique<ast::stmt_waittillmatch>(loc, std::move(obj), std::move(expr), std::move(args));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_WaitTill:
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
        case opcode::OP_Notify:
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
        case opcode::OP_EndOn:
        {
            auto obj = ast::expr(std::move(stack_.top())); stack_.pop();
            auto event = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = event.as_node->loc();
            auto stmt = std::make_unique<ast::stmt_endon>(loc, std::move(obj) , std::move(event));
            func_->stmt->list.push_back(ast::stmt(std::move(stmt)));
        }
            break;
        case opcode::OP_VoidCodePos:
        {
            auto node = std::make_unique<ast::asm_voidcodepos>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Switch:
        {
            auto expr = ast::expr(std::move(stack_.top()));
            stack_.pop();
            loc = expr.as_node->loc();
            auto sw = std::make_unique<ast::asm_switch>(loc, std::move(expr), inst->data[0]);
            func_->stmt->list.push_back(ast::stmt(std::move(sw)));
        }
            break;
        case opcode::OP_EndSwitch:
        {
            auto count = inst->data[0];
            inst->data.erase(inst->data.begin());
            auto data = inst->data;
            auto end = std::make_unique<ast::asm_endswitch>(loc, data, count);
            func_->stmt->list.push_back(ast::stmt(std::move(end)));
        }
            break;
        case opcode::OP_Vector:
        {
            auto x = ast::expr(std::move(stack_.top())); stack_.pop();
            auto y = ast::expr(std::move(stack_.top())); stack_.pop();
            auto z = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = z.as_node->loc();
            auto node = std::make_unique<ast::expr_vector>(loc, std::move(x), std::move(y), std::move(z));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetHash:
        {
            auto node = std::make_unique<ast::expr_hash>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_RealWait:
        {
            auto expr = ast::expr(std::move(stack_.top())); stack_.pop();
            loc = expr.loc();
            auto stmt = ast::stmt(std::make_unique<ast::stmt_realwait>(loc, std::move(expr)));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_VectorConstant:
        {
            auto flags = static_cast<std::uint8_t>(std::stoi(inst->data[0]));
            auto x = ast::expr(std::make_unique<ast::expr_float>(loc, (flags & 0x20) ? "1" : (flags & 0x10) ? "-1" : "0"));
            auto y = ast::expr(std::make_unique<ast::expr_float>(loc, (flags & 0x08) ? "1" : (flags & 0x04) ? "-1" : "0"));
            auto z = ast::expr(std::make_unique<ast::expr_float>(loc, (flags & 0x02) ? "1" : (flags & 0x01) ? "-1" : "0"));
            auto node = std::make_unique<ast::expr_vector>(loc, std::move(x), std::move(y), std::move(z));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_IsDefined:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_isdefined>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_VectorScale:
        {
            auto arg1 = std::move(stack_.top()); stack_.pop();
            auto arg2 = std::move(stack_.top()); stack_.pop();
            loc = arg2->loc();
            auto node = std::make_unique<ast::expr_vectorscale>(loc, std::move(arg1), std::move(arg2));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_AnglesToUp:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_anglestoup>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_AnglesToRight:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_anglestoright>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_AnglesToForward:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_anglestoforward>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_AngleClamp180:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_angleclamp180>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_VectorToAngles:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_vectortoangles>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_Abs:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_abs>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetTime:
        {
            auto node = std::make_unique<ast::expr_gettime>(loc);
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetDvar:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_getdvar>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetDvarInt:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_getdvarint>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetDvarFloat:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_getdvarfloat>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetDvarVector:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_getdvarvector>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetDvarColorRed:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_getdvarcolorred>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetDvarColorGreen:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_getdvarcolorgreen>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetDvarColorBlue:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_getdvarcolorblue>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_GetDvarColorAlpha:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            loc = arg->loc();
            auto node = std::make_unique<ast::expr_getdvarcoloralpha>(loc, std::move(arg));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_FirstArrayKey:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, "getfirstarraykey");
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();
            args->list.push_back(std::move(var));
            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_NextArrayKey:
        {
            auto args = std::make_unique<ast::expr_arguments>(loc);
            auto path = std::make_unique<ast::expr_path>(loc);
            auto name = std::make_unique<ast::expr_identifier>(loc, "getnextarraykey");
            auto var = std::move(stack_.top()); stack_.pop();
            args->list.push_back(std::move(var));
            var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();
            args->list.push_back(std::move(var));
            auto call = ast::call(std::make_unique<ast::expr_function>(loc, std::move(path), std::move(name), std::move(args), ast::call::mode::normal));
            auto node = std::make_unique<ast::expr_call>(loc, std::move(call));
            stack_.push(std::move(node));
        }
            break;
        case opcode::OP_ProfileStart:
        case opcode::OP_ProfileStop:
            throw decomp_error("unhandled opcode " + resolver::opcode_name(inst->opcode));
        case opcode::OP_SafeDecTop:
            break;
        case opcode::OP_Nop:
        case opcode::OP_Abort:
        case opcode::OP_Object:
        case opcode::OP_ThreadObject:
        case opcode::OP_EvalLocalVariable:
        case opcode::OP_EvalLocalVariableRef:
            throw decomp_error("unhandled opcode " + resolver::opcode_name(inst->opcode));
        case opcode::OP_DevblockBegin:
        {
            auto stmt = ast::stmt(std::make_unique<ast::asm_dev>(loc, inst->data[0]));
            func_->stmt->list.push_back(std::move(stmt));
        }
            break;
        case opcode::OP_DevblockEnd:
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
    try
    {
        decompile_infinites(stmt);
        decompile_loops(stmt);
        decompile_switches(stmt);
        decompile_ifelses(stmt);
        decompile_aborts(stmt);
        decompile_devblocks(stmt);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
}

void decompiler::decompile_infinites(const ast::stmt_list::ptr& stmt)
{
    if (stmt->list.size() == 0) return;

    for (auto i = stmt->list.size() - 1; i > 0; i--)
    {
        if (stmt->list.at(i) == ast::kind::asm_jump)
        {
            if (stmt->list.at(i).as_node->loc().begin.line < std::stol(stmt->list.at(i).as_jump->value.substr(4), 0, 16))
                continue;

            if (stmt->list.at(i).as_jump->value == blocks_.back().loc_continue)
                continue;

            auto break_loc = last_location_index(stmt, i) ? blocks_.back().loc_end : stmt->list.at(i + 1).loc().label();
            auto start = find_location_index(stmt, stmt->list.at(i).as_jump->value);

            if (stmt->list.at(i - 1).as_node->kind() == ast::kind::asm_jump_cond && stmt->list.at(i - 1).as_cond->value == break_loc)
            {
                continue;
            }
            else if (stmt->list.at(start).as_node->kind() != ast::kind::asm_jump_cond)
            {
                decompile_infinite(stmt, start, i);
                i = stmt->list.size();
            }
            else if (stmt->list.at(start).as_cond->value != break_loc)
            {
                decompile_infinite(stmt, start, i);
                i = stmt->list.size();
            }
            else if (stmt->list.at(start).as_cond->value == break_loc)
            {
                decompile_loop(stmt, start, i);
                i = stmt->list.size();
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
            auto j = (entry.as_cond->value == blocks_.back().loc_end) ? (stmt->list.size()) : (find_location_index(stmt, entry.as_cond->value));

            if (j < i)
            {
                decompile_dowhile(stmt, j, i);
                i = 0;
                continue;
            }

            j -= 1;

            if (stmt->list.at(j) == ast::kind::asm_jump)
            {
                if (stmt->list.at(j).as_node->loc().begin.line < std::stol(stmt->list.at(j).as_jump->value.substr(4), 0, 16))
                    continue;

                if (stmt->list.at(i).loc().label() == stmt->list.at(j).as_jump->value)
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
                    //if its a while, continue jumps back
                    if (stmt->list.at(j).as_node->loc().begin.line > std::stol(stmt->list.at(j).as_jump->value.substr(4), 0, 16))
                    {
                        decompile_if(stmt, i, j);
                    }
                    // a dowhile, for or foreach, check for if/else or if/continue
                    else if (j - i > 1 && stmt->list.at(j - 1) == ast::kind::stmt_return)
                    {
                        // block ends with a return, so jump belows to if/else
                        decompile_ifelse(stmt, i, j);
                    }
                    else if (j - i > 1 && stmt->list.at(j - 1) == ast::kind::asm_jump)
                    {
                        if (stmt->list.at(j - 1).as_jump->value == blocks_.back().loc_break)
                        {
                            // block ends with a break, so jump belows to if/else
                            decompile_ifelse(stmt, i, j);
                        }
                        else if (stmt->list.at(j - 1).as_jump->value == blocks_.back().loc_continue)
                        {
                            // block ends with a continue, so jump belows to if/else
                            decompile_ifelse(stmt, i, j);
                        }
                        else
                        {
                            // jump belows to if/continue
                            decompile_if(stmt, i, j);
                        }
                    }
                    else
                    {
                        decompile_if(stmt, i, j);
                    }
                }
                else if (stmt->list.at(j).as_jump->value == blocks_.back().loc_break)
                {
                    decompile_if(stmt, i, j);
                }
                else if (stmt->list.at(j).as_jump->value == blocks_.back().loc_end)
                {
                    if (find_location_reference(stmt, i + 1, j, entry.as_cond->value))
                        decompile_if(stmt, i, j);
                    else
                        decompile_ifelse(stmt, i, j);
                }
                else if (stmt->list.at(j).as_jump->value == entry.as_cond->value)
                {
                    if (find_location_reference(stmt, i + 1, j, entry.as_cond->value))
                        decompile_if(stmt, i, j);
                    else
                        decompile_ifelse(stmt, i, j);
                }
                else
                {
                    decompile_ifelse(stmt, i, j);
                }
            }
            else
            {
                decompile_if(stmt, i, j);
            }
        }
    }
}

void decompiler::decompile_aborts(const ast::stmt_list::ptr& stmt)
{
    for (auto i = 0u; i < stmt->list.size(); i++)
    {
        if (stmt->list.at(i) == ast::kind::asm_jump)
        {
            auto loc = stmt->list.at(i).loc();
            auto jump_loc = stmt->list.at(i).as_jump->value;

            if (jump_loc == blocks_.back().loc_continue)
            {
                stmt->list.erase(stmt->list.begin() + i);
                auto new_stmt = ast::stmt(std::make_unique<ast::stmt_continue>(loc));
                stmt->list.insert(stmt->list.begin() + i, std::move(new_stmt));
            }
            else if (jump_loc == blocks_.back().loc_break)
            {
                stmt->list.erase(stmt->list.begin() + i);
                auto new_stmt = ast::stmt(std::make_unique<ast::stmt_break>(loc));
                stmt->list.insert(stmt->list.begin() + i, std::move(new_stmt));
            }
        }
    }
}

void decompiler::decompile_devblocks(const ast::stmt_list::ptr& stmt)
{
    for (auto i = 0u; i < stmt->list.size(); i++)
    {
        if (stmt->list.at(i) == ast::kind::asm_dev)
        {
            if (blocks_.back().is_dev)
            {
                stmt->list.erase(stmt->list.begin() + i--);
                continue;
            }

            if (i + 1 < stmt->list.size())
            {
                if (stmt->list.at(i+1) == ast::kind::asm_dev && stmt->list.at(i+1).as_asm_dev->value == stmt->list.at(i).as_asm_dev->value)
                {
                    stmt->list.erase(stmt->list.begin() + i + 1);
                }
            }

            auto loc = stmt->list.at(i).loc();
            auto end = find_location_index(stmt, stmt->list.at(i).as_asm_dev->value);

            block dev_blk;
            dev_blk.loc_end = stmt->list.at(i).as_asm_dev->value;
            dev_blk.loc_break = blocks_.back().loc_break;
            dev_blk.loc_continue = blocks_.back().loc_continue;
            dev_blk.is_dev = true;

            stmt->list.erase(stmt->list.begin() + i);
            end -= 1;

            auto list_stmt = std::make_unique<ast::stmt_list>(loc);

            for (auto j = i; j < end; j++)
            {
                list_stmt->list.push_back(std::move(stmt->list[i]));
                stmt->list.erase(stmt->list.begin() + i);
            }

            blocks_.push_back(dev_blk);
            decompile_statements(list_stmt);
            blocks_.pop_back();

            if (list_stmt->list.size() == 1 && list_stmt->list.at(0) == ast::kind::stmt_call)
            {
                const auto& st = list_stmt->list.at(0);

                if (st.as_call->expr == ast::kind::expr_call && st.as_call->expr.as_call->call == ast::kind::expr_function)
                {
                    if (st.as_call->expr.as_call->call.as_function->name->value == "assert")
                    {
                        auto new_stmt = ast::stmt(std::make_unique<ast::stmt_call>(loc, std::move(st.as_call->expr)));
                        stmt->list.insert(stmt->list.begin() + i, std::move(new_stmt));
                        continue;
                    }
                    
                }
            }

            auto new_stmt = ast::stmt(std::make_unique<ast::stmt_dev>(loc, std::move(list_stmt)));
            stmt->list.insert(stmt->list.begin() + i, std::move(new_stmt));
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

void decompiler::decompile_infinite(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block blk;
    blk.loc_break = last_location_index(stmt, end) ? blocks_.back().loc_end : stmt->list.at(end + 1).loc().label();
    blk.loc_end = stmt->list.at(end).loc().label();
    blk.loc_continue = stmt->list.at(end).loc().label();

    auto loc = stmt->list.at(begin).loc();

    stmt->list.erase(stmt->list.begin() + end); // remove 'jump'

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

void decompiler::decompile_loop(const ast::stmt_list::ptr& stmt, std::size_t start, std::size_t end)
{
    auto& last = stmt->list.at(end - 1);

    if (last == ast::kind::stmt_assign)
    {
        if (last.as_assign->expr == ast::kind::expr_assign_equal)
        {
            auto& call = last.as_assign->expr.as_assign_equal->rvalue;

            if (call == ast::kind::expr_call && call.as_call->call == ast::kind::expr_function)
            {
                if (utils::string::to_lower(call.as_call->call.as_function->name->value) == "getnextarraykey")
                {
                    auto ref = stmt->list.at(start).loc().label();

                    if (!find_location_reference(stmt, 0, start, ref))
                    {
                        decompile_foreach(stmt, start, end);
                        return;
                    }
                }
            }
        }

        if (start > 0) // while at func start
        {
            if (stmt->list.at(start - 1) == ast::kind::stmt_assign)
            {
                if (!lvalues_match(stmt->list.at(start - 1).as_assign, last.as_assign))
                {
                    decompile_while(stmt, start, end);
                    return;
                }

                auto ref1 = stmt->list.at(end).loc().label();
                auto ref2 = stmt->list.at(start).loc().label();

                if (find_location_reference(stmt, start, end, ref1))
                {
                    // jump is referenced, not post-expr
                    decompile_while(stmt, start, end);
                    return;
                }
                else if (find_location_reference(stmt, start, end, ref2))
                {
                    // continue is at begin, not post-expr
                    decompile_while(stmt, start, end);
                    return;
                }
                else if (find_location_reference(stmt, 0, start, ref2))
                {
                    // begin is at condition, not pre-expr
                    decompile_while(stmt, start, end);
                    return;
                }
                else
                {
                    decompile_for(stmt, start, end);
                    return;
                }
            }
        }
    }

    decompile_while(stmt, start, end);
}

void decompiler::decompile_while(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block blk;
    blk.loc_break = stmt->list.at(begin).as_cond->value;
    blk.loc_end = stmt->list.at(end).loc().label();
    blk.loc_continue = stmt->list.at(begin).loc().label();

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
    blk.loc_break = last_location_index(stmt, end) ? blocks_.back().loc_end : stmt->list.at(end + 1).loc().label();
    blk.loc_end = stmt->list.at(end).loc().label();
    blk.loc_continue = stmt->list.at(end).loc().label();

    auto test = std::move(stmt->list.at(end).as_cond->expr);
    auto loc = stmt->list.at(begin).loc();

    stmt->list.erase(stmt->list.begin() + end); // remove 'test jump'

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
    stmt->list.insert(stmt->list.begin() + begin, std::move(new_stmt));
}

void decompiler::decompile_foreach(const ast::stmt_list::ptr& stmt, std::size_t begin, std::size_t end)
{
    block blk;
    blk.loc_break = stmt->list.at(begin).as_cond->value;
    blk.loc_end = stmt->list.at(end - 1).loc().label();
    blk.loc_continue = stmt->list.at(end - 1).loc().label();

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

    auto foreach_stmt = std::make_unique<ast::stmt_list>(loc);

    for (auto i = begin; i < end; i++)
    {
        foreach_stmt->list.push_back(std::move(stmt->list[begin]));
        stmt->list.erase(stmt->list.begin() + begin);
    }

    blocks_.push_back(blk);
    decompile_statements(foreach_stmt);
    blocks_.pop_back();

    auto new_stmt = ast::stmt(std::make_unique<ast::stmt_foreach>(loc, ast::stmt(std::move(foreach_stmt)), false));

    new_stmt.as_foreach->array_expr = std::move(init.as_list->list[0].as_assign->expr.as_assign->rvalue);
    new_stmt.as_foreach->value_expr = std::move(stmt0.as_assign->expr.as_assign->lvalue);
    new_stmt.as_foreach->key_expr = std::move(init.as_list->list[1].as_assign->expr.as_assign->lvalue);

    if (!new_stmt.as_foreach->key_expr.as_identifier->value.starts_with("_k"))
    {
        new_stmt.as_foreach->use_key = true;
    }

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
    auto numerical = data.back() == "i";
    auto idx = 0;

    for (auto i = 0; i < casenum; i++)
    {
        if (data.at(idx) == "case")
        {
            auto loc_str = data.at(idx + 2);
            auto loc_idx = find_location_index(stmt, loc_str);
            auto loc_pos = location(&filename_, std::stol(loc_str.substr(4), 0, 16));
            auto value = numerical ? ast::expr(std::make_unique<ast::expr_integer>(loc_pos, data.at(idx + 1))) : ast::expr(std::make_unique<ast::expr_string>(loc_pos, data.at(idx + 1)));
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

    end = find_location_index(stmt, end_loc); // update end

    // fix empty cases at end
    if (stmt->list.at(end) == ast::kind::asm_endswitch)
        end--;

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
        else if (entry == ast::kind::asm_dev && entry.as_asm_dev->value == location)
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

    for (const auto& entry : stmt->list)
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

auto decompiler::lvalues_match(const ast::stmt_assign::ptr& stmt1, const ast::stmt_assign::ptr& stmt2) -> bool
{
    ast::expr* lvalue1 {};
    ast::expr* lvalue2 {};

    switch (stmt1->expr.kind())
    {
        case ast::kind::expr_increment:
            lvalue1 = &stmt1->expr.as_increment->lvalue;
            break;
        case ast::kind::expr_decrement:
            lvalue1 = &stmt1->expr.as_decrement->lvalue;
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
            lvalue1 = &stmt1->expr.as_assign->lvalue;
            break;
        default:
            break;
    }

    switch (stmt2->expr.kind())
    {
        case ast::kind::expr_increment:
            lvalue2 = &stmt2->expr.as_increment->lvalue;
            break;
        case ast::kind::expr_decrement:
            lvalue2 = &stmt2->expr.as_decrement->lvalue;
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
            lvalue2 = &stmt2->expr.as_assign->lvalue;
            break;
        default:
            break;
    }

    if (lvalue1 && lvalue2 && *lvalue1 == *lvalue2)
        return true;

    return false;
}

auto decompiler::resolve_label(const std::string& name) -> std::uint32_t
{
    for (const auto& entry : labels_)
    {
        if (entry.second == name)
        {
            return entry.first;
        }
    }

    throw decomp_error("Couldn't resolve label address of '" + name + "'!");
}

void decompiler::process_thread(const ast::decl_thread::ptr& thread)
{
    process_stmt_list(thread->stmt);
}

void decompiler::process_stmt(const ast::stmt& stmt)
{
    switch (stmt.kind())
    {
        case ast::kind::stmt_list:
            process_stmt_list(stmt.as_list);
            break;
        case ast::kind::stmt_dev:
            process_stmt_dev(stmt.as_dev);
            break;
        case ast::kind::stmt_expr:
            process_stmt_expr(stmt.as_expr);
            break;
        case ast::kind::stmt_call:
            process_stmt_call(stmt.as_call);
            break;
        case ast::kind::stmt_assign:
            process_stmt_assign(stmt.as_assign);
            break;
        case ast::kind::stmt_endon:
            process_stmt_endon(stmt.as_endon);
            break;
        case ast::kind::stmt_notify:
            process_stmt_notify(stmt.as_notify);
            break;
        case ast::kind::stmt_wait:
            process_stmt_wait(stmt.as_wait);
            break;
        case ast::kind::stmt_waittill:
            process_stmt_waittill(stmt.as_waittill);
            break;
        case ast::kind::stmt_waittillmatch:
            process_stmt_waittillmatch(stmt.as_waittillmatch);
            break;
        case ast::kind::stmt_if:
            process_stmt_if(stmt.as_if);
            break;
        case ast::kind::stmt_ifelse:
            process_stmt_ifelse(stmt.as_ifelse);
            break;
        case ast::kind::stmt_while:
            process_stmt_while(stmt.as_while);
            break;
        case ast::kind::stmt_dowhile:
            process_stmt_dowhile(stmt.as_dowhile);
            break;
        case ast::kind::stmt_for:
            process_stmt_for(stmt.as_for);
            break;
        case ast::kind::stmt_foreach:
            process_stmt_foreach(stmt.as_foreach);
            break;
        case ast::kind::stmt_switch:
            process_stmt_switch(stmt.as_switch);
            break;
        case ast::kind::stmt_return:
            process_stmt_return(stmt.as_return);
            break;
        default:
            break;
    }
}

void decompiler::process_stmt_list(const ast::stmt_list::ptr& stmt)
{
    for (const auto& entry : stmt->list)
    {
        process_stmt(entry);
    }
}

void decompiler::process_stmt_dev(const ast::stmt_dev::ptr& stmt)
{
    process_stmt_list(stmt->list);
}

void decompiler::process_stmt_expr(const ast::stmt_expr::ptr& stmt)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            process_expr_increment(stmt->expr.as_increment);
            break;
        case ast::kind::expr_decrement:
            process_expr_decrement(stmt->expr.as_decrement);
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
            process_expr_assign(stmt->expr.as_assign);
            break;
        default:
            break;
    }
}

void decompiler::process_stmt_call(const ast::stmt_call::ptr& stmt)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_call:
            process_expr_call(stmt->expr.as_call);
            break;
        case ast::kind::expr_method:
            process_expr_method(stmt->expr.as_method);
            break;
        default:
            break;
    }
}

void decompiler::process_stmt_assign(const ast::stmt_assign::ptr& stmt)
{
    switch (stmt->expr.kind())
    {
        case ast::kind::expr_increment:
            process_expr_increment(stmt->expr.as_increment);
            break;
        case ast::kind::expr_decrement:
            process_expr_decrement(stmt->expr.as_decrement);
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
            process_expr_assign(stmt->expr.as_assign);
            break;
        default:
            break;
    }
}

void decompiler::process_stmt_endon(const ast::stmt_endon::ptr& stmt)
{
    process_expr(stmt->event);
    process_expr(stmt->obj);
}

void decompiler::process_stmt_notify(const ast::stmt_notify::ptr& stmt)
{
    process_expr_arguments(stmt->args);
    process_expr(stmt->event);
    process_expr(stmt->obj);
}

void decompiler::process_stmt_wait(const ast::stmt_wait::ptr& stmt)
{
    process_expr(stmt->time);
}

void decompiler::process_stmt_waittill(const ast::stmt_waittill::ptr& stmt)
{
    process_expr(stmt->event);
    process_expr(stmt->obj);

    for (auto& entry : stmt->args->list)
    {
        process_expr(entry);
    }
}

void decompiler::process_stmt_waittillmatch(const ast::stmt_waittillmatch::ptr& stmt)
{
    process_expr(stmt->event);
    process_expr(stmt->obj);
    process_expr_arguments(stmt->args);
}

void decompiler::process_stmt_if(const ast::stmt_if::ptr& stmt)
{
    process_expr(stmt->test);
    process_stmt(stmt->stmt);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list[0].as_node->is_special_stmt_dev())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }
}

void decompiler::process_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt)
{
    process_expr(stmt->test);
    process_stmt(stmt->stmt_if);
    process_stmt(stmt->stmt_else);

    if (stmt->stmt_if.as_list->list.size() == 1 && !stmt->stmt_if.as_list->list[0].as_node->is_special_stmt_dev())
    {
        stmt->stmt_if = std::move(stmt->stmt_if.as_list->list.back());
    }

    if (stmt->stmt_else.as_list->list.size() == 1 && !stmt->stmt_else.as_list->list[0].as_node->is_special_stmt_dev_noif())
    {
        stmt->stmt_else = std::move(stmt->stmt_else.as_list->list.back());
    }
}

void decompiler::process_stmt_while(const ast::stmt_while::ptr& stmt)
{
    if (stmt->test == ast::kind::expr_integer && stmt->test.as_integer->value == "1")
    {
        stmt->test = ast::expr(std::make_unique<ast::expr_true>());
    }

    process_expr(stmt->test);
    process_stmt(stmt->stmt);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list[0].as_node->is_special_stmt_dev())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }
}

void decompiler::process_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt)
{
    process_expr(stmt->test);
    process_stmt(stmt->stmt);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list[0].as_node->is_special_stmt_dev())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }
}

void decompiler::process_stmt_for(const ast::stmt_for::ptr& stmt)
{
    process_stmt(stmt->init);
    process_expr(stmt->test);
    process_stmt(stmt->stmt);
    process_stmt(stmt->iter);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list[0].as_node->is_special_stmt_dev())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }
}

void decompiler::process_stmt_foreach(const ast::stmt_foreach::ptr& stmt)
{
    process_expr(stmt->array_expr);
    process_expr(stmt->value_expr);
    process_expr(stmt->key_expr);
    process_stmt(stmt->stmt);

    if (stmt->stmt.as_list->list.size() == 1 && !stmt->stmt.as_list->list.at(0).as_node->is_special_stmt_dev())
    {
        stmt->stmt = std::move(stmt->stmt.as_list->list.back());
    }
}

void decompiler::process_stmt_switch(const ast::stmt_switch::ptr& stmt)
{
    process_expr(stmt->test);
    process_stmt_cases(stmt->stmt);
}

void decompiler::process_stmt_cases(const ast::stmt_list::ptr& stmt)
{
    for (auto& entry : stmt->list)
    {
        if (entry == ast::kind::stmt_case)
        {
            process_stmt_list(entry.as_case->stmt);
        }
        else if (entry == ast::kind::stmt_default)
        {
            process_stmt_list(entry.as_default->stmt);
        }
    }
}

void decompiler::process_stmt_return(const ast::stmt_return::ptr& stmt)
{
    if (stmt->expr != ast::kind::null)
    {
        if (retbool_ && retnum_ > 1)
        {
            if (stmt->expr.as_integer->value == "1")
            {
                stmt->expr = ast::expr(std::make_unique<ast::expr_true>());
            }
            else
            {
                stmt->expr = ast::expr(std::make_unique<ast::expr_false>());
            }
        }
        else
            process_expr(stmt->expr);
    }
}

void decompiler::process_expr(const ast::expr& expr)
{
    switch (expr.kind())
    {
        case ast::kind::expr_ternary:
            process_expr_ternary(expr.as_ternary);
            break;
        case ast::kind::expr_and:
            process_expr_and(expr.as_and);
            break;
        case ast::kind::expr_or:
            process_expr_or(expr.as_or);
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
            process_expr_binary(expr.as_binary);
            break;
        case ast::kind::expr_complement:
            process_expr_complement(expr.as_complement);
            break;
        case ast::kind::expr_not:
            process_expr_not(expr.as_not);
            break;
        case ast::kind::expr_call:
            process_expr_call(expr.as_call);
            break;
        case ast::kind::expr_method:
            process_expr_method(expr.as_method);
            break;
        case ast::kind::expr_getnextarraykey:
            process_expr(expr.as_getnextarraykey->arg2);
            process_expr(expr.as_getnextarraykey->arg1);
            break;
        case ast::kind::expr_getfirstarraykey:
            process_expr(expr.as_getfirstarraykey->arg);
            break;
        case ast::kind::expr_getdvarcoloralpha:
            process_expr(expr.as_getdvarcoloralpha->arg);
            break;
        case ast::kind::expr_getdvarcolorblue:
            process_expr(expr.as_getdvarcolorblue->arg);
            break;
        case ast::kind::expr_getdvarcolorgreen:
            process_expr(expr.as_getdvarcolorgreen->arg);
            break;
        case ast::kind::expr_getdvarcolorred:
            process_expr(expr.as_getdvarcolorred->arg);
            break;
        case ast::kind::expr_getdvarvector:
            process_expr(expr.as_getdvarvector->arg);
            break;
        case ast::kind::expr_getdvarfloat:
            process_expr(expr.as_getdvarfloat->arg);
            break;
        case ast::kind::expr_getdvarint:
            process_expr(expr.as_getdvarint->arg);
            break;
        case ast::kind::expr_getdvar:
            process_expr(expr.as_getdvar->arg);
            break;
        case ast::kind::expr_abs:
            process_expr(expr.as_abs->arg);
            break;
        case ast::kind::expr_vectortoangles:
            process_expr(expr.as_vectortoangles->arg);
            break;
        case ast::kind::expr_angleclamp180:
            process_expr(expr.as_angleclamp180->arg);
            break;
        case ast::kind::expr_anglestoforward:
            process_expr(expr.as_anglestoforward->arg);
            break;
        case ast::kind::expr_anglestoright:
            process_expr(expr.as_anglestoright->arg);
            break;
        case ast::kind::expr_anglestoup:
            process_expr(expr.as_anglestoup->arg);
            break;
        case ast::kind::expr_vectorscale:
            process_expr(expr.as_vectorscale->arg2);
            process_expr(expr.as_vectorscale->arg1);
            break;
        case ast::kind::expr_isdefined:
            process_expr(expr.as_isdefined->arg);
            break;
        case ast::kind::expr_array:
            process_array_variable(expr.as_array);
            break;
        case ast::kind::expr_field:
            process_field_variable(expr.as_field);
            break;
        case ast::kind::expr_size:
            process_expr_size(expr.as_size);
            break;
        case ast::kind::expr_vector:
            process_expr_vector(expr.as_vector);
            break;
        default:
            break;
    }
}

void decompiler::process_expr_assign(ast::expr_assign::ptr& expr)
{
    process_expr(expr->rvalue);
    process_expr(expr->lvalue);

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

void decompiler::process_expr_increment(const ast::expr_increment::ptr& expr)
{
    process_expr(expr->lvalue);
}

void decompiler::process_expr_decrement(const ast::expr_decrement::ptr& expr)
{
    process_expr(expr->lvalue);
}

void decompiler::process_expr_ternary(const ast::expr_ternary::ptr& expr)
{
    process_expr(expr->test);
    process_expr(expr->true_expr);
    process_expr(expr->false_expr);
}

void decompiler::process_expr_binary(const ast::expr_binary::ptr& expr)
{
    process_expr(expr->lvalue);
    process_expr(expr->rvalue);

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

void decompiler::process_expr_and(const ast::expr_and::ptr& expr)
{
    process_expr(expr->lvalue);
    process_expr(expr->rvalue);

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

void decompiler::process_expr_or(const ast::expr_or::ptr& expr)
{
    process_expr(expr->lvalue);
    process_expr(expr->rvalue);
}

void decompiler::process_expr_complement(const ast::expr_complement::ptr& expr)
{
    process_expr(expr->rvalue);

    if (expr->rvalue.as_node->is_binary())
    {
        expr->rvalue = ast::expr(std::make_unique<ast::expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_not(const ast::expr_not::ptr& expr)
{
    process_expr(expr->rvalue);

    if (expr->rvalue.as_node->is_binary())
    {
        expr->rvalue = ast::expr(std::make_unique<ast::expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_call(const ast::expr_call::ptr& expr)
{
    switch (expr->call.kind())
    {
        case ast::kind::expr_pointer:
            process_expr_call_pointer(expr->call.as_pointer);
            break;
        case ast::kind::expr_function:
            process_expr_call_function(expr->call.as_function);
            break;
        default:
            break;
    }
}

void decompiler::process_expr_method(const ast::expr_method::ptr& expr)
{
    switch (expr->call.kind())
    {
        case ast::kind::expr_pointer:
            process_expr_method_pointer(expr->call.as_pointer, expr->obj);
            break;
        case ast::kind::expr_function:
            process_expr_method_function(expr->call.as_function, expr->obj);
            break;
        default:
            break;
    }
}

void decompiler::process_expr_call_pointer(const ast::expr_pointer::ptr& expr)
{
    process_expr_arguments(expr->args);
    process_expr(expr->func);
}

void decompiler::process_expr_call_function(const ast::expr_function::ptr& expr)
{
    process_expr_arguments(expr->args);
}

void decompiler::process_expr_method_pointer(const ast::expr_pointer::ptr& expr, ast::expr& obj)
{
    process_expr_arguments(expr->args);
    process_expr(obj);
    process_expr(expr->func);
}

void decompiler::process_expr_method_function(const ast::expr_function::ptr& expr, ast::expr& obj)
{
    process_expr_arguments(expr->args);
    process_expr(obj);
}

void decompiler::process_expr_arguments(const ast::expr_arguments::ptr& expr)
{
    for (auto i = expr->list.size(); i > 0; i--)
    {
        process_expr(expr->list.at(i - 1));
    }
}

void decompiler::process_expr_size(const ast::expr_size::ptr& expr)
{
    process_expr(expr->obj);
}

void decompiler::process_array_variable(const ast::expr_array::ptr& expr)
{
    process_expr(expr->key);
    process_expr(expr->obj);
}

void decompiler::process_field_variable(const ast::expr_field::ptr& expr)
{
    process_expr(expr->obj);
}

void decompiler::process_expr_vector(const ast::expr_vector::ptr& expr)
{
    process_expr(expr->z);
    process_expr(expr->y);
    process_expr(expr->x);
}

} // namespace xsk::arc::t6
