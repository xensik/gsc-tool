// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

struct node
{
    using ptr = std::unique_ptr<node>;

    enum type
    {
        node_null,
        node_prescriptcall,
        node_voidcodepos,
        expr_empty,
        expr_true,
        expr_false,
        expr_integer,
        expr_float,
        expr_vector,
        expr_hash,
        expr_string,
        expr_istring,
        expr_path,
        expr_identifier,
        expr_animtree,
        expr_animation,
        expr_classes,
        expr_world,
        expr_level,
        expr_anim,
        expr_self,
        expr_game,
        expr_undefined,
        expr_empty_array,
        expr_ellipsis,
        expr_paren,
        expr_size,
        expr_field,
        expr_array,
        expr_reference,
        expr_getnextarraykey,
        expr_getfirstarraykey,
        expr_getdvarcoloralpha,
        expr_getdvarcolorblue,
        expr_getdvarcolorgreen,
        expr_getdvarcolorred,
        expr_getdvarvector,
        expr_getdvarfloat,
        expr_getdvarint,
        expr_getdvar,
        expr_gettime,
        expr_abs,
        expr_vectortoangles,
        expr_angleclamp180,
        expr_anglestoforward,
        expr_anglestoright,
        expr_anglestoup,
        expr_vectorscale,
        expr_isdefined,
        expr_arguments,
        expr_parameters,
        expr_member,
        expr_pointer,
        expr_function,
        expr_method,
        expr_call,
        expr_new,
        expr_complement,
        expr_negate,
        expr_not,
        expr_binary,
        expr_ternary,
        expr_const,
        expr_assign,
        expr_increment,
        expr_decrement,
        stmt_empty,
        stmt_list,
        stmt_comp,
        stmt_dev,
        stmt_expr,
        stmt_endon,
        stmt_notify,
        stmt_wait,
        stmt_waittill,
        stmt_waittillmatch,
        stmt_waittillframeend,
        stmt_waitrealtime,
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
        stmt_jmp,
        stmt_jmp_back,
        stmt_jmp_cond,
        stmt_jmp_true,
        stmt_jmp_false,
        stmt_jmp_switch,
        stmt_jmp_endswitch,
        stmt_jmp_dev,
        decl_empty,
        decl_function,
        decl_usingtree,
        decl_namespace,
        decl_dev_begin,
        decl_dev_end,
        include,
        program,
    };

    virtual ~node() = default;

    auto kind() const -> type { return kind_; }
    auto loc() const -> location const& { return loc_; }
    auto label() const -> std::string { return loc_.label(); }

    auto is_special_stmt() -> bool;
    auto is_special_stmt_dev() -> bool;
    auto is_special_stmt_noif() -> bool;
    auto is_special_stmt_dev_noif() -> bool;
    auto is_boolean() -> bool;
    auto is_binary() -> bool;
    auto is_assign() -> bool;

    virtual auto precedence() -> u8;

    template<typename T>
    static auto as(node::ptr) -> std::unique_ptr<T>;

protected:
    node(type t) : kind_(t) {}
    node(type t, location const& loc) : kind_(t), loc_(loc) {}

private:
    type kind_;
    location loc_;
};

struct expr : node
{
    using ptr = std::unique_ptr<expr>;

    virtual ~expr() = default;

    friend auto operator==(expr const& lhs, expr const& rhs) -> bool;

    template<typename T>
    auto is() const -> bool;

    template<typename T>
    auto as() const -> T const&;

    template<typename T>
    auto as() -> T&;

protected:
    expr(type t);
    expr(type t, location const& loc);
};

struct call : expr
{
    using ptr = std::unique_ptr<call>;

    enum class mode { normal, thread, };

    virtual ~call() = default;

    template<typename T>
    auto is() const -> bool;

    template<typename T>
    auto as() const -> T const&;

    template<typename T>
    auto as() -> T&;

protected:
    call(node::type t);
    call(node::type t, location const& loc);
};

struct stmt : node
{
    using ptr = std::unique_ptr<stmt>;

    virtual ~stmt() = default;

    template<typename T>
    auto is() const -> bool;

    template<typename T>
    auto as() const -> T const&;

    template<typename T>
    auto as() -> T&;

protected:
    stmt(type t);
    stmt(type t, location const& loc);
};

struct decl : node
{
    using ptr = std::unique_ptr<decl>;

    virtual ~decl() = default;

    template<typename T>
    auto is() const -> bool;

    template<typename T>
    auto as() const -> T const&;

    template<typename T>
    auto as() -> T&;

protected:
    decl(type t);
    decl(type t, location const& loc);
};

#define XSK_ARC_AST_MAKE(node_type)                                                 \
template<class... Args>                                                             \
inline static auto make(Args&&... args) -> std::unique_ptr<node_type>               \
{                                                                                   \
    return std::unique_ptr<node_type>(new node_type(std::forward<Args>(args)...));  \
}

struct node_prescriptcall : public node
{
    using ptr = std::unique_ptr<node_prescriptcall>;

    node_prescriptcall(location const& loc);
    XSK_ARC_AST_MAKE(node_prescriptcall)
};

struct node_voidcodepos : public node
{
    using ptr = std::unique_ptr<node_voidcodepos>;

    node_voidcodepos(location const& loc);
    XSK_ARC_AST_MAKE(node_voidcodepos)
};

struct expr_empty : public expr
{
    using ptr = std::unique_ptr<expr_empty>;

    expr_empty(location const& loc);
    friend auto operator==(expr_empty const& lhs, expr_empty const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_empty)
};

struct expr_true : public expr
{
    using ptr = std::unique_ptr<expr_true>;

    expr_true(location const& loc);
    friend auto operator==(expr_true const& lhs, expr_true const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_true)
};

struct expr_false : public expr
{
    using ptr = std::unique_ptr<expr_false>;

    expr_false(location const& loc);
    friend auto operator==(expr_false const& lhs, expr_false const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_false)
};

struct expr_integer : public expr
{
    using ptr = std::unique_ptr<expr_integer>;

    std::string value;

    expr_integer(location const& loc, std::string const& value);
    friend auto operator==(expr_integer const& lhs, expr_integer const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_integer)
};

struct expr_float : public expr
{
    using ptr = std::unique_ptr<expr_float>;

    std::string value;

    expr_float(location const& loc, std::string const& value);
    friend auto operator==(expr_float const& lhs, expr_float const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_float)
};

struct expr_vector : public expr
{
    using ptr = std::unique_ptr<expr_vector>;

    expr::ptr x;
    expr::ptr y;
    expr::ptr z;

    expr_vector(location const& loc, expr::ptr x, expr::ptr y, expr::ptr z);
    friend auto operator==(expr_vector const& lhs, expr_vector const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_vector)
};

struct expr_hash : public expr
{
    using ptr = std::unique_ptr<expr_hash>;

    std::string value;

    expr_hash(location const& loc, std::string const& value);
    friend auto operator==(expr_hash const& lhs, expr_hash const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_hash)
};

struct expr_string : public expr
{
    using ptr = std::unique_ptr<expr_string>;

    std::string value;

    expr_string(location const& loc, std::string const& value);
    friend auto operator==(expr_string const& lhs, expr_string const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_string)
};

struct expr_istring : public expr
{
    using ptr = std::unique_ptr<expr_istring>;

    std::string value;

    expr_istring(location const& loc, std::string const& value);
    friend auto operator==(expr_istring const& lhs, expr_istring const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_istring)
};

struct expr_path : public expr
{
    using ptr = std::unique_ptr<expr_path>;

    std::string value;

    expr_path(location const& loc);
    expr_path(location const& loc, std::string const& value);
    friend auto operator==(expr_path const& lhs, expr_path const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_path)
};

struct expr_identifier : public expr
{
    using ptr = std::unique_ptr<expr_identifier>;

    std::string value;

    expr_identifier(location const& loc, std::string const& value);
    friend auto operator==(expr_identifier const& lhs, expr_identifier const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_identifier)
};

struct expr_animtree : public expr
{
    using ptr = std::unique_ptr<expr_animtree>;

    expr_animtree(location const& loc);
    friend auto operator==(expr_animtree const& lhs, expr_animtree const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_animtree)
};

struct expr_animation : public expr
{
    using ptr = std::unique_ptr<expr_animation>;

    std::string value;

    expr_animation(location const& loc, std::string const& value);
    friend auto operator==(expr_animation const& lhs, expr_animation const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_animation)
};

struct expr_classes : public expr
{
    using ptr = std::unique_ptr<expr_classes>;

    expr_classes(location const& loc);
    friend auto operator==(expr_classes const& lhs, expr_classes const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_classes)
};

struct expr_world : public expr
{
    using ptr = std::unique_ptr<expr_world>;

    expr_world(location const& loc);
    friend auto operator==(expr_world const& lhs, expr_world const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_world)
};

struct expr_level : public expr
{
    using ptr = std::unique_ptr<expr_level>;

    expr_level(location const& loc);
    friend auto operator==(expr_level const& lhs, expr_level const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_level)
};

struct expr_anim : public expr
{
    using ptr = std::unique_ptr<expr_anim>;

    expr_anim(location const& loc);
    friend auto operator==(expr_anim const& lhs, expr_anim const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_anim)
};

struct expr_self : public expr
{
    using ptr = std::unique_ptr<expr_self>;

    expr_self(location const& loc);
    friend auto operator==(expr_self const& lhs, expr_self const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_self)
};

struct expr_game : public expr
{
    using ptr = std::unique_ptr<expr_game>;

    expr_game(location const& loc);
    friend auto operator==(expr_game const& lhs, expr_game const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_game)
};

struct expr_undefined : public expr
{
    using ptr = std::unique_ptr<expr_undefined>;

    expr_undefined(location const& loc);
    friend auto operator==(expr_undefined const& lhs, expr_undefined const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_undefined)
};

struct expr_empty_array : public expr
{
    using ptr = std::unique_ptr<expr_empty_array>;

    expr_empty_array(location const& loc);
    friend auto operator==(expr_empty_array const& lhs, expr_empty_array const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_empty_array)
};

struct expr_ellipsis : public expr
{
    using ptr = std::unique_ptr<expr_ellipsis>;

    expr_ellipsis(location const& loc);
    friend auto operator==(expr_ellipsis const& lhs, expr_ellipsis const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_ellipsis)
};

struct expr_paren : public expr
{
    using ptr = std::unique_ptr<expr_paren>;

    expr::ptr value;

    expr_paren(location const& loc, expr::ptr value);
    friend auto operator==(expr_paren const& lhs, expr_paren const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_paren)
};

struct expr_size : public expr
{
    using ptr = std::unique_ptr<expr_size>;

    expr::ptr obj;

    expr_size(location const& loc, expr::ptr obj);
    friend auto operator==(expr_size const& lhs, expr_size const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_size)
};

struct expr_field : public expr
{
    using ptr = std::unique_ptr<expr_field>;

    expr::ptr obj;
    expr_identifier::ptr field;

    expr_field(location const& loc, expr::ptr obj, expr_identifier::ptr field);
    friend auto operator==(expr_field const& lhs, expr_field const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_field)
};

struct expr_array : public expr
{
    using ptr = std::unique_ptr<expr_array>;

    expr::ptr obj;
    expr::ptr key;

    expr_array(location const& loc, expr::ptr obj, expr::ptr key);
    friend auto operator==(expr_array const& lhs, expr_array const& rhs) -> bool;
    XSK_ARC_AST_MAKE(expr_array)
};

struct expr_reference : public expr
{
    using ptr = std::unique_ptr<expr_reference>;

    expr_path::ptr path;
    expr_identifier::ptr name;

    expr_reference(location const& loc, expr_path::ptr path, expr_identifier::ptr name);
    XSK_ARC_AST_MAKE(expr_reference)
};

struct expr_getnextarraykey : public expr
{
    using ptr = std::unique_ptr<expr_getnextarraykey>;

    expr::ptr arg1;
    expr::ptr arg2;

    expr_getnextarraykey(location const& loc, expr::ptr arg1, expr::ptr arg2);
    XSK_ARC_AST_MAKE(expr_getnextarraykey)
};

struct expr_getfirstarraykey : public expr
{
    using ptr = std::unique_ptr<expr_getfirstarraykey>;

    expr::ptr arg;

    expr_getfirstarraykey(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_getfirstarraykey)
};

struct expr_getdvarcoloralpha : public expr
{
    using ptr = std::unique_ptr<expr_getdvarcoloralpha>;

    expr::ptr arg;

    expr_getdvarcoloralpha(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_getdvarcoloralpha)
};

struct expr_getdvarcolorblue : public expr
{
    using ptr = std::unique_ptr<expr_getdvarcolorblue>;

    expr::ptr arg;

    expr_getdvarcolorblue(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_getdvarcolorblue)
};

struct expr_getdvarcolorgreen : public expr
{
    using ptr = std::unique_ptr<expr_getdvarcolorgreen>;

    expr::ptr arg;

    expr_getdvarcolorgreen(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_getdvarcolorgreen)
};

struct expr_getdvarcolorred : public expr
{
    using ptr = std::unique_ptr<expr_getdvarcolorred>;

    expr::ptr arg;

    expr_getdvarcolorred(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_getdvarcolorred)
};

struct expr_getdvarvector : public expr
{
    using ptr = std::unique_ptr<expr_getdvarvector>;

    expr::ptr arg;

    expr_getdvarvector(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_getdvarvector)
};

struct expr_getdvarfloat : public expr
{
    using ptr = std::unique_ptr<expr_getdvarfloat>;

    expr::ptr arg;

    expr_getdvarfloat(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_getdvarfloat)
};

struct expr_getdvarint : public expr
{
    using ptr = std::unique_ptr<expr_getdvarint>;

    expr::ptr arg;

    expr_getdvarint(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_getdvarint)
};


struct expr_getdvar : public expr
{
    using ptr = std::unique_ptr<expr_getdvar>;

    expr::ptr arg;

    expr_getdvar(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_getdvar)
};

struct expr_gettime : public expr
{
    using ptr = std::unique_ptr<expr_gettime>;

    expr_gettime(location const& loc);
    XSK_ARC_AST_MAKE(expr_gettime)
};

struct expr_abs : public expr
{
    using ptr = std::unique_ptr<expr_abs>;

    expr::ptr arg;

    expr_abs(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_abs)
};

struct expr_vectortoangles : public expr
{
    using ptr = std::unique_ptr<expr_vectortoangles>;

    expr::ptr arg;

    expr_vectortoangles(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_vectortoangles)
};

struct expr_angleclamp180 : public expr
{
    using ptr = std::unique_ptr<expr_angleclamp180>;

    expr::ptr arg;

    expr_angleclamp180(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_angleclamp180)
};

struct expr_anglestoforward : public expr
{
    using ptr = std::unique_ptr<expr_anglestoforward>;

    expr::ptr arg;

    expr_anglestoforward(const location& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_anglestoforward)
};

struct expr_anglestoright : public expr
{
    using ptr = std::unique_ptr<expr_anglestoright>;

    expr::ptr arg;

    expr_anglestoright(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_anglestoright)
};

struct expr_anglestoup : public expr
{
    using ptr = std::unique_ptr<expr_anglestoup>;

    expr::ptr arg;

    expr_anglestoup(location const& loc, expr::ptr arg);
    XSK_ARC_AST_MAKE(expr_anglestoup)
};

struct expr_vectorscale : public expr
{
    using ptr = std::unique_ptr<expr_vectorscale>;

    expr::ptr arg1;
    expr::ptr arg2;

    expr_vectorscale(location const& loc, expr::ptr arg1, expr::ptr arg2);
    XSK_ARC_AST_MAKE(expr_vectorscale)
};

struct expr_isdefined : public expr
{
    using ptr = std::unique_ptr<expr_isdefined>;

    expr::ptr value;

    expr_isdefined(location const& loc, expr::ptr value);
    XSK_ARC_AST_MAKE(expr_isdefined)
};

struct expr_arguments : public expr
{
    using ptr = std::unique_ptr<expr_arguments>;

    std::vector<expr::ptr> list;

    expr_arguments(location const& loc);
    XSK_ARC_AST_MAKE(expr_arguments)
};

struct expr_parameters : public expr
{
    using ptr = std::unique_ptr<expr_parameters>;

    std::vector<expr::ptr> list;

    expr_parameters(location const& loc);
    XSK_ARC_AST_MAKE(expr_parameters)
};

struct expr_member : public call
{
    using ptr = std::unique_ptr<expr_member>;

    expr::ptr obj;
    expr_identifier::ptr name;
    expr_arguments::ptr args;
    call::mode mode;

    expr_member(location const& loc, expr::ptr obj, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode);
    XSK_ARC_AST_MAKE(expr_member)
};

struct expr_pointer : public call
{
    using ptr = std::unique_ptr<expr_pointer>;

    expr::ptr func;
    expr_arguments::ptr args;
    call::mode mode;

    expr_pointer(location const& loc, expr::ptr func, expr_arguments::ptr args, call::mode mode);
    XSK_ARC_AST_MAKE(expr_pointer)
};

struct expr_function : public call
{
    using ptr = std::unique_ptr<expr_function>;

    expr_path::ptr path;
    expr_identifier::ptr name;
    expr_arguments::ptr args;
    call::mode mode;

    expr_function(location const& loc, expr_path::ptr path, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode);
    XSK_ARC_AST_MAKE(expr_function)
};

struct expr_method : public expr
{
    using ptr = std::unique_ptr<expr_method>;

    expr::ptr obj;
    call::ptr value;

    expr_method(location const& loc, expr::ptr obj, call::ptr value);
    XSK_ARC_AST_MAKE(expr_method)
};

struct expr_call : public expr
{
    using ptr = std::unique_ptr<expr_call>;

    call::ptr value;

    expr_call(location const& loc, call::ptr value);
    XSK_ARC_AST_MAKE(expr_call)
};

struct expr_new : public expr
{
    using ptr = std::unique_ptr<expr_new>;

    expr_identifier::ptr name;

    expr_new(location const& loc, expr_identifier::ptr name);
    XSK_ARC_AST_MAKE(expr_new)
};

struct expr_complement : public expr
{
    using ptr = std::unique_ptr<expr_complement>;

    expr::ptr rvalue;

    expr_complement(location const& loc, expr::ptr rvalue);
    XSK_ARC_AST_MAKE(expr_complement)
};

struct expr_negate : public expr
{
    using ptr = std::unique_ptr<expr_negate>;

    expr::ptr rvalue;

    expr_negate(location const& loc, expr::ptr rvalue);
    XSK_ARC_AST_MAKE(expr_negate)
};

struct expr_not : public expr
{
    using ptr = std::unique_ptr<expr_not>;

    expr::ptr rvalue;

    expr_not(location const& loc, expr::ptr rvalue);
    XSK_ARC_AST_MAKE(expr_not)
};

struct expr_binary : public expr
{
    using ptr = std::unique_ptr<expr_binary>;

    enum class op { seq, sne, eq, ne, le, ge, lt, gt, add, sub, mul, div, mod, shl, shr, bwor, bwand, bwexor, bool_or, bool_and };

    expr::ptr lvalue;
    expr::ptr rvalue;
    op oper;

    expr_binary(location const& loc, expr::ptr lvalue, expr::ptr rvalue, op oper);
    XSK_ARC_AST_MAKE(expr_binary)
    auto precedence() -> u8;
};

struct expr_ternary : public expr
{
    using ptr = std::unique_ptr<expr_ternary>;

    expr::ptr test;
    expr::ptr true_expr;
    expr::ptr false_expr;

    expr_ternary(location const& loc, expr::ptr test, expr::ptr true_expr, expr::ptr false_expr);
    XSK_ARC_AST_MAKE(expr_ternary)
};

struct expr_const : public expr
{
    using ptr = std::unique_ptr<expr_const>;

    expr_identifier::ptr lvalue;
    expr::ptr rvalue;

    expr_const(location const& loc, expr_identifier::ptr lvalue, expr::ptr rvalue);
    XSK_ARC_AST_MAKE(expr_const)
};

struct expr_assign : public expr
{
    using ptr = std::unique_ptr<expr_assign>;

    enum class op { eq, add, sub, mul, div, mod, shl, shr, bwor, bwand, bwexor };

    expr::ptr lvalue;
    expr::ptr rvalue;
    op oper;

    expr_assign(location const& loc, expr::ptr lvalue, expr::ptr rvalue, op oper);
    XSK_ARC_AST_MAKE(expr_assign)
};

struct expr_increment : expr
{
    using ptr = std::unique_ptr<expr_increment>;

    expr::ptr lvalue;
    bool prefix;

    expr_increment(location const& loc, expr::ptr lvalue, bool prefix);
    XSK_ARC_AST_MAKE(expr_increment)
};

struct expr_decrement : expr
{
    using ptr = std::unique_ptr<expr_decrement>;

    expr::ptr lvalue;
    bool prefix;

    expr_decrement(location const& loc, expr::ptr lvalue, bool prefix);
    XSK_ARC_AST_MAKE(expr_decrement)
};

struct stmt_empty : public stmt
{
    using ptr = std::unique_ptr<stmt_empty>;

    stmt_empty(location const& loc);
    XSK_ARC_AST_MAKE(stmt_empty)
};

struct stmt_list : public stmt
{
    using ptr = std::unique_ptr<stmt_list>;

    std::vector<stmt::ptr> list;

    stmt_list(location const& loc);
    XSK_ARC_AST_MAKE(stmt_list)
};

struct stmt_comp : public stmt
{
    using ptr = std::unique_ptr<stmt_comp>;

    stmt_list::ptr block;

    stmt_comp(location const& loc, stmt_list::ptr block);
    XSK_ARC_AST_MAKE(stmt_comp)
};

struct stmt_dev : public stmt
{
    using ptr = std::unique_ptr<stmt_dev>;

    stmt_list::ptr block;

    stmt_dev(location const& loc, stmt_list::ptr block);
    XSK_ARC_AST_MAKE(stmt_dev)
};

struct stmt_expr : public stmt
{
    using ptr = std::unique_ptr<stmt_expr>;

    expr::ptr value;

    stmt_expr(location const& loc, expr::ptr value);
    XSK_ARC_AST_MAKE(stmt_expr)
};

struct stmt_endon : public stmt
{
    using ptr = std::unique_ptr<stmt_endon>;

    expr::ptr obj;
    expr::ptr event;

    stmt_endon(location const& loc, expr::ptr obj, expr::ptr event);
    XSK_ARC_AST_MAKE(stmt_endon)
};

struct stmt_notify : public stmt
{
    using ptr = std::unique_ptr<stmt_notify>;

    expr::ptr obj;
    expr::ptr event;
    expr_arguments::ptr args;

    stmt_notify(location const& loc, expr::ptr obj, expr::ptr event, expr_arguments::ptr args);
    XSK_ARC_AST_MAKE(stmt_notify)
};

struct stmt_wait : public stmt
{
    using ptr = std::unique_ptr<stmt_wait>;

    expr::ptr time;

    stmt_wait(location const& loc, expr::ptr time);
    XSK_ARC_AST_MAKE(stmt_wait)
};

struct stmt_waittill : public stmt
{
    using ptr = std::unique_ptr<stmt_waittill>;

    expr::ptr obj;
    expr::ptr event;
    expr_arguments::ptr args;

    stmt_waittill(location const& loc, expr::ptr obj, expr::ptr event, expr_arguments::ptr args);
    XSK_ARC_AST_MAKE(stmt_waittill)
};

struct stmt_waittillmatch : public stmt
{
    using ptr = std::unique_ptr<stmt_waittillmatch>;

    expr::ptr obj;
    expr::ptr event;
    expr_arguments::ptr args;

    stmt_waittillmatch(location const& loc, expr::ptr obj, expr::ptr expr, expr_arguments::ptr args);
    XSK_ARC_AST_MAKE(stmt_waittillmatch)
};

struct stmt_waittillframeend : public stmt
{
    using ptr = std::unique_ptr<stmt_waittillframeend>;

    stmt_waittillframeend(location const& loc);
    XSK_ARC_AST_MAKE(stmt_waittillframeend)
};

struct stmt_waitrealtime : public stmt
{
    using ptr = std::unique_ptr<stmt_waitrealtime>;

    expr::ptr time;

    stmt_waitrealtime(location const& loc, expr::ptr time);
    XSK_ARC_AST_MAKE(stmt_waitrealtime)
};

struct stmt_if : public stmt
{
    using ptr = std::unique_ptr<stmt_if>;

    expr::ptr test;
    stmt::ptr body;

    stmt_if(location const& loc, expr::ptr test, stmt::ptr body);
    XSK_ARC_AST_MAKE(stmt_if)
};

struct stmt_ifelse : public stmt
{
    using ptr = std::unique_ptr<stmt_ifelse>;

    expr::ptr test;
    stmt::ptr stmt_if;
    stmt::ptr stmt_else;

    stmt_ifelse(location const& loc, expr::ptr test, stmt::ptr stmt_if, stmt::ptr stmt_else);
    XSK_ARC_AST_MAKE(stmt_ifelse)
};

struct stmt_while : public stmt
{
    using ptr = std::unique_ptr<stmt_while>;

    expr::ptr test;
    stmt::ptr body;

    stmt_while(location const& loc, expr::ptr test, stmt::ptr body);
    XSK_ARC_AST_MAKE(stmt_while)
};

struct stmt_dowhile : public stmt
{
    using ptr = std::unique_ptr<stmt_dowhile>;

    expr::ptr test;
    stmt::ptr body;

    stmt_dowhile(location const& loc, expr::ptr test, stmt::ptr body);
    XSK_ARC_AST_MAKE(stmt_dowhile)
};

struct stmt_for : public stmt
{
    using ptr = std::unique_ptr<stmt_for>;

    stmt::ptr init;
    expr::ptr test;
    stmt::ptr iter;
    stmt::ptr body;

    stmt_for(location const& loc, stmt::ptr init, expr::ptr test, stmt::ptr iter, stmt::ptr body);
    XSK_ARC_AST_MAKE(stmt_for)
};

struct stmt_foreach : public stmt
{
    using ptr = std::unique_ptr<stmt_foreach>;

    expr::ptr container;
    expr::ptr value;
    expr::ptr array;
    expr::ptr key;
    stmt::ptr body;
    bool use_key;

    stmt_foreach(location const& loc, expr::ptr container, expr::ptr value, expr::ptr array, expr::ptr key, stmt::ptr body, bool use_key);
    XSK_ARC_AST_MAKE(stmt_foreach)
};

struct stmt_switch : public stmt
{
    using ptr = std::unique_ptr<stmt_switch>;

    expr::ptr test;
    stmt_comp::ptr body;

    stmt_switch(location const& loc, expr::ptr test, stmt_comp::ptr body);
    XSK_ARC_AST_MAKE(stmt_switch)
};

struct stmt_case : public stmt
{
    using ptr = std::unique_ptr<stmt_case>;

    expr::ptr value;
    stmt_list::ptr body;

    stmt_case(location const& loc, expr::ptr value);
    stmt_case(location const& loc, expr::ptr value, stmt_list::ptr body);
    XSK_ARC_AST_MAKE(stmt_case)
};

struct stmt_default : public stmt
{
    using ptr = std::unique_ptr<stmt_default>;

    stmt_list::ptr body;

    stmt_default(location const& loc);
    stmt_default(location const& loc, stmt_list::ptr body);
    XSK_ARC_AST_MAKE(stmt_default)
};

struct stmt_break : public stmt
{
    using ptr = std::unique_ptr<stmt_break>;

    stmt_break(location const& loc);
    XSK_ARC_AST_MAKE(stmt_break)
};

struct stmt_continue : public stmt
{
    using ptr = std::unique_ptr<stmt_continue>;

    stmt_continue(location const& loc);
    XSK_ARC_AST_MAKE(stmt_continue)
};

struct stmt_return : public stmt
{
    using ptr = std::unique_ptr<stmt_return>;

    expr::ptr value;

    stmt_return(location const& loc, expr::ptr value);
    XSK_ARC_AST_MAKE(stmt_return)
};

struct stmt_breakpoint : public stmt
{
    using ptr = std::unique_ptr<stmt_breakpoint>;

    stmt_breakpoint(location const& loc);
    XSK_ARC_AST_MAKE(stmt_breakpoint)
};

struct stmt_prof_begin : public stmt
{
    using ptr = std::unique_ptr<stmt_prof_begin>;

    expr_arguments::ptr args;

    stmt_prof_begin(location const& loc, expr_arguments::ptr args);
    XSK_ARC_AST_MAKE(stmt_prof_begin)
};

struct stmt_prof_end : public stmt
{
    using ptr = std::unique_ptr<stmt_prof_end>;

    expr_arguments::ptr args;

    stmt_prof_end(location const& loc, expr_arguments::ptr args);
    XSK_ARC_AST_MAKE(stmt_prof_end)
};

struct stmt_jmp : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp>;

    std::string value;

    stmt_jmp(location const& loc, std::string const& value);
    XSK_ARC_AST_MAKE(stmt_jmp)
};

struct stmt_jmp_back : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_back>;

    std::string value;

    stmt_jmp_back(location const& loc, std::string const& value);
    XSK_ARC_AST_MAKE(stmt_jmp_back)
};

struct stmt_jmp_cond : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_cond>;

    expr::ptr test;
    std::string value;

    stmt_jmp_cond(location const& loc, expr::ptr test, std::string const& value);
    XSK_ARC_AST_MAKE(stmt_jmp_cond)
};

struct stmt_jmp_true : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_true>;

    expr::ptr test;
    std::string value;

    stmt_jmp_true(location const& loc, expr::ptr test, std::string const& value);
    XSK_ARC_AST_MAKE(stmt_jmp_true)
};

struct stmt_jmp_false : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_false>;

    expr::ptr test;
    std::string value;

    stmt_jmp_false(location const& loc, expr::ptr test, std::string const& value);
    XSK_ARC_AST_MAKE(stmt_jmp_false)
};

struct stmt_jmp_switch : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_switch>;

    expr::ptr test;
    std::string value;

    stmt_jmp_switch(location const& loc, expr::ptr test, std::string const& value);
    XSK_ARC_AST_MAKE(stmt_jmp_switch)
};

struct stmt_jmp_endswitch : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_endswitch>;

    std::vector<std::string> data;

    stmt_jmp_endswitch(location const& loc, std::vector<std::string> data);
    XSK_ARC_AST_MAKE(stmt_jmp_endswitch)
};

struct stmt_jmp_dev : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_dev>;

    std::string value;

    stmt_jmp_dev(location const& loc, std::string const& value);
    XSK_ARC_AST_MAKE(stmt_jmp_dev)
};

struct decl_empty : public decl
{
    using ptr = std::unique_ptr<decl_empty>;

    decl_empty(location const& loc);
    XSK_ARC_AST_MAKE(decl_empty)
};

struct decl_function : public decl
{
    using ptr = std::unique_ptr<decl_function>;

    expr_identifier::ptr space;
    expr_identifier::ptr name;
    expr_parameters::ptr params;
    stmt_comp::ptr body;
    export_flags flags;

    decl_function(location const& loc, expr_identifier::ptr space, expr_identifier::ptr name, expr_parameters::ptr params, stmt_comp::ptr body, export_flags flags);
    XSK_ARC_AST_MAKE(decl_function)
};

struct decl_usingtree : public decl
{
    using ptr = std::unique_ptr<decl_usingtree>;

    expr_string::ptr name;

    decl_usingtree(location const& loc, expr_string::ptr name);
    XSK_ARC_AST_MAKE(decl_usingtree)
};

struct decl_namespace : public decl
{
    using ptr = std::unique_ptr<decl_namespace>;

    expr_string::ptr name;

    decl_namespace(location const& loc, expr_string::ptr name);
    XSK_ARC_AST_MAKE(decl_namespace)
};


struct decl_dev_begin : public decl
{
    using ptr = std::unique_ptr<decl_dev_begin>;

    decl_dev_begin(location const& loc);
    XSK_ARC_AST_MAKE(decl_dev_begin)
};

struct decl_dev_end : public decl
{
    using ptr = std::unique_ptr<decl_dev_end>;

    decl_dev_end(location const& loc);
    XSK_ARC_AST_MAKE(decl_dev_end)
};

struct include : public node
{
    using ptr = std::unique_ptr<include>;

    expr_path::ptr path;

    include(location const& loc, expr_path::ptr path);
    XSK_ARC_AST_MAKE(include)
};

struct program : public node
{
    using ptr = std::unique_ptr<program>;

    std::vector<include::ptr> includes;
    std::vector<decl::ptr> declarations;

    program();
    program(location const& loc);
    XSK_ARC_AST_MAKE(program)
};

#undef XSK_GSC_AST_MAKE

} // namespace xsk::arc
