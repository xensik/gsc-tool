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
        null,
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
        expr_super_equal,
        expr_super_not_equal,
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
        stmt_comp,
        stmt_dev,
        stmt_expr,
        stmt_call,
        stmt_const,
        stmt_assign,
        stmt_endon,
        stmt_notify,
        stmt_realwait,
        stmt_wait,
        stmt_waittill,
        stmt_waittillmatch,
        stmt_waittillframeend,
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
        decl_function,
        decl_usingtree,
        decl_namespace,
        decl_dev_begin,
        decl_dev_end,
        include,
        program,
        asm_loc,
        asm_jmp,
        asm_jmp_back,
        asm_jmp_cond,
        asm_jmp_true,
        asm_jmp_false,
        asm_switch,
        asm_endswitch,
        asm_prescriptcall,
        asm_voidcodepos,
        asm_dev,
    };

public:
    node() : kind_(type::null) {}
    node(location const& loc) : kind_(type::null), loc_(loc) {}
    node(type t) : kind_(t) {}
    node(type t, location const& loc) : kind_(t), loc_(loc) {}

    virtual ~node() = default;
    friend bool operator==(node const& n, type t);
    friend bool operator==(node const& lhs, node const& rhs);

    auto kind() const -> type { return kind_; }
    auto loc() const -> location const& { return loc_; }
    auto label() const -> std::string { return loc_.label(); }

    auto is_special_stmt() -> bool;
    auto is_special_stmt_dev() -> bool;
    auto is_special_stmt_noif() -> bool;
    auto is_special_stmt_dev_noif() -> bool;
    auto is_boolean() -> bool;
    auto is_binary() -> bool;
    auto precedence() -> u8;

private:
    type kind_;
    location loc_;
};

struct expr_true;
struct expr_false;
struct expr_integer;
struct expr_float;
struct expr_vector;
struct expr_hash;
struct expr_string;
struct expr_istring;
struct expr_path;
struct expr_identifier;
struct expr_animtree;
struct expr_animation;
struct expr_classes;
struct expr_world;
struct expr_level;
struct expr_anim;
struct expr_self;
struct expr_game;
struct expr_undefined;
struct expr_empty_array;
struct expr_ellipsis;
struct expr_paren;
struct expr_size;
struct expr_field;
struct expr_array;
struct expr_reference;
struct expr_getnextarraykey;
struct expr_getfirstarraykey;
struct expr_getdvarcoloralpha;
struct expr_getdvarcolorblue;
struct expr_getdvarcolorgreen;
struct expr_getdvarcolorred;
struct expr_getdvarvector;
struct expr_getdvarfloat;
struct expr_getdvarint;
struct expr_getdvar;
struct expr_gettime;
struct expr_abs;
struct expr_vectortoangles;
struct expr_angleclamp180;
struct expr_anglestoforward;
struct expr_anglestoright;
struct expr_anglestoup;
struct expr_vectorscale;
struct expr_isdefined;
struct expr_arguments;
struct expr_parameters;
struct expr_member;
struct expr_pointer;
struct expr_function;
struct expr_method;
struct expr_call;
struct expr_new;
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
struct expr_super_equal;
struct expr_super_not_equal;
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
struct stmt_comp;
struct stmt_dev;
struct stmt_expr;
struct stmt_call;
struct stmt_const;
struct stmt_assign;
struct stmt_endon;
struct stmt_notify;
struct stmt_realwait;
struct stmt_wait;
struct stmt_waittill;
struct stmt_waittillmatch;
struct stmt_waittillframeend;
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
struct decl_function;
struct decl_usingtree;
struct decl_namespace;
struct decl_dev_begin;
struct decl_dev_end;
struct include;
struct program;
struct asm_loc;
struct asm_jmp;
struct asm_jmp_back;
struct asm_jmp_cond;
struct asm_jmp_false;
struct asm_jmp_true;
struct asm_switch;
struct asm_endswitch;
struct asm_prescriptcall;
struct asm_voidcodepos;
struct asm_dev;

union call
{
    enum class mode { normal, thread };

    std::unique_ptr<node> as_node;
    std::unique_ptr<expr_member> as_member;
    std::unique_ptr<expr_pointer> as_pointer;
    std::unique_ptr<expr_function> as_function;

    call();
    call(std::unique_ptr<node> value);
    call(call&& value);
    call(call const&) = delete;
    call& operator=(call const&) = delete;
    ~call();
    friend auto operator==(call const& lhs, node::type rhs) -> bool;
    auto loc() const -> location;
    auto kind() const -> node::type;
    auto label() const -> std::string;
};

union expr
{
    std::unique_ptr<node> as_node;
    std::unique_ptr<expr_true> as_true;
    std::unique_ptr<expr_false> as_false;
    std::unique_ptr<expr_integer> as_integer;
    std::unique_ptr<expr_float> as_float;
    std::unique_ptr<expr_vector> as_vector;
    std::unique_ptr<expr_hash> as_hash;
    std::unique_ptr<expr_string> as_string;
    std::unique_ptr<expr_istring> as_istring;
    std::unique_ptr<expr_path> as_path;
    std::unique_ptr<expr_identifier> as_identifier;
    std::unique_ptr<expr_animtree> as_animtree;
    std::unique_ptr<expr_animation> as_animation;
    std::unique_ptr<expr_classes> as_classes;
    std::unique_ptr<expr_world> as_world;
    std::unique_ptr<expr_level> as_level;
    std::unique_ptr<expr_anim> as_anim;
    std::unique_ptr<expr_self> as_self;
    std::unique_ptr<expr_game> as_game;
    std::unique_ptr<expr_undefined> as_undefined;
    std::unique_ptr<expr_empty_array> as_empty_array;
    std::unique_ptr<expr_ellipsis> as_ellipsis;
    std::unique_ptr<expr_paren> as_paren;
    std::unique_ptr<expr_size> as_size;
    std::unique_ptr<expr_field> as_field;
    std::unique_ptr<expr_array> as_array;
    std::unique_ptr<expr_reference> as_reference;
    std::unique_ptr<expr_getnextarraykey> as_getnextarraykey;
    std::unique_ptr<expr_getfirstarraykey> as_getfirstarraykey;
    std::unique_ptr<expr_getdvarcoloralpha> as_getdvarcoloralpha;
    std::unique_ptr<expr_getdvarcolorblue> as_getdvarcolorblue;
    std::unique_ptr<expr_getdvarcolorgreen> as_getdvarcolorgreen;
    std::unique_ptr<expr_getdvarcolorred> as_getdvarcolorred;
    std::unique_ptr<expr_getdvarvector> as_getdvarvector;
    std::unique_ptr<expr_getdvarfloat> as_getdvarfloat;
    std::unique_ptr<expr_getdvarint> as_getdvarint;
    std::unique_ptr<expr_getdvar> as_getdvar;
    std::unique_ptr<expr_gettime> as_gettime;
    std::unique_ptr<expr_abs> as_abs;
    std::unique_ptr<expr_vectortoangles> as_vectortoangles;
    std::unique_ptr<expr_angleclamp180> as_angleclamp180;
    std::unique_ptr<expr_anglestoforward> as_anglestoforward;
    std::unique_ptr<expr_anglestoright> as_anglestoright;
    std::unique_ptr<expr_anglestoup> as_anglestoup;
    std::unique_ptr<expr_vectorscale> as_vectorscale;
    std::unique_ptr<expr_isdefined> as_isdefined;
    std::unique_ptr<expr_arguments> as_arguments;
    std::unique_ptr<expr_parameters> as_parameters;
    std::unique_ptr<expr_member> as_member;
    std::unique_ptr<expr_pointer> as_pointer;
    std::unique_ptr<expr_function> as_function;
    std::unique_ptr<expr_method> as_method;
    std::unique_ptr<expr_call> as_call;
    std::unique_ptr<expr_new> as_new;
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
    std::unique_ptr<expr_super_equal> as_super_equal;
    std::unique_ptr<expr_super_not_equal> as_super_not_equal;
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

    expr();
    expr(std::unique_ptr<node> value);
    expr(expr&& value);
    expr& operator=(expr&& value);
    expr(expr const&) = delete;
    expr& operator=(expr const&) = delete;
    ~expr();
    friend auto operator!=(expr const& lhs, node::type rhs) -> bool;
    friend auto operator==(expr const& lhs, node::type rhs) -> bool;
    friend auto operator==(expr const& lhs, expr const& rhs) -> bool;
    auto loc() const -> location;
    auto kind() const -> node::type;
    auto label() const -> std::string;
};

union stmt
{
    std::unique_ptr<node> as_node;
    std::unique_ptr<stmt_list> as_list;
    std::unique_ptr<stmt_comp> as_comp;
    std::unique_ptr<stmt_dev> as_dev;
    std::unique_ptr<stmt_expr> as_expr;
    std::unique_ptr<stmt_call> as_call;
    std::unique_ptr<stmt_const> as_const;
    std::unique_ptr<stmt_assign> as_assign;
    std::unique_ptr<stmt_endon> as_endon;
    std::unique_ptr<stmt_notify> as_notify;
    std::unique_ptr<stmt_realwait> as_realwait;
    std::unique_ptr<stmt_wait> as_wait;
    std::unique_ptr<stmt_waittill> as_waittill;
    std::unique_ptr<stmt_waittillmatch> as_waittillmatch;
    std::unique_ptr<stmt_waittillframeend> as_waittillframeend;
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
    std::unique_ptr<asm_jmp> as_jump;
    std::unique_ptr<asm_jmp_cond> as_cond;
    std::unique_ptr<asm_jmp_back> as_jump_back;
    std::unique_ptr<asm_switch> as_asm_switch;
    std::unique_ptr<asm_endswitch> as_asm_endswitch;
    std::unique_ptr<asm_dev> as_asm_dev;

    stmt();
    stmt(std::unique_ptr<node> value);
    stmt(stmt&& value);
    stmt& operator=(stmt&& value);
    stmt(stmt const&) = delete;
    stmt& operator=(stmt const&) = delete;
    ~stmt();
    friend auto operator==(stmt const& lhs, node::type rhs) -> bool;
    auto loc() const -> location;
    auto kind() const -> node::type;
    auto label() const -> std::string;
};

union decl
{
    std::unique_ptr<node> as_node;
    std::unique_ptr<decl_dev_begin> as_dev_begin;
    std::unique_ptr<decl_dev_end> as_dev_end;
    std::unique_ptr<decl_namespace> as_namespace;
    std::unique_ptr<decl_usingtree> as_usingtree;
    std::unique_ptr<decl_function> as_function;

    decl();
    decl(std::unique_ptr<node> value);
    decl(decl&& value);
    decl& operator=(decl&& value);
    decl(decl const&) = delete;
    decl& operator=(decl const&) = delete;
    ~decl();
    friend auto operator==(decl const& lhs, node::type rhs) -> bool;
    auto loc() const -> location;
    auto kind() const -> node::type;
    auto label() const -> std::string;
};

struct expr_true : public node
{
    using ptr = std::unique_ptr<expr_true>;

    expr_true(location const& loc);
    friend auto operator==(expr_true const& lhs, expr_true const& rhs) -> bool;
};

struct expr_false : public node
{
    using ptr = std::unique_ptr<expr_false>;

    expr_false(location const& loc);
    friend auto operator==(expr_false const& lhs, expr_false const& rhs) -> bool;
};

struct expr_integer : public node
{
    using ptr = std::unique_ptr<expr_integer>;

    std::string value;

    expr_integer(location const& loc, std::string const& value);
    friend auto operator==(expr_integer const& lhs, expr_integer const& rhs) -> bool;
};

struct expr_float : public node
{
    using ptr = std::unique_ptr<expr_float>;

    std::string value;

    expr_float(location const& loc, std::string const& value);
    friend auto operator==(expr_float const& lhs, expr_float const& rhs) -> bool;
};

struct expr_vector : public node
{
    using ptr = std::unique_ptr<expr_vector>;

    expr x;
    expr y;
    expr z;

    expr_vector(location const& loc, expr x, expr y, expr z);
    friend auto operator==(expr_vector const& lhs, expr_vector const& rhs) -> bool;
};

struct expr_hash : public node
{
    using ptr = std::unique_ptr<expr_hash>;

    std::string value;

    expr_hash(location const& loc, std::string const& value);
    friend auto operator==(expr_hash const& lhs, expr_hash const& rhs) -> bool;
};

struct expr_string : public node
{
    using ptr = std::unique_ptr<expr_string>;

    std::string value;

    expr_string(location const& loc, std::string const& value);
    friend auto operator==(expr_string const& lhs, expr_string const& rhs) -> bool;
};

struct expr_istring : public node
{
    using ptr = std::unique_ptr<expr_istring>;

    std::string value;

    expr_istring(location const& loc, std::string const& value);
    friend auto operator==(expr_istring const& lhs, expr_istring const& rhs) -> bool;
};

struct expr_path : public node
{
    using ptr = std::unique_ptr<expr_path>;

    std::string value;

    expr_path(location const& loc);
    expr_path(location const& loc, std::string const& value);
    friend auto operator==(expr_path const& lhs, expr_path const& rhs) -> bool;
};

struct expr_identifier : public node
{
    using ptr = std::unique_ptr<expr_identifier>;

    std::string value;

    expr_identifier(location const& loc, std::string const& value);
    friend auto operator==(expr_identifier const& lhs, expr_identifier const& rhs) -> bool;
};

struct expr_animtree : public node
{
    using ptr = std::unique_ptr<expr_animtree>;

    expr_animtree(location const& loc);
    friend auto operator==(expr_animtree const& lhs, expr_animtree const& rhs) -> bool;
};

struct expr_animation : public node
{
    using ptr = std::unique_ptr<expr_animation>;

    std::string value;

    expr_animation(location const& loc, std::string const& value);
    friend auto operator==(expr_animation const& lhs, expr_animation const& rhs) -> bool;
};

struct expr_classes : public node
{
    using ptr = std::unique_ptr<expr_classes>;

    expr_classes(location const& loc);
    friend auto operator==(expr_classes const& lhs, expr_classes const& rhs) -> bool;
};

struct expr_world : public node
{
    using ptr = std::unique_ptr<expr_world>;

    expr_world(location const& loc);
    friend auto operator==(expr_world const& lhs, expr_world const& rhs) -> bool;
};

struct expr_level : public node
{
    using ptr = std::unique_ptr<expr_level>;

    expr_level(location const& loc);
    friend auto operator==(expr_level const& lhs, expr_level const& rhs) -> bool;
};

struct expr_anim : public node
{
    using ptr = std::unique_ptr<expr_anim>;

    expr_anim(location const& loc);
    friend auto operator==(expr_anim const& lhs, expr_anim const& rhs) -> bool;
};

struct expr_self : public node
{
    using ptr = std::unique_ptr<expr_self>;

    expr_self(location const& loc);
    friend auto operator==(expr_self const& lhs, expr_self const& rhs) -> bool;
};

struct expr_game : public node
{
    using ptr = std::unique_ptr<expr_game>;

    expr_game(location const& loc);
    friend auto operator==(expr_game const& lhs, expr_game const& rhs) -> bool;
};

struct expr_undefined : public node
{
    using ptr = std::unique_ptr<expr_undefined>;

    expr_undefined(location const& loc);
    friend auto operator==(expr_undefined const& lhs, expr_undefined const& rhs) -> bool;
};

struct expr_empty_array : public node
{
    using ptr = std::unique_ptr<expr_empty_array>;

    expr_empty_array(location const& loc);
    friend auto operator==(expr_empty_array const& lhs, expr_empty_array const& rhs) -> bool;
};

struct expr_ellipsis : public node
{
    using ptr = std::unique_ptr<expr_ellipsis>;

    expr_ellipsis(location const& loc);
    friend auto operator==(expr_ellipsis const& lhs, expr_ellipsis const& rhs) -> bool;
};

struct expr_paren : public node
{
    using ptr = std::unique_ptr<expr_paren>;

    expr value;

    expr_paren(location const& loc, expr value);
    friend auto operator==(expr_paren const& lhs, expr_paren const& rhs) -> bool;
};

struct expr_size : public node
{
    using ptr = std::unique_ptr<expr_size>;

    expr obj;

    expr_size(location const& loc, expr obj);
    friend auto operator==(expr_size const& lhs, expr_size const& rhs) -> bool;
};

struct expr_field : public node
{
    using ptr = std::unique_ptr<expr_field>;

    expr obj;
    expr_identifier::ptr field;

    expr_field(location const& loc, expr obj, expr_identifier::ptr field);
    friend auto operator==(expr_field const& lhs, expr_field const& rhs) -> bool;
};

struct expr_array : public node
{
    using ptr = std::unique_ptr<expr_array>;

    expr obj;
    expr key;

    expr_array(location const& loc, expr obj, expr key);
    friend auto operator==(expr_array const& lhs, expr_array const& rhs) -> bool;
};

struct expr_reference : public node
{
    using ptr = std::unique_ptr<expr_reference>;

    expr_path::ptr path;
    expr_identifier::ptr name;

    expr_reference(location const& loc, expr_path::ptr path, expr_identifier::ptr name);
};

struct expr_getnextarraykey : public node
{
    using ptr = std::unique_ptr<expr_getnextarraykey>;

    expr arg1;
    expr arg2;

    expr_getnextarraykey(location const& loc, expr arg1, expr arg2);
};

struct expr_getfirstarraykey : public node
{
    using ptr = std::unique_ptr<expr_getfirstarraykey>;

    expr arg;

    expr_getfirstarraykey(location const& loc, expr arg);
};

struct expr_getdvarcoloralpha : public node
{
    using ptr = std::unique_ptr<expr_getdvarcoloralpha>;

    expr arg;

    expr_getdvarcoloralpha(location const& loc, expr arg);
};

struct expr_getdvarcolorblue : public node
{
    using ptr = std::unique_ptr<expr_getdvarcolorblue>;

    expr arg;

    expr_getdvarcolorblue(location const& loc, expr arg);
};

struct expr_getdvarcolorgreen : public node
{
    using ptr = std::unique_ptr<expr_getdvarcolorgreen>;

    expr arg;

    expr_getdvarcolorgreen(location const& loc, expr arg);
};

struct expr_getdvarcolorred : public node
{
    using ptr = std::unique_ptr<expr_getdvarcolorred>;

    expr arg;

    expr_getdvarcolorred(location const& loc, expr arg);
};

struct expr_getdvarvector : public node
{
    using ptr = std::unique_ptr<expr_getdvarvector>;

    expr arg;

    expr_getdvarvector(location const& loc, expr arg);
};

struct expr_getdvarfloat : public node
{
    using ptr = std::unique_ptr<expr_getdvarfloat>;

    expr arg;

    expr_getdvarfloat(location const& loc, expr arg);
};

struct expr_getdvarint : public node
{
    using ptr = std::unique_ptr<expr_getdvarint>;

    expr arg;

    expr_getdvarint(location const& loc, expr arg);
};


struct expr_getdvar : public node
{
    using ptr = std::unique_ptr<expr_getdvar>;

    expr arg;

    expr_getdvar(location const& loc, expr arg);
};

struct expr_gettime : public node
{
    using ptr = std::unique_ptr<expr_gettime>;

    expr_gettime(location const& loc);
};

struct expr_abs : public node
{
    using ptr = std::unique_ptr<expr_abs>;

    expr arg;

    expr_abs(location const& loc, expr arg);
};

struct expr_vectortoangles : public node
{
    using ptr = std::unique_ptr<expr_vectortoangles>;

    expr arg;

    expr_vectortoangles(location const& loc, expr arg);
};

struct expr_angleclamp180 : public node
{
    using ptr = std::unique_ptr<expr_angleclamp180>;

    expr arg;

    expr_angleclamp180(location const& loc, expr arg);
};

struct expr_anglestoforward : public node
{
    using ptr = std::unique_ptr<expr_anglestoforward>;

    expr arg;

    expr_anglestoforward(const location& loc, expr arg);
};

struct expr_anglestoright : public node
{
    using ptr = std::unique_ptr<expr_anglestoright>;

    expr arg;

    expr_anglestoright(location const& loc, expr arg);
};

struct expr_anglestoup : public node
{
    using ptr = std::unique_ptr<expr_anglestoup>;

    expr arg;

    expr_anglestoup(location const& loc, expr arg);
};

struct expr_vectorscale : public node
{
    using ptr = std::unique_ptr<expr_vectorscale>;

    expr arg1;
    expr arg2;

    expr_vectorscale(location const& loc, expr arg1, expr arg2);
};

struct expr_isdefined : public node
{
    using ptr = std::unique_ptr<expr_isdefined>;

    expr value;

    expr_isdefined(location const& loc, expr value);
};

struct expr_arguments : public node
{
    using ptr = std::unique_ptr<expr_arguments>;

    std::vector<expr> list;

    expr_arguments(location const& loc);
};

struct expr_parameters : public node
{
    using ptr = std::unique_ptr<expr_parameters>;

    std::vector<expr> list;

    expr_parameters(location const& loc);
};

struct expr_member : public node
{
    using ptr = std::unique_ptr<expr_member>;

    expr obj;
    expr_identifier::ptr name;
    expr_arguments::ptr args;
    call::mode mode;

    expr_member(location const& loc, expr obj, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode);
};

struct expr_pointer : public node
{
    using ptr = std::unique_ptr<expr_pointer>;

    expr func;
    expr_arguments::ptr args;
    call::mode mode;

    expr_pointer(location const& loc, expr func, expr_arguments::ptr args, call::mode mode);
};

struct expr_function : public node
{
    using ptr = std::unique_ptr<expr_function>;

    expr_path::ptr path;
    expr_identifier::ptr name;
    expr_arguments::ptr args;
    call::mode mode;

    expr_function(location const& loc, expr_path::ptr path, expr_identifier::ptr name, expr_arguments::ptr args, call::mode mode);
};

struct expr_method : public node
{
    using ptr = std::unique_ptr<expr_method>;

    expr obj;
    call value;

    expr_method(location const& loc, expr obj, call value);
};

struct expr_call : public node
{
    using ptr = std::unique_ptr<expr_call>;

    call value;

    expr_call(location const& loc, call value);
};

struct expr_new : public node
{
    using ptr = std::unique_ptr<expr_new>;

    expr_identifier::ptr name;

    expr_new(location const& loc, expr_identifier::ptr name);
};

struct expr_complement : public node
{
    using ptr = std::unique_ptr<expr_complement>;

    expr rvalue;

    expr_complement(location const& loc, expr rvalue);
};

struct expr_negate : public node
{
    using ptr = std::unique_ptr<expr_negate>;

    expr rvalue;

    expr_negate(location const& loc, expr rvalue);
};

struct expr_not : public node
{
    using ptr = std::unique_ptr<expr_not>;

    expr rvalue;

    expr_not(location const& loc, expr rvalue);
};

struct expr_binary : public node
{
    using ptr = std::unique_ptr<expr_binary>;

    expr lvalue;
    expr rvalue;

    expr_binary(type t, location const& loc, expr lvalue, expr rvalue);
};

struct expr_add : public expr_binary
{
    using ptr = std::unique_ptr<expr_add>;

    expr_add(location const& loc, expr lvalue, expr rvalue);
};

struct expr_sub : public expr_binary
{
    using ptr = std::unique_ptr<expr_sub>;

    expr_sub(location const& loc, expr lvalue, expr rvalue);
};

struct expr_mul : public expr_binary
{
    using ptr = std::unique_ptr<expr_mul>;

    expr_mul(location const& loc, expr lvalue, expr rvalue);
};

struct expr_div : public expr_binary
{
    using ptr = std::unique_ptr<expr_div>;

    expr_div(location const& loc, expr lvalue, expr rvalue);
};

struct expr_mod : public expr_binary
{
    using ptr = std::unique_ptr<expr_mod>;

    expr_mod(location const& loc, expr lvalue, expr rvalue);
};

struct expr_shift_left : public expr_binary
{
    using ptr = std::unique_ptr<expr_shift_left>;

    expr_shift_left(location const& loc, expr lvalue, expr rvalue);
};

struct expr_shift_right : public expr_binary
{
    using ptr = std::unique_ptr<expr_shift_right>;

    expr_shift_right(location const& loc, expr lvalue, expr rvalue);
};

struct expr_bitwise_or : public expr_binary
{
    using ptr = std::unique_ptr<expr_bitwise_or>;

    expr_bitwise_or(location const& loc, expr lvalue, expr rvalue);
};

struct expr_bitwise_and : public expr_binary
{
    using ptr = std::unique_ptr<expr_bitwise_and>;

    expr_bitwise_and(location const& loc, expr lvalue, expr rvalue);
};

struct expr_bitwise_exor : public expr_binary
{
    using ptr = std::unique_ptr<expr_bitwise_exor>;

    expr_bitwise_exor(location const& loc, expr lvalue, expr rvalue);
};

struct expr_super_equal : public expr_binary
{
    using ptr = std::unique_ptr<expr_super_equal>;

    expr_super_equal(location const& loc, expr lvalue, expr rvalue);
};

struct expr_super_not_equal : public expr_binary
{
    using ptr = std::unique_ptr<expr_super_not_equal>;

    expr_super_not_equal(location const& loc, expr lvalue, expr rvalue);
};

struct expr_equality : public expr_binary
{
    using ptr = std::unique_ptr<expr_equality>;

    expr_equality(location const& loc, expr lvalue, expr rvalue);
};

struct expr_inequality : public expr_binary
{
    using ptr = std::unique_ptr<expr_inequality>;

    expr_inequality(location const& loc, expr lvalue, expr rvalue);
};

struct expr_less_equal : public expr_binary
{
    using ptr = std::unique_ptr<expr_less_equal>;

    expr_less_equal(location const& loc, expr lvalue, expr rvalue);
};

struct expr_greater_equal : public expr_binary
{
    using ptr = std::unique_ptr<expr_greater_equal>;

    expr_greater_equal(location const& loc, expr lvalue, expr rvalue);
};

struct expr_less : public expr_binary
{
    using ptr = std::unique_ptr<expr_less>;

    expr_less(location const& loc, expr lvalue, expr rvalue);
};

struct expr_greater : public expr_binary
{
    using ptr = std::unique_ptr<expr_greater>;

    expr_greater(location const& loc, expr lvalue, expr rvalue);
};

struct expr_or : public expr_binary
{
    using ptr = std::unique_ptr<expr_or>;

    expr_or(location const& loc, expr lvalue, expr rvalue);
};

struct expr_and : public expr_binary
{
    using ptr = std::unique_ptr<expr_and>;

    expr_and(location const& loc, expr lvalue, expr rvalue);
};

struct expr_ternary : public node
{
    using ptr = std::unique_ptr<expr_ternary>;

    expr test;
    expr true_expr;
    expr false_expr;

    expr_ternary(location const& loc, expr test, expr true_expr, expr false_expr);
};

struct expr_increment : node
{
    using ptr = std::unique_ptr<expr_increment>;

    expr lvalue;
    bool prefix;

    expr_increment(location const& loc, expr lvalue, bool prefix);
};

struct expr_decrement : node
{
    using ptr = std::unique_ptr<expr_decrement>;

    expr lvalue;
    bool prefix;

    expr_decrement(location const& loc, expr lvalue, bool prefix);
};

struct expr_assign : public node
{
    using ptr = std::unique_ptr<expr_assign>;

    expr lvalue;
    expr rvalue;

    expr_assign(type t, location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_equal : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_equal>;

    expr_assign_equal(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_add : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_add>;

    expr_assign_add(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_sub : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_sub>;

    expr_assign_sub(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_mul : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_mul>;

    expr_assign_mul(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_div : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_div>;

    expr_assign_div(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_mod : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_mod>;

    expr_assign_mod(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_shift_left : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_shift_left>;

    expr_assign_shift_left(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_shift_right : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_shift_right>;

    expr_assign_shift_right(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_bitwise_or : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_bitwise_or>;

    expr_assign_bitwise_or(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_bitwise_and : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_bitwise_and>;

    expr_assign_bitwise_and(location const& loc, expr lvalue, expr rvalue);
};

struct expr_assign_bitwise_exor : public expr_assign
{
    using ptr = std::unique_ptr<expr_assign_bitwise_exor>;

    expr_assign_bitwise_exor(location const& loc, expr lvalue, expr rvalue);
};

struct stmt_list : public node
{
    using ptr = std::unique_ptr<stmt_list>;

    std::vector<stmt> list;

    stmt_list(location const& loc);
};

struct stmt_comp : public node
{
    using ptr = std::unique_ptr<stmt_comp>;

    stmt_list::ptr block;

    stmt_comp(location const& loc, stmt_list::ptr block);
};

struct stmt_dev : public node
{
    using ptr = std::unique_ptr<stmt_dev>;

    stmt_list::ptr block;

    stmt_dev(location const& loc, stmt_list::ptr block);
};

struct stmt_expr : public node
{
    using ptr = std::unique_ptr<stmt_expr>;

    expr value;

    stmt_expr(location const& loc, expr value);
};

struct stmt_call : public node
{
    using ptr = std::unique_ptr<stmt_call>;

    expr value;

    stmt_call(location const& loc, expr value);
};

struct stmt_const : public node
{
    using ptr = std::unique_ptr<stmt_const>;

    expr_identifier::ptr lvalue;
    expr rvalue;

    stmt_const(location const& loc, expr_identifier::ptr lvalue, expr rvalue);
};

struct stmt_assign : public node
{
    using ptr = std::unique_ptr<stmt_assign>;

    expr value;

    stmt_assign(location const& loc, expr value);
};

struct stmt_endon : public node
{
    using ptr = std::unique_ptr<stmt_endon>;

    expr obj;
    expr event;

    stmt_endon(location const& loc, expr obj, expr event);
};

struct stmt_notify : public node
{
    using ptr = std::unique_ptr<stmt_notify>;

    expr obj;
    expr event;
    expr_arguments::ptr args;

    stmt_notify(location const& loc, expr obj, expr event, expr_arguments::ptr args);
};

struct stmt_realwait : public node
{
    using ptr = std::unique_ptr<stmt_realwait>;

    expr time;

    stmt_realwait(location const& loc, expr time);
};

struct stmt_wait : public node
{
    using ptr = std::unique_ptr<stmt_wait>;

    expr time;

    stmt_wait(location const& loc, expr time);
};

struct stmt_waittill : public node
{
    using ptr = std::unique_ptr<stmt_waittill>;

    expr obj;
    expr event;
    expr_arguments::ptr args;

    stmt_waittill(location const& loc, expr obj, expr event, expr_arguments::ptr args);
};

struct stmt_waittillmatch : public node
{
    using ptr = std::unique_ptr<stmt_waittillmatch>;

    expr obj;
    expr event;
    expr_arguments::ptr args;

    stmt_waittillmatch(location const& loc, expr obj, expr expr, expr_arguments::ptr args);
};

struct stmt_waittillframeend : public node
{
    using ptr = std::unique_ptr<stmt_waittillframeend>;

    stmt_waittillframeend(location const& loc);
};

struct stmt_if : public node
{
    using ptr = std::unique_ptr<stmt_if>;

    expr test;
    stmt body;

    stmt_if(location const& loc, expr test, stmt body);
};

struct stmt_ifelse : public node
{
    using ptr = std::unique_ptr<stmt_ifelse>;

    expr test;
    stmt stmt_if;
    stmt stmt_else;

    stmt_ifelse(location const& loc, expr test, stmt stmt_if, stmt stmt_else);
};

struct stmt_while : public node
{
    using ptr = std::unique_ptr<stmt_while>;

    expr test;
    stmt body;

    stmt_while(location const& loc, expr test, stmt body);
};

struct stmt_dowhile : public node
{
    using ptr = std::unique_ptr<stmt_dowhile>;

    expr test;
    stmt body;

    stmt_dowhile(location const& loc, expr test, stmt body);
};

struct stmt_for : public node
{
    using ptr = std::unique_ptr<stmt_for>;

    stmt init;
    expr test;
    stmt iter;
    stmt body;

    stmt_for(location const& loc, stmt init, expr test, stmt iter, stmt body);
};

struct stmt_foreach : public node
{
    using ptr = std::unique_ptr<stmt_foreach>;

    expr container;
    expr value;
    expr array;
    expr key;
    stmt body;
    bool use_key;

    stmt_foreach(location const& loc, expr container, expr value, expr array, expr key, stmt body, bool use_key);
};

struct stmt_switch : public node
{
    using ptr = std::unique_ptr<stmt_switch>;

    expr test;
    stmt_comp::ptr body;

    stmt_switch(location const& loc, expr test, stmt_comp::ptr body);
};

struct stmt_case : public node
{
    using ptr = std::unique_ptr<stmt_case>;

    expr value;
    stmt_list::ptr body;

    stmt_case(location const& loc, expr value);
    stmt_case(location const& loc, expr value, stmt_list::ptr body);
};

struct stmt_default : public node
{
    using ptr = std::unique_ptr<stmt_default>;

    stmt_list::ptr body;

    stmt_default(location const& loc);
    stmt_default(location const& loc, stmt_list::ptr body);
};

struct stmt_break : public node
{
    using ptr = std::unique_ptr<stmt_break>;

    stmt_break(location const& loc);
};

struct stmt_continue : public node
{
    using ptr = std::unique_ptr<stmt_continue>;

    stmt_continue(location const& loc);
};

struct stmt_return : public node
{
    using ptr = std::unique_ptr<stmt_return>;

    expr value;

    stmt_return(location const& loc, expr value);
};

struct stmt_breakpoint : public node
{
    using ptr = std::unique_ptr<stmt_breakpoint>;

    stmt_breakpoint(location const& loc);
};

struct stmt_prof_begin : public node
{
    using ptr = std::unique_ptr<stmt_prof_begin>;

    expr_arguments::ptr args;

    stmt_prof_begin(location const& loc, expr_arguments::ptr args);
};

struct stmt_prof_end : public node
{
    using ptr = std::unique_ptr<stmt_prof_end>;

    expr_arguments::ptr args;

    stmt_prof_end(location const& loc, expr_arguments::ptr args);
};

struct decl_function : public node
{
    using ptr = std::unique_ptr<decl_function>;

    expr_identifier::ptr space;
    expr_identifier::ptr name;
    expr_parameters::ptr params;
    stmt_comp::ptr body;
    export_flags flags;

    decl_function(location const& loc, expr_identifier::ptr space, expr_identifier::ptr name, expr_parameters::ptr params, stmt_comp::ptr body, export_flags flags);
};

struct decl_usingtree : public node
{
    using ptr = std::unique_ptr<decl_usingtree>;

    expr_string::ptr name;

    decl_usingtree(location const& loc, expr_string::ptr name);
};

struct decl_namespace : public node
{
    using ptr = std::unique_ptr<decl_namespace>;

    expr_string::ptr name;

    decl_namespace(location const& loc, expr_string::ptr name);
};


struct decl_dev_begin : public node
{
    using ptr = std::unique_ptr<decl_dev_begin>;

    decl_dev_begin(location const& loc);
};

struct decl_dev_end : public node
{
    using ptr = std::unique_ptr<decl_dev_end>;

    decl_dev_end(location const& loc);
};

struct include : public node
{
    using ptr = std::unique_ptr<include>;

    expr_path::ptr path;

    include(location const& loc, expr_path::ptr path);
};

struct program : public node
{
    using ptr = std::unique_ptr<program>;

    std::vector<include::ptr> includes;
    std::vector<decl> declarations;

    program();
    program(location const& loc);
};

struct asm_loc : public node
{
    using ptr = std::unique_ptr<asm_loc>;

    std::string value;

    asm_loc(location const& loc, std::string const& value);
};

struct asm_jmp : public node
{
    using ptr = std::unique_ptr<asm_jmp>;

    std::string value;

    asm_jmp(location const& loc, std::string const& value);
};

struct asm_jmp_back : public node
{
    using ptr = std::unique_ptr<asm_jmp_back>;

    std::string value;

    asm_jmp_back(location const& loc, std::string const& value);
};

struct asm_jmp_cond : public node
{
    using ptr = std::unique_ptr<asm_jmp_cond>;

    expr test;
    std::string value;

    asm_jmp_cond(location const& loc, expr test, std::string const& value);
};

struct asm_jmp_true : public node
{
    using ptr = std::unique_ptr<asm_jmp_true>;

    expr test;
    std::string value;

    asm_jmp_true(location const& loc, expr test, std::string const& value);
};

struct asm_jmp_false : public node
{
    using ptr = std::unique_ptr<asm_jmp_false>;

    expr test;
    std::string value;

    asm_jmp_false(location const& loc, expr test, std::string const& value);
};

struct asm_switch : public node
{
    using ptr = std::unique_ptr<asm_switch>;

    expr test;
    std::string value;

    asm_switch(location const& loc, expr test, std::string const& value);
};

struct asm_endswitch : public node
{
    using ptr = std::unique_ptr<asm_endswitch>;

    std::vector<std::string> data;

    asm_endswitch(location const& loc, std::vector<std::string> data);
};

struct asm_prescriptcall : public node
{
    using ptr = std::unique_ptr<asm_prescriptcall>;

    asm_prescriptcall(location const& loc);
};

struct asm_voidcodepos : public node
{
    using ptr = std::unique_ptr<asm_voidcodepos>;

    asm_voidcodepos(location const& loc);
};

struct asm_dev : public node
{
    using ptr = std::unique_ptr<asm_dev>;

    std::string value;

    asm_dev(location const& loc, std::string const& value);
};

#define XSK_ARC_MAKE_GENERIC(node_type)                                             \
template<class... Args>                                                             \
inline auto make_ ## node_type(Args&&... args) -> std::unique_ptr<node_type>        \
{                                                                                   \
    return std::unique_ptr<node_type>(new node_type(std::forward<Args>(args)...));  \
}

XSK_ARC_MAKE_GENERIC(node)
XSK_ARC_MAKE_GENERIC(expr_true)
XSK_ARC_MAKE_GENERIC(expr_false)
XSK_ARC_MAKE_GENERIC(expr_integer)
XSK_ARC_MAKE_GENERIC(expr_float)
XSK_ARC_MAKE_GENERIC(expr_vector)
XSK_ARC_MAKE_GENERIC(expr_hash)
XSK_ARC_MAKE_GENERIC(expr_string)
XSK_ARC_MAKE_GENERIC(expr_istring)
XSK_ARC_MAKE_GENERIC(expr_path)
XSK_ARC_MAKE_GENERIC(expr_identifier)
XSK_ARC_MAKE_GENERIC(expr_animtree)
XSK_ARC_MAKE_GENERIC(expr_animation)
XSK_ARC_MAKE_GENERIC(expr_classes)
XSK_ARC_MAKE_GENERIC(expr_world)
XSK_ARC_MAKE_GENERIC(expr_level)
XSK_ARC_MAKE_GENERIC(expr_anim)
XSK_ARC_MAKE_GENERIC(expr_self)
XSK_ARC_MAKE_GENERIC(expr_game)
XSK_ARC_MAKE_GENERIC(expr_undefined)
XSK_ARC_MAKE_GENERIC(expr_empty_array)
XSK_ARC_MAKE_GENERIC(expr_ellipsis)
XSK_ARC_MAKE_GENERIC(expr_paren)
XSK_ARC_MAKE_GENERIC(expr_size)
XSK_ARC_MAKE_GENERIC(expr_field)
XSK_ARC_MAKE_GENERIC(expr_array)
XSK_ARC_MAKE_GENERIC(expr_reference)
XSK_ARC_MAKE_GENERIC(expr_getnextarraykey)
XSK_ARC_MAKE_GENERIC(expr_getfirstarraykey)
XSK_ARC_MAKE_GENERIC(expr_getdvarcoloralpha)
XSK_ARC_MAKE_GENERIC(expr_getdvarcolorblue)
XSK_ARC_MAKE_GENERIC(expr_getdvarcolorgreen)
XSK_ARC_MAKE_GENERIC(expr_getdvarcolorred)
XSK_ARC_MAKE_GENERIC(expr_getdvarvector)
XSK_ARC_MAKE_GENERIC(expr_getdvarfloat)
XSK_ARC_MAKE_GENERIC(expr_getdvarint)
XSK_ARC_MAKE_GENERIC(expr_getdvar)
XSK_ARC_MAKE_GENERIC(expr_gettime)
XSK_ARC_MAKE_GENERIC(expr_abs)
XSK_ARC_MAKE_GENERIC(expr_vectortoangles)
XSK_ARC_MAKE_GENERIC(expr_angleclamp180)
XSK_ARC_MAKE_GENERIC(expr_anglestoforward)
XSK_ARC_MAKE_GENERIC(expr_anglestoright)
XSK_ARC_MAKE_GENERIC(expr_anglestoup)
XSK_ARC_MAKE_GENERIC(expr_vectorscale)
XSK_ARC_MAKE_GENERIC(expr_isdefined)
XSK_ARC_MAKE_GENERIC(expr_arguments)
XSK_ARC_MAKE_GENERIC(expr_parameters)
XSK_ARC_MAKE_GENERIC(expr_member)
XSK_ARC_MAKE_GENERIC(expr_pointer)
XSK_ARC_MAKE_GENERIC(expr_function)
XSK_ARC_MAKE_GENERIC(expr_method)
XSK_ARC_MAKE_GENERIC(expr_call)
XSK_ARC_MAKE_GENERIC(expr_new)
XSK_ARC_MAKE_GENERIC(expr_complement)
XSK_ARC_MAKE_GENERIC(expr_negate)
XSK_ARC_MAKE_GENERIC(expr_not)
XSK_ARC_MAKE_GENERIC(expr_add)
XSK_ARC_MAKE_GENERIC(expr_sub)
XSK_ARC_MAKE_GENERIC(expr_mul)
XSK_ARC_MAKE_GENERIC(expr_div)
XSK_ARC_MAKE_GENERIC(expr_mod)
XSK_ARC_MAKE_GENERIC(expr_shift_left)
XSK_ARC_MAKE_GENERIC(expr_shift_right)
XSK_ARC_MAKE_GENERIC(expr_bitwise_or)
XSK_ARC_MAKE_GENERIC(expr_bitwise_and)
XSK_ARC_MAKE_GENERIC(expr_bitwise_exor)
XSK_ARC_MAKE_GENERIC(expr_super_equal)
XSK_ARC_MAKE_GENERIC(expr_super_not_equal)
XSK_ARC_MAKE_GENERIC(expr_equality)
XSK_ARC_MAKE_GENERIC(expr_inequality)
XSK_ARC_MAKE_GENERIC(expr_less_equal)
XSK_ARC_MAKE_GENERIC(expr_greater_equal)
XSK_ARC_MAKE_GENERIC(expr_less)
XSK_ARC_MAKE_GENERIC(expr_greater)
XSK_ARC_MAKE_GENERIC(expr_or)
XSK_ARC_MAKE_GENERIC(expr_and)
XSK_ARC_MAKE_GENERIC(expr_ternary)
XSK_ARC_MAKE_GENERIC(expr_increment)
XSK_ARC_MAKE_GENERIC(expr_decrement)
XSK_ARC_MAKE_GENERIC(expr_assign_equal)
XSK_ARC_MAKE_GENERIC(expr_assign_add)
XSK_ARC_MAKE_GENERIC(expr_assign_sub)
XSK_ARC_MAKE_GENERIC(expr_assign_mul)
XSK_ARC_MAKE_GENERIC(expr_assign_div)
XSK_ARC_MAKE_GENERIC(expr_assign_mod)
XSK_ARC_MAKE_GENERIC(expr_assign_shift_left)
XSK_ARC_MAKE_GENERIC(expr_assign_shift_right)
XSK_ARC_MAKE_GENERIC(expr_assign_bitwise_or)
XSK_ARC_MAKE_GENERIC(expr_assign_bitwise_and)
XSK_ARC_MAKE_GENERIC(expr_assign_bitwise_exor)
XSK_ARC_MAKE_GENERIC(stmt_list)
XSK_ARC_MAKE_GENERIC(stmt_comp)
XSK_ARC_MAKE_GENERIC(stmt_dev)
XSK_ARC_MAKE_GENERIC(stmt_expr)
XSK_ARC_MAKE_GENERIC(stmt_call)
XSK_ARC_MAKE_GENERIC(stmt_assign)
XSK_ARC_MAKE_GENERIC(stmt_endon)
XSK_ARC_MAKE_GENERIC(stmt_notify)
XSK_ARC_MAKE_GENERIC(stmt_realwait)
XSK_ARC_MAKE_GENERIC(stmt_wait)
XSK_ARC_MAKE_GENERIC(stmt_waittill)
XSK_ARC_MAKE_GENERIC(stmt_waittillmatch)
XSK_ARC_MAKE_GENERIC(stmt_waittillframeend)
XSK_ARC_MAKE_GENERIC(stmt_if)
XSK_ARC_MAKE_GENERIC(stmt_ifelse)
XSK_ARC_MAKE_GENERIC(stmt_while)
XSK_ARC_MAKE_GENERIC(stmt_dowhile)
XSK_ARC_MAKE_GENERIC(stmt_for)
XSK_ARC_MAKE_GENERIC(stmt_foreach)
XSK_ARC_MAKE_GENERIC(stmt_switch)
XSK_ARC_MAKE_GENERIC(stmt_case)
XSK_ARC_MAKE_GENERIC(stmt_default)
XSK_ARC_MAKE_GENERIC(stmt_break)
XSK_ARC_MAKE_GENERIC(stmt_continue)
XSK_ARC_MAKE_GENERIC(stmt_return)
XSK_ARC_MAKE_GENERIC(stmt_breakpoint)
XSK_ARC_MAKE_GENERIC(stmt_prof_begin)
XSK_ARC_MAKE_GENERIC(stmt_prof_end)
XSK_ARC_MAKE_GENERIC(decl_function)
XSK_ARC_MAKE_GENERIC(decl_usingtree)
XSK_ARC_MAKE_GENERIC(decl_dev_begin)
XSK_ARC_MAKE_GENERIC(decl_dev_end)
XSK_ARC_MAKE_GENERIC(include)
XSK_ARC_MAKE_GENERIC(program)
XSK_ARC_MAKE_GENERIC(asm_loc)
XSK_ARC_MAKE_GENERIC(asm_jmp)
XSK_ARC_MAKE_GENERIC(asm_jmp_back)
XSK_ARC_MAKE_GENERIC(asm_jmp_cond)
XSK_ARC_MAKE_GENERIC(asm_jmp_false)
XSK_ARC_MAKE_GENERIC(asm_jmp_true)
XSK_ARC_MAKE_GENERIC(asm_switch)
XSK_ARC_MAKE_GENERIC(asm_endswitch)
XSK_ARC_MAKE_GENERIC(asm_prescriptcall)
XSK_ARC_MAKE_GENERIC(asm_voidcodepos)
XSK_ARC_MAKE_GENERIC(asm_dev)

#undef XSK_ARC_MAKE_GENERIC

} // namespace xsk::arc
