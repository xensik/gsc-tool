// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/common/location.hpp"
#include "xsk/arc/common/asset.hpp"
#include "xsk/arc/common/ast.hpp"

namespace xsk::arc
{

auto node::is_special_stmt() -> bool
{
    switch (kind_)
    {
        case type::stmt_if:
        case type::stmt_ifelse:
        case type::stmt_while:
        case type::stmt_dowhile:
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
        case type::stmt_dowhile:
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
        case type::stmt_dowhile:
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
        case type::stmt_dowhile:
        case type::stmt_for:
        case type::stmt_foreach:
        case type::stmt_switch:
            return true;
        default:
            return false;
    }
}

auto node::is_boolean() -> bool
{
    switch (kind_)
    {
        case type::expr_integer:
            return reinterpret_cast<arc::expr_integer*>(this)->value == "1" ||
                reinterpret_cast<arc::expr_integer*>(this)->value == "0";
        case type::expr_true:
        case type::expr_false:
            return true;
        case type::expr_binary:
            switch (reinterpret_cast<arc::expr_binary*>(this)->oper)
            {
                case expr_binary::op::bool_or:
                case expr_binary::op::bool_and:
                case expr_binary::op::seq:
                case expr_binary::op::sne:
                case expr_binary::op::eq:
                case expr_binary::op::ne:
                case expr_binary::op::le:
                case expr_binary::op::ge:
                case expr_binary::op::lt:
                case expr_binary::op::gt:
                    return true;
                default:
                    return false;
            }
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
        case op::seq:      return 6;
        case op::sne:      return 6;
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

#define XSK_ARC_EXPR_IS(expr_type)                                    \
template<>                                                            \
auto expr::is<arc::expr_type>() const -> bool                         \
{                                                                     \
    return kind() == type::expr_type;                                 \
}                                                                     \
                                                                      \
template<>                                                            \
auto expr::as<arc::expr_type>() -> arc::expr_type &                   \
{                                                                     \
    return static_cast<arc::expr_type &>(*this);                      \
}                                                                     \
                                                                      \
template<>                                                            \
auto expr::as<arc::expr_type>() const -> arc::expr_type const&        \
{                                                                     \
    return static_cast<arc::expr_type const&>(*this);                 \
}                                                                     \

#define XSK_ARC_CALL_IS(expr_type)                                    \
template<>                                                            \
auto call::is<arc::expr_type>() const -> bool                         \
{                                                                     \
    return kind() == node::type::expr_type;                           \
}                                                                     \
                                                                      \
template<>                                                            \
auto call::as<arc::expr_type>() -> arc::expr_type &                   \
{                                                                     \
    return static_cast<arc::expr_type &>(*this);                      \
}                                                                     \
                                                                      \
template<>                                                            \
auto call::as<arc::expr_type>() const -> arc::expr_type const&        \
{                                                                     \
    return static_cast<arc::expr_type const&>(*this);                 \
}                                                                     \

#define XSK_ARC_STMT_IS(expr_type)                                    \
template<>                                                            \
auto stmt::is<arc::expr_type>() const -> bool                         \
{                                                                     \
    return kind() == type::expr_type;                                 \
}                                                                     \
                                                                      \
template<>                                                            \
auto stmt::as<arc::expr_type>() -> arc::expr_type &                   \
{                                                                     \
    return static_cast<arc::expr_type &>(*this);                      \
}                                                                     \
                                                                      \
template<>                                                            \
auto stmt::as<arc::expr_type>() const -> arc::expr_type const&        \
{                                                                     \
    return static_cast<arc::expr_type const&>(*this);                 \
}                                                                     \

#define XSK_ARC_DECL_IS(expr_type)                                    \
template<>                                                            \
auto decl::is<arc::expr_type>() const -> bool                         \
{                                                                     \
    return kind() == type::expr_type;                                 \
}                                                                     \
                                                                      \
template<>                                                            \
auto decl::as<arc::expr_type>() -> arc::expr_type &                   \
{                                                                     \
    return static_cast<arc::expr_type &>(*this);                      \
}                                                                     \
                                                                      \
template<>                                                            \
auto decl::as<arc::expr_type>() const -> arc::expr_type const&        \
{                                                                     \
    return static_cast<arc::expr_type const&>(*this);                 \
}                                                                     \

XSK_ARC_EXPR_IS(expr_empty)
XSK_ARC_EXPR_IS(expr_true)
XSK_ARC_EXPR_IS(expr_false)
XSK_ARC_EXPR_IS(expr_integer)
XSK_ARC_EXPR_IS(expr_float)
XSK_ARC_EXPR_IS(expr_vector)
XSK_ARC_EXPR_IS(expr_hash)
XSK_ARC_EXPR_IS(expr_string)
XSK_ARC_EXPR_IS(expr_istring)
XSK_ARC_EXPR_IS(expr_path)
XSK_ARC_EXPR_IS(expr_identifier)
XSK_ARC_EXPR_IS(expr_animtree)
XSK_ARC_EXPR_IS(expr_animation)
XSK_ARC_EXPR_IS(expr_classes)
XSK_ARC_EXPR_IS(expr_world)
XSK_ARC_EXPR_IS(expr_level)
XSK_ARC_EXPR_IS(expr_anim)
XSK_ARC_EXPR_IS(expr_self)
XSK_ARC_EXPR_IS(expr_game)
XSK_ARC_EXPR_IS(expr_undefined)
XSK_ARC_EXPR_IS(expr_empty_array)
XSK_ARC_EXPR_IS(expr_ellipsis)
XSK_ARC_EXPR_IS(expr_paren)
XSK_ARC_EXPR_IS(expr_size)
XSK_ARC_EXPR_IS(expr_field)
XSK_ARC_EXPR_IS(expr_array)
XSK_ARC_EXPR_IS(expr_reference)
XSK_ARC_EXPR_IS(expr_getnextarraykey)
XSK_ARC_EXPR_IS(expr_getfirstarraykey)
XSK_ARC_EXPR_IS(expr_getdvarcoloralpha)
XSK_ARC_EXPR_IS(expr_getdvarcolorblue)
XSK_ARC_EXPR_IS(expr_getdvarcolorgreen)
XSK_ARC_EXPR_IS(expr_getdvarcolorred)
XSK_ARC_EXPR_IS(expr_getdvarvector)
XSK_ARC_EXPR_IS(expr_getdvarfloat)
XSK_ARC_EXPR_IS(expr_getdvarint)
XSK_ARC_EXPR_IS(expr_getdvar)
XSK_ARC_EXPR_IS(expr_gettime)
XSK_ARC_EXPR_IS(expr_abs)
XSK_ARC_EXPR_IS(expr_vectortoangles)
XSK_ARC_EXPR_IS(expr_angleclamp180)
XSK_ARC_EXPR_IS(expr_anglestoforward)
XSK_ARC_EXPR_IS(expr_anglestoright)
XSK_ARC_EXPR_IS(expr_anglestoup)
XSK_ARC_EXPR_IS(expr_vectorscale)
XSK_ARC_EXPR_IS(expr_isdefined)
XSK_ARC_EXPR_IS(expr_arguments)
XSK_ARC_EXPR_IS(expr_parameters)
XSK_ARC_EXPR_IS(expr_member)
XSK_ARC_EXPR_IS(expr_pointer)
XSK_ARC_EXPR_IS(expr_function)
XSK_ARC_EXPR_IS(expr_method)
XSK_ARC_EXPR_IS(expr_call)
XSK_ARC_EXPR_IS(expr_new)
XSK_ARC_EXPR_IS(expr_complement)
XSK_ARC_EXPR_IS(expr_negate)
XSK_ARC_EXPR_IS(expr_not)
XSK_ARC_EXPR_IS(expr_binary)
XSK_ARC_EXPR_IS(expr_ternary)
XSK_ARC_EXPR_IS(expr_const)
XSK_ARC_EXPR_IS(expr_assign)
XSK_ARC_EXPR_IS(expr_increment)
XSK_ARC_EXPR_IS(expr_decrement)

XSK_ARC_CALL_IS(expr_member)
XSK_ARC_CALL_IS(expr_pointer)
XSK_ARC_CALL_IS(expr_function)

XSK_ARC_STMT_IS(stmt_empty)
XSK_ARC_STMT_IS(stmt_list)
XSK_ARC_STMT_IS(stmt_comp)
XSK_ARC_STMT_IS(stmt_dev)
XSK_ARC_STMT_IS(stmt_expr)
XSK_ARC_STMT_IS(stmt_endon)
XSK_ARC_STMT_IS(stmt_notify)
XSK_ARC_STMT_IS(stmt_wait)
XSK_ARC_STMT_IS(stmt_waitrealtime)
XSK_ARC_STMT_IS(stmt_waittill)
XSK_ARC_STMT_IS(stmt_waittillmatch)
XSK_ARC_STMT_IS(stmt_waittillframeend)
XSK_ARC_STMT_IS(stmt_if)
XSK_ARC_STMT_IS(stmt_ifelse)
XSK_ARC_STMT_IS(stmt_while)
XSK_ARC_STMT_IS(stmt_dowhile)
XSK_ARC_STMT_IS(stmt_for)
XSK_ARC_STMT_IS(stmt_foreach)
XSK_ARC_STMT_IS(stmt_switch)
XSK_ARC_STMT_IS(stmt_case)
XSK_ARC_STMT_IS(stmt_default)
XSK_ARC_STMT_IS(stmt_break)
XSK_ARC_STMT_IS(stmt_continue)
XSK_ARC_STMT_IS(stmt_return)
XSK_ARC_STMT_IS(stmt_breakpoint)
XSK_ARC_STMT_IS(stmt_prof_begin)
XSK_ARC_STMT_IS(stmt_prof_end)
XSK_ARC_STMT_IS(stmt_jmp)
XSK_ARC_STMT_IS(stmt_jmp_back)
XSK_ARC_STMT_IS(stmt_jmp_cond)
XSK_ARC_STMT_IS(stmt_jmp_true)
XSK_ARC_STMT_IS(stmt_jmp_false)
XSK_ARC_STMT_IS(stmt_jmp_switch)
XSK_ARC_STMT_IS(stmt_jmp_endswitch)
XSK_ARC_STMT_IS(stmt_jmp_dev)

XSK_ARC_DECL_IS(decl_empty)
XSK_ARC_DECL_IS(decl_function)
XSK_ARC_DECL_IS(decl_usingtree)
XSK_ARC_DECL_IS(decl_namespace)
XSK_ARC_DECL_IS(decl_dev_begin)
XSK_ARC_DECL_IS(decl_dev_end)

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

expr_hash::expr_hash(location const& loc, std::string const& value) : expr{ type::expr_hash, loc }, value{ value }
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

expr_animation::expr_animation(location const& loc, std::string const& space, std::string const& value) : expr{ type::expr_animation, loc }, space{ space }, value{ value }
{
}

expr_classes::expr_classes(location const& loc) : expr{ type::expr_classes, loc }
{
}

expr_world::expr_world(location const& loc) : expr{ type::expr_world, loc }
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

expr_ellipsis::expr_ellipsis(location const& loc) : expr{ type::expr_ellipsis, loc }
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

expr_reference::expr_reference(location const& loc, expr_path::ptr path, expr_identifier::ptr name) : expr{ type::expr_reference, loc }, path{ std::move(path) }, name{ std::move(name) }
{
}

expr_getnextarraykey::expr_getnextarraykey(location const& loc, expr::ptr arg1, expr::ptr arg2) : expr{ type::expr_getnextarraykey, loc }, arg1{ std::move(arg1) }, arg2{ std::move(arg2) }
{
}

expr_getfirstarraykey::expr_getfirstarraykey(location const& loc, expr::ptr arg) : expr{ type::expr_getfirstarraykey, loc }, arg{ std::move(arg) }
{
}

expr_getdvarcoloralpha::expr_getdvarcoloralpha(location const& loc, expr::ptr arg) : expr{ type::expr_getdvarcoloralpha, loc }, arg{ std::move(arg) }
{
}

expr_getdvarcolorblue::expr_getdvarcolorblue(location const& loc, expr::ptr arg) : expr{ type::expr_getdvarcolorblue, loc }, arg{ std::move(arg) }
{
}

expr_getdvarcolorgreen::expr_getdvarcolorgreen(location const& loc, expr::ptr arg) : expr{ type::expr_getdvarcolorgreen, loc }, arg{ std::move(arg) }
{
}

expr_getdvarcolorred::expr_getdvarcolorred(location const& loc, expr::ptr arg) : expr{ type::expr_getdvarcolorred, loc }, arg{ std::move(arg) }
{
}

expr_getdvarvector::expr_getdvarvector(location const& loc, expr::ptr arg) : expr{ type::expr_getdvarvector, loc }, arg{ std::move(arg) }
{
}

expr_getdvarfloat::expr_getdvarfloat(location const& loc, expr::ptr arg) : expr{ type::expr_getdvarfloat, loc }, arg{ std::move(arg) }
{
}

expr_getdvarint::expr_getdvarint(location const& loc, expr::ptr arg) : expr{ type::expr_getdvarint, loc }, arg{ std::move(arg) }
{
}

expr_getdvar::expr_getdvar(location const& loc, expr::ptr arg) : expr{ type::expr_getdvar, loc }, arg{ std::move(arg) }
{
}

expr_gettime::expr_gettime(location const& loc) : expr{ type::expr_gettime, loc }
{
}

expr_abs::expr_abs(location const& loc, expr::ptr arg) : expr{ type::expr_abs, loc }, arg{ std::move(arg) }
{
}

expr_vectortoangles::expr_vectortoangles(location const& loc, expr::ptr arg) : expr{ type::expr_vectortoangles, loc }, arg{ std::move(arg) }
{
}

expr_angleclamp180::expr_angleclamp180(location const& loc, expr::ptr arg) : expr{ type::expr_angleclamp180, loc }, arg{ std::move(arg) }
{
}

expr_anglestoforward::expr_anglestoforward(location const& loc, expr::ptr arg) : expr{ type::expr_anglestoforward, loc }, arg{ std::move(arg) }
{
}

expr_anglestoright::expr_anglestoright(location const& loc, expr::ptr arg) : expr{ type::expr_anglestoright, loc }, arg{ std::move(arg) }
{
}

expr_anglestoup::expr_anglestoup(location const& loc, expr::ptr arg) : expr{ type::expr_anglestoup, loc }, arg{ std::move(arg) }
{
}

expr_vectorscale::expr_vectorscale(location const& loc, expr::ptr arg1, expr::ptr arg2) : expr{ type::expr_vectorscale, loc }, arg1{ std::move(arg1) }, arg2{ std::move(arg2) }
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

expr_member::expr_member(location const& loc, expr::ptr obj, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode) : call{ type::expr_member, loc }, obj{ std::move(obj) }, name{ std::move(name) }, args{ std::move(args) }, mode{ mode }
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

expr_new::expr_new(location const& loc, expr_identifier::ptr name) : expr{ type::expr_new, loc }, name{ std::move(name) }
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

expr_const::expr_const(location const& loc, expr_identifier::ptr lvalue, expr::ptr rvalue) : expr{ type::expr_const, loc }, lvalue{ std::move(lvalue) }, rvalue{ std::move(rvalue) }
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

stmt_waitrealtime::stmt_waitrealtime(location const& loc, expr::ptr time) : stmt{ type::stmt_waitrealtime, loc }, time{ std::move(time) }
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

stmt_foreach::stmt_foreach(location const& loc, expr::ptr container, expr::ptr value, expr::ptr array, expr::ptr key, stmt::ptr body, bool use_key) : stmt{ type::stmt_foreach, loc }, container{ std::move(container) }, value{ std::move(value) }, array{ std::move(array) }, key{ std::move(key) }, body{ std::move(body) }, use_key{ use_key }
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

stmt_jmp_dev::stmt_jmp_dev(location const& loc, std::string const& value) : stmt{ type::stmt_jmp_dev, loc }, value{ value }
{
}

decl_empty::decl_empty(location const& loc) : decl{ type::decl_empty, loc }
{
}

decl_function::decl_function(location const& loc, expr_identifier::ptr space, expr_identifier::ptr name, expr_parameters::ptr params, stmt_comp::ptr body, export_flags flags) : decl{ type::decl_function, loc }, space{ std::move(space) }, name{ std::move(name) }, params{ std::move(params) }, body{ std::move(body) }, flags{ flags }
{
}

decl_namespace::decl_namespace(location const& loc, expr_string::ptr name) : decl{ type::decl_namespace, loc }, name{ std::move(name) }
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

    switch(lhs.kind())
    {
        case node::expr_empty: return true;
        case node::expr_true: return lhs.as<expr_true>() == rhs.as<expr_true>();
        case node::expr_false: return lhs.as<expr_false>() == rhs.as<expr_false>();
        case node::expr_integer: return lhs.as<expr_integer>() == rhs.as<expr_integer>();
        case node::expr_float: return lhs.as<expr_float>() == rhs.as<expr_float>();
        case node::expr_vector: return lhs.as<expr_vector>() == rhs.as<expr_vector>();
        case node::expr_hash: return lhs.as<expr_hash>() == rhs.as<expr_hash>();
        case node::expr_string: return lhs.as<expr_string>() == rhs.as<expr_string>();
        case node::expr_istring: return lhs.as<expr_istring>() == rhs.as<expr_istring>();
        case node::expr_path: return lhs.as<expr_path>() == rhs.as<expr_path>();
        case node::expr_identifier: return lhs.as<expr_identifier>() == rhs.as<expr_identifier>();
        case node::expr_animtree: return lhs.as<expr_animtree>() == rhs.as<expr_animtree>();
        case node::expr_animation: return lhs.as<expr_animation>() == rhs.as<expr_animation>();
        case node::expr_classes: return lhs.as<expr_classes>() == rhs.as<expr_classes>();
        case node::expr_world: return lhs.as<expr_world>() == rhs.as<expr_world>();
        case node::expr_level: return lhs.as<expr_level>() == rhs.as<expr_level>();
        case node::expr_anim: return lhs.as<expr_anim>() == rhs.as<expr_anim>();
        case node::expr_self: return lhs.as<expr_self>() == rhs.as<expr_self>();
        case node::expr_game: return lhs.as<expr_game>() == rhs.as<expr_game>();
        case node::expr_undefined: return lhs.as<expr_undefined>() == rhs.as<expr_undefined>();
        case node::expr_empty_array: return lhs.as<expr_empty_array>() == rhs.as<expr_empty_array>();
        case node::expr_ellipsis: return lhs.as<expr_ellipsis>() == rhs.as<expr_ellipsis>();
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

auto operator==(expr_hash const& lhs, expr_hash const& rhs) -> bool
{
    return lhs.value == rhs.value;
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
    return lhs.space == rhs.space && lhs.value == rhs.value;
}

auto operator==(expr_classes const&, expr_classes const&) -> bool
{
    return true;
}

auto operator==(expr_world const&, expr_world const&) -> bool
{
    return true;
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

auto operator==(expr_ellipsis const&, expr_ellipsis const&) -> bool
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

} // namespace xsk::arc
