// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/common/location.hpp"
#include "xsk/gsc/common/ast.hpp"

namespace xsk::gsc
{

auto node::is_special_stmt() -> bool
{
    switch (kind_)
    {
        case type::stmt_if:
        case type::stmt_ifelse:
        case type::stmt_while:
        case type::stmt_for:
        case type::stmt_foreach:
        case type::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_special_stmt_dev() -> bool
{
    switch (kind_)
    {
        case type::stmt_dev:
        case type::stmt_if:
        case type::stmt_ifelse:
        case type::stmt_while:
        case type::stmt_for:
        case type::stmt_foreach:
        case type::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_special_stmt_noif() -> bool
{
    switch (kind_)
    {
        case type::stmt_while:
        case type::stmt_for:
        case type::stmt_foreach:
        case type::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_special_stmt_dev_noif() -> bool
{
    switch (kind_)
    {
        case type::stmt_dev:
        case type::stmt_while:
        case type::stmt_for:
        case type::stmt_foreach:
        case type::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_assign() -> bool
{
    switch (kind_)
    {
        case type::expr_assign:
        case type::expr_increment:
        case type::expr_decrement:
            return true;
        default:
            return false;
    }
}

auto node::precedence() -> u8
{
    return 0;
}

auto expr_binary::precedence() -> u8
{
    switch (oper)
    {
        case op::bool_or:  return 1;
        case op::bool_and: return 2;
        case op::bwor:     return 3;
        case op::bwexor:   return 4;
        case op::bwand:    return 5;
        case op::eq:       return 6;
        case op::ne:       return 6;
        case op::lt:       return 7;
        case op::gt:       return 7;
        case op::le:       return 7;
        case op::ge:       return 7;
        case op::shl:      return 8;
        case op::shr:      return 8;
        case op::add:      return 9;
        case op::sub:      return 9;
        case op::mul:      return 10;
        case op::div:      return 10;
        case op::mod:      return 10;
        default: return 0;
    }
}

template<typename T>
auto node::as(node::ptr) -> std::unique_ptr<T>
{
    static_assert(std::is_same_v<T, node>, "invalid cast");
}

template<>
auto node::as(node::ptr from) -> std::unique_ptr<expr>
{
    return std::unique_ptr<expr>(static_cast<expr*>(from.release()));
}

template<>
auto node::as(node::ptr from) -> std::unique_ptr<stmt>
{
    return std::unique_ptr<stmt>(static_cast<stmt*>(from.release()));
}

expr::expr(type t) : node{ t } {}
expr::expr(type t, location const& loc) : node{ t, loc } {}

template<typename T>
auto expr::is() const -> bool
{
    static_assert(std::is_same_v<T, expr>, "invalid test");
}

template<typename T>
auto expr::as() const -> T const&
{
    static_assert(std::is_same_v<T, expr>, "invalid cast");
}

template<typename T>
auto expr::as() -> T&
{
    static_assert(std::is_same_v<T, expr>, "invalid cast");
}

call::call(node::type t) : expr{ t } {}
call::call(node::type t, location const& loc) : expr{ t, loc } {}

template<typename T>
auto call::is() const -> bool
{
    static_assert(std::is_same_v<T, call>, "invalid test");
}

template<typename T>
auto call::as() const -> T const&
{
    static_assert(std::is_same_v<T, call>, "invalid cast");
}

template<typename T>
auto call::as() -> T&
{
    static_assert(std::is_same_v<T, call>, "invalid cast");
}

stmt::stmt(type t) : node{ t } {}
stmt::stmt(type t, location const& loc) : node{ t, loc } {}

template<typename T>
auto stmt::is() const -> bool
{
    static_assert(std::is_same_v<T, stmt>, "invalid test");
}

template<typename T>
auto stmt::as() const -> T const&
{
    static_assert(std::is_same_v<T, stmt>, "invalid cast");
}

template<typename T>
auto stmt::as() -> T&
{
    static_assert(std::is_same_v<T, stmt>, "invalid cast");
}

decl::decl(type t) : node{ t } {}
decl::decl(type t, location const& loc) : node{ t, loc } {}

template<typename T>
auto decl::is() const -> bool
{
    static_assert(std::is_same_v<T, decl>, "invalid test");
}

template<typename T>
auto decl::as() const -> T const&
{
    static_assert(std::is_same_v<T, decl>, "invalid cast");
}

template<typename T>
auto decl::as() -> T&
{
    static_assert(std::is_same_v<T, decl>, "invalid cast");
}

#define XSK_GSC_EXPR_IS(expr_type)                                    \
template<>                                                            \
auto expr::is<gsc::expr_type>() const -> bool                         \
{                                                                     \
    return kind() == type::expr_type;                                 \
}                                                                     \
                                                                      \
template<>                                                            \
auto expr::as<gsc::expr_type>() -> gsc::expr_type &                   \
{                                                                     \
    return static_cast<gsc::expr_type &>(*this);                      \
}                                                                     \
                                                                      \
template<>                                                            \
auto expr::as<gsc::expr_type>() const -> gsc::expr_type const&        \
{                                                                     \
    return static_cast<gsc::expr_type const&>(*this);                 \
}                                                                     \

#define XSK_GSC_CALL_IS(expr_type)                                    \
template<>                                                            \
auto call::is<gsc::expr_type>() const -> bool                         \
{                                                                     \
    return kind() == node::type::expr_type;                           \
}                                                                     \
                                                                      \
template<>                                                            \
auto call::as<gsc::expr_type>() -> gsc::expr_type &                   \
{                                                                     \
    return static_cast<gsc::expr_type &>(*this);                      \
}                                                                     \
                                                                      \
template<>                                                            \
auto call::as<gsc::expr_type>() const -> gsc::expr_type const&        \
{                                                                     \
    return static_cast<gsc::expr_type const&>(*this);                 \
}                                                                     \

#define XSK_GSC_STMT_IS(expr_type)                                    \
template<>                                                            \
auto stmt::is<gsc::expr_type>() const -> bool                         \
{                                                                     \
    return kind() == type::expr_type;                                 \
}                                                                     \
                                                                      \
template<>                                                            \
auto stmt::as<gsc::expr_type>() -> gsc::expr_type &                   \
{                                                                     \
    return static_cast<gsc::expr_type &>(*this);                      \
}                                                                     \
                                                                      \
template<>                                                            \
auto stmt::as<gsc::expr_type>() const -> gsc::expr_type const&        \
{                                                                     \
    return static_cast<gsc::expr_type const&>(*this);                 \
}                                                                     \

#define XSK_GSC_DECL_IS(expr_type)                                    \
template<>                                                            \
auto decl::is<gsc::expr_type>() const -> bool                         \
{                                                                     \
    return kind() == type::expr_type;                                 \
}                                                                     \
                                                                      \
template<>                                                            \
auto decl::as<gsc::expr_type>() -> gsc::expr_type &                   \
{                                                                     \
    return static_cast<gsc::expr_type &>(*this);                      \
}                                                                     \
                                                                      \
template<>                                                            \
auto decl::as<gsc::expr_type>() const -> gsc::expr_type const&        \
{                                                                     \
    return static_cast<gsc::expr_type const&>(*this);                 \
}                                                                     \

XSK_GSC_EXPR_IS(expr_empty)
XSK_GSC_EXPR_IS(expr_true)
XSK_GSC_EXPR_IS(expr_false)
XSK_GSC_EXPR_IS(expr_integer)
XSK_GSC_EXPR_IS(expr_float)
XSK_GSC_EXPR_IS(expr_vector)
XSK_GSC_EXPR_IS(expr_string)
XSK_GSC_EXPR_IS(expr_istring)
XSK_GSC_EXPR_IS(expr_path)
XSK_GSC_EXPR_IS(expr_identifier)
XSK_GSC_EXPR_IS(expr_animtree)
XSK_GSC_EXPR_IS(expr_animation)
XSK_GSC_EXPR_IS(expr_level)
XSK_GSC_EXPR_IS(expr_anim)
XSK_GSC_EXPR_IS(expr_self)
XSK_GSC_EXPR_IS(expr_game)
XSK_GSC_EXPR_IS(expr_undefined)
XSK_GSC_EXPR_IS(expr_empty_array)
XSK_GSC_EXPR_IS(expr_thisthread)
XSK_GSC_EXPR_IS(expr_paren)
XSK_GSC_EXPR_IS(expr_size)
XSK_GSC_EXPR_IS(expr_field)
XSK_GSC_EXPR_IS(expr_array)
XSK_GSC_EXPR_IS(expr_tuple)
XSK_GSC_EXPR_IS(expr_reference)
XSK_GSC_EXPR_IS(expr_istrue)
XSK_GSC_EXPR_IS(expr_isdefined)
XSK_GSC_EXPR_IS(expr_arguments)
XSK_GSC_EXPR_IS(expr_parameters)
XSK_GSC_EXPR_IS(expr_add_array)
XSK_GSC_EXPR_IS(expr_pointer)
XSK_GSC_EXPR_IS(expr_function)
XSK_GSC_EXPR_IS(expr_method)
XSK_GSC_EXPR_IS(expr_call)
XSK_GSC_EXPR_IS(expr_complement)
XSK_GSC_EXPR_IS(expr_negate)
XSK_GSC_EXPR_IS(expr_not)
XSK_GSC_EXPR_IS(expr_binary)
XSK_GSC_EXPR_IS(expr_ternary)
XSK_GSC_EXPR_IS(expr_increment)
XSK_GSC_EXPR_IS(expr_decrement)
XSK_GSC_EXPR_IS(expr_assign)
XSK_GSC_EXPR_IS(expr_var_create)
XSK_GSC_EXPR_IS(expr_var_access)

XSK_GSC_CALL_IS(expr_pointer)
XSK_GSC_CALL_IS(expr_function)

XSK_GSC_STMT_IS(stmt_empty)
XSK_GSC_STMT_IS(stmt_list)
XSK_GSC_STMT_IS(stmt_comp)
XSK_GSC_STMT_IS(stmt_dev)
XSK_GSC_STMT_IS(stmt_expr)
XSK_GSC_STMT_IS(stmt_endon)
XSK_GSC_STMT_IS(stmt_notify)
XSK_GSC_STMT_IS(stmt_wait)
XSK_GSC_STMT_IS(stmt_waittill)
XSK_GSC_STMT_IS(stmt_waittillmatch)
XSK_GSC_STMT_IS(stmt_waittillframeend)
XSK_GSC_STMT_IS(stmt_waitframe)
XSK_GSC_STMT_IS(stmt_if)
XSK_GSC_STMT_IS(stmt_ifelse)
XSK_GSC_STMT_IS(stmt_while)
XSK_GSC_STMT_IS(stmt_dowhile)
XSK_GSC_STMT_IS(stmt_for)
XSK_GSC_STMT_IS(stmt_foreach)
XSK_GSC_STMT_IS(stmt_switch)
XSK_GSC_STMT_IS(stmt_case)
XSK_GSC_STMT_IS(stmt_default)
XSK_GSC_STMT_IS(stmt_break)
XSK_GSC_STMT_IS(stmt_continue)
XSK_GSC_STMT_IS(stmt_return)
XSK_GSC_STMT_IS(stmt_breakpoint)
XSK_GSC_STMT_IS(stmt_prof_begin)
XSK_GSC_STMT_IS(stmt_prof_end)
XSK_GSC_STMT_IS(stmt_assert)
XSK_GSC_STMT_IS(stmt_assertex)
XSK_GSC_STMT_IS(stmt_assertmsg)
XSK_GSC_STMT_IS(stmt_create)
XSK_GSC_STMT_IS(stmt_remove)
XSK_GSC_STMT_IS(stmt_clear)
XSK_GSC_STMT_IS(stmt_jmp)
XSK_GSC_STMT_IS(stmt_jmp_back)
XSK_GSC_STMT_IS(stmt_jmp_cond)
XSK_GSC_STMT_IS(stmt_jmp_true)
XSK_GSC_STMT_IS(stmt_jmp_false)
XSK_GSC_STMT_IS(stmt_jmp_switch)
XSK_GSC_STMT_IS(stmt_jmp_endswitch)

XSK_GSC_DECL_IS(decl_empty)
XSK_GSC_DECL_IS(decl_function)
XSK_GSC_DECL_IS(decl_constant)
XSK_GSC_DECL_IS(decl_usingtree)
XSK_GSC_DECL_IS(decl_dev_begin)
XSK_GSC_DECL_IS(decl_dev_end)

node_prescriptcall::node_prescriptcall(location const& loc) : node{ type::node_prescriptcall, loc }
{
}

node_voidcodepos::node_voidcodepos(location const& loc) : node{ type::node_voidcodepos, loc }
{
}

expr_empty::expr_empty(location const& loc) : expr{ type::expr_empty, loc }
{
}

expr_true::expr_true(location const& loc) : expr{ type::expr_true, loc }
{
}

expr_false::expr_false(location const& loc) : expr{ type::expr_false, loc }
{
}

expr_integer::expr_integer(location const& loc, std::string const& value) : expr{ type::expr_integer, loc }, value{ std::move(value) }
{
}

expr_float::expr_float(location const& loc, std::string const& value) : expr{ type::expr_float, loc }, value{ std::move(value) }
{
}

expr_vector::expr_vector(location const& loc, expr::ptr x, expr::ptr y, expr::ptr z) : expr{ type::expr_vector, loc }, x{ std::move(x) }, y{ std::move(y) }, z{ std::move(z) }
{
}

expr_string::expr_string(location const& loc, const std::string& value) : expr{ type::expr_string, loc }, value{ value }
{
}

expr_istring::expr_istring(location const& loc, const std::string& value) : expr{ type::expr_istring, loc }, value{ std::move(value) }
{
}

expr_path::expr_path(location const& loc) : expr{ type::expr_path, loc }
{
}

expr_path::expr_path(location const& loc, std::string const& value) : expr{ type::expr_path, loc }, value{ value }
{
}

expr_identifier::expr_identifier(location const& loc, std::string const& value) : expr{ type::expr_identifier, loc }, value{ value }
{
}

expr_animtree::expr_animtree(location const& loc) : expr{ type::expr_animtree, loc }
{
}

expr_animation::expr_animation(location const& loc, std::string const& value) : expr{ type::expr_animation, loc }, value{ value }
{
}

expr_level::expr_level(location const& loc) : expr{ type::expr_level, loc }
{
}

expr_anim::expr_anim(location const& loc) : expr{ type::expr_anim, loc }
{
}

expr_self::expr_self(location const& loc) : expr{ type::expr_self, loc }
{
}

expr_game::expr_game(location const& loc) : expr{ type::expr_game, loc }
{
}

expr_undefined::expr_undefined(location const& loc) : expr{ type::expr_undefined, loc }
{
}

expr_empty_array::expr_empty_array(location const& loc) : expr{ type::expr_empty_array, loc }
{
}

expr_thisthread::expr_thisthread(location const& loc) : expr{ type::expr_thisthread, loc }
{
}

expr_paren::expr_paren(location const& loc, expr::ptr value) : expr{ type::expr_paren, loc }, value{ std::move(value) }
{
}

expr_size::expr_size(location const& loc, expr::ptr obj) : expr{ type::expr_size, loc }, obj{ std::move(obj) }
{
}

expr_field::expr_field(location const& loc, expr::ptr obj, expr_identifier::ptr field) : expr{ type::expr_field, loc }, obj{ std::move(obj) }, field{ std::move(field) }
{
}

expr_array::expr_array(location const& loc, expr::ptr obj, expr::ptr key) : expr{ type::expr_array, loc }, obj{ std::move(obj) }, key{ std::move(key) }
{
}

expr_tuple::expr_tuple(location const& loc) : expr{ type::expr_tuple, loc }
{
}

expr_reference::expr_reference(location const& loc, expr_path::ptr path, expr_identifier::ptr name) : expr{ type::expr_reference, loc }, path{ std::move(path) }, name{ std::move(name) }
{
}

expr_istrue::expr_istrue(location const& loc, expr::ptr value) : expr{ type::expr_istrue, loc }, value{ std::move(value) }
{
}

expr_isdefined::expr_isdefined(location const& loc, expr::ptr value) : expr{ type::expr_isdefined, loc }, value{ std::move(value) }
{
}

expr_arguments::expr_arguments(location const& loc) : expr{ type::expr_arguments, loc }
{
}

expr_parameters::expr_parameters(location const& loc) : expr{ type::expr_parameters, loc }
{
}

expr_add_array::expr_add_array(location const& loc, expr_arguments::ptr args) : expr{ type::expr_add_array, loc }, args{ std::move(args) }
{
}

expr_pointer::expr_pointer(location const& loc, expr::ptr func, expr_arguments::ptr args, call::mode mode) : call{ node::type::expr_pointer, loc }, func{ std::move(func) }, args{ std::move(args) }, mode{ mode }
{
}

expr_function::expr_function(location const& loc, expr_path::ptr path, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode) : call{ node::type::expr_function, loc }, path{ std::move(path) }, name{ std::move(name) }, args{ std::move(args) }, mode{ mode }
{
}

expr_method::expr_method(location const& loc, expr::ptr obj, call::ptr value) : expr{ type::expr_method, loc }, obj{ std::move(obj) }, value{ std::move(value) }
{
}

expr_call::expr_call(location const& loc, call::ptr value) : expr{ type::expr_call, loc }, value{ std::move(value) }
{
}

expr_complement::expr_complement(location const& loc, expr::ptr rvalue) : expr{ type::expr_complement, loc }, rvalue{ std::move(rvalue) }
{
}

expr_negate::expr_negate(location const& loc, expr::ptr rvalue) : expr{ type::expr_negate, loc }, rvalue{ std::move(rvalue) }
{
}

expr_not::expr_not(location const& loc, expr::ptr rvalue) : expr{ type::expr_not, loc }, rvalue{ std::move(rvalue) }
{
}

expr_binary::expr_binary(location const& loc, expr::ptr lvalue, expr::ptr rvalue, op oper) : expr{ type::expr_binary, loc }, lvalue{ std::move(lvalue) }, rvalue{ std::move(rvalue) }, oper{ oper }
{
}

expr_ternary::expr_ternary(location const& loc, expr::ptr test, expr::ptr true_expr, expr::ptr false_expr) : expr{ type::expr_ternary, loc }, test{ std::move(test) }, true_expr{ std::move(true_expr) }, false_expr{ std::move(false_expr) }
{
}

expr_assign::expr_assign(location const& loc, expr::ptr lvalue, expr::ptr rvalue, op oper) : expr{ type::expr_assign, loc }, lvalue{ std::move(lvalue) }, rvalue{ std::move(rvalue) }, oper{ oper }
{
}

expr_increment::expr_increment(location const& loc, expr::ptr lvalue, bool prefix) : expr{ type::expr_increment, loc }, lvalue{ std::move(lvalue) }, prefix{ prefix }
{
}

expr_decrement::expr_decrement(location const& loc, expr::ptr lvalue, bool prefix) : expr{ type::expr_decrement, loc }, lvalue{ std::move(lvalue) }, prefix{ prefix }
{
}

expr_var_create::expr_var_create(location const& loc, std::string const& index) : expr{ type::expr_var_create, loc }, index{ index }
{
}

expr_var_access::expr_var_access(location const& loc, std::string const& index) : expr{ type::expr_var_access, loc }, index{ index }
{
}

stmt_empty::stmt_empty(location const& loc) : stmt{ type::stmt_empty, loc }
{
}

stmt_list::stmt_list(location const& loc) : stmt{ type::stmt_list, loc }
{
}

stmt_comp::stmt_comp(location const& loc, stmt_list::ptr block) : stmt{ type::stmt_comp, loc }, block{ std::move(block) }
{
}

stmt_dev::stmt_dev(location const& loc, stmt_list::ptr block) : stmt{ type::stmt_dev, loc }, block{ std::move(block) }
{
}

stmt_expr::stmt_expr(location const& loc, expr::ptr value) : stmt{ type::stmt_expr, loc }, value{ std::move(value) }
{
}

stmt_endon::stmt_endon(location const& loc, expr::ptr obj, expr::ptr event) : stmt{ type::stmt_endon, loc }, obj{ std::move(obj) }, event{ std::move(event) }
{
}

stmt_notify::stmt_notify(location const& loc, expr::ptr obj, expr::ptr event, expr_arguments::ptr args) : stmt{ type::stmt_notify, loc }, obj{ std::move(obj) }, event{ std::move(event) }, args{ std::move(args) }
{
}

stmt_wait::stmt_wait(location const& loc, expr::ptr time) : stmt{ type::stmt_wait, loc }, time{ std::move(time) }
{
}

stmt_waittill::stmt_waittill(location const& loc, expr::ptr obj, expr::ptr event, expr_arguments::ptr args) : stmt{ type::stmt_waittill, loc }, obj{ std::move(obj) }, event{ std::move(event) }, args{ std::move(args) }
{
}

stmt_waittillmatch::stmt_waittillmatch(location const& loc, expr::ptr obj, expr::ptr event, expr_arguments::ptr args) : stmt{ type::stmt_waittillmatch, loc }, obj{ std::move(obj) }, event{ std::move(event) }, args{ std::move(args) }
{
}

stmt_waittillframeend::stmt_waittillframeend(location const& loc) : stmt{ type::stmt_waittillframeend, loc }
{
}

stmt_waitframe::stmt_waitframe(location const& loc) : stmt{ type::stmt_waitframe, loc }
{
}

stmt_if::stmt_if(location const& loc, expr::ptr test, stmt::ptr body) : stmt{ type::stmt_if, loc }, test{ std::move(test) }, body{ std::move(body) }
{
}

stmt_ifelse::stmt_ifelse(location const& loc, expr::ptr test, stmt::ptr stmt_if, stmt::ptr stmt_else) : stmt{ type::stmt_ifelse, loc }, test{ std::move(test) }, stmt_if{ std::move(stmt_if) }, stmt_else{ std::move(stmt_else) }
{
}

stmt_while::stmt_while(location const& loc, expr::ptr test, stmt::ptr body) : stmt{ type::stmt_while, loc }, test{ std::move(test) }, body{ std::move(body) }
{
}

stmt_dowhile::stmt_dowhile(location const& loc, expr::ptr test, stmt::ptr body) : stmt{ type::stmt_dowhile, loc }, test{ std::move(test) }, body{ std::move(body) }
{
}

stmt_for::stmt_for(location const& loc, stmt::ptr init, expr::ptr test, stmt::ptr iter, stmt::ptr body) : stmt{ type::stmt_for, loc }, init{ std::move(init) }, test{ std::move(test) }, iter{ std::move(iter) }, body{ std::move(body) }
{
}

stmt_foreach::stmt_foreach(location const& loc, expr::ptr container, expr::ptr value, expr::ptr index, expr::ptr array, expr::ptr key, stmt::ptr body, bool use_key) : stmt{ type::stmt_foreach, loc }, container{ std::move(container) }, value{ std::move(value) }, index{ std::move(index) }, array{ std::move(array) }, key{ std::move(key) }, body{ std::move(body) }, use_key{ use_key }
{
}

stmt_switch::stmt_switch(location const& loc, expr::ptr test, stmt_comp::ptr body) : stmt{ type::stmt_switch, loc }, test{ std::move(test) }, body{ std::move(body) }
{
}

stmt_case::stmt_case(location const& loc, expr::ptr value) : stmt{ type::stmt_case, loc }, value{ std::move(value) }, body{ nullptr }
{
}

stmt_case::stmt_case(location const& loc, expr::ptr value, stmt_list::ptr body) : stmt{ type::stmt_case, loc }, value{ std::move(value) }, body{ std::move(body) }
{
}

stmt_default::stmt_default(location const& loc) : stmt{ type::stmt_default, loc }, body{ nullptr }
{
}

stmt_default::stmt_default(location const& loc, stmt_list::ptr body) : stmt{ type::stmt_default, loc }, body{ std::move(body) }
{
}

stmt_break::stmt_break(location const& loc) : stmt{ type::stmt_break, loc }
{
}

stmt_continue::stmt_continue(location const& loc) : stmt{ type::stmt_continue, loc }
{
}

stmt_return::stmt_return(location const& loc, expr::ptr value) : stmt{ type::stmt_return, loc }, value{ std::move(value) }
{
}

stmt_breakpoint::stmt_breakpoint(location const& loc) : stmt{ type::stmt_breakpoint, loc }
{
}

stmt_prof_begin::stmt_prof_begin(location const& loc, expr_arguments::ptr args) : stmt{ type::stmt_prof_begin, loc }, args{ std::move(args) }
{
}

stmt_prof_end::stmt_prof_end(location const& loc, expr_arguments::ptr args) : stmt{ type::stmt_prof_end, loc }, args{ std::move(args) }
{
}

stmt_assert::stmt_assert(location const& loc, expr_arguments::ptr args) : stmt{ type::stmt_assert, loc }, args{ std::move(args) }
{
}

stmt_assertex::stmt_assertex(location const& loc, expr_arguments::ptr args) : stmt{ type::stmt_assertex, loc }, args{ std::move(args) }
{
}

stmt_assertmsg::stmt_assertmsg(location const& loc, expr_arguments::ptr args) : stmt{ type::stmt_assertmsg, loc }, args{ std::move(args) }
{
}

stmt_create::stmt_create(location const& loc, std::string const& index) : stmt{ type::stmt_create, loc }, index{ index }
{
}

stmt_remove::stmt_remove(location const& loc, std::string const& index) : stmt{ type::stmt_remove, loc }, index{ index }
{
}

stmt_clear::stmt_clear(location const& loc, std::string const& index) : stmt{ type::stmt_clear, loc }, index{ index }
{
}

stmt_jmp::stmt_jmp(location const& loc, std::string const& value) : stmt{ type::stmt_jmp, loc }, value{ value }
{
}

stmt_jmp_back::stmt_jmp_back(location const& loc, std::string const& value) : stmt{ type::stmt_jmp_back, loc }, value{ value }
{
}

stmt_jmp_cond::stmt_jmp_cond(location const& loc, expr::ptr test, std::string const& value) : stmt{ type::stmt_jmp_cond, loc }, test{ std::move(test) }, value{ value }
{
}

stmt_jmp_true::stmt_jmp_true(location const& loc, expr::ptr test, std::string const& value) : stmt{ type::stmt_jmp_true, loc }, test{ std::move(test) }, value{ value }
{
}

stmt_jmp_false::stmt_jmp_false(location const& loc, expr::ptr test, std::string const& value) : stmt{ type::stmt_jmp_false, loc }, test{ std::move(test) }, value{ value }
{
}

stmt_jmp_switch::stmt_jmp_switch(location const& loc, expr::ptr test, std::string const& value) : stmt{ type::stmt_jmp_switch, loc }, test{ std::move(test) }, value{ value }
{
}

stmt_jmp_endswitch::stmt_jmp_endswitch(location const& loc, std::vector<std::string> data) : stmt{ type::stmt_jmp_endswitch, loc }, data{ std::move(data) }
{
}

decl_empty::decl_empty(location const& loc) : decl{ type::decl_empty, loc }
{
}

decl_function::decl_function(location const& loc, expr_identifier::ptr name, expr_parameters::ptr params, stmt_comp::ptr body) : decl{ type::decl_function, loc }, name{ std::move(name) }, params{ std::move(params) }, body{ std::move(body) }
{
}

decl_constant::decl_constant(location const& loc, expr_identifier::ptr name, expr::ptr value) : decl{ type::decl_constant, loc }, name{ std::move(name) }, value{ std::move(value) }
{
}

decl_usingtree::decl_usingtree(location const& loc, expr_string::ptr name) : decl{ type::decl_usingtree, loc }, name{ std::move(name) }
{
}

decl_dev_begin::decl_dev_begin(location const& loc) : decl{ type::decl_dev_begin, loc }
{
}

decl_dev_end::decl_dev_end(location const& loc) : decl{ type::decl_dev_end, loc }
{
}

include::include(location const& loc, expr_path::ptr path) : node{ type::include, loc }, path{ std::move(path) }
{
}

program::program() : node{ type::program }
{
}

program::program(location const& loc) : node{ type::program, loc }
{
}

auto operator==(expr const& lhs, expr const& rhs)  -> bool
{
    if (!(lhs.kind() == rhs.kind())) return false;

    switch (lhs.kind())
    {
        case node::expr_empty: return true;
        case node::expr_true: return lhs.as<expr_true>() == rhs.as<expr_true>();
        case node::expr_false: return lhs.as<expr_false>() == rhs.as<expr_false>();
        case node::expr_integer: return lhs.as<expr_integer>() == rhs.as<expr_integer>();
        case node::expr_float: return lhs.as<expr_float>() == rhs.as<expr_float>();
        case node::expr_vector: return lhs.as<expr_vector>() == rhs.as<expr_vector>();
        case node::expr_string: return lhs.as<expr_string>() == rhs.as<expr_string>();
        case node::expr_istring: return lhs.as<expr_istring>() == rhs.as<expr_istring>();
        case node::expr_path: return lhs.as<expr_path>() == rhs.as<expr_path>();
        case node::expr_identifier: return lhs.as<expr_identifier>() == rhs.as<expr_identifier>();
        case node::expr_animtree: return lhs.as<expr_animtree>() == rhs.as<expr_animtree>();
        case node::expr_animation: return lhs.as<expr_animation>() == rhs.as<expr_animation>();
        case node::expr_level: return lhs.as<expr_level>() == rhs.as<expr_level>();
        case node::expr_anim: return lhs.as<expr_anim>() == rhs.as<expr_anim>();
        case node::expr_self: return lhs.as<expr_self>() == rhs.as<expr_self>();
        case node::expr_game: return lhs.as<expr_game>() == rhs.as<expr_game>();
        case node::expr_undefined: return lhs.as<expr_undefined>() == rhs.as<expr_undefined>();
        case node::expr_empty_array: return lhs.as<expr_empty_array>() == rhs.as<expr_empty_array>();
        case node::expr_thisthread: return lhs.as<expr_thisthread>() == rhs.as<expr_thisthread>();
        case node::expr_paren: return lhs.as<expr_paren>() == rhs.as<expr_paren>();
        case node::expr_size: return lhs.as<expr_size>() == rhs.as<expr_size>();
        case node::expr_field: return lhs.as<expr_field>() == rhs.as<expr_field>();
        case node::expr_array: return lhs.as<expr_array>() == rhs.as<expr_array>();
        default: return false;
    }
}

auto operator==(expr_true const&, expr_true const&) -> bool
{
    return true;
}

auto operator==(expr_false const&, expr_false const&) -> bool
{
    return true;
}

auto operator==(expr_integer const& lhs, expr_integer const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_float const& lhs, expr_float const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_vector const& lhs, expr_vector const& rhs) -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

auto operator==(expr_string const& lhs, expr_string const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_istring const& lhs, expr_istring const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_path const& lhs, expr_path const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_identifier const& lhs, expr_identifier const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_animtree const&, expr_animtree const&) -> bool
{
    return true;
}

auto operator==(expr_animation const& lhs, expr_animation const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_level const&, expr_level const&) -> bool
{
    return true;
}

auto operator==(expr_anim const&, expr_anim const&) -> bool
{
    return true;
}

auto operator==(expr_self const&, expr_self const&) -> bool
{
    return true;
}

auto operator==(expr_game const&, expr_game const&) -> bool
{
    return true;
}

auto operator==(expr_undefined const&, expr_undefined const&) -> bool
{
    return true;
}

auto operator==(expr_empty_array const&, expr_empty_array const&) -> bool
{
    return true;
}

auto operator==(expr_thisthread const&, expr_thisthread const&) -> bool
{
    return true;
}

auto operator==(expr_paren const& lhs, expr_paren const& rhs) -> bool
{
    return lhs.value == rhs.value;
}

auto operator==(expr_size const& lhs, expr_size const& rhs) -> bool
{
    return lhs.obj == rhs.obj;
}

auto operator==(expr_field const& lhs, expr_field const& rhs) -> bool
{
    return lhs.obj == rhs.obj && *lhs.field == *rhs.field;
}

auto operator==(expr_array const& lhs, expr_array const& rhs) -> bool
{
    return lhs.obj == rhs.obj && lhs.key == rhs.key;
}

} // namespace xsk::gsc
