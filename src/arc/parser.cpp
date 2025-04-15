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
#line 41 "parser.ypp"

#include "xsk/stdinc.hpp"
#include "xsk/arc/parser.hpp"
#include "xsk/arc/preprocessor.hpp"
using namespace xsk::arc;
namespace xsk::arc
{
    auto ARClex(context const* ctx_, preprocessor& ppr) -> parser::symbol_type;
    auto parse_switch(stmt_switch& stm) -> void;
}

#line 51 "parser.cpp"

// Take the name prefix into account.
#define yylex   ARClex


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
#if ARCDEBUG

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

#else // !ARCDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !ARCDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace arc {
#line 153 "parser.cpp"

  /// Build a parser object.
  parser::parser (xsk::arc::context const* ctx__yyarg, xsk::arc::preprocessor& ppr_yyarg, xsk::arc::program::ptr& ast_yyarg, std::uint32_t index_yyarg)
#if ARCDEBUG
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

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_pointer: // expr_pointer
        value.YY_MOVE_OR_COPY< call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< decl::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.YY_MOVE_OR_COPY< decl_function::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.YY_MOVE_OR_COPY< decl_usingtree::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_include: // include
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

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_pointer: // expr_pointer
        value.move< call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.move< decl_function::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.move< decl_usingtree::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_include: // include
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
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_pointer: // expr_pointer
        value.copy< call::ptr > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< decl::ptr > (that.value);
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.copy< decl_function::ptr > (that.value);
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.copy< decl_usingtree::ptr > (that.value);
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

      case symbol_kind::S_include: // include
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

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_pointer: // expr_pointer
        value.move< call::ptr > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl::ptr > (that.value);
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.move< decl_function::ptr > (that.value);
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.move< decl_usingtree::ptr > (that.value);
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

      case symbol_kind::S_include: // include
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
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if ARCDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if ARCDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // ARCDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    [[maybe_unused]] int yynerrs_ = 0;
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
        yylhs.value.emplace< call::ptr > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< decl::ptr > ();
        break;

      case symbol_kind::S_decl_function: // decl_function
        yylhs.value.emplace< decl_function::ptr > ();
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        yylhs.value.emplace< decl_usingtree::ptr > ();
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

      case symbol_kind::S_include: // include
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
  case 2: // root: program
#line 299 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program::ptr > ()); }
#line 2336 "parser.cpp"
    break;

  case 3: // root: %empty
#line 300 "parser.ypp"
              { ast = program::make(yylhs.location); }
#line 2342 "parser.cpp"
    break;

  case 4: // program: program ";"
#line 305 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2348 "parser.cpp"
    break;

  case 5: // program: program inline
#line 307 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2354 "parser.cpp"
    break;

  case 6: // program: program include
#line 309 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2360 "parser.cpp"
    break;

  case 7: // program: program declaration
#line 311 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2366 "parser.cpp"
    break;

  case 8: // program: ";"
#line 313 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2372 "parser.cpp"
    break;

  case 9: // program: inline
#line 315 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2378 "parser.cpp"
    break;

  case 10: // program: include
#line 317 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2384 "parser.cpp"
    break;

  case 11: // program: declaration
#line 319 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2390 "parser.cpp"
    break;

  case 12: // inline: "#inline" expr_path ";"
#line 323 "parser.ypp"
                                 { ppr.push_header(yylhs.location, yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2396 "parser.cpp"
    break;

  case 13: // include: "#include" expr_path ";"
#line 328 "parser.ypp"
        { yylhs.value.as < include::ptr > () = include::make(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2402 "parser.cpp"
    break;

  case 14: // declaration: "/#"
#line 332 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_begin::make(yylhs.location); }
#line 2408 "parser.cpp"
    break;

  case 15: // declaration: "#/"
#line 333 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_end::make(yylhs.location); }
#line 2414 "parser.cpp"
    break;

  case 16: // declaration: decl_usingtree
#line 334 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_usingtree::ptr > ()); }
#line 2420 "parser.cpp"
    break;

  case 17: // declaration: decl_function
#line 335 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_function::ptr > ()); }
#line 2426 "parser.cpp"
    break;

  case 18: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 340 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_usingtree::ptr > () = decl_usingtree::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 2432 "parser.cpp"
    break;

  case 19: // decl_function: expr_identifier "(" expr_parameters ")" stmt_comp
#line 345 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_none); }
#line 2438 "parser.cpp"
    break;

  case 20: // decl_function: "autoexec" expr_identifier "(" expr_parameters ")" stmt_comp
#line 347 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_autoexec); }
#line 2444 "parser.cpp"
    break;

  case 21: // decl_function: "codecall" expr_identifier "(" expr_parameters ")" stmt_comp
#line 349 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_codecall); }
#line 2450 "parser.cpp"
    break;

  case 22: // decl_function: "private" expr_identifier "(" expr_parameters ")" stmt_comp
#line 351 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_private2); }
#line 2456 "parser.cpp"
    break;

  case 23: // stmt: stmt_comp
#line 355 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_comp::ptr > ()); }
#line 2462 "parser.cpp"
    break;

  case 24: // stmt: stmt_call
#line 356 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2468 "parser.cpp"
    break;

  case 25: // stmt: stmt_const
#line 357 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2474 "parser.cpp"
    break;

  case 26: // stmt: stmt_assign
#line 358 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2480 "parser.cpp"
    break;

  case 27: // stmt: stmt_endon
#line 359 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_endon::ptr > ()); }
#line 2486 "parser.cpp"
    break;

  case 28: // stmt: stmt_notify
#line 360 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_notify::ptr > ()); }
#line 2492 "parser.cpp"
    break;

  case 29: // stmt: stmt_wait
#line 361 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_wait::ptr > ()); }
#line 2498 "parser.cpp"
    break;

  case 30: // stmt: stmt_waitrealtime
#line 362 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waitrealtime::ptr > ()); }
#line 2504 "parser.cpp"
    break;

  case 31: // stmt: stmt_waittill
#line 363 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittill::ptr > ()); }
#line 2510 "parser.cpp"
    break;

  case 32: // stmt: stmt_waittillmatch
#line 364 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillmatch::ptr > ()); }
#line 2516 "parser.cpp"
    break;

  case 33: // stmt: stmt_waittillframeend
#line 365 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillframeend::ptr > ()); }
#line 2522 "parser.cpp"
    break;

  case 34: // stmt: stmt_if
#line 366 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_if::ptr > ()); }
#line 2528 "parser.cpp"
    break;

  case 35: // stmt: stmt_ifelse
#line 367 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_ifelse::ptr > ()); }
#line 2534 "parser.cpp"
    break;

  case 36: // stmt: stmt_while
#line 368 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_while::ptr > ()); }
#line 2540 "parser.cpp"
    break;

  case 37: // stmt: stmt_dowhile
#line 369 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dowhile::ptr > ()); }
#line 2546 "parser.cpp"
    break;

  case 38: // stmt: stmt_for
#line 370 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_for::ptr > ()); }
#line 2552 "parser.cpp"
    break;

  case 39: // stmt: stmt_foreach
#line 371 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_foreach::ptr > ()); }
#line 2558 "parser.cpp"
    break;

  case 40: // stmt: stmt_switch
#line 372 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_switch::ptr > ()); }
#line 2564 "parser.cpp"
    break;

  case 41: // stmt: stmt_case
#line 373 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_case::ptr > ()); }
#line 2570 "parser.cpp"
    break;

  case 42: // stmt: stmt_default
#line 374 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_default::ptr > ()); }
#line 2576 "parser.cpp"
    break;

  case 43: // stmt: stmt_break
#line 375 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_break::ptr > ()); }
#line 2582 "parser.cpp"
    break;

  case 44: // stmt: stmt_continue
#line 376 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_continue::ptr > ()); }
#line 2588 "parser.cpp"
    break;

  case 45: // stmt: stmt_return
#line 377 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_return::ptr > ()); }
#line 2594 "parser.cpp"
    break;

  case 46: // stmt: stmt_prof_begin
#line 378 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_begin::ptr > ()); }
#line 2600 "parser.cpp"
    break;

  case 47: // stmt: stmt_prof_end
#line 379 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_end::ptr > ()); }
#line 2606 "parser.cpp"
    break;

  case 48: // stmt_or_dev: stmt
#line 383 "parser.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt::ptr > ()); }
#line 2612 "parser.cpp"
    break;

  case 49: // stmt_or_dev: stmt_dev
#line 384 "parser.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dev::ptr > ()); }
#line 2618 "parser.cpp"
    break;

  case 50: // stmt_list: stmt_list stmt
#line 389 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2624 "parser.cpp"
    break;

  case 51: // stmt_list: stmt
#line 391 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2630 "parser.cpp"
    break;

  case 52: // stmt_list: stmt_list ";"
#line 393 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2636 "parser.cpp"
    break;

  case 53: // stmt_list: ";"
#line 395 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2642 "parser.cpp"
    break;

  case 54: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 400 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2648 "parser.cpp"
    break;

  case 55: // stmt_or_dev_list: stmt_or_dev
#line 402 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2654 "parser.cpp"
    break;

  case 56: // stmt_or_dev_list: stmt_or_dev_list ";"
#line 404 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2660 "parser.cpp"
    break;

  case 57: // stmt_or_dev_list: ";"
#line 406 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2666 "parser.cpp"
    break;

  case 58: // stmt_dev: "/#" stmt_list "#/"
#line 410 "parser.ypp"
                                { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2672 "parser.cpp"
    break;

  case 59: // stmt_dev: "/#" "#/"
#line 411 "parser.ypp"
                      { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2678 "parser.cpp"
    break;

  case 60: // stmt_comp: "{" stmt_or_dev_list "}"
#line 415 "parser.ypp"
                                     { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2684 "parser.cpp"
    break;

  case 61: // stmt_comp: "{" "}"
#line 416 "parser.ypp"
                    { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2690 "parser.cpp"
    break;

  case 62: // stmt_expr: expr_assign
#line 421 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2696 "parser.cpp"
    break;

  case 63: // stmt_expr: expr_increment
#line 423 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2702 "parser.cpp"
    break;

  case 64: // stmt_expr: expr_decrement
#line 425 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2708 "parser.cpp"
    break;

  case 65: // stmt_expr: %empty
#line 427 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 2714 "parser.cpp"
    break;

  case 66: // stmt_call: expr_call ";"
#line 432 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_call::ptr > ())); }
#line 2720 "parser.cpp"
    break;

  case 67: // stmt_call: expr_method ";"
#line 434 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_method::ptr > ())); }
#line 2726 "parser.cpp"
    break;

  case 68: // stmt_const: "const" expr_identifier "=" expr ";"
#line 439 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, expr_const::make(yylhs.location, std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ()))); }
#line 2732 "parser.cpp"
    break;

  case 69: // stmt_assign: expr_assign ";"
#line 444 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2738 "parser.cpp"
    break;

  case 70: // stmt_assign: expr_increment ";"
#line 446 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2744 "parser.cpp"
    break;

  case 71: // stmt_assign: expr_decrement ";"
#line 448 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2750 "parser.cpp"
    break;

  case 72: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 453 "parser.ypp"
        { yylhs.value.as < stmt_endon::ptr > () = stmt_endon::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 2756 "parser.cpp"
    break;

  case 73: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 458 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2762 "parser.cpp"
    break;

  case 74: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 460 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2768 "parser.cpp"
    break;

  case 75: // stmt_wait: "wait" expr ";"
#line 465 "parser.ypp"
        { yylhs.value.as < stmt_wait::ptr > () = stmt_wait::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2774 "parser.cpp"
    break;

  case 76: // stmt_waitrealtime: "waitrealtime" expr ";"
#line 470 "parser.ypp"
        { yylhs.value.as < stmt_waitrealtime::ptr > () = stmt_waitrealtime::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2780 "parser.cpp"
    break;

  case 77: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 475 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2786 "parser.cpp"
    break;

  case 78: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 477 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2792 "parser.cpp"
    break;

  case 79: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 482 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2798 "parser.cpp"
    break;

  case 80: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 484 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2804 "parser.cpp"
    break;

  case 81: // stmt_waittillframeend: "waittillframeend" ";"
#line 489 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend::ptr > () = stmt_waittillframeend::make(yylhs.location); }
#line 2810 "parser.cpp"
    break;

  case 82: // stmt_if: "if" "(" expr ")" stmt
#line 494 "parser.ypp"
        { yylhs.value.as < stmt_if::ptr > () = stmt_if::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2816 "parser.cpp"
    break;

  case 83: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 499 "parser.ypp"
        { yylhs.value.as < stmt_ifelse::ptr > () = stmt_ifelse::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2822 "parser.cpp"
    break;

  case 84: // stmt_while: "while" "(" expr ")" stmt
#line 504 "parser.ypp"
        { yylhs.value.as < stmt_while::ptr > () = stmt_while::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2828 "parser.cpp"
    break;

  case 85: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 509 "parser.ypp"
        { yylhs.value.as < stmt_dowhile::ptr > () = stmt_dowhile::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[5].value.as < stmt::ptr > ())); }
#line 2834 "parser.cpp"
    break;

  case 86: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 514 "parser.ypp"
        { yylhs.value.as < stmt_for::ptr > () = stmt_for::make(yylhs.location, std::move(yystack_[6].value.as < stmt_expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt_expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2840 "parser.cpp"
    break;

  case 87: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 519 "parser.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, std::format("_a{}", ++index));
            auto key = expr_identifier::make(yylhs.location, std::format("_k{}", ++index));
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt::ptr > ()), false);
        }
#line 2850 "parser.cpp"
    break;

  case 88: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 525 "parser.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, std::format("_a{}", ++index));
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(array), std::move(yystack_[6].value.as < expr_identifier::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ()), true);
        }
#line 2859 "parser.cpp"
    break;

  case 89: // stmt_switch: "switch" "(" expr ")" stmt_comp
#line 533 "parser.ypp"
        { yylhs.value.as < stmt_switch::ptr > () = stmt_switch::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()));
          parse_switch(*yylhs.value.as < stmt_switch::ptr > ());
        }
#line 2867 "parser.cpp"
    break;

  case 90: // stmt_case: "case" expr_integer ":"
#line 540 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_integer::ptr > ()), stmt_list::make(yylhs.location)); }
#line 2873 "parser.cpp"
    break;

  case 91: // stmt_case: "case" expr_string ":"
#line 542 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_string::ptr > ()), stmt_list::make(yylhs.location)); }
#line 2879 "parser.cpp"
    break;

  case 92: // stmt_default: "default" ":"
#line 547 "parser.ypp"
        { yylhs.value.as < stmt_default::ptr > () = stmt_default::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2885 "parser.cpp"
    break;

  case 93: // stmt_break: "break" ";"
#line 552 "parser.ypp"
        { yylhs.value.as < stmt_break::ptr > () = stmt_break::make(yylhs.location); }
#line 2891 "parser.cpp"
    break;

  case 94: // stmt_continue: "continue" ";"
#line 557 "parser.ypp"
        { yylhs.value.as < stmt_continue::ptr > () = stmt_continue::make(yylhs.location); }
#line 2897 "parser.cpp"
    break;

  case 95: // stmt_return: "return" expr ";"
#line 562 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2903 "parser.cpp"
    break;

  case 96: // stmt_return: "return" ";"
#line 564 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 2909 "parser.cpp"
    break;

  case 97: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 569 "parser.ypp"
        { yylhs.value.as < stmt_prof_begin::ptr > () = stmt_prof_begin::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2915 "parser.cpp"
    break;

  case 98: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 574 "parser.ypp"
        { yylhs.value.as < stmt_prof_end::ptr > () = stmt_prof_end::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2921 "parser.cpp"
    break;

  case 99: // expr: expr_ternary
#line 578 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2927 "parser.cpp"
    break;

  case 100: // expr: expr_binary
#line 579 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2933 "parser.cpp"
    break;

  case 101: // expr: expr_primitive
#line 580 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2939 "parser.cpp"
    break;

  case 102: // expr_or_empty: expr
#line 584 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2945 "parser.cpp"
    break;

  case 103: // expr_or_empty: %empty
#line 585 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = expr_empty::make(yylhs.location); }
#line 2951 "parser.cpp"
    break;

  case 104: // expr_increment: "++" expr_object
#line 590 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 2957 "parser.cpp"
    break;

  case 105: // expr_increment: expr_object "++"
#line 592 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 2963 "parser.cpp"
    break;

  case 106: // expr_decrement: "--" expr_object
#line 597 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 2969 "parser.cpp"
    break;

  case 107: // expr_decrement: expr_object "--"
#line 599 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 2975 "parser.cpp"
    break;

  case 108: // expr_assign: expr_object "=" expr
#line 604 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 2981 "parser.cpp"
    break;

  case 109: // expr_assign: expr_object "|=" expr
#line 606 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwor); }
#line 2987 "parser.cpp"
    break;

  case 110: // expr_assign: expr_object "&=" expr
#line 608 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwand); }
#line 2993 "parser.cpp"
    break;

  case 111: // expr_assign: expr_object "^=" expr
#line 610 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwexor); }
#line 2999 "parser.cpp"
    break;

  case 112: // expr_assign: expr_object "<<=" expr
#line 612 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shl); }
#line 3005 "parser.cpp"
    break;

  case 113: // expr_assign: expr_object ">>=" expr
#line 614 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shr); }
#line 3011 "parser.cpp"
    break;

  case 114: // expr_assign: expr_object "+=" expr
#line 616 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::add); }
#line 3017 "parser.cpp"
    break;

  case 115: // expr_assign: expr_object "-=" expr
#line 618 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::sub); }
#line 3023 "parser.cpp"
    break;

  case 116: // expr_assign: expr_object "*=" expr
#line 620 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mul); }
#line 3029 "parser.cpp"
    break;

  case 117: // expr_assign: expr_object "/=" expr
#line 622 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::div); }
#line 3035 "parser.cpp"
    break;

  case 118: // expr_assign: expr_object "%=" expr
#line 624 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mod); }
#line 3041 "parser.cpp"
    break;

  case 119: // expr_ternary: expr "?" expr ":" expr
#line 629 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_ternary::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3047 "parser.cpp"
    break;

  case 120: // expr_binary: expr "||" expr
#line 634 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_or); }
#line 3053 "parser.cpp"
    break;

  case 121: // expr_binary: expr "&&" expr
#line 636 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_and); }
#line 3059 "parser.cpp"
    break;

  case 122: // expr_binary: expr "==" expr
#line 638 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::eq); }
#line 3065 "parser.cpp"
    break;

  case 123: // expr_binary: expr "!=" expr
#line 640 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ne); }
#line 3071 "parser.cpp"
    break;

  case 124: // expr_binary: expr "<=" expr
#line 642 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::le); }
#line 3077 "parser.cpp"
    break;

  case 125: // expr_binary: expr ">=" expr
#line 644 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ge); }
#line 3083 "parser.cpp"
    break;

  case 126: // expr_binary: expr "<" expr
#line 646 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::lt); }
#line 3089 "parser.cpp"
    break;

  case 127: // expr_binary: expr ">" expr
#line 648 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::gt); }
#line 3095 "parser.cpp"
    break;

  case 128: // expr_binary: expr "|" expr
#line 650 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwor); }
#line 3101 "parser.cpp"
    break;

  case 129: // expr_binary: expr "&" expr
#line 652 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwand); }
#line 3107 "parser.cpp"
    break;

  case 130: // expr_binary: expr "^" expr
#line 654 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwexor); }
#line 3113 "parser.cpp"
    break;

  case 131: // expr_binary: expr "<<" expr
#line 656 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shl); }
#line 3119 "parser.cpp"
    break;

  case 132: // expr_binary: expr ">>" expr
#line 658 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shr); }
#line 3125 "parser.cpp"
    break;

  case 133: // expr_binary: expr "+" expr
#line 660 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::add); }
#line 3131 "parser.cpp"
    break;

  case 134: // expr_binary: expr "-" expr
#line 662 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::sub); }
#line 3137 "parser.cpp"
    break;

  case 135: // expr_binary: expr "*" expr
#line 664 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mul); }
#line 3143 "parser.cpp"
    break;

  case 136: // expr_binary: expr "/" expr
#line 666 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::div); }
#line 3149 "parser.cpp"
    break;

  case 137: // expr_binary: expr "%" expr
#line 668 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mod); }
#line 3155 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_complement
#line 672 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_complement::ptr > ()); }
#line 3161 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_negate
#line 673 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_negate::ptr > ()); }
#line 3167 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_not
#line 674 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_not::ptr > ()); }
#line 3173 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_call
#line 675 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3179 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_method
#line 676 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3185 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_getnextarraykey
#line 677 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getnextarraykey::ptr > ()); }
#line 3191 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_getfirstarraykey
#line 678 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getfirstarraykey::ptr > ()); }
#line 3197 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_getdvarcoloralpha
#line 679 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcoloralpha::ptr > ()); }
#line 3203 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_getdvarcolorblue
#line 680 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorblue::ptr > ()); }
#line 3209 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_getdvarcolorgreen
#line 681 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorgreen::ptr > ()); }
#line 3215 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_getdvarcolorred
#line 682 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorred::ptr > ()); }
#line 3221 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_getdvarvector
#line 683 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarvector::ptr > ()); }
#line 3227 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_getdvarfloat
#line 684 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarfloat::ptr > ()); }
#line 3233 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_getdvarint
#line 685 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarint::ptr > ()); }
#line 3239 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_getdvar
#line 686 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvar::ptr > ()); }
#line 3245 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_gettime
#line 687 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_gettime::ptr > ()); }
#line 3251 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_abs
#line 688 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_abs::ptr > ()); }
#line 3257 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_vectortoangles
#line 689 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vectortoangles::ptr > ()); }
#line 3263 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_angleclamp180
#line 690 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_angleclamp180::ptr > ()); }
#line 3269 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_anglestoforward
#line 691 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoforward::ptr > ()); }
#line 3275 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_anglestoright
#line 692 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoright::ptr > ()); }
#line 3281 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_anglestoup
#line 693 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoup::ptr > ()); }
#line 3287 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_vectorscale
#line 694 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vectorscale::ptr > ()); }
#line 3293 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_isdefined
#line 695 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_isdefined::ptr > ()); }
#line 3299 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_reference
#line 696 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_reference::ptr > ()); }
#line 3305 "parser.cpp"
    break;

  case 163: // expr_primitive: expr_array
#line 697 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3311 "parser.cpp"
    break;

  case 164: // expr_primitive: expr_field
#line 698 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3317 "parser.cpp"
    break;

  case 165: // expr_primitive: expr_size
#line 699 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_size::ptr > ()); }
#line 3323 "parser.cpp"
    break;

  case 166: // expr_primitive: expr_paren
#line 700 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_paren::ptr > ()); }
#line 3329 "parser.cpp"
    break;

  case 167: // expr_primitive: expr_empty_array
#line 701 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_empty_array::ptr > ()); }
#line 3335 "parser.cpp"
    break;

  case 168: // expr_primitive: expr_undefined
#line 702 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_undefined::ptr > ()); }
#line 3341 "parser.cpp"
    break;

  case 169: // expr_primitive: expr_game
#line 703 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3347 "parser.cpp"
    break;

  case 170: // expr_primitive: expr_self
#line 704 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3353 "parser.cpp"
    break;

  case 171: // expr_primitive: expr_anim
#line 705 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3359 "parser.cpp"
    break;

  case 172: // expr_primitive: expr_level
#line 706 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3365 "parser.cpp"
    break;

  case 173: // expr_primitive: expr_animation
#line 707 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animation::ptr > ()); }
#line 3371 "parser.cpp"
    break;

  case 174: // expr_primitive: expr_animtree
#line 708 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animtree::ptr > ()); }
#line 3377 "parser.cpp"
    break;

  case 175: // expr_primitive: expr_identifier
#line 709 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3383 "parser.cpp"
    break;

  case 176: // expr_primitive: expr_istring
#line 710 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_istring::ptr > ()); }
#line 3389 "parser.cpp"
    break;

  case 177: // expr_primitive: expr_string
#line 711 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_string::ptr > ()); }
#line 3395 "parser.cpp"
    break;

  case 178: // expr_primitive: expr_vector
#line 712 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vector::ptr > ()); }
#line 3401 "parser.cpp"
    break;

  case 179: // expr_primitive: expr_hash
#line 713 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_hash::ptr > ()); }
#line 3407 "parser.cpp"
    break;

  case 180: // expr_primitive: expr_float
#line 714 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_float::ptr > ()); }
#line 3413 "parser.cpp"
    break;

  case 181: // expr_primitive: expr_integer
#line 715 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_integer::ptr > ()); }
#line 3419 "parser.cpp"
    break;

  case 182: // expr_primitive: expr_false
#line 716 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_false::ptr > ()); }
#line 3425 "parser.cpp"
    break;

  case 183: // expr_primitive: expr_true
#line 717 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_true::ptr > ()); }
#line 3431 "parser.cpp"
    break;

  case 184: // expr_complement: "~" expr
#line 722 "parser.ypp"
        { yylhs.value.as < expr_complement::ptr > () = expr_complement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3437 "parser.cpp"
    break;

  case 185: // expr_negate: "-" expr_identifier
#line 727 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3443 "parser.cpp"
    break;

  case 186: // expr_negate: "-" expr_paren
#line 729 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_paren::ptr > ())); }
#line 3449 "parser.cpp"
    break;

  case 187: // expr_negate: "-" expr_array
#line 731 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_array::ptr > ())); }
#line 3455 "parser.cpp"
    break;

  case 188: // expr_negate: "-" expr_field
#line 733 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_field::ptr > ())); }
#line 3461 "parser.cpp"
    break;

  case 189: // expr_not: "!" expr
#line 738 "parser.ypp"
        { yylhs.value.as < expr_not::ptr > () = expr_not::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3467 "parser.cpp"
    break;

  case 190: // expr_call: expr_function
#line 742 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3473 "parser.cpp"
    break;

  case 191: // expr_call: expr_pointer
#line 743 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3479 "parser.cpp"
    break;

  case 192: // expr_method: expr_object expr_function
#line 748 "parser.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3490 "parser.cpp"
    break;

  case 193: // expr_method: expr_object expr_pointer
#line 755 "parser.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3501 "parser.cpp"
    break;

  case 194: // expr_function: expr_identifier "(" expr_arguments ")"
#line 765 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3507 "parser.cpp"
    break;

  case 195: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 767 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3513 "parser.cpp"
    break;

  case 196: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 769 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3519 "parser.cpp"
    break;

  case 197: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 771 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3525 "parser.cpp"
    break;

  case 198: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 776 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3531 "parser.cpp"
    break;

  case 199: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 778 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3537 "parser.cpp"
    break;

  case 200: // expr_parameters: expr_parameters "," expr_parameters_default
#line 783 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3543 "parser.cpp"
    break;

  case 201: // expr_parameters: expr_parameters "," expr_identifier
#line 785 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3549 "parser.cpp"
    break;

  case 202: // expr_parameters: expr_parameters_default
#line 787 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3555 "parser.cpp"
    break;

  case 203: // expr_parameters: expr_identifier
#line 789 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3561 "parser.cpp"
    break;

  case 204: // expr_parameters: %empty
#line 791 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); }
#line 3567 "parser.cpp"
    break;

  case 205: // expr_parameters_default: expr_identifier "=" expr
#line 796 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr_identifier::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 3573 "parser.cpp"
    break;

  case 206: // expr_arguments: expr_arguments_no_empty
#line 801 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[0].value.as < expr_arguments::ptr > ()); }
#line 3579 "parser.cpp"
    break;

  case 207: // expr_arguments: %empty
#line 803 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); }
#line 3585 "parser.cpp"
    break;

  case 208: // expr_arguments_no_empty: expr_arguments "," expr
#line 808 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[2].value.as < expr_arguments::ptr > ()); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3591 "parser.cpp"
    break;

  case 209: // expr_arguments_no_empty: expr
#line 810 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3597 "parser.cpp"
    break;

  case 210: // expr_getnextarraykey: "getnextarraykey" "(" expr "," expr ")"
#line 815 "parser.ypp"
        { yylhs.value.as < expr_getnextarraykey::ptr > () = expr_getnextarraykey::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3603 "parser.cpp"
    break;

  case 211: // expr_getfirstarraykey: "getfirstarraykey" "(" expr ")"
#line 820 "parser.ypp"
        { yylhs.value.as < expr_getfirstarraykey::ptr > () = expr_getfirstarraykey::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3609 "parser.cpp"
    break;

  case 212: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr ")"
#line 825 "parser.ypp"
        { yylhs.value.as < expr_getdvarcoloralpha::ptr > () = expr_getdvarcoloralpha::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3615 "parser.cpp"
    break;

  case 213: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr ")"
#line 830 "parser.ypp"
        { yylhs.value.as < expr_getdvarcolorblue::ptr > () = expr_getdvarcolorblue::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3621 "parser.cpp"
    break;

  case 214: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr ")"
#line 835 "parser.ypp"
        { yylhs.value.as < expr_getdvarcolorgreen::ptr > () = expr_getdvarcolorgreen::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3627 "parser.cpp"
    break;

  case 215: // expr_getdvarcolorred: "getdvarcolorred" "(" expr ")"
#line 840 "parser.ypp"
        { yylhs.value.as < expr_getdvarcolorred::ptr > () = expr_getdvarcolorred::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3633 "parser.cpp"
    break;

  case 216: // expr_getdvarvector: "getdvarvector" "(" expr ")"
#line 845 "parser.ypp"
        { yylhs.value.as < expr_getdvarvector::ptr > () = expr_getdvarvector::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3639 "parser.cpp"
    break;

  case 217: // expr_getdvarfloat: "getdvarfloat" "(" expr ")"
#line 850 "parser.ypp"
        { yylhs.value.as < expr_getdvarfloat::ptr > () = expr_getdvarfloat::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3645 "parser.cpp"
    break;

  case 218: // expr_getdvarint: "getdvarint" "(" expr ")"
#line 855 "parser.ypp"
        { yylhs.value.as < expr_getdvarint::ptr > () = expr_getdvarint::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3651 "parser.cpp"
    break;

  case 219: // expr_getdvar: "getdvar" "(" expr ")"
#line 860 "parser.ypp"
        { yylhs.value.as < expr_getdvar::ptr > () = expr_getdvar::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3657 "parser.cpp"
    break;

  case 220: // expr_gettime: "gettime" "(" ")"
#line 865 "parser.ypp"
        { yylhs.value.as < expr_gettime::ptr > () = expr_gettime::make(yylhs.location); }
#line 3663 "parser.cpp"
    break;

  case 221: // expr_abs: "abs" "(" expr ")"
#line 870 "parser.ypp"
        { yylhs.value.as < expr_abs::ptr > () = expr_abs::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3669 "parser.cpp"
    break;

  case 222: // expr_vectortoangles: "vectortoangles" "(" expr ")"
#line 875 "parser.ypp"
        { yylhs.value.as < expr_vectortoangles::ptr > () = expr_vectortoangles::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3675 "parser.cpp"
    break;

  case 223: // expr_angleclamp180: "angleclamp180" "(" expr ")"
#line 880 "parser.ypp"
        { yylhs.value.as < expr_angleclamp180::ptr > () = expr_angleclamp180::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3681 "parser.cpp"
    break;

  case 224: // expr_anglestoforward: "anglestoforward" "(" expr ")"
#line 885 "parser.ypp"
        { yylhs.value.as < expr_anglestoforward::ptr > () = expr_anglestoforward::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3687 "parser.cpp"
    break;

  case 225: // expr_anglestoright: "anglestoright" "(" expr ")"
#line 890 "parser.ypp"
        { yylhs.value.as < expr_anglestoright::ptr > () = expr_anglestoright::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3693 "parser.cpp"
    break;

  case 226: // expr_anglestoup: "anglestoup" "(" expr ")"
#line 895 "parser.ypp"
        { yylhs.value.as < expr_anglestoup::ptr > () = expr_anglestoup::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3699 "parser.cpp"
    break;

  case 227: // expr_vectorscale: "vectorscale" "(" expr "," expr ")"
#line 900 "parser.ypp"
        { yylhs.value.as < expr_vectorscale::ptr > () = expr_vectorscale::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3705 "parser.cpp"
    break;

  case 228: // expr_isdefined: "isdefined" "(" expr ")"
#line 905 "parser.ypp"
        { yylhs.value.as < expr_isdefined::ptr > () = expr_isdefined::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3711 "parser.cpp"
    break;

  case 229: // expr_reference: "::" expr_identifier
#line 910 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3717 "parser.cpp"
    break;

  case 230: // expr_reference: expr_path "::" expr_identifier
#line 912 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, std::move(yystack_[2].value.as < expr_path::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3723 "parser.cpp"
    break;

  case 231: // expr_array: expr_object "[" expr "]"
#line 917 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3729 "parser.cpp"
    break;

  case 232: // expr_array: expr_getdvarvector "[" expr "]"
#line 919 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_getdvarvector::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3735 "parser.cpp"
    break;

  case 233: // expr_array: expr_vectortoangles "[" expr "]"
#line 921 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_vectortoangles::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3741 "parser.cpp"
    break;

  case 234: // expr_array: expr_angleclamp180 "[" expr "]"
#line 923 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_angleclamp180::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3747 "parser.cpp"
    break;

  case 235: // expr_array: expr_anglestoforward "[" expr "]"
#line 925 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoforward::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3753 "parser.cpp"
    break;

  case 236: // expr_array: expr_anglestoright "[" expr "]"
#line 927 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoright::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3759 "parser.cpp"
    break;

  case 237: // expr_array: expr_anglestoup "[" expr "]"
#line 929 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoup::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3765 "parser.cpp"
    break;

  case 238: // expr_array: expr_vectorscale "[" expr "]"
#line 931 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_vectorscale::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3771 "parser.cpp"
    break;

  case 239: // expr_field: expr_object "." expr_identifier_nosize
#line 936 "parser.ypp"
        { yylhs.value.as < expr_field::ptr > () = expr_field::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3777 "parser.cpp"
    break;

  case 240: // expr_size: expr_object "." "size"
#line 941 "parser.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 3783 "parser.cpp"
    break;

  case 241: // expr_size: expr_string "." "size"
#line 943 "parser.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 3789 "parser.cpp"
    break;

  case 242: // expr_paren: "(" expr ")"
#line 948 "parser.ypp"
        { yylhs.value.as < expr_paren::ptr > () = expr_paren::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3795 "parser.cpp"
    break;

  case 243: // expr_object: expr_call
#line 952 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3801 "parser.cpp"
    break;

  case 244: // expr_object: expr_method
#line 953 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3807 "parser.cpp"
    break;

  case 245: // expr_object: expr_array
#line 954 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3813 "parser.cpp"
    break;

  case 246: // expr_object: expr_field
#line 955 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3819 "parser.cpp"
    break;

  case 247: // expr_object: expr_game
#line 956 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3825 "parser.cpp"
    break;

  case 248: // expr_object: expr_self
#line 957 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3831 "parser.cpp"
    break;

  case 249: // expr_object: expr_anim
#line 958 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3837 "parser.cpp"
    break;

  case 250: // expr_object: expr_level
#line 959 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3843 "parser.cpp"
    break;

  case 251: // expr_object: expr_identifier
#line 960 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3849 "parser.cpp"
    break;

  case 252: // expr_empty_array: "[" "]"
#line 965 "parser.ypp"
        { yylhs.value.as < expr_empty_array::ptr > () = expr_empty_array::make(yylhs.location); }
#line 3855 "parser.cpp"
    break;

  case 253: // expr_undefined: "undefined"
#line 970 "parser.ypp"
        { yylhs.value.as < expr_undefined::ptr > () = expr_undefined::make(yylhs.location); }
#line 3861 "parser.cpp"
    break;

  case 254: // expr_game: "game"
#line 975 "parser.ypp"
        { yylhs.value.as < expr_game::ptr > () = expr_game::make(yylhs.location); }
#line 3867 "parser.cpp"
    break;

  case 255: // expr_self: "self"
#line 980 "parser.ypp"
        { yylhs.value.as < expr_self::ptr > () = expr_self::make(yylhs.location); }
#line 3873 "parser.cpp"
    break;

  case 256: // expr_anim: "anim"
#line 985 "parser.ypp"
        { yylhs.value.as < expr_anim::ptr > () = expr_anim::make(yylhs.location); }
#line 3879 "parser.cpp"
    break;

  case 257: // expr_level: "level"
#line 990 "parser.ypp"
        { yylhs.value.as < expr_level::ptr > () = expr_level::make(yylhs.location); }
#line 3885 "parser.cpp"
    break;

  case 258: // expr_animation: "%" "identifier"
#line 995 "parser.ypp"
        { yylhs.value.as < expr_animation::ptr > () = expr_animation::make(yylhs.location, "", yystack_[0].value.as < std::string > ()); }
#line 3891 "parser.cpp"
    break;

  case 259: // expr_animation: "%" "identifier" "::" "identifier"
#line 997 "parser.ypp"
        { yylhs.value.as < expr_animation::ptr > () = expr_animation::make(yylhs.location, yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::string > ()); }
#line 3897 "parser.cpp"
    break;

  case 260: // expr_animtree: "#animtree"
#line 1002 "parser.ypp"
        { yylhs.value.as < expr_animtree::ptr > () = expr_animtree::make(yylhs.location); }
#line 3903 "parser.cpp"
    break;

  case 261: // expr_identifier_nosize: "identifier"
#line 1007 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3909 "parser.cpp"
    break;

  case 262: // expr_identifier: "identifier"
#line 1012 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3915 "parser.cpp"
    break;

  case 263: // expr_identifier: "size"
#line 1014 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, "size"); }
#line 3921 "parser.cpp"
    break;

  case 264: // expr_path: "identifier"
#line 1019 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3927 "parser.cpp"
    break;

  case 265: // expr_path: "path"
#line 1021 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3933 "parser.cpp"
    break;

  case 266: // expr_istring: "localized string"
#line 1026 "parser.ypp"
        { yylhs.value.as < expr_istring::ptr > () = expr_istring::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3939 "parser.cpp"
    break;

  case 267: // expr_string: "string literal"
#line 1031 "parser.ypp"
        { yylhs.value.as < expr_string::ptr > () = expr_string::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3945 "parser.cpp"
    break;

  case 268: // expr_vector: "(" expr "," expr "," expr ")"
#line 1036 "parser.ypp"
        { yylhs.value.as < expr_vector::ptr > () = expr_vector::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3951 "parser.cpp"
    break;

  case 269: // expr_hash: "hash string"
#line 1041 "parser.ypp"
        { yylhs.value.as < expr_hash::ptr > () = expr_hash::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3957 "parser.cpp"
    break;

  case 270: // expr_float: "-" "float"
#line 1046 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3963 "parser.cpp"
    break;

  case 271: // expr_float: "float"
#line 1048 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3969 "parser.cpp"
    break;

  case 272: // expr_integer: "-" "integer"
#line 1053 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3975 "parser.cpp"
    break;

  case 273: // expr_integer: "integer"
#line 1055 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3981 "parser.cpp"
    break;

  case 274: // expr_false: "false"
#line 1060 "parser.ypp"
        { yylhs.value.as < expr_false::ptr > () = expr_false::make(yylhs.location); }
#line 3987 "parser.cpp"
    break;

  case 275: // expr_true: "true"
#line 1065 "parser.ypp"
        { yylhs.value.as < expr_true::ptr > () = expr_true::make(yylhs.location); }
#line 3993 "parser.cpp"
    break;


#line 3997 "parser.cpp"

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
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "#", "/#", "#/", "#inline",
  "#include", "#using_animtree", "#animtree", "autoexec", "codecall",
  "private", "endon", "notify", "wait", "waitrealtime", "waittill",
  "waittillmatch", "waittillframeend", "if", "else", "do", "while", "for",
  "foreach", "in", "switch", "case", "default", "break", "continue",
  "return", "prof_begin", "prof_end", "thread", "true", "false",
  "undefined", "size", "game", "self", "anim", "level", "const",
  "getnextarraykey", "getfirstarraykey", "getdvarcoloralpha",
  "getdvarcolorblue", "getdvarcolorgreen", "getdvarcolorred",
  "getdvarvector", "getdvarfloat", "getdvarint", "getdvar", "gettime",
  "abs", "vectortoangles", "angleclamp180", "anglestoforward",
  "anglestoright", "anglestoup", "vectorscale", "isdefined", "(", ")", "{",
  "}", "[", "]", ",", ".", "..", "...", "::", ":", ";", "?", "++", "--",
  "<<", ">>", "||", "&&", "==", "!=", "<=", ">=", "<", ">", "!", "~", "=",
  "+=", "-=", "*=", "/=", "%=", "|=", "&=", "^=", ">>=", "<<=", "|", "&",
  "^", "+", "-", "*", "/", "%", "path", "identifier", "string literal",
  "localized string", "hash string", "float", "integer", "SIZEOF", "THEN",
  "TERN", "NEG", "ANIMREF", "PREINC", "PREDEC", "POSTINC", "POSTDEC",
  "$accept", "root", "program", "inline", "include", "declaration",
  "decl_usingtree", "decl_function", "stmt", "stmt_or_dev", "stmt_list",
  "stmt_or_dev_list", "stmt_dev", "stmt_comp", "stmt_expr", "stmt_call",
  "stmt_const", "stmt_assign", "stmt_endon", "stmt_notify", "stmt_wait",
  "stmt_waitrealtime", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_if", "stmt_ifelse", "stmt_while",
  "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case",
  "stmt_default", "stmt_break", "stmt_continue", "stmt_return",
  "stmt_prof_begin", "stmt_prof_end", "expr", "expr_or_empty",
  "expr_increment", "expr_decrement", "expr_assign", "expr_ternary",
  "expr_binary", "expr_primitive", "expr_complement", "expr_negate",
  "expr_not", "expr_call", "expr_method", "expr_function", "expr_pointer",
  "expr_parameters", "expr_parameters_default", "expr_arguments",
  "expr_arguments_no_empty", "expr_getnextarraykey",
  "expr_getfirstarraykey", "expr_getdvarcoloralpha",
  "expr_getdvarcolorblue", "expr_getdvarcolorgreen",
  "expr_getdvarcolorred", "expr_getdvarvector", "expr_getdvarfloat",
  "expr_getdvarint", "expr_getdvar", "expr_gettime", "expr_abs",
  "expr_vectortoangles", "expr_angleclamp180", "expr_anglestoforward",
  "expr_anglestoright", "expr_anglestoup", "expr_vectorscale",
  "expr_isdefined", "expr_reference", "expr_array", "expr_field",
  "expr_size", "expr_paren", "expr_object", "expr_empty_array",
  "expr_undefined", "expr_game", "expr_self", "expr_anim", "expr_level",
  "expr_animation", "expr_animtree", "expr_identifier_nosize",
  "expr_identifier", "expr_path", "expr_istring", "expr_string",
  "expr_vector", "expr_hash", "expr_float", "expr_integer", "expr_false",
  "expr_true", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if ARCDEBUG
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
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if ARCDEBUG
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
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
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
#if ARCDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* event)
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
  parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  parser::yysyntax_error_ (const context& yyctx) const
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


  const short parser::yypact_ninf_ = -404;

  const short parser::yytable_ninf_ = -265;

  const short
  parser::yypact_[] =
  {
     164,  -404,  -404,    21,    21,   -62,   -22,   -22,   -22,  -404,
    -404,  -404,    20,   380,  -404,  -404,  -404,  -404,  -404,   -10,
    -404,  -404,   -45,   -31,   -57,     3,     7,    17,  -404,  -404,
    -404,  -404,  -404,   -22,  -404,  -404,  -404,    -2,   -22,   -22,
     -22,   -46,  -404,   -15,    19,   -42,   -36,   -19,    37,   -22,
    1399,  -404,    37,    37,    37,  1586,  -404,  -404,   -15,  -404,
     -24,  -404,  -404,  -404,  -404,  -404,  -404,  -404,    42,    52,
      60,    66,    73,    77,    82,    83,    88,    90,    93,    96,
     116,   118,   122,   124,   125,   127,   130,  1399,    43,   -22,
    1399,  1399,  1353,    23,   128,  -404,  -404,  -404,  -404,  3196,
    -404,  -404,  -404,  -404,  -404,  -404,    -3,     2,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,   131,  -404,  -404,  -404,
    -404,  -404,   133,   140,   144,   146,   150,   151,  -404,  -404,
      47,   174,  -404,  -404,   176,  -404,  -404,   186,   282,   335,
     363,  -404,  -404,     8,   152,  -404,   153,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  1716,  1399,  1399,   120,
     165,  1846,   171,   172,   175,   179,   -65,   163,   170,   177,
    1233,   187,   195,   -22,  -404,   194,  -404,  1153,  1153,  -404,
    -404,  1651,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,   188,   191,
     192,   193,   199,   131,   133,   140,   144,   146,   150,   151,
    -404,  -404,   793,  -404,  -404,  -404,  -404,   206,   189,   212,
     218,   209,  1399,  1399,  1399,  1399,  1399,  1399,  1399,  1399,
    1399,  1399,   185,  1399,  1399,  1399,  1399,  1399,  1399,  1399,
    1399,  1856,  1399,  -404,  -404,  -404,  -404,  1399,  -404,  -404,
    -404,  -404,    47,   174,  -404,   476,     8,   210,  1399,  1399,
    1399,  1399,  1399,  1399,  1399,  1399,  1399,  1399,  1399,  1399,
    1399,  1399,  1399,  1399,  1399,  1399,  1399,  1399,  1399,  1399,
    1399,  1399,  1399,  1399,  1482,   -21,  -404,  -404,   206,  1399,
     -22,   251,  -404,  -404,  -404,  1781,   986,  1395,  -404,  1399,
     268,  1399,  1089,   -22,  1399,   178,   221,   227,  -404,  -404,
    -404,  -404,  3148,  1399,  1399,   201,   476,   476,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,   242,   243,   245,   246,
     202,  -404,  -404,  1399,  1399,  1399,  1399,  1399,  1399,  1399,
    1399,  1399,  1399,  1399,   -22,  1399,  1399,   -22,  2995,  2007,
    2041,  2054,  2088,  2101,  2135,  2148,  2182,  2195,  -404,  2229,
    2242,  2276,  2289,  2323,  2336,  3036,  2370,  -404,  1399,   677,
    2383,   208,  3113,   314,   314,  3227,  1889,   547,   547,   622,
     622,   622,   622,  1143,   842,  1935,    41,    41,  -404,  -404,
    -404,  1478,  2660,  2702,  2744,  2786,  2828,  2870,  1316,  2912,
    -404,  -404,  -404,  3196,    -8,  -404,   258,  -404,  -404,  -404,
    -404,  -404,  -404,  2417,   259,  2430,   249,  -404,  -404,  -404,
     875,   -12,  2464,  -404,  -404,  -404,    -1,    13,  1399,  1399,
    1399,  1399,  1399,  3196,  3196,  3196,  3196,  3196,  3196,  3196,
    3196,  3196,  3196,  3196,   258,  2954,    15,   264,  1399,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  1399,  -404,  3077,   261,  -404,  1399,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  1399,
    1399,  1846,  1399,  1846,  1399,  1399,   -22,    37,   255,   260,
    3183,  2477,  1902,  1948,  1994,   266,  -404,  1399,  2511,  2524,
    1399,   273,  3196,  3196,    31,   318,  2558,  -404,  3196,   271,
    2571,   316,  -404,  -404,  -404,  -404,   272,   276,  1399,   279,
    1399,   288,  1399,   294,    32,  -404,  -404,  2605,  1399,  -404,
    1846,   290,  1089,  1846,  1399,  -404,  -404,   298,   304,  -404,
     306,  -404,   308,  1399,  -404,  -404,    34,  -404,  -404,   310,
    -404,  2618,   296,   303,   313,    40,  -404,  1846,  1846,  -404,
    -404,  -404,  -404,  -404,  -404
  };

  const short
  parser::yydefact_[] =
  {
       3,    14,    15,     0,     0,     0,     0,     0,     0,   263,
       8,   262,     0,     2,     9,    10,    11,    16,    17,     0,
     265,   264,     0,     0,     0,     0,     0,     0,     1,     4,
       5,     6,     7,   204,    12,    13,   267,     0,   204,   204,
     204,     0,   202,   203,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    19,   200,   201,   260,
       0,   275,   274,   253,   254,   255,   256,   257,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   262,   266,   269,   271,   273,   205,
      99,   100,   101,   138,   139,   140,   141,   142,   190,   191,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,     0,   167,   168,   169,   170,   171,
     172,   173,   174,   175,     0,   176,   177,   178,   179,   180,
     181,   182,   183,    20,    21,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,     0,    57,     0,     0,    48,
      55,     0,    49,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     0,     0,
       0,   243,   244,     0,     0,     0,     0,     0,     0,     0,
     245,   246,     0,   247,   248,   249,   250,   251,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   252,   229,   189,   184,     0,   270,   272,
     243,   244,   187,   188,   186,     0,   185,   258,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,   193,     0,   207,
       0,     0,    59,    53,    51,     0,     0,     0,    81,     0,
       0,     0,    65,     0,     0,     0,     0,     0,    92,    93,
      94,    96,     0,   207,   207,     0,   104,   106,    60,    56,
      54,    70,    71,    69,    66,    67,     0,     0,     0,     0,
       0,   105,   107,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   207,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   220,     0,
       0,     0,     0,     0,     0,     0,     0,   242,     0,     0,
       0,     0,     0,   131,   132,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   133,   134,   135,   136,
     137,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     240,   261,   239,   209,     0,   206,   230,   241,    58,    52,
      50,    75,    76,     0,     0,     0,     0,    63,    64,    62,
       0,     0,     0,    91,    90,    95,     0,     0,     0,     0,
       0,     0,     0,   108,   114,   115,   116,   117,   118,   109,
     110,   111,   113,   112,     0,     0,     0,     0,     0,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   221,   222,
     223,   224,   225,   226,     0,   228,     0,     0,   259,     0,
     232,   233,   234,   235,   236,   237,   238,   231,   194,     0,
     207,     0,     0,     0,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   196,   207,     0,     0,
       0,     0,   119,   208,     0,    82,     0,    84,   102,     0,
       0,     0,    89,    97,    98,    68,     0,     0,   207,     0,
     207,     0,   207,     0,     0,   210,   227,     0,   207,   195,
       0,     0,    65,     0,     0,    72,    74,     0,   206,    78,
     206,    80,   206,   207,   197,   268,     0,    83,    85,     0,
      87,     0,     0,     0,     0,     0,   198,     0,     0,    73,
      77,    79,   199,    86,    88
  };

  const short
  parser::yypgoto_[] =
  {
    -404,  -404,  -404,   367,   369,   382,  -404,  -404,  -126,   215,
    -404,  -404,  -404,   -27,  -145,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,
    -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,  -404,   767,
    -404,  -311,  -309,  -308,  -404,  -404,  -404,  -404,  -404,  -404,
     -39,   -33,  -129,  -122,   126,   351,  -249,  -403,  -404,  -404,
    -404,  -404,  -404,  -404,    29,  -404,  -404,  -404,  -404,  -404,
      39,    71,   100,   138,   168,   182,  -404,  -404,   200,   248,
    -404,   309,   307,  -404,  -404,   377,   422,   540,   595,  -404,
    -404,  -404,     0,     6,  -404,   -13,  -404,  -404,  -404,   241,
    -404,  -404
  };

  const short
  parser::yydefgoto_[] =
  {
       0,    12,    13,    14,    15,    16,    17,    18,   179,   180,
     305,   181,   182,   183,   426,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   413,
     519,   208,   209,   210,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,    41,    42,   547,   415,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   412,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152
  };

  const short
  parser::yytable_[] =
  {
      19,   427,    24,   428,   429,   296,    25,    26,    27,    22,
      23,    37,   297,    19,   495,     9,   211,     9,   410,    48,
      28,    56,   212,    52,    49,   153,   154,   155,    49,    53,
     304,    34,  -243,    43,    49,   310,  -243,  -244,    43,    43,
      43,  -244,   315,  -251,   229,    35,    54,  -251,    36,    58,
     414,    49,    98,   260,    33,   227,    36,   488,   496,   261,
     230,   228,   489,    44,   498,  -243,   231,    38,  -243,   489,
    -244,    39,   299,  -244,   436,   437,  -251,    50,   499,  -251,
     506,    40,  -245,   489,   213,   489,  -245,    20,    94,   254,
      11,   411,   266,   296,   214,    51,   539,   554,   228,   566,
     297,   489,   489,    55,   489,   572,   232,   456,  -243,  -243,
     489,   252,   253,  -244,  -244,  -245,   233,   211,  -245,  -251,
    -251,   213,   211,   212,   234,   548,   215,   550,   212,   552,
     235,   214,    20,    21,   298,   267,   296,   236,   260,   260,
     228,   237,   211,   297,   261,   261,   238,   239,   212,   284,
     285,   286,   240,   316,   241,   216,   227,   242,  -245,  -245,
     243,   227,   228,   215,    45,    46,    47,   228,     1,     2,
       3,     4,     5,   325,     6,     7,     8,   227,   227,   420,
     244,   227,   245,   228,   228,   213,   246,   228,   247,   248,
     213,   249,   216,   217,   250,   214,   308,   296,   296,   287,
     214,   288,  -264,     9,   297,   297,   213,   213,   289,  -246,
     213,    60,   290,  -246,   291,     9,   214,   214,   292,   293,
     214,  -247,   298,   218,   301,  -247,   300,   215,   228,   309,
     217,   427,   215,   428,   429,   311,   312,   219,   318,   313,
      10,   514,  -246,   314,   294,  -246,   319,   295,   215,   215,
     368,   323,   215,   320,  -247,   220,   216,  -247,   534,   324,
     218,   216,   252,   354,   331,   298,   211,   332,   333,   334,
     299,   228,   212,   260,   219,   335,    11,   216,   216,   261,
     355,   216,   356,   357,   381,  -246,  -246,    20,    94,   556,
     417,   424,   262,   438,   217,   259,   433,  -247,  -247,   217,
     416,   296,   434,   221,   565,   227,   439,   440,   297,   441,
     442,   228,   227,   431,   411,   217,   217,  -248,   228,   217,
     478,  -248,   490,   492,   218,   494,   298,   298,   507,   218,
     511,   523,   228,   228,   213,   533,   524,   538,   219,   540,
     263,   213,   544,   219,   214,   218,   218,   542,   545,   218,
    -248,   214,   546,  -248,   454,   549,   220,   457,   553,   219,
     219,   220,   222,   219,   551,   515,   558,   517,   489,   562,
    -249,   563,   569,   564,  -249,   567,   215,   220,   220,   570,
      30,   220,    31,   215,     1,     2,     3,     4,     5,   571,
       6,     7,     8,  -248,  -248,    32,   330,   559,  -250,   265,
      57,   264,  -250,  -249,   221,   216,  -249,   317,     0,   221,
       0,     0,   216,     0,   557,     0,     0,   560,     0,     9,
     282,   283,   284,   285,   286,   221,   221,     0,     0,   221,
     298,  -250,   223,     0,  -250,     0,   228,     0,     0,     0,
       0,   573,   574,   217,     0,     0,  -249,  -249,     0,     0,
     217,     0,   211,     0,   211,     0,    29,     0,   212,     0,
     212,     0,     0,   222,     0,     0,     0,     0,   222,   223,
     522,     0,     0,   218,  -250,  -250,     0,   224,     0,     0,
     218,     0,     0,     0,   326,   327,     0,   219,   222,     0,
       0,   227,    11,   227,   219,     0,   521,   228,     0,   228,
       0,   211,     0,   260,   211,   220,     0,   212,     0,   261,
     212,    60,   220,     0,   224,     9,     0,     0,     0,     0,
     213,     0,   213,     0,     0,     0,     0,     0,   211,   211,
     214,     0,   214,   223,   212,   212,     0,     0,   223,     0,
     227,     0,   227,   227,   294,     0,   228,   340,   228,   228,
       0,     0,     0,   221,   223,   223,     0,     0,   223,     0,
     221,     0,   215,     0,   215,     0,     0,   227,   227,   213,
       0,   213,   213,   228,   228,     0,     0,     0,   224,   214,
       0,   214,   214,   224,     0,     0,     0,    20,    94,     0,
       0,   216,     0,   216,     0,   225,   213,   213,     0,   224,
     224,     0,     0,   224,     0,     0,   214,   214,     0,     0,
       0,   215,   222,   215,   215,     0,     0,     0,     0,   430,
       0,     0,     0,     0,     0,     0,     0,   269,   270,   217,
       0,   217,   225,   275,   276,   277,   278,     0,   215,   215,
     216,     0,   216,   216,     0,     0,     0,     0,     0,     0,
     226,     0,     0,   282,   283,   284,   285,   286,     0,   218,
       0,   218,     0,     0,     0,     0,     0,   216,   216,     0,
       0,     0,     0,   219,     0,   219,     0,     0,   217,     0,
     217,   217,   223,     0,     0,     0,     0,   226,     0,   223,
       0,   220,     0,   220,     0,     0,   225,     0,     0,     0,
       0,   225,   269,   270,     0,   217,   217,     0,   218,     0,
     218,   218,     0,     0,     0,     0,     0,   225,   225,     0,
       0,   225,   219,     0,   219,   219,     0,   224,   282,   283,
     284,   285,   286,     0,   224,   218,   218,     0,     0,   221,
     220,   221,   220,   220,     0,     0,   477,     0,     0,   219,
     219,   226,     0,     0,   268,     0,   226,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   220,   220,     0,
       0,     0,   226,   226,     0,     0,   226,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   221,     0,
     221,   221,     0,     0,     0,     0,     0,     0,   222,     0,
     222,     0,     0,     0,     0,     0,   336,   337,     0,     0,
     338,   339,     0,     0,     0,   221,   221,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,     0,
       0,     0,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   225,     0,   222,     0,   430,
     222,     0,   225,     0,   251,     0,     0,   255,   256,     0,
       0,   294,     0,     0,   340,     0,     0,     0,   223,     0,
     223,   341,   342,     0,   222,   222,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,     0,     0,     0,     0,
     226,     0,     0,     0,    20,    94,     0,   226,     0,     0,
      60,     0,     0,   224,     9,   224,     0,   223,     0,   223,
     223,     0,   269,   270,   306,   307,   273,   274,   275,   276,
     277,   278,     0,     0,     0,     0,     0,   322,     0,     0,
       0,     0,     0,   294,   223,   223,   340,     0,   282,   283,
     284,   285,   286,   341,   342,     0,     0,     0,     0,     0,
       0,     0,   224,     0,   224,   224,     0,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,     0,     0,
       0,     0,     0,     0,     0,     0,    20,    94,     0,   224,
     224,     0,     0,     0,     0,     0,     0,     0,     0,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,     0,
     369,   370,   371,   372,   373,   374,   375,   376,     0,   379,
       0,     0,     0,     0,   380,     0,     0,     0,     0,     0,
       0,   225,     0,   225,     0,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   409,   421,   268,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   423,     0,   425,     0,
     225,   432,   225,   225,     0,     0,   226,     0,   226,   279,
     280,   281,   282,   283,   284,   285,   286,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   225,   225,     0,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,     0,   455,     0,    60,     0,     0,     0,     9,    64,
      65,    66,    67,     0,     0,   226,     0,   226,   226,     0,
      74,     0,     0,     0,     0,   476,    80,    81,    82,    83,
      84,    85,     0,     0,     0,     0,     0,   175,     0,     0,
       0,     0,   226,   226,     0,     0,     0,   177,   178,     0,
       0,     0,     0,     0,     0,   379,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,     0,
       0,     0,     9,    64,    65,    66,    67,     0,     0,     0,
      20,    94,     0,     0,    74,   500,   501,   502,   503,   504,
      80,    81,    82,    83,    84,    85,     0,     0,     0,     0,
       0,   175,     0,   269,   270,   508,     0,   273,   274,   275,
     276,   277,   278,     0,     0,     0,     0,     0,     0,     0,
       0,   509,    59,     0,     0,     0,   512,   280,   281,   282,
     283,   284,   285,   286,     0,     0,   513,     0,     0,   516,
       0,   518,   520,     0,    20,    94,     0,     0,    60,    61,
      62,    63,     9,    64,    65,    66,    67,   537,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,     0,     0,
       0,    88,     0,     0,     0,     0,     0,    89,     0,   321,
       0,   561,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92,     0,     0,    93,    20,    94,    36,    95,    96,    97,
      98,    60,    61,    62,    63,     9,    64,    65,    66,    67,
       0,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     0,     0,     0,   408,   253,     0,     0,    60,     0,
      89,     0,     9,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,     0,    74,     0,    90,    91,    59,     0,
      80,    81,    82,    83,    84,    85,     0,   257,     0,     0,
       0,   175,     0,    92,     0,     0,    93,    20,    94,    36,
      95,    96,    97,    98,    60,    61,    62,    63,     9,    64,
      65,    66,    67,     0,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    20,    94,     0,    88,     0,   258,
     259,   422,   268,    89,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,     0,     0,     0,     0,    90,
      91,    59,     0,     0,     0,     0,     0,     0,   279,   280,
     281,   282,   283,   284,   285,   286,    92,     0,     0,    93,
      20,    94,    36,    95,    96,    97,    98,    60,    61,    62,
      63,     9,    64,    65,    66,    67,     0,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,   480,     0,     0,
     408,     0,     0,     0,     0,   268,    89,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,     0,     0,
       0,     0,    90,    91,     0,     0,     0,     0,     0,     0,
       0,   279,   280,   281,   282,   283,   284,   285,   286,    92,
     156,     0,    93,    20,    94,    36,    95,    96,    97,    98,
       0,   157,   158,     0,     0,   159,   160,     0,   161,   162,
     163,   164,     0,   165,   166,   167,   168,   169,   170,   171,
     172,    60,     0,     0,     0,     9,    64,    65,    66,    67,
     173,     0,     0,     0,     0,     0,     0,    74,     0,     0,
       0,     0,     0,    80,    81,    82,    83,    84,    85,     0,
       0,     0,    55,   174,   175,   156,     0,     0,     0,     0,
       0,     0,   176,     0,   177,   178,   157,   158,     0,     0,
     159,   160,     0,   161,   162,   163,   164,     0,   165,   166,
     167,   168,   169,   170,   171,   172,    60,     0,     0,     0,
       9,    64,    65,    66,    67,   173,     0,    20,    94,     0,
       0,     0,    74,     0,     0,     0,     0,     0,    80,    81,
      82,    83,    84,    85,     0,     0,     0,    55,   328,   175,
       0,   302,     0,     0,     0,     0,     0,   329,     0,   177,
     178,   157,   158,     0,     0,   159,   160,     0,   161,   162,
     163,   164,     0,   165,   166,   167,   168,   169,   170,   171,
     172,    60,     0,     0,     0,     9,    64,    65,    66,    67,
     173,     0,    20,    94,     0,     0,     0,    74,     0,     0,
       0,     0,     0,    80,    81,    82,    83,    84,    85,     0,
       0,     0,    55,     0,   175,     0,   418,     0,     0,     0,
       0,     0,   303,     0,   177,   178,   157,   158,     0,     0,
     159,   160,     0,   161,   162,   163,   164,     0,   165,   166,
     167,   168,   169,   170,   171,   172,    60,     0,     0,     0,
       9,    64,    65,    66,    67,   173,     0,    20,    94,     0,
       0,     0,    74,     0,     0,     0,     0,     0,    80,    81,
      82,    83,    84,    85,     0,     0,     0,    55,     0,   175,
       0,     0,     0,     0,     0,     0,     0,   419,     0,   177,
     178,   157,   158,     0,     0,   159,   160,     0,   161,   162,
     163,   164,     0,   165,   166,   167,   168,   169,   170,   171,
     172,    60,     0,     0,     0,     9,    64,    65,    66,    67,
     173,     0,    20,    94,     0,     0,     0,    74,     0,     0,
       0,     0,     0,    80,    81,    82,    83,    84,    85,     0,
       0,     0,    55,     0,   175,     0,     0,     0,     0,     0,
       0,   377,     0,     0,   177,   178,   378,     0,     0,     0,
       0,     0,     0,   268,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    94,   279,
     280,   281,   282,   283,   284,   285,   286,   527,     0,   269,
     270,     0,   528,   273,   274,   275,   276,   277,   278,   268,
       0,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
       0,     0,     0,     0,     0,   279,   280,   281,   282,   283,
     284,   285,   286,   529,     0,   269,   270,     0,   530,   273,
     274,   275,   276,   277,   278,   268,     0,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,     0,   280,
       0,   282,   283,   284,   285,   286,     0,     0,     0,     0,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   531,
       0,     0,     0,     0,   532,     0,     0,     0,     0,     0,
       0,   268,   459,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   268,     0,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,     0,   460,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   268,   461,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   268,     0,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,     0,   462,     0,     0,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   268,   463,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   268,     0,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,     0,
     464,     0,     0,     0,   279,   280,   281,   282,   283,   284,
     285,   286,   268,   465,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   268,     0,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,     0,   466,     0,     0,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   268,
     467,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   268,     0,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,     0,   468,     0,     0,     0,   279,   280,
     281,   282,   283,   284,   285,   286,   268,   469,     0,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   268,
       0,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
       0,   470,     0,     0,     0,   279,   280,   281,   282,   283,
     284,   285,   286,   268,   471,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   268,     0,     0,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,     0,   472,     0,
       0,     0,   279,   280,   281,   282,   283,   284,   285,   286,
     268,   473,     0,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   268,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,     0,   475,     0,     0,     0,   279,
     280,   281,   282,   283,   284,   285,   286,   268,   377,     0,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     268,     0,     0,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,     0,   491,     0,     0,     0,   279,   280,   281,   282,
     283,   284,   285,   286,   268,   493,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   268,     0,     0,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,     0,   497,
       0,     0,     0,   279,   280,   281,   282,   283,   284,   285,
     286,   268,   526,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   268,     0,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,     0,   535,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   268,   536,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   268,     0,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,     0,   541,     0,     0,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   268,   543,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   268,     0,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,     0,
     555,     0,     0,     0,   279,   280,   281,   282,   283,   284,
     285,   286,   268,   568,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   268,     0,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,     0,     0,     0,     0,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   481,
       0,     0,     0,     0,     0,     0,     0,   268,     0,     0,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   279,   280,   281,   282,   283,   284,   285,
     286,   482,     0,     0,     0,     0,     0,     0,     0,   268,
       0,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   279,   280,   281,   282,   283,
     284,   285,   286,   483,     0,     0,     0,     0,     0,     0,
       0,   268,     0,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   484,     0,     0,     0,     0,
       0,     0,     0,   268,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   279,
     280,   281,   282,   283,   284,   285,   286,   485,     0,     0,
       0,     0,     0,     0,     0,   268,     0,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   486,
       0,     0,     0,     0,     0,     0,     0,   268,     0,     0,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   279,   280,   281,   282,   283,   284,   285,
     286,   487,     0,     0,     0,     0,     0,     0,     0,   268,
       0,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   279,   280,   281,   282,   283,
     284,   285,   286,   505,     0,     0,     0,     0,     0,     0,
       0,   268,     0,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   458,     0,     0,     0,     0,
       0,     0,   268,     0,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   279,   280,
     281,   282,   283,   284,   285,   286,   474,     0,     0,     0,
       0,     0,     0,   268,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   279,
     280,   281,   282,   283,   284,   285,   286,   510,     0,     0,
       0,     0,     0,     0,   268,     0,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   479,     0,
     268,     0,     0,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   279,   280,   281,   282,
     283,   284,   285,   286,   435,   268,     0,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   525,
     268,     0,     0,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   268,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,     0,     0,     0,     0,     0,   279,
     280,   281,   282,   283,   284,   285,   286,   269,   270,     0,
     272,   273,   274,   275,   276,   277,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286
  };

  const short
  parser::yycheck_[] =
  {
       0,   312,    64,   312,   312,   134,     6,     7,     8,     3,
       4,    24,   134,    13,    26,    39,    55,    39,    39,    65,
       0,    48,    55,    65,    70,    52,    53,    54,    70,    65,
     156,    76,    35,    33,    70,   161,    39,    35,    38,    39,
      40,    39,   107,    35,    68,    76,    65,    39,   113,    49,
     299,    70,   117,    92,    64,    55,   113,    65,    70,    92,
      60,    55,    70,    65,    65,    68,    60,    64,    71,    70,
      68,    64,    64,    71,   323,   324,    68,    92,    65,    71,
      65,    64,    35,    70,    55,    70,    39,   111,   112,    89,
     112,   112,    92,   222,    55,    76,    65,    65,    92,    65,
     222,    70,    70,    66,    70,    65,    64,   356,   111,   112,
      70,    68,    69,   111,   112,    68,    64,   156,    71,   111,
     112,    92,   161,   156,    64,   528,    55,   530,   161,   532,
      64,    92,   111,   112,   134,   112,   265,    64,   177,   178,
     134,    64,   181,   265,   177,   178,    64,    64,   181,   108,
     109,   110,    64,   166,    64,    55,   156,    64,   111,   112,
      64,   161,   156,    92,    38,    39,    40,   161,     4,     5,
       6,     7,     8,   173,    10,    11,    12,   177,   178,   305,
      64,   181,    64,   177,   178,   156,    64,   181,    64,    64,
     161,    64,    92,    55,    64,   156,    76,   326,   327,    68,
     161,    68,    74,    39,   326,   327,   177,   178,    68,    35,
     181,    35,    68,    39,    68,    39,   177,   178,    68,    68,
     181,    35,   222,    55,    71,    39,    74,   156,   222,    64,
      92,   542,   161,   542,   542,    64,    64,    55,    75,    64,
      76,   490,    68,    64,    68,    71,    76,    71,   177,   178,
      65,    64,   181,    76,    68,    55,   156,    71,   507,    64,
      92,   161,    68,    74,    76,   265,   305,    76,    76,    76,
      64,   265,   305,   312,    92,    76,   112,   177,   178,   312,
      68,   181,    64,    74,    74,   111,   112,   111,   112,   538,
      39,    23,    92,    92,   156,   117,    75,   111,   112,   161,
     300,   430,    75,    55,   553,   305,    64,    64,   430,    64,
      64,   305,   312,   313,   112,   177,   178,    35,   312,   181,
     112,    39,    64,    64,   156,    76,   326,   327,    64,   161,
      69,    76,   326,   327,   305,    69,    76,    64,   156,    21,
      92,   312,    26,   161,   305,   177,   178,    76,    76,   181,
      68,   312,    76,    71,   354,    76,   156,   357,    64,   177,
     178,   161,    55,   181,    76,   491,    76,   493,    70,    65,
      35,    65,    76,    65,    39,    65,   305,   177,   178,    76,
      13,   181,    13,   312,     4,     5,     6,     7,     8,    76,
      10,    11,    12,   111,   112,    13,   181,   542,    35,    92,
      49,    92,    39,    68,   156,   305,    71,   166,    -1,   161,
      -1,    -1,   312,    -1,   540,    -1,    -1,   543,    -1,    39,
     106,   107,   108,   109,   110,   177,   178,    -1,    -1,   181,
     430,    68,    55,    -1,    71,    -1,   430,    -1,    -1,    -1,
      -1,   567,   568,   305,    -1,    -1,   111,   112,    -1,    -1,
     312,    -1,   491,    -1,   493,    -1,    76,    -1,   491,    -1,
     493,    -1,    -1,   156,    -1,    -1,    -1,    -1,   161,    92,
     497,    -1,    -1,   305,   111,   112,    -1,    55,    -1,    -1,
     312,    -1,    -1,    -1,   177,   178,    -1,   305,   181,    -1,
      -1,   491,   112,   493,   312,    -1,   496,   491,    -1,   493,
      -1,   540,    -1,   542,   543,   305,    -1,   540,    -1,   542,
     543,    35,   312,    -1,    92,    39,    -1,    -1,    -1,    -1,
     491,    -1,   493,    -1,    -1,    -1,    -1,    -1,   567,   568,
     491,    -1,   493,   156,   567,   568,    -1,    -1,   161,    -1,
     540,    -1,   542,   543,    68,    -1,   540,    71,   542,   543,
      -1,    -1,    -1,   305,   177,   178,    -1,    -1,   181,    -1,
     312,    -1,   491,    -1,   493,    -1,    -1,   567,   568,   540,
      -1,   542,   543,   567,   568,    -1,    -1,    -1,   156,   540,
      -1,   542,   543,   161,    -1,    -1,    -1,   111,   112,    -1,
      -1,   491,    -1,   493,    -1,    55,   567,   568,    -1,   177,
     178,    -1,    -1,   181,    -1,    -1,   567,   568,    -1,    -1,
      -1,   540,   305,   542,   543,    -1,    -1,    -1,    -1,   312,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,   491,
      -1,   493,    92,    86,    87,    88,    89,    -1,   567,   568,
     540,    -1,   542,   543,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    -1,   106,   107,   108,   109,   110,    -1,   491,
      -1,   493,    -1,    -1,    -1,    -1,    -1,   567,   568,    -1,
      -1,    -1,    -1,   491,    -1,   493,    -1,    -1,   540,    -1,
     542,   543,   305,    -1,    -1,    -1,    -1,    92,    -1,   312,
      -1,   491,    -1,   493,    -1,    -1,   156,    -1,    -1,    -1,
      -1,   161,    80,    81,    -1,   567,   568,    -1,   540,    -1,
     542,   543,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,
      -1,   181,   540,    -1,   542,   543,    -1,   305,   106,   107,
     108,   109,   110,    -1,   312,   567,   568,    -1,    -1,   491,
     540,   493,   542,   543,    -1,    -1,    69,    -1,    -1,   567,
     568,   156,    -1,    -1,    77,    -1,   161,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   567,   568,    -1,
      -1,    -1,   177,   178,    -1,    -1,   181,    -1,    -1,    -1,
     103,   104,   105,   106,   107,   108,   109,   110,   540,    -1,
     542,   543,    -1,    -1,    -1,    -1,    -1,    -1,   491,    -1,
     493,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,
      17,    18,    -1,    -1,    -1,   567,   568,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   305,    -1,   540,    -1,   542,
     543,    -1,   312,    -1,    87,    -1,    -1,    90,    91,    -1,
      -1,    68,    -1,    -1,    71,    -1,    -1,    -1,   491,    -1,
     493,    78,    79,    -1,   567,   568,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,    -1,    -1,    -1,    -1,
     305,    -1,    -1,    -1,   111,   112,    -1,   312,    -1,    -1,
      35,    -1,    -1,   491,    39,   493,    -1,   540,    -1,   542,
     543,    -1,    80,    81,   157,   158,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,   170,    -1,    -1,
      -1,    -1,    -1,    68,   567,   568,    71,    -1,   106,   107,
     108,   109,   110,    78,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   540,    -1,   542,   543,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   111,   112,    -1,   567,
     568,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,    -1,
     243,   244,   245,   246,   247,   248,   249,   250,    -1,   252,
      -1,    -1,    -1,    -1,   257,    -1,    -1,    -1,    -1,    -1,
      -1,   491,    -1,   493,    -1,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,    76,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   309,    -1,   311,    -1,
     540,   314,   542,   543,    -1,    -1,   491,    -1,   493,   103,
     104,   105,   106,   107,   108,   109,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   567,   568,    -1,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,    -1,   355,    -1,    35,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    -1,    -1,   540,    -1,   542,   543,    -1,
      51,    -1,    -1,    -1,    -1,   378,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,   567,   568,    -1,    -1,    -1,    78,    79,    -1,
      -1,    -1,    -1,    -1,    -1,   408,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    39,    40,    41,    42,    43,    -1,    -1,    -1,
     111,   112,    -1,    -1,    51,   438,   439,   440,   441,   442,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    80,    81,   458,    -1,    84,    85,    86,
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   474,     9,    -1,    -1,    -1,   479,   104,   105,   106,
     107,   108,   109,   110,    -1,    -1,   489,    -1,    -1,   492,
      -1,   494,   495,    -1,   111,   112,    -1,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    43,   510,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,
      -1,   544,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    91,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     107,    -1,    -1,   110,   111,   112,   113,   114,   115,   116,
     117,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    68,    69,    -1,    -1,    35,    -1,
      74,    -1,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    90,    91,     9,    -1,
      57,    58,    59,    60,    61,    62,    -1,    64,    -1,    -1,
      -1,    68,    -1,   107,    -1,    -1,   110,   111,   112,   113,
     114,   115,   116,   117,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,   111,   112,    -1,    68,    -1,   116,
     117,    76,    77,    74,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    90,
      91,     9,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,   107,   108,   109,   110,   107,    -1,    -1,   110,
     111,   112,   113,   114,   115,   116,   117,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    69,    -1,    -1,
      68,    -1,    -1,    -1,    -1,    77,    74,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,   107,
       4,    -1,   110,   111,   112,   113,   114,   115,   116,   117,
      -1,    15,    16,    -1,    -1,    19,    20,    -1,    22,    23,
      24,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    66,    67,    68,     4,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    78,    79,    15,    16,    -1,    -1,
      19,    20,    -1,    22,    23,    24,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      39,    40,    41,    42,    43,    44,    -1,   111,   112,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    66,    67,    68,
      -1,     5,    -1,    -1,    -1,    -1,    -1,    76,    -1,    78,
      79,    15,    16,    -1,    -1,    19,    20,    -1,    22,    23,
      24,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    39,    40,    41,    42,    43,
      44,    -1,   111,   112,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    66,    -1,    68,    -1,     5,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    78,    79,    15,    16,    -1,    -1,
      19,    20,    -1,    22,    23,    24,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      39,    40,    41,    42,    43,    44,    -1,   111,   112,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    66,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    78,
      79,    15,    16,    -1,    -1,    19,    20,    -1,    22,    23,
      24,    25,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    39,    40,    41,    42,    43,
      44,    -1,   111,   112,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    66,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    78,    79,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,   103,
     104,   105,   106,   107,   108,   109,   110,    65,    -1,    80,
      81,    -1,    70,    84,    85,    86,    87,    88,    89,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,   103,   104,   105,   106,   107,   108,   109,   110,
      -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    65,    -1,    80,    81,    -1,    70,    84,
      85,    86,    87,    88,    89,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,   104,
      -1,   106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    65,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    65,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    77,    -1,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   103,   104,   105,
     106,   107,   108,   109,   110,    -1,    65,    -1,    -1,    -1,
     103,   104,   105,   106,   107,   108,   109,   110,    77,    65,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,   103,   104,   105,   106,   107,   108,
     109,   110,    -1,    65,    -1,    -1,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,    77,    65,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    77,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   103,   104,   105,   106,   107,   108,   109,   110,    -1,
      65,    -1,    -1,    -1,   103,   104,   105,   106,   107,   108,
     109,   110,    77,    65,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,   103,   104,
     105,   106,   107,   108,   109,   110,    -1,    65,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    77,
      65,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    77,    -1,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,   103,   104,   105,   106,   107,
     108,   109,   110,    -1,    65,    -1,    -1,    -1,   103,   104,
     105,   106,   107,   108,   109,   110,    77,    65,    -1,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,   103,   104,   105,   106,   107,   108,   109,   110,
      -1,    65,    -1,    -1,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    77,    65,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    77,    -1,    -1,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,   103,
     104,   105,   106,   107,   108,   109,   110,    -1,    65,    -1,
      -1,    -1,   103,   104,   105,   106,   107,   108,   109,   110,
      77,    65,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   103,   104,   105,   106,
     107,   108,   109,   110,    -1,    65,    -1,    -1,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    77,    65,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      77,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   103,   104,   105,   106,   107,   108,   109,
     110,    -1,    65,    -1,    -1,    -1,   103,   104,   105,   106,
     107,   108,   109,   110,    77,    65,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
     103,   104,   105,   106,   107,   108,   109,   110,    -1,    65,
      -1,    -1,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    77,    65,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    77,    -1,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   103,   104,   105,
     106,   107,   108,   109,   110,    -1,    65,    -1,    -1,    -1,
     103,   104,   105,   106,   107,   108,   109,   110,    77,    65,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,   103,   104,   105,   106,   107,   108,
     109,   110,    -1,    65,    -1,    -1,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,    77,    65,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    77,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   103,   104,   105,   106,   107,   108,   109,   110,    -1,
      65,    -1,    -1,    -1,   103,   104,   105,   106,   107,   108,
     109,   110,    77,    65,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,   103,   104,
     105,   106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,   107,   108,   109,   110,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,   105,   106,   107,   108,   109,   110,    75,    -1,
      77,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,
     107,   108,   109,   110,    76,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    76,
      77,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   103,   104,   105,   106,
     107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    80,    81,    -1,
      83,    84,    85,    86,    87,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,   105,   106,   107,   108,   109,   110
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     4,     5,     6,     7,     8,    10,    11,    12,    39,
      76,   112,   128,   129,   130,   131,   132,   133,   134,   219,
     111,   112,   220,   220,    64,   219,   219,   219,     0,    76,
     130,   131,   132,    64,    76,    76,   113,   222,    64,    64,
      64,   181,   182,   219,    65,   181,   181,   181,    65,    70,
      92,    76,    65,    65,    65,    66,   140,   182,   219,     9,
      35,    36,    37,    38,    40,    41,    42,    43,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    68,    74,
      90,    91,   107,   110,   112,   114,   115,   116,   117,   166,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   140,   140,   140,     4,    15,    16,    19,
      20,    22,    23,    24,    25,    27,    28,    29,    30,    31,
      32,    33,    34,    44,    67,    68,    76,    78,    79,   135,
     136,   138,   139,   140,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   168,   169,
     170,   177,   178,   191,   197,   198,   199,   200,   201,   202,
     205,   206,   209,   212,   213,   214,   215,   219,   220,    68,
     219,   220,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,   166,    68,    69,   219,   166,   166,    64,   116,   117,
     177,   178,   205,   206,   208,   209,   219,   112,    77,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,   103,
     104,   105,   106,   107,   108,   109,   110,    68,    68,    68,
      68,    68,    68,    68,    68,    71,   179,   180,   219,    64,
      74,    71,     5,    76,   135,   137,   166,   166,    76,    64,
     135,    64,    64,    64,    64,   107,   222,   226,    75,    76,
      76,    76,   166,    64,    64,   219,   209,   209,    67,    76,
     136,    76,    76,    76,    76,    76,    13,    14,    17,    18,
      71,    78,    79,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,    74,    68,    64,    74,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,    65,   166,
     166,   166,   166,   166,   166,   166,   166,    65,    70,   166,
     166,    74,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,    68,   166,
      39,   112,   218,   166,   183,   184,   219,    39,     5,    76,
     135,    76,    76,   166,    23,   166,   141,   168,   169,   170,
     209,   219,   166,    75,    75,    76,   183,   183,    92,    64,
      64,    64,    64,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   219,   166,   183,   219,    70,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    70,    65,   166,    69,   112,    75,
      69,    69,    69,    69,    69,    69,    69,    69,    65,    70,
      64,    65,    64,    65,    76,    26,    70,    65,    65,    65,
     166,   166,   166,   166,   166,    69,    65,    64,   166,   166,
      70,    69,   166,   166,   183,   135,   166,   135,   166,   167,
     166,   219,   140,    76,    76,    76,    65,    65,    70,    65,
      70,    65,    70,    69,   183,    65,    65,   166,    64,    65,
      21,    65,    76,    65,    26,    76,    76,   183,   184,    76,
     184,    76,   184,    64,    65,    65,   183,   135,    76,   141,
     135,   166,    65,    65,    65,   183,    65,    65,    65,    76,
      76,    76,    65,   135,   135
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   127,   128,   128,   129,   129,   129,   129,   129,   129,
     129,   129,   130,   131,   132,   132,   132,   132,   133,   134,
     134,   134,   134,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   136,   136,
     137,   137,   137,   137,   138,   138,   138,   138,   139,   139,
     140,   140,   141,   141,   141,   141,   142,   142,   143,   144,
     144,   144,   145,   146,   146,   147,   148,   149,   149,   150,
     150,   151,   152,   153,   154,   155,   156,   157,   157,   158,
     159,   159,   160,   161,   162,   163,   163,   164,   165,   166,
     166,   166,   167,   167,   168,   168,   169,   169,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   171,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   174,   175,   175,   175,   175,   176,
     177,   177,   178,   178,   179,   179,   179,   179,   180,   180,
     181,   181,   181,   181,   181,   182,   183,   183,   184,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     204,   205,   205,   205,   205,   205,   205,   205,   205,   206,
     207,   207,   208,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   210,   211,   212,   213,   214,   215,   216,   216,
     217,   218,   219,   219,   220,   220,   221,   222,   223,   224,
     225,   225,   226,   226,   227,   228
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     2,     1,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     5,     5,
       6,     6,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     2,     1,     2,     1,     3,     2,
       3,     2,     1,     1,     1,     0,     2,     2,     5,     2,
       2,     2,     6,     8,     6,     3,     3,     8,     6,     8,
       6,     2,     5,     7,     5,     7,     9,     7,     9,     5,
       3,     3,     2,     2,     2,     3,     2,     5,     5,     1,
       1,     1,     1,     0,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       1,     1,     2,     2,     4,     6,     5,     7,     8,     9,
       3,     3,     1,     1,     0,     3,     1,     0,     3,     1,
       6,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,     4,     4,     4,     4,     4,     4,     6,     4,     2,
       3,     4,     4,     4,     4,     4,     4,     4,     4,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     7,     1,
       2,     1,     2,     1,     1,     1
  };




#if ARCDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   299,   299,   300,   304,   306,   308,   310,   312,   314,
     316,   318,   323,   327,   332,   333,   334,   335,   339,   344,
     346,   348,   350,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   383,   384,
     388,   390,   392,   394,   399,   401,   403,   405,   410,   411,
     415,   416,   420,   422,   424,   427,   431,   433,   438,   443,
     445,   447,   452,   457,   459,   464,   469,   474,   476,   481,
     483,   488,   493,   498,   503,   508,   513,   518,   524,   532,
     539,   541,   546,   551,   556,   561,   563,   568,   573,   578,
     579,   580,   584,   585,   589,   591,   596,   598,   603,   605,
     607,   609,   611,   613,   615,   617,   619,   621,   623,   628,
     633,   635,   637,   639,   641,   643,   645,   647,   649,   651,
     653,   655,   657,   659,   661,   663,   665,   667,   672,   673,
     674,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   692,   693,
     694,   695,   696,   697,   698,   699,   700,   701,   702,   703,
     704,   705,   706,   707,   708,   709,   710,   711,   712,   713,
     714,   715,   716,   717,   721,   726,   728,   730,   732,   737,
     742,   743,   747,   754,   764,   766,   768,   770,   775,   777,
     782,   784,   786,   788,   791,   795,   800,   803,   807,   809,
     814,   819,   824,   829,   834,   839,   844,   849,   854,   859,
     864,   869,   874,   879,   884,   889,   894,   899,   904,   909,
     911,   916,   918,   920,   922,   924,   926,   928,   930,   935,
     940,   942,   947,   952,   953,   954,   955,   956,   957,   958,
     959,   960,   964,   969,   974,   979,   984,   989,   994,   996,
    1001,  1006,  1011,  1013,  1018,  1020,  1025,  1030,  1035,  1040,
    1045,  1047,  1052,  1054,  1059,  1064
  };

  void
  parser::yy_stack_print_ () const
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
  parser::yy_reduce_print_ (int yyrule) const
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
#endif // ARCDEBUG


#line 13 "parser.ypp"
} } // xsk::arc
#line 5530 "parser.cpp"

#line 1068 "parser.ypp"


namespace xsk::arc
{

void parser::error(location const& loc, std::string const& msg)
{
    throw comp_error(loc, msg);
}

auto parse_switch(stmt_switch& stm) -> void
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

extern std::unordered_map<token::kind, parser::token::token_kind_type> const tok_to_parser;
extern std::unordered_map<std::string_view, parser::token::token_kind_type> const keyword_map;

auto map_token(context const* ctx_, token& tok) -> parser::symbol_type
{
    if (tok.type == token::NAME)
    {
        tok.data = ctx_->make_token(tok.data);

        auto const it = keyword_map.find(tok.data);

        if (it != keyword_map.end())
        {
            return parser::symbol_type(it->second, tok.pos);
        }

        return parser::symbol_type(parser::token::IDENTIFIER, std::move(tok.data), tok.pos);
    }
    else if (tok.type == token::PATH ||tok.type == token::HASHSTR ||tok.type == token::STRING ||tok.type == token::ISTRING || tok.type == token::INT ||tok.type == token::FLT)
    {
        auto it = tok_to_parser.find(tok.type);

        if (it != tok_to_parser.end())
        {
            return parser::symbol_type(it->second, std::move(tok.data), tok.pos);
        }
    }
    else
    {
        auto it = tok_to_parser.find(tok.type);

        if (it != tok_to_parser.end())
        {
            return parser::symbol_type(it->second, tok.pos);
        }
    }

    throw error(std::format("unmapped token! {}", (u8)tok.type));
}

auto ARClex(context const* ctx_, preprocessor& ppr) -> parser::symbol_type
{
    auto tok = ppr.process();
    return map_token(ctx_, tok);
}

std::unordered_map<token::kind, parser::token::token_kind_type> const tok_to_parser
{{
    { token::NAME, parser::token::IDENTIFIER },
    { token::PATH, parser::token::PATH },
    { token::STRING, parser::token::STRING },
    { token::ISTRING, parser::token::ISTRING },
    { token::HASHSTR, parser::token::HASHSTR },
    { token::INT, parser::token::INTEGER },
    { token::FLT, parser::token::FLOAT },
    { token::PLUS, parser::token::ADD },
    { token::MINUS, parser::token::SUB },
    { token::STAR, parser::token::MUL },
    { token::DIV, parser::token::DIV },
    { token::MOD, parser::token::MOD },
    { token::BITOR, parser::token::BITWISE_OR },
    { token::BITAND, parser::token::BITWISE_AND },
    { token::BITEXOR, parser::token::BITWISE_EXOR },
    { token::ASSIGN, parser::token::ASSIGN },
    { token::PLUSEQ, parser::token::ASSIGN_ADD },
    { token::MINUSEQ, parser::token::ASSIGN_SUB },
    { token::STAREQ, parser::token::ASSIGN_MUL },
    { token::DIVEQ, parser::token::ASSIGN_DIV },
    { token::MODEQ, parser::token::ASSIGN_MOD },
    { token::BITOREQ, parser::token::ASSIGN_BW_OR },
    { token::BITANDEQ, parser::token::ASSIGN_BW_AND },
    { token::BITEXOREQ, parser::token::ASSIGN_BW_EXOR },
    { token::SHLEQ, parser::token::ASSIGN_LSHIFT },
    { token::SHREQ, parser::token::ASSIGN_RSHIFT },
    { token::TILDE, parser::token::COMPLEMENT },
    { token::BANG, parser::token::NOT },
    { token::GT, parser::token::GREATER },
    { token::LT, parser::token::LESS },
    { token::GE, parser::token::GREATER_EQUAL },
    { token::LE, parser::token::LESS_EQUAL },
    { token::NE, parser::token::INEQUALITY },
    { token::EQ, parser::token::EQUALITY },
    { token::OR, parser::token::OR },
    { token::AND, parser::token::AND },
    { token::SHL, parser::token::LSHIFT },
    { token::SHR, parser::token::RSHIFT },
    { token::INC, parser::token::INCREMENT },
    { token::DEC, parser::token::DECREMENT },
    { token::QMARK, parser::token::QMARK },
    { token::DOT, parser::token::DOT },
    { token::DOUBLEDOT, parser::token::DOUBLEDOT },
    { token::ELLIPSIS, parser::token::ELLIPSIS },
    { token::COMMA, parser::token::COMMA },
    { token::COLON, parser::token::COLON },
    { token::SEMICOLON, parser::token::SEMICOLON },
    { token::DOUBLECOLON, parser::token::DOUBLECOLON },
    { token::LBRACKET, parser::token::LBRACKET },
    { token::RBRACKET, parser::token::RBRACKET },
    { token::LBRACE, parser::token::LBRACE },
    { token::RBRACE, parser::token::RBRACE },
    { token::LPAREN, parser::token::LPAREN },
    { token::RPAREN, parser::token::RPAREN },
    { token::DEVBEGIN, parser::token::DEVBEGIN },
    { token::DEVEND, parser::token::DEVEND },
    { token::INLINE, parser::token::INLINE },
    { token::INCLUDE, parser::token::INCLUDE },
    { token::USINGTREE, parser::token::USINGTREE },
    { token::ANIMTREE, parser::token::ANIMTREE },
    { token::AUTOEXEC, parser::token::AUTOEXEC },
    { token::CODECALL, parser::token::CODECALL },
    { token::PRIVATE, parser::token::PRIVATE },
    { token::ENDON, parser::token::ENDON },
    { token::NOTIFY, parser::token::NOTIFY },
    { token::WAIT, parser::token::WAIT },
    { token::WAITREALTIME, parser::token::WAITREALTIME },
    { token::WAITTILL, parser::token::WAITTILL },
    { token::WAITTILLMATCH, parser::token::WAITTILLMATCH },
    { token::WAITTILLFRAMEEND, parser::token::WAITTILLFRAMEEND },
    { token::IF, parser::token::IF },
    { token::ELSE, parser::token::ELSE },
    { token::DO, parser::token::DO },
    { token::WHILE, parser::token::WHILE },
    { token::FOR, parser::token::FOR },
    { token::FOREACH, parser::token::FOREACH },
    { token::IN, parser::token::IN },
    { token::SWITCH, parser::token::SWITCH },
    { token::CASE, parser::token::CASE },
    { token::DEFAULT, parser::token::DEFAULT },
    { token::BREAK, parser::token::BREAK },
    { token::CONTINUE, parser::token::CONTINUE },
    { token::RETURN, parser::token::RETURN },
    { token::PROFBEGIN, parser::token::PROFBEGIN },
    { token::PROFEND, parser::token::PROFEND },
    { token::THREAD, parser::token::THREAD },
    { token::TRUE, parser::token::TRUE },
    { token::FALSE, parser::token::FALSE },
    { token::UNDEFINED, parser::token::UNDEFINED },
    { token::SIZE, parser::token::SIZE },
    { token::GAME, parser::token::GAME },
    { token::SELF, parser::token::SELF },
    { token::ANIM, parser::token::ANIM },
    { token::LEVEL, parser::token::LEVEL },
    { token::CONST, parser::token::CONST },
    { token::ISDEFINED, parser::token::ISDEFINED },
    { token::VECTORSCALE, parser::token::VECTORSCALE },
    { token::ANGLESTOUP, parser::token::ANGLESTOUP },
    { token::ANGLESTORIGHT, parser::token::ANGLESTORIGHT },
    { token::ANGLESTOFORWARD, parser::token::ANGLESTOFORWARD },
    { token::ANGLECLAMP180, parser::token::ANGLECLAMP180 },
    { token::VECTORTOANGLES, parser::token::VECTORTOANGLES },
    { token::ABS, parser::token::ABS },
    { token::GETTIME, parser::token::GETTIME },
    { token::GETDVAR, parser::token::GETDVAR },
    { token::GETDVARINT, parser::token::GETDVARINT },
    { token::GETDVARFLOAT, parser::token::GETDVARFLOAT },
    { token::GETDVARVECTOR, parser::token::GETDVARVECTOR },
    { token::GETDVARCOLORRED, parser::token::GETDVARCOLORRED },
    { token::GETDVARCOLORGREEN, parser::token::GETDVARCOLORGREEN },
    { token::GETDVARCOLORBLUE, parser::token::GETDVARCOLORBLUE },
    { token::GETDVARCOLORALPHA, parser::token::GETDVARCOLORALPHA },
    { token::GETFIRSTARRAYKEY, parser::token::GETFIRSTARRAYKEY },
    { token::GETNEXTARRAYKEY, parser::token::GETNEXTARRAYKEY },
    { token::EOS, parser::token::ARCEOF },
    { token::HASH, parser::token::HASH }
}};

std::unordered_map<std::string_view, parser::token::token_kind_type> const keyword_map
{{
    { "autoexec", parser::token::AUTOEXEC },
    { "codecall", parser::token::CODECALL },
    { "private", parser::token::PRIVATE },
    { "endon", parser::token::ENDON },
    { "notify", parser::token::NOTIFY },
    { "wait", parser::token::WAIT },
    { "waitrealtime", parser::token::WAITREALTIME},
    { "waittill", parser::token::WAITTILL },
    { "waittillmatch", parser::token::WAITTILLMATCH },
    { "waittillframeend", parser::token::WAITTILLFRAMEEND },
    { "if", parser::token::IF },
    { "else", parser::token::ELSE },
    { "do", parser::token::DO },
    { "while", parser::token::WHILE },
    { "for", parser::token::FOR },
    { "foreach", parser::token::FOREACH },
    { "in", parser::token::IN },
    { "switch", parser::token::SWITCH },
    { "case", parser::token::CASE },
    { "default", parser::token::DEFAULT },
    { "break", parser::token::BREAK },
    { "continue", parser::token::CONTINUE },
    { "return", parser::token::RETURN },
    { "prof_begin", parser::token::PROFBEGIN },
    { "prof_end", parser::token::PROFEND },
    { "thread", parser::token::THREAD },
    { "true", parser::token::TRUE },
    { "false", parser::token::FALSE },
    { "undefined", parser::token::UNDEFINED },
    { "size", parser::token::SIZE },
    { "game", parser::token::GAME },
    { "self", parser::token::SELF },
    { "anim", parser::token::ANIM },
    { "level", parser::token::LEVEL },
    { "const", parser::token::CONST },
    { "isdefined", parser::token::ISDEFINED },
    { "vectorscale", parser::token::VECTORSCALE },
    { "anglestoup", parser::token::ANGLESTOUP },
    { "anglestoright", parser::token::ANGLESTORIGHT },
    { "anglestoforward", parser::token::ANGLESTOFORWARD },
    { "angleclamp180", parser::token::ANGLECLAMP180 },
    { "vectortoangles", parser::token::VECTORTOANGLES },
    { "abs", parser::token::ABS },
    { "gettime", parser::token::GETTIME },
    { "getdvar", parser::token::GETDVAR },
    { "getdvarint", parser::token::GETDVARINT },
    { "getdvarfloat", parser::token::GETDVARFLOAT },
    { "getdvarvector", parser::token::GETDVARVECTOR },
    { "getdvarcolorred", parser::token::GETDVARCOLORRED },
    { "getdvarcolorgreen", parser::token::GETDVARCOLORGREEN },
    { "getdvarcolorblue", parser::token::GETDVARCOLORBLUE },
    { "getdvarcoloralpha", parser::token::GETDVARCOLORALPHA },
    { "getfirstarraykey", parser::token::GETFIRSTARRAYKEY },
    { "getnextarraykey", parser::token::GETNEXTARRAYKEY },
}};

} // namespace xsk::arc
