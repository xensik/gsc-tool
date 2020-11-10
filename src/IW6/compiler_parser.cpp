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
#line 33 "IW6.parser.ypp"

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
  parser::parser (yyscan_t yyscanner_yyarg, gsc::script_ptr& astout_yyarg)
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
      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< gsc::block_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.YY_MOVE_OR_COPY< gsc::expr_arguments_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.YY_MOVE_OR_COPY< gsc::expr_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.YY_MOVE_OR_COPY< gsc::expr_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.YY_MOVE_OR_COPY< gsc::expr_call_type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.YY_MOVE_OR_COPY< gsc::expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_filepath: // filepath
        value.YY_MOVE_OR_COPY< gsc::filepath_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_float: // data_float
        value.YY_MOVE_OR_COPY< gsc::float_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.YY_MOVE_OR_COPY< gsc::identifier_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.YY_MOVE_OR_COPY< gsc::include_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_integer: // data_integer
        value.YY_MOVE_OR_COPY< gsc::integer_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.YY_MOVE_OR_COPY< gsc::localized_string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_object: // object
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_size: // size
      case symbol_kind::S_game: // game
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
        value.YY_MOVE_OR_COPY< gsc::node_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
        value.YY_MOVE_OR_COPY< gsc::parameters_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.YY_MOVE_OR_COPY< gsc::script_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.YY_MOVE_OR_COPY< gsc::stmt_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.YY_MOVE_OR_COPY< gsc::stmt_break_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.YY_MOVE_OR_COPY< gsc::stmt_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.YY_MOVE_OR_COPY< gsc::stmt_case_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.YY_MOVE_OR_COPY< gsc::stmt_continue_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.YY_MOVE_OR_COPY< gsc::stmt_default_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.YY_MOVE_OR_COPY< gsc::stmt_endon_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.YY_MOVE_OR_COPY< gsc::stmt_for_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.YY_MOVE_OR_COPY< gsc::stmt_foreach_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.YY_MOVE_OR_COPY< gsc::stmt_if_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.YY_MOVE_OR_COPY< gsc::stmt_ifelse_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.YY_MOVE_OR_COPY< gsc::stmt_notify_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< gsc::stmt_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.YY_MOVE_OR_COPY< gsc::stmt_return_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.YY_MOVE_OR_COPY< gsc::stmt_switch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.YY_MOVE_OR_COPY< gsc::stmt_wait_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.YY_MOVE_OR_COPY< gsc::stmt_waittill_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.YY_MOVE_OR_COPY< gsc::stmt_waittillframeend_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.YY_MOVE_OR_COPY< gsc::stmt_waittillmatch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.YY_MOVE_OR_COPY< gsc::stmt_while_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_string: // data_string
        value.YY_MOVE_OR_COPY< gsc::string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_thread: // thread
        value.YY_MOVE_OR_COPY< gsc::thread_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.YY_MOVE_OR_COPY< gsc::using_animtree_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
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
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_block: // block
        value.move< gsc::block_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.move< gsc::expr_arguments_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< gsc::expr_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.move< gsc::expr_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.move< gsc::expr_call_type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.move< gsc::expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_filepath: // filepath
        value.move< gsc::filepath_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_float: // data_float
        value.move< gsc::float_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< gsc::identifier_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.move< gsc::include_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_integer: // data_integer
        value.move< gsc::integer_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.move< gsc::localized_string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_object: // object
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_size: // size
      case symbol_kind::S_game: // game
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
        value.move< gsc::node_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
        value.move< gsc::parameters_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< gsc::script_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< gsc::stmt_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< gsc::stmt_break_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< gsc::stmt_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< gsc::stmt_case_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< gsc::stmt_continue_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< gsc::stmt_default_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< gsc::stmt_endon_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< gsc::stmt_for_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< gsc::stmt_foreach_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< gsc::stmt_if_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< gsc::stmt_ifelse_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< gsc::stmt_notify_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< gsc::stmt_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< gsc::stmt_return_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< gsc::stmt_switch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< gsc::stmt_wait_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< gsc::stmt_waittill_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< gsc::stmt_waittillframeend_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< gsc::stmt_waittillmatch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< gsc::stmt_while_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_string: // data_string
        value.move< gsc::string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_thread: // thread
        value.move< gsc::thread_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.move< gsc::using_animtree_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
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
      case symbol_kind::S_block: // block
        value.copy< gsc::block_ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.copy< gsc::expr_arguments_ptr > (that.value);
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.copy< gsc::expr_assign_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.copy< gsc::expr_call_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.copy< gsc::expr_call_type_ptr > (that.value);
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.copy< gsc::expr_ptr > (that.value);
        break;

      case symbol_kind::S_filepath: // filepath
        value.copy< gsc::filepath_ptr > (that.value);
        break;

      case symbol_kind::S_data_float: // data_float
        value.copy< gsc::float_ptr > (that.value);
        break;

      case symbol_kind::S_identifier: // identifier
        value.copy< gsc::identifier_ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.copy< gsc::include_ptr > (that.value);
        break;

      case symbol_kind::S_data_integer: // data_integer
        value.copy< gsc::integer_ptr > (that.value);
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.copy< gsc::localized_string_ptr > (that.value);
        break;

      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_object: // object
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_size: // size
      case symbol_kind::S_game: // game
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
        value.copy< gsc::node_ptr > (that.value);
        break;

      case symbol_kind::S_parameters: // parameters
        value.copy< gsc::parameters_ptr > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.copy< gsc::script_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.copy< gsc::stmt_assign_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.copy< gsc::stmt_break_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.copy< gsc::stmt_call_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.copy< gsc::stmt_case_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.copy< gsc::stmt_continue_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.copy< gsc::stmt_default_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.copy< gsc::stmt_endon_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.copy< gsc::stmt_for_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.copy< gsc::stmt_foreach_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.copy< gsc::stmt_if_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.copy< gsc::stmt_ifelse_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.copy< gsc::stmt_notify_ptr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< gsc::stmt_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.copy< gsc::stmt_return_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.copy< gsc::stmt_switch_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.copy< gsc::stmt_wait_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.copy< gsc::stmt_waittill_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.copy< gsc::stmt_waittillframeend_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.copy< gsc::stmt_waittillmatch_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.copy< gsc::stmt_while_ptr > (that.value);
        break;

      case symbol_kind::S_data_string: // data_string
        value.copy< gsc::string_ptr > (that.value);
        break;

      case symbol_kind::S_thread: // thread
        value.copy< gsc::thread_ptr > (that.value);
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.copy< gsc::using_animtree_ptr > (that.value);
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.copy< std::string > (that.value);
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
      case symbol_kind::S_block: // block
        value.move< gsc::block_ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.move< gsc::expr_arguments_ptr > (that.value);
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< gsc::expr_assign_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.move< gsc::expr_call_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.move< gsc::expr_call_type_ptr > (that.value);
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.move< gsc::expr_ptr > (that.value);
        break;

      case symbol_kind::S_filepath: // filepath
        value.move< gsc::filepath_ptr > (that.value);
        break;

      case symbol_kind::S_data_float: // data_float
        value.move< gsc::float_ptr > (that.value);
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< gsc::identifier_ptr > (that.value);
        break;

      case symbol_kind::S_include: // include
        value.move< gsc::include_ptr > (that.value);
        break;

      case symbol_kind::S_data_integer: // data_integer
        value.move< gsc::integer_ptr > (that.value);
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.move< gsc::localized_string_ptr > (that.value);
        break;

      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_object: // object
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_size: // size
      case symbol_kind::S_game: // game
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
        value.move< gsc::node_ptr > (that.value);
        break;

      case symbol_kind::S_parameters: // parameters
        value.move< gsc::parameters_ptr > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.move< gsc::script_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< gsc::stmt_assign_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< gsc::stmt_break_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< gsc::stmt_call_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< gsc::stmt_case_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< gsc::stmt_continue_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< gsc::stmt_default_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< gsc::stmt_endon_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< gsc::stmt_for_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< gsc::stmt_foreach_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< gsc::stmt_if_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< gsc::stmt_ifelse_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< gsc::stmt_notify_ptr > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< gsc::stmt_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< gsc::stmt_return_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< gsc::stmt_switch_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< gsc::stmt_wait_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< gsc::stmt_waittill_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< gsc::stmt_waittillframeend_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< gsc::stmt_waittillmatch_ptr > (that.value);
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< gsc::stmt_while_ptr > (that.value);
        break;

      case symbol_kind::S_data_string: // data_string
        value.move< gsc::string_ptr > (that.value);
        break;

      case symbol_kind::S_thread: // thread
        value.move< gsc::thread_ptr > (that.value);
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.move< gsc::using_animtree_ptr > (that.value);
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< std::string > (that.value);
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
      case symbol_kind::S_block: // block
        yylhs.value.emplace< gsc::block_ptr > ();
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        yylhs.value.emplace< gsc::expr_arguments_ptr > ();
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        yylhs.value.emplace< gsc::expr_assign_ptr > ();
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        yylhs.value.emplace< gsc::expr_call_ptr > ();
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        yylhs.value.emplace< gsc::expr_call_type_ptr > ();
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        yylhs.value.emplace< gsc::expr_ptr > ();
        break;

      case symbol_kind::S_filepath: // filepath
        yylhs.value.emplace< gsc::filepath_ptr > ();
        break;

      case symbol_kind::S_data_float: // data_float
        yylhs.value.emplace< gsc::float_ptr > ();
        break;

      case symbol_kind::S_identifier: // identifier
        yylhs.value.emplace< gsc::identifier_ptr > ();
        break;

      case symbol_kind::S_include: // include
        yylhs.value.emplace< gsc::include_ptr > ();
        break;

      case symbol_kind::S_data_integer: // data_integer
        yylhs.value.emplace< gsc::integer_ptr > ();
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        yylhs.value.emplace< gsc::localized_string_ptr > ();
        break;

      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
      case symbol_kind::S_expr_add_array: // expr_add_array
      case symbol_kind::S_object: // object
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_size: // size
      case symbol_kind::S_game: // game
      case symbol_kind::S_self: // self
      case symbol_kind::S_anim: // anim
      case symbol_kind::S_level: // level
        yylhs.value.emplace< gsc::node_ptr > ();
        break;

      case symbol_kind::S_parameters: // parameters
        yylhs.value.emplace< gsc::parameters_ptr > ();
        break;

      case symbol_kind::S_script: // script
        yylhs.value.emplace< gsc::script_ptr > ();
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        yylhs.value.emplace< gsc::stmt_assign_ptr > ();
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        yylhs.value.emplace< gsc::stmt_break_ptr > ();
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        yylhs.value.emplace< gsc::stmt_call_ptr > ();
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        yylhs.value.emplace< gsc::stmt_case_ptr > ();
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        yylhs.value.emplace< gsc::stmt_continue_ptr > ();
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        yylhs.value.emplace< gsc::stmt_default_ptr > ();
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        yylhs.value.emplace< gsc::stmt_endon_ptr > ();
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        yylhs.value.emplace< gsc::stmt_for_ptr > ();
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        yylhs.value.emplace< gsc::stmt_foreach_ptr > ();
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        yylhs.value.emplace< gsc::stmt_if_ptr > ();
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        yylhs.value.emplace< gsc::stmt_ifelse_ptr > ();
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        yylhs.value.emplace< gsc::stmt_notify_ptr > ();
        break;

      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< gsc::stmt_ptr > ();
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        yylhs.value.emplace< gsc::stmt_return_ptr > ();
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        yylhs.value.emplace< gsc::stmt_switch_ptr > ();
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        yylhs.value.emplace< gsc::stmt_wait_ptr > ();
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        yylhs.value.emplace< gsc::stmt_waittill_ptr > ();
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        yylhs.value.emplace< gsc::stmt_waittillframeend_ptr > ();
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        yylhs.value.emplace< gsc::stmt_waittillmatch_ptr > ();
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        yylhs.value.emplace< gsc::stmt_while_ptr > ();
        break;

      case symbol_kind::S_data_string: // data_string
        yylhs.value.emplace< gsc::string_ptr > ();
        break;

      case symbol_kind::S_thread: // thread
        yylhs.value.emplace< gsc::thread_ptr > ();
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        yylhs.value.emplace< gsc::using_animtree_ptr > ();
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        yylhs.value.emplace< std::string > ();
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
#line 113 "IW6.parser.ypp"
                 { astout = std::move(yystack_[0].value.as < gsc::script_ptr > ()); }
#line 1455 "./IW6/compiler_parser.cpp"
    break;

  case 3: // root: %empty
#line 114 "IW6.parser.ypp"
                 { astout = std::make_unique<gsc::node_script>(); }
#line 1461 "./IW6/compiler_parser.cpp"
    break;

  case 4: // script: script include
#line 119 "IW6.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ())); }
#line 1467 "./IW6/compiler_parser.cpp"
    break;

  case 5: // script: script using_animtree
#line 121 "IW6.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1473 "./IW6/compiler_parser.cpp"
    break;

  case 6: // script: script animtree
#line 123 "IW6.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1479 "./IW6/compiler_parser.cpp"
    break;

  case 7: // script: script thread
#line 125 "IW6.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ())); }
#line 1485 "./IW6/compiler_parser.cpp"
    break;

  case 8: // script: include
#line 127 "IW6.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ()));}
#line 1491 "./IW6/compiler_parser.cpp"
    break;

  case 9: // script: using_animtree
#line 129 "IW6.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1497 "./IW6/compiler_parser.cpp"
    break;

  case 10: // script: animtree
#line 131 "IW6.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1503 "./IW6/compiler_parser.cpp"
    break;

  case 11: // script: thread
#line 133 "IW6.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ()));}
#line 1509 "./IW6/compiler_parser.cpp"
    break;

  case 12: // include: INCLUDE filepath SEMICOLON
#line 138 "IW6.parser.ypp"
                { yylhs.value.as < gsc::include_ptr > () = std::make_unique<gsc::node_include>(std::move(yystack_[1].value.as < gsc::filepath_ptr > ())); }
#line 1515 "./IW6/compiler_parser.cpp"
    break;

  case 13: // using_animtree: USING_ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 143 "IW6.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>(std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1521 "./IW6/compiler_parser.cpp"
    break;

  case 14: // animtree: ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 148 "IW6.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>(std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1527 "./IW6/compiler_parser.cpp"
    break;

  case 15: // thread: identifier LPAREN parameters RPAREN LBRACE block RBRACE
#line 153 "IW6.parser.ypp"
                { yylhs.value.as < gsc::thread_ptr > () = std::make_unique<gsc::node_thread>(std::move(yystack_[6].value.as < gsc::identifier_ptr > ()), std::move(yystack_[4].value.as < gsc::parameters_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1533 "./IW6/compiler_parser.cpp"
    break;

  case 16: // parameters: parameters COMMA identifier
#line 158 "IW6.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::move(yystack_[2].value.as < gsc::parameters_ptr > ()); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1539 "./IW6/compiler_parser.cpp"
    break;

  case 17: // parameters: identifier
#line 160 "IW6.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1545 "./IW6/compiler_parser.cpp"
    break;

  case 18: // parameters: %empty
#line 162 "IW6.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(); }
#line 1551 "./IW6/compiler_parser.cpp"
    break;

  case 19: // block: block stmt
#line 167 "IW6.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::move(yystack_[1].value.as < gsc::block_ptr > ()); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1557 "./IW6/compiler_parser.cpp"
    break;

  case 20: // block: stmt
#line 169 "IW6.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1563 "./IW6/compiler_parser.cpp"
    break;

  case 21: // block: %empty
#line 171 "IW6.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(); }
#line 1569 "./IW6/compiler_parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 175 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_call = std::move(yystack_[0].value.as < gsc::stmt_call_ptr > ()); }
#line 1575 "./IW6/compiler_parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 176 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < gsc::stmt_assign_ptr > ()); }
#line 1581 "./IW6/compiler_parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 177 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < gsc::stmt_endon_ptr > ()); }
#line 1587 "./IW6/compiler_parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 178 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < gsc::stmt_notify_ptr > ()); }
#line 1593 "./IW6/compiler_parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 179 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < gsc::stmt_wait_ptr > ()); }
#line 1599 "./IW6/compiler_parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 180 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < gsc::stmt_waittill_ptr > ()); }
#line 1605 "./IW6/compiler_parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 181 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < gsc::stmt_waittillmatch_ptr > ()); }
#line 1611 "./IW6/compiler_parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 182 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < gsc::stmt_waittillframeend_ptr > ()); }
#line 1617 "./IW6/compiler_parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 183 "IW6.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_if = std::move(yystack_[0].value.as < gsc::stmt_if_ptr > ()); }
#line 1623 "./IW6/compiler_parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 184 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < gsc::stmt_ifelse_ptr > ()); }
#line 1629 "./IW6/compiler_parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 185 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_while = std::move(yystack_[0].value.as < gsc::stmt_while_ptr > ()); }
#line 1635 "./IW6/compiler_parser.cpp"
    break;

  case 33: // stmt: stmt_for
#line 186 "IW6.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_for = std::move(yystack_[0].value.as < gsc::stmt_for_ptr > ()); }
#line 1641 "./IW6/compiler_parser.cpp"
    break;

  case 34: // stmt: stmt_foreach
#line 187 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < gsc::stmt_foreach_ptr > ()); }
#line 1647 "./IW6/compiler_parser.cpp"
    break;

  case 35: // stmt: stmt_switch
#line 188 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < gsc::stmt_switch_ptr > ()); }
#line 1653 "./IW6/compiler_parser.cpp"
    break;

  case 36: // stmt: stmt_case
#line 189 "IW6.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_case = std::move(yystack_[0].value.as < gsc::stmt_case_ptr > ()); }
#line 1659 "./IW6/compiler_parser.cpp"
    break;

  case 37: // stmt: stmt_default
#line 190 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_default = std::move(yystack_[0].value.as < gsc::stmt_default_ptr > ()); }
#line 1665 "./IW6/compiler_parser.cpp"
    break;

  case 38: // stmt: stmt_break
#line 191 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_break = std::move(yystack_[0].value.as < gsc::stmt_break_ptr > ()); }
#line 1671 "./IW6/compiler_parser.cpp"
    break;

  case 39: // stmt: stmt_continue
#line 192 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < gsc::stmt_continue_ptr > ()); }
#line 1677 "./IW6/compiler_parser.cpp"
    break;

  case 40: // stmt: stmt_return
#line 193 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_return = std::move(yystack_[0].value.as < gsc::stmt_return_ptr > ()); }
#line 1683 "./IW6/compiler_parser.cpp"
    break;

  case 41: // stmt_call: expr_call SEMICOLON
#line 198 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>(std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1689 "./IW6/compiler_parser.cpp"
    break;

  case 42: // stmt_call: expr_call_thread SEMICOLON
#line 200 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>(std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1695 "./IW6/compiler_parser.cpp"
    break;

  case 43: // stmt_assign: expr_assign SEMICOLON
#line 205 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_assign_ptr > () = std::make_unique<gsc::node_stmt_assign>(std::move(yystack_[1].value.as < gsc::expr_assign_ptr > ())); }
#line 1701 "./IW6/compiler_parser.cpp"
    break;

  case 44: // stmt_endon: object ENDON LPAREN expr RPAREN SEMICOLON
#line 210 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_endon_ptr > () = std::make_unique<gsc::node_stmt_endon>(std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1707 "./IW6/compiler_parser.cpp"
    break;

  case 45: // stmt_notify: object NOTIFY LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 215 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>(std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1713 "./IW6/compiler_parser.cpp"
    break;

  case 46: // stmt_notify: object NOTIFY LPAREN expr RPAREN SEMICOLON
#line 217 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>(std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>()); }
#line 1719 "./IW6/compiler_parser.cpp"
    break;

  case 47: // stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON
#line 222 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>(std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1725 "./IW6/compiler_parser.cpp"
    break;

  case 48: // stmt_wait: WAIT num SEMICOLON
#line 224 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>(std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1731 "./IW6/compiler_parser.cpp"
    break;

  case 49: // stmt_waittill: object WAITTILL LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 229 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>(std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1737 "./IW6/compiler_parser.cpp"
    break;

  case 50: // stmt_waittill: object WAITTILL LPAREN expr RPAREN SEMICOLON
#line 231 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>(std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>()); }
#line 1743 "./IW6/compiler_parser.cpp"
    break;

  case 51: // stmt_waittillmatch: object WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON
#line 236 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillmatch_ptr > () = std::make_unique<gsc::node_stmt_waittillmatch>(std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1749 "./IW6/compiler_parser.cpp"
    break;

  case 52: // stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON
#line 241 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillframeend_ptr > () = std::make_unique<gsc::node_stmt_waittillframeend>(); }
#line 1755 "./IW6/compiler_parser.cpp"
    break;

  case 53: // stmt_if: IF LPAREN expr RPAREN LBRACE block RBRACE
#line 246 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>(std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1761 "./IW6/compiler_parser.cpp"
    break;

  case 54: // stmt_if: IF LPAREN expr RPAREN stmt
#line 248 "IW6.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>();
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1770 "./IW6/compiler_parser.cpp"
    break;

  case 55: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE LBRACE block RBRACE
#line 256 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[5].value.as < gsc::block_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1776 "./IW6/compiler_parser.cpp"
    break;

  case 56: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE block RBRACE
#line 258 "IW6.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>();
			blk->stmts.push_back(std::move(yystack_[4].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(blk), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1785 "./IW6/compiler_parser.cpp"
    break;

  case 57: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE stmt
#line 263 "IW6.parser.ypp"
                { 
			auto blk = std::make_unique<gsc::node_block>();
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::block_ptr > ()), std::move(blk)); }
#line 1794 "./IW6/compiler_parser.cpp"
    break;

  case 58: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt
#line 268 "IW6.parser.ypp"
                {
			auto blk1 = std::make_unique<gsc::node_block>();
			blk1->stmts.push_back(std::move(yystack_[2].value.as < gsc::stmt_ptr > ()));
			auto blk2 = std::make_unique<gsc::node_block>();
			blk2->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(blk1), std::move(blk2)); }
#line 1805 "./IW6/compiler_parser.cpp"
    break;

  case 59: // stmt_while: WHILE LPAREN expr RPAREN LBRACE block RBRACE
#line 278 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>(std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1811 "./IW6/compiler_parser.cpp"
    break;

  case 60: // stmt_while: WHILE LPAREN expr RPAREN stmt
#line 280 "IW6.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>();
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1820 "./IW6/compiler_parser.cpp"
    break;

  case 61: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE block RBRACE
#line 288 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>(std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1826 "./IW6/compiler_parser.cpp"
    break;

  case 62: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt
#line 290 "IW6.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>();
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>(std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1836 "./IW6/compiler_parser.cpp"
    break;

  case 63: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE block RBRACE
#line 299 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>(std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1842 "./IW6/compiler_parser.cpp"
    break;

  case 64: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt
#line 301 "IW6.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>();
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>(std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1852 "./IW6/compiler_parser.cpp"
    break;

  case 65: // stmt_switch: SWITCH LPAREN expr RPAREN LBRACE block RBRACE
#line 310 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_switch_ptr > () = std::make_unique<gsc::node_stmt_switch>(std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1858 "./IW6/compiler_parser.cpp"
    break;

  case 66: // stmt_case: CASE data_integer COLON
#line 315 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>(std::move(yystack_[1].value.as < gsc::integer_ptr > ())); }
#line 1864 "./IW6/compiler_parser.cpp"
    break;

  case 67: // stmt_case: CASE data_string COLON
#line 317 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>(std::move(yystack_[1].value.as < gsc::string_ptr > ())); }
#line 1870 "./IW6/compiler_parser.cpp"
    break;

  case 68: // stmt_default: DEFAULT COLON
#line 322 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_default_ptr > () = std::make_unique<gsc::node_stmt_default>(); }
#line 1876 "./IW6/compiler_parser.cpp"
    break;

  case 69: // stmt_break: BREAK SEMICOLON
#line 327 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_break_ptr > () = std::make_unique<gsc::node_stmt_break>(); }
#line 1882 "./IW6/compiler_parser.cpp"
    break;

  case 70: // stmt_continue: CONTINUE SEMICOLON
#line 331 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_continue_ptr > () = std::make_unique<gsc::node_stmt_continue>(); }
#line 1888 "./IW6/compiler_parser.cpp"
    break;

  case 71: // stmt_return: RETURN expr SEMICOLON
#line 336 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>(std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 1894 "./IW6/compiler_parser.cpp"
    break;

  case 72: // stmt_return: RETURN SEMICOLON
#line 338 "IW6.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>(std::make_unique<gsc::node>()); }
#line 1900 "./IW6/compiler_parser.cpp"
    break;

  case 73: // for_assign: expr_assign
#line 342 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_assign_ptr > ()); }
#line 1906 "./IW6/compiler_parser.cpp"
    break;

  case 74: // for_assign: %empty
#line 343 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1912 "./IW6/compiler_parser.cpp"
    break;

  case 75: // for_cond: expr_cmp
#line 347 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1918 "./IW6/compiler_parser.cpp"
    break;

  case 76: // for_cond: %empty
#line 348 "IW6.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1924 "./IW6/compiler_parser.cpp"
    break;

  case 77: // expr: expr_cmp
#line 352 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1930 "./IW6/compiler_parser.cpp"
    break;

  case 78: // expr: expr_ternary
#line 353 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1936 "./IW6/compiler_parser.cpp"
    break;

  case 79: // expr: expr_binary
#line 354 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1942 "./IW6/compiler_parser.cpp"
    break;

  case 80: // expr: expr_primitive
#line 355 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1948 "./IW6/compiler_parser.cpp"
    break;

  case 81: // expr_assign: object INCREMENT
#line 359 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_increment>(std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1954 "./IW6/compiler_parser.cpp"
    break;

  case 82: // expr_assign: object DECREMENT
#line 360 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_decrement>(std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1960 "./IW6/compiler_parser.cpp"
    break;

  case 83: // expr_assign: object ASSIGN expr
#line 361 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_equal>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1966 "./IW6/compiler_parser.cpp"
    break;

  case 84: // expr_assign: object ASSIGN_BITWISE_OR expr
#line 362 "IW6.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_or>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1972 "./IW6/compiler_parser.cpp"
    break;

  case 85: // expr_assign: object ASSIGN_BITWISE_AND expr
#line 363 "IW6.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_and>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1978 "./IW6/compiler_parser.cpp"
    break;

  case 86: // expr_assign: object ASSIGN_BITWISE_EXOR expr
#line 364 "IW6.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_exor>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1984 "./IW6/compiler_parser.cpp"
    break;

  case 87: // expr_assign: object ASSIGN_LSHIFT expr
#line 365 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_left>(std::move(yystack_[2].value.as < gsc::node_ptr > ()),std::move( yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1990 "./IW6/compiler_parser.cpp"
    break;

  case 88: // expr_assign: object ASSIGN_RSHIFT expr
#line 366 "IW6.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_right>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1996 "./IW6/compiler_parser.cpp"
    break;

  case 89: // expr_assign: object ASSIGN_ADD expr
#line 367 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_add>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2002 "./IW6/compiler_parser.cpp"
    break;

  case 90: // expr_assign: object ASSIGN_SUB expr
#line 368 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_sub>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2008 "./IW6/compiler_parser.cpp"
    break;

  case 91: // expr_assign: object ASSIGN_MULT expr
#line 369 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mult>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2014 "./IW6/compiler_parser.cpp"
    break;

  case 92: // expr_assign: object ASSIGN_DIV expr
#line 370 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_div>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2020 "./IW6/compiler_parser.cpp"
    break;

  case 93: // expr_assign: object ASSIGN_MOD expr
#line 371 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mod>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2026 "./IW6/compiler_parser.cpp"
    break;

  case 94: // expr_cmp: expr OR expr
#line 375 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_or>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2032 "./IW6/compiler_parser.cpp"
    break;

  case 95: // expr_cmp: expr AND expr
#line 376 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_and>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2038 "./IW6/compiler_parser.cpp"
    break;

  case 96: // expr_cmp: expr EQUALITY expr
#line 377 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_equality>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2044 "./IW6/compiler_parser.cpp"
    break;

  case 97: // expr_cmp: expr INEQUALITY expr
#line 378 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_inequality>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2050 "./IW6/compiler_parser.cpp"
    break;

  case 98: // expr_cmp: expr LESS_EQUAL expr
#line 379 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less_equal>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2056 "./IW6/compiler_parser.cpp"
    break;

  case 99: // expr_cmp: expr GREATER_EQUAL expr
#line 380 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater_equal>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2062 "./IW6/compiler_parser.cpp"
    break;

  case 100: // expr_cmp: expr LESS expr
#line 381 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2068 "./IW6/compiler_parser.cpp"
    break;

  case 101: // expr_cmp: expr GREATER expr
#line 382 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2074 "./IW6/compiler_parser.cpp"
    break;

  case 102: // expr_ternary: expr_cmp QMARK expr COLON expr
#line 386 "IW6.parser.ypp"
                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_ternary>(std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2080 "./IW6/compiler_parser.cpp"
    break;

  case 103: // expr_binary: expr BITWISE_OR expr
#line 390 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_or>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2086 "./IW6/compiler_parser.cpp"
    break;

  case 104: // expr_binary: expr BITWISE_AND expr
#line 391 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_and>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2092 "./IW6/compiler_parser.cpp"
    break;

  case 105: // expr_binary: expr BITWISE_EXOR expr
#line 392 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_exor>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2098 "./IW6/compiler_parser.cpp"
    break;

  case 106: // expr_binary: expr LSHIFT expr
#line 393 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_left>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2104 "./IW6/compiler_parser.cpp"
    break;

  case 107: // expr_binary: expr RSHIFT expr
#line 394 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_right>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2110 "./IW6/compiler_parser.cpp"
    break;

  case 108: // expr_binary: expr ADD expr
#line 395 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_add>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2116 "./IW6/compiler_parser.cpp"
    break;

  case 109: // expr_binary: expr SUB expr
#line 396 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_sub>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2122 "./IW6/compiler_parser.cpp"
    break;

  case 110: // expr_binary: expr MULT expr
#line 397 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mult>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2128 "./IW6/compiler_parser.cpp"
    break;

  case 111: // expr_binary: expr DIV expr
#line 398 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_div>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2134 "./IW6/compiler_parser.cpp"
    break;

  case 112: // expr_binary: expr MOD expr
#line 399 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mod>(std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2140 "./IW6/compiler_parser.cpp"
    break;

  case 113: // expr_primitive: LPAREN expr RPAREN
#line 403 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[1].value.as < gsc::expr_ptr > ()); }
#line 2146 "./IW6/compiler_parser.cpp"
    break;

  case 114: // expr_primitive: COMPLEMENT expr
#line 404 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_complement>(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2152 "./IW6/compiler_parser.cpp"
    break;

  case 115: // expr_primitive: NOT expr
#line 405 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_not>(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2158 "./IW6/compiler_parser.cpp"
    break;

  case 116: // expr_primitive: expr_call
#line 406 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2164 "./IW6/compiler_parser.cpp"
    break;

  case 117: // expr_primitive: expr_call_thread
#line 407 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2170 "./IW6/compiler_parser.cpp"
    break;

  case 118: // expr_primitive: expr_function_ref
#line 408 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2176 "./IW6/compiler_parser.cpp"
    break;

  case 119: // expr_primitive: expr_array
#line 409 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2182 "./IW6/compiler_parser.cpp"
    break;

  case 120: // expr_primitive: expr_field
#line 410 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2188 "./IW6/compiler_parser.cpp"
    break;

  case 121: // expr_primitive: expr_size
#line 411 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2194 "./IW6/compiler_parser.cpp"
    break;

  case 122: // expr_primitive: expr_vector
#line 412 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2200 "./IW6/compiler_parser.cpp"
    break;

  case 123: // expr_primitive: expr_add_array
#line 413 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2206 "./IW6/compiler_parser.cpp"
    break;

  case 124: // expr_primitive: vector
#line 414 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2212 "./IW6/compiler_parser.cpp"
    break;

  case 125: // expr_primitive: num
#line 415 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2218 "./IW6/compiler_parser.cpp"
    break;

  case 126: // expr_primitive: data_localized_string
#line 416 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::localized_string_ptr > ()); }
#line 2224 "./IW6/compiler_parser.cpp"
    break;

  case 127: // expr_primitive: data_string
#line 417 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::string_ptr > ()); }
#line 2230 "./IW6/compiler_parser.cpp"
    break;

  case 128: // expr_primitive: identifier
#line 418 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2236 "./IW6/compiler_parser.cpp"
    break;

  case 129: // expr_primitive: empty_array
#line 419 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2242 "./IW6/compiler_parser.cpp"
    break;

  case 130: // expr_primitive: undefined
#line 420 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2248 "./IW6/compiler_parser.cpp"
    break;

  case 131: // expr_primitive: game
#line 421 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2254 "./IW6/compiler_parser.cpp"
    break;

  case 132: // expr_primitive: self
#line 422 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2260 "./IW6/compiler_parser.cpp"
    break;

  case 133: // expr_primitive: anim
#line 423 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2266 "./IW6/compiler_parser.cpp"
    break;

  case 134: // expr_primitive: level
#line 424 "IW6.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2272 "./IW6/compiler_parser.cpp"
    break;

  case 135: // expr_call: expr_call_function
#line 428 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2278 "./IW6/compiler_parser.cpp"
    break;

  case 136: // expr_call: expr_call_pointer
#line 429 "IW6.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2284 "./IW6/compiler_parser.cpp"
    break;

  case 137: // expr_call: object expr_call_function
#line 430 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2290 "./IW6/compiler_parser.cpp"
    break;

  case 138: // expr_call: object expr_call_pointer
#line 431 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2296 "./IW6/compiler_parser.cpp"
    break;

  case 139: // expr_call_thread: THREAD expr_call_function
#line 435 "IW6.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2302 "./IW6/compiler_parser.cpp"
    break;

  case 140: // expr_call_thread: THREAD expr_call_pointer
#line 436 "IW6.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2308 "./IW6/compiler_parser.cpp"
    break;

  case 141: // expr_call_thread: object THREAD expr_call_function
#line 437 "IW6.parser.ypp"
                                            { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2314 "./IW6/compiler_parser.cpp"
    break;

  case 142: // expr_call_thread: object THREAD expr_call_pointer
#line 438 "IW6.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2320 "./IW6/compiler_parser.cpp"
    break;

  case 143: // expr_call_function: identifier LPAREN expr_arguments RPAREN
#line 443 "IW6.parser.ypp"
                {yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>(std::make_unique<gsc::node_filepath>(""), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2326 "./IW6/compiler_parser.cpp"
    break;

  case 144: // expr_call_function: filepath DOUBLECOLON identifier LPAREN expr_arguments RPAREN
#line 445 "IW6.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>(std::move(yystack_[5].value.as < gsc::filepath_ptr > ()), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2332 "./IW6/compiler_parser.cpp"
    break;

  case 145: // expr_call_pointer: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 450 "IW6.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>(std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2338 "./IW6/compiler_parser.cpp"
    break;

  case 146: // expr_arguments: expr_arguments COMMA expr
#line 455 "IW6.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ()); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2344 "./IW6/compiler_parser.cpp"
    break;

  case 147: // expr_arguments: expr
#line 457 "IW6.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2350 "./IW6/compiler_parser.cpp"
    break;

  case 148: // expr_arguments: %empty
#line 459 "IW6.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(); }
#line 2356 "./IW6/compiler_parser.cpp"
    break;

  case 149: // expr_function_ref: DOUBLECOLON identifier
#line 464 "IW6.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>(std::make_unique<gsc::node_filepath>(""), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2362 "./IW6/compiler_parser.cpp"
    break;

  case 150: // expr_function_ref: filepath DOUBLECOLON identifier
#line 466 "IW6.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>(std::move(yystack_[2].value.as < gsc::filepath_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2368 "./IW6/compiler_parser.cpp"
    break;

  case 151: // expr_array: object LBRACKET expr RBRACKET
#line 471 "IW6.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_array>(std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2374 "./IW6/compiler_parser.cpp"
    break;

  case 152: // expr_field: object DOT identifier
#line 476 "IW6.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_field>(std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2380 "./IW6/compiler_parser.cpp"
    break;

  case 153: // expr_size: object DOT size
#line 481 "IW6.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_size>(std::move(yystack_[2].value.as < gsc::node_ptr > ())); }
#line 2386 "./IW6/compiler_parser.cpp"
    break;

  case 154: // expr_vector: LPAREN expr COMMA expr COMMA expr RPAREN
#line 486 "IW6.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_vector>(std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2392 "./IW6/compiler_parser.cpp"
    break;

  case 155: // expr_add_array: LBRACKET expr_arguments RBRACKET
#line 491 "IW6.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_add_array>(std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2398 "./IW6/compiler_parser.cpp"
    break;

  case 156: // object: expr_call
#line 495 "IW6.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2404 "./IW6/compiler_parser.cpp"
    break;

  case 157: // object: expr_array
#line 496 "IW6.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2410 "./IW6/compiler_parser.cpp"
    break;

  case 158: // object: expr_field
#line 497 "IW6.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2416 "./IW6/compiler_parser.cpp"
    break;

  case 159: // object: identifier
#line 498 "IW6.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2422 "./IW6/compiler_parser.cpp"
    break;

  case 160: // object: level
#line 499 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2428 "./IW6/compiler_parser.cpp"
    break;

  case 161: // object: anim
#line 500 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2434 "./IW6/compiler_parser.cpp"
    break;

  case 162: // object: self
#line 501 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2440 "./IW6/compiler_parser.cpp"
    break;

  case 163: // object: game
#line 502 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2446 "./IW6/compiler_parser.cpp"
    break;

  case 164: // vector: LPAREN num COMMA num COMMA num RPAREN
#line 507 "IW6.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_vector>(std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2452 "./IW6/compiler_parser.cpp"
    break;

  case 165: // num: data_float
#line 511 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::float_ptr > ()); }
#line 2458 "./IW6/compiler_parser.cpp"
    break;

  case 166: // num: data_integer
#line 512 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::integer_ptr > ()); }
#line 2464 "./IW6/compiler_parser.cpp"
    break;

  case 167: // num: false
#line 513 "IW6.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2470 "./IW6/compiler_parser.cpp"
    break;

  case 168: // num: true
#line 514 "IW6.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2476 "./IW6/compiler_parser.cpp"
    break;

  case 169: // false: FALSE
#line 517 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>("0"); }
#line 2482 "./IW6/compiler_parser.cpp"
    break;

  case 170: // true: TRUE
#line 518 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>("1"); }
#line 2488 "./IW6/compiler_parser.cpp"
    break;

  case 171: // data_float: FLOAT
#line 519 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::float_ptr > () = std::make_unique<gsc::node_float>(yystack_[0].value.as < std::string > ()); }
#line 2494 "./IW6/compiler_parser.cpp"
    break;

  case 172: // data_integer: INTEGER
#line 520 "IW6.parser.ypp"
                                { yylhs.value.as < gsc::integer_ptr > () = std::make_unique<gsc::node_integer>(yystack_[0].value.as < std::string > ()); }
#line 2500 "./IW6/compiler_parser.cpp"
    break;

  case 173: // data_localized_string: STRING_LOC
#line 521 "IW6.parser.ypp"
                                   { yylhs.value.as < gsc::localized_string_ptr > () = std::make_unique<gsc::node_localized_string>(yystack_[0].value.as < std::string > ()); }
#line 2506 "./IW6/compiler_parser.cpp"
    break;

  case 174: // data_string: STRING
#line 522 "IW6.parser.ypp"
                                { yylhs.value.as < gsc::string_ptr > () = std::make_unique<gsc::node_string>(yystack_[0].value.as < std::string > ()); }
#line 2512 "./IW6/compiler_parser.cpp"
    break;

  case 175: // identifier: IDENTIFIER
#line 523 "IW6.parser.ypp"
                                { yylhs.value.as < gsc::identifier_ptr > () = std::make_unique<gsc::node_identifier>(yystack_[0].value.as < std::string > ()); }
#line 2518 "./IW6/compiler_parser.cpp"
    break;

  case 176: // filepath: FILEPATH
#line 524 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::filepath_ptr > () = std::make_unique<gsc::node_filepath>(yystack_[0].value.as < std::string > ()); }
#line 2524 "./IW6/compiler_parser.cpp"
    break;

  case 177: // empty_array: EMPTY_ARRAY
#line 525 "IW6.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_empty_array>(); }
#line 2530 "./IW6/compiler_parser.cpp"
    break;

  case 178: // undefined: UNDEFINED
#line 526 "IW6.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_undefined>(); }
#line 2536 "./IW6/compiler_parser.cpp"
    break;

  case 179: // size: SIZE
#line 527 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_size>(); }
#line 2542 "./IW6/compiler_parser.cpp"
    break;

  case 180: // game: GAME
#line 528 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_game>(); }
#line 2548 "./IW6/compiler_parser.cpp"
    break;

  case 181: // self: SELF
#line 529 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_self>(); }
#line 2554 "./IW6/compiler_parser.cpp"
    break;

  case 182: // anim: ANIM
#line 530 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_anim>(); }
#line 2560 "./IW6/compiler_parser.cpp"
    break;

  case 183: // level: LEVEL
#line 531 "IW6.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_level>(); }
#line 2566 "./IW6/compiler_parser.cpp"
    break;


#line 2570 "./IW6/compiler_parser.cpp"

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
  "MOD", "INCREMENT", "DECREMENT", "LSHIFT", "RSHIFT", "OR", "AND",
  "EQUALITY", "INEQUALITY", "LESS_EQUAL", "GREATER_EQUAL", "LESS",
  "GREATER", "ASSIGN", "ASSIGN_ADD", "ASSIGN_SUB", "ASSIGN_MULT",
  "ASSIGN_DIV", "ASSIGN_MOD", "ASSIGN_BITWISE_OR", "ASSIGN_BITWISE_AND",
  "ASSIGN_BITWISE_EXOR", "ASSIGN_LSHIFT", "ASSIGN_RSHIFT", "BITWISE_OR",
  "BITWISE_AND", "BITWISE_EXOR", "ADD", "SUB", "MULT", "DIV", "NOT",
  "COMPLEMENT", "FILEPATH", "IDENTIFIER", "STRING", "STRING_LOC", "FLOAT",
  "INTEGER", "IFX", "$accept", "root", "script", "include",
  "using_animtree", "animtree", "thread", "parameters", "block", "stmt",
  "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify", "stmt_wait",
  "stmt_waittill", "stmt_waittillmatch", "stmt_waittillframeend",
  "stmt_if", "stmt_ifelse", "stmt_while", "stmt_for", "stmt_foreach",
  "stmt_switch", "stmt_case", "stmt_default", "stmt_break",
  "stmt_continue", "stmt_return", "for_assign", "for_cond", "expr",
  "expr_assign", "expr_cmp", "expr_ternary", "expr_binary",
  "expr_primitive", "expr_call", "expr_call_thread", "expr_call_function",
  "expr_call_pointer", "expr_arguments", "expr_function_ref", "expr_array",
  "expr_field", "expr_size", "expr_vector", "expr_add_array", "object",
  "vector", "num", "false", "true", "data_float", "data_integer",
  "data_localized_string", "data_string", "identifier", "filepath",
  "empty_array", "undefined", "size", "game", "self", "anim", "level", YY_NULLPTR
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


  const short parser::yypact_ninf_ = -273;

  const short parser::yytable_ninf_ = -164;

  const short
  parser::yypact_[] =
  {
       5,   -66,    15,    27,  -273,    35,     5,  -273,  -273,  -273,
    -273,    39,  -273,    -1,   -28,   -28,  -273,  -273,  -273,  -273,
    -273,    -9,  -273,  -273,    42,    87,   -24,  -273,    79,    80,
      92,    -9,  -273,  -273,  1603,  -273,    96,   100,   -59,    97,
      98,   113,   114,   115,   106,  1619,    13,     3,   108,  -273,
    -273,  -273,  -273,   103,  1067,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,   109,   112,   117,  -273,  -273,
    -273,  -273,  1733,   123,   116,  -273,  -273,  -273,  -273,  1639,
    1639,  -273,   119,   120,  -273,  -273,   107,  1639,  1639,  -273,
    -273,  -273,  -273,  -273,  1639,  1707,    -9,  -273,  1639,  1639,
    -273,  -273,  2328,   121,  -273,  -273,  -273,     1,  -273,  -273,
       9,    19,  -273,  -273,  -273,    21,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,   -14,   128,  -273,  -273,    31,    38,
      53,    88,  -273,  -273,   123,  1639,   127,  -273,  1639,  -273,
    -273,  -273,  -273,  -273,    13,   125,   131,   138,   139,  1707,
      -9,  -273,  -273,  1639,  1639,  1639,  1639,  1639,  1639,  1639,
    1639,  1639,  1639,  1639,  -273,  -273,  1639,    -9,  1894,  1925,
    -273,  -273,   132,  -273,  -273,   327,  1779,  1956,   179,   111,
    1707,  2359,    -7,  -273,  2359,  2359,  -273,  1639,  1639,  1639,
    1639,  1639,  1639,  1639,  1639,  1639,  1639,  1639,  1639,  1639,
    1639,  1639,  1639,  1639,  1639,  1639,   -13,    -9,  1987,  -273,
    2149,  -273,  -273,  1639,  1639,  1639,  1639,  2187,  -273,  2359,
    2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,
     -12,   140,  1101,   142,  1639,  1639,  1147,  -273,  1639,    37,
    2149,  -273,  1639,  2359,  2359,  2359,  2359,  2359,  2359,  2359,
    2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,  2359,
    2359,  2295,  -273,  -273,   140,   135,   136,  1821,  2224,  2018,
    1863,  -273,  -273,  1639,  1603,   173,  1603,   137,  2359,    71,
    2049,  1603,  -273,  2261,   143,  2359,  1639,  -273,   148,   144,
    1639,  1639,   145,   146,  1639,    55,  1178,  1223,  1254,   107,
    1298,  1331,  1639,    37,  2359,  1639,  -273,    62,  2080,  -273,
    -273,    68,  -273,   184,  1603,  -273,  -273,   157,  1603,  -273,
    -273,  2111,   158,    69,   150,   151,   152,  1376,  1407,  1452,
    1483,  -273,  -273,  -273,  -273,  -273,  -273,  1603,  -273,  -273,
    1603,  -273,  -273,  1527,  1560,  -273,  -273
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,   175,     0,     2,     8,     9,    10,
      11,     0,   176,     0,     0,     0,     1,     4,     5,     6,
       7,    18,    12,   174,     0,     0,     0,    17,     0,     0,
       0,     0,    13,    14,    21,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     183,   182,   181,     0,     0,    20,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,   156,     0,   135,   136,
     157,   158,     0,   159,     0,   163,   162,   161,   160,     0,
       0,   172,     0,     0,    68,    69,    74,     0,     0,    70,
     178,   170,   169,   177,     0,   148,     0,    72,     0,     0,
     173,   171,     0,    77,    78,    79,    80,   116,   117,   118,
     119,   120,   121,   122,   123,     0,   124,   125,   167,   168,
     165,   166,   126,   127,   128,     0,   129,   130,   131,   132,
     133,   134,   139,   140,     0,     0,     0,    52,     0,    15,
      19,    43,    41,    42,     0,     0,     0,     0,     0,     0,
       0,    81,    82,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,   148,     0,     0,     0,
      66,    67,     0,    73,   156,     0,     0,     0,     0,   125,
     148,   147,     0,   149,   115,   114,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
       0,   141,   142,     0,     0,     0,     0,     0,   152,    83,
      89,    90,    91,    92,    93,    84,    85,    86,    87,    88,
       0,     0,     0,     0,    76,     0,     0,   113,     0,     0,
     147,   155,     0,   112,   106,   107,    94,    95,    96,    97,
      98,    99,   100,   101,   103,   104,   105,   108,   109,   110,
     111,     0,   179,   153,   150,     0,     0,     0,     0,     0,
       0,   151,   143,   148,    21,    54,    21,     0,     0,    77,
       0,    21,    60,     0,     0,   146,     0,    47,     0,     0,
     148,     0,     0,     0,   148,     0,     0,     0,     0,    74,
       0,     0,     0,     0,   102,   148,    50,     0,     0,    44,
      46,     0,   144,    53,    21,    58,    65,     0,    21,    64,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   154,   164,   145,    49,    51,    45,    21,    57,    56,
      21,    62,    63,     0,     0,    55,    61
  };

  const short
  parser::yypgoto_[] =
  {
    -273,  -273,  -273,   191,   193,   194,   195,  -273,  -272,   -37,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -107,
    -273,   842,   -94,   -40,  -273,  -273,  -273,   130,   619,   -42,
     -41,  -169,  -273,   187,   245,  -273,  -273,  -273,   302,  -273,
     -46,  -273,  -273,  -273,   168,  -273,    30,     0,    73,  -273,
    -273,  -273,   390,   425,   504,   562
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,     9,    10,    26,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   182,
     287,   191,    75,   113,   114,   115,   116,   117,   118,    78,
      79,   192,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   273,   138,   139,   140,   141
  };

  const short
  parser::yytable_[] =
  {
      11,   146,   183,  -159,   142,   143,    11,   240,     1,     2,
       3,    30,   306,    12,   308,   272,    31,   150,  -156,   311,
     176,    27,    23,   282,  -159,    91,  -157,  -159,   252,   101,
     102,    35,   251,   252,    83,    16,  -158,   145,   154,  -156,
     174,   175,  -156,    22,    24,    25,   144,  -157,  -163,    14,
    -157,    53,   338,    23,    83,  -162,   340,  -158,   189,   159,
    -158,    15,   216,   101,   102,  -159,  -159,     4,    93,  -163,
    -161,     4,  -163,    21,    13,   353,  -162,    28,   354,  -162,
    -156,  -156,   144,   174,   175,     4,   111,    91,  -157,  -157,
     322,  -161,    12,     4,  -161,   252,    83,   334,  -158,  -158,
      12,     4,   252,   336,   343,  -160,   193,    84,   252,   252,
    -163,  -163,   221,   222,   305,   -75,   215,  -162,  -162,    84,
     111,    91,    29,    32,    33,   144,  -160,    84,    34,  -160,
      89,   317,  -161,  -161,    90,   321,    49,    50,    51,    52,
      94,   148,    95,   174,   175,    53,   333,    96,    97,    98,
      99,   249,   147,   151,   144,    84,   152,   176,   177,   223,
     228,   153,   180,   181,    76,   224,   215,  -160,  -160,    84,
     217,   219,   225,   226,   283,   298,   244,   241,   286,   297,
     307,   309,   315,   313,    76,   144,    12,     4,   316,   319,
     320,   337,   339,   342,   344,   345,   346,    17,    84,    18,
      19,    20,   327,   294,   289,   285,    92,     0,     0,   292,
       0,     0,     0,     0,   247,   183,   228,   274,     0,   248,
       0,    80,     0,     0,     0,   197,   184,    84,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,     0,     0,
       0,    80,    83,     0,     0,     0,    83,     0,     0,   208,
     209,   210,   211,   212,   213,   214,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,   332,     0,   150,
     325,   150,     0,   329,   150,     0,     0,     0,     0,    81,
       0,     0,     0,    80,    83,     0,    83,     0,     0,     0,
       0,    83,     0,     0,     0,     0,     0,     0,     0,    81,
     348,   150,   351,   150,     0,     0,    83,    83,    83,    83,
      83,    83,     0,     0,     0,    84,   150,   150,     0,    84,
       0,     0,     0,     0,    83,     0,     0,     0,    83,     0,
       0,     0,     0,     0,     0,     0,    82,    83,    83,    83,
      83,    81,     0,     0,     0,     0,     0,    83,     0,     0,
      83,     0,     0,    83,    83,     0,    82,    84,     0,    84,
       0,     0,     0,     0,    84,   159,     0,     0,   160,     0,
       0,     0,    76,     0,   161,   162,    76,     0,     0,    84,
      84,    84,    84,    84,    84,     0,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,    84,   185,     0,
       0,    84,     0,     0,     0,     0,    12,     4,     0,     0,
      84,    84,    84,    84,    76,     0,    76,     0,     0,     0,
      84,    76,     0,    84,    85,     0,    84,    84,     0,    80,
       0,     0,     0,    80,     0,     0,    76,    76,    76,   184,
      76,    76,     0,     0,    85,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,     0,     0,     0,    76,    86,
       0,     0,     0,     0,     0,     0,     0,    76,    76,    76,
      76,    80,     0,    80,     0,     0,     0,    76,    80,    86,
      76,     0,     0,    76,    76,     0,    85,    81,     0,     0,
       0,    81,     0,    80,    80,    80,    80,    80,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,     0,     0,     0,    80,     0,     0,     0,     0,
       0,    86,     0,     0,    80,    80,    80,    80,     0,    81,
       0,    81,     0,     0,    80,     0,    81,    80,    87,     0,
      80,    80,     0,     0,    82,     0,     0,     0,    82,     0,
       0,    81,    81,    81,    81,    81,    81,     0,    87,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
       0,     0,     0,    81,     0,     0,     0,     0,     0,     0,
       0,     0,    81,    81,    81,    81,    82,     0,    82,     0,
       0,     0,    81,    82,     0,    81,    88,     0,    81,    81,
      87,     0,     0,     0,     0,     0,     0,     0,    82,    82,
      82,   185,    82,    82,     0,     0,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,     0,     0,
      82,     0,    85,     0,     0,     0,    85,     0,     0,    82,
      82,    82,    82,     0,     0,     0,     0,     0,     0,    82,
       0,     0,    82,    77,     0,    82,    82,     0,    88,     0,
       0,     0,     0,     0,     0,     0,     0,    86,     0,     0,
       0,    86,     0,    77,    85,     0,    85,     0,     0,     0,
       0,    85,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    85,    85,    85,
      85,    85,     0,     0,     0,     0,     0,     0,     0,    86,
       0,    86,     0,     0,    85,     0,    86,     0,    85,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    85,    85,
      85,    86,    86,    86,    86,    86,    86,    85,     0,     0,
      85,     0,     0,    85,    85,     0,    87,     0,     0,    86,
      87,     0,     0,    86,     0,     0,     0,     0,     0,     0,
       0,     0,    86,    86,    86,    86,     0,     0,     0,     0,
       0,     0,    86,     0,     0,    86,     0,     0,    86,    86,
       0,     0,     0,     0,     0,     0,     0,     0,    87,     0,
      87,     0,     0,     0,     0,    87,     0,     0,     0,     0,
       0,     0,     0,     0,    88,     0,     0,     0,    88,     0,
      87,    87,    87,    87,    87,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    87,     0,
       0,     0,    87,     0,     0,     0,     0,     0,     0,     0,
       0,    87,    87,    87,    87,     0,    88,     0,    88,     0,
       0,    87,     0,    88,    87,     0,     0,    87,    87,     0,
       0,    77,     0,     0,     0,    77,     0,     0,    88,    88,
      88,    88,    88,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    88,   112,     0,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,    88,
      88,    88,    88,    77,     0,    77,     0,     0,     0,    88,
      77,     0,    88,     0,     0,    88,    88,     0,     0,     0,
       0,     0,     0,     0,     0,    77,    77,    77,     0,    77,
      77,   178,   179,     0,     0,     0,     0,     0,     0,   186,
     187,     0,     0,    77,     0,     0,   188,    77,     0,     0,
     194,   195,     0,     0,     0,     0,    77,    77,    77,    77,
       0,     0,     0,     0,     0,     0,    77,     0,     0,    77,
       0,     0,    77,    77,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   218,     0,     0,
     220,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   227,     0,     0,     0,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   250,     0,     0,     0,     0,     0,     0,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,     0,     0,
       0,     0,     0,     0,     0,   277,   278,   279,   280,     0,
       0,     0,     0,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,   288,   290,    48,     0,
     293,     0,     0,     0,   295,     0,    49,    50,    51,    52,
       0,     0,     0,     0,   149,    53,     0,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,     0,     0,     0,   284,   314,    53,
       0,     0,     0,   318,     0,     0,    12,     4,     0,     0,
       0,     0,     0,    36,   331,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,    48,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
      12,     4,     0,   291,    36,    53,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,    49,    50,    51,
      52,     0,     0,     0,     0,   323,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,     4,     0,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,     0,    12,     4,   324,
      36,    53,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     0,     0,    48,     0,     0,     0,     0,
       0,     0,     0,    49,    50,    51,    52,     0,     0,     0,
       0,   326,    53,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    12,     4,    36,     0,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,    49,    50,    51,
      52,     0,     0,    12,     4,   328,    53,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,     0,     0,     0,     0,   330,    53,
       0,     0,     0,     0,     0,     0,     0,    12,     4,     0,
       0,     0,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,     0,    49,    50,    51,    52,     0,
      12,     4,   347,    36,    53,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,    48,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
       0,     0,     0,     0,   349,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     4,     0,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,    49,    50,    51,    52,     0,    12,     4,   350,    36,
      53,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,     0,     0,     0,     0,
     352,    53,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     4,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,     0,     0,    48,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
       0,     0,    12,     4,   355,    53,    36,     0,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     0,
       0,    48,     0,     0,     0,     0,     0,     0,     0,    49,
      50,    51,    52,     0,     0,     0,     0,   356,    53,     0,
       0,     0,     0,     0,     0,     0,    12,     4,     0,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     0,     0,    48,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,    46,     0,     0,    12,
       4,    53,     0,     0,   100,   101,   102,     0,    49,    50,
      51,    52,   103,   104,     0,     0,    46,   105,     0,     0,
       0,   106,     0,   107,   100,   101,   102,     0,    49,    50,
      51,    52,   103,   104,     0,     0,     0,   105,     0,     0,
       0,   106,    12,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,    12,     4,
      23,   110,   111,    91,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,    12,     4,
      23,   110,   111,    91,    46,     0,     0,     0,     0,     0,
       0,     0,   100,   101,   102,     0,    49,    50,    51,    52,
     103,   104,     0,     0,     0,   190,     0,     0,     0,   106,
     154,     0,   155,   156,     0,   157,   158,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,     0,     0,   160,     0,     0,     0,     0,     0,
     161,   162,     0,     0,   108,   109,    12,     4,    23,   110,
     111,    91,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   245,     0,     0,     0,     0,     0,     0,
       0,     0,    12,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   197,     0,     0,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   208,
     209,   210,   211,   212,   213,   214,   299,     0,     0,     0,
       0,   300,     0,     0,     0,     0,     0,   197,     0,     0,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   208,   209,   210,   211,   212,   213,   214,   303,     0,
       0,     0,     0,   304,     0,     0,     0,     0,     0,   197,
       0,     0,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,     0,     0,     0,     0,     0,     0,     0,   242,
       0,     0,     0,   208,   209,   210,   211,   212,   213,   214,
     197,     0,     0,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,     0,     0,     0,     0,     0,     0,     0,
     243,     0,     0,     0,   208,   209,   210,   211,   212,   213,
     214,   197,     0,     0,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,     0,     0,     0,     0,     0,     0,
       0,   246,     0,     0,     0,   208,   209,   210,   211,   212,
     213,   214,   197,     0,     0,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,     0,     0,     0,     0,     0,
       0,     0,   275,     0,     0,     0,   208,   209,   210,   211,
     212,   213,   214,   197,     0,     0,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,     0,     0,     0,     0,
       0,     0,     0,   302,     0,     0,     0,   208,   209,   210,
     211,   212,   213,   214,   197,     0,     0,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,     0,     0,     0,
       0,     0,     0,     0,   310,     0,     0,     0,   208,   209,
     210,   211,   212,   213,   214,   197,     0,     0,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,     0,     0,
       0,     0,     0,     0,     0,   335,     0,     0,     0,   208,
     209,   210,   211,   212,   213,   214,   197,     0,     0,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,     0,
       0,     0,     0,     0,     0,     0,   341,     0,     0,     0,
     208,   209,   210,   211,   212,   213,   214,   197,     0,     0,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   208,   209,   210,   211,   212,   213,   214,   276,     0,
       0,     0,     0,     0,     0,   197,     0,     0,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   208,
     209,   210,   211,   212,   213,   214,   281,     0,     0,     0,
       0,     0,     0,   197,     0,     0,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   208,   209,   210,
     211,   212,   213,   214,   301,     0,     0,     0,     0,     0,
     197,     0,     0,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   208,   209,   210,   211,   212,   213,
     214,   312,     0,     0,     0,     0,     0,   197,     0,     0,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   208,   209,   210,   211,   212,   213,   214,   296,     0,
       0,   197,     0,     0,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   208,   209,   210,   211,   212,
     213,   214,   196,     0,   197,     0,     0,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   208,   209,
     210,   211,   212,   213,   214,   197,     0,     0,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   208,
     209,   210,   211,   212,   213,   214
  };

  const short
  parser::yycheck_[] =
  {
       0,    47,    96,    17,    46,    46,     6,   176,     3,     4,
       5,    35,   284,    79,   286,    28,    40,    54,    17,   291,
      34,    21,    81,    35,    38,    84,    17,    41,    40,    26,
      27,    31,    39,    40,    34,     0,    17,    34,    17,    38,
      82,    82,    41,    44,    14,    15,    46,    38,    17,    34,
      41,    38,   324,    81,    54,    17,   328,    38,   104,    38,
      41,    34,    41,    26,    27,    79,    80,    80,    38,    38,
      17,    80,    41,    34,     1,   347,    38,    35,   350,    41,
      79,    80,    82,   125,   125,    80,    83,    84,    79,    80,
      35,    38,    79,    80,    41,    40,    96,    35,    79,    80,
      79,    80,    40,    35,    35,    17,   106,    34,    40,    40,
      79,    80,   154,   154,   283,    44,    45,    79,    80,    46,
      83,    84,    35,    44,    44,   125,    38,    54,    36,    41,
      34,   300,    79,    80,    34,   304,    29,    30,    31,    32,
      43,    38,    44,   185,   185,    38,   315,    34,    34,    34,
      44,    40,    44,    44,   154,    82,    44,    34,    42,    34,
     160,    44,    43,    43,    34,    34,    45,    79,    80,    96,
      42,    44,    34,    34,    34,    39,    44,   177,    36,    44,
       7,    44,    34,    40,    54,   185,    79,    80,    44,    44,
      44,     7,    35,    35,    44,    44,    44,     6,   125,     6,
       6,     6,   309,   249,   244,   242,    38,    -1,    -1,   246,
      -1,    -1,    -1,    -1,    35,   309,   216,   217,    -1,    40,
      -1,    34,    -1,    -1,    -1,    46,    96,   154,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    54,   242,    -1,    -1,    -1,   246,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,   185,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   313,    -1,   306,
     307,   308,    -1,   310,   311,    -1,    -1,    -1,    -1,    34,
      -1,    -1,    -1,    96,   284,    -1,   286,    -1,    -1,    -1,
      -1,   291,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
     337,   338,   339,   340,    -1,    -1,   306,   307,   308,   309,
     310,   311,    -1,    -1,    -1,   242,   353,   354,    -1,   246,
      -1,    -1,    -1,    -1,   324,    -1,    -1,    -1,   328,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,   337,   338,   339,
     340,    96,    -1,    -1,    -1,    -1,    -1,   347,    -1,    -1,
     350,    -1,    -1,   353,   354,    -1,    54,   284,    -1,   286,
      -1,    -1,    -1,    -1,   291,    38,    -1,    -1,    41,    -1,
      -1,    -1,   242,    -1,    47,    48,   246,    -1,    -1,   306,
     307,   308,   309,   310,   311,    -1,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,   324,    96,    -1,
      -1,   328,    -1,    -1,    -1,    -1,    79,    80,    -1,    -1,
     337,   338,   339,   340,   284,    -1,   286,    -1,    -1,    -1,
     347,   291,    -1,   350,    34,    -1,   353,   354,    -1,   242,
      -1,    -1,    -1,   246,    -1,    -1,   306,   307,   308,   309,
     310,   311,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   324,    -1,    -1,    -1,   328,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,
     340,   284,    -1,   286,    -1,    -1,    -1,   347,   291,    54,
     350,    -1,    -1,   353,   354,    -1,    96,   242,    -1,    -1,
      -1,   246,    -1,   306,   307,   308,   309,   310,   311,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   324,    -1,    -1,    -1,   328,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,   337,   338,   339,   340,    -1,   284,
      -1,   286,    -1,    -1,   347,    -1,   291,   350,    34,    -1,
     353,   354,    -1,    -1,   242,    -1,    -1,    -1,   246,    -1,
      -1,   306,   307,   308,   309,   310,   311,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   324,
      -1,    -1,    -1,   328,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   337,   338,   339,   340,   284,    -1,   286,    -1,
      -1,    -1,   347,   291,    -1,   350,    34,    -1,   353,   354,
      96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,   307,
     308,   309,   310,   311,    -1,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   324,    -1,    -1,    -1,
     328,    -1,   242,    -1,    -1,    -1,   246,    -1,    -1,   337,
     338,   339,   340,    -1,    -1,    -1,    -1,    -1,    -1,   347,
      -1,    -1,   350,    34,    -1,   353,   354,    -1,    96,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   242,    -1,    -1,
      -1,   246,    -1,    54,   284,    -1,   286,    -1,    -1,    -1,
      -1,   291,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   306,   307,   308,   309,
     310,   311,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   284,
      -1,   286,    -1,    -1,   324,    -1,   291,    -1,   328,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,   338,   339,
     340,   306,   307,   308,   309,   310,   311,   347,    -1,    -1,
     350,    -1,    -1,   353,   354,    -1,   242,    -1,    -1,   324,
     246,    -1,    -1,   328,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   337,   338,   339,   340,    -1,    -1,    -1,    -1,
      -1,    -1,   347,    -1,    -1,   350,    -1,    -1,   353,   354,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   284,    -1,
     286,    -1,    -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   242,    -1,    -1,    -1,   246,    -1,
     306,   307,   308,   309,   310,   311,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   324,    -1,
      -1,    -1,   328,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   337,   338,   339,   340,    -1,   284,    -1,   286,    -1,
      -1,   347,    -1,   291,   350,    -1,    -1,   353,   354,    -1,
      -1,   242,    -1,    -1,    -1,   246,    -1,    -1,   306,   307,
     308,   309,   310,   311,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   324,    45,    -1,    -1,
     328,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   337,
     338,   339,   340,   284,    -1,   286,    -1,    -1,    -1,   347,
     291,    -1,   350,    -1,    -1,   353,   354,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   306,   307,   308,    -1,   310,
     311,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    97,
      98,    -1,    -1,   324,    -1,    -1,   104,   328,    -1,    -1,
     108,   109,    -1,    -1,    -1,    -1,   337,   338,   339,   340,
      -1,    -1,    -1,    -1,    -1,    -1,   347,    -1,    -1,   350,
      -1,    -1,   353,   354,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,    -1,    -1,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   159,    -1,    -1,    -1,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   190,    -1,    -1,    -1,    -1,    -1,    -1,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   223,   224,   225,   226,    -1,
      -1,    -1,    -1,     6,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,   244,   245,    21,    -1,
     248,    -1,    -1,    -1,   252,    -1,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    37,    38,    -1,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    -1,    -1,    -1,    36,   296,    38,
      -1,    -1,    -1,   301,    -1,    -1,    79,    80,    -1,    -1,
      -1,    -1,    -1,     6,   312,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      79,    80,    -1,    36,     6,    38,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    -1,    79,    80,    36,
       6,    38,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    -1,    -1,    -1,
      -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,     6,    -1,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    -1,    -1,    79,    80,    37,    38,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,
      -1,    -1,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    -1,
      79,    80,    36,     6,    38,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    80,    -1,     6,    -1,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    -1,    79,    80,    36,     6,
      38,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    -1,    -1,    -1,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,     6,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      -1,    -1,    79,    80,    37,    38,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    17,    -1,    -1,    79,
      80,    38,    -1,    -1,    25,    26,    27,    -1,    29,    30,
      31,    32,    33,    34,    -1,    -1,    17,    38,    -1,    -1,
      -1,    42,    -1,    44,    25,    26,    27,    -1,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    38,    -1,    -1,
      -1,    42,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,
      81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    79,    80,
      81,    82,    83,    84,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    26,    27,    -1,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    38,    -1,    -1,    -1,    42,
      17,    -1,    19,    20,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    77,    78,    79,    80,    81,    82,
      83,    84,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    35,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    35,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    40,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    40,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    43,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    44,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,    80,    87,    88,    89,    90,    91,
      92,   143,    79,   144,    34,    34,     0,    89,    90,    91,
      92,    34,    44,    81,   142,   142,    93,   143,    35,    35,
      35,    40,    44,    44,    36,   143,     6,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    21,    29,
      30,    31,    32,    38,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   118,   123,   124,   125,   126,
     129,   130,   134,   143,   144,   148,   149,   150,   151,    34,
      34,    84,   140,   142,    43,    44,    34,    34,    34,    44,
      25,    26,    27,    33,    34,    38,    42,    44,    77,    78,
      82,    83,   117,   119,   120,   121,   122,   123,   124,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   148,   149,
     150,   151,   125,   126,   143,    34,   136,    44,    38,    37,
      95,    44,    44,    44,    17,    19,    20,    22,    23,    38,
      41,    47,    48,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,   125,   126,    34,    42,   117,   117,
      43,    43,   115,   118,   123,   134,   117,   117,   117,   136,
      38,   117,   127,   143,   117,   117,    44,    46,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    70,    71,
      72,    73,    74,    75,    76,    45,    41,    42,   117,    44,
     117,   125,   126,    34,    34,    34,    34,   117,   143,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     127,   143,    35,    35,    44,    24,    35,    35,    40,    40,
     117,    39,    40,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,    28,   147,   143,    35,    39,   117,   117,   117,
     117,    39,    35,    34,    36,    95,    36,   116,   117,   119,
     117,    36,    95,   117,   136,   117,    43,    44,    39,    35,
      40,    40,    35,    35,    40,   127,    94,     7,    94,    44,
      35,    94,    40,    40,   117,    34,    44,   127,   117,    44,
      44,   127,    35,    37,    36,    95,    37,   115,    37,    95,
      37,   117,   136,   127,    35,    35,    35,     7,    94,    35,
      94,    35,    35,    35,    44,    44,    44,    36,    95,    37,
      36,    95,    37,    94,    94,    37,    37
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    86,    87,    87,    88,    88,    88,    88,    88,    88,
      88,    88,    89,    90,    91,    92,    93,    93,    93,    94,
      94,    94,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    96,    96,    97,    98,    99,    99,   100,   100,   101,
     101,   102,   103,   104,   104,   105,   105,   105,   105,   106,
     106,   107,   107,   108,   108,   109,   110,   110,   111,   112,
     113,   114,   114,   115,   115,   116,   116,   117,   117,   117,
     117,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   123,   123,   123,   123,   124,
     124,   124,   124,   125,   125,   126,   127,   127,   127,   128,
     128,   129,   130,   131,   132,   133,   134,   134,   134,   134,
     134,   134,   134,   134,   135,   136,   136,   136,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151
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
       3,     3,     3,     3,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     3,     3,     4,     6,     8,     3,     1,     0,     2,
       3,     4,     3,     3,     7,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     7,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   113,   113,   114,   118,   120,   122,   124,   126,   128,
     130,   132,   137,   142,   147,   152,   157,   159,   162,   166,
     168,   171,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   197,   199,   204,   209,   214,   216,   221,   223,   228,
     230,   235,   240,   245,   247,   255,   257,   262,   267,   277,
     279,   287,   289,   298,   300,   309,   314,   316,   321,   326,
     330,   335,   337,   342,   343,   347,   348,   352,   353,   354,
     355,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   375,   376,   377,   378,   379,   380,
     381,   382,   386,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   428,   429,   430,   431,   435,
     436,   437,   438,   442,   444,   449,   454,   456,   459,   463,
     465,   470,   475,   480,   485,   490,   495,   496,   497,   498,
     499,   500,   501,   502,   506,   511,   512,   513,   514,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531
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
#line 3796 "./IW6/compiler_parser.cpp"

#line 533 "IW6.parser.ypp"


void yy::parser::error(const std::string& msg)
{
    std::cout << "An error occured: " << msg << std::endl;
	exit(1);
}
