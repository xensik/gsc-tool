// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::ast
{

enum class kind
{
    null,
    expr_true,
    expr_false,
    expr_integer,
    expr_float,
    expr_vector,
    expr_string,
    expr_istring,
    expr_path,
    expr_identifier,
    expr_animtree,
    expr_animation,
    expr_level,
    expr_anim,
    expr_self,
    expr_game,
    expr_undefined,
    expr_empty_array,
    expr_thisthread,
    expr_paren,
    expr_size,
    expr_field,
    expr_array,
    expr_tuple,
    expr_reference,
    expr_istrue,
    expr_isdefined,
    expr_arguments,
    expr_parameters,
    expr_add_array,
    expr_pointer,
    expr_function,
    expr_method,
    expr_call,
    expr_complement,
    expr_negate,
    expr_not,
    expr_add,
    expr_sub,
    expr_mul,
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
    expr_increment,
    expr_decrement,
    expr_assign_equal,
    expr_assign_add,
    expr_assign_sub,
    expr_assign_mul,
    expr_assign_div,
    expr_assign_mod,
    expr_assign_shift_left,
    expr_assign_shift_right,
    expr_assign_bitwise_or,
    expr_assign_bitwise_and,
    expr_assign_bitwise_exor,
    stmt_list,
    stmt_dev,
    stmt_expr,
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
    stmt_dowhile,
    stmt_for,
    stmt_foreach,
    stmt_switch,
    stmt_case,
    stmt_default,
    stmt_break,
    stmt_continue,
    stmt_return,
    stmt_breakpoint,
    stmt_prof_begin,
    stmt_prof_end,
    decl_thread,
    decl_constant,
    decl_usingtree,
    decl_dev_begin,
    decl_dev_end,
    include,
    program,
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
    asm_create,
    asm_access,
    asm_remove,
    asm_clear,
};

struct node;
struct expr_true;
struct expr_false;
struct expr_integer;
struct expr_float;
struct expr_vector;
struct expr_string;
struct expr_istring;
struct expr_path;
struct expr_identifier;
struct expr_animtree;
struct expr_animation;
struct expr_level;
struct expr_anim;
struct expr_self;
struct expr_game;
struct expr_undefined;
struct expr_empty_array;
struct expr_thisthread;
struct expr_paren;
struct expr_size;
struct expr_field;
struct expr_array;
struct expr_tuple;
struct expr_reference;
struct expr_istrue;
struct expr_isdefined;
struct expr_arguments;
struct expr_parameters;
struct expr_add_array;
struct expr_pointer;
struct expr_function;
struct expr_method;
struct expr_call;
struct expr_complement;
struct expr_negate;
struct expr_not;
struct expr_binary;
struct expr_add;
struct expr_sub;
struct expr_mul;
struct expr_div;
struct expr_mod;
struct expr_shift_left;
struct expr_shift_right;
struct expr_bitwise_or;
struct expr_bitwise_and;
struct expr_bitwise_exor;
struct expr_equality;
struct expr_inequality;
struct expr_less_equal;
struct expr_greater_equal;
struct expr_less;
struct expr_greater;
struct expr_or;
struct expr_and;
struct expr_ternary;
struct expr_increment;
struct expr_decrement;
struct expr_assign;
struct expr_assign_equal;
struct expr_assign_add;
struct expr_assign_sub;
struct expr_assign_mul;
struct expr_assign_div;
struct expr_assign_mod;
struct expr_assign_shift_left;
struct expr_assign_shift_right;
struct expr_assign_bitwise_or;
struct expr_assign_bitwise_and;
struct expr_assign_bitwise_exor;
struct stmt_list;
struct stmt_dev;
struct stmt_expr;
struct stmt_call;
struct stmt_assign;
struct stmt_endon;
struct stmt_notify;
struct stmt_wait;
struct stmt_waittill;
struct stmt_waittillmatch;
struct stmt_waittillframeend;
struct stmt_waitframe;
struct stmt_if;
struct stmt_ifelse;
struct stmt_while;
struct stmt_dowhile;
struct stmt_for;
struct stmt_foreach;
struct stmt_switch;
struct stmt_case;
struct stmt_default;
struct stmt_break;
struct stmt_continue;
struct stmt_return;
struct stmt_breakpoint;
struct stmt_prof_begin;
struct stmt_prof_end;
struct decl_thread;
struct decl_constant;
struct decl_usingtree;
struct decl_dev_begin;
struct decl_dev_end;
struct include;
struct program;
struct asm_loc;
struct asm_jump;
struct asm_jump_back;
struct asm_jump_cond;
struct asm_jump_false_expr;
struct asm_jump_true_expr;
struct asm_switch;
struct asm_endswitch;
struct asm_create;
struct asm_access;
struct asm_remove;
struct asm_clear;

union call
{
    enum class type { local, far, builtin };
    enum class mode { normal, thread, childthread, builtin };

    std::unique_ptr<node> as_node;
    std::unique_ptr<expr_pointer> as_pointer;
    std::unique_ptr<expr_function> as_function;

    call();
    call(std::unique_ptr<node> value);
    call(call&& value);
    call(const call&) = delete;
    call& operator=(const call&) = delete;
    ~call();
    friend bool operator==(const call& lhs, kind rhs);
    auto loc() const -> location;
    auto kind() const -> ast::kind;
    auto print() const -> std::string;
};

union expr
{
    std::unique_ptr<node> as_node;
    std::unique_ptr<expr_true> as_true;
    std::unique_ptr<expr_false> as_false;
    std::unique_ptr<expr_integer> as_integer;
    std::unique_ptr<expr_float> as_float;
    std::unique_ptr<expr_vector> as_vector;
    std::unique_ptr<expr_string> as_string;
    std::unique_ptr<expr_istring> as_istring;
    std::unique_ptr<expr_path> as_path;
    std::unique_ptr<expr_identifier> as_identifier;
    std::unique_ptr<expr_animtree> as_animtree;
    std::unique_ptr<expr_animation> as_animation;
    std::unique_ptr<expr_level> as_level;
    std::unique_ptr<expr_anim> as_anim;
    std::unique_ptr<expr_self> as_self;
    std::unique_ptr<expr_game> as_game;
    std::unique_ptr<expr_undefined> as_undefined;
    std::unique_ptr<expr_empty_array> as_empty_array;
    std::unique_ptr<expr_thisthread> as_thisthread;
    std::unique_ptr<expr_paren> as_paren;
    std::unique_ptr<expr_size> as_size;
    std::unique_ptr<expr_field> as_field;
    std::unique_ptr<expr_array> as_array;
    std::unique_ptr<expr_tuple> as_tuple;
    std::unique_ptr<expr_reference> as_reference;
    std::unique_ptr<expr_istrue> as_istrue;
    std::unique_ptr<expr_isdefined> as_isdefined;
    std::unique_ptr<expr_arguments> as_arguments;
    std::unique_ptr<expr_parameters> as_parameters;
    std::unique_ptr<expr_add_array> as_add_array;
    std::unique_ptr<expr_pointer> as_pointer;
    std::unique_ptr<expr_function> as_function;
    std::unique_ptr<expr_method> as_method;
    std::unique_ptr<expr_call> as_call;
    std::unique_ptr<expr_complement> as_complement;
    std::unique_ptr<expr_negate> as_negate;
    std::unique_ptr<expr_not> as_not;
    std::unique_ptr<expr_binary> as_binary;
    std::unique_ptr<expr_add> as_add;
    std::unique_ptr<expr_sub> as_sub;
    std::unique_ptr<expr_mul> as_mul;
    std::unique_ptr<expr_div> as_div;
    std::unique_ptr<expr_mod> as_mod;
    std::unique_ptr<expr_shift_left> as_shift_left;
    std::unique_ptr<expr_shift_right> as_shift_right;
    std::unique_ptr<expr_bitwise_or> as_bitwise_or;
    std::unique_ptr<expr_bitwise_and> as_bitwise_and;
    std::unique_ptr<expr_bitwise_exor> as_bitwise_exor;
    std::unique_ptr<expr_equality> as_equality;
    std::unique_ptr<expr_inequality> as_inequality;
    std::unique_ptr<expr_less_equal> as_less_equal;
    std::unique_ptr<expr_greater_equal> as_greater_equal;
    std::unique_ptr<expr_less> as_less;
    std::unique_ptr<expr_greater> as_greater;
    std::unique_ptr<expr_or> as_or;
    std::unique_ptr<expr_and> as_and;
    std::unique_ptr<expr_ternary> as_ternary;
    std::unique_ptr<expr_increment> as_increment;
    std::unique_ptr<expr_decrement> as_decrement;
    std::unique_ptr<expr_assign> as_assign;
    std::unique_ptr<expr_assign_equal> as_assign_equal;
    std::unique_ptr<expr_assign_add> as_assign_add;
    std::unique_ptr<expr_assign_sub> as_assign_sub;
    std::unique_ptr<expr_assign_mul> as_assign_mul;
    std::unique_ptr<expr_assign_div> as_assign_div;
    std::unique_ptr<expr_assign_mod> as_assign_mod;
    std::unique_ptr<expr_assign_shift_left> as_assign_shift_left;
    std::unique_ptr<expr_assign_shift_right> as_assign_shift_right;
    std::unique_ptr<expr_assign_bitwise_or> as_assign_bw_or;
    std::unique_ptr<expr_assign_bitwise_and> as_assign_bw_and;
    std::unique_ptr<expr_assign_bitwise_exor> as_assign_bw_exor;
    std::unique_ptr<asm_create> as_asm_create;
    std::unique_ptr<asm_access> as_asm_access;

    expr();
    expr(std::unique_ptr<node> value);
    expr(expr&& value);
    expr& operator=(expr&& value);
    expr(const expr&) = delete;
    expr& operator=(const expr&) = delete;
    ~expr();
    friend bool operator!=(const expr& lhs, kind rhs);
    friend bool operator==(const expr& lhs, kind rhs);
    friend bool operator==(const expr& lhs, const expr& rhs);
    auto loc() const -> location;
    auto kind() const -> ast::kind;
    auto print() const -> std::string;
};

union stmt
{
    std::unique_ptr<node> as_node;
    std::unique_ptr<stmt_list> as_list;
    std::unique_ptr<stmt_dev> as_dev;
    std::unique_ptr<stmt_expr> as_expr;
    std::unique_ptr<stmt_call> as_call;
    std::unique_ptr<stmt_assign> as_assign;
    std::unique_ptr<stmt_endon> as_endon;
    std::unique_ptr<stmt_notify> as_notify;
    std::unique_ptr<stmt_wait> as_wait;
    std::unique_ptr<stmt_waittill> as_waittill;
    std::unique_ptr<stmt_waittillmatch> as_waittillmatch;
    std::unique_ptr<stmt_waittillframeend> as_waittillframeend;
    std::unique_ptr<stmt_waitframe> as_waitframe;
    std::unique_ptr<stmt_if> as_if;
    std::unique_ptr<stmt_ifelse> as_ifelse;
    std::unique_ptr<stmt_while> as_while;
    std::unique_ptr<stmt_dowhile> as_dowhile;
    std::unique_ptr<stmt_for> as_for;
    std::unique_ptr<stmt_foreach> as_foreach;
    std::unique_ptr<stmt_switch> as_switch;
    std::unique_ptr<stmt_case> as_case;
    std::unique_ptr<stmt_default> as_default;
    std::unique_ptr<stmt_break> as_break;
    std::unique_ptr<stmt_continue> as_continue;
    std::unique_ptr<stmt_return> as_return;
    std::unique_ptr<stmt_breakpoint> as_breakpoint;
    std::unique_ptr<stmt_prof_begin> as_prof_begin;
    std::unique_ptr<stmt_prof_end> as_prof_end;
    std::unique_ptr<asm_loc> as_loc;
    std::unique_ptr<asm_jump_cond> as_cond;
    std::unique_ptr<asm_jump> as_jump;
    std::unique_ptr<asm_jump_back> as_jump_back;
    std::unique_ptr<asm_switch> as_asm_switch;
    std::unique_ptr<asm_endswitch> as_asm_endswitch;
    std::unique_ptr<asm_create> as_asm_create;
    std::unique_ptr<asm_access> as_asm_access;
    std::unique_ptr<asm_remove> as_asm_remove;
    std::unique_ptr<asm_clear> as_asm_clear;

    stmt();
    stmt(std::unique_ptr<node> value);
    stmt(stmt&& value);
    stmt& operator=(stmt&& value);
    stmt(const stmt&) = delete;
    stmt& operator=(const stmt&) = delete;
    ~stmt();
    friend bool operator==(const stmt& lhs, kind rhs);
    auto loc() const -> location;
    auto kind() const -> ast::kind;
    auto print() const -> std::string;
};

union decl
{
    std::unique_ptr<node> as_node;
    std::unique_ptr<decl_dev_begin> as_dev_begin;
    std::unique_ptr<decl_dev_end> as_dev_end;
    std::unique_ptr<decl_usingtree> as_usingtree;
    std::unique_ptr<decl_constant> as_constant;
    std::unique_ptr<decl_thread> as_thread;

    decl();
    decl(std::unique_ptr<node> value);
    decl(decl&& value);
    decl& operator=(decl&& value);
    decl(const decl&) = delete;
    decl& operator=(const decl&) = delete;
    ~decl();
    friend bool operator==(const decl& lhs, kind rhs);
    auto loc() const -> location;
    auto kind() const -> ast::kind;
    auto print() const -> std::string;
};

struct node
{
    using ptr = std::unique_ptr<node>;

private:
    kind kind_;
    location loc_;

public:
    node() : kind_(kind::null) {}
    node(const location& loc) : kind_(kind::null), loc_(loc) {}
    node(kind type) : kind_(type) {}
    node(kind type, const location& loc) : kind_(type), loc_(loc) {}

    virtual ~node() = default;
    virtual auto print() const -> std::string { return ""; };
    friend bool operator==(const node& n, kind k);
    friend bool operator==(const node& lhs, const node& rhs);

    auto kind() -> kind { return kind_; }
    auto loc() -> location& { return loc_; }

    auto is_special_stmt() -> bool;
    auto is_special_stmt_dev() -> bool;
    auto is_special_stmt_noif() -> bool;
    auto is_special_stmt_dev_noif() -> bool;
    auto is_binary() -> bool;
    auto precedence() -> std::uint8_t;

protected:
    static std::uint32_t indent_;
    static void reset_indentation();
    static std::string indented(std::uint32_t indent);
};

struct expr_true : public node
{
    using ptr = std::unique_ptr<expr_true>;

    expr_true();
    expr_true(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_true&, const expr_true&);
};

struct expr_false : public node
{
    using ptr = std::unique_ptr<expr_false>;

    expr_false();
    expr_false(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_false&, const expr_false&);
};

struct expr_integer : public node
{
    using ptr = std::unique_ptr<expr_integer>;

    std::string value;

    expr_integer(const std::string& value);
    expr_integer(const location& loc, const std::string& value);
    auto print() const -> std::string override;
    friend bool operator==(const expr_integer& lhs, const expr_integer& rhs);
};

struct expr_float : public node
{
    using ptr = std::unique_ptr<expr_float>;

    std::string value;

    expr_float(const std::string& value);
    expr_float(const location& loc, const std::string& value);
    auto print() const -> std::string override;
    friend bool operator==(const expr_float& lhs, const expr_float& rhs);
};

struct expr_vector : public node
{
    using ptr = std::unique_ptr<expr_vector>;

    expr x;
    expr y;
    expr z;

    expr_vector(expr x, expr y, expr z);
    expr_vector(const location& loc, expr x, expr y, expr z);
    auto print() const -> std::string override;
    friend bool operator==(const expr_vector& lhs, const expr_vector& rhs);
};

struct expr_string : public node
{
    using ptr = std::unique_ptr<expr_string>;

    std::string value;

    expr_string(const std::string& value);
    expr_string(const location& loc, const std::string& value);
    auto print() const -> std::string override;
    friend bool operator==(const expr_string& lhs, const expr_string& rhs);
};

struct expr_istring : public node
{
    using ptr = std::unique_ptr<expr_istring>;

    std::string value;

    expr_istring(const std::string& value);
    expr_istring(const location& loc, const std::string& value);
    auto print() const -> std::string override;
    friend bool operator==(const expr_istring& lhs, const expr_istring& rhs);
};

struct expr_path : public node
{
    using ptr = std::unique_ptr<expr_path>;

    std::string value;

    expr_path();
    expr_path(const std::string& value);
    expr_path(const location& loc);
    expr_path(const location& loc, const std::string& value);
    auto print() const -> std::string override;
    friend bool operator==(const expr_path& lhs, const expr_path& rhs);
};

struct expr_identifier : public node
{
    using ptr = std::unique_ptr<expr_identifier>;

    std::string value;

    expr_identifier(const std::string& value);
    expr_identifier(const location& loc, const std::string& value);
    auto print() const -> std::string override;
    friend bool operator==(const expr_identifier& lhs, const expr_identifier& rhs);
};

struct expr_animtree : public node
{
    using ptr = std::unique_ptr<expr_animtree>;

    expr_animtree();
    expr_animtree(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_animtree& lhs, const expr_animtree& rhs);
};

struct expr_animation : public node
{
    using ptr = std::unique_ptr<expr_animation>;

    std::string value;

    expr_animation(const std::string& value);
    expr_animation(const location& loc, const std::string& value);
    auto print() const -> std::string override;
    friend bool operator==(const expr_animation& lhs, const expr_animation& rhs);
};

struct expr_level : public node
{
    using ptr = std::unique_ptr<expr_level>;

    expr_level();
    expr_level(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_level& lhs, const expr_level& rhs);
};

struct expr_anim : public node
{
    using ptr = std::unique_ptr<expr_anim>;

    expr_anim();
    expr_anim(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_anim& lhs, const expr_anim& rhs);
};

struct expr_self : public node
{
    using ptr = std::unique_ptr<expr_self>;

    expr_self();
    expr_self(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_self& lhs, const expr_self& rhs);
};

struct expr_game : public node
{
    using ptr = std::unique_ptr<expr_game>;

    expr_game();
    expr_game(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_game& lhs, const expr_game& rhs);
};

struct expr_undefined : public node
{
    using ptr = std::unique_ptr<expr_undefined>;

    expr_undefined();
    expr_undefined(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_undefined& lhs, const expr_undefined& rhs);
};

struct expr_empty_array : public node
{
    using ptr = std::unique_ptr<expr_empty_array>;

    expr_empty_array();
    expr_empty_array(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_empty_array& lhs, const expr_empty_array& rhs);
};

struct expr_thisthread : public node
{
    using ptr = std::unique_ptr<expr_thisthread>;

    expr_thisthread();
    expr_thisthread(const location& loc);
    auto print() const -> std::string override;
    friend bool operator==(const expr_thisthread& lhs, const expr_thisthread& rhs);
};

struct expr_paren : public node
{
    using ptr = std::unique_ptr<expr_paren>;

    expr child;

    expr_paren(expr expr);
    expr_paren(const location& loc, expr expr);
    auto print() const -> std::string override;
    friend bool operator==(const expr_paren& lhs, const expr_paren& rhs);
};

struct expr_size : public node
{
    using ptr = std::unique_ptr<expr_size>;

    expr obj;

    expr_size(expr obj);
    expr_size(const location& loc, expr obj);
    auto print() const -> std::string override;
    friend bool operator==(const expr_size& lhs, const expr_size& rhs);
};

struct expr_field : public node
{
    using ptr = std::unique_ptr<expr_field>;

    expr obj;
    expr_identifier::ptr field;

    expr_field(expr obj, expr_identifier::ptr field);
    expr_field(const location& loc, expr obj, expr_identifier::ptr field);
    auto print() const -> std::string override;
    friend bool operator==(const expr_field& lhs, const expr_field& rhs);
};

struct expr_array : public node
{
    using ptr = std::unique_ptr<expr_array>;

    expr obj;
    expr key;

    expr_array(expr obj, expr key);
    expr_array(const location& loc, expr obj, expr key);
    auto print() const -> std::string override;
    friend bool operator==(const expr_array& lhs, const expr_array& rhs);
};

struct expr_tuple : public node
{
    using ptr = std::unique_ptr<expr_tuple>;

    std::vector<expr> list;
    expr temp;

    expr_tuple();
    expr_tuple(const location& loc);
    auto print() const -> std::string override;
};

struct expr_reference : public node
{
    using ptr = std::unique_ptr<expr_reference>;

    expr_path::ptr path;
    expr_identifier::ptr name;

    expr_reference(expr_path::ptr path, expr_identifier::ptr name);
    expr_reference(const location& loc, expr_path::ptr path, expr_identifier::ptr name);
    auto print() const -> std::string override;
};

struct expr_istrue : public node
{
    using ptr = std::unique_ptr<expr_istrue>;

    ast::expr expr;

    expr_istrue(ast::expr expr);
    expr_istrue(const location& loc, ast::expr expr);
    auto print() const -> std::string override;
};

struct expr_isdefined : public node
{
    using ptr = std::unique_ptr<expr_isdefined>;

    ast::expr expr;

    expr_isdefined(ast::expr expr);
    expr_isdefined(const location& loc, ast::expr expr);
    auto print() const -> std::string override;
};

struct expr_arguments : public node
{
    using ptr = std::unique_ptr<expr_arguments>;

    std::vector<expr> list;

    expr_arguments();
    expr_arguments(const location& loc);
    auto print() const -> std::string override;
};

struct expr_parameters : public node
{
    using ptr = std::unique_ptr<expr_parameters>;

    std::vector<expr_identifier::ptr> list;

    expr_parameters();
    expr_parameters(const location& loc);
    auto print() const -> std::string override;
};

struct expr_add_array : public node
{
    using ptr = std::unique_ptr<expr_add_array>;

    expr_arguments::ptr args;

    expr_add_array(expr_arguments::ptr args);
    expr_add_array(const location& loc, expr_arguments::ptr args);
    auto print() const -> std::string override;
};

struct expr_pointer : public node
{
    using ptr = std::unique_ptr<expr_pointer>;

    expr func;
    expr_arguments::ptr args;
    call::mode mode;

    expr_pointer(expr func, expr_arguments::ptr args, call::mode mode);
    expr_pointer(const location& loc, expr func, expr_arguments::ptr args, call::mode mode);
    auto print() const -> std::string override;
};

struct expr_function : public node
{
    using ptr = std::unique_ptr<expr_function>;

    expr_path::ptr path;
    expr_identifier::ptr name;
    expr_arguments::ptr args;
    call::mode mode;

    expr_function(expr_path::ptr path, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode);
    expr_function(const location& loc, expr_path::ptr path, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode);
    auto print() const -> std::string override;
};

struct expr_method : public node
{
    using ptr = std::unique_ptr<expr_method>;

    expr obj;
    ast::call call;

    expr_method(expr obj, ast::call call);
    expr_method(const location& loc, expr obj, ast::call call);
    auto print() const -> std::string override;
};

struct expr_call : public node
{
    using ptr = std::unique_ptr<expr_call>;

    ast::call call;

    expr_call(ast::call call);
    expr_call(const location& loc, ast::call call);
    auto print() const -> std::string override;
};

struct expr_complement : public node
{
    using ptr = std::unique_ptr<expr_complement>;

    expr rvalue;

    expr_complement(expr rvalue);
    expr_complement(const location& loc, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_negate : public node
{
    using ptr = std::unique_ptr<expr_negate>;

    expr rvalue;

    expr_negate(expr rvalue);
    expr_negate(const location& loc, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_not : public node
{
    using ptr = std::unique_ptr<expr_not>;

    expr rvalue;

    expr_not(expr rvalue);
    expr_not(const location& loc, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_binary : public node
{
    using ptr = std::unique_ptr<expr_binary>;

    expr lvalue;
    expr rvalue;

    expr_binary(ast::kind kind, expr lvalue, expr rvalue);
    expr_binary(ast::kind kind, const location& loc, expr lvalue, expr rvalue);
    virtual auto print() const -> std::string = 0;
};

struct expr_add : public expr_binary
{
    using ptr = std::unique_ptr<expr_add>;

    expr_add(expr lvalue, expr rvalue);
    expr_add(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_sub : public expr_binary
{
    using ptr = std::unique_ptr<expr_sub>;

    expr_sub(expr lvalue, expr rvalue);
    expr_sub(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_mul : public expr_binary
{
    using ptr = std::unique_ptr<expr_mul>;

    expr_mul(expr lvalue, expr rvalue);
    expr_mul(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_div : public expr_binary
{
    using ptr = std::unique_ptr<expr_div>;

    expr_div(expr lvalue, expr rvalue);
    expr_div(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_mod : public expr_binary
{
    using ptr = std::unique_ptr<expr_mod>;

    expr_mod(expr lvalue, expr rvalue);
    expr_mod(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_shift_left : public expr_binary
{
    using ptr = std::unique_ptr<expr_shift_left>;

    expr_shift_left(expr lvalue, expr rvalue);
    expr_shift_left(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_shift_right : public expr_binary
{
    using ptr = std::unique_ptr<expr_shift_right>;

    expr_shift_right(expr lvalue, expr rvalue);
    expr_shift_right(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_bitwise_or : public expr_binary
{
    using ptr = std::unique_ptr<expr_bitwise_or>;

    expr_bitwise_or(expr lvalue, expr rvalue);
    expr_bitwise_or(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_bitwise_and : public expr_binary
{
    using ptr = std::unique_ptr<expr_bitwise_and>;

    expr_bitwise_and(expr lvalue, expr rvalue);
    expr_bitwise_and(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_bitwise_exor : public expr_binary
{
    using ptr = std::unique_ptr<expr_bitwise_exor>;

    expr_bitwise_exor(expr lvalue, expr rvalue);
    expr_bitwise_exor(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_equality : public expr_binary
{
    using ptr = std::unique_ptr<expr_equality>;

    expr_equality(expr lvalue, expr rvalue);
    expr_equality(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_inequality : public expr_binary
{
    using ptr = std::unique_ptr<expr_inequality>;

    expr_inequality(expr lvalue, expr rvalue);
    expr_inequality(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_less_equal : public expr_binary
{
    using ptr = std::unique_ptr<expr_less_equal>;

    expr_less_equal(expr lvalue, expr rvalue);
    expr_less_equal(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_greater_equal : public expr_binary
{
    using ptr = std::unique_ptr<expr_greater_equal>;

    expr_greater_equal(expr lvalue, expr rvalue);
    expr_greater_equal(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_less : public expr_binary
{
    using ptr = std::unique_ptr<expr_less>;

    expr_less(expr lvalue, expr rvalue);
    expr_less(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_greater : public expr_binary
{
    using ptr = std::unique_ptr<expr_greater>;

    expr_greater(expr lvalue, expr rvalue);
    expr_greater(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_or : public expr_binary
{
    using ptr = std::unique_ptr<expr_or>;

    expr_or(expr lvalue, expr rvalue);
    expr_or(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_and : public expr_binary
{
    using ptr = std::unique_ptr<expr_and>;

    expr_and(expr lvalue, expr rvalue);
    expr_and(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_ternary : public node
{
    using ptr = std::unique_ptr<expr_ternary>;

    expr test;
    expr true_expr;
    expr false_expr;

    expr_ternary(expr test, expr true_expr, expr false_expr);
    expr_ternary(const location& loc, expr test, expr true_expr, expr false_expr);
    auto print() const -> std::string override;
};

struct expr_increment : node
{
    using ptr = std::unique_ptr<expr_increment>;

    expr lvalue;
    bool prefix;

    expr_increment(expr lvalue, bool prefix);
    expr_increment(const location& loc, expr lvalue, bool prefix);
    auto print() const -> std::string override;
};

struct expr_decrement : node
{
    using ptr = std::unique_ptr<expr_decrement>;

    expr lvalue;
    bool prefix;

    expr_decrement(expr lvalue, bool prefix);
    expr_decrement(const location& loc, expr lvalue, bool prefix);
    auto print() const -> std::string override;
};

struct expr_assign : public node
{
    using ptr = std::unique_ptr<expr_assign>;

    expr lvalue;
    expr rvalue;

    expr_assign(ast::kind kind, expr lvalue, expr rvalue);
    expr_assign(ast::kind kind, const location& loc, expr lvalue, expr rvalue);
    virtual auto print() const -> std::string = 0;
};

struct expr_assign_equal : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_equal>;

    expr_assign_equal(expr lvalue, expr rvalue);
    expr_assign_equal(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_add : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_add>;

    expr_assign_add(expr lvalue, expr rvalue);
    expr_assign_add(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_sub : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_sub>;

    expr_assign_sub(expr lvalue, expr rvalue);
    expr_assign_sub(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_mul : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_mul>;

    expr_assign_mul(expr lvalue, expr rvalue);
    expr_assign_mul(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_div : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_div>;

    expr_assign_div(expr lvalue, expr rvalue);
    expr_assign_div(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_mod : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_mod>;

    expr_assign_mod(expr lvalue, expr rvalue);
    expr_assign_mod(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_shift_left : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_shift_left>;

    expr_assign_shift_left(expr lvalue, expr rvalue);
    expr_assign_shift_left(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_shift_right : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_shift_right>;

    expr_assign_shift_right(expr lvalue, expr rvalue);
    expr_assign_shift_right(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_bitwise_or : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_bitwise_or>;

    expr_assign_bitwise_or(expr lvalue, expr rvalue);
    expr_assign_bitwise_or(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_bitwise_and : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_bitwise_and>;

    expr_assign_bitwise_and(expr lvalue, expr rvalue);
    expr_assign_bitwise_and(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct expr_assign_bitwise_exor : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_bitwise_exor>;

    expr_assign_bitwise_exor(expr lvalue, expr rvalue);
    expr_assign_bitwise_exor(const location& loc, expr lvalue, expr rvalue);
    auto print() const -> std::string override;
};

struct stmt_list : public node
{
    using ptr = std::unique_ptr<stmt_list>;

    std::vector<stmt> list;
    bool is_case = false;
    bool is_expr = false;

    stmt_list();
    stmt_list(const location& loc);
    auto print() const -> std::string override;
};

struct stmt_dev : public node
{
    using ptr = std::unique_ptr<stmt_dev>;

    stmt_list::ptr list;

    stmt_dev(stmt_list::ptr list);
    stmt_dev(const location& loc, stmt_list::ptr list);
    auto print() const -> std::string override;
};

struct stmt_expr : public node
{
    using ptr = std::unique_ptr<stmt_expr>;

    ast::expr expr;

    stmt_expr(ast::expr expr);
    stmt_expr(const location& loc, ast::expr expr);
    auto print() const -> std::string override;
};

struct stmt_call : public node
{
    using ptr = std::unique_ptr<stmt_call>;

    ast::expr expr;

    stmt_call(ast::expr expr);
    stmt_call(const location& loc, ast::expr expr);
    auto print() const -> std::string override;
};

struct stmt_assign : public node
{
    using ptr = std::unique_ptr<stmt_assign>;

    ast::expr expr;

    stmt_assign(ast::expr expr);
    stmt_assign(const location& loc, ast::expr expr);
    auto print() const -> std::string override;
};

struct stmt_endon : public node
{
    using ptr = std::unique_ptr<stmt_endon>;

    expr obj;
    expr event;

    stmt_endon(expr obj, expr event);
    stmt_endon(const location& loc, expr obj, expr event);
    auto print() const -> std::string override;
};

struct stmt_notify : public node
{
    using ptr = std::unique_ptr<stmt_notify>;

    expr obj;
    expr event;
    expr_arguments::ptr args;

    stmt_notify(expr obj, expr event, expr_arguments::ptr args);
    stmt_notify(const location& loc, expr obj, expr event, expr_arguments::ptr args);
    auto print() const -> std::string override;
};

struct stmt_wait : public node
{
    using ptr = std::unique_ptr<stmt_wait>;

    expr time;

    stmt_wait(expr time);
    stmt_wait(const location& loc, expr time);
    auto print() const -> std::string override;
};

struct stmt_waittill : public node
{
    using ptr = std::unique_ptr<stmt_waittill>;

    expr obj;
    expr event;
    expr_arguments::ptr args;

    stmt_waittill(expr obj, expr event, expr_arguments::ptr params);
    stmt_waittill(const location& loc, expr obj, expr event, expr_arguments::ptr args);
    auto print() const -> std::string override;
};

struct stmt_waittillmatch : public node
{
    using ptr = std::unique_ptr<stmt_waittillmatch>;

    expr obj;
    expr event;
    expr_arguments::ptr args;

    stmt_waittillmatch(expr obj, expr event, expr_arguments::ptr args);
    stmt_waittillmatch(const location& loc, expr obj, expr expr, expr_arguments::ptr args);
    auto print() const -> std::string override;
};

struct stmt_waittillframeend : public node
{
    using ptr = std::unique_ptr<stmt_waittillframeend>;

    stmt_waittillframeend();
    stmt_waittillframeend(const location& loc);

    auto print() const -> std::string override;
};

struct stmt_waitframe : public node
{
    using ptr = std::unique_ptr<stmt_waitframe>;

    stmt_waitframe();
    stmt_waitframe(const location& loc);
    auto print() const -> std::string override;
};

struct stmt_if : public node
{
    using ptr = std::unique_ptr<stmt_if>;

    expr test;
    ast::stmt stmt;
    block::ptr blk;

    stmt_if(expr test, ast::stmt stmt);
    stmt_if(const location& loc, expr test, ast::stmt stmt);
    auto print() const -> std::string override;
};

struct stmt_ifelse : public node
{
    using ptr = std::unique_ptr<stmt_ifelse>;

    expr test;
    stmt stmt_if;
    stmt stmt_else;
    block::ptr blk_if;
    block::ptr blk_else;

    stmt_ifelse(expr test, stmt stmt_if, stmt stmt_else);
    stmt_ifelse(const location& loc, expr test, stmt stmt_if, stmt stmt_else);
    auto print() const -> std::string override;
};

struct stmt_while : public node
{
    using ptr = std::unique_ptr<stmt_while>;

    expr test;
    ast::stmt stmt;
    block::ptr blk;

    stmt_while(expr test, ast::stmt stmt);
    stmt_while(const location& loc, expr test, ast::stmt stmt);
    auto print() const -> std::string override;
};

struct stmt_dowhile : public node
{
    using ptr = std::unique_ptr<stmt_dowhile>;

    expr test;
    ast::stmt stmt;
    block::ptr blk;

    stmt_dowhile(expr test, ast::stmt stmt);
    stmt_dowhile(const location& loc, expr test, ast::stmt stmt);
    auto print() const -> std::string override;
};

struct stmt_for : public node
{
    using ptr = std::unique_ptr<stmt_for>;

    ast::stmt init;
    ast::expr test;
    ast::stmt iter;
    ast::stmt stmt;
    block::ptr blk;
    block::ptr blk_iter;
    std::vector<std::string> vars;

    stmt_for(ast::stmt init, expr test, ast::stmt iter, ast::stmt stmt);
    stmt_for(const location& loc, ast::stmt init, expr test, ast::stmt iter, ast::stmt stmt);
    auto print() const -> std::string override;
};

struct stmt_foreach : public node
{
    using ptr = std::unique_ptr<stmt_foreach>;

    ast::expr array_expr;
    ast::expr value_expr;
    ast::expr key_expr;
    ast::expr array;
    ast::stmt pre_expr;
    ast::expr cond_expr;
    ast::stmt post_expr;
    ast::stmt stmt0;
    ast::stmt stmt;
    block::ptr ctx;
    block::ptr ctx_post;
    bool use_key;
    std::vector<std::string> vars;

    stmt_foreach(const location& loc, ast::stmt stmt, bool use_key);
    stmt_foreach(ast::expr element, ast::expr container, ast::stmt stmt);
    stmt_foreach(ast::expr key, ast::expr element, ast::expr container, ast::stmt stmt);
    stmt_foreach(const location& loc, ast::expr element, ast::expr container, ast::stmt stmt);
    stmt_foreach(const location& loc, ast::expr key, ast::expr element, ast::expr container, ast::stmt stmt);
    auto print() const -> std::string override;
};

struct stmt_switch : public node
{
    using ptr = std::unique_ptr<stmt_switch>;

    expr test;
    stmt_list::ptr stmt;
    block::ptr ctx;

    stmt_switch(expr test, stmt_list::ptr stmt);
    stmt_switch(const location& loc, expr test, stmt_list::ptr stmt);
    auto print() const -> std::string override;
};

struct stmt_case : public node
{
    using ptr = std::unique_ptr<stmt_case>;

    expr label;
    stmt_list::ptr stmt;
    block::ptr blk;

    stmt_case(expr label);
    stmt_case(const location& loc, expr label);
    stmt_case(const location& loc, expr label, stmt_list::ptr stmt);
    auto print() const -> std::string override;
};

struct stmt_default : public node
{
    using ptr = std::unique_ptr<stmt_default>;

    stmt_list::ptr stmt;
    block::ptr blk;

    stmt_default();
    stmt_default(const location& loc);
    stmt_default(const location& loc, stmt_list::ptr stmt);
    auto print() const -> std::string override;
};

struct stmt_break : public node
{
    using ptr = std::unique_ptr<stmt_break>;

    stmt_break();
    stmt_break(const location& loc);
    auto print() const -> std::string override;
};

struct stmt_continue : public node
{
    using ptr = std::unique_ptr<stmt_continue>;

    stmt_continue();
    stmt_continue(const location& loc);
    auto print() const -> std::string override;
};

struct stmt_return : public node
{
    using ptr = std::unique_ptr<stmt_return>;

    ast::expr expr;

    stmt_return(ast::expr expr);
    stmt_return(const location& loc, ast::expr expr);

    auto print() const -> std::string override;
};

struct stmt_breakpoint : public node
{
    using ptr = std::unique_ptr<stmt_breakpoint>;

    stmt_breakpoint();
    stmt_breakpoint(const location& loc);
    auto print() const -> std::string override;
};

struct stmt_prof_begin : public node
{
    using ptr = std::unique_ptr<stmt_prof_begin>;

    expr_arguments::ptr args;

    stmt_prof_begin(expr_arguments::ptr args);
    stmt_prof_begin(const location& loc, expr_arguments::ptr args);
    auto print() const -> std::string override;
};

struct stmt_prof_end : public node
{
    using ptr = std::unique_ptr<stmt_prof_end>;

    expr_arguments::ptr args;

    stmt_prof_end(expr_arguments::ptr args);
    stmt_prof_end(const location& loc, expr_arguments::ptr args);
    auto print() const -> std::string override;
};

struct decl_thread : public node
{
    using ptr = std::unique_ptr<decl_thread>;

    expr_identifier::ptr name;
    expr_parameters::ptr params;
    stmt_list::ptr stmt;

    decl_thread(expr_identifier::ptr name, expr_parameters::ptr params, stmt_list::ptr stmt);
    decl_thread(const location& loc, expr_identifier::ptr name, expr_parameters::ptr params, stmt_list::ptr stmt);
    auto print() const -> std::string override;
};

struct decl_constant : public node
{
    using ptr = std::unique_ptr<decl_constant>;

    expr_identifier::ptr name;
    expr value;

    decl_constant(expr_identifier::ptr name, expr value);
    decl_constant(const location& loc, expr_identifier::ptr name, expr value);
    auto print() const -> std::string override;
};

struct decl_usingtree : public node
{
    using ptr = std::unique_ptr<decl_usingtree>;

    expr_string::ptr name;

    decl_usingtree(expr_string::ptr name);
    decl_usingtree(const location& loc, expr_string::ptr name);
    auto print() const -> std::string override;
};

struct decl_dev_begin : public node
{
    using ptr = std::unique_ptr<decl_dev_begin>;

    decl_dev_begin();
    decl_dev_begin(const location& loc);
    auto print() const -> std::string override;
};

struct decl_dev_end : public node
{
    using ptr = std::unique_ptr<decl_dev_end>;

    decl_dev_end();
    decl_dev_end(const location& loc);
    auto print() const -> std::string override;
};

struct include : public node
{
    using ptr = std::unique_ptr<include>;

    expr_path::ptr path;

    include(expr_path::ptr path);
    include(const location& loc, expr_path::ptr path);
    auto print() const -> std::string override;
};

struct program : public node
{
    using ptr = std::unique_ptr<program>;

    std::vector<include::ptr> includes;
    std::vector<decl> declarations;

    program();
    program(const location& loc);
    auto print() const -> std::string override;
};

struct asm_loc : public node
{
    using ptr = std::unique_ptr<asm_loc>;

    std::string value;

    asm_loc(const std::string& value);
    asm_loc(const location& loc, const std::string& value);
    auto print() const -> std::string override;
};

struct asm_jump : public node
{
    using ptr = std::unique_ptr<asm_jump>;

    std::string value;

    asm_jump(const std::string& value);
    asm_jump(const location& loc, const std::string& value);
    auto print() const -> std::string override;
};

struct asm_jump_back : public node
{
    using ptr = std::unique_ptr<asm_jump_back>;

    std::string value;

    asm_jump_back(const std::string& value);
    asm_jump_back(const location& loc, const std::string& value);
    auto print() const -> std::string override;
};

struct asm_jump_cond : public node
{
    using ptr = std::unique_ptr<asm_jump_cond>;

    ast::expr expr;
    std::string value;

    asm_jump_cond(ast::expr expr, const std::string& value);
    asm_jump_cond(const location& loc, ast::expr expr, const std::string& value);
    auto print() const -> std::string override;
};

struct asm_jump_true_expr : public node
{
    using ptr = std::unique_ptr<asm_jump_true_expr>;

    ast::expr expr;
    std::string value;

    asm_jump_true_expr(ast::expr expr, const std::string& value);
    asm_jump_true_expr(const location& loc, ast::expr expr, const std::string& value);
    auto print() const -> std::string override;
};

struct asm_jump_false_expr : public node
{
    using ptr = std::unique_ptr<asm_jump_false_expr>;

    ast::expr expr;
    std::string value;

    asm_jump_false_expr(ast::expr expr, const std::string& value);
    asm_jump_false_expr(const location& loc, ast::expr expr, const std::string& value);
    auto print() const -> std::string override;
};

struct asm_switch : public node
{
    using ptr = std::unique_ptr<asm_switch>;

    ast::expr expr;
    std::string value;

    asm_switch(ast::expr expr, const std::string& value);
    asm_switch(const location& loc, ast::expr expr, const std::string& value);
    auto print() const -> std::string override;
};

struct asm_endswitch : public node
{
    using ptr = std::unique_ptr<asm_endswitch>;

    std::vector<std::string> data;
    std::string count;

    asm_endswitch(std::vector<std::string> data, const std::string& count);
    asm_endswitch(const location& loc, std::vector<std::string> data, const std::string& count);
    auto print() const -> std::string override;
};

struct asm_prescriptcall : public node
{
    using ptr = std::unique_ptr<asm_prescriptcall>;

    asm_prescriptcall();
    asm_prescriptcall(const location& loc);
    auto print() const -> std::string override;
};

struct asm_voidcodepos : public node
{
    using ptr = std::unique_ptr<asm_voidcodepos>;

    asm_voidcodepos();
    asm_voidcodepos(const location& loc);
    auto print() const -> std::string override;
};

struct asm_create : public node
{
    using ptr = std::unique_ptr<asm_create>;

    std::string index;
    std::vector<std::string> vars;

    asm_create(const std::string& index);
    asm_create(const location& loc, const std::string& index);
    auto print() const -> std::string override;
};

struct asm_access : public node
{
    using ptr = std::unique_ptr<asm_access>;

    std::string index;

    asm_access(const std::string& index);
    asm_access(const location& loc, const std::string& index);
    auto print() const -> std::string override;
};

struct asm_remove : public node
{
    using ptr = std::unique_ptr<asm_remove>;

    std::string index;

    asm_remove(const std::string& index);
    asm_remove(const location& loc, const std::string& index);
    auto print() const -> std::string override;
};

struct asm_clear : public node
{
    using ptr = std::unique_ptr<asm_clear>;

    std::string index;

    asm_clear(const std::string& index);
    asm_clear(const location& loc, const std::string& index);
    auto print() const -> std::string override;
};

} // namespace xsk::gsc::ast
