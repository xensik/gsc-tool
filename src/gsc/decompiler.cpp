// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"
#include "decompiler.hpp"
#include "context.hpp"
#include "utils/string.hpp"

namespace xsk::gsc
{

decompiler::decompiler(context const* ctx) : ctx_{ ctx }
{
}

auto decompiler::decompile(assembly const& data) -> program::ptr
{
    program_ = make_program();

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
    in_waittill_ = false;
    labels_ = func.labels;
    locs_ = {};
    stack_ = {};

    auto loc = location{ nullptr, static_cast<location::counter_type>(func.index) };
    auto name = make_expr_identifier(loc, func.name);
    auto prms = make_expr_parameters(loc);
    auto body = make_stmt_comp(loc, make_stmt_list(loc));
    func_ = make_decl_function(loc, std::move(name), std::move(prms), std::move(body));

    for (auto const& inst : func.instructions)
    {
        decompile_instruction(*inst);
    }

    if (stack_.size())
    {
        throw decomp_error("stack isn't empty at function end");
    }

    locs_.last = true;
    locs_.end = func_->body->block->list.back().label();
    func_->body->block->list.pop_back();

    decompile_statements(*func_->body->block);
    process_function(*func_);

    program_->declarations.push_back(decl{ move(func_) });
}

auto decompiler::decompile_instruction(instruction const& inst) -> void
{
    decompile_expressions(inst);

    auto loc = location{ nullptr, static_cast<location::counter_type>(inst.index) };

    switch (inst.opcode)
    {
        case opcode::OP_End:
        {
            func_->body->block->list.push_back(stmt{ make_stmt_return(loc, expr{ make_node(loc) }) });
            break;
        }
        case opcode::OP_Return:
        {
            auto value = expr{ std::move(stack_.top()) }; stack_.pop();
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
        case opcode::OP_GetUnsignedInt:
        case opcode::OP_GetInteger:
        case opcode::OP_GetInteger64:
        {
            stack_.push(make_expr_integer(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetNegByte:
        case opcode::OP_GetNegUnsignedShort:
        case opcode::OP_GetNegUnsignedInt:
        {
            stack_.push(make_expr_integer(loc, "-" + inst.data[0]));
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
            if (!inst.data[0].empty())
            {
                auto dec = make_decl_usingtree(loc, make_expr_string(loc, inst.data[0]));
                program_->declarations.push_back(decl{ std::move(dec) });
            }

            stack_.push(make_expr_animation(loc, inst.data[1]));
            break;
        }
        case opcode::OP_GetAnimTree:
        {
            if (!inst.data[0].empty())
            {
                auto dec = make_decl_usingtree(loc, make_expr_string(loc, inst.data[0]));
                program_->declarations.push_back(decl{ std::move(dec) });
            }

            stack_.push(make_expr_animtree(loc));
            break;
        }
        case opcode::OP_GetThisthread:
        {
            stack_.push(make_expr_thisthread(loc));
            break;
        }
        case opcode::OP_GetBuiltinFunction:
        case opcode::OP_GetBuiltinMethod:
        {
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_reference(loc, std::move(path), std::move(name)));
            break;
        }
        case opcode::OP_GetLocalFunction:
        {
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_reference(loc, std::move(path), std::move(name)));
            break;
        }
        case opcode::OP_GetFarFunction:
        {
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);
            stack_.push(make_expr_reference(loc, std::move(path), std::move(name)));
            break;
        }
        case opcode::OP_CreateLocalVariable:
        {
            if (in_waittill_)
            {
                stack_.push(make_asm_create(loc, inst.data[0]));
            }
            else
            {
                func_->body->block->list.push_back(stmt{ make_asm_create(loc, inst.data[0]) });
            }
            break;
        }
        case opcode::OP_RemoveLocalVariables:
        {
            func_->body->block->list.push_back(stmt{ make_asm_remove(loc, inst.data[0]) });
            break;
        }
        case opcode::OP_EvalLocalVariableCached0:
        {
            stack_.push(make_asm_access(loc, "0"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached1:
        {
            stack_.push(make_asm_access(loc, "1"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached2:
        {
            stack_.push(make_asm_access(loc, "2"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached3:
        {
            stack_.push(make_asm_access(loc, "3"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached4:
        {
            stack_.push(make_asm_access(loc, "4"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached5:
        {
            stack_.push(make_asm_access(loc, "5"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached:
        {
            stack_.push(make_asm_access(loc, inst.data[0]));
            break;
        }
        case opcode::OP_EvalLocalArrayCached:
        {
            auto key = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ make_asm_access(loc, inst.data[0]) };
            stack_.push(make_expr_array(key.loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalArray:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto key = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_array(key.loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalNewLocalArrayRefCached0:
        {
            auto key = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ make_asm_create(loc, inst.data[0]) };
            stack_.push(make_expr_array(key.loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalLocalArrayRefCached0:
        {
            auto key = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ make_asm_access(loc, "0") };
            stack_.push(make_expr_array(key.loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalLocalArrayRefCached:
        {
            auto key = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ make_asm_access(loc, inst.data[0]) };
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
        case opcode::OP_AddArray:
        {
            auto value = expr{ std::move(stack_.top()) }; stack_.pop();
            auto array = std::move(stack_.top()); stack_.pop();

            if (array->kind() == node::expr_empty_array)
            {
                auto args = make_expr_arguments(loc);
                args->list.push_back(std::move(value));
                stack_.push(make_expr_add_array(array->loc(), std::move(args)));
            }
            else if (array->kind() == node::expr_add_array)
            {
                reinterpret_cast<expr_add_array*>(array.get())->args->list.push_back(std::move(value));
                stack_.push(std::move(array));
            }
            else
            {
                throw decomp_error("unknown add array type (could be an array variable name?)");
            }
            break;
        }
        case opcode::OP_PreScriptCall:
        {
            stack_.push(make_asm_prescriptcall(loc));
            break;
        }
        case opcode::OP_ScriptLocalFunctionCall2:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_ScriptLocalFunctionCall:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

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
        case opcode::OP_ScriptLocalMethodCall:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

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
        case opcode::OP_ScriptLocalThreadCall:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_ScriptLocalChildThreadCall:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::childthread) }));
            break;
        }
        case opcode::OP_ScriptLocalMethodThreadCall:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_ScriptLocalMethodChildThreadCall:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::childthread) }));
            break;
        }
        case opcode::OP_ScriptFarFunctionCall2:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);
            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::normal) }));
            break;
        }
        case opcode::OP_ScriptFarFunctionCall:
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
        case opcode::OP_ScriptFarMethodCall:
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
        case opcode::OP_ScriptFarThreadCall:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            for (auto i = std::stoul(inst.data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_ScriptFarChildThreadCall:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            for (auto i = std::stoul(inst.data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::childthread) }));
            break;
        }
        case opcode::OP_ScriptFarMethodThreadCall:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            for (auto i = std::stoul(inst.data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_ScriptFarMethodChildThreadCall:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc, inst.data[0]);
            auto name = make_expr_identifier(loc, inst.data[1]);

            for (auto i = std::stoul(inst.data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::childthread) }));
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
        case opcode::OP_ScriptThreadCallPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = func.loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_ScriptChildThreadCallPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = func.loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::childthread) }));
            break;
        }
        case opcode::OP_ScriptMethodThreadCallPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::thread) }));
            break;
        }
        case opcode::OP_ScriptMethodChildThreadCallPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::childthread) }));
            break;
        }
        case opcode::OP_CallBuiltinPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = func.loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltinMethodPointer:
        {
            auto args = make_expr_arguments(loc);
            auto func = expr{ std::move(stack_.top()) }; stack_.pop();
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_pointer(loc, std::move(func), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltin0:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltin1:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 1u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltin2:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 2u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltin3:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 3u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltin4:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 4u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltin5:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 5u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltin:
        {
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_call(loc, call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltinMethod0:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltinMethod1:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 1u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltinMethod2:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 2u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltinMethod3:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 3u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltinMethod4:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 4u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltinMethod5:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = 5u; i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_CallBuiltinMethod:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = obj.loc();
            auto args = make_expr_arguments(loc);
            auto path = make_expr_path(loc);
            auto name = make_expr_identifier(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(make_expr_method(loc, std::move(obj), call{ make_expr_function(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin) }));
            break;
        }
        case opcode::OP_DecTop:
        {
            auto exp = expr{ std::move(stack_.top()) }; stack_.pop();
            func_->body->block->list.push_back(stmt{ make_stmt_call(exp.loc(), std::move(exp)) });
            break;
        }
        case opcode::OP_inc:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_increment(lvalue.loc(), std::move(lvalue), false));
            break;
        }
        case opcode::OP_dec:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_decrement(lvalue.loc(), std::move(lvalue), false));
            break;
        }
        case opcode::OP_bit_or:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_bitwise_or(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_bit_ex_or:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_bitwise_exor(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_bit_and:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_bitwise_and(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_equality:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_equality(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_inequality:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_inequality(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_less:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_less(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_greater:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_greater(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_less_equal:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_less_equal(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_greater_equal:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_greater_equal(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_shift_left:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_shift_left(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_shift_right:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_shift_right(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_plus:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_add(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_minus:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_sub(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_multiply:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_mul(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_divide:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_div(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_mod:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_mod(lvalue.loc(), std::move(lvalue), std::move(rvalue)));
            break;
        }
        case opcode::OP_wait:
        {
            auto exp = expr{ std::move(stack_.top()) }; stack_.pop();
            func_->body->block->list.push_back(stmt{ make_stmt_wait(exp.loc(), std::move(exp)) });
            break;
        }
        case opcode::OP_waittillFrameEnd:
        {
            func_->body->block->list.push_back(stmt{ make_stmt_waittillframeend(loc) });
            break;
        }
        case opcode::OP_waitframe:
        {
            func_->body->block->list.push_back(stmt{ make_stmt_waitframe(loc) });
            break;
        }
        case opcode::OP_waittill:
        {
            auto args = make_expr_arguments(loc);
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto event = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_stmt_waittill(event.loc(), std::move(obj), std::move(event), std::move(args)));
            in_waittill_ = true;
            break;
        }
        case opcode::OP_waittillmatch:
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
        case opcode::OP_clearparams:
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
        case opcode::OP_notify:
        {
            auto args = make_expr_arguments(loc);
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto event = expr{ std::move(stack_.top()) }; stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::asm_voidcodepos)
            {
                args->list.push_back(std::move(var));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            func_->body->block->list.push_back(stmt{ make_stmt_notify(loc, std::move(obj), std::move(event), std::move(args)) });
            break;
        }
        case opcode::OP_endon:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto event = expr{ std::move(stack_.top()) }; stack_.pop();
            func_->body->block->list.push_back(stmt{ make_stmt_endon(event.loc(), std::move(obj), std::move(event)) });
            break;
        }
        case opcode::OP_voidCodepos:
        {
            stack_.push(make_asm_voidcodepos(loc));
            break;
        }
        case opcode::OP_vector:
        {
            auto x = expr{ std::move(stack_.top()) }; stack_.pop();
            auto y = expr{ std::move(stack_.top()) }; stack_.pop();
            auto z = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_vector(z.loc(), std::move(x), std::move(y), std::move(z)));
            break;
        }
        case opcode::OP_size:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_size(lvalue.loc(), std::move(lvalue)));
            break;
        }
        case opcode::OP_EvalLevelFieldVariable:
        {
            auto obj = expr{ make_expr_level(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalAnimFieldVariable:
        {
            auto obj = expr{ make_expr_anim(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalSelfFieldVariable:
        {
            auto obj = expr{ make_expr_self(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalFieldVariable:
        {
            auto obj = expr{ std::move(stack_.top()) }; stack_.pop();
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(obj.loc(), std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalLevelFieldVariableRef:
        {
            auto obj = expr{ make_expr_level(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalAnimFieldVariableRef:
        {
            auto obj = expr{ make_expr_anim(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalSelfFieldVariableRef:
        {
            auto obj = expr{ make_expr_self(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            stack_.push(make_expr_field(loc, std::move(obj), std::move(field)));
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
        case opcode::OP_SafeCreateVariableFieldCached:
        {
            auto name = (ctx_->props() & props::hash) ? inst.data[0] : fmt::format("var_{}", inst.data[0]);
            func_->params->list.push_back(make_expr_identifier(loc, name));
            break;
        }
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        {
            if (stack_.top()->kind() != node::asm_create)
            {
                stack_.push(make_asm_access(loc, inst.data[0]));
            }
            break;
        }
        case opcode::OP_SafeSetVariableFieldCached0:
        {
            func_->params->list.push_back(make_expr_identifier(loc, "var_0"));
            break;
        }
        case opcode::OP_SafeSetVariableFieldCached:
        {
            func_->params->list.push_back(make_expr_identifier(loc, "var_" + inst.data[0]));
            break;
        }
        case opcode::OP_EvalLocalVariableRefCached0:
        {
            stack_.push(make_asm_access(loc, "0"));
            break;
        }
        case opcode::OP_EvalLocalVariableRefCached:
        {
            stack_.push(make_asm_access(loc, inst.data[0]));
            break;
        }
        case opcode::OP_SetLevelFieldVariableField:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = rvalue.loc();
            auto obj = expr{ make_expr_level(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            auto lvalue = expr{ make_expr_field(loc, std::move(obj), std::move(field)) };
            auto exp = expr{ make_expr_assign_equal(loc, std::move(lvalue), std::move(rvalue)) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_SetVariableField:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = lvalue.loc();

            if (lvalue == node::expr_increment)
            {
                func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(lvalue)) });
            }
            else if (lvalue == node::expr_decrement)
            {
                func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(lvalue)) });
            }
            else
            {
                auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
                loc = rvalue.loc();
                auto exp = expr{ make_expr_assign_equal(loc, std::move(lvalue), std::move(rvalue)) };
                func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            }
            break;
        }
        case opcode::OP_SetAnimFieldVariableField:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = rvalue.loc();
            auto obj = expr{ make_expr_anim(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            auto lvalue = expr{ make_expr_field(loc, std::move(obj), std::move(field)) };
            auto exp = expr{ make_expr_assign_equal(loc, std::move(lvalue), std::move(rvalue)) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_SetSelfFieldVariableField:
        {
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = rvalue.loc();
            auto obj = expr{ make_expr_self(loc) };
            auto field = make_expr_identifier(loc, inst.data[0]);
            auto lvalue = expr{ make_expr_field(loc, std::move(obj), std::move(field)) };
            auto exp = expr{ make_expr_assign_equal(loc, std::move(lvalue), std::move(rvalue)) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_SetLocalVariableFieldCached0:
        {
            auto lvalue = expr{ make_asm_access(loc, "0") };
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = rvalue.loc();
            auto exp = expr{ make_expr_assign_equal(loc, std::move(lvalue), std::move(rvalue)) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_SetNewLocalVariableFieldCached0:
        {
            auto lvalue = expr{ make_asm_create(loc, inst.data[0]) };
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = rvalue.loc();

            if (func_->body->block->list.size() > 0)
            {
                std::vector<std::string> vars;

                while (func_->body->block->list.back() == node::asm_create)
                {
                    auto& entry = func_->body->block->list.back();
                    if (loc.begin.line < entry.loc().begin.line)
                    {
                        vars.push_back(entry.as_asm_create->index);
                        func_->body->block->list.pop_back();
                        continue;
                    }
                    break;
                }

                std::reverse(vars.begin(), vars.end());
                lvalue.as_asm_create->vars = vars;
            }

            auto exp = expr{ make_expr_assign_equal(loc, std::move(lvalue), std::move(rvalue)) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_SetLocalVariableFieldCached:
        {
            auto lvalue = expr{ make_asm_access(loc, inst.data[0]) };
            auto rvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = rvalue.loc();
            auto exp = expr{ make_expr_assign_equal(loc, std::move(lvalue), std::move(rvalue)) };
            func_->body->block->list.push_back(stmt{ make_stmt_assign(loc, std::move(exp)) });
            break;
        }
        case opcode::OP_ClearLocalVariableFieldCached:
        {
            func_->body->block->list.push_back(stmt{ make_asm_clear(loc, inst.data[0]) });
            break;
        }
        case opcode::OP_ClearLocalVariableFieldCached0:
        {
            func_->body->block->list.push_back(stmt{ make_asm_clear(loc, "0") });
            break;
        }
        case opcode::OP_EvalLocalVariableObjectCached:
        {
            stack_.push(make_asm_access(loc, inst.data[0]));
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
        case opcode::OP_switch:
        {
            auto test = expr{ std::move(stack_.top()) }; stack_.pop();
            func_->body->block->list.push_back(stmt{ make_asm_switch(test.loc(), std::move(test), inst.data[0]) });
            break;
        }
        case opcode::OP_endswitch:
        {
            func_->body->block->list.push_back(stmt{ make_asm_endswitch(loc, inst.data) });
            break;
        }
        case opcode::OP_jump:
        {
            func_->body->block->list.push_back(stmt{ make_asm_jmp(loc, inst.data[0]) });
            if (stack_.size() != 0) tern_labels_.push_back(inst.data[0]);
            break;
        }
        case opcode::OP_jumpback:
        {
            func_->body->block->list.push_back(stmt{ make_asm_jmp_back(loc, inst.data[0]) });
            break;
        }
        case opcode::OP_JumpOnTrue:
        {
            auto lvalue = expr{ std::move(stack_.top()) }; stack_.pop();
            loc = lvalue.loc();
            auto test = expr{ make_expr_not(loc, std::move(lvalue)) };
            func_->body->block->list.push_back(stmt{ make_asm_jmp_cond(loc, std::move(test), inst.data[0]) });
            break;
        }
        case opcode::OP_JumpOnFalse:
        {
            auto test = expr{ std::move(stack_.top()) }; stack_.pop();
            func_->body->block->list.push_back(stmt{ make_asm_jmp_cond(test.loc(), std::move(test), inst.data[0]) });
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
        case opcode::OP_FormalParams:
        {
            auto count = std::stoi(inst.data[0]);

            for (auto i = 1; i <= count; i++)
            {
                auto name = (ctx_->props() & props::hash) ? inst.data[i] : fmt::format("var_{}", inst.data[i]);
                func_->params->list.push_back(make_expr_identifier(loc, name));
            }
            break;
        }
        case opcode::OP_IsDefined:
        {
            auto value = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_isdefined(value.loc(), std::move(value)));
            break;
        }
        case opcode::OP_IsTrue:
        {
            auto value = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_istrue(value.loc(), std::move(value)));
            break;
        }
        case opcode::OP_BoolNotAfterAnd:
        {
            auto value = expr{ std::move(stack_.top()) }; stack_.pop();
            stack_.push(make_expr_not(value.loc(), std::move(value)));
            break;
        }
        case opcode::OP_GetStatHash:
        {
            stack_.push(make_expr_string(loc, fmt::format("stat_{}", inst.data[0])));
            break;
        }
        case opcode::OP_GetUnkxHash:
        {
            stack_.push(make_expr_string(loc, fmt::format("hunk_{}", inst.data[0])));
            break;
        }
        case opcode::OP_GetEnumHash:
        {
            stack_.push(make_expr_string(loc, fmt::format("enum_{}", inst.data[0])));
            break;
        }
        case opcode::OP_GetDvarHash:
        {
            stack_.push(make_expr_string(loc, fmt::format("dvar_{}", inst.data[0])));
            break;
        }
        case opcode::OP_waittillmatch2:
        case opcode::OP_checkclearparams:
        case opcode::OP_CastFieldObject:
        case opcode::OP_CastBool:
            break;
        default:
            throw decomp_error(fmt::format("unhandled opcode {}", opcode_name(inst.opcode)));
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
    decompile_loops(stm);
    decompile_switches(stm);
    decompile_ifelses(stm);
    decompile_aborts(stm);
    decompile_tuples(stm);
}

auto decompiler::decompile_loops(stmt_list& stm) -> void
{
    if (stm.list.size() == 0)
        return;

    for (auto i = static_cast<i32>(stm.list.size() - 1); i >= 0; i--)
    {
        if (stm.list.at(i) == node::asm_jmp_back)
        {
            auto break_loc = last_location_index(stm, i) ? locs_.end : stm.list.at(i + 1).label();
            auto start = find_location_index(stm, stm.list.at(i).as_jump_back->value);

            if (i > 0 && stm.list.at(i - 1) == node::asm_jmp_cond)
            {
                if (i - 1 == static_cast<i32>(start)) // condition belongs to empty loop
                {
                    decompile_while(stm, start, i);
                    i = static_cast<i32>(stm.list.size());
                    continue;
                }
                else if (static_cast<usize>(i) < find_location_index(stm, stm.list.at(i - 1).as_cond->value))
                {
                    decompile_dowhile(stm, i - 1, i);
                    i = static_cast<i32>(stm.list.size());
                    continue;
                }
            }

            if (i == static_cast<i32>(start)) // empty inf loop
            {
                decompile_inf(stm, start, i);
            }
            else if (stm.list.at(start) != node::asm_jmp_cond) // no condition
            {
                decompile_inf(stm, start, i);
            }
            else if (stm.list.at(start).as_cond->value != break_loc) // condition belong to other stmt
            {
                decompile_inf(stm, start, i);
            }
            else // condition belong to loop
            {
                decompile_loop(stm, start, i);
            }

            i = static_cast<i32>(stm.list.size());
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
        auto const& entry = stm.list.at(i);

        if (entry == node::asm_jmp_cond)
        {
            auto j = find_location_index(stm, entry.as_cond->value) - 1;
            auto last_loc = locs_.end;

            if (stm.list.at(j) == node::asm_jmp)
            {
                // if scope is a loop check break, continue
                if (stm.list.at(j).as_jump->value == locs_.cnt)
                {
                    // check for if/else or if/continue
                    if (j - i > 1 && stm.list.at(j - 1) == node::stmt_return)
                    {
                        // scope ends with a return, so jump belows to if/else
                        decompile_ifelse(stm, i, j);
                    }
                    else if (j - i > 1 && stm.list.at(j - 1) == node::asm_jmp)
                    {
                        if (stm.list.at(j - 1).as_jump->value == locs_.brk)
                        {
                            // scope ends with a break, so jump belows to if/else
                            decompile_ifelse(stm, i, j);
                        }
                        else if (stm.list.at(j - 1).as_jump->value == locs_.cnt)
                        {
                            // if { break/return } else { continue } at loop scope end
                            if (j - i > 2 && (stm.list.at(j - 2) == node::asm_jmp || stm.list.at(j - 2) == node::stmt_return))
                            {
                                decompile_if(stm, i, j);
                            }
                            else
                            {
                                // scope ends with a continue, so jump belows to if/else
                                decompile_ifelse(stm, i, j);
                            }
                        }
                        else
                        {
                            // jump belows to if/continue
                            decompile_if(stm, i, j);
                        }
                    }
                    else 
                    {   // last if/else inside a loop still trigger this :(
                        decompile_if(stm, i, j);
                    }
                }
                else if (stm.list.at(j).as_jump->value == locs_.brk)
                {
                    decompile_if(stm, i, j);
                }
                else if (stm.list.at(j).as_jump->value == entry.as_cond->value)
                {
                    if (find_location_reference(stm, i + 1, j, entry.as_cond->value))
                    {
                        // if scope, have a empty else inside at end
                        decompile_if(stm, i, j);
                    }
                    else
                    {
                        decompile_ifelse(stm, i, j); // if scope with empty else
                    }
                }
                else
                {
                    decompile_ifelse(stm, i, j);
                }
            }
            else if (stm.list.at(j) == node::stmt_return && stm.list.at(j).as_return->value == node::null)
            {
                if(entry.as_cond->value != locs_.end)
                {
                    auto ref = stm.list.at(j + 1).label();

                    if (find_location_reference(stm, i + 1, j, ref))
                    {
                        // after return is referenced inside the scope
                        decompile_if(stm, i, j);
                        continue;
                    }
                }

                if (locs_.brk != "" || locs_.cnt != "")
                {
                    decompile_if(stm, i, j); // inside a loop cant be last
                }
                else if (j - i  == 1)
                {
                    decompile_if(stm, i, j); // only one explicit return
                }
                else if (stm.list.back() != node::stmt_return)
                {
                    decompile_if(stm, i, j); // scope end is not a last return
                }
                else if (locs_.last && stm.list.back() != node::stmt_return)
                {
                    decompile_if(stm, i, j); // inside a last scope but is not and inner last
                }
                else if (find_location_reference(stm, j, stm.list.size(), last_loc))
                {
                    decompile_if(stm, i, j); // reference to func end after the if
                }
                else if (!locs_.last)
                {
                    decompile_if(stm, i, j); // fake last ifelse
                }
                else
                {
                    decompile_ifelse_end(stm, i, j); // special case
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
    for (auto i = 0u; i < stm.list.size(); i++)
    {
        if (stm.list[i] == node::asm_jmp)
        {
            auto const loc = stm.list[i].loc();
            auto const jmp = stm.list[i].as_jump->value;

            if (jmp == locs_.brk)
            {
                stm.list.erase(stm.list.begin() + i);
                stm.list.insert(stm.list.begin() + i, stmt{ make_stmt_break(loc) });
            }
            else if (jmp == locs_.cnt)
            {
                stm.list.erase(stm.list.begin() + i);
                stm.list.insert(stm.list.begin() + i, stmt{ make_stmt_continue(loc) });
            }
            else
            {
                fmt::print("WARNING: unresolved jump to '{}', maybe incomplete for loop\n", jmp);
            }
        }
    }
}

auto decompiler::decompile_tuples(stmt_list& stm) -> void
{
    for (auto i = 1u; i < stm.list.size(); i++)
    {
        if (stm.list.at(i) == node::asm_clear)
        {
            auto j = i - 1;
            auto found = false, done = false;

            while (j >= 0 && stm.list.at(j) == node::stmt_assign)
            {
                auto const& exp = stm.list.at(j).as_assign->value;

                if (exp != node::expr_assign_equal)
                    break;

                if (!done)
                {
                    if (exp.as_assign_equal->rvalue != node::expr_array)
                        break;

                    if (exp.as_assign_equal->rvalue.as_array->key != node::expr_integer)
                        break;

                    if (exp.as_assign_equal->rvalue.as_array->key.as_integer->value == "0")
                        done = true;

                    j--;
                }
                else
                {
                    if (exp.as_assign_equal->lvalue == node::asm_create || exp.as_assign_equal->lvalue == node::asm_access)
                        found = true;

                    break;
                }
            }

            if (found)
            {
                auto& entry = stm.list.at(j);  // temp = expr;
                auto tuple = make_expr_tuple(entry.loc());
                tuple->temp = std::move(entry.as_assign->value.as_assign_equal->lvalue);
                j++;

                while (j < i)
                {
                    tuple->list.push_back(std::move(stm.list.at(j).as_assign->value.as_assign_equal->lvalue));
                    stm.list.erase(stm.list.begin() + j);
                    i--;
                }

                stm.list.erase(stm.list.begin() + j); // clear temp array
                i--;

                entry.as_assign->value.as_assign_equal->lvalue = expr{ std::move(tuple) };
            }
        }
    }
}

auto decompiler::decompile_if(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
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
    locs_.last = false;
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
    locs_.last = false;
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

auto decompiler::decompile_ifelse_end(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = true;
    locs_.end = stm.list[find_location_index(stm, stm.list[begin].as_cond->value) - 1].label();

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

    stm.list.erase(stm.list.begin() + begin);

    decompile_statements(*body_if);
    locs_ = save;

    if (begin == stm.list.size())
    {
        stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_if(loc, std::move(test), stmt{ make_stmt_comp(loc, std::move(body_if)) }) });
    }
    else
    {
        end = stm.list.size() - 1;
        save = locs_;
        locs_.last = true;
        locs_.end = stm.list[end].label();

        auto body_else = make_stmt_list(loc);

        for (auto i = begin; i < end; i++)
        {
            body_else->list.push_back(std::move(stm.list[begin]));
            stm.list.erase(stm.list.begin() + begin);
        }

        stm.list.erase(stm.list.begin() + begin);

        decompile_statements(*body_else);
        locs_ = save;
        stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_ifelse(loc, std::move(test), stmt{ make_stmt_comp(loc, std::move(body_if)) }, stmt{ make_stmt_comp(loc, std::move(body_else)) }) });
    }
}

auto decompiler::decompile_inf(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
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

auto decompiler::decompile_loop(stmt_list& stm, usize start, usize end) -> void
{
    auto const& last = stm.list.at(end - 1);

    if (last == node::stmt_assign)
    {
        if (last.as_assign->value == node::expr_assign_equal)
        {
            auto& val = last.as_assign->value.as_assign_equal->rvalue;

            if (val == node::expr_call && val.as_call->value == node::expr_function)
            {
                if (utils::string::to_lower(val.as_call->value.as_function->name->value) == "getnextarraykey")
                {
                    auto ref = stm.list.at(start).label();

                    if (!find_location_reference(stm, 0, start, ref))
                    {
                        decompile_foreach(stm, start, end);
                        return;
                    }
                }
            }
        }

        if (start > 0) // while at func start
        {
            auto index = 1;
            while (stm.list.at(start - index) == node::asm_create)
            {
                if (start - index > 0)
                    index++;
                else
                    break;
            }

            if (stm.list.at(start - index) == node::stmt_assign)
            {
                auto ref = stm.list.at(end).label();
                auto ref2 = stm.list.at(start - index + 1).label();

                if (find_location_reference(stm, start, end, ref))
                {
                    // jump is referenced, not post-expr
                    decompile_while(stm, start, end);
                    return;
                }
                else if (find_location_reference(stm, 0, start, ref2))
                {
                    // begin is at condition or localVarCreate, not pre-expr
                    decompile_while(stm, start, end);
                    return;
                }
                else
                {
                    decompile_for(stm, start, end);
                    return;
                }
            }
        }
    }

    decompile_while(stm, start, end);
}

auto decompiler::decompile_while(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
    locs_.end = stm.list[end].label();
    locs_.cnt = stm.list[end].label();
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
    locs_.last = false;
    locs_.end = stm.list[begin].label();
    locs_.cnt = stm.list[begin].label();
    locs_.brk = stm.list[begin].as_cond->value;

    auto test = std::move(stm.list[begin].as_cond->test);
    begin = find_location_index(stm, stm.list[end].as_jump_back->value);
    auto loc = stm.list[begin].loc();

    end--;
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
    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_dowhile(loc, std::move(test), stmt{ make_stmt_comp(loc, std::move(body)) }) });
}

auto decompiler::decompile_for(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
    locs_.end = stm.list[end - 1].label();
    locs_.cnt = stm.list[end - 1].label();
    locs_.brk = stm.list[begin].as_cond->value;

    for (begin -= 1; stm.list[begin] == node::asm_create; begin--);

    auto loc = stm.list[begin].loc();
    auto init = make_stmt_list(loc);

    while (stm.list[begin] != node::asm_jmp_cond)
    {
        init->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    auto test = std::move(stm.list[begin].as_cond->test);
    stm.list.erase(stm.list.begin() + begin);

    end -= 2 + init->list.size();

    auto iter = make_stmt_list(loc);
    iter->list.push_back(std::move(stm.list[end]));
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
    locs_.last = false;
    locs_.end = stm.list[end - 1].label();
    locs_.cnt = stm.list[end - 1].label();
    locs_.brk = stm.list[begin].as_cond->value;

    for (begin -= 1; stm.list[begin] == node::asm_create; begin--);

    auto use_index = false;

    if ((ctx_->props() & props::foreach) && stm.list[begin] == node::stmt_assign && stm.list[begin].as_assign->value.as_assign->rvalue == node::expr_undefined)
    {
        use_index = true;
        begin--;
    }

    begin--;

    auto loc = stm.list[begin].loc();

    auto container = std::move(stm.list[begin].as_assign->value.as_assign->rvalue);
    auto array = std::move(stm.list[begin].as_assign->value.as_assign->lvalue);
    stm.list.erase(stm.list.begin() + begin);

    auto key = std::move(stm.list[begin].as_assign->value.as_assign->lvalue);
    stm.list.erase(stm.list.begin() + begin);

    auto index = (use_index) ? std::move(stm.list[begin].as_assign->value.as_assign->lvalue): expr{ make_node() };
    
    if (use_index)
    {
        stm.list.erase(stm.list.begin() + begin);
    }

    auto init = make_stmt_list(loc);

    while (stm.list[begin] != node::asm_jmp_cond)
    {
        init->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    stm.list.erase(stm.list.begin() + begin);

    auto value = std::move(stm.list[begin].as_assign->value.as_assign->lvalue);
    stm.list.erase(stm.list.begin() + begin);

    if (use_index)
    {
        stm.list.erase(stm.list.begin() + begin);
    }

    end -= (use_index ? 7 : 5) + init->list.size();
    stm.list.erase(stm.list.begin() + end);
    stm.list.erase(stm.list.begin() + end);

    auto use_key = true;

    if (stm.list.size() > end && stm.list[end] == node::asm_clear)
    {
        stm.list.erase(stm.list.begin() + end);
    }

    if (stm.list.size() > end && stm.list[end] == node::asm_clear)
    {
        stm.list.erase(stm.list.begin() + end);
        use_key = false;
    }

    auto body = make_stmt_list(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    body->list.insert(body->list.begin(), stmt{ std::move(init) });
    stm.list.insert(stm.list.begin() + begin, stmt{ make_stmt_foreach(loc, std::move(container), std::move(value), std::move(index), std::move(array), std::move(key), stmt{ make_stmt_comp(loc, std::move(body)) }, (ctx_->props() & props::foreach) ? use_index : use_key) });
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
                if (ctx_->engine() == engine::iw9)
                {
                    type = static_cast<switch_type>(std::stoul(data[index + 1])); 
                    auto j = find_location_index(stm, data[index + 3]);
                    auto loc = stm.list[j].loc();
                    auto exp = (type == switch_type::integer) ? expr{ make_expr_integer(loc, data[index + 2]) } : expr{ make_expr_string(loc, data[index + 2]) };
                    while (stm.list[j] == node::stmt_case) j++;
                    stm.list.insert(stm.list.begin() + j, stmt{ make_stmt_case(loc, std::move(exp), make_stmt_list(loc)) });
                    index += 4; 
                }
                else
                {
                    auto j = find_location_index(stm, data[index + 2]);
                    auto loc = stm.list[j].loc();
                    auto exp = (type == switch_type::integer) ? expr{ make_expr_integer(loc, data[index + 1]) } : expr{ make_expr_string(loc, data[index + 1]) };
                    while (stm.list[j] == node::stmt_case) j++;
                    stm.list.insert(stm.list.begin() + j, stmt{ make_stmt_case(loc, std::move(exp), make_stmt_list(loc)) });
                    index += 3;
                }
                
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
    locs_.last = false;
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
    return (index == stm.list.size() - 1) ? true : false;
}

auto decompiler::process_function(decl_function& func) -> void
{
    auto scp_body = make_scope();

    for (auto const& entry : func.params->list)
    {
        scp_body->vars.push_back({ entry->value, static_cast<u8>(scp_body->create_count), true });
        scp_body->create_count++;
    }

    process_stmt_comp(*func.body, *scp_body);
}

auto decompiler::process_stmt(stmt& stm, scope& scp) -> void
{
    switch (stm.kind())
    {
        case node::stmt_list:
            process_stmt_list(*stm.as_list, scp);
            break;
        case node::stmt_comp:
            process_stmt_comp(*stm.as_comp, scp);
            break;
        case node::stmt_dev:
            process_stmt_dev(*stm.as_dev, scp);
            break;
        case node::stmt_expr:
            process_stmt_expr(*stm.as_expr, scp);
            break;
        case node::stmt_call:
            process_stmt_call(*stm.as_call, scp);
            break;
        case node::stmt_assign:
            process_stmt_assign(*stm.as_assign, scp);
            break;
        case node::stmt_endon:
            process_stmt_endon(*stm.as_endon, scp);
            break;
        case node::stmt_notify:
            process_stmt_notify(*stm.as_notify, scp);
            break;
        case node::stmt_wait:
            process_stmt_wait(*stm.as_wait, scp);
            break;
        case node::stmt_waittill:
            process_stmt_waittill(*stm.as_waittill, scp);
            break;
        case node::stmt_waittillmatch:
            process_stmt_waittillmatch(*stm.as_waittillmatch, scp);
            break;
        case node::stmt_if:
            process_stmt_if(*stm.as_if, scp);
            break;
        case node::stmt_ifelse:
            process_stmt_ifelse(*stm.as_ifelse, scp);
            break;
        case node::stmt_while:
            process_stmt_while(*stm.as_while, scp);
            break;
        case node::stmt_dowhile:
            process_stmt_dowhile(*stm.as_dowhile, scp);
            break;
        case node::stmt_for:
            process_stmt_for(*stm.as_for, scp);
            break;
        case node::stmt_foreach:
            process_stmt_foreach(*stm.as_foreach, scp);
            break;
        case node::stmt_switch:
            process_stmt_switch(*stm.as_switch, scp);
            break;
        case node::stmt_break:
            process_stmt_break(*stm.as_break, scp);
            break;
        case node::stmt_continue:
            process_stmt_continue(*stm.as_continue, scp);
            break;
        case node::stmt_return:
            process_stmt_return(*stm.as_return, scp);
            break;
        case node::asm_create:
            process_stmt_asm_create(*stm.as_asm_create, scp);
            break;
        case node::asm_remove:
            process_stmt_asm_remove(*stm.as_asm_remove, scp);
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_list(stmt_list& stm, scope& scp) -> void
{
    for (auto& entry : stm.list)
    {
        process_stmt(entry, scp);
    }

    for (auto i = 0u; i < stm.list.size(); )
    {
        if (stm.list[i] == node::asm_create || stm.list[i] == node::asm_remove)
            stm.list.erase(stm.list.begin() + i);
        else
            i++;
    }
}

auto decompiler::process_stmt_comp(stmt_comp& stm, scope& scp) -> void
{
    process_stmt_list(*stm.block, scp);
}

auto decompiler::process_stmt_dev(stmt_dev& stm, scope& scp) -> void
{
    process_stmt_list(*stm.block, scp);
}

auto decompiler::process_stmt_expr(stmt_expr& stm, scope& scp) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_increment:
            process_expr_increment(*stm.value.as_increment, scp);
            break;
        case node::expr_decrement:
            process_expr_decrement(*stm.value.as_decrement, scp);
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
            process_expr_assign(stm.value.as_assign, scp);
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_call(stmt_call& stm, scope& scp) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_call:
            process_expr_call(*stm.value.as_call, scp);
            break;
        case node::expr_method:
            process_expr_method(*stm.value.as_method, scp);
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_assign(stmt_assign& stm, scope& scp) -> void
{
    switch (stm.value.kind())
    {
        case node::expr_increment:
            process_expr_increment(*stm.value.as_increment, scp);
            break;
        case node::expr_decrement:
            process_expr_decrement(*stm.value.as_decrement, scp);
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
            process_expr_assign(stm.value.as_assign, scp);
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_endon(stmt_endon& stm, scope& scp) -> void
{
    process_expr(stm.event, scp);
    process_expr(stm.obj, scp);
}

void decompiler::process_stmt_notify(stmt_notify& stm, scope& scp)
{
    process_expr_arguments(*stm.args, scp);
    process_expr(stm.event, scp);
    process_expr(stm.obj, scp);
}

auto decompiler::process_stmt_wait(stmt_wait& stm, scope& scp) -> void
{
    process_expr(stm.time, scp);
}

auto decompiler::process_stmt_waittill(stmt_waittill& stm, scope& scp) -> void
{
    process_expr(stm.event, scp);
    process_expr(stm.obj, scp);

    for (auto& entry : stm.args->list)
    {
        process_expr(entry, scp);
    }
}

auto decompiler::process_stmt_waittillmatch(stmt_waittillmatch& stm, scope& scp) -> void
{
    process_expr_arguments(*stm.args, scp);
    process_expr(stm.event, scp);
    process_expr(stm.obj, scp);
}

auto decompiler::process_stmt_if(stmt_if& stm, scope& scp) -> void
{
    auto scp_then = make_scope();

    process_expr(stm.test, scp);

    scp.transfer_dec(scp_then);

    process_stmt(stm.body, *scp_then);

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_ifelse(stmt_ifelse& stm, scope& scp) -> void
{
    auto childs = std::vector<scope*>{};
    auto abort = scope::abort_return;
    auto scp_then = make_scope();
    auto scp_else = make_scope();

    process_expr(stm.test, scp);

    scp.transfer_dec(scp_then);

    process_stmt(stm.stmt_if, *scp_then);

    if (scp_then->abort <= scope::abort_return)
    {
        abort = scp_then->abort;

        if (abort == scope::abort_none)
            childs.push_back(scp_then.get());
    }

    scp.transfer_dec(scp_else);

    process_stmt(stm.stmt_else, *scp_else);

    if (scp_else->abort <= abort)
    {
        abort = scp_else->abort;

        if (abort == scope::abort_none)
            childs.push_back(scp_else.get());
    }

    if (scp.abort == scope::abort_none)
        scp.abort = abort;

    scp.append(childs);

    if (stm.stmt_if.as_comp->block->list.size() == 1 && !stm.stmt_if.as_comp->block->list[0].as_node->is_special_stmt())
    {
        stm.stmt_if = std::move(stm.stmt_if.as_comp->block->list.back());
    }

    if (stm.stmt_else.as_comp->block->list.size() == 1 && !stm.stmt_else.as_comp->block->list[0].as_node->is_special_stmt_noif())
    {
        stm.stmt_else = std::move(stm.stmt_else.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_while(stmt_while& stm, scope& scp) -> void
{
    auto scp_body = make_scope();

    process_expr(stm.test, scp);

    scp.transfer_dec(scp_body);

    process_stmt(stm.body, *scp_body);

    if (stm.test == node::null)
        scp.append_dec(scp_body);

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_dowhile(stmt_dowhile& stm, scope& scp) -> void
{
    auto scp_body = make_scope();

    process_expr(stm.test, scp);

    scp.transfer_dec(scp_body);

    process_stmt(stm.body, *scp_body);

    if (stm.test == node::null)
        scp.append_dec(scp_body);

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_for(stmt_for& stm, scope& scp) -> void
{
    auto scp_body = make_scope();

    process_stmt(stm.init, scp);

    if (stm.init == node::stmt_list && stm.init.as_list->list[0] == node::stmt_assign)
    {
        stm.init = stmt{ make_stmt_expr(stm.init.loc(), std::move(stm.init.as_list->list[0].as_assign->value)) };
    }

    scp.transfer_dec(scp_body);

    process_expr(stm.test, scp);

    process_stmt(stm.body, *scp_body);

    process_stmt(stm.iter, scp);

    if (stm.iter == node::stmt_list && stm.iter.as_list->list[0] == node::stmt_assign)
    {
        stm.iter = stmt{ make_stmt_expr(stm.iter.loc(), std::move(stm.iter.as_list->list[0].as_assign->value)) };
    }

    if (stm.test == node::null)
        scp.append_dec(scp_body);

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_foreach(stmt_foreach& stm, scope& scp) -> void
{
    auto scp_body = make_scope();

    process_expr(stm.container, scp);
    process_expr(stm.array, scp);
    process_expr(stm.key, scp);

    if ((ctx_->props() & props::foreach) && stm.use_key)
    {
        process_expr(stm.index, scp);
    }

    process_stmt(stm.body.as_comp->block->list[0], scp);

    stm.body.as_comp->block->list.erase(stm.body.as_comp->block->list.begin());

    scp.transfer_dec(scp_body);

    process_expr(stm.value, *scp_body);
    process_stmt(stm.body, *scp_body);

    if (stm.body.as_comp->block->list.size() == 1 && !stm.body.as_comp->block->list[0].as_node->is_special_stmt())
    {
        stm.body = std::move(stm.body.as_comp->block->list.back());
    }
}

auto decompiler::process_stmt_switch(stmt_switch& stm, scope& scp) -> void
{
    auto scopes = std::vector<scope::ptr>{};
    auto childs = std::vector<scope*>{};
    auto has_default = false;

    process_expr(stm.test, scp);

    for (auto& entry : stm.body->block->list)
    {
        if (entry == node::stmt_case)
        {
            auto scp_case = make_scope();

            scp.transfer_dec(scp_case);

            process_stmt_list(*entry.as_case->body, *scp_case);

            if (scp_case->abort == scope::abort_break)
            {
                childs.push_back(scp_case.get());
                scopes.push_back(std::move(scp_case));
            }
        }
        else if (entry == node::stmt_default)
        {
            has_default = true;
            auto scp_case = make_scope();

            scp.transfer_dec(scp_case);

            process_stmt_list(*entry.as_default->body, *scp_case);

            if (scp_case->abort == scope::abort_break)
            {
                childs.push_back(scp_case.get());
                scopes.push_back(std::move(scp_case));
            }
        }
    }

    if (has_default)
    {
        scp.append(childs);
    }
}

auto decompiler::process_stmt_break(stmt_break&, scope& scp) -> void
{
    if (scp.abort == scope::abort_none)
    {
        scp.abort = scope::abort_break;
    }
}

auto decompiler::process_stmt_continue(stmt_continue&, scope& scp) -> void
{
    if (scp.abort == scope::abort_none)
    {
        scp.abort = scope::abort_continue;
    }
}

auto decompiler::process_stmt_return(stmt_return& stm, scope& scp) -> void
{
    if (scp.abort == scope::abort_none)
    {
        scp.abort = scope::abort_return;
    }

    if (stm.value != node::null)
    {
        process_expr(stm.value, scp);
    }
}

auto decompiler::process_stmt_asm_create(asm_create& stm, scope& scp) -> void
{
    auto var = (ctx_->props() & props::hash) ? stm.index : fmt::format("var_{}", stm.index);
    scp.vars.push_back({ var, static_cast<u8>(scp.create_count), true });
    scp.create_count++;
}

auto decompiler::process_stmt_asm_remove(asm_remove& stm, scope& scp) -> void
{
    scp.public_count = static_cast<u32>(scp.vars.size() - std::stoi(stm.index));
}

auto decompiler::process_expr(expr& exp, scope& scp) -> void
{
    switch (exp.kind())
    {
        case node::expr_ternary:
            process_expr_ternary(*exp.as_ternary, scp);
            break;
        case node::expr_and:
            process_expr_and(*exp.as_and, scp);
            break;
        case node::expr_or:
            process_expr_or(*exp.as_or, scp);
            break;
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
            process_expr_binary(*exp.as_binary, scp);
            break;
        case node::expr_complement:
            process_expr_complement(*exp.as_complement, scp);
            break;
        case node::expr_not:
            process_expr_not(*exp.as_not, scp);
            break;
        case node::expr_call:
            process_expr_call(*exp.as_call, scp);
            break;
        case node::expr_method:
            process_expr_method(*exp.as_method, scp);
            break;
        case node::expr_isdefined:
            process_expr(exp.as_isdefined->value, scp);
            break;
        case node::expr_istrue:
            process_expr(exp.as_istrue->value, scp);
            break;
        case node::expr_add_array:
            process_expr_add_array(*exp.as_add_array, scp);
            break;
        case node::expr_size:
            process_expr_size(*exp.as_size, scp);
            break;
        case node::expr_tuple:
            process_expr_tuple(*exp.as_tuple, scp);
            break;
        case node::expr_array:
            process_expr_array(*exp.as_array, scp);
            break;
        case node::expr_field:
            process_expr_field(*exp.as_field, scp);
            break;
        case node::expr_vector:
            process_expr_vector(*exp.as_vector, scp);
            break;
        case node::asm_create:
            process_expr_asm_create(exp, scp);
            break;
        case node::asm_access:
            process_expr_asm_access(exp, scp);
            break;
        default:
            break;
    }
}

auto decompiler::process_expr_assign(expr_assign::ptr& exp, scope& scp) -> void
{
    process_expr(exp->rvalue, scp);
    process_expr(exp->lvalue, scp);

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

auto decompiler::process_expr_increment(expr_increment& exp, scope& scp) -> void
{
    process_expr(exp.lvalue, scp);
}

auto decompiler::process_expr_decrement(expr_decrement& exp, scope& scp) -> void
{
    process_expr(exp.lvalue, scp);
}

auto decompiler::process_expr_ternary(expr_ternary& exp, scope& scp) -> void
{
    process_expr(exp.test, scp);
    process_expr(exp.true_expr, scp);
    process_expr(exp.false_expr, scp);
}

auto decompiler::process_expr_binary(expr_binary& exp, scope& scp) -> void
{
    process_expr(exp.lvalue, scp);
    process_expr(exp.rvalue, scp);

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

auto decompiler::process_expr_and(expr_and& exp, scope& scp) -> void
{
    process_expr(exp.lvalue, scp);
    process_expr(exp.rvalue, scp);

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

auto decompiler::process_expr_or(expr_or& exp, scope& scp) -> void
{
    process_expr(exp.lvalue, scp);
    process_expr(exp.rvalue, scp);
}

auto decompiler::process_expr_complement(expr_complement& exp, scope& scp) -> void
{
    process_expr(exp.rvalue, scp);

    if (exp.rvalue.as_node->is_binary())
    {
        exp.rvalue = expr{ make_expr_paren(exp.loc(), std::move(exp.rvalue)) };
    }
}

auto decompiler::process_expr_not(expr_not& exp, scope& scp) -> void
{
    process_expr(exp.rvalue, scp);

    if (exp.rvalue.as_node->is_binary())
    {
        exp.rvalue = expr{ make_expr_paren(exp.loc(), std::move(exp.rvalue)) };
    }
}

auto decompiler::process_expr_call(expr_call& exp, scope& scp) -> void
{
    switch (exp.value.kind())
    {
        case node::expr_pointer:
            process_expr_call_pointer(*exp.value.as_pointer, scp);
            break;
        case node::expr_function:
            process_expr_call_function(*exp.value.as_function, scp);
            break;
        default:
            break;
    }
}

auto decompiler::process_expr_method(expr_method& exp, scope& scp) -> void
{
    switch (exp.value.kind())
    {
        case node::expr_pointer:
            process_expr_method_pointer(*exp.value.as_pointer, exp.obj, scp);
            break;
        case node::expr_function:
            process_expr_method_function(*exp.value.as_function, exp.obj, scp);
            break;
        default:
            break;
    }
}

auto decompiler::process_expr_call_pointer(expr_pointer& exp, scope& scp) -> void
{
    process_expr_arguments(*exp.args, scp);
    process_expr(exp.func, scp);
}

auto decompiler::process_expr_call_function(expr_function& exp, scope& scp) -> void
{
    process_expr_arguments(*exp.args, scp);
}

auto decompiler::process_expr_method_pointer(expr_pointer& exp, expr& obj, scope& scp) -> void
{
    process_expr_arguments(*exp.args, scp);
    process_expr(obj, scp);
    process_expr(exp.func, scp);
}

auto decompiler::process_expr_method_function(expr_function& exp, expr& obj, scope& scp) -> void
{
    process_expr_arguments(*exp.args, scp);
    process_expr(obj, scp);
}

auto decompiler::process_expr_arguments(expr_arguments& exp, scope& scp) -> void
{
    for (auto i = exp.list.size(); i > 0; i--)
    {
        process_expr(exp.list[i - 1], scp);
    }
}

auto decompiler::process_expr_add_array(expr_add_array& exp, scope& scp) -> void
{
    for (auto& entry : exp.args->list)
    {
        process_expr(entry, scp);
    }
}

auto decompiler::process_expr_size(expr_size& exp, scope& scp) -> void
{
    process_expr(exp.obj, scp);
}

auto decompiler::process_expr_tuple(expr_tuple& exp, scope& scp) -> void
{
    process_expr(exp.temp, scp);

    for (auto& entry : exp.list)
    {
        process_expr(entry, scp);
    }
}

auto decompiler::process_expr_array(expr_array& exp, scope& scp) -> void
{
    process_expr(exp.key, scp);
    process_expr(exp.obj, scp);
}

auto decompiler::process_expr_field(expr_field& exp, scope& scp) -> void
{
    process_expr(exp.obj, scp);
}

auto decompiler::process_expr_vector(expr_vector& exp, scope& scp) -> void
{
    process_expr(exp.z, scp);
    process_expr(exp.y, scp);
    process_expr(exp.x, scp);
}

auto decompiler::process_expr_asm_create(expr& exp, scope& scp) -> void
{
    for (auto const& entry : exp.as_asm_create->vars)
    {
        auto var = (ctx_->props() & props::hash) ? entry : fmt::format("var_{}", entry);
        scp.vars.push_back({ var, static_cast<u8>(scp.create_count), true });
        scp.create_count++;
    }

    auto var = (ctx_->props() & props::hash) ? exp.as_asm_create->index : fmt::format("var_{}", exp.as_asm_create->index);
    scp.vars.push_back({ var, static_cast<u8>(scp.create_count), true });
    scp.create_count++;

    exp = expr{ make_expr_identifier(exp.loc(), var) };
}

auto decompiler::process_expr_asm_access(expr& exp, scope& scp) -> void
{
    auto const index = std::stoul(exp.as_asm_access->index);

    if (scp.vars.size() <= index)
    {
        fmt::print("WARNING: bad local var access\n");
    }
    else
    {
        exp = expr{ make_expr_identifier(exp.loc(), scp.vars[scp.vars.size() - 1 - index].name) };
    }
}

} // namespace xsk::gsc
