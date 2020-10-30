// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.
#pragma once


std::string indented(std::uint32_t indent);

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
    //
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
    stmt_switch_list,
    stmt_break,
    stmt_continue,
    stmt_return,

    stmt_block,
    parameter_list,
    function,
    using_animtree,
    include,
    script,

    // decompiler
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
    virtual auto print() -> std::string { return ""; };
     
protected:
    static std::uint32_t indent;
    static void reset_indentation() { indent = 0; }
};

struct node_filepath : public node
{
    std::string value;

    node_filepath(const std::string& value) : node(node_type::filepath), value(value) {}

    auto print() -> std::string override { return value; }
};

struct node_identifier : public node
{
    std::string value;

    node_identifier(const std::string& value) : node(node_type::identifier), value(value) {}

    auto print() -> std::string override { return value; }
};

struct node_string : public node
{
    std::string value;

    node_string(const std::string& value) : node(node_type::string), value(value) {}

    auto print() -> std::string override { return value; }
};

struct node_string_loc : public node
{
    std::string value;

    node_string_loc(const std::string& value) : node(node_type::string_loc), value(value) {}

    auto print() -> std::string override { return value; }
};

struct node_string_hash : public node
{
    std::string value;

    node_string_hash(const std::string& value) : node(node_type::string_hash), value(value) {}

    auto print() -> std::string override { return value; }
};

struct node_num_integer : public node
{
    std::string value;

    node_num_integer(const std::string& value) : node(node_type::num_integer), value(value) {}

    auto print() -> std::string override { return value; }
};

struct node_num_float : public node
{
    std::string value;

    node_num_float(const std::string& value) : node(node_type::string), value(value) {}

    auto print() -> std::string override { return value; }
};

struct node_vector : public node
{
    node* x;
    node* y;
    node* z;

    node_vector(node* x, node* y, node* z) : node(node_type::vector), x(x), y(y), z(z) {}

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
    node* x;
    node* y;
    node* z;

    node_expr_vector(node* x, node* y, node* z) : node(node_type::expr_vector), x(x), y(y), z(z) {}

    auto print() -> std::string override
    {
        return "( "s + x->print() + ", " + y->print() + ", "+ z->print() + " )";
    }
};

struct node_expr_func_ref : public node
{
    node* file;
    node* func;

    node_expr_func_ref(node* file, node* func)
        : node(node_type::expr_func_ref), file(file), func(func) {}

    auto print() -> std::string override
    {
        return file->print() + "::" + func->print();
    }
};

struct node_expr_subscribe : public node
{
    node* obj;
    node* key;

    node_expr_subscribe(node* obj, node* key)
        : node(node_type::expr_subscribe), obj(obj), key(key) {}

    auto print() -> std::string override
    {
        return obj->print() + "[ " + key->print() + " ]";
    }
};

struct node_expr_select : public node
{
    node* obj;
    node* field;

    node_expr_select(node* obj, node* field)
        : node(node_type::expr_select), obj(obj), field(field) {}

    auto print() -> std::string override
    {
        return obj->print() + "." + field->print();
    }
};

struct node_expr_arg_list : public node
{
    std::vector<node*> args;

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
    node* expr;
    node* arg_list;

    node_expr_func_call_ptr(node* expr, node* arg_list)
        : node(node_type::expr_func_call_ptr), expr(expr), arg_list(arg_list) {}

    auto print() -> std::string override
    {
        return "[["s + expr->print() + "]](" + arg_list->print() + ")";
    }
};

struct node_expr_func_call : public node
{
    node* file;
    node* func;
    node* arg_list;

    node_expr_func_call(node* file, node* func, node* arg_list)
        : node(node_type::expr_func_call), file(file), func(func), arg_list(arg_list) {}

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
    node* obj;
    node* call;

    node_expr_call_thread(node* obj, node* call)
        : node(node_type::expr_call_thread), obj(obj), call(call) {}

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
    node* obj;
    node* call;

    node_expr_call(node* obj, node* call)
        : node(node_type::expr_call), obj(obj), call(call) {}

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
    node* rvalue;

    node_expr_complement(node* rvalue)
        : node(node_type::expr_complement), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return "~" + rvalue->print();
    }
};

struct node_expr_not : public node
{
    node* rvalue;

    node_expr_not(node* rvalue)
        : node(node_type::expr_not), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return "!" + rvalue->print();
    }
};

struct node_expr_add : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_add(node* lvalue, node* rvalue)
        : node(node_type::expr_add), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " + " + rvalue->print();
    }
};

struct node_expr_sub : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_sub(node* lvalue, node* rvalue)
        : node(node_type::expr_sub), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " - " + rvalue->print();
    }
};

struct node_expr_mult : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_mult(node* lvalue, node* rvalue)
        : node(node_type::expr_mult), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " * " + rvalue->print();
    }
};

struct node_expr_div : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_div(node* lvalue, node* rvalue)
        : node(node_type::expr_div), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " / " + rvalue->print();
    }
};

struct node_expr_mod : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_mod(node* lvalue, node* rvalue)
        : node(node_type::expr_mod), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " % " + rvalue->print();
    }
};

struct node_expr_shift_left : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_shift_left(node* lvalue, node* rvalue)
        : node(node_type::expr_shift_left), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " << " + rvalue->print();
    }
};

struct node_expr_shift_right : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_shift_right(node* lvalue, node* rvalue)
        : node(node_type::expr_shift_right), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " >> " + rvalue->print();
    }
};

struct node_expr_bw_or : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_bw_or(node* lvalue, node* rvalue)
        : node(node_type::expr_bw_or), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " | " + rvalue->print();
    }
};

struct node_expr_bw_and : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_bw_and(node* lvalue, node* rvalue)
        : node(node_type::expr_bw_and), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " & " + rvalue->print();
    }
};

struct node_expr_bw_xor : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_bw_xor(node* lvalue, node* rvalue)
        : node(node_type::expr_bw_xor), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " ^ " + rvalue->print();
    }
};

struct node_expr_ternary : public node
{
    node* cmp;
    node* lvalue;
    node* rvalue;

    node_expr_ternary(node* cmp, node* lvalue, node* rvalue)
        : node(node_type::expr_bw_xor), cmp(cmp), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return cmp->print() + " ? " + lvalue->print() + " : " + rvalue->print();
    }
};

struct node_expr_cmp_equal : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_cmp_equal(node* lvalue, node* rvalue)
        : node(node_type::expr_cmp_equal), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " == " + rvalue->print();
    }
};

struct node_expr_cmp_not_equal : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_cmp_not_equal(node* lvalue, node* rvalue)
        : node(node_type::expr_cmp_not_equal), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " != " + rvalue->print();
    }
};

struct node_expr_cmp_less_equal : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_cmp_less_equal(node* lvalue, node* rvalue)
        : node(node_type::expr_cmp_less_equal), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " <= " + rvalue->print();
    }
};

struct node_expr_cmp_greater_equal : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_cmp_greater_equal(node* lvalue, node* rvalue)
        : node(node_type::expr_cmp_greater_equal), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " >= " + rvalue->print();
    }
};

struct node_expr_cmp_less : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_cmp_less(node* lvalue, node* rvalue)
        : node(node_type::expr_cmp_less), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " < " + rvalue->print();
    }
};

struct node_expr_cmp_greater : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_cmp_greater(node* lvalue, node* rvalue)
        : node(node_type::expr_cmp_greater), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " > " + rvalue->print();
    }
};

struct node_expr_cmp_or : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_cmp_or(node* lvalue, node* rvalue)
        : node(node_type::expr_cmp_or), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " || " + rvalue->print();
    }
};

struct node_expr_cmp_and : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_cmp_and(node* lvalue, node* rvalue)
        : node(node_type::expr_cmp_and), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " && " + rvalue->print();
    }
};

struct node_expr_assign : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign(node* lvalue, node* rvalue) : node(node_type::expr_assign), lvalue(lvalue), rvalue(rvalue) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " = " + rvalue->print() ;
    };
};

struct node_expr_assign_add : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_add(node* lvalue, node* rvalue) : node(node_type::expr_assign_add), lvalue(lvalue), rvalue(rvalue) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " += " + rvalue->print() ;
    };
};

struct node_expr_assign_sub : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_sub(node* lvalue, node* rvalue) : node(node_type::expr_assign_sub), lvalue(lvalue), rvalue(rvalue) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " -= " + rvalue->print() ;
    };
};

struct node_expr_assign_mult : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_mult(node* lvalue, node* rvalue) : node(node_type::expr_assign_mult), lvalue(lvalue), rvalue(rvalue) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " *= " + rvalue->print() ;
    };
};

struct node_expr_assign_div : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_div(node* lvalue, node* rvalue) : node(node_type::expr_assign_div), lvalue(lvalue), rvalue(rvalue) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " /= " + rvalue->print() ;
    };
};

struct node_expr_assign_mod : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_mod(node* lvalue, node* rvalue) : node(node_type::expr_assign_mod), lvalue(lvalue), rvalue(rvalue) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " %= " + rvalue->print() ;
    };
};

struct node_expr_assign_shift_left : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_shift_left(node* lvalue, node* rvalue)
        : node(node_type::expr_assign_shift_left), lvalue(lvalue), rvalue(rvalue) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " <<= " + rvalue->print() ;
    };
};

struct node_expr_assign_shift_right : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_shift_right(node* lvalue, node* rvalue)
        : node(node_type::expr_assign_shift_right), lvalue(lvalue), rvalue(rvalue) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " >>= " + rvalue->print() ;
    };
};

struct node_expr_assign_bw_or : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_bw_or(node* lvalue, node* rvalue)
        : node(node_type::expr_assign_bw_or), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " |= " + rvalue->print();
    }
};

struct node_expr_assign_bw_and : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_bw_and(node* lvalue, node* rvalue)
        : node(node_type::expr_assign_bw_and), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " &= " + rvalue->print();
    }
};

struct node_expr_assign_bw_xor : public node
{
    node* lvalue;
    node* rvalue;

    node_expr_assign_bw_xor(node* lvalue, node* rvalue)
        : node(node_type::expr_assign_bw_xor), lvalue(lvalue), rvalue(rvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + " ^= " + rvalue->print();
    }
};

struct node_expr_inc : public node
{
    node* lvalue;

    node_expr_inc(node* lvalue)
        : node(node_type::expr_inc), lvalue(lvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + "++";
    }
};

struct node_expr_dec : public node
{
    node* lvalue;

    node_expr_dec(node* lvalue)
        : node(node_type::expr_inc), lvalue(lvalue) {}

    auto print() -> std::string override
    {
        return lvalue->print() + "--";
    }
};

struct node_stmt_call : public node
{
    node* expr;

    node_stmt_call(node* expr) : node(node_type::stmt_call), expr(expr) {}

    auto print()->std::string override
    {
        return expr->print() + ";";
    };
};

struct node_stmt_assign : public node
{
    node* expr;

    node_stmt_assign(node* expr) : node(node_type::stmt_assign), expr(expr) {}
    
    auto print()->std::string override
    {
        return expr->print() + ";";
    };
};

struct node_stmt_endon : public node
{
    node* obj;
    node* expr;

    node_stmt_endon(node* obj, node* expr) : node(node_type::stmt_endon), obj(obj), expr(expr) {}

    auto print() -> std::string override
    {
        return obj->print() + " endon( " + expr->print() + " );";
    };
};

struct node_stmt_notify : public node
{
    node* obj;
    node* expr;
    node* params;

    node_stmt_notify(node* obj, node* expr, node* params)
        : node(node_type::stmt_notify), obj(obj), expr(expr), params(params) {}

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
    node* expr;

    node_stmt_wait(node* expr) : node(node_type::stmt_wait), expr(expr) {}

    auto print() -> std::string override
    {
        return "wait(" + expr->print() + ");";
    };
};

struct node_stmt_waittill : public node
{
    node* obj;
    node* expr;
    node* params;

    node_stmt_waittill(node* obj, node* expr, node* params)
        : node(node_type::stmt_waittill), obj(obj), expr(expr), params(params) {}

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
    node* obj;
    node* lexpr;
    node* rexpr;

    node_stmt_waittillmatch(node* obj, node* lexpr, node* rexpr)
        : node(node_type::stmt_waittillmatch), obj(obj), lexpr(lexpr), rexpr(rexpr) {}

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
    node* expr;
    node* stmt;

    node_stmt_if(node* expr, node* stmt) : node(node_type::stmt_if), expr(expr), stmt(stmt) {}

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
    node* expr;
    node* stmt;
    node* stmt2;

    node_stmt_ifelse(node* expr, node* stmt, node* stmt2)
        : node(node_type::stmt_ifelse), expr(expr), stmt(stmt), stmt2(stmt2) {}

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
    node* expr;
    node* stmt;

    node_stmt_while(node* expr, node* stmt)
        : node(node_type::stmt_while), expr(expr), stmt(stmt) {}

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
    node* stmt1;
    node* expr;
    node* stmt2;
    node* stmt;

    node_stmt_for(node* stmt1, node* expr, node* stmt2, node* stmt)
        : node(node_type::stmt_for), stmt1(stmt1), expr(expr), stmt2(stmt2), stmt(stmt) {}

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
    node* stmt1;
    node* stmt2;
    node* stmt;

    node_stmt_foreach(node* stmt1, node* stmt2, node* stmt)
        : node(node_type::stmt_foreach), stmt1(stmt1), stmt2(stmt2), stmt(stmt) {}

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

/*
    stmt_switch,
    stmt_switch_list,
    case,
    default,
*/

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
    node* expr;

    node_stmt_return(node* expr) : node(node_type::stmt_return), expr(expr) {}

    auto print() -> std::string override
    {
        if(expr->type == node_type::null)
            return "return;";

        return "return " + expr->print() + ";";
    };
};

struct node_stmt_block : public node
{
    std::vector<node*> stmts;

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
    std::vector<node*> params;

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
    node* name;
    node* params;
    node* stmts;

    node_function(node* name, node* params, node* stmts)
        : node(node_type::function), name(name), params(params), stmts(stmts) {}

    auto print() -> std::string override
    {
        return name->print() + "(" + params->print() + ")" + "\n{\n" + stmts->print() + "\n}\n";
    }
};

struct node_using_animtree : public node
{
    node* child;

    node_using_animtree(node* child) : node(node_type::using_animtree), child(child) {}

    auto print() -> std::string override
    {
        return "#using_animtree"s + "(" + child->print() + ");\n";
    }
};

struct node_include : public node
{
    node* child;

    node_include(node* child) : node(node_type::include), child(child) {}

    auto print() -> std::string override
    {
        return "#include"s + " " + child->print() + ";\n";
    }
};

struct node_script : public node
{
    std::vector<node*> childs;
    
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