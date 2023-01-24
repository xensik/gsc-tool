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

#include "stdinc.hpp"
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
#line 2340 "parser.cpp"
    break;

  case 3: // root: %empty
#line 296 "parser.ypp"
              { ast = std::make_unique<ast::program>(yylhs.location); }
#line 2346 "parser.cpp"
    break;

  case 4: // program: program inline
#line 301 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); }
#line 2352 "parser.cpp"
    break;

  case 5: // program: program include
#line 303 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2358 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 305 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::move(yystack_[1].value.as < ast::program::ptr > ()); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2364 "parser.cpp"
    break;

  case 7: // program: inline
#line 307 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); }
#line 2370 "parser.cpp"
    break;

  case 8: // program: include
#line 309 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < ast::include::ptr > ())); }
#line 2376 "parser.cpp"
    break;

  case 9: // program: declaration
#line 311 "parser.ypp"
        { yylhs.value.as < ast::program::ptr > () = std::make_unique<ast::program>(yylhs.location); yylhs.value.as < ast::program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < ast::decl > ())); }
#line 2382 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 315 "parser.ypp"
                                 { lexer.push_header(yystack_[1].value.as < ast::expr_path::ptr > ()->value); }
#line 2388 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 320 "parser.ypp"
        { yylhs.value.as < ast::include::ptr > () = std::make_unique<ast::include>(yylhs.location, std::move(yystack_[1].value.as < ast::expr_path::ptr > ())); }
#line 2394 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 324 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_begin = std::make_unique<ast::decl_dev_begin>(yylhs.location); }
#line 2400 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 325 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_dev_end = std::make_unique<ast::decl_dev_end>(yylhs.location); }
#line 2406 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 326 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_usingtree = std::move(yystack_[0].value.as < ast::decl_usingtree::ptr > ()); }
#line 2412 "parser.cpp"
    break;

  case 15: // declaration: decl_thread
#line 327 "parser.ypp"
                        { yylhs.value.as < ast::decl > ().as_thread = std::move(yystack_[0].value.as < ast::decl_thread::ptr > ()); }
#line 2418 "parser.cpp"
    break;

  case 16: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 332 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_usingtree::ptr > () = std::make_unique<ast::decl_usingtree>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_string::ptr > ())); }
#line 2424 "parser.cpp"
    break;

  case 17: // decl_thread: expr_identifier "(" expr_parameters ")" stmt_block
#line 337 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()), export_flags::export_none); }
#line 2430 "parser.cpp"
    break;

  case 18: // decl_thread: "autoexec" expr_identifier "(" expr_parameters ")" stmt_block
#line 339 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()), export_flags::export_autoexec); }
#line 2436 "parser.cpp"
    break;

  case 19: // decl_thread: "codecall" expr_identifier "(" expr_parameters ")" stmt_block
#line 341 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()), export_flags::export_codecall); }
#line 2442 "parser.cpp"
    break;

  case 20: // decl_thread: "private" expr_identifier "(" expr_parameters ")" stmt_block
#line 343 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < ast::decl_thread::ptr > () = std::make_unique<ast::decl_thread>(yylhs.location, std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()), export_flags::export_private2); }
#line 2448 "parser.cpp"
    break;

  case 21: // stmt: stmt_block
#line 347 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_list = std::move(yystack_[0].value.as < ast::stmt_list::ptr > ()); }
#line 2454 "parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 348 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_call = std::move(yystack_[0].value.as < ast::stmt_call::ptr > ()); }
#line 2460 "parser.cpp"
    break;

  case 23: // stmt: stmt_const
#line 349 "parser.ypp"
                            { yylhs.value.as < ast::stmt > ().as_const = std::move(yystack_[0].value.as < ast::stmt_const::ptr > ()); }
#line 2466 "parser.cpp"
    break;

  case 24: // stmt: stmt_assign
#line 350 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_assign = std::move(yystack_[0].value.as < ast::stmt_assign::ptr > ()); }
#line 2472 "parser.cpp"
    break;

  case 25: // stmt: stmt_endon
#line 351 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_endon = std::move(yystack_[0].value.as < ast::stmt_endon::ptr > ()); }
#line 2478 "parser.cpp"
    break;

  case 26: // stmt: stmt_notify
#line 352 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_notify = std::move(yystack_[0].value.as < ast::stmt_notify::ptr > ()); }
#line 2484 "parser.cpp"
    break;

  case 27: // stmt: stmt_wait
#line 353 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_wait = std::move(yystack_[0].value.as < ast::stmt_wait::ptr > ()); }
#line 2490 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittill
#line 354 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittill = std::move(yystack_[0].value.as < ast::stmt_waittill::ptr > ()); }
#line 2496 "parser.cpp"
    break;

  case 29: // stmt: stmt_waittillmatch
#line 355 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < ast::stmt_waittillmatch::ptr > ()); }
#line 2502 "parser.cpp"
    break;

  case 30: // stmt: stmt_waittillframeend
#line 356 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < ast::stmt_waittillframeend::ptr > ()); }
#line 2508 "parser.cpp"
    break;

  case 31: // stmt: stmt_if
#line 357 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_if = std::move(yystack_[0].value.as < ast::stmt_if::ptr > ()); }
#line 2514 "parser.cpp"
    break;

  case 32: // stmt: stmt_ifelse
#line 358 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_ifelse = std::move(yystack_[0].value.as < ast::stmt_ifelse::ptr > ()); }
#line 2520 "parser.cpp"
    break;

  case 33: // stmt: stmt_while
#line 359 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_while = std::move(yystack_[0].value.as < ast::stmt_while::ptr > ()); }
#line 2526 "parser.cpp"
    break;

  case 34: // stmt: stmt_dowhile
#line 360 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_dowhile = std::move(yystack_[0].value.as < ast::stmt_dowhile::ptr > ()); }
#line 2532 "parser.cpp"
    break;

  case 35: // stmt: stmt_for
#line 361 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_for = std::move(yystack_[0].value.as < ast::stmt_for::ptr > ()); }
#line 2538 "parser.cpp"
    break;

  case 36: // stmt: stmt_foreach
#line 362 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_foreach = std::move(yystack_[0].value.as < ast::stmt_foreach::ptr > ()); }
#line 2544 "parser.cpp"
    break;

  case 37: // stmt: stmt_switch
#line 363 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_switch = std::move(yystack_[0].value.as < ast::stmt_switch::ptr > ()); }
#line 2550 "parser.cpp"
    break;

  case 38: // stmt: stmt_case
#line 364 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_case = std::move(yystack_[0].value.as < ast::stmt_case::ptr > ()); }
#line 2556 "parser.cpp"
    break;

  case 39: // stmt: stmt_default
#line 365 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_default = std::move(yystack_[0].value.as < ast::stmt_default::ptr > ()); }
#line 2562 "parser.cpp"
    break;

  case 40: // stmt: stmt_break
#line 366 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_break = std::move(yystack_[0].value.as < ast::stmt_break::ptr > ()); }
#line 2568 "parser.cpp"
    break;

  case 41: // stmt: stmt_continue
#line 367 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_continue = std::move(yystack_[0].value.as < ast::stmt_continue::ptr > ()); }
#line 2574 "parser.cpp"
    break;

  case 42: // stmt: stmt_return
#line 368 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_return = std::move(yystack_[0].value.as < ast::stmt_return::ptr > ()); }
#line 2580 "parser.cpp"
    break;

  case 43: // stmt: stmt_prof_begin
#line 369 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_begin = std::move(yystack_[0].value.as < ast::stmt_prof_begin::ptr > ()); }
#line 2586 "parser.cpp"
    break;

  case 44: // stmt: stmt_prof_end
#line 370 "parser.ypp"
                             { yylhs.value.as < ast::stmt > ().as_prof_end = std::move(yystack_[0].value.as < ast::stmt_prof_end::ptr > ()); }
#line 2592 "parser.cpp"
    break;

  case 45: // stmt_or_dev: stmt
#line 374 "parser.ypp"
               { yylhs.value.as < ast::stmt > () = std::move(yystack_[0].value.as < ast::stmt > ()); }
#line 2598 "parser.cpp"
    break;

  case 46: // stmt_or_dev: stmt_dev
#line 375 "parser.ypp"
               { yylhs.value.as < ast::stmt > ().as_dev = std::move(yystack_[0].value.as < ast::stmt_dev::ptr > ()); }
#line 2604 "parser.cpp"
    break;

  case 47: // stmt_list: stmt_list stmt
#line 380 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2610 "parser.cpp"
    break;

  case 48: // stmt_list: stmt
#line 382 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2616 "parser.cpp"
    break;

  case 49: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 387 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2622 "parser.cpp"
    break;

  case 50: // stmt_or_dev_list: stmt_or_dev
#line 389 "parser.ypp"
        { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); yylhs.value.as < ast::stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2628 "parser.cpp"
    break;

  case 51: // stmt_dev: "/#" stmt_list "#/"
#line 393 "parser.ypp"
                                { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::move(yystack_[1].value.as < ast::stmt_list::ptr > ())); }
#line 2634 "parser.cpp"
    break;

  case 52: // stmt_dev: "/#" "#/"
#line 394 "parser.ypp"
                      { yylhs.value.as < ast::stmt_dev::ptr > () = std::make_unique<ast::stmt_dev>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2640 "parser.cpp"
    break;

  case 53: // stmt_block: "{" stmt_or_dev_list "}"
#line 398 "parser.ypp"
                                     { yylhs.value.as < ast::stmt_list::ptr > () = std::move(yystack_[1].value.as < ast::stmt_list::ptr > ()); }
#line 2646 "parser.cpp"
    break;

  case 54: // stmt_block: "{" "}"
#line 399 "parser.ypp"
                    { yylhs.value.as < ast::stmt_list::ptr > () = std::make_unique<ast::stmt_list>(yylhs.location); }
#line 2652 "parser.cpp"
    break;

  case 55: // stmt_expr: expr_assign
#line 404 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2658 "parser.cpp"
    break;

  case 56: // stmt_expr: expr_increment
#line 406 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2664 "parser.cpp"
    break;

  case 57: // stmt_expr: expr_decrement
#line 408 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2670 "parser.cpp"
    break;

  case 58: // stmt_expr: %empty
#line 410 "parser.ypp"
        { yylhs.value.as < ast::stmt_expr::ptr > () = std::make_unique<ast::stmt_expr>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2676 "parser.cpp"
    break;

  case 59: // stmt_call: expr_call ";"
#line 415 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_call::ptr > ()))); }
#line 2682 "parser.cpp"
    break;

  case 60: // stmt_call: expr_method ";"
#line 417 "parser.ypp"
        { yylhs.value.as < ast::stmt_call::ptr > () = std::make_unique<ast::stmt_call>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_method::ptr > ()))); }
#line 2688 "parser.cpp"
    break;

  case 61: // stmt_const: "const" expr_identifier "=" expr ";"
#line 422 "parser.ypp"
        { yylhs.value.as < ast::stmt_const::ptr > () = std::make_unique<ast::stmt_const>(yylhs.location, std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2694 "parser.cpp"
    break;

  case 62: // stmt_assign: expr_assign ";"
#line 427 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2700 "parser.cpp"
    break;

  case 63: // stmt_assign: expr_increment ";"
#line 429 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2706 "parser.cpp"
    break;

  case 64: // stmt_assign: expr_decrement ";"
#line 431 "parser.ypp"
        { yylhs.value.as < ast::stmt_assign::ptr > () = std::make_unique<ast::stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2712 "parser.cpp"
    break;

  case 65: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 436 "parser.ypp"
        { yylhs.value.as < ast::stmt_endon::ptr > () = std::make_unique<ast::stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ())); }
#line 2718 "parser.cpp"
    break;

  case 66: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 441 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2724 "parser.cpp"
    break;

  case 67: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 443 "parser.ypp"
        { yylhs.value.as < ast::stmt_notify::ptr > () = std::make_unique<ast::stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2730 "parser.cpp"
    break;

  case 68: // stmt_wait: "wait" expr ";"
#line 448 "parser.ypp"
        { yylhs.value.as < ast::stmt_wait::ptr > () = std::make_unique<ast::stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2736 "parser.cpp"
    break;

  case 69: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 453 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2742 "parser.cpp"
    break;

  case 70: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 455 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittill::ptr > () = std::make_unique<ast::stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2748 "parser.cpp"
    break;

  case 71: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 460 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < ast::expr > ()), std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2754 "parser.cpp"
    break;

  case 72: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 462 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillmatch::ptr > () = std::make_unique<ast::stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::make_unique<ast::expr_arguments>(yylhs.location)); }
#line 2760 "parser.cpp"
    break;

  case 73: // stmt_waittillframeend: "waittillframeend" ";"
#line 467 "parser.ypp"
        { yylhs.value.as < ast::stmt_waittillframeend::ptr > () = std::make_unique<ast::stmt_waittillframeend>(yylhs.location); }
#line 2766 "parser.cpp"
    break;

  case 74: // stmt_if: "if" "(" expr ")" stmt
#line 472 "parser.ypp"
        { yylhs.value.as < ast::stmt_if::ptr > () = std::make_unique<ast::stmt_if>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2772 "parser.cpp"
    break;

  case 75: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 477 "parser.ypp"
        { yylhs.value.as < ast::stmt_ifelse::ptr > () = std::make_unique<ast::stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::stmt > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2778 "parser.cpp"
    break;

  case 76: // stmt_while: "while" "(" expr ")" stmt
#line 482 "parser.ypp"
        { yylhs.value.as < ast::stmt_while::ptr > () = std::make_unique<ast::stmt_while>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2784 "parser.cpp"
    break;

  case 77: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 487 "parser.ypp"
        { yylhs.value.as < ast::stmt_dowhile::ptr > () = std::make_unique<ast::stmt_dowhile>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[5].value.as < ast::stmt > ())); }
#line 2790 "parser.cpp"
    break;

  case 78: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 492 "parser.ypp"
        { yylhs.value.as < ast::stmt_for::ptr > () = std::make_unique<ast::stmt_for>(yylhs.location, ast::stmt(std::move(yystack_[6].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[4].value.as < ast::expr > ()), ast::stmt(std::move(yystack_[2].value.as < ast::stmt_expr::ptr > ())), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2796 "parser.cpp"
    break;

  case 79: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 497 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2802 "parser.cpp"
    break;

  case 80: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 499 "parser.ypp"
        { yylhs.value.as < ast::stmt_foreach::ptr > () = std::make_unique<ast::stmt_foreach>(yylhs.location, ast::expr(std::move(yystack_[6].value.as < ast::expr_identifier::ptr > ())), ast::expr(std::move(yystack_[4].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt > ())); }
#line 2808 "parser.cpp"
    break;

  case 81: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 504 "parser.ypp"
        { yylhs.value.as < ast::stmt_switch::ptr > () = std::make_unique<ast::stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::stmt_list::ptr > ())); }
#line 2814 "parser.cpp"
    break;

  case 82: // stmt_case: "case" expr_integer ":"
#line 509 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_integer::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2820 "parser.cpp"
    break;

  case 83: // stmt_case: "case" expr_string ":"
#line 511 "parser.ypp"
        { yylhs.value.as < ast::stmt_case::ptr > () = std::make_unique<ast::stmt_case>(yylhs.location, ast::expr(std::move(yystack_[1].value.as < ast::expr_string::ptr > ())), std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2826 "parser.cpp"
    break;

  case 84: // stmt_default: "default" ":"
#line 516 "parser.ypp"
        { yylhs.value.as < ast::stmt_default::ptr > () = std::make_unique<ast::stmt_default>(yylhs.location, std::make_unique<ast::stmt_list>(yylhs.location)); }
#line 2832 "parser.cpp"
    break;

  case 85: // stmt_break: "break" ";"
#line 521 "parser.ypp"
        { yylhs.value.as < ast::stmt_break::ptr > () = std::make_unique<ast::stmt_break>(yylhs.location); }
#line 2838 "parser.cpp"
    break;

  case 86: // stmt_continue: "continue" ";"
#line 526 "parser.ypp"
        { yylhs.value.as < ast::stmt_continue::ptr > () = std::make_unique<ast::stmt_continue>(yylhs.location); }
#line 2844 "parser.cpp"
    break;

  case 87: // stmt_return: "return" expr ";"
#line 531 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 2850 "parser.cpp"
    break;

  case 88: // stmt_return: "return" ";"
#line 533 "parser.ypp"
        { yylhs.value.as < ast::stmt_return::ptr > () = std::make_unique<ast::stmt_return>(yylhs.location, std::make_unique<ast::node>(yylhs.location)); }
#line 2856 "parser.cpp"
    break;

  case 89: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 538 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_begin::ptr > () = std::make_unique<ast::stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2862 "parser.cpp"
    break;

  case 90: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 543 "parser.ypp"
        { yylhs.value.as < ast::stmt_prof_end::ptr > () = std::make_unique<ast::stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ())); }
#line 2868 "parser.cpp"
    break;

  case 91: // expr: expr_ternary
#line 547 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2874 "parser.cpp"
    break;

  case 92: // expr: expr_binary
#line 548 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2880 "parser.cpp"
    break;

  case 93: // expr: expr_primitive
#line 549 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2886 "parser.cpp"
    break;

  case 94: // expr_or_empty: expr
#line 553 "parser.ypp"
                     { yylhs.value.as < ast::expr > () = std::move(yystack_[0].value.as < ast::expr > ()); }
#line 2892 "parser.cpp"
    break;

  case 95: // expr_or_empty: %empty
#line 554 "parser.ypp"
                     { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::node>(yylhs.location); }
#line 2898 "parser.cpp"
    break;

  case 96: // expr_assign: expr_object "=" expr
#line 559 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2904 "parser.cpp"
    break;

  case 97: // expr_assign: expr_object "|=" expr
#line 561 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2910 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object "&=" expr
#line 563 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2916 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "^=" expr
#line 565 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2922 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object "<<=" expr
#line 567 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()),std::move( yystack_[0].value.as < ast::expr > ())); }
#line 2928 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object ">>=" expr
#line 569 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2934 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "+=" expr
#line 571 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2940 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object "-=" expr
#line 573 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2946 "parser.cpp"
    break;

  case 104: // expr_assign: expr_object "*=" expr
#line 575 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2952 "parser.cpp"
    break;

  case 105: // expr_assign: expr_object "/=" expr
#line 577 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2958 "parser.cpp"
    break;

  case 106: // expr_assign: expr_object "%=" expr
#line 579 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2964 "parser.cpp"
    break;

  case 107: // expr_increment: "++" expr_object
#line 584 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2970 "parser.cpp"
    break;

  case 108: // expr_increment: expr_object "++"
#line 586 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_increment>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2976 "parser.cpp"
    break;

  case 109: // expr_decrement: "--" expr_object
#line 591 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ()), true); }
#line 2982 "parser.cpp"
    break;

  case 110: // expr_decrement: expr_object "--"
#line 593 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), false); }
#line 2988 "parser.cpp"
    break;

  case 111: // expr_ternary: expr "?" expr ":" expr
#line 598 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_ternary>(yylhs.location, std::move(yystack_[4].value.as < ast::expr > ()), std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 2994 "parser.cpp"
    break;

  case 112: // expr_binary: expr "||" expr
#line 603 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3000 "parser.cpp"
    break;

  case 113: // expr_binary: expr "&&" expr
#line 605 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3006 "parser.cpp"
    break;

  case 114: // expr_binary: expr "==" expr
#line 607 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_equality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3012 "parser.cpp"
    break;

  case 115: // expr_binary: expr "!=" expr
#line 609 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3018 "parser.cpp"
    break;

  case 116: // expr_binary: expr "<=" expr
#line 611 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3024 "parser.cpp"
    break;

  case 117: // expr_binary: expr ">=" expr
#line 613 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3030 "parser.cpp"
    break;

  case 118: // expr_binary: expr "<" expr
#line 615 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_less>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3036 "parser.cpp"
    break;

  case 119: // expr_binary: expr ">" expr
#line 617 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_greater>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3042 "parser.cpp"
    break;

  case 120: // expr_binary: expr "|" expr
#line 619 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3048 "parser.cpp"
    break;

  case 121: // expr_binary: expr "&" expr
#line 621 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3054 "parser.cpp"
    break;

  case 122: // expr_binary: expr "^" expr
#line 623 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3060 "parser.cpp"
    break;

  case 123: // expr_binary: expr "<<" expr
#line 625 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3066 "parser.cpp"
    break;

  case 124: // expr_binary: expr ">>" expr
#line 627 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3072 "parser.cpp"
    break;

  case 125: // expr_binary: expr "+" expr
#line 629 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_add>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3078 "parser.cpp"
    break;

  case 126: // expr_binary: expr "-" expr
#line 631 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_sub>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3084 "parser.cpp"
    break;

  case 127: // expr_binary: expr "*" expr
#line 633 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mul>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3090 "parser.cpp"
    break;

  case 128: // expr_binary: expr "/" expr
#line 635 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_div>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3096 "parser.cpp"
    break;

  case 129: // expr_binary: expr "%" expr
#line 637 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_mod>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3102 "parser.cpp"
    break;

  case 130: // expr_primitive: expr_complement
#line 641 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_complement::ptr > ()); }
#line 3108 "parser.cpp"
    break;

  case 131: // expr_primitive: expr_negate
#line 642 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_negate::ptr > ()); }
#line 3114 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_not
#line 643 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_not::ptr > ()); }
#line 3120 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_call
#line 644 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3126 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_method
#line 645 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3132 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_getnextarraykey
#line 646 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getnextarraykey::ptr > ()); }
#line 3138 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_getfirstarraykey
#line 647 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getfirstarraykey::ptr > ()); }
#line 3144 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_getdvarcoloralpha
#line 648 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcoloralpha::ptr > ()); }
#line 3150 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_getdvarcolorblue
#line 649 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorblue::ptr > ()); }
#line 3156 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_getdvarcolorgreen
#line 650 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorgreen::ptr > ()); }
#line 3162 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_getdvarcolorred
#line 651 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarcolorred::ptr > ()); }
#line 3168 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_getdvarvector
#line 652 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarvector::ptr > ()); }
#line 3174 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_getdvarfloat
#line 653 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarfloat::ptr > ()); }
#line 3180 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_getdvarint
#line 654 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvarint::ptr > ()); }
#line 3186 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_getdvar
#line 655 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_getdvar::ptr > ()); }
#line 3192 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_gettime
#line 656 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_gettime::ptr > ()); }
#line 3198 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_abs
#line 657 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_abs::ptr > ()); }
#line 3204 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_vectortoangles
#line 658 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vectortoangles::ptr > ()); }
#line 3210 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_angleclamp180
#line 659 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_angleclamp180::ptr > ()); }
#line 3216 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_anglestoforward
#line 660 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoforward::ptr > ()); }
#line 3222 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_anglestoright
#line 661 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoright::ptr > ()); }
#line 3228 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_anglestoup
#line 662 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anglestoup::ptr > ()); }
#line 3234 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_vectorscale
#line 663 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vectorscale::ptr > ()); }
#line 3240 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_isdefined
#line 664 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_isdefined::ptr > ()); }
#line 3246 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_reference
#line 665 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_reference::ptr > ()); }
#line 3252 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_array
#line 666 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3258 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_field
#line 667 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3264 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_size
#line 668 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_size::ptr > ()); }
#line 3270 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_paren
#line 669 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()); }
#line 3276 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_empty_array
#line 670 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_empty_array::ptr > ()); }
#line 3282 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_undefined
#line 671 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_undefined::ptr > ()); }
#line 3288 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_game
#line 672 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3294 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_self
#line 673 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3300 "parser.cpp"
    break;

  case 163: // expr_primitive: expr_anim
#line 674 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3306 "parser.cpp"
    break;

  case 164: // expr_primitive: expr_level
#line 675 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3312 "parser.cpp"
    break;

  case 165: // expr_primitive: expr_animation
#line 676 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animation::ptr > ()); }
#line 3318 "parser.cpp"
    break;

  case 166: // expr_primitive: expr_animtree
#line 677 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_animtree::ptr > ()); }
#line 3324 "parser.cpp"
    break;

  case 167: // expr_primitive: expr_identifier
#line 678 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3330 "parser.cpp"
    break;

  case 168: // expr_primitive: expr_istring
#line 679 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_istring::ptr > ()); }
#line 3336 "parser.cpp"
    break;

  case 169: // expr_primitive: expr_string
#line 680 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_string::ptr > ()); }
#line 3342 "parser.cpp"
    break;

  case 170: // expr_primitive: expr_vector
#line 681 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_vector::ptr > ()); }
#line 3348 "parser.cpp"
    break;

  case 171: // expr_primitive: expr_hash
#line 682 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_hash::ptr > ()); }
#line 3354 "parser.cpp"
    break;

  case 172: // expr_primitive: expr_float
#line 683 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_float::ptr > ()); }
#line 3360 "parser.cpp"
    break;

  case 173: // expr_primitive: expr_integer
#line 684 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_integer::ptr > ()); }
#line 3366 "parser.cpp"
    break;

  case 174: // expr_primitive: expr_false
#line 685 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_false::ptr > ()); }
#line 3372 "parser.cpp"
    break;

  case 175: // expr_primitive: expr_true
#line 686 "parser.ypp"
                             { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_true::ptr > ()); }
#line 3378 "parser.cpp"
    break;

  case 176: // expr_complement: "~" expr
#line 691 "parser.ypp"
        { yylhs.value.as < ast::expr_complement::ptr > () = std::make_unique<ast::expr_complement>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3384 "parser.cpp"
    break;

  case 177: // expr_negate: "-" expr_identifier
#line 696 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()))); }
#line 3390 "parser.cpp"
    break;

  case 178: // expr_negate: "-" expr_paren
#line 698 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_paren::ptr > ()))); }
#line 3396 "parser.cpp"
    break;

  case 179: // expr_negate: "-" expr_array
#line 700 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_array::ptr > ()))); }
#line 3402 "parser.cpp"
    break;

  case 180: // expr_negate: "-" expr_field
#line 702 "parser.ypp"
        { yylhs.value.as < ast::expr_negate::ptr > () = std::make_unique<ast::expr_negate>(yylhs.location, ast::expr(std::move(yystack_[0].value.as < ast::expr_field::ptr > ()))); }
#line 3408 "parser.cpp"
    break;

  case 181: // expr_not: "!" expr
#line 707 "parser.ypp"
        { yylhs.value.as < ast::expr_not::ptr > () = std::make_unique<ast::expr_not>(yylhs.location, std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3414 "parser.cpp"
    break;

  case 182: // expr_call: expr_function
#line 711 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3420 "parser.cpp"
    break;

  case 183: // expr_call: expr_pointer
#line 712 "parser.ypp"
                                   { yylhs.value.as < ast::expr_call::ptr > () = std::make_unique<ast::expr_call>(yylhs.location, std::move(yystack_[0].value.as < ast::call > ())); }
#line 3426 "parser.cpp"
    break;

  case 184: // expr_method: expr_object expr_function
#line 715 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3432 "parser.cpp"
    break;

  case 185: // expr_method: expr_object expr_pointer
#line 716 "parser.ypp"
                                   { yylhs.value.as < ast::expr_method::ptr > () = std::make_unique<ast::expr_method>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::call > ())); }
#line 3438 "parser.cpp"
    break;

  case 186: // expr_function: expr_identifier "(" expr_arguments ")"
#line 721 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3444 "parser.cpp"
    break;

  case 187: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 723 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3450 "parser.cpp"
    break;

  case 188: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 725 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3456 "parser.cpp"
    break;

  case 189: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 727 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_function = std::make_unique<ast::expr_function>(yylhs.location, std::move(yystack_[5].value.as < ast::expr_path::ptr > ()), std::move(yystack_[3].value.as < ast::expr_identifier::ptr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3462 "parser.cpp"
    break;

  case 190: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 732 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::normal); }
#line 3468 "parser.cpp"
    break;

  case 191: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 734 "parser.ypp"
        { yylhs.value.as < ast::call > ().as_pointer = std::make_unique<ast::expr_pointer>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr_arguments::ptr > ()), ast::call::mode::thread); }
#line 3474 "parser.cpp"
    break;

  case 192: // expr_parameters: expr_parameters "," expr_parameters_default
#line 739 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3480 "parser.cpp"
    break;

  case 193: // expr_parameters: expr_parameters "," expr_identifier
#line 741 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::move(yystack_[2].value.as < ast::expr_parameters::ptr > ()); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(ast::expr(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()))); }
#line 3486 "parser.cpp"
    break;

  case 194: // expr_parameters: expr_parameters_default
#line 743 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3492 "parser.cpp"
    break;

  case 195: // expr_parameters: expr_identifier
#line 745 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); yylhs.value.as < ast::expr_parameters::ptr > ()->list.push_back(ast::expr(std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()))); }
#line 3498 "parser.cpp"
    break;

  case 196: // expr_parameters: %empty
#line 747 "parser.ypp"
        { yylhs.value.as < ast::expr_parameters::ptr > () = std::make_unique<ast::expr_parameters>(yylhs.location); }
#line 3504 "parser.cpp"
    break;

  case 197: // expr_parameters_default: expr_identifier "=" expr
#line 752 "parser.ypp"
        { yylhs.value.as < ast::expr > ().as_node = std::make_unique<ast::expr_assign_equal>(yylhs.location, ast::expr(std::move(yystack_[2].value.as < ast::expr_identifier::ptr > ())), std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3510 "parser.cpp"
    break;

  case 198: // expr_arguments: expr_arguments_no_empty
#line 757 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[0].value.as < ast::expr_arguments::ptr > ()); }
#line 3516 "parser.cpp"
    break;

  case 199: // expr_arguments: %empty
#line 759 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); }
#line 3522 "parser.cpp"
    break;

  case 200: // expr_arguments_no_empty: expr_arguments "," expr
#line 764 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::move(yystack_[2].value.as < ast::expr_arguments::ptr > ()); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3528 "parser.cpp"
    break;

  case 201: // expr_arguments_no_empty: expr
#line 766 "parser.ypp"
        { yylhs.value.as < ast::expr_arguments::ptr > () = std::make_unique<ast::expr_arguments>(yylhs.location); yylhs.value.as < ast::expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < ast::expr > ())); }
#line 3534 "parser.cpp"
    break;

  case 202: // expr_getnextarraykey: "getnextarraykey" "(" expr "," expr ")"
#line 771 "parser.ypp"
        { yylhs.value.as < ast::expr_getnextarraykey::ptr > () = std::make_unique<ast::expr_getnextarraykey>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3540 "parser.cpp"
    break;

  case 203: // expr_getfirstarraykey: "getfirstarraykey" "(" expr ")"
#line 776 "parser.ypp"
        { yylhs.value.as < ast::expr_getfirstarraykey::ptr > () = std::make_unique<ast::expr_getfirstarraykey>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3546 "parser.cpp"
    break;

  case 204: // expr_getdvarcoloralpha: "getdvarcoloralpha" "(" expr ")"
#line 781 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcoloralpha::ptr > () = std::make_unique<ast::expr_getdvarcoloralpha>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3552 "parser.cpp"
    break;

  case 205: // expr_getdvarcolorblue: "getdvarcolorblue" "(" expr ")"
#line 786 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorblue::ptr > () = std::make_unique<ast::expr_getdvarcolorblue>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3558 "parser.cpp"
    break;

  case 206: // expr_getdvarcolorgreen: "getdvarcolorgreen" "(" expr ")"
#line 791 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorgreen::ptr > () = std::make_unique<ast::expr_getdvarcolorgreen>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3564 "parser.cpp"
    break;

  case 207: // expr_getdvarcolorred: "getdvarcolorred" "(" expr ")"
#line 796 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarcolorred::ptr > () = std::make_unique<ast::expr_getdvarcolorred>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3570 "parser.cpp"
    break;

  case 208: // expr_getdvarvector: "getdvarvector" "(" expr ")"
#line 801 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarvector::ptr > () = std::make_unique<ast::expr_getdvarvector>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3576 "parser.cpp"
    break;

  case 209: // expr_getdvarfloat: "getdvarfloat" "(" expr ")"
#line 806 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarfloat::ptr > () = std::make_unique<ast::expr_getdvarfloat>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3582 "parser.cpp"
    break;

  case 210: // expr_getdvarint: "getdvarint" "(" expr ")"
#line 811 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvarint::ptr > () = std::make_unique<ast::expr_getdvarint>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3588 "parser.cpp"
    break;

  case 211: // expr_getdvar: "getdvar" "(" expr ")"
#line 816 "parser.ypp"
        { yylhs.value.as < ast::expr_getdvar::ptr > () = std::make_unique<ast::expr_getdvar>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3594 "parser.cpp"
    break;

  case 212: // expr_gettime: "gettime" "(" ")"
#line 821 "parser.ypp"
        { yylhs.value.as < ast::expr_gettime::ptr > () = std::make_unique<ast::expr_gettime>(yylhs.location); }
#line 3600 "parser.cpp"
    break;

  case 213: // expr_abs: "abs" "(" expr ")"
#line 826 "parser.ypp"
        { yylhs.value.as < ast::expr_abs::ptr > () = std::make_unique<ast::expr_abs>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3606 "parser.cpp"
    break;

  case 214: // expr_vectortoangles: "vectortoangles" "(" expr ")"
#line 831 "parser.ypp"
        { yylhs.value.as < ast::expr_vectortoangles::ptr > () = std::make_unique<ast::expr_vectortoangles>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3612 "parser.cpp"
    break;

  case 215: // expr_angleclamp180: "angleclamp180" "(" expr ")"
#line 836 "parser.ypp"
        { yylhs.value.as < ast::expr_angleclamp180::ptr > () = std::make_unique<ast::expr_angleclamp180>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3618 "parser.cpp"
    break;

  case 216: // expr_anglestoforward: "anglestoforward" "(" expr ")"
#line 841 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoforward::ptr > () = std::make_unique<ast::expr_anglestoforward>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3624 "parser.cpp"
    break;

  case 217: // expr_anglestoright: "anglestoright" "(" expr ")"
#line 846 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoright::ptr > () = std::make_unique<ast::expr_anglestoright>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3630 "parser.cpp"
    break;

  case 218: // expr_anglestoup: "anglestoup" "(" expr ")"
#line 851 "parser.ypp"
        { yylhs.value.as < ast::expr_anglestoup::ptr > () = std::make_unique<ast::expr_anglestoup>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3636 "parser.cpp"
    break;

  case 219: // expr_vectorscale: "vectorscale" "(" expr "," expr ")"
#line 856 "parser.ypp"
        { yylhs.value.as < ast::expr_vectorscale::ptr > () = std::make_unique<ast::expr_vectorscale>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3642 "parser.cpp"
    break;

  case 220: // expr_isdefined: "isdefined" "(" expr ")"
#line 861 "parser.ypp"
        { yylhs.value.as < ast::expr_isdefined::ptr > () = std::make_unique<ast::expr_isdefined>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3648 "parser.cpp"
    break;

  case 221: // expr_reference: "::" expr_identifier
#line 866 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::make_unique<ast::expr_path>(yylhs.location), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3654 "parser.cpp"
    break;

  case 222: // expr_reference: expr_path "::" expr_identifier
#line 868 "parser.ypp"
        { yylhs.value.as < ast::expr_reference::ptr > () = std::make_unique<ast::expr_reference>(yylhs.location, std::move(yystack_[2].value.as < ast::expr_path::ptr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3660 "parser.cpp"
    break;

  case 223: // expr_array: expr_object "[" expr "]"
#line 873 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3666 "parser.cpp"
    break;

  case 224: // expr_array: expr_getdvarvector "[" expr "]"
#line 875 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_getdvarvector::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3672 "parser.cpp"
    break;

  case 225: // expr_array: expr_vectortoangles "[" expr "]"
#line 877 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_vectortoangles::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3678 "parser.cpp"
    break;

  case 226: // expr_array: expr_angleclamp180 "[" expr "]"
#line 879 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_angleclamp180::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3684 "parser.cpp"
    break;

  case 227: // expr_array: expr_anglestoforward "[" expr "]"
#line 881 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_anglestoforward::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3690 "parser.cpp"
    break;

  case 228: // expr_array: expr_anglestoright "[" expr "]"
#line 883 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_anglestoright::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3696 "parser.cpp"
    break;

  case 229: // expr_array: expr_anglestoup "[" expr "]"
#line 885 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_anglestoup::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3702 "parser.cpp"
    break;

  case 230: // expr_array: expr_vectorscale "[" expr "]"
#line 887 "parser.ypp"
        { yylhs.value.as < ast::expr_array::ptr > () = std::make_unique<ast::expr_array>(yylhs.location, ast::expr(std::move(yystack_[3].value.as < ast::expr_vectorscale::ptr > ())), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3708 "parser.cpp"
    break;

  case 231: // expr_field: expr_object "." expr_identifier_nosize
#line 892 "parser.ypp"
        { yylhs.value.as < ast::expr_field::ptr > () = std::make_unique<ast::expr_field>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ()), std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ())); }
#line 3714 "parser.cpp"
    break;

  case 232: // expr_size: expr_object "." "size"
#line 897 "parser.ypp"
        { yylhs.value.as < ast::expr_size::ptr > () = std::make_unique<ast::expr_size>(yylhs.location, std::move(yystack_[2].value.as < ast::expr > ())); }
#line 3720 "parser.cpp"
    break;

  case 233: // expr_paren: "(" expr ")"
#line 902 "parser.ypp"
        { yylhs.value.as < ast::expr_paren::ptr > () = std::make_unique<ast::expr_paren>(yylhs.location, std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3726 "parser.cpp"
    break;

  case 234: // expr_object: expr_call
#line 906 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_call::ptr > ()); }
#line 3732 "parser.cpp"
    break;

  case 235: // expr_object: expr_method
#line 907 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_method::ptr > ()); }
#line 3738 "parser.cpp"
    break;

  case 236: // expr_object: expr_array
#line 908 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_array::ptr > ()); }
#line 3744 "parser.cpp"
    break;

  case 237: // expr_object: expr_field
#line 909 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_field::ptr > ()); }
#line 3750 "parser.cpp"
    break;

  case 238: // expr_object: expr_game
#line 910 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_game::ptr > ()); }
#line 3756 "parser.cpp"
    break;

  case 239: // expr_object: expr_self
#line 911 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_self::ptr > ()); }
#line 3762 "parser.cpp"
    break;

  case 240: // expr_object: expr_anim
#line 912 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_anim::ptr > ()); }
#line 3768 "parser.cpp"
    break;

  case 241: // expr_object: expr_level
#line 913 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_level::ptr > ()); }
#line 3774 "parser.cpp"
    break;

  case 242: // expr_object: expr_identifier
#line 914 "parser.ypp"
                      { yylhs.value.as < ast::expr > ().as_node = std::move(yystack_[0].value.as < ast::expr_identifier::ptr > ()); }
#line 3780 "parser.cpp"
    break;

  case 243: // expr_empty_array: "[" "]"
#line 919 "parser.ypp"
        { yylhs.value.as < ast::expr_empty_array::ptr > () = std::make_unique<ast::expr_empty_array>(yylhs.location); }
#line 3786 "parser.cpp"
    break;

  case 244: // expr_undefined: "undefined"
#line 924 "parser.ypp"
        { yylhs.value.as < ast::expr_undefined::ptr > () = std::make_unique<ast::expr_undefined>(yylhs.location); }
#line 3792 "parser.cpp"
    break;

  case 245: // expr_game: "game"
#line 929 "parser.ypp"
        { yylhs.value.as < ast::expr_game::ptr > () = std::make_unique<ast::expr_game>(yylhs.location); }
#line 3798 "parser.cpp"
    break;

  case 246: // expr_self: "self"
#line 934 "parser.ypp"
        { yylhs.value.as < ast::expr_self::ptr > () = std::make_unique<ast::expr_self>(yylhs.location); }
#line 3804 "parser.cpp"
    break;

  case 247: // expr_anim: "anim"
#line 939 "parser.ypp"
        { yylhs.value.as < ast::expr_anim::ptr > () = std::make_unique<ast::expr_anim>(yylhs.location); }
#line 3810 "parser.cpp"
    break;

  case 248: // expr_level: "level"
#line 944 "parser.ypp"
        { yylhs.value.as < ast::expr_level::ptr > () = std::make_unique<ast::expr_level>(yylhs.location); }
#line 3816 "parser.cpp"
    break;

  case 249: // expr_animation: "%" "identifier"
#line 949 "parser.ypp"
        { yylhs.value.as < ast::expr_animation::ptr > () = std::make_unique<ast::expr_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3822 "parser.cpp"
    break;

  case 250: // expr_animtree: "#animtree"
#line 954 "parser.ypp"
        { yylhs.value.as < ast::expr_animtree::ptr > () = std::make_unique<ast::expr_animtree>(yylhs.location); }
#line 3828 "parser.cpp"
    break;

  case 251: // expr_identifier_nosize: "identifier"
#line 959 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3834 "parser.cpp"
    break;

  case 252: // expr_identifier: "identifier"
#line 964 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3840 "parser.cpp"
    break;

  case 253: // expr_identifier: "size"
#line 966 "parser.ypp"
        { yylhs.value.as < ast::expr_identifier::ptr > () = std::make_unique<ast::expr_identifier>(yylhs.location, "size"); }
#line 3846 "parser.cpp"
    break;

  case 254: // expr_path: "path" "/" "identifier"
#line 971 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[2].value.as < std::string > () + "/" + yystack_[0].value.as < std::string > ()); }
#line 3852 "parser.cpp"
    break;

  case 255: // expr_path: "identifier"
#line 973 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3858 "parser.cpp"
    break;

  case 256: // expr_path: "path"
#line 975 "parser.ypp"
        { yylhs.value.as < ast::expr_path::ptr > () = std::make_unique<ast::expr_path>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3864 "parser.cpp"
    break;

  case 257: // expr_istring: "localized string"
#line 980 "parser.ypp"
        { yylhs.value.as < ast::expr_istring::ptr > () = std::make_unique<ast::expr_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3870 "parser.cpp"
    break;

  case 258: // expr_string: "string literal"
#line 985 "parser.ypp"
        { yylhs.value.as < ast::expr_string::ptr > () = std::make_unique<ast::expr_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3876 "parser.cpp"
    break;

  case 259: // expr_vector: "(" expr "," expr "," expr ")"
#line 990 "parser.ypp"
        { yylhs.value.as < ast::expr_vector::ptr > () = std::make_unique<ast::expr_vector>(yylhs.location, std::move(yystack_[5].value.as < ast::expr > ()), std::move(yystack_[3].value.as < ast::expr > ()), std::move(yystack_[1].value.as < ast::expr > ())); }
#line 3882 "parser.cpp"
    break;

  case 260: // expr_hash: "hash"
#line 995 "parser.ypp"
        { yylhs.value.as < ast::expr_hash::ptr > () = std::make_unique<ast::expr_hash>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3888 "parser.cpp"
    break;

  case 261: // expr_float: "-" "float"
#line 1000 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3894 "parser.cpp"
    break;

  case 262: // expr_float: "float"
#line 1002 "parser.ypp"
        { yylhs.value.as < ast::expr_float::ptr > () = std::make_unique<ast::expr_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3900 "parser.cpp"
    break;

  case 263: // expr_integer: "-" "integer"
#line 1007 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3906 "parser.cpp"
    break;

  case 264: // expr_integer: "integer"
#line 1009 "parser.ypp"
        { yylhs.value.as < ast::expr_integer::ptr > () = std::make_unique<ast::expr_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3912 "parser.cpp"
    break;

  case 265: // expr_false: "false"
#line 1014 "parser.ypp"
        { yylhs.value.as < ast::expr_false::ptr > () = std::make_unique<ast::expr_false>(yylhs.location); }
#line 3918 "parser.cpp"
    break;

  case 266: // expr_true: "true"
#line 1019 "parser.ypp"
        { yylhs.value.as < ast::expr_true::ptr > () = std::make_unique<ast::expr_true>(yylhs.location); }
#line 3924 "parser.cpp"
    break;


#line 3928 "parser.cpp"

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
  "#include", "#using_animtree", "#animtree", "autoexec", "codecall",
  "private", "endon", "notify", "wait", "waittill", "waittillmatch",
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


  const short parser::yypact_ninf_ = -450;

  const short parser::yytable_ninf_ = -256;

  const short
  parser::yypact_[] =
  {
      33,  -450,  -450,   -82,   -82,   -68,   -28,   -28,   -28,  -450,
    -450,    18,    33,  -450,  -450,  -450,  -450,  -450,   -40,   -86,
    -450,   -27,   -23,   -77,   -11,     3,    27,  -450,  -450,  -450,
    -450,   -28,   -13,  -450,  -450,  -450,    46,   -28,   -28,   -28,
     -35,  -450,    26,  -450,    24,     4,     5,     6,    51,   -28,
    1421,  -450,    51,    51,    51,   928,  -450,  -450,    26,  -450,
     -10,  -450,  -450,  -450,  -450,  -450,  -450,  -450,    58,    60,
      62,    63,    65,    68,    71,    72,    82,    83,    85,    91,
      93,    95,   101,   104,   110,   111,   113,  1421,    19,   -28,
    1421,  1421,  1541,    74,    48,  -450,  -450,  -450,  -450,  3449,
    -450,  -450,  -450,  -450,  -450,  -450,    21,   137,  -450,  -450,
    -450,  -450,  -450,  -450,  -450,  -450,   121,  -450,  -450,  -450,
    -450,  -450,   123,   124,   125,   126,   128,   139,  -450,  -450,
     258,   295,  -450,  -450,   310,  -450,  -450,   312,   319,   399,
     519,  -450,  -450,   -16,   106,  -450,  -450,  -450,  -450,  -450,
    -450,  -450,  -450,  -450,  -450,  -450,  1602,  1421,   114,   145,
    1727,   148,   151,   152,   153,   -89,   146,   154,   156,   812,
     163,   167,   -28,  -450,   164,  1757,  1757,  -450,  -450,  1231,
    -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,
    -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,
    -450,  -450,  -450,  -450,  -450,   161,   168,   170,   176,   177,
     121,   123,   124,   125,   126,   128,   139,  -450,  -450,   992,
    -450,  -450,  -450,  -450,   172,   165,   173,   174,   182,  1421,
    1421,  1421,  1421,  1421,  1421,  1421,  1421,  1421,  1421,   192,
    1421,  1421,  1421,  1421,  1421,  1421,  1421,  1421,  1768,  1421,
    -450,  -450,  -450,  -450,  1421,  -450,  -450,  -450,  -450,   258,
     295,  -450,   530,   -16,  -450,  1421,  1421,  1421,  1421,  1421,
    1421,  1421,  1421,  1421,  1421,  1421,  1421,  1421,  1421,  1421,
    1421,  1421,  1421,  1421,  1421,  1421,  1421,  1421,  1421,  1421,
    1421,  1502,   -25,  -450,  -450,   172,  1421,   -28,  -450,  -450,
    1665,  3366,  -450,  1421,   238,  1421,  1261,   -28,  1421,   147,
     194,   197,  -450,  -450,  -450,  -450,  3401,  1421,  1421,   183,
     530,   530,  -450,  -450,  -450,  -450,  -450,  -450,  -450,   210,
     211,   212,   213,   171,  -450,  -450,  1421,  1421,  1421,  1421,
    1421,  1421,  1421,  1421,  1421,  1421,  1421,   -28,  1421,  1421,
     -28,  3217,  1934,  1968,  2002,  2036,  2070,  2104,  2138,  2172,
    2206,  -450,  2240,  2274,  2308,  2342,  2376,  2410,  3256,  2444,
    -450,  1421,  1417,  2478,  3331,    94,    94,  1100,  3480,   824,
     824,   510,   510,   510,   510,  3490,  3521,  1133,    55,    55,
    -450,  -450,  -450,  2858,  2898,  2938,  2978,  3018,  3058,  3098,
    1340,  3138,  -450,  -450,  -450,  3449,     8,  -450,   219,  -450,
    -450,  -450,  2512,   220,  2546,   214,  -450,  -450,  -450,   678,
      -8,  2580,  -450,  -450,  -450,    14,    25,  1421,  1421,  1421,
    1421,  1421,  3449,  3449,  3449,  3449,  3449,  3449,  3449,  3449,
    3449,  3449,  3449,   219,  3178,    36,   221,  1421,  -450,  -450,
    -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,
    -450,  -450,  -450,  1421,  -450,  3295,   217,  1421,  -450,  -450,
    -450,  -450,  -450,  -450,  -450,  -450,  -450,  1421,  1421,  1727,
    1421,  1727,  1421,  1421,   -28,    51,   216,   218,  3436,  2614,
    1812,  1856,  1900,   226,  -450,  1421,  2648,  2682,  1421,   223,
    3449,  3449,    39,   275,  2716,  -450,  3449,   224,  2750,   273,
    -450,  -450,  -450,  -450,   229,   231,  1421,   233,  1421,   234,
    1421,   245,    42,  -450,  -450,  2784,  1421,  -450,  1727,   239,
    1261,  1727,  1421,  -450,  -450,   248,   255,  -450,   256,  -450,
     262,  1421,  -450,  -450,    43,  -450,  -450,   263,  -450,  2818,
     259,   272,   274,    45,  -450,  1727,  1727,  -450,  -450,  -450,
    -450,  -450,  -450
  };

  const short
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,     0,     0,     0,   253,
     252,     0,     2,     7,     8,     9,    14,    15,     0,   256,
     255,     0,     0,     0,     0,     0,     0,     1,     4,     5,
       6,   196,     0,    10,    11,   258,     0,   196,   196,   196,
       0,   194,   195,   254,     0,     0,     0,     0,     0,     0,
       0,    16,     0,     0,     0,     0,    17,   192,   193,   250,
       0,   266,   265,   244,   245,   246,   247,   248,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   252,   257,   260,   262,   264,   197,
      91,    92,    93,   130,   131,   132,   133,   134,   182,   183,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,     0,   159,   160,   161,   162,   163,
     164,   165,   166,   167,     0,   168,   169,   170,   171,   172,
     173,   174,   175,    18,    19,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,     0,     0,     0,    45,    50,     0,
      46,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,     0,     0,     0,   234,   235,
       0,     0,     0,     0,     0,     0,     0,   236,   237,     0,
     238,   239,   240,   241,   242,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     243,   221,   181,   176,     0,   261,   263,   234,   235,   179,
     180,   178,     0,   177,   249,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   184,   185,     0,   199,     0,    52,    48,
       0,     0,    73,     0,     0,     0,    58,     0,     0,     0,
       0,     0,    84,    85,    86,    88,     0,   199,   199,     0,
     107,   109,    53,    49,    62,    63,    64,    59,    60,     0,
       0,     0,     0,     0,   108,   110,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   199,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   212,     0,     0,     0,     0,     0,     0,     0,     0,
     233,     0,     0,     0,     0,   123,   124,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   125,   126,
     127,   128,   129,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   232,   251,   231,   201,     0,   198,   222,    51,
      47,    68,     0,     0,     0,     0,    55,    56,    57,     0,
       0,     0,    83,    82,    87,     0,     0,     0,     0,     0,
       0,     0,    96,   102,   103,   104,   105,   106,    97,    98,
      99,   101,   100,     0,     0,     0,     0,     0,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   213,   214,   215,
     216,   217,   218,     0,   220,     0,     0,     0,   224,   225,
     226,   227,   228,   229,   230,   223,   186,     0,   199,     0,
       0,     0,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,   199,     0,     0,     0,     0,
     111,   200,     0,    74,     0,    76,    94,     0,     0,     0,
      81,    89,    90,    61,     0,     0,   199,     0,   199,     0,
     199,     0,     0,   202,   219,     0,   199,   187,     0,     0,
      58,     0,     0,    65,    67,     0,   198,    70,   198,    72,
     198,   199,   189,   259,     0,    75,    77,     0,    79,     0,
       0,     0,     0,     0,   190,     0,     0,    66,    69,    71,
     191,    78,    80
  };

  const short
  parser::yypgoto_[] =
  {
    -450,  -450,  -450,   316,   330,   331,  -450,  -450,   -73,   179,
    -450,  -450,  -450,   -43,  -169,  -450,  -450,  -450,  -450,  -450,
    -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,
    -450,  -450,  -450,  -450,  -450,  -450,  -450,  -450,   892,  -450,
    -302,  -291,  -290,  -450,  -450,  -450,  -450,  -450,  -450,   -36,
     -29,  -133,  -111,   120,   317,  -275,  -449,  -450,  -450,  -450,
    -450,  -450,  -450,    17,  -450,  -450,  -450,  -450,  -450,    56,
      70,    99,   109,   162,   169,  -450,  -450,   203,   257,  -450,
     276,   291,  -450,  -450,   357,   491,   527,   589,  -450,  -450,
    -450,     0,    10,  -450,   -20,  -450,  -450,  -450,   200,  -450,
    -450
  };

  const short
  parser::yydefgoto_[] =
  {
       0,    11,    12,    13,    14,    15,    16,    17,   177,   178,
     300,   179,   180,   181,   415,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   405,   507,
     205,   206,   207,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    40,    41,   535,   407,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     404,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152
  };

  const short
  parser::yytable_[] =
  {
      18,   293,    23,    36,   416,    56,    24,    25,    26,   153,
     154,   155,    18,    21,    22,   417,   418,     9,    27,   208,
     402,   406,   309,   294,   483,  -242,   209,    32,    35,  -242,
      31,    42,    98,    19,    20,     9,    48,    42,    42,    42,
      35,    49,   425,   426,     1,     2,     3,     4,     5,    58,
       6,     7,     8,    33,   296,   224,   257,    34,  -242,    37,
     227,  -242,  -234,   258,   226,   225,  -234,   536,   484,   538,
     228,   540,   210,    38,   445,    52,    53,    54,     9,   476,
      49,    49,    49,   299,   477,   486,   293,   304,    10,   251,
     477,   403,   263,   249,   250,  -234,   487,    39,  -234,  -242,
    -242,   477,   225,    43,    51,    19,    94,   494,   294,   210,
     527,   211,   477,   542,   554,   477,   560,    44,   477,   477,
     208,   477,    50,    55,   208,   212,  -255,   209,   229,   293,
     230,   209,   231,   232,   295,   233,  -234,  -234,   234,   257,
     257,   235,   236,   208,   225,   310,   258,   258,   211,    10,
     209,   294,   237,   238,   213,   239,   224,    45,    46,    47,
     224,   240,   212,   241,   214,   242,   225,   281,   282,   283,
     225,   243,   319,   210,   244,   224,   224,   210,  -235,   224,
     245,   246,  -235,   247,   297,   225,   225,   293,   293,   225,
     264,   213,   210,   210,   302,   284,   210,   285,   286,   287,
     288,   214,   289,   502,   279,   280,   281,   282,   283,   294,
     294,  -235,   211,   290,  -235,   303,   211,   215,   305,   295,
     522,   306,   307,   308,   216,   312,   212,   410,   416,   225,
     212,   211,   211,   317,   313,   211,   314,   318,   249,   417,
     418,   324,   296,   347,   349,   212,   212,   348,   325,   212,
     326,   544,  -235,  -235,   215,   213,   327,   328,   217,   213,
     350,   216,   295,   361,   208,   214,   553,   413,   256,   214,
     257,   209,   225,   422,   213,   213,   423,   258,   213,   427,
     428,   429,   430,   431,   214,   214,   293,   403,   214,   478,
     480,   495,   499,   526,   482,   259,   511,   408,   512,  -236,
     224,   521,   528,  -236,   530,   532,   224,   420,   294,   533,
     225,   534,   218,   537,   539,   541,   225,   210,   215,   546,
     295,   295,   215,   210,   477,   216,   550,   551,    28,   216,
     225,   225,  -236,   552,   555,  -236,  -237,   215,   215,   557,
    -237,   215,    29,    30,   216,   216,   219,   443,   216,   260,
     446,    60,   558,  -238,   559,     9,   211,  -238,   323,   217,
    -239,   547,   211,   217,  -239,   311,    57,     0,   261,  -237,
     212,     0,  -237,  -236,  -236,     0,   212,     0,   217,   217,
       0,     0,   217,   262,   291,     0,  -238,   292,     0,  -238,
       0,     0,     0,  -239,     0,     0,  -239,     0,     0,   213,
       0,     0,     0,     0,     0,   213,   503,     0,   505,   214,
    -237,  -237,   220,   218,     0,   214,     0,   218,     0,   295,
       0,     0,     0,     0,     0,    19,    94,  -238,  -238,   225,
       0,     0,   218,   218,  -239,  -239,   218,     0,     0,     0,
    -240,     0,   510,   208,  -240,   208,     0,   219,     0,   220,
     209,   219,   209,     0,     0,   545,     0,     0,   548,     0,
       0,     0,   215,     0,     0,     0,   320,   321,   215,   216,
     219,     0,     0,  -240,     0,   216,  -240,     0,     0,   224,
       0,   224,   561,   562,   509,     0,     0,     0,     0,   225,
       0,   225,   208,     0,   257,   208,   210,     0,   210,   209,
       0,   258,   209,   217,     0,     0,     0,     0,     0,   217,
       0,     0,     0,   220,  -240,  -240,     0,   220,     0,   208,
     208,     0,     0,     0,     0,     0,   209,   209,   224,     0,
     224,   224,   220,   220,     0,   211,   220,   211,   225,     0,
     225,   225,     0,     0,     0,   210,   221,   210,   210,   212,
       0,   212,     0,     0,     0,   224,   224,   218,     0,     0,
    -241,     0,     0,   218,  -241,   225,   225,     0,     0,     0,
       0,    60,   210,   210,     0,     9,     0,     0,   213,     0,
     213,     0,   222,   221,   211,     0,   211,   211,   214,     0,
     214,   219,     0,  -241,   266,   267,  -241,   419,   212,     0,
     212,   212,     0,     0,   291,     0,     0,   333,     0,     0,
       0,   211,   211,     0,     0,     0,     0,     0,     0,   222,
     279,   280,   281,   282,   283,   212,   212,   213,     0,   213,
     213,     0,     0,     0,  -241,  -241,     0,   214,     0,   214,
     214,   215,     0,   215,   223,    19,    94,   221,   216,     0,
     216,   221,     0,     0,   213,   213,     0,   220,     0,     0,
       0,     0,     0,   220,   214,   214,   221,   221,     0,     0,
     221,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   223,   217,   222,   217,     0,     0,   222,     0,     0,
     215,     0,   215,   215,     0,     0,     0,   216,     0,   216,
     216,     0,   222,   222,     0,     0,   222,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,   215,    60,
       0,     0,     0,     9,   216,   216,     0,     0,     0,     0,
       0,   217,     0,   217,   217,     0,   218,     0,   218,     0,
       0,     0,     0,     0,     0,   223,     0,     0,     0,   223,
       0,     0,   291,     0,     0,   333,     0,     0,   217,   217,
     334,   335,     0,     0,   223,   223,     0,     0,   223,     0,
     219,     0,   219,     0,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   218,     0,   218,   218,     0,
       0,   221,     0,    19,    94,     0,     0,   221,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   218,   218,     0,     0,     0,     0,     0,   219,
       0,   419,   219,     0,     0,     0,     0,   222,    59,     0,
       0,     0,     0,   222,     0,     0,   220,     0,   220,     0,
       0,     0,     0,     0,     0,     0,   219,   219,     0,     0,
       0,     0,     0,    60,    61,    62,    63,     9,    64,    65,
      66,    67,     0,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,     0,     0,   220,    88,   220,   220,   223,
      89,     0,   315,     0,     0,   223,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    90,    91,   266,   267,
       0,     0,   220,   220,   272,   273,   274,   275,     0,     0,
       0,     0,     0,    92,     0,     0,    93,    19,    94,    35,
      95,    96,    97,    98,   279,   280,   281,   282,   283,   156,
       0,     0,    99,     0,     0,     0,     0,     0,     0,     0,
     157,     0,     0,   158,   159,     0,   160,   161,   162,   163,
       0,   164,   165,   166,   167,   168,   169,   170,   171,    60,
     221,     0,   221,     9,    64,    65,    66,    67,   172,   248,
       0,     0,   252,   253,     0,    74,     0,     0,     0,     0,
       0,    80,    81,    82,    83,    84,    85,     0,     0,     0,
      55,   173,   174,     0,     0,     0,   222,     0,   222,     0,
     175,   176,   329,   330,     0,   331,   332,     0,     0,   221,
       0,   221,   221,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,     0,     0,     0,     9,     0,     0,
       0,     0,     0,    19,    94,     0,   221,   221,     0,   301,
       0,     0,     0,     0,     0,   222,     0,   222,   222,     0,
       0,   316,     0,     0,     0,     0,   291,     0,   223,   333,
     223,     0,     0,     0,   334,   335,     0,     0,     0,     0,
       0,     0,   222,   222,     0,     0,     0,     0,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,     0,
       0,     0,     0,     0,     0,     0,     0,    19,    94,     0,
       0,     0,     0,     0,     0,     0,     0,   223,     0,   223,
     223,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,     0,   362,   363,   364,   365,   366,   367,   368,   369,
       0,   372,     0,     0,   223,   223,   373,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   374,   375,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   401,   266,   267,     0,   269,   270,   271,
     272,   273,   274,   275,     0,   412,     0,   414,     0,     0,
     421,     0,     0,     0,     0,     0,     0,   276,   277,   278,
     279,   280,   281,   282,   283,     0,     0,   266,   267,     0,
       0,   270,   271,   272,   273,   274,   275,     0,   432,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,     0,
     444,   277,   156,   279,   280,   281,   282,   283,     0,     0,
       0,     0,     0,   157,     0,     0,   158,   159,     0,   160,
     161,   162,   163,   465,   164,   165,   166,   167,   168,   169,
     170,   171,    60,     0,     0,     0,     9,    64,    65,    66,
      67,   172,     0,     0,     0,     0,     0,     0,    74,     0,
       0,     0,   372,     0,    80,    81,    82,    83,    84,    85,
       0,     0,    60,    55,   322,   174,     9,    64,    65,    66,
      67,     0,     0,   175,   176,     0,     0,     0,    74,   488,
     489,   490,   491,   492,    80,    81,    82,    83,    84,    85,
       0,     0,     0,     0,     0,   174,     0,     0,     0,   496,
       0,     0,     0,   175,   176,     0,    19,    94,     0,     0,
       0,     0,     0,     0,     0,   497,    59,     0,     0,   500,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   501,
       0,     0,   504,     0,   506,   508,    19,    94,     0,     0,
       0,    60,    61,    62,    63,     9,    64,    65,    66,    67,
     525,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     0,     0,     0,   400,   250,     0,     0,    89,     0,
       0,     0,     0,     0,   549,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    90,    91,     0,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    92,     0,     0,    93,    19,    94,    35,    95,    96,
      97,    98,    60,    61,    62,    63,     9,    64,    65,    66,
      67,     0,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,   466,     0,     0,    88,     0,     0,   265,    89,
       0,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,     0,     0,     0,     0,    90,    91,     0,    59,     0,
       0,     0,     0,     0,   276,   277,   278,   279,   280,   281,
     282,   283,    92,     0,     0,    93,    19,    94,    35,    95,
      96,    97,    98,    60,    61,    62,    63,     9,    64,    65,
      66,    67,     0,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,     0,     0,     0,   400,     0,     0,     0,
      89,     0,    60,     0,     0,     0,     9,    64,    65,    66,
      67,     0,     0,     0,     0,     0,    90,    91,    74,     0,
       0,     0,     0,     0,    80,    81,    82,    83,    84,    85,
       0,   254,     0,    92,   298,   174,    93,    19,    94,    35,
      95,    96,    97,    98,   157,     0,     0,   158,   159,     0,
     160,   161,   162,   163,     0,   164,   165,   166,   167,   168,
     169,   170,   171,    60,     0,     0,     0,     9,    64,    65,
      66,    67,   172,     0,     0,     0,    19,    94,     0,    74,
       0,   255,   256,     0,     0,    80,    81,    82,    83,    84,
      85,     0,     0,     0,    55,     0,   174,   409,     0,     0,
       0,     0,     0,     0,   175,   176,     0,   157,     0,     0,
     158,   159,     0,   160,   161,   162,   163,     0,   164,   165,
     166,   167,   168,   169,   170,   171,    60,     0,     0,     0,
       9,    64,    65,    66,    67,   172,     0,    19,    94,     0,
       0,     0,    74,     0,     0,     0,     0,     0,    80,    81,
      82,    83,    84,    85,     0,     0,     0,    55,     0,   174,
       0,     0,     0,     0,     0,     0,     0,   175,   176,   157,
       0,     0,   158,   159,     0,   160,   161,   162,   163,     0,
     164,   165,   166,   167,   168,   169,   170,   171,    60,     0,
       0,     0,     9,    64,    65,    66,    67,   172,     0,     0,
      19,    94,     0,     0,    74,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,     0,     0,    60,    55,
       0,   174,     9,    64,    65,    66,    67,     0,     0,   175,
     176,     0,     0,     0,    74,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,     0,     0,     0,     0,
       0,   174,     0,     0,     0,     0,     0,     0,     0,   370,
       0,     0,    19,    94,   371,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,    94,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   515,     0,     0,     0,     0,   516,     0,
       0,     0,     0,   265,     0,     0,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   276,
     277,   278,   279,   280,   281,   282,   283,   517,     0,     0,
       0,     0,   518,     0,     0,     0,     0,   265,     0,     0,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   276,   277,   278,   279,   280,   281,   282,
     283,   519,     0,     0,     0,     0,   520,     0,     0,     0,
       0,   265,     0,     0,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   448,     0,   276,   277,   278,
     279,   280,   281,   282,   283,   265,     0,     0,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   449,
       0,   276,   277,   278,   279,   280,   281,   282,   283,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   450,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   265,     0,     0,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   451,     0,   276,
     277,   278,   279,   280,   281,   282,   283,   265,     0,     0,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   452,     0,   276,   277,   278,   279,   280,   281,   282,
     283,   265,     0,     0,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   453,     0,   276,   277,   278,
     279,   280,   281,   282,   283,   265,     0,     0,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   454,
       0,   276,   277,   278,   279,   280,   281,   282,   283,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   455,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   265,     0,     0,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   456,     0,   276,
     277,   278,   279,   280,   281,   282,   283,   265,     0,     0,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   457,     0,   276,   277,   278,   279,   280,   281,   282,
     283,   265,     0,     0,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   458,     0,   276,   277,   278,
     279,   280,   281,   282,   283,   265,     0,     0,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   459,
       0,   276,   277,   278,   279,   280,   281,   282,   283,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   460,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   265,     0,     0,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   461,     0,   276,
     277,   278,   279,   280,   281,   282,   283,   265,     0,     0,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   462,     0,   276,   277,   278,   279,   280,   281,   282,
     283,   265,     0,     0,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   464,     0,   276,   277,   278,
     279,   280,   281,   282,   283,   265,     0,     0,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   370,
       0,   276,   277,   278,   279,   280,   281,   282,   283,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   479,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   265,     0,     0,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   481,     0,   276,
     277,   278,   279,   280,   281,   282,   283,   265,     0,     0,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   485,     0,   276,   277,   278,   279,   280,   281,   282,
     283,   265,     0,     0,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   514,     0,   276,   277,   278,
     279,   280,   281,   282,   283,   265,     0,     0,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   523,
       0,   276,   277,   278,   279,   280,   281,   282,   283,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   524,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   265,     0,     0,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   529,     0,   276,
     277,   278,   279,   280,   281,   282,   283,   265,     0,     0,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   531,     0,   276,   277,   278,   279,   280,   281,   282,
     283,   265,     0,     0,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   543,     0,   276,   277,   278,
     279,   280,   281,   282,   283,   265,     0,     0,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   556,
       0,   276,   277,   278,   279,   280,   281,   282,   283,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   468,     0,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   469,     0,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   470,     0,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   471,     0,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   472,     0,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   473,     0,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   474,     0,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   475,     0,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   493,     0,     0,     0,     0,     0,   265,
       0,     0,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,   277,   278,   279,   280,
     281,   282,   283,   447,     0,     0,     0,     0,   265,     0,
       0,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   276,   277,   278,   279,   280,   281,
     282,   283,   463,     0,     0,     0,     0,   265,     0,     0,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   276,   277,   278,   279,   280,   281,   282,
     283,   498,     0,     0,     0,     0,   265,     0,     0,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   276,   277,   278,   279,   280,   281,   282,   283,
     467,     0,   265,     0,     0,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   276,   277,
     278,   279,   280,   281,   282,   283,   411,   265,     0,     0,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   276,   277,   278,   279,   280,   281,   282,
     283,   424,   265,     0,     0,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   276,   277,
     278,   279,   280,   281,   282,   283,   513,   265,     0,     0,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     265,     0,     0,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,     0,     0,     0,     0,     0,   276,   277,   278,   279,
     280,   281,   282,   283,   266,   267,     0,     0,   270,   271,
     272,   273,   274,   275,   266,   267,     0,     0,   270,   271,
     272,   273,   274,   275,     0,     0,     0,   276,   277,   278,
     279,   280,   281,   282,   283,     0,     0,     0,   277,   278,
     279,   280,   281,   282,   283,   266,   267,     0,     0,   270,
     271,   272,   273,   274,   275,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   279,   280,   281,   282,   283
  };

  const short
  parser::yycheck_[] =
  {
       0,   134,    70,    23,   306,    48,     6,     7,     8,    52,
      53,    54,    12,     3,     4,   306,   306,    45,     0,    55,
      45,   296,   111,   134,    32,    41,    55,   113,   117,    45,
      70,    31,   121,   115,   116,    45,    71,    37,    38,    39,
     117,    76,   317,   318,    11,    12,    13,    14,    15,    49,
      17,    18,    19,    80,    70,    55,    92,    80,    74,    70,
      60,    77,    41,    92,    74,    55,    45,   516,    76,   518,
      60,   520,    55,    70,   349,    71,    71,    71,    45,    71,
      76,    76,    76,   156,    76,    71,   219,   160,   116,    89,
      76,   116,    92,    74,    75,    74,    71,    70,    77,   115,
     116,    76,    92,   116,    80,   115,   116,    71,   219,    92,
      71,    55,    76,    71,    71,    76,    71,    71,    76,    76,
     156,    76,    96,    72,   160,    55,    78,   156,    70,   262,
      70,   160,    70,    70,   134,    70,   115,   116,    70,   175,
     176,    70,    70,   179,   134,   165,   175,   176,    92,   116,
     179,   262,    70,    70,    55,    70,   156,    37,    38,    39,
     160,    70,    92,    70,    55,    70,   156,   112,   113,   114,
     160,    70,   172,   156,    70,   175,   176,   160,    41,   179,
      70,    70,    45,    70,    78,   175,   176,   320,   321,   179,
     116,    92,   175,   176,    80,    74,   179,    74,    74,    74,
      74,    92,    74,   478,   110,   111,   112,   113,   114,   320,
     321,    74,   156,    74,    77,    70,   160,    55,    70,   219,
     495,    70,    70,    70,    55,    79,   156,   300,   530,   219,
     160,   175,   176,    70,    80,   179,    80,    70,    74,   530,
     530,    80,    70,    78,    70,   175,   176,    74,    80,   179,
      80,   526,   115,   116,    92,   156,    80,    80,    55,   160,
      78,    92,   262,    71,   300,   156,   541,    29,   121,   160,
     306,   300,   262,    79,   175,   176,    79,   306,   179,    96,
      70,    70,    70,    70,   175,   176,   419,   116,   179,    70,
      70,    70,    75,    70,    80,    92,    80,   297,    80,    41,
     300,    75,    27,    45,    80,    32,   306,   307,   419,    80,
     300,    80,    55,    80,    80,    70,   306,   300,   156,    80,
     320,   321,   160,   306,    76,   156,    71,    71,    12,   160,
     320,   321,    74,    71,    71,    77,    41,   175,   176,    80,
      45,   179,    12,    12,   175,   176,    55,   347,   179,    92,
     350,    41,    80,    41,    80,    45,   300,    45,   179,   156,
      41,   530,   306,   160,    45,   165,    49,    -1,    92,    74,
     300,    -1,    77,   115,   116,    -1,   306,    -1,   175,   176,
      -1,    -1,   179,    92,    74,    -1,    74,    77,    -1,    77,
      -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    -1,   300,
      -1,    -1,    -1,    -1,    -1,   306,   479,    -1,   481,   300,
     115,   116,    55,   156,    -1,   306,    -1,   160,    -1,   419,
      -1,    -1,    -1,    -1,    -1,   115,   116,   115,   116,   419,
      -1,    -1,   175,   176,   115,   116,   179,    -1,    -1,    -1,
      41,    -1,   485,   479,    45,   481,    -1,   156,    -1,    92,
     479,   160,   481,    -1,    -1,   528,    -1,    -1,   531,    -1,
      -1,    -1,   300,    -1,    -1,    -1,   175,   176,   306,   300,
     179,    -1,    -1,    74,    -1,   306,    77,    -1,    -1,   479,
      -1,   481,   555,   556,   484,    -1,    -1,    -1,    -1,   479,
      -1,   481,   528,    -1,   530,   531,   479,    -1,   481,   528,
      -1,   530,   531,   300,    -1,    -1,    -1,    -1,    -1,   306,
      -1,    -1,    -1,   156,   115,   116,    -1,   160,    -1,   555,
     556,    -1,    -1,    -1,    -1,    -1,   555,   556,   528,    -1,
     530,   531,   175,   176,    -1,   479,   179,   481,   528,    -1,
     530,   531,    -1,    -1,    -1,   528,    55,   530,   531,   479,
      -1,   481,    -1,    -1,    -1,   555,   556,   300,    -1,    -1,
      41,    -1,    -1,   306,    45,   555,   556,    -1,    -1,    -1,
      -1,    41,   555,   556,    -1,    45,    -1,    -1,   479,    -1,
     481,    -1,    55,    92,   528,    -1,   530,   531,   479,    -1,
     481,   300,    -1,    74,    84,    85,    77,   306,   528,    -1,
     530,   531,    -1,    -1,    74,    -1,    -1,    77,    -1,    -1,
      -1,   555,   556,    -1,    -1,    -1,    -1,    -1,    -1,    92,
     110,   111,   112,   113,   114,   555,   556,   528,    -1,   530,
     531,    -1,    -1,    -1,   115,   116,    -1,   528,    -1,   530,
     531,   479,    -1,   481,    55,   115,   116,   156,   479,    -1,
     481,   160,    -1,    -1,   555,   556,    -1,   300,    -1,    -1,
      -1,    -1,    -1,   306,   555,   556,   175,   176,    -1,    -1,
     179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    92,   479,   156,   481,    -1,    -1,   160,    -1,    -1,
     528,    -1,   530,   531,    -1,    -1,    -1,   528,    -1,   530,
     531,    -1,   175,   176,    -1,    -1,   179,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   555,   556,    41,
      -1,    -1,    -1,    45,   555,   556,    -1,    -1,    -1,    -1,
      -1,   528,    -1,   530,   531,    -1,   479,    -1,   481,    -1,
      -1,    -1,    -1,    -1,    -1,   156,    -1,    -1,    -1,   160,
      -1,    -1,    74,    -1,    -1,    77,    -1,    -1,   555,   556,
      82,    83,    -1,    -1,   175,   176,    -1,    -1,   179,    -1,
     479,    -1,   481,    -1,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   528,    -1,   530,   531,    -1,
      -1,   300,    -1,   115,   116,    -1,    -1,   306,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   555,   556,    -1,    -1,    -1,    -1,    -1,   528,
      -1,   530,   531,    -1,    -1,    -1,    -1,   300,    16,    -1,
      -1,    -1,    -1,   306,    -1,    -1,   479,    -1,   481,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   555,   556,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,   528,    74,   530,   531,   300,
      78,    -1,    80,    -1,    -1,   306,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    84,    85,
      -1,    -1,   555,   556,    90,    91,    92,    93,    -1,    -1,
      -1,    -1,    -1,   111,    -1,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   110,   111,   112,   113,   114,    11,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    -1,    28,    29,    30,    31,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
     479,    -1,   481,    45,    46,    47,    48,    49,    50,    87,
      -1,    -1,    90,    91,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,   479,    -1,   481,    -1,
      82,    83,    20,    21,    -1,    23,    24,    -1,    -1,   528,
      -1,   530,   531,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,   115,   116,    -1,   555,   556,    -1,   157,
      -1,    -1,    -1,    -1,    -1,   528,    -1,   530,   531,    -1,
      -1,   169,    -1,    -1,    -1,    -1,    74,    -1,   479,    77,
     481,    -1,    -1,    -1,    82,    83,    -1,    -1,    -1,    -1,
      -1,    -1,   555,   556,    -1,    -1,    -1,    -1,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,   116,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   528,    -1,   530,
     531,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,    -1,   240,   241,   242,   243,   244,   245,   246,   247,
      -1,   249,    -1,    -1,   555,   556,   254,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,    84,    85,    -1,    87,    88,    89,
      90,    91,    92,    93,    -1,   303,    -1,   305,    -1,    -1,
     308,    -1,    -1,    -1,    -1,    -1,    -1,   107,   108,   109,
     110,   111,   112,   113,   114,    -1,    -1,    84,    85,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,    -1,
     348,   108,    11,   110,   111,   112,   113,   114,    -1,    -1,
      -1,    -1,    -1,    22,    -1,    -1,    25,    26,    -1,    28,
      29,    30,    31,   371,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,   400,    -1,    63,    64,    65,    66,    67,    68,
      -1,    -1,    41,    72,    73,    74,    45,    46,    47,    48,
      49,    -1,    -1,    82,    83,    -1,    -1,    -1,    57,   427,
     428,   429,   430,   431,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,   447,
      -1,    -1,    -1,    82,    83,    -1,   115,   116,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   463,    16,    -1,    -1,   467,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   477,
      -1,    -1,   480,    -1,   482,   483,   115,   116,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
     498,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    74,    75,    -1,    -1,    78,    -1,
      -1,    -1,    -1,    -1,   532,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   111,    -1,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    75,    -1,    -1,    74,    -1,    -1,    81,    78,
      -1,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    -1,    -1,    -1,    -1,    94,    95,    -1,    16,    -1,
      -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,   112,
     113,   114,   111,    -1,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      78,    -1,    41,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    94,    95,    57,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,    68,
      -1,    70,    -1,   111,    12,    74,   114,   115,   116,   117,
     118,   119,   120,   121,    22,    -1,    -1,    25,    26,    -1,
      28,    29,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,   115,   116,    -1,    57,
      -1,   120,   121,    -1,    -1,    63,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    72,    -1,    74,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    82,    83,    -1,    22,    -1,    -1,
      25,    26,    -1,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    -1,   115,   116,    -1,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    -1,    -1,    -1,    72,    -1,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    83,    22,
      -1,    -1,    25,    26,    -1,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    -1,    -1,
     115,   116,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    -1,    -1,    41,    72,
      -1,    74,    45,    46,    47,    48,    49,    -1,    -1,    82,
      83,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    -1,   115,   116,    76,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   115,   116,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    71,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    81,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,
     108,   109,   110,   111,   112,   113,   114,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   107,   108,   109,   110,   111,   112,   113,
     114,    71,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,   107,   108,   109,
     110,   111,   112,   113,   114,    81,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,   107,   108,   109,   110,   111,   112,   113,   114,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    81,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,   107,
     108,   109,   110,   111,   112,   113,   114,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,   107,   108,   109,   110,   111,   112,   113,
     114,    81,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,   107,   108,   109,
     110,   111,   112,   113,   114,    81,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,   107,   108,   109,   110,   111,   112,   113,   114,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    81,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,   107,
     108,   109,   110,   111,   112,   113,   114,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,   107,   108,   109,   110,   111,   112,   113,
     114,    81,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,   107,   108,   109,
     110,   111,   112,   113,   114,    81,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,   107,   108,   109,   110,   111,   112,   113,   114,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    81,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,   107,
     108,   109,   110,   111,   112,   113,   114,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,   107,   108,   109,   110,   111,   112,   113,
     114,    81,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,   107,   108,   109,
     110,   111,   112,   113,   114,    81,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,   107,   108,   109,   110,   111,   112,   113,   114,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    81,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,   107,
     108,   109,   110,   111,   112,   113,   114,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,   107,   108,   109,   110,   111,   112,   113,
     114,    81,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,   107,   108,   109,
     110,   111,   112,   113,   114,    81,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,   107,   108,   109,   110,   111,   112,   113,   114,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    81,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,   107,
     108,   109,   110,   111,   112,   113,   114,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,   107,   108,   109,   110,   111,   112,   113,
     114,    81,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,   107,   108,   109,
     110,   111,   112,   113,   114,    81,    -1,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,   107,   108,   109,   110,   111,   112,   113,   114,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,
     112,   113,   114,    76,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   107,   108,   109,   110,   111,   112,
     113,   114,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   107,   108,   109,   110,   111,   112,   113,
     114,    76,    -1,    -1,    -1,    -1,    81,    -1,    -1,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   107,   108,   109,   110,   111,   112,   113,   114,
      79,    -1,    81,    -1,    -1,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,   108,
     109,   110,   111,   112,   113,   114,    80,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   107,   108,   109,   110,   111,   112,   113,
     114,    80,    81,    -1,    -1,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   107,   108,
     109,   110,   111,   112,   113,   114,    80,    81,    -1,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      81,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,   107,   108,   109,   110,   111,   112,   113,
     114,    -1,    -1,    -1,    -1,    -1,   107,   108,   109,   110,
     111,   112,   113,   114,    84,    85,    -1,    -1,    88,    89,
      90,    91,    92,    93,    84,    85,    -1,    -1,    88,    89,
      90,    91,    92,    93,    -1,    -1,    -1,   107,   108,   109,
     110,   111,   112,   113,   114,    -1,    -1,    -1,   108,   109,
     110,   111,   112,   113,   114,    84,    85,    -1,    -1,    88,
      89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   110,   111,   112,   113,   114
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    11,    12,    13,    14,    15,    17,    18,    19,    45,
     116,   132,   133,   134,   135,   136,   137,   138,   222,   115,
     116,   223,   223,    70,   222,   222,   222,     0,   134,   135,
     136,    70,   113,    80,    80,   117,   225,    70,    70,    70,
     184,   185,   222,   116,    71,   184,   184,   184,    71,    76,
      96,    80,    71,    71,    71,    72,   144,   185,   222,    16,
      41,    42,    43,    44,    46,    47,    48,    49,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    74,    78,
      94,    95,   111,   114,   116,   118,   119,   120,   121,   169,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   144,   144,   144,    11,    22,    25,    26,
      28,    29,    30,    31,    33,    34,    35,    36,    37,    38,
      39,    40,    50,    73,    74,    82,    83,   139,   140,   142,
     143,   144,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   171,   172,   173,   180,   181,
     194,   200,   201,   202,   203,   204,   205,   208,   209,   212,
     215,   216,   217,   218,   222,   223,    74,   222,   223,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,   169,    74,
      75,   222,   169,   169,    70,   120,   121,   180,   181,   208,
     209,   211,   212,   222,   116,    81,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,   107,   108,   109,   110,
     111,   112,   113,   114,    74,    74,    74,    74,    74,    74,
      74,    74,    77,   182,   183,   222,    70,    78,    12,   139,
     141,   169,    80,    70,   139,    70,    70,    70,    70,   111,
     225,   229,    79,    80,    80,    80,   169,    70,    70,   222,
     212,   212,    73,   140,    80,    80,    80,    80,    80,    20,
      21,    23,    24,    77,    82,    83,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    78,    74,    70,
      78,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,    71,   169,   169,   169,   169,   169,   169,   169,   169,
      71,    76,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
      74,   169,    45,   116,   221,   169,   186,   187,   222,    12,
     139,    80,   169,    29,   169,   145,   171,   172,   173,   212,
     222,   169,    79,    79,    80,   186,   186,    96,    70,    70,
      70,    70,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   222,   169,   186,   222,    76,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    76,    71,   169,    75,    79,    75,    75,
      75,    75,    75,    75,    75,    75,    71,    76,    70,    71,
      70,    71,    80,    32,    76,    71,    71,    71,   169,   169,
     169,   169,   169,    75,    71,    70,   169,   169,    76,    75,
     169,   169,   186,   139,   169,   139,   169,   170,   169,   222,
     144,    80,    80,    80,    71,    71,    76,    71,    76,    71,
      76,    75,   186,    71,    71,   169,    70,    71,    27,    71,
      80,    71,    32,    80,    80,   186,   187,    80,   187,    80,
     187,    70,    71,    71,   186,   139,    80,   145,   139,   169,
      71,    71,    71,   186,    71,    71,    71,    80,    80,    80,
      71,   139,   139
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   131,   132,   132,   133,   133,   133,   133,   133,   133,
     134,   135,   136,   136,   136,   136,   137,   138,   138,   138,
     138,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   140,   140,   141,   141,   142,
     142,   143,   143,   144,   144,   145,   145,   145,   145,   146,
     146,   147,   148,   148,   148,   149,   150,   150,   151,   152,
     152,   153,   153,   154,   155,   156,   157,   158,   159,   160,
     160,   161,   162,   162,   163,   164,   165,   166,   166,   167,
     168,   169,   169,   169,   170,   170,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   172,   172,   173,
     173,   174,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   177,   178,   178,   178,
     178,   179,   180,   180,   181,   181,   182,   182,   182,   182,
     183,   183,   184,   184,   184,   184,   184,   185,   186,   186,
     187,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   207,   208,   208,   208,   208,   208,   208,   208,
     208,   209,   210,   211,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   222,   223,   223,   223,   224,   225,   226,
     227,   228,   228,   229,   229,   230,   231
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     5,     5,     6,     6,
       6,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     3,     2,     3,     2,     1,     1,     1,     0,     2,
       2,     5,     2,     2,     2,     6,     8,     6,     3,     8,
       6,     8,     6,     2,     5,     7,     5,     7,     9,     7,
       9,     5,     3,     3,     2,     2,     2,     3,     2,     5,
       5,     1,     1,     1,     1,     0,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     1,     1,     2,     2,     4,     6,     5,     7,
       8,     9,     3,     3,     1,     1,     0,     3,     1,     0,
       3,     1,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,     4,     4,     4,     4,     4,     4,     6,
       4,     2,     3,     4,     4,     4,     4,     4,     4,     4,
       4,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     7,
       1,     2,     1,     2,     1,     1,     1
  };




#if T6DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   295,   295,   296,   300,   302,   304,   306,   308,   310,
     315,   319,   324,   325,   326,   327,   331,   336,   338,   340,
     342,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   374,   375,   379,   381,   386,
     388,   393,   394,   398,   399,   403,   405,   407,   410,   414,
     416,   421,   426,   428,   430,   435,   440,   442,   447,   452,
     454,   459,   461,   466,   471,   476,   481,   486,   491,   496,
     498,   503,   508,   510,   515,   520,   525,   530,   532,   537,
     542,   547,   548,   549,   553,   554,   558,   560,   562,   564,
     566,   568,   570,   572,   574,   576,   578,   583,   585,   590,
     592,   597,   602,   604,   606,   608,   610,   612,   614,   616,
     618,   620,   622,   624,   626,   628,   630,   632,   634,   636,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   670,
     671,   672,   673,   674,   675,   676,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   690,   695,   697,   699,
     701,   706,   711,   712,   715,   716,   720,   722,   724,   726,
     731,   733,   738,   740,   742,   744,   747,   751,   756,   759,
     763,   765,   770,   775,   780,   785,   790,   795,   800,   805,
     810,   815,   820,   825,   830,   835,   840,   845,   850,   855,
     860,   865,   867,   872,   874,   876,   878,   880,   882,   884,
     886,   891,   896,   901,   906,   907,   908,   909,   910,   911,
     912,   913,   914,   918,   923,   928,   933,   938,   943,   948,
     953,   958,   963,   965,   970,   972,   974,   979,   984,   989,
     994,   999,  1001,  1006,  1008,  1013,  1018
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
#line 5515 "parser.cpp"

#line 1022 "parser.ypp"


void xsk::arc::t6::parser::error(const xsk::arc::location& loc, const std::string& msg)
{
    throw xsk::arc::comp_error(loc, msg);
}
