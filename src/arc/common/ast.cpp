// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/common/location.hpp"
#include "xsk/arc/common/asset.hpp"
#include "xsk/arc/common/ast.hpp"

namespace xsk::arc
{

auto node::is_special_stmt() -> bool
{
    switch (kind_)
    {
        case type::stmt_if:
        case type::stmt_ifelse:
        case type::stmt_while:
        case type::stmt_dowhile:
        case type::stmt_for:
        case type::stmt_foreach:
        case type::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_special_stmt_dev() -> bool
{
    switch (kind_)
    {
        case type::stmt_dev:
        case type::stmt_if:
        case type::stmt_ifelse:
        case type::stmt_while:
        case type::stmt_dowhile:
        case type::stmt_for:
        case type::stmt_foreach:
        case type::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_special_stmt_noif() -> bool
{
    switch (kind_)
    {
        case type::stmt_while:
        case type::stmt_dowhile:
        case type::stmt_for:
        case type::stmt_foreach:
        case type::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_special_stmt_dev_noif() -> bool
{
    switch (kind_)
    {
        case type::stmt_dev:
        case type::stmt_while:
        case type::stmt_dowhile:
        case type::stmt_for:
        case type::stmt_foreach:
        case type::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_boolean() -> bool
{
    switch (kind_)
    {
        case type::expr_integer:
            return reinterpret_cast<arc::expr_integer*>(this)->value == "1" ||
                reinterpret_cast<arc::expr_integer*>(this)->value == "0";
        case type::expr_true:
        case type::expr_false:
        case type::expr_or:
        case type::expr_and:
        case type::expr_super_equal:
        case type::expr_super_not_equal:
        case type::expr_equality:
        case type::expr_inequality:
        case type::expr_less:
        case type::expr_greater:
        case type::expr_less_equal:
        case type::expr_greater_equal:
            return true;
        default:
            return false;
    }
}

auto node::is_binary() -> bool
{
    switch (kind_)
    {
        case type::expr_or:
        case type::expr_and:
        case type::expr_bitwise_or:
        case type::expr_bitwise_exor:
        case type::expr_bitwise_and:
        case type::expr_super_equal:
        case type::expr_super_not_equal:
        case type::expr_equality:
        case type::expr_inequality:
        case type::expr_less:
        case type::expr_greater:
        case type::expr_less_equal:
        case type::expr_greater_equal:
        case type::expr_shift_left:
        case type::expr_shift_right:
        case type::expr_add:
        case type::expr_sub:
        case type::expr_mul:
        case type::expr_div:
        case type::expr_mod:
            return true;
        default:
            return false;
    }
}

auto node::precedence() -> u8
{
    switch (kind_)
    {
        case type::expr_or:              return 1;
        case type::expr_and:             return 2;
        case type::expr_bitwise_or:      return 3;
        case type::expr_bitwise_exor:    return 4;
        case type::expr_bitwise_and:     return 5;
        case type::expr_super_equal:     return 6;
        case type::expr_super_not_equal: return 6;
        case type::expr_equality:        return 6;
        case type::expr_inequality:      return 6;
        case type::expr_less:            return 7;
        case type::expr_greater:         return 7;
        case type::expr_less_equal:      return 7;
        case type::expr_greater_equal:   return 7;
        case type::expr_shift_left:      return 8;
        case type::expr_shift_right:     return 8;
        case type::expr_add:             return 9;
        case type::expr_sub:             return 9;
        case type::expr_mul:             return 10;
        case type::expr_div:             return 10;
        case type::expr_mod:             return 10;
        default: return 0;
    }
}

expr_true::expr_true(location const& loc) : node{ type::expr_true, loc }
{
}

expr_false::expr_false(location const& loc) : node{ type::expr_false, loc }
{
}

expr_integer::expr_integer(location const& loc, std::string const& value) : node{ type::expr_integer, loc }, value{ std::move(value) }
{
}

expr_float::expr_float(location const& loc, std::string const& value) : node{ type::expr_float, loc }, value{ std::move(value) }
{
}

expr_vector::expr_vector(location const& loc, expr x, expr y, expr z) : node{ type::expr_vector, loc }, x{ std::move(x) }, y{ std::move(y) }, z{ std::move(z) }
{
}

expr_hash::expr_hash(location const& loc, const std::string& value) : node{ type::expr_hash, loc }, value{ value }
{
}
expr_string::expr_string(location const& loc, const std::string& value) : node{ type::expr_string, loc }, value{ value }
{
}

expr_istring::expr_istring(location const& loc, const std::string& value) : node{ type::expr_istring, loc }, value{ std::move(value) }
{
}

expr_path::expr_path(location const& loc) : node{ type::expr_path, loc }
{
}

expr_path::expr_path(location const& loc, std::string const& value) : node{ type::expr_path, loc }, value{ value }
{
}

expr_identifier::expr_identifier(location const& loc, std::string const& value) : node{ type::expr_identifier, loc }, value{ value }
{
}

expr_animtree::expr_animtree(location const& loc) : node{ type::expr_animtree, loc }
{
}

expr_animation::expr_animation(location const& loc, std::string const& value) : node{ type::expr_animation, loc }, value{ value }
{
}

expr_classes::expr_classes(location const& loc) : node{ type::expr_classes, loc }
{
}

expr_world::expr_world(location const& loc) : node{ type::expr_world, loc }
{
}

expr_level::expr_level(location const& loc) : node{ type::expr_level, loc }
{
}

expr_anim::expr_anim(location const& loc) : node{ type::expr_anim, loc }
{
}

expr_self::expr_self(location const& loc) : node{ type::expr_self, loc }
{
}

expr_game::expr_game(location const& loc) : node{ type::expr_game, loc }
{
}

expr_undefined::expr_undefined(location const& loc) : node{ type::expr_undefined, loc }
{
}

expr_empty_array::expr_empty_array(location const& loc) : node{ type::expr_empty_array, loc }
{
}

expr_paren::expr_paren(location const& loc, expr value) : node{ type::expr_paren, loc }, value{ std::move(value) }
{
}

expr_size::expr_size(location const& loc, expr obj) : node{ type::expr_size, loc }, obj{ std::move(obj) }
{
}

expr_field::expr_field(location const& loc, expr obj, expr_identifier::ptr field) : node{ type::expr_field, loc }, obj{ std::move(obj) }, field{ std::move(field) }
{
}

expr_array::expr_array(location const& loc, expr obj, expr key) : node{ type::expr_array, loc }, obj{ std::move(obj) }, key{ std::move(key) }
{
}

expr_reference::expr_reference(location const& loc, expr_path::ptr path, expr_identifier::ptr name) : node{ type::expr_reference, loc }, path{ std::move(path) }, name{ std::move(name) }
{
}

expr_getnextarraykey::expr_getnextarraykey(location const& loc, expr arg1, expr arg2) : node{ type::expr_getnextarraykey, loc }, arg1{ std::move(arg1) }, arg2{ std::move(arg2) }
{
}

expr_getfirstarraykey::expr_getfirstarraykey(location const& loc, expr arg) : node{ type::expr_getfirstarraykey, loc }, arg{ std::move(arg) }
{
}

expr_getdvarcoloralpha::expr_getdvarcoloralpha(location const& loc, expr arg) : node{ type::expr_getdvarcoloralpha, loc }, arg{ std::move(arg) }
{
}

expr_getdvarcolorblue::expr_getdvarcolorblue(location const& loc, expr arg) : node{ type::expr_getdvarcolorblue, loc }, arg{ std::move(arg) }
{
}

expr_getdvarcolorgreen::expr_getdvarcolorgreen(location const& loc, expr arg) : node{ type::expr_getdvarcolorgreen, loc }, arg{ std::move(arg) }
{
}

expr_getdvarcolorred::expr_getdvarcolorred(location const& loc, expr arg) : node{ type::expr_getdvarcolorred, loc }, arg{ std::move(arg) }
{
}

expr_getdvarvector::expr_getdvarvector(location const& loc, expr arg) : node{ type::expr_getdvarvector, loc }, arg{ std::move(arg) }
{
}

expr_getdvarfloat::expr_getdvarfloat(location const& loc, expr arg) : node{ type::expr_getdvarfloat, loc }, arg{ std::move(arg) }
{
}

expr_getdvarint::expr_getdvarint(location const& loc, expr arg) : node{ type::expr_getdvarint, loc }, arg{ std::move(arg) }
{
}

expr_getdvar::expr_getdvar(location const& loc, expr arg) : node{ type::expr_getdvar, loc }, arg{ std::move(arg) }
{
}

expr_gettime::expr_gettime(location const& loc) : node{ type::expr_gettime, loc }
{
}

expr_abs::expr_abs(location const& loc, expr arg) : node{ type::expr_abs, loc }, arg{ std::move(arg) }
{
}

expr_vectortoangles::expr_vectortoangles(location const& loc, expr arg) : node{ type::expr_vectortoangles, loc }, arg{ std::move(arg) }
{
}

expr_angleclamp180::expr_angleclamp180(location const& loc, expr arg) : node{ type::expr_angleclamp180, loc }, arg{ std::move(arg) }
{
}

expr_anglestoforward::expr_anglestoforward(location const& loc, expr arg) : node{ type::expr_anglestoforward, loc }, arg{ std::move(arg) }
{
}

expr_anglestoright::expr_anglestoright(location const& loc, expr arg) : node{ type::expr_anglestoright, loc }, arg{ std::move(arg) }
{
}

expr_anglestoup::expr_anglestoup(location const& loc, expr arg) : node{ type::expr_anglestoup, loc }, arg{ std::move(arg) }
{
}

expr_vectorscale::expr_vectorscale(location const& loc, expr arg1, expr arg2) : node{ type::expr_vectorscale, loc }, arg1{ std::move(arg1) }, arg2{ std::move(arg2) }
{
}

expr_isdefined::expr_isdefined(location const& loc, expr value) : node{ type::expr_isdefined, loc }, value{ std::move(value) }
{
}

expr_arguments::expr_arguments(location const& loc) : node{ type::expr_arguments, loc }
{
}

expr_parameters::expr_parameters(location const& loc) : node{ type::expr_parameters, loc }
{
}

expr_member::expr_member(location const& loc, expr obj, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode) : node{ type::expr_member, loc }, obj{ std::move(obj) }, name{ std::move(name) }, args{ std::move(args) }, mode{ mode }
{
}

expr_pointer::expr_pointer(location const& loc, expr func, expr_arguments::ptr args, call::mode mode) : node{ type::expr_pointer, loc }, func{ std::move(func) }, args{ std::move(args) }, mode{ mode }
{
}

expr_function::expr_function(location const& loc, expr_path::ptr path, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode) : node{ type::expr_function, loc }, path{ std::move(path) }, name{ std::move(name) }, args{ std::move(args) }, mode{ mode }
{
}

expr_method::expr_method(location const& loc, expr obj, call value) : node{ type::expr_method, loc }, obj{ std::move(obj) }, value{ std::move(value) }
{
}

expr_call::expr_call(location const& loc, call value) : node{ type::expr_call, loc }, value{ std::move(value) }
{
}

expr_new::expr_new(location const& loc, expr_identifier::ptr name) : node{ type::expr_new, loc }, name{ std::move(name) }
{
}

expr_complement::expr_complement(location const& loc, expr rvalue) : node{ type::expr_complement, loc }, rvalue{ std::move(rvalue) }
{
}

expr_negate::expr_negate(location const& loc, expr rvalue) : node{ type::expr_negate, loc }, rvalue{ std::move(rvalue) }
{
}

expr_not::expr_not(location const& loc, expr rvalue) : node{ type::expr_not, loc }, rvalue{ std::move(rvalue) }
{
}

expr_binary::expr_binary(type t, location const& loc, expr lvalue, expr rvalue) : node{ t, loc }, lvalue{ std::move(lvalue) }, rvalue{ std::move(rvalue) }
{
}

expr_add::expr_add(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_add, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_sub::expr_sub(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_sub, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_mul::expr_mul(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_mul, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_div::expr_div(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_div, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_mod::expr_mod(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_mod, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_shift_left::expr_shift_left(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_shift_left, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_shift_right::expr_shift_right(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_shift_right, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_bitwise_or::expr_bitwise_or(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_bitwise_or, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_bitwise_and::expr_bitwise_and(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_bitwise_and, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_bitwise_exor::expr_bitwise_exor(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_bitwise_exor, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_super_equal::expr_super_equal(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_super_equal, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_super_not_equal::expr_super_not_equal(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_super_not_equal, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_equality::expr_equality(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_equality, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_inequality::expr_inequality(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_inequality, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_less_equal::expr_less_equal(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_less_equal, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_greater_equal::expr_greater_equal(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_greater_equal, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_less::expr_less(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_less, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_greater::expr_greater(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_greater, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_or::expr_or(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_or, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_and::expr_and(location const& loc, expr lvalue, expr rvalue) : expr_binary{ type::expr_and, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_ternary::expr_ternary(location const& loc, expr test, expr true_expr, expr false_expr) : node{ type::expr_ternary, loc }, test{ std::move(test) }, true_expr{ std::move(true_expr) }, false_expr{ std::move(false_expr) }
{
}

expr_increment::expr_increment(location const& loc, expr lvalue, bool prefix) : node{ type::expr_increment, loc }, lvalue{ std::move(lvalue) }, prefix{ prefix }
{
}

expr_decrement::expr_decrement(location const& loc, expr lvalue, bool prefix) : node{ type::expr_decrement, loc }, lvalue{ std::move(lvalue) }, prefix{ prefix }
{
}

expr_assign::expr_assign(type t, location const& loc, expr lvalue, expr rvalue) : node{ t, loc }, lvalue{ std::move(lvalue) }, rvalue{ std::move(rvalue) }
{
}

expr_assign_equal::expr_assign_equal(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_equal, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_add::expr_assign_add(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_add, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_sub::expr_assign_sub(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_sub, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_mul::expr_assign_mul(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_mul, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_div::expr_assign_div(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_div, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_mod::expr_assign_mod(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_mod, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_shift_left::expr_assign_shift_left(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_shift_left, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_shift_right::expr_assign_shift_right(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_shift_right, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_bitwise_or::expr_assign_bitwise_or(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_bitwise_or, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_bitwise_and::expr_assign_bitwise_and(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_bitwise_and, loc, std::move(lvalue), std::move(rvalue) }
{
}

expr_assign_bitwise_exor::expr_assign_bitwise_exor(location const& loc, expr lvalue, expr rvalue) : expr_assign{ type::expr_assign_bitwise_exor, loc, std::move(lvalue), std::move(rvalue) }
{
}

stmt_list::stmt_list(location const& loc) : node{ type::stmt_list, loc }
{
}

stmt_comp::stmt_comp(location const& loc, stmt_list::ptr block) : node{ type::stmt_comp, loc }, block{ std::move(block) }
{
}

stmt_dev::stmt_dev(location const& loc, stmt_list::ptr block) : node{ type::stmt_dev, loc }, block{ std::move(block) }
{
}

stmt_expr::stmt_expr(location const& loc, expr value) : node{ type::stmt_expr, loc }, value{ std::move(value) }
{
}

stmt_call::stmt_call(location const& loc, expr value) : node{ type::stmt_call, loc }, value{ std::move(value) }
{
}

stmt_const::stmt_const(location const& loc, expr_identifier::ptr lvalue, expr rvalue) : node{ type::stmt_const, loc }, lvalue{ std::move(lvalue) }, rvalue{ std::move(rvalue) }
{
}

stmt_assign::stmt_assign(location const& loc, expr value) : node{ type::stmt_assign, loc }, value{ std::move(value) }
{
}

stmt_endon::stmt_endon(location const& loc, expr obj, expr event) : node{ type::stmt_endon, loc }, obj{ std::move(obj) }, event{ std::move(event) }
{
}

stmt_notify::stmt_notify(location const& loc, expr obj, expr event, expr_arguments::ptr args) : node{ type::stmt_notify, loc }, obj{ std::move(obj) }, event{ std::move(event) }, args{ std::move(args) }
{
}

stmt_realwait::stmt_realwait(location const& loc, expr time) : node{ type::stmt_realwait, loc }, time{ std::move(time) }
{
}

stmt_wait::stmt_wait(location const& loc, expr time) : node{ type::stmt_wait, loc }, time{ std::move(time) }
{
}

stmt_waittill::stmt_waittill(location const& loc, expr obj, expr event, expr_arguments::ptr args) : node{ type::stmt_waittill, loc }, obj{ std::move(obj) }, event{ std::move(event) }, args{ std::move(args) }
{
}

stmt_waittillmatch::stmt_waittillmatch(location const& loc, expr obj, expr event, expr_arguments::ptr args) : node{ type::stmt_waittillmatch, loc }, obj{ std::move(obj) }, event{ std::move(event) }, args{ std::move(args) }
{
}

stmt_waittillframeend::stmt_waittillframeend(location const& loc) : node{ type::stmt_waittillframeend, loc }
{
}

stmt_if::stmt_if(location const& loc, expr test, stmt body) : node{ type::stmt_if, loc }, test{ std::move(test) }, body{ std::move(body) }
{
}

stmt_ifelse::stmt_ifelse(location const& loc, expr test, stmt stmt_if, stmt stmt_else) : node{ type::stmt_ifelse, loc }, test{ std::move(test) }, stmt_if{ std::move(stmt_if) }, stmt_else{ std::move(stmt_else) }
{
}

stmt_while::stmt_while(location const& loc, expr test, stmt body) : node{ type::stmt_while, loc }, test{ std::move(test) }, body{ std::move(body) }
{
}

stmt_dowhile::stmt_dowhile(location const& loc, expr test, stmt body) : node{ type::stmt_dowhile, loc }, test{ std::move(test) }, body{ std::move(body) }
{
}

stmt_for::stmt_for(location const& loc, stmt init, expr test, stmt iter, stmt body) : node{ type::stmt_for, loc }, init{ std::move(init) }, test{ std::move(test) }, iter{ std::move(iter) }, body{ std::move(body) }
{
}

stmt_foreach::stmt_foreach(location const& loc, expr container, expr value, expr array, expr key, stmt body, bool use_key) : node{ type::stmt_foreach, loc }, container{ std::move(container) }, value{ std::move(value) }, array{ std::move(array) }, key{ std::move(key) }, body{ std::move(body) }, use_key{ use_key }
{
}

stmt_switch::stmt_switch(location const& loc, expr test, stmt_comp::ptr body) : node{ type::stmt_switch, loc }, test{ std::move(test) }, body{ std::move(body) }
{
}

stmt_case::stmt_case(location const& loc, expr value) : node{ type::stmt_case, loc }, value{ std::move(value) }, body{ nullptr }
{
}

stmt_case::stmt_case(location const& loc, expr value, stmt_list::ptr body) : node{ type::stmt_case, loc }, value{ std::move(value) }, body{ std::move(body) }
{
}

stmt_default::stmt_default(location const& loc) : node{ type::stmt_default, loc }, body{ nullptr }
{
}

stmt_default::stmt_default(location const& loc, stmt_list::ptr body) : node{ type::stmt_default, loc }, body{ std::move(body) }
{
}

stmt_break::stmt_break(location const& loc) : node{ type::stmt_break, loc }
{
}

stmt_continue::stmt_continue(location const& loc) : node{ type::stmt_continue, loc }
{
}

stmt_return::stmt_return(location const& loc, expr value) : node{ type::stmt_return, loc }, value{ std::move(value) }
{
}

stmt_breakpoint::stmt_breakpoint(location const& loc) : node{ type::stmt_breakpoint, loc }
{
}

stmt_prof_begin::stmt_prof_begin(location const& loc, expr_arguments::ptr args) : node{ type::stmt_prof_begin, loc }, args{ std::move(args) }
{
}

stmt_prof_end::stmt_prof_end(location const& loc, expr_arguments::ptr args) : node{ type::stmt_prof_end, loc }, args{ std::move(args) }
{
}

decl_function::decl_function(location const& loc, expr_identifier::ptr space, expr_identifier::ptr name, expr_parameters::ptr params, stmt_comp::ptr body, export_flags flags) : node{ type::decl_function, loc }, space{ std::move(space) }, name{ std::move(name) }, params{ std::move(params) }, body{ std::move(body) }, flags{ flags }
{
}

decl_namespace::decl_namespace(location const& loc, expr_string::ptr name) : node{ type::decl_namespace, loc }, name{ std::move(name) }
{
}

decl_usingtree::decl_usingtree(location const& loc, expr_string::ptr name) : node{ type::decl_usingtree, loc }, name{ std::move(name) }
{
}

decl_dev_begin::decl_dev_begin(location const& loc) : node{ type::decl_dev_begin, loc }
{
}

decl_dev_end::decl_dev_end(location const& loc) : node{ type::decl_dev_end, loc }
{
}

include::include(location const& loc, expr_path::ptr path) : node{ type::include, loc }, path{ std::move(path) }
{
}

program::program() : node{ type::program }
{
}

program::program(location const& loc) : node{ type::program, loc }
{
}

asm_loc::asm_loc(location const& loc, std::string const& value) : node{ type::asm_loc, loc }, value{ value }
{
}

asm_jmp::asm_jmp(location const& loc, std::string const& value) : node{ type::asm_jmp, loc }, value{ value }
{
}

asm_jmp_back::asm_jmp_back(location const& loc, std::string const& value) : node{ type::asm_jmp_back, loc }, value{ value }
{
}

asm_jmp_cond::asm_jmp_cond(location const& loc, expr test, std::string const& value) : node{ type::asm_jmp_cond, loc }, test{ std::move(test) }, value{ value }
{
}

asm_jmp_true::asm_jmp_true(location const& loc, expr test, std::string const& value) : node{ type::asm_jmp_true, loc }, test{ std::move(test) }, value{ value }
{
}

asm_jmp_false::asm_jmp_false(location const& loc, expr test, std::string const& value) : node{ type::asm_jmp_false, loc }, test{ std::move(test) }, value{ value }
{
}

asm_switch::asm_switch(location const& loc, expr test, std::string const& value) : node{ type::asm_switch, loc }, test{ std::move(test) }, value{ value }
{
}

asm_endswitch::asm_endswitch(location const& loc, std::vector<std::string> data) : node{ type::asm_endswitch, loc }, data{ std::move(data) }
{
}

asm_prescriptcall::asm_prescriptcall(location const& loc) : node{ type::asm_prescriptcall, loc }
{
}

asm_voidcodepos::asm_voidcodepos(location const& loc) : node{ type::asm_voidcodepos, loc }
{
}

asm_dev::asm_dev(location const& loc, std::string const& value) : node{ type::asm_dev, loc }, value{ value }
{
}

auto operator==(node const& n, node::type k) -> bool
{
    return n.kind_ == k;
}

auto operator==(node const& lhs, node const& rhs) -> bool
{
    return lhs.kind_ == rhs.kind_;
}

auto operator==(expr_true const&, expr_true const&) -> bool
{
    return true;
}

auto operator==(expr_false const&, expr_false const&) -> bool
{
    return true;
}

auto operator==(expr_integer const& lhs, expr_integer const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_float const& lhs, expr_float const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_vector const& lhs, expr_vector const& rhs) -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

auto operator==(expr_hash const& lhs, expr_hash const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_string const& lhs, expr_string const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_istring const& lhs, expr_istring const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_path const& lhs, expr_path const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_identifier const& lhs, expr_identifier const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_animtree const&, expr_animtree const&) -> bool
{
    return true;
}

auto operator==(expr_animation const& lhs, expr_animation const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_classes const&, expr_classes const&) -> bool
{
    return true;
}

auto operator==(expr_world const&, expr_world const&) -> bool
{
    return true;
}

auto operator==(expr_level const&, expr_level const&) -> bool
{
    return true;
}

auto operator==(expr_anim const&, expr_anim const&) -> bool
{
    return true;
}

auto operator==(expr_self const&, expr_self const&) -> bool
{
    return true;
}

auto operator==(expr_game const&, expr_game const&) -> bool
{
    return true;
}

auto operator==(expr_undefined const&, expr_undefined const&) -> bool
{
    return true;
}

auto operator==(expr_empty_array const&, expr_empty_array const&) -> bool
{
    return true;
}

auto operator==(expr_paren const& lhs, expr_paren const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_size const& lhs, expr_size const& rhs) -> bool
{
    return lhs.obj == rhs.obj;
}

auto operator==(expr_field const& lhs, expr_field const& rhs) -> bool
{
    return lhs.obj == rhs.obj && *lhs.field == *rhs.field;
}

auto operator==(expr_array const& lhs, expr_array const& rhs) -> bool
{
    return lhs.obj == rhs.obj && lhs.key == rhs.key;
}

call::call() : as_node{ nullptr }
{
}

call::call(std::unique_ptr<node> value) : as_node{ std::move(value) }
{
}

call::call(call&& value)
{
    new(&as_node) std::unique_ptr<node>{ std::move(value.as_node) };
}

call::~call()
{
    if (as_node == nullptr) return;

    switch (as_node->kind())
    {
        case node::null: as_node.~unique_ptr(); return;
        case node::expr_pointer: as_pointer.~unique_ptr(); return;
        case node::expr_function: as_function.~unique_ptr(); return;
        default: return;
    }
}

auto operator==(call const& lhs, node::type rhs) -> bool
{
    return *lhs.as_node == rhs;
}

auto call::loc() const -> location
{
    return as_node->loc();
}

auto call::kind() const -> node::type
{
    return as_node->kind();
}

auto call::label() const -> std::string
{
    return as_node->label();
}

expr::expr() : as_node{ nullptr }
{
}

expr::expr(std::unique_ptr<node> value) : as_node{ std::move(value) }
{
}

expr::expr(expr&& value)
{
    new(&as_node) std::unique_ptr<node>{ std::move(value.as_node) };
}

expr& expr::operator=(expr&& value)
{
    new(&as_node) std::unique_ptr<node>{ std::move(value.as_node) };
    return *(expr*)&as_node;
}

expr::~expr()
{
    if (as_node == nullptr) return;

    switch (as_node->kind())
    {
        case node::null: as_node.~unique_ptr(); return;
        case node::expr_true: as_true.~unique_ptr(); return;
        case node::expr_false: as_false.~unique_ptr(); return;
        case node::expr_integer: as_integer.~unique_ptr(); return;
        case node::expr_float: as_float.~unique_ptr(); return;
        case node::expr_vector: as_vector.~unique_ptr(); return;
        case node::expr_hash: as_hash.~unique_ptr(); return;
        case node::expr_string: as_string.~unique_ptr(); return;
        case node::expr_istring: as_istring.~unique_ptr(); return;
        case node::expr_path: as_path.~unique_ptr(); return;
        case node::expr_identifier: as_identifier.~unique_ptr(); return;
        case node::expr_animtree: as_animtree.~unique_ptr(); return;
        case node::expr_animation: as_animation.~unique_ptr(); return;
        case node::expr_classes: as_classes.~unique_ptr(); return;
        case node::expr_world: as_world.~unique_ptr(); return;
        case node::expr_level: as_level.~unique_ptr(); return;
        case node::expr_anim: as_anim.~unique_ptr(); return;
        case node::expr_self: as_self.~unique_ptr(); return;
        case node::expr_game: as_game.~unique_ptr(); return;
        case node::expr_undefined: as_undefined.~unique_ptr(); return;
        case node::expr_empty_array: as_empty_array.~unique_ptr(); return;
        case node::expr_paren: as_paren.~unique_ptr(); return;
        case node::expr_size: as_size.~unique_ptr(); return;
        case node::expr_field: as_field.~unique_ptr(); return;
        case node::expr_array: as_array.~unique_ptr(); return;
        case node::expr_reference: as_reference.~unique_ptr(); return;
        case node::expr_getnextarraykey: as_getnextarraykey.~unique_ptr(); return;
        case node::expr_getfirstarraykey: as_getfirstarraykey.~unique_ptr(); return;
        case node::expr_getdvarcoloralpha: as_getdvarcoloralpha.~unique_ptr(); return;
        case node::expr_getdvarcolorblue: as_getdvarcolorblue.~unique_ptr(); return;
        case node::expr_getdvarcolorgreen: as_getdvarcolorgreen.~unique_ptr(); return;
        case node::expr_getdvarcolorred: as_getdvarcolorred.~unique_ptr(); return;
        case node::expr_getdvarvector: as_getdvarvector.~unique_ptr(); return;
        case node::expr_getdvarfloat: as_getdvarfloat.~unique_ptr(); return;
        case node::expr_getdvarint: as_getdvarint.~unique_ptr(); return;
        case node::expr_getdvar: as_getdvar.~unique_ptr(); return;
        case node::expr_gettime: as_gettime.~unique_ptr(); return;
        case node::expr_abs: as_abs.~unique_ptr(); return;
        case node::expr_vectortoangles: as_vectortoangles.~unique_ptr(); return;
        case node::expr_angleclamp180: as_angleclamp180.~unique_ptr(); return;
        case node::expr_anglestoforward: as_anglestoforward.~unique_ptr(); return;
        case node::expr_anglestoright: as_anglestoright.~unique_ptr(); return;
        case node::expr_anglestoup: as_anglestoup.~unique_ptr(); return;
        case node::expr_vectorscale: as_vectorscale.~unique_ptr(); return;
        case node::expr_isdefined: as_isdefined.~unique_ptr(); return;
        case node::expr_arguments: as_arguments.~unique_ptr(); return;
        case node::expr_parameters: as_parameters.~unique_ptr(); return;
        case node::expr_member: as_member.~unique_ptr(); return;
        case node::expr_pointer: as_pointer.~unique_ptr(); return;
        case node::expr_function: as_function.~unique_ptr(); return;
        case node::expr_method: as_method.~unique_ptr(); return;
        case node::expr_call: as_call.~unique_ptr(); return;
        case node::expr_new: as_new.~unique_ptr(); return;
        case node::expr_complement: as_complement.~unique_ptr(); return;
        case node::expr_negate: as_negate.~unique_ptr(); return;
        case node::expr_not: as_not.~unique_ptr(); return;
        case node::expr_add: as_add.~unique_ptr(); return;
        case node::expr_sub: as_sub.~unique_ptr(); return;
        case node::expr_mul: as_mul.~unique_ptr(); return;
        case node::expr_div: as_div.~unique_ptr(); return;
        case node::expr_mod: as_mod.~unique_ptr(); return;
        case node::expr_shift_left: as_shift_left.~unique_ptr(); return;
        case node::expr_shift_right: as_shift_right.~unique_ptr(); return;
        case node::expr_bitwise_or: as_bitwise_or.~unique_ptr(); return;
        case node::expr_bitwise_and: as_bitwise_and.~unique_ptr(); return;
        case node::expr_bitwise_exor: as_bitwise_exor.~unique_ptr(); return;
        case node::expr_super_equal: as_super_equal.~unique_ptr(); return;
        case node::expr_super_not_equal: as_super_not_equal.~unique_ptr(); return;
        case node::expr_equality: as_equality.~unique_ptr(); return;
        case node::expr_inequality: as_inequality.~unique_ptr(); return;
        case node::expr_less_equal: as_less_equal.~unique_ptr(); return;
        case node::expr_greater_equal: as_greater_equal.~unique_ptr(); return;
        case node::expr_less: as_less.~unique_ptr(); return;
        case node::expr_greater: as_greater.~unique_ptr(); return;
        case node::expr_or: as_or.~unique_ptr(); return;
        case node::expr_and: as_and.~unique_ptr(); return;
        case node::expr_ternary: as_ternary.~unique_ptr(); return;
        case node::expr_increment: as_increment.~unique_ptr(); return;
        case node::expr_decrement: as_decrement.~unique_ptr(); return;
        case node::expr_assign_equal: as_assign_equal.~unique_ptr(); return;
        case node::expr_assign_add: as_assign_add.~unique_ptr(); return;
        case node::expr_assign_sub: as_assign_sub.~unique_ptr(); return;
        case node::expr_assign_mul: as_assign_mul.~unique_ptr(); return;
        case node::expr_assign_div: as_assign_div.~unique_ptr(); return;
        case node::expr_assign_mod: as_assign_mod.~unique_ptr(); return;
        case node::expr_assign_shift_left: as_assign_shift_left.~unique_ptr(); return;
        case node::expr_assign_shift_right: as_assign_shift_right.~unique_ptr(); return;
        case node::expr_assign_bitwise_or: as_assign_bw_or.~unique_ptr(); return;
        case node::expr_assign_bitwise_and: as_assign_bw_and.~unique_ptr(); return;
        case node::expr_assign_bitwise_exor: as_assign_bw_exor.~unique_ptr(); return;
        default: return;
    }
}

auto operator!=(expr const& lhs, node::type rhs)  -> bool
{
    return lhs.as_node->kind() != rhs;
}

auto operator==(expr const& lhs, node::type rhs)  -> bool
{
    return *lhs.as_node == rhs;
}

auto operator==(expr const& lhs, expr const& rhs)  -> bool
{
    if (!(*lhs.as_node == *rhs.as_node)) return false;

    switch(lhs.as_node->kind())
    {
        case node::expr_true: return *lhs.as_true == *rhs.as_true;
        case node::expr_false: return *lhs.as_false == *rhs.as_false;
        case node::expr_integer: return *lhs.as_integer == *rhs.as_integer;
        case node::expr_float: return *lhs.as_float == *rhs.as_float;
        case node::expr_vector: return *lhs.as_vector == *rhs.as_vector;
        case node::expr_hash: return *lhs.as_hash == *rhs.as_hash;
        case node::expr_string: return *lhs.as_string == *rhs.as_string;
        case node::expr_istring: return *lhs.as_istring == *rhs.as_istring;
        case node::expr_path: return *lhs.as_path == *rhs.as_path;
        case node::expr_identifier: return *lhs.as_identifier == *rhs.as_identifier;
        case node::expr_animtree: return *lhs.as_animtree == *rhs.as_animtree;
        case node::expr_animation: return *lhs.as_animation == *rhs.as_animation;
        case node::expr_classes: return *lhs.as_classes == *rhs.as_classes;
        case node::expr_world: return *lhs.as_world == *rhs.as_world;
        case node::expr_level: return *lhs.as_level == *rhs.as_level;
        case node::expr_anim: return *lhs.as_anim == *rhs.as_anim;
        case node::expr_self: return *lhs.as_self == *rhs.as_self;
        case node::expr_game: return *lhs.as_game == *rhs.as_game;
        case node::expr_undefined: return *lhs.as_undefined == *rhs.as_undefined;
        case node::expr_empty_array: return *lhs.as_empty_array == *rhs.as_empty_array;
        case node::expr_paren: return *lhs.as_paren == *rhs.as_paren;
        case node::expr_size: return *lhs.as_size == *rhs.as_size;
        case node::expr_field: return *lhs.as_field == *rhs.as_field;
        case node::expr_array: return *lhs.as_array == *rhs.as_array;
        default: return false;
    }
}

auto expr::loc() const -> location
{
    return as_node->loc();
}

auto expr::kind() const -> node::type
{
    return as_node->kind();
}

auto expr::label() const -> std::string
{
    return as_node->label();
}

stmt::stmt() : as_node{ nullptr }
{
}

stmt::stmt(std::unique_ptr<node> value) : as_node{ std::move(value) }
{
}

stmt::stmt(stmt&& value)
{
    new(&as_node) std::unique_ptr<node>{ std::move(value.as_node) };
}

stmt& stmt::operator=(stmt&& value)
{
    new(&as_node) std::unique_ptr<node>{ std::move(value.as_node) };
    return *(stmt*)&as_node;
}

stmt::~stmt()
{
    if (as_node == nullptr) return;

    switch (as_node->kind())
    {
        case node::null: as_node.~unique_ptr(); return;
        case node::stmt_list: as_list.~unique_ptr(); return;
        case node::stmt_comp: as_comp.~unique_ptr(); return;
        case node::stmt_dev: as_dev.~unique_ptr(); return;
        case node::stmt_expr: as_expr.~unique_ptr(); return;
        case node::stmt_call: as_call.~unique_ptr(); return;
        case node::stmt_const: as_const.~unique_ptr(); return;
        case node::stmt_assign: as_assign.~unique_ptr(); return;
        case node::stmt_endon: as_endon.~unique_ptr(); return;
        case node::stmt_notify: as_notify.~unique_ptr(); return;
        case node::stmt_realwait: as_realwait.~unique_ptr(); return;
        case node::stmt_wait: as_wait.~unique_ptr(); return;
        case node::stmt_waittill: as_waittill.~unique_ptr(); return;
        case node::stmt_waittillmatch: as_waittillmatch.~unique_ptr(); return;
        case node::stmt_waittillframeend: as_waittillframeend.~unique_ptr(); return;
        case node::stmt_if: as_if.~unique_ptr(); return;
        case node::stmt_ifelse: as_ifelse.~unique_ptr(); return;
        case node::stmt_while: as_while.~unique_ptr(); return;
        case node::stmt_dowhile: as_dowhile.~unique_ptr(); return;
        case node::stmt_for: as_for.~unique_ptr(); return;
        case node::stmt_foreach: as_foreach.~unique_ptr(); return;
        case node::stmt_switch: as_switch.~unique_ptr(); return;
        case node::stmt_case: as_case.~unique_ptr(); return;
        case node::stmt_default: as_default.~unique_ptr(); return;
        case node::stmt_break: as_break.~unique_ptr(); return;
        case node::stmt_continue: as_continue.~unique_ptr(); return;
        case node::stmt_return: as_return.~unique_ptr(); return;
        case node::stmt_breakpoint: as_breakpoint.~unique_ptr(); return;
        case node::stmt_prof_begin: as_prof_begin.~unique_ptr(); return;
        case node::stmt_prof_end: as_prof_end.~unique_ptr(); return;
        case node::asm_loc: as_loc.~unique_ptr(); return;
        case node::asm_jmp: as_jump.~unique_ptr(); return;
        case node::asm_jmp_back: as_jump_back.~unique_ptr(); return;
        case node::asm_jmp_cond: as_cond.~unique_ptr(); return;
        case node::asm_switch: as_asm_switch.~unique_ptr(); return;
        case node::asm_endswitch: as_asm_endswitch.~unique_ptr(); return;
        case node::asm_dev: as_asm_dev.~unique_ptr(); return;
        default: return;
    }
}

auto operator==(stmt const& lhs, node::type rhs)  -> bool
{
    return *lhs.as_node == rhs;
}

auto stmt::loc() const -> location
{
    return as_node->loc();
}

auto stmt::kind() const -> node::type
{
    return as_node->kind();
}

auto stmt::label() const -> std::string
{
    return as_node->label();
}

decl::decl() : as_node{ nullptr }
{
}

decl::decl(std::unique_ptr<node> value) : as_node{ std::move(value) }
{
}

decl::decl(decl&& value)
{
    new(&as_node) std::unique_ptr<node>{ std::move(value.as_node) };
}

decl& decl::operator=(decl&& value)
{
    new(&as_node) std::unique_ptr<node>{ std::move(value.as_node) };
    return *(decl*)&as_node;
}

decl::~decl()
{
    if (as_node == nullptr) return;

    switch (as_node->kind())
    {
        case node::null: as_node.~unique_ptr(); return;
        case node::decl_dev_begin: as_dev_begin.~unique_ptr(); return;
        case node::decl_dev_end: as_dev_end.~unique_ptr(); return;
        case node::decl_function: as_function.~unique_ptr(); return;
        case node::decl_usingtree: as_usingtree.~unique_ptr(); return;
        case node::decl_namespace: as_namespace.~unique_ptr(); return;
        default: return;
    }
}

auto operator==(decl const& lhs, node::type rhs)  -> bool
{
    return *lhs.as_node == rhs;
}

auto decl::loc() const -> location
{
    return as_node->loc();
}

auto decl::kind() const -> node::type
{
    return as_node->kind();
}

auto decl::label() const -> std::string
{
    return as_node->label();
}

} // namespace xsk::arc
