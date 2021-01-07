// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_NODETREE_HPP_
#define _GSC_NODETREE_HPP_

namespace gsc
{

enum class node_type
{
    null,
    level,
    anim,
    self,
    game,
    size,
    undefined,
    empty_array,
    filepath,
    identifier,
    animtree,
    animref,
    data_true,
    data_false,
    data_string,
    data_localized_string,
    data_integer,
    data_float,
    data_vector,
    expr_vector,
    expr_add_array,
    expr_size,
    expr_field,
    expr_array,
    expr_function_ref,
    expr_arguments,
    expr_call_pointer,
    expr_call_function,
    expr_call,
    expr_complement,
    expr_not,
    expr_add,
    expr_sub,
    expr_mult,
    expr_div,
    expr_mod,
    expr_shift_left,
    expr_shift_right,
    expr_bitwise_or,
    expr_bitwise_and,
    expr_bitwise_exor,
    expr_equality,
    expr_inequality,
    expr_less_equal,
    expr_greater_equal,
    expr_less,
    expr_greater,
    expr_or,
    expr_and,
    expr_ternary,
    expr_assign_equal,
    expr_assign_add,
    expr_assign_sub,
    expr_assign_mult,
    expr_assign_div,
    expr_assign_mod,
    expr_assign_shift_left,
    expr_assign_shift_right,
    expr_assign_bitwise_or,
    expr_assign_bitwise_and,
    expr_assign_bitwise_exor,
    expr_increment,
    expr_decrement,
    stmt_call,
    stmt_assign,
    stmt_endon,
    stmt_notify,
    stmt_wait,
    stmt_waittill,
    stmt_waittillmatch,
    stmt_waittillframeend,
    stmt_waitframe,
    stmt_if,
    stmt_ifelse,
    stmt_while,
    stmt_for,
    stmt_foreach,
    stmt_switch,
    stmt_case,
    stmt_default,
    stmt_break,
    stmt_continue,
    stmt_return,
    block,
    parameters,
    thread,
    constant,
    using_animtree,
    include,
    script,
    // DECOMPILER
    asm_loc,
    asm_jump,
    asm_jump_back,
    asm_jump_cond,
    asm_jump_true_expr,
    asm_jump_false_expr,
    asm_switch,
    asm_endswitch,
    asm_prescriptcall,
    asm_voidcodepos,
};

struct node;
struct node_level;
struct node_anim;
struct node_self;
struct node_game;
struct node_size;
struct node_undefined;
struct node_empty_array;
struct node_filepath;
struct node_identifier;
struct node_animtree;
struct node_animref;
struct node_true;
struct node_false;
struct node_string;
struct node_localized_string;
struct node_integer;
struct node_float;
struct node_vector;
struct node_expr_vector;
struct node_expr_add_array;
struct node_expr_size;
struct node_expr_field;
struct node_expr_array;
struct node_expr_function_ref;
struct node_expr_arguments;
struct node_expr_call_pointer;
struct node_expr_call_function;
struct node_expr_call;
struct node_expr_complement;
struct node_expr_not;
struct node_expr_binary;
struct node_expr_add;
struct node_expr_sub;
struct node_expr_mult;
struct node_expr_div;
struct node_expr_mod;
struct node_expr_shift_left;
struct node_expr_shift_right;
struct node_expr_bitwise_or;
struct node_expr_bitwise_and;
struct node_expr_bitwise_exor;
struct node_expr_equality;
struct node_expr_inequality;
struct node_expr_less_equal;
struct node_expr_greater_equal;
struct node_expr_less;
struct node_expr_greater;
struct node_expr_or;
struct node_expr_and;
struct node_expr_ternary;
struct node_expr_assign;
struct node_expr_assign_equal;
struct node_expr_assign_add;
struct node_expr_assign_sub;
struct node_expr_assign_mult;
struct node_expr_assign_div;
struct node_expr_assign_mod;
struct node_expr_assign_shift_left;
struct node_expr_assign_shift_right;
struct node_expr_assign_bitwise_or;
struct node_expr_assign_bitwise_and;
struct node_expr_assign_bitwise_exor;
struct node_expr_increment;
struct node_expr_decrement;
struct node_stmt_call;
struct node_stmt_assign;
struct node_stmt_endon;
struct node_stmt_notify;
struct node_stmt_wait;
struct node_stmt_waittill;
struct node_stmt_waittillmatch;
struct node_stmt_waittillframeend;
struct node_stmt_waitframe;
struct node_stmt_if;
struct node_stmt_ifelse;
struct node_stmt_while;
struct node_stmt_for;
struct node_stmt_foreach;
struct node_stmt_switch;
struct node_stmt_case;
struct node_stmt_default;
struct node_stmt_break;
struct node_stmt_continue;
struct node_stmt_return;
struct node_block;
struct node_parameters;
struct node_thread;
struct node_constant;
struct node_animtree;
struct node_using_animtree;
struct node_include;
struct node_script;
struct node_asm_loc;
struct node_asm_jump;
struct node_asm_jump_back;
struct node_asm_jump_cond;
struct node_asm_jump_false_expr;
struct node_asm_jump_true_expr;
struct node_asm_switch;
struct node_asm_endswitch;

using node_ptr = std::unique_ptr<node>;
using level_ptr = std::unique_ptr<node_level>;
using anim_ptr = std::unique_ptr<node_anim>;
using self_ptr = std::unique_ptr<node_self>;
using game_ptr = std::unique_ptr<node_game>;
using size_ptr = std::unique_ptr<node_size>;
using undefined_ptr = std::unique_ptr<node_undefined>;
using empty_array_ptr = std::unique_ptr<node_empty_array>;
using filepath_ptr = std::unique_ptr<node_filepath>;
using identifier_ptr = std::unique_ptr<node_identifier>;
using animtree_ptr = std::unique_ptr<node_animtree>;
using animref_ptr = std::unique_ptr<node_animref>;
using true_ptr = std::unique_ptr<node_true>;
using false_ptr = std::unique_ptr<node_false>;
using string_ptr = std::unique_ptr<node_string>;
using localized_string_ptr = std::unique_ptr<node_localized_string>;
using integer_ptr = std::unique_ptr<node_integer>;
using float_ptr = std::unique_ptr<node_float>;
using vector_ptr = std::unique_ptr<node_vector>;
using expr_vector_ptr = std::unique_ptr<node_expr_vector>;
using expr_add_array_ptr = std::unique_ptr<node_expr_add_array>;
using expr_size_ptr = std::unique_ptr<node_expr_size>;
using expr_field_ptr = std::unique_ptr<node_expr_field>;
using expr_array_ptr = std::unique_ptr<node_expr_array>;
using expr_function_ref_ptr = std::unique_ptr<node_expr_function_ref>;
using expr_arguments_ptr = std::unique_ptr<node_expr_arguments>;
using expr_call_pointer_ptr = std::unique_ptr<node_expr_call_pointer>;
using expr_call_function_ptr = std::unique_ptr<node_expr_call_function>;
using expr_call_ptr = std::unique_ptr<node_expr_call>;
using expr_complement_ptr = std::unique_ptr<node_expr_complement>;
using expr_not_ptr = std::unique_ptr<node_expr_not>;
using expr_binary_ptr = std::unique_ptr<node_expr_binary>;
using expr_add_ptr = std::unique_ptr<node_expr_add>;
using expr_sub_ptr = std::unique_ptr<node_expr_sub>;
using expr_mult_ptr = std::unique_ptr<node_expr_mult>;
using expr_div_ptr = std::unique_ptr<node_expr_div>;
using expr_mod_ptr = std::unique_ptr<node_expr_mod>;
using expr_shift_left_ptr = std::unique_ptr<node_expr_shift_left>;
using expr_shift_right_ptr = std::unique_ptr<node_expr_shift_right>;
using expr_bitwise_or_ptr = std::unique_ptr<node_expr_bitwise_or>;
using expr_bitwise_and_ptr = std::unique_ptr<node_expr_bitwise_and>;
using expr_bitwise_exor_ptr = std::unique_ptr<node_expr_bitwise_exor>;
using expr_equality_ptr = std::unique_ptr<node_expr_equality>;
using expr_inequality_ptr = std::unique_ptr<node_expr_inequality>;
using expr_less_equal_ptr = std::unique_ptr<node_expr_less_equal>;
using expr_greater_equal_ptr = std::unique_ptr<node_expr_greater_equal>;
using expr_less_ptr = std::unique_ptr<node_expr_less>;
using expr_greater_ptr = std::unique_ptr<node_expr_greater>;
using expr_or_ptr = std::unique_ptr<node_expr_or>;
using expr_and_ptr = std::unique_ptr<node_expr_and>;
using expr_ternary_ptr = std::unique_ptr<node_expr_ternary>;
using expr_assign_ptr = std::unique_ptr<node_expr_assign>;
using expr_assign_equal_ptr = std::unique_ptr<node_expr_assign_equal>;
using expr_assign_add_ptr = std::unique_ptr<node_expr_assign_add>;
using expr_assign_sub_ptr = std::unique_ptr<node_expr_assign_sub>;
using expr_assign_mult_ptr = std::unique_ptr<node_expr_assign_mult>;
using expr_assign_div_ptr = std::unique_ptr<node_expr_assign_div>;
using expr_assign_mod_ptr = std::unique_ptr<node_expr_assign_mod>;
using expr_assign_shift_left_ptr = std::unique_ptr<node_expr_assign_shift_left>;
using expr_assign_shift_right_ptr = std::unique_ptr<node_expr_assign_shift_right>;
using expr_assign_bitwise_or_ptr = std::unique_ptr<node_expr_assign_bitwise_or>;
using expr_assign_bitwise_and_ptr = std::unique_ptr<node_expr_assign_bitwise_and>;
using expr_assign_bitwise_exor_ptr = std::unique_ptr<node_expr_assign_bitwise_exor>;
using expr_increment_ptr = std::unique_ptr<node_expr_increment>;
using expr_decrement_ptr = std::unique_ptr<node_expr_decrement>;
using stmt_call_ptr = std::unique_ptr<node_stmt_call>;
using stmt_assign_ptr = std::unique_ptr<node_stmt_assign>;
using stmt_endon_ptr = std::unique_ptr<node_stmt_endon>;
using stmt_notify_ptr = std::unique_ptr<node_stmt_notify>;
using stmt_wait_ptr = std::unique_ptr<node_stmt_wait>;
using stmt_waittill_ptr = std::unique_ptr<node_stmt_waittill>;
using stmt_waittillmatch_ptr = std::unique_ptr<node_stmt_waittillmatch>;
using stmt_waitframe_ptr = std::unique_ptr<node_stmt_waitframe>;
using stmt_waittillframeend_ptr = std::unique_ptr<node_stmt_waittillframeend>;
using stmt_if_ptr = std::unique_ptr<node_stmt_if>;
using stmt_ifelse_ptr = std::unique_ptr<node_stmt_ifelse>;
using stmt_while_ptr = std::unique_ptr<node_stmt_while>;
using stmt_for_ptr = std::unique_ptr<node_stmt_for>;
using stmt_foreach_ptr = std::unique_ptr<node_stmt_foreach>;
using stmt_switch_ptr = std::unique_ptr<node_stmt_switch>;
using stmt_case_ptr = std::unique_ptr<node_stmt_case>;
using stmt_default_ptr = std::unique_ptr<node_stmt_default>;
using stmt_break_ptr = std::unique_ptr<node_stmt_break>;
using stmt_continue_ptr = std::unique_ptr<node_stmt_continue>;
using stmt_return_ptr = std::unique_ptr<node_stmt_return>;
using block_ptr = std::unique_ptr<node_block>;
using parameters_ptr = std::unique_ptr<node_parameters>;
using thread_ptr = std::unique_ptr<node_thread>;
using constant_ptr = std::unique_ptr<node_constant>;
using animtree_ptr = std::unique_ptr<node_animtree>;
using using_animtree_ptr = std::unique_ptr<node_using_animtree>;
using include_ptr = std::unique_ptr<node_include>;
using script_ptr = std::unique_ptr<node_script>;
using asm_loc_ptr = std::unique_ptr<node_asm_loc>;
using asm_jump_ptr = std::unique_ptr<node_asm_jump>;
using asm_jump_back_ptr = std::unique_ptr<node_asm_jump_back>;
using asm_jump_cond_ptr = std::unique_ptr<node_asm_jump_cond>;
using asm_jump_false_expr_ptr = std::unique_ptr<node_asm_jump_false_expr>;
using asm_jump_true_expr_ptr = std::unique_ptr<node_asm_jump_true_expr>;
using asm_switch_ptr = std::unique_ptr<node_asm_switch>;
using asm_endswitch_ptr = std::unique_ptr<node_asm_endswitch>;

union expr_call_type_ptr
{
    node_ptr as_node;
    expr_call_pointer_ptr as_pointer;
    expr_call_function_ptr as_func;

    expr_call_type_ptr() {}
    expr_call_type_ptr(node_ptr val): as_node(std::move(val)) {}
    expr_call_type_ptr(expr_call_type_ptr && val) { new(&as_node) node_ptr(std::move(val.as_node)); }
    ~expr_call_type_ptr(){}
};

union expr_ptr
{
    node_ptr as_node;
    level_ptr as_level;
    anim_ptr as_anim;
    self_ptr as_self;
    game_ptr as_game;
    size_ptr as_size;
    undefined_ptr as_undefined;
    empty_array_ptr as_empty_array;
    true_ptr as_true;
    false_ptr as_false;
    filepath_ptr as_filepath;
    identifier_ptr as_identifier;
    animtree_ptr as_animtree;
    animref_ptr as_animref;
    string_ptr as_string;
    localized_string_ptr as_localized_string;
    integer_ptr as_integer;
    float_ptr as_float;
    vector_ptr as_vector;
    expr_vector_ptr as_vector_expr;
    expr_add_array_ptr as_add_array;
    expr_field_ptr as_field;
    expr_array_ptr as_array;
    expr_size_ptr as_size_expr;
    expr_function_ref_ptr as_function_ref;
    expr_arguments_ptr as_arguments;
    expr_call_pointer_ptr as_call_pointer;
    expr_call_function_ptr as_call_function;
    expr_call_ptr as_call;
    expr_complement_ptr as_complement;
    expr_not_ptr as_not;
    expr_add_ptr as_add;
    expr_sub_ptr as_sub;
    expr_mult_ptr as_mult;
    expr_div_ptr as_div;
    expr_mod_ptr as_mod;
    expr_shift_left_ptr as_shift_left;
    expr_shift_right_ptr as_shift_right;
    expr_bitwise_or_ptr as_bitwise_or;
    expr_bitwise_and_ptr as_bitwise_and;
    expr_bitwise_exor_ptr as_bitwise_exor;
    expr_equality_ptr as_equality;
    expr_inequality_ptr as_inequality;
    expr_less_equal_ptr as_less_equal;
    expr_greater_equal_ptr as_greater_equal;
    expr_less_ptr as_less;
    expr_greater_ptr as_greater;
    expr_or_ptr as_or;
    expr_and_ptr as_and;
    expr_binary_ptr as_binary;
    expr_ternary_ptr as_ternary;
    expr_assign_ptr as_assign;
    expr_assign_equal_ptr as_assign_equal;
    expr_assign_add_ptr as_assign_add;
    expr_assign_sub_ptr as_assign_sub;
    expr_assign_mult_ptr as_assign_mult;
    expr_assign_div_ptr as_assign_div;
    expr_assign_mod_ptr as_assign_mod;
    expr_assign_shift_left_ptr as_assign_shift_left;
    expr_assign_shift_right_ptr as_assign_shift_right;
    expr_assign_bitwise_or_ptr as_assign_bw_or;
    expr_assign_bitwise_and_ptr as_assign_bw_and;
    expr_assign_bitwise_exor_ptr as_assign_bw_xor;
    expr_increment_ptr as_increment;
    expr_decrement_ptr as_decrement;

    expr_ptr() {}
    expr_ptr(node_ptr val): as_node(std::move(val)) {}
    expr_ptr (expr_ptr && val)
    {
        new(&as_node) node_ptr(std::move(val.as_node));
    }

    expr_ptr& operator=(expr_ptr && val)
    {
        new(&as_node) node_ptr(std::move(val.as_node));
        return *(expr_ptr*)&as_node;
    }
    ~expr_ptr(){}
};

union stmt_ptr
{
    node_ptr as_node;
    stmt_call_ptr as_call;
    stmt_assign_ptr as_assign;
    stmt_endon_ptr as_endon;
    stmt_notify_ptr as_notify;
    stmt_wait_ptr as_wait;
    stmt_waittill_ptr as_waittill;
    stmt_waittillmatch_ptr as_waittillmatch;
    stmt_waittillframeend_ptr as_waittillframeend;
    stmt_waitframe_ptr as_waitframe;
    stmt_if_ptr as_if;
    stmt_ifelse_ptr as_ifelse;
    stmt_while_ptr as_while;
    stmt_for_ptr as_for;
    stmt_foreach_ptr as_foreach;
    stmt_switch_ptr as_switch;
    stmt_case_ptr as_case;
    stmt_default_ptr as_default;
    stmt_break_ptr as_break;
    stmt_continue_ptr as_continue;
    stmt_return_ptr as_return;

    asm_loc_ptr as_loc;
    asm_jump_cond_ptr as_cond;
    asm_jump_ptr as_jump;
    asm_jump_back_ptr as_jump_back;
    asm_switch_ptr as_asm_switch;
    asm_endswitch_ptr as_asm_endswitch;

    stmt_ptr() {}
    stmt_ptr(node_ptr val): as_node(std::move(val)) {}
    stmt_ptr(const stmt_ptr &) = delete;
    stmt_ptr & operator=(const stmt_ptr &) = delete;

    stmt_ptr (stmt_ptr && val) { new(&as_node) node_ptr(std::move(val.as_node)); }
    stmt_ptr& operator=(stmt_ptr &&val )
    {
        new(&as_node) node_ptr(std::move(val.as_node));
        return *(stmt_ptr*)&as_node;
    }
    ~stmt_ptr(){}
};

union definition_ptr
{
    node_ptr as_node;
    using_animtree_ptr as_using_animtree;
    constant_ptr as_constant;
    thread_ptr as_thread;

    definition_ptr() {}
    definition_ptr(node_ptr val): as_node(std::move(val)) {}
    definition_ptr(definition_ptr && val) { new(&as_node) node_ptr(std::move(val.as_node)); }
    ~definition_ptr(){}
};

struct node
{
    node_type type;
    std::string location;

    node() : type(node_type::null) {}
    node(node_type type) : type(type) {}
    node(node_type type, const std::string& location) : type(type), location(location) {}
    
    virtual ~node() = default;
    virtual auto print() -> std::string { return ""; };
     
protected:
    static std::uint32_t indent;
    static void reset_indentation() { indent = 0; }
    static std::string indented(std::uint32_t indent)
    {
        static char buff[100];
        snprintf(buff, sizeof(buff), "%*s", indent, "");
        return std::string(buff);
    }
};

struct node_level : public node
{
    node_level() : node(node_type::level) {}
    node_level(const std::string& location) : node(node_type::level, location) {}

    auto print() -> std::string override
    {
        return "level";
    }
};

struct node_anim : public node
{
    node_anim() : node(node_type::anim) {}
    node_anim(const std::string& location) : node(node_type::anim, location) {}

    auto print() -> std::string override
    {
        return "anim";
    }
};

struct node_self : public node
{
    node_self() : node(node_type::self) {}
    node_self(const std::string& location) : node(node_type::self, location) {}

    auto print() -> std::string override
    {
        return "self";
    }
};

struct node_game : public node
{
    node_game() : node(node_type::game) {}
    node_game(const std::string& location) : node(node_type::game, location) {}

    auto print() -> std::string override
    {
        return "game";
    }
};

struct node_size : public node
{
    node_size() : node(node_type::size) {}
    node_size(const std::string& location) : node(node_type::size, location) {}

    auto print() -> std::string override
    {
        return "size";
    }
};

struct node_undefined : public node
{
    node_undefined() : node(node_type::undefined) {}
    node_undefined(const std::string& location) : node(node_type::undefined, location) {}

    auto print() -> std::string override
    {
        return "undefined";
    }
};

struct node_empty_array : public node
{
    node_empty_array() : node(node_type::empty_array) {}
    node_empty_array(const std::string& location) : node(node_type::empty_array, location) {}

    auto print() -> std::string override
    {
        return "[]";
    }
};

struct node_filepath : public node
{
    std::string value;

    node_filepath(const std::string& value)
        : node(node_type::filepath), value(value) {}

    node_filepath(const std::string& location, const std::string& value)
        : node(node_type::filepath, location), value(value) {}

    auto print() -> std::string override
    {
        return value;
    }
};

struct node_identifier : public node
{
    std::string value;

    node_identifier(const std::string& value)
        : node(node_type::identifier), value(value) {}

    node_identifier(const std::string& location, const std::string& value)
        : node(node_type::identifier, location), value(value) {}

    auto print() -> std::string override
    {
        return value;
    }
};

struct node_animtree : public node
{
    node_animtree() : node(node_type::animref) {}

    node_animtree(const std::string& location) : node(node_type::animtree, location) {}

    auto print() -> std::string override
    {
        return "#animtree"s;
    }
};

struct node_animref : public node
{
    std::string value;

    node_animref(const std::string& value)
        : node(node_type::animref), value(value) {}

    node_animref(const std::string& location, const std::string& value)
        : node(node_type::animref, location), value(value) {}

    auto print() -> std::string override
    {
        return "%"s += value;
    }
};

struct node_true : public node
{
    node_true() : node(node_type::data_true) {}
    node_true(const std::string& location) : node(node_type::data_true, location) {}

    auto print() -> std::string override
    {
        return "true";
    }
};

struct node_false : public node
{
    node_false() : node(node_type::data_false) {}
    node_false(const std::string& location) : node(node_type::data_false, location) {}

    auto print() -> std::string override
    {
        return "false";
    }
};

struct node_string : public node
{
    std::string value;

    node_string(const std::string& value)
        : node(node_type::data_string), value(value) {}

    node_string(const std::string& location, const std::string& value)
        : node(node_type::data_string, location), value(value) {}

    auto print() -> std::string override
    {
        return value;
    }
};

struct node_localized_string : public node
{
    std::string value;

    node_localized_string(const std::string& value)
        : node(node_type::data_localized_string), value(std::move(value)) {}

    node_localized_string(const std::string& location, const std::string& value)
        : node(node_type::data_localized_string, location), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "&" + value;
    }
};

struct node_integer : public node
{
    std::string value;

    node_integer(const std::string& value)
        : node(node_type::data_integer), value(std::move(value)) {}

    node_integer(const std::string& location, const std::string& value)
        : node(node_type::data_integer, location), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return value;
    }
};

struct node_float : public node
{
    std::string value;

    node_float(const std::string& value)
        : node(node_type::data_float), value(std::move(value)) {}

    node_float(const std::string& location, const std::string& value)
        : node(node_type::data_float, location), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return value;
    }
};

struct node_vector : public node
{
    node_ptr x;
    node_ptr y;
    node_ptr z;

    node_vector(node_ptr x, node_ptr y, node_ptr z)
        : node(node_type::data_vector), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}

    node_vector(const std::string& location, node_ptr x, node_ptr y, node_ptr z)
        : node(node_type::data_vector, location), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}

    auto print() -> std::string override
    {
        return "( "s + x->print() + ", " + y->print() + ", "+ z->print() + " )";
    }
};

struct node_expr_vector : public node
{
    expr_ptr x;
    expr_ptr y;
    expr_ptr z;

    node_expr_vector(expr_ptr x, expr_ptr y, expr_ptr z)
        : node(node_type::expr_vector), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}

    node_expr_vector(const std::string& location, expr_ptr x, expr_ptr y, expr_ptr z)
        : node(node_type::expr_vector, location), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}

    auto print() -> std::string override
    {
        return "( "s + x.as_node->print() + ", " + y.as_node->print() + ", "+ z.as_node->print() + " )";
    }
};

struct node_expr_size : public node
{
    expr_ptr obj;

    node_expr_size(expr_ptr obj)
        : node(node_type::expr_size), obj(std::move(obj)) {}

    node_expr_size(const std::string& location, expr_ptr obj)
        : node(node_type::expr_size, location), obj(std::move(obj)) {}

    auto print() -> std::string override
    {
        return obj.as_node->print() + ".size";
    }
};

struct node_expr_field : public node
{
    expr_ptr obj;
    identifier_ptr field;

    node_expr_field(expr_ptr obj, identifier_ptr field)
        : node(node_type::expr_field), obj(std::move(obj)), field(std::move(field)) {}

    node_expr_field(const std::string& location, expr_ptr obj, identifier_ptr field)
        : node(node_type::expr_field, location), obj(std::move(obj)), field(std::move(field)) {}

    auto print() -> std::string override
    {
        return obj.as_node->print() + "." + field->print();
    }
};

struct node_expr_array : public node
{
    expr_ptr obj;
    expr_ptr key;

    node_expr_array(expr_ptr obj, expr_ptr key)
        : node(node_type::expr_array), obj(std::move(obj)), key(std::move(key)) {}

    node_expr_array(const std::string& location, expr_ptr obj, expr_ptr key)
        : node(node_type::expr_array, location), obj(std::move(obj)), key(std::move(key)) {}

    auto print() -> std::string override
    {
        return obj.as_node->print() + "[" + key.as_node->print() + "]";
    }
};

struct node_expr_function_ref : public node
{
    filepath_ptr file;
    identifier_ptr func;

    node_expr_function_ref(filepath_ptr file, identifier_ptr func)
        : node(node_type::expr_function_ref), file(std::move(file)), func(std::move(func)) {}

    node_expr_function_ref(const std::string& location, filepath_ptr file, identifier_ptr func)
        : node(node_type::expr_function_ref, location), file(std::move(file)), func(std::move(func)) {}

    auto print() -> std::string override
    {
        return file->print() + "::" + func->print();
    }
};

struct node_expr_arguments : public node
{
    std::vector<expr_ptr> list;

    node_expr_arguments()
        : node(node_type::expr_arguments) {}

    node_expr_arguments(const std::string& location)
        : node(node_type::expr_arguments, location) {}

    auto print() -> std::string override
    {
        std::string data;

        for (const auto& arg : list)
        {
            data += " " + arg.as_node->print();
            data += (&arg != &list.back()) ? "," : " ";
        }

        return data;
    }
};

struct node_expr_call_pointer : public node
{
    expr_ptr expr;
    expr_arguments_ptr args;
    bool builtin;

    node_expr_call_pointer(bool builtin, expr_ptr expr, expr_arguments_ptr args)
        : node(node_type::expr_call_pointer), builtin(builtin), expr(std::move(expr)), args(std::move(args)) {}

    node_expr_call_pointer(const std::string& location, bool builtin, expr_ptr expr, expr_arguments_ptr args)
        : node(node_type::expr_call_pointer, location), builtin(builtin), expr(std::move(expr)), args(std::move(args)) {}

    auto print() -> std::string override
    {
        if(builtin)
            return "call [[ "s + expr.as_node->print() + " ]](" + args->print() + ")";
        else
            return "[[ "s + expr.as_node->print() + " ]](" + args->print() + ")";
    }
};

struct node_expr_call_function : public node
{
    filepath_ptr file;
    identifier_ptr name;
    expr_arguments_ptr args;

    node_expr_call_function(filepath_ptr file, identifier_ptr name, expr_arguments_ptr args)
        : node(node_type::expr_call_function), file(std::move(file)), name(std::move(name)), args(std::move(args)) {}

    node_expr_call_function(const std::string& location, filepath_ptr file, identifier_ptr name, expr_arguments_ptr args)
        : node(node_type::expr_call_function, location), file(std::move(file)), name(std::move(name)), args(std::move(args)) {}

    auto print() -> std::string override
    {
        if(file->value == "")
        {
            return name->print() + "(" + args->print() + ")";
        }

        return file->print() + "::" + name->print() + "(" + args->print() + ")";
    }
};

struct node_expr_call : public node
{
    expr_ptr obj;
    expr_call_type_ptr func;
    bool thread;

    node_expr_call(bool thread, expr_ptr obj, expr_call_type_ptr func)
        : node(node_type::expr_call), thread(thread), obj(std::move(obj)), func(std::move(func)){}

    node_expr_call(const std::string& location, bool thread, expr_ptr obj, expr_call_type_ptr func)
        : node(node_type::expr_call, location), thread(thread), obj(std::move(obj)), func(std::move(func)){}

    auto print() -> std::string override
    {
        if(thread)
        {
            if(obj.as_node->type == node_type::null)
                return "thread " + func.as_node->print();

            return obj.as_node->print() + " thread " + func.as_node->print();
        }
        else if(obj.as_node->type == node_type::null)
            return func.as_node->print();
        else
            return obj.as_node->print() + " " + func.as_node->print();
    }
};

struct node_expr_add_array : public node
{
    expr_arguments_ptr args;

    node_expr_add_array(expr_arguments_ptr args)
        : node(node_type::expr_add_array), args(std::move(args)) {}

    node_expr_add_array(const std::string& location, expr_arguments_ptr args)
        : node(node_type::expr_add_array, location), args(std::move(args)) {}

    auto print() -> std::string override
    {
        return "[" + args->print() + "]";
    }
};

struct node_expr_complement : public node
{
    expr_ptr rvalue;

    node_expr_complement(expr_ptr rvalue)
        : node(node_type::expr_complement), rvalue(std::move(rvalue)) {}

    node_expr_complement(const std::string& location, expr_ptr rvalue)
        : node(node_type::expr_complement, location), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return "~" + rvalue.as_node->print();
    }
};

struct node_expr_not : public node
{
    expr_ptr rvalue;

    node_expr_not(expr_ptr rvalue)
        : node(node_type::expr_not), rvalue(std::move(rvalue)) {}

    node_expr_not(const std::string& location, expr_ptr rvalue)
        : node(node_type::expr_not, location), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return "!" + rvalue.as_node->print();
    }
};

struct node_expr_binary : public node
{
    expr_ptr lvalue;
    expr_ptr rvalue;

    node_expr_binary(node_type type, expr_ptr lvalue, expr_ptr rvalue)
        : node(type), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    node_expr_binary(node_type type, const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node(type, location), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
};

struct node_expr_add : public node_expr_binary
{
    node_expr_add(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_add, std::move(lvalue), std::move(rvalue)) {}

    node_expr_add(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_add, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " + " + rvalue.as_node->print();
    }
};

struct node_expr_sub : public node_expr_binary
{
    node_expr_sub(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_sub, std::move(lvalue), std::move(rvalue)) {}

    node_expr_sub(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_sub, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " - " + rvalue.as_node->print();
    }
};

struct node_expr_mult : public node_expr_binary
{
    node_expr_mult( expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_mult, std::move(lvalue), std::move(rvalue)) {}

    node_expr_mult(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_mult, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " * " + rvalue.as_node->print();
    }
};

struct node_expr_div : public node_expr_binary
{
    node_expr_div(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_div, std::move(lvalue), std::move(rvalue)) {}

    node_expr_div(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_div, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " / " + rvalue.as_node->print();
    }
};

struct node_expr_mod : public node_expr_binary
{
    node_expr_mod(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_mod, std::move(lvalue), std::move(rvalue)) {}

    node_expr_mod(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_mod, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " % " + rvalue.as_node->print();
    }
};

struct node_expr_shift_left : public node_expr_binary
{
    node_expr_shift_left(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_shift_left, std::move(lvalue), std::move(rvalue)) {}

    node_expr_shift_left(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_shift_left, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " << " + rvalue.as_node->print();
    }
};

struct node_expr_shift_right : public node_expr_binary
{
    node_expr_shift_right(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_shift_right, std::move(lvalue), std::move(rvalue)) {}

    node_expr_shift_right(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_shift_right, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " >> " + rvalue.as_node->print();
    }
};

struct node_expr_bitwise_or : public node_expr_binary
{
    node_expr_bitwise_or(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_bitwise_or, std::move(lvalue), std::move(rvalue)) {}

    node_expr_bitwise_or(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_bitwise_or, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " | " + rvalue.as_node->print();
    }
};

struct node_expr_bitwise_and : public node_expr_binary
{
    node_expr_bitwise_and(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_bitwise_and, std::move(lvalue), std::move(rvalue)) {}

    node_expr_bitwise_and(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_bitwise_and, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " & " + rvalue.as_node->print();
    }
};

struct node_expr_bitwise_exor : public node_expr_binary
{
    node_expr_bitwise_exor(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_bitwise_exor, std::move(lvalue), std::move(rvalue)) {}

    node_expr_bitwise_exor(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_bitwise_exor, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " ^ " + rvalue.as_node->print();
    }
};

struct node_expr_equality : public node_expr_binary
{
    node_expr_equality(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_equality, std::move(lvalue), std::move(rvalue)) {}

    node_expr_equality(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_equality, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " == " + rvalue.as_node->print();
    }
};

struct node_expr_inequality : public node_expr_binary
{
    node_expr_inequality(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_inequality, std::move(lvalue), std::move(rvalue)) {}

    node_expr_inequality(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_inequality, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " != " + rvalue.as_node->print();
    }
};

struct node_expr_less_equal : public node_expr_binary
{
    node_expr_less_equal(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_less_equal, std::move(lvalue), std::move(rvalue)) {}

    node_expr_less_equal(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_less_equal, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " <= " + rvalue.as_node->print();
    }
};

struct node_expr_greater_equal : public node_expr_binary
{
    node_expr_greater_equal(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_greater_equal, std::move(lvalue), std::move(rvalue)) {}

    node_expr_greater_equal(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_greater_equal, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " >= " + rvalue.as_node->print();
    }
};

struct node_expr_less : public node_expr_binary
{
    node_expr_less(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_less, std::move(lvalue), std::move(rvalue)) {}

    node_expr_less(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_less, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " < " + rvalue.as_node->print();
    }
};

struct node_expr_greater : public node_expr_binary
{
    node_expr_greater(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_greater, std::move(lvalue), std::move(rvalue)) {}

    node_expr_greater(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_greater, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " > " + rvalue.as_node->print();
    }
};

struct node_expr_or : public node_expr_binary
{
    node_expr_or(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_or, std::move(lvalue), std::move(rvalue)) {}

    node_expr_or(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_or, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " || " + rvalue.as_node->print();
    }
};

struct node_expr_and : public node_expr_binary
{
    node_expr_and(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_and, std::move(lvalue), std::move(rvalue)) {}

    node_expr_and(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_binary(node_type::expr_and, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " && " + rvalue.as_node->print();
    }
};

struct node_expr_ternary : public node
{
    expr_ptr cmp;
    expr_ptr lvalue;
    expr_ptr rvalue;

    node_expr_ternary(expr_ptr cmp, expr_ptr lvalue, expr_ptr rvalue)
        : node(node_type::expr_ternary), cmp(std::move(cmp)), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    node_expr_ternary(const std::string& location, expr_ptr cmp, expr_ptr lvalue, expr_ptr rvalue)
        : node(node_type::expr_ternary, location), cmp(std::move(cmp)), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return cmp.as_node->print() + " ? " + lvalue.as_node->print() + " : " + rvalue.as_node->print();
    }
};

struct node_expr_assign: public node
{
    expr_ptr lvalue;
    expr_ptr rvalue;

    node_expr_assign(node_type type, expr_ptr lvalue, expr_ptr rvalue)
        : node(type), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    node_expr_assign(node_type type, const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node(type, location), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
};

struct node_expr_assign_equal : public node_expr_assign
{
    node_expr_assign_equal(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_equal, std::move(lvalue), std::move(rvalue)) {}
    
    node_expr_assign_equal(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_equal, location, std::move(lvalue), std::move(rvalue)) {}
    
    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " = " + rvalue.as_node->print() ;
    };
};

struct node_expr_assign_add : public node_expr_assign
{
    node_expr_assign_add(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_add, std::move(lvalue), std::move(rvalue)) {}
    
    node_expr_assign_add(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_add, location, std::move(lvalue), std::move(rvalue)) {}
    
    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " += " + rvalue.as_node->print() ;
    };
};

struct node_expr_assign_sub : public node_expr_assign
{
    node_expr_assign_sub(expr_ptr lvalue, expr_ptr rvalue)
       : node_expr_assign(node_type::expr_assign_sub, std::move(lvalue), std::move(rvalue)) {}
    
    node_expr_assign_sub(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
       : node_expr_assign(node_type::expr_assign_sub, location, std::move(lvalue), std::move(rvalue)) {}
    
    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " -= " + rvalue.as_node->print() ;
    };
};

struct node_expr_assign_mult : public node_expr_assign
{
    node_expr_assign_mult(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_mult, std::move(lvalue), std::move(rvalue)) {}
    
    node_expr_assign_mult(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_mult, location, std::move(lvalue), std::move(rvalue)) {}
    
    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " *= " + rvalue.as_node->print() ;
    };
};

struct node_expr_assign_div : public node_expr_assign
{
    node_expr_assign_div(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_div, std::move(lvalue), std::move(rvalue)) {}
    
    node_expr_assign_div(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_div, location, std::move(lvalue), std::move(rvalue)) {}
    
    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " /= " + rvalue.as_node->print() ;
    };
};

struct node_expr_assign_mod : public node_expr_assign
{
    node_expr_assign_mod(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_mod, std::move(lvalue), std::move(rvalue)) {}
    
    node_expr_assign_mod(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_mod, location, std::move(lvalue), std::move(rvalue)) {}
    
    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " %= " + rvalue.as_node->print() ;
    };
};

struct node_expr_assign_shift_left : public node_expr_assign
{
    node_expr_assign_shift_left(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_shift_left, std::move(lvalue), std::move(rvalue)) {}
    
    node_expr_assign_shift_left(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_shift_left, location, std::move(lvalue), std::move(rvalue)) {}
    
    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " <<= " + rvalue.as_node->print() ;
    };
};

struct node_expr_assign_shift_right : public node_expr_assign
{
    node_expr_assign_shift_right(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_shift_right, std::move(lvalue), std::move(rvalue)) {}
    
    node_expr_assign_shift_right(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_shift_right, location, std::move(lvalue), std::move(rvalue)) {}
    
    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " >>= " + rvalue.as_node->print() ;
    };
};

struct node_expr_assign_bitwise_or : public node_expr_assign
{
    node_expr_assign_bitwise_or(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_bitwise_or, std::move(lvalue),
            std::move(rvalue)) {}

    node_expr_assign_bitwise_or(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_bitwise_or, location, std::move(lvalue),
            std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " |= " + rvalue.as_node->print();
    }
};

struct node_expr_assign_bitwise_and : public node_expr_assign
{
    node_expr_assign_bitwise_and(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_bitwise_and, std::move(lvalue), std::move(rvalue)) {}

    node_expr_assign_bitwise_and(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_bitwise_and, location, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " &= " + rvalue.as_node->print();
    }
};

struct node_expr_assign_bitwise_exor : public node_expr_assign
{
    node_expr_assign_bitwise_exor(expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_bitwise_exor, std::move(lvalue),
            std::move(rvalue)) {}

    node_expr_assign_bitwise_exor(const std::string& location, expr_ptr lvalue, expr_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_bitwise_exor, location, std::move(lvalue),
            std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + " ^= " + rvalue.as_node->print();
    }
};

struct node_expr_increment : public node_expr_assign
{
    node_expr_increment(expr_ptr lvalue)
        : node_expr_assign(node_type::expr_increment, std::move(lvalue), std::make_unique<node>()) {}

    node_expr_increment(const std::string& location, expr_ptr lvalue)
        : node_expr_assign(node_type::expr_increment, location, std::move(lvalue), std::make_unique<node>()) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + "++";
    }
};

struct node_expr_decrement : public node_expr_assign
{
    node_expr_decrement(expr_ptr lvalue)
        : node_expr_assign(node_type::expr_decrement, std::move(lvalue), std::make_unique<node>()) {}

    node_expr_decrement(const std::string& location, expr_ptr lvalue)
        : node_expr_assign(node_type::expr_decrement, location, std::move(lvalue), std::make_unique<node>()) {}

    auto print() -> std::string override
    {
        return lvalue.as_node->print() + "--";
    }
};

struct node_block : public node
{
    std::vector<stmt_ptr> stmts;

    node_block() : node(node_type::block) {}

    node_block(const std::string& location) : node(node_type::block, location) {}

    auto print() -> std::string override
    {
        std::string data;

        indent += 4;

        std::string pad = indented(indent);

        bool last_special = false;
        for (const auto& stmt : stmts)
        {
            if (&stmt != &stmts.front()
                && (stmt.as_node->type == node_type::stmt_if || stmt.as_node->type == node_type::stmt_ifelse
                || stmt.as_node->type == node_type::stmt_for || stmt.as_node->type == node_type::stmt_foreach
                || stmt.as_node->type == node_type::stmt_while || stmt.as_node->type == node_type::stmt_switch))
            {
                data += "\n";
            }
            else if(last_special) data += "\n";

            data += pad + stmt.as_node->print();

            if (&stmt != &stmts.back())
            {
                data += "\n";

                if(stmt.as_node->type == node_type::stmt_if || stmt.as_node->type == node_type::stmt_ifelse
                || stmt.as_node->type == node_type::stmt_for || stmt.as_node->type == node_type::stmt_foreach
                || stmt.as_node->type == node_type::stmt_while || stmt.as_node->type == node_type::stmt_switch)
                {
                    last_special = true;
                }
                else last_special = false;
            }
        }

        indent -= 4;

        return data;
    }
};

struct node_stmt_call : public node
{
    expr_call_ptr expr;

    node_stmt_call(expr_call_ptr expr)
        : node(node_type::stmt_call), expr(std::move(expr)) {}

    node_stmt_call(const std::string& location, expr_call_ptr expr)
        : node(node_type::stmt_call, location), expr(std::move(expr)) {}

    auto print()->std::string override
    {
        return expr->print() + ";";
    };
};

struct node_stmt_assign : public node
{
    expr_assign_ptr expr;

    node_stmt_assign(expr_assign_ptr expr)
        : node(node_type::stmt_assign), expr(std::move(expr)) {}
    
    node_stmt_assign(const std::string& location, expr_assign_ptr expr)
        : node(node_type::stmt_assign, location), expr(std::move(expr)) {}
    
    auto print()->std::string override
    {
        return expr->print() + ";";
    };
};

struct node_stmt_endon : public node
{
    expr_ptr obj;
    expr_ptr expr;

    node_stmt_endon(expr_ptr obj, expr_ptr expr)
        : node(node_type::stmt_endon), obj(std::move(obj)), expr(std::move(expr)) {}

    node_stmt_endon(const std::string& location, expr_ptr obj, expr_ptr expr)
        : node(node_type::stmt_endon, location), obj(std::move(obj)), expr(std::move(expr)) {}

    auto print() -> std::string override
    {
        return obj.as_node->print() + " endon( " + expr.as_node->print() + " );";
    };
};

struct node_stmt_notify : public node
{
    expr_ptr obj;
    expr_ptr expr;
    expr_arguments_ptr args;

    node_stmt_notify(expr_ptr obj, expr_ptr expr, expr_arguments_ptr args)
        : node(node_type::stmt_notify), obj(std::move(obj)), expr(std::move(expr)), args(std::move(args)) {}

    node_stmt_notify(const std::string& location, expr_ptr obj, expr_ptr expr, expr_arguments_ptr args)
        : node(node_type::stmt_notify, location), obj(std::move(obj)), expr(std::move(expr)), args(std::move(args)) {}

    auto print() -> std::string override
    {
        if (args->list.size() == 0)
        {
            return obj.as_node->print() + " notify( " + expr.as_node->print() + " );"; 
        }
        else
        {
            return obj.as_node->print() + " notify( " + expr.as_node->print() + ", " + args->print() + " );";
        }
    };
};

struct node_stmt_wait : public node
{
    expr_ptr expr;

    node_stmt_wait(expr_ptr expr)
        : node(node_type::stmt_wait), expr(std::move(expr)) {}

    node_stmt_wait(const std::string& location, expr_ptr expr)
        : node(node_type::stmt_wait, location), expr(std::move(expr)) {}

    auto print() -> std::string override
    {
        if(expr.as_node->type == node_type::data_float || expr.as_node->type == node_type::data_integer)
            return "wait " + expr.as_node->print() + ";";
        else
            return "wait(" + expr.as_node->print() + ");";
    };
};

struct node_stmt_waittill : public node
{
    expr_ptr obj;
    expr_ptr expr;
    expr_arguments_ptr args;

    node_stmt_waittill(expr_ptr obj, expr_ptr expr, expr_arguments_ptr args)
        : node(node_type::stmt_waittill), obj(std::move(obj)), expr(std::move(expr)), args(std::move(args)) {}

    node_stmt_waittill(const std::string& location, expr_ptr obj, expr_ptr expr, expr_arguments_ptr args)
        : node(node_type::stmt_waittill, location), obj(std::move(obj)), expr(std::move(expr)), args(std::move(args)) {}

    auto print() -> std::string override
    {
        if (args->list.size() == 0)
        {
            return obj.as_node->print() + " waittill( " + expr.as_node->print() + " );";
        }
        else
        {
            return obj.as_node->print() + " waittill( " + expr.as_node->print() + ", " + args->print() + " );";
        }
    };
};

struct node_stmt_waittillmatch : public node
{
    expr_ptr obj;
    expr_ptr lexpr;
    expr_ptr rexpr;

    node_stmt_waittillmatch(expr_ptr obj, expr_ptr lexpr, expr_ptr rexpr)
        : node(node_type::stmt_waittillmatch), obj(std::move(obj)), lexpr(std::move(lexpr)), rexpr(std::move(rexpr)) {}

    node_stmt_waittillmatch(const std::string& location, expr_ptr obj, expr_ptr lexpr, expr_ptr rexpr)
        : node(node_type::stmt_waittillmatch, location), obj(std::move(obj)), lexpr(std::move(lexpr)), rexpr(std::move(rexpr)) {}

    auto print() -> std::string override
    {
        return obj.as_node->print() + " waittillmatch( " + lexpr.as_node->print() + ", " + rexpr.as_node->print() + " );";
    };
};

struct node_stmt_waittillframeend : public node
{
    node_stmt_waittillframeend()
        : node(node_type::stmt_waittillframeend) {}

    node_stmt_waittillframeend(const std::string& location)
        : node(node_type::stmt_waittillframeend, location) {}

    auto print() -> std::string override
    {
        return "waittillframeend;";
    };
};

struct node_stmt_waitframe : public node
{
    node_stmt_waitframe()
        : node(node_type::stmt_waitframe) {}

    node_stmt_waitframe(const std::string& location)
        : node(node_type::stmt_waitframe, location) {}

    auto print() -> std::string override
    {
        return "waitframe;";
    };
};

struct node_stmt_if : public node
{
    expr_ptr expr;
    block_ptr block;

    node_stmt_if(expr_ptr expr, block_ptr block)
        : node(node_type::stmt_if), expr(std::move(expr)), block(std::move(block)) {}

    node_stmt_if(const std::string& location, expr_ptr expr, block_ptr block)
        : node(node_type::stmt_if, location), expr(std::move(expr)), block(std::move(block)) {}

    auto print() -> std::string override
    {
        std::string data = "if ( " + expr.as_node->print() + " )\n";

        std::string pad = indented(indent);

        if (block->stmts.size() == 1)
        {
            auto& stmt = block->stmts.front();
            if(stmt.as_node->type == node_type::stmt_if || stmt.as_node->type == node_type::stmt_ifelse
                || stmt.as_node->type == node_type::stmt_for || stmt.as_node->type == node_type::stmt_foreach
                || stmt.as_node->type == node_type::stmt_while || stmt.as_node->type == node_type::stmt_switch)
            {
                data +=  pad + "{\n" + block->print() + "\n" + pad + "}";
            }
            else
                data +=  block->print();
        }
        else
        {
            data +=  pad + "{\n" + block->print() + "\n" + pad + "}";
        }
        
        return data;
    };
};

struct node_stmt_ifelse : public node
{
    expr_ptr expr;
    block_ptr block_if;
    block_ptr block_else;

    node_stmt_ifelse(expr_ptr expr, block_ptr block_if, block_ptr block_else)
        : node(node_type::stmt_ifelse), expr(std::move(expr)), block_if(std::move(block_if)), block_else(std::move(block_else)) {}

    node_stmt_ifelse(const std::string& location, expr_ptr expr, block_ptr block_if, block_ptr block_else)
        : node(node_type::stmt_ifelse, location), expr(std::move(expr)), block_if(std::move(block_if)), block_else(std::move(block_else)) {}

    auto print() -> std::string override
    {
        std::string pad = indented(indent);
        std::string data = "if ( " + expr.as_node->print() + " )\n";
        
        if (block_if->stmts.size() == 1)
        {
            auto& stmt = block_if->stmts.front().as_node;
            if(stmt->type == node_type::stmt_if || stmt->type == node_type::stmt_ifelse
                || stmt->type == node_type::stmt_for || stmt->type == node_type::stmt_foreach
                || stmt->type == node_type::stmt_while || stmt->type == node_type::stmt_switch)
            {
                data +=  pad + "{\n" + block_if->print() + "\n" + pad + "}\n";
            }
            else
                data +=  block_if->print() + "\n";
        }
        else
        {
            data +=  pad + "{\n" + block_if->print() + "\n" + pad + "}\n";
        }

        data += pad + "else";

        if (block_else->stmts.size() == 1)
        {
            auto& blk = block_else->stmts.front().as_node;
            if(blk->type == node_type::stmt_if || blk->type == node_type::stmt_ifelse)
            {
                data += " " + blk->print();
            }
            else if(blk->type == node_type::stmt_for || blk->type == node_type::stmt_foreach
                || blk->type == node_type::stmt_while || blk->type == node_type::stmt_switch)
            {
                data +=  "\n" + pad + "{\n" + block_else->print() + "\n" + pad + "}";
            }
            else
            {
                data +=  "\n" + block_else->print();
            }
        }
        else
        { 
            data +=  "\n" + pad + "{\n" + block_else->print() + "\n" + pad + "}";
        }
        
        return data;
    };
};

struct node_stmt_while : public node
{
    expr_ptr expr;
    block_ptr block;

    node_stmt_while(expr_ptr expr, block_ptr block)
        : node(node_type::stmt_while), expr(std::move(expr)), block(std::move(block)) {}

    node_stmt_while(const std::string& location, expr_ptr expr, block_ptr block)
        : node(node_type::stmt_while, location), expr(std::move(expr)), block(std::move(block)) {}

    auto print() -> std::string override
    {
        std::string data;

        if (expr.as_node->type == node_type::null)
        {
            data += "while ( true )\n";
        }
        else
        {
            data += "while ( " + expr.as_node->print() + " )\n";
        }

        std::string pad = indented(indent);

        if (block->stmts.size() == 1)
        {
            auto& stmt = block->stmts.front();
            if(stmt.as_node->type == node_type::stmt_if || stmt.as_node->type == node_type::stmt_ifelse
                || stmt.as_node->type == node_type::stmt_for || stmt.as_node->type == node_type::stmt_foreach
                || stmt.as_node->type == node_type::stmt_while || stmt.as_node->type == node_type::stmt_switch)
            {
                data +=  pad + "{\n" + block->print() + "\n" + pad + "}";
            }
            else
                data +=  block->print();
        }
        else
        {
            data +=  pad + "{\n" + block->print() + "\n" + pad + "}";
        }

        return data;
    };
};

struct node_stmt_for : public node
{
    expr_ptr pre_expr;
    expr_ptr expr;
    expr_ptr post_expr;
    block_ptr block;

    node_stmt_for(expr_ptr pre_expr, expr_ptr expr, expr_ptr post_expr, block_ptr block)
        : node(node_type::stmt_for), pre_expr(std::move(pre_expr)), expr(std::move(expr)),
            post_expr(std::move(post_expr)), block(std::move(block)) {}

    node_stmt_for(const std::string& location, expr_ptr pre_expr, expr_ptr expr, expr_ptr post_expr, block_ptr block)
        : node(node_type::stmt_for, location), pre_expr(std::move(pre_expr)), expr(std::move(expr)),
            post_expr(std::move(post_expr)), block(std::move(block)) {}

    auto print() -> std::string override
    {
        std::string data;

        if (expr.as_node->type == node_type::null)
        {
            data += "for (;;)\n";
        }
        else
        {
            data += "for ( " + pre_expr.as_node->print() + "; " + expr.as_node->print() + "; " + post_expr.as_node->print() + " )\n";
        }

        std::string pad = indented(indent);

        if (block->stmts.size() == 1)
        {
            auto& stmt = block->stmts.front();
            if(stmt.as_node->type == node_type::stmt_if || stmt.as_node->type == node_type::stmt_ifelse
                || stmt.as_node->type == node_type::stmt_for || stmt.as_node->type == node_type::stmt_foreach
                || stmt.as_node->type == node_type::stmt_while || stmt.as_node->type == node_type::stmt_switch)
            {
                data += pad + "{\n" + block->print() + "\n" + pad + "}";
            }
            else
                data += block->print();
        }
        else
        {
            data +=  pad + "{\n" + block->print() + "\n" + pad + "}";
        }

        return data;
    };
};

struct node_stmt_foreach : public node
{
    expr_ptr expr1;
    expr_ptr expr2;
    block_ptr block;

    node_stmt_foreach(expr_ptr expr1, expr_ptr expr2, block_ptr block)
        : node(node_type::stmt_foreach), expr1(std::move(expr1)), expr2(std::move(expr2)),
            block(std::move(block)) {}

    node_stmt_foreach(const std::string& location, expr_ptr expr1, expr_ptr expr2, block_ptr block)
        : node(node_type::stmt_foreach, location), expr1(std::move(expr1)), expr2(std::move(expr2)),
            block(std::move(block)) {}

    auto print() -> std::string override
    {
        std::string data;

        data += "foreach ( " + expr1.as_node->print() + " in " + expr2.as_node->print() + " )\n";

        std::string pad = indented(indent);

        if (block->stmts.size() == 1)
        {
            auto& stmt = block->stmts.front();
            if(stmt.as_node->type == node_type::stmt_if || stmt.as_node->type == node_type::stmt_ifelse
                || stmt.as_node->type == node_type::stmt_for || stmt.as_node->type == node_type::stmt_foreach
                || stmt.as_node->type == node_type::stmt_while || stmt.as_node->type == node_type::stmt_switch)
            {
                data +=  pad + "{\n" + block->print() + "\n" + pad + "}";
            }
            else
                data +=  block->print(); 
        }
        else
        {
            data +=  pad + "{\n" + block->print() + "\n" + pad + "}";
        }

        return data;
    };
};

struct node_stmt_switch : public node
{
    expr_ptr expr;
    block_ptr block;

    node_stmt_switch(expr_ptr expr, block_ptr block)
        : node(node_type::stmt_switch), expr(std::move(expr)), block(std::move(block)) {}

    node_stmt_switch(const std::string& location, expr_ptr expr, block_ptr block)
        : node(node_type::stmt_switch, location), expr(std::move(expr)), block(std::move(block)) {}

    auto print() -> std::string override
    {
        std::string data;
        std::string pad = indented(indent);

        data += "switch ( " + expr.as_node->print() + " )\n";
        data +=  pad + "{\n" + block->print() + "\n" + pad + "}";

        return data;
    };
};

struct node_stmt_case : public node
{
    expr_ptr value;

    node_stmt_case(expr_ptr value)
        : node(node_type::stmt_case), value(std::move(value)) {}

    node_stmt_case(const std::string& location, expr_ptr value)
        : node(node_type::stmt_case, location), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "case " + value.as_node->print() + ":";
    };
};

struct node_stmt_default : public node
{
    node_stmt_default()
        : node(node_type::stmt_default) {}

    node_stmt_default(const std::string& location)
        : node(node_type::stmt_default, location) {}

    auto print() -> std::string override
    {
        return "default:";
    };
};

struct node_stmt_break : public node
{
    node_stmt_break()
        : node(node_type::stmt_break) {}

    node_stmt_break(const std::string& location)
        : node(node_type::stmt_break, location) {}

    auto print() -> std::string override
    {
        return "break;";
    };
};

struct node_stmt_continue : public node
{
    node_stmt_continue()
        : node(node_type::stmt_continue) {}

    node_stmt_continue(const std::string& location)
        : node(node_type::stmt_continue, location) {}

    auto print() -> std::string override
    {
        return "continue;";
    };
};

struct node_stmt_return : public node
{
    expr_ptr expr;

    node_stmt_return(expr_ptr expr)
        : node(node_type::stmt_return), expr(std::move(expr)) {}

    node_stmt_return(const std::string& location, expr_ptr expr)
        : node(node_type::stmt_return, location), expr(std::move(expr)) {}

    auto print() -> std::string override
    {
        if(expr.as_node->type == node_type::null)
            return "return;";

        return "return " + expr.as_node->print() + ";";
    };
};

struct node_parameters : public node
{
    std::vector<identifier_ptr> list;

    node_parameters()
        : node(node_type::parameters) {}

    node_parameters(const std::string& location)
        : node(node_type::parameters, location) {}

    auto print() -> std::string override
    {
        std::string data;

        for (const auto& param : list)
        {
            data += " " + param->print();
            data += (&param != &list.back()) ? "," : " ";
        }

        return data;
    }
};

struct node_thread : public node
{
    identifier_ptr name;
    parameters_ptr params;
    block_ptr block;

    node_thread(identifier_ptr name, parameters_ptr params, block_ptr block)
        : node(node_type::thread), name(std::move(name)), params(std::move(params)),
            block(std::move(block)) {}

    node_thread(const std::string& location, identifier_ptr name, parameters_ptr params, block_ptr block)
        : node(node_type::thread, location), name(std::move(name)), params(std::move(params)),
            block(std::move(block)) {}

    auto print() -> std::string override
    {
        return name->print() + "(" + params->print() + ")" + "\n{\n" + block->print() + "\n}\n";
    }
};

struct node_constant : public node
{
    identifier_ptr id;
    expr_ptr value;

    node_constant(identifier_ptr id, expr_ptr value)
        : node(node_type::constant), id(std::move(id)), value(std::move(value)) {}

    node_constant(const std::string& location, identifier_ptr id, expr_ptr value)
        : node(node_type::constant, location), id(std::move(id)), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return id->print() + " = "s + value.as_node->print() + ";\n";
    }
};

struct node_using_animtree : public node
{
    string_ptr animtree;

    node_using_animtree(string_ptr animtree)
        : node(node_type::using_animtree), animtree(std::move(animtree)) {}

    node_using_animtree(const std::string& location, string_ptr animtree)
        : node(node_type::using_animtree, location), animtree(std::move(animtree)) {}

    auto print() -> std::string override
    {
        return "#using_animtree"s + "(" + animtree->print() + ");\n";
    }
};

struct node_include : public node
{
    filepath_ptr file;

    node_include(filepath_ptr file)
        : node(node_type::include), file(std::move(file)) {}

    node_include(const std::string& location, filepath_ptr file)
        : node(node_type::include, location), file(std::move(file)) {}

    auto print() -> std::string override
    {
        return "#include"s + " " + file->print() + ";\n";
    }
};

struct node_script : public node
{
    std::vector<include_ptr> includes;
    std::vector<definition_ptr> definitions;
    
    node_script()
        : node(node_type::script) {}

    node_script(const std::string& location)
        : node(node_type::script, location) {}

    auto print() -> std::string override
    {
        std::string data;

        for (const auto& include : includes)
        {
            data += include->print();
        }

        for (const auto& def : definitions)
        {
            if(def.as_node->type == node_type::thread)
            {
                data += "\n";
            }

            data += def.as_node->print();
        }

        return data;
    }
};

struct node_asm_loc : public node
{
    std::string value;

    node_asm_loc(std::string value)
        : node(node_type::asm_loc), value(std::move(value)) {}

    node_asm_loc(const std::string& location, std::string value)
        : node(node_type::asm_loc, location), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return value + ":";
    }
};

struct node_asm_jump : public node
{
    std::string value;

    node_asm_jump(std::string value)
        : node(node_type::asm_jump), value(std::move(value)) {}

    node_asm_jump(const std::string& location, std::string value)
        : node(node_type::asm_jump, location), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "jump " + value;
    }
};

struct node_asm_jump_back : public node
{
    std::string value;

    node_asm_jump_back(std::string value)
        : node(node_type::asm_jump_back), value(std::move(value)) {}

    node_asm_jump_back(const std::string& location, std::string value)
        : node(node_type::asm_jump_back, location), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "jump_back " + value;
    }
};

struct node_asm_jump_cond : public node
{
    std::string value;
    expr_ptr expr;

    node_asm_jump_cond(expr_ptr expr, std::string value)
        : node(node_type::asm_jump_cond), expr(std::move(expr)), value(std::move(value)) {}

    node_asm_jump_cond(const std::string& location, expr_ptr expr, std::string value)
        : node(node_type::asm_jump_cond, location), expr(std::move(expr)), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "jump_cond( " + expr.as_node->print() + " ) " + value;
    }
};

struct node_asm_jump_true_expr : public node
{
    expr_ptr expr;
    std::string value;

    node_asm_jump_true_expr(expr_ptr expr, std::string value)
        : node(node_type::asm_jump_true_expr), expr(std::move(expr)), value(std::move(value)) {}

    node_asm_jump_true_expr(const std::string& location, expr_ptr expr, std::string value)
        : node(node_type::asm_jump_true_expr, location), expr(std::move(expr)), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "expr_true " + value;
    }
};

struct node_asm_jump_false_expr : public node
{
    expr_ptr expr;
    std::string value;

    node_asm_jump_false_expr(expr_ptr expr, std::string value)
        : node(node_type::asm_jump_false_expr), expr(std::move(expr)), value(std::move(value)) {}

    node_asm_jump_false_expr(const std::string& location, expr_ptr expr, std::string value)
        : node(node_type::asm_jump_false_expr, location), expr(std::move(expr)), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "expr_false " + value;
    }
};

struct node_asm_switch : public node
{
    expr_ptr expr;
    std::string value;

    node_asm_switch(expr_ptr expr, std::string value)
        : node(node_type::asm_switch), expr(std::move(expr)), value(std::move(value)) {}

    node_asm_switch(const std::string& location, expr_ptr expr, std::string value)
        : node(node_type::asm_switch, location), expr(std::move(expr)), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "switch( " + expr.as_node->print() + " ) " + value;
    }
};

struct node_asm_endswitch : public node
{
    std::vector<std::string> data;
    std::string count;

    node_asm_endswitch(std::vector<std::string> data, std::string count)
        : node(node_type::asm_endswitch), data(std::move(data)), count(std::move(count)) {}

    node_asm_endswitch(const std::string& location, std::vector<std::string> data, std::string count)
        : node(node_type::asm_endswitch, location), data(std::move(data)), count(std::move(count)) {}

    auto print() -> std::string override
    {
        std::string p;
        for(auto& d : data)
        {
            p+= " " + d;
        }
        return "endswitch( " + count + " ) " + p;
    }
};

struct node_asm_prescriptcall : public node
{
    node_asm_prescriptcall()
        : node(node_type::asm_prescriptcall) {}

    node_asm_prescriptcall(const std::string& location)
        : node(node_type::asm_prescriptcall, location) {}

    auto print() -> std::string override
    {
        return "prescriptcall";
    }
};

struct node_asm_voidcodepos : public node
{
    node_asm_voidcodepos()
        : node(node_type::asm_voidcodepos) {}

    node_asm_voidcodepos(const std::string& location)
        : node(node_type::asm_voidcodepos, location) {}

    auto print() -> std::string override
    {
        return "voidcodepos";
    }
};

} // namespace gsc

#endif // _GSC_NODETREE_HPP_
