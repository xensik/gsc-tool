// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"
#include "decompiler.hpp"
#include "context.hpp"
#include "utils/string.hpp"

namespace xsk::arc
{

decompiler::decompiler(context const* ctx) : ctx_{ ctx }
{
}

auto decompiler::decompile(assembly const& data) -> program::ptr
{
    program_ = make_program();

    for (auto it = data.includes.rbegin(); it != data.includes.rend(); it++)
    {
        program_->includes.push_back(make_include(location{}, make_expr_path(location{}, *it)));
    }

    for (auto const& func : data.functions)
    {
        decompile_function(*func);
    }

    return std::move(program_);
}

auto decompiler::decompile_function(function const& func) -> void
{
    expr_labels_.clear();
    tern_labels_.clear();
    locals_.clear();
    vars_.clear();
    labels_ = func.labels;
    in_waittill_ = false;
    retbool_ = true;
    locs_ = {};
    stack_ = {};

    auto loc = location{ nullptr, static_cast<location::counter_type>(func.index) };
    auto space = make_expr_identifier(loc, func.space);
    auto name = make_expr_identifier(loc, func.name);
    auto prms = make_expr_parameters(loc);
    auto body = make_stmt_comp(loc, make_stmt_list(loc));
    auto flags = static_cast<export_flags>(func.flags);
    func_ = make_decl_function(loc, std::move(space), std::move(name), std::move(prms), std::move(body), flags);

    for (auto const& inst : func.instructions)
    {
        decompile_instruction(*inst, &inst == &func.instructions.back());
    }

    for (auto i = 0u; i < func.params; i++)
    {
        func_->params->list.push_back(expr{ make_expr_identifier(loc, locals_.at(locals_.size() - 1 - i)) });
    }

    if (!stack_.empty())
    {
        throw decomp_error("stack isn't empty at function end");
    }

    auto& list = func_->body->block->list;
    locs_.end = fmt::format("loc_{:X}", list.back().loc().begin.line + 1);

    decompile_statements(*func_->body->block);

    if (!list.empty() && list.back() == node::stmt_return)
    {
        if (list.back().as_return->value == node::null)
            list.pop_back();
    }

    process_function(*func_);

    program_->declarations.push_back(decl{ std::move(func_) });
}

auto decompiler::decompile_instruction(instruction const& inst, bool last) -> void
{
    decompile_expressions(inst);

    auto loc = location{ nullptr, static_cast<location::counter_type>(inst.index) };

    switch (inst.opcode)
    {
        case opcode::OP_End:
        {
            retbool_ = !last ? false : retbool_;
            func_->body->block->list.push_back(stmt{ make_stmt_return(loc, expr{ make_node(loc) }) });
            break;
        }
        case opcode::OP_Return:
        {
            auto value = expr{ std::move(stack_.top()) }; stack_.pop();
            retbool_ = !value.as_node->is_boolean() ? false : retbool_;
            func_->body->block->list.push_back(stmt{ make_stmt_return(value.loc(), std::move(value)) });
            break;
        }
        case opcode::OP_GetZero:
        {
            stack_.push(make_expr_integer(loc, "0"));
            break;
        }
        case opcode::OP_GetByte:
        case opcode::OP_GetUnsignedShort:
        {
            stack_.push(make_expr_integer(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetNegByte:
        case opcode::OP_GetNegUnsignedShort:
        {
            stack_.push(make_expr_integer(loc, "-" + inst.data[0]));
            break;
        }
        case opcode::OP_GetInteger:
        {
            if (inst.data.size() == 2)
            {
                auto found = false;

                for (auto i = program_->declarations.rbegin(); i != program_->declarations.rend(); i++)
                {
                    if (*i == node::decl_usingtree)
                    {
                        found = (i->as_usingtree->name->value == inst.data[0]);
                        break;
                    }
                }

                if (!found)
                {
                    auto dec = make_decl_usingtree(loc, make_expr_string(loc, inst.data[0]));
                    program_->declarations.push_back(decl{ std::move(dec) });
                }

                stack_.push(make_expr_animtree(loc));
            }
            else
            {
                stack_.push(make_expr_integer(loc, inst.data[0]));
            }
            break;
        }
        case opcode::OP_GetFloat:
        {
            stack_.push(make_expr_float(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetVector:
        {
            auto x = expr{ make_expr_float(loc, inst.data[0]) };
            auto y = expr{ make_expr_float(loc, inst.data[1]) };
            auto z = expr{ make_expr_float(loc, inst.data[2]) };
            stack_.push(make_expr_vector(loc, std::move(x), std::move(y), std::move(z)));
            break;
        }
        case opcode::OP_GetString:
        {
            stack_.push(make_expr_string(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetIString:
        {
            stack_.push(make_expr_istring(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetUndefined:
        {
            stack_.push(make_expr_undefined(loc));
            break;
        }
        case opcode::OP_EmptyArray:
        {
            stack_.push(make_expr_empty_array(loc));
            break;
        }
        case opcode::OP_GetClasses:
        case opcode::OP_GetClassesObject:
        {
            stack_.push(make_expr_classes(loc));
            break;
        }
        case opcode::OP_GetWorld:
        case opcode::OP_GetWorldObject:
        {
            stack_.push(make_expr_world(loc));
            break;
        }
        case opcode::OP_GetLevel:
        case opcode::OP_GetLevelObject:
        {
            stack_.push(make_expr_level(loc));
            break;
        }
        case opcode::OP_GetAnim:
        case opcode::OP_GetAnimObject:
        {
            stack_.push(make_expr_anim(loc));
            break;
        }
        case opcode::OP_GetSelf:
        case opcode::OP_GetSelfObject:
        {
            stack_.push(make_expr_self(loc));
            break;
        }
        case opcode::OP_GetGame:
        case opcode::OP_GetGameRef:
        {
            stack_.push(make_expr_game(loc));
            break;
        }
        case opcode::OP_GetAnimation:
        {
            auto found = false;

            for (auto i = program_->declarations.rbegin(); i != program_->declarations.rend(); i++)
            {
                if (*i == node::decl_usingtree)
                {
                    found = (i->as_usingtree->name->value == inst.data[0]);
                    break;
                }
            }

            if (!found)
            {
                auto dec = make_decl_usingtree(loc, make_expr_string(loc, inst.data[0]));
                program_->declarations.push_back(decl{ std::move(dec) });
            }

            stack_.push(make_expr_animation(loc, inst.data[1]));
            break;
        }
        case opcode::OP_GetFunction:
        {
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);
            stack_.push(make_expr_reference(loc, std::move(path), std::move(name)));
            break;
        }
        case opcode::OP_SafeCreateLocalVariables:
        {
            for (const auto& entry : inst.data)
                locals_.insert(locals_.begin(), entry);

            break;
        }
        case opcode::OP_EvalLocalVariableCached:
        {
            stack_.push(make_expr_identifier(loc, locals_.at(std::stoi(inst.data[0]))));
            break;
        }
        case opcode::OP_EvalArray:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto key = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_array(key.loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalLocalArrayRefCached:
        {
            auto key = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ make_expr_identifier(loc, locals_.at(std::stoi(inst.data[0]))) };
            stack_.push(make_expr_array(key.loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalArrayRef:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto key = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_array(key.loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_ClearArray:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto key = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = key.loc();
            auto lvalue = expr{ make_expr_array(loc, std::move(obj), std::move(key)) };
            auto rvalue = expr{ make_expr_undefined(loc) };
            auto exp = expr{ make_expr_assign_equal(loc, std::move(lvalue), std::move(rvalue)) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_EvalFieldVariable:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(obj.loc(), std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalFieldVariableRef:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(obj.loc(), std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_ClearFieldVariable:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();
            auto name = make_expr_identifier(loc, inst.data[0]);
            auto field = expr{ make_expr_field(loc, std::move(obj), std::move(name)) };
            auto undef = expr{ make_expr_undefined(loc) };
            auto exp = expr{ make_expr_assign_equal(loc, std::move(field), std::move(undef)) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        {
            stack_.push(make_expr_identifier(loc, locals_.at(std::stoi(inst.data[0]))));
            break;
        }
        case opcode::OP_ClearParams:
        {
            if (in_waittill_)
            {
                auto args = make_expr_arguments(loc);
                auto arg = std::move(stack_.top()); stack_.pop();

                while (arg->kind() != node::stmt_waittill)
                {
                    args->list.push_back(std::move(arg));
                    arg = std::move(stack_.top()); stack_.pop();
                }

                if (arg->kind() == node::stmt_waittill)
                {
                    std::reverse(args->list.begin(), args->list.end());
                    reinterpret_cast<stmt_waittill*>(arg.get())->args = std::move(args);
                    in_waittill_ = false;
                }

                func_->body->block->list.push_back(stmt{ std::move(arg) });
            }
            break;
        }
        case opcode::OP_EvalLocalVariableRefCached:
        {
            stack_.push(make_expr_identifier(loc, locals_.at(std::stoi(inst.data[0]))));
            break;
        }
        case opcode::OP_SetVariableField:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = rvalue.loc();
            auto exp = expr{ make_expr_assign_equal(loc, std::move(lvalue), std::move(rvalue)) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_CallBuiltin:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_CallBuiltinMethod:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_Wait:
        {
            auto exp = expr{ std::move(stack_.top()) }; stack_.pop();
            func_->body->block->list.push_back(stmt{ make_stmt_wait(exp.loc(), std::move(exp)) });
            break;
        }
        case opcode::OP_WaitTillFrameEnd:
        {
            func_->body->block->list.push_back(stmt{ make_stmt_waittillframeend(loc) });
            break;
        }
        case opcode::OP_PreScriptCall:
        {
            stack_.push(make_asm_prescriptcall(loc));
            break;
        }
        case opcode::OP_ScriptFunctionCall:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_ScriptFunctionCallPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_call(loc, call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_ScriptMethodCall:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_ScriptMethodCallPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_ScriptThreadCall:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_ScriptThreadCallPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = func.loc();

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_call(loc, call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_ScriptMethodThreadCall:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_ScriptMethodThreadCallPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_prescriptcall)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_DecTop:
        {
            if (stack_.top()->kind() != node::expr_new)
            {
                auto exp = expr{ std::move(stack_.top()) }; stack_.pop();
                func_->body->block->list.push_back(stmt{ make_stmt_call(exp.loc(), std::move(exp)) });  
            }

            break;
        }
        case opcode::OP_BoolNot:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_not(lvalue.loc(), std::move(lvalue)));
            break;
        }
        case opcode::OP_BoolComplement:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_complement(lvalue.loc(), std::move(lvalue)));
            break;
        }
        case opcode::OP_JumpOnTrue:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = lvalue.loc();

            if (inst.index > resolve_label(inst.data[0]))
            {
                func_->body->block->list.push_back(stmt{ make_asm_jmp_cond(loc, std::move(lvalue), inst.data[0]) });
            }
            else
            {
                auto test = expr{ make_expr_not(loc, std::move(lvalue)) };
                func_->body->block->list.push_back(stmt{ make_asm_jmp_cond(loc, std::move(test), inst.data[0]) });
            }
            break;
        }
        case opcode::OP_JumpOnFalse:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = lvalue.loc();

            if (inst.index > resolve_label(inst.data[0]))
            {
                auto test = expr{ make_expr_not(loc, std::move(lvalue)) };
                func_->body->block->list.push_back(stmt{ make_asm_jmp_cond(loc, std::move(test), inst.data[0]) });
            }
            else
            {
                func_->body->block->list.push_back(stmt{ make_asm_jmp_cond(lvalue.loc(), std::move(lvalue), inst.data[0]) });
            }
            break;
        }
        case opcode::OP_JumpOnTrueExpr:
        {
            auto test = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_asm_jmp_true(test.loc(), std::move(test), inst.data[0]));
            expr_labels_.push_back(inst.data[0]);
            break;
        }
        case opcode::OP_JumpOnFalseExpr:
        {
            auto test = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_asm_jmp_false(test.loc(), std::move(test), inst.data[0]));
            expr_labels_.push_back(inst.data[0]);
            break;
        }
        case opcode::OP_Jump:
        {
            func_->body->block->list.push_back(stmt{ make_asm_jmp(loc, inst.data[0]) });
            if (stack_.size() != 0) tern_labels_.push_back(inst.data[0]);
            break;
        }
        case opcode::OP_JumpBack:
        {
            func_->body->block->list.push_back(stmt{ make_asm_jmp_back(loc, inst.data[0]) });
            break;
        }
        case opcode::OP_Inc:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = lvalue.loc();
            auto exp = expr{ make_expr_increment(lvalue.loc(), std::move(lvalue), false) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_Dec:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = lvalue.loc();
            auto exp = expr{ make_expr_decrement(loc, std::move(lvalue), false) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_Bit_Or:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_bitwise_or(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_Bit_Xor:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_bitwise_exor(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_Bit_And:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_bitwise_and(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_SuperEqual:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_super_equal(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_SuperNotEqual:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_super_not_equal(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_Equal:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_equality(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_NotEqual:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_inequality(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_LessThan:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_less(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_GreaterThan:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_greater(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_LessThanOrEqualTo:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_less_equal(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_GreaterThanOrEqualTo:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_greater_equal(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_ShiftLeft:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_shift_left(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_ShiftRight:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_shift_right(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_Plus:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_add(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_Minus:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_sub(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_Multiply:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_mul(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_Divide:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_div(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_Modulus:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_mod(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_SizeOf:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_size(lvalue.loc(), std::move(lvalue)));
            break;
        }
        case opcode::OP_WaitTillMatch:
        {
            auto args = make_expr_arguments(loc);
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto event = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = event.loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto arg = std::move(stack_.top()); stack_.pop();
                loc = arg->loc();
                args->list.push_back(std::move(arg));
            }

            func_->body->block->list.push_back(stmt{ make_stmt_waittillmatch(loc, std::move(obj), std::move(event), std::move(args)) });
            break;
        }
        case opcode::OP_WaitTill:
        {
            auto args = make_expr_arguments(loc);
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto event = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_stmt_waittill(event.loc(), std::move(obj), std::move(event), std::move(args)));
            in_waittill_ = true;
            break;
        }
        case opcode::OP_Notify:
        {
            auto args = make_expr_arguments(loc);
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto event = expr{ std::move(stack_.top()) }; stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ((ctx_->props() & props::version2) ? node::asm_prescriptcall : node::asm_voidcodepos))
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            func_->body->block->list.push_back(stmt{ make_stmt_notify(loc, std::move(obj), std::move(event), std::move(args)) });
            break;
        }
        case opcode::OP_EndOn:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto event = expr{ std::move(stack_.top()) }; stack_.pop();
            func_->body->block->list.push_back(stmt{ make_stmt_endon(event.loc(), std::move(obj), std::move(event)) });
            break;
        }
        case opcode::OP_VoidCodePos:
        {
            stack_.push(make_asm_voidcodepos(loc));
            break;
        }
        case opcode::OP_Switch:
        {
            auto test = expr{ std::move(stack_.top()) }; stack_.pop();
            func_->body->block->list.push_back(stmt{ make_asm_switch(test.loc(), std::move(test), inst.data[0]) });
            break;
        }
        case opcode::OP_EndSwitch:
        {
            func_->body->block->list.push_back(stmt{ make_asm_endswitch(loc, inst.data) });
            break;
        }
        case opcode::OP_Vector:
        {
            auto x = expr{ std::move(stack_.top()) }; stack_.pop();
            auto y = expr{ std::move(stack_.top()) }; stack_.pop();
            auto z = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_vector(z.loc(), std::move(x), std::move(y), std::move(z)));
            break;
        }
        case opcode::OP_GetHash:
        {
            stack_.push(make_expr_hash(loc, inst.data[0]));
            break;
        }
        case opcode::OP_RealWait:
        {
            auto exp = expr{ std::move(stack_.top()) }; stack_.pop();
            func_->body->block->list.push_back(stmt{ make_stmt_realwait(exp.loc(), std::move(exp)) });
            break;
        }
        case opcode::OP_VectorConstant:
        {
            auto flags = static_cast<std::uint8_t>(std::stoi(inst.data[0]));
            auto x = expr{ make_expr_float(loc, (flags & 0x20) ? "1" : (flags & 0x10) ? "-1" : "0") };
            auto y = expr{ make_expr_float(loc, (flags & 0x08) ? "1" : (flags & 0x04) ? "-1" : "0") };
            auto z = expr{ make_expr_float(loc, (flags & 0x02) ? "1" : (flags & 0x01) ? "-1" : "0") };
            stack_.push(make_expr_vector(loc, std::move(x), std::move(y), std::move(z)));
            break;
        }
        case opcode::OP_IsDefined:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_isdefined(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_VectorScale:
        {
            auto arg1 = std::move(stack_.top()); stack_.pop();
            auto arg2 = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_vectorscale(arg2->loc(), std::move(arg1), std::move(arg2)));
            break;
        }
        case opcode::OP_AnglesToUp:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_anglestoup(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_AnglesToRight:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_anglestoright(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_AnglesToForward:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_anglestoforward(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_AngleClamp180:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_angleclamp180(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_VectorToAngles:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_vectortoangles(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_Abs:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_abs(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetTime:
        {
            stack_.push(make_expr_gettime(loc));
            break;
        }
        case opcode::OP_GetDvar:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_getdvar(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarInt:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_getdvarint(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarFloat:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_getdvarfloat(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarVector:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_getdvarvector(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarColorRed:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_getdvarcolorred(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarColorGreen:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_getdvarcolorgreen(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarColorBlue:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_getdvarcolorblue(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarColorAlpha:
        {
            auto arg = std::move(stack_.top()); stack_.pop();
            stack_.push(make_expr_getdvarcoloralpha(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_FirstArrayKey:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, "getfirstarraykey");
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();
            args->list.push_back(std::move(var));
            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_NextArrayKey:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, "getnextarraykey");
            auto var = std::move(stack_.top()); stack_.pop();
            args->list.push_back(std::move(var));
            var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();
            args->list.push_back(std::move(var));
            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_LevelEvalFieldVariable:
        case opcode::OP_LevelEvalFieldVariableRef:
        {
            auto obj = expr{ make_expr_level(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_SelfEvalFieldVariable:
        case opcode::OP_SelfEvalFieldVariableRef:
        {
            auto obj = expr{ make_expr_self(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_DevblockBegin:
        {
            func_->body->block->list.push_back(stmt{ make_asm_dev(loc, inst.data[0]) });
            break;
        }
        case opcode::OP_New:
        {
            stack_.push(make_expr_new(loc, make_expr_identifier(loc, inst.data[0])));
            break;
        }
        case opcode::OP_ScriptFunctionCallClass:
        {
            if (stack_.top()->kind() != node::expr_new)
            {
                auto args = make_expr_arguments(loc);
                auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();

                while (var->kind() != node::asm_prescriptcall)
                {
                    args->list.push_back(std::move(var));
                    var = std::move(stack_.top()); stack_.pop();
                    loc = var->loc();
                }

                stack_.push(make_expr_call(loc, call{ make_expr_member(loc, std::move(obj), make_expr_identifier(loc, inst.data[0]), std::move(args), call::mode::normal) }));
            }
            break;
        }
        case opcode::OP_ScriptThreadCallClass:
        {
            if (stack_.top()->kind() != node::expr_new)
            {
                auto args = make_expr_arguments(loc);
                auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();

                while (var->kind() != node::asm_prescriptcall)
                {
                    args->list.push_back(std::move(var));
                    var = std::move(stack_.top()); stack_.pop();
                    loc = var->loc();
                }

                stack_.push(make_expr_call(loc, call{ make_expr_member(loc, std::move(obj), make_expr_identifier(loc, inst.data[0]), std::move(args), call::mode::thread) }));
            }
            break;
        }
        case opcode::OP_CheckClearParams:
        case opcode::OP_CastFieldObject:
        case opcode::OP_CastBool:
        case opcode::OP_SafeDecTop:
            break;
        case opcode::OP_CreateLocalVariable:
        case opcode::OP_RemoveLocalVariables:
        case opcode::OP_SafeSetVariableFieldCached:
        case opcode::OP_ProfileStart:
        case opcode::OP_ProfileStop:
        case opcode::OP_Nop:
        case opcode::OP_Abort:
        case opcode::OP_Object:
        case opcode::OP_ThreadObject:
        case opcode::OP_EvalLocalVariable:
        case opcode::OP_EvalLocalVariableRef:
        case opcode::OP_DevblockEnd:
        case opcode::OP_GetUintptr:
        case opcode::OP_GetAPIFunction:
        case opcode::OP_EvalLocalVariableCachedDebug:
        case opcode::OP_EvalLocalVariableRefCachedDebug:
        default:
            throw decomp_error(fmt::format("unhandled opcode {}", ctx_->opcode_name(inst.opcode)));
    }
}

auto decompiler::decompile_expressions(instruction const& inst) -> void
{
    auto const itr = labels_.find(inst.index);

    if (itr == labels_.end())
        return;

    for (auto const& exp : expr_labels_)
    {
        if (exp == itr->second)
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto jump = std::move(stack_.top()); stack_.pop();
            auto loc = jump->loc();

            if (jump->kind() == node::asm_jmp_true)
            {
                auto lvalue = std::move(reinterpret_cast<asm_jmp_true*>(jump.get())->test);
                stack_.push(make_expr_or(loc, std::move(lvalue), std::move(rvalue)));
            }
            else if (jump->kind() == node::asm_jmp_false)
            {
                auto lvalue = std::move(reinterpret_cast<asm_jmp_false*>(jump.get())->test);
                stack_.push(make_expr_and(loc, std::move(lvalue), std::move(rvalue)));
            }
            else
            {
                throw decomp_error("invalid conditional expression");
            }
        }
    }

    for (auto const& tern : tern_labels_)
    {
        if (tern == itr->second)
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();

            func_->body->block->list.pop_back();
            auto stm = std::move(func_->body->block->list.back());
            func_->body->block->list.pop_back();

            if (stm == node::asm_jmp_cond)
            {
                auto loc = stm.as_cond->loc();
                stack_.push(make_expr_ternary(loc, std::move(stm.as_cond->test), std::move(lvalue), std::move(rvalue)));
            }
            else
            {
                throw decomp_error("invalid ternary expression");
            }
        }
    }
}

auto decompiler::decompile_statements(stmt_list& stm) -> void
{
    decompile_infinites(stm);
    decompile_loops(stm);
    decompile_switches(stm);
    decompile_ifelses(stm);
    decompile_aborts(stm);
    decompile_devblocks(stm);
}

auto decompiler::decompile_infinites(stmt_list& stm) -> void
{
    if (stm.list.empty())
        return;

    for (auto i = static_cast<i32>(stm.list.size() - 1); i > 0; i--)
    {
        if (stm.list.at(i) == node::asm_jmp)
        {
            if (stm.list.at(i).loc().begin.line < std::stol(stm.list.at(i).as_jump->value.substr(4), 0, 16))
                continue;

            if (stm.list.at(i).as_jump->value == locs_.cnt)
                continue;

            auto break_loc = last_location_index(stm, i) ? locs_.end : stm.list.at(i + 1).label();
            auto start = find_location_index(stm, stm.list.at(i).as_jump->value);

            if (stm.list.at(i - 1) == node::asm_jmp_cond && stm.list.at(i - 1).as_cond->value == break_loc)
            {
                continue;
            }
            else if (stm.list.at(start) != node::asm_jmp_cond)
            {
                decompile_inf(stm, start, i);
                i = stm.list.size();
            }
            else if (stm.list.at(start).as_cond->value != break_loc)
            {
                decompile_inf(stm, start, i);
                i = stm.list.size();
            }
            else if (stm.list.at(start).as_cond->value == break_loc)
            {
                decompile_loop(stm, start, i);
                i = stm.list.size();
            }
        }
    } 
}

auto decompiler::decompile_loops(stmt_list& stm) -> void
{
    for (auto i = 0u; i < stm.list.size(); i++)
    {
        auto& entry = stm.list.at(i);

        if (entry == node::asm_jmp_cond)
        {
            auto j = find_location_index(stm, entry.as_cond->value);

            if (j < i)
            {
                decompile_dowhile(stm, j, i);
                i = 0;
                continue;
            }

            j -= 1;

            if (stm.list.at(j) == node::asm_jmp)
            {
                if (stm.list.at(j).as_node->loc().begin.line < std::stol(stm.list.at(j).as_jump->value.substr(4), 0, 16))
                    continue;

                if (stm.list.at(i).loc().label() == stm.list.at(j).as_jump->value)
                {
                    decompile_loop(stm, i, j);
                    i = 0;
                }
            }
        }
    }
}

auto decompiler::decompile_switches(stmt_list& stm) -> void
{
    for (auto i = 0u; i < stm.list.size(); i++)
    {
        if (stm.list[i] == node::asm_switch)
        {
            auto end = find_location_index(stm, stm.list[i].as_asm_switch->value);
            decompile_switch(stm, i, end);
        }
    }
}

auto decompiler::decompile_ifelses(stmt_list& stm) -> void
{
    for (auto i = 0u; i < stm.list.size(); i++)
    {
        const auto& entry = stm.list.at(i);

        if (entry == node::asm_jmp_cond)
        {
            auto j = find_location_index(stm, entry.as_cond->value) - 1;
            auto last_loc = locs_.end;

            if (stm.list.at(j) == node::asm_jmp)
            {
                // if block is a loop check break, continue
                if (stm.list.at(j).as_jump->value == locs_.cnt)
                {
                    //if its a while, continue jumps back
                    if (stm.list.at(j).as_node->loc().begin.line > std::stol(stm.list.at(j).as_jump->value.substr(4), 0, 16))
                    {
                        decompile_if(stm, i, j);
                    }
                    // a dowhile, for or foreach, check for if/else or if/continue
                    else if (j - i > 1 && stm.list.at(j - 1) == node::stmt_return)
                    {
                        // block ends with a return, so jump belows to if/else
                        decompile_ifelse(stm, i, j);
                    }
                    else if (j - i > 1 && stm.list.at(j - 1) == node::asm_jmp)
                    {
                        if (stm.list.at(j - 1).as_jump->value == locs_.brk)
                        {
                            // block ends with a break, so jump belows to if/else
                            decompile_ifelse(stm, i, j);
                        }
                        else if (stm.list.at(j - 1).as_jump->value == locs_.cnt)
                        {
                            // block ends with a continue, so jump belows to if/else
                            decompile_ifelse(stm, i, j);
                        }
                        else
                        {
                            // jump belows to if/continue
                            decompile_if(stm, i, j);
                        }
                    }
                    else
                    {
                        decompile_if(stm, i, j);
                    }
                }
                else if (stm.list.at(j).as_jump->value == locs_.brk)
                {
                    decompile_if(stm, i, j);
                }
                else if (stm.list.at(j).as_jump->value == locs_.end)
                {
                    if (find_location_reference(stm, i + 1, j, entry.as_cond->value))
                        decompile_if(stm, i, j);
                    else
                        decompile_ifelse(stm, i, j);
                }
                else if (stm.list.at(j).as_jump->value == entry.as_cond->value)
                {
                    if (find_location_reference(stm, i + 1, j, entry.as_cond->value))
                        decompile_if(stm, i, j);
                    else
                        decompile_ifelse(stm, i, j);
                }
                else
                {
                    decompile_ifelse(stm, i, j);
                }
            }
            else
            {
                decompile_if(stm, i, j);
            }
        }
    }
}

auto decompiler::decompile_aborts(stmt_list& stm) -> void
{
    for (auto i = static_cast<std::make_signed_t<std::size_t>>(stm.list.size() - 1); i >= 0; i--)
    {
        if (stm.list.at(i) == node::asm_jmp)
        {
            auto loc = stm.list.at(i).loc();
            auto jump_loc = stm.list.at(i).as_jump->value;

            if (jump_loc == locs_.brk)
            {
                stm.list.erase(stm.list.begin() + i);
                stm.list.insert(stm.list.begin() + i, stmt{ make_stmt_break(loc) });
            }
            else if (jump_loc == locs_.cnt)
            {
                stm.list.erase(stm.list.begin() + i);
                stm.list.insert(stm.list.begin() + i, stmt{ make_stmt_continue(loc) });
            }
            else
            {
                // fix for treyarch compiler bug: nested switch break locs are not preserved
                if (jump_loc != locs_.end)
                {
                    auto j = find_location_index(stm, jump_loc);

                    if (stm.list.at(j) == node::stmt_break)
                    {
                        stm.list.erase(stm.list.begin() + i);
                        stm.list.insert(stm.list.begin() + i, stmt{ make_stmt_break(loc) });

                        continue;
                    }
                }
                std::cout << "WARNING: unresolved jump to '" + jump_loc + "', maybe incomplete for loop\n";
            }
        }
    }  
}

auto decompiler::decompile_devblocks(stmt_list& stm) -> void
{
    for (auto i = 0u; i < stm.list.size(); i++)
    {
        if (stm.list.at(i) == node::asm_dev)
        {
            if (locs_.is_dev)
            {
                stm.list.erase(stm.list.begin() + i--);
                continue;
            }

            if (i + 1 < stm.list.size())
            {
                if (stm.list.at(i + 1) == node::asm_dev && stm.list.at(i + 1).as_asm_dev->value == stm.list.at(i).as_asm_dev->value)
                {
                    stm.list.erase(stm.list.begin() + i + 1);
                }
            }

            auto loc = stm.list.at(i).loc();
            auto end = find_location_index(stm, stm.list.at(i).as_asm_dev->value);

            auto save = locs_;
            locs_.end = stm.list.at(i).as_asm_dev->value;
            locs_.is_dev = true;

            stm.list.erase(stm.list.begin() + i);
            end -= 1;

            auto list_stmt = make_stmt_list(loc);

            for (auto j = i; j < end; j++)
            {
                list_stmt->list.push_back(std::move(stm.list[i]));
                stm.list.erase(stm.list.begin() + i);
            }

            decompile_statements(*list_stmt);
            locs_ = save;

            if (list_stmt->list.size() == 1 && list_stmt->list.at(0) == node::stmt_call)
            {
                const auto& st = list_stmt->list.at(0);

                if (st.as_call->value == node::expr_call && st.as_call->value.as_call->value == node::expr_function)
                {
                    if (st.as_call->value.as_call->value.as_function->name->value == "assert")
                    {
                        auto new_stmt = stmt{ make_stmt_call(loc, std::move(st.as_call->value)) };
                        stm.list.insert(stm.list.begin() + i, std::move(new_stmt));
                        continue;
                    }
                    
                }
            }

            auto new_stmt = stmt{ make_stmt_dev(loc, std::move(list_stmt)) };
            stm.list.insert(stm.list.begin() + i, std::move(new_stmt));
        }
    }
}

auto decompiler::decompile_if(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.end = stm.list[begin].as_cond->value;

    auto loc = stm.list[begin].loc();
    auto test = std::move(stm.list[begin].as_cond->test);

    stm.list.erase(stm.list.begin() + begin);

    auto body = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_if(loc, std::move(test), stmt{ make_stmt_comp(loc, std::move(body)) }) });
}

auto decompiler::decompile_ifelse(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.end = stm.list[end].label();

    auto loc = stm.list[begin].loc();
    auto test = std::move(stm.list[begin].as_cond->test);

    stm.list.erase(stm.list.begin() + begin);
    end--;

    auto body_if = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body_if->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body_if);
    locs_ = save;

    auto end_loc = stm.list[begin].as_jump->value;

    stm.list.erase(stm.list.begin() + begin);

    end = find_location_index(stm, end_loc);

    save = locs_;
    locs_.end = end_loc;

    auto body_else = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body_else->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body_else);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_ifelse(loc, std::move(test), stmt{ make_stmt_comp(loc, std::move(body_if)) }, stmt{ make_stmt_comp(loc, std::move(body_else)) }) });
}

auto decompiler::decompile_inf(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.brk = last_location_index(stm, end) ? locs_.end : stm.list[end + 1].label();
    locs_.end = stm.list[end].label();
    locs_.cnt = stm.list[end].label();

    auto loc = stm.list[begin].loc();

    stm.list.erase(stm.list.begin() + end);

    auto body = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_for(loc, stmt{ make_node(loc) }, expr{ make_node(loc) }, stmt{ make_node(loc) }, stmt{ make_stmt_comp(loc, std::move(body)) }) });
}

auto decompiler::decompile_loop(stmt_list& stm, usize begin, usize end) -> void
{
    if (ctx_->props() & props::version2 && (begin + 2 < end))
    {
        auto& last = stm.list.at(begin + 2);

        if (last == node::stmt_assign)
        {
            if (last.as_assign->value == node::expr_assign_equal)
            {
                auto& call = last.as_assign->value.as_assign_equal->rvalue;

                if (call == node::expr_call && call.as_call->value == node::expr_function)
                {
                    if (utils::string::to_lower(call.as_call->value.as_function->name->value) == "getnextarraykey")
                    {
                        auto ref = stm.list.at(begin).loc().label();

                        if (!find_location_reference(stm, 0, begin, ref))
                        {
                            decompile_foreach(stm, begin, end);
                            return;
                        }
                    }
                }
            }
        }
    }

    auto& last = stm.list.at(end - 1);

    if (last == node::stmt_assign)
    {
        if (last.as_assign->value == node::expr_assign_equal)
        {
            auto& call = last.as_assign->value.as_assign_equal->rvalue;

            if (call == node::expr_call && call.as_call->value == node::expr_function)
            {
                if (utils::string::to_lower(call.as_call->value.as_function->name->value) == "getnextarraykey")
                {
                    auto ref = stm.list.at(begin).loc().label();

                    if (!find_location_reference(stm, 0, begin, ref))
                    {
                        decompile_foreach(stm, begin, end);
                        return;
                    }
                }
            }
        }

        if (begin > 0) // while at func start
        {
            if (stm.list.at(begin - 1) == node::stmt_assign)
            {
                if (!lvalues_match(*stm.list.at(begin - 1).as_assign, *last.as_assign))
                {
                    decompile_while(stm, begin, end);
                    return;
                }

                auto ref1 = stm.list.at(end).loc().label();
                auto ref2 = stm.list.at(begin).loc().label();

                if (find_location_reference(stm, begin, end, ref1))
                {
                    // jump is referenced, not post-expr
                    decompile_while(stm, begin, end);
                    return;
                }
                else if (find_location_reference(stm, begin, end, ref2))
                {
                    // continue is at begin, not post-expr
                    decompile_while(stm, begin, end);
                    return;
                }
                else if (find_location_reference(stm, 0, begin, ref2))
                {
                    // begin is at condition, not pre-expr
                    decompile_while(stm, begin, end);
                    return;
                }
                else
                {
                    decompile_for(stm, begin, end);
                    return;
                }
            }
        }
    }

    decompile_while(stm, begin, end);
}

auto decompiler::decompile_while(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.end = stm.list[end].label();
    locs_.cnt = stm.list[begin].label();
    locs_.brk = stm.list[begin].as_cond->value;

    auto loc = stm.list[begin].loc();
    auto test = std::move(stm.list[begin].as_cond->test);

    end--;
    stm.list.erase(stm.list.begin() + begin);
    stm.list.erase(stm.list.begin() + end);

    auto body = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_while(loc, std::move(test), stmt{ make_stmt_comp(loc, std::move(body)) }) });
}

auto decompiler::decompile_dowhile(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.end = stm.list[end].label();
    locs_.cnt = stm.list[end].label();
    locs_.brk = last_location_index(stm, end) ? save.end : stm.list[end + 1].label();

    auto test = std::move(stm.list[end].as_cond->test);
    auto loc = stm.list[begin].loc();
    stm.list.erase(stm.list.begin() + end);

    auto body = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_dowhile(loc, std::move(test), stmt{ make_stmt_comp(loc, std::move(body)) }) });
}

auto decompiler::decompile_for(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.end = stm.list[end - 1].label();
    locs_.cnt = stm.list[end - 1].label();
    locs_.brk = stm.list[begin].as_cond->value;

    begin--;
    auto loc = stm.list[begin].loc();
    auto init = make_stmt_expr(loc, std::move(stm.list[begin].as_assign->value));
    stm.list.erase(stm.list.begin() + begin);

    auto test = std::move(stm.list[begin].as_cond->test);
    stm.list.erase(stm.list.begin() + begin);

    end -= 3;
    auto iter = make_stmt_expr(loc, std::move(stm.list[end].as_assign->value));
    stm.list.erase(stm.list.begin() + end);
    stm.list.erase(stm.list.begin() + end);

    auto body = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_for(loc, stmt { std::move(init) }, std::move(test), stmt { std::move(iter) }, stmt{ make_stmt_comp(loc, std::move(body)) }) });
}

auto decompiler::decompile_foreach(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.end = stm.list[end - 1].label();
    locs_.cnt = stm.list[end - 1].label();
    locs_.brk = stm.list[begin].as_cond->value;

    begin -= 2;

    auto loc = stm.list[begin].loc();
    auto container = std::move(stm.list[begin].as_assign->value.as_assign->rvalue);
    auto array = std::move(stm.list[begin].as_assign->value.as_assign->lvalue);
    stm.list.erase(stm.list.begin() + begin);

    auto key = std::move(stm.list[begin].as_assign->value.as_assign->lvalue);
    stm.list.erase(stm.list.begin() + begin);
    stm.list.erase(stm.list.begin() + begin);

    auto value = std::move(stm.list[begin].as_assign->value.as_assign->lvalue);
    stm.list.erase(stm.list.begin() + begin);

    end -= (ctx_->props() & props::version2) ? 6 : 5;

    if (ctx_->props() & props::version2)
        stm.list.erase(stm.list.begin() + begin);
    
    stm.list.erase(stm.list.begin() + end);
    stm.list.erase(stm.list.begin() + end);

    auto use_key = !key.as_identifier->value.starts_with("_k");

    if ((ctx_->props() & props::version2) && key.as_identifier->value.starts_with("_id_"))
        use_key = false;

    auto body = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_foreach(loc, std::move(container), std::move(value), std::move(array), std::move(key), stmt{ make_stmt_comp(loc, std::move(body)) }, use_key) });
}

auto decompiler::decompile_switch(stmt_list& stm, usize begin, usize end) -> void
{
    auto const& data = stm.list[end].as_asm_endswitch->data;
    auto const count = std::stoul(data[0]);

    if (count)
    {
        auto type = static_cast<switch_type>(std::stoul(data.back()));
        auto index = 1u;

        for (auto i = 0u; i < count; i++)
        {
            if (data[index] == "case")
            {
                auto j = find_location_index(stm, data[index + 2]);
                auto loc = stm.list[j].loc();
                auto exp = (type == switch_type::integer) ? expr{ make_expr_integer(loc, data[index + 1]) } : expr{ make_expr_string(loc, data[index + 1]) };
                while (stm.list[j] == node::stmt_case) j++;
                stm.list.insert(stm.list.begin() + j, stmt{ make_stmt_case(loc, std::move(exp), make_stmt_list(loc)) });
                index += 3;
            }
            else if (data[index] == "default")
            {
                auto j = find_location_index(stm, data[index + 1]);
                auto loc = stm.list[j].loc();
                while (stm.list[j] == node::stmt_case) j++;
                stm.list.insert(stm.list.begin() + j, stmt{ make_stmt_default(loc, make_stmt_list(loc)) });
                index += 2;
            }
            else
            {
                decomp_error("malformed endswitch statement");
            }
        }

        end += count;
    }

    auto save = locs_;
    locs_.brk = last_location_index(stm, end) ? locs_.end : stm.list[end + 1].label();
    locs_.end = stm.list[begin].as_asm_switch->value;

    auto loc = stm.list[begin].loc();
    auto test = std::move(stm.list[begin].as_asm_switch->test);

    end--;
    stm.list.erase(stm.list.begin() + begin);
    stm.list.erase(stm.list.begin() + end);

    auto body = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;

    auto temp = stmt{ make_node() };

    for (auto i = 0u; i < body->list.size(); )
    {
        if (body->list[i] == node::stmt_case || body->list[i] == node::stmt_default)
        {
            if (temp != node::null)
            {
                body->list.insert(body->list.begin() + i, std::move(temp));
                i++;
            }

            temp = std::move(body->list[i]);
            body->list.erase(body->list.begin() + i);
        }
        else
        {
            if (temp == node::stmt_case)
            {
                temp.as_case->body->list.push_back(std::move(body->list[i]));
                body->list.erase(body->list.begin() + i);
            }
            else if (temp == node::stmt_default)
            {
                temp.as_default->body->list.push_back(std::move(body->list[i]));
                body->list.erase(body->list.begin() + i);
            }
            else
            {
                decomp_error("missing case or default before stmt inside a switch");
            }
        }
    }

    if (temp != node::null)
    {
        body->list.push_back(std::move(temp));
    }

    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_switch(loc, std::move(test), make_stmt_comp(loc, std::move(body))) });
}

auto decompiler::find_location_reference(stmt_list const& stm, usize begin, usize end, std::string const& loc) -> bool
{
    for (auto i = begin; i < end; i++)
    {
        auto const& entry = stm.list.at(i);

        if (entry == node::asm_jmp_cond && entry.as_cond->value == loc)
        {
            return true;
        }
        else if (entry == node::asm_jmp && entry.as_jump->value == loc)
        {
            return true;
        }
        else if (entry == node::asm_dev && entry.as_asm_dev->value == loc)
        {
            return true;
        }
    }

    return false;
}

auto decompiler::find_location_index(stmt_list const& stm, std::string const& loc) -> usize
{
    auto index = 0u;

    if (loc == locs_.end)
        return stm.list.size();

    for (auto const& entry : stm.list)
    {
        if (entry.label() == loc)
            return index;

        index++;
    }

    throw decomp_error(fmt::format("location '{}' not found", loc));
}

auto decompiler::last_location_index(stmt_list const& stm, usize index) -> bool
{
    return (index == stm.list.size() - 1);
}

auto decompiler::lvalues_match(stmt_assign const& stm1, stmt_assign const& stm2) -> bool
{
    expr* lvalue1 {};
    expr* lvalue2 {};

    switch (stm1.value.kind())
    {
        case node::expr_increment:
            lvalue1 = &stm1.value.as_increment->lvalue;
            break;
        case node::expr_decrement:
            lvalue1 = &stm1.value.as_decrement->lvalue;
            break;
        case node::expr_assign_equal:
        case node::expr_assign_add:
        case node::expr_assign_sub:
        case node::expr_assign_mul:
        case node::expr_assign_div:
        case node::expr_assign_mod:
        case node::expr_assign_shift_left:
        case node::expr_assign_shift_right:
        case node::expr_assign_bitwise_or:
        case node::expr_assign_bitwise_and:
        case node::expr_assign_bitwise_exor:
            lvalue1 = &stm1.value.as_assign->lvalue;
            break;
        default:
            break;
    }

    switch (stm2.value.kind())
    {
        case node::expr_increment:
            lvalue2 = &stm2.value.as_increment->lvalue;
            break;
        case node::expr_decrement:
            lvalue2 = &stm2.value.as_decrement->lvalue;
            break;
        case node::expr_assign_equal:
        case node::expr_assign_add:
        case node::expr_assign_sub:
        case node::expr_assign_mul:
        case node::expr_assign_div:
        case node::expr_assign_mod:
        case node::expr_assign_shift_left:
        case node::expr_assign_shift_right:
        case node::expr_assign_bitwise_or:
        case node::expr_assign_bitwise_and:
        case node::expr_assign_bitwise_exor:
            lvalue2 = &stm2.value.as_assign->lvalue;
            break;
        default:
            break;
    }

    if (lvalue1 && lvalue2 && *lvalue1 == *lvalue2)
        return true;

    return false;
}

auto decompiler::resolve_label(std::string const& name) -> u32
{
    for (auto const& entry : labels_)
    {
        if (entry.second == name)
        {
            return entry.first;
        }
    }

    throw decomp_error(fmt::format("couldn't resolve label address of '{}'", name));
}

auto decompiler::process_function(decl_function& func) -> void
{
    process_stmt_comp(*func.body);
    process_expr_parameters(*func.params);
}

auto decompiler::process_stmt(stmt& stm) -> void
{
    switch (stm.kind())
    {
        case node::stmt_list:
            process_stmt_list(*stm.as_list);
            break;
                case node::stmt_comp:
            process_stmt_comp(*stm.as_comp);
            break;
        case node::stmt_dev:
            process_stmt_dev(*stm.as_dev);
            break;
        case node::stmt_expr:
            process_stmt_expr(*stm.as_expr);
            break;
        case node::stmt_call:
            process_stmt_call(*stm.as_call);
            break;
        case node::stmt_assign:
            process_stmt_assign(*stm.as_assign);
            break;
        case node::stmt_endon:
            process_stmt_endon(*stm.as_endon);
            break;
        case node::stmt_notify:
            process_stmt_notify(*stm.as_notify);
            break;
        case node::stmt_realwait:
            process_stmt_realwait(*stm.as_realwait);
            break;
        case node::stmt_wait:
            process_stmt_wait(*stm.as_wait);
            break;
        case node::stmt_waittill:
            process_stmt_waittill(*stm.as_waittill);
            break;
        case node::stmt_waittillmatch:
            process_stmt_waittillmatch(*stm.as_waittillmatch);
            break;
        case node::stmt_if:
            process_stmt_if(*stm.as_if);
            break;
        case node::stmt_ifelse:
            process_stmt_ifelse(*stm.as_ifelse);
            break;
        case node::stmt_while:
            process_stmt_while(*stm.as_while);
            break;
        case node::stmt_dowhile:
            process_stmt_dowhile(*stm.as_dowhile);
            break;
        case node::stmt_for:
            process_stmt_for(*stm.as_for);
            break;
        case node::stmt_foreach:
            process_stmt_foreach(*stm.as_foreach);
            break;
        case node::stmt_switch:
            process_stmt_switch(*stm.as_switch);
            break;
        case node::stmt_return:
            process_stmt_return(*stm.as_return);
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_list(stmt_list& stm) -> void
{
    for (auto& entry : stm.list)
    {
        process_stmt(entry);
    }
}

auto decompiler::process_stmt_comp(stmt_comp& stm) -> void
{
    process_stmt_list(*stm.block);
}

auto decompiler::process_stmt_dev(stmt_dev& stm) -> void
{
    process_stmt_list(*stm.block);
}

auto decompiler::process_stmt_expr(stmt_expr& stm) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_increment:
            process_expr_increment(*stm.value.as_increment);
            break;
        case node::expr_decrement:
            process_expr_decrement(*stm.value.as_decrement);
            break;
        case node::expr_assign_equal:
        case node::expr_assign_add:
        case node::expr_assign_sub:
        case node::expr_assign_mul:
        case node::expr_assign_div:
        case node::expr_assign_mod:
        case node::expr_assign_shift_left:
        case node::expr_assign_shift_right:
        case node::expr_assign_bitwise_or:
        case node::expr_assign_bitwise_and:
        case node::expr_assign_bitwise_exor:
            process_expr_assign(stm.value.as_assign);
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_call(stmt_call& stm) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_call:
            process_expr_call(*stm.value.as_call);
            break;
        case node::expr_method:
            process_expr_method(*stm.value.as_method);
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_assign(stmt_assign& stm) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_increment:
            process_expr_increment(*stm.value.as_increment);
            break;
        case node::expr_decrement:
            process_expr_decrement(*stm.value.as_decrement);
            break;
        case node::expr_assign_equal:
        case node::expr_assign_add:
        case node::expr_assign_sub:
        case node::expr_assign_mul:
        case node::expr_assign_div:
        case node::expr_assign_mod:
        case node::expr_assign_shift_left:
        case node::expr_assign_shift_right:
        case node::expr_assign_bitwise_or:
        case node::expr_assign_bitwise_and:
        case node::expr_assign_bitwise_exor:
            process_expr_assign(stm.value.as_assign);
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_endon(stmt_endon& stm) -> void
{
    process_expr(stm.event);
    process_expr(stm.obj);
}

void decompiler::process_stmt_notify(stmt_notify& stm)
{
    process_expr_arguments(*stm.args);
    process_expr(stm.event);
    process_expr(stm.obj);
}

auto decompiler::process_stmt_realwait(stmt_realwait& stm) -> void
{
    process_expr(stm.time);
}

auto decompiler::process_stmt_wait(stmt_wait& stm) -> void
{
    process_expr(stm.time);
}

auto decompiler::process_stmt_waittill(stmt_waittill& stm) -> void
{
    process_expr(stm.event);
    process_expr(stm.obj);

    for (auto& entry : stm.args->list)
    {
        process_expr(entry);
    }
}

auto decompiler::process_stmt_waittillmatch(stmt_waittillmatch& stm) -> void
{
    process_expr_arguments(*stm.args);
    process_expr(stm.event);
    process_expr(stm.obj);
}

auto decompiler::process_stmt_if(stmt_if& stm) -> void
{
    process_expr(stm.test);

    process_stmt(stm.body);

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_ifelse(stmt_ifelse& stm) -> void
{
    process_expr(stm.test);
    process_stmt(stm.stmt_if);
    process_stmt(stm.stmt_else);

    if (stm.stmt_if.as_comp->block->list.size() == 1 && !stm.stmt_if.as_comp->block->list[0].as_node->is_special_stmt_dev())
    {
        stm.stmt_if = std::move(stm.stmt_if.as_comp->block->list.back());
    }

    if (stm.stmt_else.as_comp->block->list.size() == 1 && !stm.stmt_else.as_comp->block->list[0].as_node->is_special_stmt_dev_noif())
    {
        stm.stmt_else = std::move(stm.stmt_else.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_while(stmt_while& stm) -> void
{
    if (stm.test == node::expr_integer && stm.test.as_integer->value == "1")
    {
        stm.test = expr{ make_expr_true(stm.test.loc()) };
    }

    process_expr(stm.test);
    process_stmt(stm.body);

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_dowhile(stmt_dowhile& stm) -> void
{
    if (stm.test == node::expr_integer && stm.test.as_integer->value == "1")
    {
        stm.test = expr{ make_expr_true(stm.test.loc()) };
    }

    process_expr(stm.test);
    process_stmt(stm.body);

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_for(stmt_for& stm) -> void
{
    process_stmt(stm.init);
    process_expr(stm.test);
    process_stmt(stm.body);
    process_stmt(stm.iter);

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_foreach(stmt_foreach& stm) -> void
{
    process_expr(stm.container);
    process_expr(stm.array);
    process_expr(stm.key);
    process_expr(stm.value);

    if ((ctx_->props() & props::version2) && !stm.use_key)
        vars_.insert(stm.key.as_identifier->value);

    process_stmt(stm.body);

    if ((ctx_->props() & props::version2) && !stm.use_key)
    {
        auto const it = vars_.find(stm.key.as_identifier->value);

        if (it != vars_.end())
            vars_.erase(it);
        else
            stm.use_key = true;  
    }

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_switch(stmt_switch& stm) -> void
{
    process_expr(stm.test);

    for (auto& entry : stm.body->block->list)
    {
        if (entry == node::stmt_case)
        {
            process_stmt_list(*entry.as_case->body);
        }
        else if (entry == node::stmt_default)
        {
            process_stmt_list(*entry.as_default->body);
        }
    }
}

auto decompiler::process_stmt_return(stmt_return& stm) -> void
{
    if (stm.value != node::null)
    {
        if (retbool_ && stm.value == node::expr_integer)
            stm.value = stm.value.as_integer->value == "1" ? expr{ make_expr_true(stm.loc()) } : expr{ make_expr_false(stm.loc()) };
        else
            process_expr(stm.value);
    }
}

auto decompiler::process_expr(expr& exp) -> void
{
    switch (exp.kind())
    {
        case node::expr_ternary:
            process_expr_ternary(*exp.as_ternary);
            break;
        case node::expr_and:
            process_expr_and(*exp.as_and);
            break;
        case node::expr_or:
            process_expr_or(*exp.as_or);
            break;
        case node::expr_super_equal:
        case node::expr_super_not_equal:
        case node::expr_equality:
        case node::expr_inequality:
        case node::expr_less:
        case node::expr_greater:
        case node::expr_less_equal:
        case node::expr_greater_equal:
        case node::expr_bitwise_or:
        case node::expr_bitwise_and:
        case node::expr_bitwise_exor:
        case node::expr_shift_left:
        case node::expr_shift_right:
        case node::expr_add:
        case node::expr_sub:
        case node::expr_mul:
        case node::expr_div:
        case node::expr_mod:
            process_expr_binary(*exp.as_binary);
            break;
        case node::expr_complement:
            process_expr_complement(*exp.as_complement);
            break;
        case node::expr_not:
            process_expr_not(*exp.as_not);
            break;
        case node::expr_call:
            process_expr_call(*exp.as_call);
            break;
        case node::expr_method:
            process_expr_method(*exp.as_method);
            break;
        case node::expr_getnextarraykey:
            process_expr(exp.as_getnextarraykey->arg2);
            process_expr(exp.as_getnextarraykey->arg1);
            break;
        case node::expr_getfirstarraykey:
            process_expr(exp.as_getfirstarraykey->arg);
            break;
        case node::expr_getdvarcoloralpha:
            process_expr(exp.as_getdvarcoloralpha->arg);
            break;
        case node::expr_getdvarcolorblue:
            process_expr(exp.as_getdvarcolorblue->arg);
            break;
        case node::expr_getdvarcolorgreen:
            process_expr(exp.as_getdvarcolorgreen->arg);
            break;
        case node::expr_getdvarcolorred:
            process_expr(exp.as_getdvarcolorred->arg);
            break;
        case node::expr_getdvarvector:
            process_expr(exp.as_getdvarvector->arg);
            break;
        case node::expr_getdvarfloat:
            process_expr(exp.as_getdvarfloat->arg);
            break;
        case node::expr_getdvarint:
            process_expr(exp.as_getdvarint->arg);
            break;
        case node::expr_getdvar:
            process_expr(exp.as_getdvar->arg);
            break;
        case node::expr_abs:
            process_expr(exp.as_abs->arg);
            break;
        case node::expr_vectortoangles:
            process_expr(exp.as_vectortoangles->arg);
            break;
        case node::expr_angleclamp180:
            process_expr(exp.as_angleclamp180->arg);
            break;
        case node::expr_anglestoforward:
            process_expr(exp.as_anglestoforward->arg);
            break;
        case node::expr_anglestoright:
            process_expr(exp.as_anglestoright->arg);
            break;
        case node::expr_anglestoup:
            process_expr(exp.as_anglestoup->arg);
            break;
        case node::expr_vectorscale:
            process_expr(exp.as_vectorscale->arg2);
            process_expr(exp.as_vectorscale->arg1);
            break;
        case node::expr_isdefined:
            process_expr(exp.as_isdefined->value);
            break;
        case node::expr_array:
            process_expr_array(*exp.as_array);
            break;
        case node::expr_field:
            process_expr_field(*exp.as_field);
            break;
        case node::expr_size:
            process_expr_size(*exp.as_size);
            break;
        case node::expr_vector:
            process_expr_vector(*exp.as_vector);
            break;
        case node::expr_identifier:
            process_expr_identifier(*exp.as_identifier);
            break;
        default:
            break;
    }
}

auto decompiler::process_expr_assign(expr_assign::ptr& exp) -> void
{
    process_expr(exp->rvalue);
    process_expr(exp->lvalue);

    if (exp->kind() == node::expr_assign_equal)
    {
        switch (exp->rvalue.kind())
        {
            case node::expr_bitwise_or:
                if (exp->lvalue == exp->rvalue.as_bitwise_or->lvalue)
                    exp = make_expr_assign_bitwise_or(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_bitwise_or->rvalue));
                break;
            case node::expr_bitwise_and:
                if (exp->lvalue == exp->rvalue.as_bitwise_and->lvalue)
                    exp = make_expr_assign_bitwise_and(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_bitwise_and->rvalue));
                break;
            case node::expr_bitwise_exor:
                if (exp->lvalue == exp->rvalue.as_bitwise_exor->lvalue)
                    exp = make_expr_assign_bitwise_exor(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_bitwise_exor->rvalue));
                break;
            case node::expr_shift_left:
                if (exp->lvalue == exp->rvalue.as_shift_left->lvalue)
                    exp = make_expr_assign_shift_left(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_shift_left->rvalue));
                break;
            case node::expr_shift_right:
                if (exp->lvalue == exp->rvalue.as_shift_right->lvalue)
                    exp = make_expr_assign_shift_right(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_shift_right->rvalue));
                break;
            case node::expr_add:
                if (exp->lvalue == exp->rvalue.as_add->lvalue)
                    exp = make_expr_assign_add(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_add->rvalue));
                break;
            case node::expr_sub:
                if (exp->lvalue == exp->rvalue.as_sub->lvalue)
                    exp = make_expr_assign_sub(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_sub->rvalue));
                break;
            case node::expr_mul:
                if (exp->lvalue == exp->rvalue.as_mul->lvalue)
                    exp = make_expr_assign_mul(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_mul->rvalue));
                break;
            case node::expr_div:
                if (exp->lvalue == exp->rvalue.as_div->lvalue)
                    exp = make_expr_assign_div(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_div->rvalue));
                break;
            case node::expr_mod:
                if (exp->lvalue == exp->rvalue.as_mod->lvalue)
                    exp = make_expr_assign_mod(exp->loc(), std::move(exp->lvalue), std::move(exp->rvalue.as_mod->rvalue));
                break;
            default:
                break;
        }
    }
}

auto decompiler::process_expr_increment(expr_increment& exp) -> void
{
    process_expr(exp.lvalue);
}

auto decompiler::process_expr_decrement(expr_decrement& exp) -> void
{
    process_expr(exp.lvalue);
}

auto decompiler::process_expr_ternary(expr_ternary& exp) -> void
{
    process_expr(exp.test);
    process_expr(exp.true_expr);
    process_expr(exp.false_expr);
}

auto decompiler::process_expr_binary(expr_binary& exp) -> void
{
    process_expr(exp.lvalue);
    process_expr(exp.rvalue);

    auto prec = exp.lvalue.as_node->precedence();

    if (prec && prec < exp.precedence())
    {
        exp.lvalue = expr{ make_expr_paren(exp.loc(), std::move(exp.lvalue)) };
    }

    prec = exp.rvalue.as_node->precedence();

    if ((prec && prec < exp.precedence()) || (prec == exp.precedence() && exp.kind() == exp.rvalue.as_node->kind()))
    {
        exp.rvalue = expr{ make_expr_paren(exp.loc(), std::move(exp.rvalue)) };
    }
}

auto decompiler::process_expr_and(expr_and& exp) -> void
{
    process_expr(exp.lvalue);
    process_expr(exp.rvalue);

    auto prec = exp.lvalue.as_node->precedence();

    if (prec && prec < exp.precedence())
    {
        exp.lvalue = expr{ make_expr_paren(exp.loc(), std::move(exp.lvalue)) };
    }

    prec = exp.rvalue.as_node->precedence();

    if ((prec && prec < exp.precedence()) || (prec == exp.precedence() && exp.kind() == exp.rvalue.kind()))
    {
        exp.rvalue = expr{ make_expr_paren(exp.loc(), std::move(exp.rvalue)) };
    }
}

auto decompiler::process_expr_or(expr_or& exp) -> void
{
    process_expr(exp.lvalue);
    process_expr(exp.rvalue);
}

auto decompiler::process_expr_complement(expr_complement& exp) -> void
{
    process_expr(exp.rvalue);

    if (exp.rvalue.as_node->is_binary())
    {
        exp.rvalue = expr{ make_expr_paren(exp.loc(), std::move(exp.rvalue)) };
    }
}

auto decompiler::process_expr_not(expr_not& exp) -> void
{
    process_expr(exp.rvalue);

    if (exp.rvalue.as_node->is_binary())
    {
        exp.rvalue = expr{ make_expr_paren(exp.loc(), std::move(exp.rvalue)) };
    }
}

auto decompiler::process_expr_call(expr_call& exp) -> void
{
    switch (exp.value.kind())
    {
        case node::expr_member:
            process_expr_call_member(*exp.value.as_member);
            break;
        case node::expr_pointer:
            process_expr_call_pointer(*exp.value.as_pointer);
            break;
        case node::expr_function:
            process_expr_call_function(*exp.value.as_function);
            break;
        default:
            break;
    }
}

auto decompiler::process_expr_method(expr_method& exp) -> void
{
    switch (exp.value.kind())
    {
        case node::expr_pointer:
            process_expr_method_pointer(*exp.value.as_pointer, exp.obj);
            break;
        case node::expr_function:
            process_expr_method_function(*exp.value.as_function, exp.obj);
            break;
        default:
            break;
    }
}

auto decompiler::process_expr_call_member(expr_member& exp) -> void
{
    process_expr_arguments(*exp.args);
    process_expr(exp.obj);
}

auto decompiler::process_expr_call_pointer(expr_pointer& exp) -> void
{
    process_expr_arguments(*exp.args);
    process_expr(exp.func);
}

auto decompiler::process_expr_call_function(expr_function& exp) -> void
{
    process_expr_arguments(*exp.args);
}

auto decompiler::process_expr_method_pointer(expr_pointer& exp, expr& obj) -> void
{
    process_expr_arguments(*exp.args);
    process_expr(obj);
    process_expr(exp.func);
}

auto decompiler::process_expr_method_function(expr_function& exp, expr& obj) -> void
{
    process_expr_arguments(*exp.args);
    process_expr(obj);
}

auto decompiler::process_expr_parameters(expr_parameters& exp) -> void
{
    if (exp.list.empty()) return;

    while (!func_->body->block->list.empty())
    {
        auto& stmt = func_->body->block->list.at(0);

        if (stmt != node::stmt_if || stmt.as_if->test != node::expr_not)
            return;

        auto& test = stmt.as_if->test.as_not->rvalue;

        if (test != node::expr_isdefined || test.as_isdefined->value != node::expr_identifier)
            return;

        if (stmt.as_if->body != node::stmt_assign || stmt.as_if->body.as_assign->value != node::expr_assign_equal)
            return;
        
        if (test.as_isdefined->value != stmt.as_if->body.as_assign->value.as_assign_equal->lvalue)
            return;
        
        auto index = 0u;

        for (auto& entry : exp.list)
        {
            if (entry == node::expr_identifier && entry.as_identifier->value == test.as_isdefined->value.as_identifier->value)
            {
                exp.list.erase(exp.list.begin() + index);
                exp.list.insert(exp.list.begin() + index, std::move(stmt.as_if->body.as_assign->value));
                func_->body->block->list.erase(func_->body->block->list.begin());
                break;
            }
            index++;
        }

        if (index == exp.list.size()) return;
    }
}

auto decompiler::process_expr_arguments(expr_arguments& exp) -> void
{
    for (auto i = exp.list.size(); i > 0; i--)
    {
        process_expr(exp.list[i - 1]);
    }
}

auto decompiler::process_expr_size(expr_size& exp) -> void
{
    process_expr(exp.obj);
}

auto decompiler::process_expr_array(expr_array& exp) -> void
{
    process_expr(exp.key);
    process_expr(exp.obj);
}

auto decompiler::process_expr_field(expr_field& exp) -> void
{
    process_expr(exp.obj);
}

auto decompiler::process_expr_vector(expr_vector& exp) -> void
{
    process_expr(exp.z);
    process_expr(exp.y);
    process_expr(exp.x);
}

auto decompiler::process_expr_identifier(expr_identifier& exp) -> void
{
    auto const it = vars_.find(exp.value);
    if (it != vars_.end()) vars_.erase(it);     
}

} // namespace xsk::arc
