// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::iw7
{

enum class opcode : std::uint8_t;

class compiler : public gsc::compiler
{
    std::string filename_;
    std::vector<gsc::function_ptr> assembly_;
    gsc::function_ptr function_;
    std::uint32_t index_;
    std::uint32_t label_idx_;
    std::uint8_t stack_idx_;
    std::vector<std::string> local_stack_;
    std::vector<std::string> local_functions_;
    std::vector<include_t> includes_;
    std::vector<animtree_t> animtrees_;
    std::unordered_map<std::string, gsc::expr_ptr> constants_;
    std::function<std::vector<std::uint8_t>(const std::string&)> callback_readf_;
    std::vector<gsc::context*> break_ctxs_;
    std::vector<gsc::context*> continue_ctxs_;
    bool can_break_;
    bool can_continue_;

public:
    auto output() -> std::vector<gsc::function_ptr>;
    void compile(const std::string& file, std::vector<std::uint8_t>& data);
    void set_readf_callback(std::function<std::vector<std::uint8_t>(const std::string&)> func);

private:
    auto parse_buffer(const std::string& file, std::vector<std::uint8_t>& data) -> gsc::program_ptr;
    auto parse_file(const std::string& file) -> gsc::program_ptr;
    void compile_program(const gsc::program_ptr& program);
    void emit_include(const gsc::include_ptr& include);
    void emit_define(const gsc::define_ptr& define);
    void emit_usingtree(const gsc::usingtree_ptr& animtree);
    void emit_constant(const gsc::constant_ptr& constant);
    void emit_thread(const gsc::thread_ptr& thread);
    void emit_parameters(const gsc::context_ptr& ctx, const gsc::parameters_ptr& params);
    void emit_stmt(const gsc::context_ptr& ctx, const gsc::stmt_ptr& stmt, bool last);
    void emit_stmt_list(const gsc::context_ptr& ctx, const gsc::stmt_list_ptr& stmt, bool last);
    void emit_stmt_call(const gsc::context_ptr& ctx, const gsc::stmt_call_ptr& stmt);
    void emit_stmt_assign(const gsc::context_ptr& ctx, const gsc::stmt_assign_ptr& stmt);
    void emit_stmt_endon(const gsc::context_ptr& ctx, const gsc::stmt_endon_ptr& stmt);
    void emit_stmt_notify(const gsc::context_ptr& ctx, const gsc::stmt_notify_ptr& stmt);
    void emit_stmt_wait(const gsc::context_ptr& ctx, const gsc::stmt_wait_ptr& stmt);
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
    void emit_expr_call_pointer(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr);
    void emit_expr_call_pointer_type(const gsc::context_ptr& ctx, int args, bool builtin, bool method, bool thread, bool child);
    void emit_expr_call_function(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr);
    void emit_expr_call_function_builtin(const gsc::context_ptr& ctx, const std::string& func, int args, bool method);
    void emit_expr_call_function_local(const gsc::context_ptr& ctx, const std::string& func, int args, bool method, bool thread, bool child);
    void emit_expr_call_function_far(const gsc::context_ptr& ctx, const std::string& file, const std::string& func, int args, bool method, bool thread, bool child);
    void emit_expr_arguments(const gsc::context_ptr& ctx, const gsc::expr_arguments_ptr& arg_list);
    void emit_expr_function(const gsc::context_ptr& ctx, const gsc::expr_function_ptr& node);
    void emit_expr_clear_variable(const gsc::context_ptr& ctx, const gsc::expr_ptr& lvalue);
    void emit_expr_add_array(const gsc::context_ptr& ctx, const gsc::expr_add_array_ptr& expr);
    void emit_expr_size(const gsc::context_ptr& ctx, const gsc::expr_size_ptr& expr);
    void emit_variable_ref(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr, bool set);
    void emit_array_variable_ref(const gsc::context_ptr& ctx, const gsc::expr_array_ptr& expr, bool set);
    void emit_field_variable_ref(const gsc::context_ptr& ctx, const gsc::expr_field_ptr& expr, bool set);
    void emit_local_variable_ref(const gsc::context_ptr& ctx, const gsc::name_ptr& expr, bool set);
    void emit_variable(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr);
    void emit_array_variable(const gsc::context_ptr& ctx, const gsc::expr_array_ptr& expr);
    void emit_field_variable(const gsc::context_ptr& ctx, const gsc::expr_field_ptr& expr);
    void emit_local_variable(const gsc::context_ptr& ctx, const gsc::name_ptr& expr);
    void emit_clear_local_variable(const gsc::context_ptr& ctx, const gsc::name_ptr& expr);
    void emit_create_local_vars(const gsc::context_ptr& ctx);
    void emit_remove_local_vars(const gsc::context_ptr& ctx);
    void emit_object(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr);
    void emit_animtree(const gsc::context_ptr& ctx, const gsc::animtree_ptr& animtree);
    void emit_animation(const gsc::context_ptr& ctx, const gsc::animation_ptr& animation);
    void emit_istring(const gsc::context_ptr& ctx, const gsc::istring_ptr& str);
    void emit_string(const gsc::context_ptr& ctx, const gsc::string_ptr& str);
    void emit_color(const gsc::context_ptr& ctx, const gsc::color_ptr& color);
    void emit_vector(const gsc::context_ptr& ctx, const gsc::vector_ptr& vec);
    void emit_float(const gsc::context_ptr& ctx, const gsc::float_ptr& num);
    void emit_integer(const gsc::context_ptr& ctx, const gsc::integer_ptr& num);
    void emit_false(const gsc::context_ptr& ctx, const gsc::false_ptr& expr);
    void emit_true(const gsc::context_ptr& ctx, const gsc::true_ptr& expr);
    void emit_opcode(const gsc::context_ptr& ctx, opcode op);
    void emit_opcode(const gsc::context_ptr& ctx, opcode op, const std::string& data);
    void emit_opcode(const gsc::context_ptr& ctx, opcode op, const std::vector<std::string>& data);
    void process_thread(const gsc::context_ptr& ctx, const gsc::thread_ptr& thread);
    void process_parameters(const gsc::context_ptr& ctx, const gsc::parameters_ptr& params);
    void process_stmt(const gsc::context_ptr& ctx, const gsc::stmt_ptr& stmt);
    void process_stmt_list(const gsc::context_ptr& ctx, const gsc::stmt_list_ptr& stmt);
    void process_expr(const gsc::context_ptr& ctx, const gsc::expr_ptr& expr);
    void process_stmt_waittill(const gsc::context_ptr& ctx, const gsc::stmt_waittill_ptr& stmt);
    void process_stmt_if(const gsc::context_ptr& ctx, const gsc::stmt_if_ptr& stmt);
    void process_stmt_ifelse(const gsc::context_ptr& ctx, const gsc::stmt_ifelse_ptr& stmt);
    void process_stmt_while(const gsc::context_ptr& ctx, const gsc::stmt_while_ptr& stmt);
    void process_stmt_for(const gsc::context_ptr& ctx, const gsc::stmt_for_ptr& stmt);
    void process_stmt_foreach(const gsc::context_ptr& ctx, const gsc::stmt_foreach_ptr& stmt);
    void process_stmt_switch(const gsc::context_ptr& ctx, const gsc::stmt_switch_ptr& stmt);
    void process_stmt_break(const gsc::context_ptr& ctx, const gsc::stmt_break_ptr& stmt);
    void process_stmt_continue(const gsc::context_ptr& ctx, const gsc::stmt_continue_ptr& stmt);
    void process_stmt_return(const gsc::context_ptr& ctx, const gsc::stmt_return_ptr& stmt);
    void register_variable(const gsc::context_ptr& ctx, const std::string& name);
    void initialize_variable(const gsc::context_ptr& ctx, const gsc::name_ptr& name);
    void create_variable(const gsc::context_ptr& ctx, const gsc::name_ptr& name);
    auto variable_stack_index(const gsc::context_ptr& ctx, const gsc::name_ptr& name) -> std::uint8_t;
    auto variable_create_index(const gsc::context_ptr& ctx, const gsc::name_ptr& name) -> std::string;
    auto variable_access_index(const gsc::context_ptr& ctx, const gsc::name_ptr& name) -> std::string;
    auto variable_initialized(const gsc::context_ptr& ctx, const gsc::name_ptr& name) -> bool;
    auto is_include_call(const std::string& name, std::string& file) -> bool;
    auto is_local_call(const std::string& name) -> bool;
    auto is_builtin_call(const std::string& name) -> bool;
    auto is_builtin_func(const std::string& name) -> bool;
    auto is_builtin_method(const std::string& name) -> bool;
    auto is_constant_condition(const gsc::expr_ptr& expr) -> bool;
    auto create_label() -> std::string;
    auto insert_label() -> std::string;
    void insert_label(const std::string& label);

    auto map_known_includes(const std::string& include) -> bool;
};

} // namespace xsk::gsc::iw7
