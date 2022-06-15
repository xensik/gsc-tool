// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"

namespace xsk::arc::ast
{

std::uint32_t node::indent_;

void node::reset_indentation()
{
    indent_ = 0;
}

auto node::indented(std::uint32_t indent) -> std::string
{
    static char buff[100];
    snprintf(buff, sizeof(buff), "%*s", indent, "");
    return std::string(buff);
}

auto node::is_special_stmt() -> bool
{
    switch (kind_)
    {
        case kind::stmt_waittill:
        case kind::stmt_waittillmatch:
        case kind::stmt_if:
        case kind::stmt_ifelse:
        case kind::stmt_while:
        case kind::stmt_dowhile:
        case kind::stmt_for:
        case kind::stmt_foreach:
        case kind::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_special_stmt_dev() -> bool
{
    switch (kind_)
    {
        case kind::stmt_dev:
        case kind::stmt_if:
        case kind::stmt_ifelse:
        case kind::stmt_while:
        case kind::stmt_dowhile:
        case kind::stmt_for:
        case kind::stmt_foreach:
        case kind::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_special_stmt_noif() -> bool
{
    switch (kind_)
    {
        case kind::stmt_waittill:
        case kind::stmt_waittillmatch:
        case kind::stmt_while:
        case kind::stmt_dowhile:
        case kind::stmt_for:
        case kind::stmt_foreach:
        case kind::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_special_stmt_dev_noif() -> bool
{
    switch (kind_)
    {
        case kind::stmt_dev:
        case kind::stmt_while:
        case kind::stmt_dowhile:
        case kind::stmt_for:
        case kind::stmt_foreach:
        case kind::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_binary() -> bool
{
    switch (kind_)
    {
        case kind::expr_or:
        case kind::expr_and:
        case kind::expr_bitwise_or:
        case kind::expr_bitwise_exor:
        case kind::expr_bitwise_and:
        case kind::expr_equality:
        case kind::expr_inequality:
        case kind::expr_less:
        case kind::expr_greater:
        case kind::expr_less_equal:
        case kind::expr_greater_equal:
        case kind::expr_shift_left:
        case kind::expr_shift_right:
        case kind::expr_add:
        case kind::expr_sub:
        case kind::expr_mul:
        case kind::expr_div:
        case kind::expr_mod:
            return true;
        default:
            return false;
    }
}

auto node::precedence() -> std::uint8_t
{
    switch (kind_)
    {
        case kind::expr_or:           return 1;
        case kind::expr_and:          return 2;
        case kind::expr_bitwise_or:   return 3;
        case kind::expr_bitwise_exor: return 4;
        case kind::expr_bitwise_and:  return 5;
        case kind::expr_equality:     return 6;
        case kind::expr_inequality:   return 6;
        case kind::expr_less:         return 7;
        case kind::expr_greater:      return 7;
        case kind::expr_less_equal:   return 7;
        case kind::expr_greater_equal:return 7;
        case kind::expr_shift_left:   return 8;
        case kind::expr_shift_right:  return 8;
        case kind::expr_add:          return 9;
        case kind::expr_sub:          return 9;
        case kind::expr_mul:          return 10;
        case kind::expr_div:          return 10;
        case kind::expr_mod:          return 10;
        default: return 0;
    }
}

expr_true::expr_true() : node(kind::expr_true) {}
expr_true::expr_true(const location& loc) : node(kind::expr_true, loc) {}

expr_false::expr_false() : node(kind::expr_false) {}
expr_false::expr_false(const location& loc) : node(kind::expr_false, loc) {}

expr_integer::expr_integer(const std::string& value) : node(kind::expr_integer), value(std::move(value)) {}
expr_integer::expr_integer(const location& loc, const std::string& value) : node(kind::expr_integer, loc), value(std::move(value)) {}

expr_float::expr_float(const std::string& value) : node(kind::expr_float), value(std::move(value)) {}
expr_float::expr_float(const location& loc, const std::string& value) : node(kind::expr_float, loc), value(std::move(value)) {}

expr_vector::expr_vector(expr x, expr y, expr z) : node(kind::expr_vector), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}
expr_vector::expr_vector(const location& loc, expr x, expr y, expr z) : node(kind::expr_vector, loc), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}

expr_hash::expr_hash(const std::string& value) : node(kind::expr_hash), value(value) {}
expr_hash::expr_hash(const location& loc, const std::string& value) : node(kind::expr_hash, loc), value(value) {}

expr_string::expr_string(const std::string& value) : node(kind::expr_string), value(value) {}
expr_string::expr_string(const location& loc, const std::string& value) : node(kind::expr_string, loc), value(value) {}

expr_istring::expr_istring(const std::string& value) : node(kind::expr_istring), value(std::move(value)) {}
expr_istring::expr_istring(const location& loc, const std::string& value) : node(kind::expr_istring, loc), value(std::move(value)) {}

expr_path::expr_path() : node(kind::expr_path) {}
expr_path::expr_path(const std::string& value) : node(kind::expr_path), value(value) {}
expr_path::expr_path(const location& loc) : node(kind::expr_path, loc) {}
expr_path::expr_path(const location& loc, const std::string& value) : node(kind::expr_path, loc), value(value) {}

expr_identifier::expr_identifier(const std::string& value) : node(kind::expr_identifier), value(value) {}
expr_identifier::expr_identifier(const location& loc, const std::string& value) : node(kind::expr_identifier, loc), value(value) {}

expr_animation::expr_animation(const std::string& value) : node(kind::expr_animation), value(value) {}
expr_animation::expr_animation(const location& loc, const std::string& value) : node(kind::expr_animation, loc), value(value) {}

expr_level::expr_level() : node(kind::expr_level) {}
expr_level::expr_level(const location& loc) : node(kind::expr_level, loc) {}

expr_anim::expr_anim() : node(kind::expr_anim) {}
expr_anim::expr_anim(const location& loc) : node(kind::expr_anim, loc) {}

expr_self::expr_self() : node(kind::expr_self) {}
expr_self::expr_self(const location& loc) : node(kind::expr_self, loc) {}

expr_game::expr_game() : node(kind::expr_game) {}
expr_game::expr_game(const location& loc) : node(kind::expr_game, loc) {}

expr_undefined::expr_undefined() : node(kind::expr_undefined) {}
expr_undefined::expr_undefined(const location& loc) : node(kind::expr_undefined, loc) {}

expr_empty_array::expr_empty_array() : node(kind::expr_empty_array) {}
expr_empty_array::expr_empty_array(const location& loc) : node(kind::expr_empty_array, loc) {}

expr_paren::expr_paren(expr child) : node(kind::expr_paren), child(std::move(child)) {}
expr_paren::expr_paren(const location& loc, expr child) : node(kind::expr_paren, loc), child(std::move(child)) {}

expr_size::expr_size(expr obj) : node(kind::expr_size), obj(std::move(obj)) {}
expr_size::expr_size(const location& loc, expr obj) : node(kind::expr_size, loc), obj(std::move(obj)) {}

expr_field::expr_field(expr obj, expr_identifier::ptr field) : node(kind::expr_field), obj(std::move(obj)), field(std::move(field)) {}
expr_field::expr_field(const location& loc, expr obj, expr_identifier::ptr field) : node(kind::expr_field, loc), obj(std::move(obj)), field(std::move(field)) {}

expr_array::expr_array(expr obj, expr key) : node(kind::expr_array), obj(std::move(obj)), key(std::move(key)) {}
expr_array::expr_array(const location& loc, expr obj, expr key) : node(kind::expr_array, loc), obj(std::move(obj)), key(std::move(key)) {}

expr_reference::expr_reference(expr_path::ptr path, expr_identifier::ptr name) : node(kind::expr_reference), path(std::move(path)), name(std::move(name)) {}
expr_reference::expr_reference(const location& loc, expr_path::ptr path, expr_identifier::ptr name) : node(kind::expr_reference, loc), path(std::move(path)), name(std::move(name)) {}

expr_getnextarraykey::expr_getnextarraykey(expr arg1, expr arg2) : node(kind::expr_getnextarraykey), arg1(std::move(arg1)), arg2(std::move(arg2)) {}
expr_getnextarraykey::expr_getnextarraykey(const location& loc, expr arg1, expr arg2) : node(kind::expr_getnextarraykey, loc), arg1(std::move(arg1)), arg2(std::move(arg2)) {}

expr_getfirstarraykey::expr_getfirstarraykey(expr arg) : node(kind::expr_getfirstarraykey), arg(std::move(arg)) {}
expr_getfirstarraykey::expr_getfirstarraykey(const location& loc, expr arg) : node(kind::expr_getfirstarraykey, loc), arg(std::move(arg)) {}

expr_getdvarcoloralpha::expr_getdvarcoloralpha(expr arg) : node(kind::expr_getdvarcoloralpha), arg(std::move(arg)) {}
expr_getdvarcoloralpha::expr_getdvarcoloralpha(const location& loc, expr arg) : node(kind::expr_getdvarcoloralpha, loc), arg(std::move(arg)) {}

expr_getdvarcolorblue::expr_getdvarcolorblue(expr arg) : node(kind::expr_getdvarcolorblue), arg(std::move(arg)) {}
expr_getdvarcolorblue::expr_getdvarcolorblue(const location& loc, expr arg) : node(kind::expr_getdvarcolorblue, loc), arg(std::move(arg)) {}

expr_getdvarcolorgreen::expr_getdvarcolorgreen(expr arg) : node(kind::expr_getdvarcolorgreen), arg(std::move(arg)) {}
expr_getdvarcolorgreen::expr_getdvarcolorgreen(const location& loc, expr arg) : node(kind::expr_getdvarcolorgreen, loc), arg(std::move(arg)) {}

expr_getdvarcolorred::expr_getdvarcolorred(expr arg) : node(kind::expr_getdvarcolorred), arg(std::move(arg)) {}
expr_getdvarcolorred::expr_getdvarcolorred(const location& loc, expr arg) : node(kind::expr_getdvarcolorred, loc), arg(std::move(arg)) {}

expr_getdvarvector::expr_getdvarvector(expr arg) : node(kind::expr_getdvarvector), arg(std::move(arg)) {}
expr_getdvarvector::expr_getdvarvector(const location& loc, expr arg) : node(kind::expr_getdvarvector, loc), arg(std::move(arg)) {}

expr_getdvarfloat::expr_getdvarfloat(expr arg) : node(kind::expr_getdvarfloat), arg(std::move(arg)) {}
expr_getdvarfloat::expr_getdvarfloat(const location& loc, expr arg) : node(kind::expr_getdvarfloat, loc), arg(std::move(arg)) {}

expr_getdvarint::expr_getdvarint(expr arg) : node(kind::expr_getdvarint), arg(std::move(arg)) {}
expr_getdvarint::expr_getdvarint(const location& loc, expr arg) : node(kind::expr_getdvarint, loc), arg(std::move(arg)) {}

expr_getdvar::expr_getdvar(expr arg) : node(kind::expr_getdvar), arg(std::move(arg)) {}
expr_getdvar::expr_getdvar(const location& loc, expr arg) : node(kind::expr_getdvar, loc), arg(std::move(arg)) {}

expr_gettime::expr_gettime() : node(kind::expr_gettime) {}
expr_gettime::expr_gettime(const location& loc) : node(kind::expr_gettime, loc) {}

expr_abs::expr_abs(expr arg) : node(kind::expr_abs), arg(std::move(arg)) {}
expr_abs::expr_abs(const location& loc, expr arg) : node(kind::expr_abs, loc), arg(std::move(arg)) {}

expr_vectortoangles::expr_vectortoangles(expr arg) : node(kind::expr_vectortoangles), arg(std::move(arg)) {}
expr_vectortoangles::expr_vectortoangles(const location& loc, expr arg) : node(kind::expr_vectortoangles, loc), arg(std::move(arg)) {}

expr_angleclamp180::expr_angleclamp180(expr arg) : node(kind::expr_angleclamp180), arg(std::move(arg)) {}
expr_angleclamp180::expr_angleclamp180(const location& loc, expr arg) : node(kind::expr_angleclamp180, loc), arg(std::move(arg)) {}

expr_anglestoforward::expr_anglestoforward(expr arg) : node(kind::expr_anglestoforward), arg(std::move(arg)) {}
expr_anglestoforward::expr_anglestoforward(const location& loc, expr arg) : node(kind::expr_anglestoforward, loc), arg(std::move(arg)) {}

expr_anglestoright::expr_anglestoright(expr arg) : node(kind::expr_anglestoright), arg(std::move(arg)) {}
expr_anglestoright::expr_anglestoright(const location& loc, expr arg) : node(kind::expr_anglestoright, loc), arg(std::move(arg)) {}

expr_anglestoup::expr_anglestoup(expr arg) : node(kind::expr_anglestoup), arg(std::move(arg)) {}
expr_anglestoup::expr_anglestoup(const location& loc, expr arg) : node(kind::expr_anglestoup, loc), arg(std::move(arg)) {}

expr_vectorscale::expr_vectorscale(expr arg1, expr arg2) : node(kind::expr_vectorscale), arg1(std::move(arg1)), arg2(std::move(arg2)) {}
expr_vectorscale::expr_vectorscale(const location& loc, expr arg1, expr arg2) : node(kind::expr_vectorscale, loc), arg1(std::move(arg1)), arg2(std::move(arg2)) {}

expr_isdefined::expr_isdefined(expr arg) : node(kind::expr_isdefined), arg(std::move(arg)) {}
expr_isdefined::expr_isdefined(const location& loc, expr arg) : node(kind::expr_isdefined, loc), arg(std::move(arg)) {}

expr_arguments::expr_arguments() : node(kind::expr_arguments) {}
expr_arguments::expr_arguments(const location& loc) : node(kind::expr_arguments, loc) {}

expr_parameters::expr_parameters() : node(kind::expr_parameters) {}
expr_parameters::expr_parameters(const location& loc) : node(kind::expr_parameters, loc) {}

expr_pointer::expr_pointer(expr func, expr_arguments::ptr args, call::mode mode) : node(kind::expr_pointer), func(std::move(func)), args(std::move(args)), mode(mode) {}
expr_pointer::expr_pointer(const location& loc, expr func, expr_arguments::ptr args, call::mode mode) : node(kind::expr_pointer, loc), func(std::move(func)), args(std::move(args)), mode(mode) {}

expr_function::expr_function(expr_path::ptr path, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode) : node(kind::expr_function), path(std::move(path)), name(std::move(name)), args(std::move(args)), mode(mode) {}
expr_function::expr_function(const location& loc, expr_path::ptr path, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode) : node(kind::expr_function, loc), path(std::move(path)), name(std::move(name)), args(std::move(args)), mode(mode) {}

expr_method::expr_method(expr obj, ast::call call) : node(kind::expr_method), obj(std::move(obj)), call(std::move(call)) {}
expr_method::expr_method(const location& loc, expr obj, ast::call call) : node(kind::expr_method, loc), obj(std::move(obj)), call(std::move(call)) {}

expr_call::expr_call(ast::call call) : node(kind::expr_call), call(std::move(call)) {}
expr_call::expr_call(const location& loc, ast::call call) : node(kind::expr_call, loc), call(std::move(call)) {}

expr_complement::expr_complement(expr rvalue) : node(kind::expr_complement), rvalue(std::move(rvalue)) {}
expr_complement::expr_complement(const location& loc, expr rvalue) : node(kind::expr_complement, loc), rvalue(std::move(rvalue)) {}

expr_negate::expr_negate(expr rvalue) : node(kind::expr_negate), rvalue(std::move(rvalue)) {}
expr_negate::expr_negate(const location& loc, expr rvalue) : node(kind::expr_negate, loc), rvalue(std::move(rvalue)) {}

expr_not::expr_not(expr rvalue) : node(kind::expr_not), rvalue(std::move(rvalue)) {}
expr_not::expr_not(const location& loc, expr rvalue) : node(kind::expr_not, loc), rvalue(std::move(rvalue)) {}

expr_binary::expr_binary(ast::kind kind, expr lvalue, expr rvalue) : node(kind), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
expr_binary::expr_binary(ast::kind kind, const location& loc, expr lvalue, expr rvalue) : node(kind, loc), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

expr_add::expr_add(expr lvalue, expr rvalue) : expr_binary(kind::expr_add, std::move(lvalue), std::move(rvalue)) {}
expr_add::expr_add(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_add, loc, std::move(lvalue), std::move(rvalue)) {}

expr_sub::expr_sub(expr lvalue, expr rvalue) : expr_binary(kind::expr_sub, std::move(lvalue), std::move(rvalue)) {}
expr_sub::expr_sub(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_sub, loc, std::move(lvalue), std::move(rvalue)) {}

expr_mul::expr_mul( expr lvalue, expr rvalue) : expr_binary(kind::expr_mul, std::move(lvalue), std::move(rvalue)) {}
expr_mul::expr_mul(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_mul, loc, std::move(lvalue), std::move(rvalue)) {}

expr_div::expr_div(expr lvalue, expr rvalue) : expr_binary(kind::expr_div, std::move(lvalue), std::move(rvalue)) {}
expr_div::expr_div(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_div, loc, std::move(lvalue), std::move(rvalue)) {}

expr_mod::expr_mod(expr lvalue, expr rvalue) : expr_binary(kind::expr_mod, std::move(lvalue), std::move(rvalue)) {}
expr_mod::expr_mod(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_mod, loc, std::move(lvalue), std::move(rvalue)) {}

expr_shift_left::expr_shift_left(expr lvalue, expr rvalue) : expr_binary(kind::expr_shift_left, std::move(lvalue), std::move(rvalue)) {}
expr_shift_left::expr_shift_left(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_shift_left, loc, std::move(lvalue), std::move(rvalue)) {}

expr_shift_right::expr_shift_right(expr lvalue, expr rvalue) : expr_binary(kind::expr_shift_right, std::move(lvalue), std::move(rvalue)) {}
expr_shift_right::expr_shift_right(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_shift_right, loc, std::move(lvalue), std::move(rvalue)) {}

expr_bitwise_or::expr_bitwise_or(expr lvalue, expr rvalue) : expr_binary(kind::expr_bitwise_or, std::move(lvalue), std::move(rvalue)) {}
expr_bitwise_or::expr_bitwise_or(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_bitwise_or, loc, std::move(lvalue), std::move(rvalue)) {}

expr_bitwise_and::expr_bitwise_and(expr lvalue, expr rvalue) : expr_binary(kind::expr_bitwise_and, std::move(lvalue), std::move(rvalue)) {}
expr_bitwise_and::expr_bitwise_and(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_bitwise_and, loc, std::move(lvalue), std::move(rvalue)) {}

expr_bitwise_exor::expr_bitwise_exor(expr lvalue, expr rvalue) : expr_binary(kind::expr_bitwise_exor, std::move(lvalue), std::move(rvalue)) {}
expr_bitwise_exor::expr_bitwise_exor(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_bitwise_exor, loc, std::move(lvalue), std::move(rvalue)) {}

expr_equality::expr_equality(expr lvalue, expr rvalue) : expr_binary(kind::expr_equality, std::move(lvalue), std::move(rvalue)) {}
expr_equality::expr_equality(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_equality, loc, std::move(lvalue), std::move(rvalue)) {}

expr_inequality::expr_inequality(expr lvalue, expr rvalue) : expr_binary(kind::expr_inequality, std::move(lvalue), std::move(rvalue)) {}
expr_inequality::expr_inequality(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_inequality, loc, std::move(lvalue), std::move(rvalue)) {}

expr_less_equal::expr_less_equal(expr lvalue, expr rvalue) : expr_binary(kind::expr_less_equal, std::move(lvalue), std::move(rvalue)) {}
expr_less_equal::expr_less_equal(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_less_equal, loc, std::move(lvalue), std::move(rvalue)) {}

expr_greater_equal::expr_greater_equal(expr lvalue, expr rvalue) : expr_binary(kind::expr_greater_equal, std::move(lvalue), std::move(rvalue)) {}
expr_greater_equal::expr_greater_equal(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_greater_equal, loc, std::move(lvalue), std::move(rvalue)) {}

expr_less::expr_less(expr lvalue, expr rvalue) : expr_binary(kind::expr_less, std::move(lvalue), std::move(rvalue)) {}
expr_less::expr_less(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_less, loc, std::move(lvalue), std::move(rvalue)) {}

expr_greater::expr_greater(expr lvalue, expr rvalue) : expr_binary(kind::expr_greater, std::move(lvalue), std::move(rvalue)) {}
expr_greater::expr_greater(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_greater, loc, std::move(lvalue), std::move(rvalue)) {}

expr_or::expr_or(expr lvalue, expr rvalue) : expr_binary(kind::expr_or, std::move(lvalue), std::move(rvalue)) {}
expr_or::expr_or(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_or, loc, std::move(lvalue), std::move(rvalue)) {}

expr_and::expr_and(expr lvalue, expr rvalue) : expr_binary(kind::expr_and, std::move(lvalue), std::move(rvalue)) {}
expr_and::expr_and(const location& loc, expr lvalue, expr rvalue) : expr_binary(kind::expr_and, loc, std::move(lvalue), std::move(rvalue)) {}

expr_ternary::expr_ternary(expr test, expr true_expr, expr false_expr) : node(kind::expr_ternary), test(std::move(test)), true_expr(std::move(true_expr)), false_expr(std::move(false_expr)) {}
expr_ternary::expr_ternary(const location& loc, expr test, expr true_expr, expr false_expr) : node(kind::expr_ternary, loc), test(std::move(test)), true_expr(std::move(true_expr)), false_expr(std::move(false_expr)) {}

expr_increment::expr_increment(expr lvalue, bool prefix) : node(kind::expr_increment), lvalue(std::move(lvalue)), prefix(prefix) {}
expr_increment::expr_increment(const location& loc, expr lvalue, bool prefix) : node(kind::expr_increment, loc), lvalue(std::move(lvalue)), prefix(prefix)  {}

expr_decrement::expr_decrement(expr lvalue, bool prefix) : node(kind::expr_decrement), lvalue(std::move(lvalue)), prefix(prefix) {}
expr_decrement::expr_decrement(const location& loc, expr lvalue, bool prefix) : node(kind::expr_decrement, loc), lvalue(std::move(lvalue)), prefix(prefix)  {}

expr_assign::expr_assign(ast::kind kind, expr lvalue, expr rvalue) : node(kind), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
expr_assign::expr_assign(ast::kind kind, const location& loc, expr lvalue, expr rvalue) : node(kind, loc), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

expr_assign_equal::expr_assign_equal(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_equal, std::move(lvalue), std::move(rvalue)) {}
expr_assign_equal::expr_assign_equal(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_equal, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_add::expr_assign_add(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_add, std::move(lvalue), std::move(rvalue)) {}
expr_assign_add::expr_assign_add(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_add, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_sub::expr_assign_sub(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_sub, std::move(lvalue), std::move(rvalue)) {}
expr_assign_sub::expr_assign_sub(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_sub, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_mul::expr_assign_mul(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_mul, std::move(lvalue), std::move(rvalue)) {}
expr_assign_mul::expr_assign_mul(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_mul, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_div::expr_assign_div(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_div, std::move(lvalue), std::move(rvalue)) {}
expr_assign_div::expr_assign_div(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_div, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_mod::expr_assign_mod(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_mod, std::move(lvalue), std::move(rvalue)) {}
expr_assign_mod::expr_assign_mod(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_mod, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_shift_left::expr_assign_shift_left(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_shift_left, std::move(lvalue), std::move(rvalue)) {}
expr_assign_shift_left::expr_assign_shift_left(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_shift_left, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_shift_right::expr_assign_shift_right(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_shift_right, std::move(lvalue), std::move(rvalue)) {}
expr_assign_shift_right::expr_assign_shift_right(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_shift_right, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_bitwise_or::expr_assign_bitwise_or(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_bitwise_or, std::move(lvalue), std::move(rvalue)) {}
expr_assign_bitwise_or::expr_assign_bitwise_or(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_bitwise_or, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_bitwise_and::expr_assign_bitwise_and(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_bitwise_and, std::move(lvalue), std::move(rvalue)) {}
expr_assign_bitwise_and::expr_assign_bitwise_and(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_bitwise_and, loc, std::move(lvalue), std::move(rvalue)) {}

expr_assign_bitwise_exor::expr_assign_bitwise_exor(expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_bitwise_exor, std::move(lvalue), std::move(rvalue)) {}
expr_assign_bitwise_exor::expr_assign_bitwise_exor(const location& loc, expr lvalue, expr rvalue) : expr_assign(kind::expr_assign_bitwise_exor, loc, std::move(lvalue), std::move(rvalue)) {}

stmt_list::stmt_list() : node(kind::stmt_list) {}
stmt_list::stmt_list(const location& loc) : node(kind::stmt_list, loc) {}

stmt_dev::stmt_dev(ast::stmt_list::ptr list) : node(kind::stmt_dev), list(std::move(list)) {}
stmt_dev::stmt_dev(const location& loc, ast::stmt_list::ptr list) : node(kind::stmt_dev, loc), list(std::move(list)) {}

stmt_expr::stmt_expr(ast::expr expr) : node(kind::stmt_expr), expr(std::move(expr)) {}
stmt_expr::stmt_expr(const location& loc, ast::expr expr) : node(kind::stmt_expr, loc), expr(std::move(expr)) {}

stmt_call::stmt_call(ast::expr expr) : node(kind::stmt_call), expr(std::move(expr)) {}
stmt_call::stmt_call(const location& loc, ast::expr expr) : node(kind::stmt_call, loc), expr(std::move(expr)) {}

stmt_assign::stmt_assign(ast::expr expr) : node(kind::stmt_assign), expr(std::move(expr)) {}
stmt_assign::stmt_assign(const location& loc, ast::expr expr) : node(kind::stmt_assign, loc), expr(std::move(expr)) {}

stmt_endon::stmt_endon(expr obj, expr event) : node(kind::stmt_endon), obj(std::move(obj)), event(std::move(event)) {}
stmt_endon::stmt_endon(const location& loc, expr obj, expr event) : node(kind::stmt_endon, loc), obj(std::move(obj)), event(std::move(event)) {}

stmt_notify::stmt_notify(expr obj, expr event, expr_arguments::ptr args) : node(kind::stmt_notify), obj(std::move(obj)), event(std::move(event)), args(std::move(args)) {}
stmt_notify::stmt_notify(const location& loc, expr obj, expr event, expr_arguments::ptr args) : node(kind::stmt_notify, loc), obj(std::move(obj)), event(std::move(event)), args(std::move(args)) {}

stmt_realwait::stmt_realwait(expr time) : node(kind::stmt_realwait), time(std::move(time)) {}
stmt_realwait::stmt_realwait(const location& loc, expr time) : node(kind::stmt_realwait, loc), time(std::move(time)) {}

stmt_wait::stmt_wait(expr time) : node(kind::stmt_wait), time(std::move(time)) {}
stmt_wait::stmt_wait(const location& loc, expr time) : node(kind::stmt_wait, loc), time(std::move(time)) {}

stmt_waittill::stmt_waittill(expr obj, expr event, expr_arguments::ptr args) : node(kind::stmt_waittill), obj(std::move(obj)), event(std::move(event)), args(std::move(args)) {}
stmt_waittill::stmt_waittill(const location& loc, expr obj, expr event, expr_arguments::ptr args) : node(kind::stmt_waittill, loc), obj(std::move(obj)), event(std::move(event)), args(std::move(args)) {}

stmt_waittillmatch::stmt_waittillmatch(expr obj, expr event, expr_arguments::ptr args) : node(kind::stmt_waittillmatch), obj(std::move(obj)), event(std::move(event)), args(std::move(args)) {}
stmt_waittillmatch::stmt_waittillmatch(const location& loc, expr obj, expr event, expr_arguments::ptr args) : node(kind::stmt_waittillmatch, loc), obj(std::move(obj)), event(std::move(event)), args(std::move(args)) {}

stmt_waittillframeend::stmt_waittillframeend() : node(kind::stmt_waittillframeend) {}
stmt_waittillframeend::stmt_waittillframeend(const location& loc) : node(kind::stmt_waittillframeend, loc) {}

stmt_if::stmt_if(expr test, ast::stmt stmt) : node(kind::stmt_if), test(std::move(test)), stmt(std::move(stmt)), blk(nullptr) {}
stmt_if::stmt_if(const location& loc, expr test, ast::stmt stmt) : node(kind::stmt_if, loc), test(std::move(test)), stmt(std::move(stmt)), blk(nullptr) {}

stmt_ifelse::stmt_ifelse(expr test, stmt stmt_if, stmt stmt_else) : node(kind::stmt_ifelse), test(std::move(test)), stmt_if(std::move(stmt_if)), stmt_else(std::move(stmt_else)), blk_if(nullptr), blk_else(nullptr) {}
stmt_ifelse::stmt_ifelse(const location& loc, expr test, stmt stmt_if, stmt stmt_else) : node(kind::stmt_ifelse, loc), test(std::move(test)), stmt_if(std::move(stmt_if)), stmt_else(std::move(stmt_else)), blk_if(nullptr), blk_else(nullptr) {}

stmt_while::stmt_while(expr test, ast::stmt stmt) : node(kind::stmt_while), test(std::move(test)), stmt(std::move(stmt)), blk(nullptr) {}
stmt_while::stmt_while(const location& loc, expr test, ast::stmt stmt) : node(kind::stmt_while, loc), test(std::move(test)), stmt(std::move(stmt)), blk(nullptr) {}

stmt_dowhile::stmt_dowhile(expr test, ast::stmt stmt) : node(kind::stmt_dowhile), test(std::move(test)), stmt(std::move(stmt)), blk(nullptr) {}
stmt_dowhile::stmt_dowhile(const location& loc, expr test, ast::stmt stmt) : node(kind::stmt_dowhile, loc), test(std::move(test)), stmt(std::move(stmt)), blk(nullptr) {}

stmt_for::stmt_for(ast::stmt init, expr test, ast::stmt iter, ast::stmt stmt) : node(kind::stmt_for), init(std::move(init)), test(std::move(test)), iter(std::move(iter)), stmt(std::move(stmt)), blk(nullptr), blk_iter(nullptr) {}
stmt_for::stmt_for(const location& loc, ast::stmt init, expr test, ast::stmt iter, ast::stmt stmt) : node(kind::stmt_for, loc), init(std::move(init)), test(std::move(test)), iter(std::move(iter)), stmt(std::move(stmt)), blk(nullptr), blk_iter(nullptr) {}

stmt_foreach::stmt_foreach(const location& loc, ast::stmt stmt, bool use_key) : node(kind::stmt_foreach, loc), array_expr(nullptr), value_expr(nullptr), key_expr(nullptr), array(nullptr), pre_expr(nullptr), cond_expr(nullptr), post_expr(nullptr), stmt0(nullptr), stmt(std::move(stmt)), ctx(nullptr), ctx_post(nullptr), use_key(use_key) {}
stmt_foreach::stmt_foreach(ast::expr element, ast::expr container, ast::stmt stmt) : node(kind::stmt_foreach), array_expr(std::move(container)), value_expr(std::move(element)), key_expr(nullptr), array(nullptr), pre_expr(nullptr), cond_expr(nullptr), post_expr(nullptr), stmt0(nullptr), stmt(std::move(stmt)), ctx(nullptr), ctx_post(nullptr), use_key(false) {}
stmt_foreach::stmt_foreach(ast::expr key, ast::expr element, ast::expr container, ast::stmt stmt) : node(kind::stmt_foreach), array_expr(std::move(container)), value_expr(std::move(element)), key_expr(std::move(key)), array(nullptr), pre_expr(nullptr), cond_expr(nullptr), post_expr(nullptr), stmt0(nullptr), stmt(std::move(stmt)), ctx(nullptr), ctx_post(nullptr), use_key(true) {}
stmt_foreach::stmt_foreach(const location& loc, ast::expr element, ast::expr container, ast::stmt stmt) : node(kind::stmt_foreach, loc), array_expr(std::move(container)), value_expr(std::move(element)), key_expr(nullptr), array(nullptr), pre_expr(nullptr), cond_expr(nullptr), post_expr(nullptr), stmt0(nullptr), stmt(std::move(stmt)), ctx(nullptr), ctx_post(nullptr), use_key(false) {}
stmt_foreach::stmt_foreach(const location& loc, ast::expr key, ast::expr element, ast::expr container, ast::stmt stmt) : node(kind::stmt_foreach, loc), array_expr(std::move(container)), value_expr(std::move(element)), key_expr(std::move(key)), array(nullptr), pre_expr(nullptr), cond_expr(nullptr), post_expr(nullptr), stmt0(nullptr), stmt(std::move(stmt)), ctx(nullptr), ctx_post(nullptr), use_key(true) {}

stmt_switch::stmt_switch(expr test, stmt_list::ptr stmt) : node(kind::stmt_switch), test(std::move(test)), stmt(std::move(stmt)), ctx(nullptr) {}
stmt_switch::stmt_switch(const location& loc, expr test, stmt_list::ptr stmt) : node(kind::stmt_switch, loc), test(std::move(test)), stmt(std::move(stmt)), ctx(nullptr) {}

stmt_case::stmt_case(expr label) : node(kind::stmt_case), label(std::move(label)), stmt(nullptr), blk(nullptr) {}
stmt_case::stmt_case(const location& loc, expr label) : node(kind::stmt_case, loc), label(std::move(label)), stmt(nullptr), blk(nullptr) {}
stmt_case::stmt_case(const location& loc, expr label, stmt_list::ptr stmt) : node(kind::stmt_case, loc), label(std::move(label)), stmt(std::move(stmt)), blk(nullptr) {}

stmt_default::stmt_default() : node(kind::stmt_default), stmt(nullptr), blk(nullptr) {}
stmt_default::stmt_default(const location& loc) : node(kind::stmt_default, loc), stmt(nullptr), blk(nullptr) {}
stmt_default::stmt_default(const location& loc, stmt_list::ptr stmt) : node(kind::stmt_default, loc), stmt(std::move(stmt)), blk(nullptr) {}

stmt_break::stmt_break() : node(kind::stmt_break) {}
stmt_break::stmt_break(const location& loc) : node(kind::stmt_break, loc) {}

stmt_continue::stmt_continue() : node(kind::stmt_continue) {}
stmt_continue::stmt_continue(const location& loc) : node(kind::stmt_continue, loc) {}

stmt_return::stmt_return(ast::expr expr) : node(kind::stmt_return), expr(std::move(expr)) {}
stmt_return::stmt_return(const location& loc, ast::expr expr) : node(kind::stmt_return, loc), expr(std::move(expr)) {}

stmt_breakpoint::stmt_breakpoint() : node(kind::stmt_breakpoint) {}
stmt_breakpoint::stmt_breakpoint(const location& loc) : node(kind::stmt_breakpoint, loc) {}

stmt_prof_begin::stmt_prof_begin(expr_arguments::ptr args) : node(kind::stmt_prof_begin), args(std::move(args)) {}
stmt_prof_begin::stmt_prof_begin(const location& loc, expr_arguments::ptr args) : node(kind::stmt_prof_begin, loc), args(std::move(args)) {}

stmt_prof_end::stmt_prof_end(expr_arguments::ptr args) : node(kind::stmt_prof_end), args(std::move(args)) {}
stmt_prof_end::stmt_prof_end(const location& loc, expr_arguments::ptr args) : node(kind::stmt_prof_end, loc), args(std::move(args)) {}

decl_thread::decl_thread(expr_identifier::ptr name, expr_parameters::ptr params, stmt_list::ptr stmt) : node(kind::decl_thread), name(std::move(name)), params(std::move(params)), stmt(std::move(stmt)) {}
decl_thread::decl_thread(const location& loc, expr_identifier::ptr name, expr_parameters::ptr params, stmt_list::ptr stmt) : node(kind::decl_thread, loc), name(std::move(name)), params(std::move(params)), stmt(std::move(stmt)) {}

decl_constant::decl_constant(expr_identifier::ptr name, expr value) : node(kind::decl_constant), name(std::move(name)), value(std::move(value)) {}
decl_constant::decl_constant(const location& loc, expr_identifier::ptr name, expr value) : node(kind::decl_constant, loc), name(std::move(name)), value(std::move(value)) {}

decl_usingtree::decl_usingtree(expr_string::ptr name) : node(kind::decl_usingtree), name(std::move(name)) {}
decl_usingtree::decl_usingtree(const location& loc, expr_string::ptr name) : node(kind::decl_usingtree, loc), name(std::move(name)) {}

decl_dev_begin::decl_dev_begin() : node(kind::decl_dev_begin) {}
decl_dev_begin::decl_dev_begin(const location& loc) : node(kind::decl_dev_begin, loc) {}

decl_dev_end::decl_dev_end() : node(kind::decl_dev_end) {}
decl_dev_end::decl_dev_end(const location& loc) : node(kind::decl_dev_end, loc) {}

include::include(expr_path::ptr path) : node(kind::include), path(std::move(path)) {}
include::include(const location& loc, expr_path::ptr path) : node(kind::include, loc), path(std::move(path)) {}

program::program() : node(kind::program) {}
program::program(const location& loc) : node(kind::program, loc) {}

asm_loc::asm_loc(const std::string& value) : node(kind::asm_loc), value(value) {}
asm_loc::asm_loc(const location& loc, const std::string& value) : node(kind::asm_loc, loc), value(value) {}

asm_jump::asm_jump(const std::string& value) : node(kind::asm_jump), value(std::move(value)) {}
asm_jump::asm_jump(const location& loc, const std::string& value) : node(kind::asm_jump, loc), value(value) {}

asm_jump_back::asm_jump_back(const std::string& value) : node(kind::asm_jump_back), value(value) {}
asm_jump_back::asm_jump_back(const location& loc, const std::string& value) : node(kind::asm_jump_back, loc), value(value) {}

asm_jump_cond::asm_jump_cond(ast::expr expr, const std::string& value) : node(kind::asm_jump_cond), expr(std::move(expr)), value(value) {}
asm_jump_cond::asm_jump_cond(const location& loc, ast::expr expr, const std::string& value) : node(kind::asm_jump_cond, loc), expr(std::move(expr)), value(value) {}

asm_jump_true_expr::asm_jump_true_expr(ast::expr expr, const std::string& value) : node(kind::asm_jump_true_expr), expr(std::move(expr)), value(value) {}
asm_jump_true_expr::asm_jump_true_expr(const location& loc, ast::expr expr, const std::string& value) : node(kind::asm_jump_true_expr, loc), expr(std::move(expr)), value(value) {}

asm_jump_false_expr::asm_jump_false_expr(ast::expr expr, const std::string& value) : node(kind::asm_jump_false_expr), expr(std::move(expr)), value(value) {}
asm_jump_false_expr::asm_jump_false_expr(const location& loc, ast::expr expr, const std::string& value) : node(kind::asm_jump_false_expr, loc), expr(std::move(expr)), value(value) {}

asm_switch::asm_switch(ast::expr expr, const std::string& value) : node(kind::asm_switch), expr(std::move(expr)), value(value) {}
asm_switch::asm_switch(const location& loc, ast::expr expr, const std::string& value) : node(kind::asm_switch, loc), expr(std::move(expr)), value(value) {}

asm_endswitch::asm_endswitch(std::vector<std::string> data, const std::string& count) : node(kind::asm_endswitch), data(std::move(data)), count(count) {}
asm_endswitch::asm_endswitch(const location& loc, std::vector<std::string> data, const std::string& count) : node(kind::asm_endswitch, loc), data(std::move(data)), count(count) {}

asm_prescriptcall::asm_prescriptcall() : node(kind::asm_prescriptcall) {}
asm_prescriptcall::asm_prescriptcall(const location& loc) : node(kind::asm_prescriptcall, loc) {}

asm_voidcodepos::asm_voidcodepos() : node(kind::asm_voidcodepos) {}
asm_voidcodepos::asm_voidcodepos(const location& loc) : node(kind::asm_voidcodepos, loc) {}

asm_dev::asm_dev(const std::string& value) : node(kind::asm_dev), value(std::move(value)) {}
asm_dev::asm_dev(const location& loc, const std::string& value) : node(kind::asm_dev, loc), value(value) {}

auto expr_true::print() const -> std::string
{
    return "true";
}

auto expr_false::print() const -> std::string
{
    return "false";
}

auto expr_integer::print() const -> std::string
{
    return value;
}

auto expr_float::print() const -> std::string
{
    return value;
}

auto expr_vector::print() const -> std::string
{
    return "( "s + x.print() + ", " + y.print() + ", " + z.print() + " )";
}

auto expr_hash::print() const -> std::string
{
    return value.starts_with("_hash_") ? value : ("\"" + value + "\"");
}

auto expr_string::print() const -> std::string
{
    return utils::string::to_literal(value);
}

auto expr_istring::print() const -> std::string
{
    return "&"s += utils::string::to_literal(value);
}

auto expr_path::print() const -> std::string
{
    return utils::string::backslash(value);
}

auto expr_identifier::print() const -> std::string
{
    return value;
}

auto expr_animation::print() const -> std::string
{
    return "%"s += value;
}

auto expr_level::print() const -> std::string
{
    return "level";
}

auto expr_anim::print() const -> std::string
{
    return "anim";
}

auto expr_self::print() const -> std::string
{
    return "self";
}

auto expr_game::print() const -> std::string
{
    return "game";
}

auto expr_undefined::print() const -> std::string
{
    return "undefined";
}

auto expr_empty_array::print() const -> std::string
{
    return "[]";
}

auto expr_paren::print() const -> std::string
{
    return "( " + child.print() + " )";
}

auto expr_size::print() const -> std::string
{
    return obj.print() + ".size";
}

auto expr_field::print() const -> std::string
{
    return obj.print() + "." + field->print();
}

auto expr_array::print() const -> std::string
{
    return obj.print() + "[" + key.print() + "]";
}

auto expr_reference::print() const -> std::string
{
    return path->print() + "::" + name->print();
}

auto expr_getnextarraykey::print() const -> std::string
{
    return "getnextarraykey( " + arg1.print() + ", " + arg2.print() + " )";
}

auto expr_getfirstarraykey::print() const -> std::string
{
    return "getfirstarraykey( " + arg.print() + " )";
}

auto expr_getdvarcoloralpha::print() const -> std::string
{
    return "getdvarcoloralpha( " + arg.print() + " )";
}

auto expr_getdvarcolorblue::print() const -> std::string
{
    return "getdvarcolorblue( " + arg.print() + " )";
}

auto expr_getdvarcolorgreen::print() const -> std::string
{
    return "getdvarcolorgreen( " + arg.print() + " )";
}

auto expr_getdvarcolorred::print() const -> std::string
{
    return "getdvarcolorred( " + arg.print() + " )";
}

auto expr_getdvarvector::print() const -> std::string
{
    return "getdvarvector( " + arg.print() + " )";
}

auto expr_getdvarfloat::print() const -> std::string
{
    return "getdvarfloat( " + arg.print() + " )";
}

auto expr_getdvarint::print() const -> std::string
{
    return "getdvarint( " + arg.print() + " )";
}

auto expr_getdvar::print() const -> std::string
{
    return "getdvar( " + arg.print() + " )";
}

auto expr_gettime::print() const -> std::string
{
    return "gettime()";
}

auto expr_abs::print() const -> std::string
{
    return "abs( " + arg.print() + " )";
}

auto expr_vectortoangles::print() const -> std::string
{
    return "vectortoangles( " + arg.print() + " )";
}

auto expr_angleclamp180::print() const -> std::string
{
    return "angleclamp180( " + arg.print() + " )";
}

auto expr_anglestoforward::print() const -> std::string
{
    return "anglestoforward( " + arg.print() + " )";
}

auto expr_anglestoright::print() const -> std::string
{
    return "anglestoright( " + arg.print() + " )";
}

auto expr_anglestoup::print() const -> std::string
{
    return "anglestoup( " + arg.print() + " )";
}

auto expr_vectorscale::print() const -> std::string
{
    return "vectorscale( " + arg1.print() + ", " + arg2.print() + " )";
}

auto expr_isdefined::print() const -> std::string
{
    return "isdefined( " + arg.print() + " )";
}

auto expr_arguments::print() const -> std::string
{
    std::string data;

    for (const auto& entry : list)
    {
        data += " " + entry.print();
        data += (&entry != &list.back()) ? "," : " ";
    }

    return data;
}

auto expr_parameters::print() const -> std::string
{
    std::string data;

    for (const auto& entry : list)
    {
        data += " " + entry->print();
        data += (&entry != &list.back()) ? "," : " ";
    }

    return data;
}

auto expr_pointer::print() const -> std::string
{
    std::string data;

    if (mode == call::mode::thread)
        data += "thread ";

    return data += "[[ "s + func.print() + " ]](" + args->print() + ")";
}

auto expr_function::print() const -> std::string
{
    std::string data;

    if (mode == call::mode::thread)
        data += "thread ";

    if (path->value != "")
        data += path->print() + "::";

    return data += name->print() + "(" + args->print() + ")";
}

auto expr_method::print() const -> std::string
{
    return obj.print() + " " + call.print();
}

auto expr_call::print() const -> std::string
{
    return call.print();
}

auto expr_complement::print() const -> std::string
{
    return "~" + rvalue.print();
}

auto expr_negate::print() const -> std::string
{
    return "-" + rvalue.print();
}

auto expr_not::print() const -> std::string
{
    return "!" + rvalue.print();
}

auto expr_add::print() const -> std::string
{
    return lvalue.print() + " + " + rvalue.print();
}

auto expr_sub::print() const -> std::string
{
    return lvalue.print() + " - " + rvalue.print();
}

auto expr_mul::print() const -> std::string
{
    return lvalue.print() + " * " + rvalue.print();
}

auto expr_div::print() const -> std::string
{
    return lvalue.print() + " / " + rvalue.print();
}

auto expr_mod::print() const -> std::string
{
    return lvalue.print() + " % " + rvalue.print();
}

auto expr_shift_left::print() const -> std::string
{
    return lvalue.print() + " << " + rvalue.print();
}

auto expr_shift_right::print() const -> std::string
{
    return lvalue.print() + " >> " + rvalue.print();
}

auto expr_bitwise_or::print() const -> std::string
{
    return lvalue.print() + " | " + rvalue.print();
}

auto expr_bitwise_and::print() const -> std::string
{
    return lvalue.print() + " & " + rvalue.print();
}

auto expr_bitwise_exor::print() const -> std::string
{
    return lvalue.print() + " ^ " + rvalue.print();
}

auto expr_equality::print() const -> std::string
{
    return lvalue.print() + " == " + rvalue.print();
}

auto expr_inequality::print() const -> std::string
{
    return lvalue.print() + " != " + rvalue.print();
}

auto expr_less_equal::print() const -> std::string
{
    return lvalue.print() + " <= " + rvalue.print();
}

auto expr_greater_equal::print() const -> std::string
{
    return lvalue.print() + " >= " + rvalue.print();
}

auto expr_less::print() const -> std::string
{
    return lvalue.print() + " < " + rvalue.print();
}

auto expr_greater::print() const -> std::string
{
    return lvalue.print() + " > " + rvalue.print();
}

auto expr_or::print() const -> std::string
{
    return lvalue.print() + " || " + rvalue.print();
}

auto expr_and::print() const -> std::string
{
    return lvalue.print() + " && " + rvalue.print();
}

auto expr_ternary::print() const -> std::string
{
    return test.print() + " ? " + true_expr.print() + " : " + false_expr.print();
}

auto expr_increment::print() const -> std::string
{
    if (prefix) return "++" + lvalue.print();
    return lvalue.print() + "++";
}

auto expr_decrement::print() const -> std::string
{
    if (prefix) return "--" + lvalue.print();
    return lvalue.print() + "--";
}

auto expr_assign_equal::print() const -> std::string
{
    return lvalue.print() + " = " + rvalue.print();
};

auto expr_assign_add::print() const -> std::string
{
    return lvalue.print() + " += " + rvalue.print() ;
};

auto expr_assign_sub::print() const -> std::string
{
    return lvalue.print() + " -= " + rvalue.print() ;
};

auto expr_assign_mul::print() const -> std::string
{
    return lvalue.print() + " *= " + rvalue.print() ;
};

auto expr_assign_div::print() const -> std::string
{
    return lvalue.print() + " /= " + rvalue.print() ;
};

auto expr_assign_mod::print() const -> std::string
{
    return lvalue.print() + " %= " + rvalue.print() ;
};

auto expr_assign_shift_left::print() const -> std::string
{
    return lvalue.print() + " <<= " + rvalue.print() ;
};

auto expr_assign_shift_right::print() const -> std::string
{
    return lvalue.print() + " >>= " + rvalue.print() ;
};

auto expr_assign_bitwise_or::print() const -> std::string
{
    return lvalue.print() + " |= " + rvalue.print();
}

auto expr_assign_bitwise_and::print() const -> std::string
{
    return lvalue.print() + " &= " + rvalue.print();
}

auto expr_assign_bitwise_exor::print() const -> std::string
{
    return lvalue.print() + " ^= " + rvalue.print();
}

auto stmt_list::print() const -> std::string
{
    if (is_expr)
    {
        if (list.size() > 0)
        {
            auto s = list[0].print();
            s.pop_back();
            return s;
        }
        else return "";
    }

    std::string data;
    bool last_special = false;
    bool last_devblock = false;
    auto block_pad = indented(indent_);
    indent_ += 4;

    auto stmts_pad = indented(indent_);

    if (!is_case)
        data += block_pad + "{\n";

    for (const auto& stmt : list)
    {
        if (((&stmt != &list.front() && stmt.as_node->is_special_stmt()) || last_special) && stmt != kind::stmt_dev && !last_devblock)
            data += "\n";

        if (stmt == kind::stmt_dev)
        {
            data += stmt.print();
            last_devblock = true;
        }
        else
        {
            data += stmts_pad + stmt.print();
            last_devblock = false;
        }

        if (&stmt != &list.back())
            data += "\n";

        if (stmt.as_node->is_special_stmt())
            last_special = true;
        else
            last_special = false;
    }

    indent_ -= 4;

    if (!is_case)
        data += "\n" + block_pad + "}";

    return data;
}

auto stmt_dev::print() const -> std::string
{
    std::string data;
    bool last_special = false;

    auto stmts_pad = indented(indent_);

    data += "/#\n";

    for (const auto& stmt : list->list)
    {
        if ((&stmt != &list->list.front() && stmt.as_node->is_special_stmt()) || last_special)
            data += "\n";

        data += stmts_pad + stmt.print();

        if (&stmt != &list->list.back())
            data += "\n";

        if (stmt.as_node->is_special_stmt())
            last_special = true;
        else
            last_special = false;
    }

    data += "\n#/";

    return data;
}

auto stmt_expr::print() const -> std::string
{
    return expr.print();
}

auto stmt_call::print() const -> std::string
{
    return expr.print() + ";";
};

auto stmt_assign::print() const -> std::string
{
    return expr.print() + ";";
};

auto stmt_endon::print() const -> std::string
{
    return obj.print() + " endon( " + event.print() + " );";
};

auto stmt_notify::print() const -> std::string
{
    if (args->list.size() == 0)
        return obj.print() + " notify( " + event.print() + " );";
    else
        return obj.print() + " notify( " + event.print() + "," + args->print() + ");";
};

auto stmt_realwait::print() const -> std::string
{
    if (time == kind::expr_float || time == kind::expr_integer)
        return "realwait " + time.print() + ";";
    else
        return "realwait( " + time.print() + " );";
};

auto stmt_wait::print() const -> std::string
{
    if (time == kind::expr_float || time == kind::expr_integer)
        return "wait " + time.print() + ";";
    else
        return "wait( " + time.print() + " );";
};

auto stmt_waittill::print() const -> std::string
{
    if (args->list.size() == 0)
        return obj.print() + " waittill( " + event.print() + " );";
    else
        return obj.print() + " waittill( " + event.print() + "," + args->print() + ");";
};

auto stmt_waittillmatch::print() const -> std::string
{
    if (args->list.size() == 0)
        return obj.print() + " waittillmatch( " + event.print() + " );";
    else
        return obj.print() + " waittillmatch( " + event.print() + "," + args->print() + ");";
};

auto stmt_waittillframeend::print() const -> std::string
{
    return "waittillframeend;";
};

auto stmt_if::print() const -> std::string
{
    std::string data = "if ( " + test.print() + " )\n";

    if (stmt == kind::stmt_list)
    {
        data += stmt.as_list->print();
    }
    else
    {
        indent_ += 4;
        data += indented(indent_) + stmt.print();
        indent_ -= 4;
    }

    return data;
};

auto stmt_ifelse::print() const -> std::string
{
    std::string pad = indented(indent_);
    std::string data = "if ( " + test.print() + " )\n";

    if (stmt_if == kind::stmt_list)
    {
        data += stmt_if.print();
    }
    else
    {
        indent_ += 4;
        data += indented(indent_) + stmt_if.print();
        indent_ -= 4;
    }

    data += "\n" + pad + "else";

    if (stmt_else == kind::stmt_list)
    {
        data += "\n" + stmt_else.as_list->print();
    }
    else
    {
        if (stmt_else == kind::stmt_if || stmt_else == kind::stmt_ifelse)
        {
            data += " " + stmt_else.print();
        }
        else
        {
            indent_ += 4;
            data += "\n" + indented(indent_) + stmt_else.print();
            indent_ -= 4;
        }
    }

    return data;
};

auto stmt_while::print() const -> std::string
{
    std::string data;

    if (test == kind::null)
    {
        data += "while ( true )\n";
    }
    else
    {
        data += "while ( " + test.print() + " )\n";
    }

    std::string pad = indented(indent_);

    if (stmt == kind::stmt_list)
    {
        data += stmt.print();
    }
    else
    {
        indent_ += 4;
        data += indented(indent_) + stmt.print();
        indent_ -= 4;
    }

    return data;
};

auto stmt_dowhile::print() const -> std::string
{
    std::string data;

    data += "do\n";

    std::string pad = indented(indent_);

    if (stmt == kind::stmt_list)
    {
        data += stmt.print();
    }
    else
    {
        indent_ += 4;
        data += indented(indent_) + stmt.print();
        indent_ -= 4;
    }

    if (test == kind::null)
    {
        data += "\n" + pad + "while ( true );";
    }
    else
    {
        data += "\n" + pad + "while ( " + test.print() + " );";
    }

    return data;
};

auto stmt_for::print() const -> std::string
{
    std::string data;

    if (test == kind::null)
    {
        data += "for (;;)\n";
    }
    else
    {
        data += "for ( " + init.print() + "; " + test.print() + "; " + iter.print() + " )";
        data += "\n";
    }

    if (stmt == kind::stmt_list)
    {
        data += stmt.print();
    }
    else
    {
        indent_ += 4;
        data += indented(indent_) + stmt.print();
        indent_ -= 4;
    }

    return data;
};

auto stmt_foreach::print() const -> std::string
{
    std::string data;

    data += "foreach ( ";

    if (use_key) data += key_expr.print() + ", ";

    data += value_expr.print() + " in " + array_expr.print() + " )\n";

    if (stmt == kind::stmt_list)
    {
        data += stmt.print();
    }
    else
    {
        indent_ += 4;
        data += indented(indent_) + stmt.print();
        indent_ -= 4;
    }

    return data;
};

auto stmt_switch::print() const -> std::string
{
    std::string data;

    data += "switch ( " + test.print() + " )\n";
    data += stmt->print();

    return data;
};

auto stmt_case::print() const -> std::string
{
    if (stmt != nullptr && stmt->list.size() == 0)
        return "case " + label.print() + ":";
    else
        return "case " + label.print() + ":\n" + stmt->print();
};

auto stmt_default::print() const -> std::string
{
    if (stmt != nullptr && stmt->list.size() == 0)
        return "default:";
    else
        return "default:\n" + stmt->print();
};

auto stmt_break::print() const -> std::string
{
    return "break;";
};

auto stmt_continue::print() const -> std::string
{
    return "continue;";
};

auto stmt_return::print() const -> std::string
{
    if (expr == kind::null) return "return;";

    return "return " + expr.print() + ";";
};

auto stmt_breakpoint::print() const -> std::string
{
    return "breakpoint;";
};

auto stmt_prof_begin::print() const -> std::string
{
    return "prof_begin(" + args->print() + ");";
};

auto stmt_prof_end::print() const -> std::string
{
    return "prof_end(" + args->print() + ");";
};

auto decl_thread::print() const -> std::string
{
    return name->print() + "(" + params->print() + ")" + "\n" + stmt->print() + "\n";
}

auto decl_constant::print() const -> std::string
{
    return name->print() + " = "s + value.print() + ";\n";
}

auto decl_usingtree::print() const -> std::string
{
    return "#using_animtree"s + "(" + name->print() + ");\n";
}

auto decl_dev_begin::print() const -> std::string
{
    return "/#\n";
}

auto decl_dev_end::print() const -> std::string
{
    return "#/\n";
}

auto include::print() const -> std::string
{
    return "#include"s + " " + path->print() + ";\n";
}

auto program::print() const -> std::string
{
    std::string data;

    for (const auto& include : includes)
    {
        data += include->print();
    }

    data += "\n";

    for (const auto& entry : declarations)
    {
        data += entry.print();

        if (&entry != &declarations.back())
            data += "\n";
    }

    return data;
}

auto asm_loc::print() const -> std::string
{
    return value + ":";
}

auto asm_jump::print() const -> std::string
{
    return "asm_jump( " + value + " );";
}

auto asm_jump_back::print() const -> std::string
{
    return "asm_jump_back( " + value + " );";
}

auto asm_jump_cond::print() const -> std::string
{
    return "asm_cond( " + expr.print() + ", " + value + " );";
}

auto asm_jump_true_expr::print() const -> std::string
{
    return "asm_expr_true( " + value + " );";
}

auto asm_jump_false_expr::print() const -> std::string
{
    return "asm_expr_false( " + value + " );";
}

auto asm_switch::print() const -> std::string
{
    return "asm_switch( " + expr.print() + ", " + value + " );";
}

auto asm_endswitch::print() const -> std::string
{
    std::string result;

    for (auto& entry : data)
    {
        result += " " + entry;
    }
    return "asm_endswitch( " + count + result + " );";
}

auto asm_prescriptcall::print() const -> std::string
{
    return "asm_prescriptcall();";
}

auto asm_voidcodepos::print() const -> std::string
{
    return "asm_voidcodepos();";
}

auto asm_dev::print() const -> std::string
{
    return "devblock( " + value + " );";
}

// operators

bool operator==(const node& n, kind k)
{
    return n.kind_ == k;
}

bool operator==(const node& lhs, const node& rhs)
{
    return lhs.kind_ == rhs.kind_;
}

bool operator==(const expr_true&, const expr_true&)
{
    return true;
}

bool operator==(const expr_false&, const expr_false&)
{
    return true;
}

bool operator==(const expr_integer& lhs, const expr_integer& rhs)
{
    return lhs.value == rhs.value;
}

bool operator==(const expr_float& lhs, const expr_float& rhs)
{
    return lhs.value == rhs.value;
}

bool operator==(const expr_vector& lhs, const expr_vector& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator==(const expr_hash& lhs, const expr_hash& rhs)
{
    return lhs.value == rhs.value;
}

bool operator==(const expr_string& lhs, const expr_string& rhs)
{
    return lhs.value == rhs.value;
}

bool operator==(const expr_istring& lhs, const expr_istring& rhs)
{
    return lhs.value == rhs.value;
}

bool operator==(const expr_path& lhs, const expr_path& rhs)
{
    return lhs.value == rhs.value;
}

bool operator==(const expr_identifier& lhs, const expr_identifier& rhs)
{
    return lhs.value == rhs.value;
}

bool operator==(const expr_animation& lhs, const expr_animation& rhs)
{
    return lhs.value == rhs.value;
}

bool operator==(const expr_level&, const expr_level&)
{
    return true;
}

bool operator==(const expr_anim&, const expr_anim&)
{
    return true;
}

bool operator==(const expr_self&, const expr_self&)
{
    return true;
}

bool operator==(const expr_game&, const expr_game&)
{
    return true;
}

bool operator==(const expr_undefined&, const expr_undefined&)
{
    return true;
}

bool operator==(const expr_empty_array&, const expr_empty_array&)
{
    return true;
}

bool operator==(const expr_paren& lhs, const expr_paren& rhs)
{
    return lhs.child == rhs.child;
}

bool operator==(const expr_size& lhs, const expr_size& rhs)
{
    return lhs.obj == rhs.obj;
}

bool operator==(const expr_field& lhs, const expr_field& rhs)
{
    return lhs.obj == rhs.obj && *lhs.field == *rhs.field;
}

bool operator==(const expr_array& lhs, const expr_array& rhs)
{
    return lhs.obj == rhs.obj && lhs.key == rhs.key;
}

call::call() : as_node(nullptr) {}

call::call(std::unique_ptr<node> value) : as_node(std::move(value)) {}

call::call(call&& value)
{
    new(&as_node) std::unique_ptr<node>(std::move(value.as_node));
}

call::~call()
{
    if (as_node == nullptr) return;

    switch (as_node->kind())
    {
        case kind::null: as_node.~unique_ptr(); return;
        case kind::expr_pointer: as_pointer.~unique_ptr(); return;
        case kind::expr_function: as_function.~unique_ptr(); return;
        default: return;
    }
}

bool operator==(const call& lhs, kind rhs)
{
    return *lhs.as_node == rhs;
}

auto call::loc() const -> location
{
    return as_node->loc();
}

auto call::kind() const -> ast::kind
{
    return as_node->kind();
}

auto call::print() const -> std::string
{
    return as_node->print();
}

expr::expr() : as_node(nullptr) {}

expr::expr(std::unique_ptr<node> value) : as_node(std::move(value)) {}

expr::expr(expr&& value)
{
    new(&as_node) std::unique_ptr<node>(std::move(value.as_node));
}

expr& expr::operator=(expr&& value)
{
    new(&as_node) std::unique_ptr<node>(std::move(value.as_node));
    return *(expr*)&as_node;
}

expr::~expr()
{
    if (as_node == nullptr) return;

    switch (as_node->kind())
    {
        case kind::null: as_node.~unique_ptr(); return;
        case kind::expr_true: as_true.~unique_ptr(); return;
        case kind::expr_false: as_false.~unique_ptr(); return;
        case kind::expr_integer: as_integer.~unique_ptr(); return;
        case kind::expr_float: as_float.~unique_ptr(); return;
        case kind::expr_vector: as_vector.~unique_ptr(); return;
        case kind::expr_hash: as_hash.~unique_ptr(); return;
        case kind::expr_string: as_string.~unique_ptr(); return;
        case kind::expr_istring: as_istring.~unique_ptr(); return;
        case kind::expr_path: as_path.~unique_ptr(); return;
        case kind::expr_identifier: as_identifier.~unique_ptr(); return;
        case kind::expr_animation: as_animation.~unique_ptr(); return;
        case kind::expr_level: as_level.~unique_ptr(); return;
        case kind::expr_anim: as_anim.~unique_ptr(); return;
        case kind::expr_self: as_self.~unique_ptr(); return;
        case kind::expr_game: as_game.~unique_ptr(); return;
        case kind::expr_undefined: as_undefined.~unique_ptr(); return;
        case kind::expr_empty_array: as_empty_array.~unique_ptr(); return;
        case kind::expr_paren: as_paren.~unique_ptr(); return;
        case kind::expr_size: as_size.~unique_ptr(); return;
        case kind::expr_field: as_field.~unique_ptr(); return;
        case kind::expr_array: as_array.~unique_ptr(); return;
        case kind::expr_reference: as_reference.~unique_ptr(); return;
        case kind::expr_getnextarraykey: as_getnextarraykey.~unique_ptr(); return;
        case kind::expr_getfirstarraykey: as_getfirstarraykey.~unique_ptr(); return;
        case kind::expr_getdvarcoloralpha: as_getdvarcoloralpha.~unique_ptr(); return;
        case kind::expr_getdvarcolorblue: as_getdvarcolorblue.~unique_ptr(); return;
        case kind::expr_getdvarcolorgreen: as_getdvarcolorgreen.~unique_ptr(); return;
        case kind::expr_getdvarcolorred: as_getdvarcolorred.~unique_ptr(); return;
        case kind::expr_getdvarvector: as_getdvarvector.~unique_ptr(); return;
        case kind::expr_getdvarfloat: as_getdvarfloat.~unique_ptr(); return;
        case kind::expr_getdvarint: as_getdvarint.~unique_ptr(); return;
        case kind::expr_getdvar: as_getdvar.~unique_ptr(); return;
        case kind::expr_gettime: as_gettime.~unique_ptr(); return;
        case kind::expr_abs: as_abs.~unique_ptr(); return;
        case kind::expr_vectortoangles: as_vectortoangles.~unique_ptr(); return;
        case kind::expr_angleclamp180: as_angleclamp180.~unique_ptr(); return;
        case kind::expr_anglestoforward: as_anglestoforward.~unique_ptr(); return;
        case kind::expr_anglestoright: as_anglestoright.~unique_ptr(); return;
        case kind::expr_anglestoup: as_anglestoup.~unique_ptr(); return;
        case kind::expr_vectorscale: as_vectorscale.~unique_ptr(); return;
        case kind::expr_isdefined: as_isdefined.~unique_ptr(); return;
        case kind::expr_arguments: as_arguments.~unique_ptr(); return;
        case kind::expr_parameters: as_parameters.~unique_ptr(); return;
        case kind::expr_pointer: as_pointer.~unique_ptr(); return;
        case kind::expr_function: as_function.~unique_ptr(); return;
        case kind::expr_method: as_method.~unique_ptr(); return;
        case kind::expr_call: as_call.~unique_ptr(); return;
        case kind::expr_complement: as_complement.~unique_ptr(); return;
        case kind::expr_negate: as_negate.~unique_ptr(); return;
        case kind::expr_not: as_not.~unique_ptr(); return;
        case kind::expr_add: as_add.~unique_ptr(); return;
        case kind::expr_sub: as_sub.~unique_ptr(); return;
        case kind::expr_mul: as_mul.~unique_ptr(); return;
        case kind::expr_div: as_div.~unique_ptr(); return;
        case kind::expr_mod: as_mod.~unique_ptr(); return;
        case kind::expr_shift_left: as_shift_left.~unique_ptr(); return;
        case kind::expr_shift_right: as_shift_right.~unique_ptr(); return;
        case kind::expr_bitwise_or: as_bitwise_or.~unique_ptr(); return;
        case kind::expr_bitwise_and: as_bitwise_and.~unique_ptr(); return;
        case kind::expr_bitwise_exor: as_bitwise_exor.~unique_ptr(); return;
        case kind::expr_equality: as_equality.~unique_ptr(); return;
        case kind::expr_inequality: as_inequality.~unique_ptr(); return;
        case kind::expr_less_equal: as_less_equal.~unique_ptr(); return;
        case kind::expr_greater_equal: as_greater_equal.~unique_ptr(); return;
        case kind::expr_less: as_less.~unique_ptr(); return;
        case kind::expr_greater: as_greater.~unique_ptr(); return;
        case kind::expr_or: as_or.~unique_ptr(); return;
        case kind::expr_and: as_and.~unique_ptr(); return;
        case kind::expr_ternary: as_ternary.~unique_ptr(); return;
        case kind::expr_increment: as_increment.~unique_ptr(); return;
        case kind::expr_decrement: as_decrement.~unique_ptr(); return;
        case kind::expr_assign_equal: as_assign_equal.~unique_ptr(); return;
        case kind::expr_assign_add: as_assign_add.~unique_ptr(); return;
        case kind::expr_assign_sub: as_assign_sub.~unique_ptr(); return;
        case kind::expr_assign_mul: as_assign_mul.~unique_ptr(); return;
        case kind::expr_assign_div: as_assign_div.~unique_ptr(); return;
        case kind::expr_assign_mod: as_assign_mod.~unique_ptr(); return;
        case kind::expr_assign_shift_left: as_assign_shift_left.~unique_ptr(); return;
        case kind::expr_assign_shift_right: as_assign_shift_right.~unique_ptr(); return;
        case kind::expr_assign_bitwise_or: as_assign_bw_or.~unique_ptr(); return;
        case kind::expr_assign_bitwise_and: as_assign_bw_and.~unique_ptr(); return;
        case kind::expr_assign_bitwise_exor: as_assign_bw_exor.~unique_ptr(); return;
        default: return;
    }
}

bool operator!=(const expr& lhs, kind rhs)
{
    return lhs.as_node->kind() != rhs;
}

bool operator==(const expr& lhs, kind rhs)
{
    return *lhs.as_node == rhs;
}

bool operator==(const expr& lhs, const expr& rhs)
{
    if (!(*lhs.as_node == *rhs.as_node)) return false;

    switch(lhs.as_node->kind())
    {
        case kind::expr_true: return *lhs.as_true == *rhs.as_true;
        case kind::expr_false: return *lhs.as_false == *rhs.as_false;
        case kind::expr_integer: return *lhs.as_integer == *rhs.as_integer;
        case kind::expr_float: return *lhs.as_float == *rhs.as_float;
        case kind::expr_vector: return *lhs.as_vector == *rhs.as_vector;
        case kind::expr_hash: return *lhs.as_hash == *rhs.as_hash;
        case kind::expr_string: return *lhs.as_string == *rhs.as_string;
        case kind::expr_istring: return *lhs.as_istring == *rhs.as_istring;
        case kind::expr_path: return *lhs.as_path == *rhs.as_path;
        case kind::expr_identifier: return *lhs.as_identifier == *rhs.as_identifier;
        case kind::expr_animation: return *lhs.as_animation == *rhs.as_animation;
        case kind::expr_level: return *lhs.as_level == *rhs.as_level;
        case kind::expr_anim: return *lhs.as_anim == *rhs.as_anim;
        case kind::expr_self: return *lhs.as_self == *rhs.as_self;
        case kind::expr_game: return *lhs.as_game == *rhs.as_game;
        case kind::expr_undefined: return *lhs.as_undefined == *rhs.as_undefined;
        case kind::expr_empty_array: return *lhs.as_empty_array == *rhs.as_empty_array;
        case kind::expr_paren: return *lhs.as_paren == *rhs.as_paren;
        case kind::expr_size: return *lhs.as_size == *rhs.as_size;
        case kind::expr_field: return *lhs.as_field == *rhs.as_field;
        case kind::expr_array: return *lhs.as_array == *rhs.as_array;
        default: return false;
    }
}

auto expr::loc() const -> location
{
    return as_node->loc();
}

auto expr::kind() const -> ast::kind
{
    return as_node->kind();
}

auto expr::print() const -> std::string
{
    return as_node->print();
}

stmt::stmt() : as_node(nullptr) {}

stmt::stmt(std::unique_ptr<node> value) : as_node(std::move(value)) {}

stmt::stmt(stmt&& value)
{
    new(&as_node) std::unique_ptr<node>(std::move(value.as_node));
}

stmt& stmt::operator=(stmt&& value)
{
    new(&as_node) std::unique_ptr<node>(std::move(value.as_node));
    return *(stmt*)&as_node;
}

stmt::~stmt()
{
    if (as_node == nullptr) return;

    switch (as_node->kind())
    {
        case kind::null: as_node.~unique_ptr(); return;
        case kind::stmt_list: as_list.~unique_ptr(); return;
        case kind::stmt_dev: as_dev.~unique_ptr(); return;
        case kind::stmt_expr: as_expr.~unique_ptr(); return;
        case kind::stmt_call: as_call.~unique_ptr(); return;
        case kind::stmt_assign: as_assign.~unique_ptr(); return;
        case kind::stmt_endon: as_endon.~unique_ptr(); return;
        case kind::stmt_notify: as_notify.~unique_ptr(); return;
        case kind::stmt_realwait: as_realwait.~unique_ptr(); return;
        case kind::stmt_wait: as_wait.~unique_ptr(); return;
        case kind::stmt_waittill: as_waittill.~unique_ptr(); return;
        case kind::stmt_waittillmatch: as_waittillmatch.~unique_ptr(); return;
        case kind::stmt_waittillframeend: as_waittillframeend.~unique_ptr(); return;
        case kind::stmt_if: as_if.~unique_ptr(); return;
        case kind::stmt_ifelse: as_ifelse.~unique_ptr(); return;
        case kind::stmt_while: as_while.~unique_ptr(); return;
        case kind::stmt_dowhile: as_dowhile.~unique_ptr(); return;
        case kind::stmt_for: as_for.~unique_ptr(); return;
        case kind::stmt_foreach: as_foreach.~unique_ptr(); return;
        case kind::stmt_switch: as_switch.~unique_ptr(); return;
        case kind::stmt_case: as_case.~unique_ptr(); return;
        case kind::stmt_default: as_default.~unique_ptr(); return;
        case kind::stmt_break: as_break.~unique_ptr(); return;
        case kind::stmt_continue: as_continue.~unique_ptr(); return;
        case kind::stmt_return: as_return.~unique_ptr(); return;
        case kind::stmt_breakpoint: as_breakpoint.~unique_ptr(); return;
        case kind::stmt_prof_begin: as_prof_begin.~unique_ptr(); return;
        case kind::stmt_prof_end: as_prof_end.~unique_ptr(); return;
        case kind::asm_loc: as_loc.~unique_ptr(); return;
        case kind::asm_jump: as_jump.~unique_ptr(); return;
        case kind::asm_jump_back: as_jump_back.~unique_ptr(); return;
        case kind::asm_jump_cond: as_cond.~unique_ptr(); return;
        case kind::asm_jump_true_expr: as_jump_true_expr.~unique_ptr(); return;
        case kind::asm_jump_false_expr: as_jump_false_expr.~unique_ptr(); return;
        case kind::asm_switch: as_asm_switch.~unique_ptr(); return;
        case kind::asm_endswitch: as_asm_endswitch.~unique_ptr(); return;
        case kind::asm_prescriptcall: as_asm_prescriptcall.~unique_ptr(); return;
        case kind::asm_voidcodepos: as_asm_voidcodepos.~unique_ptr(); return;
        case kind::asm_dev: as_asm_dev.~unique_ptr(); return;
        default: return;
    }
}

bool operator==(const stmt& lhs, kind rhs)
{
    return *lhs.as_node == rhs;
}

auto stmt::loc() const -> location
{
    return as_node->loc();
}

auto stmt::kind() const -> ast::kind
{
    return as_node->kind();
}

auto stmt::print() const -> std::string
{
    return as_node->print();
}

decl::decl() : as_node(nullptr) {}

decl::decl(std::unique_ptr<node> value) : as_node(std::move(value)) {}

decl::decl(decl&& value)
{
    new(&as_node) std::unique_ptr<node>(std::move(value.as_node));
}

decl& decl::operator=(decl&& value)
{
    new(&as_node) std::unique_ptr<node>(std::move(value.as_node));
    return *(decl*)&as_node;
}

decl::~decl()
{
    if (as_node == nullptr) return;

    switch (as_node->kind())
    {
        case kind::null: as_node.~unique_ptr(); return;
        case kind::decl_dev_begin: as_dev_begin.~unique_ptr(); return;
        case kind::decl_dev_end: as_dev_end.~unique_ptr(); return;
        case kind::decl_thread: as_thread.~unique_ptr(); return;
        case kind::decl_constant: as_constant.~unique_ptr(); return;
        case kind::decl_usingtree: as_usingtree.~unique_ptr(); return;
        default: return;
    }
}

bool operator==(const decl& lhs, kind rhs)
{
    return *lhs.as_node == rhs;
}

auto decl::loc() const -> location
{
    return as_node->loc();
}

auto decl::kind() const -> ast::kind
{
    return as_node->kind();
}

auto decl::print() const -> std::string
{
    return as_node->print();
}

} // namespace xsk::arc::ast
