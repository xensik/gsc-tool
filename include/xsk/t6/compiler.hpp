// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc::t6
{

enum class opcode : std::uint8_t;

class compiler : public arc::compiler
{
    std::string filename_;
    assembly::ptr assembly_;
    function::ptr function_;
    std::uint32_t index_;
    std::uint32_t label_idx_;
    std::uint8_t stack_idx_;
    std::vector<std::string> local_stack_;
    std::vector<std::string> local_functions_;
    std::vector<include_t> includes_;
    std::vector<std::string> animtrees_;
    std::unordered_map<std::string, ast::expr> constants_;
    std::vector<block> blocks_;
    bool can_break_;
    bool can_continue_;
    bool developer_thread_;
    build mode_;
    utils::writer::ptr output_;

public:
    auto output() -> assembly::ptr;
    auto output_raw() -> std::vector<std::uint8_t>;
    void compile(const std::string& file, std::vector<std::uint8_t>& data);
    void mode(build mode);

private:
    auto parse_buffer(const std::string& file, const char* data, size_t size) -> ast::program::ptr;
    auto parse_file(const std::string& file) -> ast::program::ptr;
    void compile_program(const ast::program::ptr& program);
    void emit_include(const ast::include::ptr& include);
    void emit_declaration(const ast::decl& decl);
    void emit_decl_usingtree(const ast::decl_usingtree::ptr& animtree);
    void emit_decl_thread(const ast::decl_thread::ptr& thread);
    void emit_stmt(const ast::stmt& stmt);
    void emit_stmt_list(const ast::stmt_list::ptr& stmt);
    void emit_stmt_dev(const ast::stmt_dev::ptr& stmt);
    void emit_stmt_expr(const ast::stmt_expr::ptr& stmt);
    void emit_stmt_call(const ast::stmt_call::ptr& stmt);
    void emit_stmt_const(const ast::stmt_const::ptr& stmt);
    void emit_stmt_assign(const ast::stmt_assign::ptr& stmt);
    void emit_stmt_endon(const ast::stmt_endon::ptr& stmt);
    void emit_stmt_notify(const ast::stmt_notify::ptr& stmt);
    void emit_stmt_wait(const ast::stmt_wait::ptr& stmt);
    void emit_stmt_waittill(const ast::stmt_waittill::ptr& stmt);
    void emit_stmt_waittillmatch(const ast::stmt_waittillmatch::ptr& stmt);
    void emit_stmt_waittillframeend(const ast::stmt_waittillframeend::ptr& stmt);
    void emit_stmt_if(const ast::stmt_if::ptr& stmt);
    void emit_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt);
    void emit_stmt_while(const ast::stmt_while::ptr& stmt);
    void emit_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt);
    void emit_stmt_for(const ast::stmt_for::ptr& stmt);
    void emit_stmt_foreach(const ast::stmt_foreach::ptr& stmt);
    void emit_stmt_switch(const ast::stmt_switch::ptr& stmt);
    void emit_stmt_case(const ast::stmt_case::ptr& stmt);
    void emit_stmt_default(const ast::stmt_default::ptr& stmt);
    void emit_stmt_break(const ast::stmt_break::ptr& stmt);
    void emit_stmt_continue(const ast::stmt_continue::ptr& stmt);
    void emit_stmt_return(const ast::stmt_return::ptr& stmt);
    void emit_stmt_prof_begin(const ast::stmt_prof_begin::ptr& stmt);
    void emit_stmt_prof_end(const ast::stmt_prof_end::ptr& stmt);
    void emit_expr(const ast::expr& expr);
    void emit_expr_assign(const ast::expr_assign::ptr& expr);
    void emit_expr_clear(const ast::expr& expr);
    void emit_expr_increment(const ast::expr_increment::ptr& expr, bool is_stmt);
    void emit_expr_decrement(const ast::expr_decrement::ptr& expr, bool is_stmt);
    void emit_expr_ternary(const ast::expr_ternary::ptr& expr);
    void emit_expr_binary(const ast::expr_binary::ptr& expr);
    void emit_expr_and(const ast::expr_and::ptr& expr);
    void emit_expr_or(const ast::expr_or::ptr& expr);
    void emit_expr_complement(const ast::expr_complement::ptr& expr);
    void emit_expr_negate(const ast::expr_negate::ptr& expr);
    void emit_expr_not(const ast::expr_not::ptr& expr);
    void emit_expr_call(const ast::expr_call::ptr& expr, bool is_stmt);
    void emit_expr_call_pointer(const ast::expr_pointer::ptr& expr, bool is_stmt);
    void emit_expr_call_function(const ast::expr_function::ptr& expr, bool is_stmt);
    void emit_expr_method(const ast::expr_method::ptr& expr, bool is_stmt);
    void emit_expr_method_pointer(const ast::expr_pointer::ptr& expr, const ast::expr& obj, bool is_stmt);
    void emit_expr_method_function(const ast::expr_function::ptr& expr, const ast::expr& obj, bool is_stmt);
    void emit_expr_parameters(const ast::expr_parameters::ptr& expr);
    void emit_expr_arguments(const ast::expr_arguments::ptr& expr);
    void emit_expr_isdefined(const ast::expr_isdefined::ptr& expr);
    void emit_expr_vectorscale(const ast::expr_vectorscale::ptr& expr);
    void emit_expr_anglestoup(const ast::expr_anglestoup::ptr& expr);
    void emit_expr_anglestoright(const ast::expr_anglestoright::ptr& expr);
    void emit_expr_anglestoforward(const ast::expr_anglestoforward::ptr& expr);
    void emit_expr_angleclamp180(const ast::expr_angleclamp180::ptr& expr);
    void emit_expr_vectortoangles(const ast::expr_vectortoangles::ptr& expr);
    void emit_expr_abs(const ast::expr_abs::ptr& expr);
    void emit_expr_gettime(const ast::expr_gettime::ptr& expr);
    void emit_expr_getdvar(const ast::expr_getdvar::ptr& expr);
    void emit_expr_getdvarint(const ast::expr_getdvarint::ptr& expr);
    void emit_expr_getdvarfloat(const ast::expr_getdvarfloat::ptr& expr);
    void emit_expr_getdvarvector(const ast::expr_getdvarvector::ptr& expr);
    void emit_expr_getdvarcolorred(const ast::expr_getdvarcolorred::ptr& expr);
    void emit_expr_getdvarcolorgreen(const ast::expr_getdvarcolorgreen::ptr& expr);
    void emit_expr_getdvarcolorblue(const ast::expr_getdvarcolorblue::ptr& expr);
    void emit_expr_getdvarcoloralpha(const ast::expr_getdvarcoloralpha::ptr& expr);
    void emit_expr_getfirstarraykey(const ast::expr_getfirstarraykey::ptr& expr);
    void emit_expr_getnextarraykey(const ast::expr_getnextarraykey::ptr& expr);
    void emit_expr_reference(const ast::expr_reference::ptr& expr);
    void emit_expr_size(const ast::expr_size::ptr& expr);
    void emit_expr_variable_ref(const ast::expr& expr, bool set);
    void emit_expr_array_ref(const ast::expr_array::ptr& expr, bool set);
    void emit_expr_field_ref(const ast::expr_field::ptr& expr, bool set);
    void emit_expr_local_ref(const ast::expr_identifier::ptr& expr, bool set);
    void emit_expr_variable(const ast::expr& expr);
    void emit_expr_array(const ast::expr_array::ptr& expr);
    void emit_expr_field(const ast::expr_field::ptr& expr);
    void emit_expr_local(const ast::expr_identifier::ptr& expr);
    void emit_expr_object(const ast::expr& expr);
    void emit_expr_vector(const ast::expr_vector::ptr& expr);
    void emit_expr_animation(const ast::expr_animation::ptr& expr);
    void emit_expr_animtree(const ast::expr_animtree::ptr& expr);
    void emit_expr_istring(const ast::expr_istring::ptr& expr);
    void emit_expr_string(const ast::expr_string::ptr& expr);
    void emit_expr_hash(const ast::expr_hash::ptr& expr);
    void emit_expr_float(const ast::expr_float::ptr& expr);
    void emit_expr_integer(const ast::expr_integer::ptr& expr);
    void emit_expr_false(const ast::expr_false::ptr& expr);
    void emit_expr_true(const ast::expr_true::ptr& expr);
    void emit_opcode(opcode op);
    void emit_opcode(opcode op, const std::string& data);
    void emit_opcode(opcode op, const std::vector<std::string>& data);
    void process_thread(const ast::decl_thread::ptr& decl);
    void process_stmt(const ast::stmt& stmt);
    void process_stmt_list(const ast::stmt_list::ptr& stmt);
    void process_stmt_dev(const ast::stmt_dev::ptr& stmt);
    void process_stmt_expr(const ast::stmt_expr::ptr& stmt);
    void process_stmt_assign(const ast::stmt_assign::ptr& stmt);
    void process_stmt_waittill(const ast::stmt_waittill::ptr& stmt);
    void process_stmt_if(const ast::stmt_if::ptr& stmt);
    void process_stmt_ifelse(const ast::stmt_ifelse::ptr& stmt);
    void process_stmt_while(const ast::stmt_while::ptr& stmt);
    void process_stmt_dowhile(const ast::stmt_dowhile::ptr& stmt);
    void process_stmt_for(const ast::stmt_for::ptr& stmt);
    void process_stmt_foreach(const ast::stmt_foreach::ptr& stmt);
    void process_stmt_switch(const ast::stmt_switch::ptr& stmt);
    void process_expr(const ast::expr& expr);
    void process_expr_parameters(const ast::expr_parameters::ptr& expr);
    void variable_register(const std::string& name);
    auto variable_access(const ast::expr_identifier::ptr& name) -> std::string;
    auto is_constant_condition(const ast::expr& expr) -> bool;
    auto create_label() -> std::string;
    auto insert_label() -> std::string;
    void insert_label(const std::string& label);
    auto map_known_includes(const std::string& include) -> bool;
    void print_function(const function::ptr& func);
    void print_instruction(const instruction::ptr& inst);
};

} // namespace xsk::arc::t6
