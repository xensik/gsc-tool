// A Bison parser, made by GNU Bison 3.7.5.

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
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
#line 34 "parser.ypp"

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

  /*---------------.
  | symbol kinds.  |
  `---------------*/



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

      case symbol_kind::S_decl_constant: // decl_constant
        value.YY_MOVE_OR_COPY< ast::decl_constant::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.YY_MOVE_OR_COPY< ast::stmt_breakpoint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.YY_MOVE_OR_COPY< ast::stmt_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.YY_MOVE_OR_COPY< ast::stmt_case::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_decl_constant: // decl_constant
        value.move< ast::decl_constant::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.move< ast::stmt_breakpoint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< ast::stmt_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< ast::stmt_case::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_decl_constant: // decl_constant
        value.copy< ast::decl_constant::ptr > (that.value);
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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.copy< ast::stmt_breakpoint::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.copy< ast::stmt_call::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.copy< ast::stmt_case::ptr > (that.value);
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

      case symbol_kind::S_decl_constant: // decl_constant
        value.move< ast::decl_constant::ptr > (that.value);
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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.move< ast::stmt_breakpoint::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< ast::stmt_call::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< ast::stmt_case::ptr > (that.value);
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
  parser::yypop_ (int n)
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
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
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

    /// Discard the LAC context in case there still is one left from a
    /// previous invocation.
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

      case symbol_kind::S_decl_constant: // decl_constant
        yylhs.value.emplace< ast::decl_constant::ptr > ();
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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        yylhs.value.emplace< ast::stmt_breakpoint::ptr > ();
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        yylhs.value.emplace< ast::stmt_call::ptr > ();
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        yylhs.value.emplace< ast::stmt_case::ptr > ();
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
#line 285 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < ast::program::ptr > ()); }
#line 2315 "parser.cpp"
    break;

  case 3: // root: %empty
#line 286 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 2321 "parser.cpp"
    break;

  case 4: // program: program inline
#line 291 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 2327 "parser.cpp"
    break;

  case 5: // program: program include
#line 293 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2333 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 295 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2339 "parser.cpp"
    break;

  case 7: // program: inline
#line 297 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 2345 "parser.cpp"
    break;

  case 8: // program: include
#line 299 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2351 "parser.cpp"
    break;

  case 9: // program: declaration
#line 301 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2357 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 305 "parser.ypp"
                                 { lexer.push_header(yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2363 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 310 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2369 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 314 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2375 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 315 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2381 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 316 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2387 "parser.cpp"
    break;

  case 15: // declaration: decl_constant
#line 317 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_constant = std::move(yystack_[0].value.as < ast::decl_constant::ptr > ()); }
#line 2393 "parser.cpp"
    break;

  case 16: // declaration: decl_thread
#line 318 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2399 "parser.cpp"
    break;

  case 17: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 323 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2405 "parser.cpp"
    break;

  case 18: // decl_constant: expr_identifier "=" expr ";"
#line 328 "parser.ypp"
        { yylhs.value.as < ast::decl_constant::ptr > () = std::make_unique<ast::decl_constant>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2411 "parser.cpp"
    break;

  case 19: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 333 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2417 "parser.cpp"
    break;

  case 20: // stmt: stmt_block
#line 337 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2423 "parser.cpp"
    break;

  case 21: // stmt: stmt_call
#line 338 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2429 "parser.cpp"
    break;

  case 22: // stmt: stmt_assign
#line 339 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2435 "parser.cpp"
    break;

  case 23: // stmt: stmt_endon
#line 340 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2441 "parser.cpp"
    break;

  case 24: // stmt: stmt_notify
#line 341 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2447 "parser.cpp"
    break;

  case 25: // stmt: stmt_wait
#line 342 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2453 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittill
#line 343 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2459 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittillmatch
#line 344 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2465 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillframeend
#line 345 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2471 "parser.cpp"
    break;

  case 29: // stmt: stmt_if
#line 346 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2477 "parser.cpp"
    break;

  case 30: // stmt: stmt_ifelse
#line 347 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2483 "parser.cpp"
    break;

  case 31: // stmt: stmt_while
#line 348 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2489 "parser.cpp"
    break;

  case 32: // stmt: stmt_dowhile
#line 349 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2495 "parser.cpp"
    break;

  case 33: // stmt: stmt_for
#line 350 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2501 "parser.cpp"
    break;

  case 34: // stmt: stmt_foreach
#line 351 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2507 "parser.cpp"
    break;

  case 35: // stmt: stmt_switch
#line 352 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2513 "parser.cpp"
    break;

  case 36: // stmt: stmt_case
#line 353 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2519 "parser.cpp"
    break;

  case 37: // stmt: stmt_default
#line 354 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2525 "parser.cpp"
    break;

  case 38: // stmt: stmt_break
#line 355 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2531 "parser.cpp"
    break;

  case 39: // stmt: stmt_continue
#line 356 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2537 "parser.cpp"
    break;

  case 40: // stmt: stmt_return
#line 357 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2543 "parser.cpp"
    break;

  case 41: // stmt: stmt_breakpoint
#line 358 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_breakpoint = std::move(yystack_[0].value.as < ast::stmt_breakpoint::ptr > ()); }
#line 2549 "parser.cpp"
    break;

  case 42: // stmt: stmt_prof_begin
#line 359 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2555 "parser.cpp"
    break;

  case 43: // stmt: stmt_prof_end
#line 360 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2561 "parser.cpp"
    break;

  case 44: // stmt_or_dev: stmt
#line 364 "parser.ypp"
               { yylhs.value.as < ast::stmt > () = std::move(yystack_[0].value.as < ast::stmt > ()); }
#line 2567 "parser.cpp"
    break;

  case 45: // stmt_or_dev: stmt_dev
#line 365 "parser.ypp"
               { yylhs.value.as < ast::stmt > ().as_dev = std::move(yystack_[0].value.as < ast::stmt_dev::ptr > ()); }
#line 2573 "parser.cpp"
    break;

  case 46: // stmt_list: stmt_list stmt
#line 370 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2579 "parser.cpp"
    break;

  case 47: // stmt_list: stmt
#line 372 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2585 "parser.cpp"
    break;

  case 48: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 377 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2591 "parser.cpp"
    break;

  case 49: // stmt_or_dev_list: stmt_or_dev
#line 379 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2597 "parser.cpp"
    break;

  case 50: // stmt_dev: "/#" stmt_list "#/"
#line 383 "parser.ypp"
                                { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::move(yystack_[1].value.as < ast::stmt_list::ptr > ())); }
#line 2603 "parser.cpp"
    break;

  case 51: // stmt_dev: "/#" "#/"
#line 384 "parser.ypp"
                      { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2609 "parser.cpp"
    break;

  case 52: // stmt_block: "{" stmt_or_dev_list "}"
#line 388 "parser.ypp"
                                     { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2615 "parser.cpp"
    break;

  case 53: // stmt_block: "{" "}"
#line 389 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2621 "parser.cpp"
    break;

  case 54: // stmt_expr: expr_assign
#line 394 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2627 "parser.cpp"
    break;

  case 55: // stmt_expr: expr_increment
#line 396 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2633 "parser.cpp"
    break;

  case 56: // stmt_expr: expr_decrement
#line 398 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2639 "parser.cpp"
    break;

  case 57: // stmt_expr: %empty
#line 400 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2645 "parser.cpp"
    break;

  case 58: // stmt_call: expr_call ";"
#line 405 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2651 "parser.cpp"
    break;

  case 59: // stmt_call: expr_method ";"
#line 407 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2657 "parser.cpp"
    break;

  case 60: // stmt_assign: expr_assign ";"
#line 412 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2663 "parser.cpp"
    break;

  case 61: // stmt_assign: expr_increment ";"
#line 414 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2669 "parser.cpp"
    break;

  case 62: // stmt_assign: expr_decrement ";"
#line 416 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2675 "parser.cpp"
    break;

  case 63: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 421 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2681 "parser.cpp"
    break;

  case 64: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 426 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2687 "parser.cpp"
    break;

  case 65: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 428 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2693 "parser.cpp"
    break;

  case 66: // stmt_wait: "wait" expr ";"
#line 433 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2699 "parser.cpp"
    break;

  case 67: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 438 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2705 "parser.cpp"
    break;

  case 68: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 440 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2711 "parser.cpp"
    break;

  case 69: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 445 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2717 "parser.cpp"
    break;

  case 70: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 447 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2723 "parser.cpp"
    break;

  case 71: // stmt_waittillframeend: "waittillframeend" ";"
#line 452 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2729 "parser.cpp"
    break;

  case 72: // stmt_if: "if" "(" expr ")" stmt
#line 457 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2735 "parser.cpp"
    break;

  case 73: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 462 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2741 "parser.cpp"
    break;

  case 74: // stmt_while: "while" "(" expr ")" stmt
#line 467 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2747 "parser.cpp"
    break;

  case 75: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 472 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2753 "parser.cpp"
    break;

  case 76: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 477 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2759 "parser.cpp"
    break;

  case 77: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 482 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2765 "parser.cpp"
    break;

  case 78: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 484 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2771 "parser.cpp"
    break;

  case 79: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 489 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2777 "parser.cpp"
    break;

  case 80: // stmt_case: "case" expr_integer ":"
#line 494 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2783 "parser.cpp"
    break;

  case 81: // stmt_case: "case" expr_string ":"
#line 496 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2789 "parser.cpp"
    break;

  case 82: // stmt_default: "default" ":"
#line 501 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2795 "parser.cpp"
    break;

  case 83: // stmt_break: "break" ";"
#line 506 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2801 "parser.cpp"
    break;

  case 84: // stmt_continue: "continue" ";"
#line 511 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2807 "parser.cpp"
    break;

  case 85: // stmt_return: "return" expr ";"
#line 516 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2813 "parser.cpp"
    break;

  case 86: // stmt_return: "return" ";"
#line 518 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2819 "parser.cpp"
    break;

  case 87: // stmt_breakpoint: "breakpoint" ";"
#line 523 "parser.ypp"
        { yylhs.value.as < ast::stmt_breakpoint::ptr > () = std::make_unique<ast::stmt_breakpoint>(yylhs.location); }
#line 2825 "parser.cpp"
    break;

  case 88: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 528 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2831 "parser.cpp"
    break;

  case 89: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 533 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2837 "parser.cpp"
    break;

  case 90: // expr: expr_ternary
#line 537 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2843 "parser.cpp"
    break;

  case 91: // expr: expr_binary
#line 538 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2849 "parser.cpp"
    break;

  case 92: // expr: expr_primitive
#line 539 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2855 "parser.cpp"
    break;

  case 93: // expr_or_empty: expr
#line 543 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2861 "parser.cpp"
    break;

  case 94: // expr_or_empty: %empty
#line 544 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2867 "parser.cpp"
    break;

  case 95: // expr_assign: expr_object "=" expr
#line 549 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2873 "parser.cpp"
    break;

  case 96: // expr_assign: expr_object "|=" expr
#line 551 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2879 "parser.cpp"
    break;

  case 97: // expr_assign: expr_object "&=" expr
#line 553 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2885 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object "^=" expr
#line 555 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2891 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "<<=" expr
#line 557 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2897 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object ">>=" expr
#line 559 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2903 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "+=" expr
#line 561 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2909 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "-=" expr
#line 563 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2915 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object "*=" expr
#line 565 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2921 "parser.cpp"
    break;

  case 104: // expr_assign: expr_object "/=" expr
#line 567 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2927 "parser.cpp"
    break;

  case 105: // expr_assign: expr_object "%=" expr
#line 569 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2933 "parser.cpp"
    break;

  case 106: // expr_increment: "++" expr_object
#line 574 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2939 "parser.cpp"
    break;

  case 107: // expr_increment: expr_object "++"
#line 576 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2945 "parser.cpp"
    break;

  case 108: // expr_decrement: "--" expr_object
#line 581 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2951 "parser.cpp"
    break;

  case 109: // expr_decrement: expr_object "--"
#line 583 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2957 "parser.cpp"
    break;

  case 110: // expr_ternary: expr "?" expr ":" expr
#line 588 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2963 "parser.cpp"
    break;

  case 111: // expr_binary: expr "||" expr
#line 593 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2969 "parser.cpp"
    break;

  case 112: // expr_binary: expr "&&" expr
#line 595 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2975 "parser.cpp"
    break;

  case 113: // expr_binary: expr "==" expr
#line 597 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2981 "parser.cpp"
    break;

  case 114: // expr_binary: expr "!=" expr
#line 599 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2987 "parser.cpp"
    break;

  case 115: // expr_binary: expr "<=" expr
#line 601 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2993 "parser.cpp"
    break;

  case 116: // expr_binary: expr ">=" expr
#line 603 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2999 "parser.cpp"
    break;

  case 117: // expr_binary: expr "<" expr
#line 605 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3005 "parser.cpp"
    break;

  case 118: // expr_binary: expr ">" expr
#line 607 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3011 "parser.cpp"
    break;

  case 119: // expr_binary: expr "|" expr
#line 609 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3017 "parser.cpp"
    break;

  case 120: // expr_binary: expr "&" expr
#line 611 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3023 "parser.cpp"
    break;

  case 121: // expr_binary: expr "^" expr
#line 613 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3029 "parser.cpp"
    break;

  case 122: // expr_binary: expr "<<" expr
#line 615 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3035 "parser.cpp"
    break;

  case 123: // expr_binary: expr ">>" expr
#line 617 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3041 "parser.cpp"
    break;

  case 124: // expr_binary: expr "+" expr
#line 619 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3047 "parser.cpp"
    break;

  case 125: // expr_binary: expr "-" expr
#line 621 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3053 "parser.cpp"
    break;

  case 126: // expr_binary: expr "*" expr
#line 623 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3059 "parser.cpp"
    break;

  case 127: // expr_binary: expr "/" expr
#line 625 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3065 "parser.cpp"
    break;

  case 128: // expr_binary: expr "%" expr
#line 627 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3071 "parser.cpp"
    break;

  case 129: // expr_primitive: expr_complement
#line 631 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 3077 "parser.cpp"
    break;

  case 130: // expr_primitive: expr_not
#line 632 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 3083 "parser.cpp"
    break;

  case 131: // expr_primitive: expr_call
#line 633 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3089 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_method
#line 634 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3095 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_getnextarraykey
#line 635 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getnextarraykey::ptr > ()); }
#line 3101 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_getfirstarraykey
#line 636 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getfirstarraykey::ptr > ()); }
#line 3107 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_getdvarcoloralpha
#line 637 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcoloralpha::ptr > ()); }
#line 3113 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_getdvarcolorblue
#line 638 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorblue::ptr > ()); }
#line 3119 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_getdvarcolorgreen
#line 639 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorgreen::ptr > ()); }
#line 3125 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_getdvarcolorred
#line 640 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorred::ptr > ()); }
#line 3131 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_getdvarvector
#line 641 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarvector::ptr > ()); }
#line 3137 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_getdvarfloat
#line 642 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarfloat::ptr > ()); }
#line 3143 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_getdvarint
#line 643 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarint::ptr > ()); }
#line 3149 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_getdvar
#line 644 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvar::ptr > ()); }
#line 3155 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_gettime
#line 645 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_gettime::ptr > ()); }
#line 3161 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_abs
#line 646 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_abs::ptr > ()); }
#line 3167 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_vectortoangles
#line 647 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vectortoangles::ptr > ()); }
#line 3173 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_angleclamp180
#line 648 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_angleclamp180::ptr > ()); }
#line 3179 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_anglestoforward
#line 649 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoforward::ptr > ()); }
#line 3185 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_anglestoright
#line 650 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoright::ptr > ()); }
#line 3191 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_anglestoup
#line 651 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoup::ptr > ()); }
#line 3197 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_vectorscale
#line 652 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vectorscale::ptr > ()); }
#line 3203 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_isdefined
#line 653 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_isdefined::ptr > ()); }
#line 3209 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_reference
#line 654 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 3215 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_array
#line 655 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3221 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_field
#line 656 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3227 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_size
#line 657 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 3233 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_paren
#line 658 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 3239 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_empty_array
#line 659 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 3245 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_undefined
#line 660 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 3251 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_game
#line 661 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3257 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_self
#line 662 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3263 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_anim
#line 663 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3269 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_level
#line 664 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3275 "parser.cpp"
    break;

  case 163: // expr_primitive: expr_animation
#line 665 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 3281 "parser.cpp"
    break;

  case 164: // expr_primitive: expr_identifier
#line 666 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3287 "parser.cpp"
    break;

  case 165: // expr_primitive: expr_istring
#line 667 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 3293 "parser.cpp"
    break;

  case 166: // expr_primitive: expr_string
#line 668 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 3299 "parser.cpp"
    break;

  case 167: // expr_primitive: expr_vector
#line 669 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 3305 "parser.cpp"
    break;

  case 168: // expr_primitive: expr_hash
#line 670 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_hash::ptr > ()); }
#line 3311 "parser.cpp"
    break;

  case 169: // expr_primitive: expr_float
#line 671 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 3317 "parser.cpp"
    break;

  case 170: // expr_primitive: expr_integer
#line 672 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 3323 "parser.cpp"
    break;

  case 171: // expr_primitive: expr_false
#line 673 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 3329 "parser.cpp"
    break;

  case 172: // expr_primitive: expr_true
#line 674 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 3335 "parser.cpp"
    break;

  case 173: // expr_complement: "~" expr
#line 679 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3341 "parser.cpp"
    break;

  case 174: // expr_not: "!" expr
#line 684 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3347 "parser.cpp"
    break;

  case 175: // expr_call: expr_function
#line 688 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3353 "parser.cpp"
    break;

  case 176: // expr_call: expr_pointer
#line 689 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3359 "parser.cpp"
    break;

  case 177: // expr_method: expr_object expr_function
#line 692 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3365 "parser.cpp"
    break;

  case 178: // expr_method: expr_object expr_pointer
#line 693 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3371 "parser.cpp"
    break;

  case 179: // expr_function: expr_identifier "(" expr_arguments ")"
#line 698 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3377 "parser.cpp"
    break;

  case 180: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 700 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3383 "parser.cpp"
    break;

  case 181: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 702 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3389 "parser.cpp"
    break;

  case 182: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 704 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3395 "parser.cpp"
    break;

  case 183: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 709 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3401 "parser.cpp"
    break;

  case 184: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 711 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3407 "parser.cpp"
    break;

  case 185: // expr_parameters: expr_parameters "," expr_identifier
#line 716 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3413 "parser.cpp"
    break;

  case 186: // expr_parameters: expr_identifier
#line 718 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3419 "parser.cpp"
    break;

  case 187: // expr_parameters: %empty
#line 720 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 3425 "parser.cpp"
    break;

  case 188: // expr_arguments: expr_arguments_no_empty
#line 725 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 3431 "parser.cpp"
    break;

  case 189: // expr_arguments: %empty
#line 727 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3437 "parser.cpp"
    break;

  case 190: // expr_arguments_no_empty: expr_arguments "," expr
#line 732 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3443 "parser.cpp"
    break;

  case 191: // expr_arguments_no_empty: expr
#line 734 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3449 "parser.cpp"
    break;

  case 192: // expr_getnextarraykey: "getnextarraykey" "(" expr "," expr ")"
#line 739 "parser.ypp"
        { yylhs.value.as < ast::expr_getnextarraykey::ptr > () = std::make_unique<ast::expr_getnextarraykey>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3455 "parser.cpp"
    break;

  case 193: // expr_getfirstarraykey: "getfirstarraykey" "(" expr ")"
#line 744 "parser.ypp"
        { yylhs.value.as < ast::expr_getfirstarraykey::ptr > () = std::make_unique<ast::expr_getfirstarraykey>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3461 "parser.cpp"
    break;

  case 194: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr ")"
#line 749 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcoloralpha::ptr > () = std::make_unique<ast::expr_getdvarcoloralpha>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3467 "parser.cpp"
    break;

  case 195: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr ")"
#line 754 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorblue::ptr > () = std::make_unique<ast::expr_getdvarcolorblue>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3473 "parser.cpp"
    break;

  case 196: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr ")"
#line 759 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorgreen::ptr > () = std::make_unique<ast::expr_getdvarcolorgreen>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3479 "parser.cpp"
    break;

  case 197: // expr_getdvarcolorred: "getdvarcolorred" "(" expr ")"
#line 764 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorred::ptr > () = std::make_unique<ast::expr_getdvarcolorred>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3485 "parser.cpp"
    break;

  case 198: // expr_getdvarvector: "getdvarvector" "(" expr ")"
#line 769 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarvector::ptr > () = std::make_unique<ast::expr_getdvarvector>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3491 "parser.cpp"
    break;

  case 199: // expr_getdvarfloat: "getdvarfloat" "(" expr ")"
#line 774 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarfloat::ptr > () = std::make_unique<ast::expr_getdvarfloat>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3497 "parser.cpp"
    break;

  case 200: // expr_getdvarint: "getdvarint" "(" expr ")"
#line 779 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarint::ptr > () = std::make_unique<ast::expr_getdvarint>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3503 "parser.cpp"
    break;

  case 201: // expr_getdvar: "getdvar" "(" expr ")"
#line 784 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvar::ptr > () = std::make_unique<ast::expr_getdvar>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3509 "parser.cpp"
    break;

  case 202: // expr_gettime: "gettime" "(" ")"
#line 789 "parser.ypp"
        { yylhs.value.as < ast::expr_gettime::ptr > () = std::make_unique<ast::expr_gettime>(yylhs.location); }
#line 3515 "parser.cpp"
    break;

  case 203: // expr_abs: "abs" "(" expr ")"
#line 794 "parser.ypp"
        { yylhs.value.as < ast::expr_abs::ptr > () = std::make_unique<ast::expr_abs>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3521 "parser.cpp"
    break;

  case 204: // expr_vectortoangles: "vectortoangles" "(" expr ")"
#line 799 "parser.ypp"
        { yylhs.value.as < ast::expr_vectortoangles::ptr > () = std::make_unique<ast::expr_vectortoangles>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3527 "parser.cpp"
    break;

  case 205: // expr_angleclamp180: "angleclamp180" "(" expr ")"
#line 804 "parser.ypp"
        { yylhs.value.as < ast::expr_angleclamp180::ptr > () = std::make_unique<ast::expr_angleclamp180>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3533 "parser.cpp"
    break;

  case 206: // expr_anglestoforward: "anglestoforward" "(" expr ")"
#line 809 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoforward::ptr > () = std::make_unique<ast::expr_anglestoforward>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3539 "parser.cpp"
    break;

  case 207: // expr_anglestoright: "anglestoright" "(" expr ")"
#line 814 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoright::ptr > () = std::make_unique<ast::expr_anglestoright>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3545 "parser.cpp"
    break;

  case 208: // expr_anglestoup: "anglestoup" "(" expr ")"
#line 819 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoup::ptr > () = std::make_unique<ast::expr_anglestoup>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3551 "parser.cpp"
    break;

  case 209: // expr_vectorscale: "vectorscale" "(" expr "," expr ")"
#line 824 "parser.ypp"
        { yylhs.value.as < ast::expr_vectorscale::ptr > () = std::make_unique<ast::expr_vectorscale>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3557 "parser.cpp"
    break;

  case 210: // expr_isdefined: "isdefined" "(" expr ")"
#line 829 "parser.ypp"
        { yylhs.value.as < ast::expr_isdefined::ptr > () = std::make_unique<ast::expr_isdefined>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3563 "parser.cpp"
    break;

  case 211: // expr_reference: "::" expr_identifier
#line 834 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3569 "parser.cpp"
    break;

  case 212: // expr_reference: expr_path "::" expr_identifier
#line 836 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3575 "parser.cpp"
    break;

  case 213: // expr_array: expr_object "[" expr "]"
#line 841 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3581 "parser.cpp"
    break;

  case 214: // expr_field: expr_object "." expr_identifier_nosize
#line 846 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3587 "parser.cpp"
    break;

  case 215: // expr_size: expr_object "." "size"
#line 851 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ())); }
#line 3593 "parser.cpp"
    break;

  case 216: // expr_paren: "(" expr ")"
#line 856 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3599 "parser.cpp"
    break;

  case 217: // expr_object: expr_call
#line 860 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3605 "parser.cpp"
    break;

  case 218: // expr_object: expr_method
#line 861 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3611 "parser.cpp"
    break;

  case 219: // expr_object: expr_array
#line 862 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3617 "parser.cpp"
    break;

  case 220: // expr_object: expr_field
#line 863 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3623 "parser.cpp"
    break;

  case 221: // expr_object: expr_game
#line 864 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3629 "parser.cpp"
    break;

  case 222: // expr_object: expr_self
#line 865 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3635 "parser.cpp"
    break;

  case 223: // expr_object: expr_anim
#line 866 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3641 "parser.cpp"
    break;

  case 224: // expr_object: expr_level
#line 867 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3647 "parser.cpp"
    break;

  case 225: // expr_object: expr_identifier
#line 868 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3653 "parser.cpp"
    break;

  case 226: // expr_empty_array: "[" "]"
#line 873 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3659 "parser.cpp"
    break;

  case 227: // expr_undefined: "undefined"
#line 878 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3665 "parser.cpp"
    break;

  case 228: // expr_game: "game"
#line 883 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3671 "parser.cpp"
    break;

  case 229: // expr_self: "self"
#line 888 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3677 "parser.cpp"
    break;

  case 230: // expr_anim: "anim"
#line 893 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3683 "parser.cpp"
    break;

  case 231: // expr_level: "level"
#line 898 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3689 "parser.cpp"
    break;

  case 232: // expr_animation: "%" "identifier"
#line 903 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3695 "parser.cpp"
    break;

  case 233: // expr_identifier_nosize: "identifier"
#line 908 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3701 "parser.cpp"
    break;

  case 234: // expr_identifier: "identifier"
#line 913 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3707 "parser.cpp"
    break;

  case 235: // expr_identifier: "size"
#line 915 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, "size"); }
#line 3713 "parser.cpp"
    break;

  case 236: // expr_path: "identifier"
#line 920 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3719 "parser.cpp"
    break;

  case 237: // expr_path: "path"
#line 922 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3725 "parser.cpp"
    break;

  case 238: // expr_istring: "localized string"
#line 927 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3731 "parser.cpp"
    break;

  case 239: // expr_string: "string literal"
#line 932 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3737 "parser.cpp"
    break;

  case 240: // expr_vector: "(" expr "," expr "," expr ")"
#line 937 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3743 "parser.cpp"
    break;

  case 241: // expr_hash: "hash"
#line 942 "parser.ypp"
        { yylhs.value.as < ast::expr_hash::ptr > () = std::make_unique<ast::expr_hash>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3749 "parser.cpp"
    break;

  case 242: // expr_float: "-" "float"
#line 947 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3755 "parser.cpp"
    break;

  case 243: // expr_float: "float"
#line 949 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3761 "parser.cpp"
    break;

  case 244: // expr_integer: "-" "integer"
#line 954 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3767 "parser.cpp"
    break;

  case 245: // expr_integer: "integer"
#line 956 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3773 "parser.cpp"
    break;

  case 246: // expr_false: "false"
#line 961 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3779 "parser.cpp"
    break;

  case 247: // expr_true: "true"
#line 966 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3785 "parser.cpp"
    break;


#line 3789 "parser.cpp"

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
  "#include", "#using_animtree", "endon", "notify", "wait", "waittill",
  "waittillmatch", "waittillframeend", "if", "else", "do", "while", "for",
  "foreach", "in", "switch", "case", "default", "break", "continue",
  "return", "breakpoint", "prof_begin", "prof_end", "thread", "true",
  "false", "undefined", "size", "game", "self", "anim", "level",
  "getnextarraykey", "getfirstarraykey", "getdvarcoloralpha",
  "getdvarcolorblue", "getdvarcolorgreen", "getdvarcolorred",
  "getdvarvector", "getdvarfloat", "getdvarint", "getdvar", "gettime",
  "abs", "vectortoangles", "angleclamp180", "anglestoforward",
  "anglestoright", "anglestoup", "vectorscale", "isdefined", "(", ")", "{",
  "}", "[", "]", ",", ".", "::", ":", ";", "?", "++", "--", "<<", ">>",
  "||", "&&", "==", "!=", "<=", ">=", "<", ">", "!", "~", "=", "+=", "-=",
  "*=", "/=", "%=", "|=", "&=", "^=", ">>=", "<<=", "|", "&", "^", "+",
  "-", "*", "/", "%", "path", "identifier", "string literal",
  "localized string", "hash", "float", "integer", "SIZEOF", "THEN", "TERN",
  "NEG", "ANIMREF", "PREINC", "PREDEC", "POSTINC", "POSTDEC", "$accept",
  "root", "program", "inline", "include", "declaration", "decl_usingtree",
  "decl_constant", "decl_thread", "stmt", "stmt_or_dev", "stmt_list",
  "stmt_or_dev_list", "stmt_dev", "stmt_block", "stmt_expr", "stmt_call",
  "stmt_assign", "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch",
  "stmt_case", "stmt_default", "stmt_break", "stmt_continue",
  "stmt_return", "stmt_breakpoint", "stmt_prof_begin", "stmt_prof_end",
  "expr", "expr_or_empty", "expr_assign", "expr_increment",
  "expr_decrement", "expr_ternary", "expr_binary", "expr_primitive",
  "expr_complement", "expr_not", "expr_call", "expr_method",
  "expr_function", "expr_pointer", "expr_parameters", "expr_arguments",
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
  "expr_animation", "expr_identifier_nosize", "expr_identifier",
  "expr_path", "expr_istring", "expr_string", "expr_vector", "expr_hash",
  "expr_float", "expr_integer", "expr_false", "expr_true", YY_NULLPTR
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
    if (!yy_lac_established_)
      {
#if T6DEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
    return true;
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* evt)
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
                 << evt << '\n';
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


  const short parser::yypact_ninf_ = -422;

  const short parser::yytable_ninf_ = -237;

  const short
  parser::yypact_[] =
  {
       2,  -422,  -422,   -53,   -53,   -58,  -422,  -422,    19,     2,
    -422,  -422,  -422,  -422,  -422,  -422,   -56,  -422,  -422,   -38,
     -35,   -90,  -422,  -422,  -422,  -422,   -17,  1242,  -422,  -422,
    -422,    -6,   -40,  -422,   -18,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,   -12,    -1,     1,     3,    18,    24,    43,    45,
      62,    64,    67,    68,    75,    76,    80,    81,    83,    84,
      88,  1242,     5,   -17,  1242,  1242,   -14,    44,    46,  -422,
    -422,  -422,  -422,  2588,  -422,  -422,  -422,  -422,  -422,    40,
     171,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,   260,   343,  -422,  -422,   348,  -422,  -422,
     396,   463,   521,   530,  -422,   -20,    86,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,    79,    90,   -17,    96,   101,
      94,  1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,
    1242,   102,  1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,
     700,  1242,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,
    1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,  1322,
     -13,  -422,  -422,   105,    98,  1242,   -17,  -422,   800,  -422,
    -422,  1242,  1242,   -17,  2439,  1510,  1544,  1578,  1612,  1646,
    1680,  1714,  1748,  1782,  -422,  1816,  1850,  1884,  1918,  1952,
    1986,  2478,  2020,  -422,  1242,  1078,  2553,   241,   241,  2702,
    2712,  1153,  1153,   152,   152,   152,   152,  2743,  2753,   584,
     -22,   -22,  -422,  -422,  -422,  1082,  1238,  -422,  -422,  -422,
     -17,  2671,   -32,  -422,   108,   921,  1242,    99,   113,  1039,
     115,   116,   117,   121,   -74,   110,   114,   118,  1162,   123,
     125,   126,  -422,   133,    28,    28,  -422,  -422,   862,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,   130,   131,   132,   136,   138,  -422,
    -422,   637,  -422,  -422,  -422,  -422,   105,  2400,   -16,   129,
    1242,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  1242,  -422,  2517,   139,
    1242,  -422,   108,  -422,  1242,  1242,  -422,  -422,   980,  2623,
    -422,  1242,   191,  1242,   119,   -17,  1242,   100,   146,   147,
    -422,  -422,  -422,  -422,  2658,  -422,  1242,  1242,  -422,  -422,
     538,   538,  -422,  -422,  -422,  -422,  -422,  -422,  -422,   160,
     161,   162,   163,   124,  -422,  -422,  1242,  1242,  1242,  1242,
    1242,  1242,  1242,  1242,  1242,  1242,  1242,   166,  -422,  1242,
    2054,  2088,  1242,   172,  2671,  2671,   -10,  -422,  -422,  -422,
    2122,   173,  2156,   167,  -422,  -422,  -422,  1352,   -24,  2190,
    -422,  -422,  -422,    34,    50,  1242,  1242,  1242,  1242,  2671,
    2671,  2671,  2671,  2671,  2671,  2671,  2671,  2671,  2671,  2671,
     176,    51,  -422,  -422,  2224,  1242,  -422,  1039,  1242,  1039,
    1242,  1242,   -17,    90,   170,   174,  2258,  1388,  1432,  1476,
    1242,  -422,  -422,    52,   224,  2292,  -422,  2671,   175,  2326,
     220,  -422,  -422,  -422,   179,   180,  1242,   187,  1242,   194,
    1242,    54,  -422,  1039,   202,   119,  1039,  1242,  -422,  -422,
     195,   214,  -422,   219,  -422,   225,  -422,  -422,  -422,   227,
    -422,  2360,   211,   213,   221,  1039,  1039,  -422,  -422,  -422,
    -422,  -422
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   235,   234,     0,     2,
       7,     8,     9,    14,    15,    16,     0,   237,   236,     0,
       0,     0,     1,     4,     5,     6,   187,     0,    10,    11,
     239,     0,     0,   186,     0,   247,   246,   227,   228,   229,
     230,   231,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   234,   238,
     241,   243,   245,     0,    90,    91,    92,   129,   130,   131,
     132,   175,   176,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   157,   158,
     159,   160,   161,   162,   163,   164,     0,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   226,   211,   174,   173,   242,   244,   232,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   177,   178,     0,     0,   189,     0,    17,     0,    19,
     185,     0,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,     0,     0,     0,     0,     0,
       0,     0,     0,   216,     0,     0,     0,   122,   123,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     124,   125,   126,   127,   128,     0,     0,   215,   233,   214,
       0,   191,     0,   188,   212,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    53,     0,     0,     0,    44,    49,     0,    45,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,     0,     0,     0,   217,   218,   219,
     220,     0,   221,   222,   223,   224,   225,     0,     0,     0,
       0,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     203,   204,   205,   206,   207,   208,     0,   210,     0,     0,
       0,   213,     0,   179,     0,   189,    51,    47,     0,     0,
      71,     0,     0,     0,    57,     0,     0,     0,     0,     0,
      82,    83,    84,    86,     0,    87,   189,   189,   217,   218,
     106,   108,    52,    48,    60,    61,    62,    58,    59,     0,
       0,     0,     0,     0,   107,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   181,   189,
       0,     0,     0,     0,   110,   190,     0,    50,    46,    66,
       0,     0,     0,     0,    54,    55,    56,     0,     0,     0,
      81,    80,    85,     0,     0,     0,     0,     0,     0,    95,
     101,   102,   103,   104,   105,    96,    97,    98,   100,    99,
       0,     0,   192,   209,     0,   189,   180,     0,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     189,   182,   240,     0,    72,     0,    74,    93,     0,     0,
       0,    79,    88,    89,     0,     0,   189,     0,   189,     0,
     189,     0,   183,     0,     0,    57,     0,     0,    63,    65,
       0,   188,    68,   188,    70,   188,   184,    73,    75,     0,
      77,     0,     0,     0,     0,     0,     0,    64,    67,    69,
      76,    78
  };

  const short
  parser::yypgoto_[] =
  {
    -422,  -422,  -422,   287,   291,   294,  -422,  -422,  -422,   -72,
      55,  -422,  -422,  -422,  -125,  -163,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,   379,
    -422,  -339,  -338,  -337,  -422,  -422,  -422,  -422,  -422,  -185,
    -168,   -86,   -76,  -422,  -155,  -421,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,  -422,
    -422,  -422,  -422,  -422,  -422,  -422,  -160,  -133,  -422,  -422,
    -120,  -422,  -422,   -45,   134,   144,   222,  -422,  -422,     0,
       8,  -422,   -19,  -422,  -422,  -422,    60,  -422,  -422
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    11,    12,    13,    14,    15,   266,
     267,   338,   268,   269,   270,   403,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   241,
     458,   294,   295,   296,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    32,   480,   243,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   239,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124
  };

  const short
  parser::yytable_[] =
  {
      16,   189,    31,   297,   441,   404,   405,   406,    21,    16,
      26,    19,    20,     1,     2,     3,     4,     5,  -225,    22,
     298,   181,  -225,    30,     6,     6,    33,   126,   299,   237,
     242,   182,   127,   347,   129,   333,    27,   308,    28,    30,
     334,    29,   130,    72,     6,   481,   185,   483,   442,   485,
    -225,   388,   128,  -225,   131,   300,   334,   436,    17,    18,
     297,   125,   334,   153,   297,   132,    34,   133,   301,   134,
       6,    38,    39,    40,    41,   151,   152,   298,  -217,   358,
     358,   298,  -217,   297,   135,   299,   176,   177,   178,   299,
     136,  -225,  -225,    17,    68,     7,   359,   359,   263,   238,
     298,   444,   156,   157,   299,   299,   334,   183,   299,   137,
    -217,   138,   300,  -217,     7,   184,   300,   445,   451,   472,
    -236,   486,   334,   334,   334,   301,   334,   190,   139,   301,
     140,   300,   300,   141,   142,   300,   404,   405,   406,    17,
      68,   143,   144,   302,   360,   361,   145,   146,   301,   147,
     148,  -217,  -217,   297,   149,   187,   158,    34,   188,   358,
     186,     6,    38,    39,    40,    41,   191,   192,   193,   204,
     298,   185,   240,   337,   335,   340,   359,   342,   299,   341,
     396,   343,   344,   345,   299,   350,   244,   346,   306,   263,
     351,   356,   357,   309,   352,   389,   184,   264,   265,   355,
     302,   413,   414,   151,   302,   300,   364,   365,   366,  -218,
     393,   300,   367,  -218,   368,   181,   401,   157,   301,   302,
     302,   410,   411,   302,   407,   182,   415,   416,   417,   418,
      17,    68,   161,   162,   431,   348,   238,   430,   435,   438,
     332,  -218,   450,   440,  -218,   306,   462,   473,   477,   306,
     463,   475,   297,   184,   297,   478,   479,   184,   174,   175,
     176,   177,   178,   482,   306,   306,   398,   334,   306,   298,
     484,   298,   184,   184,   181,   181,   184,   299,   488,   299,
     453,   492,  -218,  -218,   182,   182,   493,   497,   297,   498,
     358,   297,   494,   302,   495,   471,    23,   499,  -219,   302,
      24,   183,  -219,    25,   300,   298,   300,   359,   298,   184,
     297,   297,   489,   299,   349,   299,   299,   301,   461,   301,
       0,   181,   303,   363,     0,     0,     0,   298,   298,     0,
    -219,   182,   304,  -219,     0,   299,   299,     0,   306,     0,
     300,     0,   300,   300,   306,   408,   184,   174,   175,   176,
     177,   178,   184,   301,     0,   407,   301,     0,     0,     0,
     183,   183,   300,   300,     0,   454,     0,   456,   184,   184,
       0,  -219,  -219,     0,     0,   301,   301,     0,     0,   303,
       0,  -220,     0,   303,     0,  -220,    34,     0,     0,   304,
       6,     0,   302,   304,   302,     0,     0,     0,   303,   303,
       0,   487,   303,     0,   490,     0,    73,   183,   304,   304,
     305,     0,   304,  -220,     0,   184,  -220,     0,   179,     0,
       0,   180,     0,   500,   501,     0,     0,     0,   302,     0,
     302,   302,     0,     0,  -221,     0,     0,   306,  -221,   306,
     150,     0,   460,   154,   155,   184,     0,   184,     0,     0,
     302,   302,     0,     0,  -220,  -220,     0,     0,     0,    17,
      68,     0,     0,     0,     0,     0,  -221,   305,     0,  -221,
       0,   305,   303,   306,     0,   306,   306,     0,   303,     0,
       0,   184,   304,   184,   184,     0,   305,   305,   304,     0,
     305,     0,     0,     0,     0,   306,   306,     0,     0,     0,
       0,  -222,     0,   184,   184,  -222,     0,  -221,  -221,     0,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
       0,   205,   206,   207,   208,   209,   210,   211,   212,     0,
     215,     0,     0,  -222,     0,     0,  -222,     0,     0,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   236,  -223,
     305,     0,     0,  -223,     0,     0,   305,     0,  -224,     0,
     307,   303,  -224,   303,  -222,  -222,    34,     0,     0,     0,
       6,   304,     0,   304,     0,     0,     0,     0,     0,     0,
       0,  -223,     0,   328,  -223,     0,     0,     0,     0,     0,
    -224,     0,     0,  -224,     0,     0,     0,   303,   179,   303,
     303,   373,     0,     0,   215,     0,     0,   304,     0,   304,
     304,     0,     0,     0,     0,   339,     0,     0,     0,   303,
     303,     0,  -223,  -223,     0,     0,     0,   354,     0,   304,
     304,  -224,  -224,     0,     0,     0,     0,     0,     0,    17,
      68,     0,     0,   369,   370,     0,   371,   372,     0,   305,
       0,   305,     0,     0,   161,   162,     0,     0,   165,   166,
     167,   168,   169,   170,     0,    34,     0,     0,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,   172,   390,
     174,   175,   176,   177,   178,   305,     0,   305,   305,     0,
       0,     0,     0,     0,     0,   391,     0,   179,     0,   394,
     373,     0,     0,   395,     0,   374,   375,   305,   305,     0,
     400,     0,   402,     0,     0,   409,     0,     0,     0,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    68,
       0,     0,     0,     0,     0,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,     0,   213,     0,     0,
       0,   434,   214,     0,     0,     0,     0,   160,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,     0,     0,     0,   446,   447,   448,   449,     0,     0,
       0,     0,     0,   171,   172,   173,   174,   175,   176,   177,
     178,   245,     0,     0,     0,     0,     0,   455,   246,   457,
     459,   247,   248,     0,   249,   250,   251,   252,     0,   253,
     254,   255,   256,   257,   258,   259,   260,   261,    34,     0,
       0,     0,     6,    38,    39,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   491,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,   262,
     263,     0,     0,   245,     0,     0,     0,     0,   264,   265,
     246,     0,     0,   247,   248,     0,   249,   250,   251,   252,
       0,   253,   254,   255,   256,   257,   258,   259,   260,   261,
      34,     0,     0,     0,     6,    38,    39,    40,    41,     0,
       0,    17,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,   362,   263,   336,     0,     0,     0,     0,     0,   246,
     264,   265,   247,   248,     0,   249,   250,   251,   252,     0,
     253,   254,   255,   256,   257,   258,   259,   260,   261,    34,
       0,     0,     0,     6,    38,    39,    40,    41,     0,     0,
       0,     0,     0,    17,    68,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   188,
       0,   263,   397,     0,     0,     0,     0,     0,   246,   264,
     265,   247,   248,     0,   249,   250,   251,   252,     0,   253,
     254,   255,   256,   257,   258,   259,   260,   261,    34,     0,
       0,     0,     6,    38,    39,    40,    41,     0,     0,     0,
       0,     0,    17,    68,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,     0,
     263,     0,     0,     0,     0,     0,     0,   246,   264,   265,
     247,   248,     0,   249,   250,   251,   252,     0,   253,   254,
     255,   256,   257,   258,   259,   260,   261,    34,     0,     0,
       0,     6,    38,    39,    40,    41,     0,     0,     0,     0,
       0,    17,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   188,     0,   263,
       0,     0,     0,     0,     0,     0,     0,   264,   265,     0,
      34,    35,    36,    37,     6,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,   329,
      17,    68,   235,   152,     0,   160,    63,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,    64,    65,     0,     0,     0,     0,     0,     0,
       0,   171,   172,   173,   174,   175,   176,   177,   178,    66,
       0,     0,    67,    17,    68,    30,    69,    70,    71,    72,
      34,    35,    36,    37,     6,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,     0,
       0,     0,    62,   161,   162,     0,    63,     0,   353,   167,
     168,   169,   170,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,    65,     0,     0,     0,     0,     0,   174,
     175,   176,   177,   178,     0,     0,     0,     0,     0,    66,
       0,     0,    67,    17,    68,    30,    69,    70,    71,    72,
      34,    35,    36,    37,     6,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,   331,
       0,     0,    62,     0,     0,   160,    63,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,    64,    65,     0,     0,     0,     0,     0,     0,
       0,   171,   172,   173,   174,   175,   176,   177,   178,    66,
       0,     0,    67,    17,    68,    30,    69,    70,    71,    72,
      34,    35,    36,    37,     6,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,     0,
      34,     0,   235,     0,     6,     0,    63,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,    65,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,   373,     0,     0,     0,    66,
     374,   375,    67,    17,    68,    30,    69,    70,    71,    72,
       0,     0,     0,     0,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   386,   465,     0,     0,     0,     0,
     466,     0,     0,    17,    68,   160,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   467,
       0,     0,     0,     0,   468,     0,     0,     0,     0,   160,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   171,   172,   173,   174,   175,
     176,   177,   178,   469,     0,     0,     0,     0,   470,     0,
       0,     0,     0,   160,     0,     0,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   311,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   160,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   312,     0,   171,   172,   173,   174,   175,   176,   177,
     178,   160,     0,     0,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   313,     0,   171,   172,   173,
     174,   175,   176,   177,   178,   160,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   314,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   160,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   315,     0,   171,   172,   173,   174,   175,
     176,   177,   178,   160,     0,     0,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   316,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   160,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   317,     0,   171,   172,   173,   174,   175,   176,   177,
     178,   160,     0,     0,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   318,     0,   171,   172,   173,
     174,   175,   176,   177,   178,   160,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   319,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   160,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   320,     0,   171,   172,   173,   174,   175,
     176,   177,   178,   160,     0,     0,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   160,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   322,     0,   171,   172,   173,   174,   175,   176,   177,
     178,   160,     0,     0,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   323,     0,   171,   172,   173,
     174,   175,   176,   177,   178,   160,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   324,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   160,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   325,     0,   171,   172,   173,   174,   175,
     176,   177,   178,   160,     0,     0,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   327,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   160,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   432,     0,   171,   172,   173,   174,   175,   176,   177,
     178,   160,     0,     0,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   433,     0,   171,   172,   173,
     174,   175,   176,   177,   178,   160,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   437,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   160,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   439,     0,   171,   172,   173,   174,   175,
     176,   177,   178,   160,     0,     0,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   443,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   160,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   452,     0,   171,   172,   173,   174,   175,   176,   177,
     178,   160,     0,     0,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   464,     0,   171,   172,   173,
     174,   175,   176,   177,   178,   160,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   474,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   160,
       0,     0,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   476,     0,   171,   172,   173,   174,   175,
     176,   177,   178,   160,     0,     0,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   496,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   160,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   171,   172,   173,   174,   175,   176,   177,
     178,   387,     0,     0,     0,     0,     0,   160,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   171,   172,   173,   174,   175,   176,   177,
     178,   310,     0,     0,     0,     0,   160,     0,     0,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   171,   172,   173,   174,   175,   176,   177,   178,
     326,     0,     0,     0,     0,   160,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   392,
       0,     0,     0,     0,   160,     0,     0,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     171,   172,   173,   174,   175,   176,   177,   178,   330,     0,
     160,     0,     0,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   171,   172,   173,   174,
     175,   176,   177,   178,   159,   160,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   399,
     160,     0,     0,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   171,   172,   173,   174,
     175,   176,   177,   178,   412,   160,     0,     0,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   160,     0,
       0,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,     0,
       0,     0,     0,     0,   171,   172,   173,   174,   175,   176,
     177,   178,   161,   162,     0,   164,   165,   166,   167,   168,
     169,   170,   161,   162,     0,     0,   165,   166,   167,   168,
     169,   170,     0,     0,     0,   171,   172,   173,   174,   175,
     176,   177,   178,     0,     0,   171,   172,   173,   174,   175,
     176,   177,   178,   161,   162,     0,     0,   165,   166,   167,
     168,   169,   170,   161,   162,     0,     0,   165,   166,   167,
     168,   169,   170,     0,     0,     0,     0,   172,   173,   174,
     175,   176,   177,   178,     0,     0,     0,     0,     0,   174,
     175,   176,   177,   178
  };

  const short
  parser::yycheck_[] =
  {
       0,   126,    21,   188,    28,   344,   344,   344,    66,     9,
      66,     3,     4,    11,    12,    13,    14,    15,    38,     0,
     188,   107,    42,   113,    42,    42,    26,    67,   188,    42,
     185,   107,    72,   107,    34,    67,    92,   192,    76,   113,
      72,    76,    34,   117,    42,   466,    66,   468,    72,   470,
      70,    67,    70,    73,    66,   188,    72,    67,   111,   112,
     245,    67,    72,    63,   249,    66,    38,    66,   188,    66,
      42,    43,    44,    45,    46,    70,    71,   245,    38,   264,
     265,   249,    42,   268,    66,   245,   108,   109,   110,   249,
      66,   111,   112,   111,   112,   112,   264,   265,    70,   112,
     268,    67,   116,   117,   264,   265,    72,   107,   268,    66,
      70,    66,   245,    73,   112,   107,   249,    67,    67,    67,
      74,    67,    72,    72,    72,   245,    72,   127,    66,   249,
      66,   264,   265,    66,    66,   268,   475,   475,   475,   111,
     112,    66,    66,   188,   264,   265,    66,    66,   268,    66,
      66,   111,   112,   338,    66,    76,   112,    38,    68,   344,
      74,    42,    43,    44,    45,    46,    70,    66,    74,    67,
     338,    66,    74,   245,    66,    76,   344,   249,   338,    66,
     335,    66,    66,    66,   344,    75,   186,    66,   188,    70,
      76,    66,    66,   193,    76,    66,   188,    78,    79,    76,
     245,   356,   357,    70,   249,   338,    76,    76,    76,    38,
      71,   344,    76,    42,    76,   301,    25,   117,   338,   264,
     265,    75,    75,   268,   344,   301,    66,    66,    66,    66,
     111,   112,    80,    81,   389,   254,   112,    71,    66,    66,
     240,    70,    66,    76,    73,   245,    76,    23,    28,   249,
      76,    76,   437,   245,   439,    76,    76,   249,   106,   107,
     108,   109,   110,    76,   264,   265,   338,    72,   268,   437,
      76,   439,   264,   265,   360,   361,   268,   437,    76,   439,
     435,    67,   111,   112,   360,   361,    67,    76,   473,    76,
     475,   476,    67,   338,    67,   450,     9,    76,    38,   344,
       9,   301,    42,     9,   437,   473,   439,   475,   476,   301,
     495,   496,   475,   473,   254,   475,   476,   437,   443,   439,
      -1,   407,   188,   268,    -1,    -1,    -1,   495,   496,    -1,
      70,   407,   188,    73,    -1,   495,   496,    -1,   338,    -1,
     473,    -1,   475,   476,   344,   345,   338,   106,   107,   108,
     109,   110,   344,   473,    -1,   475,   476,    -1,    -1,    -1,
     360,   361,   495,   496,    -1,   437,    -1,   439,   360,   361,
      -1,   111,   112,    -1,    -1,   495,   496,    -1,    -1,   245,
      -1,    38,    -1,   249,    -1,    42,    38,    -1,    -1,   245,
      42,    -1,   437,   249,   439,    -1,    -1,    -1,   264,   265,
      -1,   473,   268,    -1,   476,    -1,    27,   407,   264,   265,
     188,    -1,   268,    70,    -1,   407,    73,    -1,    70,    -1,
      -1,    73,    -1,   495,   496,    -1,    -1,    -1,   473,    -1,
     475,   476,    -1,    -1,    38,    -1,    -1,   437,    42,   439,
      61,    -1,   442,    64,    65,   437,    -1,   439,    -1,    -1,
     495,   496,    -1,    -1,   111,   112,    -1,    -1,    -1,   111,
     112,    -1,    -1,    -1,    -1,    -1,    70,   245,    -1,    73,
      -1,   249,   338,   473,    -1,   475,   476,    -1,   344,    -1,
      -1,   473,   338,   475,   476,    -1,   264,   265,   344,    -1,
     268,    -1,    -1,    -1,    -1,   495,   496,    -1,    -1,    -1,
      -1,    38,    -1,   495,   496,    42,    -1,   111,   112,    -1,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
      -1,   142,   143,   144,   145,   146,   147,   148,   149,    -1,
     151,    -1,    -1,    70,    -1,    -1,    73,    -1,    -1,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,    38,
     338,    -1,    -1,    42,    -1,    -1,   344,    -1,    38,    -1,
     191,   437,    42,   439,   111,   112,    38,    -1,    -1,    -1,
      42,   437,    -1,   439,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,   214,    73,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    -1,    73,    -1,    -1,    -1,   473,    70,   475,
     476,    73,    -1,    -1,   235,    -1,    -1,   473,    -1,   475,
     476,    -1,    -1,    -1,    -1,   246,    -1,    -1,    -1,   495,
     496,    -1,   111,   112,    -1,    -1,    -1,   258,    -1,   495,
     496,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,   111,
     112,    -1,    -1,    16,    17,    -1,    19,    20,    -1,   437,
      -1,   439,    -1,    -1,    80,    81,    -1,    -1,    84,    85,
      86,    87,    88,    89,    -1,    38,    -1,    -1,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   310,
     106,   107,   108,   109,   110,   473,    -1,   475,   476,    -1,
      -1,    -1,    -1,    -1,    -1,   326,    -1,    70,    -1,   330,
      73,    -1,    -1,   334,    -1,    78,    79,   495,   496,    -1,
     341,    -1,   343,    -1,    -1,   346,    -1,    -1,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,   112,
      -1,    -1,    -1,    -1,    -1,   376,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,    -1,    67,    -1,    -1,
      -1,   392,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,   415,   416,   417,   418,    -1,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    11,    -1,    -1,    -1,    -1,    -1,   438,    18,   440,
     441,    21,    22,    -1,    24,    25,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   477,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    -1,    -1,    11,    -1,    -1,    -1,    -1,    78,    79,
      18,    -1,    -1,    21,    22,    -1,    24,    25,    26,    27,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    42,    43,    44,    45,    46,    -1,
      -1,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    12,    -1,    -1,    -1,    -1,    -1,    18,
      78,    79,    21,    22,    -1,    24,    25,    26,    27,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,   111,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    70,    12,    -1,    -1,    -1,    -1,    -1,    18,    78,
      79,    21,    22,    -1,    24,    25,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    18,    78,    79,
      21,    22,    -1,    24,    25,    26,    27,    -1,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,   111,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    71,
     111,   112,    70,    71,    -1,    77,    74,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,   107,
      -1,    -1,   110,   111,   112,   113,   114,   115,   116,   117,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    80,    81,    -1,    74,    -1,    76,    86,
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    91,    -1,    -1,    -1,    -1,    -1,   106,
     107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,   107,
      -1,    -1,   110,   111,   112,   113,   114,   115,   116,   117,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    71,
      -1,    -1,    70,    -1,    -1,    77,    74,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,   107,
      -1,    -1,   110,   111,   112,   113,   114,   115,   116,   117,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      38,    -1,    70,    -1,    42,    -1,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    73,    -1,    -1,    -1,   107,
      78,    79,   110,   111,   112,   113,   114,   115,   116,   117,
      -1,    -1,    -1,    -1,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,    67,    -1,    -1,    -1,    -1,
      72,    -1,    -1,   111,   112,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    67,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    67,    -1,    -1,    -1,    -1,    72,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    77,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,   103,   104,   105,
     106,   107,   108,   109,   110,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    77,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    77,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,   103,
     104,   105,   106,   107,   108,   109,   110,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    71,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,   107,   108,   109,
     110,    72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   104,   105,   106,   107,   108,   109,   110,
      72,    -1,    -1,    -1,    -1,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,   105,   106,   107,   108,   109,   110,    72,
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
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,
     107,   108,   109,   110,    76,    77,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    77,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   103,   104,   105,   106,   107,   108,   109,   110,    -1,
      -1,    -1,    -1,    -1,   103,   104,   105,   106,   107,   108,
     109,   110,    80,    81,    -1,    83,    84,    85,    86,    87,
      88,    89,    80,    81,    -1,    -1,    84,    85,    86,    87,
      88,    89,    -1,    -1,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    -1,    -1,   103,   104,   105,   106,   107,
     108,   109,   110,    80,    81,    -1,    -1,    84,    85,    86,
      87,    88,    89,    80,    81,    -1,    -1,    84,    85,    86,
      87,    88,    89,    -1,    -1,    -1,    -1,   104,   105,   106,
     107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,   106,
     107,   108,   109,   110
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    11,    12,    13,    14,    15,    42,   112,   128,   129,
     130,   131,   132,   133,   134,   135,   216,   111,   112,   217,
     217,    66,     0,   130,   131,   132,    66,    92,    76,    76,
     113,   219,   180,   216,    38,    39,    40,    41,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    70,    74,    90,    91,   107,   110,   112,   114,
     115,   116,   117,   166,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,    67,    67,    72,    70,   216,
     217,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
     166,    70,    71,   216,   166,   166,   116,   117,   112,    76,
      77,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   103,   104,   105,   106,   107,   108,   109,   110,    70,
      73,   178,   179,   216,   217,    66,    74,    76,    68,   141,
     216,    70,    66,    74,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,    67,   166,   166,   166,   166,   166,
     166,   166,   166,    67,    72,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,    70,   166,    42,   112,   215,
      74,   166,   181,   182,   216,    11,    18,    21,    22,    24,
      25,    26,    27,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    69,    70,    78,    79,   136,   137,   139,   140,
     141,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   168,   169,   170,   176,   177,   203,
     204,   207,   210,   211,   212,   213,   216,   166,   181,   216,
      72,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    72,    67,   166,    71,
      75,    71,   216,    67,    72,    66,    12,   136,   138,   166,
      76,    66,   136,    66,    66,    66,    66,   107,   219,   223,
      75,    76,    76,    76,   166,    76,    66,    66,   176,   177,
     207,   207,    69,   137,    76,    76,    76,    76,    76,    16,
      17,    19,    20,    73,    78,    79,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,    71,    67,    66,
     166,   166,    72,    71,   166,   166,   181,    12,   136,    76,
     166,    25,   166,   142,   168,   169,   170,   207,   216,   166,
      75,    75,    76,   181,   181,    66,    66,    66,    66,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
      71,   181,    67,    67,   166,    66,    67,    67,    66,    67,
      76,    28,    72,    67,    67,    67,   166,   166,   166,   166,
      66,    67,    67,   181,   136,   166,   136,   166,   167,   166,
     216,   141,    76,    76,    67,    67,    72,    67,    72,    67,
      72,   181,    67,    23,    67,    76,    67,    28,    76,    76,
     181,   182,    76,   182,    76,   182,    67,   136,    76,   142,
     136,   166,    67,    67,    67,    67,    67,    76,    76,    76,
     136,   136
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   127,   128,   128,   129,   129,   129,   129,   129,   129,
     130,   131,   132,   132,   132,   132,   132,   133,   134,   135,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   141,   141,   142,   142,   142,   142,   143,   143,
     144,   144,   144,   145,   146,   146,   147,   148,   148,   149,
     149,   150,   151,   152,   153,   154,   155,   156,   156,   157,
     158,   158,   159,   160,   161,   162,   162,   163,   164,   165,
     166,   166,   166,   167,   167,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   169,   169,   170,   170,
     171,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   174,   175,   176,   176,   177,   177,   178,
     178,   178,   178,   179,   179,   180,   180,   180,   181,   181,
     182,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   202,   203,   204,   205,   206,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   216,   217,   217,   218,   219,
     220,   221,   222,   222,   223,   223,   224,   225
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     5,     4,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       3,     2,     3,     2,     1,     1,     1,     0,     2,     2,
       2,     2,     2,     6,     8,     6,     3,     8,     6,     8,
       6,     2,     5,     7,     5,     7,     9,     7,     9,     5,
       3,     3,     2,     2,     2,     3,     2,     2,     5,     5,
       1,     1,     1,     1,     0,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       5,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     2,     2,     4,
       6,     5,     7,     8,     9,     3,     1,     0,     1,     0,
       3,     1,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,     4,     4,     4,     4,     4,     4,     6,
       4,     2,     3,     4,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       7,     1,     2,     1,     2,     1,     1,     1
  };




#if T6DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   285,   285,   286,   290,   292,   294,   296,   298,   300,
     305,   309,   314,   315,   316,   317,   318,   322,   327,   332,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   364,   365,   369,   371,   376,   378,
     383,   384,   388,   389,   393,   395,   397,   400,   404,   406,
     411,   413,   415,   420,   425,   427,   432,   437,   439,   444,
     446,   451,   456,   461,   466,   471,   476,   481,   483,   488,
     493,   495,   500,   505,   510,   515,   517,   522,   527,   532,
     537,   538,   539,   543,   544,   548,   550,   552,   554,   556,
     558,   560,   562,   564,   566,   568,   573,   575,   580,   582,
     587,   592,   594,   596,   598,   600,   602,   604,   606,   608,
     610,   612,   614,   616,   618,   620,   622,   624,   626,   631,
     632,   633,   634,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   667,   668,   669,   670,   671,
     672,   673,   674,   678,   683,   688,   689,   692,   693,   697,
     699,   701,   703,   708,   710,   715,   717,   720,   724,   727,
     731,   733,   738,   743,   748,   753,   758,   763,   768,   773,
     778,   783,   788,   793,   798,   803,   808,   813,   818,   823,
     828,   833,   835,   840,   845,   850,   855,   860,   861,   862,
     863,   864,   865,   866,   867,   868,   872,   877,   882,   887,
     892,   897,   902,   907,   912,   914,   919,   921,   926,   931,
     936,   941,   946,   948,   953,   955,   960,   965
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
#line 5190 "parser.cpp"

#line 969 "parser.ypp"


void xsk::arc::t6::parser::error(const xsk::arc::location& loc, const std::string& msg)
{
    throw xsk::arc::comp_error(loc, msg);
}
