// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// "%code top" blocks.
#line 42 "parser2.ypp"

#include "xsk/stdinc.hpp"
#include "xsk/arc/parser2.hpp"
#include "xsk/arc/preprocessor.hpp"
using namespace xsk::arc;
namespace xsk::arc
{ 
    auto ARC2lex(context const* ctx_, preprocessor& ppr) -> parser2::symbol_type;
    auto parse_switch2(stmt_switch& stm) -> void;
}

#line 51 "parser2.cpp"

// Take the name prefix into account.
#define yylex   ARC2lex



#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if ARC2DEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !ARC2DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !ARC2DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "parser2.ypp"
namespace xsk { namespace arc {
#line 153 "parser2.cpp"

  /// Build a parser object.
  parser2::parser2 (xsk::arc::context const* ctx__yyarg, xsk::arc::preprocessor& ppr_yyarg, xsk::arc::program::ptr& ast_yyarg, std::uint32_t index_yyarg)
#if ARC2DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      ctx_ (ctx__yyarg),
      ppr (ppr_yyarg),
      ast (ast_yyarg),
      index (index_yyarg)
  {}

  parser2::~parser2 ()
  {}

  parser2::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser2::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser2::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser2::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser2::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser2::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser2::symbol_kind_type
  parser2::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser2::stack_symbol_type::stack_symbol_type ()
  {}

  parser2::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_pointer: // expr_pointer
      case symbol_kind::S_expr_member: // expr_member
        value.YY_MOVE_OR_COPY< call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< decl::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_class: // decl_class
        value.YY_MOVE_OR_COPY< decl_class::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.YY_MOVE_OR_COPY< decl_function::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.YY_MOVE_OR_COPY< decl_list::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        value.YY_MOVE_OR_COPY< decl_namespace::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.YY_MOVE_OR_COPY< decl_usingtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_variable: // decl_variable
        value.YY_MOVE_OR_COPY< decl_variable::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_object: // expr_object
        value.YY_MOVE_OR_COPY< expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        value.YY_MOVE_OR_COPY< expr_abs::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        value.YY_MOVE_OR_COPY< expr_angleclamp180::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        value.YY_MOVE_OR_COPY< expr_anglestoforward::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        value.YY_MOVE_OR_COPY< expr_anglestoright::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        value.YY_MOVE_OR_COPY< expr_anglestoup::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.YY_MOVE_OR_COPY< expr_anim::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.YY_MOVE_OR_COPY< expr_animation::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.YY_MOVE_OR_COPY< expr_animtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.YY_MOVE_OR_COPY< expr_arguments::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.YY_MOVE_OR_COPY< expr_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.YY_MOVE_OR_COPY< expr_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_classes: // expr_classes
        value.YY_MOVE_OR_COPY< expr_classes::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.YY_MOVE_OR_COPY< expr_complement::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.YY_MOVE_OR_COPY< expr_empty_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.YY_MOVE_OR_COPY< expr_false::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.YY_MOVE_OR_COPY< expr_field::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.YY_MOVE_OR_COPY< expr_float::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.YY_MOVE_OR_COPY< expr_game::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        value.YY_MOVE_OR_COPY< expr_getdvar::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        value.YY_MOVE_OR_COPY< expr_getdvarcoloralpha::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        value.YY_MOVE_OR_COPY< expr_getdvarcolorblue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        value.YY_MOVE_OR_COPY< expr_getdvarcolorgreen::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        value.YY_MOVE_OR_COPY< expr_getdvarcolorred::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        value.YY_MOVE_OR_COPY< expr_getdvarfloat::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        value.YY_MOVE_OR_COPY< expr_getdvarint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        value.YY_MOVE_OR_COPY< expr_getdvarvector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        value.YY_MOVE_OR_COPY< expr_getfirstarraykey::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        value.YY_MOVE_OR_COPY< expr_getnextarraykey::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        value.YY_MOVE_OR_COPY< expr_gettime::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        value.YY_MOVE_OR_COPY< expr_hash::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_class_base: // opt_class_base
      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.YY_MOVE_OR_COPY< expr_identifier::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.YY_MOVE_OR_COPY< expr_integer::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.YY_MOVE_OR_COPY< expr_isdefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.YY_MOVE_OR_COPY< expr_istring::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.YY_MOVE_OR_COPY< expr_level::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.YY_MOVE_OR_COPY< expr_method::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.YY_MOVE_OR_COPY< expr_negate::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_new: // expr_new
        value.YY_MOVE_OR_COPY< expr_new::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.YY_MOVE_OR_COPY< expr_not::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.YY_MOVE_OR_COPY< expr_parameters::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.YY_MOVE_OR_COPY< expr_paren::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.YY_MOVE_OR_COPY< expr_path::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.YY_MOVE_OR_COPY< expr_reference::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.YY_MOVE_OR_COPY< expr_self::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.YY_MOVE_OR_COPY< expr_size::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.YY_MOVE_OR_COPY< expr_string::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.YY_MOVE_OR_COPY< expr_true::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.YY_MOVE_OR_COPY< expr_undefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.YY_MOVE_OR_COPY< expr_vector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        value.YY_MOVE_OR_COPY< expr_vectorscale::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        value.YY_MOVE_OR_COPY< expr_vectortoangles::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_world: // expr_world
        value.YY_MOVE_OR_COPY< expr_world::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using: // using
        value.YY_MOVE_OR_COPY< include::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< program::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASHSTR: // "hash string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.YY_MOVE_OR_COPY< stmt::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.YY_MOVE_OR_COPY< stmt_break::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.YY_MOVE_OR_COPY< stmt_case::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        value.YY_MOVE_OR_COPY< stmt_comp::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.YY_MOVE_OR_COPY< stmt_continue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.YY_MOVE_OR_COPY< stmt_default::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.YY_MOVE_OR_COPY< stmt_dev::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.YY_MOVE_OR_COPY< stmt_dowhile::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.YY_MOVE_OR_COPY< stmt_endon::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_const: // stmt_const
      case symbol_kind::S_stmt_assign: // stmt_assign
        value.YY_MOVE_OR_COPY< stmt_expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.YY_MOVE_OR_COPY< stmt_for::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.YY_MOVE_OR_COPY< stmt_foreach::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.YY_MOVE_OR_COPY< stmt_if::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.YY_MOVE_OR_COPY< stmt_ifelse::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        value.YY_MOVE_OR_COPY< stmt_list::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.YY_MOVE_OR_COPY< stmt_notify::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.YY_MOVE_OR_COPY< stmt_prof_begin::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.YY_MOVE_OR_COPY< stmt_prof_end::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.YY_MOVE_OR_COPY< stmt_return::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.YY_MOVE_OR_COPY< stmt_switch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.YY_MOVE_OR_COPY< stmt_wait::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waitrealtime: // stmt_waitrealtime
        value.YY_MOVE_OR_COPY< stmt_waitrealtime::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.YY_MOVE_OR_COPY< stmt_waittill::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.YY_MOVE_OR_COPY< stmt_waittillframeend::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.YY_MOVE_OR_COPY< stmt_waittillmatch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.YY_MOVE_OR_COPY< stmt_while::ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser2::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_pointer: // expr_pointer
      case symbol_kind::S_expr_member: // expr_member
        value.move< call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_class: // decl_class
        value.move< decl_class::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.move< decl_function::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< decl_list::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        value.move< decl_namespace::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.move< decl_usingtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_variable: // decl_variable
        value.move< decl_variable::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_object: // expr_object
        value.move< expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        value.move< expr_abs::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        value.move< expr_angleclamp180::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        value.move< expr_anglestoforward::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        value.move< expr_anglestoright::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        value.move< expr_anglestoup::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.move< expr_anim::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.move< expr_animation::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.move< expr_animtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.move< expr_arguments::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.move< expr_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.move< expr_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_classes: // expr_classes
        value.move< expr_classes::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.move< expr_complement::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.move< expr_empty_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.move< expr_false::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.move< expr_field::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.move< expr_float::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.move< expr_game::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        value.move< expr_getdvar::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        value.move< expr_getdvarcoloralpha::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        value.move< expr_getdvarcolorblue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        value.move< expr_getdvarcolorgreen::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        value.move< expr_getdvarcolorred::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        value.move< expr_getdvarfloat::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        value.move< expr_getdvarint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        value.move< expr_getdvarvector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        value.move< expr_getfirstarraykey::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        value.move< expr_getnextarraykey::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        value.move< expr_gettime::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        value.move< expr_hash::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_class_base: // opt_class_base
      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.move< expr_identifier::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.move< expr_integer::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.move< expr_isdefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.move< expr_istring::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.move< expr_level::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.move< expr_method::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.move< expr_negate::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_new: // expr_new
        value.move< expr_new::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.move< expr_not::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.move< expr_parameters::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.move< expr_paren::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.move< expr_path::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.move< expr_reference::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.move< expr_self::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.move< expr_size::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.move< expr_string::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.move< expr_true::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.move< expr_undefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.move< expr_vector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        value.move< expr_vectorscale::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        value.move< expr_vectortoangles::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_world: // expr_world
        value.move< expr_world::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using: // using
        value.move< include::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< program::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASHSTR: // "hash string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.move< stmt::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< stmt_break::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< stmt_case::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        value.move< stmt_comp::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< stmt_continue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< stmt_default::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.move< stmt_dev::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.move< stmt_dowhile::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< stmt_endon::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_const: // stmt_const
      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< stmt_for::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< stmt_foreach::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< stmt_if::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< stmt_ifelse::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        value.move< stmt_list::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< stmt_notify::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.move< stmt_prof_begin::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.move< stmt_prof_end::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< stmt_return::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< stmt_switch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< stmt_wait::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waitrealtime: // stmt_waitrealtime
        value.move< stmt_waitrealtime::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< stmt_waittill::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< stmt_waittillframeend::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< stmt_waittillmatch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< stmt_while::ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser2::stack_symbol_type&
  parser2::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_pointer: // expr_pointer
      case symbol_kind::S_expr_member: // expr_member
        value.copy< call::ptr > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< decl::ptr > (that.value);
        break;

      case symbol_kind::S_decl_class: // decl_class
        value.copy< decl_class::ptr > (that.value);
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.copy< decl_function::ptr > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< decl_list::ptr > (that.value);
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        value.copy< decl_namespace::ptr > (that.value);
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.copy< decl_usingtree::ptr > (that.value);
        break;

      case symbol_kind::S_decl_variable: // decl_variable
        value.copy< decl_variable::ptr > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_object: // expr_object
        value.copy< expr::ptr > (that.value);
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        value.copy< expr_abs::ptr > (that.value);
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        value.copy< expr_angleclamp180::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        value.copy< expr_anglestoforward::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        value.copy< expr_anglestoright::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        value.copy< expr_anglestoup::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.copy< expr_anim::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.copy< expr_animation::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.copy< expr_animtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.copy< expr_arguments::ptr > (that.value);
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.copy< expr_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.copy< expr_call::ptr > (that.value);
        break;

      case symbol_kind::S_expr_classes: // expr_classes
        value.copy< expr_classes::ptr > (that.value);
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.copy< expr_complement::ptr > (that.value);
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.copy< expr_empty_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.copy< expr_false::ptr > (that.value);
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.copy< expr_field::ptr > (that.value);
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.copy< expr_float::ptr > (that.value);
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.copy< expr_game::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        value.copy< expr_getdvar::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        value.copy< expr_getdvarcoloralpha::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        value.copy< expr_getdvarcolorblue::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        value.copy< expr_getdvarcolorgreen::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        value.copy< expr_getdvarcolorred::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        value.copy< expr_getdvarfloat::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        value.copy< expr_getdvarint::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        value.copy< expr_getdvarvector::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        value.copy< expr_getfirstarraykey::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        value.copy< expr_getnextarraykey::ptr > (that.value);
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        value.copy< expr_gettime::ptr > (that.value);
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        value.copy< expr_hash::ptr > (that.value);
        break;

      case symbol_kind::S_opt_class_base: // opt_class_base
      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.copy< expr_identifier::ptr > (that.value);
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.copy< expr_integer::ptr > (that.value);
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.copy< expr_isdefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.copy< expr_istring::ptr > (that.value);
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.copy< expr_level::ptr > (that.value);
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.copy< expr_method::ptr > (that.value);
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.copy< expr_negate::ptr > (that.value);
        break;

      case symbol_kind::S_expr_new: // expr_new
        value.copy< expr_new::ptr > (that.value);
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.copy< expr_not::ptr > (that.value);
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.copy< expr_parameters::ptr > (that.value);
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.copy< expr_paren::ptr > (that.value);
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.copy< expr_path::ptr > (that.value);
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.copy< expr_reference::ptr > (that.value);
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.copy< expr_self::ptr > (that.value);
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.copy< expr_size::ptr > (that.value);
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.copy< expr_string::ptr > (that.value);
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.copy< expr_true::ptr > (that.value);
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.copy< expr_undefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.copy< expr_vector::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        value.copy< expr_vectorscale::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        value.copy< expr_vectortoangles::ptr > (that.value);
        break;

      case symbol_kind::S_expr_world: // expr_world
        value.copy< expr_world::ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using: // using
        value.copy< include::ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< program::ptr > (that.value);
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASHSTR: // "hash string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.copy< stmt::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.copy< stmt_break::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.copy< stmt_case::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        value.copy< stmt_comp::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.copy< stmt_continue::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.copy< stmt_default::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.copy< stmt_dev::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.copy< stmt_dowhile::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.copy< stmt_endon::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_const: // stmt_const
      case symbol_kind::S_stmt_assign: // stmt_assign
        value.copy< stmt_expr::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.copy< stmt_for::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.copy< stmt_foreach::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.copy< stmt_if::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.copy< stmt_ifelse::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        value.copy< stmt_list::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.copy< stmt_notify::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.copy< stmt_prof_begin::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.copy< stmt_prof_end::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.copy< stmt_return::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.copy< stmt_switch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.copy< stmt_wait::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waitrealtime: // stmt_waitrealtime
        value.copy< stmt_waitrealtime::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.copy< stmt_waittill::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.copy< stmt_waittillframeend::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.copy< stmt_waittillmatch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.copy< stmt_while::ptr > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser2::stack_symbol_type&
  parser2::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_pointer: // expr_pointer
      case symbol_kind::S_expr_member: // expr_member
        value.move< call::ptr > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl::ptr > (that.value);
        break;

      case symbol_kind::S_decl_class: // decl_class
        value.move< decl_class::ptr > (that.value);
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.move< decl_function::ptr > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< decl_list::ptr > (that.value);
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        value.move< decl_namespace::ptr > (that.value);
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.move< decl_usingtree::ptr > (that.value);
        break;

      case symbol_kind::S_decl_variable: // decl_variable
        value.move< decl_variable::ptr > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_object: // expr_object
        value.move< expr::ptr > (that.value);
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        value.move< expr_abs::ptr > (that.value);
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        value.move< expr_angleclamp180::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        value.move< expr_anglestoforward::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        value.move< expr_anglestoright::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        value.move< expr_anglestoup::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.move< expr_anim::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.move< expr_animation::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.move< expr_animtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.move< expr_arguments::ptr > (that.value);
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.move< expr_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.move< expr_call::ptr > (that.value);
        break;

      case symbol_kind::S_expr_classes: // expr_classes
        value.move< expr_classes::ptr > (that.value);
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.move< expr_complement::ptr > (that.value);
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.move< expr_empty_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.move< expr_false::ptr > (that.value);
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.move< expr_field::ptr > (that.value);
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.move< expr_float::ptr > (that.value);
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.move< expr_game::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        value.move< expr_getdvar::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        value.move< expr_getdvarcoloralpha::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        value.move< expr_getdvarcolorblue::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        value.move< expr_getdvarcolorgreen::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        value.move< expr_getdvarcolorred::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        value.move< expr_getdvarfloat::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        value.move< expr_getdvarint::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        value.move< expr_getdvarvector::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        value.move< expr_getfirstarraykey::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        value.move< expr_getnextarraykey::ptr > (that.value);
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        value.move< expr_gettime::ptr > (that.value);
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        value.move< expr_hash::ptr > (that.value);
        break;

      case symbol_kind::S_opt_class_base: // opt_class_base
      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.move< expr_identifier::ptr > (that.value);
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.move< expr_integer::ptr > (that.value);
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.move< expr_isdefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.move< expr_istring::ptr > (that.value);
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.move< expr_level::ptr > (that.value);
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.move< expr_method::ptr > (that.value);
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.move< expr_negate::ptr > (that.value);
        break;

      case symbol_kind::S_expr_new: // expr_new
        value.move< expr_new::ptr > (that.value);
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.move< expr_not::ptr > (that.value);
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.move< expr_parameters::ptr > (that.value);
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.move< expr_paren::ptr > (that.value);
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.move< expr_path::ptr > (that.value);
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.move< expr_reference::ptr > (that.value);
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.move< expr_self::ptr > (that.value);
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.move< expr_size::ptr > (that.value);
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.move< expr_string::ptr > (that.value);
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.move< expr_true::ptr > (that.value);
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.move< expr_undefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.move< expr_vector::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        value.move< expr_vectorscale::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        value.move< expr_vectortoangles::ptr > (that.value);
        break;

      case symbol_kind::S_expr_world: // expr_world
        value.move< expr_world::ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using: // using
        value.move< include::ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< program::ptr > (that.value);
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASHSTR: // "hash string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.move< stmt::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< stmt_break::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< stmt_case::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        value.move< stmt_comp::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< stmt_continue::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< stmt_default::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.move< stmt_dev::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.move< stmt_dowhile::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< stmt_endon::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_const: // stmt_const
      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_expr::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< stmt_for::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< stmt_foreach::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< stmt_if::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< stmt_ifelse::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        value.move< stmt_list::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< stmt_notify::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.move< stmt_prof_begin::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.move< stmt_prof_end::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< stmt_return::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< stmt_switch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< stmt_wait::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waitrealtime: // stmt_waitrealtime
        value.move< stmt_waitrealtime::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< stmt_waittill::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< stmt_waittillframeend::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< stmt_waittillmatch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< stmt_while::ptr > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser2::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if ARC2DEBUG
  template <typename Base>
  void
  parser2::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser2::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser2::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser2::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if ARC2DEBUG
  std::ostream&
  parser2::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser2::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser2::debug_level_type
  parser2::debug_level () const
  {
    return yydebug_;
  }

  void
  parser2::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // ARC2DEBUG

  parser2::state_type
  parser2::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser2::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser2::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser2::operator() ()
  {
    return parse ();
  }

  int
  parser2::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // Discard the LAC context in case there still is one left from a
    // previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (ctx_, ppr));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_pointer: // expr_pointer
      case symbol_kind::S_expr_member: // expr_member
        yylhs.value.emplace< call::ptr > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< decl::ptr > ();
        break;

      case symbol_kind::S_decl_class: // decl_class
        yylhs.value.emplace< decl_class::ptr > ();
        break;

      case symbol_kind::S_decl_function: // decl_function
        yylhs.value.emplace< decl_function::ptr > ();
        break;

      case symbol_kind::S_decl_list: // decl_list
        yylhs.value.emplace< decl_list::ptr > ();
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        yylhs.value.emplace< decl_namespace::ptr > ();
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        yylhs.value.emplace< decl_usingtree::ptr > ();
        break;

      case symbol_kind::S_decl_variable: // decl_variable
        yylhs.value.emplace< decl_variable::ptr > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_object: // expr_object
        yylhs.value.emplace< expr::ptr > ();
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        yylhs.value.emplace< expr_abs::ptr > ();
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        yylhs.value.emplace< expr_angleclamp180::ptr > ();
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        yylhs.value.emplace< expr_anglestoforward::ptr > ();
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        yylhs.value.emplace< expr_anglestoright::ptr > ();
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        yylhs.value.emplace< expr_anglestoup::ptr > ();
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        yylhs.value.emplace< expr_anim::ptr > ();
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        yylhs.value.emplace< expr_animation::ptr > ();
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        yylhs.value.emplace< expr_animtree::ptr > ();
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        yylhs.value.emplace< expr_arguments::ptr > ();
        break;

      case symbol_kind::S_expr_array: // expr_array
        yylhs.value.emplace< expr_array::ptr > ();
        break;

      case symbol_kind::S_expr_call: // expr_call
        yylhs.value.emplace< expr_call::ptr > ();
        break;

      case symbol_kind::S_expr_classes: // expr_classes
        yylhs.value.emplace< expr_classes::ptr > ();
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        yylhs.value.emplace< expr_complement::ptr > ();
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        yylhs.value.emplace< expr_empty_array::ptr > ();
        break;

      case symbol_kind::S_expr_false: // expr_false
        yylhs.value.emplace< expr_false::ptr > ();
        break;

      case symbol_kind::S_expr_field: // expr_field
        yylhs.value.emplace< expr_field::ptr > ();
        break;

      case symbol_kind::S_expr_float: // expr_float
        yylhs.value.emplace< expr_float::ptr > ();
        break;

      case symbol_kind::S_expr_game: // expr_game
        yylhs.value.emplace< expr_game::ptr > ();
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        yylhs.value.emplace< expr_getdvar::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        yylhs.value.emplace< expr_getdvarcoloralpha::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        yylhs.value.emplace< expr_getdvarcolorblue::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        yylhs.value.emplace< expr_getdvarcolorgreen::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        yylhs.value.emplace< expr_getdvarcolorred::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        yylhs.value.emplace< expr_getdvarfloat::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        yylhs.value.emplace< expr_getdvarint::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        yylhs.value.emplace< expr_getdvarvector::ptr > ();
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        yylhs.value.emplace< expr_getfirstarraykey::ptr > ();
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        yylhs.value.emplace< expr_getnextarraykey::ptr > ();
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        yylhs.value.emplace< expr_gettime::ptr > ();
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        yylhs.value.emplace< expr_hash::ptr > ();
        break;

      case symbol_kind::S_opt_class_base: // opt_class_base
      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        yylhs.value.emplace< expr_identifier::ptr > ();
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        yylhs.value.emplace< expr_integer::ptr > ();
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        yylhs.value.emplace< expr_isdefined::ptr > ();
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        yylhs.value.emplace< expr_istring::ptr > ();
        break;

      case symbol_kind::S_expr_level: // expr_level
        yylhs.value.emplace< expr_level::ptr > ();
        break;

      case symbol_kind::S_expr_method: // expr_method
        yylhs.value.emplace< expr_method::ptr > ();
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        yylhs.value.emplace< expr_negate::ptr > ();
        break;

      case symbol_kind::S_expr_new: // expr_new
        yylhs.value.emplace< expr_new::ptr > ();
        break;

      case symbol_kind::S_expr_not: // expr_not
        yylhs.value.emplace< expr_not::ptr > ();
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        yylhs.value.emplace< expr_parameters::ptr > ();
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        yylhs.value.emplace< expr_paren::ptr > ();
        break;

      case symbol_kind::S_expr_path: // expr_path
        yylhs.value.emplace< expr_path::ptr > ();
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        yylhs.value.emplace< expr_reference::ptr > ();
        break;

      case symbol_kind::S_expr_self: // expr_self
        yylhs.value.emplace< expr_self::ptr > ();
        break;

      case symbol_kind::S_expr_size: // expr_size
        yylhs.value.emplace< expr_size::ptr > ();
        break;

      case symbol_kind::S_expr_string: // expr_string
        yylhs.value.emplace< expr_string::ptr > ();
        break;

      case symbol_kind::S_expr_true: // expr_true
        yylhs.value.emplace< expr_true::ptr > ();
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        yylhs.value.emplace< expr_undefined::ptr > ();
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        yylhs.value.emplace< expr_vector::ptr > ();
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        yylhs.value.emplace< expr_vectorscale::ptr > ();
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        yylhs.value.emplace< expr_vectortoangles::ptr > ();
        break;

      case symbol_kind::S_expr_world: // expr_world
        yylhs.value.emplace< expr_world::ptr > ();
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using: // using
        yylhs.value.emplace< include::ptr > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< program::ptr > ();
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASHSTR: // "hash string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        yylhs.value.emplace< stmt::ptr > ();
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        yylhs.value.emplace< stmt_break::ptr > ();
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        yylhs.value.emplace< stmt_case::ptr > ();
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        yylhs.value.emplace< stmt_comp::ptr > ();
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        yylhs.value.emplace< stmt_continue::ptr > ();
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        yylhs.value.emplace< stmt_default::ptr > ();
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        yylhs.value.emplace< stmt_dev::ptr > ();
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        yylhs.value.emplace< stmt_dowhile::ptr > ();
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        yylhs.value.emplace< stmt_endon::ptr > ();
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_const: // stmt_const
      case symbol_kind::S_stmt_assign: // stmt_assign
        yylhs.value.emplace< stmt_expr::ptr > ();
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        yylhs.value.emplace< stmt_for::ptr > ();
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        yylhs.value.emplace< stmt_foreach::ptr > ();
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        yylhs.value.emplace< stmt_if::ptr > ();
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        yylhs.value.emplace< stmt_ifelse::ptr > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        yylhs.value.emplace< stmt_list::ptr > ();
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        yylhs.value.emplace< stmt_notify::ptr > ();
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        yylhs.value.emplace< stmt_prof_begin::ptr > ();
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        yylhs.value.emplace< stmt_prof_end::ptr > ();
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        yylhs.value.emplace< stmt_return::ptr > ();
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        yylhs.value.emplace< stmt_switch::ptr > ();
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        yylhs.value.emplace< stmt_wait::ptr > ();
        break;

      case symbol_kind::S_stmt_waitrealtime: // stmt_waitrealtime
        yylhs.value.emplace< stmt_waitrealtime::ptr > ();
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        yylhs.value.emplace< stmt_waittill::ptr > ();
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        yylhs.value.emplace< stmt_waittillframeend::ptr > ();
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        yylhs.value.emplace< stmt_waittillmatch::ptr > ();
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        yylhs.value.emplace< stmt_while::ptr > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // main: program
#line 324 "parser2.ypp"
              { ast = std::move(yystack_[0].value.as < program::ptr > ()); }
#line 2491 "parser2.cpp"
    break;

  case 3: // main: %empty
#line 325 "parser2.ypp"
              { ast = program::make(yylhs.location); }
#line 2497 "parser2.cpp"
    break;

  case 4: // program: program ";"
#line 330 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2503 "parser2.cpp"
    break;

  case 5: // program: program inline
#line 332 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2509 "parser2.cpp"
    break;

  case 6: // program: program insert
#line 334 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2515 "parser2.cpp"
    break;

  case 7: // program: program include
#line 336 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2521 "parser2.cpp"
    break;

  case 8: // program: program using
#line 338 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2527 "parser2.cpp"
    break;

  case 9: // program: program declaration
#line 340 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2533 "parser2.cpp"
    break;

  case 10: // program: ";"
#line 342 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2539 "parser2.cpp"
    break;

  case 11: // program: inline
#line 344 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2545 "parser2.cpp"
    break;

  case 12: // program: insert
#line 346 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2551 "parser2.cpp"
    break;

  case 13: // program: include
#line 348 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2557 "parser2.cpp"
    break;

  case 14: // program: using
#line 350 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2563 "parser2.cpp"
    break;

  case 15: // program: declaration
#line 352 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2569 "parser2.cpp"
    break;

  case 16: // inline: "#inline" expr_path ";"
#line 356 "parser2.ypp"
                                 { ppr.push_header(yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2575 "parser2.cpp"
    break;

  case 17: // insert: "#insert" expr_path ";"
#line 360 "parser2.ypp"
                                 { ppr.push_header(yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2581 "parser2.cpp"
    break;

  case 18: // include: "#include" expr_path ";"
#line 365 "parser2.ypp"
        { yylhs.value.as < include::ptr > () = include::make(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2587 "parser2.cpp"
    break;

  case 19: // using: "#using" expr_path ";"
#line 370 "parser2.ypp"
        { yylhs.value.as < include::ptr > () = include::make(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2593 "parser2.cpp"
    break;

  case 20: // declaration: "/#"
#line 374 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_begin::make(yylhs.location); }
#line 2599 "parser2.cpp"
    break;

  case 21: // declaration: "#/"
#line 375 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_end::make(yylhs.location); }
#line 2605 "parser2.cpp"
    break;

  case 22: // declaration: decl_namespace
#line 376 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_namespace::ptr > ()); }
#line 2611 "parser2.cpp"
    break;

  case 23: // declaration: decl_usingtree
#line 377 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_usingtree::ptr > ()); }
#line 2617 "parser2.cpp"
    break;

  case 24: // declaration: decl_function
#line 378 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_function::ptr > ()); }
#line 2623 "parser2.cpp"
    break;

  case 25: // declaration: decl_class
#line 379 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_class::ptr > ()); }
#line 2629 "parser2.cpp"
    break;

  case 26: // decl_namespace: "#namespace" expr_identifier ";"
#line 384 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_namespace::ptr > () = decl_namespace::make(yylhs.location, std::move(yystack_[1].value.as < expr_identifier::ptr > ())); }
#line 2635 "parser2.cpp"
    break;

  case 27: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 389 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_usingtree::ptr > () = decl_usingtree::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 2641 "parser2.cpp"
    break;

  case 28: // decl_function: "function" expr_identifier "(" expr_parameters ")" stmt_comp
#line 394 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_none); }
#line 2647 "parser2.cpp"
    break;

  case 29: // decl_function: "function" "autoexec" expr_identifier "(" expr_parameters ")" stmt_comp
#line 396 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_autoexec); }
#line 2653 "parser2.cpp"
    break;

  case 30: // decl_function: "function" "codecall" expr_identifier "(" expr_parameters ")" stmt_comp
#line 398 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_codecall); }
#line 2659 "parser2.cpp"
    break;

  case 31: // decl_function: "function" "private" expr_identifier "(" expr_parameters ")" stmt_comp
#line 400 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_private); }
#line 2665 "parser2.cpp"
    break;

  case 32: // decl_variable: "var" expr_identifier ";"
#line 405 "parser2.ypp"
        { yylhs.value.as < decl_variable::ptr > () = decl_variable::make(yylhs.location, std::move(yystack_[1].value.as < expr_identifier::ptr > ())); }
#line 2671 "parser2.cpp"
    break;

  case 33: // decl_class: "class" expr_identifier opt_class_base "{" decl_list "}"
#line 410 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_class::ptr > () = decl_class::make(yylhs.location, std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < decl_list::ptr > ())); }
#line 2677 "parser2.cpp"
    break;

  case 34: // decl_list: decl_list "constructor" "(" ")" stmt_comp
#line 415 "parser2.ypp"
        { yylhs.value.as < decl_list::ptr > () = std::move(yystack_[4].value.as < decl_list::ptr > ()); yylhs.value.as < decl_list::ptr > ()->list.push_back(decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), expr_identifier::make(yylhs.location, "constructor"), expr_parameters::make(yylhs.location), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_none)); }
#line 2683 "parser2.cpp"
    break;

  case 35: // decl_list: decl_list "destructor" "(" ")" stmt_comp
#line 417 "parser2.ypp"
        { yylhs.value.as < decl_list::ptr > () = std::move(yystack_[4].value.as < decl_list::ptr > ()); yylhs.value.as < decl_list::ptr > ()->list.push_back(decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), expr_identifier::make(yylhs.location, "destructor"), expr_parameters::make(yylhs.location), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_none)); }
#line 2689 "parser2.cpp"
    break;

  case 36: // decl_list: decl_list decl_function
#line 419 "parser2.ypp"
        { yylhs.value.as < decl_list::ptr > () = std::move(yystack_[1].value.as < decl_list::ptr > ()); yylhs.value.as < decl_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < decl_function::ptr > ())); }
#line 2695 "parser2.cpp"
    break;

  case 37: // decl_list: decl_list decl_variable
#line 421 "parser2.ypp"
        { yylhs.value.as < decl_list::ptr > () = std::move(yystack_[1].value.as < decl_list::ptr > ()); yylhs.value.as < decl_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < decl_variable::ptr > ())); }
#line 2701 "parser2.cpp"
    break;

  case 38: // decl_list: %empty
#line 423 "parser2.ypp"
        { yylhs.value.as < decl_list::ptr > () = decl_list::make(yylhs.location); }
#line 2707 "parser2.cpp"
    break;

  case 39: // opt_class_base: ":" expr_identifier
#line 428 "parser2.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 2713 "parser2.cpp"
    break;

  case 40: // opt_class_base: %empty
#line 430 "parser2.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, ""); }
#line 2719 "parser2.cpp"
    break;

  case 41: // stmt: stmt_comp
#line 434 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_comp::ptr > ()); }
#line 2725 "parser2.cpp"
    break;

  case 42: // stmt: stmt_call
#line 435 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2731 "parser2.cpp"
    break;

  case 43: // stmt: stmt_const
#line 436 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2737 "parser2.cpp"
    break;

  case 44: // stmt: stmt_assign
#line 437 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2743 "parser2.cpp"
    break;

  case 45: // stmt: stmt_endon
#line 438 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_endon::ptr > ()); }
#line 2749 "parser2.cpp"
    break;

  case 46: // stmt: stmt_notify
#line 439 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_notify::ptr > ()); }
#line 2755 "parser2.cpp"
    break;

  case 47: // stmt: stmt_wait
#line 440 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_wait::ptr > ()); }
#line 2761 "parser2.cpp"
    break;

  case 48: // stmt: stmt_waitrealtime
#line 441 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waitrealtime::ptr > ()); }
#line 2767 "parser2.cpp"
    break;

  case 49: // stmt: stmt_waittill
#line 442 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittill::ptr > ()); }
#line 2773 "parser2.cpp"
    break;

  case 50: // stmt: stmt_waittillmatch
#line 443 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillmatch::ptr > ()); }
#line 2779 "parser2.cpp"
    break;

  case 51: // stmt: stmt_waittillframeend
#line 444 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillframeend::ptr > ()); }
#line 2785 "parser2.cpp"
    break;

  case 52: // stmt: stmt_if
#line 445 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_if::ptr > ()); }
#line 2791 "parser2.cpp"
    break;

  case 53: // stmt: stmt_ifelse
#line 446 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_ifelse::ptr > ()); }
#line 2797 "parser2.cpp"
    break;

  case 54: // stmt: stmt_while
#line 447 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_while::ptr > ()); }
#line 2803 "parser2.cpp"
    break;

  case 55: // stmt: stmt_dowhile
#line 448 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dowhile::ptr > ()); }
#line 2809 "parser2.cpp"
    break;

  case 56: // stmt: stmt_for
#line 449 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_for::ptr > ()); }
#line 2815 "parser2.cpp"
    break;

  case 57: // stmt: stmt_foreach
#line 450 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_foreach::ptr > ()); }
#line 2821 "parser2.cpp"
    break;

  case 58: // stmt: stmt_switch
#line 451 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_switch::ptr > ()); }
#line 2827 "parser2.cpp"
    break;

  case 59: // stmt: stmt_case
#line 452 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_case::ptr > ()); }
#line 2833 "parser2.cpp"
    break;

  case 60: // stmt: stmt_default
#line 453 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_default::ptr > ()); }
#line 2839 "parser2.cpp"
    break;

  case 61: // stmt: stmt_break
#line 454 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_break::ptr > ()); }
#line 2845 "parser2.cpp"
    break;

  case 62: // stmt: stmt_continue
#line 455 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_continue::ptr > ()); }
#line 2851 "parser2.cpp"
    break;

  case 63: // stmt: stmt_return
#line 456 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_return::ptr > ()); }
#line 2857 "parser2.cpp"
    break;

  case 64: // stmt: stmt_prof_begin
#line 457 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_begin::ptr > ()); }
#line 2863 "parser2.cpp"
    break;

  case 65: // stmt: stmt_prof_end
#line 458 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_end::ptr > ()); }
#line 2869 "parser2.cpp"
    break;

  case 66: // stmt_or_dev: stmt
#line 462 "parser2.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt::ptr > ()); }
#line 2875 "parser2.cpp"
    break;

  case 67: // stmt_or_dev: stmt_dev
#line 463 "parser2.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dev::ptr > ()); }
#line 2881 "parser2.cpp"
    break;

  case 68: // stmt_list: stmt_list stmt
#line 468 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2887 "parser2.cpp"
    break;

  case 69: // stmt_list: stmt
#line 470 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2893 "parser2.cpp"
    break;

  case 70: // stmt_list: stmt_list ";"
#line 472 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2899 "parser2.cpp"
    break;

  case 71: // stmt_list: ";"
#line 474 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2905 "parser2.cpp"
    break;

  case 72: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 479 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2911 "parser2.cpp"
    break;

  case 73: // stmt_or_dev_list: stmt_or_dev
#line 481 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2917 "parser2.cpp"
    break;

  case 74: // stmt_or_dev_list: stmt_or_dev_list ";"
#line 483 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2923 "parser2.cpp"
    break;

  case 75: // stmt_or_dev_list: ";"
#line 485 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2929 "parser2.cpp"
    break;

  case 76: // stmt_dev: "/#" stmt_list "#/"
#line 489 "parser2.ypp"
                                { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2935 "parser2.cpp"
    break;

  case 77: // stmt_dev: "/#" "#/"
#line 490 "parser2.ypp"
                      { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2941 "parser2.cpp"
    break;

  case 78: // stmt_comp: "{" stmt_or_dev_list "}"
#line 494 "parser2.ypp"
                                     { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2947 "parser2.cpp"
    break;

  case 79: // stmt_comp: "{" "}"
#line 495 "parser2.ypp"
                    { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2953 "parser2.cpp"
    break;

  case 80: // stmt_expr: expr_assign
#line 500 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2959 "parser2.cpp"
    break;

  case 81: // stmt_expr: expr_increment
#line 502 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2965 "parser2.cpp"
    break;

  case 82: // stmt_expr: expr_decrement
#line 504 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2971 "parser2.cpp"
    break;

  case 83: // stmt_expr: %empty
#line 506 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 2977 "parser2.cpp"
    break;

  case 84: // stmt_call: expr_call ";"
#line 511 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_call::ptr > ())); }
#line 2983 "parser2.cpp"
    break;

  case 85: // stmt_call: expr_method ";"
#line 513 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_method::ptr > ())); }
#line 2989 "parser2.cpp"
    break;

  case 86: // stmt_const: "const" expr_identifier "=" expr ";"
#line 518 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, expr_const::make(yylhs.location, std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ()))); }
#line 2995 "parser2.cpp"
    break;

  case 87: // stmt_assign: expr_assign ";"
#line 523 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3001 "parser2.cpp"
    break;

  case 88: // stmt_assign: expr_increment ";"
#line 525 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3007 "parser2.cpp"
    break;

  case 89: // stmt_assign: expr_decrement ";"
#line 527 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3013 "parser2.cpp"
    break;

  case 90: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 532 "parser2.ypp"
        { yylhs.value.as < stmt_endon::ptr > () = stmt_endon::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 3019 "parser2.cpp"
    break;

  case 91: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 537 "parser2.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 3025 "parser2.cpp"
    break;

  case 92: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 539 "parser2.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 3031 "parser2.cpp"
    break;

  case 93: // stmt_wait: "wait" expr ";"
#line 544 "parser2.ypp"
        { yylhs.value.as < stmt_wait::ptr > () = stmt_wait::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3037 "parser2.cpp"
    break;

  case 94: // stmt_waitrealtime: "waitrealtime" expr ";"
#line 549 "parser2.ypp"
        { yylhs.value.as < stmt_waitrealtime::ptr > () = stmt_waitrealtime::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3043 "parser2.cpp"
    break;

  case 95: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 554 "parser2.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 3049 "parser2.cpp"
    break;

  case 96: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 556 "parser2.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 3055 "parser2.cpp"
    break;

  case 97: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 561 "parser2.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 3061 "parser2.cpp"
    break;

  case 98: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 563 "parser2.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 3067 "parser2.cpp"
    break;

  case 99: // stmt_waittillframeend: "waittillframeend" ";"
#line 568 "parser2.ypp"
        { yylhs.value.as < stmt_waittillframeend::ptr > () = stmt_waittillframeend::make(yylhs.location); }
#line 3073 "parser2.cpp"
    break;

  case 100: // stmt_if: "if" "(" expr ")" stmt
#line 573 "parser2.ypp"
        { yylhs.value.as < stmt_if::ptr > () = stmt_if::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 3079 "parser2.cpp"
    break;

  case 101: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 578 "parser2.ypp"
        { yylhs.value.as < stmt_ifelse::ptr > () = stmt_ifelse::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 3085 "parser2.cpp"
    break;

  case 102: // stmt_while: "while" "(" expr ")" stmt
#line 583 "parser2.ypp"
        { yylhs.value.as < stmt_while::ptr > () = stmt_while::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 3091 "parser2.cpp"
    break;

  case 103: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 588 "parser2.ypp"
        { yylhs.value.as < stmt_dowhile::ptr > () = stmt_dowhile::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[5].value.as < stmt::ptr > ())); }
#line 3097 "parser2.cpp"
    break;

  case 104: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 593 "parser2.ypp"
        { yylhs.value.as < stmt_for::ptr > () = stmt_for::make(yylhs.location, std::move(yystack_[6].value.as < stmt_expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt_expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 3103 "parser2.cpp"
    break;

  case 105: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 598 "parser2.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, std::format("_a{}", ++index));
            auto key = expr_identifier::make(yylhs.location, std::format("_k{}", ++index));
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt::ptr > ()), false);
        }
#line 3113 "parser2.cpp"
    break;

  case 106: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 604 "parser2.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, std::format("_a{}", ++index));
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(array), std::move(yystack_[6].value.as < expr_identifier::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ()), true);
        }
#line 3122 "parser2.cpp"
    break;

  case 107: // stmt_switch: "switch" "(" expr ")" stmt_comp
#line 612 "parser2.ypp"
        { yylhs.value.as < stmt_switch::ptr > () = stmt_switch::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); 
          parse_switch2(*yylhs.value.as < stmt_switch::ptr > ());
        }
#line 3130 "parser2.cpp"
    break;

  case 108: // stmt_case: "case" expr_integer ":"
#line 619 "parser2.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_integer::ptr > ()), stmt_list::make(yylhs.location)); }
#line 3136 "parser2.cpp"
    break;

  case 109: // stmt_case: "case" expr_string ":"
#line 621 "parser2.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_string::ptr > ()), stmt_list::make(yylhs.location)); }
#line 3142 "parser2.cpp"
    break;

  case 110: // stmt_default: "default" ":"
#line 626 "parser2.ypp"
        { yylhs.value.as < stmt_default::ptr > () = stmt_default::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 3148 "parser2.cpp"
    break;

  case 111: // stmt_break: "break" ";"
#line 631 "parser2.ypp"
        { yylhs.value.as < stmt_break::ptr > () = stmt_break::make(yylhs.location); }
#line 3154 "parser2.cpp"
    break;

  case 112: // stmt_continue: "continue" ";"
#line 636 "parser2.ypp"
        { yylhs.value.as < stmt_continue::ptr > () = stmt_continue::make(yylhs.location); }
#line 3160 "parser2.cpp"
    break;

  case 113: // stmt_return: "return" expr ";"
#line 641 "parser2.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3166 "parser2.cpp"
    break;

  case 114: // stmt_return: "return" ";"
#line 643 "parser2.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 3172 "parser2.cpp"
    break;

  case 115: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 648 "parser2.ypp"
        { yylhs.value.as < stmt_prof_begin::ptr > () = stmt_prof_begin::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 3178 "parser2.cpp"
    break;

  case 116: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 653 "parser2.ypp"
        { yylhs.value.as < stmt_prof_end::ptr > () = stmt_prof_end::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 3184 "parser2.cpp"
    break;

  case 117: // expr: expr_ternary
#line 657 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 3190 "parser2.cpp"
    break;

  case 118: // expr: expr_binary
#line 658 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 3196 "parser2.cpp"
    break;

  case 119: // expr: expr_primitive
#line 659 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 3202 "parser2.cpp"
    break;

  case 120: // expr_or_empty: expr
#line 663 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 3208 "parser2.cpp"
    break;

  case 121: // expr_or_empty: %empty
#line 664 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = expr_empty::make(yylhs.location); }
#line 3214 "parser2.cpp"
    break;

  case 122: // expr_increment: "++" expr_object
#line 669 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 3220 "parser2.cpp"
    break;

  case 123: // expr_increment: expr_object "++"
#line 671 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 3226 "parser2.cpp"
    break;

  case 124: // expr_decrement: "--" expr_object
#line 676 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 3232 "parser2.cpp"
    break;

  case 125: // expr_decrement: expr_object "--"
#line 678 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 3238 "parser2.cpp"
    break;

  case 126: // expr_assign: expr_object "=" expr
#line 683 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 3244 "parser2.cpp"
    break;

  case 127: // expr_assign: expr_object "|=" expr
#line 685 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwor); }
#line 3250 "parser2.cpp"
    break;

  case 128: // expr_assign: expr_object "&=" expr
#line 687 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwand); }
#line 3256 "parser2.cpp"
    break;

  case 129: // expr_assign: expr_object "^=" expr
#line 689 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwexor); }
#line 3262 "parser2.cpp"
    break;

  case 130: // expr_assign: expr_object "<<=" expr
#line 691 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shl); }
#line 3268 "parser2.cpp"
    break;

  case 131: // expr_assign: expr_object ">>=" expr
#line 693 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shr); }
#line 3274 "parser2.cpp"
    break;

  case 132: // expr_assign: expr_object "+=" expr
#line 695 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::add); }
#line 3280 "parser2.cpp"
    break;

  case 133: // expr_assign: expr_object "-=" expr
#line 697 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::sub); }
#line 3286 "parser2.cpp"
    break;

  case 134: // expr_assign: expr_object "*=" expr
#line 699 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mul); }
#line 3292 "parser2.cpp"
    break;

  case 135: // expr_assign: expr_object "/=" expr
#line 701 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::div); }
#line 3298 "parser2.cpp"
    break;

  case 136: // expr_assign: expr_object "%=" expr
#line 703 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mod); }
#line 3304 "parser2.cpp"
    break;

  case 137: // expr_ternary: expr "?" expr ":" expr
#line 708 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_ternary::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3310 "parser2.cpp"
    break;

  case 138: // expr_binary: expr "||" expr
#line 713 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_or); }
#line 3316 "parser2.cpp"
    break;

  case 139: // expr_binary: expr "&&" expr
#line 715 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_and); }
#line 3322 "parser2.cpp"
    break;

  case 140: // expr_binary: expr "===" expr
#line 717 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::seq); }
#line 3328 "parser2.cpp"
    break;

  case 141: // expr_binary: expr "!==" expr
#line 719 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::sne); }
#line 3334 "parser2.cpp"
    break;

  case 142: // expr_binary: expr "==" expr
#line 721 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::eq); }
#line 3340 "parser2.cpp"
    break;

  case 143: // expr_binary: expr "!=" expr
#line 723 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ne); }
#line 3346 "parser2.cpp"
    break;

  case 144: // expr_binary: expr "<=" expr
#line 725 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::le); }
#line 3352 "parser2.cpp"
    break;

  case 145: // expr_binary: expr ">=" expr
#line 727 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ge); }
#line 3358 "parser2.cpp"
    break;

  case 146: // expr_binary: expr "<" expr
#line 729 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::lt); }
#line 3364 "parser2.cpp"
    break;

  case 147: // expr_binary: expr ">" expr
#line 731 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::gt); }
#line 3370 "parser2.cpp"
    break;

  case 148: // expr_binary: expr "|" expr
#line 733 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwor); }
#line 3376 "parser2.cpp"
    break;

  case 149: // expr_binary: expr "&" expr
#line 735 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwand); }
#line 3382 "parser2.cpp"
    break;

  case 150: // expr_binary: expr "^" expr
#line 737 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwexor); }
#line 3388 "parser2.cpp"
    break;

  case 151: // expr_binary: expr "<<" expr
#line 739 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shl); }
#line 3394 "parser2.cpp"
    break;

  case 152: // expr_binary: expr ">>" expr
#line 741 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shr); }
#line 3400 "parser2.cpp"
    break;

  case 153: // expr_binary: expr "+" expr
#line 743 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::add); }
#line 3406 "parser2.cpp"
    break;

  case 154: // expr_binary: expr "-" expr
#line 745 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::sub); }
#line 3412 "parser2.cpp"
    break;

  case 155: // expr_binary: expr "*" expr
#line 747 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mul); }
#line 3418 "parser2.cpp"
    break;

  case 156: // expr_binary: expr "/" expr
#line 749 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::div); }
#line 3424 "parser2.cpp"
    break;

  case 157: // expr_binary: expr "%" expr
#line 751 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mod); }
#line 3430 "parser2.cpp"
    break;

  case 158: // expr_primitive: expr_complement
#line 755 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_complement::ptr > ()); }
#line 3436 "parser2.cpp"
    break;

  case 159: // expr_primitive: expr_negate
#line 756 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_negate::ptr > ()); }
#line 3442 "parser2.cpp"
    break;

  case 160: // expr_primitive: expr_not
#line 757 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_not::ptr > ()); }
#line 3448 "parser2.cpp"
    break;

  case 161: // expr_primitive: expr_new
#line 758 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_new::ptr > ()); }
#line 3454 "parser2.cpp"
    break;

  case 162: // expr_primitive: expr_call
#line 759 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3460 "parser2.cpp"
    break;

  case 163: // expr_primitive: expr_method
#line 760 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3466 "parser2.cpp"
    break;

  case 164: // expr_primitive: expr_getnextarraykey
#line 761 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getnextarraykey::ptr > ()); }
#line 3472 "parser2.cpp"
    break;

  case 165: // expr_primitive: expr_getfirstarraykey
#line 762 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getfirstarraykey::ptr > ()); }
#line 3478 "parser2.cpp"
    break;

  case 166: // expr_primitive: expr_getdvarcoloralpha
#line 763 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcoloralpha::ptr > ()); }
#line 3484 "parser2.cpp"
    break;

  case 167: // expr_primitive: expr_getdvarcolorblue
#line 764 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorblue::ptr > ()); }
#line 3490 "parser2.cpp"
    break;

  case 168: // expr_primitive: expr_getdvarcolorgreen
#line 765 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorgreen::ptr > ()); }
#line 3496 "parser2.cpp"
    break;

  case 169: // expr_primitive: expr_getdvarcolorred
#line 766 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorred::ptr > ()); }
#line 3502 "parser2.cpp"
    break;

  case 170: // expr_primitive: expr_getdvarvector
#line 767 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarvector::ptr > ()); }
#line 3508 "parser2.cpp"
    break;

  case 171: // expr_primitive: expr_getdvarfloat
#line 768 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarfloat::ptr > ()); }
#line 3514 "parser2.cpp"
    break;

  case 172: // expr_primitive: expr_getdvarint
#line 769 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarint::ptr > ()); }
#line 3520 "parser2.cpp"
    break;

  case 173: // expr_primitive: expr_getdvar
#line 770 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvar::ptr > ()); }
#line 3526 "parser2.cpp"
    break;

  case 174: // expr_primitive: expr_gettime
#line 771 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_gettime::ptr > ()); }
#line 3532 "parser2.cpp"
    break;

  case 175: // expr_primitive: expr_abs
#line 772 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_abs::ptr > ()); }
#line 3538 "parser2.cpp"
    break;

  case 176: // expr_primitive: expr_vectortoangles
#line 773 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vectortoangles::ptr > ()); }
#line 3544 "parser2.cpp"
    break;

  case 177: // expr_primitive: expr_angleclamp180
#line 774 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_angleclamp180::ptr > ()); }
#line 3550 "parser2.cpp"
    break;

  case 178: // expr_primitive: expr_anglestoforward
#line 775 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoforward::ptr > ()); }
#line 3556 "parser2.cpp"
    break;

  case 179: // expr_primitive: expr_anglestoright
#line 776 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoright::ptr > ()); }
#line 3562 "parser2.cpp"
    break;

  case 180: // expr_primitive: expr_anglestoup
#line 777 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoup::ptr > ()); }
#line 3568 "parser2.cpp"
    break;

  case 181: // expr_primitive: expr_vectorscale
#line 778 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vectorscale::ptr > ()); }
#line 3574 "parser2.cpp"
    break;

  case 182: // expr_primitive: expr_isdefined
#line 779 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_isdefined::ptr > ()); }
#line 3580 "parser2.cpp"
    break;

  case 183: // expr_primitive: expr_reference
#line 780 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_reference::ptr > ()); }
#line 3586 "parser2.cpp"
    break;

  case 184: // expr_primitive: expr_array
#line 781 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3592 "parser2.cpp"
    break;

  case 185: // expr_primitive: expr_field
#line 782 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3598 "parser2.cpp"
    break;

  case 186: // expr_primitive: expr_size
#line 783 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_size::ptr > ()); }
#line 3604 "parser2.cpp"
    break;

  case 187: // expr_primitive: expr_paren
#line 784 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_paren::ptr > ()); }
#line 3610 "parser2.cpp"
    break;

  case 188: // expr_primitive: expr_empty_array
#line 785 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_empty_array::ptr > ()); }
#line 3616 "parser2.cpp"
    break;

  case 189: // expr_primitive: expr_undefined
#line 786 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_undefined::ptr > ()); }
#line 3622 "parser2.cpp"
    break;

  case 190: // expr_primitive: expr_game
#line 787 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3628 "parser2.cpp"
    break;

  case 191: // expr_primitive: expr_self
#line 788 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3634 "parser2.cpp"
    break;

  case 192: // expr_primitive: expr_anim
#line 789 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3640 "parser2.cpp"
    break;

  case 193: // expr_primitive: expr_level
#line 790 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3646 "parser2.cpp"
    break;

  case 194: // expr_primitive: expr_animation
#line 791 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animation::ptr > ()); }
#line 3652 "parser2.cpp"
    break;

  case 195: // expr_primitive: expr_animtree
#line 792 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animtree::ptr > ()); }
#line 3658 "parser2.cpp"
    break;

  case 196: // expr_primitive: expr_identifier
#line 793 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3664 "parser2.cpp"
    break;

  case 197: // expr_primitive: expr_istring
#line 794 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_istring::ptr > ()); }
#line 3670 "parser2.cpp"
    break;

  case 198: // expr_primitive: expr_string
#line 795 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_string::ptr > ()); }
#line 3676 "parser2.cpp"
    break;

  case 199: // expr_primitive: expr_vector
#line 796 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vector::ptr > ()); }
#line 3682 "parser2.cpp"
    break;

  case 200: // expr_primitive: expr_hash
#line 797 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_hash::ptr > ()); }
#line 3688 "parser2.cpp"
    break;

  case 201: // expr_primitive: expr_float
#line 798 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_float::ptr > ()); }
#line 3694 "parser2.cpp"
    break;

  case 202: // expr_primitive: expr_integer
#line 799 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_integer::ptr > ()); }
#line 3700 "parser2.cpp"
    break;

  case 203: // expr_primitive: expr_false
#line 800 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_false::ptr > ()); }
#line 3706 "parser2.cpp"
    break;

  case 204: // expr_primitive: expr_true
#line 801 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_true::ptr > ()); }
#line 3712 "parser2.cpp"
    break;

  case 205: // expr_complement: "~" expr
#line 806 "parser2.ypp"
        { yylhs.value.as < expr_complement::ptr > () = expr_complement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3718 "parser2.cpp"
    break;

  case 206: // expr_negate: "-" expr_identifier
#line 811 "parser2.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3724 "parser2.cpp"
    break;

  case 207: // expr_negate: "-" expr_paren
#line 813 "parser2.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_paren::ptr > ())); }
#line 3730 "parser2.cpp"
    break;

  case 208: // expr_negate: "-" expr_array
#line 815 "parser2.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_array::ptr > ())); }
#line 3736 "parser2.cpp"
    break;

  case 209: // expr_negate: "-" expr_field
#line 817 "parser2.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_field::ptr > ())); }
#line 3742 "parser2.cpp"
    break;

  case 210: // expr_not: "!" expr
#line 822 "parser2.ypp"
        { yylhs.value.as < expr_not::ptr > () = expr_not::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3748 "parser2.cpp"
    break;

  case 211: // expr_new: "new" expr_identifier "(" ")"
#line 827 "parser2.ypp"
        { yylhs.value.as < expr_new::ptr > () = expr_new::make(yylhs.location, std::move(yystack_[2].value.as < expr_identifier::ptr > ())); }
#line 3754 "parser2.cpp"
    break;

  case 212: // expr_call: expr_function
#line 831 "parser2.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3760 "parser2.cpp"
    break;

  case 213: // expr_call: expr_pointer
#line 832 "parser2.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3766 "parser2.cpp"
    break;

  case 214: // expr_call: expr_member
#line 833 "parser2.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3772 "parser2.cpp"
    break;

  case 215: // expr_method: expr_object expr_function
#line 838 "parser2.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3783 "parser2.cpp"
    break;

  case 216: // expr_method: expr_object expr_pointer
#line 845 "parser2.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3794 "parser2.cpp"
    break;

  case 217: // expr_method: expr_object expr_member
#line 852 "parser2.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3805 "parser2.cpp"
    break;

  case 218: // expr_function: expr_identifier "(" expr_arguments ")"
#line 862 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3811 "parser2.cpp"
    break;

  case 219: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 864 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3817 "parser2.cpp"
    break;

  case 220: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 866 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3823 "parser2.cpp"
    break;

  case 221: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 868 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3829 "parser2.cpp"
    break;

  case 222: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 873 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3835 "parser2.cpp"
    break;

  case 223: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 875 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3841 "parser2.cpp"
    break;

  case 224: // expr_member: "[" "[" expr "]" "]" "->" expr_identifier "(" expr_arguments ")"
#line 880 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_member::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3847 "parser2.cpp"
    break;

  case 225: // expr_member: "thread" "[" "[" expr "]" "]" "->" expr_identifier "(" expr_arguments ")"
#line 882 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_member::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3853 "parser2.cpp"
    break;

  case 226: // expr_parameters: expr_parameters "," expr_parameters_default
#line 887 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3859 "parser2.cpp"
    break;

  case 227: // expr_parameters: expr_parameters "," expr_identifier
#line 889 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3865 "parser2.cpp"
    break;

  case 228: // expr_parameters: expr_parameters_default
#line 891 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3871 "parser2.cpp"
    break;

  case 229: // expr_parameters: expr_identifier
#line 893 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3877 "parser2.cpp"
    break;

  case 230: // expr_parameters: %empty
#line 895 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); }
#line 3883 "parser2.cpp"
    break;

  case 231: // expr_parameters_default: expr_identifier "=" expr
#line 900 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr_identifier::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 3889 "parser2.cpp"
    break;

  case 232: // expr_arguments: expr_arguments_no_empty
#line 905 "parser2.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[0].value.as < expr_arguments::ptr > ()); }
#line 3895 "parser2.cpp"
    break;

  case 233: // expr_arguments: %empty
#line 907 "parser2.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); }
#line 3901 "parser2.cpp"
    break;

  case 234: // expr_arguments_no_empty: expr_arguments "," expr
#line 912 "parser2.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[2].value.as < expr_arguments::ptr > ()); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3907 "parser2.cpp"
    break;

  case 235: // expr_arguments_no_empty: expr
#line 914 "parser2.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3913 "parser2.cpp"
    break;

  case 236: // expr_getnextarraykey: "getnextarraykey" "(" expr "," expr ")"
#line 919 "parser2.ypp"
        { yylhs.value.as < expr_getnextarraykey::ptr > () = expr_getnextarraykey::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3919 "parser2.cpp"
    break;

  case 237: // expr_getfirstarraykey: "getfirstarraykey" "(" expr ")"
#line 924 "parser2.ypp"
        { yylhs.value.as < expr_getfirstarraykey::ptr > () = expr_getfirstarraykey::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3925 "parser2.cpp"
    break;

  case 238: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr ")"
#line 929 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcoloralpha::ptr > () = expr_getdvarcoloralpha::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3931 "parser2.cpp"
    break;

  case 239: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr "," expr ")"
#line 931 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcoloralpha::ptr > () = expr_getdvarcoloralpha::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3937 "parser2.cpp"
    break;

  case 240: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr ")"
#line 936 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorblue::ptr > () = expr_getdvarcolorblue::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3943 "parser2.cpp"
    break;

  case 241: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr "," expr ")"
#line 938 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorblue::ptr > () = expr_getdvarcolorblue::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3949 "parser2.cpp"
    break;

  case 242: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr ")"
#line 943 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorgreen::ptr > () = expr_getdvarcolorgreen::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3955 "parser2.cpp"
    break;

  case 243: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr "," expr ")"
#line 945 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorgreen::ptr > () = expr_getdvarcolorgreen::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3961 "parser2.cpp"
    break;

  case 244: // expr_getdvarcolorred: "getdvarcolorred" "(" expr ")"
#line 950 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorred::ptr > () = expr_getdvarcolorred::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3967 "parser2.cpp"
    break;

  case 245: // expr_getdvarcolorred: "getdvarcolorred" "(" expr "," expr ")"
#line 952 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorred::ptr > () = expr_getdvarcolorred::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3973 "parser2.cpp"
    break;

  case 246: // expr_getdvarvector: "getdvarvector" "(" expr ")"
#line 957 "parser2.ypp"
        { yylhs.value.as < expr_getdvarvector::ptr > () = expr_getdvarvector::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3979 "parser2.cpp"
    break;

  case 247: // expr_getdvarvector: "getdvarvector" "(" expr "," expr ")"
#line 959 "parser2.ypp"
        { yylhs.value.as < expr_getdvarvector::ptr > () = expr_getdvarvector::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3985 "parser2.cpp"
    break;

  case 248: // expr_getdvarfloat: "getdvarfloat" "(" expr ")"
#line 964 "parser2.ypp"
        { yylhs.value.as < expr_getdvarfloat::ptr > () = expr_getdvarfloat::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3991 "parser2.cpp"
    break;

  case 249: // expr_getdvarfloat: "getdvarfloat" "(" expr "," expr ")"
#line 966 "parser2.ypp"
        { yylhs.value.as < expr_getdvarfloat::ptr > () = expr_getdvarfloat::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3997 "parser2.cpp"
    break;

  case 250: // expr_getdvarint: "getdvarint" "(" expr ")"
#line 971 "parser2.ypp"
        { yylhs.value.as < expr_getdvarint::ptr > () = expr_getdvarint::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4003 "parser2.cpp"
    break;

  case 251: // expr_getdvarint: "getdvarint" "(" expr "," expr ")"
#line 973 "parser2.ypp"
        { yylhs.value.as < expr_getdvarint::ptr > () = expr_getdvarint::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 4009 "parser2.cpp"
    break;

  case 252: // expr_getdvar: "getdvar" "(" expr ")"
#line 978 "parser2.ypp"
        { yylhs.value.as < expr_getdvar::ptr > () = expr_getdvar::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4015 "parser2.cpp"
    break;

  case 253: // expr_gettime: "gettime" "(" ")"
#line 983 "parser2.ypp"
        { yylhs.value.as < expr_gettime::ptr > () = expr_gettime::make(yylhs.location); }
#line 4021 "parser2.cpp"
    break;

  case 254: // expr_abs: "abs" "(" expr ")"
#line 988 "parser2.ypp"
        { yylhs.value.as < expr_abs::ptr > () = expr_abs::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4027 "parser2.cpp"
    break;

  case 255: // expr_vectortoangles: "vectortoangles" "(" expr ")"
#line 993 "parser2.ypp"
        { yylhs.value.as < expr_vectortoangles::ptr > () = expr_vectortoangles::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4033 "parser2.cpp"
    break;

  case 256: // expr_angleclamp180: "angleclamp180" "(" expr ")"
#line 998 "parser2.ypp"
        { yylhs.value.as < expr_angleclamp180::ptr > () = expr_angleclamp180::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4039 "parser2.cpp"
    break;

  case 257: // expr_anglestoforward: "anglestoforward" "(" expr ")"
#line 1003 "parser2.ypp"
        { yylhs.value.as < expr_anglestoforward::ptr > () = expr_anglestoforward::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4045 "parser2.cpp"
    break;

  case 258: // expr_anglestoright: "anglestoright" "(" expr ")"
#line 1008 "parser2.ypp"
        { yylhs.value.as < expr_anglestoright::ptr > () = expr_anglestoright::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4051 "parser2.cpp"
    break;

  case 259: // expr_anglestoup: "anglestoup" "(" expr ")"
#line 1013 "parser2.ypp"
        { yylhs.value.as < expr_anglestoup::ptr > () = expr_anglestoup::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4057 "parser2.cpp"
    break;

  case 260: // expr_vectorscale: "vectorscale" "(" expr "," expr ")"
#line 1018 "parser2.ypp"
        { yylhs.value.as < expr_vectorscale::ptr > () = expr_vectorscale::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4063 "parser2.cpp"
    break;

  case 261: // expr_isdefined: "isdefined" "(" expr ")"
#line 1023 "parser2.ypp"
        { yylhs.value.as < expr_isdefined::ptr > () = expr_isdefined::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4069 "parser2.cpp"
    break;

  case 262: // expr_reference: "&" expr_identifier
#line 1028 "parser2.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 4075 "parser2.cpp"
    break;

  case 263: // expr_reference: "&" expr_path "::" expr_identifier
#line 1030 "parser2.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, std::move(yystack_[2].value.as < expr_path::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 4081 "parser2.cpp"
    break;

  case 264: // expr_array: expr_object "[" expr "]"
#line 1035 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4087 "parser2.cpp"
    break;

  case 265: // expr_array: expr_getdvarvector "[" expr "]"
#line 1037 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_getdvarvector::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4093 "parser2.cpp"
    break;

  case 266: // expr_array: expr_vectortoangles "[" expr "]"
#line 1039 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_vectortoangles::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4099 "parser2.cpp"
    break;

  case 267: // expr_array: expr_angleclamp180 "[" expr "]"
#line 1041 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_angleclamp180::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4105 "parser2.cpp"
    break;

  case 268: // expr_array: expr_anglestoforward "[" expr "]"
#line 1043 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoforward::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4111 "parser2.cpp"
    break;

  case 269: // expr_array: expr_anglestoright "[" expr "]"
#line 1045 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoright::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4117 "parser2.cpp"
    break;

  case 270: // expr_array: expr_anglestoup "[" expr "]"
#line 1047 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoup::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4123 "parser2.cpp"
    break;

  case 271: // expr_array: expr_vectorscale "[" expr "]"
#line 1049 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_vectorscale::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4129 "parser2.cpp"
    break;

  case 272: // expr_field: expr_object "." expr_identifier_nosize
#line 1054 "parser2.ypp"
        { yylhs.value.as < expr_field::ptr > () = expr_field::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 4135 "parser2.cpp"
    break;

  case 273: // expr_size: expr_object "." "size"
#line 1059 "parser2.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 4141 "parser2.cpp"
    break;

  case 274: // expr_size: expr_string "." "size"
#line 1061 "parser2.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 4147 "parser2.cpp"
    break;

  case 275: // expr_paren: "(" expr ")"
#line 1066 "parser2.ypp"
        { yylhs.value.as < expr_paren::ptr > () = expr_paren::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4153 "parser2.cpp"
    break;

  case 276: // expr_object: expr_call
#line 1070 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 4159 "parser2.cpp"
    break;

  case 277: // expr_object: expr_method
#line 1071 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 4165 "parser2.cpp"
    break;

  case 278: // expr_object: expr_array
#line 1072 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 4171 "parser2.cpp"
    break;

  case 279: // expr_object: expr_field
#line 1073 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 4177 "parser2.cpp"
    break;

  case 280: // expr_object: expr_game
#line 1074 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 4183 "parser2.cpp"
    break;

  case 281: // expr_object: expr_self
#line 1075 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 4189 "parser2.cpp"
    break;

  case 282: // expr_object: expr_anim
#line 1076 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 4195 "parser2.cpp"
    break;

  case 283: // expr_object: expr_level
#line 1077 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 4201 "parser2.cpp"
    break;

  case 284: // expr_object: expr_world
#line 1078 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_world::ptr > ()); }
#line 4207 "parser2.cpp"
    break;

  case 285: // expr_object: expr_classes
#line 1079 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_classes::ptr > ()); }
#line 4213 "parser2.cpp"
    break;

  case 286: // expr_object: expr_identifier
#line 1080 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 4219 "parser2.cpp"
    break;

  case 287: // expr_empty_array: "[" "]"
#line 1085 "parser2.ypp"
        { yylhs.value.as < expr_empty_array::ptr > () = expr_empty_array::make(yylhs.location); }
#line 4225 "parser2.cpp"
    break;

  case 288: // expr_undefined: "undefined"
#line 1090 "parser2.ypp"
        { yylhs.value.as < expr_undefined::ptr > () = expr_undefined::make(yylhs.location); }
#line 4231 "parser2.cpp"
    break;

  case 289: // expr_game: "game"
#line 1095 "parser2.ypp"
        { yylhs.value.as < expr_game::ptr > () = expr_game::make(yylhs.location); }
#line 4237 "parser2.cpp"
    break;

  case 290: // expr_self: "self"
#line 1100 "parser2.ypp"
        { yylhs.value.as < expr_self::ptr > () = expr_self::make(yylhs.location); }
#line 4243 "parser2.cpp"
    break;

  case 291: // expr_anim: "anim"
#line 1105 "parser2.ypp"
        { yylhs.value.as < expr_anim::ptr > () = expr_anim::make(yylhs.location); }
#line 4249 "parser2.cpp"
    break;

  case 292: // expr_level: "level"
#line 1110 "parser2.ypp"
        { yylhs.value.as < expr_level::ptr > () = expr_level::make(yylhs.location); }
#line 4255 "parser2.cpp"
    break;

  case 293: // expr_world: "world"
#line 1115 "parser2.ypp"
        { yylhs.value.as < expr_world::ptr > () = expr_world::make(yylhs.location); }
#line 4261 "parser2.cpp"
    break;

  case 294: // expr_classes: "classes"
#line 1120 "parser2.ypp"
        { yylhs.value.as < expr_classes::ptr > () = expr_classes::make(yylhs.location); }
#line 4267 "parser2.cpp"
    break;

  case 295: // expr_animation: "%" "identifier"
#line 1125 "parser2.ypp"
        { yylhs.value.as < expr_animation::ptr > () = expr_animation::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4273 "parser2.cpp"
    break;

  case 296: // expr_animtree: "#animtree"
#line 1130 "parser2.ypp"
        { yylhs.value.as < expr_animtree::ptr > () = expr_animtree::make(yylhs.location); }
#line 4279 "parser2.cpp"
    break;

  case 297: // expr_identifier_nosize: "identifier"
#line 1135 "parser2.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4285 "parser2.cpp"
    break;

  case 298: // expr_identifier: "identifier"
#line 1140 "parser2.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4291 "parser2.cpp"
    break;

  case 299: // expr_identifier: "size"
#line 1142 "parser2.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, "size"); }
#line 4297 "parser2.cpp"
    break;

  case 300: // expr_path: "identifier"
#line 1147 "parser2.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4303 "parser2.cpp"
    break;

  case 301: // expr_path: "path"
#line 1149 "parser2.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4309 "parser2.cpp"
    break;

  case 302: // expr_istring: "localized string"
#line 1154 "parser2.ypp"
        { yylhs.value.as < expr_istring::ptr > () = expr_istring::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4315 "parser2.cpp"
    break;

  case 303: // expr_string: "string literal"
#line 1159 "parser2.ypp"
        { yylhs.value.as < expr_string::ptr > () = expr_string::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4321 "parser2.cpp"
    break;

  case 304: // expr_vector: "(" expr "," expr "," expr ")"
#line 1164 "parser2.ypp"
        { yylhs.value.as < expr_vector::ptr > () = expr_vector::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4327 "parser2.cpp"
    break;

  case 305: // expr_hash: "hash string"
#line 1169 "parser2.ypp"
        { yylhs.value.as < expr_hash::ptr > () = expr_hash::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4333 "parser2.cpp"
    break;

  case 306: // expr_float: "-" "float"
#line 1174 "parser2.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 4339 "parser2.cpp"
    break;

  case 307: // expr_float: "float"
#line 1176 "parser2.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4345 "parser2.cpp"
    break;

  case 308: // expr_integer: "-" "integer"
#line 1181 "parser2.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 4351 "parser2.cpp"
    break;

  case 309: // expr_integer: "integer"
#line 1183 "parser2.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4357 "parser2.cpp"
    break;

  case 310: // expr_false: "false"
#line 1188 "parser2.ypp"
        { yylhs.value.as < expr_false::ptr > () = expr_false::make(yylhs.location); }
#line 4363 "parser2.cpp"
    break;

  case 311: // expr_true: "true"
#line 1193 "parser2.ypp"
        { yylhs.value.as < expr_true::ptr > () = expr_true::make(yylhs.location); }
#line 4369 "parser2.cpp"
    break;


#line 4373 "parser2.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser2::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser2::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "#", "/#", "#/", "#inline",
  "#include", "#insert", "#using", "#using_animtree", "#namespace",
  "#animtree", "var", "class", "constructor", "destructor", "function",
  "autoexec", "codecall", "private", "endon", "notify", "wait",
  "waitrealtime", "waittill", "waittillmatch", "waittillframeend", "if",
  "else", "do", "while", "for", "foreach", "in", "switch", "case",
  "default", "break", "continue", "return", "prof_begin", "prof_end",
  "thread", "true", "false", "undefined", "size", "game", "self", "anim",
  "level", "const", "world", "classes", "new", "getnextarraykey",
  "getfirstarraykey", "getdvarcoloralpha", "getdvarcolorblue",
  "getdvarcolorgreen", "getdvarcolorred", "getdvarvector", "getdvarfloat",
  "getdvarint", "getdvar", "gettime", "abs", "vectortoangles",
  "angleclamp180", "anglestoforward", "anglestoright", "anglestoup",
  "vectorscale", "isdefined", "(", ")", "{", "}", "[", "]", ",", ".", "..",
  "...", "::", ":", ";", "?", "->", "++", "--", "<<", ">>", "||", "&&",
  "===", "!==", "==", "!=", "<=", ">=", "<", ">", "!", "~", "=", "+=",
  "-=", "*=", "/=", "%=", "|=", "&=", "^=", ">>=", "<<=", "|", "&", "^",
  "+", "-", "*", "/", "%", "path", "identifier", "string literal",
  "localized string", "hash string", "float", "integer", "SIZEOF", "THEN",
  "TERN", "NEG", "ANIMREF", "PREINC", "PREDEC", "POSTINC", "POSTDEC",
  "$accept", "main", "program", "inline", "insert", "include", "using",
  "declaration", "decl_namespace", "decl_usingtree", "decl_function",
  "decl_variable", "decl_class", "decl_list", "opt_class_base", "stmt",
  "stmt_or_dev", "stmt_list", "stmt_or_dev_list", "stmt_dev", "stmt_comp",
  "stmt_expr", "stmt_call", "stmt_const", "stmt_assign", "stmt_endon",
  "stmt_notify", "stmt_wait", "stmt_waitrealtime", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch",
  "stmt_case", "stmt_default", "stmt_break", "stmt_continue",
  "stmt_return", "stmt_prof_begin", "stmt_prof_end", "expr",
  "expr_or_empty", "expr_increment", "expr_decrement", "expr_assign",
  "expr_ternary", "expr_binary", "expr_primitive", "expr_complement",
  "expr_negate", "expr_not", "expr_new", "expr_call", "expr_method",
  "expr_function", "expr_pointer", "expr_member", "expr_parameters",
  "expr_parameters_default", "expr_arguments", "expr_arguments_no_empty",
  "expr_getnextarraykey", "expr_getfirstarraykey",
  "expr_getdvarcoloralpha", "expr_getdvarcolorblue",
  "expr_getdvarcolorgreen", "expr_getdvarcolorred", "expr_getdvarvector",
  "expr_getdvarfloat", "expr_getdvarint", "expr_getdvar", "expr_gettime",
  "expr_abs", "expr_vectortoangles", "expr_angleclamp180",
  "expr_anglestoforward", "expr_anglestoright", "expr_anglestoup",
  "expr_vectorscale", "expr_isdefined", "expr_reference", "expr_array",
  "expr_field", "expr_size", "expr_paren", "expr_object",
  "expr_empty_array", "expr_undefined", "expr_game", "expr_self",
  "expr_anim", "expr_level", "expr_world", "expr_classes",
  "expr_animation", "expr_animtree", "expr_identifier_nosize",
  "expr_identifier", "expr_path", "expr_istring", "expr_string",
  "expr_vector", "expr_hash", "expr_float", "expr_integer", "expr_false",
  "expr_true", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser2::context.
  parser2::context::context (const parser2& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser2::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if ARC2DEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }




  bool
  parser2::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if ARC2DEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser2::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (yy_lac_established_)
      return true;
    else
      {
#if ARC2DEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
  }

  // Discard any previous initial lookahead context.
  void
  parser2::yy_lac_discard_ (const char* event)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << event << '\n';
        yy_lac_established_ = false;
      }
  }


  int
  parser2::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser2::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short parser2::yypact_ninf_ = -452;

  const short parser2::yytable_ninf_ = -301;

  const short
  parser2::yypact_[] =
  {
     720,  -452,  -452,    96,    96,    96,    96,   -43,   -33,   -33,
       5,  -452,    35,   805,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,   -46,   -12,     0,    14,   -79,
    -452,  -452,    18,   -20,   -33,   -33,   -33,     4,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
      52,  -452,   -33,    47,    55,   100,   103,   -33,    94,  -452,
    -452,   -33,   -33,   -33,   -42,  -452,    79,  -452,    56,     2,
      13,    23,   111,   -33,  1537,   -33,   131,   140,  -452,  -452,
    -452,   111,   111,   111,  1022,  -452,  -452,    79,  -452,   -29,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,   -33,
     155,   156,   160,   165,   166,   167,   172,   173,   175,   176,
     177,   179,   183,   190,   191,   192,   201,   205,   206,  1537,
      38,  1537,  1537,   -41,  1400,    87,   199,  -452,  -452,  -452,
    -452,  4007,  -452,  -452,  -452,  -452,  -452,  -452,  -452,    43,
      65,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
     207,  -452,  -452,  -452,  -452,  -452,   208,   212,   213,   216,
     219,   221,  -452,  -452,   118,   275,  -452,  -452,   280,  -452,
    -452,   364,   472,   545,   582,  -452,  -452,  -452,  -452,    -5,
     200,  -452,   220,  -452,  -452,  -452,  -452,  -452,  -452,   214,
     227,   228,  -452,  -452,  -452,  1241,  1537,  1537,   218,   233,
    1735,   234,   237,   238,   242,   -39,   202,   239,   241,  1359,
     246,   249,   -33,  -452,   253,  -452,  1489,  1489,  -452,  -452,
    1172,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,   247,   251,   252,
     254,   257,   207,   208,   212,   213,   216,   219,   221,  -452,
    -452,   676,  -452,  -452,  -452,  -452,   265,   268,   273,   235,
     274,  1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,
    1537,   279,  1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,
    1746,  1537,  -452,  -452,  -452,  -452,   276,  1537,  -452,  -452,
    -452,  -452,   118,   275,  -452,   674,    -5,  -452,  1537,  1537,
    1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,
    1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,
    1537,  1537,  1537,  1537,  1537,  1537,  1626,   -28,  -452,  -452,
    -452,   265,  1537,   -33,   311,  -452,   111,   111,  -452,  -452,
    -452,  1310,  1530,  3894,  -452,  1537,   329,  1537,  1670,   -33,
    1537,   232,   286,   287,  -452,  -452,  -452,  -452,  3932,  1537,
    1537,   260,   674,   674,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,   300,   302,   303,   304,   259,  -452,  -452,  1537,
    1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,  1537,
    1537,  1537,   -33,   307,  3729,  2273,  1795,  1844,  1893,  1942,
    1991,  2040,  2089,  2310,  -452,  2347,  2384,  2421,  2458,  2495,
    2532,  3773,  2569,  -452,  1537,  3280,   -33,  2606,  3856,   151,
     151,  4019,  1018,   -63,   -63,  1807,  1807,   -63,   -63,   -63,
     -63,  4052,   783,  4064,   104,   104,  -452,  -452,  -452,  3325,
    3370,  3415,  3460,  3505,  3550,  3595,  1448,  3640,  -452,  -452,
    -452,  4007,    26,  -452,   309,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  2643,   314,  2680,   299,  -452,  -452,  -452,
     902,   -13,  2717,  -452,  -452,  -452,    61,    83,  1537,  1537,
    1537,  1537,  1537,  4007,  4007,  4007,  4007,  4007,  4007,  4007,
    4007,  4007,  4007,  4007,  3685,    86,   316,  -452,  1537,  -452,
    -452,  1537,  -452,  1537,  -452,  1537,  -452,  1537,  -452,  1537,
    -452,  1537,  -452,  1537,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  1537,  -452,  3817,   312,  -452,  1537,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  1537,  1537,  1735,  1537,
    1735,  1537,  1537,   -33,   111,   306,   308,  3970,  2754,  2138,
    2187,  2236,   318,  -452,  1537,  2791,  2828,  2865,  2902,  2939,
    2976,  3013,  3050,  3087,  1537,   -58,  4007,  4007,   101,   367,
    3124,  -452,  4007,   315,  3161,   365,  -452,  -452,  -452,  -452,
     321,   323,  1537,   325,  1537,   327,  1537,   -38,   108,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  3198,  1537,
     -33,  -452,  1735,   328,  1670,  1735,  1537,  -452,  -452,   322,
     340,  -452,   343,  -452,   347,  1537,   -33,  -452,  -452,   122,
     349,  -452,  -452,   351,  -452,  3235,   341,   344,   350,   126,
     355,  -452,  1537,  1735,  1735,  -452,  -452,  -452,  -452,  1537,
     129,  -452,  -452,   138,  -452,  -452
  };

  const short
  parser2::yydefact_[] =
  {
       3,    20,    21,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,     2,    11,    12,    13,    14,    15,    22,
      23,    24,    25,   301,   300,     0,     0,     0,     0,     0,
     299,   298,     0,    40,     0,     0,     0,     0,     1,     4,
       5,     6,     7,     8,     9,    16,    18,    17,    19,   303,
       0,    26,     0,     0,     0,     0,     0,   230,     0,    39,
      38,   230,   230,   230,     0,   228,   229,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    36,
      37,     0,     0,     0,     0,    28,   226,   227,   296,     0,
     311,   310,   288,   289,   290,   291,   292,   293,   294,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   298,   302,   305,   307,
     309,   231,   117,   118,   119,   158,   159,   160,   161,   162,
     163,   212,   213,   214,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,     0,   188,
     189,   190,   191,   192,   193,   284,   285,   194,   195,   196,
       0,   197,   198,   199,   200,   201,   202,   203,   204,     0,
       0,     0,    29,    30,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,     0,    75,     0,     0,    66,    73,
       0,    67,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     0,     0,     0,
     276,   277,     0,     0,     0,     0,     0,     0,     0,   278,
     279,     0,   280,   281,   282,   283,   286,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   287,   210,   205,   262,     0,     0,   306,   308,
     276,   277,   208,   209,   207,     0,   206,   295,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,   216,
     217,     0,   233,     0,     0,    32,     0,     0,    77,    71,
      69,     0,     0,     0,    99,     0,     0,     0,    83,     0,
       0,     0,     0,     0,   110,   111,   112,   114,     0,   233,
     233,     0,   122,   124,    78,    74,    72,    88,    89,    87,
      84,    85,     0,     0,     0,     0,     0,   123,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   233,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   253,     0,     0,     0,     0,     0,
       0,     0,     0,   275,     0,     0,     0,     0,     0,   151,
     152,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   153,   154,   155,   156,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   273,   297,
     272,   235,     0,   232,     0,   274,    34,    35,    76,    70,
      68,    93,    94,     0,     0,     0,     0,    81,    82,    80,
       0,     0,     0,   109,   108,   113,     0,     0,     0,     0,
       0,     0,     0,   126,   132,   133,   134,   135,   136,   127,
     128,   129,   131,   130,     0,     0,     0,   211,     0,   237,
     238,     0,   240,     0,   242,     0,   244,     0,   246,     0,
     248,     0,   250,     0,   252,   254,   255,   256,   257,   258,
     259,     0,   261,     0,     0,   263,     0,   265,   266,   267,
     268,   269,   270,   271,   264,   218,     0,   233,     0,     0,
       0,   121,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   220,   233,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   137,   234,     0,   100,
       0,   102,   120,     0,     0,     0,   107,   115,   116,    86,
       0,     0,   233,     0,   233,     0,   233,     0,     0,   236,
     239,   241,   243,   245,   247,   249,   251,   260,     0,   233,
       0,   219,     0,     0,    83,     0,     0,    90,    92,     0,
     232,    96,   232,    98,   232,   233,     0,   221,   304,     0,
       0,   101,   103,     0,   105,     0,     0,     0,     0,     0,
       0,   222,   233,     0,     0,    91,    95,    97,   223,   233,
       0,   104,   106,     0,   224,   225
  };

  const short
  parser2::yypgoto_[] =
  {
    -452,  -452,  -452,   421,   423,   428,   431,   434,  -452,  -452,
     380,  -452,  -452,  -452,  -452,  -180,   231,  -452,  -452,  -452,
     -36,  -162,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,  -452,
    -452,  -452,  -452,  -452,  -452,  -452,   642,  -452,  -353,  -351,
    -350,  -452,  -452,  -452,  -452,  -452,  -452,  -452,   -81,   -68,
    -155,  -135,  -104,    48,   381,  -176,  -451,  -452,  -452,  -452,
    -452,  -452,  -452,   -62,  -452,  -452,  -452,  -452,  -452,   -44,
     -21,    16,    29,    39,    62,  -452,  -452,    99,   136,  -452,
     331,   209,  -452,  -452,   222,   245,   258,   297,  -452,  -452,
    -452,  -452,  -452,    -8,     6,  -452,   -25,  -452,  -452,  -452,
     255,  -452,  -452
  };

  const short
  parser2::yydefgoto_[] =
  {
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    80,    22,    68,    53,   218,   219,   351,   220,   221,
     222,   476,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   461,   583,   247,   248,
     249,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,    64,    65,   619,   463,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   460,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188
  };

  const short
  parser2::yytable_[] =
  {
      32,    33,    37,   250,    50,   477,    30,   478,   479,    25,
      26,    27,    28,   338,    30,   350,   251,   609,    30,   458,
     356,   552,   252,    34,    35,    36,    54,    55,    56,   309,
     310,   610,    29,   339,    72,    38,    85,   625,  -286,    73,
     253,    45,  -286,   300,    59,   192,   193,   194,    49,    66,
     267,   626,    30,    66,    66,    66,   301,   324,   325,   326,
     327,   328,   252,   254,   340,    87,    52,   189,   553,    75,
     342,    76,    77,    10,  -286,    46,   266,  -286,    81,    57,
     253,   268,   361,    73,    23,   126,  -276,    47,    49,    82,
    -276,   270,   130,    31,    73,   269,    23,   126,   459,    83,
     255,    48,   545,   254,    73,    51,   338,   546,  -277,    69,
      70,    71,  -277,   256,   250,   295,   306,   291,   292,   250,
    -286,  -286,  -276,   257,    60,  -276,   339,   251,    58,   296,
      61,    31,   251,   252,    78,   300,   300,   555,   252,   250,
     255,   620,   546,   622,  -277,   624,   258,  -277,   301,   301,
     338,   253,   251,   256,   252,   252,   253,   340,   252,   556,
     341,  -278,   563,   257,   546,  -278,   462,   546,  -276,  -276,
     339,   470,   253,   253,   254,    62,   253,   611,    63,   254,
     362,    67,   546,   259,   627,    74,   258,   266,    84,   546,
    -277,  -277,   266,   486,   487,   254,   254,  -278,   641,   254,
    -278,   340,   648,   546,   371,   654,   190,   546,   266,   266,
     546,   255,   266,   307,   655,   191,   255,   338,   338,   546,
     260,    23,    24,   302,   256,   505,   326,   327,   328,   256,
     271,   272,   255,   255,   257,   273,   255,   339,   339,   257,
     274,   275,   276,  -278,  -278,   256,   256,   277,   278,   256,
     279,   280,   281,   341,   282,   257,   257,   258,   283,   257,
     303,   477,   258,   478,   479,   284,   285,   286,   340,   340,
     250,   324,   325,   326,   327,   328,   287,   300,   258,   258,
     288,   289,   258,   251,  -300,   343,   329,   330,   364,   252,
     301,   331,   332,   261,   259,   333,   252,   341,   334,   259,
     335,   345,   344,   346,   347,   354,   262,   253,   355,   357,
     466,   467,   358,   359,   253,   259,   259,   360,  -279,   259,
     402,   369,  -279,    89,   370,   338,   365,    30,   366,   263,
     254,   260,   291,   305,   377,   464,   260,   254,   378,   379,
     342,   380,   264,   266,   381,   339,   262,   400,   401,   403,
     266,   481,   260,   260,  -279,   414,   260,  -279,   465,   336,
     474,   426,   337,   299,   341,   341,   488,   255,   579,   263,
     581,   578,   483,   484,   255,   489,   340,   490,   491,   492,
     256,   265,   264,   507,   547,   459,   551,   256,   598,   549,
     257,   564,   575,   587,   506,   588,   612,   257,   597,   616,
    -279,  -279,   614,   546,   261,    23,   126,  -280,   617,   261,
     618,  -280,   621,   258,   623,   632,   636,   262,   535,   637,
     258,   265,   262,   638,   642,   372,   373,   643,   645,   261,
     649,   646,   631,   629,    40,   634,    41,   647,   262,   262,
     263,    42,   262,  -280,    43,   263,  -280,    44,    79,   639,
     259,   376,   633,   264,    86,   304,     0,   259,   264,     0,
     363,   263,   263,   651,   652,   263,   650,   250,     0,   250,
       0,     0,   341,   653,   264,   264,     0,     0,   264,     0,
     251,     0,   251,     0,     0,     0,   252,   260,   252,  -280,
    -280,     0,   265,     0,   260,     0,     0,   265,     0,     0,
       0,     0,     0,     0,   253,     0,   253,     0,     0,     0,
       0,     0,     0,   265,   265,  -281,     0,   265,   586,  -281,
       0,     0,     0,     0,     0,     0,     0,   254,     0,   254,
       0,   250,     0,   300,   250,     0,     0,     0,     0,     0,
     266,     0,   266,     0,   251,   585,   301,   251,     0,     0,
     252,  -281,   252,   252,  -281,     0,     0,     0,     0,     0,
     261,     0,   250,   250,   255,     0,   255,   480,   253,     0,
     253,   253,     0,   262,     0,   251,   251,   256,     0,   256,
     262,   252,   252,     0,     0,     0,     0,   257,  -282,   257,
       0,   254,  -282,   254,   254,     0,   263,  -281,  -281,   253,
     253,     0,   630,   263,   266,     0,   266,   266,     0,   264,
     258,     0,   258,     0,     0,     0,   264,     0,   640,     0,
       0,     0,   254,   254,  -282,  -283,     0,  -282,   255,  -283,
     255,   255,     0,     0,     0,   266,   266,     0,     0,     0,
       0,   256,     0,   256,   256,     0,     0,   259,   265,   259,
       0,   257,     0,   257,   257,   265,     0,     0,     0,   255,
     255,  -283,     0,     0,  -283,     0,     0,     0,     0,     0,
    -282,  -282,   256,   256,   258,     0,   258,   258,     0,     0,
       0,     0,   257,   257,   260,     0,   260,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   382,   383,     0,
       0,   384,   385,     0,     0,   258,   258,  -283,  -283,     0,
       0,   259,     0,   259,   259,     0,   131,    89,     0,    89,
       0,    30,     0,    30,     1,     2,     3,     4,     5,     6,
       7,     8,     0,     0,     9,     0,     0,    10,     0,     0,
       0,     0,   259,   259,     0,     0,     0,     0,   260,     0,
     260,   260,     0,   336,     0,   336,   386,   261,   386,   261,
       0,   290,     0,   293,   294,     0,   387,   388,     0,     0,
     262,     0,   262,     0,     0,     0,     0,     0,     0,   260,
     260,     0,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   263,     0,   263,     0,     0,     0,    23,
     126,    23,   126,     0,     0,     0,   264,    11,   264,     1,
       2,     3,     4,     5,     6,     7,     8,     0,     0,     9,
       0,   261,    10,   480,   261,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   262,     0,   262,   262,   352,   353,
       0,     0,     0,     0,     0,   265,     0,   265,     0,     0,
       0,   368,   261,   261,     0,     0,     0,   263,     0,   263,
     263,     0,     0,     0,     0,   262,   262,     0,     0,     0,
     264,     0,   264,   264,     0,   309,   310,     0,     0,   313,
     314,   315,   316,   317,   318,   319,   320,     0,   263,   263,
       0,     0,    39,     0,     0,     0,     0,     0,     0,     0,
       0,   264,   264,   324,   325,   326,   327,   328,     0,   265,
       0,   265,   265,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,     0,   415,   416,   417,   418,   419,   420,
     421,   422,     0,   425,     0,     0,     0,     0,     0,   427,
     265,   265,     0,     0,     0,    89,     0,     0,     0,    30,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   457,     0,
       0,   336,     0,     0,   386,     0,     0,     0,     0,     0,
       0,     0,   387,   388,     0,     0,     0,   473,     0,   475,
       0,     0,   482,     0,     0,     0,     0,     0,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,     0,
       0,     0,     0,     0,     0,     0,   195,    23,   126,     0,
       0,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,     0,     0,   196,   197,     0,     0,   198,
     199,     0,   200,   201,   202,   203,     0,   204,   205,   206,
     207,   208,   209,   210,   211,    89,   533,     0,     0,    30,
      93,    94,    95,    96,   212,    97,    98,     0,     0,     0,
       0,     0,     0,     0,   106,     0,     0,     0,     0,     0,
     112,   113,   114,   115,   116,   117,     0,     0,   425,    84,
     213,   214,     0,     0,     0,     0,     0,     0,     0,   215,
     309,   310,   216,   217,   313,   314,   315,   316,   317,   318,
     319,   320,     0,     0,     0,     0,     0,     0,     0,     0,
     557,   558,   559,   560,   561,   321,   322,   323,   324,   325,
     326,   327,   328,     0,     0,     0,     0,    23,   126,     0,
     565,     0,     0,   566,     0,   567,     0,   568,     0,   569,
       0,   570,     0,   571,     0,   572,     0,     0,     0,     0,
       0,     0,     0,   573,     0,     0,   195,     0,   576,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   577,     0,
       0,   580,     0,   582,   584,   196,   197,     0,     0,   198,
     199,     0,   200,   201,   202,   203,     0,   204,   205,   206,
     207,   208,   209,   210,   211,    89,   608,     0,     0,    30,
      93,    94,    95,    96,   212,    97,    98,     0,     0,     0,
       0,     0,     0,     0,   106,     0,     0,     0,     0,     0,
     112,   113,   114,   115,   116,   117,   348,     0,     0,    84,
     374,   214,     0,     0,     0,     0,     0,     0,   635,   375,
       0,     0,   216,   217,   196,   197,     0,     0,   198,   199,
       0,   200,   201,   202,   203,     0,   204,   205,   206,   207,
     208,   209,   210,   211,    89,     0,     0,     0,    30,    93,
      94,    95,    96,   212,    97,    98,     0,    23,   126,     0,
       0,     0,     0,   106,     0,     0,     0,     0,     0,   112,
     113,   114,   115,   116,   117,   468,     0,     0,    84,     0,
     214,     0,     0,     0,     0,     0,     0,     0,   349,     0,
       0,   216,   217,   196,   197,     0,     0,   198,   199,     0,
     200,   201,   202,   203,     0,   204,   205,   206,   207,   208,
     209,   210,   211,    89,     0,     0,     0,    30,    93,    94,
      95,    96,   212,    97,    98,     0,    23,   126,     0,     0,
       0,    88,   106,     0,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,     0,     0,     0,    84,     0,   214,
       0,     0,     0,     0,     0,     0,     0,   469,     0,     0,
     216,   217,    89,    90,    91,    92,    30,    93,    94,    95,
      96,     0,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,    23,   126,     0,   120,     0,
       0,     0,     0,    89,     0,     0,   367,    30,    93,    94,
      95,    96,     0,    97,    98,     0,     0,     0,     0,     0,
      88,     0,   106,   121,   122,     0,     0,     0,   112,   113,
     114,   115,   116,   117,     0,   297,     0,   123,     0,   214,
     124,     0,     0,   125,    23,   126,    49,   127,   128,   129,
     130,    89,    90,    91,    92,    30,    93,    94,    95,    96,
       0,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,     0,    23,   126,   456,   292,     0,
     298,   299,    89,     0,     0,     0,    30,    93,    94,    95,
      96,     0,    97,    98,     0,     0,     0,     0,     0,    88,
       0,   106,   121,   122,     0,     0,     0,   112,   113,   114,
     115,   116,   117,     0,     0,     0,   123,     0,   214,   124,
       0,     0,   125,    23,   126,    49,   127,   128,   129,   130,
      89,    90,    91,    92,    30,    93,    94,    95,    96,     0,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,     0,    23,   126,   120,   471,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,    88,     0,
       0,   121,   122,     0,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   123,     0,     0,   124,     0,
       0,   125,    23,   126,    49,   127,   128,   129,   130,    89,
      90,    91,    92,    30,    93,    94,    95,    96,     0,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,     0,     0,     0,   456,     0,     0,     0,     0,
       0,     0,     0,    89,     0,     0,     0,    30,    93,    94,
      95,    96,     0,    97,    98,     0,     0,     0,     0,     0,
     121,   122,   106,     0,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,   123,     0,     0,   124,     0,   214,
     125,    23,   126,    49,   127,   128,   129,   130,   196,   197,
     216,   217,   198,   199,     0,   200,   201,   202,   203,     0,
     204,   205,   206,   207,   208,   209,   210,   211,    89,     0,
       0,     0,    30,    93,    94,    95,    96,   212,    97,    98,
       0,     0,     0,     0,     0,    23,   126,   106,     0,     0,
       0,     0,     0,   112,   113,   114,   115,   116,   117,     0,
       0,     0,    84,     0,   214,     0,     0,     0,     0,     0,
       0,     0,   423,     0,     0,   216,   217,   424,     0,     0,
       0,     0,     0,     0,   308,     0,     0,     0,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,   126,     0,   321,   322,   323,   324,   325,   326,   327,
     328,   510,     0,     0,     0,     0,   511,     0,     0,     0,
       0,     0,     0,   308,     0,     0,     0,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   309,
     310,     0,     0,   313,   314,     0,     0,   317,   318,   319,
     320,     0,   321,   322,   323,   324,   325,   326,   327,   328,
     512,     0,     0,     0,     0,   513,     0,   324,   325,   326,
     327,   328,   308,     0,     0,     0,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   321,   322,   323,   324,   325,   326,   327,   328,   514,
       0,     0,     0,     0,   515,     0,     0,     0,     0,     0,
       0,   308,     0,     0,     0,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     321,   322,   323,   324,   325,   326,   327,   328,   516,     0,
       0,     0,     0,   517,     0,     0,     0,     0,     0,     0,
     308,     0,     0,     0,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   321,
     322,   323,   324,   325,   326,   327,   328,   518,     0,     0,
       0,     0,   519,     0,     0,     0,     0,     0,     0,   308,
       0,     0,     0,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   321,   322,
     323,   324,   325,   326,   327,   328,   520,     0,     0,     0,
       0,   521,     0,     0,     0,     0,     0,     0,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   522,     0,     0,     0,     0,
     523,     0,     0,     0,     0,     0,     0,   308,     0,     0,
       0,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   321,   322,   323,   324,
     325,   326,   327,   328,   591,     0,     0,     0,     0,   592,
       0,     0,     0,     0,     0,     0,   308,     0,     0,     0,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   321,   322,   323,   324,   325,
     326,   327,   328,   593,     0,     0,     0,     0,   594,     0,
       0,     0,     0,     0,     0,   308,     0,     0,     0,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   321,   322,   323,   324,   325,   326,
     327,   328,   595,     0,     0,     0,     0,   596,     0,     0,
       0,     0,     0,     0,   308,     0,     0,     0,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   509,
       0,     0,     0,   321,   322,   323,   324,   325,   326,   327,
     328,   308,     0,     0,     0,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   524,     0,     0,     0,
     321,   322,   323,   324,   325,   326,   327,   328,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   525,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   308,     0,     0,     0,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     526,     0,     0,     0,   321,   322,   323,   324,   325,   326,
     327,   328,   308,     0,     0,     0,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   527,     0,     0,
       0,   321,   322,   323,   324,   325,   326,   327,   328,   308,
       0,     0,     0,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   528,     0,     0,     0,   321,   322,
     323,   324,   325,   326,   327,   328,   308,     0,     0,     0,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   529,     0,     0,     0,   321,   322,   323,   324,   325,
     326,   327,   328,   308,     0,     0,     0,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   530,     0,
       0,     0,   321,   322,   323,   324,   325,   326,   327,   328,
     308,     0,     0,     0,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   532,     0,     0,     0,   321,
     322,   323,   324,   325,   326,   327,   328,   308,     0,     0,
       0,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   423,     0,     0,     0,   321,   322,   323,   324,
     325,   326,   327,   328,   308,     0,     0,     0,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   548,
       0,     0,     0,   321,   322,   323,   324,   325,   326,   327,
     328,   308,     0,     0,     0,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   550,     0,     0,     0,
     321,   322,   323,   324,   325,   326,   327,   328,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   554,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   308,     0,     0,     0,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     590,     0,     0,     0,   321,   322,   323,   324,   325,   326,
     327,   328,   308,     0,     0,     0,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   599,     0,     0,
       0,   321,   322,   323,   324,   325,   326,   327,   328,   308,
       0,     0,     0,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   600,     0,     0,     0,   321,   322,
     323,   324,   325,   326,   327,   328,   308,     0,     0,     0,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   601,     0,     0,     0,   321,   322,   323,   324,   325,
     326,   327,   328,   308,     0,     0,     0,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   602,     0,
       0,     0,   321,   322,   323,   324,   325,   326,   327,   328,
     308,     0,     0,     0,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   603,     0,     0,     0,   321,
     322,   323,   324,   325,   326,   327,   328,   308,     0,     0,
       0,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   604,     0,     0,     0,   321,   322,   323,   324,
     325,   326,   327,   328,   308,     0,     0,     0,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   605,
       0,     0,     0,   321,   322,   323,   324,   325,   326,   327,
     328,   308,     0,     0,     0,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   606,     0,     0,     0,
     321,   322,   323,   324,   325,   326,   327,   328,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   607,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   308,     0,     0,     0,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     613,     0,     0,     0,   321,   322,   323,   324,   325,   326,
     327,   328,   308,     0,     0,     0,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   615,     0,     0,
       0,   321,   322,   323,   324,   325,   326,   327,   328,   308,
       0,     0,     0,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   628,     0,     0,     0,   321,   322,
     323,   324,   325,   326,   327,   328,   308,     0,     0,     0,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   644,     0,     0,     0,   321,   322,   323,   324,   325,
     326,   327,   328,   308,     0,     0,     0,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   321,   322,   323,   324,   325,   326,   327,   328,
     534,     0,     0,     0,     0,     0,     0,     0,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   537,     0,     0,     0,     0,
       0,     0,     0,   308,     0,     0,     0,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   321,   322,   323,   324,   325,   326,   327,   328,
     538,     0,     0,     0,     0,     0,     0,     0,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   539,     0,     0,     0,     0,
       0,     0,     0,   308,     0,     0,     0,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   321,   322,   323,   324,   325,   326,   327,   328,
     540,     0,     0,     0,     0,     0,     0,     0,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   541,     0,     0,     0,     0,
       0,     0,     0,   308,     0,     0,     0,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   321,   322,   323,   324,   325,   326,   327,   328,
     542,     0,     0,     0,     0,     0,     0,     0,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   543,     0,     0,     0,     0,
       0,     0,     0,   308,     0,     0,     0,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   321,   322,   323,   324,   325,   326,   327,   328,
     544,     0,     0,     0,     0,     0,     0,     0,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   562,     0,     0,     0,     0,
       0,     0,     0,   308,     0,     0,     0,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   321,   322,   323,   324,   325,   326,   327,   328,
     508,     0,     0,     0,     0,     0,     0,   308,     0,     0,
       0,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   321,   322,   323,   324,
     325,   326,   327,   328,   531,     0,     0,     0,     0,     0,
       0,   308,     0,     0,     0,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     321,   322,   323,   324,   325,   326,   327,   328,   574,     0,
       0,     0,     0,     0,     0,   308,     0,     0,     0,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   321,   322,   323,   324,   325,   326,
     327,   328,   536,     0,   308,     0,     0,     0,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   321,   322,   323,   324,   325,   326,   327,
     328,   472,   308,     0,     0,     0,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   321,   322,   323,   324,   325,   326,   327,   328,   485,
     308,     0,     0,     0,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   321,
     322,   323,   324,   325,   326,   327,   328,   589,   308,     0,
       0,     0,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,   322,   323,
     324,   325,   326,   327,   328,   308,     0,     0,     0,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   309,   310,     0,   312,   313,   314,   315,   316,   317,
     318,   319,   320,     0,   321,   322,   323,   324,   325,   326,
     327,   328,     0,     0,     0,     0,   321,   322,   323,   324,
     325,   326,   327,   328,   309,   310,     0,     0,   313,   314,
     315,   316,   317,   318,   319,   320,   309,   310,     0,     0,
     313,   314,   315,   316,   317,   318,   319,   320,     0,     0,
     322,   323,   324,   325,   326,   327,   328,     0,     0,     0,
       0,     0,   322,     0,   324,   325,   326,   327,   328
  };

  const short
  parser2::yycheck_[] =
  {
       8,     9,    10,    84,    29,   358,    47,   358,   358,     3,
       4,     5,     6,   168,    47,   195,    84,    75,    47,    47,
     200,    34,    84,    18,    19,    20,    34,    35,    36,    92,
      93,    89,    75,   168,    76,     0,    72,    75,    43,    81,
      84,    87,    47,   124,    52,    81,    82,    83,   127,    57,
      79,    89,    47,    61,    62,    63,   124,   120,   121,   122,
     123,   124,   124,    84,   168,    73,    86,    75,    81,    13,
      75,    15,    16,    17,    79,    87,    84,    82,    76,    75,
     124,    89,   121,    81,   125,   126,    43,    87,   127,    76,
      47,    99,   131,   126,    81,    89,   125,   126,   126,    76,
      84,    87,    76,   124,    81,    87,   261,    81,    43,    61,
      62,    63,    47,    84,   195,   123,   124,    79,    80,   200,
     125,   126,    79,    84,    77,    82,   261,   195,    76,   123,
      75,   126,   200,   195,    78,   216,   217,    76,   200,   220,
     124,   592,    81,   594,    79,   596,    84,    82,   216,   217,
     305,   195,   220,   124,   216,   217,   200,   261,   220,    76,
     168,    43,    76,   124,    81,    47,   342,    81,   125,   126,
     305,   351,   216,   217,   195,    75,   220,    76,    75,   200,
     205,    87,    81,    84,    76,   106,   124,   195,    77,    81,
     125,   126,   200,   369,   370,   216,   217,    79,    76,   220,
      82,   305,    76,    81,   212,    76,    75,    81,   216,   217,
      81,   195,   220,   126,    76,    75,   200,   372,   373,    81,
      84,   125,   126,   124,   195,   401,   122,   123,   124,   200,
      75,    75,   216,   217,   195,    75,   220,   372,   373,   200,
      75,    75,    75,   125,   126,   216,   217,    75,    75,   220,
      75,    75,    75,   261,    75,   216,   217,   195,    75,   220,
     124,   614,   200,   614,   614,    75,    75,    75,   372,   373,
     351,   120,   121,   122,   123,   124,    75,   358,   216,   217,
      75,    75,   220,   351,    85,    85,    79,    79,    86,   351,
     358,    79,    79,    84,   195,    79,   358,   305,    79,   200,
      79,    87,    82,    76,    76,    87,    84,   351,    75,    75,
     346,   347,    75,    75,   358,   216,   217,    75,    43,   220,
      85,    75,    47,    43,    75,   480,    87,    47,    87,    84,
     351,   195,    79,   124,    87,   343,   200,   358,    87,    87,
      75,    87,    84,   351,    87,   480,   124,    79,    75,    75,
     358,   359,   216,   217,    79,    76,   220,    82,    47,    79,
      31,    85,    82,   131,   372,   373,   106,   351,   548,   124,
     550,   547,    86,    86,   358,    75,   480,    75,    75,    75,
     351,    84,   124,    76,    75,   126,    87,   358,   564,    75,
     351,    75,    80,    87,   402,    87,    29,   358,    80,    34,
     125,   126,    87,    81,   195,   125,   126,    43,    87,   200,
      87,    47,    87,   351,    87,    87,    76,   195,   426,    76,
     358,   124,   200,    76,    75,   216,   217,    76,    87,   220,
      75,    87,   612,   609,    13,   615,    13,    87,   216,   217,
     195,    13,   220,    79,    13,   200,    82,    13,    68,   625,
     351,   220,   614,   195,    73,   124,    -1,   358,   200,    -1,
     205,   216,   217,   643,   644,   220,   642,   548,    -1,   550,
      -1,    -1,   480,   649,   216,   217,    -1,    -1,   220,    -1,
     548,    -1,   550,    -1,    -1,    -1,   548,   351,   550,   125,
     126,    -1,   195,    -1,   358,    -1,    -1,   200,    -1,    -1,
      -1,    -1,    -1,    -1,   548,    -1,   550,    -1,    -1,    -1,
      -1,    -1,    -1,   216,   217,    43,    -1,   220,   554,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   548,    -1,   550,
      -1,   612,    -1,   614,   615,    -1,    -1,    -1,    -1,    -1,
     548,    -1,   550,    -1,   612,   553,   614,   615,    -1,    -1,
     612,    79,   614,   615,    82,    -1,    -1,    -1,    -1,    -1,
     351,    -1,   643,   644,   548,    -1,   550,   358,   612,    -1,
     614,   615,    -1,   351,    -1,   643,   644,   548,    -1,   550,
     358,   643,   644,    -1,    -1,    -1,    -1,   548,    43,   550,
      -1,   612,    47,   614,   615,    -1,   351,   125,   126,   643,
     644,    -1,   610,   358,   612,    -1,   614,   615,    -1,   351,
     548,    -1,   550,    -1,    -1,    -1,   358,    -1,   626,    -1,
      -1,    -1,   643,   644,    79,    43,    -1,    82,   612,    47,
     614,   615,    -1,    -1,    -1,   643,   644,    -1,    -1,    -1,
      -1,   612,    -1,   614,   615,    -1,    -1,   548,   351,   550,
      -1,   612,    -1,   614,   615,   358,    -1,    -1,    -1,   643,
     644,    79,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
     125,   126,   643,   644,   612,    -1,   614,   615,    -1,    -1,
      -1,    -1,   643,   644,   548,    -1,   550,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    -1,
      -1,    25,    26,    -1,    -1,   643,   644,   125,   126,    -1,
      -1,   612,    -1,   614,   615,    -1,    74,    43,    -1,    43,
      -1,    47,    -1,    47,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    14,    -1,    -1,    17,    -1,    -1,
      -1,    -1,   643,   644,    -1,    -1,    -1,    -1,   612,    -1,
     614,   615,    -1,    79,    -1,    79,    82,   548,    82,   550,
      -1,   119,    -1,   121,   122,    -1,    90,    91,    -1,    -1,
     548,    -1,   550,    -1,    -1,    -1,    -1,    -1,    -1,   643,
     644,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   548,    -1,   550,    -1,    -1,    -1,   125,
     126,   125,   126,    -1,    -1,    -1,   548,    87,   550,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    14,
      -1,   612,    17,   614,   615,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   612,    -1,   614,   615,   196,   197,
      -1,    -1,    -1,    -1,    -1,   548,    -1,   550,    -1,    -1,
      -1,   209,   643,   644,    -1,    -1,    -1,   612,    -1,   614,
     615,    -1,    -1,    -1,    -1,   643,   644,    -1,    -1,    -1,
     612,    -1,   614,   615,    -1,    92,    93,    -1,    -1,    96,
      97,    98,    99,   100,   101,   102,   103,    -1,   643,   644,
      -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   643,   644,   120,   121,   122,   123,   124,    -1,   612,
      -1,   614,   615,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,    -1,   282,   283,   284,   285,   286,   287,
     288,   289,    -1,   291,    -1,    -1,    -1,    -1,    -1,   297,
     643,   644,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,    -1,
      -1,    79,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    91,    -1,    -1,    -1,   355,    -1,   357,
      -1,    -1,   360,    -1,    -1,    -1,    -1,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,   125,   126,    -1,
      -1,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,    -1,    -1,    23,    24,    -1,    -1,    27,
      28,    -1,    30,    31,    32,    33,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43,   424,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    -1,    -1,   456,    77,
      78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,
      92,    93,    90,    91,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     488,   489,   490,   491,   492,   117,   118,   119,   120,   121,
     122,   123,   124,    -1,    -1,    -1,    -1,   125,   126,    -1,
     508,    -1,    -1,   511,    -1,   513,    -1,   515,    -1,   517,
      -1,   519,    -1,   521,    -1,   523,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   531,    -1,    -1,     4,    -1,   536,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   546,    -1,
      -1,   549,    -1,   551,   552,    23,    24,    -1,    -1,    27,
      28,    -1,    30,    31,    32,    33,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43,   574,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,     5,    -1,    -1,    77,
      78,    79,    -1,    -1,    -1,    -1,    -1,    -1,   616,    87,
      -1,    -1,    90,    91,    23,    24,    -1,    -1,    27,    28,
      -1,    30,    31,    32,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,   125,   126,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,     5,    -1,    -1,    77,    -1,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,
      -1,    90,    91,    23,    24,    -1,    -1,    27,    28,    -1,
      30,    31,    32,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,   125,   126,    -1,    -1,
      -1,    12,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    77,    -1,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      90,    91,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   125,   126,    -1,    79,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    87,    47,    48,    49,
      50,    51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    62,   104,   105,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,    75,    -1,   118,    -1,    79,
     121,    -1,    -1,   124,   125,   126,   127,   128,   129,   130,
     131,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,   125,   126,    79,    80,    -1,
     130,   131,    43,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    62,   104,   105,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,   118,    -1,    79,   121,
      -1,    -1,   124,   125,   126,   127,   128,   129,   130,   131,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    -1,   125,   126,    79,    87,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    12,    -1,
      -1,   104,   105,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,   118,    -1,    -1,   121,    -1,
      -1,   124,   125,   126,   127,   128,   129,   130,   131,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,
     104,   105,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,   118,    -1,    -1,   121,    -1,    79,
     124,   125,   126,   127,   128,   129,   130,   131,    23,    24,
      90,    91,    27,    28,    -1,    30,    31,    32,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,   125,   126,    62,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    77,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    90,    91,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     125,   126,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    92,
      93,    -1,    -1,    96,    97,    -1,    -1,   100,   101,   102,
     103,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
      76,    -1,    -1,    -1,    -1,    81,    -1,   120,   121,   122,
     123,   124,    88,    -1,    -1,    -1,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,    76,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,    76,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,    76,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,    76,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    76,    -1,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,    76,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,    76,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,    88,    -1,    -1,    -1,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    88,    -1,    -1,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,    88,    -1,    -1,    -1,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,    88,
      -1,    -1,    -1,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,    88,    -1,    -1,    -1,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
      88,    -1,    -1,    -1,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,    88,    -1,    -1,
      -1,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,    88,    -1,    -1,    -1,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,    88,    -1,    -1,    -1,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    88,    -1,    -1,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,    88,    -1,    -1,    -1,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,    88,
      -1,    -1,    -1,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,    88,    -1,    -1,    -1,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
      88,    -1,    -1,    -1,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,    88,    -1,    -1,
      -1,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,    88,    -1,    -1,    -1,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,    88,    -1,    -1,    -1,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    88,    -1,    -1,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,    88,    -1,    -1,    -1,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,    88,
      -1,    -1,    -1,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,    88,    -1,    -1,    -1,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,
      -1,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    -1,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,    86,    -1,    88,    -1,    -1,    -1,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,    87,    88,    -1,    -1,    -1,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,    87,
      88,    -1,    -1,    -1,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,    87,    88,    -1,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,    88,    -1,    -1,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    92,    93,    -1,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,    92,    93,    -1,    -1,    96,    97,
      98,    99,   100,   101,   102,   103,    92,    93,    -1,    -1,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
     118,   119,   120,   121,   122,   123,   124,    -1,    -1,    -1,
      -1,    -1,   118,    -1,   120,   121,   122,   123,   124
  };

  const unsigned char
  parser2::yystos_[] =
  {
       0,     4,     5,     6,     7,     8,     9,    10,    11,    14,
      17,    87,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   153,   125,   126,   245,   245,   245,   245,    75,
      47,   126,   244,   244,    18,    19,    20,   244,     0,    87,
     144,   145,   146,   147,   148,    87,    87,    87,    87,   127,
     247,    87,    86,   155,   244,   244,   244,    75,    76,   244,
      77,    75,    75,    75,   204,   205,   244,    87,   154,   204,
     204,   204,    76,    81,   106,    13,    15,    16,    78,   151,
     152,    76,    76,    76,    77,   161,   205,   244,    12,    43,
      44,    45,    46,    48,    49,    50,    51,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      79,   104,   105,   118,   121,   124,   126,   128,   129,   130,
     131,   187,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   244,
      75,    75,   161,   161,   161,     4,    23,    24,    27,    28,
      30,    31,    32,    33,    35,    36,    37,    38,    39,    40,
      41,    42,    52,    78,    79,    87,    90,    91,   156,   157,
     159,   160,   161,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   189,   190,   191,
     199,   200,   214,   220,   221,   222,   223,   224,   225,   228,
     229,   232,   235,   236,   237,   238,   244,    79,   244,   245,
     244,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
     187,    79,    80,   187,   187,   244,   245,    75,   130,   131,
     199,   200,   228,   229,   231,   232,   244,   126,    88,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   117,   118,   119,   120,   121,   122,   123,   124,    79,
      79,    79,    79,    79,    79,    79,    79,    82,   201,   202,
     203,   244,    75,    85,    82,    87,    76,    76,     5,    87,
     156,   158,   187,   187,    87,    75,   156,    75,    75,    75,
      75,   121,   247,   251,    86,    87,    87,    87,   187,    75,
      75,   244,   232,   232,    78,    87,   157,    87,    87,    87,
      87,    87,    21,    22,    25,    26,    82,    90,    91,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
      79,    75,    85,    75,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,    76,   187,   187,   187,   187,   187,
     187,   187,   187,    76,    81,   187,    85,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,    79,   187,    47,   126,
     243,   187,   206,   207,   244,    47,   161,   161,     5,    87,
     156,    87,    87,   187,    31,   187,   162,   189,   190,   191,
     232,   244,   187,    86,    86,    87,   206,   206,   106,    75,
      75,    75,    75,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   206,   244,    76,    81,    76,
      76,    81,    76,    81,    76,    81,    76,    81,    76,    81,
      76,    81,    76,    81,    76,    76,    76,    76,    76,    76,
      76,    81,    76,   187,    80,   244,    86,    80,    80,    80,
      80,    80,    80,    80,    80,    76,    81,    75,    76,    75,
      76,    87,    34,    81,    76,    76,    76,   187,   187,   187,
     187,   187,    80,    76,    75,   187,   187,   187,   187,   187,
     187,   187,   187,   187,    81,    80,   187,   187,   206,   156,
     187,   156,   187,   188,   187,   244,   161,    87,    87,    87,
      76,    76,    81,    76,    81,    76,    81,    80,   206,    76,
      76,    76,    76,    76,    76,    76,    76,    76,   187,    75,
      89,    76,    29,    76,    87,    76,    34,    87,    87,   206,
     207,    87,   207,    87,   207,    75,    89,    76,    76,   206,
     244,   156,    87,   162,   156,   187,    76,    76,    76,   206,
     244,    76,    75,    76,    76,    87,    87,    87,    76,    75,
     206,   156,   156,   206,    76,    76
  };

  const unsigned char
  parser2::yyr1_[] =
  {
       0,   141,   142,   142,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   144,   145,   146,   147,
     148,   148,   148,   148,   148,   148,   149,   150,   151,   151,
     151,   151,   152,   153,   154,   154,   154,   154,   154,   155,
     155,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   157,   157,   158,   158,
     158,   158,   159,   159,   159,   159,   160,   160,   161,   161,
     162,   162,   162,   162,   163,   163,   164,   165,   165,   165,
     166,   167,   167,   168,   169,   170,   170,   171,   171,   172,
     173,   174,   175,   176,   177,   178,   178,   179,   180,   180,
     181,   182,   183,   184,   184,   185,   186,   187,   187,   187,
     188,   188,   189,   189,   190,   190,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   192,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   195,   196,   196,   196,   196,
     197,   198,   199,   199,   199,   200,   200,   200,   201,   201,
     201,   201,   202,   202,   203,   203,   204,   204,   204,   204,
     204,   205,   206,   206,   207,   207,   208,   209,   210,   210,
     211,   211,   212,   212,   213,   213,   214,   214,   215,   215,
     216,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   227,   228,   228,   228,   228,   228,   228,
     228,   228,   229,   230,   230,   231,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   244,
     245,   245,   246,   247,   248,   249,   250,   250,   251,   251,
     252,   253
  };

  const signed char
  parser2::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     3,     5,     6,     7,
       7,     7,     3,     6,     5,     5,     2,     2,     0,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     2,     1,     2,     1,     3,     2,     3,     2,
       1,     1,     1,     0,     2,     2,     5,     2,     2,     2,
       6,     8,     6,     3,     3,     8,     6,     8,     6,     2,
       5,     7,     5,     7,     9,     7,     9,     5,     3,     3,
       2,     2,     2,     3,     2,     5,     5,     1,     1,     1,
       1,     0,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     4,     1,     1,     1,     2,     2,     2,     4,     6,
       5,     7,     8,     9,    10,    11,     3,     3,     1,     1,
       0,     3,     1,     0,     3,     1,     6,     4,     4,     6,
       4,     6,     4,     6,     4,     6,     4,     6,     4,     6,
       4,     6,     4,     3,     4,     4,     4,     4,     4,     4,
       6,     4,     2,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     7,     1,     2,     1,     2,     1,
       1,     1
  };




#if ARC2DEBUG
  const short
  parser2::yyrline_[] =
  {
       0,   324,   324,   325,   329,   331,   333,   335,   337,   339,
     341,   343,   345,   347,   349,   351,   356,   360,   364,   369,
     374,   375,   376,   377,   378,   379,   383,   388,   393,   395,
     397,   399,   404,   409,   414,   416,   418,   420,   423,   427,
     430,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   462,   463,   467,   469,
     471,   473,   478,   480,   482,   484,   489,   490,   494,   495,
     499,   501,   503,   506,   510,   512,   517,   522,   524,   526,
     531,   536,   538,   543,   548,   553,   555,   560,   562,   567,
     572,   577,   582,   587,   592,   597,   603,   611,   618,   620,
     625,   630,   635,   640,   642,   647,   652,   657,   658,   659,
     663,   664,   668,   670,   675,   677,   682,   684,   686,   688,
     690,   692,   694,   696,   698,   700,   702,   707,   712,   714,
     716,   718,   720,   722,   724,   726,   728,   730,   732,   734,
     736,   738,   740,   742,   744,   746,   748,   750,   755,   756,
     757,   758,   759,   760,   761,   762,   763,   764,   765,   766,
     767,   768,   769,   770,   771,   772,   773,   774,   775,   776,
     777,   778,   779,   780,   781,   782,   783,   784,   785,   786,
     787,   788,   789,   790,   791,   792,   793,   794,   795,   796,
     797,   798,   799,   800,   801,   805,   810,   812,   814,   816,
     821,   826,   831,   832,   833,   837,   844,   851,   861,   863,
     865,   867,   872,   874,   879,   881,   886,   888,   890,   892,
     895,   899,   904,   907,   911,   913,   918,   923,   928,   930,
     935,   937,   942,   944,   949,   951,   956,   958,   963,   965,
     970,   972,   977,   982,   987,   992,   997,  1002,  1007,  1012,
    1017,  1022,  1027,  1029,  1034,  1036,  1038,  1040,  1042,  1044,
    1046,  1048,  1053,  1058,  1060,  1065,  1070,  1071,  1072,  1073,
    1074,  1075,  1076,  1077,  1078,  1079,  1080,  1084,  1089,  1094,
    1099,  1104,  1109,  1114,  1119,  1124,  1129,  1134,  1139,  1141,
    1146,  1148,  1153,  1158,  1163,  1168,  1173,  1175,  1180,  1182,
    1187,  1192
  };

  void
  parser2::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser2::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // ARC2DEBUG


#line 14 "parser2.ypp"
} } // xsk::arc
#line 6118 "parser2.cpp"

#line 1196 "parser2.ypp"


namespace xsk::arc
{

void parser2::error(location const& loc, std::string const& msg)
{
    throw comp_error(loc, msg);
}

auto parse_switch2(stmt_switch& stm) -> void
{
    auto body = stmt_list::make(stm.body->block->loc());
    auto curr = stmt::ptr{ nullptr };

    auto num = stm.body->block->list.size();

    for (auto i = 0u; i < num; i++)
    {
        auto& entry = stm.body->block->list[0];

        if (entry->is<stmt_case>() || entry->is<stmt_default>())
        {
            if (curr != nullptr)
            {
                body->list.push_back(std::move(curr));
            }

            curr = std::move(stm.body->block->list[0]);
            stm.body->block->list.erase(stm.body->block->list.begin());
        }
        else
        {
            if (curr != nullptr)
            {
                if (curr->is<stmt_case>())
                {
                    curr->as<stmt_case>().body->list.push_back(std::move(entry));
                    stm.body->block->list.erase(stm.body->block->list.begin());
                }
                else
                {
                    curr->as<stmt_default>().body->list.push_back(std::move(entry));
                    stm.body->block->list.erase(stm.body->block->list.begin());
                }
            }
            else
            {
                throw comp_error(entry->loc(), "missing case statement");
            }
        }
    }

    if (curr != nullptr)
    {
        body->list.push_back(std::move(curr));
    }

    stm.body->block = std::move(body);
}

extern std::unordered_map<token::kind, parser2::token::token_kind_type> const tok_to_parser2;
extern std::unordered_map<std::string_view, parser2::token::token_kind_type> const keyword_map2;

auto map_token2(context const* ctx_, token& tok) -> parser2::symbol_type
{
    if (tok.type == token::NAME)
    {
        tok.data = ctx_->make_token(tok.data);

        auto const it = keyword_map2.find(tok.data);

        if (it != keyword_map2.end())
        {
            return parser2::symbol_type(it->second, tok.pos);
        }

        return parser2::symbol_type(parser2::token::IDENTIFIER, std::move(tok.data), tok.pos);
    }
    else if (tok.type == token::PATH ||tok.type == token::HASHSTR ||tok.type == token::STRING ||tok.type == token::ISTRING || tok.type == token::INT ||tok.type == token::FLT)
    {
        auto it = tok_to_parser2.find(tok.type);

        if (it != tok_to_parser2.end())
        {
            return parser2::symbol_type(it->second, std::move(tok.data), tok.pos);
        }
    }
    else
    {
        auto it = tok_to_parser2.find(tok.type);

        if (it != tok_to_parser2.end())
        {
            return parser2::symbol_type(it->second, tok.pos);
        }
    }

    throw error(std::format("unmapped token! {}", (u8)tok.type));
}

auto ARC2lex(context const* ctx_, preprocessor& ppr) -> parser2::symbol_type
{
    auto tok = ppr.process();
    return map_token2(ctx_, tok);
}

std::unordered_map<token::kind, parser2::token::token_kind_type> const tok_to_parser2
{{
    { token::NAME, parser2::token::IDENTIFIER },
    { token::PATH, parser2::token::PATH },
    { token::STRING, parser2::token::STRING },
    { token::ISTRING, parser2::token::ISTRING },
    { token::HASHSTR, parser2::token::HASHSTR },
    { token::INT, parser2::token::INTEGER },
    { token::FLT, parser2::token::FLOAT },
    { token::PLUS, parser2::token::ADD },
    { token::MINUS, parser2::token::SUB },
    { token::STAR, parser2::token::MUL },
    { token::DIV, parser2::token::DIV },
    { token::MOD, parser2::token::MOD },
    { token::BITOR, parser2::token::BITWISE_OR },
    { token::BITAND, parser2::token::BITWISE_AND },
    { token::BITEXOR, parser2::token::BITWISE_EXOR },
    { token::ASSIGN, parser2::token::ASSIGN },
    { token::PLUSEQ, parser2::token::ASSIGN_ADD },
    { token::MINUSEQ, parser2::token::ASSIGN_SUB },
    { token::STAREQ, parser2::token::ASSIGN_MUL },
    { token::DIVEQ, parser2::token::ASSIGN_DIV },
    { token::MODEQ, parser2::token::ASSIGN_MOD },
    { token::BITOREQ, parser2::token::ASSIGN_BW_OR },
    { token::BITANDEQ, parser2::token::ASSIGN_BW_AND },
    { token::BITEXOREQ, parser2::token::ASSIGN_BW_EXOR },
    { token::SHLEQ, parser2::token::ASSIGN_LSHIFT },
    { token::SHREQ, parser2::token::ASSIGN_RSHIFT },
    { token::TILDE, parser2::token::COMPLEMENT },
    { token::BANG, parser2::token::NOT },
    { token::GT, parser2::token::GREATER },
    { token::LT, parser2::token::LESS },
    { token::GE, parser2::token::GREATER_EQUAL },
    { token::LE, parser2::token::LESS_EQUAL },
    { token::NE, parser2::token::INEQUALITY },
    { token::EQ, parser2::token::EQUALITY },
    { token::SNE, parser2::token::SUPER_NOTEQUAL },
    { token::SEQ, parser2::token::SUPER_EQUAL },
    { token::OR, parser2::token::OR },
    { token::AND, parser2::token::AND },
    { token::SHL, parser2::token::LSHIFT },
    { token::SHR, parser2::token::RSHIFT },
    { token::INC, parser2::token::INCREMENT },
    { token::DEC, parser2::token::DECREMENT },
    { token::ARROW, parser2::token::ARROW },
    { token::QMARK, parser2::token::QMARK },
    { token::DOT, parser2::token::DOT },
    { token::DOUBLEDOT, parser2::token::DOUBLEDOT },
    { token::ELLIPSIS, parser2::token::ELLIPSIS },
    { token::COMMA, parser2::token::COMMA },
    { token::COLON, parser2::token::COLON },
    { token::SEMICOLON, parser2::token::SEMICOLON },
    { token::DOUBLECOLON, parser2::token::DOUBLECOLON },
    { token::LBRACKET, parser2::token::LBRACKET },
    { token::RBRACKET, parser2::token::RBRACKET },
    { token::LBRACE, parser2::token::LBRACE },
    { token::RBRACE, parser2::token::RBRACE },
    { token::LPAREN, parser2::token::LPAREN },
    { token::RPAREN, parser2::token::RPAREN },
    { token::DEVBEGIN, parser2::token::DEVBEGIN },
    { token::DEVEND, parser2::token::DEVEND },
    { token::INLINE, parser2::token::INLINE },
    { token::INCLUDE, parser2::token::INCLUDE },
    { token::INSERT, parser2::token::INSERT },
    { token::USING, parser2::token::USING },
    { token::NAMESPACE, parser2::token::NAMESPACE },
    { token::USINGTREE, parser2::token::USINGTREE },
    { token::ANIMTREE, parser2::token::ANIMTREE },
    { token::VAR, parser2::token::VAR },
    { token::CLASS, parser2::token::CLASS },
    { token::CONSTRUCTOR, parser2::token::CONSTRUCTOR },
    { token::DESTRUCTOR, parser2::token::DESTRUCTOR },
    { token::FUNCTION, parser2::token::FUNCTION },
    { token::AUTOEXEC, parser2::token::AUTOEXEC },
    { token::CODECALL, parser2::token::CODECALL },
    { token::PRIVATE, parser2::token::PRIVATE },
    { token::ENDON, parser2::token::ENDON },
    { token::NOTIFY, parser2::token::NOTIFY },
    { token::WAIT, parser2::token::WAIT },
    { token::WAITREALTIME, parser2::token::WAITREALTIME },
    { token::WAITTILL, parser2::token::WAITTILL },
    { token::WAITTILLMATCH, parser2::token::WAITTILLMATCH },
    { token::WAITTILLFRAMEEND, parser2::token::WAITTILLFRAMEEND },
    { token::IF, parser2::token::IF },
    { token::ELSE, parser2::token::ELSE },
    { token::DO, parser2::token::DO },
    { token::WHILE, parser2::token::WHILE },
    { token::FOR, parser2::token::FOR },
    { token::FOREACH, parser2::token::FOREACH },
    { token::IN, parser2::token::IN },
    { token::SWITCH, parser2::token::SWITCH },
    { token::CASE, parser2::token::CASE },
    { token::DEFAULT, parser2::token::DEFAULT },
    { token::BREAK, parser2::token::BREAK },
    { token::CONTINUE, parser2::token::CONTINUE },
    { token::RETURN, parser2::token::RETURN },
    { token::PROFBEGIN, parser2::token::PROFBEGIN },
    { token::PROFEND, parser2::token::PROFEND },
    { token::THREAD, parser2::token::THREAD },
    { token::TRUE, parser2::token::TRUE },
    { token::FALSE, parser2::token::FALSE },
    { token::UNDEFINED, parser2::token::UNDEFINED },
    { token::SIZE, parser2::token::SIZE },
    { token::GAME, parser2::token::GAME },
    { token::SELF, parser2::token::SELF },
    { token::ANIM, parser2::token::ANIM },
    { token::LEVEL, parser2::token::LEVEL },
    { token::CONST, parser2::token::CONST },
    { token::WORLD, parser2::token::WORLD },
    { token::CLASSES, parser2::token::CLASSES },
    { token::NEW, parser2::token::NEW },
    { token::ISDEFINED, parser2::token::ISDEFINED },
    { token::VECTORSCALE, parser2::token::VECTORSCALE },
    { token::ANGLESTOUP, parser2::token::ANGLESTOUP },
    { token::ANGLESTORIGHT, parser2::token::ANGLESTORIGHT },
    { token::ANGLESTOFORWARD, parser2::token::ANGLESTOFORWARD },
    { token::ANGLECLAMP180, parser2::token::ANGLECLAMP180 },
    { token::VECTORTOANGLES, parser2::token::VECTORTOANGLES },
    { token::ABS, parser2::token::ABS },
    { token::GETTIME, parser2::token::GETTIME },
    { token::GETDVAR, parser2::token::GETDVAR },
    { token::GETDVARINT, parser2::token::GETDVARINT },
    { token::GETDVARFLOAT, parser2::token::GETDVARFLOAT },
    { token::GETDVARVECTOR, parser2::token::GETDVARVECTOR },
    { token::GETDVARCOLORRED, parser2::token::GETDVARCOLORRED },
    { token::GETDVARCOLORGREEN, parser2::token::GETDVARCOLORGREEN },
    { token::GETDVARCOLORBLUE, parser2::token::GETDVARCOLORBLUE },
    { token::GETDVARCOLORALPHA, parser2::token::GETDVARCOLORALPHA },
    { token::GETFIRSTARRAYKEY, parser2::token::GETFIRSTARRAYKEY },
    { token::GETNEXTARRAYKEY, parser2::token::GETNEXTARRAYKEY },
    { token::EOS, parser2::token::ARC2EOF },
    { token::HASH, parser2::token::HASH }
}};

std::unordered_map<std::string_view, parser2::token::token_kind_type> const keyword_map2
{{
    { "var", parser2::token::VAR },
    { "class", parser2::token::CLASS },
    { "constructor", parser2::token::CONSTRUCTOR },
    { "destructor", parser2::token::DESTRUCTOR },
    { "function", parser2::token::FUNCTION },
    { "autoexec", parser2::token::AUTOEXEC },
    { "codecall", parser2::token::CODECALL },
    { "private", parser2::token::PRIVATE },
    { "endon", parser2::token::ENDON },
    { "notify", parser2::token::NOTIFY },
    { "wait", parser2::token::WAIT },
    { "waitrealtime", parser2::token::WAITREALTIME},
    { "waittill", parser2::token::WAITTILL },
    { "waittillmatch", parser2::token::WAITTILLMATCH },
    { "waittillframeend", parser2::token::WAITTILLFRAMEEND },
    { "if", parser2::token::IF },
    { "else", parser2::token::ELSE },
    { "do", parser2::token::DO },
    { "while", parser2::token::WHILE },
    { "for", parser2::token::FOR },
    { "foreach", parser2::token::FOREACH },
    { "in", parser2::token::IN },
    { "switch", parser2::token::SWITCH },
    { "case", parser2::token::CASE },
    { "default", parser2::token::DEFAULT },
    { "break", parser2::token::BREAK },
    { "continue", parser2::token::CONTINUE },
    { "return", parser2::token::RETURN },
    { "prof_begin", parser2::token::PROFBEGIN },
    { "prof_end", parser2::token::PROFEND },
    { "thread", parser2::token::THREAD },
    { "true", parser2::token::TRUE },
    { "false", parser2::token::FALSE },
    { "undefined", parser2::token::UNDEFINED },
    { "size", parser2::token::SIZE },
    { "game", parser2::token::GAME },
    { "self", parser2::token::SELF },
    { "anim", parser2::token::ANIM },
    { "level", parser2::token::LEVEL },
    { "const", parser2::token::CONST },
    { "world", parser2::token::WORLD },
    { "classes", parser2::token::CLASSES },
    { "new", parser2::token::NEW },
    { "isdefined", parser2::token::ISDEFINED },
    { "vectorscale", parser2::token::VECTORSCALE },
    { "anglestoup", parser2::token::ANGLESTOUP },
    { "anglestoright", parser2::token::ANGLESTORIGHT },
    { "anglestoforward", parser2::token::ANGLESTOFORWARD },
    { "angleclamp180", parser2::token::ANGLECLAMP180 },
    { "vectortoangles", parser2::token::VECTORTOANGLES },
    { "abs", parser2::token::ABS },
    { "gettime", parser2::token::GETTIME },
    { "getdvar", parser2::token::GETDVAR },
    { "getdvarint", parser2::token::GETDVARINT },
    { "getdvarfloat", parser2::token::GETDVARFLOAT },
    { "getdvarvector", parser2::token::GETDVARVECTOR },
    { "getdvarcolorred", parser2::token::GETDVARCOLORRED },
    { "getdvarcolorgreen", parser2::token::GETDVARCOLORGREEN },
    { "getdvarcolorblue", parser2::token::GETDVARCOLORBLUE },
    { "getdvarcoloralpha", parser2::token::GETDVARCOLORALPHA },
    { "getfirstarraykey", parser2::token::GETFIRSTARRAYKEY },
    { "getnextarraykey", parser2::token::GETNEXTARRAYKEY },
}};

} // namespace xsk::arc
