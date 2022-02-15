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
using namespace xsk::gsc;
xsk::gsc::s1::parser::symbol_type S1lex(xsk::gsc::s1::lexer& lexer);

#line 47 "parser.cpp"

// Take the name prefix into account.
#define yylex   S1lex



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
#if S1DEBUG

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

#else // !S1DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !S1DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace gsc { namespace s1 {
#line 149 "parser.cpp"

  /// Build a parser object.
  parser::parser (xsk::gsc::s1::lexer& lexer_yyarg, xsk::gsc::ast::program::ptr& ast_yyarg)
#if S1DEBUG
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

      case symbol_kind::S_expr_add_array: // expr_add_array
        value.YY_MOVE_OR_COPY< ast::expr_add_array::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr_color: // expr_color
        value.YY_MOVE_OR_COPY< ast::expr_color::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr_identifier: // expr_identifier
        value.YY_MOVE_OR_COPY< ast::expr_identifier::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.YY_MOVE_OR_COPY< ast::expr_integer::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.YY_MOVE_OR_COPY< ast::expr_thisthread::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.YY_MOVE_OR_COPY< ast::stmt_waitframe::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_FIELD: // "field"
      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_COLOR: // "color"
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

      case symbol_kind::S_expr_add_array: // expr_add_array
        value.move< ast::expr_add_array::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr_color: // expr_color
        value.move< ast::expr_color::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr_identifier: // expr_identifier
        value.move< ast::expr_identifier::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.move< ast::expr_integer::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.move< ast::expr_thisthread::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< ast::stmt_waitframe::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_FIELD: // "field"
      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_COLOR: // "color"
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

      case symbol_kind::S_expr_add_array: // expr_add_array
        value.copy< ast::expr_add_array::ptr > (that.value);
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

      case symbol_kind::S_expr_color: // expr_color
        value.copy< ast::expr_color::ptr > (that.value);
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

      case symbol_kind::S_expr_identifier: // expr_identifier
        value.copy< ast::expr_identifier::ptr > (that.value);
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.copy< ast::expr_integer::ptr > (that.value);
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.copy< ast::expr_thisthread::ptr > (that.value);
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.copy< ast::stmt_waitframe::ptr > (that.value);
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

      case symbol_kind::S_FIELD: // "field"
      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_COLOR: // "color"
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

      case symbol_kind::S_expr_add_array: // expr_add_array
        value.move< ast::expr_add_array::ptr > (that.value);
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

      case symbol_kind::S_expr_color: // expr_color
        value.move< ast::expr_color::ptr > (that.value);
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

      case symbol_kind::S_expr_identifier: // expr_identifier
        value.move< ast::expr_identifier::ptr > (that.value);
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.move< ast::expr_integer::ptr > (that.value);
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.move< ast::expr_thisthread::ptr > (that.value);
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< ast::stmt_waitframe::ptr > (that.value);
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

      case symbol_kind::S_FIELD: // "field"
      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_COLOR: // "color"
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

#if S1DEBUG
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

#if S1DEBUG
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
#endif // S1DEBUG

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

      case symbol_kind::S_expr_add_array: // expr_add_array
        yylhs.value.emplace< ast::expr_add_array::ptr > ();
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

      case symbol_kind::S_expr_color: // expr_color
        yylhs.value.emplace< ast::expr_color::ptr > ();
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

      case symbol_kind::S_expr_identifier: // expr_identifier
        yylhs.value.emplace< ast::expr_identifier::ptr > ();
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        yylhs.value.emplace< ast::expr_integer::ptr > ();
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        yylhs.value.emplace< ast::expr_thisthread::ptr > ();
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        yylhs.value.emplace< ast::stmt_waitframe::ptr > ();
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

      case symbol_kind::S_FIELD: // "field"
      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_COLOR: // "color"
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
#line 256 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < ast::program::ptr > ()); }
#line 2015 "parser.cpp"
    break;

  case 3: // root: %empty
#line 257 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 2021 "parser.cpp"
    break;

  case 4: // program: program inline
#line 262 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 2027 "parser.cpp"
    break;

  case 5: // program: program include
#line 264 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2033 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 266 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2039 "parser.cpp"
    break;

  case 7: // program: inline
#line 268 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 2045 "parser.cpp"
    break;

  case 8: // program: include
#line 270 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2051 "parser.cpp"
    break;

  case 9: // program: declaration
#line 272 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2057 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 276 "parser.ypp"
                                 { lexer.push_header(yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2063 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 281 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2069 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 285 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2075 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 286 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2081 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 287 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2087 "parser.cpp"
    break;

  case 15: // declaration: decl_constant
#line 288 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_constant = std::move(yystack_[0].value.as < ast::decl_constant::ptr > ()); }
#line 2093 "parser.cpp"
    break;

  case 16: // declaration: decl_thread
#line 289 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2099 "parser.cpp"
    break;

  case 17: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 294 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2105 "parser.cpp"
    break;

  case 18: // decl_constant: expr_identifier "=" expr ";"
#line 299 "parser.ypp"
        { yylhs.value.as < ast::decl_constant::ptr > () = std::make_unique<ast::decl_constant>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2111 "parser.cpp"
    break;

  case 19: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 304 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2117 "parser.cpp"
    break;

  case 20: // stmt: stmt_block
#line 308 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2123 "parser.cpp"
    break;

  case 21: // stmt: stmt_call
#line 309 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2129 "parser.cpp"
    break;

  case 22: // stmt: stmt_assign
#line 310 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2135 "parser.cpp"
    break;

  case 23: // stmt: stmt_endon
#line 311 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2141 "parser.cpp"
    break;

  case 24: // stmt: stmt_notify
#line 312 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2147 "parser.cpp"
    break;

  case 25: // stmt: stmt_wait
#line 313 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2153 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittill
#line 314 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2159 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittillmatch
#line 315 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2165 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillframeend
#line 316 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2171 "parser.cpp"
    break;

  case 29: // stmt: stmt_waitframe
#line 317 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waitframe = std::move(yystack_[0].value.as < ast::stmt_waitframe::ptr > ()); }
#line 2177 "parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 318 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2183 "parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 319 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2189 "parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 320 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2195 "parser.cpp"
    break;

  case 33: // stmt: stmt_dowhile
#line 321 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2201 "parser.cpp"
    break;

  case 34: // stmt: stmt_for
#line 322 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2207 "parser.cpp"
    break;

  case 35: // stmt: stmt_foreach
#line 323 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2213 "parser.cpp"
    break;

  case 36: // stmt: stmt_switch
#line 324 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2219 "parser.cpp"
    break;

  case 37: // stmt: stmt_case
#line 325 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2225 "parser.cpp"
    break;

  case 38: // stmt: stmt_default
#line 326 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2231 "parser.cpp"
    break;

  case 39: // stmt: stmt_break
#line 327 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2237 "parser.cpp"
    break;

  case 40: // stmt: stmt_continue
#line 328 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2243 "parser.cpp"
    break;

  case 41: // stmt: stmt_return
#line 329 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2249 "parser.cpp"
    break;

  case 42: // stmt: stmt_breakpoint
#line 330 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_breakpoint = std::move(yystack_[0].value.as < ast::stmt_breakpoint::ptr > ()); }
#line 2255 "parser.cpp"
    break;

  case 43: // stmt: stmt_prof_begin
#line 331 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2261 "parser.cpp"
    break;

  case 44: // stmt: stmt_prof_end
#line 332 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2267 "parser.cpp"
    break;

  case 45: // stmt_or_dev: stmt
#line 336 "parser.ypp"
               { yylhs.value.as < ast::stmt > () = std::move(yystack_[0].value.as < ast::stmt > ()); }
#line 2273 "parser.cpp"
    break;

  case 46: // stmt_or_dev: stmt_dev
#line 337 "parser.ypp"
               { yylhs.value.as < ast::stmt > ().as_dev = std::move(yystack_[0].value.as < ast::stmt_dev::ptr > ()); }
#line 2279 "parser.cpp"
    break;

  case 47: // stmt_list: stmt_list stmt
#line 342 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2285 "parser.cpp"
    break;

  case 48: // stmt_list: stmt
#line 344 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2291 "parser.cpp"
    break;

  case 49: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 349 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2297 "parser.cpp"
    break;

  case 50: // stmt_or_dev_list: stmt_or_dev
#line 351 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2303 "parser.cpp"
    break;

  case 51: // stmt_dev: "/#" stmt_list "#/"
#line 355 "parser.ypp"
                                { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::move(yystack_[1].value.as < ast::stmt_list::ptr > ())); }
#line 2309 "parser.cpp"
    break;

  case 52: // stmt_dev: "/#" "#/"
#line 356 "parser.ypp"
                      { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2315 "parser.cpp"
    break;

  case 53: // stmt_block: "{" stmt_or_dev_list "}"
#line 360 "parser.ypp"
                                     { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2321 "parser.cpp"
    break;

  case 54: // stmt_block: "{" "}"
#line 361 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2327 "parser.cpp"
    break;

  case 55: // stmt_expr: expr_assign
#line 366 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2333 "parser.cpp"
    break;

  case 56: // stmt_expr: expr_increment
#line 368 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2339 "parser.cpp"
    break;

  case 57: // stmt_expr: expr_decrement
#line 370 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2345 "parser.cpp"
    break;

  case 58: // stmt_expr: %empty
#line 372 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2351 "parser.cpp"
    break;

  case 59: // stmt_call: expr_call ";"
#line 377 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2357 "parser.cpp"
    break;

  case 60: // stmt_call: expr_method ";"
#line 379 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2363 "parser.cpp"
    break;

  case 61: // stmt_assign: expr_assign ";"
#line 384 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2369 "parser.cpp"
    break;

  case 62: // stmt_assign: expr_increment ";"
#line 386 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2375 "parser.cpp"
    break;

  case 63: // stmt_assign: expr_decrement ";"
#line 388 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2381 "parser.cpp"
    break;

  case 64: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 393 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2387 "parser.cpp"
    break;

  case 65: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 398 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2393 "parser.cpp"
    break;

  case 66: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 400 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2399 "parser.cpp"
    break;

  case 67: // stmt_wait: "wait" expr ";"
#line 405 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2405 "parser.cpp"
    break;

  case 68: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 410 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2411 "parser.cpp"
    break;

  case 69: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 412 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2417 "parser.cpp"
    break;

  case 70: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 417 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2423 "parser.cpp"
    break;

  case 71: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 419 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2429 "parser.cpp"
    break;

  case 72: // stmt_waittillframeend: "waittillframeend" ";"
#line 424 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2435 "parser.cpp"
    break;

  case 73: // stmt_waitframe: "waitframe" ";"
#line 429 "parser.ypp"
        { yylhs.value.as < ast::stmt_waitframe::ptr > () = std::make_unique<ast::stmt_waitframe>(yylhs.location); }
#line 2441 "parser.cpp"
    break;

  case 74: // stmt_waitframe: "waitframe" "(" ")" ";"
#line 431 "parser.ypp"
        { yylhs.value.as < ast::stmt_waitframe::ptr > () = std::make_unique<ast::stmt_waitframe>(yylhs.location); }
#line 2447 "parser.cpp"
    break;

  case 75: // stmt_if: "if" "(" expr ")" stmt
#line 436 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2453 "parser.cpp"
    break;

  case 76: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 441 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2459 "parser.cpp"
    break;

  case 77: // stmt_while: "while" "(" expr ")" stmt
#line 446 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2465 "parser.cpp"
    break;

  case 78: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 451 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2471 "parser.cpp"
    break;

  case 79: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 456 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2477 "parser.cpp"
    break;

  case 80: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 461 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2483 "parser.cpp"
    break;

  case 81: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 463 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2489 "parser.cpp"
    break;

  case 82: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 468 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2495 "parser.cpp"
    break;

  case 83: // stmt_case: "case" expr_integer ":"
#line 473 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2501 "parser.cpp"
    break;

  case 84: // stmt_case: "case" expr_string ":"
#line 475 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2507 "parser.cpp"
    break;

  case 85: // stmt_default: "default" ":"
#line 480 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2513 "parser.cpp"
    break;

  case 86: // stmt_break: "break" ";"
#line 485 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2519 "parser.cpp"
    break;

  case 87: // stmt_continue: "continue" ";"
#line 490 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2525 "parser.cpp"
    break;

  case 88: // stmt_return: "return" expr ";"
#line 495 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2531 "parser.cpp"
    break;

  case 89: // stmt_return: "return" ";"
#line 497 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2537 "parser.cpp"
    break;

  case 90: // stmt_breakpoint: "breakpoint" ";"
#line 502 "parser.ypp"
        { yylhs.value.as < ast::stmt_breakpoint::ptr > () = std::make_unique<ast::stmt_breakpoint>(yylhs.location); }
#line 2543 "parser.cpp"
    break;

  case 91: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 507 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2549 "parser.cpp"
    break;

  case 92: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 512 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2555 "parser.cpp"
    break;

  case 93: // expr: expr_ternary
#line 516 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2561 "parser.cpp"
    break;

  case 94: // expr: expr_binary
#line 517 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2567 "parser.cpp"
    break;

  case 95: // expr: expr_primitive
#line 518 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2573 "parser.cpp"
    break;

  case 96: // expr_or_empty: expr
#line 522 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2579 "parser.cpp"
    break;

  case 97: // expr_or_empty: %empty
#line 523 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2585 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object "=" expr
#line 528 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2591 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "|=" expr
#line 530 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2597 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object "&=" expr
#line 532 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2603 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "^=" expr
#line 534 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2609 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "<<=" expr
#line 536 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2615 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object ">>=" expr
#line 538 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2621 "parser.cpp"
    break;

  case 104: // expr_assign: expr_object "+=" expr
#line 540 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2627 "parser.cpp"
    break;

  case 105: // expr_assign: expr_object "-=" expr
#line 542 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2633 "parser.cpp"
    break;

  case 106: // expr_assign: expr_object "*=" expr
#line 544 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2639 "parser.cpp"
    break;

  case 107: // expr_assign: expr_object "/=" expr
#line 546 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2645 "parser.cpp"
    break;

  case 108: // expr_assign: expr_object "%=" expr
#line 548 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2651 "parser.cpp"
    break;

  case 109: // expr_increment: "++" expr_object
#line 553 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2657 "parser.cpp"
    break;

  case 110: // expr_increment: expr_object "++"
#line 555 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2663 "parser.cpp"
    break;

  case 111: // expr_decrement: "--" expr_object
#line 560 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2669 "parser.cpp"
    break;

  case 112: // expr_decrement: expr_object "--"
#line 562 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2675 "parser.cpp"
    break;

  case 113: // expr_ternary: expr "?" expr ":" expr
#line 567 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2681 "parser.cpp"
    break;

  case 114: // expr_binary: expr "||" expr
#line 572 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2687 "parser.cpp"
    break;

  case 115: // expr_binary: expr "&&" expr
#line 574 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2693 "parser.cpp"
    break;

  case 116: // expr_binary: expr "==" expr
#line 576 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2699 "parser.cpp"
    break;

  case 117: // expr_binary: expr "!=" expr
#line 578 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2705 "parser.cpp"
    break;

  case 118: // expr_binary: expr "<=" expr
#line 580 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2711 "parser.cpp"
    break;

  case 119: // expr_binary: expr ">=" expr
#line 582 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2717 "parser.cpp"
    break;

  case 120: // expr_binary: expr "<" expr
#line 584 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2723 "parser.cpp"
    break;

  case 121: // expr_binary: expr ">" expr
#line 586 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2729 "parser.cpp"
    break;

  case 122: // expr_binary: expr "|" expr
#line 588 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2735 "parser.cpp"
    break;

  case 123: // expr_binary: expr "&" expr
#line 590 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2741 "parser.cpp"
    break;

  case 124: // expr_binary: expr "^" expr
#line 592 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2747 "parser.cpp"
    break;

  case 125: // expr_binary: expr "<<" expr
#line 594 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2753 "parser.cpp"
    break;

  case 126: // expr_binary: expr ">>" expr
#line 596 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2759 "parser.cpp"
    break;

  case 127: // expr_binary: expr "+" expr
#line 598 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2765 "parser.cpp"
    break;

  case 128: // expr_binary: expr "-" expr
#line 600 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2771 "parser.cpp"
    break;

  case 129: // expr_binary: expr "*" expr
#line 602 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2777 "parser.cpp"
    break;

  case 130: // expr_binary: expr "/" expr
#line 604 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2783 "parser.cpp"
    break;

  case 131: // expr_binary: expr "%" expr
#line 606 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2789 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_complement
#line 610 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 2795 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_not
#line 611 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 2801 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_call
#line 612 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 2807 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_method
#line 613 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 2813 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_add_array
#line 614 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_add_array::ptr > ()); }
#line 2819 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_reference
#line 615 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 2825 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_array
#line 616 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 2831 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_field
#line 617 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 2837 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_size
#line 618 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 2843 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_paren
#line 619 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 2849 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_thisthread
#line 620 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_thisthread::ptr > ()); }
#line 2855 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_empty_array
#line 621 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 2861 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_undefined
#line 622 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 2867 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_game
#line 623 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 2873 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_self
#line 624 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 2879 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_anim
#line 625 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 2885 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_level
#line 626 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 2891 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_animation
#line 627 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 2897 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_animtree
#line 628 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animtree::ptr > ()); }
#line 2903 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_identifier
#line 629 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 2909 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_istring
#line 630 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 2915 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_string
#line 631 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 2921 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_color
#line 632 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_color::ptr > ()); }
#line 2927 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_vector
#line 633 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 2933 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_float
#line 634 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 2939 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_integer
#line 635 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 2945 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_false
#line 636 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 2951 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_true
#line 637 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 2957 "parser.cpp"
    break;

  case 160: // expr_complement: "~" expr
#line 642 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2963 "parser.cpp"
    break;

  case 161: // expr_not: "!" expr
#line 647 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2969 "parser.cpp"
    break;

  case 162: // expr_call: expr_function
#line 651 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2975 "parser.cpp"
    break;

  case 163: // expr_call: expr_pointer
#line 652 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2981 "parser.cpp"
    break;

  case 164: // expr_method: expr_object expr_function
#line 655 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 2987 "parser.cpp"
    break;

  case 165: // expr_method: expr_object expr_pointer
#line 656 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 2993 "parser.cpp"
    break;

  case 166: // expr_function: expr_identifier "(" expr_arguments ")"
#line 661 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 2999 "parser.cpp"
    break;

  case 167: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 663 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3005 "parser.cpp"
    break;

  case 168: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 665 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3011 "parser.cpp"
    break;

  case 169: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 667 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3017 "parser.cpp"
    break;

  case 170: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 669 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3023 "parser.cpp"
    break;

  case 171: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 671 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3029 "parser.cpp"
    break;

  case 172: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 676 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3035 "parser.cpp"
    break;

  case 173: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 678 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3041 "parser.cpp"
    break;

  case 174: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 680 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3047 "parser.cpp"
    break;

  case 175: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 682 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::builtin); }
#line 3053 "parser.cpp"
    break;

  case 176: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 687 "parser.ypp"
        { yylhs.value.as < ast::expr_add_array::ptr > () = std::make_unique<ast::expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ())); }
#line 3059 "parser.cpp"
    break;

  case 177: // expr_parameters: expr_parameters "," expr_identifier
#line 692 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3065 "parser.cpp"
    break;

  case 178: // expr_parameters: expr_identifier
#line 694 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3071 "parser.cpp"
    break;

  case 179: // expr_parameters: %empty
#line 696 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 3077 "parser.cpp"
    break;

  case 180: // expr_arguments: expr_arguments_no_empty
#line 701 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 3083 "parser.cpp"
    break;

  case 181: // expr_arguments: %empty
#line 703 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3089 "parser.cpp"
    break;

  case 182: // expr_arguments_no_empty: expr_arguments "," expr
#line 708 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3095 "parser.cpp"
    break;

  case 183: // expr_arguments_no_empty: expr
#line 710 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3101 "parser.cpp"
    break;

  case 184: // expr_reference: "::" expr_identifier
#line 715 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3107 "parser.cpp"
    break;

  case 185: // expr_reference: expr_path "::" expr_identifier
#line 717 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3113 "parser.cpp"
    break;

  case 186: // expr_array: expr_object "[" expr "]"
#line 722 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3119 "parser.cpp"
    break;

  case 187: // expr_field: expr_object "." expr_identifier
#line 727 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3125 "parser.cpp"
    break;

  case 188: // expr_field: expr_object "field"
#line 729 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ())); }
#line 3131 "parser.cpp"
    break;

  case 189: // expr_size: expr_object ".size"
#line 734 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3137 "parser.cpp"
    break;

  case 190: // expr_paren: "(" expr ")"
#line 739 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3143 "parser.cpp"
    break;

  case 191: // expr_object: expr_call
#line 743 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3149 "parser.cpp"
    break;

  case 192: // expr_object: expr_method
#line 744 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3155 "parser.cpp"
    break;

  case 193: // expr_object: expr_array
#line 745 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3161 "parser.cpp"
    break;

  case 194: // expr_object: expr_field
#line 746 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3167 "parser.cpp"
    break;

  case 195: // expr_object: expr_game
#line 747 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3173 "parser.cpp"
    break;

  case 196: // expr_object: expr_self
#line 748 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3179 "parser.cpp"
    break;

  case 197: // expr_object: expr_anim
#line 749 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3185 "parser.cpp"
    break;

  case 198: // expr_object: expr_level
#line 750 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3191 "parser.cpp"
    break;

  case 199: // expr_object: expr_identifier
#line 751 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3197 "parser.cpp"
    break;

  case 200: // expr_thisthread: "thisthread"
#line 756 "parser.ypp"
        { yylhs.value.as < ast::expr_thisthread::ptr > () = std::make_unique<ast::expr_thisthread>(yylhs.location); }
#line 3203 "parser.cpp"
    break;

  case 201: // expr_empty_array: "[" "]"
#line 761 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3209 "parser.cpp"
    break;

  case 202: // expr_undefined: "undefined"
#line 766 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3215 "parser.cpp"
    break;

  case 203: // expr_game: "game"
#line 771 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3221 "parser.cpp"
    break;

  case 204: // expr_self: "self"
#line 776 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3227 "parser.cpp"
    break;

  case 205: // expr_anim: "anim"
#line 781 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3233 "parser.cpp"
    break;

  case 206: // expr_level: "level"
#line 786 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3239 "parser.cpp"
    break;

  case 207: // expr_animation: "%" "identifier"
#line 791 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3245 "parser.cpp"
    break;

  case 208: // expr_animtree: "#animtree"
#line 796 "parser.ypp"
        { yylhs.value.as < ast::expr_animtree::ptr > () = std::make_unique<ast::expr_animtree>(yylhs.location); }
#line 3251 "parser.cpp"
    break;

  case 209: // expr_identifier: "identifier"
#line 801 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3257 "parser.cpp"
    break;

  case 210: // expr_path: "path"
#line 806 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3263 "parser.cpp"
    break;

  case 211: // expr_path: expr_identifier
#line 808 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < ast::expr_identifier::ptr > ()->value); }
#line 3269 "parser.cpp"
    break;

  case 212: // expr_istring: "localized string"
#line 813 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3275 "parser.cpp"
    break;

  case 213: // expr_string: "string literal"
#line 818 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3281 "parser.cpp"
    break;

  case 214: // expr_color: "color"
#line 823 "parser.ypp"
        { yylhs.value.as < ast::expr_color::ptr > () = std::make_unique<ast::expr_color>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3287 "parser.cpp"
    break;

  case 215: // expr_vector: "(" expr "," expr "," expr ")"
#line 828 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3293 "parser.cpp"
    break;

  case 216: // expr_float: "-" "float"
#line 833 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3299 "parser.cpp"
    break;

  case 217: // expr_float: "float"
#line 835 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3305 "parser.cpp"
    break;

  case 218: // expr_integer: "-" "integer"
#line 840 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3311 "parser.cpp"
    break;

  case 219: // expr_integer: "integer"
#line 842 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3317 "parser.cpp"
    break;

  case 220: // expr_false: "false"
#line 847 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3323 "parser.cpp"
    break;

  case 221: // expr_true: "true"
#line 852 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3329 "parser.cpp"
    break;


#line 3333 "parser.cpp"

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
  "#include", "#using_animtree", "#animtree", "endon", "notify", "wait",
  "waittill", "waittillmatch", "waittillframeend", "waitframe", "if",
  "else", "do", "while", "for", "foreach", "in", "switch", "case",
  "default", "break", "continue", "return", "breakpoint", "prof_begin",
  "prof_end", "thread", "childthread", "thisthread", "call", "true",
  "false", "undefined", ".size", "game", "self", "anim", "level", "(", ")",
  "{", "}", "[", "]", ",", ".", "::", ":", ";", "?", "++", "--", "<<",
  ">>", "||", "&&", "==", "!=", "<=", ">=", "<", ">", "!", "~", "=", "+=",
  "-=", "*=", "/=", "%=", "|=", "&=", "^=", ">>=", "<<=", "|", "&", "^",
  "+", "-", "*", "/", "%", "field", "path", "identifier", "string literal",
  "localized string", "color", "float", "integer", "ADD_ARRAY", "THEN",
  "TERN", "NEG", "ANIMREF", "PREINC", "PREDEC", "POSTINC", "POSTDEC",
  "$accept", "root", "program", "inline", "include", "declaration",
  "decl_usingtree", "decl_constant", "decl_thread", "stmt", "stmt_or_dev",
  "stmt_list", "stmt_or_dev_list", "stmt_dev", "stmt_block", "stmt_expr",
  "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify", "stmt_wait",
  "stmt_waittill", "stmt_waittillmatch", "stmt_waittillframeend",
  "stmt_waitframe", "stmt_if", "stmt_ifelse", "stmt_while", "stmt_dowhile",
  "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case", "stmt_default",
  "stmt_break", "stmt_continue", "stmt_return", "stmt_breakpoint",
  "stmt_prof_begin", "stmt_prof_end", "expr", "expr_or_empty",
  "expr_assign", "expr_increment", "expr_decrement", "expr_ternary",
  "expr_binary", "expr_primitive", "expr_complement", "expr_not",
  "expr_call", "expr_method", "expr_function", "expr_pointer",
  "expr_add_array", "expr_parameters", "expr_arguments",
  "expr_arguments_no_empty", "expr_reference", "expr_array", "expr_field",
  "expr_size", "expr_paren", "expr_object", "expr_thisthread",
  "expr_empty_array", "expr_undefined", "expr_game", "expr_self",
  "expr_anim", "expr_level", "expr_animation", "expr_animtree",
  "expr_identifier", "expr_path", "expr_istring", "expr_string",
  "expr_color", "expr_vector", "expr_float", "expr_integer", "expr_false",
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

#if S1DEBUG
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
#if S1DEBUG
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
#if S1DEBUG
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


  const short parser::yypact_ninf_ = -270;

  const short parser::yytable_ninf_ = -212;

  const short
  parser::yypact_[] =
  {
       3,  -270,  -270,   -42,   -42,   -16,  -270,    43,     3,  -270,
    -270,  -270,  -270,  -270,  -270,   -25,  -270,  -270,     1,     7,
     -50,  -270,  -270,  -270,  -270,   -28,   934,  -270,  -270,  -270,
      24,   -14,  -270,  -270,   -37,   -33,  -270,    59,  -270,  -270,
    -270,  -270,  -270,  -270,  -270,   934,   627,   -28,   934,   934,
      37,   -11,  -270,  -270,  -270,  -270,  2024,  -270,  -270,  -270,
    -270,  -270,    69,   293,  -270,  -270,  -270,  -270,   433,   532,
    -270,  -270,   542,  -270,  -270,  -270,   665,   692,   965,  1179,
    -270,  -270,     8,    41,  -270,  -270,  -270,  -270,  -270,  -270,
    -270,  -270,    49,    73,   -28,    62,    82,    78,    88,    95,
      89,    96,  1310,   627,  -270,  2107,    98,   106,  -270,  -270,
    -270,  -270,  -270,  -270,  -270,   934,   934,   934,   934,   934,
     934,   934,   934,   934,   934,   934,   934,   934,   934,   934,
     934,   934,   934,   934,  -270,   999,   -28,  -270,  -270,  -270,
     112,   114,   934,   -28,  -270,   791,  -270,  -270,   934,   934,
     -28,   934,   934,   -28,   934,  -270,   934,  1754,   934,  -270,
    1989,    65,    65,  2138,  2148,   860,   860,   152,   152,   152,
     152,  2179,  1013,  2189,    75,    75,  -270,  -270,  -270,  1794,
    -270,   -28,    17,  -270,   120,  1092,   934,   113,   -10,   124,
    1268,   131,   134,   137,   140,    -7,   141,   133,   136,   869,
     139,   155,   156,  -270,   148,    33,    33,  -270,  -270,   843,
    -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
    -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
    -270,  -270,  -270,  -270,  -270,  -270,   151,   159,   161,   162,
     165,  -270,  -270,  1187,  -270,  -270,  -270,  -270,   -32,  1834,
      32,   158,  1874,    34,   176,  1914,  1953,   157,  2107,   934,
    -270,   120,  -270,   934,  -270,  -270,  1146,  2059,  -270,   164,
    -270,   934,   202,   934,   -19,   -28,   934,   128,   172,   173,
    -270,  -270,  -270,  -270,  2094,  -270,   934,   934,   934,  -270,
    -270,   592,   592,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
     184,   185,   188,   189,  -270,  -270,   934,   934,   934,   934,
     934,   934,   934,   934,   934,   934,   934,   193,  -270,   934,
     194,  -270,   934,   195,   934,   201,  2107,    38,  -270,  -270,
    -270,   180,  1476,   203,  1510,   196,  -270,  -270,  -270,  1272,
      -4,  1544,  -270,  -270,  -270,    42,    45,  1754,   934,   934,
     934,   934,  2107,  2107,  2107,  2107,  2107,  2107,  2107,  2107,
    2107,  2107,  2107,   204,    55,   205,    64,   207,  1578,   934,
    -270,  -270,  1268,   934,  1268,   934,   934,   -28,    73,   208,
     209,  1612,  1354,  1398,  1442,   934,  -270,   934,  -270,   934,
    -270,    68,   238,  1646,  -270,  2107,   215,  1680,   235,  -270,
    -270,  -270,   217,   219,   934,   220,   934,   221,   934,    71,
      77,    84,  -270,  1268,   227,   -19,  1268,   934,  -270,  -270,
     214,  -270,   216,  -270,   237,  -270,  -270,  -270,  -270,  -270,
     241,  -270,  1714,   233,   234,   239,  1268,  1268,  -270,  -270,
    -270,  -270,  -270
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   209,     0,     2,     7,
       8,     9,    14,    15,    16,     0,   210,   211,     0,     0,
       0,     1,     4,     5,     6,   179,     0,    10,    11,   213,
       0,     0,   178,   208,     0,     0,   200,     0,   221,   220,
     202,   203,   204,   205,   206,     0,   181,     0,     0,     0,
       0,     0,   212,   214,   217,   219,     0,    93,    94,    95,
     132,   133,   134,   135,   162,   163,   136,   137,   138,   139,
     140,   141,     0,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,     0,   152,   153,   154,   155,   156,   157,
     158,   159,     0,     0,     0,     0,   211,     0,     0,   211,
       0,     0,     0,   181,   201,   183,     0,   180,   184,   161,
     160,   216,   218,   207,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   189,     0,     0,   188,   164,   165,
     211,     0,   181,     0,    17,     0,    19,   177,     0,   181,
       0,     0,   181,     0,     0,   190,     0,   183,     0,   176,
       0,   125,   126,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   127,   128,   129,   130,   131,     0,
     187,     0,     0,   180,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,     0,     0,     0,    45,    50,     0,
      46,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,     0,     0,     0,   191,
     192,   193,   194,     0,   195,   196,   197,   198,   199,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,     0,
     186,     0,   166,   181,    52,    48,     0,     0,    72,     0,
      73,     0,     0,     0,    58,     0,     0,     0,     0,     0,
      85,    86,    87,    89,     0,    90,   181,   181,     0,   191,
     192,   109,   111,    53,    49,    61,    62,    63,    59,    60,
       0,     0,     0,     0,   110,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   168,   181,
       0,   170,   181,     0,     0,     0,   113,     0,    51,    47,
      67,     0,     0,     0,     0,     0,    55,    56,    57,     0,
       0,     0,    84,    83,    88,     0,     0,     0,     0,     0,
       0,     0,    98,   104,   105,   106,   107,   108,    99,   100,
     101,   103,   102,     0,     0,     0,     0,     0,     0,   181,
     167,    74,     0,     0,     0,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   181,   169,   181,   171,   181,
     215,     0,    75,     0,    77,    96,     0,     0,     0,    82,
      91,    92,     0,     0,   181,     0,   181,     0,   181,     0,
       0,     0,   172,     0,     0,    58,     0,     0,    64,    66,
     180,    69,   180,    71,   180,   173,   174,   175,    76,    78,
       0,    80,     0,     0,     0,     0,     0,     0,    65,    68,
      70,    79,    81
  };

  const short
  parser::yypgoto_[] =
  {
    -270,  -270,  -270,   294,   295,   296,  -270,  -270,  -270,  -152,
     117,  -270,  -270,  -270,   -91,   -87,  -270,  -270,  -270,  -270,
    -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
    -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,  -270,
     190,  -270,  -269,  -267,  -261,  -270,  -270,  -270,  -270,  -270,
     -86,   -12,   -66,   -61,  -270,  -270,    13,   -45,  -270,    -6,
     179,  -270,  -270,   249,  -270,  -270,  -270,   282,   337,   362,
     372,  -270,  -270,     0,     6,  -270,    -8,  -270,  -270,  -270,
     142,  -270,  -270
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     7,     8,     9,    10,    11,    12,    13,    14,   207,
     208,   266,   209,   210,   211,   335,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     105,   396,   236,   237,   238,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    31,   106,   183,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91
  };

  const short
  parser::yytable_[] =
  {
      15,   107,   146,    17,    17,   336,   138,   337,    15,    18,
      19,   139,    30,   338,     1,     2,     3,     4,     5,    95,
     142,    34,    35,    98,    37,    32,   376,    25,  -211,    41,
      42,    43,    44,   265,    96,    99,    20,   204,   272,    93,
      97,   100,   269,    21,    94,   205,   206,   108,  -199,  -199,
      29,  -199,   270,    26,   377,  -199,    16,     6,   107,   239,
     142,    16,     6,    27,  -199,    16,     6,  -199,  -211,    28,
     262,     6,   140,    34,    35,   158,    37,    92,   141,    16,
       6,    41,    42,    43,    44,   318,   277,   321,   113,   204,
     158,   370,   158,    29,   147,   379,   158,    55,   380,   239,
     158,   143,     6,   158,   239,  -199,  -199,  -199,   386,  -191,
    -191,   144,  -191,   158,   329,   101,  -191,   388,   148,   289,
     289,   412,   158,   239,   425,  -191,   158,   145,  -191,   158,
     426,    16,     6,   240,   149,   158,   180,   427,   150,   241,
     111,   112,   158,   184,   151,   248,   336,   152,   337,   153,
     251,   141,   154,   254,   338,   182,   158,   129,   130,   131,
     132,   133,   250,   159,   142,   253,  -191,  -191,  -191,   131,
     132,   133,   263,   240,   181,   268,   271,   138,   240,   241,
     239,   261,   139,   273,   241,   248,   274,   278,   289,   275,
     248,   141,   276,   290,   290,   281,   141,   240,   282,   241,
     241,   285,   280,   241,   288,   248,   248,   286,   287,   248,
     319,   141,   141,   295,   325,   141,    56,   331,   116,   117,
     392,   296,   394,   297,   298,   138,   138,   299,   322,   333,
     139,   139,   112,   342,   343,   102,   348,   349,   109,   110,
     350,   351,   371,   140,   129,   130,   131,   132,   133,   141,
     363,   365,   367,   369,   240,   373,   385,   387,   375,   389,
     241,   428,   290,   413,   431,   417,   248,   433,   241,   434,
     400,   401,   141,   138,   248,   340,   327,   415,   139,   418,
     141,   419,   421,   423,   441,   442,   239,   399,   239,   429,
     435,   140,   140,   157,   436,   438,   439,   141,   141,   345,
     346,   440,    22,    23,    24,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   242,   179,   294,   239,   430,   289,
     239,     0,   364,  -192,  -192,   366,  -192,   279,   249,   140,
    -192,   252,     0,     0,   255,   141,   256,     0,   258,  -192,
     239,   239,  -192,     0,     0,     0,     0,     0,     0,   420,
     240,   422,   240,   424,   242,     0,   241,     0,   241,   242,
       0,     0,   248,     0,   248,     0,   267,   398,   141,     0,
     141,     0,   391,     0,   242,   242,     0,     0,   242,   284,
    -192,  -192,  -192,     0,   243,     0,     0,     0,   409,     0,
     410,   240,   411,   290,   240,     0,     0,   241,     0,   241,
     241,     0,     0,   248,     0,   248,   248,     0,     0,   141,
       0,   141,   141,     0,   240,   240,     0,   244,     0,     0,
     241,   241,     0,     0,   243,     0,   248,   248,     0,   243,
       0,     0,   141,   141,     0,   242,     0,     0,     0,   326,
       0,     0,     0,   242,   291,   292,     0,     0,   243,     0,
       0,   332,     0,   334,     0,     0,   341,   244,     0,     0,
       0,     0,   244,  -193,  -193,     0,  -193,     0,   347,     0,
    -193,     0,   245,     0,     0,     0,     0,   244,   244,  -193,
       0,   244,  -193,     0,     0,     0,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   246,     0,     0,
       0,     0,     0,     0,   368,   243,     0,   247,     0,     0,
       0,     0,   245,   339,     0,     0,     0,   245,     0,     0,
    -193,  -193,  -193,     0,     0,     0,     0,     0,   381,   382,
     383,   384,   245,   245,     0,     0,   245,   246,   244,     0,
       0,   242,   246,   242,     0,     0,   244,   247,     0,     0,
       0,     0,   247,   393,     0,   395,   397,   246,   246,     0,
       0,   246,  -194,  -194,     0,  -194,     0,   247,   247,  -194,
       0,   247,    34,    35,     0,    37,     0,     0,  -194,   134,
       0,  -194,   242,     0,   242,   242,     0,     0,   135,     0,
       0,   136,     0,   245,     0,     0,     0,   432,     0,     0,
       0,   245,     0,     0,     0,   242,   242,     0,     0,     0,
       0,   243,     0,   243,     0,     0,     0,     0,   246,  -194,
    -194,  -194,    34,    35,     0,    37,   246,     0,   247,   137,
      16,     6,     0,    33,     0,     0,   247,     0,   135,     0,
       0,   136,     0,     0,   244,     0,   244,     0,     0,     0,
       0,     0,   243,     0,   339,   243,     0,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,    45,
       0,     0,     0,   103,   104,   243,   243,    47,     0,   137,
      16,     6,     0,     0,     0,   244,     0,   244,   244,     0,
       0,     0,     0,    48,    49,  -195,  -195,     0,  -195,   245,
       0,   245,  -195,     0,     0,     0,     0,     0,   244,   244,
      50,  -195,     0,    51,  -195,    16,     6,    29,    52,    53,
      54,    55,  -196,  -196,   246,  -196,   246,     0,     0,  -196,
       0,     0,     0,     0,   247,     0,   247,     0,  -196,     0,
     245,  -196,   245,   245,     0,     0,     0,     0,     0,     0,
       0,     0,  -195,  -195,  -195,     0,     0,     0,     0,     0,
       0,     0,     0,   245,   245,   246,     0,   246,   246,     0,
       0,     0,     0,     0,     0,   247,     0,   247,   247,  -196,
    -196,  -196,     0,     0,     0,     0,     0,     0,   246,   246,
       0,     0,   185,     0,     0,     0,     0,     0,   247,   247,
     186,     0,     0,   187,   188,   189,     0,   190,   191,   192,
     193,     0,   194,   195,   196,   197,   198,   199,   200,   201,
     202,    34,    35,     0,    37,     0,     0,     0,     0,    41,
      42,    43,    44,     0,     0,   145,   203,   204,     0,     0,
       0,     0,     0,     0,   185,   205,   206,     0,     0,     0,
       0,     0,   186,     0,     0,   187,   188,   189,     0,   190,
     191,   192,   193,     0,   194,   195,   196,   197,   198,   199,
     200,   201,   202,    34,    35,    33,    37,     0,     0,    16,
       6,    41,    42,    43,    44,     0,     0,   145,   293,   204,
       0,     0,     0,     0,     0,     0,     0,   205,   206,    34,
      35,    36,    37,    38,    39,    40,     0,    41,    42,    43,
      44,    45,     0,     0,     0,    46,   116,   117,     0,    47,
       0,   283,   122,   123,   124,   125,     0,     0,     0,     0,
       0,    16,     6,     0,     0,    48,    49,     0,     0,     0,
      33,     0,   129,   130,   131,   132,   133,     0,     0,     0,
       0,     0,    50,     0,     0,    51,     0,    16,     6,    29,
      52,    53,    54,    55,    34,    35,    36,    37,    38,    39,
      40,     0,    41,    42,    43,    44,    45,     0,     0,     0,
      46,     0,     0,     0,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -197,  -197,     0,  -197,     0,
      48,    49,  -197,     0,     0,    33,     0,     0,     0,     0,
       0,  -197,     0,     0,  -197,     0,     0,    50,     0,     0,
      51,     0,    16,     6,    29,    52,    53,    54,    55,    34,
      35,    36,    37,    38,    39,    40,     0,    41,    42,    43,
      44,    45,     0,     0,     0,   103,     0,     0,     0,    47,
       0,     0,  -197,  -197,  -197,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,     0,     0,   116,
     117,     0,     0,   120,   121,   122,   123,   124,   125,     0,
       0,     0,    50,     0,     0,    51,     0,    16,     6,    29,
      52,    53,    54,    55,   264,   129,   130,   131,   132,   133,
       0,   186,     0,     0,   187,   188,   189,     0,   190,   191,
     192,   193,     0,   194,   195,   196,   197,   198,   199,   200,
     201,   202,    34,    35,     0,    37,     0,     0,     0,     0,
      41,    42,    43,    44,     0,     0,   145,     0,   204,     0,
       0,     0,     0,     0,     0,     0,   205,   206,   328,     0,
       0,     0,     0,     0,     0,   186,     0,     0,   187,   188,
     189,     0,   190,   191,   192,   193,     0,   194,   195,   196,
     197,   198,   199,   200,   201,   202,    34,    35,     0,    37,
      16,     6,     0,     0,    41,    42,    43,    44,     0,     0,
     145,     0,   204,     0,   300,   301,     0,   302,   303,     0,
     205,   206,     0,     0,     0,     0,     0,     0,     0,  -198,
    -198,     0,  -198,     0,     0,     0,  -198,    34,    35,     0,
      37,     0,     0,     0,     0,  -198,     0,     0,  -198,     0,
       0,     0,     0,   135,    16,     6,   136,     0,     0,     0,
       0,   304,   305,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,  -198,  -198,  -198,     0,
       0,     0,     0,     0,   137,    16,     6,   186,     0,     0,
     187,   188,   189,     0,   190,   191,   192,   193,     0,   194,
     195,   196,   197,   198,   199,   200,   201,   202,    34,    35,
       0,    37,    34,    35,     0,    37,    41,    42,    43,    44,
       0,     0,   145,     0,   204,     0,     0,     0,   135,     0,
       0,   136,   205,   206,     0,     0,   304,   305,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,     0,     0,   155,     0,     0,    16,     6,   156,   137,
      16,     6,     0,   115,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   126,
     127,   128,   129,   130,   131,   132,   133,   403,     0,     0,
       0,     0,   404,     0,     0,     0,     0,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   405,     0,     0,     0,     0,   406,     0,     0,     0,
       0,   115,     0,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   126,   127,   128,
     129,   130,   131,   132,   133,   407,     0,     0,     0,     0,
     408,     0,     0,     0,     0,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   372,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   115,
       0,     0,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   374,     0,   126,   127,   128,   129,   130,
     131,   132,   133,   115,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   378,     0,   126,
     127,   128,   129,   130,   131,   132,   133,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   390,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   115,     0,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   402,     0,   126,   127,   128,
     129,   130,   131,   132,   133,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   414,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   115,
       0,     0,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   416,     0,   126,   127,   128,   129,   130,
     131,   132,   133,   115,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   437,     0,   126,
     127,   128,   129,   130,   131,   132,   133,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   257,     0,     0,     0,     0,     0,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   260,     0,     0,     0,     0,     0,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   317,     0,     0,     0,     0,     0,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   320,     0,     0,     0,     0,     0,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   323,     0,     0,     0,     0,     0,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   324,     0,     0,     0,     0,   115,     0,     0,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   126,   127,   128,   129,   130,   131,   132,   133,
     259,     0,   115,     0,     0,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   126,   127,
     128,   129,   130,   131,   132,   133,   114,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   330,   115,     0,     0,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   126,   127,
     128,   129,   130,   131,   132,   133,   344,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     115,     0,     0,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,     0,     0,     0,     0,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   116,   117,     0,   119,   120,   121,
     122,   123,   124,   125,   116,   117,     0,     0,   120,   121,
     122,   123,   124,   125,     0,     0,     0,   126,   127,   128,
     129,   130,   131,   132,   133,     0,     0,   126,   127,   128,
     129,   130,   131,   132,   133,   116,   117,     0,     0,   120,
     121,   122,   123,   124,   125,   116,   117,     0,     0,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   133,     0,     0,     0,   127,
       0,   129,   130,   131,   132,   133
  };

  const short
  parser::yycheck_[] =
  {
       0,    46,    93,     3,     4,   274,    72,   274,     8,     3,
       4,    72,    20,   274,    11,    12,    13,    14,    15,    56,
      52,    40,    41,    56,    43,    25,    30,    52,    60,    48,
      49,    50,    51,   185,    34,    35,    52,    56,   190,    53,
      34,    35,    52,     0,    58,    64,    65,    47,    40,    41,
     100,    43,    62,    78,    58,    47,    98,    99,   103,   145,
      52,    98,    99,    62,    56,    98,    99,    59,    60,    62,
      53,    99,    72,    40,    41,    58,    43,    53,    72,    98,
      99,    48,    49,    50,    51,    53,    93,    53,    99,    56,
      58,    53,    58,   100,    94,    53,    58,   104,    53,   185,
      58,    60,    99,    58,   190,    97,    98,    99,    53,    40,
      41,    62,    43,    58,   266,    56,    47,    53,    56,   205,
     206,    53,    58,   209,    53,    56,    58,    54,    59,    58,
      53,    98,    99,   145,    52,    58,   136,    53,    60,   145,
     103,   104,    58,   143,    56,   145,   415,    52,   415,    60,
     150,   145,    56,   153,   415,   142,    58,    92,    93,    94,
      95,    96,   149,    57,    52,   152,    97,    98,    99,    94,
      95,    96,    52,   185,    60,    62,    52,   243,   190,   185,
     266,   181,   243,    52,   190,   185,    52,   195,   274,    52,
     190,   185,    52,   205,   206,    62,   190,   209,    62,   205,
     206,    62,    61,   209,    56,   205,   206,    52,    52,   209,
      52,   205,   206,    62,    57,   209,    26,    53,    66,    67,
     372,    62,   374,    62,    62,   291,   292,    62,    52,    27,
     291,   292,   104,    61,    61,    45,    52,    52,    48,    49,
      52,    52,    62,   243,    92,    93,    94,    95,    96,   243,
      57,    57,    57,    52,   266,    52,    52,    52,    62,    52,
     266,   413,   274,    25,   416,    30,   266,    53,   274,    53,
      62,    62,   266,   339,   274,   275,   263,    62,   339,    62,
     274,    62,    62,    62,   436,   437,   372,   378,   374,    62,
      53,   291,   292,   103,    53,    62,    62,   291,   292,   286,
     287,    62,     8,     8,     8,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   145,   135,   209,   413,   415,   415,
     416,    -1,   319,    40,    41,   322,    43,   195,   148,   339,
      47,   151,    -1,    -1,   154,   339,   156,    -1,   158,    56,
     436,   437,    59,    -1,    -1,    -1,    -1,    -1,    -1,   404,
     372,   406,   374,   408,   185,    -1,   372,    -1,   374,   190,
      -1,    -1,   372,    -1,   374,    -1,   186,   377,   372,    -1,
     374,    -1,   369,    -1,   205,   206,    -1,    -1,   209,   199,
      97,    98,    99,    -1,   145,    -1,    -1,    -1,   385,    -1,
     387,   413,   389,   415,   416,    -1,    -1,   413,    -1,   415,
     416,    -1,    -1,   413,    -1,   415,   416,    -1,    -1,   413,
      -1,   415,   416,    -1,   436,   437,    -1,   145,    -1,    -1,
     436,   437,    -1,    -1,   185,    -1,   436,   437,    -1,   190,
      -1,    -1,   436,   437,    -1,   266,    -1,    -1,    -1,   259,
      -1,    -1,    -1,   274,   205,   206,    -1,    -1,   209,    -1,
      -1,   271,    -1,   273,    -1,    -1,   276,   185,    -1,    -1,
      -1,    -1,   190,    40,    41,    -1,    43,    -1,   288,    -1,
      47,    -1,   145,    -1,    -1,    -1,    -1,   205,   206,    56,
      -1,   209,    59,    -1,    -1,    -1,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   145,    -1,    -1,
      -1,    -1,    -1,    -1,   324,   266,    -1,   145,    -1,    -1,
      -1,    -1,   185,   274,    -1,    -1,    -1,   190,    -1,    -1,
      97,    98,    99,    -1,    -1,    -1,    -1,    -1,   348,   349,
     350,   351,   205,   206,    -1,    -1,   209,   185,   266,    -1,
      -1,   372,   190,   374,    -1,    -1,   274,   185,    -1,    -1,
      -1,    -1,   190,   373,    -1,   375,   376,   205,   206,    -1,
      -1,   209,    40,    41,    -1,    43,    -1,   205,   206,    47,
      -1,   209,    40,    41,    -1,    43,    -1,    -1,    56,    47,
      -1,    59,   413,    -1,   415,   416,    -1,    -1,    56,    -1,
      -1,    59,    -1,   266,    -1,    -1,    -1,   417,    -1,    -1,
      -1,   274,    -1,    -1,    -1,   436,   437,    -1,    -1,    -1,
      -1,   372,    -1,   374,    -1,    -1,    -1,    -1,   266,    97,
      98,    99,    40,    41,    -1,    43,   274,    -1,   266,    97,
      98,    99,    -1,    16,    -1,    -1,   274,    -1,    56,    -1,
      -1,    59,    -1,    -1,   372,    -1,   374,    -1,    -1,    -1,
      -1,    -1,   413,    -1,   415,   416,    -1,    40,    41,    42,
      43,    44,    45,    46,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    56,    57,   436,   437,    60,    -1,    97,
      98,    99,    -1,    -1,    -1,   413,    -1,   415,   416,    -1,
      -1,    -1,    -1,    76,    77,    40,    41,    -1,    43,   372,
      -1,   374,    47,    -1,    -1,    -1,    -1,    -1,   436,   437,
      93,    56,    -1,    96,    59,    98,    99,   100,   101,   102,
     103,   104,    40,    41,   372,    43,   374,    -1,    -1,    47,
      -1,    -1,    -1,    -1,   372,    -1,   374,    -1,    56,    -1,
     413,    59,   415,   416,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   436,   437,   413,    -1,   415,   416,    -1,
      -1,    -1,    -1,    -1,    -1,   413,    -1,   415,   416,    97,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,   436,   437,
      -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,   436,   437,
      19,    -1,    -1,    22,    23,    24,    -1,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    43,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    -1,    -1,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    11,    64,    65,    -1,    -1,    -1,
      -1,    -1,    19,    -1,    -1,    22,    23,    24,    -1,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    16,    43,    -1,    -1,    98,
      99,    48,    49,    50,    51,    -1,    -1,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    40,
      41,    42,    43,    44,    45,    46,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    56,    66,    67,    -1,    60,
      -1,    62,    72,    73,    74,    75,    -1,    -1,    -1,    -1,
      -1,    98,    99,    -1,    -1,    76,    77,    -1,    -1,    -1,
      16,    -1,    92,    93,    94,    95,    96,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    96,    -1,    98,    99,   100,
     101,   102,   103,   104,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    43,    -1,
      76,    77,    47,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    -1,    59,    -1,    -1,    93,    -1,    -1,
      96,    -1,    98,    99,   100,   101,   102,   103,   104,    40,
      41,    42,    43,    44,    45,    46,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,    60,
      -1,    -1,    97,    98,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    66,
      67,    -1,    -1,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    93,    -1,    -1,    96,    -1,    98,    99,   100,
     101,   102,   103,   104,    12,    92,    93,    94,    95,    96,
      -1,    19,    -1,    -1,    22,    23,    24,    -1,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    -1,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    22,    23,
      24,    -1,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      98,    99,    -1,    -1,    48,    49,    50,    51,    -1,    -1,
      54,    -1,    56,    -1,    17,    18,    -1,    20,    21,    -1,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    -1,    43,    -1,    -1,    -1,    47,    40,    41,    -1,
      43,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    56,    98,    99,    59,    -1,    -1,    -1,
      -1,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    97,    98,    99,    -1,
      -1,    -1,    -1,    -1,    97,    98,    99,    19,    -1,    -1,
      22,    23,    24,    -1,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,    40,    41,    -1,    43,    48,    49,    50,    51,
      -1,    -1,    54,    -1,    56,    -1,    -1,    -1,    56,    -1,
      -1,    59,    64,    65,    -1,    -1,    64,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    53,    -1,    -1,    98,    99,    58,    97,
      98,    99,    -1,    63,    -1,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      90,    91,    92,    93,    94,    95,    96,    53,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,
      92,    93,    94,    95,    96,    53,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    89,    90,    91,    92,    93,    94,    95,    96,    63,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    89,    90,    91,    92,    93,
      94,    95,    96,    63,    -1,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    89,
      90,    91,    92,    93,    94,    95,    96,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    63,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    89,    90,    91,
      92,    93,    94,    95,    96,    63,    -1,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    89,    90,    91,    92,    93,    94,    95,    96,    63,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    89,    90,    91,    92,    93,
      94,    95,    96,    63,    -1,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    89,
      90,    91,    92,    93,    94,    95,    96,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    57,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    58,    -1,    -1,    -1,    -1,    63,    -1,    -1,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    92,    93,    94,    95,    96,
      61,    -1,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94,    95,    96,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    62,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94,    95,    96,    62,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      63,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    89,    90,    91,    92,    93,    94,    95,
      96,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,    92,
      93,    94,    95,    96,    66,    67,    -1,    69,    70,    71,
      72,    73,    74,    75,    66,    67,    -1,    -1,    70,    71,
      72,    73,    74,    75,    -1,    -1,    -1,    89,    90,    91,
      92,    93,    94,    95,    96,    -1,    -1,    89,    90,    91,
      92,    93,    94,    95,    96,    66,    67,    -1,    -1,    70,
      71,    72,    73,    74,    75,    66,    67,    -1,    -1,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    90,
      91,    92,    93,    94,    95,    96,    -1,    -1,    -1,    90,
      -1,    92,    93,    94,    95,    96
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    11,    12,    13,    14,    15,    99,   115,   116,   117,
     118,   119,   120,   121,   122,   187,    98,   187,   188,   188,
      52,     0,   117,   118,   119,    52,    78,    62,    62,   100,
     190,   169,   187,    16,    40,    41,    42,    43,    44,    45,
      46,    48,    49,    50,    51,    52,    56,    60,    76,    77,
      93,    96,   101,   102,   103,   104,   154,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,    53,    53,    58,    56,   187,   188,    56,   187,
     188,    56,   154,    56,    57,   154,   170,   171,   187,   154,
     154,   103,   104,    99,    62,    63,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    89,    90,    91,    92,
      93,    94,    95,    96,    47,    56,    59,    97,   166,   167,
     187,   188,    52,    60,    62,    54,   128,   187,    56,    52,
      60,    56,    52,    60,    56,    53,    58,   154,    58,    57,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     187,    60,   170,   171,   187,    11,    19,    22,    23,    24,
      26,    27,    28,    29,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    55,    56,    64,    65,   123,   124,   126,
     127,   128,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   156,   157,   158,   164,
     165,   173,   174,   177,   181,   182,   183,   184,   187,   154,
     170,   187,   154,   170,   187,   154,   154,    57,   154,    61,
      57,   187,    53,    52,    12,   123,   125,   154,    62,    52,
      62,    52,   123,    52,    52,    52,    52,    93,   190,   194,
      61,    62,    62,    62,   154,    62,    52,    52,    56,   164,
     165,   177,   177,    55,   124,    62,    62,    62,    62,    62,
      17,    18,    20,    21,    64,    65,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    57,    53,    52,
      57,    53,    52,    57,    58,    57,   154,   170,    12,   123,
      62,    53,   154,    27,   154,   129,   156,   157,   158,   177,
     187,   154,    61,    61,    62,   170,   170,   154,    52,    52,
      52,    52,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,    57,   170,    57,   170,    57,   154,    52,
      53,    62,    53,    52,    53,    62,    30,    58,    53,    53,
      53,   154,   154,   154,   154,    52,    53,    52,    53,    52,
      53,   170,   123,   154,   123,   154,   155,   154,   187,   128,
      62,    62,    53,    53,    58,    53,    58,    53,    58,   170,
     170,   170,    53,    25,    53,    62,    53,    30,    62,    62,
     171,    62,   171,    62,   171,    53,    53,    53,   123,    62,
     129,   123,   154,    53,    53,    53,    53,    53,    62,    62,
      62,   123,   123
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   114,   115,   115,   116,   116,   116,   116,   116,   116,
     117,   118,   119,   119,   119,   119,   119,   120,   121,   122,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   124,   124,   125,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   129,   129,   130,
     130,   131,   131,   131,   132,   133,   133,   134,   135,   135,
     136,   136,   137,   138,   138,   139,   140,   141,   142,   143,
     144,   144,   145,   146,   146,   147,   148,   149,   150,   150,
     151,   152,   153,   154,   154,   154,   155,   155,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   157,
     157,   158,   158,   159,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     162,   163,   164,   164,   165,   165,   166,   166,   166,   166,
     166,   166,   167,   167,   167,   167,   168,   169,   169,   169,
     170,   170,   171,   171,   172,   172,   173,   174,   174,   175,
     176,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   188,   189,   190,   191,   192,   193,   193,   194,   194,
     195,   196
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     5,     4,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     3,     2,     3,     2,     1,     1,     1,     0,     2,
       2,     2,     2,     2,     6,     8,     6,     3,     8,     6,
       8,     6,     2,     2,     4,     5,     7,     5,     7,     9,
       7,     9,     5,     3,     3,     2,     2,     2,     3,     2,
       2,     5,     5,     1,     1,     1,     1,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     5,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     1,     2,     2,     4,     6,     5,     7,
       5,     7,     8,     9,     9,     9,     3,     3,     1,     0,
       1,     0,     3,     1,     2,     3,     4,     3,     2,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     7,     2,     1,     2,     1,
       1,     1
  };




#if S1DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   256,   256,   257,   261,   263,   265,   267,   269,   271,
     276,   280,   285,   286,   287,   288,   289,   293,   298,   303,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   336,   337,   341,   343,   348,
     350,   355,   356,   360,   361,   365,   367,   369,   372,   376,
     378,   383,   385,   387,   392,   397,   399,   404,   409,   411,
     416,   418,   423,   428,   430,   435,   440,   445,   450,   455,
     460,   462,   467,   472,   474,   479,   484,   489,   494,   496,
     501,   506,   511,   516,   517,   518,   522,   523,   527,   529,
     531,   533,   535,   537,   539,   541,   543,   545,   547,   552,
     554,   559,   561,   566,   571,   573,   575,   577,   579,   581,
     583,   585,   587,   589,   591,   593,   595,   597,   599,   601,
     603,   605,   610,   611,   612,   613,   614,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,   633,   634,   635,   636,   637,
     641,   646,   651,   652,   655,   656,   660,   662,   664,   666,
     668,   670,   675,   677,   679,   681,   686,   691,   693,   696,
     700,   703,   707,   709,   714,   716,   721,   726,   728,   733,
     738,   743,   744,   745,   746,   747,   748,   749,   750,   751,
     755,   760,   765,   770,   775,   780,   785,   790,   795,   800,
     805,   807,   812,   817,   822,   827,   832,   834,   839,   841,
     846,   851
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
#endif // S1DEBUG


#line 13 "parser.ypp"
} } } // xsk::gsc::s1
#line 4583 "parser.cpp"

#line 855 "parser.ypp"


void xsk::gsc::s1::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
