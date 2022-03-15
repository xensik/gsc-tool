// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::iw7
{

enum class opcode : std::uint8_t;

class compiler : public gsc::compiler
{
    build mode_;
    std::string filename_;
    std::vector<function::ptr> assembly_;
    function::ptr function_;
    std::uint32_t index_;
    std::uint32_t label_idx_;
    std::uint8_t stack_idx_;
    std::vector<std::string> local_stack_;
    std::vector<std::string> local_functions_;
    std::vector<include_t> includes_;
    std::vector<animtree_t> animtrees_;
    std::unordered_map<std::string, ast::expr> constants_;
    std::vector<block*> break_blks_;
    std::vector<block*> continue_blks_;
    bool can_break_;
    bool can_continue_;
    bool developer_thread_;

public:
    auto output() -> std::vector<function::ptr>;
    void compile(const std::string& file, std::vector<std::uint8_t>& data);
    void mode(build mode);

private:
    auto parse_buffer(const std::string& file, char* data, size_t size) -> ast::program::ptr;
    auto parse_file(const std::string& file) -> ast::program::ptr;
    void compile_program(const ast::program::ptr& program);
    void emit_include(const ast::include::ptr& include);
    void emit_declaration(const ast::decl& decl);
    void emit_decl_usingtree(const ast::decl_usingtree::ptr& animtree);
    void emit_decl_constant(const ast::decl_constant::ptr& constant);
    void emit_decl_thread(const ast::decl_thread::ptr& thread);
    void emit_stmt(const ast::stmt& stmt, const block::ptr& blk, bool last);
    void emit_stmt_list(const ast::stmt_list::ptr& stmt, const block::ptr& blk, bool last);
    void emit_stmt_dev(const ast::stmt_dev::ptr& stmt, const block::ptr& blk, bool last);
    void emit_stmt_expr(const ast::stmt_expr::ptr& stmt, const block::ptr& blk);
    void emit_stmt_call(const ast::stmt_call::ptr& stmt, const block::ptr& blk);
    void emit_stmt_assign(const ast::stmt_assign::ptr& stmt, const block::ptr& blk);
    void emit_stmt_endon(const ast::stmt_endon::ptr& stmt, const block::ptr& blk);
    void emit_stmt_notify(const ast::stmt_notify::ptr& stmt, const block::ptr& blk);
    void emit_stmt_wait(const ast::stmt_wait::ptr& stmt, const block::ptr& blk);
    void emit_stmt_waittill(const ast::stmt_waittill::ptr& stmt, const block::ptr& blk);
    void emit_stmt_waittillmatch(const ast::stmt_waittillmatch::ptr& stmt, const block::ptr& blk);
    void emit_stmt_waittillframeend(const ast::stmt_waittillframeend::ptr& stmt, const block::ptr& blk);
    void emit_stmt_if(const ast::stmt_if::ptr& stmt, const block::ptr& blk, bool last);
    void emit_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt, const block::ptr& blk, bool last);
    void emit_stmt_while(const ast::stmt_while::ptr& stmt, const block::ptr& blk);
    void emit_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt, const block::ptr& blk);
    void emit_stmt_for(const ast::stmt_for::ptr& stmt, const block::ptr& blk);
    void emit_stmt_foreach(const ast::stmt_foreach::ptr& stmt, const block::ptr& blk);
    void emit_stmt_switch(const ast::stmt_switch::ptr& stmt, const block::ptr& blk);
    void emit_stmt_case(const ast::stmt_case::ptr& stmt, const block::ptr& blk);
    void emit_stmt_default(const ast::stmt_default::ptr& stmt, const block::ptr& blk);
    void emit_stmt_break(const ast::stmt_break::ptr& stmt, const block::ptr& blk);
    void emit_stmt_continue(const ast::stmt_continue::ptr& stmt, const block::ptr& blk);
    void emit_stmt_return(const ast::stmt_return::ptr& stmt, const block::ptr& blk);
    void emit_stmt_breakpoint(const ast::stmt_breakpoint::ptr& stmt, const block::ptr& blk);
    void emit_stmt_prof_begin(const ast::stmt_prof_begin::ptr& stmt, const block::ptr& blk);
    void emit_stmt_prof_end(const ast::stmt_prof_end::ptr& stmt, const block::ptr& blk);
    void emit_expr(const ast::expr& expr, const block::ptr& blk);
    void emit_expr_assign(const ast::expr_assign::ptr& expr, const block::ptr& blk);
    void emit_expr_clear(const ast::expr& expr, const block::ptr& blk);
    void emit_expr_clear_local(const ast::expr_identifier::ptr& expr, const block::ptr& blk);
    void emit_expr_increment(const ast::expr_increment::ptr& expr, const block::ptr& blk, bool stmt);
    void emit_expr_decrement(const ast::expr_decrement::ptr& expr, const block::ptr& blk,  bool stmt);
    void emit_expr_ternary(const ast::expr_ternary::ptr& expr, const block::ptr& blk);
    void emit_expr_binary(const ast::expr_binary::ptr& expr, const block::ptr& blk);
    void emit_expr_and(const ast::expr_and::ptr& expr, const block::ptr& blk);
    void emit_expr_or(const ast::expr_or::ptr& expr, const block::ptr& blk);
    void emit_expr_complement(const ast::expr_complement::ptr& expr, const block::ptr& blk);
    void emit_expr_not(const ast::expr_not::ptr& expr, const block::ptr& blk);
    void emit_expr_call(const ast::expr_call::ptr& expr, const block::ptr& blk);
    void emit_expr_call_pointer(const ast::expr_pointer::ptr& expr, const block::ptr& blk);
    void emit_expr_call_function(const ast::expr_function::ptr& expr, const block::ptr& blk);
    void emit_expr_method(const ast::expr_method::ptr& expr, const block::ptr& blk);
    void emit_expr_method_pointer(const ast::expr_pointer::ptr& expr, const ast::expr& obj, const block::ptr& blk);
    void emit_expr_method_function(const ast::expr_function::ptr& expr, const ast::expr& obj, const block::ptr& blk);
    void emit_expr_add_array(const ast::expr_add_array::ptr& expr, const block::ptr& blk);
    void emit_expr_parameters(const ast::expr_parameters::ptr& expr, const block::ptr& blk);
    void emit_expr_arguments(const ast::expr_arguments::ptr& expr, const block::ptr& blk);
    void emit_expr_reference(const ast::expr_reference::ptr& expr, const block::ptr& blk);
    void emit_expr_size(const ast::expr_size::ptr& expr, const block::ptr& blk);
    void emit_expr_variable_ref(const ast::expr& expr, const block::ptr& blk, bool set);
    void emit_expr_array_ref(const ast::expr_array::ptr& expr, const block::ptr& blk, bool set);
    void emit_expr_field_ref(const ast::expr_field::ptr& expr, const block::ptr& blk, bool set);
    void emit_expr_local_ref(const ast::expr_identifier::ptr& expr, const block::ptr& blk, bool set);
    void emit_expr_variable(const ast::expr& expr, const block::ptr& blk);
    void emit_expr_array(const ast::expr_array::ptr& expr, const block::ptr& blk);
    void emit_expr_field(const ast::expr_field::ptr& expr, const block::ptr& blk);
    void emit_expr_local(const ast::expr_identifier::ptr& expr, const block::ptr& blk);
    void emit_expr_object(const ast::expr& expr, const block::ptr& blk);
    void emit_expr_vector(const ast::expr_vector::ptr& expr, const block::ptr& blk);
    void emit_expr_animation(const ast::expr_animation::ptr& expr);
    void emit_expr_animtree(const ast::expr_animtree::ptr& expr);
    void emit_expr_istring(const ast::expr_istring::ptr& expr);
    void emit_expr_string(const ast::expr_string::ptr& expr);
    void emit_expr_float(const ast::expr_float::ptr& expr);
    void emit_expr_integer(const ast::expr_integer::ptr& expr);
    void emit_expr_false(const ast::expr_false::ptr& expr);
    void emit_expr_true(const ast::expr_true::ptr& expr);
    void emit_create_local_vars(const block::ptr& blk);
    void emit_remove_local_vars(const block::ptr& blk);
    void emit_opcode(opcode op);
    void emit_opcode(opcode op, const std::string& data);
    void emit_opcode(opcode op, const std::vector<std::string>& data);
    void process_thread(const ast::decl_thread::ptr& decl, const block::ptr& blk);
    void process_stmt(const ast::stmt& stmt, const block::ptr& blk);
    void process_stmt_list(const ast::stmt_list::ptr& stmt, const block::ptr& blk);
    void process_stmt_dev(const ast::stmt_dev::ptr& stmt, const block::ptr& blk);
    void process_stmt_expr(const ast::stmt_expr::ptr& stmt, const block::ptr& blk);
    void process_stmt_assign(const ast::stmt_assign::ptr& stmt, const block::ptr& blk);
    void process_stmt_waittill(const ast::stmt_waittill::ptr& stmt, const block::ptr& blk);
    void process_stmt_if(const ast::stmt_if::ptr& stmt, const block::ptr& blk);
    void process_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt, const block::ptr& blk);
    void process_stmt_while(const ast::stmt_while::ptr& stmt, const block::ptr& blk);
    void process_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt, const block::ptr& blk);
    void process_stmt_for(const ast::stmt_for::ptr& stmt, const block::ptr& blk);
    void process_stmt_foreach(const ast::stmt_foreach::ptr& stmt, const block::ptr& blk);
    void process_stmt_switch(const ast::stmt_switch::ptr& stmt, const block::ptr& blk);
    void process_stmt_break(const ast::stmt_break::ptr& stmt, const block::ptr& blk);
    void process_stmt_continue(const ast::stmt_continue::ptr& stmt, const block::ptr& blk);
    void process_stmt_return(const ast::stmt_return::ptr& stmt, const block::ptr& blk);
    void process_expr(const ast::expr& expr, const block::ptr& blk);
    void process_expr_parameters(const ast::expr_parameters::ptr& decl, const block::ptr& blk);
    void register_variable(const std::string& name, const block::ptr& blk);
    void initialize_variable(const ast::expr_identifier::ptr& name, const block::ptr& blk);
    void create_variable(const ast::expr_identifier::ptr& name, const block::ptr& blk);
    auto variable_stack_index(const ast::expr_identifier::ptr& name, const block::ptr& blk) -> std::uint8_t;
    auto variable_create_index(const ast::expr_identifier::ptr& name, const block::ptr& blk) -> std::string;
    auto variable_access_index(const ast::expr_identifier::ptr& name, const block::ptr& blk) -> std::string;
    auto variable_initialized(const ast::expr_identifier::ptr& name, const block::ptr& blk) -> bool;
    auto resolve_function_type(const ast::expr_function::ptr& expr) -> ast::call::type;
    auto resolve_reference_type(const ast::expr_reference::ptr& expr, bool& method) -> ast::call::type;
    auto is_constant_condition(const ast::expr& expr) -> bool;
    auto create_label() -> std::string;
    auto insert_label() -> std::string;
    void insert_label(const std::string& label);

    auto map_known_includes(const std::string& include) -> bool;
};

} // namespace xsk::gsc::iw7
