// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

struct node
{
    using ptr = std::unique_ptr<node>;

    enum type
    {
        node_null,
        node_voidcodepos,
        node_prescriptcall,
        expr_empty,
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
        expr_binary,
        expr_ternary,
        expr_assign,
        expr_increment,
        expr_decrement,
        expr_var_create,
        expr_var_access,
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
        stmt_assert,
        stmt_assertex,
        stmt_assertmsg,
        stmt_create,
        stmt_remove,
        stmt_clear,
        stmt_jmp,
        stmt_jmp_back,
        stmt_jmp_cond,
        stmt_jmp_true,
        stmt_jmp_false,
        stmt_jmp_switch,
        stmt_jmp_endswitch,
        decl_empty,
        decl_function,
        decl_constant,
        decl_usingtree,
        decl_dev_begin,
        decl_dev_end,
        include,
        program,
    };

    node(node const&) = delete;
    node(node&&) = delete;
    auto operator=(node const&) -> node& = delete;
    auto operator=(node&&) -> node& = delete;
    virtual ~node() = default;

    auto kind() const -> type { return kind_; }
    auto loc() const -> location const& { return loc_; }
    auto label() const -> std::string { return loc_.label(); }

    auto is_special_stmt() -> bool;
    auto is_special_stmt_dev() -> bool;
    auto is_special_stmt_noif() -> bool;
    auto is_special_stmt_dev_noif() -> bool;
    auto is_assign() -> bool;

    virtual auto precedence() -> u8;

    template <typename T>
    static auto as(node::ptr /*unused*/) -> std::unique_ptr<T>;

protected:
    explicit node(const type t) : kind_(t) {}
    explicit node(const type t, location const& loc) : kind_(t), loc_(loc) {}

private:
    type kind_;
    location loc_;
};

struct expr : node
{
    using ptr = std::unique_ptr<expr>;

    friend auto operator==(expr const& lhs, expr const& rhs) -> bool;

    template <typename T>
    auto is() const -> bool;

    template <typename T>
    auto as() const -> T const&;

    template <typename T>
    auto as() -> T&;

protected:
    explicit expr(type t);
    expr(type t, location const& loc);
};

struct call : expr
{
    using ptr = std::unique_ptr<call>;

    enum class type { local, far, builtin };
    enum class mode { normal, thread, childthread, builtin };

    template <typename T>
    auto is() const -> bool;

    template <typename T>
    auto as() const -> T const&;

    template <typename T>
    auto as() -> T&;

protected:
    explicit call(node::type t);
    call(node::type t, location const& loc);
};

struct stmt : node
{
    using ptr = std::unique_ptr<stmt>;

    template <typename T>
    auto is() const -> bool;

    template <typename T>
    auto as() const -> T const&;

    template <typename T>
    auto as() -> T&;

protected:
    explicit stmt(type t);
    stmt(type t, location const& loc);
};

struct decl : node
{
    using ptr = std::unique_ptr<decl>;

    template <typename T>
    auto is() const -> bool;

    template <typename T>
    auto as() const -> T const&;

    template <typename T>
    auto as() -> T&;

protected:
    explicit decl(type t);
    decl(type t, location const& loc);
};

#define XSK_GSC_AST_MAKE(node_type)                                                    \
    template <class... Args>                                                            \
    inline static auto make(Args&&... args) -> std::unique_ptr<node_type>              \
    {                                                                                  \
        return std::unique_ptr<node_type>(new node_type(std::forward<Args>(args)...)); \
    }

struct node_prescriptcall final : public node
{
    using ptr = std::unique_ptr<node_prescriptcall>;

    explicit node_prescriptcall(location const& loc);
    XSK_GSC_AST_MAKE(node_prescriptcall)
};

struct node_voidcodepos final : public node
{
    using ptr = std::unique_ptr<node_voidcodepos>;

    explicit node_voidcodepos(location const& loc);
    XSK_GSC_AST_MAKE(node_voidcodepos)
};

struct expr_empty final : public expr
{
    using ptr = std::unique_ptr<expr_empty>;

    explicit expr_empty(location const& loc);
    friend auto operator==(expr_empty const& lhs, expr_empty const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_empty)
};

struct expr_true final : public expr
{
    using ptr = std::unique_ptr<expr_true>;

    explicit expr_true(location const& loc);
    friend auto operator==(expr_true const& lhs, expr_true const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_true)
};

struct expr_false final : public expr
{
    using ptr = std::unique_ptr<expr_false>;

    explicit expr_false(location const& loc);
    friend auto operator==(expr_false const& lhs, expr_false const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_false)
};

struct expr_integer final : public expr
{
    using ptr = std::unique_ptr<expr_integer>;

    std::string value;

    expr_integer(location const& loc, std::string value);
    friend auto operator==(expr_integer const& lhs, expr_integer const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_integer)
};

struct expr_float final : public expr
{
    using ptr = std::unique_ptr<expr_float>;

    std::string value;

    expr_float(location const& loc, std::string value);
    friend auto operator==(expr_float const& lhs, expr_float const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_float)
};

struct expr_vector final : public expr
{
    using ptr = std::unique_ptr<expr_vector>;

    expr::ptr x;
    expr::ptr y;
    expr::ptr z;

    expr_vector(location const& loc, expr::ptr x, expr::ptr y, expr::ptr z);
    friend auto operator==(expr_vector const& lhs, expr_vector const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_vector)
};

struct expr_string final : public expr
{
    using ptr = std::unique_ptr<expr_string>;

    std::string value;

    expr_string(location const& loc, std::string const& value);
    friend auto operator==(expr_string const& lhs, expr_string const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_string)
};

struct expr_istring final : public expr
{
    using ptr = std::unique_ptr<expr_istring>;

    std::string value;

    expr_istring(location const& loc, std::string value);
    friend auto operator==(expr_istring const& lhs, expr_istring const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_istring)
};

struct expr_path final : public expr
{
    using ptr = std::unique_ptr<expr_path>;

    std::string value;

    explicit expr_path(location const& loc);
    expr_path(location const& loc, std::string const& value);
    friend auto operator==(expr_path const& lhs, expr_path const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_path)
};

struct expr_identifier final : public expr
{
    using ptr = std::unique_ptr<expr_identifier>;

    std::string value;

    expr_identifier(location const& loc, std::string const& value);
    friend auto operator==(expr_identifier const& lhs, expr_identifier const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_identifier)
};

struct expr_animtree final : public expr
{
    using ptr = std::unique_ptr<expr_animtree>;

    explicit expr_animtree(location const& loc);
    friend auto operator==(expr_animtree const& lhs, expr_animtree const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_animtree)
};

struct expr_animation final : public expr
{
    using ptr = std::unique_ptr<expr_animation>;

    std::string value;

    expr_animation(location const& loc, std::string const& value);
    friend auto operator==(expr_animation const& lhs, expr_animation const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_animation)
};

struct expr_level final : public expr
{
    using ptr = std::unique_ptr<expr_level>;

    explicit expr_level(location const& loc);
    friend auto operator==(expr_level const& lhs, expr_level const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_level)
};

struct expr_anim final : public expr
{
    using ptr = std::unique_ptr<expr_anim>;

    explicit expr_anim(location const& loc);
    friend auto operator==(expr_anim const& lhs, expr_anim const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_anim)
};

struct expr_self final : public expr
{
    using ptr = std::unique_ptr<expr_self>;

    explicit expr_self(location const& loc);
    friend auto operator==(expr_self const& lhs, expr_self const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_self)
};

struct expr_game final : public expr
{
    using ptr = std::unique_ptr<expr_game>;

    explicit expr_game(location const& loc);
    friend auto operator==(expr_game const& lhs, expr_game const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_game)
};

struct expr_undefined final : public expr
{
    using ptr = std::unique_ptr<expr_undefined>;

    explicit expr_undefined(location const& loc);
    friend auto operator==(expr_undefined const& lhs, expr_undefined const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_undefined)
};

struct expr_empty_array final : public expr
{
    using ptr = std::unique_ptr<expr_empty_array>;

    explicit expr_empty_array(location const& loc);
    friend auto operator==(expr_empty_array const& lhs, expr_empty_array const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_empty_array)
};

struct expr_thisthread final : public expr
{
    using ptr = std::unique_ptr<expr_thisthread>;

    explicit expr_thisthread(location const& loc);
    friend auto operator==(expr_thisthread const& lhs, expr_thisthread const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_thisthread)
};

struct expr_paren final : public expr
{
    using ptr = std::unique_ptr<expr_paren>;

    expr::ptr value;

    expr_paren(location const& loc, expr::ptr value);
    friend auto operator==(expr_paren const& lhs, expr_paren const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_paren)
};

struct expr_size final : public expr
{
    using ptr = std::unique_ptr<expr_size>;

    expr::ptr obj;

    expr_size(location const& loc, expr::ptr obj);
    friend auto operator==(expr_size const& lhs, expr_size const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_size)
};

struct expr_field final : public expr
{
    using ptr = std::unique_ptr<expr_field>;

    expr::ptr obj;
    expr_identifier::ptr field;

    expr_field(location const& loc, expr::ptr obj, expr_identifier::ptr field);
    friend auto operator==(expr_field const& lhs, expr_field const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_field)
};

struct expr_array final : public expr
{
    using ptr = std::unique_ptr<expr_array>;

    expr::ptr obj;
    expr::ptr key;

    expr_array(location const& loc, expr::ptr obj, expr::ptr key);
    friend auto operator==(expr_array const& lhs, expr_array const& rhs) -> bool;
    XSK_GSC_AST_MAKE(expr_array)
};

struct expr_tuple final : public expr
{
    using ptr = std::unique_ptr<expr_tuple>;

    std::vector<expr::ptr> list;
    expr::ptr temp;

    explicit expr_tuple(location const& loc);
    XSK_GSC_AST_MAKE(expr_tuple)
};

struct expr_reference final : public expr
{
    using ptr = std::unique_ptr<expr_reference>;

    expr_path::ptr path;
    expr_identifier::ptr name;

    expr_reference(location const& loc, expr_path::ptr path, expr_identifier::ptr name);
    XSK_GSC_AST_MAKE(expr_reference)
};

struct expr_istrue final : public expr
{
    using ptr = std::unique_ptr<expr_istrue>;

    expr::ptr value;

    expr_istrue(location const& loc, expr::ptr value);
    XSK_GSC_AST_MAKE(expr_istrue)
};

struct expr_isdefined final : public expr
{
    using ptr = std::unique_ptr<expr_isdefined>;

    expr::ptr value;

    expr_isdefined(location const& loc, expr::ptr value);
    XSK_GSC_AST_MAKE(expr_isdefined)
};

struct expr_arguments final : public expr
{
    using ptr = std::unique_ptr<expr_arguments>;

    std::vector<expr::ptr> list;

    explicit expr_arguments(location const& loc);
    XSK_GSC_AST_MAKE(expr_arguments)
};

struct expr_parameters final : public expr
{
    using ptr = std::unique_ptr<expr_parameters>;

    std::vector<expr_identifier::ptr> list;

    explicit expr_parameters(location const& loc);
    XSK_GSC_AST_MAKE(expr_parameters)
};

struct expr_add_array final : public expr
{
    using ptr = std::unique_ptr<expr_add_array>;

    expr_arguments::ptr args;

    expr_add_array(location const& loc, expr_arguments::ptr args);
    XSK_GSC_AST_MAKE(expr_add_array)
};

struct expr_pointer final : public call
{
    using ptr = std::unique_ptr<expr_pointer>;

    expr::ptr func;
    expr_arguments::ptr args;
    call::mode mode;

    expr_pointer(location const& loc, expr::ptr func, expr_arguments::ptr args, call::mode mode);
    XSK_GSC_AST_MAKE(expr_pointer)
};

struct expr_function final : public call
{
    using ptr = std::unique_ptr<expr_function>;

    expr_path::ptr path;
    expr_identifier::ptr name;
    expr_arguments::ptr args;
    call::mode mode;

    expr_function(location const& loc, expr_path::ptr path, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode);
    XSK_GSC_AST_MAKE(expr_function)
};

struct expr_method final : public expr
{
    using ptr = std::unique_ptr<expr_method>;

    expr::ptr obj;
    call::ptr value;

    expr_method(location const& loc, expr::ptr obj, call::ptr value);
    XSK_GSC_AST_MAKE(expr_method)
};

struct expr_call final : public expr
{
    using ptr = std::unique_ptr<expr_call>;

    call::ptr value;

    expr_call(location const& loc, call::ptr value);
    XSK_GSC_AST_MAKE(expr_call)
};

struct expr_complement final : public expr
{
    using ptr = std::unique_ptr<expr_complement>;

    expr::ptr rvalue;

    expr_complement(location const& loc, expr::ptr rvalue);
    XSK_GSC_AST_MAKE(expr_complement)
};

struct expr_negate final : public expr
{
    using ptr = std::unique_ptr<expr_negate>;

    expr::ptr rvalue;

    expr_negate(location const& loc, expr::ptr rvalue);
    XSK_GSC_AST_MAKE(expr_negate)
};

struct expr_not final : public expr
{
    using ptr = std::unique_ptr<expr_not>;

    expr::ptr rvalue;

    expr_not(location const& loc, expr::ptr rvalue);
    XSK_GSC_AST_MAKE(expr_not)
};

struct expr_binary final : public expr
{
    using ptr = std::unique_ptr<expr_binary>;

    enum class op { eq, ne, le, ge, lt, gt, add, sub, mul, div, mod, shl, shr, bwor, bwand, bwexor, bool_or, bool_and };

    expr::ptr lvalue;
    expr::ptr rvalue;
    op oper;

    expr_binary(location const& loc, expr::ptr lvalue, expr::ptr rvalue, op oper);
    XSK_GSC_AST_MAKE(expr_binary)
    auto precedence() -> u8 override;
};

struct expr_ternary final : public expr
{
    using ptr = std::unique_ptr<expr_ternary>;

    expr::ptr test;
    expr::ptr true_expr;
    expr::ptr false_expr;

    expr_ternary(location const& loc, expr::ptr test, expr::ptr true_expr, expr::ptr false_expr);
    XSK_GSC_AST_MAKE(expr_ternary)
};

struct expr_assign final : public expr
{
    using ptr = std::unique_ptr<expr_assign>;

    enum class op { eq, add, sub, mul, div, mod, shl, shr, bwor, bwand, bwexor };

    expr::ptr lvalue;
    expr::ptr rvalue;
    op oper;

    expr_assign(location const& loc, expr::ptr lvalue, expr::ptr rvalue, op oper);
    XSK_GSC_AST_MAKE(expr_assign)
};

struct expr_increment final : expr
{
    using ptr = std::unique_ptr<expr_increment>;

    expr::ptr lvalue;
    bool prefix;

    expr_increment(location const& loc, expr::ptr lvalue, bool prefix);
    XSK_GSC_AST_MAKE(expr_increment)
};

struct expr_decrement final : expr
{
    using ptr = std::unique_ptr<expr_decrement>;

    expr::ptr lvalue;
    bool prefix;

    expr_decrement(location const& loc, expr::ptr lvalue, bool prefix);
    XSK_GSC_AST_MAKE(expr_decrement)
};

struct expr_var_create final : public expr
{
    using ptr = std::unique_ptr<expr_var_create>;

    std::string index;
    std::vector<std::string> vars;

    expr_var_create(location const& loc, std::string const& index);
    XSK_GSC_AST_MAKE(expr_var_create)
};

struct expr_var_access final : public expr
{
    using ptr = std::unique_ptr<expr_var_access>;

    std::string index;

    expr_var_access(location const& loc, std::string const& index);
    XSK_GSC_AST_MAKE(expr_var_access)
};

struct stmt_empty final : public stmt
{
    using ptr = std::unique_ptr<stmt_empty>;

    explicit stmt_empty(location const& loc);
    XSK_GSC_AST_MAKE(stmt_empty)
};

struct stmt_list final : public stmt
{
    using ptr = std::unique_ptr<stmt_list>;

    std::vector<stmt::ptr> list;

    explicit stmt_list(location const& loc);
    XSK_GSC_AST_MAKE(stmt_list)
};

struct stmt_comp final : public stmt
{
    using ptr = std::unique_ptr<stmt_comp>;

    stmt_list::ptr block;

    stmt_comp(location const& loc, stmt_list::ptr block);
    XSK_GSC_AST_MAKE(stmt_comp)
};

struct stmt_dev final : public stmt
{
    using ptr = std::unique_ptr<stmt_dev>;

    stmt_list::ptr block;

    stmt_dev(location const& loc, stmt_list::ptr block);
    XSK_GSC_AST_MAKE(stmt_dev)
};

struct stmt_expr final : public stmt
{
    using ptr = std::unique_ptr<stmt_expr>;

    expr::ptr value;

    stmt_expr(location const& loc, expr::ptr value);
    XSK_GSC_AST_MAKE(stmt_expr)
};

struct stmt_endon final : public stmt
{
    using ptr = std::unique_ptr<stmt_endon>;

    expr::ptr obj;
    expr::ptr event;

    stmt_endon(location const& loc, expr::ptr obj, expr::ptr event);
    XSK_GSC_AST_MAKE(stmt_endon)
};

struct stmt_notify final : public stmt
{
    using ptr = std::unique_ptr<stmt_notify>;

    expr::ptr obj;
    expr::ptr event;
    expr_arguments::ptr args;

    stmt_notify(location const& loc, expr::ptr obj, expr::ptr event, expr_arguments::ptr args);
    XSK_GSC_AST_MAKE(stmt_notify)
};

struct stmt_wait final : public stmt
{
    using ptr = std::unique_ptr<stmt_wait>;

    expr::ptr time;

    stmt_wait(location const& loc, expr::ptr time);
    XSK_GSC_AST_MAKE(stmt_wait)
};

struct stmt_waittill final : public stmt
{
    using ptr = std::unique_ptr<stmt_waittill>;

    expr::ptr obj;
    expr::ptr event;
    expr_arguments::ptr args;

    stmt_waittill(location const& loc, expr::ptr obj, expr::ptr event, expr_arguments::ptr args);
    XSK_GSC_AST_MAKE(stmt_waittill)
};

struct stmt_waittillmatch final : public stmt
{
    using ptr = std::unique_ptr<stmt_waittillmatch>;

    expr::ptr obj;
    expr::ptr event;
    expr_arguments::ptr args;

    stmt_waittillmatch(location const& loc, expr::ptr obj, expr::ptr event, expr_arguments::ptr args);
    XSK_GSC_AST_MAKE(stmt_waittillmatch)
};

struct stmt_waittillframeend final : public stmt
{
    using ptr = std::unique_ptr<stmt_waittillframeend>;

    explicit stmt_waittillframeend(location const& loc);
    XSK_GSC_AST_MAKE(stmt_waittillframeend)
};

struct stmt_waitframe final : public stmt
{
    using ptr = std::unique_ptr<stmt_waitframe>;

    explicit stmt_waitframe(location const& loc);
    XSK_GSC_AST_MAKE(stmt_waitframe)
};

struct stmt_if final : public stmt
{
    using ptr = std::unique_ptr<stmt_if>;

    expr::ptr test;
    stmt::ptr body;

    stmt_if(location const& loc, expr::ptr test, stmt::ptr body);
    XSK_GSC_AST_MAKE(stmt_if)
};

struct stmt_ifelse final : public stmt
{
    using ptr = std::unique_ptr<stmt_ifelse>;

    expr::ptr test;
    stmt::ptr stmt_if;
    stmt::ptr stmt_else;

    stmt_ifelse(location const& loc, expr::ptr test, stmt::ptr stmt_if, stmt::ptr stmt_else);
    XSK_GSC_AST_MAKE(stmt_ifelse)
};

struct stmt_while final : public stmt
{
    using ptr = std::unique_ptr<stmt_while>;

    expr::ptr test;
    stmt::ptr body;

    stmt_while(location const& loc, expr::ptr test, stmt::ptr body);
    XSK_GSC_AST_MAKE(stmt_while)
};

struct stmt_dowhile final : public stmt
{
    using ptr = std::unique_ptr<stmt_dowhile>;

    expr::ptr test;
    stmt::ptr body;

    stmt_dowhile(location const& loc, expr::ptr test, stmt::ptr body);
    XSK_GSC_AST_MAKE(stmt_dowhile)
};

struct stmt_for final : public stmt
{
    using ptr = std::unique_ptr<stmt_for>;

    stmt::ptr init;
    expr::ptr test;
    stmt::ptr iter;
    stmt::ptr body;

    stmt_for(location const& loc, stmt::ptr init, expr::ptr test, stmt::ptr iter, stmt::ptr body);
    XSK_GSC_AST_MAKE(stmt_for)
};

struct stmt_foreach final : public stmt
{
    using ptr = std::unique_ptr<stmt_foreach>;

    expr::ptr container;
    expr::ptr value;
    expr::ptr index;
    expr::ptr array;
    expr::ptr key;
    stmt::ptr body;
    bool use_key;

    stmt_foreach(location const& loc, expr::ptr container, expr::ptr value, expr::ptr index, expr::ptr array, expr::ptr key, stmt::ptr body, bool use_key);
    XSK_GSC_AST_MAKE(stmt_foreach)
};

struct stmt_switch final : public stmt
{
    using ptr = std::unique_ptr<stmt_switch>;

    expr::ptr test;
    stmt_comp::ptr body;

    stmt_switch(location const& loc, expr::ptr test, stmt_comp::ptr body);
    XSK_GSC_AST_MAKE(stmt_switch)
};

struct stmt_case final : public stmt
{
    using ptr = std::unique_ptr<stmt_case>;

    expr::ptr value;
    stmt_list::ptr body;

    stmt_case(location const& loc, expr::ptr value);
    stmt_case(location const& loc, expr::ptr value, stmt_list::ptr body);
    XSK_GSC_AST_MAKE(stmt_case)
};

struct stmt_default final : public stmt
{
    using ptr = std::unique_ptr<stmt_default>;

    stmt_list::ptr body;

    explicit stmt_default(location const& loc);
    stmt_default(location const& loc, stmt_list::ptr body);
    XSK_GSC_AST_MAKE(stmt_default)
};

struct stmt_break final : public stmt
{
    using ptr = std::unique_ptr<stmt_break>;

    explicit stmt_break(location const& loc);
    XSK_GSC_AST_MAKE(stmt_break)
};

struct stmt_continue final : public stmt
{
    using ptr = std::unique_ptr<stmt_continue>;

    explicit stmt_continue(location const& loc);
    XSK_GSC_AST_MAKE(stmt_continue)
};

struct stmt_return final : public stmt
{
    using ptr = std::unique_ptr<stmt_return>;

    expr::ptr value;

    stmt_return(location const& loc, expr::ptr value);
    XSK_GSC_AST_MAKE(stmt_return)
};

struct stmt_breakpoint final : public stmt
{
    using ptr = std::unique_ptr<stmt_breakpoint>;

    explicit stmt_breakpoint(location const& loc);
    XSK_GSC_AST_MAKE(stmt_breakpoint)
};

struct stmt_prof_begin final : public stmt
{
    using ptr = std::unique_ptr<stmt_prof_begin>;

    expr_arguments::ptr args;

    stmt_prof_begin(location const& loc, expr_arguments::ptr args);
    XSK_GSC_AST_MAKE(stmt_prof_begin)
};

struct stmt_prof_end final : public stmt
{
    using ptr = std::unique_ptr<stmt_prof_end>;

    expr_arguments::ptr args;

    stmt_prof_end(location const& loc, expr_arguments::ptr args);
    XSK_GSC_AST_MAKE(stmt_prof_end)
};

struct stmt_assert final : public stmt
{
    using ptr = std::unique_ptr<stmt_assert>;

    expr_arguments::ptr args;

    stmt_assert(location const& loc, expr_arguments::ptr args);
    XSK_GSC_AST_MAKE(stmt_assert)
};

struct stmt_assertex final : public stmt
{
    using ptr = std::unique_ptr<stmt_assertex>;

    expr_arguments::ptr args;

    stmt_assertex(location const& loc, expr_arguments::ptr args);
    XSK_GSC_AST_MAKE(stmt_assertex)
};

struct stmt_assertmsg final : public stmt
{
    using ptr = std::unique_ptr<stmt_assertmsg>;

    expr_arguments::ptr args;

    stmt_assertmsg(location const& loc, expr_arguments::ptr args);
    XSK_GSC_AST_MAKE(stmt_assertmsg)
};

struct stmt_create final : public stmt
{
    using ptr = std::unique_ptr<stmt_create>;

    std::string index;
    std::vector<std::string> vars;

    stmt_create(location const& loc, std::string const& index);
    XSK_GSC_AST_MAKE(stmt_create)
};

struct stmt_remove final : public stmt
{
    using ptr = std::unique_ptr<stmt_remove>;

    std::string index;

    stmt_remove(location const& loc, std::string const& index);
    XSK_GSC_AST_MAKE(stmt_remove)
};

struct stmt_clear final : public stmt
{
    using ptr = std::unique_ptr<stmt_clear>;

    std::string index;

    stmt_clear(location const& loc, std::string const& index);
    XSK_GSC_AST_MAKE(stmt_clear)
};

struct stmt_jmp final : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp>;

    std::string value;

    stmt_jmp(location const& loc, std::string const& value);
    XSK_GSC_AST_MAKE(stmt_jmp)
};

struct stmt_jmp_back final : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_back>;

    std::string value;

    stmt_jmp_back(location const& loc, std::string const& value);
    XSK_GSC_AST_MAKE(stmt_jmp_back)
};

struct stmt_jmp_cond final : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_cond>;

    expr::ptr test;
    std::string value;

    stmt_jmp_cond(location const& loc, expr::ptr test, std::string const& value);
    XSK_GSC_AST_MAKE(stmt_jmp_cond)
};

struct stmt_jmp_true final : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_true>;

    expr::ptr test;
    std::string value;

    stmt_jmp_true(location const& loc, expr::ptr test, std::string const& value);
    XSK_GSC_AST_MAKE(stmt_jmp_true)
};

struct stmt_jmp_false final : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_false>;

    expr::ptr test;
    std::string value;

    stmt_jmp_false(location const& loc, expr::ptr test, std::string const& value);
    XSK_GSC_AST_MAKE(stmt_jmp_false)
};

struct stmt_jmp_switch final : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_switch>;

    expr::ptr test;
    std::string value;

    stmt_jmp_switch(location const& loc, expr::ptr test, std::string const& value);
    XSK_GSC_AST_MAKE(stmt_jmp_switch)
};

struct stmt_jmp_endswitch final : public stmt
{
    using ptr = std::unique_ptr<stmt_jmp_endswitch>;

    std::vector<std::string> data;

    stmt_jmp_endswitch(location const& loc, std::vector<std::string> data);
    XSK_GSC_AST_MAKE(stmt_jmp_endswitch)
};

struct decl_empty final : public decl
{
    using ptr = std::unique_ptr<decl_empty>;

    explicit decl_empty(location const& loc);
    XSK_GSC_AST_MAKE(decl_empty)
};

struct decl_function final : public decl
{
    using ptr = std::unique_ptr<decl_function>;

    expr_identifier::ptr name;
    expr_parameters::ptr params;
    stmt_comp::ptr body;

    decl_function(location const& loc, expr_identifier::ptr name, expr_parameters::ptr params, stmt_comp::ptr body);
    XSK_GSC_AST_MAKE(decl_function)
};

struct decl_constant final : public decl
{
    using ptr = std::unique_ptr<decl_constant>;

    expr_identifier::ptr name;
    expr::ptr value;

    decl_constant(location const& loc, expr_identifier::ptr name, expr::ptr value);
    XSK_GSC_AST_MAKE(decl_constant)
};

struct decl_usingtree final : public decl
{
    using ptr = std::unique_ptr<decl_usingtree>;

    expr_string::ptr name;

    decl_usingtree(location const& loc, expr_string::ptr name);
    XSK_GSC_AST_MAKE(decl_usingtree)
};

struct decl_dev_begin final : public decl
{
    using ptr = std::unique_ptr<decl_dev_begin>;

    explicit decl_dev_begin(location const& loc);
    XSK_GSC_AST_MAKE(decl_dev_begin)
};

struct decl_dev_end final : public decl
{
    using ptr = std::unique_ptr<decl_dev_end>;

    explicit decl_dev_end(location const& loc);
    XSK_GSC_AST_MAKE(decl_dev_end)
};

struct include final : public node
{
    using ptr = std::unique_ptr<include>;

    expr_path::ptr path;

    include(location const& loc, expr_path::ptr path);
    XSK_GSC_AST_MAKE(include)
};

struct program final : public node
{
    using ptr = std::unique_ptr<program>;

    std::vector<include::ptr> includes;
    std::vector<decl::ptr> declarations;

    program();
    explicit program(location const& loc);
    XSK_GSC_AST_MAKE(program)
};

#undef XSK_GSC_AST_MAKE

} // namespace xsk::gsc
