// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.
#pragma once


std::string indented(std::uint32_t indent);

enum class node_type
{
    null,
    literal, // abstract node!
    literal_path,
    literal_identifier,
    literal_string,
    literal_istring,
    literal_float,
    literal_integer,
    literal_vector,
    literal_undefined,
    literal_emptyarray,
    expression, // abstract node!

    // primitive expressions
    expression_variable,
    // eval_local_var
    // eval_local_var_cached
    // variable_array
    
    

    expression_binary_or,
    expression_binary_exor,
    expression_binary_and,
    expression_binary_equality,
    expression_binary_inequality,
    expression_binary_less,
    expression_binary_greater,
    expression_binary_equal,
    expression_binary_less_equal,
    expression_binary_greater_equal,
    expression_binary_shift_left,
    expression_binary_shift_right,
    expression_binary_plus,
    expression_binary_minus,
    expression_binary_multiply,
    expression_binary_divide,
    expression_binary_mod,


    expression_call, // abstract node!
    expression_call_function,
    expression_call_method,
    expression_call_function_pointer,
    expression_call_method_pointer,
    expression_call_function_thread,
    expression_call_method_thread,
    expression_call_function_thread_pointer,
    expression_call_method_thread_pointer,

    expression_variable_ref, // used on assignment
    expression_variable_local_ref,
    expression_variable_array_ref,
    expression_variable_field_ref,

    argument_list,
    statement, // abstract node!
    statement_assign,
    statement_call,
    statement_return,
    statement_wait,
    statement_waittill,
    statement_waittillmatch,
    statement_waittillframeend,
    statement_notify,
    statement_endon,
    statement_if,
    statement_ifelse,
    statement_for,
    statement_foreach,
    statement_while,
    statement_switch,
    statement_switch_list,
    statement_break,
    statement_continue,
    statement_block,
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
};

struct node_literal : public node
{
    std::string value;

    node_literal(node_type type, const std::string& value) : node(type), value(value) {}

    auto print() -> std::string override { return value; }
};

struct node_string : public node_literal
{
    node_string(const std::string& value) : node_literal(node_type::literal_string, value) {}
};

struct node_filepath : public node_literal
{
    node_filepath(const std::string& value) : node_literal(node_type::literal_path, value) {}
};

struct node_identifier : public node_literal
{
    node_identifier(const std::string& value) : node_literal(node_type::literal_identifier, value) {}
};

struct node_float : public node_literal
{
    node_float(const std::string& value) : node_literal(node_type::literal_float, value) {}
};

struct node_integer : public node_literal
{
    node_integer(const std::string& value) : node_literal(node_type::literal_integer, value) {}
};


struct node_argument_list : public node
{
    std::vector<node*> args;

    node_argument_list(const std::vector<node*>& args) : node(node_type::argument_list), args(args) {}

    auto print() -> std::string override
    {
        std::string data;

        for (const auto& arg : args)
        {
            data += arg->print();
            if (&arg != &args.back()) data += ", ";
        }

        return data;
    }
};

struct node_statement_assign : public node
{
    node* lvalue;
    node* rvalue;

    node_statement_assign(node* lvalue, node* rvalue) : node(node_type::statement_assign), lvalue(lvalue), rvalue(rvalue) {}
    
    auto print()->std::string override
    {
        return lvalue->print() + " = " + rvalue->print() + ";";
    };
};

struct node_statement_call : public node
{
    node* expr;

    node_statement_call(node* expr) : node(node_type::statement_call), expr(expr) {}

    auto print()->std::string override
    {
        return expr->print() + ";";
    };
};

struct node_statement_return : public node
{
    node* expr;

    node_statement_return(node* expr) : node(node_type::statement_return), expr(expr) {}

    auto print() -> std::string override
    {
        return "return " + expr->print() + ";";
    };
};

struct node_statement_wait : public node
{
    node* expr;

    node_statement_wait(node* expr) : node(node_type::statement_wait), expr(expr) {}

    auto print() -> std::string override
    {
        return "wait(" + expr->print() + ");";
    };
};

struct node_statement_waittill : public node
{
    node* obj;
    node* expr;
    node* params;

    node_statement_waittill(node* obj, node* expr, node* params)
        : node(node_type::statement_waittill), obj(obj), expr(expr), params(params) {}

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

struct node_statement_waittillmatch : public node
{
    node* obj;
    node* lexpr;
    node* rexpr;

    node_statement_waittillmatch(node* obj, node* lexpr, node* rexpr)
        : node(node_type::statement_waittillmatch), obj(obj), lexpr(lexpr), rexpr(rexpr) {}

    auto print() -> std::string override
    {
        return obj->print() + " waittillmatch( " + lexpr->print() + ", " + rexpr->print() + " );";
    };
};

struct node_statement_waittillframeend : public node
{
    node_statement_waittillframeend() : node(node_type::statement_waittillframeend) {}

    auto print() -> std::string override
    {
        return "waittillframeend;";
    };
};

struct node_statement_notify : public node
{
    node* obj;
    node* expr;
    node* params;

    node_statement_notify(node* obj, node* expr, node* params)
        : node(node_type::statement_notify), obj(obj), expr(expr), params(params) {}

    auto print() -> std::string override
    {
        if (params->type == node_type::null)
        {
            return obj->print() + " notify( " + expr->print() + " );"; 
        }
        else
        {
            return obj->print() + " notify( " + expr->print() + ", " + params->print() + " );";
        }
    };
};

struct node_statement_endon : public node
{
    node* obj;
    node* expr;

    node_statement_endon(node* obj, node* expr) : node(node_type::statement_endon), obj(obj), expr(expr) {}

    auto print() -> std::string override
    {
        return obj->print() + " endon( " + expr->print() + " );";
    };
};

struct node_statement_if : public node
{
    node* expr;
    node* stmt;

    node_statement_if(node* expr, node* stmt) : node(node_type::statement_if), expr(expr), stmt(stmt) {}

    auto print() -> std::string override
    {
        return "if ( " + expr->print() + " )\n{\n" + stmt->print() + "\n}\n";
    };
};

struct node_statement_ifelse : public node
{
    node* expr;
    node* stmt;
    node* stmt2;

    node_statement_ifelse(node* expr, node* stmt, node* stmt2)
        : node(node_type::statement_ifelse), expr(expr), stmt(stmt), stmt2(stmt2) {}

    auto print() -> std::string override
    {
        return "if ( " + expr->print() + " )\n{\n" + stmt->print() + "\n}\nelse\n{\n" + stmt2->print() + "\n}\n";
    };
};

struct node_statement_for : public node
{
    node* stmt1;
    node* expr;
    node* stmt2;
    node* stmt;

    node_statement_for(node* stmt1, node* expr, node* stmt2, node* stmt)
        : node(node_type::statement_for), stmt1(stmt1), expr(expr), stmt2(stmt2), stmt(stmt) {}

    auto print() -> std::string override
    {
        if (expr->type == node_type::null)
        {
            return "for ( ;; )\n{\n" + stmt->print() + "\n}\n";
        }
        else
        {
            return "for ( " + stmt1->print() + ";" + expr->print() + ";" + stmt2->print() + " )\n{\n" + stmt->print() + "\n}\n";
        }
    };
};

struct node_statement_foreach : public node
{
    node* stmt1;
    node* stmt2;
    node* stmt;

    node_statement_foreach(node* stmt1, node* stmt2, node* stmt)
        : node(node_type::statement_foreach), stmt1(stmt1), stmt2(stmt2), stmt(stmt) {}

    auto print() -> std::string override
    {
        return "foreach ( " + stmt1->print() + " in " + stmt2->print() + " )\n{\n" + stmt->print() + "\n}\n";

    };
};

struct node_statement_while : public node
{
    node* expr;
    node* stmt;

    node_statement_while(node* expr, node* stmt)
        : node(node_type::statement_while), expr(expr), stmt(stmt) {}

    auto print() -> std::string override
    {
        if (expr->type == node_type::null)
        {
            return "while ( 1 )\n{\n" + stmt->print() + "\n}\n";
        }
        else
        {
            return "while ( " + expr->print() + " )\n{\n" + stmt->print() + "\n}\n";
        }
    };
};


/*
    statement_switch,
    statement_switch_list,
    statement_break,
    statement_continue,
*/

struct node_statement_block : public node
{
    std::vector<node*> stmts;

    node_statement_block() : node(node_type::statement_block) {}

    auto print() -> std::string override
    {
        std::string data;

        indent += 4;

        std::string pad = indented(indent);
        for (const auto& stmt : stmts)
        {
            data += pad + stmt->print();

            if (&stmt != &stmts.back())
                data += "\n";
        }

        indent -= 4;

        return data;
    }

    static void reset_indentation() { indent = 0; }

protected:
   static std::uint32_t indent;
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