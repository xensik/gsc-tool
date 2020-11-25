// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW6_COMPILER_HPP_
#define _GSC_IW6_COMPILER_HPP_

namespace IW6
{

enum class opcode : std::uint8_t;

class compiler : public gsc::compiler
{
	std::vector<gsc::function_ptr> 	assembly_;
	gsc::function_ptr 				function_;
	std::uint32_t 					index_;
	std::vector<std::string> 		local_functions_;
	std::vector<std::string> 		includes_;
	std::vector<std::string> 		animtrees_;
	std::vector<std::string> 		local_vars_;
	std::vector<std::string> 		param_vars_;
	std::uint32_t 					label_idx_;
	std::vector<gsc::block> 		blocks_;

public:
	auto output() -> std::vector<gsc::function_ptr>;
	void compile(std::string& data);

private:
	auto parse_buffer(std::string& data) -> gsc::script_ptr;
	auto parse_file(const std::string& file) -> gsc::script_ptr;
	void compile_script(const gsc::script_ptr& script);
	void emit_include(const gsc::include_ptr& include);
	void emit_using_animtree(const gsc::using_animtree_ptr& animtree);
	void emit_thread(const gsc::thread_ptr& thread);
	void emit_parameters(const gsc::parameters_ptr& params);
	void emit_block(const gsc::block_ptr& block, bool last);
	void emit_statement(const gsc::stmt_ptr& stmt, bool last);
	void emit_statement_call(const gsc::stmt_call_ptr& stmt);
	void emit_statement_assign(const gsc::stmt_assign_ptr& stmt);
	void emit_statement_endon(const gsc::stmt_endon_ptr& stmt);
	void emit_statement_notify(const gsc::stmt_notify_ptr& stmt);
	void emit_statement_wait(const gsc::stmt_wait_ptr& stmt);
	void emit_statement_waittill(const gsc::stmt_waittill_ptr& stmt);
	void emit_statement_waittillmatch(const gsc::stmt_waittillmatch_ptr& stmt);
	void emit_statement_waittillframeend(const gsc::stmt_waittillframeend_ptr& stmt);
	void emit_statement_if(const gsc::stmt_if_ptr& stmt, bool last);
	void emit_statement_ifelse(const gsc::stmt_ifelse_ptr& stmt, bool last);
	void emit_statement_while(const gsc::stmt_while_ptr& stmt);
	void emit_statement_for(const gsc::stmt_for_ptr& stmt);
	void emit_statement_foreach(const gsc::stmt_foreach_ptr& stmt);
	void emit_statement_switch(const gsc::stmt_switch_ptr& stmt);
	void emit_statement_case(const gsc::stmt_case_ptr& stmt);
	void emit_statement_default(const gsc::stmt_default_ptr& stmt);
	void emit_statement_break(const gsc::stmt_break_ptr& stmt);
	void emit_statement_continue(const gsc::stmt_continue_ptr& stmt);
	void emit_statement_return(const gsc::stmt_return_ptr& stmt);
	void emit_expression(const gsc::expr_ptr& expr);
	void emit_expr_assign(const gsc::expr_assign_ptr& expr);
	void emit_expr_ternary(const gsc::expr_ternary_ptr& expr);
	void emit_expr_binary(const gsc::expr_binary_ptr& expr);
	void emit_expr_and(const gsc::expr_and_ptr& expr);
	void emit_expr_or(const gsc::expr_or_ptr& expr);
	void emit_expr_complement(const gsc::expr_complement_ptr& expr);
	void emit_expr_not(const gsc::expr_not_ptr& expr);
	void emit_expr_call(const gsc::expr_call_ptr& expr);
	void emit_expr_call_pointer(int args, bool builtin, bool method, bool thread, bool child);
	void emit_expr_call_far(const std::string& file, const std::string& func, int args, bool method, bool thread, bool child);
	void emit_expr_call_local(const std::string& func, int args, bool method, bool thread, bool child);
	void emit_expr_call_builtin(const std::string& func, int args, bool method);
	void emit_expr_arguments(const gsc::expr_arguments_ptr& arg_list);
	void emit_expr_function_ref(const gsc::expr_function_ref_ptr& node);
	void emit_size(const gsc::expr_size_ptr& expr);
	void emit_variable_ref(const gsc::expr_ptr& expr, bool set);
	void emit_array_variable_ref(const gsc::expr_array_ptr& expr, bool set);
	void emit_field_variable_ref(const gsc::expr_field_ptr& expr, bool set);
	void emit_local_variable_ref(const gsc::identifier_ptr& expr, bool set);
	void emit_array_variable(const gsc::expr_array_ptr& expr);
	void emit_field_variable(const gsc::expr_field_ptr& expr);
	void emit_local_variable(const gsc::identifier_ptr& expr);
	void emit_expr_vector(const gsc::expr_vector_ptr& expr);
	void emit_expr_add_array(const gsc::expr_add_array_ptr& expr);
	void emit_object(const gsc::expr_ptr& expr);
	void emit_vector(const gsc::vector_ptr& vec);
	void emit_float(const gsc::float_ptr& num);
	void emit_integer(const gsc::integer_ptr& num);
	void emit_localized_string(const gsc::localized_string_ptr& str);
	void emit_string(const gsc::string_ptr& str);
	auto emit_instruction(opcode op) -> const gsc::instruction_ptr&;

	// helper
	auto get_local_var_index(const gsc::node_ptr& var) -> std::uint8_t;
	auto is_parameter_var(const gsc::node_ptr& var) -> bool;
	auto is_local_var(const gsc::identifier_ptr& var) -> bool;
	auto is_local_call(const gsc::identifier_ptr& func) -> bool;
	auto is_builtin_call(const gsc::identifier_ptr& func) -> bool;
	auto is_builtin_func(const gsc::identifier_ptr& func) -> bool;
	auto is_builtin_method(const gsc::identifier_ptr& func) -> bool;
	auto create_label() -> std::string;
	auto insert_label() -> std::string;
	void insert_label(const std::string& label);
	void transfer_block(const gsc::block& parent, gsc::block& child);

	// debug
	void print_opcodes(std::uint32_t index, std::uint32_t size);
	void print_function(const gsc::function_ptr& func);
	void print_instruction(const gsc::instruction_ptr& inst);
	void print_label(const std::string& label);
};

} // namespace IW6

#endif // _GSC_IW6_COMPILER_HPP_
