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
#line 266 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program::ptr > ()); }
#line 2081 "parser.cpp"
    break;

  case 3: // root: %empty
#line 267 "parser.ypp"
              { ast = make_program(yylhs.location); }
#line 2087 "parser.cpp"
    break;

  case 4: // program: program inline
#line 272 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2093 "parser.cpp"
    break;

  case 5: // program: program include
#line 274 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2099 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 276 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl > ())); }
#line 2105 "parser.cpp"
    break;

  case 7: // program: inline
#line 278 "parser.ypp"
        { yylhs.value.as < program::ptr > () = make_program(yylhs.location); }
#line 2111 "parser.cpp"
    break;

  case 8: // program: include
#line 280 "parser.ypp"
        { yylhs.value.as < program::ptr > () = make_program(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2117 "parser.cpp"
    break;

  case 9: // program: declaration
#line 282 "parser.ypp"
        { yylhs.value.as < program::ptr > () = make_program(yylhs.location); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl > ())); }
#line 2123 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 286 "parser.ypp"
                                 { ppr.push_header(yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2129 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 291 "parser.ypp"
        { yylhs.value.as < include::ptr > () = make_include(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2135 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 295 "parser.ypp"
                        { yylhs.value.as < decl > ().as_dev_begin = make_decl_dev_begin(yylhs.location); }
#line 2141 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 296 "parser.ypp"
                        { yylhs.value.as < decl > ().as_dev_end = make_decl_dev_end(yylhs.location); }
#line 2147 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 297 "parser.ypp"
                        { yylhs.value.as < decl > ().as_usingtree = std::move(yystack_[0].value.as < decl_usingtree::ptr > ()); }
#line 2153 "parser.cpp"
    break;

  case 15: // declaration: decl_function
#line 298 "parser.ypp"
                        { yylhs.value.as < decl > ().as_function = std::move(yystack_[0].value.as < decl_function::ptr > ()); }
#line 2159 "parser.cpp"
    break;

  case 16: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 303 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_usingtree::ptr > () = make_decl_usingtree(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 2165 "parser.cpp"
    break;

  case 17: // decl_function: expr_identifier "(" expr_parameters ")" stmt_comp
#line 308 "parser.ypp"
        { ppr.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = make_decl_function(yylhs.location, std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); }
#line 2171 "parser.cpp"
    break;

  case 18: // stmt: stmt_comp
#line 312 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_comp = std::move(yystack_[0].value.as < stmt_comp::ptr > ()); }
#line 2177 "parser.cpp"
    break;

  case 19: // stmt: stmt_call
#line 313 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_call = std::move(yystack_[0].value.as < stmt_call::ptr > ()); }
#line 2183 "parser.cpp"
    break;

  case 20: // stmt: stmt_assign
#line 314 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_assign = std::move(yystack_[0].value.as < stmt_assign::ptr > ()); }
#line 2189 "parser.cpp"
    break;

  case 21: // stmt: stmt_endon
#line 315 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_endon = std::move(yystack_[0].value.as < stmt_endon::ptr > ()); }
#line 2195 "parser.cpp"
    break;

  case 22: // stmt: stmt_notify
#line 316 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_notify = std::move(yystack_[0].value.as < stmt_notify::ptr > ()); }
#line 2201 "parser.cpp"
    break;

  case 23: // stmt: stmt_wait
#line 317 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_wait = std::move(yystack_[0].value.as < stmt_wait::ptr > ()); }
#line 2207 "parser.cpp"
    break;

  case 24: // stmt: stmt_waittill
#line 318 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waittill = std::move(yystack_[0].value.as < stmt_waittill::ptr > ()); }
#line 2213 "parser.cpp"
    break;

  case 25: // stmt: stmt_waittillmatch
#line 319 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < stmt_waittillmatch::ptr > ()); }
#line 2219 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittillframeend
#line 320 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < stmt_waittillframeend::ptr > ()); }
#line 2225 "parser.cpp"
    break;

  case 27: // stmt: stmt_waitframe
#line 321 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waitframe = std::move(yystack_[0].value.as < stmt_waitframe::ptr > ()); }
#line 2231 "parser.cpp"
    break;

  case 28: // stmt: stmt_if
#line 322 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_if = std::move(yystack_[0].value.as < stmt_if::ptr > ()); }
#line 2237 "parser.cpp"
    break;

  case 29: // stmt: stmt_ifelse
#line 323 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_ifelse = std::move(yystack_[0].value.as < stmt_ifelse::ptr > ()); }
#line 2243 "parser.cpp"
    break;

  case 30: // stmt: stmt_while
#line 324 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_while = std::move(yystack_[0].value.as < stmt_while::ptr > ()); }
#line 2249 "parser.cpp"
    break;

  case 31: // stmt: stmt_dowhile
#line 325 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_dowhile = std::move(yystack_[0].value.as < stmt_dowhile::ptr > ()); }
#line 2255 "parser.cpp"
    break;

  case 32: // stmt: stmt_for
#line 326 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_for = std::move(yystack_[0].value.as < stmt_for::ptr > ()); }
#line 2261 "parser.cpp"
    break;

  case 33: // stmt: stmt_foreach
#line 327 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_foreach = std::move(yystack_[0].value.as < stmt_foreach::ptr > ()); }
#line 2267 "parser.cpp"
    break;

  case 34: // stmt: stmt_switch
#line 328 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_switch = std::move(yystack_[0].value.as < stmt_switch::ptr > ()); }
#line 2273 "parser.cpp"
    break;

  case 35: // stmt: stmt_case
#line 329 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_case = std::move(yystack_[0].value.as < stmt_case::ptr > ()); }
#line 2279 "parser.cpp"
    break;

  case 36: // stmt: stmt_default
#line 330 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_default = std::move(yystack_[0].value.as < stmt_default::ptr > ()); }
#line 2285 "parser.cpp"
    break;

  case 37: // stmt: stmt_break
#line 331 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_break = std::move(yystack_[0].value.as < stmt_break::ptr > ()); }
#line 2291 "parser.cpp"
    break;

  case 38: // stmt: stmt_continue
#line 332 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_continue = std::move(yystack_[0].value.as < stmt_continue::ptr > ()); }
#line 2297 "parser.cpp"
    break;

  case 39: // stmt: stmt_return
#line 333 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_return = std::move(yystack_[0].value.as < stmt_return::ptr > ()); }
#line 2303 "parser.cpp"
    break;

  case 40: // stmt: stmt_breakpoint
#line 334 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_breakpoint = std::move(yystack_[0].value.as < stmt_breakpoint::ptr > ()); }
#line 2309 "parser.cpp"
    break;

  case 41: // stmt: stmt_prof_begin
#line 335 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_prof_begin = std::move(yystack_[0].value.as < stmt_prof_begin::ptr > ()); }
#line 2315 "parser.cpp"
    break;

  case 42: // stmt: stmt_prof_end
#line 336 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_prof_end = std::move(yystack_[0].value.as < stmt_prof_end::ptr > ()); }
#line 2321 "parser.cpp"
    break;

  case 43: // stmt_or_dev: stmt
#line 340 "parser.ypp"
               { yylhs.value.as < stmt > () = std::move(yystack_[0].value.as < stmt > ()); }
#line 2327 "parser.cpp"
    break;

  case 44: // stmt_or_dev: stmt_dev
#line 341 "parser.ypp"
               { yylhs.value.as < stmt > ().as_dev = std::move(yystack_[0].value.as < stmt_dev::ptr > ()); }
#line 2333 "parser.cpp"
    break;

  case 45: // stmt_list: stmt_list stmt
#line 346 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2339 "parser.cpp"
    break;

  case 46: // stmt_list: stmt
#line 348 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2345 "parser.cpp"
    break;

  case 47: // stmt_list: stmt_list ";"
#line 350 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2351 "parser.cpp"
    break;

  case 48: // stmt_list: ";"
#line 352 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); }
#line 2357 "parser.cpp"
    break;

  case 49: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 357 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2363 "parser.cpp"
    break;

  case 50: // stmt_or_dev_list: stmt_or_dev
#line 359 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2369 "parser.cpp"
    break;

  case 51: // stmt_or_dev_list: stmt_or_dev_list ";"
#line 361 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); }
#line 2375 "parser.cpp"
    break;

  case 52: // stmt_or_dev_list: ";"
#line 363 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); }
#line 2381 "parser.cpp"
    break;

  case 53: // stmt_dev: "/#" stmt_list "#/"
#line 367 "parser.ypp"
                                { yylhs.value.as < stmt_dev::ptr > () = make_stmt_dev(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2387 "parser.cpp"
    break;

  case 54: // stmt_dev: "/#" "#/"
#line 368 "parser.ypp"
                      { yylhs.value.as < stmt_dev::ptr > () = make_stmt_dev(yylhs.location, make_stmt_list(yylhs.location)); }
#line 2393 "parser.cpp"
    break;

  case 55: // stmt_comp: "{" stmt_or_dev_list "}"
#line 372 "parser.ypp"
                                     { yylhs.value.as < stmt_comp::ptr > () = make_stmt_comp(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2399 "parser.cpp"
    break;

  case 56: // stmt_comp: "{" "}"
#line 373 "parser.ypp"
                    { yylhs.value.as < stmt_comp::ptr > () = make_stmt_comp(yylhs.location, make_stmt_list(yylhs.location)); }
#line 2405 "parser.cpp"
    break;

  case 57: // stmt_expr: expr_assign
#line 378 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 2411 "parser.cpp"
    break;

  case 58: // stmt_expr: expr_increment
#line 380 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 2417 "parser.cpp"
    break;

  case 59: // stmt_expr: expr_decrement
#line 382 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 2423 "parser.cpp"
    break;

  case 60: // stmt_expr: %empty
#line 384 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, make_node(yylhs.location)); }
#line 2429 "parser.cpp"
    break;

  case 61: // stmt_call: expr_call ";"
#line 389 "parser.ypp"
        { yylhs.value.as < stmt_call::ptr > () = make_stmt_call(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_call::ptr > ()) }); }
#line 2435 "parser.cpp"
    break;

  case 62: // stmt_call: expr_method ";"
#line 391 "parser.ypp"
        { yylhs.value.as < stmt_call::ptr > () = make_stmt_call(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_method::ptr > ()) }); }
#line 2441 "parser.cpp"
    break;

  case 63: // stmt_assign: expr_assign ";"
#line 396 "parser.ypp"
        { yylhs.value.as < stmt_assign::ptr > () = make_stmt_assign(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2447 "parser.cpp"
    break;

  case 64: // stmt_assign: expr_increment ";"
#line 398 "parser.ypp"
        { yylhs.value.as < stmt_assign::ptr > () = make_stmt_assign(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2453 "parser.cpp"
    break;

  case 65: // stmt_assign: expr_decrement ";"
#line 400 "parser.ypp"
        { yylhs.value.as < stmt_assign::ptr > () = make_stmt_assign(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2459 "parser.cpp"
    break;

  case 66: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 405 "parser.ypp"
        { yylhs.value.as < stmt_endon::ptr > () = make_stmt_endon(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ())); }
#line 2465 "parser.cpp"
    break;

  case 67: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 410 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = make_stmt_notify(yylhs.location, std::move(yystack_[7].value.as < expr > ()), std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2471 "parser.cpp"
    break;

  case 68: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 412 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = make_stmt_notify(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), make_expr_arguments(yylhs.location)); }
#line 2477 "parser.cpp"
    break;

  case 69: // stmt_wait: "wait" expr ";"
#line 417 "parser.ypp"
        { yylhs.value.as < stmt_wait::ptr > () = make_stmt_wait(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2483 "parser.cpp"
    break;

  case 70: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 422 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = make_stmt_waittill(yylhs.location, std::move(yystack_[7].value.as < expr > ()), std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2489 "parser.cpp"
    break;

  case 71: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 424 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = make_stmt_waittill(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), make_expr_arguments(yylhs.location)); }
#line 2495 "parser.cpp"
    break;

  case 72: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 429 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = make_stmt_waittillmatch(yylhs.location, std::move(yystack_[7].value.as < expr > ()), std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2501 "parser.cpp"
    break;

  case 73: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 431 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = make_stmt_waittillmatch(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), make_expr_arguments(yylhs.location)); }
#line 2507 "parser.cpp"
    break;

  case 74: // stmt_waittillframeend: "waittillframeend" ";"
#line 436 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend::ptr > () = make_stmt_waittillframeend(yylhs.location); }
#line 2513 "parser.cpp"
    break;

  case 75: // stmt_waitframe: "waitframe" ";"
#line 441 "parser.ypp"
        { yylhs.value.as < stmt_waitframe::ptr > () = make_stmt_waitframe(yylhs.location); }
#line 2519 "parser.cpp"
    break;

  case 76: // stmt_waitframe: "waitframe" "(" ")" ";"
#line 443 "parser.ypp"
        { yylhs.value.as < stmt_waitframe::ptr > () = make_stmt_waitframe(yylhs.location); }
#line 2525 "parser.cpp"
    break;

  case 77: // stmt_if: "if" "(" expr ")" stmt
#line 448 "parser.ypp"
        { yylhs.value.as < stmt_if::ptr > () = make_stmt_if(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < stmt > ())); }
#line 2531 "parser.cpp"
    break;

  case 78: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 453 "parser.ypp"
        { yylhs.value.as < stmt_ifelse::ptr > () = make_stmt_ifelse(yylhs.location, std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < stmt > ()), std::move(yystack_[0].value.as < stmt > ())); }
#line 2537 "parser.cpp"
    break;

  case 79: // stmt_while: "while" "(" expr ")" stmt
#line 458 "parser.ypp"
        { yylhs.value.as < stmt_while::ptr > () = make_stmt_while(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < stmt > ())); }
#line 2543 "parser.cpp"
    break;

  case 80: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 463 "parser.ypp"
        { yylhs.value.as < stmt_dowhile::ptr > () = make_stmt_dowhile(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[5].value.as < stmt > ())); }
#line 2549 "parser.cpp"
    break;

  case 81: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 468 "parser.ypp"
        { yylhs.value.as < stmt_for::ptr > () = make_stmt_for(yylhs.location, stmt{ std::move(yystack_[6].value.as < stmt_expr::ptr > ()) }, std::move(yystack_[4].value.as < expr > ()), stmt{ std::move(yystack_[2].value.as < stmt_expr::ptr > ()) }, std::move(yystack_[0].value.as < stmt > ())); }
#line 2555 "parser.cpp"
    break;

  case 82: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 473 "parser.ypp"
        {
            auto array = expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) };
            auto key = expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) };
            yylhs.value.as < stmt_foreach::ptr > () = make_stmt_foreach(yylhs.location, std::move(yystack_[2].value.as < expr > ()), expr{ std::move(yystack_[4].value.as < expr_identifier::ptr > ()) }, expr{ make_node(yylhs.location) }, std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt > ()), false); }
#line 2564 "parser.cpp"
    break;

  case 83: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 478 "parser.ypp"
        {
            auto array = expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) };
            auto key = (ctx_->props() & props::foreach) ? expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) } : expr{ std::move(yystack_[6].value.as < expr_identifier::ptr > ()) };
            yylhs.value.as < stmt_foreach::ptr > () = make_stmt_foreach(yylhs.location, std::move(yystack_[2].value.as < expr > ()), expr{ std::move(yystack_[4].value.as < expr_identifier::ptr > ()) }, (ctx_->props() & props::foreach) ? expr{ std::move(yystack_[6].value.as < expr_identifier::ptr > ()) } : expr{ make_node(yylhs.location) }, std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt > ()), true);
        }
#line 2574 "parser.cpp"
    break;

  case 84: // stmt_switch: "switch" "(" expr ")" stmt_comp
#line 487 "parser.ypp"
        { yylhs.value.as < stmt_switch::ptr > () = make_stmt_switch(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); 
          parse_switch(*yylhs.value.as < stmt_switch::ptr > ());
        }
#line 2582 "parser.cpp"
    break;

  case 85: // stmt_case: "case" expr_integer ":"
#line 494 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = make_stmt_case(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_integer::ptr > ()) }, make_stmt_list(yylhs.location)); }
#line 2588 "parser.cpp"
    break;

  case 86: // stmt_case: "case" expr_string ":"
#line 496 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = make_stmt_case(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_string::ptr > ()) }, make_stmt_list(yylhs.location)); }
#line 2594 "parser.cpp"
    break;

  case 87: // stmt_default: "default" ":"
#line 501 "parser.ypp"
        { yylhs.value.as < stmt_default::ptr > () = make_stmt_default(yylhs.location, make_stmt_list(yylhs.location)); }
#line 2600 "parser.cpp"
    break;

  case 88: // stmt_break: "break" ";"
#line 506 "parser.ypp"
        { yylhs.value.as < stmt_break::ptr > () = make_stmt_break(yylhs.location); }
#line 2606 "parser.cpp"
    break;

  case 89: // stmt_continue: "continue" ";"
#line 511 "parser.ypp"
        { yylhs.value.as < stmt_continue::ptr > () = make_stmt_continue(yylhs.location); }
#line 2612 "parser.cpp"
    break;

  case 90: // stmt_return: "return" expr ";"
#line 516 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = make_stmt_return(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2618 "parser.cpp"
    break;

  case 91: // stmt_return: "return" ";"
#line 518 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = make_stmt_return(yylhs.location, make_node(yylhs.location)); }
#line 2624 "parser.cpp"
    break;

  case 92: // stmt_breakpoint: "breakpoint" ";"
#line 523 "parser.ypp"
        { yylhs.value.as < stmt_breakpoint::ptr > () = make_stmt_breakpoint(yylhs.location); }
#line 2630 "parser.cpp"
    break;

  case 93: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 528 "parser.ypp"
        { yylhs.value.as < stmt_prof_begin::ptr > () = make_stmt_prof_begin(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2636 "parser.cpp"
    break;

  case 94: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 533 "parser.ypp"
        { yylhs.value.as < stmt_prof_end::ptr > () = make_stmt_prof_end(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2642 "parser.cpp"
    break;

  case 95: // expr: expr_ternary
#line 537 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2648 "parser.cpp"
    break;

  case 96: // expr: expr_binary
#line 538 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2654 "parser.cpp"
    break;

  case 97: // expr: expr_primitive
#line 539 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2660 "parser.cpp"
    break;

  case 98: // expr_or_empty: expr
#line 543 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2666 "parser.cpp"
    break;

  case 99: // expr_or_empty: %empty
#line 544 "parser.ypp"
                     { yylhs.value.as < expr > ().as_node = make_node(yylhs.location); }
#line 2672 "parser.cpp"
    break;

  case 100: // expr_assign: expr_tuple "=" expr
#line 549 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2678 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "=" expr
#line 551 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2684 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object "|=" expr
#line 553 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_bitwise_or(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2690 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object "&=" expr
#line 555 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_bitwise_and(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2696 "parser.cpp"
    break;

  case 104: // expr_assign: expr_object "^=" expr
#line 557 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_bitwise_exor(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2702 "parser.cpp"
    break;

  case 105: // expr_assign: expr_object "<<=" expr
#line 559 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_shift_left(yylhs.location, std::move(yystack_[2].value.as < expr > ()),std::move( yystack_[0].value.as < expr > ())); }
#line 2708 "parser.cpp"
    break;

  case 106: // expr_assign: expr_object ">>=" expr
#line 561 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_shift_right(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2714 "parser.cpp"
    break;

  case 107: // expr_assign: expr_object "+=" expr
#line 563 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_add(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2720 "parser.cpp"
    break;

  case 108: // expr_assign: expr_object "-=" expr
#line 565 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_sub(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2726 "parser.cpp"
    break;

  case 109: // expr_assign: expr_object "*=" expr
#line 567 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_mul(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2732 "parser.cpp"
    break;

  case 110: // expr_assign: expr_object "/=" expr
#line 569 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_div(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2738 "parser.cpp"
    break;

  case 111: // expr_assign: expr_object "%=" expr
#line 571 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_mod(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2744 "parser.cpp"
    break;

  case 112: // expr_increment: "++" expr_object
#line 576 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_increment(yylhs.location, std::move(yystack_[0].value.as < expr > ()), true); }
#line 2750 "parser.cpp"
    break;

  case 113: // expr_increment: expr_object "++"
#line 578 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_increment(yylhs.location, std::move(yystack_[1].value.as < expr > ()), false); }
#line 2756 "parser.cpp"
    break;

  case 114: // expr_decrement: "--" expr_object
#line 583 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_decrement(yylhs.location, std::move(yystack_[0].value.as < expr > ()), true); }
#line 2762 "parser.cpp"
    break;

  case 115: // expr_decrement: expr_object "--"
#line 585 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_decrement(yylhs.location, std::move(yystack_[1].value.as < expr > ()), false); }
#line 2768 "parser.cpp"
    break;

  case 116: // expr_ternary: expr "?" expr ":" expr
#line 590 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_ternary(yylhs.location, std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2774 "parser.cpp"
    break;

  case 117: // expr_binary: expr "||" expr
#line 595 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_or(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2780 "parser.cpp"
    break;

  case 118: // expr_binary: expr "&&" expr
#line 597 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_and(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2786 "parser.cpp"
    break;

  case 119: // expr_binary: expr "==" expr
#line 599 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_equality(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2792 "parser.cpp"
    break;

  case 120: // expr_binary: expr "!=" expr
#line 601 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_inequality(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2798 "parser.cpp"
    break;

  case 121: // expr_binary: expr "<=" expr
#line 603 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_less_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2804 "parser.cpp"
    break;

  case 122: // expr_binary: expr ">=" expr
#line 605 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_greater_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2810 "parser.cpp"
    break;

  case 123: // expr_binary: expr "<" expr
#line 607 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_less(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2816 "parser.cpp"
    break;

  case 124: // expr_binary: expr ">" expr
#line 609 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_greater(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2822 "parser.cpp"
    break;

  case 125: // expr_binary: expr "|" expr
#line 611 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_bitwise_or(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2828 "parser.cpp"
    break;

  case 126: // expr_binary: expr "&" expr
#line 613 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_bitwise_and(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2834 "parser.cpp"
    break;

  case 127: // expr_binary: expr "^" expr
#line 615 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_bitwise_exor(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2840 "parser.cpp"
    break;

  case 128: // expr_binary: expr "<<" expr
#line 617 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_shift_left(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2846 "parser.cpp"
    break;

  case 129: // expr_binary: expr ">>" expr
#line 619 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_shift_right(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2852 "parser.cpp"
    break;

  case 130: // expr_binary: expr "+" expr
#line 621 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_add(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2858 "parser.cpp"
    break;

  case 131: // expr_binary: expr "-" expr
#line 623 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_sub(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2864 "parser.cpp"
    break;

  case 132: // expr_binary: expr "*" expr
#line 625 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_mul(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2870 "parser.cpp"
    break;

  case 133: // expr_binary: expr "/" expr
#line 627 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_div(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2876 "parser.cpp"
    break;

  case 134: // expr_binary: expr "%" expr
#line 629 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_mod(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2882 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_complement
#line 633 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_complement::ptr > ()); }
#line 2888 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_negate
#line 634 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_negate::ptr > ()); }
#line 2894 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_not
#line 635 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_not::ptr > ()); }
#line 2900 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_call
#line 636 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 2906 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_method
#line 637 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 2912 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_add_array
#line 638 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_add_array::ptr > ()); }
#line 2918 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_isdefined
#line 639 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_isdefined::ptr > ()); }
#line 2924 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_istrue
#line 640 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_istrue::ptr > ()); }
#line 2930 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_reference
#line 641 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_reference::ptr > ()); }
#line 2936 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_array
#line 642 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 2942 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_field
#line 643 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 2948 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_size
#line 644 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_size::ptr > ()); }
#line 2954 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_paren
#line 645 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_paren::ptr > ()); }
#line 2960 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_thisthread
#line 646 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_thisthread::ptr > ()); }
#line 2966 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_empty_array
#line 647 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_empty_array::ptr > ()); }
#line 2972 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_undefined
#line 648 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_undefined::ptr > ()); }
#line 2978 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_game
#line 649 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 2984 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_self
#line 650 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 2990 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_anim
#line 651 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 2996 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_level
#line 652 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3002 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_animation
#line 653 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_animation::ptr > ()); }
#line 3008 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_animtree
#line 654 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_animtree::ptr > ()); }
#line 3014 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_identifier
#line 655 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3020 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_istring
#line 656 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_istring::ptr > ()); }
#line 3026 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_string
#line 657 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_string::ptr > ()); }
#line 3032 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_vector
#line 658 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_vector::ptr > ()); }
#line 3038 "parser.cpp"
    break;

  case 161: // expr_primitive: expr_float
#line 659 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_float::ptr > ()); }
#line 3044 "parser.cpp"
    break;

  case 162: // expr_primitive: expr_integer
#line 660 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_integer::ptr > ()); }
#line 3050 "parser.cpp"
    break;

  case 163: // expr_primitive: expr_false
#line 661 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_false::ptr > ()); }
#line 3056 "parser.cpp"
    break;

  case 164: // expr_primitive: expr_true
#line 662 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_true::ptr > ()); }
#line 3062 "parser.cpp"
    break;

  case 165: // expr_complement: "~" expr
#line 667 "parser.ypp"
        { yylhs.value.as < expr_complement::ptr > () = make_expr_complement(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 3068 "parser.cpp"
    break;

  case 166: // expr_negate: "-" expr_identifier
#line 672 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_identifier::ptr > ()) }); }
#line 3074 "parser.cpp"
    break;

  case 167: // expr_negate: "-" expr_paren
#line 674 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_paren::ptr > ()) }); }
#line 3080 "parser.cpp"
    break;

  case 168: // expr_negate: "-" expr_array
#line 676 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_array::ptr > ()) }); }
#line 3086 "parser.cpp"
    break;

  case 169: // expr_negate: "-" expr_field
#line 678 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_field::ptr > ()) }); }
#line 3092 "parser.cpp"
    break;

  case 170: // expr_not: "!" expr
#line 683 "parser.ypp"
        { yylhs.value.as < expr_not::ptr > () = make_expr_not(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 3098 "parser.cpp"
    break;

  case 171: // expr_call: expr_function
#line 687 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = make_expr_call(yylhs.location, std::move(yystack_[0].value.as < call > ())); }
#line 3104 "parser.cpp"
    break;

  case 172: // expr_call: expr_pointer
#line 688 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = make_expr_call(yylhs.location, std::move(yystack_[0].value.as < call > ())); }
#line 3110 "parser.cpp"
    break;

  case 173: // expr_method: expr_object expr_function
#line 691 "parser.ypp"
                                   { yylhs.value.as < expr_method::ptr > () = make_expr_method(yylhs.location, std::move(yystack_[1].value.as < expr > ()), std::move(yystack_[0].value.as < call > ())); }
#line 3116 "parser.cpp"
    break;

  case 174: // expr_method: expr_object expr_pointer
#line 692 "parser.ypp"
                                   { yylhs.value.as < expr_method::ptr > () = make_expr_method(yylhs.location, std::move(yystack_[1].value.as < expr > ()), std::move(yystack_[0].value.as < call > ())); }
#line 3122 "parser.cpp"
    break;

  case 175: // expr_function: expr_identifier "(" expr_arguments ")"
#line 697 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3128 "parser.cpp"
    break;

  case 176: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 699 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3134 "parser.cpp"
    break;

  case 177: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 701 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3140 "parser.cpp"
    break;

  case 178: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 703 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3146 "parser.cpp"
    break;

  case 179: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 705 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3152 "parser.cpp"
    break;

  case 180: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 707 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3158 "parser.cpp"
    break;

  case 181: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 712 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3164 "parser.cpp"
    break;

  case 182: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 714 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3170 "parser.cpp"
    break;

  case 183: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 716 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3176 "parser.cpp"
    break;

  case 184: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 718 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::builtin); }
#line 3182 "parser.cpp"
    break;

  case 185: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 723 "parser.ypp"
        { yylhs.value.as < expr_add_array::ptr > () = make_expr_add_array(yylhs.location, std::move(yystack_[1].value.as < expr_arguments::ptr > ())); }
#line 3188 "parser.cpp"
    break;

  case 186: // expr_parameters: expr_parameters "," expr_identifier
#line 728 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3194 "parser.cpp"
    break;

  case 187: // expr_parameters: expr_identifier
#line 730 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = make_expr_parameters(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3200 "parser.cpp"
    break;

  case 188: // expr_parameters: %empty
#line 732 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = make_expr_parameters(yylhs.location); }
#line 3206 "parser.cpp"
    break;

  case 189: // expr_arguments: expr_arguments_no_empty
#line 737 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[0].value.as < expr_arguments::ptr > ()); }
#line 3212 "parser.cpp"
    break;

  case 190: // expr_arguments: %empty
#line 739 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = make_expr_arguments(yylhs.location); }
#line 3218 "parser.cpp"
    break;

  case 191: // expr_arguments_no_empty: expr_arguments "," expr
#line 744 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[2].value.as < expr_arguments::ptr > ()); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3224 "parser.cpp"
    break;

  case 192: // expr_arguments_no_empty: expr
#line 746 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = make_expr_arguments(yylhs.location); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3230 "parser.cpp"
    break;

  case 193: // expr_isdefined: "isdefined" "(" expr ")"
#line 751 "parser.ypp"
        { yylhs.value.as < expr_isdefined::ptr > () = make_expr_isdefined(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 3236 "parser.cpp"
    break;

  case 194: // expr_istrue: "istrue" "(" expr ")"
#line 756 "parser.ypp"
        { yylhs.value.as < expr_istrue::ptr > () = make_expr_istrue(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 3242 "parser.cpp"
    break;

  case 195: // expr_reference: "::" expr_identifier
#line 761 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = make_expr_reference(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3248 "parser.cpp"
    break;

  case 196: // expr_reference: expr_path "::" expr_identifier
#line 763 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = make_expr_reference(yylhs.location, std::move(yystack_[2].value.as < expr_path::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3254 "parser.cpp"
    break;

  case 197: // expr_tuple: "[" expr_tuple_arguments "]"
#line 768 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = std::move(yystack_[1].value.as < expr_tuple::ptr > ());
          yylhs.value.as < expr > ().as_tuple->temp = expr{ std::make_unique<expr_identifier>(yylhs.value.as < expr > ().loc(), fmt::format("_temp_{}", ++index)) };
        }
#line 3262 "parser.cpp"
    break;

  case 198: // expr_tuple_arguments: expr_tuple_arguments "," expr_tuple_types
#line 775 "parser.ypp"
        { yylhs.value.as < expr_tuple::ptr > () = std::move(yystack_[2].value.as < expr_tuple::ptr > ()); yylhs.value.as < expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3268 "parser.cpp"
    break;

  case 199: // expr_tuple_arguments: expr_tuple_types
#line 777 "parser.ypp"
        { yylhs.value.as < expr_tuple::ptr > () = make_expr_tuple(yylhs.location); yylhs.value.as < expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3274 "parser.cpp"
    break;

  case 200: // expr_tuple_types: expr_array
#line 781 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3280 "parser.cpp"
    break;

  case 201: // expr_tuple_types: expr_field
#line 782 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3286 "parser.cpp"
    break;

  case 202: // expr_tuple_types: expr_identifier
#line 783 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3292 "parser.cpp"
    break;

  case 203: // expr_array: expr_object "[" expr "]"
#line 788 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = make_expr_array(yylhs.location, std::move(yystack_[3].value.as < expr > ()), std::move(yystack_[1].value.as < expr > ())); }
#line 3298 "parser.cpp"
    break;

  case 204: // expr_field: expr_object "." expr_identifier_nosize
#line 793 "parser.ypp"
        { yylhs.value.as < expr_field::ptr > () = make_expr_field(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3304 "parser.cpp"
    break;

  case 205: // expr_size: expr_object "." "size"
#line 798 "parser.ypp"
        { yylhs.value.as < expr_size::ptr > () = make_expr_size(yylhs.location, std::move(yystack_[2].value.as < expr > ())); }
#line 3310 "parser.cpp"
    break;

  case 206: // expr_paren: "(" expr ")"
#line 803 "parser.ypp"
        { yylhs.value.as < expr_paren::ptr > () = make_expr_paren(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 3316 "parser.cpp"
    break;

  case 207: // expr_object: expr_call
#line 807 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3322 "parser.cpp"
    break;

  case 208: // expr_object: expr_method
#line 808 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3328 "parser.cpp"
    break;

  case 209: // expr_object: expr_array
#line 809 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3334 "parser.cpp"
    break;

  case 210: // expr_object: expr_field
#line 810 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3340 "parser.cpp"
    break;

  case 211: // expr_object: expr_game
#line 811 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3346 "parser.cpp"
    break;

  case 212: // expr_object: expr_self
#line 812 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3352 "parser.cpp"
    break;

  case 213: // expr_object: expr_anim
#line 813 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3358 "parser.cpp"
    break;

  case 214: // expr_object: expr_level
#line 814 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3364 "parser.cpp"
    break;

  case 215: // expr_object: expr_identifier
#line 815 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3370 "parser.cpp"
    break;

  case 216: // expr_thisthread: "thisthread"
#line 820 "parser.ypp"
        { yylhs.value.as < expr_thisthread::ptr > () = make_expr_thisthread(yylhs.location); }
#line 3376 "parser.cpp"
    break;

  case 217: // expr_empty_array: "[" "]"
#line 825 "parser.ypp"
        { yylhs.value.as < expr_empty_array::ptr > () = make_expr_empty_array(yylhs.location); }
#line 3382 "parser.cpp"
    break;

  case 218: // expr_undefined: "undefined"
#line 830 "parser.ypp"
        { yylhs.value.as < expr_undefined::ptr > () = make_expr_undefined(yylhs.location); }
#line 3388 "parser.cpp"
    break;

  case 219: // expr_game: "game"
#line 835 "parser.ypp"
        { yylhs.value.as < expr_game::ptr > () = make_expr_game(yylhs.location); }
#line 3394 "parser.cpp"
    break;

  case 220: // expr_self: "self"
#line 840 "parser.ypp"
        { yylhs.value.as < expr_self::ptr > () = make_expr_self(yylhs.location); }
#line 3400 "parser.cpp"
    break;

  case 221: // expr_anim: "anim"
#line 845 "parser.ypp"
        { yylhs.value.as < expr_anim::ptr > () = make_expr_anim(yylhs.location); }
#line 3406 "parser.cpp"
    break;

  case 222: // expr_level: "level"
#line 850 "parser.ypp"
        { yylhs.value.as < expr_level::ptr > () = make_expr_level(yylhs.location); }
#line 3412 "parser.cpp"
    break;

  case 223: // expr_animation: "%" "identifier"
#line 855 "parser.ypp"
        { yylhs.value.as < expr_animation::ptr > () = make_expr_animation(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3418 "parser.cpp"
    break;

  case 224: // expr_animtree: "#animtree"
#line 860 "parser.ypp"
        { yylhs.value.as < expr_animtree::ptr > () = make_expr_animtree(yylhs.location); }
#line 3424 "parser.cpp"
    break;

  case 225: // expr_identifier_nosize: "identifier"
#line 865 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = make_expr_identifier(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3430 "parser.cpp"
    break;

  case 226: // expr_identifier: "identifier"
#line 870 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = make_expr_identifier(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3436 "parser.cpp"
    break;

  case 227: // expr_identifier: "size"
#line 872 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = make_expr_identifier(yylhs.location, "size"); }
#line 3442 "parser.cpp"
    break;

  case 228: // expr_path: "path" "/" "identifier"
#line 877 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = make_expr_path(yylhs.location, yystack_[2].value.as < std::string > () + "/" + yystack_[0].value.as < std::string > ()); }
#line 3448 "parser.cpp"
    break;

  case 229: // expr_path: "identifier"
#line 879 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = make_expr_path(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3454 "parser.cpp"
    break;

  case 230: // expr_path: "path"
#line 881 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = make_expr_path(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3460 "parser.cpp"
    break;

  case 231: // expr_istring: "localized string"
#line 886 "parser.ypp"
        { yylhs.value.as < expr_istring::ptr > () = make_expr_istring(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3466 "parser.cpp"
    break;

  case 232: // expr_string: "string literal"
#line 891 "parser.ypp"
        { yylhs.value.as < expr_string::ptr > () = make_expr_string(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3472 "parser.cpp"
    break;

  case 233: // expr_vector: "(" expr "," expr "," expr ")"
#line 896 "parser.ypp"
        { yylhs.value.as < expr_vector::ptr > () = make_expr_vector(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[3].value.as < expr > ()), std::move(yystack_[1].value.as < expr > ())); }
#line 3478 "parser.cpp"
    break;

  case 234: // expr_float: "-" "float"
#line 901 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = make_expr_float(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3484 "parser.cpp"
    break;

  case 235: // expr_float: "float"
#line 903 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = make_expr_float(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3490 "parser.cpp"
    break;

  case 236: // expr_integer: "-" "integer"
#line 908 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = make_expr_integer(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3496 "parser.cpp"
    break;

  case 237: // expr_integer: "integer"
#line 910 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = make_expr_integer(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3502 "parser.cpp"
    break;

  case 238: // expr_false: "false"
#line 915 "parser.ypp"
        { yylhs.value.as < expr_false::ptr > () = make_expr_false(yylhs.location); }
#line 3508 "parser.cpp"
    break;

  case 239: // expr_true: "true"
#line 920 "parser.ypp"
        { yylhs.value.as < expr_true::ptr > () = make_expr_true(yylhs.location); }
#line 3514 "parser.cpp"
    break;


#line 3518 "parser.cpp"

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
  "prof_end", "thread", "childthread", "thisthread", "call", "true",
  "false", "undefined", "size", "game", "self", "anim", "level",
  "isdefined", "istrue", "(", ")", "{", "}", "[", "]", ",", ".", "::", ":",
  ";", "?", "++", "--", "<<", ">>", "||", "&&", "==", "!=", "<=", ">=",
  "<", ">", "!", "~", "=", "+=", "-=", "*=", "/=", "%=", "|=", "&=", "^=",
  ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/", "%", "path",
  "identifier", "string literal", "localized string", "float", "integer",
  "SIZEOF", "ADD_ARRAY", "THEN", "TERN", "NEG", "ANIMREF", "PREINC",
  "PREDEC", "POSTINC", "POSTDEC", "$accept", "root", "program", "inline",
  "include", "declaration", "decl_usingtree", "decl_function", "stmt",
  "stmt_or_dev", "stmt_list", "stmt_or_dev_list", "stmt_dev", "stmt_comp",
  "stmt_expr", "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify",
  "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_waitframe", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_dowhile", "stmt_for", "stmt_foreach", "stmt_switch",
  "stmt_case", "stmt_default", "stmt_break", "stmt_continue",
  "stmt_return", "stmt_breakpoint", "stmt_prof_begin", "stmt_prof_end",
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


  const short parser::yypact_ninf_ = -178;

  const short parser::yytable_ninf_ = -230;

  const short
  parser::yypact_[] =
  {
      15,  -178,  -178,   -64,   -64,   -45,  -178,  -178,    26,    15,
    -178,  -178,  -178,  -178,  -178,   -33,   -51,  -178,   -15,   -12,
     -32,  -178,  -178,  -178,  -178,   -30,   -39,  -178,  -178,  -178,
      16,   -13,  -178,  -178,    11,    52,   -30,  -178,   825,  -178,
    -178,   986,  1223,    37,   -40,    67,  1414,    71,    75,    83,
     101,     5,    60,   107,   110,  1093,   116,   123,   129,   -27,
      -8,    90,  -178,  -178,  -178,  -178,  -178,   368,  -178,   780,
     780,   133,  -178,  -178,   907,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,   139,   145,   151,   153,   157,  -178,  -178,   122,  -178,
    -178,  1335,  -178,  -178,  -178,  -178,   170,   164,  -178,  -178,
    -178,  1065,  -178,  -178,  -178,  -178,  -178,   173,   176,  1223,
    1158,   -30,  1223,  1223,   513,   134,  -178,  -178,  -178,  2200,
    -178,  -178,  -178,  -178,  -178,  -178,    -3,   305,  -178,  -178,
    -178,  -178,   432,   486,  -178,  -178,   553,  -178,  -178,  -178,
     698,   939,  1018,  1119,  -178,  -178,   182,   171,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,   180,  -178,  1223,   212,
    1223,   853,   -30,  1223,   142,   174,   185,  -178,  -178,  -178,
    -178,  2235,  -178,  1223,  1223,   187,   195,   188,   193,   200,
     202,   219,  1288,  -178,  -178,    25,  -178,    76,   105,  1183,
      45,   225,  1183,  1183,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  1223,   231,   234,   235,   236,  1288,   192,  -178,
    -178,  1223,  1223,  1223,  1223,  1223,  1223,  1223,  1223,  1223,
    1223,  1223,  -178,  -178,   170,  1223,   -30,  -178,  -178,  -178,
    1223,  1223,  1424,  1158,  -178,  2248,   238,   237,  -178,  -178,
    -178,  1223,  -178,  -178,   432,   486,  -178,   182,  -178,  -178,
    1223,  1223,  1223,  1223,  1223,  1223,  1223,  1223,  1223,  1223,
    1223,  1223,  1223,  1223,  1223,  1223,  1223,  1223,  1223,    -6,
     -30,   230,  1590,   241,  1624,   240,  -178,  -178,  -178,   625,
       4,  1658,  -178,  -178,  -178,    47,  -178,    84,  1223,  1223,
     -30,  1223,  1223,   -30,  1223,  1219,  -178,   780,  1223,  2248,
    1223,  1223,  1223,  1223,  1970,  -178,  -178,  2248,  2248,  2248,
    2248,  2248,  2248,  2248,  2248,  2248,  2248,  2248,    94,   245,
    1692,  1726,  -178,  1223,  1219,  1223,  -178,  1760,  2165,   172,
     172,  2279,  2289,   893,   893,    64,    64,    64,    64,  2320,
    2361,  2330,    14,    14,  -178,  -178,  -178,  -178,   245,  -178,
    1414,  1223,  1414,  1223,  1223,   -30,    52,   244,   246,  2010,
      96,   247,  2050,    97,   251,  2090,   253,  -178,  1794,  1468,
    1512,  1556,  -178,  -178,  1223,  -178,  -178,  2129,  2248,  1223,
     289,  1828,  -178,  2248,   252,  1862,   285,  -178,  -178,  -178,
     262,  -178,  1223,   263,  -178,  1223,   264,   272,   265,   267,
    1223,   268,  1223,   269,  1223,   112,  1223,  2248,  1414,   270,
     853,  1414,  1223,   274,   113,   281,   126,   283,  1223,  -178,
    -178,   287,  -178,   288,  -178,   292,  -178,  1896,  -178,  -178,
     295,  -178,  1930,  1223,  -178,  1223,  -178,  1223,   132,   280,
     291,   294,  -178,  1414,  1414,   138,   141,   144,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   227,   226,     0,     2,
       7,     8,     9,    14,    15,     0,   230,   229,     0,     0,
       0,     1,     4,     5,     6,   188,     0,    10,    11,   232,
       0,     0,   187,   228,     0,     0,     0,    16,     0,    17,
     186,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   219,   220,   221,   222,    56,     0,    52,     0,
       0,   226,    43,    50,     0,    44,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     0,     0,     0,   207,   208,   171,   172,     0,   209,
     210,     0,   211,   212,   213,   214,   215,     0,    54,    48,
      46,     0,   224,   216,   239,   238,   218,     0,     0,     0,
     190,     0,     0,     0,     0,     0,   231,   235,   237,     0,
      95,    96,    97,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,     0,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,     0,   158,   159,
     160,   161,   162,   163,   164,    74,     0,    75,     0,     0,
       0,    60,     0,     0,     0,     0,     0,    87,    88,    89,
      91,     0,    92,   190,   190,     0,     0,     0,     0,     0,
       0,     0,     0,   207,   208,     0,   199,   209,   210,     0,
     215,     0,   112,   114,    55,    51,    49,    63,    64,    65,
      61,    62,     0,     0,     0,     0,     0,     0,     0,   113,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,   174,     0,   190,     0,    53,    47,    45,
       0,     0,     0,   190,   217,   192,     0,   189,   195,   170,
     165,     0,   234,   236,   168,   169,   167,   166,   223,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,    59,     0,
       0,     0,    86,    85,    90,     0,   189,     0,     0,   190,
       0,     0,   190,     0,     0,     0,   197,     0,     0,   100,
       0,     0,     0,     0,     0,   225,   204,   101,   107,   108,
     109,   110,   111,   102,   103,   104,   106,   105,     0,     0,
       0,     0,   206,     0,   192,     0,   185,     0,     0,   128,
     129,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   130,   131,   132,   133,   134,   205,   196,    76,
       0,     0,     0,    99,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   198,     0,     0,
       0,     0,   203,   175,   190,   193,   194,     0,   191,     0,
      77,     0,    79,    98,     0,     0,     0,    84,    93,    94,
       0,   177,   190,     0,   179,   190,     0,     0,     0,     0,
     190,     0,   190,     0,   190,     0,     0,   116,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,   190,    66,
      68,   189,    71,   189,    73,   189,   176,     0,    78,    80,
       0,    82,     0,   190,   178,   190,   180,   190,     0,     0,
       0,     0,   233,     0,     0,     0,     0,     0,   181,    67,
      70,    72,    81,    83,   182,   183,   184
  };

  const short
  parser::yypgoto_[] =
  {
    -178,  -178,  -178,   337,   340,   343,  -178,  -178,   -38,   284,
    -178,  -178,  -178,   -34,   -76,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,   489,
    -178,  -177,  -176,  -175,  -178,  -178,  -178,  -178,  -178,  -178,
       6,    50,  -100,   -50,  -178,  -178,    41,  -118,  -178,  -178,
    -178,  -178,  -178,    38,    69,   131,  -178,   223,   137,  -178,
    -178,  -178,   199,   210,   226,   325,  -178,  -178,  -178,     0,
      12,  -178,    -2,  -178,  -178,   310,  -178,  -178
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    11,    12,    13,    14,    72,    73,
     121,    74,    75,    76,   295,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   255,
     404,   101,   102,   103,   140,   141,   142,   143,   144,   145,
     146,   147,   106,   107,   148,    31,   256,   306,   149,   150,
     151,   108,   205,   206,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   326,   166,
     167,   168,   169,   170,   171,   172,   173,   174
  };

  const short
  parser::yytable_[] =
  {
      15,    39,    20,   120,   296,   297,   298,   176,   179,    15,
       6,   242,   257,     6,    25,    18,    19,   177,    30,     1,
       2,     3,     4,     5,   195,    32,    21,   374,    16,    17,
    -207,  -207,     6,  -207,   367,    35,    40,  -207,   116,    26,
      36,   116,    27,   198,   104,    28,   116,   104,  -207,   185,
     117,  -207,   104,   117,    33,     6,   242,   375,   117,   196,
     199,   243,    29,     7,    34,    16,    71,   210,    37,   116,
     116,   197,   200,   203,   116,   203,   203,   316,   317,   117,
     104,   117,   117,   249,    16,    71,   117,   325,   105,  -207,
    -207,   105,   245,   184,   175,   377,   105,  -202,  -202,    29,
     345,    38,   138,   286,   287,   288,   243,   109,     7,   242,
     109,   244,   242,   242,   178,   109,   187,   204,   180,   204,
     204,   116,   181,   117,   105,   271,   272,   104,  -200,  -200,
     182,   258,   378,   117,   267,   257,   207,   345,   109,   109,
     203,   201,   393,   109,   411,   414,   117,   345,   183,   345,
     345,   284,   285,   286,   287,   288,   244,  -201,  -201,   243,
     446,   454,   243,   243,   188,   345,   345,   189,   117,   110,
     193,   105,   110,   192,   456,   111,   194,   110,   111,   345,
     468,   116,   300,   111,   204,   345,   474,   203,  -229,   475,
     109,   345,   476,   117,   345,   222,   217,   345,   208,   242,
     110,   110,   218,   264,   209,   110,   212,   213,   219,   244,
     220,   111,   244,   244,   221,  -215,  -215,   245,  -215,   246,
     250,   117,  -215,   251,   117,   117,   290,   268,   291,   245,
     302,   204,   293,  -215,   305,   307,  -215,   112,   308,   263,
     112,   303,   309,   310,   311,   112,   339,   312,   113,   243,
     109,   113,   110,   296,   297,   298,   113,   313,   111,   284,
     285,   286,   287,   288,   114,   265,   112,   114,   112,   112,
     314,   209,   114,   112,  -215,  -215,   318,   113,   320,   113,
     113,   321,   322,   323,   113,   325,   338,   369,   371,   346,
     368,   345,   394,   114,   412,   114,   114,   373,   415,   244,
     114,   408,   441,   409,   443,   417,   445,   428,   432,   430,
     381,   117,   110,   384,   433,   435,   437,   210,   299,   438,
     112,   453,   439,   203,   440,   442,   444,   449,   455,   117,
     457,   113,   400,   112,   402,   459,   460,   469,  -208,  -208,
     461,  -208,   407,   463,   113,  -208,    22,   114,   470,    23,
     380,   471,    24,   383,   450,   387,  -208,   266,   216,  -208,
     114,   186,     0,   115,     0,     0,   115,   204,     0,     0,
     116,   115,   116,     0,     0,   406,   104,     0,   104,     0,
     112,     0,   117,     0,   117,     0,   207,     0,     0,     0,
     448,   113,   115,   451,   115,   115,     0,  -208,  -208,   115,
       0,    59,    60,     0,    61,     0,     0,   114,     6,    62,
      63,    64,    65,     0,     0,     0,     0,     0,     0,   202,
     105,     0,   105,     0,     0,   472,   473,     0,   116,     0,
     116,   116,     0,     0,   104,   425,   203,   104,     0,   109,
     117,   109,   117,   117,     0,     0,   115,     0,   208,     0,
       0,     0,     0,   434,   209,     0,   436,     0,     0,   115,
      16,    71,     0,   116,   116,  -209,  -209,     0,  -209,   104,
     104,     0,  -209,     0,     0,   117,   117,     0,   105,   458,
     204,   105,     0,  -209,     0,     0,  -209,     0,     0,     0,
       0,     0,     0,     0,   465,     0,   466,   109,   467,   109,
     109,   110,     0,   110,     0,     0,   115,   111,     0,   111,
       0,     0,     0,   105,   105,     0,   112,     0,     0,  -210,
    -210,     0,  -210,     0,  -209,  -209,  -210,   113,     0,     0,
       0,   139,   109,   109,     0,     0,     0,  -210,     0,     0,
    -210,     0,     0,   114,   191,     0,    59,    60,     0,    61,
       0,     0,     0,     6,    62,    63,    64,    65,     0,   110,
     261,   110,   110,     0,   211,   111,     0,   299,   111,   112,
       0,   112,     0,     0,     0,     0,     0,     0,  -210,  -210,
     113,     0,   113,     0,     0,     0,    59,    60,     0,    61,
       0,     0,     0,     6,   110,   110,   114,     0,   114,     0,
     111,   111,     0,     0,   227,    16,    71,   289,     0,   262,
     263,     0,     0,     0,     0,     0,     0,     0,   252,     0,
       0,   259,   260,     0,     0,     0,     0,   112,     0,   112,
     112,     0,     0,     0,     0,     0,     0,     0,   113,     0,
     113,   113,   115,     0,     0,    16,    71,     0,     0,     0,
       0,     0,     0,     0,   114,     0,   114,   114,    59,    60,
       0,    61,   112,   112,     0,     6,     0,   292,     0,   294,
       0,     0,   301,   113,   113,     0,   227,     0,     0,   228,
       0,     0,     0,     0,   229,   230,     0,     0,     0,   114,
     114,   315,     0,     0,     0,   115,     0,   115,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,     0,
       0,   319,     0,     0,     0,     0,   324,    16,    71,     0,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,  -211,  -211,     0,  -211,     0,     0,     0,  -211,   340,
     341,     0,   344,     0,     0,     0,     0,     0,     0,  -211,
     347,     0,  -211,   115,     0,   115,   115,     0,     0,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   115,   115,
    -211,  -211,     0,     0,     0,     0,     0,   379,     0,     0,
     382,     0,     0,   385,     0,     0,     0,   315,     0,   388,
     389,   390,   391,    59,    60,     0,    61,     0,     0,     0,
       6,    62,    63,    64,    65,     0,     0,     0,     0,    41,
       0,   211,   397,     0,   398,     0,     0,    42,     0,     0,
      43,    44,    45,     0,    46,    47,    48,    49,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     401,    61,   403,   405,     0,     6,    62,    63,    64,    65,
       0,     0,    16,    71,    38,    66,    67,     0,     0,     0,
       0,     0,    68,     0,    69,    70,    59,    60,   427,    61,
       0,     0,     0,     6,    62,    63,    64,    65,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,     0,
       0,    41,    69,    70,     0,   447,     0,    16,    71,    42,
       0,   452,    43,    44,    45,     0,    46,    47,    48,    49,
       0,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     0,    61,     0,    16,    71,     6,    62,    63,
      64,    65,     0,     0,   271,   272,    38,   214,    67,     0,
     277,   278,   279,   280,   215,     0,    69,    70,     0,     0,
       0,     0,  -212,  -212,     0,  -212,     0,     0,     0,  -212,
     284,   285,   286,   287,   288,     0,     0,     0,     0,     0,
    -212,   118,     0,  -212,     0,     0,     0,     0,    42,    16,
      71,    43,    44,    45,     0,    46,    47,    48,    49,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,     0,    61,     0,     0,     0,     6,    62,    63,    64,
      65,  -212,  -212,     0,     0,    38,     0,    67,     0,     0,
       0,     0,     0,   119,     0,    69,    70,     0,     0,     0,
       0,  -213,  -213,     0,  -213,     0,     0,     0,  -213,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -213,
     247,     0,  -213,     0,     0,     0,     0,    42,    16,    71,
      43,    44,    45,     0,    46,    47,    48,    49,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
       0,    61,   122,     0,     0,     6,    62,    63,    64,    65,
    -213,  -213,     0,     0,    38,     0,    67,     0,     0,     0,
       0,     0,   248,     0,    69,    70,    59,    60,   123,    61,
     124,   125,   126,     6,    62,    63,    64,    65,   127,   128,
     129,     0,     0,     0,   130,     0,     0,     0,   131,     0,
     190,     0,  -214,  -214,     0,  -214,     0,    16,    71,  -214,
       0,     0,     0,     0,   132,   133,     0,   122,     0,     0,
    -214,     0,     0,  -214,     0,     0,     0,     0,     0,     0,
       0,   134,     0,     0,   135,    16,    71,    29,   136,   137,
     138,    59,    60,   123,    61,   124,   125,   126,     6,    62,
      63,    64,    65,   127,   128,   129,     0,     0,     0,   253,
     254,  -214,  -214,   131,     0,     0,    59,    60,     0,    61,
       0,     0,     0,     6,     0,     0,     0,     0,     0,   132,
     133,     0,   122,     0,   227,     0,     0,   228,     0,     0,
       0,     0,     0,     0,     0,     0,   134,     0,     0,   135,
      16,    71,    29,   136,   137,   138,    59,    60,   123,    61,
     124,   125,   126,     6,    62,    63,    64,    65,   127,   128,
     129,   386,     0,     0,   130,    16,    71,   270,   131,     0,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
       0,     0,     0,     0,   132,   133,     0,   122,     0,     0,
       0,     0,     0,   281,   282,   283,   284,   285,   286,   287,
     288,   134,     0,     0,   135,    16,    71,    29,   136,   137,
     138,    59,    60,   123,    61,   124,   125,   126,     6,    62,
      63,    64,    65,   127,   128,   129,     0,     0,     0,   253,
       0,     0,     0,   131,     0,   223,   224,     0,   225,   226,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   132,
     133,     0,     0,     0,     0,     0,     0,     0,    59,    60,
       0,    61,     0,     0,     0,     6,   134,     0,     0,   135,
      16,    71,    29,   136,   137,   138,   227,     0,     0,   228,
       0,     0,     0,     0,   229,   230,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,     0,
       0,     0,     0,     0,     0,     0,    42,    16,    71,    43,
      44,    45,     0,    46,    47,    48,    49,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     0,
      61,     0,     0,     0,     6,    62,    63,    64,    65,     0,
       0,     0,     0,    38,     0,    67,     0,     0,     0,     0,
       0,     0,   342,    69,    70,     0,     0,   343,     0,     0,
       0,     0,   270,     0,     0,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    71,   281,   282,
     283,   284,   285,   286,   287,   288,   419,     0,     0,     0,
       0,   420,     0,     0,     0,     0,   270,     0,     0,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   281,   282,   283,   284,   285,   286,   287,   288,
     421,     0,     0,     0,     0,   422,     0,     0,     0,     0,
     270,     0,     0,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   281,   282,   283,   284,
     285,   286,   287,   288,   423,     0,     0,     0,     0,   424,
       0,     0,     0,     0,   270,     0,     0,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   370,     0,
     281,   282,   283,   284,   285,   286,   287,   288,   270,     0,
       0,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   372,     0,   281,   282,   283,   284,   285,   286,
     287,   288,   270,     0,     0,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   376,     0,   281,   282,
     283,   284,   285,   286,   287,   288,   270,     0,     0,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     395,     0,   281,   282,   283,   284,   285,   286,   287,   288,
     270,     0,     0,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   396,     0,   281,   282,   283,   284,
     285,   286,   287,   288,   270,     0,     0,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   342,     0,
     281,   282,   283,   284,   285,   286,   287,   288,   270,     0,
       0,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   418,     0,   281,   282,   283,   284,   285,   286,
     287,   288,   270,     0,     0,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   429,     0,   281,   282,
     283,   284,   285,   286,   287,   288,   270,     0,     0,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     431,     0,   281,   282,   283,   284,   285,   286,   287,   288,
     270,     0,     0,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   462,     0,   281,   282,   283,   284,
     285,   286,   287,   288,   270,     0,     0,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   464,     0,
     281,   282,   283,   284,   285,   286,   287,   288,   270,     0,
       0,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   281,   282,   283,   284,   285,   286,
     287,   288,   392,     0,     0,     0,     0,     0,   270,     0,
       0,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   281,   282,   283,   284,   285,   286,
     287,   288,   410,     0,     0,     0,     0,     0,   270,     0,
       0,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   281,   282,   283,   284,   285,   286,
     287,   288,   413,     0,     0,     0,     0,     0,   270,     0,
       0,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   281,   282,   283,   284,   285,   286,
     287,   288,   416,     0,     0,     0,     0,     0,   270,     0,
       0,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   281,   282,   283,   284,   285,   286,
     287,   288,   426,     0,     0,     0,     0,   270,     0,     0,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   281,   282,   283,   284,   285,   286,   287,
     288,   399,     0,   270,     0,     0,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   281,
     282,   283,   284,   285,   286,   287,   288,   269,   270,     0,
       0,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   281,   282,   283,   284,   285,   286,
     287,   288,   304,   270,     0,     0,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   270,     0,     0,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,     0,     0,     0,
       0,     0,   281,   282,   283,   284,   285,   286,   287,   288,
     271,   272,     0,   274,   275,   276,   277,   278,   279,   280,
     271,   272,     0,     0,   275,   276,   277,   278,   279,   280,
       0,     0,     0,   281,   282,   283,   284,   285,   286,   287,
     288,     0,     0,   281,   282,   283,   284,   285,   286,   287,
     288,   271,   272,     0,     0,   275,   276,   277,   278,   279,
     280,   271,   272,     0,     0,   275,   276,   277,   278,   279,
     280,     0,     0,     0,     0,   282,   283,   284,   285,   286,
     287,   288,     0,     0,     0,   282,     0,   284,   285,   286,
     287,   288,   271,   272,     0,     0,   275,   276,   277,   278,
     279,   280,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   284,   285,
     286,   287,   288
  };

  const short
  parser::yycheck_[] =
  {
       0,    35,    47,    41,   181,   181,   181,    47,    46,     9,
      40,   111,   130,    40,    47,     3,     4,    57,    20,     4,
       5,     6,     7,     8,    51,    25,     0,    23,    92,    93,
      33,    34,    40,    36,    40,    48,    36,    40,    38,    90,
      53,    41,    57,    51,    38,    57,    46,    41,    51,    51,
      38,    54,    46,    41,    93,    40,   156,    53,    46,    59,
      60,   111,    94,    93,    48,    92,    93,    67,    57,    69,
      70,    59,    60,    67,    74,    69,    70,    52,    53,    67,
      74,    69,    70,   121,    92,    93,    74,    93,    38,    92,
      93,    41,    47,    88,    57,    48,    46,    52,    53,    94,
      53,    49,    97,    89,    90,    91,   156,    38,    93,   209,
      41,   111,   212,   213,    47,    46,    56,    67,    47,    69,
      70,   121,    47,   111,    74,    61,    62,   121,    52,    53,
      47,   131,    48,   121,   134,   253,    67,    53,    69,    70,
     134,    51,    48,    74,    48,    48,   134,    53,    47,    53,
      53,    87,    88,    89,    90,    91,   156,    52,    53,   209,
      48,    48,   212,   213,    57,    53,    53,    57,   156,    38,
      47,   121,    41,    57,    48,    38,    47,    46,    41,    53,
      48,   181,   182,    46,   134,    53,    48,   181,    55,    48,
     121,    53,    48,   181,    53,    73,    57,    53,    67,   299,
      69,    70,    57,   134,    67,    74,    69,    70,    57,   209,
      57,    74,   212,   213,    57,    33,    34,    47,    36,    55,
      47,   209,    40,    47,   212,   213,    55,    93,    48,    47,
      56,   181,    20,    51,   193,   194,    54,    38,    51,    97,
      41,    56,    47,    55,    51,    46,   246,    47,    38,   299,
     181,    41,   121,   430,   430,   430,    46,    55,   121,    87,
      88,    89,    90,    91,    38,   134,    67,    41,    69,    70,
      51,   134,    46,    74,    92,    93,    51,    67,    47,    69,
      70,    47,    47,    47,    74,    93,   245,    57,    47,    52,
     290,    53,    47,    67,    47,    69,    70,    57,    47,   299,
      74,    57,   420,    57,   422,    52,   424,    18,    23,    57,
     310,   299,   181,   313,    52,    52,    52,   317,   181,    47,
     121,    47,    57,   317,    57,    57,    57,    57,    47,   317,
      47,   121,   370,   134,   372,    48,    48,    57,    33,    34,
      48,    36,   376,    48,   134,    40,     9,   121,    57,     9,
     309,    57,     9,   312,   430,   317,    51,   134,    74,    54,
     134,    51,    -1,    38,    -1,    -1,    41,   317,    -1,    -1,
     370,    46,   372,    -1,    -1,   375,   370,    -1,   372,    -1,
     181,    -1,   370,    -1,   372,    -1,   317,    -1,    -1,    -1,
     428,   181,    67,   431,    69,    70,    -1,    92,    93,    74,
      -1,    33,    34,    -1,    36,    -1,    -1,   181,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    51,
     370,    -1,   372,    -1,    -1,   463,   464,    -1,   428,    -1,
     430,   431,    -1,    -1,   428,   394,   430,   431,    -1,   370,
     428,   372,   430,   431,    -1,    -1,   121,    -1,   317,    -1,
      -1,    -1,    -1,   412,   317,    -1,   415,    -1,    -1,   134,
      92,    93,    -1,   463,   464,    33,    34,    -1,    36,   463,
     464,    -1,    40,    -1,    -1,   463,   464,    -1,   428,   438,
     430,   431,    -1,    51,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   453,    -1,   455,   428,   457,   430,
     431,   370,    -1,   372,    -1,    -1,   181,   370,    -1,   372,
      -1,    -1,    -1,   463,   464,    -1,   317,    -1,    -1,    33,
      34,    -1,    36,    -1,    92,    93,    40,   317,    -1,    -1,
      -1,    42,   463,   464,    -1,    -1,    -1,    51,    -1,    -1,
      54,    -1,    -1,   317,    55,    -1,    33,    34,    -1,    36,
      -1,    -1,    -1,    40,    41,    42,    43,    44,    -1,   428,
      47,   430,   431,    -1,    51,   428,    -1,   430,   431,   370,
      -1,   372,    -1,    -1,    -1,    -1,    -1,    -1,    92,    93,
     370,    -1,   372,    -1,    -1,    -1,    33,    34,    -1,    36,
      -1,    -1,    -1,    40,   463,   464,   370,    -1,   372,    -1,
     463,   464,    -1,    -1,    51,    92,    93,    54,    -1,    96,
      97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,
      -1,   132,   133,    -1,    -1,    -1,    -1,   428,    -1,   430,
     431,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   428,    -1,
     430,   431,   317,    -1,    -1,    92,    93,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   428,    -1,   430,   431,    33,    34,
      -1,    36,   463,   464,    -1,    40,    -1,   178,    -1,   180,
      -1,    -1,   183,   463,   464,    -1,    51,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    -1,   463,
     464,   202,    -1,    -1,    -1,   370,    -1,   372,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,   222,    -1,    -1,    -1,    -1,   227,    92,    93,    -1,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,    33,    34,    -1,    36,    -1,    -1,    -1,    40,   250,
     251,    -1,   253,    -1,    -1,    -1,    -1,    -1,    -1,    51,
     261,    -1,    54,   428,    -1,   430,   431,    -1,    -1,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   463,   464,
      92,    93,    -1,    -1,    -1,    -1,    -1,   308,    -1,    -1,
     311,    -1,    -1,   314,    -1,    -1,    -1,   318,    -1,   320,
     321,   322,   323,    33,    34,    -1,    36,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,     4,
      -1,    51,   343,    -1,   345,    -1,    -1,    12,    -1,    -1,
      15,    16,    17,    -1,    19,    20,    21,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
     371,    36,   373,   374,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    92,    93,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    59,    60,    33,    34,   399,    36,
      -1,    -1,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,     4,    59,    60,    -1,   426,    -1,    92,    93,    12,
      -1,   432,    15,    16,    17,    -1,    19,    20,    21,    22,
      -1,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    -1,    92,    93,    40,    41,    42,
      43,    44,    -1,    -1,    61,    62,    49,    50,    51,    -1,
      67,    68,    69,    70,    57,    -1,    59,    60,    -1,    -1,
      -1,    -1,    33,    34,    -1,    36,    -1,    -1,    -1,    40,
      87,    88,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,
      51,     5,    -1,    54,    -1,    -1,    -1,    -1,    12,    92,
      93,    15,    16,    17,    -1,    19,    20,    21,    22,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    -1,    -1,    -1,    40,    41,    42,    43,
      44,    92,    93,    -1,    -1,    49,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    59,    60,    -1,    -1,    -1,
      -1,    33,    34,    -1,    36,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
       5,    -1,    54,    -1,    -1,    -1,    -1,    12,    92,    93,
      15,    16,    17,    -1,    19,    20,    21,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,     9,    -1,    -1,    40,    41,    42,    43,    44,
      92,    93,    -1,    -1,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    59,    60,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      57,    -1,    33,    34,    -1,    36,    -1,    92,    93,    40,
      -1,    -1,    -1,    -1,    71,    72,    -1,     9,    -1,    -1,
      51,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    -1,    91,    92,    93,    94,    95,    96,
      97,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    51,
      52,    92,    93,    55,    -1,    -1,    33,    34,    -1,    36,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    71,
      72,    -1,     9,    -1,    51,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    91,
      92,    93,    94,    95,    96,    97,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    52,    -1,    -1,    51,    92,    93,    58,    55,    -1,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    71,    72,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    88,    -1,    -1,    91,    92,    93,    94,    95,    96,
      97,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    10,    11,    -1,    13,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    36,    -1,    -1,    -1,    40,    88,    -1,    -1,    91,
      92,    93,    94,    95,    96,    97,    51,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    92,    93,    15,
      16,    17,    -1,    19,    20,    21,    22,    -1,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    -1,    -1,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    59,    60,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    92,    93,    84,    85,
      86,    87,    88,    89,    90,    91,    48,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      48,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    48,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    58,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    58,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    58,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      58,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    58,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    58,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    58,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    84,    85,
      86,    87,    88,    89,    90,    91,    58,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      58,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    58,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      84,    85,    86,    87,    88,    89,    90,    91,    58,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    56,    -1,    58,    -1,    -1,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    86,    87,    88,    89,    90,    91,    57,    58,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    57,    58,    -1,    -1,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    58,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    88,    89,    90,    91,
      61,    62,    -1,    64,    65,    66,    67,    68,    69,    70,
      61,    62,    -1,    -1,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    -1,    84,    85,    86,    87,    88,    89,    90,
      91,    61,    62,    -1,    -1,    65,    66,    67,    68,    69,
      70,    61,    62,    -1,    -1,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    85,    86,    87,    88,    89,
      90,    91,    -1,    -1,    -1,    85,    -1,    87,    88,    89,
      90,    91,    61,    62,    -1,    -1,    65,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,
      89,    90,    91
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     4,     5,     6,     7,     8,    40,    93,   109,   110,
     111,   112,   113,   114,   115,   187,    92,    93,   188,   188,
      47,     0,   111,   112,   113,    47,    90,    57,    57,    94,
     190,   163,   187,    93,    48,    48,    53,    57,    49,   121,
     187,     4,    12,    15,    16,    17,    19,    20,    21,    22,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    36,    41,    42,    43,    44,    50,    51,    57,    59,
      60,    93,   116,   117,   119,   120,   121,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   149,   150,   151,   158,   159,   160,   161,   169,   172,
     173,   176,   180,   181,   182,   183,   187,   188,     5,    57,
     116,   118,     9,    35,    37,    38,    39,    45,    46,    47,
      51,    55,    71,    72,    88,    91,    95,    96,    97,   147,
     152,   153,   154,   155,   156,   157,   158,   159,   162,   166,
     167,   168,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   187,   188,   189,   190,
     191,   192,   193,   194,   195,    57,    47,    57,    47,   116,
      47,    47,    47,    47,    88,   190,   193,    56,    57,    57,
      57,   147,    57,    47,    47,    51,   187,   188,    51,   187,
     188,    51,    51,   158,   159,   170,   171,   172,   173,   176,
     187,    51,   176,   176,    50,    57,   117,    57,    57,    57,
      57,    57,    73,    10,    11,    13,    14,    51,    54,    59,
      60,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,   160,   161,   187,    47,    55,     5,    57,   116,
      47,    47,   147,    51,    52,   147,   164,   165,   187,   147,
     147,    47,    96,    97,   172,   173,   175,   187,    93,    57,
      58,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    84,    85,    86,    87,    88,    89,    90,    91,    54,
      55,    48,   147,    20,   147,   122,   149,   150,   151,   176,
     187,   147,    56,    56,    57,   164,   165,   164,    51,    47,
      55,    51,    47,    55,    51,   147,    52,    53,    51,   147,
      47,    47,    47,    47,   147,    93,   186,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   164,   187,
     147,   147,    48,    53,   147,    53,    52,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,    40,   187,    57,
      48,    47,    48,    57,    23,    53,    48,    48,    48,   147,
     164,   187,   147,   164,   187,   147,    52,   171,   147,   147,
     147,   147,    52,    48,    47,    48,    48,   147,   147,    56,
     116,   147,   116,   147,   148,   147,   187,   121,    57,    57,
      52,    48,    47,    52,    48,    47,    52,    52,    48,    48,
      53,    48,    53,    48,    53,   164,    53,   147,    18,    48,
      57,    48,    23,    52,   164,    52,   164,    52,    47,    57,
      57,   165,    57,   165,    57,   165,    48,   147,   116,    57,
     122,   116,   147,    47,    48,    47,    48,    47,   164,    48,
      48,    48,    48,    48,    48,   164,   164,   164,    48,    57,
      57,    57,   116,   116,    48,    48,    48
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   108,   109,   109,   110,   110,   110,   110,   110,   110,
     111,   112,   113,   113,   113,   113,   114,   115,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   117,   117,   118,   118,   118,   118,   119,
     119,   119,   119,   120,   120,   121,   121,   122,   122,   122,
     122,   123,   123,   124,   124,   124,   125,   126,   126,   127,
     128,   128,   129,   129,   130,   131,   131,   132,   133,   134,
     135,   136,   137,   137,   138,   139,   139,   140,   141,   142,
     143,   143,   144,   145,   146,   147,   147,   147,   148,   148,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   150,   150,   151,   151,   152,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   155,   156,   156,   156,   156,
     157,   158,   158,   159,   159,   160,   160,   160,   160,   160,
     160,   161,   161,   161,   161,   162,   163,   163,   163,   164,
     164,   165,   165,   166,   167,   168,   168,   169,   170,   170,
     171,   171,   171,   172,   173,   174,   175,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   187,   188,   188,
     188,   189,   190,   191,   192,   192,   193,   193,   194,   195
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     5,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     2,
       1,     2,     1,     3,     2,     3,     2,     1,     1,     1,
       0,     2,     2,     2,     2,     2,     6,     8,     6,     3,
       8,     6,     8,     6,     2,     2,     4,     5,     7,     5,
       7,     9,     7,     9,     5,     3,     3,     2,     2,     2,
       3,     2,     2,     5,     5,     1,     1,     1,     1,     0,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     5,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     1,     1,     2,     2,     4,     6,     5,     7,     5,
       7,     8,     9,     9,     9,     3,     3,     1,     0,     1,
       0,     3,     1,     4,     4,     2,     3,     3,     3,     1,
       1,     1,     1,     4,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     7,     2,     1,     2,     1,     1,     1
  };




#if GSCDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   266,   266,   267,   271,   273,   275,   277,   279,   281,
     286,   290,   295,   296,   297,   298,   302,   307,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   340,   341,   345,   347,   349,   351,   356,
     358,   360,   362,   367,   368,   372,   373,   377,   379,   381,
     384,   388,   390,   395,   397,   399,   404,   409,   411,   416,
     421,   423,   428,   430,   435,   440,   442,   447,   452,   457,
     462,   467,   472,   477,   486,   493,   495,   500,   505,   510,
     515,   517,   522,   527,   532,   537,   538,   539,   543,   544,
     548,   550,   552,   554,   556,   558,   560,   562,   564,   566,
     568,   570,   575,   577,   582,   584,   589,   594,   596,   598,
     600,   602,   604,   606,   608,   610,   612,   614,   616,   618,
     620,   622,   624,   626,   628,   633,   634,   635,   636,   637,
     638,   639,   640,   641,   642,   643,   644,   645,   646,   647,
     648,   649,   650,   651,   652,   653,   654,   655,   656,   657,
     658,   659,   660,   661,   662,   666,   671,   673,   675,   677,
     682,   687,   688,   691,   692,   696,   698,   700,   702,   704,
     706,   711,   713,   715,   717,   722,   727,   729,   732,   736,
     739,   743,   745,   750,   755,   760,   762,   767,   774,   776,
     781,   782,   783,   787,   792,   797,   802,   807,   808,   809,
     810,   811,   812,   813,   814,   815,   819,   824,   829,   834,
     839,   844,   849,   854,   859,   864,   869,   871,   876,   878,
     880,   885,   890,   895,   900,   902,   907,   909,   914,   919
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
#line 4818 "parser.cpp"

#line 923 "parser.ypp"


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

extern std::unordered_map<token::type, parser::token::token_kind_type> const tok_to_parser;
extern std::unordered_map<std::string_view, parser::token::token_kind_type> const keyword_map;

auto map_token(context const* ctx_, token& tok) -> parser::symbol_type
{
    if (tok.kind == token::tok_identifier)
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
    else if (tok.kind == token::tok_path ||tok.kind == token::tok_string ||tok.kind == token::tok_istring || tok.kind == token::tok_integer ||tok.kind == token::tok_float)
    {
        auto it = tok_to_parser.find(tok.kind);

        if (it != tok_to_parser.end())
        {
            return parser::symbol_type(it->second, std::move(tok.data), tok.pos);
        }
    }
    else
    {
        auto it = tok_to_parser.find(tok.kind);

        if (it != tok_to_parser.end())
        {
            return parser::symbol_type(it->second, tok.pos);
        }
    }

    throw error(fmt::format("unmapped token! {}", (u8)tok.kind));
}

auto GSClex(context const* ctx_, preprocessor& ppr) -> parser::symbol_type
{
    auto tok = ppr.process();
    return map_token(ctx_, tok);
}

std::unordered_map<token::type, parser::token::token_kind_type> const tok_to_parser
{{
    { token::tok_identifier, parser::token::IDENTIFIER },
    { token::tok_path, parser::token::PATH },
    { token::tok_string, parser::token::STRING },
    { token::tok_istring, parser::token::ISTRING },
    { token::tok_integer, parser::token::INTEGER },
    { token::tok_float, parser::token::FLOAT },
    { token::tok_add, parser::token::ADD },
    { token::tok_sub, parser::token::SUB },
    { token::tok_mul, parser::token::MUL },
    { token::tok_div, parser::token::DIV },
    { token::tok_mod, parser::token::MOD },
    { token::tok_bwor, parser::token::BITWISE_OR },
    { token::tok_bwand, parser::token::BITWISE_AND },
    { token::tok_bwexor, parser::token::BITWISE_EXOR },
    { token::tok_assign, parser::token::ASSIGN },
    { token::tok_assign_add, parser::token::ASSIGN_ADD },
    { token::tok_assign_sub, parser::token::ASSIGN_SUB },
    { token::tok_assign_mul, parser::token::ASSIGN_MUL },
    { token::tok_assign_div, parser::token::ASSIGN_DIV },
    { token::tok_assign_mod, parser::token::ASSIGN_MOD },
    { token::tok_assign_bwor, parser::token::ASSIGN_BW_OR },
    { token::tok_assign_bwand, parser::token::ASSIGN_BW_AND },
    { token::tok_assign_bwexor, parser::token::ASSIGN_BW_EXOR },
    { token::tok_assign_lshift, parser::token::ASSIGN_LSHIFT },
    { token::tok_assign_rshift, parser::token::ASSIGN_RSHIFT },
    { token::tok_complement, parser::token::COMPLEMENT },
    { token::tok_not, parser::token::NOT },
    { token::tok_greater, parser::token::GREATER },
    { token::tok_less, parser::token::LESS },
    { token::tok_greater_equal, parser::token::GREATER_EQUAL },
    { token::tok_less_equal, parser::token::LESS_EQUAL },
    { token::tok_inequality, parser::token::INEQUALITY },
    { token::tok_equality, parser::token::EQUALITY },
    { token::tok_or, parser::token::OR },
    { token::tok_and, parser::token::AND },
    { token::tok_lshift, parser::token::LSHIFT },
    { token::tok_rshift, parser::token::RSHIFT },
    { token::tok_increment, parser::token::INCREMENT },
    { token::tok_decrement, parser::token::DECREMENT },
    { token::tok_qmark, parser::token::QMARK },
    { token::tok_dot, parser::token::DOT },
    { token::tok_comma, parser::token::COMMA },
    { token::tok_colon, parser::token::COLON },
    { token::tok_semicolon, parser::token::SEMICOLON },
    { token::tok_doublecolon, parser::token::DOUBLECOLON },
    { token::tok_lbracket, parser::token::LBRACKET },
    { token::tok_rbracket, parser::token::RBRACKET },
    { token::tok_lbrace, parser::token::LBRACE },
    { token::tok_rbrace, parser::token::RBRACE },
    { token::tok_lparen, parser::token::LPAREN },
    { token::tok_rparen, parser::token::RPAREN },
    { token::tok_devbegin, parser::token::DEVBEGIN },
    { token::tok_devend, parser::token::DEVEND },
    { token::tok_inline, parser::token::INLINE },
    { token::tok_include, parser::token::INCLUDE },
    { token::tok_usingtree, parser::token::USINGTREE },
    { token::tok_animtree, parser::token::ANIMTREE },
    { token::tok_endon, parser::token::ENDON },
    { token::tok_notify, parser::token::NOTIFY },
    { token::tok_wait, parser::token::WAIT },
    { token::tok_waittill, parser::token::WAITTILL },
    { token::tok_waittillmatch, parser::token::WAITTILLMATCH },
    { token::tok_waittillframeend, parser::token::WAITTILLFRAMEEND },
    { token::tok_waitframe, parser::token::WAITFRAME },
    { token::tok_if, parser::token::IF },
    { token::tok_else, parser::token::ELSE },
    { token::tok_do, parser::token::DO },
    { token::tok_while, parser::token::WHILE },
    { token::tok_for, parser::token::FOR },
    { token::tok_foreach, parser::token::FOREACH },
    { token::tok_in, parser::token::IN },
    { token::tok_switch, parser::token::SWITCH },
    { token::tok_case, parser::token::CASE },
    { token::tok_default, parser::token::DEFAULT },
    { token::tok_break, parser::token::BREAK },
    { token::tok_continue, parser::token::CONTINUE },
    { token::tok_return, parser::token::RETURN },
    { token::tok_breakpoint, parser::token::BREAKPOINT },
    { token::tok_prof_begin, parser::token::PROFBEGIN },
    { token::tok_prof_end, parser::token::PROFEND },
    { token::tok_thread, parser::token::THREAD },
    { token::tok_childthread, parser::token::CHILDTHREAD },
    { token::tok_thisthread, parser::token::THISTHREAD },
    { token::tok_call, parser::token::CALL },
    { token::tok_true, parser::token::TRUE },
    { token::tok_false, parser::token::FALSE },
    { token::tok_undefined, parser::token::UNDEFINED },
    { token::tok_size, parser::token::SIZE },
    { token::tok_game, parser::token::GAME },
    { token::tok_self, parser::token::SELF },
    { token::tok_anim, parser::token::ANIM },
    { token::tok_level, parser::token::LEVEL },
    { token::tok_isdefined, parser::token::ISDEFINED },
    { token::tok_istrue, parser::token::ISTRUE },
    { token::tok_eof, parser::token::GSCEOF },
    { token::tok_cleanhash, parser::token::HASH }
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
