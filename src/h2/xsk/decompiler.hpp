// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::h2
{

class decompiler : public gsc::decompiler
{
    std::string filename_;
    std::unique_ptr<utils::byte_buffer> output_;
    gsc::program_ptr program_;
    gsc::thread_ptr func_;
    std::unordered_map<std::uint32_t, std::string> labels_;
    std::vector<std::string> expr_labels_;
    std::vector<std::string> tern_labels_;
    std::stack<gsc::node_ptr> stack_;
    std::vector<gsc::context> blocks_;

public:
    auto output() -> std::vector<std::uint8_t>;
    void decompile(const std::string& file, std::vector<gsc::function_ptr>& functions);

private:
    void decompile_function(const gsc::function_ptr& func);
    void decompile_statements(const gsc::function_ptr& func);
    void decompile_expr();
    void decompile_ternary();
    void decompile_block(const gsc::stmt_list_ptr& block);
    void decompile_search_infinite(const gsc::stmt_list_ptr& block);
    void decompile_search_loop(const gsc::stmt_list_ptr& block);
    void decompile_search_switch(const gsc::stmt_list_ptr& block);
    void decompile_search_ifelse(const gsc::stmt_list_ptr& block);
    void decompile_break_continue(const gsc::stmt_list_ptr& block);
    void decompile_if(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_ifelse(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_last_ifelse(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_infinite(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_loop(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_while(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_for(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_foreach(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_switch(const gsc::stmt_list_ptr& block, std::uint32_t start);
    auto find_location_reference(const gsc::stmt_list_ptr& block, std::uint32_t start, std::uint32_t end, const std::string& location) -> bool;
    auto find_location_index(const gsc::stmt_list_ptr& block, const std::string& location) -> std::uint32_t;
    auto last_location_index(const gsc::stmt_list_ptr& block, std::uint32_t index) -> bool;
    void process_stack(const gsc::thread_ptr& thread);
    void process_parameters(const gsc::context_ptr& ctx, const gsc::parameters_ptr& params);
    void process_stmt(const gsc::context_ptr& ctx, const gsc::stmt_ptr& stmt);
    void process_stmt_list(const gsc::context_ptr& ctx, const gsc::stmt_list_ptr& stmt);
    void process_stmt_call(const gsc::context_ptr& ctx, const gsc::stmt_call_ptr& stmt);
    void process_stmt_assign(const gsc::context_ptr& ctx, const gsc::stmt_assign_ptr& stmt);
    void process_stmt_endon(const gsc::context_ptr& ctx, const gsc::stmt_endon_ptr& stmt);
    void process_stmt_notify(const gsc::context_ptr& ctx, const gsc::stmt_notify_ptr& stmt);
    void process_stmt_wait(const gsc::context_ptr& ctx, const gsc::stmt_wait_ptr& stmt);
    void process_stmt_waittill(const gsc::context_ptr& ctx, const gsc::stmt_waittill_ptr& stmt);
    void process_stmt_waittillmatch(const gsc::context_ptr& ctx, const gsc::stmt_waittillmatch_ptr& stmt);
    void process_stmt_waittillframeend(const gsc::context_ptr& ctx, const gsc::stmt_waittillframeend_ptr& stmt);
    void process_stmt_if(const gsc::context_ptr& ctx, const gsc::stmt_if_ptr& stmt);
    void process_stmt_ifelse(const gsc::context_ptr& ctx, const gsc::stmt_ifelse_ptr& stmt);
    void process_stmt_while(const gsc::context_ptr& ctx, const gsc::stmt_while_ptr& stmt);
    void process_stmt_for(const gsc::context_ptr& ctx, const gsc::stmt_for_ptr& stmt);
    void process_stmt_foreach(const gsc::context_ptr& ctx, const gsc::stmt_foreach_ptr& stmt);
    void process_stmt_switch(const gsc::context_ptr& ctx, const gsc::stmt_switch_ptr& stmt);
    void process_stmt_cases(const gsc::context_ptr& ctx, const gsc::stmt_list_ptr& stmt);
    void process_stmt_break(const gsc::context_ptr& ctx, const gsc::stmt_break_ptr& stmt);
    void process_stmt_continue(const gsc::context_ptr& ctx, const gsc::stmt_continue_ptr& stmt);
    void process_stmt_return(const gsc::context_ptr& ctx, const gsc::stmt_return_ptr& stmt);
    void process_expr(const gsc::context_ptr& ctx, gsc::expr_ptr& expr);
    void process_expr_assign(const gsc::context_ptr& ctx, gsc::expr_assign_ptr& expr);
    void process_expr_ternary(const gsc::context_ptr& ctx, const gsc::expr_ternary_ptr& expr);
    void process_expr_binary(const gsc::context_ptr& ctx, const gsc::expr_binary_ptr& expr);
    void process_expr_and(const gsc::context_ptr& ctx, const gsc::expr_and_ptr& expr);
    void process_expr_or(const gsc::context_ptr& ctx, const gsc::expr_or_ptr& expr);
    void process_expr_complement(const gsc::context_ptr& ctx, const gsc::expr_complement_ptr& expr);
    void process_expr_not(const gsc::context_ptr& ctx, const gsc::expr_not_ptr& expr);
    void process_expr_call(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr);
    void process_expr_call_pointer(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr);
    void process_expr_call_function(const gsc::context_ptr& ctx, const gsc::expr_call_ptr& expr);
    void process_expr_arguments(const gsc::context_ptr& ctx, const gsc::expr_arguments_ptr& arg_list);
    void process_expr_function(const gsc::context_ptr& ctx, const gsc::expr_function_ptr& node);
    void process_expr_add_array(const gsc::context_ptr& ctx, const gsc::expr_add_array_ptr& expr);
    void process_expr_size(const gsc::context_ptr& ctx, const gsc::expr_size_ptr& expr);
    void process_array_variable(const gsc::context_ptr& ctx, const gsc::expr_array_ptr& expr);
    void process_field_variable(const gsc::context_ptr& ctx, const gsc::expr_field_ptr& expr);
    void process_local_variable(const gsc::context_ptr& ctx, const gsc::name_ptr& expr);
    void process_vector(const gsc::context_ptr& ctx, const gsc::vector_ptr& vec);
    void process_var_create(const gsc::context_ptr& ctx, gsc::expr_ptr& expr, bool fromstmt = false);
    void process_var_access(const gsc::context_ptr& ctx, gsc::expr_ptr& expr);
    void process_var_remove(const gsc::context_ptr& ctx, const gsc::asm_remove_ptr& expr);
};

} // namespace xsk::gsc::h2
