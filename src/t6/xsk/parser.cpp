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
      case symbol_kind::S_expr_identifier_neg: // expr_identifier_neg
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
      case symbol_kind::S_expr_identifier_neg: // expr_identifier_neg
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
      case symbol_kind::S_expr_identifier_neg: // expr_identifier_neg
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
      case symbol_kind::S_expr_identifier_neg: // expr_identifier_neg
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
      case symbol_kind::S_expr_identifier_neg: // expr_identifier_neg
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
#line 288 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < ast::program::ptr > ()); }
#line 2300 "parser.cpp"
    break;

  case 3: // root: %empty
#line 289 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 2306 "parser.cpp"
    break;

  case 4: // program: program inline
#line 294 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 2312 "parser.cpp"
    break;

  case 5: // program: program include
#line 296 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2318 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 298 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2324 "parser.cpp"
    break;

  case 7: // program: inline
#line 300 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 2330 "parser.cpp"
    break;

  case 8: // program: include
#line 302 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2336 "parser.cpp"
    break;

  case 9: // program: declaration
#line 304 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2342 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 308 "parser.ypp"
                                 { lexer.push_header(yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2348 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 313 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2354 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 317 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2360 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 318 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2366 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 319 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2372 "parser.cpp"
    break;

  case 15: // declaration: decl_constant
#line 320 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_constant = std::move(yystack_[0].value.as < ast::decl_constant::ptr > ()); }
#line 2378 "parser.cpp"
    break;

  case 16: // declaration: decl_thread
#line 321 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2384 "parser.cpp"
    break;

  case 17: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 326 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2390 "parser.cpp"
    break;

  case 18: // decl_constant: expr_identifier "=" expr ";"
#line 331 "parser.ypp"
        { yylhs.value.as < ast::decl_constant::ptr > () = std::make_unique<ast::decl_constant>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2396 "parser.cpp"
    break;

  case 19: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 336 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2402 "parser.cpp"
    break;

  case 20: // stmt: stmt_block
#line 340 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2408 "parser.cpp"
    break;

  case 21: // stmt: stmt_call
#line 341 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2414 "parser.cpp"
    break;

  case 22: // stmt: stmt_assign
#line 342 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2420 "parser.cpp"
    break;

  case 23: // stmt: stmt_endon
#line 343 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2426 "parser.cpp"
    break;

  case 24: // stmt: stmt_notify
#line 344 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2432 "parser.cpp"
    break;

  case 25: // stmt: stmt_wait
#line 345 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2438 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittill
#line 346 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2444 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittillmatch
#line 347 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2450 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillframeend
#line 348 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2456 "parser.cpp"
    break;

  case 29: // stmt: stmt_if
#line 349 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2462 "parser.cpp"
    break;

  case 30: // stmt: stmt_ifelse
#line 350 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2468 "parser.cpp"
    break;

  case 31: // stmt: stmt_while
#line 351 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2474 "parser.cpp"
    break;

  case 32: // stmt: stmt_dowhile
#line 352 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2480 "parser.cpp"
    break;

  case 33: // stmt: stmt_for
#line 353 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2486 "parser.cpp"
    break;

  case 34: // stmt: stmt_foreach
#line 354 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2492 "parser.cpp"
    break;

  case 35: // stmt: stmt_switch
#line 355 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2498 "parser.cpp"
    break;

  case 36: // stmt: stmt_case
#line 356 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2504 "parser.cpp"
    break;

  case 37: // stmt: stmt_default
#line 357 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2510 "parser.cpp"
    break;

  case 38: // stmt: stmt_break
#line 358 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2516 "parser.cpp"
    break;

  case 39: // stmt: stmt_continue
#line 359 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2522 "parser.cpp"
    break;

  case 40: // stmt: stmt_return
#line 360 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2528 "parser.cpp"
    break;

  case 41: // stmt: stmt_prof_begin
#line 361 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2534 "parser.cpp"
    break;

  case 42: // stmt: stmt_prof_end
#line 362 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2540 "parser.cpp"
    break;

  case 43: // stmt_or_dev: stmt
#line 366 "parser.ypp"
               { yylhs.value.as < ast::stmt > () = std::move(yystack_[0].value.as < ast::stmt > ()); }
#line 2546 "parser.cpp"
    break;

  case 44: // stmt_or_dev: stmt_dev
#line 367 "parser.ypp"
               { yylhs.value.as < ast::stmt > ().as_dev = std::move(yystack_[0].value.as < ast::stmt_dev::ptr > ()); }
#line 2552 "parser.cpp"
    break;

  case 45: // stmt_list: stmt_list stmt
#line 372 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2558 "parser.cpp"
    break;

  case 46: // stmt_list: stmt
#line 374 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2564 "parser.cpp"
    break;

  case 47: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 379 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2570 "parser.cpp"
    break;

  case 48: // stmt_or_dev_list: stmt_or_dev
#line 381 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2576 "parser.cpp"
    break;

  case 49: // stmt_dev: "/#" stmt_list "#/"
#line 385 "parser.ypp"
                                { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::move(yystack_[1].value.as < ast::stmt_list::ptr > ())); }
#line 2582 "parser.cpp"
    break;

  case 50: // stmt_dev: "/#" "#/"
#line 386 "parser.ypp"
                      { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2588 "parser.cpp"
    break;

  case 51: // stmt_block: "{" stmt_or_dev_list "}"
#line 390 "parser.ypp"
                                     { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2594 "parser.cpp"
    break;

  case 52: // stmt_block: "{" "}"
#line 391 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2600 "parser.cpp"
    break;

  case 53: // stmt_expr: expr_assign
#line 396 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2606 "parser.cpp"
    break;

  case 54: // stmt_expr: expr_increment
#line 398 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2612 "parser.cpp"
    break;

  case 55: // stmt_expr: expr_decrement
#line 400 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2618 "parser.cpp"
    break;

  case 56: // stmt_expr: %empty
#line 402 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2624 "parser.cpp"
    break;

  case 57: // stmt_call: expr_call ";"
#line 407 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2630 "parser.cpp"
    break;

  case 58: // stmt_call: expr_method ";"
#line 409 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2636 "parser.cpp"
    break;

  case 59: // stmt_assign: expr_assign ";"
#line 414 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2642 "parser.cpp"
    break;

  case 60: // stmt_assign: expr_increment ";"
#line 416 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2648 "parser.cpp"
    break;

  case 61: // stmt_assign: expr_decrement ";"
#line 418 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2654 "parser.cpp"
    break;

  case 62: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 423 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2660 "parser.cpp"
    break;

  case 63: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 428 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2666 "parser.cpp"
    break;

  case 64: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 430 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2672 "parser.cpp"
    break;

  case 65: // stmt_wait: "wait" expr ";"
#line 435 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2678 "parser.cpp"
    break;

  case 66: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 440 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2684 "parser.cpp"
    break;

  case 67: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 442 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2690 "parser.cpp"
    break;

  case 68: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 447 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2696 "parser.cpp"
    break;

  case 69: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 449 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2702 "parser.cpp"
    break;

  case 70: // stmt_waittillframeend: "waittillframeend" ";"
#line 454 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2708 "parser.cpp"
    break;

  case 71: // stmt_if: "if" "(" expr ")" stmt
#line 459 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2714 "parser.cpp"
    break;

  case 72: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 464 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2720 "parser.cpp"
    break;

  case 73: // stmt_while: "while" "(" expr ")" stmt
#line 469 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2726 "parser.cpp"
    break;

  case 74: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 474 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2732 "parser.cpp"
    break;

  case 75: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 479 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2738 "parser.cpp"
    break;

  case 76: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 484 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2744 "parser.cpp"
    break;

  case 77: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 486 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2750 "parser.cpp"
    break;

  case 78: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 491 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2756 "parser.cpp"
    break;

  case 79: // stmt_case: "case" expr_integer ":"
#line 496 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2762 "parser.cpp"
    break;

  case 80: // stmt_case: "case" expr_string ":"
#line 498 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2768 "parser.cpp"
    break;

  case 81: // stmt_default: "default" ":"
#line 503 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2774 "parser.cpp"
    break;

  case 82: // stmt_break: "break" ";"
#line 508 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2780 "parser.cpp"
    break;

  case 83: // stmt_continue: "continue" ";"
#line 513 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2786 "parser.cpp"
    break;

  case 84: // stmt_return: "return" expr ";"
#line 518 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2792 "parser.cpp"
    break;

  case 85: // stmt_return: "return" ";"
#line 520 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2798 "parser.cpp"
    break;

  case 86: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 525 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2804 "parser.cpp"
    break;

  case 87: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 530 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2810 "parser.cpp"
    break;

  case 88: // expr: expr_ternary
#line 534 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2816 "parser.cpp"
    break;

  case 89: // expr: expr_binary
#line 535 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2822 "parser.cpp"
    break;

  case 90: // expr: expr_primitive
#line 536 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2828 "parser.cpp"
    break;

  case 91: // expr_or_empty: expr
#line 540 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2834 "parser.cpp"
    break;

  case 92: // expr_or_empty: %empty
#line 541 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2840 "parser.cpp"
    break;

  case 93: // expr_assign: expr_object "=" expr
#line 546 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2846 "parser.cpp"
    break;

  case 94: // expr_assign: expr_object "|=" expr
#line 548 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2852 "parser.cpp"
    break;

  case 95: // expr_assign: expr_object "&=" expr
#line 550 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2858 "parser.cpp"
    break;

  case 96: // expr_assign: expr_object "^=" expr
#line 552 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2864 "parser.cpp"
    break;

  case 97: // expr_assign: expr_object "<<=" expr
#line 554 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2870 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object ">>=" expr
#line 556 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2876 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "+=" expr
#line 558 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2882 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object "-=" expr
#line 560 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2888 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "*=" expr
#line 562 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2894 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "/=" expr
#line 564 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2900 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object "%=" expr
#line 566 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2906 "parser.cpp"
    break;

  case 104: // expr_increment: "++" expr_object
#line 571 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2912 "parser.cpp"
    break;

  case 105: // expr_increment: expr_object "++"
#line 573 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2918 "parser.cpp"
    break;

  case 106: // expr_decrement: "--" expr_object
#line 578 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2924 "parser.cpp"
    break;

  case 107: // expr_decrement: expr_object "--"
#line 580 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2930 "parser.cpp"
    break;

  case 108: // expr_ternary: expr "?" expr ":" expr
#line 585 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2936 "parser.cpp"
    break;

  case 109: // expr_binary: expr "||" expr
#line 590 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2942 "parser.cpp"
    break;

  case 110: // expr_binary: expr "&&" expr
#line 592 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2948 "parser.cpp"
    break;

  case 111: // expr_binary: expr "==" expr
#line 594 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2954 "parser.cpp"
    break;

  case 112: // expr_binary: expr "!=" expr
#line 596 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2960 "parser.cpp"
    break;

  case 113: // expr_binary: expr "<=" expr
#line 598 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2966 "parser.cpp"
    break;

  case 114: // expr_binary: expr ">=" expr
#line 600 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2972 "parser.cpp"
    break;

  case 115: // expr_binary: expr "<" expr
#line 602 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2978 "parser.cpp"
    break;

  case 116: // expr_binary: expr ">" expr
#line 604 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2984 "parser.cpp"
    break;

  case 117: // expr_binary: expr "|" expr
#line 606 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2990 "parser.cpp"
    break;

  case 118: // expr_binary: expr "&" expr
#line 608 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2996 "parser.cpp"
    break;

  case 119: // expr_binary: expr "^" expr
#line 610 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3002 "parser.cpp"
    break;

  case 120: // expr_binary: expr "<<" expr
#line 612 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3008 "parser.cpp"
    break;

  case 121: // expr_binary: expr ">>" expr
#line 614 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3014 "parser.cpp"
    break;

  case 122: // expr_binary: expr "+" expr
#line 616 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3020 "parser.cpp"
    break;

  case 123: // expr_binary: expr "-" expr
#line 618 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3026 "parser.cpp"
    break;

  case 124: // expr_binary: expr "*" expr
#line 620 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3032 "parser.cpp"
    break;

  case 125: // expr_binary: expr "/" expr
#line 622 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3038 "parser.cpp"
    break;

  case 126: // expr_binary: expr "%" expr
#line 624 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3044 "parser.cpp"
    break;

  case 127: // expr_primitive: expr_complement
#line 628 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 3050 "parser.cpp"
    break;

  case 128: // expr_primitive: expr_not
#line 629 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 3056 "parser.cpp"
    break;

  case 129: // expr_primitive: expr_call
#line 630 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3062 "parser.cpp"
    break;

  case 130: // expr_primitive: expr_method
#line 631 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3068 "parser.cpp"
    break;

  case 131: // expr_primitive: expr_getnextarraykey
#line 632 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getnextarraykey::ptr > ()); }
#line 3074 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_getfirstarraykey
#line 633 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getfirstarraykey::ptr > ()); }
#line 3080 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_getdvarcoloralpha
#line 634 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcoloralpha::ptr > ()); }
#line 3086 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_getdvarcolorblue
#line 635 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorblue::ptr > ()); }
#line 3092 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_getdvarcolorgreen
#line 636 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorgreen::ptr > ()); }
#line 3098 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_getdvarcolorred
#line 637 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorred::ptr > ()); }
#line 3104 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_getdvarvector
#line 638 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarvector::ptr > ()); }
#line 3110 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_getdvarfloat
#line 639 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarfloat::ptr > ()); }
#line 3116 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_getdvarint
#line 640 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarint::ptr > ()); }
#line 3122 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_getdvar
#line 641 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvar::ptr > ()); }
#line 3128 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_gettime
#line 642 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_gettime::ptr > ()); }
#line 3134 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_abs
#line 643 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_abs::ptr > ()); }
#line 3140 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_vectortoangles
#line 644 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vectortoangles::ptr > ()); }
#line 3146 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_angleclamp180
#line 645 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_angleclamp180::ptr > ()); }
#line 3152 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_anglestoforward
#line 646 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoforward::ptr > ()); }
#line 3158 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_anglestoright
#line 647 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoright::ptr > ()); }
#line 3164 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_anglestoup
#line 648 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoup::ptr > ()); }
#line 3170 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_vectorscale
#line 649 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vectorscale::ptr > ()); }
#line 3176 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_isdefined
#line 650 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_isdefined::ptr > ()); }
#line 3182 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_reference
#line 651 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 3188 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_array
#line 652 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3194 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_field
#line 653 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3200 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_size
#line 654 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 3206 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_paren
#line 655 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 3212 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_empty_array
#line 656 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 3218 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_undefined
#line 657 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 3224 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_game
#line 658 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3230 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_self
#line 659 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3236 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_anim
#line 660 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3242 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_level
#line 661 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3248 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_animation
#line 662 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 3254 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_identifier_neg
#line 663 "parser.ypp"
                             { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 3260 "parser.cpp"
    break;

  case 163: // expr_primitive: expr_identifier
#line 664 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3266 "parser.cpp"
    break;

  case 164: // expr_primitive: expr_istring
#line 665 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 3272 "parser.cpp"
    break;

  case 165: // expr_primitive: expr_string
#line 666 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 3278 "parser.cpp"
    break;

  case 166: // expr_primitive: expr_vector
#line 667 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 3284 "parser.cpp"
    break;

  case 167: // expr_primitive: expr_hash
#line 668 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_hash::ptr > ()); }
#line 3290 "parser.cpp"
    break;

  case 168: // expr_primitive: expr_float
#line 669 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 3296 "parser.cpp"
    break;

  case 169: // expr_primitive: expr_integer
#line 670 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 3302 "parser.cpp"
    break;

  case 170: // expr_primitive: expr_false
#line 671 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 3308 "parser.cpp"
    break;

  case 171: // expr_primitive: expr_true
#line 672 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 3314 "parser.cpp"
    break;

  case 172: // expr_complement: "~" expr
#line 677 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3320 "parser.cpp"
    break;

  case 173: // expr_not: "!" expr
#line 682 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3326 "parser.cpp"
    break;

  case 174: // expr_call: expr_function
#line 686 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3332 "parser.cpp"
    break;

  case 175: // expr_call: expr_pointer
#line 687 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3338 "parser.cpp"
    break;

  case 176: // expr_method: expr_object expr_function
#line 690 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3344 "parser.cpp"
    break;

  case 177: // expr_method: expr_object expr_pointer
#line 691 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3350 "parser.cpp"
    break;

  case 178: // expr_function: expr_identifier "(" expr_arguments ")"
#line 696 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3356 "parser.cpp"
    break;

  case 179: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 698 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3362 "parser.cpp"
    break;

  case 180: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 700 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3368 "parser.cpp"
    break;

  case 181: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 702 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3374 "parser.cpp"
    break;

  case 182: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 707 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3380 "parser.cpp"
    break;

  case 183: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 709 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3386 "parser.cpp"
    break;

  case 184: // expr_parameters: expr_parameters "," expr_identifier
#line 714 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3392 "parser.cpp"
    break;

  case 185: // expr_parameters: expr_identifier
#line 716 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3398 "parser.cpp"
    break;

  case 186: // expr_parameters: %empty
#line 718 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 3404 "parser.cpp"
    break;

  case 187: // expr_arguments: expr_arguments_no_empty
#line 723 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 3410 "parser.cpp"
    break;

  case 188: // expr_arguments: %empty
#line 725 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3416 "parser.cpp"
    break;

  case 189: // expr_arguments_no_empty: expr_arguments "," expr
#line 730 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3422 "parser.cpp"
    break;

  case 190: // expr_arguments_no_empty: expr
#line 732 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3428 "parser.cpp"
    break;

  case 191: // expr_getnextarraykey: "getnextarraykey" "(" expr "," expr ")"
#line 737 "parser.ypp"
        { yylhs.value.as < ast::expr_getnextarraykey::ptr > () = std::make_unique<ast::expr_getnextarraykey>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3434 "parser.cpp"
    break;

  case 192: // expr_getfirstarraykey: "getfirstarraykey" "(" expr ")"
#line 742 "parser.ypp"
        { yylhs.value.as < ast::expr_getfirstarraykey::ptr > () = std::make_unique<ast::expr_getfirstarraykey>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3440 "parser.cpp"
    break;

  case 193: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr ")"
#line 747 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcoloralpha::ptr > () = std::make_unique<ast::expr_getdvarcoloralpha>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3446 "parser.cpp"
    break;

  case 194: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr ")"
#line 752 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorblue::ptr > () = std::make_unique<ast::expr_getdvarcolorblue>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3452 "parser.cpp"
    break;

  case 195: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr ")"
#line 757 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorgreen::ptr > () = std::make_unique<ast::expr_getdvarcolorgreen>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3458 "parser.cpp"
    break;

  case 196: // expr_getdvarcolorred: "getdvarcolorred" "(" expr ")"
#line 762 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorred::ptr > () = std::make_unique<ast::expr_getdvarcolorred>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3464 "parser.cpp"
    break;

  case 197: // expr_getdvarvector: "getdvarvector" "(" expr ")"
#line 767 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarvector::ptr > () = std::make_unique<ast::expr_getdvarvector>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3470 "parser.cpp"
    break;

  case 198: // expr_getdvarfloat: "getdvarfloat" "(" expr ")"
#line 772 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarfloat::ptr > () = std::make_unique<ast::expr_getdvarfloat>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3476 "parser.cpp"
    break;

  case 199: // expr_getdvarint: "getdvarint" "(" expr ")"
#line 777 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarint::ptr > () = std::make_unique<ast::expr_getdvarint>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3482 "parser.cpp"
    break;

  case 200: // expr_getdvar: "getdvar" "(" expr ")"
#line 782 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvar::ptr > () = std::make_unique<ast::expr_getdvar>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3488 "parser.cpp"
    break;

  case 201: // expr_gettime: "gettime" "(" ")"
#line 787 "parser.ypp"
        { yylhs.value.as < ast::expr_gettime::ptr > () = std::make_unique<ast::expr_gettime>(yylhs.location); }
#line 3494 "parser.cpp"
    break;

  case 202: // expr_abs: "abs" "(" expr ")"
#line 792 "parser.ypp"
        { yylhs.value.as < ast::expr_abs::ptr > () = std::make_unique<ast::expr_abs>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3500 "parser.cpp"
    break;

  case 203: // expr_vectortoangles: "vectortoangles" "(" expr ")"
#line 797 "parser.ypp"
        { yylhs.value.as < ast::expr_vectortoangles::ptr > () = std::make_unique<ast::expr_vectortoangles>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3506 "parser.cpp"
    break;

  case 204: // expr_angleclamp180: "angleclamp180" "(" expr ")"
#line 802 "parser.ypp"
        { yylhs.value.as < ast::expr_angleclamp180::ptr > () = std::make_unique<ast::expr_angleclamp180>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3512 "parser.cpp"
    break;

  case 205: // expr_anglestoforward: "anglestoforward" "(" expr ")"
#line 807 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoforward::ptr > () = std::make_unique<ast::expr_anglestoforward>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3518 "parser.cpp"
    break;

  case 206: // expr_anglestoright: "anglestoright" "(" expr ")"
#line 812 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoright::ptr > () = std::make_unique<ast::expr_anglestoright>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3524 "parser.cpp"
    break;

  case 207: // expr_anglestoup: "anglestoup" "(" expr ")"
#line 817 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoup::ptr > () = std::make_unique<ast::expr_anglestoup>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3530 "parser.cpp"
    break;

  case 208: // expr_vectorscale: "vectorscale" "(" expr "," expr ")"
#line 822 "parser.ypp"
        { yylhs.value.as < ast::expr_vectorscale::ptr > () = std::make_unique<ast::expr_vectorscale>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3536 "parser.cpp"
    break;

  case 209: // expr_isdefined: "isdefined" "(" expr ")"
#line 827 "parser.ypp"
        { yylhs.value.as < ast::expr_isdefined::ptr > () = std::make_unique<ast::expr_isdefined>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3542 "parser.cpp"
    break;

  case 210: // expr_reference: "::" expr_identifier
#line 832 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3548 "parser.cpp"
    break;

  case 211: // expr_reference: expr_path "::" expr_identifier
#line 834 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3554 "parser.cpp"
    break;

  case 212: // expr_array: expr_object "[" expr "]"
#line 839 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3560 "parser.cpp"
    break;

  case 213: // expr_array: expr_getdvarvector "[" expr "]"
#line 841 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_getdvarvector::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3566 "parser.cpp"
    break;

  case 214: // expr_array: expr_vectortoangles "[" expr "]"
#line 843 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_vectortoangles::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3572 "parser.cpp"
    break;

  case 215: // expr_array: expr_angleclamp180 "[" expr "]"
#line 845 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_angleclamp180::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3578 "parser.cpp"
    break;

  case 216: // expr_array: expr_anglestoforward "[" expr "]"
#line 847 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_anglestoforward::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3584 "parser.cpp"
    break;

  case 217: // expr_array: expr_anglestoright "[" expr "]"
#line 849 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_anglestoright::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3590 "parser.cpp"
    break;

  case 218: // expr_array: expr_anglestoup "[" expr "]"
#line 851 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_anglestoup::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3596 "parser.cpp"
    break;

  case 219: // expr_array: expr_vectorscale "[" expr "]"
#line 853 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_vectorscale::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3602 "parser.cpp"
    break;

  case 220: // expr_field: expr_object "." expr_identifier_nosize
#line 858 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3608 "parser.cpp"
    break;

  case 221: // expr_size: expr_object "." "size"
#line 863 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ())); }
#line 3614 "parser.cpp"
    break;

  case 222: // expr_paren: "(" expr ")"
#line 868 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3620 "parser.cpp"
    break;

  case 223: // expr_object: expr_call
#line 872 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3626 "parser.cpp"
    break;

  case 224: // expr_object: expr_method
#line 873 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3632 "parser.cpp"
    break;

  case 225: // expr_object: expr_array
#line 874 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3638 "parser.cpp"
    break;

  case 226: // expr_object: expr_field
#line 875 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3644 "parser.cpp"
    break;

  case 227: // expr_object: expr_game
#line 876 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3650 "parser.cpp"
    break;

  case 228: // expr_object: expr_self
#line 877 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3656 "parser.cpp"
    break;

  case 229: // expr_object: expr_anim
#line 878 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3662 "parser.cpp"
    break;

  case 230: // expr_object: expr_level
#line 879 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3668 "parser.cpp"
    break;

  case 231: // expr_object: expr_identifier
#line 880 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3674 "parser.cpp"
    break;

  case 232: // expr_empty_array: "[" "]"
#line 885 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3680 "parser.cpp"
    break;

  case 233: // expr_undefined: "undefined"
#line 890 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3686 "parser.cpp"
    break;

  case 234: // expr_game: "game"
#line 895 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3692 "parser.cpp"
    break;

  case 235: // expr_self: "self"
#line 900 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3698 "parser.cpp"
    break;

  case 236: // expr_anim: "anim"
#line 905 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3704 "parser.cpp"
    break;

  case 237: // expr_level: "level"
#line 910 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3710 "parser.cpp"
    break;

  case 238: // expr_animation: "%" "identifier"
#line 915 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3716 "parser.cpp"
    break;

  case 239: // expr_identifier_neg: "-" "identifier"
#line 920 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, ast::expr(std::make_unique<ast::expr_integer>(yylhs.location, "0")), ast::expr(std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()))); }
#line 3722 "parser.cpp"
    break;

  case 240: // expr_identifier_nosize: "identifier"
#line 925 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3728 "parser.cpp"
    break;

  case 241: // expr_identifier: "identifier"
#line 930 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3734 "parser.cpp"
    break;

  case 242: // expr_identifier: "size"
#line 932 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, "size"); }
#line 3740 "parser.cpp"
    break;

  case 243: // expr_path: "identifier"
#line 937 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3746 "parser.cpp"
    break;

  case 244: // expr_path: "path"
#line 939 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3752 "parser.cpp"
    break;

  case 245: // expr_istring: "localized string"
#line 944 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3758 "parser.cpp"
    break;

  case 246: // expr_string: "string literal"
#line 949 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3764 "parser.cpp"
    break;

  case 247: // expr_vector: "(" expr "," expr "," expr ")"
#line 954 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3770 "parser.cpp"
    break;

  case 248: // expr_hash: "hash"
#line 959 "parser.ypp"
        { yylhs.value.as < ast::expr_hash::ptr > () = std::make_unique<ast::expr_hash>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3776 "parser.cpp"
    break;

  case 249: // expr_float: "-" "float"
#line 964 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3782 "parser.cpp"
    break;

  case 250: // expr_float: "float"
#line 966 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3788 "parser.cpp"
    break;

  case 251: // expr_integer: "-" "integer"
#line 971 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3794 "parser.cpp"
    break;

  case 252: // expr_integer: "integer"
#line 973 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3800 "parser.cpp"
    break;

  case 253: // expr_false: "false"
#line 978 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3806 "parser.cpp"
    break;

  case 254: // expr_true: "true"
#line 983 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3812 "parser.cpp"
    break;


#line 3816 "parser.cpp"

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
  "return", "prof_begin", "prof_end", "thread", "true", "false",
  "undefined", "size", "game", "self", "anim", "level", "getnextarraykey",
  "getfirstarraykey", "getdvarcoloralpha", "getdvarcolorblue",
  "getdvarcolorgreen", "getdvarcolorred", "getdvarvector", "getdvarfloat",
  "getdvarint", "getdvar", "gettime", "abs", "vectortoangles",
  "angleclamp180", "anglestoforward", "anglestoright", "anglestoup",
  "vectorscale", "isdefined", "(", ")", "{", "}", "[", "]", ",", ".", "::",
  ":", ";", "?", "++", "--", "<<", ">>", "||", "&&", "==", "!=", "<=",
  ">=", "<", ">", "!", "~", "=", "+=", "-=", "*=", "/=", "%=", "|=", "&=",
  "^=", ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/", "%", "path",
  "identifier", "string literal", "localized string", "hash", "float",
  "integer", "SIZEOF", "THEN", "TERN", "NEG", "ANIMREF", "PREINC",
  "PREDEC", "POSTINC", "POSTDEC", "$accept", "root", "program", "inline",
  "include", "declaration", "decl_usingtree", "decl_constant",
  "decl_thread", "stmt", "stmt_or_dev", "stmt_list", "stmt_or_dev_list",
  "stmt_dev", "stmt_block", "stmt_expr", "stmt_call", "stmt_assign",
  "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch",
  "stmt_case", "stmt_default", "stmt_break", "stmt_continue",
  "stmt_return", "stmt_prof_begin", "stmt_prof_end", "expr",
  "expr_or_empty", "expr_assign", "expr_increment", "expr_decrement",
  "expr_ternary", "expr_binary", "expr_primitive", "expr_complement",
  "expr_not", "expr_call", "expr_method", "expr_function", "expr_pointer",
  "expr_parameters", "expr_arguments", "expr_arguments_no_empty",
  "expr_getnextarraykey", "expr_getfirstarraykey",
  "expr_getdvarcoloralpha", "expr_getdvarcolorblue",
  "expr_getdvarcolorgreen", "expr_getdvarcolorred", "expr_getdvarvector",
  "expr_getdvarfloat", "expr_getdvarint", "expr_getdvar", "expr_gettime",
  "expr_abs", "expr_vectortoangles", "expr_angleclamp180",
  "expr_anglestoforward", "expr_anglestoright", "expr_anglestoup",
  "expr_vectorscale", "expr_isdefined", "expr_reference", "expr_array",
  "expr_field", "expr_size", "expr_paren", "expr_object",
  "expr_empty_array", "expr_undefined", "expr_game", "expr_self",
  "expr_anim", "expr_level", "expr_animation", "expr_identifier_neg",
  "expr_identifier_nosize", "expr_identifier", "expr_path", "expr_istring",
  "expr_string", "expr_vector", "expr_hash", "expr_float", "expr_integer",
  "expr_false", "expr_true", YY_NULLPTR
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


  const short parser::yypact_ninf_ = -367;

  const short parser::yytable_ninf_ = -244;

  const short
  parser::yypact_[] =
  {
      18,  -367,  -367,   -74,   -74,   -49,  -367,  -367,    46,    18,
    -367,  -367,  -367,  -367,  -367,  -367,   -47,  -367,  -367,   -25,
      -9,   -50,  -367,  -367,  -367,  -367,   -36,  1610,  -367,  -367,
    -367,     2,   -44,  -367,   -31,  -367,  -367,  -367,  -367,  -367,
    -367,  -367,     9,    33,    35,    38,    39,    44,    47,    49,
      59,    61,    66,    68,    76,    77,    80,    83,    84,    85,
      89,  1610,   -30,   -36,  1610,  1610,   -91,    -5,    86,  -367,
    -367,  -367,  -367,  3220,  -367,  -367,  -367,  -367,  -367,    12,
      36,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,    42,
    -367,  -367,  -367,  -367,  -367,    98,   102,   104,   105,   106,
     107,  -367,  -367,    41,    58,  -367,  -367,   119,  -367,  -367,
     129,   279,   295,   367,  -367,  -367,   -18,   109,  -367,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,   110,    91,   -36,   111,
     114,   113,  1610,  1610,  1610,  1610,  1610,  1610,  1610,  1610,
    1610,  1610,   118,  1610,  1610,  1610,  1610,  1610,  1610,  1610,
    1610,  1295,  1610,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
    -367,  -367,  1610,  1610,  1610,  1610,  1610,  1610,  1610,  1610,
    1610,  1610,  1610,  1610,  1610,  1610,  1610,  1610,  1610,  1610,
    1610,  1610,  1610,  1610,  1610,  1610,  1610,  1610,  1690,   -24,
    -367,  -367,   122,   116,  1610,   -36,  -367,  1028,  -367,  -367,
    1610,  1610,   -36,  3071,  1902,  1936,  1970,  2004,  2038,  2072,
    2106,  2140,  2174,  -367,  2208,  2242,  2276,  2310,  2344,  2378,
    3110,  2412,  -367,  1610,  1446,  3185,    56,    56,  3334,  3344,
    1024,  1024,   128,   128,   128,   128,  3375,   547,  3385,    10,
      10,  -367,  -367,  -367,  1606,  1686,  2792,  2832,  2872,  2912,
    2952,  1450,  2992,  -367,  -367,  -367,   -36,  3303,   -23,  -367,
     127,  1201,  1610,   124,   138,  1407,   139,   141,   144,   147,
     -71,   120,   142,   150,  1530,   151,   157,  -367,   154,  1083,
    1083,  -367,  -367,  1140,  -367,  -367,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,   156,   163,
     166,   167,   169,    42,    98,   102,   104,   105,   106,   107,
    -367,  -367,  1316,  -367,  -367,  -367,  -367,   122,  3032,   -11,
     181,  1610,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,  1610,  -367,  3149,
     123,  1610,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
     127,  -367,  1610,  1610,  -367,  -367,  1262,  3255,  -367,  1610,
     188,  1610,  1770,   -36,  1610,   131,   174,   176,  -367,  -367,
    -367,  -367,  3290,  1610,  1610,  -367,  -367,   380,   380,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,   187,   189,   190,   192,
     149,  -367,  -367,  1610,  1610,  1610,  1610,  1610,  1610,  1610,
    1610,  1610,  1610,  1610,   183,  -367,  1610,  2446,  2480,  1610,
     193,  3303,  3303,   -10,  -367,  -367,  -367,  2514,   194,  2548,
     191,  -367,  -367,  -367,   905,   -13,  2582,  -367,  -367,  -367,
      -2,    -1,  1610,  1610,  1610,  1610,  3303,  3303,  3303,  3303,
    3303,  3303,  3303,  3303,  3303,  3303,  3303,   197,    17,  -367,
    -367,  2616,  1610,  -367,  1407,  1610,  1407,  1610,  1610,   -36,
      91,   196,   199,  2650,  1780,  1824,  1868,  1610,  -367,  -367,
      30,   245,  2684,  -367,  3303,   201,  2718,   250,  -367,  -367,
    -367,   206,   207,  1610,   211,  1610,   215,  1610,    31,  -367,
    1407,   217,  1770,  1407,  1610,  -367,  -367,   224,   230,  -367,
     231,  -367,   232,  -367,  -367,  -367,   234,  -367,  2752,   227,
     228,   235,  1407,  1407,  -367,  -367,  -367,  -367,  -367
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   242,   241,     0,     2,
       7,     8,     9,    14,    15,    16,     0,   244,   243,     0,
       0,     0,     1,     4,     5,     6,   186,     0,    10,    11,
     246,     0,     0,   185,     0,   254,   253,   233,   234,   235,
     236,   237,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   241,   245,
     248,   250,   252,     0,    88,    89,    90,   127,   128,   129,
     130,   174,   175,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,     0,   155,   156,
     157,   158,   159,   160,   161,   162,   163,     0,   164,   165,
     166,   167,   168,   169,   170,   171,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   232,   210,   173,   172,   239,   249,   251,
     238,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,     0,     0,   188,     0,    17,     0,    19,   184,
       0,   188,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,     0,     0,     0,     0,     0,     0,
       0,     0,   222,     0,     0,     0,   120,   121,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   122,
     123,   124,   125,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   221,   240,   220,     0,   190,     0,   187,
     211,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    52,     0,     0,
       0,    43,    48,     0,    44,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,     0,     0,
       0,   223,   224,     0,     0,     0,     0,     0,     0,     0,
     225,   226,     0,   227,   228,   229,   230,   231,     0,     0,
       0,     0,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   202,   203,   204,   205,   206,   207,     0,   209,     0,
       0,     0,   213,   214,   215,   216,   217,   218,   219,   212,
       0,   178,     0,   188,    50,    46,     0,     0,    70,     0,
       0,     0,    56,     0,     0,     0,     0,     0,    81,    82,
      83,    85,     0,   188,   188,   223,   224,   104,   106,    51,
      47,    59,    60,    61,    57,    58,     0,     0,     0,     0,
       0,   105,   107,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   188,     0,     0,     0,
       0,   108,   189,     0,    49,    45,    65,     0,     0,     0,
       0,    53,    54,    55,     0,     0,     0,    80,    79,    84,
       0,     0,     0,     0,     0,     0,    93,    99,   100,   101,
     102,   103,    94,    95,    96,    98,    97,     0,     0,   191,
     208,     0,   188,   179,     0,     0,     0,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   188,   181,   247,
       0,    71,     0,    73,    91,     0,     0,     0,    78,    86,
      87,     0,     0,   188,     0,   188,     0,   188,     0,   182,
       0,     0,    56,     0,     0,    62,    64,     0,   187,    67,
     187,    69,   187,   183,    72,    74,     0,    76,     0,     0,
       0,     0,     0,     0,    63,    66,    68,    75,    77
  };

  const short
  parser::yypgoto_[] =
  {
    -367,  -367,  -367,   290,   296,   303,  -367,  -367,  -367,   -41,
      32,  -367,  -367,  -367,  -126,  -185,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,
    -367,  -367,  -367,  -367,  -367,  -367,  -367,  -367,   406,  -367,
    -366,  -365,  -358,  -367,  -367,  -367,  -367,  -367,  -194,  -189,
    -103,   -94,  -367,  -173,  -340,  -367,  -367,  -367,  -367,  -367,
    -367,  -145,  -367,  -367,  -367,  -367,  -367,  -140,   -65,   -16,
     148,   233,   336,  -367,  -367,   360,   412,  -367,  -367,   421,
    -367,  -367,   462,   509,   525,   657,  -367,  -367,  -367,     0,
       8,  -367,   -19,  -367,  -367,  -367,    48,  -367,  -367
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    11,    12,    13,    14,    15,   281,
     282,   366,   283,   284,   285,   430,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   257,   485,
     308,   309,   310,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    32,   507,   259,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   255,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125
  };

  const short
  parser::yytable_[] =
  {
      16,   198,    31,   311,   190,     6,   431,   432,   312,    16,
       6,    19,    20,   191,   433,   468,    21,   253,    26,  -231,
     157,   258,   127,  -231,   158,   159,    33,   128,   329,     1,
       2,     3,     4,     5,   130,   375,    17,    18,   129,   152,
     153,    30,   131,   361,    27,    72,    22,   194,   362,  -223,
      28,  -231,   313,  -223,  -231,   415,   463,   314,   469,     6,
     362,   362,    30,   154,   471,   472,    29,   311,   126,   362,
     362,   311,   312,  -224,   132,     7,   312,  -224,  -225,    17,
      68,  -223,  -225,   478,  -223,   385,   385,   254,   362,   311,
     386,   386,  -231,  -231,   312,  -226,   499,   513,   133,  -226,
     134,   362,   362,   135,   136,  -224,   160,   192,  -224,   137,
    -225,   181,   138,  -225,   139,   193,   313,   178,   179,   180,
     313,   314,  -223,  -223,   140,   314,   141,  -226,   199,     7,
    -226,   142,   315,   143,   313,   313,   431,   432,   313,   314,
     314,   144,   145,   314,   433,   146,  -224,  -224,   147,   148,
     149,  -225,  -225,   508,   150,   510,    34,   512,   197,  -243,
       6,   176,   177,   178,   179,   180,  -227,   182,  -226,  -226,
    -227,   183,   311,   184,   185,   186,   187,   312,   385,   201,
     200,   316,   195,   386,   213,   196,   202,   194,   188,   256,
     423,   189,   363,   420,   378,   260,   315,   327,  -227,   368,
     315,  -227,   330,   369,   371,   193,   372,   163,   164,   373,
     440,   441,   374,   428,   315,   315,   383,   379,   315,   190,
     365,   313,   384,   152,   370,   380,   314,   313,   191,    17,
      68,   391,   314,   176,   177,   178,   179,   180,   392,  -227,
    -227,   393,   394,   458,   395,   316,   416,   159,   437,   316,
     438,   376,   442,   457,   443,   444,   360,   445,   462,   465,
     254,   327,   477,   316,   316,   327,   467,   316,   500,   193,
     311,   489,   311,   193,   490,   312,   502,   312,   504,   327,
     327,   505,   506,   327,   190,   190,   509,   193,   193,   480,
     511,   193,   515,   191,   191,   362,   519,   520,   521,    23,
     522,   315,   524,   525,   498,    24,   311,   315,   385,   311,
     526,   312,    25,   386,   312,   390,  -228,   516,   377,   313,
    -228,   313,   192,     0,   314,   425,   314,     0,   311,   311,
     193,   190,  -229,   312,   312,     0,  -229,     0,     0,     0,
     191,     0,     0,     0,   488,   317,     0,     0,  -228,     0,
     316,  -228,     0,     0,     0,   313,   316,   313,   313,     0,
     314,     0,   314,   314,  -229,     0,   327,  -229,     0,     0,
       0,     0,   327,   435,   193,     0,     0,   313,   313,     0,
     193,     0,   314,   314,     0,     0,     0,   192,   192,  -228,
    -228,     0,     0,     0,     0,   193,   193,     0,     0,   315,
       0,   315,     0,     0,  -230,  -229,  -229,     0,  -230,   317,
       0,     0,     0,   317,     0,     0,     0,    34,     0,     0,
       0,     6,     0,   481,     0,   483,     0,   317,   317,     0,
     318,   317,     0,    73,   192,   315,  -230,   315,   315,  -230,
       0,     0,   193,     0,     0,     0,     0,     0,   316,   188,
     316,     0,   400,     0,     0,     0,     0,   315,   315,   514,
       0,     0,   517,     0,   327,     0,   327,   151,     0,   487,
     155,   156,   193,     0,   193,     0,     0,  -230,  -230,     0,
       0,   527,   528,     0,   316,     0,   316,   316,     0,     0,
      17,    68,     0,     0,   318,     0,     0,     0,   318,     0,
     327,     0,   327,   327,     0,     0,   316,   316,   193,     0,
     193,   193,   318,   318,   317,     0,   318,     0,     0,     0,
     317,     0,   327,   327,     0,     0,     0,     0,     0,     0,
     193,   193,     0,   319,     0,     0,     0,     0,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,   214,
     215,   216,   217,   218,   219,   220,   221,   320,   224,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   252,     0,     0,   319,     0,   318,
       0,   319,     0,     0,     0,   318,   328,     0,     0,   321,
       0,     0,   317,     0,   317,   319,   319,     0,   322,   319,
       0,   320,     0,     0,     0,   320,   163,   164,     0,   349,
     167,   168,   169,   170,   171,   172,     0,     0,     0,   320,
     320,     0,     0,   320,     0,     0,     0,     0,   317,     0,
     317,   317,   176,   177,   178,   179,   180,   224,     0,   323,
       0,     0,     0,     0,     0,     0,     0,     0,   367,     0,
     317,   317,     0,   321,     0,     0,     0,   321,     0,     0,
     382,     0,   322,     0,     0,     0,   322,     0,     0,     0,
       0,   321,   321,     0,     0,   321,     0,   318,     0,   318,
     387,   388,   319,     0,   322,     0,   324,     0,   319,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   325,   323,     0,     0,   320,   323,     0,     0,
       0,     0,   320,   318,     0,   318,   318,   417,     0,     0,
       0,   323,   323,     0,     0,   323,     0,     0,     0,     0,
       0,     0,     0,   418,     0,   318,   318,   421,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   422,     0,
     324,     0,     0,     0,   324,   427,     0,   429,   321,     0,
     436,     0,     0,     0,   321,     0,   325,   322,   324,   324,
     325,     0,   324,   434,     0,     0,     0,     0,     0,     0,
     319,     0,   319,     0,   325,   325,     0,     0,   325,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
       0,     0,     0,     0,   320,   461,   320,     0,   323,     0,
       0,     0,     0,     0,   323,     0,   319,     0,   319,   319,
       0,     0,     0,     0,     0,     0,     0,     0,   473,   474,
     475,   476,     0,     0,   326,     0,     0,     0,   319,   319,
     320,     0,   320,   320,     0,     0,     0,     0,     0,     0,
       0,   482,     0,   484,   486,   324,   321,     0,   321,     0,
       0,   324,   320,   320,     0,   322,     0,   322,     0,     0,
       0,   325,     0,     0,     0,     0,     0,   325,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     518,     0,   321,     0,   321,   321,     0,     0,   326,     0,
       0,   322,   326,   434,   322,     0,   323,     0,   323,     0,
       0,     0,     0,     0,   321,   321,   326,   326,     0,     0,
     326,     0,    34,   322,   322,     0,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   323,     0,   323,   323,     0,     0,     0,     0,
       0,     0,     0,   324,   188,   324,     0,   400,     0,     0,
       0,     0,   401,   402,   323,   323,     0,     0,     0,   325,
       0,   325,     0,     0,     0,     0,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,     0,     0,   324,
       0,   324,   324,     0,     0,    17,    68,     0,     0,     0,
       0,     0,     0,   326,     0,   325,     0,   325,   325,   326,
       0,   324,   324,     0,     0,     0,     0,     0,     0,   261,
       0,     0,     0,     0,     0,     0,   262,   325,   325,   263,
     264,     0,   265,   266,   267,   268,     0,   269,   270,   271,
     272,   273,   274,   275,   276,    34,     0,     0,     0,     6,
      38,    39,    40,    41,     0,     0,     0,     0,     0,     0,
      48,     0,     0,     0,     0,     0,    54,    55,    56,    57,
      58,    59,     0,     0,     0,   197,   277,   278,     0,     0,
       0,     0,     0,   163,   164,   279,   280,     0,     0,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
      34,   326,     0,   326,     6,    38,    39,    40,    41,   176,
     177,   178,   179,   180,     0,    48,     0,     0,    17,    68,
       0,    54,    55,    56,    57,    58,    59,     0,     0,     0,
       0,   261,   278,     0,     0,     0,     0,   326,   262,   326,
     326,   263,   264,     0,   265,   266,   267,   268,     0,   269,
     270,   271,   272,   273,   274,   275,   276,    34,     0,   326,
     326,     6,    38,    39,    40,    41,     0,     0,     0,     0,
       0,     0,    48,    17,    68,     0,     0,     0,    54,    55,
      56,    57,    58,    59,     0,     0,     0,   197,   389,   278,
       0,     0,     0,   364,     0,     0,     0,   279,   280,   262,
       0,     0,   263,   264,     0,   265,   266,   267,   268,     0,
     269,   270,   271,   272,   273,   274,   275,   276,    34,     0,
       0,     0,     6,    38,    39,    40,    41,     0,     0,     0,
      17,    68,     0,    48,     0,     0,     0,     0,     0,    54,
      55,    56,    57,    58,    59,     0,     0,     0,   197,     0,
     278,     0,     0,     0,   424,     0,     0,     0,   279,   280,
     262,     0,     0,   263,   264,     0,   265,   266,   267,   268,
       0,   269,   270,   271,   272,   273,   274,   275,   276,    34,
       0,     0,     0,     6,    38,    39,    40,    41,     0,     0,
       0,    17,    68,     0,    48,     0,     0,     0,     0,     0,
      54,    55,    56,    57,    58,    59,     0,     0,     0,   197,
       0,   278,   396,   397,     0,   398,   399,     0,     0,   279,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,     0,     0,     0,     6,     0,     0,
       0,   222,     0,     0,     0,     0,   223,     0,     0,     0,
       0,   162,    17,    68,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,   188,     0,     0,   400,     0,
       0,     0,     0,   401,   402,     0,     0,   173,   174,   175,
     176,   177,   178,   179,   180,     0,     0,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,     0,     0,
       0,     0,     0,     0,     0,   262,    17,    68,   263,   264,
       0,   265,   266,   267,   268,     0,   269,   270,   271,   272,
     273,   274,   275,   276,    34,     0,     0,     0,     6,    38,
      39,    40,    41,     0,     0,     0,     0,     0,     0,    48,
       0,     0,     0,     0,     0,    54,    55,    56,    57,    58,
      59,     0,     0,     0,   197,     0,   278,     0,     0,     0,
       0,     0,     0,     0,   279,   280,     0,    34,    35,    36,
      37,     6,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,   350,    17,    68,   251,
     153,     0,   162,    63,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,    64,
      65,     0,     0,     0,     0,     0,     0,     0,   173,   174,
     175,   176,   177,   178,   179,   180,    66,     0,     0,    67,
      17,    68,    30,    69,    70,    71,    72,    34,    35,    36,
      37,     6,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,     0,     0,     0,    62,
       0,     0,     0,    63,     0,   381,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
      65,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,     0,     0,    67,
      17,    68,    30,    69,    70,    71,    72,    34,    35,    36,
      37,     6,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,   352,     0,     0,    62,
       0,     0,   162,    63,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,    64,
      65,     0,     0,     0,     0,     0,     0,     0,   173,   174,
     175,   176,   177,   178,   179,   180,    66,     0,     0,    67,
      17,    68,    30,    69,    70,    71,    72,    34,    35,    36,
      37,     6,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,   353,     0,     0,   251,
       0,     0,   162,    63,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,    64,
      65,     0,     0,     0,     0,     0,     0,     0,   173,   174,
     175,   176,   177,   178,   179,   180,    66,     0,     0,    67,
      17,    68,    30,    69,    70,    71,    72,    34,     0,     0,
       0,     6,    38,    39,    40,    41,     0,     0,     0,     0,
       0,     0,    48,     0,     0,     0,     0,     0,    54,    55,
      56,    57,    58,    59,     0,     0,     0,     0,     0,   278,
       0,     0,     0,     0,     0,     0,   492,   279,   280,     0,
       0,   493,     0,     0,     0,     0,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    68,   173,   174,   175,   176,   177,   178,   179,   180,
     494,     0,     0,     0,     0,   495,     0,     0,     0,     0,
     162,     0,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,   174,   175,   176,
     177,   178,   179,   180,   496,     0,     0,     0,     0,   497,
       0,     0,     0,     0,   162,     0,     0,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   332,     0,
     173,   174,   175,   176,   177,   178,   179,   180,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   333,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   162,     0,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   334,     0,   173,   174,
     175,   176,   177,   178,   179,   180,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     335,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     162,     0,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   336,     0,   173,   174,   175,   176,
     177,   178,   179,   180,   162,     0,     0,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   337,     0,
     173,   174,   175,   176,   177,   178,   179,   180,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   338,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   162,     0,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   339,     0,   173,   174,
     175,   176,   177,   178,   179,   180,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     340,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     162,     0,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   341,     0,   173,   174,   175,   176,
     177,   178,   179,   180,   162,     0,     0,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   342,     0,
     173,   174,   175,   176,   177,   178,   179,   180,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   343,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   162,     0,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   344,     0,   173,   174,
     175,   176,   177,   178,   179,   180,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     345,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     162,     0,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   346,     0,   173,   174,   175,   176,
     177,   178,   179,   180,   162,     0,     0,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   348,     0,
     173,   174,   175,   176,   177,   178,   179,   180,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   459,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   162,     0,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   460,     0,   173,   174,
     175,   176,   177,   178,   179,   180,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     464,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     162,     0,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   466,     0,   173,   174,   175,   176,
     177,   178,   179,   180,   162,     0,     0,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   470,     0,
     173,   174,   175,   176,   177,   178,   179,   180,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   479,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   162,     0,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   491,     0,   173,   174,
     175,   176,   177,   178,   179,   180,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     501,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     162,     0,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   503,     0,   173,   174,   175,   176,
     177,   178,   179,   180,   162,     0,     0,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   523,     0,
     173,   174,   175,   176,   177,   178,   179,   180,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   354,     0,     0,     0,     0,     0,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   355,     0,     0,     0,     0,     0,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   356,     0,     0,     0,     0,     0,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   357,     0,     0,     0,     0,     0,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   358,     0,     0,     0,     0,     0,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   359,     0,     0,     0,     0,     0,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   414,     0,     0,     0,     0,     0,   162,     0,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   173,   174,   175,   176,   177,   178,
     179,   180,   331,     0,     0,     0,     0,   162,     0,     0,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   173,   174,   175,   176,   177,   178,   179,
     180,   347,     0,     0,     0,     0,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     419,     0,     0,     0,     0,   162,     0,     0,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   173,   174,   175,   176,   177,   178,   179,   180,   351,
       0,   162,     0,     0,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   173,   174,   175,
     176,   177,   178,   179,   180,   161,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,   174,   175,   176,   177,   178,   179,   180,
     426,   162,     0,     0,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   173,   174,   175,
     176,   177,   178,   179,   180,   439,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   162,
       0,     0,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
       0,     0,     0,     0,     0,   173,   174,   175,   176,   177,
     178,   179,   180,   163,   164,     0,   166,   167,   168,   169,
     170,   171,   172,   163,   164,     0,     0,   167,   168,   169,
     170,   171,   172,     0,     0,     0,   173,   174,   175,   176,
     177,   178,   179,   180,     0,     0,   173,   174,   175,   176,
     177,   178,   179,   180,   163,   164,     0,     0,   167,   168,
     169,   170,   171,   172,   163,   164,     0,     0,   167,   168,
     169,   170,   171,   172,     0,     0,     0,     0,   174,   175,
     176,   177,   178,   179,   180,     0,     0,     0,   174,     0,
     176,   177,   178,   179,   180
  };

  const short
  parser::yycheck_[] =
  {
       0,   127,    21,   197,   107,    41,   372,   372,   197,     9,
      41,     3,     4,   107,   372,    28,    65,    41,    65,    37,
     111,   194,    66,    41,   115,   116,    26,    71,   201,    11,
      12,    13,    14,    15,    34,   106,   110,   111,    69,    69,
      70,   112,    34,    66,    91,   116,     0,    65,    71,    37,
      75,    69,   197,    41,    72,    66,    66,   197,    71,    41,
      71,    71,   112,    63,    66,    66,    75,   261,    66,    71,
      71,   265,   261,    37,    65,   111,   265,    41,    37,   110,
     111,    69,    41,    66,    72,   279,   280,   111,    71,   283,
     279,   280,   110,   111,   283,    37,    66,    66,    65,    41,
      65,    71,    71,    65,    65,    69,   111,   107,    72,    65,
      69,    69,    65,    72,    65,   107,   261,   107,   108,   109,
     265,   261,   110,   111,    65,   265,    65,    69,   128,   111,
      72,    65,   197,    65,   279,   280,   502,   502,   283,   279,
     280,    65,    65,   283,   502,    65,   110,   111,    65,    65,
      65,   110,   111,   493,    65,   495,    37,   497,    67,    73,
      41,   105,   106,   107,   108,   109,    37,    69,   110,   111,
      41,    69,   366,    69,    69,    69,    69,   366,   372,    65,
      69,   197,    73,   372,    66,    75,    73,    65,    69,    73,
     363,    72,    65,    70,    74,   195,   261,   197,    69,    75,
     265,    72,   202,    65,    65,   197,    65,    79,    80,    65,
     383,   384,    65,    25,   279,   280,    65,    75,   283,   322,
     261,   366,    65,    69,   265,    75,   366,   372,   322,   110,
     111,    75,   372,   105,   106,   107,   108,   109,    75,   110,
     111,    75,    75,   416,    75,   261,    65,   116,    74,   265,
      74,   270,    65,    70,    65,    65,   256,    65,    65,    65,
     111,   261,    65,   279,   280,   265,    75,   283,    23,   261,
     464,    75,   466,   265,    75,   464,    75,   466,    28,   279,
     280,    75,    75,   283,   387,   388,    75,   279,   280,   462,
      75,   283,    75,   387,   388,    71,    66,    66,    66,     9,
      66,   366,    75,    75,   477,     9,   500,   372,   502,   503,
      75,   500,     9,   502,   503,   283,    37,   502,   270,   464,
      41,   466,   322,    -1,   464,   366,   466,    -1,   522,   523,
     322,   434,    37,   522,   523,    -1,    41,    -1,    -1,    -1,
     434,    -1,    -1,    -1,   470,   197,    -1,    -1,    69,    -1,
     366,    72,    -1,    -1,    -1,   500,   372,   502,   503,    -1,
     500,    -1,   502,   503,    69,    -1,   366,    72,    -1,    -1,
      -1,    -1,   372,   373,   366,    -1,    -1,   522,   523,    -1,
     372,    -1,   522,   523,    -1,    -1,    -1,   387,   388,   110,
     111,    -1,    -1,    -1,    -1,   387,   388,    -1,    -1,   464,
      -1,   466,    -1,    -1,    37,   110,   111,    -1,    41,   261,
      -1,    -1,    -1,   265,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    41,    -1,   464,    -1,   466,    -1,   279,   280,    -1,
     197,   283,    -1,    27,   434,   500,    69,   502,   503,    72,
      -1,    -1,   434,    -1,    -1,    -1,    -1,    -1,   464,    69,
     466,    -1,    72,    -1,    -1,    -1,    -1,   522,   523,   500,
      -1,    -1,   503,    -1,   464,    -1,   466,    61,    -1,   469,
      64,    65,   464,    -1,   466,    -1,    -1,   110,   111,    -1,
      -1,   522,   523,    -1,   500,    -1,   502,   503,    -1,    -1,
     110,   111,    -1,    -1,   261,    -1,    -1,    -1,   265,    -1,
     500,    -1,   502,   503,    -1,    -1,   522,   523,   500,    -1,
     502,   503,   279,   280,   366,    -1,   283,    -1,    -1,    -1,
     372,    -1,   522,   523,    -1,    -1,    -1,    -1,    -1,    -1,
     522,   523,    -1,   197,    -1,    -1,    -1,    -1,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,    -1,   143,
     144,   145,   146,   147,   148,   149,   150,   197,   152,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,    -1,    -1,   261,    -1,   366,
      -1,   265,    -1,    -1,    -1,   372,   200,    -1,    -1,   197,
      -1,    -1,   464,    -1,   466,   279,   280,    -1,   197,   283,
      -1,   261,    -1,    -1,    -1,   265,    79,    80,    -1,   223,
      83,    84,    85,    86,    87,    88,    -1,    -1,    -1,   279,
     280,    -1,    -1,   283,    -1,    -1,    -1,    -1,   500,    -1,
     502,   503,   105,   106,   107,   108,   109,   251,    -1,   197,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   262,    -1,
     522,   523,    -1,   261,    -1,    -1,    -1,   265,    -1,    -1,
     274,    -1,   261,    -1,    -1,    -1,   265,    -1,    -1,    -1,
      -1,   279,   280,    -1,    -1,   283,    -1,   464,    -1,   466,
     279,   280,   366,    -1,   283,    -1,   197,    -1,   372,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   197,   261,    -1,    -1,   366,   265,    -1,    -1,
      -1,    -1,   372,   500,    -1,   502,   503,   331,    -1,    -1,
      -1,   279,   280,    -1,    -1,   283,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   347,    -1,   522,   523,   351,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   362,    -1,
     261,    -1,    -1,    -1,   265,   369,    -1,   371,   366,    -1,
     374,    -1,    -1,    -1,   372,    -1,   261,   366,   279,   280,
     265,    -1,   283,   372,    -1,    -1,    -1,    -1,    -1,    -1,
     464,    -1,   466,    -1,   279,   280,    -1,    -1,   283,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
      -1,    -1,    -1,    -1,   464,   419,   466,    -1,   366,    -1,
      -1,    -1,    -1,    -1,   372,    -1,   500,    -1,   502,   503,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   442,   443,
     444,   445,    -1,    -1,   197,    -1,    -1,    -1,   522,   523,
     500,    -1,   502,   503,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   465,    -1,   467,   468,   366,   464,    -1,   466,    -1,
      -1,   372,   522,   523,    -1,   464,    -1,   466,    -1,    -1,
      -1,   366,    -1,    -1,    -1,    -1,    -1,   372,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     504,    -1,   500,    -1,   502,   503,    -1,    -1,   261,    -1,
      -1,   500,   265,   502,   503,    -1,   464,    -1,   466,    -1,
      -1,    -1,    -1,    -1,   522,   523,   279,   280,    -1,    -1,
     283,    -1,    37,   522,   523,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   500,    -1,   502,   503,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   464,    69,   466,    -1,    72,    -1,    -1,
      -1,    -1,    77,    78,   522,   523,    -1,    -1,    -1,   464,
      -1,   466,    -1,    -1,    -1,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,    -1,    -1,   500,
      -1,   502,   503,    -1,    -1,   110,   111,    -1,    -1,    -1,
      -1,    -1,    -1,   366,    -1,   500,    -1,   502,   503,   372,
      -1,   522,   523,    -1,    -1,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    18,   522,   523,    21,
      22,    -1,    24,    25,    26,    27,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      62,    63,    -1,    -1,    -1,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    79,    80,    77,    78,    -1,    -1,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,   464,    -1,   466,    41,    42,    43,    44,    45,   105,
     106,   107,   108,   109,    -1,    52,    -1,    -1,   110,   111,
      -1,    58,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      -1,    11,    69,    -1,    -1,    -1,    -1,   500,    18,   502,
     503,    21,    22,    -1,    24,    25,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,   522,
     523,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    52,   110,   111,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    67,    68,    69,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    77,    78,    18,
      -1,    -1,    21,    22,    -1,    24,    25,    26,    27,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    -1,    -1,    -1,
     110,   111,    -1,    52,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    67,    -1,
      69,    -1,    -1,    -1,    12,    -1,    -1,    -1,    77,    78,
      18,    -1,    -1,    21,    22,    -1,    24,    25,    26,    27,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    -1,    -1,
      -1,   110,   111,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    67,
      -1,    69,    16,    17,    -1,    19,    20,    -1,    -1,    77,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,
      -1,    76,   110,   111,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    69,    -1,    -1,    72,    -1,
      -1,    -1,    -1,    77,    78,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,    -1,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    18,   110,   111,    21,    22,
      -1,    24,    25,    26,    27,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    -1,    -1,    -1,    67,    -1,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    78,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    70,   110,   111,    69,
      70,    -1,    76,    73,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   106,    -1,    -1,   109,
     110,   111,   112,   113,   114,   115,   116,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    73,    -1,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   106,    -1,    -1,   109,
     110,   111,   112,   113,   114,   115,   116,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    70,    -1,    -1,    69,
      -1,    -1,    76,    73,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   106,    -1,    -1,   109,
     110,   111,   112,   113,   114,   115,   116,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    70,    -1,    -1,    69,
      -1,    -1,    76,    73,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   106,    -1,    -1,   109,
     110,   111,   112,   113,   114,   115,   116,    37,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    77,    78,    -1,
      -1,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     110,   111,   102,   103,   104,   105,   106,   107,   108,   109,
      66,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    66,    -1,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    76,    -1,    -1,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      76,    -1,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    76,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      71,    -1,    -1,    -1,    -1,    76,    -1,    -1,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,    74,
      -1,    76,    -1,    -1,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,    75,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
      75,    76,    -1,    -1,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,    75,    76,    -1,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    76,
      -1,    -1,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,    79,    80,    -1,    82,    83,    84,    85,
      86,    87,    88,    79,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,    79,    80,    -1,    -1,    83,    84,
      85,    86,    87,    88,    79,    80,    -1,    -1,    83,    84,
      85,    86,    87,    88,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,   107,   108,   109,    -1,    -1,    -1,   103,    -1,
     105,   106,   107,   108,   109
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    11,    12,    13,    14,    15,    41,   111,   127,   128,
     129,   130,   131,   132,   133,   134,   215,   110,   111,   216,
     216,    65,     0,   129,   130,   131,    65,    91,    75,    75,
     112,   218,   178,   215,    37,    38,    39,    40,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    69,    73,    89,    90,   106,   109,   111,   113,
     114,   115,   116,   164,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,    66,    66,    71,    69,
     215,   216,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,   164,    69,    70,   215,   164,   164,   111,   115,   116,
     111,    75,    76,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,   102,   103,   104,   105,   106,   107,   108,
     109,    69,    69,    69,    69,    69,    69,    69,    69,    72,
     176,   177,   215,   216,    65,    73,    75,    67,   140,   215,
      69,    65,    73,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,    66,   164,   164,   164,   164,   164,   164,
     164,   164,    66,    71,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,    69,   164,    41,   111,   214,    73,   164,   179,   180,
     215,    11,    18,    21,    22,    24,    25,    26,    27,    29,
      30,    31,    32,    33,    34,    35,    36,    68,    69,    77,
      78,   135,   136,   138,   139,   140,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   166,   167,
     168,   174,   175,   187,   193,   194,   195,   196,   197,   198,
     201,   202,   205,   208,   209,   210,   211,   215,   164,   179,
     215,    71,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    71,    66,   164,
      70,    74,    70,    70,    70,    70,    70,    70,    70,    70,
     215,    66,    71,    65,    12,   135,   137,   164,    75,    65,
     135,    65,    65,    65,    65,   106,   218,   222,    74,    75,
      75,    75,   164,    65,    65,   174,   175,   205,   205,    68,
     136,    75,    75,    75,    75,    75,    16,    17,    19,    20,
      72,    77,    78,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,    70,    66,    65,   164,   164,    71,
      70,   164,   164,   179,    12,   135,    75,   164,    25,   164,
     141,   166,   167,   168,   205,   215,   164,    74,    74,    75,
     179,   179,    65,    65,    65,    65,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,    70,   179,    66,
      66,   164,    65,    66,    66,    65,    66,    75,    28,    71,
      66,    66,    66,   164,   164,   164,   164,    65,    66,    66,
     179,   135,   164,   135,   164,   165,   164,   215,   140,    75,
      75,    66,    66,    71,    66,    71,    66,    71,   179,    66,
      23,    66,    75,    66,    28,    75,    75,   179,   180,    75,
     180,    75,   180,    66,   135,    75,   141,   135,   164,    66,
      66,    66,    66,    66,    75,    75,    75,   135,   135
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   126,   127,   127,   128,   128,   128,   128,   128,   128,
     129,   130,   131,   131,   131,   131,   131,   132,   133,   134,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   136,   136,   137,   137,   138,   138,   139,
     139,   140,   140,   141,   141,   141,   141,   142,   142,   143,
     143,   143,   144,   145,   145,   146,   147,   147,   148,   148,
     149,   150,   151,   152,   153,   154,   155,   155,   156,   157,
     157,   158,   159,   160,   161,   161,   162,   163,   164,   164,
     164,   165,   165,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   167,   167,   168,   168,   169,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   172,   173,   174,   174,   175,   175,   176,   176,
     176,   176,   177,   177,   178,   178,   178,   179,   179,   180,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   200,   201,   201,   201,   201,   201,   201,   201,   201,
     202,   203,   204,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   215,   216,   216,   217,   218,   219,   220,   221,
     221,   222,   222,   223,   224
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     5,     4,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     3,
       2,     3,     2,     1,     1,     1,     0,     2,     2,     2,
       2,     2,     6,     8,     6,     3,     8,     6,     8,     6,
       2,     5,     7,     5,     7,     9,     7,     9,     5,     3,
       3,     2,     2,     2,     3,     2,     5,     5,     1,     1,
       1,     1,     0,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     2,     2,     4,     6,
       5,     7,     8,     9,     3,     1,     0,     1,     0,     3,
       1,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,     4,     4,     4,     4,     4,     4,     6,     4,
       2,     3,     4,     4,     4,     4,     4,     4,     4,     4,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     7,     1,     2,
       1,     2,     1,     1,     1
  };




#if T6DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   288,   288,   289,   293,   295,   297,   299,   301,   303,
     308,   312,   317,   318,   319,   320,   321,   325,   330,   335,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   366,   367,   371,   373,   378,   380,   385,
     386,   390,   391,   395,   397,   399,   402,   406,   408,   413,
     415,   417,   422,   427,   429,   434,   439,   441,   446,   448,
     453,   458,   463,   468,   473,   478,   483,   485,   490,   495,
     497,   502,   507,   512,   517,   519,   524,   529,   534,   535,
     536,   540,   541,   545,   547,   549,   551,   553,   555,   557,
     559,   561,   563,   565,   570,   572,   577,   579,   584,   589,
     591,   593,   595,   597,   599,   601,   603,   605,   607,   609,
     611,   613,   615,   617,   619,   621,   623,   628,   629,   630,
     631,   632,   633,   634,   635,   636,   637,   638,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   670,
     671,   672,   676,   681,   686,   687,   690,   691,   695,   697,
     699,   701,   706,   708,   713,   715,   718,   722,   725,   729,
     731,   736,   741,   746,   751,   756,   761,   766,   771,   776,
     781,   786,   791,   796,   801,   806,   811,   816,   821,   826,
     831,   833,   838,   840,   842,   844,   846,   848,   850,   852,
     857,   862,   867,   872,   873,   874,   875,   876,   877,   878,
     879,   880,   884,   889,   894,   899,   904,   909,   914,   919,
     924,   929,   931,   936,   938,   943,   948,   953,   958,   963,
     965,   970,   972,   977,   982
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
#line 5356 "parser.cpp"

#line 986 "parser.ypp"


void xsk::arc::t6::parser::error(const xsk::arc::location& loc, const std::string& msg)
{
    throw xsk::arc::comp_error(loc, msg);
}
