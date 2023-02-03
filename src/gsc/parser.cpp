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

#include "stdinc.hpp"
#include "parser.hpp"
#include "preprocessor.hpp"
using namespace xsk::gsc;
namespace xsk::gsc
{ 
    auto GSClex(context const* ctx_, preprocessor& ppr) -> parser::symbol_type;
    auto parse_switch(stmt_switch& stm) -> void;
}

#line 51 "parser.cpp"

// Take the name prefix into account.
#define yylex   GSClex



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
        value.YY_MOVE_OR_COPY< call > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< decl > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        value.YY_MOVE_OR_COPY< expr > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< stmt > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.YY_MOVE_OR_COPY< stmt_assign::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.YY_MOVE_OR_COPY< stmt_break::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.YY_MOVE_OR_COPY< stmt_breakpoint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.YY_MOVE_OR_COPY< stmt_call::ptr > (YY_MOVE (that.value));
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
        value.move< call > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        value.move< expr > (YY_MOVE (that.value));
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
        value.move< stmt > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_assign::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< stmt_break::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.move< stmt_breakpoint::ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< stmt_call::ptr > (YY_MOVE (that.value));
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
        value.copy< call > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< decl > (that.value);
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
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        value.copy< expr > (that.value);
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
        value.copy< stmt > (that.value);
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

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.copy< stmt_assign::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.copy< stmt_break::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.copy< stmt_breakpoint::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.copy< stmt_call::ptr > (that.value);
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
        value.move< call > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< decl > (that.value);
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
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        value.move< expr > (that.value);
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
        value.move< stmt > (that.value);
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

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_assign::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< stmt_break::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.move< stmt_breakpoint::ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< stmt_call::ptr > (that.value);
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
        yylhs.value.emplace< call > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< decl > ();
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
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_increment: // expr_increment
      case symbol_kind::S_expr_decrement: // expr_decrement
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_tuple: // expr_tuple
      case symbol_kind::S_expr_tuple_types: // expr_tuple_types
      case symbol_kind::S_expr_object: // expr_object
        yylhs.value.emplace< expr > ();
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
        yylhs.value.emplace< stmt > ();
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

      case symbol_kind::S_stmt_assign: // stmt_assign
        yylhs.value.emplace< stmt_assign::ptr > ();
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        yylhs.value.emplace< stmt_break::ptr > ();
        break;

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        yylhs.value.emplace< stmt_breakpoint::ptr > ();
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        yylhs.value.emplace< stmt_call::ptr > ();
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
#line 274 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program::ptr > ()); }
#line 2161 "parser.cpp"
    break;

  case 3: // root: %empty
#line 275 "parser.ypp"
              { ast = make_program(yylhs.location); }
#line 2167 "parser.cpp"
    break;

  case 4: // program: program inline
#line 280 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2173 "parser.cpp"
    break;

  case 5: // program: program include
#line 282 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2179 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 284 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl > ())); }
#line 2185 "parser.cpp"
    break;

  case 7: // program: inline
#line 286 "parser.ypp"
        { yylhs.value.as < program::ptr > () = make_program(yylhs.location); }
#line 2191 "parser.cpp"
    break;

  case 8: // program: include
#line 288 "parser.ypp"
        { yylhs.value.as < program::ptr > () = make_program(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2197 "parser.cpp"
    break;

  case 9: // program: declaration
#line 290 "parser.ypp"
        { yylhs.value.as < program::ptr > () = make_program(yylhs.location); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl > ())); }
#line 2203 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 294 "parser.ypp"
                                 { ppr.push_header(yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2209 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 299 "parser.ypp"
        { yylhs.value.as < include::ptr > () = make_include(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2215 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 303 "parser.ypp"
                        { yylhs.value.as < decl > ().as_dev_begin = make_decl_dev_begin(yylhs.location); }
#line 2221 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 304 "parser.ypp"
                        { yylhs.value.as < decl > ().as_dev_end = make_decl_dev_end(yylhs.location); }
#line 2227 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 305 "parser.ypp"
                        { yylhs.value.as < decl > ().as_usingtree = std::move(yystack_[0].value.as < decl_usingtree::ptr > ()); }
#line 2233 "parser.cpp"
    break;

  case 15: // declaration: decl_constant
#line 306 "parser.ypp"
                        { yylhs.value.as < decl > ().as_constant = std::move(yystack_[0].value.as < decl_constant::ptr > ()); }
#line 2239 "parser.cpp"
    break;

  case 16: // declaration: decl_function
#line 307 "parser.ypp"
                        { yylhs.value.as < decl > ().as_function = std::move(yystack_[0].value.as < decl_function::ptr > ()); }
#line 2245 "parser.cpp"
    break;

  case 17: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 312 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_usingtree::ptr > () = make_decl_usingtree(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 2251 "parser.cpp"
    break;

  case 18: // decl_constant: expr_identifier "=" expr ";"
#line 317 "parser.ypp"
        {
            ppr.ban_header(yylhs.location); yylhs.value.as < decl_constant::ptr > () = make_decl_constant(yylhs.location, std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr > ())); 
            printf("%s" , fmt::format("{}: constants deprecated, use #define instead\n", yylhs.location.print()).data());
        }
#line 2260 "parser.cpp"
    break;

  case 19: // decl_function: expr_identifier "(" expr_parameters ")" stmt_comp
#line 325 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = make_decl_function(yylhs.location, std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); }
#line 2266 "parser.cpp"
    break;

  case 20: // stmt: stmt_comp
#line 329 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_comp = std::move(yystack_[0].value.as < stmt_comp::ptr > ()); }
#line 2272 "parser.cpp"
    break;

  case 21: // stmt: stmt_call
#line 330 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_call = std::move(yystack_[0].value.as < stmt_call::ptr > ()); }
#line 2278 "parser.cpp"
    break;

  case 22: // stmt: stmt_assign
#line 331 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_assign = std::move(yystack_[0].value.as < stmt_assign::ptr > ()); }
#line 2284 "parser.cpp"
    break;

  case 23: // stmt: stmt_endon
#line 332 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_endon = std::move(yystack_[0].value.as < stmt_endon::ptr > ()); }
#line 2290 "parser.cpp"
    break;

  case 24: // stmt: stmt_notify
#line 333 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_notify = std::move(yystack_[0].value.as < stmt_notify::ptr > ()); }
#line 2296 "parser.cpp"
    break;

  case 25: // stmt: stmt_wait
#line 334 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_wait = std::move(yystack_[0].value.as < stmt_wait::ptr > ()); }
#line 2302 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittill
#line 335 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waittill = std::move(yystack_[0].value.as < stmt_waittill::ptr > ()); }
#line 2308 "parser.cpp"
    break;

  case 27: // stmt: stmt_waittillmatch
#line 336 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < stmt_waittillmatch::ptr > ()); }
#line 2314 "parser.cpp"
    break;

  case 28: // stmt: stmt_waittillframeend
#line 337 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < stmt_waittillframeend::ptr > ()); }
#line 2320 "parser.cpp"
    break;

  case 29: // stmt: stmt_waitframe
#line 338 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waitframe = std::move(yystack_[0].value.as < stmt_waitframe::ptr > ()); }
#line 2326 "parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 339 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_if = std::move(yystack_[0].value.as < stmt_if::ptr > ()); }
#line 2332 "parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 340 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_ifelse = std::move(yystack_[0].value.as < stmt_ifelse::ptr > ()); }
#line 2338 "parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 341 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_while = std::move(yystack_[0].value.as < stmt_while::ptr > ()); }
#line 2344 "parser.cpp"
    break;

  case 33: // stmt: stmt_dowhile
#line 342 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_dowhile = std::move(yystack_[0].value.as < stmt_dowhile::ptr > ()); }
#line 2350 "parser.cpp"
    break;

  case 34: // stmt: stmt_for
#line 343 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_for = std::move(yystack_[0].value.as < stmt_for::ptr > ()); }
#line 2356 "parser.cpp"
    break;

  case 35: // stmt: stmt_foreach
#line 344 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_foreach = std::move(yystack_[0].value.as < stmt_foreach::ptr > ()); }
#line 2362 "parser.cpp"
    break;

  case 36: // stmt: stmt_switch
#line 345 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_switch = std::move(yystack_[0].value.as < stmt_switch::ptr > ()); }
#line 2368 "parser.cpp"
    break;

  case 37: // stmt: stmt_case
#line 346 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_case = std::move(yystack_[0].value.as < stmt_case::ptr > ()); }
#line 2374 "parser.cpp"
    break;

  case 38: // stmt: stmt_default
#line 347 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_default = std::move(yystack_[0].value.as < stmt_default::ptr > ()); }
#line 2380 "parser.cpp"
    break;

  case 39: // stmt: stmt_break
#line 348 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_break = std::move(yystack_[0].value.as < stmt_break::ptr > ()); }
#line 2386 "parser.cpp"
    break;

  case 40: // stmt: stmt_continue
#line 349 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_continue = std::move(yystack_[0].value.as < stmt_continue::ptr > ()); }
#line 2392 "parser.cpp"
    break;

  case 41: // stmt: stmt_return
#line 350 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_return = std::move(yystack_[0].value.as < stmt_return::ptr > ()); }
#line 2398 "parser.cpp"
    break;

  case 42: // stmt: stmt_breakpoint
#line 351 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_breakpoint = std::move(yystack_[0].value.as < stmt_breakpoint::ptr > ()); }
#line 2404 "parser.cpp"
    break;

  case 43: // stmt: stmt_prof_begin
#line 352 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_prof_begin = std::move(yystack_[0].value.as < stmt_prof_begin::ptr > ()); }
#line 2410 "parser.cpp"
    break;

  case 44: // stmt: stmt_prof_end
#line 353 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_prof_end = std::move(yystack_[0].value.as < stmt_prof_end::ptr > ()); }
#line 2416 "parser.cpp"
    break;

  case 45: // stmt: stmt_assert
#line 354 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_assert = std::move(yystack_[0].value.as < stmt_assert::ptr > ()); }
#line 2422 "parser.cpp"
    break;

  case 46: // stmt: stmt_assertex
#line 355 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_assertex = std::move(yystack_[0].value.as < stmt_assertex::ptr > ()); }
#line 2428 "parser.cpp"
    break;

  case 47: // stmt: stmt_assertmsg
#line 356 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_assertmsg = std::move(yystack_[0].value.as < stmt_assertmsg::ptr > ()); }
#line 2434 "parser.cpp"
    break;

  case 48: // stmt_or_dev: stmt
#line 360 "parser.ypp"
               { yylhs.value.as < stmt > () = std::move(yystack_[0].value.as < stmt > ()); }
#line 2440 "parser.cpp"
    break;

  case 49: // stmt_or_dev: stmt_dev
#line 361 "parser.ypp"
               { yylhs.value.as < stmt > ().as_dev = std::move(yystack_[0].value.as < stmt_dev::ptr > ()); }
#line 2446 "parser.cpp"
    break;

  case 50: // stmt_list: stmt_list stmt
#line 366 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2452 "parser.cpp"
    break;

  case 51: // stmt_list: stmt
#line 368 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2458 "parser.cpp"
    break;

  case 52: // stmt_list: stmt_list ";"
#line 370 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2464 "parser.cpp"
    break;

  case 53: // stmt_list: ";"
#line 372 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); }
#line 2470 "parser.cpp"
    break;

  case 54: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 377 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2476 "parser.cpp"
    break;

  case 55: // stmt_or_dev_list: stmt_or_dev
#line 379 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2482 "parser.cpp"
    break;

  case 56: // stmt_or_dev_list: stmt_or_dev_list ";"
#line 381 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2488 "parser.cpp"
    break;

  case 57: // stmt_or_dev_list: ";"
#line 383 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); }
#line 2494 "parser.cpp"
    break;

  case 58: // stmt_dev: "/#" stmt_list "#/"
#line 387 "parser.ypp"
                                { yylhs.value.as < stmt_dev::ptr > () = make_stmt_dev(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2500 "parser.cpp"
    break;

  case 59: // stmt_dev: "/#" "#/"
#line 388 "parser.ypp"
                      { yylhs.value.as < stmt_dev::ptr > () = make_stmt_dev(yylhs.location, make_stmt_list(yylhs.location)); }
#line 2506 "parser.cpp"
    break;

  case 60: // stmt_comp: "{" stmt_or_dev_list "}"
#line 392 "parser.ypp"
                                     { yylhs.value.as < stmt_comp::ptr > () = make_stmt_comp(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2512 "parser.cpp"
    break;

  case 61: // stmt_comp: "{" "}"
#line 393 "parser.ypp"
                    { yylhs.value.as < stmt_comp::ptr > () = make_stmt_comp(yylhs.location, make_stmt_list(yylhs.location)); }
#line 2518 "parser.cpp"
    break;

  case 62: // stmt_expr: expr_assign
#line 398 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 2524 "parser.cpp"
    break;

  case 63: // stmt_expr: expr_increment
#line 400 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 2530 "parser.cpp"
    break;

  case 64: // stmt_expr: expr_decrement
#line 402 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 2536 "parser.cpp"
    break;

  case 65: // stmt_expr: %empty
#line 404 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, make_node(yylhs.location)); }
#line 2542 "parser.cpp"
    break;

  case 66: // stmt_call: expr_call ";"
#line 409 "parser.ypp"
        { yylhs.value.as < stmt_call::ptr > () = make_stmt_call(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_call::ptr > ()) }); }
#line 2548 "parser.cpp"
    break;

  case 67: // stmt_call: expr_method ";"
#line 411 "parser.ypp"
        { yylhs.value.as < stmt_call::ptr > () = make_stmt_call(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_method::ptr > ()) }); }
#line 2554 "parser.cpp"
    break;

  case 68: // stmt_assign: expr_assign ";"
#line 416 "parser.ypp"
        { yylhs.value.as < stmt_assign::ptr > () = make_stmt_assign(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2560 "parser.cpp"
    break;

  case 69: // stmt_assign: expr_increment ";"
#line 418 "parser.ypp"
        { yylhs.value.as < stmt_assign::ptr > () = make_stmt_assign(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2566 "parser.cpp"
    break;

  case 70: // stmt_assign: expr_decrement ";"
#line 420 "parser.ypp"
        { yylhs.value.as < stmt_assign::ptr > () = make_stmt_assign(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2572 "parser.cpp"
    break;

  case 71: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 425 "parser.ypp"
        { yylhs.value.as < stmt_endon::ptr > () = make_stmt_endon(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ())); }
#line 2578 "parser.cpp"
    break;

  case 72: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 430 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = make_stmt_notify(yylhs.location, std::move(yystack_[7].value.as < expr > ()), std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2584 "parser.cpp"
    break;

  case 73: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 432 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = make_stmt_notify(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), make_expr_arguments(yylhs.location)); }
#line 2590 "parser.cpp"
    break;

  case 74: // stmt_wait: "wait" expr ";"
#line 437 "parser.ypp"
        { yylhs.value.as < stmt_wait::ptr > () = make_stmt_wait(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2596 "parser.cpp"
    break;

  case 75: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 442 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = make_stmt_waittill(yylhs.location, std::move(yystack_[7].value.as < expr > ()), std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2602 "parser.cpp"
    break;

  case 76: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 444 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = make_stmt_waittill(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), make_expr_arguments(yylhs.location)); }
#line 2608 "parser.cpp"
    break;

  case 77: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 449 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = make_stmt_waittillmatch(yylhs.location, std::move(yystack_[7].value.as < expr > ()), std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2614 "parser.cpp"
    break;

  case 78: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 451 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = make_stmt_waittillmatch(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), make_expr_arguments(yylhs.location)); }
#line 2620 "parser.cpp"
    break;

  case 79: // stmt_waittillframeend: "waittillframeend" ";"
#line 456 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend::ptr > () = make_stmt_waittillframeend(yylhs.location); }
#line 2626 "parser.cpp"
    break;

  case 80: // stmt_waitframe: "waitframe" ";"
#line 461 "parser.ypp"
        { yylhs.value.as < stmt_waitframe::ptr > () = make_stmt_waitframe(yylhs.location); }
#line 2632 "parser.cpp"
    break;

  case 81: // stmt_waitframe: "waitframe" "(" ")" ";"
#line 463 "parser.ypp"
        { yylhs.value.as < stmt_waitframe::ptr > () = make_stmt_waitframe(yylhs.location); }
#line 2638 "parser.cpp"
    break;

  case 82: // stmt_if: "if" "(" expr ")" stmt
#line 468 "parser.ypp"
        { yylhs.value.as < stmt_if::ptr > () = make_stmt_if(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < stmt > ())); }
#line 2644 "parser.cpp"
    break;

  case 83: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 473 "parser.ypp"
        { yylhs.value.as < stmt_ifelse::ptr > () = make_stmt_ifelse(yylhs.location, std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < stmt > ()), std::move(yystack_[0].value.as < stmt > ())); }
#line 2650 "parser.cpp"
    break;

  case 84: // stmt_while: "while" "(" expr ")" stmt
#line 478 "parser.ypp"
        { yylhs.value.as < stmt_while::ptr > () = make_stmt_while(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < stmt > ())); }
#line 2656 "parser.cpp"
    break;

  case 85: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 483 "parser.ypp"
        { yylhs.value.as < stmt_dowhile::ptr > () = make_stmt_dowhile(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[5].value.as < stmt > ())); }
#line 2662 "parser.cpp"
    break;

  case 86: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 488 "parser.ypp"
        { yylhs.value.as < stmt_for::ptr > () = make_stmt_for(yylhs.location, stmt{ std::move(yystack_[6].value.as < stmt_expr::ptr > ()) }, std::move(yystack_[4].value.as < expr > ()), stmt{ std::move(yystack_[2].value.as < stmt_expr::ptr > ()) }, std::move(yystack_[0].value.as < stmt > ())); }
#line 2668 "parser.cpp"
    break;

  case 87: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 493 "parser.ypp"
        {
            auto array = expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) };
            auto key = expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) };
            yylhs.value.as < stmt_foreach::ptr > () = make_stmt_foreach(yylhs.location, std::move(yystack_[2].value.as < expr > ()), expr{ std::move(yystack_[4].value.as < expr_identifier::ptr > ()) }, expr{ make_node(yylhs.location) }, std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt > ()), false); }
#line 2677 "parser.cpp"
    break;

  case 88: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 498 "parser.ypp"
        {
            auto array = expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) };
            auto key = (ctx_->props() & props::foreach) ? expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) } : expr{ std::move(yystack_[6].value.as < expr_identifier::ptr > ()) };
            yylhs.value.as < stmt_foreach::ptr > () = make_stmt_foreach(yylhs.location, std::move(yystack_[2].value.as < expr > ()), expr{ std::move(yystack_[4].value.as < expr_identifier::ptr > ()) }, (ctx_->props() & props::foreach) ? expr{ std::move(yystack_[6].value.as < expr_identifier::ptr > ()) } : expr{ make_node(yylhs.location) }, std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt > ()), true);
        }
#line 2687 "parser.cpp"
    break;

  case 89: // stmt_switch: "switch" "(" expr ")" stmt_comp
#line 507 "parser.ypp"
        { yylhs.value.as < stmt_switch::ptr > () = make_stmt_switch(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); 
          parse_switch(*yylhs.value.as < stmt_switch::ptr > ());
        }
#line 2695 "parser.cpp"
    break;

  case 90: // stmt_case: "case" expr_integer ":"
#line 514 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = make_stmt_case(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_integer::ptr > ()) }, make_stmt_list(yylhs.location)); }
#line 2701 "parser.cpp"
    break;

  case 91: // stmt_case: "case" expr_string ":"
#line 516 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = make_stmt_case(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_string::ptr > ()) }, make_stmt_list(yylhs.location)); }
#line 2707 "parser.cpp"
    break;

  case 92: // stmt_default: "default" ":"
#line 521 "parser.ypp"
        { yylhs.value.as < stmt_default::ptr > () = make_stmt_default(yylhs.location, make_stmt_list(yylhs.location)); }
#line 2713 "parser.cpp"
    break;

  case 93: // stmt_break: "break" ";"
#line 526 "parser.ypp"
        { yylhs.value.as < stmt_break::ptr > () = make_stmt_break(yylhs.location); }
#line 2719 "parser.cpp"
    break;

  case 94: // stmt_continue: "continue" ";"
#line 531 "parser.ypp"
        { yylhs.value.as < stmt_continue::ptr > () = make_stmt_continue(yylhs.location); }
#line 2725 "parser.cpp"
    break;

  case 95: // stmt_return: "return" expr ";"
#line 536 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = make_stmt_return(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2731 "parser.cpp"
    break;

  case 96: // stmt_return: "return" ";"
#line 538 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = make_stmt_return(yylhs.location, make_node(yylhs.location)); }
#line 2737 "parser.cpp"
    break;

  case 97: // stmt_breakpoint: "breakpoint" ";"
#line 543 "parser.ypp"
        { yylhs.value.as < stmt_breakpoint::ptr > () = make_stmt_breakpoint(yylhs.location); }
#line 2743 "parser.cpp"
    break;

  case 98: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 548 "parser.ypp"
        { yylhs.value.as < stmt_prof_begin::ptr > () = make_stmt_prof_begin(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2749 "parser.cpp"
    break;

  case 99: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 553 "parser.ypp"
        { yylhs.value.as < stmt_prof_end::ptr > () = make_stmt_prof_end(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2755 "parser.cpp"
    break;

  case 100: // stmt_assert: "assert" "(" expr_arguments ")" ";"
#line 558 "parser.ypp"
        { yylhs.value.as < stmt_assert::ptr > () = make_stmt_assert(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2761 "parser.cpp"
    break;

  case 101: // stmt_assertex: "assertex" "(" expr_arguments ")" ";"
#line 563 "parser.ypp"
        { yylhs.value.as < stmt_assertex::ptr > () = make_stmt_assertex(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2767 "parser.cpp"
    break;

  case 102: // stmt_assertmsg: "assertmsg" "(" expr_arguments ")" ";"
#line 568 "parser.ypp"
        { yylhs.value.as < stmt_assertmsg::ptr > () = make_stmt_assertmsg(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2773 "parser.cpp"
    break;

  case 103: // expr: expr_ternary
#line 572 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2779 "parser.cpp"
    break;

  case 104: // expr: expr_binary
#line 573 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2785 "parser.cpp"
    break;

  case 105: // expr: expr_primitive
#line 574 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2791 "parser.cpp"
    break;

  case 106: // expr_or_empty: expr
#line 578 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2797 "parser.cpp"
    break;

  case 107: // expr_or_empty: %empty
#line 579 "parser.ypp"
                     { yylhs.value.as < expr > ().as_node = make_node(yylhs.location); }
#line 2803 "parser.cpp"
    break;

  case 108: // expr_assign: expr_tuple "=" expr
#line 584 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2809 "parser.cpp"
    break;

  case 109: // expr_assign: expr_object "=" expr
#line 586 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2815 "parser.cpp"
    break;

  case 110: // expr_assign: expr_object "|=" expr
#line 588 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_bitwise_or(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2821 "parser.cpp"
    break;

  case 111: // expr_assign: expr_object "&=" expr
#line 590 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_bitwise_and(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2827 "parser.cpp"
    break;

  case 112: // expr_assign: expr_object "^=" expr
#line 592 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_bitwise_exor(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2833 "parser.cpp"
    break;

  case 113: // expr_assign: expr_object "<<=" expr
#line 594 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_shift_left(yylhs.location, std::move(yystack_[2].value.as < expr > ()),std::move( yystack_[0].value.as < expr > ())); }
#line 2839 "parser.cpp"
    break;

  case 114: // expr_assign: expr_object ">>=" expr
#line 596 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_shift_right(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2845 "parser.cpp"
    break;

  case 115: // expr_assign: expr_object "+=" expr
#line 598 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_add(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2851 "parser.cpp"
    break;

  case 116: // expr_assign: expr_object "-=" expr
#line 600 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_sub(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2857 "parser.cpp"
    break;

  case 117: // expr_assign: expr_object "*=" expr
#line 602 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_mul(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2863 "parser.cpp"
    break;

  case 118: // expr_assign: expr_object "/=" expr
#line 604 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_div(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2869 "parser.cpp"
    break;

  case 119: // expr_assign: expr_object "%=" expr
#line 606 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_mod(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2875 "parser.cpp"
    break;

  case 120: // expr_increment: "++" expr_object
#line 611 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_increment(yylhs.location, std::move(yystack_[0].value.as < expr > ()), true); }
#line 2881 "parser.cpp"
    break;

  case 121: // expr_increment: expr_object "++"
#line 613 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_increment(yylhs.location, std::move(yystack_[1].value.as < expr > ()), false); }
#line 2887 "parser.cpp"
    break;

  case 122: // expr_decrement: "--" expr_object
#line 618 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_decrement(yylhs.location, std::move(yystack_[0].value.as < expr > ()), true); }
#line 2893 "parser.cpp"
    break;

  case 123: // expr_decrement: expr_object "--"
#line 620 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_decrement(yylhs.location, std::move(yystack_[1].value.as < expr > ()), false); }
#line 2899 "parser.cpp"
    break;

  case 124: // expr_ternary: expr "?" expr ":" expr
#line 625 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_ternary(yylhs.location, std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2905 "parser.cpp"
    break;

  case 125: // expr_binary: expr "||" expr
#line 630 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_or(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2911 "parser.cpp"
    break;

  case 126: // expr_binary: expr "&&" expr
#line 632 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_and(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2917 "parser.cpp"
    break;

  case 127: // expr_binary: expr "==" expr
#line 634 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_equality(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2923 "parser.cpp"
    break;

  case 128: // expr_binary: expr "!=" expr
#line 636 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_inequality(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2929 "parser.cpp"
    break;

  case 129: // expr_binary: expr "<=" expr
#line 638 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_less_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2935 "parser.cpp"
    break;

  case 130: // expr_binary: expr ">=" expr
#line 640 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_greater_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2941 "parser.cpp"
    break;

  case 131: // expr_binary: expr "<" expr
#line 642 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_less(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2947 "parser.cpp"
    break;

  case 132: // expr_binary: expr ">" expr
#line 644 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_greater(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2953 "parser.cpp"
    break;

  case 133: // expr_binary: expr "|" expr
#line 646 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_bitwise_or(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2959 "parser.cpp"
    break;

  case 134: // expr_binary: expr "&" expr
#line 648 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_bitwise_and(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2965 "parser.cpp"
    break;

  case 135: // expr_binary: expr "^" expr
#line 650 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_bitwise_exor(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2971 "parser.cpp"
    break;

  case 136: // expr_binary: expr "<<" expr
#line 652 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_shift_left(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2977 "parser.cpp"
    break;

  case 137: // expr_binary: expr ">>" expr
#line 654 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_shift_right(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2983 "parser.cpp"
    break;

  case 138: // expr_binary: expr "+" expr
#line 656 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_add(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2989 "parser.cpp"
    break;

  case 139: // expr_binary: expr "-" expr
#line 658 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_sub(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2995 "parser.cpp"
    break;

  case 140: // expr_binary: expr "*" expr
#line 660 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_mul(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 3001 "parser.cpp"
    break;

  case 141: // expr_binary: expr "/" expr
#line 662 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_div(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 3007 "parser.cpp"
    break;

  case 142: // expr_binary: expr "%" expr
#line 664 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_mod(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 3013 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_complement
#line 668 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_complement::ptr > ()); }
#line 3019 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_negate
#line 669 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_negate::ptr > ()); }
#line 3025 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_not
#line 670 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_not::ptr > ()); }
#line 3031 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_call
#line 671 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3037 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_method
#line 672 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3043 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_add_array
#line 673 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_add_array::ptr > ()); }
#line 3049 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_isdefined
#line 674 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_isdefined::ptr > ()); }
#line 3055 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_istrue
#line 675 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_istrue::ptr > ()); }
#line 3061 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_reference
#line 676 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_reference::ptr > ()); }
#line 3067 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_array
#line 677 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3073 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_field
#line 678 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3079 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_size
#line 679 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_size::ptr > ()); }
#line 3085 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_paren
#line 680 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_paren::ptr > ()); }
#line 3091 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_thisthread
#line 681 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_thisthread::ptr > ()); }
#line 3097 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_empty_array
#line 682 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_empty_array::ptr > ()); }
#line 3103 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_undefined
#line 683 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_undefined::ptr > ()); }
#line 3109 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_game
#line 684 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3115 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_self
#line 685 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3121 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_anim
#line 686 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3127 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_level
#line 687 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3133 "parser.cpp"
    break;

  case 163: // expr_primitive: expr_animation
#line 688 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_animation::ptr > ()); }
#line 3139 "parser.cpp"
    break;

  case 164: // expr_primitive: expr_animtree
#line 689 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_animtree::ptr > ()); }
#line 3145 "parser.cpp"
    break;

  case 165: // expr_primitive: expr_identifier
#line 690 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3151 "parser.cpp"
    break;

  case 166: // expr_primitive: expr_istring
#line 691 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_istring::ptr > ()); }
#line 3157 "parser.cpp"
    break;

  case 167: // expr_primitive: expr_string
#line 692 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_string::ptr > ()); }
#line 3163 "parser.cpp"
    break;

  case 168: // expr_primitive: expr_vector
#line 693 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_vector::ptr > ()); }
#line 3169 "parser.cpp"
    break;

  case 169: // expr_primitive: expr_float
#line 694 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_float::ptr > ()); }
#line 3175 "parser.cpp"
    break;

  case 170: // expr_primitive: expr_integer
#line 695 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_integer::ptr > ()); }
#line 3181 "parser.cpp"
    break;

  case 171: // expr_primitive: expr_false
#line 696 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_false::ptr > ()); }
#line 3187 "parser.cpp"
    break;

  case 172: // expr_primitive: expr_true
#line 697 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_true::ptr > ()); }
#line 3193 "parser.cpp"
    break;

  case 173: // expr_complement: "~" expr
#line 702 "parser.ypp"
        { yylhs.value.as < expr_complement::ptr > () = make_expr_complement(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 3199 "parser.cpp"
    break;

  case 174: // expr_negate: "-" expr_identifier
#line 707 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_identifier::ptr > ()) }); }
#line 3205 "parser.cpp"
    break;

  case 175: // expr_negate: "-" expr_paren
#line 709 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_paren::ptr > ()) }); }
#line 3211 "parser.cpp"
    break;

  case 176: // expr_negate: "-" expr_array
#line 711 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_array::ptr > ()) }); }
#line 3217 "parser.cpp"
    break;

  case 177: // expr_negate: "-" expr_field
#line 713 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_field::ptr > ()) }); }
#line 3223 "parser.cpp"
    break;

  case 178: // expr_not: "!" expr
#line 718 "parser.ypp"
        { yylhs.value.as < expr_not::ptr > () = make_expr_not(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 3229 "parser.cpp"
    break;

  case 179: // expr_call: expr_function
#line 722 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = make_expr_call(yylhs.location, std::move(yystack_[0].value.as < call > ())); }
#line 3235 "parser.cpp"
    break;

  case 180: // expr_call: expr_pointer
#line 723 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = make_expr_call(yylhs.location, std::move(yystack_[0].value.as < call > ())); }
#line 3241 "parser.cpp"
    break;

  case 181: // expr_method: expr_object expr_function
#line 726 "parser.ypp"
                                   { yylhs.value.as < expr_method::ptr > () = make_expr_method(yylhs.location, std::move(yystack_[1].value.as < expr > ()), std::move(yystack_[0].value.as < call > ())); }
#line 3247 "parser.cpp"
    break;

  case 182: // expr_method: expr_object expr_pointer
#line 727 "parser.ypp"
                                   { yylhs.value.as < expr_method::ptr > () = make_expr_method(yylhs.location, std::move(yystack_[1].value.as < expr > ()), std::move(yystack_[0].value.as < call > ())); }
#line 3253 "parser.cpp"
    break;

  case 183: // expr_function: expr_identifier "(" expr_arguments ")"
#line 732 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3259 "parser.cpp"
    break;

  case 184: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 734 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3265 "parser.cpp"
    break;

  case 185: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 736 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3271 "parser.cpp"
    break;

  case 186: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 738 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3277 "parser.cpp"
    break;

  case 187: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 740 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3283 "parser.cpp"
    break;

  case 188: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 742 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3289 "parser.cpp"
    break;

  case 189: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 747 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3295 "parser.cpp"
    break;

  case 190: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 749 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3301 "parser.cpp"
    break;

  case 191: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 751 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3307 "parser.cpp"
    break;

  case 192: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 753 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::builtin); }
#line 3313 "parser.cpp"
    break;

  case 193: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 758 "parser.ypp"
        { yylhs.value.as < expr_add_array::ptr > () = make_expr_add_array(yylhs.location, std::move(yystack_[1].value.as < expr_arguments::ptr > ())); }
#line 3319 "parser.cpp"
    break;

  case 194: // expr_parameters: expr_parameters "," expr_identifier
#line 763 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3325 "parser.cpp"
    break;

  case 195: // expr_parameters: expr_identifier
#line 765 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = make_expr_parameters(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3331 "parser.cpp"
    break;

  case 196: // expr_parameters: %empty
#line 767 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = make_expr_parameters(yylhs.location); }
#line 3337 "parser.cpp"
    break;

  case 197: // expr_arguments: expr_arguments_no_empty
#line 772 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[0].value.as < expr_arguments::ptr > ()); }
#line 3343 "parser.cpp"
    break;

  case 198: // expr_arguments: %empty
#line 774 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = make_expr_arguments(yylhs.location); }
#line 3349 "parser.cpp"
    break;

  case 199: // expr_arguments_no_empty: expr_arguments "," expr
#line 779 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[2].value.as < expr_arguments::ptr > ()); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3355 "parser.cpp"
    break;

  case 200: // expr_arguments_no_empty: expr
#line 781 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = make_expr_arguments(yylhs.location); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3361 "parser.cpp"
    break;

  case 201: // expr_isdefined: "isdefined" "(" expr ")"
#line 786 "parser.ypp"
        { yylhs.value.as < expr_isdefined::ptr > () = make_expr_isdefined(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 3367 "parser.cpp"
    break;

  case 202: // expr_istrue: "istrue" "(" expr ")"
#line 791 "parser.ypp"
        { yylhs.value.as < expr_istrue::ptr > () = make_expr_istrue(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 3373 "parser.cpp"
    break;

  case 203: // expr_reference: "::" expr_identifier
#line 796 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = make_expr_reference(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3379 "parser.cpp"
    break;

  case 204: // expr_reference: expr_path "::" expr_identifier
#line 798 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = make_expr_reference(yylhs.location, std::move(yystack_[2].value.as < expr_path::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3385 "parser.cpp"
    break;

  case 205: // expr_tuple: "[" expr_tuple_arguments "]"
#line 803 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = std::move(yystack_[1].value.as < expr_tuple::ptr > ());
          yylhs.value.as < expr > ().as_tuple->temp = expr{ std::make_unique<expr_identifier>(yylhs.value.as < expr > ().loc(), fmt::format("_temp_{}", ++index)) };
        }
#line 3393 "parser.cpp"
    break;

  case 206: // expr_tuple_arguments: expr_tuple_arguments "," expr_tuple_types
#line 810 "parser.ypp"
        { yylhs.value.as < expr_tuple::ptr > () = std::move(yystack_[2].value.as < expr_tuple::ptr > ()); yylhs.value.as < expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3399 "parser.cpp"
    break;

  case 207: // expr_tuple_arguments: expr_tuple_types
#line 812 "parser.ypp"
        { yylhs.value.as < expr_tuple::ptr > () = make_expr_tuple(yylhs.location); yylhs.value.as < expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3405 "parser.cpp"
    break;

  case 208: // expr_tuple_types: expr_array
#line 816 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3411 "parser.cpp"
    break;

  case 209: // expr_tuple_types: expr_field
#line 817 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3417 "parser.cpp"
    break;

  case 210: // expr_tuple_types: expr_identifier
#line 818 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3423 "parser.cpp"
    break;

  case 211: // expr_array: expr_object "[" expr "]"
#line 823 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = make_expr_array(yylhs.location, std::move(yystack_[3].value.as < expr > ()), std::move(yystack_[1].value.as < expr > ())); }
#line 3429 "parser.cpp"
    break;

  case 212: // expr_field: expr_object "." expr_identifier_nosize
#line 828 "parser.ypp"
        { yylhs.value.as < expr_field::ptr > () = make_expr_field(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3435 "parser.cpp"
    break;

  case 213: // expr_size: expr_object "." "size"
#line 833 "parser.ypp"
        { yylhs.value.as < expr_size::ptr > () = make_expr_size(yylhs.location, std::move(yystack_[2].value.as < expr > ())); }
#line 3441 "parser.cpp"
    break;

  case 214: // expr_paren: "(" expr ")"
#line 838 "parser.ypp"
        { yylhs.value.as < expr_paren::ptr > () = make_expr_paren(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 3447 "parser.cpp"
    break;

  case 215: // expr_object: expr_call
#line 842 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3453 "parser.cpp"
    break;

  case 216: // expr_object: expr_method
#line 843 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3459 "parser.cpp"
    break;

  case 217: // expr_object: expr_array
#line 844 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3465 "parser.cpp"
    break;

  case 218: // expr_object: expr_field
#line 845 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3471 "parser.cpp"
    break;

  case 219: // expr_object: expr_game
#line 846 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3477 "parser.cpp"
    break;

  case 220: // expr_object: expr_self
#line 847 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3483 "parser.cpp"
    break;

  case 221: // expr_object: expr_anim
#line 848 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3489 "parser.cpp"
    break;

  case 222: // expr_object: expr_level
#line 849 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3495 "parser.cpp"
    break;

  case 223: // expr_object: expr_identifier
#line 850 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3501 "parser.cpp"
    break;

  case 224: // expr_thisthread: "thisthread"
#line 855 "parser.ypp"
        { yylhs.value.as < expr_thisthread::ptr > () = make_expr_thisthread(yylhs.location); }
#line 3507 "parser.cpp"
    break;

  case 225: // expr_empty_array: "[" "]"
#line 860 "parser.ypp"
        { yylhs.value.as < expr_empty_array::ptr > () = make_expr_empty_array(yylhs.location); }
#line 3513 "parser.cpp"
    break;

  case 226: // expr_undefined: "undefined"
#line 865 "parser.ypp"
        { yylhs.value.as < expr_undefined::ptr > () = make_expr_undefined(yylhs.location); }
#line 3519 "parser.cpp"
    break;

  case 227: // expr_game: "game"
#line 870 "parser.ypp"
        { yylhs.value.as < expr_game::ptr > () = make_expr_game(yylhs.location); }
#line 3525 "parser.cpp"
    break;

  case 228: // expr_self: "self"
#line 875 "parser.ypp"
        { yylhs.value.as < expr_self::ptr > () = make_expr_self(yylhs.location); }
#line 3531 "parser.cpp"
    break;

  case 229: // expr_anim: "anim"
#line 880 "parser.ypp"
        { yylhs.value.as < expr_anim::ptr > () = make_expr_anim(yylhs.location); }
#line 3537 "parser.cpp"
    break;

  case 230: // expr_level: "level"
#line 885 "parser.ypp"
        { yylhs.value.as < expr_level::ptr > () = make_expr_level(yylhs.location); }
#line 3543 "parser.cpp"
    break;

  case 231: // expr_animation: "%" "identifier"
#line 890 "parser.ypp"
        { yylhs.value.as < expr_animation::ptr > () = make_expr_animation(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3549 "parser.cpp"
    break;

  case 232: // expr_animtree: "#animtree"
#line 895 "parser.ypp"
        { yylhs.value.as < expr_animtree::ptr > () = make_expr_animtree(yylhs.location); }
#line 3555 "parser.cpp"
    break;

  case 233: // expr_identifier_nosize: "identifier"
#line 900 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = make_expr_identifier(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3561 "parser.cpp"
    break;

  case 234: // expr_identifier: "identifier"
#line 905 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = make_expr_identifier(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3567 "parser.cpp"
    break;

  case 235: // expr_identifier: "size"
#line 907 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = make_expr_identifier(yylhs.location, "size"); }
#line 3573 "parser.cpp"
    break;

  case 236: // expr_path: "path" "/" "identifier"
#line 912 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = make_expr_path(yylhs.location, yystack_[2].value.as < std::string > () + "/" + yystack_[0].value.as < std::string > ()); }
#line 3579 "parser.cpp"
    break;

  case 237: // expr_path: "identifier"
#line 914 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = make_expr_path(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3585 "parser.cpp"
    break;

  case 238: // expr_path: "path"
#line 916 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = make_expr_path(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3591 "parser.cpp"
    break;

  case 239: // expr_istring: "localized string"
#line 921 "parser.ypp"
        { yylhs.value.as < expr_istring::ptr > () = make_expr_istring(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3597 "parser.cpp"
    break;

  case 240: // expr_string: "string literal"
#line 926 "parser.ypp"
        { yylhs.value.as < expr_string::ptr > () = make_expr_string(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3603 "parser.cpp"
    break;

  case 241: // expr_vector: "(" expr "," expr "," expr ")"
#line 931 "parser.ypp"
        { yylhs.value.as < expr_vector::ptr > () = make_expr_vector(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[3].value.as < expr > ()), std::move(yystack_[1].value.as < expr > ())); }
#line 3609 "parser.cpp"
    break;

  case 242: // expr_float: "-" "float"
#line 936 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = make_expr_float(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3615 "parser.cpp"
    break;

  case 243: // expr_float: "float"
#line 938 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = make_expr_float(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3621 "parser.cpp"
    break;

  case 244: // expr_integer: "-" "integer"
#line 943 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = make_expr_integer(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3627 "parser.cpp"
    break;

  case 245: // expr_integer: "integer"
#line 945 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = make_expr_integer(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3633 "parser.cpp"
    break;

  case 246: // expr_false: "false"
#line 950 "parser.ypp"
        { yylhs.value.as < expr_false::ptr > () = make_expr_false(yylhs.location); }
#line 3639 "parser.cpp"
    break;

  case 247: // expr_true: "true"
#line 955 "parser.ypp"
        { yylhs.value.as < expr_true::ptr > () = make_expr_true(yylhs.location); }
#line 3645 "parser.cpp"
    break;


#line 3649 "parser.cpp"

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
  "]", ",", ".", "...", "::", ":", ";", "?", "++", "--", "<<", ">>", "||",
  "&&", "==", "!=", "<=", ">=", "<", ">", "!", "~", "=", "+=", "-=", "*=",
  "/=", "%=", "|=", "&=", "^=", ">>=", "<<=", "|", "&", "^", "+", "-", "*",
  "/", "%", "path", "identifier", "string literal", "localized string",
  "float", "integer", "SIZEOF", "ADD_ARRAY", "THEN", "TERN", "NEG",
  "ANIMREF", "PREINC", "PREDEC", "POSTINC", "POSTDEC", "$accept", "root",
  "program", "inline", "include", "declaration", "decl_usingtree",
  "decl_constant", "decl_function", "stmt", "stmt_or_dev", "stmt_list",
  "stmt_or_dev_list", "stmt_dev", "stmt_comp", "stmt_expr", "stmt_call",
  "stmt_assign", "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_waitframe",
  "stmt_if", "stmt_ifelse", "stmt_while", "stmt_dowhile", "stmt_for",
  "stmt_foreach", "stmt_switch", "stmt_case", "stmt_default", "stmt_break",
  "stmt_continue", "stmt_return", "stmt_breakpoint", "stmt_prof_begin",
  "stmt_prof_end", "stmt_assert", "stmt_assertex", "stmt_assertmsg",
  "expr", "expr_or_empty", "expr_assign", "expr_increment",
  "expr_decrement", "expr_ternary", "expr_binary", "expr_primitive",
  "expr_complement", "expr_negate", "expr_not", "expr_call", "expr_method",
  "expr_function", "expr_pointer", "expr_add_array", "expr_parameters",
  "expr_arguments", "expr_arguments_no_empty", "expr_isdefined",
  "expr_istrue", "expr_reference", "expr_tuple", "expr_tuple_arguments",
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


  const short parser::yypact_ninf_ = -308;

  const short parser::yytable_ninf_ = -238;

  const short
  parser::yypact_[] =
  {
      12,  -308,  -308,     6,     6,   -16,  -308,  -308,    32,    12,
    -308,  -308,  -308,  -308,  -308,  -308,   -37,   -73,  -308,   -22,
     -13,   -35,  -308,  -308,  -308,  -308,   -29,  1340,    -3,  -308,
    -308,  -308,    26,   -18,  -308,  -308,   -31,    21,  -308,    42,
    -308,  -308,  -308,  -308,  -308,  -308,  -308,    62,   101,  1340,
    1204,   -29,  1340,  1340,    37,    44,   100,  -308,  -308,  -308,
    2125,  -308,  -308,  -308,  -308,  -308,  -308,    56,   233,  -308,
    -308,  -308,  -308,  -308,  -308,   245,   368,  -308,  -308,   487,
    -308,  -308,  -308,   550,   602,   643,   665,  -308,  -308,    -8,
     112,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,   123,
     134,   -29,   133,   140,   135,   138,   143,   141,   147,  1340,
    1340,  1508,  1204,  -308,  2208,   148,   154,  -308,  -308,  -308,
    1340,   156,  -308,  -308,  -308,  -308,   245,   368,  -308,   802,
    -308,  -308,  -308,  -308,    -8,   155,  -308,  -308,  1340,  1340,
    1340,  1340,  1340,  1340,  1340,  1340,  1340,  1340,  1340,  1340,
    1340,  1340,  1340,  1340,  1340,  1340,  1340,  1408,   -19,  -308,
    -308,   161,  1340,   -29,  -308,  1010,  -308,  -308,  1340,  1340,
     -29,  1340,  1340,   -29,  1340,  1656,  1690,  -308,  1340,  1336,
    1340,  -308,  1703,  1340,   116,   -29,  2090,   305,   305,   778,
    1195,   856,   856,   279,   279,   279,   279,  2239,  1564,  1519,
     -24,   -24,  -308,  -308,  -308,  1404,  -308,  -308,  -308,    -4,
    -308,   166,  1120,  1340,   159,   -20,   171,  1498,   172,   173,
     176,   179,   -42,   182,   178,   184,  1272,   185,   183,   200,
     201,   203,   209,  -308,   152,  -308,   779,   779,  -308,  -308,
    1065,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,
    -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,
    -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,
     204,   206,   213,   214,   216,   202,  -308,  -308,   716,   161,
    1932,    34,   230,  1973,    60,   236,  2014,  -308,  -308,  2054,
     177,  2208,  1336,   166,  1340,  -308,  -308,  1340,  -308,  -308,
    -308,  1175,  2160,  -308,   232,  -308,  1340,   269,  1340,    61,
     -29,  1340,   193,   237,   238,  -308,  -308,  -308,  -308,  2195,
    -308,  1340,  1340,  1340,  1340,  1340,  1408,    76,  -308,   124,
     126,    64,   802,   802,  -308,  -308,  -308,  -308,  -308,  -308,
    -308,  -308,  1340,   246,   253,   254,   255,  -308,  -308,  1340,
    1340,  1340,  1340,  1340,  1340,  1340,  1340,  1340,  1340,  1340,
     251,  -308,  1340,   256,  -308,  1340,   258,  1340,   265,  2208,
      70,  -308,  -308,  -308,  -308,   257,  1737,   272,  1750,   263,
    -308,  -308,  -308,   899,     4,  1784,  -308,  -308,  -308,    71,
      72,    79,    88,    89,  -308,   779,  2208,  1340,  1340,  1340,
    1340,  2208,  2208,  2208,  2208,  2208,  2208,  2208,  2208,  2208,
    2208,  2208,   275,    91,   276,    92,   284,  1797,  1340,  -308,
    -308,  1498,  1340,  1498,  1340,  1340,   -29,   134,   274,   282,
     285,   286,   287,  -308,  1831,  1553,  1598,  1643,  1340,  -308,
    1340,  -308,  1340,  -308,    98,   318,  1844,  -308,  2208,   314,
    1878,   353,  -308,  -308,  -308,  -308,  -308,  -308,   316,   317,
    1340,   319,  1340,   320,  1340,   104,   110,   111,  -308,  1498,
     326,    61,  1498,  1340,  -308,  -308,   337,  -308,   341,  -308,
     342,  -308,  -308,  -308,  -308,  -308,   350,  -308,  1891,   345,
     347,   348,  1498,  1498,  -308,  -308,  -308,  -308,  -308
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   235,   234,     0,     2,
       7,     8,     9,    14,    15,    16,     0,   238,   237,     0,
       0,     0,     1,     4,     5,     6,   196,     0,     0,    10,
      11,   240,     0,     0,   195,   232,     0,     0,   224,     0,
     247,   246,   226,   227,   228,   229,   230,     0,     0,     0,
     198,     0,     0,     0,     0,     0,   234,   239,   243,   245,
       0,   103,   104,   105,   143,   144,   145,   146,   147,   179,
     180,   148,   149,   150,   151,   152,   153,   154,   155,     0,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
       0,   166,   167,   168,   169,   170,   171,   172,   236,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   198,   225,   200,     0,   197,   203,   178,   173,
       0,     0,   242,   244,   215,   216,   176,   177,   175,     0,
     219,   220,   221,   222,   174,     0,   231,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   181,
     182,     0,   198,     0,    17,     0,    19,   194,     0,   198,
       0,     0,   198,     0,     0,     0,     0,   214,     0,   200,
       0,   193,     0,     0,     0,     0,     0,   136,   137,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     138,   139,   140,   141,   142,     0,   213,   233,   212,     0,
     197,   204,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,     0,    57,     0,     0,    48,    55,
       0,    49,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
       0,     0,     0,   215,   216,     0,   217,   218,     0,   223,
       0,     0,     0,     0,     0,     0,     0,   201,   202,     0,
       0,   199,     0,     0,     0,   211,   183,   198,    59,    53,
      51,     0,     0,    79,     0,    80,     0,     0,     0,    65,
       0,     0,     0,     0,     0,    92,    93,    94,    96,     0,
      97,   198,   198,   198,   198,   198,     0,     0,   207,   217,
     218,   223,   120,   122,    60,    56,    54,    68,    69,    70,
      66,    67,     0,     0,     0,     0,     0,   121,   123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   185,   198,     0,   187,   198,     0,     0,     0,   124,
       0,    58,    52,    50,    74,     0,     0,     0,     0,     0,
      62,    63,    64,     0,     0,     0,    91,    90,    95,     0,
       0,     0,     0,     0,   205,     0,   108,     0,     0,     0,
       0,   109,   115,   116,   117,   118,   119,   110,   111,   112,
     114,   113,     0,     0,     0,     0,     0,     0,   198,   184,
      81,     0,     0,     0,   107,     0,     0,     0,     0,     0,
       0,     0,     0,   206,     0,     0,     0,     0,   198,   186,
     198,   188,   198,   241,     0,    82,     0,    84,   106,     0,
       0,     0,    89,    98,    99,   100,   101,   102,     0,     0,
     198,     0,   198,     0,   198,     0,     0,     0,   189,     0,
       0,    65,     0,     0,    71,    73,   197,    76,   197,    78,
     197,   190,   191,   192,    83,    85,     0,    87,     0,     0,
       0,     0,     0,     0,    72,    75,    77,    86,    88
  };

  const short
  parser::yypgoto_[] =
  {
    -308,  -308,  -308,   394,   401,   407,  -308,  -308,  -308,  -155,
     180,  -308,  -308,  -308,   -99,   -53,  -308,  -308,  -308,  -308,
    -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,
    -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,
    -308,  -308,  -308,   211,  -308,  -307,  -303,  -302,  -308,  -308,
    -308,  -308,  -308,  -308,    -9,    18,   -76,   -71,  -308,  -308,
    -147,   -45,  -308,  -308,  -308,  -308,  -308,    38,   219,   315,
    -308,   373,   414,  -308,  -308,  -308,   432,   441,   520,   531,
    -308,  -308,  -308,     0,     7,  -308,   -17,  -308,  -308,   207,
    -308,  -308
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    11,    12,    13,    14,    15,   238,
     239,   301,   240,   241,   242,   379,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   114,   449,   270,   271,   272,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    33,
     115,   210,    72,    73,    74,   275,   327,   328,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,   208,    89,    90,    91,    92,    93,    94,    95,
      96,    97
  };

  const short
  parser::yytable_[] =
  {
      16,   166,   380,   159,    32,   116,   381,   382,   160,    16,
      19,    20,     6,    26,     6,   209,     1,     2,     3,     4,
       5,    28,   281,   102,   206,   284,    34,   425,  -223,  -223,
     304,  -223,    22,   100,    21,  -223,   103,   106,   101,    29,
      27,   305,   162,   104,   107,   124,  -223,   296,    30,  -223,
     312,   117,   180,   159,   134,     6,    31,   300,   160,    59,
     426,   135,   307,    31,     6,    17,    56,   116,     7,   154,
     155,   156,   125,    36,    37,   105,    39,    99,   207,   161,
       6,    43,    44,    45,    46,   361,   135,   120,  -223,  -223,
     180,   121,  -215,  -215,    98,  -215,   108,    36,    37,  -215,
      39,   167,    17,    18,     6,    43,    44,    45,    46,     7,
    -215,   364,   109,  -215,   162,   234,   180,    17,    56,  -210,
    -210,   419,   428,   429,   236,   237,   180,   180,   180,   161,
     430,   394,   395,    17,    56,   180,   135,   122,   123,   431,
     432,   136,   439,   441,   180,   180,   373,   180,   180,   468,
     370,   110,  -215,  -215,   180,   481,   273,    17,    56,  -237,
     180,   482,   483,   211,   380,   279,   180,   180,   381,   382,
     282,   163,   135,   285,   389,   390,   391,   392,   393,  -208,
    -208,  -209,  -209,   274,   164,   293,   165,   168,    36,    37,
     169,    39,   171,   172,   170,     6,    43,    44,    45,    46,
     173,   174,   159,   273,   180,   313,   326,   160,   273,   181,
     183,   162,   279,   207,   185,   413,   297,   279,   415,   135,
     303,   306,   308,   309,   135,   124,   310,   124,   124,   311,
     274,   273,   368,   321,   331,   274,   279,   279,    60,   316,
     279,   135,   315,   135,   135,   317,   320,   135,    17,    56,
     322,   323,   125,   324,   125,   125,   159,   159,   274,   325,
     111,   160,   160,   118,   119,   337,   445,   338,   447,  -216,
    -216,   444,  -216,   126,   339,   340,  -216,   341,   161,   342,
     362,  -217,  -217,   375,  -217,   135,   365,  -216,  -217,   377,
    -216,   465,   273,   466,   123,   467,   397,   386,   387,  -217,
     124,   279,  -217,   398,   399,   400,   412,   159,   135,   279,
     384,   414,   160,   416,   484,   418,   135,   487,   420,   274,
     175,   176,   422,   179,   424,   438,   440,   125,   452,  -216,
    -216,   182,   161,   161,   442,   453,   469,   497,   498,   135,
     135,  -217,  -217,   454,   139,   140,   455,   456,   457,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   127,
     152,   153,   154,   155,   156,   471,   473,   474,   475,   280,
     477,   479,   283,   161,   276,   286,   124,   485,   489,   289,
     135,   291,   490,   491,   292,   331,   152,   153,   154,   155,
     156,   492,   135,    23,  -218,  -218,   494,  -218,   495,   496,
      24,  -218,   273,   125,   273,   476,    25,   478,   486,   480,
     336,   279,  -218,   279,   302,  -218,   451,   128,   135,   314,
     135,   276,     0,   433,     0,     0,   276,   319,     0,   274,
       0,   274,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   329,     0,   276,   276,     0,     0,   276,
     273,     0,   124,   273,  -218,  -218,     0,     0,   129,   279,
       0,   279,   279,     0,     0,     0,   135,     0,   135,   135,
     277,     0,     0,   273,   273,     0,   130,   274,     0,   125,
     274,     0,   279,   279,     0,   131,     0,     0,     0,   135,
     135,     0,     0,     0,     0,   369,     0,     0,     0,     0,
     274,   274,     0,     0,     0,     0,     0,   376,     0,   378,
     276,     0,   385,    36,    37,     0,    39,   277,   276,     0,
       6,     0,   277,     0,     0,     0,     0,   292,     0,     0,
       0,   157,     0,     0,   158,     0,     0,     0,     0,   330,
       0,   277,   277,   396,     0,   277,     0,     0,     0,     0,
     401,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,     0,     0,     0,   132,     0,     0,     0,   417,   278,
       0,     0,     0,    17,    56,   133,  -219,  -219,     0,  -219,
       0,     0,     0,  -219,     0,     0,     0,   130,     0,     0,
       0,     0,     0,     0,  -219,     0,   131,  -219,   434,   435,
     436,   437,     0,     0,   329,     0,   277,     0,     0,     0,
       0,     0,     0,     0,   277,     0,   278,     0,     0,     0,
       0,   278,     0,   446,     0,   448,   450,     0,  -220,  -220,
     276,  -220,   276,     0,   130,  -220,  -219,  -219,   129,   130,
     332,   333,     0,   131,   278,     0,  -220,     0,   131,  -220,
       0,     0,     0,     0,     0,     0,   130,     0,   130,   130,
       0,     0,   130,     0,     0,   131,     0,   131,   131,  -221,
    -221,   131,  -221,     0,   488,   132,  -221,     0,   276,     0,
     276,   276,     0,     0,     0,     0,   133,  -221,  -220,  -220,
    -221,  -222,  -222,     0,  -222,     0,     0,     0,  -222,     0,
     330,   276,   276,     0,     0,   278,     0,     0,     0,  -222,
       0,     0,  -222,   383,     0,     0,   343,   344,     0,   345,
     346,     0,   132,   130,     0,     0,   277,   132,   277,  -221,
    -221,   130,   131,   133,     0,     0,     0,     0,   133,     0,
     131,     0,    36,    37,   132,    39,   132,   132,     0,     6,
     132,  -222,  -222,     0,     0,   133,     0,   133,   133,     0,
     157,   133,     0,   184,     0,     0,     0,     0,     0,   347,
     348,     0,     0,     0,   277,     0,   277,   277,     0,     0,
       0,     0,     0,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,     0,     0,     0,   277,   277,   129,
       0,     0,    17,    56,     0,    36,    37,     0,    39,     0,
       0,   132,     6,    43,    44,    45,    46,   130,     0,   132,
       0,     0,   133,   121,     0,   278,   131,   278,    36,    37,
     133,    39,     0,   139,   140,     6,   142,   143,   144,   145,
     146,   147,   148,   130,     0,   130,   157,     0,     0,   184,
       0,     0,   131,     0,   131,     0,   149,   150,   151,   152,
     153,   154,   155,   156,     0,    17,    56,     0,     0,     0,
       0,     0,     0,   278,     0,   383,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    56,
       0,   130,     0,   130,   130,     0,   278,   278,     0,     0,
     131,     0,   131,   131,     0,   132,     0,     0,     0,     0,
       0,   139,   140,     0,   130,   130,   133,   145,   146,   147,
     148,     0,     0,   131,   131,    36,    37,     0,    39,     0,
       0,   132,     6,   132,     0,     0,     0,   152,   153,   154,
     155,   156,   133,   157,   133,     0,   184,     0,     0,     0,
       0,     0,   347,   348,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,     0,     0,   132,
       0,   132,   132,     0,     0,    17,    56,     0,     0,     0,
     133,     0,   133,   133,     0,     0,     0,     0,     0,     0,
       0,     0,   132,   132,   212,     0,     0,     0,     0,     0,
       0,     0,   213,   133,   133,   214,   215,   216,     0,   217,
     218,   219,   220,     0,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,    36,    37,     0,    39,
       0,     0,     0,     6,    43,    44,    45,    46,     0,     0,
       0,     0,   165,   233,   234,     0,     0,     0,     0,   212,
       0,   235,     0,   236,   237,     0,     0,   213,     0,     0,
     214,   215,   216,     0,   217,   218,   219,   220,     0,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,    36,    37,     0,    39,     0,    17,    56,     6,    43,
      44,    45,    46,     0,     0,     0,     0,   165,   334,   234,
       0,     0,     0,     0,     0,   298,   335,     0,   236,   237,
       0,     0,   213,     0,     0,   214,   215,   216,     0,   217,
     218,   219,   220,     0,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,    36,    37,     0,    39,
       0,    17,    56,     6,    43,    44,    45,    46,     0,     0,
       0,     0,   165,     0,   234,     0,     0,     0,     0,     0,
     371,   299,     0,   236,   237,     0,     0,   213,     0,     0,
     214,   215,   216,     0,   217,   218,   219,   220,     0,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,    36,    37,    35,    39,     0,    17,    56,     6,    43,
      44,    45,    46,     0,     0,     0,     0,   165,     0,   234,
       0,     0,     0,     0,     0,     0,   372,     0,   236,   237,
      36,    37,    38,    39,    40,    41,    42,     6,    43,    44,
      45,    46,    47,    48,    49,     0,     0,     0,   112,   113,
     139,   140,     0,    51,   143,   144,   145,   146,   147,   148,
       0,    17,    56,     0,     0,     0,     0,     0,     0,    52,
      53,    35,     0,   149,   150,   151,   152,   153,   154,   155,
     156,     0,     0,     0,     0,     0,    54,     0,     0,    55,
      17,    56,    31,    57,    58,    59,     0,     0,    36,    37,
      38,    39,    40,    41,    42,     6,    43,    44,    45,    46,
      47,    48,    49,     0,     0,     0,    50,     0,     0,     0,
       0,    51,     0,   318,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    52,    53,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,     0,     0,    55,    17,    56,
      31,    57,    58,    59,     0,     0,    36,    37,    38,    39,
      40,    41,    42,     6,    43,    44,    45,    46,    47,    48,
      49,   290,     0,     0,    50,     0,     0,     0,   138,    51,
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,     0,     0,     0,     0,    52,    53,    35,     0,     0,
       0,     0,     0,     0,   149,   150,   151,   152,   153,   154,
     155,   156,    54,     0,     0,    55,    17,    56,    31,    57,
      58,    59,     0,     0,    36,    37,    38,    39,    40,    41,
      42,     6,    43,    44,    45,    46,    47,    48,    49,   295,
       0,     0,   112,     0,     0,     0,   138,    51,     0,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,     0,
       0,     0,     0,    52,    53,     0,     0,     0,     0,     0,
       0,     0,   149,   150,   151,   152,   153,   154,   155,   156,
      54,     0,     0,    55,    17,    56,    31,    57,    58,    59,
     213,     0,     0,   214,   215,   216,     0,   217,   218,   219,
     220,     0,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,    36,    37,     0,    39,     0,     0,
       0,     6,    43,    44,    45,    46,     0,     0,     0,     0,
     165,     0,   234,     0,     0,     0,     0,     0,     0,   177,
       0,   236,   237,     0,   178,     0,     0,     0,     0,     0,
     138,     0,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,     0,   139,   140,     0,     0,   143,   144,
     145,   146,   147,   148,    17,    56,   149,   150,   151,   152,
     153,   154,   155,   156,   459,     0,     0,     0,   150,   460,
     152,   153,   154,   155,   156,   138,     0,     0,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,     0,   139,
     140,     0,     0,   143,   144,   145,   146,   147,   148,     0,
       0,   149,   150,   151,   152,   153,   154,   155,   156,   461,
       0,     0,     0,     0,   462,   152,   153,   154,   155,   156,
     138,     0,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   149,   150,   151,   152,
     153,   154,   155,   156,   463,     0,     0,     0,     0,   464,
       0,     0,     0,     0,     0,   138,     0,   287,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   138,     0,
       0,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
       0,   288,     0,     0,   149,   150,   151,   152,   153,   154,
     155,   156,   138,     0,   177,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   138,     0,     0,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,     0,     0,   421,     0,
       0,   149,   150,   151,   152,   153,   154,   155,   156,   138,
       0,   423,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   138,     0,     0,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,     0,     0,   427,     0,     0,   149,   150,
     151,   152,   153,   154,   155,   156,   138,     0,   443,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   138,
       0,     0,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
       0,     0,   458,     0,     0,   149,   150,   151,   152,   153,
     154,   155,   156,   138,     0,   470,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   138,     0,     0,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,     0,   472,
       0,     0,   149,   150,   151,   152,   153,   154,   155,   156,
     138,     0,   493,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   138,     0,     0,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,     0,     0,     0,     0,   149,
     150,   151,   152,   153,   154,   155,   156,   360,     0,     0,
       0,     0,     0,     0,   138,     0,     0,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     149,   150,   151,   152,   153,   154,   155,   156,   363,     0,
       0,     0,     0,     0,     0,   138,     0,     0,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,   153,   154,   155,   156,   366,
       0,     0,     0,     0,     0,     0,   138,     0,     0,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   149,   150,   151,   152,   153,   154,   155,   156,
     367,     0,     0,     0,     0,     0,   138,     0,     0,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   149,   150,   151,   152,   153,   154,   155,   156,
     294,     0,   138,     0,     0,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,   150,
     151,   152,   153,   154,   155,   156,   137,   138,     0,     0,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   150,   151,   152,   153,   154,   155,
     156,   374,   138,     0,     0,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   149,   150,
     151,   152,   153,   154,   155,   156,   388,   138,     0,     0,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     138,     0,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,     0,     0,     0,     0,   149,   150,   151,   152,
     153,   154,   155,   156,   139,   140,     0,     0,   143,   144,
     145,   146,   147,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,   154,   155,   156
  };

  const short
  parser::yycheck_[] =
  {
       0,   100,   309,    79,    21,    50,   309,   309,    79,     9,
       3,     4,    43,    50,    43,   162,     4,     5,     6,     7,
       8,    94,   169,    54,    43,   172,    26,    23,    36,    37,
      50,    39,     0,    51,    50,    43,    36,    37,    56,    61,
      77,    61,    50,    36,    37,    54,    54,    51,    61,    57,
      92,    51,    56,   129,    54,    43,    98,   212,   129,   101,
      56,    54,   217,    98,    43,    96,    97,   112,    97,    93,
      94,    95,    54,    36,    37,    54,    39,    51,    97,    79,
      43,    44,    45,    46,    47,    51,    79,    50,    96,    97,
      56,    54,    36,    37,    97,    39,    54,    36,    37,    43,
      39,   101,    96,    97,    43,    44,    45,    46,    47,    97,
      54,    51,    50,    57,    50,    54,    56,    96,    97,    55,
      56,    51,    51,    51,    63,    64,    56,    56,    56,   129,
      51,    55,    56,    96,    97,    56,   129,   100,   101,    51,
      51,    97,    51,    51,    56,    56,   301,    56,    56,    51,
     297,    50,    96,    97,    56,    51,   165,    96,    97,    59,
      56,    51,    51,   163,   471,   165,    56,    56,   471,   471,
     170,    59,   165,   173,   321,   322,   323,   324,   325,    55,
      56,    55,    56,   165,    61,   185,    52,    54,    36,    37,
      50,    39,    54,    50,    59,    43,    44,    45,    46,    47,
      59,    54,   278,   212,    56,   222,    54,   278,   217,    55,
      54,    50,   212,    97,    59,   362,    50,   217,   365,   212,
      61,    50,    50,    50,   217,   234,    50,   236,   237,    50,
     212,   240,    55,    50,   234,   217,   236,   237,    27,    61,
     240,   234,    60,   236,   237,    61,    61,   240,    96,    97,
      50,    50,   234,    50,   236,   237,   332,   333,   240,    50,
      49,   332,   333,    52,    53,    61,   421,    61,   423,    36,
      37,   418,    39,    54,    61,    61,    43,    61,   278,    77,
      50,    36,    37,    51,    39,   278,    50,    54,    43,    20,
      57,   438,   301,   440,   101,   442,    50,    60,    60,    54,
     309,   301,    57,    50,    50,    50,    55,   383,   301,   309,
     310,    55,   383,    55,   469,    50,   309,   472,    61,   301,
     109,   110,    50,   112,    61,    50,    50,   309,   427,    96,
      97,   120,   332,   333,    50,    61,    18,   492,   493,   332,
     333,    96,    97,    61,    65,    66,    61,    61,    61,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,    54,
      91,    92,    93,    94,    95,    61,    23,    61,    61,   168,
      61,    61,   171,   383,   165,   174,   395,    61,    51,   178,
     383,   180,    51,    51,   183,   395,    91,    92,    93,    94,
      95,    51,   395,     9,    36,    37,    61,    39,    61,    61,
       9,    43,   421,   395,   423,   460,     9,   462,   471,   464,
     240,   421,    54,   423,   213,    57,   426,    54,   421,   222,
     423,   212,    -1,   395,    -1,    -1,   217,   226,    -1,   421,
      -1,   423,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   234,    -1,   236,   237,    -1,    -1,   240,
     469,    -1,   471,   472,    96,    97,    -1,    -1,    54,   469,
      -1,   471,   472,    -1,    -1,    -1,   469,    -1,   471,   472,
     165,    -1,    -1,   492,   493,    -1,    54,   469,    -1,   471,
     472,    -1,   492,   493,    -1,    54,    -1,    -1,    -1,   492,
     493,    -1,    -1,    -1,    -1,   294,    -1,    -1,    -1,    -1,
     492,   493,    -1,    -1,    -1,    -1,    -1,   306,    -1,   308,
     301,    -1,   311,    36,    37,    -1,    39,   212,   309,    -1,
      43,    -1,   217,    -1,    -1,    -1,    -1,   326,    -1,    -1,
      -1,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,   234,
      -1,   236,   237,   342,    -1,   240,    -1,    -1,    -1,    -1,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,    -1,    -1,    -1,    54,    -1,    -1,    -1,   367,   165,
      -1,    -1,    -1,    96,    97,    54,    36,    37,    -1,    39,
      -1,    -1,    -1,    43,    -1,    -1,    -1,   165,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,   165,    57,   397,   398,
     399,   400,    -1,    -1,   395,    -1,   301,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   309,    -1,   212,    -1,    -1,    -1,
      -1,   217,    -1,   422,    -1,   424,   425,    -1,    36,    37,
     421,    39,   423,    -1,   212,    43,    96,    97,   234,   217,
     236,   237,    -1,   212,   240,    -1,    54,    -1,   217,    57,
      -1,    -1,    -1,    -1,    -1,    -1,   234,    -1,   236,   237,
      -1,    -1,   240,    -1,    -1,   234,    -1,   236,   237,    36,
      37,   240,    39,    -1,   473,   165,    43,    -1,   469,    -1,
     471,   472,    -1,    -1,    -1,    -1,   165,    54,    96,    97,
      57,    36,    37,    -1,    39,    -1,    -1,    -1,    43,    -1,
     395,   492,   493,    -1,    -1,   301,    -1,    -1,    -1,    54,
      -1,    -1,    57,   309,    -1,    -1,    10,    11,    -1,    13,
      14,    -1,   212,   301,    -1,    -1,   421,   217,   423,    96,
      97,   309,   301,   212,    -1,    -1,    -1,    -1,   217,    -1,
     309,    -1,    36,    37,   234,    39,   236,   237,    -1,    43,
     240,    96,    97,    -1,    -1,   234,    -1,   236,   237,    -1,
      54,   240,    -1,    57,    -1,    -1,    -1,    -1,    -1,    63,
      64,    -1,    -1,    -1,   469,    -1,   471,   472,    -1,    -1,
      -1,    -1,    -1,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    -1,    -1,    -1,   492,   493,   395,
      -1,    -1,    96,    97,    -1,    36,    37,    -1,    39,    -1,
      -1,   301,    43,    44,    45,    46,    47,   395,    -1,   309,
      -1,    -1,   301,    54,    -1,   421,   395,   423,    36,    37,
     309,    39,    -1,    65,    66,    43,    68,    69,    70,    71,
      72,    73,    74,   421,    -1,   423,    54,    -1,    -1,    57,
      -1,    -1,   421,    -1,   423,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    -1,    96,    97,    -1,    -1,    -1,
      -1,    -1,    -1,   469,    -1,   471,   472,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    97,
      -1,   469,    -1,   471,   472,    -1,   492,   493,    -1,    -1,
     469,    -1,   471,   472,    -1,   395,    -1,    -1,    -1,    -1,
      -1,    65,    66,    -1,   492,   493,   395,    71,    72,    73,
      74,    -1,    -1,   492,   493,    36,    37,    -1,    39,    -1,
      -1,   421,    43,   423,    -1,    -1,    -1,    91,    92,    93,
      94,    95,   421,    54,   423,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    -1,    -1,   469,
      -1,   471,   472,    -1,    -1,    96,    97,    -1,    -1,    -1,
     469,    -1,   471,   472,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   492,   493,     4,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,   492,   493,    15,    16,    17,    -1,    19,
      20,    21,    22,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      -1,    -1,    -1,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,     4,
      -1,    61,    -1,    63,    64,    -1,    -1,    12,    -1,    -1,
      15,    16,    17,    -1,    19,    20,    21,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    39,    -1,    96,    97,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,     5,    61,    -1,    63,    64,
      -1,    -1,    12,    -1,    -1,    15,    16,    17,    -1,    19,
      20,    21,    22,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      -1,    96,    97,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,
       5,    61,    -1,    63,    64,    -1,    -1,    12,    -1,    -1,
      15,    16,    17,    -1,    19,    20,    21,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,     9,    39,    -1,    96,    97,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    63,    64,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    54,    55,
      65,    66,    -1,    59,    69,    70,    71,    72,    73,    74,
      -1,    96,    97,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,     9,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,
      96,    97,    98,    99,   100,   101,    -1,    -1,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    59,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,    -1,    -1,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    55,    -1,    -1,    54,    -1,    -1,    -1,    62,    59,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    75,    76,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    92,    -1,    -1,    95,    96,    97,    98,    99,
     100,   101,    -1,    -1,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    55,
      -1,    -1,    54,    -1,    -1,    -1,    62,    59,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      92,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
      12,    -1,    -1,    15,    16,    17,    -1,    19,    20,    21,
      22,    -1,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    39,    -1,    -1,
      -1,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    63,    64,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    65,    66,    -1,    -1,    69,    70,
      71,    72,    73,    74,    96,    97,    88,    89,    90,    91,
      92,    93,    94,    95,    51,    -1,    -1,    -1,    89,    56,
      91,    92,    93,    94,    95,    62,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    65,
      66,    -1,    -1,    69,    70,    71,    72,    73,    74,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    51,
      -1,    -1,    -1,    -1,    56,    91,    92,    93,    94,    95,
      62,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    51,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    51,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    62,    -1,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    88,    89,    90,    91,    92,    93,    94,    95,    -1,
      -1,    51,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    62,    -1,    51,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    62,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    88,    89,
      90,    91,    92,    93,    94,    95,    -1,    -1,    51,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    62,
      -1,    51,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    62,    -1,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    88,    89,    90,    91,    92,
      93,    94,    95,    -1,    -1,    51,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    62,    -1,    51,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    62,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    88,    89,    90,    91,    92,    93,    94,    95,
      -1,    -1,    51,    -1,    -1,    88,    89,    90,    91,    92,
      93,    94,    95,    62,    -1,    51,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    62,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    88,
      89,    90,    91,    92,    93,    94,    95,    -1,    -1,    51,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      62,    -1,    51,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    88,    89,    90,    91,
      92,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      60,    -1,    62,    -1,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    61,    62,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    94,
      95,    61,    62,    -1,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    61,    62,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      62,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    88,    89,    90,    91,    92,    93,    94,
      95,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    65,    66,    -1,    -1,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94,    95
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     4,     5,     6,     7,     8,    43,    97,   113,   114,
     115,   116,   117,   118,   119,   120,   195,    96,    97,   196,
     196,    50,     0,   115,   116,   117,    50,    77,    94,    61,
      61,    98,   198,   171,   195,     9,    36,    37,    38,    39,
      40,    41,    42,    44,    45,    46,    47,    48,    49,    50,
      54,    59,    75,    76,    92,    95,    97,    99,   100,   101,
     155,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   174,   175,   176,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   195,
     196,   197,   198,   199,   200,   201,   202,   203,    97,    51,
      51,    56,    54,   195,   196,    54,   195,   196,    54,    50,
      50,   155,    54,    55,   155,   172,   173,   195,   155,   155,
      50,    54,   100,   101,   166,   167,   180,   181,   183,   184,
     188,   189,   190,   191,   195,   196,    97,    61,    62,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    88,
      89,    90,    91,    92,    93,    94,    95,    54,    57,   168,
     169,   195,    50,    59,    61,    52,   126,   195,    54,    50,
      59,    54,    50,    59,    54,   155,   155,    51,    56,   155,
      56,    55,   155,    54,    57,    59,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,    43,    97,   194,   172,
     173,   195,     4,    12,    15,    16,    17,    19,    20,    21,
      22,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    53,    54,    61,    63,    64,   121,   122,
     124,   125,   126,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     157,   158,   159,   166,   167,   177,   180,   181,   184,   195,
     155,   172,   195,   155,   172,   195,   155,    51,    51,   155,
      55,   155,   155,   195,    60,    55,    51,    50,     5,    61,
     121,   123,   155,    61,    50,    61,    50,   121,    50,    50,
      50,    50,    92,   198,   201,    60,    61,    61,    61,   155,
      61,    50,    50,    50,    50,    50,    54,   178,   179,   180,
     181,   195,   184,   184,    53,    61,   122,    61,    61,    61,
      61,    61,    77,    10,    11,    13,    14,    63,    64,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      55,    51,    50,    55,    51,    50,    55,    56,    55,   155,
     172,     5,    61,   121,    61,    51,   155,    20,   155,   127,
     157,   158,   159,   184,   195,   155,    60,    60,    61,   172,
     172,   172,   172,   172,    55,    56,   155,    50,    50,    50,
      50,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,    55,   172,    55,   172,    55,   155,    50,    51,
      61,    51,    50,    51,    61,    23,    56,    51,    51,    51,
      51,    51,    51,   179,   155,   155,   155,   155,    50,    51,
      50,    51,    50,    51,   172,   121,   155,   121,   155,   156,
     155,   195,   126,    61,    61,    61,    61,    61,    51,    51,
      56,    51,    56,    51,    56,   172,   172,   172,    51,    18,
      51,    61,    51,    23,    61,    61,   173,    61,   173,    61,
     173,    51,    51,    51,   121,    61,   127,   121,   155,    51,
      51,    51,    51,    51,    61,    61,    61,   121,   121
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   112,   113,   113,   114,   114,   114,   114,   114,   114,
     115,   116,   117,   117,   117,   117,   117,   118,   119,   120,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   122,   122,
     123,   123,   123,   123,   124,   124,   124,   124,   125,   125,
     126,   126,   127,   127,   127,   127,   128,   128,   129,   129,
     129,   130,   131,   131,   132,   133,   133,   134,   134,   135,
     136,   136,   137,   138,   139,   140,   141,   142,   142,   143,
     144,   144,   145,   146,   147,   148,   148,   149,   150,   151,
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
     191,   192,   193,   194,   195,   195,   196,   196,   196,   197,
     198,   199,   200,   200,   201,   201,   202,   203
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     5,     4,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     2,     1,     2,     1,     3,     2,
       3,     2,     1,     1,     1,     0,     2,     2,     2,     2,
       2,     6,     8,     6,     3,     8,     6,     8,     6,     2,
       2,     4,     5,     7,     5,     7,     9,     7,     9,     5,
       3,     3,     2,     2,     2,     3,     2,     2,     5,     5,
       5,     5,     5,     1,     1,     1,     1,     0,     3,     3,
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
       1,     2,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     7,     2,     1,     2,     1,     1,     1
  };




#if GSCDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   274,   274,   275,   279,   281,   283,   285,   287,   289,
     294,   298,   303,   304,   305,   306,   307,   311,   316,   324,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   360,   361,
     365,   367,   369,   371,   376,   378,   380,   382,   387,   388,
     392,   393,   397,   399,   401,   404,   408,   410,   415,   417,
     419,   424,   429,   431,   436,   441,   443,   448,   450,   455,
     460,   462,   467,   472,   477,   482,   487,   492,   497,   506,
     513,   515,   520,   525,   530,   535,   537,   542,   547,   552,
     557,   562,   567,   572,   573,   574,   578,   579,   583,   585,
     587,   589,   591,   593,   595,   597,   599,   601,   603,   605,
     610,   612,   617,   619,   624,   629,   631,   633,   635,   637,
     639,   641,   643,   645,   647,   649,   651,   653,   655,   657,
     659,   661,   663,   668,   669,   670,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,   701,   706,   708,   710,   712,   717,   722,
     723,   726,   727,   731,   733,   735,   737,   739,   741,   746,
     748,   750,   752,   757,   762,   764,   767,   771,   774,   778,
     780,   785,   790,   795,   797,   802,   809,   811,   816,   817,
     818,   822,   827,   832,   837,   842,   843,   844,   845,   846,
     847,   848,   849,   850,   854,   859,   864,   869,   874,   879,
     884,   889,   894,   899,   904,   906,   911,   913,   915,   920,
     925,   930,   935,   937,   942,   944,   949,   954
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
#line 4937 "parser.cpp"

#line 958 "parser.ypp"


namespace xsk::gsc
{

void parser::error(location const& loc, std::string const& msg)
{
    throw comp_error(loc, msg);
}

auto parse_switch(stmt_switch& stm) -> void
{
    auto body = make_stmt_list(stm.body->block->loc());
    auto current_case = stmt{ nullptr };

    auto num = stm.body->block->list.size();

    for (auto i = 0u; i < num; i++)
    {
        auto& entry = stm.body->block->list[0];

        if (entry == node::stmt_case || entry == node::stmt_default)
        {
            if (current_case.as_node != nullptr)
            {
                body->list.push_back(std::move(current_case));
            }

            current_case = std::move(stm.body->block->list[0]);
            stm.body->block->list.erase(stm.body->block->list.begin());
        }
        else
        {
            if (current_case.as_node != nullptr)
            {
                if (current_case == node::stmt_case)
                {
                    current_case.as_case->body->list.push_back(std::move(entry));
                    stm.body->block->list.erase(stm.body->block->list.begin());
                }
                else
                {
                    current_case.as_default->body->list.push_back(std::move(entry));
                    stm.body->block->list.erase(stm.body->block->list.begin());
                }
            }
            else
            {
                throw comp_error(entry.loc(), "missing case statement");
            }
        }
    }

    if (current_case.as_node != nullptr)
    {
        body->list.push_back(std::move(current_case));
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
                    parser::symbol_type(it->second, tok.pos);
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
