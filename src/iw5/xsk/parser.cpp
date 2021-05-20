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
xsk::gsc::iw5::parser::symbol_type IW5lex(yyscan_t yyscanner, xsk::gsc::location& loc);

#line 47 "parser.cpp"

// Take the name prefix into account.
#define yylex   IW5lex



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
#if IW5DEBUG

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

#else // !IW5DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !IW5DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace gsc { namespace iw5 {
#line 149 "parser.cpp"

  /// Build a parser object.
  parser::parser (yyscan_t yyscanner_yyarg, xsk::gsc::location& loc_yyarg, xsk::gsc::program_ptr& ast_yyarg)
#if IW5DEBUG
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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.YY_MOVE_OR_COPY< stmt_breakpoint_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.YY_MOVE_OR_COPY< stmt_prof_begin_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.YY_MOVE_OR_COPY< stmt_prof_end_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.move< stmt_breakpoint_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.move< stmt_prof_begin_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.move< stmt_prof_end_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.copy< stmt_breakpoint_ptr > (that.value);
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

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.copy< stmt_prof_begin_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.copy< stmt_prof_end_ptr > (that.value);
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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        value.move< stmt_breakpoint_ptr > (that.value);
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

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        value.move< stmt_prof_begin_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        value.move< stmt_prof_end_ptr > (that.value);
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

#if IW5DEBUG
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

#if IW5DEBUG
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
#endif // IW5DEBUG

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

      case symbol_kind::S_stmt_breakpoint: // stmt_breakpoint
        yylhs.value.emplace< stmt_breakpoint_ptr > ();
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

      case symbol_kind::S_stmt_prof_begin: // stmt_prof_begin
        yylhs.value.emplace< stmt_prof_begin_ptr > ();
        break;

      case symbol_kind::S_stmt_prof_end: // stmt_prof_end
        yylhs.value.emplace< stmt_prof_end_ptr > ();
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
#line 237 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program_ptr > ()); }
#line 1791 "parser.cpp"
    break;

  case 3: // root: %empty
#line 238 "parser.ypp"
              { ast = std::make_unique<node_program>(yylhs.location); }
#line 1797 "parser.cpp"
    break;

  case 4: // program: program include
#line 243 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::move(yystack_[1].value.as < program_ptr > ()); yylhs.value.as < program_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1803 "parser.cpp"
    break;

  case 5: // program: program define
#line 245 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::move(yystack_[1].value.as < program_ptr > ()); yylhs.value.as < program_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < define_ptr > ())); }
#line 1809 "parser.cpp"
    break;

  case 6: // program: include
#line 247 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::make_unique<node_program>(yylhs.location); yylhs.value.as < program_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1815 "parser.cpp"
    break;

  case 7: // program: define
#line 249 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::make_unique<node_program>(yylhs.location); yylhs.value.as < program_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < define_ptr > ())); }
#line 1821 "parser.cpp"
    break;

  case 8: // include: "#include" file ";"
#line 254 "parser.ypp"
        { yylhs.value.as < include_ptr > () = std::make_unique<node_include>(yylhs.location, std::move(yystack_[1].value.as < file_ptr > ())); }
#line 1827 "parser.cpp"
    break;

  case 9: // define: usingtree
#line 258 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_usingtree = std::move(yystack_[0].value.as < usingtree_ptr > ()); }
#line 1833 "parser.cpp"
    break;

  case 10: // define: constant
#line 259 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_constant = std::move(yystack_[0].value.as < constant_ptr > ()); }
#line 1839 "parser.cpp"
    break;

  case 11: // define: thread
#line 260 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_thread = std::move(yystack_[0].value.as < thread_ptr > ()); }
#line 1845 "parser.cpp"
    break;

  case 12: // usingtree: "#using_animtree" "(" string ")" ";"
#line 265 "parser.ypp"
        { yylhs.value.as < usingtree_ptr > () = std::make_unique<node_usingtree>(yylhs.location, std::move(yystack_[2].value.as < string_ptr > ())); }
#line 1851 "parser.cpp"
    break;

  case 13: // constant: name "=" expr ";"
#line 270 "parser.ypp"
        { yylhs.value.as < constant_ptr > () = std::make_unique<node_constant>(yylhs.location, std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 1857 "parser.cpp"
    break;

  case 14: // thread: name "(" parameters ")" stmt_block
#line 275 "parser.ypp"
        { yylhs.value.as < thread_ptr > () = std::make_unique<node_thread>(yylhs.location, std::move(yystack_[4].value.as < name_ptr > ()), std::move(yystack_[2].value.as < parameters_ptr > ()), std::move(yystack_[0].value.as < stmt_list_ptr > ())); }
#line 1863 "parser.cpp"
    break;

  case 15: // parameters: parameters "," name
#line 280 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::move(yystack_[2].value.as < parameters_ptr > ()); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < name_ptr > ())); }
#line 1869 "parser.cpp"
    break;

  case 16: // parameters: name
#line 282 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(yylhs.location); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < name_ptr > ())); }
#line 1875 "parser.cpp"
    break;

  case 17: // parameters: %empty
#line 284 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(yylhs.location); }
#line 1881 "parser.cpp"
    break;

  case 18: // stmt: stmt_block
#line 288 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_list = std::move(yystack_[0].value.as < stmt_list_ptr > ()); }
#line 1887 "parser.cpp"
    break;

  case 19: // stmt: stmt_call
#line 289 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_call = std::move(yystack_[0].value.as < stmt_call_ptr > ()); }
#line 1893 "parser.cpp"
    break;

  case 20: // stmt: stmt_assign
#line 290 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < stmt_assign_ptr > ()); }
#line 1899 "parser.cpp"
    break;

  case 21: // stmt: stmt_endon
#line 291 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < stmt_endon_ptr > ()); }
#line 1905 "parser.cpp"
    break;

  case 22: // stmt: stmt_notify
#line 292 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < stmt_notify_ptr > ()); }
#line 1911 "parser.cpp"
    break;

  case 23: // stmt: stmt_wait
#line 293 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < stmt_wait_ptr > ()); }
#line 1917 "parser.cpp"
    break;

  case 24: // stmt: stmt_waittill
#line 294 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < stmt_waittill_ptr > ()); }
#line 1923 "parser.cpp"
    break;

  case 25: // stmt: stmt_waittillmatch
#line 295 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < stmt_waittillmatch_ptr > ()); }
#line 1929 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittillframeend
#line 296 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < stmt_waittillframeend_ptr > ()); }
#line 1935 "parser.cpp"
    break;

  case 27: // stmt: stmt_if
#line 297 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_if = std::move(yystack_[0].value.as < stmt_if_ptr > ()); }
#line 1941 "parser.cpp"
    break;

  case 28: // stmt: stmt_ifelse
#line 298 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < stmt_ifelse_ptr > ()); }
#line 1947 "parser.cpp"
    break;

  case 29: // stmt: stmt_while
#line 299 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_while = std::move(yystack_[0].value.as < stmt_while_ptr > ()); }
#line 1953 "parser.cpp"
    break;

  case 30: // stmt: stmt_for
#line 300 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_for = std::move(yystack_[0].value.as < stmt_for_ptr > ()); }
#line 1959 "parser.cpp"
    break;

  case 31: // stmt: stmt_foreach
#line 301 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < stmt_foreach_ptr > ()); }
#line 1965 "parser.cpp"
    break;

  case 32: // stmt: stmt_switch
#line 302 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < stmt_switch_ptr > ()); }
#line 1971 "parser.cpp"
    break;

  case 33: // stmt: stmt_case
#line 303 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_case = std::move(yystack_[0].value.as < stmt_case_ptr > ()); }
#line 1977 "parser.cpp"
    break;

  case 34: // stmt: stmt_default
#line 304 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_default = std::move(yystack_[0].value.as < stmt_default_ptr > ()); }
#line 1983 "parser.cpp"
    break;

  case 35: // stmt: stmt_break
#line 305 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_break = std::move(yystack_[0].value.as < stmt_break_ptr > ()); }
#line 1989 "parser.cpp"
    break;

  case 36: // stmt: stmt_continue
#line 306 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < stmt_continue_ptr > ()); }
#line 1995 "parser.cpp"
    break;

  case 37: // stmt: stmt_return
#line 307 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_return = std::move(yystack_[0].value.as < stmt_return_ptr > ()); }
#line 2001 "parser.cpp"
    break;

  case 38: // stmt: stmt_breakpoint
#line 308 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_breakpoint = std::move(yystack_[0].value.as < stmt_breakpoint_ptr > ()); }
#line 2007 "parser.cpp"
    break;

  case 39: // stmt: stmt_prof_begin
#line 309 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_prof_begin = std::move(yystack_[0].value.as < stmt_prof_begin_ptr > ()); }
#line 2013 "parser.cpp"
    break;

  case 40: // stmt: stmt_prof_end
#line 310 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_prof_end = std::move(yystack_[0].value.as < stmt_prof_end_ptr > ()); }
#line 2019 "parser.cpp"
    break;

  case 41: // stmt_block: "{" stmt_list "}"
#line 314 "parser.ypp"
                              { yylhs.value.as < stmt_list_ptr > () = std::move(yystack_[1].value.as < stmt_list_ptr > ()); }
#line 2025 "parser.cpp"
    break;

  case 42: // stmt_block: "{" "}"
#line 315 "parser.ypp"
                    { yylhs.value.as < stmt_list_ptr > () = std::make_unique<node_stmt_list>(yylhs.location); }
#line 2031 "parser.cpp"
    break;

  case 43: // stmt_list: stmt_list stmt
#line 320 "parser.ypp"
        { yylhs.value.as < stmt_list_ptr > () = std::move(yystack_[1].value.as < stmt_list_ptr > ()); yylhs.value.as < stmt_list_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2037 "parser.cpp"
    break;

  case 44: // stmt_list: stmt
#line 322 "parser.ypp"
        { yylhs.value.as < stmt_list_ptr > () = std::make_unique<node_stmt_list>(yylhs.location); yylhs.value.as < stmt_list_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2043 "parser.cpp"
    break;

  case 45: // stmt_call: expr_call ";"
#line 327 "parser.ypp"
        { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(yylhs.location, std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 2049 "parser.cpp"
    break;

  case 46: // stmt_call: expr_call_thread ";"
#line 329 "parser.ypp"
        { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(yylhs.location, std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 2055 "parser.cpp"
    break;

  case 47: // stmt_assign: expr_assign ";"
#line 334 "parser.ypp"
        { yylhs.value.as < stmt_assign_ptr > () = std::make_unique<node_stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < expr_assign_ptr > ())); }
#line 2061 "parser.cpp"
    break;

  case 48: // stmt_endon: object "endon" "(" expr ")" ";"
#line 339 "parser.ypp"
        { yylhs.value.as < stmt_endon_ptr > () = std::make_unique<node_stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ())); }
#line 2067 "parser.cpp"
    break;

  case 49: // stmt_notify: object "notify" "(" expr "," expr_arguments ")" ";"
#line 344 "parser.ypp"
        { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2073 "parser.cpp"
    break;

  case 50: // stmt_notify: object "notify" "(" expr ")" ";"
#line 346 "parser.ypp"
        { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2079 "parser.cpp"
    break;

  case 51: // stmt_wait: "wait" expr ";"
#line 351 "parser.ypp"
        { yylhs.value.as < stmt_wait_ptr > () = std::make_unique<node_stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2085 "parser.cpp"
    break;

  case 52: // stmt_waittill: object "waittill" "(" expr "," expr_arguments ")" ";"
#line 356 "parser.ypp"
        { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2091 "parser.cpp"
    break;

  case 53: // stmt_waittill: object "waittill" "(" expr ")" ";"
#line 358 "parser.ypp"
        { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2097 "parser.cpp"
    break;

  case 54: // stmt_waittillmatch: object "waittillmatch" "(" expr "," expr_arguments ")" ";"
#line 363 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2103 "parser.cpp"
    break;

  case 55: // stmt_waittillmatch: object "waittillmatch" "(" expr ")" ";"
#line 365 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2109 "parser.cpp"
    break;

  case 56: // stmt_waittillframeend: "waittillframeend" ";"
#line 370 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend_ptr > () = std::make_unique<node_stmt_waittillframeend>(yylhs.location); }
#line 2115 "parser.cpp"
    break;

  case 57: // stmt_if: "if" "(" expr ")" stmt
#line 375 "parser.ypp"
        { yylhs.value.as < stmt_if_ptr > () = std::make_unique<node_stmt_if>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2121 "parser.cpp"
    break;

  case 58: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 380 "parser.ypp"
        { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2127 "parser.cpp"
    break;

  case 59: // stmt_while: "while" "(" expr ")" stmt
#line 385 "parser.ypp"
        { yylhs.value.as < stmt_while_ptr > () = std::make_unique<node_stmt_while>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2133 "parser.cpp"
    break;

  case 60: // stmt_for: "for" "(" for_stmt ";" for_expr ";" for_stmt ")" stmt
#line 390 "parser.ypp"
        { yylhs.value.as < stmt_for_ptr > () = std::make_unique<node_stmt_for>(yylhs.location, std::move(yystack_[6].value.as < stmt_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2139 "parser.cpp"
    break;

  case 61: // stmt_foreach: "foreach" "(" name "in" expr ")" stmt
#line 395 "parser.ypp"
        { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(yylhs.location, expr_ptr(std::move(yystack_[4].value.as < name_ptr > ())), std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2145 "parser.cpp"
    break;

  case 62: // stmt_foreach: "foreach" "(" name "," name "in" expr ")" stmt
#line 397 "parser.ypp"
        { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(yylhs.location, expr_ptr(std::move(yystack_[6].value.as < name_ptr > ())), expr_ptr(std::move(yystack_[4].value.as < name_ptr > ())), std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2151 "parser.cpp"
    break;

  case 63: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 402 "parser.ypp"
        { yylhs.value.as < stmt_switch_ptr > () = std::make_unique<node_stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_list_ptr > ())); }
#line 2157 "parser.cpp"
    break;

  case 64: // stmt_case: "case" integer ":"
#line 407 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < integer_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2163 "parser.cpp"
    break;

  case 65: // stmt_case: "case" neg_integer ":"
#line 409 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < integer_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2169 "parser.cpp"
    break;

  case 66: // stmt_case: "case" string ":"
#line 411 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < string_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2175 "parser.cpp"
    break;

  case 67: // stmt_default: "default" ":"
#line 416 "parser.ypp"
        { yylhs.value.as < stmt_default_ptr > () = std::make_unique<node_stmt_default>(yylhs.location, std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2181 "parser.cpp"
    break;

  case 68: // stmt_break: "break" ";"
#line 421 "parser.ypp"
        { yylhs.value.as < stmt_break_ptr > () = std::make_unique<node_stmt_break>(yylhs.location); }
#line 2187 "parser.cpp"
    break;

  case 69: // stmt_continue: "continue" ";"
#line 426 "parser.ypp"
        { yylhs.value.as < stmt_continue_ptr > () = std::make_unique<node_stmt_continue>(yylhs.location); }
#line 2193 "parser.cpp"
    break;

  case 70: // stmt_return: "return" expr ";"
#line 431 "parser.ypp"
        { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(yylhs.location, std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2199 "parser.cpp"
    break;

  case 71: // stmt_return: "return" ";"
#line 433 "parser.ypp"
        { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(yylhs.location, std::make_unique<node>(yylhs.location)); }
#line 2205 "parser.cpp"
    break;

  case 72: // stmt_breakpoint: "breakpoint" ";"
#line 438 "parser.ypp"
        { yylhs.value.as < stmt_breakpoint_ptr > () = std::make_unique<node_stmt_breakpoint>(yylhs.location); }
#line 2211 "parser.cpp"
    break;

  case 73: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 443 "parser.ypp"
        { yylhs.value.as < stmt_prof_begin_ptr > () = std::make_unique<node_stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2217 "parser.cpp"
    break;

  case 74: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 448 "parser.ypp"
        { yylhs.value.as < stmt_prof_end_ptr > () = std::make_unique<node_stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2223 "parser.cpp"
    break;

  case 75: // for_stmt: expr_assign
#line 452 "parser.ypp"
                                        { yylhs.value.as < stmt_ptr > ().as_list = std::make_unique<node_stmt_list>(yylhs.location); yylhs.value.as < stmt_ptr > ().as_list->stmts.push_back(stmt_ptr(std::make_unique<node_stmt_assign>(yylhs.location, std::move(yystack_[0].value.as < expr_assign_ptr > ())))); }
#line 2229 "parser.cpp"
    break;

  case 76: // for_stmt: %empty
#line 453 "parser.ypp"
                                        { yylhs.value.as < stmt_ptr > ().as_node = std::make_unique<node>(yylhs.location); }
#line 2235 "parser.cpp"
    break;

  case 77: // for_expr: expr
#line 457 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2241 "parser.cpp"
    break;

  case 78: // for_expr: %empty
#line 458 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node>(yylhs.location); }
#line 2247 "parser.cpp"
    break;

  case 79: // expr: expr_compare
#line 462 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2253 "parser.cpp"
    break;

  case 80: // expr: expr_binary
#line 463 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2259 "parser.cpp"
    break;

  case 81: // expr: expr_primitive
#line 464 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2265 "parser.cpp"
    break;

  case 82: // expr_assign: "++" object
#line 468 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_increment>(yylhs.location, std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2271 "parser.cpp"
    break;

  case 83: // expr_assign: "--" object
#line 469 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2277 "parser.cpp"
    break;

  case 84: // expr_assign: object "++"
#line 470 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_increment>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2283 "parser.cpp"
    break;

  case 85: // expr_assign: object "--"
#line 471 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2289 "parser.cpp"
    break;

  case 86: // expr_assign: object "=" expr
#line 472 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2295 "parser.cpp"
    break;

  case 87: // expr_assign: object "|=" expr
#line 473 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2301 "parser.cpp"
    break;

  case 88: // expr_assign: object "&=" expr
#line 474 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2307 "parser.cpp"
    break;

  case 89: // expr_assign: object "^=" expr
#line 475 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2313 "parser.cpp"
    break;

  case 90: // expr_assign: object "<<=" expr
#line 476 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()),std::move( yystack_[0].value.as < expr_ptr > ())); }
#line 2319 "parser.cpp"
    break;

  case 91: // expr_assign: object ">>=" expr
#line 477 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2325 "parser.cpp"
    break;

  case 92: // expr_assign: object "+=" expr
#line 478 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2331 "parser.cpp"
    break;

  case 93: // expr_assign: object "-=" expr
#line 479 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2337 "parser.cpp"
    break;

  case 94: // expr_assign: object "*=" expr
#line 480 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mult>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2343 "parser.cpp"
    break;

  case 95: // expr_assign: object "/=" expr
#line 481 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2349 "parser.cpp"
    break;

  case 96: // expr_assign: object "%=" expr
#line 482 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2355 "parser.cpp"
    break;

  case 97: // expr_compare: expr "||" expr
#line 486 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_or>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2361 "parser.cpp"
    break;

  case 98: // expr_compare: expr "&&" expr
#line 487 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_and>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2367 "parser.cpp"
    break;

  case 99: // expr_compare: expr "==" expr
#line 488 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_equality>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2373 "parser.cpp"
    break;

  case 100: // expr_compare: expr "!=" expr
#line 489 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2379 "parser.cpp"
    break;

  case 101: // expr_compare: expr "<=" expr
#line 490 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2385 "parser.cpp"
    break;

  case 102: // expr_compare: expr ">=" expr
#line 491 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2391 "parser.cpp"
    break;

  case 103: // expr_compare: expr "<" expr
#line 492 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_less>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2397 "parser.cpp"
    break;

  case 104: // expr_compare: expr ">" expr
#line 493 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_greater>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2403 "parser.cpp"
    break;

  case 105: // expr_binary: expr "|" expr
#line 497 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2409 "parser.cpp"
    break;

  case 106: // expr_binary: expr "&" expr
#line 498 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2415 "parser.cpp"
    break;

  case 107: // expr_binary: expr "^" expr
#line 499 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2421 "parser.cpp"
    break;

  case 108: // expr_binary: expr "<<" expr
#line 500 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2427 "parser.cpp"
    break;

  case 109: // expr_binary: expr ">>" expr
#line 501 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2433 "parser.cpp"
    break;

  case 110: // expr_binary: expr "+" expr
#line 502 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_add>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2439 "parser.cpp"
    break;

  case 111: // expr_binary: expr "-" expr
#line 503 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_sub>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2445 "parser.cpp"
    break;

  case 112: // expr_binary: expr "*" expr
#line 504 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_mult>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2451 "parser.cpp"
    break;

  case 113: // expr_binary: expr "/" expr
#line 505 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_div>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2457 "parser.cpp"
    break;

  case 114: // expr_binary: expr "%" expr
#line 506 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_mod>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2463 "parser.cpp"
    break;

  case 115: // expr_primitive: "(" expr ")"
#line 510 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2469 "parser.cpp"
    break;

  case 116: // expr_primitive: "~" expr
#line 511 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_complement>(yylhs.location, std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2475 "parser.cpp"
    break;

  case 117: // expr_primitive: "!" expr
#line 512 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_not>(yylhs.location, std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2481 "parser.cpp"
    break;

  case 118: // expr_primitive: expr_call
#line 513 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2487 "parser.cpp"
    break;

  case 119: // expr_primitive: expr_call_thread
#line 514 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2493 "parser.cpp"
    break;

  case 120: // expr_primitive: expr_call_childthread
#line 515 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2499 "parser.cpp"
    break;

  case 121: // expr_primitive: expr_function
#line 516 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2505 "parser.cpp"
    break;

  case 122: // expr_primitive: expr_add_array
#line 517 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2511 "parser.cpp"
    break;

  case 123: // expr_primitive: expr_array
#line 518 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2517 "parser.cpp"
    break;

  case 124: // expr_primitive: expr_field
#line 519 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2523 "parser.cpp"
    break;

  case 125: // expr_primitive: expr_size
#line 520 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2529 "parser.cpp"
    break;

  case 126: // expr_primitive: thisthread
#line 521 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < thisthread_ptr > ()); }
#line 2535 "parser.cpp"
    break;

  case 127: // expr_primitive: empty_array
#line 522 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < empty_array_ptr > ()); }
#line 2541 "parser.cpp"
    break;

  case 128: // expr_primitive: undefined
#line 523 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < undefined_ptr > ()); }
#line 2547 "parser.cpp"
    break;

  case 129: // expr_primitive: game
#line 524 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < game_ptr > ()); }
#line 2553 "parser.cpp"
    break;

  case 130: // expr_primitive: self
#line 525 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < self_ptr > ()); }
#line 2559 "parser.cpp"
    break;

  case 131: // expr_primitive: anim
#line 526 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < anim_ptr > ()); }
#line 2565 "parser.cpp"
    break;

  case 132: // expr_primitive: level
#line 527 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < level_ptr > ()); }
#line 2571 "parser.cpp"
    break;

  case 133: // expr_primitive: animation
#line 528 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < animation_ptr > ()); }
#line 2577 "parser.cpp"
    break;

  case 134: // expr_primitive: animtree
#line 529 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < animtree_ptr > ()); }
#line 2583 "parser.cpp"
    break;

  case 135: // expr_primitive: name
#line 530 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < name_ptr > ()); }
#line 2589 "parser.cpp"
    break;

  case 136: // expr_primitive: istring
#line 531 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < istring_ptr > ()); }
#line 2595 "parser.cpp"
    break;

  case 137: // expr_primitive: string
#line 532 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < string_ptr > ()); }
#line 2601 "parser.cpp"
    break;

  case 138: // expr_primitive: vector
#line 533 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < vector_ptr > ()); }
#line 2607 "parser.cpp"
    break;

  case 139: // expr_primitive: neg_float
#line 534 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2613 "parser.cpp"
    break;

  case 140: // expr_primitive: neg_integer
#line 535 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2619 "parser.cpp"
    break;

  case 141: // expr_primitive: float
#line 536 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2625 "parser.cpp"
    break;

  case 142: // expr_primitive: integer
#line 537 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2631 "parser.cpp"
    break;

  case 143: // expr_primitive: false
#line 538 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < false_ptr > ()); }
#line 2637 "parser.cpp"
    break;

  case 144: // expr_primitive: true
#line 539 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < true_ptr > ()); }
#line 2643 "parser.cpp"
    break;

  case 145: // expr_call: expr_call_function
#line 543 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2649 "parser.cpp"
    break;

  case 146: // expr_call: expr_call_pointer
#line 544 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2655 "parser.cpp"
    break;

  case 147: // expr_call: object expr_call_function
#line 545 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2661 "parser.cpp"
    break;

  case 148: // expr_call: object expr_call_pointer
#line 546 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2667 "parser.cpp"
    break;

  case 149: // expr_call_thread: "thread" expr_call_function
#line 550 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2673 "parser.cpp"
    break;

  case 150: // expr_call_thread: "thread" expr_call_pointer
#line 551 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2679 "parser.cpp"
    break;

  case 151: // expr_call_thread: object "thread" expr_call_function
#line 552 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2685 "parser.cpp"
    break;

  case 152: // expr_call_thread: object "thread" expr_call_pointer
#line 553 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2691 "parser.cpp"
    break;

  case 153: // expr_call_childthread: "childthread" expr_call_function
#line 557 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2697 "parser.cpp"
    break;

  case 154: // expr_call_childthread: "childthread" expr_call_pointer
#line 558 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2703 "parser.cpp"
    break;

  case 155: // expr_call_childthread: object "childthread" expr_call_function
#line 559 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2709 "parser.cpp"
    break;

  case 156: // expr_call_childthread: object "childthread" expr_call_pointer
#line 560 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2715 "parser.cpp"
    break;

  case 157: // expr_call_function: name "(" expr_arguments ")"
#line 565 "parser.ypp"
        {yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(yylhs.location, std::make_unique<node_file>(), std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2721 "parser.cpp"
    break;

  case 158: // expr_call_function: file "::" name "(" expr_arguments ")"
#line 567 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(yylhs.location, std::move(yystack_[5].value.as < file_ptr > ()), std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2727 "parser.cpp"
    break;

  case 159: // expr_call_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 572 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_call_pointer>(yylhs.location, false, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2733 "parser.cpp"
    break;

  case 160: // expr_call_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 574 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_call_pointer>(yylhs.location, true, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2739 "parser.cpp"
    break;

  case 161: // expr_arguments: expr_arguments_filled
#line 578 "parser.ypp"
                            { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[0].value.as < expr_arguments_ptr > ()); }
#line 2745 "parser.cpp"
    break;

  case 162: // expr_arguments: expr_arguments_empty
#line 579 "parser.ypp"
                            { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[0].value.as < expr_arguments_ptr > ()); }
#line 2751 "parser.cpp"
    break;

  case 163: // expr_arguments_filled: expr_arguments_filled "," expr
#line 584 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[2].value.as < expr_arguments_ptr > ()); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2757 "parser.cpp"
    break;

  case 164: // expr_arguments_filled: expr
#line 586 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(yylhs.location); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2763 "parser.cpp"
    break;

  case 165: // expr_arguments_empty: %empty
#line 591 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(yylhs.location); }
#line 2769 "parser.cpp"
    break;

  case 166: // expr_function: "::" name
#line 596 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function>(yylhs.location, std::make_unique<node_file>(yylhs.location), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2775 "parser.cpp"
    break;

  case 167: // expr_function: file "::" name
#line 598 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function>(yylhs.location, std::move(yystack_[2].value.as < file_ptr > ()), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2781 "parser.cpp"
    break;

  case 168: // expr_add_array: "[" expr_arguments_filled "]"
#line 603 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2787 "parser.cpp"
    break;

  case 169: // expr_array: object "[" expr "]"
#line 608 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_array>(yylhs.location, std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2793 "parser.cpp"
    break;

  case 170: // expr_field: object "." name
#line 613 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_field>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2799 "parser.cpp"
    break;

  case 171: // expr_size: object ".size"
#line 618 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_size>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2805 "parser.cpp"
    break;

  case 172: // object: expr_call
#line 622 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2811 "parser.cpp"
    break;

  case 173: // object: expr_array
#line 623 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2817 "parser.cpp"
    break;

  case 174: // object: expr_field
#line 624 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2823 "parser.cpp"
    break;

  case 175: // object: game
#line 625 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < game_ptr > ()); }
#line 2829 "parser.cpp"
    break;

  case 176: // object: self
#line 626 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < self_ptr > ()); }
#line 2835 "parser.cpp"
    break;

  case 177: // object: anim
#line 627 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < anim_ptr > ()); }
#line 2841 "parser.cpp"
    break;

  case 178: // object: level
#line 628 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < level_ptr > ()); }
#line 2847 "parser.cpp"
    break;

  case 179: // object: name
#line 629 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < name_ptr > ()); }
#line 2853 "parser.cpp"
    break;

  case 180: // thisthread: "thisthread"
#line 632 "parser.ypp"
                                                       { yylhs.value.as < thisthread_ptr > () = std::make_unique<node_thisthread>(yylhs.location); }
#line 2859 "parser.cpp"
    break;

  case 181: // empty_array: "[" "]"
#line 633 "parser.ypp"
                                                       { yylhs.value.as < empty_array_ptr > () = std::make_unique<node_empty_array>(yylhs.location); }
#line 2865 "parser.cpp"
    break;

  case 182: // undefined: "undefined"
#line 634 "parser.ypp"
                                                       { yylhs.value.as < undefined_ptr > () = std::make_unique<node_undefined>(yylhs.location); }
#line 2871 "parser.cpp"
    break;

  case 183: // game: "game"
#line 635 "parser.ypp"
                                                       { yylhs.value.as < game_ptr > () = std::make_unique<node_game>(yylhs.location); }
#line 2877 "parser.cpp"
    break;

  case 184: // self: "self"
#line 636 "parser.ypp"
                                                       { yylhs.value.as < self_ptr > () = std::make_unique<node_self>(yylhs.location); }
#line 2883 "parser.cpp"
    break;

  case 185: // anim: "anim"
#line 637 "parser.ypp"
                                                       { yylhs.value.as < anim_ptr > () = std::make_unique<node_anim>(yylhs.location); }
#line 2889 "parser.cpp"
    break;

  case 186: // level: "level"
#line 638 "parser.ypp"
                                                       { yylhs.value.as < level_ptr > () = std::make_unique<node_level>(yylhs.location); }
#line 2895 "parser.cpp"
    break;

  case 187: // animation: "%" "identifier"
#line 639 "parser.ypp"
                                                       { yylhs.value.as < animation_ptr > () = std::make_unique<node_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2901 "parser.cpp"
    break;

  case 188: // animtree: "#animtree"
#line 640 "parser.ypp"
                                                       { yylhs.value.as < animtree_ptr > () = std::make_unique<node_animtree>(yylhs.location); }
#line 2907 "parser.cpp"
    break;

  case 189: // name: "identifier"
#line 641 "parser.ypp"
                                                       { yylhs.value.as < name_ptr > () = std::make_unique<node_name>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2913 "parser.cpp"
    break;

  case 190: // file: "file path"
#line 642 "parser.ypp"
                                                       { yylhs.value.as < file_ptr > () = std::make_unique<node_file>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2919 "parser.cpp"
    break;

  case 191: // istring: "localized string"
#line 643 "parser.ypp"
                                                       { yylhs.value.as < istring_ptr > () = std::make_unique<node_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2925 "parser.cpp"
    break;

  case 192: // string: "string literal"
#line 644 "parser.ypp"
                                                       { yylhs.value.as < string_ptr > () = std::make_unique<node_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2931 "parser.cpp"
    break;

  case 193: // vector: "(" expr "," expr "," expr ")"
#line 645 "parser.ypp"
                                                       { yylhs.value.as < vector_ptr > () = std::make_unique<node_vector>(yylhs.location, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[3].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2937 "parser.cpp"
    break;

  case 194: // neg_float: "-" "float"
#line 646 "parser.ypp"
                                                       { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 2943 "parser.cpp"
    break;

  case 195: // neg_integer: "-" "int"
#line 647 "parser.ypp"
                                                       { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 2949 "parser.cpp"
    break;

  case 196: // float: "float"
#line 648 "parser.ypp"
                                                       { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2955 "parser.cpp"
    break;

  case 197: // integer: "int"
#line 649 "parser.ypp"
                                                       { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2961 "parser.cpp"
    break;

  case 198: // false: "false"
#line 650 "parser.ypp"
                                                       { yylhs.value.as < false_ptr > () = std::make_unique<node_false>(yylhs.location); }
#line 2967 "parser.cpp"
    break;

  case 199: // true: "true"
#line 651 "parser.ypp"
                                                       { yylhs.value.as < true_ptr > () = std::make_unique<node_true>(yylhs.location); }
#line 2973 "parser.cpp"
    break;


#line 2977 "parser.cpp"

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
    "end of file", "error", "invalid token", "breakpoint", "prof_begin",
  "prof_end", "#include", "#using_animtree", "#animtree", "endon",
  "notify", "wait", "waittill", "waittillmatch", "waittillframeend", "if",
  "else", "while", "for", "foreach", "in", "switch", "case", "default",
  "break", "continue", "return", "thread", "childthread", "thisthread",
  "call", "true", "false", "undefined", ".size", "game", "self", "anim",
  "level", "(", ")", "{", "}", "[", "]", ",", ".", "::", ":", ";", "++",
  "--", "<<", ">>", "||", "&&", "==", "!=", "<=", ">=", "<", ">", "!", "~",
  "=", "+=", "-=", "*=", "/=", "%=", "|=", "&=", "^=", ">>=", "<<=", "|",
  "&", "^", "+", "-", "*", "/", "%", "file path", "identifier",
  "string literal", "localized string", "float", "int", "ADD_ARRAY",
  "THEN", "NEG", "ANIMREF", "PREINC", "PREDEC", "POSTINC", "POSTDEC",
  "$accept", "root", "program", "include", "define", "usingtree",
  "constant", "thread", "parameters", "stmt", "stmt_block", "stmt_list",
  "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify", "stmt_wait",
  "stmt_waittill", "stmt_waittillmatch", "stmt_waittillframeend",
  "stmt_if", "stmt_ifelse", "stmt_while", "stmt_for", "stmt_foreach",
  "stmt_switch", "stmt_case", "stmt_default", "stmt_break",
  "stmt_continue", "stmt_return", "stmt_breakpoint", "stmt_prof_begin",
  "stmt_prof_end", "for_stmt", "for_expr", "expr", "expr_assign",
  "expr_compare", "expr_binary", "expr_primitive", "expr_call",
  "expr_call_thread", "expr_call_childthread", "expr_call_function",
  "expr_call_pointer", "expr_arguments", "expr_arguments_filled",
  "expr_arguments_empty", "expr_function", "expr_add_array", "expr_array",
  "expr_field", "expr_size", "object", "thisthread", "empty_array",
  "undefined", "game", "self", "anim", "level", "animation", "animtree",
  "name", "file", "istring", "string", "vector", "neg_float",
  "neg_integer", "float", "integer", "false", "true", YY_NULLPTR
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

#if IW5DEBUG
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
#if IW5DEBUG
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
#if IW5DEBUG
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


  const short parser::yypact_ninf_ = -240;

  const short parser::yytable_ninf_ = -180;

  const short
  parser::yypact_[] =
  {
       7,   -68,    -9,  -240,    43,     7,  -240,  -240,  -240,  -240,
    -240,   -30,  -240,    -1,   -21,  -240,  -240,  -240,   -24,   787,
    -240,  -240,    15,   -29,  -240,  -240,    79,    79,  -240,    28,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,   787,   663,   -24,
     787,   787,   -59,   -11,  -240,  -240,  -240,  1345,  -240,  -240,
    -240,    24,  -240,  -240,  -240,  -240,  -240,  -240,    35,   269,
    -240,   361,  -240,  -240,  -240,   474,   686,   748,   756,  -240,
    -240,    10,    27,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,    31,    36,   -24,    33,  -240,  -240,    44,    38,
    -240,  -240,    52,   909,   663,  -240,  1423,     1,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,   787,   787,   787,   787,   787,
     787,   787,   787,   787,   787,   787,   787,   787,   787,   787,
     787,   787,   787,    79,    79,  -240,   849,   -24,  -240,  -240,
     787,   -24,  -240,   550,  -240,  -240,   787,   -24,   787,  -240,
     787,  1216,  -240,   787,    77,    77,  1433,   942,   405,   405,
     200,   200,   200,   200,   985,  1474,  1464,   -61,   -61,  -240,
    -240,  -240,  -240,  -240,  -240,  -240,  1255,  -240,    46,    42,
    -240,    57,    54,    67,    71,   787,    65,    76,    78,    81,
      82,    86,   -38,    87,    90,    91,   725,  -240,   416,   416,
    -240,  -240,   594,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,    92,    94,    95,  -240,  -240,
     468,  -240,  -240,  -240,  -240,    44,  1216,    57,  1294,  1332,
     103,  1423,  -240,  -240,   787,  -240,   787,   787,  1379,  -240,
     787,   787,   378,   -24,   787,    48,   100,   102,   104,  -240,
    -240,  -240,  -240,  1392,  -240,    29,    29,  -240,  -240,  -240,
    -240,  -240,   112,   114,   122,   125,  -240,  -240,   787,   787,
     787,   787,   787,   787,   787,   787,   787,   787,   787,   116,
     787,   148,   150,   151,   162,  -240,  1048,  1081,   155,  -240,
     874,   -10,  1091,  -240,  -240,  -240,  -240,   787,   787,   787,
     787,  1423,  1423,  1423,  1423,  1423,  1423,  1423,  1423,  1423,
    1423,  1423,   166,  1124,   787,  -240,   157,   161,   638,   638,
     787,   787,   -24,    36,  1134,   952,   995,  1038,   787,  -240,
     171,  -240,  -240,   110,  -240,   163,  1423,  1167,   193,  -240,
     168,   172,   787,   173,   787,   174,   787,   175,  -240,   638,
     378,   638,   787,  -240,  -240,   184,  -240,   186,  -240,   187,
    -240,  -240,   188,  -240,  1177,   180,   189,   191,   638,   638,
    -240,  -240,  -240,  -240,  -240
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,   189,     0,     2,     6,     7,     9,    10,
      11,     0,   190,     0,     0,     1,     4,     5,    17,     0,
       8,   192,     0,     0,    16,   188,     0,     0,   180,     0,
     199,   198,   182,   183,   184,   185,   186,     0,     0,     0,
       0,     0,     0,     0,   191,   196,   197,     0,    79,    80,
      81,   118,   119,   120,   145,   146,   121,   122,   123,   124,
     125,     0,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,     0,   136,   137,   138,   139,   140,   141,   142,
     143,   144,     0,     0,     0,     0,   149,   150,     0,     0,
     153,   154,     0,     0,     0,   181,   164,     0,   166,   117,
     116,   194,   195,   187,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   171,     0,     0,   147,   148,
     165,     0,    12,     0,    14,    15,     0,     0,     0,   115,
       0,   164,   168,     0,   108,   109,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   110,   111,   112,
     113,   114,   151,   152,   155,   156,     0,   170,     0,   161,
     162,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,     0,     0,
      44,    18,     0,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,   172,     0,   173,   174,
       0,   175,   176,   177,   178,   179,     0,     0,     0,     0,
       0,   163,   169,   157,   165,    72,   165,   165,     0,    56,
       0,     0,    76,     0,     0,     0,     0,     0,     0,    67,
      68,    69,    71,     0,   172,    82,    83,    41,    43,    47,
      45,    46,     0,     0,     0,     0,    84,    85,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,    75,
       0,     0,     0,    66,    65,    64,    70,     0,     0,     0,
       0,    86,    92,    93,    94,    95,    96,    87,    88,    89,
      91,    90,     0,     0,   165,   158,     0,     0,     0,     0,
      78,     0,     0,     0,     0,     0,     0,     0,   165,   193,
       0,    73,    74,    57,    59,     0,    77,     0,     0,    63,
       0,     0,   165,     0,   165,     0,   165,     0,   159,     0,
      76,     0,     0,    48,    50,     0,    53,     0,    55,     0,
     160,    58,     0,    61,     0,     0,     0,     0,     0,     0,
      49,    52,    54,    60,    62
  };

  const short
  parser::yypgoto_[] =
  {
    -240,  -240,  -240,   240,   243,  -240,  -240,  -240,  -240,  -135,
     -79,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,  -240,
    -240,  -240,  -240,  -240,   -93,  -240,    60,  -239,  -240,  -240,
    -240,  -100,  -110,  -240,   -25,   -19,  -212,   -26,  -240,  -240,
    -240,   -43,    74,  -240,    99,  -240,  -240,  -240,   121,   156,
     178,   194,  -240,  -240,     0,     5,  -240,     3,  -240,  -240,
      85,  -240,    88,  -240,  -240
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,     8,     9,    10,    23,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   288,   335,    96,   215,    48,    49,
      50,    51,    52,    53,    54,    55,   168,   169,   170,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81
  };

  const short
  parser::yytable_[] =
  {
      11,    86,    90,   289,   134,    11,    13,    87,    91,    18,
     321,    83,    97,     1,     2,    12,    84,    22,    24,   120,
     121,   122,   282,   217,   283,   284,    88,    88,   101,   102,
      14,    89,    89,   216,    19,   322,   128,  -179,  -179,    98,
    -179,   245,   129,    15,  -179,   142,   143,    21,    20,   130,
      46,  -172,  -172,  -179,  -172,    82,  -179,   258,  -172,    29,
       3,    88,  -173,  -173,    21,  -173,    89,  -172,    97,  -173,
    -172,    92,   126,   103,   131,   127,   136,   133,  -173,    47,
     132,  -173,   217,   130,   135,   137,   233,   143,   254,   254,
     218,     3,   216,  -179,  -179,   138,   234,    93,   162,   164,
      99,   100,   330,   235,   163,   165,   236,  -172,  -172,    29,
     237,   289,    12,     3,   239,   240,   347,   241,  -173,  -173,
     242,   243,    85,    88,    88,   244,   349,   167,    89,    89,
     355,   171,   357,   225,   359,   249,   102,   227,    89,   250,
     251,   259,   254,   260,   261,   218,   218,   281,   293,   218,
     294,   297,   295,   298,   141,   118,   119,   120,   121,   122,
     312,   299,    12,     3,   300,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   333,   334,   246,   166,   314,   225,   225,
     315,   316,   225,    89,    89,   128,   226,    89,   228,   218,
     229,   129,   317,   231,   320,   328,   331,   219,   217,   217,
     332,   348,   350,   352,   361,   360,   363,   353,   216,   216,
      88,   354,   356,   358,   365,    89,   366,   367,   368,   370,
     128,   128,   220,   373,   374,   238,   129,   129,   371,   217,
     372,   217,   225,   291,   339,    16,   253,    89,    17,   216,
     254,   216,   105,   106,   221,    88,    88,   362,   217,   217,
      89,    89,   219,   219,     0,   128,   219,   247,   216,   216,
     248,   129,     0,     0,     0,   218,   218,     0,   118,   119,
     120,   121,   122,     0,     0,     0,     0,   255,   256,   222,
      88,   220,     0,     0,     0,    89,  -174,  -174,     0,  -174,
     286,   287,     0,  -174,   292,     0,   218,   218,   218,   221,
     221,   223,  -174,   221,     0,  -174,   219,     0,   225,   225,
       0,     0,   338,    89,    89,   218,   218,   224,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,     0,
     313,   290,     0,     0,   222,   222,     0,     0,   222,   225,
     225,   225,  -174,  -174,    89,    89,    89,   324,   325,   326,
     327,     0,     0,   221,     0,     0,   223,   223,   225,   225,
     223,     0,     0,    89,    89,     0,     0,     0,     0,     0,
     336,   337,   224,   224,     0,     0,   224,     0,   123,   124,
       0,    29,   219,   219,     0,   125,     0,     0,   222,     0,
       0,     0,     0,     0,   126,     0,     0,   127,    29,     0,
       0,     0,   364,    33,    34,    35,    36,   220,   220,     0,
     223,    85,     0,   219,   219,   219,     0,     0,   188,   189,
       0,     0,     0,     0,     0,     0,   224,     0,     0,   221,
     221,     0,   219,   219,    12,     3,    29,     0,   220,   290,
     220,    33,    34,    35,    36,     0,     0,   105,   106,    85,
       0,    12,     3,   111,   112,   113,   114,   220,   220,     0,
     221,   221,   221,     0,   222,   222,     0,   262,   263,     0,
     264,   265,     0,   118,   119,   120,   121,   122,     0,   221,
     221,     0,     0,     0,     0,   123,   223,   223,    29,    12,
       3,  -175,  -175,     0,  -175,   222,   222,   222,  -175,     0,
       0,   126,   224,   224,   127,     0,     0,  -175,   266,   267,
    -175,     0,     0,     0,   222,   222,     0,   223,   223,   223,
       0,     0,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   224,   224,   224,   223,   223,     0,     0,
       0,    12,     3,   172,   173,   174,     0,  -175,  -175,     0,
       0,   175,   224,   224,   176,   177,     0,   178,   179,   180,
       0,   181,   182,   183,   184,   185,   186,    26,     0,     0,
      29,     0,     0,     0,     0,    33,    34,    35,    36,     0,
       0,   133,   187,    85,     0,     0,     0,   172,   173,   174,
     188,   189,     0,     0,     0,   175,     0,     0,   176,   177,
       0,   178,   179,   180,     0,   181,   182,   183,   184,   185,
     186,    26,     0,     0,    29,     0,     0,     0,     0,    33,
      34,    35,    36,    12,     3,   133,   257,    85,     0,     0,
       0,   172,   173,   174,   188,   189,     0,     0,     0,   175,
       0,     0,   176,   177,     0,   178,   179,   180,     0,   181,
     182,   183,   184,   185,   186,    26,     0,     0,    29,     0,
       0,    25,     0,    33,    34,    35,    36,    12,     3,   133,
       0,    85,     0,     0,     0,     0,     0,     0,   188,   189,
      26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
      35,    36,    37,     0,     0,     0,    94,    95,     0,     0,
      39,     0,     0,  -176,  -176,     0,  -176,     0,     0,     0,
    -176,    12,     3,     0,     0,    40,    41,     0,     0,  -176,
       0,     0,  -176,    25,     0,     0,     0,     0,     0,     0,
       0,     0,    42,     0,     0,    43,    12,     3,    21,    44,
      45,    46,    26,    27,    28,    29,    30,    31,    32,     0,
      33,    34,    35,    36,    37,     0,     0,     0,    38,  -176,
    -176,     0,    39,     0,   252,  -177,  -177,     0,  -177,     0,
       0,     0,  -177,  -178,  -178,     0,  -178,    40,    41,     0,
    -178,  -177,     0,     0,  -177,    25,     0,     0,     0,  -178,
       0,     0,  -178,     0,    42,     0,     0,    43,    12,     3,
      21,    44,    45,    46,    26,    27,    28,    29,    30,    31,
      32,     0,    33,    34,    35,    36,    37,     0,     0,     0,
      38,  -177,  -177,     0,    39,     0,     0,     0,     0,  -178,
    -178,     0,     0,     0,     0,     0,     0,     0,     0,    40,
      41,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,    43,
      12,     3,    21,    44,    45,    46,    26,    27,    28,    29,
      30,    31,    32,     0,    33,    34,    35,    36,    37,     0,
       0,     0,    94,     0,     0,     0,    39,     0,     0,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
       0,    40,    41,     0,     0,     0,     0,   126,     0,     0,
     127,     0,     0,     0,   266,   267,     0,     0,    42,     0,
       0,    43,    12,     3,    21,    44,    45,    46,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   139,
       0,     0,     0,     0,   140,     0,     0,    12,     3,     0,
       0,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,   116,   117,   118,   119,   120,
     121,   122,   341,     0,   105,   106,     0,   342,   109,   110,
     111,   112,   113,   114,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,     0,     0,     0,   115,   116,   117,
     118,   119,   120,   121,   122,     0,     0,   115,   116,   117,
     118,   119,   120,   121,   122,   343,     0,   105,   106,     0,
     344,   109,   110,   111,   112,   113,   114,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
       0,   116,   117,   118,   119,   120,   121,   122,     0,     0,
     115,   116,   117,   118,   119,   120,   121,   122,   345,     0,
       0,     0,     0,   346,     0,     0,     0,     0,   318,     0,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   319,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   323,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   329,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   340,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,   351,     0,   115,
     116,   117,   118,   119,   120,   121,   122,   369,     0,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
       0,     0,   115,   116,   117,   118,   119,   120,   121,   122,
     230,     0,     0,     0,     0,     0,     0,     0,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,   116,   117,   118,   119,   120,   121,   122,   232,
       0,     0,     0,     0,     0,     0,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     115,   116,   117,   118,   119,   120,   121,   122,   279,     0,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,   121,   122,   280,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   104,     0,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,     0,     0,     0,     0,     0,
     115,   116,   117,   118,   119,   120,   121,   122,   285,     0,
       0,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   296,     0,     0,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,     0,     0,     0,     0,     0,   115,   116,   117,
     118,   119,   120,   121,   122,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   105,   106,     0,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,   115,   116,
     117,   118,   119,   120,   121,   122,     0,     0,   115,   116,
     117,   118,   119,   120,   121,   122,   105,   106,     0,     0,
     109,   110,   111,   112,   113,   114,   105,   106,     0,     0,
     109,   110,   111,   112,   113,   114,     0,     0,     0,     0,
     116,     0,   118,   119,   120,   121,   122,     0,     0,     0,
       0,     0,   118,   119,   120,   121,   122
  };

  const short
  parser::yycheck_[] =
  {
       0,    26,    27,   242,    83,     5,     1,    26,    27,    39,
      20,    40,    38,     6,     7,    83,    45,    14,    18,    80,
      81,    82,   234,   133,   236,   237,    26,    27,    87,    88,
      39,    26,    27,   133,    64,    45,    61,    27,    28,    39,
      30,    79,    61,     0,    34,    44,    45,    85,    49,    39,
      88,    27,    28,    43,    30,    40,    46,   192,    34,    30,
      84,    61,    27,    28,    85,    30,    61,    43,    94,    34,
      46,    43,    43,    84,    47,    46,    43,    41,    43,    19,
      49,    46,   192,    39,    84,    47,    40,    45,   188,   189,
     133,    84,   192,    83,    84,    43,    39,    37,   123,   124,
      40,    41,   314,    49,   123,   124,    39,    83,    84,    30,
      39,   350,    83,    84,    49,    39,   328,    39,    83,    84,
      39,    39,    43,   123,   124,    39,    16,   127,   123,   124,
     342,   131,   344,   133,   346,    48,    88,   137,   133,    49,
      49,    49,   242,    49,    49,   188,   189,    44,    48,   192,
      48,    39,    48,    39,    94,    78,    79,    80,    81,    82,
      44,    39,    83,    84,    39,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   318,   319,   182,   126,    39,   188,   189,
      40,    40,   192,   188,   189,   220,   136,   192,   138,   242,
     140,   220,    40,   143,    49,    39,    49,   133,   318,   319,
      49,    40,    49,    20,   349,    40,   351,    49,   318,   319,
     220,    49,    49,    49,    40,   220,    40,    40,    40,    49,
     255,   256,   133,   368,   369,   175,   255,   256,    49,   349,
      49,   351,   242,   243,   323,     5,   186,   242,     5,   349,
     350,   351,    52,    53,   133,   255,   256,   350,   368,   369,
     255,   256,   188,   189,    -1,   290,   192,   182,   368,   369,
     182,   290,    -1,    -1,    -1,   318,   319,    -1,    78,    79,
      80,    81,    82,    -1,    -1,    -1,    -1,   188,   189,   133,
     290,   192,    -1,    -1,    -1,   290,    27,    28,    -1,    30,
     240,   241,    -1,    34,   244,    -1,   349,   350,   351,   188,
     189,   133,    43,   192,    -1,    46,   242,    -1,   318,   319,
      -1,    -1,   322,   318,   319,   368,   369,   133,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,    -1,
     280,   242,    -1,    -1,   188,   189,    -1,    -1,   192,   349,
     350,   351,    83,    84,   349,   350,   351,   297,   298,   299,
     300,    -1,    -1,   242,    -1,    -1,   188,   189,   368,   369,
     192,    -1,    -1,   368,   369,    -1,    -1,    -1,    -1,    -1,
     320,   321,   188,   189,    -1,    -1,   192,    -1,    27,    28,
      -1,    30,   318,   319,    -1,    34,    -1,    -1,   242,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    30,    -1,
      -1,    -1,   352,    35,    36,    37,    38,   318,   319,    -1,
     242,    43,    -1,   349,   350,   351,    -1,    -1,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,   318,
     319,    -1,   368,   369,    83,    84,    30,    -1,   349,   350,
     351,    35,    36,    37,    38,    -1,    -1,    52,    53,    43,
      -1,    83,    84,    58,    59,    60,    61,   368,   369,    -1,
     349,   350,   351,    -1,   318,   319,    -1,     9,    10,    -1,
      12,    13,    -1,    78,    79,    80,    81,    82,    -1,   368,
     369,    -1,    -1,    -1,    -1,    27,   318,   319,    30,    83,
      84,    27,    28,    -1,    30,   349,   350,   351,    34,    -1,
      -1,    43,   318,   319,    46,    -1,    -1,    43,    50,    51,
      46,    -1,    -1,    -1,   368,   369,    -1,   349,   350,   351,
      -1,    -1,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   349,   350,   351,   368,   369,    -1,    -1,
      -1,    83,    84,     3,     4,     5,    -1,    83,    84,    -1,
      -1,    11,   368,   369,    14,    15,    -1,    17,    18,    19,
      -1,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,
      -1,    41,    42,    43,    -1,    -1,    -1,     3,     4,     5,
      50,    51,    -1,    -1,    -1,    11,    -1,    -1,    14,    15,
      -1,    17,    18,    19,    -1,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    83,    84,    41,    42,    43,    -1,    -1,
      -1,     3,     4,     5,    50,    51,    -1,    -1,    -1,    11,
      -1,    -1,    14,    15,    -1,    17,    18,    19,    -1,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    -1,
      -1,     8,    -1,    35,    36,    37,    38,    83,    84,    41,
      -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      27,    28,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    43,    44,    -1,    -1,
      47,    -1,    -1,    27,    28,    -1,    30,    -1,    -1,    -1,
      34,    83,    84,    -1,    -1,    62,    63,    -1,    -1,    43,
      -1,    -1,    46,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    82,    83,    84,    85,    86,
      87,    88,    27,    28,    29,    30,    31,    32,    33,    -1,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    43,    83,
      84,    -1,    47,    -1,    49,    27,    28,    -1,    30,    -1,
      -1,    -1,    34,    27,    28,    -1,    30,    62,    63,    -1,
      34,    43,    -1,    -1,    46,     8,    -1,    -1,    -1,    43,
      -1,    -1,    46,    -1,    79,    -1,    -1,    82,    83,    84,
      85,    86,    87,    88,    27,    28,    29,    30,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    83,    84,    -1,    47,    -1,    -1,    -1,    -1,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    82,
      83,    84,    85,    86,    87,    88,    27,    28,    29,    30,
      31,    32,    33,    -1,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    -1,    -1,    79,    -1,
      -1,    82,    83,    84,    85,    86,    87,    88,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    40,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    83,    84,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    40,    -1,    52,    53,    -1,    45,    56,    57,
      58,    59,    60,    61,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    40,    -1,    52,    53,    -1,
      45,    56,    57,    58,    59,    60,    61,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    76,    77,    78,    79,    80,    81,    82,    -1,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    40,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    40,    -1,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    40,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    40,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    40,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    40,    -1,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    40,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    40,    -1,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    49,    -1,    -1,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    49,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    49,    -1,    -1,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    52,    53,    -1,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    52,    53,    -1,    -1,
      56,    57,    58,    59,    60,    61,    52,    53,    -1,    -1,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      76,    -1,    78,    79,    80,    81,    82,    -1,    -1,    -1,
      -1,    -1,    78,    79,    80,    81,    82
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     6,     7,    84,    98,    99,   100,   101,   102,   103,
     104,   161,    83,   162,    39,     0,   100,   101,    39,    64,
      49,    85,   164,   105,   161,     8,    27,    28,    29,    30,
      31,    32,    33,    35,    36,    37,    38,    39,    43,    47,
      62,    63,    79,    82,    86,    87,    88,   133,   135,   136,
     137,   138,   139,   140,   141,   142,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,    40,    40,    45,    43,   141,   142,   161,   162,
     141,   142,    43,   133,    43,    44,   133,   144,   161,   133,
     133,    87,    88,    84,    49,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    75,    76,    77,    78,    79,
      80,    81,    82,    27,    28,    34,    43,    46,   141,   142,
      39,    47,    49,    41,   107,   161,    43,    47,    43,    40,
      45,   133,    44,    45,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   141,   142,   141,   142,   133,   161,   143,   144,
     145,   161,     3,     4,     5,    11,    14,    15,    17,    18,
      19,    21,    22,    23,    24,    25,    26,    42,    50,    51,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   134,   138,   139,   148,   149,
     151,   155,   156,   157,   158,   161,   133,   161,   133,   133,
      44,   133,    44,    40,    39,    49,    39,    39,   133,    49,
      39,    39,    39,    39,    39,    79,   164,   167,   169,    48,
      49,    49,    49,   133,   138,   151,   151,    42,   106,    49,
      49,    49,     9,    10,    12,    13,    50,    51,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    44,
      45,    44,   143,   143,   143,    49,   133,   133,   131,   134,
     151,   161,   133,    48,    48,    48,    49,    39,    39,    39,
      39,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,    44,   133,    39,    40,    40,    40,    40,    40,
      49,    20,    45,    40,   133,   133,   133,   133,    39,    40,
     143,    49,    49,   106,   106,   132,   133,   133,   161,   107,
      40,    40,    45,    40,    45,    40,    45,   143,    40,    16,
      49,    40,    20,    49,    49,   143,    49,   143,    49,   143,
      40,   106,   131,   106,   133,    40,    40,    40,    40,    40,
      49,    49,    49,   106,   106
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    97,    98,    98,    99,    99,    99,    99,   100,   101,
     101,   101,   102,   103,   104,   105,   105,   105,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   107,   107,   108,   108,   109,   109,   110,   111,   112,
     112,   113,   114,   114,   115,   115,   116,   117,   118,   119,
     120,   121,   121,   122,   123,   123,   123,   124,   125,   126,
     127,   127,   128,   129,   130,   131,   131,   132,   132,   133,
     133,   133,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   135,   135,   135,
     135,   135,   135,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   138,   138,   138,   139,
     139,   139,   139,   140,   140,   140,   140,   141,   141,   142,
     142,   143,   143,   144,   144,   145,   146,   146,   147,   148,
     149,   150,   151,   151,   151,   151,   151,   151,   151,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     1,     1,     3,     1,
       1,     1,     5,     4,     5,     3,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     1,     2,     2,     2,     6,     8,
       6,     3,     8,     6,     8,     6,     2,     5,     7,     5,
       9,     7,     9,     5,     3,     3,     3,     2,     2,     2,
       3,     2,     2,     5,     5,     1,     0,     1,     0,     1,
       1,     1,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     3,     3,     2,     2,     3,     3,     4,     6,     8,
       9,     1,     1,     3,     1,     0,     2,     3,     3,     4,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     7,     2,     2,     1,     1,     1,     1
  };




#if IW5DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   237,   237,   238,   242,   244,   246,   248,   253,   258,
     259,   260,   264,   269,   274,   279,   281,   284,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   314,   315,   319,   321,   326,   328,   333,   338,   343,
     345,   350,   355,   357,   362,   364,   369,   374,   379,   384,
     389,   394,   396,   401,   406,   408,   410,   415,   420,   425,
     430,   432,   437,   442,   447,   452,   453,   457,   458,   462,
     463,   464,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   486,   487,   488,
     489,   490,   491,   492,   493,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   543,   544,   545,   546,   550,
     551,   552,   553,   557,   558,   559,   560,   564,   566,   571,
     573,   578,   579,   583,   585,   591,   595,   597,   602,   607,
     612,   617,   622,   623,   624,   625,   626,   627,   628,   629,
     632,   633,   634,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651
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
#endif // IW5DEBUG


#line 13 "parser.ypp"
} } } // xsk::gsc::iw5
#line 4043 "parser.cpp"

#line 653 "parser.ypp"


void xsk::gsc::iw5::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
