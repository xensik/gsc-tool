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
#line 41 "parser.ypp"

#include "xsk/stdinc.hpp"
#include "xsk/gsc/parser.hpp"
#include "xsk/gsc/preprocessor.hpp"
using namespace xsk::gsc;
namespace xsk::gsc
{ 
    auto GSClex(context const* ctx_, preprocessor& ppr) -> parser::symbol_type;
    auto parse_switch(stmt_switch& stm) -> void;
}

#line 51 "parser.cpp"

// Take the name prefix into account.
#define yylex   GSClex

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
#if GSCDEBUG

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

#else // !GSCDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !GSCDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace gsc {
#line 153 "parser.cpp"

  /// Build a parser object.
  parser::parser (xsk::gsc::context const* ctx__yyarg, xsk::gsc::preprocessor& ppr_yyarg, xsk::gsc::program::ptr& ast_yyarg, std::uint32_t index_yyarg)
#if GSCDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      ctx_ (ctx__yyarg),
      ppr (ppr_yyarg),
      ast (ast_yyarg),
      index (index_yyarg)
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
        value.YY_MOVE_OR_COPY< call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< decl::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_constant: // decl_constant
        value.YY_MOVE_OR_COPY< decl_constant::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.YY_MOVE_OR_COPY< decl_function::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.YY_MOVE_OR_COPY< decl_usingtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        value.YY_MOVE_OR_COPY< expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_add_array: // expr_add_array
        value.YY_MOVE_OR_COPY< expr_add_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.YY_MOVE_OR_COPY< expr_anim::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.YY_MOVE_OR_COPY< expr_animation::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.YY_MOVE_OR_COPY< expr_animtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.YY_MOVE_OR_COPY< expr_arguments::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.YY_MOVE_OR_COPY< expr_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.YY_MOVE_OR_COPY< expr_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.YY_MOVE_OR_COPY< expr_complement::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.YY_MOVE_OR_COPY< expr_empty_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.YY_MOVE_OR_COPY< expr_false::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.YY_MOVE_OR_COPY< expr_field::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.YY_MOVE_OR_COPY< expr_float::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.YY_MOVE_OR_COPY< expr_game::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.YY_MOVE_OR_COPY< expr_identifier::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.YY_MOVE_OR_COPY< expr_integer::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.YY_MOVE_OR_COPY< expr_isdefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.YY_MOVE_OR_COPY< expr_istring::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        value.YY_MOVE_OR_COPY< expr_istrue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.YY_MOVE_OR_COPY< expr_level::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.YY_MOVE_OR_COPY< expr_method::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.YY_MOVE_OR_COPY< expr_negate::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.YY_MOVE_OR_COPY< expr_not::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.YY_MOVE_OR_COPY< expr_parameters::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.YY_MOVE_OR_COPY< expr_paren::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.YY_MOVE_OR_COPY< expr_path::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.YY_MOVE_OR_COPY< expr_reference::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.YY_MOVE_OR_COPY< expr_self::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.YY_MOVE_OR_COPY< expr_size::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.YY_MOVE_OR_COPY< expr_string::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.YY_MOVE_OR_COPY< expr_thisthread::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.YY_MOVE_OR_COPY< expr_true::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        value.YY_MOVE_OR_COPY< expr_tuple::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.YY_MOVE_OR_COPY< expr_undefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.YY_MOVE_OR_COPY< expr_vector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.YY_MOVE_OR_COPY< include::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< program::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.YY_MOVE_OR_COPY< stmt::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assert: // stmt_assert
        value.YY_MOVE_OR_COPY< stmt_assert::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assertex: // stmt_assertex
        value.YY_MOVE_OR_COPY< stmt_assertex::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assertmsg: // stmt_assertmsg
        value.YY_MOVE_OR_COPY< stmt_assertmsg::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.YY_MOVE_OR_COPY< stmt_break::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.YY_MOVE_OR_COPY< stmt_breakpoint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.YY_MOVE_OR_COPY< stmt_case::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        value.YY_MOVE_OR_COPY< stmt_comp::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.YY_MOVE_OR_COPY< stmt_continue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.YY_MOVE_OR_COPY< stmt_default::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.YY_MOVE_OR_COPY< stmt_dev::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.YY_MOVE_OR_COPY< stmt_dowhile::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.YY_MOVE_OR_COPY< stmt_endon::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
        value.YY_MOVE_OR_COPY< stmt_expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.YY_MOVE_OR_COPY< stmt_for::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.YY_MOVE_OR_COPY< stmt_foreach::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.YY_MOVE_OR_COPY< stmt_if::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.YY_MOVE_OR_COPY< stmt_ifelse::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        value.YY_MOVE_OR_COPY< stmt_list::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.YY_MOVE_OR_COPY< stmt_notify::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.YY_MOVE_OR_COPY< stmt_prof_begin::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.YY_MOVE_OR_COPY< stmt_prof_end::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.YY_MOVE_OR_COPY< stmt_return::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.YY_MOVE_OR_COPY< stmt_switch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.YY_MOVE_OR_COPY< stmt_wait::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.YY_MOVE_OR_COPY< stmt_waitframe::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.YY_MOVE_OR_COPY< stmt_waittill::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.YY_MOVE_OR_COPY< stmt_waittillframeend::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.YY_MOVE_OR_COPY< stmt_waittillmatch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.YY_MOVE_OR_COPY< stmt_while::ptr > (YY_MOVE (that.value));
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
        value.move< call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_constant: // decl_constant
        value.move< decl_constant::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.move< decl_function::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.move< decl_usingtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        value.move< expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_add_array: // expr_add_array
        value.move< expr_add_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.move< expr_anim::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.move< expr_animation::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.move< expr_animtree::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.move< expr_arguments::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.move< expr_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.move< expr_call::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.move< expr_complement::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.move< expr_empty_array::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.move< expr_false::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.move< expr_field::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.move< expr_float::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.move< expr_game::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.move< expr_identifier::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.move< expr_integer::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.move< expr_isdefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.move< expr_istring::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        value.move< expr_istrue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.move< expr_level::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.move< expr_method::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.move< expr_negate::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.move< expr_not::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.move< expr_parameters::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.move< expr_paren::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.move< expr_path::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.move< expr_reference::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.move< expr_self::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.move< expr_size::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.move< expr_string::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.move< expr_thisthread::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.move< expr_true::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        value.move< expr_tuple::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.move< expr_undefined::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.move< expr_vector::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.move< include::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< program::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.move< stmt::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assert: // stmt_assert
        value.move< stmt_assert::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assertex: // stmt_assertex
        value.move< stmt_assertex::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assertmsg: // stmt_assertmsg
        value.move< stmt_assertmsg::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< stmt_break::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.move< stmt_breakpoint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< stmt_case::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        value.move< stmt_comp::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< stmt_continue::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< stmt_default::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.move< stmt_dev::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.move< stmt_dowhile::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< stmt_endon::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_expr::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< stmt_for::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< stmt_foreach::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< stmt_if::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< stmt_ifelse::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        value.move< stmt_list::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< stmt_notify::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.move< stmt_prof_begin::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.move< stmt_prof_end::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< stmt_return::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< stmt_switch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< stmt_wait::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< stmt_waitframe::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< stmt_waittill::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< stmt_waittillframeend::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< stmt_waittillmatch::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< stmt_while::ptr > (YY_MOVE (that.value));
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
        value.copy< call::ptr > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< decl::ptr > (that.value);
        break;

      case symbol_kind::S_decl_constant: // decl_constant
        value.copy< decl_constant::ptr > (that.value);
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.copy< decl_function::ptr > (that.value);
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.copy< decl_usingtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        value.copy< expr::ptr > (that.value);
        break;

      case symbol_kind::S_expr_add_array: // expr_add_array
        value.copy< expr_add_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.copy< expr_anim::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.copy< expr_animation::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.copy< expr_animtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.copy< expr_arguments::ptr > (that.value);
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.copy< expr_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.copy< expr_call::ptr > (that.value);
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.copy< expr_complement::ptr > (that.value);
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.copy< expr_empty_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.copy< expr_false::ptr > (that.value);
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.copy< expr_field::ptr > (that.value);
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.copy< expr_float::ptr > (that.value);
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.copy< expr_game::ptr > (that.value);
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.copy< expr_identifier::ptr > (that.value);
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.copy< expr_integer::ptr > (that.value);
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.copy< expr_isdefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.copy< expr_istring::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        value.copy< expr_istrue::ptr > (that.value);
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.copy< expr_level::ptr > (that.value);
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.copy< expr_method::ptr > (that.value);
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.copy< expr_negate::ptr > (that.value);
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.copy< expr_not::ptr > (that.value);
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.copy< expr_parameters::ptr > (that.value);
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.copy< expr_paren::ptr > (that.value);
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.copy< expr_path::ptr > (that.value);
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.copy< expr_reference::ptr > (that.value);
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.copy< expr_self::ptr > (that.value);
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.copy< expr_size::ptr > (that.value);
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.copy< expr_string::ptr > (that.value);
        break;

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.copy< expr_thisthread::ptr > (that.value);
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.copy< expr_true::ptr > (that.value);
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        value.copy< expr_tuple::ptr > (that.value);
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.copy< expr_undefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.copy< expr_vector::ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.copy< include::ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< program::ptr > (that.value);
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.copy< stmt::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_assert: // stmt_assert
        value.copy< stmt_assert::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_assertex: // stmt_assertex
        value.copy< stmt_assertex::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_assertmsg: // stmt_assertmsg
        value.copy< stmt_assertmsg::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.copy< stmt_break::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.copy< stmt_breakpoint::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.copy< stmt_case::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        value.copy< stmt_comp::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.copy< stmt_continue::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.copy< stmt_default::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.copy< stmt_dev::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.copy< stmt_dowhile::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.copy< stmt_endon::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
        value.copy< stmt_expr::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.copy< stmt_for::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.copy< stmt_foreach::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.copy< stmt_if::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.copy< stmt_ifelse::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        value.copy< stmt_list::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.copy< stmt_notify::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.copy< stmt_prof_begin::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.copy< stmt_prof_end::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.copy< stmt_return::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.copy< stmt_switch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.copy< stmt_wait::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.copy< stmt_waitframe::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.copy< stmt_waittill::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.copy< stmt_waittillframeend::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.copy< stmt_waittillmatch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.copy< stmt_while::ptr > (that.value);
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
        value.move< call::ptr > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl::ptr > (that.value);
        break;

      case symbol_kind::S_decl_constant: // decl_constant
        value.move< decl_constant::ptr > (that.value);
        break;

      case symbol_kind::S_decl_function: // decl_function
        value.move< decl_function::ptr > (that.value);
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        value.move< decl_usingtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        value.move< expr::ptr > (that.value);
        break;

      case symbol_kind::S_expr_add_array: // expr_add_array
        value.move< expr_add_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        value.move< expr_anim::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        value.move< expr_animation::ptr > (that.value);
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        value.move< expr_animtree::ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        value.move< expr_arguments::ptr > (that.value);
        break;

      case symbol_kind::S_expr_array: // expr_array
        value.move< expr_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
        value.move< expr_call::ptr > (that.value);
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        value.move< expr_complement::ptr > (that.value);
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        value.move< expr_empty_array::ptr > (that.value);
        break;

      case symbol_kind::S_expr_false: // expr_false
        value.move< expr_false::ptr > (that.value);
        break;

      case symbol_kind::S_expr_field: // expr_field
        value.move< expr_field::ptr > (that.value);
        break;

      case symbol_kind::S_expr_float: // expr_float
        value.move< expr_float::ptr > (that.value);
        break;

      case symbol_kind::S_expr_game: // expr_game
        value.move< expr_game::ptr > (that.value);
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        value.move< expr_identifier::ptr > (that.value);
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        value.move< expr_integer::ptr > (that.value);
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        value.move< expr_isdefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        value.move< expr_istring::ptr > (that.value);
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        value.move< expr_istrue::ptr > (that.value);
        break;

      case symbol_kind::S_expr_level: // expr_level
        value.move< expr_level::ptr > (that.value);
        break;

      case symbol_kind::S_expr_method: // expr_method
        value.move< expr_method::ptr > (that.value);
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        value.move< expr_negate::ptr > (that.value);
        break;

      case symbol_kind::S_expr_not: // expr_not
        value.move< expr_not::ptr > (that.value);
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        value.move< expr_parameters::ptr > (that.value);
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        value.move< expr_paren::ptr > (that.value);
        break;

      case symbol_kind::S_expr_path: // expr_path
        value.move< expr_path::ptr > (that.value);
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        value.move< expr_reference::ptr > (that.value);
        break;

      case symbol_kind::S_expr_self: // expr_self
        value.move< expr_self::ptr > (that.value);
        break;

      case symbol_kind::S_expr_size: // expr_size
        value.move< expr_size::ptr > (that.value);
        break;

      case symbol_kind::S_expr_string: // expr_string
        value.move< expr_string::ptr > (that.value);
        break;

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        value.move< expr_thisthread::ptr > (that.value);
        break;

      case symbol_kind::S_expr_true: // expr_true
        value.move< expr_true::ptr > (that.value);
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        value.move< expr_tuple::ptr > (that.value);
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        value.move< expr_undefined::ptr > (that.value);
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        value.move< expr_vector::ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.move< include::ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< program::ptr > (that.value);
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        value.move< stmt::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_assert: // stmt_assert
        value.move< stmt_assert::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_assertex: // stmt_assertex
        value.move< stmt_assertex::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_assertmsg: // stmt_assertmsg
        value.move< stmt_assertmsg::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< stmt_break::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.move< stmt_breakpoint::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< stmt_case::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        value.move< stmt_comp::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< stmt_continue::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< stmt_default::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        value.move< stmt_dev::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        value.move< stmt_dowhile::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< stmt_endon::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_expr::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< stmt_for::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< stmt_foreach::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< stmt_if::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< stmt_ifelse::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        value.move< stmt_list::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< stmt_notify::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.move< stmt_prof_begin::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.move< stmt_prof_end::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< stmt_return::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< stmt_switch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< stmt_wait::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< stmt_waitframe::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< stmt_waittill::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< stmt_waittillframeend::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< stmt_waittillmatch::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< stmt_while::ptr > (that.value);
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

#if GSCDEBUG
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

#if GSCDEBUG
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
#endif // GSCDEBUG

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
            symbol_type yylookahead (yylex (ctx_, ppr));
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
        yylhs.value.emplace< call::ptr > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< decl::ptr > ();
        break;

      case symbol_kind::S_decl_constant: // decl_constant
        yylhs.value.emplace< decl_constant::ptr > ();
        break;

      case symbol_kind::S_decl_function: // decl_function
        yylhs.value.emplace< decl_function::ptr > ();
        break;

      case symbol_kind::S_decl_usingtree: // decl_usingtree
        yylhs.value.emplace< decl_usingtree::ptr > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_or_empty: // expr_or_empty
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        yylhs.value.emplace< expr::ptr > ();
        break;

      case symbol_kind::S_expr_add_array: // expr_add_array
        yylhs.value.emplace< expr_add_array::ptr > ();
        break;

      case symbol_kind::S_expr_anim: // expr_anim
        yylhs.value.emplace< expr_anim::ptr > ();
        break;

      case symbol_kind::S_expr_animation: // expr_animation
        yylhs.value.emplace< expr_animation::ptr > ();
        break;

      case symbol_kind::S_expr_animtree: // expr_animtree
        yylhs.value.emplace< expr_animtree::ptr > ();
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_no_empty: // expr_arguments_no_empty
        yylhs.value.emplace< expr_arguments::ptr > ();
        break;

      case symbol_kind::S_expr_array: // expr_array
        yylhs.value.emplace< expr_array::ptr > ();
        break;

      case symbol_kind::S_expr_call: // expr_call
        yylhs.value.emplace< expr_call::ptr > ();
        break;

      case symbol_kind::S_expr_complement: // expr_complement
        yylhs.value.emplace< expr_complement::ptr > ();
        break;

      case symbol_kind::S_expr_empty_array: // expr_empty_array
        yylhs.value.emplace< expr_empty_array::ptr > ();
        break;

      case symbol_kind::S_expr_false: // expr_false
        yylhs.value.emplace< expr_false::ptr > ();
        break;

      case symbol_kind::S_expr_field: // expr_field
        yylhs.value.emplace< expr_field::ptr > ();
        break;

      case symbol_kind::S_expr_float: // expr_float
        yylhs.value.emplace< expr_float::ptr > ();
        break;

      case symbol_kind::S_expr_game: // expr_game
        yylhs.value.emplace< expr_game::ptr > ();
        break;

      case symbol_kind::S_expr_identifier_nosize: // expr_identifier_nosize
      case symbol_kind::S_expr_identifier: // expr_identifier
        yylhs.value.emplace< expr_identifier::ptr > ();
        break;

      case symbol_kind::S_expr_integer: // expr_integer
        yylhs.value.emplace< expr_integer::ptr > ();
        break;

      case symbol_kind::S_expr_isdefined: // expr_isdefined
        yylhs.value.emplace< expr_isdefined::ptr > ();
        break;

      case symbol_kind::S_expr_istring: // expr_istring
        yylhs.value.emplace< expr_istring::ptr > ();
        break;

      case symbol_kind::S_expr_istrue: // expr_istrue
        yylhs.value.emplace< expr_istrue::ptr > ();
        break;

      case symbol_kind::S_expr_level: // expr_level
        yylhs.value.emplace< expr_level::ptr > ();
        break;

      case symbol_kind::S_expr_method: // expr_method
        yylhs.value.emplace< expr_method::ptr > ();
        break;

      case symbol_kind::S_expr_negate: // expr_negate
        yylhs.value.emplace< expr_negate::ptr > ();
        break;

      case symbol_kind::S_expr_not: // expr_not
        yylhs.value.emplace< expr_not::ptr > ();
        break;

      case symbol_kind::S_expr_parameters: // expr_parameters
        yylhs.value.emplace< expr_parameters::ptr > ();
        break;

      case symbol_kind::S_expr_paren: // expr_paren
        yylhs.value.emplace< expr_paren::ptr > ();
        break;

      case symbol_kind::S_expr_path: // expr_path
        yylhs.value.emplace< expr_path::ptr > ();
        break;

      case symbol_kind::S_expr_reference: // expr_reference
        yylhs.value.emplace< expr_reference::ptr > ();
        break;

      case symbol_kind::S_expr_self: // expr_self
        yylhs.value.emplace< expr_self::ptr > ();
        break;

      case symbol_kind::S_expr_size: // expr_size
        yylhs.value.emplace< expr_size::ptr > ();
        break;

      case symbol_kind::S_expr_string: // expr_string
        yylhs.value.emplace< expr_string::ptr > ();
        break;

      case symbol_kind::S_expr_thisthread: // expr_thisthread
        yylhs.value.emplace< expr_thisthread::ptr > ();
        break;

      case symbol_kind::S_expr_true: // expr_true
        yylhs.value.emplace< expr_true::ptr > ();
        break;

      case symbol_kind::S_expr_tuple_arguments: // expr_tuple_arguments
        yylhs.value.emplace< expr_tuple::ptr > ();
        break;

      case symbol_kind::S_expr_undefined: // expr_undefined
        yylhs.value.emplace< expr_undefined::ptr > ();
        break;

      case symbol_kind::S_expr_vector: // expr_vector
        yylhs.value.emplace< expr_vector::ptr > ();
        break;

      case symbol_kind::S_include: // include
        yylhs.value.emplace< include::ptr > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< program::ptr > ();
        break;

      case symbol_kind::S_PATH: // "path"
      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "integer"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_or_dev: // stmt_or_dev
        yylhs.value.emplace< stmt::ptr > ();
        break;

      case symbol_kind::S_stmt_assert: // stmt_assert
        yylhs.value.emplace< stmt_assert::ptr > ();
        break;

      case symbol_kind::S_stmt_assertex: // stmt_assertex
        yylhs.value.emplace< stmt_assertex::ptr > ();
        break;

      case symbol_kind::S_stmt_assertmsg: // stmt_assertmsg
        yylhs.value.emplace< stmt_assertmsg::ptr > ();
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        yylhs.value.emplace< stmt_break::ptr > ();
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        yylhs.value.emplace< stmt_breakpoint::ptr > ();
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        yylhs.value.emplace< stmt_case::ptr > ();
        break;

      case symbol_kind::S_stmt_comp: // stmt_comp
        yylhs.value.emplace< stmt_comp::ptr > ();
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        yylhs.value.emplace< stmt_continue::ptr > ();
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        yylhs.value.emplace< stmt_default::ptr > ();
        break;

      case symbol_kind::S_stmt_dev: // stmt_dev
        yylhs.value.emplace< stmt_dev::ptr > ();
        break;

      case symbol_kind::S_stmt_dowhile: // stmt_dowhile
        yylhs.value.emplace< stmt_dowhile::ptr > ();
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        yylhs.value.emplace< stmt_endon::ptr > ();
        break;

      case symbol_kind::S_stmt_expr: // stmt_expr
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
        yylhs.value.emplace< stmt_expr::ptr > ();
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        yylhs.value.emplace< stmt_for::ptr > ();
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        yylhs.value.emplace< stmt_foreach::ptr > ();
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        yylhs.value.emplace< stmt_if::ptr > ();
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        yylhs.value.emplace< stmt_ifelse::ptr > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
      case symbol_kind::S_stmt_or_dev_list: // stmt_or_dev_list
        yylhs.value.emplace< stmt_list::ptr > ();
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        yylhs.value.emplace< stmt_notify::ptr > ();
        break;

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        yylhs.value.emplace< stmt_prof_begin::ptr > ();
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        yylhs.value.emplace< stmt_prof_end::ptr > ();
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        yylhs.value.emplace< stmt_return::ptr > ();
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        yylhs.value.emplace< stmt_switch::ptr > ();
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        yylhs.value.emplace< stmt_wait::ptr > ();
        break;

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        yylhs.value.emplace< stmt_waitframe::ptr > ();
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        yylhs.value.emplace< stmt_waittill::ptr > ();
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        yylhs.value.emplace< stmt_waittillframeend::ptr > ();
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        yylhs.value.emplace< stmt_waittillmatch::ptr > ();
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        yylhs.value.emplace< stmt_while::ptr > ();
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
#line 275 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program::ptr > ()); }
#line 2131 "parser.cpp"
    break;

  case 3: // root: %empty
#line 276 "parser.ypp"
              { ast = program::make(yylhs.location); }
#line 2137 "parser.cpp"
    break;

  case 4: // program: program ";"
#line 281 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2143 "parser.cpp"
    break;

  case 5: // program: program inline
#line 283 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2149 "parser.cpp"
    break;

  case 6: // program: program include
#line 285 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2155 "parser.cpp"
    break;

  case 7: // program: program declaration
#line 287 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2161 "parser.cpp"
    break;

  case 8: // program: ";"
#line 289 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2167 "parser.cpp"
    break;

  case 9: // program: inline
#line 291 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); }
#line 2173 "parser.cpp"
    break;

  case 10: // program: include
#line 293 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2179 "parser.cpp"
    break;

  case 11: // program: declaration
#line 295 "parser.ypp"
        { yylhs.value.as < program::ptr > () = program::make(yylhs.location); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl::ptr > ())); }
#line 2185 "parser.cpp"
    break;

  case 12: // inline: "#inline" expr_path ";"
#line 299 "parser.ypp"
                                 { ppr.push_header(yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2191 "parser.cpp"
    break;

  case 13: // include: "#include" expr_path ";"
#line 304 "parser.ypp"
        { yylhs.value.as < include::ptr > () = include::make(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2197 "parser.cpp"
    break;

  case 14: // declaration: "/#"
#line 308 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_begin::make(yylhs.location); }
#line 2203 "parser.cpp"
    break;

  case 15: // declaration: "#/"
#line 309 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = decl_dev_end::make(yylhs.location); }
#line 2209 "parser.cpp"
    break;

  case 16: // declaration: decl_usingtree
#line 310 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_usingtree::ptr > ()); }
#line 2215 "parser.cpp"
    break;

  case 17: // declaration: decl_constant
#line 311 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_constant::ptr > ()); }
#line 2221 "parser.cpp"
    break;

  case 18: // declaration: decl_function
#line 312 "parser.ypp"
                        { yylhs.value.as < decl::ptr > () = std::move(yystack_[0].value.as < decl_function::ptr > ()); }
#line 2227 "parser.cpp"
    break;

  case 19: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 317 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_usingtree::ptr > () = decl_usingtree::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 2233 "parser.cpp"
    break;

  case 20: // decl_constant: expr_identifier "=" expr ";"
#line 322 "parser.ypp"
        {
            ppr.ban_header(yylhs.location); yylhs.value.as < decl_constant::ptr > () = decl_constant::make(yylhs.location, std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); 
            printf("%s" , fmt::format("{}: constants deprecated, use #define instead\n", yylhs.location.print()).data());
        }
#line 2242 "parser.cpp"
    break;

  case 21: // decl_function: expr_identifier "(" expr_parameters ")" stmt_comp
#line 330 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = decl_function::make(yylhs.location, std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); }
#line 2248 "parser.cpp"
    break;

  case 22: // stmt: stmt_comp
#line 334 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_comp::ptr > ()); }
#line 2254 "parser.cpp"
    break;

  case 23: // stmt: stmt_call
#line 335 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2260 "parser.cpp"
    break;

  case 24: // stmt: stmt_assign
#line 336 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_expr::ptr > ()); }
#line 2266 "parser.cpp"
    break;

  case 25: // stmt: stmt_endon
#line 337 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_endon::ptr > ()); }
#line 2272 "parser.cpp"
    break;

  case 26: // stmt: stmt_notify
#line 338 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_notify::ptr > ()); }
#line 2278 "parser.cpp"
    break;

  case 27: // stmt: stmt_wait
#line 339 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_wait::ptr > ()); }
#line 2284 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittill
#line 340 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittill::ptr > ()); }
#line 2290 "parser.cpp"
    break;

  case 29: // stmt: stmt_waittillmatch
#line 341 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillmatch::ptr > ()); }
#line 2296 "parser.cpp"
    break;

  case 30: // stmt: stmt_waittillframeend
#line 342 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waittillframeend::ptr > ()); }
#line 2302 "parser.cpp"
    break;

  case 31: // stmt: stmt_waitframe
#line 343 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_waitframe::ptr > ()); }
#line 2308 "parser.cpp"
    break;

  case 32: // stmt: stmt_if
#line 344 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_if::ptr > ()); }
#line 2314 "parser.cpp"
    break;

  case 33: // stmt: stmt_ifelse
#line 345 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_ifelse::ptr > ()); }
#line 2320 "parser.cpp"
    break;

  case 34: // stmt: stmt_while
#line 346 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_while::ptr > ()); }
#line 2326 "parser.cpp"
    break;

  case 35: // stmt: stmt_dowhile
#line 347 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dowhile::ptr > ()); }
#line 2332 "parser.cpp"
    break;

  case 36: // stmt: stmt_for
#line 348 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_for::ptr > ()); }
#line 2338 "parser.cpp"
    break;

  case 37: // stmt: stmt_foreach
#line 349 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_foreach::ptr > ()); }
#line 2344 "parser.cpp"
    break;

  case 38: // stmt: stmt_switch
#line 350 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_switch::ptr > ()); }
#line 2350 "parser.cpp"
    break;

  case 39: // stmt: stmt_case
#line 351 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_case::ptr > ()); }
#line 2356 "parser.cpp"
    break;

  case 40: // stmt: stmt_default
#line 352 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_default::ptr > ()); }
#line 2362 "parser.cpp"
    break;

  case 41: // stmt: stmt_break
#line 353 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_break::ptr > ()); }
#line 2368 "parser.cpp"
    break;

  case 42: // stmt: stmt_continue
#line 354 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_continue::ptr > ()); }
#line 2374 "parser.cpp"
    break;

  case 43: // stmt: stmt_return
#line 355 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_return::ptr > ()); }
#line 2380 "parser.cpp"
    break;

  case 44: // stmt: stmt_breakpoint
#line 356 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_breakpoint::ptr > ()); }
#line 2386 "parser.cpp"
    break;

  case 45: // stmt: stmt_prof_begin
#line 357 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_begin::ptr > ()); }
#line 2392 "parser.cpp"
    break;

  case 46: // stmt: stmt_prof_end
#line 358 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_prof_end::ptr > ()); }
#line 2398 "parser.cpp"
    break;

  case 47: // stmt: stmt_assert
#line 359 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_assert::ptr > ()); }
#line 2404 "parser.cpp"
    break;

  case 48: // stmt: stmt_assertex
#line 360 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_assertex::ptr > ()); }
#line 2410 "parser.cpp"
    break;

  case 49: // stmt: stmt_assertmsg
#line 361 "parser.ypp"
                             { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_assertmsg::ptr > ()); }
#line 2416 "parser.cpp"
    break;

  case 50: // stmt_or_dev: stmt
#line 365 "parser.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt::ptr > ()); }
#line 2422 "parser.cpp"
    break;

  case 51: // stmt_or_dev: stmt_dev
#line 366 "parser.ypp"
               { yylhs.value.as < stmt::ptr > () = std::move(yystack_[0].value.as < stmt_dev::ptr > ()); }
#line 2428 "parser.cpp"
    break;

  case 52: // stmt_list: stmt_list stmt
#line 371 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2434 "parser.cpp"
    break;

  case 53: // stmt_list: stmt
#line 373 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2440 "parser.cpp"
    break;

  case 54: // stmt_list: stmt_list ";"
#line 375 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2446 "parser.cpp"
    break;

  case 55: // stmt_list: ";"
#line 377 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2452 "parser.cpp"
    break;

  case 56: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 382 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2458 "parser.cpp"
    break;

  case 57: // stmt_or_dev_list: stmt_or_dev
#line 384 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2464 "parser.cpp"
    break;

  case 58: // stmt_or_dev_list: stmt_or_dev_list ";"
#line 386 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2470 "parser.cpp"
    break;

  case 59: // stmt_or_dev_list: ";"
#line 388 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = stmt_list::make(yylhs.location); }
#line 2476 "parser.cpp"
    break;

  case 60: // stmt_dev: "/#" stmt_list "#/"
#line 392 "parser.ypp"
                                { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2482 "parser.cpp"
    break;

  case 61: // stmt_dev: "/#" "#/"
#line 393 "parser.ypp"
                      { yylhs.value.as < stmt_dev::ptr > () = stmt_dev::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2488 "parser.cpp"
    break;

  case 62: // stmt_comp: "{" stmt_or_dev_list "}"
#line 397 "parser.ypp"
                                     { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2494 "parser.cpp"
    break;

  case 63: // stmt_comp: "{" "}"
#line 398 "parser.ypp"
                    { yylhs.value.as < stmt_comp::ptr > () = stmt_comp::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2500 "parser.cpp"
    break;

  case 64: // stmt_expr: expr_assign
#line 403 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2506 "parser.cpp"
    break;

  case 65: // stmt_expr: expr_increment
#line 405 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2512 "parser.cpp"
    break;

  case 66: // stmt_expr: expr_decrement
#line 407 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2518 "parser.cpp"
    break;

  case 67: // stmt_expr: %empty
#line 409 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 2524 "parser.cpp"
    break;

  case 68: // stmt_call: expr_call ";"
#line 414 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_call::ptr > ())); }
#line 2530 "parser.cpp"
    break;

  case 69: // stmt_call: expr_method ";"
#line 416 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr_method::ptr > ())); }
#line 2536 "parser.cpp"
    break;

  case 70: // stmt_assign: expr_assign ";"
#line 421 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2542 "parser.cpp"
    break;

  case 71: // stmt_assign: expr_increment ";"
#line 423 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2548 "parser.cpp"
    break;

  case 72: // stmt_assign: expr_decrement ";"
#line 425 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = stmt_expr::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2554 "parser.cpp"
    break;

  case 73: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 430 "parser.ypp"
        { yylhs.value.as < stmt_endon::ptr > () = stmt_endon::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 2560 "parser.cpp"
    break;

  case 74: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 435 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2566 "parser.cpp"
    break;

  case 75: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 437 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = stmt_notify::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2572 "parser.cpp"
    break;

  case 76: // stmt_wait: "wait" expr ";"
#line 442 "parser.ypp"
        { yylhs.value.as < stmt_wait::ptr > () = stmt_wait::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2578 "parser.cpp"
    break;

  case 77: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 447 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2584 "parser.cpp"
    break;

  case 78: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 449 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = stmt_waittill::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2590 "parser.cpp"
    break;

  case 79: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 454 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[7].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2596 "parser.cpp"
    break;

  case 80: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 456 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = stmt_waittillmatch::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), expr_arguments::make(yylhs.location)); }
#line 2602 "parser.cpp"
    break;

  case 81: // stmt_waittillframeend: "waittillframeend" ";"
#line 461 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend::ptr > () = stmt_waittillframeend::make(yylhs.location); }
#line 2608 "parser.cpp"
    break;

  case 82: // stmt_waitframe: "waitframe" ";"
#line 466 "parser.ypp"
        { yylhs.value.as < stmt_waitframe::ptr > () = stmt_waitframe::make(yylhs.location); }
#line 2614 "parser.cpp"
    break;

  case 83: // stmt_waitframe: "waitframe" "(" ")" ";"
#line 468 "parser.ypp"
        { yylhs.value.as < stmt_waitframe::ptr > () = stmt_waitframe::make(yylhs.location); }
#line 2620 "parser.cpp"
    break;

  case 84: // stmt_if: "if" "(" expr ")" stmt
#line 473 "parser.ypp"
        { yylhs.value.as < stmt_if::ptr > () = stmt_if::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2626 "parser.cpp"
    break;

  case 85: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 478 "parser.ypp"
        { yylhs.value.as < stmt_ifelse::ptr > () = stmt_ifelse::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2632 "parser.cpp"
    break;

  case 86: // stmt_while: "while" "(" expr ")" stmt
#line 483 "parser.ypp"
        { yylhs.value.as < stmt_while::ptr > () = stmt_while::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2638 "parser.cpp"
    break;

  case 87: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 488 "parser.ypp"
        { yylhs.value.as < stmt_dowhile::ptr > () = stmt_dowhile::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[5].value.as < stmt::ptr > ())); }
#line 2644 "parser.cpp"
    break;

  case 88: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 493 "parser.ypp"
        { yylhs.value.as < stmt_for::ptr > () = stmt_for::make(yylhs.location, std::move(yystack_[6].value.as < stmt_expr::ptr > ()), std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < stmt_expr::ptr > ()), std::move(yystack_[0].value.as < stmt::ptr > ())); }
#line 2650 "parser.cpp"
    break;

  case 89: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 498 "parser.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, fmt::format("_temp_{}", ++index));
            auto key = expr_identifier::make(yylhs.location, fmt::format("_temp_{}", ++index));
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), expr_empty::make(yylhs.location), std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt::ptr > ()), false);
        }
#line 2660 "parser.cpp"
    break;

  case 90: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 504 "parser.ypp"
        {
            auto array = expr_identifier::make(yylhs.location, fmt::format("_temp_{}", ++index));
            expr::ptr key = (ctx_->props() & props::foreach) ? expr_identifier::make(yylhs.location, fmt::format("_temp_{}", ++index)) : std::move(yystack_[6].value.as < expr_identifier::ptr > ());
            yylhs.value.as < stmt_foreach::ptr > () = stmt_foreach::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[4].value.as < expr_identifier::ptr > ()), (ctx_->props() & props::foreach) ? std::move(yystack_[6].value.as < expr_identifier::ptr > ()) : (expr::ptr)expr_empty::make(yylhs.location), std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt::ptr > ()), true);
        }
#line 2670 "parser.cpp"
    break;

  case 91: // stmt_switch: "switch" "(" expr ")" stmt_comp
#line 513 "parser.ypp"
        { yylhs.value.as < stmt_switch::ptr > () = stmt_switch::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); 
          parse_switch(*yylhs.value.as < stmt_switch::ptr > ());
        }
#line 2678 "parser.cpp"
    break;

  case 92: // stmt_case: "case" expr_integer ":"
#line 520 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_integer::ptr > ()), stmt_list::make(yylhs.location)); }
#line 2684 "parser.cpp"
    break;

  case 93: // stmt_case: "case" expr_string ":"
#line 522 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = stmt_case::make(yylhs.location, std::move(yystack_[1].value.as < expr_string::ptr > ()), stmt_list::make(yylhs.location)); }
#line 2690 "parser.cpp"
    break;

  case 94: // stmt_default: "default" ":"
#line 527 "parser.ypp"
        { yylhs.value.as < stmt_default::ptr > () = stmt_default::make(yylhs.location, stmt_list::make(yylhs.location)); }
#line 2696 "parser.cpp"
    break;

  case 95: // stmt_break: "break" ";"
#line 532 "parser.ypp"
        { yylhs.value.as < stmt_break::ptr > () = stmt_break::make(yylhs.location); }
#line 2702 "parser.cpp"
    break;

  case 96: // stmt_continue: "continue" ";"
#line 537 "parser.ypp"
        { yylhs.value.as < stmt_continue::ptr > () = stmt_continue::make(yylhs.location); }
#line 2708 "parser.cpp"
    break;

  case 97: // stmt_return: "return" expr ";"
#line 542 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 2714 "parser.cpp"
    break;

  case 98: // stmt_return: "return" ";"
#line 544 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = stmt_return::make(yylhs.location, expr_empty::make(yylhs.location)); }
#line 2720 "parser.cpp"
    break;

  case 99: // stmt_breakpoint: "breakpoint" ";"
#line 549 "parser.ypp"
        { yylhs.value.as < stmt_breakpoint::ptr > () = stmt_breakpoint::make(yylhs.location); }
#line 2726 "parser.cpp"
    break;

  case 100: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 554 "parser.ypp"
        { yylhs.value.as < stmt_prof_begin::ptr > () = stmt_prof_begin::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2732 "parser.cpp"
    break;

  case 101: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 559 "parser.ypp"
        { yylhs.value.as < stmt_prof_end::ptr > () = stmt_prof_end::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2738 "parser.cpp"
    break;

  case 102: // stmt_assert: "assert" "(" expr_arguments ")" ";"
#line 564 "parser.ypp"
        { yylhs.value.as < stmt_assert::ptr > () = stmt_assert::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2744 "parser.cpp"
    break;

  case 103: // stmt_assertex: "assertex" "(" expr_arguments ")" ";"
#line 569 "parser.ypp"
        { yylhs.value.as < stmt_assertex::ptr > () = stmt_assertex::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2750 "parser.cpp"
    break;

  case 104: // stmt_assertmsg: "assertmsg" "(" expr_arguments ")" ";"
#line 574 "parser.ypp"
        { yylhs.value.as < stmt_assertmsg::ptr > () = stmt_assertmsg::make(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2756 "parser.cpp"
    break;

  case 105: // expr: expr_ternary
#line 578 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2762 "parser.cpp"
    break;

  case 106: // expr: expr_binary
#line 579 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2768 "parser.cpp"
    break;

  case 107: // expr: expr_primitive
#line 580 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2774 "parser.cpp"
    break;

  case 108: // expr_or_empty: expr
#line 584 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr::ptr > ()); }
#line 2780 "parser.cpp"
    break;

  case 109: // expr_or_empty: %empty
#line 585 "parser.ypp"
                     { yylhs.value.as < expr::ptr > () = expr_empty::make(yylhs.location); }
#line 2786 "parser.cpp"
    break;

  case 110: // expr_increment: "++" expr_object
#line 590 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 2792 "parser.cpp"
    break;

  case 111: // expr_increment: expr_object "++"
#line 592 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_increment::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 2798 "parser.cpp"
    break;

  case 112: // expr_decrement: "--" expr_object
#line 597 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ()), true); }
#line 2804 "parser.cpp"
    break;

  case 113: // expr_decrement: expr_object "--"
#line 599 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_decrement::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), false); }
#line 2810 "parser.cpp"
    break;

  case 114: // expr_assign: expr_tuple "=" expr
#line 604 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 2816 "parser.cpp"
    break;

  case 115: // expr_assign: expr_object "=" expr
#line 606 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::eq); }
#line 2822 "parser.cpp"
    break;

  case 116: // expr_assign: expr_object "|=" expr
#line 608 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwor); }
#line 2828 "parser.cpp"
    break;

  case 117: // expr_assign: expr_object "&=" expr
#line 610 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwand); }
#line 2834 "parser.cpp"
    break;

  case 118: // expr_assign: expr_object "^=" expr
#line 612 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::bwexor); }
#line 2840 "parser.cpp"
    break;

  case 119: // expr_assign: expr_object "<<=" expr
#line 614 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shl); }
#line 2846 "parser.cpp"
    break;

  case 120: // expr_assign: expr_object ">>=" expr
#line 616 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::shr); }
#line 2852 "parser.cpp"
    break;

  case 121: // expr_assign: expr_object "+=" expr
#line 618 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::add); }
#line 2858 "parser.cpp"
    break;

  case 122: // expr_assign: expr_object "-=" expr
#line 620 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::sub); }
#line 2864 "parser.cpp"
    break;

  case 123: // expr_assign: expr_object "*=" expr
#line 622 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mul); }
#line 2870 "parser.cpp"
    break;

  case 124: // expr_assign: expr_object "/=" expr
#line 624 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::div); }
#line 2876 "parser.cpp"
    break;

  case 125: // expr_assign: expr_object "%=" expr
#line 626 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_assign::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_assign::op::mod); }
#line 2882 "parser.cpp"
    break;

  case 126: // expr_ternary: expr "?" expr ":" expr
#line 631 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_ternary::make(yylhs.location, std::move(yystack_[4].value.as < expr::ptr > ()), std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 2888 "parser.cpp"
    break;

  case 127: // expr_binary: expr "||" expr
#line 636 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_or); }
#line 2894 "parser.cpp"
    break;

  case 128: // expr_binary: expr "&&" expr
#line 638 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bool_and); }
#line 2900 "parser.cpp"
    break;

  case 129: // expr_binary: expr "==" expr
#line 640 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::eq); }
#line 2906 "parser.cpp"
    break;

  case 130: // expr_binary: expr "!=" expr
#line 642 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ne); }
#line 2912 "parser.cpp"
    break;

  case 131: // expr_binary: expr "<=" expr
#line 644 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::le); }
#line 2918 "parser.cpp"
    break;

  case 132: // expr_binary: expr ">=" expr
#line 646 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::ge); }
#line 2924 "parser.cpp"
    break;

  case 133: // expr_binary: expr "<" expr
#line 648 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::lt); }
#line 2930 "parser.cpp"
    break;

  case 134: // expr_binary: expr ">" expr
#line 650 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::gt); }
#line 2936 "parser.cpp"
    break;

  case 135: // expr_binary: expr "|" expr
#line 652 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwor); }
#line 2942 "parser.cpp"
    break;

  case 136: // expr_binary: expr "&" expr
#line 654 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwand); }
#line 2948 "parser.cpp"
    break;

  case 137: // expr_binary: expr "^" expr
#line 656 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::bwexor); }
#line 2954 "parser.cpp"
    break;

  case 138: // expr_binary: expr "<<" expr
#line 658 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shl); }
#line 2960 "parser.cpp"
    break;

  case 139: // expr_binary: expr ">>" expr
#line 660 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::shr); }
#line 2966 "parser.cpp"
    break;

  case 140: // expr_binary: expr "+" expr
#line 662 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::add); }
#line 2972 "parser.cpp"
    break;

  case 141: // expr_binary: expr "-" expr
#line 664 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::sub); }
#line 2978 "parser.cpp"
    break;

  case 142: // expr_binary: expr "*" expr
#line 666 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mul); }
#line 2984 "parser.cpp"
    break;

  case 143: // expr_binary: expr "/" expr
#line 668 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::div); }
#line 2990 "parser.cpp"
    break;

  case 144: // expr_binary: expr "%" expr
#line 670 "parser.ypp"
        { yylhs.value.as < expr::ptr > () = expr_binary::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr::ptr > ()), expr_binary::op::mod); }
#line 2996 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_complement
#line 674 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_complement::ptr > ()); }
#line 3002 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_negate
#line 675 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_negate::ptr > ()); }
#line 3008 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_not
#line 676 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_not::ptr > ()); }
#line 3014 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_call
#line 677 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3020 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_method
#line 678 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3026 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_add_array
#line 679 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_add_array::ptr > ()); }
#line 3032 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_isdefined
#line 680 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_isdefined::ptr > ()); }
#line 3038 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_istrue
#line 681 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_istrue::ptr > ()); }
#line 3044 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_reference
#line 682 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_reference::ptr > ()); }
#line 3050 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_array
#line 683 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3056 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_field
#line 684 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3062 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_size
#line 685 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_size::ptr > ()); }
#line 3068 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_paren
#line 686 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_paren::ptr > ()); }
#line 3074 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_thisthread
#line 687 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_thisthread::ptr > ()); }
#line 3080 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_empty_array
#line 688 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_empty_array::ptr > ()); }
#line 3086 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_undefined
#line 689 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_undefined::ptr > ()); }
#line 3092 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_game
#line 690 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3098 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_self
#line 691 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3104 "parser.cpp"
    break;

  case 163: // expr_primitive: expr_anim
#line 692 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3110 "parser.cpp"
    break;

  case 164: // expr_primitive: expr_level
#line 693 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3116 "parser.cpp"
    break;

  case 165: // expr_primitive: expr_animation
#line 694 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animation::ptr > ()); }
#line 3122 "parser.cpp"
    break;

  case 166: // expr_primitive: expr_animtree
#line 695 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_animtree::ptr > ()); }
#line 3128 "parser.cpp"
    break;

  case 167: // expr_primitive: expr_identifier
#line 696 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3134 "parser.cpp"
    break;

  case 168: // expr_primitive: expr_istring
#line 697 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_istring::ptr > ()); }
#line 3140 "parser.cpp"
    break;

  case 169: // expr_primitive: expr_string
#line 698 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_string::ptr > ()); }
#line 3146 "parser.cpp"
    break;

  case 170: // expr_primitive: expr_vector
#line 699 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_vector::ptr > ()); }
#line 3152 "parser.cpp"
    break;

  case 171: // expr_primitive: expr_float
#line 700 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_float::ptr > ()); }
#line 3158 "parser.cpp"
    break;

  case 172: // expr_primitive: expr_integer
#line 701 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_integer::ptr > ()); }
#line 3164 "parser.cpp"
    break;

  case 173: // expr_primitive: expr_false
#line 702 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_false::ptr > ()); }
#line 3170 "parser.cpp"
    break;

  case 174: // expr_primitive: expr_true
#line 703 "parser.ypp"
                            { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_true::ptr > ()); }
#line 3176 "parser.cpp"
    break;

  case 175: // expr_complement: "~" expr
#line 708 "parser.ypp"
        { yylhs.value.as < expr_complement::ptr > () = expr_complement::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3182 "parser.cpp"
    break;

  case 176: // expr_negate: "-" expr_identifier
#line 713 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3188 "parser.cpp"
    break;

  case 177: // expr_negate: "-" expr_paren
#line 715 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_paren::ptr > ())); }
#line 3194 "parser.cpp"
    break;

  case 178: // expr_negate: "-" expr_array
#line 717 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_array::ptr > ())); }
#line 3200 "parser.cpp"
    break;

  case 179: // expr_negate: "-" expr_field
#line 719 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = expr_negate::make(yylhs.location, std::move(yystack_[0].value.as < expr_field::ptr > ())); }
#line 3206 "parser.cpp"
    break;

  case 180: // expr_not: "!" expr
#line 724 "parser.ypp"
        { yylhs.value.as < expr_not::ptr > () = expr_not::make(yylhs.location, std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3212 "parser.cpp"
    break;

  case 181: // expr_call: expr_function
#line 728 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3218 "parser.cpp"
    break;

  case 182: // expr_call: expr_pointer
#line 729 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = expr_call::make(yylhs.location, std::move(yystack_[0].value.as < call::ptr > ())); }
#line 3224 "parser.cpp"
    break;

  case 183: // expr_method: expr_object expr_function
#line 734 "parser.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3235 "parser.cpp"
    break;

  case 184: // expr_method: expr_object expr_pointer
#line 741 "parser.ypp"
        {
            if (yystack_[1].value.as < expr::ptr > ()->loc().begin.line != yystack_[0].value.as < call::ptr > ()->loc().begin.line)
                error(yystack_[0].value.as < call::ptr > ()->loc(), "missing ';' ?");

            yylhs.value.as < expr_method::ptr > () = expr_method::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < call::ptr > ()));
        }
#line 3246 "parser.cpp"
    break;

  case 185: // expr_function: expr_identifier "(" expr_arguments ")"
#line 751 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3252 "parser.cpp"
    break;

  case 186: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 753 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3258 "parser.cpp"
    break;

  case 187: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 755 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3264 "parser.cpp"
    break;

  case 188: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 757 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3270 "parser.cpp"
    break;

  case 189: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 759 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3276 "parser.cpp"
    break;

  case 190: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 761 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_function::make(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3282 "parser.cpp"
    break;

  case 191: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 766 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3288 "parser.cpp"
    break;

  case 192: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 768 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3294 "parser.cpp"
    break;

  case 193: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 770 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3300 "parser.cpp"
    break;

  case 194: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 772 "parser.ypp"
        { yylhs.value.as < call::ptr > () = expr_pointer::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::builtin); }
#line 3306 "parser.cpp"
    break;

  case 195: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 777 "parser.ypp"
        { yylhs.value.as < expr_add_array::ptr > () = expr_add_array::make(yylhs.location, std::move(yystack_[1].value.as < expr_arguments::ptr > ())); }
#line 3312 "parser.cpp"
    break;

  case 196: // expr_parameters: expr_parameters "," expr_identifier
#line 782 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3318 "parser.cpp"
    break;

  case 197: // expr_parameters: expr_identifier
#line 784 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3324 "parser.cpp"
    break;

  case 198: // expr_parameters: %empty
#line 786 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = expr_parameters::make(yylhs.location); }
#line 3330 "parser.cpp"
    break;

  case 199: // expr_arguments: expr_arguments_no_empty
#line 791 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[0].value.as < expr_arguments::ptr > ()); }
#line 3336 "parser.cpp"
    break;

  case 200: // expr_arguments: %empty
#line 793 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); }
#line 3342 "parser.cpp"
    break;

  case 201: // expr_arguments_no_empty: expr_arguments "," expr
#line 798 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[2].value.as < expr_arguments::ptr > ()); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3348 "parser.cpp"
    break;

  case 202: // expr_arguments_no_empty: expr
#line 800 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = expr_arguments::make(yylhs.location); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3354 "parser.cpp"
    break;

  case 203: // expr_isdefined: "isdefined" "(" expr ")"
#line 805 "parser.ypp"
        { yylhs.value.as < expr_isdefined::ptr > () = expr_isdefined::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3360 "parser.cpp"
    break;

  case 204: // expr_istrue: "istrue" "(" expr ")"
#line 810 "parser.ypp"
        { yylhs.value.as < expr_istrue::ptr > () = expr_istrue::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3366 "parser.cpp"
    break;

  case 205: // expr_reference: "::" expr_identifier
#line 815 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, expr_path::make(yylhs.location), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3372 "parser.cpp"
    break;

  case 206: // expr_reference: expr_path "::" expr_identifier
#line 817 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = expr_reference::make(yylhs.location, std::move(yystack_[2].value.as < expr_path::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3378 "parser.cpp"
    break;

  case 207: // expr_tuple: "[" expr_tuple_arguments "]"
#line 822 "parser.ypp"
        {
            yylhs.value.as < expr::ptr > () = std::move(yystack_[1].value.as < expr_tuple::ptr > ());
            yylhs.value.as < expr::ptr > ()->as<expr_tuple>().temp = expr_identifier::make(yylhs.value.as < expr::ptr > ()->loc(), fmt::format("_temp_{}", ++index));
        }
#line 3387 "parser.cpp"
    break;

  case 208: // expr_tuple_arguments: expr_tuple_arguments "," expr_tuple_types
#line 830 "parser.ypp"
        { yylhs.value.as < expr_tuple::ptr > () = std::move(yystack_[2].value.as < expr_tuple::ptr > ()); yylhs.value.as < expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3393 "parser.cpp"
    break;

  case 209: // expr_tuple_arguments: expr_tuple_types
#line 832 "parser.ypp"
        { yylhs.value.as < expr_tuple::ptr > () = expr_tuple::make(yylhs.location); yylhs.value.as < expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr::ptr > ())); }
#line 3399 "parser.cpp"
    break;

  case 210: // expr_tuple_types: expr_array
#line 836 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3405 "parser.cpp"
    break;

  case 211: // expr_tuple_types: expr_field
#line 837 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3411 "parser.cpp"
    break;

  case 212: // expr_tuple_types: expr_identifier
#line 838 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3417 "parser.cpp"
    break;

  case 213: // expr_array: expr_object "[" expr "]"
#line 843 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = expr_array::make(yylhs.location, std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3423 "parser.cpp"
    break;

  case 214: // expr_field: expr_object "." expr_identifier_nosize
#line 848 "parser.ypp"
        { yylhs.value.as < expr_field::ptr > () = expr_field::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3429 "parser.cpp"
    break;

  case 215: // expr_size: expr_object "." "size"
#line 853 "parser.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr::ptr > ())); }
#line 3435 "parser.cpp"
    break;

  case 216: // expr_size: expr_string "." "size"
#line 855 "parser.ypp"
        { yylhs.value.as < expr_size::ptr > () = expr_size::make(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 3441 "parser.cpp"
    break;

  case 217: // expr_paren: "(" expr ")"
#line 860 "parser.ypp"
        { yylhs.value.as < expr_paren::ptr > () = expr_paren::make(yylhs.location, std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3447 "parser.cpp"
    break;

  case 218: // expr_object: expr_call
#line 864 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3453 "parser.cpp"
    break;

  case 219: // expr_object: expr_method
#line 865 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3459 "parser.cpp"
    break;

  case 220: // expr_object: expr_array
#line 866 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3465 "parser.cpp"
    break;

  case 221: // expr_object: expr_field
#line 867 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3471 "parser.cpp"
    break;

  case 222: // expr_object: expr_game
#line 868 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3477 "parser.cpp"
    break;

  case 223: // expr_object: expr_self
#line 869 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3483 "parser.cpp"
    break;

  case 224: // expr_object: expr_anim
#line 870 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3489 "parser.cpp"
    break;

  case 225: // expr_object: expr_level
#line 871 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3495 "parser.cpp"
    break;

  case 226: // expr_object: expr_identifier
#line 872 "parser.ypp"
                      { yylhs.value.as < expr::ptr > () = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3501 "parser.cpp"
    break;

  case 227: // expr_thisthread: "thisthread"
#line 877 "parser.ypp"
        { yylhs.value.as < expr_thisthread::ptr > () = expr_thisthread::make(yylhs.location); }
#line 3507 "parser.cpp"
    break;

  case 228: // expr_empty_array: "[" "]"
#line 882 "parser.ypp"
        { yylhs.value.as < expr_empty_array::ptr > () = expr_empty_array::make(yylhs.location); }
#line 3513 "parser.cpp"
    break;

  case 229: // expr_undefined: "undefined"
#line 887 "parser.ypp"
        { yylhs.value.as < expr_undefined::ptr > () = expr_undefined::make(yylhs.location); }
#line 3519 "parser.cpp"
    break;

  case 230: // expr_game: "game"
#line 892 "parser.ypp"
        { yylhs.value.as < expr_game::ptr > () = expr_game::make(yylhs.location); }
#line 3525 "parser.cpp"
    break;

  case 231: // expr_self: "self"
#line 897 "parser.ypp"
        { yylhs.value.as < expr_self::ptr > () = expr_self::make(yylhs.location); }
#line 3531 "parser.cpp"
    break;

  case 232: // expr_anim: "anim"
#line 902 "parser.ypp"
        { yylhs.value.as < expr_anim::ptr > () = expr_anim::make(yylhs.location); }
#line 3537 "parser.cpp"
    break;

  case 233: // expr_level: "level"
#line 907 "parser.ypp"
        { yylhs.value.as < expr_level::ptr > () = expr_level::make(yylhs.location); }
#line 3543 "parser.cpp"
    break;

  case 234: // expr_animation: "%" "identifier"
#line 912 "parser.ypp"
        { yylhs.value.as < expr_animation::ptr > () = expr_animation::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3549 "parser.cpp"
    break;

  case 235: // expr_animtree: "#animtree"
#line 917 "parser.ypp"
        { yylhs.value.as < expr_animtree::ptr > () = expr_animtree::make(yylhs.location); }
#line 3555 "parser.cpp"
    break;

  case 236: // expr_identifier_nosize: "identifier"
#line 922 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3561 "parser.cpp"
    break;

  case 237: // expr_identifier: "identifier"
#line 927 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3567 "parser.cpp"
    break;

  case 238: // expr_identifier: "size"
#line 929 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = expr_identifier::make(yylhs.location, "size"); }
#line 3573 "parser.cpp"
    break;

  case 239: // expr_path: "identifier"
#line 934 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3579 "parser.cpp"
    break;

  case 240: // expr_path: "path"
#line 936 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = expr_path::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3585 "parser.cpp"
    break;

  case 241: // expr_istring: "localized string"
#line 941 "parser.ypp"
        { yylhs.value.as < expr_istring::ptr > () = expr_istring::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3591 "parser.cpp"
    break;

  case 242: // expr_string: "string literal"
#line 946 "parser.ypp"
        { yylhs.value.as < expr_string::ptr > () = expr_string::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3597 "parser.cpp"
    break;

  case 243: // expr_vector: "(" expr "," expr "," expr ")"
#line 951 "parser.ypp"
        { yylhs.value.as < expr_vector::ptr > () = expr_vector::make(yylhs.location, std::move(yystack_[5].value.as < expr::ptr > ()), std::move(yystack_[3].value.as < expr::ptr > ()), std::move(yystack_[1].value.as < expr::ptr > ())); }
#line 3603 "parser.cpp"
    break;

  case 244: // expr_float: "-" "float"
#line 956 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3609 "parser.cpp"
    break;

  case 245: // expr_float: "float"
#line 958 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = expr_float::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3615 "parser.cpp"
    break;

  case 246: // expr_integer: "-" "integer"
#line 963 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3621 "parser.cpp"
    break;

  case 247: // expr_integer: "integer"
#line 965 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = expr_integer::make(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3627 "parser.cpp"
    break;

  case 248: // expr_false: "false"
#line 970 "parser.ypp"
        { yylhs.value.as < expr_false::ptr > () = expr_false::make(yylhs.location); }
#line 3633 "parser.cpp"
    break;

  case 249: // expr_true: "true"
#line 975 "parser.ypp"
        { yylhs.value.as < expr_true::ptr > () = expr_true::make(yylhs.location); }
#line 3639 "parser.cpp"
    break;


#line 3643 "parser.cpp"

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
    "end of file", "error", "invalid token", "#", "/#", "#/", "#inline",
  "#include", "#using_animtree", "#animtree", "endon", "notify", "wait",
  "waittill", "waittillmatch", "waittillframeend", "waitframe", "if",
  "else", "do", "while", "for", "foreach", "in", "switch", "case",
  "default", "break", "continue", "return", "breakpoint", "prof_begin",
  "prof_end", "assert", "assertex", "assertmsg", "thread", "childthread",
  "thisthread", "call", "true", "false", "undefined", "size", "game",
  "self", "anim", "level", "isdefined", "istrue", "(", ")", "{", "}", "[",
  "]", ",", ".", "..", "...", "::", ":", ";", "?", "++", "--", "<<", ">>",
  "||", "&&", "==", "!=", "<=", ">=", "<", ">", "!", "~", "=", "+=", "-=",
  "*=", "/=", "%=", "|=", "&=", "^=", ">>=", "<<=", "|", "&", "^", "+",
  "-", "*", "/", "%", "path", "identifier", "string literal",
  "localized string", "float", "integer", "SIZEOF", "ADD_ARRAY", "THEN",
  "TERN", "NEG", "ANIMREF", "PREINC", "PREDEC", "POSTINC", "POSTDEC",
  "$accept", "root", "program", "inline", "include", "declaration",
  "decl_usingtree", "decl_constant", "decl_function", "stmt",
  "stmt_or_dev", "stmt_list", "stmt_or_dev_list", "stmt_dev", "stmt_comp",
  "stmt_expr", "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify",
  "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_waitframe", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch",
  "stmt_case", "stmt_default", "stmt_break", "stmt_continue",
  "stmt_return", "stmt_breakpoint", "stmt_prof_begin", "stmt_prof_end",
  "stmt_assert", "stmt_assertex", "stmt_assertmsg", "expr",
  "expr_or_empty", "expr_increment", "expr_decrement", "expr_assign",
  "expr_ternary", "expr_binary", "expr_primitive", "expr_complement",
  "expr_negate", "expr_not", "expr_call", "expr_method", "expr_function",
  "expr_pointer", "expr_add_array", "expr_parameters", "expr_arguments",
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

#if GSCDEBUG
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
#if GSCDEBUG
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
#if GSCDEBUG
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


  const short parser::yypact_ninf_ = -309;

  const short parser::yytable_ninf_ = -240;

  const short
  parser::yypact_[] =
  {
      17,  -309,  -309,   -62,   -62,   -46,  -309,  -309,  -309,    20,
      26,  -309,  -309,  -309,  -309,  -309,  -309,    -4,  -309,  -309,
      -1,     4,   -31,  -309,  -309,  -309,  -309,  -309,   -26,  1214,
    -309,  -309,  -309,    22,   -12,  -309,  -309,   -35,   -27,  -309,
      23,  -309,  -309,  -309,  -309,  -309,  -309,  -309,    31,    37,
    1214,  1076,   -26,  1214,  1214,    39,     2,    51,  -309,  -309,
    -309,  2157,  -309,  -309,  -309,  -309,  -309,  -309,    55,   245,
    -309,  -309,  -309,  -309,  -309,  -309,   496,   641,  -309,  -309,
     688,  -309,  -309,  -309,   885,  1241,  1318,  1406,  -309,  -309,
     403,    59,  -309,    53,  -309,  -309,  -309,  -309,  -309,    70,
      86,   -26,    93,   119,    90,   118,   153,   127,   151,  1214,
    1214,  1449,  1076,  -309,  2240,   150,   152,  -309,  -309,  -309,
    1214,   154,  -309,  -309,  -309,  -309,   496,   641,  -309,  1416,
    -309,  -309,  -309,  -309,   403,   155,  -309,  -309,  1214,  1214,
    1214,  1214,  1214,  1214,  1214,  1214,  1214,  1214,  1214,  1214,
    1214,  1214,  1214,  1214,  1214,  1214,  1214,  1283,    -3,  -309,
    -309,   160,  1214,   -26,   168,  -309,   745,  -309,  -309,  1214,
    1214,   -26,  1214,  1214,   -26,  1214,  1600,  1634,  -309,  1214,
    1877,  1214,  -309,  1647,  1214,   114,   -26,  2122,   138,   138,
    1275,  1482,  1066,  1066,    50,    50,    50,    50,  1528,  2281,
    2271,    66,    66,  -309,  -309,  -309,  1919,  -309,  -309,  -309,
      -2,  -309,   166,  -309,   989,  1214,   156,    -9,   167,  1374,
     171,   172,   175,   176,    28,   174,   165,   178,  1145,   179,
     187,   193,   194,   195,   197,  -309,    60,  -309,   552,   552,
    -309,  -309,   933,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,   189,   191,   192,   196,   198,   184,  -309,  -309,
     815,   160,  1961,    57,   207,  2003,    67,   215,  2045,  -309,
    -309,  2086,   173,  2240,  1877,   166,  1214,  -309,  -309,  1214,
    -309,  -309,  -309,  1045,  2192,  -309,   218,  -309,  1214,   252,
    1214,  1172,   -26,  1214,   185,   212,   216,  -309,  -309,  -309,
    -309,  2227,  -309,  1214,  1214,  1214,  1214,  1214,  1283,   -13,
    -309,    79,   144,     1,  1416,  1416,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  1214,   228,   241,   242,   243,  -309,
    -309,  1214,  1214,  1214,  1214,  1214,  1214,  1214,  1214,  1214,
    1214,  1214,   239,  -309,  1214,   246,  -309,  1214,   250,  1214,
     247,  2240,    69,  -309,  -309,  -309,  -309,   248,  1681,   257,
    1694,   253,  -309,  -309,  -309,  1397,   -11,  1728,  -309,  -309,
    -309,    75,    77,    98,   100,   108,  -309,   552,  2240,  1214,
    1214,  1214,  1214,  2240,  2240,  2240,  2240,  2240,  2240,  2240,
    2240,  2240,  2240,  2240,   258,   122,   259,   133,   267,  1741,
    1214,  -309,  -309,  1374,  1214,  1374,  1214,  1214,   -26,    86,
     256,   260,   261,   262,   263,  -309,  1775,  1495,  1541,  1587,
    1214,  -309,  1214,  -309,  1214,  -309,   134,   302,  1788,  -309,
    2240,   264,  1822,   305,  -309,  -309,  -309,  -309,  -309,  -309,
     275,   276,  1214,   284,  1214,   285,  1214,   137,   140,   146,
    -309,  1374,   286,  1172,  1374,  1214,  -309,  -309,   278,  -309,
     303,  -309,   306,  -309,  -309,  -309,  -309,  -309,   329,  -309,
    1835,   294,   320,   321,  1374,  1374,  -309,  -309,  -309,  -309,
    -309
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    14,    15,     0,     0,     0,   238,     8,   237,     0,
       2,     9,    10,    11,    16,    17,    18,     0,   240,   239,
       0,     0,     0,     1,     4,     5,     6,     7,   198,     0,
      12,    13,   242,     0,     0,   197,   235,     0,     0,   227,
       0,   249,   248,   229,   230,   231,   232,   233,     0,     0,
       0,   200,     0,     0,     0,     0,     0,   237,   241,   245,
     247,     0,   105,   106,   107,   145,   146,   147,   148,   149,
     181,   182,   150,   151,   152,   153,   154,   155,   156,   157,
       0,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,     0,   168,   169,   170,   171,   172,   173,   174,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   200,   228,   202,     0,   199,   205,   180,   175,
       0,     0,   244,   246,   218,   219,   178,   179,   177,     0,
     222,   223,   224,   225,   176,     0,   234,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   183,
     184,     0,   200,     0,     0,    19,     0,    21,   196,     0,
     200,     0,     0,   200,     0,     0,     0,     0,   217,     0,
     202,     0,   195,     0,     0,     0,     0,     0,   138,   139,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   140,   141,   142,   143,   144,     0,   215,   236,   214,
       0,   199,   206,   216,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    63,     0,    59,     0,     0,
      50,    57,     0,    51,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,     0,     0,     0,   218,   219,     0,   220,   221,
       0,   226,     0,     0,     0,     0,     0,     0,     0,   203,
     204,     0,     0,   201,     0,     0,     0,   213,   185,   200,
      61,    55,    53,     0,     0,    81,     0,    82,     0,     0,
       0,    67,     0,     0,     0,     0,     0,    94,    95,    96,
      98,     0,    99,   200,   200,   200,   200,   200,     0,     0,
     209,   220,   221,   226,   110,   112,    62,    58,    56,    71,
      72,    70,    68,    69,     0,     0,     0,     0,     0,   111,
     113,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   187,   200,     0,   189,   200,     0,     0,
       0,   126,     0,    60,    54,    52,    76,     0,     0,     0,
       0,     0,    65,    66,    64,     0,     0,     0,    93,    92,
      97,     0,     0,     0,     0,     0,   207,     0,   114,     0,
       0,     0,     0,   115,   121,   122,   123,   124,   125,   116,
     117,   118,   120,   119,     0,     0,     0,     0,     0,     0,
     200,   186,    83,     0,     0,     0,   109,     0,     0,     0,
       0,     0,     0,     0,     0,   208,     0,     0,     0,     0,
     200,   188,   200,   190,   200,   243,     0,    84,     0,    86,
     108,     0,     0,     0,    91,   100,   101,   102,   103,   104,
       0,     0,   200,     0,   200,     0,   200,     0,     0,     0,
     191,     0,     0,    67,     0,     0,    73,    75,   199,    78,
     199,    80,   199,   192,   193,   194,    85,    87,     0,    89,
       0,     0,     0,     0,     0,     0,    74,    77,    79,    88,
      90
  };

  const short
  parser::yypgoto_[] =
  {
    -309,  -309,  -309,   374,   376,   377,  -309,  -309,  -309,  -155,
     147,  -309,  -309,  -309,   -93,   -85,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,  -309,
    -309,  -309,  -309,   221,  -309,  -308,  -306,  -296,  -309,  -309,
    -309,  -309,  -309,  -309,   -44,    47,   -79,   -71,  -309,  -309,
    -144,   -45,  -309,  -309,  -309,  -309,  -309,    -6,   113,   240,
    -309,   337,   249,  -309,  -309,  -309,   390,   397,   437,   452,
    -309,  -309,  -309,     0,    10,  -309,   -20,  -309,  -309,   170,
    -309,  -309
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     9,    10,    11,    12,    13,    14,    15,    16,   240,
     241,   303,   242,   243,   244,   381,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   114,   451,   272,   273,   274,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    34,
     115,   211,    73,    74,    75,   277,   329,   330,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,   209,    90,    91,    92,    93,    94,    95,    96,
      97,    98
  };

  const short
  parser::yytable_[] =
  {
      17,   159,    33,   382,    22,   383,   116,   167,     6,   160,
      17,   124,   427,    20,    21,   384,     6,     6,   210,   102,
      23,     1,     2,     3,     4,     5,   283,   105,    35,   286,
       1,     2,     3,     4,     5,    18,    19,   103,   106,   100,
     207,   306,   396,   397,   101,   428,    28,   104,   107,   298,
     159,   162,   117,   307,   181,   134,  -212,  -212,   160,   302,
       6,    30,    18,    57,   309,   135,    31,   116,    32,     6,
      18,    57,     8,    99,    29,    37,    38,   108,    40,     7,
     161,   109,     6,    44,    45,    46,    47,   110,    24,   120,
     135,  -218,  -218,   121,  -218,   208,    37,    38,  -218,    40,
     136,   168,   125,     6,    44,    45,    46,    47,   363,  -218,
     164,  -239,  -218,   181,   328,     8,   139,   140,   366,   163,
     421,   314,   275,   181,     8,   181,   430,    32,   431,   161,
      60,   181,   165,   181,  -210,  -210,    18,    57,   166,   135,
     122,   123,   152,   153,   154,   155,   156,   169,   375,   432,
     171,   433,  -218,  -218,   181,   372,   181,    18,    57,   434,
     154,   155,   156,   212,   181,   382,   281,   383,   126,   170,
     275,   284,   172,   441,   287,   275,   135,   384,   181,   391,
     392,   393,   394,   395,   443,   470,   295,   174,   483,   181,
     181,   484,   124,   181,   124,   124,   181,   485,   275,  -211,
    -211,   159,   181,   173,   315,   175,   181,   182,   184,   160,
     162,   213,   208,   276,   281,   186,   299,   308,   305,   281,
     415,   310,   311,   417,   135,   312,   313,   318,   370,   135,
     152,   153,   154,   155,   156,   317,   333,   323,   281,   281,
     319,   322,   281,   324,   325,   326,   135,   327,   135,   135,
      61,   339,   135,   340,   341,   159,   159,   364,   342,   275,
     343,   276,   344,   160,   160,   367,   276,   124,   447,   377,
     449,   111,   379,   388,   118,   119,   446,   389,   399,   278,
     161,  -219,  -219,   125,  -219,   125,   125,   123,  -219,   276,
     135,   400,   401,   402,   414,   127,   467,   420,   468,  -219,
     469,   416,  -219,   281,   129,   418,   159,   424,   440,   442,
     422,   281,   386,   135,   160,   426,   486,   444,   455,   489,
     471,   135,   456,   457,   458,   459,   473,   278,   475,   491,
     176,   177,   278,   180,   161,   161,   454,   476,   477,   499,
     500,   183,  -219,  -219,   135,   135,   479,   481,   487,   331,
     276,   278,   278,   124,   492,   278,   496,   493,   125,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   275,
     494,   275,   497,   498,    25,   161,    26,    27,   488,   338,
     282,   435,   128,   285,   316,   135,   288,   333,     0,     0,
     291,     0,   293,     0,     0,   294,   279,   135,     0,     0,
       0,     0,     0,     0,     0,   280,   278,   478,     0,   480,
       0,   482,     0,   281,   278,   281,     0,   275,   453,   124,
     275,     0,     0,   135,     0,   135,   304,     0,     0,  -226,
    -226,     0,  -226,     0,   125,   130,  -226,     0,     0,   321,
     275,   275,   131,   162,   279,     0,     0,  -226,     0,   279,
    -226,     0,     0,   280,     0,     0,     0,     0,   280,     0,
     276,   281,   276,   281,   281,     0,   332,     0,   279,   279,
       0,   135,   279,   135,   135,   129,     0,   334,   335,     0,
       0,   280,   132,     0,   281,   281,     0,     0,     0,     0,
    -226,  -226,     0,     0,   135,   135,     0,   133,     0,     0,
     331,     0,     0,     0,     0,     0,     0,   371,   276,     0,
     125,   276,     0,     0,     0,     0,     0,     0,     0,   378,
       0,   380,  -220,  -220,   387,  -220,   278,     0,   278,  -220,
       0,   276,   276,   279,     0,     0,     0,     0,     0,   294,
    -220,   279,   280,  -220,     0,     0,   130,     0,     0,     0,
     385,     0,     0,   131,     0,   398,     0,     0,     0,     0,
       0,     0,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,     0,   278,     0,   278,   278,    37,    38,
     419,    40,     0,  -220,  -220,     6,    44,    45,    46,    47,
       0,     0,     0,   132,   130,     0,   121,   278,   278,   130,
       0,   131,     0,     0,     0,     0,   131,     0,   133,     0,
     436,   437,   438,   439,     0,     0,   130,     0,   130,   130,
       0,     0,   130,   131,     0,   131,   131,   332,     0,   131,
       0,     0,     0,     0,     0,   448,   129,   450,   452,    18,
      57,   132,     0,     0,     0,     0,   132,     0,     0,     0,
       0,     0,     0,   279,     0,   279,   133,     0,     0,     0,
       0,   133,   280,   132,   280,   132,   132,  -221,  -221,   132,
    -221,     0,     0,     0,  -221,     0,     0,     0,   133,     0,
     133,   133,     0,   130,   133,  -221,   490,     0,  -221,     0,
     131,   130,     0,     0,     0,     0,     0,     0,   131,     0,
       0,   279,     0,   279,   279,     0,     0,     0,     0,     0,
     280,     0,   385,   280,    37,    38,     0,    40,     0,     0,
       0,     6,     0,     0,   279,   279,     0,     0,  -221,  -221,
     132,     0,   157,   280,   280,   158,     0,     0,   132,   214,
       0,     0,     0,     0,     0,   133,     0,   215,     0,     0,
     216,   217,   218,   133,   219,   220,   221,   222,     0,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,    37,    38,     0,    40,    18,    57,   130,     6,    44,
      45,    46,    47,     0,   131,     0,     0,   166,   235,   236,
       0,     0,     0,     0,     0,     0,     0,   237,     0,   238,
     239,     0,     0,   130,     0,   130,     0,     0,     0,     0,
     131,     0,   131,     0,     0,   345,   346,     0,   347,   348,
       0,     0,     0,     0,   132,     0,     0,     0,     0,     0,
       0,     0,    18,    57,     0,     0,     0,     0,     0,   133,
       0,    37,    38,     0,    40,     0,     0,     0,     6,     0,
     132,   130,   132,   130,   130,     0,     0,     0,   131,   157,
     131,   131,   185,     0,     0,   133,     0,   133,     0,   349,
     350,     0,     0,     0,   130,   130,     0,     0,     0,     0,
       0,   131,   131,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,     0,     0,     0,     0,   132,     0,
     132,   132,    18,    57,     0,     0,     0,     0,     0,     0,
       0,  -222,  -222,   133,  -222,   133,   133,     0,  -222,     0,
       0,   132,   132,     0,     0,     0,     0,   214,     0,  -222,
       0,     0,  -222,     0,     0,   215,   133,   133,   216,   217,
     218,     0,   219,   220,   221,   222,     0,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,    37,
      38,     0,    40,     0,     0,     0,     6,    44,    45,    46,
      47,     0,  -222,  -222,     0,   166,   336,   236,     0,     0,
       0,     0,     0,     0,   300,   337,     0,   238,   239,     0,
       0,   215,     0,     0,   216,   217,   218,     0,   219,   220,
     221,   222,     0,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,    37,    38,     0,    40,     0,
      18,    57,     6,    44,    45,    46,    47,     0,     0,     0,
       0,   166,     0,   236,     0,     0,     0,     0,     0,     0,
     373,   301,     0,   238,   239,     0,     0,   215,     0,     0,
     216,   217,   218,     0,   219,   220,   221,   222,     0,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,    37,    38,     0,    40,    36,    18,    57,     6,    44,
      45,    46,    47,     0,     0,     0,     0,   166,     0,   236,
       0,     0,     0,     0,     0,     0,     0,   374,     0,   238,
     239,     0,    37,    38,    39,    40,    41,    42,    43,     6,
      44,    45,    46,    47,    48,    49,    50,     0,     0,     0,
     112,   113,   139,   140,     0,     0,    52,     0,   145,   146,
     147,   148,    18,    57,     0,     0,     0,     0,     0,     0,
       0,     0,    53,    54,    36,     0,     0,     0,   152,   153,
     154,   155,   156,     0,     0,     0,     0,     0,     0,    55,
       0,     0,    56,    18,    57,    32,    58,    59,    60,     0,
       0,    37,    38,    39,    40,    41,    42,    43,     6,    44,
      45,    46,    47,    48,    49,    50,     0,     0,     0,    51,
       0,     0,     0,     0,     0,    52,     0,   320,    37,    38,
       0,    40,     0,     0,     0,     6,    44,    45,    46,    47,
       0,    53,    54,    36,     0,     0,   236,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   238,   239,    55,     0,
       0,    56,    18,    57,    32,    58,    59,    60,     0,     0,
      37,    38,    39,    40,    41,    42,    43,     6,    44,    45,
      46,    47,    48,    49,    50,     0,     0,     0,    51,    18,
      57,     0,     0,     0,    52,     0,     0,  -223,  -223,     0,
    -223,     0,     0,     0,  -223,     0,     0,     0,     0,     0,
      53,    54,    36,     0,     0,  -223,     0,     0,  -223,     0,
       0,     0,     0,     0,     0,     0,     0,    55,     0,     0,
      56,    18,    57,    32,    58,    59,    60,     0,     0,    37,
      38,    39,    40,    41,    42,    43,     6,    44,    45,    46,
      47,    48,    49,    50,     0,     0,     0,   112,  -223,  -223,
       0,   139,   140,    52,   142,   143,   144,   145,   146,   147,
     148,     0,     0,     0,  -224,  -224,     0,  -224,     0,    53,
      54,  -224,     0,     0,   149,   150,   151,   152,   153,   154,
     155,   156,  -224,     0,     0,  -224,    55,     0,     0,    56,
      18,    57,    32,    58,    59,    60,   215,     0,     0,   216,
     217,   218,     0,   219,   220,   221,   222,     0,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
      37,    38,     0,    40,     0,  -224,  -224,     6,    44,    45,
      46,    47,     0,     0,     0,     0,   166,     0,   236,     0,
       0,     0,     0,    37,    38,     0,    40,     0,   238,   239,
       6,     0,  -225,  -225,     0,  -225,     0,     0,     0,  -225,
       0,   157,    37,    38,   185,    40,     0,     0,     0,     6,
    -225,   349,   350,  -225,     0,     0,     0,     0,     0,     0,
     157,    18,    57,   185,     0,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,     0,     0,     0,     0,
       0,     0,     0,     0,    18,    57,     0,     0,     0,     0,
     178,     0,     0,  -225,  -225,   179,     0,     0,     0,     0,
       0,     0,   138,    18,    57,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,   150,
     151,   152,   153,   154,   155,   156,   461,     0,   139,   140,
       0,   462,   143,   144,   145,   146,   147,   148,   138,     0,
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
       0,     0,     0,     0,   149,   150,   151,   152,   153,   154,
     155,   156,   463,     0,   139,   140,     0,   464,   143,   144,
     145,   146,   147,   148,   138,     0,     0,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,     0,   150,   151,
     152,   153,   154,   155,   156,     0,     0,     0,     0,     0,
     149,   150,   151,   152,   153,   154,   155,   156,   465,     0,
       0,     0,     0,   466,     0,     0,     0,     0,     0,     0,
     138,   289,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   138,     0,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,   290,     0,     0,     0,   149,
     150,   151,   152,   153,   154,   155,   156,   138,   178,     0,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     138,     0,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,   423,     0,     0,     0,   149,   150,   151,   152,
     153,   154,   155,   156,   138,   425,     0,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   138,     0,     0,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,     0,   429,
       0,     0,     0,   149,   150,   151,   152,   153,   154,   155,
     156,   138,   445,     0,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   138,     0,     0,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   460,     0,     0,     0,
     149,   150,   151,   152,   153,   154,   155,   156,   138,   472,
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   138,     0,     0,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   474,     0,     0,     0,   149,   150,   151,
     152,   153,   154,   155,   156,   138,   495,     0,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   138,     0,
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
       0,     0,     0,     0,   149,   150,   151,   152,   153,   154,
     155,   156,   292,     0,     0,     0,     0,     0,     0,     0,
     138,     0,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   149,   150,   151,   152,
     153,   154,   155,   156,   297,     0,     0,     0,     0,     0,
       0,     0,   138,     0,     0,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,   150,
     151,   152,   153,   154,   155,   156,   362,     0,     0,     0,
       0,     0,     0,     0,   138,     0,     0,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     149,   150,   151,   152,   153,   154,   155,   156,   365,     0,
       0,     0,     0,     0,     0,     0,   138,     0,     0,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   149,   150,   151,   152,   153,   154,   155,   156,
     368,     0,     0,     0,     0,     0,     0,     0,   138,     0,
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   149,   150,   151,   152,   153,   154,
     155,   156,   369,     0,     0,     0,     0,     0,     0,   138,
       0,     0,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   149,   150,   151,   152,   153,
     154,   155,   156,   296,     0,   138,     0,     0,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,   153,   154,   155,   156,   137,
     138,     0,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   149,   150,   151,   152,
     153,   154,   155,   156,   376,   138,     0,     0,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,   153,   154,   155,   156,   390,
     138,     0,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   138,     0,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,     0,     0,     0,     0,   149,
     150,   151,   152,   153,   154,   155,   156,   139,   140,     0,
       0,   143,   144,   145,   146,   147,   148,   139,   140,     0,
       0,   143,   144,   145,   146,   147,   148,     0,     0,     0,
       0,   150,     0,   152,   153,   154,   155,   156,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156
  };

  const short
  parser::yycheck_[] =
  {
       0,    80,    22,   311,    50,   311,    51,   100,    43,    80,
      10,    55,    23,     3,     4,   311,    43,    43,   162,    54,
       0,     4,     5,     6,     7,     8,   170,    54,    28,   173,
       4,     5,     6,     7,     8,    97,    98,    37,    38,    51,
      43,    50,    55,    56,    56,    56,    50,    37,    38,    51,
     129,    50,    52,    62,    56,    55,    55,    56,   129,   214,
      43,    62,    97,    98,   219,    55,    62,   112,    99,    43,
      97,    98,    98,    51,    78,    36,    37,    54,    39,    62,
      80,    50,    43,    44,    45,    46,    47,    50,    62,    50,
      80,    36,    37,    54,    39,    98,    36,    37,    43,    39,
      98,   101,    55,    43,    44,    45,    46,    47,    51,    54,
      57,    60,    57,    56,    54,    98,    66,    67,    51,    60,
      51,    93,   166,    56,    98,    56,    51,    99,    51,   129,
     102,    56,    62,    56,    55,    56,    97,    98,    52,   129,
     101,   102,    92,    93,    94,    95,    96,    54,   303,    51,
      60,    51,    97,    98,    56,   299,    56,    97,    98,    51,
      94,    95,    96,   163,    56,   473,   166,   473,    55,    50,
     214,   171,    54,    51,   174,   219,   166,   473,    56,   323,
     324,   325,   326,   327,    51,    51,   186,    60,    51,    56,
      56,    51,   236,    56,   238,   239,    56,    51,   242,    55,
      56,   280,    56,    50,   224,    54,    56,    55,    54,   280,
      50,    43,    98,   166,   214,    60,    50,    50,    62,   219,
     364,    50,    50,   367,   214,    50,    50,    62,    55,   219,
      92,    93,    94,    95,    96,    61,   236,    50,   238,   239,
      62,    62,   242,    50,    50,    50,   236,    50,   238,   239,
      29,    62,   242,    62,    62,   334,   335,    50,    62,   303,
      62,   214,    78,   334,   335,    50,   219,   311,   423,    51,
     425,    50,    20,    61,    53,    54,   420,    61,    50,   166,
     280,    36,    37,   236,    39,   238,   239,   102,    43,   242,
     280,    50,    50,    50,    55,    55,   440,    50,   442,    54,
     444,    55,    57,   303,    55,    55,   385,    50,    50,    50,
      62,   311,   312,   303,   385,    62,   471,    50,    62,   474,
      18,   311,    62,    62,    62,    62,    62,   214,    23,    51,
     109,   110,   219,   112,   334,   335,   429,    62,    62,   494,
     495,   120,    97,    98,   334,   335,    62,    62,    62,   236,
     303,   238,   239,   397,    51,   242,    62,    51,   311,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   423,
      51,   425,    62,    62,    10,   385,    10,    10,   473,   242,
     169,   397,    55,   172,   224,   385,   175,   397,    -1,    -1,
     179,    -1,   181,    -1,    -1,   184,   166,   397,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   166,   303,   462,    -1,   464,
      -1,   466,    -1,   423,   311,   425,    -1,   471,   428,   473,
     474,    -1,    -1,   423,    -1,   425,   215,    -1,    -1,    36,
      37,    -1,    39,    -1,   397,    55,    43,    -1,    -1,   228,
     494,   495,    55,    50,   214,    -1,    -1,    54,    -1,   219,
      57,    -1,    -1,   214,    -1,    -1,    -1,    -1,   219,    -1,
     423,   471,   425,   473,   474,    -1,   236,    -1,   238,   239,
      -1,   471,   242,   473,   474,   236,    -1,   238,   239,    -1,
      -1,   242,    55,    -1,   494,   495,    -1,    -1,    -1,    -1,
      97,    98,    -1,    -1,   494,   495,    -1,    55,    -1,    -1,
     397,    -1,    -1,    -1,    -1,    -1,    -1,   296,   471,    -1,
     473,   474,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   308,
      -1,   310,    36,    37,   313,    39,   423,    -1,   425,    43,
      -1,   494,   495,   303,    -1,    -1,    -1,    -1,    -1,   328,
      54,   311,   303,    57,    -1,    -1,   166,    -1,    -1,    -1,
     311,    -1,    -1,   166,    -1,   344,    -1,    -1,    -1,    -1,
      -1,    -1,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,    -1,   471,    -1,   473,   474,    36,    37,
     369,    39,    -1,    97,    98,    43,    44,    45,    46,    47,
      -1,    -1,    -1,   166,   214,    -1,    54,   494,   495,   219,
      -1,   214,    -1,    -1,    -1,    -1,   219,    -1,   166,    -1,
     399,   400,   401,   402,    -1,    -1,   236,    -1,   238,   239,
      -1,    -1,   242,   236,    -1,   238,   239,   397,    -1,   242,
      -1,    -1,    -1,    -1,    -1,   424,   397,   426,   427,    97,
      98,   214,    -1,    -1,    -1,    -1,   219,    -1,    -1,    -1,
      -1,    -1,    -1,   423,    -1,   425,   214,    -1,    -1,    -1,
      -1,   219,   423,   236,   425,   238,   239,    36,    37,   242,
      39,    -1,    -1,    -1,    43,    -1,    -1,    -1,   236,    -1,
     238,   239,    -1,   303,   242,    54,   475,    -1,    57,    -1,
     303,   311,    -1,    -1,    -1,    -1,    -1,    -1,   311,    -1,
      -1,   471,    -1,   473,   474,    -1,    -1,    -1,    -1,    -1,
     471,    -1,   473,   474,    36,    37,    -1,    39,    -1,    -1,
      -1,    43,    -1,    -1,   494,   495,    -1,    -1,    97,    98,
     303,    -1,    54,   494,   495,    57,    -1,    -1,   311,     4,
      -1,    -1,    -1,    -1,    -1,   303,    -1,    12,    -1,    -1,
      15,    16,    17,   311,    19,    20,    21,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    39,    97,    98,   397,    43,    44,
      45,    46,    47,    -1,   397,    -1,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,
      65,    -1,    -1,   423,    -1,   425,    -1,    -1,    -1,    -1,
     423,    -1,   425,    -1,    -1,    10,    11,    -1,    13,    14,
      -1,    -1,    -1,    -1,   397,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,    98,    -1,    -1,    -1,    -1,    -1,   397,
      -1,    36,    37,    -1,    39,    -1,    -1,    -1,    43,    -1,
     423,   471,   425,   473,   474,    -1,    -1,    -1,   471,    54,
     473,   474,    57,    -1,    -1,   423,    -1,   425,    -1,    64,
      65,    -1,    -1,    -1,   494,   495,    -1,    -1,    -1,    -1,
      -1,   494,   495,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    -1,    -1,    -1,    -1,   471,    -1,
     473,   474,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,   471,    39,   473,   474,    -1,    43,    -1,
      -1,   494,   495,    -1,    -1,    -1,    -1,     4,    -1,    54,
      -1,    -1,    57,    -1,    -1,    12,   494,   495,    15,    16,
      17,    -1,    19,    20,    21,    22,    -1,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    39,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    -1,    97,    98,    -1,    52,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,     5,    62,    -1,    64,    65,    -1,
      -1,    12,    -1,    -1,    15,    16,    17,    -1,    19,    20,
      21,    22,    -1,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    -1,
      97,    98,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    62,    -1,    64,    65,    -1,    -1,    12,    -1,    -1,
      15,    16,    17,    -1,    19,    20,    21,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    39,     9,    97,    98,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,
      65,    -1,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    55,    66,    67,    -1,    -1,    60,    -1,    72,    73,
      74,    75,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,     9,    -1,    -1,    -1,    92,    93,
      94,    95,    96,    -1,    -1,    -1,    -1,    -1,    -1,    93,
      -1,    -1,    96,    97,    98,    99,   100,   101,   102,    -1,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    62,    36,    37,
      -1,    39,    -1,    -1,    -1,    43,    44,    45,    46,    47,
      -1,    76,    77,     9,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    93,    -1,
      -1,    96,    97,    98,    99,   100,   101,   102,    -1,    -1,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    54,    97,
      98,    -1,    -1,    -1,    60,    -1,    -1,    36,    37,    -1,
      39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      76,    77,     9,    -1,    -1,    54,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,
      96,    97,    98,    99,   100,   101,   102,    -1,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    54,    97,    98,
      -1,    66,    67,    60,    69,    70,    71,    72,    73,    74,
      75,    -1,    -1,    -1,    36,    37,    -1,    39,    -1,    76,
      77,    43,    -1,    -1,    89,    90,    91,    92,    93,    94,
      95,    96,    54,    -1,    -1,    57,    93,    -1,    -1,    96,
      97,    98,    99,   100,   101,   102,    12,    -1,    -1,    15,
      16,    17,    -1,    19,    20,    21,    22,    -1,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    -1,    97,    98,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    -1,    36,    37,    -1,    39,    -1,    64,    65,
      43,    -1,    36,    37,    -1,    39,    -1,    -1,    -1,    43,
      -1,    54,    36,    37,    57,    39,    -1,    -1,    -1,    43,
      54,    64,    65,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    97,    98,    57,    -1,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    97,    98,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    97,    98,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    97,    98,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94,    95,    96,    51,    -1,    66,    67,
      -1,    56,    70,    71,    72,    73,    74,    75,    63,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    89,    90,    91,    92,    93,    94,    95,    96,    -1,
      -1,    -1,    -1,    -1,    89,    90,    91,    92,    93,    94,
      95,    96,    51,    -1,    66,    67,    -1,    56,    70,    71,
      72,    73,    74,    75,    63,    -1,    -1,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    -1,    90,    91,
      92,    93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,
      89,    90,    91,    92,    93,    94,    95,    96,    51,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    51,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    63,    -1,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    89,    90,    91,    92,
      93,    94,    95,    96,    -1,    51,    -1,    -1,    -1,    89,
      90,    91,    92,    93,    94,    95,    96,    63,    51,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      63,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    89,    90,    91,    92,    93,    94,    95,
      96,    -1,    51,    -1,    -1,    -1,    89,    90,    91,    92,
      93,    94,    95,    96,    63,    51,    -1,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    63,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      89,    90,    91,    92,    93,    94,    95,    96,    -1,    51,
      -1,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    63,    51,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    63,    -1,    -1,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    89,    90,    91,
      92,    93,    94,    95,    96,    -1,    51,    -1,    -1,    -1,
      89,    90,    91,    92,    93,    94,    95,    96,    63,    51,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    63,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    89,    90,    91,    92,    93,    94,
      95,    96,    -1,    51,    -1,    -1,    -1,    89,    90,    91,
      92,    93,    94,    95,    96,    63,    51,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    63,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    89,    90,    91,    92,    93,    94,    95,    96,    -1,
      -1,    -1,    -1,    -1,    89,    90,    91,    92,    93,    94,
      95,    96,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,    92,
      93,    94,    95,    96,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94,    95,    96,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    90,    91,    92,    93,    94,    95,    96,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    91,    92,    93,    94,    95,    96,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    90,    91,    92,    93,    94,
      95,    96,    56,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    91,    92,    93,
      94,    95,    96,    61,    -1,    63,    -1,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    90,    91,    92,    93,    94,    95,    96,    62,
      63,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,    92,
      93,    94,    95,    96,    62,    63,    -1,    -1,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    90,    91,    92,    93,    94,    95,    96,    62,
      63,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    63,    -1,    -1,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    89,    90,    91,    92,
      93,    94,    95,    96,    -1,    -1,    -1,    -1,    -1,    89,
      90,    91,    92,    93,    94,    95,    96,    66,    67,    -1,
      -1,    70,    71,    72,    73,    74,    75,    66,    67,    -1,
      -1,    70,    71,    72,    73,    74,    75,    -1,    -1,    -1,
      -1,    90,    -1,    92,    93,    94,    95,    96,    -1,    -1,
      -1,    -1,    -1,    92,    93,    94,    95,    96
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     4,     5,     6,     7,     8,    43,    62,    98,   114,
     115,   116,   117,   118,   119,   120,   121,   196,    97,    98,
     197,   197,    50,     0,    62,   116,   117,   118,    50,    78,
      62,    62,    99,   199,   172,   196,     9,    36,    37,    38,
      39,    40,    41,    42,    44,    45,    46,    47,    48,    49,
      50,    54,    60,    76,    77,    93,    96,    98,   100,   101,
     102,   156,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   175,   176,   177,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     196,   197,   198,   199,   200,   201,   202,   203,   204,    51,
      51,    56,    54,   196,   197,    54,   196,   197,    54,    50,
      50,   156,    54,    55,   156,   173,   174,   196,   156,   156,
      50,    54,   101,   102,   167,   168,   181,   182,   184,   185,
     189,   190,   191,   192,   196,   197,    98,    62,    63,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    89,
      90,    91,    92,    93,    94,    95,    96,    54,    57,   169,
     170,   196,    50,    60,    57,    62,    52,   127,   196,    54,
      50,    60,    54,    50,    60,    54,   156,   156,    51,    56,
     156,    56,    55,   156,    54,    57,    60,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,    43,    98,   195,
     173,   174,   196,    43,     4,    12,    15,    16,    17,    19,
      20,    21,    22,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    53,    54,    62,    64,    65,
     122,   123,   125,   126,   127,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   158,   159,   160,   167,   168,   178,   181,   182,
     185,   196,   156,   173,   196,   156,   173,   196,   156,    51,
      51,   156,    55,   156,   156,   196,    61,    55,    51,    50,
       5,    62,   122,   124,   156,    62,    50,    62,    50,   122,
      50,    50,    50,    50,    93,   199,   202,    61,    62,    62,
      62,   156,    62,    50,    50,    50,    50,    50,    54,   179,
     180,   181,   182,   196,   185,   185,    53,    62,   123,    62,
      62,    62,    62,    62,    78,    10,    11,    13,    14,    64,
      65,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    55,    51,    50,    55,    51,    50,    55,    56,
      55,   156,   173,     5,    62,   122,    62,    51,   156,    20,
     156,   128,   158,   159,   160,   185,   196,   156,    61,    61,
      62,   173,   173,   173,   173,   173,    55,    56,   156,    50,
      50,    50,    50,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,    55,   173,    55,   173,    55,   156,
      50,    51,    62,    51,    50,    51,    62,    23,    56,    51,
      51,    51,    51,    51,    51,   180,   156,   156,   156,   156,
      50,    51,    50,    51,    50,    51,   173,   122,   156,   122,
     156,   157,   156,   196,   127,    62,    62,    62,    62,    62,
      51,    51,    56,    51,    56,    51,    56,   173,   173,   173,
      51,    18,    51,    62,    51,    23,    62,    62,   174,    62,
     174,    62,   174,    51,    51,    51,   122,    62,   128,   122,
     156,    51,    51,    51,    51,    51,    62,    62,    62,   122,
     122
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   113,   114,   114,   115,   115,   115,   115,   115,   115,
     115,   115,   116,   117,   118,   118,   118,   118,   118,   119,
     120,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     123,   123,   124,   124,   124,   124,   125,   125,   125,   125,
     126,   126,   127,   127,   128,   128,   128,   128,   129,   129,
     130,   130,   130,   131,   132,   132,   133,   134,   134,   135,
     135,   136,   137,   137,   138,   139,   140,   141,   142,   143,
     143,   144,   145,   145,   146,   147,   148,   149,   149,   150,
     151,   152,   153,   154,   155,   156,   156,   156,   157,   157,
     158,   158,   159,   159,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   161,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   164,   165,   165,   165,   165,
     166,   167,   167,   168,   168,   169,   169,   169,   169,   169,
     169,   170,   170,   170,   170,   171,   172,   172,   172,   173,
     173,   174,   174,   175,   176,   177,   177,   178,   179,   179,
     180,   180,   180,   181,   182,   183,   183,   184,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   196,   197,
     197,   198,   199,   200,   201,   201,   202,   202,   203,   204
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     2,     1,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     1,     5,
       4,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     2,     1,     2,     1,
       3,     2,     3,     2,     1,     1,     1,     0,     2,     2,
       2,     2,     2,     6,     8,     6,     3,     8,     6,     8,
       6,     2,     2,     4,     5,     7,     5,     7,     9,     7,
       9,     5,     3,     3,     2,     2,     2,     3,     2,     2,
       5,     5,     5,     5,     5,     1,     1,     1,     1,     0,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     1,     1,     2,     2,     4,     6,     5,     7,     5,
       7,     8,     9,     9,     9,     3,     3,     1,     0,     1,
       0,     3,     1,     4,     4,     2,     3,     3,     3,     1,
       1,     1,     1,     4,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     7,     2,     1,     2,     1,     1,     1
  };




#if GSCDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   275,   275,   276,   280,   282,   284,   286,   288,   290,
     292,   294,   299,   303,   308,   309,   310,   311,   312,   316,
     321,   329,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     365,   366,   370,   372,   374,   376,   381,   383,   385,   387,
     392,   393,   397,   398,   402,   404,   406,   409,   413,   415,
     420,   422,   424,   429,   434,   436,   441,   446,   448,   453,
     455,   460,   465,   467,   472,   477,   482,   487,   492,   497,
     503,   512,   519,   521,   526,   531,   536,   541,   543,   548,
     553,   558,   563,   568,   573,   578,   579,   580,   584,   585,
     589,   591,   596,   598,   603,   605,   607,   609,   611,   613,
     615,   617,   619,   621,   623,   625,   630,   635,   637,   639,
     641,   643,   645,   647,   649,   651,   653,   655,   657,   659,
     661,   663,   665,   667,   669,   674,   675,   676,   677,   678,
     679,   680,   681,   682,   683,   684,   685,   686,   687,   688,
     689,   690,   691,   692,   693,   694,   695,   696,   697,   698,
     699,   700,   701,   702,   703,   707,   712,   714,   716,   718,
     723,   728,   729,   733,   740,   750,   752,   754,   756,   758,
     760,   765,   767,   769,   771,   776,   781,   783,   786,   790,
     793,   797,   799,   804,   809,   814,   816,   821,   829,   831,
     836,   837,   838,   842,   847,   852,   854,   859,   864,   865,
     866,   867,   868,   869,   870,   871,   872,   876,   881,   886,
     891,   896,   901,   906,   911,   916,   921,   926,   928,   933,
     935,   940,   945,   950,   955,   957,   962,   964,   969,   974
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
#endif // GSCDEBUG


#line 13 "parser.ypp"
} } // xsk::gsc
#line 4943 "parser.cpp"

#line 978 "parser.ypp"


namespace xsk::gsc
{

void parser::error(location const& loc, std::string const& msg)
{
    throw comp_error(loc, msg);
}

auto parse_switch(stmt_switch& stm) -> void
{
    auto body = stmt_list::make(stm.body->block->loc());
    auto curr = stmt::ptr{ nullptr };

    auto num = stm.body->block->list.size();

    for (auto i = 0u; i < num; i++)
    {
        auto& entry = stm.body->block->list[0];

        if (entry->is<stmt_case>() || entry->is<stmt_default>())
        {
            if (curr != nullptr)
            {
                body->list.push_back(std::move(curr));
            }

            curr = std::move(stm.body->block->list[0]);
            stm.body->block->list.erase(stm.body->block->list.begin());
        }
        else
        {
            if (curr != nullptr)
            {
                if (curr->is<stmt_case>())
                {
                    curr->as<stmt_case>().body->list.push_back(std::move(entry));
                    stm.body->block->list.erase(stm.body->block->list.begin());
                }
                else
                {
                    curr->as<stmt_default>().body->list.push_back(std::move(entry));
                    stm.body->block->list.erase(stm.body->block->list.begin());
                }
            }
            else
            {
                throw comp_error(entry->loc(), "missing case statement");
            }
        }
    }

    if (curr != nullptr)
    {
        body->list.push_back(std::move(curr));
    }

    stm.body->block = std::move(body);
}

extern std::unordered_map<token::kind, parser::token::token_kind_type> const tok_to_parser;
extern std::unordered_map<std::string_view, parser::token::token_kind_type> const keyword_map;

auto map_token(context const* ctx_, token& tok) -> parser::symbol_type
{
    if (tok.type == token::NAME)
    {
        tok.data = ctx_->make_token(tok.data);

        auto const it = keyword_map.find(tok.data);

        if (it != keyword_map.end())
        {
            if (it->second == parser::token::WAITFRAME)
            {
                if (ctx_->props() & props::waitframe)
                    return parser::symbol_type(it->second, tok.pos);
            }
            else if (it->second == parser::token::ISDEFINED || it->second == parser::token::ISTRUE)
            {
                if (ctx_->props() & props::boolfuncs)
                {
                    return parser::symbol_type(it->second, tok.pos);
                }
            }
            else
            {
                return parser::symbol_type(it->second, tok.pos);
            }
        }

        return parser::symbol_type(parser::token::IDENTIFIER, std::move(tok.data), tok.pos);
    }
    else if (tok.type == token::PATH ||tok.type == token::STRING ||tok.type == token::ISTRING || tok.type == token::INT ||tok.type == token::FLT)
    {
        auto it = tok_to_parser.find(tok.type);

        if (it != tok_to_parser.end())
        {
            return parser::symbol_type(it->second, std::move(tok.data), tok.pos);
        }
    }
    else
    {
        auto it = tok_to_parser.find(tok.type);

        if (it != tok_to_parser.end())
        {
            return parser::symbol_type(it->second, tok.pos);
        }
    }

    throw error(fmt::format("unmapped token! {}", (u8)tok.type));
}

auto GSClex(context const* ctx_, preprocessor& ppr) -> parser::symbol_type
{
    auto tok = ppr.process();
    return map_token(ctx_, tok);
}

std::unordered_map<token::kind, parser::token::token_kind_type> const tok_to_parser
{{
    { token::NAME, parser::token::IDENTIFIER },
    { token::PATH, parser::token::PATH },
    { token::STRING, parser::token::STRING },
    { token::ISTRING, parser::token::ISTRING },
    { token::INT, parser::token::INTEGER },
    { token::FLT, parser::token::FLOAT },
    { token::PLUS, parser::token::ADD },
    { token::MINUS, parser::token::SUB },
    { token::STAR, parser::token::MUL },
    { token::DIV, parser::token::DIV },
    { token::MOD, parser::token::MOD },
    { token::BITOR, parser::token::BITWISE_OR },
    { token::BITAND, parser::token::BITWISE_AND },
    { token::BITEXOR, parser::token::BITWISE_EXOR },
    { token::ASSIGN, parser::token::ASSIGN },
    { token::PLUSEQ, parser::token::ASSIGN_ADD },
    { token::MINUSEQ, parser::token::ASSIGN_SUB },
    { token::STAREQ, parser::token::ASSIGN_MUL },
    { token::DIVEQ, parser::token::ASSIGN_DIV },
    { token::MODEQ, parser::token::ASSIGN_MOD },
    { token::BITOREQ, parser::token::ASSIGN_BW_OR },
    { token::BITANDEQ, parser::token::ASSIGN_BW_AND },
    { token::BITEXOREQ, parser::token::ASSIGN_BW_EXOR },
    { token::SHLEQ, parser::token::ASSIGN_LSHIFT },
    { token::SHREQ, parser::token::ASSIGN_RSHIFT },
    { token::TILDE, parser::token::COMPLEMENT },
    { token::BANG, parser::token::NOT },
    { token::GT, parser::token::GREATER },
    { token::LT, parser::token::LESS },
    { token::GE, parser::token::GREATER_EQUAL },
    { token::LE, parser::token::LESS_EQUAL },
    { token::NE, parser::token::INEQUALITY },
    { token::EQ, parser::token::EQUALITY },
    { token::OR, parser::token::OR },
    { token::AND, parser::token::AND },
    { token::SHL, parser::token::LSHIFT },
    { token::SHR, parser::token::RSHIFT },
    { token::INC, parser::token::INCREMENT },
    { token::DEC, parser::token::DECREMENT },
    { token::QMARK, parser::token::QMARK },
    { token::DOT, parser::token::DOT },
    { token::DOUBLEDOT, parser::token::DOUBLEDOT },
    { token::ELLIPSIS, parser::token::ELLIPSIS },
    { token::COMMA, parser::token::COMMA },
    { token::COLON, parser::token::COLON },
    { token::SEMICOLON, parser::token::SEMICOLON },
    { token::DOUBLECOLON, parser::token::DOUBLECOLON },
    { token::LBRACKET, parser::token::LBRACKET },
    { token::RBRACKET, parser::token::RBRACKET },
    { token::LBRACE, parser::token::LBRACE },
    { token::RBRACE, parser::token::RBRACE },
    { token::LPAREN, parser::token::LPAREN },
    { token::RPAREN, parser::token::RPAREN },
    { token::DEVBEGIN, parser::token::DEVBEGIN },
    { token::DEVEND, parser::token::DEVEND },
    { token::INLINE, parser::token::INLINE },
    { token::INCLUDE, parser::token::INCLUDE },
    { token::USINGTREE, parser::token::USINGTREE },
    { token::ANIMTREE, parser::token::ANIMTREE },
    { token::ENDON, parser::token::ENDON },
    { token::NOTIFY, parser::token::NOTIFY },
    { token::WAIT, parser::token::WAIT },
    { token::WAITTILL, parser::token::WAITTILL },
    { token::WAITTILLMATCH, parser::token::WAITTILLMATCH },
    { token::WAITTILLFRAMEEND, parser::token::WAITTILLFRAMEEND },
    { token::WAITFRAME, parser::token::WAITFRAME },
    { token::IF, parser::token::IF },
    { token::ELSE, parser::token::ELSE },
    { token::DO, parser::token::DO },
    { token::WHILE, parser::token::WHILE },
    { token::FOR, parser::token::FOR },
    { token::FOREACH, parser::token::FOREACH },
    { token::IN, parser::token::IN },
    { token::SWITCH, parser::token::SWITCH },
    { token::CASE, parser::token::CASE },
    { token::DEFAULT, parser::token::DEFAULT },
    { token::BREAK, parser::token::BREAK },
    { token::CONTINUE, parser::token::CONTINUE },
    { token::RETURN, parser::token::RETURN },
    { token::BREAKPOINT, parser::token::BREAKPOINT },
    { token::PROFBEGIN, parser::token::PROFBEGIN },
    { token::PROFEND, parser::token::PROFEND },
    { token::ASSERT, parser::token::ASSERT },
    { token::ASSERTEX, parser::token::ASSERTEX },
    { token::ASSERTMSG, parser::token::ASSERTMSG },
    { token::THREAD, parser::token::THREAD },
    { token::CHILDTHREAD, parser::token::CHILDTHREAD },
    { token::THISTHREAD, parser::token::THISTHREAD },
    { token::CALL, parser::token::CALL },
    { token::TRUE, parser::token::TRUE },
    { token::FALSE, parser::token::FALSE },
    { token::UNDEFINED, parser::token::UNDEFINED },
    { token::SIZE, parser::token::SIZE },
    { token::GAME, parser::token::GAME },
    { token::SELF, parser::token::SELF },
    { token::ANIM, parser::token::ANIM },
    { token::LEVEL, parser::token::LEVEL },
    { token::ISDEFINED, parser::token::ISDEFINED },
    { token::ISTRUE, parser::token::ISTRUE },
    { token::EOS, parser::token::GSCEOF },
    { token::HASH, parser::token::HASH }
}};

std::unordered_map<std::string_view, parser::token::token_kind_type> const keyword_map
{{
    { "endon", parser::token::ENDON },
    { "notify", parser::token::NOTIFY },
    { "wait", parser::token::WAIT },
    { "waittill", parser::token::WAITTILL },
    { "waittillmatch", parser::token::WAITTILLMATCH },
    { "waittillframeend", parser::token::WAITTILLFRAMEEND },
    { "waitframe", parser::token::WAITFRAME },
    { "if", parser::token::IF },
    { "else", parser::token::ELSE },
    { "do", parser::token::DO },
    { "while", parser::token::WHILE },
    { "for", parser::token::FOR },
    { "foreach", parser::token::FOREACH },
    { "in", parser::token::IN },
    { "switch", parser::token::SWITCH },
    { "case", parser::token::CASE },
    { "default", parser::token::DEFAULT },
    { "break", parser::token::BREAK },
    { "continue", parser::token::CONTINUE },
    { "return", parser::token::RETURN },
    { "breakpoint", parser::token::BREAKPOINT },
    { "prof_begin", parser::token::PROFBEGIN },
    { "prof_end", parser::token::PROFEND },
    { "assert", parser::token::ASSERT },
    { "assertex", parser::token::ASSERTEX },
    { "assertmsg", parser::token::ASSERTMSG },
    { "thread", parser::token::THREAD },
    { "childthread", parser::token::CHILDTHREAD },
    { "thisthread", parser::token::THISTHREAD },
    { "call", parser::token::CALL },
    { "true", parser::token::TRUE },
    { "false", parser::token::FALSE },
    { "undefined", parser::token::UNDEFINED },
    { "size", parser::token::SIZE },
    { "game", parser::token::GAME },
    { "self", parser::token::SELF },
    { "anim", parser::token::ANIM },
    { "level", parser::token::LEVEL },
    { "isdefined", parser::token::ISDEFINED },
    { "istrue", parser::token::ISTRUE },
}};

} // namespace xsk::gsc
