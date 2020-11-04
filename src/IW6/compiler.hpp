// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW6_COMPILER_H_
#define _GSC_IW6_COMPILER_H_

namespace IW6
{

enum class opcode : std::uint8_t;

class compiler : public gsc::compiler
{
public:
    compiler();

	void compile(std::string& buffer);
	auto output() -> std::vector<std::shared_ptr<function>>;

private:
	std::vector<std::shared_ptr<function>> assembly_;
	std::vector<std::string> local_functions_;
	std::vector<std::string> includes_;
	std::vector<std::string> animtrees_;
	std::shared_ptr<function> function_;
	std::uint32_t index_;
	std::vector<std::string> local_vars;
	std::vector<std::string> param_vars;
	std::uint32_t 			label_idx;

	void compile_tree(node_ptr tree);
	void emit_include(const include_ptr& include);
	void emit_using_animtree(const using_animtree_ptr& animtree);
	void emit_function(const function_ptr& function);
	void emit_parameters(const parameters_ptr& params);
	void emit_block(const block_ptr& block);
	void emit_statement(const stmt_ptr& stmt);
	void emit_statement_call(const stmt_call_ptr& stmt);
	void emit_statement_assign(const stmt_assign_ptr& stmt);
	void emit_statement_endon(const stmt_endon_ptr& stmt);
	void emit_statement_notify(const stmt_notify_ptr& stmt);
	void emit_statement_wait(const stmt_wait_ptr& stmt);
	void emit_statement_waittill(const stmt_waittill_ptr& stmt);
	void emit_statement_waittillmatch(const stmt_waittillmatch_ptr& stmt);
	void emit_statement_waittillframeend(const stmt_waittillframeend_ptr& stmt);
	void emit_statement_if(const stmt_if_ptr& stmt);
	void emit_statement_ifelse(const stmt_ifelse_ptr& stmt);
	void emit_statement_while(const stmt_while_ptr& stmt);
	void emit_statement_for(const stmt_for_ptr& stmt);
	void emit_statement_foreach(const stmt_foreach_ptr& stmt);
	void emit_statement_switch(const stmt_switch_ptr& stmt);
	void emit_statement_case(const stmt_case_ptr& stmt);
	void emit_statement_default(const stmt_default_ptr& stmt);
	void emit_statement_break(const stmt_break_ptr& stmt);
	void emit_statement_continue(const stmt_continue_ptr& stmt);
	void emit_statement_return(const stmt_return_ptr& stmt);
	void emit_expression(const expr_ptr& expr);
	void emit_expr_assign(const expr_assign_ptr& expr);
	void emit_expr_ternary(const expr_ternary_ptr& expr);
	void emit_expr_binary(const expr_binary_ptr& expr);
	void emit_expr_and(const expr_and_ptr& expr);
	void emit_expr_or(const expr_or_ptr& expr);
	void emit_expr_complement(const expr_complement_ptr& expr);
	void emit_expr_not(const expr_not_ptr& expr);
	void emit_expr_call(const expr_call_ptr& expr);
	void emit_expr_call_pointer(int args, bool builtin, bool method, bool thread, bool child);
	void emit_expr_call_far(const std::string& file, const std::string& func, int args, bool method, bool thread, bool child);
	void emit_expr_call_local(const std::string& func, int args, bool method, bool thread, bool child);
	void emit_expr_call_builtin(const std::string& func, int args, bool method);
	void emit_expr_arguments(const expr_arguments_ptr& arg_list);
	void emit_expr_function_ref(const expr_function_ref_ptr& node);
	void emit_size(const expr_size_ptr& expr);
	void emit_variable_ref(const expr_ptr& expr, bool set);
	void emit_array_variable_ref(const expr_array_ptr& expr, bool set);
	void emit_field_variable_ref(const expr_field_ptr& expr, bool set);
	void emit_local_variable_ref(const identifier_ptr& expr, bool set);
	void emit_array_variable(const expr_array_ptr& expr);
	void emit_field_variable(const expr_field_ptr& expr);
	void emit_local_variable(const identifier_ptr& expr);
	void emit_expr_vector(const expr_vector_ptr& expr);
	// expr_add_array =>  array = [0, 1, 2];
	void emit_object(const expr_ptr& expr);
	void emit_vector(const vector_ptr& vec);
	void emit_float(const float_ptr& num);
	void emit_integer(const integer_ptr& num);
	void emit_localized_string(const localized_string_ptr& str);
	void emit_string(const string_ptr& str);
	auto emit_instruction(opcode op) -> std::shared_ptr<instruction>;

	// helper
	auto get_local_var_index(const node_ptr& var) -> std::uint8_t;
	auto is_parameter_var(const node_ptr& var) -> bool;
	auto is_local_var(const identifier_ptr& var) -> bool;
	auto is_local_call(const identifier_ptr& func) -> bool;
	auto is_builtin_call(const identifier_ptr& func) -> bool;
	auto is_builtin_func(const identifier_ptr& func) -> bool;
	auto is_builtin_method(const identifier_ptr& func) -> bool;
	auto create_label() -> std::string;
	auto create_label_ahead() -> std::string;
	auto add_label(const std::string& label);
};

} // namespace IW6

#endif // _GSC_IW6_COMPILER_H_
