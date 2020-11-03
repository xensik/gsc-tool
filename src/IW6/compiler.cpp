// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW6.hpp"

#include "compiler_parser.hpp"
#include "compiler_lexer.hpp"

namespace IW6
{

compiler::compiler()
{

}

void compiler::compile(std::string& buffer)
{
    yyscan_t scanner;
    std::unique_ptr<node> result(nullptr);
    
    // Add the two NUL terminators, required by flex.   
    buffer.append("\0\0", 2);

    if (yylex_init(&scanner))
        exit(1);

    YY_BUFFER_STATE yybuffer = yy_scan_buffer(buffer.data(), buffer.size(), scanner);

    yy::parser parser(scanner, result);
    
    if(parser.parse())
    {
        LOG_ERROR("An error ocurred while parsing file.");
    }

    yy_delete_buffer(yybuffer, scanner);
    yylex_destroy(scanner);

    LOG_INFO("file parsing complete.");

    if(result != nullptr)
    {
        LOG_INFO("starting to compile...");
        //printf("%s", result->print().data());
        compile_tree(std::move(result));
    }
}

auto compiler::output() -> std::vector<std::shared_ptr<function>>
{
    return std::vector<std::shared_ptr<function>>();
}

void compiler::compile_tree(std::unique_ptr<node> tree)
{
    index_ = 0;

    if(tree->type == node_type::script)
    {
        auto script = (node_script*)tree.get();

        for(const auto& func : script->functions)
        {
            local_functions_.push_back(func->name->value);
        }
        for(const auto& include : script->includes)
        {
            emit_include(include);
        }
        for(const auto& animtree : script->animtrees)
        {
            emit_using_animtree(animtree);  
        }
        for(const auto& function : script->functions)
        {
            emit_function(function);
        }
        LOG_DEBUG("----------------------------------");
        LOG_DEBUG("files included: %d", includes_.size());
        LOG_DEBUG("animtrees used: %d", animtrees_.size());
        LOG_DEBUG("functions compiled: %d",assembly_.size());
    }    
}

void compiler::emit_include(const include_ptr& include)
{
    includes_.push_back(include->file->value);
    // need to parse the included file here, and make a vector with all function names
    // later assemble calls check if far call
    // ...
}

void compiler::emit_using_animtree(const using_animtree_ptr& animtree)
{
    animtrees_.push_back(animtree->animtree->value);
}

void compiler::emit_function(const function_ptr& func)
{
    function_ = std::make_shared<function>();
    function_->index = index_;
    local_vars.clear();
    param_vars.clear();

    function_->name = func->name->value;
    
    emit_parameters(func->param_list);
    emit_statement_list(func->stmt_block);
    emit_instruction(opcode::OP_End);

    function_->size = index_ - function_->index;
    assembly_.push_back(function_);
    LOG_DEBUG("function '%s' with %d instructions.",function_->name.data(), function_->instructions.size());
}

void compiler::emit_parameters(const param_list_ptr& param_list)
{
    for(auto& param : param_list->params)
    {
        auto inst = emit_instruction(opcode::OP_SafeCreateVariableFieldCached);
        inst->data.push_back(utils::string::va("%d", local_vars.size()));
        local_vars.insert(local_vars.begin(), param->value);      
    }

    auto inst = emit_instruction(opcode::OP_checkclearparams);
}

void compiler::emit_statement_list(const stmt_block_ptr& block)
{
    for(const auto& stmt : block->stmts)
    {
        emit_statement(stmt);
    }
}

void compiler::emit_statement(const stmt_ptr& stmt)
{
    switch(stmt.as_node->type)
    {
        case node_type::stmt_call:
            emit_statement_call(stmt.as_call);
            break;
        case node_type::stmt_assign:
            emit_statement_assign(stmt.as_assign);
            break;
        case node_type::stmt_endon:
            emit_statement_endon(stmt.as_endon);
            break;
        case node_type::stmt_notify:
            emit_statement_notify(stmt.as_notify);
            break;
        case node_type::stmt_wait:
            emit_statement_wait(stmt.as_wait);
            break;
        case node_type::stmt_waittill:
            emit_statement_waittill(stmt.as_waittill);
            break;
        case node_type::stmt_waittillmatch:
            emit_statement_waittillmatch(stmt.as_waittillmatch);
            break;
        case node_type::stmt_waittillframeend:
            emit_statement_waittillframeend(stmt.as_waittillframeend);
            break;
        case node_type::stmt_if:
            emit_statement_if(stmt.as_if);
            break;
        case node_type::stmt_ifelse:
            emit_statement_ifelse(stmt.as_ifelse);
            break;
        case node_type::stmt_while:
            emit_statement_while(stmt.as_while);
            break;
        case node_type::stmt_for:
            emit_statement_for(stmt.as_for);
            break;
        case node_type::stmt_foreach:
            emit_statement_foreach(stmt.as_foreach);
            break;
        case node_type::stmt_switch:
            emit_statement_switch(stmt.as_switch);
            break;
        case node_type::stmt_case: // ERROR ONLY ON SWITCH
            break;
        case node_type::stmt_default:  // ERROR ONLY ON SWITCH
            break;
        case node_type::stmt_break:  // ERROR ONLY ON LOOP
            break;
        case node_type::stmt_continue: // ERROR ONLY ON LOOP
            break;
        case node_type::stmt_return:
            emit_statement_return(stmt.as_return);
            break;
        default: // ERROR UNKNOWN
            break;
    }
}

void compiler::emit_statement_call(const stmt_call_ptr& stmt)
{
    emit_expr_call(stmt->expr);
    emit_instruction(opcode::OP_DecTop);
}

void compiler::emit_statement_assign(const stmt_assign_ptr& stmt)
{
    emit_expr_assign(stmt->expr);
}

void compiler::emit_statement_endon(const stmt_endon_ptr& stmt)
{

}

void compiler::emit_statement_notify(const stmt_notify_ptr& stmt)
{

}

void compiler::emit_statement_wait(const stmt_wait_ptr& stmt)
{

}

void compiler::emit_statement_waittill(const stmt_waittill_ptr& stmt)
{

}

void compiler::emit_statement_waittillmatch(const stmt_waittillmatch_ptr& stmt)
{

}

void compiler::emit_statement_waittillframeend(const stmt_waittillframeend_ptr& stmt)
{

}

void compiler::emit_statement_if(const stmt_if_ptr& stmt)
{

}

void compiler::emit_statement_ifelse(const stmt_ifelse_ptr& stmt)
{

}

void compiler::emit_statement_while(const stmt_while_ptr& stmt)
{

}

void compiler::emit_statement_for(const stmt_for_ptr& stmt)
{

}

void compiler::emit_statement_foreach(const stmt_foreach_ptr& stmt)
{

}

void compiler::emit_statement_switch(const stmt_switch_ptr& stmt)
{

}

void compiler::emit_statement_case(const stmt_case_ptr& stmt)
{

}

void compiler::emit_statement_default(const stmt_default_ptr& stmt)
{

}

void compiler::emit_statement_break(const stmt_break_ptr& stmt)
{

}

void compiler::emit_statement_continue(const stmt_continue_ptr& stmt)
{

}

void compiler::emit_statement_return(const stmt_return_ptr& stmt)
{

}

void compiler::emit_expression(const expr_ptr& expr)
{
    // objects not used? (level, anim, self)

    switch(expr.as_node->type)
    {
        case node_type::expr_ternary:
            emit_expr_ternary(expr.as_expr_ternary);
            break;
        case node_type::expr_cmp_and:
        case node_type::expr_cmp_or:
        case node_type::expr_cmp_equal:
        case node_type::expr_cmp_less:
        case node_type::expr_cmp_greater:
        case node_type::expr_cmp_less_equal:
        case node_type::expr_cmp_greater_equal:
        case node_type::expr_cmp_not_equal:

        case node_type::expr_bw_or:
        case node_type::expr_bw_and:
        case node_type::expr_bw_xor:
        case node_type::expr_shift_left:
        case node_type::expr_shift_right:
        case node_type::expr_add:
        case node_type::expr_sub:
        case node_type::expr_mult:
        case node_type::expr_div:
        case node_type::expr_mod:
            emit_expr_binary(expr);
            break;
        case node_type::expr_complement:
            emit_expr_complement(expr.as_expr_complement);
            break;
        case node_type::expr_not:
            emit_expr_not(expr.as_expr_not);
            break;
        case node_type::expr_call:
            emit_expr_call(expr.as_expr_call);
            break;
        case node_type::expr_subscribe:
            emit_expr_subscribe(expr.as_expr_subscribe);
            break;
        case node_type::expr_select:
            emit_expr_select(expr.as_expr_select);
            break;
        case node_type::expr_func_ref:
            emit_expr_func_ref(expr.as_expr_func_ref);
            break;
        case node_type::empty_array:
            emit_instruction(opcode::OP_EmptyArray);
            break;
        case node_type::undefined:
            emit_instruction(opcode::OP_GetUndefined);
            break;
        // globals
       case node_type::level:
            emit_instruction(opcode::OP_GetLevel);
            break;
        case node_type::anim:
            emit_instruction(opcode::OP_GetAnim);
            break;
        case node_type::self:
            emit_instruction(opcode::OP_GetSelf);
            break;
        case node_type::game:
            emit_instruction(opcode::OP_GetGame);
            break;
        // basic
        case node_type::identifier:
            emit_expr_variable(expr.as_identifier);
            break;
        case node_type::string:
            emit_string(expr.as_string);
            break;
        case node_type::string_loc:
            emit_string_loc(expr.as_string_loc);
            break;
        case node_type::float_:
            emit_float(expr.as_float_);
            break;
        case node_type::integer:
            emit_integer(expr.as_integer);
            break;
        case node_type::vector:
            emit_vector(expr.as_vector);
            break;
    }
}

void compiler::emit_expr_assign(const expr_assign_ptr& expr)	
{
    if(expr->type == node_type::expr_inc)
    {
        emit_expression(*(expr_ptr*)&expr->lvalue);
        emit_instruction(opcode::OP_inc);
    }
    else if(expr->type == node_type::expr_dec)
    {
        emit_expression(*(expr_ptr*)&expr->lvalue);
        emit_instruction(opcode::OP_dec);
    }
    else if(expr->type == node_type::expr_assign_equal)
    {
        //TODO:  undefined, clear array ????
        emit_expression(*(expr_ptr*)&expr->rvalue);
        emit_expr_ref(*(expr_ptr*)&expr->lvalue, true);
    }
    else
    {
        emit_expression(*(expr_ptr*)&expr->rvalue);
        emit_expression(*(expr_ptr*)&expr->lvalue);

        switch(expr->type)
        {
            case node_type::expr_assign_add:
                emit_instruction(opcode::OP_plus);
                break;
            case node_type::expr_assign_sub:
                emit_instruction(opcode::OP_minus);
                break;
            case node_type::expr_assign_mult:
                emit_instruction(opcode::OP_multiply);
                break;
            case node_type::expr_assign_div:
                emit_instruction(opcode::OP_divide);
                break;
            case node_type::expr_assign_mod:
                emit_instruction(opcode::OP_mod);
                break;
            case node_type::expr_assign_shift_left:
                emit_instruction(opcode::OP_shift_left);
                break;
            case node_type::expr_assign_shift_right:
                emit_instruction(opcode::OP_shift_right);
                break;
            case node_type::expr_assign_bw_or:
                emit_instruction(opcode::OP_bit_or);
                break;
            case node_type::expr_assign_bw_and:
                emit_instruction(opcode::OP_bit_and);
                break;
            case node_type::expr_assign_bw_xor:
                emit_instruction(opcode::OP_bit_ex_or);
                break;
            default:
                LOG_ERROR("unknown assignment operation!");
                break;
        }

        emit_expr_ref(*(expr_ptr*)&expr->lvalue, true);
    }  
}

void compiler::emit_expr_ternary(const expr_ternary_ptr& expr)
{

}

void compiler::emit_expr_binary(const expr_ptr& expr)
{

}

void compiler::emit_expr_complement(const expr_complement_ptr& expr)
{
    emit_expression(*(expr_ptr*)&expr->rvalue);
    emit_instruction(opcode::OP_BoolComplement);
}

void compiler::emit_expr_not(const expr_not_ptr& expr)
{
    emit_expression(*(expr_ptr*)&expr->rvalue);
    emit_instruction(opcode::OP_BoolNot);
}

void compiler::emit_expr_call(const expr_call_ptr& expr)
{
    bool thread, method, builtin, far, local = false;
    std::string file, name;
    node_expr_arg_list* arg_list;
    node* pointer_expr;
    std::uint32_t args = 0;

    thread = expr->thread;

    if(expr->obj->type != node_type::null)
    {
        method = true;
    }

    if(expr->func.as_node->type == node_type::expr_pointer_call)
    {
        if(expr->func.as_pointer->expr->type == node_type::identifier)
        {
            builtin = is_builtin_call(*(identifier_ptr*)&expr->func.as_pointer->expr);
        }
        
        args = expr->func.as_pointer->arg_list->args.size();
        
        if(!thread && !builtin)
            emit_instruction(opcode::OP_PreScriptCall);
  
        emit_expr_arg_list(expr->func.as_pointer->arg_list);
        emit_expression(*(expr_ptr*)&expr->func.as_pointer->expr);
        emit_expr_call_pointer(args, builtin, method, thread, false);
    }
    else
    {
        args = expr->func.as_func->arg_list->args.size();
        name = expr->func.as_func->name->value;
        file = expr->func.as_func->file->value;

        if(file != "")
        {
            far = true;
        }
        else
        {
            if(is_local_call(expr->func.as_func->name))
            {
                local = true;
            }
            else if(is_builtin_call(expr->func.as_func->name))
            {
                builtin = true;
            }
            else
            {
                // include files not supported!
                LOG_ERROR("unknown call type. maybe far call without file.");
            }
        }

        if(args > 0 && !thread && !builtin)
            emit_instruction(opcode::OP_PreScriptCall);

        emit_expr_arg_list(expr->func.as_func->arg_list);

        if(far)
            emit_expr_call_far(file, name, args, method, thread, false);
        else if(local)
            emit_expr_call_local(name, args, method, thread, false);
        else if(builtin)
            emit_expr_call_builtin(name, args, method);
    }
}

void compiler::emit_expr_call_pointer(int args, bool builtin, bool method, bool thread, bool child)
{
    std::shared_ptr<instruction> inst;

    if(builtin && !method)
    {
        inst = emit_instruction(opcode::OP_CallBuiltinPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(builtin && !method)
    {
        inst = emit_instruction(opcode::OP_CallBuiltinMethodPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && method && child)
    {
        inst = emit_instruction(opcode::OP_ScriptMethodChildThreadCallPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && method && !child)
    {
        inst = emit_instruction(opcode::OP_ScriptMethodThreadCallPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if (thread && !method && child)
    {
        inst = emit_instruction(opcode::OP_ScriptChildThreadCallPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && !method && !child)
    {
        inst = emit_instruction(opcode::OP_ScriptThreadCallPointer);
        inst->data.push_back(utils::string::va("%d", args));
    } 
    else // no args
    {
        if(method)
            emit_instruction(opcode::OP_ScriptMethodCallPointer);
        else
            emit_instruction(opcode::OP_ScriptFunctionCallPointer);
    }
}

void compiler::emit_expr_call_far(const std::string& file, const std::string& func, int args, bool method, bool thread, bool child)
{
    std::shared_ptr<instruction> inst;

    if(thread && method && child)
    {
        inst = emit_instruction(opcode::OP_ScriptFarMethodChildThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && method && !child)
    {
        inst = emit_instruction(opcode::OP_ScriptFarMethodThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
    }
   else if(thread && !method && child)
    {
        inst = emit_instruction(opcode::OP_ScriptFarChildThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && !method && !child)
    {
        inst = emit_instruction(opcode::OP_ScriptFarThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(!thread && method)
    {
        inst = emit_instruction(opcode::OP_ScriptFarMethodCall);
    }
    else if(!thread && !method && args == 0) // no args
    {
        inst = emit_instruction(opcode::OP_ScriptFarFunctionCall2);
    }
    else if(!thread && !method && args != 0) // args
    {
        inst = emit_instruction(opcode::OP_ScriptFarFunctionCall);
    }

    inst->data.push_back(file);
    inst->data.push_back(func);
}

void compiler::emit_expr_call_local(const std::string& func, int args, bool method, bool thread, bool child)
{
    std::shared_ptr<instruction> inst;

    if(thread && method && child)
    {
        inst = emit_instruction(opcode::OP_ScriptLocalMethodChildThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && method && !child)
    {
        inst = emit_instruction(opcode::OP_ScriptLocalMethodThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
    }
   else if(thread && !method && child)
    {
        inst = emit_instruction(opcode::OP_ScriptLocalChildThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && !method && !child)
    {
        inst = emit_instruction(opcode::OP_ScriptLocalThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(!thread && method)
    {
        inst = emit_instruction(opcode::OP_ScriptLocalMethodCall);
    }
    else if(!thread && !method && args == 0) // no args
    {
        inst = emit_instruction(opcode::OP_ScriptLocalFunctionCall2);
    }
    else if(!thread && !method && args != 0) // args
    {
        inst = emit_instruction(opcode::OP_ScriptLocalFunctionCall);
    }

    inst->data.push_back(func);
}

void compiler::emit_expr_call_builtin(const std::string& func, int args, bool method)
{
    std::shared_ptr<instruction> inst;

    if(method)
    {
        if(args == 0)
            inst = emit_instruction(opcode::OP_CallBuiltinMethod0);
        else if(args == 1)
            inst = emit_instruction(opcode::OP_CallBuiltinMethod1);
         else if(args == 2)
            inst = emit_instruction(opcode::OP_CallBuiltinMethod2);
         else if(args == 3)
            inst = emit_instruction(opcode::OP_CallBuiltinMethod3);
         else if(args == 4)
            inst = emit_instruction(opcode::OP_CallBuiltinMethod4);
         else if(args == 5)
            inst = emit_instruction(opcode::OP_CallBuiltinMethod5);
        else
        {
            inst = emit_instruction(opcode::OP_CallBuiltinMethod);
            inst->data.push_back(utils::string::va("%d", args));
        }
    }
    else
    {
        if(args == 0)
            inst = emit_instruction(opcode::OP_CallBuiltin0);
        else if(args == 1)
            inst = emit_instruction(opcode::OP_CallBuiltin1);
         else if(args == 2)
            inst = emit_instruction(opcode::OP_CallBuiltin2);
         else if(args == 3)
            inst = emit_instruction(opcode::OP_CallBuiltin3);
         else if(args == 4)
            inst = emit_instruction(opcode::OP_CallBuiltin4);
         else if(args == 5)
            inst = emit_instruction(opcode::OP_CallBuiltin5);
        else
        {
            inst = emit_instruction(opcode::OP_CallBuiltin);
            inst->data.push_back(utils::string::va("%d", args));
        }
    }

    inst->data.push_back(func);
}

void compiler::emit_expr_arg_list(const expr_arg_list_ptr& arg_list)
{
    std::reverse(arg_list->args.begin(), arg_list->args.end());

    for(auto& arg : arg_list->args)
    {
        emit_expression(*(expr_ptr*)&arg);
    }
}

void compiler::emit_expr_func_ref(const expr_func_ref_ptr& node)
{
    bool far, local, builtin, method = false;
    auto name = node->func->value;
    auto file = node->file->value;

    if(file != "")
    {
        far = true;
    }
    else if(is_builtin_method(node->func))
    {
        builtin = true;
        method = true;
    }
    else if(is_builtin_func(node->func))
    {
        builtin = true;
    }
    else if(is_local_call(node->func))
    {
        local = true;
    }

    std::shared_ptr<instruction> inst;

    if(local)
    {
        inst = emit_instruction(opcode::OP_GetLocalFunction);
        inst->data.push_back(name);
    }
    else if(far)
    {
        inst = emit_instruction(opcode::OP_GetFarFunction);
        inst->data.push_back(file);
        inst->data.push_back(name);
    }
    else if(builtin && method)
    {
        inst = emit_instruction(opcode::OP_GetBuiltinMethod);
        inst->data.push_back(name);
    }
    else if(builtin && !method)
    {
        inst = emit_instruction(opcode::OP_GetBuiltinFunction);
        inst->data.push_back(name);
    }
}

void compiler::emit_expr_ref(const expr_ptr& expr, bool set)
{
    if(expr.as_node->type == node_type::expr_subscribe)
    {
        emit_expr_subscribe_ref(expr.as_expr_subscribe, set);
    }
    else if(expr.as_node->type == node_type::expr_select)
    {
        emit_expr_select_ref(expr.as_expr_select, set);
    }
    else if(expr.as_node->type == node_type::identifier)
    {
        emit_expr_variable_ref(expr.as_identifier, set);
    }
    else
    {
        LOG_ERROR("ERROR: variable ref type.");
    }
}

void compiler::emit_expr_subscribe_ref(const expr_subscribe_ptr& expr, bool set)
{
    emit_expression(*(expr_ptr*)&expr->key);

    if(expr->obj->type == node_type::expr_call)
    {
        LOG_ERROR("call result can't be referenced");
    }
    else if(expr->obj->type == node_type::game)
    {
        emit_instruction(opcode::OP_GetGameRef);
        emit_instruction(opcode::OP_EvalArrayRef);
        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
    else if(expr->obj->type == node_type::expr_subscribe
            || expr->obj->type == node_type::expr_select)
    {
        emit_expr_variable_ref(*(identifier_ptr*)&expr->obj, false);
        emit_instruction(opcode::OP_EvalArrayRef);
        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
    else // local var
    {
        // OP_EvalLocalArrayRefCached0: for new array??
	    // OP_EvalLocalArrayRefCached: alredy created??
        // OP_EvalNewLocalArrayRefCached0: add new array index?
        auto index = get_local_var_index(expr->obj);
        auto inst = emit_instruction(opcode::OP_EvalLocalArrayRefCached);
        inst->data.push_back(utils::string::va("%d", index));
    
        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
}

void compiler::emit_expr_select_ref(const expr_select_ptr&  expr, bool set)
{
    if(expr->field->type ==  node_type::size)
    {
        LOG_ERROR("size field can't be referenced");
        return;
    }

    auto field = ((node_identifier*)expr->field.get())->value;

    if(expr->obj->type == node_type::level)
    {
        if(set)
        {
            auto inst = emit_instruction(opcode::OP_SetLevelFieldVariableField);
            inst->data.push_back(field);
        }
        else
        {
            auto inst = emit_instruction(opcode::OP_EvalLevelFieldVariableRef);
            inst->data.push_back(field);
        } 
    }
    else if(expr->obj->type == node_type::anim)
    {
        if(set)
        {
            auto inst = emit_instruction(opcode::OP_SetAnimFieldVariableField);
            inst->data.push_back(field);
        }
        else
        {
            auto inst = emit_instruction(opcode::OP_EvalAnimFieldVariableRef);
            inst->data.push_back(field);
        } 
    }
    else if(expr->obj->type == node_type::self)
    {
        if(set)
        {
            auto inst = emit_instruction(opcode::OP_SetSelfFieldVariableField);
            inst->data.push_back(field);
        }
        else
        {
            auto inst = emit_instruction(opcode::OP_EvalSelfFieldVariableRef);
            inst->data.push_back(field);
        } 
    }
    else if(expr->obj->type == node_type::expr_subscribe)
    {
        emit_expr_subscribe_ref(*(expr_subscribe_ptr*)&expr->obj, false);
        emit_instruction(opcode::OP_CastFieldObject);
        auto inst = emit_instruction(opcode::OP_EvalFieldVariableRef);
        inst->data.push_back(field);
        
        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
    else if(expr->obj->type == node_type::expr_call)
    {
        LOG_ERROR("function call result can't be referenced");
        return;
    }
    else // local variable identifier
    {
        auto index = get_local_var_index(expr->obj);
        auto inst = emit_instruction(opcode::OP_EvalLocalVariableObjectCached);
        inst->data.push_back(utils::string::va("%d", index));

        inst = emit_instruction(opcode::OP_EvalFieldVariableRef);
        inst->data.push_back(field);

        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
}

void compiler::emit_expr_variable_ref(const identifier_ptr& expr, bool set)
{
        // local var

        // if no exist, create
}

void compiler::emit_expr_subscribe(const expr_subscribe_ptr& expr)
{
    //TODO: eval arrays
}

void compiler::emit_expr_select(const expr_select_ptr& expr)
{
    // TODO: eval fields

    /*if(expr->field->type ==  node_type::size)
    {
        // emit_variable(expr->obj)
        emit_instruction(opcode::OP_size);
    }*/

    // emit_instruction(opcode::OP_EvalSelfFieldVariable);
    // emit_instruction(opcode::OP_EvalLevelFieldVariable);
    // emit_instruction(opcode::OP_EvalAnimFieldVariable);
}

void compiler::emit_expr_variable(const identifier_ptr& expr)
{
    // TODO: eval variables
}

void compiler::emit_vector(const vector_ptr& vec)
{
    auto inst = emit_instruction(opcode::OP_GetVector);

    if(vec->x->type == node_type::integer)
        inst->data.push_back(static_cast<node_integer*>(vec->x.get())->value);
    else if(vec->x->type == node_type::float_)
        inst->data.push_back(static_cast<node_float*>(vec->x.get())->value);
    
    if(vec->y->type == node_type::integer)
        inst->data.push_back(static_cast<node_integer*>(vec->y.get())->value);
    else if(vec->y->type == node_type::float_)
        inst->data.push_back(static_cast<node_float*>(vec->y.get())->value);
    
    if(vec->z->type == node_type::integer)
        inst->data.push_back(static_cast<node_integer*>(vec->z.get())->value);
    else if(vec->z->type == node_type::float_)
        inst->data.push_back(static_cast<node_float*>(vec->z.get())->value);
}

void compiler::emit_float(const float_ptr& num)
{
    auto inst = emit_instruction(opcode::OP_GetFloat);
    inst->data.push_back(num->value);
}

void compiler::emit_integer(const integer_ptr& num)
{
    std::int32_t value = std::atol(num->value.data());

    if(value == 0)
    {
        auto inst = emit_instruction(opcode::OP_GetZero);
    }
    else if(value > 0 && value < 255)
    {
        auto inst = emit_instruction(opcode::OP_GetByte);
        inst->data.push_back(num->value);
    }
    else if(value < 0 && value >= -256)
    {
        auto inst = emit_instruction(opcode::OP_GetNegByte);
        inst->data.push_back(num->value);
    }
    else if(value < 65535)
    {
        auto inst = emit_instruction(opcode::OP_GetUnsignedShort);
        inst->data.push_back(num->value);
    }
    else if(value < 0 && value >= -65536)
    {
        auto inst = emit_instruction(opcode::OP_GetNegUnsignedShort);
        inst->data.push_back(num->value);
    }
    else
    {
        auto inst = emit_instruction(opcode::OP_GetInteger);
        inst->data.push_back(num->value);
    } 
}

void compiler::emit_string_loc(const string_loc_ptr& str)
{
    auto inst = emit_instruction(opcode::OP_GetIString);
    inst->data.push_back(str->value);
}

void compiler::emit_string(const string_ptr& str)
{
    auto inst = emit_instruction(opcode::OP_GetString);
    inst->data.push_back(str->value);
}

auto compiler::emit_instruction(opcode op) -> std::shared_ptr<instruction>
{
    auto inst = std::make_shared<instruction>();
    inst->opcode = static_cast<std::uint8_t>(op);
    inst->size = opcode_size(op);
    inst->parent = function_;
    inst->index = index_;

    index_ += inst->size;
    function_->instructions.push_back(inst);

    return inst;
}

auto compiler::get_local_var_index(const node_ptr& var) -> std::uint8_t
{
    if(var->type != node_type::identifier)
        return 0xFF;
    
    auto name = (*(identifier_ptr*)&var)->value;
    int i = 0;

    for(const auto& var : local_vars)
    {
        if(var == name) return i;
        i++;
    }

    return 0xFF;
}

auto compiler::is_parameter_var(const node_ptr& var) -> bool
{
    if(var->type != node_type::identifier)
        return false;
    
    auto name = (*(identifier_ptr*)&var)->value;
    
    for(const auto& var : param_vars)
    {
        if(var == name)
            return true;
    }

    return false;
}

auto compiler::is_local_var(const identifier_ptr& var) -> bool
{
    auto name = var->value;

    for(const auto& var : local_vars)
    {
        if(var == name)
            return true;
    }

    return false;
}

auto compiler::is_local_call(const identifier_ptr& func) -> bool
{
    auto name = func->value;

    for(const auto& f : local_functions_)
    {
        if(f == name)
            return true;
    }

    return false;
}

auto compiler::is_builtin_call(const identifier_ptr& func) -> bool
{
    if(is_builtin_func(func))
        return true;
    
    if(is_builtin_method(func))
        return true;

    return false;
}

auto compiler::is_builtin_func(const identifier_ptr& func) -> bool
{
    auto name = func->value;

    auto res = resolver::builtin_func_id(name);
    if(res != 0xFFFF) return true;

    return false;
}
auto compiler::is_builtin_method(const identifier_ptr& func) -> bool
{
    auto name = func->value;

    auto res = resolver::builtin_method_id(name);
    if(res != 0xFFFF) return true;

    return false;
}

} // namespace IW6
