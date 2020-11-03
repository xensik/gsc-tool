// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_NODETREE_H_
#define _GSC_NODETREE_H_

enum class node_type
{
    // EMPTY NODE
    null,
    // KEYWORDS
    level,
    anim,
    self,
    game,
    size,
    undefined,
    empty_array,
    // DATA TYPES
    filepath,
    identifier,
    string,
    string_loc,
    string_hash,
    animref,
    integer,
    float_,
    vector,
    // EXPRESSIONS
    expr_vector,
    expr_select,
    expr_subscribe,
    expr_func_ref,
    expr_arg_list,
    expr_pointer_call,
    expr_func_call,
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
    expr_bw_or,
    expr_bw_and,
    expr_bw_xor,
    expr_cmp_equal,
    expr_cmp_not_equal,
    expr_cmp_less_equal,
    expr_cmp_greater_equal,
    expr_cmp_less,
    expr_cmp_greater,
    expr_cmp_or,
    expr_cmp_and,
    expr_ternary,
    // EXPR ASSIGN
    expr_assign_equal,
    expr_assign_add,
    expr_assign_sub,
    expr_assign_mult,
    expr_assign_div,
    expr_assign_mod,
    expr_assign_shift_left,
    expr_assign_shift_right,
    expr_assign_bw_or,
    expr_assign_bw_and,
    expr_assign_bw_xor,
    expr_inc,
    expr_dec,
    // STATEMENTS
    stmt_call,
    stmt_assign,
    stmt_endon,
    stmt_notify,
    stmt_wait,
    stmt_waittill,
    stmt_waittillmatch,
    stmt_waittillframeend,
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
    stmt_block,
    // SCRIPT
    param_list,
    function,
    animtree,
    using_animtree,
    include,
    script,
    // DECOMPILER
    asm_loc,
    asm_jump,
    asm_jumpback,
    asm_jump_on_true,
    asm_jump_on_false,
    asm_jump_on_true_expr,
    asm_jump_on_false_expr,
};

struct node
{
    node_type type;

    node() : type(node_type::null) {}
    node(node_type type) : type(type) {}
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

using node_ptr = std::unique_ptr<node>;

struct node_level : public node
{
    node_level() : node(node_type::level) {}

    auto print() -> std::string override
    {
        return "level";
    }
};

using level_ptr = std::unique_ptr<node_level>;

struct node_anim : public node
{
    node_anim() : node(node_type::anim) {}

    auto print() -> std::string override
    {
        return "anim";
    }
};

using anim_ptr = std::unique_ptr<node_anim>;

struct node_self : public node
{
    node_self() : node(node_type::self) {}

    auto print() -> std::string override
    {
        return "self";
    }
};

using self_ptr = std::unique_ptr<node_self>;

struct node_game : public node
{
    node_game() : node(node_type::game) {}

    auto print() -> std::string override
    {
        return "game";
    }
};

using game_ptr = std::unique_ptr<node_game>;

struct node_size : public node
{
    node_size() : node(node_type::size) {}

    auto print() -> std::string override
    {
        return "size";
    }
};

using size_ptr = std::unique_ptr<node_size>;

struct node_undefined : public node
{
    node_undefined() : node(node_type::undefined) {}

    auto print() -> std::string override
    {
        return "undefined";
    }
};

using undefined_ptr = std::unique_ptr<node_undefined>;

struct node_empty_array : public node
{
    node_empty_array() : node(node_type::empty_array) {}

    auto print() -> std::string override
    {
        return "[]";
    }
};

using empty_array_ptr = std::unique_ptr<node_empty_array>;

struct node_filepath : public node
{
    std::string value;

    node_filepath(const std::string& value) : node(node_type::filepath), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

using filepath_ptr = std::unique_ptr<node_filepath>;

struct node_identifier : public node
{
    std::string value;

    node_identifier(const std::string& value) : node(node_type::identifier), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

using identifier_ptr = std::unique_ptr<node_identifier>;

struct node_string : public node
{
    std::string value;

    node_string(const std::string& value) : node(node_type::string), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

using string_ptr = std::unique_ptr<node_string>;

struct node_string_loc : public node
{
    std::string value;

    node_string_loc(const std::string& value) : node(node_type::string_loc), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

using string_loc_ptr = std::unique_ptr<node_string_loc>;

struct node_string_hash : public node
{
    std::string value;

    node_string_hash(const std::string& value) : node(node_type::string_hash), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

using string_hash_ptr = std::unique_ptr<node_string_hash>;

struct node_integer : public node
{
    std::string value;

    node_integer(const std::string& value) : node(node_type::integer), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

using integer_ptr = std::unique_ptr<node_integer>;

struct node_float : public node
{
    std::string value;

    node_float(const std::string& value) : node(node_type::float_), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

using float_ptr = std::unique_ptr<node_float>;

struct node_vector : public node
{
    node_ptr x;
    node_ptr y;
    node_ptr z;

    node_vector(node_ptr x, node_ptr y, node_ptr z)
        : node(node_type::vector), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}

    auto print() -> std::string override
    {
        return "( "s + x->print() + ", " + y->print() + ", "+ z->print() + " )";
    }
};

using vector_ptr = std::unique_ptr<node_vector>;

// EXPRESSIONS

struct node_expr_vector : public node
{
    node_ptr x;
    node_ptr y;
    node_ptr z;

    node_expr_vector(node_ptr x, node_ptr y, node_ptr z)
        : node(node_type::expr_vector), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}

    auto print() -> std::string override
    {
        return "( "s + x->print() + ", " + y->print() + ", "+ z->print() + " )";
    }
};

using expr_vector_ptr = std::unique_ptr<node_expr_vector>;

struct node_expr_select : public node
{
    node_ptr obj;
    node_ptr field;

    node_expr_select(node_ptr obj, node_ptr field)
        : node(node_type::expr_select), obj(std::move(obj)), field(std::move(field)) {}

    auto print() -> std::string override
    {
        return obj->print() + "." + field->print();
    }
};

using expr_select_ptr = std::unique_ptr<node_expr_select>;

struct node_expr_subscribe : public node
{
    node_ptr obj;
    node_ptr key;

    node_expr_subscribe(node_ptr obj, node_ptr key)
        : node(node_type::expr_subscribe), obj(std::move(obj)), key(std::move(key)) {}

    auto print() -> std::string override
    {
        return obj->print() + "[ " + key->print() + " ]";
    }
};

using expr_subscribe_ptr = std::unique_ptr<node_expr_subscribe>;

struct node_expr_func_ref : public node
{
    filepath_ptr file;
    identifier_ptr func;

    node_expr_func_ref(filepath_ptr file, identifier_ptr func)
        : node(node_type::expr_func_ref), file(std::move(file)), func(std::move(func)) {}

    auto print() -> std::string override
    {
        return file->print() + "::" + func->print();
    }
};

using expr_func_ref_ptr = std::unique_ptr<node_expr_func_ref>;

struct node_expr_arg_list : public node
{
    std::vector<node_ptr> args;

    node_expr_arg_list() : node(node_type::expr_arg_list) {}

    auto print() -> std::string override
    {
        std::string data;

        for (const auto& arg : args)
        {
            data += " " + arg->print();
            data += (&arg != &args.back()) ? "," : " ";
        }

        return data;
    }
};

using expr_arg_list_ptr = std::unique_ptr<node_expr_arg_list>;

struct node_expr_pointer_call : public node
{
    node_ptr expr;
    expr_arg_list_ptr arg_list;

    node_expr_pointer_call(node_ptr expr, expr_arg_list_ptr arg_list)
        : node(node_type::expr_pointer_call), expr(std::move(expr)),
            arg_list(std::move(arg_list)) {}

    auto print() -> std::string override
    {
        return "[["s + expr->print() + "]](" + arg_list->print() + ")";
    }
};

using expr_pointer_call_ptr = std::unique_ptr<node_expr_pointer_call>;

struct node_expr_func_call : public node
{
    filepath_ptr file;
    identifier_ptr name;
    expr_arg_list_ptr arg_list;

    node_expr_func_call(filepath_ptr file, identifier_ptr name, expr_arg_list_ptr arg_list)
        : node(node_type::expr_func_call), file(std::move(file)), name(std::move(name)),
            arg_list(std::move(arg_list)) {}

    auto print() -> std::string override
    {
        if(file->value == "")
        {
            return name->print() + "(" + arg_list->print() + ")";
        }

        return file->print() + "::" + name->print() + "(" + arg_list->print() + ")";
    }
};

using expr_func_call_ptr = std::unique_ptr<node_expr_func_call>;

union expr_call_type_ptr
{
    node_ptr as_node;
    expr_pointer_call_ptr as_pointer;
    expr_func_call_ptr as_func;

    expr_call_type_ptr() {}
    expr_call_type_ptr(expr_call_type_ptr && val) { new(&as_node) node_ptr(std::move(val.as_node)); }
    ~expr_call_type_ptr(){}
};

struct node_expr_call : public node
{
    node_ptr obj;
    expr_call_type_ptr func;
    bool thread;

    node_expr_call(bool thread, node_ptr obj, expr_call_type_ptr func)
        : node(node_type::expr_call), thread(thread), obj(std::move(obj)), 
            func(std::move(func)){}

    auto print() -> std::string override
    {
        if(thread)
        {
            if(obj->type == node_type::null)
                return "thread " + func.as_node->print();

            return obj->print() + " thread " + func.as_node->print();
        }
        else if(obj->type == node_type::null)
            return func.as_node->print();
        else
            return obj->print() + " " + func.as_node->print();
    }
};

using expr_call_ptr = std::unique_ptr<node_expr_call>;

struct node_expr_complement : public node
{
    node_ptr rvalue;

    node_expr_complement(node_ptr rvalue)
        : node(node_type::expr_complement), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return "~" + rvalue->print();
    }
};

using expr_complement_ptr = std::unique_ptr<node_expr_complement>;

struct node_expr_not : public node
{
    node_ptr rvalue;

    node_expr_not(node_ptr rvalue)
        : node(node_type::expr_not), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return "!" + rvalue->print();
    }
};

using expr_not_ptr = std::unique_ptr<node_expr_not>;

struct node_expr_binary : public node
{
    node_ptr lvalue;
    node_ptr rvalue;

    node_expr_binary(node_type type, node_ptr lvalue, node_ptr rvalue)
        : node(type), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
};

using expr_binary_ptr = std::unique_ptr<node_expr_binary>;

struct node_expr_add : public node_expr_binary
{
    node_expr_add(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_add, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " + " + rvalue->print();
    }
};

using expr_add_ptr = std::unique_ptr<node_expr_add>;

struct node_expr_sub : public node_expr_binary
{
    node_expr_sub(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_sub, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " - " + rvalue->print();
    }
};

using expr_sub_ptr = std::unique_ptr<node_expr_sub>;

struct node_expr_mult : public node_expr_binary
{
    node_expr_mult(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_mult, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " * " + rvalue->print();
    }
};

using expr_mult_ptr = std::unique_ptr<node_expr_mult>;

struct node_expr_div : public node_expr_binary
{
    node_expr_div(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_div, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " / " + rvalue->print();
    }
};

using expr_div_ptr = std::unique_ptr<node_expr_div>;

struct node_expr_mod : public node_expr_binary
{
    node_expr_mod(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_mod, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " % " + rvalue->print();
    }
};

using expr_mod_ptr = std::unique_ptr<node_expr_mod>;

struct node_expr_shift_left : public node_expr_binary
{
    node_expr_shift_left(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_shift_left, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " << " + rvalue->print();
    }
};

using expr_shift_left_ptr = std::unique_ptr<node_expr_shift_left>;

struct node_expr_shift_right : public node_expr_binary
{
    node_expr_shift_right(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_shift_right, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " >> " + rvalue->print();
    }
};

using expr_shift_right_ptr = std::unique_ptr<node_expr_shift_right>;

struct node_expr_bw_or : public node_expr_binary
{
    node_expr_bw_or(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_bw_or, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " | " + rvalue->print();
    }
};

using expr_bw_or_ptr = std::unique_ptr<node_expr_bw_or>;

struct node_expr_bw_and : public node_expr_binary
{
    node_expr_bw_and(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_bw_and, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " & " + rvalue->print();
    }
};

using expr_bw_and_ptr = std::unique_ptr<node_expr_bw_and>;

struct node_expr_bw_xor : public node_expr_binary
{
    node_expr_bw_xor(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_bw_xor, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " ^ " + rvalue->print();
    }
};

using expr_bw_xor_ptr = std::unique_ptr<node_expr_bw_xor>;

struct node_expr_cmp_equal : public node_expr_binary
{
    node_expr_cmp_equal(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_cmp_equal, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " == " + rvalue->print();
    }
};

using expr_cmp_equal_ptr = std::unique_ptr<node_expr_cmp_equal>;

struct node_expr_cmp_not_equal : public node_expr_binary
{
    node_expr_cmp_not_equal(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_cmp_not_equal, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " != " + rvalue->print();
    }
};

using expr_cmp_not_equal_ptr = std::unique_ptr<node_expr_cmp_not_equal>;

struct node_expr_cmp_less_equal : public node_expr_binary
{
    node_expr_cmp_less_equal(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_cmp_less_equal, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " <= " + rvalue->print();
    }
};

using expr_cmp_less_equal_ptr = std::unique_ptr<node_expr_cmp_less_equal>;

struct node_expr_cmp_greater_equal : public node_expr_binary
{
    node_expr_cmp_greater_equal(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_cmp_greater_equal, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " >= " + rvalue->print();
    }
};

using expr_cmp_greater_equal_ptr = std::unique_ptr<node_expr_cmp_greater_equal>;

struct node_expr_cmp_less : public node_expr_binary
{
    node_expr_cmp_less(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_cmp_less, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " < " + rvalue->print();
    }
};

using expr_cmp_less_ptr = std::unique_ptr<node_expr_cmp_less>;

struct node_expr_cmp_greater : public node_expr_binary
{
    node_expr_cmp_greater(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_cmp_greater, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " > " + rvalue->print();
    }
};

using expr_cmp_greater_ptr = std::unique_ptr<node_expr_cmp_greater>;

struct node_expr_cmp_or : public node_expr_binary
{
    node_expr_cmp_or(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_cmp_or, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " || " + rvalue->print();
    }
};

using expr_cmp_or_ptr = std::unique_ptr<node_expr_cmp_or>;

struct node_expr_cmp_and : public node_expr_binary
{
    node_expr_cmp_and(node_ptr lvalue, node_ptr rvalue)
        : node_expr_binary(node_type::expr_cmp_and, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " && " + rvalue->print();
    }
};

using expr_cmp_and_ptr = std::unique_ptr<node_expr_cmp_and>;

struct node_expr_ternary : public node
{
    node_ptr cmp;
    node_ptr lvalue;
    node_ptr rvalue;

    node_expr_ternary(node_ptr cmp, node_ptr lvalue, node_ptr rvalue)
        : node(node_type::expr_ternary), cmp(std::move(cmp)), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return cmp->print() + " ? " + lvalue->print() + " : " + rvalue->print();
    }
};

using expr_ternary_ptr = std::unique_ptr<node_expr_ternary>;

struct node_expr_assign: public node
{
    node_ptr lvalue;
    node_ptr rvalue;

    node_expr_assign(node_type type, node_ptr lvalue, node_ptr rvalue)
        : node(type), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
};

using expr_assign_ptr = std::unique_ptr<node_expr_assign>;

struct node_expr_assign_equal : public node_expr_assign
{
    node_expr_assign_equal(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_equal, std::move(lvalue), std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " = " + rvalue->print() ;
    };
};

using expr_assign_equal_ptr = std::unique_ptr<node_expr_assign_equal>;

struct node_expr_assign_add : public node_expr_assign
{
    node_expr_assign_add(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_add, std::move(lvalue), std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " += " + rvalue->print() ;
    };
};

using expr_assign_add_ptr = std::unique_ptr<node_expr_assign_add>;

struct node_expr_assign_sub : public node_expr_assign
{
    node_expr_assign_sub(node_ptr lvalue, node_ptr rvalue)
       : node_expr_assign(node_type::expr_assign_sub, std::move(lvalue), std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " -= " + rvalue->print() ;
    };
};

using expr_assign_sub_ptr = std::unique_ptr<node_expr_assign_sub>;

struct node_expr_assign_mult : public node_expr_assign
{
    node_expr_assign_mult(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_mult, std::move(lvalue), std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " *= " + rvalue->print() ;
    };
};

using expr_assign_mult_ptr = std::unique_ptr<node_expr_assign_mult>;

struct node_expr_assign_div : public node_expr_assign
{
    node_expr_assign_div(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_div, std::move(lvalue), std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " /= " + rvalue->print() ;
    };
};

using expr_assign_div_ptr = std::unique_ptr<node_expr_assign_div>;

struct node_expr_assign_mod : public node_expr_assign
{
    node_expr_assign_mod(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_mod, std::move(lvalue), std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " %= " + rvalue->print() ;
    };
};

using expr_assign_mod_ptr = std::unique_ptr<node_expr_assign_mod>;

struct node_expr_assign_shift_left : public node_expr_assign
{
    node_expr_assign_shift_left(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_shift_left, std::move(lvalue), std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " <<= " + rvalue->print() ;
    };
};

using expr_assign_shift_left_ptr = std::unique_ptr<node_expr_assign_shift_left>;

struct node_expr_assign_shift_right : public node_expr_assign
{
    node_expr_assign_shift_right(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_shift_right, std::move(lvalue), std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " >>= " + rvalue->print() ;
    };
};

using expr_assign_shift_right_ptr = std::unique_ptr<node_expr_assign_shift_right>;

struct node_expr_assign_bw_or : public node_expr_assign
{
    node_expr_assign_bw_or(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_bw_or, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " |= " + rvalue->print();
    }
};

using expr_assign_bw_or_ptr = std::unique_ptr<node_expr_assign_bw_or>;

struct node_expr_assign_bw_and : public node_expr_assign
{
    node_expr_assign_bw_and(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_bw_and, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " &= " + rvalue->print();
    }
};

using expr_assign_bw_and_ptr = std::unique_ptr<node_expr_assign_bw_and>;

struct node_expr_assign_bw_xor : public node_expr_assign
{
    node_expr_assign_bw_xor(node_ptr lvalue, node_ptr rvalue)
        : node_expr_assign(node_type::expr_assign_bw_xor, std::move(lvalue), std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " ^= " + rvalue->print();
    }
};

using expr_assign_bw_xor_ptr = std::unique_ptr<node_expr_assign_bw_xor>;

struct node_expr_inc : public node_expr_assign
{
    node_expr_inc(node_ptr lvalue)
        : node_expr_assign(node_type::expr_inc, std::move(lvalue), std::make_unique<node>()) {}

    auto print() -> std::string override
    {
        return lvalue->print() + "++";
    }
};

using expr_inc_ptr = std::unique_ptr<node_expr_inc>;

struct node_expr_dec : public node_expr_assign
{
    node_expr_dec(node_ptr lvalue)
        : node_expr_assign(node_type::expr_dec, std::move(lvalue), std::make_unique<node>()) {}

    auto print() -> std::string override
    {
        return lvalue->print() + "--";
    }
};

using expr_dec_ptr = std::unique_ptr<node_expr_dec>;

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
    filepath_ptr as_filepath;
    identifier_ptr as_identifier;
    string_ptr as_string;
    string_loc_ptr as_string_loc;
    string_hash_ptr as_string_hash;
    //animref_ptr  as_animref;
    integer_ptr as_integer;
    float_ptr as_float_;
    vector_ptr as_vector;
    expr_vector_ptr as_expr_vector;
    expr_select_ptr as_expr_select;
    expr_subscribe_ptr as_expr_subscribe;
    expr_func_ref_ptr as_expr_func_ref;
    expr_arg_list_ptr as_expr_arg_list;
    expr_pointer_call_ptr as_expr_pointer_call;
    expr_func_call_ptr as_expr_func_call;
    expr_call_ptr as_expr_call;
    expr_complement_ptr as_expr_complement;
    expr_not_ptr as_expr_not;
    expr_add_ptr as_expr_add;
    expr_sub_ptr as_expr_sub;
    expr_mult_ptr as_expr_mult;
    expr_div_ptr as_expr_div;
    expr_mod_ptr as_expr_mod;
    expr_shift_left_ptr as_expr_shift_left;
    expr_shift_right_ptr as_expr_shift_right;
    expr_bw_or_ptr as_expr_bw_or;
    expr_bw_and_ptr as_expr_bw_and;
    expr_bw_xor_ptr as_expr_bw_xor;
    expr_cmp_equal_ptr as_expr_cmp_equal;
    expr_cmp_not_equal_ptr as_expr_cmp_not_equal;
    expr_cmp_less_equal_ptr as_expr_cmp_less_equal;
    expr_cmp_greater_equal_ptr as_expr_cmp_greater_equal;
    expr_cmp_less_ptr as_expr_cmp_less;
    expr_cmp_greater_ptr as_expr_cmp_greater;
    expr_cmp_or_ptr as_expr_cmp_or;
    expr_cmp_and_ptr as_expr_cmp_and;
    expr_binary_ptr as_expr_binary;
    expr_ternary_ptr as_expr_ternary;
    // EXPR ASSIGN
    expr_assign_equal_ptr as_expr_assign_equal;
    expr_assign_add_ptr as_expr_assign_add;
    expr_assign_sub_ptr as_expr_assign_sub;
    expr_assign_mult_ptr as_expr_assign_mult;
    expr_assign_div_ptr as_expr_assign_div;
    expr_assign_mod_ptr as_expr_assign_mod;
    expr_assign_shift_left_ptr as_expr_assign_shift_left;
    expr_assign_shift_right_ptr as_expr_assign_shift_right;
    expr_assign_bw_or_ptr as_expr_assign_bw_or;
    expr_assign_bw_and_ptr as_expr_assign_bw_and;
    expr_assign_bw_xor_ptr as_expr_assign_bw_xor;
    expr_inc_ptr as_expr_inc;
    expr_dec_ptr as_expr_dec;

    expr_ptr() {}
    expr_ptr (expr_ptr && val) { new(&as_node) node_ptr(std::move(val.as_node)); }
    ~expr_ptr(){}
};

struct node_stmt_call : public node
{
    expr_call_ptr expr;

    node_stmt_call(expr_call_ptr expr) : node(node_type::stmt_call), expr(std::move(expr)) {}

    auto print()->std::string override
    {
        return expr->print() + ";";
    };
};

using stmt_call_ptr = std::unique_ptr<node_stmt_call>;

struct node_stmt_assign : public node
{
    expr_assign_ptr expr;

    node_stmt_assign(expr_assign_ptr expr)
        : node(node_type::stmt_assign), expr(std::move(expr)) {}
    
    auto print()->std::string override
    {
        return expr->print() + ";";
    };
};

using stmt_assign_ptr = std::unique_ptr<node_stmt_assign>;

struct node_stmt_endon : public node
{
    node_ptr obj;
    node_ptr expr;

    node_stmt_endon(node_ptr obj, node_ptr expr) : node(node_type::stmt_endon), obj(std::move(obj)), expr(std::move(expr)) {}

    auto print() -> std::string override
    {
        return obj->print() + " endon( " + expr->print() + " );";
    };
};

using stmt_endon_ptr = std::unique_ptr<node_stmt_endon>;

struct node_stmt_notify : public node
{
    node_ptr obj;
    node_ptr expr;
    node_ptr params;

    node_stmt_notify(node_ptr obj, node_ptr expr, node_ptr params)
        : node(node_type::stmt_notify), obj(std::move(obj)), expr(std::move(expr)),
            params(std::move(params)) {}

    auto print() -> std::string override
    {
        if (params->type == node_type::null) // TODO: solve empty arg_list => ' notify("ok",) '
        {
            return obj->print() + " notify( " + expr->print() + " );"; 
        }
        else
        {
            return obj->print() + " notify( " + expr->print() + ", " + params->print() + " );";
        }
    };
};

using stmt_notify_ptr = std::unique_ptr<node_stmt_notify>;

struct node_stmt_wait : public node
{
    node_ptr expr;

    node_stmt_wait(node_ptr expr) : node(node_type::stmt_wait), expr(std::move(expr)) {}

    auto print() -> std::string override
    {
        return "wait(" + expr->print() + ");";
    };
};

using stmt_wait_ptr = std::unique_ptr<node_stmt_wait>;

struct node_stmt_waittill : public node
{
    node_ptr obj;
    node_ptr expr;
    node_ptr params;

    node_stmt_waittill(node_ptr obj, node_ptr expr, node_ptr params)
        : node(node_type::stmt_waittill), obj(std::move(obj)), expr(std::move(expr)),
            params(std::move(params)) {}

    auto print() -> std::string override
    {
        if (params->type == node_type::null)
        {
            return obj->print() + " waittill( " + expr->print() + " );";
        }
        else
        {
            return obj->print() + " waittill( " + expr->print() + ", " + params->print() + " );";
        }
    };
};

using stmt_waittill_ptr = std::unique_ptr<node_stmt_waittill>;

struct node_stmt_waittillmatch : public node
{
    node_ptr obj;
    node_ptr lexpr;
    node_ptr rexpr;

    node_stmt_waittillmatch(node_ptr obj, node_ptr lexpr, node_ptr rexpr)
        : node(node_type::stmt_waittillmatch), obj(std::move(obj)), lexpr(std::move(lexpr)),
            rexpr(std::move(rexpr)) {}

    auto print() -> std::string override
    {
        return obj->print() + " waittillmatch( " + lexpr->print() + ", " + rexpr->print() + " );";
    };
};

using stmt_waittillmatch_ptr = std::unique_ptr<node_stmt_waittillmatch>;

struct node_stmt_waittillframeend : public node
{
    node_stmt_waittillframeend() : node(node_type::stmt_waittillframeend) {}

    auto print() -> std::string override
    {
        return "waittillframeend;";
    };
};

using stmt_waittillframeend_ptr = std::unique_ptr<node_stmt_waittillframeend>;

struct node_stmt_if : public node
{
    node_ptr expr;
    node_ptr stmt;

    node_stmt_if(node_ptr expr, node_ptr stmt)
        : node(node_type::stmt_if), expr(std::move(expr)), stmt(std::move(stmt)) {}

    auto print() -> std::string override
    {
        std::string data = "if ( " + expr->print() + " )\n";

        std::string pad = indented(indent);

        if (stmt->type == node_type::stmt_block)
        {
            data +=  pad + "{\n" + stmt->print() + "\n" + pad + "}\n";
        }
        else
        {
            indent += 4;
            data += indented(indent) + stmt->print() + "\n";
            indent -= 4;
        }
        
        return data;
    };
};

using stmt_if_ptr = std::unique_ptr<node_stmt_if>;

struct node_stmt_ifelse : public node
{
    node_ptr expr;
    node_ptr stmt;
    node_ptr stmt2;

    node_stmt_ifelse(node_ptr expr, node_ptr stmt, node_ptr stmt2)
        : node(node_type::stmt_ifelse), expr(std::move(expr)), stmt(std::move(stmt)),
            stmt2(std::move(stmt2)) {}

    auto print() -> std::string override
    {
        std::string pad = indented(indent);
        std::string data = "if ( " + expr->print() + " )\n";
        
        if (stmt->type == node_type::stmt_block)
        {
            data +=  pad + "{\n" + stmt->print() + "\n" + pad + "}\n";
        }
        else
        {
            indent += 4;
            data += indented(indent) + stmt->print() + "\n";
            indent -= 4;
        }

        data += pad + "else\n";

        if (stmt2->type == node_type::stmt_block)
        {
            data +=  pad + "{\n" + stmt2->print() + "\n" + pad + "}\n";
        }
        else
        {
            indent += 4;
            data += indented(indent) + stmt2->print() + "\n";
            indent -= 4;
        }
        
        return data;
    };
};

using stmt_ifelse_ptr = std::unique_ptr<node_stmt_ifelse>;

struct node_stmt_while : public node
{
    node_ptr expr;
    node_ptr stmt;

    node_stmt_while(node_ptr expr, node_ptr stmt)
        : node(node_type::stmt_while), expr(std::move(expr)), stmt(std::move(stmt)) {}

    auto print() -> std::string override
    {
        std::string data;

        if (expr->type == node_type::null)
        {
            data += "while ( true )\n";
        }
        else
        {
            data += "while ( " + expr->print() + " )\n";
        }

        std::string pad = indented(indent);

        if (stmt->type == node_type::stmt_block)
        {
            data +=  pad + "{\n" + stmt->print() + "\n" + pad + "}\n";
        }
        else
        {
            indent += 4;
            data += indented(indent) + stmt->print() + "\n";
            indent -= 4;
        }

        return data;
    };
};

using stmt_while_ptr = std::unique_ptr<node_stmt_while>;

struct node_stmt_for : public node
{
    node_ptr stmt1;
    node_ptr expr;
    node_ptr stmt2;
    node_ptr stmt;

    node_stmt_for(node_ptr stmt1, node_ptr expr, node_ptr stmt2, node_ptr stmt)
        : node(node_type::stmt_for), stmt1(std::move(stmt1)), expr(std::move(expr)),
            stmt2(std::move(stmt2)), stmt(std::move(stmt)) {}

    auto print() -> std::string override
    {
        std::string data;

        if (expr->type == node_type::null)
        {
            data += "for ( ;; )\n";
        }
        else
        {
            data += "for ( " + stmt1->print() + "; " + expr->print() + "; " + stmt2->print() + " )\n";
        }

        std::string pad = indented(indent);

        if (stmt->type == node_type::stmt_block)
        {
            data +=  pad + "{\n" + stmt->print() + "\n" + pad + "}\n";
        }
        else
        {
            indent += 4;
            data += indented(indent) + stmt->print() + "\n";
            indent -= 4;
        }

        return data;
    };
};

using stmt_for_ptr = std::unique_ptr<node_stmt_for>;

struct node_stmt_foreach : public node
{
    node_ptr stmt1;
    node_ptr stmt2;
    node_ptr stmt;

    node_stmt_foreach(node_ptr stmt1, node_ptr stmt2, node_ptr stmt)
        : node(node_type::stmt_foreach), stmt1(std::move(stmt1)), stmt2(std::move(stmt2)), stmt(std::move(stmt)) {}

    auto print() -> std::string override
    {
        std::string data;

        data += "foreach ( " + stmt1->print() + " in " + stmt2->print() + " )\n";

        std::string pad = indented(indent);

        if (stmt->type == node_type::stmt_block)
        {
            data +=  pad + "{\n" + stmt->print() + "\n" + pad + "}\n";
        }
        else
        {
            indent += 4;
            data += indented(indent) + stmt->print() + "\n";
            indent -= 4;
        }

        return data;
    };
};

using stmt_foreach_ptr = std::unique_ptr<node_stmt_foreach>;

struct node_stmt_switch : public node
{
    node_ptr expr;
    node_ptr stmts;

    node_stmt_switch(node_ptr expr, node_ptr stmts)
        : node(node_type::stmt_switch), expr(std::move(expr)), stmts(std::move(stmts)) {}

    auto print() -> std::string override
    {
        std::string data;
        std::string pad = indented(indent);

        data += "switch ( " + expr->print() + " )\n";
        data +=  pad + "{\n" + stmts->print() + "\n" + pad + "}\n";

        return data;
    };
};

using stmt_switch_ptr = std::unique_ptr<node_stmt_switch>;

struct node_stmt_case : public node
{
    node_ptr value;

    node_stmt_case(node_ptr value) : node(node_type::stmt_case), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "case " + value->print() + ":";
    };
};

using stmt_case_ptr = std::unique_ptr<node_stmt_case>;

struct node_stmt_default : public node
{
    node_stmt_default() : node(node_type::stmt_default) {}

    auto print() -> std::string override
    {
        return "default:";
    };
};

using stmt_default_ptr = std::unique_ptr<node_stmt_default>;

struct node_stmt_break : public node
{
    node_stmt_break() : node(node_type::stmt_break) {}

    auto print() -> std::string override
    {
        return "break;";
    };
};

using stmt_break_ptr = std::unique_ptr<node_stmt_break>;

struct node_stmt_continue : public node
{
    node_stmt_continue() : node(node_type::stmt_continue) {}

    auto print() -> std::string override
    {
        return "continue;";
    };
};

using stmt_continue_ptr = std::unique_ptr<node_stmt_continue>;

struct node_stmt_return : public node
{
    node_ptr expr;

    node_stmt_return(node_ptr expr) : node(node_type::stmt_return), expr(std::move(expr)) {}

    auto print() -> std::string override
    {
        if(expr->type == node_type::null)
            return "return;";

        return "return " + expr->print() + ";";
    };
};

using stmt_return_ptr = std::unique_ptr<node_stmt_return>;

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

    stmt_ptr() {}
    stmt_ptr (stmt_ptr && val) { new(&as_node) node_ptr(std::move(val.as_node)); }
    ~stmt_ptr(){}
};

struct node_stmt_block : public node
{
    std::vector<stmt_ptr> stmts;

    node_stmt_block() : node(node_type::stmt_block) {}

    auto print() -> std::string override
    {
        std::string data;

        indent += 4;

        std::string pad = indented(indent);
        for (const auto& stmt : stmts)
        {
            if (&stmt != &stmts.front()
                && (stmt.as_node->type == node_type::stmt_if || stmt.as_node->type == node_type::stmt_ifelse
                || stmt.as_node->type == node_type::stmt_for || stmt.as_node->type == node_type::stmt_foreach
                || stmt.as_node->type == node_type::stmt_while || stmt.as_node->type == node_type::stmt_switch))
                data += "\n";
            data += pad + stmt.as_node->print();

            if (&stmt != &stmts.back())
                data += "\n";
        }

        indent -= 4;

        return data;
    }
};

using stmt_block_ptr = std::unique_ptr<node_stmt_block>;

struct node_param_list : public node
{
    std::vector<identifier_ptr> params;

    node_param_list() : node(node_type::param_list) {}

    auto print() -> std::string override
    {
        std::string data;
        
        for (const auto& param : params)
        {
            data += " " + param->print();
            data += (&param != &params.back()) ? "," : " ";
        }

        return data;
    }
};

using param_list_ptr = std::unique_ptr<node_param_list>;

struct node_function : public node
{
    identifier_ptr name;
    param_list_ptr param_list;
    stmt_block_ptr stmt_block;

    node_function(identifier_ptr name, param_list_ptr param_list, stmt_block_ptr stmt_block)
        : node(node_type::function), name(std::move(name)), param_list(std::move(param_list)),
            stmt_block(std::move(stmt_block)) {}

    auto print() -> std::string override
    {
        return name->print() + "(" + param_list->print() + ")" + "\n{\n" + stmt_block->print() + "\n}\n";
    }
};

using function_ptr = std::unique_ptr<node_function>;

struct node_animtree : public node
{
     string_ptr animtree;

    node_animtree(string_ptr animtree)
        : node(node_type::animtree), animtree(std::move(animtree)) {}

    auto print() -> std::string override
    {
        return "#animtree"s + "(" + animtree->print() + ");\n";
    }
};

using animtree_ptr = std::unique_ptr<node_animtree>;

struct node_using_animtree : public node
{
    string_ptr animtree;

    node_using_animtree(string_ptr animtree)
        : node(node_type::using_animtree), animtree(std::move(animtree)) {}

    auto print() -> std::string override
    {
        return "#using_animtree"s + "(" + animtree->print() + ");\n";
    }
};

using using_animtree_ptr = std::unique_ptr<node_using_animtree>;

struct node_include : public node
{
    filepath_ptr file;

    node_include(filepath_ptr file)
        : node(node_type::include), file(std::move(file)) {}

    auto print() -> std::string override
    {
        return "#include"s + " " + file->print() + ";\n";
    }
};

using include_ptr = std::unique_ptr<node_include>;

struct node_script : public node
{
    std::vector<include_ptr> includes;
    std::vector<using_animtree_ptr> animtrees;
    std::vector<function_ptr> functions;
    
    node_script() : node(node_type::script) {}

    auto print() -> std::string override
    {
        std::string data;

        for (const auto& include : includes)
        {
            data += include->print();
        }
        for (const auto& animtree : animtrees)
        {
            data += animtree->print();
        }
        for (const auto& function : functions)
        {
            data += "\n" + function->print();
        }

        return data;
    }
};

using script_ptr = std::unique_ptr<node_script>;

#endif // _GSC_NODETREE_H_
