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
xsk::gsc::iw7::parser::symbol_type IW7lex(yyscan_t yyscanner, xsk::gsc::context* ctx);

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
  parser::parser (yyscan_t yyscanner_yyarg, xsk::gsc::context* ctx_yyarg, xsk::gsc::ast::program::ptr& ast_yyarg)
#if IW7DEBUG
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
#line 252 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < ast::program::ptr > ()); }
#line 1981 "parser.cpp"
    break;

  case 3: // root: %empty
#line 253 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 1987 "parser.cpp"
    break;

  case 4: // program: program inline
#line 258 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 1993 "parser.cpp"
    break;

  case 5: // program: program include
#line 260 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 1999 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 262 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2005 "parser.cpp"
    break;

  case 7: // program: inline
#line 264 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 2011 "parser.cpp"
    break;

  case 8: // program: include
#line 266 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2017 "parser.cpp"
    break;

  case 9: // program: declaration
#line 268 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2023 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 272 "parser.ypp"
                                 { iw7_push_header(ctx, yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2029 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 277 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2035 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 281 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2041 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 282 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2047 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 283 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2053 "parser.cpp"
    break;

  case 15: // declaration: decl_constant
#line 284 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_constant = std::move(yystack_[0].value.as < ast::decl_constant::ptr > ()); }
#line 2059 "parser.cpp"
    break;

  case 16: // declaration: decl_thread
#line 285 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2065 "parser.cpp"
    break;

  case 17: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 290 "parser.ypp"
        { ctx->restrict_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2071 "parser.cpp"
    break;

  case 18: // decl_constant: expr_identifier "=" expr ";"
#line 295 "parser.ypp"
        { yylhs.value.as < ast::decl_constant::ptr > () = std::make_unique<ast::decl_constant>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2077 "parser.cpp"
    break;

  case 19: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 300 "parser.ypp"
        { ctx->restrict_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2083 "parser.cpp"
    break;

  case 20: // stmt: stmt_dev
#line 304 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2089 "parser.cpp"
    break;

  case 21: // stmt: stmt_block
#line 305 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2095 "parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 306 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2101 "parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 307 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2107 "parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 308 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2113 "parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 309 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2119 "parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 310 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2125 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 311 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2131 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 312 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2137 "parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 313 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2143 "parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 314 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2149 "parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 315 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2155 "parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 316 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2161 "parser.cpp"
    break;

  case 33: // stmt: stmt_dowhile
#line 317 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2167 "parser.cpp"
    break;

  case 34: // stmt: stmt_for
#line 318 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2173 "parser.cpp"
    break;

  case 35: // stmt: stmt_foreach
#line 319 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2179 "parser.cpp"
    break;

  case 36: // stmt: stmt_switch
#line 320 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2185 "parser.cpp"
    break;

  case 37: // stmt: stmt_case
#line 321 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2191 "parser.cpp"
    break;

  case 38: // stmt: stmt_default
#line 322 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2197 "parser.cpp"
    break;

  case 39: // stmt: stmt_break
#line 323 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2203 "parser.cpp"
    break;

  case 40: // stmt: stmt_continue
#line 324 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2209 "parser.cpp"
    break;

  case 41: // stmt: stmt_return
#line 325 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2215 "parser.cpp"
    break;

  case 42: // stmt: stmt_breakpoint
#line 326 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_breakpoint = std::move(yystack_[0].value.as < ast::stmt_breakpoint::ptr > ()); }
#line 2221 "parser.cpp"
    break;

  case 43: // stmt: stmt_prof_begin
#line 327 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2227 "parser.cpp"
    break;

  case 44: // stmt: stmt_prof_end
#line 328 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2233 "parser.cpp"
    break;

  case 45: // stmt_dev: "/#" stmt_list "#/"
#line 332 "parser.ypp"
                                { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2239 "parser.cpp"
    break;

  case 46: // stmt_dev: "/#" "#/"
#line 333 "parser.ypp"
                      { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2245 "parser.cpp"
    break;

  case 47: // stmt_block: "{" stmt_list "}"
#line 337 "parser.ypp"
                              { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2251 "parser.cpp"
    break;

  case 48: // stmt_block: "{" "}"
#line 338 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2257 "parser.cpp"
    break;

  case 49: // stmt_list: stmt_list stmt
#line 343 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2263 "parser.cpp"
    break;

  case 50: // stmt_list: stmt
#line 345 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2269 "parser.cpp"
    break;

  case 51: // stmt_expr: expr_assign
#line 350 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2275 "parser.cpp"
    break;

  case 52: // stmt_expr: expr_increment
#line 352 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2281 "parser.cpp"
    break;

  case 53: // stmt_expr: expr_decrement
#line 354 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2287 "parser.cpp"
    break;

  case 54: // stmt_expr: %empty
#line 356 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2293 "parser.cpp"
    break;

  case 55: // stmt_call: expr_call ";"
#line 361 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2299 "parser.cpp"
    break;

  case 56: // stmt_call: expr_method ";"
#line 363 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2305 "parser.cpp"
    break;

  case 57: // stmt_assign: expr_assign ";"
#line 368 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2311 "parser.cpp"
    break;

  case 58: // stmt_assign: expr_increment ";"
#line 370 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2317 "parser.cpp"
    break;

  case 59: // stmt_assign: expr_decrement ";"
#line 372 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2323 "parser.cpp"
    break;

  case 60: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 377 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2329 "parser.cpp"
    break;

  case 61: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 382 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2335 "parser.cpp"
    break;

  case 62: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 384 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2341 "parser.cpp"
    break;

  case 63: // stmt_wait: "wait" expr ";"
#line 389 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2347 "parser.cpp"
    break;

  case 64: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 394 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2353 "parser.cpp"
    break;

  case 65: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 396 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2359 "parser.cpp"
    break;

  case 66: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 401 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2365 "parser.cpp"
    break;

  case 67: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 403 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2371 "parser.cpp"
    break;

  case 68: // stmt_waittillframeend: "waittillframeend" ";"
#line 408 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2377 "parser.cpp"
    break;

  case 69: // stmt_if: "if" "(" expr ")" stmt
#line 413 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2383 "parser.cpp"
    break;

  case 70: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 418 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2389 "parser.cpp"
    break;

  case 71: // stmt_while: "while" "(" expr ")" stmt
#line 423 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2395 "parser.cpp"
    break;

  case 72: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 428 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2401 "parser.cpp"
    break;

  case 73: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 433 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2407 "parser.cpp"
    break;

  case 74: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 438 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2413 "parser.cpp"
    break;

  case 75: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 440 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2419 "parser.cpp"
    break;

  case 76: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 445 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2425 "parser.cpp"
    break;

  case 77: // stmt_case: "case" expr_integer ":"
#line 450 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2431 "parser.cpp"
    break;

  case 78: // stmt_case: "case" expr_string ":"
#line 452 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2437 "parser.cpp"
    break;

  case 79: // stmt_default: "default" ":"
#line 457 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2443 "parser.cpp"
    break;

  case 80: // stmt_break: "break" ";"
#line 462 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2449 "parser.cpp"
    break;

  case 81: // stmt_continue: "continue" ";"
#line 467 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2455 "parser.cpp"
    break;

  case 82: // stmt_return: "return" expr ";"
#line 472 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2461 "parser.cpp"
    break;

  case 83: // stmt_return: "return" ";"
#line 474 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2467 "parser.cpp"
    break;

  case 84: // stmt_breakpoint: "breakpoint" ";"
#line 479 "parser.ypp"
        { yylhs.value.as < ast::stmt_breakpoint::ptr > () = std::make_unique<ast::stmt_breakpoint>(yylhs.location); }
#line 2473 "parser.cpp"
    break;

  case 85: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 484 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2479 "parser.cpp"
    break;

  case 86: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 489 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2485 "parser.cpp"
    break;

  case 87: // expr: expr_ternary
#line 493 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2491 "parser.cpp"
    break;

  case 88: // expr: expr_binary
#line 494 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2497 "parser.cpp"
    break;

  case 89: // expr: expr_primitive
#line 495 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2503 "parser.cpp"
    break;

  case 90: // expr_or_empty: expr
#line 499 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2509 "parser.cpp"
    break;

  case 91: // expr_or_empty: %empty
#line 500 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2515 "parser.cpp"
    break;

  case 92: // expr_assign: expr_object "=" expr
#line 505 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2521 "parser.cpp"
    break;

  case 93: // expr_assign: expr_object "|=" expr
#line 507 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2527 "parser.cpp"
    break;

  case 94: // expr_assign: expr_object "&=" expr
#line 509 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2533 "parser.cpp"
    break;

  case 95: // expr_assign: expr_object "^=" expr
#line 511 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2539 "parser.cpp"
    break;

  case 96: // expr_assign: expr_object "<<=" expr
#line 513 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2545 "parser.cpp"
    break;

  case 97: // expr_assign: expr_object ">>=" expr
#line 515 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2551 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object "+=" expr
#line 517 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2557 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "-=" expr
#line 519 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2563 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object "*=" expr
#line 521 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2569 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "/=" expr
#line 523 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2575 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "%=" expr
#line 525 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2581 "parser.cpp"
    break;

  case 103: // expr_increment: "++" expr_object
#line 530 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2587 "parser.cpp"
    break;

  case 104: // expr_increment: expr_object "++"
#line 532 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2593 "parser.cpp"
    break;

  case 105: // expr_decrement: "--" expr_object
#line 537 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2599 "parser.cpp"
    break;

  case 106: // expr_decrement: expr_object "--"
#line 539 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2605 "parser.cpp"
    break;

  case 107: // expr_ternary: expr "?" expr ":" expr
#line 544 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2611 "parser.cpp"
    break;

  case 108: // expr_binary: expr "||" expr
#line 549 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2617 "parser.cpp"
    break;

  case 109: // expr_binary: expr "&&" expr
#line 551 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2623 "parser.cpp"
    break;

  case 110: // expr_binary: expr "==" expr
#line 553 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2629 "parser.cpp"
    break;

  case 111: // expr_binary: expr "!=" expr
#line 555 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2635 "parser.cpp"
    break;

  case 112: // expr_binary: expr "<=" expr
#line 557 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2641 "parser.cpp"
    break;

  case 113: // expr_binary: expr ">=" expr
#line 559 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2647 "parser.cpp"
    break;

  case 114: // expr_binary: expr "<" expr
#line 561 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2653 "parser.cpp"
    break;

  case 115: // expr_binary: expr ">" expr
#line 563 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2659 "parser.cpp"
    break;

  case 116: // expr_binary: expr "|" expr
#line 565 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2665 "parser.cpp"
    break;

  case 117: // expr_binary: expr "&" expr
#line 567 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2671 "parser.cpp"
    break;

  case 118: // expr_binary: expr "^" expr
#line 569 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2677 "parser.cpp"
    break;

  case 119: // expr_binary: expr "<<" expr
#line 571 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2683 "parser.cpp"
    break;

  case 120: // expr_binary: expr ">>" expr
#line 573 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2689 "parser.cpp"
    break;

  case 121: // expr_binary: expr "+" expr
#line 575 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2695 "parser.cpp"
    break;

  case 122: // expr_binary: expr "-" expr
#line 577 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2701 "parser.cpp"
    break;

  case 123: // expr_binary: expr "*" expr
#line 579 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2707 "parser.cpp"
    break;

  case 124: // expr_binary: expr "/" expr
#line 581 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2713 "parser.cpp"
    break;

  case 125: // expr_binary: expr "%" expr
#line 583 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2719 "parser.cpp"
    break;

  case 126: // expr_primitive: expr_complement
#line 587 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 2725 "parser.cpp"
    break;

  case 127: // expr_primitive: expr_not
#line 588 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 2731 "parser.cpp"
    break;

  case 128: // expr_primitive: expr_call
#line 589 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 2737 "parser.cpp"
    break;

  case 129: // expr_primitive: expr_method
#line 590 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 2743 "parser.cpp"
    break;

  case 130: // expr_primitive: expr_add_array
#line 591 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_add_array::ptr > ()); }
#line 2749 "parser.cpp"
    break;

  case 131: // expr_primitive: expr_reference
#line 592 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 2755 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_array
#line 593 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 2761 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_field
#line 594 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 2767 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_size
#line 595 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 2773 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_paren
#line 596 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 2779 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_thisthread
#line 597 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_thisthread::ptr > ()); }
#line 2785 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_empty_array
#line 598 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 2791 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_undefined
#line 599 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 2797 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_game
#line 600 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 2803 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_self
#line 601 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 2809 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_anim
#line 602 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 2815 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_level
#line 603 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 2821 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_animation
#line 604 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 2827 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_animtree
#line 605 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animtree::ptr > ()); }
#line 2833 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_identifier
#line 606 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 2839 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_istring
#line 607 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 2845 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_string
#line 608 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 2851 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_color
#line 609 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_color::ptr > ()); }
#line 2857 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_vector
#line 610 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 2863 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_float
#line 611 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 2869 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_integer
#line 612 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 2875 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_false
#line 613 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 2881 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_true
#line 614 "parser.ypp"
                            { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 2887 "parser.cpp"
    break;

  case 154: // expr_complement: "~" expr
#line 619 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2893 "parser.cpp"
    break;

  case 155: // expr_not: "!" expr
#line 624 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2899 "parser.cpp"
    break;

  case 156: // expr_call: expr_function
#line 628 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2905 "parser.cpp"
    break;

  case 157: // expr_call: expr_pointer
#line 629 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 2911 "parser.cpp"
    break;

  case 158: // expr_method: expr_object expr_function
#line 632 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 2917 "parser.cpp"
    break;

  case 159: // expr_method: expr_object expr_pointer
#line 633 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 2923 "parser.cpp"
    break;

  case 160: // expr_function: expr_identifier "(" expr_arguments ")"
#line 638 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 2929 "parser.cpp"
    break;

  case 161: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 640 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 2935 "parser.cpp"
    break;

  case 162: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 642 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 2941 "parser.cpp"
    break;

  case 163: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 644 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 2947 "parser.cpp"
    break;

  case 164: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 646 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 2953 "parser.cpp"
    break;

  case 165: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 648 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 2959 "parser.cpp"
    break;

  case 166: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 653 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 2965 "parser.cpp"
    break;

  case 167: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 655 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 2971 "parser.cpp"
    break;

  case 168: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 657 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::childthread); }
#line 2977 "parser.cpp"
    break;

  case 169: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 659 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::builtin); }
#line 2983 "parser.cpp"
    break;

  case 170: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 664 "parser.ypp"
        { yylhs.value.as < ast::expr_add_array::ptr > () = std::make_unique<ast::expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ())); }
#line 2989 "parser.cpp"
    break;

  case 171: // expr_parameters: expr_parameters "," expr_identifier
#line 669 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 2995 "parser.cpp"
    break;

  case 172: // expr_parameters: expr_identifier
#line 671 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3001 "parser.cpp"
    break;

  case 173: // expr_parameters: %empty
#line 673 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 3007 "parser.cpp"
    break;

  case 174: // expr_arguments: expr_arguments_no_empty
#line 678 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 3013 "parser.cpp"
    break;

  case 175: // expr_arguments: %empty
#line 680 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3019 "parser.cpp"
    break;

  case 176: // expr_arguments_no_empty: expr_arguments "," expr
#line 685 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3025 "parser.cpp"
    break;

  case 177: // expr_arguments_no_empty: expr
#line 687 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3031 "parser.cpp"
    break;

  case 178: // expr_reference: "::" expr_identifier
#line 692 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3037 "parser.cpp"
    break;

  case 179: // expr_reference: expr_path "::" expr_identifier
#line 694 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3043 "parser.cpp"
    break;

  case 180: // expr_array: expr_object "[" expr "]"
#line 699 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3049 "parser.cpp"
    break;

  case 181: // expr_field: expr_object "." expr_identifier
#line 704 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3055 "parser.cpp"
    break;

  case 182: // expr_size: expr_object ".size"
#line 709 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3061 "parser.cpp"
    break;

  case 183: // expr_paren: "(" expr ")"
#line 714 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3067 "parser.cpp"
    break;

  case 184: // expr_object: expr_call
#line 718 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3073 "parser.cpp"
    break;

  case 185: // expr_object: expr_method
#line 719 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3079 "parser.cpp"
    break;

  case 186: // expr_object: expr_array
#line 720 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3085 "parser.cpp"
    break;

  case 187: // expr_object: expr_field
#line 721 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3091 "parser.cpp"
    break;

  case 188: // expr_object: expr_game
#line 722 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3097 "parser.cpp"
    break;

  case 189: // expr_object: expr_self
#line 723 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3103 "parser.cpp"
    break;

  case 190: // expr_object: expr_anim
#line 724 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3109 "parser.cpp"
    break;

  case 191: // expr_object: expr_level
#line 725 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3115 "parser.cpp"
    break;

  case 192: // expr_object: expr_identifier
#line 726 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3121 "parser.cpp"
    break;

  case 193: // expr_thisthread: "thisthread"
#line 731 "parser.ypp"
        { yylhs.value.as < ast::expr_thisthread::ptr > () = std::make_unique<ast::expr_thisthread>(yylhs.location); }
#line 3127 "parser.cpp"
    break;

  case 194: // expr_empty_array: "[" "]"
#line 736 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3133 "parser.cpp"
    break;

  case 195: // expr_undefined: "undefined"
#line 741 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3139 "parser.cpp"
    break;

  case 196: // expr_game: "game"
#line 746 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3145 "parser.cpp"
    break;

  case 197: // expr_self: "self"
#line 751 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3151 "parser.cpp"
    break;

  case 198: // expr_anim: "anim"
#line 756 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3157 "parser.cpp"
    break;

  case 199: // expr_level: "level"
#line 761 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3163 "parser.cpp"
    break;

  case 200: // expr_animation: "%" "identifier"
#line 766 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3169 "parser.cpp"
    break;

  case 201: // expr_animtree: "#animtree"
#line 771 "parser.ypp"
        { yylhs.value.as < ast::expr_animtree::ptr > () = std::make_unique<ast::expr_animtree>(yylhs.location); }
#line 3175 "parser.cpp"
    break;

  case 202: // expr_identifier: "identifier"
#line 776 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3181 "parser.cpp"
    break;

  case 203: // expr_path: "path"
#line 781 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3187 "parser.cpp"
    break;

  case 204: // expr_path: expr_identifier
#line 783 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < ast::expr_identifier::ptr > ()->value); }
#line 3193 "parser.cpp"
    break;

  case 205: // expr_istring: "localized string"
#line 788 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3199 "parser.cpp"
    break;

  case 206: // expr_string: "string literal"
#line 793 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3205 "parser.cpp"
    break;

  case 207: // expr_color: "color"
#line 798 "parser.ypp"
        { yylhs.value.as < ast::expr_color::ptr > () = std::make_unique<ast::expr_color>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3211 "parser.cpp"
    break;

  case 208: // expr_vector: "(" expr "," expr "," expr ")"
#line 803 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3217 "parser.cpp"
    break;

  case 209: // expr_float: "-" "float"
#line 808 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3223 "parser.cpp"
    break;

  case 210: // expr_float: "float"
#line 810 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3229 "parser.cpp"
    break;

  case 211: // expr_integer: "-" "int"
#line 815 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3235 "parser.cpp"
    break;

  case 212: // expr_integer: "int"
#line 817 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3241 "parser.cpp"
    break;

  case 213: // expr_integer: "octal int"
#line 819 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3247 "parser.cpp"
    break;

  case 214: // expr_integer: "binary int"
#line 821 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3253 "parser.cpp"
    break;

  case 215: // expr_integer: "hexadecimal int"
#line 823 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3259 "parser.cpp"
    break;

  case 216: // expr_false: "false"
#line 828 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3265 "parser.cpp"
    break;

  case 217: // expr_true: "true"
#line 833 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3271 "parser.cpp"
    break;


#line 3275 "parser.cpp"

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
  "float", "int", "octal int", "binary int", "hexadecimal int",
  "ADD_ARRAY", "THEN", "TERN", "NEG", "ANIMREF", "PREINC", "PREDEC",
  "POSTINC", "POSTDEC", "$accept", "root", "program", "inline", "include",
  "declaration", "decl_usingtree", "decl_constant", "decl_thread", "stmt",
  "stmt_dev", "stmt_block", "stmt_list", "stmt_expr", "stmt_call",
  "stmt_assign", "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_if", "stmt_ifelse",
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


  const short parser::yypact_ninf_ = -261;

  const short parser::yytable_ninf_ = -205;

  const short
  parser::yypact_[] =
  {
      17,  -261,  -261,   -61,   -61,   -12,  -261,    42,    17,  -261,
    -261,  -261,  -261,  -261,  -261,   -17,  -261,  -261,   -36,    15,
     -16,  -261,  -261,  -261,  -261,    -8,   911,  -261,  -261,  -261,
      38,    18,  -261,  -261,   -40,   -33,  -261,    41,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,   911,   777,    -8,   911,   911,
     -43,     1,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  2063,
    -261,  -261,  -261,  -261,  -261,    69,   347,  -261,  -261,  -261,
    -261,   507,   710,  -261,  -261,   734,  -261,  -261,  -261,   742,
     801,   867,   875,  -261,  -261,    26,    45,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,    49,    53,    -8,    58,    66,
      60,    70,    77,    89,    90,  1389,   777,  -261,  2146,    95,
     103,  -261,  -261,  -261,  -261,  -261,  -261,  -261,   911,   911,
     911,   911,   911,   911,   911,   911,   911,   911,   911,   911,
     911,   911,   911,   911,   911,   911,   911,  -261,   978,    -8,
    -261,  -261,   117,   112,   911,    -8,  -261,  1073,  -261,  -261,
     911,   911,    -8,   911,   911,    -8,   911,  -261,   911,   974,
     911,  -261,  2028,   162,   162,  2177,  2187,  1059,  1059,     8,
       8,     8,     8,  2218,  2259,  2228,   -15,   -15,  -261,  -261,
    -261,  1833,  -261,    -8,    36,  -261,   123,  1149,   911,   120,
     125,  1327,   128,   132,   134,   135,    28,   127,   131,   133,
     844,   136,   145,   150,  -261,   147,   570,   570,  -261,  -261,
    -261,  1200,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,   142,   144,   146,   148,   149,
    -261,  -261,   642,  -261,  -261,  -261,  -261,   -10,  1873,    55,
     155,  1913,    64,   160,  1953,  1992,   156,  2146,   911,  -261,
     123,  -261,   911,  -261,  1276,  2098,  -261,   911,   190,   911,
      -2,    -8,   911,   111,   158,   167,  -261,  -261,  -261,  -261,
    2133,  -261,   911,   911,   911,  -261,  -261,   438,   438,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,   166,   169,   171,   180,
    -261,  -261,   911,   911,   911,   911,   911,   911,   911,   911,
     911,   911,   911,   176,  -261,   911,   177,  -261,   911,   178,
     911,   185,  2146,    82,  -261,  -261,  1555,   186,  1589,   188,
    -261,  -261,  -261,  1353,    -3,  1623,  -261,  -261,  -261,    83,
      84,   974,   911,   911,   911,   911,  2146,  2146,  2146,  2146,
    2146,  2146,  2146,  2146,  2146,  2146,  2146,   197,    85,   200,
      86,   207,  1657,   911,  -261,  1327,   911,  1327,   911,   911,
      -8,    53,   199,   203,  1691,  1433,  1477,  1521,   911,  -261,
     911,  -261,   911,  -261,    94,   214,  1725,  -261,  2146,   204,
    1759,   232,  -261,  -261,  -261,   205,   206,   911,   208,   911,
     209,   911,    97,   115,   118,  -261,  1327,   212,    -2,  1327,
     911,  -261,  -261,   216,  -261,   222,  -261,   224,  -261,  -261,
    -261,  -261,  -261,   225,  -261,  1793,   219,   221,   223,  1327,
    1327,  -261,  -261,  -261,  -261,  -261
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   202,     0,     2,     7,
       8,     9,    14,    15,    16,     0,   203,   204,     0,     0,
       0,     1,     4,     5,     6,   173,     0,    10,    11,   206,
       0,     0,   172,   201,     0,     0,   193,     0,   217,   216,
     195,   196,   197,   198,   199,     0,   175,     0,     0,     0,
       0,     0,   205,   207,   210,   212,   213,   214,   215,     0,
      87,    88,    89,   126,   127,   128,   129,   156,   157,   130,
     131,   132,   133,   134,   135,     0,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,     0,   146,   147,   148,
     149,   150,   151,   152,   153,     0,     0,     0,     0,   204,
       0,     0,   204,     0,     0,     0,   175,   194,   177,     0,
     174,   178,   155,   154,   209,   211,   200,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   182,     0,     0,
     158,   159,   204,     0,   175,     0,    17,     0,    19,   171,
       0,   175,     0,     0,   175,     0,     0,   183,     0,   177,
       0,   170,     0,   119,   120,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   121,   122,   123,   124,
     125,     0,   181,     0,     0,   174,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,     0,     0,     0,    50,    20,
      21,     0,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,     0,     0,     0,   184,   185,
     186,   187,     0,   188,   189,   190,   191,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   176,     0,   180,
       0,   160,   175,    46,     0,     0,    68,     0,     0,     0,
      54,     0,     0,     0,     0,     0,    79,    80,    81,    83,
       0,    84,   175,   175,     0,   184,   185,   103,   105,    47,
      49,    57,    58,    59,    55,    56,     0,     0,     0,     0,
     104,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   162,   175,     0,   164,   175,     0,
       0,     0,   107,     0,    45,    63,     0,     0,     0,     0,
      51,    52,    53,     0,     0,     0,    78,    77,    82,     0,
       0,     0,     0,     0,     0,     0,    92,    98,    99,   100,
     101,   102,    93,    94,    95,    97,    96,     0,     0,     0,
       0,     0,     0,   175,   161,     0,     0,     0,    91,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   175,   163,
     175,   165,   175,   208,     0,    69,     0,    71,    90,     0,
       0,     0,    76,    85,    86,     0,     0,   175,     0,   175,
       0,   175,     0,     0,     0,   166,     0,     0,    54,     0,
       0,    60,    62,   174,    65,   174,    67,   174,   167,   168,
     169,    70,    72,     0,    74,     0,     0,     0,     0,     0,
       0,    61,    64,    66,    73,    75
  };

  const short
  parser::yypgoto_[] =
  {
    -261,  -261,  -261,   267,   274,   275,  -261,  -261,  -261,  -175,
    -261,   -94,    98,  -124,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,   187,  -261,  -260,
    -259,  -255,  -261,  -261,  -261,  -261,  -261,  -128,   -37,   -70,
     -66,  -261,  -261,   425,   -45,  -261,   -26,   157,  -261,  -261,
     241,  -261,  -261,  -261,   255,   273,   329,   361,  -261,  -261,
       0,     9,  -261,   -14,  -261,  -261,  -261,    93,  -261,  -261
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     7,     8,     9,    10,    11,    12,    13,    14,   208,
     209,   210,   211,   329,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   108,   389,   235,
     236,   237,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    31,   109,   185,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94
  };

  const short
  parser::yytable_[] =
  {
      15,   110,   148,    17,    17,   140,    30,    98,    15,   141,
     330,   331,    18,    19,   101,   332,   268,    27,   369,   238,
       1,     2,     3,     4,     5,    32,    25,    16,     6,    34,
      35,    20,    37,   144,    99,   102,   290,    41,    42,    43,
      44,  -204,    21,   100,   103,   205,   370,   111,    16,     6,
     114,   115,    26,   206,   207,    16,     6,  -192,  -192,   238,
    -192,   110,    96,   238,  -192,   119,   120,    97,    28,   144,
     134,   135,   136,  -192,    29,   142,  -192,  -204,   285,   285,
     261,     6,    95,   238,   143,   160,    16,     6,   104,   290,
     116,   132,   133,   134,   135,   136,   145,   149,   147,   314,
    -184,  -184,   146,  -184,   160,   150,     6,  -184,   317,   151,
     239,   152,   273,   160,  -192,  -192,  -184,   153,    29,  -184,
     154,   240,    55,    56,    57,    58,   364,   372,   373,   379,
     381,   160,   160,   160,   160,   160,   238,   156,   405,   182,
     155,   418,   285,   160,   160,   186,   160,   247,   330,   331,
     239,   161,   250,   332,   239,   253,   143,  -184,  -184,   419,
     144,   240,   420,   183,   160,   240,   262,   160,   267,   286,
     286,   269,   140,   266,   239,   270,   141,   271,   272,   276,
     240,   240,   274,   260,   277,   240,   278,   247,   282,   281,
     385,   247,   387,   283,   284,   291,   143,   292,   315,   293,
     143,   294,   295,   318,   321,   115,   247,   247,   327,   342,
     336,   247,   343,    59,   344,   143,   143,   140,   140,   337,
     143,   141,   141,   345,   357,   359,   361,   239,   363,   366,
     406,   421,   105,   286,   424,   112,   113,   238,   240,   238,
     378,   368,   142,   380,   240,   132,   133,   134,   135,   136,
     382,   143,   393,   410,   434,   435,   394,   408,   411,   412,
     426,   414,   416,   140,   247,   422,   427,   141,   428,   429,
     247,   334,   431,   143,   432,    22,   433,   392,   238,   143,
     285,   238,    23,    24,   423,   264,     0,   142,   142,   275,
       0,     0,     0,   159,     0,     0,   143,   143,     0,     0,
       0,   238,   238,     0,   241,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,     0,   181,     0,     0,   239,     0,
     239,     0,     0,   142,     0,     0,     0,   248,     0,   240,
     251,   240,   143,   254,   241,   255,     0,   257,   241,     0,
       0,     0,   413,     0,   415,     0,   417,     0,     0,     0,
       0,     0,     0,   241,   241,   247,     0,   247,   241,   239,
     391,   286,   239,     0,   143,   265,   143,     0,  -185,  -185,
     240,  -185,   240,   240,     0,  -185,     0,   280,   242,     0,
       0,     0,   239,   239,  -185,     0,     0,  -185,     0,     0,
       0,     0,   243,   240,   240,     0,   247,     0,   247,   247,
       0,     0,     0,     0,     0,   143,     0,   143,   143,     0,
     244,   241,     0,     0,     0,     0,     0,   241,   242,   247,
     247,     0,   242,     0,     0,  -185,  -185,     0,   143,   143,
       0,     0,   243,     0,     0,   322,   243,   287,   288,     0,
       0,     0,   242,     0,   326,     0,   328,     0,     0,   335,
     244,   243,   243,     0,   244,     0,   243,     0,     0,    34,
      35,   341,    37,     0,     0,     0,   245,     0,     0,   244,
     244,     0,     0,     0,   244,   138,     0,     0,   139,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
       0,     0,     0,     0,     0,   242,     0,   362,   246,     0,
       0,   333,     0,     0,     0,     0,   245,     0,     0,   243,
     245,     0,   241,     0,   241,   243,    16,     6,     0,   374,
     375,   376,   377,     0,     0,   245,   245,   244,  -186,  -186,
     245,  -186,     0,   244,     0,  -186,     0,     0,   246,     0,
       0,     0,   246,   386,  -186,   388,   390,  -186,     0,     0,
       0,     0,     0,   241,     0,   241,   241,   246,   246,   184,
       0,     0,   246,     0,     0,     0,   249,     0,     0,   252,
       0,     0,     0,     0,     0,     0,   241,   241,     0,     0,
       0,     0,     0,   245,     0,  -186,  -186,   425,     0,   245,
       0,    34,    35,     0,    37,     0,   242,     0,   242,    41,
      42,    43,    44,     0,     0,     0,     0,   205,     0,     0,
     243,     0,   243,     0,     0,   246,     0,     0,     0,     0,
       0,   246,     0,     0,     0,     0,     0,     0,   244,     0,
     244,     0,     0,     0,     0,     0,     0,   242,     0,   333,
     242,   296,   297,     0,   298,   299,     0,     0,    16,     6,
       0,   243,     0,   243,   243,     0,     0,     0,     0,     0,
     242,   242,     0,    34,    35,     0,    37,     0,     0,   244,
       0,   244,   244,     0,   243,   243,     0,   323,     0,   138,
       0,     0,   139,     0,   245,     0,   245,   300,   301,     0,
       0,     0,   244,   244,     0,     0,     0,   339,   340,     0,
       0,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,     0,     0,     0,     0,   246,     0,   246,     0,
      16,     6,     0,     0,     0,   245,     0,   245,   245,     0,
     358,  -187,  -187,   360,  -187,     0,     0,     0,  -187,     0,
       0,     0,     0,     0,     0,     0,     0,  -187,   245,   245,
    -187,     0,     0,     0,     0,    34,    35,   246,    37,   246,
     246,     0,   137,  -188,  -188,     0,  -188,     0,     0,     0,
    -188,   138,     0,     0,   139,    33,     0,     0,   384,  -188,
     246,   246,  -188,     0,     0,     0,     0,     0,  -187,  -187,
       0,     0,     0,   402,     0,   403,     0,   404,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,    43,    44,
      45,     0,    16,     6,   106,   107,     0,     0,    47,     0,
    -188,  -188,  -189,  -189,     0,  -189,     0,     0,     0,  -189,
       0,     0,     0,     0,    48,    49,     0,     0,  -189,     0,
       0,  -189,    33,     0,     0,     0,     0,     0,     0,     0,
       0,    50,     0,     0,    51,    16,     6,    29,    52,    53,
      54,    55,    56,    57,    58,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,    43,    44,    45,     0,  -189,
    -189,    46,     0,     0,     0,    47,     0,   279,  -190,  -190,
       0,  -190,     0,     0,     0,  -190,  -191,  -191,     0,  -191,
       0,    48,    49,  -191,  -190,     0,     0,  -190,     0,    33,
       0,     0,  -191,     0,     0,  -191,     0,     0,    50,     0,
       0,    51,    16,     6,    29,    52,    53,    54,    55,    56,
      57,    58,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,    45,  -190,  -190,     0,    46,     0,
       0,     0,    47,  -191,  -191,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,     0,    51,    16,
       6,    29,    52,    53,    54,    55,    56,    57,    58,    34,
      35,    36,    37,    38,    39,    40,     0,    41,    42,    43,
      44,    45,   256,     0,     0,   106,     0,     0,   118,    47,
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,     0,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,   129,   130,   131,   132,   133,   134,
     135,   136,    50,     0,     0,    51,    16,     6,    29,    52,
      53,    54,    55,    56,    57,    58,   187,     0,     0,     0,
       0,     0,     0,     0,   188,     0,     0,   189,   190,     0,
     191,   192,   193,   194,     0,   195,   196,   197,   198,   199,
     200,   201,   202,   203,    34,    35,     0,    37,     0,     0,
       0,     0,    41,    42,    43,    44,   119,   120,   147,   204,
     205,     0,   125,   126,   127,   128,     0,     0,   206,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,   133,   134,   135,   136,     0,     0,     0,
       0,     0,   187,   263,     0,     0,     0,     0,     0,     0,
     188,    16,     6,   189,   190,     0,   191,   192,   193,   194,
       0,   195,   196,   197,   198,   199,   200,   201,   202,   203,
      34,    35,     0,    37,     0,     0,     0,     0,    41,    42,
      43,    44,     0,     0,   147,     0,   205,     0,     0,     0,
       0,     0,     0,   187,   206,   207,     0,     0,     0,     0,
       0,   188,     0,     0,   189,   190,     0,   191,   192,   193,
     194,     0,   195,   196,   197,   198,   199,   200,   201,   202,
     203,    34,    35,     0,    37,     0,     0,    16,     6,    41,
      42,    43,    44,     0,     0,   147,   289,   205,     0,     0,
       0,     0,     0,     0,     0,   206,   207,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   187,
     324,     0,     0,     0,     0,     0,     0,   188,    16,     6,
     189,   190,     0,   191,   192,   193,   194,     0,   195,   196,
     197,   198,   199,   200,   201,   202,   203,    34,    35,     0,
      37,     0,     0,     0,     0,    41,    42,    43,    44,     0,
       0,   147,     0,   205,     0,     0,     0,     0,     0,     0,
     187,   206,   207,     0,     0,     0,     0,     0,   188,     0,
       0,   189,   190,     0,   191,   192,   193,   194,     0,   195,
     196,   197,   198,   199,   200,   201,   202,   203,    34,    35,
       0,    37,     0,     0,    16,     6,    41,    42,    43,    44,
       0,     0,   147,     0,   205,     0,     0,     0,     0,     0,
       0,     0,   206,   207,    34,    35,     0,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,     0,     0,   139,     0,     0,     0,     0,   300,   301,
       0,     0,     0,     0,     0,    16,     6,     0,     0,     0,
       0,     0,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   157,     0,     0,     0,     0,   158,     0,
       0,    16,     6,   118,     0,     0,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
     130,   131,   132,   133,   134,   135,   136,   396,     0,     0,
       0,     0,   397,     0,     0,     0,     0,   118,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   398,     0,     0,     0,     0,   399,     0,     0,     0,
       0,   118,     0,     0,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   400,     0,     0,     0,     0,
     401,     0,     0,     0,     0,   118,     0,     0,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   365,
       0,   129,   130,   131,   132,   133,   134,   135,   136,   118,
       0,     0,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   367,     0,   129,   130,   131,   132,   133,
     134,   135,   136,   118,     0,     0,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,   129,
     130,   131,   132,   133,   134,   135,   136,   118,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   383,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   118,     0,     0,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   395,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   118,     0,     0,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   407,
       0,   129,   130,   131,   132,   133,   134,   135,   136,   118,
       0,     0,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   409,     0,   129,   130,   131,   132,   133,
     134,   135,   136,   118,     0,     0,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   430,     0,   129,
     130,   131,   132,   133,   134,   135,   136,   118,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   259,     0,     0,     0,     0,     0,   118,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   313,     0,     0,     0,     0,     0,   118,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   316,     0,     0,     0,     0,     0,   118,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   319,     0,     0,     0,     0,     0,   118,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   320,     0,     0,     0,     0,   118,     0,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     258,     0,   118,     0,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   130,
     131,   132,   133,   134,   135,   136,   117,   118,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   325,   118,     0,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   130,
     131,   132,   133,   134,   135,   136,   338,   118,     0,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     118,     0,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,     0,     0,     0,     0,     0,   129,   130,   131,   132,
     133,   134,   135,   136,   119,   120,     0,   122,   123,   124,
     125,   126,   127,   128,   119,   120,     0,     0,   123,   124,
     125,   126,   127,   128,     0,     0,     0,   129,   130,   131,
     132,   133,   134,   135,   136,     0,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   119,   120,     0,     0,   123,
     124,   125,   126,   127,   128,   119,   120,     0,     0,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,   130,
     131,   132,   133,   134,   135,   136,     0,     0,     0,   130,
       0,   132,   133,   134,   135,   136,   119,   120,     0,     0,
     123,   124,   125,   126,   127,   128,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,   133,   134,   135,   136
  };

  const short
  parser::yycheck_[] =
  {
       0,    46,    96,     3,     4,    75,    20,    47,     8,    75,
     270,   270,     3,     4,    47,   270,   191,    53,    21,   147,
       3,     4,     5,     6,     7,    25,    43,    88,    89,    31,
      32,    43,    34,    43,    34,    35,   211,    39,    40,    41,
      42,    51,     0,    34,    35,    47,    49,    47,    88,    89,
      93,    94,    69,    55,    56,    88,    89,    31,    32,   187,
      34,   106,    44,   191,    38,    57,    58,    49,    53,    43,
      85,    86,    87,    47,    90,    75,    50,    51,   206,   207,
      44,    89,    44,   211,    75,    49,    88,    89,    47,   264,
      89,    83,    84,    85,    86,    87,    51,    97,    45,    44,
      31,    32,    53,    34,    49,    47,    89,    38,    44,    43,
     147,    51,    84,    49,    88,    89,    47,    47,    90,    50,
      43,   147,    94,    95,    96,    97,    44,    44,    44,    44,
      44,    49,    49,    49,    49,    49,   264,    47,    44,   139,
      51,    44,   270,    49,    49,   145,    49,   147,   408,   408,
     187,    48,   152,   408,   191,   155,   147,    88,    89,    44,
      43,   187,    44,    51,    49,   191,    43,    49,    43,   206,
     207,    43,   242,    53,   211,    43,   242,    43,    43,    52,
     206,   207,   196,   183,    53,   211,    53,   187,    43,    53,
     365,   191,   367,    43,    47,    53,   187,    53,    43,    53,
     191,    53,    53,    43,    48,    94,   206,   207,    18,    43,
      52,   211,    43,    26,    43,   206,   207,   287,   288,    52,
     211,   287,   288,    43,    48,    48,    48,   264,    43,    43,
      16,   406,    45,   270,   409,    48,    49,   365,   264,   367,
      43,    53,   242,    43,   270,    83,    84,    85,    86,    87,
      43,   242,    53,    21,   429,   430,    53,    53,    53,    53,
      44,    53,    53,   333,   264,    53,    44,   333,    44,    44,
     270,   271,    53,   264,    53,     8,    53,   371,   406,   270,
     408,   409,     8,     8,   408,   187,    -1,   287,   288,   196,
      -1,    -1,    -1,   106,    -1,    -1,   287,   288,    -1,    -1,
      -1,   429,   430,    -1,   147,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,    -1,   138,    -1,    -1,   365,    -1,
     367,    -1,    -1,   333,    -1,    -1,    -1,   150,    -1,   365,
     153,   367,   333,   156,   187,   158,    -1,   160,   191,    -1,
      -1,    -1,   397,    -1,   399,    -1,   401,    -1,    -1,    -1,
      -1,    -1,    -1,   206,   207,   365,    -1,   367,   211,   406,
     370,   408,   409,    -1,   365,   188,   367,    -1,    31,    32,
     406,    34,   408,   409,    -1,    38,    -1,   200,   147,    -1,
      -1,    -1,   429,   430,    47,    -1,    -1,    50,    -1,    -1,
      -1,    -1,   147,   429,   430,    -1,   406,    -1,   408,   409,
      -1,    -1,    -1,    -1,    -1,   406,    -1,   408,   409,    -1,
     147,   264,    -1,    -1,    -1,    -1,    -1,   270,   187,   429,
     430,    -1,   191,    -1,    -1,    88,    89,    -1,   429,   430,
      -1,    -1,   187,    -1,    -1,   258,   191,   206,   207,    -1,
      -1,    -1,   211,    -1,   267,    -1,   269,    -1,    -1,   272,
     187,   206,   207,    -1,   191,    -1,   211,    -1,    -1,    31,
      32,   284,    34,    -1,    -1,    -1,   147,    -1,    -1,   206,
     207,    -1,    -1,    -1,   211,    47,    -1,    -1,    50,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
      -1,    -1,    -1,    -1,    -1,   264,    -1,   320,   147,    -1,
      -1,   270,    -1,    -1,    -1,    -1,   187,    -1,    -1,   264,
     191,    -1,   365,    -1,   367,   270,    88,    89,    -1,   342,
     343,   344,   345,    -1,    -1,   206,   207,   264,    31,    32,
     211,    34,    -1,   270,    -1,    38,    -1,    -1,   187,    -1,
      -1,    -1,   191,   366,    47,   368,   369,    50,    -1,    -1,
      -1,    -1,    -1,   406,    -1,   408,   409,   206,   207,   144,
      -1,    -1,   211,    -1,    -1,    -1,   151,    -1,    -1,   154,
      -1,    -1,    -1,    -1,    -1,    -1,   429,   430,    -1,    -1,
      -1,    -1,    -1,   264,    -1,    88,    89,   410,    -1,   270,
      -1,    31,    32,    -1,    34,    -1,   365,    -1,   367,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    47,    -1,    -1,
     365,    -1,   367,    -1,    -1,   264,    -1,    -1,    -1,    -1,
      -1,   270,    -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,
     367,    -1,    -1,    -1,    -1,    -1,    -1,   406,    -1,   408,
     409,     9,    10,    -1,    12,    13,    -1,    -1,    88,    89,
      -1,   406,    -1,   408,   409,    -1,    -1,    -1,    -1,    -1,
     429,   430,    -1,    31,    32,    -1,    34,    -1,    -1,   406,
      -1,   408,   409,    -1,   429,   430,    -1,   262,    -1,    47,
      -1,    -1,    50,    -1,   365,    -1,   367,    55,    56,    -1,
      -1,    -1,   429,   430,    -1,    -1,    -1,   282,   283,    -1,
      -1,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    -1,    -1,    -1,    -1,   365,    -1,   367,    -1,
      88,    89,    -1,    -1,    -1,   406,    -1,   408,   409,    -1,
     315,    31,    32,   318,    34,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,   429,   430,
      50,    -1,    -1,    -1,    -1,    31,    32,   406,    34,   408,
     409,    -1,    38,    31,    32,    -1,    34,    -1,    -1,    -1,
      38,    47,    -1,    -1,    50,     8,    -1,    -1,   363,    47,
     429,   430,    50,    -1,    -1,    -1,    -1,    -1,    88,    89,
      -1,    -1,    -1,   378,    -1,   380,    -1,   382,    31,    32,
      33,    34,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    -1,    88,    89,    47,    48,    -1,    -1,    51,    -1,
      88,    89,    31,    32,    -1,    34,    -1,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    67,    68,    -1,    -1,    47,    -1,
      -1,    50,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    -1,    88,
      89,    47,    -1,    -1,    -1,    51,    -1,    53,    31,    32,
      -1,    34,    -1,    -1,    -1,    38,    31,    32,    -1,    34,
      -1,    67,    68,    38,    47,    -1,    -1,    50,    -1,     8,
      -1,    -1,    47,    -1,    -1,    50,    -1,    -1,    84,    -1,
      -1,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    31,    32,    33,    34,    35,    36,    37,    -1,
      39,    40,    41,    42,    43,    88,    89,    -1,    47,    -1,
      -1,    -1,    51,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    31,
      32,    33,    34,    35,    36,    37,    -1,    39,    40,    41,
      42,    43,    48,    -1,    -1,    47,    -1,    -1,    54,    51,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    67,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    81,    82,    83,    84,    85,
      86,    87,    84,    -1,    -1,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    11,    -1,    -1,    14,    15,    -1,
      17,    18,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    57,    58,    45,    46,
      47,    -1,    63,    64,    65,    66,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      11,    88,    89,    14,    15,    -1,    17,    18,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    -1,    -1,    45,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    55,    56,    -1,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    14,    15,    -1,    17,    18,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    -1,    -1,    88,    89,    39,
      40,    41,    42,    -1,    -1,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,    -1,    -1,    -1,    -1,    -1,    -1,    11,    88,    89,
      14,    15,    -1,    17,    18,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    -1,
      34,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,
      -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    55,    56,    -1,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    14,    15,    -1,    17,    18,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    -1,    -1,    88,    89,    39,    40,    41,    42,
      -1,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    31,    32,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    50,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    -1,    -1,    -1,    88,    89,    -1,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    44,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    88,    89,    54,    -1,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      81,    82,    83,    84,    85,    86,    87,    44,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    44,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,    58,
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
      -1,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    49,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    80,    81,    82,    83,    84,    85,    86,    87,
      52,    -1,    54,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    53,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    82,    83,    84,    85,    86,
      87,    53,    54,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    53,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      54,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    80,    81,    82,    83,    84,    85,    86,
      87,    -1,    -1,    -1,    -1,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    57,    58,    -1,    60,    61,    62,
      63,    64,    65,    66,    57,    58,    -1,    -1,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    -1,    -1,    80,    81,    82,
      83,    84,    85,    86,    87,    57,    58,    -1,    -1,    61,
      62,    63,    64,    65,    66,    57,    58,    -1,    -1,    61,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    -1,    -1,    -1,    81,
      -1,    83,    84,    85,    86,    87,    57,    58,    -1,    -1,
      61,    62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    85,    86,    87
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,    89,   108,   109,   110,
     111,   112,   113,   114,   115,   177,    88,   177,   178,   178,
      43,     0,   110,   111,   112,    43,    69,    53,    53,    90,
     180,   159,   177,     8,    31,    32,    33,    34,    35,    36,
      37,    39,    40,    41,    42,    43,    47,    51,    67,    68,
      84,    87,    91,    92,    93,    94,    95,    96,    97,   144,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,    44,    44,    49,    47,   177,
     178,    47,   177,   178,    47,   144,    47,    48,   144,   160,
     161,   177,   144,   144,    93,    94,    89,    53,    54,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    80,
      81,    82,    83,    84,    85,    86,    87,    38,    47,    50,
     156,   157,   177,   178,    43,    51,    53,    45,   118,   177,
      47,    43,    51,    47,    43,    51,    47,    44,    49,   144,
      49,    48,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   177,    51,   160,   161,   177,     3,    11,    14,
      15,    17,    18,    19,    20,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    46,    47,    55,    56,   116,   117,
     118,   119,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   146,   147,   148,   154,   155,
     163,   164,   167,   171,   172,   173,   174,   177,   144,   160,
     177,   144,   160,   177,   144,   144,    48,   144,    52,    48,
     177,    44,    43,     4,   119,   144,    53,    43,   116,    43,
      43,    43,    43,    84,   180,   184,    52,    53,    53,    53,
     144,    53,    43,    43,    47,   154,   155,   167,   167,    46,
     116,    53,    53,    53,    53,    53,     9,    10,    12,    13,
      55,    56,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    48,    44,    43,    48,    44,    43,    48,
      49,    48,   144,   160,     4,    53,   144,    18,   144,   120,
     146,   147,   148,   167,   177,   144,    52,    52,    53,   160,
     160,   144,    43,    43,    43,    43,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,    48,   160,    48,
     160,    48,   144,    43,    44,    44,    43,    44,    53,    21,
      49,    44,    44,    44,   144,   144,   144,   144,    43,    44,
      43,    44,    43,    44,   160,   116,   144,   116,   144,   145,
     144,   177,   118,    53,    53,    44,    44,    49,    44,    49,
      44,    49,   160,   160,   160,    44,    16,    44,    53,    44,
      21,    53,    53,   161,    53,   161,    53,   161,    44,    44,
      44,   116,    53,   120,   116,   144,    44,    44,    44,    44,
      44,    53,    53,    53,   116,   116
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   107,   108,   108,   109,   109,   109,   109,   109,   109,
     110,   111,   112,   112,   112,   112,   112,   113,   114,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   117,   117,   118,   118,   119,
     119,   120,   120,   120,   120,   121,   121,   122,   122,   122,
     123,   124,   124,   125,   126,   126,   127,   127,   128,   129,
     130,   131,   132,   133,   134,   134,   135,   136,   136,   137,
     138,   139,   140,   140,   141,   142,   143,   144,   144,   144,
     145,   145,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   147,   147,   148,   148,   149,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   152,   153,   154,   154,   155,   155,
     156,   156,   156,   156,   156,   156,   157,   157,   157,   157,
     158,   159,   159,   159,   160,   160,   161,   161,   162,   162,
     163,   164,   165,   166,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   178,   179,   180,   181,   182,   183,
     183,   184,   184,   184,   184,   184,   185,   186
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
       1,     2,     1,     1,     1,     1,     1,     1
  };




#if IW7DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   252,   252,   253,   257,   259,   261,   263,   265,   267,
     272,   276,   281,   282,   283,   284,   285,   289,   294,   299,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   332,   333,   337,   338,   342,
     344,   349,   351,   353,   356,   360,   362,   367,   369,   371,
     376,   381,   383,   388,   393,   395,   400,   402,   407,   412,
     417,   422,   427,   432,   437,   439,   444,   449,   451,   456,
     461,   466,   471,   473,   478,   483,   488,   493,   494,   495,
     499,   500,   504,   506,   508,   510,   512,   514,   516,   518,
     520,   522,   524,   529,   531,   536,   538,   543,   548,   550,
     552,   554,   556,   558,   560,   562,   564,   566,   568,   570,
     572,   574,   576,   578,   580,   582,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     611,   612,   613,   614,   618,   623,   628,   629,   632,   633,
     637,   639,   641,   643,   645,   647,   652,   654,   656,   658,
     663,   668,   670,   673,   677,   680,   684,   686,   691,   693,
     698,   703,   708,   713,   718,   719,   720,   721,   722,   723,
     724,   725,   726,   730,   735,   740,   745,   750,   755,   760,
     765,   770,   775,   780,   782,   787,   792,   797,   802,   807,
     809,   814,   816,   818,   820,   822,   827,   832
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
#line 4527 "parser.cpp"

#line 836 "parser.ypp"


void xsk::gsc::iw7::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
