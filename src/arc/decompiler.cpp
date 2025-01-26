// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/arc/decompiler.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc
{

decompiler::decompiler(context const* ctx) : ctx_{ ctx }
{
}

auto decompiler::decompile(assembly const& data) -> program::ptr
{
    program_ = program::make();
    namespace_ = {};

    for (auto it = data.includes.rbegin(); it != data.includes.rend(); it++)
    {
        program_->includes.push_back(include::make(location{}, expr_path::make(location{}, *it)));
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
    params_.clear();
    vars_.clear();
    labels_ = func.labels;
    in_waittill_ = false;
    retbool_ = true;
    locs_ = {};
    stack_ = {};

    auto loc = location{ nullptr, static_cast<i32>(func.index) };
    auto space = expr_identifier::make(loc, func.space);
    auto name = expr_identifier::make(loc, func.name);
    auto prms = expr_parameters::make(loc);
    auto body = stmt_comp::make(loc, stmt_list::make(loc));
    auto flags = static_cast<export_flags>(func.flags);
    func_ = decl_function::make(loc, std::move(space), std::move(name), std::move(prms), std::move(body), flags);

    for (auto const& inst : func.instructions)
    {
        decompile_instruction(*inst, &inst == &func.instructions.back());
    }

    for (auto i = 0u; i < func.params; i++)
    {
        auto const& param = locals_.at(locals_.size() - 1 - i);

        if (ctx_->props() & props::refvarg)
        {
            auto const& type = params_.at(params_.size() - 1 - i);

            if (type == param_type::reference)
                func_->params->list.push_back(expr_reference::make(loc, expr_path::make(loc), expr_identifier::make(loc, param)));
            else if (type == param_type::vararg)
                func_->params->list.push_back(expr_ellipsis::make(loc));
            else
                func_->params->list.push_back(expr_identifier::make(loc, param));
        }
        else
        {
            func_->params->list.push_back(expr_identifier::make(loc, param));
        }
    }

    if (!stack_.empty())
    {
        throw decomp_error("stack isn't empty at function end");
    }

    auto& list = func_->body->block->list;
    locs_.end = std::format("loc_{:X}", list.back()->loc().begin.line + 1);

    decompile_statements(*func_->body->block);

    if (!list.empty() && list.back()->is<stmt_return>())
    {
        if (list.back()->as<stmt_return>().value->is<expr_empty>())
            list.pop_back();
    }

    process_function(*func_);

    program_->declarations.push_back(std::move(func_));
}

auto decompiler::decompile_instruction(instruction const& inst, bool last) -> void
{
    decompile_expressions(inst);

    auto loc = location{ nullptr, static_cast<i32>(inst.index) };

    switch (inst.opcode)
    {
        case opcode::OP_End:
        {
            retbool_ = !last ? false : retbool_;
            func_->body->block->list.push_back(stmt_return::make(loc, expr_empty::make(loc)));
            break;
        }
        case opcode::OP_Return:
        {
            auto value = node::as<expr>(std::move(stack_.top())); stack_.pop();
            retbool_ = !value->is_boolean() ? false : retbool_;
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
        {
            stack_.push(expr_integer::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_GetNegByte:
        case opcode::OP_GetNegUnsignedShort:
        {
            stack_.push(expr_integer::make(loc, "-" + inst.data[0]));
            break;
        }
        case opcode::OP_GetInteger:
        {
            if (inst.data.size() == 2)
            {
                auto found = false;

                for (auto i = program_->declarations.rbegin(); i != program_->declarations.rend(); i++)
                {
                    if ((*i)->is<decl_usingtree>())
                    {
                        found = (*i)->as<decl_usingtree>().name->value == inst.data[0];
                        break;
                    }
                }

                if (!found)
                {
                    auto dec = decl_usingtree::make(loc, expr_string::make(loc, inst.data[0]));
                    program_->declarations.push_back(std::move(dec));
                }

                stack_.push(expr_animtree::make(loc));
            }
            else
            {
                stack_.push(expr_integer::make(loc, inst.data[0]));
            }
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
        case opcode::OP_SafeDecTop:
        {
            stack_.push(expr_undefined::make(loc));
            break;
        }
        case opcode::OP_EmptyArray:
        {
            stack_.push(expr_empty_array::make(loc));
            break;
        }
        case opcode::OP_GetClasses:
        case opcode::OP_GetClassesObject:
        {
            stack_.push(expr_classes::make(loc));
            break;
        }
        case opcode::OP_GetWorld:
        case opcode::OP_GetWorldObject:
        {
            stack_.push(expr_world::make(loc));
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
            auto found = false;
            auto space = ""s;

            for (auto i = program_->declarations.rbegin(); i != program_->declarations.rend(); i++)
            {
                if ((*i)->is<decl_usingtree>())
                {
                    found = (*i)->as<decl_usingtree>().name->value == inst.data[0];
                    space = (*i)->as<decl_usingtree>().name->value;
                    break;
                }
            }

            if (!found)
            {
                if (space == "")
                {
                    auto dec = decl_usingtree::make(loc, expr_string::make(loc, inst.data[0]));
                    program_->declarations.push_back(std::move(dec));
                    stack_.push(expr_animation::make(loc, "", inst.data[1]));
                }
                else
                {
                    stack_.push(expr_animation::make(loc, inst.data[0], inst.data[1]));
                }
            }
            else if (space == inst.data[0])
            {
                stack_.push(expr_animation::make(loc, "", inst.data[1]));
            }
            else
            {
                stack_.push(expr_animation::make(loc, inst.data[0], inst.data[1]));
            }

            break;
        }
        case opcode::OP_GetFunction:
        {
            auto path = expr_path::make(loc, inst.data[0]);
            auto name = expr_identifier::make(loc, inst.data[1]);
            stack_.push(expr_reference::make(loc, std::move(path), std::move(name)));
            break;
        }
        case opcode::OP_SafeCreateLocalVariables:
        {
            if (ctx_->props() & props::refvarg)
            {
                for (auto i = 0u; i < inst.data.size(); i += 2)
                {
                    locals_.insert(locals_.begin(), inst.data[i]);
                    params_.insert(params_.begin(), static_cast<param_type>(std::stoul(inst.data[i + 1])));
                }
            }
            else
            {
                for (const auto& entry : inst.data)
                    locals_.insert(locals_.begin(), entry);
            }

            break;
        }
        case opcode::OP_EvalLocalVariableCached:
        {
            if (!ctx_->fixup())
            {
                stack_.push(expr_identifier::make(loc, locals_.at(std::stoi(inst.data[0]))));
                break;
            }
            else // fix old compiler bug
            {
                try
                {
                    stack_.push(expr_identifier::make(loc, locals_.at(std::stoi(inst.data[0]))));
                }
                catch (const std::exception&)
                {
                    stack_.push(expr_identifier::make(loc, "broken_code!!"));
                }
                break;
            }
        }
        case opcode::OP_EvalArray:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto key = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_array::make(key->loc(), std::move(obj), std::move(key)));
            break;
        }
        case opcode::OP_EvalLocalArrayRefCached:
        {
            auto key = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = expr_identifier::make(loc, locals_.at(std::stoi(inst.data[0])));
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
        case opcode::OP_EvalFieldVariable:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(obj->loc(), std::move(obj), std::move(field)));
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
        case opcode::OP_SafeSetWaittillVariableFieldCached:
        {
            stack_.push(expr_identifier::make(loc, locals_.at(std::stoi(inst.data[0]))));
            break;
        }
        case opcode::OP_ClearParams:
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
        case opcode::OP_EvalLocalVariableRefCached:
        {
            stack_.push(expr_identifier::make(loc, locals_.at(std::stoi(inst.data[0]))));
            break;
        }
        case opcode::OP_SetVariableField:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = rvalue->loc();
            auto exp = expr_assign::make(loc, std::move(lvalue), std::move(rvalue), expr_assign::op::eq);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_CallBuiltin:
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
        case opcode::OP_CallBuiltinMethod:
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
        case opcode::OP_Wait:
        {
            auto exp = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_wait::make(exp->loc(), std::move(exp)));
            break;
        }
        case opcode::OP_WaitTillFrameEnd:
        {
            func_->body->block->list.push_back(stmt_waittillframeend::make(loc));
            break;
        }
        case opcode::OP_PreScriptCall:
        {
            stack_.push(node_prescriptcall::make(loc));
            break;
        }
        case opcode::OP_ScriptFunctionCall:
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
        case opcode::OP_ScriptMethodCall:
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
        case opcode::OP_ScriptThreadCall:
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

            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_ScriptThreadCallPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = func->loc();

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::node_prescriptcall)
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(expr_call::make(loc, expr_pointer::make(loc, std::move(func), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_ScriptMethodThreadCall:
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

            stack_.push(expr_method::make(loc, std::move(obj), expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_ScriptMethodThreadCallPointer:
        {
            auto args = expr_arguments::make(loc);
            auto func = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = obj->loc();

            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != node::node_prescriptcall)
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            stack_.push(expr_method::make(loc, std::move(obj), expr_pointer::make(loc, std::move(func), std::move(args), call::mode::thread)));
            break;
        }
        case opcode::OP_DecTop:
        {
            if (stack_.top()->kind() != node::expr_new)
            {
                auto exp = node::as<expr>(std::move(stack_.top())); stack_.pop();
                func_->body->block->list.push_back(stmt_expr::make(exp->loc(), std::move(exp)));
            }

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
        case opcode::OP_JumpOnTrue:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = lvalue->loc();

            if (inst.index > resolve_label(inst.data[0]))
            {
                func_->body->block->list.push_back(stmt_jmp_cond::make(loc, std::move(lvalue), inst.data[0]));
            }
            else
            {
                auto test = expr_not::make(loc, std::move(lvalue));
                func_->body->block->list.push_back(stmt_jmp_cond::make(loc, std::move(test), inst.data[0]));
            }
            break;
        }
        case opcode::OP_JumpOnFalse:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = lvalue->loc();

            if (inst.index > resolve_label(inst.data[0]))
            {
                auto test = expr_not::make(loc, std::move(lvalue));
                func_->body->block->list.push_back(stmt_jmp_cond::make(loc, std::move(test), inst.data[0]));
            }
            else
            {
                func_->body->block->list.push_back(stmt_jmp_cond::make(lvalue->loc(), std::move(lvalue), inst.data[0]));
            }
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
        case opcode::OP_Jump:
        {
            func_->body->block->list.push_back(stmt_jmp::make(loc, inst.data[0]));
            if (stack_.size() != 0) tern_labels_.push_back(inst.data[0]);
            break;
        }
        case opcode::OP_JumpBack:
        {
            func_->body->block->list.push_back(stmt_jmp_back::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_Inc:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = lvalue->loc();
            auto exp = expr_increment::make(lvalue->loc(), std::move(lvalue), false);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_Dec:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = lvalue->loc();
            auto exp = expr_decrement::make(loc, std::move(lvalue), false);
            func_->body->block->list.push_back(stmt_expr::make(loc, std::move(exp)));
            break;
        }
        case opcode::OP_Bit_Or:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::bwor));
            break;
        }
        case opcode::OP_Bit_Xor:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::bwexor));
            break;
        }
        case opcode::OP_Bit_And:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::bwand));
            break;
        }
        case opcode::OP_SuperEqual:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::seq));
            break;
        }
        case opcode::OP_SuperNotEqual:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::sne));
            break;
        }
        case opcode::OP_Equal:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::eq));
            break;
        }
        case opcode::OP_NotEqual:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::ne));
            break;
        }
        case opcode::OP_LessThan:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::lt));
            break;
        }
        case opcode::OP_GreaterThan:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::gt));
            break;
        }
        case opcode::OP_LessThanOrEqualTo:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::le));
            break;
        }
        case opcode::OP_GreaterThanOrEqualTo:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::ge));
            break;
        }
        case opcode::OP_ShiftLeft:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::shl));
            break;
        }
        case opcode::OP_ShiftRight:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::shr));
            break;
        }
        case opcode::OP_Plus:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::add));
            break;
        }
        case opcode::OP_Minus:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::sub));
            break;
        }
        case opcode::OP_Multiply:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::mul));
            break;
        }
        case opcode::OP_Divide:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::div));
            break;
        }
        case opcode::OP_Modulus:
        {
            auto rvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_binary::make(lvalue->loc(), std::move(lvalue), std::move(rvalue), expr_binary::op::mod));
            break;
        }
        case opcode::OP_SizeOf:
        {
            auto lvalue = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_size::make(lvalue->loc(), std::move(lvalue)));
            break;
        }
        case opcode::OP_WaitTillMatch:
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
        case opcode::OP_WaitTill:
        {
            auto args = expr_arguments::make(loc);
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto event = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(stmt_waittill::make(event->loc(), std::move(obj), std::move(event), std::move(args)));
            in_waittill_ = true;
            break;
        }
        case opcode::OP_Notify:
        {
            auto args = expr_arguments::make(loc);
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto event = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto var = std::move(stack_.top()); stack_.pop();
            loc = var->loc();

            while (var->kind() != ((ctx_->props() & props::size64) ? node::node_prescriptcall : node::node_voidcodepos))
            {
                args->list.push_back(node::as<expr>(std::move(var)));
                var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();
            }

            func_->body->block->list.push_back(stmt_notify::make(loc, std::move(obj), std::move(event), std::move(args)));
            break;
        }
        case opcode::OP_EndOn:
        {
            auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto event = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_endon::make(event->loc(), std::move(obj), std::move(event)));
            break;
        }
        case opcode::OP_VoidCodePos:
        {
            stack_.push(node_voidcodepos::make(loc));
            break;
        }
        case opcode::OP_Switch:
        {
            auto test = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_jmp_switch::make(test->loc(), std::move(test), inst.data[0]));
            break;
        }
        case opcode::OP_EndSwitch:
        {
            func_->body->block->list.push_back(stmt_jmp_endswitch::make(loc, inst.data));
            break;
        }
        case opcode::OP_Vector:
        {
            auto x = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto y = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto z = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_vector::make(z->loc(), std::move(x), std::move(y), std::move(z)));
            break;
        }
        case opcode::OP_GetHash:
        {
            stack_.push(expr_hash::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_RealWait:
        {
            auto exp = node::as<expr>(std::move(stack_.top())); stack_.pop();
            func_->body->block->list.push_back(stmt_waitrealtime::make(exp->loc(), std::move(exp)));
            break;
        }
        case opcode::OP_VectorConstant:
        {
            auto flags = static_cast<std::uint8_t>(std::stoi(inst.data[0]));
            auto x = expr_float::make(loc, (flags & 0x20) ? "1" : (flags & 0x10) ? "-1" : "0");
            auto y = expr_float::make(loc, (flags & 0x08) ? "1" : (flags & 0x04) ? "-1" : "0");
            auto z = expr_float::make(loc, (flags & 0x02) ? "1" : (flags & 0x01) ? "-1" : "0");
            stack_.push(expr_vector::make(loc, std::move(x), std::move(y), std::move(z)));
            break;
        }
        case opcode::OP_IsDefined:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_isdefined::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_VectorScale:
        {
            auto arg1 = node::as<expr>(std::move(stack_.top())); stack_.pop();
            auto arg2 = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_vectorscale::make(arg2->loc(), std::move(arg1), std::move(arg2)));
            break;
        }
        case opcode::OP_AnglesToUp:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_anglestoup::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_AnglesToRight:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_anglestoright::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_AnglesToForward:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_anglestoforward::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_AngleClamp180:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_angleclamp180::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_VectorToAngles:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_vectortoangles::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_Abs:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_abs::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetTime:
        {
            stack_.push(expr_gettime::make(loc));
            break;
        }
        case opcode::OP_GetDvar:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_getdvar::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarInt:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_getdvarint::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarFloat:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_getdvarfloat::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarVector:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_getdvarvector::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarColorRed:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_getdvarcolorred::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarColorGreen:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_getdvarcolorgreen::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarColorBlue:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_getdvarcolorblue::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_GetDvarColorAlpha:
        {
            auto arg = node::as<expr>(std::move(stack_.top())); stack_.pop();
            stack_.push(expr_getdvarcoloralpha::make(arg->loc(), std::move(arg)));
            break;
        }
        case opcode::OP_FirstArrayKey:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, "getfirstarraykey");
            auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = var->loc();
            args->list.push_back(std::move(var));
            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_NextArrayKey:
        {
            auto args = expr_arguments::make(loc);
            auto path = expr_path::make(loc);
            auto name = expr_identifier::make(loc, "getnextarraykey");
            auto var = node::as<expr>(std::move(stack_.top())); stack_.pop();
            args->list.push_back(std::move(var));
            var = node::as<expr>(std::move(stack_.top())); stack_.pop();
            loc = var->loc();
            args->list.push_back(std::move(var));
            stack_.push(expr_call::make(loc, expr_function::make(loc, std::move(path), std::move(name), std::move(args), call::mode::normal)));
            break;
        }
        case opcode::OP_LevelEvalFieldVariable:
        case opcode::OP_LevelEvalFieldVariableRef:
        {
            auto obj = expr_level::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_SelfEvalFieldVariable:
        case opcode::OP_SelfEvalFieldVariableRef:
        {
            auto obj = expr_self::make(loc);
            auto field = expr_identifier::make(loc, inst.data[0]);
            stack_.push(expr_field::make(loc, std::move(obj), std::move(field)));
            break;
        }
        case opcode::OP_DevblockBegin:
        {
            func_->body->block->list.push_back(stmt_jmp_dev::make(loc, inst.data[0]));
            break;
        }
        case opcode::OP_New:
        {
            stack_.push(expr_new::make(loc, expr_identifier::make(loc, inst.data[0])));
            break;
        }
        case opcode::OP_ScriptFunctionCallClass:
        {
            if (stack_.top()->kind() != node::expr_new || inst.data[0] != "__constructor")
            {
                auto args = expr_arguments::make(loc);
                auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();

                while (var->kind() != node::node_prescriptcall)
                {
                    args->list.push_back(node::as<expr>(std::move(var)));
                    var = std::move(stack_.top()); stack_.pop();
                    loc = var->loc();
                }

                stack_.push(expr_call::make(loc, expr_member::make(loc, std::move(obj), expr_identifier::make(loc, inst.data[0]), std::move(args), call::mode::normal)));
            }
            break;
        }
        case opcode::OP_ScriptThreadCallClass:
        {
            if (stack_.top()->kind() != node::expr_new)
            {
                auto args = expr_arguments::make(loc);
                auto obj = node::as<expr>(std::move(stack_.top())); stack_.pop();
                auto var = std::move(stack_.top()); stack_.pop();
                loc = var->loc();

                while (var->kind() != node::node_prescriptcall)
                {
                    args->list.push_back(node::as<expr>(std::move(var)));
                    var = std::move(stack_.top()); stack_.pop();
                    loc = var->loc();
                }

                stack_.push(expr_call::make(loc, expr_member::make(loc, std::move(obj), expr_identifier::make(loc, inst.data[0]), std::move(args), call::mode::thread)));
            }
            break;
        }
        case opcode::OP_CheckClearParams:
        case opcode::OP_CastFieldObject:
        case opcode::OP_CastBool:
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
        if (stm.list.at(i)->is<stmt_jmp>())
        {
            if (stm.list.at(i)->loc().begin.line < std::stol(stm.list.at(i)->as<stmt_jmp>().value.substr(4), 0, 16))
                continue;

            if (stm.list.at(i)->as<stmt_jmp>().value == locs_.cnt)
                continue;

            auto break_loc = last_location_index(stm, i) ? locs_.end : stm.list.at(i + 1)->label();
            auto start = find_location_index(stm, stm.list.at(i)->as<stmt_jmp>().value);

            if (stm.list.at(i - 1)->is<stmt_jmp_cond>() && stm.list.at(i - 1)->as<stmt_jmp_cond>().value == break_loc)
            {
                continue;
            }
            else if (!stm.list.at(start)->is<stmt_jmp_cond>())
            {
                decompile_inf(stm, start, i);
                i = static_cast<i32>(stm.list.size());
            }
            else if (stm.list.at(start)->as<stmt_jmp_cond>().value != break_loc)
            {
                decompile_inf(stm, start, i);
                i = static_cast<i32>(stm.list.size());
            }
            else if (stm.list.at(start)->as<stmt_jmp_cond>().value == break_loc)
            {
                decompile_loop(stm, start, i);
                i = static_cast<i32>(stm.list.size());
            }
        }
    }
}

auto decompiler::decompile_loops(stmt_list& stm) -> void
{
    for (auto i = 0u; i < stm.list.size(); i++)
    {
        auto& entry = stm.list.at(i);

        if (entry->is<stmt_jmp_cond>())
        {
            auto j = find_location_index(stm, entry->as<stmt_jmp_cond>().value);

            if (j < i)
            {
                decompile_dowhile(stm, j, i);
                i = 0;
                continue;
            }

            j -= 1;

            if (stm.list.at(j)->is<stmt_jmp>())
            {
                if (stm.list.at(j)->loc().begin.line < std::stol(stm.list.at(j)->as<stmt_jmp>().value.substr(4), 0, 16))
                    continue;

                if (stm.list.at(i)->loc().label() == stm.list.at(j)->as<stmt_jmp>().value)
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
        const auto& entry = stm.list.at(i);

        if (entry->is<stmt_jmp_cond>())
        {
            auto j = find_location_index(stm, entry->as<stmt_jmp_cond>().value) - 1;
            auto last_loc = locs_.end;

            if (stm.list.at(j)->is<stmt_jmp>())
            {
                // if block is a loop check break, continue
                if (stm.list.at(j)->as<stmt_jmp>().value == locs_.cnt)
                {
                    //if its a while, continue jumps back
                    if (stm.list.at(j)->loc().begin.line > std::stol(stm.list.at(j)->as<stmt_jmp>().value.substr(4), 0, 16))
                    {
                        decompile_if(stm, i, j);
                    }
                    // a dowhile, for or foreach, check for if/else or if/continue
                    else if (j - i > 1 && stm.list.at(j - 1)->is<stmt_return>())
                    {
                        // block ends with a return, so jump belows to if/else
                        decompile_ifelse(stm, i, j);
                    }
                    else if (j - i > 1 && stm.list.at(j - 1)->is<stmt_jmp>())
                    {
                        if (stm.list.at(j - 1)->as<stmt_jmp>().value == locs_.brk)
                        {
                            // block ends with a break, so jump belows to if/else
                            decompile_ifelse(stm, i, j);
                        }
                        else if (stm.list.at(j - 1)->as<stmt_jmp>().value == locs_.cnt)
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
                else if (stm.list.at(j)->as<stmt_jmp>().value == locs_.brk)
                {
                    decompile_if(stm, i, j);
                }
                else if (stm.list.at(j)->as<stmt_jmp>().value == locs_.end)
                {
                    if (find_location_reference(stm, i + 1, j, entry->as<stmt_jmp_cond>().value))
                        decompile_if(stm, i, j);
                    else
                        decompile_ifelse(stm, i, j);
                }
                else if (stm.list.at(j)->as<stmt_jmp>().value == entry->as<stmt_jmp_cond>().value)
                {
                    if (find_location_reference(stm, i + 1, j, entry->as<stmt_jmp_cond>().value))
                        decompile_if(stm, i, j);
                    else
                        decompile_ifelse(stm, i, j);
                }
                else
                {
                    // fix treyarch compiler bug: breaks outside loops or switches
                    auto out_of_scope = stm.list.at(stm.list.size() - 1)->loc().begin.line < std::stol(stm.list.at(j)->as<stmt_jmp>().value.substr(4), 0, 16);

                    if (locs_.brk == "" && out_of_scope)
                        decompile_if(stm, i, j);
                    else
                        decompile_ifelse(stm, i, j);

                    //decompile_ifelse(stm, i, j);
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
                // fix treyarch compiler bug: breaks outside loops or switches
                if (locs_.brk == "")
                {
                    stm.list.erase(stm.list.begin() + i);
                    stm.list.insert(stm.list.begin() + i, stmt_break::make(loc));
                }
                // fix treyarch compiler bug: nested switch break locs are not preserved
                else if (jmp != locs_.end && stm.list.at(find_location_index(stm, jmp))->is<stmt_break>())
                {
                    stm.list.erase(stm.list.begin() + i);
                    stm.list.insert(stm.list.begin() + i, stmt_break::make(loc));
                    continue;
                }
                else if (locs_.is_switch && stm.list.at(stm.list.size() - 1)->is<stmt_switch>())
                {
                    stm.list.erase(stm.list.begin() + i);
                    stm.list.insert(stm.list.begin() + i, stmt_break::make(loc));
                    continue;
                }

                std::cout << "WARNING: unresolved jump to '" + jmp + "', maybe incomplete for loop\n";
            }
        }
    }
}

auto decompiler::decompile_devblocks(stmt_list& stm) -> void
{
    for (auto i = 0u; i < stm.list.size(); i++)
    {
        if (stm.list.at(i)->is<stmt_jmp_dev>())
        {
            if (locs_.is_dev)
            {
                stm.list.erase(stm.list.begin() + i--);
                continue;
            }

            if (i + 1 < stm.list.size())
            {
                if (stm.list.at(i + 1)->is<stmt_jmp_dev>() && stm.list.at(i + 1)->as<stmt_jmp_dev>().value == stm.list.at(i)->as<stmt_jmp_dev>().value)
                {
                    stm.list.erase(stm.list.begin() + i + 1);
                }
            }

            auto loc = stm.list.at(i)->loc();
            auto end = find_location_index(stm, stm.list.at(i)->as<stmt_jmp_dev>().value);

            auto save = locs_;
            locs_.end = stm.list.at(i)->as<stmt_jmp_dev>().value;
            locs_.is_dev = true;

            stm.list.erase(stm.list.begin() + i);
            end -= 1;

            auto list_stmt = stmt_list::make(loc);

            for (auto j = i; j < end; j++)
            {
                list_stmt->list.push_back(std::move(stm.list[i]));
                stm.list.erase(stm.list.begin() + i);
            }

            decompile_statements(*list_stmt);
            locs_ = save;

            if (list_stmt->list.size() == 1 && list_stmt->list.at(0)->is<stmt_expr>())
            {
                const auto& st = list_stmt->list.at(0);

                if (st->as<stmt_expr>().value->is<expr_call>() && st->as<stmt_expr>().value->as<expr_call>().value->is<expr_function>())
                {
                    auto func = st->as<stmt_expr>().value->as<expr_call>().value->as<expr_function>().name->value;

                    if (func == "assert" || func == "assertmsg")
                    {
                        stm.list.insert(stm.list.begin() + i, std::move(list_stmt->list.at(0)));
                        continue;
                    }
                }
            }

            auto new_stmt = stmt_dev::make(loc, std::move(list_stmt));
            stm.list.insert(stm.list.begin() + i, std::move(new_stmt));
        }
    }
}

auto decompiler::decompile_if(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
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

auto decompiler::decompile_inf(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.brk = last_location_index(stm, end) ? locs_.end : stm.list[end + 1]->label();
    locs_.end = stm.list[end]->label();
    locs_.cnt = stm.list[ctx_->fixup() ? begin : end]->label(); // fix old compiler bug

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

auto decompiler::decompile_loop(stmt_list& stm, usize begin, usize end) -> void
{
    if (ctx_->props() & props::foreach && (begin + 2 < end))
    {
        auto& last = stm.list.at(begin + 2);

        if (last->is<stmt_expr>())
        {
            if (last->as<stmt_expr>().value->is<expr_assign>())
            {
                auto& val = last->as<stmt_expr>().value->as<expr_assign>().rvalue;

                if (val->is<expr_call>() && val->as<expr_call>().value->is<expr_function>())
                {
                    if (utils::string::to_lower(val->as<expr_call>().value->as<expr_function>().name->value) == "getnextarraykey")
                    {
                        auto ref = stm.list.at(begin)->label();

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

    if (last->is<stmt_expr>())
    {
        if (last->as<stmt_expr>().value->is<expr_assign>())
        {
            auto& val = last->as<stmt_expr>().value->as<expr_assign>().rvalue;

            if (val->is<expr_call>() && val->as<expr_call>().value->is<expr_function>())
            {
                if (utils::string::to_lower(val->as<expr_call>().value->as<expr_function>().name->value) == "getnextarraykey")
                {
                    auto ref = stm.list.at(begin)->label();

                    if (!find_location_reference(stm, 0, begin, ref))
                    {
                        decompile_foreach(stm, begin, end);
                        return;
                    }
                }
            }
        }

        if (begin > 0 && stm.list.at(begin - 1)->is<stmt_expr>()) // while at func start
        {
            if (stm.list.at(begin - 1)->as<stmt_expr>().value->is_assign())
            {
                if (!lvalues_match(stm.list.at(begin - 1)->as<stmt_expr>(), last->as<stmt_expr>()))
                {
                    decompile_while(stm, begin, end);
                    return;
                }

                auto ref1 = stm.list.at(end)->label();
                auto ref2 = stm.list.at(begin)->label();

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
    locs_.end = stm.list[end]->label();
    locs_.cnt = stm.list[begin]->label();
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
    locs_.end = stm.list[end]->label();
    locs_.cnt = stm.list[end]->label();
    locs_.brk = last_location_index(stm, end) ? save.end : stm.list[end + 1]->label();

    auto test = std::move(stm.list[end]->as<stmt_jmp_cond>().test);
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
    stm.list.insert(stm.list.begin() + begin, stmt_dowhile::make(loc, std::move(test), stmt_comp::make(loc, std::move(body))));
}

auto decompiler::decompile_for(stmt_list& stm, usize begin, usize end) -> void
{
    auto save = locs_;
    locs_.end = stm.list[end - 1]->label();
    locs_.cnt = stm.list[end - 1]->label();
    locs_.brk = stm.list[begin]->as<stmt_jmp_cond>().value;

    begin--;
    auto loc = stm.list[begin]->loc();
    auto init = std::move(stm.list[begin]);
    stm.list.erase(stm.list.begin() + begin);

    auto test = std::move(stm.list[begin]->as<stmt_jmp_cond>().test);
    stm.list.erase(stm.list.begin() + begin);

    end -= 3;
    auto iter = std::move(stm.list[end]);
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
    locs_.end = stm.list[end - 1]->label();
    locs_.cnt = stm.list[end - 1]->label();
    locs_.brk = stm.list[begin]->as<stmt_jmp_cond>().value;

    begin -= 2;

    auto loc = stm.list[begin]->loc();
    auto container = std::move(stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().rvalue);
    auto array = std::move(stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().lvalue);
    stm.list.erase(stm.list.begin() + begin);

    auto key = std::move(stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().lvalue);
    stm.list.erase(stm.list.begin() + begin);
    stm.list.erase(stm.list.begin() + begin);

    auto value = std::move(stm.list[begin]->as<stmt_expr>().value->as<expr_assign>().lvalue);
    stm.list.erase(stm.list.begin() + begin);

    end -= (ctx_->props() & props::foreach) ? 6 : 5;

    if (ctx_->props() & props::foreach)
        stm.list.erase(stm.list.begin() + begin);

    stm.list.erase(stm.list.begin() + end);
    stm.list.erase(stm.list.begin() + end);

    auto use_key = !key->as<expr_identifier>().value.starts_with("_k");

    if ((ctx_->props() & props::foreach) && key->as<expr_identifier>().value.starts_with("_id_"))
        use_key = false;

    auto body = stmt_list::make(loc);

    for (auto i = begin; i < end; i++)
    {
        body->list.push_back(std::move(stm.list[begin]));
        stm.list.erase(stm.list.begin() + begin);
    }

    decompile_statements(*body);
    locs_ = save;
    stm.list.insert(stm.list.begin() + begin, stmt_foreach::make(loc, std::move(container), std::move(value), std::move(array), std::move(key), stmt_comp::make(loc, std::move(body)), use_key));
}

auto decompiler::decompile_switch(stmt_list& stm, usize begin, usize end) -> void
{
    auto const& data = stm.list[end]->as<stmt_jmp_endswitch>().data;
    auto const count = std::stoul(data[0]);
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

    auto save = locs_;
    locs_.brk = last_location_index(stm, end) ? locs_.end : stm.list[end + 1]->label();
    locs_.end = stm.list[begin]->as<stmt_jmp_switch>().value;
    locs_.is_switch = true;

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
        else if (entry->is<stmt_jmp_dev>() && entry->as<stmt_jmp_dev>().value == loc)
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
    return (index == stm.list.size() - 1);
}

auto decompiler::lvalues_match(stmt_expr const& stm1, stmt_expr const& stm2) -> bool
{
    expr* lvalue1 {};
    expr* lvalue2 {};

    switch (stm1.value->kind())
    {
        case node::expr_increment:
            lvalue1 = stm1.value->as<expr_increment>().lvalue.get();
            break;
        case node::expr_decrement:
            lvalue1 = stm1.value->as<expr_decrement>().lvalue.get();
            break;
        case node::expr_assign:
            lvalue1 = stm1.value->as<expr_assign>().lvalue.get();
            break;
        default:
            break;
    }

    switch (stm2.value->kind())
    {
        case node::expr_increment:
            lvalue2 = stm2.value->as<expr_increment>().lvalue.get();
            break;
        case node::expr_decrement:
            lvalue2 = stm2.value->as<expr_decrement>().lvalue.get();
            break;
        case node::expr_assign:
            lvalue2 = stm2.value->as<expr_assign>().lvalue.get();
            break;
        default:
            break;
    }

    if (lvalue1 && lvalue2 && *lvalue1 == *lvalue2)
        return true;

    return false;
}

auto decompiler::resolve_label(std::string const& name) const -> usize
{
    for (auto const& entry : labels_)
    {
        if (entry.second == name)
        {
            return entry.first;
        }
    }

    throw decomp_error(std::format("couldn't resolve label address of '{}'", name));
}

auto decompiler::process_function(decl_function& func) -> void
{
    process_stmt_comp(*func.body);
    process_expr_parameters(*func.params);

    if (ctx_->props() & props::spaces)
    {
        if (namespace_ != func.space->value)
        {
            namespace_ = func.space->value;
            program_->declarations.push_back(decl_namespace::make(func.loc(), expr_string::make(func.loc(), func.space->value)));
        }
    }

    func.space->value = {};
}

auto decompiler::process_stmt(stmt& stm) -> void
{
    switch (stm.kind())
    {
        case node::stmt_list:
            process_stmt_list(stm.as<stmt_list>());
            break;
        case node::stmt_comp:
            process_stmt_comp(stm.as<stmt_comp>());
            break;
        case node::stmt_dev:
            process_stmt_dev(stm.as<stmt_dev>());
            break;
        case node::stmt_expr:
            process_stmt_expr(stm.as<stmt_expr>());
            break;
        case node::stmt_endon:
            process_stmt_endon(stm.as<stmt_endon>());
            break;
        case node::stmt_notify:
            process_stmt_notify(stm.as<stmt_notify>());
            break;
        case node::stmt_wait:
            process_stmt_wait(stm.as<stmt_wait>());
            break;
        case node::stmt_waitrealtime:
            process_stmt_waitrealtime(stm.as<stmt_waitrealtime>());
            break;
        case node::stmt_waittill:
            process_stmt_waittill(stm.as<stmt_waittill>());
            break;
        case node::stmt_waittillmatch:
            process_stmt_waittillmatch(stm.as<stmt_waittillmatch>());
            break;
        case node::stmt_if:
            process_stmt_if(stm.as<stmt_if>());
            break;
        case node::stmt_ifelse:
            process_stmt_ifelse(stm.as<stmt_ifelse>());
            break;
        case node::stmt_while:
            process_stmt_while(stm.as<stmt_while>());
            break;
        case node::stmt_dowhile:
            process_stmt_dowhile(stm.as<stmt_dowhile>());
            break;
        case node::stmt_for:
            process_stmt_for(stm.as<stmt_for>());
            break;
        case node::stmt_foreach:
            process_stmt_foreach(stm.as<stmt_foreach>());
            break;
        case node::stmt_switch:
            process_stmt_switch(stm.as<stmt_switch>());
            break;
        case node::stmt_return:
            process_stmt_return(stm.as<stmt_return>());
            break;
        default:
            break;
    }
}

auto decompiler::process_stmt_list(stmt_list& stm) -> void
{
    for (auto& entry : stm.list)
    {
        process_stmt(*entry);
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
    switch (stm.value->kind())
    {
        case node::expr_increment:
            process_expr_increment(stm.value->as<expr_increment>());
            break;
        case node::expr_decrement:
            process_expr_decrement(stm.value->as<expr_decrement>());
            break;
        case node::expr_assign:
            process_expr_assign(*reinterpret_cast<expr_assign::ptr*>(&stm.value));
            break;
        case node::expr_call:
            process_expr_call(stm.value->as<expr_call>());
            break;
        case node::expr_method:
            process_expr_method(stm.value->as<expr_method>());
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

auto decompiler::process_stmt_wait(stmt_wait& stm) -> void
{
    process_expr(stm.time);
}

auto decompiler::process_stmt_waitrealtime(stmt_waitrealtime& stm) -> void
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

    process_stmt(*stm.body);

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
    }
}

auto decompiler::process_stmt_ifelse(stmt_ifelse& stm) -> void
{
    process_expr(stm.test);
    process_stmt(*stm.stmt_if);
    process_stmt(*stm.stmt_else);

    if (stm.stmt_if->as<stmt_comp>().block->list.size() == 1 && !stm.stmt_if->as<stmt_comp>().block->list[0]->is_special_stmt_dev())
    {
        stm.stmt_if = std::move(stm.stmt_if->as<stmt_comp>().block->list.back());
    }

    if (stm.stmt_else->as<stmt_comp>().block->list.size() == 1 && !stm.stmt_else->as<stmt_comp>().block->list[0]->is_special_stmt_dev_noif())
    {
        stm.stmt_else = std::move(stm.stmt_else->as<stmt_comp>().block->list.back());
    }
}

auto decompiler::process_stmt_while(stmt_while& stm) -> void
{
    if (stm.test->is<expr_integer>() && stm.test->as<expr_integer>().value == "1")
    {
        stm.test = expr_true::make(stm.test->loc());
    }

    process_expr(stm.test);
    process_stmt(*stm.body);

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
    }
}

auto decompiler::process_stmt_dowhile(stmt_dowhile& stm) -> void
{
    if (stm.test->is<expr_integer>() && stm.test->as<expr_integer>().value == "1")
    {
        stm.test = expr_true::make(stm.test->loc());
    }

    process_expr(stm.test);
    process_stmt(*stm.body);

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
    }
}

auto decompiler::process_stmt_for(stmt_for& stm) -> void
{
    process_stmt(*stm.init);
    process_expr(stm.test);
    process_stmt(*stm.body);
    process_stmt(*stm.iter);

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
    }
}

auto decompiler::process_stmt_foreach(stmt_foreach& stm) -> void
{
    process_expr(stm.container);
    process_expr(stm.array);
    process_expr(stm.key);
    process_expr(stm.value);

    if ((ctx_->props() & props::foreach) && !stm.use_key)
        vars_.insert(stm.key->as<expr_identifier>().value);

    process_stmt(*stm.body);

    if ((ctx_->props() & props::foreach) && !stm.use_key)
    {
        auto const it = vars_.find(stm.key->as<expr_identifier>().value);

        if (it != vars_.end())
            vars_.erase(it);
        else
            stm.use_key = true;
    }

    if (stm.body->as<stmt_comp>().block->list.size() == 1 && !stm.body->as<stmt_comp>().block->list[0]->is_special_stmt_dev())
    {
        stm.body = std::move(stm.body->as<stmt_comp>().block->list.back());
    }
}

auto decompiler::process_stmt_switch(stmt_switch& stm) -> void
{
    process_expr(stm.test);

    for (auto& entry : stm.body->block->list)
    {
        if (entry->is<stmt_case>())
        {
            process_stmt_list(*entry->as<stmt_case>().body);
        }
        else if (entry->is<stmt_default>())
        {
            process_stmt_list(*entry->as<stmt_default>().body);
        }
    }
}

auto decompiler::process_stmt_return(stmt_return& stm) -> void
{
    if (!stm.value->is<expr_empty>())
    {
        if (retbool_ && stm.value->is<expr_integer>())
            stm.value = stm.value->as<expr_integer>().value == "1" ? expr::ptr{ expr_true::make(stm.loc()) } : expr::ptr{ expr_false::make(stm.loc()) };
        else
            process_expr(stm.value);
    }
}

auto decompiler::process_expr(expr::ptr& exp) -> void
{
    switch (exp->kind())
    {
        case node::expr_ternary:
            process_expr_ternary(exp->as<expr_ternary>());
            break;
        case node::expr_binary:
            process_expr_binary(exp->as<expr_binary>());
            break;
        case node::expr_complement:
            process_expr_complement(exp->as<expr_complement>());
            break;
        case node::expr_not:
            process_expr_not(exp->as<expr_not>());
            break;
        case node::expr_call:
            process_expr_call(exp->as<expr_call>());
            break;
        case node::expr_method:
            process_expr_method(exp->as<expr_method>());
            break;
        case node::expr_getnextarraykey:
            process_expr(exp->as<expr_getnextarraykey>().arg2);
            process_expr(exp->as<expr_getnextarraykey>().arg1);
            break;
        case node::expr_getfirstarraykey:
            process_expr(exp->as<expr_getfirstarraykey>().arg);
            break;
        case node::expr_getdvarcoloralpha:
            process_expr(exp->as<expr_getdvarcoloralpha>().arg);
            break;
        case node::expr_getdvarcolorblue:
            process_expr(exp->as<expr_getdvarcolorblue>().arg);
            break;
        case node::expr_getdvarcolorgreen:
            process_expr(exp->as<expr_getdvarcolorgreen>().arg);
            break;
        case node::expr_getdvarcolorred:
            process_expr(exp->as<expr_getdvarcolorred>().arg);
            break;
        case node::expr_getdvarvector:
            process_expr(exp->as<expr_getdvarvector>().arg);
            break;
        case node::expr_getdvarfloat:
            process_expr(exp->as<expr_getdvarfloat>().arg);
            break;
        case node::expr_getdvarint:
            process_expr(exp->as<expr_getdvarint>().arg);
            break;
        case node::expr_getdvar:
            process_expr(exp->as<expr_getdvar>().arg);
            break;
        case node::expr_abs:
            process_expr(exp->as<expr_abs>().arg);
            break;
        case node::expr_vectortoangles:
            process_expr(exp->as<expr_vectortoangles>().arg);
            break;
        case node::expr_angleclamp180:
            process_expr(exp->as<expr_angleclamp180>().arg);
            break;
        case node::expr_anglestoforward:
            process_expr(exp->as<expr_anglestoforward>().arg);
            break;
        case node::expr_anglestoright:
            process_expr(exp->as<expr_anglestoright>().arg);
            break;
        case node::expr_anglestoup:
            process_expr(exp->as<expr_anglestoup>().arg);
            break;
        case node::expr_vectorscale:
            process_expr(exp->as<expr_vectorscale>().arg2);
            process_expr(exp->as<expr_vectorscale>().arg1);
            break;
        case node::expr_isdefined:
            process_expr(exp->as<expr_isdefined>().value);
            break;
        case node::expr_reference:
            process_expr_reference(exp->as<expr_reference>());
            break;
        case node::expr_array:
            process_expr_array(exp->as<expr_array>());
            break;
        case node::expr_field:
            process_expr_field(exp->as<expr_field>());
            break;
        case node::expr_size:
            process_expr_size(exp->as<expr_size>());
            break;
        case node::expr_vector:
            process_expr_vector(exp->as<expr_vector>());
            break;
        case node::expr_identifier:
            process_expr_identifier(exp->as<expr_identifier>());
            break;
        default:
            break;
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

auto decompiler::process_expr_assign(expr_assign::ptr& exp) -> void
{
    process_expr(exp->rvalue);
    process_expr(exp->lvalue);

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

auto decompiler::process_expr_complement(expr_complement& exp) -> void
{
    process_expr(exp.rvalue);

    if (exp.rvalue->is<expr_binary>())
    {
        exp.rvalue = expr_paren::make(exp.loc(), std::move(exp.rvalue));
    }
}

auto decompiler::process_expr_not(expr_not& exp) -> void
{
    process_expr(exp.rvalue);

    if (exp.rvalue->is<expr_binary>())
    {
        exp.rvalue = expr_paren::make(exp.loc(), std::move(exp.rvalue));
    }
}

auto decompiler::process_expr_call(expr_call& exp) -> void
{
    switch (exp.value->kind())
    {
        case node::expr_member:
            process_expr_call_member(exp.value->as<expr_member>());
            break;
        case node::expr_pointer:
            process_expr_call_pointer(exp.value->as<expr_pointer>());
            break;
        case node::expr_function:
            process_expr_call_function(exp.value->as<expr_function>());
            break;
        default:
            break;
    }
}

auto decompiler::process_expr_method(expr_method& exp) -> void
{
    switch (exp.value->kind())
    {
        case node::expr_pointer:
            process_expr_method_pointer(exp.value->as<expr_pointer>(), exp.obj);
            break;
        case node::expr_function:
            process_expr_method_function(exp.value->as<expr_function>(), exp.obj);
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

    if (ctx_->props() & props::spaces)
    {
        if (exp.path->value == namespace_)
        {
            exp.path->value = {};
        }
    }
}

auto decompiler::process_expr_method_pointer(expr_pointer& exp, expr::ptr& obj) -> void
{
    process_expr_arguments(*exp.args);
    process_expr(obj);
    process_expr(exp.func);
}

auto decompiler::process_expr_method_function(expr_function& exp, expr::ptr& obj) -> void
{
    process_expr_arguments(*exp.args);
    process_expr(obj);

    if (ctx_->props() & props::spaces)
    {
        if (exp.path->value == namespace_)
        {
            exp.path->value = {};
        }
    }
}

auto decompiler::process_expr_parameters(expr_parameters& exp) -> void
{
    if (exp.list.empty()) return;

    while (!func_->body->block->list.empty())
    {
        auto& stmt = func_->body->block->list.at(0);

        if (!stmt->is<stmt_if>() || !stmt->as<stmt_if>().test->is<expr_not>())
            return;

        auto& test = stmt->as<stmt_if>().test->as<expr_not>().rvalue;

        if (!test->is<expr_isdefined>() || !test->as<expr_isdefined>().value->is<expr_identifier>())
            return;

        if (!stmt->as<stmt_if>().body->is<stmt_expr>() || !stmt->as<stmt_if>().body->as<stmt_expr>().value->is<expr_assign>())
            return;

        if (stmt->as<stmt_if>().body->as<stmt_expr>().value->as<expr_assign>().oper != expr_assign::op::eq)
            return;

        if (test->as<expr_isdefined>().value != stmt->as<stmt_if>().body->as<stmt_expr>().value->as<expr_assign>().lvalue)
            return;

        auto index = 0u;

        for (auto& entry : exp.list)
        {
            if (entry->is<expr_identifier>() && entry->as<expr_identifier>().value == test->as<expr_isdefined>().value->as<expr_identifier>().value)
            {
                exp.list.erase(exp.list.begin() + index);
                exp.list.insert(exp.list.begin() + index, std::move(stmt->as<stmt_if>().body->as<stmt_expr>().value));
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

auto decompiler::process_expr_reference(expr_reference& exp) -> void
{
    if (ctx_->props() & props::spaces)
    {
        if (exp.path->value == namespace_)
        {
            exp.path->value = {};
        }
    }
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

auto decompiler::process_expr_size(expr_size& exp) -> void
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
