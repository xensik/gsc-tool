// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/gsc/common/types.hpp"

namespace xsk::gsc
{

struct decompiler
{
private:
    context const* ctx_;
    program::ptr program_;
    decl_function::ptr func_;
    std::unordered_map<usize, std::string> labels_;
    std::vector<std::string> expr_labels_;
    std::vector<std::string> tern_labels_;
    std::stack<node::ptr> stack_;
    bool in_waittill_;
    locjmp locs_;

public:
    explicit decompiler(context const* ctx);
    auto decompile(assembly const& data) -> program::ptr;

private:
    auto decompile_function(function const& func) -> void;
    auto decompile_instruction(instruction const& inst) -> void;
    auto decompile_expressions(instruction const& inst) -> void;
    auto decompile_statements(stmt_list& stm) -> void;
    auto decompile_loops(stmt_list& stm) -> void;
    auto decompile_switches(stmt_list& stm) -> void;
    auto decompile_ifelses(stmt_list& stm) -> void;
    auto decompile_aborts(stmt_list& stm) -> void;
    auto decompile_tuples(stmt_list& stm) -> void;
    auto decompile_if(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_ifelse(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_ifelse_end(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_inf(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_loop(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_while(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_dowhile(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_for(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_foreach(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_switch(stmt_list& stm, usize begin, usize end) -> void;
    auto find_location_reference(stmt_list const& stm, usize begin, usize end, std::string const& loc) -> bool;
    auto find_location_index(stmt_list const& stm, std::string const& loc) -> usize;
    auto last_location_index(stmt_list const& stm, usize index) -> bool;
    auto process_function(decl_function& func) -> void;
    auto process_stmt(stmt& stm, scope& scp) -> void;
    auto process_stmt_list(stmt_list& stm, scope& scp) -> void;
    auto process_stmt_comp(stmt_comp& stm, scope& scp) -> void;
    auto process_stmt_dev(stmt_dev& stm, scope& scp) -> void;
    auto process_stmt_expr(stmt_expr& stm, scope& scp) -> void;
    auto process_stmt_endon(stmt_endon& stm, scope& scp) -> void;
    auto process_stmt_notify(stmt_notify& stm, scope& scp) -> void;
    auto process_stmt_wait(stmt_wait& stm, scope& scp) -> void;
    auto process_stmt_waittill(stmt_waittill& stm, scope& scp) -> void;
    auto process_stmt_waittillmatch(stmt_waittillmatch& stm, scope& scp) -> void;
    auto process_stmt_if(stmt_if& stm, scope& scp) -> void;
    auto process_stmt_ifelse(stmt_ifelse& stm, scope& scp) -> void;
    auto process_stmt_while(stmt_while& stm, scope& scp) -> void;
    auto process_stmt_dowhile(stmt_dowhile& stm, scope& scp) -> void;
    auto process_stmt_for(stmt_for& stm, scope& scp) -> void;
    auto process_stmt_foreach(stmt_foreach& stm, scope& scp) -> void;
    auto process_stmt_switch(stmt_switch& stm, scope& scp) -> void;
    auto process_stmt_break(stmt_break& stm, scope& scp) -> void;
    auto process_stmt_continue(stmt_continue& stm, scope& scp) -> void;
    auto process_stmt_return(stmt_return& stm, scope& scp) -> void;
    auto process_stmt_create(stmt_create& stm, scope& scp) -> void;
    auto process_stmt_remove(stmt_remove& stm, scope& scp) -> void;
    auto process_expr(expr::ptr& exp, scope& scp) -> void;
    auto process_expr_increment(expr_increment& exp, scope& scp) -> void;
    auto process_expr_decrement(expr_decrement& exp, scope& scp) -> void;
    auto process_expr_assign(expr_assign::ptr& exp, scope& scp) -> void;
    auto process_expr_ternary(expr_ternary& exp, scope& scp) -> void;
    auto process_expr_binary(expr_binary& exp, scope& scp) -> void;
    auto process_expr_complement(expr_complement& exp, scope& scp) -> void;
    auto process_expr_not(expr_not& exp, scope& scp) -> void;
    auto process_expr_call(expr_call& exp, scope& scp) -> void;
    auto process_expr_method(expr_method& exp, scope& scp) -> void;
    auto process_expr_call_pointer(expr_pointer& exp, scope& scp) -> void;
    auto process_expr_call_function(expr_function& exp, scope& scp) -> void;
    auto process_expr_method_pointer(expr_pointer& exp, expr::ptr& obj, scope& scp) -> void;
    auto process_expr_method_function(expr_function& exp, expr::ptr& obj, scope& scp) -> void;
    auto process_expr_arguments(expr_arguments& exp, scope& scp) -> void;
    auto process_expr_add_array(expr_add_array& exp, scope& scp) -> void;
    auto process_expr_size(expr_size& exp, scope& scp) -> void;
    auto process_expr_tuple(expr_tuple& exp, scope& scp) -> void;
    auto process_expr_array(expr_array& exp, scope& scp) -> void;
    auto process_expr_field(expr_field& exp, scope& scp) -> void;
    auto process_expr_vector(expr_vector& exp, scope& scp) -> void;
    auto process_expr_var_create(expr::ptr& exp, scope& scp) -> void;
    auto process_expr_var_access(expr::ptr& exp, scope& scp) -> void;
};

} // namespace xsk::gsc
