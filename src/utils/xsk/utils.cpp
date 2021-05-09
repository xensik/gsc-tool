// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"

namespace xsk
{

std::uint32_t gsc::node::indent_;

bool gsc::expr_ptr::operator==(const gsc::expr_ptr& rhs) const
{
    if(as_node->type != rhs.as_node->type)
        return false;

    switch(as_node->type)
    {
        case gsc::node_t::data_true:
            return *as_true == *rhs.as_true;
        case gsc::node_t::data_false:
            return *as_false == *rhs.as_false;
        case gsc::node_t::data_integer:
            return *as_integer == *rhs.as_integer;
        case gsc::node_t::data_float:
            return *as_float == *rhs.as_float;
        case gsc::node_t::data_vector:
            return *as_vector == *rhs.as_vector;
        case gsc::node_t::data_string:
            return *as_string == *rhs.as_string;
        case gsc::node_t::data_istring:
            return *as_istring == *rhs.as_istring;
        case gsc::node_t::data_file:
            return *as_file == *rhs.as_file;
        case gsc::node_t::data_name:
            return *as_name == *rhs.as_name;
        case gsc::node_t::data_animtree:
            return *as_animtree == *rhs.as_animtree;
        case gsc::node_t::data_animation:
            return *as_animation == *rhs.as_animation;
        case gsc::node_t::data_level:
            return *as_level == *rhs.as_level;
        case gsc::node_t::data_anim:
            return *as_anim == *rhs.as_anim;
        case gsc::node_t::data_self:
            return *as_self == *rhs.as_self;
        case gsc::node_t::data_game:
            return *as_game == *rhs.as_game;
        case gsc::node_t::data_undefined:
            return *as_undefined == *rhs.as_undefined;
        case gsc::node_t::data_empty_array:
            return *as_empty_array == *rhs.as_empty_array;
        case gsc::node_t::data_thisthread:
            return *as_thisthread == *rhs.as_thisthread;
        case gsc::node_t::expr_paren:
            return *as_paren == *rhs.as_paren;
        case gsc::node_t::expr_size:
            return *as_size == *rhs.as_size;
        case gsc::node_t::expr_field:
            return *as_field == *rhs.as_field;
        case gsc::node_t::expr_array:
            return *as_array == *rhs.as_array;
        default:
            return false;
    }
}

} // namespace xsk
