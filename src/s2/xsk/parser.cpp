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
xsk::gsc::s2::parser::symbol_type S2lex(yyscan_t yyscanner, xsk::gsc::location& loc);

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
  parser::parser (yyscan_t yyscanner_yyarg, xsk::gsc::location& loc_yyarg, xsk::gsc::program_ptr& ast_yyarg)
#if S2DEBUG
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
#line 233 "parser.ypp"
              { ast = std::move(yystack_[0].value.as < program_ptr > ()); }
#line 1751 "parser.cpp"
    break;

  case 3: // root: %empty
#line 234 "parser.ypp"
              { ast = std::make_unique<node_program>(yylhs.location); }
#line 1757 "parser.cpp"
    break;

  case 4: // program: program include
#line 239 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::move(yystack_[1].value.as < program_ptr > ()); yylhs.value.as < program_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1763 "parser.cpp"
    break;

  case 5: // program: program define
#line 241 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::move(yystack_[1].value.as < program_ptr > ()); yylhs.value.as < program_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < define_ptr > ())); }
#line 1769 "parser.cpp"
    break;

  case 6: // program: include
#line 243 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::make_unique<node_program>(yylhs.location); yylhs.value.as < program_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1775 "parser.cpp"
    break;

  case 7: // program: define
#line 245 "parser.ypp"
        { yylhs.value.as < program_ptr > () = std::make_unique<node_program>(yylhs.location); yylhs.value.as < program_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < define_ptr > ())); }
#line 1781 "parser.cpp"
    break;

  case 8: // include: "#include" file ";"
#line 250 "parser.ypp"
        { yylhs.value.as < include_ptr > () = std::make_unique<node_include>(yylhs.location, std::move(yystack_[1].value.as < file_ptr > ())); }
#line 1787 "parser.cpp"
    break;

  case 9: // define: usingtree
#line 254 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_usingtree = std::move(yystack_[0].value.as < usingtree_ptr > ()); }
#line 1793 "parser.cpp"
    break;

  case 10: // define: constant
#line 255 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_constant = std::move(yystack_[0].value.as < constant_ptr > ()); }
#line 1799 "parser.cpp"
    break;

  case 11: // define: thread
#line 256 "parser.ypp"
                   { yylhs.value.as < define_ptr > ().as_thread = std::move(yystack_[0].value.as < thread_ptr > ()); }
#line 1805 "parser.cpp"
    break;

  case 12: // usingtree: "#using_animtree" "(" string ")" ";"
#line 261 "parser.ypp"
        { yylhs.value.as < usingtree_ptr > () = std::make_unique<node_usingtree>(yylhs.location, std::move(yystack_[2].value.as < string_ptr > ())); }
#line 1811 "parser.cpp"
    break;

  case 13: // constant: name "=" expr ";"
#line 266 "parser.ypp"
        { yylhs.value.as < constant_ptr > () = std::make_unique<node_constant>(yylhs.location, std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 1817 "parser.cpp"
    break;

  case 14: // thread: name "(" parameters ")" stmt_block
#line 271 "parser.ypp"
        { yylhs.value.as < thread_ptr > () = std::make_unique<node_thread>(yylhs.location, std::move(yystack_[4].value.as < name_ptr > ()), std::move(yystack_[2].value.as < parameters_ptr > ()), std::move(yystack_[0].value.as < stmt_list_ptr > ())); }
#line 1823 "parser.cpp"
    break;

  case 15: // parameters: parameters "," name
#line 276 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::move(yystack_[2].value.as < parameters_ptr > ()); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < name_ptr > ())); }
#line 1829 "parser.cpp"
    break;

  case 16: // parameters: name
#line 278 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(yylhs.location); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < name_ptr > ())); }
#line 1835 "parser.cpp"
    break;

  case 17: // parameters: %empty
#line 280 "parser.ypp"
        { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(yylhs.location); }
#line 1841 "parser.cpp"
    break;

  case 18: // stmt: stmt_block
#line 284 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_list = std::move(yystack_[0].value.as < stmt_list_ptr > ()); }
#line 1847 "parser.cpp"
    break;

  case 19: // stmt: stmt_call
#line 285 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_call = std::move(yystack_[0].value.as < stmt_call_ptr > ()); }
#line 1853 "parser.cpp"
    break;

  case 20: // stmt: stmt_assign
#line 286 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < stmt_assign_ptr > ()); }
#line 1859 "parser.cpp"
    break;

  case 21: // stmt: stmt_endon
#line 287 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < stmt_endon_ptr > ()); }
#line 1865 "parser.cpp"
    break;

  case 22: // stmt: stmt_notify
#line 288 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < stmt_notify_ptr > ()); }
#line 1871 "parser.cpp"
    break;

  case 23: // stmt: stmt_wait
#line 289 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < stmt_wait_ptr > ()); }
#line 1877 "parser.cpp"
    break;

  case 24: // stmt: stmt_waittill
#line 290 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < stmt_waittill_ptr > ()); }
#line 1883 "parser.cpp"
    break;

  case 25: // stmt: stmt_waittillmatch
#line 291 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < stmt_waittillmatch_ptr > ()); }
#line 1889 "parser.cpp"
    break;

  case 26: // stmt: stmt_waittillframeend
#line 292 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < stmt_waittillframeend_ptr > ()); }
#line 1895 "parser.cpp"
    break;

  case 27: // stmt: stmt_waitframe
#line 293 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_waitframe = std::move(yystack_[0].value.as < stmt_waitframe_ptr > ()); }
#line 1901 "parser.cpp"
    break;

  case 28: // stmt: stmt_if
#line 294 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_if = std::move(yystack_[0].value.as < stmt_if_ptr > ()); }
#line 1907 "parser.cpp"
    break;

  case 29: // stmt: stmt_ifelse
#line 295 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < stmt_ifelse_ptr > ()); }
#line 1913 "parser.cpp"
    break;

  case 30: // stmt: stmt_while
#line 296 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_while = std::move(yystack_[0].value.as < stmt_while_ptr > ()); }
#line 1919 "parser.cpp"
    break;

  case 31: // stmt: stmt_for
#line 297 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_for = std::move(yystack_[0].value.as < stmt_for_ptr > ()); }
#line 1925 "parser.cpp"
    break;

  case 32: // stmt: stmt_foreach
#line 298 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < stmt_foreach_ptr > ()); }
#line 1931 "parser.cpp"
    break;

  case 33: // stmt: stmt_switch
#line 299 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < stmt_switch_ptr > ()); }
#line 1937 "parser.cpp"
    break;

  case 34: // stmt: stmt_case
#line 300 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_case = std::move(yystack_[0].value.as < stmt_case_ptr > ()); }
#line 1943 "parser.cpp"
    break;

  case 35: // stmt: stmt_default
#line 301 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_default = std::move(yystack_[0].value.as < stmt_default_ptr > ()); }
#line 1949 "parser.cpp"
    break;

  case 36: // stmt: stmt_break
#line 302 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_break = std::move(yystack_[0].value.as < stmt_break_ptr > ()); }
#line 1955 "parser.cpp"
    break;

  case 37: // stmt: stmt_continue
#line 303 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < stmt_continue_ptr > ()); }
#line 1961 "parser.cpp"
    break;

  case 38: // stmt: stmt_return
#line 304 "parser.ypp"
                             { yylhs.value.as < stmt_ptr > ().as_return = std::move(yystack_[0].value.as < stmt_return_ptr > ()); }
#line 1967 "parser.cpp"
    break;

  case 39: // stmt_block: "{" stmt_list "}"
#line 308 "parser.ypp"
                              { yylhs.value.as < stmt_list_ptr > () = std::move(yystack_[1].value.as < stmt_list_ptr > ()); }
#line 1973 "parser.cpp"
    break;

  case 40: // stmt_block: "{" "}"
#line 309 "parser.ypp"
                    { yylhs.value.as < stmt_list_ptr > () = std::make_unique<node_stmt_list>(yylhs.location); }
#line 1979 "parser.cpp"
    break;

  case 41: // stmt_list: stmt_list stmt
#line 314 "parser.ypp"
        { yylhs.value.as < stmt_list_ptr > () = std::move(yystack_[1].value.as < stmt_list_ptr > ()); yylhs.value.as < stmt_list_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 1985 "parser.cpp"
    break;

  case 42: // stmt_list: stmt
#line 316 "parser.ypp"
        { yylhs.value.as < stmt_list_ptr > () = std::make_unique<node_stmt_list>(yylhs.location); yylhs.value.as < stmt_list_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 1991 "parser.cpp"
    break;

  case 43: // stmt_call: expr_call ";"
#line 321 "parser.ypp"
        { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(yylhs.location, std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 1997 "parser.cpp"
    break;

  case 44: // stmt_call: expr_call_thread ";"
#line 323 "parser.ypp"
        { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(yylhs.location, std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 2003 "parser.cpp"
    break;

  case 45: // stmt_assign: expr_assign ";"
#line 328 "parser.ypp"
        { yylhs.value.as < stmt_assign_ptr > () = std::make_unique<node_stmt_assign>(yylhs.location, std::move(yystack_[1].value.as < expr_assign_ptr > ())); }
#line 2009 "parser.cpp"
    break;

  case 46: // stmt_endon: object "endon" "(" expr ")" ";"
#line 333 "parser.ypp"
        { yylhs.value.as < stmt_endon_ptr > () = std::make_unique<node_stmt_endon>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ())); }
#line 2015 "parser.cpp"
    break;

  case 47: // stmt_notify: object "notify" "(" expr "," expr_arguments ")" ";"
#line 338 "parser.ypp"
        { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2021 "parser.cpp"
    break;

  case 48: // stmt_notify: object "notify" "(" expr ")" ";"
#line 340 "parser.ypp"
        { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2027 "parser.cpp"
    break;

  case 49: // stmt_wait: "wait" expr ";"
#line 345 "parser.ypp"
        { yylhs.value.as < stmt_wait_ptr > () = std::make_unique<node_stmt_wait>(yylhs.location, std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2033 "parser.cpp"
    break;

  case 50: // stmt_waittill: object "waittill" "(" expr "," expr_arguments ")" ";"
#line 350 "parser.ypp"
        { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2039 "parser.cpp"
    break;

  case 51: // stmt_waittill: object "waittill" "(" expr ")" ";"
#line 352 "parser.ypp"
        { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2045 "parser.cpp"
    break;

  case 52: // stmt_waittillmatch: object "waittillmatch" "(" expr "," expr_arguments ")" ";"
#line 357 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(yylhs.location, std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 2051 "parser.cpp"
    break;

  case 53: // stmt_waittillmatch: object "waittillmatch" "(" expr ")" ";"
#line 359 "parser.ypp"
        { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(yylhs.location, std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_ptr > ()), std::make_unique<node_expr_arguments>(yylhs.location)); }
#line 2057 "parser.cpp"
    break;

  case 54: // stmt_waittillframeend: "waittillframeend" ";"
#line 364 "parser.ypp"
        { yylhs.value.as < stmt_waittillframeend_ptr > () = std::make_unique<node_stmt_waittillframeend>(yylhs.location); }
#line 2063 "parser.cpp"
    break;

  case 55: // stmt_waitframe: "waitframe" ";"
#line 369 "parser.ypp"
        { yylhs.value.as < stmt_waitframe_ptr > () = std::make_unique<node_stmt_waitframe>(yylhs.location); }
#line 2069 "parser.cpp"
    break;

  case 56: // stmt_waitframe: "waitframe" "(" ")" ";"
#line 371 "parser.ypp"
        { yylhs.value.as < stmt_waitframe_ptr > () = std::make_unique<node_stmt_waitframe>(yylhs.location); }
#line 2075 "parser.cpp"
    break;

  case 57: // stmt_if: "if" "(" expr ")" stmt
#line 376 "parser.ypp"
        { yylhs.value.as < stmt_if_ptr > () = std::make_unique<node_stmt_if>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2081 "parser.cpp"
    break;

  case 58: // stmt_ifelse: "if" "(" expr ")" stmt "else" stmt
#line 381 "parser.ypp"
        { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(yylhs.location, std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2087 "parser.cpp"
    break;

  case 59: // stmt_while: "while" "(" expr ")" stmt
#line 386 "parser.ypp"
        { yylhs.value.as < stmt_while_ptr > () = std::make_unique<node_stmt_while>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2093 "parser.cpp"
    break;

  case 60: // stmt_for: "for" "(" for_stmt ";" for_expr ";" for_stmt ")" stmt
#line 391 "parser.ypp"
        { yylhs.value.as < stmt_for_ptr > () = std::make_unique<node_stmt_for>(yylhs.location, std::move(yystack_[6].value.as < stmt_ptr > ()), std::move(yystack_[4].value.as < expr_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2099 "parser.cpp"
    break;

  case 61: // stmt_foreach: "foreach" "(" name "in" expr ")" stmt
#line 396 "parser.ypp"
        { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(yylhs.location, expr_ptr(std::move(yystack_[4].value.as < name_ptr > ())), std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2105 "parser.cpp"
    break;

  case 62: // stmt_foreach: "foreach" "(" name "," name "in" expr ")" stmt
#line 398 "parser.ypp"
        { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(yylhs.location, expr_ptr(std::move(yystack_[6].value.as < name_ptr > ())), expr_ptr(std::move(yystack_[4].value.as < name_ptr > ())), std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 2111 "parser.cpp"
    break;

  case 63: // stmt_switch: "switch" "(" expr ")" stmt_block
#line 403 "parser.ypp"
        { yylhs.value.as < stmt_switch_ptr > () = std::make_unique<node_stmt_switch>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < stmt_list_ptr > ())); }
#line 2117 "parser.cpp"
    break;

  case 64: // stmt_case: "case" integer ":"
#line 408 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < integer_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2123 "parser.cpp"
    break;

  case 65: // stmt_case: "case" neg_integer ":"
#line 410 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < integer_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2129 "parser.cpp"
    break;

  case 66: // stmt_case: "case" string ":"
#line 412 "parser.ypp"
        { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(yylhs.location, expr_ptr(std::move(yystack_[1].value.as < string_ptr > ())), std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2135 "parser.cpp"
    break;

  case 67: // stmt_default: "default" ":"
#line 417 "parser.ypp"
        { yylhs.value.as < stmt_default_ptr > () = std::make_unique<node_stmt_default>(yylhs.location, std::make_unique<gsc::node_stmt_list>(yylhs.location)); }
#line 2141 "parser.cpp"
    break;

  case 68: // stmt_break: "break" ";"
#line 422 "parser.ypp"
        { yylhs.value.as < stmt_break_ptr > () = std::make_unique<node_stmt_break>(yylhs.location); }
#line 2147 "parser.cpp"
    break;

  case 69: // stmt_continue: "continue" ";"
#line 427 "parser.ypp"
        { yylhs.value.as < stmt_continue_ptr > () = std::make_unique<node_stmt_continue>(yylhs.location); }
#line 2153 "parser.cpp"
    break;

  case 70: // stmt_return: "return" expr ";"
#line 432 "parser.ypp"
        { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(yylhs.location, std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2159 "parser.cpp"
    break;

  case 71: // stmt_return: "return" ";"
#line 434 "parser.ypp"
        { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(yylhs.location, std::make_unique<node>(yylhs.location)); }
#line 2165 "parser.cpp"
    break;

  case 72: // for_stmt: expr_assign
#line 438 "parser.ypp"
                                        { yylhs.value.as < stmt_ptr > ().as_list = std::make_unique<node_stmt_list>(yylhs.location); yylhs.value.as < stmt_ptr > ().as_list->stmts.push_back(stmt_ptr(std::make_unique<node_stmt_assign>(yylhs.location, std::move(yystack_[0].value.as < expr_assign_ptr > ())))); }
#line 2171 "parser.cpp"
    break;

  case 73: // for_stmt: %empty
#line 439 "parser.ypp"
                                        { yylhs.value.as < stmt_ptr > ().as_node = std::make_unique<node>(yylhs.location); }
#line 2177 "parser.cpp"
    break;

  case 74: // for_expr: expr
#line 443 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2183 "parser.cpp"
    break;

  case 75: // for_expr: %empty
#line 444 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node>(yylhs.location); }
#line 2189 "parser.cpp"
    break;

  case 76: // expr: expr_compare
#line 448 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2195 "parser.cpp"
    break;

  case 77: // expr: expr_binary
#line 449 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2201 "parser.cpp"
    break;

  case 78: // expr: expr_primitive
#line 450 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[0].value.as < expr_ptr > ()); }
#line 2207 "parser.cpp"
    break;

  case 79: // expr_assign: "++" object
#line 454 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_increment>(yylhs.location, std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2213 "parser.cpp"
    break;

  case 80: // expr_assign: "--" object
#line 455 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_decrement>(yylhs.location, std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2219 "parser.cpp"
    break;

  case 81: // expr_assign: object "++"
#line 456 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_increment>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2225 "parser.cpp"
    break;

  case 82: // expr_assign: object "--"
#line 457 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_decrement>(yylhs.location, std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2231 "parser.cpp"
    break;

  case 83: // expr_assign: object "=" expr
#line 458 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_equal>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2237 "parser.cpp"
    break;

  case 84: // expr_assign: object "|=" expr
#line 459 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2243 "parser.cpp"
    break;

  case 85: // expr_assign: object "&=" expr
#line 460 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2249 "parser.cpp"
    break;

  case 86: // expr_assign: object "^=" expr
#line 461 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2255 "parser.cpp"
    break;

  case 87: // expr_assign: object "<<=" expr
#line 462 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_left>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()),std::move( yystack_[0].value.as < expr_ptr > ())); }
#line 2261 "parser.cpp"
    break;

  case 88: // expr_assign: object ">>=" expr
#line 463 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_right>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2267 "parser.cpp"
    break;

  case 89: // expr_assign: object "+=" expr
#line 464 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_add>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2273 "parser.cpp"
    break;

  case 90: // expr_assign: object "-=" expr
#line 465 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_sub>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2279 "parser.cpp"
    break;

  case 91: // expr_assign: object "*=" expr
#line 466 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mult>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2285 "parser.cpp"
    break;

  case 92: // expr_assign: object "/=" expr
#line 467 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_div>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2291 "parser.cpp"
    break;

  case 93: // expr_assign: object "%=" expr
#line 468 "parser.ypp"
                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mod>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2297 "parser.cpp"
    break;

  case 94: // expr_compare: expr "||" expr
#line 472 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_or>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2303 "parser.cpp"
    break;

  case 95: // expr_compare: expr "&&" expr
#line 473 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_and>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2309 "parser.cpp"
    break;

  case 96: // expr_compare: expr "==" expr
#line 474 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_equality>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2315 "parser.cpp"
    break;

  case 97: // expr_compare: expr "!=" expr
#line 475 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_inequality>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2321 "parser.cpp"
    break;

  case 98: // expr_compare: expr "<=" expr
#line 476 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_less_equal>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2327 "parser.cpp"
    break;

  case 99: // expr_compare: expr ">=" expr
#line 477 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_greater_equal>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2333 "parser.cpp"
    break;

  case 100: // expr_compare: expr "<" expr
#line 478 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_less>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2339 "parser.cpp"
    break;

  case 101: // expr_compare: expr ">" expr
#line 479 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_greater>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2345 "parser.cpp"
    break;

  case 102: // expr_binary: expr "|" expr
#line 483 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_or>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2351 "parser.cpp"
    break;

  case 103: // expr_binary: expr "&" expr
#line 484 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_and>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2357 "parser.cpp"
    break;

  case 104: // expr_binary: expr "^" expr
#line 485 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_bitwise_exor>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2363 "parser.cpp"
    break;

  case 105: // expr_binary: expr "<<" expr
#line 486 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_shift_left>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2369 "parser.cpp"
    break;

  case 106: // expr_binary: expr ">>" expr
#line 487 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_shift_right>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2375 "parser.cpp"
    break;

  case 107: // expr_binary: expr "+" expr
#line 488 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_add>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2381 "parser.cpp"
    break;

  case 108: // expr_binary: expr "-" expr
#line 489 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_sub>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2387 "parser.cpp"
    break;

  case 109: // expr_binary: expr "*" expr
#line 490 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_mult>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2393 "parser.cpp"
    break;

  case 110: // expr_binary: expr "/" expr
#line 491 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_div>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2399 "parser.cpp"
    break;

  case 111: // expr_binary: expr "%" expr
#line 492 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_mod>(yylhs.location, std::move(yystack_[2].value.as < expr_ptr > ()), std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2405 "parser.cpp"
    break;

  case 112: // expr_primitive: "(" expr ")"
#line 496 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > () = std::move(yystack_[1].value.as < expr_ptr > ()); }
#line 2411 "parser.cpp"
    break;

  case 113: // expr_primitive: "~" expr
#line 497 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_complement>(yylhs.location, std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2417 "parser.cpp"
    break;

  case 114: // expr_primitive: "!" expr
#line 498 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::make_unique<node_expr_not>(yylhs.location, std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2423 "parser.cpp"
    break;

  case 115: // expr_primitive: expr_call
#line 499 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2429 "parser.cpp"
    break;

  case 116: // expr_primitive: expr_call_thread
#line 500 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2435 "parser.cpp"
    break;

  case 117: // expr_primitive: expr_call_childthread
#line 501 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2441 "parser.cpp"
    break;

  case 118: // expr_primitive: expr_function
#line 502 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2447 "parser.cpp"
    break;

  case 119: // expr_primitive: expr_add_array
#line 503 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2453 "parser.cpp"
    break;

  case 120: // expr_primitive: expr_array
#line 504 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2459 "parser.cpp"
    break;

  case 121: // expr_primitive: expr_field
#line 505 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2465 "parser.cpp"
    break;

  case 122: // expr_primitive: expr_size
#line 506 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2471 "parser.cpp"
    break;

  case 123: // expr_primitive: thisthread
#line 507 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < thisthread_ptr > ()); }
#line 2477 "parser.cpp"
    break;

  case 124: // expr_primitive: empty_array
#line 508 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < empty_array_ptr > ()); }
#line 2483 "parser.cpp"
    break;

  case 125: // expr_primitive: undefined
#line 509 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < undefined_ptr > ()); }
#line 2489 "parser.cpp"
    break;

  case 126: // expr_primitive: game
#line 510 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < game_ptr > ()); }
#line 2495 "parser.cpp"
    break;

  case 127: // expr_primitive: self
#line 511 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < self_ptr > ()); }
#line 2501 "parser.cpp"
    break;

  case 128: // expr_primitive: anim
#line 512 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < anim_ptr > ()); }
#line 2507 "parser.cpp"
    break;

  case 129: // expr_primitive: level
#line 513 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < level_ptr > ()); }
#line 2513 "parser.cpp"
    break;

  case 130: // expr_primitive: animation
#line 514 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < animation_ptr > ()); }
#line 2519 "parser.cpp"
    break;

  case 131: // expr_primitive: animtree
#line 515 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < animtree_ptr > ()); }
#line 2525 "parser.cpp"
    break;

  case 132: // expr_primitive: name
#line 516 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < name_ptr > ()); }
#line 2531 "parser.cpp"
    break;

  case 133: // expr_primitive: istring
#line 517 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < istring_ptr > ()); }
#line 2537 "parser.cpp"
    break;

  case 134: // expr_primitive: string
#line 518 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < string_ptr > ()); }
#line 2543 "parser.cpp"
    break;

  case 135: // expr_primitive: vector
#line 519 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < vector_ptr > ()); }
#line 2549 "parser.cpp"
    break;

  case 136: // expr_primitive: neg_float
#line 520 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2555 "parser.cpp"
    break;

  case 137: // expr_primitive: neg_integer
#line 521 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2561 "parser.cpp"
    break;

  case 138: // expr_primitive: float
#line 522 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2567 "parser.cpp"
    break;

  case 139: // expr_primitive: integer
#line 523 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2573 "parser.cpp"
    break;

  case 140: // expr_primitive: false
#line 524 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < false_ptr > ()); }
#line 2579 "parser.cpp"
    break;

  case 141: // expr_primitive: true
#line 525 "parser.ypp"
                                        { yylhs.value.as < expr_ptr > ().as_node = std::move(yystack_[0].value.as < true_ptr > ()); }
#line 2585 "parser.cpp"
    break;

  case 142: // expr_call: expr_call_function
#line 529 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2591 "parser.cpp"
    break;

  case 143: // expr_call: expr_call_pointer
#line 530 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2597 "parser.cpp"
    break;

  case 144: // expr_call: object expr_call_function
#line 531 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2603 "parser.cpp"
    break;

  case 145: // expr_call: object expr_call_pointer
#line 532 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2609 "parser.cpp"
    break;

  case 146: // expr_call_thread: "thread" expr_call_function
#line 536 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2615 "parser.cpp"
    break;

  case 147: // expr_call_thread: "thread" expr_call_pointer
#line 537 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2621 "parser.cpp"
    break;

  case 148: // expr_call_thread: object "thread" expr_call_function
#line 538 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2627 "parser.cpp"
    break;

  case 149: // expr_call_thread: object "thread" expr_call_pointer
#line 539 "parser.ypp"
                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, true, false, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2633 "parser.cpp"
    break;

  case 150: // expr_call_childthread: "childthread" expr_call_function
#line 543 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2639 "parser.cpp"
    break;

  case 151: // expr_call_childthread: "childthread" expr_call_pointer
#line 544 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::make_unique<node>(yylhs.location), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2645 "parser.cpp"
    break;

  case 152: // expr_call_childthread: object "childthread" expr_call_function
#line 545 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2651 "parser.cpp"
    break;

  case 153: // expr_call_childthread: object "childthread" expr_call_pointer
#line 546 "parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(yylhs.location, false, true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2657 "parser.cpp"
    break;

  case 154: // expr_call_function: name "(" expr_arguments ")"
#line 551 "parser.ypp"
        {yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(yylhs.location, std::make_unique<node_file>(), std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2663 "parser.cpp"
    break;

  case 155: // expr_call_function: file "::" name "(" expr_arguments ")"
#line 553 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(yylhs.location, std::move(yystack_[5].value.as < file_ptr > ()), std::move(yystack_[3].value.as < name_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2669 "parser.cpp"
    break;

  case 156: // expr_call_pointer: "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 558 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_call_pointer>(yylhs.location, false, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2675 "parser.cpp"
    break;

  case 157: // expr_call_pointer: "call" "[" "[" expr "]" "]" "(" expr_arguments ")"
#line 560 "parser.ypp"
        { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_call_pointer>(yylhs.location, true, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2681 "parser.cpp"
    break;

  case 158: // expr_arguments: expr_arguments_filled
#line 564 "parser.ypp"
                            { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[0].value.as < expr_arguments_ptr > ()); }
#line 2687 "parser.cpp"
    break;

  case 159: // expr_arguments: expr_arguments_empty
#line 565 "parser.ypp"
                            { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[0].value.as < expr_arguments_ptr > ()); }
#line 2693 "parser.cpp"
    break;

  case 160: // expr_arguments_filled: expr_arguments "," expr
#line 570 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[2].value.as < expr_arguments_ptr > ()); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2699 "parser.cpp"
    break;

  case 161: // expr_arguments_filled: expr
#line 572 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(yylhs.location); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < expr_ptr > ())); }
#line 2705 "parser.cpp"
    break;

  case 162: // expr_arguments_empty: %empty
#line 577 "parser.ypp"
        { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(yylhs.location); }
#line 2711 "parser.cpp"
    break;

  case 163: // expr_function: "::" name
#line 582 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function>(yylhs.location, std::make_unique<node_file>(yylhs.location), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2717 "parser.cpp"
    break;

  case 164: // expr_function: file "::" name
#line 584 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function>(yylhs.location, std::move(yystack_[2].value.as < file_ptr > ()), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2723 "parser.cpp"
    break;

  case 165: // expr_add_array: "[" expr_arguments_filled "]"
#line 589 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_add_array>(yylhs.location, std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2729 "parser.cpp"
    break;

  case 166: // expr_array: object "[" expr "]"
#line 594 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_array>(yylhs.location, std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2735 "parser.cpp"
    break;

  case 167: // expr_field: object "." name
#line 599 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_field>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < name_ptr > ())); }
#line 2741 "parser.cpp"
    break;

  case 168: // expr_size: object "." "size"
#line 604 "parser.ypp"
        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_size>(yylhs.location, std::move(yystack_[2].value.as < node_ptr > ())); }
#line 2747 "parser.cpp"
    break;

  case 169: // object: expr_call
#line 608 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2753 "parser.cpp"
    break;

  case 170: // object: expr_array
#line 609 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2759 "parser.cpp"
    break;

  case 171: // object: expr_field
#line 610 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2765 "parser.cpp"
    break;

  case 172: // object: game
#line 611 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < game_ptr > ()); }
#line 2771 "parser.cpp"
    break;

  case 173: // object: self
#line 612 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < self_ptr > ()); }
#line 2777 "parser.cpp"
    break;

  case 174: // object: anim
#line 613 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < anim_ptr > ()); }
#line 2783 "parser.cpp"
    break;

  case 175: // object: level
#line 614 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < level_ptr > ()); }
#line 2789 "parser.cpp"
    break;

  case 176: // object: name
#line 615 "parser.ypp"
                                                       { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < name_ptr > ()); }
#line 2795 "parser.cpp"
    break;

  case 177: // thisthread: "thisthread"
#line 618 "parser.ypp"
                                                       { yylhs.value.as < thisthread_ptr > () = std::make_unique<node_thisthread>(yylhs.location); }
#line 2801 "parser.cpp"
    break;

  case 178: // empty_array: "[" "]"
#line 619 "parser.ypp"
                                                       { yylhs.value.as < empty_array_ptr > () = std::make_unique<node_empty_array>(yylhs.location); }
#line 2807 "parser.cpp"
    break;

  case 179: // undefined: "undefined"
#line 620 "parser.ypp"
                                                       { yylhs.value.as < undefined_ptr > () = std::make_unique<node_undefined>(yylhs.location); }
#line 2813 "parser.cpp"
    break;

  case 180: // game: "game"
#line 621 "parser.ypp"
                                                       { yylhs.value.as < game_ptr > () = std::make_unique<node_game>(yylhs.location); }
#line 2819 "parser.cpp"
    break;

  case 181: // self: "self"
#line 622 "parser.ypp"
                                                       { yylhs.value.as < self_ptr > () = std::make_unique<node_self>(yylhs.location); }
#line 2825 "parser.cpp"
    break;

  case 182: // anim: "anim"
#line 623 "parser.ypp"
                                                       { yylhs.value.as < anim_ptr > () = std::make_unique<node_anim>(yylhs.location); }
#line 2831 "parser.cpp"
    break;

  case 183: // level: "level"
#line 624 "parser.ypp"
                                                       { yylhs.value.as < level_ptr > () = std::make_unique<node_level>(yylhs.location); }
#line 2837 "parser.cpp"
    break;

  case 184: // animation: "%" "identifier"
#line 625 "parser.ypp"
                                                       { yylhs.value.as < animation_ptr > () = std::make_unique<node_animation>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2843 "parser.cpp"
    break;

  case 185: // animtree: "#animtree"
#line 626 "parser.ypp"
                                                       { yylhs.value.as < animtree_ptr > () = std::make_unique<node_animtree>(yylhs.location); }
#line 2849 "parser.cpp"
    break;

  case 186: // name: "identifier"
#line 627 "parser.ypp"
                                                       { yylhs.value.as < name_ptr > () = std::make_unique<node_name>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2855 "parser.cpp"
    break;

  case 187: // file: "file path"
#line 628 "parser.ypp"
                                                       { yylhs.value.as < file_ptr > () = std::make_unique<node_file>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2861 "parser.cpp"
    break;

  case 188: // istring: "localized string"
#line 629 "parser.ypp"
                                                       { yylhs.value.as < istring_ptr > () = std::make_unique<node_istring>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2867 "parser.cpp"
    break;

  case 189: // string: "string literal"
#line 630 "parser.ypp"
                                                       { yylhs.value.as < string_ptr > () = std::make_unique<node_string>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2873 "parser.cpp"
    break;

  case 190: // vector: "(" expr "," expr "," expr ")"
#line 631 "parser.ypp"
                                                       { yylhs.value.as < vector_ptr > () = std::make_unique<node_vector>(yylhs.location, std::move(yystack_[5].value.as < expr_ptr > ()), std::move(yystack_[3].value.as < expr_ptr > ()), std::move(yystack_[1].value.as < expr_ptr > ())); }
#line 2879 "parser.cpp"
    break;

  case 191: // neg_float: "-" "float"
#line 632 "parser.ypp"
                                                       { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 2885 "parser.cpp"
    break;

  case 192: // neg_integer: "-" "int"
#line 633 "parser.ypp"
                                                       { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yylhs.location, "-" + yystack_[0].value.as < std::string > ()); }
#line 2891 "parser.cpp"
    break;

  case 193: // float: "float"
#line 634 "parser.ypp"
                                                       { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2897 "parser.cpp"
    break;

  case 194: // integer: "int"
#line 635 "parser.ypp"
                                                       { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yylhs.location, yystack_[0].value.as < std::string > ()); }
#line 2903 "parser.cpp"
    break;

  case 195: // false: "false"
#line 636 "parser.ypp"
                                                       { yylhs.value.as < false_ptr > () = std::make_unique<node_false>(yylhs.location); }
#line 2909 "parser.cpp"
    break;

  case 196: // true: "true"
#line 637 "parser.ypp"
                                                       { yylhs.value.as < true_ptr > () = std::make_unique<node_true>(yylhs.location); }
#line 2915 "parser.cpp"
    break;


#line 2919 "parser.cpp"

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
  "waittillframeend", "waitframe", "if", "else", "while", "for", "foreach",
  "in", "switch", "case", "default", "break", "continue", "return",
  "thread", "childthread", "thisthread", "call", "true", "false",
  "undefined", "size", "game", "self", "anim", "level", "(", ")", "{", "}",
  "[", "]", ",", ".", "::", ":", ";", "++", "--", "<<", ">>", "||", "&&",
  "==", "!=", "<=", ">=", "<", ">", "!", "~", "=", "+=", "-=", "*=", "/=",
  "%=", "|=", "&=", "^=", ">>=", "<<=", "|", "&", "^", "+", "-", "*", "/",
  "%", "file path", "identifier", "string literal", "localized string",
  "float", "int", "ADD_ARRAY", "THEN", "NEG", "ANIMREF", "PREINC",
  "PREDEC", "POSTINC", "POSTDEC", "$accept", "root", "program", "include",
  "define", "usingtree", "constant", "thread", "parameters", "stmt",
  "stmt_block", "stmt_list", "stmt_call", "stmt_assign", "stmt_endon",
  "stmt_notify", "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_waitframe", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case",
  "stmt_default", "stmt_break", "stmt_continue", "stmt_return", "for_stmt",
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


  const short parser::yypact_ninf_ = -230;

  const short parser::yytable_ninf_ = -177;

  const short
  parser::yypact_[] =
  {
       7,   -67,   -20,  -230,    53,     7,  -230,  -230,  -230,  -230,
    -230,   -21,  -230,    13,   -10,  -230,  -230,  -230,    -3,   607,
    -230,  -230,    25,   -15,  -230,  -230,    41,    41,  -230,    29,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,   607,   480,    -3,
     607,   607,   -50,    -1,  -230,  -230,  -230,  1341,  -230,  -230,
    -230,    18,  -230,  -230,  -230,  -230,  -230,  -230,    23,    30,
    -230,   332,  -230,  -230,  -230,   446,   507,   569,   573,  -230,
    -230,    -4,    38,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,    47,    85,    -3,    56,  -230,  -230,    84,    64,
    -230,  -230,    86,   905,   480,  -230,  1419,    90,    95,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,   607,   607,   607,
     607,   607,   607,   607,   607,   607,   607,   607,   607,   607,
     607,   607,   607,   607,   607,    41,    41,   669,   -17,  -230,
    -230,   607,    -3,  -230,   787,  -230,  -230,   607,    -3,   607,
    -230,   607,  1212,   607,  -230,   124,   124,  1429,   938,  1501,
    1501,    40,    40,    40,    40,   981,  1460,  1470,   101,   101,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  1251,  -230,  -230,
     -13,  -230,   103,   607,    94,   -18,   123,   126,   128,   130,
     131,     9,   125,   135,   138,   545,  -230,   732,   732,  -230,
    -230,   826,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,   139,   143,   148,  -230,  -230,   715,  -230,  -230,
    -230,  -230,    84,  1212,   103,  1290,  1328,   133,  1419,  -230,
    -230,   607,  1375,  -230,   132,  -230,   607,   607,   630,    -3,
     607,    91,   151,   159,   160,  -230,  -230,  -230,  -230,  1388,
    -230,     6,     6,  -230,  -230,  -230,  -230,  -230,   152,   172,
     173,   174,    -3,  -230,  -230,   607,   607,   607,   607,   607,
     607,   607,   607,   607,   607,   607,   170,   607,   176,    14,
    -230,   177,  1044,  1077,   178,  -230,   868,     2,  1087,  -230,
    -230,  -230,  -230,   607,   607,   607,   607,  1419,  1419,  1419,
    1419,  1419,  1419,  1419,  1419,  1419,  1419,  1419,   182,  1120,
     607,  -230,  -230,   865,   865,   607,   607,    -3,    85,  1130,
     948,   991,  1034,   607,  -230,    42,   207,  -230,   187,  1419,
    1163,   205,  -230,   188,   190,   607,   193,   607,   195,   607,
      55,  -230,   865,   630,   865,   607,  -230,  -230,    58,  -230,
      70,  -230,    72,  -230,  -230,   206,  -230,  1173,   198,   199,
     200,   865,   865,  -230,  -230,  -230,  -230,  -230
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,   186,     0,     2,     6,     7,     9,    10,
      11,     0,   187,     0,     0,     1,     4,     5,    17,     0,
       8,   189,     0,     0,    16,   185,     0,     0,   177,     0,
     196,   195,   179,   180,   181,   182,   183,     0,   162,     0,
       0,     0,     0,     0,   188,   193,   194,     0,    76,    77,
      78,   115,   116,   117,   142,   143,   118,   119,   120,   121,
     122,     0,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,     0,   133,   134,   135,   136,   137,   138,   139,
     140,   141,     0,     0,     0,     0,   146,   147,     0,     0,
     150,   151,     0,     0,   162,   178,   161,     0,   158,   159,
     163,   114,   113,   191,   192,   184,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144,
     145,   162,     0,    12,     0,    14,    15,     0,     0,     0,
     112,     0,   161,     0,   165,   105,   106,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   107,   108,
     109,   110,   111,   148,   149,   152,   153,     0,   168,   167,
       0,   158,   164,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    40,     0,     0,    42,
      18,     0,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,     0,   169,     0,   170,   171,     0,   172,   173,
     174,   175,   176,     0,     0,     0,     0,     0,   160,   166,
     154,   162,     0,    54,     0,    55,     0,     0,    73,     0,
       0,     0,     0,     0,     0,    67,    68,    69,    71,     0,
     169,    79,    80,    39,    41,    45,    43,    44,     0,     0,
       0,     0,     0,    81,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,    72,     0,     0,     0,    66,
      65,    64,    70,     0,     0,     0,     0,    83,    89,    90,
      91,    92,    93,    84,    85,    86,    88,    87,     0,     0,
     162,   155,    56,     0,     0,    75,     0,     0,     0,     0,
       0,     0,     0,   162,   190,     0,    57,    59,     0,    74,
       0,     0,    63,     0,     0,   162,     0,   162,     0,   162,
       0,   156,     0,    73,     0,     0,    46,    48,     0,    51,
       0,    53,     0,   157,    58,     0,    61,     0,     0,     0,
       0,     0,     0,    47,    50,    52,    60,    62
  };

  const short
  parser::yypgoto_[] =
  {
    -230,  -230,  -230,   243,   244,  -230,  -230,  -230,  -230,  -178,
     -82,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,   -93,  -230,    35,  -229,  -230,  -230,  -230,    27,
     142,  -230,   -23,   -19,    68,   -26,  -230,  -230,  -230,    39,
      73,  -230,    82,  -230,  -230,  -230,    97,   107,   134,   241,
    -230,  -230,     0,     5,  -230,   -12,  -230,  -230,    74,  -230,
      77,  -230,  -230
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,     8,     9,    10,    23,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   284,   328,    96,   212,    48,    49,    50,    51,
      52,    53,    54,    55,    97,   171,    99,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81
  };

  const short
  parser::yytable_[] =
  {
      11,   135,    22,    86,    90,    11,    13,    87,    91,   285,
       1,     2,    98,   254,    12,   168,    18,    14,    24,   234,
     316,  -176,  -176,    83,  -176,   230,    88,    88,    84,   235,
     143,    89,    89,   131,    29,   103,   104,  -176,   129,   100,
    -176,    19,   130,  -169,  -169,   317,  -169,   127,  -170,  -170,
     262,  -170,   311,    15,    47,  -171,  -171,   143,  -171,  -169,
      20,    88,  -169,    82,  -170,     3,    89,  -170,    98,    29,
      92,  -171,    93,    21,  -171,   101,   102,  -176,  -176,     3,
     341,   105,    85,   132,   136,   143,   241,    12,     3,     3,
     107,   108,    21,   353,   133,    46,   358,   137,   143,  -169,
    -169,   143,   163,   165,  -170,  -170,   164,   166,   359,   138,
     360,  -171,  -171,   143,   285,   143,   120,   121,   122,   123,
     124,   131,    12,     3,   134,    88,    88,   139,   169,   142,
      89,    89,   172,   143,   222,   326,   327,   144,   224,    89,
     231,   233,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     236,   213,   167,   237,   354,   238,   356,   239,   240,   242,
     281,   245,   223,   215,   225,   278,   226,   104,   228,   122,
     123,   124,   246,   366,   367,   247,   255,   222,   222,   293,
     256,   222,    89,    89,   129,   257,    89,   289,   130,   170,
     120,   121,   122,   123,   124,   290,   291,   216,   232,   294,
     295,   296,   308,   310,   250,   250,   217,    88,   213,   323,
     249,   342,    89,   345,   312,   315,   215,   215,   129,   129,
     215,   218,   130,   130,   343,   346,   332,   347,   222,   287,
     349,   219,   351,    89,   361,   363,   364,   365,    16,    17,
     355,    88,    88,     0,     0,   243,    89,    89,   244,     0,
     216,   216,   169,   129,   216,   250,     0,   130,   220,   251,
     252,   282,   283,   217,     0,   288,   214,   215,     0,     0,
       0,     0,     0,     0,   218,   218,    88,     0,   218,     0,
       0,    89,     0,     0,   219,   219,     0,     0,   219,   279,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   216,   309,   222,   222,     0,     0,   331,    89,    89,
     286,   220,   220,     0,     0,   220,     0,     0,   319,   320,
     321,   322,     0,   214,     0,   218,     0,     0,     0,     0,
     213,   213,   222,   222,   222,   219,     0,    89,    89,    89,
     329,   330,   215,   215,     0,     0,     0,   125,   126,     0,
      29,   222,   222,     0,     0,     0,    89,    89,     0,   213,
     250,   213,   220,   127,     0,   221,   128,     0,   325,     0,
     357,   215,   215,   215,     0,     0,   216,   216,   213,   213,
       0,   340,     0,     0,     0,   217,   217,     0,     0,     0,
     215,   215,     0,   348,     0,   350,     0,   352,     0,     0,
     218,   218,     0,    12,     3,   216,   216,   216,     0,     0,
     219,   219,     0,     0,   217,   286,   217,     0,   221,   221,
       0,     0,   221,     0,   216,   216,     0,     0,     0,   218,
     218,   218,     0,   217,   217,     0,     0,   220,   220,   219,
     219,   219,     0,     0,     0,   214,   214,     0,   218,   218,
       0,     0,     0,     0,     0,     0,     0,     0,   219,   219,
       0,  -172,  -172,     0,  -172,     0,   220,   220,   220,   221,
       0,     0,     0,     0,   214,    25,   214,  -172,     0,     0,
    -172,     0,     0,     0,     0,   220,   220,     0,     0,     0,
       0,     0,     0,   214,   214,    26,    27,    28,    29,    30,
      31,    32,     0,    33,    34,    35,    36,    37,     0,     0,
       0,    94,    95,     0,     0,    39,     0,  -172,  -172,     0,
       0,     0,  -173,  -173,     0,  -173,     0,     0,     0,     0,
      40,    41,     0,     0,     0,     0,     0,     0,  -173,     0,
      25,  -173,     0,     0,   221,   221,     0,    42,     0,     0,
      43,    12,     3,    21,    44,    45,    46,     0,     0,     0,
      26,    27,    28,    29,    30,    31,    32,     0,    33,    34,
      35,    36,    37,   221,   221,   221,    38,     0,  -173,  -173,
      39,     0,   248,     0,  -174,  -174,     0,  -174,  -175,  -175,
       0,  -175,   221,   221,     0,    40,    41,     0,     0,     0,
    -174,     0,    25,  -174,  -175,     0,     0,  -175,     0,     0,
       0,     0,    42,     0,     0,    43,    12,     3,    21,    44,
      45,    46,    26,    27,    28,    29,    30,    31,    32,     0,
      33,    34,    35,    36,    37,     0,     0,     0,    38,     0,
    -174,  -174,    39,     0,  -175,  -175,     0,     0,    29,     0,
       0,     0,     0,    33,    34,    35,    36,    40,    41,     0,
       0,    85,     0,     0,    25,     0,     0,     0,   187,   188,
       0,     0,     0,     0,    42,     0,     0,    43,    12,     3,
      21,    44,    45,    46,    26,    27,    28,    29,    30,    31,
      32,     0,    33,    34,    35,    36,    37,     0,     0,     0,
      94,    12,     3,     0,    39,     0,     0,     0,     0,     0,
       0,   258,   259,     0,   260,   261,     0,     0,     0,    40,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     125,     0,     0,    29,     0,     0,    42,     0,     0,    43,
      12,     3,    21,    44,    45,    46,   127,     0,     0,   262,
      29,     0,     0,   263,   264,    33,    34,    35,    36,     0,
       0,     0,     0,    85,     0,     0,     0,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,     0,     0,
       0,     0,     0,     0,     0,   173,    12,     3,   174,   175,
     176,     0,   177,   178,   179,     0,   180,   181,   182,   183,
     184,   185,    26,    12,     3,    29,     0,     0,     0,     0,
      33,    34,    35,    36,     0,     0,   134,   186,    85,     0,
       0,     0,     0,     0,   173,   187,   188,   174,   175,   176,
       0,   177,   178,   179,     0,   180,   181,   182,   183,   184,
     185,    26,     0,     0,    29,     0,     0,     0,     0,    33,
      34,    35,    36,     0,     0,   134,   253,    85,    12,     3,
       0,     0,     0,   173,   187,   188,   174,   175,   176,     0,
     177,   178,   179,     0,   180,   181,   182,   183,   184,   185,
      26,     0,     0,    29,     0,     0,    29,     0,    33,    34,
      35,    36,     0,     0,   134,     0,    85,    12,     3,   127,
       0,     0,   262,   187,   188,     0,   263,   264,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,     0,     0,   140,     0,     0,    12,     3,   141,    12,
       3,     0,     0,     0,     0,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   334,     0,   107,   108,
       0,   335,   111,   112,   113,   114,   115,   116,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   336,
       0,   107,   108,     0,   337,   111,   112,   113,   114,   115,
     116,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     0,     0,     0,     0,   118,   119,   120,   121,   122,
     123,   124,     0,     0,   117,   118,   119,   120,   121,   122,
     123,   124,   338,     0,     0,     0,     0,   339,     0,     0,
       0,     0,   313,     0,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   314,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   318,     0,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,     0,     0,     0,
     117,   118,   119,   120,   121,   122,   123,   124,   324,     0,
     117,   118,   119,   120,   121,   122,   123,   124,   333,     0,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   344,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   362,     0,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   227,     0,     0,     0,     0,     0,
       0,     0,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   229,     0,     0,     0,     0,     0,     0,
       0,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,   119,   120,   121,   122,
     123,   124,   276,     0,     0,     0,     0,     0,     0,     0,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   277,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   106,     0,
       0,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,     0,
       0,     0,     0,     0,   117,   118,   119,   120,   121,   122,
     123,   124,   280,     0,     0,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   292,     0,     0,   107,   108,
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
     124,   107,   108,     0,     0,     0,     0,   113,   114,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   120,   121,   122,
     123,   124
  };

  const short
  parser::yycheck_[] =
  {
       0,    83,    14,    26,    27,     5,     1,    26,    27,   238,
       3,     4,    38,   191,    81,    32,    37,    37,    18,    37,
      18,    25,    26,    38,    28,    38,    26,    27,    43,    47,
      43,    26,    27,    37,    28,    85,    86,    41,    61,    39,
      44,    62,    61,    25,    26,    43,    28,    41,    25,    26,
      44,    28,    38,     0,    19,    25,    26,    43,    28,    41,
      47,    61,    44,    38,    41,    82,    61,    44,    94,    28,
      41,    41,    37,    83,    44,    40,    41,    81,    82,    82,
      38,    82,    41,    45,    84,    43,    77,    81,    82,    82,
      50,    51,    83,    38,    47,    86,    38,    41,    43,    81,
      82,    43,   125,   126,    81,    82,   125,   126,    38,    45,
      38,    81,    82,    43,   343,    43,    76,    77,    78,    79,
      80,    37,    81,    82,    39,   125,   126,    41,   128,    94,
     125,   126,   132,    43,   134,   313,   314,    42,   138,   134,
      37,    47,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
      37,   134,   127,    37,   342,    37,   344,    37,    37,   181,
      38,    46,   137,   134,   139,    42,   141,    86,   143,    78,
      79,    80,    47,   361,   362,    47,    47,   187,   188,    37,
      47,   191,   187,   188,   217,    47,   191,    46,   217,   131,
      76,    77,    78,    79,    80,    46,    46,   134,   173,    37,
      37,    37,    42,    37,   187,   188,   134,   217,   191,    37,
     185,    14,   217,    18,    47,    47,   187,   188,   251,   252,
     191,   134,   251,   252,    47,    47,   318,    47,   238,   239,
      47,   134,    47,   238,    38,    47,    47,    47,     5,     5,
     343,   251,   252,    -1,    -1,   181,   251,   252,   181,    -1,
     187,   188,   262,   286,   191,   238,    -1,   286,   134,   187,
     188,   236,   237,   191,    -1,   240,   134,   238,    -1,    -1,
      -1,    -1,    -1,    -1,   187,   188,   286,    -1,   191,    -1,
      -1,   286,    -1,    -1,   187,   188,    -1,    -1,   191,   231,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   238,   277,   313,   314,    -1,    -1,   317,   313,   314,
     238,   187,   188,    -1,    -1,   191,    -1,    -1,   293,   294,
     295,   296,    -1,   191,    -1,   238,    -1,    -1,    -1,    -1,
     313,   314,   342,   343,   344,   238,    -1,   342,   343,   344,
     315,   316,   313,   314,    -1,    -1,    -1,    25,    26,    -1,
      28,   361,   362,    -1,    -1,    -1,   361,   362,    -1,   342,
     343,   344,   238,    41,    -1,   134,    44,    -1,   310,    -1,
     345,   342,   343,   344,    -1,    -1,   313,   314,   361,   362,
      -1,   323,    -1,    -1,    -1,   313,   314,    -1,    -1,    -1,
     361,   362,    -1,   335,    -1,   337,    -1,   339,    -1,    -1,
     313,   314,    -1,    81,    82,   342,   343,   344,    -1,    -1,
     313,   314,    -1,    -1,   342,   343,   344,    -1,   187,   188,
      -1,    -1,   191,    -1,   361,   362,    -1,    -1,    -1,   342,
     343,   344,    -1,   361,   362,    -1,    -1,   313,   314,   342,
     343,   344,    -1,    -1,    -1,   313,   314,    -1,   361,   362,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   361,   362,
      -1,    25,    26,    -1,    28,    -1,   342,   343,   344,   238,
      -1,    -1,    -1,    -1,   342,     5,   344,    41,    -1,    -1,
      44,    -1,    -1,    -1,    -1,   361,   362,    -1,    -1,    -1,
      -1,    -1,    -1,   361,   362,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    41,    42,    -1,    -1,    45,    -1,    81,    82,    -1,
      -1,    -1,    25,    26,    -1,    28,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
       5,    44,    -1,    -1,   313,   314,    -1,    77,    -1,    -1,
      80,    81,    82,    83,    84,    85,    86,    -1,    -1,    -1,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    37,   342,   343,   344,    41,    -1,    81,    82,
      45,    -1,    47,    -1,    25,    26,    -1,    28,    25,    26,
      -1,    28,   361,   362,    -1,    60,    61,    -1,    -1,    -1,
      41,    -1,     5,    44,    41,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    80,    81,    82,    83,    84,
      85,    86,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    41,    -1,
      81,    82,    45,    -1,    81,    82,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    60,    61,    -1,
      -1,    41,    -1,    -1,     5,    -1,    -1,    -1,    48,    49,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    80,    81,    82,
      83,    84,    85,    86,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    34,    35,    36,    37,    -1,    -1,    -1,
      41,    81,    82,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,    -1,     9,    10,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    28,    -1,    -1,    77,    -1,    -1,    80,
      81,    82,    83,    84,    85,    86,    41,    -1,    -1,    44,
      28,    -1,    -1,    48,    49,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    81,    82,    11,    12,
      13,    -1,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    81,    82,    28,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    -1,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,     8,    48,    49,    11,    12,    13,
      -1,    15,    16,    17,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    -1,    -1,    39,    40,    41,    81,    82,
      -1,    -1,    -1,     8,    48,    49,    11,    12,    13,    -1,
      15,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    28,    -1,    -1,    28,    -1,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    41,    81,    82,    41,
      -1,    -1,    44,    48,    49,    -1,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    -1,    38,    -1,    -1,    81,    82,    43,    81,
      82,    -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      75,    76,    77,    78,    79,    80,    38,    -1,    50,    51,
      -1,    43,    54,    55,    56,    57,    58,    59,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    38,
      -1,    50,    51,    -1,    43,    54,    55,    56,    57,    58,
      59,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    73,    74,    75,    76,    77,    78,
      79,    80,    38,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    38,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    73,    74,    75,
      76,    77,    78,    79,    80,    38,    -1,    73,    74,    75,
      76,    77,    78,    79,    80,    38,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      73,    74,    75,    76,    77,    78,    79,    80,    38,    -1,
      73,    74,    75,    76,    77,    78,    79,    80,    38,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    38,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    38,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    73,    74,    75,    76,
      77,    78,    79,    80,    -1,    -1,    73,    74,    75,    76,
      77,    78,    79,    80,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,
      78,    79,    80,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,    78,
      79,    80,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    47,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,    78,
      79,    80,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    47,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    -1,    73,    74,    75,    76,    77,    78,    79,    80,
      50,    51,    -1,    -1,    54,    55,    56,    57,    58,    59,
      50,    51,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    50,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,    82,    96,    97,    98,    99,   100,   101,
     102,   157,    81,   158,    37,     0,    98,    99,    37,    62,
      47,    83,   160,   103,   157,     5,    25,    26,    27,    28,
      29,    30,    31,    33,    34,    35,    36,    37,    41,    45,
      60,    61,    77,    80,    84,    85,    86,   129,   131,   132,
     133,   134,   135,   136,   137,   138,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,    38,    38,    43,    41,   137,   138,   157,   158,
     137,   138,    41,   129,    41,    42,   129,   139,   140,   141,
     157,   129,   129,    85,    86,    82,    47,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    73,    74,    75,
      76,    77,    78,    79,    80,    25,    26,    41,    44,   137,
     138,    37,    45,    47,    39,   105,   157,    41,    45,    41,
      38,    43,   129,    43,    42,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   137,   138,   137,   138,   129,    32,   157,
     139,   140,   157,     8,    11,    12,    13,    15,    16,    17,
      19,    20,    21,    22,    23,    24,    40,    48,    49,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   130,   134,   135,   144,   145,   147,   151,   152,
     153,   154,   157,   129,   157,   129,   129,    42,   129,    42,
      38,    37,   129,    47,    37,    47,    37,    37,    37,    37,
      37,    77,   160,   163,   165,    46,    47,    47,    47,   129,
     134,   147,   147,    40,   104,    47,    47,    47,     6,     7,
       9,    10,    44,    48,    49,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    42,    43,    42,   139,
      47,    38,   129,   129,   127,   130,   147,   157,   129,    46,
      46,    46,    47,    37,    37,    37,    37,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,    42,   129,
      37,    38,    47,    38,    38,    47,    18,    43,    38,   129,
     129,   129,   129,    37,    38,   139,   104,   104,   128,   129,
     129,   157,   105,    38,    38,    43,    38,    43,    38,    43,
     139,    38,    14,    47,    38,    18,    47,    47,   139,    47,
     139,    47,   139,    38,   104,   127,   104,   129,    38,    38,
      38,    38,    38,    47,    47,    47,   104,   104
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    95,    96,    96,    97,    97,    97,    97,    98,    99,
      99,    99,   100,   101,   102,   103,   103,   103,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   105,
     105,   106,   106,   107,   107,   108,   109,   110,   110,   111,
     112,   112,   113,   113,   114,   115,   115,   116,   117,   118,
     119,   120,   120,   121,   122,   122,   122,   123,   124,   125,
     126,   126,   127,   127,   128,   128,   129,   129,   129,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   131,   131,   131,   131,
     131,   131,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   134,   134,   134,   134,   135,   135,   135,   135,
     136,   136,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   141,   142,   142,   143,   144,   145,   146,   147,
     147,   147,   147,   147,   147,   147,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     1,     1,     3,     1,
       1,     1,     5,     4,     5,     3,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     1,     2,     2,     2,     6,     8,     6,     3,
       8,     6,     8,     6,     2,     2,     4,     5,     7,     5,
       9,     7,     9,     5,     3,     3,     3,     2,     2,     2,
       3,     2,     1,     0,     1,     0,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     3,     3,
       2,     2,     3,     3,     4,     6,     8,     9,     1,     1,
       3,     1,     0,     2,     3,     3,     4,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       7,     2,     2,     1,     1,     1,     1
  };




#if S2DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   233,   233,   234,   238,   240,   242,   244,   249,   254,
     255,   256,   260,   265,   270,   275,   277,   280,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   308,
     309,   313,   315,   320,   322,   327,   332,   337,   339,   344,
     349,   351,   356,   358,   363,   368,   370,   375,   380,   385,
     390,   395,   397,   402,   407,   409,   411,   416,   421,   426,
     431,   433,   438,   439,   443,   444,   448,   449,   450,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   472,   473,   474,   475,   476,   477,
     478,   479,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   529,   530,   531,   532,   536,   537,   538,   539,
     543,   544,   545,   546,   550,   552,   557,   559,   564,   565,
     569,   571,   577,   581,   583,   588,   593,   598,   603,   608,
     609,   610,   611,   612,   613,   614,   615,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   628,   629,   630,
     631,   632,   633,   634,   635,   636,   637
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
#line 3987 "parser.cpp"

#line 639 "parser.ypp"


void xsk::gsc::s2::parser::error(const xsk::gsc::location& loc, const std::string& msg)
{
    throw xsk::gsc::comp_error(loc, msg);
}
