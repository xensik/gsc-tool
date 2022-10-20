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
#line 38 "parser.ypp"

#include "stdafx.hpp"
#include "parser.hpp"
#include "lexer.hpp"
using namespace xsk::arc;
xsk::arc::t6::parser::symbol_type T6lex(xsk::arc::t6::lexer& lexer);

#line 47 "parser.cpp"

// Take the name prefix into account.
#define yylex   T6lex



#include "parser.hpp"




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
#if T6DEBUG

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

#else // !T6DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !T6DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace arc { namespace t6 {
#line 149 "parser.cpp"

  /// Build a parser object.
  parser::parser (xsk::arc::t6::lexer& lexer_yyarg, xsk::arc::ast::program::ptr& ast_yyarg)
#if T6DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      lexer (lexer_yyarg),
      ast (ast_yyarg)
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
        value.YY_MOVE_OR_COPY< ast::call > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< ast::decl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_thread: // decl_thread
        value.YY_MOVE_OR_COPY< ast::decl_thread::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.YY_MOVE_OR_COPY< ast::decl_usingtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_literal: // expr_literal
      case symbol_kind::S_expr_object: // expr_object
        value.YY_MOVE_OR_COPY< ast::expr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        value.YY_MOVE_OR_COPY< ast::expr_abs::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        value.YY_MOVE_OR_COPY< ast::expr_angleclamp180::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        value.YY_MOVE_OR_COPY< ast::expr_anglestoforward::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        value.YY_MOVE_OR_COPY< ast::expr_anglestoright::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        value.YY_MOVE_OR_COPY< ast::expr_anglestoup::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.YY_MOVE_OR_COPY< ast::expr_anim::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.YY_MOVE_OR_COPY< ast::expr_animation::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.YY_MOVE_OR_COPY< ast::expr_animtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.YY_MOVE_OR_COPY< ast::expr_arguments::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.YY_MOVE_OR_COPY< ast::expr_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.YY_MOVE_OR_COPY< ast::expr_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.YY_MOVE_OR_COPY< ast::expr_complement::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.YY_MOVE_OR_COPY< ast::expr_empty_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.YY_MOVE_OR_COPY< ast::expr_false::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.YY_MOVE_OR_COPY< ast::expr_field::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.YY_MOVE_OR_COPY< ast::expr_float::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.YY_MOVE_OR_COPY< ast::expr_game::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        value.YY_MOVE_OR_COPY< ast::expr_getdvar::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        value.YY_MOVE_OR_COPY< ast::expr_getdvarcoloralpha::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        value.YY_MOVE_OR_COPY< ast::expr_getdvarcolorblue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        value.YY_MOVE_OR_COPY< ast::expr_getdvarcolorgreen::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        value.YY_MOVE_OR_COPY< ast::expr_getdvarcolorred::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        value.YY_MOVE_OR_COPY< ast::expr_getdvarfloat::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        value.YY_MOVE_OR_COPY< ast::expr_getdvarint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        value.YY_MOVE_OR_COPY< ast::expr_getdvarvector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        value.YY_MOVE_OR_COPY< ast::expr_getfirstarraykey::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        value.YY_MOVE_OR_COPY< ast::expr_getnextarraykey::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        value.YY_MOVE_OR_COPY< ast::expr_gettime::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        value.YY_MOVE_OR_COPY< ast::expr_hash::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.YY_MOVE_OR_COPY< ast::expr_identifier::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.YY_MOVE_OR_COPY< ast::expr_integer::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.YY_MOVE_OR_COPY< ast::expr_isdefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.YY_MOVE_OR_COPY< ast::expr_istring::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.YY_MOVE_OR_COPY< ast::expr_level::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.YY_MOVE_OR_COPY< ast::expr_method::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.YY_MOVE_OR_COPY< ast::expr_negate::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.YY_MOVE_OR_COPY< ast::expr_not::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.YY_MOVE_OR_COPY< ast::expr_parameters::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.YY_MOVE_OR_COPY< ast::expr_paren::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.YY_MOVE_OR_COPY< ast::expr_path::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.YY_MOVE_OR_COPY< ast::expr_reference::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.YY_MOVE_OR_COPY< ast::expr_self::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.YY_MOVE_OR_COPY< ast::expr_size::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.YY_MOVE_OR_COPY< ast::expr_string::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.YY_MOVE_OR_COPY< ast::expr_true::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.YY_MOVE_OR_COPY< ast::expr_undefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.YY_MOVE_OR_COPY< ast::expr_vector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        value.YY_MOVE_OR_COPY< ast::expr_vectorscale::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        value.YY_MOVE_OR_COPY< ast::expr_vectortoangles::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.YY_MOVE_OR_COPY< ast::include::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< ast::program::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.YY_MOVE_OR_COPY< ast::stmt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.YY_MOVE_OR_COPY< ast::stmt_assign::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.YY_MOVE_OR_COPY< ast::stmt_break::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.YY_MOVE_OR_COPY< ast::stmt_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.YY_MOVE_OR_COPY< ast::stmt_case::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_const: // stmt_const
        value.YY_MOVE_OR_COPY< ast::stmt_const::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.YY_MOVE_OR_COPY< ast::stmt_continue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.YY_MOVE_OR_COPY< ast::stmt_default::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.YY_MOVE_OR_COPY< ast::stmt_dev::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.YY_MOVE_OR_COPY< ast::stmt_dowhile::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.YY_MOVE_OR_COPY< ast::stmt_endon::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
        value.YY_MOVE_OR_COPY< ast::stmt_expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.YY_MOVE_OR_COPY< ast::stmt_for::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.YY_MOVE_OR_COPY< ast::stmt_foreach::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.YY_MOVE_OR_COPY< ast::stmt_if::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.YY_MOVE_OR_COPY< ast::stmt_ifelse::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
      case symbol_kind::S_stmt_block: // stmt_block
        value.YY_MOVE_OR_COPY< ast::stmt_list::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.YY_MOVE_OR_COPY< ast::stmt_notify::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.YY_MOVE_OR_COPY< ast::stmt_prof_begin::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.YY_MOVE_OR_COPY< ast::stmt_prof_end::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.YY_MOVE_OR_COPY< ast::stmt_return::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.YY_MOVE_OR_COPY< ast::stmt_switch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.YY_MOVE_OR_COPY< ast::stmt_wait::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.YY_MOVE_OR_COPY< ast::stmt_waittill::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.YY_MOVE_OR_COPY< ast::stmt_waittillframeend::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.YY_MOVE_OR_COPY< ast::stmt_waittillmatch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.YY_MOVE_OR_COPY< ast::stmt_while::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASH: // "hash"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
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
        value.move< ast::call > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< ast::decl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_thread: // decl_thread
        value.move< ast::decl_thread::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.move< ast::decl_usingtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_literal: // expr_literal
      case symbol_kind::S_expr_object: // expr_object
        value.move< ast::expr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        value.move< ast::expr_abs::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        value.move< ast::expr_angleclamp180::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        value.move< ast::expr_anglestoforward::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        value.move< ast::expr_anglestoright::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        value.move< ast::expr_anglestoup::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.move< ast::expr_anim::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.move< ast::expr_animation::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.move< ast::expr_animtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.move< ast::expr_arguments::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.move< ast::expr_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.move< ast::expr_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.move< ast::expr_complement::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.move< ast::expr_empty_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.move< ast::expr_false::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.move< ast::expr_field::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.move< ast::expr_float::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.move< ast::expr_game::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        value.move< ast::expr_getdvar::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        value.move< ast::expr_getdvarcoloralpha::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        value.move< ast::expr_getdvarcolorblue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        value.move< ast::expr_getdvarcolorgreen::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        value.move< ast::expr_getdvarcolorred::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        value.move< ast::expr_getdvarfloat::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        value.move< ast::expr_getdvarint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        value.move< ast::expr_getdvarvector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        value.move< ast::expr_getfirstarraykey::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        value.move< ast::expr_getnextarraykey::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        value.move< ast::expr_gettime::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        value.move< ast::expr_hash::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.move< ast::expr_identifier::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.move< ast::expr_integer::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.move< ast::expr_isdefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.move< ast::expr_istring::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.move< ast::expr_level::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.move< ast::expr_method::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.move< ast::expr_negate::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.move< ast::expr_not::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.move< ast::expr_parameters::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.move< ast::expr_paren::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.move< ast::expr_path::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.move< ast::expr_reference::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.move< ast::expr_self::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.move< ast::expr_size::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.move< ast::expr_string::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.move< ast::expr_true::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.move< ast::expr_undefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.move< ast::expr_vector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        value.move< ast::expr_vectorscale::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        value.move< ast::expr_vectortoangles::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.move< ast::include::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< ast::program::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.move< ast::stmt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< ast::stmt_assign::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< ast::stmt_break::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< ast::stmt_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< ast::stmt_case::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_const: // stmt_const
        value.move< ast::stmt_const::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< ast::stmt_continue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< ast::stmt_default::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.move< ast::stmt_dev::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.move< ast::stmt_dowhile::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< ast::stmt_endon::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
        value.move< ast::stmt_expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< ast::stmt_for::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< ast::stmt_foreach::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< ast::stmt_if::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< ast::stmt_ifelse::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
      case symbol_kind::S_stmt_block: // stmt_block
        value.move< ast::stmt_list::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< ast::stmt_notify::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.move< ast::stmt_prof_begin::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.move< ast::stmt_prof_end::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< ast::stmt_return::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< ast::stmt_switch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< ast::stmt_wait::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< ast::stmt_waittill::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< ast::stmt_waittillframeend::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< ast::stmt_waittillmatch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< ast::stmt_while::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASH: // "hash"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.move< std::string > (YY_MOVE (that.value));
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
        value.copy< ast::call > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< ast::decl > (that.value);
        break;

      case symbol_kind::S_decl_thread: // decl_thread
        value.copy< ast::decl_thread::ptr > (that.value);
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.copy< ast::decl_usingtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_literal: // expr_literal
      case symbol_kind::S_expr_object: // expr_object
        value.copy< ast::expr > (that.value);
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        value.copy< ast::expr_abs::ptr > (that.value);
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        value.copy< ast::expr_angleclamp180::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        value.copy< ast::expr_anglestoforward::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        value.copy< ast::expr_anglestoright::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        value.copy< ast::expr_anglestoup::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.copy< ast::expr_anim::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.copy< ast::expr_animation::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.copy< ast::expr_animtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.copy< ast::expr_arguments::ptr > (that.value);
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.copy< ast::expr_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.copy< ast::expr_call::ptr > (that.value);
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.copy< ast::expr_complement::ptr > (that.value);
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.copy< ast::expr_empty_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.copy< ast::expr_false::ptr > (that.value);
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.copy< ast::expr_field::ptr > (that.value);
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.copy< ast::expr_float::ptr > (that.value);
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.copy< ast::expr_game::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        value.copy< ast::expr_getdvar::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        value.copy< ast::expr_getdvarcoloralpha::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        value.copy< ast::expr_getdvarcolorblue::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        value.copy< ast::expr_getdvarcolorgreen::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        value.copy< ast::expr_getdvarcolorred::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        value.copy< ast::expr_getdvarfloat::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        value.copy< ast::expr_getdvarint::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        value.copy< ast::expr_getdvarvector::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        value.copy< ast::expr_getfirstarraykey::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        value.copy< ast::expr_getnextarraykey::ptr > (that.value);
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        value.copy< ast::expr_gettime::ptr > (that.value);
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        value.copy< ast::expr_hash::ptr > (that.value);
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.copy< ast::expr_identifier::ptr > (that.value);
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.copy< ast::expr_integer::ptr > (that.value);
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.copy< ast::expr_isdefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.copy< ast::expr_istring::ptr > (that.value);
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.copy< ast::expr_level::ptr > (that.value);
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.copy< ast::expr_method::ptr > (that.value);
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.copy< ast::expr_negate::ptr > (that.value);
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.copy< ast::expr_not::ptr > (that.value);
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.copy< ast::expr_parameters::ptr > (that.value);
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.copy< ast::expr_paren::ptr > (that.value);
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.copy< ast::expr_path::ptr > (that.value);
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.copy< ast::expr_reference::ptr > (that.value);
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.copy< ast::expr_self::ptr > (that.value);
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.copy< ast::expr_size::ptr > (that.value);
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.copy< ast::expr_string::ptr > (that.value);
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.copy< ast::expr_true::ptr > (that.value);
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.copy< ast::expr_undefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.copy< ast::expr_vector::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        value.copy< ast::expr_vectorscale::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        value.copy< ast::expr_vectortoangles::ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.copy< ast::include::ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< ast::program::ptr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.copy< ast::stmt > (that.value);
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.copy< ast::stmt_assign::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.copy< ast::stmt_break::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.copy< ast::stmt_call::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.copy< ast::stmt_case::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_const: // stmt_const
        value.copy< ast::stmt_const::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.copy< ast::stmt_continue::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.copy< ast::stmt_default::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.copy< ast::stmt_dev::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.copy< ast::stmt_dowhile::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.copy< ast::stmt_endon::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
        value.copy< ast::stmt_expr::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.copy< ast::stmt_for::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.copy< ast::stmt_foreach::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.copy< ast::stmt_if::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.copy< ast::stmt_ifelse::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
      case symbol_kind::S_stmt_block: // stmt_block
        value.copy< ast::stmt_list::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.copy< ast::stmt_notify::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.copy< ast::stmt_prof_begin::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.copy< ast::stmt_prof_end::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.copy< ast::stmt_return::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.copy< ast::stmt_switch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.copy< ast::stmt_wait::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.copy< ast::stmt_waittill::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.copy< ast::stmt_waittillframeend::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.copy< ast::stmt_waittillmatch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.copy< ast::stmt_while::ptr > (that.value);
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASH: // "hash"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.copy< std::string > (that.value);
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
        value.move< ast::call > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< ast::decl > (that.value);
        break;

      case symbol_kind::S_decl_thread: // decl_thread
        value.move< ast::decl_thread::ptr > (that.value);
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.move< ast::decl_usingtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_literal: // expr_literal
      case symbol_kind::S_expr_object: // expr_object
        value.move< ast::expr > (that.value);
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        value.move< ast::expr_abs::ptr > (that.value);
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        value.move< ast::expr_angleclamp180::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        value.move< ast::expr_anglestoforward::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        value.move< ast::expr_anglestoright::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        value.move< ast::expr_anglestoup::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.move< ast::expr_anim::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.move< ast::expr_animation::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.move< ast::expr_animtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.move< ast::expr_arguments::ptr > (that.value);
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.move< ast::expr_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.move< ast::expr_call::ptr > (that.value);
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.move< ast::expr_complement::ptr > (that.value);
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.move< ast::expr_empty_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.move< ast::expr_false::ptr > (that.value);
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.move< ast::expr_field::ptr > (that.value);
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.move< ast::expr_float::ptr > (that.value);
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.move< ast::expr_game::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        value.move< ast::expr_getdvar::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        value.move< ast::expr_getdvarcoloralpha::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        value.move< ast::expr_getdvarcolorblue::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        value.move< ast::expr_getdvarcolorgreen::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        value.move< ast::expr_getdvarcolorred::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        value.move< ast::expr_getdvarfloat::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        value.move< ast::expr_getdvarint::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        value.move< ast::expr_getdvarvector::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        value.move< ast::expr_getfirstarraykey::ptr > (that.value);
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        value.move< ast::expr_getnextarraykey::ptr > (that.value);
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        value.move< ast::expr_gettime::ptr > (that.value);
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        value.move< ast::expr_hash::ptr > (that.value);
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.move< ast::expr_identifier::ptr > (that.value);
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.move< ast::expr_integer::ptr > (that.value);
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.move< ast::expr_isdefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.move< ast::expr_istring::ptr > (that.value);
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.move< ast::expr_level::ptr > (that.value);
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.move< ast::expr_method::ptr > (that.value);
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.move< ast::expr_negate::ptr > (that.value);
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.move< ast::expr_not::ptr > (that.value);
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.move< ast::expr_parameters::ptr > (that.value);
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.move< ast::expr_paren::ptr > (that.value);
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.move< ast::expr_path::ptr > (that.value);
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.move< ast::expr_reference::ptr > (that.value);
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.move< ast::expr_self::ptr > (that.value);
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.move< ast::expr_size::ptr > (that.value);
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.move< ast::expr_string::ptr > (that.value);
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.move< ast::expr_true::ptr > (that.value);
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.move< ast::expr_undefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.move< ast::expr_vector::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        value.move< ast::expr_vectorscale::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        value.move< ast::expr_vectortoangles::ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.move< ast::include::ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< ast::program::ptr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.move< ast::stmt > (that.value);
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< ast::stmt_assign::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< ast::stmt_break::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< ast::stmt_call::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< ast::stmt_case::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_const: // stmt_const
        value.move< ast::stmt_const::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< ast::stmt_continue::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< ast::stmt_default::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.move< ast::stmt_dev::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.move< ast::stmt_dowhile::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< ast::stmt_endon::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
        value.move< ast::stmt_expr::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< ast::stmt_for::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< ast::stmt_foreach::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< ast::stmt_if::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< ast::stmt_ifelse::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
      case symbol_kind::S_stmt_block: // stmt_block
        value.move< ast::stmt_list::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< ast::stmt_notify::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.move< ast::stmt_prof_begin::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.move< ast::stmt_prof_end::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< ast::stmt_return::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< ast::stmt_switch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< ast::stmt_wait::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< ast::stmt_waittill::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< ast::stmt_waittillframeend::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< ast::stmt_waittillmatch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< ast::stmt_while::ptr > (that.value);
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASH: // "hash"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.move< std::string > (that.value);
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

#if T6DEBUG
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

#if T6DEBUG
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
#endif // T6DEBUG

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
            symbol_type yylookahead (yylex (lexer));
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
        yylhs.value.emplace< ast::call > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< ast::decl > ();
        break;

      case symbol_kind::S_decl_thread: // decl_thread
        yylhs.value.emplace< ast::decl_thread::ptr > ();
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        yylhs.value.emplace< ast::decl_usingtree::ptr > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_parameters_default: // expr_parameters_default
      case symbol_kind::S_expr_literal: // expr_literal
      case symbol_kind::S_expr_object: // expr_object
        yylhs.value.emplace< ast::expr > ();
        break;

      case symbol_kind::S_expr_abs: // expr_abs
        yylhs.value.emplace< ast::expr_abs::ptr > ();
        break;

      case symbol_kind::S_expr_angleclamp180: // expr_angleclamp180
        yylhs.value.emplace< ast::expr_angleclamp180::ptr > ();
        break;

      case symbol_kind::S_expr_anglestoforward: // expr_anglestoforward
        yylhs.value.emplace< ast::expr_anglestoforward::ptr > ();
        break;

      case symbol_kind::S_expr_anglestoright: // expr_anglestoright
        yylhs.value.emplace< ast::expr_anglestoright::ptr > ();
        break;

      case symbol_kind::S_expr_anglestoup: // expr_anglestoup
        yylhs.value.emplace< ast::expr_anglestoup::ptr > ();
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        yylhs.value.emplace< ast::expr_anim::ptr > ();
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        yylhs.value.emplace< ast::expr_animation::ptr > ();
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        yylhs.value.emplace< ast::expr_animtree::ptr > ();
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        yylhs.value.emplace< ast::expr_arguments::ptr > ();
        break;

      case symbol_kind::S_expr_array: // expr_array
        yylhs.value.emplace< ast::expr_array::ptr > ();
        break;

      case symbol_kind::S_expr_call: // expr_call
        yylhs.value.emplace< ast::expr_call::ptr > ();
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        yylhs.value.emplace< ast::expr_complement::ptr > ();
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        yylhs.value.emplace< ast::expr_empty_array::ptr > ();
        break;

      case symbol_kind::S_expr_false: // expr_false
        yylhs.value.emplace< ast::expr_false::ptr > ();
        break;

      case symbol_kind::S_expr_field: // expr_field
        yylhs.value.emplace< ast::expr_field::ptr > ();
        break;

      case symbol_kind::S_expr_float: // expr_float
        yylhs.value.emplace< ast::expr_float::ptr > ();
        break;

      case symbol_kind::S_expr_game: // expr_game
        yylhs.value.emplace< ast::expr_game::ptr > ();
        break;

      case symbol_kind::S_expr_getdvar: // expr_getdvar
        yylhs.value.emplace< ast::expr_getdvar::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarcoloralpha: // expr_getdvarcoloralpha
        yylhs.value.emplace< ast::expr_getdvarcoloralpha::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarcolorblue: // expr_getdvarcolorblue
        yylhs.value.emplace< ast::expr_getdvarcolorblue::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarcolorgreen: // expr_getdvarcolorgreen
        yylhs.value.emplace< ast::expr_getdvarcolorgreen::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarcolorred: // expr_getdvarcolorred
        yylhs.value.emplace< ast::expr_getdvarcolorred::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarfloat: // expr_getdvarfloat
        yylhs.value.emplace< ast::expr_getdvarfloat::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarint: // expr_getdvarint
        yylhs.value.emplace< ast::expr_getdvarint::ptr > ();
        break;

      case symbol_kind::S_expr_getdvarvector: // expr_getdvarvector
        yylhs.value.emplace< ast::expr_getdvarvector::ptr > ();
        break;

      case symbol_kind::S_expr_getfirstarraykey: // expr_getfirstarraykey
        yylhs.value.emplace< ast::expr_getfirstarraykey::ptr > ();
        break;

      case symbol_kind::S_expr_getnextarraykey: // expr_getnextarraykey
        yylhs.value.emplace< ast::expr_getnextarraykey::ptr > ();
        break;

      case symbol_kind::S_expr_gettime: // expr_gettime
        yylhs.value.emplace< ast::expr_gettime::ptr > ();
        break;

      case symbol_kind::S_expr_hash: // expr_hash
        yylhs.value.emplace< ast::expr_hash::ptr > ();
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        yylhs.value.emplace< ast::expr_identifier::ptr > ();
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        yylhs.value.emplace< ast::expr_integer::ptr > ();
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        yylhs.value.emplace< ast::expr_isdefined::ptr > ();
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        yylhs.value.emplace< ast::expr_istring::ptr > ();
        break;

      case symbol_kind::S_expr_level: // expr_level
        yylhs.value.emplace< ast::expr_level::ptr > ();
        break;

      case symbol_kind::S_expr_method: // expr_method
        yylhs.value.emplace< ast::expr_method::ptr > ();
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        yylhs.value.emplace< ast::expr_negate::ptr > ();
        break;

      case symbol_kind::S_expr_not: // expr_not
        yylhs.value.emplace< ast::expr_not::ptr > ();
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        yylhs.value.emplace< ast::expr_parameters::ptr > ();
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        yylhs.value.emplace< ast::expr_paren::ptr > ();
        break;

      case symbol_kind::S_expr_path: // expr_path
        yylhs.value.emplace< ast::expr_path::ptr > ();
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        yylhs.value.emplace< ast::expr_reference::ptr > ();
        break;

      case symbol_kind::S_expr_self: // expr_self
        yylhs.value.emplace< ast::expr_self::ptr > ();
        break;

      case symbol_kind::S_expr_size: // expr_size
        yylhs.value.emplace< ast::expr_size::ptr > ();
        break;

      case symbol_kind::S_expr_string: // expr_string
        yylhs.value.emplace< ast::expr_string::ptr > ();
        break;

      case symbol_kind::S_expr_true: // expr_true
        yylhs.value.emplace< ast::expr_true::ptr > ();
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        yylhs.value.emplace< ast::expr_undefined::ptr > ();
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        yylhs.value.emplace< ast::expr_vector::ptr > ();
        break;

      case symbol_kind::S_expr_vectorscale: // expr_vectorscale
        yylhs.value.emplace< ast::expr_vectorscale::ptr > ();
        break;

      case symbol_kind::S_expr_vectortoangles: // expr_vectortoangles
        yylhs.value.emplace< ast::expr_vectortoangles::ptr > ();
        break;

      case symbol_kind::S_include: // include
        yylhs.value.emplace< ast::include::ptr > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< ast::program::ptr > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        yylhs.value.emplace< ast::stmt > ();
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        yylhs.value.emplace< ast::stmt_assign::ptr > ();
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        yylhs.value.emplace< ast::stmt_break::ptr > ();
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        yylhs.value.emplace< ast::stmt_call::ptr > ();
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        yylhs.value.emplace< ast::stmt_case::ptr > ();
        break;

      case symbol_kind::S_stmt_const: // stmt_const
        yylhs.value.emplace< ast::stmt_const::ptr > ();
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        yylhs.value.emplace< ast::stmt_continue::ptr > ();
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        yylhs.value.emplace< ast::stmt_default::ptr > ();
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        yylhs.value.emplace< ast::stmt_dev::ptr > ();
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        yylhs.value.emplace< ast::stmt_dowhile::ptr > ();
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        yylhs.value.emplace< ast::stmt_endon::ptr > ();
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
        yylhs.value.emplace< ast::stmt_expr::ptr > ();
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        yylhs.value.emplace< ast::stmt_for::ptr > ();
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        yylhs.value.emplace< ast::stmt_foreach::ptr > ();
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        yylhs.value.emplace< ast::stmt_if::ptr > ();
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        yylhs.value.emplace< ast::stmt_ifelse::ptr > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
      case symbol_kind::S_stmt_block: // stmt_block
        yylhs.value.emplace< ast::stmt_list::ptr > ();
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        yylhs.value.emplace< ast::stmt_notify::ptr > ();
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        yylhs.value.emplace< ast::stmt_prof_begin::ptr > ();
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        yylhs.value.emplace< ast::stmt_prof_end::ptr > ();
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        yylhs.value.emplace< ast::stmt_return::ptr > ();
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        yylhs.value.emplace< ast::stmt_switch::ptr > ();
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        yylhs.value.emplace< ast::stmt_wait::ptr > ();
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        yylhs.value.emplace< ast::stmt_waittill::ptr > ();
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        yylhs.value.emplace< ast::stmt_waittillframeend::ptr > ();
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        yylhs.value.emplace< ast::stmt_waittillmatch::ptr > ();
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        yylhs.value.emplace< ast::stmt_while::ptr > ();
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_HASH: // "hash"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        yylhs.value.emplace< std::string > ();
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
#line 295 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < ast::program::ptr > ()); }
#line 2345 "parser.cpp"
    break;

  case 3: // root: %empty
#line 296 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 2351 "parser.cpp"
    break;

  case 4: // program: program inline
#line 301 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 2357 "parser.cpp"
    break;

  case 5: // program: program include
#line 303 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2363 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 305 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2369 "parser.cpp"
    break;

  case 7: // program: inline
#line 307 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 2375 "parser.cpp"
    break;

  case 8: // program: include
#line 309 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2381 "parser.cpp"
    break;

  case 9: // program: declaration
#line 311 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2387 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 315 "parser.ypp"
                                 { lexer.push_header(yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2393 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 320 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2399 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 324 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2405 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 325 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2411 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 326 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2417 "parser.cpp"
    break;

  case 15: // declaration: decl_thread
#line 327 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2423 "parser.cpp"
    break;

  case 16: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 332 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2429 "parser.cpp"
    break;

  case 17: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 337 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()), export_flags::none); }
#line 2435 "parser.cpp"
    break;

  case 18: // decl_thread: "autoexec" expr_identifier "(" expr_parameters ")" stmt_block
#line 339 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()), export_flags::vis_autoexec); }
#line 2441 "parser.cpp"
    break;

  case 19: // decl_thread: "private" expr_identifier "(" expr_parameters ")" stmt_block
#line 341 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()), export_flags::vis_private); }
#line 2447 "parser.cpp"
    break;

  case 20: // stmt: stmt_block
#line 345 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2453 "parser.cpp"
    break;

  case 21: // stmt: stmt_call
#line 346 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2459 "parser.cpp"
    break;

  case 22: // stmt: stmt_const
#line 347 "parser.ypp"
                            { yylhs.value.as < ast::stmt > ().as_const = std::move(yystack_[0].value.as < ast::stmt_const::ptr > ()); }
#line 2465 "parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 348 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2471 "parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 349 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2477 "parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 350 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2483 "parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 351 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2489 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 352 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2495 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 353 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2501 "parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 354 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2507 "parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 355 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2513 "parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 356 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2519 "parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 357 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2525 "parser.cpp"
    break;

  case 33: // stmt: stmt_dowhile
#line 358 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2531 "parser.cpp"
    break;

  case 34: // stmt: stmt_for
#line 359 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2537 "parser.cpp"
    break;

  case 35: // stmt: stmt_foreach
#line 360 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2543 "parser.cpp"
    break;

  case 36: // stmt: stmt_switch
#line 361 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2549 "parser.cpp"
    break;

  case 37: // stmt: stmt_case
#line 362 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2555 "parser.cpp"
    break;

  case 38: // stmt: stmt_default
#line 363 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2561 "parser.cpp"
    break;

  case 39: // stmt: stmt_break
#line 364 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2567 "parser.cpp"
    break;

  case 40: // stmt: stmt_continue
#line 365 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2573 "parser.cpp"
    break;

  case 41: // stmt: stmt_return
#line 366 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2579 "parser.cpp"
    break;

  case 42: // stmt: stmt_prof_begin
#line 367 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2585 "parser.cpp"
    break;

  case 43: // stmt: stmt_prof_end
#line 368 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2591 "parser.cpp"
    break;

  case 44: // stmt_or_dev: stmt
#line 372 "parser.ypp"
               { yylhs.value.as < ast::stmt > () = std::move(yystack_[0].value.as < ast::stmt > ()); }
#line 2597 "parser.cpp"
    break;

  case 45: // stmt_or_dev: stmt_dev
#line 373 "parser.ypp"
               { yylhs.value.as < ast::stmt > ().as_dev = std::move(yystack_[0].value.as < ast::stmt_dev::ptr > ()); }
#line 2603 "parser.cpp"
    break;

  case 46: // stmt_list: stmt_list stmt
#line 378 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2609 "parser.cpp"
    break;

  case 47: // stmt_list: stmt
#line 380 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2615 "parser.cpp"
    break;

  case 48: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 385 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2621 "parser.cpp"
    break;

  case 49: // stmt_or_dev_list: stmt_or_dev
#line 387 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2627 "parser.cpp"
    break;

  case 50: // stmt_dev: "/#" stmt_list "#/"
#line 391 "parser.ypp"
                                { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::move(yystack_[1].value.as < ast::stmt_list::ptr > ())); }
#line 2633 "parser.cpp"
    break;

  case 51: // stmt_dev: "/#" "#/"
#line 392 "parser.ypp"
                      { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2639 "parser.cpp"
    break;

  case 52: // stmt_block: "{" stmt_or_dev_list "}"
#line 396 "parser.ypp"
                                     { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2645 "parser.cpp"
    break;

  case 53: // stmt_block: "{" "}"
#line 397 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2651 "parser.cpp"
    break;

  case 54: // stmt_expr: expr_assign
#line 402 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2657 "parser.cpp"
    break;

  case 55: // stmt_expr: expr_increment
#line 404 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2663 "parser.cpp"
    break;

  case 56: // stmt_expr: expr_decrement
#line 406 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2669 "parser.cpp"
    break;

  case 57: // stmt_expr: %empty
#line 408 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2675 "parser.cpp"
    break;

  case 58: // stmt_call: expr_call ";"
#line 413 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2681 "parser.cpp"
    break;

  case 59: // stmt_call: expr_method ";"
#line 415 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2687 "parser.cpp"
    break;

  case 60: // stmt_const: "const" expr_identifier "=" expr ";"
#line 420 "parser.ypp"
        { yylhs.value.as < ast::stmt_const::ptr > () = std::make_unique<ast::stmt_const>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2693 "parser.cpp"
    break;

  case 61: // stmt_assign: expr_assign ";"
#line 425 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2699 "parser.cpp"
    break;

  case 62: // stmt_assign: expr_increment ";"
#line 427 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2705 "parser.cpp"
    break;

  case 63: // stmt_assign: expr_decrement ";"
#line 429 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2711 "parser.cpp"
    break;

  case 64: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 434 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2717 "parser.cpp"
    break;

  case 65: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 439 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2723 "parser.cpp"
    break;

  case 66: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 441 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2729 "parser.cpp"
    break;

  case 67: // stmt_wait: "wait" expr ";"
#line 446 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2735 "parser.cpp"
    break;

  case 68: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 451 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2741 "parser.cpp"
    break;

  case 69: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 453 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2747 "parser.cpp"
    break;

  case 70: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 458 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2753 "parser.cpp"
    break;

  case 71: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 460 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2759 "parser.cpp"
    break;

  case 72: // stmt_waittillframeend: "waittillframeend" ";"
#line 465 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2765 "parser.cpp"
    break;

  case 73: // stmt_if: "if" "(" expr ")" stmt
#line 470 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2771 "parser.cpp"
    break;

  case 74: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 475 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2777 "parser.cpp"
    break;

  case 75: // stmt_while: "while" "(" expr ")" stmt
#line 480 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2783 "parser.cpp"
    break;

  case 76: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 485 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2789 "parser.cpp"
    break;

  case 77: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 490 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2795 "parser.cpp"
    break;

  case 78: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 495 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2801 "parser.cpp"
    break;

  case 79: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 497 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2807 "parser.cpp"
    break;

  case 80: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 502 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2813 "parser.cpp"
    break;

  case 81: // stmt_case: "case" expr_integer ":"
#line 507 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2819 "parser.cpp"
    break;

  case 82: // stmt_case: "case" expr_string ":"
#line 509 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2825 "parser.cpp"
    break;

  case 83: // stmt_default: "default" ":"
#line 514 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2831 "parser.cpp"
    break;

  case 84: // stmt_break: "break" ";"
#line 519 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2837 "parser.cpp"
    break;

  case 85: // stmt_continue: "continue" ";"
#line 524 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2843 "parser.cpp"
    break;

  case 86: // stmt_return: "return" expr ";"
#line 529 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2849 "parser.cpp"
    break;

  case 87: // stmt_return: "return" ";"
#line 531 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2855 "parser.cpp"
    break;

  case 88: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 536 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2861 "parser.cpp"
    break;

  case 89: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 541 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2867 "parser.cpp"
    break;

  case 90: // expr: expr_ternary
#line 545 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2873 "parser.cpp"
    break;

  case 91: // expr: expr_binary
#line 546 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2879 "parser.cpp"
    break;

  case 92: // expr: expr_primitive
#line 547 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2885 "parser.cpp"
    break;

  case 93: // expr_or_empty: expr
#line 551 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2891 "parser.cpp"
    break;

  case 94: // expr_or_empty: %empty
#line 552 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2897 "parser.cpp"
    break;

  case 95: // expr_assign: expr_object "=" expr
#line 557 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2903 "parser.cpp"
    break;

  case 96: // expr_assign: expr_object "|=" expr
#line 559 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2909 "parser.cpp"
    break;

  case 97: // expr_assign: expr_object "&=" expr
#line 561 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2915 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object "^=" expr
#line 563 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2921 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "<<=" expr
#line 565 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2927 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object ">>=" expr
#line 567 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2933 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "+=" expr
#line 569 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2939 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "-=" expr
#line 571 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2945 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object "*=" expr
#line 573 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2951 "parser.cpp"
    break;

  case 104: // expr_assign: expr_object "/=" expr
#line 575 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2957 "parser.cpp"
    break;

  case 105: // expr_assign: expr_object "%=" expr
#line 577 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2963 "parser.cpp"
    break;

  case 106: // expr_increment: "++" expr_object
#line 582 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2969 "parser.cpp"
    break;

  case 107: // expr_increment: expr_object "++"
#line 584 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2975 "parser.cpp"
    break;

  case 108: // expr_decrement: "--" expr_object
#line 589 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2981 "parser.cpp"
    break;

  case 109: // expr_decrement: expr_object "--"
#line 591 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2987 "parser.cpp"
    break;

  case 110: // expr_ternary: expr "?" expr ":" expr
#line 596 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2993 "parser.cpp"
    break;

  case 111: // expr_binary: expr "||" expr
#line 601 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2999 "parser.cpp"
    break;

  case 112: // expr_binary: expr "&&" expr
#line 603 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3005 "parser.cpp"
    break;

  case 113: // expr_binary: expr "==" expr
#line 605 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3011 "parser.cpp"
    break;

  case 114: // expr_binary: expr "!=" expr
#line 607 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3017 "parser.cpp"
    break;

  case 115: // expr_binary: expr "<=" expr
#line 609 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3023 "parser.cpp"
    break;

  case 116: // expr_binary: expr ">=" expr
#line 611 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3029 "parser.cpp"
    break;

  case 117: // expr_binary: expr "<" expr
#line 613 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3035 "parser.cpp"
    break;

  case 118: // expr_binary: expr ">" expr
#line 615 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3041 "parser.cpp"
    break;

  case 119: // expr_binary: expr "|" expr
#line 617 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3047 "parser.cpp"
    break;

  case 120: // expr_binary: expr "&" expr
#line 619 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3053 "parser.cpp"
    break;

  case 121: // expr_binary: expr "^" expr
#line 621 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3059 "parser.cpp"
    break;

  case 122: // expr_binary: expr "<<" expr
#line 623 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3065 "parser.cpp"
    break;

  case 123: // expr_binary: expr ">>" expr
#line 625 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3071 "parser.cpp"
    break;

  case 124: // expr_binary: expr "+" expr
#line 627 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3077 "parser.cpp"
    break;

  case 125: // expr_binary: expr "-" expr
#line 629 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3083 "parser.cpp"
    break;

  case 126: // expr_binary: expr "*" expr
#line 631 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3089 "parser.cpp"
    break;

  case 127: // expr_binary: expr "/" expr
#line 633 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3095 "parser.cpp"
    break;

  case 128: // expr_binary: expr "%" expr
#line 635 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3101 "parser.cpp"
    break;

  case 129: // expr_primitive: expr_complement
#line 639 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 3107 "parser.cpp"
    break;

  case 130: // expr_primitive: expr_negate
#line 640 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_negate::ptr > ()); }
#line 3113 "parser.cpp"
    break;

  case 131: // expr_primitive: expr_not
#line 641 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 3119 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_call
#line 642 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3125 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_method
#line 643 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3131 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_getnextarraykey
#line 644 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getnextarraykey::ptr > ()); }
#line 3137 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_getfirstarraykey
#line 645 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getfirstarraykey::ptr > ()); }
#line 3143 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_getdvarcoloralpha
#line 646 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcoloralpha::ptr > ()); }
#line 3149 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_getdvarcolorblue
#line 647 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorblue::ptr > ()); }
#line 3155 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_getdvarcolorgreen
#line 648 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorgreen::ptr > ()); }
#line 3161 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_getdvarcolorred
#line 649 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorred::ptr > ()); }
#line 3167 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_getdvarvector
#line 650 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarvector::ptr > ()); }
#line 3173 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_getdvarfloat
#line 651 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarfloat::ptr > ()); }
#line 3179 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_getdvarint
#line 652 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarint::ptr > ()); }
#line 3185 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_getdvar
#line 653 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvar::ptr > ()); }
#line 3191 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_gettime
#line 654 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_gettime::ptr > ()); }
#line 3197 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_abs
#line 655 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_abs::ptr > ()); }
#line 3203 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_vectortoangles
#line 656 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vectortoangles::ptr > ()); }
#line 3209 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_angleclamp180
#line 657 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_angleclamp180::ptr > ()); }
#line 3215 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_anglestoforward
#line 658 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoforward::ptr > ()); }
#line 3221 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_anglestoright
#line 659 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoright::ptr > ()); }
#line 3227 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_anglestoup
#line 660 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoup::ptr > ()); }
#line 3233 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_vectorscale
#line 661 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vectorscale::ptr > ()); }
#line 3239 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_isdefined
#line 662 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_isdefined::ptr > ()); }
#line 3245 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_reference
#line 663 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 3251 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_array
#line 664 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3257 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_field
#line 665 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3263 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_size
#line 666 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 3269 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_paren
#line 667 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 3275 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_empty_array
#line 668 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 3281 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_undefined
#line 669 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 3287 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_game
#line 670 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3293 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_self
#line 671 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3299 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_anim
#line 672 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3305 "parser.cpp"
    break;

  case 163: // expr_primitive: expr_level
#line 673 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3311 "parser.cpp"
    break;

  case 164: // expr_primitive: expr_animation
#line 674 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 3317 "parser.cpp"
    break;

  case 165: // expr_primitive: expr_animtree
#line 675 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animtree::ptr > ()); }
#line 3323 "parser.cpp"
    break;

  case 166: // expr_primitive: expr_identifier
#line 676 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3329 "parser.cpp"
    break;

  case 167: // expr_primitive: expr_istring
#line 677 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 3335 "parser.cpp"
    break;

  case 168: // expr_primitive: expr_string
#line 678 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 3341 "parser.cpp"
    break;

  case 169: // expr_primitive: expr_vector
#line 679 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 3347 "parser.cpp"
    break;

  case 170: // expr_primitive: expr_hash
#line 680 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_hash::ptr > ()); }
#line 3353 "parser.cpp"
    break;

  case 171: // expr_primitive: expr_float
#line 681 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 3359 "parser.cpp"
    break;

  case 172: // expr_primitive: expr_integer
#line 682 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 3365 "parser.cpp"
    break;

  case 173: // expr_primitive: expr_false
#line 683 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 3371 "parser.cpp"
    break;

  case 174: // expr_primitive: expr_true
#line 684 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 3377 "parser.cpp"
    break;

  case 175: // expr_complement: "~" expr
#line 689 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3383 "parser.cpp"
    break;

  case 176: // expr_negate: "-" expr_identifier
#line 694 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()))); }
#line 3389 "parser.cpp"
    break;

  case 177: // expr_negate: "-" expr_paren
#line 696 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()))); }
#line 3395 "parser.cpp"
    break;

  case 178: // expr_negate: "-" expr_array
#line 698 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_array::ptr > ()))); }
#line 3401 "parser.cpp"
    break;

  case 179: // expr_negate: "-" expr_field
#line 700 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_field::ptr > ()))); }
#line 3407 "parser.cpp"
    break;

  case 180: // expr_not: "!" expr
#line 705 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3413 "parser.cpp"
    break;

  case 181: // expr_call: expr_function
#line 709 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3419 "parser.cpp"
    break;

  case 182: // expr_call: expr_pointer
#line 710 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3425 "parser.cpp"
    break;

  case 183: // expr_method: expr_object expr_function
#line 713 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3431 "parser.cpp"
    break;

  case 184: // expr_method: expr_object expr_pointer
#line 714 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3437 "parser.cpp"
    break;

  case 185: // expr_function: expr_identifier "(" expr_arguments ")"
#line 719 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3443 "parser.cpp"
    break;

  case 186: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 721 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3449 "parser.cpp"
    break;

  case 187: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 723 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3455 "parser.cpp"
    break;

  case 188: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 725 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3461 "parser.cpp"
    break;

  case 189: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 730 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3467 "parser.cpp"
    break;

  case 190: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 732 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3473 "parser.cpp"
    break;

  case 191: // expr_parameters: expr_parameters "," expr_parameters_default
#line 737 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3479 "parser.cpp"
    break;

  case 192: // expr_parameters: expr_parameters "," expr_identifier
#line 739 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(ast::expr(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()))); }
#line 3485 "parser.cpp"
    break;

  case 193: // expr_parameters: expr_parameters_default
#line 741 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3491 "parser.cpp"
    break;

  case 194: // expr_parameters: expr_identifier
#line 743 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(ast::expr(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()))); }
#line 3497 "parser.cpp"
    break;

  case 195: // expr_parameters: %empty
#line 745 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 3503 "parser.cpp"
    break;

  case 196: // expr_parameters_default: expr_identifier "=" expr_literal
#line 750 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, ast::expr(std::move(yystack_[2].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3509 "parser.cpp"
    break;

  case 197: // expr_literal: expr_istring
#line 754 "parser.ypp"
                    { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 3515 "parser.cpp"
    break;

  case 198: // expr_literal: expr_string
#line 755 "parser.ypp"
                    { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 3521 "parser.cpp"
    break;

  case 199: // expr_literal: expr_float
#line 756 "parser.ypp"
                    { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 3527 "parser.cpp"
    break;

  case 200: // expr_literal: expr_integer
#line 757 "parser.ypp"
                    { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 3533 "parser.cpp"
    break;

  case 201: // expr_literal: expr_false
#line 758 "parser.ypp"
                    { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 3539 "parser.cpp"
    break;

  case 202: // expr_literal: expr_true
#line 759 "parser.ypp"
                    { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 3545 "parser.cpp"
    break;

  case 203: // expr_arguments: expr_arguments_no_empty
#line 764 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 3551 "parser.cpp"
    break;

  case 204: // expr_arguments: %empty
#line 766 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3557 "parser.cpp"
    break;

  case 205: // expr_arguments_no_empty: expr_arguments "," expr
#line 771 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3563 "parser.cpp"
    break;

  case 206: // expr_arguments_no_empty: expr
#line 773 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3569 "parser.cpp"
    break;

  case 207: // expr_getnextarraykey: "getnextarraykey" "(" expr "," expr ")"
#line 778 "parser.ypp"
        { yylhs.value.as < ast::expr_getnextarraykey::ptr > () = std::make_unique<ast::expr_getnextarraykey>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3575 "parser.cpp"
    break;

  case 208: // expr_getfirstarraykey: "getfirstarraykey" "(" expr ")"
#line 783 "parser.ypp"
        { yylhs.value.as < ast::expr_getfirstarraykey::ptr > () = std::make_unique<ast::expr_getfirstarraykey>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3581 "parser.cpp"
    break;

  case 209: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr ")"
#line 788 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcoloralpha::ptr > () = std::make_unique<ast::expr_getdvarcoloralpha>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3587 "parser.cpp"
    break;

  case 210: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr ")"
#line 793 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorblue::ptr > () = std::make_unique<ast::expr_getdvarcolorblue>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3593 "parser.cpp"
    break;

  case 211: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr ")"
#line 798 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorgreen::ptr > () = std::make_unique<ast::expr_getdvarcolorgreen>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3599 "parser.cpp"
    break;

  case 212: // expr_getdvarcolorred: "getdvarcolorred" "(" expr ")"
#line 803 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorred::ptr > () = std::make_unique<ast::expr_getdvarcolorred>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3605 "parser.cpp"
    break;

  case 213: // expr_getdvarvector: "getdvarvector" "(" expr ")"
#line 808 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarvector::ptr > () = std::make_unique<ast::expr_getdvarvector>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3611 "parser.cpp"
    break;

  case 214: // expr_getdvarfloat: "getdvarfloat" "(" expr ")"
#line 813 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarfloat::ptr > () = std::make_unique<ast::expr_getdvarfloat>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3617 "parser.cpp"
    break;

  case 215: // expr_getdvarint: "getdvarint" "(" expr ")"
#line 818 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarint::ptr > () = std::make_unique<ast::expr_getdvarint>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3623 "parser.cpp"
    break;

  case 216: // expr_getdvar: "getdvar" "(" expr ")"
#line 823 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvar::ptr > () = std::make_unique<ast::expr_getdvar>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3629 "parser.cpp"
    break;

  case 217: // expr_gettime: "gettime" "(" ")"
#line 828 "parser.ypp"
        { yylhs.value.as < ast::expr_gettime::ptr > () = std::make_unique<ast::expr_gettime>(yylhs.location); }
#line 3635 "parser.cpp"
    break;

  case 218: // expr_abs: "abs" "(" expr ")"
#line 833 "parser.ypp"
        { yylhs.value.as < ast::expr_abs::ptr > () = std::make_unique<ast::expr_abs>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3641 "parser.cpp"
    break;

  case 219: // expr_vectortoangles: "vectortoangles" "(" expr ")"
#line 838 "parser.ypp"
        { yylhs.value.as < ast::expr_vectortoangles::ptr > () = std::make_unique<ast::expr_vectortoangles>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3647 "parser.cpp"
    break;

  case 220: // expr_angleclamp180: "angleclamp180" "(" expr ")"
#line 843 "parser.ypp"
        { yylhs.value.as < ast::expr_angleclamp180::ptr > () = std::make_unique<ast::expr_angleclamp180>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3653 "parser.cpp"
    break;

  case 221: // expr_anglestoforward: "anglestoforward" "(" expr ")"
#line 848 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoforward::ptr > () = std::make_unique<ast::expr_anglestoforward>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3659 "parser.cpp"
    break;

  case 222: // expr_anglestoright: "anglestoright" "(" expr ")"
#line 853 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoright::ptr > () = std::make_unique<ast::expr_anglestoright>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3665 "parser.cpp"
    break;

  case 223: // expr_anglestoup: "anglestoup" "(" expr ")"
#line 858 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoup::ptr > () = std::make_unique<ast::expr_anglestoup>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3671 "parser.cpp"
    break;

  case 224: // expr_vectorscale: "vectorscale" "(" expr "," expr ")"
#line 863 "parser.ypp"
        { yylhs.value.as < ast::expr_vectorscale::ptr > () = std::make_unique<ast::expr_vectorscale>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3677 "parser.cpp"
    break;

  case 225: // expr_isdefined: "isdefined" "(" expr ")"
#line 868 "parser.ypp"
        { yylhs.value.as < ast::expr_isdefined::ptr > () = std::make_unique<ast::expr_isdefined>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3683 "parser.cpp"
    break;

  case 226: // expr_reference: "::" expr_identifier
#line 873 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3689 "parser.cpp"
    break;

  case 227: // expr_reference: expr_path "::" expr_identifier
#line 875 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3695 "parser.cpp"
    break;

  case 228: // expr_array: expr_object "[" expr "]"
#line 880 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3701 "parser.cpp"
    break;

  case 229: // expr_array: expr_getdvarvector "[" expr "]"
#line 882 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_getdvarvector::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3707 "parser.cpp"
    break;

  case 230: // expr_array: expr_vectortoangles "[" expr "]"
#line 884 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_vectortoangles::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3713 "parser.cpp"
    break;

  case 231: // expr_array: expr_angleclamp180 "[" expr "]"
#line 886 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_angleclamp180::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3719 "parser.cpp"
    break;

  case 232: // expr_array: expr_anglestoforward "[" expr "]"
#line 888 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_anglestoforward::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3725 "parser.cpp"
    break;

  case 233: // expr_array: expr_anglestoright "[" expr "]"
#line 890 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_anglestoright::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3731 "parser.cpp"
    break;

  case 234: // expr_array: expr_anglestoup "[" expr "]"
#line 892 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_anglestoup::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3737 "parser.cpp"
    break;

  case 235: // expr_array: expr_vectorscale "[" expr "]"
#line 894 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_vectorscale::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3743 "parser.cpp"
    break;

  case 236: // expr_field: expr_object "." expr_identifier_nosize
#line 899 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3749 "parser.cpp"
    break;

  case 237: // expr_size: expr_object "." "size"
#line 904 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ())); }
#line 3755 "parser.cpp"
    break;

  case 238: // expr_paren: "(" expr ")"
#line 909 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3761 "parser.cpp"
    break;

  case 239: // expr_object: expr_call
#line 913 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3767 "parser.cpp"
    break;

  case 240: // expr_object: expr_method
#line 914 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3773 "parser.cpp"
    break;

  case 241: // expr_object: expr_array
#line 915 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3779 "parser.cpp"
    break;

  case 242: // expr_object: expr_field
#line 916 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3785 "parser.cpp"
    break;

  case 243: // expr_object: expr_game
#line 917 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3791 "parser.cpp"
    break;

  case 244: // expr_object: expr_self
#line 918 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3797 "parser.cpp"
    break;

  case 245: // expr_object: expr_anim
#line 919 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3803 "parser.cpp"
    break;

  case 246: // expr_object: expr_level
#line 920 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3809 "parser.cpp"
    break;

  case 247: // expr_object: expr_identifier
#line 921 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3815 "parser.cpp"
    break;

  case 248: // expr_empty_array: "[" "]"
#line 926 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3821 "parser.cpp"
    break;

  case 249: // expr_undefined: "undefined"
#line 931 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3827 "parser.cpp"
    break;

  case 250: // expr_game: "game"
#line 936 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3833 "parser.cpp"
    break;

  case 251: // expr_self: "self"
#line 941 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3839 "parser.cpp"
    break;

  case 252: // expr_anim: "anim"
#line 946 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3845 "parser.cpp"
    break;

  case 253: // expr_level: "level"
#line 951 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3851 "parser.cpp"
    break;

  case 254: // expr_animation: "%" "identifier"
#line 956 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3857 "parser.cpp"
    break;

  case 255: // expr_animtree: "#animtree"
#line 961 "parser.ypp"
        { yylhs.value.as < ast::expr_animtree::ptr > () = std::make_unique<ast::expr_animtree>(yylhs.location); }
#line 3863 "parser.cpp"
    break;

  case 256: // expr_identifier_nosize: "identifier"
#line 966 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3869 "parser.cpp"
    break;

  case 257: // expr_identifier: "identifier"
#line 971 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3875 "parser.cpp"
    break;

  case 258: // expr_identifier: "size"
#line 973 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, "size"); }
#line 3881 "parser.cpp"
    break;

  case 259: // expr_path: "identifier"
#line 978 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3887 "parser.cpp"
    break;

  case 260: // expr_path: "path"
#line 980 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3893 "parser.cpp"
    break;

  case 261: // expr_istring: "localized string"
#line 985 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3899 "parser.cpp"
    break;

  case 262: // expr_string: "string literal"
#line 990 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3905 "parser.cpp"
    break;

  case 263: // expr_vector: "(" expr "," expr "," expr ")"
#line 995 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3911 "parser.cpp"
    break;

  case 264: // expr_hash: "hash"
#line 1000 "parser.ypp"
        { yylhs.value.as < ast::expr_hash::ptr > () = std::make_unique<ast::expr_hash>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3917 "parser.cpp"
    break;

  case 265: // expr_float: "-" "float"
#line 1005 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3923 "parser.cpp"
    break;

  case 266: // expr_float: "float"
#line 1007 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3929 "parser.cpp"
    break;

  case 267: // expr_integer: "-" "integer"
#line 1012 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3935 "parser.cpp"
    break;

  case 268: // expr_integer: "integer"
#line 1014 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3941 "parser.cpp"
    break;

  case 269: // expr_false: "false"
#line 1019 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3947 "parser.cpp"
    break;

  case 270: // expr_true: "true"
#line 1024 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3953 "parser.cpp"
    break;


#line 3957 "parser.cpp"

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
    "end of file", "error", "invalid token", "#define", "#undef", "#ifdef",
  "#ifndef", "#if", "#elif", "#else", "#endif", "/#", "#/", "#inline",
  "#include", "#using_animtree", "#animtree", "autoexec", "private",
  "endon", "notify", "wait", "waittill", "waittillmatch",
  "waittillframeend", "if", "else", "do", "while", "for", "foreach", "in",
  "switch", "case", "default", "break", "continue", "return", "prof_begin",
  "prof_end", "thread", "true", "false", "undefined", "size", "game",
  "self", "anim", "level", "const", "getnextarraykey", "getfirstarraykey",
  "getdvarcoloralpha", "getdvarcolorblue", "getdvarcolorgreen",
  "getdvarcolorred", "getdvarvector", "getdvarfloat", "getdvarint",
  "getdvar", "gettime", "abs", "vectortoangles", "angleclamp180",
  "anglestoforward", "anglestoright", "anglestoup", "vectorscale",
  "isdefined", "(", ")", "{", "}", "[", "]", ",", ".", "::", ":", ";", "?",
  "++", "--", "<<", ">>", "||", "&&", "==", "!=", "<=", ">=", "<", ">",
  "!", "~", "=", "+=", "-=", "*=", "/=", "%=", "|=", "&=", "^=", ">>=",
  "<<=", "|", "&", "^", "+", "-", "*", "/", "%", "path", "identifier",
  "string literal", "localized string", "hash", "float", "integer",
  "SIZEOF", "THEN", "TERN", "NEG", "ANIMREF", "PREINC", "PREDEC",
  "POSTINC", "POSTDEC", "$accept", "root", "program", "inline", "include",
  "declaration", "decl_usingtree", "decl_thread", "stmt", "stmt_or_dev",
  "stmt_list", "stmt_or_dev_list", "stmt_dev", "stmt_block", "stmt_expr",
  "stmt_call", "stmt_const", "stmt_assign", "stmt_endon", "stmt_notify",
  "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_if", "stmt_ifelse", "stmt_while",
  "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case",
  "stmt_default", "stmt_break", "stmt_continue", "stmt_return",
  "stmt_prof_begin", "stmt_prof_end", "expr", "expr_or_empty",
  "expr_assign", "expr_increment", "expr_decrement", "expr_ternary",
  "expr_binary", "expr_primitive", "expr_complement", "expr_negate",
  "expr_not", "expr_call", "expr_method", "expr_function", "expr_pointer",
  "expr_parameters", "expr_parameters_default", "expr_literal",
  "expr_arguments", "expr_arguments_no_empty", "expr_getnextarraykey",
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

#if T6DEBUG
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
#if T6DEBUG
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
#if T6DEBUG
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


  const short parser::yypact_ninf_ = -373;

  const short parser::yytable_ninf_ = -260;

  const short
  parser::yypact_[] =
  {
      79,  -373,  -373,    32,    32,   -65,   -31,   -31,  -373,  -373,
      20,    79,  -373,  -373,  -373,  -373,  -373,   -41,  -373,  -373,
     -49,   -43,   -77,   -25,   -19,  -373,  -373,  -373,  -373,   -31,
    -373,  -373,  -373,   -23,   -31,   -31,   -24,  -373,   -17,    28,
     -15,    -9,    40,   -31,   127,  -373,    40,    40,  1407,  -373,
    -373,   -17,  -373,  -373,     9,  -373,  -373,  -373,  -373,  -373,
    -373,  -373,  -373,  -373,  -373,  -373,  -373,  1532,  1226,    35,
      55,  1656,    64,    69,    71,    91,   -78,    83,    84,    85,
    1064,   103,   106,    93,  -373,  -373,  -373,  -373,   -31,   111,
     116,   118,   122,   123,   136,   140,  -373,    62,  1030,  1030,
     109,  -373,  -373,  1470,  -373,  -373,  -373,  -373,  -373,  -373,
    -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,
    -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,   125,
     132,   138,   143,   147,  -373,  -373,   141,   154,   155,   166,
     167,   169,   172,  -373,  -373,   727,  -373,  -373,  -373,  -373,
     183,   119,  -373,  -373,  -373,  -373,  1594,  -373,  -373,   195,
     197,   201,   203,   205,   206,   208,   209,   210,   211,   214,
     216,  1226,    76,   -31,  1226,  1226,   669,   179,  -373,  3184,
    -373,  -373,  -373,  -373,  -373,  -373,   402,   427,  -373,  -373,
    -373,  -373,  -373,  -373,   141,  -373,  -373,  -373,  -373,  -373,
     154,   155,   166,   167,   169,   172,  -373,  -373,   510,   517,
    -373,  -373,   571,  -373,  -373,   737,   771,   777,   950,  -373,
    -373,   351,   218,  -373,  -373,  -373,  -373,  -373,  -373,  -373,
    -373,  -373,  1226,   259,  1226,   973,   -31,  1226,   176,   219,
     229,  -373,  -373,  -373,  -373,  3219,  1226,  1226,   237,   243,
     236,   222,  1226,  1226,  1226,  1226,  1226,  1226,  1226,  1226,
    -373,  -373,   984,   984,  -373,  -373,  -373,  -373,  -373,  -373,
    -373,  1226,  1226,  1226,  1226,  1226,  1226,  1226,   245,   249,
     253,   257,  1307,   212,  -373,  -373,  1226,  1226,  1226,  1226,
    1226,  1226,  1226,  1226,  1226,  1226,  1226,  -373,  -373,   183,
    1226,   -31,  -373,  -373,  1226,  1226,  1226,  1226,  1226,  1226,
    1226,  1226,  1226,   254,  1226,  1226,  1666,  -373,  -373,  -373,
    -373,  1226,   510,   517,  -373,   984,   351,  -373,  -373,  1226,
    1226,  1226,  1226,  1226,  1226,  1226,  1226,  1226,  1226,  1226,
    1226,  1226,  1226,  1226,  1226,  1226,  1226,  1226,   -29,   -31,
    1832,   260,  1866,   251,  -373,  -373,  -373,   900,    -5,  1900,
    -373,  -373,  -373,  3267,     4,  -373,     5,  1226,  1226,   -31,
    1226,  1934,  1968,  2002,  2036,  2070,  2104,  3035,  1141,  1222,
    1303,  2756,  2796,  2836,  2876,  2916,  1226,  1226,  1226,  1226,
    1145,  2956,  -373,  -373,  3267,  3267,  3267,  3267,  3267,  3267,
    3267,  3267,  3267,  3267,  3267,    12,   263,  3074,  2138,  2172,
    2206,  2240,  2274,  2308,  2342,  2376,  -373,  2410,  2444,  -373,
    1226,  2478,  3149,   383,   383,  3298,  3308,  3380,  3380,   148,
     148,   148,   148,  3339,   255,  3349,    66,    66,  -373,  -373,
    -373,  -373,   263,  1656,  1226,  1656,  1226,  1226,   -31,    40,
     261,  1226,   269,  2996,    25,   264,  3254,  -373,  -373,  -373,
    -373,  -373,  -373,  1226,   279,  -373,  -373,  -373,  -373,  -373,
    -373,  -373,  2512,  1710,  1754,  1798,  -373,  -373,  1226,  1226,
    -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,
    3113,  1226,   308,  2546,  -373,  3267,   275,  2580,   327,  -373,
    -373,  3267,  -373,   285,  -373,  1226,  -373,  2614,   291,   292,
     293,  1226,   295,  1226,   296,  1226,    31,  2648,  1226,  3267,
    1656,   298,   973,  1656,  1226,   309,    45,  -373,  1226,  -373,
    -373,   304,   310,  -373,   312,  -373,   316,  -373,  -373,  2682,
    -373,  -373,   318,  -373,  2716,  1226,  -373,    56,   305,   311,
     313,  -373,  1656,  1656,    57,  -373,  -373,  -373,  -373,  -373,
    -373,  -373
  };

  const short
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,     0,     0,   258,   257,
       0,     2,     7,     8,     9,    14,    15,     0,   260,   259,
       0,     0,     0,     0,     0,     1,     4,     5,     6,   195,
      10,    11,   262,     0,   195,   195,     0,   193,   194,     0,
       0,     0,     0,     0,     0,    16,     0,     0,     0,    17,
     191,   192,   270,   269,     0,   261,   266,   268,   196,   197,
     198,   199,   200,   201,   202,    18,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   250,   251,   252,   253,     0,     0,
       0,     0,     0,     0,     0,     0,    53,     0,     0,     0,
     257,    44,    49,     0,    45,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     0,
       0,     0,   239,   240,   181,   182,     0,     0,     0,     0,
       0,     0,     0,   241,   242,     0,   243,   244,   245,   246,
     247,     0,   265,   267,    51,    47,     0,   255,   249,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   264,     0,
      90,    91,    92,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,     0,   158,   159,   160,   161,   162,   163,   164,
     165,   166,     0,   167,   168,   169,   170,   171,   172,   173,
     174,    72,     0,     0,     0,    57,     0,     0,     0,     0,
       0,    83,    84,    85,    87,     0,   204,   204,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     239,   240,   106,   108,    52,    48,    61,    62,    63,    58,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   107,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   183,   184,     0,
     204,     0,    50,    46,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   248,   226,   180,
     175,     0,   178,   179,   177,     0,   176,   254,    67,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,    55,    56,     0,     0,     0,
      82,    81,    86,   206,     0,   203,     0,     0,   204,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   256,   236,    95,   101,   102,   103,   104,   105,
      96,    97,    98,   100,    99,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   217,     0,     0,   238,
       0,     0,     0,   122,   123,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   124,   125,   126,   127,
     128,   237,   227,     0,     0,     0,    94,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   213,   219,   220,
     221,   222,   223,     0,     0,   229,   230,   231,   232,   233,
     234,   235,     0,     0,     0,     0,   228,   185,   204,     0,
     208,   209,   210,   211,   212,   214,   215,   216,   218,   225,
       0,     0,    73,     0,    75,    93,     0,     0,     0,    80,
      88,   205,    89,     0,   187,   204,    60,     0,     0,     0,
       0,   204,     0,   204,     0,   204,     0,     0,     0,   110,
       0,     0,    57,     0,     0,     0,     0,   224,   204,    64,
      66,     0,   203,    69,   203,    71,   203,   186,   207,     0,
      74,    76,     0,    78,     0,   204,   188,     0,     0,     0,
       0,   263,     0,     0,     0,   189,    65,    68,    70,    77,
      79,   190
  };

  const short
  parser::yypgoto_[] =
  {
    -373,  -373,  -373,   378,   385,   387,  -373,  -373,   -22,   297,
    -373,  -373,  -373,   -30,  -121,  -373,  -373,  -373,  -373,  -373,
    -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,
    -373,  -373,  -373,  -373,  -373,  -373,  -373,  -373,   622,  -373,
    -232,  -230,  -216,  -373,  -373,  -373,  -373,  -373,  -373,   -46,
     -40,  -144,  -104,   120,   361,  -373,  -224,  -372,  -373,  -373,
    -373,  -373,  -373,  -373,   -34,  -373,  -373,  -373,  -373,  -373,
      14,    54,   100,   117,   126,   135,  -373,  -373,   152,   200,
    -373,   231,   217,  -373,  -373,   238,   252,   314,   335,  -373,
    -373,  -373,     0,     6,   366,    -4,  -373,  -373,   371,   -20,
     372,   374
  };

  const short
  parser::yydefgoto_[] =
  {
       0,    10,    11,    12,    13,    14,    15,    16,   101,   102,
     156,   103,   104,   105,   353,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   363,   496,
     129,   130,   131,   180,   181,   182,   183,   184,   185,   186,
     187,   134,   135,    36,    37,    58,   531,   365,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   393,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230
  };

  const short
  parser::yytable_[] =
  {
      17,   297,   132,   354,    22,   355,    23,    24,   133,    20,
      21,    17,    49,     8,   136,   441,    65,    66,    33,   356,
      25,   132,   364,   366,    62,   132,   447,   133,    29,    38,
      30,   133,   238,   136,    38,    38,    31,   136,    32,    32,
      60,   298,    57,    51,    34,   155,    42,    39,   150,   233,
      35,    43,   260,   260,   151,    46,   240,   132,   261,   261,
      43,    47,   137,   133,   136,   136,    43,   150,   297,   136,
     448,   150,   239,   151,   450,   452,   405,   151,    44,   451,
     451,   137,   477,   249,     9,   137,   392,   451,   251,   250,
       1,     2,     3,     4,     5,   504,     6,     7,   150,   150,
     451,   537,   138,   150,   151,   151,   451,    45,   298,   151,
     132,    48,   137,   137,   231,   546,   133,   137,   297,   297,
     451,   138,   136,     8,   232,   138,   555,   561,   152,   153,
     260,   451,   451,   234,   303,   259,   261,     8,   235,   532,
     236,   534,   136,   536,   454,   299,    18,    19,   139,   259,
     317,   151,   138,   138,    40,    41,   150,   138,   298,   298,
     237,   241,   151,   242,   243,   140,   248,   139,    52,    53,
     137,   139,   246,   318,   141,   247,   326,   345,   346,   347,
     252,   297,   151,   142,   140,   253,  -259,   254,   140,   260,
     137,   255,   256,   141,     9,   261,   301,   141,   139,   139,
     143,   136,   142,   139,   266,   257,   142,    18,   100,   258,
     138,   267,   299,   297,   271,   140,   140,   268,   151,   143,
     140,   298,   269,   143,   141,   141,   270,   272,   273,   141,
     138,   330,   331,   142,   142,   150,   358,    54,   142,   274,
     275,   151,   276,    32,    55,   277,    56,    57,   144,   137,
     143,   143,   300,   298,   516,   143,   139,   343,   344,   345,
     346,   347,   299,   299,   304,   145,   305,   144,   151,   151,
     306,   144,   307,   140,   308,   309,   139,   310,   311,   312,
     313,   526,   141,   314,   145,   315,   146,   351,   145,   138,
     354,   142,   355,   140,   327,   349,   153,   360,   144,   144,
     147,   406,   141,   144,   547,   146,   356,   361,   143,   146,
     367,   142,   368,   369,   386,   262,   263,   370,   387,   147,
     145,   554,   388,   147,   416,   299,   389,   392,   322,   444,
     446,   151,   478,   505,   520,   139,   146,   146,   330,   331,
     500,   146,   334,   335,   336,   337,   338,   339,   502,   442,
     147,   147,   140,   508,   522,   147,   144,   299,   524,   525,
     528,   141,   148,   151,   343,   344,   345,   346,   347,   455,
     142,   529,   530,   145,   533,   535,   323,   541,   545,   451,
     548,   148,   549,   149,   556,   148,   550,   143,   552,    26,
     557,  -247,   558,   325,   146,  -247,    27,   132,    28,   132,
     265,   542,   149,   133,    50,   133,   149,   324,   147,   136,
      59,   136,   148,   148,   146,    61,    63,   148,    64,   499,
     300,   492,     0,   494,  -247,     0,     0,  -247,   147,     0,
       0,     0,     0,   149,   149,   144,     0,     0,   149,     0,
       0,     0,  -239,   150,     0,   150,  -239,     0,   498,   151,
       0,   151,   357,     0,     0,     0,     0,   137,     0,   137,
       0,     0,     0,     0,     0,  -247,  -247,  -240,     0,     0,
     148,  -240,     0,   146,   132,  -239,   260,   132,  -239,     0,
     133,     0,   261,   133,     0,     0,   136,   147,   136,   136,
     148,   149,   343,   344,   345,   346,   347,   138,   540,   138,
    -240,   543,     0,  -240,     0,     0,   132,   132,     0,     0,
       0,   149,   133,   133,     0,     0,  -239,  -239,   136,   136,
     150,     0,   150,   150,     0,     0,   151,     0,   151,   151,
     559,   560,     0,     0,   137,     0,   137,   137,     0,     0,
       0,  -240,  -240,   139,     0,   139,     0,     0,     0,   148,
    -241,     0,   150,   150,  -241,     0,     0,  -242,   151,   151,
     140,  -242,   140,     0,     0,     0,   137,   137,     0,   141,
     149,   141,     0,     0,   138,     0,   138,   138,   142,     0,
     142,     0,     0,  -241,     0,     0,  -241,     0,     0,     0,
    -242,     0,     0,  -242,     0,   143,     0,   143,     0,     0,
       0,     0,     0,     0,     0,     0,   138,   138,     0,     0,
       0,    83,     0,     0,     0,     8,     0,     0,     0,     0,
     139,     0,   139,   139,  -241,  -241,     0,     0,     0,     0,
       0,  -242,  -242,     0,     0,     0,     0,   140,     0,   140,
     140,     0,     0,   144,   282,   144,   141,   348,   141,   141,
       0,     0,   139,   139,     0,   142,     0,   142,   142,     0,
     145,     0,   145,     0,     0,     0,     0,     0,     0,   140,
     140,     0,   143,     0,   143,   143,     0,     0,   141,   141,
       0,   146,     0,   146,     0,    18,   100,   142,   142,     0,
     179,     0,     0,     0,     0,   147,     0,   147,     0,     0,
       0,     0,   245,     0,   143,   143,     0,     0,     0,    83,
       0,     0,     0,     8,    84,    85,    86,    87,     0,     0,
     144,     0,   144,   144,     0,    89,     0,     0,     0,     0,
       0,    90,    91,    92,    93,    94,    95,   145,   321,   357,
     145,     0,    97,     0,     0,     0,   278,   279,     0,   280,
     281,     0,   144,   144,     0,     0,     0,   148,   146,   148,
     146,   146,     0,     0,     0,     0,     0,    83,     0,   145,
     145,     8,   147,     0,   147,   147,     0,  -243,   149,     0,
     149,  -243,     0,    18,   100,     0,     0,     0,   152,   153,
     146,   146,     0,   316,     0,     0,   319,   320,     0,     0,
     282,     0,     0,   283,   147,   147,     0,     0,   284,   285,
    -243,  -244,     0,  -243,     0,  -244,     0,  -245,     0,     0,
       0,  -245,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,     0,   148,     0,   148,   148,     0,     0,
       0,    18,   100,     0,  -244,     0,     0,  -244,     0,     0,
    -245,  -243,  -243,  -245,   350,   149,   352,   149,   149,   359,
       0,     0,     0,     0,     0,     0,   148,   148,     0,     0,
       0,     0,     0,     0,   371,   372,   373,   374,   375,   376,
     377,   378,     0,     0,     0,  -244,  -244,   149,   149,     0,
       0,  -245,  -245,   379,   380,   381,   382,   383,   384,   385,
       0,     0,     0,     0,   391,     0,     0,     0,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,     0,
       0,     0,     0,     0,     0,     0,   407,   408,   409,   410,
     411,   412,   413,   414,   415,     0,   417,   418,     0,     0,
      83,     0,     0,   421,     8,     0,     0,     0,     0,     0,
       0,   422,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
       0,     0,     0,   282,     0,     0,   283,     0,     0,     0,
       0,   284,   285,     0,     0,     0,     0,     0,     0,   453,
    -246,     0,   456,     0,  -246,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,     0,     0,   472,   473,
     474,   475,   378,    83,    18,   100,     0,     8,    84,    85,
      86,    87,     0,  -246,    83,     0,  -246,     0,     8,    89,
       0,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      95,     0,   490,     0,     0,     0,    97,     0,     0,     0,
       0,     0,     0,     0,    98,    99,     0,   282,     0,     0,
     283,     0,     0,     0,  -246,  -246,   493,     0,   495,   497,
      83,     0,     0,   501,     8,    84,    85,    86,    87,     0,
     157,     0,     0,     0,     0,   507,    89,    18,   100,     0,
       0,     0,    90,    91,    92,    93,    94,    95,    18,   100,
       0,   517,     0,    97,    83,    52,    53,   158,     8,    84,
      85,    86,    87,   519,   159,   160,   161,   162,   163,   164,
      89,   165,   166,   167,   168,   169,    90,    91,    92,    93,
      94,    95,   170,   171,     0,     0,     0,   172,     0,     0,
     539,   173,     0,   244,    18,   100,   544,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   174,   175,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,     0,     0,   177,    18,   100,
      32,    55,   178,    56,    57,    83,    52,    53,   158,     8,
      84,    85,    86,    87,     0,   159,   160,   161,   162,   163,
     164,    89,   165,   166,   167,   168,   169,    90,    91,    92,
      93,    94,    95,   170,   171,   464,     0,     0,   390,   317,
       0,   329,   173,     0,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,     0,     0,     0,     0,   174,   175,
       0,     0,   157,     0,     0,     0,     0,   340,   341,   342,
     343,   344,   345,   346,   347,   176,     0,     0,   177,    18,
     100,    32,    55,   178,    56,    57,    83,    52,    53,   158,
       8,    84,    85,    86,    87,     0,   159,   160,   161,   162,
     163,   164,    89,   165,   166,   167,   168,   169,    90,    91,
      92,    93,    94,    95,   170,   171,   465,     0,     0,   172,
       0,     0,   329,   173,     0,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,     0,     0,     0,     0,   174,
     175,     0,     0,   157,     0,     0,     0,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   176,     0,     0,   177,
      18,   100,    32,    55,   178,    56,    57,    83,    52,    53,
     158,     8,    84,    85,    86,    87,     0,   159,   160,   161,
     162,   163,   164,    89,   165,   166,   167,   168,   169,    90,
      91,    92,    93,    94,    95,   170,   171,   466,     0,     0,
     390,     0,     0,   329,   173,     0,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,     0,     0,     0,     0,
     174,   175,     0,     0,     0,     0,     0,     0,     0,   340,
     341,   342,   343,   344,   345,   346,   347,   176,    67,     0,
     177,    18,   100,    32,    55,   178,    56,    57,    68,     0,
       0,    69,    70,     0,    71,    72,    73,    74,     0,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     0,     0,
       0,     8,    84,    85,    86,    87,    88,     0,     0,     0,
       0,     0,     0,    89,     0,     0,     0,     0,     0,    90,
      91,    92,    93,    94,    95,     0,     0,     0,    48,    96,
      97,    67,     0,     0,     0,     0,     0,     0,    98,    99,
       0,    68,     0,     0,    69,    70,     0,    71,    72,    73,
      74,     0,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     0,     0,     0,     8,    84,    85,    86,    87,    88,
       0,    18,   100,     0,     0,     0,    89,     0,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    95,     0,     0,
       0,    48,   264,    97,   154,     0,     0,     0,     0,     0,
       0,    98,    99,    68,     0,     0,    69,    70,     0,    71,
      72,    73,    74,     0,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     0,     0,     0,     8,    84,    85,    86,
      87,    88,     0,     0,    18,   100,     0,     0,    89,     0,
       0,     0,     0,     0,    90,    91,    92,    93,    94,    95,
       0,     0,     0,    48,     0,    97,   302,     0,     0,     0,
       0,     0,     0,    98,    99,    68,     0,     0,    69,    70,
       0,    71,    72,    73,    74,     0,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     0,     0,     0,     8,    84,
      85,    86,    87,    88,     0,     0,    18,   100,     0,     0,
      89,     0,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,     0,     0,     0,    48,     0,    97,     0,     0,
       0,     0,     0,     0,     0,    98,    99,    68,     0,     0,
      69,    70,     0,    71,    72,    73,    74,     0,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,     0,     0,
       8,    84,    85,    86,    87,    88,     0,     0,    18,   100,
       0,     0,    89,     0,     0,     0,     0,     0,    90,    91,
      92,    93,    94,    95,     0,     0,     0,    48,     0,    97,
       0,     0,     0,     0,     0,     0,   419,    98,    99,     0,
       0,   420,     0,     0,     0,     0,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,   100,   340,   341,   342,   343,   344,   345,   346,   347,
     510,     0,     0,     0,     0,   511,     0,     0,     0,     0,
     329,     0,     0,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   512,     0,     0,     0,     0,   513,
       0,     0,     0,     0,   329,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   514,     0,
       0,     0,     0,   515,     0,     0,     0,     0,   329,     0,
       0,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   443,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   329,     0,     0,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   445,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     449,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     329,     0,     0,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   457,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   329,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   458,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   329,     0,
       0,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   459,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   329,     0,     0,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   460,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     461,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     329,     0,     0,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   462,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   329,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   480,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   329,     0,
       0,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   481,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   329,     0,     0,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   482,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     483,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     329,     0,     0,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   484,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   329,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   485,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   329,     0,
       0,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   486,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   329,     0,     0,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   487,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     488,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     329,     0,     0,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   489,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   329,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   419,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   329,     0,
       0,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   509,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   329,     0,     0,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   521,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     523,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     329,     0,     0,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   527,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   329,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   538,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   329,     0,
       0,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   551,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   329,     0,     0,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   553,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     467,     0,     0,     0,     0,     0,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     468,     0,     0,     0,     0,     0,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     469,     0,     0,     0,     0,     0,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     470,     0,     0,     0,     0,     0,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     471,     0,     0,     0,     0,     0,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     476,     0,     0,     0,     0,     0,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     503,     0,     0,     0,     0,     0,   329,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     463,     0,     0,     0,     0,   329,     0,     0,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   479,
       0,     0,     0,     0,   329,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   518,     0,
       0,     0,     0,   329,     0,     0,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   340,
     341,   342,   343,   344,   345,   346,   347,   491,     0,   329,
       0,     0,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   340,   341,   342,   343,   344,
     345,   346,   347,   328,   329,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   362,   329,
       0,     0,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   340,   341,   342,   343,   344,
     345,   346,   347,   506,   329,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   329,     0,     0,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,     0,     0,
       0,     0,     0,   340,   341,   342,   343,   344,   345,   346,
     347,   330,   331,     0,   333,   334,   335,   336,   337,   338,
     339,   330,   331,     0,     0,   334,   335,   336,   337,   338,
     339,     0,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   330,   331,     0,     0,   334,   335,   336,   337,
     338,   339,   330,   331,     0,     0,   334,   335,   336,   337,
     338,   339,     0,     0,     0,     0,   341,   342,   343,   344,
     345,   346,   347,     0,     0,     0,   341,     0,   343,   344,
     345,   346,   347,   330,   331,     0,     0,     0,     0,   336,
     337,   338,   339,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   343,
     344,   345,   346,   347
  };

  const short
  parser::yycheck_[] =
  {
       0,   145,    48,   235,    69,   235,     6,     7,    48,     3,
       4,    11,    42,    44,    48,    44,    46,    47,    22,   235,
       0,    67,   246,   247,    44,    71,    31,    67,    69,    29,
      79,    71,   110,    67,    34,    35,    79,    71,   116,   116,
      44,   145,   120,    43,    69,    67,    70,    70,    48,    71,
      69,    75,    98,    99,    48,    70,    76,   103,    98,    99,
      75,    70,    48,   103,    98,    99,    75,    67,   212,   103,
      75,    71,    76,    67,    70,    70,   300,    71,    95,    75,
      75,    67,    70,    83,   115,    71,   115,    75,    88,    83,
      11,    12,    13,    14,    15,    70,    17,    18,    98,    99,
      75,    70,    48,   103,    98,    99,    75,    79,   212,   103,
     156,    71,    98,    99,    79,    70,   156,   103,   262,   263,
      75,    67,   156,    44,    69,    71,    70,    70,   119,   120,
     176,    75,    75,    69,   156,    73,   176,    44,    69,   511,
      69,   513,   176,   515,   368,   145,   114,   115,    48,    73,
      74,   145,    98,    99,    34,    35,   156,   103,   262,   263,
      69,    78,   156,    79,    79,    48,    73,    67,    41,    42,
     156,    71,    69,   173,    48,    69,   176,   111,   112,   113,
      69,   325,   176,    48,    67,    69,    77,    69,    71,   235,
     176,    69,    69,    67,   115,   235,    77,    71,    98,    99,
      48,   235,    67,   103,    79,    69,    71,   114,   115,    69,
     156,    79,   212,   357,    73,    98,    99,    79,   212,    67,
     103,   325,    79,    71,    98,    99,    79,    73,    73,   103,
     176,    83,    84,    98,    99,   235,   236,   110,   103,    73,
      73,   235,    73,   116,   117,    73,   119,   120,    48,   235,
      98,    99,    69,   357,   478,   103,   156,   109,   110,   111,
     112,   113,   262,   263,    69,    48,    69,    67,   262,   263,
      69,    71,    69,   156,    69,    69,   176,    69,    69,    69,
      69,   505,   156,    69,    67,    69,    48,    28,    71,   235,
     522,   156,   522,   176,   115,    77,   120,    78,    98,    99,
      48,   301,   176,   103,   528,    67,   522,    78,   156,    71,
      73,   176,    69,    77,    69,    98,    99,    95,    69,    67,
     103,   545,    69,    71,    70,   325,    69,   115,   176,    69,
      79,   325,    69,    69,    26,   235,    98,    99,    83,    84,
      79,   103,    87,    88,    89,    90,    91,    92,    79,   349,
      98,    99,   235,    74,    79,   103,   156,   357,    31,    74,
      69,   235,    48,   357,   109,   110,   111,   112,   113,   369,
     235,    79,    79,   156,    79,    79,   176,    79,    69,    75,
      70,    67,    70,    48,    79,    71,    70,   235,    70,    11,
      79,    40,    79,   176,   156,    44,    11,   443,    11,   445,
     103,   522,    67,   443,    43,   445,    71,   176,   156,   443,
      44,   445,    98,    99,   176,    44,    44,   103,    44,   449,
      69,   443,    -1,   445,    73,    -1,    -1,    76,   176,    -1,
      -1,    -1,    -1,    98,    99,   235,    -1,    -1,   103,    -1,
      -1,    -1,    40,   443,    -1,   445,    44,    -1,   448,   443,
      -1,   445,   235,    -1,    -1,    -1,    -1,   443,    -1,   445,
      -1,    -1,    -1,    -1,    -1,   114,   115,    40,    -1,    -1,
     156,    44,    -1,   235,   520,    73,   522,   523,    76,    -1,
     520,    -1,   522,   523,    -1,    -1,   520,   235,   522,   523,
     176,   156,   109,   110,   111,   112,   113,   443,   520,   445,
      73,   523,    -1,    76,    -1,    -1,   552,   553,    -1,    -1,
      -1,   176,   552,   553,    -1,    -1,   114,   115,   552,   553,
     520,    -1,   522,   523,    -1,    -1,   520,    -1,   522,   523,
     552,   553,    -1,    -1,   520,    -1,   522,   523,    -1,    -1,
      -1,   114,   115,   443,    -1,   445,    -1,    -1,    -1,   235,
      40,    -1,   552,   553,    44,    -1,    -1,    40,   552,   553,
     443,    44,   445,    -1,    -1,    -1,   552,   553,    -1,   443,
     235,   445,    -1,    -1,   520,    -1,   522,   523,   443,    -1,
     445,    -1,    -1,    73,    -1,    -1,    76,    -1,    -1,    -1,
      73,    -1,    -1,    76,    -1,   443,    -1,   445,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   552,   553,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,
     520,    -1,   522,   523,   114,   115,    -1,    -1,    -1,    -1,
      -1,   114,   115,    -1,    -1,    -1,    -1,   520,    -1,   522,
     523,    -1,    -1,   443,    73,   445,   520,    76,   522,   523,
      -1,    -1,   552,   553,    -1,   520,    -1,   522,   523,    -1,
     443,    -1,   445,    -1,    -1,    -1,    -1,    -1,    -1,   552,
     553,    -1,   520,    -1,   522,   523,    -1,    -1,   552,   553,
      -1,   443,    -1,   445,    -1,   114,   115,   552,   553,    -1,
      68,    -1,    -1,    -1,    -1,   443,    -1,   445,    -1,    -1,
      -1,    -1,    80,    -1,   552,   553,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    -1,    -1,
     520,    -1,   522,   523,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,   520,    69,   522,
     523,    -1,    73,    -1,    -1,    -1,    19,    20,    -1,    22,
      23,    -1,   552,   553,    -1,    -1,    -1,   443,   520,   445,
     522,   523,    -1,    -1,    -1,    -1,    -1,    40,    -1,   552,
     553,    44,   520,    -1,   522,   523,    -1,    40,   443,    -1,
     445,    44,    -1,   114,   115,    -1,    -1,    -1,   119,   120,
     552,   553,    -1,   171,    -1,    -1,   174,   175,    -1,    -1,
      73,    -1,    -1,    76,   552,   553,    -1,    -1,    81,    82,
      73,    40,    -1,    76,    -1,    44,    -1,    40,    -1,    -1,
      -1,    44,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,   520,    -1,   522,   523,    -1,    -1,
      -1,   114,   115,    -1,    73,    -1,    -1,    76,    -1,    -1,
      73,   114,   115,    76,   232,   520,   234,   522,   523,   237,
      -1,    -1,    -1,    -1,    -1,    -1,   552,   553,    -1,    -1,
      -1,    -1,    -1,    -1,   252,   253,   254,   255,   256,   257,
     258,   259,    -1,    -1,    -1,   114,   115,   552,   553,    -1,
      -1,   114,   115,   271,   272,   273,   274,   275,   276,   277,
      -1,    -1,    -1,    -1,   282,    -1,    -1,    -1,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   304,   305,   306,   307,
     308,   309,   310,   311,   312,    -1,   314,   315,    -1,    -1,
      40,    -1,    -1,   321,    44,    -1,    -1,    -1,    -1,    -1,
      -1,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
      -1,    -1,    -1,    73,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,   367,
      40,    -1,   370,    -1,    44,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,    -1,    -1,   386,   387,
     388,   389,   390,    40,   114,   115,    -1,    44,    45,    46,
      47,    48,    -1,    73,    40,    -1,    76,    -1,    44,    56,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    -1,   420,    -1,    -1,    -1,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    73,    -1,    -1,
      76,    -1,    -1,    -1,   114,   115,   444,    -1,   446,   447,
      40,    -1,    -1,   451,    44,    45,    46,    47,    48,    -1,
      16,    -1,    -1,    -1,    -1,   463,    56,   114,   115,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    67,   114,   115,
      -1,   479,    -1,    73,    40,    41,    42,    43,    44,    45,
      46,    47,    48,   491,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    73,    -1,    -1,
     518,    77,    -1,    79,   114,   115,   524,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    -1,
      -1,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   110,    -1,    -1,   113,   114,   115,
     116,   117,   118,   119,   120,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    74,    -1,    -1,    73,    74,
      -1,    80,    77,    -1,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    -1,    -1,    -1,    93,    94,
      -1,    -1,    16,    -1,    -1,    -1,    -1,   106,   107,   108,
     109,   110,   111,   112,   113,   110,    -1,    -1,   113,   114,
     115,   116,   117,   118,   119,   120,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    74,    -1,    -1,    73,
      -1,    -1,    80,    77,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,    93,
      94,    -1,    -1,    16,    -1,    -1,    -1,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,   110,    -1,    -1,   113,
     114,   115,   116,   117,   118,   119,   120,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    74,    -1,    -1,
      73,    -1,    -1,    80,    77,    -1,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,
      93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,
     107,   108,   109,   110,   111,   112,   113,   110,    11,    -1,
     113,   114,   115,   116,   117,   118,   119,   120,    21,    -1,
      -1,    24,    25,    -1,    27,    28,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    11,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    21,    -1,    -1,    24,    25,    -1,    27,    28,    29,
      30,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      -1,   114,   115,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    71,    72,    73,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    21,    -1,    -1,    24,    25,    -1,    27,
      28,    29,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    44,    45,    46,    47,
      48,    49,    -1,    -1,   114,   115,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    71,    -1,    73,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    21,    -1,    -1,    24,    25,
      -1,    27,    28,    29,    30,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    44,    45,
      46,    47,    48,    49,    -1,    -1,   114,   115,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    71,    -1,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    21,    -1,    -1,
      24,    25,    -1,    27,    28,    29,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      44,    45,    46,    47,    48,    49,    -1,    -1,   114,   115,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    71,    -1,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    81,    82,    -1,
      -1,    75,    -1,    -1,    -1,    -1,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     114,   115,   106,   107,   108,   109,   110,   111,   112,   113,
      70,    -1,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      80,    -1,    -1,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,    70,    -1,    -1,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,    70,    -1,
      -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,    80,    -1,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      80,    -1,    -1,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,    80,    -1,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,    80,    -1,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      80,    -1,    -1,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,    80,    -1,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,    80,    -1,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      80,    -1,    -1,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,    80,    -1,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,    80,    -1,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      80,    -1,    -1,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,    80,    -1,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,    80,    -1,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      80,    -1,    -1,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,   106,   107,   108,   109,
     110,   111,   112,   113,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,    80,    -1,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,    80,    -1,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,   106,   107,
     108,   109,   110,   111,   112,   113,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      74,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      74,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      74,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      74,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      74,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      74,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      74,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,   109,   110,   111,   112,   113,
      75,    -1,    -1,    -1,    -1,    80,    -1,    -1,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   106,   107,   108,   109,   110,   111,   112,   113,    75,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,    75,    -1,
      -1,    -1,    -1,    80,    -1,    -1,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,
     107,   108,   109,   110,   111,   112,   113,    78,    -1,    80,
      -1,    -1,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,
     111,   112,   113,    79,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     106,   107,   108,   109,   110,   111,   112,   113,    79,    80,
      -1,    -1,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,   109,   110,
     111,   112,   113,    79,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    80,    -1,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
     106,   107,   108,   109,   110,   111,   112,   113,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,   109,   110,   111,   112,
     113,    83,    84,    -1,    86,    87,    88,    89,    90,    91,
      92,    83,    84,    -1,    -1,    87,    88,    89,    90,    91,
      92,    -1,    -1,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,    -1,    -1,   106,   107,   108,   109,   110,   111,
     112,   113,    83,    84,    -1,    -1,    87,    88,    89,    90,
      91,    92,    83,    84,    -1,    -1,    87,    88,    89,    90,
      91,    92,    -1,    -1,    -1,    -1,   107,   108,   109,   110,
     111,   112,   113,    -1,    -1,    -1,   107,    -1,   109,   110,
     111,   112,   113,    83,    84,    -1,    -1,    -1,    -1,    89,
      90,    91,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,
     110,   111,   112,   113
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    11,    12,    13,    14,    15,    17,    18,    44,   115,
     131,   132,   133,   134,   135,   136,   137,   222,   114,   115,
     223,   223,    69,   222,   222,     0,   133,   134,   135,    69,
      79,    79,   116,   225,    69,    69,   183,   184,   222,    70,
     183,   183,    70,    75,    95,    79,    70,    70,    71,   143,
     184,   222,    41,    42,   110,   117,   119,   120,   185,   224,
     225,   228,   229,   230,   231,   143,   143,    11,    21,    24,
      25,    27,    28,    29,    30,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    45,    46,    47,    48,    49,    56,
      62,    63,    64,    65,    66,    67,    72,    73,    81,    82,
     115,   138,   139,   141,   142,   143,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   170,
     171,   172,   179,   180,   181,   182,   194,   200,   201,   202,
     203,   204,   205,   208,   209,   212,   215,   216,   217,   218,
     222,   223,   119,   120,    12,   138,   140,    16,    43,    50,
      51,    52,    53,    54,    55,    57,    58,    59,    60,    61,
      68,    69,    73,    77,    93,    94,   110,   113,   118,   168,
     173,   174,   175,   176,   177,   178,   179,   180,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,    79,    69,   138,    69,    69,    69,    69,   110,   225,
     229,    78,    79,    79,    79,   168,    69,    69,    73,   222,
     223,   222,    69,    69,    69,    69,    69,    69,    69,    73,
     179,   180,   212,   212,    72,   139,    79,    79,    79,    79,
      79,    73,    73,    73,    73,    73,    73,    73,    19,    20,
      22,    23,    73,    76,    81,    82,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   181,   182,   222,
      69,    77,    12,   138,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,   168,    74,   222,   168,
     168,    69,   208,   209,   211,   212,   222,   115,    79,    80,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
     106,   107,   108,   109,   110,   111,   112,   113,    76,    77,
     168,    28,   168,   144,   170,   171,   172,   212,   222,   168,
      78,    78,    79,   168,   186,   187,   186,    73,    69,    77,
      95,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,    69,    69,    69,    69,
      73,   168,   115,   221,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   186,   222,   168,   168,   168,
     168,   168,   168,   168,   168,   168,    70,   168,   168,    70,
      75,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,    44,   222,    70,    69,    70,    79,    31,    75,    70,
      70,    75,    70,   168,   186,   222,   168,    70,    70,    70,
      70,    70,    70,    75,    74,    74,    74,    74,    74,    74,
      74,    74,   168,   168,   168,   168,    74,    70,    69,    75,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
     168,    78,   138,   168,   138,   168,   169,   168,   222,   143,
      79,   168,    79,    74,    70,    69,    79,   168,    74,    70,
      70,    75,    70,    75,    70,    75,   186,   168,    75,   168,
      26,    70,    79,    70,    31,    74,   186,    70,    69,    79,
      79,   186,   187,    79,   187,    79,   187,    70,    70,   168,
     138,    79,   144,   138,   168,    69,    70,   186,    70,    70,
      70,    70,    70,    70,   186,    70,    79,    79,    79,   138,
     138,    70
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     133,   134,   135,   135,   135,   135,   136,   137,   137,   137,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   139,   139,   140,   140,   141,   141,
     142,   142,   143,   143,   144,   144,   144,   144,   145,   145,
     146,   147,   147,   147,   148,   149,   149,   150,   151,   151,
     152,   152,   153,   154,   155,   156,   157,   158,   159,   159,
     160,   161,   161,   162,   163,   164,   165,   165,   166,   167,
     168,   168,   168,   169,   169,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   171,   171,   172,   172,
     173,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   176,   177,   177,   177,   177,
     178,   179,   179,   180,   180,   181,   181,   181,   181,   182,
     182,   183,   183,   183,   183,   183,   184,   185,   185,   185,
     185,   185,   185,   186,   186,   187,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   207,   208,   208,
     208,   208,   208,   208,   208,   208,   209,   210,   211,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   222,   223,
     223,   224,   225,   226,   227,   228,   228,   229,   229,   230,
     231
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     5,     5,     6,     6,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       3,     2,     3,     2,     1,     1,     1,     0,     2,     2,
       5,     2,     2,     2,     6,     8,     6,     3,     8,     6,
       8,     6,     2,     5,     7,     5,     7,     9,     7,     9,
       5,     3,     3,     2,     2,     2,     3,     2,     5,     5,
       1,     1,     1,     1,     0,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       5,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     1,     1,     2,     2,     4,     6,     5,     7,     8,
       9,     3,     3,     1,     1,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     3,     1,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,     4,     4,
       4,     4,     4,     4,     6,     4,     2,     3,     4,     4,
       4,     4,     4,     4,     4,     4,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     7,     1,     2,     1,     2,     1,     1,
       1
  };




#if T6DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   295,   295,   296,   300,   302,   304,   306,   308,   310,
     315,   319,   324,   325,   326,   327,   331,   336,   338,   340,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   372,   373,   377,   379,   384,   386,
     391,   392,   396,   397,   401,   403,   405,   408,   412,   414,
     419,   424,   426,   428,   433,   438,   440,   445,   450,   452,
     457,   459,   464,   469,   474,   479,   484,   489,   494,   496,
     501,   506,   508,   513,   518,   523,   528,   530,   535,   540,
     545,   546,   547,   551,   552,   556,   558,   560,   562,   564,
     566,   568,   570,   572,   574,   576,   581,   583,   588,   590,
     595,   600,   602,   604,   606,   608,   610,   612,   614,   616,
     618,   620,   622,   624,   626,   628,   630,   632,   634,   639,
     640,   641,   642,   643,   644,   645,   646,   647,   648,   649,
     650,   651,   652,   653,   654,   655,   656,   657,   658,   659,
     660,   661,   662,   663,   664,   665,   666,   667,   668,   669,
     670,   671,   672,   673,   674,   675,   676,   677,   678,   679,
     680,   681,   682,   683,   684,   688,   693,   695,   697,   699,
     704,   709,   710,   713,   714,   718,   720,   722,   724,   729,
     731,   736,   738,   740,   742,   745,   749,   754,   755,   756,
     757,   758,   759,   763,   766,   770,   772,   777,   782,   787,
     792,   797,   802,   807,   812,   817,   822,   827,   832,   837,
     842,   847,   852,   857,   862,   867,   872,   874,   879,   881,
     883,   885,   887,   889,   891,   893,   898,   903,   908,   913,
     914,   915,   916,   917,   918,   919,   920,   921,   925,   930,
     935,   940,   945,   950,   955,   960,   965,   970,   972,   977,
     979,   984,   989,   994,   999,  1004,  1006,  1011,  1013,  1018,
    1023
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
#endif // T6DEBUG


#line 13 "parser.ypp"
} } } // xsk::arc::t6
#line 5519 "parser.cpp"

#line 1027 "parser.ypp"


void xsk::arc::t6::parser::error(const xsk::arc::location& loc, const std::string& msg)
{
    throw xsk::arc::comp_error(loc, msg);
}
