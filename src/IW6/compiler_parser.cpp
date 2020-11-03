// A Bison parser, made by GNU Bison 3.7.3.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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
#line 33 "iw6.parser.ypp"

    #include "IW6.hpp"
	#include "compiler_parser.hpp"
	#include "compiler_lexer.hpp"
	yy::parser::symbol_type yylex(yyscan_t yyscanner);

#line 46 "./IW6/compiler_parser.cpp"




#include "compiler_parser.hpp"




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



// Enable debugging if requested.
#if YYDEBUG

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

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 126 "./IW6/compiler_parser.cpp"

  /// Build a parser object.
  parser::parser (yyscan_t yyscanner_yyarg, std::unique_ptr<node>& astout_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      yyscanner (yyscanner_yyarg),
      astout (astout_yyarg)
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
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expr_arg_list: // expr_arg_list
        value.YY_MOVE_OR_COPY< expr_arg_list_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.YY_MOVE_OR_COPY< expr_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.YY_MOVE_OR_COPY< expr_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_pointer_call: // expr_pointer_call
        value.YY_MOVE_OR_COPY< expr_call_type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_filepath: // filepath
        value.YY_MOVE_OR_COPY< filepath_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_float_: // float_
        value.YY_MOVE_OR_COPY< float_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function: // function
        value.YY_MOVE_OR_COPY< function_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.YY_MOVE_OR_COPY< identifier_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.YY_MOVE_OR_COPY< include_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer: // integer
        value.YY_MOVE_OR_COPY< integer_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_selectable: // selectable
      case symbol_kind::S_subscriptable: // subscriptable
      case symbol_kind::S_callable: // callable
      case symbol_kind::S_assignable: // assignable
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
        value.YY_MOVE_OR_COPY< node_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.YY_MOVE_OR_COPY< param_list_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.YY_MOVE_OR_COPY< script_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.YY_MOVE_OR_COPY< stmt_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        value.YY_MOVE_OR_COPY< stmt_block_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.YY_MOVE_OR_COPY< stmt_notify_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
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

      case symbol_kind::S_string_hash: // string_hash
        value.YY_MOVE_OR_COPY< string_hash_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string_loc: // string_loc
        value.YY_MOVE_OR_COPY< string_loc_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string: // string
        value.YY_MOVE_OR_COPY< string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.YY_MOVE_OR_COPY< using_animtree_ptr > (YY_MOVE (that.value));
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
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expr_arg_list: // expr_arg_list
        value.move< expr_arg_list_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< expr_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.move< expr_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_pointer_call: // expr_pointer_call
        value.move< expr_call_type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_filepath: // filepath
        value.move< filepath_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_float_: // float_
        value.move< float_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function: // function
        value.move< function_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< identifier_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.move< include_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer: // integer
        value.move< integer_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_selectable: // selectable
      case symbol_kind::S_subscriptable: // subscriptable
      case symbol_kind::S_callable: // callable
      case symbol_kind::S_assignable: // assignable
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
        value.move< node_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.move< param_list_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< script_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        value.move< stmt_block_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< stmt_notify_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
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

      case symbol_kind::S_string_hash: // string_hash
        value.move< string_hash_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string_loc: // string_loc
        value.move< string_loc_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string: // string
        value.move< string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.move< using_animtree_ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr_arg_list: // expr_arg_list
        value.copy< expr_arg_list_ptr > (that.value);
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.copy< expr_assign_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.copy< expr_call_ptr > (that.value);
        break;

      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_pointer_call: // expr_pointer_call
        value.copy< expr_call_type_ptr > (that.value);
        break;

      case symbol_kind::S_filepath: // filepath
        value.copy< filepath_ptr > (that.value);
        break;

      case symbol_kind::S_float_: // float_
        value.copy< float_ptr > (that.value);
        break;

      case symbol_kind::S_function: // function
        value.copy< function_ptr > (that.value);
        break;

      case symbol_kind::S_identifier: // identifier
        value.copy< identifier_ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.copy< include_ptr > (that.value);
        break;

      case symbol_kind::S_integer: // integer
        value.copy< integer_ptr > (that.value);
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_selectable: // selectable
      case symbol_kind::S_subscriptable: // subscriptable
      case symbol_kind::S_callable: // callable
      case symbol_kind::S_assignable: // assignable
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
        value.copy< node_ptr > (that.value);
        break;

      case symbol_kind::S_param_list: // param_list
        value.copy< param_list_ptr > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.copy< script_ptr > (that.value);
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.copy< stmt_assign_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        value.copy< stmt_block_ptr > (that.value);
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

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.copy< stmt_notify_ptr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
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

      case symbol_kind::S_string_hash: // string_hash
        value.copy< string_hash_ptr > (that.value);
        break;

      case symbol_kind::S_string_loc: // string_loc
        value.copy< string_loc_ptr > (that.value);
        break;

      case symbol_kind::S_string: // string
        value.copy< string_ptr > (that.value);
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.copy< using_animtree_ptr > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_expr_arg_list: // expr_arg_list
        value.move< expr_arg_list_ptr > (that.value);
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< expr_assign_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.move< expr_call_ptr > (that.value);
        break;

      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_pointer_call: // expr_pointer_call
        value.move< expr_call_type_ptr > (that.value);
        break;

      case symbol_kind::S_filepath: // filepath
        value.move< filepath_ptr > (that.value);
        break;

      case symbol_kind::S_float_: // float_
        value.move< float_ptr > (that.value);
        break;

      case symbol_kind::S_function: // function
        value.move< function_ptr > (that.value);
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< identifier_ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.move< include_ptr > (that.value);
        break;

      case symbol_kind::S_integer: // integer
        value.move< integer_ptr > (that.value);
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_selectable: // selectable
      case symbol_kind::S_subscriptable: // subscriptable
      case symbol_kind::S_callable: // callable
      case symbol_kind::S_assignable: // assignable
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
        value.move< node_ptr > (that.value);
        break;

      case symbol_kind::S_param_list: // param_list
        value.move< param_list_ptr > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.move< script_ptr > (that.value);
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< stmt_assign_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        value.move< stmt_block_ptr > (that.value);
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

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< stmt_notify_ptr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
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

      case symbol_kind::S_string_hash: // string_hash
        value.move< string_hash_ptr > (that.value);
        break;

      case symbol_kind::S_string_loc: // string_loc
        value.move< string_loc_ptr > (that.value);
        break;

      case symbol_kind::S_string: // string
        value.move< string_ptr > (that.value);
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.move< using_animtree_ptr > (that.value);
        break;

      default:
        break;
    }

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

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YYUSE (yykind);
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

#if YYDEBUG
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
#endif // YYDEBUG

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
            symbol_type yylookahead (yylex (yyscanner));
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
      case symbol_kind::S_expr_arg_list: // expr_arg_list
        yylhs.value.emplace< expr_arg_list_ptr > ();
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        yylhs.value.emplace< expr_assign_ptr > ();
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        yylhs.value.emplace< expr_call_ptr > ();
        break;

      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_pointer_call: // expr_pointer_call
        yylhs.value.emplace< expr_call_type_ptr > ();
        break;

      case symbol_kind::S_filepath: // filepath
        yylhs.value.emplace< filepath_ptr > ();
        break;

      case symbol_kind::S_float_: // float_
        yylhs.value.emplace< float_ptr > ();
        break;

      case symbol_kind::S_function: // function
        yylhs.value.emplace< function_ptr > ();
        break;

      case symbol_kind::S_identifier: // identifier
        yylhs.value.emplace< identifier_ptr > ();
        break;

      case symbol_kind::S_include: // include
        yylhs.value.emplace< include_ptr > ();
        break;

      case symbol_kind::S_integer: // integer
        yylhs.value.emplace< integer_ptr > ();
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_selectable: // selectable
      case symbol_kind::S_subscriptable: // subscriptable
      case symbol_kind::S_callable: // callable
      case symbol_kind::S_assignable: // assignable
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
        yylhs.value.emplace< node_ptr > ();
        break;

      case symbol_kind::S_param_list: // param_list
        yylhs.value.emplace< param_list_ptr > ();
        break;

      case symbol_kind::S_script: // script
        yylhs.value.emplace< script_ptr > ();
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        yylhs.value.emplace< stmt_assign_ptr > ();
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        yylhs.value.emplace< stmt_block_ptr > ();
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

      case symbol_kind::S_stmt_notify: // stmt_notify
        yylhs.value.emplace< stmt_notify_ptr > ();
        break;

      case symbol_kind::S_stmt: // stmt
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

      case symbol_kind::S_string_hash: // string_hash
        yylhs.value.emplace< string_hash_ptr > ();
        break;

      case symbol_kind::S_string_loc: // string_loc
        yylhs.value.emplace< string_loc_ptr > ();
        break;

      case symbol_kind::S_string: // string
        yylhs.value.emplace< string_ptr > ();
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        yylhs.value.emplace< using_animtree_ptr > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // root: script
#line 109 "iw6.parser.ypp"
                { astout = std::move(yystack_[0].value.as < script_ptr > ()); }
#line 1465 "./IW6/compiler_parser.cpp"
    break;

  case 3: // root: %empty
#line 111 "iw6.parser.ypp"
                { astout = std::make_unique<node>(); }
#line 1471 "./IW6/compiler_parser.cpp"
    break;

  case 4: // script: script include
#line 116 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::move(yystack_[1].value.as < script_ptr > ()); yylhs.value.as < script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1477 "./IW6/compiler_parser.cpp"
    break;

  case 5: // script: script using_animtree
#line 118 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::move(yystack_[1].value.as < script_ptr > ()); yylhs.value.as < script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < using_animtree_ptr > ())); }
#line 1483 "./IW6/compiler_parser.cpp"
    break;

  case 6: // script: script animtree
#line 120 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::move(yystack_[1].value.as < script_ptr > ()); yylhs.value.as < script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < using_animtree_ptr > ())); }
#line 1489 "./IW6/compiler_parser.cpp"
    break;

  case 7: // script: script function
#line 122 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::move(yystack_[1].value.as < script_ptr > ()); yylhs.value.as < script_ptr > ()->functions.push_back(std::move(yystack_[0].value.as < function_ptr > ())); }
#line 1495 "./IW6/compiler_parser.cpp"
    break;

  case 8: // script: include
#line 124 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::make_unique<node_script>(); yylhs.value.as < script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ()));}
#line 1501 "./IW6/compiler_parser.cpp"
    break;

  case 9: // script: using_animtree
#line 126 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::make_unique<node_script>(); yylhs.value.as < script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < using_animtree_ptr > ()));}
#line 1507 "./IW6/compiler_parser.cpp"
    break;

  case 10: // script: animtree
#line 128 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::make_unique<node_script>(); yylhs.value.as < script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < using_animtree_ptr > ()));}
#line 1513 "./IW6/compiler_parser.cpp"
    break;

  case 11: // script: function
#line 130 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::make_unique<node_script>(); yylhs.value.as < script_ptr > ()->functions.push_back(std::move(yystack_[0].value.as < function_ptr > ()));}
#line 1519 "./IW6/compiler_parser.cpp"
    break;

  case 12: // include: INCLUDE filepath SEMICOLON
#line 135 "iw6.parser.ypp"
                { yylhs.value.as < include_ptr > () = std::make_unique<node_include>(std::move(yystack_[1].value.as < filepath_ptr > ())); }
#line 1525 "./IW6/compiler_parser.cpp"
    break;

  case 13: // using_animtree: USING_ANIMTREE LPAREN string RPAREN SEMICOLON
#line 140 "iw6.parser.ypp"
                { yylhs.value.as < using_animtree_ptr > () = std::make_unique<node_using_animtree>(std::move(yystack_[2].value.as < string_ptr > ())); }
#line 1531 "./IW6/compiler_parser.cpp"
    break;

  case 14: // animtree: ANIMTREE LPAREN string RPAREN SEMICOLON
#line 145 "iw6.parser.ypp"
                { yylhs.value.as < using_animtree_ptr > () = std::make_unique<node_using_animtree>(std::move(yystack_[2].value.as < string_ptr > ())); }
#line 1537 "./IW6/compiler_parser.cpp"
    break;

  case 15: // function: identifier LPAREN param_list RPAREN LBRACE stmt_block RBRACE
#line 150 "iw6.parser.ypp"
                { yylhs.value.as < function_ptr > () = std::make_unique<node_function>(std::move(yystack_[6].value.as < identifier_ptr > ()), std::move(yystack_[4].value.as < param_list_ptr > ()), std::move(yystack_[1].value.as < stmt_block_ptr > ())); }
#line 1543 "./IW6/compiler_parser.cpp"
    break;

  case 16: // param_list: param_list COMMA identifier
#line 155 "iw6.parser.ypp"
                { yylhs.value.as < param_list_ptr > () = std::move(yystack_[2].value.as < param_list_ptr > ()); yylhs.value.as < param_list_ptr > ()->params.push_back(std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 1549 "./IW6/compiler_parser.cpp"
    break;

  case 17: // param_list: identifier
#line 157 "iw6.parser.ypp"
                { yylhs.value.as < param_list_ptr > () = std::make_unique<node_param_list>(); yylhs.value.as < param_list_ptr > ()->params.push_back(std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 1555 "./IW6/compiler_parser.cpp"
    break;

  case 18: // param_list: %empty
#line 159 "iw6.parser.ypp"
                { yylhs.value.as < param_list_ptr > () = std::make_unique<node_param_list>(); }
#line 1561 "./IW6/compiler_parser.cpp"
    break;

  case 19: // stmt_block: stmt_block stmt
#line 164 "iw6.parser.ypp"
                { yylhs.value.as < stmt_block_ptr > () = std::move(yystack_[1].value.as < stmt_block_ptr > ()); yylhs.value.as < stmt_block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 1567 "./IW6/compiler_parser.cpp"
    break;

  case 20: // stmt_block: stmt
#line 166 "iw6.parser.ypp"
                { yylhs.value.as < stmt_block_ptr > () = std::make_unique<node_stmt_block>(); yylhs.value.as < stmt_block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 1573 "./IW6/compiler_parser.cpp"
    break;

  case 21: // stmt_block: %empty
#line 168 "iw6.parser.ypp"
                { yylhs.value.as < stmt_block_ptr > () = std::make_unique<node_stmt_block>(); }
#line 1579 "./IW6/compiler_parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 172 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_call = std::move(yystack_[0].value.as < stmt_call_ptr > ()); }
#line 1585 "./IW6/compiler_parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 173 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < stmt_assign_ptr > ()); }
#line 1591 "./IW6/compiler_parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 174 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < stmt_endon_ptr > ()); }
#line 1597 "./IW6/compiler_parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 175 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < stmt_notify_ptr > ()); }
#line 1603 "./IW6/compiler_parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 176 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < stmt_wait_ptr > ()); }
#line 1609 "./IW6/compiler_parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 177 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < stmt_waittill_ptr > ()); }
#line 1615 "./IW6/compiler_parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 178 "iw6.parser.ypp"
                                                                        { yylhs.value.as < stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < stmt_waittillmatch_ptr > ()); }
#line 1621 "./IW6/compiler_parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 179 "iw6.parser.ypp"
                                                                        { yylhs.value.as < stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < stmt_waittillframeend_ptr > ()); }
#line 1627 "./IW6/compiler_parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 180 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < stmt_ptr > ().as_if = std::move(yystack_[0].value.as < stmt_if_ptr > ()); }
#line 1633 "./IW6/compiler_parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 181 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < stmt_ifelse_ptr > ()); }
#line 1639 "./IW6/compiler_parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 182 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_while = std::move(yystack_[0].value.as < stmt_while_ptr > ()); }
#line 1645 "./IW6/compiler_parser.cpp"
    break;

  case 33: // stmt: stmt_for
#line 183 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < stmt_ptr > ().as_for = std::move(yystack_[0].value.as < stmt_for_ptr > ()); }
#line 1651 "./IW6/compiler_parser.cpp"
    break;

  case 34: // stmt: stmt_foreach
#line 184 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < stmt_foreach_ptr > ()); }
#line 1657 "./IW6/compiler_parser.cpp"
    break;

  case 35: // stmt: stmt_switch
#line 185 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < stmt_switch_ptr > ()); }
#line 1663 "./IW6/compiler_parser.cpp"
    break;

  case 36: // stmt: stmt_case
#line 186 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < stmt_ptr > ().as_case = std::move(yystack_[0].value.as < stmt_case_ptr > ()); }
#line 1669 "./IW6/compiler_parser.cpp"
    break;

  case 37: // stmt: stmt_default
#line 187 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_default = std::move(yystack_[0].value.as < stmt_default_ptr > ()); }
#line 1675 "./IW6/compiler_parser.cpp"
    break;

  case 38: // stmt: stmt_break
#line 188 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_break = std::move(yystack_[0].value.as < stmt_break_ptr > ()); }
#line 1681 "./IW6/compiler_parser.cpp"
    break;

  case 39: // stmt: stmt_continue
#line 189 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < stmt_continue_ptr > ()); }
#line 1687 "./IW6/compiler_parser.cpp"
    break;

  case 40: // stmt: stmt_return
#line 190 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_return = std::move(yystack_[0].value.as < stmt_return_ptr > ()); }
#line 1693 "./IW6/compiler_parser.cpp"
    break;

  case 41: // stmt_call: expr_call SEMICOLON
#line 195 "iw6.parser.ypp"
                { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 1699 "./IW6/compiler_parser.cpp"
    break;

  case 42: // stmt_call: expr_call_thread SEMICOLON
#line 197 "iw6.parser.ypp"
                { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 1705 "./IW6/compiler_parser.cpp"
    break;

  case 43: // stmt_assign: expr_assign SEMICOLON
#line 202 "iw6.parser.ypp"
                { yylhs.value.as < stmt_assign_ptr > () = std::make_unique<node_stmt_assign>(std::move(yystack_[1].value.as < expr_assign_ptr > ())); }
#line 1711 "./IW6/compiler_parser.cpp"
    break;

  case 44: // stmt_endon: callable ENDON LPAREN expr RPAREN SEMICOLON
#line 207 "iw6.parser.ypp"
                { yylhs.value.as < stmt_endon_ptr > () = std::make_unique<node_stmt_endon>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ())); }
#line 1717 "./IW6/compiler_parser.cpp"
    break;

  case 45: // stmt_notify: callable NOTIFY LPAREN expr COMMA expr_arg_list RPAREN SEMICOLON
#line 212 "iw6.parser.ypp"
                { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_arg_list_ptr > ())); }
#line 1723 "./IW6/compiler_parser.cpp"
    break;

  case 46: // stmt_notify: callable NOTIFY LPAREN expr RPAREN SEMICOLON
#line 214 "iw6.parser.ypp"
                { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::make_unique<node>()); }
#line 1729 "./IW6/compiler_parser.cpp"
    break;

  case 47: // stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON
#line 219 "iw6.parser.ypp"
                { yylhs.value.as < stmt_wait_ptr > () = std::make_unique<node_stmt_wait>(std::move(yystack_[2].value.as < node_ptr > ())); }
#line 1735 "./IW6/compiler_parser.cpp"
    break;

  case 48: // stmt_wait: WAIT num SEMICOLON
#line 221 "iw6.parser.ypp"
                { yylhs.value.as < stmt_wait_ptr > () = std::make_unique<node_stmt_wait>(std::move(yystack_[1].value.as < node_ptr > ())); }
#line 1741 "./IW6/compiler_parser.cpp"
    break;

  case 49: // stmt_waittill: callable WAITTILL LPAREN expr COMMA expr_arg_list RPAREN SEMICOLON
#line 226 "iw6.parser.ypp"
                { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_arg_list_ptr > ())); }
#line 1747 "./IW6/compiler_parser.cpp"
    break;

  case 50: // stmt_waittill: callable WAITTILL LPAREN expr RPAREN SEMICOLON
#line 228 "iw6.parser.ypp"
                { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::make_unique<node>()); }
#line 1753 "./IW6/compiler_parser.cpp"
    break;

  case 51: // stmt_waittillmatch: callable WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON
#line 233 "iw6.parser.ypp"
                { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ())); }
#line 1759 "./IW6/compiler_parser.cpp"
    break;

  case 52: // stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON
#line 238 "iw6.parser.ypp"
                { yylhs.value.as < stmt_waittillframeend_ptr > () = std::make_unique<node_stmt_waittillframeend>(); }
#line 1765 "./IW6/compiler_parser.cpp"
    break;

  case 53: // stmt_if: IF LPAREN expr RPAREN LBRACE stmt_block RBRACE
#line 243 "iw6.parser.ypp"
                { yylhs.value.as < stmt_if_ptr > () = std::make_unique<node_stmt_if>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < stmt_block_ptr > ())); }
#line 1771 "./IW6/compiler_parser.cpp"
    break;

  case 54: // stmt_if: IF LPAREN expr RPAREN stmt
#line 245 "iw6.parser.ypp"
                { yylhs.value.as < stmt_if_ptr > () = std::make_unique<node_stmt_if>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1777 "./IW6/compiler_parser.cpp"
    break;

  case 55: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE stmt_block RBRACE ELSE LBRACE stmt_block RBRACE
#line 250 "iw6.parser.ypp"
                { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[8].value.as < node_ptr > ()), std::move(yystack_[5].value.as < stmt_block_ptr > ()), std::move(yystack_[1].value.as < stmt_block_ptr > ())); }
#line 1783 "./IW6/compiler_parser.cpp"
    break;

  case 56: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE stmt_block RBRACE
#line 252 "iw6.parser.ypp"
                { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[4].value.as < stmt_ptr > ().as_node), std::move(yystack_[1].value.as < stmt_block_ptr > ())); }
#line 1789 "./IW6/compiler_parser.cpp"
    break;

  case 57: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE stmt_block RBRACE ELSE stmt
#line 254 "iw6.parser.ypp"
                { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[3].value.as < stmt_block_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1795 "./IW6/compiler_parser.cpp"
    break;

  case 58: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt
#line 256 "iw6.parser.ypp"
                { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ().as_node), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1801 "./IW6/compiler_parser.cpp"
    break;

  case 59: // stmt_while: WHILE LPAREN expr RPAREN LBRACE stmt_block RBRACE
#line 261 "iw6.parser.ypp"
                { yylhs.value.as < stmt_while_ptr > () = std::make_unique<node_stmt_while>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < stmt_block_ptr > ())); }
#line 1807 "./IW6/compiler_parser.cpp"
    break;

  case 60: // stmt_while: WHILE LPAREN expr RPAREN stmt
#line 263 "iw6.parser.ypp"
                { yylhs.value.as < stmt_while_ptr > () = std::make_unique<node_stmt_while>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1813 "./IW6/compiler_parser.cpp"
    break;

  case 61: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE stmt_block RBRACE
#line 268 "iw6.parser.ypp"
                { yylhs.value.as < stmt_for_ptr > () = std::make_unique<node_stmt_for>(std::move(yystack_[8].value.as < node_ptr > ()), std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < stmt_block_ptr > ())); }
#line 1819 "./IW6/compiler_parser.cpp"
    break;

  case 62: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt
#line 270 "iw6.parser.ypp"
                { yylhs.value.as < stmt_for_ptr > () = std::make_unique< node_stmt_for>(std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1825 "./IW6/compiler_parser.cpp"
    break;

  case 63: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE stmt_block RBRACE
#line 275 "iw6.parser.ypp"
                { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < stmt_block_ptr > ())); }
#line 1831 "./IW6/compiler_parser.cpp"
    break;

  case 64: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt
#line 277 "iw6.parser.ypp"
                { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1837 "./IW6/compiler_parser.cpp"
    break;

  case 65: // stmt_switch: SWITCH LPAREN expr RPAREN LBRACE stmt_block RBRACE
#line 282 "iw6.parser.ypp"
                { yylhs.value.as < stmt_switch_ptr > () = std::make_unique<node_stmt_switch>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < stmt_block_ptr > ())); }
#line 1843 "./IW6/compiler_parser.cpp"
    break;

  case 66: // stmt_case: CASE integer COLON
#line 287 "iw6.parser.ypp"
                { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(std::move(yystack_[1].value.as < integer_ptr > ())); }
#line 1849 "./IW6/compiler_parser.cpp"
    break;

  case 67: // stmt_case: CASE string COLON
#line 289 "iw6.parser.ypp"
                { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(std::move(yystack_[1].value.as < string_ptr > ())); }
#line 1855 "./IW6/compiler_parser.cpp"
    break;

  case 68: // stmt_default: DEFAULT COLON
#line 294 "iw6.parser.ypp"
                { yylhs.value.as < stmt_default_ptr > () = std::make_unique<node_stmt_default>(); }
#line 1861 "./IW6/compiler_parser.cpp"
    break;

  case 69: // stmt_break: BREAK SEMICOLON
#line 299 "iw6.parser.ypp"
                { yylhs.value.as < stmt_break_ptr > () = std::make_unique<node_stmt_break>(); }
#line 1867 "./IW6/compiler_parser.cpp"
    break;

  case 70: // stmt_continue: CONTINUE SEMICOLON
#line 303 "iw6.parser.ypp"
                { yylhs.value.as < stmt_continue_ptr > () = std::make_unique<node_stmt_continue>(); }
#line 1873 "./IW6/compiler_parser.cpp"
    break;

  case 71: // stmt_return: RETURN expr SEMICOLON
#line 308 "iw6.parser.ypp"
                { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(std::move(yystack_[1].value.as < node_ptr > ())); }
#line 1879 "./IW6/compiler_parser.cpp"
    break;

  case 72: // stmt_return: RETURN SEMICOLON
#line 310 "iw6.parser.ypp"
                { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(std::make_unique<node>()); }
#line 1885 "./IW6/compiler_parser.cpp"
    break;

  case 73: // for_assign: expr_assign
#line 314 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_assign_ptr > ()); }
#line 1891 "./IW6/compiler_parser.cpp"
    break;

  case 74: // for_assign: %empty
#line 315 "iw6.parser.ypp"
                                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node>(); }
#line 1897 "./IW6/compiler_parser.cpp"
    break;

  case 75: // for_cond: expr_cmp
#line 319 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1903 "./IW6/compiler_parser.cpp"
    break;

  case 76: // for_cond: %empty
#line 320 "iw6.parser.ypp"
                                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node>(); }
#line 1909 "./IW6/compiler_parser.cpp"
    break;

  case 77: // expr: expr_cmp
#line 324 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1915 "./IW6/compiler_parser.cpp"
    break;

  case 78: // expr: expr_ternary
#line 325 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1921 "./IW6/compiler_parser.cpp"
    break;

  case 79: // expr: expr_binary
#line 326 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1927 "./IW6/compiler_parser.cpp"
    break;

  case 80: // expr: expr_unary
#line 327 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1933 "./IW6/compiler_parser.cpp"
    break;

  case 81: // expr_assign: assignable INC
#line 331 "iw6.parser.ypp"
                                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_inc>(std::move(yystack_[1].value.as < node_ptr > ())); }
#line 1939 "./IW6/compiler_parser.cpp"
    break;

  case 82: // expr_assign: assignable DEC
#line 332 "iw6.parser.ypp"
                                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_dec>(std::move(yystack_[1].value.as < node_ptr > ())); }
#line 1945 "./IW6/compiler_parser.cpp"
    break;

  case 83: // expr_assign: assignable ASSIGN expr
#line 333 "iw6.parser.ypp"
                                                                { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_equal>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1951 "./IW6/compiler_parser.cpp"
    break;

  case 84: // expr_assign: assignable ASSIGN_BW_OR expr
#line 334 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bw_or>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1957 "./IW6/compiler_parser.cpp"
    break;

  case 85: // expr_assign: assignable ASSIGN_BW_AND expr
#line 335 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bw_and>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1963 "./IW6/compiler_parser.cpp"
    break;

  case 86: // expr_assign: assignable ASSIGN_BW_XOR expr
#line 336 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bw_xor>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1969 "./IW6/compiler_parser.cpp"
    break;

  case 87: // expr_assign: assignable ASSIGN_LSHIFT expr
#line 337 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_left>(std::move(yystack_[2].value.as < node_ptr > ()),std::move( yystack_[0].value.as < node_ptr > ())); }
#line 1975 "./IW6/compiler_parser.cpp"
    break;

  case 88: // expr_assign: assignable ASSIGN_RSHIFT expr
#line 338 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_right>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1981 "./IW6/compiler_parser.cpp"
    break;

  case 89: // expr_assign: assignable ASSIGN_ADD expr
#line 339 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_add>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1987 "./IW6/compiler_parser.cpp"
    break;

  case 90: // expr_assign: assignable ASSIGN_SUB expr
#line 340 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_sub>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1993 "./IW6/compiler_parser.cpp"
    break;

  case 91: // expr_assign: assignable ASSIGN_MULT expr
#line 341 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mult>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1999 "./IW6/compiler_parser.cpp"
    break;

  case 92: // expr_assign: assignable ASSIGN_DIV expr
#line 342 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_div>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2005 "./IW6/compiler_parser.cpp"
    break;

  case 93: // expr_assign: assignable ASSIGN_MOD expr
#line 343 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mod>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2011 "./IW6/compiler_parser.cpp"
    break;

  case 94: // expr_cmp: expr CMP_OR expr
#line 347 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_cmp_or>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2017 "./IW6/compiler_parser.cpp"
    break;

  case 95: // expr_cmp: expr CMP_AND expr
#line 348 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_cmp_and>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2023 "./IW6/compiler_parser.cpp"
    break;

  case 96: // expr_cmp: expr CMP_EQUAL expr
#line 349 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_cmp_equal>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2029 "./IW6/compiler_parser.cpp"
    break;

  case 97: // expr_cmp: expr CMP_NOT_EQ expr
#line 350 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_cmp_not_equal>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2035 "./IW6/compiler_parser.cpp"
    break;

  case 98: // expr_cmp: expr CMP_LESS_EQ expr
#line 351 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_cmp_less_equal>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2041 "./IW6/compiler_parser.cpp"
    break;

  case 99: // expr_cmp: expr CMP_GREATER_EQ expr
#line 352 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_cmp_greater_equal>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2047 "./IW6/compiler_parser.cpp"
    break;

  case 100: // expr_cmp: expr CMP_LESS expr
#line 353 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_cmp_less>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2053 "./IW6/compiler_parser.cpp"
    break;

  case 101: // expr_cmp: expr CMP_GREATER expr
#line 354 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_cmp_greater>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2059 "./IW6/compiler_parser.cpp"
    break;

  case 102: // expr_ternary: expr_cmp QMARK expr COLON expr
#line 358 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_ternary>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2065 "./IW6/compiler_parser.cpp"
    break;

  case 103: // expr_binary: expr BW_OR expr
#line 362 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_bw_or>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2071 "./IW6/compiler_parser.cpp"
    break;

  case 104: // expr_binary: expr BW_AND expr
#line 363 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_bw_and>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2077 "./IW6/compiler_parser.cpp"
    break;

  case 105: // expr_binary: expr BW_XOR expr
#line 364 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_bw_xor>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2083 "./IW6/compiler_parser.cpp"
    break;

  case 106: // expr_binary: expr LSHIFT expr
#line 365 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_shift_left>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2089 "./IW6/compiler_parser.cpp"
    break;

  case 107: // expr_binary: expr RSHIFT expr
#line 366 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_shift_right>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2095 "./IW6/compiler_parser.cpp"
    break;

  case 108: // expr_binary: expr ADD expr
#line 367 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_add>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2101 "./IW6/compiler_parser.cpp"
    break;

  case 109: // expr_binary: expr SUB expr
#line 368 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_sub>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2107 "./IW6/compiler_parser.cpp"
    break;

  case 110: // expr_binary: expr MULT expr
#line 369 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_mult>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2113 "./IW6/compiler_parser.cpp"
    break;

  case 111: // expr_binary: expr DIV expr
#line 370 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_div>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2119 "./IW6/compiler_parser.cpp"
    break;

  case 112: // expr_binary: expr MOD expr
#line 371 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_mod>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2125 "./IW6/compiler_parser.cpp"
    break;

  case 113: // expr_unary: COMPLEMENT expr
#line 375 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_complement>(std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2131 "./IW6/compiler_parser.cpp"
    break;

  case 114: // expr_unary: NOT expr
#line 376 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_not>(std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2137 "./IW6/compiler_parser.cpp"
    break;

  case 115: // expr_unary: expr_call
#line 377 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2143 "./IW6/compiler_parser.cpp"
    break;

  case 116: // expr_unary: expr_call_thread
#line 378 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2149 "./IW6/compiler_parser.cpp"
    break;

  case 117: // expr_unary: expr_select
#line 379 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2155 "./IW6/compiler_parser.cpp"
    break;

  case 118: // expr_unary: expr_subscribe
#line 380 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2161 "./IW6/compiler_parser.cpp"
    break;

  case 119: // expr_unary: expr_func_ref
#line 381 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2167 "./IW6/compiler_parser.cpp"
    break;

  case 120: // expr_unary: empty_array
#line 382 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2173 "./IW6/compiler_parser.cpp"
    break;

  case 121: // expr_unary: undefined
#line 383 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2179 "./IW6/compiler_parser.cpp"
    break;

  case 122: // expr_unary: LPAREN expr COMMA expr COMMA expr RPAREN
#line 384 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_vector>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2185 "./IW6/compiler_parser.cpp"
    break;

  case 123: // expr_unary: vector
#line 385 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2191 "./IW6/compiler_parser.cpp"
    break;

  case 124: // expr_unary: num
#line 386 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2197 "./IW6/compiler_parser.cpp"
    break;

  case 125: // expr_unary: string_hash
#line 387 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < string_hash_ptr > ()); }
#line 2203 "./IW6/compiler_parser.cpp"
    break;

  case 126: // expr_unary: string_loc
#line 388 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < string_loc_ptr > ()); }
#line 2209 "./IW6/compiler_parser.cpp"
    break;

  case 127: // expr_unary: string
#line 389 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < string_ptr > ()); }
#line 2215 "./IW6/compiler_parser.cpp"
    break;

  case 128: // expr_unary: identifier
#line 390 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < identifier_ptr > ()); }
#line 2221 "./IW6/compiler_parser.cpp"
    break;

  case 129: // expr_unary: level
#line 391 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2227 "./IW6/compiler_parser.cpp"
    break;

  case 130: // expr_unary: anim
#line 392 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2233 "./IW6/compiler_parser.cpp"
    break;

  case 131: // expr_unary: self
#line 393 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2239 "./IW6/compiler_parser.cpp"
    break;

  case 132: // expr_unary: game
#line 394 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2245 "./IW6/compiler_parser.cpp"
    break;

  case 133: // expr_unary: LPAREN expr RPAREN
#line 395 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[1].value.as < node_ptr > ()); }
#line 2251 "./IW6/compiler_parser.cpp"
    break;

  case 134: // expr_call: expr_func_call
#line 399 "iw6.parser.ypp"
                                                                                { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(false, std::make_unique<node>(), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2257 "./IW6/compiler_parser.cpp"
    break;

  case 135: // expr_call: expr_pointer_call
#line 400 "iw6.parser.ypp"
                                                                                { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(false, std::make_unique<node>(), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2263 "./IW6/compiler_parser.cpp"
    break;

  case 136: // expr_call: callable expr_func_call
#line 401 "iw6.parser.ypp"
                                                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2269 "./IW6/compiler_parser.cpp"
    break;

  case 137: // expr_call: callable expr_pointer_call
#line 402 "iw6.parser.ypp"
                                                                { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2275 "./IW6/compiler_parser.cpp"
    break;

  case 138: // expr_call_thread: THREAD expr_func_call
#line 406 "iw6.parser.ypp"
                                                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(true, std::make_unique<node>(), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2281 "./IW6/compiler_parser.cpp"
    break;

  case 139: // expr_call_thread: THREAD expr_pointer_call
#line 407 "iw6.parser.ypp"
                                                                { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(true, std::make_unique<node>(), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2287 "./IW6/compiler_parser.cpp"
    break;

  case 140: // expr_call_thread: callable THREAD expr_func_call
#line 408 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2293 "./IW6/compiler_parser.cpp"
    break;

  case 141: // expr_call_thread: callable THREAD expr_pointer_call
#line 409 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2299 "./IW6/compiler_parser.cpp"
    break;

  case 142: // expr_func_call: identifier LPAREN expr_arg_list RPAREN
#line 414 "iw6.parser.ypp"
                {yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_func_call>(std::make_unique<node_filepath>(""), std::move(yystack_[3].value.as < identifier_ptr > ()), std::move(yystack_[1].value.as < expr_arg_list_ptr > ())); }
#line 2305 "./IW6/compiler_parser.cpp"
    break;

  case 143: // expr_func_call: filepath DOUBLECOLON identifier LPAREN expr_arg_list RPAREN
#line 416 "iw6.parser.ypp"
                { yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_func_call>(std::move(yystack_[5].value.as < filepath_ptr > ()), std::move(yystack_[3].value.as < identifier_ptr > ()), std::move(yystack_[1].value.as < expr_arg_list_ptr > ())); }
#line 2311 "./IW6/compiler_parser.cpp"
    break;

  case 144: // expr_pointer_call: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arg_list RPAREN
#line 421 "iw6.parser.ypp"
                { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_pointer_call>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[1].value.as < expr_arg_list_ptr > ())); }
#line 2317 "./IW6/compiler_parser.cpp"
    break;

  case 145: // expr_arg_list: expr_arg_list COMMA expr
#line 426 "iw6.parser.ypp"
                { yylhs.value.as < expr_arg_list_ptr > () = std::move(yystack_[2].value.as < expr_arg_list_ptr > ()); yylhs.value.as < expr_arg_list_ptr > ()->args.push_back(std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2323 "./IW6/compiler_parser.cpp"
    break;

  case 146: // expr_arg_list: expr
#line 428 "iw6.parser.ypp"
                { yylhs.value.as < expr_arg_list_ptr > () = std::make_unique<node_expr_arg_list>(); yylhs.value.as < expr_arg_list_ptr > ()->args.push_back(std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2329 "./IW6/compiler_parser.cpp"
    break;

  case 147: // expr_arg_list: %empty
#line 430 "iw6.parser.ypp"
                { yylhs.value.as < expr_arg_list_ptr > () = std::make_unique<node_expr_arg_list>(); }
#line 2335 "./IW6/compiler_parser.cpp"
    break;

  case 148: // expr_func_ref: DOUBLECOLON identifier
#line 435 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_func_ref>(std::make_unique<node_filepath>(""), std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 2341 "./IW6/compiler_parser.cpp"
    break;

  case 149: // expr_func_ref: filepath DOUBLECOLON identifier
#line 437 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_func_ref>(std::move(yystack_[2].value.as < filepath_ptr > ()), std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 2347 "./IW6/compiler_parser.cpp"
    break;

  case 150: // expr_select: selectable DOT identifier
#line 442 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_select>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 2353 "./IW6/compiler_parser.cpp"
    break;

  case 151: // expr_select: selectable DOT size
#line 444 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_select>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2359 "./IW6/compiler_parser.cpp"
    break;

  case 152: // expr_subscribe: subscriptable LBRACKET expr RBRACKET
#line 449 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_subscribe>(std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2365 "./IW6/compiler_parser.cpp"
    break;

  case 153: // selectable: expr_call
#line 453 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2371 "./IW6/compiler_parser.cpp"
    break;

  case 154: // selectable: expr_subscribe
#line 454 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2377 "./IW6/compiler_parser.cpp"
    break;

  case 155: // selectable: expr_select
#line 455 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2383 "./IW6/compiler_parser.cpp"
    break;

  case 156: // selectable: identifier
#line 456 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < identifier_ptr > ()); }
#line 2389 "./IW6/compiler_parser.cpp"
    break;

  case 157: // selectable: level
#line 457 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2395 "./IW6/compiler_parser.cpp"
    break;

  case 158: // selectable: anim
#line 458 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2401 "./IW6/compiler_parser.cpp"
    break;

  case 159: // selectable: self
#line 459 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2407 "./IW6/compiler_parser.cpp"
    break;

  case 160: // subscriptable: expr_call
#line 463 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2413 "./IW6/compiler_parser.cpp"
    break;

  case 161: // subscriptable: expr_subscribe
#line 464 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2419 "./IW6/compiler_parser.cpp"
    break;

  case 162: // subscriptable: expr_select
#line 465 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2425 "./IW6/compiler_parser.cpp"
    break;

  case 163: // subscriptable: identifier
#line 466 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < identifier_ptr > ()); }
#line 2431 "./IW6/compiler_parser.cpp"
    break;

  case 164: // subscriptable: game
#line 467 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2437 "./IW6/compiler_parser.cpp"
    break;

  case 165: // callable: expr_call
#line 471 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2443 "./IW6/compiler_parser.cpp"
    break;

  case 166: // callable: expr_subscribe
#line 472 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2449 "./IW6/compiler_parser.cpp"
    break;

  case 167: // callable: expr_select
#line 473 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2455 "./IW6/compiler_parser.cpp"
    break;

  case 168: // callable: identifier
#line 474 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < identifier_ptr > ()); }
#line 2461 "./IW6/compiler_parser.cpp"
    break;

  case 169: // callable: level
#line 475 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2467 "./IW6/compiler_parser.cpp"
    break;

  case 170: // callable: anim
#line 476 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2473 "./IW6/compiler_parser.cpp"
    break;

  case 171: // callable: self
#line 477 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2479 "./IW6/compiler_parser.cpp"
    break;

  case 172: // assignable: expr_subscribe
#line 481 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2485 "./IW6/compiler_parser.cpp"
    break;

  case 173: // assignable: expr_select
#line 482 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2491 "./IW6/compiler_parser.cpp"
    break;

  case 174: // assignable: identifier
#line 483 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < identifier_ptr > ()); }
#line 2497 "./IW6/compiler_parser.cpp"
    break;

  case 175: // size: SIZE
#line 488 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_size>(); }
#line 2503 "./IW6/compiler_parser.cpp"
    break;

  case 176: // false: FALSE
#line 493 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_integer>("0"); }
#line 2509 "./IW6/compiler_parser.cpp"
    break;

  case 177: // true: TRUE
#line 498 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_integer>("1"); }
#line 2515 "./IW6/compiler_parser.cpp"
    break;

  case 178: // self: SELF
#line 503 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_self>(); }
#line 2521 "./IW6/compiler_parser.cpp"
    break;

  case 179: // anim: ANIM
#line 508 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_anim>(); }
#line 2527 "./IW6/compiler_parser.cpp"
    break;

  case 180: // level: LEVEL
#line 513 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_level>(); }
#line 2533 "./IW6/compiler_parser.cpp"
    break;

  case 181: // game: GAME
#line 518 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_game>(); }
#line 2539 "./IW6/compiler_parser.cpp"
    break;

  case 182: // empty_array: EMPTY_ARRAY
#line 523 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_empty_array>(); }
#line 2545 "./IW6/compiler_parser.cpp"
    break;

  case 183: // undefined: UNDEFINED
#line 528 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_undefined>(); }
#line 2551 "./IW6/compiler_parser.cpp"
    break;

  case 184: // vector: LPAREN num COMMA num COMMA num RPAREN
#line 533 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_vector>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2557 "./IW6/compiler_parser.cpp"
    break;

  case 185: // num: float_
#line 537 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2563 "./IW6/compiler_parser.cpp"
    break;

  case 186: // num: integer
#line 538 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2569 "./IW6/compiler_parser.cpp"
    break;

  case 187: // num: false
#line 539 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2575 "./IW6/compiler_parser.cpp"
    break;

  case 188: // num: true
#line 540 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2581 "./IW6/compiler_parser.cpp"
    break;

  case 189: // float_: FLOAT
#line 544 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yystack_[0].value.as < std::string > ()); }
#line 2587 "./IW6/compiler_parser.cpp"
    break;

  case 190: // integer: INTEGER
#line 548 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yystack_[0].value.as < std::string > ()); }
#line 2593 "./IW6/compiler_parser.cpp"
    break;

  case 191: // string_hash: STRING_HASH
#line 552 "iw6.parser.ypp"
                                                                                { yylhs.value.as < string_hash_ptr > () = std::make_unique<node_string_hash>(yystack_[0].value.as < std::string > ()); }
#line 2599 "./IW6/compiler_parser.cpp"
    break;

  case 192: // string_loc: STRING_LOC
#line 556 "iw6.parser.ypp"
                                                                                { yylhs.value.as < string_loc_ptr > () = std::make_unique<node_string_loc>(yystack_[0].value.as < std::string > ()); }
#line 2605 "./IW6/compiler_parser.cpp"
    break;

  case 193: // string: STRING
#line 560 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < string_ptr > () = std::make_unique<node_string>(yystack_[0].value.as < std::string > ()); }
#line 2611 "./IW6/compiler_parser.cpp"
    break;

  case 194: // identifier: IDENTIFIER
#line 564 "iw6.parser.ypp"
                                                                                { yylhs.value.as < identifier_ptr > () = std::make_unique<node_identifier>(yystack_[0].value.as < std::string > ()); }
#line 2617 "./IW6/compiler_parser.cpp"
    break;

  case 195: // filepath: FILEPATH
#line 568 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < filepath_ptr > () = std::make_unique<node_filepath>(yystack_[0].value.as < std::string > ()); }
#line 2623 "./IW6/compiler_parser.cpp"
    break;


#line 2627 "./IW6/compiler_parser.cpp"

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
        error (YY_MOVE (msg));
      }


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

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


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
    error (yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "INCLUDE", "USING_ANIMTREE",
  "ANIMTREE", "IF", "ELSE", "SWITCH", "CASE", "DEFAULT", "BREAK", "FOR",
  "FOREACH", "WHILE", "CONTINUE", "RETURN", "THREAD", "WAIT", "WAITTILL",
  "WAITTILLMATCH", "WAITTILLFRAMEEND", "ENDON", "NOTIFY", "IN",
  "UNDEFINED", "TRUE", "FALSE", "SIZE", "GAME", "LEVEL", "ANIM", "SELF",
  "EMPTY_ARRAY", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "COMMA", "DOT", "DOUBLECOLON", "COLON", "SEMICOLON", "QMARK",
  "MOD", "INC", "DEC", "LSHIFT", "RSHIFT", "CMP_OR", "CMP_AND",
  "CMP_EQUAL", "CMP_NOT_EQ", "CMP_LESS_EQ", "CMP_GREATER_EQ", "CMP_LESS",
  "CMP_GREATER", "ASSIGN", "ASSIGN_ADD", "ASSIGN_SUB", "ASSIGN_MULT",
  "ASSIGN_DIV", "ASSIGN_MOD", "ASSIGN_BW_OR", "ASSIGN_BW_AND",
  "ASSIGN_BW_XOR", "ASSIGN_LSHIFT", "ASSIGN_RSHIFT", "BW_OR", "BW_AND",
  "BW_XOR", "ADD", "SUB", "MULT", "DIV", "NOT", "COMPLEMENT", "FILEPATH",
  "IDENTIFIER", "STRING", "STRING_LOC", "STRING_HASH", "FLOAT", "INTEGER",
  "IFX", "$accept", "root", "script", "include", "using_animtree",
  "animtree", "function", "param_list", "stmt_block", "stmt", "stmt_call",
  "stmt_assign", "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case",
  "stmt_default", "stmt_break", "stmt_continue", "stmt_return",
  "for_assign", "for_cond", "expr", "expr_assign", "expr_cmp",
  "expr_ternary", "expr_binary", "expr_unary", "expr_call",
  "expr_call_thread", "expr_func_call", "expr_pointer_call",
  "expr_arg_list", "expr_func_ref", "expr_select", "expr_subscribe",
  "selectable", "subscriptable", "callable", "assignable", "size", "false",
  "true", "self", "anim", "level", "game", "empty_array", "undefined",
  "vector", "num", "float_", "integer", "string_hash", "string_loc",
  "string", "identifier", "filepath", YY_NULLPTR
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

#if YYDEBUG
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
#if YYDEBUG
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
#if YYDEBUG
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

  const short parser::yytable_ninf_ = -172;

  const short
  parser::yypact_[] =
  {
       5,   -74,   -21,   -12,  -261,    30,     5,  -261,  -261,  -261,
    -261,    -1,  -261,     6,   -32,   -32,  -261,  -261,  -261,  -261,
    -261,    10,  -261,  -261,    52,    69,   -11,  -261,    80,    83,
      77,    10,  -261,  -261,  1440,  -261,    92,    94,   -23,    72,
      85,    96,    97,    99,    91,   898,   -24,    26,    93,  -261,
    -261,  -261,  -261,    98,   159,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,    95,   -18,   101,  -261,  -261,
     231,   382,   105,   102,   504,  1442,   107,   108,   111,  -261,
     196,   112,  1450,  1450,  -261,   123,   138,  -261,  -261,   539,
    1450,  1450,  -261,  -261,  -261,  -261,  -261,  1450,    10,  -261,
    1450,  1450,  -261,  -261,  -261,  2050,   113,  -261,  -261,  -261,
     -13,  -261,  -261,   115,   121,    27,  -261,  -261,   144,   146,
     194,   155,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,    71,   141,  -261,  -261,   164,  1450,   158,  -261,  1450,
    -261,  -261,  -261,  -261,  -261,   -17,  1450,   -24,   170,   171,
     173,   178,  -261,  -261,  -261,  -261,  1450,  1450,  1450,  1450,
    1450,  1450,  1450,  1450,  1450,  1450,  1450,  1450,    10,  1616,
    1647,  -261,  -261,   176,  -261,   -26,   -24,   624,  1678,  1501,
     177,  -261,  2081,  2081,  -261,  1450,  1450,  1450,  1450,  1450,
    1450,  1450,  1450,  1450,  1450,  1450,  1450,  1450,  1450,  1450,
    1450,  1450,  1450,  1450,    10,  1709,  -261,  1871,  -261,  -261,
    -261,  1909,  -261,  -261,  1450,  1450,  1450,  1450,  2081,  2081,
    2081,  2081,  2081,  2081,  2081,  2081,  2081,  2081,  2081,  2081,
      -8,   188,    62,   191,  1450,  1450,   742,  -261,  1450,    11,
    2081,  2081,  2081,  2081,  2081,  2081,  2081,  2081,  2081,  2081,
    2081,  2081,  2081,  2081,  2081,  2081,  2081,  2081,  2017,   188,
     184,   192,  -261,  1543,  1946,  1740,  1585,  -261,  1450,  1450,
    1440,   226,  1440,   197,  2081,    58,  1771,  1440,  -261,  1983,
     200,  1450,  -261,   202,   199,  1450,  1450,   201,   203,  1450,
    2081,     7,  1020,  1054,  1099,   539,  1132,  1176,  1450,    11,
    2081,  1450,  -261,     8,  1802,  -261,  -261,    81,  -261,   245,
    1440,  -261,  -261,   220,  1440,  -261,  -261,  1833,   221,    82,
     213,   214,   215,  1209,  1253,  1286,  1330,  -261,  -261,  -261,
    -261,  -261,  -261,  1440,  -261,  -261,  1440,  -261,  -261,  1363,
    1407,  -261,  -261
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,   194,     0,     2,     8,     9,    10,
      11,     0,   195,     0,     0,     0,     1,     4,     5,     6,
       7,    18,    12,   193,     0,     0,     0,    17,     0,     0,
       0,     0,    13,    14,    21,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   181,
     180,   179,   178,     0,     0,    20,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,   165,     0,   134,   135,
     173,   172,     0,     0,     0,     0,   171,   170,   169,   164,
     174,     0,     0,     0,   190,     0,     0,    68,    69,    74,
       0,     0,    70,   183,   177,   176,   182,     0,     0,    72,
       0,     0,   192,   191,   189,     0,    77,    78,    79,    80,
     115,   116,   119,   117,   118,     0,   187,   188,   131,   130,
     129,   132,   120,   121,   123,   124,   185,   186,   125,   126,
     127,   128,     0,   138,   139,     0,     0,     0,    52,     0,
      15,    19,    43,    41,    42,     0,     0,     0,     0,     0,
       0,     0,   136,   137,    81,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   147,     0,     0,
       0,    66,    67,     0,    73,   165,     0,     0,     0,     0,
     124,   148,   114,   113,    71,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,     0,   175,   151,
     150,     0,   140,   141,     0,     0,     0,     0,    83,    89,
      90,    91,    92,    93,    84,    85,    86,    87,    88,   146,
       0,     0,     0,     0,    76,     0,     0,   133,     0,     0,
     112,   106,   107,    94,    95,    96,    97,    98,    99,   100,
     101,   103,   104,   105,   108,   109,   110,   111,     0,   149,
       0,     0,   152,     0,     0,     0,     0,   142,     0,   147,
      21,    54,    21,     0,     0,    77,     0,    21,    60,     0,
       0,     0,    47,     0,     0,   147,     0,     0,     0,   147,
     145,     0,     0,     0,     0,    74,     0,     0,     0,     0,
     102,   147,    50,     0,     0,    44,    46,     0,   143,    53,
      21,    58,    65,     0,    21,    64,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   184,   144,
      49,    51,    45,    21,    57,    56,    21,    62,    63,     0,
       0,    55,    61
  };

  const short
  parser::yypgoto_[] =
  {
    -261,  -261,  -261,   254,   255,   256,   259,  -261,  -223,   -36,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,   -27,
    -261,   798,   -97,    39,  -261,  -261,  -261,   110,   568,   -43,
     -39,  -260,  -261,   145,   195,  -261,  -261,   230,  -261,  -261,
    -261,  -261,   310,   385,   462,   533,  -261,  -261,  -261,   -46,
    -261,   241,  -261,  -261,     2,     0,    35
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,     9,    10,    26,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   183,
     283,   239,    75,   116,   117,   118,   119,   120,   121,    78,
      79,   240,   122,   123,   124,    82,    83,   125,    85,   219,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142
  };

  const short
  parser::yytable_[] =
  {
      11,   147,   184,   143,  -165,    12,    11,   144,     1,     2,
       3,   218,  -160,    14,    53,  -153,    24,    25,   151,   301,
    -160,    27,    15,  -153,    30,  -160,   153,   277,  -153,    31,
      16,    35,   278,    21,    90,   313,    13,   104,   105,   317,
      96,   162,   318,   330,   157,   163,   145,   278,   278,    23,
      22,   329,   104,   105,    90,    12,     4,   302,    23,   304,
     146,   190,    94,     4,   307,    53,  -165,  -165,    36,    91,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    91,   162,    48,   145,     4,   163,    28,  -168,    91,
       4,    49,    50,    51,    52,   114,    94,   334,   280,    90,
      53,   336,   -75,   213,    29,   177,    12,     4,   191,  -163,
     114,    94,  -156,    34,   222,    97,   332,   339,   223,    91,
     349,   278,   278,   350,    32,   145,    92,    33,    93,    98,
      99,   100,  -167,   101,    91,   102,   149,   148,  -166,   152,
     156,    12,     4,   162,    76,   154,   155,   163,  -159,  -158,
    -168,  -168,  -157,  -162,   178,   220,  -155,   145,   213,  -161,
      91,  -171,  -154,  -170,    76,    36,   181,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,   241,    80,
      48,   182,  -171,   214,  -170,  -159,   145,  -158,    49,    50,
      51,    52,    91,  -164,  -167,  -167,   150,    53,   177,    80,
    -166,  -166,   216,   290,   224,   225,   281,   226,   184,   185,
     288,  -169,   227,  -168,   269,  -168,  -168,   249,  -168,  -168,
     244,    91,   279,  -171,  -171,  -170,  -170,   282,   292,    81,
     177,   293,  -169,   303,  -163,  -157,   311,  -156,    12,     4,
     309,   305,    90,   312,    80,   315,    90,   316,  -167,    81,
    -167,  -167,   333,  -167,  -167,   335,   338,   340,   341,   342,
      17,    18,    19,   328,    84,    20,   151,   321,   151,  -162,
     325,   151,  -155,  -169,  -169,  -168,  -168,    91,   323,    95,
      90,    91,    90,   285,    84,     0,     0,    90,     0,     0,
       0,     0,     0,     0,    81,     0,     0,   344,   151,   347,
     151,     0,    90,    90,    90,    90,    90,    90,     0,     0,
    -167,  -167,     0,   151,   151,    91,     0,    91,     0,     0,
      90,     0,    91,     0,    90,     0,     0,     0,     0,   186,
       0,     0,     0,    90,    90,    90,    90,    91,    91,    91,
      91,    91,    91,    90,    86,     0,    90,     0,     0,    90,
      90,     0,    76,     0,     0,    91,    76,     0,     0,    91,
       0,     0,     0,     0,    86,     0,     0,     0,    91,    91,
      91,    91,     0,     0,     0,     0,     0,     0,    91,     0,
       0,    91,     0,     0,    91,    91,     0,    80,     0,     0,
      76,    80,    76,     0,     0,     0,     0,    76,     0,  -166,
       0,  -166,  -166,     0,  -166,  -166,     0,     0,     0,    86,
       0,     0,    76,    76,    76,   185,    76,    76,     0,    87,
    -161,     0,     0,  -154,     0,    80,     0,    80,     0,     0,
      76,     0,    80,     0,    76,     0,     0,    81,     0,    87,
       0,    81,     0,    76,    76,    76,    76,    80,    80,    80,
      80,    80,    80,    76,     0,     0,    76,     0,     0,    76,
      76,  -166,  -166,     0,     0,    80,     0,     0,     0,    80,
       0,     0,    84,     0,     0,    81,    84,    81,    80,    80,
      80,    80,    81,     0,    87,     0,     0,     0,    80,     0,
       0,    80,     0,     0,    80,    80,    88,    81,    81,    81,
      81,    81,    81,     0,     0,     0,     0,     0,     0,     0,
      84,     0,    84,     0,     0,    81,    88,    84,     0,    81,
       0,   157,     0,   158,   159,     0,   160,   161,    81,    81,
      81,    81,    84,    84,    84,   186,    84,    84,    81,     0,
       0,    81,    53,     0,    81,    81,     0,     0,     0,     0,
      84,     0,    86,     0,    84,     0,    86,     0,     0,     0,
       0,    88,     0,    84,    84,    84,    84,    89,    49,    50,
      51,    52,     0,    84,     0,     0,    84,    53,     0,    84,
      84,     0,     0,    12,     4,     0,     0,    89,     0,     0,
      86,     0,    86,     0,     0,     0,     0,    86,     0,     0,
       0,     0,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,    86,    86,    86,    86,    86,    12,     4,
       0,     0,    77,     0,     0,     0,     0,    87,     0,     0,
      86,    87,    89,     0,    86,     0,     0,     0,     0,     0,
       0,     0,     0,    86,    86,    86,    86,     0,   245,     0,
       0,     0,     0,    86,     0,     0,    86,     0,     0,    86,
      86,     0,     0,     0,     0,    87,     0,    87,     0,     0,
     195,     0,    87,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,     0,     0,     0,     0,    87,    87,    87,
      87,    87,    87,     0,   206,   207,   208,   209,   210,   211,
     212,     0,     0,     0,    88,    87,     0,     0,    88,    87,
       0,     0,     0,     0,     0,     0,     0,     0,    87,    87,
      87,    87,     0,     0,     0,     0,     0,     0,    87,     0,
       0,    87,     0,     0,    87,    87,     0,     0,     0,     0,
       0,     0,    88,     0,    88,     0,     0,     0,    36,    88,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     0,     0,    48,    88,    88,    88,    88,    88,    88,
       0,    49,    50,    51,    52,    89,     0,     0,   287,    89,
      53,     0,    88,     0,     0,     0,    88,     0,     0,     0,
       0,     0,     0,     0,     0,    88,    88,    88,    88,     0,
       0,     0,     0,     0,     0,    88,     0,     0,    88,     0,
      77,    88,    88,    89,    77,    89,     0,     0,     0,     0,
      89,    12,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,    89,    89,    89,    89,
      89,     0,     0,   115,     0,     0,     0,     0,    77,     0,
      77,     0,     0,    89,     0,    77,     0,    89,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    89,    89,    89,
      77,    77,    77,     0,    77,    77,    89,     0,     0,    89,
       0,     0,    89,    89,     0,     0,     0,     0,    77,     0,
     179,   180,    77,     0,     0,     0,     0,     0,   187,   188,
       0,    77,    77,    77,    77,   189,     0,     0,   192,   193,
       0,    77,     0,     0,    77,    46,     0,    77,    77,     0,
       0,     0,     0,   103,   104,   105,     0,    49,    50,    51,
      52,   106,   107,     0,     0,     0,    53,     0,     0,     0,
     108,     0,   109,     0,   215,     0,     0,   217,     0,     0,
       0,     0,     0,     0,   221,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   110,   111,    12,     4,    23,
     112,   113,   114,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   273,   274,   275,   276,    36,     0,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     0,
       0,    48,   284,   286,     0,     0,   289,     0,     0,    49,
      50,    51,    52,     0,     0,     0,     0,   319,    53,     0,
      36,     0,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     0,     0,    48,   300,     0,     0,     0,
       0,     0,     0,    49,    50,    51,    52,     0,     0,   310,
     320,     0,    53,     0,   314,     0,     0,     0,     0,    12,
       4,     0,     0,     0,     0,    36,   327,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     0,     0,
      48,     0,     0,     0,     0,     0,     0,     0,    49,    50,
      51,    52,     0,    12,     4,     0,   322,    53,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,    49,    50,    51,    52,     0,     0,     0,     0,   324,
      53,     0,     0,     0,     0,     0,     0,     0,    12,     4,
       0,     0,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,     0,    49,    50,    51,    52,     0,
       0,    12,     4,   326,    53,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     0,     0,
      48,     0,     0,     0,     0,     0,     0,     0,    49,    50,
      51,    52,     0,     0,     0,   343,     0,    53,     0,     0,
       0,     0,     0,     0,     0,    12,     4,     0,     0,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,     0,     0,    12,     4,
     345,    53,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,     0,    49,    50,    51,    52,     0,
       0,     0,   346,     0,    53,     0,     0,     0,     0,     0,
       0,     0,    12,     4,     0,     0,    36,     0,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     0,
       0,    48,     0,     0,     0,     0,     0,     0,     0,    49,
      50,    51,    52,     0,     0,    12,     4,   348,    53,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,     0,     0,     0,     0,
     351,    53,     0,     0,     0,     0,     0,     0,     0,    12,
       4,     0,     0,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,    48,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
       0,     0,    12,     4,   352,    53,    36,     0,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     0,
       0,    48,     0,     0,     0,     0,     0,    46,     0,    49,
      50,    51,    52,     0,     0,   103,   104,   105,    53,    49,
      50,    51,    52,   106,   107,     0,    12,     4,    53,   164,
     165,     0,   108,     0,     0,     0,     0,     0,     0,     0,
       0,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,     0,     0,     0,     0,     0,     0,     0,    12,
       4,     0,     0,     0,     0,     0,     0,   110,   111,    12,
       4,    23,   112,   113,   114,    94,   247,     0,     0,     0,
       0,   248,     0,     0,     0,     0,     0,   195,     0,     0,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   206,   207,   208,   209,   210,   211,   212,   294,     0,
       0,     0,     0,   295,     0,     0,     0,     0,     0,   195,
       0,     0,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   206,   207,   208,   209,   210,   211,   212,
     298,     0,     0,     0,     0,   299,     0,     0,     0,     0,
       0,   195,     0,     0,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,     0,     0,     0,     0,     0,     0,
       0,   242,     0,     0,     0,   206,   207,   208,   209,   210,
     211,   212,   195,     0,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,     0,     0,     0,     0,     0,
       0,     0,   243,     0,     0,     0,   206,   207,   208,   209,
     210,   211,   212,   195,     0,     0,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,     0,     0,     0,     0,
       0,     0,     0,   246,     0,     0,     0,   206,   207,   208,
     209,   210,   211,   212,   195,     0,     0,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,     0,     0,     0,
       0,     0,     0,     0,   270,     0,     0,     0,   206,   207,
     208,   209,   210,   211,   212,   195,     0,     0,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,     0,     0,
       0,     0,     0,     0,     0,   297,     0,     0,     0,   206,
     207,   208,   209,   210,   211,   212,   195,     0,     0,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
       0,     0,     0,     0,     0,     0,   306,     0,     0,     0,
     206,   207,   208,   209,   210,   211,   212,   195,     0,     0,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
       0,     0,     0,     0,     0,     0,     0,   331,     0,     0,
       0,   206,   207,   208,   209,   210,   211,   212,   195,     0,
       0,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,     0,     0,     0,     0,     0,     0,     0,   337,     0,
       0,     0,   206,   207,   208,   209,   210,   211,   212,   195,
       0,     0,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   206,   207,   208,   209,   210,   211,   212,
     271,     0,     0,     0,     0,     0,     0,   195,     0,     0,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   206,   207,   208,   209,   210,   211,   212,   272,     0,
       0,     0,     0,     0,     0,   195,     0,     0,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   206,
     207,   208,   209,   210,   211,   212,   296,     0,     0,     0,
       0,     0,   195,     0,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   206,   207,   208,   209,
     210,   211,   212,   308,     0,     0,     0,     0,     0,   195,
       0,     0,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   206,   207,   208,   209,   210,   211,   212,
     291,     0,     0,   195,     0,     0,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   206,   207,   208,
     209,   210,   211,   212,   194,     0,   195,     0,     0,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     206,   207,   208,   209,   210,   211,   212,   195,     0,     0,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   206,   207,   208,   209,   210,   211,   212
  };

  const short
  parser::yycheck_[] =
  {
       0,    47,    99,    46,    17,    79,     6,    46,     3,     4,
       5,    28,    38,    34,    38,    41,    14,    15,    54,   279,
      38,    21,    34,    41,    35,    38,    44,    35,    41,    40,
       0,    31,    40,    34,    34,   295,     1,    26,    27,   299,
      38,    84,    35,    35,    17,    84,    46,    40,    40,    81,
      44,   311,    26,    27,    54,    79,    80,   280,    81,   282,
      34,   107,    85,    80,   287,    38,    79,    80,     6,    34,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    46,   125,    21,    84,    80,   125,    35,    17,    54,
      80,    29,    30,    31,    32,    84,    85,   320,    36,    99,
      38,   324,    44,    45,    35,    34,    79,    80,   108,    38,
      84,    85,    41,    36,   157,    43,    35,    35,   157,    84,
     343,    40,    40,   346,    44,   125,    34,    44,    34,    44,
      34,    34,    17,    34,    99,    44,    38,    44,    17,    44,
      38,    79,    80,   186,    34,    44,    41,   186,    41,    41,
      79,    80,    41,    38,    42,   155,    41,   157,    45,    38,
     125,    17,    41,    17,    54,     6,    43,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,   178,    34,
      21,    43,    38,    42,    38,    41,   186,    41,    29,    30,
      31,    32,   157,    38,    79,    80,    37,    38,    34,    54,
      79,    80,    44,   249,    34,    34,   242,    34,   305,    99,
     246,    17,    34,    17,   214,    19,    20,    40,    22,    23,
      44,   186,    34,    79,    80,    79,    80,    36,    44,    34,
      34,    39,    38,     7,    38,    41,    34,    41,    79,    80,
      40,    44,   242,    44,    99,    44,   246,    44,    17,    54,
      19,    20,     7,    22,    23,    35,    35,    44,    44,    44,
       6,     6,     6,   309,    34,     6,   302,   303,   304,    38,
     306,   307,    41,    79,    80,    79,    80,   242,   305,    38,
     280,   246,   282,   244,    54,    -1,    -1,   287,    -1,    -1,
      -1,    -1,    -1,    -1,    99,    -1,    -1,   333,   334,   335,
     336,    -1,   302,   303,   304,   305,   306,   307,    -1,    -1,
      79,    80,    -1,   349,   350,   280,    -1,   282,    -1,    -1,
     320,    -1,   287,    -1,   324,    -1,    -1,    -1,    -1,    99,
      -1,    -1,    -1,   333,   334,   335,   336,   302,   303,   304,
     305,   306,   307,   343,    34,    -1,   346,    -1,    -1,   349,
     350,    -1,   242,    -1,    -1,   320,   246,    -1,    -1,   324,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,   333,   334,
     335,   336,    -1,    -1,    -1,    -1,    -1,    -1,   343,    -1,
      -1,   346,    -1,    -1,   349,   350,    -1,   242,    -1,    -1,
     280,   246,   282,    -1,    -1,    -1,    -1,   287,    -1,    17,
      -1,    19,    20,    -1,    22,    23,    -1,    -1,    -1,    99,
      -1,    -1,   302,   303,   304,   305,   306,   307,    -1,    34,
      38,    -1,    -1,    41,    -1,   280,    -1,   282,    -1,    -1,
     320,    -1,   287,    -1,   324,    -1,    -1,   242,    -1,    54,
      -1,   246,    -1,   333,   334,   335,   336,   302,   303,   304,
     305,   306,   307,   343,    -1,    -1,   346,    -1,    -1,   349,
     350,    79,    80,    -1,    -1,   320,    -1,    -1,    -1,   324,
      -1,    -1,   242,    -1,    -1,   280,   246,   282,   333,   334,
     335,   336,   287,    -1,    99,    -1,    -1,    -1,   343,    -1,
      -1,   346,    -1,    -1,   349,   350,    34,   302,   303,   304,
     305,   306,   307,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     280,    -1,   282,    -1,    -1,   320,    54,   287,    -1,   324,
      -1,    17,    -1,    19,    20,    -1,    22,    23,   333,   334,
     335,   336,   302,   303,   304,   305,   306,   307,   343,    -1,
      -1,   346,    38,    -1,   349,   350,    -1,    -1,    -1,    -1,
     320,    -1,   242,    -1,   324,    -1,   246,    -1,    -1,    -1,
      -1,    99,    -1,   333,   334,   335,   336,    34,    29,    30,
      31,    32,    -1,   343,    -1,    -1,   346,    38,    -1,   349,
     350,    -1,    -1,    79,    80,    -1,    -1,    54,    -1,    -1,
     280,    -1,   282,    -1,    -1,    -1,    -1,   287,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   302,   303,   304,   305,   306,   307,    79,    80,
      -1,    -1,    54,    -1,    -1,    -1,    -1,   242,    -1,    -1,
     320,   246,    99,    -1,   324,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   333,   334,   335,   336,    -1,    24,    -1,
      -1,    -1,    -1,   343,    -1,    -1,   346,    -1,    -1,   349,
     350,    -1,    -1,    -1,    -1,   280,    -1,   282,    -1,    -1,
      46,    -1,   287,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,   302,   303,   304,
     305,   306,   307,    -1,    70,    71,    72,    73,    74,    75,
      76,    -1,    -1,    -1,   242,   320,    -1,    -1,   246,   324,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,   334,
     335,   336,    -1,    -1,    -1,    -1,    -1,    -1,   343,    -1,
      -1,   346,    -1,    -1,   349,   350,    -1,    -1,    -1,    -1,
      -1,    -1,   280,    -1,   282,    -1,    -1,    -1,     6,   287,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,   302,   303,   304,   305,   306,   307,
      -1,    29,    30,    31,    32,   242,    -1,    -1,    36,   246,
      38,    -1,   320,    -1,    -1,    -1,   324,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   333,   334,   335,   336,    -1,
      -1,    -1,    -1,    -1,    -1,   343,    -1,    -1,   346,    -1,
     242,   349,   350,   280,   246,   282,    -1,    -1,    -1,    -1,
     287,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   302,   303,   304,   305,   306,
     307,    -1,    -1,    45,    -1,    -1,    -1,    -1,   280,    -1,
     282,    -1,    -1,   320,    -1,   287,    -1,   324,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   333,   334,   335,   336,
     302,   303,   304,    -1,   306,   307,   343,    -1,    -1,   346,
      -1,    -1,   349,   350,    -1,    -1,    -1,    -1,   320,    -1,
      92,    93,   324,    -1,    -1,    -1,    -1,    -1,   100,   101,
      -1,   333,   334,   335,   336,   107,    -1,    -1,   110,   111,
      -1,   343,    -1,    -1,   346,    17,    -1,   349,   350,    -1,
      -1,    -1,    -1,    25,    26,    27,    -1,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      42,    -1,    44,    -1,   146,    -1,    -1,   149,    -1,    -1,
      -1,    -1,    -1,    -1,   156,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   224,   225,   226,   227,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,   244,   245,    -1,    -1,   248,    -1,    -1,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,    -1,
       6,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    21,   278,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    -1,    -1,   291,
      36,    -1,    38,    -1,   296,    -1,    -1,    -1,    -1,    79,
      80,    -1,    -1,    -1,    -1,     6,   308,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    -1,    79,    80,    -1,    37,    38,     6,    -1,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    -1,    -1,    -1,    -1,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,
      -1,    -1,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    -1,
      -1,    79,    80,    37,    38,     6,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    80,    -1,    -1,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    -1,    -1,    79,    80,
      37,    38,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    -1,
      -1,    -1,    36,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    -1,    -1,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    -1,    -1,    79,    80,    37,    38,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    -1,    -1,    -1,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      80,    -1,    -1,     6,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      -1,    -1,    79,    80,    37,    38,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    17,    -1,    29,
      30,    31,    32,    -1,    -1,    25,    26,    27,    38,    29,
      30,    31,    32,    33,    34,    -1,    79,    80,    38,    47,
      48,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    35,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    35,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      35,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    40,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    40,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      43,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    44,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,    80,    88,    89,    90,    91,    92,
      93,   152,    79,   153,    34,    34,     0,    90,    91,    92,
      93,    34,    44,    81,   151,   151,    94,   152,    35,    35,
      35,    40,    44,    44,    36,   152,     6,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    21,    29,
      30,    31,    32,    38,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   119,   124,   125,   126,   127,
     130,   131,   132,   133,   134,   135,   139,   140,   141,   142,
     152,   153,    34,    34,    85,   148,   151,    43,    44,    34,
      34,    34,    44,    25,    26,    27,    33,    34,    42,    44,
      77,    78,    82,    83,    84,   118,   120,   121,   122,   123,
     124,   125,   129,   130,   131,   134,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   126,   127,   152,    34,   146,    44,    38,
      37,    96,    44,    44,    44,    41,    38,    17,    19,    20,
      22,    23,   126,   127,    47,    48,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    34,    42,   118,
     118,    43,    43,   116,   119,   124,   134,   118,   118,   118,
     146,   152,   118,   118,    44,    46,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    70,    71,    72,    73,
      74,    75,    76,    45,    42,   118,    44,   118,    28,   136,
     152,   118,   126,   127,    34,    34,    34,    34,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     128,   152,    35,    35,    44,    24,    35,    35,    40,    40,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   152,
      35,    39,    39,   118,   118,   118,   118,    35,    40,    34,
      36,    96,    36,   117,   118,   120,   118,    36,    96,   118,
     146,    43,    44,    39,    35,    40,    40,    35,    35,    40,
     118,   128,    95,     7,    95,    44,    35,    95,    40,    40,
     118,    34,    44,   128,   118,    44,    44,   128,    35,    37,
      36,    96,    37,   116,    37,    96,    37,   118,   146,   128,
      35,    35,    35,     7,    95,    35,    95,    35,    35,    35,
      44,    44,    44,    36,    96,    37,    36,    96,    37,    95,
      95,    37,    37
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    87,    88,    88,    89,    89,    89,    89,    89,    89,
      89,    89,    90,    91,    92,    93,    94,    94,    94,    95,
      95,    95,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    97,    97,    98,    99,   100,   100,   101,   101,   102,
     102,   103,   104,   105,   105,   106,   106,   106,   106,   107,
     107,   108,   108,   109,   109,   110,   111,   111,   112,   113,
     114,   115,   115,   116,   116,   117,   117,   118,   118,   118,
     118,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   121,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   124,   124,   124,   124,   125,   125,
     125,   125,   126,   126,   127,   128,   128,   128,   129,   129,
     130,   130,   131,   132,   132,   132,   132,   132,   132,   132,
     133,   133,   133,   133,   133,   134,   134,   134,   134,   134,
     134,   134,   135,   135,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   146,   146,   146,   147,
     148,   149,   150,   151,   152,   153
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     2,     1,     1,
       1,     1,     3,     5,     5,     7,     3,     1,     0,     2,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     6,     8,     6,     5,     3,     8,
       6,     8,     2,     7,     5,    11,     9,     9,     7,     7,
       5,    11,     9,     9,     7,     7,     3,     3,     2,     2,
       2,     3,     2,     1,     0,     1,     0,     1,     1,     1,
       1,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     5,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     7,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     2,     2,     2,     2,
       3,     3,     4,     6,     8,     3,     1,     0,     2,     3,
       3,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     7,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   108,   108,   111,   115,   117,   119,   121,   123,   125,
     127,   129,   134,   139,   144,   149,   154,   156,   159,   163,
     165,   168,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   194,   196,   201,   206,   211,   213,   218,   220,   225,
     227,   232,   237,   242,   244,   249,   251,   253,   255,   260,
     262,   267,   269,   274,   276,   281,   286,   288,   293,   298,
     302,   307,   309,   314,   315,   319,   320,   324,   325,   326,
     327,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   347,   348,   349,   350,   351,   352,
     353,   354,   358,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   386,   387,   388,   389,   390,   391,
     392,   393,   394,   395,   399,   400,   401,   402,   406,   407,
     408,   409,   413,   415,   420,   425,   427,   430,   434,   436,
     441,   443,   448,   453,   454,   455,   456,   457,   458,   459,
     463,   464,   465,   466,   467,   471,   472,   473,   474,   475,
     476,   477,   481,   482,   483,   487,   492,   497,   502,   507,
     512,   517,   522,   527,   532,   537,   538,   539,   540,   544,
     548,   552,   556,   560,   564,   568
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
#endif // YYDEBUG


} // yy
#line 3800 "./IW6/compiler_parser.cpp"

#line 571 "iw6.parser.ypp"


void yy::parser::error(const std::string& msg)
{
    std::cout << "An error occured: " << msg << std::endl;
}
