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
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
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

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.YY_MOVE_OR_COPY< ast::expr_thisthread::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.YY_MOVE_OR_COPY< ast::expr_true::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        value.YY_MOVE_OR_COPY< ast::expr_tuple::ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
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

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.move< ast::expr_thisthread::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.move< ast::expr_true::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        value.move< ast::expr_tuple::ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
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

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.copy< ast::expr_thisthread::ptr > (that.value);
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.copy< ast::expr_true::ptr > (that.value);
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        value.copy< ast::expr_tuple::ptr > (that.value);
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
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
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

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.move< ast::expr_thisthread::ptr > (that.value);
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.move< ast::expr_true::ptr > (that.value);
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        value.move< ast::expr_tuple::ptr > (that.value);
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
  parser::yypop_ (int n) YY_NOEXCEPT
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
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
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

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
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

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        yylhs.value.emplace< ast::expr_thisthread::ptr > ();
        break;

      case symbol_kind::S_expr_true: // expr_true
        yylhs.value.emplace< ast::expr_true::ptr > ();
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        yylhs.value.emplace< ast::expr_tuple::ptr > ();
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
#line 261 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < ast::program::ptr > ()); }
#line 2020 "parser.cpp"
    break;

  case 3: // root: %empty
#line 262 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 2026 "parser.cpp"
    break;

  case 4: // program: program inline
#line 267 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 2032 "parser.cpp"
    break;

  case 5: // program: program include
#line 269 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2038 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 271 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2044 "parser.cpp"
    break;

  case 7: // program: inline
#line 273 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 2050 "parser.cpp"
    break;

  case 8: // program: include
#line 275 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2056 "parser.cpp"
    break;

  case 9: // program: declaration
#line 277 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2062 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 281 "parser.ypp"
                                 { lexer.push_header(yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2068 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 286 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2074 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 290 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2080 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 291 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2086 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 292 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2092 "parser.cpp"
    break;

  case 15: // declaration: decl_constant
#line 293 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_constant = std::move(yystack_[0].value.as < ast::decl_constant::ptr > ()); }
#line 2098 "parser.cpp"
    break;

  case 16: // declaration: decl_thread
#line 294 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2104 "parser.cpp"
    break;

  case 17: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 299 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2110 "parser.cpp"
    break;

  case 18: // decl_constant: expr_identifier "=" expr ";"
#line 304 "parser.ypp"
        { yylhs.value.as < ast::decl_constant::ptr > () = std::make_unique<ast::decl_constant>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2116 "parser.cpp"
    break;

  case 19: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 309 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2122 "parser.cpp"
    break;

  case 20: // stmt: stmt_block
#line 313 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2128 "parser.cpp"
    break;

  case 21: // stmt: stmt_call
#line 314 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2134 "parser.cpp"
    break;

  case 22: // stmt: stmt_assign
#line 315 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2140 "parser.cpp"
    break;

  case 23: // stmt: stmt_endon
#line 316 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2146 "parser.cpp"
    break;

  case 24: // stmt: stmt_notify
#line 317 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2152 "parser.cpp"
    break;

  case 25: // stmt: stmt_wait
#line 318 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2158 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittill
#line 319 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2164 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittillmatch
#line 320 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2170 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillframeend
#line 321 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2176 "parser.cpp"
    break;

  case 29: // stmt: stmt_if
#line 322 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2182 "parser.cpp"
    break;

  case 30: // stmt: stmt_ifelse
#line 323 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2188 "parser.cpp"
    break;

  case 31: // stmt: stmt_while
#line 324 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2194 "parser.cpp"
    break;

  case 32: // stmt: stmt_dowhile
#line 325 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2200 "parser.cpp"
    break;

  case 33: // stmt: stmt_for
#line 326 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2206 "parser.cpp"
    break;

  case 34: // stmt: stmt_foreach
#line 327 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2212 "parser.cpp"
    break;

  case 35: // stmt: stmt_switch
#line 328 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2218 "parser.cpp"
    break;

  case 36: // stmt: stmt_case
#line 329 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2224 "parser.cpp"
    break;

  case 37: // stmt: stmt_default
#line 330 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2230 "parser.cpp"
    break;

  case 38: // stmt: stmt_break
#line 331 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2236 "parser.cpp"
    break;

  case 39: // stmt: stmt_continue
#line 332 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2242 "parser.cpp"
    break;

  case 40: // stmt: stmt_return
#line 333 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2248 "parser.cpp"
    break;

  case 41: // stmt: stmt_breakpoint
#line 334 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_breakpoint = std::move(yystack_[0].value.as < ast::stmt_breakpoint::ptr > ()); }
#line 2254 "parser.cpp"
    break;

  case 42: // stmt: stmt_prof_begin
#line 335 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2260 "parser.cpp"
    break;

  case 43: // stmt: stmt_prof_end
#line 336 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2266 "parser.cpp"
    break;

  case 44: // stmt_or_dev: stmt
#line 340 "parser.ypp"
               { yylhs.value.as < ast::stmt > () = std::move(yystack_[0].value.as < ast::stmt > ()); }
#line 2272 "parser.cpp"
    break;

  case 45: // stmt_or_dev: stmt_dev
#line 341 "parser.ypp"
               { yylhs.value.as < ast::stmt > ().as_dev = std::move(yystack_[0].value.as < ast::stmt_dev::ptr > ()); }
#line 2278 "parser.cpp"
    break;

  case 46: // stmt_list: stmt_list stmt
#line 346 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2284 "parser.cpp"
    break;

  case 47: // stmt_list: stmt
#line 348 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2290 "parser.cpp"
    break;

  case 48: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 353 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2296 "parser.cpp"
    break;

  case 49: // stmt_or_dev_list: stmt_or_dev
#line 355 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2302 "parser.cpp"
    break;

  case 50: // stmt_dev: "/#" stmt_list "#/"
#line 359 "parser.ypp"
                                { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::move(yystack_[1].value.as < ast::stmt_list::ptr > ())); }
#line 2308 "parser.cpp"
    break;

  case 51: // stmt_dev: "/#" "#/"
#line 360 "parser.ypp"
                      { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2314 "parser.cpp"
    break;

  case 52: // stmt_block: "{" stmt_or_dev_list "}"
#line 364 "parser.ypp"
                                     { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2320 "parser.cpp"
    break;

  case 53: // stmt_block: "{" "}"
#line 365 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2326 "parser.cpp"
    break;

  case 54: // stmt_expr: expr_assign
#line 370 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2332 "parser.cpp"
    break;

  case 55: // stmt_expr: expr_increment
#line 372 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2338 "parser.cpp"
    break;

  case 56: // stmt_expr: expr_decrement
#line 374 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2344 "parser.cpp"
    break;

  case 57: // stmt_expr: %empty
#line 376 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2350 "parser.cpp"
    break;

  case 58: // stmt_call: expr_call ";"
#line 381 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2356 "parser.cpp"
    break;

  case 59: // stmt_call: expr_method ";"
#line 383 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2362 "parser.cpp"
    break;

  case 60: // stmt_assign: expr_assign ";"
#line 388 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2368 "parser.cpp"
    break;

  case 61: // stmt_assign: expr_increment ";"
#line 390 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2374 "parser.cpp"
    break;

  case 62: // stmt_assign: expr_decrement ";"
#line 392 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2380 "parser.cpp"
    break;

  case 63: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 397 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2386 "parser.cpp"
    break;

  case 64: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 402 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2392 "parser.cpp"
    break;

  case 65: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 404 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2398 "parser.cpp"
    break;

  case 66: // stmt_wait: "wait" expr ";"
#line 409 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2404 "parser.cpp"
    break;

  case 67: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 414 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2410 "parser.cpp"
    break;

  case 68: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 416 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2416 "parser.cpp"
    break;

  case 69: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 421 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2422 "parser.cpp"
    break;

  case 70: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 423 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2428 "parser.cpp"
    break;

  case 71: // stmt_waittillframeend: "waittillframeend" ";"
#line 428 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2434 "parser.cpp"
    break;

  case 72: // stmt_if: "if" "(" expr ")" stmt
#line 433 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2440 "parser.cpp"
    break;

  case 73: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 438 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2446 "parser.cpp"
    break;

  case 74: // stmt_while: "while" "(" expr ")" stmt
#line 443 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2452 "parser.cpp"
    break;

  case 75: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 448 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2458 "parser.cpp"
    break;

  case 76: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 453 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2464 "parser.cpp"
    break;

  case 77: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 458 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2470 "parser.cpp"
    break;

  case 78: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 460 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2476 "parser.cpp"
    break;

  case 79: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 465 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2482 "parser.cpp"
    break;

  case 80: // stmt_case: "case" expr_integer ":"
#line 470 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2488 "parser.cpp"
    break;

  case 81: // stmt_case: "case" expr_string ":"
#line 472 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2494 "parser.cpp"
    break;

  case 82: // stmt_default: "default" ":"
#line 477 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2500 "parser.cpp"
    break;

  case 83: // stmt_break: "break" ";"
#line 482 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2506 "parser.cpp"
    break;

  case 84: // stmt_continue: "continue" ";"
#line 487 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2512 "parser.cpp"
    break;

  case 85: // stmt_return: "return" expr ";"
#line 492 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2518 "parser.cpp"
    break;

  case 86: // stmt_return: "return" ";"
#line 494 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2524 "parser.cpp"
    break;

  case 87: // stmt_breakpoint: "breakpoint" ";"
#line 499 "parser.ypp"
        { yylhs.value.as < ast::stmt_breakpoint::ptr > () = std::make_unique<ast::stmt_breakpoint>(yylhs.location); }
#line 2530 "parser.cpp"
    break;

  case 88: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 504 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2536 "parser.cpp"
    break;

  case 89: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 509 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2542 "parser.cpp"
    break;

  case 90: // expr: expr_ternary
#line 513 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2548 "parser.cpp"
    break;

  case 91: // expr: expr_binary
#line 514 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2554 "parser.cpp"
    break;

  case 92: // expr: expr_primitive
#line 515 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2560 "parser.cpp"
    break;

  case 93: // expr_or_empty: expr
#line 519 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2566 "parser.cpp"
    break;

  case 94: // expr_or_empty: %empty
#line 520 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2572 "parser.cpp"
    break;

  case 95: // expr_assign: expr_tuple "=" expr
#line 525 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2578 "parser.cpp"
    break;

  case 96: // expr_assign: expr_object "=" expr
#line 527 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2584 "parser.cpp"
    break;

  case 97: // expr_assign: expr_object "|=" expr
#line 529 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2590 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object "&=" expr
#line 531 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2596 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "^=" expr
#line 533 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2602 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object "<<=" expr
#line 535 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2608 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object ">>=" expr
#line 537 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2614 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "+=" expr
#line 539 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2620 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object "-=" expr
#line 541 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2626 "parser.cpp"
    break;

  case 104: // expr_assign: expr_object "*=" expr
#line 543 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2632 "parser.cpp"
    break;

  case 105: // expr_assign: expr_object "/=" expr
#line 545 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2638 "parser.cpp"
    break;

  case 106: // expr_assign: expr_object "%=" expr
#line 547 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2644 "parser.cpp"
    break;

  case 107: // expr_increment: "++" expr_object
#line 552 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2650 "parser.cpp"
    break;

  case 108: // expr_increment: expr_object "++"
#line 554 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2656 "parser.cpp"
    break;

  case 109: // expr_decrement: "--" expr_object
#line 559 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2662 "parser.cpp"
    break;

  case 110: // expr_decrement: expr_object "--"
#line 561 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2668 "parser.cpp"
    break;

  case 111: // expr_ternary: expr "?" expr ":" expr
#line 566 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2674 "parser.cpp"
    break;

  case 112: // expr_binary: expr "||" expr
#line 571 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2680 "parser.cpp"
    break;

  case 113: // expr_binary: expr "&&" expr
#line 573 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2686 "parser.cpp"
    break;

  case 114: // expr_binary: expr "==" expr
#line 575 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2692 "parser.cpp"
    break;

  case 115: // expr_binary: expr "!=" expr
#line 577 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2698 "parser.cpp"
    break;

  case 116: // expr_binary: expr "<=" expr
#line 579 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2704 "parser.cpp"
    break;

  case 117: // expr_binary: expr ">=" expr
#line 581 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2710 "parser.cpp"
    break;

  case 118: // expr_binary: expr "<" expr
#line 583 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2716 "parser.cpp"
    break;

  case 119: // expr_binary: expr ">" expr
#line 585 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2722 "parser.cpp"
    break;

  case 120: // expr_binary: expr "|" expr
#line 587 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2728 "parser.cpp"
    break;

  case 121: // expr_binary: expr "&" expr
#line 589 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2734 "parser.cpp"
    break;

  case 122: // expr_binary: expr "^" expr
#line 591 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2740 "parser.cpp"
    break;

  case 123: // expr_binary: expr "<<" expr
#line 593 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2746 "parser.cpp"
    break;

  case 124: // expr_binary: expr ">>" expr
#line 595 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2752 "parser.cpp"
    break;

  case 125: // expr_binary: expr "+" expr
#line 597 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2758 "parser.cpp"
    break;

  case 126: // expr_binary: expr "-" expr
#line 599 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2764 "parser.cpp"
    break;

  case 127: // expr_binary: expr "*" expr
#line 601 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2770 "parser.cpp"
    break;

  case 128: // expr_binary: expr "/" expr
#line 603 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2776 "parser.cpp"
    break;

  case 129: // expr_binary: expr "%" expr
#line 605 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2782 "parser.cpp"
    break;

  case 130: // expr_primitive: expr_complement
#line 609 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 2788 "parser.cpp"
    break;

  case 131: // expr_primitive: expr_negate
#line 610 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_negate::ptr > ()); }
#line 2794 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_not
#line 611 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 2800 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_call
#line 612 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 2806 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_method
#line 613 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 2812 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_add_array
#line 614 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_add_array::ptr > ()); }
#line 2818 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_reference
#line 615 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 2824 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_array
#line 616 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 2830 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_field
#line 617 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 2836 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_size
#line 618 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 2842 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_paren
#line 619 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 2848 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_thisthread
#line 620 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_thisthread::ptr > ()); }
#line 2854 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_empty_array
#line 621 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 2860 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_undefined
#line 622 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 2866 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_game
#line 623 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 2872 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_self
#line 624 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 2878 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_anim
#line 625 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 2884 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_level
#line 626 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 2890 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_animation
#line 627 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 2896 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_animtree
#line 628 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animtree::ptr > ()); }
#line 2902 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_identifier
#line 629 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 2908 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_istring
#line 630 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 2914 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_string
#line 631 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 2920 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_vector
#line 632 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 2926 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_float
#line 633 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 2932 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_integer
#line 634 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 2938 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_false
#line 635 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 2944 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_true
#line 636 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 2950 "parser.cpp"
    break;

  case 158: // expr_complement: "~" expr
#line 641 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2956 "parser.cpp"
    break;

  case 159: // expr_negate: "-" expr_identifier
#line 646 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()))); }
#line 2962 "parser.cpp"
    break;

  case 160: // expr_negate: "-" expr_paren
#line 648 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()))); }
#line 2968 "parser.cpp"
    break;

  case 161: // expr_negate: "-" expr_array
#line 650 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_array::ptr > ()))); }
#line 2974 "parser.cpp"
    break;

  case 162: // expr_negate: "-" expr_field
#line 652 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_field::ptr > ()))); }
#line 2980 "parser.cpp"
    break;

  case 163: // expr_not: "!" expr
#line 657 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2986 "parser.cpp"
    break;

  case 164: // expr_call: expr_function
#line 661 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2992 "parser.cpp"
    break;

  case 165: // expr_call: expr_pointer
#line 662 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2998 "parser.cpp"
    break;

  case 166: // expr_method: expr_object expr_function
#line 665 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3004 "parser.cpp"
    break;

  case 167: // expr_method: expr_object expr_pointer
#line 666 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3010 "parser.cpp"
    break;

  case 168: // expr_function: expr_identifier "(" expr_arguments ")"
#line 671 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3016 "parser.cpp"
    break;

  case 169: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 673 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3022 "parser.cpp"
    break;

  case 170: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 675 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3028 "parser.cpp"
    break;

  case 171: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 677 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3034 "parser.cpp"
    break;

  case 172: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 679 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3040 "parser.cpp"
    break;

  case 173: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 681 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3046 "parser.cpp"
    break;

  case 174: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 686 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3052 "parser.cpp"
    break;

  case 175: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 688 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3058 "parser.cpp"
    break;

  case 176: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 690 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3064 "parser.cpp"
    break;

  case 177: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 692 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::builtin); }
#line 3070 "parser.cpp"
    break;

  case 178: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 697 "parser.ypp"
        { yylhs.value.as < ast::expr_add_array::ptr > () = std::make_unique<ast::expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ())); }
#line 3076 "parser.cpp"
    break;

  case 179: // expr_parameters: expr_parameters "," expr_identifier
#line 702 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3082 "parser.cpp"
    break;

  case 180: // expr_parameters: expr_identifier
#line 704 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3088 "parser.cpp"
    break;

  case 181: // expr_parameters: %empty
#line 706 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 3094 "parser.cpp"
    break;

  case 182: // expr_arguments: expr_arguments_no_empty
#line 711 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 3100 "parser.cpp"
    break;

  case 183: // expr_arguments: %empty
#line 713 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3106 "parser.cpp"
    break;

  case 184: // expr_arguments_no_empty: expr_arguments "," expr
#line 718 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3112 "parser.cpp"
    break;

  case 185: // expr_arguments_no_empty: expr
#line 720 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3118 "parser.cpp"
    break;

  case 186: // expr_reference: "::" expr_identifier
#line 725 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3124 "parser.cpp"
    break;

  case 187: // expr_reference: expr_path "::" expr_identifier
#line 727 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3130 "parser.cpp"
    break;

  case 188: // expr_tuple: "[" expr_tuple_arguments "]"
#line 732 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[1].value.as < ast::expr_tuple::ptr > ()); }
#line 3136 "parser.cpp"
    break;

  case 189: // expr_tuple_arguments: expr_tuple_arguments "," expr_tuple_types
#line 737 "parser.ypp"
        { yylhs.value.as < ast::expr_tuple::ptr > () = std::move(yystack_[2].value.as < ast::expr_tuple::ptr > ()); yylhs.value.as < ast::expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3142 "parser.cpp"
    break;

  case 190: // expr_tuple_arguments: expr_tuple_types
#line 739 "parser.ypp"
        { yylhs.value.as < ast::expr_tuple::ptr > () = std::make_unique<ast::expr_tuple>(yylhs.location); yylhs.value.as < ast::expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3148 "parser.cpp"
    break;

  case 191: // expr_tuple_types: expr_array
#line 743 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3154 "parser.cpp"
    break;

  case 192: // expr_tuple_types: expr_field
#line 744 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3160 "parser.cpp"
    break;

  case 193: // expr_tuple_types: expr_identifier
#line 745 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3166 "parser.cpp"
    break;

  case 194: // expr_array: expr_object "[" expr "]"
#line 750 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3172 "parser.cpp"
    break;

  case 195: // expr_field: expr_object "." expr_identifier_nosize
#line 755 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3178 "parser.cpp"
    break;

  case 196: // expr_size: expr_object "." "size"
#line 760 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ())); }
#line 3184 "parser.cpp"
    break;

  case 197: // expr_paren: "(" expr ")"
#line 765 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3190 "parser.cpp"
    break;

  case 198: // expr_object: expr_call
#line 769 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3196 "parser.cpp"
    break;

  case 199: // expr_object: expr_method
#line 770 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3202 "parser.cpp"
    break;

  case 200: // expr_object: expr_array
#line 771 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3208 "parser.cpp"
    break;

  case 201: // expr_object: expr_field
#line 772 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3214 "parser.cpp"
    break;

  case 202: // expr_object: expr_game
#line 773 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3220 "parser.cpp"
    break;

  case 203: // expr_object: expr_self
#line 774 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3226 "parser.cpp"
    break;

  case 204: // expr_object: expr_anim
#line 775 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3232 "parser.cpp"
    break;

  case 205: // expr_object: expr_level
#line 776 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3238 "parser.cpp"
    break;

  case 206: // expr_object: expr_identifier
#line 777 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3244 "parser.cpp"
    break;

  case 207: // expr_thisthread: "thisthread"
#line 782 "parser.ypp"
        { yylhs.value.as < ast::expr_thisthread::ptr > () = std::make_unique<ast::expr_thisthread>(yylhs.location); }
#line 3250 "parser.cpp"
    break;

  case 208: // expr_empty_array: "[" "]"
#line 787 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3256 "parser.cpp"
    break;

  case 209: // expr_undefined: "undefined"
#line 792 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3262 "parser.cpp"
    break;

  case 210: // expr_game: "game"
#line 797 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3268 "parser.cpp"
    break;

  case 211: // expr_self: "self"
#line 802 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3274 "parser.cpp"
    break;

  case 212: // expr_anim: "anim"
#line 807 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3280 "parser.cpp"
    break;

  case 213: // expr_level: "level"
#line 812 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3286 "parser.cpp"
    break;

  case 214: // expr_animation: "%" "identifier"
#line 817 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3292 "parser.cpp"
    break;

  case 215: // expr_animtree: "#animtree"
#line 822 "parser.ypp"
        { yylhs.value.as < ast::expr_animtree::ptr > () = std::make_unique<ast::expr_animtree>(yylhs.location); }
#line 3298 "parser.cpp"
    break;

  case 216: // expr_identifier_nosize: "identifier"
#line 827 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3304 "parser.cpp"
    break;

  case 217: // expr_identifier: "identifier"
#line 832 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3310 "parser.cpp"
    break;

  case 218: // expr_identifier: "size"
#line 834 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, "size"); }
#line 3316 "parser.cpp"
    break;

  case 219: // expr_path: "identifier"
#line 839 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3322 "parser.cpp"
    break;

  case 220: // expr_path: "path"
#line 841 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3328 "parser.cpp"
    break;

  case 221: // expr_istring: "localized string"
#line 846 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3334 "parser.cpp"
    break;

  case 222: // expr_string: "string literal"
#line 851 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3340 "parser.cpp"
    break;

  case 223: // expr_vector: "(" expr "," expr "," expr ")"
#line 856 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3346 "parser.cpp"
    break;

  case 224: // expr_float: "-" "float"
#line 861 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3352 "parser.cpp"
    break;

  case 225: // expr_float: "float"
#line 863 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3358 "parser.cpp"
    break;

  case 226: // expr_integer: "-" "integer"
#line 868 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3364 "parser.cpp"
    break;

  case 227: // expr_integer: "integer"
#line 870 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3370 "parser.cpp"
    break;

  case 228: // expr_false: "false"
#line 875 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3376 "parser.cpp"
    break;

  case 229: // expr_true: "true"
#line 880 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3382 "parser.cpp"
    break;


#line 3386 "parser.cpp"

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
  "waittill", "waittillmatch", "waittillframeend", "if", "else", "do",
  "while", "for", "foreach", "in", "switch", "case", "default", "break",
  "continue", "return", "breakpoint", "prof_begin", "prof_end", "thread",
  "childthread", "thisthread", "call", "true", "false", "undefined",
  "size", "game", "self", "anim", "level", "(", ")", "{", "}", "[", "]",
  ",", ".", "::", ":", ";", "?", "++", "--", "<<", ">>", "||", "&&", "==",
  "!=", "<=", ">=", "<", ">", "!", "~", "=", "+=", "-=", "*=", "/=", "%=",
  "|=", "&=", "^=", ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/", "%",
  "path", "identifier", "string literal", "localized string", "float",
  "integer", "SIZEOF", "ADD_ARRAY", "THEN", "TERN", "NEG", "ANIMREF",
  "PREINC", "PREDEC", "POSTINC", "POSTDEC", "$accept", "root", "program",
  "inline", "include", "declaration", "decl_usingtree", "decl_constant",
  "decl_thread", "stmt", "stmt_or_dev", "stmt_list", "stmt_or_dev_list",
  "stmt_dev", "stmt_block", "stmt_expr", "stmt_call", "stmt_assign",
  "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch",
  "stmt_case", "stmt_default", "stmt_break", "stmt_continue",
  "stmt_return", "stmt_breakpoint", "stmt_prof_begin", "stmt_prof_end",
  "expr", "expr_or_empty", "expr_assign", "expr_increment",
  "expr_decrement", "expr_ternary", "expr_binary", "expr_primitive",
  "expr_complement", "expr_negate", "expr_not", "expr_call", "expr_method",
  "expr_function", "expr_pointer", "expr_add_array", "expr_parameters",
  "expr_arguments", "expr_arguments_no_empty", "expr_reference",
  "expr_tuple", "expr_tuple_arguments", "expr_tuple_types", "expr_array",
  "expr_field", "expr_size", "expr_paren", "expr_object",
  "expr_thisthread", "expr_empty_array", "expr_undefined", "expr_game",
  "expr_self", "expr_anim", "expr_level", "expr_animation",
  "expr_animtree", "expr_identifier_nosize", "expr_identifier",
  "expr_path", "expr_istring", "expr_string", "expr_vector", "expr_float",
  "expr_integer", "expr_false", "expr_true", YY_NULLPTR
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
    if (yy_lac_established_)
      return true;
    else
      {
#if IW7DEBUG
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


  const short parser::yypact_ninf_ = -281;

  const short parser::yytable_ninf_ = -220;

  const short
  parser::yypact_[] =
  {
       4,  -281,  -281,   -72,   -72,   -41,  -281,  -281,    32,     4,
    -281,  -281,  -281,  -281,  -281,  -281,   -21,  -281,  -281,   -28,
      -1,   -22,  -281,  -281,  -281,  -281,   -43,  1235,  -281,  -281,
    -281,     5,   -29,  -281,  -281,   -26,   -24,  -281,     8,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  1235,  1109,   -43,  1235,
    1235,   612,     1,    47,  -281,  -281,  -281,  2111,  -281,  -281,
    -281,  -281,  -281,  -281,   108,   145,  -281,  -281,  -281,  -281,
     372,   438,  -281,  -281,   633,  -281,  -281,  -281,   664,   818,
     982,   987,  -281,  -281,    39,    59,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,    61,    16,   -43,    65,    78,    79,   103,
     109,   127,   133,  1443,  1109,  -281,  2194,   125,   136,  -281,
    -281,  -281,  1235,   134,  -281,  -281,  -281,  -281,   372,   438,
    -281,  1132,  -281,  -281,  -281,  -281,    39,   137,  -281,  -281,
    1235,  1235,  1235,  1235,  1235,  1235,  1235,  1235,  1235,  1235,
    1235,  1235,  1235,  1235,  1235,  1235,  1235,  1235,  1235,  1298,
     -35,  -281,  -281,   147,  1235,   -43,  -281,   951,  -281,  -281,
    1235,  1235,   -43,  1235,  1235,   -43,  1235,  -281,  1235,  1231,
    1235,  -281,  1609,  1235,   102,   -43,  2076,   -51,   -51,  2225,
     865,  2276,  2276,   -27,   -27,   -27,   -27,  2235,   273,  2266,
      51,    51,  -281,  -281,  -281,  1294,  -281,  -281,  -281,    23,
    -281,   150,    77,  1235,   148,   157,  1381,   160,   162,   163,
     166,   -15,   158,   165,   167,  1172,   168,   172,   173,  -281,
     409,   703,   703,  -281,  -281,  1027,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,   175,   184,   185,   186,   187,   142,  -281,  -281,   808,
     147,  1921,    30,   176,  1961,    36,   182,  2001,  2040,   195,
    2194,  1231,   150,  1235,  -281,  -281,  1235,  -281,  -281,  1080,
    2146,  -281,  1235,   224,  1235,   738,   -43,  1235,   151,   193,
     196,  -281,  -281,  -281,  -281,  2181,  -281,  1235,  1235,  1298,
      35,  -281,   112,   123,    -4,  1132,  1132,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  1235,   204,   206,   209,   210,  -281,
    -281,  1235,  1235,  1235,  1235,  1235,  1235,  1235,  1235,  1235,
    1235,  1235,   207,  -281,  1235,   211,  -281,  1235,   212,  1235,
     214,  2194,    76,  -281,  -281,  -281,  1643,   215,  1677,   201,
    -281,  -281,  -281,  1407,    -8,  1711,  -281,  -281,  -281,    82,
      85,  -281,   703,  2194,  1235,  1235,  1235,  1235,  2194,  2194,
    2194,  2194,  2194,  2194,  2194,  2194,  2194,  2194,  2194,   219,
     104,   220,   107,   221,  1745,  1235,  -281,  1381,  1235,  1381,
    1235,  1235,   -43,    16,   216,   222,  -281,  1779,  1487,  1531,
    1575,  1235,  -281,  1235,  -281,  1235,  -281,   120,   249,  1813,
    -281,  2194,   223,  1847,   246,  -281,  -281,  -281,   227,   229,
    1235,   232,  1235,   235,  1235,   124,   126,   138,  -281,  1381,
     236,   738,  1381,  1235,  -281,  -281,   228,  -281,   230,  -281,
     247,  -281,  -281,  -281,  -281,  -281,   250,  -281,  1881,   242,
     243,   248,  1381,  1381,  -281,  -281,  -281,  -281,  -281
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   218,   217,     0,     2,
       7,     8,     9,    14,    15,    16,     0,   220,   219,     0,
       0,     0,     1,     4,     5,     6,   181,     0,    10,    11,
     222,     0,     0,   180,   215,     0,     0,   207,     0,   229,
     228,   209,   210,   211,   212,   213,     0,   183,     0,     0,
       0,     0,     0,   217,   221,   225,   227,     0,    90,    91,
      92,   130,   131,   132,   133,   134,   164,   165,   135,   136,
     137,   138,   139,   140,     0,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,     0,   151,   152,   153,   154,
     155,   156,   157,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   183,   208,   185,     0,   182,   186,
     163,   158,     0,     0,   224,   226,   198,   199,   161,   162,
     160,     0,   202,   203,   204,   205,   159,     0,   214,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,   167,     0,   183,     0,    17,     0,    19,   179,
       0,   183,     0,     0,   183,     0,     0,   197,     0,   185,
       0,   178,     0,     0,     0,     0,     0,   123,   124,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     125,   126,   127,   128,   129,     0,   196,   216,   195,     0,
     182,   187,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
       0,     0,     0,    44,    49,     0,    45,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,     0,     0,     0,   198,   199,     0,   200,   201,     0,
     206,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     184,     0,     0,     0,   194,   168,   183,    51,    47,     0,
       0,    71,     0,     0,     0,    57,     0,     0,     0,     0,
       0,    82,    83,    84,    86,     0,    87,   183,   183,     0,
       0,   190,   200,   201,   206,   107,   109,    52,    48,    60,
      61,    62,    58,    59,     0,     0,     0,     0,     0,   108,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   170,   183,     0,   172,   183,     0,     0,
       0,   111,     0,    50,    46,    66,     0,     0,     0,     0,
      54,    55,    56,     0,     0,     0,    81,    80,    85,     0,
       0,   188,     0,    95,     0,     0,     0,     0,    96,   102,
     103,   104,   105,   106,    97,    98,    99,   101,   100,     0,
       0,     0,     0,     0,     0,   183,   169,     0,     0,     0,
      94,     0,     0,     0,     0,     0,   189,     0,     0,     0,
       0,   183,   171,   183,   173,   183,   223,     0,    72,     0,
      74,    93,     0,     0,     0,    79,    88,    89,     0,     0,
     183,     0,   183,     0,   183,     0,     0,     0,   174,     0,
       0,    57,     0,     0,    63,    65,   182,    68,   182,    70,
     182,   175,   176,   177,    73,    75,     0,    77,     0,     0,
       0,     0,     0,     0,    64,    67,    69,    76,    78
  };

  const short
  parser::yypgoto_[] =
  {
    -281,  -281,  -281,   272,   298,   299,  -281,  -281,  -281,   194,
      86,  -281,  -281,  -281,   -92,  -121,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,   188,
    -281,  -280,  -279,  -278,  -281,  -281,  -281,  -281,  -281,  -281,
      92,   203,   -66,   -62,  -281,  -281,  -127,   -46,  -281,  -281,
    -281,   -13,   213,   337,  -281,   289,   385,  -281,  -281,  -281,
     392,   480,   512,   519,  -281,  -281,  -281,     0,    10,  -281,
     -17,  -281,  -281,   130,  -281,  -281
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    11,    12,    13,    14,    15,   223,
     224,   279,   225,   226,   227,   349,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   106,
     412,   251,   252,   253,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    32,   107,   200,    69,   256,
     300,   301,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,   198,    84,    85,    86,
      87,    88,    89,    90,    91,    92
  };

  const short
  parser::yytable_[] =
  {
      16,   108,   158,     6,    31,   350,   351,   352,   151,    16,
      21,   196,   152,    19,    20,     1,     2,     3,     4,     5,
       6,   391,     6,    94,    17,    18,    33,   199,    95,    96,
      26,    99,    22,    28,   262,    97,   100,   265,   131,   132,
     144,   145,   146,   147,   148,    98,   101,   154,   109,   392,
       6,   126,  -193,  -193,     7,   151,    27,    93,   108,   152,
      29,   127,   197,   102,   144,   145,   146,   147,   148,   157,
      17,    53,    17,    53,   153,   275,    30,   288,  -206,  -206,
     170,  -206,   333,    30,   127,  -206,    56,   170,   336,   277,
     154,   361,   362,   170,  -206,   159,   203,  -206,   128,   204,
     205,     7,   206,   207,   208,   209,  -219,   210,   211,   212,
     213,   214,   215,   216,   217,   218,    35,    36,   155,    38,
     160,   153,   156,     6,    42,    43,    44,    45,   386,   161,
     157,   127,   220,   170,   394,  -206,  -206,   395,   162,   170,
     221,   222,   170,   116,   146,   147,   148,  -198,  -198,   342,
    -198,   350,   351,   352,  -198,   201,   402,   260,   163,   404,
     164,   170,   263,  -198,   170,   266,  -198,   127,  -191,  -191,
     359,   360,   428,    17,    53,   272,   441,   170,   442,  -192,
    -192,   170,   170,   170,  -199,  -199,   165,  -199,   166,   173,
     443,  -199,   171,   151,   289,   170,   175,   152,   154,   197,
    -199,   276,   260,  -199,  -198,  -198,   260,   380,   282,   281,
     382,   284,   127,   285,   286,    57,   127,   287,   291,   314,
     304,   260,   260,   297,   298,   260,   292,   334,   293,   296,
     127,   127,   127,   337,   103,   127,   309,   110,   111,   151,
     151,  -199,  -199,   152,   152,   310,   311,   312,   313,   254,
     347,   340,   115,   356,   117,   364,   357,   365,   407,   153,
     366,   367,   390,   379,   118,   385,   388,   381,   383,   127,
     401,   403,   405,   429,   425,   433,   426,   416,   427,   260,
     449,    23,   450,   417,   431,   260,   354,   151,   434,   127,
     435,   152,   169,   437,   254,   127,   439,   445,   254,   451,
     172,   415,   452,   454,   455,   153,   153,    24,    25,   456,
     446,   308,   116,   116,   116,   127,   127,   254,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   131,   132,
     120,   290,   135,   136,   137,   138,   139,   140,   261,   396,
       0,   264,     0,   153,   267,     0,   268,     0,   270,     0,
     255,   271,   304,   127,   144,   145,   146,   147,   148,     0,
     257,   254,   127,     0,   436,     0,   438,   116,   440,     0,
       0,     0,     0,     0,     0,     0,     0,   260,   119,   260,
       0,   280,   414,     0,     0,     0,   278,   127,     0,   127,
     283,     0,     0,   295,     0,   255,     0,     0,     0,   255,
       0,  -200,  -200,     0,  -200,   257,     0,     0,  -200,   257,
       0,     0,     0,   117,   117,   117,     0,  -200,   255,   260,
    -200,   260,   260,   302,   257,   257,   121,     0,   257,   127,
       0,   127,   127,   122,     0,     0,     0,     0,    35,    36,
       0,    38,   260,   260,   116,     6,    42,    43,    44,    45,
       0,   341,   127,   127,   299,     0,     0,     0,  -200,  -200,
     346,     0,   348,   344,     0,   355,     0,  -201,  -201,   254,
    -201,   254,   255,     0,  -201,     0,     0,   271,   117,     0,
       0,     0,   257,  -201,   258,     0,  -201,     0,   257,     0,
       0,     0,   363,     0,     0,    17,    53,     0,     0,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
       0,   254,     0,   116,   254,     0,     0,   384,     0,     0,
       0,   123,     0,     0,  -201,  -201,     0,     0,     0,   258,
       0,     0,   259,   258,   254,   254,     0,     0,     0,   122,
       0,     0,   397,   398,   399,   400,     0,   303,   258,   258,
       0,     0,   258,   124,     0,   117,     0,     0,     0,     0,
     125,     0,     0,     0,     0,   302,   409,     0,   411,   413,
       0,   408,     0,   410,     0,     0,     0,   259,     0,     0,
     255,   259,   255,     0,   122,     0,     0,     0,   122,     0,
     257,     0,   257,     0,     0,   121,   305,   306,     0,     0,
     259,     0,   122,   122,   122,     0,   258,   122,     0,     0,
       0,   448,   258,   444,     0,     0,   447,     0,     0,     0,
       0,     0,   255,     0,   117,   255,     0,   123,     0,     0,
       0,     0,   257,     0,   257,   257,   457,   458,     0,     0,
       0,    35,    36,     0,    38,   255,   255,     0,     6,    42,
      43,    44,    45,   112,   259,   257,   257,   113,     0,   124,
     353,   122,    35,    36,     0,    38,   125,   122,     0,     6,
       0,     0,   123,     0,     0,     0,   123,     0,   149,     0,
       0,   150,     0,     0,     0,     0,     0,     0,     0,   303,
     123,   123,   123,  -202,  -202,   123,  -202,     0,    17,    53,
    -202,     0,   114,   115,   124,     0,     0,     0,   124,  -202,
       0,   125,  -202,     0,   258,   125,   258,     0,     0,    17,
      53,     0,   124,   124,   124,     0,     0,   124,     0,   125,
     125,   125,    35,    36,   125,    38,     0,   121,     0,     6,
      42,    43,    44,    45,   122,     0,     0,     0,   113,   123,
    -202,  -202,     0,     0,     0,   123,   258,     0,   258,   258,
       0,     0,   259,     0,   259,     0,     0,    35,    36,   122,
      38,   122,     0,     0,     6,    42,    43,    44,    45,   258,
     258,   124,     0,   220,     0,     0,     0,   124,   125,    17,
      53,   221,   222,     0,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   259,     0,   353,   259,     0,     0,
       0,   122,     0,   122,   122,   315,   316,     0,   317,   318,
       0,     0,     0,     0,    17,    53,     0,   259,   259,     0,
       0,     0,   123,     0,   122,   122,     0,    35,    36,     0,
      38,     0,     0,     0,     6,     0,     0,  -203,  -203,     0,
    -203,     0,     0,   149,  -203,     0,   174,   123,     0,   123,
       0,   319,   320,  -203,   124,     0,  -203,     0,     0,     0,
       0,   125,     0,     0,     0,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,     0,     0,     0,   124,
       0,   124,     0,     0,    17,    53,   125,     0,   125,   123,
       0,   123,   123,     0,  -203,  -203,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     131,   132,   123,   123,   135,   136,   137,   138,   139,   140,
       0,   124,     0,   124,   124,     0,     0,     0,   125,     0,
     125,   125,     0,   141,   142,   143,   144,   145,   146,   147,
     148,     0,   202,     0,   124,   124,     0,     0,     0,     0,
     203,   125,   125,   204,   205,     0,   206,   207,   208,   209,
       0,   210,   211,   212,   213,   214,   215,   216,   217,   218,
      35,    36,     0,    38,     0,     0,     0,     6,    42,    43,
      44,    45,     0,     0,   157,   219,   220,     0,     0,     0,
       0,     0,     0,     0,   221,   222,     0,     0,     0,     0,
       0,  -204,  -204,     0,  -204,     0,  -205,  -205,  -204,  -205,
       0,     0,     0,  -205,     0,     0,     0,  -204,   202,     0,
    -204,     0,  -205,     0,     0,  -205,   203,    17,    53,   204,
     205,     0,   206,   207,   208,   209,     0,   210,   211,   212,
     213,   214,   215,   216,   217,   218,    35,    36,     0,    38,
       0,     0,     0,     6,    42,    43,    44,    45,  -204,  -204,
     157,   307,   220,  -205,  -205,     0,     0,     0,     0,     0,
     221,   222,   343,     0,     0,     0,     0,     0,     0,   203,
       0,     0,   204,   205,     0,   206,   207,   208,   209,     0,
     210,   211,   212,   213,   214,   215,   216,   217,   218,    35,
      36,     0,    38,    17,    53,    34,     6,    42,    43,    44,
      45,     0,     0,   157,     0,   220,     0,     0,     0,     0,
       0,     0,     0,   221,   222,     0,     0,     0,    35,    36,
      37,    38,    39,    40,    41,     6,    42,    43,    44,    45,
      46,     0,     0,     0,   104,   105,     0,     0,    48,     0,
       0,    35,    36,     0,    38,     0,    17,    53,     6,     0,
       0,     0,     0,     0,    49,    50,     0,   149,    34,     0,
     174,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,    52,    17,    53,    30,    54,    55,
      56,    35,    36,    37,    38,    39,    40,    41,     6,    42,
      43,    44,    45,    46,     0,     0,     0,    47,    17,    53,
       0,    48,     0,   294,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,     0,    52,    17,    53,
      30,    54,    55,    56,    35,    36,    37,    38,    39,    40,
      41,     6,    42,    43,    44,    45,    46,   269,     0,     0,
      47,     0,     0,   130,    48,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     0,     0,     0,     0,
      49,    50,     0,     0,    34,     0,     0,     0,     0,   141,
     142,   143,   144,   145,   146,   147,   148,    51,     0,     0,
      52,    17,    53,    30,    54,    55,    56,    35,    36,    37,
      38,    39,    40,    41,     6,    42,    43,    44,    45,    46,
     274,     0,     0,   104,     0,     0,   130,    48,     0,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,     0,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,   141,   142,   143,   144,   145,   146,   147,   148,
      51,     0,     0,    52,    17,    53,    30,    54,    55,    56,
     203,     0,     0,   204,   205,     0,   206,   207,   208,   209,
       0,   210,   211,   212,   213,   214,   215,   216,   217,   218,
      35,    36,     0,    38,     0,     0,     0,     6,    42,    43,
      44,    45,     0,     0,   157,     0,   220,     0,     0,     0,
       0,     0,     0,     0,   221,   222,    35,    36,     0,    38,
       0,     0,     0,     6,     0,     0,     0,     0,     0,     0,
       0,     0,   149,     0,     0,   174,     0,     0,     0,     0,
     319,   320,     0,     0,     0,     0,     0,    17,    53,     0,
       0,     0,     0,     0,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   167,     0,     0,     0,     0,
     168,     0,     0,    17,    53,   130,     0,     0,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   141,   142,   143,   144,   145,   146,   147,   148,   419,
       0,     0,     0,     0,   420,     0,     0,     0,     0,   130,
       0,     0,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   141,   142,   143,   144,   145,
     146,   147,   148,   421,     0,     0,     0,     0,   422,     0,
       0,     0,     0,   130,     0,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
     142,   143,   144,   145,   146,   147,   148,   423,     0,     0,
       0,     0,   424,     0,     0,     0,     0,   130,     0,     0,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   167,     0,   141,   142,   143,   144,   145,   146,   147,
     148,   130,     0,     0,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   387,     0,   141,   142,   143,
     144,   145,   146,   147,   148,   130,     0,     0,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   389,
       0,   141,   142,   143,   144,   145,   146,   147,   148,   130,
       0,     0,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   393,     0,   141,   142,   143,   144,   145,
     146,   147,   148,   130,     0,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   406,     0,   141,
     142,   143,   144,   145,   146,   147,   148,   130,     0,     0,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   418,     0,   141,   142,   143,   144,   145,   146,   147,
     148,   130,     0,     0,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   430,     0,   141,   142,   143,
     144,   145,   146,   147,   148,   130,     0,     0,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   432,
       0,   141,   142,   143,   144,   145,   146,   147,   148,   130,
       0,     0,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   453,     0,   141,   142,   143,   144,   145,
     146,   147,   148,   130,     0,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
     142,   143,   144,   145,   146,   147,   148,   332,     0,     0,
       0,     0,     0,   130,     0,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
     142,   143,   144,   145,   146,   147,   148,   335,     0,     0,
       0,     0,     0,   130,     0,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
     142,   143,   144,   145,   146,   147,   148,   338,     0,     0,
       0,     0,     0,   130,     0,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
     142,   143,   144,   145,   146,   147,   148,   339,     0,     0,
       0,     0,   130,     0,     0,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   141,   142,
     143,   144,   145,   146,   147,   148,   273,     0,   130,     0,
       0,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   141,   142,   143,   144,   145,   146,
     147,   148,   129,   130,     0,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
     142,   143,   144,   145,   146,   147,   148,   345,   130,     0,
       0,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   141,   142,   143,   144,   145,   146,
     147,   148,   358,   130,     0,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   130,     0,     0,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,     0,     0,     0,
       0,     0,   141,   142,   143,   144,   145,   146,   147,   148,
     131,   132,     0,   134,   135,   136,   137,   138,   139,   140,
     131,   132,     0,     0,   135,   136,   137,   138,   139,   140,
       0,     0,     0,   141,   142,   143,   144,   145,   146,   147,
     148,     0,     0,     0,   142,   143,   144,   145,   146,   147,
     148,   131,   132,     0,     0,   135,   136,   137,   138,   139,
     140,   131,   132,     0,     0,     0,     0,   137,   138,   139,
     140,     0,     0,     0,     0,   142,     0,   144,   145,   146,
     147,   148,     0,     0,     0,     0,     0,   144,   145,   146,
     147,   148
  };

  const short
  parser::yycheck_[] =
  {
       0,    47,    94,    46,    21,   285,   285,   285,    74,     9,
      51,    46,    74,     3,     4,    11,    12,    13,    14,    15,
      46,    29,    46,    52,    96,    97,    26,   154,    57,    55,
      51,    55,     0,    61,   161,    35,    36,   164,    65,    66,
      91,    92,    93,    94,    95,    35,    36,    51,    48,    57,
      46,    51,    56,    57,    97,   121,    77,    52,   104,   121,
      61,    51,    97,    55,    91,    92,    93,    94,    95,    53,
      96,    97,    96,    97,    74,    52,    98,    92,    39,    40,
      57,    42,    52,    98,    74,    46,   101,    57,    52,    12,
      51,    56,    57,    57,    55,    95,    19,    58,    97,    22,
      23,    97,    25,    26,    27,    28,    59,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    59,    42,
      55,   121,    61,    46,    47,    48,    49,    50,    52,    51,
      53,   121,    55,    57,    52,    96,    97,    52,    59,    57,
      63,    64,    57,    51,    93,    94,    95,    39,    40,   276,
      42,   431,   431,   431,    46,   155,    52,   157,    55,    52,
      51,    57,   162,    55,    57,   165,    58,   157,    56,    57,
     297,   298,    52,    96,    97,   175,    52,    57,    52,    56,
      57,    57,    57,    57,    39,    40,    59,    42,    55,    55,
      52,    46,    56,   259,   211,    57,    59,   259,    51,    97,
      55,    51,   202,    58,    96,    97,   206,   334,    51,    61,
     337,    51,   202,    51,    51,    27,   206,    51,    60,    77,
     220,   221,   222,    51,    51,   225,    61,    51,    61,    61,
     220,   221,   222,    51,    46,   225,    61,    49,    50,   305,
     306,    96,    97,   305,   306,    61,    61,    61,    61,   157,
      26,    56,   101,    60,    51,    51,    60,    51,   385,   259,
      51,    51,    61,    56,    51,    51,    51,    56,    56,   259,
      51,    51,    51,    24,   401,    29,   403,    61,   405,   279,
      52,     9,    52,    61,    61,   285,   286,   353,    61,   279,
      61,   353,   104,    61,   202,   285,    61,    61,   206,    52,
     112,   393,    52,    61,    61,   305,   306,     9,     9,    61,
     431,   225,   220,   221,   222,   305,   306,   225,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,    65,    66,
      51,   211,    69,    70,    71,    72,    73,    74,   160,   362,
      -1,   163,    -1,   353,   166,    -1,   168,    -1,   170,    -1,
     157,   173,   362,   353,    91,    92,    93,    94,    95,    -1,
     157,   279,   362,    -1,   420,    -1,   422,   285,   424,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   387,    51,   389,
      -1,   203,   392,    -1,    -1,    -1,   202,   387,    -1,   389,
     206,    -1,    -1,   215,    -1,   202,    -1,    -1,    -1,   206,
      -1,    39,    40,    -1,    42,   202,    -1,    -1,    46,   206,
      -1,    -1,    -1,   220,   221,   222,    -1,    55,   225,   429,
      58,   431,   432,   220,   221,   222,    51,    -1,   225,   429,
      -1,   431,   432,    51,    -1,    -1,    -1,    -1,    39,    40,
      -1,    42,   452,   453,   362,    46,    47,    48,    49,    50,
      -1,   273,   452,   453,    55,    -1,    -1,    -1,    96,    97,
     282,    -1,   284,   279,    -1,   287,    -1,    39,    40,   387,
      42,   389,   279,    -1,    46,    -1,    -1,   299,   285,    -1,
      -1,    -1,   279,    55,   157,    -1,    58,    -1,   285,    -1,
      -1,    -1,   314,    -1,    -1,    96,    97,    -1,    -1,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
      -1,   429,    -1,   431,   432,    -1,    -1,   339,    -1,    -1,
      -1,    51,    -1,    -1,    96,    97,    -1,    -1,    -1,   202,
      -1,    -1,   157,   206,   452,   453,    -1,    -1,    -1,   157,
      -1,    -1,   364,   365,   366,   367,    -1,   220,   221,   222,
      -1,    -1,   225,    51,    -1,   362,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,   362,   388,    -1,   390,   391,
      -1,   387,    -1,   389,    -1,    -1,    -1,   202,    -1,    -1,
     387,   206,   389,    -1,   202,    -1,    -1,    -1,   206,    -1,
     387,    -1,   389,    -1,    -1,   220,   221,   222,    -1,    -1,
     225,    -1,   220,   221,   222,    -1,   279,   225,    -1,    -1,
      -1,   433,   285,   429,    -1,    -1,   432,    -1,    -1,    -1,
      -1,    -1,   429,    -1,   431,   432,    -1,   157,    -1,    -1,
      -1,    -1,   429,    -1,   431,   432,   452,   453,    -1,    -1,
      -1,    39,    40,    -1,    42,   452,   453,    -1,    46,    47,
      48,    49,    50,    51,   279,   452,   453,    55,    -1,   157,
     285,   279,    39,    40,    -1,    42,   157,   285,    -1,    46,
      -1,    -1,   202,    -1,    -1,    -1,   206,    -1,    55,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   362,
     220,   221,   222,    39,    40,   225,    42,    -1,    96,    97,
      46,    -1,   100,   101,   202,    -1,    -1,    -1,   206,    55,
      -1,   202,    58,    -1,   387,   206,   389,    -1,    -1,    96,
      97,    -1,   220,   221,   222,    -1,    -1,   225,    -1,   220,
     221,   222,    39,    40,   225,    42,    -1,   362,    -1,    46,
      47,    48,    49,    50,   362,    -1,    -1,    -1,    55,   279,
      96,    97,    -1,    -1,    -1,   285,   429,    -1,   431,   432,
      -1,    -1,   387,    -1,   389,    -1,    -1,    39,    40,   387,
      42,   389,    -1,    -1,    46,    47,    48,    49,    50,   452,
     453,   279,    -1,    55,    -1,    -1,    -1,   285,   279,    96,
      97,    63,    64,    -1,   285,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   429,    -1,   431,   432,    -1,    -1,
      -1,   429,    -1,   431,   432,    17,    18,    -1,    20,    21,
      -1,    -1,    -1,    -1,    96,    97,    -1,   452,   453,    -1,
      -1,    -1,   362,    -1,   452,   453,    -1,    39,    40,    -1,
      42,    -1,    -1,    -1,    46,    -1,    -1,    39,    40,    -1,
      42,    -1,    -1,    55,    46,    -1,    58,   387,    -1,   389,
      -1,    63,    64,    55,   362,    -1,    58,    -1,    -1,    -1,
      -1,   362,    -1,    -1,    -1,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    -1,    -1,    -1,   387,
      -1,   389,    -1,    -1,    96,    97,   387,    -1,   389,   429,
      -1,   431,   432,    -1,    96,    97,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,   452,   453,    69,    70,    71,    72,    73,    74,
      -1,   429,    -1,   431,   432,    -1,    -1,    -1,   429,    -1,
     431,   432,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    -1,    11,    -1,   452,   453,    -1,    -1,    -1,    -1,
      19,   452,   453,    22,    23,    -1,    25,    26,    27,    28,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    42,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    -1,    -1,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    -1,    -1,    -1,    -1,
      -1,    39,    40,    -1,    42,    -1,    39,    40,    46,    42,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    55,    11,    -1,
      58,    -1,    55,    -1,    -1,    58,    19,    96,    97,    22,
      23,    -1,    25,    26,    27,    28,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    42,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    96,    97,
      53,    54,    55,    96,    97,    -1,    -1,    -1,    -1,    -1,
      63,    64,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    -1,    22,    23,    -1,    25,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    42,    96,    97,    16,    46,    47,    48,    49,
      50,    -1,    -1,    53,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    -1,    55,    56,    -1,    -1,    59,    -1,
      -1,    39,    40,    -1,    42,    -1,    96,    97,    46,    -1,
      -1,    -1,    -1,    -1,    75,    76,    -1,    55,    16,    -1,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    95,    96,    97,    98,    99,   100,
     101,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    -1,    -1,    55,    96,    97,
      -1,    59,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    -1,
      -1,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    56,    -1,    -1,
      55,    -1,    -1,    62,    59,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      75,    76,    -1,    -1,    16,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    92,    -1,    -1,
      95,    96,    97,    98,    99,   100,   101,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      56,    -1,    -1,    55,    -1,    -1,    62,    59,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      92,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
      19,    -1,    -1,    22,    23,    -1,    25,    26,    27,    28,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    42,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    -1,    -1,    53,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    39,    40,    -1,    42,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      63,    64,    -1,    -1,    -1,    -1,    -1,    96,    97,    -1,
      -1,    -1,    -1,    -1,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    52,    -1,    -1,    -1,    -1,
      57,    -1,    -1,    96,    97,    62,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    52,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    52,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    52,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    62,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    88,    89,    90,
      91,    92,    93,    94,    95,    62,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    62,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    62,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    62,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    88,    89,    90,
      91,    92,    93,    94,    95,    62,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    62,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    56,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    56,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    56,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    57,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    60,    -1,    62,    -1,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    61,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    61,    62,    -1,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    61,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    62,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      65,    66,    -1,    68,    69,    70,    71,    72,    73,    74,
      65,    66,    -1,    -1,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    -1,    -1,    -1,    89,    90,    91,    92,    93,    94,
      95,    65,    66,    -1,    -1,    69,    70,    71,    72,    73,
      74,    65,    66,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    89,    -1,    91,    92,    93,
      94,    95,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,
      94,    95
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    11,    12,    13,    14,    15,    46,    97,   113,   114,
     115,   116,   117,   118,   119,   120,   189,    96,    97,   190,
     190,    51,     0,   115,   116,   117,    51,    77,    61,    61,
      98,   192,   167,   189,    16,    39,    40,    41,    42,    43,
      44,    45,    47,    48,    49,    50,    51,    55,    59,    75,
      76,    92,    95,    97,    99,   100,   101,   151,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   170,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   189,   190,   191,   192,   193,   194,
     195,   196,   197,    52,    52,    57,    55,   189,   190,    55,
     189,   190,    55,   151,    55,    56,   151,   168,   169,   189,
     151,   151,    51,    55,   100,   101,   162,   163,   174,   175,
     177,   178,   182,   183,   184,   185,   189,   190,    97,    61,
      62,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    88,    89,    90,    91,    92,    93,    94,    95,    55,
      58,   164,   165,   189,    51,    59,    61,    53,   126,   189,
      55,    51,    59,    55,    51,    59,    55,    52,    57,   151,
      57,    56,   151,    55,    58,    59,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,    46,    97,   188,   168,
     169,   189,    11,    19,    22,    23,    25,    26,    27,    28,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    54,
      55,    63,    64,   121,   122,   124,   125,   126,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   153,   154,   155,   162,   163,   171,   174,   175,   178,
     189,   151,   168,   189,   151,   168,   189,   151,   151,    56,
     151,   151,   189,    60,    56,    52,    51,    12,   121,   123,
     151,    61,    51,   121,    51,    51,    51,    51,    92,   192,
     195,    60,    61,    61,    61,   151,    61,    51,    51,    55,
     172,   173,   174,   175,   189,   178,   178,    54,   122,    61,
      61,    61,    61,    61,    77,    17,    18,    20,    21,    63,
      64,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    56,    52,    51,    56,    52,    51,    56,    57,
      56,   151,   168,    12,   121,    61,   151,    26,   151,   127,
     153,   154,   155,   178,   189,   151,    60,    60,    61,   168,
     168,    56,    57,   151,    51,    51,    51,    51,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,    56,
     168,    56,   168,    56,   151,    51,    52,    52,    51,    52,
      61,    29,    57,    52,    52,    52,   173,   151,   151,   151,
     151,    51,    52,    51,    52,    51,    52,   168,   121,   151,
     121,   151,   152,   151,   189,   126,    61,    61,    52,    52,
      57,    52,    57,    52,    57,   168,   168,   168,    52,    24,
      52,    61,    52,    29,    61,    61,   169,    61,   169,    61,
     169,    52,    52,    52,   121,    61,   127,   121,   151,    52,
      52,    52,    52,    52,    61,    61,    61,   121,   121
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   112,   113,   113,   114,   114,   114,   114,   114,   114,
     115,   116,   117,   117,   117,   117,   117,   118,   119,   120,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   122,   122,   123,   123,   124,   124,
     125,   125,   126,   126,   127,   127,   127,   127,   128,   128,
     129,   129,   129,   130,   131,   131,   132,   133,   133,   134,
     134,   135,   136,   137,   138,   139,   140,   141,   141,   142,
     143,   143,   144,   145,   146,   147,   147,   148,   149,   150,
     151,   151,   151,   152,   152,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   154,   154,   155,
     155,   156,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   159,   160,
     160,   160,   160,   161,   162,   162,   163,   163,   164,   164,
     164,   164,   164,   164,   165,   165,   165,   165,   166,   167,
     167,   167,   168,   168,   169,   169,   170,   170,   171,   172,
     172,   173,   173,   173,   174,   175,   176,   177,   178,   178,
     178,   178,   178,   178,   178,   178,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   189,   190,
     190,   191,   192,   193,   194,   194,   195,   195,   196,   197
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
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     2,     2,     1,     1,     2,     2,     4,     6,
       5,     7,     5,     7,     8,     9,     9,     9,     3,     3,
       1,     0,     1,     0,     3,     1,     2,     3,     3,     3,
       1,     1,     1,     1,     4,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     7,     2,     1,     2,     1,     1,     1
  };




#if IW7DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   261,   261,   262,   266,   268,   270,   272,   274,   276,
     281,   285,   290,   291,   292,   293,   294,   298,   303,   308,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   340,   341,   345,   347,   352,   354,
     359,   360,   364,   365,   369,   371,   373,   376,   380,   382,
     387,   389,   391,   396,   401,   403,   408,   413,   415,   420,
     422,   427,   432,   437,   442,   447,   452,   457,   459,   464,
     469,   471,   476,   481,   486,   491,   493,   498,   503,   508,
     513,   514,   515,   519,   520,   524,   526,   528,   530,   532,
     534,   536,   538,   540,   542,   544,   546,   551,   553,   558,
     560,   565,   570,   572,   574,   576,   578,   580,   582,   584,
     586,   588,   590,   592,   594,   596,   598,   600,   602,   604,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   618,
     619,   620,   621,   622,   623,   624,   625,   626,   627,   628,
     629,   630,   631,   632,   633,   634,   635,   636,   640,   645,
     647,   649,   651,   656,   661,   662,   665,   666,   670,   672,
     674,   676,   678,   680,   685,   687,   689,   691,   696,   701,
     703,   706,   710,   713,   717,   719,   724,   726,   731,   736,
     738,   743,   744,   745,   749,   754,   759,   764,   769,   770,
     771,   772,   773,   774,   775,   776,   777,   781,   786,   791,
     796,   801,   806,   811,   816,   821,   826,   831,   833,   838,
     840,   845,   850,   855,   860,   862,   867,   869,   874,   879
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
#line 4661 "parser.cpp"

#line 883 "parser.ypp"


void xsk::gsc::iw7::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
