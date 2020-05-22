#pragma once
#include "parsetree.hpp"

_GSC_BEGIN

class compiler
{
public:
	void compile(sval_u rootnode);
	void output();

private:
	void emit_function_list();
	void emit_function();
	void emit_parameter_list();
	void emit_end();
	void emit_statement_list();
	void emit_statement();
	void emit_expression();
	void emit_expression_list();
	void emit_or_eval_expression();
	void emit_or_eval_primite_expresion();
	void emit_primetive_expression();
	void emit_assignment_statement();
	void emit_call_expresion_statement();
	void emit_return_statement();
	void emit_end_statement();
	void emit_wait_statement();
	void emit_if_statement();
	void emit_if_else_statement();
	void emit_while_statement();
	void emit_for_statement();
	void emit_inc_statement();
	void emit_dec_statement();
	void emit_binary_equals_operator_expresion();
	void emit_waittill_statement();
	void emit_waittillmatch_statement();
	void emit_waittillframe_statement();
	void emit_notify_statement();
	void emit_endon_statement();
	void emit_switch_statement();
	void emit_switch_statement_list();
	void emit_case_statement();
	void emit_default_statement();
	void emit_break_statement();
	void emit_continue_statement();
	void emit_call_expresion();
	void emit_call();
	void emit_method();
	void emit_pre_function_call();
	void emit_post_function_call();
	void emit_variable_expression();
	void emit_get_function();
	void emit_call_expression();
	void emit_self();
	void emit_level();
	void emit_game();
	void emit_anim();
	void emit_or_eval_primitive_expression_list();
	void emit_size();
	void emit_empty_array();
	void emit_animation();
	void emit_animtree();
	void emit_breakon();
	void emit_set_Variable_field();
	void emit_local_variable();
	void emit_array_variable();
	void emit_field_variable();
	void emit_primitive_expression_field_object();
	void emit_object();
	void emit_opcode();
	void emit_string();
	void emit_eval_array();
	void emit_value();
	void emit_get_undefined();
	void emit_get_string();
	void emit_get_istring();
	void emit_get_vector();
	void emit_get_float();
	void emit_get_integer();
	void emit_dec_top();
	void emit_bool_or_expression();
	void emit_bool_and_expression();
	void emit_cast_bool();
	void emit_or_eval_binary_operator_expresion();
	void emit_bool_not();
	void emit_bool_complement();
};

_GSC_END
