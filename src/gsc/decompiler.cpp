// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/gsc/decompiler.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc
{

decompiler::decompiler(context const* ctx) : ctx_{ ctx }
{
}

auto decompiler::decompile(assembly const& data) -> program::ptr
{
    program_ = program::make();

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

    auto loc = location{ nullptr, static_cast<i32>(func.index) };
    auto name = expr_identifier::make(loc, func.name);
    auto prms = expr_parameters::make(loc);
    auto body = stmt_comp::make(loc, stmt_list::make(loc));
    func_ = decl_function::make(loc, std::move(name), std::move(prms), std::move(body));

    for (auto const& inst : func.instructions)
    {
        decompile_instruction(*inst);
    }

    if (!stack_.empty())
    {
        std::cout << std::format("[WRN]: orphan stack data at function {}\n", func.name);
        //throw decomp_error("stack isn't empty at function end");
    }

    locs_.last = true;
    locs_.end = func_->body->block->list.back()->label();
    func_->body->block->list.pop_back();

    decompile_statements(*func_->body->block);
    process_function(*func_);

    program_->declarations.push_back(std::move(func_));
}

auto decompiler::decompile_instruction(instruction const& inst) -> void
{
    decompile_expressions(inst);

    auto loc = location{ nullptr, static_cast<i32>(inst.index) };

    switch (inst.opcode)
    {
        case opcode::OP_End:
        {
            func_->body->block->list.push_back(stmt_return::make(loc, expr_empty::make(loc)));
            break;
        }
        case opcode::OP_Return:
        {
            auto value = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_return::make(value->loc(), std::move(value)));
            break;
        }
        case opcode::OP_GetZero:
        {
            stack_.push(expr_integer::make(loc, "0"));
            break;
        }
        case opcode::OP_GetByte:
        case opcode::OP_GetUnsignedShort:
        case opcode::OP_GetUnsignedInt:
        case opcode::OP_GetInteger:
        case opcode::OP_GetInteger64:
        {
            stack_.push(expr_integer::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetNegByte:
        case opcode::OP_GetNegUnsignedShort:
        case opcode::OP_GetNegUnsignedInt:
        {
            stack_.push(expr_integer::make(loc, "-" + inst.data[0]));
            break;
        }
        case opcode::OP_GetFloat:
        {
            stack_.push(expr_float::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetVector:
        {
            auto x = expr_float::make(loc, inst.data[0]);
            auto y = expr_float::make(loc, inst.data[1]);
            auto z = expr_float::make(loc, inst.data[2]);
            stack_.push(expr_vector::make(loc, std::move(x), std::move(y), std::move(z)));
            break;
        }
        case opcode::OP_GetString:
        {
            stack_.push(expr_string::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetIString:
        {
            stack_.push(expr_istring::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetUndefined:
        {
            stack_.push(expr_undefined::make(loc));
            break;
        }
        case opcode::OP_EmptyArray:
        {
            stack_.push(expr_empty_array::make(loc));
            break;
        }
        case opcode::OP_GetLevel:
        case opcode::OP_GetLevelObject:
        {
            stack_.push(expr_level::make(loc));
            break;
        }
        case opcode::OP_GetAnim:
        case opcode::OP_GetAnimObject:
        {
            stack_.push(expr_anim::make(loc));
            break;
        }
        case opcode::OP_GetSelf:
        case opcode::OP_GetSelfObject:
        {
            stack_.push(expr_self::make(loc));
            break;
        }
        case opcode::OP_GetGame:
        case opcode::OP_GetGameRef:
        {
            stack_.push(expr_game::make(loc));
            break;
        }
        case opcode::OP_GetAnimation:
        {
            if (!inst.data[0].empty())
            {
                auto dec = decl_usingtree::make(loc, expr_string::make(loc, inst.data[0]));
                program_->declarations.push_back(std::move(dec));
            }

            stack_.push(expr_animation::make(loc, inst.data[1]));
            break;
        }
        case opcode::OP_GetAnimTree:
        {
            if (!inst.data[0].empty())
            {
                auto dec = decl_usingtree::make(loc, expr_string::make(loc, inst.data[0]));
                program_->declarations.push_back(std::move(dec));
            }

            stack_.push(expr_animtree::make(loc));
            break;
        }
        case opcode::OP_GetThisthread:
        {
            stack_.push(expr_thisthread::make(loc));
            break;
        }
        case opcode::OP_GetBuiltinFunction:
        case opcode::OP_GetBuiltinMethod:
        {
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_reference::make(loc, std::move(path), std::move(name)));
            break;
        }
        case opcode::OP_GetLocalFunction:
        {
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_reference::make(loc, std::move(path), std::move(name)));
            break;
        }
        case opcode::OP_GetFarFunction:
        {
            auto path = expr_path::make(loc, inst.data[0]);
            auto name = expr_identifier::make(loc, inst.data[1]);
            stack_.push(expr_reference::make(loc, std::move(path), std::move(name)));
            break;
        }
        case opcode::OP_CreateLocalVariable:
        {
            if (in_waittill_)
            {
                stack_.push(expr_var_create::make(loc, inst.data[0]));
            }
            else
            {
                func_->body->block->list.push_back(stmt_create::make(loc, inst.data[0]));
            }
            break;
        }
        case opcode::OP_RemoveLocalVariables:
        {
            func_->body->block->list.push_back(stmt_remove::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_EvalLocalVariableCached0:
        {
            stack_.push(expr_var_access::make(loc, "0"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached1:
        {
            stack_.push(expr_var_access::make(loc, "1"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached2:
        {
            stack_.push(expr_var_access::make(loc, "2"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached3:
        {
            stack_.push(expr_var_access::make(loc, "3"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached4:
        {
            stack_.push(expr_var_access::make(loc, "4"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached5:
        {
            stack_.push(expr_var_access::make(loc, "5"));
            break;
        }
        case opcode::OP_EvalLocalVariableCached:
        {
            stack_.push(expr_var_access::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_EvalLocalArrayCached:
        {
            auto key = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = expr_var_access::make(loc, inst.data[0]);
            stack_.push(expr_array::make(key->loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalArray:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto key = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_array::make(key->loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalNewLocalArrayRefCached0:
        {
            auto key = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = expr_var_create::make(loc, inst.data[0]);
            stack_.push(expr_array::make(key->loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalLocalArrayRefCached0:
        {
            auto key = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = expr_var_access::make(loc, "0");
            stack_.push(expr_array::make(key->loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalLocalArrayRefCached:
        {
            auto key = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = expr_var_access::make(loc, inst.data[0]);
            stack_.push(expr_array::make(key->loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalArrayRef:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto key = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_array::make(key->loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_ClearArray:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto key = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = key->loc();
            auto lvalue = expr_array::make(loc, std::move(obj), std::move(key));
            auto rvalue = expr_undefined::make(loc);
            auto exp = expr_assign::make(loc, std::move(lvalue), std::move(rvalue), expr_assign::op::eq);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_AddArray:
        {
            auto value = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto array = std::move(stack_.top()); stack_.pop();

            if (array->kind() == node::expr_empty_array)
            {
                auto args = expr_arguments::make(loc);
                args->list.push_back(std::move(value));
                stack_.push(expr_add_array::make(array->loc(), std::move(args)));
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
            stack_.push(node_prescriptcall::make(loc));
            break;
        }
        case opcode::OP_ScriptLocalFunctionCall2:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_ScriptLocalFunctionCall:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::node_prescriptcall)
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_ScriptLocalMethodCall:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::node_prescriptcall)
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_ScriptLocalThreadCall:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_ScriptLocalChildThreadCall:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::childthread)));
            break;
        }
        case opcode::OP_ScriptLocalMethodThreadCall:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_ScriptLocalMethodChildThreadCall:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::childthread)));
            break;
        }
        case opcode::OP_ScriptFarFunctionCall2:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc, inst.data[0]);
            auto name = expr_identifier::make(loc, inst.data[1]);
            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_ScriptFarFunctionCall:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc, inst.data[0]);
            auto name = expr_identifier::make(loc, inst.data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::node_prescriptcall)
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_ScriptFarMethodCall:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc, inst.data[0]);
            auto name = expr_identifier::make(loc, inst.data[1]);

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::node_prescriptcall)
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_ScriptFarThreadCall:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc, inst.data[0]);
            auto name = expr_identifier::make(loc, inst.data[1]);

            for (auto i = std::stoul(inst.data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_ScriptFarChildThreadCall:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc, inst.data[0]);
            auto name = expr_identifier::make(loc, inst.data[1]);

            for (auto i = std::stoul(inst.data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::childthread)));
            break;
        }
        case opcode::OP_ScriptFarMethodThreadCall:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc, inst.data[0]);
            auto name = expr_identifier::make(loc, inst.data[1]);

            for (auto i = std::stoul(inst.data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_ScriptFarMethodChildThreadCall:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc, inst.data[0]);
            auto name = expr_identifier::make(loc, inst.data[1]);

            for (auto i = std::stoul(inst.data[2]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::childthread)));
            break;
        }
        case opcode::OP_ScriptFunctionCallPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::node_prescriptcall)
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(expr_call::make(loc, expr_pointer::make(loc, std::move(func), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_ScriptMethodCallPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::node_prescriptcall)
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_pointer::make(loc, std::move(func), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_ScriptThreadCallPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = func->loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_call::make(loc, expr_pointer::make(loc, std::move(func), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_ScriptChildThreadCallPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = func->loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_call::make(loc, expr_pointer::make(loc, std::move(func), std::move(args), call::mode::childthread)));
            break;
        }
        case opcode::OP_ScriptMethodThreadCallPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_pointer::make(loc, std::move(func), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_ScriptMethodChildThreadCallPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_pointer::make(loc, std::move(func), std::move(args), call::mode::childthread)));
            break;
        }
        case opcode::OP_CallBuiltinPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = func->loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_call::make(loc, expr_pointer::make(loc, std::move(func), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltinMethodPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
                args->list.push_back(node::as<expr>(std::move(var)));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_pointer::make(loc, std::move(func), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltin0:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltin1:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 1u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltin2:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 2u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltin3:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 3u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltin4:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 4u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltin5:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 5u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltin:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltinMethod0:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltinMethod1:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 1u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltinMethod2:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 2u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltinMethod3:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 3u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltinMethod4:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 4u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltinMethod5:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = 5u; i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_CallBuiltinMethod:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, inst.data[0]);

            for (auto i = std::stoul(inst.data[1]); i > 0; i--)
            {
                auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = var->loc();
                args->list.push_back(std::move(var));
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::builtin)));
            break;
        }
        case opcode::OP_DecTop:
        {
            auto exp = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_expr::make(exp->loc(), std::move(exp)));
            break;
        }
        case opcode::OP_inc:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_increment::make(lvalue->loc(), std::move(lvalue), false));
            break;
        }
        case opcode::OP_dec:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_decrement::make(lvalue->loc(), std::move(lvalue), false));
            break;
        }
        case opcode::OP_bit_or:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::bwor));
            break;
        }
        case opcode::OP_bit_ex_or:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::bwexor));
            break;
        }
        case opcode::OP_bit_and:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::bwand));
            break;
        }
        case opcode::OP_equality:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::eq));
            break;
        }
        case opcode::OP_inequality:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::ne));
            break;
        }
        case opcode::OP_less:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::lt));
            break;
        }
        case opcode::OP_greater:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::gt));
            break;
        }
        case opcode::OP_less_equal:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::le));
            break;
        }
        case opcode::OP_greater_equal:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::ge));
            break;
        }
        case opcode::OP_shift_left:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::shl));
            break;
        }
        case opcode::OP_shift_right:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::shr));
            break;
        }
        case opcode::OP_plus:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::add));
            break;
        }
        case opcode::OP_minus:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::sub));
            break;
        }
        case opcode::OP_multiply:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::mul));
            break;
        }
        case opcode::OP_divide:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::div));
            break;
        }
        case opcode::OP_mod:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::mod));
            break;
        }
        case opcode::OP_wait:
        {
            auto exp = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_wait::make(exp->loc(), std::move(exp)));
            break;
        }
        case opcode::OP_waittillFrameEnd:
        {
            func_->body->block->list.push_back(stmt_waittillframeend::make(loc));
            break;
        }
        case opcode::OP_waitframe:
        {
            func_->body->block->list.push_back(stmt_waitframe::make(loc));
            break;
        }
        case opcode::OP_waittill:
        {
            auto args = expr_arguments::make(loc);
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto event = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(stmt_waittill::make(event->loc(), std::move(obj), std::move(event), std::move(args)));
            in_waittill_ = true;
            break;
        }
        case opcode::OP_waittillmatch:
        {
            auto args = expr_arguments::make(loc);
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto event = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = event->loc();

            for (auto i = std::stoul(inst.data[0]); i > 0; i--)
            {
                auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = arg->loc();
                args->list.push_back(std::move(arg));
            }

            func_->body->block->list.push_back(stmt_waittillmatch::make(loc, std::move(obj), std::move(event), std::move(args)));
            break;
        }
        case opcode::OP_clearparams:
        {
            if (in_waittill_)
            {
                auto args = expr_arguments::make(loc);
                auto arg = std::move(stack_.top()); stack_.pop();

                while (arg->kind() != node::stmt_waittill)
                {
                    args->list.push_back(node::as<expr>(std::move(arg)));
                    arg = std::move(stack_.top()); stack_.pop();
                }

                if (arg->kind() == node::stmt_waittill)
                {
                    std::reverse(args->list.begin(), args->list.end());
                    reinterpret_cast<stmt_waittill*>(arg.get())->args = std::move(args);
                    in_waittill_ = false;
                }

                func_->body->block->list.push_back(node::as<stmt>(std::move(arg)));
            }
            break;
        }
        case opcode::OP_notify:
        {
            auto args = expr_arguments::make(loc);
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto event = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::node_voidcodepos)
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            func_->body->block->list.push_back(stmt_notify::make(loc, std::move(obj), std::move(event), std::move(args)));
            break;
        }
        case opcode::OP_endon:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto event = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_endon::make(event->loc(), std::move(obj), std::move(event)));
            break;
        }
        case opcode::OP_voidCodepos:
        {
            stack_.push(node_voidcodepos::make(loc));
            break;
        }
        case opcode::OP_vector:
        {
            auto x = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto y = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto z = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_vector::make(z->loc(), std::move(x), std::move(y), std::move(z)));
            break;
        }
        case opcode::OP_size:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_size::make(lvalue->loc(), std::move(lvalue)));
            break;
        }
        case opcode::OP_EvalLevelFieldVariable:
        {
            auto obj = expr_level::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalAnimFieldVariable:
        {
            auto obj = expr_anim::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalSelfFieldVariable:
        {
            auto obj = expr_self::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalFieldVariable:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(obj->loc(), std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalLevelFieldVariableRef:
        {
            auto obj = expr_level::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalAnimFieldVariableRef:
        {
            auto obj = expr_anim::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalSelfFieldVariableRef:
        {
            auto obj = expr_self::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_EvalFieldVariableRef:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(obj->loc(), std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_ClearFieldVariable:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();
            auto name = expr_identifier::make(loc, inst.data[0]);
            auto field = expr_field::make(loc, std::move(obj), std::move(name));
            auto undef = expr_undefined::make(loc);
            auto exp = expr_assign::make(loc, std::move(field), std::move(undef), expr_assign::op::eq);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_SafeCreateVariableFieldCached:
        {
            auto name = (ctx_->props() & props::hash) ? inst.data[0] : std::format("var_{}", inst.data[0]);
            func_->params->list.push_back(expr_identifier::make(loc, name));
            break;
        }
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        {
            if (stack_.top()->kind() != node::expr_var_create)
            {
                stack_.push(expr_var_access::make(loc, inst.data[0]));
            }
            break;
        }
        case opcode::OP_SafeSetVariableFieldCached0:
        {
            if (func_->params->list.empty())
                func_->params->list.push_back(expr_identifier::make(loc, "¡ERROR!"));
            else
                func_->params->list.push_back(expr_identifier::make(loc, func_->params->list.at(func_->params->list.size() - 1)->as<expr_identifier>().value));
            break;
        }
        case opcode::OP_SafeSetVariableFieldCached:
        {
            if (auto index = func_->params->list.size() - 1 - std::stoul(inst.data[0]); index > func_->params->list.size())
                func_->params->list.push_back(expr_identifier::make(loc, "¡ERROR!"));
            else
                func_->params->list.push_back(expr_identifier::make(loc, func_->params->list.at(index)->as<expr_identifier>().value));
            break;
        }
        case opcode::OP_EvalLocalVariableRefCached0:
        {
            stack_.push(expr_var_access::make(loc, "0"));
            break;
        }
        case opcode::OP_EvalLocalVariableRefCached:
        {
            stack_.push(expr_var_access::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_SetLevelFieldVariableField:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = rvalue->loc();
            auto obj = expr_level::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            auto lvalue = expr_field::make(loc, std::move(obj), std::move(field));
            auto exp = expr_assign::make(loc, std::move(lvalue), std::move(rvalue), expr_assign::op::eq);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_SetVariableField:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = lvalue->loc();

            if (lvalue->is<expr_increment>())
            {
                func_->body->block->list.push_back(stmt_expr::make(loc, std::move(lvalue)));
            }
            else if (lvalue->is<expr_decrement>())
            {
                func_->body->block->list.push_back(stmt_expr::make(loc, std::move(lvalue)));
            }
            else
            {
                auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
                loc = rvalue->loc();
                auto exp = expr_assign::make(loc, std::move(lvalue), std::move(rvalue), expr_assign::op::eq);
                func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            }
            break;
        }
        case opcode::OP_SetAnimFieldVariableField:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = rvalue->loc();
            auto obj = expr_anim::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            auto lvalue = expr_field::make(loc, std::move(obj), std::move(field));
            auto exp = expr_assign::make(loc, std::move(lvalue), std::move(rvalue), expr_assign::op::eq);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_SetSelfFieldVariableField:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = rvalue->loc();
            auto obj = expr_self::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            auto lvalue = expr_field::make(loc, std::move(obj), std::move(field));
            auto exp = expr_assign::make(loc, std::move(lvalue), std::move(rvalue), expr_assign::op::eq);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_SetLocalVariableFieldCached0:
        {
            auto lvalue = expr_var_access::make(loc, "0");
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = rvalue->loc();
            auto exp = expr_assign::make(loc, std::move(lvalue), std::move(rvalue), expr_assign::op::eq);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_SetNewLocalVariableFieldCached0:
        {
            auto lvalue = expr_var_create::make(loc, inst.data[0]);
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = rvalue->loc();

            if (func_->body->block->list.size() > 0)
            {
                std::vector<std::string> vars;

                while (func_->body->block->list.back()->is<stmt_create>())
                {
                    auto& entry = func_->body->block->list.back();
                    if (loc.begin.line < entry->loc().begin.line)
                    {
                        vars.push_back(entry->as<stmt_create>().index);
                        func_->body->block->list.pop_back();
                        continue;
                    }
                    break;
                }

                std::reverse(vars.begin(), vars.end());
                lvalue->vars = vars;
            }

            auto exp = expr_assign::make(loc, std::move(lvalue), std::move(rvalue), expr_assign::op::eq);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_SetLocalVariableFieldCached:
        {
            auto lvalue = expr_var_access::make(loc, inst.data[0]);
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = rvalue->loc();
            auto exp = expr_assign::make(loc, std::move(lvalue), std::move(rvalue), expr_assign::op::eq);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_ClearLocalVariableFieldCached:
        {
            func_->body->block->list.push_back(stmt_clear::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_ClearLocalVariableFieldCached0:
        {
            func_->body->block->list.push_back(stmt_clear::make(loc, "0"));
            break;
        }
        case opcode::OP_EvalLocalVariableObjectCached:
        {
            stack_.push(expr_var_access::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_BoolNot:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_not::make(lvalue->loc(), std::move(lvalue)));
            break;
        }
        case opcode::OP_BoolComplement:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_complement::make(lvalue->loc(), std::move(lvalue)));
            break;
        }
        case opcode::OP_switch:
        {
            auto test = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_jmp_switch::make(test->loc(), std::move(test), inst.data[0]));
            break;
        }
        case opcode::OP_endswitch:
        {
            func_->body->block->list.push_back(stmt_jmp_endswitch::make(loc, inst.data));
            break;
        }
        case opcode::OP_jump:
        {
            func_->body->block->list.push_back(stmt_jmp::make(loc, inst.data[0]));
            if (stack_.size() != 0) tern_labels_.push_back(inst.data[0]);
            break;
        }
        case opcode::OP_jumpback:
        {
            func_->body->block->list.push_back(stmt_jmp_back::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_JumpOnTrue:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = lvalue->loc();
            auto test = expr_not::make(loc, std::move(lvalue));
            func_->body->block->list.push_back(stmt_jmp_cond::make(loc, std::move(test), inst.data[0]));
            break;
        }
        case opcode::OP_JumpOnFalse:
        {
            auto test = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_jmp_cond::make(test->loc(), std::move(test), inst.data[0]));
            break;
        }
        case opcode::OP_JumpOnTrueExpr:
        {
            auto test = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(stmt_jmp_true::make(test->loc(), std::move(test), inst.data[0]));
            expr_labels_.push_back(inst.data[0]);
            break;
        }
        case opcode::OP_JumpOnFalseExpr:
        {
            auto test = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(stmt_jmp_false::make(test->loc(), std::move(test), inst.data[0]));
            expr_labels_.push_back(inst.data[0]);
            break;
        }
        case opcode::OP_FormalParams:
        {
            auto count = std::stoi(inst.data[0]);

            for (auto i = 1; i <= count; i++)
            {
                auto name = (ctx_->props() & props::hash) ? inst.data[i] : std::format("var_{}", inst.data[i]);
                func_->params->list.push_back(expr_identifier::make(loc, name));
            }
            break;
        }
        case opcode::OP_IsDefined:
        {
            auto value = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_isdefined::make(value->loc(), std::move(value)));
            break;
        }
        case opcode::OP_IsTrue:
        {
            auto value = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_istrue::make(value->loc(), std::move(value)));
            break;
        }
        case opcode::OP_BoolNotAfterAnd:
        {
            auto value = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_not::make(value->loc(), std::move(value)));
            break;
        }
        case opcode::OP_GetStatHash:
        {
            stack_.push(expr_string::make(loc, std::format("stat_{}", inst.data[0])));
            break;
        }
        case opcode::OP_GetUnkxHash:
        {
            stack_.push(expr_string::make(loc, std::format("hunk_{}", inst.data[0])));
            break;
        }
        case opcode::OP_GetEnumHash:
        {
            stack_.push(expr_string::make(loc, std::format("enum_{}", inst.data[0])));
            break;
        }
        case opcode::OP_GetDvarHash:
        {
            stack_.push(expr_string::make(loc, std::format("dvar_{}", inst.data[0])));
            break;
        }
        case opcode::OP_waittillmatch2:
        case opcode::OP_checkclearparams:
        case opcode::OP_CastFieldObject:
        case opcode::OP_CastBool:
            break;
        default:
            throw decomp_error(std::format("unhandled opcode {}", ctx_->opcode_name(inst.opcode)));
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
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto jump = std::move(stack_.top()); stack_.pop();
            auto loc = jump->loc();

            if (jump->kind() == node::stmt_jmp_true)
            {
                auto lvalue = std::move(reinterpret_cast<stmt_jmp_true*>(jump.get())->test);
                stack_.push(expr_binary::make(loc, std::move(lvalue), std::move(rvalue), expr_binary::op::bool_or));
            }
            else if (jump->kind() == node::stmt_jmp_false)
            {
                auto lvalue = std::move(reinterpret_cast<stmt_jmp_false*>(jump.get())->test);
                stack_.push(expr_binary::make(loc, std::move(lvalue), std::move(rvalue), expr_binary::op::bool_and));
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
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();

            func_->body->block->list.pop_back();
            auto stm = std::move(func_->body->block->list.back());
            func_->body->block->list.pop_back();

            if (stm->is<stmt_jmp_cond>())
            {
                auto loc = stm->as<stmt_jmp_cond>().loc();
                stack_.push(expr_ternary::make(loc, std::move(stm->as<stmt_jmp_cond>().test), std::move(lvalue), std::move(rvalue)));
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
        if (stm.list.at(i)->is<stmt_jmp_back>())
        {
            auto break_loc = last_location_index(stm, i) ? locs_.end : stm.list.at(i + 1)->label();
            auto start = find_location_index(stm, stm.list.at(i)->as<stmt_jmp_back>().value);

            if (i > 0 && stm.list.at(i - 1)->is<stmt_jmp_cond>())
            {
                if (i - 1 == static_cast<i32>(start)) // condition belongs to empty loop
                {
                    decompile_while(stm, start, i);
                    i = static_cast<i32>(stm.list.size());
                    continue;
                }
                else if (static_cast<usize>(i) < find_location_index(stm, stm.list.at(i - 1)->as<stmt_jmp_cond>().value))
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
            else if (!stm.list.at(start)->is<stmt_jmp_cond>()) // no condition
            {
                decompile_inf(stm, start, i);
            }
            else if (stm.list.at(start)->as<stmt_jmp_cond>().value != break_loc) // condition belong to other stmt
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
        if (stm.list[i]->is<stmt_jmp_switch>())
        {
            auto end = find_location_index(stm, stm.list[i]->as<stmt_jmp_switch>().value);
            decompile_switch(stm, i, end);
        }
    }
}

auto decompiler::decompile_ifelses(stmt_list& stm) -> void
{
    for (auto i = 0u; i < stm.list.size(); i++)
    {
        auto const& entry = stm.list.at(i);

        if (entry->is<stmt_jmp_cond>())
        {
            auto j = find_location_index(stm, entry->as<stmt_jmp_cond>().value) - 1;
            auto last_loc = locs_.end;

            if (stm.list.at(j)->is<stmt_jmp>())
            {
                // if scope is a loop check break, continue
                if (stm.list.at(j)->as<stmt_jmp>().value == locs_.cnt)
                {
                    // check for if/else or if/continue
                    if (j - i > 1 && stm.list.at(j - 1)->is<stmt_return>())
                    {
                        // scope ends with a return, so jump belows to if/else
                        decompile_ifelse(stm, i, j);
                    }
                    else if (j - i > 1 && stm.list.at(j - 1)->is<stmt_jmp>())
                    {
                        if (stm.list.at(j - 1)->as<stmt_jmp>().value == locs_.brk)
                        {
                            // scope ends with a break, so jump belows to if/else
                            decompile_ifelse(stm, i, j);
                        }
                        else if (stm.list.at(j - 1)->as<stmt_jmp>().value == locs_.cnt)
                        {
                            // if { break/return } else { continue } at loop scope end
                            if (j - i > 2 && (stm.list.at(j - 2)->is<stmt_jmp>() || stm.list.at(j - 2)->is<stmt_return>()))
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
                else if (stm.list.at(j)->as<stmt_jmp>().value == locs_.brk)
                {
                    decompile_if(stm, i, j);
                }
                else if (stm.list.at(j)->as<stmt_jmp>().value == entry->as<stmt_jmp_cond>().value)
                {
                    if (find_location_reference(stm, i + 1, j, entry->as<stmt_jmp_cond>().value))
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
            else if (stm.list.at(j)->is<stmt_return>() && stm.list.at(j)->as<stmt_return>().value->is<expr_empty>())
            {
                if(entry->as<stmt_jmp_cond>().value != locs_.end)
                {
                    auto ref = stm.list.at(j + 1)->label();

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
                else if (!stm.list.back()->is<stmt_return>())
                {
                    decompile_if(stm, i, j); // scope end is not a last return
                }
                else if (locs_.last && !stm.list.back()->is<stmt_return>())
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
        if (stm.list[i]->is<stmt_jmp>())
        {
            auto const loc = stm.list[i]->loc();
            auto const jmp = stm.list[i]->as<stmt_jmp>().value;

            if (jmp == locs_.brk)
            {
                stm.list.erase(stm.list.begin() + i);
                stm.list.insert(stm.list.begin() + i, stmt_break::make(loc));
            }
            else if (jmp == locs_.cnt)
            {
                stm.list.erase(stm.list.begin() + i);
                stm.list.insert(stm.list.begin() + i, stmt_continue::make(loc));
            }
            else
            {
                std::cout << std::format("[WRN]: unresolved jump to '{}', maybe incomplete for loop at {}\n", jmp, func_->name->value);
            }
        }
    }
}

auto decompiler::decompile_tuples(stmt_list& stm) -> void
{
    for (auto i = 1u; i < stm.list.size(); i++)
    {
        if (stm.list.at(i)->is<stmt_clear>())
        {
            auto j = i - 1;
            auto found = false, done = false;

            while (j >= 0 && stm.list.at(j)->is<stmt_expr>())
            {
                auto const& exp = stm.list.at(j)->as<stmt_expr>().value;

                if (!exp->is<expr_assign>())
                    break;

                if (!done)
                {
                    if (!exp->as<expr_assign>().rvalue->is<expr_array>())
                        break;

                    if (!exp->as<expr_assign>().rvalue->as<expr_array>().key->is<expr_integer>())
                        break;

                    if (exp->as<expr_assign>().rvalue->as<expr_array>().key->as<expr_integer>().value == "0")
                        done = true;

                    j--;
                }
                else
                {
                    if (exp->as<expr_assign>().lvalue->is<expr_var_create>() || exp->as<expr_assign>().lvalue->is<expr_var_access>())
                        found = true;

                    break;
                }
            }

            if (found)
            {
                auto& entry = stm.list.at(j);  // temp = expr;
                auto tuple = expr_tuple::make(entry->loc());
                tuple->temp = std::move(entry->as<stmt_expr>().value->as<expr_assign>().lvalue);
                j++;

                while (j < i)
                {
                    tuple->list.push_back(std::move(stm.list.at(j)->as<stmt_expr>().value->as<expr_assign>().lvalue));
                    stm.list.erase(stm.list.begin() + j);
                    i--;
                }

                stm.list.erase(stm.list.begin() + j); // clear temp array
                i--;

                entry->as<stmt_expr>().value->as<expr_assign>().lvalue = std::move(tuple);
            }
        }
    }
}

auto decompiler::decompile_if(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
    locs_.end = stm.list[begin]->as<stmt_jmp_cond>().value;

    auto loc = stm.list[begin]->loc();
    auto test = std::move(stm.list[begin]->as<stmt_jmp_cond>().test);

    stm.list.erase(stm.list.begin() + begin);

    auto body = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt_if::make(loc, std::move(test), stmt_comp::make(loc, std::move(body))));
}

auto decompiler::decompile_ifelse(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
    locs_.end = stm.list[end]->label();

    auto loc = stm.list[begin]->loc();
    auto test = std::move(stm.list[begin]->as<stmt_jmp_cond>().test);

    stm.list.erase(stm.list.begin() + begin);
    end--;

    auto body_if = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body_if->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body_if);
    locs_ = save;

    auto end_loc = stm.list[begin]->as<stmt_jmp>().value;

    stm.list.erase(stm.list.begin() + begin);

    end = find_location_index(stm, end_loc);

    save = locs_;
    locs_.last = false;
    locs_.end = end_loc;

    auto body_else = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body_else->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body_else);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt_ifelse::make(loc, std::move(test), stmt_comp::make(loc, std::move(body_if)), stmt_comp::make(loc, std::move(body_else))));
}

auto decompiler::decompile_ifelse_end(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = true;
    locs_.end = stm.list[find_location_index(stm, stm.list[begin]->as<stmt_jmp_cond>().value) - 1]->label();

    auto loc = stm.list[begin]->loc();
    auto test = std::move(stm.list[begin]->as<stmt_jmp_cond>().test);

    stm.list.erase(stm.list.begin() + begin);
    end--;

    auto body_if = stmt_list::make(loc);

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
        stm.list.insert(stm.list.begin() + begin, stmt_if::make(loc, std::move(test), stmt_comp::make(loc, std::move(body_if))));
    }
    else
    {
        end = stm.list.size() - 1;
        save = locs_;
        locs_.last = true;
        locs_.end = stm.list[end]->label();

        auto body_else = stmt_list::make(loc);

        for (auto i = begin; i < end; i++)
        {
            body_else->list.push_back(std::move(stm.list[begin]));
            stm.list.erase(stm.list.begin() + begin);
        }

        stm.list.erase(stm.list.begin() + begin);

        decompile_statements(*body_else);
        locs_ = save;
        stm.list.insert(stm.list.begin() + begin, stmt_ifelse::make(loc, std::move(test), stmt_comp::make(loc, std::move(body_if)), stmt_comp::make(loc, std::move(body_else))));
    }
}

auto decompiler::decompile_inf(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
    locs_.brk = last_location_index(stm, end) ? locs_.end : stm.list[end + 1]->label();
    locs_.end = stm.list[end]->label();
    locs_.cnt = stm.list[end]->label();

    auto loc = stm.list[begin]->loc();

    stm.list.erase(stm.list.begin() + end);

    auto body = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt_for::make(loc, stmt_empty::make(loc), expr_empty::make(loc), stmt_empty::make(loc), stmt_comp::make(loc, std::move(body))));
}

auto decompiler::decompile_loop(stmt_list& stm, usize start, usize end) -> void
{
    auto const& last = stm.list.at(end - 1);

    if (last->is<stmt_expr>())
    {
        if (last->as<stmt_expr>().value->is<expr_assign>())
        {
            auto& val = last->as<stmt_expr>().value->as<expr_assign>().rvalue;

            if (val->is<expr_call>() && val->as<expr_call>().value->is<expr_function>())
            {
                if (utils::string::to_lower(val->as<expr_call>().value->as<expr_function>().name->value) == "getnextarraykey")
                {
                    auto ref = stm.list.at(start)->label();

                    if (!find_location_reference(stm, 0, start, ref))
                    {
                        decompile_foreach(stm, start, end);
                        return;
                    }
                }
            }
        }

        if (start > 0 && last->as<stmt_expr>().value->is_assign()) // while at func start
        {
            auto index = 1;
            while (stm.list.at(start - index)->is<stmt_create>())
            {
                if (start - index > 0)
                    index++;
                else
                    break;
            }

            if (stm.list.at(start - index)->is<stmt_expr>() && stm.list.at(start - index)->as<stmt_expr>().value->is_assign())
            {
                auto ref = stm.list.at(end)->label();
                auto ref2 = stm.list.at(start - index + 1)->label();

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
    locs_.end = stm.list[end]->label();
    locs_.cnt = stm.list[end]->label();
    locs_.brk = stm.list[begin]->as<stmt_jmp_cond>().value;

    auto loc = stm.list[begin]->loc();
    auto test = std::move(stm.list[begin]->as<stmt_jmp_cond>().test);

    end--;
    stm.list.erase(stm.list.begin() + begin);
    stm.list.erase(stm.list.begin() + end);

    auto body = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt_while::make(loc, std::move(test), stmt_comp::make(loc, std::move(body))));
}

auto decompiler::decompile_dowhile(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
    locs_.end = stm.list[begin]->label();
    locs_.cnt = stm.list[begin]->label();
    locs_.brk = stm.list[begin]->as<stmt_jmp_cond>().value;

    auto test = std::move(stm.list[begin]->as<stmt_jmp_cond>().test);
    begin = find_location_index(stm, stm.list[end]->as<stmt_jmp_back>().value);
    auto loc = stm.list[begin]->loc();

    end--;
    stm.list.erase(stm.list.begin() + end);
    stm.list.erase(stm.list.begin() + end);

    auto body = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt_dowhile::make(loc, std::move(test), stmt_comp::make(loc, std::move(body))));
}

auto decompiler::decompile_for(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
    locs_.end = stm.list[end - 1]->label();
    locs_.cnt = stm.list[end - 1]->label();
    locs_.brk = stm.list[begin]->as<stmt_jmp_cond>().value;

    for (begin -= 1; stm.list[begin]->is<stmt_create>(); begin--);

    auto loc = stm.list[begin]->loc();
    auto init = stmt_list::make(loc);

    while (!stm.list[begin]->is<stmt_jmp_cond>())
    {
        init->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    auto test = std::move(stm.list[begin]->as<stmt_jmp_cond>().test);
    stm.list.erase(stm.list.begin() + begin);

    end -= 2 + init->list.size();

    auto iter = stmt_list::make(loc);
    iter->list.push_back(std::move(stm.list[end]));
    stm.list.erase(stm.list.begin() + end);
    stm.list.erase(stm.list.begin() + end);

    auto body = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt_for::make(loc, std::move(init), std::move(test), std::move(iter), stmt_comp::make(loc, std::move(body))));
}

auto decompiler::decompile_foreach(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.last = false;
    locs_.end = stm.list[end - 1]->label();
    locs_.cnt = stm.list[end - 1]->label();
    locs_.brk = stm.list[begin]->as<stmt_jmp_cond>().value;

    for (begin -= 1; stm.list[begin]->is<stmt_create>(); begin--);

    auto use_index = false;

    if ((ctx_->props() & props::foreach) && stm.list[begin]->is<stmt_expr>() && stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().rvalue->is<expr_undefined>())
    {
        use_index = true;
        begin--;
    }

    begin--;

    auto loc = stm.list[begin]->loc();

    auto container = std::move(stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().rvalue);
    auto array = std::move(stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().lvalue);
    stm.list.erase(stm.list.begin() + begin);

    auto key = std::move(stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().lvalue);
    stm.list.erase(stm.list.begin() + begin);

    auto index = (use_index) ? std::move(stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().lvalue) : expr_empty::make(location{});

    if (use_index)
    {
        stm.list.erase(stm.list.begin() + begin);
    }

    auto init = stmt_list::make(loc);

    while (!stm.list[begin]->is<stmt_jmp_cond>())
    {
        init->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    stm.list.erase(stm.list.begin() + begin);

    auto value = std::move(stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().lvalue);
    stm.list.erase(stm.list.begin() + begin);

    if (use_index)
    {
        stm.list.erase(stm.list.begin() + begin);
    }

    end -= (use_index ? 7 : 5) + init->list.size();
    stm.list.erase(stm.list.begin() + end);
    stm.list.erase(stm.list.begin() + end);

    auto use_key = true;

    if (stm.list.size() > end && stm.list[end]->is<stmt_clear>())
    {
        stm.list.erase(stm.list.begin() + end);
    }

    if (stm.list.size() > end && stm.list[end]->is<stmt_clear>())
    {
        stm.list.erase(stm.list.begin() + end);
        use_key = false;
    }

    auto body = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    body->list.insert(body->list.begin(), std::move(init));
    stm.list.insert(stm.list.begin() + begin, stmt_foreach::make(loc, std::move(container), std::move(value), std::move(index), std::move(array), std::move(key), stmt_comp::make(loc, std::move(body)), (ctx_->props() & props::foreach) ? use_index : use_key));
}

auto decompiler::decompile_switch(stmt_list& stm, usize begin, usize end) -> void
{
    auto const& data = stm.list[end]->as<stmt_jmp_endswitch>().data;
    auto count = std::stoul(data[0]);
    auto index = 1u;

    for (auto i = 0u; i < count; i++)
    {
        if (data[index] == "case")
        {
            auto type = static_cast<switch_type>(std::stoul(data[index + 1]));
            auto pos = find_location_index(stm, data[index + 3]);
            auto loc = stm.list[pos]->loc();
            auto exp = (type == switch_type::integer) ? expr::ptr{ expr_integer::make(loc, data[index + 2]) } : expr::ptr{ expr_string::make(loc, data[index + 2]) };
            while (stm.list[pos]->is<stmt_case>()) pos++;
            stm.list.insert(stm.list.begin() + pos, stmt_case::make(loc, std::move(exp), stmt_list::make(loc)));
            index += 4;
        }
        else if (data[index] == "default")
        {
            auto pos = find_location_index(stm, data[index + 1]);
            auto loc = stm.list[pos]->loc();
            while (stm.list[pos]->is<stmt_case>()) pos++;
            stm.list.insert(stm.list.begin() + pos, stmt_default::make(loc, stmt_list::make(loc)));
            index += 2;
        }
        else
        {
            decomp_error("malformed endswitch statement");
        }
    }

    end += count;

    // check if last case is empty and shift location
    auto last = find_location_index(stm, stm.list[begin]->as<stmt_jmp_switch>().value);

    auto save = locs_;
    locs_.last = false;
    locs_.brk = last_location_index(stm, end) ? locs_.end : stm.list[end + 1]->label();
    locs_.end = (last == end) ? stm.list[begin]->as<stmt_jmp_switch>().value : std::format("loc_{:X}", stm.list[end]->as<stmt_jmp_endswitch>().loc().begin.line + 1);

    auto loc = stm.list[begin]->loc();
    auto test = std::move(stm.list[begin]->as<stmt_jmp_switch>().test);

    end--;
    stm.list.erase(stm.list.begin() + begin);
    stm.list.erase(stm.list.begin() + end);

    auto body = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;

    auto temp = stmt::ptr{ stmt_empty::make(location{}) };

    for (auto i = 0u; i < body->list.size(); )
    {
        if (body->list[i]->is<stmt_case>() || body->list[i]->is<stmt_default>())
        {
            if (!temp->is<stmt_empty>())
            {
                body->list.insert(body->list.begin() + i, std::move(temp));
                i++;
            }

            temp = std::move(body->list[i]);
            body->list.erase(body->list.begin() + i);
        }
        else
        {
            if (temp->is<stmt_case>())
            {
                temp->as<stmt_case>().body->list.push_back(std::move(body->list[i]));
                body->list.erase(body->list.begin() + i);
            }
            else if (temp->is<stmt_default>())
            {
                temp->as<stmt_default>().body->list.push_back(std::move(body->list[i]));
                body->list.erase(body->list.begin() + i);
            }
            else
            {
                decomp_error("missing case or default before stmt inside a switch");
            }
        }
    }

    if (!temp->is<stmt_empty>())
    {
        body->list.push_back(std::move(temp));
    }

    stm.list.insert(stm.list.begin() + begin, stmt_switch::make(loc, std::move(test), stmt_comp::make(loc, std::move(body))));
}

auto decompiler::find_location_reference(stmt_list const& stm, usize begin, usize end, std::string const& loc) -> bool
{
    for (auto i = begin; i < end; i++)
    {
        auto const& entry = stm.list.at(i);

        if (entry->is<stmt_jmp_cond>() && entry->as<stmt_jmp_cond>().value == loc)
        {
            return true;
        }
        else if (entry->is<stmt_jmp>() && entry->as<stmt_jmp>().value == loc)
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
        if (entry->label() == loc)
            return index;

        index++;
    }

    throw decomp_error(std::format("location '{}' not found", loc));
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
        if (scp_body->find(0, entry->value) == -1)
        {
            scp_body->vars.push_back({ entry->value, static_cast<u8>(scp_body->create_count), true });
            scp_body->create_count++;
        }
    }

    process_stmt_comp(*func.body, *scp_body);
}

auto decompiler::process_stmt(stmt& stm, scope& scp) -> void
{
    switch (stm.kind())
    {
        case node::stmt_list:
            process_stmt_list(stm.as<stmt_list>(), scp);
            break;
        case node::stmt_comp:
            process_stmt_comp(stm.as<stmt_comp>(), scp);
            break;
        case node::stmt_dev:
            process_stmt_dev(stm.as<stmt_dev>(), scp);
            break;
        case node::stmt_expr:
            process_stmt_expr(stm.as<stmt_expr>(), scp);
            break;
        case node::stmt_endon:
            process_stmt_endon(stm.as<stmt_endon>(), scp);
            break;
        case node::stmt_notify:
            process_stmt_notify(stm.as<stmt_notify>(), scp);
            break;
        case node::stmt_wait:
            process_stmt_wait(stm.as<stmt_wait>(), scp);
            break;
        case node::stmt_waittill:
            process_stmt_waittill(stm.as<stmt_waittill>(), scp);
            break;
        case node::stmt_waittillmatch:
            process_stmt_waittillmatch(stm.as<stmt_waittillmatch>(), scp);
            break;
        case node::stmt_if:
            process_stmt_if(stm.as<stmt_if>(), scp);
            break;
        case node::stmt_ifelse:
            process_stmt_ifelse(stm.as<stmt_ifelse>(), scp);
            break;
        case node::stmt_while:
            process_stmt_while(stm.as<stmt_while>(), scp);
            break;
        case node::stmt_dowhile:
            process_stmt_dowhile(stm.as<stmt_dowhile>(), scp);
            break;
        case node::stmt_for:
            process_stmt_for(stm.as<stmt_for>(), scp);
            break;
        case node::stmt_foreach:
            process_stmt_foreach(stm.as<stmt_foreach>(), scp);
            break;
        case node::stmt_switch:
            process_stmt_switch(stm.as<stmt_switch>(), scp);
            break;
        case node::stmt_break:
            process_stmt_break(stm.as<stmt_break>(), scp);
            break;
        case node::stmt_continue:
            process_stmt_continue(stm.as<stmt_continue>(), scp);
            break;
        case node::stmt_return:
            process_stmt_return(stm.as<stmt_return>(), scp);
            break;
        case node::stmt_create:
            process_stmt_create(stm.as<stmt_create>(), scp);
            break;
        case node::stmt_remove:
            process_stmt_remove(stm.as<stmt_remove>(), scp);
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_list(stmt_list& stm, scope& scp) -> void
{
    for (auto& entry : stm.list)
    {
        process_stmt(*entry, scp);
    }

    for (auto i = 0u; i < stm.list.size(); )
    {
        if (stm.list[i]->is<stmt_create>() || stm.list[i]->is<stmt_remove>())
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
    switch (stm.value->kind())
    {
        case node::expr_increment:
            process_expr_increment(stm.value->as<expr_increment>(), scp);
            break;
        case node::expr_decrement:
            process_expr_decrement(stm.value->as<expr_decrement>(), scp);
            break;
        case node::expr_assign:
            process_expr_assign(*reinterpret_cast<expr_assign::ptr*>(&stm.value), scp);
            break;
        case node::expr_call:
            process_expr_call(stm.value->as<expr_call>(), scp);
            break;
        case node::expr_method:
            process_expr_method(stm.value->as<expr_method>(), scp);
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

    process_stmt(*stm.body, *scp_then);

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
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

    process_stmt(*stm.stmt_if, *scp_then);

    if (scp_then->abort <= scope::abort_return)
    {
        abort = scp_then->abort;

        if (abort == scope::abort_none)
            childs.push_back(scp_then.get());
    }

    scp.transfer_dec(scp_else);

    process_stmt(*stm.stmt_else, *scp_else);

    if (scp_else->abort <= abort)
    {
        abort = scp_else->abort;

        if (abort == scope::abort_none)
            childs.push_back(scp_else.get());
    }

    if (scp.abort == scope::abort_none)
        scp.abort = abort;

    scp.append(childs);

    if (stm.stmt_if->as<stmt_comp>().block->list.size() == 1 && !stm.stmt_if->as<stmt_comp>().block->list[0]->is_special_stmt())
    {
        stm.stmt_if = std::move(stm.stmt_if->as<stmt_comp>().block->list.back());
    }

    if (stm.stmt_else->as<stmt_comp>().block->list.size() == 1 && !stm.stmt_else->as<stmt_comp>().block->list[0]->is_special_stmt_noif())
    {
        stm.stmt_else = std::move(stm.stmt_else->as<stmt_comp>().block->list.back());
    }
}

auto decompiler::process_stmt_while(stmt_while& stm, scope& scp) -> void
{
    auto scp_body = make_scope();

    process_expr(stm.test, scp);

    scp.transfer_dec(scp_body);

    process_stmt(*stm.body, *scp_body);

    if (stm.test->is<expr_empty>())
        scp.append_dec(scp_body);

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
    }
}

auto decompiler::process_stmt_dowhile(stmt_dowhile& stm, scope& scp) -> void
{
    auto scp_body = make_scope();

    process_expr(stm.test, scp);

    scp.transfer_dec(scp_body);

    process_stmt(*stm.body, *scp_body);

    if (stm.test->is<expr_empty>())
        scp.append_dec(scp_body);

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
    }
}

auto decompiler::process_stmt_for(stmt_for& stm, scope& scp) -> void
{
    auto scp_body = make_scope();

    process_stmt(*stm.init, scp);

    if (stm.init->is<stmt_list>() && stm.init->as<stmt_list>().list[0]->is<stmt_expr>())
    {
        stm.init = stmt_expr::make(stm.init->loc(), std::move(stm.init->as<stmt_list>().list[0]->as<stmt_expr>().value));
    }

    scp.transfer_dec(scp_body);

    process_expr(stm.test, scp);

    process_stmt(*stm.body, *scp_body);

    process_stmt(*stm.iter, scp);

    if (stm.iter->is<stmt_list>() && stm.iter->as<stmt_list>().list[0]->is<stmt_expr>())
    {
        stm.iter = stmt_expr::make(stm.iter->loc(), std::move(stm.iter->as<stmt_list>().list[0]->as<stmt_expr>().value));
    }

    if (stm.test->is<expr_empty>())
        scp.append_dec(scp_body);

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
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

    process_stmt(*stm.body->as<stmt_comp>().block->list[0], scp);

    stm.body->as<stmt_comp>().block->list.erase(stm.body->as<stmt_comp>().block->list.begin());

    scp.transfer_dec(scp_body);

    process_expr(stm.value, *scp_body);
    process_stmt(*stm.body, *scp_body);

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
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
        if (entry->is<stmt_case>())
        {
            auto scp_case = make_scope();

            scp.transfer_dec(scp_case);

            process_stmt_list(*entry->as<stmt_case>().body, *scp_case);

            if (scp_case->abort == scope::abort_break)
            {
                childs.push_back(scp_case.get());
                scopes.push_back(std::move(scp_case));
            }
        }
        else if (entry->is<stmt_default>())
        {
            has_default = true;
            auto scp_case = make_scope();

            scp.transfer_dec(scp_case);

            process_stmt_list(*entry->as<stmt_default>().body, *scp_case);

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

    if (!stm.value->is<expr_empty>())
    {
        process_expr(stm.value, scp);
    }
}

auto decompiler::process_stmt_create(stmt_create& stm, scope& scp) -> void
{
    auto var = (ctx_->props() & props::hash) ? stm.index : std::format("var_{}", stm.index);
    scp.vars.push_back({ var, static_cast<u8>(scp.create_count), true });
    scp.create_count++;
}

auto decompiler::process_stmt_remove(stmt_remove& stm, scope& scp) -> void
{
    scp.public_count = static_cast<u32>(scp.vars.size() - std::stoi(stm.index));
}

auto decompiler::process_expr(expr::ptr& exp, scope& scp) -> void
{
    switch (exp->kind())
    {
        case node::expr_ternary:
            process_expr_ternary(exp->as<expr_ternary>(), scp);
            break;
        case node::expr_binary:
            process_expr_binary(exp->as<expr_binary>(), scp);
            break;
        case node::expr_complement:
            process_expr_complement(exp->as<expr_complement>(), scp);
            break;
        case node::expr_not:
            process_expr_not(exp->as<expr_not>(), scp);
            break;
        case node::expr_call:
            process_expr_call(exp->as<expr_call>(), scp);
            break;
        case node::expr_method:
            process_expr_method(exp->as<expr_method>(), scp);
            break;
        case node::expr_isdefined:
            process_expr(exp->as<expr_isdefined>().value, scp);
            break;
        case node::expr_istrue:
            process_expr(exp->as<expr_istrue>().value, scp);
            break;
        case node::expr_add_array:
            process_expr_add_array(exp->as<expr_add_array>(), scp);
            break;
        case node::expr_size:
            process_expr_size(exp->as<expr_size>(), scp);
            break;
        case node::expr_tuple:
            process_expr_tuple(exp->as<expr_tuple>(), scp);
            break;
        case node::expr_array:
            process_expr_array(exp->as<expr_array>(), scp);
            break;
        case node::expr_field:
            process_expr_field(exp->as<expr_field>(), scp);
            break;
        case node::expr_vector:
            process_expr_vector(exp->as<expr_vector>(), scp);
            break;
        case node::expr_var_create:
            process_expr_var_create(exp, scp);
            break;
        case node::expr_var_access:
            process_expr_var_access(exp, scp);
            break;
        default:
            break;
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

auto decompiler::process_expr_assign(expr_assign::ptr& exp, scope& scp) -> void
{
    process_expr(exp->rvalue, scp);
    process_expr(exp->lvalue, scp);

    if (exp->oper != expr_assign::op::eq)
        return;

    if (exp->rvalue->kind() != node::expr_binary)
        return;

    auto& rval = exp->rvalue->as<expr_binary>();

    if (exp->lvalue != rval.lvalue)
        return;

    switch (rval.oper)
    {
        case expr_binary::op::add:
            exp->oper = expr_assign::op::add;
            break;
        case expr_binary::op::sub:
            exp->oper = expr_assign::op::sub;
            break;
        case expr_binary::op::mul:
            exp->oper = expr_assign::op::mul;
            break;
        case expr_binary::op::div:
            exp->oper = expr_assign::op::div;
            break;
        case expr_binary::op::mod:
            exp->oper = expr_assign::op::mod;
            break;
        case expr_binary::op::shl:
            exp->oper = expr_assign::op::shl;
            break;
        case expr_binary::op::shr:
            exp->oper = expr_assign::op::shr;
            break;
        case expr_binary::op::bwor:
            exp->oper = expr_assign::op::bwor;
            break;
        case expr_binary::op::bwand:
            exp->oper = expr_assign::op::bwand;
            break;
        case expr_binary::op::bwexor:
            exp->oper = expr_assign::op::bwexor;
            break;
        default:
            return;
    }

    exp->rvalue = std::move(rval.rvalue);
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

    auto prec = exp.lvalue->precedence();

    if (prec && prec < exp.precedence())
    {
        exp.lvalue = expr_paren::make(exp.loc(), std::move(exp.lvalue));
    }

    prec = exp.rvalue->precedence();

    if ((prec && prec < exp.precedence()) || (prec == exp.precedence() && exp.kind() == exp.rvalue->kind()))
    {
        exp.rvalue = expr_paren::make(exp.loc(), std::move(exp.rvalue));
    }
}

auto decompiler::process_expr_complement(expr_complement& exp, scope& scp) -> void
{
    process_expr(exp.rvalue, scp);

    if (exp.rvalue->is<expr_binary>())
    {
        exp.rvalue = expr_paren::make(exp.loc(), std::move(exp.rvalue));
    }
}

auto decompiler::process_expr_not(expr_not& exp, scope& scp) -> void
{
    process_expr(exp.rvalue, scp);

    if (exp.rvalue->is<expr_binary>())
    {
        exp.rvalue = expr_paren::make(exp.loc(), std::move(exp.rvalue));
    }
}

auto decompiler::process_expr_call(expr_call& exp, scope& scp) -> void
{
    switch (exp.value->kind())
    {
        case node::expr_pointer:
            process_expr_call_pointer(exp.value->as<expr_pointer>(), scp);
            break;
        case node::expr_function:
            process_expr_call_function(exp.value->as<expr_function>(), scp);
            break;
        default:
            break;
    }
}

auto decompiler::process_expr_method(expr_method& exp, scope& scp) -> void
{
    switch (exp.value->kind())
    {
        case node::expr_pointer:
            process_expr_method_pointer(exp.value->as<expr_pointer>(), exp.obj, scp);
            break;
        case node::expr_function:
            process_expr_method_function(exp.value->as<expr_function>(), exp.obj, scp);
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

auto decompiler::process_expr_method_pointer(expr_pointer& exp, expr::ptr& obj, scope& scp) -> void
{
    process_expr_arguments(*exp.args, scp);
    process_expr(obj, scp);
    process_expr(exp.func, scp);
}

auto decompiler::process_expr_method_function(expr_function& exp, expr::ptr& obj, scope& scp) -> void
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

auto decompiler::process_expr_var_create(expr::ptr& exp, scope& scp) -> void
{
    for (auto const& entry : exp->as<expr_var_create>().vars)
    {
        auto var = (ctx_->props() & props::hash) ? entry : std::format("var_{}", entry);
        scp.vars.push_back({ var, static_cast<u8>(scp.create_count), true });
        scp.create_count++;
    }

    auto var = (ctx_->props() & props::hash) ? exp->as<expr_var_create>().index : std::format("var_{}", exp->as<expr_var_create>().index);
    scp.vars.push_back({ var, static_cast<u8>(scp.create_count), true });
    scp.create_count++;

    exp = expr_identifier::make(exp->loc(), var);
}

auto decompiler::process_expr_var_access(expr::ptr& exp, scope& scp) -> void
{
    auto const index = std::stoul(exp->as<expr_var_access>().index);

    if (scp.vars.size() <= index)
    {
        std::cout << std::format("[WRN]: bad variable access {} at {} \n", index, func_->name->value);
    }
    else
    {
        exp = expr_identifier::make(exp->loc(), scp.vars[scp.vars.size() - 1 - index].name);
    }
}

} // namespace xsk::gsc
