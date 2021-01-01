// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW7.hpp"
#include "compiler_parser.hpp"
#include "compiler_lexer.hpp"

namespace IW7
{

auto compiler::output() -> std::vector<gsc::function_ptr>
{
    return std::move(assembly_);
}

void compiler::compile(std::vector<std::uint8_t>& data)
{
    auto result = parse_buffer(data);

    compile_script(result);
}

auto compiler::parse_buffer(std::vector<std::uint8_t>& data) -> gsc::script_ptr
{
    yyscan_t scanner;
    std::uint32_t location = 1;
    gsc::script_ptr result(nullptr);
    
    // Add the two NULL terminators, required by flex.
    data.reserve(2);
    data.push_back(0);
    data.push_back(0);

    if (IW7lex_init(&scanner))
        exit(1);

    YY_BUFFER_STATE yybuffer = IW7_scan_buffer(reinterpret_cast<char*>(data.data()), data.size(), scanner);

    parser parser(scanner, &location, result);
    
    if(parser.parse() || result == nullptr)
    {
        GSC_COMP_ERROR("An error ocurred while parsing gsc file.");
    }

    IW7_delete_buffer(yybuffer, scanner);
    IW7lex_destroy(scanner);

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

#ifdef DEBUG
    print_debug_info();
#endif
}

void compiler::emit_include(const gsc::include_ptr& include)
{
    GSC_COMP_ERROR("INCLUDE FILES NOT SUPPORTED!");

    // TODO:
    // includes_.push_back(include->file->value);
    // need to parse the included file here, and make a vector with all function names
    // later assemble calls check if far call
    // ...
}

void compiler::emit_using_animtree(const gsc::using_animtree_ptr& animtree)
{
    animtrees_.push_back(animtree->animtree->value);
}

void compiler::emit_thread(const gsc::thread_ptr& thread)
{
    function_ = std::make_unique<gsc::function>();
    function_->index = index_;
    function_->name = thread->name->value;

    auto ctx = std::make_unique<gsc::context>();
    
    calc_local_vars(ctx, thread);
    
    emit_parameters(ctx, thread->params);
    emit_block(ctx, thread->block, true);
    emit_opcode(ctx, opcode::OP_End);

    function_->size = index_ - function_->index;
    assembly_.push_back(std::move(function_));
}

void compiler::emit_parameters(const gsc::context_ptr& ctx, const gsc::parameters_ptr& params)
{
    for(const auto& param : params->list)
    {
        auto data = utils::string::va("%d", find_local_var_create_index(ctx, param->value));
        emit_opcode(ctx, opcode::OP_SafeCreateVariableFieldCached, data);     
    }

    emit_opcode(ctx, opcode::OP_checkclearparams);
}

void compiler::emit_block(const gsc::context_ptr& ctx, const gsc::block_ptr& block, bool last)
{
    for(const auto& stmt : block->stmts)
    {
        bool last_ = (&stmt == &block->stmts.back() && last) ? true : false;
        emit_stmt(ctx, stmt, last_);
    }
}

void compiler::emit_stmt(const gsc::context_ptr& ctx, const gsc::stmt_ptr& stmt, bool last)
{
    switch(stmt.as_node->type)
    {
        case gsc::node_type::stmt_call:             emit_stmt_call(ctx, stmt.as_call); break;
        case gsc::node_type::stmt_assign:           emit_stmt_assign(ctx, stmt.as_assign); break;
        case gsc::node_type::stmt_endon:            emit_stmt_endon(ctx, stmt.as_endon); break;
        case gsc::node_type::stmt_notify:           emit_stmt_notify(ctx, stmt.as_notify); break;
        case gsc::node_type::stmt_wait:             emit_stmt_wait(ctx, stmt.as_wait); break;
        case gsc::node_type::stmt_waittill:         emit_stmt_waittill(ctx, stmt.as_waittill); break;
        case gsc::node_type::stmt_waittillmatch:    emit_stmt_waittillmatch(ctx, stmt.as_waittillmatch); break;
        case gsc::node_type::stmt_waittillframeend: emit_stmt_waittillframeend(ctx, stmt.as_waittillframeend); break;
        case gsc::node_type::stmt_if:               emit_stmt_if(ctx, stmt.as_if, last); break;
        case gsc::node_type::stmt_ifelse:           emit_stmt_ifelse(ctx, stmt.as_ifelse, last); break;
        case gsc::node_type::stmt_while:            emit_stmt_while(ctx, stmt.as_while); break;
        case gsc::node_type::stmt_for:              emit_stmt_for(ctx, stmt.as_for); break;
        case gsc::node_type::stmt_foreach:          emit_stmt_foreach(ctx, stmt.as_foreach); break;
        case gsc::node_type::stmt_switch:           emit_stmt_switch(ctx, stmt.as_switch); break;
        case gsc::node_type::stmt_case:             emit_stmt_case(ctx, stmt.as_case); break;
        case gsc::node_type::stmt_default:          emit_stmt_default(ctx, stmt.as_default); break;
        case gsc::node_type::stmt_break:            emit_stmt_break(ctx, stmt.as_break); break;
        case gsc::node_type::stmt_continue:         emit_stmt_continue(ctx, stmt.as_continue); break;
        case gsc::node_type::stmt_return:           emit_stmt_return(ctx, stmt.as_return); break;
        default: GSC_COMP_ERROR("line %s: unknown statement", stmt.as_node->location.data()); break;
    }
}

void compiler::emit_stmt_call(const gsc::context_ptr& ctx, const gsc::stmt_call_ptr& stmt)
{
    emit_expr_call(ctx, stmt->expr);
    emit_opcode(ctx, opcode::OP_DecTop);
}

void compiler::emit_stmt_assign(const gsc::context_ptr& ctx, const gsc::stmt_assign_ptr& stmt)
{
    emit_expr_assign(ctx, stmt->expr);
}

void compiler::emit_stmt_endon(const gsc::context_ptr& ctx, const gsc::stmt_endon_ptr& stmt)
{
    emit_expr(ctx, stmt->expr);
    emit_expr(ctx, stmt->obj);
    emit_opcode(ctx, opcode::OP_endon);
}

void compiler::emit_stmt_notify(const gsc::context_ptr& ctx, const gsc::stmt_notify_ptr& stmt)
{
    emit_opcode(ctx, opcode::OP_voidCodepos);
    
    std::reverse(stmt->args->list.begin(), stmt->args->list.end());
    
    for(const auto& arg : stmt->args->list)
    {
        emit_expr(ctx, arg);
    }

    emit_expr(ctx, stmt->expr);
    emit_expr(ctx, stmt->obj);
    emit_opcode(ctx, opcode::OP_notify);
}

void compiler::emit_stmt_wait(const gsc::context_ptr& ctx, const gsc::stmt_wait_ptr& stmt)
{
    emit_expr(ctx, stmt->expr);
    emit_opcode(ctx, opcode::OP_wait);
}

void compiler::emit_stmt_waittill(const gsc::context_ptr& ctx, const gsc::stmt_waittill_ptr& stmt)
{
    emit_expr(ctx, stmt->expr);
    emit_expr(ctx, stmt->obj);
    emit_opcode(ctx, opcode::OP_waittill);

    std::reverse(stmt->args->list.begin(), stmt->args->list.end());

    for(const auto& arg : stmt->args->list)
    {
        create_local_var(ctx, arg.as_identifier->value);
        auto data = utils::string::va("%d", find_local_var_index(ctx, arg.as_identifier->value));
        emit_opcode(ctx, opcode::OP_SafeSetWaittillVariableFieldCached, data);
    }

    emit_opcode(ctx, opcode::OP_clearparams);
}

void compiler::emit_stmt_waittillmatch(const gsc::context_ptr& ctx, const gsc::stmt_waittillmatch_ptr& stmt)
{
    emit_expr(ctx, stmt->rexpr);
    emit_expr(ctx, stmt->lexpr);
    emit_expr(ctx, stmt->obj);
    emit_opcode(ctx, opcode::OP_waittillmatch);
    emit_opcode(ctx, opcode::OP_clearparams);
}

void compiler::emit_stmt_waittillframeend(const gsc::context_ptr& ctx, const gsc::stmt_waittillframeend_ptr& stmt)
{
    emit_opcode(ctx, opcode::OP_waittillFrameEnd);
}

void compiler::emit_stmt_if(const gsc::context_ptr& ctx, const gsc::stmt_if_ptr& stmt, bool last)
{
    auto end_loc = create_label();
    auto if_ctx = ctx->transfer();

    if_ctx->is_last = last;

    calc_local_vars_block(if_ctx, stmt->block);

    if(stmt->expr.as_node->type == gsc::node_type::expr_not)
    {
        emit_expr(ctx, stmt->expr.as_not->rvalue);
        emit_opcode(ctx, opcode::OP_JumpOnTrue, end_loc);
    }
    else
    {
        emit_expr(ctx, stmt->expr);
        emit_opcode(ctx, opcode::OP_JumpOnFalse, end_loc);
    }

    emit_block(if_ctx, stmt->block, last);

    last ? emit_opcode(ctx, opcode::OP_End) : emit_remove_local_vars(if_ctx);

    insert_label(end_loc);
}

void compiler::emit_stmt_ifelse(const gsc::context_ptr& ctx, const gsc::stmt_ifelse_ptr& stmt, bool last)
{
    auto else_loc = create_label();
    auto end_loc = create_label();

    auto if_ctx = ctx->transfer();   // TODO: merge else block private variables ?
    auto else_ctx = ctx->transfer(); // TODO: merge if block private variables ?

    if_ctx->is_last = last;
    else_ctx->is_last = last;

    calc_local_vars_block(if_ctx, stmt->block_if);
    calc_local_vars_block(else_ctx, stmt->block_else);

    if(stmt->expr.as_node->type == gsc::node_type::expr_not)
    {
        emit_expr(ctx, stmt->expr.as_not->rvalue);
        emit_opcode(ctx, opcode::OP_JumpOnTrue, else_loc);
    }
    else
    {
        emit_expr(ctx, stmt->expr);
        emit_opcode(ctx, opcode::OP_JumpOnFalse, else_loc);
    }

    emit_block(if_ctx, stmt->block_if, last);

    emit_remove_local_vars(if_ctx);

    last ? emit_opcode(ctx, opcode::OP_End) : emit_opcode(ctx, opcode::OP_jump, end_loc);

    insert_label(else_loc);

    emit_block(else_ctx, stmt->block_else, last);

    last ? emit_opcode(ctx, opcode::OP_End) : emit_remove_local_vars(else_ctx);

    insert_label(end_loc);
}

void compiler::emit_stmt_while(const gsc::context_ptr& ctx, const gsc::stmt_while_ptr& stmt)
{
    auto begin_loc = create_label();
    auto break_loc = create_label();
    auto continue_loc = create_label();
    auto while_ctx = ctx->transfer();

    while_ctx->is_loop = true;
    while_ctx->loc_break = break_loc;
    while_ctx->loc_continue = continue_loc;

    calc_local_vars_block(while_ctx, stmt->block);
    emit_create_local_vars(while_ctx);

    // TODO: check if constant condition
    insert_label(begin_loc);
    emit_expr(ctx, stmt->expr);
    emit_opcode(ctx, opcode::OP_JumpOnFalse, break_loc);

    emit_block(while_ctx, stmt->block, false);

    insert_label(continue_loc);
    emit_opcode(ctx, opcode::OP_jumpback, begin_loc);

    insert_label(break_loc);
}

void compiler::emit_stmt_for(const gsc::context_ptr& ctx, const gsc::stmt_for_ptr& stmt)
{
    auto begin_loc = create_label();
    auto break_loc = create_label();
    auto continue_loc = create_label();

    if(stmt->pre_expr.as_node->type != gsc::node_type::null)
        emit_expr(ctx, stmt->pre_expr);

    auto for_ctx = ctx->transfer();

    for_ctx->is_loop = true;
    for_ctx->loc_break = break_loc;
    for_ctx->loc_continue = continue_loc;

    calc_local_vars_block(for_ctx, stmt->block);
    emit_create_local_vars(for_ctx);

    // TODO: check if constant condition
    insert_label(begin_loc);

    if(stmt->expr.as_node->type != gsc::node_type::null)
        emit_expr(ctx, stmt->expr);

    emit_block(for_ctx, stmt->block, false);

    insert_label(continue_loc);

    if(stmt->post_expr.as_node->type != gsc::node_type::null)
        emit_expr(ctx, stmt->post_expr);

    emit_opcode(ctx, opcode::OP_jumpback, begin_loc);
    
    insert_label(break_loc);
}

void compiler::emit_stmt_foreach(const gsc::context_ptr& ctx, const gsc::stmt_foreach_ptr& stmt)
{
    GSC_COMP_ERROR("FOREACH STATEMENT NOT SUPPORTED!");

    // TODO:

    auto begin_loc = create_label();
    auto break_loc = create_label();
    auto continue_loc = create_label();

    // TODO: insert first array key

    // TODO: create local variables

    insert_label(begin_loc);
    
    // TODO: insert isDefined, assign

    auto foreach_ctx = ctx->transfer();

    foreach_ctx->is_loop = true;
    foreach_ctx->loc_break = break_loc;
    foreach_ctx->loc_continue = continue_loc;

    emit_block(foreach_ctx, stmt->block, false);

    insert_label(continue_loc);
    // TODO: insert next array key
    emit_opcode(ctx, opcode::OP_jumpback, begin_loc);
    
    insert_label(break_loc);
    
    // TODO: clear key and array vars
        //OP_ClearLocalVariableFieldCached0 = 0x30,
        //OP_ClearLocalVariableFieldCached = 0x31,
}

void compiler::emit_stmt_switch(const gsc::context_ptr& ctx, const gsc::stmt_switch_ptr& stmt)
{
    auto jmptable_loc = create_label();
    auto break_loc = create_label();

    auto switch_ctx = ctx->transfer();

    switch_ctx->is_switch = true;
    switch_ctx->loc_break = break_loc;

    // calc local vars & emit ?

    emit_expr(ctx, stmt->expr);
    emit_opcode(ctx, opcode::OP_switch, jmptable_loc);
    
    emit_block(switch_ctx, stmt->block, false);

    insert_label(jmptable_loc);

    std::vector<std::string> data;
    data.push_back(utils::string::va("%d", switch_ctx->case_id.size()));
    
    auto i = 0;
    for(auto& id : switch_ctx->case_id)
    {
        if(id != "default")
        {
            data.push_back("case");
            data.push_back(id);
            data.push_back(switch_ctx->case_loc.at(i));
            i++;
        }
        else
        {
            data.push_back(id);
            data.push_back(switch_ctx->case_loc.at(i));
            i++;
        }   
    }

    emit_opcode(ctx, opcode::OP_endswitch, data);

    auto offset =  7 * switch_ctx->case_id.size();
    function_->instructions.back()->size += offset;
    index_ += offset;

    insert_label(break_loc);
}

void compiler::emit_stmt_case(const gsc::context_ptr& ctx, const gsc::stmt_case_ptr& stmt)
{
    if(!ctx->is_switch)
    {
        GSC_COMP_ERROR("line %s: illegal case statement outside a switch", stmt->location.data());
    }

    if(stmt->value.as_node->type == gsc::node_type::data_integer)
    {
        auto loc = insert_label();
        ctx->case_id.push_back(stmt->value.as_integer->value);
        ctx->case_loc.push_back(loc);
    }
    else if(stmt->value.as_node->type == gsc::node_type::data_string)
    {
        auto loc = insert_label();
        ctx->case_id.push_back(stmt->value.as_string->value);
        ctx->case_loc.push_back(loc);
    }
    else
    {
        GSC_COMP_ERROR("line %s: illegal case type", stmt->location.data());
    }
}

void compiler::emit_stmt_default(const gsc::context_ptr& ctx, const gsc::stmt_default_ptr& stmt)
{
    if(!ctx->is_switch)
    {
        GSC_COMP_ERROR("line %s: illegal default statement outside a switch", stmt->location.data());
    }

    auto loc = insert_label();
    ctx->case_id.push_back("default");
    ctx->case_loc.push_back(loc);
}

void compiler::emit_stmt_break(const gsc::context_ptr& ctx, const gsc::stmt_break_ptr& stmt)
{
    if(ctx->loc_break == "")
    {
        GSC_COMP_ERROR("line %s: illegal break statement outside a loop", stmt->location.data());
    }

    emit_remove_local_vars(ctx);
    emit_opcode(ctx, opcode::OP_jump, ctx->loc_break);
}

void compiler::emit_stmt_continue(const gsc::context_ptr& ctx, const gsc::stmt_continue_ptr& stmt)
{
    if(ctx->loc_continue == "")
    {
        GSC_COMP_ERROR("line %s: illegal continue statement outside a loop", stmt->location.data());
    }

    emit_remove_local_vars(ctx);
    emit_opcode(ctx, opcode::OP_jump, ctx->loc_continue);
}

void compiler::emit_stmt_return(const gsc::context_ptr& ctx, const gsc::stmt_return_ptr& stmt)
{
    if(stmt->expr.as_node->type == gsc::node_type::null)
    {
        emit_opcode(ctx, opcode::OP_End);
        return; 
    }
    
    emit_expr(ctx, stmt->expr);
    emit_opcode(ctx, opcode::OP_Return);
}

void compiler::emit_expr(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr)
{
    switch(expr.as_node->type)
    {
        case gsc::node_type::expr_ternary:          emit_expr_ternary(ctx, expr.as_ternary); break;
        case gsc::node_type::expr_and:              emit_expr_and(ctx, expr.as_and); break;
        case gsc::node_type::expr_or:               emit_expr_or(ctx, expr.as_or); break;
        case gsc::node_type::expr_equality:         emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_inequality:       emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_less:             emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_greater:          emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_less_equal:       emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_greater_equal:    emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_bitwise_or:       emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_bitwise_and:      emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_bitwise_exor:     emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_shift_left:       emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_shift_right:      emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_add:              emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_sub:              emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_mult:             emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_div:              emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_mod:              emit_expr_binary(ctx, expr.as_binary); break;
        case gsc::node_type::expr_complement:       emit_expr_complement(ctx, expr.as_complement); break;
        case gsc::node_type::expr_not:              emit_expr_not(ctx, expr.as_not); break;
        case gsc::node_type::expr_call:             emit_expr_call(ctx, expr.as_call); break;
        case gsc::node_type::expr_array:            emit_array_variable(ctx, expr.as_array); break;
        case gsc::node_type::expr_field:            emit_field_variable(ctx, expr.as_field); break;
        case gsc::node_type::expr_size:             emit_expr_size(ctx, expr.as_size_expr); break;
        case gsc::node_type::expr_function_ref:     emit_expr_function_ref(ctx, expr.as_function_ref); break;
        case gsc::node_type::empty_array:           emit_opcode(ctx, opcode::OP_EmptyArray); break;
        case gsc::node_type::undefined:             emit_opcode(ctx, opcode::OP_GetUndefined); break;
        case gsc::node_type::level:                 emit_opcode(ctx, opcode::OP_GetLevel); break;
        case gsc::node_type::anim:                  emit_opcode(ctx, opcode::OP_GetAnim); break;
        case gsc::node_type::self:                  emit_opcode(ctx, opcode::OP_GetSelf); break;
        case gsc::node_type::game:                  emit_opcode(ctx, opcode::OP_GetGame); break;
        case gsc::node_type::identifier:            emit_local_variable(ctx, expr.as_identifier); break;
        case gsc::node_type::data_string:           emit_string(ctx, expr.as_string); break;
        case gsc::node_type::data_localized_string: emit_localized_string(ctx, expr.as_localized_string); break;
        case gsc::node_type::data_float:            emit_float(ctx, expr.as_float); break;
        case gsc::node_type::data_integer:          emit_integer(ctx, expr.as_integer); break;
        case gsc::node_type::data_vector:           emit_vector(ctx, expr.as_vector); break;
        case gsc::node_type::expr_vector:           emit_expr_vector(ctx, expr.as_vector_expr); break;
        default: GSC_COMP_ERROR("line %s: unknown expression", expr.as_node->location.data()); break;
    }
}

void compiler::emit_expr_assign(const gsc::context_ptr& ctx, const gsc::expr_assign_ptr& expr)	
{
    if(expr->type == gsc::node_type::expr_increment)
    {
        emit_variable_ref(ctx, expr->lvalue, false);
        emit_opcode(ctx, opcode::OP_inc);
        emit_opcode(ctx, opcode::OP_SetVariableField);
    }
    else if(expr->type == gsc::node_type::expr_decrement)
    {
        emit_variable_ref(ctx, expr->lvalue, false);
        emit_opcode(ctx, opcode::OP_dec);
        emit_opcode(ctx, opcode::OP_SetVariableField);
    }
    else if(expr->type == gsc::node_type::expr_assign_equal)
    {
        if(expr->rvalue.as_node->type == gsc::node_type::undefined)
        {
            emit_expr_clear_variable(ctx, expr->lvalue);
        }
        else
        {
            emit_expr(ctx, expr->rvalue);
            emit_variable_ref(ctx, expr->lvalue, true);
        }
    }
    else
    {
        emit_expr(ctx, expr->lvalue);
        emit_expr(ctx, expr->rvalue);

        switch(expr->type)
        {
            case gsc::node_type::expr_assign_add:           emit_opcode(ctx, opcode::OP_plus); break;
            case gsc::node_type::expr_assign_sub:           emit_opcode(ctx, opcode::OP_minus); break;
            case gsc::node_type::expr_assign_mult:          emit_opcode(ctx, opcode::OP_multiply); break;
            case gsc::node_type::expr_assign_div:           emit_opcode(ctx, opcode::OP_divide); break;
            case gsc::node_type::expr_assign_mod:           emit_opcode(ctx, opcode::OP_mod); break;
            case gsc::node_type::expr_assign_shift_left:    emit_opcode(ctx, opcode::OP_shift_left); break;
            case gsc::node_type::expr_assign_shift_right:   emit_opcode(ctx, opcode::OP_shift_right); break;
            case gsc::node_type::expr_assign_bitwise_or:    emit_opcode(ctx, opcode::OP_bit_or); break;
            case gsc::node_type::expr_assign_bitwise_and:   emit_opcode(ctx, opcode::OP_bit_and); break;
            case gsc::node_type::expr_assign_bitwise_exor:  emit_opcode(ctx, opcode::OP_bit_ex_or); break;
            default: GSC_COMP_ERROR("line %s: unknown assign operation", expr->location.data()); break;
        }

        emit_variable_ref(ctx, expr->lvalue, true);
    }  
}

void compiler::emit_expr_ternary(const gsc::context_ptr& ctx, const gsc::expr_ternary_ptr& expr)
{
    GSC_COMP_ERROR("TERNARY EXPRESSION NOT SUPPORTED!");
}

void compiler::emit_expr_binary(const gsc::context_ptr& ctx, const gsc::expr_binary_ptr& expr)
{
    emit_expr(ctx, expr->lvalue);
    emit_expr(ctx, expr->rvalue);

    switch(expr->type)
    {
        case gsc::node_type::expr_equality:         emit_opcode(ctx, opcode::OP_equality); break;
        case gsc::node_type::expr_inequality:       emit_opcode(ctx, opcode::OP_inequality); break;
        case gsc::node_type::expr_less:             emit_opcode(ctx, opcode::OP_less); break;
        case gsc::node_type::expr_greater:          emit_opcode(ctx, opcode::OP_greater); break;
        case gsc::node_type::expr_less_equal:       emit_opcode(ctx, opcode::OP_less_equal); break;
        case gsc::node_type::expr_greater_equal:    emit_opcode(ctx, opcode::OP_greater_equal); break;
        case gsc::node_type::expr_bitwise_or:       emit_opcode(ctx, opcode::OP_bit_or); break;
        case gsc::node_type::expr_bitwise_and:      emit_opcode(ctx, opcode::OP_bit_and); break;
        case gsc::node_type::expr_bitwise_exor:     emit_opcode(ctx, opcode::OP_bit_ex_or); break;
        case gsc::node_type::expr_shift_left:       emit_opcode(ctx, opcode::OP_shift_left); break;
        case gsc::node_type::expr_shift_right:      emit_opcode(ctx, opcode::OP_shift_right); break;
        case gsc::node_type::expr_add:              emit_opcode(ctx, opcode::OP_plus); break;
        case gsc::node_type::expr_sub:              emit_opcode(ctx, opcode::OP_minus); break;
        case gsc::node_type::expr_mult:             emit_opcode(ctx, opcode::OP_multiply); break;
        case gsc::node_type::expr_div:              emit_opcode(ctx, opcode::OP_divide); break;
        case gsc::node_type::expr_mod:              emit_opcode(ctx, opcode::OP_mod); break;
        default: GSC_COMP_ERROR("line %s: unknown binary expression", expr->location.data()); break;
    }
}

void compiler::emit_expr_and(const gsc::context_ptr& ctx, const gsc::expr_and_ptr& expr)
{
    auto label = create_label();

    emit_expr(ctx, expr->lvalue);
    emit_opcode(ctx, opcode::OP_JumpOnFalseExpr, label);
    emit_expr(ctx, expr->rvalue);
    emit_opcode(ctx, opcode::OP_CastBool);

    insert_label(label);
}

void compiler::emit_expr_or(const gsc::context_ptr& ctx, const gsc::expr_or_ptr& expr)
{
    auto label = create_label();

    emit_expr(ctx, expr->lvalue);
    emit_opcode(ctx, opcode::OP_JumpOnTrueExpr, label);
    emit_expr(ctx, expr->rvalue);
    emit_opcode(ctx, opcode::OP_CastBool);

    insert_label(label);
}

void compiler::emit_expr_complement(const gsc::context_ptr& ctx, const gsc::expr_complement_ptr& expr)
{
    emit_expr(ctx, expr->rvalue);
    emit_opcode(ctx, opcode::OP_BoolComplement);
}

void compiler::emit_expr_not(const gsc::context_ptr& ctx, const gsc::expr_not_ptr& expr)
{
    emit_expr(ctx, expr->rvalue);
    emit_opcode(ctx, opcode::OP_BoolNot);
}

void compiler::emit_expr_call(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr)
{
    bool thread = false, method = false, builtin = false, far = false, local = false;
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
            emit_opcode(ctx, opcode::OP_PreScriptCall);
  
        emit_expr_arguments(ctx, expr->func.as_pointer->args);

        if(method)
            emit_expr(ctx, expr->obj);

        emit_expr(ctx, expr->func.as_pointer->expr);
        emit_expr_call_pointer(ctx, args, builtin, method, thread, false);
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
            if(is_local_call(name))
            {
                local = true;
            }
            else if(method && is_builtin_method(name))
            {
                builtin = true;
            }
            else if(!method && is_builtin_func(name))
            {
                builtin = true;
            }
            else
            {
                // maybe a far call, but include files not supported!
                GSC_COMP_ERROR("line %s: unknown function call '%s'", expr->location.data(), name.data());
            }
        }

        if(args > 0 && !thread && !builtin)
            emit_opcode(ctx, opcode::OP_PreScriptCall);

        emit_expr_arguments(ctx, expr->func.as_func->args);

        if(method)
            emit_expr(ctx, expr->obj);

        if(far)
            emit_expr_call_far(ctx, file, name, args, method, thread, false);
        else if(local)
            emit_expr_call_local(ctx, name, args, method, thread, false);
        else if(builtin)
            emit_expr_call_builtin(ctx, name, args, method);
    }
}

void compiler::emit_expr_call_pointer(const gsc::context_ptr& ctx, int args, bool builtin, bool method, bool thread, bool child)
{
    if(builtin && !method)
    {
        emit_opcode(ctx, opcode::OP_CallBuiltinPointer, utils::string::va("%d", args));
    }
    else if(builtin && !method)
    {
        emit_opcode(ctx, opcode::OP_CallBuiltinMethodPointer, utils::string::va("%d", args));
    }
    /*else if(thread && method && child)
    {
        emit_opcode(ctx, opcode::OP_ScriptMethodChildThreadCallPointer, utils::string::va("%d", args));
    }*/
    else if(thread && method && !child)
    {
        emit_opcode(ctx, opcode::OP_ScriptMethodThreadCallPointer, utils::string::va("%d", args));
    }
    /*else if (thread && !method && child)
    {
        emit_opcode(ctx, opcode::OP_ScriptChildThreadCallPointer, utils::string::va("%d", args));
    }*/
    else if(thread && !method && !child)
    {
        emit_opcode(ctx, opcode::OP_ScriptThreadCallPointer, utils::string::va("%d", args));
    } 
    else
    {
        method ? emit_opcode(ctx, opcode::OP_ScriptMethodCallPointer) : emit_opcode(ctx, opcode::OP_ScriptFunctionCallPointer);
    }
}

void compiler::emit_expr_call_far(const gsc::context_ptr& ctx, const std::string& file, const std::string& func, int args, bool method, bool thread, bool child)
{
    /*if(thread && method && child)
    {
        emit_opcode(ctx, opcode::OP_ScriptFarMethodChildThreadCall, { utils::string::va("%d", args), file, func });
    }
    else */if(thread && method && !child)
    {
        emit_opcode(ctx, opcode::OP_ScriptFarMethodThreadCall, { utils::string::va("%d", args), file, func });
    }
    /*else if(thread && !method && child)
    {
        emit_opcode(ctx, opcode::OP_ScriptFarChildThreadCall, { utils::string::va("%d", args), file, func });
    }*/
    else if(thread && !method && !child)
    {
        emit_opcode(ctx, opcode::OP_ScriptFarThreadCall, { utils::string::va("%d", args), file, func });
    }
    else if(!thread && method)
    {
        emit_opcode(ctx, opcode::OP_ScriptFarMethodCall, { file, func });
    }
    else if(!thread && !method && args == 0)
    {
        emit_opcode(ctx, opcode::OP_ScriptFarFunctionCall2, { file, func });
    }
    else if(!thread && !method && args != 0)
    {
        emit_opcode(ctx, opcode::OP_ScriptFarFunctionCall, { file, func });
    }
}

void compiler::emit_expr_call_local(const gsc::context_ptr& ctx, const std::string& func, int args, bool method, bool thread, bool child)
{
    if(thread && method && child)
    {
        emit_opcode(ctx, opcode::OP_ScriptLocalMethodChildThreadCall, { func, utils::string::va("%d", args) });
    }
    else if(thread && method && !child)
    {
        emit_opcode(ctx, opcode::OP_ScriptLocalMethodThreadCall, { func, utils::string::va("%d", args) });
    }
   else if(thread && !method && child)
    {
        emit_opcode(ctx, opcode::OP_ScriptLocalChildThreadCall, { func, utils::string::va("%d", args) });
    }
    else if(thread && !method && !child)
    {
        emit_opcode(ctx, opcode::OP_ScriptLocalThreadCall, { func, utils::string::va("%d", args) });
    }
    else if(!thread && method)
    {
        emit_opcode(ctx, opcode::OP_ScriptLocalMethodCall, func);
    }
    else if(!thread && !method && args == 0)
    {
        emit_opcode(ctx, opcode::OP_ScriptLocalFunctionCall2, func);
    }
    else if(!thread && !method && args != 0)
    {
        emit_opcode(ctx, opcode::OP_ScriptLocalFunctionCall, func);
    }
}

void compiler::emit_expr_call_builtin(const gsc::context_ptr& ctx, const std::string& func, int args, bool method)
{
    if(method)
    {
        switch(args)
        {
            case 0: emit_opcode(ctx, opcode::OP_CallBuiltinMethod0, func); break;
            case 1: emit_opcode(ctx, opcode::OP_CallBuiltinMethod1, func); break;
            case 2: emit_opcode(ctx, opcode::OP_CallBuiltinMethod2, func); break;
            case 3: emit_opcode(ctx, opcode::OP_CallBuiltinMethod3, func); break;
            case 4: emit_opcode(ctx, opcode::OP_CallBuiltinMethod4, func); break;
            case 5: emit_opcode(ctx, opcode::OP_CallBuiltinMethod5, func); break;
            default: emit_opcode(ctx, opcode::OP_CallBuiltinMethod, { utils::string::va("%d", args), func }); break;
        }
    }
    else
    {
        switch(args)
        {
            case 0: emit_opcode(ctx, opcode::OP_CallBuiltin0, func); break;
            case 1: emit_opcode(ctx, opcode::OP_CallBuiltin1, func); break;
            case 2: emit_opcode(ctx, opcode::OP_CallBuiltin2, func); break;
            case 3: emit_opcode(ctx, opcode::OP_CallBuiltin3, func); break;
            case 4: emit_opcode(ctx, opcode::OP_CallBuiltin4, func); break;
            case 5: emit_opcode(ctx, opcode::OP_CallBuiltin5, func); break;
            default: emit_opcode(ctx, opcode::OP_CallBuiltin, { utils::string::va("%d", args), func }); break;
        }
    }
}

void compiler::emit_expr_arguments(const gsc::context_ptr& ctx, const gsc::expr_arguments_ptr& args)
{
    std::reverse(args->list.begin(), args->list.end());

    for(auto& arg : args->list)
    {
        emit_expr(ctx, arg);
    }
}

void compiler::emit_expr_function_ref(const gsc::context_ptr& ctx, const gsc::expr_function_ref_ptr& expr)
{
    bool far = false, local = false, builtin = false, method = false;
    auto name = expr->func->value;
    auto file = expr->file->value;

    if(file != "")
    {
        far = true;
    }
    else if(is_builtin_method(name))
    {
        builtin = true;
        method = true;
    }
    else if(is_builtin_func(name))
    {
        builtin = true;
    }
    else if(is_local_call(name))
    {
        local = true;
    }

    if(local)
    {
        emit_opcode(ctx, opcode::OP_GetLocalFunction, name);
    }
    else if(far)
    {
        emit_opcode(ctx, opcode::OP_GetFarFunction, { file, name } );
    }
    else if(builtin && method)
    {
        emit_opcode(ctx, opcode::OP_GetBuiltinMethod, name);
    }
    else if(builtin && !method)
    {
        emit_opcode(ctx, opcode::OP_GetBuiltinFunction, name);
    }
}

void compiler::emit_expr_clear_variable(const gsc::context_ptr& ctx, const gsc::expr_ptr& lvalue)
{
    switch(lvalue.as_node->type)
    {
    case gsc::node_type::expr_array:
        emit_expr(ctx, lvalue.as_array->key);
        lvalue.as_array->obj.as_node->type == gsc::node_type::game ? emit_opcode(ctx, opcode::OP_GetGameRef) : emit_variable_ref(ctx, lvalue.as_array->obj, false);
        emit_opcode(ctx, opcode::OP_ClearArray);
        break;
    case gsc::node_type::expr_field:
        emit_object(ctx, lvalue.as_field->obj);
        emit_opcode(ctx, opcode::OP_ClearFieldVariable,lvalue.as_field->field->value);
        break;
    case gsc::node_type::identifier:
        emit_opcode(ctx, opcode::OP_GetUndefined);
        emit_local_variable_ref(ctx, lvalue.as_identifier, true);
        break;
    default:
        GSC_COMP_ERROR("line %s: unknown clear variable lvalue", lvalue.as_node->location.data());
        break;
    }
}

void compiler::emit_expr_add_array(const gsc::context_ptr& ctx, const gsc::expr_add_array_ptr& expr)
{
    if(expr->args->list.size() <= 0)
    {
        GSC_COMP_ERROR("line %s: invalid empty add array. did u mean '[]' ?", expr->location.data());
    }
    
    emit_opcode(ctx, opcode::OP_EmptyArray);

    for(const auto& arg : expr->args->list)
    {
        emit_expr(ctx, arg);
        emit_opcode(ctx, opcode::OP_AddArray);
    }
}

void compiler::emit_expr_vector(const gsc::context_ptr& ctx, const gsc::expr_vector_ptr& expr)
{
    emit_expr(ctx, expr->z);
    emit_expr(ctx, expr->y);
    emit_expr(ctx, expr->x);
    emit_opcode(ctx, opcode::OP_vector);
}

void compiler::emit_expr_size(const gsc::context_ptr& ctx, const gsc::expr_size_ptr& expr)
{
    emit_object(ctx, expr->obj);
    emit_opcode(ctx, opcode::OP_size);
}

void compiler::emit_variable_ref(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr, bool set)
{
    switch(expr.as_node->type)
    {
        case gsc::node_type::expr_array: emit_array_variable_ref(ctx, expr.as_array, set); break;
        case gsc::node_type::expr_field: emit_field_variable_ref(ctx, expr.as_field, set); break;
        case gsc::node_type::identifier: emit_local_variable_ref(ctx, expr.as_identifier, set); break;
        default: GSC_COMP_ERROR("line %s: invalid variable reference type.", expr.as_node->location.data()); break;
    }
}

void compiler::emit_array_variable_ref(const gsc::context_ptr& ctx, const gsc::expr_array_ptr& expr, bool set)
{
    emit_expr(ctx, expr->key);

    switch(expr->obj.as_node->type)
    {
    case gsc::node_type::game:
        emit_opcode(ctx, opcode::OP_GetGameRef);
        emit_opcode(ctx, opcode::OP_EvalArrayRef);
        if(set) emit_opcode(ctx, opcode::OP_SetVariableField);
        break;
    case gsc::node_type::expr_array:
    case gsc::node_type::expr_field:
        emit_variable_ref(ctx, expr->obj, false);
        emit_opcode(ctx, opcode::OP_EvalArrayRef);      
        if(set) emit_opcode(ctx, opcode::OP_SetVariableField);
        break;
    case gsc::node_type::identifier: // local array
        {
            auto name = expr->obj.as_identifier->value;

            if(!is_local_var_initialized(ctx, name))
            {
                // create a local array and set one of its elements without having to initialize it first
                auto index = find_local_var_create_index(ctx, name);
                ctx->local_vars_init.at(index) = true;
                ctx->local_vars_create_count++;
                emit_opcode(ctx, opcode::OP_EvalNewLocalArrayRefCached0, utils::string::va("%d", index));

                if(!set)
                {
                    GSC_COMP_ERROR("INTERNAL: VAR CREATED BUT NOT SET! line %s", expr->location.data());
                }
            }
            else if(find_local_var_index(ctx, name) == 0)
            {
                // evaluates the last created local array.
                emit_opcode(ctx, opcode::OP_EvalLocalArrayRefCached0);
            }
            else
            {
                // evaluate an array by local_variable_index
                auto index = find_local_var_index(ctx,name);
                emit_opcode(ctx, opcode::OP_EvalLocalArrayRefCached, utils::string::va("%d", index));
            }

            if(set) emit_opcode(ctx, opcode::OP_SetVariableField);
        }
        break;
    case gsc::node_type::expr_call:
        GSC_COMP_ERROR("line %s: call result can't be referenced.", expr->location.data());
        break;
    default:
        GSC_COMP_ERROR("line %s: unknown array object type", expr->location.data());
        break;
    }
}

void compiler::emit_field_variable_ref(const gsc::context_ptr& ctx, const gsc::expr_field_ptr&  expr, bool set)
{
    const auto& field = expr->field->value;

    switch(expr->obj.as_node->type)
    {
    case gsc::node_type::level:
        set ? emit_opcode(ctx, opcode::OP_SetLevelFieldVariableField, field) : emit_opcode(ctx, opcode::OP_EvalLevelFieldVariableRef, field);
        break;
    case gsc::node_type::anim:
        set ? emit_opcode(ctx, opcode::OP_SetAnimFieldVariableField, field) : emit_opcode(ctx, opcode::OP_EvalAnimFieldVariableRef, field);
        break;
    case gsc::node_type::self:
        set ? emit_opcode(ctx, opcode::OP_SetSelfFieldVariableField, field) : emit_opcode(ctx, opcode::OP_EvalSelfFieldVariableRef, field);
        break;
    case gsc::node_type::expr_array:
        emit_array_variable_ref(ctx, expr->obj.as_array, false);
        emit_opcode(ctx, opcode::OP_CastFieldObject);             // TODO: need?
        emit_opcode(ctx, opcode::OP_EvalFieldVariableRef, field);    
        if(set) emit_opcode(ctx, opcode::OP_SetVariableField);
        break;
    case gsc::node_type::identifier:
        emit_opcode(ctx, opcode::OP_EvalLocalVariableObjectCached, utils::string::va("%d", find_local_var_index(ctx, expr->obj.as_identifier->value)));
        emit_opcode(ctx, opcode::OP_EvalFieldVariableRef, field);
        if(set) emit_opcode(ctx, opcode::OP_SetVariableField);
        break;
    // case field:  var.field.field
    case gsc::node_type::expr_call:
        GSC_COMP_ERROR("line %s: function call result can't be referenced", expr->location.data());
        break;
    default:
        GSC_COMP_ERROR("line %s: unknown field variable objet type", expr->location.data());
        break;
    }
}

void compiler::emit_local_variable_ref(const gsc::context_ptr& ctx, const gsc::identifier_ptr& expr, bool set)
{
    if(set)
    {
        if(!is_local_var_initialized(ctx, expr->value))
        {
            auto index = find_local_var_create_index(ctx, expr->value);
            ctx->local_vars_init.at(index) = true;
            ctx->local_vars_create_count++;
            emit_opcode(ctx, opcode::OP_SetNewLocalVariableFieldCached0, utils::string::va("%d", index));
        }
        else if(find_local_var_index(ctx, expr->value) == 0)
        {
            emit_opcode(ctx, opcode::OP_SetLocalVariableFieldCached0);
        }
        else
        {
            auto index = find_local_var_index(ctx, expr->value);
            emit_opcode(ctx, opcode::OP_SetLocalVariableFieldCached, utils::string::va("%d", index));
        }
    }
    else
    {
        auto index = find_local_var_index(ctx, expr->value);

        index == 0 ? emit_opcode(ctx, opcode::OP_EvalLocalVariableRefCached0) : emit_opcode(ctx, opcode::OP_EvalLocalVariableRefCached, utils::string::va("%d", index));
    }
}

void compiler::emit_array_variable(const gsc::context_ptr& ctx, const gsc::expr_array_ptr& expr)
{
    emit_expr(ctx, expr->key);

    if(expr->obj.as_node->type == gsc::node_type::identifier)
    {
        auto data = utils::string::va("%d", find_local_var_index(ctx, expr->obj.as_identifier->value));
        emit_opcode(ctx, opcode::OP_EvalLocalArrayCached, data);
    }
    else
    {
        emit_expr(ctx, expr->obj);
        emit_opcode(ctx, opcode::OP_EvalArray);
    }
}

void compiler::emit_field_variable(const gsc::context_ptr& ctx, const gsc::expr_field_ptr& expr)
{
    switch(expr->obj.as_node->type)
    {
    case gsc::node_type::level:
        emit_opcode(ctx, opcode::OP_EvalLevelFieldVariable, expr->field->value);
        break;
    case gsc::node_type::anim:
        emit_opcode(ctx, opcode::OP_EvalAnimFieldVariable, expr->field->value);
        break;
    case gsc::node_type::self:
        emit_opcode(ctx, opcode::OP_EvalSelfFieldVariable, expr->field->value);
        break;
    default:
        emit_object(ctx, expr->obj);
        emit_opcode(ctx, opcode::OP_EvalFieldVariable, expr->field->value);
        break;

        // arrays?
    }
}

void compiler::emit_local_variable(const gsc::context_ptr& ctx, const gsc::identifier_ptr& expr)
{
    auto index = find_local_var_index(ctx, expr->value);

    switch(index)
    {
        case 0: emit_opcode(ctx, opcode::OP_EvalLocalVariableCached0); break;
        case 1: emit_opcode(ctx, opcode::OP_EvalLocalVariableCached1); break;
        case 2: emit_opcode(ctx, opcode::OP_EvalLocalVariableCached2); break;
        case 3: emit_opcode(ctx, opcode::OP_EvalLocalVariableCached3); break;
        case 4: emit_opcode(ctx, opcode::OP_EvalLocalVariableCached4); break;
        case 5: emit_opcode(ctx, opcode::OP_EvalLocalVariableCached5); break;
        default: emit_opcode(ctx, opcode::OP_EvalLocalVariableCached, utils::string::va("%d", index)); break;
    }
}

void compiler::emit_create_local_vars(const gsc::context_ptr& ctx)
{
    auto count = ctx->local_vars.size() - ctx->local_vars_create_count;

    for(auto i = ctx->local_vars_create_count; i < count; i++)
    {
        auto data = utils::string::va("%d", ctx->local_vars_create_count);
        emit_opcode(ctx, opcode::OP_CreateLocalVariable, data);
        ctx->local_vars_init.at(i) = true;
        ctx->local_vars_create_count++;
    }
}

void compiler::emit_remove_local_vars(const gsc::context_ptr& ctx)
{
    auto count = ctx->local_vars_create_count - ctx->local_vars_public_count;

    if(count > 0)
    {
        auto data = utils::string::va("%d", count);
        emit_opcode(ctx, opcode::OP_RemoveLocalVariables, data);
    }
}

void compiler::emit_object(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr)
{
    switch(expr.as_node->type)
    {
        case gsc::node_type::level:
            emit_opcode(ctx, opcode::OP_GetLevelObject);
            break;
        case gsc::node_type::anim:
            emit_opcode(ctx, opcode::OP_GetAnimObject);
            break;
        case gsc::node_type::self:
            emit_opcode(ctx, opcode::OP_GetSelfObject);
            break;
        case gsc::node_type::identifier:
            emit_opcode(ctx, opcode::OP_EvalLocalVariableObjectCached, utils::string::va("%d", find_local_var_index(ctx, expr.as_identifier->value)));
            break;
        case gsc::node_type::expr_call:
            emit_expr_call(ctx, expr.as_call);
            emit_opcode(ctx, opcode::OP_CastFieldObject);
            break;
        // array ?
        // field ?
        default:
            GSC_COMP_ERROR("line %s: unknown object type", expr.as_node->location.data());
            break;
    }
}

void compiler::emit_vector(const gsc::context_ptr& ctx, const gsc::vector_ptr& vec)
{
    std::vector<std::string> data;

    if(vec->x->type == gsc::node_type::data_integer)
        data.push_back(static_cast<gsc::node_integer*>(vec->x.get())->value);
    else if(vec->x->type == gsc::node_type::data_float)
        data.push_back(static_cast<gsc::node_float*>(vec->x.get())->value);
    
    if(vec->y->type == gsc::node_type::data_integer)
        data.push_back(static_cast<gsc::node_integer*>(vec->y.get())->value);
    else if(vec->y->type == gsc::node_type::data_float)
        data.push_back(static_cast<gsc::node_float*>(vec->y.get())->value);
    
    if(vec->z->type == gsc::node_type::data_integer)
        data.push_back(static_cast<gsc::node_integer*>(vec->z.get())->value);
    else if(vec->z->type == gsc::node_type::data_float)
        data.push_back(static_cast<gsc::node_float*>(vec->z.get())->value);

    emit_opcode(ctx, opcode::OP_GetVector, data);
}

void compiler::emit_float(const gsc::context_ptr& ctx, const gsc::float_ptr& num)
{
    emit_opcode(ctx, opcode::OP_GetFloat, num->value);
}

void compiler::emit_integer(const gsc::context_ptr& ctx, const gsc::integer_ptr& num)
{
    auto value = std::atol(num->value.data());

    if(value == 0)
    {
        emit_opcode(ctx, opcode::OP_GetZero);
    }
    else if(value > 0 && value < 255)
    {
        emit_opcode(ctx, opcode::OP_GetByte, num->value);
    }
    else if(value < 0 && value >= -256)
    {
        emit_opcode(ctx, opcode::OP_GetNegByte, num->value);
    }
    else if(value < 65535)
    {
        emit_opcode(ctx, opcode::OP_GetUnsignedShort, num->value);
    }
    else if(value < 0 && value >= -65536)
    {
        emit_opcode(ctx, opcode::OP_GetNegUnsignedShort, num->value);
    }
    else
    {
        emit_opcode(ctx, opcode::OP_GetInteger, num->value);
    } 
}

void compiler::emit_localized_string(const gsc::context_ptr& ctx, const gsc::localized_string_ptr& str)
{
    emit_opcode(ctx, opcode::OP_GetIString, str->value);
}

void compiler::emit_string(const gsc::context_ptr& ctx, const gsc::string_ptr& str)
{
    emit_opcode(ctx, opcode::OP_GetString, str->value);
}

void compiler::emit_opcode(const gsc::context_ptr& ctx, opcode op)
{
    function_->instructions.push_back(std::make_unique<gsc::instruction>());
    
    auto& inst = function_->instructions.back();
    inst->opcode = static_cast<std::uint8_t>(op);
    inst->size = opcode_size(op);
    inst->index = index_;

    index_ += inst->size;
}

void compiler::emit_opcode(const gsc::context_ptr& ctx, opcode op, const std::string& data)
{
    function_->instructions.push_back(std::make_unique<gsc::instruction>());
    
    auto& inst = function_->instructions.back();
    inst->opcode = static_cast<std::uint8_t>(op);
    inst->size = opcode_size(op);
    inst->index = index_;
    inst->data.push_back(data);

    index_ += inst->size;
}

void compiler::emit_opcode(const gsc::context_ptr& ctx, opcode op, const std::vector<std::string>& data)
{
    function_->instructions.push_back(std::make_unique<gsc::instruction>());
    
    auto& inst = function_->instructions.back();
    inst->opcode = static_cast<std::uint8_t>(op);
    inst->size = opcode_size(op);
    inst->index = index_;
    inst->data = data;

    index_ += inst->size;
}

void compiler::calc_local_vars(const gsc::context_ptr& ctx, const gsc::thread_ptr& thread)
{
    calc_local_vars_parameters(ctx, thread->params);
    calc_local_vars_block(ctx, thread->block);
}

void compiler::calc_local_vars_parameters(const gsc::context_ptr& ctx, const gsc::parameters_ptr& params)
{
    for(const auto& param : params->list)
    {
        auto it = std::find(ctx->local_vars.begin(), ctx->local_vars.end(), param->value);

        if(it == ctx->local_vars.end())
        {
            ctx->local_vars.push_back(param->value);
            ctx->local_vars_init.push_back(true);
            ctx->local_vars_create_count++;
        }
    }
}

void compiler::calc_local_vars_block(const gsc::context_ptr& ctx, const gsc::block_ptr& block)
{
    for(const auto& stmt : block->stmts)
    {
        switch(stmt.as_node->type)
        {
            case gsc::node_type::stmt_assign:   calc_local_vars_expr(ctx, stmt.as_assign->expr->lvalue); break;
            case gsc::node_type::stmt_waittill: calc_local_vars_waittill(ctx, stmt.as_waittill); break;
            case gsc::node_type::stmt_for:      calc_local_vars_for(ctx, stmt.as_for); break;
            case gsc::node_type::stmt_foreach: /* foreach pre assign */ break;
            default: break;
        }
    }
}

void compiler::calc_local_vars_expr(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr)
{
    if(expr.as_node->type == gsc::node_type::identifier)
    {
        calc_local_vars_variable(ctx, expr.as_identifier->value);
    }
    else if(expr.as_node->type == gsc::node_type::expr_array)
    {
        calc_local_vars_expr(ctx, expr.as_array->obj);
    }
}

void compiler::calc_local_vars_variable(const gsc::context_ptr& ctx, const std::string& name)
{
    auto it = std::find(ctx->local_vars.begin(), ctx->local_vars.end(), name);

    if(it == ctx->local_vars.end())
    {
        ctx->local_vars.push_back(name);
        ctx->local_vars_init.push_back(false);
    }
}

void compiler::calc_local_vars_waittill(const gsc::context_ptr& ctx, const gsc::stmt_waittill_ptr& stmt)
{
    std::reverse(stmt->args->list.begin(), stmt->args->list.end());

    for(const auto& arg : stmt->args->list)
    {
        auto it = std::find(ctx->local_vars.begin(), ctx->local_vars.end(), arg.as_identifier->value);

        if(it == ctx->local_vars.end())
        {
            ctx->local_vars.push_back(arg.as_identifier->value);
            ctx->local_vars_init.push_back(false);
        }
    }

    std::reverse(stmt->args->list.begin(), stmt->args->list.end());
}

void compiler::calc_local_vars_for(const gsc::context_ptr& ctx, const gsc::stmt_for_ptr& stmt)
{
    // TODO: modify this
    if(stmt->pre_expr.as_node->type == gsc::node_type::expr_assign_equal)
    {
        calc_local_vars_expr(ctx, stmt->pre_expr.as_assign->lvalue);
    }
}

void compiler::create_local_var(const gsc::context_ptr& ctx, const std::string& name)
{
    auto i = 0;

    for(const auto& var : ctx->local_vars)
    {
        if(var == name)
        {
            if(!ctx->local_vars_init.at(i))
            {
                emit_opcode(ctx, opcode::OP_CreateLocalVariable, utils::string::va("%d", i));
                ctx->local_vars_init.at(i) = true;
                ctx->local_vars_create_count++;
            }
            return;
        }
    }

    GSC_COMP_ERROR("local variable '%s' not found.", name.data());
}

auto compiler::find_local_var_create_index(const gsc::context_ptr& ctx, const std::string& name) -> std::int8_t
{
    auto i = 0;

    for(auto& var : ctx->local_vars)
    {
        if(var == name) return i;
        i++;
    }

    GSC_COMP_ERROR("local variable '%s' not found.", name.data());
    return -1;
}

auto compiler::find_local_var_index(const gsc::context_ptr& ctx, const std::string& name) -> std::int8_t
{
    auto i = 0;

    for(auto& var : ctx->local_vars)
    {
        if(var == name)
        {
            if(!ctx->local_vars_init.at(i))
            {
                GSC_COMP_ERROR("local variable '%s' not initialized", name.data());
            }

            return ctx->local_vars_create_count - 1 - i;
        }
        
        i++;
    }

    GSC_COMP_ERROR("local variable '%s' not found.", name.data());
    return -1;
}

auto compiler::is_local_var_initialized(const gsc::context_ptr& ctx, const std::string& name) -> bool
{
    auto i = 0;

    for(auto& var : ctx->local_vars)
    {
        if(var == name)
        {
            if(!ctx->local_vars_init.at(i)) return false;

            return true;
        }
        
        i++;
    }

    GSC_COMP_ERROR("local variable '%s' not found.", name.data());
    return false;
}

auto compiler::is_local_call(const std::string& name) -> bool
{
    for(const auto& f : local_functions_)
    {
        if(f == name) return true;
    }

    return false;
}

auto compiler::is_builtin_call(const std::string& name) -> bool
{
    if(is_builtin_func(name)) return true;
    
    if(is_builtin_method(name)) return true;

    return false;
}

auto compiler::is_builtin_func(const std::string& name) -> bool
{
    return resolver::find_builtin_func(name);
}
auto compiler::is_builtin_method(const std::string& name) -> bool
{
    return resolver::find_builtin_meth(name);
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

void compiler::print_debug_info()
{
    GSC_LOG_DEBUG("----------------------------------");
    GSC_LOG_DEBUG("files included: %zu", includes_.size());
    GSC_LOG_DEBUG("animtrees used: %zu", animtrees_.size());
    GSC_LOG_DEBUG("functions compiled: %zu",assembly_.size());

    for (auto& func : assembly_)
    {
        this->print_function(func);

        for (auto& inst : func->instructions)
        {
            const auto itr = func->labels.find(inst->index);

            if (itr != func->labels.end())
            {
                this->print_label(itr->second);
            }

            this->print_instruction(inst);
        }
    }

    GSC_LOG_DEBUG("----------------------------------");
}

void compiler::print_opcodes(std::uint32_t index, std::uint32_t size)
{
    printf("    ");
}

void compiler::print_function(const gsc::function_ptr& func)
{
    printf("\n");
    printf("%s\n", func->name.data());
}

void compiler::print_instruction(const gsc::instruction_ptr& inst)
{
    switch (opcode(inst->opcode))
    {
    case opcode::OP_endswitch:
        this->print_opcodes(inst->index, 3);
        printf("%s", resolver::opcode_name(opcode(inst->opcode)).data());
        printf(" %s\n", inst->data[0].data());
        {
            std::uint32_t totalcase = std::stoul(inst->data[0]);
            auto index = 0;
            for (auto casenum = 0u; casenum < totalcase; casenum++)
            {
                this->print_opcodes(inst->index, 7);
                if (inst->data[1 + index] == "case")
                {
                    printf("%s %s %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data(), inst->data[1 + index + 2].data());
                    index += 3;
                }
                else if (inst->data[1 + index] == "default")
                {
                    printf("%s %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data());
                    index += 2;
                }
                if (casenum != totalcase - 1)
                {
                    printf("\n");
                }
            }
        }
        break;
    default:
        this->print_opcodes(inst->index, inst->size);
        printf("%s", resolver::opcode_name(opcode(inst->opcode)).data());
        for (auto& d : inst->data)
        {
            printf(" %s", d.data());
        }
        break;
    }

    printf("\n");
}

void compiler::print_label(const std::string& label)
{
    printf("  %s\n", label.data());
}

} // namespace IW7
