// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW6.hpp"
#include "compiler_parser.hpp"
#include "compiler_lexer.hpp"

namespace IW6
{

auto compiler::output() -> std::vector<gsc::function_ptr>
{
    return std::move(assembly_);
}

void compiler::compile(std::string& data)
{
    auto result = parse_buffer(data);

    compile_script(result);
}

auto compiler::parse_buffer(std::string& data) -> gsc::script_ptr
{
    yyscan_t scanner;
    gsc::script_ptr result(nullptr);
    
    // Add the two NULL terminators, required by flex.   
    data.append("\0\0", 2);

    if (yylex_init(&scanner))
        exit(1);

    YY_BUFFER_STATE yybuffer = yy_scan_buffer(data.data(), data.size(), scanner);

    yy::parser parser(scanner, result);
    
    if(parser.parse() || result == nullptr)
    {
        LOG_ERROR("An error ocurred while parsing file.");
    }

    yy_delete_buffer(yybuffer, scanner);
    yylex_destroy(scanner);

    return result;
}

auto compiler::parse_file(const std::string& file) -> gsc::script_ptr
{
    auto buffer = utils::file::read(file);
    auto result = parse_buffer(buffer);

    return result;
}

void compiler::compile_script(const gsc::script_ptr& script)
{
    index_ = 1; // skip magic

    for(const auto& thread : script->threads)
    {
        local_functions_.push_back(thread->name->value);
    }

    for(const auto& include : script->includes)
    {
        emit_include(include);
    }

    for(const auto& animtree : script->animtrees)
    {
        emit_using_animtree(animtree);  
    }

    for(const auto& thread : script->threads)
    {
        emit_thread(thread);
    }

    LOG_DEBUG("----------------------------------");
    LOG_DEBUG("files included: %zu", includes_.size());
    LOG_DEBUG("animtrees used: %zu", animtrees_.size());
    LOG_DEBUG("functions compiled: %zu",assembly_.size());
}

void compiler::emit_include(const gsc::include_ptr& include)
{
    includes_.push_back(include->file->value);
    // need to parse the included file here, and make a vector with all function names
    // later assemble calls check if far call
    // ...
}

void compiler::emit_using_animtree(const gsc::using_animtree_ptr& animtree)
{
    animtrees_.push_back(animtree->animtree->value);
}

void compiler::emit_thread(const gsc::thread_ptr& func)
{
    function_ = std::make_unique<gsc::function>();
    function_->index = index_;
    local_vars_.clear();
    param_vars_.clear();
    blocks_.clear();

    function_->name = func->name->value;
    
    emit_parameters(func->params);
    emit_block(func->block);
    emit_instruction(opcode::OP_End);

    LOG_DEBUG("function '%s' with %zu instructions.",function_->name.data(), function_->instructions.size());

    function_->size = index_ - function_->index;
    assembly_.push_back(std::move(function_));
}

void compiler::emit_parameters(const gsc::parameters_ptr& params)
{
    for(auto& param : params->list)
    {
        auto& inst = emit_instruction(opcode::OP_SafeCreateVariableFieldCached);
        inst->data.push_back(utils::string::va("%d", local_vars_.size()));
        local_vars_.insert(local_vars_.begin(), param->value);      
    }

    emit_instruction(opcode::OP_checkclearparams);
}

void compiler::emit_block(const gsc::block_ptr& block)
{
    for(const auto& stmt : block->stmts)
    {
        emit_statement(stmt);
    }
}

void compiler::emit_statement(const gsc::stmt_ptr& stmt)
{
    switch(stmt.as_node->type)
    {
        case gsc::node_type::stmt_call:
            emit_statement_call(stmt.as_call);
            break;
        case gsc::node_type::stmt_assign:
            emit_statement_assign(stmt.as_assign);
            break;
        case gsc::node_type::stmt_endon:
            emit_statement_endon(stmt.as_endon);
            break;
        case gsc::node_type::stmt_notify:
            emit_statement_notify(stmt.as_notify);
            break;
        case gsc::node_type::stmt_wait:
            emit_statement_wait(stmt.as_wait);
            break;
        case gsc::node_type::stmt_waittill:
            emit_statement_waittill(stmt.as_waittill);
            break;
        case gsc::node_type::stmt_waittillmatch:
            emit_statement_waittillmatch(stmt.as_waittillmatch);
            break;
        case gsc::node_type::stmt_waittillframeend:
            emit_statement_waittillframeend(stmt.as_waittillframeend);
            break;
        case gsc::node_type::stmt_if:
            emit_statement_if(stmt.as_if);
            break;
        case gsc::node_type::stmt_ifelse:
            emit_statement_ifelse(stmt.as_ifelse);
            break;
        case gsc::node_type::stmt_while:
            emit_statement_while(stmt.as_while);
            break;
        case gsc::node_type::stmt_for:
            emit_statement_for(stmt.as_for);
            break;
        case gsc::node_type::stmt_foreach:
            emit_statement_foreach(stmt.as_foreach);
            break;
        case gsc::node_type::stmt_switch:
            emit_statement_switch(stmt.as_switch);
            break;
        case gsc::node_type::stmt_case:
            emit_statement_case(stmt.as_case);
            break;
        case gsc::node_type::stmt_default:
            emit_statement_default(stmt.as_default);
            break;
        case gsc::node_type::stmt_break:
            emit_statement_break(stmt.as_break);
            break;
        case gsc::node_type::stmt_continue:
            emit_statement_continue(stmt.as_continue);
            break;
        case gsc::node_type::stmt_return:
            emit_statement_return(stmt.as_return);
            break;
        default:
            LOG_ERROR("UNKNOWN STATEMENT!");
            break;
    }
}

void compiler::emit_statement_call(const gsc::stmt_call_ptr& stmt)
{
    emit_expr_call(stmt->expr);
    emit_instruction(opcode::OP_DecTop);
}

void compiler::emit_statement_assign(const gsc::stmt_assign_ptr& stmt)
{
    emit_expr_assign(stmt->expr);
}

void compiler::emit_statement_endon(const gsc::stmt_endon_ptr& stmt)
{
    emit_expression(stmt->expr);
    emit_expression(stmt->obj);
    emit_instruction(opcode::OP_endon);
}

void compiler::emit_statement_notify(const gsc::stmt_notify_ptr& stmt)
{
    emit_instruction(opcode::OP_voidCodepos);
    
    std::reverse(stmt->args->list.begin(), stmt->args->list.end());
    
    for(const auto& arg : stmt->args->list)
    {
        emit_expression(arg);
    }

    emit_expression(stmt->expr);
    emit_expression(stmt->obj);
    emit_instruction(opcode::OP_notify);
}

void compiler::emit_statement_wait(const gsc::stmt_wait_ptr& stmt)
{
    emit_expression(stmt->expr);
    emit_instruction(opcode::OP_wait);
}

void compiler::emit_statement_waittill(const gsc::stmt_waittill_ptr& stmt)
{
    emit_expression(stmt->expr);
    emit_expression(stmt->obj);
    emit_instruction(opcode::OP_waittill);

    std::reverse(stmt->args->list.begin(), stmt->args->list.end()); // needed?
    
    for(const auto& arg : stmt->args->list)
    {
        // TODO: move this code to create variable function, 
        // if this is inside a for loop, variable is created outside too. (create_local_variable 0)
        local_vars_.insert(local_vars_.begin(), arg.as_identifier->value);
        auto index = local_vars_.size() - 1;
        auto& inst = emit_instruction(opcode::OP_SafeSetWaittillVariableFieldCached);
        inst->data.push_back(utils::string::va("%d", index));
    }

    emit_instruction(opcode::OP_clearparams);
}

void compiler::emit_statement_waittillmatch(const gsc::stmt_waittillmatch_ptr& stmt)
{
    emit_expression(stmt->rexpr);
    emit_expression(stmt->lexpr);
    emit_expression(stmt->obj);
    emit_instruction(opcode::OP_waittillmatch);
    emit_instruction(opcode::OP_clearparams);
}

void compiler::emit_statement_waittillframeend(const gsc::stmt_waittillframeend_ptr& stmt)
{
    emit_instruction(opcode::OP_waittillFrameEnd);
}

void compiler::emit_statement_if(const gsc::stmt_if_ptr& stmt)
{
    // need bool isLastStatement ?
    auto out_loc = create_label();

    if(stmt->expr.as_node->type == gsc::node_type::expr_not)
    {
        emit_expression(stmt->expr.as_not->rvalue);
        auto& inst = emit_instruction(opcode::OP_JumpOnTrue);
        inst->data.push_back(out_loc);
    }
    else
    {
        emit_expression(stmt->expr);
        auto& inst = emit_instruction(opcode::OP_JumpOnFalse);
        inst->data.push_back(out_loc);
    }
    
    emit_block(stmt->block);
    
    // if lastStatement -> emit end, else emit remove local variables

    insert_label(out_loc);
}

void compiler::emit_statement_ifelse(const gsc::stmt_ifelse_ptr& stmt)
{
    // need bool isLastStatement ?
    auto else_loc = create_label();
    auto out_loc = create_label();

    if(stmt->expr.as_node->type == gsc::node_type::expr_not)
    {
        emit_expression(stmt->expr.as_not->rvalue);
        auto& inst = emit_instruction(opcode::OP_JumpOnTrue);
        inst->data.push_back(else_loc);
    }
    else
    {
        emit_expression(stmt->expr);
        auto& inst = emit_instruction(opcode::OP_JumpOnFalse);
        inst->data.push_back(else_loc);
    }
    
    emit_block(stmt->block_if);
    
    // emit remove local vars
    // if lastStatement -> emit end, else emit OP_jump to out
    // ...

    auto& jmp = emit_instruction(opcode::OP_jump);
    jmp->data.push_back(out_loc);

    insert_label(else_loc);

    emit_block(stmt->block_else);

    // if lastStatement -> emit end, else removelocalvars
    //...

    insert_label(out_loc);
}

void compiler::emit_statement_while(const gsc::stmt_while_ptr& stmt)
{
    // set can break, can continue

    // emit create local variables!
    auto cont_loc = create_label();
    auto end_loc = create_label();
    
    auto begin_loc = insert_label();
    emit_expression(stmt->expr);    // TODO: check if constant condition
    auto& jmpout = emit_instruction(opcode::OP_JumpOnFalse);
    jmpout->data.push_back(end_loc);

    // emit block
    emit_block(stmt->block);
    
    // jump back to begin
    insert_label(cont_loc);
    auto& jmpback = emit_instruction(opcode::OP_jumpback);
    jmpback->data.push_back(begin_loc);
    
    // end
    insert_label(end_loc);
}

void compiler::emit_statement_for(const gsc::stmt_for_ptr& stmt)
{
    // set can break, can continue

    // -------------------------------------
    // emit create local variables!
    //emit precond

    //emit condition + label loop begin

    // emit block

    // emit post cond
    // jumpback loop begin
    // label loop out ( for break stmt )
}

void compiler::emit_statement_foreach(const gsc::stmt_foreach_ptr& stmt)
{
    // set can break, can continue???
}

void compiler::emit_statement_switch(const gsc::stmt_switch_ptr& stmt)
{
    // set can break.

    // emit expression
    // emit switch + label to jumptable

    // emit case blocks + label
    // ...

    // emit enswitxh jumptable
    // case x jump case block label
}

void compiler::emit_statement_case(const gsc::stmt_case_ptr& stmt)
{
    // in switch?
}

void compiler::emit_statement_default(const gsc::stmt_default_ptr& stmt)
{
    // in switch?
}

void compiler::emit_statement_break(const gsc::stmt_break_ptr& stmt)
{
    // can break?

    // remove_localvariables of current block
    // emit OP_jump location (loop end out )
}

void compiler::emit_statement_continue(const gsc::stmt_continue_ptr& stmt)
{
    // can continue?

    // remove_localvariables of current block
    // emit OP_jump location (loop begin )
}

void compiler::emit_statement_return(const gsc::stmt_return_ptr& stmt)
{
    if(stmt->expr.as_node->type != gsc::node_type::null)
    {
        emit_expression(stmt->expr);
        emit_instruction(opcode::OP_Return);
        return; 
    }
    
    emit_instruction(opcode::OP_End);
}

void compiler::emit_expression(const gsc::expr_ptr& expr)
{
    switch(expr.as_node->type)
    {
        case gsc::node_type::expr_ternary:
            emit_expr_ternary(expr.as_ternary);
            break;
        case gsc::node_type::expr_and:
            emit_expr_and(expr.as_and);
            break;
        case gsc::node_type::expr_or:
            emit_expr_or(expr.as_or);
            break;
        case gsc::node_type::expr_equality:
        case gsc::node_type::expr_inequality:
        case gsc::node_type::expr_less:
        case gsc::node_type::expr_greater:
        case gsc::node_type::expr_less_equal:
        case gsc::node_type::expr_greater_equal:
        case gsc::node_type::expr_bitwise_or:
        case gsc::node_type::expr_bitwise_and:
        case gsc::node_type::expr_bitwise_exor:
        case gsc::node_type::expr_shift_left:
        case gsc::node_type::expr_shift_right:
        case gsc::node_type::expr_add:
        case gsc::node_type::expr_sub:
        case gsc::node_type::expr_mult:
        case gsc::node_type::expr_div:
        case gsc::node_type::expr_mod:
            emit_expr_binary(expr.as_binary);
            break;
        case gsc::node_type::expr_complement:
            emit_expr_complement(expr.as_complement);
            break;
        case gsc::node_type::expr_not:
            emit_expr_not(expr.as_not);
            break;
        case gsc::node_type::expr_call:
            emit_expr_call(expr.as_call);
            break;
        case gsc::node_type::expr_array:
            emit_array_variable(expr.as_array);
            break;
        case gsc::node_type::expr_field:
            emit_field_variable(expr.as_field);
            break;
        case gsc::node_type::expr_size:
            emit_size(expr.as_size_expr);
            break;
        case gsc::node_type::expr_function_ref:
            emit_expr_function_ref(expr.as_function_ref);
            break;
        case gsc::node_type::empty_array:
            emit_instruction(opcode::OP_EmptyArray);
            break;
        case gsc::node_type::undefined:
            emit_instruction(opcode::OP_GetUndefined);
            break;
       case gsc::node_type::level:
            emit_instruction(opcode::OP_GetLevel);
            break;
        case gsc::node_type::anim:
            emit_instruction(opcode::OP_GetAnim);
            break;
        case gsc::node_type::self:
            emit_instruction(opcode::OP_GetSelf);
            break;
        case gsc::node_type::game:
            emit_instruction(opcode::OP_GetGame);
            break;
        case gsc::node_type::identifier:
            emit_local_variable(expr.as_identifier);
            break;
        case gsc::node_type::data_string:
            emit_string(expr.as_string);
            break;
        case gsc::node_type::data_localized_string:
            emit_localized_string(expr.as_localized_string);
            break;
        case gsc::node_type::data_float:
            emit_float(expr.as_float);
            break;
        case gsc::node_type::data_integer:
            emit_integer(expr.as_integer);
            break;
        case gsc::node_type::data_vector:
            emit_vector(expr.as_vector);
            break;
        case gsc::node_type::expr_vector:
            emit_expr_vector(expr.as_vector_expr);
            break;
    }
}

void compiler::emit_expr_assign(const gsc::expr_assign_ptr& expr)	
{
    if(expr->type == gsc::node_type::expr_increment)
    {
        emit_expression(expr->lvalue);
        emit_instruction(opcode::OP_inc);
        emit_instruction(opcode::OP_SetVariableField);
    }
    else if(expr->type == gsc::node_type::expr_decrement)
    {
        emit_expression(expr->lvalue);
        emit_instruction(opcode::OP_dec);
        emit_instruction(opcode::OP_SetVariableField);
    }
    else if(expr->type == gsc::node_type::expr_assign_equal)
    {
        if(expr->rvalue.as_node->type == gsc::node_type::undefined) // ClearVariable
        {
            if(expr->lvalue.as_node->type == gsc::node_type::expr_array) // CLEAR ARRAY
            {
                emit_expression(expr->lvalue.as_array->key);
                // emit game_ref or eval array_ref
                //emit_expr_ref(*(expr_ptr*)&((*(expr_subscribe_ptr*)&expr->lvalue)->obj), false);
                emit_instruction(opcode::OP_ClearArray);
            }
            else if(expr->lvalue.as_node->type == gsc::node_type::expr_field) // CLEAR FIELD
            {
                // TODO: size cant be cleared!!
                auto field = expr->lvalue.as_field->field->value;
                emit_object(expr->lvalue.as_field->obj);
                auto& inst = emit_instruction(opcode::OP_ClearFieldVariable);
                inst->data.push_back(field);
            }
            else // is a local var, use OP_Get_undefined ?? 
            {
                // this 2 opcodes are always after for/foreach loops !!!
                //OP_ClearLocalVariableFieldCached0 = 0x30,
	            //OP_ClearLocalVariableFieldCached = 0x31,
                emit_expression(expr->rvalue);
                emit_variable_ref(expr->lvalue, true);
            } 
        }
        else
        {
            emit_expression(expr->rvalue);
            emit_variable_ref(expr->lvalue, true);
        }
    }
    else
    {
        emit_expression(expr->lvalue);
        emit_expression(expr->rvalue);

        switch(expr->type)
        {
            case gsc::node_type::expr_assign_add:
                emit_instruction(opcode::OP_plus);
                break;
            case gsc::node_type::expr_assign_sub:
                emit_instruction(opcode::OP_minus);
                break;
            case gsc::node_type::expr_assign_mult:
                emit_instruction(opcode::OP_multiply);
                break;
            case gsc::node_type::expr_assign_div:
                emit_instruction(opcode::OP_divide);
                break;
            case gsc::node_type::expr_assign_mod:
                emit_instruction(opcode::OP_mod);
                break;
            case gsc::node_type::expr_assign_shift_left:
                emit_instruction(opcode::OP_shift_left);
                break;
            case gsc::node_type::expr_assign_shift_right:
                emit_instruction(opcode::OP_shift_right);
                break;
            case gsc::node_type::expr_assign_bitwise_or:
                emit_instruction(opcode::OP_bit_or);
                break;
            case gsc::node_type::expr_assign_bitwise_and:
                emit_instruction(opcode::OP_bit_and);
                break;
            case gsc::node_type::expr_assign_bitwise_exor:
                emit_instruction(opcode::OP_bit_ex_or);
                break;
            default:
                LOG_ERROR("unknown assignment operation!");
                break;
        }

        emit_variable_ref(expr->lvalue, true);
    }  
}

void compiler::emit_expr_ternary(const gsc::expr_ternary_ptr& expr)
{
    LOG_ERROR("EXPR TERNARY NOT IMPLEMENTED!");
}

void compiler::emit_expr_binary(const gsc::expr_binary_ptr& expr)
{
    emit_expression(expr->lvalue);
    emit_expression(expr->rvalue);

    switch(expr->type)
    {
        case gsc::node_type::expr_equality:
            emit_instruction(opcode::OP_equality);
            break;
        case gsc::node_type::expr_inequality:
            emit_instruction(opcode::OP_inequality);
            break;
        case gsc::node_type::expr_less:
            emit_instruction(opcode::OP_less);
            break;
        case gsc::node_type::expr_greater:
            emit_instruction(opcode::OP_greater);
            break;
        case gsc::node_type::expr_less_equal:
            emit_instruction(opcode::OP_less_equal);
            break;
        case gsc::node_type::expr_greater_equal:
            emit_instruction(opcode::OP_greater_equal);
            break;
        case gsc::node_type::expr_bitwise_or:
            emit_instruction(opcode::OP_bit_or);
            break;
        case gsc::node_type::expr_bitwise_and:
            emit_instruction(opcode::OP_bit_and);
            break;
        case gsc::node_type::expr_bitwise_exor:
            emit_instruction(opcode::OP_bit_ex_or);
            break;
        case gsc::node_type::expr_shift_left:
            emit_instruction(opcode::OP_shift_left);
            break;
        case gsc::node_type::expr_shift_right:
            emit_instruction(opcode::OP_shift_right);
            break;
        case gsc::node_type::expr_add:
            emit_instruction(opcode::OP_plus);
            break;
        case gsc::node_type::expr_sub:
            emit_instruction(opcode::OP_minus);
            break;
        case gsc::node_type::expr_mult:
            emit_instruction(opcode::OP_multiply);
            break;
        case gsc::node_type::expr_div:
            emit_instruction(opcode::OP_divide);
            break;
        case gsc::node_type::expr_mod:
            emit_instruction(opcode::OP_mod);
            break;
    }
}

void compiler::emit_expr_and(const gsc::expr_and_ptr& expr)
{
    emit_expression(expr->lvalue);
    auto& inst = emit_instruction(opcode::OP_JumpOnFalseExpr);

    emit_expression(expr->rvalue);
    emit_instruction(opcode::OP_CastBool);

    auto label = insert_label(); // jumpOnFalseExpr here
    inst->data.push_back(label);
}

void compiler::emit_expr_or(const gsc::expr_or_ptr& expr)
{
    emit_expression(expr->lvalue);
    auto& inst = emit_instruction(opcode::OP_JumpOnTrueExpr);

    emit_expression(expr->rvalue);
    emit_instruction(opcode::OP_CastBool);

    auto label = insert_label(); // jumpOnTrueExpr here
    inst->data.push_back(label);
}

void compiler::emit_expr_complement(const gsc::expr_complement_ptr& expr)
{
    emit_expression(expr->rvalue);
    emit_instruction(opcode::OP_BoolComplement);
}

void compiler::emit_expr_not(const gsc::expr_not_ptr& expr)
{
    emit_expression(expr->rvalue);
    emit_instruction(opcode::OP_BoolNot);
}

void compiler::emit_expr_call(const gsc::expr_call_ptr& expr)
{
    bool thread, method, builtin, far, local = false;
    std::string file, name;
    std::uint32_t args = 0;

    thread = expr->thread;

    if(expr->obj.as_node->type != gsc::node_type::null)
    {
        method = true;
    }

    if(expr->func.as_node->type == gsc::node_type::expr_call_pointer)
    {
        builtin = expr->func.as_pointer->builtin;
        
        args = expr->func.as_pointer->args->list.size();
        
        if(!thread && !builtin)
            emit_instruction(opcode::OP_PreScriptCall);
  
        emit_expr_arguments(expr->func.as_pointer->args);

        if(method)
            emit_expression(expr->obj);

        emit_expression(expr->func.as_pointer->expr);
        emit_expr_call_pointer(args, builtin, method, thread, false);
    }
    else
    {
        args = expr->func.as_func->args->list.size();
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

        emit_expr_arguments(expr->func.as_func->args);

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
    if(builtin && !method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltinPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(builtin && !method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltinMethodPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && method && child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptMethodChildThreadCallPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && method && !child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptMethodThreadCallPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if (thread && !method && child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptChildThreadCallPointer);
        inst->data.push_back(utils::string::va("%d", args));
    }
    else if(thread && !method && !child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptThreadCallPointer);
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
    if(thread && method && child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptFarMethodChildThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(file);
        inst->data.push_back(func);
    }
    else if(thread && method && !child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptFarMethodThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(file);
        inst->data.push_back(func);
    }
   else if(thread && !method && child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptFarChildThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(file);
        inst->data.push_back(func);
    }
    else if(thread && !method && !child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptFarThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(file);
        inst->data.push_back(func);
    }
    else if(!thread && method)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptFarMethodCall);
        inst->data.push_back(file);
        inst->data.push_back(func);
    }
    else if(!thread && !method && args == 0) // no args
    {
        auto& inst = emit_instruction(opcode::OP_ScriptFarFunctionCall2);
        inst->data.push_back(file);
        inst->data.push_back(func);
    }
    else if(!thread && !method && args != 0) // args
    {
        auto& inst = emit_instruction(opcode::OP_ScriptFarFunctionCall);
        inst->data.push_back(file);
        inst->data.push_back(func);
    }
}

void compiler::emit_expr_call_local(const std::string& func, int args, bool method, bool thread, bool child)
{
    if(thread && method && child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptLocalMethodChildThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(func);
    }
    else if(thread && method && !child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptLocalMethodThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(func);
    }
   else if(thread && !method && child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptLocalChildThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(func);
    }
    else if(thread && !method && !child)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptLocalThreadCall);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(func);
    }
    else if(!thread && method)
    {
        auto& inst = emit_instruction(opcode::OP_ScriptLocalMethodCall);
        inst->data.push_back(func);
    }
    else if(!thread && !method && args == 0) // no args
    {
        auto& inst = emit_instruction(opcode::OP_ScriptLocalFunctionCall2);
        inst->data.push_back(func);
    }
    else if(!thread && !method && args != 0) // args
    {
        auto& inst = emit_instruction(opcode::OP_ScriptLocalFunctionCall);
        inst->data.push_back(func);
    }
}

void compiler::emit_expr_call_builtin(const std::string& func, int args, bool method)
{
    if(args == 0 && method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltinMethod0);
        inst->data.push_back(func);
    }
    else if(args == 0 && !method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltin0);
        inst->data.push_back(func);
    }
    if(args == 1 && method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltinMethod1);
        inst->data.push_back(func);
    }
    else if(args == 1 && !method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltin1);
        inst->data.push_back(func);
    }
    if(args == 2 && method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltinMethod2);
        inst->data.push_back(func);
    }
    else if(args == 2 && !method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltin2);
        inst->data.push_back(func);
    }
    if(args == 3 && method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltinMethod3);
        inst->data.push_back(func);
    }
    else if(args == 3 && !method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltin3);
        inst->data.push_back(func);
    }
    if(args == 4 && method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltinMethod4);
        inst->data.push_back(func);
    }
    else if(args == 4 && !method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltin4);
        inst->data.push_back(func);
    }
    if(args == 5 && method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltinMethod5);
        inst->data.push_back(func);
    }
    else if(args == 5 && !method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltin5);
        inst->data.push_back(func);
    }
    else if(method)
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltinMethod);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(func);
    }
    else
    {
        auto& inst = emit_instruction(opcode::OP_CallBuiltin);
        inst->data.push_back(utils::string::va("%d", args));
        inst->data.push_back(func);
    }
}

void compiler::emit_expr_arguments(const gsc::expr_arguments_ptr& args)
{
    std::reverse(args->list.begin(), args->list.end());

    for(auto& arg : args->list)
    {
        emit_expression(arg);
    }
}

void compiler::emit_expr_function_ref(const gsc::expr_function_ref_ptr& expr)
{
    bool far, local, builtin, method = false;
    auto name = expr->func->value;
    auto file = expr->file->value;

    if(file != "")
    {
        far = true;
    }
    else if(is_builtin_method(expr->func))
    {
        builtin = true;
        method = true;
    }
    else if(is_builtin_func(expr->func))
    {
        builtin = true;
    }
    else if(is_local_call(expr->func))
    {
        local = true;
    }

    if(local)
    {
        auto& inst = emit_instruction(opcode::OP_GetLocalFunction);
        inst->data.push_back(name);
    }
    else if(far)
    {
        auto& inst = emit_instruction(opcode::OP_GetFarFunction);
        inst->data.push_back(file);
        inst->data.push_back(name);
    }
    else if(builtin && method)
    {
        auto& inst = emit_instruction(opcode::OP_GetBuiltinMethod);
        inst->data.push_back(name);
    }
    else if(builtin && !method)
    {
        auto& inst = emit_instruction(opcode::OP_GetBuiltinFunction);
        inst->data.push_back(name);
    }
}

void compiler::emit_size(const gsc::expr_size_ptr& expr)
{
    emit_object(expr->obj);
    emit_instruction(opcode::OP_size);
}

void compiler::emit_variable_ref(const gsc::expr_ptr& expr, bool set)
{
    if(expr.as_node->type == gsc::node_type::expr_array)
    {
        emit_array_variable_ref(expr.as_array, set);
    }
    else if(expr.as_node->type == gsc::node_type::expr_field)
    {
        emit_field_variable_ref(expr.as_field, set);
    }
    else if(expr.as_node->type == gsc::node_type::identifier)
    {
        emit_local_variable_ref(expr.as_identifier, set);
    }
    else
    {
        LOG_ERROR("ERROR: variable ref type.");
    }
}

void compiler::emit_array_variable_ref(const gsc::expr_array_ptr& expr, bool set)
{
    emit_expression(expr->key);

    if(expr->obj.as_node->type == gsc::node_type::expr_call)
    {
        LOG_ERROR("call result can't be referenced");
    }
    else if(expr->obj.as_node->type == gsc::node_type::game)
    {
        emit_instruction(opcode::OP_GetGameRef);
        emit_instruction(opcode::OP_EvalArrayRef);
        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
    else if(expr->obj.as_node->type == gsc::node_type::expr_array
            || expr->obj.as_node->type == gsc::node_type::expr_field)
    {
        emit_variable_ref(expr->obj, false);
        emit_instruction(opcode::OP_EvalArrayRef);
        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
    else // local var
    {
        // OP_EvalNewLocalArrayRefCached0 add new array index? on IW6
        // create a local array and set one of its elements without having to initialize it first
        
        // OP_EvalLocalArrayRefCached0:
        // evaluates the last created local array.

	    // OP_EvalLocalArrayRefCached: evaluate an array by local_variable_index
        auto index = get_local_var_index(expr->obj.as_node);
        auto& inst = emit_instruction(opcode::OP_EvalLocalArrayRefCached);
        inst->data.push_back(utils::string::va("%d", index));
    
        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
}

void compiler::emit_field_variable_ref(const gsc::expr_field_ptr&  expr, bool set)
{
    auto field = expr->field->value;

    if(expr->obj.as_node->type == gsc::node_type::level)
    {
        if(set)
        {
            auto& inst = emit_instruction(opcode::OP_SetLevelFieldVariableField);
            inst->data.push_back(field);
        }
        else
        {
            auto& inst = emit_instruction(opcode::OP_EvalLevelFieldVariableRef);
            inst->data.push_back(field);
        } 
    }
    else if(expr->obj.as_node->type == gsc::node_type::anim)
    {
        if(set)
        {
            auto& inst = emit_instruction(opcode::OP_SetAnimFieldVariableField);
            inst->data.push_back(field);
        }
        else
        {
            auto& inst = emit_instruction(opcode::OP_EvalAnimFieldVariableRef);
            inst->data.push_back(field);
        } 
    }
    else if(expr->obj.as_node->type == gsc::node_type::self)
    {
        if(set)
        {
            auto& inst = emit_instruction(opcode::OP_SetSelfFieldVariableField);
            inst->data.push_back(field);
        }
        else
        {
            auto& inst = emit_instruction(opcode::OP_EvalSelfFieldVariableRef);
            inst->data.push_back(field);
        } 
    }
    else if(expr->obj.as_node->type == gsc::node_type::expr_array)
    {
        emit_array_variable_ref(expr->obj.as_array, false);
        emit_instruction(opcode::OP_CastFieldObject);                  // TODO: ?????????
        auto& inst = emit_instruction(opcode::OP_EvalFieldVariableRef);
        inst->data.push_back(field);
        
        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
    else if(expr->obj.as_node->type == gsc::node_type::expr_call)
    {
        LOG_ERROR("function call result can't be referenced");
        return;
    }
    else // local variable identifier
    {
        auto index = get_local_var_index(expr->obj.as_node);
        auto& inst = emit_instruction(opcode::OP_EvalLocalVariableObjectCached);
        inst->data.push_back(utils::string::va("%d", index));

        auto& inst2 = emit_instruction(opcode::OP_EvalFieldVariableRef);
        inst2->data.push_back(field);

        if(set)
        {
            emit_instruction(opcode::OP_SetVariableField);
        }
    }
}

void compiler::emit_local_variable_ref(const gsc::identifier_ptr& expr, bool set)
{
        // local var

        // no exist?, create

        // OP_SetNewLocalVariableFieldCached0
        // OP_SetLocalVariableFieldCached0 = 0x44,
	    // OP_SetLocalVariableFieldCached = 0x45,
        // OP_EvalNewLocalVariableRefCached0 = 0x7C,
        // OP_CreateLocalVariable
}

void compiler::emit_array_variable(const gsc::expr_array_ptr& expr)
{
    emit_expression(expr->key);

    if(expr->obj.as_node->type == gsc::node_type::identifier) // local array
    {
        auto index = get_local_var_index(expr->obj.as_node);
        auto& inst = emit_instruction(opcode::OP_EvalLocalArrayCached);
        inst->data.push_back(utils::string::va("%d", index));
    }
    else
    {
        emit_expression(expr->obj);
        emit_instruction(opcode::OP_EvalArray);
    }
}

void compiler::emit_field_variable(const gsc::expr_field_ptr& expr)
{
    if(expr->obj.as_node->type ==  gsc::node_type::level)
    {
        auto& inst = emit_instruction(opcode::OP_EvalLevelFieldVariable);
        inst->data.push_back(expr->field->value);
    }
    else if(expr->obj.as_node->type ==  gsc::node_type::anim)
    {
        auto& inst = emit_instruction(opcode::OP_EvalAnimFieldVariable);
        inst->data.push_back(expr->field->value);
    }
    else if(expr->obj.as_node->type ==  gsc::node_type::self)
    {
        auto& inst = emit_instruction(opcode::OP_EvalSelfFieldVariable);
        inst->data.push_back(expr->field->value);
    }
    else
    {
        emit_object(expr->obj);
        auto& inst = emit_instruction(opcode::OP_EvalFieldVariable);
        inst->data.push_back(expr->field->value);
    }
}

void compiler::emit_local_variable(const gsc::identifier_ptr& expr)
{
    auto index = get_local_var_index(*(gsc::node_ptr*)&expr);

    if(index == 0xFF)
    {
        LOG_ERROR("no local var found!");
        return;
    }

    switch(index)
    {
        case 0:
            emit_instruction(opcode::OP_EvalLocalVariableCached0);
            break;
        case 1:
            emit_instruction(opcode::OP_EvalLocalVariableCached1);
            break;
        case 2:
            emit_instruction(opcode::OP_EvalLocalVariableCached2);
            break;
        case 3:
            emit_instruction(opcode::OP_EvalLocalVariableCached3);
            break;
        case 4:
            emit_instruction(opcode::OP_EvalLocalVariableCached4);
            break;
        case 5:
            emit_instruction(opcode::OP_EvalLocalVariableCached5);
            break;
        default:
        {
            auto& inst = emit_instruction(opcode::OP_EvalLocalVariableCached);
            inst->data.push_back(utils::string::va("%d", index));
        }
            break;
    }
}

void compiler::emit_expr_vector(const gsc::expr_vector_ptr& expr)
{
    emit_expression(expr->z);
    emit_expression(expr->y);
    emit_expression(expr->x);
    emit_instruction(opcode::OP_vector);
}

void compiler::emit_expr_add_array(const gsc::expr_add_array_ptr& expr)
{
    if(expr->args->list.size() > 0)
    {
        emit_instruction(opcode::OP_EmptyArray);
        for(auto& arg : expr->args->list)
        {
            emit_expression(arg);
            emit_instruction(opcode::OP_AddArray);
        }
    }
    else
    {
        LOG_ERROR("can't add empty array");
    }
}

void compiler::emit_object(const gsc::expr_ptr& expr)
{
    switch(expr.as_node->type)
    {
        case gsc::node_type::level:
            emit_instruction(opcode::OP_GetLevelObject);
        break;
        case gsc::node_type::anim:
            emit_instruction(opcode::OP_GetAnimObject);
        break;
        case gsc::node_type::self:
            emit_instruction(opcode::OP_GetSelfObject);
        break;
        case gsc::node_type::identifier:
        {
            auto index = get_local_var_index(expr.as_node);
            auto& inst = emit_instruction(opcode::OP_EvalLocalVariableObjectCached);
            inst->data.push_back(utils::string::va("%d", index));
        }
        break;
        case gsc::node_type::expr_call:
        {
            emit_expr_call(expr.as_call);
            emit_instruction(opcode::OP_CastFieldObject);
        }
        break;
        default:
            LOG_ERROR("emit object unkown type.");
        break;
    }
}

void compiler::emit_vector(const gsc::vector_ptr& vec)
{
    auto& inst = emit_instruction(opcode::OP_GetVector);

    if(vec->x->type == gsc::node_type::data_integer)
        inst->data.push_back(static_cast<gsc::node_integer*>(vec->x.get())->value);
    else if(vec->x->type == gsc::node_type::data_float)
        inst->data.push_back(static_cast<gsc::node_float*>(vec->x.get())->value);
    
    if(vec->y->type == gsc::node_type::data_integer)
        inst->data.push_back(static_cast<gsc::node_integer*>(vec->y.get())->value);
    else if(vec->y->type == gsc::node_type::data_float)
        inst->data.push_back(static_cast<gsc::node_float*>(vec->y.get())->value);
    
    if(vec->z->type == gsc::node_type::data_integer)
        inst->data.push_back(static_cast<gsc::node_integer*>(vec->z.get())->value);
    else if(vec->z->type == gsc::node_type::data_float)
        inst->data.push_back(static_cast<gsc::node_float*>(vec->z.get())->value);
}

void compiler::emit_float(const gsc::float_ptr& num)
{
    auto& inst = emit_instruction(opcode::OP_GetFloat);
    inst->data.push_back(num->value);
}

void compiler::emit_integer(const gsc::integer_ptr& num)
{
    std::int32_t value = std::atol(num->value.data());

    if(value == 0)
    {
        emit_instruction(opcode::OP_GetZero);
    }
    else if(value > 0 && value < 255)
    {
        auto& inst = emit_instruction(opcode::OP_GetByte);
        inst->data.push_back(num->value);
    }
    else if(value < 0 && value >= -256)
    {
        auto& inst = emit_instruction(opcode::OP_GetNegByte);
        inst->data.push_back(num->value);
    }
    else if(value < 65535)
    {
        auto& inst = emit_instruction(opcode::OP_GetUnsignedShort);
        inst->data.push_back(num->value);
    }
    else if(value < 0 && value >= -65536)
    {
        auto& inst = emit_instruction(opcode::OP_GetNegUnsignedShort);
        inst->data.push_back(num->value);
    }
    else
    {
        auto& inst = emit_instruction(opcode::OP_GetInteger);
        inst->data.push_back(num->value);
    } 
}

void compiler::emit_localized_string(const gsc::localized_string_ptr& str)
{
    auto& inst = emit_instruction(opcode::OP_GetIString);
    inst->data.push_back(str->value);
}

void compiler::emit_string(const gsc::string_ptr& str)
{
    auto& inst = emit_instruction(opcode::OP_GetString);
    inst->data.push_back(str->value);
}

auto compiler::emit_instruction(opcode op) -> const gsc::instruction_ptr&
{
    function_->instructions.push_back(std::make_unique<gsc::instruction>());
    
    auto& inst = function_->instructions.back();
    inst->opcode = static_cast<std::uint8_t>(op);
    inst->size = opcode_size(op);
    inst->index = index_;

    index_ += inst->size;

    return inst;
}

auto compiler::get_local_var_index(const gsc::node_ptr& var) -> std::uint8_t
{
    if(var->type != gsc::node_type::identifier)
        return 0xFF;
    
    auto name = (*(gsc::identifier_ptr*)&var)->value;
    int i = 0;

    for(const auto& var : local_vars_)
    {
        if(var == name) return i;
        i++;
    }

    return 0xFF;
}

auto compiler::is_parameter_var(const gsc::node_ptr& var) -> bool
{
    if(var->type != gsc::node_type::identifier)
        return false;
    
    auto name = (*(gsc::identifier_ptr*)&var)->value;
    
    for(const auto& var : param_vars_)
    {
        if(var == name)
            return true;
    }

    return false;
}

auto compiler::is_local_var(const gsc::identifier_ptr& var) -> bool
{
    auto name = var->value;

    for(const auto& var : local_vars_)
    {
        if(var == name)
            return true;
    }

    return false;
}

auto compiler::is_local_call(const gsc::identifier_ptr& func) -> bool
{
    auto name = func->value;

    for(const auto& f : local_functions_)
    {
        if(f == name)
            return true;
    }

    return false;
}

auto compiler::is_builtin_call(const gsc::identifier_ptr& func) -> bool
{
    if(is_builtin_func(func))
        return true;
    
    if(is_builtin_method(func))
        return true;

    return false;
}

auto compiler::is_builtin_func(const gsc::identifier_ptr& func) -> bool
{
    auto name = func->value;

    auto res = resolver::builtin_func_id(name);
    if(res != 0xFFFF) return true;

    return false;
}
auto compiler::is_builtin_method(const gsc::identifier_ptr& func) -> bool
{
    auto name = func->value;

    auto res = resolver::builtin_method_id(name);
    if(res != 0xFFFF) return true;

    return false;
}

auto compiler::create_label() -> std::string
{
    label_idx_++;
    auto name = utils::string::va("loc_%d", label_idx_);
    return name;
}

auto compiler::insert_label() -> std::string
{
    label_idx_++;
    auto name = utils::string::va("loc_%d", label_idx_);
    function_->labels.insert({index_, name});
    return name;
}

void compiler::insert_label(const std::string& name)
{
    function_->labels.insert({index_, name});
}

} // namespace IW6
