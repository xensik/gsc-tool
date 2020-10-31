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
    // BASIC TYPES
    filepath,
    identifier,
    string,
    string_loc,
    string_hash,
    num_integer,
    num_float,
    vector,
    undefined,
    empty_array,
    game,
    level,
    size,
    // missing %animref
    // EXPRESSIONS
    expr_vector,
    expr_func_ref,
    expr_subscribe,
    expr_select,
    expr_arg_list,
    expr_func_call_ptr,
    expr_func_call,
    expr_call_thread,
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
    expr_ternary,
    expr_cmp_equal,
    expr_cmp_not_equal,
    expr_cmp_less_equal,
    expr_cmp_greater_equal,
    expr_cmp_less,
    expr_cmp_greater,
    expr_cmp_or,
    expr_cmp_and,
    expr_assign,
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
    stmt_for,
    stmt_foreach,
    stmt_while,
    stmt_switch,
    stmt_case,
    stmt_default,
    stmt_break,
    stmt_continue,
    stmt_return,
    stmt_block,
    // SCRIPT
    parameter_list,
    function,
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

struct node_filepath : public node
{
    std::string value;

    node_filepath(const std::string& value) : node(node_type::filepath), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

struct node_identifier : public node
{
    std::string value;

    node_identifier(const std::string& value) : node(node_type::identifier), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

struct node_string : public node
{
    std::string value;

    node_string(const std::string& value) : node(node_type::string), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

struct node_string_loc : public node
{
    std::string value;

    node_string_loc(const std::string& value) : node(node_type::string_loc), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

struct node_string_hash : public node
{
    std::string value;

    node_string_hash(const std::string& value) : node(node_type::string_hash), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

struct node_num_integer : public node
{
    std::string value;

    node_num_integer(const std::string& value) : node(node_type::num_integer), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

struct node_num_float : public node
{
    std::string value;

    node_num_float(const std::string& value) : node(node_type::string), value(std::move(value)) {}

    auto print() -> std::string override { return value; }
};

struct node_vector : public node
{
    std::unique_ptr<node> x;
    std::unique_ptr<node> y;
    std::unique_ptr<node> z;

    node_vector(std::unique_ptr<node> x, std::unique_ptr<node> y, std::unique_ptr<node> z)
        : node(node_type::vector), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}

    auto print() -> std::string override
    {
        return "( "s + x->print() + ", " + y->print() + ", "+ z->print() + " )";
    }
};

struct node_undefined : public node
{
    node_undefined() : node(node_type::undefined) {}

    auto print() -> std::string override
    {
        return "undefined";
    }
};

struct node_empty_array : public node
{
    node_empty_array() : node(node_type::empty_array) {}

    auto print() -> std::string override
    {
        return "[]";
    }
};

struct node_game : public node
{
    node_game() : node(node_type::game) {}

    auto print() -> std::string override
    {
        return "game";
    }
};

struct node_level : public node
{
    node_level() : node(node_type::level) {}

    auto print() -> std::string override
    {
        return "level";
    }
};

struct node_size : public node
{
    node_size() : node(node_type::size) {}

    auto print() -> std::string override
    {
        return "size";
    }
};

struct node_expr_vector : public node
{
    std::unique_ptr<node> x;
    std::unique_ptr<node> y;
    std::unique_ptr<node> z;

    node_expr_vector(std::unique_ptr<node> x, std::unique_ptr<node> y, std::unique_ptr<node> z)
        : node(node_type::expr_vector), x(std::move(x)), y(std::move(y)), z(std::move(z)) {}

    auto print() -> std::string override
    {
        return "( "s + x->print() + ", " + y->print() + ", "+ z->print() + " )";
    }
};

struct node_expr_func_ref : public node
{
    std::unique_ptr<node> file;
    std::unique_ptr<node> func;

    node_expr_func_ref(std::unique_ptr<node> file, std::unique_ptr<node> func)
        : node(node_type::expr_func_ref), file(std::move(file)), func(std::move(func)) {}

    auto print() -> std::string override
    {
        return file->print() + "::" + func->print();
    }
};

struct node_expr_subscribe : public node
{
    std::unique_ptr<node> obj;
    std::unique_ptr<node> key;

    node_expr_subscribe(std::unique_ptr<node> obj, std::unique_ptr<node> key)
        : node(node_type::expr_subscribe), obj(std::move(obj)), key(std::move(key)) {}

    auto print() -> std::string override
    {
        return obj->print() + "[ " + key->print() + " ]";
    }
};

struct node_expr_select : public node
{
    std::unique_ptr<node> obj;
    std::unique_ptr<node> field;

    node_expr_select(std::unique_ptr<node> obj, std::unique_ptr<node> field)
        : node(node_type::expr_select), obj(std::move(obj)), field(std::move(field)) {}

    auto print() -> std::string override
    {
        return obj->print() + "." + field->print();
    }
};

struct node_expr_arg_list : public node
{
    std::vector<std::unique_ptr<node>> args;

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
 
struct node_expr_func_call_ptr : public node
{
    std::unique_ptr<node> expr;
    std::unique_ptr<node> arg_list;

    node_expr_func_call_ptr(std::unique_ptr<node> expr, std::unique_ptr<node> arg_list)
        : node(node_type::expr_func_call_ptr), expr(std::move(expr)), arg_list(std::move(arg_list)) {}

    auto print() -> std::string override
    {
        return "[["s + expr->print() + "]](" + arg_list->print() + ")";
    }
};

struct node_expr_func_call : public node
{
    std::unique_ptr<node> file;
    std::unique_ptr<node> func;
    std::unique_ptr<node> arg_list;

    node_expr_func_call(std::unique_ptr<node> file, std::unique_ptr<node> func, std::unique_ptr<node> arg_list)
        : node(node_type::expr_func_call), file(std::move(file)), func(std::move(func)), arg_list(std::move(arg_list)) {}

    auto print() -> std::string override
    {
        if(file->type == node_type::null)
        {
            return func->print() + "(" + arg_list->print() + ")";
        }

        return file->print() + "::" + func->print() + "(" + arg_list->print() + ")";
    }
};

struct node_expr_call_thread : public node
{
    std::unique_ptr<node> obj;
    std::unique_ptr<node> call;

    node_expr_call_thread(std::unique_ptr<node> obj, std::unique_ptr<node> call)
        : node(node_type::expr_call_thread), obj(std::move(obj)), call(std::move(call)) {}

    auto print() -> std::string override
    {
        if(obj->type == node_type::null)
        {
            return "thread " + call->print();
        }

        return obj->print() + " thread " + call->print();
    }
};

struct node_expr_call : public node
{
    std::unique_ptr<node> obj;
    std::unique_ptr<node> call;

    node_expr_call(std::unique_ptr<node> obj, std::unique_ptr<node> call)
        : node(node_type::expr_call), obj(std::move(obj)), call(std::move(call)) {}

    auto print() -> std::string override
    {
        if(obj->type == node_type::null)
        {
            return call->print();
        }

        return obj->print() + " " + call->print();
    }
};

struct node_expr_complement : public node
{
    std::unique_ptr<node> rvalue;

    node_expr_complement(std::unique_ptr<node> rvalue)
        : node(node_type::expr_complement), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return "~" + rvalue->print();
    }
};

struct node_expr_not : public node
{
    std::unique_ptr<node> rvalue;

    node_expr_not(std::unique_ptr<node> rvalue)
        : node(node_type::expr_not), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return "!" + rvalue->print();
    }
};

struct node_expr_add : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_add(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_add), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " + " + rvalue->print();
    }
};

struct node_expr_sub : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_sub(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_sub), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " - " + rvalue->print();
    }
};

struct node_expr_mult : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_mult(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_mult), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " * " + rvalue->print();
    }
};

struct node_expr_div : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_div(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_div), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " / " + rvalue->print();
    }
};

struct node_expr_mod : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_mod(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_mod), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " % " + rvalue->print();
    }
};

struct node_expr_shift_left : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_shift_left(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_shift_left), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " << " + rvalue->print();
    }
};

struct node_expr_shift_right : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_shift_right(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_shift_right), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " >> " + rvalue->print();
    }
};

struct node_expr_bw_or : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_bw_or(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_bw_or), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " | " + rvalue->print();
    }
};

struct node_expr_bw_and : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_bw_and(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_bw_and), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " & " + rvalue->print();
    }
};

struct node_expr_bw_xor : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_bw_xor(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_bw_xor), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " ^ " + rvalue->print();
    }
};

struct node_expr_ternary : public node
{
    std::unique_ptr<node> cmp;
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_ternary(std::unique_ptr<node> cmp, std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_bw_xor), cmp(std::move(cmp)), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return cmp->print() + " ? " + lvalue->print() + " : " + rvalue->print();
    }
};

struct node_expr_cmp_equal : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_cmp_equal(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_cmp_equal), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " == " + rvalue->print();
    }
};

struct node_expr_cmp_not_equal : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_cmp_not_equal(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_cmp_not_equal), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " != " + rvalue->print();
    }
};

struct node_expr_cmp_less_equal : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_cmp_less_equal(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_cmp_less_equal), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " <= " + rvalue->print();
    }
};

struct node_expr_cmp_greater_equal : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_cmp_greater_equal(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_cmp_greater_equal), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " >= " + rvalue->print();
    }
};

struct node_expr_cmp_less : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_cmp_less(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_cmp_less), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " < " + rvalue->print();
    }
};

struct node_expr_cmp_greater : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_cmp_greater(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_cmp_greater), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " > " + rvalue->print();
    }
};

struct node_expr_cmp_or : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_cmp_or(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_cmp_or), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " || " + rvalue->print();
    }
};

struct node_expr_cmp_and : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_cmp_and(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_cmp_and), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " && " + rvalue->print();
    }
};

struct node_expr_assign : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue) : node(node_type::expr_assign), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " = " + rvalue->print() ;
    };
};

struct node_expr_assign_add : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_add(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue) : node(node_type::expr_assign_add), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " += " + rvalue->print() ;
    };
};

struct node_expr_assign_sub : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_sub(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue) : node(node_type::expr_assign_sub), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " -= " + rvalue->print() ;
    };
};

struct node_expr_assign_mult : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_mult(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue) : node(node_type::expr_assign_mult), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " *= " + rvalue->print() ;
    };
};

struct node_expr_assign_div : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_div(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue) : node(node_type::expr_assign_div), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " /= " + rvalue->print() ;
    };
};

struct node_expr_assign_mod : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_mod(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue) : node(node_type::expr_assign_mod), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " %= " + rvalue->print() ;
    };
};

struct node_expr_assign_shift_left : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_shift_left(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_assign_shift_left), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " <<= " + rvalue->print() ;
    };
};

struct node_expr_assign_shift_right : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_shift_right(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_assign_shift_right), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " >>= " + rvalue->print() ;
    };
};

struct node_expr_assign_bw_or : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_bw_or(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_assign_bw_or), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " |= " + rvalue->print();
    }
};

struct node_expr_assign_bw_and : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_bw_and(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_assign_bw_and), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " &= " + rvalue->print();
    }
};

struct node_expr_assign_bw_xor : public node
{
    std::unique_ptr<node> lvalue;
    std::unique_ptr<node> rvalue;

    node_expr_assign_bw_xor(std::unique_ptr<node> lvalue, std::unique_ptr<node> rvalue)
        : node(node_type::expr_assign_bw_xor), lvalue(std::move(lvalue)), rvalue(std::move(rvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " ^= " + rvalue->print();
    }
};

struct node_expr_inc : public node
{
    std::unique_ptr<node> lvalue;

    node_expr_inc(std::unique_ptr<node> lvalue)
        : node(node_type::expr_inc), lvalue(std::move(lvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + "++";
    }
};

struct node_expr_dec : public node
{
    std::unique_ptr<node> lvalue;

    node_expr_dec(std::unique_ptr<node> lvalue)
        : node(node_type::expr_inc), lvalue(std::move(lvalue)) {}

    auto print() -> std::string override
    {
        return lvalue->print() + "--";
    }
};

struct node_stmt_call : public node
{
    std::unique_ptr<node> expr;

    node_stmt_call(std::unique_ptr<node> expr) : node(node_type::stmt_call), expr(std::move(expr)) {}

    auto print()->std::string override
    {
        return expr->print() + ";";
    };
};

struct node_stmt_assign : public node
{
    std::unique_ptr<node> expr;

    node_stmt_assign(std::unique_ptr<node> expr) : node(node_type::stmt_assign), expr(std::move(expr)) {}
    
    auto print()->std::string override
    {
        return expr->print() + ";";
    };
};

struct node_stmt_endon : public node
{
    std::unique_ptr<node> obj;
    std::unique_ptr<node> expr;

    node_stmt_endon(std::unique_ptr<node> obj, std::unique_ptr<node> expr) : node(node_type::stmt_endon), obj(std::move(obj)), expr(std::move(expr)) {}

    auto print() -> std::string override
    {
        return obj->print() + " endon( " + expr->print() + " );";
    };
};

struct node_stmt_notify : public node
{
    std::unique_ptr<node> obj;
    std::unique_ptr<node> expr;
    std::unique_ptr<node> params;

    node_stmt_notify(std::unique_ptr<node> obj, std::unique_ptr<node> expr, std::unique_ptr<node> params)
        : node(node_type::stmt_notify), obj(std::move(obj)), expr(std::move(expr)), params(std::move(params)) {}

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

struct node_stmt_wait : public node
{
    std::unique_ptr<node> expr;

    node_stmt_wait(std::unique_ptr<node> expr) : node(node_type::stmt_wait), expr(std::move(expr)) {}

    auto print() -> std::string override
    {
        return "wait(" + expr->print() + ");";
    };
};

struct node_stmt_waittill : public node
{
    std::unique_ptr<node> obj;
    std::unique_ptr<node> expr;
    std::unique_ptr<node> params;

    node_stmt_waittill(std::unique_ptr<node> obj, std::unique_ptr<node> expr, std::unique_ptr<node> params)
        : node(node_type::stmt_waittill), obj(std::move(obj)), expr(std::move(expr)), params(std::move(params)) {}

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

struct node_stmt_waittillmatch : public node
{
    std::unique_ptr<node> obj;
    std::unique_ptr<node> lexpr;
    std::unique_ptr<node> rexpr;

    node_stmt_waittillmatch(std::unique_ptr<node> obj, std::unique_ptr<node> lexpr, std::unique_ptr<node> rexpr)
        : node(node_type::stmt_waittillmatch), obj(std::move(obj)), lexpr(std::move(lexpr)), rexpr(std::move(rexpr)) {}

    auto print() -> std::string override
    {
        return obj->print() + " waittillmatch( " + lexpr->print() + ", " + rexpr->print() + " );";
    };
};

struct node_stmt_waittillframeend : public node
{
    node_stmt_waittillframeend() : node(node_type::stmt_waittillframeend) {}

    auto print() -> std::string override
    {
        return "waittillframeend;";
    };
};

struct node_stmt_if : public node
{
    std::unique_ptr<node> expr;
    std::unique_ptr<node> stmt;

    node_stmt_if(std::unique_ptr<node> expr, std::unique_ptr<node> stmt) : node(node_type::stmt_if), expr(std::move(expr)), stmt(std::move(stmt)) {}

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

struct node_stmt_ifelse : public node
{
    std::unique_ptr<node> expr;
    std::unique_ptr<node> stmt;
    std::unique_ptr<node> stmt2;

    node_stmt_ifelse(std::unique_ptr<node> expr, std::unique_ptr<node> stmt, std::unique_ptr<node> stmt2)
        : node(node_type::stmt_ifelse), expr(std::move(expr)), stmt(std::move(stmt)), stmt2(std::move(stmt2)) {}

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

struct node_stmt_while : public node
{
    std::unique_ptr<node> expr;
    std::unique_ptr<node> stmt;

    node_stmt_while(std::unique_ptr<node> expr, std::unique_ptr<node> stmt)
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

struct node_stmt_for : public node
{
    std::unique_ptr<node> stmt1;
    std::unique_ptr<node> expr;
    std::unique_ptr<node> stmt2;
    std::unique_ptr<node> stmt;

    node_stmt_for(std::unique_ptr<node> stmt1, std::unique_ptr<node> expr, std::unique_ptr<node> stmt2, std::unique_ptr<node> stmt)
        : node(node_type::stmt_for), stmt1(std::move(stmt1)), expr(std::move(expr)), stmt2(std::move(stmt2)), stmt(std::move(stmt)) {}

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

struct node_stmt_foreach : public node
{
    std::unique_ptr<node> stmt1;
    std::unique_ptr<node> stmt2;
    std::unique_ptr<node> stmt;

    node_stmt_foreach(std::unique_ptr<node> stmt1, std::unique_ptr<node> stmt2, std::unique_ptr<node> stmt)
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

struct node_stmt_switch : public node
{
    std::unique_ptr<node> expr;
    std::unique_ptr<node> stmt;

    node_stmt_switch(std::unique_ptr<node> expr, std::unique_ptr<node> stmt)
        : node(node_type::stmt_switch), expr(std::move(expr)), stmt(std::move(stmt)) {}

    auto print() -> std::string override
    {
        std::string data;
        std::string pad = indented(indent);

        data += "switch ( " + expr->print() + " )\n";
        data +=  pad + "{\n" + stmt->print() + "\n" + pad + "}\n";

        return data;
    };
};
struct node_stmt_case : public node
{
    std::unique_ptr<node> value;

    node_stmt_case(std::unique_ptr<node> value) : node(node_type::stmt_case), value(std::move(value)) {}

    auto print() -> std::string override
    {
        return "case " + value->print() + ":";
    };
};

struct node_stmt_default : public node
{
    node_stmt_default() : node(node_type::stmt_default) {}

    auto print() -> std::string override
    {
        return "default:";
    };
};

struct node_stmt_break : public node
{
    node_stmt_break() : node(node_type::stmt_break) {}

    auto print() -> std::string override
    {
        return "break;";
    };
};

struct node_stmt_continue : public node
{
    node_stmt_continue() : node(node_type::stmt_continue) {}

    auto print() -> std::string override
    {
        return "continue;";
    };
};

struct node_stmt_return : public node
{
    std::unique_ptr<node> expr;

    node_stmt_return(std::unique_ptr<node> expr) : node(node_type::stmt_return), expr(std::move(expr)) {}

    auto print() -> std::string override
    {
        if(expr->type == node_type::null)
            return "return;";

        return "return " + expr->print() + ";";
    };
};

struct node_stmt_block : public node
{
    std::vector<std::unique_ptr<node>> stmts;

    node_stmt_block() : node(node_type::stmt_block) {}

    auto print() -> std::string override
    {
        std::string data;

        indent += 4;

        std::string pad = indented(indent);
        for (const auto& stmt : stmts)
        {
            if (&stmt != &stmts.front()
                && (stmt->type == node_type::stmt_if || stmt->type == node_type::stmt_ifelse
                || stmt->type == node_type::stmt_for || stmt->type == node_type::stmt_foreach
                || stmt->type == node_type::stmt_while || stmt->type == node_type::stmt_switch))
                data += "\n";
            data += pad + stmt->print();

            if (&stmt != &stmts.back())
                data += "\n";
        }

        indent -= 4;

        return data;
    }
};

struct node_parameter_list : public node
{
    std::vector<std::unique_ptr<node>> params;

    node_parameter_list() : node(node_type::parameter_list) {}

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

struct node_function : public node
{
    std::unique_ptr<node> name;
    std::unique_ptr<node> params;
    std::unique_ptr<node> stmts;

    node_function(std::unique_ptr<node> name, std::unique_ptr<node> params, std::unique_ptr<node> stmts)
        : node(node_type::function), name(std::move(name)), params(std::move(params)), stmts(std::move(stmts)) {}

    auto print() -> std::string override
    {
        return name->print() + "(" + params->print() + ")" + "\n{\n" + stmts->print() + "\n}\n";
    }
};

struct node_using_animtree : public node
{
    std::unique_ptr<node> child;

    node_using_animtree(std::unique_ptr<node> child)
        : node(node_type::using_animtree), child(std::move(child)) {}

    auto print() -> std::string override
    {
        return "#using_animtree"s + "(" + child->print() + ");\n";
    }
};

struct node_include : public node
{
    std::unique_ptr<node> child;

    node_include(std::unique_ptr<node> child)
        : node(node_type::include), child(std::move(child)) {}

    auto print() -> std::string override
    {
        return "#include"s + " " + child->print() + ";\n";
    }
};

struct node_script : public node
{
    std::vector<std::unique_ptr<node>> childs;
    
    node_script() : node(node_type::script) {}

    auto print() -> std::string override
    {
        std::string data;
        for (const auto& child : childs)
        {
            if(child->type == node_type::function)
            {
                data += "\n";
            }

            data += child->print();
        }

        return data;
    }
};

#endif // _GSC_NODETREE_H_
