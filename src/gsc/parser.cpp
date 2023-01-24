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
#line 40 "parser.ypp"

#include "stdinc.hpp"
#include "parser.hpp"
#include "lexer.hpp"
using namespace xsk::gsc;
namespace xsk::gsc
{ 
    auto GSClex(lexer& lexer) -> parser::symbol_type;
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
  parser::parser (xsk::gsc::context const* ctx__yyarg, xsk::gsc::lexer& lexer_yyarg, xsk::gsc::program::ptr& ast_yyarg, std::uint32_t index_yyarg)
#if GSCDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      ctx_ (ctx__yyarg),
      lexer (lexer_yyarg),
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
#line 272 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program::ptr > ()); }
#line 2081 "parser.cpp"
    break;

  case 3: // root: %empty
#line 273 "parser.ypp"
              { ast = make_program(yylhs.location); }
#line 2087 "parser.cpp"
    break;

  case 4: // program: program inline
#line 278 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); }
#line 2093 "parser.cpp"
    break;

  case 5: // program: program include
#line 280 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2099 "parser.cpp"
    break;

  case 6: // program: program declaration
#line 282 "parser.ypp"
        { yylhs.value.as < program::ptr > () = std::move(yystack_[1].value.as < program::ptr > ()); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl > ())); }
#line 2105 "parser.cpp"
    break;

  case 7: // program: inline
#line 284 "parser.ypp"
        { yylhs.value.as < program::ptr > () = make_program(yylhs.location); }
#line 2111 "parser.cpp"
    break;

  case 8: // program: include
#line 286 "parser.ypp"
        { yylhs.value.as < program::ptr > () = make_program(yylhs.location); yylhs.value.as < program::ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include::ptr > ())); }
#line 2117 "parser.cpp"
    break;

  case 9: // program: declaration
#line 288 "parser.ypp"
        { yylhs.value.as < program::ptr > () = make_program(yylhs.location); yylhs.value.as < program::ptr > ()->declarations.push_back(std::move(yystack_[0].value.as < decl > ())); }
#line 2123 "parser.cpp"
    break;

  case 10: // inline: "#inline" expr_path ";"
#line 292 "parser.ypp"
                                 { lexer.push_header(yystack_[1].value.as < expr_path::ptr > ()->value); }
#line 2129 "parser.cpp"
    break;

  case 11: // include: "#include" expr_path ";"
#line 297 "parser.ypp"
        { yylhs.value.as < include::ptr > () = make_include(yylhs.location, std::move(yystack_[1].value.as < expr_path::ptr > ())); }
#line 2135 "parser.cpp"
    break;

  case 12: // declaration: "/#"
#line 301 "parser.ypp"
                        { yylhs.value.as < decl > ().as_dev_begin = make_decl_dev_begin(yylhs.location); }
#line 2141 "parser.cpp"
    break;

  case 13: // declaration: "#/"
#line 302 "parser.ypp"
                        { yylhs.value.as < decl > ().as_dev_end = make_decl_dev_end(yylhs.location); }
#line 2147 "parser.cpp"
    break;

  case 14: // declaration: decl_usingtree
#line 303 "parser.ypp"
                        { yylhs.value.as < decl > ().as_usingtree = std::move(yystack_[0].value.as < decl_usingtree::ptr > ()); }
#line 2153 "parser.cpp"
    break;

  case 15: // declaration: decl_function
#line 304 "parser.ypp"
                        { yylhs.value.as < decl > ().as_function = std::move(yystack_[0].value.as < decl_function::ptr > ()); }
#line 2159 "parser.cpp"
    break;

  case 16: // decl_usingtree: "#using_animtree" "(" expr_string ")" ";"
#line 309 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < decl_usingtree::ptr > () = make_decl_usingtree(yylhs.location, std::move(yystack_[2].value.as < expr_string::ptr > ())); }
#line 2165 "parser.cpp"
    break;

  case 17: // decl_function: expr_identifier "(" expr_parameters ")" stmt_comp
#line 314 "parser.ypp"
        { lexer.ban_header(yylhs.location); yylhs.value.as < decl_function::ptr > () = make_decl_function(yylhs.location, std::move(yystack_[4].value.as < expr_identifier::ptr > ()), std::move(yystack_[2].value.as < expr_parameters::ptr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); }
#line 2171 "parser.cpp"
    break;

  case 18: // stmt: stmt_comp
#line 318 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_comp = std::move(yystack_[0].value.as < stmt_comp::ptr > ()); }
#line 2177 "parser.cpp"
    break;

  case 19: // stmt: stmt_call
#line 319 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_call = std::move(yystack_[0].value.as < stmt_call::ptr > ()); }
#line 2183 "parser.cpp"
    break;

  case 20: // stmt: stmt_assign
#line 320 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_assign = std::move(yystack_[0].value.as < stmt_assign::ptr > ()); }
#line 2189 "parser.cpp"
    break;

  case 21: // stmt: stmt_endon
#line 321 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_endon = std::move(yystack_[0].value.as < stmt_endon::ptr > ()); }
#line 2195 "parser.cpp"
    break;

  case 22: // stmt: stmt_notify
#line 322 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_notify = std::move(yystack_[0].value.as < stmt_notify::ptr > ()); }
#line 2201 "parser.cpp"
    break;

  case 23: // stmt: stmt_wait
#line 323 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_wait = std::move(yystack_[0].value.as < stmt_wait::ptr > ()); }
#line 2207 "parser.cpp"
    break;

  case 24: // stmt: stmt_waittill
#line 324 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waittill = std::move(yystack_[0].value.as < stmt_waittill::ptr > ()); }
#line 2213 "parser.cpp"
    break;

  case 25: // stmt: stmt_waittillmatch
#line 325 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waittillmatch = std::move(yystack_[0].value.as < stmt_waittillmatch::ptr > ()); }
#line 2219 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittillframeend
#line 326 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waittillframeend = std::move(yystack_[0].value.as < stmt_waittillframeend::ptr > ()); }
#line 2225 "parser.cpp"
    break;

  case 27: // stmt: stmt_waitframe
#line 327 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_waitframe = std::move(yystack_[0].value.as < stmt_waitframe::ptr > ()); }
#line 2231 "parser.cpp"
    break;

  case 28: // stmt: stmt_if
#line 328 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_if = std::move(yystack_[0].value.as < stmt_if::ptr > ()); }
#line 2237 "parser.cpp"
    break;

  case 29: // stmt: stmt_ifelse
#line 329 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_ifelse = std::move(yystack_[0].value.as < stmt_ifelse::ptr > ()); }
#line 2243 "parser.cpp"
    break;

  case 30: // stmt: stmt_while
#line 330 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_while = std::move(yystack_[0].value.as < stmt_while::ptr > ()); }
#line 2249 "parser.cpp"
    break;

  case 31: // stmt: stmt_dowhile
#line 331 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_dowhile = std::move(yystack_[0].value.as < stmt_dowhile::ptr > ()); }
#line 2255 "parser.cpp"
    break;

  case 32: // stmt: stmt_for
#line 332 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_for = std::move(yystack_[0].value.as < stmt_for::ptr > ()); }
#line 2261 "parser.cpp"
    break;

  case 33: // stmt: stmt_foreach
#line 333 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_foreach = std::move(yystack_[0].value.as < stmt_foreach::ptr > ()); }
#line 2267 "parser.cpp"
    break;

  case 34: // stmt: stmt_switch
#line 334 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_switch = std::move(yystack_[0].value.as < stmt_switch::ptr > ()); }
#line 2273 "parser.cpp"
    break;

  case 35: // stmt: stmt_case
#line 335 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_case = std::move(yystack_[0].value.as < stmt_case::ptr > ()); }
#line 2279 "parser.cpp"
    break;

  case 36: // stmt: stmt_default
#line 336 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_default = std::move(yystack_[0].value.as < stmt_default::ptr > ()); }
#line 2285 "parser.cpp"
    break;

  case 37: // stmt: stmt_break
#line 337 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_break = std::move(yystack_[0].value.as < stmt_break::ptr > ()); }
#line 2291 "parser.cpp"
    break;

  case 38: // stmt: stmt_continue
#line 338 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_continue = std::move(yystack_[0].value.as < stmt_continue::ptr > ()); }
#line 2297 "parser.cpp"
    break;

  case 39: // stmt: stmt_return
#line 339 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_return = std::move(yystack_[0].value.as < stmt_return::ptr > ()); }
#line 2303 "parser.cpp"
    break;

  case 40: // stmt: stmt_breakpoint
#line 340 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_breakpoint = std::move(yystack_[0].value.as < stmt_breakpoint::ptr > ()); }
#line 2309 "parser.cpp"
    break;

  case 41: // stmt: stmt_prof_begin
#line 341 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_prof_begin = std::move(yystack_[0].value.as < stmt_prof_begin::ptr > ()); }
#line 2315 "parser.cpp"
    break;

  case 42: // stmt: stmt_prof_end
#line 342 "parser.ypp"
                             { yylhs.value.as < stmt > ().as_prof_end = std::move(yystack_[0].value.as < stmt_prof_end::ptr > ()); }
#line 2321 "parser.cpp"
    break;

  case 43: // stmt_or_dev: stmt
#line 346 "parser.ypp"
               { yylhs.value.as < stmt > () = std::move(yystack_[0].value.as < stmt > ()); }
#line 2327 "parser.cpp"
    break;

  case 44: // stmt_or_dev: stmt_dev
#line 347 "parser.ypp"
               { yylhs.value.as < stmt > ().as_dev = std::move(yystack_[0].value.as < stmt_dev::ptr > ()); }
#line 2333 "parser.cpp"
    break;

  case 45: // stmt_list: stmt_list stmt
#line 352 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2339 "parser.cpp"
    break;

  case 46: // stmt_list: stmt
#line 354 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2345 "parser.cpp"
    break;

  case 47: // stmt_or_dev_list: stmt_or_dev_list stmt_or_dev
#line 359 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = std::move(yystack_[1].value.as < stmt_list::ptr > ()); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2351 "parser.cpp"
    break;

  case 48: // stmt_or_dev_list: stmt_or_dev
#line 361 "parser.ypp"
        { yylhs.value.as < stmt_list::ptr > () = make_stmt_list(yylhs.location); yylhs.value.as < stmt_list::ptr > ()->list.push_back(std::move(yystack_[0].value.as < stmt > ())); }
#line 2357 "parser.cpp"
    break;

  case 49: // stmt_dev: "/#" stmt_list "#/"
#line 365 "parser.ypp"
                                { yylhs.value.as < stmt_dev::ptr > () = make_stmt_dev(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2363 "parser.cpp"
    break;

  case 50: // stmt_dev: "/#" "#/"
#line 366 "parser.ypp"
                      { yylhs.value.as < stmt_dev::ptr > () = make_stmt_dev(yylhs.location, make_stmt_list(yylhs.location)); }
#line 2369 "parser.cpp"
    break;

  case 51: // stmt_comp: "{" stmt_or_dev_list "}"
#line 370 "parser.ypp"
                                     { yylhs.value.as < stmt_comp::ptr > () = make_stmt_comp(yylhs.location, std::move(yystack_[1].value.as < stmt_list::ptr > ())); }
#line 2375 "parser.cpp"
    break;

  case 52: // stmt_comp: "{" "}"
#line 371 "parser.ypp"
                    { yylhs.value.as < stmt_comp::ptr > () = make_stmt_comp(yylhs.location, make_stmt_list(yylhs.location)); }
#line 2381 "parser.cpp"
    break;

  case 53: // stmt_expr: expr_assign
#line 376 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 2387 "parser.cpp"
    break;

  case 54: // stmt_expr: expr_increment
#line 378 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 2393 "parser.cpp"
    break;

  case 55: // stmt_expr: expr_decrement
#line 380 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 2399 "parser.cpp"
    break;

  case 56: // stmt_expr: %empty
#line 382 "parser.ypp"
        { yylhs.value.as < stmt_expr::ptr > () = make_stmt_expr(yylhs.location, make_node(yylhs.location)); }
#line 2405 "parser.cpp"
    break;

  case 57: // stmt_call: expr_call ";"
#line 387 "parser.ypp"
        { yylhs.value.as < stmt_call::ptr > () = make_stmt_call(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_call::ptr > ()) }); }
#line 2411 "parser.cpp"
    break;

  case 58: // stmt_call: expr_method ";"
#line 389 "parser.ypp"
        { yylhs.value.as < stmt_call::ptr > () = make_stmt_call(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_method::ptr > ()) }); }
#line 2417 "parser.cpp"
    break;

  case 59: // stmt_assign: expr_assign ";"
#line 394 "parser.ypp"
        { yylhs.value.as < stmt_assign::ptr > () = make_stmt_assign(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2423 "parser.cpp"
    break;

  case 60: // stmt_assign: expr_increment ";"
#line 396 "parser.ypp"
        { yylhs.value.as < stmt_assign::ptr > () = make_stmt_assign(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2429 "parser.cpp"
    break;

  case 61: // stmt_assign: expr_decrement ";"
#line 398 "parser.ypp"
        { yylhs.value.as < stmt_assign::ptr > () = make_stmt_assign(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2435 "parser.cpp"
    break;

  case 62: // stmt_endon: expr_object "endon" "(" expr ")" ";"
#line 403 "parser.ypp"
        { yylhs.value.as < stmt_endon::ptr > () = make_stmt_endon(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ())); }
#line 2441 "parser.cpp"
    break;

  case 63: // stmt_notify: expr_object "notify" "(" expr "," expr_arguments_no_empty ")" ";"
#line 408 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = make_stmt_notify(yylhs.location, std::move(yystack_[7].value.as < expr > ()), std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2447 "parser.cpp"
    break;

  case 64: // stmt_notify: expr_object "notify" "(" expr ")" ";"
#line 410 "parser.ypp"
        { yylhs.value.as < stmt_notify::ptr > () = make_stmt_notify(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), make_expr_arguments(yylhs.location)); }
#line 2453 "parser.cpp"
    break;

  case 65: // stmt_wait: "wait" expr ";"
#line 415 "parser.ypp"
        { yylhs.value.as < stmt_wait::ptr > () = make_stmt_wait(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2459 "parser.cpp"
    break;

  case 66: // stmt_waittill: expr_object "waittill" "(" expr "," expr_arguments_no_empty ")" ";"
#line 420 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = make_stmt_waittill(yylhs.location, std::move(yystack_[7].value.as < expr > ()), std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2465 "parser.cpp"
    break;

  case 67: // stmt_waittill: expr_object "waittill" "(" expr ")" ";"
#line 422 "parser.ypp"
        { yylhs.value.as < stmt_waittill::ptr > () = make_stmt_waittill(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), make_expr_arguments(yylhs.location)); }
#line 2471 "parser.cpp"
    break;

  case 68: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr "," expr_arguments_no_empty ")" ";"
#line 427 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = make_stmt_waittillmatch(yylhs.location, std::move(yystack_[7].value.as < expr > ()), std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2477 "parser.cpp"
    break;

  case 69: // stmt_waittillmatch: expr_object "waittillmatch" "(" expr ")" ";"
#line 429 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch::ptr > () = make_stmt_waittillmatch(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), make_expr_arguments(yylhs.location)); }
#line 2483 "parser.cpp"
    break;

  case 70: // stmt_waittillframeend: "waittillframeend" ";"
#line 434 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend::ptr > () = make_stmt_waittillframeend(yylhs.location); }
#line 2489 "parser.cpp"
    break;

  case 71: // stmt_waitframe: "waitframe" ";"
#line 439 "parser.ypp"
        { yylhs.value.as < stmt_waitframe::ptr > () = make_stmt_waitframe(yylhs.location); }
#line 2495 "parser.cpp"
    break;

  case 72: // stmt_waitframe: "waitframe" "(" ")" ";"
#line 441 "parser.ypp"
        { yylhs.value.as < stmt_waitframe::ptr > () = make_stmt_waitframe(yylhs.location); }
#line 2501 "parser.cpp"
    break;

  case 73: // stmt_if: "if" "(" expr ")" stmt
#line 446 "parser.ypp"
        { yylhs.value.as < stmt_if::ptr > () = make_stmt_if(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < stmt > ())); }
#line 2507 "parser.cpp"
    break;

  case 74: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 451 "parser.ypp"
        { yylhs.value.as < stmt_ifelse::ptr > () = make_stmt_ifelse(yylhs.location, std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < stmt > ()), std::move(yystack_[0].value.as < stmt > ())); }
#line 2513 "parser.cpp"
    break;

  case 75: // stmt_while: "while" "(" expr ")" stmt
#line 456 "parser.ypp"
        { yylhs.value.as < stmt_while::ptr > () = make_stmt_while(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < stmt > ())); }
#line 2519 "parser.cpp"
    break;

  case 76: // stmt_dowhile: "do" stmt "while" "(" expr ")" ";"
#line 461 "parser.ypp"
        { yylhs.value.as < stmt_dowhile::ptr > () = make_stmt_dowhile(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[5].value.as < stmt > ())); }
#line 2525 "parser.cpp"
    break;

  case 77: // stmt_for: "for" "(" stmt_expr ";" expr_or_empty ";" stmt_expr ")" stmt
#line 466 "parser.ypp"
        { yylhs.value.as < stmt_for::ptr > () = make_stmt_for(yylhs.location, stmt{ std::move(yystack_[6].value.as < stmt_expr::ptr > ()) }, std::move(yystack_[4].value.as < expr > ()), stmt{ std::move(yystack_[2].value.as < stmt_expr::ptr > ()) }, std::move(yystack_[0].value.as < stmt > ())); }
#line 2531 "parser.cpp"
    break;

  case 78: // stmt_foreach: "foreach" "(" expr_identifier "in" expr ")" stmt
#line 471 "parser.ypp"
        {
            auto array = expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) };
            auto key = expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) };
            yylhs.value.as < stmt_foreach::ptr > () = make_stmt_foreach(yylhs.location, std::move(yystack_[2].value.as < expr > ()), expr{ std::move(yystack_[4].value.as < expr_identifier::ptr > ()) }, expr{ make_node(yylhs.location) }, std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt > ()), false); }
#line 2540 "parser.cpp"
    break;

  case 79: // stmt_foreach: "foreach" "(" expr_identifier "," expr_identifier "in" expr ")" stmt
#line 476 "parser.ypp"
        {
            auto array = expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) };
            auto key = (ctx_->props() & props::foreach) ? expr{ make_expr_identifier(yylhs.location, fmt::format("_temp_{}", ++index)) } : expr{ std::move(yystack_[6].value.as < expr_identifier::ptr > ()) };
            yylhs.value.as < stmt_foreach::ptr > () = make_stmt_foreach(yylhs.location, std::move(yystack_[2].value.as < expr > ()), expr{ std::move(yystack_[4].value.as < expr_identifier::ptr > ()) }, (ctx_->props() & props::foreach) ? expr{ std::move(yystack_[6].value.as < expr_identifier::ptr > ()) } : expr{ make_node(yylhs.location) }, std::move(array), std::move(key), std::move(yystack_[0].value.as < stmt > ()), true);
        }
#line 2550 "parser.cpp"
    break;

  case 80: // stmt_switch: "switch" "(" expr ")" stmt_comp
#line 485 "parser.ypp"
        { yylhs.value.as < stmt_switch::ptr > () = make_stmt_switch(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < stmt_comp::ptr > ())); 
          parse_switch(*yylhs.value.as < stmt_switch::ptr > ());
        }
#line 2558 "parser.cpp"
    break;

  case 81: // stmt_case: "case" expr_integer ":"
#line 492 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = make_stmt_case(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_integer::ptr > ()) }, make_stmt_list(yylhs.location)); }
#line 2564 "parser.cpp"
    break;

  case 82: // stmt_case: "case" expr_string ":"
#line 494 "parser.ypp"
        { yylhs.value.as < stmt_case::ptr > () = make_stmt_case(yylhs.location, expr{ std::move(yystack_[1].value.as < expr_string::ptr > ()) }, make_stmt_list(yylhs.location)); }
#line 2570 "parser.cpp"
    break;

  case 83: // stmt_default: "default" ":"
#line 499 "parser.ypp"
        { yylhs.value.as < stmt_default::ptr > () = make_stmt_default(yylhs.location, make_stmt_list(yylhs.location)); }
#line 2576 "parser.cpp"
    break;

  case 84: // stmt_break: "break" ";"
#line 504 "parser.ypp"
        { yylhs.value.as < stmt_break::ptr > () = make_stmt_break(yylhs.location); }
#line 2582 "parser.cpp"
    break;

  case 85: // stmt_continue: "continue" ";"
#line 509 "parser.ypp"
        { yylhs.value.as < stmt_continue::ptr > () = make_stmt_continue(yylhs.location); }
#line 2588 "parser.cpp"
    break;

  case 86: // stmt_return: "return" expr ";"
#line 514 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = make_stmt_return(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 2594 "parser.cpp"
    break;

  case 87: // stmt_return: "return" ";"
#line 516 "parser.ypp"
        { yylhs.value.as < stmt_return::ptr > () = make_stmt_return(yylhs.location, make_node(yylhs.location)); }
#line 2600 "parser.cpp"
    break;

  case 88: // stmt_breakpoint: "breakpoint" ";"
#line 521 "parser.ypp"
        { yylhs.value.as < stmt_breakpoint::ptr > () = make_stmt_breakpoint(yylhs.location); }
#line 2606 "parser.cpp"
    break;

  case 89: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 526 "parser.ypp"
        { yylhs.value.as < stmt_prof_begin::ptr > () = make_stmt_prof_begin(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2612 "parser.cpp"
    break;

  case 90: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 531 "parser.ypp"
        { yylhs.value.as < stmt_prof_end::ptr > () = make_stmt_prof_end(yylhs.location, std::move(yystack_[2].value.as < expr_arguments::ptr > ())); }
#line 2618 "parser.cpp"
    break;

  case 91: // expr: expr_ternary
#line 535 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2624 "parser.cpp"
    break;

  case 92: // expr: expr_binary
#line 536 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2630 "parser.cpp"
    break;

  case 93: // expr: expr_primitive
#line 537 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2636 "parser.cpp"
    break;

  case 94: // expr_or_empty: expr
#line 541 "parser.ypp"
                     { yylhs.value.as < expr > () = std::move(yystack_[0].value.as < expr > ()); }
#line 2642 "parser.cpp"
    break;

  case 95: // expr_or_empty: %empty
#line 542 "parser.ypp"
                     { yylhs.value.as < expr > ().as_node = make_node(yylhs.location); }
#line 2648 "parser.cpp"
    break;

  case 96: // expr_assign: expr_tuple "=" expr
#line 547 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2654 "parser.cpp"
    break;

  case 97: // expr_assign: expr_object "=" expr
#line 549 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2660 "parser.cpp"
    break;

  case 98: // expr_assign: expr_object "|=" expr
#line 551 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_bitwise_or(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2666 "parser.cpp"
    break;

  case 99: // expr_assign: expr_object "&=" expr
#line 553 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_bitwise_and(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2672 "parser.cpp"
    break;

  case 100: // expr_assign: expr_object "^=" expr
#line 555 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_bitwise_exor(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2678 "parser.cpp"
    break;

  case 101: // expr_assign: expr_object "<<=" expr
#line 557 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_shift_left(yylhs.location, std::move(yystack_[2].value.as < expr > ()),std::move( yystack_[0].value.as < expr > ())); }
#line 2684 "parser.cpp"
    break;

  case 102: // expr_assign: expr_object ">>=" expr
#line 559 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_shift_right(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2690 "parser.cpp"
    break;

  case 103: // expr_assign: expr_object "+=" expr
#line 561 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_add(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2696 "parser.cpp"
    break;

  case 104: // expr_assign: expr_object "-=" expr
#line 563 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_sub(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2702 "parser.cpp"
    break;

  case 105: // expr_assign: expr_object "*=" expr
#line 565 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_mul(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2708 "parser.cpp"
    break;

  case 106: // expr_assign: expr_object "/=" expr
#line 567 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_div(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2714 "parser.cpp"
    break;

  case 107: // expr_assign: expr_object "%=" expr
#line 569 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_assign_mod(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2720 "parser.cpp"
    break;

  case 108: // expr_increment: "++" expr_object
#line 574 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_increment(yylhs.location, std::move(yystack_[0].value.as < expr > ()), true); }
#line 2726 "parser.cpp"
    break;

  case 109: // expr_increment: expr_object "++"
#line 576 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_increment(yylhs.location, std::move(yystack_[1].value.as < expr > ()), false); }
#line 2732 "parser.cpp"
    break;

  case 110: // expr_decrement: "--" expr_object
#line 581 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_decrement(yylhs.location, std::move(yystack_[0].value.as < expr > ()), true); }
#line 2738 "parser.cpp"
    break;

  case 111: // expr_decrement: expr_object "--"
#line 583 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_decrement(yylhs.location, std::move(yystack_[1].value.as < expr > ()), false); }
#line 2744 "parser.cpp"
    break;

  case 112: // expr_ternary: expr "?" expr ":" expr
#line 588 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_ternary(yylhs.location, std::move(yystack_[4].value.as < expr > ()), std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2750 "parser.cpp"
    break;

  case 113: // expr_binary: expr "||" expr
#line 593 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_or(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2756 "parser.cpp"
    break;

  case 114: // expr_binary: expr "&&" expr
#line 595 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_and(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2762 "parser.cpp"
    break;

  case 115: // expr_binary: expr "==" expr
#line 597 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_equality(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2768 "parser.cpp"
    break;

  case 116: // expr_binary: expr "!=" expr
#line 599 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_inequality(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2774 "parser.cpp"
    break;

  case 117: // expr_binary: expr "<=" expr
#line 601 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_less_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2780 "parser.cpp"
    break;

  case 118: // expr_binary: expr ">=" expr
#line 603 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_greater_equal(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2786 "parser.cpp"
    break;

  case 119: // expr_binary: expr "<" expr
#line 605 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_less(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2792 "parser.cpp"
    break;

  case 120: // expr_binary: expr ">" expr
#line 607 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_greater(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2798 "parser.cpp"
    break;

  case 121: // expr_binary: expr "|" expr
#line 609 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_bitwise_or(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2804 "parser.cpp"
    break;

  case 122: // expr_binary: expr "&" expr
#line 611 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_bitwise_and(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2810 "parser.cpp"
    break;

  case 123: // expr_binary: expr "^" expr
#line 613 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_bitwise_exor(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2816 "parser.cpp"
    break;

  case 124: // expr_binary: expr "<<" expr
#line 615 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_shift_left(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2822 "parser.cpp"
    break;

  case 125: // expr_binary: expr ">>" expr
#line 617 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_shift_right(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2828 "parser.cpp"
    break;

  case 126: // expr_binary: expr "+" expr
#line 619 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_add(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2834 "parser.cpp"
    break;

  case 127: // expr_binary: expr "-" expr
#line 621 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_sub(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2840 "parser.cpp"
    break;

  case 128: // expr_binary: expr "*" expr
#line 623 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_mul(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2846 "parser.cpp"
    break;

  case 129: // expr_binary: expr "/" expr
#line 625 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_div(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2852 "parser.cpp"
    break;

  case 130: // expr_binary: expr "%" expr
#line 627 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = make_expr_mod(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr > ())); }
#line 2858 "parser.cpp"
    break;

  case 131: // expr_primitive: expr_complement
#line 631 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_complement::ptr > ()); }
#line 2864 "parser.cpp"
    break;

  case 132: // expr_primitive: expr_negate
#line 632 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_negate::ptr > ()); }
#line 2870 "parser.cpp"
    break;

  case 133: // expr_primitive: expr_not
#line 633 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_not::ptr > ()); }
#line 2876 "parser.cpp"
    break;

  case 134: // expr_primitive: expr_call
#line 634 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 2882 "parser.cpp"
    break;

  case 135: // expr_primitive: expr_method
#line 635 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 2888 "parser.cpp"
    break;

  case 136: // expr_primitive: expr_add_array
#line 636 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_add_array::ptr > ()); }
#line 2894 "parser.cpp"
    break;

  case 137: // expr_primitive: expr_isdefined
#line 637 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_isdefined::ptr > ()); }
#line 2900 "parser.cpp"
    break;

  case 138: // expr_primitive: expr_istrue
#line 638 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_istrue::ptr > ()); }
#line 2906 "parser.cpp"
    break;

  case 139: // expr_primitive: expr_reference
#line 639 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_reference::ptr > ()); }
#line 2912 "parser.cpp"
    break;

  case 140: // expr_primitive: expr_array
#line 640 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 2918 "parser.cpp"
    break;

  case 141: // expr_primitive: expr_field
#line 641 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 2924 "parser.cpp"
    break;

  case 142: // expr_primitive: expr_size
#line 642 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_size::ptr > ()); }
#line 2930 "parser.cpp"
    break;

  case 143: // expr_primitive: expr_paren
#line 643 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_paren::ptr > ()); }
#line 2936 "parser.cpp"
    break;

  case 144: // expr_primitive: expr_thisthread
#line 644 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_thisthread::ptr > ()); }
#line 2942 "parser.cpp"
    break;

  case 145: // expr_primitive: expr_empty_array
#line 645 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_empty_array::ptr > ()); }
#line 2948 "parser.cpp"
    break;

  case 146: // expr_primitive: expr_undefined
#line 646 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_undefined::ptr > ()); }
#line 2954 "parser.cpp"
    break;

  case 147: // expr_primitive: expr_game
#line 647 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 2960 "parser.cpp"
    break;

  case 148: // expr_primitive: expr_self
#line 648 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 2966 "parser.cpp"
    break;

  case 149: // expr_primitive: expr_anim
#line 649 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 2972 "parser.cpp"
    break;

  case 150: // expr_primitive: expr_level
#line 650 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 2978 "parser.cpp"
    break;

  case 151: // expr_primitive: expr_animation
#line 651 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_animation::ptr > ()); }
#line 2984 "parser.cpp"
    break;

  case 152: // expr_primitive: expr_animtree
#line 652 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_animtree::ptr > ()); }
#line 2990 "parser.cpp"
    break;

  case 153: // expr_primitive: expr_identifier
#line 653 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 2996 "parser.cpp"
    break;

  case 154: // expr_primitive: expr_istring
#line 654 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_istring::ptr > ()); }
#line 3002 "parser.cpp"
    break;

  case 155: // expr_primitive: expr_string
#line 655 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_string::ptr > ()); }
#line 3008 "parser.cpp"
    break;

  case 156: // expr_primitive: expr_vector
#line 656 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_vector::ptr > ()); }
#line 3014 "parser.cpp"
    break;

  case 157: // expr_primitive: expr_float
#line 657 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_float::ptr > ()); }
#line 3020 "parser.cpp"
    break;

  case 158: // expr_primitive: expr_integer
#line 658 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_integer::ptr > ()); }
#line 3026 "parser.cpp"
    break;

  case 159: // expr_primitive: expr_false
#line 659 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_false::ptr > ()); }
#line 3032 "parser.cpp"
    break;

  case 160: // expr_primitive: expr_true
#line 660 "parser.ypp"
                            { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_true::ptr > ()); }
#line 3038 "parser.cpp"
    break;

  case 161: // expr_complement: "~" expr
#line 665 "parser.ypp"
        { yylhs.value.as < expr_complement::ptr > () = make_expr_complement(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 3044 "parser.cpp"
    break;

  case 162: // expr_negate: "-" expr_identifier
#line 670 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_identifier::ptr > ()) }); }
#line 3050 "parser.cpp"
    break;

  case 163: // expr_negate: "-" expr_paren
#line 672 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_paren::ptr > ()) }); }
#line 3056 "parser.cpp"
    break;

  case 164: // expr_negate: "-" expr_array
#line 674 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_array::ptr > ()) }); }
#line 3062 "parser.cpp"
    break;

  case 165: // expr_negate: "-" expr_field
#line 676 "parser.ypp"
        { yylhs.value.as < expr_negate::ptr > () = make_expr_negate(yylhs.location, expr{ std::move(yystack_[0].value.as < expr_field::ptr > ()) }); }
#line 3068 "parser.cpp"
    break;

  case 166: // expr_not: "!" expr
#line 681 "parser.ypp"
        { yylhs.value.as < expr_not::ptr > () = make_expr_not(yylhs.location, std::move(yystack_[0].value.as < expr > ())); }
#line 3074 "parser.cpp"
    break;

  case 167: // expr_call: expr_function
#line 685 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = make_expr_call(yylhs.location, std::move(yystack_[0].value.as < call > ())); }
#line 3080 "parser.cpp"
    break;

  case 168: // expr_call: expr_pointer
#line 686 "parser.ypp"
                                   { yylhs.value.as < expr_call::ptr > () = make_expr_call(yylhs.location, std::move(yystack_[0].value.as < call > ())); }
#line 3086 "parser.cpp"
    break;

  case 169: // expr_method: expr_object expr_function
#line 689 "parser.ypp"
                                   { yylhs.value.as < expr_method::ptr > () = make_expr_method(yylhs.location, std::move(yystack_[1].value.as < expr > ()), std::move(yystack_[0].value.as < call > ())); }
#line 3092 "parser.cpp"
    break;

  case 170: // expr_method: expr_object expr_pointer
#line 690 "parser.ypp"
                                   { yylhs.value.as < expr_method::ptr > () = make_expr_method(yylhs.location, std::move(yystack_[1].value.as < expr > ()), std::move(yystack_[0].value.as < call > ())); }
#line 3098 "parser.cpp"
    break;

  case 171: // expr_function: expr_identifier "(" expr_arguments ")"
#line 695 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3104 "parser.cpp"
    break;

  case 172: // expr_function: expr_path "::" expr_identifier "(" expr_arguments ")"
#line 697 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3110 "parser.cpp"
    break;

  case 173: // expr_function: "thread" expr_identifier "(" expr_arguments ")"
#line 699 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3116 "parser.cpp"
    break;

  case 174: // expr_function: "thread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 701 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3122 "parser.cpp"
    break;

  case 175: // expr_function: "childthread" expr_identifier "(" expr_arguments ")"
#line 703 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3128 "parser.cpp"
    break;

  case 176: // expr_function: "childthread" expr_path "::" expr_identifier "(" expr_arguments ")"
#line 705 "parser.ypp"
        { yylhs.value.as < call > ().as_function = make_expr_function(yylhs.location, std::move(yystack_[5].value.as < expr_path::ptr > ()), std::move(yystack_[3].value.as < expr_identifier::ptr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3134 "parser.cpp"
    break;

  case 177: // expr_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 710 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::normal); }
#line 3140 "parser.cpp"
    break;

  case 178: // expr_pointer: "thread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 712 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::thread); }
#line 3146 "parser.cpp"
    break;

  case 179: // expr_pointer: "childthread" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 714 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::childthread); }
#line 3152 "parser.cpp"
    break;

  case 180: // expr_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 716 "parser.ypp"
        { yylhs.value.as < call > ().as_pointer = make_expr_pointer(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[1].value.as < expr_arguments::ptr > ()), call::mode::builtin); }
#line 3158 "parser.cpp"
    break;

  case 181: // expr_add_array: "[" expr_arguments_no_empty "]"
#line 721 "parser.ypp"
        { yylhs.value.as < expr_add_array::ptr > () = make_expr_add_array(yylhs.location, std::move(yystack_[1].value.as < expr_arguments::ptr > ())); }
#line 3164 "parser.cpp"
    break;

  case 182: // expr_parameters: expr_parameters "," expr_identifier
#line 726 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = std::move(yystack_[2].value.as < expr_parameters::ptr > ()); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3170 "parser.cpp"
    break;

  case 183: // expr_parameters: expr_identifier
#line 728 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = make_expr_parameters(yylhs.location); yylhs.value.as < expr_parameters::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3176 "parser.cpp"
    break;

  case 184: // expr_parameters: %empty
#line 730 "parser.ypp"
        { yylhs.value.as < expr_parameters::ptr > () = make_expr_parameters(yylhs.location); }
#line 3182 "parser.cpp"
    break;

  case 185: // expr_arguments: expr_arguments_no_empty
#line 735 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[0].value.as < expr_arguments::ptr > ()); }
#line 3188 "parser.cpp"
    break;

  case 186: // expr_arguments: %empty
#line 737 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = make_expr_arguments(yylhs.location); }
#line 3194 "parser.cpp"
    break;

  case 187: // expr_arguments_no_empty: expr_arguments "," expr
#line 742 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = std::move(yystack_[2].value.as < expr_arguments::ptr > ()); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3200 "parser.cpp"
    break;

  case 188: // expr_arguments_no_empty: expr
#line 744 "parser.ypp"
        { yylhs.value.as < expr_arguments::ptr > () = make_expr_arguments(yylhs.location); yylhs.value.as < expr_arguments::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3206 "parser.cpp"
    break;

  case 189: // expr_isdefined: "isdefined" "(" expr ")"
#line 749 "parser.ypp"
        { yylhs.value.as < expr_isdefined::ptr > () = make_expr_isdefined(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 3212 "parser.cpp"
    break;

  case 190: // expr_istrue: "istrue" "(" expr ")"
#line 754 "parser.ypp"
        { yylhs.value.as < expr_istrue::ptr > () = make_expr_istrue(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 3218 "parser.cpp"
    break;

  case 191: // expr_reference: "::" expr_identifier
#line 759 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = make_expr_reference(yylhs.location, make_expr_path(yylhs.location), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3224 "parser.cpp"
    break;

  case 192: // expr_reference: expr_path "::" expr_identifier
#line 761 "parser.ypp"
        { yylhs.value.as < expr_reference::ptr > () = make_expr_reference(yylhs.location, std::move(yystack_[2].value.as < expr_path::ptr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3230 "parser.cpp"
    break;

  case 193: // expr_tuple: "[" expr_tuple_arguments "]"
#line 766 "parser.ypp"
        { yylhs.value.as < expr > ().as_node = std::move(yystack_[1].value.as < expr_tuple::ptr > ());
          yylhs.value.as < expr > ().as_tuple->temp = expr{ std::make_unique<expr_identifier>(yylhs.value.as < expr > ().loc(), fmt::format("_temp_{}", ++index)) };
        }
#line 3238 "parser.cpp"
    break;

  case 194: // expr_tuple_arguments: expr_tuple_arguments "," expr_tuple_types
#line 773 "parser.ypp"
        { yylhs.value.as < expr_tuple::ptr > () = std::move(yystack_[2].value.as < expr_tuple::ptr > ()); yylhs.value.as < expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3244 "parser.cpp"
    break;

  case 195: // expr_tuple_arguments: expr_tuple_types
#line 775 "parser.ypp"
        { yylhs.value.as < expr_tuple::ptr > () = make_expr_tuple(yylhs.location); yylhs.value.as < expr_tuple::ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr > ())); }
#line 3250 "parser.cpp"
    break;

  case 196: // expr_tuple_types: expr_array
#line 779 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3256 "parser.cpp"
    break;

  case 197: // expr_tuple_types: expr_field
#line 780 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3262 "parser.cpp"
    break;

  case 198: // expr_tuple_types: expr_identifier
#line 781 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3268 "parser.cpp"
    break;

  case 199: // expr_array: expr_object "[" expr "]"
#line 786 "parser.ypp"
        { yylhs.value.as < expr_array::ptr > () = make_expr_array(yylhs.location, std::move(yystack_[3].value.as < expr > ()), std::move(yystack_[1].value.as < expr > ())); }
#line 3274 "parser.cpp"
    break;

  case 200: // expr_field: expr_object "." expr_identifier_nosize
#line 791 "parser.ypp"
        { yylhs.value.as < expr_field::ptr > () = make_expr_field(yylhs.location, std::move(yystack_[2].value.as < expr > ()), std::move(yystack_[0].value.as < expr_identifier::ptr > ())); }
#line 3280 "parser.cpp"
    break;

  case 201: // expr_size: expr_object "." "size"
#line 796 "parser.ypp"
        { yylhs.value.as < expr_size::ptr > () = make_expr_size(yylhs.location, std::move(yystack_[2].value.as < expr > ())); }
#line 3286 "parser.cpp"
    break;

  case 202: // expr_paren: "(" expr ")"
#line 801 "parser.ypp"
        { yylhs.value.as < expr_paren::ptr > () = make_expr_paren(yylhs.location, std::move(yystack_[1].value.as < expr > ())); }
#line 3292 "parser.cpp"
    break;

  case 203: // expr_object: expr_call
#line 805 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_call::ptr > ()); }
#line 3298 "parser.cpp"
    break;

  case 204: // expr_object: expr_method
#line 806 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_method::ptr > ()); }
#line 3304 "parser.cpp"
    break;

  case 205: // expr_object: expr_array
#line 807 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_array::ptr > ()); }
#line 3310 "parser.cpp"
    break;

  case 206: // expr_object: expr_field
#line 808 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_field::ptr > ()); }
#line 3316 "parser.cpp"
    break;

  case 207: // expr_object: expr_game
#line 809 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_game::ptr > ()); }
#line 3322 "parser.cpp"
    break;

  case 208: // expr_object: expr_self
#line 810 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_self::ptr > ()); }
#line 3328 "parser.cpp"
    break;

  case 209: // expr_object: expr_anim
#line 811 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_anim::ptr > ()); }
#line 3334 "parser.cpp"
    break;

  case 210: // expr_object: expr_level
#line 812 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_level::ptr > ()); }
#line 3340 "parser.cpp"
    break;

  case 211: // expr_object: expr_identifier
#line 813 "parser.ypp"
                      { yylhs.value.as < expr > ().as_node = std::move(yystack_[0].value.as < expr_identifier::ptr > ()); }
#line 3346 "parser.cpp"
    break;

  case 212: // expr_thisthread: "thisthread"
#line 818 "parser.ypp"
        { yylhs.value.as < expr_thisthread::ptr > () = make_expr_thisthread(yylhs.location); }
#line 3352 "parser.cpp"
    break;

  case 213: // expr_empty_array: "[" "]"
#line 823 "parser.ypp"
        { yylhs.value.as < expr_empty_array::ptr > () = make_expr_empty_array(yylhs.location); }
#line 3358 "parser.cpp"
    break;

  case 214: // expr_undefined: "undefined"
#line 828 "parser.ypp"
        { yylhs.value.as < expr_undefined::ptr > () = make_expr_undefined(yylhs.location); }
#line 3364 "parser.cpp"
    break;

  case 215: // expr_game: "game"
#line 833 "parser.ypp"
        { yylhs.value.as < expr_game::ptr > () = make_expr_game(yylhs.location); }
#line 3370 "parser.cpp"
    break;

  case 216: // expr_self: "self"
#line 838 "parser.ypp"
        { yylhs.value.as < expr_self::ptr > () = make_expr_self(yylhs.location); }
#line 3376 "parser.cpp"
    break;

  case 217: // expr_anim: "anim"
#line 843 "parser.ypp"
        { yylhs.value.as < expr_anim::ptr > () = make_expr_anim(yylhs.location); }
#line 3382 "parser.cpp"
    break;

  case 218: // expr_level: "level"
#line 848 "parser.ypp"
        { yylhs.value.as < expr_level::ptr > () = make_expr_level(yylhs.location); }
#line 3388 "parser.cpp"
    break;

  case 219: // expr_animation: "%" "identifier"
#line 853 "parser.ypp"
        { yylhs.value.as < expr_animation::ptr > () = make_expr_animation(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3394 "parser.cpp"
    break;

  case 220: // expr_animtree: "#animtree"
#line 858 "parser.ypp"
        { yylhs.value.as < expr_animtree::ptr > () = make_expr_animtree(yylhs.location); }
#line 3400 "parser.cpp"
    break;

  case 221: // expr_identifier_nosize: "identifier"
#line 863 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = make_expr_identifier(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3406 "parser.cpp"
    break;

  case 222: // expr_identifier: "identifier"
#line 868 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = make_expr_identifier(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3412 "parser.cpp"
    break;

  case 223: // expr_identifier: "size"
#line 870 "parser.ypp"
        { yylhs.value.as < expr_identifier::ptr > () = make_expr_identifier(yylhs.location, "size"); }
#line 3418 "parser.cpp"
    break;

  case 224: // expr_path: "path" "/" "identifier"
#line 875 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = make_expr_path(yylhs.location, yystack_[2].value.as < std::string > () + "/" + yystack_[0].value.as < std::string > ()); }
#line 3424 "parser.cpp"
    break;

  case 225: // expr_path: "identifier"
#line 877 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = make_expr_path(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3430 "parser.cpp"
    break;

  case 226: // expr_path: "path"
#line 879 "parser.ypp"
        { yylhs.value.as < expr_path::ptr > () = make_expr_path(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3436 "parser.cpp"
    break;

  case 227: // expr_istring: "localized string"
#line 884 "parser.ypp"
        { yylhs.value.as < expr_istring::ptr > () = make_expr_istring(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3442 "parser.cpp"
    break;

  case 228: // expr_string: "string literal"
#line 889 "parser.ypp"
        { yylhs.value.as < expr_string::ptr > () = make_expr_string(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3448 "parser.cpp"
    break;

  case 229: // expr_vector: "(" expr "," expr "," expr ")"
#line 894 "parser.ypp"
        { yylhs.value.as < expr_vector::ptr > () = make_expr_vector(yylhs.location, std::move(yystack_[5].value.as < expr > ()), std::move(yystack_[3].value.as < expr > ()), std::move(yystack_[1].value.as < expr > ())); }
#line 3454 "parser.cpp"
    break;

  case 230: // expr_float: "-" "float"
#line 899 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = make_expr_float(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3460 "parser.cpp"
    break;

  case 231: // expr_float: "float"
#line 901 "parser.ypp"
        { yylhs.value.as < expr_float::ptr > () = make_expr_float(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3466 "parser.cpp"
    break;

  case 232: // expr_integer: "-" "integer"
#line 906 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = make_expr_integer(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 3472 "parser.cpp"
    break;

  case 233: // expr_integer: "integer"
#line 908 "parser.ypp"
        { yylhs.value.as < expr_integer::ptr > () = make_expr_integer(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 3478 "parser.cpp"
    break;

  case 234: // expr_false: "false"
#line 913 "parser.ypp"
        { yylhs.value.as < expr_false::ptr > () = make_expr_false(yylhs.location); }
#line 3484 "parser.cpp"
    break;

  case 235: // expr_true: "true"
#line 918 "parser.ypp"
        { yylhs.value.as < expr_true::ptr > () = make_expr_true(yylhs.location); }
#line 3490 "parser.cpp"
    break;


#line 3494 "parser.cpp"

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


  const short parser::yypact_ninf_ = -177;

  const short parser::yytable_ninf_ = -226;

  const short
  parser::yypact_[] =
  {
     185,  -177,  -177,   -51,   -51,   -43,  -177,  -177,    30,   185,
    -177,  -177,  -177,  -177,  -177,    -3,   -31,  -177,   -10,    10,
     -11,  -177,  -177,  -177,  -177,   -30,     4,  -177,  -177,  -177,
      29,   -16,  -177,  -177,    33,    44,   -30,  -177,   928,  -177,
    -177,  1089,  1326,    48,   -50,    85,  1477,    86,   101,   104,
     105,   -73,    74,    97,   107,  1196,   108,   127,   129,   -37,
     -35,    89,  -177,  -177,  -177,  -177,  -177,   229,   565,   565,
      87,  -177,  -177,  1010,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
     120,   121,   126,   130,   131,  -177,  -177,    70,  -177,  -177,
     626,  -177,  -177,  -177,  -177,   147,   140,  -177,  -177,  1168,
    -177,  -177,  -177,  -177,  -177,   152,   154,  1326,  1261,   -30,
    1326,  1326,   486,    69,  -177,  -177,  -177,  2183,  -177,  -177,
    -177,  -177,  -177,  -177,    35,   448,  -177,  -177,  -177,  -177,
     526,   638,  -177,  -177,   765,  -177,  -177,  -177,   888,   956,
     965,  1042,  -177,  -177,   352,   151,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,   157,  -177,  1326,   189,  1326,   551,
     -30,  1326,   113,   158,   161,  -177,  -177,  -177,  -177,  2218,
    -177,  1326,  1326,   162,   171,   164,   170,   175,   169,   176,
    1391,  -177,  -177,    55,  -177,    58,    68,  1121,   -27,   177,
    1121,  1121,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  1326,
     179,   183,   186,   187,  1391,   139,  -177,  -177,  1326,  1326,
    1326,  1326,  1326,  1326,  1326,  1326,  1326,  1326,  1326,  -177,
    -177,   147,  1326,   -30,  -177,  -177,  1326,  1326,  1487,  1261,
    -177,  2231,   182,   190,  -177,  -177,  -177,  1326,  -177,  -177,
     526,   638,  -177,   352,  -177,  -177,  1326,  1326,  1326,  1326,
    1326,  1326,  1326,  1326,  1326,  1326,  1326,  1326,  1326,  1326,
    1326,  1326,  1326,  1326,  1326,   -23,   -30,   193,  1653,   204,
    1687,   195,  -177,  -177,  -177,   688,   -17,  1721,  -177,  -177,
    -177,   -13,  -177,    28,  1326,  1326,   -30,  1326,  1326,   -30,
    1326,  1257,  -177,   565,  1326,  2231,  1326,  1326,  1326,  1326,
    1322,  -177,  -177,  2231,  2231,  2231,  2231,  2231,  2231,  2231,
    2231,  2231,  2231,  2231,    31,   206,  1755,  1789,  -177,  1326,
    1257,  1326,  -177,  1823,  2148,   150,   150,  2262,  2272,   559,
     559,   254,   254,   254,   254,  2303,   829,  2313,   -78,   -78,
    -177,  -177,  -177,  -177,   206,  -177,  1477,  1326,  1477,  1326,
    1326,   -30,    44,   198,   199,  1387,    32,   210,  2033,    39,
     211,  2073,   207,  -177,  1857,  1531,  1575,  1619,  -177,  -177,
    1326,  -177,  -177,  2112,  2231,  1326,   242,  1891,  -177,  2231,
     209,  1925,   241,  -177,  -177,  -177,   216,  -177,  1326,   222,
    -177,  1326,   230,   237,   232,   233,  1326,   235,  1326,   239,
    1326,    51,  1326,  2231,  1477,   240,   551,  1477,  1326,   257,
      61,   258,    83,   260,  1326,  -177,  -177,   238,  -177,   253,
    -177,   261,  -177,  1959,  -177,  -177,   262,  -177,  1993,  1326,
    -177,  1326,  -177,  1326,    93,   255,   256,   263,  -177,  1477,
    1477,    96,   115,   118,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,    12,    13,     0,     0,     0,   223,   222,     0,     2,
       7,     8,     9,    14,    15,     0,   226,   225,     0,     0,
       0,     1,     4,     5,     6,   184,     0,    10,    11,   228,
       0,     0,   183,   224,     0,     0,     0,    16,     0,    17,
     182,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   215,   216,   217,   218,    52,     0,     0,     0,
     222,    43,    48,     0,    44,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
       0,     0,     0,   203,   204,   167,   168,     0,   205,   206,
       0,   207,   208,   209,   210,   211,     0,    50,    46,     0,
     220,   212,   235,   234,   214,     0,     0,     0,   186,     0,
       0,     0,     0,     0,   227,   231,   233,     0,    91,    92,
      93,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,     0,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,     0,   154,   155,   156,   157,
     158,   159,   160,    70,     0,    71,     0,     0,     0,    56,
       0,     0,     0,     0,     0,    83,    84,    85,    87,     0,
      88,   186,   186,     0,     0,     0,     0,     0,     0,     0,
       0,   203,   204,     0,   195,   205,   206,     0,   211,     0,
     108,   110,    51,    47,    59,    60,    61,    57,    58,     0,
       0,     0,     0,     0,     0,     0,   109,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   169,
     170,     0,   186,     0,    49,    45,     0,     0,     0,   186,
     213,   188,     0,   185,   191,   166,   161,     0,   230,   232,
     164,   165,   163,   162,   219,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    53,    54,    55,     0,     0,     0,    82,    81,
      86,     0,   185,     0,     0,   186,     0,     0,   186,     0,
       0,     0,   193,     0,     0,    96,     0,     0,     0,     0,
       0,   221,   200,    97,   103,   104,   105,   106,   107,    98,
      99,   100,   102,   101,     0,     0,     0,     0,   202,     0,
     188,     0,   181,     0,     0,   124,   125,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   126,   127,
     128,   129,   130,   201,   192,    72,     0,     0,     0,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   194,     0,     0,     0,     0,   199,   171,
     186,   189,   190,     0,   187,     0,    73,     0,    75,    94,
       0,     0,     0,    80,    89,    90,     0,   173,   186,     0,
     175,   186,     0,     0,     0,     0,   186,     0,   186,     0,
     186,     0,     0,   112,     0,     0,    56,     0,     0,     0,
       0,     0,     0,     0,   186,    62,    64,   185,    67,   185,
      69,   185,   172,     0,    74,    76,     0,    78,     0,   186,
     174,   186,   176,   186,     0,     0,     0,     0,   229,     0,
       0,     0,     0,     0,   177,    63,    66,    68,    77,    79,
     178,   179,   180
  };

  const short
  parser::yypgoto_[] =
  {
    -177,  -177,  -177,   315,   317,   321,  -177,  -177,    -6,   266,
    -177,  -177,  -177,   -34,   -91,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,   603,
    -177,  -176,  -174,  -172,  -177,  -177,  -177,  -177,  -177,  -177,
     -12,    57,  -102,   -65,  -177,  -177,   -90,  -126,  -177,  -177,
    -177,  -177,  -177,    23,    95,   119,  -177,   208,   136,  -177,
    -177,  -177,   215,   264,   336,   432,  -177,  -177,  -177,     0,
      12,  -177,   -14,  -177,  -177,   290,  -177,  -177
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    11,    12,    13,    14,    71,    72,
     119,    73,    74,    75,   291,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   251,
     400,   100,   101,   102,   138,   139,   140,   141,   142,   143,
     144,   145,   105,   106,   146,    31,   252,   302,   147,   148,
     149,   107,   203,   204,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   322,   164,
     165,   166,   167,   168,   169,   170,   171,   172
  };

  const short
  parser::yytable_[] =
  {
      15,    39,   253,   292,   174,   293,    30,   294,   239,    15,
       6,    20,     6,   370,   175,    18,    19,     6,   282,   283,
     284,   193,   182,   196,   363,    32,   103,   242,    29,   103,
      21,   136,  -198,  -198,   103,   118,    40,   183,   115,    35,
     177,   115,   373,   371,    36,   240,   115,   341,    16,    17,
     116,    25,   239,   116,    27,   201,   201,   201,   116,   194,
     197,   103,    16,    70,    16,    70,    26,   208,   115,   115,
       7,   195,   198,   115,    28,  -203,  -203,   321,  -203,   116,
     116,   116,  -203,   374,    34,   116,   389,   407,   341,   240,
      29,   341,   341,  -203,   410,   104,  -203,    37,   104,   341,
      38,   301,   303,   104,    33,   239,   442,   103,   239,   239,
     241,   341,   173,   245,   312,   313,   450,  -196,  -196,   115,
     201,   341,   116,   253,   202,   202,   202,  -197,  -197,   254,
     104,   116,   263,   108,  -203,  -203,   108,   185,   452,   176,
     178,   108,   240,   341,   116,   240,   240,   199,   464,  -225,
     219,   470,   334,   341,   241,   179,   341,   109,   180,   181,
     109,   186,   205,   108,   108,   109,   116,   201,   108,   264,
     471,   187,   190,   472,   110,   341,   104,   110,   341,   115,
     296,   191,   110,   192,   214,   215,   206,   109,   109,   202,
     216,   116,   109,   239,   217,   218,     1,     2,     3,     4,
       5,   242,   243,   207,   210,   211,   246,   241,   247,   110,
     241,   241,   287,   286,   108,   376,   289,   259,   379,   116,
     304,   298,   116,   116,   299,   305,   306,   260,   307,   308,
     240,   309,     6,   316,   310,   314,   202,   317,   109,   321,
     318,   319,   341,   335,   280,   281,   282,   283,   284,   342,
     292,   261,   293,   111,   294,   110,   111,   365,   367,   369,
     390,   111,   404,   405,   408,   411,   413,   424,   207,    59,
      60,   428,    61,   426,   108,   429,     6,    62,    63,    64,
      65,   431,   111,   111,   111,     7,   364,   200,   111,   433,
     437,   434,   439,   455,   441,   241,   435,   436,   109,   438,
     421,   201,   112,   440,   445,   112,   377,   116,   456,   380,
     112,   449,   451,   208,   453,   295,   457,   459,   430,   465,
     466,   432,   267,   268,    22,   116,    23,   467,    16,    70,
      24,   112,   112,   112,   111,   446,   383,   112,   403,   213,
     262,   184,     0,     0,   454,     0,     0,   111,   280,   281,
     282,   283,   284,     0,   103,     0,   103,     0,     0,   461,
     396,   462,   398,   463,     0,     0,   115,     0,   115,     0,
     202,   402,     0,     0,   113,     0,     0,   113,   116,     0,
     116,     0,   113,   112,     0,     0,     0,     0,     0,     0,
       0,     0,  -211,  -211,   111,  -211,   112,     0,     0,  -211,
       0,     0,     0,   113,   113,   113,   242,     0,   205,   113,
    -211,     0,   103,  -211,   201,   103,     0,     0,   444,     0,
       0,   447,     0,   104,   115,   104,   115,   115,     0,     0,
       0,     0,   206,     0,     0,     0,   116,     0,   116,   116,
       0,     0,     0,   112,     0,     0,     0,   103,   103,   207,
       0,  -211,  -211,   468,   469,   113,     0,     0,     0,   115,
     115,   108,     0,   108,     0,     0,     0,     0,   113,     0,
     114,   116,   116,   114,     0,     0,     0,     0,   114,     0,
       0,   104,     0,   202,   104,   109,     0,   109,  -204,  -204,
       0,  -204,     0,     0,     0,  -204,     0,     0,     0,   114,
     114,   114,   110,     0,   110,   114,  -204,     0,     0,  -204,
       0,     0,     0,     0,     0,   113,   104,   104,     0,   108,
       0,   108,   108,     0,     0,     0,    59,    60,   111,    61,
       0,     0,     0,     6,    62,    63,    64,    65,     0,     0,
     257,     0,     0,   109,   209,   109,   109,  -204,  -204,     0,
       0,   114,     0,     0,   108,   108,     0,     0,     0,     0,
     110,     0,   295,   110,   114,     0,  -205,  -205,     0,  -205,
       0,     0,     0,  -205,     0,     0,     0,   112,   109,   109,
       0,   111,     0,   111,  -205,    16,    70,  -205,     0,   258,
     259,    59,    60,     0,    61,   110,   110,     0,     6,    62,
      63,    64,    65,     0,     0,    59,    60,     0,    61,    67,
       0,   114,     6,    62,    63,    64,    65,    68,    69,     0,
       0,     0,     0,   209,     0,  -205,  -205,   267,   268,     0,
     112,     0,   112,   273,   274,   275,   276,     0,     0,   111,
       0,   111,   111,   220,   221,   137,   222,   223,     0,   113,
      16,    70,     0,   280,   281,   282,   283,   284,   189,     0,
       0,     0,     0,     0,    16,    70,    59,    60,     0,    61,
       0,     0,     0,     6,   111,   111,     0,     0,  -206,  -206,
       0,  -206,     0,     0,   224,  -206,     0,   225,   112,     0,
     112,   112,   226,   227,     0,     0,  -206,     0,     0,  -206,
       0,     0,   113,     0,   113,     0,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,     0,     0,     0,
       0,     0,     0,   112,   112,    16,    70,     0,    59,    60,
     248,    61,     0,   255,   256,     6,     0,  -206,  -206,     0,
       0,     0,     0,     0,     0,   114,   224,     0,     0,   225,
       0,     0,     0,     0,   226,   227,     0,     0,     0,     0,
     113,     0,   113,   113,     0,     0,     0,     0,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   288,
       0,   290,     0,     0,   297,     0,     0,    16,    70,     0,
       0,     0,     0,     0,     0,   113,   113,     0,   114,     0,
     114,     0,     0,   311,     0,    59,    60,     0,    61,     0,
       0,     0,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   315,   224,     0,     0,   285,   320,     0,     0,
       0,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,     0,     0,     0,     0,     0,     0,     0,   336,
     337,     0,   340,     0,     0,     0,   114,     0,   114,   114,
     343,     0,     0,     0,    16,    70,     0,     0,     0,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,     0,     0,
       0,   114,   114,     0,     0,     0,     0,   267,   268,     0,
       0,   271,   272,   273,   274,   275,   276,   375,     0,     0,
     378,     0,     0,   381,     0,     0,     0,   311,     0,   384,
     385,   386,   387,   280,   281,   282,   283,   284,  -207,  -207,
       0,  -207,     0,     0,     0,  -207,     0,     0,     0,    41,
       0,     0,   393,     0,   394,     0,  -207,    42,     0,  -207,
      43,    44,    45,     0,    46,    47,    48,    49,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     397,    61,   399,   401,     0,     6,    62,    63,    64,    65,
       0,     0,     0,     0,    38,    66,    67,  -207,  -207,     0,
       0,     0,     0,     0,    68,    69,  -208,  -208,   423,  -208,
       0,     0,     0,  -208,     0,  -209,  -209,     0,  -209,     0,
       0,     0,  -209,     0,  -208,     0,     0,  -208,     0,     0,
       0,    41,     0,  -209,     0,   443,  -209,    16,    70,    42,
       0,   448,    43,    44,    45,     0,    46,    47,    48,    49,
       0,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     0,    61,     0,  -208,  -208,     6,    62,    63,
      64,    65,     0,     0,  -209,  -209,    38,   212,    67,     0,
       0,     0,     0,     0,     0,     0,    68,    69,     0,     0,
       0,     0,  -210,  -210,     0,  -210,     0,     0,     0,  -210,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -210,   117,     0,  -210,     0,     0,     0,     0,    42,    16,
      70,    43,    44,    45,     0,    46,    47,    48,    49,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,     0,    61,     0,     0,     0,     6,    62,    63,    64,
      65,  -210,  -210,     0,     0,    38,     0,    67,     0,     0,
       0,     0,     0,     0,     0,    68,    69,     0,     0,     0,
       0,    59,    60,     0,    61,     0,     0,     0,     6,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   224,
     244,     0,   225,     0,     0,     0,     0,    42,    16,    70,
      43,    44,    45,     0,    46,    47,    48,    49,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
       0,    61,   120,     0,     0,     6,    62,    63,    64,    65,
      16,    70,     0,     0,    38,     0,    67,     0,     0,     0,
       0,     0,     0,     0,    68,    69,    59,    60,   121,    61,
     122,   123,   124,     6,    62,    63,    64,    65,   125,   126,
     127,     0,     0,     0,   128,     0,     0,     0,   129,     0,
     188,     0,     0,     0,     0,     0,     0,    16,    70,     0,
       0,     0,     0,     0,   130,   131,     0,   120,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   132,     0,     0,   133,    16,    70,    29,   134,   135,
     136,    59,    60,   121,    61,   122,   123,   124,     6,    62,
      63,    64,    65,   125,   126,   127,   382,     0,     0,   249,
     250,     0,   266,   129,     0,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,     0,     0,     0,     0,   130,
     131,     0,   120,     0,     0,     0,     0,     0,   277,   278,
     279,   280,   281,   282,   283,   284,   132,     0,     0,   133,
      16,    70,    29,   134,   135,   136,    59,    60,   121,    61,
     122,   123,   124,     6,    62,    63,    64,    65,   125,   126,
     127,   388,     0,     0,   128,     0,     0,   266,   129,     0,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
       0,     0,     0,     0,   130,   131,     0,   120,     0,     0,
       0,     0,     0,   277,   278,   279,   280,   281,   282,   283,
     284,   132,     0,     0,   133,    16,    70,    29,   134,   135,
     136,    59,    60,   121,    61,   122,   123,   124,     6,    62,
      63,    64,    65,   125,   126,   127,   406,     0,     0,   249,
       0,     0,   266,   129,     0,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,     0,     0,     0,     0,   130,
     131,     0,     0,     0,     0,     0,     0,     0,   277,   278,
     279,   280,   281,   282,   283,   284,   132,     0,     0,   133,
      16,    70,    29,   134,   135,   136,    42,     0,     0,    43,
      44,    45,     0,    46,    47,    48,    49,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     0,
      61,     0,     0,     0,     6,    62,    63,    64,    65,     0,
       0,     0,     0,    38,     0,    67,     0,     0,     0,     0,
       0,     0,   338,    68,    69,     0,     0,   339,     0,     0,
       0,     0,   266,     0,     0,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    70,   277,   278,
     279,   280,   281,   282,   283,   284,   415,     0,     0,     0,
       0,   416,     0,     0,     0,     0,   266,     0,     0,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   277,   278,   279,   280,   281,   282,   283,   284,
     417,     0,     0,     0,     0,   418,     0,     0,     0,     0,
     266,     0,     0,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   277,   278,   279,   280,
     281,   282,   283,   284,   419,     0,     0,     0,     0,   420,
       0,     0,     0,     0,   266,     0,     0,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   366,     0,
     277,   278,   279,   280,   281,   282,   283,   284,   266,     0,
       0,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   368,     0,   277,   278,   279,   280,   281,   282,
     283,   284,   266,     0,     0,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   372,     0,   277,   278,
     279,   280,   281,   282,   283,   284,   266,     0,     0,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     391,     0,   277,   278,   279,   280,   281,   282,   283,   284,
     266,     0,     0,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   392,     0,   277,   278,   279,   280,
     281,   282,   283,   284,   266,     0,     0,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   338,     0,
     277,   278,   279,   280,   281,   282,   283,   284,   266,     0,
       0,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   414,     0,   277,   278,   279,   280,   281,   282,
     283,   284,   266,     0,     0,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   425,     0,   277,   278,
     279,   280,   281,   282,   283,   284,   266,     0,     0,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     427,     0,   277,   278,   279,   280,   281,   282,   283,   284,
     266,     0,     0,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   458,     0,   277,   278,   279,   280,
     281,   282,   283,   284,   266,     0,     0,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   460,     0,
     277,   278,   279,   280,   281,   282,   283,   284,   266,     0,
       0,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   277,   278,   279,   280,   281,   282,
     283,   284,   409,     0,     0,     0,     0,     0,   266,     0,
       0,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   277,   278,   279,   280,   281,   282,
     283,   284,   412,     0,     0,     0,     0,     0,   266,     0,
       0,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   277,   278,   279,   280,   281,   282,
     283,   284,   422,     0,     0,     0,     0,   266,     0,     0,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   277,   278,   279,   280,   281,   282,   283,
     284,   395,     0,   266,     0,     0,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   277,
     278,   279,   280,   281,   282,   283,   284,   265,   266,     0,
       0,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   277,   278,   279,   280,   281,   282,
     283,   284,   300,   266,     0,     0,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   266,     0,     0,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,     0,     0,     0,
       0,     0,   277,   278,   279,   280,   281,   282,   283,   284,
     267,   268,     0,   270,   271,   272,   273,   274,   275,   276,
     267,   268,     0,     0,   271,   272,   273,   274,   275,   276,
       0,     0,     0,   277,   278,   279,   280,   281,   282,   283,
     284,     0,     0,   277,   278,   279,   280,   281,   282,   283,
     284,   267,   268,     0,     0,   271,   272,   273,   274,   275,
     276,   267,   268,     0,     0,   271,   272,   273,   274,   275,
     276,     0,     0,     0,     0,   278,   279,   280,   281,   282,
     283,   284,     0,     0,     0,   278,     0,   280,   281,   282,
     283,   284
  };

  const short
  parser::yycheck_[] =
  {
       0,    35,   128,   179,    54,   179,    20,   179,   110,     9,
      47,    54,    47,    30,    64,     3,     4,    47,    96,    97,
      98,    58,    95,    58,    47,    25,    38,    54,   101,    41,
       0,   104,    59,    60,    46,    41,    36,    51,    38,    55,
      46,    41,    55,    60,    60,   110,    46,    60,    99,   100,
      38,    54,   154,    41,    64,    67,    68,    69,    46,    59,
      60,    73,    99,   100,    99,   100,    97,    67,    68,    69,
     100,    59,    60,    73,    64,    40,    41,   100,    43,    67,
      68,    69,    47,    55,    55,    73,    55,    55,    60,   154,
     101,    60,    60,    58,    55,    38,    61,    64,    41,    60,
      56,   191,   192,    46,   100,   207,    55,   119,   210,   211,
     110,    60,    64,   119,    59,    60,    55,    59,    60,   119,
     132,    60,   110,   249,    67,    68,    69,    59,    60,   129,
      73,   119,   132,    38,    99,   100,    41,    63,    55,    54,
      54,    46,   207,    60,   132,   210,   211,    58,    55,    62,
      80,    55,   242,    60,   154,    54,    60,    38,    54,    54,
      41,    64,    67,    68,    69,    46,   154,   179,    73,   100,
      55,    64,    64,    55,    38,    60,   119,    41,    60,   179,
     180,    54,    46,    54,    64,    64,    67,    68,    69,   132,
      64,   179,    73,   295,    64,    64,    11,    12,    13,    14,
      15,    54,    62,    67,    68,    69,    54,   207,    54,    73,
     210,   211,    55,    62,   119,   305,    27,   104,   308,   207,
      58,    63,   210,   211,    63,    54,    62,   132,    58,    54,
     295,    62,    47,    54,    58,    58,   179,    54,   119,   100,
      54,    54,    60,   243,    94,    95,    96,    97,    98,    59,
     426,   132,   426,    38,   426,   119,    41,    64,    54,    64,
      54,    46,    64,    64,    54,    54,    59,    25,   132,    40,
      41,    30,    43,    64,   179,    59,    47,    48,    49,    50,
      51,    59,    67,    68,    69,   100,   286,    58,    73,    59,
     416,    54,   418,    55,   420,   295,    64,    64,   179,    64,
     390,   313,    38,    64,    64,    41,   306,   295,    55,   309,
      46,    54,    54,   313,    54,   179,    55,    55,   408,    64,
      64,   411,    68,    69,     9,   313,     9,    64,    99,   100,
       9,    67,    68,    69,   119,   426,   313,    73,   372,    73,
     132,    51,    -1,    -1,   434,    -1,    -1,   132,    94,    95,
      96,    97,    98,    -1,   366,    -1,   368,    -1,    -1,   449,
     366,   451,   368,   453,    -1,    -1,   366,    -1,   368,    -1,
     313,   371,    -1,    -1,    38,    -1,    -1,    41,   366,    -1,
     368,    -1,    46,   119,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,   179,    43,   132,    -1,    -1,    47,
      -1,    -1,    -1,    67,    68,    69,    54,    -1,   313,    73,
      58,    -1,   424,    61,   426,   427,    -1,    -1,   424,    -1,
      -1,   427,    -1,   366,   424,   368,   426,   427,    -1,    -1,
      -1,    -1,   313,    -1,    -1,    -1,   424,    -1,   426,   427,
      -1,    -1,    -1,   179,    -1,    -1,    -1,   459,   460,   313,
      -1,    99,   100,   459,   460,   119,    -1,    -1,    -1,   459,
     460,   366,    -1,   368,    -1,    -1,    -1,    -1,   132,    -1,
      38,   459,   460,    41,    -1,    -1,    -1,    -1,    46,    -1,
      -1,   424,    -1,   426,   427,   366,    -1,   368,    40,    41,
      -1,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    67,
      68,    69,   366,    -1,   368,    73,    58,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    -1,   179,   459,   460,    -1,   424,
      -1,   426,   427,    -1,    -1,    -1,    40,    41,   313,    43,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    -1,    -1,
      54,    -1,    -1,   424,    58,   426,   427,    99,   100,    -1,
      -1,   119,    -1,    -1,   459,   460,    -1,    -1,    -1,    -1,
     424,    -1,   426,   427,   132,    -1,    40,    41,    -1,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,   313,   459,   460,
      -1,   366,    -1,   368,    58,    99,   100,    61,    -1,   103,
     104,    40,    41,    -1,    43,   459,   460,    -1,    47,    48,
      49,    50,    51,    -1,    -1,    40,    41,    -1,    43,    58,
      -1,   179,    47,    48,    49,    50,    51,    66,    67,    -1,
      -1,    -1,    -1,    58,    -1,    99,   100,    68,    69,    -1,
     366,    -1,   368,    74,    75,    76,    77,    -1,    -1,   424,
      -1,   426,   427,    17,    18,    42,    20,    21,    -1,   313,
      99,   100,    -1,    94,    95,    96,    97,    98,    55,    -1,
      -1,    -1,    -1,    -1,    99,   100,    40,    41,    -1,    43,
      -1,    -1,    -1,    47,   459,   460,    -1,    -1,    40,    41,
      -1,    43,    -1,    -1,    58,    47,    -1,    61,   424,    -1,
     426,   427,    66,    67,    -1,    -1,    58,    -1,    -1,    61,
      -1,    -1,   366,    -1,   368,    -1,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,   459,   460,    99,   100,    -1,    40,    41,
     127,    43,    -1,   130,   131,    47,    -1,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,   313,    58,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,
     424,    -1,   426,   427,    -1,    -1,    -1,    -1,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,   176,
      -1,   178,    -1,    -1,   181,    -1,    -1,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,   459,   460,    -1,   366,    -1,
     368,    -1,    -1,   200,    -1,    40,    41,    -1,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   219,    58,    -1,    -1,    61,   224,    -1,    -1,
      -1,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   246,
     247,    -1,   249,    -1,    -1,    -1,   424,    -1,   426,   427,
     257,    -1,    -1,    -1,    99,   100,    -1,    -1,    -1,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,    -1,    -1,
      -1,   459,   460,    -1,    -1,    -1,    -1,    68,    69,    -1,
      -1,    72,    73,    74,    75,    76,    77,   304,    -1,    -1,
     307,    -1,    -1,   310,    -1,    -1,    -1,   314,    -1,   316,
     317,   318,   319,    94,    95,    96,    97,    98,    40,    41,
      -1,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    11,
      -1,    -1,   339,    -1,   341,    -1,    58,    19,    -1,    61,
      22,    23,    24,    -1,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
     367,    43,   369,   370,    -1,    47,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    56,    57,    58,    99,   100,    -1,
      -1,    -1,    -1,    -1,    66,    67,    40,    41,   395,    43,
      -1,    -1,    -1,    47,    -1,    40,    41,    -1,    43,    -1,
      -1,    -1,    47,    -1,    58,    -1,    -1,    61,    -1,    -1,
      -1,    11,    -1,    58,    -1,   422,    61,    99,   100,    19,
      -1,   428,    22,    23,    24,    -1,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    -1,    99,   100,    47,    48,    49,
      50,    51,    -1,    -1,    99,   100,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    -1,    -1,
      -1,    -1,    40,    41,    -1,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    12,    -1,    61,    -1,    -1,    -1,    -1,    19,    99,
     100,    22,    23,    24,    -1,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    99,   100,    -1,    -1,    56,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,
      -1,    40,    41,    -1,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      12,    -1,    61,    -1,    -1,    -1,    -1,    19,    99,   100,
      22,    23,    24,    -1,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,    16,    -1,    -1,    47,    48,    49,    50,    51,
      99,   100,    -1,    -1,    56,    -1,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,    -1,
      -1,    -1,    -1,    -1,    78,    79,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    59,    -1,    -1,    58,
      59,    -1,    65,    62,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    78,
      79,    -1,    16,    -1,    -1,    -1,    -1,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    59,    -1,    -1,    58,    -1,    -1,    65,    62,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    -1,    -1,    78,    79,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    59,    -1,    -1,    58,
      -1,    -1,    65,    62,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    78,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,
      93,    94,    95,    96,    97,    98,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,    19,    -1,    -1,    22,
      23,    24,    -1,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      43,    -1,    -1,    -1,    47,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    56,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    66,    67,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    99,   100,    91,    92,
      93,    94,    95,    96,    97,    98,    55,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      55,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    91,    92,    93,    94,
      95,    96,    97,    98,    55,    -1,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    60,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    63,    -1,    65,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      92,    93,    94,    95,    96,    97,    98,    64,    65,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    64,    65,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    65,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,    91,    92,    93,    94,    95,    96,    97,    98,
      68,    69,    -1,    71,    72,    73,    74,    75,    76,    77,
      68,    69,    -1,    -1,    72,    73,    74,    75,    76,    77,
      -1,    -1,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    -1,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    68,    69,    -1,    -1,    72,    73,    74,    75,    76,
      77,    68,    69,    -1,    -1,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    92,    93,    94,    95,    96,
      97,    98,    -1,    -1,    -1,    92,    -1,    94,    95,    96,
      97,    98
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    11,    12,    13,    14,    15,    47,   100,   116,   117,
     118,   119,   120,   121,   122,   194,    99,   100,   195,   195,
      54,     0,   118,   119,   120,    54,    97,    64,    64,   101,
     197,   170,   194,   100,    55,    55,    60,    64,    56,   128,
     194,    11,    19,    22,    23,    24,    26,    27,    28,    29,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    43,    48,    49,    50,    51,    57,    58,    66,    67,
     100,   123,   124,   126,   127,   128,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     156,   157,   158,   165,   166,   167,   168,   176,   179,   180,
     183,   187,   188,   189,   190,   194,   195,    12,   123,   125,
      16,    42,    44,    45,    46,    52,    53,    54,    58,    62,
      78,    79,    95,    98,   102,   103,   104,   154,   159,   160,
     161,   162,   163,   164,   165,   166,   169,   173,   174,   175,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   194,   195,   196,   197,   198,   199,
     200,   201,   202,    64,    54,    64,    54,   123,    54,    54,
      54,    54,    95,   197,   200,    63,    64,    64,    64,   154,
      64,    54,    54,    58,   194,   195,    58,   194,   195,    58,
      58,   165,   166,   177,   178,   179,   180,   183,   194,    58,
     183,   183,    57,   124,    64,    64,    64,    64,    64,    80,
      17,    18,    20,    21,    58,    61,    66,    67,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,   167,
     168,   194,    54,    62,    12,   123,    54,    54,   154,    58,
      59,   154,   171,   172,   194,   154,   154,    54,   103,   104,
     179,   180,   182,   194,   100,    64,    65,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    91,    92,    93,
      94,    95,    96,    97,    98,    61,    62,    55,   154,    27,
     154,   129,   156,   157,   158,   183,   194,   154,    63,    63,
      64,   171,   172,   171,    58,    54,    62,    58,    54,    62,
      58,   154,    59,    60,    58,   154,    54,    54,    54,    54,
     154,   100,   193,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   171,   194,   154,   154,    55,    60,
     154,    60,    59,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,    47,   194,    64,    55,    54,    55,    64,
      30,    60,    55,    55,    55,   154,   171,   194,   154,   171,
     194,   154,    59,   178,   154,   154,   154,   154,    59,    55,
      54,    55,    55,   154,   154,    63,   123,   154,   123,   154,
     155,   154,   194,   128,    64,    64,    59,    55,    54,    59,
      55,    54,    59,    59,    55,    55,    60,    55,    60,    55,
      60,   171,    60,   154,    25,    55,    64,    55,    30,    59,
     171,    59,   171,    59,    54,    64,    64,   172,    64,   172,
      64,   172,    55,   154,   123,    64,   129,   123,   154,    54,
      55,    54,    55,    54,   171,    55,    55,    55,    55,    55,
      55,   171,   171,   171,    55,    64,    64,    64,   123,   123,
      55,    55,    55
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,   115,   116,   116,   117,   117,   117,   117,   117,   117,
     118,   119,   120,   120,   120,   120,   121,   122,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   128,   129,   129,   129,   129,   130,   130,   131,
     131,   131,   132,   133,   133,   134,   135,   135,   136,   136,
     137,   138,   138,   139,   140,   141,   142,   143,   144,   144,
     145,   146,   146,   147,   148,   149,   150,   150,   151,   152,
     153,   154,   154,   154,   155,   155,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   157,   157,
     158,   158,   159,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   162,   163,   163,   163,   163,   164,   165,   165,   166,
     166,   167,   167,   167,   167,   167,   167,   168,   168,   168,
     168,   169,   170,   170,   170,   171,   171,   172,   172,   173,
     174,   175,   175,   176,   177,   177,   178,   178,   178,   179,
     180,   181,   182,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   194,   195,   195,   195,   196,   197,   198,
     199,   199,   200,   200,   201,   202
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     5,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     3,
       2,     3,     2,     1,     1,     1,     0,     2,     2,     2,
       2,     2,     6,     8,     6,     3,     8,     6,     8,     6,
       2,     2,     4,     5,     7,     5,     7,     9,     7,     9,
       5,     3,     3,     2,     2,     2,     3,     2,     2,     5,
       5,     1,     1,     1,     1,     0,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     5,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     1,     1,     2,
       2,     4,     6,     5,     7,     5,     7,     8,     9,     9,
       9,     3,     3,     1,     0,     1,     0,     3,     1,     4,
       4,     2,     3,     3,     3,     1,     1,     1,     1,     4,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     7,
       2,     1,     2,     1,     1,     1
  };




#if GSCDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   272,   272,   273,   277,   279,   281,   283,   285,   287,
     292,   296,   301,   302,   303,   304,   308,   313,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   346,   347,   351,   353,   358,   360,   365,
     366,   370,   371,   375,   377,   379,   382,   386,   388,   393,
     395,   397,   402,   407,   409,   414,   419,   421,   426,   428,
     433,   438,   440,   445,   450,   455,   460,   465,   470,   475,
     484,   491,   493,   498,   503,   508,   513,   515,   520,   525,
     530,   535,   536,   537,   541,   542,   546,   548,   550,   552,
     554,   556,   558,   560,   562,   564,   566,   568,   573,   575,
     580,   582,   587,   592,   594,   596,   598,   600,   602,   604,
     606,   608,   610,   612,   614,   616,   618,   620,   622,   624,
     626,   631,   632,   633,   634,   635,   636,   637,   638,   639,
     640,   641,   642,   643,   644,   645,   646,   647,   648,   649,
     650,   651,   652,   653,   654,   655,   656,   657,   658,   659,
     660,   664,   669,   671,   673,   675,   680,   685,   686,   689,
     690,   694,   696,   698,   700,   702,   704,   709,   711,   713,
     715,   720,   725,   727,   730,   734,   737,   741,   743,   748,
     753,   758,   760,   765,   772,   774,   779,   780,   781,   785,
     790,   795,   800,   805,   806,   807,   808,   809,   810,   811,
     812,   813,   817,   822,   827,   832,   837,   842,   847,   852,
     857,   862,   867,   869,   874,   876,   878,   883,   888,   893,
     898,   900,   905,   907,   912,   917
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
#line 4787 "parser.cpp"

#line 921 "parser.ypp"


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

} // namespace xsk::gsc
