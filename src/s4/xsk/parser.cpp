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
xsk::gsc::s4::parser::symbol_type S4lex(xsk::gsc::s4::lexer& lexer);

#line 47 "parser.cpp"

// Take the name prefix into account.
#define yylex   S4lex



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
#if S4DEBUG

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

#else // !S4DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !S4DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace gsc { namespace s4 {
#line 149 "parser.cpp"

  /// Build a parser object.
  parser::parser (xsk::gsc::s4::lexer& lexer_yyarg, xsk::gsc::ast::program::ptr& ast_yyarg)
#if S4DEBUG
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

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.YY_MOVE_OR_COPY< ast::expr_isdefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.YY_MOVE_OR_COPY< ast::expr_istring::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        value.YY_MOVE_OR_COPY< ast::expr_istrue::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.move< ast::expr_isdefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.move< ast::expr_istring::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        value.move< ast::expr_istrue::ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.copy< ast::expr_isdefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.copy< ast::expr_istring::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        value.copy< ast::expr_istrue::ptr > (that.value);
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

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.move< ast::expr_isdefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.move< ast::expr_istring::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        value.move< ast::expr_istrue::ptr > (that.value);
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

#if S4DEBUG
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

#if S4DEBUG
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
#endif // S4DEBUG

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

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        yylhs.value.emplace< ast::expr_isdefined::ptr > ();
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        yylhs.value.emplace< ast::expr_istring::ptr > ();
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        yylhs.value.emplace< ast::expr_istrue::ptr > ();
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
#line 267 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < ast::program::ptr > ()); }
#line 2080 "parser.cpp"
    break;

  case 3: // root: %empty
#line 268 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 2086 "parser.cpp"
    break;

  case 4: // program: program inline
#line 273 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 2092 "parser.cpp"
    break;

  case 5: // program: program include
#line 275 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2098 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 277 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2104 "parser.cpp"
    break;

  case 7: // program: inline
#line 279 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 2110 "parser.cpp"
    break;

  case 8: // program: include
#line 281 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2116 "parser.cpp"
    break;

  case 9: // program: declaration
#line 283 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2122 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 287 "parser.ypp"
                                 { lexer.push_header(yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2128 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 292 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2134 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 296 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2140 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 297 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2146 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 298 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2152 "parser.cpp"
    break;

  case 15: // declaration: decl_constant
#line 299 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_constant = std::move(yystack_[0].value.as < ast::decl_constant::ptr > ()); }
#line 2158 "parser.cpp"
    break;

  case 16: // declaration: decl_thread
#line 300 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2164 "parser.cpp"
    break;

  case 17: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 305 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2170 "parser.cpp"
    break;

  case 18: // decl_constant: expr_identifier "=" expr ";"
#line 310 "parser.ypp"
        { yylhs.value.as < ast::decl_constant::ptr > () = std::make_unique<ast::decl_constant>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2176 "parser.cpp"
    break;

  case 19: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 315 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2182 "parser.cpp"
    break;

  case 20: // stmt: stmt_block
#line 319 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2188 "parser.cpp"
    break;

  case 21: // stmt: stmt_call
#line 320 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2194 "parser.cpp"
    break;

  case 22: // stmt: stmt_assign
#line 321 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2200 "parser.cpp"
    break;

  case 23: // stmt: stmt_endon
#line 322 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2206 "parser.cpp"
    break;

  case 24: // stmt: stmt_notify
#line 323 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2212 "parser.cpp"
    break;

  case 25: // stmt: stmt_wait
#line 324 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2218 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittill
#line 325 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2224 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittillmatch
#line 326 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2230 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillframeend
#line 327 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2236 "parser.cpp"
    break;

  case 29: // stmt: stmt_waitframe
#line 328 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waitframe = std::move(yystack_[0].value.as < ast::stmt_waitframe::ptr > ()); }
#line 2242 "parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 329 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2248 "parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 330 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2254 "parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 331 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2260 "parser.cpp"
    break;

  case 33: // stmt: stmt_dowhile
#line 332 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2266 "parser.cpp"
    break;

  case 34: // stmt: stmt_for
#line 333 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2272 "parser.cpp"
    break;

  case 35: // stmt: stmt_foreach
#line 334 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2278 "parser.cpp"
    break;

  case 36: // stmt: stmt_switch
#line 335 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2284 "parser.cpp"
    break;

  case 37: // stmt: stmt_case
#line 336 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2290 "parser.cpp"
    break;

  case 38: // stmt: stmt_default
#line 337 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2296 "parser.cpp"
    break;

  case 39: // stmt: stmt_break
#line 338 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2302 "parser.cpp"
    break;

  case 40: // stmt: stmt_continue
#line 339 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2308 "parser.cpp"
    break;

  case 41: // stmt: stmt_return
#line 340 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2314 "parser.cpp"
    break;

  case 42: // stmt: stmt_breakpoint
#line 341 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_breakpoint = std::move(yystack_[0].value.as < ast::stmt_breakpoint::ptr > ()); }
#line 2320 "parser.cpp"
    break;

  case 43: // stmt: stmt_prof_begin
#line 342 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2326 "parser.cpp"
    break;

  case 44: // stmt: stmt_prof_end
#line 343 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2332 "parser.cpp"
    break;

  case 45: // stmt_or_dev: stmt
#line 347 "parser.ypp"
               { yylhs.value.as < ast::stmt > () = std::move(yystack_[0].value.as < ast::stmt > ()); }
#line 2338 "parser.cpp"
    break;

  case 46: // stmt_or_dev: stmt_dev
#line 348 "parser.ypp"
               { yylhs.value.as < ast::stmt > ().as_dev = std::move(yystack_[0].value.as < ast::stmt_dev::ptr > ()); }
#line 2344 "parser.cpp"
    break;

  case 47: // stmt_list: stmt_list stmt
#line 353 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2350 "parser.cpp"
    break;

  case 48: // stmt_list: stmt
#line 355 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2356 "parser.cpp"
    break;

  case 49: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 360 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2362 "parser.cpp"
    break;

  case 50: // stmt_or_dev_list: stmt_or_dev
#line 362 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2368 "parser.cpp"
    break;

  case 51: // stmt_dev: "/#" stmt_list "#/"
#line 366 "parser.ypp"
                                { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::move(yystack_[1].value.as < ast::stmt_list::ptr > ())); }
#line 2374 "parser.cpp"
    break;

  case 52: // stmt_dev: "/#" "#/"
#line 367 "parser.ypp"
                      { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2380 "parser.cpp"
    break;

  case 53: // stmt_block: "{" stmt_or_dev_list "}"
#line 371 "parser.ypp"
                                     { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2386 "parser.cpp"
    break;

  case 54: // stmt_block: "{" "}"
#line 372 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2392 "parser.cpp"
    break;

  case 55: // stmt_expr: expr_assign
#line 377 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2398 "parser.cpp"
    break;

  case 56: // stmt_expr: expr_increment
#line 379 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2404 "parser.cpp"
    break;

  case 57: // stmt_expr: expr_decrement
#line 381 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2410 "parser.cpp"
    break;

  case 58: // stmt_expr: %empty
#line 383 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2416 "parser.cpp"
    break;

  case 59: // stmt_call: expr_call ";"
#line 388 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2422 "parser.cpp"
    break;

  case 60: // stmt_call: expr_method ";"
#line 390 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2428 "parser.cpp"
    break;

  case 61: // stmt_assign: expr_assign ";"
#line 395 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2434 "parser.cpp"
    break;

  case 62: // stmt_assign: expr_increment ";"
#line 397 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2440 "parser.cpp"
    break;

  case 63: // stmt_assign: expr_decrement ";"
#line 399 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2446 "parser.cpp"
    break;

  case 64: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 404 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2452 "parser.cpp"
    break;

  case 65: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 409 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2458 "parser.cpp"
    break;

  case 66: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 411 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2464 "parser.cpp"
    break;

  case 67: // stmt_wait: "wait" expr ";"
#line 416 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2470 "parser.cpp"
    break;

  case 68: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 421 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2476 "parser.cpp"
    break;

  case 69: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 423 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2482 "parser.cpp"
    break;

  case 70: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 428 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2488 "parser.cpp"
    break;

  case 71: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 430 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2494 "parser.cpp"
    break;

  case 72: // stmt_waittillframeend: "waittillframeend" ";"
#line 435 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2500 "parser.cpp"
    break;

  case 73: // stmt_waitframe: "waitframe" ";"
#line 440 "parser.ypp"
        { yylhs.value.as < ast::stmt_waitframe::ptr > () = std::make_unique<ast::stmt_waitframe>(yylhs.location); }
#line 2506 "parser.cpp"
    break;

  case 74: // stmt_waitframe: "waitframe" "(" ")" ";"
#line 442 "parser.ypp"
        { yylhs.value.as < ast::stmt_waitframe::ptr > () = std::make_unique<ast::stmt_waitframe>(yylhs.location); }
#line 2512 "parser.cpp"
    break;

  case 75: // stmt_if: "if" "(" expr ")" stmt
#line 447 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2518 "parser.cpp"
    break;

  case 76: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 452 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2524 "parser.cpp"
    break;

  case 77: // stmt_while: "while" "(" expr ")" stmt
#line 457 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2530 "parser.cpp"
    break;

  case 78: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 462 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2536 "parser.cpp"
    break;

  case 79: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 467 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2542 "parser.cpp"
    break;

  case 80: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 472 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2548 "parser.cpp"
    break;

  case 81: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 474 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2554 "parser.cpp"
    break;

  case 82: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 479 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2560 "parser.cpp"
    break;

  case 83: // stmt_case: "case" expr_integer ":"
#line 484 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2566 "parser.cpp"
    break;

  case 84: // stmt_case: "case" expr_string ":"
#line 486 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2572 "parser.cpp"
    break;

  case 85: // stmt_default: "default" ":"
#line 491 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2578 "parser.cpp"
    break;

  case 86: // stmt_break: "break" ";"
#line 496 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2584 "parser.cpp"
    break;

  case 87: // stmt_continue: "continue" ";"
#line 501 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2590 "parser.cpp"
    break;

  case 88: // stmt_return: "return" expr ";"
#line 506 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2596 "parser.cpp"
    break;

  case 89: // stmt_return: "return" ";"
#line 508 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2602 "parser.cpp"
    break;

  case 90: // stmt_breakpoint: "breakpoint" ";"
#line 513 "parser.ypp"
        { yylhs.value.as < ast::stmt_breakpoint::ptr > () = std::make_unique<ast::stmt_breakpoint>(yylhs.location); }
#line 2608 "parser.cpp"
    break;

  case 91: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 518 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2614 "parser.cpp"
    break;

  case 92: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 523 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2620 "parser.cpp"
    break;

  case 93: // expr: expr_ternary
#line 527 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2626 "parser.cpp"
    break;

  case 94: // expr: expr_binary
#line 528 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2632 "parser.cpp"
    break;

  case 95: // expr: expr_primitive
#line 529 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2638 "parser.cpp"
    break;

  case 96: // expr_or_empty: expr
#line 533 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2644 "parser.cpp"
    break;

  case 97: // expr_or_empty: %empty
#line 534 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2650 "parser.cpp"
    break;

  case 98: // expr_assign: expr_tuple "=" expr
#line 539 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2656 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "=" expr
#line 541 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2662 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object "|=" expr
#line 543 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2668 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "&=" expr
#line 545 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2674 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "^=" expr
#line 547 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2680 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object "<<=" expr
#line 549 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2686 "parser.cpp"
    break;

  case 104: // expr_assign: expr_object ">>=" expr
#line 551 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2692 "parser.cpp"
    break;

  case 105: // expr_assign: expr_object "+=" expr
#line 553 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2698 "parser.cpp"
    break;

  case 106: // expr_assign: expr_object "-=" expr
#line 555 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2704 "parser.cpp"
    break;

  case 107: // expr_assign: expr_object "*=" expr
#line 557 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2710 "parser.cpp"
    break;

  case 108: // expr_assign: expr_object "/=" expr
#line 559 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2716 "parser.cpp"
    break;

  case 109: // expr_assign: expr_object "%=" expr
#line 561 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2722 "parser.cpp"
    break;

  case 110: // expr_increment: "++" expr_object
#line 566 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2728 "parser.cpp"
    break;

  case 111: // expr_increment: expr_object "++"
#line 568 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2734 "parser.cpp"
    break;

  case 112: // expr_decrement: "--" expr_object
#line 573 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2740 "parser.cpp"
    break;

  case 113: // expr_decrement: expr_object "--"
#line 575 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2746 "parser.cpp"
    break;

  case 114: // expr_ternary: expr "?" expr ":" expr
#line 580 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2752 "parser.cpp"
    break;

  case 115: // expr_binary: expr "||" expr
#line 585 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2758 "parser.cpp"
    break;

  case 116: // expr_binary: expr "&&" expr
#line 587 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2764 "parser.cpp"
    break;

  case 117: // expr_binary: expr "==" expr
#line 589 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2770 "parser.cpp"
    break;

  case 118: // expr_binary: expr "!=" expr
#line 591 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2776 "parser.cpp"
    break;

  case 119: // expr_binary: expr "<=" expr
#line 593 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2782 "parser.cpp"
    break;

  case 120: // expr_binary: expr ">=" expr
#line 595 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2788 "parser.cpp"
    break;

  case 121: // expr_binary: expr "<" expr
#line 597 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2794 "parser.cpp"
    break;

  case 122: // expr_binary: expr ">" expr
#line 599 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2800 "parser.cpp"
    break;

  case 123: // expr_binary: expr "|" expr
#line 601 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2806 "parser.cpp"
    break;

  case 124: // expr_binary: expr "&" expr
#line 603 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2812 "parser.cpp"
    break;

  case 125: // expr_binary: expr "^" expr
#line 605 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2818 "parser.cpp"
    break;

  case 126: // expr_binary: expr "<<" expr
#line 607 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2824 "parser.cpp"
    break;

  case 127: // expr_binary: expr ">>" expr
#line 609 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2830 "parser.cpp"
    break;

  case 128: // expr_binary: expr "+" expr
#line 611 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2836 "parser.cpp"
    break;

  case 129: // expr_binary: expr "-" expr
#line 613 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2842 "parser.cpp"
    break;

  case 130: // expr_binary: expr "*" expr
#line 615 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2848 "parser.cpp"
    break;

  case 131: // expr_binary: expr "/" expr
#line 617 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2854 "parser.cpp"
    break;

  case 132: // expr_binary: expr "%" expr
#line 619 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2860 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_complement
#line 623 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 2866 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_negate
#line 624 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_negate::ptr > ()); }
#line 2872 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_not
#line 625 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 2878 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_call
#line 626 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 2884 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_method
#line 627 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 2890 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_add_array
#line 628 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_add_array::ptr > ()); }
#line 2896 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_isdefined
#line 629 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_isdefined::ptr > ()); }
#line 2902 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_istrue
#line 630 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istrue::ptr > ()); }
#line 2908 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_reference
#line 631 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 2914 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_array
#line 632 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 2920 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_field
#line 633 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 2926 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_size
#line 634 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 2932 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_paren
#line 635 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 2938 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_thisthread
#line 636 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_thisthread::ptr > ()); }
#line 2944 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_empty_array
#line 637 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 2950 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_undefined
#line 638 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 2956 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_game
#line 639 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 2962 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_self
#line 640 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 2968 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_anim
#line 641 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 2974 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_level
#line 642 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 2980 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_animation
#line 643 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 2986 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_animtree
#line 644 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animtree::ptr > ()); }
#line 2992 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_identifier
#line 645 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 2998 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_istring
#line 646 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 3004 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_string
#line 647 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 3010 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_vector
#line 648 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 3016 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_float
#line 649 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 3022 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_integer
#line 650 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 3028 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_false
#line 651 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 3034 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_true
#line 652 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 3040 "parser.cpp"
    break;

  case 163: // expr_complement: "~" expr
#line 657 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3046 "parser.cpp"
    break;

  case 164: // expr_negate: "-" expr_identifier
#line 662 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()))); }
#line 3052 "parser.cpp"
    break;

  case 165: // expr_negate: "-" expr_paren
#line 664 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()))); }
#line 3058 "parser.cpp"
    break;

  case 166: // expr_negate: "-" expr_array
#line 666 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_array::ptr > ()))); }
#line 3064 "parser.cpp"
    break;

  case 167: // expr_negate: "-" expr_field
#line 668 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_field::ptr > ()))); }
#line 3070 "parser.cpp"
    break;

  case 168: // expr_not: "!" expr
#line 673 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3076 "parser.cpp"
    break;

  case 169: // expr_call: expr_function
#line 677 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3082 "parser.cpp"
    break;

  case 170: // expr_call: expr_pointer
#line 678 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3088 "parser.cpp"
    break;

  case 171: // expr_method: expr_object expr_function
#line 681 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3094 "parser.cpp"
    break;

  case 172: // expr_method: expr_object expr_pointer
#line 682 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3100 "parser.cpp"
    break;

  case 173: // expr_function: expr_identifier "(" expr_arguments ")"
#line 687 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3106 "parser.cpp"
    break;

  case 174: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 689 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3112 "parser.cpp"
    break;

  case 175: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 691 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3118 "parser.cpp"
    break;

  case 176: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 693 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3124 "parser.cpp"
    break;

  case 177: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 695 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3130 "parser.cpp"
    break;

  case 178: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 697 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3136 "parser.cpp"
    break;

  case 179: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 702 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3142 "parser.cpp"
    break;

  case 180: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 704 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3148 "parser.cpp"
    break;

  case 181: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 706 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3154 "parser.cpp"
    break;

  case 182: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 708 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::builtin); }
#line 3160 "parser.cpp"
    break;

  case 183: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 713 "parser.ypp"
        { yylhs.value.as < ast::expr_add_array::ptr > () = std::make_unique<ast::expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ())); }
#line 3166 "parser.cpp"
    break;

  case 184: // expr_parameters: expr_parameters "," expr_identifier
#line 718 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3172 "parser.cpp"
    break;

  case 185: // expr_parameters: expr_identifier
#line 720 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3178 "parser.cpp"
    break;

  case 186: // expr_parameters: %empty
#line 722 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 3184 "parser.cpp"
    break;

  case 187: // expr_arguments: expr_arguments_no_empty
#line 727 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 3190 "parser.cpp"
    break;

  case 188: // expr_arguments: %empty
#line 729 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3196 "parser.cpp"
    break;

  case 189: // expr_arguments_no_empty: expr_arguments "," expr
#line 734 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3202 "parser.cpp"
    break;

  case 190: // expr_arguments_no_empty: expr
#line 736 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3208 "parser.cpp"
    break;

  case 191: // expr_isdefined: "isdefined" "(" expr ")"
#line 741 "parser.ypp"
        { yylhs.value.as < ast::expr_isdefined::ptr > () = std::make_unique<ast::expr_isdefined>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3214 "parser.cpp"
    break;

  case 192: // expr_istrue: "istrue" "(" expr ")"
#line 746 "parser.ypp"
        { yylhs.value.as < ast::expr_istrue::ptr > () = std::make_unique<ast::expr_istrue>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3220 "parser.cpp"
    break;

  case 193: // expr_reference: "::" expr_identifier
#line 751 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3226 "parser.cpp"
    break;

  case 194: // expr_reference: expr_path "::" expr_identifier
#line 753 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3232 "parser.cpp"
    break;

  case 195: // expr_tuple: "[" expr_tuple_arguments "]"
#line 758 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[1].value.as < ast::expr_tuple::ptr > ()); }
#line 3238 "parser.cpp"
    break;

  case 196: // expr_tuple_arguments: expr_tuple_arguments "," expr_tuple_types
#line 763 "parser.ypp"
        { yylhs.value.as < ast::expr_tuple::ptr > () = std::move(yystack_[2].value.as < ast::expr_tuple::ptr > ()); yylhs.value.as < ast::expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3244 "parser.cpp"
    break;

  case 197: // expr_tuple_arguments: expr_tuple_types
#line 765 "parser.ypp"
        { yylhs.value.as < ast::expr_tuple::ptr > () = std::make_unique<ast::expr_tuple>(yylhs.location); yylhs.value.as < ast::expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3250 "parser.cpp"
    break;

  case 198: // expr_tuple_types: expr_array
#line 769 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3256 "parser.cpp"
    break;

  case 199: // expr_tuple_types: expr_field
#line 770 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3262 "parser.cpp"
    break;

  case 200: // expr_tuple_types: expr_identifier
#line 771 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3268 "parser.cpp"
    break;

  case 201: // expr_array: expr_object "[" expr "]"
#line 776 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3274 "parser.cpp"
    break;

  case 202: // expr_field: expr_object "." expr_identifier_nosize
#line 781 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3280 "parser.cpp"
    break;

  case 203: // expr_size: expr_object "." "size"
#line 786 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ())); }
#line 3286 "parser.cpp"
    break;

  case 204: // expr_paren: "(" expr ")"
#line 791 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3292 "parser.cpp"
    break;

  case 205: // expr_object: expr_call
#line 795 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3298 "parser.cpp"
    break;

  case 206: // expr_object: expr_method
#line 796 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3304 "parser.cpp"
    break;

  case 207: // expr_object: expr_array
#line 797 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3310 "parser.cpp"
    break;

  case 208: // expr_object: expr_field
#line 798 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3316 "parser.cpp"
    break;

  case 209: // expr_object: expr_game
#line 799 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3322 "parser.cpp"
    break;

  case 210: // expr_object: expr_self
#line 800 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3328 "parser.cpp"
    break;

  case 211: // expr_object: expr_anim
#line 801 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3334 "parser.cpp"
    break;

  case 212: // expr_object: expr_level
#line 802 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3340 "parser.cpp"
    break;

  case 213: // expr_object: expr_identifier
#line 803 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3346 "parser.cpp"
    break;

  case 214: // expr_thisthread: "thisthread"
#line 808 "parser.ypp"
        { yylhs.value.as < ast::expr_thisthread::ptr > () = std::make_unique<ast::expr_thisthread>(yylhs.location); }
#line 3352 "parser.cpp"
    break;

  case 215: // expr_empty_array: "[" "]"
#line 813 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3358 "parser.cpp"
    break;

  case 216: // expr_undefined: "undefined"
#line 818 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3364 "parser.cpp"
    break;

  case 217: // expr_game: "game"
#line 823 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3370 "parser.cpp"
    break;

  case 218: // expr_self: "self"
#line 828 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3376 "parser.cpp"
    break;

  case 219: // expr_anim: "anim"
#line 833 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3382 "parser.cpp"
    break;

  case 220: // expr_level: "level"
#line 838 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3388 "parser.cpp"
    break;

  case 221: // expr_animation: "%" "identifier"
#line 843 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3394 "parser.cpp"
    break;

  case 222: // expr_animtree: "#animtree"
#line 848 "parser.ypp"
        { yylhs.value.as < ast::expr_animtree::ptr > () = std::make_unique<ast::expr_animtree>(yylhs.location); }
#line 3400 "parser.cpp"
    break;

  case 223: // expr_identifier_nosize: "identifier"
#line 853 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3406 "parser.cpp"
    break;

  case 224: // expr_identifier: "identifier"
#line 858 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3412 "parser.cpp"
    break;

  case 225: // expr_identifier: "size"
#line 860 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, "size"); }
#line 3418 "parser.cpp"
    break;

  case 226: // expr_path: "identifier"
#line 865 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3424 "parser.cpp"
    break;

  case 227: // expr_path: "path"
#line 867 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3430 "parser.cpp"
    break;

  case 228: // expr_istring: "localized string"
#line 872 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3436 "parser.cpp"
    break;

  case 229: // expr_string: "string literal"
#line 877 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3442 "parser.cpp"
    break;

  case 230: // expr_vector: "(" expr "," expr "," expr ")"
#line 882 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3448 "parser.cpp"
    break;

  case 231: // expr_float: "-" "float"
#line 887 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3454 "parser.cpp"
    break;

  case 232: // expr_float: "float"
#line 889 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3460 "parser.cpp"
    break;

  case 233: // expr_integer: "-" "integer"
#line 894 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3466 "parser.cpp"
    break;

  case 234: // expr_integer: "integer"
#line 896 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3472 "parser.cpp"
    break;

  case 235: // expr_false: "false"
#line 901 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3478 "parser.cpp"
    break;

  case 236: // expr_true: "true"
#line 906 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3484 "parser.cpp"
    break;


#line 3488 "parser.cpp"

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
  "false", "undefined", "size", "game", "self", "anim", "level",
  "isdefined", "istrue", "(", ")", "{", "}", "[", "]", ",", ".", "::", ":",
  ";", "?", "++", "--", "<<", ">>", "||", "&&", "==", "!=", "<=", ">=",
  "<", ">", "!", "~", "=", "+=", "-=", "*=", "/=", "%=", "|=", "&=", "^=",
  ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/", "%", "path",
  "identifier", "string literal", "localized string", "float", "integer",
  "SIZEOF", "ADD_ARRAY", "THEN", "TERN", "NEG", "ANIMREF", "PREINC",
  "PREDEC", "POSTINC", "POSTDEC", "$accept", "root", "program", "inline",
  "include", "declaration", "decl_usingtree", "decl_constant",
  "decl_thread", "stmt", "stmt_or_dev", "stmt_list", "stmt_or_dev_list",
  "stmt_dev", "stmt_block", "stmt_expr", "stmt_call", "stmt_assign",
  "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_waitframe",
  "stmt_if", "stmt_ifelse", "stmt_while", "stmt_dowhile", "stmt_for",
  "stmt_foreach", "stmt_switch", "stmt_case", "stmt_default", "stmt_break",
  "stmt_continue", "stmt_return", "stmt_breakpoint", "stmt_prof_begin",
  "stmt_prof_end", "expr", "expr_or_empty", "expr_assign",
  "expr_increment", "expr_decrement", "expr_ternary", "expr_binary",
  "expr_primitive", "expr_complement", "expr_negate", "expr_not",
  "expr_call", "expr_method", "expr_function", "expr_pointer",
  "expr_add_array", "expr_parameters", "expr_arguments",
  "expr_arguments_no_empty", "expr_isdefined", "expr_istrue",
  "expr_reference", "expr_tuple", "expr_tuple_arguments",
  "expr_tuple_types", "expr_array", "expr_field", "expr_size",
  "expr_paren", "expr_object", "expr_thisthread", "expr_empty_array",
  "expr_undefined", "expr_game", "expr_self", "expr_anim", "expr_level",
  "expr_animation", "expr_animtree", "expr_identifier_nosize",
  "expr_identifier", "expr_path", "expr_istring", "expr_string",
  "expr_vector", "expr_float", "expr_integer", "expr_false", "expr_true", YY_NULLPTR
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

#if S4DEBUG
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
#if S4DEBUG
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
#if S4DEBUG
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


  const short parser::yypact_ninf_ = -296;

  const short parser::yytable_ninf_ = -227;

  const short
  parser::yypact_[] =
  {
       2,  -296,  -296,   -24,   -24,   -29,  -296,  -296,    27,     2,
    -296,  -296,  -296,  -296,  -296,  -296,   -35,  -296,  -296,   -30,
      -7,   -49,  -296,  -296,  -296,  -296,   -41,  1265,  -296,  -296,
    -296,    45,   -31,  -296,  -296,   -27,   -19,  -296,    66,  -296,
    -296,  -296,  -296,  -296,  -296,  -296,    72,    74,  1265,  1135,
     -41,  1265,  1265,   817,    37,    73,  -296,  -296,  -296,  2289,
    -296,  -296,  -296,  -296,  -296,  -296,   119,   430,  -296,  -296,
    -296,  -296,  -296,  -296,   604,   647,  -296,  -296,   750,  -296,
    -296,  -296,   904,   981,  1060,  1161,  -296,  -296,    -3,    84,
    -296,  -296,  -296,  -296,  -296,  -296,  -296,    89,   102,   -41,
     109,   115,   114,   120,   125,   122,   134,  1265,  1265,  1513,
    1135,  -296,  2372,   135,   146,  -296,  -296,  -296,  1265,   136,
    -296,  -296,  -296,  -296,   604,   647,  -296,  1225,  -296,  -296,
    -296,  -296,    -3,   144,  -296,  -296,  1265,  1265,  1265,  1265,
    1265,  1265,  1265,  1265,  1265,  1265,  1265,  1265,  1265,  1265,
    1265,  1265,  1265,  1265,  1265,  1330,   -26,  -296,  -296,   153,
    1265,   -41,  -296,    82,  -296,  -296,  1265,  1265,   -41,  1265,
    1265,   -41,  1265,  1679,  1713,  -296,  1265,  1261,  1265,  -296,
    1747,  1265,   112,   -41,  2254,    91,    91,  2403,  2413,   758,
     758,   176,   176,   176,   176,  2444,   680,   543,    46,    46,
    -296,  -296,  -296,  2059,  -296,  -296,  -296,   -14,  -296,   159,
    1028,  1265,   152,   -32,   166,  1456,   167,   172,   178,   179,
     -39,   177,   171,   175,  1200,   191,   188,   189,  -296,   150,
     382,   382,  -296,  -296,   949,  -296,  -296,  -296,  -296,  -296,
    -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,
    -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,
    -296,   192,   193,   194,   196,   198,   185,  -296,  -296,  1377,
     153,  2099,    22,   212,  2139,    24,   213,  2179,  -296,  -296,
    2218,   209,  2372,  1261,   159,  1265,  -296,  -296,  1265,  -296,
    -296,  1107,  2324,  -296,   220,  -296,  1265,   250,  1265,   833,
     -41,  1265,   174,   216,   218,  -296,  -296,  -296,  -296,  2359,
    -296,  1265,  1265,  1330,     8,  -296,   105,   113,    10,  1225,
    1225,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  1265,   229,
     232,   233,   234,  -296,  -296,  1265,  1265,  1265,  1265,  1265,
    1265,  1265,  1265,  1265,  1265,  1265,   230,  -296,  1265,   231,
    -296,  1265,   235,  1265,   238,  2372,    28,  -296,  -296,  -296,
     239,  1781,   242,  1815,   241,  -296,  -296,  -296,  1477,   -12,
    1849,  -296,  -296,  -296,    31,    32,  -296,   382,  2372,  1265,
    1265,  1265,  1265,  2372,  2372,  2372,  2372,  2372,  2372,  2372,
    2372,  2372,  2372,  2372,   243,    34,   255,    35,   259,  1883,
    1265,  -296,  -296,  1456,  1265,  1456,  1265,  1265,   -41,   102,
     251,   253,  -296,  1917,  1557,  1601,  1645,  1265,  -296,  1265,
    -296,  1265,  -296,    43,   289,  1951,  -296,  2372,   257,  1985,
     292,  -296,  -296,  -296,   264,   265,  1265,   269,  1265,   270,
    1265,    52,    81,    90,  -296,  1456,   293,   833,  1456,  1265,
    -296,  -296,   268,  -296,   301,  -296,   303,  -296,  -296,  -296,
    -296,  -296,   304,  -296,  2019,   296,   297,   298,  1456,  1456,
    -296,  -296,  -296,  -296,  -296
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   225,   224,     0,     2,
       7,     8,     9,    14,    15,    16,     0,   227,   226,     0,
       0,     0,     1,     4,     5,     6,   186,     0,    10,    11,
     229,     0,     0,   185,   222,     0,     0,   214,     0,   236,
     235,   216,   217,   218,   219,   220,     0,     0,     0,   188,
       0,     0,     0,     0,     0,   224,   228,   232,   234,     0,
      93,    94,    95,   133,   134,   135,   136,   137,   169,   170,
     138,   139,   140,   141,   142,   143,   144,   145,     0,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,     0,
     156,   157,   158,   159,   160,   161,   162,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,   215,   190,     0,   187,   193,   168,   163,     0,     0,
     231,   233,   205,   206,   166,   167,   165,     0,   209,   210,
     211,   212,   164,     0,   221,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   171,   172,     0,
     188,     0,    17,     0,    19,   184,     0,   188,     0,     0,
     188,     0,     0,     0,     0,   204,     0,   190,     0,   183,
       0,     0,     0,     0,     0,   126,   127,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   128,   129,
     130,   131,   132,     0,   203,   223,   202,     0,   187,   194,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,     0,
       0,     0,    45,    50,     0,    46,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,     0,     0,     0,   205,   206,     0,   207,   208,     0,
     213,     0,     0,     0,     0,     0,     0,     0,   191,   192,
       0,     0,   189,     0,     0,     0,   201,   173,   188,    52,
      48,     0,     0,    72,     0,    73,     0,     0,     0,    58,
       0,     0,     0,     0,     0,    85,    86,    87,    89,     0,
      90,   188,   188,     0,     0,   197,   207,   208,   213,   110,
     112,    53,    49,    61,    62,    63,    59,    60,     0,     0,
       0,     0,     0,   111,   113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   175,   188,     0,
     177,   188,     0,     0,     0,   114,     0,    51,    47,    67,
       0,     0,     0,     0,     0,    55,    56,    57,     0,     0,
       0,    84,    83,    88,     0,     0,   195,     0,    98,     0,
       0,     0,     0,    99,   105,   106,   107,   108,   109,   100,
     101,   102,   104,   103,     0,     0,     0,     0,     0,     0,
     188,   174,    74,     0,     0,     0,    97,     0,     0,     0,
       0,     0,   196,     0,     0,     0,     0,   188,   176,   188,
     178,   188,   230,     0,    75,     0,    77,    96,     0,     0,
       0,    82,    91,    92,     0,     0,   188,     0,   188,     0,
     188,     0,     0,     0,   179,     0,     0,    58,     0,     0,
      64,    66,   187,    69,   187,    71,   187,   180,   181,   182,
      76,    78,     0,    80,     0,     0,     0,     0,     0,     0,
      65,    68,    70,    79,    81
  };

  const short
  parser::yypgoto_[] =
  {
    -296,  -296,  -296,   354,   355,   356,  -296,  -296,  -296,  -144,
     133,  -296,  -296,  -296,   -97,   -77,  -296,  -296,  -296,  -296,
    -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,
    -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,  -296,
     200,  -296,  -295,  -292,  -291,  -296,  -296,  -296,  -296,  -296,
    -296,    -6,   101,   -73,   -66,  -296,  -296,  -137,   -47,  -296,
    -296,  -296,  -296,  -296,    -4,   337,   362,  -296,   321,   368,
    -296,  -296,  -296,   393,   442,   467,   501,  -296,  -296,  -296,
       0,     7,  -296,   -18,  -296,  -296,   160,  -296,  -296
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    11,    12,    13,    14,    15,   232,
     233,   291,   234,   235,   236,   364,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     112,   428,   261,   262,   263,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    32,   113,   208,    71,
      72,    73,   266,   314,   315,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   206,
      88,    89,    90,    91,    92,    93,    94,    95,    96
  };

  const short
  parser::yytable_[] =
  {
      16,   164,   114,    31,   365,   157,     6,   366,   367,    16,
      19,    20,   158,     1,     2,     3,     4,     5,   407,    26,
       6,   204,   294,   207,    98,    21,    33,    22,     6,    99,
     272,   100,   295,   275,    28,   101,   104,  -213,  -213,   103,
    -213,   287,   102,   105,  -213,    27,   178,   122,   408,     6,
     115,   160,    30,   132,   157,  -213,   302,    29,  -213,     7,
     133,   158,    30,   114,   160,    58,   290,   376,   377,  -200,
    -200,   297,    17,    55,   205,    17,    18,   347,   159,   350,
      17,    55,   178,   401,   178,   133,   410,   411,   178,   418,
     420,   178,   178,   210,   178,   178,  -213,  -213,   444,   165,
      97,   211,     7,   178,   212,   213,   214,   457,   215,   216,
     217,   218,   178,   219,   220,   221,   222,   223,   224,   225,
     226,   227,    35,    36,   106,    38,   107,   159,   108,     6,
      42,    43,    44,    45,   133,  -226,   458,   134,   163,   228,
     229,   178,   152,   153,   154,   459,   161,   358,   230,   231,
     178,   356,   365,   162,   123,   366,   367,   264,   163,  -205,
    -205,   209,  -205,   270,  -198,  -198,  -205,   166,   273,   167,
     133,   276,  -199,  -199,   374,   375,   168,  -205,   169,   170,
    -205,    17,    55,   284,   171,   150,   151,   152,   153,   154,
      35,    36,   172,    38,   181,   178,   157,     6,    42,    43,
      44,    45,   303,   158,   264,   179,   183,   160,   313,   264,
     270,   395,   205,   288,   397,   270,   293,   133,  -205,  -205,
     296,   298,   133,   122,   122,   122,   299,    59,   264,   318,
     270,   270,   300,   301,   270,   306,   133,   133,   133,   307,
     305,   133,   311,   312,   137,   138,   157,   157,   109,    17,
      55,   116,   117,   158,   158,   310,   323,   324,   325,   424,
     326,   426,   327,   423,   265,   328,   348,   351,   354,   159,
     150,   151,   152,   153,   154,   360,   133,   362,   121,   371,
     441,   372,   442,   379,   443,   264,   380,   381,   382,   394,
     396,   270,   400,   122,   398,   157,   404,   417,   133,   270,
     369,   460,   158,   402,   463,   406,   133,   173,   174,   419,
     177,   265,   431,   421,   445,   432,   265,   433,   180,   159,
     159,   447,   449,   465,   473,   474,   133,   133,   450,   451,
     123,   123,   123,   453,   455,   265,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   466,   461,   467,   468,
     470,   471,   472,    23,    24,    25,   271,   322,   159,   274,
     462,   122,   277,   412,   126,   133,   280,   318,   282,     0,
     304,   283,     0,     0,   133,     0,     0,     0,     0,   452,
     124,   454,   265,   456,     0,     0,     0,   264,     0,   264,
     123,     0,     0,   270,     0,   270,     0,     0,   430,     0,
     133,   292,   133,     0,     0,   125,     0,     0,     0,     0,
       0,   127,    35,    36,   309,    38,     0,     0,     0,     6,
      42,    43,    44,    45,     0,     0,     0,     0,     0,   264,
     119,   122,   264,     0,     0,   270,   128,   270,   270,     0,
       0,     0,   133,     0,   133,   133,     0,     0,     0,     0,
       0,     0,   264,   264,     0,     0,     0,     0,   270,   270,
    -206,  -206,     0,  -206,     0,   133,   133,  -206,   123,     0,
       0,    17,    55,     0,     0,   355,     0,     0,  -206,     0,
       0,  -206,     0,     0,     0,   129,   361,     0,   363,     0,
     267,   370,     0,     0,   265,     0,   265,     0,     0,     0,
       0,     0,     0,   283,     0,     0,     0,     0,     0,     0,
     130,     0,     0,     0,     0,   268,     0,     0,   378,  -206,
    -206,   269,     0,     0,     0,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   265,   267,   123,   265,
       0,     0,   267,   399,   131,     0,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   316,   267,   267,   265,
     265,   267,   268,     0,     0,     0,     0,   268,   269,   413,
     414,   415,   416,   269,     0,     0,     0,     0,     0,     0,
       0,   317,   268,   268,     0,     0,   268,   127,   319,   320,
       0,     0,   269,   128,   425,   129,   427,   429,   128,     0,
       0,   137,   138,     0,     0,   141,   142,   143,   144,   145,
     146,     0,   128,   128,   128,     0,     0,   128,   267,     0,
     130,     0,     0,     0,     0,   148,   267,   150,   151,   152,
     153,   154,     0,     0,  -207,  -207,     0,  -207,     0,   464,
       0,  -207,   129,   268,     0,     0,     0,   129,     0,   269,
       0,   268,  -207,     0,   131,  -207,     0,   368,     0,     0,
       0,   129,   129,   129,     0,     0,   129,   130,     0,     0,
       0,     0,   130,     0,   128,     0,     0,  -208,  -208,     0,
    -208,     0,   128,     0,  -208,     0,   130,   130,   130,     0,
       0,   130,     0,  -207,  -207,  -208,     0,     0,  -208,     0,
       0,   131,     0,     0,   316,     0,   131,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     131,   131,   131,   129,     0,   131,     0,     0,     0,   317,
     267,   129,   267,     0,     0,   127,  -208,  -208,   137,   138,
       0,     0,   141,   142,   143,   144,   145,   146,   130,     0,
       0,     0,     0,     0,     0,   268,   130,   268,     0,     0,
     128,   269,     0,   269,   150,   151,   152,   153,   154,     0,
       0,     0,   267,     0,   267,   267,     0,     0,     0,     0,
      35,    36,   131,    38,     0,     0,   128,     6,   128,     0,
     131,     0,     0,     0,     0,   267,   267,   268,   155,   268,
     268,   156,     0,   269,     0,   368,   269,     0,     0,   129,
       0,     0,     0,     0,     0,     0,   137,   138,     0,     0,
     268,   268,   143,   144,   145,   146,   269,   269,   128,     0,
     128,   128,     0,     0,   130,   129,     0,   129,     0,    17,
      55,     0,   150,   151,   152,   153,   154,    35,    36,     0,
      38,   128,   128,     0,     6,    42,    43,    44,    45,     0,
     130,   118,   130,    35,    36,   119,    38,     0,   131,     0,
       6,    42,    43,    44,    45,     0,     0,   129,     0,   129,
     129,   229,     0,     0,     0,     0,     0,     0,     0,   230,
     231,     0,     0,     0,   131,     0,   131,     0,     0,     0,
     129,   129,   130,     0,   130,   130,    17,    55,     0,     0,
     120,   121,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,    55,     0,   130,   130,     0,     0,     0,
       0,     0,     0,     0,  -209,  -209,   131,  -209,   131,   131,
       0,  -209,     0,     0,     0,     0,     0,     0,     0,     0,
     210,     0,  -209,     0,     0,  -209,     0,     0,   211,   131,
     131,   212,   213,   214,     0,   215,   216,   217,   218,     0,
     219,   220,   221,   222,   223,   224,   225,   226,   227,    35,
      36,     0,    38,     0,     0,     0,     6,    42,    43,    44,
      45,     0,     0,  -209,  -209,   163,   321,   229,     0,     0,
       0,     0,     0,     0,     0,   230,   231,     0,     0,     0,
       0,  -210,  -210,     0,  -210,     0,     0,     0,  -210,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -210,
     289,     0,  -210,     0,     0,     0,     0,   211,    17,    55,
     212,   213,   214,     0,   215,   216,   217,   218,     0,   219,
     220,   221,   222,   223,   224,   225,   226,   227,    35,    36,
       0,    38,     0,     0,     0,     6,    42,    43,    44,    45,
    -210,  -210,     0,     0,   163,     0,   229,     0,     0,     0,
       0,     0,     0,     0,   230,   231,     0,     0,     0,     0,
    -211,  -211,     0,  -211,     0,     0,     0,  -211,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -211,   357,
       0,  -211,     0,     0,     0,     0,   211,    17,    55,   212,
     213,   214,     0,   215,   216,   217,   218,     0,   219,   220,
     221,   222,   223,   224,   225,   226,   227,    35,    36,     0,
      38,    34,     0,     0,     6,    42,    43,    44,    45,  -211,
    -211,     0,     0,   163,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,   231,    35,    36,    37,    38,    39,
      40,    41,     6,    42,    43,    44,    45,    46,    47,    48,
       0,     0,     0,   110,   111,     0,     0,    50,     0,     0,
       0,  -212,  -212,     0,  -212,     0,    17,    55,  -212,     0,
       0,     0,     0,    51,    52,     0,    34,     0,     0,  -212,
       0,     0,  -212,     0,     0,     0,     0,     0,     0,     0,
      53,     0,     0,    54,    17,    55,    30,    56,    57,    58,
      35,    36,    37,    38,    39,    40,    41,     6,    42,    43,
      44,    45,    46,    47,    48,     0,     0,     0,    49,     0,
    -212,  -212,    50,     0,   308,    35,    36,     0,    38,     0,
       0,     0,     6,     0,     0,     0,     0,     0,    51,    52,
       0,    34,     0,   155,     0,     0,   182,     0,     0,     0,
       0,     0,     0,     0,     0,    53,     0,     0,    54,    17,
      55,    30,    56,    57,    58,    35,    36,    37,    38,    39,
      40,    41,     6,    42,    43,    44,    45,    46,    47,    48,
     281,     0,     0,    49,    17,    55,   136,    50,     0,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,     0,
       0,     0,     0,    51,    52,     0,    34,     0,     0,     0,
       0,     0,   147,   148,   149,   150,   151,   152,   153,   154,
      53,     0,     0,    54,    17,    55,    30,    56,    57,    58,
      35,    36,    37,    38,    39,    40,    41,     6,    42,    43,
      44,    45,    46,    47,    48,     0,     0,     0,   110,     0,
       0,     0,    50,     0,   329,   330,     0,   331,   332,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,    52,
       0,     0,     0,     0,     0,     0,     0,    35,    36,     0,
      38,     0,     0,     0,     6,    53,     0,     0,    54,    17,
      55,    30,    56,    57,    58,   155,     0,     0,   182,     0,
       0,     0,     0,   333,   334,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,     0,     0,
       0,     0,     0,     0,     0,   211,    17,    55,   212,   213,
     214,     0,   215,   216,   217,   218,     0,   219,   220,   221,
     222,   223,   224,   225,   226,   227,    35,    36,     0,    38,
       0,     0,     0,     6,    42,    43,    44,    45,     0,     0,
       0,     0,   163,     0,   229,     0,     0,    35,    36,     0,
      38,     0,   230,   231,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   155,     0,     0,   182,     0,
       0,     0,     0,   333,   334,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    55,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   175,     0,
       0,     0,     0,   176,     0,     0,    17,    55,   136,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   148,   149,   150,   151,   152,
     153,   154,   435,     0,     0,     0,     0,   436,     0,     0,
       0,     0,   136,     0,     0,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   153,   154,   437,     0,     0,     0,
       0,   438,     0,     0,     0,     0,   136,     0,     0,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   147,   148,   149,   150,   151,   152,   153,   154,
     439,     0,     0,     0,     0,   440,     0,     0,     0,     0,
     136,     0,     0,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   278,     0,   147,   148,   149,   150,
     151,   152,   153,   154,   136,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   279,     0,
     147,   148,   149,   150,   151,   152,   153,   154,   136,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   175,     0,   147,   148,   149,   150,   151,   152,
     153,   154,   136,     0,     0,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   403,     0,   147,   148,
     149,   150,   151,   152,   153,   154,   136,     0,     0,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     405,     0,   147,   148,   149,   150,   151,   152,   153,   154,
     136,     0,     0,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   409,     0,   147,   148,   149,   150,
     151,   152,   153,   154,   136,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   422,     0,
     147,   148,   149,   150,   151,   152,   153,   154,   136,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   434,     0,   147,   148,   149,   150,   151,   152,
     153,   154,   136,     0,     0,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   446,     0,   147,   148,
     149,   150,   151,   152,   153,   154,   136,     0,     0,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     448,     0,   147,   148,   149,   150,   151,   152,   153,   154,
     136,     0,     0,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   469,     0,   147,   148,   149,   150,
     151,   152,   153,   154,   136,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   152,   153,   154,   286,     0,
       0,     0,     0,     0,   136,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   152,   153,   154,   346,     0,
       0,     0,     0,     0,   136,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   152,   153,   154,   349,     0,
       0,     0,     0,     0,   136,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   152,   153,   154,   352,     0,
       0,     0,     0,     0,   136,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   152,   153,   154,   353,     0,
       0,     0,     0,   136,     0,     0,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   147,
     148,   149,   150,   151,   152,   153,   154,   285,     0,   136,
       0,     0,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   147,   148,   149,   150,   151,
     152,   153,   154,   135,   136,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   152,   153,   154,   359,   136,
       0,     0,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   147,   148,   149,   150,   151,
     152,   153,   154,   373,   136,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   136,     0,     0,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,     0,     0,
       0,     0,     0,   147,   148,   149,   150,   151,   152,   153,
     154,   137,   138,     0,   140,   141,   142,   143,   144,   145,
     146,   137,   138,     0,     0,   141,   142,   143,   144,   145,
     146,     0,     0,     0,   147,   148,   149,   150,   151,   152,
     153,   154,     0,     0,   147,   148,   149,   150,   151,   152,
     153,   154,   137,   138,     0,     0,   141,   142,   143,   144,
     145,   146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   148,   149,   150,   151,
     152,   153,   154
  };

  const short
  parser::yycheck_[] =
  {
       0,    98,    49,    21,   299,    78,    47,   299,   299,     9,
       3,     4,    78,    11,    12,    13,    14,    15,    30,    54,
      47,    47,    54,   160,    55,    54,    26,     0,    47,    60,
     167,    58,    64,   170,    64,    35,    36,    40,    41,    58,
      43,    55,    35,    36,    47,    80,    60,    53,    60,    47,
      50,    54,   101,    53,   127,    58,    95,    64,    61,   100,
      53,   127,   101,   110,    54,   104,   210,    59,    60,    59,
      60,   215,    99,   100,   100,    99,   100,    55,    78,    55,
      99,   100,    60,    55,    60,    78,    55,    55,    60,    55,
      55,    60,    60,    11,    60,    60,    99,   100,    55,    99,
      55,    19,   100,    60,    22,    23,    24,    55,    26,    27,
      28,    29,    60,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    58,    43,    54,   127,    54,    47,
      48,    49,    50,    51,   127,    62,    55,   100,    56,    57,
      58,    60,    96,    97,    98,    55,    62,   291,    66,    67,
      60,   288,   447,    64,    53,   447,   447,   163,    56,    40,
      41,   161,    43,   163,    59,    60,    47,    58,   168,    54,
     163,   171,    59,    60,   311,   312,    62,    58,    58,    54,
      61,    99,   100,   183,    62,    94,    95,    96,    97,    98,
      40,    41,    58,    43,    58,    60,   269,    47,    48,    49,
      50,    51,   220,   269,   210,    59,    62,    54,    58,   215,
     210,   348,   100,    54,   351,   215,    64,   210,    99,   100,
      54,    54,   215,   229,   230,   231,    54,    27,   234,   229,
     230,   231,    54,    54,   234,    64,   229,   230,   231,    64,
      63,   234,    54,    54,    68,    69,   319,   320,    48,    99,
     100,    51,    52,   319,   320,    64,    64,    64,    64,   403,
      64,   405,    64,   400,   163,    80,    54,    54,    59,   269,
      94,    95,    96,    97,    98,    55,   269,    27,   104,    63,
     417,    63,   419,    54,   421,   291,    54,    54,    54,    59,
      59,   291,    54,   299,    59,   368,    54,    54,   291,   299,
     300,   445,   368,    64,   448,    64,   299,   107,   108,    54,
     110,   210,   409,    54,    25,    64,   215,    64,   118,   319,
     320,    64,    30,    55,   468,   469,   319,   320,    64,    64,
     229,   230,   231,    64,    64,   234,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,    55,    64,    55,    55,
      64,    64,    64,     9,     9,     9,   166,   234,   368,   169,
     447,   377,   172,   377,    53,   368,   176,   377,   178,    -1,
     220,   181,    -1,    -1,   377,    -1,    -1,    -1,    -1,   436,
      53,   438,   291,   440,    -1,    -1,    -1,   403,    -1,   405,
     299,    -1,    -1,   403,    -1,   405,    -1,    -1,   408,    -1,
     403,   211,   405,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    53,    40,    41,   224,    43,    -1,    -1,    -1,    47,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,   445,
      58,   447,   448,    -1,    -1,   445,    53,   447,   448,    -1,
      -1,    -1,   445,    -1,   447,   448,    -1,    -1,    -1,    -1,
      -1,    -1,   468,   469,    -1,    -1,    -1,    -1,   468,   469,
      40,    41,    -1,    43,    -1,   468,   469,    47,   377,    -1,
      -1,    99,   100,    -1,    -1,   285,    -1,    -1,    58,    -1,
      -1,    61,    -1,    -1,    -1,    53,   296,    -1,   298,    -1,
     163,   301,    -1,    -1,   403,    -1,   405,    -1,    -1,    -1,
      -1,    -1,    -1,   313,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,   163,    -1,    -1,   328,    99,
     100,   163,    -1,    -1,    -1,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   445,   210,   447,   448,
      -1,    -1,   215,   353,    53,    -1,   163,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   229,   230,   231,   468,
     469,   234,   210,    -1,    -1,    -1,    -1,   215,   210,   379,
     380,   381,   382,   215,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   229,   230,   231,    -1,    -1,   234,   229,   230,   231,
      -1,    -1,   234,   210,   404,   163,   406,   407,   215,    -1,
      -1,    68,    69,    -1,    -1,    72,    73,    74,    75,    76,
      77,    -1,   229,   230,   231,    -1,    -1,   234,   291,    -1,
     163,    -1,    -1,    -1,    -1,    92,   299,    94,    95,    96,
      97,    98,    -1,    -1,    40,    41,    -1,    43,    -1,   449,
      -1,    47,   210,   291,    -1,    -1,    -1,   215,    -1,   291,
      -1,   299,    58,    -1,   163,    61,    -1,   299,    -1,    -1,
      -1,   229,   230,   231,    -1,    -1,   234,   210,    -1,    -1,
      -1,    -1,   215,    -1,   291,    -1,    -1,    40,    41,    -1,
      43,    -1,   299,    -1,    47,    -1,   229,   230,   231,    -1,
      -1,   234,    -1,    99,   100,    58,    -1,    -1,    61,    -1,
      -1,   210,    -1,    -1,   377,    -1,   215,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     229,   230,   231,   291,    -1,   234,    -1,    -1,    -1,   377,
     403,   299,   405,    -1,    -1,   377,    99,   100,    68,    69,
      -1,    -1,    72,    73,    74,    75,    76,    77,   291,    -1,
      -1,    -1,    -1,    -1,    -1,   403,   299,   405,    -1,    -1,
     377,   403,    -1,   405,    94,    95,    96,    97,    98,    -1,
      -1,    -1,   445,    -1,   447,   448,    -1,    -1,    -1,    -1,
      40,    41,   291,    43,    -1,    -1,   403,    47,   405,    -1,
     299,    -1,    -1,    -1,    -1,   468,   469,   445,    58,   447,
     448,    61,    -1,   445,    -1,   447,   448,    -1,    -1,   377,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    -1,    -1,
     468,   469,    74,    75,    76,    77,   468,   469,   445,    -1,
     447,   448,    -1,    -1,   377,   403,    -1,   405,    -1,    99,
     100,    -1,    94,    95,    96,    97,    98,    40,    41,    -1,
      43,   468,   469,    -1,    47,    48,    49,    50,    51,    -1,
     403,    54,   405,    40,    41,    58,    43,    -1,   377,    -1,
      47,    48,    49,    50,    51,    -1,    -1,   445,    -1,   447,
     448,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    -1,    -1,    -1,   403,    -1,   405,    -1,    -1,    -1,
     468,   469,   445,    -1,   447,   448,    99,   100,    -1,    -1,
     103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    99,   100,    -1,   468,   469,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,   445,    43,   447,   448,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      11,    -1,    58,    -1,    -1,    61,    -1,    -1,    19,   468,
     469,    22,    23,    24,    -1,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    -1,    -1,    99,   100,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,
      -1,    40,    41,    -1,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      12,    -1,    61,    -1,    -1,    -1,    -1,    19,    99,   100,
      22,    23,    24,    -1,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,    -1,    -1,    -1,    47,    48,    49,    50,    51,
      99,   100,    -1,    -1,    56,    -1,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      40,    41,    -1,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    12,
      -1,    61,    -1,    -1,    -1,    -1,    19,    99,   100,    22,
      23,    24,    -1,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    16,    -1,    -1,    47,    48,    49,    50,    51,    99,
     100,    -1,    -1,    56,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    58,    59,    -1,    -1,    62,    -1,    -1,
      -1,    40,    41,    -1,    43,    -1,    99,   100,    47,    -1,
      -1,    -1,    -1,    78,    79,    -1,    16,    -1,    -1,    58,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    58,    -1,
      99,   100,    62,    -1,    64,    40,    41,    -1,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    78,    79,
      -1,    16,    -1,    58,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      59,    -1,    -1,    58,    99,   100,    65,    62,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    -1,    -1,    78,    79,    -1,    16,    -1,    -1,    -1,
      -1,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    62,    -1,    17,    18,    -1,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,
      43,    -1,    -1,    -1,    47,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,    58,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    99,   100,    22,    23,
      24,    -1,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    43,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    56,    -1,    58,    -1,    -1,    40,    41,    -1,
      43,    -1,    66,    67,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    99,   100,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    55,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    99,   100,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    55,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    55,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      55,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    65,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      65,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    65,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      65,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    60,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      92,    93,    94,    95,    96,    97,    98,    63,    -1,    65,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,
      96,    97,    98,    64,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    64,    65,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,
      96,    97,    98,    64,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    65,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      91,    92,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    68,    69,    -1,    71,    72,    73,    74,    75,    76,
      77,    68,    69,    -1,    -1,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    -1,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    68,    69,    -1,    -1,    72,    73,    74,    75,
      76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    92,    93,    94,    95,
      96,    97,    98
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    11,    12,    13,    14,    15,    47,   100,   116,   117,
     118,   119,   120,   121,   122,   123,   195,    99,   100,   196,
     196,    54,     0,   118,   119,   120,    54,    80,    64,    64,
     101,   198,   171,   195,    16,    40,    41,    42,    43,    44,
      45,    46,    48,    49,    50,    51,    52,    53,    54,    58,
      62,    78,    79,    95,    98,   100,   102,   103,   104,   155,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   174,   175,   176,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   195,   196,
     197,   198,   199,   200,   201,   202,   203,    55,    55,    60,
      58,   195,   196,    58,   195,   196,    58,    54,    54,   155,
      58,    59,   155,   172,   173,   195,   155,   155,    54,    58,
     103,   104,   166,   167,   180,   181,   183,   184,   188,   189,
     190,   191,   195,   196,   100,    64,    65,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    91,    92,    93,
      94,    95,    96,    97,    98,    58,    61,   168,   169,   195,
      54,    62,    64,    56,   129,   195,    58,    54,    62,    58,
      54,    62,    58,   155,   155,    55,    60,   155,    60,    59,
     155,    58,    61,    62,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,    47,   100,   194,   172,   173,   195,
      11,    19,    22,    23,    24,    26,    27,    28,    29,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    57,    58,
      66,    67,   124,   125,   127,   128,   129,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   157,   158,   159,   166,   167,   177,   180,   181,   184,
     195,   155,   172,   195,   155,   172,   195,   155,    55,    55,
     155,    59,   155,   155,   195,    63,    59,    55,    54,    12,
     124,   126,   155,    64,    54,    64,    54,   124,    54,    54,
      54,    54,    95,   198,   201,    63,    64,    64,    64,   155,
      64,    54,    54,    58,   178,   179,   180,   181,   195,   184,
     184,    57,   125,    64,    64,    64,    64,    64,    80,    17,
      18,    20,    21,    66,    67,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    59,    55,    54,    59,
      55,    54,    59,    60,    59,   155,   172,    12,   124,    64,
      55,   155,    27,   155,   130,   157,   158,   159,   184,   195,
     155,    63,    63,    64,   172,   172,    59,    60,   155,    54,
      54,    54,    54,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,    59,   172,    59,   172,    59,   155,
      54,    55,    64,    55,    54,    55,    64,    30,    60,    55,
      55,    55,   179,   155,   155,   155,   155,    54,    55,    54,
      55,    54,    55,   172,   124,   155,   124,   155,   156,   155,
     195,   129,    64,    64,    55,    55,    60,    55,    60,    55,
      60,   172,   172,   172,    55,    25,    55,    64,    55,    30,
      64,    64,   173,    64,   173,    64,   173,    55,    55,    55,
     124,    64,   130,   124,   155,    55,    55,    55,    55,    55,
      64,    64,    64,   124,   124
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   115,   116,   116,   117,   117,   117,   117,   117,   117,
     118,   119,   120,   120,   120,   120,   120,   121,   122,   123,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   128,   129,   129,   130,   130,   130,   130,   131,
     131,   132,   132,   132,   133,   134,   134,   135,   136,   136,
     137,   137,   138,   139,   139,   140,   141,   142,   143,   144,
     145,   145,   146,   147,   147,   148,   149,   150,   151,   151,
     152,   153,   154,   155,   155,   155,   156,   156,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     158,   158,   159,   159,   160,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   163,   164,   164,   164,   164,   165,   166,
     166,   167,   167,   168,   168,   168,   168,   168,   168,   169,
     169,   169,   169,   170,   171,   171,   171,   172,   172,   173,
     173,   174,   175,   176,   176,   177,   178,   178,   179,   179,
     179,   180,   181,   182,   183,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   195,   196,   196,   197,   198,
     199,   200,   200,   201,   201,   202,   203
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
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     5,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     1,
       1,     2,     2,     4,     6,     5,     7,     5,     7,     8,
       9,     9,     9,     3,     3,     1,     0,     1,     0,     3,
       1,     4,     4,     2,     3,     3,     3,     1,     1,     1,
       1,     4,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       7,     2,     1,     2,     1,     1,     1
  };




#if S4DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   267,   267,   268,   272,   274,   276,   278,   280,   282,
     287,   291,   296,   297,   298,   299,   300,   304,   309,   314,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   347,   348,   352,   354,   359,
     361,   366,   367,   371,   372,   376,   378,   380,   383,   387,
     389,   394,   396,   398,   403,   408,   410,   415,   420,   422,
     427,   429,   434,   439,   441,   446,   451,   456,   461,   466,
     471,   473,   478,   483,   485,   490,   495,   500,   505,   507,
     512,   517,   522,   527,   528,   529,   533,   534,   538,   540,
     542,   544,   546,   548,   550,   552,   554,   556,   558,   560,
     565,   567,   572,   574,   579,   584,   586,   588,   590,   592,
     594,   596,   598,   600,   602,   604,   606,   608,   610,   612,
     614,   616,   618,   623,   624,   625,   626,   627,   628,   629,
     630,   631,   632,   633,   634,   635,   636,   637,   638,   639,
     640,   641,   642,   643,   644,   645,   646,   647,   648,   649,
     650,   651,   652,   656,   661,   663,   665,   667,   672,   677,
     678,   681,   682,   686,   688,   690,   692,   694,   696,   701,
     703,   705,   707,   712,   717,   719,   722,   726,   729,   733,
     735,   740,   745,   750,   752,   757,   762,   764,   769,   770,
     771,   775,   780,   785,   790,   795,   796,   797,   798,   799,
     800,   801,   802,   803,   807,   812,   817,   822,   827,   832,
     837,   842,   847,   852,   857,   859,   864,   866,   871,   876,
     881,   886,   888,   893,   895,   900,   905
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
#endif // S4DEBUG


#line 13 "parser.ypp"
} } } // xsk::gsc::s4
#line 4808 "parser.cpp"

#line 909 "parser.ypp"


void xsk::gsc::s4::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
