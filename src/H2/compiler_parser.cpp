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
#line 33 "H2.parser.ypp"

    #include "H2.hpp"
	#include "compiler_parser.hpp"
	#include "compiler_lexer.hpp"
	yy::parser::symbol_type yylex(yyscan_t yyscanner);

#line 46 "./H2/compiler_parser.cpp"




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
#line 126 "./H2/compiler_parser.cpp"

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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.YY_MOVE_OR_COPY< gsc::stmt_waitframe_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< gsc::stmt_waitframe_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.copy< gsc::stmt_waitframe_ptr > (that.value);
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< gsc::stmt_waitframe_ptr > (that.value);
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

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        yylhs.value.emplace< gsc::stmt_waitframe_ptr > ();
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
#line 114 "H2.parser.ypp"
                 { astout = std::move(yystack_[0].value.as < gsc::script_ptr > ()); }
#line 1475 "./H2/compiler_parser.cpp"
    break;

  case 3: // root: %empty
#line 115 "H2.parser.ypp"
                 { astout = std::make_unique<gsc::node_script>(""); }
#line 1481 "./H2/compiler_parser.cpp"
    break;

  case 4: // script: script include
#line 120 "H2.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ())); }
#line 1487 "./H2/compiler_parser.cpp"
    break;

  case 5: // script: script using_animtree
#line 122 "H2.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1493 "./H2/compiler_parser.cpp"
    break;

  case 6: // script: script animtree
#line 124 "H2.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1499 "./H2/compiler_parser.cpp"
    break;

  case 7: // script: script thread
#line 126 "H2.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ())); }
#line 1505 "./H2/compiler_parser.cpp"
    break;

  case 8: // script: include
#line 128 "H2.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(""); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ()));}
#line 1511 "./H2/compiler_parser.cpp"
    break;

  case 9: // script: using_animtree
#line 130 "H2.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(""); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1517 "./H2/compiler_parser.cpp"
    break;

  case 10: // script: animtree
#line 132 "H2.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(""); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1523 "./H2/compiler_parser.cpp"
    break;

  case 11: // script: thread
#line 134 "H2.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(""); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ()));}
#line 1529 "./H2/compiler_parser.cpp"
    break;

  case 12: // include: INCLUDE filepath SEMICOLON
#line 139 "H2.parser.ypp"
                { yylhs.value.as < gsc::include_ptr > () = std::make_unique<gsc::node_include>("", std::move(yystack_[1].value.as < gsc::filepath_ptr > ())); }
#line 1535 "./H2/compiler_parser.cpp"
    break;

  case 13: // using_animtree: USING_ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 144 "H2.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>("", std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1541 "./H2/compiler_parser.cpp"
    break;

  case 14: // animtree: ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 149 "H2.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>("", std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1547 "./H2/compiler_parser.cpp"
    break;

  case 15: // thread: identifier LPAREN parameters RPAREN LBRACE block RBRACE
#line 154 "H2.parser.ypp"
                { yylhs.value.as < gsc::thread_ptr > () = std::make_unique<gsc::node_thread>("", std::move(yystack_[6].value.as < gsc::identifier_ptr > ()), std::move(yystack_[4].value.as < gsc::parameters_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1553 "./H2/compiler_parser.cpp"
    break;

  case 16: // parameters: parameters COMMA identifier
#line 159 "H2.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::move(yystack_[2].value.as < gsc::parameters_ptr > ()); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1559 "./H2/compiler_parser.cpp"
    break;

  case 17: // parameters: identifier
#line 161 "H2.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(""); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1565 "./H2/compiler_parser.cpp"
    break;

  case 18: // parameters: %empty
#line 163 "H2.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(""); }
#line 1571 "./H2/compiler_parser.cpp"
    break;

  case 19: // block: block stmt
#line 168 "H2.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::move(yystack_[1].value.as < gsc::block_ptr > ()); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1577 "./H2/compiler_parser.cpp"
    break;

  case 20: // block: stmt
#line 170 "H2.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(""); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1583 "./H2/compiler_parser.cpp"
    break;

  case 21: // block: %empty
#line 172 "H2.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(""); }
#line 1589 "./H2/compiler_parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 176 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_call = std::move(yystack_[0].value.as < gsc::stmt_call_ptr > ()); }
#line 1595 "./H2/compiler_parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 177 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < gsc::stmt_assign_ptr > ()); }
#line 1601 "./H2/compiler_parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 178 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < gsc::stmt_endon_ptr > ()); }
#line 1607 "./H2/compiler_parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 179 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < gsc::stmt_notify_ptr > ()); }
#line 1613 "./H2/compiler_parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 180 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < gsc::stmt_wait_ptr > ()); }
#line 1619 "./H2/compiler_parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 181 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < gsc::stmt_waittill_ptr > ()); }
#line 1625 "./H2/compiler_parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 182 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < gsc::stmt_waittillmatch_ptr > ()); }
#line 1631 "./H2/compiler_parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 183 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < gsc::stmt_waittillframeend_ptr > ()); }
#line 1637 "./H2/compiler_parser.cpp"
    break;

  case 30: // stmt: stmt_waitframe
#line 184 "H2.parser.ypp"
                                                                            { yylhs.value.as < gsc::stmt_ptr > ().as_waitframe = std::move(yystack_[0].value.as < gsc::stmt_waitframe_ptr > ()); }
#line 1643 "./H2/compiler_parser.cpp"
    break;

  case 31: // stmt: stmt_if
#line 185 "H2.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_if = std::move(yystack_[0].value.as < gsc::stmt_if_ptr > ()); }
#line 1649 "./H2/compiler_parser.cpp"
    break;

  case 32: // stmt: stmt_ifelse
#line 186 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < gsc::stmt_ifelse_ptr > ()); }
#line 1655 "./H2/compiler_parser.cpp"
    break;

  case 33: // stmt: stmt_while
#line 187 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_while = std::move(yystack_[0].value.as < gsc::stmt_while_ptr > ()); }
#line 1661 "./H2/compiler_parser.cpp"
    break;

  case 34: // stmt: stmt_for
#line 188 "H2.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_for = std::move(yystack_[0].value.as < gsc::stmt_for_ptr > ()); }
#line 1667 "./H2/compiler_parser.cpp"
    break;

  case 35: // stmt: stmt_foreach
#line 189 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < gsc::stmt_foreach_ptr > ()); }
#line 1673 "./H2/compiler_parser.cpp"
    break;

  case 36: // stmt: stmt_switch
#line 190 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < gsc::stmt_switch_ptr > ()); }
#line 1679 "./H2/compiler_parser.cpp"
    break;

  case 37: // stmt: stmt_case
#line 191 "H2.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_case = std::move(yystack_[0].value.as < gsc::stmt_case_ptr > ()); }
#line 1685 "./H2/compiler_parser.cpp"
    break;

  case 38: // stmt: stmt_default
#line 192 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_default = std::move(yystack_[0].value.as < gsc::stmt_default_ptr > ()); }
#line 1691 "./H2/compiler_parser.cpp"
    break;

  case 39: // stmt: stmt_break
#line 193 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_break = std::move(yystack_[0].value.as < gsc::stmt_break_ptr > ()); }
#line 1697 "./H2/compiler_parser.cpp"
    break;

  case 40: // stmt: stmt_continue
#line 194 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < gsc::stmt_continue_ptr > ()); }
#line 1703 "./H2/compiler_parser.cpp"
    break;

  case 41: // stmt: stmt_return
#line 195 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_return = std::move(yystack_[0].value.as < gsc::stmt_return_ptr > ()); }
#line 1709 "./H2/compiler_parser.cpp"
    break;

  case 42: // stmt_call: expr_call SEMICOLON
#line 200 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>("", std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1715 "./H2/compiler_parser.cpp"
    break;

  case 43: // stmt_call: expr_call_thread SEMICOLON
#line 202 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>("", std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1721 "./H2/compiler_parser.cpp"
    break;

  case 44: // stmt_assign: expr_assign SEMICOLON
#line 207 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_assign_ptr > () = std::make_unique<gsc::node_stmt_assign>("", std::move(yystack_[1].value.as < gsc::expr_assign_ptr > ())); }
#line 1727 "./H2/compiler_parser.cpp"
    break;

  case 45: // stmt_endon: object ENDON LPAREN expr RPAREN SEMICOLON
#line 212 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_endon_ptr > () = std::make_unique<gsc::node_stmt_endon>("", std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1733 "./H2/compiler_parser.cpp"
    break;

  case 46: // stmt_notify: object NOTIFY LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 217 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>("", std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1739 "./H2/compiler_parser.cpp"
    break;

  case 47: // stmt_notify: object NOTIFY LPAREN expr RPAREN SEMICOLON
#line 219 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>("", std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>("")); }
#line 1745 "./H2/compiler_parser.cpp"
    break;

  case 48: // stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON
#line 224 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1751 "./H2/compiler_parser.cpp"
    break;

  case 49: // stmt_wait: WAIT num SEMICOLON
#line 226 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>("", std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1757 "./H2/compiler_parser.cpp"
    break;

  case 50: // stmt_waittill: object WAITTILL LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 231 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>("", std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1763 "./H2/compiler_parser.cpp"
    break;

  case 51: // stmt_waittill: object WAITTILL LPAREN expr RPAREN SEMICOLON
#line 233 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>("", std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>("")); }
#line 1769 "./H2/compiler_parser.cpp"
    break;

  case 52: // stmt_waittillmatch: object WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON
#line 238 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillmatch_ptr > () = std::make_unique<gsc::node_stmt_waittillmatch>("", std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1775 "./H2/compiler_parser.cpp"
    break;

  case 53: // stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON
#line 243 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillframeend_ptr > () = std::make_unique<gsc::node_stmt_waittillframeend>(""); }
#line 1781 "./H2/compiler_parser.cpp"
    break;

  case 54: // stmt_waitframe: WAITFRAME SEMICOLON
#line 248 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_waitframe_ptr > () = std::make_unique<gsc::node_stmt_waitframe>(""); }
#line 1787 "./H2/compiler_parser.cpp"
    break;

  case 55: // stmt_if: IF LPAREN expr RPAREN LBRACE block RBRACE
#line 253 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1793 "./H2/compiler_parser.cpp"
    break;

  case 56: // stmt_if: IF LPAREN expr RPAREN stmt
#line 255 "H2.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1802 "./H2/compiler_parser.cpp"
    break;

  case 57: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE LBRACE block RBRACE
#line 263 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>("", std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[5].value.as < gsc::block_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1808 "./H2/compiler_parser.cpp"
    break;

  case 58: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE block RBRACE
#line 265 "H2.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[4].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>("", std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(blk), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1817 "./H2/compiler_parser.cpp"
    break;

  case 59: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE stmt
#line 270 "H2.parser.ypp"
                { 
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>("", std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::block_ptr > ()), std::move(blk)); }
#line 1826 "./H2/compiler_parser.cpp"
    break;

  case 60: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt
#line 275 "H2.parser.ypp"
                {
			auto blk1 = std::make_unique<gsc::node_block>("");
			blk1->stmts.push_back(std::move(yystack_[2].value.as < gsc::stmt_ptr > ()));
			auto blk2 = std::make_unique<gsc::node_block>("");
			blk2->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(blk1), std::move(blk2)); }
#line 1837 "./H2/compiler_parser.cpp"
    break;

  case 61: // stmt_while: WHILE LPAREN expr RPAREN LBRACE block RBRACE
#line 285 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1843 "./H2/compiler_parser.cpp"
    break;

  case 62: // stmt_while: WHILE LPAREN expr RPAREN stmt
#line 287 "H2.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1852 "./H2/compiler_parser.cpp"
    break;

  case 63: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE block RBRACE
#line 295 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>("", std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1858 "./H2/compiler_parser.cpp"
    break;

  case 64: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt
#line 297 "H2.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>("", std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1868 "./H2/compiler_parser.cpp"
    break;

  case 65: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE block RBRACE
#line 306 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>("", std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1874 "./H2/compiler_parser.cpp"
    break;

  case 66: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt
#line 308 "H2.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1884 "./H2/compiler_parser.cpp"
    break;

  case 67: // stmt_switch: SWITCH LPAREN expr RPAREN LBRACE block RBRACE
#line 317 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_switch_ptr > () = std::make_unique<gsc::node_stmt_switch>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1890 "./H2/compiler_parser.cpp"
    break;

  case 68: // stmt_case: CASE data_integer COLON
#line 322 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>("", gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::integer_ptr > ()))); }
#line 1896 "./H2/compiler_parser.cpp"
    break;

  case 69: // stmt_case: CASE data_string COLON
#line 324 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>("", gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::string_ptr > ()))); }
#line 1902 "./H2/compiler_parser.cpp"
    break;

  case 70: // stmt_default: DEFAULT COLON
#line 329 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_default_ptr > () = std::make_unique<gsc::node_stmt_default>(""); }
#line 1908 "./H2/compiler_parser.cpp"
    break;

  case 71: // stmt_break: BREAK SEMICOLON
#line 334 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_break_ptr > () = std::make_unique<gsc::node_stmt_break>(""); }
#line 1914 "./H2/compiler_parser.cpp"
    break;

  case 72: // stmt_continue: CONTINUE SEMICOLON
#line 338 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_continue_ptr > () = std::make_unique<gsc::node_stmt_continue>(""); }
#line 1920 "./H2/compiler_parser.cpp"
    break;

  case 73: // stmt_return: RETURN expr SEMICOLON
#line 343 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>("", std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 1926 "./H2/compiler_parser.cpp"
    break;

  case 74: // stmt_return: RETURN SEMICOLON
#line 345 "H2.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>("", std::make_unique<gsc::node>()); }
#line 1932 "./H2/compiler_parser.cpp"
    break;

  case 75: // for_assign: expr_assign
#line 349 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_assign_ptr > ()); }
#line 1938 "./H2/compiler_parser.cpp"
    break;

  case 76: // for_assign: %empty
#line 350 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1944 "./H2/compiler_parser.cpp"
    break;

  case 77: // for_cond: expr_cmp
#line 354 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1950 "./H2/compiler_parser.cpp"
    break;

  case 78: // for_cond: %empty
#line 355 "H2.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1956 "./H2/compiler_parser.cpp"
    break;

  case 79: // expr: expr_cmp
#line 359 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1962 "./H2/compiler_parser.cpp"
    break;

  case 80: // expr: expr_ternary
#line 360 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1968 "./H2/compiler_parser.cpp"
    break;

  case 81: // expr: expr_binary
#line 361 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1974 "./H2/compiler_parser.cpp"
    break;

  case 82: // expr: expr_primitive
#line 362 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1980 "./H2/compiler_parser.cpp"
    break;

  case 83: // expr_assign: object INCREMENT
#line 366 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_increment>("", std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1986 "./H2/compiler_parser.cpp"
    break;

  case 84: // expr_assign: object DECREMENT
#line 367 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_decrement>("", std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1992 "./H2/compiler_parser.cpp"
    break;

  case 85: // expr_assign: object ASSIGN expr
#line 368 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_equal>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1998 "./H2/compiler_parser.cpp"
    break;

  case 86: // expr_assign: object ASSIGN_BITWISE_OR expr
#line 369 "H2.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_or>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2004 "./H2/compiler_parser.cpp"
    break;

  case 87: // expr_assign: object ASSIGN_BITWISE_AND expr
#line 370 "H2.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_and>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2010 "./H2/compiler_parser.cpp"
    break;

  case 88: // expr_assign: object ASSIGN_BITWISE_EXOR expr
#line 371 "H2.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_exor>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2016 "./H2/compiler_parser.cpp"
    break;

  case 89: // expr_assign: object ASSIGN_LSHIFT expr
#line 372 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_left>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()),std::move( yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2022 "./H2/compiler_parser.cpp"
    break;

  case 90: // expr_assign: object ASSIGN_RSHIFT expr
#line 373 "H2.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_right>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2028 "./H2/compiler_parser.cpp"
    break;

  case 91: // expr_assign: object ASSIGN_ADD expr
#line 374 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_add>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2034 "./H2/compiler_parser.cpp"
    break;

  case 92: // expr_assign: object ASSIGN_SUB expr
#line 375 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_sub>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2040 "./H2/compiler_parser.cpp"
    break;

  case 93: // expr_assign: object ASSIGN_MULT expr
#line 376 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mult>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2046 "./H2/compiler_parser.cpp"
    break;

  case 94: // expr_assign: object ASSIGN_DIV expr
#line 377 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_div>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2052 "./H2/compiler_parser.cpp"
    break;

  case 95: // expr_assign: object ASSIGN_MOD expr
#line 378 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mod>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2058 "./H2/compiler_parser.cpp"
    break;

  case 96: // expr_cmp: expr OR expr
#line 382 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_or>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2064 "./H2/compiler_parser.cpp"
    break;

  case 97: // expr_cmp: expr AND expr
#line 383 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_and>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2070 "./H2/compiler_parser.cpp"
    break;

  case 98: // expr_cmp: expr EQUALITY expr
#line 384 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_equality>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2076 "./H2/compiler_parser.cpp"
    break;

  case 99: // expr_cmp: expr INEQUALITY expr
#line 385 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_inequality>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2082 "./H2/compiler_parser.cpp"
    break;

  case 100: // expr_cmp: expr LESS_EQUAL expr
#line 386 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less_equal>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2088 "./H2/compiler_parser.cpp"
    break;

  case 101: // expr_cmp: expr GREATER_EQUAL expr
#line 387 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater_equal>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2094 "./H2/compiler_parser.cpp"
    break;

  case 102: // expr_cmp: expr LESS expr
#line 388 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2100 "./H2/compiler_parser.cpp"
    break;

  case 103: // expr_cmp: expr GREATER expr
#line 389 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2106 "./H2/compiler_parser.cpp"
    break;

  case 104: // expr_ternary: expr_cmp QMARK expr COLON expr
#line 393 "H2.parser.ypp"
                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_ternary>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2112 "./H2/compiler_parser.cpp"
    break;

  case 105: // expr_binary: expr BITWISE_OR expr
#line 397 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_or>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2118 "./H2/compiler_parser.cpp"
    break;

  case 106: // expr_binary: expr BITWISE_AND expr
#line 398 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_and>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2124 "./H2/compiler_parser.cpp"
    break;

  case 107: // expr_binary: expr BITWISE_EXOR expr
#line 399 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_exor>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2130 "./H2/compiler_parser.cpp"
    break;

  case 108: // expr_binary: expr LSHIFT expr
#line 400 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_left>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2136 "./H2/compiler_parser.cpp"
    break;

  case 109: // expr_binary: expr RSHIFT expr
#line 401 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_right>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2142 "./H2/compiler_parser.cpp"
    break;

  case 110: // expr_binary: expr ADD expr
#line 402 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_add>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2148 "./H2/compiler_parser.cpp"
    break;

  case 111: // expr_binary: expr SUB expr
#line 403 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_sub>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2154 "./H2/compiler_parser.cpp"
    break;

  case 112: // expr_binary: expr MULT expr
#line 404 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mult>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2160 "./H2/compiler_parser.cpp"
    break;

  case 113: // expr_binary: expr DIV expr
#line 405 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_div>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2166 "./H2/compiler_parser.cpp"
    break;

  case 114: // expr_binary: expr MOD expr
#line 406 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mod>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2172 "./H2/compiler_parser.cpp"
    break;

  case 115: // expr_primitive: LPAREN expr RPAREN
#line 410 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[1].value.as < gsc::expr_ptr > ()); }
#line 2178 "./H2/compiler_parser.cpp"
    break;

  case 116: // expr_primitive: COMPLEMENT expr
#line 411 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_complement>("", std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2184 "./H2/compiler_parser.cpp"
    break;

  case 117: // expr_primitive: NOT expr
#line 412 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_not>("", std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2190 "./H2/compiler_parser.cpp"
    break;

  case 118: // expr_primitive: expr_call
#line 413 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2196 "./H2/compiler_parser.cpp"
    break;

  case 119: // expr_primitive: expr_call_thread
#line 414 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2202 "./H2/compiler_parser.cpp"
    break;

  case 120: // expr_primitive: expr_function_ref
#line 415 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2208 "./H2/compiler_parser.cpp"
    break;

  case 121: // expr_primitive: expr_array
#line 416 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2214 "./H2/compiler_parser.cpp"
    break;

  case 122: // expr_primitive: expr_field
#line 417 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2220 "./H2/compiler_parser.cpp"
    break;

  case 123: // expr_primitive: expr_size
#line 418 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2226 "./H2/compiler_parser.cpp"
    break;

  case 124: // expr_primitive: expr_vector
#line 419 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2232 "./H2/compiler_parser.cpp"
    break;

  case 125: // expr_primitive: expr_add_array
#line 420 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2238 "./H2/compiler_parser.cpp"
    break;

  case 126: // expr_primitive: vector
#line 421 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2244 "./H2/compiler_parser.cpp"
    break;

  case 127: // expr_primitive: num
#line 422 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2250 "./H2/compiler_parser.cpp"
    break;

  case 128: // expr_primitive: data_localized_string
#line 423 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::localized_string_ptr > ()); }
#line 2256 "./H2/compiler_parser.cpp"
    break;

  case 129: // expr_primitive: data_string
#line 424 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::string_ptr > ()); }
#line 2262 "./H2/compiler_parser.cpp"
    break;

  case 130: // expr_primitive: identifier
#line 425 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2268 "./H2/compiler_parser.cpp"
    break;

  case 131: // expr_primitive: empty_array
#line 426 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2274 "./H2/compiler_parser.cpp"
    break;

  case 132: // expr_primitive: undefined
#line 427 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2280 "./H2/compiler_parser.cpp"
    break;

  case 133: // expr_primitive: game
#line 428 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2286 "./H2/compiler_parser.cpp"
    break;

  case 134: // expr_primitive: self
#line 429 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2292 "./H2/compiler_parser.cpp"
    break;

  case 135: // expr_primitive: anim
#line 430 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2298 "./H2/compiler_parser.cpp"
    break;

  case 136: // expr_primitive: level
#line 431 "H2.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2304 "./H2/compiler_parser.cpp"
    break;

  case 137: // expr_call: expr_call_function
#line 435 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2310 "./H2/compiler_parser.cpp"
    break;

  case 138: // expr_call: expr_call_pointer
#line 436 "H2.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2316 "./H2/compiler_parser.cpp"
    break;

  case 139: // expr_call: object expr_call_function
#line 437 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2322 "./H2/compiler_parser.cpp"
    break;

  case 140: // expr_call: object expr_call_pointer
#line 438 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2328 "./H2/compiler_parser.cpp"
    break;

  case 141: // expr_call_thread: THREAD expr_call_function
#line 442 "H2.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2334 "./H2/compiler_parser.cpp"
    break;

  case 142: // expr_call_thread: THREAD expr_call_pointer
#line 443 "H2.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2340 "./H2/compiler_parser.cpp"
    break;

  case 143: // expr_call_thread: object THREAD expr_call_function
#line 444 "H2.parser.ypp"
                                            { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2346 "./H2/compiler_parser.cpp"
    break;

  case 144: // expr_call_thread: object THREAD expr_call_pointer
#line 445 "H2.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2352 "./H2/compiler_parser.cpp"
    break;

  case 145: // expr_call_function: identifier LPAREN expr_arguments RPAREN
#line 450 "H2.parser.ypp"
                {yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>("", std::make_unique<gsc::node_filepath>("", ""), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2358 "./H2/compiler_parser.cpp"
    break;

  case 146: // expr_call_function: filepath DOUBLECOLON identifier LPAREN expr_arguments RPAREN
#line 452 "H2.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>("", std::move(yystack_[5].value.as < gsc::filepath_ptr > ()), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2364 "./H2/compiler_parser.cpp"
    break;

  case 147: // expr_call_pointer: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 457 "H2.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>("", false, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2370 "./H2/compiler_parser.cpp"
    break;

  case 148: // expr_call_pointer: CALL LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 459 "H2.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>("", true, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2376 "./H2/compiler_parser.cpp"
    break;

  case 149: // expr_arguments: expr_arguments COMMA expr
#line 464 "H2.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ()); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2382 "./H2/compiler_parser.cpp"
    break;

  case 150: // expr_arguments: expr
#line 466 "H2.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(""); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2388 "./H2/compiler_parser.cpp"
    break;

  case 151: // expr_arguments: %empty
#line 468 "H2.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(""); }
#line 2394 "./H2/compiler_parser.cpp"
    break;

  case 152: // expr_function_ref: DOUBLECOLON identifier
#line 473 "H2.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>("", std::make_unique<gsc::node_filepath>("", ""), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2400 "./H2/compiler_parser.cpp"
    break;

  case 153: // expr_function_ref: filepath DOUBLECOLON identifier
#line 475 "H2.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>("", std::move(yystack_[2].value.as < gsc::filepath_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2406 "./H2/compiler_parser.cpp"
    break;

  case 154: // expr_array: object LBRACKET expr RBRACKET
#line 480 "H2.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_array>("", std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2412 "./H2/compiler_parser.cpp"
    break;

  case 155: // expr_field: object DOT identifier
#line 485 "H2.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_field>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2418 "./H2/compiler_parser.cpp"
    break;

  case 156: // expr_size: object DOT size
#line 490 "H2.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_size>("", std::move(yystack_[2].value.as < gsc::node_ptr > ())); }
#line 2424 "./H2/compiler_parser.cpp"
    break;

  case 157: // expr_vector: LPAREN expr COMMA expr COMMA expr RPAREN
#line 495 "H2.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_vector>("", std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2430 "./H2/compiler_parser.cpp"
    break;

  case 158: // expr_add_array: LBRACKET expr_arguments RBRACKET
#line 500 "H2.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_add_array>("", std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2436 "./H2/compiler_parser.cpp"
    break;

  case 159: // object: expr_call
#line 504 "H2.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2442 "./H2/compiler_parser.cpp"
    break;

  case 160: // object: expr_array
#line 505 "H2.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2448 "./H2/compiler_parser.cpp"
    break;

  case 161: // object: expr_field
#line 506 "H2.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2454 "./H2/compiler_parser.cpp"
    break;

  case 162: // object: identifier
#line 507 "H2.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2460 "./H2/compiler_parser.cpp"
    break;

  case 163: // object: level
#line 508 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2466 "./H2/compiler_parser.cpp"
    break;

  case 164: // object: anim
#line 509 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2472 "./H2/compiler_parser.cpp"
    break;

  case 165: // object: self
#line 510 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2478 "./H2/compiler_parser.cpp"
    break;

  case 166: // object: game
#line 511 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2484 "./H2/compiler_parser.cpp"
    break;

  case 167: // vector: LPAREN num COMMA num COMMA num RPAREN
#line 516 "H2.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_vector>("", std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2490 "./H2/compiler_parser.cpp"
    break;

  case 168: // num: data_float
#line 520 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::float_ptr > ()); }
#line 2496 "./H2/compiler_parser.cpp"
    break;

  case 169: // num: data_integer
#line 521 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::integer_ptr > ()); }
#line 2502 "./H2/compiler_parser.cpp"
    break;

  case 170: // num: false
#line 522 "H2.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2508 "./H2/compiler_parser.cpp"
    break;

  case 171: // num: true
#line 523 "H2.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2514 "./H2/compiler_parser.cpp"
    break;

  case 172: // false: FALSE
#line 526 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>("", "0"); }
#line 2520 "./H2/compiler_parser.cpp"
    break;

  case 173: // true: TRUE
#line 527 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>("", "1"); }
#line 2526 "./H2/compiler_parser.cpp"
    break;

  case 174: // data_float: FLOAT
#line 528 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::float_ptr > () = std::make_unique<gsc::node_float>("", yystack_[0].value.as < std::string > ()); }
#line 2532 "./H2/compiler_parser.cpp"
    break;

  case 175: // data_integer: INTEGER
#line 529 "H2.parser.ypp"
                                { yylhs.value.as < gsc::integer_ptr > () = std::make_unique<gsc::node_integer>("", yystack_[0].value.as < std::string > ()); }
#line 2538 "./H2/compiler_parser.cpp"
    break;

  case 176: // data_localized_string: STRING_LOC
#line 530 "H2.parser.ypp"
                                   { yylhs.value.as < gsc::localized_string_ptr > () = std::make_unique<gsc::node_localized_string>("", yystack_[0].value.as < std::string > ()); }
#line 2544 "./H2/compiler_parser.cpp"
    break;

  case 177: // data_string: STRING
#line 531 "H2.parser.ypp"
                                { yylhs.value.as < gsc::string_ptr > () = std::make_unique<gsc::node_string>("", yystack_[0].value.as < std::string > ()); }
#line 2550 "./H2/compiler_parser.cpp"
    break;

  case 178: // identifier: IDENTIFIER
#line 532 "H2.parser.ypp"
                                { yylhs.value.as < gsc::identifier_ptr > () = std::make_unique<gsc::node_identifier>("", yystack_[0].value.as < std::string > ()); }
#line 2556 "./H2/compiler_parser.cpp"
    break;

  case 179: // filepath: FILEPATH
#line 533 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::filepath_ptr > () = std::make_unique<gsc::node_filepath>("", yystack_[0].value.as < std::string > ()); }
#line 2562 "./H2/compiler_parser.cpp"
    break;

  case 180: // empty_array: EMPTY_ARRAY
#line 534 "H2.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_empty_array>(""); }
#line 2568 "./H2/compiler_parser.cpp"
    break;

  case 181: // undefined: UNDEFINED
#line 535 "H2.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_undefined>(""); }
#line 2574 "./H2/compiler_parser.cpp"
    break;

  case 182: // size: SIZE
#line 536 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_size>(""); }
#line 2580 "./H2/compiler_parser.cpp"
    break;

  case 183: // game: GAME
#line 537 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_game>(""); }
#line 2586 "./H2/compiler_parser.cpp"
    break;

  case 184: // self: SELF
#line 538 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_self>(""); }
#line 2592 "./H2/compiler_parser.cpp"
    break;

  case 185: // anim: ANIM
#line 539 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_anim>(""); }
#line 2598 "./H2/compiler_parser.cpp"
    break;

  case 186: // level: LEVEL
#line 540 "H2.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_level>(""); }
#line 2604 "./H2/compiler_parser.cpp"
    break;


#line 2608 "./H2/compiler_parser.cpp"

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
  "FOREACH", "WHILE", "CONTINUE", "RETURN", "THREAD", "CALL", "WAIT",
  "WAITTILL", "WAITTILLMATCH", "WAITTILLFRAMEEND", "WAITFRAME", "ENDON",
  "NOTIFY", "IN", "UNDEFINED", "TRUE", "FALSE", "SIZE", "GAME", "LEVEL",
  "ANIM", "SELF", "EMPTY_ARRAY", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "COMMA", "DOT", "DOUBLECOLON", "COLON",
  "SEMICOLON", "QMARK", "MOD", "INCREMENT", "DECREMENT", "LSHIFT",
  "RSHIFT", "OR", "AND", "EQUALITY", "INEQUALITY", "LESS_EQUAL",
  "GREATER_EQUAL", "LESS", "GREATER", "ASSIGN", "ASSIGN_ADD", "ASSIGN_SUB",
  "ASSIGN_MULT", "ASSIGN_DIV", "ASSIGN_MOD", "ASSIGN_BITWISE_OR",
  "ASSIGN_BITWISE_AND", "ASSIGN_BITWISE_EXOR", "ASSIGN_LSHIFT",
  "ASSIGN_RSHIFT", "BITWISE_OR", "BITWISE_AND", "BITWISE_EXOR", "ADD",
  "SUB", "MULT", "DIV", "NOT", "COMPLEMENT", "FILEPATH", "IDENTIFIER",
  "STRING", "STRING_LOC", "FLOAT", "INTEGER", "IFX", "$accept", "root",
  "script", "include", "using_animtree", "animtree", "thread",
  "parameters", "block", "stmt", "stmt_call", "stmt_assign", "stmt_endon",
  "stmt_notify", "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_waitframe", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case",
  "stmt_default", "stmt_break", "stmt_continue", "stmt_return",
  "for_assign", "for_cond", "expr", "expr_assign", "expr_cmp",
  "expr_ternary", "expr_binary", "expr_primitive", "expr_call",
  "expr_call_thread", "expr_call_function", "expr_call_pointer",
  "expr_arguments", "expr_function_ref", "expr_array", "expr_field",
  "expr_size", "expr_vector", "expr_add_array", "object", "vector", "num",
  "false", "true", "data_float", "data_integer", "data_localized_string",
  "data_string", "identifier", "filepath", "empty_array", "undefined",
  "size", "game", "self", "anim", "level", YY_NULLPTR
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


  const short parser::yypact_ninf_ = -280;

  const short parser::yytable_ninf_ = -167;

  const short
  parser::yypact_[] =
  {
       6,   -73,     2,    17,  -280,    16,     6,  -280,  -280,  -280,
    -280,    21,  -280,    -4,   -59,   -59,  -280,  -280,  -280,  -280,
    -280,   -11,  -280,  -280,    41,    52,   -22,  -280,    49,    56,
      60,   -11,  -280,  -280,   224,  -280,    93,    95,   -51,    70,
      89,   104,   105,   106,   101,  1537,    11,   111,   126,   112,
     117,  -280,  -280,  -280,  -280,   124,  1000,  -280,  -280,  -280,
    -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,
    -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,   121,   123,
     127,  -280,  -280,  -280,  -280,  1645,   134,   130,  -280,  -280,
    -280,  -280,  1557,  1557,  -280,   135,   136,  -280,  -280,    43,
    1557,  1557,  -280,  -280,  -280,  -280,  -280,  1557,  1617,   -11,
    -280,  1557,  1557,  -280,  -280,  2241,   132,  -280,  -280,  -280,
      19,  -280,  -280,    23,    30,  -280,  -280,  -280,    63,  -280,
    -280,  -280,  -280,  -280,  -280,  -280,  -280,     9,   139,  -280,
    -280,    79,    90,    96,   103,  -280,  -280,   134,   146,  1557,
     141,  -280,  -280,  1557,  -280,  -280,  -280,  -280,  -280,    11,
     153,   155,   156,   157,  1617,   -11,  -280,  -280,  1557,  1557,
    1557,  1557,  1557,  1557,  1557,  1557,  1557,  1557,  1557,  -280,
    -280,  1557,   -11,  1807,  1838,  -280,  -280,   150,  -280,  -280,
    1699,   564,  1869,   647,   158,  1617,  2272,    26,  -280,  2272,
    2272,  -280,  1557,  1557,  1557,  1557,  1557,  1557,  1557,  1557,
    1557,  1557,  1557,  1557,  1557,  1557,  1557,  1557,  1557,  1557,
    1557,   -17,   -11,  1557,  1900,  -280,  1555,  -280,  -280,  1557,
    1557,  1557,  1557,  2062,  -280,  2272,  2272,  2272,  2272,  2272,
    2272,  2272,  2272,  2272,  2272,  2272,   -20,   162,  1036,   163,
    1557,  1557,  1088,  -280,  1557,   128,  1555,  -280,  1557,  2272,
    2272,  2272,  2272,  2272,  2272,  2272,  2272,  2272,  2272,  2272,
    2272,  2272,  2272,  2272,  2272,  2272,  2272,  2208,  -280,  -280,
     162,  2100,   159,   161,  1734,  2137,  1931,  1776,  -280,  -280,
    1557,   224,   196,   224,   169,  2272,    80,  1962,   224,  -280,
    2174,   164,  2272,  1557,   166,  -280,   168,   171,  1557,  1557,
     172,   173,  1557,   -19,  1121,  1166,  1199,    43,  1243,  1278,
    1557,   128,  2272,   187,  1557,  -280,   -12,  1993,  -280,  -280,
      -9,  -280,   202,   224,  -280,  -280,   188,   224,  -280,  -280,
    2024,   189,  1557,    13,   178,   181,   183,  1323,  1356,  1401,
    1434,  -280,  -280,    27,  -280,  -280,  -280,  -280,   224,  -280,
    -280,   224,  -280,  -280,  -280,  1478,  1513,  -280,  -280
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,   178,     0,     2,     8,     9,    10,
      11,     0,   179,     0,     0,     0,     1,     4,     5,     6,
       7,    18,    12,   177,     0,     0,     0,    17,     0,     0,
       0,     0,    13,    14,    21,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   183,   186,   185,   184,     0,     0,    20,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,     0,   159,
       0,   137,   138,   160,   161,     0,   162,     0,   166,   165,
     164,   163,     0,     0,   175,     0,     0,    70,    71,    76,
       0,     0,    72,   181,   173,   172,   180,     0,   151,     0,
      74,     0,     0,   176,   174,     0,    79,    80,    81,    82,
     118,   119,   120,   121,   122,   123,   124,   125,     0,   126,
     127,   170,   171,   168,   169,   128,   129,   130,     0,   131,
     132,   133,   134,   135,   136,   141,   142,     0,     0,     0,
       0,    53,    54,     0,    15,    19,    44,    42,    43,     0,
       0,     0,     0,     0,     0,     0,    83,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   139,
     140,   151,     0,     0,     0,    68,    69,     0,    75,   159,
       0,     0,     0,     0,   127,   151,   150,     0,   152,   117,
     116,    73,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,     0,   143,   144,     0,
       0,     0,     0,     0,   155,    85,    91,    92,    93,    94,
      95,    86,    87,    88,    89,    90,     0,     0,     0,     0,
      78,     0,     0,   115,     0,     0,   150,   158,     0,   114,
     108,   109,    96,    97,    98,    99,   100,   101,   102,   103,
     105,   106,   107,   110,   111,   112,   113,     0,   182,   156,
     153,     0,     0,     0,     0,     0,     0,     0,   154,   145,
     151,    21,    56,    21,     0,     0,    79,     0,    21,    62,
       0,     0,   149,     0,     0,    48,     0,     0,   151,     0,
       0,     0,   151,     0,     0,     0,     0,    76,     0,     0,
       0,     0,   104,     0,   151,    51,     0,     0,    45,    47,
       0,   146,    55,    21,    60,    67,     0,    21,    66,    61,
       0,     0,   151,     0,     0,     0,     0,     0,     0,     0,
       0,   157,   167,     0,   147,    50,    52,    46,    21,    59,
      58,    21,    64,    65,   148,     0,     0,    57,    63
  };

  const short
  parser::yypgoto_[] =
  {
    -280,  -280,  -280,   225,   238,   239,   243,  -280,  -279,   -53,
    -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,
    -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,  -280,
     -67,  -280,   770,   -97,     1,  -280,  -280,  -280,    76,   542,
     -42,   -41,  -174,  -280,   154,   160,  -280,  -280,  -280,   236,
    -280,   -47,  -280,  -280,  -280,   216,  -280,   138,     0,    38,
    -280,  -280,  -280,   312,   399,   460,   536
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,     9,    10,    26,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
     187,   294,   196,    78,   116,   117,   118,   119,   120,   121,
      81,    82,   197,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   279,   141,   142,   143,   144
  };

  const short
  parser::yytable_[] =
  {
      11,   150,   188,   155,   145,   146,    11,   246,    12,     1,
       2,     3,   314,   278,   316,    30,    16,   289,   331,   319,
      31,    27,   258,   258,    23,   344,  -162,  -162,   346,    47,
     258,    35,    23,   258,    86,    94,  -159,  -159,    14,    13,
    -160,  -160,    22,   179,   180,   181,   147,  -161,  -161,  -162,
     354,    55,  -162,    15,   348,   258,    86,    21,   350,  -159,
     194,    47,  -159,  -160,   364,     4,  -160,   257,   258,   258,
    -161,     4,    87,  -161,    51,    52,    53,    54,    28,   365,
     159,    47,   366,    55,    87,   147,   179,   180,     4,    29,
    -162,  -162,    12,     4,    87,    32,  -166,  -166,    34,    86,
    -159,  -159,    33,   164,  -160,  -160,   221,  -165,  -165,   198,
      79,  -161,  -161,  -164,  -164,    97,   313,   227,   228,  -166,
    -163,  -163,  -166,    87,    12,     4,   -77,   220,   147,    92,
    -165,    93,    79,  -165,   326,    98,  -164,    87,   330,  -164,
      99,   100,   101,  -163,    12,     4,  -163,   102,   179,   180,
     343,   148,    24,    25,   104,   105,   104,   105,   151,   147,
    -166,  -166,   149,   152,   153,   234,    87,   156,   353,   157,
     181,  -165,  -165,   158,   182,   189,    96,  -164,  -164,   220,
     185,   186,   247,   222,  -163,  -163,   223,   225,    83,   229,
     147,   230,   231,   232,    84,   292,   250,    87,   290,   299,
     255,   293,   306,   315,   324,   305,   321,   323,   301,   347,
      83,   114,    94,   114,    94,   317,    84,   325,   328,   329,
     188,   234,   280,   342,   355,   349,   352,   356,    87,   357,
      36,    17,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    18,    19,    49,    50,    86,    20,
     336,   296,    86,    83,    95,    51,    52,    53,    54,    84,
       0,   155,   334,   155,    55,   338,   155,     0,     0,     0,
      85,     0,     0,     0,   341,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,     0,     0,     0,
      87,    86,    85,    86,   359,   155,   362,   155,    86,     0,
       0,     0,     0,     0,     0,    12,     4,     0,     0,     0,
       0,     0,   155,   155,    86,    86,    86,    86,    86,    86,
       0,     0,     0,     0,    79,     0,     0,     0,    79,    87,
       0,    87,     0,    86,     0,   190,    87,    86,     0,     0,
       0,     0,     0,     0,     0,     0,    88,    86,    86,    86,
      86,     0,    87,    87,    87,    87,    87,    87,    86,     0,
       0,    86,     0,     0,     0,    86,    86,    79,    88,    79,
       0,    87,     0,     0,    79,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    87,    87,    87,    87,     0,
      79,    79,    79,   189,    79,    79,    87,     0,     0,    87,
       0,     0,    83,    87,    87,     0,    83,     0,    84,    79,
       0,    88,    84,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,    79,    79,    79,     0,     0,     0,
       0,     0,     0,    89,    79,     0,     0,    79,     0,     0,
       0,    79,    79,     0,     0,    83,     0,    83,     0,     0,
       0,    84,    83,    84,     0,    89,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    83,    83,
      83,    83,    83,    83,    84,    84,    84,    84,    84,    84,
       0,     0,     0,     0,    85,     0,     0,    83,    85,     0,
       0,    83,     0,    84,    90,     0,     0,    84,    89,     0,
       0,    83,    83,    83,    83,     0,     0,    84,    84,    84,
      84,     0,    83,     0,     0,    83,    90,     0,    84,    83,
      83,    84,     0,     0,     0,    84,    84,    85,     0,    85,
       0,     0,     0,     0,    85,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    85,    85,   190,    85,    85,     0,     0,     0,    90,
      88,     0,     0,     0,    88,     0,     0,     0,     0,    85,
      91,     0,     0,    85,     0,     0,    80,     0,     0,     0,
       0,     0,     0,    85,    85,    85,    85,     0,     0,     0,
     251,     0,    91,     0,    85,     0,     0,    85,    80,     0,
       0,    85,    85,    88,     0,    88,     0,     0,     0,     0,
      88,     0,   202,     0,     0,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,    88,    88,    88,    88,
      88,    88,     0,     0,     0,    91,   213,   214,   215,   216,
     217,   218,   219,     0,     0,    88,     0,    89,     0,    88,
       0,    89,     0,     0,     0,     0,     0,     0,     0,    88,
      88,    88,    88,     0,     0,     0,     0,     0,     0,     0,
      88,     0,     0,    88,     0,     0,     0,    88,    88,     0,
       0,     0,     0,     0,   253,     0,     0,     0,     0,   254,
      89,     0,    89,     0,     0,   202,     0,    89,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,    90,     0,
       0,     0,    90,    89,    89,    89,    89,    89,    89,   213,
     214,   215,   216,   217,   218,   219,     0,     0,     0,     0,
       0,     0,    89,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    89,    89,    89,
       0,    90,     0,    90,     0,     0,     0,    89,    90,     0,
      89,     0,     0,     0,    89,    89,     0,     0,     0,     0,
       0,     0,     0,     0,    90,    90,    90,    90,    90,    90,
       0,     0,     0,     0,    91,     0,     0,     0,    91,     0,
      80,     0,     0,    90,    80,     0,     0,    90,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,    90,    90,
      90,     0,     0,     0,     0,   115,     0,     0,    90,     0,
       0,    90,     0,     0,     0,    90,    90,    91,     0,    91,
       0,     0,     0,    80,    91,    80,     0,     0,     0,     0,
      80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    91,    91,    91,    91,    91,    80,    80,    80,     0,
      80,    80,   183,   184,     0,     0,     0,     0,     0,    91,
     191,   192,     0,    91,     0,    80,     0,   193,     0,    80,
       0,   199,   200,    91,    91,    91,    91,     0,     0,    80,
      80,    80,    80,     0,    91,     0,     0,    91,     0,     0,
      80,    91,    91,    80,     0,     0,     0,    80,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   224,
       0,     0,     0,   226,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   233,     0,     0,     0,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   256,     0,     0,     0,     0,
       0,     0,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,     0,     0,   281,     0,     0,     0,     0,     0,   284,
     285,   286,   287,     0,     0,     0,    36,     0,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
     295,   297,    49,    50,   300,     0,     0,     0,   302,     0,
       0,    51,    52,    53,    54,     0,     0,     0,     0,   154,
      55,     0,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,     0,     0,    49,    50,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,     0,     0,   322,   291,     0,    55,     0,     0,   327,
       0,    12,     4,     0,     0,     0,     0,     0,     0,     0,
     340,     0,     0,     0,    36,     0,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,     0,     0,
      49,    50,     0,     0,     0,     0,     0,    12,     4,    51,
      52,    53,    54,     0,     0,     0,   298,    36,    55,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    53,    54,     0,     0,     0,     0,
     332,    55,     0,     0,     0,     0,     0,     0,     0,    12,
       4,     0,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,     0,     0,    49,    50,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,     0,    12,     4,   333,    36,    55,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     0,
       0,    49,    50,     0,     0,     0,     0,     0,     0,     0,
      51,    52,    53,    54,     0,     0,     0,     0,   335,    55,
       0,     0,     0,     0,     0,     0,     0,    12,     4,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,     0,     0,
      12,     4,   337,    55,    36,     0,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    53,    54,     0,     0,     0,     0,   339,    55,     0,
       0,     0,     0,     0,    12,     4,     0,     0,     0,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,     0,    12,
       4,   358,    36,    55,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,     0,     0,    49,    50,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,     0,     0,     0,     0,   360,    55,     0,     0,     0,
       0,     0,     0,     0,    12,     4,     0,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    53,    54,     0,    12,     4,   361,
      36,    55,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,     0,
       0,     0,     0,   363,    55,     0,     0,     0,     0,     0,
       0,     0,    12,     4,    36,     0,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    53,    54,     0,     0,    12,     4,   367,    55,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,     0,     0,
       0,     0,   368,    55,    46,    47,     0,     0,     0,    12,
       4,     0,     0,     0,   103,   104,   105,     0,    51,    52,
      53,    54,   106,   107,    46,    47,     0,   108,     0,     0,
       0,   109,     0,   110,   103,   104,   105,     0,    51,    52,
      53,    54,   106,   107,    12,     4,   283,   108,     0,     0,
       0,   109,     0,   202,     0,     0,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   111,   112,    12,     4,
      23,   113,   114,    94,     0,     0,     0,   213,   214,   215,
     216,   217,   218,   219,    46,    47,   111,   112,    12,     4,
      23,   113,   114,    94,   103,   104,   105,     0,    51,    52,
      53,    54,   106,   107,     0,     0,     0,   195,     0,     0,
       0,   109,   159,    47,     0,   160,   161,     0,     0,   162,
     163,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   164,     0,     0,   165,     0,
       0,     0,     0,     0,   166,   167,   111,   112,    12,     4,
      23,   113,   114,    94,     0,     0,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,    47,     0,     0,
       0,     0,     0,     0,     0,     0,    12,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   164,
       0,     0,   165,     0,     0,     0,     0,     0,   166,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   307,     0,     0,     0,     0,   308,     0,     0,     0,
      12,     4,   202,     0,     0,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   213,   214,   215,   216,
     217,   218,   219,   311,     0,     0,     0,     0,   312,     0,
       0,     0,     0,     0,   202,     0,     0,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,     0,     0,
       0,     0,     0,     0,   248,     0,     0,     0,   213,   214,
     215,   216,   217,   218,   219,   202,     0,     0,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
       0,     0,     0,     0,     0,   249,     0,     0,     0,   213,
     214,   215,   216,   217,   218,   219,   202,     0,     0,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
       0,     0,     0,     0,     0,     0,   252,     0,     0,     0,
     213,   214,   215,   216,   217,   218,   219,   202,     0,     0,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,     0,     0,     0,     0,     0,     0,   282,     0,     0,
       0,   213,   214,   215,   216,   217,   218,   219,   202,     0,
       0,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,     0,     0,     0,     0,     0,     0,   310,     0,
       0,     0,   213,   214,   215,   216,   217,   218,   219,   202,
       0,     0,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,     0,     0,     0,     0,     0,     0,   318,
       0,     0,     0,   213,   214,   215,   216,   217,   218,   219,
     202,     0,     0,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,     0,     0,     0,     0,     0,     0,
     345,     0,     0,     0,   213,   214,   215,   216,   217,   218,
     219,   202,     0,     0,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,     0,     0,     0,     0,     0,
       0,   351,     0,     0,     0,   213,   214,   215,   216,   217,
     218,   219,   202,     0,     0,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   213,   214,   215,   216,
     217,   218,   219,   288,     0,     0,     0,     0,     0,     0,
     202,     0,     0,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   213,   214,   215,   216,   217,   218,
     219,   304,     0,     0,     0,     0,     0,     0,   202,     0,
       0,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   213,   214,   215,   216,   217,   218,   219,   309,
       0,     0,     0,     0,     0,   202,     0,     0,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   213,
     214,   215,   216,   217,   218,   219,   320,     0,     0,     0,
       0,     0,   202,     0,     0,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   213,   214,   215,   216,
     217,   218,   219,   303,     0,     0,   202,     0,     0,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     213,   214,   215,   216,   217,   218,   219,   201,     0,   202,
       0,     0,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   213,   214,   215,   216,   217,   218,   219,
     202,     0,     0,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   213,   214,   215,   216,   217,   218,
     219
  };

  const short
  parser::yycheck_[] =
  {
       0,    48,    99,    56,    46,    46,     6,   181,    81,     3,
       4,     5,   291,    30,   293,    37,     0,    37,    37,   298,
      42,    21,    42,    42,    83,    37,    17,    18,    37,    18,
      42,    31,    83,    42,    34,    86,    17,    18,    36,     1,
      17,    18,    46,    85,    85,    36,    46,    17,    18,    40,
      37,    40,    43,    36,   333,    42,    56,    36,   337,    40,
     107,    18,    43,    40,    37,    82,    43,    41,    42,    42,
      40,    82,    34,    43,    31,    32,    33,    34,    37,   358,
      17,    18,   361,    40,    46,    85,   128,   128,    82,    37,
      81,    82,    81,    82,    56,    46,    17,    18,    38,    99,
      81,    82,    46,    40,    81,    82,    43,    17,    18,   109,
      34,    81,    82,    17,    18,    45,   290,   159,   159,    40,
      17,    18,    43,    85,    81,    82,    46,    47,   128,    36,
      40,    36,    56,    43,   308,    46,    40,    99,   312,    43,
      36,    36,    36,    40,    81,    82,    43,    46,   190,   190,
     324,    40,    14,    15,    28,    29,    28,    29,    46,   159,
      81,    82,    36,    46,    40,   165,   128,    46,   342,    46,
      36,    81,    82,    46,    44,    99,    38,    81,    82,    47,
      45,    45,   182,    44,    81,    82,    40,    46,    34,    36,
     190,    36,    36,    36,    34,   248,    46,   159,    36,   252,
      42,    38,    41,     7,    36,    46,    42,    41,   255,     7,
      56,    85,    86,    85,    86,    46,    56,    46,    46,    46,
     317,   221,   222,    36,    46,    37,    37,    46,   190,    46,
       6,     6,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     6,     6,    22,    23,   248,     6,
     317,   250,   252,    99,    38,    31,    32,    33,    34,    99,
      -1,   314,   315,   316,    40,   318,   319,    -1,    -1,    -1,
      34,    -1,    -1,    -1,   321,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,    -1,
     252,   291,    56,   293,   347,   348,   349,   350,   298,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,   365,   366,   314,   315,   316,   317,   318,   319,
      -1,    -1,    -1,    -1,   248,    -1,    -1,    -1,   252,   291,
      -1,   293,    -1,   333,    -1,    99,   298,   337,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,   347,   348,   349,
     350,    -1,   314,   315,   316,   317,   318,   319,   358,    -1,
      -1,   361,    -1,    -1,    -1,   365,   366,   291,    56,   293,
      -1,   333,    -1,    -1,   298,   337,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   347,   348,   349,   350,    -1,
     314,   315,   316,   317,   318,   319,   358,    -1,    -1,   361,
      -1,    -1,   248,   365,   366,    -1,   252,    -1,   248,   333,
      -1,    99,   252,   337,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   347,   348,   349,   350,    -1,    -1,    -1,
      -1,    -1,    -1,    34,   358,    -1,    -1,   361,    -1,    -1,
      -1,   365,   366,    -1,    -1,   291,    -1,   293,    -1,    -1,
      -1,   291,   298,   293,    -1,    56,    -1,    -1,   298,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   314,   315,
     316,   317,   318,   319,   314,   315,   316,   317,   318,   319,
      -1,    -1,    -1,    -1,   248,    -1,    -1,   333,   252,    -1,
      -1,   337,    -1,   333,    34,    -1,    -1,   337,    99,    -1,
      -1,   347,   348,   349,   350,    -1,    -1,   347,   348,   349,
     350,    -1,   358,    -1,    -1,   361,    56,    -1,   358,   365,
     366,   361,    -1,    -1,    -1,   365,   366,   291,    -1,   293,
      -1,    -1,    -1,    -1,   298,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     314,   315,   316,   317,   318,   319,    -1,    -1,    -1,    99,
     248,    -1,    -1,    -1,   252,    -1,    -1,    -1,    -1,   333,
      34,    -1,    -1,   337,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,   347,   348,   349,   350,    -1,    -1,    -1,
      26,    -1,    56,    -1,   358,    -1,    -1,   361,    56,    -1,
      -1,   365,   366,   291,    -1,   293,    -1,    -1,    -1,    -1,
     298,    -1,    48,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,   314,   315,   316,   317,
     318,   319,    -1,    -1,    -1,    99,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,   333,    -1,   248,    -1,   337,
      -1,   252,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   347,
     348,   349,   350,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     358,    -1,    -1,   361,    -1,    -1,    -1,   365,   366,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    42,
     291,    -1,   293,    -1,    -1,    48,    -1,   298,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,   248,    -1,
      -1,    -1,   252,   314,   315,   316,   317,   318,   319,    72,
      73,    74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,
      -1,    -1,   333,    -1,    -1,    -1,   337,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   347,   348,   349,   350,
      -1,   291,    -1,   293,    -1,    -1,    -1,   358,   298,    -1,
     361,    -1,    -1,    -1,   365,   366,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   314,   315,   316,   317,   318,   319,
      -1,    -1,    -1,    -1,   248,    -1,    -1,    -1,   252,    -1,
     248,    -1,    -1,   333,   252,    -1,    -1,   337,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   347,   348,   349,
     350,    -1,    -1,    -1,    -1,    45,    -1,    -1,   358,    -1,
      -1,   361,    -1,    -1,    -1,   365,   366,   291,    -1,   293,
      -1,    -1,    -1,   291,   298,   293,    -1,    -1,    -1,    -1,
     298,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     314,   315,   316,   317,   318,   319,   314,   315,   316,    -1,
     318,   319,    92,    93,    -1,    -1,    -1,    -1,    -1,   333,
     100,   101,    -1,   337,    -1,   333,    -1,   107,    -1,   337,
      -1,   111,   112,   347,   348,   349,   350,    -1,    -1,   347,
     348,   349,   350,    -1,   358,    -1,    -1,   361,    -1,    -1,
     358,   365,   366,   361,    -1,    -1,    -1,   365,   366,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
      -1,    -1,    -1,   153,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   164,    -1,    -1,    -1,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   195,    -1,    -1,    -1,    -1,
      -1,    -1,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,    -1,    -1,   223,    -1,    -1,    -1,    -1,    -1,   229,
     230,   231,   232,    -1,    -1,    -1,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
     250,   251,    22,    23,   254,    -1,    -1,    -1,   258,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    -1,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,   303,    38,    -1,    40,    -1,    -1,   309,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     320,    -1,    -1,    -1,     6,    -1,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    81,    82,    31,
      32,    33,    34,    -1,    -1,    -1,    38,     6,    40,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    81,    82,    38,     6,    40,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,
      81,    82,    39,    40,     6,    -1,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,    81,
      82,    38,     6,    40,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    81,    82,    38,
       6,    40,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,     6,    -1,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    81,    82,    39,    40,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,    40,    17,    18,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    17,    18,    -1,    40,    -1,    -1,
      -1,    44,    -1,    46,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    81,    82,    41,    40,    -1,    -1,
      -1,    44,    -1,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    79,    80,    81,    82,
      83,    84,    85,    86,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    17,    18,    79,    80,    81,    82,
      83,    84,    85,    86,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    44,    17,    18,    -1,    20,    21,    -1,    -1,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    49,    50,    79,    80,    81,    82,
      83,    84,    85,    86,    -1,    -1,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    37,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      81,    82,    48,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    37,    -1,    -1,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    48,    -1,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    48,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    48,    -1,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    48,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    48,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      48,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    48,    -1,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    48,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    42,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    42,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    45,    -1,    -1,    48,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    46,    -1,    48,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      48,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,    82,    89,    90,    91,    92,    93,
      94,   146,    81,   147,    36,    36,     0,    91,    92,    93,
      94,    36,    46,    83,   145,   145,    95,   146,    37,    37,
      37,    42,    46,    46,    38,   146,     6,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    22,
      23,    31,    32,    33,    34,    40,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   121,   126,
     127,   128,   129,   132,   133,   137,   146,   147,   151,   152,
     153,   154,    36,    36,    86,   143,   145,    45,    46,    36,
      36,    36,    46,    27,    28,    29,    35,    36,    40,    44,
      46,    79,    80,    84,    85,   120,   122,   123,   124,   125,
     126,   127,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   151,   152,   153,   154,   128,   129,   146,    40,    36,
     139,    46,    46,    40,    39,    97,    46,    46,    46,    17,
      20,    21,    24,    25,    40,    43,    49,    50,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,   128,
     129,    36,    44,   120,   120,    45,    45,   118,   121,   126,
     137,   120,   120,   120,   139,    40,   120,   130,   146,   120,
     120,    46,    48,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    72,    73,    74,    75,    76,    77,    78,
      47,    43,    44,    40,   120,    46,   120,   128,   129,    36,
      36,    36,    36,   120,   146,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   130,   146,    37,    37,
      46,    26,    37,    37,    42,    42,   120,    41,    42,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,    30,   150,
     146,   120,    37,    41,   120,   120,   120,   120,    41,    37,
      36,    38,    97,    38,   119,   120,   122,   120,    38,    97,
     120,   139,   120,    45,    41,    46,    41,    37,    42,    42,
      37,    37,    42,   130,    96,     7,    96,    46,    37,    96,
      42,    42,   120,    41,    36,    46,   130,   120,    46,    46,
     130,    37,    39,    38,    97,    39,   118,    39,    97,    39,
     120,   139,    36,   130,    37,    37,    37,     7,    96,    37,
      96,    37,    37,   130,    37,    46,    46,    46,    38,    97,
      39,    38,    97,    39,    37,    96,    96,    39,    39
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    88,    89,    89,    90,    90,    90,    90,    90,    90,
      90,    90,    91,    92,    93,    94,    95,    95,    95,    96,
      96,    96,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    98,    98,    99,   100,   101,   101,   102,   102,
     103,   103,   104,   105,   106,   107,   107,   108,   108,   108,
     108,   109,   109,   110,   110,   111,   111,   112,   113,   113,
     114,   115,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   120,   120,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   122,   122,   122,   122,
     122,   122,   122,   122,   123,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   126,   126,   126,
     126,   127,   127,   127,   127,   128,   128,   129,   129,   130,
     130,   130,   131,   131,   132,   133,   134,   135,   136,   137,
     137,   137,   137,   137,   137,   137,   137,   138,   139,   139,
     139,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     2,     1,     1,
       1,     1,     3,     5,     5,     7,     3,     1,     0,     2,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     6,     8,     6,     5,     3,
       8,     6,     8,     2,     2,     7,     5,    11,     9,     9,
       7,     7,     5,    11,     9,     9,     7,     7,     3,     3,
       2,     2,     2,     3,     2,     1,     0,     1,     0,     1,
       1,     1,     1,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     5,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     4,     6,     8,     9,     3,
       1,     0,     2,     3,     4,     3,     3,     7,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     7,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   114,   114,   115,   119,   121,   123,   125,   127,   129,
     131,   133,   138,   143,   148,   153,   158,   160,   163,   167,
     169,   172,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   199,   201,   206,   211,   216,   218,   223,   225,
     230,   232,   237,   242,   247,   252,   254,   262,   264,   269,
     274,   284,   286,   294,   296,   305,   307,   316,   321,   323,
     328,   333,   337,   342,   344,   349,   350,   354,   355,   359,
     360,   361,   362,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   382,   383,   384,   385,
     386,   387,   388,   389,   393,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   435,   436,   437,
     438,   442,   443,   444,   445,   449,   451,   456,   458,   463,
     465,   468,   472,   474,   479,   484,   489,   494,   499,   504,
     505,   506,   507,   508,   509,   510,   511,   515,   520,   521,
     522,   523,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540
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
#line 3822 "./H2/compiler_parser.cpp"

#line 542 "H2.parser.ypp"


void yy::parser::error(const std::string& msg)
{
    GSC_COMP_ERROR("%s", msg.data());
}
