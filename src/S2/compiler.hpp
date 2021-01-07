// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_S2_COMPILER_HPP_
#define _GSC_S2_COMPILER_HPP_

namespace S2
{

enum class opcode : std::uint8_t;

class compiler : public gsc::compiler
{
    std::vector<gsc::function_ptr> assembly_;
    gsc::function_ptr function_;
    std::uint32_t index_;
    std::uint32_t label_idx_;
    std::vector<std::string> local_functions_;
    std::vector<std::string> includes_;
    std::vector<std::string> animtrees_;

public:
    auto output() -> std::vector<gsc::function_ptr>;
    void compile(std::vector<std::uint8_t>& data);

private:
    auto parse_buffer(std::vector<std::uint8_t>& data) -> gsc::script_ptr;
    auto parse_file(const std::string& file) -> gsc::script_ptr;
    void compile_script(const gsc::script_ptr& script);
    void emit_include(const gsc::include_ptr& include);
    void emit_definition(const gsc::definition_ptr& definition);
    void emit_using_animtree(const gsc::using_animtree_ptr& animtree);
    void emit_constant(const gsc::constant_ptr& constant);
    void emit_thread(const gsc::thread_ptr& thread);
    void emit_parameters(const gsc::context_ptr& ctx, const gsc::parameters_ptr& params);
    void emit_block(const gsc::context_ptr& ctx, const gsc::block_ptr& block, bool last);
    void emit_stmt(const gsc::context_ptr& ctx, const gsc::stmt_ptr& stmt, bool last);
    void emit_stmt_call(const gsc::context_ptr& ctx, const gsc::stmt_call_ptr& stmt);
    void emit_stmt_assign(const gsc::context_ptr& ctx, const gsc::stmt_assign_ptr& stmt);
    void emit_stmt_endon(const gsc::context_ptr& ctx, const gsc::stmt_endon_ptr& stmt);
    void emit_stmt_notify(const gsc::context_ptr& ctx, const gsc::stmt_notify_ptr& stmt);
    void emit_stmt_wait(const gsc::context_ptr& ctx, const gsc::stmt_wait_ptr& stmt);
	void emit_stmt_waitframe(const gsc::context_ptr& ctx, const gsc::stmt_waitframe_ptr& stmt);
    void emit_stmt_waittill(const gsc::context_ptr& ctx, const gsc::stmt_waittill_ptr& stmt);
    void emit_stmt_waittillmatch(const gsc::context_ptr& ctx, const gsc::stmt_waittillmatch_ptr& stmt);
    void emit_stmt_waittillframeend(const gsc::context_ptr& ctx, const gsc::stmt_waittillframeend_ptr& stmt);
    void emit_stmt_if(const gsc::context_ptr& ctx, const gsc::stmt_if_ptr& stmt, bool last);
    void emit_stmt_ifelse(const gsc::context_ptr& ctx, const gsc::stmt_ifelse_ptr& stmt, bool last);
    void emit_stmt_while(const gsc::context_ptr& ctx, const gsc::stmt_while_ptr& stmt);
    void emit_stmt_for(const gsc::context_ptr& ctx, const gsc::stmt_for_ptr& stmt);
    void emit_stmt_foreach(const gsc::context_ptr& ctx, const gsc::stmt_foreach_ptr& stmt);
    void emit_stmt_switch(const gsc::context_ptr& ctx, const gsc::stmt_switch_ptr& stmt);
    void emit_stmt_case(const gsc::context_ptr& ctx, const gsc::stmt_case_ptr& stmt);
    void emit_stmt_default(const gsc::context_ptr& ctx, const gsc::stmt_default_ptr& stmt);
    void emit_stmt_break(const gsc::context_ptr& ctx, const gsc::stmt_break_ptr& stmt);
    void emit_stmt_continue(const gsc::context_ptr& ctx, const gsc::stmt_continue_ptr& stmt);
    void emit_stmt_return(const gsc::context_ptr& ctx, const gsc::stmt_return_ptr& stmt);
    void emit_expr(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr);
    void emit_expr_assign(const gsc::context_ptr& ctx, const gsc::expr_assign_ptr& expr);
    void emit_expr_ternary(const gsc::context_ptr& ctx, const gsc::expr_ternary_ptr& expr);
    void emit_expr_binary(const gsc::context_ptr& ctx, const gsc::expr_binary_ptr& expr);
    void emit_expr_and(const gsc::context_ptr& ctx, const gsc::expr_and_ptr& expr);
    void emit_expr_or(const gsc::context_ptr& ctx, const gsc::expr_or_ptr& expr);
    void emit_expr_complement(const gsc::context_ptr& ctx, const gsc::expr_complement_ptr& expr);
    void emit_expr_not(const gsc::context_ptr& ctx, const gsc::expr_not_ptr& expr);
    void emit_expr_call(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr);
    void emit_expr_call_pointer(const gsc::context_ptr& ctx, int args, bool builtin, bool method, bool thread, bool child);
    void emit_expr_call_far(const gsc::context_ptr& ctx, const std::string& file, const std::string& func, int args, bool method, bool thread, bool child);
    void emit_expr_call_local(const gsc::context_ptr& ctx, const std::string& func, int args, bool method, bool thread, bool child);
    void emit_expr_call_builtin(const gsc::context_ptr& ctx, const std::string& func, int args, bool method);
    void emit_expr_arguments(const gsc::context_ptr& ctx, const gsc::expr_arguments_ptr& arg_list);
    void emit_expr_function_ref(const gsc::context_ptr& ctx, const gsc::expr_function_ref_ptr& node);
    void emit_expr_clear_variable(const gsc::context_ptr& ctx, const gsc::expr_ptr& lvalue);
    void emit_expr_add_array(const gsc::context_ptr& ctx, const gsc::expr_add_array_ptr& expr);
    void emit_expr_vector(const gsc::context_ptr& ctx, const gsc::expr_vector_ptr& expr);
    void emit_expr_size(const gsc::context_ptr& ctx, const gsc::expr_size_ptr& expr);
    void emit_variable_ref(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr, bool set);
    void emit_array_variable_ref(const gsc::context_ptr& ctx, const gsc::expr_array_ptr& expr, bool set);
    void emit_field_variable_ref(const gsc::context_ptr& ctx, const gsc::expr_field_ptr& expr, bool set);
    void emit_local_variable_ref(const gsc::context_ptr& ctx, const gsc::identifier_ptr& expr, bool set);
    void emit_variable(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr);
    void emit_array_variable(const gsc::context_ptr& ctx, const gsc::expr_array_ptr& expr);
    void emit_field_variable(const gsc::context_ptr& ctx, const gsc::expr_field_ptr& expr);
    void emit_local_variable(const gsc::context_ptr& ctx, const gsc::identifier_ptr& expr);
    void emit_create_local_vars(const gsc::context_ptr& ctx);
    void emit_remove_local_vars(const gsc::context_ptr& ctx);
    void emit_object(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr);
    void emit_vector(const gsc::context_ptr& ctx, const gsc::vector_ptr& vec);
    void emit_float(const gsc::context_ptr& ctx, const gsc::float_ptr& num);
    void emit_integer(const gsc::context_ptr& ctx, const gsc::integer_ptr& num);
    void emit_localized_string(const gsc::context_ptr& ctx, const gsc::localized_string_ptr& str);
    void emit_string(const gsc::context_ptr& ctx, const gsc::string_ptr& str);
    void emit_animtree(const gsc::context_ptr& ctx, const gsc::animtree_ptr& tree);
    void emit_animation(const gsc::context_ptr& ctx, const gsc::animref_ptr& anim);
    void emit_true(const gsc::context_ptr& ctx, const gsc::true_ptr& expr);
    void emit_false(const gsc::context_ptr& ctx, const gsc::false_ptr& expr);
    void emit_opcode(const gsc::context_ptr& ctx, opcode op);
    void emit_opcode(const gsc::context_ptr& ctx, opcode op, const std::string& data);
    void emit_opcode(const gsc::context_ptr& ctx, opcode op, const std::vector<std::string>& data);

    void calc_local_vars(const gsc::context_ptr& ctx, const gsc::thread_ptr& thread);
    void calc_local_vars_parameters(const gsc::context_ptr& ctx, const gsc::parameters_ptr& params);
    void calc_local_vars_block(const gsc::context_ptr& ctx, const gsc::block_ptr& block);
    void calc_local_vars_expr(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr);
    void calc_local_vars_variable(const gsc::context_ptr& ctx, const std::string& name);
    void calc_local_vars_waittill(const gsc::context_ptr& ctx, const gsc::stmt_waittill_ptr& stmt);
    void calc_local_vars_for(const gsc::context_ptr& ctx, const gsc::stmt_for_ptr& stmt);

    void create_local_var(const gsc::context_ptr& ctx, const std::string& name);
    auto find_local_var_create_index(const gsc::context_ptr& ctx, const std::string& name) -> std::int8_t;
    auto find_local_var_index(const gsc::context_ptr& ctx, const std::string& name) -> std::int8_t;
    auto is_local_var_initialized(const gsc::context_ptr& ctx, const std::string& name) -> bool;

    auto is_local_call(const std::string& name) -> bool;
    auto is_builtin_call(const std::string& name) -> bool;
    auto is_builtin_func(const std::string& name) -> bool;
    auto is_builtin_method(const std::string& name) -> bool;
    
    auto create_label() -> std::string;
    auto insert_label() -> std::string;
    void insert_label(const std::string& label);

    // debug
    void print_debug_info();
    void print_opcodes(std::uint32_t index, std::uint32_t size);
    void print_function(const gsc::function_ptr& func);
    void print_instruction(const gsc::instruction_ptr& inst);
    void print_label(const std::string& label);
};

} // namespace S2

#endif // _GSC_S2_COMPILER_HPP_
