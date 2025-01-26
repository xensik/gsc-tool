// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/arc/common/types.hpp"

namespace xsk::arc
{

struct decompiler
{
private:
    context const* ctx_;
    program::ptr program_;
    decl_function::ptr func_;
    std::unordered_set<std::string> vars_;
    std::unordered_map<usize, std::string> labels_;
    std::vector<std::string> expr_labels_;
    std::vector<std::string> tern_labels_;
    std::vector<std::string> locals_;
    std::vector<param_type> params_;
    std::stack<node::ptr> stack_;
    std::string namespace_;
    locjmp locs_;
    bool in_waittill_;
    bool retbool_;

public:
    explicit decompiler(context const* ctx);
    auto decompile(assembly const& data) -> program::ptr;

private:
    auto decompile_function(function const& func) -> void;
    auto decompile_instruction(instruction const& inst, bool last) -> void;
    auto decompile_expressions(instruction const& inst) -> void;
    auto decompile_statements(stmt_list& stm) -> void;
    auto decompile_infinites(stmt_list& stm) -> void;
    auto decompile_loops(stmt_list& stm) -> void;
    auto decompile_switches(stmt_list& stm) -> void;
    auto decompile_ifelses(stmt_list& stm) -> void;
    auto decompile_aborts(stmt_list& stm) -> void;
    auto decompile_devblocks(stmt_list& stm) -> void;
    auto decompile_if(stmt_list& stm, usize begin, usize end) -> void;
    auto decompile_ifelse(stmt_list& stm, usize begin, usize end) -> void;
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
    auto lvalues_match(stmt_expr const& stm1, stmt_expr const& stm2) -> bool;
    auto resolve_label(std::string const& name) const -> usize;
    auto process_function(decl_function& func) -> void;
    auto process_stmt(stmt& stm) -> void;
    auto process_stmt_list(stmt_list& stm) -> void;
    auto process_stmt_comp(stmt_comp& stm) -> void;
    auto process_stmt_dev(stmt_dev& stm) -> void;
    auto process_stmt_expr(stmt_expr& stm) -> void;
    auto process_stmt_endon(stmt_endon& stm) -> void;
    auto process_stmt_notify(stmt_notify& stm) -> void;
    auto process_stmt_wait(stmt_wait& stm) -> void;
    auto process_stmt_waitrealtime(stmt_waitrealtime& stm) -> void;
    auto process_stmt_waittill(stmt_waittill& stm) -> void;
    auto process_stmt_waittillmatch(stmt_waittillmatch& stm) -> void;
    auto process_stmt_if(stmt_if& stm) -> void;
    auto process_stmt_ifelse(stmt_ifelse& stm) -> void;
    auto process_stmt_while(stmt_while& stm) -> void;
    auto process_stmt_dowhile(stmt_dowhile& stm) -> void;
    auto process_stmt_for(stmt_for& stm) -> void;
    auto process_stmt_foreach(stmt_foreach& stm) -> void;
    auto process_stmt_switch(stmt_switch& stm) -> void;
    auto process_stmt_break(stmt_break& stm) -> void;
    auto process_stmt_continue(stmt_continue& stm) -> void;
    auto process_stmt_return(stmt_return& stm) -> void;
    auto process_expr(expr::ptr& exp) -> void;
    auto process_expr_increment(expr_increment& exp) -> void;
    auto process_expr_decrement(expr_decrement& exp) -> void;
    auto process_expr_assign(expr_assign::ptr& exp) -> void;
    auto process_expr_ternary(expr_ternary& exp) -> void;
    auto process_expr_binary(expr_binary& exp) -> void;
    auto process_expr_complement(expr_complement& exp) -> void;
    auto process_expr_not(expr_not& exp) -> void;
    auto process_expr_call(expr_call& exp) -> void;
    auto process_expr_method(expr_method& exp) -> void;
    auto process_expr_call_member(expr_member& exp) -> void;
    auto process_expr_call_pointer(expr_pointer& exp) -> void;
    auto process_expr_call_function(expr_function& exp) -> void;
    auto process_expr_method_pointer(expr_pointer& exp, expr::ptr& obj) -> void;
    auto process_expr_method_function(expr_function& exp, expr::ptr& obj) -> void;
    auto process_expr_parameters(expr_parameters& exp) -> void;
    auto process_expr_arguments(expr_arguments& exp) -> void;
    auto process_expr_reference(expr_reference& exp) -> void;
    auto process_expr_array(expr_array& exp) -> void;
    auto process_expr_field(expr_field& exp) -> void;
    auto process_expr_size(expr_size& exp) -> void;
    auto process_expr_vector(expr_vector& exp) -> void;
    auto process_expr_identifier(expr_identifier& exp) -> void;
};

} // namespace xsk::arc
