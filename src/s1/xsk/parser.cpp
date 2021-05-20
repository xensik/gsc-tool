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
xsk::gsc::s1::parser::symbol_type S1lex(yyscan_t yyscanner, xsk::gsc::location& loc);

#line 47 "parser.cpp"

// Take the name prefix into account.
#define yylex   S1lex



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
#if S1DEBUG

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

#else // !S1DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !S1DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "parser.ypp"
namespace xsk { namespace gsc { namespace s1 {
#line 149 "parser.cpp"

  /// Build a parser object.
  parser::parser (yyscan_t yyscanner_yyarg, xsk::gsc::location& loc_yyarg, xsk::gsc::program_ptr& ast_yyarg)
#if S1DEBUG
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.YY_MOVE_OR_COPY< stmt_waitframe_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< stmt_waitframe_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.copy< stmt_waitframe_ptr > (that.value);
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< stmt_waitframe_ptr > (that.value);
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

#if S1DEBUG
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

#if S1DEBUG
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
#endif // S1DEBUG

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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        yylhs.value.emplace< stmt_waitframe_ptr > ();
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
#line 239 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program_ptr > ()); }
#line 1811 "parser.cpp"
    break;

  case 3: // root: %empty
#line 240 "parser.ypp"
              { ast = std::make_unique<node_program>(yylhs.location); }
#line 1817 "parser.cpp"
    break;

  case 4: // program: program include
#line 245 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::move(yystack_[1].value.as < program_ptr > ()); yylhs.value.as < program_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1823 "parser.cpp"
    break;

  case 5: // program: program define
#line 247 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::move(yystack_[1].value.as < program_ptr > ()); yylhs.value.as < program_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < define_ptr > ())); }
#line 1829 "parser.cpp"
    break;

  case 6: // program: include
#line 249 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::make_unique<node_program>(yylhs.location); yylhs.value.as < program_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1835 "parser.cpp"
    break;

  case 7: // program: define
#line 251 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::make_unique<node_program>(yylhs.location); yylhs.value.as < program_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < define_ptr > ())); }
#line 1841 "parser.cpp"
    break;

  case 8: // include: "#include" file ";"
#line 256 "parser.ypp"
        { yylhs.value.as < include_ptr > () = std::make_unique<node_include>(yylhs.location, std::move(yystack_[1].value.as < file_ptr > ())); }
#line 1847 "parser.cpp"
    break;

  case 9: // define: usingtree
#line 260 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_usingtree = std::move(yystack_[0].value.as < usingtree_ptr > ()); }
#line 1853 "parser.cpp"
    break;

  case 10: // define: constant
#line 261 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_constant = std::move(yystack_[0].value.as < constant_ptr > ()); }
#line 1859 "parser.cpp"
    break;

  case 11: // define: thread
#line 262 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_thread = std::move(yystack_[0].value.as < thread_ptr > ()); }
#line 1865 "parser.cpp"
    break;

  case 12: // usingtree: "#using_animtree" "(" string ")" ";"
#line 267 "parser.ypp"
        { yylhs.value.as < usingtree_ptr > () = std::make_unique<node_usingtree>(yylhs.location, std::move(yystack_[2].value.as < string_ptr > ())); }
#line 1871 "parser.cpp"
    break;

  case 13: // constant: name "=" expr ";"
#line 272 "parser.ypp"
        { yylhs.value.as < constant_ptr > () = std::make_unique<node_constant>(yylhs.location, std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 1877 "parser.cpp"
    break;

  case 14: // thread: name "(" parameters ")" stmt_block
#line 277 "parser.ypp"
        { yylhs.value.as < thread_ptr > () = std::make_unique<node_thread>(yylhs.location, std::move(yystack_[4].value.as < name_ptr > ()), std::move(yystack_[2].value.as < parameters_ptr > ()), std::move(yystack_[0].value.as < stmt_list_ptr > ())); }
#line 1883 "parser.cpp"
    break;

  case 15: // parameters: parameters "," name
#line 282 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::move(yystack_[2].value.as < parameters_ptr > ()); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < name_ptr > ())); }
#line 1889 "parser.cpp"
    break;

  case 16: // parameters: name
#line 284 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(yylhs.location); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < name_ptr > ())); }
#line 1895 "parser.cpp"
    break;

  case 17: // parameters: %empty
#line 286 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(yylhs.location); }
#line 1901 "parser.cpp"
    break;

  case 18: // stmt: stmt_block
#line 290 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_list = std::move(yystack_[0].value.as < stmt_list_ptr > ()); }
#line 1907 "parser.cpp"
    break;

  case 19: // stmt: stmt_call
#line 291 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_call = std::move(yystack_[0].value.as < stmt_call_ptr > ()); }
#line 1913 "parser.cpp"
    break;

  case 20: // stmt: stmt_assign
#line 292 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < stmt_assign_ptr > ()); }
#line 1919 "parser.cpp"
    break;

  case 21: // stmt: stmt_endon
#line 293 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < stmt_endon_ptr > ()); }
#line 1925 "parser.cpp"
    break;

  case 22: // stmt: stmt_notify
#line 294 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < stmt_notify_ptr > ()); }
#line 1931 "parser.cpp"
    break;

  case 23: // stmt: stmt_wait
#line 295 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < stmt_wait_ptr > ()); }
#line 1937 "parser.cpp"
    break;

  case 24: // stmt: stmt_waittill
#line 296 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < stmt_waittill_ptr > ()); }
#line 1943 "parser.cpp"
    break;

  case 25: // stmt: stmt_waittillmatch
#line 297 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < stmt_waittillmatch_ptr > ()); }
#line 1949 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittillframeend
#line 298 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < stmt_waittillframeend_ptr > ()); }
#line 1955 "parser.cpp"
    break;

  case 27: // stmt: stmt_waitframe
#line 299 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waitframe = std::move(yystack_[0].value.as < stmt_waitframe_ptr > ()); }
#line 1961 "parser.cpp"
    break;

  case 28: // stmt: stmt_if
#line 300 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_if = std::move(yystack_[0].value.as < stmt_if_ptr > ()); }
#line 1967 "parser.cpp"
    break;

  case 29: // stmt: stmt_ifelse
#line 301 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < stmt_ifelse_ptr > ()); }
#line 1973 "parser.cpp"
    break;

  case 30: // stmt: stmt_while
#line 302 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_while = std::move(yystack_[0].value.as < stmt_while_ptr > ()); }
#line 1979 "parser.cpp"
    break;

  case 31: // stmt: stmt_for
#line 303 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_for = std::move(yystack_[0].value.as < stmt_for_ptr > ()); }
#line 1985 "parser.cpp"
    break;

  case 32: // stmt: stmt_foreach
#line 304 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < stmt_foreach_ptr > ()); }
#line 1991 "parser.cpp"
    break;

  case 33: // stmt: stmt_switch
#line 305 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < stmt_switch_ptr > ()); }
#line 1997 "parser.cpp"
    break;

  case 34: // stmt: stmt_case
#line 306 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_case = std::move(yystack_[0].value.as < stmt_case_ptr > ()); }
#line 2003 "parser.cpp"
    break;

  case 35: // stmt: stmt_default
#line 307 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_default = std::move(yystack_[0].value.as < stmt_default_ptr > ()); }
#line 2009 "parser.cpp"
    break;

  case 36: // stmt: stmt_break
#line 308 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_break = std::move(yystack_[0].value.as < stmt_break_ptr > ()); }
#line 2015 "parser.cpp"
    break;

  case 37: // stmt: stmt_continue
#line 309 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < stmt_continue_ptr > ()); }
#line 2021 "parser.cpp"
    break;

  case 38: // stmt: stmt_return
#line 310 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_return = std::move(yystack_[0].value.as < stmt_return_ptr > ()); }
#line 2027 "parser.cpp"
    break;

  case 39: // stmt: stmt_breakpoint
#line 311 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_breakpoint = std::move(yystack_[0].value.as < stmt_breakpoint_ptr > ()); }
#line 2033 "parser.cpp"
    break;

  case 40: // stmt: stmt_prof_begin
#line 312 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_prof_begin = std::move(yystack_[0].value.as < stmt_prof_begin_ptr > ()); }
#line 2039 "parser.cpp"
    break;

  case 41: // stmt: stmt_prof_end
#line 313 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_prof_end = std::move(yystack_[0].value.as < stmt_prof_end_ptr > ()); }
#line 2045 "parser.cpp"
    break;

  case 42: // stmt_block: "{" stmt_list "}"
#line 317 "parser.ypp"
                              { yylhs.value.as < stmt_list_ptr > () = std::move(yystack_[1].value.as < stmt_list_ptr > ()); }
#line 2051 "parser.cpp"
    break;

  case 43: // stmt_block: "{" "}"
#line 318 "parser.ypp"
                    { yylhs.value.as < stmt_list_ptr > () = std::make_unique<node_stmt_list>(yylhs.location); }
#line 2057 "parser.cpp"
    break;

  case 44: // stmt_list: stmt_list stmt
#line 323 "parser.ypp"
        { yylhs.value.as < stmt_list_ptr > () = std::move(yystack_[1].value.as < stmt_list_ptr > ()); yylhs.value.as < stmt_list_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2063 "parser.cpp"
    break;

  case 45: // stmt_list: stmt
#line 325 "parser.ypp"
        { yylhs.value.as < stmt_list_ptr > () = std::make_unique<node_stmt_list>(yylhs.location); yylhs.value.as < stmt_list_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2069 "parser.cpp"
    break;

  case 46: // stmt_call: expr_call ";"
#line 330 "parser.ypp"
        { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(yylhs.location, std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 2075 "parser.cpp"
    break;

  case 47: // stmt_call: expr_call_thread ";"
#line 332 "parser.ypp"
        { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(yylhs.location, std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 2081 "parser.cpp"
    break;

  case 48: // stmt_assign: expr_assign ";"
#line 337 "parser.ypp"
        { yylhs.value.as < stmt_assign_ptr > () = std::make_unique<node_stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < expr_assign_ptr > ())); }
#line 2087 "parser.cpp"
    break;

  case 49: // stmt_endon: object "endon" "(" expr ")" ";"
#line 342 "parser.ypp"
        { yylhs.value.as < stmt_endon_ptr > () = std::make_unique<node_stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ())); }
#line 2093 "parser.cpp"
    break;

  case 50: // stmt_notify: object "notify" "(" expr "," expr_arguments ")" ";"
#line 347 "parser.ypp"
        { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2099 "parser.cpp"
    break;

  case 51: // stmt_notify: object "notify" "(" expr ")" ";"
#line 349 "parser.ypp"
        { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2105 "parser.cpp"
    break;

  case 52: // stmt_wait: "wait" expr ";"
#line 354 "parser.ypp"
        { yylhs.value.as < stmt_wait_ptr > () = std::make_unique<node_stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2111 "parser.cpp"
    break;

  case 53: // stmt_waittill: object "waittill" "(" expr "," expr_arguments ")" ";"
#line 359 "parser.ypp"
        { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2117 "parser.cpp"
    break;

  case 54: // stmt_waittill: object "waittill" "(" expr ")" ";"
#line 361 "parser.ypp"
        { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2123 "parser.cpp"
    break;

  case 55: // stmt_waittillmatch: object "waittillmatch" "(" expr "," expr_arguments ")" ";"
#line 366 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2129 "parser.cpp"
    break;

  case 56: // stmt_waittillmatch: object "waittillmatch" "(" expr ")" ";"
#line 368 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2135 "parser.cpp"
    break;

  case 57: // stmt_waittillframeend: "waittillframeend" ";"
#line 373 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend_ptr > () = std::make_unique<node_stmt_waittillframeend>(yylhs.location); }
#line 2141 "parser.cpp"
    break;

  case 58: // stmt_waitframe: "waitframe" ";"
#line 378 "parser.ypp"
        { yylhs.value.as < stmt_waitframe_ptr > () = std::make_unique<node_stmt_waitframe>(yylhs.location); }
#line 2147 "parser.cpp"
    break;

  case 59: // stmt_waitframe: "waitframe" "(" ")" ";"
#line 380 "parser.ypp"
        { yylhs.value.as < stmt_waitframe_ptr > () = std::make_unique<node_stmt_waitframe>(yylhs.location); }
#line 2153 "parser.cpp"
    break;

  case 60: // stmt_if: "if" "(" expr ")" stmt
#line 385 "parser.ypp"
        { yylhs.value.as < stmt_if_ptr > () = std::make_unique<node_stmt_if>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2159 "parser.cpp"
    break;

  case 61: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 390 "parser.ypp"
        { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2165 "parser.cpp"
    break;

  case 62: // stmt_while: "while" "(" expr ")" stmt
#line 395 "parser.ypp"
        { yylhs.value.as < stmt_while_ptr > () = std::make_unique<node_stmt_while>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2171 "parser.cpp"
    break;

  case 63: // stmt_for: "for" "(" for_stmt ";" for_expr ";" for_stmt ")" stmt
#line 400 "parser.ypp"
        { yylhs.value.as < stmt_for_ptr > () = std::make_unique<node_stmt_for>(yylhs.location, std::move(yystack_[6].value.as < stmt_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2177 "parser.cpp"
    break;

  case 64: // stmt_foreach: "foreach" "(" name "in" expr ")" stmt
#line 405 "parser.ypp"
        { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(yylhs.location, expr_ptr(std::move(yystack_[4].value.as < name_ptr > ())), std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2183 "parser.cpp"
    break;

  case 65: // stmt_foreach: "foreach" "(" name "," name "in" expr ")" stmt
#line 407 "parser.ypp"
        { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(yylhs.location, expr_ptr(std::move(yystack_[6].value.as < name_ptr > ())), expr_ptr(std::move(yystack_[4].value.as < name_ptr > ())), std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2189 "parser.cpp"
    break;

  case 66: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 412 "parser.ypp"
        { yylhs.value.as < stmt_switch_ptr > () = std::make_unique<node_stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_list_ptr > ())); }
#line 2195 "parser.cpp"
    break;

  case 67: // stmt_case: "case" integer ":"
#line 417 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < integer_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2201 "parser.cpp"
    break;

  case 68: // stmt_case: "case" neg_integer ":"
#line 419 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < integer_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2207 "parser.cpp"
    break;

  case 69: // stmt_case: "case" string ":"
#line 421 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < string_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2213 "parser.cpp"
    break;

  case 70: // stmt_default: "default" ":"
#line 426 "parser.ypp"
        { yylhs.value.as < stmt_default_ptr > () = std::make_unique<node_stmt_default>(yylhs.location, std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2219 "parser.cpp"
    break;

  case 71: // stmt_break: "break" ";"
#line 431 "parser.ypp"
        { yylhs.value.as < stmt_break_ptr > () = std::make_unique<node_stmt_break>(yylhs.location); }
#line 2225 "parser.cpp"
    break;

  case 72: // stmt_continue: "continue" ";"
#line 436 "parser.ypp"
        { yylhs.value.as < stmt_continue_ptr > () = std::make_unique<node_stmt_continue>(yylhs.location); }
#line 2231 "parser.cpp"
    break;

  case 73: // stmt_return: "return" expr ";"
#line 441 "parser.ypp"
        { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(yylhs.location, std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2237 "parser.cpp"
    break;

  case 74: // stmt_return: "return" ";"
#line 443 "parser.ypp"
        { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(yylhs.location, std::make_unique<node>(yylhs.location)); }
#line 2243 "parser.cpp"
    break;

  case 75: // stmt_breakpoint: "breakpoint" ";"
#line 448 "parser.ypp"
        { yylhs.value.as < stmt_breakpoint_ptr > () = std::make_unique<node_stmt_breakpoint>(yylhs.location); }
#line 2249 "parser.cpp"
    break;

  case 76: // stmt_prof_begin: "prof_begin" "(" expr_arguments ")" ";"
#line 453 "parser.ypp"
        { yylhs.value.as < stmt_prof_begin_ptr > () = std::make_unique<node_stmt_prof_begin>(yylhs.location, std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2255 "parser.cpp"
    break;

  case 77: // stmt_prof_end: "prof_end" "(" expr_arguments ")" ";"
#line 458 "parser.ypp"
        { yylhs.value.as < stmt_prof_end_ptr > () = std::make_unique<node_stmt_prof_end>(yylhs.location, std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2261 "parser.cpp"
    break;

  case 78: // for_stmt: expr_assign
#line 462 "parser.ypp"
                                        { yylhs.value.as < stmt_ptr > ().as_list = std::make_unique<node_stmt_list>(yylhs.location); yylhs.value.as < stmt_ptr > ().as_list->stmts.push_back(stmt_ptr(std::make_unique<node_stmt_assign>(yylhs.location, std::move(yystack_[0].value.as < expr_assign_ptr > ())))); }
#line 2267 "parser.cpp"
    break;

  case 79: // for_stmt: %empty
#line 463 "parser.ypp"
                                        { yylhs.value.as < stmt_ptr > ().as_node = std::make_unique<node>(yylhs.location); }
#line 2273 "parser.cpp"
    break;

  case 80: // for_expr: expr
#line 467 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2279 "parser.cpp"
    break;

  case 81: // for_expr: %empty
#line 468 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node>(yylhs.location); }
#line 2285 "parser.cpp"
    break;

  case 82: // expr: expr_compare
#line 472 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2291 "parser.cpp"
    break;

  case 83: // expr: expr_binary
#line 473 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2297 "parser.cpp"
    break;

  case 84: // expr: expr_primitive
#line 474 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2303 "parser.cpp"
    break;

  case 85: // expr_assign: "++" object
#line 478 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_increment>(yylhs.location, std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2309 "parser.cpp"
    break;

  case 86: // expr_assign: "--" object
#line 479 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2315 "parser.cpp"
    break;

  case 87: // expr_assign: object "++"
#line 480 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_increment>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2321 "parser.cpp"
    break;

  case 88: // expr_assign: object "--"
#line 481 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2327 "parser.cpp"
    break;

  case 89: // expr_assign: object "=" expr
#line 482 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2333 "parser.cpp"
    break;

  case 90: // expr_assign: object "|=" expr
#line 483 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2339 "parser.cpp"
    break;

  case 91: // expr_assign: object "&=" expr
#line 484 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2345 "parser.cpp"
    break;

  case 92: // expr_assign: object "^=" expr
#line 485 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2351 "parser.cpp"
    break;

  case 93: // expr_assign: object "<<=" expr
#line 486 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()),std::move( yystack_[0].value.as < expr_ptr > ())); }
#line 2357 "parser.cpp"
    break;

  case 94: // expr_assign: object ">>=" expr
#line 487 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2363 "parser.cpp"
    break;

  case 95: // expr_assign: object "+=" expr
#line 488 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2369 "parser.cpp"
    break;

  case 96: // expr_assign: object "-=" expr
#line 489 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2375 "parser.cpp"
    break;

  case 97: // expr_assign: object "*=" expr
#line 490 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mult>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2381 "parser.cpp"
    break;

  case 98: // expr_assign: object "/=" expr
#line 491 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2387 "parser.cpp"
    break;

  case 99: // expr_assign: object "%=" expr
#line 492 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2393 "parser.cpp"
    break;

  case 100: // expr_compare: expr "||" expr
#line 496 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_or>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2399 "parser.cpp"
    break;

  case 101: // expr_compare: expr "&&" expr
#line 497 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_and>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2405 "parser.cpp"
    break;

  case 102: // expr_compare: expr "==" expr
#line 498 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_equality>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2411 "parser.cpp"
    break;

  case 103: // expr_compare: expr "!=" expr
#line 499 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2417 "parser.cpp"
    break;

  case 104: // expr_compare: expr "<=" expr
#line 500 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2423 "parser.cpp"
    break;

  case 105: // expr_compare: expr ">=" expr
#line 501 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2429 "parser.cpp"
    break;

  case 106: // expr_compare: expr "<" expr
#line 502 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_less>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2435 "parser.cpp"
    break;

  case 107: // expr_compare: expr ">" expr
#line 503 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_greater>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2441 "parser.cpp"
    break;

  case 108: // expr_binary: expr "|" expr
#line 507 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2447 "parser.cpp"
    break;

  case 109: // expr_binary: expr "&" expr
#line 508 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2453 "parser.cpp"
    break;

  case 110: // expr_binary: expr "^" expr
#line 509 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2459 "parser.cpp"
    break;

  case 111: // expr_binary: expr "<<" expr
#line 510 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2465 "parser.cpp"
    break;

  case 112: // expr_binary: expr ">>" expr
#line 511 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2471 "parser.cpp"
    break;

  case 113: // expr_binary: expr "+" expr
#line 512 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_add>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2477 "parser.cpp"
    break;

  case 114: // expr_binary: expr "-" expr
#line 513 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_sub>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2483 "parser.cpp"
    break;

  case 115: // expr_binary: expr "*" expr
#line 514 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_mult>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2489 "parser.cpp"
    break;

  case 116: // expr_binary: expr "/" expr
#line 515 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_div>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2495 "parser.cpp"
    break;

  case 117: // expr_binary: expr "%" expr
#line 516 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_mod>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2501 "parser.cpp"
    break;

  case 118: // expr_primitive: "(" expr ")"
#line 520 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2507 "parser.cpp"
    break;

  case 119: // expr_primitive: "~" expr
#line 521 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_complement>(yylhs.location, std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2513 "parser.cpp"
    break;

  case 120: // expr_primitive: "!" expr
#line 522 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_not>(yylhs.location, std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2519 "parser.cpp"
    break;

  case 121: // expr_primitive: expr_call
#line 523 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2525 "parser.cpp"
    break;

  case 122: // expr_primitive: expr_call_thread
#line 524 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2531 "parser.cpp"
    break;

  case 123: // expr_primitive: expr_call_childthread
#line 525 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2537 "parser.cpp"
    break;

  case 124: // expr_primitive: expr_function
#line 526 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2543 "parser.cpp"
    break;

  case 125: // expr_primitive: expr_add_array
#line 527 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2549 "parser.cpp"
    break;

  case 126: // expr_primitive: expr_array
#line 528 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2555 "parser.cpp"
    break;

  case 127: // expr_primitive: expr_field
#line 529 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2561 "parser.cpp"
    break;

  case 128: // expr_primitive: expr_size
#line 530 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2567 "parser.cpp"
    break;

  case 129: // expr_primitive: thisthread
#line 531 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < thisthread_ptr > ()); }
#line 2573 "parser.cpp"
    break;

  case 130: // expr_primitive: empty_array
#line 532 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < empty_array_ptr > ()); }
#line 2579 "parser.cpp"
    break;

  case 131: // expr_primitive: undefined
#line 533 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < undefined_ptr > ()); }
#line 2585 "parser.cpp"
    break;

  case 132: // expr_primitive: game
#line 534 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < game_ptr > ()); }
#line 2591 "parser.cpp"
    break;

  case 133: // expr_primitive: self
#line 535 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < self_ptr > ()); }
#line 2597 "parser.cpp"
    break;

  case 134: // expr_primitive: anim
#line 536 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < anim_ptr > ()); }
#line 2603 "parser.cpp"
    break;

  case 135: // expr_primitive: level
#line 537 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < level_ptr > ()); }
#line 2609 "parser.cpp"
    break;

  case 136: // expr_primitive: animation
#line 538 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < animation_ptr > ()); }
#line 2615 "parser.cpp"
    break;

  case 137: // expr_primitive: animtree
#line 539 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < animtree_ptr > ()); }
#line 2621 "parser.cpp"
    break;

  case 138: // expr_primitive: name
#line 540 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < name_ptr > ()); }
#line 2627 "parser.cpp"
    break;

  case 139: // expr_primitive: istring
#line 541 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < istring_ptr > ()); }
#line 2633 "parser.cpp"
    break;

  case 140: // expr_primitive: string
#line 542 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < string_ptr > ()); }
#line 2639 "parser.cpp"
    break;

  case 141: // expr_primitive: vector
#line 543 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < vector_ptr > ()); }
#line 2645 "parser.cpp"
    break;

  case 142: // expr_primitive: neg_float
#line 544 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2651 "parser.cpp"
    break;

  case 143: // expr_primitive: neg_integer
#line 545 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2657 "parser.cpp"
    break;

  case 144: // expr_primitive: float
#line 546 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2663 "parser.cpp"
    break;

  case 145: // expr_primitive: integer
#line 547 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2669 "parser.cpp"
    break;

  case 146: // expr_primitive: false
#line 548 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < false_ptr > ()); }
#line 2675 "parser.cpp"
    break;

  case 147: // expr_primitive: true
#line 549 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < true_ptr > ()); }
#line 2681 "parser.cpp"
    break;

  case 148: // expr_call: expr_call_function
#line 553 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2687 "parser.cpp"
    break;

  case 149: // expr_call: expr_call_pointer
#line 554 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2693 "parser.cpp"
    break;

  case 150: // expr_call: object expr_call_function
#line 555 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2699 "parser.cpp"
    break;

  case 151: // expr_call: object expr_call_pointer
#line 556 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2705 "parser.cpp"
    break;

  case 152: // expr_call_thread: "thread" expr_call_function
#line 560 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2711 "parser.cpp"
    break;

  case 153: // expr_call_thread: "thread" expr_call_pointer
#line 561 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2717 "parser.cpp"
    break;

  case 154: // expr_call_thread: object "thread" expr_call_function
#line 562 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2723 "parser.cpp"
    break;

  case 155: // expr_call_thread: object "thread" expr_call_pointer
#line 563 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2729 "parser.cpp"
    break;

  case 156: // expr_call_childthread: "childthread" expr_call_function
#line 567 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2735 "parser.cpp"
    break;

  case 157: // expr_call_childthread: "childthread" expr_call_pointer
#line 568 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2741 "parser.cpp"
    break;

  case 158: // expr_call_childthread: object "childthread" expr_call_function
#line 569 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2747 "parser.cpp"
    break;

  case 159: // expr_call_childthread: object "childthread" expr_call_pointer
#line 570 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2753 "parser.cpp"
    break;

  case 160: // expr_call_function: name "(" expr_arguments ")"
#line 575 "parser.ypp"
        {yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(yylhs.location, std::make_unique<node_file>(), std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2759 "parser.cpp"
    break;

  case 161: // expr_call_function: file "::" name "(" expr_arguments ")"
#line 577 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(yylhs.location, std::move(yystack_[5].value.as < file_ptr > ()), std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2765 "parser.cpp"
    break;

  case 162: // expr_call_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 582 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_call_pointer>(yylhs.location, false, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2771 "parser.cpp"
    break;

  case 163: // expr_call_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 584 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_call_pointer>(yylhs.location, true, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2777 "parser.cpp"
    break;

  case 164: // expr_arguments: expr_arguments_filled
#line 588 "parser.ypp"
                            { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[0].value.as < expr_arguments_ptr > ()); }
#line 2783 "parser.cpp"
    break;

  case 165: // expr_arguments: expr_arguments_empty
#line 589 "parser.ypp"
                            { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[0].value.as < expr_arguments_ptr > ()); }
#line 2789 "parser.cpp"
    break;

  case 166: // expr_arguments_filled: expr_arguments "," expr
#line 594 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[2].value.as < expr_arguments_ptr > ()); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2795 "parser.cpp"
    break;

  case 167: // expr_arguments_filled: expr
#line 596 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(yylhs.location); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2801 "parser.cpp"
    break;

  case 168: // expr_arguments_empty: %empty
#line 601 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(yylhs.location); }
#line 2807 "parser.cpp"
    break;

  case 169: // expr_function: "::" name
#line 606 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function>(yylhs.location, std::make_unique<node_file>(yylhs.location), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2813 "parser.cpp"
    break;

  case 170: // expr_function: file "::" name
#line 608 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function>(yylhs.location, std::move(yystack_[2].value.as < file_ptr > ()), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2819 "parser.cpp"
    break;

  case 171: // expr_add_array: "[" expr_arguments_filled "]"
#line 613 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2825 "parser.cpp"
    break;

  case 172: // expr_array: object "[" expr "]"
#line 618 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_array>(yylhs.location, std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2831 "parser.cpp"
    break;

  case 173: // expr_field: object "." name
#line 623 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_field>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2837 "parser.cpp"
    break;

  case 174: // expr_size: object ".size"
#line 628 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_size>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2843 "parser.cpp"
    break;

  case 175: // object: expr_call
#line 632 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2849 "parser.cpp"
    break;

  case 176: // object: expr_array
#line 633 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2855 "parser.cpp"
    break;

  case 177: // object: expr_field
#line 634 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2861 "parser.cpp"
    break;

  case 178: // object: game
#line 635 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < game_ptr > ()); }
#line 2867 "parser.cpp"
    break;

  case 179: // object: self
#line 636 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < self_ptr > ()); }
#line 2873 "parser.cpp"
    break;

  case 180: // object: anim
#line 637 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < anim_ptr > ()); }
#line 2879 "parser.cpp"
    break;

  case 181: // object: level
#line 638 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < level_ptr > ()); }
#line 2885 "parser.cpp"
    break;

  case 182: // object: name
#line 639 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < name_ptr > ()); }
#line 2891 "parser.cpp"
    break;

  case 183: // thisthread: "thisthread"
#line 642 "parser.ypp"
                                                       { yylhs.value.as < thisthread_ptr > () = std::make_unique<node_thisthread>(yylhs.location); }
#line 2897 "parser.cpp"
    break;

  case 184: // empty_array: "[" "]"
#line 643 "parser.ypp"
                                                       { yylhs.value.as < empty_array_ptr > () = std::make_unique<node_empty_array>(yylhs.location); }
#line 2903 "parser.cpp"
    break;

  case 185: // undefined: "undefined"
#line 644 "parser.ypp"
                                                       { yylhs.value.as < undefined_ptr > () = std::make_unique<node_undefined>(yylhs.location); }
#line 2909 "parser.cpp"
    break;

  case 186: // game: "game"
#line 645 "parser.ypp"
                                                       { yylhs.value.as < game_ptr > () = std::make_unique<node_game>(yylhs.location); }
#line 2915 "parser.cpp"
    break;

  case 187: // self: "self"
#line 646 "parser.ypp"
                                                       { yylhs.value.as < self_ptr > () = std::make_unique<node_self>(yylhs.location); }
#line 2921 "parser.cpp"
    break;

  case 188: // anim: "anim"
#line 647 "parser.ypp"
                                                       { yylhs.value.as < anim_ptr > () = std::make_unique<node_anim>(yylhs.location); }
#line 2927 "parser.cpp"
    break;

  case 189: // level: "level"
#line 648 "parser.ypp"
                                                       { yylhs.value.as < level_ptr > () = std::make_unique<node_level>(yylhs.location); }
#line 2933 "parser.cpp"
    break;

  case 190: // animation: "%" "identifier"
#line 649 "parser.ypp"
                                                       { yylhs.value.as < animation_ptr > () = std::make_unique<node_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2939 "parser.cpp"
    break;

  case 191: // animtree: "#animtree"
#line 650 "parser.ypp"
                                                       { yylhs.value.as < animtree_ptr > () = std::make_unique<node_animtree>(yylhs.location); }
#line 2945 "parser.cpp"
    break;

  case 192: // name: "identifier"
#line 651 "parser.ypp"
                                                       { yylhs.value.as < name_ptr > () = std::make_unique<node_name>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2951 "parser.cpp"
    break;

  case 193: // file: "file path"
#line 652 "parser.ypp"
                                                       { yylhs.value.as < file_ptr > () = std::make_unique<node_file>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2957 "parser.cpp"
    break;

  case 194: // istring: "localized string"
#line 653 "parser.ypp"
                                                       { yylhs.value.as < istring_ptr > () = std::make_unique<node_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2963 "parser.cpp"
    break;

  case 195: // string: "string literal"
#line 654 "parser.ypp"
                                                       { yylhs.value.as < string_ptr > () = std::make_unique<node_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2969 "parser.cpp"
    break;

  case 196: // vector: "(" expr "," expr "," expr ")"
#line 655 "parser.ypp"
                                                       { yylhs.value.as < vector_ptr > () = std::make_unique<node_vector>(yylhs.location, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[3].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2975 "parser.cpp"
    break;

  case 197: // neg_float: "-" "float"
#line 656 "parser.ypp"
                                                       { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 2981 "parser.cpp"
    break;

  case 198: // neg_integer: "-" "int"
#line 657 "parser.ypp"
                                                       { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 2987 "parser.cpp"
    break;

  case 199: // float: "float"
#line 658 "parser.ypp"
                                                       { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2993 "parser.cpp"
    break;

  case 200: // integer: "int"
#line 659 "parser.ypp"
                                                       { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2999 "parser.cpp"
    break;

  case 201: // false: "false"
#line 660 "parser.ypp"
                                                       { yylhs.value.as < false_ptr > () = std::make_unique<node_false>(yylhs.location); }
#line 3005 "parser.cpp"
    break;

  case 202: // true: "true"
#line 661 "parser.ypp"
                                                       { yylhs.value.as < true_ptr > () = std::make_unique<node_true>(yylhs.location); }
#line 3011 "parser.cpp"
    break;


#line 3015 "parser.cpp"

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
  "notify", "wait", "waittill", "waittillmatch", "waittillframeend",
  "waitframe", "if", "else", "while", "for", "foreach", "in", "switch",
  "case", "default", "break", "continue", "return", "thread",
  "childthread", "thisthread", "call", "true", "false", "undefined",
  ".size", "game", "self", "anim", "level", "(", ")", "{", "}", "[", "]",
  ",", ".", "::", ":", ";", "++", "--", "<<", ">>", "||", "&&", "==", "!=",
  "<=", ">=", "<", ">", "!", "~", "=", "+=", "-=", "*=", "/=", "%=", "|=",
  "&=", "^=", ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/", "%",
  "file path", "identifier", "string literal", "localized string", "float",
  "int", "ADD_ARRAY", "THEN", "NEG", "ANIMREF", "PREINC", "PREDEC",
  "POSTINC", "POSTDEC", "$accept", "root", "program", "include", "define",
  "usingtree", "constant", "thread", "parameters", "stmt", "stmt_block",
  "stmt_list", "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify",
  "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_waitframe", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case",
  "stmt_default", "stmt_break", "stmt_continue", "stmt_return",
  "stmt_breakpoint", "stmt_prof_begin", "stmt_prof_end", "for_stmt",
  "for_expr", "expr", "expr_assign", "expr_compare", "expr_binary",
  "expr_primitive", "expr_call", "expr_call_thread",
  "expr_call_childthread", "expr_call_function", "expr_call_pointer",
  "expr_arguments", "expr_arguments_filled", "expr_arguments_empty",
  "expr_function", "expr_add_array", "expr_array", "expr_field",
  "expr_size", "object", "thisthread", "empty_array", "undefined", "game",
  "self", "anim", "level", "animation", "animtree", "name", "file",
  "istring", "string", "vector", "neg_float", "neg_integer", "float",
  "integer", "false", "true", YY_NULLPTR
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

#if S1DEBUG
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
#if S1DEBUG
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
#if S1DEBUG
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


  const short parser::yypact_ninf_ = -236;

  const short parser::yytable_ninf_ = -183;

  const short
  parser::yypact_[] =
  {
       8,   -65,    -6,  -236,    25,     8,  -236,  -236,  -236,  -236,
    -236,   -32,  -236,    -8,   -28,  -236,  -236,  -236,   -17,   774,
    -236,  -236,    21,    30,  -236,  -236,     6,     6,  -236,    51,
    -236,  -236,  -236,  -236,  -236,  -236,  -236,   774,   377,   -17,
     774,   774,    10,    -3,  -236,  -236,  -236,  1403,  -236,  -236,
    -236,    20,  -236,  -236,  -236,  -236,  -236,  -236,   403,   449,
    -236,   472,  -236,  -236,  -236,   739,   798,   858,   930,  -236,
    -236,    12,    17,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,    24,    50,   -17,    63,  -236,  -236,    76,    79,
    -236,  -236,    80,   967,   377,  -236,  1481,    71,    89,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,  -236,   774,   774,   774,
     774,   774,   774,   774,   774,   774,   774,   774,   774,   774,
     774,   774,   774,   774,   774,     6,     6,  -236,   836,   -17,
    -236,  -236,   774,   -17,  -236,   599,  -236,  -236,   774,   -17,
     774,  -236,   774,  1274,   774,  -236,   106,   106,  1491,  1000,
    1563,  1563,   130,   130,   130,   130,  1043,  1532,  1522,   -37,
     -37,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  1313,  -236,
      31,  -236,    96,    87,   101,   104,   774,    88,   -20,   123,
     124,   127,   131,   134,   -26,   121,   147,   152,   712,  -236,
     -15,   -15,  -236,  -236,   643,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,   153,   155,
     157,  -236,  -236,   882,  -236,  -236,  -236,  -236,    76,  1274,
      96,  1352,  1390,   132,  1481,  -236,  -236,   774,  -236,   774,
     774,  1437,  -236,   140,  -236,   774,   774,   544,   -17,   774,
     117,   159,   166,   172,  -236,  -236,  -236,  -236,  1450,  -236,
     173,   173,  -236,  -236,  -236,  -236,  -236,   182,   184,   187,
     189,  -236,  -236,   774,   774,   774,   774,   774,   774,   774,
     774,   774,   774,   774,   186,   774,   199,    39,    40,    42,
    -236,   190,  1106,  1139,   191,  -236,   932,   -11,  1149,  -236,
    -236,  -236,  -236,   774,   774,   774,   774,  1481,  1481,  1481,
    1481,  1481,  1481,  1481,  1481,  1481,  1481,  1481,   205,  1182,
     774,  -236,   196,   200,  -236,   687,   687,   774,   774,   -17,
      50,  1192,  1010,  1053,  1096,   774,  -236,    48,  -236,  -236,
     225,  -236,   203,  1481,  1225,   234,  -236,   206,   209,   774,
     212,   774,   213,   774,    65,  -236,   687,   544,   687,   774,
    -236,  -236,    69,  -236,    73,  -236,    82,  -236,  -236,   223,
    -236,  1235,   217,   220,   222,   687,   687,  -236,  -236,  -236,
    -236,  -236
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,   192,     0,     2,     6,     7,     9,    10,
      11,     0,   193,     0,     0,     1,     4,     5,    17,     0,
       8,   195,     0,     0,    16,   191,     0,     0,   183,     0,
     202,   201,   185,   186,   187,   188,   189,     0,   168,     0,
       0,     0,     0,     0,   194,   199,   200,     0,    82,    83,
      84,   121,   122,   123,   148,   149,   124,   125,   126,   127,
     128,     0,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,     0,   139,   140,   141,   142,   143,   144,   145,
     146,   147,     0,     0,     0,     0,   152,   153,     0,     0,
     156,   157,     0,     0,   168,   184,   167,     0,   164,   165,
     169,   120,   119,   197,   198,   190,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   174,     0,     0,
     150,   151,   168,     0,    12,     0,    14,    15,     0,     0,
       0,   118,     0,   167,     0,   171,   111,   112,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   113,
     114,   115,   116,   117,   154,   155,   158,   159,     0,   173,
       0,   164,   170,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
       0,     0,    45,    18,     0,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,     0,   175,
       0,   176,   177,     0,   178,   179,   180,   181,   182,     0,
       0,     0,     0,     0,   166,   172,   160,   168,    75,   168,
     168,     0,    57,     0,    58,     0,     0,    79,     0,     0,
       0,     0,     0,     0,    70,    71,    72,    74,     0,   175,
      85,    86,    42,    44,    48,    46,    47,     0,     0,     0,
       0,    87,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,     0,     0,     0,     0,    78,     0,     0,     0,    69,
      68,    67,    73,     0,     0,     0,     0,    89,    95,    96,
      97,    98,    99,    90,    91,    92,    94,    93,     0,     0,
     168,   161,     0,     0,    59,     0,     0,    81,     0,     0,
       0,     0,     0,     0,     0,   168,   196,     0,    76,    77,
      60,    62,     0,    80,     0,     0,    66,     0,     0,   168,
       0,   168,     0,   168,     0,   162,     0,    79,     0,     0,
      49,    51,     0,    54,     0,    56,     0,   163,    61,     0,
      64,     0,     0,     0,     0,     0,     0,    50,    53,    55,
      63,    65
  };

  const short
  parser::yypgoto_[] =
  {
    -236,  -236,  -236,   272,   273,  -236,  -236,  -236,  -236,  -183,
     -76,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,  -236,   -78,  -236,    38,  -235,  -236,
    -236,  -236,   -82,  -107,  -236,   -25,   -23,  -119,   -21,  -236,
    -236,  -236,   -22,    98,  -236,   156,  -236,  -236,  -236,   192,
     197,   202,   236,  -236,  -236,     0,     5,  -236,    -5,  -236,
    -236,    97,  -236,   102,  -236,  -236
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,     8,     9,    10,    23,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   294,   342,    96,   218,    48,
      49,    50,    51,    52,    53,    54,    55,    97,   171,    99,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81
  };

  const short
  parser::yytable_[] =
  {
      11,    86,    90,    87,    91,    11,    13,   136,    18,    22,
     328,   263,   295,   170,     1,     2,    29,    98,    24,    12,
     243,    33,    34,    35,    36,    15,    88,    88,   220,    85,
     244,    89,    89,    19,    14,   329,   130,    29,   131,   100,
    -182,  -182,    20,  -182,   122,   123,   124,  -182,  -175,  -175,
      85,  -175,   132,   219,   250,  -175,  -182,    47,    21,  -182,
      21,    88,    82,    46,  -175,   133,    89,  -175,     3,    12,
       3,    83,   236,    98,   134,    93,    84,   144,   101,   102,
     321,   322,   105,   323,   137,   144,   144,   220,   144,   355,
      12,     3,   135,     3,   144,    92,  -182,  -182,   103,   104,
     164,   166,   165,   167,  -175,  -175,   367,   138,   259,   259,
     372,   144,   219,   221,   373,   144,   132,   144,   287,   144,
     288,   289,   295,   374,   140,    88,    88,   139,   144,   169,
      89,    89,   143,   172,   145,   228,   237,   238,   242,   230,
      89,   239,   340,   341,   240,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   245,   246,   259,   168,   247,   221,   221,
     254,   248,   221,   368,   249,   370,   229,   286,   231,   251,
     232,   291,   234,   107,   108,   120,   121,   122,   123,   124,
     228,   228,   380,   381,   228,    89,    89,   255,   130,    89,
     131,   337,   256,   264,    29,   265,   104,   266,   299,   120,
     121,   122,   123,   124,   241,   300,   354,   128,   220,   220,
     129,   301,   303,    88,   304,   221,   258,   305,    89,   306,
     362,   318,   364,   222,   366,   130,   130,   131,   131,   320,
     324,   327,   356,   219,   219,   335,   338,   228,   297,   220,
     339,   220,    89,   357,   346,   359,   360,    12,     3,   361,
      88,    88,   363,   365,   375,    89,    89,   377,   220,   220,
     378,   130,   379,   131,   219,   259,   219,    16,    17,   369,
       0,   252,     0,   292,   293,     0,   253,   298,   222,   222,
       0,   223,   222,   219,   219,     0,    88,     0,     0,     0,
       0,    89,     0,   221,   221,     0,     0,     0,     0,     0,
       0,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,     0,   319,     0,   228,   228,   224,     0,   345,
      89,    89,   225,     0,   221,   221,   221,   226,     0,     0,
       0,   331,   332,   333,   334,   222,   260,   261,     0,     0,
     223,     0,     0,   221,   221,     0,   228,   228,   228,     0,
       0,    89,    89,    89,     0,   343,   344,     0,     0,     0,
       0,   227,     0,     0,     0,   228,   228,     0,     0,     0,
      89,    89,   224,   224,     0,    25,   224,   225,   225,     0,
       0,   225,   226,   226,     0,     0,   226,   371,     0,     0,
       0,     0,     0,   296,     0,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,    35,    36,    37,     0,     0,
       0,    94,    95,   222,   222,    39,   227,   227,     0,     0,
     227,  -176,  -176,     0,  -176,     0,     0,     0,  -176,   224,
      40,    41,     0,     0,   225,     0,     0,  -176,     0,   226,
    -176,     0,     0,     0,   222,   222,   222,    42,     0,     0,
      43,    12,     3,    21,    44,    45,    46,     0,     0,     0,
       0,     0,     0,   222,   222,     0,     0,  -177,  -177,     0,
    -177,   223,   223,   227,  -177,     0,     0,  -176,  -176,     0,
       0,     0,     0,  -177,     0,     0,  -177,     0,     0,     0,
     125,   126,     0,    29,     0,     0,     0,   127,     0,     0,
       0,     0,   223,   296,   223,     0,   128,   224,   224,   129,
       0,     0,   225,   225,     0,     0,     0,   226,   226,     0,
       0,   223,   223,  -177,  -177,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   224,   224,
     224,     0,     0,   225,   225,   225,    12,     3,   226,   226,
     226,   227,   227,     0,     0,     0,     0,   224,   224,     0,
       0,     0,   225,   225,     0,    29,     0,   226,   226,     0,
      33,    34,    35,    36,     0,     0,     0,     0,    85,     0,
       0,     0,   227,   227,   227,   190,   191,     0,     0,     0,
       0,     0,   173,   174,   175,     0,     0,     0,     0,     0,
     176,   227,   227,   177,   178,   179,     0,   180,   181,   182,
       0,   183,   184,   185,   186,   187,   188,    26,    12,     3,
      29,     0,     0,     0,     0,    33,    34,    35,    36,     0,
       0,   135,   189,    85,     0,     0,   173,   174,   175,     0,
     190,   191,     0,     0,   176,     0,     0,   177,   178,   179,
       0,   180,   181,   182,     0,   183,   184,   185,   186,   187,
     188,    26,     0,     0,    29,     0,     0,     0,     0,    33,
      34,    35,    36,    12,     3,   135,   262,    85,     0,     0,
     173,   174,   175,     0,   190,   191,     0,     0,   176,     0,
       0,   177,   178,   179,     0,   180,   181,   182,     0,   183,
     184,   185,   186,   187,   188,    26,     0,     0,    29,     0,
      25,     0,     0,    33,    34,    35,    36,    12,     3,   135,
       0,    85,     0,     0,     0,     0,     0,     0,   190,   191,
      26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
      35,    36,    37,     0,     0,     0,    38,     0,     0,     0,
      39,     0,   257,     0,     0,     0,     0,  -178,  -178,     0,
    -178,    12,     3,     0,  -178,    40,    41,     0,     0,     0,
       0,     0,    25,  -178,     0,     0,  -178,     0,     0,     0,
       0,     0,    42,     0,     0,    43,    12,     3,    21,    44,
      45,    46,    26,    27,    28,    29,    30,    31,    32,     0,
      33,    34,    35,    36,    37,     0,     0,     0,    38,     0,
       0,     0,    39,  -178,  -178,     0,  -179,  -179,     0,  -179,
       0,     0,     0,  -179,     0,     0,     0,    40,    41,     0,
       0,     0,  -179,     0,    25,  -179,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,    43,    12,     3,
      21,    44,    45,    46,    26,    27,    28,    29,    30,    31,
      32,     0,    33,    34,    35,    36,    37,     0,     0,     0,
      94,     0,  -179,  -179,    39,     0,  -180,  -180,     0,  -180,
       0,   267,   268,  -180,   269,   270,     0,     0,     0,    40,
      41,     0,  -180,     0,     0,  -180,     0,     0,     0,     0,
     125,     0,     0,    29,     0,     0,    42,     0,     0,    43,
      12,     3,    21,    44,    45,    46,   128,     0,     0,   129,
       0,     0,     0,   271,   272,     0,     0,     0,     0,     0,
       0,     0,  -180,  -180,     0,     0,     0,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,  -181,  -181,
       0,  -181,     0,    29,     0,  -181,    12,     3,     0,     0,
       0,     0,     0,     0,  -181,     0,   128,  -181,     0,   129,
       0,     0,     0,   271,   272,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   141,     0,
       0,     0,     0,   142,  -181,  -181,    12,     3,     0,     0,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   348,     0,   107,   108,     0,   349,   111,   112,   113,
     114,   115,   116,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   350,     0,   107,   108,     0,   351,
     111,   112,   113,   114,   115,   116,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,     0,     0,     0,     0,
     118,   119,   120,   121,   122,   123,   124,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   352,     0,     0,
       0,     0,   353,     0,     0,     0,     0,   325,     0,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,     0,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     326,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     330,     0,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,     0,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   336,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   347,     0,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   358,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   376,     0,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   233,
       0,     0,     0,     0,     0,     0,     0,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,   119,   120,   121,   122,   123,   124,   235,     0,
       0,     0,     0,     0,     0,     0,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   284,     0,     0,
       0,     0,     0,     0,     0,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   285,     0,     0,     0,
       0,     0,     0,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   106,     0,     0,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   290,     0,     0,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     302,     0,     0,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,     0,     0,     0,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   107,   108,     0,   110,   111,   112,
     113,   114,   115,   116,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   107,   108,     0,     0,   111,
     112,   113,   114,   115,   116,   107,   108,     0,     0,   111,
     112,   113,   114,   115,   116,     0,     0,     0,     0,   118,
       0,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,   120,   121,   122,   123,   124,   107,   108,     0,     0,
       0,     0,   113,   114,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,   121,   122,   123,   124
  };

  const short
  parser::yycheck_[] =
  {
       0,    26,    27,    26,    27,     5,     1,    83,    40,    14,
      21,   194,   247,   132,     6,     7,    31,    38,    18,    84,
      40,    36,    37,    38,    39,     0,    26,    27,   135,    44,
      50,    26,    27,    65,    40,    46,    61,    31,    61,    39,
      28,    29,    50,    31,    81,    82,    83,    35,    28,    29,
      44,    31,    40,   135,    80,    35,    44,    19,    86,    47,
      86,    61,    41,    89,    44,    48,    61,    47,    85,    84,
      85,    41,    41,    94,    50,    37,    46,    46,    40,    41,
      41,    41,    85,    41,    84,    46,    46,   194,    46,    41,
      84,    85,    42,    85,    46,    44,    84,    85,    88,    89,
     125,   126,   125,   126,    84,    85,    41,    44,   190,   191,
      41,    46,   194,   135,    41,    46,    40,    46,   237,    46,
     239,   240,   357,    41,    44,   125,   126,    48,    46,   129,
     125,   126,    94,   133,    45,   135,    40,    50,    50,   139,
     135,    40,   325,   326,    40,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,    40,    40,   247,   128,    40,   190,   191,
      49,    40,   194,   356,    40,   358,   138,    45,   140,   184,
     142,    41,   144,    53,    54,    79,    80,    81,    82,    83,
     190,   191,   375,   376,   194,   190,   191,    50,   223,   194,
     223,   320,    50,    50,    31,    50,    89,    50,    49,    79,
      80,    81,    82,    83,   176,    49,   335,    44,   325,   326,
      47,    49,    40,   223,    40,   247,   188,    40,   223,    40,
     349,    45,   351,   135,   353,   260,   261,   260,   261,    40,
      50,    50,    17,   325,   326,    40,    50,   247,   248,   356,
      50,   358,   247,    50,   330,    21,    50,    84,    85,    50,
     260,   261,    50,    50,    41,   260,   261,    50,   375,   376,
      50,   296,    50,   296,   356,   357,   358,     5,     5,   357,
      -1,   184,    -1,   245,   246,    -1,   184,   249,   190,   191,
      -1,   135,   194,   375,   376,    -1,   296,    -1,    -1,    -1,
      -1,   296,    -1,   325,   326,    -1,    -1,    -1,    -1,    -1,
      -1,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,    -1,   285,    -1,   325,   326,   135,    -1,   329,
     325,   326,   135,    -1,   356,   357,   358,   135,    -1,    -1,
      -1,   303,   304,   305,   306,   247,   190,   191,    -1,    -1,
     194,    -1,    -1,   375,   376,    -1,   356,   357,   358,    -1,
      -1,   356,   357,   358,    -1,   327,   328,    -1,    -1,    -1,
      -1,   135,    -1,    -1,    -1,   375,   376,    -1,    -1,    -1,
     375,   376,   190,   191,    -1,     8,   194,   190,   191,    -1,
      -1,   194,   190,   191,    -1,    -1,   194,   359,    -1,    -1,
      -1,    -1,    -1,   247,    -1,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    44,    45,   325,   326,    48,   190,   191,    -1,    -1,
     194,    28,    29,    -1,    31,    -1,    -1,    -1,    35,   247,
      63,    64,    -1,    -1,   247,    -1,    -1,    44,    -1,   247,
      47,    -1,    -1,    -1,   356,   357,   358,    80,    -1,    -1,
      83,    84,    85,    86,    87,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,   375,   376,    -1,    -1,    28,    29,    -1,
      31,   325,   326,   247,    35,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    47,    -1,    -1,    -1,
      28,    29,    -1,    31,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    -1,   356,   357,   358,    -1,    44,   325,   326,    47,
      -1,    -1,   325,   326,    -1,    -1,    -1,   325,   326,    -1,
      -1,   375,   376,    84,    85,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,   357,
     358,    -1,    -1,   356,   357,   358,    84,    85,   356,   357,
     358,   325,   326,    -1,    -1,    -1,    -1,   375,   376,    -1,
      -1,    -1,   375,   376,    -1,    31,    -1,   375,   376,    -1,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,   356,   357,   358,    51,    52,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,
      11,   375,   376,    14,    15,    16,    -1,    18,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    84,    85,
      31,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    -1,
      -1,    42,    43,    44,    -1,    -1,     3,     4,     5,    -1,
      51,    52,    -1,    -1,    11,    -1,    -1,    14,    15,    16,
      -1,    18,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    84,    85,    42,    43,    44,    -1,    -1,
       3,     4,     5,    -1,    51,    52,    -1,    -1,    11,    -1,
      -1,    14,    15,    16,    -1,    18,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    31,    -1,
       8,    -1,    -1,    36,    37,    38,    39,    84,    85,    42,
      -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      48,    -1,    50,    -1,    -1,    -1,    -1,    28,    29,    -1,
      31,    84,    85,    -1,    35,    63,    64,    -1,    -1,    -1,
      -1,    -1,     8,    44,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    83,    84,    85,    86,    87,
      88,    89,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    48,    84,    85,    -1,    28,    29,    -1,    31,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    63,    64,    -1,
      -1,    -1,    44,    -1,     8,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    83,    84,    85,
      86,    87,    88,    89,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      44,    -1,    84,    85,    48,    -1,    28,    29,    -1,    31,
      -1,     9,    10,    35,    12,    13,    -1,    -1,    -1,    63,
      64,    -1,    44,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    31,    -1,    -1,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    44,    -1,    -1,    47,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    28,    29,
      -1,    31,    -1,    31,    -1,    35,    84,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    44,    47,    -1,    47,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    41,    -1,
      -1,    -1,    -1,    46,    84,    85,    84,    85,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    41,    -1,    53,    54,    -1,    46,    57,    58,    59,
      60,    61,    62,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,    83,    41,    -1,    53,    54,    -1,    46,
      57,    58,    59,    60,    61,    62,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    41,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    41,    -1,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      41,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      41,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    41,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    41,    -1,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    41,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    41,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78,    79,    80,    81,    82,    83,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    50,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    50,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      50,    -1,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,    83,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    53,    54,    -1,    56,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    53,    54,    -1,    -1,    57,
      58,    59,    60,    61,    62,    53,    54,    -1,    -1,    57,
      58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,    77,
      -1,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      -1,    79,    80,    81,    82,    83,    53,    54,    -1,    -1,
      -1,    -1,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    81,    82,    83
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     6,     7,    85,    99,   100,   101,   102,   103,   104,
     105,   163,    84,   164,    40,     0,   101,   102,    40,    65,
      50,    86,   166,   106,   163,     8,    28,    29,    30,    31,
      32,    33,    34,    36,    37,    38,    39,    40,    44,    48,
      63,    64,    80,    83,    87,    88,    89,   135,   137,   138,
     139,   140,   141,   142,   143,   144,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,    41,    41,    46,    44,   143,   144,   163,   164,
     143,   144,    44,   135,    44,    45,   135,   145,   146,   147,
     163,   135,   135,    88,    89,    85,    50,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    76,    77,    78,
      79,    80,    81,    82,    83,    28,    29,    35,    44,    47,
     143,   144,    40,    48,    50,    42,   108,   163,    44,    48,
      44,    41,    46,   135,    46,    45,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   143,   144,   143,   144,   135,   163,
     145,   146,   163,     3,     4,     5,    11,    14,    15,    16,
      18,    19,    20,    22,    23,    24,    25,    26,    27,    43,
      51,    52,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   136,   140,
     141,   150,   151,   153,   157,   158,   159,   160,   163,   135,
     163,   135,   135,    45,   135,    45,    41,    40,    50,    40,
      40,   135,    50,    40,    50,    40,    40,    40,    40,    40,
      80,   166,   169,   171,    49,    50,    50,    50,   135,   140,
     153,   153,    43,   107,    50,    50,    50,     9,    10,    12,
      13,    51,    52,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    45,    46,    45,   145,   145,   145,
      50,    41,   135,   135,   133,   136,   153,   163,   135,    49,
      49,    49,    50,    40,    40,    40,    40,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,    45,   135,
      40,    41,    41,    41,    50,    41,    41,    50,    21,    46,
      41,   135,   135,   135,   135,    40,    41,   145,    50,    50,
     107,   107,   134,   135,   135,   163,   108,    41,    41,    46,
      41,    46,    41,    46,   145,    41,    17,    50,    41,    21,
      50,    50,   145,    50,   145,    50,   145,    41,   107,   133,
     107,   135,    41,    41,    41,    41,    41,    50,    50,    50,
     107,   107
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    98,    99,    99,   100,   100,   100,   100,   101,   102,
     102,   102,   103,   104,   105,   106,   106,   106,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   108,   108,   109,   109,   110,   110,   111,   112,
     113,   113,   114,   115,   115,   116,   116,   117,   118,   118,
     119,   120,   121,   122,   123,   123,   124,   125,   125,   125,
     126,   127,   128,   129,   129,   130,   131,   132,   133,   133,
     134,   134,   135,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     137,   137,   137,   137,   137,   137,   137,   137,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   140,   140,
     140,   140,   141,   141,   141,   141,   142,   142,   142,   142,
     143,   143,   144,   144,   145,   145,   146,   146,   147,   148,
     148,   149,   150,   151,   152,   153,   153,   153,   153,   153,
     153,   153,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     1,     1,     3,     1,
       1,     1,     5,     4,     5,     3,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     2,     1,     2,     2,     2,     6,
       8,     6,     3,     8,     6,     8,     6,     2,     2,     4,
       5,     7,     5,     9,     7,     9,     5,     3,     3,     3,
       2,     2,     2,     3,     2,     2,     5,     5,     1,     0,
       1,     0,     1,     1,     1,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     3,     3,     2,     2,     3,     3,
       4,     6,     8,     9,     1,     1,     3,     1,     0,     2,
       3,     3,     4,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     7,     2,     2,     1,
       1,     1,     1
  };




#if S1DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   239,   239,   240,   244,   246,   248,   250,   255,   260,
     261,   262,   266,   271,   276,   281,   283,   286,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   317,   318,   322,   324,   329,   331,   336,   341,
     346,   348,   353,   358,   360,   365,   367,   372,   377,   379,
     384,   389,   394,   399,   404,   406,   411,   416,   418,   420,
     425,   430,   435,   440,   442,   447,   452,   457,   462,   463,
     467,   468,   472,   473,   474,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     496,   497,   498,   499,   500,   501,   502,   503,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   520,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   553,   554,
     555,   556,   560,   561,   562,   563,   567,   568,   569,   570,
     574,   576,   581,   583,   588,   589,   593,   595,   601,   605,
     607,   612,   617,   622,   627,   632,   633,   634,   635,   636,
     637,   638,   639,   642,   643,   644,   645,   646,   647,   648,
     649,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   660,   661
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
#endif // S1DEBUG


#line 13 "parser.ypp"
} } } // xsk::gsc::s1
#line 4106 "parser.cpp"

#line 663 "parser.ypp"


void xsk::gsc::s1::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
