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
#line 297 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program::ptr > ()); }
#line 2316 "parser.cpp"
    break;

  case 3: // root: %empty
#line 298 "parser.ypp"
              { ast = program::make(yylhs.location); }
#line 2322 "parser.cpp"
    break;

  case 4: // program: program ";"
#line 303 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2328 "parser.cpp"
    break;

  case 5: // program: program inline
#line 305 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2334 "parser.cpp"
    break;

  case 6: // program: program include
#line 307 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2340 "parser.cpp"
    break;

  case 7: // program: program declaration
#line 309 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2346 "parser.cpp"
    break;

  case 8: // program: ";"
#line 311 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2352 "parser.cpp"
    break;

  case 9: // program: inline
#line 313 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2358 "parser.cpp"
    break;

  case 10: // program: include
#line 315 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2364 "parser.cpp"
    break;

  case 11: // program: declaration
#line 317 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2370 "parser.cpp"
    break;

  case 12: // inline: "#inline" expr_path ";"
#line 321 "parser.ypp"
                                 { ppr.push_header(yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2376 "parser.cpp"
    break;

  case 13: // include: "#include" expr_path ";"
#line 326 "parser.ypp"
        { yylhs.value.as < include::ptr > () = include::make(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2382 "parser.cpp"
    break;

  case 14: // declaration: "/#"
#line 330 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_begin::make(yylhs.location); }
#line 2388 "parser.cpp"
    break;

  case 15: // declaration: "#/"
#line 331 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_end::make(yylhs.location); }
#line 2394 "parser.cpp"
    break;

  case 16: // declaration: decl_usingtree
#line 332 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_usingtree::ptr > ()); }
#line 2400 "parser.cpp"
    break;

  case 17: // declaration: decl_function
#line 333 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_function::ptr > ()); }
#line 2406 "parser.cpp"
    break;

  case 18: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 338 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_usingtree::ptr > () = decl_usingtree::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 2412 "parser.cpp"
    break;

  case 19: // decl_function: expr_identifier "(" expr_parameters ")" stmt_comp
#line 343 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_none); }
#line 2418 "parser.cpp"
    break;

  case 20: // decl_function: "autoexec" expr_identifier "(" expr_parameters ")" stmt_comp
#line 345 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_autoexec); }
#line 2424 "parser.cpp"
    break;

  case 21: // decl_function: "codecall" expr_identifier "(" expr_parameters ")" stmt_comp
#line 347 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_codecall); }
#line 2430 "parser.cpp"
    break;

  case 22: // decl_function: "private" expr_identifier "(" expr_parameters ")" stmt_comp
#line 349 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_private2); }
#line 2436 "parser.cpp"
    break;

  case 23: // stmt: stmt_comp
#line 353 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_comp::ptr > ()); }
#line 2442 "parser.cpp"
    break;

  case 24: // stmt: stmt_call
#line 354 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2448 "parser.cpp"
    break;

  case 25: // stmt: stmt_const
#line 355 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2454 "parser.cpp"
    break;

  case 26: // stmt: stmt_assign
#line 356 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2460 "parser.cpp"
    break;

  case 27: // stmt: stmt_endon
#line 357 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_endon::ptr > ()); }
#line 2466 "parser.cpp"
    break;

  case 28: // stmt: stmt_notify
#line 358 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_notify::ptr > ()); }
#line 2472 "parser.cpp"
    break;

  case 29: // stmt: stmt_wait
#line 359 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_wait::ptr > ()); }
#line 2478 "parser.cpp"
    break;

  case 30: // stmt: stmt_waittill
#line 360 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittill::ptr > ()); }
#line 2484 "parser.cpp"
    break;

  case 31: // stmt: stmt_waittillmatch
#line 361 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillmatch::ptr > ()); }
#line 2490 "parser.cpp"
    break;

  case 32: // stmt: stmt_waittillframeend
#line 362 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillframeend::ptr > ()); }
#line 2496 "parser.cpp"
    break;

  case 33: // stmt: stmt_if
#line 363 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_if::ptr > ()); }
#line 2502 "parser.cpp"
    break;

  case 34: // stmt: stmt_ifelse
#line 364 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_ifelse::ptr > ()); }
#line 2508 "parser.cpp"
    break;

  case 35: // stmt: stmt_while
#line 365 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_while::ptr > ()); }
#line 2514 "parser.cpp"
    break;

  case 36: // stmt: stmt_dowhile
#line 366 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dowhile::ptr > ()); }
#line 2520 "parser.cpp"
    break;

  case 37: // stmt: stmt_for
#line 367 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_for::ptr > ()); }
#line 2526 "parser.cpp"
    break;

  case 38: // stmt: stmt_foreach
#line 368 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_foreach::ptr > ()); }
#line 2532 "parser.cpp"
    break;

  case 39: // stmt: stmt_switch
#line 369 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_switch::ptr > ()); }
#line 2538 "parser.cpp"
    break;

  case 40: // stmt: stmt_case
#line 370 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_case::ptr > ()); }
#line 2544 "parser.cpp"
    break;

  case 41: // stmt: stmt_default
#line 371 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_default::ptr > ()); }
#line 2550 "parser.cpp"
    break;

  case 42: // stmt: stmt_break
#line 372 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_break::ptr > ()); }
#line 2556 "parser.cpp"
    break;

  case 43: // stmt: stmt_continue
#line 373 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_continue::ptr > ()); }
#line 2562 "parser.cpp"
    break;

  case 44: // stmt: stmt_return
#line 374 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_return::ptr > ()); }
#line 2568 "parser.cpp"
    break;

  case 45: // stmt: stmt_prof_begin
#line 375 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_begin::ptr > ()); }
#line 2574 "parser.cpp"
    break;

  case 46: // stmt: stmt_prof_end
#line 376 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_end::ptr > ()); }
#line 2580 "parser.cpp"
    break;

  case 47: // stmt_or_dev: stmt
#line 380 "parser.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt::ptr > ()); }
#line 2586 "parser.cpp"
    break;

  case 48: // stmt_or_dev: stmt_dev
#line 381 "parser.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dev::ptr > ()); }
#line 2592 "parser.cpp"
    break;

  case 49: // stmt_list: stmt_list stmt
#line 386 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2598 "parser.cpp"
    break;

  case 50: // stmt_list: stmt
#line 388 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2604 "parser.cpp"
    break;

  case 51: // stmt_list: stmt_list ";"
#line 390 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2610 "parser.cpp"
    break;

  case 52: // stmt_list: ";"
#line 392 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2616 "parser.cpp"
    break;

  case 53: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 397 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2622 "parser.cpp"
    break;

  case 54: // stmt_or_dev_list: stmt_or_dev
#line 399 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2628 "parser.cpp"
    break;

  case 55: // stmt_or_dev_list: stmt_or_dev_list ";"
#line 401 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2634 "parser.cpp"
    break;

  case 56: // stmt_or_dev_list: ";"
#line 403 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2640 "parser.cpp"
    break;

  case 57: // stmt_dev: "/#" stmt_list "#/"
#line 407 "parser.ypp"
                                { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2646 "parser.cpp"
    break;

  case 58: // stmt_dev: "/#" "#/"
#line 408 "parser.ypp"
                      { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2652 "parser.cpp"
    break;

  case 59: // stmt_comp: "{" stmt_or_dev_list "}"
#line 412 "parser.ypp"
                                     { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2658 "parser.cpp"
    break;

  case 60: // stmt_comp: "{" "}"
#line 413 "parser.ypp"
                    { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2664 "parser.cpp"
    break;

  case 61: // stmt_expr: expr_assign
#line 418 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2670 "parser.cpp"
    break;

  case 62: // stmt_expr: expr_increment
#line 420 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2676 "parser.cpp"
    break;

  case 63: // stmt_expr: expr_decrement
#line 422 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2682 "parser.cpp"
    break;

  case 64: // stmt_expr: %empty
#line 424 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 2688 "parser.cpp"
    break;

  case 65: // stmt_call: expr_call ";"
#line 429 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_call::ptr > ())); }
#line 2694 "parser.cpp"
    break;

  case 66: // stmt_call: expr_method ";"
#line 431 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_method::ptr > ())); }
#line 2700 "parser.cpp"
    break;

  case 67: // stmt_const: "const" expr_identifier "=" expr ";"
#line 436 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, expr_const::make(yylhs.location, std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ()))); }
#line 2706 "parser.cpp"
    break;

  case 68: // stmt_assign: expr_assign ";"
#line 441 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2712 "parser.cpp"
    break;

  case 69: // stmt_assign: expr_increment ";"
#line 443 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2718 "parser.cpp"
    break;

  case 70: // stmt_assign: expr_decrement ";"
#line 445 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2724 "parser.cpp"
    break;

  case 71: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 450 "parser.ypp"
        { yylhs.value.as < stmt_endon::ptr > () = stmt_endon::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 2730 "parser.cpp"
    break;

  case 72: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 455 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2736 "parser.cpp"
    break;

  case 73: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 457 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2742 "parser.cpp"
    break;

  case 74: // stmt_wait: "wait" expr ";"
#line 462 "parser.ypp"
        { yylhs.value.as < stmt_wait::ptr > () = stmt_wait::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2748 "parser.cpp"
    break;

  case 75: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 467 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2754 "parser.cpp"
    break;

  case 76: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 469 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2760 "parser.cpp"
    break;

  case 77: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 474 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2766 "parser.cpp"
    break;

  case 78: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 476 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2772 "parser.cpp"
    break;

  case 79: // stmt_waittillframeend: "waittillframeend" ";"
#line 481 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend::ptr > () = stmt_waittillframeend::make(yylhs.location); }
#line 2778 "parser.cpp"
    break;

  case 80: // stmt_if: "if" "(" expr ")" stmt
#line 486 "parser.ypp"
        { yylhs.value.as < stmt_if::ptr > () = stmt_if::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2784 "parser.cpp"
    break;

  case 81: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 491 "parser.ypp"
        { yylhs.value.as < stmt_ifelse::ptr > () = stmt_ifelse::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2790 "parser.cpp"
    break;

  case 82: // stmt_while: "while" "(" expr ")" stmt
#line 496 "parser.ypp"
        { yylhs.value.as < stmt_while::ptr > () = stmt_while::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2796 "parser.cpp"
    break;

  case 83: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 501 "parser.ypp"
        { yylhs.value.as < stmt_dowhile::ptr > () = stmt_dowhile::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[5].value.as < stmt::ptr > ())); }
#line 2802 "parser.cpp"
    break;

  case 84: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 506 "parser.ypp"
        { yylhs.value.as < stmt_for::ptr > () = stmt_for::make(yylhs.location, std::move(yystack_[6].value.as < stmt_expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt_expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2808 "parser.cpp"
    break;

  case 85: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 511 "parser.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, fmt::format("_a{}", ++index));
            auto key = expr_identifier::make(yylhs.location, fmt::format("_k{}", ++index));
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt::ptr > ()), false);
        }
#line 2818 "parser.cpp"
    break;

  case 86: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 517 "parser.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, fmt::format("_a{}", ++index));
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(array), std::move(yystack_[6].value.as < expr_identifier::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ()), true);
        }
#line 2827 "parser.cpp"
    break;

  case 87: // stmt_switch: "switch" "(" expr ")" stmt_comp
#line 525 "parser.ypp"
        { yylhs.value.as < stmt_switch::ptr > () = stmt_switch::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); 
          parse_switch(*yylhs.value.as < stmt_switch::ptr > ());
        }
#line 2835 "parser.cpp"
    break;

  case 88: // stmt_case: "case" expr_integer ":"
#line 532 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_integer::ptr > ()), stmt_list::make(yylhs.location)); }
#line 2841 "parser.cpp"
    break;

  case 89: // stmt_case: "case" expr_string ":"
#line 534 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_string::ptr > ()), stmt_list::make(yylhs.location)); }
#line 2847 "parser.cpp"
    break;

  case 90: // stmt_default: "default" ":"
#line 539 "parser.ypp"
        { yylhs.value.as < stmt_default::ptr > () = stmt_default::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2853 "parser.cpp"
    break;

  case 91: // stmt_break: "break" ";"
#line 544 "parser.ypp"
        { yylhs.value.as < stmt_break::ptr > () = stmt_break::make(yylhs.location); }
#line 2859 "parser.cpp"
    break;

  case 92: // stmt_continue: "continue" ";"
#line 549 "parser.ypp"
        { yylhs.value.as < stmt_continue::ptr > () = stmt_continue::make(yylhs.location); }
#line 2865 "parser.cpp"
    break;

  case 93: // stmt_return: "return" expr ";"
#line 554 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2871 "parser.cpp"
    break;

  case 94: // stmt_return: "return" ";"
#line 556 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 2877 "parser.cpp"
    break;

  case 95: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 561 "parser.ypp"
        { yylhs.value.as < stmt_prof_begin::ptr > () = stmt_prof_begin::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2883 "parser.cpp"
    break;

  case 96: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 566 "parser.ypp"
        { yylhs.value.as < stmt_prof_end::ptr > () = stmt_prof_end::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2889 "parser.cpp"
    break;

  case 97: // expr: expr_ternary
#line 570 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2895 "parser.cpp"
    break;

  case 98: // expr: expr_binary
#line 571 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2901 "parser.cpp"
    break;

  case 99: // expr: expr_primitive
#line 572 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2907 "parser.cpp"
    break;

  case 100: // expr_or_empty: expr
#line 576 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2913 "parser.cpp"
    break;

  case 101: // expr_or_empty: %empty
#line 577 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = expr_empty::make(yylhs.location); }
#line 2919 "parser.cpp"
    break;

  case 102: // expr_increment: "++" expr_object
#line 582 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 2925 "parser.cpp"
    break;

  case 103: // expr_increment: expr_object "++"
#line 584 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 2931 "parser.cpp"
    break;

  case 104: // expr_decrement: "--" expr_object
#line 589 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 2937 "parser.cpp"
    break;

  case 105: // expr_decrement: expr_object "--"
#line 591 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 2943 "parser.cpp"
    break;

  case 106: // expr_assign: expr_object "=" expr
#line 596 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 2949 "parser.cpp"
    break;

  case 107: // expr_assign: expr_object "|=" expr
#line 598 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwor); }
#line 2955 "parser.cpp"
    break;

  case 108: // expr_assign: expr_object "&=" expr
#line 600 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwand); }
#line 2961 "parser.cpp"
    break;

  case 109: // expr_assign: expr_object "^=" expr
#line 602 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwexor); }
#line 2967 "parser.cpp"
    break;

  case 110: // expr_assign: expr_object "<<=" expr
#line 604 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shl); }
#line 2973 "parser.cpp"
    break;

  case 111: // expr_assign: expr_object ">>=" expr
#line 606 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shr); }
#line 2979 "parser.cpp"
    break;

  case 112: // expr_assign: expr_object "+=" expr
#line 608 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::add); }
#line 2985 "parser.cpp"
    break;

  case 113: // expr_assign: expr_object "-=" expr
#line 610 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::sub); }
#line 2991 "parser.cpp"
    break;

  case 114: // expr_assign: expr_object "*=" expr
#line 612 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mul); }
#line 2997 "parser.cpp"
    break;

  case 115: // expr_assign: expr_object "/=" expr
#line 614 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::div); }
#line 3003 "parser.cpp"
    break;

  case 116: // expr_assign: expr_object "%=" expr
#line 616 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mod); }
#line 3009 "parser.cpp"
    break;

  case 117: // expr_ternary: expr "?" expr ":" expr
#line 621 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_ternary::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3015 "parser.cpp"
    break;

  case 118: // expr_binary: expr "||" expr
#line 626 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_or); }
#line 3021 "parser.cpp"
    break;

  case 119: // expr_binary: expr "&&" expr
#line 628 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_and); }
#line 3027 "parser.cpp"
    break;

  case 120: // expr_binary: expr "==" expr
#line 630 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::eq); }
#line 3033 "parser.cpp"
    break;

  case 121: // expr_binary: expr "!=" expr
#line 632 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ne); }
#line 3039 "parser.cpp"
    break;

  case 122: // expr_binary: expr "<=" expr
#line 634 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::le); }
#line 3045 "parser.cpp"
    break;

  case 123: // expr_binary: expr ">=" expr
#line 636 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ge); }
#line 3051 "parser.cpp"
    break;

  case 124: // expr_binary: expr "<" expr
#line 638 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::lt); }
#line 3057 "parser.cpp"
    break;

  case 125: // expr_binary: expr ">" expr
#line 640 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::gt); }
#line 3063 "parser.cpp"
    break;

  case 126: // expr_binary: expr "|" expr
#line 642 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwor); }
#line 3069 "parser.cpp"
    break;

  case 127: // expr_binary: expr "&" expr
#line 644 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwand); }
#line 3075 "parser.cpp"
    break;

  case 128: // expr_binary: expr "^" expr
#line 646 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwexor); }
#line 3081 "parser.cpp"
    break;

  case 129: // expr_binary: expr "<<" expr
#line 648 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shl); }
#line 3087 "parser.cpp"
    break;

  case 130: // expr_binary: expr ">>" expr
#line 650 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shr); }
#line 3093 "parser.cpp"
    break;

  case 131: // expr_binary: expr "+" expr
#line 652 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::add); }
#line 3099 "parser.cpp"
    break;

  case 132: // expr_binary: expr "-" expr
#line 654 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::sub); }
#line 3105 "parser.cpp"
    break;

  case 133: // expr_binary: expr "*" expr
#line 656 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mul); }
#line 3111 "parser.cpp"
    break;

  case 134: // expr_binary: expr "/" expr
#line 658 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::div); }
#line 3117 "parser.cpp"
    break;

  case 135: // expr_binary: expr "%" expr
#line 660 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mod); }
#line 3123 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_complement
#line 664 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_complement::ptr > ()); }
#line 3129 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_negate
#line 665 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_negate::ptr > ()); }
#line 3135 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_not
#line 666 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_not::ptr > ()); }
#line 3141 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_call
#line 667 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3147 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_method
#line 668 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3153 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_getnextarraykey
#line 669 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getnextarraykey::ptr > ()); }
#line 3159 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_getfirstarraykey
#line 670 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getfirstarraykey::ptr > ()); }
#line 3165 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_getdvarcoloralpha
#line 671 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcoloralpha::ptr > ()); }
#line 3171 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_getdvarcolorblue
#line 672 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorblue::ptr > ()); }
#line 3177 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_getdvarcolorgreen
#line 673 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorgreen::ptr > ()); }
#line 3183 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_getdvarcolorred
#line 674 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorred::ptr > ()); }
#line 3189 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_getdvarvector
#line 675 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarvector::ptr > ()); }
#line 3195 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_getdvarfloat
#line 676 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarfloat::ptr > ()); }
#line 3201 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_getdvarint
#line 677 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarint::ptr > ()); }
#line 3207 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_getdvar
#line 678 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvar::ptr > ()); }
#line 3213 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_gettime
#line 679 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_gettime::ptr > ()); }
#line 3219 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_abs
#line 680 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_abs::ptr > ()); }
#line 3225 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_vectortoangles
#line 681 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vectortoangles::ptr > ()); }
#line 3231 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_angleclamp180
#line 682 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_angleclamp180::ptr > ()); }
#line 3237 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_anglestoforward
#line 683 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoforward::ptr > ()); }
#line 3243 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_anglestoright
#line 684 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoright::ptr > ()); }
#line 3249 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_anglestoup
#line 685 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoup::ptr > ()); }
#line 3255 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_vectorscale
#line 686 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vectorscale::ptr > ()); }
#line 3261 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_isdefined
#line 687 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_isdefined::ptr > ()); }
#line 3267 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_reference
#line 688 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_reference::ptr > ()); }
#line 3273 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_array
#line 689 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3279 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_field
#line 690 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3285 "parser.cpp"
    break;

  case 163: // expr_primitive: expr_size
#line 691 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_size::ptr > ()); }
#line 3291 "parser.cpp"
    break;

  case 164: // expr_primitive: expr_paren
#line 692 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_paren::ptr > ()); }
#line 3297 "parser.cpp"
    break;

  case 165: // expr_primitive: expr_empty_array
#line 693 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_empty_array::ptr > ()); }
#line 3303 "parser.cpp"
    break;

  case 166: // expr_primitive: expr_undefined
#line 694 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_undefined::ptr > ()); }
#line 3309 "parser.cpp"
    break;

  case 167: // expr_primitive: expr_game
#line 695 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3315 "parser.cpp"
    break;

  case 168: // expr_primitive: expr_self
#line 696 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3321 "parser.cpp"
    break;

  case 169: // expr_primitive: expr_anim
#line 697 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3327 "parser.cpp"
    break;

  case 170: // expr_primitive: expr_level
#line 698 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3333 "parser.cpp"
    break;

  case 171: // expr_primitive: expr_animation
#line 699 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animation::ptr > ()); }
#line 3339 "parser.cpp"
    break;

  case 172: // expr_primitive: expr_animtree
#line 700 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animtree::ptr > ()); }
#line 3345 "parser.cpp"
    break;

  case 173: // expr_primitive: expr_identifier
#line 701 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3351 "parser.cpp"
    break;

  case 174: // expr_primitive: expr_istring
#line 702 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_istring::ptr > ()); }
#line 3357 "parser.cpp"
    break;

  case 175: // expr_primitive: expr_string
#line 703 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_string::ptr > ()); }
#line 3363 "parser.cpp"
    break;

  case 176: // expr_primitive: expr_vector
#line 704 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vector::ptr > ()); }
#line 3369 "parser.cpp"
    break;

  case 177: // expr_primitive: expr_hash
#line 705 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_hash::ptr > ()); }
#line 3375 "parser.cpp"
    break;

  case 178: // expr_primitive: expr_float
#line 706 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_float::ptr > ()); }
#line 3381 "parser.cpp"
    break;

  case 179: // expr_primitive: expr_integer
#line 707 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_integer::ptr > ()); }
#line 3387 "parser.cpp"
    break;

  case 180: // expr_primitive: expr_false
#line 708 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_false::ptr > ()); }
#line 3393 "parser.cpp"
    break;

  case 181: // expr_primitive: expr_true
#line 709 "parser.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_true::ptr > ()); }
#line 3399 "parser.cpp"
    break;

  case 182: // expr_complement: "~" expr
#line 714 "parser.ypp"
        { yylhs.value.as < expr_complement::ptr > () = expr_complement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3405 "parser.cpp"
    break;

  case 183: // expr_negate: "-" expr_identifier
#line 719 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3411 "parser.cpp"
    break;

  case 184: // expr_negate: "-" expr_paren
#line 721 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_paren::ptr > ())); }
#line 3417 "parser.cpp"
    break;

  case 185: // expr_negate: "-" expr_array
#line 723 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_array::ptr > ())); }
#line 3423 "parser.cpp"
    break;

  case 186: // expr_negate: "-" expr_field
#line 725 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_field::ptr > ())); }
#line 3429 "parser.cpp"
    break;

  case 187: // expr_not: "!" expr
#line 730 "parser.ypp"
        { yylhs.value.as < expr_not::ptr > () = expr_not::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3435 "parser.cpp"
    break;

  case 188: // expr_call: expr_function
#line 734 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3441 "parser.cpp"
    break;

  case 189: // expr_call: expr_pointer
#line 735 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3447 "parser.cpp"
    break;

  case 190: // expr_method: expr_object expr_function
#line 740 "parser.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3458 "parser.cpp"
    break;

  case 191: // expr_method: expr_object expr_pointer
#line 747 "parser.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3469 "parser.cpp"
    break;

  case 192: // expr_function: expr_identifier "(" expr_arguments ")"
#line 757 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3475 "parser.cpp"
    break;

  case 193: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 759 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3481 "parser.cpp"
    break;

  case 194: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 761 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3487 "parser.cpp"
    break;

  case 195: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 763 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3493 "parser.cpp"
    break;

  case 196: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 768 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3499 "parser.cpp"
    break;

  case 197: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 770 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3505 "parser.cpp"
    break;

  case 198: // expr_parameters: expr_parameters "," expr_parameters_default
#line 775 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3511 "parser.cpp"
    break;

  case 199: // expr_parameters: expr_parameters "," expr_identifier
#line 777 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3517 "parser.cpp"
    break;

  case 200: // expr_parameters: expr_parameters_default
#line 779 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3523 "parser.cpp"
    break;

  case 201: // expr_parameters: expr_identifier
#line 781 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3529 "parser.cpp"
    break;

  case 202: // expr_parameters: %empty
#line 783 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); }
#line 3535 "parser.cpp"
    break;

  case 203: // expr_parameters_default: expr_identifier "=" expr
#line 788 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr_identifier::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 3541 "parser.cpp"
    break;

  case 204: // expr_arguments: expr_arguments_no_empty
#line 793 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[0].value.as < expr_arguments::ptr > ()); }
#line 3547 "parser.cpp"
    break;

  case 205: // expr_arguments: %empty
#line 795 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); }
#line 3553 "parser.cpp"
    break;

  case 206: // expr_arguments_no_empty: expr_arguments "," expr
#line 800 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[2].value.as < expr_arguments::ptr > ()); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3559 "parser.cpp"
    break;

  case 207: // expr_arguments_no_empty: expr
#line 802 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3565 "parser.cpp"
    break;

  case 208: // expr_getnextarraykey: "getnextarraykey" "(" expr "," expr ")"
#line 807 "parser.ypp"
        { yylhs.value.as < expr_getnextarraykey::ptr > () = expr_getnextarraykey::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3571 "parser.cpp"
    break;

  case 209: // expr_getfirstarraykey: "getfirstarraykey" "(" expr ")"
#line 812 "parser.ypp"
        { yylhs.value.as < expr_getfirstarraykey::ptr > () = expr_getfirstarraykey::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3577 "parser.cpp"
    break;

  case 210: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr ")"
#line 817 "parser.ypp"
        { yylhs.value.as < expr_getdvarcoloralpha::ptr > () = expr_getdvarcoloralpha::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3583 "parser.cpp"
    break;

  case 211: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr ")"
#line 822 "parser.ypp"
        { yylhs.value.as < expr_getdvarcolorblue::ptr > () = expr_getdvarcolorblue::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3589 "parser.cpp"
    break;

  case 212: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr ")"
#line 827 "parser.ypp"
        { yylhs.value.as < expr_getdvarcolorgreen::ptr > () = expr_getdvarcolorgreen::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3595 "parser.cpp"
    break;

  case 213: // expr_getdvarcolorred: "getdvarcolorred" "(" expr ")"
#line 832 "parser.ypp"
        { yylhs.value.as < expr_getdvarcolorred::ptr > () = expr_getdvarcolorred::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3601 "parser.cpp"
    break;

  case 214: // expr_getdvarvector: "getdvarvector" "(" expr ")"
#line 837 "parser.ypp"
        { yylhs.value.as < expr_getdvarvector::ptr > () = expr_getdvarvector::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3607 "parser.cpp"
    break;

  case 215: // expr_getdvarfloat: "getdvarfloat" "(" expr ")"
#line 842 "parser.ypp"
        { yylhs.value.as < expr_getdvarfloat::ptr > () = expr_getdvarfloat::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3613 "parser.cpp"
    break;

  case 216: // expr_getdvarint: "getdvarint" "(" expr ")"
#line 847 "parser.ypp"
        { yylhs.value.as < expr_getdvarint::ptr > () = expr_getdvarint::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3619 "parser.cpp"
    break;

  case 217: // expr_getdvar: "getdvar" "(" expr ")"
#line 852 "parser.ypp"
        { yylhs.value.as < expr_getdvar::ptr > () = expr_getdvar::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3625 "parser.cpp"
    break;

  case 218: // expr_gettime: "gettime" "(" ")"
#line 857 "parser.ypp"
        { yylhs.value.as < expr_gettime::ptr > () = expr_gettime::make(yylhs.location); }
#line 3631 "parser.cpp"
    break;

  case 219: // expr_abs: "abs" "(" expr ")"
#line 862 "parser.ypp"
        { yylhs.value.as < expr_abs::ptr > () = expr_abs::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3637 "parser.cpp"
    break;

  case 220: // expr_vectortoangles: "vectortoangles" "(" expr ")"
#line 867 "parser.ypp"
        { yylhs.value.as < expr_vectortoangles::ptr > () = expr_vectortoangles::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3643 "parser.cpp"
    break;

  case 221: // expr_angleclamp180: "angleclamp180" "(" expr ")"
#line 872 "parser.ypp"
        { yylhs.value.as < expr_angleclamp180::ptr > () = expr_angleclamp180::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3649 "parser.cpp"
    break;

  case 222: // expr_anglestoforward: "anglestoforward" "(" expr ")"
#line 877 "parser.ypp"
        { yylhs.value.as < expr_anglestoforward::ptr > () = expr_anglestoforward::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3655 "parser.cpp"
    break;

  case 223: // expr_anglestoright: "anglestoright" "(" expr ")"
#line 882 "parser.ypp"
        { yylhs.value.as < expr_anglestoright::ptr > () = expr_anglestoright::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3661 "parser.cpp"
    break;

  case 224: // expr_anglestoup: "anglestoup" "(" expr ")"
#line 887 "parser.ypp"
        { yylhs.value.as < expr_anglestoup::ptr > () = expr_anglestoup::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3667 "parser.cpp"
    break;

  case 225: // expr_vectorscale: "vectorscale" "(" expr "," expr ")"
#line 892 "parser.ypp"
        { yylhs.value.as < expr_vectorscale::ptr > () = expr_vectorscale::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3673 "parser.cpp"
    break;

  case 226: // expr_isdefined: "isdefined" "(" expr ")"
#line 897 "parser.ypp"
        { yylhs.value.as < expr_isdefined::ptr > () = expr_isdefined::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3679 "parser.cpp"
    break;

  case 227: // expr_reference: "::" expr_identifier
#line 902 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3685 "parser.cpp"
    break;

  case 228: // expr_reference: expr_path "::" expr_identifier
#line 904 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, std::move(yystack_[2].value.as < expr_path::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3691 "parser.cpp"
    break;

  case 229: // expr_array: expr_object "[" expr "]"
#line 909 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3697 "parser.cpp"
    break;

  case 230: // expr_array: expr_getdvarvector "[" expr "]"
#line 911 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_getdvarvector::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3703 "parser.cpp"
    break;

  case 231: // expr_array: expr_vectortoangles "[" expr "]"
#line 913 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_vectortoangles::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3709 "parser.cpp"
    break;

  case 232: // expr_array: expr_angleclamp180 "[" expr "]"
#line 915 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_angleclamp180::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3715 "parser.cpp"
    break;

  case 233: // expr_array: expr_anglestoforward "[" expr "]"
#line 917 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoforward::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3721 "parser.cpp"
    break;

  case 234: // expr_array: expr_anglestoright "[" expr "]"
#line 919 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoright::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3727 "parser.cpp"
    break;

  case 235: // expr_array: expr_anglestoup "[" expr "]"
#line 921 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoup::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3733 "parser.cpp"
    break;

  case 236: // expr_array: expr_vectorscale "[" expr "]"
#line 923 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_vectorscale::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3739 "parser.cpp"
    break;

  case 237: // expr_field: expr_object "." expr_identifier_nosize
#line 928 "parser.ypp"
        { yylhs.value.as < expr_field::ptr > () = expr_field::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3745 "parser.cpp"
    break;

  case 238: // expr_size: expr_object "." "size"
#line 933 "parser.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 3751 "parser.cpp"
    break;

  case 239: // expr_size: expr_string "." "size"
#line 935 "parser.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 3757 "parser.cpp"
    break;

  case 240: // expr_paren: "(" expr ")"
#line 940 "parser.ypp"
        { yylhs.value.as < expr_paren::ptr > () = expr_paren::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3763 "parser.cpp"
    break;

  case 241: // expr_object: expr_call
#line 944 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3769 "parser.cpp"
    break;

  case 242: // expr_object: expr_method
#line 945 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3775 "parser.cpp"
    break;

  case 243: // expr_object: expr_array
#line 946 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3781 "parser.cpp"
    break;

  case 244: // expr_object: expr_field
#line 947 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3787 "parser.cpp"
    break;

  case 245: // expr_object: expr_game
#line 948 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3793 "parser.cpp"
    break;

  case 246: // expr_object: expr_self
#line 949 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3799 "parser.cpp"
    break;

  case 247: // expr_object: expr_anim
#line 950 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3805 "parser.cpp"
    break;

  case 248: // expr_object: expr_level
#line 951 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3811 "parser.cpp"
    break;

  case 249: // expr_object: expr_identifier
#line 952 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3817 "parser.cpp"
    break;

  case 250: // expr_empty_array: "[" "]"
#line 957 "parser.ypp"
        { yylhs.value.as < expr_empty_array::ptr > () = expr_empty_array::make(yylhs.location); }
#line 3823 "parser.cpp"
    break;

  case 251: // expr_undefined: "undefined"
#line 962 "parser.ypp"
        { yylhs.value.as < expr_undefined::ptr > () = expr_undefined::make(yylhs.location); }
#line 3829 "parser.cpp"
    break;

  case 252: // expr_game: "game"
#line 967 "parser.ypp"
        { yylhs.value.as < expr_game::ptr > () = expr_game::make(yylhs.location); }
#line 3835 "parser.cpp"
    break;

  case 253: // expr_self: "self"
#line 972 "parser.ypp"
        { yylhs.value.as < expr_self::ptr > () = expr_self::make(yylhs.location); }
#line 3841 "parser.cpp"
    break;

  case 254: // expr_anim: "anim"
#line 977 "parser.ypp"
        { yylhs.value.as < expr_anim::ptr > () = expr_anim::make(yylhs.location); }
#line 3847 "parser.cpp"
    break;

  case 255: // expr_level: "level"
#line 982 "parser.ypp"
        { yylhs.value.as < expr_level::ptr > () = expr_level::make(yylhs.location); }
#line 3853 "parser.cpp"
    break;

  case 256: // expr_animation: "%" "identifier"
#line 987 "parser.ypp"
        { yylhs.value.as < expr_animation::ptr > () = expr_animation::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3859 "parser.cpp"
    break;

  case 257: // expr_animtree: "#animtree"
#line 992 "parser.ypp"
        { yylhs.value.as < expr_animtree::ptr > () = expr_animtree::make(yylhs.location); }
#line 3865 "parser.cpp"
    break;

  case 258: // expr_identifier_nosize: "identifier"
#line 997 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3871 "parser.cpp"
    break;

  case 259: // expr_identifier: "identifier"
#line 1002 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3877 "parser.cpp"
    break;

  case 260: // expr_identifier: "size"
#line 1004 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, "size"); }
#line 3883 "parser.cpp"
    break;

  case 261: // expr_path: "path" "/" "identifier"
#line 1009 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[2].value.as < std::string > () + "/" + yystack_[0].value.as < std::string > ()); }
#line 3889 "parser.cpp"
    break;

  case 262: // expr_path: "identifier"
#line 1011 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3895 "parser.cpp"
    break;

  case 263: // expr_path: "path"
#line 1013 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3901 "parser.cpp"
    break;

  case 264: // expr_istring: "localized string"
#line 1018 "parser.ypp"
        { yylhs.value.as < expr_istring::ptr > () = expr_istring::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3907 "parser.cpp"
    break;

  case 265: // expr_string: "string literal"
#line 1023 "parser.ypp"
        { yylhs.value.as < expr_string::ptr > () = expr_string::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3913 "parser.cpp"
    break;

  case 266: // expr_vector: "(" expr "," expr "," expr ")"
#line 1028 "parser.ypp"
        { yylhs.value.as < expr_vector::ptr > () = expr_vector::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3919 "parser.cpp"
    break;

  case 267: // expr_hash: "hash string"
#line 1033 "parser.ypp"
        { yylhs.value.as < expr_hash::ptr > () = expr_hash::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3925 "parser.cpp"
    break;

  case 268: // expr_float: "-" "float"
#line 1038 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3931 "parser.cpp"
    break;

  case 269: // expr_float: "float"
#line 1040 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3937 "parser.cpp"
    break;

  case 270: // expr_integer: "-" "integer"
#line 1045 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3943 "parser.cpp"
    break;

  case 271: // expr_integer: "integer"
#line 1047 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3949 "parser.cpp"
    break;

  case 272: // expr_false: "false"
#line 1052 "parser.ypp"
        { yylhs.value.as < expr_false::ptr > () = expr_false::make(yylhs.location); }
#line 3955 "parser.cpp"
    break;

  case 273: // expr_true: "true"
#line 1057 "parser.ypp"
        { yylhs.value.as < expr_true::ptr > () = expr_true::make(yylhs.location); }
#line 3961 "parser.cpp"
    break;


#line 3965 "parser.cpp"

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
  "private", "endon", "notify", "wait", "waittill", "waittillmatch",
  "waittillframeend", "if", "else", "do", "while", "for", "foreach", "in",
  "switch", "case", "default", "break", "continue", "return", "prof_begin",
  "prof_end", "thread", "true", "false", "undefined", "size", "game",
  "self", "anim", "level", "const", "getnextarraykey", "getfirstarraykey",
  "getdvarcoloralpha", "getdvarcolorblue", "getdvarcolorgreen",
  "getdvarcolorred", "getdvarvector", "getdvarfloat", "getdvarint",
  "getdvar", "gettime", "abs", "vectortoangles", "angleclamp180",
  "anglestoforward", "anglestoright", "anglestoup", "vectorscale",
  "isdefined", "(", ")", "{", "}", "[", "]", ",", ".", "..", "...", "::",
  ":", ";", "?", "++", "--", "<<", ">>", "||", "&&", "==", "!=", "<=",
  ">=", "<", ">", "!", "~", "=", "+=", "-=", "*=", "/=", "%=", "|=", "&=",
  "^=", ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/", "%", "path",
  "identifier", "string literal", "localized string", "hash string",
  "float", "integer", "SIZEOF", "THEN", "TERN", "NEG", "ANIMREF", "PREINC",
  "PREDEC", "POSTINC", "POSTDEC", "$accept", "root", "program", "inline",
  "include", "declaration", "decl_usingtree", "decl_function", "stmt",
  "stmt_or_dev", "stmt_list", "stmt_or_dev_list", "stmt_dev", "stmt_comp",
  "stmt_expr", "stmt_call", "stmt_const", "stmt_assign", "stmt_endon",
  "stmt_notify", "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
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


  const short parser::yypact_ninf_ = -432;

  const short parser::yytable_ninf_ = -263;

  const short
  parser::yypact_[] =
  {
     239,  -432,  -432,   -38,   -38,   -60,   -21,   -21,   -21,  -432,
    -432,  -432,    36,   363,  -432,  -432,  -432,  -432,  -432,   -18,
     -56,  -432,    10,    25,   -58,    23,    52,    58,  -432,  -432,
    -432,  -432,  -432,   -21,    -2,  -432,  -432,  -432,    60,   -21,
     -21,   -21,   -20,  -432,    38,  -432,    57,   -16,    -8,    -1,
      62,   -21,  1426,  -432,    62,    62,    62,  1315,  -432,  -432,
      38,  -432,   -12,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
      70,    72,    75,    78,    82,    84,    86,    87,    93,    97,
      98,   101,   102,   104,   110,   114,   117,   118,   120,  1426,
      15,   -21,  1426,  1426,   807,    65,   111,  -432,  -432,  -432,
    -432,  1182,  -432,  -432,  -432,  -432,  -432,  -432,   -33,     9,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,   121,  -432,
    -432,  -432,  -432,  -432,   124,   125,   128,   129,   130,   131,
    -432,  -432,   268,   361,  -432,  -432,   375,  -432,  -432,   395,
     545,   582,   660,  -432,  -432,    -3,   132,  -432,   115,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  1676,  1426,
     126,   140,  1804,   144,   148,   151,   152,   -74,   143,   146,
     159,   846,   155,   160,   -21,  -432,   168,  -432,  1467,  1467,
    -432,  -432,  1612,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,   162,   163,
     165,   167,   173,   121,   124,   125,   128,   129,   130,   131,
    -432,  -432,   720,  -432,  -432,  -432,  -432,   197,   188,   199,
     201,   194,  1426,  1426,  1426,  1426,  1426,  1426,  1426,  1426,
    1426,  1426,   208,  1426,  1426,  1426,  1426,  1426,  1426,  1426,
    1426,  1814,  1426,  -432,  -432,  -432,  -432,  1426,  -432,  -432,
    -432,  -432,   268,   361,  -432,   662,    -3,  -432,  1426,  1426,
    1426,  1426,  1426,  1426,  1426,  1426,  1426,  1426,  1426,  1426,
    1426,  1426,  1426,  1426,  1426,  1426,  1426,  1426,  1426,  1426,
    1426,  1426,  1426,  1426,  1509,   -19,  -432,  -432,   197,  1426,
     -21,   238,  -432,  -432,  -432,  1740,  3148,  -432,  1426,   258,
    1426,  1111,   -21,  1426,   170,   207,   209,  -432,  -432,  -432,
    -432,  3183,  1426,  1426,   193,   662,   662,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,   224,   225,   226,   229,   182,
    -432,  -432,  1426,  1426,  1426,  1426,  1426,  1426,  1426,  1426,
    1426,  1426,  1426,   -21,  1426,  1426,   -21,  2995,  1965,  1999,
    2012,  2046,  2059,  2093,  2106,  2140,  2153,  -432,  2187,  2200,
    2234,  2247,  2281,  2294,  3036,  2328,  -432,  1426,  1505,  2341,
    3113,   280,   280,  1195,  1847,  1800,  1800,   147,   147,   147,
     147,  1324,   925,  1336,   -80,   -80,  -432,  -432,  -432,  2618,
    2660,  2702,  2744,  2786,  2828,  2870,  1026,  2912,  -432,  -432,
    -432,  1182,     2,  -432,   232,  -432,  -432,  -432,  -432,  -432,
    2375,   234,  2388,   235,  -432,  -432,  -432,   896,   -10,  2422,
    -432,  -432,  -432,     5,    11,  1426,  1426,  1426,  1426,  1426,
    1182,  1182,  1182,  1182,  1182,  1182,  1182,  1182,  1182,  1182,
    1182,   232,  2954,    20,   236,  1426,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  1426,  -432,  3077,   241,  1426,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  1426,  1426,  1804,  1426,  1804,
    1426,  1426,   -21,    62,   240,   242,  3218,  2435,  1860,  1906,
    1952,   250,  -432,  1426,  2469,  2482,  1426,   257,  1182,  1182,
      37,   302,  2516,  -432,  1182,   253,  2529,   304,  -432,  -432,
    -432,  -432,   255,   262,  1426,   264,  1426,   265,  1426,   269,
      48,  -432,  -432,  2563,  1426,  -432,  1804,   266,  1111,  1804,
    1426,  -432,  -432,   274,   282,  -432,   284,  -432,   285,  1426,
    -432,  -432,    49,  -432,  -432,   288,  -432,  2576,   283,   286,
     287,    59,  -432,  1804,  1804,  -432,  -432,  -432,  -432,  -432,
    -432
  };

  const short
  parser::yydefact_[] =
  {
       3,    14,    15,     0,     0,     0,     0,     0,     0,   260,
       8,   259,     0,     2,     9,    10,    11,    16,    17,     0,
     263,   262,     0,     0,     0,     0,     0,     0,     1,     4,
       5,     6,     7,   202,     0,    12,    13,   265,     0,   202,
     202,   202,     0,   200,   201,   261,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,     0,    19,   198,
     199,   257,     0,   273,   272,   251,   252,   253,   254,   255,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   259,   264,   267,   269,
     271,   203,    97,    98,    99,   136,   137,   138,   139,   140,
     188,   189,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,     0,   165,   166,   167,
     168,   169,   170,   171,   172,   173,     0,   174,   175,   176,
     177,   178,   179,   180,   181,    20,    21,    22,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,     0,    56,     0,     0,
      47,    54,     0,    48,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,     0,     0,
       0,   241,   242,     0,     0,     0,     0,     0,     0,     0,
     243,   244,     0,   245,   246,   247,   248,   249,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   250,   227,   187,   182,     0,   268,   270,
     241,   242,   185,   186,   184,     0,   183,   256,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   190,   191,     0,   205,
       0,     0,    58,    52,    50,     0,     0,    79,     0,     0,
       0,    64,     0,     0,     0,     0,     0,    90,    91,    92,
      94,     0,   205,   205,     0,   102,   104,    59,    55,    53,
      69,    70,    68,    65,    66,     0,     0,     0,     0,     0,
     103,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   205,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   218,     0,     0,
       0,     0,     0,     0,     0,     0,   240,     0,     0,     0,
       0,   129,   130,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   131,   132,   133,   134,   135,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   238,   258,
     237,   207,     0,   204,   228,   239,    57,    51,    49,    74,
       0,     0,     0,     0,    62,    63,    61,     0,     0,     0,
      89,    88,    93,     0,     0,     0,     0,     0,     0,     0,
     106,   112,   113,   114,   115,   116,   107,   108,   109,   111,
     110,     0,     0,     0,     0,     0,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   219,   220,   221,   222,   223,
     224,     0,   226,     0,     0,     0,   230,   231,   232,   233,
     234,   235,   236,   229,   192,     0,   205,     0,     0,     0,
     101,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   194,   205,     0,     0,     0,     0,   117,   206,
       0,    80,     0,    82,   100,     0,     0,     0,    87,    95,
      96,    67,     0,     0,   205,     0,   205,     0,   205,     0,
       0,   208,   225,     0,   205,   193,     0,     0,    64,     0,
       0,    71,    73,     0,   204,    76,   204,    78,   204,   205,
     195,   266,     0,    81,    83,     0,    85,     0,     0,     0,
       0,     0,   196,     0,     0,    72,    75,    77,   197,    84,
      86
  };

  const short
  parser::yypgoto_[] =
  {
    -432,  -432,  -432,   331,   342,   350,  -432,  -432,  -142,   184,
    -432,  -432,  -432,   -32,  -161,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,
    -432,  -432,  -432,  -432,  -432,  -432,  -432,  -432,   963,  -432,
    -309,  -307,  -297,  -432,  -432,  -432,  -432,  -432,  -432,   -48,
     -36,  -126,  -106,   113,   332,  -218,  -431,  -432,  -432,  -432,
    -432,  -432,  -432,    -7,  -432,  -432,  -432,  -432,  -432,    31,
      46,    54,   100,   112,   145,  -432,  -432,   202,   214,  -432,
     296,   297,  -432,  -432,   464,   483,   564,   621,  -432,  -432,
    -432,     0,     8,  -432,     1,  -432,  -432,  -432,   215,  -432,
    -432
  };

  const short
  parser::yydefgoto_[] =
  {
       0,    12,    13,    14,    15,    16,    17,    18,   180,   181,
     305,   182,   183,   184,   423,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   411,   515,
     208,   209,   210,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,    42,    43,   543,   413,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     410,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154
  };

  const short
  parser::yytable_[] =
  {
      19,  -241,   424,    24,   425,  -241,    25,    26,    27,   211,
     296,    22,    23,    19,   426,   491,   304,     9,    58,   408,
     309,   212,   155,   156,   157,    38,     9,   284,   285,   286,
     297,  -249,   314,    44,  -241,  -249,    28,  -241,    37,    44,
      44,    44,   100,  -242,    50,    33,   260,  -242,    54,    51,
     213,    60,    34,    51,    37,   229,    55,   227,   261,   492,
     299,    51,   230,    56,  -249,   228,   484,  -249,    51,   494,
     231,   485,    20,    21,   485,   495,  -242,  -241,  -241,  -242,
     485,   412,   252,   253,   502,    35,    39,   213,   214,   485,
      11,   254,   409,   544,   266,   546,   296,   548,    20,    96,
      36,   535,   228,   215,   433,   434,   485,  -249,  -249,    45,
     211,   216,   550,   562,   211,    40,   297,   485,   485,  -242,
    -242,    41,   212,   568,    46,   214,   212,    57,   485,    52,
     260,   260,    53,   232,   211,   233,   298,   453,   234,   296,
     215,   235,   261,   261,   228,   236,   212,   237,   216,   238,
     239,   213,    47,    48,    49,   213,   240,   217,   227,   297,
     241,   242,   227,   418,   243,   244,   228,   245,   315,   218,
     228,   213,   213,   246,   324,   213,   267,   247,   227,   227,
     248,   249,   227,   250,  -262,   301,   228,   228,   287,   214,
     228,   288,   289,   214,   217,   290,   291,   292,   293,   296,
     296,   307,   219,   308,   215,   300,   218,   310,   215,   214,
     214,   311,   216,   214,   312,   313,   216,   317,   322,   297,
     297,   318,   298,   323,   215,   215,   269,   270,   215,   424,
     228,   425,   216,   216,   319,   252,   216,   330,   331,   219,
     332,   426,   333,     1,     2,     3,     4,     5,   334,     6,
       7,     8,   282,   283,   284,   285,   286,   211,   217,   220,
     299,   353,   217,   260,   355,   298,   354,   356,   510,   212,
     218,   221,   367,   228,   218,   261,   415,     9,   217,   217,
     421,   430,   217,   431,   435,   530,   259,   436,   437,   438,
     218,   218,   439,   409,   218,   486,   262,   488,   213,   503,
     414,   296,  -243,   219,   213,   227,  -243,   219,   263,   507,
     490,   227,   428,   228,    10,   519,   552,   520,   529,   228,
     534,   297,   536,   219,   219,   298,   298,   219,   538,   540,
     541,   561,   549,   228,   228,  -243,   214,   542,  -243,   545,
     547,   554,   214,   485,    30,   511,   558,   513,   559,   560,
      11,   215,   563,   451,   222,    31,   454,   215,   565,   216,
     220,   566,   567,    32,   220,   216,   329,     1,     2,     3,
       4,     5,   221,     6,     7,     8,   221,   555,  -243,  -243,
     220,   220,   316,    59,   220,   282,   283,   284,   285,   286,
     264,   265,   221,   221,   553,  -244,   221,   556,     0,  -244,
       0,     9,     0,     0,     0,   217,     0,     0,     0,    62,
       0,   217,     0,     9,     0,     0,     0,   218,     0,     0,
       0,   569,   570,   218,     0,     0,     0,   298,  -244,  -245,
       0,  -244,     0,  -245,     0,   228,     0,     0,    29,   211,
       0,   211,   294,     0,     0,   295,     0,     0,     0,     0,
     219,   212,     0,   212,     0,   222,   219,     0,     0,   222,
       0,   518,  -245,     0,     0,  -245,     0,     0,     0,     0,
       0,  -244,  -244,     0,    11,   325,   326,     0,     0,   222,
     213,     0,   213,     0,     0,    20,    96,   227,   211,   227,
     260,   211,   517,     0,     0,   228,     0,   228,     0,     0,
     212,     0,   261,   212,     0,  -245,  -245,   220,     0,     0,
       0,     0,     0,   220,     0,   211,   211,     0,   214,   221,
     214,   223,     0,     0,     0,   221,     0,   212,   212,   213,
       0,   213,   213,   215,     0,   215,   227,     0,   227,   227,
     224,   216,     0,   216,   228,     0,   228,   228,     0,     0,
       0,     0,     0,     0,     0,     0,   213,   213,   223,     0,
       0,     0,     0,   227,   227,     0,     0,   214,     0,   214,
     214,   228,   228,     0,     0,     0,     0,   224,     0,  -246,
       0,     0,   215,  -246,   215,   215,     0,   217,     0,   217,
     216,     0,   216,   216,   214,   214,     0,     0,     0,   218,
       0,   218,   222,     0,     0,     0,     0,     0,   427,   215,
     215,     0,  -246,     0,     0,  -246,  -247,   216,   216,     0,
    -247,   225,   223,     0,     0,     0,   223,     0,     0,     0,
       0,     0,   219,     0,   219,     0,   217,     0,   217,   217,
       0,   224,   223,   223,     0,   224,   223,     0,   218,  -247,
     218,   218,  -247,     0,     0,  -246,  -246,     0,   225,     0,
       0,   224,   224,   217,   217,   224,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   218,   218,     0,   226,     0,
       0,   219,     0,   219,   219,     0,     0,     0,     0,   220,
       0,   220,  -247,  -247,  -248,     0,    62,     0,  -248,     0,
       9,   221,     0,   221,     0,     0,     0,     0,   219,   219,
       0,     0,     0,     0,     0,   226,     0,     0,     0,     0,
       0,     0,   225,     0,     0,     0,   225,  -248,     0,   294,
    -248,     0,   339,   335,   336,     0,   337,   338,   220,     0,
     220,   220,   225,   225,     0,     0,   225,     0,     0,     0,
     221,     0,   221,   221,    62,     0,     0,     0,     9,     0,
       0,     0,     0,     0,     0,   220,   220,     0,     0,   223,
    -248,  -248,    20,    96,     0,   223,     0,   221,   221,   226,
       0,     0,     0,   226,   222,     0,   222,   294,   224,     0,
     339,     0,     0,     0,   224,     0,     0,   340,   341,   226,
     226,     0,     0,   226,     0,     0,     0,     0,     0,     0,
       0,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,     0,     0,     0,     0,     0,     0,     0,     0,
      20,    96,     0,   222,     0,   427,   222,     0,     0,     0,
       0,    62,     0,     0,     0,     9,    66,    67,    68,    69,
       0,     0,     0,     0,     0,    61,     0,    76,     0,     0,
     222,   222,     0,    82,    83,    84,    85,    86,    87,   225,
     257,     0,     0,     0,   176,   225,     0,     0,     0,     0,
      62,    63,    64,    65,     9,    66,    67,    68,    69,     0,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,     0,    90,     0,     0,     0,    20,    96,    91,
       0,   320,   258,   259,     0,     0,   226,     0,     0,     0,
      62,     0,   226,     0,     9,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   223,    94,   223,     0,    95,    20,    96,    37,    97,
      98,    99,   100,   294,     0,     0,   339,     0,     0,     0,
     224,     0,   224,   340,   341,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,     0,     0,
     223,     0,   223,   223,   269,   270,    20,    96,   273,   274,
     275,   276,   277,   278,     0,   101,     0,     0,     0,   224,
       0,   224,   224,     0,     0,     0,     0,   223,   223,     0,
     282,   283,   284,   285,   286,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   224,   224,     0,     0,
       0,   225,   251,   225,     0,   255,   256,     0,     0,     0,
      62,    63,    64,    65,     9,    66,    67,    68,    69,     0,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,     0,   406,   253,     0,     0,     0,     0,    91,
     225,     0,   225,   225,     0,     0,     0,     0,   226,     0,
     226,     0,     0,     0,     0,    92,    93,     0,     0,     0,
       0,     0,   306,     0,     0,     0,     0,   225,   225,     0,
       0,     0,    94,     0,   321,    95,    20,    96,    37,    97,
      98,    99,   100,     0,     0,    62,     0,     0,     0,     9,
      66,    67,    68,    69,     0,     0,     0,   226,     0,   226,
     226,    76,     0,     0,     0,     0,     0,    82,    83,    84,
      85,    86,    87,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,     0,   226,   226,     0,     0,   178,   179,
       0,     0,     0,     0,     0,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,     0,   368,   369,   370,   371,
     372,   373,   374,   375,     0,   378,     0,     0,     0,     0,
     379,    20,    96,     0,     0,     0,     0,     0,     0,     0,
       0,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,   404,   405,   407,   268,     0,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   420,     0,   422,   269,   270,   429,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,     0,     0,     0,     0,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,     0,   452,     0,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     159,     0,     0,   160,   161,     0,   162,   163,   164,   165,
     473,   166,   167,   168,   169,   170,   171,   172,   173,    62,
       0,     0,     0,     9,    66,    67,    68,    69,   174,     0,
       0,     0,     0,     0,     0,    76,     0,     0,     0,   378,
       0,    82,    83,    84,    85,    86,    87,     0,     0,     0,
      57,   175,   176,     0,     0,     0,     0,     0,     0,     0,
     177,     0,   178,   179,     0,     0,     0,     0,   496,   497,
     498,   499,   500,   269,   270,     0,     0,   273,   274,   275,
     276,   277,   278,     0,     0,   269,   270,     0,   504,   273,
     274,   275,   276,   277,   278,    20,    96,   280,   281,   282,
     283,   284,   285,   286,   505,    61,     0,     0,   508,   280,
       0,   282,   283,   284,   285,   286,     0,     0,   509,     0,
       0,   512,     0,   514,   516,     0,     0,     0,     0,     0,
      62,    63,    64,    65,     9,    66,    67,    68,    69,   533,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,     0,    90,     0,     0,     0,     0,     0,    91,
       0,    62,     0,   557,     0,     9,    66,    67,    68,    69,
       0,     0,     0,     0,     0,    92,    93,    76,    61,     0,
       0,     0,     0,    82,    83,    84,    85,    86,    87,     0,
       0,     0,    94,     0,   176,    95,    20,    96,    37,    97,
      98,    99,   100,    62,    63,    64,    65,     9,    66,    67,
      68,    69,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   474,     0,     0,   406,    20,    96,     0,
       0,   268,    91,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,     0,     0,     0,     0,    92,    93,
       0,     0,     0,     0,     0,     0,     0,   279,   280,   281,
     282,   283,   284,   285,   286,    94,   158,     0,    95,    20,
      96,    37,    97,    98,    99,   100,     0,   159,     0,     0,
     160,   161,     0,   162,   163,   164,   165,     0,   166,   167,
     168,   169,   170,   171,   172,   173,    62,     0,     0,     0,
       9,    66,    67,    68,    69,   174,     0,     0,     0,     0,
       0,     0,    76,     0,     0,     0,     0,     0,    82,    83,
      84,    85,    86,    87,     0,     0,     0,    57,   327,   176,
       0,   302,     0,     0,     0,     0,     0,   328,     0,   178,
     179,   159,     0,     0,   160,   161,     0,   162,   163,   164,
     165,     0,   166,   167,   168,   169,   170,   171,   172,   173,
      62,     0,     0,     0,     9,    66,    67,    68,    69,   174,
       0,     0,    20,    96,     0,     0,    76,     0,     0,     0,
       0,     0,    82,    83,    84,    85,    86,    87,     0,     0,
       0,    57,     0,   176,     0,   416,     0,     0,     0,     0,
       0,   303,     0,   178,   179,   159,     0,     0,   160,   161,
       0,   162,   163,   164,   165,     0,   166,   167,   168,   169,
     170,   171,   172,   173,    62,     0,     0,     0,     9,    66,
      67,    68,    69,   174,     0,     0,    20,    96,     0,     0,
      76,     0,     0,     0,     0,     0,    82,    83,    84,    85,
      86,    87,     0,     0,     0,    57,     0,   176,     0,     0,
       0,     0,     0,     0,     0,   417,     0,   178,   179,   159,
       0,     0,   160,   161,     0,   162,   163,   164,   165,     0,
     166,   167,   168,   169,   170,   171,   172,   173,    62,     0,
       0,     0,     9,    66,    67,    68,    69,   174,     0,     0,
      20,    96,     0,     0,    76,     0,     0,     0,     0,     0,
      82,    83,    84,    85,    86,    87,     0,     0,     0,    57,
       0,   176,     0,     0,     0,     0,     0,     0,   376,   269,
     270,   178,   179,   377,     0,   275,   276,   277,   278,     0,
     268,     0,     0,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,     0,     0,   282,   283,   284,   285,   286,
       0,     0,     0,     0,    20,    96,   279,   280,   281,   282,
     283,   284,   285,   286,   523,     0,   269,   270,     0,   524,
     273,   274,   275,   276,   277,   278,   268,     0,     0,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,     0,     0,     0,
       0,     0,   279,   280,   281,   282,   283,   284,   285,   286,
     525,     0,     0,     0,     0,   526,     0,     0,     0,     0,
       0,     0,   268,     0,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   279,   280,
     281,   282,   283,   284,   285,   286,   527,     0,     0,     0,
       0,   528,     0,     0,     0,     0,     0,     0,   268,   456,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   268,     0,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,     0,   457,     0,     0,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   268,   458,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   268,     0,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,     0,
     459,     0,     0,     0,   279,   280,   281,   282,   283,   284,
     285,   286,   268,   460,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   268,     0,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,     0,   461,     0,     0,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   268,
     462,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   268,     0,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,     0,   463,     0,     0,     0,   279,   280,
     281,   282,   283,   284,   285,   286,   268,   464,     0,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   268,
       0,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
       0,   465,     0,     0,     0,   279,   280,   281,   282,   283,
     284,   285,   286,   268,   466,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   268,     0,     0,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,     0,   467,     0,
       0,     0,   279,   280,   281,   282,   283,   284,   285,   286,
     268,   468,     0,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   268,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,     0,   469,     0,     0,     0,   279,
     280,   281,   282,   283,   284,   285,   286,   268,   470,     0,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     268,     0,     0,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,     0,   472,     0,     0,     0,   279,   280,   281,   282,
     283,   284,   285,   286,   268,   376,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   268,     0,     0,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,     0,   487,
       0,     0,     0,   279,   280,   281,   282,   283,   284,   285,
     286,   268,   489,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   268,     0,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,     0,   493,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   268,   522,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   268,     0,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,     0,   531,     0,     0,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   268,   532,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   268,     0,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,     0,
     537,     0,     0,     0,   279,   280,   281,   282,   283,   284,
     285,   286,   268,   539,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   268,     0,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,     0,   551,     0,     0,
       0,   279,   280,   281,   282,   283,   284,   285,   286,   268,
     564,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   268,     0,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,     0,     0,     0,     0,     0,   279,   280,
     281,   282,   283,   284,   285,   286,   476,     0,     0,     0,
       0,     0,     0,     0,   268,     0,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   477,     0,
       0,     0,     0,     0,     0,     0,   268,     0,     0,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   279,   280,   281,   282,   283,   284,   285,   286,
     478,     0,     0,     0,     0,     0,     0,     0,   268,     0,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   279,   280,   281,   282,   283,   284,
     285,   286,   479,     0,     0,     0,     0,     0,     0,     0,
     268,     0,     0,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   279,   280,   281,   282,
     283,   284,   285,   286,   480,     0,     0,     0,     0,     0,
       0,     0,   268,     0,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   279,   280,
     281,   282,   283,   284,   285,   286,   481,     0,     0,     0,
       0,     0,     0,     0,   268,     0,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   482,     0,
       0,     0,     0,     0,     0,     0,   268,     0,     0,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   279,   280,   281,   282,   283,   284,   285,   286,
     483,     0,     0,     0,     0,     0,     0,     0,   268,     0,
       0,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   279,   280,   281,   282,   283,   284,
     285,   286,   501,     0,     0,     0,     0,     0,     0,     0,
     268,     0,     0,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   279,   280,   281,   282,
     283,   284,   285,   286,   455,     0,     0,     0,     0,     0,
       0,   268,     0,     0,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   279,   280,   281,
     282,   283,   284,   285,   286,   471,     0,     0,     0,     0,
       0,     0,   268,     0,     0,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   279,   280,
     281,   282,   283,   284,   285,   286,   506,     0,     0,     0,
       0,     0,     0,   268,     0,     0,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   279,
     280,   281,   282,   283,   284,   285,   286,   475,     0,   268,
       0,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   279,   280,   281,   282,   283,
     284,   285,   286,   419,   268,     0,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   432,   268,
       0,     0,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   279,   280,   281,   282,   283,
     284,   285,   286,   521,   268,     0,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     279,   280,   281,   282,   283,   284,   285,   286
  };

  const short
  parser::yycheck_[] =
  {
       0,    34,   311,    63,   311,    38,     6,     7,     8,    57,
     136,     3,     4,    13,   311,    25,   158,    38,    50,    38,
     162,    57,    54,    55,    56,    24,    38,   107,   108,   109,
     136,    34,   106,    33,    67,    38,     0,    70,   112,    39,
      40,    41,   116,    34,    64,    63,    94,    38,    64,    69,
      57,    51,   108,    69,   112,    67,    64,    57,    94,    69,
      63,    69,    62,    64,    67,    57,    64,    70,    69,    64,
      62,    69,   110,   111,    69,    64,    67,   110,   111,    70,
      69,   299,    67,    68,    64,    75,    63,    94,    57,    69,
     111,    91,   111,   524,    94,   526,   222,   528,   110,   111,
      75,    64,    94,    57,   322,   323,    69,   110,   111,   111,
     158,    57,    64,    64,   162,    63,   222,    69,    69,   110,
     111,    63,   158,    64,    64,    94,   162,    65,    69,    91,
     178,   179,    75,    63,   182,    63,   136,   355,    63,   265,
      94,    63,   178,   179,   136,    63,   182,    63,    94,    63,
      63,   158,    39,    40,    41,   162,    63,    57,   158,   265,
      63,    63,   162,   305,    63,    63,   158,    63,   167,    57,
     162,   178,   179,    63,   174,   182,   111,    63,   178,   179,
      63,    63,   182,    63,    73,    70,   178,   179,    67,   158,
     182,    67,    67,   162,    94,    67,    67,    67,    67,   325,
     326,    75,    57,    63,   158,    73,    94,    63,   162,   178,
     179,    63,   158,   182,    63,    63,   162,    74,    63,   325,
     326,    75,   222,    63,   178,   179,    79,    80,   182,   538,
     222,   538,   178,   179,    75,    67,   182,    75,    75,    94,
      75,   538,    75,     4,     5,     6,     7,     8,    75,    10,
      11,    12,   105,   106,   107,   108,   109,   305,   158,    57,
      63,    73,   162,   311,    63,   265,    67,    73,   486,   305,
     158,    57,    64,   265,   162,   311,    38,    38,   178,   179,
      22,    74,   182,    74,    91,   503,   116,    63,    63,    63,
     178,   179,    63,   111,   182,    63,    94,    63,   305,    63,
     300,   427,    34,   158,   311,   305,    38,   162,    94,    68,
      75,   311,   312,   305,    75,    75,   534,    75,    68,   311,
      63,   427,    20,   178,   179,   325,   326,   182,    75,    25,
      75,   549,    63,   325,   326,    67,   305,    75,    70,    75,
      75,    75,   311,    69,    13,   487,    64,   489,    64,    64,
     111,   305,    64,   353,    57,    13,   356,   311,    75,   305,
     158,    75,    75,    13,   162,   311,   182,     4,     5,     6,
       7,     8,   158,    10,    11,    12,   162,   538,   110,   111,
     178,   179,   167,    51,   182,   105,   106,   107,   108,   109,
      94,    94,   178,   179,   536,    34,   182,   539,    -1,    38,
      -1,    38,    -1,    -1,    -1,   305,    -1,    -1,    -1,    34,
      -1,   311,    -1,    38,    -1,    -1,    -1,   305,    -1,    -1,
      -1,   563,   564,   311,    -1,    -1,    -1,   427,    67,    34,
      -1,    70,    -1,    38,    -1,   427,    -1,    -1,    75,   487,
      -1,   489,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
     305,   487,    -1,   489,    -1,   158,   311,    -1,    -1,   162,
      -1,   493,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,   110,   111,    -1,   111,   178,   179,    -1,    -1,   182,
     487,    -1,   489,    -1,    -1,   110,   111,   487,   536,   489,
     538,   539,   492,    -1,    -1,   487,    -1,   489,    -1,    -1,
     536,    -1,   538,   539,    -1,   110,   111,   305,    -1,    -1,
      -1,    -1,    -1,   311,    -1,   563,   564,    -1,   487,   305,
     489,    57,    -1,    -1,    -1,   311,    -1,   563,   564,   536,
      -1,   538,   539,   487,    -1,   489,   536,    -1,   538,   539,
      57,   487,    -1,   489,   536,    -1,   538,   539,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   563,   564,    94,    -1,
      -1,    -1,    -1,   563,   564,    -1,    -1,   536,    -1,   538,
     539,   563,   564,    -1,    -1,    -1,    -1,    94,    -1,    34,
      -1,    -1,   536,    38,   538,   539,    -1,   487,    -1,   489,
     536,    -1,   538,   539,   563,   564,    -1,    -1,    -1,   487,
      -1,   489,   305,    -1,    -1,    -1,    -1,    -1,   311,   563,
     564,    -1,    67,    -1,    -1,    70,    34,   563,   564,    -1,
      38,    57,   158,    -1,    -1,    -1,   162,    -1,    -1,    -1,
      -1,    -1,   487,    -1,   489,    -1,   536,    -1,   538,   539,
      -1,   158,   178,   179,    -1,   162,   182,    -1,   536,    67,
     538,   539,    70,    -1,    -1,   110,   111,    -1,    94,    -1,
      -1,   178,   179,   563,   564,   182,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   563,   564,    -1,    57,    -1,
      -1,   536,    -1,   538,   539,    -1,    -1,    -1,    -1,   487,
      -1,   489,   110,   111,    34,    -1,    34,    -1,    38,    -1,
      38,   487,    -1,   489,    -1,    -1,    -1,    -1,   563,   564,
      -1,    -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,
      -1,    -1,   158,    -1,    -1,    -1,   162,    67,    -1,    67,
      70,    -1,    70,    13,    14,    -1,    16,    17,   536,    -1,
     538,   539,   178,   179,    -1,    -1,   182,    -1,    -1,    -1,
     536,    -1,   538,   539,    34,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,   563,   564,    -1,    -1,   305,
     110,   111,   110,   111,    -1,   311,    -1,   563,   564,   158,
      -1,    -1,    -1,   162,   487,    -1,   489,    67,   305,    -1,
      70,    -1,    -1,    -1,   311,    -1,    -1,    77,    78,   178,
     179,    -1,    -1,   182,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     110,   111,    -1,   536,    -1,   538,   539,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,     9,    -1,    50,    -1,    -1,
     563,   564,    -1,    56,    57,    58,    59,    60,    61,   305,
      63,    -1,    -1,    -1,    67,   311,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    67,    -1,    -1,    -1,   110,   111,    73,
      -1,    75,   115,   116,    -1,    -1,   305,    -1,    -1,    -1,
      34,    -1,   311,    -1,    38,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   487,   106,   489,    -1,   109,   110,   111,   112,   113,
     114,   115,   116,    67,    -1,    -1,    70,    -1,    -1,    -1,
     487,    -1,   489,    77,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,    -1,    -1,
     536,    -1,   538,   539,    79,    80,   110,   111,    83,    84,
      85,    86,    87,    88,    -1,    52,    -1,    -1,    -1,   536,
      -1,   538,   539,    -1,    -1,    -1,    -1,   563,   564,    -1,
     105,   106,   107,   108,   109,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   563,   564,    -1,    -1,
      -1,   487,    89,   489,    -1,    92,    93,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,    -1,    73,
     536,    -1,   538,   539,    -1,    -1,    -1,    -1,   487,    -1,
     489,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    -1,
      -1,    -1,   159,    -1,    -1,    -1,    -1,   563,   564,    -1,
      -1,    -1,   106,    -1,   171,   109,   110,   111,   112,   113,
     114,   115,   116,    -1,    -1,    34,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    -1,    -1,    -1,   536,    -1,   538,
     539,    50,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      -1,    -1,    -1,    -1,   563,   564,    -1,    -1,    77,    78,
      -1,    -1,    -1,    -1,    -1,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,    -1,   243,   244,   245,   246,
     247,   248,   249,   250,    -1,   252,    -1,    -1,    -1,    -1,
     257,   110,   111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,   308,    -1,   310,    79,    80,   313,    82,    83,    84,
      85,    86,    87,    88,   102,   103,   104,   105,   106,   107,
     108,   109,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,    -1,   354,    -1,     4,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    18,    19,    -1,    21,    22,    23,    24,
     377,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,   406,
      -1,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    -1,    77,    78,    -1,    -1,    -1,    -1,   435,   436,
     437,   438,   439,    79,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    -1,    -1,    79,    80,    -1,   455,    83,
      84,    85,    86,    87,    88,   110,   111,   103,   104,   105,
     106,   107,   108,   109,   471,     9,    -1,    -1,   475,   103,
      -1,   105,   106,   107,   108,   109,    -1,    -1,   485,    -1,
      -1,   488,    -1,   490,   491,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,   506,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    73,
      -1,    34,    -1,   540,    -1,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    89,    90,    50,     9,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,   106,    -1,    67,   109,   110,   111,   112,   113,
     114,   115,   116,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    68,    -1,    -1,    67,   110,   111,    -1,
      -1,    76,    73,    -1,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    -1,    -1,    -1,    89,    90,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   106,     4,    -1,   109,   110,
     111,   112,   113,   114,   115,   116,    -1,    15,    -1,    -1,
      18,    19,    -1,    21,    22,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    65,    66,    67,
      -1,     5,    -1,    -1,    -1,    -1,    -1,    75,    -1,    77,
      78,    15,    -1,    -1,    18,    19,    -1,    21,    22,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      -1,    -1,   110,   111,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    65,    -1,    67,    -1,     5,    -1,    -1,    -1,    -1,
      -1,    75,    -1,    77,    78,    15,    -1,    -1,    18,    19,
      -1,    21,    22,    23,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    -1,    -1,   110,   111,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    -1,    -1,    -1,    65,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    -1,    77,    78,    15,
      -1,    -1,    18,    19,    -1,    21,    22,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    -1,    -1,
     110,   111,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    65,
      -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    64,    79,
      80,    77,    78,    69,    -1,    85,    86,    87,    88,    -1,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,   110,   111,   102,   103,   104,   105,
     106,   107,   108,   109,    64,    -1,    79,    80,    -1,    69,
      83,    84,    85,    86,    87,    88,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      64,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    64,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    64,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    76,    -1,    -1,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,   102,   103,   104,   105,   106,   107,
     108,   109,    -1,    64,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,    76,    64,    -1,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,   102,   103,   104,   105,   106,   107,   108,   109,    -1,
      64,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    76,    64,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    76,    -1,    -1,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,   102,   103,
     104,   105,   106,   107,   108,   109,    -1,    64,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,    76,
      64,    -1,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,   102,   103,   104,   105,   106,
     107,   108,   109,    -1,    64,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    76,    64,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    76,
      -1,    -1,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    64,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,    76,    64,    -1,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    64,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      76,    64,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    76,    -1,    -1,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,   102,   103,   104,   105,
     106,   107,   108,   109,    -1,    64,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,    76,    64,    -1,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,   102,   103,   104,   105,   106,   107,   108,
     109,    -1,    64,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    76,    64,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    76,    -1,    -1,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
     102,   103,   104,   105,   106,   107,   108,   109,    -1,    64,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,    76,    64,    -1,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,    64,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    76,    64,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    76,    -1,    -1,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,   102,   103,   104,   105,   106,   107,
     108,   109,    -1,    64,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,    76,    64,    -1,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,   102,   103,   104,   105,   106,   107,   108,   109,    -1,
      64,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    76,    64,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    76,    -1,    -1,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,   102,   103,
     104,   105,   106,   107,   108,   109,    -1,    64,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,    76,
      64,    -1,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,   102,   103,   104,   105,   106,
     107,   108,   109,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,    74,    -1,    76,
      -1,    -1,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,    75,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    75,    76,
      -1,    -1,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,    75,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     4,     5,     6,     7,     8,    10,    11,    12,    38,
      75,   111,   127,   128,   129,   130,   131,   132,   133,   217,
     110,   111,   218,   218,    63,   217,   217,   217,     0,    75,
     129,   130,   131,    63,   108,    75,    75,   112,   220,    63,
      63,    63,   179,   180,   217,   111,    64,   179,   179,   179,
      64,    69,    91,    75,    64,    64,    64,    65,   139,   180,
     217,     9,    34,    35,    36,    37,    39,    40,    41,    42,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      67,    73,    89,    90,   106,   109,   111,   113,   114,   115,
     116,   164,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   139,   139,   139,     4,    15,
      18,    19,    21,    22,    23,    24,    26,    27,    28,    29,
      30,    31,    32,    33,    43,    66,    67,    75,    77,    78,
     134,   135,   137,   138,   139,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   166,   167,
     168,   175,   176,   189,   195,   196,   197,   198,   199,   200,
     203,   204,   207,   210,   211,   212,   213,   217,   218,    67,
     217,   218,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,   164,    67,    68,   217,   164,   164,    63,   115,   116,
     175,   176,   203,   204,   206,   207,   217,   111,    76,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,   102,
     103,   104,   105,   106,   107,   108,   109,    67,    67,    67,
      67,    67,    67,    67,    67,    70,   177,   178,   217,    63,
      73,    70,     5,    75,   134,   136,   164,    75,    63,   134,
      63,    63,    63,    63,   106,   220,   224,    74,    75,    75,
      75,   164,    63,    63,   217,   207,   207,    66,    75,   135,
      75,    75,    75,    75,    75,    13,    14,    16,    17,    70,
      77,    78,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,    73,    67,    63,    73,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,    64,   164,   164,
     164,   164,   164,   164,   164,   164,    64,    69,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,    67,   164,    38,   111,
     216,   164,   181,   182,   217,    38,     5,    75,   134,    75,
     164,    22,   164,   140,   166,   167,   168,   207,   217,   164,
      74,    74,    75,   181,   181,    91,    63,    63,    63,    63,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   217,   164,   181,   217,    69,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    69,    64,   164,    68,    74,    68,    68,    68,    68,
      68,    68,    68,    68,    64,    69,    63,    64,    63,    64,
      75,    25,    69,    64,    64,    64,   164,   164,   164,   164,
     164,    68,    64,    63,   164,   164,    69,    68,   164,   164,
     181,   134,   164,   134,   164,   165,   164,   217,   139,    75,
      75,    75,    64,    64,    69,    64,    69,    64,    69,    68,
     181,    64,    64,   164,    63,    64,    20,    64,    75,    64,
      25,    75,    75,   181,   182,    75,   182,    75,   182,    63,
      64,    64,   181,   134,    75,   140,   134,   164,    64,    64,
      64,   181,    64,    64,    64,    75,    75,    75,    64,   134,
     134
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   126,   127,   127,   128,   128,   128,   128,   128,   128,
     128,   128,   129,   130,   131,   131,   131,   131,   132,   133,
     133,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   135,   135,   136,
     136,   136,   136,   137,   137,   137,   137,   138,   138,   139,
     139,   140,   140,   140,   140,   141,   141,   142,   143,   143,
     143,   144,   145,   145,   146,   147,   147,   148,   148,   149,
     150,   151,   152,   153,   154,   155,   155,   156,   157,   157,
     158,   159,   160,   161,   161,   162,   163,   164,   164,   164,
     165,   165,   166,   166,   167,   167,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   169,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   172,   173,   173,   173,   173,   174,   175,   175,
     176,   176,   177,   177,   177,   177,   178,   178,   179,   179,
     179,   179,   179,   180,   181,   181,   182,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   202,   203,
     203,   203,   203,   203,   203,   203,   203,   204,   205,   205,
     206,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     217,   218,   218,   218,   219,   220,   221,   222,   223,   223,
     224,   224,   225,   226
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     2,     1,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     5,     5,
       6,     6,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     1,     2,     1,     2,     1,     3,     2,     3,
       2,     1,     1,     1,     0,     2,     2,     5,     2,     2,
       2,     6,     8,     6,     3,     8,     6,     8,     6,     2,
       5,     7,     5,     7,     9,     7,     9,     5,     3,     3,
       2,     2,     2,     3,     2,     5,     5,     1,     1,     1,
       1,     0,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     1,     1,
       2,     2,     4,     6,     5,     7,     8,     9,     3,     3,
       1,     1,     0,     3,     1,     0,     3,     1,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     4,
       4,     4,     4,     4,     4,     6,     4,     2,     3,     4,
       4,     4,     4,     4,     4,     4,     4,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     7,     1,     2,     1,
       2,     1,     1,     1
  };




#if ARCDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   297,   297,   298,   302,   304,   306,   308,   310,   312,
     314,   316,   321,   325,   330,   331,   332,   333,   337,   342,
     344,   346,   348,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   380,   381,   385,
     387,   389,   391,   396,   398,   400,   402,   407,   408,   412,
     413,   417,   419,   421,   424,   428,   430,   435,   440,   442,
     444,   449,   454,   456,   461,   466,   468,   473,   475,   480,
     485,   490,   495,   500,   505,   510,   516,   524,   531,   533,
     538,   543,   548,   553,   555,   560,   565,   570,   571,   572,
     576,   577,   581,   583,   588,   590,   595,   597,   599,   601,
     603,   605,   607,   609,   611,   613,   615,   620,   625,   627,
     629,   631,   633,   635,   637,   639,   641,   643,   645,   647,
     649,   651,   653,   655,   657,   659,   664,   665,   666,   667,
     668,   669,   670,   671,   672,   673,   674,   675,   676,   677,
     678,   679,   680,   681,   682,   683,   684,   685,   686,   687,
     688,   689,   690,   691,   692,   693,   694,   695,   696,   697,
     698,   699,   700,   701,   702,   703,   704,   705,   706,   707,
     708,   709,   713,   718,   720,   722,   724,   729,   734,   735,
     739,   746,   756,   758,   760,   762,   767,   769,   774,   776,
     778,   780,   783,   787,   792,   795,   799,   801,   806,   811,
     816,   821,   826,   831,   836,   841,   846,   851,   856,   861,
     866,   871,   876,   881,   886,   891,   896,   901,   903,   908,
     910,   912,   914,   916,   918,   920,   922,   927,   932,   934,
     939,   944,   945,   946,   947,   948,   949,   950,   951,   952,
     956,   961,   966,   971,   976,   981,   986,   991,   996,  1001,
    1003,  1008,  1010,  1012,  1017,  1022,  1027,  1032,  1037,  1039,
    1044,  1046,  1051,  1056
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
#line 5495 "parser.cpp"

#line 1060 "parser.ypp"


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

    throw error(fmt::format("unmapped token! {}", (u8)tok.type));
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
