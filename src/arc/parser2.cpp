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
        value.YY_MOVE_OR_COPY< call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< decl::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.YY_MOVE_OR_COPY< decl_function::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        value.YY_MOVE_OR_COPY< decl_namespace::ptr > (YY_MOVE (that.value));
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
        value.move< call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.move< decl_function::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        value.move< decl_namespace::ptr > (YY_MOVE (that.value));
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
        value.copy< call::ptr > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< decl::ptr > (that.value);
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.copy< decl_function::ptr > (that.value);
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        value.copy< decl_namespace::ptr > (that.value);
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
        value.move< call::ptr > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl::ptr > (that.value);
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.move< decl_function::ptr > (that.value);
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        value.move< decl_namespace::ptr > (that.value);
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
        yylhs.value.emplace< call::ptr > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< decl::ptr > ();
        break;

      case symbol_kind::S_decl_function: // decl_function
        yylhs.value.emplace< decl_function::ptr > ();
        break;

      case symbol_kind::S_decl_namespace: // decl_namespace
        yylhs.value.emplace< decl_namespace::ptr > ();
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
  case 2: // root: program
#line 314 "parser2.ypp"
              { ast = std::move(yystack_[0].value.as < program::ptr > ()); }
#line 2401 "parser2.cpp"
    break;

  case 3: // root: %empty
#line 315 "parser2.ypp"
              { ast = program::make(yylhs.location); }
#line 2407 "parser2.cpp"
    break;

  case 4: // program: program ";"
#line 320 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2413 "parser2.cpp"
    break;

  case 5: // program: program inline
#line 322 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2419 "parser2.cpp"
    break;

  case 6: // program: program insert
#line 324 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2425 "parser2.cpp"
    break;

  case 7: // program: program include
#line 326 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2431 "parser2.cpp"
    break;

  case 8: // program: program using
#line 328 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2437 "parser2.cpp"
    break;

  case 9: // program: program declaration
#line 330 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2443 "parser2.cpp"
    break;

  case 10: // program: ";"
#line 332 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2449 "parser2.cpp"
    break;

  case 11: // program: inline
#line 334 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2455 "parser2.cpp"
    break;

  case 12: // program: insert
#line 336 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2461 "parser2.cpp"
    break;

  case 13: // program: include
#line 338 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2467 "parser2.cpp"
    break;

  case 14: // program: using
#line 340 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2473 "parser2.cpp"
    break;

  case 15: // program: declaration
#line 342 "parser2.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2479 "parser2.cpp"
    break;

  case 16: // inline: "#inline" expr_path ";"
#line 346 "parser2.ypp"
                                 { ppr.push_header(yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2485 "parser2.cpp"
    break;

  case 17: // insert: "#insert" expr_path ";"
#line 350 "parser2.ypp"
                                 { ppr.push_header(yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2491 "parser2.cpp"
    break;

  case 18: // include: "#include" expr_path ";"
#line 355 "parser2.ypp"
        { yylhs.value.as < include::ptr > () = include::make(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2497 "parser2.cpp"
    break;

  case 19: // using: "#using" expr_path ";"
#line 360 "parser2.ypp"
        { yylhs.value.as < include::ptr > () = include::make(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2503 "parser2.cpp"
    break;

  case 20: // declaration: "/#"
#line 364 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_begin::make(yylhs.location); }
#line 2509 "parser2.cpp"
    break;

  case 21: // declaration: "#/"
#line 365 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_end::make(yylhs.location); }
#line 2515 "parser2.cpp"
    break;

  case 22: // declaration: decl_namespace
#line 366 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_namespace::ptr > ()); }
#line 2521 "parser2.cpp"
    break;

  case 23: // declaration: decl_usingtree
#line 367 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_usingtree::ptr > ()); }
#line 2527 "parser2.cpp"
    break;

  case 24: // declaration: decl_function
#line 368 "parser2.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_function::ptr > ()); }
#line 2533 "parser2.cpp"
    break;

  case 25: // decl_namespace: "#namespace" expr_string ";"
#line 373 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_namespace::ptr > () = decl_namespace::make(yylhs.location, std::move(yystack_[1].value.as < expr_string::ptr > ())); }
#line 2539 "parser2.cpp"
    break;

  case 26: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 378 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_usingtree::ptr > () = decl_usingtree::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 2545 "parser2.cpp"
    break;

  case 27: // decl_function: "function" expr_identifier "(" expr_parameters ")" stmt_comp
#line 383 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_none); }
#line 2551 "parser2.cpp"
    break;

  case 28: // decl_function: "function" "autoexec" expr_identifier "(" expr_parameters ")" stmt_comp
#line 385 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_autoexec); }
#line 2557 "parser2.cpp"
    break;

  case 29: // decl_function: "function" "codecall" expr_identifier "(" expr_parameters ")" stmt_comp
#line 387 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_codecall); }
#line 2563 "parser2.cpp"
    break;

  case 30: // decl_function: "function" "private" expr_identifier "(" expr_parameters ")" stmt_comp
#line 389 "parser2.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, expr_identifier::make(yylhs.location, ""), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ()), export_flags::export_private); }
#line 2569 "parser2.cpp"
    break;

  case 31: // stmt: stmt_comp
#line 393 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_comp::ptr > ()); }
#line 2575 "parser2.cpp"
    break;

  case 32: // stmt: stmt_call
#line 394 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2581 "parser2.cpp"
    break;

  case 33: // stmt: stmt_const
#line 395 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2587 "parser2.cpp"
    break;

  case 34: // stmt: stmt_assign
#line 396 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2593 "parser2.cpp"
    break;

  case 35: // stmt: stmt_endon
#line 397 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_endon::ptr > ()); }
#line 2599 "parser2.cpp"
    break;

  case 36: // stmt: stmt_notify
#line 398 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_notify::ptr > ()); }
#line 2605 "parser2.cpp"
    break;

  case 37: // stmt: stmt_wait
#line 399 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_wait::ptr > ()); }
#line 2611 "parser2.cpp"
    break;

  case 38: // stmt: stmt_waitrealtime
#line 400 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waitrealtime::ptr > ()); }
#line 2617 "parser2.cpp"
    break;

  case 39: // stmt: stmt_waittill
#line 401 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittill::ptr > ()); }
#line 2623 "parser2.cpp"
    break;

  case 40: // stmt: stmt_waittillmatch
#line 402 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillmatch::ptr > ()); }
#line 2629 "parser2.cpp"
    break;

  case 41: // stmt: stmt_waittillframeend
#line 403 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillframeend::ptr > ()); }
#line 2635 "parser2.cpp"
    break;

  case 42: // stmt: stmt_if
#line 404 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_if::ptr > ()); }
#line 2641 "parser2.cpp"
    break;

  case 43: // stmt: stmt_ifelse
#line 405 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_ifelse::ptr > ()); }
#line 2647 "parser2.cpp"
    break;

  case 44: // stmt: stmt_while
#line 406 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_while::ptr > ()); }
#line 2653 "parser2.cpp"
    break;

  case 45: // stmt: stmt_dowhile
#line 407 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dowhile::ptr > ()); }
#line 2659 "parser2.cpp"
    break;

  case 46: // stmt: stmt_for
#line 408 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_for::ptr > ()); }
#line 2665 "parser2.cpp"
    break;

  case 47: // stmt: stmt_foreach
#line 409 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_foreach::ptr > ()); }
#line 2671 "parser2.cpp"
    break;

  case 48: // stmt: stmt_switch
#line 410 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_switch::ptr > ()); }
#line 2677 "parser2.cpp"
    break;

  case 49: // stmt: stmt_case
#line 411 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_case::ptr > ()); }
#line 2683 "parser2.cpp"
    break;

  case 50: // stmt: stmt_default
#line 412 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_default::ptr > ()); }
#line 2689 "parser2.cpp"
    break;

  case 51: // stmt: stmt_break
#line 413 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_break::ptr > ()); }
#line 2695 "parser2.cpp"
    break;

  case 52: // stmt: stmt_continue
#line 414 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_continue::ptr > ()); }
#line 2701 "parser2.cpp"
    break;

  case 53: // stmt: stmt_return
#line 415 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_return::ptr > ()); }
#line 2707 "parser2.cpp"
    break;

  case 54: // stmt: stmt_prof_begin
#line 416 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_begin::ptr > ()); }
#line 2713 "parser2.cpp"
    break;

  case 55: // stmt: stmt_prof_end
#line 417 "parser2.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_end::ptr > ()); }
#line 2719 "parser2.cpp"
    break;

  case 56: // stmt_or_dev: stmt
#line 421 "parser2.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt::ptr > ()); }
#line 2725 "parser2.cpp"
    break;

  case 57: // stmt_or_dev: stmt_dev
#line 422 "parser2.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dev::ptr > ()); }
#line 2731 "parser2.cpp"
    break;

  case 58: // stmt_list: stmt_list stmt
#line 427 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2737 "parser2.cpp"
    break;

  case 59: // stmt_list: stmt
#line 429 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2743 "parser2.cpp"
    break;

  case 60: // stmt_list: stmt_list ";"
#line 431 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2749 "parser2.cpp"
    break;

  case 61: // stmt_list: ";"
#line 433 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2755 "parser2.cpp"
    break;

  case 62: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 438 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2761 "parser2.cpp"
    break;

  case 63: // stmt_or_dev_list: stmt_or_dev
#line 440 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2767 "parser2.cpp"
    break;

  case 64: // stmt_or_dev_list: stmt_or_dev_list ";"
#line 442 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2773 "parser2.cpp"
    break;

  case 65: // stmt_or_dev_list: ";"
#line 444 "parser2.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2779 "parser2.cpp"
    break;

  case 66: // stmt_dev: "/#" stmt_list "#/"
#line 448 "parser2.ypp"
                                { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2785 "parser2.cpp"
    break;

  case 67: // stmt_dev: "/#" "#/"
#line 449 "parser2.ypp"
                      { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2791 "parser2.cpp"
    break;

  case 68: // stmt_comp: "{" stmt_or_dev_list "}"
#line 453 "parser2.ypp"
                                     { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2797 "parser2.cpp"
    break;

  case 69: // stmt_comp: "{" "}"
#line 454 "parser2.ypp"
                    { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2803 "parser2.cpp"
    break;

  case 70: // stmt_expr: expr_assign
#line 459 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2809 "parser2.cpp"
    break;

  case 71: // stmt_expr: expr_increment
#line 461 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2815 "parser2.cpp"
    break;

  case 72: // stmt_expr: expr_decrement
#line 463 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2821 "parser2.cpp"
    break;

  case 73: // stmt_expr: %empty
#line 465 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 2827 "parser2.cpp"
    break;

  case 74: // stmt_call: expr_call ";"
#line 470 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_call::ptr > ())); }
#line 2833 "parser2.cpp"
    break;

  case 75: // stmt_call: expr_method ";"
#line 472 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_method::ptr > ())); }
#line 2839 "parser2.cpp"
    break;

  case 76: // stmt_const: "const" expr_identifier "=" expr ";"
#line 477 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, expr_const::make(yylhs.location, std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ()))); }
#line 2845 "parser2.cpp"
    break;

  case 77: // stmt_assign: expr_assign ";"
#line 482 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2851 "parser2.cpp"
    break;

  case 78: // stmt_assign: expr_increment ";"
#line 484 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2857 "parser2.cpp"
    break;

  case 79: // stmt_assign: expr_decrement ";"
#line 486 "parser2.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2863 "parser2.cpp"
    break;

  case 80: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 491 "parser2.ypp"
        { yylhs.value.as < stmt_endon::ptr > () = stmt_endon::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 2869 "parser2.cpp"
    break;

  case 81: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 496 "parser2.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2875 "parser2.cpp"
    break;

  case 82: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 498 "parser2.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2881 "parser2.cpp"
    break;

  case 83: // stmt_wait: "wait" expr ";"
#line 503 "parser2.ypp"
        { yylhs.value.as < stmt_wait::ptr > () = stmt_wait::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2887 "parser2.cpp"
    break;

  case 84: // stmt_waitrealtime: "waitrealtime" expr ";"
#line 508 "parser2.ypp"
        { yylhs.value.as < stmt_waitrealtime::ptr > () = stmt_waitrealtime::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2893 "parser2.cpp"
    break;

  case 85: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 513 "parser2.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2899 "parser2.cpp"
    break;

  case 86: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 515 "parser2.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2905 "parser2.cpp"
    break;

  case 87: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 520 "parser2.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2911 "parser2.cpp"
    break;

  case 88: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 522 "parser2.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2917 "parser2.cpp"
    break;

  case 89: // stmt_waittillframeend: "waittillframeend" ";"
#line 527 "parser2.ypp"
        { yylhs.value.as < stmt_waittillframeend::ptr > () = stmt_waittillframeend::make(yylhs.location); }
#line 2923 "parser2.cpp"
    break;

  case 90: // stmt_if: "if" "(" expr ")" stmt
#line 532 "parser2.ypp"
        { yylhs.value.as < stmt_if::ptr > () = stmt_if::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2929 "parser2.cpp"
    break;

  case 91: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 537 "parser2.ypp"
        { yylhs.value.as < stmt_ifelse::ptr > () = stmt_ifelse::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2935 "parser2.cpp"
    break;

  case 92: // stmt_while: "while" "(" expr ")" stmt
#line 542 "parser2.ypp"
        { yylhs.value.as < stmt_while::ptr > () = stmt_while::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2941 "parser2.cpp"
    break;

  case 93: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 547 "parser2.ypp"
        { yylhs.value.as < stmt_dowhile::ptr > () = stmt_dowhile::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[5].value.as < stmt::ptr > ())); }
#line 2947 "parser2.cpp"
    break;

  case 94: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 552 "parser2.ypp"
        { yylhs.value.as < stmt_for::ptr > () = stmt_for::make(yylhs.location, std::move(yystack_[6].value.as < stmt_expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt_expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2953 "parser2.cpp"
    break;

  case 95: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 557 "parser2.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, std::format("_a{}", ++index));
            auto key = expr_identifier::make(yylhs.location, std::format("_k{}", ++index));
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt::ptr > ()), false);
        }
#line 2963 "parser2.cpp"
    break;

  case 96: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 563 "parser2.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, std::format("_a{}", ++index));
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(array), std::move(yystack_[6].value.as < expr_identifier::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ()), true);
        }
#line 2972 "parser2.cpp"
    break;

  case 97: // stmt_switch: "switch" "(" expr ")" stmt_comp
#line 571 "parser2.ypp"
        { yylhs.value.as < stmt_switch::ptr > () = stmt_switch::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); 
          parse_switch2(*yylhs.value.as < stmt_switch::ptr > ());
        }
#line 2980 "parser2.cpp"
    break;

  case 98: // stmt_case: "case" expr_integer ":"
#line 578 "parser2.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_integer::ptr > ()), stmt_list::make(yylhs.location)); }
#line 2986 "parser2.cpp"
    break;

  case 99: // stmt_case: "case" expr_string ":"
#line 580 "parser2.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_string::ptr > ()), stmt_list::make(yylhs.location)); }
#line 2992 "parser2.cpp"
    break;

  case 100: // stmt_default: "default" ":"
#line 585 "parser2.ypp"
        { yylhs.value.as < stmt_default::ptr > () = stmt_default::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2998 "parser2.cpp"
    break;

  case 101: // stmt_break: "break" ";"
#line 590 "parser2.ypp"
        { yylhs.value.as < stmt_break::ptr > () = stmt_break::make(yylhs.location); }
#line 3004 "parser2.cpp"
    break;

  case 102: // stmt_continue: "continue" ";"
#line 595 "parser2.ypp"
        { yylhs.value.as < stmt_continue::ptr > () = stmt_continue::make(yylhs.location); }
#line 3010 "parser2.cpp"
    break;

  case 103: // stmt_return: "return" expr ";"
#line 600 "parser2.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3016 "parser2.cpp"
    break;

  case 104: // stmt_return: "return" ";"
#line 602 "parser2.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 3022 "parser2.cpp"
    break;

  case 105: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 607 "parser2.ypp"
        { yylhs.value.as < stmt_prof_begin::ptr > () = stmt_prof_begin::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 3028 "parser2.cpp"
    break;

  case 106: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 612 "parser2.ypp"
        { yylhs.value.as < stmt_prof_end::ptr > () = stmt_prof_end::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 3034 "parser2.cpp"
    break;

  case 107: // expr: expr_ternary
#line 616 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 3040 "parser2.cpp"
    break;

  case 108: // expr: expr_binary
#line 617 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 3046 "parser2.cpp"
    break;

  case 109: // expr: expr_primitive
#line 618 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 3052 "parser2.cpp"
    break;

  case 110: // expr_or_empty: expr
#line 622 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 3058 "parser2.cpp"
    break;

  case 111: // expr_or_empty: %empty
#line 623 "parser2.ypp"
                     { yylhs.value.as < expr::ptr > () = expr_empty::make(yylhs.location); }
#line 3064 "parser2.cpp"
    break;

  case 112: // expr_increment: "++" expr_object
#line 628 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 3070 "parser2.cpp"
    break;

  case 113: // expr_increment: expr_object "++"
#line 630 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 3076 "parser2.cpp"
    break;

  case 114: // expr_decrement: "--" expr_object
#line 635 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 3082 "parser2.cpp"
    break;

  case 115: // expr_decrement: expr_object "--"
#line 637 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 3088 "parser2.cpp"
    break;

  case 116: // expr_assign: expr_object "=" expr
#line 642 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 3094 "parser2.cpp"
    break;

  case 117: // expr_assign: expr_object "|=" expr
#line 644 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwor); }
#line 3100 "parser2.cpp"
    break;

  case 118: // expr_assign: expr_object "&=" expr
#line 646 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwand); }
#line 3106 "parser2.cpp"
    break;

  case 119: // expr_assign: expr_object "^=" expr
#line 648 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwexor); }
#line 3112 "parser2.cpp"
    break;

  case 120: // expr_assign: expr_object "<<=" expr
#line 650 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shl); }
#line 3118 "parser2.cpp"
    break;

  case 121: // expr_assign: expr_object ">>=" expr
#line 652 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shr); }
#line 3124 "parser2.cpp"
    break;

  case 122: // expr_assign: expr_object "+=" expr
#line 654 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::add); }
#line 3130 "parser2.cpp"
    break;

  case 123: // expr_assign: expr_object "-=" expr
#line 656 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::sub); }
#line 3136 "parser2.cpp"
    break;

  case 124: // expr_assign: expr_object "*=" expr
#line 658 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mul); }
#line 3142 "parser2.cpp"
    break;

  case 125: // expr_assign: expr_object "/=" expr
#line 660 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::div); }
#line 3148 "parser2.cpp"
    break;

  case 126: // expr_assign: expr_object "%=" expr
#line 662 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mod); }
#line 3154 "parser2.cpp"
    break;

  case 127: // expr_ternary: expr "?" expr ":" expr
#line 667 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_ternary::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3160 "parser2.cpp"
    break;

  case 128: // expr_binary: expr "||" expr
#line 672 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_or); }
#line 3166 "parser2.cpp"
    break;

  case 129: // expr_binary: expr "&&" expr
#line 674 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_and); }
#line 3172 "parser2.cpp"
    break;

  case 130: // expr_binary: expr "===" expr
#line 676 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::seq); }
#line 3178 "parser2.cpp"
    break;

  case 131: // expr_binary: expr "!==" expr
#line 678 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::sne); }
#line 3184 "parser2.cpp"
    break;

  case 132: // expr_binary: expr "==" expr
#line 680 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::eq); }
#line 3190 "parser2.cpp"
    break;

  case 133: // expr_binary: expr "!=" expr
#line 682 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ne); }
#line 3196 "parser2.cpp"
    break;

  case 134: // expr_binary: expr "<=" expr
#line 684 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::le); }
#line 3202 "parser2.cpp"
    break;

  case 135: // expr_binary: expr ">=" expr
#line 686 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ge); }
#line 3208 "parser2.cpp"
    break;

  case 136: // expr_binary: expr "<" expr
#line 688 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::lt); }
#line 3214 "parser2.cpp"
    break;

  case 137: // expr_binary: expr ">" expr
#line 690 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::gt); }
#line 3220 "parser2.cpp"
    break;

  case 138: // expr_binary: expr "|" expr
#line 692 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwor); }
#line 3226 "parser2.cpp"
    break;

  case 139: // expr_binary: expr "&" expr
#line 694 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwand); }
#line 3232 "parser2.cpp"
    break;

  case 140: // expr_binary: expr "^" expr
#line 696 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwexor); }
#line 3238 "parser2.cpp"
    break;

  case 141: // expr_binary: expr "<<" expr
#line 698 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shl); }
#line 3244 "parser2.cpp"
    break;

  case 142: // expr_binary: expr ">>" expr
#line 700 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shr); }
#line 3250 "parser2.cpp"
    break;

  case 143: // expr_binary: expr "+" expr
#line 702 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::add); }
#line 3256 "parser2.cpp"
    break;

  case 144: // expr_binary: expr "-" expr
#line 704 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::sub); }
#line 3262 "parser2.cpp"
    break;

  case 145: // expr_binary: expr "*" expr
#line 706 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mul); }
#line 3268 "parser2.cpp"
    break;

  case 146: // expr_binary: expr "/" expr
#line 708 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::div); }
#line 3274 "parser2.cpp"
    break;

  case 147: // expr_binary: expr "%" expr
#line 710 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mod); }
#line 3280 "parser2.cpp"
    break;

  case 148: // expr_primitive: expr_complement
#line 714 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_complement::ptr > ()); }
#line 3286 "parser2.cpp"
    break;

  case 149: // expr_primitive: expr_negate
#line 715 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_negate::ptr > ()); }
#line 3292 "parser2.cpp"
    break;

  case 150: // expr_primitive: expr_not
#line 716 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_not::ptr > ()); }
#line 3298 "parser2.cpp"
    break;

  case 151: // expr_primitive: expr_call
#line 717 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3304 "parser2.cpp"
    break;

  case 152: // expr_primitive: expr_method
#line 718 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3310 "parser2.cpp"
    break;

  case 153: // expr_primitive: expr_getnextarraykey
#line 719 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getnextarraykey::ptr > ()); }
#line 3316 "parser2.cpp"
    break;

  case 154: // expr_primitive: expr_getfirstarraykey
#line 720 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getfirstarraykey::ptr > ()); }
#line 3322 "parser2.cpp"
    break;

  case 155: // expr_primitive: expr_getdvarcoloralpha
#line 721 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcoloralpha::ptr > ()); }
#line 3328 "parser2.cpp"
    break;

  case 156: // expr_primitive: expr_getdvarcolorblue
#line 722 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorblue::ptr > ()); }
#line 3334 "parser2.cpp"
    break;

  case 157: // expr_primitive: expr_getdvarcolorgreen
#line 723 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorgreen::ptr > ()); }
#line 3340 "parser2.cpp"
    break;

  case 158: // expr_primitive: expr_getdvarcolorred
#line 724 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarcolorred::ptr > ()); }
#line 3346 "parser2.cpp"
    break;

  case 159: // expr_primitive: expr_getdvarvector
#line 725 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarvector::ptr > ()); }
#line 3352 "parser2.cpp"
    break;

  case 160: // expr_primitive: expr_getdvarfloat
#line 726 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarfloat::ptr > ()); }
#line 3358 "parser2.cpp"
    break;

  case 161: // expr_primitive: expr_getdvarint
#line 727 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvarint::ptr > ()); }
#line 3364 "parser2.cpp"
    break;

  case 162: // expr_primitive: expr_getdvar
#line 728 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_getdvar::ptr > ()); }
#line 3370 "parser2.cpp"
    break;

  case 163: // expr_primitive: expr_gettime
#line 729 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_gettime::ptr > ()); }
#line 3376 "parser2.cpp"
    break;

  case 164: // expr_primitive: expr_abs
#line 730 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_abs::ptr > ()); }
#line 3382 "parser2.cpp"
    break;

  case 165: // expr_primitive: expr_vectortoangles
#line 731 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vectortoangles::ptr > ()); }
#line 3388 "parser2.cpp"
    break;

  case 166: // expr_primitive: expr_angleclamp180
#line 732 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_angleclamp180::ptr > ()); }
#line 3394 "parser2.cpp"
    break;

  case 167: // expr_primitive: expr_anglestoforward
#line 733 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoforward::ptr > ()); }
#line 3400 "parser2.cpp"
    break;

  case 168: // expr_primitive: expr_anglestoright
#line 734 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoright::ptr > ()); }
#line 3406 "parser2.cpp"
    break;

  case 169: // expr_primitive: expr_anglestoup
#line 735 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anglestoup::ptr > ()); }
#line 3412 "parser2.cpp"
    break;

  case 170: // expr_primitive: expr_vectorscale
#line 736 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vectorscale::ptr > ()); }
#line 3418 "parser2.cpp"
    break;

  case 171: // expr_primitive: expr_isdefined
#line 737 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_isdefined::ptr > ()); }
#line 3424 "parser2.cpp"
    break;

  case 172: // expr_primitive: expr_reference
#line 738 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_reference::ptr > ()); }
#line 3430 "parser2.cpp"
    break;

  case 173: // expr_primitive: expr_array
#line 739 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3436 "parser2.cpp"
    break;

  case 174: // expr_primitive: expr_field
#line 740 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3442 "parser2.cpp"
    break;

  case 175: // expr_primitive: expr_size
#line 741 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_size::ptr > ()); }
#line 3448 "parser2.cpp"
    break;

  case 176: // expr_primitive: expr_paren
#line 742 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_paren::ptr > ()); }
#line 3454 "parser2.cpp"
    break;

  case 177: // expr_primitive: expr_empty_array
#line 743 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_empty_array::ptr > ()); }
#line 3460 "parser2.cpp"
    break;

  case 178: // expr_primitive: expr_undefined
#line 744 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_undefined::ptr > ()); }
#line 3466 "parser2.cpp"
    break;

  case 179: // expr_primitive: expr_game
#line 745 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3472 "parser2.cpp"
    break;

  case 180: // expr_primitive: expr_self
#line 746 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3478 "parser2.cpp"
    break;

  case 181: // expr_primitive: expr_anim
#line 747 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3484 "parser2.cpp"
    break;

  case 182: // expr_primitive: expr_level
#line 748 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3490 "parser2.cpp"
    break;

  case 183: // expr_primitive: expr_animation
#line 749 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animation::ptr > ()); }
#line 3496 "parser2.cpp"
    break;

  case 184: // expr_primitive: expr_animtree
#line 750 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animtree::ptr > ()); }
#line 3502 "parser2.cpp"
    break;

  case 185: // expr_primitive: expr_identifier
#line 751 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3508 "parser2.cpp"
    break;

  case 186: // expr_primitive: expr_istring
#line 752 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_istring::ptr > ()); }
#line 3514 "parser2.cpp"
    break;

  case 187: // expr_primitive: expr_string
#line 753 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_string::ptr > ()); }
#line 3520 "parser2.cpp"
    break;

  case 188: // expr_primitive: expr_vector
#line 754 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vector::ptr > ()); }
#line 3526 "parser2.cpp"
    break;

  case 189: // expr_primitive: expr_hash
#line 755 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_hash::ptr > ()); }
#line 3532 "parser2.cpp"
    break;

  case 190: // expr_primitive: expr_float
#line 756 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_float::ptr > ()); }
#line 3538 "parser2.cpp"
    break;

  case 191: // expr_primitive: expr_integer
#line 757 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_integer::ptr > ()); }
#line 3544 "parser2.cpp"
    break;

  case 192: // expr_primitive: expr_false
#line 758 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_false::ptr > ()); }
#line 3550 "parser2.cpp"
    break;

  case 193: // expr_primitive: expr_true
#line 759 "parser2.ypp"
                             { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_true::ptr > ()); }
#line 3556 "parser2.cpp"
    break;

  case 194: // expr_complement: "~" expr
#line 764 "parser2.ypp"
        { yylhs.value.as < expr_complement::ptr > () = expr_complement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3562 "parser2.cpp"
    break;

  case 195: // expr_negate: "-" expr_identifier
#line 769 "parser2.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3568 "parser2.cpp"
    break;

  case 196: // expr_negate: "-" expr_paren
#line 771 "parser2.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_paren::ptr > ())); }
#line 3574 "parser2.cpp"
    break;

  case 197: // expr_negate: "-" expr_array
#line 773 "parser2.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_array::ptr > ())); }
#line 3580 "parser2.cpp"
    break;

  case 198: // expr_negate: "-" expr_field
#line 775 "parser2.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_field::ptr > ())); }
#line 3586 "parser2.cpp"
    break;

  case 199: // expr_not: "!" expr
#line 780 "parser2.ypp"
        { yylhs.value.as < expr_not::ptr > () = expr_not::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3592 "parser2.cpp"
    break;

  case 200: // expr_call: expr_function
#line 784 "parser2.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3598 "parser2.cpp"
    break;

  case 201: // expr_call: expr_pointer
#line 785 "parser2.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3604 "parser2.cpp"
    break;

  case 202: // expr_method: expr_object expr_function
#line 790 "parser2.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3615 "parser2.cpp"
    break;

  case 203: // expr_method: expr_object expr_pointer
#line 797 "parser2.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3626 "parser2.cpp"
    break;

  case 204: // expr_function: expr_identifier "(" expr_arguments ")"
#line 807 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3632 "parser2.cpp"
    break;

  case 205: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 809 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3638 "parser2.cpp"
    break;

  case 206: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 811 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3644 "parser2.cpp"
    break;

  case 207: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 813 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3650 "parser2.cpp"
    break;

  case 208: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 818 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3656 "parser2.cpp"
    break;

  case 209: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 820 "parser2.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3662 "parser2.cpp"
    break;

  case 210: // expr_parameters: expr_parameters "," expr_parameters_default
#line 825 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3668 "parser2.cpp"
    break;

  case 211: // expr_parameters: expr_parameters "," expr_identifier
#line 827 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3674 "parser2.cpp"
    break;

  case 212: // expr_parameters: expr_parameters_default
#line 829 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3680 "parser2.cpp"
    break;

  case 213: // expr_parameters: expr_identifier
#line 831 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3686 "parser2.cpp"
    break;

  case 214: // expr_parameters: %empty
#line 833 "parser2.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); }
#line 3692 "parser2.cpp"
    break;

  case 215: // expr_parameters_default: expr_identifier "=" expr
#line 838 "parser2.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr_identifier::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 3698 "parser2.cpp"
    break;

  case 216: // expr_arguments: expr_arguments_no_empty
#line 843 "parser2.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[0].value.as < expr_arguments::ptr > ()); }
#line 3704 "parser2.cpp"
    break;

  case 217: // expr_arguments: %empty
#line 845 "parser2.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); }
#line 3710 "parser2.cpp"
    break;

  case 218: // expr_arguments_no_empty: expr_arguments "," expr
#line 850 "parser2.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[2].value.as < expr_arguments::ptr > ()); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3716 "parser2.cpp"
    break;

  case 219: // expr_arguments_no_empty: expr
#line 852 "parser2.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3722 "parser2.cpp"
    break;

  case 220: // expr_getnextarraykey: "getnextarraykey" "(" expr "," expr ")"
#line 857 "parser2.ypp"
        { yylhs.value.as < expr_getnextarraykey::ptr > () = expr_getnextarraykey::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3728 "parser2.cpp"
    break;

  case 221: // expr_getfirstarraykey: "getfirstarraykey" "(" expr ")"
#line 862 "parser2.ypp"
        { yylhs.value.as < expr_getfirstarraykey::ptr > () = expr_getfirstarraykey::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3734 "parser2.cpp"
    break;

  case 222: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr ")"
#line 867 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcoloralpha::ptr > () = expr_getdvarcoloralpha::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3740 "parser2.cpp"
    break;

  case 223: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr "," expr ")"
#line 869 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcoloralpha::ptr > () = expr_getdvarcoloralpha::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3746 "parser2.cpp"
    break;

  case 224: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr ")"
#line 874 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorblue::ptr > () = expr_getdvarcolorblue::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3752 "parser2.cpp"
    break;

  case 225: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr "," expr ")"
#line 876 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorblue::ptr > () = expr_getdvarcolorblue::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3758 "parser2.cpp"
    break;

  case 226: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr ")"
#line 881 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorgreen::ptr > () = expr_getdvarcolorgreen::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3764 "parser2.cpp"
    break;

  case 227: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr "," expr ")"
#line 883 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorgreen::ptr > () = expr_getdvarcolorgreen::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3770 "parser2.cpp"
    break;

  case 228: // expr_getdvarcolorred: "getdvarcolorred" "(" expr ")"
#line 888 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorred::ptr > () = expr_getdvarcolorred::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3776 "parser2.cpp"
    break;

  case 229: // expr_getdvarcolorred: "getdvarcolorred" "(" expr "," expr ")"
#line 890 "parser2.ypp"
        { yylhs.value.as < expr_getdvarcolorred::ptr > () = expr_getdvarcolorred::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3782 "parser2.cpp"
    break;

  case 230: // expr_getdvarvector: "getdvarvector" "(" expr ")"
#line 895 "parser2.ypp"
        { yylhs.value.as < expr_getdvarvector::ptr > () = expr_getdvarvector::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3788 "parser2.cpp"
    break;

  case 231: // expr_getdvarvector: "getdvarvector" "(" expr "," expr ")"
#line 897 "parser2.ypp"
        { yylhs.value.as < expr_getdvarvector::ptr > () = expr_getdvarvector::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3794 "parser2.cpp"
    break;

  case 232: // expr_getdvarfloat: "getdvarfloat" "(" expr ")"
#line 902 "parser2.ypp"
        { yylhs.value.as < expr_getdvarfloat::ptr > () = expr_getdvarfloat::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3800 "parser2.cpp"
    break;

  case 233: // expr_getdvarfloat: "getdvarfloat" "(" expr "," expr ")"
#line 904 "parser2.ypp"
        { yylhs.value.as < expr_getdvarfloat::ptr > () = expr_getdvarfloat::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3806 "parser2.cpp"
    break;

  case 234: // expr_getdvarint: "getdvarint" "(" expr ")"
#line 909 "parser2.ypp"
        { yylhs.value.as < expr_getdvarint::ptr > () = expr_getdvarint::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3812 "parser2.cpp"
    break;

  case 235: // expr_getdvarint: "getdvarint" "(" expr "," expr ")"
#line 911 "parser2.ypp"
        { yylhs.value.as < expr_getdvarint::ptr > () = expr_getdvarint::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ())); }
#line 3818 "parser2.cpp"
    break;

  case 236: // expr_getdvar: "getdvar" "(" expr ")"
#line 916 "parser2.ypp"
        { yylhs.value.as < expr_getdvar::ptr > () = expr_getdvar::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3824 "parser2.cpp"
    break;

  case 237: // expr_gettime: "gettime" "(" ")"
#line 921 "parser2.ypp"
        { yylhs.value.as < expr_gettime::ptr > () = expr_gettime::make(yylhs.location); }
#line 3830 "parser2.cpp"
    break;

  case 238: // expr_abs: "abs" "(" expr ")"
#line 926 "parser2.ypp"
        { yylhs.value.as < expr_abs::ptr > () = expr_abs::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3836 "parser2.cpp"
    break;

  case 239: // expr_vectortoangles: "vectortoangles" "(" expr ")"
#line 931 "parser2.ypp"
        { yylhs.value.as < expr_vectortoangles::ptr > () = expr_vectortoangles::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3842 "parser2.cpp"
    break;

  case 240: // expr_angleclamp180: "angleclamp180" "(" expr ")"
#line 936 "parser2.ypp"
        { yylhs.value.as < expr_angleclamp180::ptr > () = expr_angleclamp180::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3848 "parser2.cpp"
    break;

  case 241: // expr_anglestoforward: "anglestoforward" "(" expr ")"
#line 941 "parser2.ypp"
        { yylhs.value.as < expr_anglestoforward::ptr > () = expr_anglestoforward::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3854 "parser2.cpp"
    break;

  case 242: // expr_anglestoright: "anglestoright" "(" expr ")"
#line 946 "parser2.ypp"
        { yylhs.value.as < expr_anglestoright::ptr > () = expr_anglestoright::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3860 "parser2.cpp"
    break;

  case 243: // expr_anglestoup: "anglestoup" "(" expr ")"
#line 951 "parser2.ypp"
        { yylhs.value.as < expr_anglestoup::ptr > () = expr_anglestoup::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3866 "parser2.cpp"
    break;

  case 244: // expr_vectorscale: "vectorscale" "(" expr "," expr ")"
#line 956 "parser2.ypp"
        { yylhs.value.as < expr_vectorscale::ptr > () = expr_vectorscale::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3872 "parser2.cpp"
    break;

  case 245: // expr_isdefined: "isdefined" "(" expr ")"
#line 961 "parser2.ypp"
        { yylhs.value.as < expr_isdefined::ptr > () = expr_isdefined::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3878 "parser2.cpp"
    break;

  case 246: // expr_reference: "&" expr_identifier
#line 966 "parser2.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3884 "parser2.cpp"
    break;

  case 247: // expr_reference: "&" expr_path "::" expr_identifier
#line 968 "parser2.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, std::move(yystack_[2].value.as < expr_path::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3890 "parser2.cpp"
    break;

  case 248: // expr_array: expr_object "[" expr "]"
#line 973 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3896 "parser2.cpp"
    break;

  case 249: // expr_array: expr_getdvarvector "[" expr "]"
#line 975 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_getdvarvector::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3902 "parser2.cpp"
    break;

  case 250: // expr_array: expr_vectortoangles "[" expr "]"
#line 977 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_vectortoangles::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3908 "parser2.cpp"
    break;

  case 251: // expr_array: expr_angleclamp180 "[" expr "]"
#line 979 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_angleclamp180::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3914 "parser2.cpp"
    break;

  case 252: // expr_array: expr_anglestoforward "[" expr "]"
#line 981 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoforward::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3920 "parser2.cpp"
    break;

  case 253: // expr_array: expr_anglestoright "[" expr "]"
#line 983 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoright::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3926 "parser2.cpp"
    break;

  case 254: // expr_array: expr_anglestoup "[" expr "]"
#line 985 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_anglestoup::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3932 "parser2.cpp"
    break;

  case 255: // expr_array: expr_vectorscale "[" expr "]"
#line 987 "parser2.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr_vectorscale::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3938 "parser2.cpp"
    break;

  case 256: // expr_field: expr_object "." expr_identifier_nosize
#line 992 "parser2.ypp"
        { yylhs.value.as < expr_field::ptr > () = expr_field::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3944 "parser2.cpp"
    break;

  case 257: // expr_size: expr_object "." "size"
#line 997 "parser2.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 3950 "parser2.cpp"
    break;

  case 258: // expr_size: expr_string "." "size"
#line 999 "parser2.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 3956 "parser2.cpp"
    break;

  case 259: // expr_paren: "(" expr ")"
#line 1004 "parser2.ypp"
        { yylhs.value.as < expr_paren::ptr > () = expr_paren::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3962 "parser2.cpp"
    break;

  case 260: // expr_object: expr_call
#line 1008 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3968 "parser2.cpp"
    break;

  case 261: // expr_object: expr_method
#line 1009 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3974 "parser2.cpp"
    break;

  case 262: // expr_object: expr_array
#line 1010 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3980 "parser2.cpp"
    break;

  case 263: // expr_object: expr_field
#line 1011 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3986 "parser2.cpp"
    break;

  case 264: // expr_object: expr_game
#line 1012 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3992 "parser2.cpp"
    break;

  case 265: // expr_object: expr_self
#line 1013 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3998 "parser2.cpp"
    break;

  case 266: // expr_object: expr_anim
#line 1014 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 4004 "parser2.cpp"
    break;

  case 267: // expr_object: expr_level
#line 1015 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 4010 "parser2.cpp"
    break;

  case 268: // expr_object: expr_world
#line 1016 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_world::ptr > ()); }
#line 4016 "parser2.cpp"
    break;

  case 269: // expr_object: expr_classes
#line 1017 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_classes::ptr > ()); }
#line 4022 "parser2.cpp"
    break;

  case 270: // expr_object: expr_identifier
#line 1018 "parser2.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 4028 "parser2.cpp"
    break;

  case 271: // expr_empty_array: "[" "]"
#line 1023 "parser2.ypp"
        { yylhs.value.as < expr_empty_array::ptr > () = expr_empty_array::make(yylhs.location); }
#line 4034 "parser2.cpp"
    break;

  case 272: // expr_undefined: "undefined"
#line 1028 "parser2.ypp"
        { yylhs.value.as < expr_undefined::ptr > () = expr_undefined::make(yylhs.location); }
#line 4040 "parser2.cpp"
    break;

  case 273: // expr_game: "game"
#line 1033 "parser2.ypp"
        { yylhs.value.as < expr_game::ptr > () = expr_game::make(yylhs.location); }
#line 4046 "parser2.cpp"
    break;

  case 274: // expr_self: "self"
#line 1038 "parser2.ypp"
        { yylhs.value.as < expr_self::ptr > () = expr_self::make(yylhs.location); }
#line 4052 "parser2.cpp"
    break;

  case 275: // expr_anim: "anim"
#line 1043 "parser2.ypp"
        { yylhs.value.as < expr_anim::ptr > () = expr_anim::make(yylhs.location); }
#line 4058 "parser2.cpp"
    break;

  case 276: // expr_level: "level"
#line 1048 "parser2.ypp"
        { yylhs.value.as < expr_level::ptr > () = expr_level::make(yylhs.location); }
#line 4064 "parser2.cpp"
    break;

  case 277: // expr_world: "world"
#line 1053 "parser2.ypp"
        { yylhs.value.as < expr_world::ptr > () = expr_world::make(yylhs.location); }
#line 4070 "parser2.cpp"
    break;

  case 278: // expr_classes: "classes"
#line 1058 "parser2.ypp"
        { yylhs.value.as < expr_classes::ptr > () = expr_classes::make(yylhs.location); }
#line 4076 "parser2.cpp"
    break;

  case 279: // expr_animation: "%" "identifier"
#line 1063 "parser2.ypp"
        { yylhs.value.as < expr_animation::ptr > () = expr_animation::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4082 "parser2.cpp"
    break;

  case 280: // expr_animtree: "#animtree"
#line 1068 "parser2.ypp"
        { yylhs.value.as < expr_animtree::ptr > () = expr_animtree::make(yylhs.location); }
#line 4088 "parser2.cpp"
    break;

  case 281: // expr_identifier_nosize: "identifier"
#line 1073 "parser2.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4094 "parser2.cpp"
    break;

  case 282: // expr_identifier: "identifier"
#line 1078 "parser2.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4100 "parser2.cpp"
    break;

  case 283: // expr_identifier: "size"
#line 1080 "parser2.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, "size"); }
#line 4106 "parser2.cpp"
    break;

  case 284: // expr_path: "identifier"
#line 1085 "parser2.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4112 "parser2.cpp"
    break;

  case 285: // expr_path: "path"
#line 1087 "parser2.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4118 "parser2.cpp"
    break;

  case 286: // expr_istring: "localized string"
#line 1092 "parser2.ypp"
        { yylhs.value.as < expr_istring::ptr > () = expr_istring::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4124 "parser2.cpp"
    break;

  case 287: // expr_string: "string literal"
#line 1097 "parser2.ypp"
        { yylhs.value.as < expr_string::ptr > () = expr_string::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4130 "parser2.cpp"
    break;

  case 288: // expr_vector: "(" expr "," expr "," expr ")"
#line 1102 "parser2.ypp"
        { yylhs.value.as < expr_vector::ptr > () = expr_vector::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 4136 "parser2.cpp"
    break;

  case 289: // expr_hash: "hash string"
#line 1107 "parser2.ypp"
        { yylhs.value.as < expr_hash::ptr > () = expr_hash::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4142 "parser2.cpp"
    break;

  case 290: // expr_float: "-" "float"
#line 1112 "parser2.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 4148 "parser2.cpp"
    break;

  case 291: // expr_float: "float"
#line 1114 "parser2.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4154 "parser2.cpp"
    break;

  case 292: // expr_integer: "-" "integer"
#line 1119 "parser2.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 4160 "parser2.cpp"
    break;

  case 293: // expr_integer: "integer"
#line 1121 "parser2.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 4166 "parser2.cpp"
    break;

  case 294: // expr_false: "false"
#line 1126 "parser2.ypp"
        { yylhs.value.as < expr_false::ptr > () = expr_false::make(yylhs.location); }
#line 4172 "parser2.cpp"
    break;

  case 295: // expr_true: "true"
#line 1131 "parser2.ypp"
        { yylhs.value.as < expr_true::ptr > () = expr_true::make(yylhs.location); }
#line 4178 "parser2.cpp"
    break;


#line 4182 "parser2.cpp"

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
  "#animtree", "function", "autoexec", "codecall", "private", "endon",
  "notify", "wait", "waitrealtime", "waittill", "waittillmatch",
  "waittillframeend", "if", "else", "do", "while", "for", "foreach", "in",
  "switch", "case", "default", "break", "continue", "return", "prof_begin",
  "prof_end", "thread", "true", "false", "undefined", "size", "game",
  "self", "anim", "level", "const", "world", "classes", "new",
  "getnextarraykey", "getfirstarraykey", "getdvarcoloralpha",
  "getdvarcolorblue", "getdvarcolorgreen", "getdvarcolorred",
  "getdvarvector", "getdvarfloat", "getdvarint", "getdvar", "gettime",
  "abs", "vectortoangles", "angleclamp180", "anglestoforward",
  "anglestoright", "anglestoup", "vectorscale", "isdefined", "(", ")", "{",
  "}", "[", "]", ",", ".", "..", "...", "::", ":", ";", "?", "->", "++",
  "--", "<<", ">>", "||", "&&", "===", "!==", "==", "!=", "<=", ">=", "<",
  ">", "!", "~", "=", "+=", "-=", "*=", "/=", "%=", "|=", "&=", "^=",
  ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/", "%", "path",
  "identifier", "string literal", "localized string", "hash string",
  "float", "integer", "SIZEOF", "THEN", "TERN", "NEG", "ANIMREF", "PREINC",
  "PREDEC", "POSTINC", "POSTDEC", "$accept", "root", "program", "inline",
  "insert", "include", "using", "declaration", "decl_namespace",
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
  "expr_world", "expr_classes", "expr_animation", "expr_animtree",
  "expr_identifier_nosize", "expr_identifier", "expr_path", "expr_istring",
  "expr_string", "expr_vector", "expr_hash", "expr_float", "expr_integer",
  "expr_false", "expr_true", YY_NULLPTR
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


  const short parser2::yypact_ninf_ = -501;

  const short parser2::yytable_ninf_ = -285;

  const short
  parser2::yypact_[] =
  {
     472,  -501,  -501,   -85,   -85,   -85,   -85,   -38,   -79,    -1,
    -501,    51,   926,  -501,  -501,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,   -29,   -12,     1,    14,   -79,  -501,    20,
     -27,   -27,   -27,  -501,  -501,    55,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,    41,  -501,    56,
      60,    64,   -27,    58,   -27,   -27,   -27,   -37,  -501,    22,
    -501,   -19,   -17,     3,   -21,   -27,  1498,   -21,   -21,   -21,
    1059,  -501,  -501,    22,  -501,   -36,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,    67,    68,    77,    78,    86,
      87,    90,    96,    97,    98,    99,   103,   104,   107,   108,
     110,   111,   119,   121,  1498,    -7,  1498,  1498,   -31,  1359,
      43,    92,  -501,  -501,  -501,  -501,  3923,  -501,  -501,  -501,
    -501,  -501,  -501,   120,   268,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,   122,  -501,  -501,  -501,  -501,  -501,   125,
     126,   127,   132,   135,   137,  -501,  -501,   317,   333,  -501,
    -501,   366,  -501,  -501,   397,   524,   549,   597,  -501,  -501,
    -501,  -501,    31,   113,  -501,    44,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  1204,  1498,  1498,   130,   145,
    1697,   146,   147,   148,   152,   -89,   114,   142,   143,  1318,
     159,   160,   -27,  -501,   165,  -501,  1449,  1449,  -501,  -501,
    1139,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,   162,   168,   172,
     173,   184,   122,   125,   126,   127,   132,   135,   137,  -501,
    -501,   870,  -501,  -501,  -501,  -501,   181,   186,   197,   189,
    1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,
     199,  1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,  1708,
    1498,  -501,  -501,  -501,  -501,   191,  1498,  -501,  -501,  -501,
    -501,   317,   333,  -501,   605,    31,  -501,  1498,  1498,  1498,
    1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,
    1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,  1498,
    1498,  1498,  1498,  1498,  1498,  1588,   -24,  -501,  -501,   181,
    1498,   -27,   236,  -501,  -501,  -501,  1269,  3772,  3810,  -501,
    1498,   258,  1498,  1632,   -27,  1498,   170,   204,   207,  -501,
    -501,  -501,  -501,  3848,  1498,  1498,   193,   605,   605,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,   232,   233,   234,
     238,   188,  -501,  -501,  1498,  1498,  1498,  1498,  1498,  1498,
    1498,  1498,  1498,  1498,  1498,  1498,  1498,   -27,  3646,  2235,
    1757,  1806,  1855,  1904,  1953,  2002,  2051,  2272,  -501,  2309,
    2346,  2383,  2420,  2457,  2494,  3690,  2531,  -501,  1498,   909,
     -27,  2568,  1490,   118,   118,  3935,  3968,   212,   212,  1818,
    1818,   212,   212,   212,   212,  3980,  1769,  4013,   -94,   -94,
    -501,  -501,  -501,  3242,  3287,  3332,  3377,  3422,  3467,  3512,
    1408,  3557,  -501,  -501,  -501,  3923,     4,  -501,   243,  -501,
    -501,  -501,  -501,  -501,  -501,  2605,   244,  2642,   235,  -501,
    -501,  -501,   795,   -13,  2679,  -501,  -501,  -501,     5,     6,
    1498,  1498,  1498,  1498,  1498,  3923,  3923,  3923,  3923,  3923,
    3923,  3923,  3923,  3923,  3923,  3923,  3602,    15,   245,  1498,
    -501,  -501,  1498,  -501,  1498,  -501,  1498,  -501,  1498,  -501,
    1498,  -501,  1498,  -501,  1498,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,  1498,  -501,  3734,   246,  -501,  1498,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,  1498,  1498,  1697,
    1498,  1697,  1498,  1498,   -27,   -21,   237,   250,  3886,  2716,
    2100,  2149,  2198,   260,  -501,  1498,  2753,  2790,  2827,  2864,
    2901,  2938,  2975,  3012,  3049,  1498,   255,  3923,  3923,    16,
     296,  3086,  -501,  3923,   251,  3123,   307,  -501,  -501,  -501,
    -501,   257,   262,  1498,   264,  1498,   265,  1498,   270,    33,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  3160,
    1498,  -501,  1697,   269,  1632,  1697,  1498,  -501,  -501,   274,
     282,  -501,   283,  -501,   287,  1498,  -501,  -501,    39,  -501,
    -501,   289,  -501,  3197,   280,   281,   288,    42,  -501,  1697,
    1697,  -501,  -501,  -501,  -501,  -501,  -501
  };

  const short
  parser2::yydefact_[] =
  {
       3,    20,    21,     0,     0,     0,     0,     0,     0,     0,
      10,     0,     2,    11,    12,    13,    14,    15,    22,    23,
      24,   285,   284,     0,     0,     0,     0,     0,   287,     0,
       0,     0,     0,   283,   282,     0,     1,     4,     5,     6,
       7,     8,     9,    16,    18,    17,    19,     0,    25,     0,
       0,     0,   214,     0,   214,   214,   214,     0,   212,   213,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,   210,   211,   280,     0,   295,   294,   272,   273,
     274,   275,   276,   277,   278,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   282,   286,   289,   291,   293,   215,   107,   108,   109,
     148,   149,   150,   151,   152,   200,   201,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,     0,   177,   178,   179,   180,   181,   182,   268,   269,
     183,   184,   185,     0,   186,   187,   188,   189,   190,   191,
     192,   193,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,    65,     0,     0,    56,    63,
       0,    57,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,     0,     0,     0,
     260,   261,     0,     0,     0,     0,     0,     0,     0,   262,
     263,     0,   264,   265,   266,   267,   270,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,   199,   194,   246,     0,     0,   290,   292,   260,
     261,   197,   198,   196,     0,   195,   279,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   202,   203,     0,
     217,     0,     0,    67,    61,    59,     0,     0,     0,    89,
       0,     0,     0,    73,     0,     0,     0,     0,     0,   100,
     101,   102,   104,     0,   217,   217,     0,   112,   114,    68,
      64,    62,    78,    79,    77,    74,    75,     0,     0,     0,
       0,     0,   113,   115,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   217,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   237,     0,
       0,     0,     0,     0,     0,     0,     0,   259,     0,     0,
       0,     0,     0,   141,   142,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   143,   144,
     145,   146,   147,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   257,   281,   256,   219,     0,   216,     0,   258,
      66,    60,    58,    83,    84,     0,     0,     0,     0,    71,
      72,    70,     0,     0,     0,    99,    98,   103,     0,     0,
       0,     0,     0,     0,     0,   116,   122,   123,   124,   125,
     126,   117,   118,   119,   121,   120,     0,     0,     0,     0,
     221,   222,     0,   224,     0,   226,     0,   228,     0,   230,
       0,   232,     0,   234,     0,   236,   238,   239,   240,   241,
     242,   243,     0,   245,     0,     0,   247,     0,   249,   250,
     251,   252,   253,   254,   255,   248,   204,     0,   217,     0,
       0,     0,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   206,   217,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   127,   218,     0,
      90,     0,    92,   110,     0,     0,     0,    97,   105,   106,
      76,     0,     0,   217,     0,   217,     0,   217,     0,     0,
     220,   223,   225,   227,   229,   231,   233,   235,   244,     0,
     217,   205,     0,     0,    73,     0,     0,    80,    82,     0,
     216,    86,   216,    88,   216,   217,   207,   288,     0,    91,
      93,     0,    95,     0,     0,     0,     0,     0,   208,     0,
       0,    81,    85,    87,   209,    94,    96
  };

  const short
  parser2::yypgoto_[] =
  {
    -501,  -501,  -501,   358,   365,   369,   370,   373,  -501,  -501,
    -501,  -118,   194,  -501,  -501,  -501,   -63,  -196,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,  -501,
    -501,  -501,   554,  -501,  -330,  -324,  -322,  -501,  -501,  -501,
    -501,  -501,  -501,   -68,   -60,  -133,   -55,    89,   331,  -272,
    -500,  -501,  -501,  -501,  -501,  -501,  -501,   -50,  -501,  -501,
    -501,  -501,  -501,   -20,     9,    24,    47,    53,    84,  -501,
    -501,    94,   102,  -501,   290,   169,  -501,  -501,   178,   187,
     218,   356,  -501,  -501,  -501,  -501,  -501,    -9,    26,  -501,
       0,  -501,  -501,  -501,   215,  -501,  -501
  };

  const short
  parser2::yydefgoto_[] =
  {
       0,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,   198,   199,   326,   200,   201,   202,   448,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   435,   554,   227,   228,   229,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,    57,    58,   589,
     437,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   434,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171
  };

  const short
  parser2::yytable_[] =
  {
      35,    71,   230,   449,   172,   173,   174,    33,    29,   450,
     231,   451,    33,    30,    31,    32,    33,   523,   317,   432,
     232,    49,    50,    51,   305,   306,   307,    47,   336,    23,
      24,    25,    26,    27,    28,    64,    21,    22,   115,   247,
      65,   279,    33,    59,    28,    59,    59,    59,   436,   280,
     233,    36,    70,    67,    43,    68,    73,   325,    65,   232,
      65,   246,   331,   590,   524,   592,   248,   594,   270,   271,
    -270,    44,   458,   459,  -270,    69,   516,   526,   527,   234,
      65,   517,   517,   517,    45,    21,   111,   534,   581,   233,
      21,   111,   517,   517,   235,    34,   318,    46,   433,   274,
     285,   249,   320,    48,   477,   596,  -270,   230,   317,  -270,
     517,   608,   230,    53,   614,   231,   517,   236,   234,   517,
     231,    34,   322,   237,    66,   232,    52,    54,   279,   279,
     232,    55,   230,   235,   275,    56,   280,   280,   250,   251,
     231,    60,   319,    61,    62,    63,   232,   232,   252,   253,
     232,   317,  -270,  -270,   238,   233,   236,   254,   255,  -260,
     233,   256,   237,  -260,   239,   286,   246,   257,   258,   259,
     260,   246,   240,  -284,   261,   262,   233,   233,   263,   264,
     233,   265,   266,   346,   234,   337,   318,   246,   246,   234,
     267,   246,   268,   238,   321,  -260,   339,   308,  -260,   235,
     309,   310,   311,   281,   235,   234,   234,   312,   442,   234,
     313,   282,   314,   329,   317,   317,   330,   332,   333,   334,
     235,   235,   236,   335,   235,   340,   341,   236,   237,   318,
     344,   345,   319,   237,   303,   304,   305,   306,   307,   241,
     270,  -260,  -260,   236,   236,   352,   549,   236,   242,   237,
     237,   353,   320,   237,   449,   354,   355,   243,   230,   238,
     450,   375,   451,   569,   238,   279,   231,   356,   376,   239,
     377,   388,   400,   280,   239,   319,   232,   240,   284,   439,
     238,   238,   240,   232,   238,   446,   455,   242,   244,   456,
     239,   239,   318,   318,   239,   460,   243,   278,   240,   240,
     288,   289,   240,   461,   462,   463,   233,  -261,   598,   464,
     433,  -261,   438,   233,   518,   520,   535,   246,   522,   317,
     558,   582,   546,   607,   246,   453,   580,   244,   303,   304,
     305,   306,   307,   559,   584,   234,   568,   586,   319,   319,
     587,   595,   234,  -261,   241,   588,  -261,   591,   593,   241,
     235,   517,   600,   242,   604,   605,  -262,   235,   242,   606,
    -262,   609,   243,   611,   612,   347,   348,   243,   478,   241,
      38,   613,  -263,   236,   242,   242,  -263,    39,   242,   237,
     236,    40,    41,   243,   243,    42,   237,   243,   601,  -261,
    -261,   506,  -262,   244,   351,  -262,    72,   318,   244,   283,
     338,   550,     0,   552,     0,    75,     0,     0,  -263,    33,
     238,  -263,     0,     0,   244,   244,     0,   238,   244,     0,
     239,     0,     0,     0,     0,     0,   245,   239,   240,     0,
       0,     0,     0,     0,     0,   240,  -264,     0,  -262,  -262,
    -264,   315,     0,   319,   316,     0,     0,     0,     0,     0,
       0,   230,     0,   230,  -263,  -263,     0,     0,     0,   231,
       0,   231,   557,     0,   599,   245,     0,   602,     0,   232,
       0,   232,  -264,     0,     0,  -264,     1,     2,     3,     4,
       5,     6,     7,     8,     0,     9,     0,    21,   111,     0,
       0,   615,   616,     0,     0,   241,     0,     0,     0,   233,
       0,   233,   452,     0,   242,     0,     0,     0,     0,     0,
     246,   242,   246,   243,   230,   556,   279,   230,  -264,  -264,
     243,     0,   231,     0,   280,   231,     0,     0,   234,     0,
     234,   245,   232,     0,   232,   232,   245,     0,     0,     0,
       0,   230,   230,   235,   244,   235,     0,     0,     0,   231,
     231,   244,   245,   245,     0,    10,   245,     0,     0,   232,
     232,     0,   233,  -265,   233,   233,   236,  -265,   236,     0,
       0,     0,   237,   246,   237,   246,   246,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -266,   233,
     233,   234,  -266,   234,   234,     0,     0,     0,     0,  -265,
     246,   246,  -265,   238,     0,   238,   235,     0,   235,   235,
       0,     0,     0,   239,     0,   239,     0,     0,   234,   234,
     116,   240,     0,   240,  -266,     0,     0,  -266,     0,   236,
       0,   236,   236,   235,   235,   237,  -267,   237,   237,     0,
    -267,     0,     0,     0,    75,  -265,  -265,     0,    33,     0,
       0,     0,     0,     0,     0,     0,   236,   236,   269,     0,
     272,   273,   237,   237,     0,     0,   238,     0,   238,   238,
    -266,  -266,  -267,     0,     0,  -267,   239,     0,   239,   239,
     315,     0,   245,   361,   240,     0,   240,   240,   241,   245,
     241,     0,     0,   238,   238,     0,     0,   242,     0,   242,
       0,     0,     0,   239,   239,     0,   243,     0,   243,     0,
       0,   240,   240,     0,     0,     0,     0,     0,  -267,  -267,
       0,     0,     0,     0,     0,     0,    21,   111,     0,     0,
     327,   328,     0,     0,     0,     0,     0,   244,     0,   244,
       0,     0,     0,   343,     0,     0,     0,     0,     0,     0,
       0,   241,     0,   452,   241,     0,     0,     0,     0,     0,
     242,     0,   242,   242,     0,     0,     0,     0,     0,   243,
       0,   243,   243,     0,     0,     0,     0,     0,   241,   241,
       0,     0,     0,     0,     0,     0,     0,   242,   242,     0,
       0,     0,     0,     0,     0,     0,   243,   243,     0,     0,
     244,     0,   244,   244,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,     0,   389,   390,   391,   392,   393,
     394,   395,   396,     0,   399,     0,     0,   244,   244,     0,
     401,     0,     0,     0,    75,     0,     0,     0,    33,     0,
       0,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,   429,   431,
     315,     0,     0,   361,     0,   245,     0,   245,     0,     0,
       0,   362,   363,     0,   445,     0,   447,   357,   358,   454,
       0,   359,   360,     0,     0,     0,     0,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,     0,    75,
       0,     0,     0,    33,     0,     0,    21,   111,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
       1,     2,     3,     4,     5,     6,     7,     8,   245,     9,
     245,   245,     0,     0,     0,   315,     0,     0,   361,     0,
       0,     0,   504,     0,     0,     0,   362,   363,     0,     0,
       0,     0,     0,     0,     0,   245,   245,     0,     0,     0,
       0,     0,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,     0,   399,   505,     0,     0,     0,     0,
       0,    21,   111,   287,     0,     0,     0,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,    37,
       0,     0,     0,     0,   528,   529,   530,   531,   532,     0,
       0,     0,   300,   301,   302,   303,   304,   305,   306,   307,
       0,     0,     0,   536,     0,     0,   537,     0,   538,     0,
     539,     0,   540,     0,   541,     0,   542,     0,   543,     0,
       0,     0,     0,     0,     0,     0,   544,     0,     0,     0,
       0,   547,     0,   175,     0,     0,     0,     0,     0,     0,
       0,   548,     0,     0,   551,     0,   553,   555,   176,   177,
       0,     0,   178,   179,     0,   180,   181,   182,   183,     0,
     184,   185,   186,   187,   188,   189,   190,   191,    75,   579,
       0,     0,    33,    79,    80,    81,    82,   192,    83,    84,
       0,     0,     0,     0,     0,     0,     0,    91,     0,     0,
       0,     0,     0,    97,    98,    99,   100,   101,   102,     0,
       0,     0,    70,   193,   194,     0,     0,     0,     0,     0,
     603,     0,   195,   175,     0,   196,   197,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   176,   177,
       0,     0,   178,   179,     0,   180,   181,   182,   183,     0,
     184,   185,   186,   187,   188,   189,   190,   191,    75,     0,
      21,   111,    33,    79,    80,    81,    82,   192,    83,    84,
       0,     0,     0,     0,     0,     0,     0,    91,     0,     0,
       0,     0,     0,    97,    98,    99,   100,   101,   102,   323,
       0,     0,    70,   349,   194,     0,     0,     0,     0,     0,
       0,     0,   350,   176,   177,   196,   197,   178,   179,     0,
     180,   181,   182,   183,     0,   184,   185,   186,   187,   188,
     189,   190,   191,    75,     0,     0,     0,    33,    79,    80,
      81,    82,   192,    83,    84,     0,     0,     0,     0,     0,
      21,   111,    91,     0,     0,     0,     0,     0,    97,    98,
      99,   100,   101,   102,   440,     0,     0,    70,     0,   194,
       0,     0,     0,     0,     0,     0,     0,   324,   176,   177,
     196,   197,   178,   179,     0,   180,   181,   182,   183,     0,
     184,   185,   186,   187,   188,   189,   190,   191,    75,     0,
       0,     0,    33,    79,    80,    81,    82,   192,    83,    84,
       0,     0,     0,     0,     0,    21,   111,    91,     0,     0,
      74,     0,     0,    97,    98,    99,   100,   101,   102,     0,
       0,     0,    70,     0,   194,     0,     0,     0,     0,     0,
       0,     0,   441,     0,     0,   196,   197,    75,    76,    77,
      78,    33,    79,    80,    81,    82,     0,    83,    84,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
      21,   111,     0,   105,     0,     0,     0,     0,    75,     0,
       0,   342,    33,    79,    80,    81,    82,     0,    83,    84,
       0,     0,     0,     0,     0,     0,     0,    91,   106,   107,
      74,     0,     0,    97,    98,    99,   100,   101,   102,     0,
     276,     0,   108,     0,   194,   109,     0,     0,   110,    21,
     111,    28,   112,   113,   114,   115,     0,    75,    76,    77,
      78,    33,    79,    80,    81,    82,     0,    83,    84,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
      21,   111,     0,   430,   271,   277,   278,     0,    75,     0,
       0,     0,    33,    79,    80,    81,    82,     0,    83,    84,
       0,     0,     0,     0,     0,     0,     0,    91,   106,   107,
      74,     0,     0,    97,    98,    99,   100,   101,   102,     0,
       0,     0,   108,     0,   194,   109,     0,     0,   110,    21,
     111,    28,   112,   113,   114,   115,     0,    75,    76,    77,
      78,    33,    79,    80,    81,    82,     0,    83,    84,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
      21,   111,   507,   105,   287,     0,     0,     0,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
       0,     0,     0,     0,     0,     0,     0,     0,   106,   107,
      74,     0,     0,   300,   301,   302,   303,   304,   305,   306,
     307,     0,   108,     0,     0,   109,     0,     0,   110,    21,
     111,    28,   112,   113,   114,   115,     0,    75,    76,    77,
      78,    33,    79,    80,    81,    82,     0,    83,    84,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
       0,     0,     0,   430,     0,     0,     0,     0,     0,     0,
       0,    75,     0,     0,     0,    33,    79,    80,    81,    82,
       0,    83,    84,     0,     0,     0,     0,     0,   106,   107,
      91,     0,     0,     0,     0,     0,    97,    98,    99,   100,
     101,   102,   108,     0,     0,   109,     0,   194,   110,    21,
     111,    28,   112,   113,   114,   115,   176,   177,   196,   197,
     178,   179,     0,   180,   181,   182,   183,     0,   184,   185,
     186,   187,   188,   189,   190,   191,    75,     0,     0,     0,
      33,    79,    80,    81,    82,   192,    83,    84,     0,     0,
       0,     0,     0,    21,   111,    91,     0,     0,     0,     0,
       0,    97,    98,    99,   100,   101,   102,     0,     0,     0,
      70,     0,   194,     0,     0,     0,     0,     0,     0,     0,
     397,     0,     0,   196,   197,   398,     0,     0,     0,     0,
       0,     0,   287,     0,     0,     0,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,   111,
       0,   300,   301,   302,   303,   304,   305,   306,   307,   481,
       0,     0,     0,     0,   482,     0,     0,     0,     0,     0,
       0,   287,     0,     0,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   288,   289,     0,
       0,   292,   293,   294,   295,   296,   297,   298,   299,     0,
     300,   301,   302,   303,   304,   305,   306,   307,   483,     0,
       0,     0,     0,   484,     0,   303,   304,   305,   306,   307,
     287,     0,     0,     0,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   288,   289,     0,     0,
     292,   293,     0,     0,   296,   297,   298,   299,     0,   300,
     301,   302,   303,   304,   305,   306,   307,   485,     0,     0,
       0,     0,   486,     0,   303,   304,   305,   306,   307,   287,
       0,     0,     0,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   300,   301,
     302,   303,   304,   305,   306,   307,   487,     0,     0,     0,
       0,   488,     0,     0,     0,     0,     0,     0,   287,     0,
       0,     0,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   300,   301,   302,
     303,   304,   305,   306,   307,   489,     0,     0,     0,     0,
     490,     0,     0,     0,     0,     0,     0,   287,     0,     0,
       0,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   300,   301,   302,   303,
     304,   305,   306,   307,   491,     0,     0,     0,     0,   492,
       0,     0,     0,     0,     0,     0,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   493,     0,     0,     0,     0,   494,     0,
       0,     0,     0,     0,     0,   287,     0,     0,     0,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   300,   301,   302,   303,   304,   305,
     306,   307,   562,     0,     0,     0,     0,   563,     0,     0,
       0,     0,     0,     0,   287,     0,     0,     0,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   300,   301,   302,   303,   304,   305,   306,
     307,   564,     0,     0,     0,     0,   565,     0,     0,     0,
       0,     0,     0,   287,     0,     0,     0,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   300,   301,   302,   303,   304,   305,   306,   307,
     566,     0,     0,     0,     0,   567,     0,     0,     0,     0,
       0,     0,   287,     0,     0,     0,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   480,     0,     0,
       0,   300,   301,   302,   303,   304,   305,   306,   307,   287,
       0,     0,     0,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   495,     0,     0,     0,   300,   301,
     302,   303,   304,   305,   306,   307,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   496,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   287,     0,     0,     0,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   497,     0,
       0,     0,   300,   301,   302,   303,   304,   305,   306,   307,
     287,     0,     0,     0,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   498,     0,     0,     0,   300,
     301,   302,   303,   304,   305,   306,   307,   287,     0,     0,
       0,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   499,     0,     0,     0,   300,   301,   302,   303,
     304,   305,   306,   307,   287,     0,     0,     0,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   500,
       0,     0,     0,   300,   301,   302,   303,   304,   305,   306,
     307,   287,     0,     0,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   501,     0,     0,     0,
     300,   301,   302,   303,   304,   305,   306,   307,   287,     0,
       0,     0,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   503,     0,     0,     0,   300,   301,   302,
     303,   304,   305,   306,   307,   287,     0,     0,     0,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     397,     0,     0,     0,   300,   301,   302,   303,   304,   305,
     306,   307,   287,     0,     0,     0,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   519,     0,     0,
       0,   300,   301,   302,   303,   304,   305,   306,   307,   287,
       0,     0,     0,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   521,     0,     0,     0,   300,   301,
     302,   303,   304,   305,   306,   307,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   525,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   287,     0,     0,     0,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   561,     0,
       0,     0,   300,   301,   302,   303,   304,   305,   306,   307,
     287,     0,     0,     0,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   570,     0,     0,     0,   300,
     301,   302,   303,   304,   305,   306,   307,   287,     0,     0,
       0,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   571,     0,     0,     0,   300,   301,   302,   303,
     304,   305,   306,   307,   287,     0,     0,     0,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   572,
       0,     0,     0,   300,   301,   302,   303,   304,   305,   306,
     307,   287,     0,     0,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   573,     0,     0,     0,
     300,   301,   302,   303,   304,   305,   306,   307,   287,     0,
       0,     0,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   574,     0,     0,     0,   300,   301,   302,
     303,   304,   305,   306,   307,   287,     0,     0,     0,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     575,     0,     0,     0,   300,   301,   302,   303,   304,   305,
     306,   307,   287,     0,     0,     0,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   576,     0,     0,
       0,   300,   301,   302,   303,   304,   305,   306,   307,   287,
       0,     0,     0,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   577,     0,     0,     0,   300,   301,
     302,   303,   304,   305,   306,   307,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   578,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   287,     0,     0,     0,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   583,     0,
       0,     0,   300,   301,   302,   303,   304,   305,   306,   307,
     287,     0,     0,     0,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   585,     0,     0,     0,   300,
     301,   302,   303,   304,   305,   306,   307,   287,     0,     0,
       0,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   597,     0,     0,     0,   300,   301,   302,   303,
     304,   305,   306,   307,   287,     0,     0,     0,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   610,
       0,     0,     0,   300,   301,   302,   303,   304,   305,   306,
     307,   287,     0,     0,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     300,   301,   302,   303,   304,   305,   306,   307,   508,     0,
       0,     0,     0,     0,     0,     0,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   509,     0,     0,     0,     0,     0,     0,
       0,   287,     0,     0,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     300,   301,   302,   303,   304,   305,   306,   307,   510,     0,
       0,     0,     0,     0,     0,     0,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   511,     0,     0,     0,     0,     0,     0,
       0,   287,     0,     0,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     300,   301,   302,   303,   304,   305,   306,   307,   512,     0,
       0,     0,     0,     0,     0,     0,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   513,     0,     0,     0,     0,     0,     0,
       0,   287,     0,     0,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     300,   301,   302,   303,   304,   305,   306,   307,   514,     0,
       0,     0,     0,     0,     0,     0,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   515,     0,     0,     0,     0,     0,     0,
       0,   287,     0,     0,     0,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     300,   301,   302,   303,   304,   305,   306,   307,   533,     0,
       0,     0,     0,     0,     0,     0,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   479,     0,     0,     0,     0,     0,     0,
     287,     0,     0,     0,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   300,
     301,   302,   303,   304,   305,   306,   307,   502,     0,     0,
       0,     0,     0,     0,   287,     0,     0,     0,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   300,   301,   302,   303,   304,   305,   306,
     307,   545,     0,     0,     0,     0,     0,     0,   287,     0,
       0,     0,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   300,   301,   302,
     303,   304,   305,   306,   307,   443,   287,     0,     0,     0,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   300,   301,   302,   303,   304,
     305,   306,   307,   444,   287,     0,     0,     0,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   300,   301,   302,   303,   304,   305,   306,
     307,   457,   287,     0,     0,     0,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   300,   301,   302,   303,   304,   305,   306,   307,   560,
     287,     0,     0,     0,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   300,
     301,   302,   303,   304,   305,   306,   307,   287,     0,     0,
       0,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   288,   289,     0,   291,   292,   293,   294,
     295,   296,   297,   298,   299,     0,   300,   301,   302,   303,
     304,   305,   306,   307,     0,     0,     0,     0,   300,   301,
     302,   303,   304,   305,   306,   307,   288,   289,     0,     0,
     292,   293,   294,   295,   296,   297,   298,   299,   288,   289,
       0,     0,   292,   293,   294,   295,   296,   297,   298,   299,
       0,   300,   301,   302,   303,   304,   305,   306,   307,     0,
       0,     0,     0,     0,   301,   302,   303,   304,   305,   306,
     307,   288,   289,     0,     0,   292,   293,   294,   295,   296,
     297,   298,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   301,     0,   303,
     304,   305,   306,   307
  };

  const short
  parser2::yycheck_[] =
  {
       9,    64,    70,   333,    67,    68,    69,    43,     8,   333,
      70,   333,    43,    14,    15,    16,    43,    30,   151,    43,
      70,    30,    31,    32,   118,   119,   120,    27,   117,     3,
       4,     5,     6,    71,   123,    72,   121,   122,   127,    75,
      77,   109,    43,    52,   123,    54,    55,    56,   320,   109,
      70,     0,    73,    72,    83,    72,    65,   175,    77,   109,
      77,    70,   180,   563,    77,   565,    75,   567,    75,    76,
      39,    83,   344,   345,    43,    72,    72,    72,    72,    70,
      77,    77,    77,    77,    83,   121,   122,    72,    72,   109,
     121,   122,    77,    77,    70,   122,   151,    83,   122,   108,
     109,    75,    71,    83,   376,    72,    75,   175,   241,    78,
      77,    72,   180,    72,    72,   175,    77,    70,   109,    77,
     180,   122,    78,    70,   102,   175,    71,    71,   196,   197,
     180,    71,   200,   109,   108,    71,   196,   197,    71,    71,
     200,    83,   151,    54,    55,    56,   196,   197,    71,    71,
     200,   284,   121,   122,    70,   175,   109,    71,    71,    39,
     180,    71,   109,    43,    70,   122,   175,    71,    71,    71,
      71,   180,    70,    81,    71,    71,   196,   197,    71,    71,
     200,    71,    71,   192,   175,   185,   241,   196,   197,   180,
      71,   200,    71,   109,    81,    75,    82,    75,    78,   175,
      75,    75,    75,   109,   180,   196,   197,    75,   326,   200,
      75,   109,    75,    83,   347,   348,    71,    71,    71,    71,
     196,   197,   175,    71,   200,    83,    83,   180,   175,   284,
      71,    71,   241,   180,   116,   117,   118,   119,   120,    70,
      75,   121,   122,   196,   197,    83,   518,   200,    70,   196,
     197,    83,    71,   200,   584,    83,    83,    70,   326,   175,
     584,    75,   584,   535,   180,   333,   326,    83,    71,   175,
      81,    72,    81,   333,   180,   284,   326,   175,   109,    43,
     196,   197,   180,   333,   200,    27,    82,   109,    70,    82,
     196,   197,   347,   348,   200,   102,   109,   127,   196,   197,
      88,    89,   200,    71,    71,    71,   326,    39,   580,    71,
     122,    43,   321,   333,    71,    71,    71,   326,    83,   452,
      83,    25,    76,   595,   333,   334,    71,   109,   116,   117,
     118,   119,   120,    83,    83,   326,    76,    30,   347,   348,
      83,    71,   333,    75,   175,    83,    78,    83,    83,   180,
     326,    77,    83,   175,    72,    72,    39,   333,   180,    72,
      43,    72,   175,    83,    83,   196,   197,   180,   377,   200,
      12,    83,    39,   326,   196,   197,    43,    12,   200,   326,
     333,    12,    12,   196,   197,    12,   333,   200,   584,   121,
     122,   400,    75,   175,   200,    78,    65,   452,   180,   109,
     185,   519,    -1,   521,    -1,    39,    -1,    -1,    75,    43,
     326,    78,    -1,    -1,   196,   197,    -1,   333,   200,    -1,
     326,    -1,    -1,    -1,    -1,    -1,    70,   333,   326,    -1,
      -1,    -1,    -1,    -1,    -1,   333,    39,    -1,   121,   122,
      43,    75,    -1,   452,    78,    -1,    -1,    -1,    -1,    -1,
      -1,   519,    -1,   521,   121,   122,    -1,    -1,    -1,   519,
      -1,   521,   525,    -1,   582,   109,    -1,   585,    -1,   519,
      -1,   521,    75,    -1,    -1,    78,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,    -1,   121,   122,    -1,
      -1,   609,   610,    -1,    -1,   326,    -1,    -1,    -1,   519,
      -1,   521,   333,    -1,   326,    -1,    -1,    -1,    -1,    -1,
     519,   333,   521,   326,   582,   524,   584,   585,   121,   122,
     333,    -1,   582,    -1,   584,   585,    -1,    -1,   519,    -1,
     521,   175,   582,    -1,   584,   585,   180,    -1,    -1,    -1,
      -1,   609,   610,   519,   326,   521,    -1,    -1,    -1,   609,
     610,   333,   196,   197,    -1,    83,   200,    -1,    -1,   609,
     610,    -1,   582,    39,   584,   585,   519,    43,   521,    -1,
      -1,    -1,   519,   582,   521,   584,   585,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,   609,
     610,   582,    43,   584,   585,    -1,    -1,    -1,    -1,    75,
     609,   610,    78,   519,    -1,   521,   582,    -1,   584,   585,
      -1,    -1,    -1,   519,    -1,   521,    -1,    -1,   609,   610,
      66,   519,    -1,   521,    75,    -1,    -1,    78,    -1,   582,
      -1,   584,   585,   609,   610,   582,    39,   584,   585,    -1,
      43,    -1,    -1,    -1,    39,   121,   122,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   609,   610,   104,    -1,
     106,   107,   609,   610,    -1,    -1,   582,    -1,   584,   585,
     121,   122,    75,    -1,    -1,    78,   582,    -1,   584,   585,
      75,    -1,   326,    78,   582,    -1,   584,   585,   519,   333,
     521,    -1,    -1,   609,   610,    -1,    -1,   519,    -1,   521,
      -1,    -1,    -1,   609,   610,    -1,   519,    -1,   521,    -1,
      -1,   609,   610,    -1,    -1,    -1,    -1,    -1,   121,   122,
      -1,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,    -1,
     176,   177,    -1,    -1,    -1,    -1,    -1,   519,    -1,   521,
      -1,    -1,    -1,   189,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   582,    -1,   584,   585,    -1,    -1,    -1,    -1,    -1,
     582,    -1,   584,   585,    -1,    -1,    -1,    -1,    -1,   582,
      -1,   584,   585,    -1,    -1,    -1,    -1,    -1,   609,   610,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   609,   610,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   609,   610,    -1,    -1,
     582,    -1,   584,   585,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,    -1,   261,   262,   263,   264,   265,
     266,   267,   268,    -1,   270,    -1,    -1,   609,   610,    -1,
     276,    -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    -1,
      -1,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
      75,    -1,    -1,    78,    -1,   519,    -1,   521,    -1,    -1,
      -1,    86,    87,    -1,   330,    -1,   332,    17,    18,   335,
      -1,    21,    22,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,    -1,    39,
      -1,    -1,    -1,    43,    -1,    -1,   121,   122,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
       4,     5,     6,     7,     8,     9,    10,    11,   582,    13,
     584,   585,    -1,    -1,    -1,    75,    -1,    -1,    78,    -1,
      -1,    -1,   398,    -1,    -1,    -1,    86,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   609,   610,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,    -1,   430,    76,    -1,    -1,    -1,    -1,
      -1,   121,   122,    84,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,    83,
      -1,    -1,    -1,    -1,   460,   461,   462,   463,   464,    -1,
      -1,    -1,   113,   114,   115,   116,   117,   118,   119,   120,
      -1,    -1,    -1,   479,    -1,    -1,   482,    -1,   484,    -1,
     486,    -1,   488,    -1,   490,    -1,   492,    -1,   494,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   502,    -1,    -1,    -1,
      -1,   507,    -1,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   517,    -1,    -1,   520,    -1,   522,   523,    19,    20,
      -1,    -1,    23,    24,    -1,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,   545,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
     586,    -1,    83,     4,    -1,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,
      -1,    -1,    23,    24,    -1,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
     121,   122,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,     5,
      -1,    -1,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    19,    20,    86,    87,    23,    24,    -1,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
     121,   122,    58,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,     5,    -1,    -1,    73,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    19,    20,
      86,    87,    23,    24,    -1,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,   121,   122,    58,    -1,    -1,
      12,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    73,    -1,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    -1,    -1,    86,    87,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
     121,   122,    -1,    75,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    83,    43,    44,    45,    46,    47,    -1,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,   100,   101,
      12,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      71,    -1,   114,    -1,    75,   117,    -1,    -1,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
     121,   122,    -1,    75,    76,   126,   127,    -1,    39,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    -1,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,   100,   101,
      12,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,   114,    -1,    75,   117,    -1,    -1,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
     121,   122,    82,    75,    84,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,   101,
      12,    -1,    -1,   113,   114,   115,   116,   117,   118,   119,
     120,    -1,   114,    -1,    -1,   117,    -1,    -1,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    44,    45,    46,    47,
      -1,    49,    50,    -1,    -1,    -1,    -1,    -1,   100,   101,
      58,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
      68,    69,   114,    -1,    -1,   117,    -1,    75,   120,   121,
     122,   123,   124,   125,   126,   127,    19,    20,    86,    87,
      23,    24,    -1,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    44,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,   121,   122,    58,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      73,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    -1,    86,    87,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,
      -1,   113,   114,   115,   116,   117,   118,   119,   120,    72,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    88,    89,    -1,
      -1,    92,    93,    94,    95,    96,    97,    98,    99,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,    72,    -1,
      -1,    -1,    -1,    77,    -1,   116,   117,   118,   119,   120,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    88,    89,    -1,    -1,
      92,    93,    -1,    -1,    96,    97,    98,    99,    -1,   113,
     114,   115,   116,   117,   118,   119,   120,    72,    -1,    -1,
      -1,    -1,    77,    -1,   116,   117,   118,   119,   120,    84,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,   114,
     115,   116,   117,   118,   119,   120,    72,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,
     116,   117,   118,   119,   120,    72,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,
     117,   118,   119,   120,    72,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    72,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,   118,
     119,   120,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,   114,   115,   116,   117,   118,   119,
     120,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   113,   114,   115,   116,   117,   118,   119,   120,
      72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,   113,   114,   115,   116,   117,   118,   119,   120,    84,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,   113,   114,
     115,   116,   117,   118,   119,   120,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    84,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,
      -1,    -1,   113,   114,   115,   116,   117,   118,   119,   120,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,   113,
     114,   115,   116,   117,   118,   119,   120,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    -1,   113,   114,   115,   116,
     117,   118,   119,   120,    84,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    -1,   113,   114,   115,   116,   117,   118,   119,
     120,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,    84,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    -1,    -1,    -1,   113,   114,   115,
     116,   117,   118,   119,   120,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    -1,    -1,   113,   114,   115,   116,   117,   118,
     119,   120,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,   113,   114,   115,   116,   117,   118,   119,   120,    84,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,   113,   114,
     115,   116,   117,   118,   119,   120,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    84,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,
      -1,    -1,   113,   114,   115,   116,   117,   118,   119,   120,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,   113,
     114,   115,   116,   117,   118,   119,   120,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    -1,   113,   114,   115,   116,
     117,   118,   119,   120,    84,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    -1,   113,   114,   115,   116,   117,   118,   119,
     120,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,    84,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    -1,    -1,    -1,   113,   114,   115,
     116,   117,   118,   119,   120,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    -1,    -1,   113,   114,   115,   116,   117,   118,
     119,   120,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,   113,   114,   115,   116,   117,   118,   119,   120,    84,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,   113,   114,
     115,   116,   117,   118,   119,   120,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    84,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,
      -1,    -1,   113,   114,   115,   116,   117,   118,   119,   120,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,   113,
     114,   115,   116,   117,   118,   119,   120,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    -1,   113,   114,   115,   116,
     117,   118,   119,   120,    84,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    -1,   113,   114,   115,   116,   117,   118,   119,
     120,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
     114,   115,   116,   117,   118,   119,   120,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,   114,   115,   116,   117,   118,   119,
     120,    77,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,   114,   115,
     116,   117,   118,   119,   120,    83,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   113,   114,   115,   116,   117,
     118,   119,   120,    83,    84,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   113,   114,   115,   116,   117,   118,   119,
     120,    83,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   113,   114,   115,   116,   117,   118,   119,   120,    83,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   113,
     114,   115,   116,   117,   118,   119,   120,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    88,    89,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    -1,   113,   114,   115,   116,
     117,   118,   119,   120,    -1,    -1,    -1,    -1,   113,   114,
     115,   116,   117,   118,   119,   120,    88,    89,    -1,    -1,
      92,    93,    94,    95,    96,    97,    98,    99,    88,    89,
      -1,    -1,    92,    93,    94,    95,    96,    97,    98,    99,
      -1,   113,   114,   115,   116,   117,   118,   119,   120,    -1,
      -1,    -1,    -1,    -1,   114,   115,   116,   117,   118,   119,
     120,    88,    89,    -1,    -1,    92,    93,    94,    95,    96,
      97,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,   116,
     117,   118,   119,   120
  };

  const unsigned char
  parser2::yystos_[] =
  {
       0,     4,     5,     6,     7,     8,     9,    10,    11,    13,
      83,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   121,   122,   235,   235,   235,   235,    71,   123,   237,
      14,    15,    16,    43,   122,   234,     0,    83,   140,   141,
     142,   143,   144,    83,    83,    83,    83,   237,    83,   234,
     234,   234,    71,    72,    71,    71,    71,   194,   195,   234,
      83,   194,   194,   194,    72,    77,   102,    72,    72,    72,
      73,   153,   195,   234,    12,    39,    40,    41,    42,    44,
      45,    46,    47,    49,    50,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    75,   100,   101,   114,   117,
     120,   122,   124,   125,   126,   127,   179,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   153,   153,   153,     4,    19,    20,    23,    24,
      26,    27,    28,    29,    31,    32,    33,    34,    35,    36,
      37,    38,    48,    74,    75,    83,    86,    87,   148,   149,
     151,   152,   153,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   181,   182,   183,
     190,   191,   204,   210,   211,   212,   213,   214,   215,   218,
     219,   222,   225,   226,   227,   228,   234,    75,   234,   235,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,   179,
      75,    76,   179,   179,   234,   235,    71,   126,   127,   190,
     191,   218,   219,   221,   222,   234,   122,    84,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     113,   114,   115,   116,   117,   118,   119,   120,    75,    75,
      75,    75,    75,    75,    75,    75,    78,   192,   193,   234,
      71,    81,    78,     5,    83,   148,   150,   179,   179,    83,
      71,   148,    71,    71,    71,    71,   117,   237,   241,    82,
      83,    83,    83,   179,    71,    71,   234,   222,   222,    74,
      83,   149,    83,    83,    83,    83,    83,    17,    18,    21,
      22,    78,    86,    87,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,    75,    71,    81,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,    72,   179,
     179,   179,   179,   179,   179,   179,   179,    72,    77,   179,
      81,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
      75,   179,    43,   122,   233,   179,   196,   197,   234,    43,
       5,    83,   148,    83,    83,   179,    27,   179,   154,   181,
     182,   183,   222,   234,   179,    82,    82,    83,   196,   196,
     102,    71,    71,    71,    71,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   196,   234,    77,
      72,    72,    77,    72,    77,    72,    77,    72,    77,    72,
      77,    72,    77,    72,    77,    72,    72,    72,    72,    72,
      72,    72,    77,    72,   179,    76,   234,    82,    76,    76,
      76,    76,    76,    76,    76,    76,    72,    77,    71,    72,
      71,    72,    83,    30,    77,    72,    72,    72,   179,   179,
     179,   179,   179,    76,    72,    71,   179,   179,   179,   179,
     179,   179,   179,   179,   179,    77,    76,   179,   179,   196,
     148,   179,   148,   179,   180,   179,   234,   153,    83,    83,
      83,    72,    72,    77,    72,    77,    72,    77,    76,   196,
      72,    72,    72,    72,    72,    72,    72,    72,    72,   179,
      71,    72,    25,    72,    83,    72,    30,    83,    83,   196,
     197,    83,   197,    83,   197,    71,    72,    72,   196,   148,
      83,   154,   148,   179,    72,    72,    72,   196,    72,    72,
      72,    83,    83,    83,    72,   148,   148
  };

  const unsigned char
  parser2::yyr1_[] =
  {
       0,   137,   138,   138,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   140,   141,   142,   143,
     144,   144,   144,   144,   144,   145,   146,   147,   147,   147,
     147,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   149,   149,   150,   150,
     150,   150,   151,   151,   151,   151,   152,   152,   153,   153,
     154,   154,   154,   154,   155,   155,   156,   157,   157,   157,
     158,   159,   159,   160,   161,   162,   162,   163,   163,   164,
     165,   166,   167,   168,   169,   170,   170,   171,   172,   172,
     173,   174,   175,   176,   176,   177,   178,   179,   179,   179,
     180,   180,   181,   181,   182,   182,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   184,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   187,   188,   188,   188,   188,   189,
     190,   190,   191,   191,   192,   192,   192,   192,   193,   193,
     194,   194,   194,   194,   194,   195,   196,   196,   197,   197,
     198,   199,   200,   200,   201,   201,   202,   202,   203,   203,
     204,   204,   205,   205,   206,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   217,   218,   218,
     218,   218,   218,   218,   218,   218,   219,   220,   220,   221,
     222,   222,   222,   222,   222,   222,   222,   222,   222,   222,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   234,   235,   235,   236,   237,   238,   239,
     240,   240,   241,   241,   242,   243
  };

  const signed char
  parser2::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     3,     5,     6,     7,     7,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       1,     1,     2,     2,     4,     6,     5,     7,     8,     9,
       3,     3,     1,     1,     0,     3,     1,     0,     3,     1,
       6,     4,     4,     6,     4,     6,     4,     6,     4,     6,
       4,     6,     4,     6,     4,     6,     4,     3,     4,     4,
       4,     4,     4,     4,     6,     4,     2,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     7,     1,
       2,     1,     2,     1,     1,     1
  };




#if ARC2DEBUG
  const short
  parser2::yyrline_[] =
  {
       0,   314,   314,   315,   319,   321,   323,   325,   327,   329,
     331,   333,   335,   337,   339,   341,   346,   350,   354,   359,
     364,   365,   366,   367,   368,   372,   377,   382,   384,   386,
     388,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   421,   422,   426,   428,
     430,   432,   437,   439,   441,   443,   448,   449,   453,   454,
     458,   460,   462,   465,   469,   471,   476,   481,   483,   485,
     490,   495,   497,   502,   507,   512,   514,   519,   521,   526,
     531,   536,   541,   546,   551,   556,   562,   570,   577,   579,
     584,   589,   594,   599,   601,   606,   611,   616,   617,   618,
     622,   623,   627,   629,   634,   636,   641,   643,   645,   647,
     649,   651,   653,   655,   657,   659,   661,   666,   671,   673,
     675,   677,   679,   681,   683,   685,   687,   689,   691,   693,
     695,   697,   699,   701,   703,   705,   707,   709,   714,   715,
     716,   717,   718,   719,   720,   721,   722,   723,   724,   725,
     726,   727,   728,   729,   730,   731,   732,   733,   734,   735,
     736,   737,   738,   739,   740,   741,   742,   743,   744,   745,
     746,   747,   748,   749,   750,   751,   752,   753,   754,   755,
     756,   757,   758,   759,   763,   768,   770,   772,   774,   779,
     784,   785,   789,   796,   806,   808,   810,   812,   817,   819,
     824,   826,   828,   830,   833,   837,   842,   845,   849,   851,
     856,   861,   866,   868,   873,   875,   880,   882,   887,   889,
     894,   896,   901,   903,   908,   910,   915,   920,   925,   930,
     935,   940,   945,   950,   955,   960,   965,   967,   972,   974,
     976,   978,   980,   982,   984,   986,   991,   996,   998,  1003,
    1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,
    1018,  1022,  1027,  1032,  1037,  1042,  1047,  1052,  1057,  1062,
    1067,  1072,  1077,  1079,  1084,  1086,  1091,  1096,  1101,  1106,
    1111,  1113,  1118,  1120,  1125,  1130
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
#line 5895 "parser2.cpp"

#line 1134 "parser2.ypp"


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
