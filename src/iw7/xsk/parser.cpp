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
xsk::gsc::iw7::parser::symbol_type IW7lex(xsk::gsc::iw7::lexer& lexer);

#line 47 "parser.cpp"

// Take the name prefix into account.
#define yylex   IW7lex



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
#if IW7DEBUG

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

#else // !IW7DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !IW7DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace gsc { namespace iw7 {
#line 149 "parser.cpp"

  /// Build a parser object.
  parser::parser (xsk::gsc::iw7::lexer& lexer_yyarg, xsk::gsc::ast::program::ptr& ast_yyarg)
#if IW7DEBUG
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

      case symbol_kind::S_stmt_dev: // stmt_dev
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
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

      case symbol_kind::S_stmt_dev: // stmt_dev
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
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

      case symbol_kind::S_stmt_dev: // stmt_dev
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
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

      case symbol_kind::S_stmt_dev: // stmt_dev
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
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

#if IW7DEBUG
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

#if IW7DEBUG
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
#endif // IW7DEBUG

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

      case symbol_kind::S_stmt_dev: // stmt_dev
      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
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
#line 243 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < ast::program::ptr > ()); }
#line 1965 "parser.cpp"
    break;

  case 3: // root: %empty
#line 244 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 1971 "parser.cpp"
    break;

  case 4: // program: program inline
#line 249 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 1977 "parser.cpp"
    break;

  case 5: // program: program include
#line 251 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 1983 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 253 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 1989 "parser.cpp"
    break;

  case 7: // program: inline
#line 255 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 1995 "parser.cpp"
    break;

  case 8: // program: include
#line 257 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2001 "parser.cpp"
    break;

  case 9: // program: declaration
#line 259 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2007 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 263 "parser.ypp"
                                 { lexer.push_header(yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2013 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 268 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2019 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 272 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2025 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 273 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2031 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 274 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2037 "parser.cpp"
    break;

  case 15: // declaration: decl_constant
#line 275 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_constant = std::move(yystack_[0].value.as < ast::decl_constant::ptr > ()); }
#line 2043 "parser.cpp"
    break;

  case 16: // declaration: decl_thread
#line 276 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2049 "parser.cpp"
    break;

  case 17: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 281 "parser.ypp"
        { lexer.restrict_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2055 "parser.cpp"
    break;

  case 18: // decl_constant: expr_identifier "=" expr ";"
#line 286 "parser.ypp"
        { yylhs.value.as < ast::decl_constant::ptr > () = std::make_unique<ast::decl_constant>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2061 "parser.cpp"
    break;

  case 19: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 291 "parser.ypp"
        { lexer.restrict_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2067 "parser.cpp"
    break;

  case 20: // stmt: stmt_dev
#line 295 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2073 "parser.cpp"
    break;

  case 21: // stmt: stmt_block
#line 296 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2079 "parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 297 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2085 "parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 298 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2091 "parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 299 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2097 "parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 300 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2103 "parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 301 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2109 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 302 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2115 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 303 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2121 "parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 304 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2127 "parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 305 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2133 "parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 306 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2139 "parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 307 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2145 "parser.cpp"
    break;

  case 33: // stmt: stmt_dowhile
#line 308 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2151 "parser.cpp"
    break;

  case 34: // stmt: stmt_for
#line 309 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2157 "parser.cpp"
    break;

  case 35: // stmt: stmt_foreach
#line 310 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2163 "parser.cpp"
    break;

  case 36: // stmt: stmt_switch
#line 311 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2169 "parser.cpp"
    break;

  case 37: // stmt: stmt_case
#line 312 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2175 "parser.cpp"
    break;

  case 38: // stmt: stmt_default
#line 313 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2181 "parser.cpp"
    break;

  case 39: // stmt: stmt_break
#line 314 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2187 "parser.cpp"
    break;

  case 40: // stmt: stmt_continue
#line 315 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2193 "parser.cpp"
    break;

  case 41: // stmt: stmt_return
#line 316 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2199 "parser.cpp"
    break;

  case 42: // stmt: stmt_breakpoint
#line 317 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_breakpoint = std::move(yystack_[0].value.as < ast::stmt_breakpoint::ptr > ()); }
#line 2205 "parser.cpp"
    break;

  case 43: // stmt: stmt_prof_begin
#line 318 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2211 "parser.cpp"
    break;

  case 44: // stmt: stmt_prof_end
#line 319 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2217 "parser.cpp"
    break;

  case 45: // stmt_dev: "/#" stmt_list "#/"
#line 323 "parser.ypp"
                                { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2223 "parser.cpp"
    break;

  case 46: // stmt_dev: "/#" "#/"
#line 324 "parser.ypp"
                      { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2229 "parser.cpp"
    break;

  case 47: // stmt_block: "{" stmt_list "}"
#line 328 "parser.ypp"
                              { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2235 "parser.cpp"
    break;

  case 48: // stmt_block: "{" "}"
#line 329 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2241 "parser.cpp"
    break;

  case 49: // stmt_list: stmt_list stmt
#line 334 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2247 "parser.cpp"
    break;

  case 50: // stmt_list: stmt
#line 336 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2253 "parser.cpp"
    break;

  case 51: // stmt_expr: expr_assign
#line 341 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2259 "parser.cpp"
    break;

  case 52: // stmt_expr: expr_increment
#line 343 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2265 "parser.cpp"
    break;

  case 53: // stmt_expr: expr_decrement
#line 345 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2271 "parser.cpp"
    break;

  case 54: // stmt_expr: %empty
#line 347 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2277 "parser.cpp"
    break;

  case 55: // stmt_call: expr_call ";"
#line 352 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2283 "parser.cpp"
    break;

  case 56: // stmt_call: expr_method ";"
#line 354 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2289 "parser.cpp"
    break;

  case 57: // stmt_assign: expr_assign ";"
#line 359 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2295 "parser.cpp"
    break;

  case 58: // stmt_assign: expr_increment ";"
#line 361 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2301 "parser.cpp"
    break;

  case 59: // stmt_assign: expr_decrement ";"
#line 363 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2307 "parser.cpp"
    break;

  case 60: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 368 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2313 "parser.cpp"
    break;

  case 61: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 373 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2319 "parser.cpp"
    break;

  case 62: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 375 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2325 "parser.cpp"
    break;

  case 63: // stmt_wait: "wait" expr ";"
#line 380 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2331 "parser.cpp"
    break;

  case 64: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 385 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2337 "parser.cpp"
    break;

  case 65: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 387 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2343 "parser.cpp"
    break;

  case 66: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 392 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2349 "parser.cpp"
    break;

  case 67: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 394 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2355 "parser.cpp"
    break;

  case 68: // stmt_waittillframeend: "waittillframeend" ";"
#line 399 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2361 "parser.cpp"
    break;

  case 69: // stmt_if: "if" "(" expr ")" stmt
#line 404 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2367 "parser.cpp"
    break;

  case 70: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 409 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2373 "parser.cpp"
    break;

  case 71: // stmt_while: "while" "(" expr ")" stmt
#line 414 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2379 "parser.cpp"
    break;

  case 72: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 419 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2385 "parser.cpp"
    break;

  case 73: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 424 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2391 "parser.cpp"
    break;

  case 74: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 429 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2397 "parser.cpp"
    break;

  case 75: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 431 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2403 "parser.cpp"
    break;

  case 76: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 436 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2409 "parser.cpp"
    break;

  case 77: // stmt_case: "case" expr_integer ":"
#line 441 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2415 "parser.cpp"
    break;

  case 78: // stmt_case: "case" expr_string ":"
#line 443 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2421 "parser.cpp"
    break;

  case 79: // stmt_default: "default" ":"
#line 448 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2427 "parser.cpp"
    break;

  case 80: // stmt_break: "break" ";"
#line 453 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2433 "parser.cpp"
    break;

  case 81: // stmt_continue: "continue" ";"
#line 458 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2439 "parser.cpp"
    break;

  case 82: // stmt_return: "return" expr ";"
#line 463 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2445 "parser.cpp"
    break;

  case 83: // stmt_return: "return" ";"
#line 465 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2451 "parser.cpp"
    break;

  case 84: // stmt_breakpoint: "breakpoint" ";"
#line 470 "parser.ypp"
        { yylhs.value.as < ast::stmt_breakpoint::ptr > () = std::make_unique<ast::stmt_breakpoint>(yylhs.location); }
#line 2457 "parser.cpp"
    break;

  case 85: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 475 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2463 "parser.cpp"
    break;

  case 86: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 480 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2469 "parser.cpp"
    break;

  case 87: // expr: expr_ternary
#line 484 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2475 "parser.cpp"
    break;

  case 88: // expr: expr_binary
#line 485 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2481 "parser.cpp"
    break;

  case 89: // expr: expr_primitive
#line 486 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2487 "parser.cpp"
    break;

  case 90: // expr_or_empty: expr
#line 490 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2493 "parser.cpp"
    break;

  case 91: // expr_or_empty: %empty
#line 491 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2499 "parser.cpp"
    break;

  case 92: // expr_assign: expr_object "=" expr
#line 496 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2505 "parser.cpp"
    break;

  case 93: // expr_assign: expr_object "|=" expr
#line 498 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2511 "parser.cpp"
    break;

  case 94: // expr_assign: expr_object "&=" expr
#line 500 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2517 "parser.cpp"
    break;

  case 95: // expr_assign: expr_object "^=" expr
#line 502 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2523 "parser.cpp"
    break;

  case 96: // expr_assign: expr_object "<<=" expr
#line 504 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2529 "parser.cpp"
    break;

  case 97: // expr_assign: expr_object ">>=" expr
#line 506 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2535 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object "+=" expr
#line 508 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2541 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "-=" expr
#line 510 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2547 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object "*=" expr
#line 512 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2553 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "/=" expr
#line 514 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2559 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "%=" expr
#line 516 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2565 "parser.cpp"
    break;

  case 103: // expr_increment: "++" expr_object
#line 521 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2571 "parser.cpp"
    break;

  case 104: // expr_increment: expr_object "++"
#line 523 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2577 "parser.cpp"
    break;

  case 105: // expr_decrement: "--" expr_object
#line 528 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2583 "parser.cpp"
    break;

  case 106: // expr_decrement: expr_object "--"
#line 530 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2589 "parser.cpp"
    break;

  case 107: // expr_ternary: expr "?" expr ":" expr
#line 535 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2595 "parser.cpp"
    break;

  case 108: // expr_binary: expr "||" expr
#line 540 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2601 "parser.cpp"
    break;

  case 109: // expr_binary: expr "&&" expr
#line 542 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2607 "parser.cpp"
    break;

  case 110: // expr_binary: expr "==" expr
#line 544 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2613 "parser.cpp"
    break;

  case 111: // expr_binary: expr "!=" expr
#line 546 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2619 "parser.cpp"
    break;

  case 112: // expr_binary: expr "<=" expr
#line 548 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2625 "parser.cpp"
    break;

  case 113: // expr_binary: expr ">=" expr
#line 550 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2631 "parser.cpp"
    break;

  case 114: // expr_binary: expr "<" expr
#line 552 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2637 "parser.cpp"
    break;

  case 115: // expr_binary: expr ">" expr
#line 554 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2643 "parser.cpp"
    break;

  case 116: // expr_binary: expr "|" expr
#line 556 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2649 "parser.cpp"
    break;

  case 117: // expr_binary: expr "&" expr
#line 558 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2655 "parser.cpp"
    break;

  case 118: // expr_binary: expr "^" expr
#line 560 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2661 "parser.cpp"
    break;

  case 119: // expr_binary: expr "<<" expr
#line 562 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2667 "parser.cpp"
    break;

  case 120: // expr_binary: expr ">>" expr
#line 564 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2673 "parser.cpp"
    break;

  case 121: // expr_binary: expr "+" expr
#line 566 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2679 "parser.cpp"
    break;

  case 122: // expr_binary: expr "-" expr
#line 568 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2685 "parser.cpp"
    break;

  case 123: // expr_binary: expr "*" expr
#line 570 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2691 "parser.cpp"
    break;

  case 124: // expr_binary: expr "/" expr
#line 572 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2697 "parser.cpp"
    break;

  case 125: // expr_binary: expr "%" expr
#line 574 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2703 "parser.cpp"
    break;

  case 126: // expr_primitive: expr_complement
#line 578 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 2709 "parser.cpp"
    break;

  case 127: // expr_primitive: expr_not
#line 579 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 2715 "parser.cpp"
    break;

  case 128: // expr_primitive: expr_call
#line 580 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 2721 "parser.cpp"
    break;

  case 129: // expr_primitive: expr_method
#line 581 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 2727 "parser.cpp"
    break;

  case 130: // expr_primitive: expr_add_array
#line 582 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_add_array::ptr > ()); }
#line 2733 "parser.cpp"
    break;

  case 131: // expr_primitive: expr_reference
#line 583 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 2739 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_array
#line 584 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 2745 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_field
#line 585 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 2751 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_size
#line 586 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 2757 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_paren
#line 587 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 2763 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_thisthread
#line 588 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_thisthread::ptr > ()); }
#line 2769 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_empty_array
#line 589 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 2775 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_undefined
#line 590 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 2781 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_game
#line 591 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 2787 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_self
#line 592 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 2793 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_anim
#line 593 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 2799 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_level
#line 594 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 2805 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_animation
#line 595 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 2811 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_animtree
#line 596 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animtree::ptr > ()); }
#line 2817 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_identifier
#line 597 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 2823 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_istring
#line 598 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 2829 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_string
#line 599 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 2835 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_color
#line 600 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_color::ptr > ()); }
#line 2841 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_vector
#line 601 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 2847 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_float
#line 602 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 2853 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_integer
#line 603 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 2859 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_false
#line 604 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 2865 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_true
#line 605 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 2871 "parser.cpp"
    break;

  case 154: // expr_complement: "~" expr
#line 610 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2877 "parser.cpp"
    break;

  case 155: // expr_not: "!" expr
#line 615 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2883 "parser.cpp"
    break;

  case 156: // expr_call: expr_function
#line 619 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2889 "parser.cpp"
    break;

  case 157: // expr_call: expr_pointer
#line 620 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2895 "parser.cpp"
    break;

  case 158: // expr_method: expr_object expr_function
#line 623 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 2901 "parser.cpp"
    break;

  case 159: // expr_method: expr_object expr_pointer
#line 624 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 2907 "parser.cpp"
    break;

  case 160: // expr_function: expr_identifier "(" expr_arguments ")"
#line 629 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 2913 "parser.cpp"
    break;

  case 161: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 631 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 2919 "parser.cpp"
    break;

  case 162: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 633 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 2925 "parser.cpp"
    break;

  case 163: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 635 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 2931 "parser.cpp"
    break;

  case 164: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 637 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 2937 "parser.cpp"
    break;

  case 165: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 639 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 2943 "parser.cpp"
    break;

  case 166: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 644 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 2949 "parser.cpp"
    break;

  case 167: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 646 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 2955 "parser.cpp"
    break;

  case 168: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 648 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 2961 "parser.cpp"
    break;

  case 169: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 650 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::builtin); }
#line 2967 "parser.cpp"
    break;

  case 170: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 655 "parser.ypp"
        { yylhs.value.as < ast::expr_add_array::ptr > () = std::make_unique<ast::expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ())); }
#line 2973 "parser.cpp"
    break;

  case 171: // expr_parameters: expr_parameters "," expr_identifier
#line 660 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 2979 "parser.cpp"
    break;

  case 172: // expr_parameters: expr_identifier
#line 662 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 2985 "parser.cpp"
    break;

  case 173: // expr_parameters: %empty
#line 664 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 2991 "parser.cpp"
    break;

  case 174: // expr_arguments: expr_arguments_no_empty
#line 669 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 2997 "parser.cpp"
    break;

  case 175: // expr_arguments: %empty
#line 671 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3003 "parser.cpp"
    break;

  case 176: // expr_arguments_no_empty: expr_arguments "," expr
#line 676 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3009 "parser.cpp"
    break;

  case 177: // expr_arguments_no_empty: expr
#line 678 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3015 "parser.cpp"
    break;

  case 178: // expr_reference: "::" expr_identifier
#line 683 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3021 "parser.cpp"
    break;

  case 179: // expr_reference: expr_path "::" expr_identifier
#line 685 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3027 "parser.cpp"
    break;

  case 180: // expr_array: expr_object "[" expr "]"
#line 690 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3033 "parser.cpp"
    break;

  case 181: // expr_field: expr_object "." expr_identifier
#line 695 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3039 "parser.cpp"
    break;

  case 182: // expr_size: expr_object ".size"
#line 700 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3045 "parser.cpp"
    break;

  case 183: // expr_paren: "(" expr ")"
#line 705 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3051 "parser.cpp"
    break;

  case 184: // expr_object: expr_call
#line 709 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3057 "parser.cpp"
    break;

  case 185: // expr_object: expr_method
#line 710 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3063 "parser.cpp"
    break;

  case 186: // expr_object: expr_array
#line 711 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3069 "parser.cpp"
    break;

  case 187: // expr_object: expr_field
#line 712 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3075 "parser.cpp"
    break;

  case 188: // expr_object: expr_game
#line 713 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3081 "parser.cpp"
    break;

  case 189: // expr_object: expr_self
#line 714 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3087 "parser.cpp"
    break;

  case 190: // expr_object: expr_anim
#line 715 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3093 "parser.cpp"
    break;

  case 191: // expr_object: expr_level
#line 716 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3099 "parser.cpp"
    break;

  case 192: // expr_object: expr_identifier
#line 717 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3105 "parser.cpp"
    break;

  case 193: // expr_thisthread: "thisthread"
#line 722 "parser.ypp"
        { yylhs.value.as < ast::expr_thisthread::ptr > () = std::make_unique<ast::expr_thisthread>(yylhs.location); }
#line 3111 "parser.cpp"
    break;

  case 194: // expr_empty_array: "[" "]"
#line 727 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3117 "parser.cpp"
    break;

  case 195: // expr_undefined: "undefined"
#line 732 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3123 "parser.cpp"
    break;

  case 196: // expr_game: "game"
#line 737 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3129 "parser.cpp"
    break;

  case 197: // expr_self: "self"
#line 742 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3135 "parser.cpp"
    break;

  case 198: // expr_anim: "anim"
#line 747 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3141 "parser.cpp"
    break;

  case 199: // expr_level: "level"
#line 752 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3147 "parser.cpp"
    break;

  case 200: // expr_animation: "%" "identifier"
#line 757 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3153 "parser.cpp"
    break;

  case 201: // expr_animtree: "#animtree"
#line 762 "parser.ypp"
        { yylhs.value.as < ast::expr_animtree::ptr > () = std::make_unique<ast::expr_animtree>(yylhs.location); }
#line 3159 "parser.cpp"
    break;

  case 202: // expr_identifier: "identifier"
#line 767 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3165 "parser.cpp"
    break;

  case 203: // expr_path: "path"
#line 772 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3171 "parser.cpp"
    break;

  case 204: // expr_path: expr_identifier
#line 774 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < ast::expr_identifier::ptr > ()->value); }
#line 3177 "parser.cpp"
    break;

  case 205: // expr_istring: "localized string"
#line 779 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3183 "parser.cpp"
    break;

  case 206: // expr_string: "string literal"
#line 784 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3189 "parser.cpp"
    break;

  case 207: // expr_color: "color"
#line 789 "parser.ypp"
        { yylhs.value.as < ast::expr_color::ptr > () = std::make_unique<ast::expr_color>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3195 "parser.cpp"
    break;

  case 208: // expr_vector: "(" expr "," expr "," expr ")"
#line 794 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3201 "parser.cpp"
    break;

  case 209: // expr_float: "-" "float"
#line 799 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3207 "parser.cpp"
    break;

  case 210: // expr_float: "float"
#line 801 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3213 "parser.cpp"
    break;

  case 211: // expr_integer: "-" "integer"
#line 806 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3219 "parser.cpp"
    break;

  case 212: // expr_integer: "integer"
#line 808 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3225 "parser.cpp"
    break;

  case 213: // expr_false: "false"
#line 813 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3231 "parser.cpp"
    break;

  case 214: // expr_true: "true"
#line 818 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3237 "parser.cpp"
    break;


#line 3241 "parser.cpp"

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
    "end of file", "error", "invalid token", "/#", "#/", "#inline",
  "#include", "#using_animtree", "#animtree", "endon", "notify", "wait",
  "waittill", "waittillmatch", "waittillframeend", "if", "else", "do",
  "while", "for", "foreach", "in", "switch", "case", "default", "break",
  "continue", "return", "breakpoint", "prof_begin", "prof_end", "thread",
  "childthread", "thisthread", "call", "true", "false", "undefined",
  ".size", "game", "self", "anim", "level", "(", ")", "{", "}", "[", "]",
  ",", ".", "::", ":", ";", "?", "++", "--", "<<", ">>", "||", "&&", "==",
  "!=", "<=", ">=", "<", ">", "!", "~", "=", "+=", "-=", "*=", "/=", "%=",
  "|=", "&=", "^=", ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/", "%",
  "path", "identifier", "string literal", "localized string", "color",
  "float", "integer", "ADD_ARRAY", "THEN", "TERN", "NEG", "ANIMREF",
  "PREINC", "PREDEC", "POSTINC", "POSTDEC", "$accept", "root", "program",
  "inline", "include", "declaration", "decl_usingtree", "decl_constant",
  "decl_thread", "stmt", "stmt_dev", "stmt_block", "stmt_list",
  "stmt_expr", "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify",
  "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_if", "stmt_ifelse", "stmt_while",
  "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case",
  "stmt_default", "stmt_break", "stmt_continue", "stmt_return",
  "stmt_breakpoint", "stmt_prof_begin", "stmt_prof_end", "expr",
  "expr_or_empty", "expr_assign", "expr_increment", "expr_decrement",
  "expr_ternary", "expr_binary", "expr_primitive", "expr_complement",
  "expr_not", "expr_call", "expr_method", "expr_function", "expr_pointer",
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

#if IW7DEBUG
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
#if IW7DEBUG
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
#if IW7DEBUG
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


  const short parser::yypact_ninf_ = -263;

  const short parser::yytable_ninf_ = -205;

  const short
  parser::yypact_[] =
  {
      34,  -263,  -263,   -22,   -22,   -28,  -263,    19,    34,  -263,
    -263,  -263,  -263,  -263,  -263,   -17,  -263,  -263,    -4,     4,
     -48,  -263,  -263,  -263,  -263,   -38,  1180,  -263,  -263,  -263,
      15,    33,  -263,  -263,   -33,   -24,  -263,     6,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  1180,   630,   -38,  1180,  1180,
     -15,   -16,  -263,  -263,  -263,  -263,  2051,  -263,  -263,  -263,
    -263,  -263,   -14,    78,  -263,  -263,  -263,  -263,   532,   652,
    -263,  -263,   678,  -263,  -263,  -263,   713,   727,   756,   866,
    -263,  -263,    57,    32,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,    37,    54,   -38,    56,    71,    62,    73,    88,
      90,    93,  1377,   630,  -263,  2134,    98,   116,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  1180,  1180,  1180,  1180,  1180,
    1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,
    1180,  1180,  1180,  1180,  -263,  1244,   -38,  -263,  -263,    94,
     110,  1180,   -38,  -263,   835,  -263,  -263,  1180,  1180,   -38,
    1180,  1180,   -38,  1180,  -263,  1180,  1176,  1180,  -263,  2016,
     115,   115,  2165,  1321,   948,   948,   271,   271,   271,   271,
     747,  2206,  2175,    84,    84,  -263,  -263,  -263,  1821,  -263,
     -38,    48,  -263,   122,   911,  1180,   119,   125,  1089,   131,
     132,   133,   134,    21,   135,   136,   137,  1116,   138,   143,
     151,  -263,   149,   605,   605,  -263,  -263,  -263,   962,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,   152,   153,   154,   156,   157,  -263,  -263,  1292,
    -263,  -263,  -263,  -263,     3,  1861,    49,   172,  1901,    52,
     173,  1941,  1980,   178,  2134,  1180,  -263,   122,  -263,  1180,
    -263,  1038,  2086,  -263,  1180,   202,  1180,    29,   -38,  1180,
     127,   175,   176,  -263,  -263,  -263,  -263,  2121,  -263,  1180,
    1180,  1180,  -263,  -263,    -2,    -2,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,   186,   188,   189,   193,  -263,  -263,  1180,
    1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,  1180,
     187,  -263,  1180,   190,  -263,  1180,   194,  1180,   198,  2134,
      75,  -263,  -263,  1543,   200,  1577,   184,  -263,  -263,  -263,
    1341,     1,  1611,  -263,  -263,  -263,    83,    85,  1176,  1180,
    1180,  1180,  1180,  2134,  2134,  2134,  2134,  2134,  2134,  2134,
    2134,  2134,  2134,  2134,   201,    86,   204,    89,   206,  1645,
    1180,  -263,  1089,  1180,  1089,  1180,  1180,   -38,    54,   197,
     199,  1679,  1421,  1465,  1509,  1180,  -263,  1180,  -263,  1180,
    -263,   106,   235,  1713,  -263,  2134,   203,  1747,   232,  -263,
    -263,  -263,   207,   209,  1180,   210,  1180,   212,  1180,   107,
     113,   114,  -263,  1089,   213,    29,  1089,  1180,  -263,  -263,
     227,  -263,   228,  -263,   231,  -263,  -263,  -263,  -263,  -263,
     237,  -263,  1781,   226,   230,   233,  1089,  1089,  -263,  -263,
    -263,  -263,  -263
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   202,     0,     2,     7,
       8,     9,    14,    15,    16,     0,   203,   204,     0,     0,
       0,     1,     4,     5,     6,   173,     0,    10,    11,   206,
       0,     0,   172,   201,     0,     0,   193,     0,   214,   213,
     195,   196,   197,   198,   199,     0,   175,     0,     0,     0,
       0,     0,   205,   207,   210,   212,     0,    87,    88,    89,
     126,   127,   128,   129,   156,   157,   130,   131,   132,   133,
     134,   135,     0,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,     0,   146,   147,   148,   149,   150,   151,
     152,   153,     0,     0,     0,     0,   204,     0,     0,   204,
       0,     0,     0,   175,   194,   177,     0,   174,   178,   155,
     154,   209,   211,   200,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,     0,     0,   158,   159,   204,
       0,   175,     0,    17,     0,    19,   171,     0,   175,     0,
       0,   175,     0,     0,   183,     0,   177,     0,   170,     0,
     119,   120,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   121,   122,   123,   124,   125,     0,   181,
       0,     0,   174,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,     0,     0,     0,    50,    20,    21,     0,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,     0,     0,     0,   184,   185,   186,   187,     0,
     188,   189,   190,   191,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   176,     0,   180,     0,   160,   175,
      46,     0,     0,    68,     0,     0,     0,    54,     0,     0,
       0,     0,     0,    79,    80,    81,    83,     0,    84,   175,
     175,     0,   184,   185,   103,   105,    47,    49,    57,    58,
      59,    55,    56,     0,     0,     0,     0,   104,   106,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   162,   175,     0,   164,   175,     0,     0,     0,   107,
       0,    45,    63,     0,     0,     0,     0,    51,    52,    53,
       0,     0,     0,    78,    77,    82,     0,     0,     0,     0,
       0,     0,     0,    92,    98,    99,   100,   101,   102,    93,
      94,    95,    97,    96,     0,     0,     0,     0,     0,     0,
     175,   161,     0,     0,     0,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   175,   163,   175,   165,   175,
     208,     0,    69,     0,    71,    90,     0,     0,     0,    76,
      85,    86,     0,     0,   175,     0,   175,     0,   175,     0,
       0,     0,   166,     0,     0,    54,     0,     0,    60,    62,
     174,    65,   174,    67,   174,   167,   168,   169,    70,    72,
       0,    74,     0,     0,     0,     0,     0,     0,    61,    64,
      66,    73,    75
  };

  const short
  parser::yypgoto_[] =
  {
    -263,  -263,  -263,   279,   281,   282,  -263,  -263,  -263,  -181,
    -263,   -91,   108,  -114,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,   185,  -263,  -262,
    -257,  -251,  -263,  -263,  -263,  -263,  -263,   -82,    70,   -66,
     -61,  -263,  -263,  -120,   -45,  -263,   181,   192,  -263,  -263,
     253,  -263,  -263,  -263,   327,   365,   373,   421,  -263,  -263,
       0,     9,  -263,   -11,  -263,  -263,  -263,   102,  -263,  -263
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     7,     8,     9,    10,    11,    12,    13,    14,   205,
     206,   207,   208,   326,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   105,   386,   232,
     233,   234,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    31,   106,   182,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91
  };

  const short
  parser::yytable_[] =
  {
      15,   107,   145,    17,    17,   327,   137,   265,    15,    30,
     328,   138,    18,    19,    95,    20,   329,  -184,  -184,    21,
    -184,   181,   366,    98,  -184,    32,    25,   287,   246,    34,
      35,   249,    37,  -184,    96,    99,  -184,     1,     2,     3,
       4,     5,    29,    97,   100,   135,   141,   108,   136,    27,
     367,     6,    26,   101,  -204,    16,     6,    28,   107,    92,
      34,    35,   235,    37,    16,     6,    16,     6,    41,    42,
      43,    44,   139,   113,  -184,  -184,   202,    93,   111,   112,
     287,   140,    94,   142,   203,   204,    16,     6,  -192,  -192,
     143,  -192,   258,   311,   146,  -192,   314,   157,   157,   144,
     141,   157,   235,   147,  -192,   270,   235,  -192,  -204,  -185,
    -185,    29,  -185,   149,   148,    55,  -185,    16,     6,   361,
     150,   282,   282,     6,   157,  -185,   235,   369,  -185,   370,
     376,   151,   157,   378,   157,   157,   179,   141,   157,   320,
     153,   152,   183,   327,   244,  -192,  -192,   157,   328,   247,
     402,   415,   250,   140,   329,   157,   157,   416,   417,   336,
     337,   180,   157,   157,   158,   259,  -185,  -185,   264,   131,
     132,   133,   263,   137,   266,   267,   268,   269,   138,   235,
     257,   382,   271,   384,   244,   282,   279,   273,   244,   274,
     275,   278,   355,   140,   280,   357,   281,   140,   129,   130,
     131,   132,   133,   244,   244,   288,   289,   290,   244,   291,
     292,    56,   140,   140,   236,   312,   315,   140,   137,   137,
     324,   112,   418,   138,   138,   421,   318,   333,   334,   339,
     102,   340,   341,   109,   110,   354,   342,   365,   356,   139,
     381,   360,   358,   363,   375,   431,   432,   377,   140,   379,
     390,   403,   391,   407,   236,   399,   405,   400,   236,   401,
     408,   244,   409,   411,   137,   413,   419,   244,   331,   138,
     140,   423,   424,   283,   283,   425,   140,   389,   236,   428,
     235,   426,   235,   429,   139,   139,   430,    22,   156,    23,
      24,   420,   261,   140,   140,   272,     0,     0,     0,     0,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,     0,
     178,   235,     0,   282,   235,   237,     0,     0,   116,   117,
     139,   236,   245,     0,     0,   248,   238,   283,   251,   140,
     252,     0,   254,     0,   235,   235,     0,     0,     0,   410,
       0,   412,     0,   414,   129,   130,   131,   132,   133,     0,
       0,     0,   244,     0,   244,   237,     0,   388,     0,   237,
     262,   140,     0,   140,     0,     0,   238,     0,     0,     0,
     238,     0,   277,     0,   237,   237,     0,     0,     0,   237,
       0,     0,     0,     0,     0,   238,   238,   239,     0,     0,
     238,     0,     0,   244,     0,   244,   244,     0,     0,     0,
       0,     0,   140,     0,   140,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   244,   244,     0,     0,
       0,     0,   236,     0,   236,   140,   140,   239,     0,     0,
     319,   239,   237,     0,     0,     0,     0,     0,   237,   323,
       0,   325,     0,   238,   332,     0,   284,   285,     0,   238,
       0,   239,     0,     0,     0,     0,   338,     0,     0,     0,
       0,   240,     0,   236,     0,   283,   236,     0,     0,     0,
       0,     0,     0,     0,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,     0,   236,   236,     0,     0,
       0,     0,   359,     0,     0,     0,     0,     0,     0,   241,
       0,   240,     0,     0,   239,   240,     0,   242,     0,     0,
     330,     0,     0,     0,   371,   372,   373,   374,     0,     0,
     240,   240,     0,     0,     0,   240,     0,     0,     0,     0,
       0,     0,     0,   237,     0,   237,     0,     0,   383,   241,
     385,   387,     0,   241,   238,     0,   238,   242,     0,     0,
       0,   242,     0,  -186,  -186,   243,  -186,     0,   241,   241,
    -186,     0,     0,   241,     0,     0,   242,   242,     0,  -186,
       0,   242,  -186,     0,   237,     0,   237,   237,   240,     0,
       0,     0,   422,     0,   240,   238,     0,   238,   238,     0,
       0,     0,     0,     0,     0,   243,     0,   237,   237,   243,
       0,     0,     0,     0,     0,   239,     0,   239,   238,   238,
    -186,  -186,     0,     0,   243,   243,   241,     0,     0,   243,
       0,     0,   241,     0,   242,     0,    34,    35,    33,    37,
     242,     0,     0,     0,    41,    42,    43,    44,     0,     0,
       0,     0,   202,     0,     0,     0,   239,     0,   330,   239,
       0,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,    45,     0,     0,     0,   103,   104,   239,
     239,    47,   243,  -187,  -187,     0,  -187,     0,   243,   240,
    -187,   240,     0,    16,     6,     0,     0,    48,    49,  -187,
       0,     0,  -187,     0,     0,     0,     0,     0,     0,    34,
      35,     0,    37,     0,    50,     0,   134,    51,    16,     6,
      29,    52,    53,    54,    55,   135,     0,   241,   136,   241,
     240,     0,   240,   240,     0,   242,     0,   242,     0,     0,
    -187,  -187,     0,     0,  -188,  -188,     0,  -188,     0,     0,
       0,  -188,     0,   240,   240,     0,     0,     0,  -189,  -189,
    -188,  -189,     0,  -188,     0,  -189,    16,     6,   241,     0,
     241,   241,     0,     0,  -189,     0,   242,  -189,   242,   242,
       0,     0,     0,   243,     0,   243,     0,  -190,  -190,     0,
    -190,   241,   241,     0,  -190,     0,     0,     0,     0,   242,
     242,  -188,  -188,  -190,   116,   117,  -190,     0,   120,   121,
     122,   123,   124,   125,     0,  -189,  -189,     0,     0,     0,
       0,     0,     0,     0,   243,     0,   243,   243,   127,   128,
     129,   130,   131,   132,   133,     0,     0,     0,   184,     0,
       0,     0,     0,     0,  -190,  -190,   185,   243,   243,   186,
     187,     0,   188,   189,   190,   191,     0,   192,   193,   194,
     195,   196,   197,   198,   199,   200,    34,    35,     0,    37,
       0,     0,     0,     0,    41,    42,    43,    44,     0,     0,
     144,   201,   202,     0,     0,     0,     0,     0,     0,     0,
     203,   204,     0,     0,     0,     0,     0,  -191,  -191,     0,
    -191,     0,     0,     0,  -191,     0,     0,     0,     0,     0,
       0,     0,     0,  -191,   184,   260,  -191,     0,     0,     0,
       0,     0,   185,    16,     6,   186,   187,     0,   188,   189,
     190,   191,     0,   192,   193,   194,   195,   196,   197,   198,
     199,   200,    34,    35,     0,    37,     0,     0,     0,     0,
      41,    42,    43,    44,  -191,  -191,   144,     0,   202,     0,
       0,     0,     0,     0,     0,   184,   203,   204,     0,     0,
       0,     0,     0,   185,     0,     0,   186,   187,     0,   188,
     189,   190,   191,     0,   192,   193,   194,   195,   196,   197,
     198,   199,   200,    34,    35,     0,    37,     0,     0,    16,
       6,    41,    42,    43,    44,   116,   117,   144,   286,   202,
       0,   122,   123,   124,   125,     0,     0,   203,   204,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   129,   130,   131,   132,   133,     0,     0,     0,     0,
       0,   184,   321,     0,     0,     0,     0,     0,     0,   185,
      16,     6,   186,   187,     0,   188,   189,   190,   191,     0,
     192,   193,   194,   195,   196,   197,   198,   199,   200,    34,
      35,     0,    37,     0,     0,     0,     0,    41,    42,    43,
      44,     0,     0,   144,     0,   202,     0,     0,     0,     0,
       0,     0,   184,   203,   204,     0,     0,     0,     0,     0,
     185,     0,     0,   186,   187,     0,   188,   189,   190,   191,
       0,   192,   193,   194,   195,   196,   197,   198,   199,   200,
      34,    35,     0,    37,    33,     0,    16,     6,    41,    42,
      43,    44,     0,     0,   144,     0,   202,     0,     0,     0,
       0,     0,     0,     0,   203,   204,     0,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,    45,
       0,     0,     0,    46,     0,     0,     0,    47,     0,   276,
       0,     0,     0,     0,     0,     0,     0,    16,     6,     0,
       0,     0,     0,    48,    49,     0,     0,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,    51,    16,     6,    29,    52,    53,    54,
      55,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,    45,   253,     0,     0,    46,     0,     0,
     115,    47,     0,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,    48,    49,     0,
       0,     0,    33,     0,     0,     0,   126,   127,   128,   129,
     130,   131,   132,   133,    50,     0,     0,    51,    16,     6,
      29,    52,    53,    54,    55,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,    43,    44,    45,     0,     0,
       0,   103,     0,     0,     0,    47,     0,     0,     0,     0,
       0,   293,   294,     0,   295,   296,     0,     0,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,     0,    37,     0,    50,     0,
       0,    51,    16,     6,    29,    52,    53,    54,    55,   135,
       0,     0,   136,     0,     0,     0,     0,   297,   298,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,    34,    35,     0,    37,     0,     0,   116,   117,
      16,     6,   120,   121,   122,   123,   124,   125,   135,     0,
       0,   136,     0,     0,     0,     0,   297,   298,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,     0,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   154,     0,     0,     0,     0,   155,     0,     0,    16,
       6,   115,     0,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   126,   127,   128,
     129,   130,   131,   132,   133,   393,     0,     0,     0,     0,
     394,     0,     0,     0,     0,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   395,
       0,     0,     0,     0,   396,     0,     0,     0,     0,   115,
       0,     0,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   126,   127,   128,   129,   130,
     131,   132,   133,   397,     0,     0,     0,     0,   398,     0,
       0,     0,     0,   115,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   362,     0,   126,
     127,   128,   129,   130,   131,   132,   133,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   364,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   115,     0,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   368,     0,   126,   127,   128,
     129,   130,   131,   132,   133,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   380,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   115,
       0,     0,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   392,     0,   126,   127,   128,   129,   130,
     131,   132,   133,   115,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   404,     0,   126,
     127,   128,   129,   130,   131,   132,   133,   115,     0,     0,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   406,     0,   126,   127,   128,   129,   130,   131,   132,
     133,   115,     0,     0,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   427,     0,   126,   127,   128,
     129,   130,   131,   132,   133,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   256,
       0,     0,     0,     0,     0,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   310,
       0,     0,     0,     0,     0,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   313,
       0,     0,     0,     0,     0,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   316,
       0,     0,     0,     0,     0,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   317,
       0,     0,     0,     0,   115,     0,     0,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   255,     0,
     115,     0,     0,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   114,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   322,
     115,     0,     0,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   335,   115,     0,     0,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   115,     0,
       0,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,     0,
       0,     0,     0,     0,   126,   127,   128,   129,   130,   131,
     132,   133,   116,   117,     0,   119,   120,   121,   122,   123,
     124,   125,   116,   117,     0,     0,   120,   121,   122,   123,
     124,   125,     0,     0,     0,   126,   127,   128,   129,   130,
     131,   132,   133,     0,     0,     0,   127,     0,   129,   130,
     131,   132,   133,   116,   117,     0,     0,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
     130,   131,   132,   133
  };

  const short
  parser::yycheck_[] =
  {
       0,    46,    93,     3,     4,   267,    72,   188,     8,    20,
     267,    72,     3,     4,    47,    43,   267,    31,    32,     0,
      34,   141,    21,    47,    38,    25,    43,   208,   148,    31,
      32,   151,    34,    47,    34,    35,    50,     3,     4,     5,
       6,     7,    90,    34,    35,    47,    43,    47,    50,    53,
      49,    89,    69,    47,    51,    88,    89,    53,   103,    44,
      31,    32,   144,    34,    88,    89,    88,    89,    39,    40,
      41,    42,    72,    89,    88,    89,    47,    44,    93,    94,
     261,    72,    49,    51,    55,    56,    88,    89,    31,    32,
      53,    34,    44,    44,    94,    38,    44,    49,    49,    45,
      43,    49,   184,    47,    47,    84,   188,    50,    51,    31,
      32,    90,    34,    51,    43,    94,    38,    88,    89,    44,
      47,   203,   204,    89,    49,    47,   208,    44,    50,    44,
      44,    43,    49,    44,    49,    49,   136,    43,    49,   259,
      47,    51,   142,   405,   144,    88,    89,    49,   405,   149,
      44,    44,   152,   144,   405,    49,    49,    44,    44,   279,
     280,    51,    49,    49,    48,    43,    88,    89,    43,    85,
      86,    87,    53,   239,    43,    43,    43,    43,   239,   261,
     180,   362,   193,   364,   184,   267,    43,    52,   188,    53,
      53,    53,   312,   184,    43,   315,    47,   188,    83,    84,
      85,    86,    87,   203,   204,    53,    53,    53,   208,    53,
      53,    26,   203,   204,   144,    43,    43,   208,   284,   285,
      18,    94,   403,   284,   285,   406,    48,    52,    52,    43,
      45,    43,    43,    48,    49,    48,    43,    53,    48,   239,
     360,    43,    48,    43,    43,   426,   427,    43,   239,    43,
      53,    16,    53,    21,   184,   375,    53,   377,   188,   379,
      53,   261,    53,    53,   330,    53,    53,   267,   268,   330,
     261,    44,    44,   203,   204,    44,   267,   368,   208,    53,
     362,    44,   364,    53,   284,   285,    53,     8,   103,     8,
       8,   405,   184,   284,   285,   193,    -1,    -1,    -1,    -1,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,    -1,
     135,   403,    -1,   405,   406,   144,    -1,    -1,    57,    58,
     330,   261,   147,    -1,    -1,   150,   144,   267,   153,   330,
     155,    -1,   157,    -1,   426,   427,    -1,    -1,    -1,   394,
      -1,   396,    -1,   398,    83,    84,    85,    86,    87,    -1,
      -1,    -1,   362,    -1,   364,   184,    -1,   367,    -1,   188,
     185,   362,    -1,   364,    -1,    -1,   184,    -1,    -1,    -1,
     188,    -1,   197,    -1,   203,   204,    -1,    -1,    -1,   208,
      -1,    -1,    -1,    -1,    -1,   203,   204,   144,    -1,    -1,
     208,    -1,    -1,   403,    -1,   405,   406,    -1,    -1,    -1,
      -1,    -1,   403,    -1,   405,   406,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   426,   427,    -1,    -1,
      -1,    -1,   362,    -1,   364,   426,   427,   184,    -1,    -1,
     255,   188,   261,    -1,    -1,    -1,    -1,    -1,   267,   264,
      -1,   266,    -1,   261,   269,    -1,   203,   204,    -1,   267,
      -1,   208,    -1,    -1,    -1,    -1,   281,    -1,    -1,    -1,
      -1,   144,    -1,   403,    -1,   405,   406,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,    -1,   426,   427,    -1,    -1,
      -1,    -1,   317,    -1,    -1,    -1,    -1,    -1,    -1,   144,
      -1,   184,    -1,    -1,   261,   188,    -1,   144,    -1,    -1,
     267,    -1,    -1,    -1,   339,   340,   341,   342,    -1,    -1,
     203,   204,    -1,    -1,    -1,   208,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   362,    -1,   364,    -1,    -1,   363,   184,
     365,   366,    -1,   188,   362,    -1,   364,   184,    -1,    -1,
      -1,   188,    -1,    31,    32,   144,    34,    -1,   203,   204,
      38,    -1,    -1,   208,    -1,    -1,   203,   204,    -1,    47,
      -1,   208,    50,    -1,   403,    -1,   405,   406,   261,    -1,
      -1,    -1,   407,    -1,   267,   403,    -1,   405,   406,    -1,
      -1,    -1,    -1,    -1,    -1,   184,    -1,   426,   427,   188,
      -1,    -1,    -1,    -1,    -1,   362,    -1,   364,   426,   427,
      88,    89,    -1,    -1,   203,   204,   261,    -1,    -1,   208,
      -1,    -1,   267,    -1,   261,    -1,    31,    32,     8,    34,
     267,    -1,    -1,    -1,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    -1,   403,    -1,   405,   406,
      -1,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    48,   426,
     427,    51,   261,    31,    32,    -1,    34,    -1,   267,   362,
      38,   364,    -1,    88,    89,    -1,    -1,    67,    68,    47,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    -1,    34,    -1,    84,    -1,    38,    87,    88,    89,
      90,    91,    92,    93,    94,    47,    -1,   362,    50,   364,
     403,    -1,   405,   406,    -1,   362,    -1,   364,    -1,    -1,
      88,    89,    -1,    -1,    31,    32,    -1,    34,    -1,    -1,
      -1,    38,    -1,   426,   427,    -1,    -1,    -1,    31,    32,
      47,    34,    -1,    50,    -1,    38,    88,    89,   403,    -1,
     405,   406,    -1,    -1,    47,    -1,   403,    50,   405,   406,
      -1,    -1,    -1,   362,    -1,   364,    -1,    31,    32,    -1,
      34,   426,   427,    -1,    38,    -1,    -1,    -1,    -1,   426,
     427,    88,    89,    47,    57,    58,    50,    -1,    61,    62,
      63,    64,    65,    66,    -1,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   403,    -1,   405,   406,    81,    82,
      83,    84,    85,    86,    87,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    88,    89,    11,   426,   427,    14,
      15,    -1,    17,    18,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,
      34,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,     3,     4,    50,    -1,    -1,    -1,
      -1,    -1,    11,    88,    89,    14,    15,    -1,    17,    18,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    -1,    -1,    -1,    -1,
      39,    40,    41,    42,    88,    89,    45,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    55,    56,    -1,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    14,    15,    -1,    17,
      18,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    -1,    -1,    88,
      89,    39,    40,    41,    42,    57,    58,    45,    46,    47,
      -1,    63,    64,    65,    66,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,    11,
      88,    89,    14,    15,    -1,    17,    18,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    -1,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    55,    56,    -1,    -1,    -1,    -1,    -1,
      11,    -1,    -1,    14,    15,    -1,    17,    18,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,     8,    -1,    88,    89,    39,    40,
      41,    42,    -1,    -1,    45,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    -1,    31,    32,    33,
      34,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    -1,
      -1,    -1,    -1,    67,    68,    -1,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    87,    88,    89,    90,    91,    92,    93,
      94,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    48,    -1,    -1,    47,    -1,    -1,
      54,    51,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,     8,    -1,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    84,    -1,    -1,    87,    88,    89,
      90,    91,    92,    93,    94,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,     9,    10,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    -1,    34,    -1,    84,    -1,
      -1,    87,    88,    89,    90,    91,    92,    93,    94,    47,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    31,    32,    -1,    34,    -1,    -1,    57,    58,
      88,    89,    61,    62,    63,    64,    65,    66,    47,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    88,
      89,    54,    -1,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    44,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    44,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    44,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    54,    -1,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    80,
      81,    82,    83,    84,    85,    86,    87,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    54,    -1,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    54,
      -1,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    54,    -1,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    80,
      81,    82,    83,    84,    85,    86,    87,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    54,    -1,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    48,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    48,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    48,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    48,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    49,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    52,    -1,
      54,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    53,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    82,    83,    84,    85,    86,    87,    53,
      54,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    53,    54,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    54,    -1,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    80,    81,    82,    83,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    57,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    57,    58,    -1,    -1,    61,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    80,    81,    82,    83,    84,
      85,    86,    87,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    86,    87,    57,    58,    -1,    -1,    61,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      84,    85,    86,    87
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,    89,   105,   106,   107,
     108,   109,   110,   111,   112,   174,    88,   174,   175,   175,
      43,     0,   107,   108,   109,    43,    69,    53,    53,    90,
     177,   156,   174,     8,    31,    32,    33,    34,    35,    36,
      37,    39,    40,    41,    42,    43,    47,    51,    67,    68,
      84,    87,    91,    92,    93,    94,   141,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,    44,    44,    49,    47,   174,   175,    47,   174,
     175,    47,   141,    47,    48,   141,   157,   158,   174,   141,
     141,    93,    94,    89,    53,    54,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    80,    81,    82,    83,
      84,    85,    86,    87,    38,    47,    50,   153,   154,   174,
     175,    43,    51,    53,    45,   115,   174,    47,    43,    51,
      47,    43,    51,    47,    44,    49,   141,    49,    48,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   174,
      51,   157,   158,   174,     3,    11,    14,    15,    17,    18,
      19,    20,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    46,    47,    55,    56,   113,   114,   115,   116,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   143,   144,   145,   151,   152,   160,   161,   164,
     168,   169,   170,   171,   174,   141,   157,   174,   141,   157,
     174,   141,   141,    48,   141,    52,    48,   174,    44,    43,
       4,   116,   141,    53,    43,   113,    43,    43,    43,    43,
      84,   177,   181,    52,    53,    53,    53,   141,    53,    43,
      43,    47,   151,   152,   164,   164,    46,   113,    53,    53,
      53,    53,    53,     9,    10,    12,    13,    55,    56,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      48,    44,    43,    48,    44,    43,    48,    49,    48,   141,
     157,     4,    53,   141,    18,   141,   117,   143,   144,   145,
     164,   174,   141,    52,    52,    53,   157,   157,   141,    43,
      43,    43,    43,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,    48,   157,    48,   157,    48,   141,
      43,    44,    44,    43,    44,    53,    21,    49,    44,    44,
      44,   141,   141,   141,   141,    43,    44,    43,    44,    43,
      44,   157,   113,   141,   113,   141,   142,   141,   174,   115,
      53,    53,    44,    44,    49,    44,    49,    44,    49,   157,
     157,   157,    44,    16,    44,    53,    44,    21,    53,    53,
     158,    53,   158,    53,   158,    44,    44,    44,   113,    53,
     117,   113,   141,    44,    44,    44,    44,    44,    53,    53,
      53,   113,   113
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   104,   105,   105,   106,   106,   106,   106,   106,   106,
     107,   108,   109,   109,   109,   109,   109,   110,   111,   112,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   117,   117,   118,   118,   119,   119,   119,
     120,   121,   121,   122,   123,   123,   124,   124,   125,   126,
     127,   128,   129,   130,   131,   131,   132,   133,   133,   134,
     135,   136,   137,   137,   138,   139,   140,   141,   141,   141,
     142,   142,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   144,   144,   145,   145,   146,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   149,   150,   151,   151,   152,   152,
     153,   153,   153,   153,   153,   153,   154,   154,   154,   154,
     155,   156,   156,   156,   157,   157,   158,   158,   159,   159,
     160,   161,   162,   163,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   175,   176,   177,   178,   179,   180,
     180,   181,   181,   182,   183
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     5,     4,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     3,     2,     2,
       1,     1,     1,     1,     0,     2,     2,     2,     2,     2,
       6,     8,     6,     3,     8,     6,     8,     6,     2,     5,
       7,     5,     7,     9,     7,     9,     5,     3,     3,     2,
       2,     2,     3,     2,     2,     5,     5,     1,     1,     1,
       1,     0,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     2,     2,
       4,     6,     5,     7,     5,     7,     8,     9,     9,     9,
       3,     3,     1,     0,     1,     0,     3,     1,     2,     3,
       4,     3,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     7,     2,
       1,     2,     1,     1,     1
  };




#if IW7DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   243,   243,   244,   248,   250,   252,   254,   256,   258,
     263,   267,   272,   273,   274,   275,   276,   280,   285,   290,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   323,   324,   328,   329,   333,
     335,   340,   342,   344,   347,   351,   353,   358,   360,   362,
     367,   372,   374,   379,   384,   386,   391,   393,   398,   403,
     408,   413,   418,   423,   428,   430,   435,   440,   442,   447,
     452,   457,   462,   464,   469,   474,   479,   484,   485,   486,
     490,   491,   495,   497,   499,   501,   503,   505,   507,   509,
     511,   513,   515,   520,   522,   527,   529,   534,   539,   541,
     543,   545,   547,   549,   551,   553,   555,   557,   559,   561,
     563,   565,   567,   569,   571,   573,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   609,   614,   619,   620,   623,   624,
     628,   630,   632,   634,   636,   638,   643,   645,   647,   649,
     654,   659,   661,   664,   668,   671,   675,   677,   682,   684,
     689,   694,   699,   704,   709,   710,   711,   712,   713,   714,
     715,   716,   717,   721,   726,   731,   736,   741,   746,   751,
     756,   761,   766,   771,   773,   778,   783,   788,   793,   798,
     800,   805,   807,   812,   817
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
#endif // IW7DEBUG


#line 13 "parser.ypp"
} } } // xsk::gsc::iw7
#line 4483 "parser.cpp"

#line 821 "parser.ypp"


void xsk::gsc::iw7::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
