// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc::t6
{

class decompiler : public arc::decompiler
{
    std::string filename_;
    ast::program::ptr program_;
    ast::decl_thread::ptr func_;
    std::unordered_map<std::uint32_t, std::string> labels_;
    std::vector<std::string> expr_labels_;
    std::vector<std::string> tern_labels_;
    std::stack<ast::node::ptr> stack_;
    std::vector<std::string> locals_;
    std::vector<block> blocks_;
    bool in_waittill_;
    bool retbool_;
    int retnum_;

public:
    auto output() -> std::vector<std::uint8_t>;
    void decompile(const std::string& file, const assembly::ptr& data);

private:
    void decompile_function(const function::ptr& func);
    void decompile_instruction(const instruction::ptr& inst, bool last);
    void decompile_expressions(const instruction::ptr& inst);
    void decompile_statements(const ast::stmt_list::ptr& stmt);
    void decompile_infinites(const ast::stmt_list::ptr& stmt);
    void decompile_loops(const ast::stmt_list::ptr& stmt);
    void decompile_switches(const ast::stmt_list::ptr& stmt);
    void decompile_ifelses(const ast::stmt_list::ptr& stmt);
    void decompile_aborts(const ast::stmt_list::ptr& stmt);
    void decompile_devblocks(const ast::stmt_list::ptr& stmt);
    void decompile_if(const ast::stmt_list::ptr& stmt, std::uint32_t begin, std::uint32_t end);
    void decompile_ifelse(const ast::stmt_list::ptr& stmt, std::uint32_t begin, std::uint32_t end);
    void decompile_infinite(const ast::stmt_list::ptr& stmt, std::uint32_t begin, std::uint32_t end);
    void decompile_loop(const ast::stmt_list::ptr& stmt, std::uint32_t begin, std::uint32_t end);
    void decompile_while(const ast::stmt_list::ptr& stmt, std::uint32_t begin, std::uint32_t end);
    void decompile_dowhile(const ast::stmt_list::ptr& stmt, std::uint32_t begin, std::uint32_t end);
    void decompile_for(const ast::stmt_list::ptr& stmt, std::uint32_t begin, std::uint32_t end);
    void decompile_foreach(const ast::stmt_list::ptr& stmt, std::uint32_t begin, std::uint32_t end);
    void decompile_switch(const ast::stmt_list::ptr& stmt, std::uint32_t begin);
    auto find_location_reference(const ast::stmt_list::ptr& stmt, std::uint32_t begin, std::uint32_t end, const std::string& location) -> bool;
    auto find_location_index(const ast::stmt_list::ptr& stmt, const std::string& location) -> std::uint32_t;
    auto last_location_index(const ast::stmt_list::ptr& stmt, std::uint32_t index) -> bool;
    auto lvalues_match(const ast::stmt_assign::ptr& stmt1, const ast::stmt_assign::ptr& stmt2) -> bool;
    auto resolve_label(const std::string& name) -> std::int32_t;
    void process_thread(const ast::decl_thread::ptr& thread);
    void process_stmt(const ast::stmt& stmt);
    void process_stmt_list(const ast::stmt_list::ptr& stmt);
    void process_stmt_dev(const ast::stmt_dev::ptr& stmt);
    void process_stmt_expr(const ast::stmt_expr::ptr& stmt);
    void process_stmt_call(const ast::stmt_call::ptr& stmt);
    void process_stmt_assign(const ast::stmt_assign::ptr& stmt);
    void process_stmt_endon(const ast::stmt_endon::ptr& stmt);
    void process_stmt_notify(const ast::stmt_notify::ptr& stmt);
    void process_stmt_wait(const ast::stmt_wait::ptr& stmt);
    void process_stmt_waittill(const ast::stmt_waittill::ptr& stmt);
    void process_stmt_waittillmatch(const ast::stmt_waittillmatch::ptr& stmt);
    void process_stmt_if(const ast::stmt_if::ptr& stmt);
    void process_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt);
    void process_stmt_while(const ast::stmt_while::ptr& stmt);
    void process_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt);
    void process_stmt_for(const ast::stmt_for::ptr& stmt);
    void process_stmt_foreach(const ast::stmt_foreach::ptr& stmt);
    void process_stmt_switch(const ast::stmt_switch::ptr& stmt);
    void process_stmt_cases(const ast::stmt_list::ptr& stmt);
    void process_stmt_return(const ast::stmt_return::ptr& stmt);
    void process_expr(const ast::expr& expr);
    void process_expr_assign(ast::expr_assign::ptr& expr);
    void process_expr_increment(const ast::expr_increment::ptr& expr);
    void process_expr_decrement(const ast::expr_decrement::ptr& expr);
    void process_expr_ternary(const ast::expr_ternary::ptr& expr);
    void process_expr_binary(const ast::expr_binary::ptr& expr);
    void process_expr_and(const ast::expr_and::ptr& expr);
    void process_expr_or(const ast::expr_or::ptr& expr);
    void process_expr_complement(const ast::expr_complement::ptr& expr);
    void process_expr_not(const ast::expr_not::ptr& expr);
    void process_expr_call(const ast::expr_call::ptr& expr);
    void process_expr_method(const ast::expr_method::ptr& expr);
    void process_expr_call_pointer(const ast::expr_pointer::ptr& expr);
    void process_expr_call_function(const ast::expr_function::ptr& expr);
    void process_expr_method_pointer(const ast::expr_pointer::ptr& expr, ast::expr& obj);
    void process_expr_method_function(const ast::expr_function::ptr& expr, ast::expr& obj);
    void process_expr_arguments(const ast::expr_arguments::ptr& expr);
    void process_expr_size(const ast::expr_size::ptr& expr);
    void process_array_variable(const ast::expr_array::ptr& expr);
    void process_field_variable(const ast::expr_field::ptr& expr);
    void process_expr_vector(const ast::expr_vector::ptr& vec);
};

} // namespace xsk::arc::t6
