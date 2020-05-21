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
xsk::gsc::iw6::parser::symbol_type IW6lex(yyscan_t yyscanner, xsk::gsc::location& loc);

#line 47 "parser.cpp"

// Take the name prefix into account.
#define yylex   IW6lex



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
#if IW6DEBUG

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

#else // !IW6DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !IW6DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace gsc { namespace iw6 {
#line 149 "parser.cpp"

  /// Build a parser object.
  parser::parser (yyscan_t yyscanner_yyarg, xsk::gsc::location& loc_yyarg, xsk::gsc::program_ptr& ast_yyarg)
#if IW6DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      yyscanner (yyscanner_yyarg),
      loc (loc_yyarg),
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
      case symbol_kind::S_anim: // anim
        value.YY_MOVE_OR_COPY< anim_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_animation: // animation
        value.YY_MOVE_OR_COPY< animation_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_animtree: // animtree
        value.YY_MOVE_OR_COPY< animtree_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.YY_MOVE_OR_COPY< constant_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_define: // define
        value.YY_MOVE_OR_COPY< define_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_empty_array: // empty_array
        value.YY_MOVE_OR_COPY< empty_array_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_filled: // expr_arguments_filled
      case symbol_kind::S_expr_arguments_empty: // expr_arguments_empty
        value.YY_MOVE_OR_COPY< expr_arguments_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.YY_MOVE_OR_COPY< expr_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_call_childthread: // expr_call_childthread
        value.YY_MOVE_OR_COPY< expr_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.YY_MOVE_OR_COPY< expr_call_type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_expr: // for_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_compare: // expr_compare
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.YY_MOVE_OR_COPY< expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_false: // false
        value.YY_MOVE_OR_COPY< false_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_file: // file
        value.YY_MOVE_OR_COPY< file_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_neg_float: // neg_float
      case symbol_kind::S_float: // float
        value.YY_MOVE_OR_COPY< float_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_game: // game
        value.YY_MOVE_OR_COPY< game_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.YY_MOVE_OR_COPY< include_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_neg_integer: // neg_integer
      case symbol_kind::S_integer: // integer
        value.YY_MOVE_OR_COPY< integer_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_istring: // istring
        value.YY_MOVE_OR_COPY< istring_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_level: // level
        value.YY_MOVE_OR_COPY< level_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.YY_MOVE_OR_COPY< name_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_object: // object
        value.YY_MOVE_OR_COPY< node_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
        value.YY_MOVE_OR_COPY< parameters_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< program_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_self: // self
        value.YY_MOVE_OR_COPY< self_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FILE: // "file path"
      case symbol_kind::S_NAME: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "int"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.YY_MOVE_OR_COPY< stmt_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.YY_MOVE_OR_COPY< stmt_break_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.YY_MOVE_OR_COPY< stmt_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.YY_MOVE_OR_COPY< stmt_case_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.YY_MOVE_OR_COPY< stmt_continue_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.YY_MOVE_OR_COPY< stmt_default_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.YY_MOVE_OR_COPY< stmt_endon_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.YY_MOVE_OR_COPY< stmt_for_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.YY_MOVE_OR_COPY< stmt_foreach_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.YY_MOVE_OR_COPY< stmt_if_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.YY_MOVE_OR_COPY< stmt_ifelse_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< stmt_list_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.YY_MOVE_OR_COPY< stmt_notify_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_stmt: // for_stmt
        value.YY_MOVE_OR_COPY< stmt_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.YY_MOVE_OR_COPY< stmt_return_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.YY_MOVE_OR_COPY< stmt_switch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.YY_MOVE_OR_COPY< stmt_wait_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.YY_MOVE_OR_COPY< stmt_waittill_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.YY_MOVE_OR_COPY< stmt_waittillframeend_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.YY_MOVE_OR_COPY< stmt_waittillmatch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.YY_MOVE_OR_COPY< stmt_while_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string: // string
        value.YY_MOVE_OR_COPY< string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_thisthread: // thisthread
        value.YY_MOVE_OR_COPY< thisthread_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_thread: // thread
        value.YY_MOVE_OR_COPY< thread_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_true: // true
        value.YY_MOVE_OR_COPY< true_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_undefined: // undefined
        value.YY_MOVE_OR_COPY< undefined_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_usingtree: // usingtree
        value.YY_MOVE_OR_COPY< usingtree_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vector: // vector
        value.YY_MOVE_OR_COPY< vector_ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_anim: // anim
        value.move< anim_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_animation: // animation
        value.move< animation_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_animtree: // animtree
        value.move< animtree_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.move< constant_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_define: // define
        value.move< define_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_empty_array: // empty_array
        value.move< empty_array_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_filled: // expr_arguments_filled
      case symbol_kind::S_expr_arguments_empty: // expr_arguments_empty
        value.move< expr_arguments_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< expr_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_call_childthread: // expr_call_childthread
        value.move< expr_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.move< expr_call_type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_expr: // for_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_compare: // expr_compare
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.move< expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_false: // false
        value.move< false_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_file: // file
        value.move< file_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_neg_float: // neg_float
      case symbol_kind::S_float: // float
        value.move< float_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_game: // game
        value.move< game_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.move< include_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_neg_integer: // neg_integer
      case symbol_kind::S_integer: // integer
        value.move< integer_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_istring: // istring
        value.move< istring_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_level: // level
        value.move< level_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.move< name_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_object: // object
        value.move< node_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
        value.move< parameters_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< program_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_self: // self
        value.move< self_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FILE: // "file path"
      case symbol_kind::S_NAME: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "int"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< stmt_break_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< stmt_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< stmt_case_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< stmt_continue_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< stmt_default_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< stmt_endon_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< stmt_for_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< stmt_foreach_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< stmt_if_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< stmt_ifelse_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< stmt_list_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< stmt_notify_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_stmt: // for_stmt
        value.move< stmt_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< stmt_return_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< stmt_switch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< stmt_wait_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< stmt_waittill_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< stmt_waittillframeend_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< stmt_waittillmatch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< stmt_while_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string: // string
        value.move< string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_thisthread: // thisthread
        value.move< thisthread_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_thread: // thread
        value.move< thread_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_true: // true
        value.move< true_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_undefined: // undefined
        value.move< undefined_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_usingtree: // usingtree
        value.move< usingtree_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vector: // vector
        value.move< vector_ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_anim: // anim
        value.copy< anim_ptr > (that.value);
        break;

      case symbol_kind::S_animation: // animation
        value.copy< animation_ptr > (that.value);
        break;

      case symbol_kind::S_animtree: // animtree
        value.copy< animtree_ptr > (that.value);
        break;

      case symbol_kind::S_constant: // constant
        value.copy< constant_ptr > (that.value);
        break;

      case symbol_kind::S_define: // define
        value.copy< define_ptr > (that.value);
        break;

      case symbol_kind::S_empty_array: // empty_array
        value.copy< empty_array_ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_filled: // expr_arguments_filled
      case symbol_kind::S_expr_arguments_empty: // expr_arguments_empty
        value.copy< expr_arguments_ptr > (that.value);
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.copy< expr_assign_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_call_childthread: // expr_call_childthread
        value.copy< expr_call_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.copy< expr_call_type_ptr > (that.value);
        break;

      case symbol_kind::S_for_expr: // for_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_compare: // expr_compare
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.copy< expr_ptr > (that.value);
        break;

      case symbol_kind::S_false: // false
        value.copy< false_ptr > (that.value);
        break;

      case symbol_kind::S_file: // file
        value.copy< file_ptr > (that.value);
        break;

      case symbol_kind::S_neg_float: // neg_float
      case symbol_kind::S_float: // float
        value.copy< float_ptr > (that.value);
        break;

      case symbol_kind::S_game: // game
        value.copy< game_ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.copy< include_ptr > (that.value);
        break;

      case symbol_kind::S_neg_integer: // neg_integer
      case symbol_kind::S_integer: // integer
        value.copy< integer_ptr > (that.value);
        break;

      case symbol_kind::S_istring: // istring
        value.copy< istring_ptr > (that.value);
        break;

      case symbol_kind::S_level: // level
        value.copy< level_ptr > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.copy< name_ptr > (that.value);
        break;

      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_object: // object
        value.copy< node_ptr > (that.value);
        break;

      case symbol_kind::S_parameters: // parameters
        value.copy< parameters_ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< program_ptr > (that.value);
        break;

      case symbol_kind::S_self: // self
        value.copy< self_ptr > (that.value);
        break;

      case symbol_kind::S_FILE: // "file path"
      case symbol_kind::S_NAME: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "int"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.copy< stmt_assign_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.copy< stmt_break_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.copy< stmt_call_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.copy< stmt_case_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.copy< stmt_continue_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.copy< stmt_default_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.copy< stmt_endon_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.copy< stmt_for_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.copy< stmt_foreach_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.copy< stmt_if_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.copy< stmt_ifelse_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< stmt_list_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.copy< stmt_notify_ptr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_stmt: // for_stmt
        value.copy< stmt_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.copy< stmt_return_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.copy< stmt_switch_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.copy< stmt_wait_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.copy< stmt_waittill_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.copy< stmt_waittillframeend_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.copy< stmt_waittillmatch_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.copy< stmt_while_ptr > (that.value);
        break;

      case symbol_kind::S_string: // string
        value.copy< string_ptr > (that.value);
        break;

      case symbol_kind::S_thisthread: // thisthread
        value.copy< thisthread_ptr > (that.value);
        break;

      case symbol_kind::S_thread: // thread
        value.copy< thread_ptr > (that.value);
        break;

      case symbol_kind::S_true: // true
        value.copy< true_ptr > (that.value);
        break;

      case symbol_kind::S_undefined: // undefined
        value.copy< undefined_ptr > (that.value);
        break;

      case symbol_kind::S_usingtree: // usingtree
        value.copy< usingtree_ptr > (that.value);
        break;

      case symbol_kind::S_vector: // vector
        value.copy< vector_ptr > (that.value);
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
      case symbol_kind::S_anim: // anim
        value.move< anim_ptr > (that.value);
        break;

      case symbol_kind::S_animation: // animation
        value.move< animation_ptr > (that.value);
        break;

      case symbol_kind::S_animtree: // animtree
        value.move< animtree_ptr > (that.value);
        break;

      case symbol_kind::S_constant: // constant
        value.move< constant_ptr > (that.value);
        break;

      case symbol_kind::S_define: // define
        value.move< define_ptr > (that.value);
        break;

      case symbol_kind::S_empty_array: // empty_array
        value.move< empty_array_ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_filled: // expr_arguments_filled
      case symbol_kind::S_expr_arguments_empty: // expr_arguments_empty
        value.move< expr_arguments_ptr > (that.value);
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< expr_assign_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_call_childthread: // expr_call_childthread
        value.move< expr_call_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.move< expr_call_type_ptr > (that.value);
        break;

      case symbol_kind::S_for_expr: // for_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_compare: // expr_compare
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.move< expr_ptr > (that.value);
        break;

      case symbol_kind::S_false: // false
        value.move< false_ptr > (that.value);
        break;

      case symbol_kind::S_file: // file
        value.move< file_ptr > (that.value);
        break;

      case symbol_kind::S_neg_float: // neg_float
      case symbol_kind::S_float: // float
        value.move< float_ptr > (that.value);
        break;

      case symbol_kind::S_game: // game
        value.move< game_ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.move< include_ptr > (that.value);
        break;

      case symbol_kind::S_neg_integer: // neg_integer
      case symbol_kind::S_integer: // integer
        value.move< integer_ptr > (that.value);
        break;

      case symbol_kind::S_istring: // istring
        value.move< istring_ptr > (that.value);
        break;

      case symbol_kind::S_level: // level
        value.move< level_ptr > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.move< name_ptr > (that.value);
        break;

      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_object: // object
        value.move< node_ptr > (that.value);
        break;

      case symbol_kind::S_parameters: // parameters
        value.move< parameters_ptr > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< program_ptr > (that.value);
        break;

      case symbol_kind::S_self: // self
        value.move< self_ptr > (that.value);
        break;

      case symbol_kind::S_FILE: // "file path"
      case symbol_kind::S_NAME: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "int"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_assign_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< stmt_break_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< stmt_call_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< stmt_case_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< stmt_continue_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< stmt_default_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< stmt_endon_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< stmt_for_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< stmt_foreach_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< stmt_if_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< stmt_ifelse_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< stmt_list_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< stmt_notify_ptr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_stmt: // for_stmt
        value.move< stmt_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< stmt_return_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< stmt_switch_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< stmt_wait_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< stmt_waittill_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< stmt_waittillframeend_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< stmt_waittillmatch_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< stmt_while_ptr > (that.value);
        break;

      case symbol_kind::S_string: // string
        value.move< string_ptr > (that.value);
        break;

      case symbol_kind::S_thisthread: // thisthread
        value.move< thisthread_ptr > (that.value);
        break;

      case symbol_kind::S_thread: // thread
        value.move< thread_ptr > (that.value);
        break;

      case symbol_kind::S_true: // true
        value.move< true_ptr > (that.value);
        break;

      case symbol_kind::S_undefined: // undefined
        value.move< undefined_ptr > (that.value);
        break;

      case symbol_kind::S_usingtree: // usingtree
        value.move< usingtree_ptr > (that.value);
        break;

      case symbol_kind::S_vector: // vector
        value.move< vector_ptr > (that.value);
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

#if IW6DEBUG
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

#if IW6DEBUG
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
#endif // IW6DEBUG

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
            symbol_type yylookahead (yylex (yyscanner, loc));
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
      case symbol_kind::S_anim: // anim
        yylhs.value.emplace< anim_ptr > ();
        break;

      case symbol_kind::S_animation: // animation
        yylhs.value.emplace< animation_ptr > ();
        break;

      case symbol_kind::S_animtree: // animtree
        yylhs.value.emplace< animtree_ptr > ();
        break;

      case symbol_kind::S_constant: // constant
        yylhs.value.emplace< constant_ptr > ();
        break;

      case symbol_kind::S_define: // define
        yylhs.value.emplace< define_ptr > ();
        break;

      case symbol_kind::S_empty_array: // empty_array
        yylhs.value.emplace< empty_array_ptr > ();
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
      case symbol_kind::S_expr_arguments_filled: // expr_arguments_filled
      case symbol_kind::S_expr_arguments_empty: // expr_arguments_empty
        yylhs.value.emplace< expr_arguments_ptr > ();
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        yylhs.value.emplace< expr_assign_ptr > ();
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_call_childthread: // expr_call_childthread
        yylhs.value.emplace< expr_call_ptr > ();
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        yylhs.value.emplace< expr_call_type_ptr > ();
        break;

      case symbol_kind::S_for_expr: // for_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_compare: // expr_compare
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        yylhs.value.emplace< expr_ptr > ();
        break;

      case symbol_kind::S_false: // false
        yylhs.value.emplace< false_ptr > ();
        break;

      case symbol_kind::S_file: // file
        yylhs.value.emplace< file_ptr > ();
        break;

      case symbol_kind::S_neg_float: // neg_float
      case symbol_kind::S_float: // float
        yylhs.value.emplace< float_ptr > ();
        break;

      case symbol_kind::S_game: // game
        yylhs.value.emplace< game_ptr > ();
        break;

      case symbol_kind::S_include: // include
        yylhs.value.emplace< include_ptr > ();
        break;

      case symbol_kind::S_neg_integer: // neg_integer
      case symbol_kind::S_integer: // integer
        yylhs.value.emplace< integer_ptr > ();
        break;

      case symbol_kind::S_istring: // istring
        yylhs.value.emplace< istring_ptr > ();
        break;

      case symbol_kind::S_level: // level
        yylhs.value.emplace< level_ptr > ();
        break;

      case symbol_kind::S_name: // name
        yylhs.value.emplace< name_ptr > ();
        break;

      case symbol_kind::S_expr_function: // expr_function
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_object: // object
        yylhs.value.emplace< node_ptr > ();
        break;

      case symbol_kind::S_parameters: // parameters
        yylhs.value.emplace< parameters_ptr > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< program_ptr > ();
        break;

      case symbol_kind::S_self: // self
        yylhs.value.emplace< self_ptr > ();
        break;

      case symbol_kind::S_FILE: // "file path"
      case symbol_kind::S_NAME: // "identifier"
      case symbol_kind::S_STRING: // "string literal"
      case symbol_kind::S_ISTRING: // "localized string"
      case symbol_kind::S_FLOAT: // "float"
      case symbol_kind::S_INTEGER: // "int"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        yylhs.value.emplace< stmt_assign_ptr > ();
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        yylhs.value.emplace< stmt_break_ptr > ();
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        yylhs.value.emplace< stmt_call_ptr > ();
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        yylhs.value.emplace< stmt_case_ptr > ();
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        yylhs.value.emplace< stmt_continue_ptr > ();
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        yylhs.value.emplace< stmt_default_ptr > ();
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        yylhs.value.emplace< stmt_endon_ptr > ();
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        yylhs.value.emplace< stmt_for_ptr > ();
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        yylhs.value.emplace< stmt_foreach_ptr > ();
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        yylhs.value.emplace< stmt_if_ptr > ();
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        yylhs.value.emplace< stmt_ifelse_ptr > ();
        break;

      case symbol_kind::S_stmt_block: // stmt_block
      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< stmt_list_ptr > ();
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        yylhs.value.emplace< stmt_notify_ptr > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_stmt: // for_stmt
        yylhs.value.emplace< stmt_ptr > ();
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        yylhs.value.emplace< stmt_return_ptr > ();
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        yylhs.value.emplace< stmt_switch_ptr > ();
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        yylhs.value.emplace< stmt_wait_ptr > ();
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        yylhs.value.emplace< stmt_waittill_ptr > ();
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        yylhs.value.emplace< stmt_waittillframeend_ptr > ();
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        yylhs.value.emplace< stmt_waittillmatch_ptr > ();
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        yylhs.value.emplace< stmt_while_ptr > ();
        break;

      case symbol_kind::S_string: // string
        yylhs.value.emplace< string_ptr > ();
        break;

      case symbol_kind::S_thisthread: // thisthread
        yylhs.value.emplace< thisthread_ptr > ();
        break;

      case symbol_kind::S_thread: // thread
        yylhs.value.emplace< thread_ptr > ();
        break;

      case symbol_kind::S_true: // true
        yylhs.value.emplace< true_ptr > ();
        break;

      case symbol_kind::S_undefined: // undefined
        yylhs.value.emplace< undefined_ptr > ();
        break;

      case symbol_kind::S_usingtree: // usingtree
        yylhs.value.emplace< usingtree_ptr > ();
        break;

      case symbol_kind::S_vector: // vector
        yylhs.value.emplace< vector_ptr > ();
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
#line 231 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program_ptr > ()); }
#line 1731 "parser.cpp"
    break;

  case 3: // root: %empty
#line 232 "parser.ypp"
              { ast = std::make_unique<node_program>(yylhs.location); }
#line 1737 "parser.cpp"
    break;

  case 4: // program: program include
#line 237 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::move(yystack_[1].value.as < program_ptr > ()); yylhs.value.as < program_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1743 "parser.cpp"
    break;

  case 5: // program: program define
#line 239 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::move(yystack_[1].value.as < program_ptr > ()); yylhs.value.as < program_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < define_ptr > ())); }
#line 1749 "parser.cpp"
    break;

  case 6: // program: include
#line 241 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::make_unique<node_program>(yylhs.location); yylhs.value.as < program_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1755 "parser.cpp"
    break;

  case 7: // program: define
#line 243 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::make_unique<node_program>(yylhs.location); yylhs.value.as < program_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < define_ptr > ())); }
#line 1761 "parser.cpp"
    break;

  case 8: // include: "#include" file ";"
#line 248 "parser.ypp"
        { yylhs.value.as < include_ptr > () = std::make_unique<node_include>(yylhs.location, std::move(yystack_[1].value.as < file_ptr > ())); }
#line 1767 "parser.cpp"
    break;

  case 9: // define: usingtree
#line 252 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_usingtree = std::move(yystack_[0].value.as < usingtree_ptr > ()); }
#line 1773 "parser.cpp"
    break;

  case 10: // define: constant
#line 253 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_constant = std::move(yystack_[0].value.as < constant_ptr > ()); }
#line 1779 "parser.cpp"
    break;

  case 11: // define: thread
#line 254 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_thread = std::move(yystack_[0].value.as < thread_ptr > ()); }
#line 1785 "parser.cpp"
    break;

  case 12: // usingtree: "#using_animtree" "(" string ")" ";"
#line 259 "parser.ypp"
        { yylhs.value.as < usingtree_ptr > () = std::make_unique<node_usingtree>(yylhs.location, std::move(yystack_[2].value.as < string_ptr > ())); }
#line 1791 "parser.cpp"
    break;

  case 13: // constant: name "=" expr ";"
#line 264 "parser.ypp"
        { yylhs.value.as < constant_ptr > () = std::make_unique<node_constant>(yylhs.location, std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 1797 "parser.cpp"
    break;

  case 14: // thread: name "(" parameters ")" stmt_block
#line 269 "parser.ypp"
        { yylhs.value.as < thread_ptr > () = std::make_unique<node_thread>(yylhs.location, std::move(yystack_[4].value.as < name_ptr > ()), std::move(yystack_[2].value.as < parameters_ptr > ()), std::move(yystack_[0].value.as < stmt_list_ptr > ())); }
#line 1803 "parser.cpp"
    break;

  case 15: // parameters: parameters "," name
#line 274 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::move(yystack_[2].value.as < parameters_ptr > ()); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < name_ptr > ())); }
#line 1809 "parser.cpp"
    break;

  case 16: // parameters: name
#line 276 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(yylhs.location); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < name_ptr > ())); }
#line 1815 "parser.cpp"
    break;

  case 17: // parameters: %empty
#line 278 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(yylhs.location); }
#line 1821 "parser.cpp"
    break;

  case 18: // stmt: stmt_block
#line 282 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_list = std::move(yystack_[0].value.as < stmt_list_ptr > ()); }
#line 1827 "parser.cpp"
    break;

  case 19: // stmt: stmt_call
#line 283 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_call = std::move(yystack_[0].value.as < stmt_call_ptr > ()); }
#line 1833 "parser.cpp"
    break;

  case 20: // stmt: stmt_assign
#line 284 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < stmt_assign_ptr > ()); }
#line 1839 "parser.cpp"
    break;

  case 21: // stmt: stmt_endon
#line 285 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < stmt_endon_ptr > ()); }
#line 1845 "parser.cpp"
    break;

  case 22: // stmt: stmt_notify
#line 286 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < stmt_notify_ptr > ()); }
#line 1851 "parser.cpp"
    break;

  case 23: // stmt: stmt_wait
#line 287 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < stmt_wait_ptr > ()); }
#line 1857 "parser.cpp"
    break;

  case 24: // stmt: stmt_waittill
#line 288 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < stmt_waittill_ptr > ()); }
#line 1863 "parser.cpp"
    break;

  case 25: // stmt: stmt_waittillmatch
#line 289 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < stmt_waittillmatch_ptr > ()); }
#line 1869 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittillframeend
#line 290 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < stmt_waittillframeend_ptr > ()); }
#line 1875 "parser.cpp"
    break;

  case 27: // stmt: stmt_if
#line 291 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_if = std::move(yystack_[0].value.as < stmt_if_ptr > ()); }
#line 1881 "parser.cpp"
    break;

  case 28: // stmt: stmt_ifelse
#line 292 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < stmt_ifelse_ptr > ()); }
#line 1887 "parser.cpp"
    break;

  case 29: // stmt: stmt_while
#line 293 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_while = std::move(yystack_[0].value.as < stmt_while_ptr > ()); }
#line 1893 "parser.cpp"
    break;

  case 30: // stmt: stmt_for
#line 294 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_for = std::move(yystack_[0].value.as < stmt_for_ptr > ()); }
#line 1899 "parser.cpp"
    break;

  case 31: // stmt: stmt_foreach
#line 295 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < stmt_foreach_ptr > ()); }
#line 1905 "parser.cpp"
    break;

  case 32: // stmt: stmt_switch
#line 296 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < stmt_switch_ptr > ()); }
#line 1911 "parser.cpp"
    break;

  case 33: // stmt: stmt_case
#line 297 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_case = std::move(yystack_[0].value.as < stmt_case_ptr > ()); }
#line 1917 "parser.cpp"
    break;

  case 34: // stmt: stmt_default
#line 298 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_default = std::move(yystack_[0].value.as < stmt_default_ptr > ()); }
#line 1923 "parser.cpp"
    break;

  case 35: // stmt: stmt_break
#line 299 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_break = std::move(yystack_[0].value.as < stmt_break_ptr > ()); }
#line 1929 "parser.cpp"
    break;

  case 36: // stmt: stmt_continue
#line 300 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < stmt_continue_ptr > ()); }
#line 1935 "parser.cpp"
    break;

  case 37: // stmt: stmt_return
#line 301 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_return = std::move(yystack_[0].value.as < stmt_return_ptr > ()); }
#line 1941 "parser.cpp"
    break;

  case 38: // stmt_block: "{" stmt_list "}"
#line 305 "parser.ypp"
                              { yylhs.value.as < stmt_list_ptr > () = std::move(yystack_[1].value.as < stmt_list_ptr > ()); }
#line 1947 "parser.cpp"
    break;

  case 39: // stmt_block: "{" "}"
#line 306 "parser.ypp"
                    { yylhs.value.as < stmt_list_ptr > () = std::make_unique<node_stmt_list>(yylhs.location); }
#line 1953 "parser.cpp"
    break;

  case 40: // stmt_list: stmt_list stmt
#line 311 "parser.ypp"
        { yylhs.value.as < stmt_list_ptr > () = std::move(yystack_[1].value.as < stmt_list_ptr > ()); yylhs.value.as < stmt_list_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 1959 "parser.cpp"
    break;

  case 41: // stmt_list: stmt
#line 313 "parser.ypp"
        { yylhs.value.as < stmt_list_ptr > () = std::make_unique<node_stmt_list>(yylhs.location); yylhs.value.as < stmt_list_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 1965 "parser.cpp"
    break;

  case 42: // stmt_call: expr_call ";"
#line 318 "parser.ypp"
        { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(yylhs.location, std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 1971 "parser.cpp"
    break;

  case 43: // stmt_call: expr_call_thread ";"
#line 320 "parser.ypp"
        { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(yylhs.location, std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 1977 "parser.cpp"
    break;

  case 44: // stmt_assign: expr_assign ";"
#line 325 "parser.ypp"
        { yylhs.value.as < stmt_assign_ptr > () = std::make_unique<node_stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < expr_assign_ptr > ())); }
#line 1983 "parser.cpp"
    break;

  case 45: // stmt_endon: object "endon" "(" expr ")" ";"
#line 330 "parser.ypp"
        { yylhs.value.as < stmt_endon_ptr > () = std::make_unique<node_stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ())); }
#line 1989 "parser.cpp"
    break;

  case 46: // stmt_notify: object "notify" "(" expr "," expr_arguments ")" ";"
#line 335 "parser.ypp"
        { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 1995 "parser.cpp"
    break;

  case 47: // stmt_notify: object "notify" "(" expr ")" ";"
#line 337 "parser.ypp"
        { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2001 "parser.cpp"
    break;

  case 48: // stmt_wait: "wait" expr ";"
#line 342 "parser.ypp"
        { yylhs.value.as < stmt_wait_ptr > () = std::make_unique<node_stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2007 "parser.cpp"
    break;

  case 49: // stmt_waittill: object "waittill" "(" expr "," expr_arguments ")" ";"
#line 347 "parser.ypp"
        { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2013 "parser.cpp"
    break;

  case 50: // stmt_waittill: object "waittill" "(" expr ")" ";"
#line 349 "parser.ypp"
        { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2019 "parser.cpp"
    break;

  case 51: // stmt_waittillmatch: object "waittillmatch" "(" expr "," expr_arguments ")" ";"
#line 354 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2025 "parser.cpp"
    break;

  case 52: // stmt_waittillmatch: object "waittillmatch" "(" expr ")" ";"
#line 356 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2031 "parser.cpp"
    break;

  case 53: // stmt_waittillframeend: "waittillframeend" ";"
#line 361 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend_ptr > () = std::make_unique<node_stmt_waittillframeend>(yylhs.location); }
#line 2037 "parser.cpp"
    break;

  case 54: // stmt_if: "if" "(" expr ")" stmt
#line 366 "parser.ypp"
        { yylhs.value.as < stmt_if_ptr > () = std::make_unique<node_stmt_if>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2043 "parser.cpp"
    break;

  case 55: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 371 "parser.ypp"
        { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2049 "parser.cpp"
    break;

  case 56: // stmt_while: "while" "(" expr ")" stmt
#line 376 "parser.ypp"
        { yylhs.value.as < stmt_while_ptr > () = std::make_unique<node_stmt_while>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2055 "parser.cpp"
    break;

  case 57: // stmt_for: "for" "(" for_stmt ";" for_expr ";" for_stmt ")" stmt
#line 381 "parser.ypp"
        { yylhs.value.as < stmt_for_ptr > () = std::make_unique<node_stmt_for>(yylhs.location, std::move(yystack_[6].value.as < stmt_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2061 "parser.cpp"
    break;

  case 58: // stmt_foreach: "foreach" "(" name "in" expr ")" stmt
#line 386 "parser.ypp"
        { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(yylhs.location, expr_ptr(std::move(yystack_[4].value.as < name_ptr > ())), std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2067 "parser.cpp"
    break;

  case 59: // stmt_foreach: "foreach" "(" name "," name "in" expr ")" stmt
#line 388 "parser.ypp"
        { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(yylhs.location, expr_ptr(std::move(yystack_[6].value.as < name_ptr > ())), expr_ptr(std::move(yystack_[4].value.as < name_ptr > ())), std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2073 "parser.cpp"
    break;

  case 60: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 393 "parser.ypp"
        { yylhs.value.as < stmt_switch_ptr > () = std::make_unique<node_stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_list_ptr > ())); }
#line 2079 "parser.cpp"
    break;

  case 61: // stmt_case: "case" integer ":"
#line 398 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < integer_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2085 "parser.cpp"
    break;

  case 62: // stmt_case: "case" neg_integer ":"
#line 400 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < integer_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2091 "parser.cpp"
    break;

  case 63: // stmt_case: "case" string ":"
#line 402 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < string_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2097 "parser.cpp"
    break;

  case 64: // stmt_default: "default" ":"
#line 407 "parser.ypp"
        { yylhs.value.as < stmt_default_ptr > () = std::make_unique<node_stmt_default>(yylhs.location, std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2103 "parser.cpp"
    break;

  case 65: // stmt_break: "break" ";"
#line 412 "parser.ypp"
        { yylhs.value.as < stmt_break_ptr > () = std::make_unique<node_stmt_break>(yylhs.location); }
#line 2109 "parser.cpp"
    break;

  case 66: // stmt_continue: "continue" ";"
#line 417 "parser.ypp"
        { yylhs.value.as < stmt_continue_ptr > () = std::make_unique<node_stmt_continue>(yylhs.location); }
#line 2115 "parser.cpp"
    break;

  case 67: // stmt_return: "return" expr ";"
#line 422 "parser.ypp"
        { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(yylhs.location, std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2121 "parser.cpp"
    break;

  case 68: // stmt_return: "return" ";"
#line 424 "parser.ypp"
        { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(yylhs.location, std::make_unique<node>(yylhs.location)); }
#line 2127 "parser.cpp"
    break;

  case 69: // for_stmt: expr_assign
#line 428 "parser.ypp"
                                        { yylhs.value.as < stmt_ptr > ().as_list = std::make_unique<node_stmt_list>(yylhs.location); yylhs.value.as < stmt_ptr > ().as_list->stmts.push_back(stmt_ptr(std::make_unique<node_stmt_assign>(yylhs.location, std::move(yystack_[0].value.as < expr_assign_ptr > ())))); }
#line 2133 "parser.cpp"
    break;

  case 70: // for_stmt: %empty
#line 429 "parser.ypp"
                                        { yylhs.value.as < stmt_ptr > ().as_node = std::make_unique<node>(yylhs.location); }
#line 2139 "parser.cpp"
    break;

  case 71: // for_expr: expr
#line 433 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2145 "parser.cpp"
    break;

  case 72: // for_expr: %empty
#line 434 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node>(yylhs.location); }
#line 2151 "parser.cpp"
    break;

  case 73: // expr: expr_compare
#line 438 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2157 "parser.cpp"
    break;

  case 74: // expr: expr_binary
#line 439 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2163 "parser.cpp"
    break;

  case 75: // expr: expr_primitive
#line 440 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2169 "parser.cpp"
    break;

  case 76: // expr_assign: "++" object
#line 444 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_increment>(yylhs.location, std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2175 "parser.cpp"
    break;

  case 77: // expr_assign: "--" object
#line 445 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2181 "parser.cpp"
    break;

  case 78: // expr_assign: object "++"
#line 446 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_increment>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2187 "parser.cpp"
    break;

  case 79: // expr_assign: object "--"
#line 447 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2193 "parser.cpp"
    break;

  case 80: // expr_assign: object "=" expr
#line 448 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2199 "parser.cpp"
    break;

  case 81: // expr_assign: object "|=" expr
#line 449 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2205 "parser.cpp"
    break;

  case 82: // expr_assign: object "&=" expr
#line 450 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2211 "parser.cpp"
    break;

  case 83: // expr_assign: object "^=" expr
#line 451 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2217 "parser.cpp"
    break;

  case 84: // expr_assign: object "<<=" expr
#line 452 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()),std::move( yystack_[0].value.as < expr_ptr > ())); }
#line 2223 "parser.cpp"
    break;

  case 85: // expr_assign: object ">>=" expr
#line 453 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2229 "parser.cpp"
    break;

  case 86: // expr_assign: object "+=" expr
#line 454 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2235 "parser.cpp"
    break;

  case 87: // expr_assign: object "-=" expr
#line 455 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2241 "parser.cpp"
    break;

  case 88: // expr_assign: object "*=" expr
#line 456 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mult>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2247 "parser.cpp"
    break;

  case 89: // expr_assign: object "/=" expr
#line 457 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2253 "parser.cpp"
    break;

  case 90: // expr_assign: object "%=" expr
#line 458 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2259 "parser.cpp"
    break;

  case 91: // expr_compare: expr "||" expr
#line 462 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_or>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2265 "parser.cpp"
    break;

  case 92: // expr_compare: expr "&&" expr
#line 463 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_and>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2271 "parser.cpp"
    break;

  case 93: // expr_compare: expr "==" expr
#line 464 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_equality>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2277 "parser.cpp"
    break;

  case 94: // expr_compare: expr "!=" expr
#line 465 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2283 "parser.cpp"
    break;

  case 95: // expr_compare: expr "<=" expr
#line 466 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2289 "parser.cpp"
    break;

  case 96: // expr_compare: expr ">=" expr
#line 467 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2295 "parser.cpp"
    break;

  case 97: // expr_compare: expr "<" expr
#line 468 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_less>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2301 "parser.cpp"
    break;

  case 98: // expr_compare: expr ">" expr
#line 469 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_greater>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2307 "parser.cpp"
    break;

  case 99: // expr_binary: expr "|" expr
#line 473 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2313 "parser.cpp"
    break;

  case 100: // expr_binary: expr "&" expr
#line 474 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2319 "parser.cpp"
    break;

  case 101: // expr_binary: expr "^" expr
#line 475 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2325 "parser.cpp"
    break;

  case 102: // expr_binary: expr "<<" expr
#line 476 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2331 "parser.cpp"
    break;

  case 103: // expr_binary: expr ">>" expr
#line 477 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2337 "parser.cpp"
    break;

  case 104: // expr_binary: expr "+" expr
#line 478 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_add>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2343 "parser.cpp"
    break;

  case 105: // expr_binary: expr "-" expr
#line 479 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_sub>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2349 "parser.cpp"
    break;

  case 106: // expr_binary: expr "*" expr
#line 480 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_mult>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2355 "parser.cpp"
    break;

  case 107: // expr_binary: expr "/" expr
#line 481 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_div>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2361 "parser.cpp"
    break;

  case 108: // expr_binary: expr "%" expr
#line 482 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_mod>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2367 "parser.cpp"
    break;

  case 109: // expr_primitive: "(" expr ")"
#line 486 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2373 "parser.cpp"
    break;

  case 110: // expr_primitive: "~" expr
#line 487 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_complement>(yylhs.location, std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2379 "parser.cpp"
    break;

  case 111: // expr_primitive: "!" expr
#line 488 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_not>(yylhs.location, std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2385 "parser.cpp"
    break;

  case 112: // expr_primitive: expr_call
#line 489 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2391 "parser.cpp"
    break;

  case 113: // expr_primitive: expr_call_thread
#line 490 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2397 "parser.cpp"
    break;

  case 114: // expr_primitive: expr_call_childthread
#line 491 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2403 "parser.cpp"
    break;

  case 115: // expr_primitive: expr_function
#line 492 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2409 "parser.cpp"
    break;

  case 116: // expr_primitive: expr_add_array
#line 493 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2415 "parser.cpp"
    break;

  case 117: // expr_primitive: expr_array
#line 494 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2421 "parser.cpp"
    break;

  case 118: // expr_primitive: expr_field
#line 495 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2427 "parser.cpp"
    break;

  case 119: // expr_primitive: expr_size
#line 496 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2433 "parser.cpp"
    break;

  case 120: // expr_primitive: thisthread
#line 497 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < thisthread_ptr > ()); }
#line 2439 "parser.cpp"
    break;

  case 121: // expr_primitive: empty_array
#line 498 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < empty_array_ptr > ()); }
#line 2445 "parser.cpp"
    break;

  case 122: // expr_primitive: undefined
#line 499 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < undefined_ptr > ()); }
#line 2451 "parser.cpp"
    break;

  case 123: // expr_primitive: game
#line 500 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < game_ptr > ()); }
#line 2457 "parser.cpp"
    break;

  case 124: // expr_primitive: self
#line 501 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < self_ptr > ()); }
#line 2463 "parser.cpp"
    break;

  case 125: // expr_primitive: anim
#line 502 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < anim_ptr > ()); }
#line 2469 "parser.cpp"
    break;

  case 126: // expr_primitive: level
#line 503 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < level_ptr > ()); }
#line 2475 "parser.cpp"
    break;

  case 127: // expr_primitive: animation
#line 504 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < animation_ptr > ()); }
#line 2481 "parser.cpp"
    break;

  case 128: // expr_primitive: animtree
#line 505 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < animtree_ptr > ()); }
#line 2487 "parser.cpp"
    break;

  case 129: // expr_primitive: name
#line 506 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < name_ptr > ()); }
#line 2493 "parser.cpp"
    break;

  case 130: // expr_primitive: istring
#line 507 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < istring_ptr > ()); }
#line 2499 "parser.cpp"
    break;

  case 131: // expr_primitive: string
#line 508 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < string_ptr > ()); }
#line 2505 "parser.cpp"
    break;

  case 132: // expr_primitive: vector
#line 509 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < vector_ptr > ()); }
#line 2511 "parser.cpp"
    break;

  case 133: // expr_primitive: neg_float
#line 510 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2517 "parser.cpp"
    break;

  case 134: // expr_primitive: neg_integer
#line 511 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2523 "parser.cpp"
    break;

  case 135: // expr_primitive: float
#line 512 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2529 "parser.cpp"
    break;

  case 136: // expr_primitive: integer
#line 513 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2535 "parser.cpp"
    break;

  case 137: // expr_primitive: false
#line 514 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < false_ptr > ()); }
#line 2541 "parser.cpp"
    break;

  case 138: // expr_primitive: true
#line 515 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < true_ptr > ()); }
#line 2547 "parser.cpp"
    break;

  case 139: // expr_call: expr_call_function
#line 519 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2553 "parser.cpp"
    break;

  case 140: // expr_call: expr_call_pointer
#line 520 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2559 "parser.cpp"
    break;

  case 141: // expr_call: object expr_call_function
#line 521 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2565 "parser.cpp"
    break;

  case 142: // expr_call: object expr_call_pointer
#line 522 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2571 "parser.cpp"
    break;

  case 143: // expr_call_thread: "thread" expr_call_function
#line 526 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2577 "parser.cpp"
    break;

  case 144: // expr_call_thread: "thread" expr_call_pointer
#line 527 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2583 "parser.cpp"
    break;

  case 145: // expr_call_thread: object "thread" expr_call_function
#line 528 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2589 "parser.cpp"
    break;

  case 146: // expr_call_thread: object "thread" expr_call_pointer
#line 529 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2595 "parser.cpp"
    break;

  case 147: // expr_call_childthread: "childthread" expr_call_function
#line 533 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2601 "parser.cpp"
    break;

  case 148: // expr_call_childthread: "childthread" expr_call_pointer
#line 534 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2607 "parser.cpp"
    break;

  case 149: // expr_call_childthread: object "childthread" expr_call_function
#line 535 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2613 "parser.cpp"
    break;

  case 150: // expr_call_childthread: object "childthread" expr_call_pointer
#line 536 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2619 "parser.cpp"
    break;

  case 151: // expr_call_function: name "(" expr_arguments ")"
#line 541 "parser.ypp"
        {yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(yylhs.location, std::make_unique<node_file>(), std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2625 "parser.cpp"
    break;

  case 152: // expr_call_function: file "::" name "(" expr_arguments ")"
#line 543 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(yylhs.location, std::move(yystack_[5].value.as < file_ptr > ()), std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2631 "parser.cpp"
    break;

  case 153: // expr_call_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 548 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_call_pointer>(yylhs.location, false, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2637 "parser.cpp"
    break;

  case 154: // expr_call_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 550 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_call_pointer>(yylhs.location, true, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2643 "parser.cpp"
    break;

  case 155: // expr_arguments: expr_arguments_filled
#line 554 "parser.ypp"
                            { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[0].value.as < expr_arguments_ptr > ()); }
#line 2649 "parser.cpp"
    break;

  case 156: // expr_arguments: expr_arguments_empty
#line 555 "parser.ypp"
                            { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[0].value.as < expr_arguments_ptr > ()); }
#line 2655 "parser.cpp"
    break;

  case 157: // expr_arguments_filled: expr_arguments "," expr
#line 560 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[2].value.as < expr_arguments_ptr > ()); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2661 "parser.cpp"
    break;

  case 158: // expr_arguments_filled: expr
#line 562 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(yylhs.location); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2667 "parser.cpp"
    break;

  case 159: // expr_arguments_empty: %empty
#line 567 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(yylhs.location); }
#line 2673 "parser.cpp"
    break;

  case 160: // expr_function: "::" name
#line 572 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function>(yylhs.location, std::make_unique<node_file>(yylhs.location), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2679 "parser.cpp"
    break;

  case 161: // expr_function: file "::" name
#line 574 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function>(yylhs.location, std::move(yystack_[2].value.as < file_ptr > ()), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2685 "parser.cpp"
    break;

  case 162: // expr_add_array: "[" expr_arguments_filled "]"
#line 579 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2691 "parser.cpp"
    break;

  case 163: // expr_array: object "[" expr "]"
#line 584 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_array>(yylhs.location, std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2697 "parser.cpp"
    break;

  case 164: // expr_field: object "." name
#line 589 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_field>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2703 "parser.cpp"
    break;

  case 165: // expr_size: object "." "size"
#line 594 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_size>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ())); }
#line 2709 "parser.cpp"
    break;

  case 166: // object: expr_call
#line 598 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2715 "parser.cpp"
    break;

  case 167: // object: expr_array
#line 599 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2721 "parser.cpp"
    break;

  case 168: // object: expr_field
#line 600 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2727 "parser.cpp"
    break;

  case 169: // object: game
#line 601 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < game_ptr > ()); }
#line 2733 "parser.cpp"
    break;

  case 170: // object: self
#line 602 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < self_ptr > ()); }
#line 2739 "parser.cpp"
    break;

  case 171: // object: anim
#line 603 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < anim_ptr > ()); }
#line 2745 "parser.cpp"
    break;

  case 172: // object: level
#line 604 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < level_ptr > ()); }
#line 2751 "parser.cpp"
    break;

  case 173: // object: name
#line 605 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < name_ptr > ()); }
#line 2757 "parser.cpp"
    break;

  case 174: // thisthread: "thisthread"
#line 608 "parser.ypp"
                                                       { yylhs.value.as < thisthread_ptr > () = std::make_unique<node_thisthread>(yylhs.location); }
#line 2763 "parser.cpp"
    break;

  case 175: // empty_array: "[" "]"
#line 609 "parser.ypp"
                                                       { yylhs.value.as < empty_array_ptr > () = std::make_unique<node_empty_array>(yylhs.location); }
#line 2769 "parser.cpp"
    break;

  case 176: // undefined: "undefined"
#line 610 "parser.ypp"
                                                       { yylhs.value.as < undefined_ptr > () = std::make_unique<node_undefined>(yylhs.location); }
#line 2775 "parser.cpp"
    break;

  case 177: // game: "game"
#line 611 "parser.ypp"
                                                       { yylhs.value.as < game_ptr > () = std::make_unique<node_game>(yylhs.location); }
#line 2781 "parser.cpp"
    break;

  case 178: // self: "self"
#line 612 "parser.ypp"
                                                       { yylhs.value.as < self_ptr > () = std::make_unique<node_self>(yylhs.location); }
#line 2787 "parser.cpp"
    break;

  case 179: // anim: "anim"
#line 613 "parser.ypp"
                                                       { yylhs.value.as < anim_ptr > () = std::make_unique<node_anim>(yylhs.location); }
#line 2793 "parser.cpp"
    break;

  case 180: // level: "level"
#line 614 "parser.ypp"
                                                       { yylhs.value.as < level_ptr > () = std::make_unique<node_level>(yylhs.location); }
#line 2799 "parser.cpp"
    break;

  case 181: // animation: "%" "identifier"
#line 615 "parser.ypp"
                                                       { yylhs.value.as < animation_ptr > () = std::make_unique<node_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2805 "parser.cpp"
    break;

  case 182: // animtree: "#animtree"
#line 616 "parser.ypp"
                                                       { yylhs.value.as < animtree_ptr > () = std::make_unique<node_animtree>(yylhs.location); }
#line 2811 "parser.cpp"
    break;

  case 183: // name: "identifier"
#line 617 "parser.ypp"
                                                       { yylhs.value.as < name_ptr > () = std::make_unique<node_name>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2817 "parser.cpp"
    break;

  case 184: // file: "file path"
#line 618 "parser.ypp"
                                                       { yylhs.value.as < file_ptr > () = std::make_unique<node_file>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2823 "parser.cpp"
    break;

  case 185: // istring: "localized string"
#line 619 "parser.ypp"
                                                       { yylhs.value.as < istring_ptr > () = std::make_unique<node_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2829 "parser.cpp"
    break;

  case 186: // string: "string literal"
#line 620 "parser.ypp"
                                                       { yylhs.value.as < string_ptr > () = std::make_unique<node_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2835 "parser.cpp"
    break;

  case 187: // vector: "(" expr "," expr "," expr ")"
#line 621 "parser.ypp"
                                                       { yylhs.value.as < vector_ptr > () = std::make_unique<node_vector>(yylhs.location, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[3].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2841 "parser.cpp"
    break;

  case 188: // neg_float: "-" "float"
#line 622 "parser.ypp"
                                                       { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 2847 "parser.cpp"
    break;

  case 189: // neg_integer: "-" "int"
#line 623 "parser.ypp"
                                                       { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 2853 "parser.cpp"
    break;

  case 190: // float: "float"
#line 624 "parser.ypp"
                                                       { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2859 "parser.cpp"
    break;

  case 191: // integer: "int"
#line 625 "parser.ypp"
                                                       { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2865 "parser.cpp"
    break;

  case 192: // false: "false"
#line 626 "parser.ypp"
                                                       { yylhs.value.as < false_ptr > () = std::make_unique<node_false>(yylhs.location); }
#line 2871 "parser.cpp"
    break;

  case 193: // true: "true"
#line 627 "parser.ypp"
                                                       { yylhs.value.as < true_ptr > () = std::make_unique<node_true>(yylhs.location); }
#line 2877 "parser.cpp"
    break;


#line 2881 "parser.cpp"

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
    "end of file", "error", "invalid token", "#include", "#using_animtree",
  "#animtree", "endon", "notify", "wait", "waittill", "waittillmatch",
  "waittillframeend", "if", "else", "while", "for", "foreach", "in",
  "switch", "case", "default", "break", "continue", "return", "thread",
  "childthread", "thisthread", "call", "true", "false", "undefined",
  "size", "game", "self", "anim", "level", "(", ")", "{", "}", "[", "]",
  ",", ".", "::", ":", ";", "++", "--", "<<", ">>", "||", "&&", "==", "!=",
  "<=", ">=", "<", ">", "!", "~", "=", "+=", "-=", "*=", "/=", "%=", "|=",
  "&=", "^=", ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/", "%",
  "file path", "identifier", "string literal", "localized string", "float",
  "int", "ADD_ARRAY", "THEN", "NEG", "ANIMREF", "PREINC", "PREDEC",
  "POSTINC", "POSTDEC", "$accept", "root", "program", "include", "define",
  "usingtree", "constant", "thread", "parameters", "stmt", "stmt_block",
  "stmt_list", "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify",
  "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_if", "stmt_ifelse", "stmt_while",
  "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case", "stmt_default",
  "stmt_break", "stmt_continue", "stmt_return", "for_stmt", "for_expr",
  "expr", "expr_assign", "expr_compare", "expr_binary", "expr_primitive",
  "expr_call", "expr_call_thread", "expr_call_childthread",
  "expr_call_function", "expr_call_pointer", "expr_arguments",
  "expr_arguments_filled", "expr_arguments_empty", "expr_function",
  "expr_add_array", "expr_array", "expr_field", "expr_size", "object",
  "thisthread", "empty_array", "undefined", "game", "self", "anim",
  "level", "animation", "animtree", "name", "file", "istring", "string",
  "vector", "neg_float", "neg_integer", "float", "integer", "false",
  "true", YY_NULLPTR
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

#if IW6DEBUG
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
#if IW6DEBUG
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
#if IW6DEBUG
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


  const short parser::yypact_ninf_ = -232;

  const short parser::yytable_ninf_ = -174;

  const short
  parser::yypact_[] =
  {
      -2,   -68,   -15,  -232,    42,    -2,  -232,  -232,  -232,  -232,
    -232,   -23,  -232,     7,   -35,  -232,  -232,  -232,   -24,   663,
    -232,  -232,    23,   -12,  -232,  -232,    -3,    -3,  -232,    28,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,   663,   539,   -24,
     663,   663,   -76,    -8,  -232,  -232,  -232,  1372,  -232,  -232,
    -232,    40,  -232,  -232,  -232,  -232,  -232,  -232,   251,   387,
    -232,   407,  -232,  -232,  -232,   416,   449,   474,   562,  -232,
    -232,    19,    25,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,    55,    78,   -24,    63,  -232,  -232,    59,    75,
    -232,  -232,    83,   975,   539,  -232,  1450,    87,    92,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,   663,   663,   663,
     663,   663,   663,   663,   663,   663,   663,   663,   663,   663,
     663,   663,   663,   663,   663,    -3,    -3,   725,    -9,  -232,
    -232,   663,   -24,  -232,   842,  -232,  -232,   663,   -24,   663,
    -232,   663,   659,   663,  -232,    66,    66,  1460,  1008,   535,
     535,   322,   322,   322,   322,  1051,  1491,  1501,    10,    10,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  1282,  -232,  -232,
      14,  -232,    88,   663,    89,   100,   101,   110,   111,   114,
     -62,   112,   113,   116,   601,  -232,   121,   121,  -232,  -232,
     880,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
     117,   136,   139,  -232,  -232,   771,  -232,  -232,  -232,  -232,
      59,   659,    88,  1321,  1359,   119,  1450,  -232,  -232,   663,
    1406,  -232,   663,   663,     1,   -24,   663,    73,   143,   144,
     152,  -232,  -232,  -232,  -232,  1419,  -232,    31,    31,  -232,
    -232,  -232,  -232,  -232,   170,   171,   173,   174,   -24,  -232,
    -232,   663,   663,   663,   663,   663,   663,   663,   663,   663,
     663,   663,   167,   663,   175,    33,  -232,  1114,  1147,   166,
    -232,   940,    12,  1157,  -232,  -232,  -232,  -232,   663,   663,
     663,   663,  1450,  1450,  1450,  1450,  1450,  1450,  1450,  1450,
    1450,  1450,  1450,   182,  1190,   663,  -232,   918,   918,   663,
     663,   -24,    78,  1200,  1018,  1061,  1104,   663,  -232,    48,
     209,  -232,   177,  1450,  1233,   207,  -232,   181,   192,   663,
     194,   663,   199,   663,    49,  -232,   918,     1,   918,   663,
    -232,  -232,    65,  -232,    76,  -232,    85,  -232,  -232,   191,
    -232,  1243,   200,   204,   211,   918,   918,  -232,  -232,  -232,
    -232,  -232
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,   183,     0,     2,     6,     7,     9,    10,
      11,     0,   184,     0,     0,     1,     4,     5,    17,     0,
       8,   186,     0,     0,    16,   182,     0,     0,   174,     0,
     193,   192,   176,   177,   178,   179,   180,     0,   159,     0,
       0,     0,     0,     0,   185,   190,   191,     0,    73,    74,
      75,   112,   113,   114,   139,   140,   115,   116,   117,   118,
     119,     0,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,     0,   130,   131,   132,   133,   134,   135,   136,
     137,   138,     0,     0,     0,     0,   143,   144,     0,     0,
     147,   148,     0,     0,   159,   175,   158,     0,   155,   156,
     160,   111,   110,   188,   189,   181,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   141,
     142,   159,     0,    12,     0,    14,    15,     0,     0,     0,
     109,     0,   158,     0,   162,   102,   103,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   104,   105,
     106,   107,   108,   145,   146,   149,   150,     0,   165,   164,
       0,   155,   161,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,     0,     0,    41,    18,
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
       0,   166,     0,   167,   168,     0,   169,   170,   171,   172,
     173,     0,     0,     0,     0,     0,   157,   163,   151,   159,
       0,    53,     0,     0,    70,     0,     0,     0,     0,     0,
       0,    64,    65,    66,    68,     0,   166,    76,    77,    38,
      40,    44,    42,    43,     0,     0,     0,     0,     0,    78,
      79,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,     0,     0,     0,
      69,     0,     0,     0,    63,    62,    61,    67,     0,     0,
       0,     0,    80,    86,    87,    88,    89,    90,    81,    82,
      83,    85,    84,     0,     0,   159,   152,     0,     0,    72,
       0,     0,     0,     0,     0,     0,     0,   159,   187,     0,
      54,    56,     0,    71,     0,     0,    60,     0,     0,   159,
       0,   159,     0,   159,     0,   153,     0,    70,     0,     0,
      45,    47,     0,    50,     0,    52,     0,   154,    55,     0,
      58,     0,     0,     0,     0,     0,     0,    46,    49,    51,
      57,    59
  };

  const short
  parser::yypgoto_[] =
  {
    -232,  -232,  -232,   224,   246,  -232,  -232,  -232,  -232,   -41,
     -79,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,   -77,  -232,    57,  -231,  -232,  -232,  -232,   -94,    69,
    -232,   -16,   -11,  -112,   -31,  -232,  -232,  -232,   -82,    82,
    -232,   115,  -232,  -232,  -232,   172,   183,   195,   205,  -232,
    -232,     0,     5,  -232,     3,  -232,  -232,    84,  -232,    91,
    -232,  -232
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,     8,     9,    10,    23,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   279,   322,    96,   210,    48,    49,    50,    51,    52,
      53,    54,    55,    97,   171,    99,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81
  };

  const short
  parser::yytable_[] =
  {
      11,     1,     2,   280,   135,    11,    13,    98,   103,   104,
      86,    90,    12,    18,   237,    87,    91,    22,    24,   170,
      21,    14,   168,    46,    29,    83,    88,    88,    29,   310,
      84,    89,    89,    33,    34,    35,    36,    85,    19,   100,
     211,    85,    15,  -173,  -173,   129,  -173,    21,   186,   187,
     130,   228,   213,    20,   311,   131,   143,     3,    29,  -173,
      82,    88,  -173,    98,  -166,  -166,    89,  -166,    92,   132,
     306,   127,     3,   105,   258,   143,    47,    12,     3,     3,
    -166,    12,     3,  -166,   136,   335,   347,   122,   123,   124,
     143,   143,   246,   246,    93,   131,   211,   101,   102,  -173,
    -173,   133,   352,   137,   213,   213,   280,   143,   213,   163,
     165,    12,     3,   353,   164,   166,   134,   275,   143,   138,
    -166,  -166,   354,   139,   229,    88,    88,   143,   169,   143,
      89,    89,   172,   144,   220,   231,   232,   233,   222,    89,
     246,   120,   121,   122,   123,   124,   234,   235,    29,   250,
     236,   142,   213,    33,    34,    35,    36,   241,   104,   242,
     274,    85,   243,   251,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   252,   238,   167,   253,   220,   220,   284,   285,
     220,    89,    89,   319,   221,    89,   223,   286,   224,   129,
     226,    12,     3,   212,   130,   334,   288,   289,   303,   290,
     291,   305,   309,   211,   211,    88,   214,   342,   317,   344,
      89,   346,   336,   337,   339,   213,   213,   340,   355,    16,
     230,   129,   129,   326,   220,   282,   130,   130,   341,    89,
     343,   245,   211,   246,   211,   345,   357,    88,    88,   215,
     358,    17,    89,    89,   213,   213,   213,   359,   169,   212,
     349,   211,   211,     0,   239,   129,   320,   321,   214,   214,
     130,   240,   214,   213,   213,  -167,  -167,     0,  -167,     0,
       0,    88,     0,     0,     0,     0,    89,     0,     0,   277,
     278,  -167,     0,   283,  -167,   348,     0,   350,     0,     0,
       0,   247,   248,     0,     0,   215,   216,   220,   220,     0,
       0,   325,    89,    89,   360,   361,   214,   217,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   218,
     304,  -167,  -167,     0,     0,     0,   220,   220,   220,   219,
       0,    89,    89,    89,     0,   313,   314,   315,   316,   281,
       0,     0,     0,     0,     0,   220,   220,     0,   216,   216,
      89,    89,   216,     0,     0,     0,   323,   324,     0,   217,
     217,   107,   108,   217,     0,     0,   212,   212,     0,     0,
       0,   218,   218,     0,     0,   218,     0,     0,     0,   214,
     214,   219,   219,     0,     0,   219,   351,   120,   121,   122,
     123,   124,     0,     0,     0,   212,   216,   212,     0,     0,
       0,  -168,  -168,     0,  -168,     0,     0,   217,   214,   214,
     214,     0,   215,   215,   212,   212,     0,  -168,     0,   218,
    -168,   125,   126,     0,    29,     0,     0,   214,   214,   219,
    -169,  -169,     0,  -169,     0,     0,     0,   127,     0,     0,
     128,   215,   281,   215,     0,     0,  -169,     0,     0,  -169,
       0,     0,     0,     0,     0,     0,     0,  -168,  -168,     0,
     215,   215,     0,  -170,  -170,     0,  -170,     0,     0,   216,
     216,     0,     0,     0,     0,     0,     0,    12,     3,  -170,
     217,   217,  -170,     0,     0,     0,  -169,  -169,  -171,  -171,
       0,  -171,   218,   218,     0,     0,     0,     0,   216,   216,
     216,     0,   219,   219,  -171,     0,     0,  -171,     0,   217,
     217,   217,     0,     0,     0,     0,     0,   216,   216,  -170,
    -170,   218,   218,   218,     0,     0,     0,     0,   217,   217,
       0,   219,   219,   219,    25,     0,     0,     0,     0,     0,
     218,   218,     0,     0,  -171,  -171,     0,     0,     0,     0,
     219,   219,     0,    26,    27,    28,    29,    30,    31,    32,
       0,    33,    34,    35,    36,    37,     0,     0,     0,    94,
      95,     0,     0,    39,   107,   108,  -172,  -172,     0,  -172,
     113,   114,   115,   116,     0,     0,     0,     0,    40,    41,
       0,     0,  -172,     0,     0,  -172,    25,     0,     0,     0,
     120,   121,   122,   123,   124,    42,     0,     0,    43,    12,
       3,    21,    44,    45,    46,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,    35,    36,    37,     0,     0,
       0,    38,  -172,  -172,     0,    39,     0,   244,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      40,    41,     0,     0,     0,     0,     0,     0,    25,     0,
       0,     0,     0,     0,     0,     0,     0,    42,     0,     0,
      43,    12,     3,    21,    44,    45,    46,    26,    27,    28,
      29,    30,    31,    32,     0,    33,    34,    35,    36,    37,
     225,     0,     0,    38,     0,     0,     0,    39,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,     0,     0,
       0,     0,    40,    41,     0,     0,     0,     0,     0,     0,
      25,   117,   118,   119,   120,   121,   122,   123,   124,    42,
       0,     0,    43,    12,     3,    21,    44,    45,    46,    26,
      27,    28,    29,    30,    31,    32,     0,    33,    34,    35,
      36,    37,     0,     0,     0,    94,     0,     0,     0,    39,
       0,     0,     0,     0,     0,     0,     0,   254,   255,     0,
     256,   257,     0,     0,    40,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   125,     0,     0,    29,     0,
       0,    42,     0,     0,    43,    12,     3,    21,    44,    45,
      46,   127,     0,     0,   258,     0,     0,     0,   259,   260,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,     0,     0,     0,     0,     0,     0,     0,
     173,    12,     3,   174,   175,     0,   176,   177,   178,     0,
     179,   180,   181,   182,   183,   184,    26,     0,     0,    29,
       0,     0,     0,     0,    33,    34,    35,    36,     0,     0,
     134,   185,    85,     0,     0,     0,     0,     0,   173,   186,
     187,   174,   175,     0,   176,   177,   178,     0,   179,   180,
     181,   182,   183,   184,    26,     0,     0,    29,     0,     0,
       0,     0,    33,    34,    35,    36,     0,     0,   134,   249,
      85,     0,    12,     3,     0,     0,   173,   186,   187,   174,
     175,     0,   176,   177,   178,     0,   179,   180,   181,   182,
     183,   184,    26,     0,     0,    29,     0,     0,     0,     0,
      33,    34,    35,    36,     0,     0,   134,     0,    85,     0,
      12,     3,     0,     0,     0,   186,   187,    29,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,     0,     0,   258,     0,     0,     0,   259,   260,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,     3,
       0,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   140,     0,     0,     0,     0,   141,     0,     0,
      12,     3,     0,     0,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   328,     0,   107,   108,     0,
     329,   111,   112,   113,   114,   115,   116,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,     0,     0,     0,
     117,   118,   119,   120,   121,   122,   123,   124,     0,     0,
     117,   118,   119,   120,   121,   122,   123,   124,   330,     0,
     107,   108,     0,   331,   111,   112,   113,   114,   115,   116,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,     0,     0,     0,   118,   119,   120,   121,   122,   123,
     124,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   332,     0,     0,     0,     0,   333,     0,     0,     0,
       0,   307,     0,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   308,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   312,     0,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   318,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   327,     0,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,     0,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     338,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     356,     0,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,     0,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   227,     0,     0,     0,     0,     0,     0,
       0,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,   119,   120,   121,   122,
     123,   124,   272,     0,     0,     0,     0,     0,     0,     0,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   273,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   106,     0,
       0,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,     0,
       0,     0,     0,     0,   117,   118,   119,   120,   121,   122,
     123,   124,   276,     0,     0,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   287,     0,     0,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   107,
     108,     0,   110,   111,   112,   113,   114,   115,   116,     0,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     107,   108,     0,     0,   111,   112,   113,   114,   115,   116,
     107,   108,     0,     0,   111,   112,   113,   114,   115,   116,
       0,     0,     0,     0,     0,   119,   120,   121,   122,   123,
     124,     0,     0,     0,     0,     0,   120,   121,   122,   123,
     124
  };

  const short
  parser::yycheck_[] =
  {
       0,     3,     4,   234,    83,     5,     1,    38,    84,    85,
      26,    27,    80,    36,    76,    26,    27,    14,    18,   131,
      82,    36,    31,    85,    27,    37,    26,    27,    27,    17,
      42,    26,    27,    32,    33,    34,    35,    40,    61,    39,
     134,    40,     0,    24,    25,    61,    27,    82,    47,    48,
      61,    37,   134,    46,    42,    36,    42,    81,    27,    40,
      37,    61,    43,    94,    24,    25,    61,    27,    40,    44,
      37,    40,    81,    81,    43,    42,    19,    80,    81,    81,
      40,    80,    81,    43,    84,    37,    37,    77,    78,    79,
      42,    42,   186,   187,    37,    36,   190,    40,    41,    80,
      81,    46,    37,    40,   186,   187,   337,    42,   190,   125,
     126,    80,    81,    37,   125,   126,    38,   229,    42,    44,
      80,    81,    37,    40,    36,   125,   126,    42,   128,    42,
     125,   126,   132,    41,   134,    46,    36,    36,   138,   134,
     234,    75,    76,    77,    78,    79,    36,    36,    27,   190,
      36,    94,   234,    32,    33,    34,    35,    45,    85,    46,
      41,    40,    46,    46,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,    46,   180,   127,    46,   186,   187,    45,    45,
     190,   186,   187,   305,   137,   190,   139,    45,   141,   215,
     143,    80,    81,   134,   215,   317,    36,    36,    41,    36,
      36,    36,    46,   307,   308,   215,   134,   329,    36,   331,
     215,   333,    13,    46,    17,   307,   308,    46,    37,     5,
     173,   247,   248,   312,   234,   235,   247,   248,    46,   234,
      46,   184,   336,   337,   338,    46,    46,   247,   248,   134,
      46,     5,   247,   248,   336,   337,   338,    46,   258,   190,
     337,   355,   356,    -1,   180,   281,   307,   308,   186,   187,
     281,   180,   190,   355,   356,    24,    25,    -1,    27,    -1,
      -1,   281,    -1,    -1,    -1,    -1,   281,    -1,    -1,   232,
     233,    40,    -1,   236,    43,   336,    -1,   338,    -1,    -1,
      -1,   186,   187,    -1,    -1,   190,   134,   307,   308,    -1,
      -1,   311,   307,   308,   355,   356,   234,   134,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   134,
     273,    80,    81,    -1,    -1,    -1,   336,   337,   338,   134,
      -1,   336,   337,   338,    -1,   288,   289,   290,   291,   234,
      -1,    -1,    -1,    -1,    -1,   355,   356,    -1,   186,   187,
     355,   356,   190,    -1,    -1,    -1,   309,   310,    -1,   186,
     187,    49,    50,   190,    -1,    -1,   307,   308,    -1,    -1,
      -1,   186,   187,    -1,    -1,   190,    -1,    -1,    -1,   307,
     308,   186,   187,    -1,    -1,   190,   339,    75,    76,    77,
      78,    79,    -1,    -1,    -1,   336,   234,   338,    -1,    -1,
      -1,    24,    25,    -1,    27,    -1,    -1,   234,   336,   337,
     338,    -1,   307,   308,   355,   356,    -1,    40,    -1,   234,
      43,    24,    25,    -1,    27,    -1,    -1,   355,   356,   234,
      24,    25,    -1,    27,    -1,    -1,    -1,    40,    -1,    -1,
      43,   336,   337,   338,    -1,    -1,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    -1,
     355,   356,    -1,    24,    25,    -1,    27,    -1,    -1,   307,
     308,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    40,
     307,   308,    43,    -1,    -1,    -1,    80,    81,    24,    25,
      -1,    27,   307,   308,    -1,    -1,    -1,    -1,   336,   337,
     338,    -1,   307,   308,    40,    -1,    -1,    43,    -1,   336,
     337,   338,    -1,    -1,    -1,    -1,    -1,   355,   356,    80,
      81,   336,   337,   338,    -1,    -1,    -1,    -1,   355,   356,
      -1,   336,   337,   338,     5,    -1,    -1,    -1,    -1,    -1,
     355,   356,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,
     355,   356,    -1,    24,    25,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      41,    -1,    -1,    44,    49,    50,    24,    25,    -1,    27,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    59,    60,
      -1,    -1,    40,    -1,    -1,    43,     5,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    76,    -1,    -1,    79,    80,
      81,    82,    83,    84,    85,    24,    25,    26,    27,    28,
      29,    30,    -1,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    40,    80,    81,    -1,    44,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      79,    80,    81,    82,    83,    84,    85,    24,    25,    26,
      27,    28,    29,    30,    -1,    32,    33,    34,    35,    36,
      41,    -1,    -1,    40,    -1,    -1,    -1,    44,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    72,    73,    74,    75,    76,    77,    78,    79,    76,
      -1,    -1,    79,    80,    81,    82,    83,    84,    85,    24,
      25,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    40,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,    -1,
       9,    10,    -1,    -1,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    27,    -1,
      -1,    76,    -1,    -1,    79,    80,    81,    82,    83,    84,
      85,    40,    -1,    -1,    43,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       8,    80,    81,    11,    12,    -1,    14,    15,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    -1,    -1,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,     8,    47,
      48,    11,    12,    -1,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    -1,    -1,    38,    39,
      40,    -1,    80,    81,    -1,    -1,     8,    47,    48,    11,
      12,    -1,    14,    15,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    -1,    -1,    38,    -1,    40,    -1,
      80,    81,    -1,    -1,    -1,    47,    48,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    43,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    37,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      80,    81,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    37,    -1,    49,    50,    -1,
      42,    53,    54,    55,    56,    57,    58,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    37,    -1,
      49,    50,    -1,    42,    53,    54,    55,    56,    57,    58,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,    78,
      79,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    37,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    37,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    37,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    37,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    37,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    37,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      37,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      37,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    49,
      50,    -1,    52,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    79,
      49,    50,    -1,    -1,    53,    54,    55,    56,    57,    58,
      49,    50,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      79,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,    81,    95,    96,    97,    98,    99,   100,
     101,   155,    80,   156,    36,     0,    97,    98,    36,    61,
      46,    82,   158,   102,   155,     5,    24,    25,    26,    27,
      28,    29,    30,    32,    33,    34,    35,    36,    40,    44,
      59,    60,    76,    79,    83,    84,    85,   127,   129,   130,
     131,   132,   133,   134,   135,   136,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,    37,    37,    42,    40,   135,   136,   155,   156,
     135,   136,    40,   127,    40,    41,   127,   137,   138,   139,
     155,   127,   127,    84,    85,    81,    46,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    72,    73,    74,
      75,    76,    77,    78,    79,    24,    25,    40,    43,   135,
     136,    36,    44,    46,    38,   104,   155,    40,    44,    40,
      37,    42,   127,    42,    41,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   135,   136,   135,   136,   127,    31,   155,
     137,   138,   155,     8,    11,    12,    14,    15,    16,    18,
      19,    20,    21,    22,    23,    39,    47,    48,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     128,   132,   133,   142,   143,   145,   149,   150,   151,   152,
     155,   127,   155,   127,   127,    41,   127,    41,    37,    36,
     127,    46,    36,    36,    36,    36,    36,    76,   158,   161,
     163,    45,    46,    46,    46,   127,   132,   145,   145,    39,
     103,    46,    46,    46,     6,     7,     9,    10,    43,    47,
      48,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    41,    42,    41,   137,    46,   127,   127,   125,
     128,   145,   155,   127,    45,    45,    45,    46,    36,    36,
      36,    36,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,    41,   127,    36,    37,    37,    37,    46,
      17,    42,    37,   127,   127,   127,   127,    36,    37,   137,
     103,   103,   126,   127,   127,   155,   104,    37,    37,    42,
      37,    42,    37,    42,   137,    37,    13,    46,    37,    17,
      46,    46,   137,    46,   137,    46,   137,    37,   103,   125,
     103,   127,    37,    37,    37,    37,    37,    46,    46,    46,
     103,   103
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    94,    95,    95,    96,    96,    96,    96,    97,    98,
      98,    98,    99,   100,   101,   102,   102,   102,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   104,   104,
     105,   105,   106,   106,   107,   108,   109,   109,   110,   111,
     111,   112,   112,   113,   114,   115,   116,   117,   118,   118,
     119,   120,   120,   120,   121,   122,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   127,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   129,   129,   129,   129,   129,   129,   129,   129,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   132,
     132,   132,   132,   133,   133,   133,   133,   134,   134,   134,
     134,   135,   135,   136,   136,   137,   137,   138,   138,   139,
     140,   140,   141,   142,   143,   144,   145,   145,   145,   145,
     145,   145,   145,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     1,     1,     3,     1,
       1,     1,     5,     4,     5,     3,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       2,     1,     2,     2,     2,     6,     8,     6,     3,     8,
       6,     8,     6,     2,     5,     7,     5,     9,     7,     9,
       5,     3,     3,     3,     2,     2,     2,     3,     2,     1,
       0,     1,     0,     1,     1,     1,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     3,     3,     2,     2,     3,
       3,     4,     6,     8,     9,     1,     1,     3,     1,     0,
       2,     3,     3,     4,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     7,     2,     2,
       1,     1,     1,     1
  };




#if IW6DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   231,   231,   232,   236,   238,   240,   242,   247,   252,
     253,   254,   258,   263,   268,   273,   275,   278,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   305,   306,
     310,   312,   317,   319,   324,   329,   334,   336,   341,   346,
     348,   353,   355,   360,   365,   370,   375,   380,   385,   387,
     392,   397,   399,   401,   406,   411,   416,   421,   423,   428,
     429,   433,   434,   438,   439,   440,   444,   445,   446,   447,
     448,   449,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   462,   463,   464,   465,   466,   467,   468,   469,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   508,   509,   510,   511,   512,   513,   514,   515,   519,
     520,   521,   522,   526,   527,   528,   529,   533,   534,   535,
     536,   540,   542,   547,   549,   554,   555,   559,   561,   567,
     571,   573,   578,   583,   588,   593,   598,   599,   600,   601,
     602,   603,   604,   605,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,   619,   620,   621,   622,   623,
     624,   625,   626,   627
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
#endif // IW6DEBUG


#line 13 "parser.ypp"
} } } // xsk::gsc::iw6
#line 3949 "parser.cpp"

#line 629 "parser.ypp"


void xsk::gsc::iw6::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
