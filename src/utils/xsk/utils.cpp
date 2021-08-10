// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"

namespace xsk::gsc
{

std::uint32_t node::indent_;

expr_call_type_ptr::~expr_call_type_ptr()
{
    if (as_node == nullptr) return;

    switch (as_node->type)
    {
        case node_t::null: as_node.~node_ptr(); break;
        case node_t::expr_call_pointer: as_pointer.~expr_call_pointer_ptr(); break;
        case node_t::expr_call_function: as_func.~expr_call_function_ptr(); break;
        default: break;
    }
}

expr_ptr::~expr_ptr()
{
    if (as_node == nullptr) return;

    switch (as_node->type)
    {
        case node_t::null: as_node.~node_ptr(); break;
        case node_t::data_true: as_true.~true_ptr(); break;
        case node_t::data_false: as_false.~false_ptr(); break;
        case node_t::data_integer: as_integer.~integer_ptr(); break;
        case node_t::data_float: as_float.~float_ptr(); break;
        case node_t::data_vector: as_vector.~vector_ptr(); break;
        case node_t::data_string: as_string.~string_ptr(); break;
        case node_t::data_istring: as_istring.~istring_ptr(); break;
        case node_t::data_file: as_file.~file_ptr(); break;
        case node_t::data_name: as_name.~name_ptr(); break;
        case node_t::data_animtree: as_animtree.~animtree_ptr(); break;
        case node_t::data_animation: as_animation.~animation_ptr(); break;
        case node_t::data_level: as_level.~level_ptr(); break;
        case node_t::data_anim: as_anim.~anim_ptr(); break;
        case node_t::data_self: as_self.~self_ptr(); break;
        case node_t::data_game: as_game.~game_ptr(); break;
        case node_t::data_undefined: as_undefined.~undefined_ptr(); break;
        case node_t::data_empty_array: as_empty_array.~empty_array_ptr(); break;
        case node_t::data_thisthread: as_thisthread.~thisthread_ptr(); break;
        case node_t::expr_paren: as_paren.~expr_paren_ptr(); break;
        case node_t::expr_size: as_size.~expr_size_ptr(); break;
        case node_t::expr_field: as_field.~expr_field_ptr(); break;
        case node_t::expr_array: as_array.~expr_array_ptr(); break;
        case node_t::expr_add_array: as_add_array.~expr_add_array_ptr(); break;
        case node_t::expr_function: as_function.~expr_function_ptr(); break;
        case node_t::expr_arguments: as_arguments.~expr_arguments_ptr(); break;
        case node_t::expr_call_pointer: as_call_pointer.~expr_call_pointer_ptr(); break;
        case node_t::expr_call_function: as_call_function.~expr_call_function_ptr(); break;
        case node_t::expr_call: as_call.~expr_call_ptr(); break;
        case node_t::expr_complement: as_complement.~expr_complement_ptr(); break;
        case node_t::expr_not: as_not.~expr_not_ptr(); break;
        case node_t::expr_add: as_add.~expr_add_ptr(); break;
        case node_t::expr_sub: as_sub.~expr_sub_ptr(); break;
        case node_t::expr_mult: as_mult.~expr_mult_ptr(); break;
        case node_t::expr_div: as_div.~expr_div_ptr(); break;
        case node_t::expr_mod: as_mod.~expr_mod_ptr(); break;
        case node_t::expr_shift_left: as_shift_left.~expr_shift_left_ptr(); break;
        case node_t::expr_shift_right: as_shift_right.~expr_shift_right_ptr(); break;
        case node_t::expr_bitwise_or: as_bitwise_or.~expr_bitwise_or_ptr(); break;
        case node_t::expr_bitwise_and: as_bitwise_and.~expr_bitwise_and_ptr(); break;
        case node_t::expr_bitwise_exor: as_bitwise_exor.~expr_bitwise_exor_ptr(); break;
        case node_t::expr_equality: as_equality.~expr_equality_ptr(); break;
        case node_t::expr_inequality: as_inequality.~expr_inequality_ptr(); break;
        case node_t::expr_less_equal: as_less_equal.~expr_less_equal_ptr(); break;
        case node_t::expr_greater_equal: as_greater_equal.~expr_greater_equal_ptr(); break;
        case node_t::expr_less: as_less.~expr_less_ptr(); break;
        case node_t::expr_greater: as_greater.~expr_greater_ptr(); break;
        case node_t::expr_or: as_or.~expr_or_ptr(); break;
        case node_t::expr_and: as_and.~expr_and_ptr(); break;
        case node_t::expr_ternary: as_ternary.~expr_ternary_ptr(); break;
        case node_t::expr_assign_equal: as_assign_equal.~expr_assign_equal_ptr(); break;
        case node_t::expr_assign_add: as_assign_add.~expr_assign_add_ptr(); break;
        case node_t::expr_assign_sub: as_assign_sub.~expr_assign_sub_ptr(); break;
        case node_t::expr_assign_mult: as_assign_mult.~expr_assign_mult_ptr(); break;
        case node_t::expr_assign_div: as_assign_div.~expr_assign_div_ptr(); break;
        case node_t::expr_assign_mod: as_assign_mod.~expr_assign_mod_ptr(); break;
        case node_t::expr_assign_shift_left: as_assign_shift_left.~expr_assign_shift_left_ptr(); break;
        case node_t::expr_assign_shift_right: as_assign_shift_right.~expr_assign_shift_right_ptr(); break;
        case node_t::expr_assign_bitwise_or: as_assign_bw_or.~expr_assign_bitwise_or_ptr(); break;
        case node_t::expr_assign_bitwise_and: as_assign_bw_and.~expr_assign_bitwise_and_ptr(); break;
        case node_t::expr_assign_bitwise_exor: as_assign_bw_xor.~expr_assign_bitwise_exor_ptr(); break;
        case node_t::expr_increment: as_increment.~expr_increment_ptr(); break;
        case node_t::expr_decrement: as_decrement.~expr_decrement_ptr(); break;
        default: break;
    }
}

stmt_ptr::~stmt_ptr()
{
    if (as_node == nullptr) return;

    switch (as_node->type)
    {
        case node_t::null: as_node.~node_ptr(); break;
        case node_t::stmt_list: as_list.~stmt_list_ptr(); break;
        case node_t::stmt_call: as_call.~stmt_call_ptr(); break;
        case node_t::stmt_assign: as_assign.~stmt_assign_ptr(); break;
        case node_t::stmt_endon: as_endon.~stmt_endon_ptr(); break;
        case node_t::stmt_notify: as_notify.~stmt_notify_ptr(); break;
        case node_t::stmt_wait: as_wait.~stmt_wait_ptr(); break;
        case node_t::stmt_waittill: as_waittill.~stmt_waittill_ptr(); break;
        case node_t::stmt_waittillmatch: as_waittillmatch.~stmt_waittillmatch_ptr(); break;
        case node_t::stmt_waittillframeend: as_waittillframeend.~stmt_waittillframeend_ptr(); break;
        case node_t::stmt_waitframe: as_waitframe.~stmt_waitframe_ptr(); break;
        case node_t::stmt_if: as_if.~stmt_if_ptr(); break;
        case node_t::stmt_ifelse: as_ifelse.~stmt_ifelse_ptr(); break;
        case node_t::stmt_while: as_while.~stmt_while_ptr(); break;
        case node_t::stmt_for: as_for.~stmt_for_ptr(); break;
        case node_t::stmt_foreach: as_foreach.~stmt_foreach_ptr(); break;
        case node_t::stmt_switch: as_switch.~stmt_switch_ptr(); break;
        case node_t::stmt_case: as_case.~stmt_case_ptr(); break;
        case node_t::stmt_default: as_default.~stmt_default_ptr(); break;
        case node_t::stmt_break: as_break.~stmt_break_ptr(); break;
        case node_t::stmt_continue: as_continue.~stmt_continue_ptr(); break;
        case node_t::stmt_return: as_return.~stmt_return_ptr(); break;
        case node_t::stmt_breakpoint: as_breakpoint.~stmt_breakpoint_ptr(); break;
        case node_t::stmt_prof_begin: as_prof_begin.~stmt_prof_begin_ptr(); break;
        case node_t::stmt_prof_end: as_prof_end.~stmt_prof_end_ptr(); break;
        default: break;
    }
}

define_ptr::~define_ptr()
{
    if (as_node == nullptr) return;

    switch(as_node->type)
    {
        case node_t::null: as_node.~node_ptr(); break;
        case node_t::thread: as_thread.~thread_ptr(); break;
        case node_t::constant: as_constant.~constant_ptr(); break;
        case node_t::usingtree: as_usingtree.~usingtree_ptr(); break;
        default: break;
    }
}

bool expr_ptr::operator==(const expr_ptr& rhs) const
{
    if(as_node->type != rhs.as_node->type) return false;

    switch(as_node->type)
    {
        case node_t::data_true: return *as_true == *rhs.as_true;
        case node_t::data_false: return *as_false == *rhs.as_false;
        case node_t::data_integer: return *as_integer == *rhs.as_integer;
        case node_t::data_float: return *as_float == *rhs.as_float;
        case node_t::data_vector: return *as_vector == *rhs.as_vector;
        case node_t::data_string: return *as_string == *rhs.as_string;
        case node_t::data_istring: return *as_istring == *rhs.as_istring;
        case node_t::data_file: return *as_file == *rhs.as_file;
        case node_t::data_name: return *as_name == *rhs.as_name;
        case node_t::data_animtree: return *as_animtree == *rhs.as_animtree;
        case node_t::data_animation: return *as_animation == *rhs.as_animation;
        case node_t::data_level: return *as_level == *rhs.as_level;
        case node_t::data_anim: return *as_anim == *rhs.as_anim;
        case node_t::data_self: return *as_self == *rhs.as_self;
        case node_t::data_game: return *as_game == *rhs.as_game;
        case node_t::data_undefined: return *as_undefined == *rhs.as_undefined;
        case node_t::data_empty_array: return *as_empty_array == *rhs.as_empty_array;
        case node_t::data_thisthread: return *as_thisthread == *rhs.as_thisthread;
        case node_t::expr_paren: return *as_paren == *rhs.as_paren;
        case node_t::expr_size: return *as_size == *rhs.as_size;
        case node_t::expr_field: return *as_field == *rhs.as_field;
        case node_t::expr_array: return *as_array == *rhs.as_array;
        default: return false;
    }
}

} // namespace xsk::gsc
