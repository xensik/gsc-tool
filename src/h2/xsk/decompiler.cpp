// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "h2.hpp"

namespace xsk::gsc::h2
{

auto decompiler::output() -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> output;

    auto data = std::make_unique<utils::byte_buffer>(0x100000);
    data->write_string("// H2 PC GSC\n// Decompiled by https://github.com/xensik/gsc-tool\n");
    data->write_string(program_->print());

    output.resize(data->pos());
    std::memcpy(output.data(), data->buffer().data(), output.size());

    return output;
}

void decompiler::decompile(const std::string& file, std::vector<gsc::function_ptr>& functions)
{
    filename_ = file;
    program_ = std::make_unique<gsc::node_program>();

    for (auto& func : functions)
    {
        auto name = std::make_unique<gsc::node_name>(func->name.substr(4));
        auto params = std::make_unique<gsc::node_parameters>();
        auto block = std::make_unique<gsc::node_stmt_list>();
        func_ = std::make_unique<gsc::node_thread>(std::move(name),std::move(params),std::move(block));

        labels_ = func->labels;
        expr_labels_.clear();
        stack_ = std::stack<gsc::node_ptr>();

        this->decompile_function(func);

        this->process_stack(func_);

        program_->definitions.push_back(gsc::define_ptr(std::move(func_)));
    }
}

void decompiler::decompile_function(const gsc::function_ptr& func)
{
    this->decompile_statements(func);

    if(stack_.size() > 0)
    {
        throw gsc::decomp_error("stack not emty at function end");
    }

    auto& block = func_->block;

    gsc::context ctx;
    ctx.loc_end = utils::string::va("loc_%X", block->stmts.back().as_node->loc.begin.line);

    // remove last return
    block->stmts.pop_back();

    // hotfix empty else block at func end
    if(block->stmts.size() > 0 && block->stmts.back().as_node->type == gsc::node_t::asm_jump)
    {
        if(block->stmts.back().as_jump->value == ctx.loc_end)
            block->stmts.pop_back();
    }

    blocks_.push_back(ctx);
    this->decompile_block(block);
    blocks_.pop_back();
}

void decompiler::decompile_statements(const gsc::function_ptr& func)
{
    std::uint32_t last_null_loc = 0;
    bool in_waittill = false;

    for (auto& inst : func->instructions)
    {
        auto loc = gsc::location(&filename_, inst->index);

        const auto itr = func->labels.find(inst->index);

        if (itr != func->labels.end())
        {
            for(auto& entry : expr_labels_)
            {
                if(entry == itr->second)
                {
                    decompile_expr();
                }
            }
        }

        switch (opcode(inst->opcode))
        {
        case opcode::OP_End:
        {
            auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_return>(loc, std::make_unique<gsc::node>()));
            func_->block->stmts.push_back(std::move(stmt));
        }
        break;
        case opcode::OP_Return:
        {
            auto expr = std::move(stack_.top());
            stack_.pop();
            auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_return>(expr->loc, std::move(expr)));
            func_->block->stmts.push_back(std::move(stmt));
        }
        break;
        case opcode::OP_GetZero:
        {
            auto node = std::make_unique<gsc::node_integer>(loc, "0");
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetByte:		
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetInteger:
        {
            auto node = std::make_unique<gsc::node_integer>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetNegByte:
        case opcode::OP_GetNegUnsignedShort:
        {
            auto node = std::make_unique<gsc::node_integer>(loc, "-" + inst->data[0]);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetFloat:
        {
            auto node = std::make_unique<gsc::node_float>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetVector:
        {
            auto x = gsc::expr_ptr(std::make_unique<gsc::node_float>(loc, inst->data[0]));
            auto y = gsc::expr_ptr(std::make_unique<gsc::node_float>(loc, inst->data[1]));
            auto z = gsc::expr_ptr(std::make_unique<gsc::node_float>(loc, inst->data[2]));
            auto node = std::make_unique<gsc::node_vector>(loc, std::move(x), std::move(y), std::move(z));
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetString:
        {
            auto node = std::make_unique<gsc::node_string>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetIString:
        {
            auto node = std::make_unique<gsc::node_istring>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetUndefined:
        {
            auto node = std::make_unique<gsc::node_undefined>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EmptyArray:
        {
            auto node = std::make_unique<gsc::node_empty_array>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetLevel:
        case opcode::OP_GetLevelObject:
        {
            auto node = std::make_unique<gsc::node_level>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetAnim:
        case opcode::OP_GetAnimObject:
        {
            auto node = std::make_unique<gsc::node_anim>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetSelf:
        case opcode::OP_GetSelfObject:
        {
            auto node = std::make_unique<gsc::node_self>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetGame:
        case opcode::OP_GetGameRef:
        {
            auto node = std::make_unique<gsc::node_game>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetAnimation:
        {
            auto tree = utils::string::unquote(inst->data[0]);

            if(tree != "")
            {
                auto treename = std::make_unique<gsc::node_string>(loc, inst->data[0]);
                auto animtree = std::make_unique<gsc::node_usingtree>(loc, std::move(treename));
                program_->definitions.push_back(gsc::define_ptr(std::move(animtree)));
            }

            auto node = std::make_unique<gsc::node_animation>(loc, utils::string::unquote(inst->data[1]));
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetAnimTree:
        {
            auto tree = utils::string::unquote(inst->data[0]);

            if(tree != "")
            {
                auto treename = std::make_unique<gsc::node_string>(loc, inst->data[0]);
                auto animtree = std::make_unique<gsc::node_usingtree>(loc, std::move(treename));
                program_->definitions.push_back(gsc::define_ptr(std::move(animtree)));
            }

            auto node = std::make_unique<gsc::node_animtree>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetThisthread:
        {
            auto node = std::make_unique<gsc::node_thisthread>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_GetBuiltinFunction:
        case opcode::OP_GetBuiltinMethod:
        {
            auto file = std::make_unique<gsc::node_file>(loc);
            auto func = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto stmt = std::make_unique<gsc::node_expr_function>(loc, std::move(file), std::move(func));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_GetLocalFunction:
        {
            auto file = std::make_unique<gsc::node_file>(loc);
            auto func = std::make_unique<gsc::node_name>(loc, inst->data[0].substr(4));
            auto stmt = std::make_unique<gsc::node_expr_function>(loc, std::move(file), std::move(func));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_GetFarFunction:
        {
            auto file = std::make_unique<gsc::node_file>(loc, utils::string::backslash(inst->data[0]));
            auto func = std::make_unique<gsc::node_name>(loc, inst->data[1]);
            auto stmt = std::make_unique<gsc::node_expr_function>(loc, std::move(file), std::move(func));
            stack_.push(std::move(stmt));
        };
        break;
        case opcode::OP_CreateLocalVariable:
        {
            if(in_waittill)
            {
                auto expr = std::make_unique<gsc::node_asm_create>(loc, inst->data[0]);
                stack_.push(std::move(expr));
            }
            else
            {
                auto stmt = std::make_unique<gsc::node_asm_create>(loc, inst->data[0]);
                func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
            }
        }
        break;
        case opcode::OP_RemoveLocalVariables:
        {
            auto stmt = std::make_unique<gsc::node_asm_remove>(loc, inst->data[0]);
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_EvalLocalVariableCached0:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, "0");
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalLocalVariableCached1:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, "1");
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalLocalVariableCached2:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, "2");
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalLocalVariableCached3:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, "3");
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalLocalVariableCached4:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, "4");
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalLocalVariableCached5:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, "5");
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalLocalVariableCached:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalLocalArrayCached:
        {
            auto key = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_asm_access>(loc, inst->data[0]));
            auto node = std::make_unique<gsc::node_expr_array>(key.as_node->loc, std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalArray:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto key = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto node = std::make_unique<gsc::node_expr_array>(key.as_node->loc, std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalNewLocalArrayRefCached0:
        {
            auto key = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_asm_create>(loc, inst->data[0]));
            auto node = std::make_unique<gsc::node_expr_array>(key.as_node->loc, std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalLocalArrayRefCached0:
        {
            auto key = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_asm_access>(loc, "0"));
            auto node = std::make_unique<gsc::node_expr_array>(key.as_node->loc, std::move(obj), std::move(key));
            stack_.push(std::move(node));	
        }
        break;
        case opcode::OP_EvalLocalArrayRefCached:
        {
            auto key = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_asm_access>(loc, inst->data[0]));
            auto node = std::make_unique<gsc::node_expr_array>(key.as_node->loc, std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalArrayRef:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto key = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto node = std::make_unique<gsc::node_expr_array>(key.as_node->loc, std::move(obj), std::move(key));
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_ClearArray:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto key = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = key.as_node->loc;
            auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_expr_array>(loc, std::move(obj), std::move(key)));
            auto rvalue = gsc::expr_ptr(std::make_unique<gsc::node_undefined>(loc));
            auto expr = std::make_unique<gsc::node_expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue));
            auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_assign>(loc, std::move(expr)));
            func_->block->stmts.push_back(std::move(stmt));
        }
        break;
        case opcode::OP_AddArray:
        {
            auto var = std::move(stack_.top());
            stack_.pop();
            auto array = std::move(stack_.top());
            stack_.pop();
            
            if (array->type == gsc::node_t::data_empty_array)
            {
                auto args = std::make_unique<gsc::node_expr_arguments>(loc);
                args->list.push_back(std::move(var));
                auto expr = std::make_unique<gsc::node_expr_add_array>(array->loc, std::move(args));
                stack_.push(std::move(expr));
            }
            else if (array->type == gsc::node_t::expr_add_array)
            {
                (*(gsc::expr_add_array_ptr*)&array)->args->list.push_back(std::move(var));
                stack_.push(std::move(array));
            }
            else
            {
                throw gsc::decomp_error("unknown add array type (could be an array variable name?)");
            }
        }
        break;
        case opcode::OP_PreScriptCall:
        {
            auto node = std::make_unique<gsc::node_asm_prescriptcall>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_ScriptLocalFunctionCall2:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0].substr(4));
            auto file = std::make_unique<gsc::node_file>(loc);
            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptLocalFunctionCall:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0].substr(4));
            auto file = std::make_unique<gsc::node_file>(loc);

            auto var = std::move(stack_.top());
            stack_.pop();
            loc = var->loc;
            while(var->type != gsc::node_t::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptLocalMethodCall:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0].substr(4));
            auto file = std::make_unique<gsc::node_file>(loc);

            auto var = std::move(stack_.top());
            stack_.pop();
            loc = var->loc;
            while(var->type != gsc::node_t::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptLocalThreadCall:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0].substr(4));
            auto file = std::make_unique<gsc::node_file>(loc);

            auto argnum = std::stoul(inst->data[1]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, true, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptLocalChildThreadCall:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0].substr(4));
            auto file = std::make_unique<gsc::node_file>(loc);

            auto argnum = std::stoul(inst->data[1]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, true, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptLocalMethodThreadCall:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0].substr(4));
            auto file = std::make_unique<gsc::node_file>(loc);

            auto argnum = std::stoul(inst->data[1]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, true, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptLocalMethodChildThreadCall:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0].substr(4));
            auto file = std::make_unique<gsc::node_file>(loc);

            auto argnum = std::stoul(inst->data[1]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, true, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptFarFunctionCall2:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[1]);
            auto file = std::make_unique<gsc::node_file>(loc, utils::string::backslash(inst->data[0]));
            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptFarFunctionCall:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[1]);
            auto file = std::make_unique<gsc::node_file>(loc, utils::string::backslash(inst->data[0]));

            auto var = std::move(stack_.top());
            stack_.pop();
            loc = var->loc;
            while(var->type != gsc::node_t::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptFarMethodCall:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[1]);
            auto file = std::make_unique<gsc::node_file>(loc, utils::string::backslash(inst->data[0]));

            auto var = std::move(stack_.top());
            stack_.pop();
            loc = var->loc;
            while(var->type != gsc::node_t::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptFarThreadCall:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[2]);
            auto file = std::make_unique<gsc::node_file>(loc, utils::string::backslash(inst->data[1]));

            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, true, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptFarMethodThreadCall:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[2]);
            auto file = std::make_unique<gsc::node_file>(loc, utils::string::backslash(inst->data[1]));

            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, true, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptFunctionCallPointer:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto exprf = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = exprf.as_node->loc;
            auto var = std::move(stack_.top());
            stack_.pop();
            loc = var->loc;
            while(var->type != gsc::node_t::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(loc, false, std::move(exprf), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptMethodCallPointer:
        {		
            auto exprf = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto var = std::move(stack_.top());
            stack_.pop();
            loc = var->loc;
            while(var->type != gsc::node_t::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(loc, false, std::move(exprf), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptThreadCallPointer:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto exprf = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = exprf.as_node->loc;
            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(loc, false, std::move(exprf), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, true, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptChildThreadCallPointer:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto exprf = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = exprf.as_node->loc;
            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(loc, false, std::move(exprf), std::move(args)));
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, true, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptMethodThreadCallPointer:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto exprf = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(loc, false, std::move(exprf), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, true, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_ScriptMethodChildThreadCallPointer:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto exprf = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(loc, false, std::move(exprf), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, true, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltinPointer:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto exprf = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = exprf.as_node->loc;

            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(loc, true, std::move(exprf), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltinMethodPointer:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto exprf = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(loc, true, std::move(exprf), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltin0:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);
            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltin1:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 1; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }
            
            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltin2:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 2; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }
            
            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltin3:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 3; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }
            
            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltin4:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 4; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }
            
            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltin5:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 5; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }
            
            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltin:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[1]);
            auto file = std::make_unique<gsc::node_file>(loc);

            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltinMethod0:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltinMethod1:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 1; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltinMethod2:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 2; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltinMethod3:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 3; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltinMethod4:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 4; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltinMethod5:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto file = std::make_unique<gsc::node_file>(loc);

            for (size_t i = 5; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_CallBuiltinMethod:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto name = std::make_unique<gsc::node_name>(loc, inst->data[1]);
            auto file = std::make_unique<gsc::node_file>(loc);

            auto argnum = std::stoul(inst->data[0]);

            for (size_t i = argnum; i > 0; i--)
            {
                auto var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
                args->list.push_back(std::move(var));
            }

            auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(loc, std::move(file), std::move(name), std::move(args)));
            auto expr = std::make_unique<gsc::node_expr_call>(loc, false, false, std::move(obj) ,std::move(func));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_DecTop:
        {
            auto expr = std::move(stack_.top());
            stack_.pop();
            loc = expr->loc;
            auto stmt = std::make_unique<gsc::node_stmt_call>(loc, std::move(*(gsc::expr_call_ptr*)&expr));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_inc:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_increment>(loc, std::move(lvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_dec:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_decrement>(loc, std::move(lvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_bit_or:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_bitwise_or>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_bit_ex_or:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_bitwise_exor>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_bit_and:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_bitwise_and>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_equality:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_equality>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_inequality:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_inequality>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_less:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_less>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_greater:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_greater>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_less_equal:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_less_equal>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_greater_equal:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_greater_equal>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_shift_left:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_shift_left>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_shift_right:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_shift_right>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_plus:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_add>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_minus:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_sub>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_multiply:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_mult>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_divide:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_div>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_mod:
        {
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_mod>(loc, std::move(lvalue), std::move(rvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_wait:
        {
            auto expr = std::move(stack_.top());
            stack_.pop();
            loc = expr->loc;
            auto stmt = std::make_unique<gsc::node_stmt_wait>(loc, std::move(expr));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_waittillFrameEnd:
        {
            auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_waittillframeend>(loc));
            func_->block->stmts.push_back(std::move(stmt));
        }
        break;
        case opcode::OP_waitFrame:
        {
            auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_waitframe>(loc));
            func_->block->stmts.push_back(std::move(stmt));
        }
        break;
        case opcode::OP_waittill:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto nstr = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = nstr.as_node->loc;
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto stmt = std::make_unique<gsc::node_stmt_waittill>(loc, std::move(obj) , std::move(nstr), std::move(args));
            stack_.push(std::move(stmt));
            in_waittill = true;
        }
        break;
        case opcode::OP_waittillmatch:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto expr = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = expr.as_node->loc;

            gsc::expr_arguments_ptr args = std::make_unique<gsc::node_expr_arguments>();
            args->loc = loc;

            while(stack_.size() > 0)
            {
                auto node = std::move(stack_.top());
                stack_.pop();
                args->loc = node->loc;
                args->list.push_back(std::move(node));
            }
            loc = args->loc;

            auto stmt = std::make_unique<gsc::node_stmt_waittillmatch>(loc, std::move(obj), std::move(expr), std::move(args));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_clearparams:
        {
            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            auto var = std::move(stack_.top());
            stack_.pop();

            while(var->type != gsc::node_t::stmt_waittill && var->type != gsc::node_t::stmt_waittillmatch)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top());
                stack_.pop();
            }

            if(var->type == gsc::node_t::stmt_waittill)
            {
                std::reverse(args->list.begin(), args->list.end());
                (*(gsc::stmt_waittill_ptr*)&var)->args = std::move(args);
                in_waittill = false;
            }

            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(var)));
        }
        break;
        case opcode::OP_checkclearparams:
        break;
        case opcode::OP_notify:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto nstr = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();

            auto args = std::make_unique<gsc::node_expr_arguments>(loc);
            
            auto var = std::move(stack_.top());
            stack_.pop();
            loc = var->loc;
            while(var->type != gsc::node_t::asm_voidcodepos)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top());
                stack_.pop();
                loc = var->loc;
            }

            auto stmt = std::make_unique<gsc::node_stmt_notify>(loc, std::move(obj) , std::move(nstr), std::move(args));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_endon:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto nstr = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = nstr.as_node->loc;
            auto stmt = std::make_unique<gsc::node_stmt_endon>(loc, std::move(obj) , std::move(nstr));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_voidCodepos:
        {
            auto node = std::make_unique<gsc::node_asm_voidcodepos>(loc);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_vector:
        {
            auto x = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto y = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            auto z = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = z.as_node->loc;
            auto expr = std::make_unique<gsc::node_vector>(loc, std::move(x), std::move(y),  std::move(z));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_size:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_size>(loc, std::move(lvalue));
            stack_.push(std::move(expr));
        }
        break;		
        case opcode::OP_EvalLevelFieldVariable:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_level>(loc));
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto stmt = std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_EvalAnimFieldVariable:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_anim>(loc));
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto stmt = std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_EvalSelfFieldVariable:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_self>(loc));
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto stmt = std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_EvalFieldVariable:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto stmt = std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_EvalLevelFieldVariableRef:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_level>(loc));
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto stmt = std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_EvalAnimFieldVariableRef:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_anim>(loc));
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto stmt = std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_EvalSelfFieldVariableRef:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_self>(loc));
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto stmt = std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_EvalFieldVariableRef:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto stmt = std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field));
            stack_.push(std::move(stmt));
        }
        break;
        case opcode::OP_ClearFieldVariable:
        {
            auto obj = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = obj.as_node->loc;
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto expr = gsc::expr_ptr(std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field)));
            auto undef = gsc::expr_ptr(std::make_unique<gsc::node_undefined>(loc));
            auto e = std::make_unique<gsc::node_expr_assign_equal>(loc, std::move(expr), std::move(undef));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::make_unique<gsc::node_stmt_assign>(loc, std::move(e))));
        }
        break;
        case opcode::OP_SafeCreateVariableFieldCached:
        {
            func_->params->list.push_back(std::make_unique<gsc::node_name>(loc, "var_" + inst->data[0]));
        }
        break;
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        {
            if(stack_.top()->type != gsc::node_t::asm_create)
            {
                auto node = std::make_unique<gsc::node_asm_access>(loc, inst->data[0]);
                stack_.push(std::move(node));
            }
        }
        break;
        case opcode::OP_EvalLocalVariableRefCached0:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, "0");
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_EvalLocalVariableRefCached:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_SetLevelFieldVariableField:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_level>(loc));
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field)));
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc;
            auto e = std::make_unique<gsc::node_expr_assign_equal>(loc,std::move(lvalue), std::move(rvalue));
            auto stmt = std::make_unique<gsc::node_stmt_assign>(loc, std::move(e));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_SetVariableField:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;

            if(lvalue.as_node->type == gsc::node_t::expr_increment)
            {
                auto stmt = std::make_unique<gsc::node_stmt_assign>(loc, std::move(lvalue.as_increment));
                func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
            }
            else if(lvalue.as_node->type == gsc::node_t::expr_decrement)
            {
                auto stmt = std::make_unique<gsc::node_stmt_assign>(loc, std::move(lvalue.as_decrement));
                func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
            }
            else
            {
                auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
                stack_.pop();
                loc = rvalue.as_node->loc;
                auto e = std::make_unique<gsc::node_expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue));
                auto stmt = std::make_unique<gsc::node_stmt_assign>(loc, std::move(e));
                func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
            }
        }
        break;
        case opcode::OP_SetAnimFieldVariableField:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_anim>(loc));
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field)));
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc;
            auto e = std::make_unique<gsc::node_expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue));
            auto stmt = std::make_unique<gsc::node_stmt_assign>(loc, std::move(e));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_SetSelfFieldVariableField:
        {
            auto obj = gsc::expr_ptr(std::make_unique<gsc::node_self>(loc));
            auto field = std::make_unique<gsc::node_name>(loc, inst->data[0]);
            auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_expr_field>(loc, std::move(obj), std::move(field)));
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc;
            auto e = std::make_unique<gsc::node_expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue));
            auto stmt = std::make_unique<gsc::node_stmt_assign>(loc, std::move(e));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_SetLocalVariableFieldCached0:
        {
            auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_asm_access>(loc, "0"));
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc;
            auto e = std::make_unique<gsc::node_expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue));
            auto stmt = std::make_unique<gsc::node_stmt_assign>(loc, std::move(e));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_SetNewLocalVariableFieldCached0:
        {
            auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_asm_create>(loc, inst->data[0]));
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc;

            if(func_->block->stmts.size() > 0)
            {
                std::vector<std::string> creates;

                while(func_->block->stmts.back().as_node->type == gsc::node_t::asm_create)
                {
                    auto& entry = func_->block->stmts.back();
                    if(loc.begin.line < entry.as_node->loc.begin.line)
                    {
                        creates.push_back(entry.as_asm_create->index);
                        func_->block->stmts.pop_back();
                        continue;
                    }
                    break;
                }

                std::reverse(creates.begin(), creates.end());
                lvalue.as_asm_create->vars = creates;
            }

            auto e = std::make_unique<gsc::node_expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue));
            auto stmt = std::make_unique<gsc::node_stmt_assign>(loc, std::move(e));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_SetLocalVariableFieldCached:
        {
            auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_asm_access>(loc, inst->data[0]));
            auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = rvalue.as_node->loc;
            auto e = std::make_unique<gsc::node_expr_assign_equal>(loc, std::move(lvalue), std::move(rvalue));
            auto stmt = std::make_unique<gsc::node_stmt_assign>(loc, std::move(e));
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_ClearLocalVariableFieldCached:
        {
            auto stmt = std::make_unique<gsc::node_asm_clear>(loc, inst->data[0]);
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_ClearLocalVariableFieldCached0:
        {
            auto stmt = std::make_unique<gsc::node_asm_clear>(loc,"0");
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
        }
        break;
        case opcode::OP_EvalLocalVariableObjectCached:
        {
            auto node = std::make_unique<gsc::node_asm_access>(loc, inst->data[0]);
            stack_.push(std::move(node));
        }
        break;
        case opcode::OP_CastFieldObject:
        case opcode::OP_CastBool:
        break;
        case opcode::OP_BoolNot:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_not>(loc, std::move(lvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_BoolComplement:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_expr_complement>(loc, std::move(lvalue));
            stack_.push(std::move(expr));
        }
        break;
        case opcode::OP_switch:
        {
            auto expr = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = expr.as_node->loc;
            auto sw = std::make_unique<gsc::node_asm_switch>(loc, std::move(expr), inst->data[0]);
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(sw)));
        }
        break;
        case opcode::OP_endswitch:
        {
            auto count = inst->data[0];
            inst->data.erase(inst->data.begin());
            auto data = inst->data;
            auto end = std::make_unique<gsc::node_asm_endswitch>(loc, data, count);
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(end)));
        }
        break;
        case opcode::OP_jump:
        {
            auto expr = std::make_unique<gsc::node_asm_jump>(loc, inst->data[0]);
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(expr)));
        }
        break;
        case opcode::OP_jumpback:
        {
            auto expr = std::make_unique<gsc::node_asm_jump_back>(loc, inst->data[0]);
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(expr)));
        }
        break;
        case opcode::OP_JumpOnTrue:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto e_not = gsc::expr_ptr(std::make_unique<gsc::node_expr_not>(loc, std::move(lvalue)));
            auto expr = std::make_unique<gsc::node_asm_jump_cond>(loc, std::move(e_not), inst->data[0]);
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(expr)));
        }
        break;
        case opcode::OP_JumpOnFalse:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_asm_jump_cond>(loc, std::move(lvalue), inst->data[0]);
            func_->block->stmts.push_back(gsc::stmt_ptr(std::move(expr)));
        }
        break;
        case opcode::OP_JumpOnTrueExpr:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_asm_jump_true_expr>(loc, std::move(lvalue), inst->data[0]);
            stack_.push(std::move(expr));
            expr_labels_.push_back(inst->data[0]);
        }
        break;
        case opcode::OP_JumpOnFalseExpr:
        {
            auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
            stack_.pop();
            loc = lvalue.as_node->loc;
            auto expr = std::make_unique<gsc::node_asm_jump_false_expr>(loc, std::move(lvalue), inst->data[0]);
            stack_.push(std::move(expr));
            expr_labels_.push_back(inst->data[0]);
        }
        break;
        default:
            throw gsc::decomp_error("unhandled opcode " + resolver::opcode_name(inst->opcode));
        break;
        }
    }
}

void decompiler::decompile_expr()
{
    auto expr = std::move(stack_.top());
    stack_.pop();

    auto jump_expr = std::move(stack_.top());
    stack_.pop();
    auto loc = jump_expr->loc;
    
    if(jump_expr->type == gsc::node_t::asm_jump_true_expr)
    {
        auto lvalue = std::move((*(gsc::asm_jump_true_expr_ptr*)&jump_expr)->expr);
        auto rvalue = gsc::expr_ptr(std::move(expr));
        auto e = std::make_unique<gsc::node_expr_or>(loc, std::move(lvalue), std::move(rvalue));
        stack_.push(std::move(e));
    }
    else if(jump_expr->type == gsc::node_t::asm_jump_false_expr)
    {
        auto lvalue = std::move((*(gsc::asm_jump_false_expr_ptr*)&jump_expr)->expr);
        auto rvalue = gsc::expr_ptr(std::move(expr));
        auto e = std::make_unique<gsc::node_expr_and>(loc, std::move(lvalue), std::move(rvalue));
        stack_.push(std::move(e));
    }
    else
    {
        throw gsc::decomp_error("TRIED TO DECOMPILE INVALID JUMP EXPR!");
    }
}

void decompiler::decompile_block(const gsc::stmt_list_ptr& block)
{
    this->decompile_search_infinite(block);
    this->decompile_search_loop(block);
    this->decompile_search_switch(block);
    this->decompile_search_ifelse(block);
    this->decompile_break_continue(block);
}

void decompiler::decompile_search_infinite(const gsc::stmt_list_ptr& block)
{
    std::int32_t index = block->stmts.size() - 1;

    while(index >= 0)
    {
        if(block->stmts.at(index).as_node->type == gsc::node_t::asm_jump_back)
        {
            auto break_loc = last_location_index(block, index) ?  blocks_.back().loc_end : utils::string::va("loc_%X", block->stmts.at(index+1).as_node->loc.begin.line);
            auto begin_loc = block->stmts.at(index).as_jump_back->value;
            auto start = find_location_index(block, begin_loc);

            if(block->stmts.at(start).as_node->type != gsc::node_t::asm_jump_cond)
            {
                decompile_infinite(block, start, index);
                index = start;
            }
            else if (block->stmts.at(start).as_cond->value != break_loc)
            {
                decompile_infinite(block, start, index);
                index = start;
            }
        }
        
        index--;
    }
}

void decompiler::decompile_search_loop(const gsc::stmt_list_ptr& block)
{
    auto index = 0;

    while(index < block->stmts.size())
    {
        auto& stmt = block->stmts.at(index);

        if(stmt.as_node->type == gsc::node_t::asm_jump_cond)
        {
            std::uint32_t end;
            if(stmt.as_cond->value == blocks_.back().loc_end)
            {
                end = block->stmts.size() - 1;
            }
            else
            {
                end = find_location_index(block, stmt.as_cond->value) - 1;
            }
            
            if(block->stmts.at(end).as_node->type == gsc::node_t::asm_jump_back
                && utils::string::va("loc_%X", block->stmts.at(index).as_node->loc.begin.line) == block->stmts.at(end).as_jump_back->value)
            {
                decompile_loop(block, index, end);
                index = 0;
            }
        }
        index++;
    }
}

void decompiler::decompile_search_switch(const gsc::stmt_list_ptr& block)
{
    auto index = 0;

    while(index < block->stmts.size())
    {
        if(block->stmts.at(index).as_node->type == gsc::node_t::asm_switch)
        {
            decompile_switch(block, index);
        }

        index++;
    }
}

void decompiler::decompile_search_ifelse(const gsc::stmt_list_ptr& block)
{
    auto index = 0;

    while(index < block->stmts.size())
    {
        auto& stmt = block->stmts.at(index);

        if(stmt.as_node->type == gsc::node_t::asm_jump_cond)
        {
            std::uint32_t end;
            if(stmt.as_cond->value == blocks_.back().loc_end)
            {
                end = block->stmts.size() - 1;
            }
            else
            {
                end = find_location_index(block, stmt.as_cond->value) - 1;
            }
            
            auto last_loc = blocks_.back().loc_end;

            if(block->stmts.at(end).as_node->type == gsc::node_t::asm_jump)
            {
                // if block is a loop check break, continue
                if(block->stmts.at(end).as_jump->value == blocks_.back().loc_continue)
                {
                    // last if/else inside a loop still trigger this :(
                    decompile_if(block, index, end);
                }
                else if(block->stmts.at(end).as_jump->value == blocks_.back().loc_break)
                {
                    decompile_if(block, index, end);
                }
                else if(block->stmts.at(end).as_jump->value == blocks_.back().loc_end)
                {
                    decompile_ifelse(block, index, end);
                }
                else if(block->stmts.at(end).as_jump->value == stmt.as_cond->value)
                {
                    decompile_if(block, index, end); // if block, have a last empty else inside
                }
                else
                {
                    decompile_ifelse(block, index, end); // TODO: if else block is empty, convert it to only if!
                }
            }
            else if(block->stmts.at(end).as_node->type == gsc::node_t::stmt_return
                && block->stmts.at(end).as_return->expr.as_node->type == gsc::node_t::null)
            {
                if(blocks_.back().loc_break != "" || blocks_.back().loc_continue != "")
                {
                    decompile_if(block, index, end); // inside a loop cant be last
                }
                else if(end - index  == 1)
                {
                    decompile_if(block, index, end); // only one explicit return
                }
                else if(block->stmts.back().as_node->type != gsc::node_t::stmt_return)
                {
                    decompile_if(block, index, end); // block end is not a last return
                }
                else if(blocks_.back().is_last && block->stmts.back().as_node->type != gsc::node_t::stmt_return)
                {
                    decompile_if(block, index, end); // inside a last block but is not and inner last
                }
                else if(find_location_reference(block, end, block->stmts.size(), last_loc))
                {
                    decompile_if(block, index, end); // reference to func end after the if
                }
                else if(blocks_.size() > 1 && !blocks_.back().is_last)
                {
                    decompile_if(block, index, end); // fake last ifelse
                }
                else
                {
                    decompile_last_ifelse(block, index, end); // special case
                }
            }
            else
            {
                decompile_if(block, index, end);
            }
        }
        index++;
    }
}

void decompiler::decompile_break_continue(const gsc::stmt_list_ptr& block)
{
    auto index = 0;

    while(index < block->stmts.size())
    {
        if(block->stmts.at(index).as_node->type == gsc::node_t::asm_jump)
        {
            auto loc = block->stmts.at(index).as_node->loc;
            auto jump_loc = block->stmts.at(index).as_jump->value;
    
            if(jump_loc == blocks_.back().loc_continue)
            {
                block->stmts.erase(block->stmts.begin() + index);
                auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_continue>(loc));
                block->stmts.insert(block->stmts.begin() + index, std::move(stmt));
            }
            else if(jump_loc == blocks_.back().loc_break)
            {
                block->stmts.erase(block->stmts.begin() + index);
                auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_break>(loc));
                block->stmts.insert(block->stmts.begin() + index, std::move(stmt));
            }
        }

        index++;
    }
}

void decompiler::decompile_if(const gsc::stmt_list_ptr& block, std::uint32_t begin, std::uint32_t end)
{
    gsc::context ctx;
    ctx.loc_end = block->stmts.at(begin).as_cond->value;
    ctx.loc_break = blocks_.back().loc_break;
    ctx.loc_continue = blocks_.back().loc_continue;

    auto loc = block->stmts.at(begin).as_node->loc;
    auto expr = std::move(block->stmts.at(begin).as_cond->expr);

    block->stmts.erase(block->stmts.begin() + begin); // remove condition

    auto if_block = std::make_unique<gsc::node_stmt_list>(loc);

    for(auto i = begin; i < end; i++)
    {
        if_block->stmts.push_back(std::move(block->stmts[begin]));
        block->stmts.erase(block->stmts.begin() + begin);
    }

    blocks_.push_back(ctx);
    decompile_block(if_block);
    blocks_.pop_back();

    auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_if>(loc, std::move(expr), gsc::stmt_ptr(std::move(if_block))));
    block->stmts.insert(block->stmts.begin() + begin, std::move(stmt));
}

void decompiler::decompile_ifelse(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end)
{
    gsc::context ctx;
    ctx.loc_end = utils::string::va("loc_%X", block->stmts.at(end).as_node->loc.begin.line);
    ctx.loc_break = blocks_.back().loc_break;
    ctx.loc_continue = blocks_.back().loc_continue;

    auto loc = block->stmts.at(start).as_node->loc;
    auto expr = std::move(block->stmts.at(start).as_cond->expr);

    block->stmts.erase(block->stmts.begin() + start); // remove condition
    end = end - 1;

    auto if_block = std::make_unique<gsc::node_stmt_list>(loc);

    for(auto i = start; i < end; i++) // skip the jump
    {
        if_block->stmts.push_back(std::move(block->stmts[start]));
        block->stmts.erase(block->stmts.begin() + start);
    }

    blocks_.push_back(ctx);
    decompile_block(if_block);
    blocks_.pop_back();

    auto end_loc = block->stmts.at(start).as_jump->value;

    block->stmts.erase(block->stmts.begin() + start); // remove jump

    std::uint32_t end_index;

    if(end_loc == blocks_.back().loc_end)
    {
        end_index = block->stmts.size();
    }
    else
    {
        end_index = find_location_index(block, end_loc);
    }

    gsc::context ctx2;
    ctx2.loc_end = end_loc;
    ctx2.loc_break = blocks_.back().loc_break;
    ctx2.loc_continue = blocks_.back().loc_continue;

    auto else_block = std::make_unique<gsc::node_stmt_list>(loc);

    for(auto i = start; i < end_index; i++)
    {
        else_block->stmts.push_back(std::move(block->stmts[start]));
        block->stmts.erase(block->stmts.begin() + start);
    }

    blocks_.push_back(ctx2);
    decompile_block(else_block);
    blocks_.pop_back();

    auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_ifelse>(loc, std::move(expr), gsc::stmt_ptr(std::move(if_block)), gsc::stmt_ptr(std::move(else_block))));
    block->stmts.insert(block->stmts.begin() + start, std::move(stmt));
}

void decompiler::decompile_last_ifelse(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end)
{
    gsc::context ctx;
    ctx.is_last = true;

    auto inner_end = find_location_index(block, block->stmts.at(start).as_cond->value) - 1;
    ctx.loc_end = utils::string::va("loc_%X",block->stmts.at(inner_end).as_node->loc.begin.line);
    auto loc = block->stmts.at(start).as_node->loc;
    auto expr = std::move(block->stmts.at(start).as_cond->expr);

    block->stmts.erase(block->stmts.begin() + start); // remove condition
    end = end - 1;

    auto if_block = std::make_unique<gsc::node_stmt_list>(loc);

    for(auto i = start; i < end; i++)
    {
        if_block->stmts.push_back(std::move(block->stmts[start]));
        block->stmts.erase(block->stmts.begin() + start);
    }

    block->stmts.erase(block->stmts.begin() + start); // remove if block return;

    blocks_.push_back(ctx);
    decompile_block(if_block);
    blocks_.pop_back();

    if(start == block->stmts.size())
    {
        auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_if>(loc, std::move(expr), gsc::stmt_ptr(std::move(if_block))));
        block->stmts.insert(block->stmts.begin() + start, std::move(stmt));
    }
    else
    {
        gsc::context ctx2;
        ctx2.is_last = true;

        auto else_block = std::make_unique<gsc::node_stmt_list>(loc);

        end = block->stmts.size();
        ctx2.loc_end = utils::string::va("loc_%X", block->stmts.at(end - 1).as_node->loc.begin.line); // return is the block end

        for(auto i = start; i < end; i++)
        {
            else_block->stmts.push_back(std::move(block->stmts[start]));
            block->stmts.erase(block->stmts.begin() + start);
        }

        else_block->stmts.pop_back(); // remove else return;

        blocks_.push_back(ctx2);
        decompile_block(else_block);
        blocks_.pop_back();

        auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_ifelse>(loc, std::move(expr), gsc::stmt_ptr(std::move(if_block)), gsc::stmt_ptr(std::move(else_block))));
        block->stmts.insert(block->stmts.begin() + start, std::move(stmt));
    }
}

void decompiler::decompile_infinite(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end)
{
    gsc::context ctx;
    ctx.loc_break = last_location_index(block, end) ? blocks_.back().loc_end : utils::string::va("loc_%X", block->stmts.at(end+1).as_node->loc.begin.line);
    ctx.loc_end = utils::string::va("loc_%X", block->stmts.at(end).as_node->loc.begin.line);
    ctx.loc_continue = utils::string::va("loc_%X", block->stmts.at(end).as_node->loc.begin.line);

    auto loc = block->stmts.at(start).as_node->loc;

    block->stmts.erase(block->stmts.begin() + end); // remove jump back

    auto for_block = std::make_unique<gsc::node_stmt_list>(loc);

    for(auto i = start; i < end; i++)
    {
        for_block->stmts.push_back(std::move(block->stmts[start]));
        block->stmts.erase(block->stmts.begin() + start);
    }

    blocks_.push_back(ctx);
    decompile_block(for_block);
    blocks_.pop_back();

    auto pre_expr = gsc::stmt_ptr(std::make_unique<gsc::node>());
    auto expr = gsc::expr_ptr(std::make_unique<gsc::node>());
    auto post_expr = gsc::stmt_ptr(std::make_unique<gsc::node>());
    auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_for>(loc, std::move(pre_expr), std::move(expr), std::move(post_expr), gsc::stmt_ptr(std::move(for_block))));
    block->stmts.insert(block->stmts.begin() + start, std::move(stmt));
}

void decompiler::decompile_loop(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end)
{
    auto& last_stmt = block->stmts.at(end-1);
    if(last_stmt.as_node->type == gsc::node_t::stmt_assign)
    {
        if(last_stmt.as_assign->expr->type == gsc::node_t::expr_assign_equal)
        {
            auto& rval = last_stmt.as_assign->expr->rvalue;
            if(rval.as_node->type == gsc::node_t::expr_call)
            {
                if(rval.as_call->func.as_node->type == gsc::node_t::expr_call_function)
                {
                    if(utils::string::to_lower(rval.as_call->func.as_func->name->value) == "getnextarraykey")
                    {
                        auto ref2 = utils::string::va("loc_%X", block->stmts.at(start).as_node->loc.begin.line);
                        if(find_location_reference(block, 0, start, ref2))
                        {
                            // begin is at condition, not pre-expr
                            //decompile_while(block, start, end);
                            //return;
                        }
                        else
                        {
                            decompile_foreach(block, start, end);
                            return;
                        }
                    }
                }
            }
        }

        if(start > 0) // while at func start
        {
            auto index = 1;
            while(block->stmts.at(start - index).as_node->type == gsc::node_t::asm_create)
            {
                if(start - index > 0)
                    index++;
            }

            if(block->stmts.at(start - index).as_node->type == gsc::node_t::stmt_assign)
            {
                auto ref = utils::string::va("loc_%X", block->stmts.at(end).as_node->loc.begin.line);
                auto ref2 = utils::string::va("loc_%X", block->stmts.at(start).as_node->loc.begin.line);

                if(find_location_reference(block, start, end, ref))
                {
                    // continue is at jumpback, not post-expr
                    decompile_while(block, start, end);
                    return;
                }
                else if(find_location_reference(block, 0, start, ref2))
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

void decompiler::decompile_while(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end)
{
    gsc::context ctx;
    ctx.loc_break = block->stmts.at(start).as_cond->value;
    ctx.loc_end = utils::string::va("loc_%X", block->stmts.at(end).as_node->loc.begin.line);
    ctx.loc_continue = utils::string::va("loc_%X",block->stmts.at(end).as_node->loc.begin.line);

    auto loc = block->stmts.at(start).as_node->loc;
    auto expr = std::move(block->stmts.at(start).as_cond->expr);

    block->stmts.erase(block->stmts.begin() + end); // remove jump back
    block->stmts.erase(block->stmts.begin() + start); // remove condition
    end = end - 1;

    auto while_block = std::make_unique<gsc::node_stmt_list>(loc);

    for(auto i = start; i < end; i++)
    {
        while_block->stmts.push_back(std::move(block->stmts[start]));
        block->stmts.erase(block->stmts.begin() + start);
    }

    blocks_.push_back(ctx);
    decompile_block(while_block);
    blocks_.pop_back();

    auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_while>(loc, std::move(expr), gsc::stmt_ptr(std::move(while_block))));
    block->stmts.insert(block->stmts.begin() + start, std::move(stmt));
}

void decompiler::decompile_for(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end)
{
    gsc::context ctx;
    ctx.loc_break = block->stmts.at(start).as_cond->value;
    ctx.loc_end = utils::string::va("loc_%X", block->stmts.at(end - 1).as_node->loc.begin.line);
    ctx.loc_continue = utils::string::va("loc_%X", block->stmts.at(end - 1).as_node->loc.begin.line);

    // remove emit local var_creates
    std::vector<std::string> creates;
    while(block->stmts.at(start - 1).as_node->type == gsc::node_t::asm_create)
    {
        creates.push_back(block->stmts.at(start - 1).as_asm_create->index);
        block->stmts.erase(block->stmts.begin() + start - 1);
        start--;
        end--;
    }

    std::reverse(creates.begin(), creates.end());

    auto loc = block->stmts.at(start - 1).as_node->loc;
    auto expr = std::move(block->stmts.at(start).as_cond->expr);
    auto pre_expr = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_list>());
    pre_expr.as_list->stmts.push_back(std::move(block->stmts.at(start - 1)));
    pre_expr.as_list->is_expr = true;
    auto post_expr = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_list>());
    post_expr.as_list->stmts.push_back(std::move(block->stmts.at(end - 1)));
    post_expr.as_list->is_expr = true;

    start = start - 1;
    end = end - 2;
    for(auto i = start; i < start + 2; i++) // remove prologue (pre-expr, condition)
    {
        block->stmts.erase(block->stmts.begin() + start);
    }

    end = end - 1; // set end in post-expr
    for(auto i = end; i < end + 2; i++) // remove epilogue (post-expr, jump back)
    {
        block->stmts.erase(block->stmts.begin() + end);
    }

    auto for_block = std::make_unique<gsc::node_stmt_list>(loc);

    for(auto i = start; i < end; i++)
    {
        for_block->stmts.push_back(std::move(block->stmts[start]));
        block->stmts.erase(block->stmts.begin() + start);
    }

    blocks_.push_back(ctx);
    decompile_block(for_block);
    blocks_.pop_back();

    auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_for>(loc, std::move(pre_expr), std::move(expr), std::move(post_expr), gsc::stmt_ptr(std::move(for_block))));
    stmt.as_for->vars = creates;
    block->stmts.insert(block->stmts.begin() + start, std::move(stmt));
}

void decompiler::decompile_foreach(const gsc::stmt_list_ptr& block, std::uint32_t begin, std::uint32_t end)
{
    gsc::context ctx;
    ctx.loc_break = block->stmts.at(begin).as_cond->value;
    ctx.loc_end = utils::string::va("loc_%X", block->stmts.at(end - 1).as_node->loc.begin.line);
    ctx.loc_continue = utils::string::va("loc_%X", block->stmts.at(end - 1).as_node->loc.begin.line);

    // remove local var_creates
    std::vector<std::string> creates;
    while(block->stmts.at(begin - 1).as_node->type == gsc::node_t::asm_create)
    {
        creates.push_back(block->stmts.at(begin - 1).as_asm_create->index);
        block->stmts.erase(block->stmts.begin() + begin - 1);
        begin--;
        end--;
    }

    std::reverse(creates.begin(), creates.end());

    auto loc = block->stmts.at(begin - 2).as_node->loc;

    auto pre_expr = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_list>());
    pre_expr.as_list->stmts.push_back(std::move(block->stmts[begin-2]));
    pre_expr.as_list->stmts.push_back(std::move(block->stmts[begin-1]));
    auto stmt0 = std::move(block->stmts[begin+1]);

    begin = begin - 2;
    end = end - 4;
    for(auto i = begin; i < begin + 4; i++) // remove prologue ( array, elem, cond, elemRef)
    {
        block->stmts.erase(block->stmts.begin() + begin);
    }

    end = end - 1; // set end to post-expr

    for(auto i = end; i < end + 2; i++) // remove epilogue ( post-expr, jump back)
    {
        block->stmts.erase(block->stmts.begin() + end);
    }

    if(block->stmts.size() > end && block->stmts.at(end).as_node->type == gsc::node_t::asm_clear)
    {
        block->stmts.erase(block->stmts.begin() + end);
    }

    auto use_key = true;
    
    if(block->stmts.size() > end && block->stmts.at(end).as_node->type == gsc::node_t::asm_clear)
    {
        block->stmts.erase(block->stmts.begin() + end);
        use_key = false;
    }

    auto foreach_block = std::make_unique<gsc::node_stmt_list>(loc);

    for(auto i = begin; i < end; i++)
    {
        foreach_block->stmts.push_back(std::move(block->stmts[begin]));
        block->stmts.erase(block->stmts.begin() + begin);
    }

    blocks_.push_back(ctx);
    decompile_block(foreach_block);
    blocks_.pop_back();

    auto foreach_stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_foreach>(loc, gsc::stmt_ptr(std::move(foreach_block)), use_key));
    foreach_stmt.as_foreach->vars = creates;
    foreach_stmt.as_foreach->pre_expr = std::move(pre_expr);
    foreach_stmt.as_foreach->stmt0 = std::move(stmt0);

    block->stmts.insert(block->stmts.begin() + begin, std::move(foreach_stmt));
}

void decompiler::decompile_switch(const gsc::stmt_list_ptr& block, std::uint32_t start)
{
    gsc::context ctx;
    ctx.loc_continue = blocks_.back().loc_continue;
    ctx.loc_end = block->stmts.at(start).as_asm_switch->value;

    auto loc = block->stmts.at(start).as_node->loc;
    auto expr = std::move(block->stmts.at(start).as_asm_switch->expr);
    auto end_loc = block->stmts.at(start).as_asm_switch->value;
    auto end = find_location_index(block, end_loc);

    if(end == block->stmts.size() - 1)
    {
        ctx.loc_break = blocks_.back().loc_end;
    }
    else
    {
        ctx.loc_break = utils::string::va("loc_%X", block->stmts.at(end + 1).as_node->loc.begin.line);
    }

    // collect cases
    auto casenum = std::atol(block->stmts.at(end).as_asm_endswitch->count.data());
    auto data = block->stmts.at(end).as_asm_endswitch->data;
    auto idx = 0;

    for(auto i = 0; i < casenum; i++)
    {
        if(data.at(idx) == "case")
        {
            auto loc_str = data.at(idx+2);
            auto loc_idx = find_location_index(block, loc_str);
            auto loc_pos = gsc::location(&filename_, std::stol(loc_str.substr(4), 0, 16));
            auto value = gsc::expr_ptr(std::make_unique<gsc::node_string>(loc_pos, data.at(idx+1)));
            auto list = std::make_unique<gsc::node_stmt_list>(loc);
            list->is_case = true;
            auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_case>(loc_pos, std::move(value), std::move(list)));
            block->stmts.insert(block->stmts.begin() + loc_idx, std::move(stmt));
            idx += 3;
        }
        else if(data.at(idx) == "default")
        {
            auto loc_str = data.at(idx+1);
            auto loc_idx = find_location_index(block, loc_str);
            auto loc_pos = gsc::location(&filename_, std::stol(loc_str.substr(4), 0, 16));
            auto list = std::make_unique<gsc::node_stmt_list>(loc);
            list->is_case = true;
            auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_default>(loc_pos, std::move(list)));
            while(block->stmts.at(loc_idx).as_node->type == gsc::node_t::stmt_case)
                loc_idx++;
            block->stmts.insert(block->stmts.begin() + loc_idx, std::move(stmt));
            idx += 2;
        }
    }

    end = find_location_index(block, end_loc) - 1; // update end;
    block->stmts.erase(block->stmts.begin() + start); // remove switch
    block->stmts.erase(block->stmts.begin() + end); // remove endswitch

    //decompile block
    auto sw_block = std::make_unique<gsc::node_stmt_list>(loc);

    for(auto i = start; i < end; i++)
    {
        sw_block->stmts.push_back(std::move(block->stmts[start]));
        block->stmts.erase(block->stmts.begin() + start);
    }

    blocks_.push_back(ctx);
    decompile_block(sw_block);
    blocks_.pop_back();

    auto stmt_list = std::make_unique<gsc::node_stmt_list>(loc);
    gsc::stmt_ptr current_case = gsc::stmt_ptr(std::make_unique<gsc::node>());

    auto num = sw_block->stmts.size();
    for(auto i = 0; i < num; i++)
    {
        auto& entry = sw_block->stmts[0];

        if(entry.as_node->type == gsc::node_t::stmt_case || entry.as_node->type == gsc::node_t::stmt_default)
        {
            if(current_case.as_node->type != gsc::node_t::null)
            {
                stmt_list->stmts.push_back(std::move(current_case));
            }

            current_case = std::move(sw_block->stmts[0]);
            sw_block->stmts.erase(sw_block->stmts.begin());
        }
        else
        {
            if(current_case.as_node->type != gsc::node_t::null)
            {
                if(current_case.as_node->type == gsc::node_t::stmt_case)
                {
                    current_case.as_case->stmt->stmts.push_back(std::move(sw_block->stmts[0]));
                    sw_block->stmts.erase(sw_block->stmts.begin());
                }
                else
                {
                    current_case.as_default->stmt->stmts.push_back(std::move(sw_block->stmts[0]));
                    sw_block->stmts.erase(sw_block->stmts.begin());
                }
            }
            else
            {
                gsc::decomp_error("missing case before stmt inside switch!");
            }
        }
    }

    if(current_case.as_node->type != gsc::node_t::null)
    {
        stmt_list->stmts.push_back(std::move(current_case));
    }

    auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_switch>(loc, std::move(expr), std::move(stmt_list)));
    block->stmts.insert(block->stmts.begin() + start, std::move(stmt));
}

auto decompiler::find_location_reference(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end, const std::string& location) -> bool
{
    for(auto i = start; i < end; i++)
    {
        if(block->stmts.at(i).as_node->type == gsc::node_t::asm_jump_cond)
        {
            if(block->stmts.at(i).as_cond->value == location)
                return true;
        }
        else if(block->stmts.at(i).as_node->type == gsc::node_t::asm_jump)
        {
            if(block->stmts.at(i).as_jump->value == location)
                return true;
        }
    }

    return false;
}

auto decompiler::find_location_index(const gsc::stmt_list_ptr& block, const std::string& location) -> std::uint32_t
{
    auto index = 0;

    if(location == blocks_.back().loc_end)
        return block->stmts.size();

    for(auto& stmt : block->stmts)
    {
        if(stmt.as_node->loc.begin.line == std::stol(location.substr(4), 0, 16))
            return index;

        index++;
    }

    throw gsc::decomp_error("LOCATION NOT FOUND! (" + location + ")");
}

auto decompiler::last_location_index(const gsc::stmt_list_ptr& block, std::uint32_t index) -> bool
{
    if(index == block->stmts.size() - 1)
        return true;
    
    return false;
}

void decompiler::process_stack(const gsc::thread_ptr& thread)
{
    auto ctx = std::make_unique<gsc::context>();

    process_parameters(ctx, thread->params);
    process_stmt_list(ctx, thread->block);

}

void decompiler::process_parameters(const gsc::context_ptr& ctx, const gsc::parameters_ptr& params)
{
    for(const auto& param : params->list)
    {
        ctx->local_vars.push_back({ param->value, static_cast<uint8_t>(std::stoi(param->value.substr(4))), true });
        ctx->local_vars_create_count++;
    }
}

void decompiler::process_stmt(const gsc::context_ptr& ctx, const gsc::stmt_ptr& stmt)
{
    switch(stmt.as_node->type)
    {
        case gsc::node_t::stmt_list:             process_stmt_list(ctx, stmt.as_list); break;
        case gsc::node_t::stmt_call:             process_stmt_call(ctx, stmt.as_call); break;
        case gsc::node_t::stmt_assign:           process_stmt_assign(ctx, stmt.as_assign); break;
        case gsc::node_t::stmt_endon:            process_stmt_endon(ctx, stmt.as_endon); break;
        case gsc::node_t::stmt_notify:           process_stmt_notify(ctx, stmt.as_notify); break;
        case gsc::node_t::stmt_wait:             process_stmt_wait(ctx, stmt.as_wait); break;
        case gsc::node_t::stmt_waittill:         process_stmt_waittill(ctx, stmt.as_waittill); break;
        case gsc::node_t::stmt_waittillmatch:    process_stmt_waittillmatch(ctx, stmt.as_waittillmatch); break;
        case gsc::node_t::stmt_if:               process_stmt_if(ctx, stmt.as_if); break;
        case gsc::node_t::stmt_ifelse:           process_stmt_ifelse(ctx, stmt.as_ifelse); break;
        case gsc::node_t::stmt_while:            process_stmt_while(ctx, stmt.as_while); break;
        case gsc::node_t::stmt_for:              process_stmt_for(ctx, stmt.as_for); break;
        case gsc::node_t::stmt_foreach:          process_stmt_foreach(ctx, stmt.as_foreach); break;
        case gsc::node_t::stmt_switch:           process_stmt_switch(ctx, stmt.as_switch); break;
        case gsc::node_t::stmt_break:            process_stmt_break(ctx, stmt.as_break); break;
        case gsc::node_t::stmt_return:           process_stmt_return(ctx, stmt.as_return); break;
        case gsc::node_t::asm_remove:            process_var_remove(ctx, stmt.as_asm_remove); break;
        case gsc::node_t::asm_create:
        {
            auto expr = gsc::expr_ptr(std::make_unique<gsc::node_asm_create>(stmt.as_asm_create->index));
            process_var_create(ctx, expr, true);
        } 
        break;
        default: break;
    }
}

void decompiler::process_stmt_list(const gsc::context_ptr& ctx, const gsc::stmt_list_ptr& stmt)
{
    for (const auto& entry : stmt->stmts)
    {
        process_stmt(ctx, entry);
    }

    for(auto i = 0; i < stmt->stmts.size(); i++)
    {
        auto type = stmt->stmts.at(i).as_node->type;

        if(type == gsc::node_t::asm_create || type == gsc::node_t::asm_remove)
        {
            stmt->stmts.erase(stmt->stmts.begin() + i);
            i--;
        }
    }
}

void decompiler::process_stmt_call(const gsc::context_ptr& ctx, const gsc::stmt_call_ptr& stmt)
{
    process_expr_call(ctx, stmt->expr);
}

void decompiler::process_stmt_assign(const gsc::context_ptr& ctx, const gsc::stmt_assign_ptr& stmt)
{
    process_expr_assign(ctx, stmt->expr);
}

void decompiler::process_stmt_endon(const gsc::context_ptr& ctx, const gsc::stmt_endon_ptr& stmt)
{
    process_expr(ctx, stmt->expr);
    process_expr(ctx, stmt->obj);
}

void decompiler::process_stmt_notify(const gsc::context_ptr& ctx, const gsc::stmt_notify_ptr& stmt)
{
    process_expr_arguments(ctx, stmt->args);
    process_expr(ctx, stmt->expr);
    process_expr(ctx, stmt->obj);
}

void decompiler::process_stmt_wait(const gsc::context_ptr& ctx, const gsc::stmt_wait_ptr& stmt)
{
    process_expr(ctx, stmt->expr);
}

void decompiler::process_stmt_waittill(const gsc::context_ptr& ctx, const gsc::stmt_waittill_ptr& stmt)
{
    process_expr(ctx, stmt->expr);
    process_expr(ctx, stmt->obj);
    
    for(auto& arg : stmt->args->list)
    {
        process_expr(ctx, arg);
    }
}

void decompiler::process_stmt_waittillmatch(const gsc::context_ptr& ctx, const gsc::stmt_waittillmatch_ptr& stmt)
{
    process_expr_arguments(ctx, stmt->args);
    process_expr(ctx, stmt->expr);
    process_expr(ctx, stmt->obj);
}

void decompiler::process_stmt_if(const gsc::context_ptr& ctx, const gsc::stmt_if_ptr& stmt)
{
    process_expr(ctx, stmt->expr);

    stmt->ctx = std::make_unique<gsc::context>();
    ctx->transfer_decompiler(stmt->ctx);

    process_stmt(stmt->ctx, stmt->stmt);

    if(stmt->stmt.as_list->stmts.size() == 1 && !gsc::node::is_special_stmt(stmt->stmt.as_list->stmts.at(0)))
    {
        stmt->stmt = std::move(stmt->stmt.as_list->stmts.back());
    }
}

void decompiler::process_stmt_ifelse(const gsc::context_ptr& ctx, const gsc::stmt_ifelse_ptr& stmt)
{
    process_expr(ctx, stmt->expr);

    stmt->ctx_if = std::make_unique<gsc::context>();
    ctx->transfer_decompiler(stmt->ctx_if);

    process_stmt(stmt->ctx_if, stmt->stmt_if);

    stmt->ctx_else = std::make_unique<gsc::context>();
    ctx->transfer_decompiler(stmt->ctx_else);

    process_stmt(stmt->ctx_else, stmt->stmt_else);

    std::vector<gsc::context*> childs({stmt->ctx_if.get(), stmt->ctx_else.get()});
    ctx->append(childs);

    if(stmt->stmt_if.as_list->stmts.size() == 1 && !gsc::node::is_special_stmt(stmt->stmt_if.as_list->stmts.at(0)))
    {
        stmt->stmt_if = std::move(stmt->stmt_if.as_list->stmts.back());
    }

    if(stmt->stmt_else.as_list->stmts.size() == 1 && !gsc::node::is_special_stmt_noif(stmt->stmt_else.as_list->stmts.at(0)))
    {
        stmt->stmt_else = std::move(stmt->stmt_else.as_list->stmts.back());
    }
}

void decompiler::process_stmt_while(const gsc::context_ptr& ctx, const gsc::stmt_while_ptr& stmt)
{
    process_expr(ctx, stmt->expr);

    stmt->ctx = std::make_unique<gsc::context>();
    ctx->transfer_decompiler(stmt->ctx);

    process_stmt(stmt->ctx, stmt->stmt);

    std::vector<gsc::context*> childs({ stmt->ctx.get() });

    if(stmt->expr.as_node->type == gsc::node_t::null)
        ctx->append_decompiler(stmt->ctx);

    if(stmt->stmt.as_list->stmts.size() == 1 && !gsc::node::is_special_stmt(stmt->stmt.as_list->stmts.at(0)))
    {
        stmt->stmt = std::move(stmt->stmt.as_list->stmts.back());
    }
}

void decompiler::process_stmt_for(const gsc::context_ptr& ctx, const gsc::stmt_for_ptr& stmt)
{
    process_stmt(ctx, stmt->pre_expr);

    for(auto& index : stmt->vars)
    {
        auto var = utils::string::va("var_%d", std::stoi(index));
        ctx->local_vars.push_back({ var, static_cast<uint8_t>(std::stoi(index)), true });
        ctx->local_vars_create_count++;
    }

    stmt->ctx = std::make_unique<gsc::context>();
    ctx->transfer_decompiler(stmt->ctx);

    process_expr(ctx, stmt->expr);

    process_stmt(stmt->ctx, stmt->stmt);

    process_stmt(ctx, stmt->post_expr);

    if(stmt->expr.as_node->type == gsc::node_t::null)
        ctx->append_decompiler(stmt->ctx);

    if(stmt->stmt.as_list->stmts.size() == 1 && !gsc::node::is_special_stmt(stmt->stmt.as_list->stmts.at(0)))
    {
        stmt->stmt = std::move(stmt->stmt.as_list->stmts.back());
    }
}

void decompiler::process_stmt_foreach(const gsc::context_ptr& ctx, const gsc::stmt_foreach_ptr& stmt)
{
    process_stmt(ctx, stmt->pre_expr);

    for(auto& index : stmt->vars)
    {
        auto var1 = utils::string::va("var_%d", std::stoi(index));
        ctx->local_vars.push_back({ var1, static_cast<uint8_t>(std::stoi(index)), true });
        ctx->local_vars_create_count++;
    }

    stmt->ctx = std::make_unique<gsc::context>();
    ctx->transfer_decompiler(stmt->ctx);

    process_stmt(stmt->ctx, stmt->stmt0);
    process_stmt(stmt->ctx, stmt->stmt);

    if(stmt->stmt.as_list->stmts.size() == 1 && !gsc::node::is_special_stmt(stmt->stmt.as_list->stmts.at(0)))
    {
        stmt->stmt = std::move(stmt->stmt.as_list->stmts.back());
    }

    stmt->array_expr = std::move(stmt->pre_expr.as_list->stmts[0].as_assign->expr->rvalue);
    stmt->value_expr = std::move(stmt->stmt0.as_assign->expr->lvalue);
    stmt->key_expr = std::move(stmt->pre_expr.as_list->stmts[1].as_assign->expr->lvalue);
}

void decompiler::process_stmt_switch(const gsc::context_ptr& ctx, const gsc::stmt_switch_ptr& stmt)
{
    process_expr(ctx, stmt->expr);

    stmt->ctx = std::make_unique<gsc::context>();
    ctx->transfer_decompiler(stmt->ctx);

    process_stmt_cases(stmt->ctx, stmt->stmt);

    ctx->append_decompiler(stmt->ctx, true);
}

void decompiler::process_stmt_cases(const gsc::context_ptr& ctx, const gsc::stmt_list_ptr& stmt)
{
    std::vector<gsc::context*> childs;

    for(auto& entry : stmt->stmts)
    {
        if(entry.as_node->type == gsc::node_t::stmt_case)
        {
            entry.as_case->ctx = std::make_unique<gsc::context>();
            ctx->transfer_decompiler(entry.as_case->ctx);

            process_stmt_list(entry.as_case->ctx, entry.as_case->stmt);

            if(entry.as_case->ctx->abort == gsc::abort_t::abort_break)
            {
                childs.push_back(entry.as_case->ctx.get());
            }
        }
        else if(entry.as_node->type == gsc::node_t::stmt_default)
        {
            entry.as_default->ctx = std::make_unique<gsc::context>();
            ctx->transfer_decompiler(entry.as_default->ctx);

            process_stmt_list(entry.as_default->ctx, entry.as_default->stmt);

            if(entry.as_default->ctx->abort == gsc::abort_t::abort_break)
            {
                childs.push_back(entry.as_default->ctx.get());
            }
        }
    }

    ctx->append(childs);
}

void decompiler::process_stmt_break(const gsc::context_ptr& ctx, const gsc::stmt_break_ptr& stmt)
{
    ctx->abort = gsc::abort_t::abort_break;
}

void decompiler::process_stmt_return(const gsc::context_ptr& ctx, const gsc::stmt_return_ptr& stmt)
{
    if(stmt->expr.as_node->type == gsc::node_t::null)
    {
        return; 
    }

    process_expr(ctx, stmt->expr);
}

void decompiler::process_expr(const gsc::context_ptr& ctx, gsc::expr_ptr& expr)
{
    switch(expr.as_node->type)
    {
        case gsc::node_t::expr_increment:        process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_decrement:        process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_equal:     process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_add:       process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_sub:       process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_mult:      process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_div:       process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_mod:       process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_shift_left:   process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_shift_right:  process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_bitwise_or:   process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_bitwise_and:  process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_assign_bitwise_exor: process_expr_assign(ctx, expr.as_assign); break;
        case gsc::node_t::expr_and:              process_expr_and(ctx, expr.as_and); break;
        case gsc::node_t::expr_or:               process_expr_or(ctx, expr.as_or); break;
        case gsc::node_t::expr_equality:         process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_inequality:       process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_less:             process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_greater:          process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_less_equal:       process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_greater_equal:    process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_bitwise_or:       process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_bitwise_and:      process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_bitwise_exor:     process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_shift_left:       process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_shift_right:      process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_add:              process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_sub:              process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_mult:             process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_div:              process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_mod:              process_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_t::expr_complement:       process_expr_complement(ctx, expr.as_complement); break;
        case gsc::node_t::expr_not:              process_expr_not(ctx, expr.as_not); break;
        case gsc::node_t::expr_call:             process_expr_call(ctx, expr.as_call); break;
        case gsc::node_t::expr_function:         process_expr_function(ctx, expr.as_function); break;
        case gsc::node_t::expr_add_array:        process_expr_add_array(ctx, expr.as_add_array); break;
        case gsc::node_t::expr_array:            process_array_variable(ctx, expr.as_array); break;
        case gsc::node_t::expr_field:            process_field_variable(ctx, expr.as_field); break;
        case gsc::node_t::expr_size:             process_expr_size(ctx, expr.as_size); break;
        case gsc::node_t::data_name:             process_local_variable(ctx, expr.as_name); break;
        case gsc::node_t::data_vector:           process_vector(ctx, expr.as_vector); break;
        case gsc::node_t::asm_create:            process_var_create(ctx, expr); break;
        case gsc::node_t::asm_access:            process_var_access(ctx, expr); break;
        default: break;
    }
}

void decompiler::process_expr_assign(const gsc::context_ptr& ctx, gsc::expr_assign_ptr& expr)
{
    if(expr->type == gsc::node_t::expr_increment)
    {
        process_expr(ctx, expr->lvalue);
    }
    else if(expr->type == gsc::node_t::expr_decrement)
    {
        process_expr(ctx, expr->lvalue);
    }
    else
    {
        process_expr(ctx, expr->rvalue);
        process_expr(ctx, expr->lvalue);

        if(expr->type == gsc::node_t::expr_assign_equal)
        {
            switch(expr->rvalue.as_node->type)
            {
                case gsc::node_t::expr_bitwise_or:
                    if(expr->lvalue == expr->rvalue.as_bitwise_or->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_bitwise_or>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                case gsc::node_t::expr_bitwise_and:
                    if(expr->lvalue == expr->rvalue.as_bitwise_and->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_bitwise_and>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                case gsc::node_t::expr_bitwise_exor:
                    if(expr->lvalue == expr->rvalue.as_bitwise_exor->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_bitwise_exor>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                case gsc::node_t::expr_shift_left:
                    if(expr->lvalue == expr->rvalue.as_shift_left->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_shift_left>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                case gsc::node_t::expr_shift_right:
                    if(expr->lvalue == expr->rvalue.as_shift_right->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_shift_right>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                case gsc::node_t::expr_add:
                    if(expr->lvalue == expr->rvalue.as_add->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_add>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                case gsc::node_t::expr_sub:
                    if(expr->lvalue == expr->rvalue.as_sub->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_sub>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                case gsc::node_t::expr_mult:
                    if(expr->lvalue == expr->rvalue.as_mult->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_mult>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                case gsc::node_t::expr_div:
                    if(expr->lvalue == expr->rvalue.as_div->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_div>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                case gsc::node_t::expr_mod:
                    if(expr->lvalue == expr->rvalue.as_mod->lvalue)
                        expr = std::make_unique<gsc::node_expr_assign_mod>(std::move(expr->lvalue), std::move(expr->rvalue.as_mod->rvalue));
                    break;
                default:
                    break;
            }
        }
    }
}

void decompiler::process_expr_binary(const gsc::context_ptr& ctx, const gsc::expr_binary_ptr& expr)
{
    process_expr(ctx, expr->lvalue);
    process_expr(ctx, expr->rvalue);

    auto prec = expr->lvalue.as_node->precedence();

    if(prec && prec < expr->precedence())
    {
        expr->lvalue = expr_ptr(std::make_unique<gsc::node_expr_paren>(std::move(expr->lvalue)));
    }

    prec = expr->rvalue.as_node->precedence();

    if(prec && prec < expr->precedence() || (prec == expr->precedence() && expr->type == expr->rvalue.as_node->type))
    {
        expr->rvalue = expr_ptr(std::make_unique<gsc::node_expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_and(const gsc::context_ptr& ctx, const gsc::expr_and_ptr& expr)
{
    process_expr(ctx, expr->lvalue);
    process_expr(ctx, expr->rvalue);

    auto prec = expr->lvalue.as_node->precedence();

    if(prec && prec < expr->precedence())
    {
        expr->lvalue = expr_ptr(std::make_unique<gsc::node_expr_paren>(std::move(expr->lvalue)));
    }

    prec = expr->rvalue.as_node->precedence();

    if(prec && prec < expr->precedence() || (prec == expr->precedence() && expr->type == expr->rvalue.as_node->type))
    {
        expr->rvalue = expr_ptr(std::make_unique<gsc::node_expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_or(const gsc::context_ptr& ctx, const gsc::expr_or_ptr& expr)
{
    process_expr(ctx, expr->lvalue);
    process_expr(ctx, expr->rvalue);
}

void decompiler::process_expr_complement(const gsc::context_ptr& ctx, const gsc::expr_complement_ptr& expr)
{
    process_expr(ctx, expr->rvalue);

    if(expr->rvalue.as_node->is_binary())
    {
        expr->rvalue = expr_ptr(std::make_unique<gsc::node_expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_not(const gsc::context_ptr& ctx, const gsc::expr_not_ptr& expr)
{
    process_expr(ctx, expr->rvalue);

    if(expr->rvalue.as_node->is_binary())
    {
        expr->rvalue = expr_ptr(std::make_unique<gsc::node_expr_paren>(std::move(expr->rvalue)));
    }
}

void decompiler::process_expr_call(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr)
{
    if(expr->func.as_node->type == gsc::node_t::expr_call_pointer)
    {
        process_expr_call_pointer(ctx, expr);
    }
    else
    {
        process_expr_call_function(ctx, expr);
    }
}

void decompiler::process_expr_call_pointer(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr)
{
    process_expr_arguments(ctx, expr->func.as_pointer->args);

    if(expr->obj.as_node->type != gsc::node_t::null)
        process_expr(ctx, expr->obj);

    process_expr(ctx, expr->func.as_pointer->expr);
}

void decompiler::process_expr_call_function(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr)
{
    process_expr_arguments(ctx, expr->func.as_func->args);

    if(expr->obj.as_node->type != gsc::node_t::null)
        process_expr(ctx, expr->obj);
}

void decompiler::process_expr_arguments(const gsc::context_ptr& ctx, const gsc::expr_arguments_ptr& args)
{
    for(auto i = args->list.size(); i > 0; i--)
    {
        process_expr(ctx, args->list.at(i - 1));
    }
}

void decompiler::process_expr_function(const gsc::context_ptr& ctx, const gsc::expr_function_ptr& expr)
{
    return;
}

void decompiler::process_expr_add_array(const gsc::context_ptr& ctx, const gsc::expr_add_array_ptr& expr)
{
    for(auto& arg : expr->args->list)
    {
        process_expr(ctx, arg);
    }
}

void decompiler::process_expr_size(const gsc::context_ptr& ctx, const gsc::expr_size_ptr& expr)
{
    process_expr(ctx, expr->obj);
}

void decompiler::process_array_variable(const gsc::context_ptr& ctx, const gsc::expr_array_ptr& expr)
{
    process_expr(ctx, expr->key);
    process_expr(ctx, expr->obj);
}

void decompiler::process_field_variable(const gsc::context_ptr& ctx, const gsc::expr_field_ptr& expr)
{
    process_expr(ctx, expr->obj);
}

void decompiler::process_local_variable(const gsc::context_ptr& ctx, const gsc::name_ptr& expr)
{
    return;
}

void decompiler::process_vector(const gsc::context_ptr& ctx, const gsc::vector_ptr& vec)
{
    process_expr(ctx, vec->z);
    process_expr(ctx, vec->y);
    process_expr(ctx, vec->x);
}

void decompiler::process_var_create(const gsc::context_ptr& ctx, gsc::expr_ptr& expr, bool fromstmt)
{
    if(fromstmt)
    {
        auto var = utils::string::va("var_%d", std::stoi(expr.as_asm_create->index));
        ctx->local_vars.push_back({ var, static_cast<uint8_t>(std::stoi(expr.as_asm_create->index)), true });
        ctx->local_vars_create_count++;
    }
    else
    {
        for(auto& entry : expr.as_asm_create->vars)
        {
            ctx->local_vars.push_back({ utils::string::va("var_%d", std::stoi(entry)), static_cast<uint8_t>(std::stoi(entry)), true });
            ctx->local_vars_create_count++;
        }

        auto var = utils::string::va("var_%d", std::stoi(expr.as_asm_create->index));
        ctx->local_vars.push_back({ var, static_cast<uint8_t>(std::stoi(expr.as_asm_create->index)), true });
        ctx->local_vars_create_count++;

        expr = gsc::expr_ptr(std::make_unique<gsc::node_name>(var));
    }
}

void decompiler::process_var_access(const gsc::context_ptr& ctx, gsc::expr_ptr& expr)
{
    if(ctx->local_vars.size() <= std::stoi(expr.as_asm_access->index))
    {
        printf("WARNING: bad local var access\n");
    }
    else
    {
        auto var = ctx->local_vars.at(ctx->local_vars.size() - 1 - std::stoi(expr.as_asm_access->index)).name;
        expr = gsc::expr_ptr(std::make_unique<gsc::node_name>(var));
    }
}

void decompiler::process_var_remove(const gsc::context_ptr& ctx, const gsc::asm_remove_ptr& expr)
{
    ctx->local_vars_public_count = ctx->local_vars.size() - std::stoi(expr->index);
}

} // namespace xsk::gsc::h2
