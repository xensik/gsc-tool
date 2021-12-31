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
#line 40 "parser.ypp"

#include "stdafx.hpp"
#include "parser.hpp"
#include "lexer.hpp"
using namespace xsk::gsc;
xsk::gsc::s2::parser::symbol_type S2lex(yyscan_t yyscanner, xsk::gsc::context* ctx);

#line 47 "parser.cpp"

// Take the name prefix into account.
#define yylex   S2lex



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
#if S2DEBUG

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

#else // !S2DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !S2DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace gsc { namespace s2 {
#line 149 "parser.cpp"

  /// Build a parser object.
  parser::parser (yyscan_t yyscanner_yyarg, xsk::gsc::context* ctx_yyarg, xsk::gsc::ast::program::ptr& ast_yyarg)
#if S2DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      yyscanner (yyscanner_yyarg),
      ctx (ctx_yyarg),
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
      case symbol_kind::S_COLOR: // "color"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INT_DEC: // "int"
      case symbol_kind::S_INT_OCT: // "octal int"
      case symbol_kind::S_INT_BIN: // "binary int"
      case symbol_kind::S_INT_HEX: // "hexadecimal int"
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
      case symbol_kind::S_COLOR: // "color"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INT_DEC: // "int"
      case symbol_kind::S_INT_OCT: // "octal int"
      case symbol_kind::S_INT_BIN: // "binary int"
      case symbol_kind::S_INT_HEX: // "hexadecimal int"
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
      case symbol_kind::S_COLOR: // "color"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INT_DEC: // "int"
      case symbol_kind::S_INT_OCT: // "octal int"
      case symbol_kind::S_INT_BIN: // "binary int"
      case symbol_kind::S_INT_HEX: // "hexadecimal int"
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
      case symbol_kind::S_COLOR: // "color"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INT_DEC: // "int"
      case symbol_kind::S_INT_OCT: // "octal int"
      case symbol_kind::S_INT_BIN: // "binary int"
      case symbol_kind::S_INT_HEX: // "hexadecimal int"
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

#if S2DEBUG
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

#if S2DEBUG
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
#endif // S2DEBUG

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
            symbol_type yylookahead (yylex (yyscanner, ctx));
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
      case symbol_kind::S_COLOR: // "color"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INT_DEC: // "int"
      case symbol_kind::S_INT_OCT: // "octal int"
      case symbol_kind::S_INT_BIN: // "binary int"
      case symbol_kind::S_INT_HEX: // "hexadecimal int"
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
#line 254 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < ast::program::ptr > ()); }
#line 2001 "parser.cpp"
    break;

  case 3: // root: %empty
#line 255 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 2007 "parser.cpp"
    break;

  case 4: // program: program inline
#line 260 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 2013 "parser.cpp"
    break;

  case 5: // program: program include
#line 262 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2019 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 264 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2025 "parser.cpp"
    break;

  case 7: // program: inline
#line 266 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 2031 "parser.cpp"
    break;

  case 8: // program: include
#line 268 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2037 "parser.cpp"
    break;

  case 9: // program: declaration
#line 270 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2043 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 274 "parser.ypp"
                                 { s2_push_header(ctx, yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2049 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 279 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2055 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 283 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2061 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 284 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2067 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 285 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2073 "parser.cpp"
    break;

  case 15: // declaration: decl_constant
#line 286 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_constant = std::move(yystack_[0].value.as < ast::decl_constant::ptr > ()); }
#line 2079 "parser.cpp"
    break;

  case 16: // declaration: decl_thread
#line 287 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2085 "parser.cpp"
    break;

  case 17: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 292 "parser.ypp"
        { ctx->restrict_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2091 "parser.cpp"
    break;

  case 18: // decl_constant: expr_identifier "=" expr ";"
#line 297 "parser.ypp"
        { yylhs.value.as < ast::decl_constant::ptr > () = std::make_unique<ast::decl_constant>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2097 "parser.cpp"
    break;

  case 19: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 302 "parser.ypp"
        { ctx->restrict_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2103 "parser.cpp"
    break;

  case 20: // stmt: stmt_dev
#line 306 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2109 "parser.cpp"
    break;

  case 21: // stmt: stmt_block
#line 307 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2115 "parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 308 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2121 "parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 309 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2127 "parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 310 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2133 "parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 311 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2139 "parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 312 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2145 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 313 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2151 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 314 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2157 "parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 315 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2163 "parser.cpp"
    break;

  case 30: // stmt: stmt_waitframe
#line 316 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waitframe = std::move(yystack_[0].value.as < ast::stmt_waitframe::ptr > ()); }
#line 2169 "parser.cpp"
    break;

  case 31: // stmt: stmt_if
#line 317 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2175 "parser.cpp"
    break;

  case 32: // stmt: stmt_ifelse
#line 318 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2181 "parser.cpp"
    break;

  case 33: // stmt: stmt_while
#line 319 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2187 "parser.cpp"
    break;

  case 34: // stmt: stmt_dowhile
#line 320 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2193 "parser.cpp"
    break;

  case 35: // stmt: stmt_for
#line 321 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2199 "parser.cpp"
    break;

  case 36: // stmt: stmt_foreach
#line 322 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2205 "parser.cpp"
    break;

  case 37: // stmt: stmt_switch
#line 323 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2211 "parser.cpp"
    break;

  case 38: // stmt: stmt_case
#line 324 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2217 "parser.cpp"
    break;

  case 39: // stmt: stmt_default
#line 325 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2223 "parser.cpp"
    break;

  case 40: // stmt: stmt_break
#line 326 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2229 "parser.cpp"
    break;

  case 41: // stmt: stmt_continue
#line 327 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2235 "parser.cpp"
    break;

  case 42: // stmt: stmt_return
#line 328 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2241 "parser.cpp"
    break;

  case 43: // stmt: stmt_breakpoint
#line 329 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_breakpoint = std::move(yystack_[0].value.as < ast::stmt_breakpoint::ptr > ()); }
#line 2247 "parser.cpp"
    break;

  case 44: // stmt: stmt_prof_begin
#line 330 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2253 "parser.cpp"
    break;

  case 45: // stmt: stmt_prof_end
#line 331 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2259 "parser.cpp"
    break;

  case 46: // stmt_dev: "/#" stmt_list "#/"
#line 335 "parser.ypp"
                                { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2265 "parser.cpp"
    break;

  case 47: // stmt_dev: "/#" "#/"
#line 336 "parser.ypp"
                      { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2271 "parser.cpp"
    break;

  case 48: // stmt_block: "{" stmt_list "}"
#line 340 "parser.ypp"
                              { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2277 "parser.cpp"
    break;

  case 49: // stmt_block: "{" "}"
#line 341 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2283 "parser.cpp"
    break;

  case 50: // stmt_list: stmt_list stmt
#line 346 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2289 "parser.cpp"
    break;

  case 51: // stmt_list: stmt
#line 348 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2295 "parser.cpp"
    break;

  case 52: // stmt_expr: expr_assign
#line 353 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2301 "parser.cpp"
    break;

  case 53: // stmt_expr: expr_increment
#line 355 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2307 "parser.cpp"
    break;

  case 54: // stmt_expr: expr_decrement
#line 357 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2313 "parser.cpp"
    break;

  case 55: // stmt_expr: %empty
#line 359 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2319 "parser.cpp"
    break;

  case 56: // stmt_call: expr_call ";"
#line 364 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2325 "parser.cpp"
    break;

  case 57: // stmt_call: expr_method ";"
#line 366 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2331 "parser.cpp"
    break;

  case 58: // stmt_assign: expr_assign ";"
#line 371 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2337 "parser.cpp"
    break;

  case 59: // stmt_assign: expr_increment ";"
#line 373 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2343 "parser.cpp"
    break;

  case 60: // stmt_assign: expr_decrement ";"
#line 375 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2349 "parser.cpp"
    break;

  case 61: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 380 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2355 "parser.cpp"
    break;

  case 62: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 385 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2361 "parser.cpp"
    break;

  case 63: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 387 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2367 "parser.cpp"
    break;

  case 64: // stmt_wait: "wait" expr ";"
#line 392 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2373 "parser.cpp"
    break;

  case 65: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 397 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2379 "parser.cpp"
    break;

  case 66: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 399 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2385 "parser.cpp"
    break;

  case 67: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 404 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2391 "parser.cpp"
    break;

  case 68: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 406 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2397 "parser.cpp"
    break;

  case 69: // stmt_waittillframeend: "waittillframeend" ";"
#line 411 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2403 "parser.cpp"
    break;

  case 70: // stmt_waitframe: "waitframe" ";"
#line 416 "parser.ypp"
        { yylhs.value.as < ast::stmt_waitframe::ptr > () = std::make_unique<ast::stmt_waitframe>(yylhs.location); }
#line 2409 "parser.cpp"
    break;

  case 71: // stmt_waitframe: "waitframe" "(" ")" ";"
#line 418 "parser.ypp"
        { yylhs.value.as < ast::stmt_waitframe::ptr > () = std::make_unique<ast::stmt_waitframe>(yylhs.location); }
#line 2415 "parser.cpp"
    break;

  case 72: // stmt_if: "if" "(" expr ")" stmt
#line 423 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2421 "parser.cpp"
    break;

  case 73: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 428 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2427 "parser.cpp"
    break;

  case 74: // stmt_while: "while" "(" expr ")" stmt
#line 433 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2433 "parser.cpp"
    break;

  case 75: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 438 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2439 "parser.cpp"
    break;

  case 76: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 443 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2445 "parser.cpp"
    break;

  case 77: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 448 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2451 "parser.cpp"
    break;

  case 78: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 450 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2457 "parser.cpp"
    break;

  case 79: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 455 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2463 "parser.cpp"
    break;

  case 80: // stmt_case: "case" expr_integer ":"
#line 460 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2469 "parser.cpp"
    break;

  case 81: // stmt_case: "case" expr_string ":"
#line 462 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2475 "parser.cpp"
    break;

  case 82: // stmt_default: "default" ":"
#line 467 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2481 "parser.cpp"
    break;

  case 83: // stmt_break: "break" ";"
#line 472 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2487 "parser.cpp"
    break;

  case 84: // stmt_continue: "continue" ";"
#line 477 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2493 "parser.cpp"
    break;

  case 85: // stmt_return: "return" expr ";"
#line 482 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2499 "parser.cpp"
    break;

  case 86: // stmt_return: "return" ";"
#line 484 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2505 "parser.cpp"
    break;

  case 87: // stmt_breakpoint: "breakpoint" ";"
#line 489 "parser.ypp"
        { yylhs.value.as < ast::stmt_breakpoint::ptr > () = std::make_unique<ast::stmt_breakpoint>(yylhs.location); }
#line 2511 "parser.cpp"
    break;

  case 88: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 494 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2517 "parser.cpp"
    break;

  case 89: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 499 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2523 "parser.cpp"
    break;

  case 90: // expr: expr_ternary
#line 503 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2529 "parser.cpp"
    break;

  case 91: // expr: expr_binary
#line 504 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2535 "parser.cpp"
    break;

  case 92: // expr: expr_primitive
#line 505 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2541 "parser.cpp"
    break;

  case 93: // expr_or_empty: expr
#line 509 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2547 "parser.cpp"
    break;

  case 94: // expr_or_empty: %empty
#line 510 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2553 "parser.cpp"
    break;

  case 95: // expr_assign: expr_object "=" expr
#line 515 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2559 "parser.cpp"
    break;

  case 96: // expr_assign: expr_object "|=" expr
#line 517 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2565 "parser.cpp"
    break;

  case 97: // expr_assign: expr_object "&=" expr
#line 519 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2571 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object "^=" expr
#line 521 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2577 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "<<=" expr
#line 523 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2583 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object ">>=" expr
#line 525 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2589 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "+=" expr
#line 527 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2595 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "-=" expr
#line 529 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2601 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object "*=" expr
#line 531 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2607 "parser.cpp"
    break;

  case 104: // expr_assign: expr_object "/=" expr
#line 533 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2613 "parser.cpp"
    break;

  case 105: // expr_assign: expr_object "%=" expr
#line 535 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2619 "parser.cpp"
    break;

  case 106: // expr_increment: "++" expr_object
#line 540 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2625 "parser.cpp"
    break;

  case 107: // expr_increment: expr_object "++"
#line 542 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2631 "parser.cpp"
    break;

  case 108: // expr_decrement: "--" expr_object
#line 547 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2637 "parser.cpp"
    break;

  case 109: // expr_decrement: expr_object "--"
#line 549 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2643 "parser.cpp"
    break;

  case 110: // expr_ternary: expr "?" expr ":" expr
#line 554 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2649 "parser.cpp"
    break;

  case 111: // expr_binary: expr "||" expr
#line 559 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2655 "parser.cpp"
    break;

  case 112: // expr_binary: expr "&&" expr
#line 561 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2661 "parser.cpp"
    break;

  case 113: // expr_binary: expr "==" expr
#line 563 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2667 "parser.cpp"
    break;

  case 114: // expr_binary: expr "!=" expr
#line 565 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2673 "parser.cpp"
    break;

  case 115: // expr_binary: expr "<=" expr
#line 567 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2679 "parser.cpp"
    break;

  case 116: // expr_binary: expr ">=" expr
#line 569 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2685 "parser.cpp"
    break;

  case 117: // expr_binary: expr "<" expr
#line 571 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2691 "parser.cpp"
    break;

  case 118: // expr_binary: expr ">" expr
#line 573 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2697 "parser.cpp"
    break;

  case 119: // expr_binary: expr "|" expr
#line 575 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2703 "parser.cpp"
    break;

  case 120: // expr_binary: expr "&" expr
#line 577 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2709 "parser.cpp"
    break;

  case 121: // expr_binary: expr "^" expr
#line 579 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2715 "parser.cpp"
    break;

  case 122: // expr_binary: expr "<<" expr
#line 581 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2721 "parser.cpp"
    break;

  case 123: // expr_binary: expr ">>" expr
#line 583 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2727 "parser.cpp"
    break;

  case 124: // expr_binary: expr "+" expr
#line 585 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2733 "parser.cpp"
    break;

  case 125: // expr_binary: expr "-" expr
#line 587 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2739 "parser.cpp"
    break;

  case 126: // expr_binary: expr "*" expr
#line 589 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2745 "parser.cpp"
    break;

  case 127: // expr_binary: expr "/" expr
#line 591 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2751 "parser.cpp"
    break;

  case 128: // expr_binary: expr "%" expr
#line 593 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2757 "parser.cpp"
    break;

  case 129: // expr_primitive: expr_complement
#line 597 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 2763 "parser.cpp"
    break;

  case 130: // expr_primitive: expr_not
#line 598 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 2769 "parser.cpp"
    break;

  case 131: // expr_primitive: expr_call
#line 599 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 2775 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_method
#line 600 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 2781 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_add_array
#line 601 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_add_array::ptr > ()); }
#line 2787 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_reference
#line 602 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 2793 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_array
#line 603 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 2799 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_field
#line 604 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 2805 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_size
#line 605 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 2811 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_paren
#line 606 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 2817 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_thisthread
#line 607 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_thisthread::ptr > ()); }
#line 2823 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_empty_array
#line 608 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 2829 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_undefined
#line 609 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 2835 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_game
#line 610 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 2841 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_self
#line 611 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 2847 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_anim
#line 612 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 2853 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_level
#line 613 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 2859 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_animation
#line 614 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 2865 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_animtree
#line 615 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animtree::ptr > ()); }
#line 2871 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_identifier
#line 616 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 2877 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_istring
#line 617 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 2883 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_string
#line 618 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 2889 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_color
#line 619 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_color::ptr > ()); }
#line 2895 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_vector
#line 620 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 2901 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_float
#line 621 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 2907 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_integer
#line 622 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 2913 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_false
#line 623 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 2919 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_true
#line 624 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 2925 "parser.cpp"
    break;

  case 157: // expr_complement: "~" expr
#line 629 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2931 "parser.cpp"
    break;

  case 158: // expr_not: "!" expr
#line 634 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2937 "parser.cpp"
    break;

  case 159: // expr_call: expr_function
#line 638 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2943 "parser.cpp"
    break;

  case 160: // expr_call: expr_pointer
#line 639 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2949 "parser.cpp"
    break;

  case 161: // expr_method: expr_object expr_function
#line 642 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 2955 "parser.cpp"
    break;

  case 162: // expr_method: expr_object expr_pointer
#line 643 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 2961 "parser.cpp"
    break;

  case 163: // expr_function: expr_identifier "(" expr_arguments ")"
#line 648 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 2967 "parser.cpp"
    break;

  case 164: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 650 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 2973 "parser.cpp"
    break;

  case 165: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 652 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 2979 "parser.cpp"
    break;

  case 166: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 654 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 2985 "parser.cpp"
    break;

  case 167: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 656 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 2991 "parser.cpp"
    break;

  case 168: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 658 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 2997 "parser.cpp"
    break;

  case 169: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 663 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3003 "parser.cpp"
    break;

  case 170: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 665 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3009 "parser.cpp"
    break;

  case 171: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 667 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 3015 "parser.cpp"
    break;

  case 172: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 669 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::builtin); }
#line 3021 "parser.cpp"
    break;

  case 173: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 674 "parser.ypp"
        { yylhs.value.as < ast::expr_add_array::ptr > () = std::make_unique<ast::expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ())); }
#line 3027 "parser.cpp"
    break;

  case 174: // expr_parameters: expr_parameters "," expr_identifier
#line 679 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3033 "parser.cpp"
    break;

  case 175: // expr_parameters: expr_identifier
#line 681 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3039 "parser.cpp"
    break;

  case 176: // expr_parameters: %empty
#line 683 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 3045 "parser.cpp"
    break;

  case 177: // expr_arguments: expr_arguments_no_empty
#line 688 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 3051 "parser.cpp"
    break;

  case 178: // expr_arguments: %empty
#line 690 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3057 "parser.cpp"
    break;

  case 179: // expr_arguments_no_empty: expr_arguments "," expr
#line 695 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3063 "parser.cpp"
    break;

  case 180: // expr_arguments_no_empty: expr
#line 697 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3069 "parser.cpp"
    break;

  case 181: // expr_reference: "::" expr_identifier
#line 702 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3075 "parser.cpp"
    break;

  case 182: // expr_reference: expr_path "::" expr_identifier
#line 704 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3081 "parser.cpp"
    break;

  case 183: // expr_array: expr_object "[" expr "]"
#line 709 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3087 "parser.cpp"
    break;

  case 184: // expr_field: expr_object "." expr_identifier
#line 714 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3093 "parser.cpp"
    break;

  case 185: // expr_size: expr_object ".size"
#line 719 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3099 "parser.cpp"
    break;

  case 186: // expr_paren: "(" expr ")"
#line 724 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3105 "parser.cpp"
    break;

  case 187: // expr_object: expr_call
#line 728 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3111 "parser.cpp"
    break;

  case 188: // expr_object: expr_method
#line 729 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3117 "parser.cpp"
    break;

  case 189: // expr_object: expr_array
#line 730 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3123 "parser.cpp"
    break;

  case 190: // expr_object: expr_field
#line 731 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3129 "parser.cpp"
    break;

  case 191: // expr_object: expr_game
#line 732 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3135 "parser.cpp"
    break;

  case 192: // expr_object: expr_self
#line 733 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3141 "parser.cpp"
    break;

  case 193: // expr_object: expr_anim
#line 734 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3147 "parser.cpp"
    break;

  case 194: // expr_object: expr_level
#line 735 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3153 "parser.cpp"
    break;

  case 195: // expr_object: expr_identifier
#line 736 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3159 "parser.cpp"
    break;

  case 196: // expr_thisthread: "thisthread"
#line 741 "parser.ypp"
        { yylhs.value.as < ast::expr_thisthread::ptr > () = std::make_unique<ast::expr_thisthread>(yylhs.location); }
#line 3165 "parser.cpp"
    break;

  case 197: // expr_empty_array: "[" "]"
#line 746 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3171 "parser.cpp"
    break;

  case 198: // expr_undefined: "undefined"
#line 751 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3177 "parser.cpp"
    break;

  case 199: // expr_game: "game"
#line 756 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3183 "parser.cpp"
    break;

  case 200: // expr_self: "self"
#line 761 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3189 "parser.cpp"
    break;

  case 201: // expr_anim: "anim"
#line 766 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3195 "parser.cpp"
    break;

  case 202: // expr_level: "level"
#line 771 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3201 "parser.cpp"
    break;

  case 203: // expr_animation: "%" "identifier"
#line 776 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3207 "parser.cpp"
    break;

  case 204: // expr_animtree: "#animtree"
#line 781 "parser.ypp"
        { yylhs.value.as < ast::expr_animtree::ptr > () = std::make_unique<ast::expr_animtree>(yylhs.location); }
#line 3213 "parser.cpp"
    break;

  case 205: // expr_identifier: "identifier"
#line 786 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3219 "parser.cpp"
    break;

  case 206: // expr_path: "path"
#line 791 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3225 "parser.cpp"
    break;

  case 207: // expr_path: expr_identifier
#line 793 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < ast::expr_identifier::ptr > ()->value); }
#line 3231 "parser.cpp"
    break;

  case 208: // expr_istring: "localized string"
#line 798 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3237 "parser.cpp"
    break;

  case 209: // expr_string: "string literal"
#line 803 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3243 "parser.cpp"
    break;

  case 210: // expr_color: "color"
#line 808 "parser.ypp"
        { yylhs.value.as < ast::expr_color::ptr > () = std::make_unique<ast::expr_color>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3249 "parser.cpp"
    break;

  case 211: // expr_vector: "(" expr "," expr "," expr ")"
#line 813 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3255 "parser.cpp"
    break;

  case 212: // expr_float: "-" "float"
#line 818 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3261 "parser.cpp"
    break;

  case 213: // expr_float: "float"
#line 820 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3267 "parser.cpp"
    break;

  case 214: // expr_integer: "-" "int"
#line 825 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3273 "parser.cpp"
    break;

  case 215: // expr_integer: "int"
#line 827 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3279 "parser.cpp"
    break;

  case 216: // expr_integer: "octal int"
#line 829 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3285 "parser.cpp"
    break;

  case 217: // expr_integer: "binary int"
#line 831 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3291 "parser.cpp"
    break;

  case 218: // expr_integer: "hexadecimal int"
#line 833 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3297 "parser.cpp"
    break;

  case 219: // expr_false: "false"
#line 838 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3303 "parser.cpp"
    break;

  case 220: // expr_true: "true"
#line 843 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3309 "parser.cpp"
    break;


#line 3313 "parser.cpp"

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
  "waittill", "waittillmatch", "waittillframeend", "waitframe", "if",
  "else", "do", "while", "for", "foreach", "in", "switch", "case",
  "default", "break", "continue", "return", "breakpoint", "prof_begin",
  "prof_end", "thread", "childthread", "thisthread", "call", "true",
  "false", "undefined", ".size", "game", "self", "anim", "level", "(", ")",
  "{", "}", "[", "]", ",", ".", "::", ":", ";", "?", "++", "--", "<<",
  ">>", "||", "&&", "==", "!=", "<=", ">=", "<", ">", "!", "~", "=", "+=",
  "-=", "*=", "/=", "%=", "|=", "&=", "^=", ">>=", "<<=", "|", "&", "^",
  "+", "-", "*", "/", "%", "path", "identifier", "string literal",
  "localized string", "color", "float", "int", "octal int", "binary int",
  "hexadecimal int", "ADD_ARRAY", "THEN", "TERN", "NEG", "ANIMREF",
  "PREINC", "PREDEC", "POSTINC", "POSTDEC", "$accept", "root", "program",
  "inline", "include", "declaration", "decl_usingtree", "decl_constant",
  "decl_thread", "stmt", "stmt_dev", "stmt_block", "stmt_list",
  "stmt_expr", "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify",
  "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_waitframe", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch",
  "stmt_case", "stmt_default", "stmt_break", "stmt_continue",
  "stmt_return", "stmt_breakpoint", "stmt_prof_begin", "stmt_prof_end",
  "expr", "expr_or_empty", "expr_assign", "expr_increment",
  "expr_decrement", "expr_ternary", "expr_binary", "expr_primitive",
  "expr_complement", "expr_not", "expr_call", "expr_method",
  "expr_function", "expr_pointer", "expr_add_array", "expr_parameters",
  "expr_arguments", "expr_arguments_no_empty", "expr_reference",
  "expr_array", "expr_field", "expr_size", "expr_paren", "expr_object",
  "expr_thisthread", "expr_empty_array", "expr_undefined", "expr_game",
  "expr_self", "expr_anim", "expr_level", "expr_animation",
  "expr_animtree", "expr_identifier", "expr_path", "expr_istring",
  "expr_string", "expr_color", "expr_vector", "expr_float", "expr_integer",
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

#if S2DEBUG
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
#if S2DEBUG
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
#if S2DEBUG
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


  const short parser::yypact_ninf_ = -269;

  const short parser::yytable_ninf_ = -208;

  const short
  parser::yypact_[] =
  {
      15,  -269,  -269,    10,    10,   -32,  -269,    26,    15,  -269,
    -269,  -269,  -269,  -269,  -269,   -20,  -269,  -269,   -24,   -21,
     -49,  -269,  -269,  -269,  -269,   -30,   858,  -269,  -269,  -269,
      25,   -18,  -269,  -269,   -35,   -25,  -269,    28,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,   858,   724,   -30,   858,   858,
      55,   -17,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  2001,
    -269,  -269,  -269,  -269,  -269,   198,   435,  -269,  -269,  -269,
    -269,   589,   690,  -269,  -269,   814,  -269,  -269,  -269,   819,
     881,   886,  1084,  -269,  -269,   552,    67,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,    80,    34,   -30,    75,   107,
     105,   112,   120,   115,   121,  1287,   724,  -269,  2084,   118,
     128,  -269,  -269,  -269,  -269,  -269,  -269,  -269,   858,   858,
     858,   858,   858,   858,   858,   858,   858,   858,   858,   858,
     858,   858,   858,   858,   858,   858,   858,  -269,   925,   -30,
    -269,  -269,   135,   132,   858,   -30,  -269,  1021,  -269,  -269,
     858,   858,   -30,   858,   858,   -30,   858,  -269,   858,  1731,
     858,  -269,  1966,   117,   117,   920,  2115,  2166,  2166,   309,
     309,   309,   309,  2125,   632,  2156,    54,    54,  -269,  -269,
    -269,  1771,  -269,   -30,    13,  -269,   141,  1072,   858,   136,
      12,   145,  1225,   147,   150,   153,   155,    33,   156,   152,
     157,   791,   161,   166,   173,  -269,   177,   130,   130,  -269,
    -269,  -269,  1123,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,   172,   174,   175,
     178,   180,  -269,  -269,    36,  -269,  -269,  -269,  -269,     7,
    1811,    22,   183,  1851,    29,   192,  1891,  1930,   193,  2084,
     858,  -269,   141,  -269,   858,  -269,  1174,  2036,  -269,   200,
    -269,   858,   228,   858,    -4,   -30,   858,   158,   199,   202,
    -269,  -269,  -269,  -269,  2071,  -269,   858,   858,   858,  -269,
    -269,    69,    69,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
     207,   212,   213,   214,  -269,  -269,   858,   858,   858,   858,
     858,   858,   858,   858,   858,   858,   858,   210,  -269,   858,
     211,  -269,   858,   215,   858,   217,  2084,    38,  -269,  -269,
     209,  1453,   221,  1487,   222,  -269,  -269,  -269,  1251,    -7,
    1521,  -269,  -269,  -269,    44,    45,  1731,   858,   858,   858,
     858,  2084,  2084,  2084,  2084,  2084,  2084,  2084,  2084,  2084,
    2084,  2084,   223,    46,   225,    53,   227,  1555,   858,  -269,
    -269,  1225,   858,  1225,   858,   858,   -30,    34,   224,   232,
    1589,  1331,  1375,  1419,   858,  -269,   858,  -269,   858,  -269,
      77,   256,  1623,  -269,  2084,   235,  1657,   255,  -269,  -269,
    -269,   236,   239,   858,   240,   858,   241,   858,    87,    88,
      98,  -269,  1225,   246,    -4,  1225,   858,  -269,  -269,   234,
    -269,   254,  -269,   257,  -269,  -269,  -269,  -269,  -269,   258,
    -269,  1691,   247,   250,   253,  1225,  1225,  -269,  -269,  -269,
    -269,  -269
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   205,     0,     2,     7,
       8,     9,    14,    15,    16,     0,   206,   207,     0,     0,
       0,     1,     4,     5,     6,   176,     0,    10,    11,   209,
       0,     0,   175,   204,     0,     0,   196,     0,   220,   219,
     198,   199,   200,   201,   202,     0,   178,     0,     0,     0,
       0,     0,   208,   210,   213,   215,   216,   217,   218,     0,
      90,    91,    92,   129,   130,   131,   132,   159,   160,   133,
     134,   135,   136,   137,   138,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,     0,   149,   150,   151,
     152,   153,   154,   155,   156,     0,     0,     0,     0,   207,
       0,     0,   207,     0,     0,     0,   178,   197,   180,     0,
     177,   181,   158,   157,   212,   214,   203,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   185,     0,     0,
     161,   162,   207,     0,   178,     0,    17,     0,    19,   174,
       0,   178,     0,     0,   178,     0,     0,   186,     0,   180,
       0,   173,     0,   122,   123,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   124,   125,   126,   127,
     128,     0,   184,     0,     0,   177,   182,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,     0,     0,     0,    51,
      20,    21,     0,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     0,     0,     0,
     187,   188,   189,   190,     0,   191,   192,   193,   194,   195,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,   183,     0,   163,   178,    47,     0,     0,    69,     0,
      70,     0,     0,     0,    55,     0,     0,     0,     0,     0,
      82,    83,    84,    86,     0,    87,   178,   178,     0,   187,
     188,   106,   108,    48,    50,    58,    59,    60,    56,    57,
       0,     0,     0,     0,   107,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   165,   178,
       0,   167,   178,     0,     0,     0,   110,     0,    46,    64,
       0,     0,     0,     0,     0,    52,    53,    54,     0,     0,
       0,    81,    80,    85,     0,     0,     0,     0,     0,     0,
       0,    95,   101,   102,   103,   104,   105,    96,    97,    98,
     100,    99,     0,     0,     0,     0,     0,     0,   178,   164,
      71,     0,     0,     0,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   178,   166,   178,   168,   178,   211,
       0,    72,     0,    74,    93,     0,     0,     0,    79,    88,
      89,     0,     0,   178,     0,   178,     0,   178,     0,     0,
       0,   169,     0,     0,    55,     0,     0,    61,    63,   177,
      66,   177,    68,   177,   170,   171,   172,    73,    75,     0,
      77,     0,     0,     0,     0,     0,     0,    62,    65,    67,
      76,    78
  };

  const short
  parser::yypgoto_[] =
  {
    -269,  -269,  -269,   273,   319,   321,  -269,  -269,  -269,   163,
    -269,   -94,   143,   -83,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,   190,  -269,
    -268,  -260,  -258,  -269,  -269,  -269,  -269,  -269,  -130,   -26,
     -70,   -68,  -269,  -269,   325,   -45,  -269,   -12,   219,  -269,
    -269,   245,  -269,  -269,  -269,   252,   300,   335,   369,  -269,
    -269,     0,     6,  -269,    -9,  -269,  -269,  -269,   137,  -269,
    -269
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     7,     8,     9,    10,    11,    12,    13,    14,   209,
     210,   211,   212,   334,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   108,   395,
     237,   238,   239,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    31,   109,   185,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94
  };

  const short
  parser::yytable_[] =
  {
      15,   110,   148,    17,    17,   140,   335,   141,    15,    18,
      19,    30,    20,    98,   336,   375,   337,   240,     1,     2,
       3,     4,     5,   101,    25,    32,    21,    96,    34,    35,
      27,    37,    97,    28,    99,   102,    41,    42,    43,    44,
     100,   103,    29,   376,   206,   300,   301,   111,   302,   303,
      26,   144,   207,   208,    16,     6,   269,   240,   263,  -207,
       6,   110,   240,   160,    16,     6,   270,   318,    34,    35,
      95,    37,   160,   116,   321,   142,   104,   289,   289,   160,
     147,   143,   240,   369,   138,    16,     6,   139,   160,   378,
     379,   385,   304,   305,   160,   160,   160,   149,   387,    16,
       6,    34,    35,   160,    37,     6,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   138,   277,   145,
     139,   241,   411,   150,    29,    16,     6,   160,    55,    56,
      57,    58,   424,   425,   146,   242,   240,   160,   160,   182,
     134,   135,   136,   426,   289,   186,   335,   249,   160,   114,
     115,   151,   252,   143,   336,   255,   337,   152,    16,     6,
     153,   241,    34,    35,   154,    37,   241,   155,   160,   156,
      41,    42,    43,    44,   140,   242,   141,   161,   206,   144,
     242,   290,   290,   262,   183,   264,   241,   249,   278,   271,
     268,   273,   249,   143,   274,   242,   242,   275,   143,   276,
     242,   132,   133,   134,   135,   136,   281,   249,   249,   280,
     286,   282,   249,   143,   143,   285,    59,   287,   143,    16,
       6,   140,   140,   141,   141,   288,   295,   319,   296,   297,
    -187,  -187,   298,  -187,   299,   105,   322,  -187,   112,   113,
     241,   240,   325,   240,   142,   330,  -187,   332,   290,  -187,
     143,   347,   341,   115,   242,   342,   348,   349,   350,   362,
     364,   368,   242,   370,   366,   372,   249,   384,   140,   386,
     141,   388,   143,   412,   249,   339,   374,   416,   399,   432,
     143,    22,   240,   398,   289,   240,   400,  -187,  -187,   414,
     417,   142,   142,   418,   420,   422,   159,   143,   143,   433,
     428,   437,   434,   435,   438,   240,   240,   439,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,    23,   181,    24,
     266,   429,     0,     0,   279,     0,     0,     0,   142,     0,
     250,     0,     0,   253,   143,   241,   256,   241,   257,     0,
     259,     0,     0,     0,     0,   272,     0,     0,   419,   242,
     421,   242,   423,     0,     0,     0,   243,   119,   120,     0,
       0,   249,     0,   249,     0,   294,   397,   143,   267,   143,
       0,     0,     0,     0,     0,     0,   241,     0,   290,   241,
       0,   284,   244,   132,   133,   134,   135,   136,     0,   245,
     242,     0,   242,   242,     0,     0,   243,     0,     0,   241,
     241,   243,   249,     0,   249,   249,     0,     0,   143,     0,
     143,   143,     0,   242,   242,     0,   243,   243,     0,   294,
       0,   243,   244,     0,     0,   249,   249,   244,     0,   245,
       0,   143,   143,     0,   245,     0,     0,   246,     0,     0,
     326,     0,   291,   292,     0,     0,     0,   244,     0,   245,
     245,   331,     0,   333,   245,     0,   340,  -188,  -188,   184,
    -188,     0,     0,     0,  -188,     0,   251,     0,   346,   254,
       0,     0,   247,  -188,     0,   243,  -188,   246,     0,     0,
       0,     0,   246,   243,     0,     0,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   246,   246,     0,
       0,   244,   246,     0,   367,     0,   248,     0,   245,   338,
       0,     0,   247,     0,  -188,  -188,   245,   247,     0,     0,
       0,     0,     0,     0,   391,     0,   393,   380,   381,   382,
     383,     0,   247,   247,     0,     0,     0,   247,     0,     0,
       0,     0,     0,     0,     0,     0,   248,     0,     0,     0,
       0,   248,   392,     0,   394,   396,   246,     0,     0,     0,
       0,     0,     0,     0,   246,   427,   248,   248,   430,     0,
       0,   248,     0,     0,  -195,  -195,     0,  -195,     0,   327,
     243,  -195,   243,     0,     0,     0,   144,     0,   440,   441,
    -195,   247,     0,  -195,  -207,     0,   431,     0,     0,   247,
       0,   344,   345,     0,     0,     0,   244,     0,   244,     0,
       0,  -189,  -189,   245,  -189,   245,     0,     0,  -189,     0,
       0,   243,     0,   243,   243,   248,     0,  -189,     0,     0,
    -189,  -195,  -195,   248,   363,     0,     0,   365,     0,     0,
       0,     0,     0,     0,   243,   243,     0,   244,     0,   338,
     244,     0,     0,     0,   245,     0,   245,   245,     0,     0,
       0,   246,     0,   246,     0,     0,     0,     0,  -189,  -189,
     244,   244,     0,     0,     0,     0,     0,   245,   245,     0,
     119,   120,     0,   390,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,   247,     0,   247,   408,
       0,   409,   246,   410,   246,   246,   132,   133,   134,   135,
     136,     0,  -190,  -190,     0,  -190,     0,     0,     0,  -190,
       0,     0,    33,     0,     0,   246,   246,     0,  -190,     0,
     248,  -190,   248,     0,     0,     0,     0,   247,     0,   247,
     247,     0,     0,     0,     0,     0,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,    43,    44,    45,     0,
     247,   247,   106,   107,     0,     0,    47,     0,     0,  -190,
    -190,   248,     0,   248,   248,     0,     0,     0,     0,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,   248,   248,     0,     0,     0,    50,
       0,     0,    51,    16,     6,    29,    52,    53,    54,    55,
      56,    57,    58,    34,    35,    36,    37,    38,    39,    40,
       0,    41,    42,    43,    44,    45,     0,     0,     0,    46,
       0,     0,     0,    47,     0,   283,    34,    35,     0,    37,
       0,  -191,  -191,   137,  -191,     0,     0,     0,  -191,    48,
      49,     0,   138,     0,     0,   139,    33,  -191,     0,     0,
    -191,     0,     0,     0,     0,     0,    50,     0,     0,    51,
      16,     6,    29,    52,    53,    54,    55,    56,    57,    58,
      34,    35,    36,    37,    38,    39,    40,     0,    41,    42,
      43,    44,    45,    16,     6,     0,    46,     0,  -191,  -191,
      47,     0,     0,  -192,  -192,     0,  -192,     0,  -193,  -193,
    -192,  -193,     0,     0,     0,  -193,    48,    49,     0,  -192,
       0,     0,  -192,    33,  -193,     0,     0,  -193,     0,     0,
       0,     0,     0,    50,     0,     0,    51,    16,     6,    29,
      52,    53,    54,    55,    56,    57,    58,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,    45,
    -192,  -192,     0,   106,     0,  -193,  -193,    47,   119,   120,
       0,   122,   123,   124,   125,   126,   127,   128,     0,     0,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,   129,   130,   131,   132,   133,   134,   135,   136,     0,
      50,     0,     0,    51,    16,     6,    29,    52,    53,    54,
      55,    56,    57,    58,   187,     0,     0,     0,     0,     0,
       0,     0,   188,     0,     0,   189,   190,   191,     0,   192,
     193,   194,   195,     0,   196,   197,   198,   199,   200,   201,
     202,   203,   204,    34,    35,     0,    37,     0,     0,     0,
       0,    41,    42,    43,    44,     0,     0,   147,   205,   206,
       0,     0,     0,     0,     0,   187,   265,   207,   208,     0,
       0,     0,     0,   188,     0,     0,   189,   190,   191,     0,
     192,   193,   194,   195,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,    34,    35,     0,    37,     0,     0,
      16,     6,    41,    42,    43,    44,  -194,  -194,   147,  -194,
     206,     0,     0,  -194,     0,     0,   187,     0,   207,   208,
       0,     0,  -194,     0,   188,  -194,     0,   189,   190,   191,
       0,   192,   193,   194,   195,     0,   196,   197,   198,   199,
     200,   201,   202,   203,   204,    34,    35,     0,    37,     0,
       0,    16,     6,    41,    42,    43,    44,     0,     0,   147,
     293,   206,     0,  -194,  -194,     0,     0,   187,   328,   207,
     208,     0,     0,     0,     0,   188,     0,     0,   189,   190,
     191,     0,   192,   193,   194,   195,     0,   196,   197,   198,
     199,   200,   201,   202,   203,   204,    34,    35,     0,    37,
       0,     0,    16,     6,    41,    42,    43,    44,     0,     0,
     147,     0,   206,     0,     0,     0,     0,     0,   187,     0,
     207,   208,     0,     0,     0,     0,   188,     0,     0,   189,
     190,   191,     0,   192,   193,   194,   195,     0,   196,   197,
     198,   199,   200,   201,   202,   203,   204,    34,    35,     0,
      37,     0,     0,    16,     6,    41,    42,    43,    44,     0,
       0,   147,     0,   206,     0,     0,     0,     0,     0,     0,
       0,   207,   208,    34,    35,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
       0,     0,   139,     0,     0,     0,     0,   304,   305,     0,
       0,     0,     0,     0,    16,     6,     0,     0,     0,     0,
       0,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   157,     0,     0,     0,     0,   158,     0,     0,
      16,     6,   118,     0,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   130,
     131,   132,   133,   134,   135,   136,   402,     0,     0,     0,
       0,   403,     0,     0,     0,     0,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     404,     0,     0,     0,     0,   405,     0,     0,     0,     0,
     118,     0,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   129,   130,   131,   132,
     133,   134,   135,   136,   406,     0,     0,     0,     0,   407,
       0,     0,     0,     0,   118,     0,     0,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   371,     0,
     129,   130,   131,   132,   133,   134,   135,   136,   118,     0,
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   373,     0,   129,   130,   131,   132,   133,   134,
     135,   136,   118,     0,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   377,     0,   129,   130,
     131,   132,   133,   134,   135,   136,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     389,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     118,     0,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   401,     0,   129,   130,   131,   132,
     133,   134,   135,   136,   118,     0,     0,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   413,     0,
     129,   130,   131,   132,   133,   134,   135,   136,   118,     0,
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   415,     0,   129,   130,   131,   132,   133,   134,
     135,   136,   118,     0,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   436,     0,   129,   130,
     131,   132,   133,   134,   135,   136,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     258,     0,     0,     0,     0,     0,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     261,     0,     0,     0,     0,     0,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     317,     0,     0,     0,     0,     0,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     320,     0,     0,     0,     0,     0,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     323,     0,     0,     0,     0,     0,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     324,     0,     0,     0,     0,   118,     0,     0,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   129,   130,   131,   132,   133,   134,   135,   136,   260,
       0,   118,     0,     0,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   117,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     329,   118,     0,     0,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   343,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   118,
       0,     0,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
       0,     0,     0,     0,     0,   129,   130,   131,   132,   133,
     134,   135,   136,   119,   120,     0,     0,   123,   124,   125,
     126,   127,   128,   119,   120,     0,     0,   123,   124,   125,
     126,   127,   128,     0,     0,     0,   129,   130,   131,   132,
     133,   134,   135,   136,     0,     0,     0,   130,   131,   132,
     133,   134,   135,   136,   119,   120,     0,     0,   123,   124,
     125,   126,   127,   128,   119,   120,     0,     0,     0,     0,
     125,   126,   127,   128,     0,     0,     0,     0,   130,     0,
     132,   133,   134,   135,   136,     0,     0,     0,     0,     0,
     132,   133,   134,   135,   136
  };

  const short
  parser::yycheck_[] =
  {
       0,    46,    96,     3,     4,    75,   274,    75,     8,     3,
       4,    20,    44,    48,   274,    22,   274,   147,     3,     4,
       5,     6,     7,    48,    44,    25,     0,    45,    32,    33,
      54,    35,    50,    54,    34,    35,    40,    41,    42,    43,
      34,    35,    91,    50,    48,     9,    10,    47,    12,    13,
      70,    44,    56,    57,    89,    90,    44,   187,    45,    52,
      90,   106,   192,    50,    89,    90,    54,    45,    32,    33,
      45,    35,    50,    90,    45,    75,    48,   207,   208,    50,
      46,    75,   212,    45,    48,    89,    90,    51,    50,    45,
      45,    45,    56,    57,    50,    50,    50,    97,    45,    89,
      90,    32,    33,    50,    35,    90,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    48,    85,    52,
      51,   147,    45,    48,    91,    89,    90,    50,    95,    96,
      97,    98,    45,    45,    54,   147,   266,    50,    50,   139,
      86,    87,    88,    45,   274,   145,   414,   147,    50,    94,
      95,    44,   152,   147,   414,   155,   414,    52,    89,    90,
      48,   187,    32,    33,    44,    35,   192,    52,    50,    48,
      40,    41,    42,    43,   244,   187,   244,    49,    48,    44,
     192,   207,   208,   183,    52,    44,   212,   187,   197,    44,
      54,    44,   192,   187,    44,   207,   208,    44,   192,    44,
     212,    84,    85,    86,    87,    88,    54,   207,   208,    53,
      44,    54,   212,   207,   208,    54,    26,    44,   212,    89,
      90,   291,   292,   291,   292,    48,    54,    44,    54,    54,
      32,    33,    54,    35,    54,    45,    44,    39,    48,    49,
     266,   371,    49,   373,   244,    45,    48,    19,   274,    51,
     244,    44,    53,    95,   266,    53,    44,    44,    44,    49,
      49,    44,   274,    54,    49,    44,   266,    44,   338,    44,
     338,    44,   266,    17,   274,   275,    54,    22,    54,    45,
     274,     8,   412,   377,   414,   415,    54,    89,    90,    54,
      54,   291,   292,    54,    54,    54,   106,   291,   292,    45,
      54,    54,    45,    45,    54,   435,   436,    54,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     8,   138,     8,
     187,   414,    -1,    -1,   197,    -1,    -1,    -1,   338,    -1,
     150,    -1,    -1,   153,   338,   371,   156,   373,   158,    -1,
     160,    -1,    -1,    -1,    -1,   192,    -1,    -1,   403,   371,
     405,   373,   407,    -1,    -1,    -1,   147,    58,    59,    -1,
      -1,   371,    -1,   373,    -1,   212,   376,   371,   188,   373,
      -1,    -1,    -1,    -1,    -1,    -1,   412,    -1,   414,   415,
      -1,   201,   147,    84,    85,    86,    87,    88,    -1,   147,
     412,    -1,   414,   415,    -1,    -1,   187,    -1,    -1,   435,
     436,   192,   412,    -1,   414,   415,    -1,    -1,   412,    -1,
     414,   415,    -1,   435,   436,    -1,   207,   208,    -1,   266,
      -1,   212,   187,    -1,    -1,   435,   436,   192,    -1,   187,
      -1,   435,   436,    -1,   192,    -1,    -1,   147,    -1,    -1,
     260,    -1,   207,   208,    -1,    -1,    -1,   212,    -1,   207,
     208,   271,    -1,   273,   212,    -1,   276,    32,    33,   144,
      35,    -1,    -1,    -1,    39,    -1,   151,    -1,   288,   154,
      -1,    -1,   147,    48,    -1,   266,    51,   187,    -1,    -1,
      -1,    -1,   192,   274,    -1,    -1,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   207,   208,    -1,
      -1,   266,   212,    -1,   324,    -1,   147,    -1,   266,   274,
      -1,    -1,   187,    -1,    89,    90,   274,   192,    -1,    -1,
      -1,    -1,    -1,    -1,   371,    -1,   373,   347,   348,   349,
     350,    -1,   207,   208,    -1,    -1,    -1,   212,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   187,    -1,    -1,    -1,
      -1,   192,   372,    -1,   374,   375,   266,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   274,   412,   207,   208,   415,    -1,
      -1,   212,    -1,    -1,    32,    33,    -1,    35,    -1,   264,
     371,    39,   373,    -1,    -1,    -1,    44,    -1,   435,   436,
      48,   266,    -1,    51,    52,    -1,   416,    -1,    -1,   274,
      -1,   286,   287,    -1,    -1,    -1,   371,    -1,   373,    -1,
      -1,    32,    33,   371,    35,   373,    -1,    -1,    39,    -1,
      -1,   412,    -1,   414,   415,   266,    -1,    48,    -1,    -1,
      51,    89,    90,   274,   319,    -1,    -1,   322,    -1,    -1,
      -1,    -1,    -1,    -1,   435,   436,    -1,   412,    -1,   414,
     415,    -1,    -1,    -1,   412,    -1,   414,   415,    -1,    -1,
      -1,   371,    -1,   373,    -1,    -1,    -1,    -1,    89,    90,
     435,   436,    -1,    -1,    -1,    -1,    -1,   435,   436,    -1,
      58,    59,    -1,   368,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,   371,    -1,   373,   384,
      -1,   386,   412,   388,   414,   415,    84,    85,    86,    87,
      88,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,    39,
      -1,    -1,     8,    -1,    -1,   435,   436,    -1,    48,    -1,
     371,    51,   373,    -1,    -1,    -1,    -1,   412,    -1,   414,
     415,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    -1,    40,    41,    42,    43,    44,    -1,
     435,   436,    48,    49,    -1,    -1,    52,    -1,    -1,    89,
      90,   412,    -1,   414,   415,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,   435,   436,    -1,    -1,    -1,    85,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    32,    33,    34,    35,    36,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    52,    -1,    54,    32,    33,    -1,    35,
      -1,    32,    33,    39,    35,    -1,    -1,    -1,    39,    68,
      69,    -1,    48,    -1,    -1,    51,     8,    48,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      32,    33,    34,    35,    36,    37,    38,    -1,    40,    41,
      42,    43,    44,    89,    90,    -1,    48,    -1,    89,    90,
      52,    -1,    -1,    32,    33,    -1,    35,    -1,    32,    33,
      39,    35,    -1,    -1,    -1,    39,    68,    69,    -1,    48,
      -1,    -1,    51,     8,    48,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    85,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    32,    33,    34,
      35,    36,    37,    38,    -1,    40,    41,    42,    43,    44,
      89,    90,    -1,    48,    -1,    89,    90,    52,    58,    59,
      -1,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      85,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    14,    15,    16,    -1,    18,
      19,    20,    21,    -1,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    -1,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    -1,    -1,    46,    47,    48,
      -1,    -1,    -1,    -1,    -1,     3,     4,    56,    57,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    14,    15,    16,    -1,
      18,    19,    20,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    -1,    35,    -1,    -1,
      89,    90,    40,    41,    42,    43,    32,    33,    46,    35,
      48,    -1,    -1,    39,    -1,    -1,     3,    -1,    56,    57,
      -1,    -1,    48,    -1,    11,    51,    -1,    14,    15,    16,
      -1,    18,    19,    20,    21,    -1,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    -1,    35,    -1,
      -1,    89,    90,    40,    41,    42,    43,    -1,    -1,    46,
      47,    48,    -1,    89,    90,    -1,    -1,     3,     4,    56,
      57,    -1,    -1,    -1,    -1,    11,    -1,    -1,    14,    15,
      16,    -1,    18,    19,    20,    21,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    -1,    89,    90,    40,    41,    42,    43,    -1,    -1,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      56,    57,    -1,    -1,    -1,    -1,    11,    -1,    -1,    14,
      15,    16,    -1,    18,    19,    20,    21,    -1,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    -1,
      35,    -1,    -1,    89,    90,    40,    41,    42,    43,    -1,
      -1,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    32,    33,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,    -1,
      -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      89,    90,    55,    -1,    -1,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    45,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      45,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      55,    -1,    -1,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    45,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    55,    -1,
      -1,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    55,    -1,    -1,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      55,    -1,    -1,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    55,    -1,    -1,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    55,    -1,
      -1,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    55,    -1,    -1,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      50,    -1,    -1,    -1,    -1,    55,    -1,    -1,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    53,
      -1,    55,    -1,    -1,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    54,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      54,    55,    -1,    -1,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    54,    55,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    55,
      -1,    -1,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    81,    82,    83,    84,    85,    86,    87,    88,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    58,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    58,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    -1,    -1,    82,    83,    84,
      85,    86,    87,    88,    58,    59,    -1,    -1,    62,    63,
      64,    65,    66,    67,    58,    59,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    82,    -1,
      84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    88
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,    90,   109,   110,   111,
     112,   113,   114,   115,   116,   179,    89,   179,   180,   180,
      44,     0,   111,   112,   113,    44,    70,    54,    54,    91,
     182,   161,   179,     8,    32,    33,    34,    35,    36,    37,
      38,    40,    41,    42,    43,    44,    48,    52,    68,    69,
      85,    88,    92,    93,    94,    95,    96,    97,    98,   146,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,    45,    45,    50,    48,   179,
     180,    48,   179,   180,    48,   146,    48,    49,   146,   162,
     163,   179,   146,   146,    94,    95,    90,    54,    55,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    81,
      82,    83,    84,    85,    86,    87,    88,    39,    48,    51,
     158,   159,   179,   180,    44,    52,    54,    46,   119,   179,
      48,    44,    52,    48,    44,    52,    48,    45,    50,   146,
      50,    49,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   179,    52,   162,   163,   179,     3,    11,    14,
      15,    16,    18,    19,    20,    21,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    47,    48,    56,    57,   117,
     118,   119,   120,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   148,   149,   150,
     156,   157,   165,   166,   169,   173,   174,   175,   176,   179,
     146,   162,   179,   146,   162,   179,   146,   146,    49,   146,
      53,    49,   179,    45,    44,     4,   120,   146,    54,    44,
      54,    44,   117,    44,    44,    44,    44,    85,   182,   186,
      53,    54,    54,    54,   146,    54,    44,    44,    48,   156,
     157,   169,   169,    47,   117,    54,    54,    54,    54,    54,
       9,    10,    12,    13,    56,    57,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    49,    45,    44,
      49,    45,    44,    49,    50,    49,   146,   162,     4,    54,
      45,   146,    19,   146,   121,   148,   149,   150,   169,   179,
     146,    53,    53,    54,   162,   162,   146,    44,    44,    44,
      44,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,    49,   162,    49,   162,    49,   146,    44,    45,
      54,    45,    44,    45,    54,    22,    50,    45,    45,    45,
     146,   146,   146,   146,    44,    45,    44,    45,    44,    45,
     162,   117,   146,   117,   146,   147,   146,   179,   119,    54,
      54,    45,    45,    50,    45,    50,    45,    50,   162,   162,
     162,    45,    17,    45,    54,    45,    22,    54,    54,   163,
      54,   163,    54,   163,    45,    45,    45,   117,    54,   121,
     117,   146,    45,    45,    45,    45,    45,    54,    54,    54,
     117,   117
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   108,   109,   109,   110,   110,   110,   110,   110,   110,
     111,   112,   113,   113,   113,   113,   113,   114,   115,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   118,   118,   119,   119,
     120,   120,   121,   121,   121,   121,   122,   122,   123,   123,
     123,   124,   125,   125,   126,   127,   127,   128,   128,   129,
     130,   130,   131,   132,   133,   134,   135,   136,   136,   137,
     138,   138,   139,   140,   141,   142,   142,   143,   144,   145,
     146,   146,   146,   147,   147,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   149,   149,   150,   150,
     151,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   154,   155,   156,
     156,   157,   157,   158,   158,   158,   158,   158,   158,   159,
     159,   159,   159,   160,   161,   161,   161,   162,   162,   163,
     163,   164,   164,   165,   166,   167,   168,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   180,   181,   182,
     183,   184,   185,   185,   186,   186,   186,   186,   186,   187,
     188
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     5,     4,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     3,     2,
       2,     1,     1,     1,     1,     0,     2,     2,     2,     2,
       2,     6,     8,     6,     3,     8,     6,     8,     6,     2,
       2,     4,     5,     7,     5,     7,     9,     7,     9,     5,
       3,     3,     2,     2,     2,     3,     2,     2,     5,     5,
       1,     1,     1,     1,     0,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       5,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     2,     2,     4,     6,     5,     7,     5,     7,     8,
       9,     9,     9,     3,     3,     1,     0,     1,     0,     3,
       1,     2,     3,     4,     3,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     7,     2,     1,     2,     1,     1,     1,     1,     1,
       1
  };




#if S2DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   254,   254,   255,   259,   261,   263,   265,   267,   269,
     274,   278,   283,   284,   285,   286,   287,   291,   296,   301,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   335,   336,   340,   341,
     345,   347,   352,   354,   356,   359,   363,   365,   370,   372,
     374,   379,   384,   386,   391,   396,   398,   403,   405,   410,
     415,   417,   422,   427,   432,   437,   442,   447,   449,   454,
     459,   461,   466,   471,   476,   481,   483,   488,   493,   498,
     503,   504,   505,   509,   510,   514,   516,   518,   520,   522,
     524,   526,   528,   530,   532,   534,   539,   541,   546,   548,
     553,   558,   560,   562,   564,   566,   568,   570,   572,   574,
     576,   578,   580,   582,   584,   586,   588,   590,   592,   597,
     598,   599,   600,   601,   602,   603,   604,   605,   606,   607,
     608,   609,   610,   611,   612,   613,   614,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   624,   628,   633,   638,
     639,   642,   643,   647,   649,   651,   653,   655,   657,   662,
     664,   666,   668,   673,   678,   680,   683,   687,   690,   694,
     696,   701,   703,   708,   713,   718,   723,   728,   729,   730,
     731,   732,   733,   734,   735,   736,   740,   745,   750,   755,
     760,   765,   770,   775,   780,   785,   790,   792,   797,   802,
     807,   812,   817,   819,   824,   826,   828,   830,   832,   837,
     842
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
#endif // S2DEBUG


#line 13 "parser.ypp"
} } } // xsk::gsc::s2
#line 4556 "parser.cpp"

#line 846 "parser.ypp"


void xsk::gsc::s2::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
