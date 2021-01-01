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
#line 36 "IW7.parser.ypp"

    #include "IW7.hpp"
	#include "compiler_parser.hpp"
	#include "compiler_lexer.hpp"
	IW7::parser::symbol_type yylex(yyscan_t yyscanner, std::uint32_t *location);

#line 46 "./IW7/compiler_parser.cpp"




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

#line 13 "IW7.parser.ypp"
namespace  IW7  {
#line 127 "./IW7/compiler_parser.cpp"

  /// Build a parser object.
  parser::parser (yyscan_t yyscanner_yyarg, std::uint32_t *location_yyarg, gsc::script_ptr& astout_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      yyscanner (yyscanner_yyarg),
      location (location_yyarg),
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
            symbol_type yylookahead (yylex (yyscanner, location));
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
#line 116 "IW7.parser.ypp"
                 { astout = std::move(yystack_[0].value.as < gsc::script_ptr > ()); }
#line 1457 "./IW7/compiler_parser.cpp"
    break;

  case 3: // root: %empty
#line 117 "IW7.parser.ypp"
                 { astout = std::make_unique<gsc::node_script>(""); }
#line 1463 "./IW7/compiler_parser.cpp"
    break;

  case 4: // script: script include
#line 122 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ())); }
#line 1469 "./IW7/compiler_parser.cpp"
    break;

  case 5: // script: script using_animtree
#line 124 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1475 "./IW7/compiler_parser.cpp"
    break;

  case 6: // script: script animtree
#line 126 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1481 "./IW7/compiler_parser.cpp"
    break;

  case 7: // script: script thread
#line 128 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ())); }
#line 1487 "./IW7/compiler_parser.cpp"
    break;

  case 8: // script: include
#line 130 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(""); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ()));}
#line 1493 "./IW7/compiler_parser.cpp"
    break;

  case 9: // script: using_animtree
#line 132 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(""); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1499 "./IW7/compiler_parser.cpp"
    break;

  case 10: // script: animtree
#line 134 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(""); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1505 "./IW7/compiler_parser.cpp"
    break;

  case 11: // script: thread
#line 136 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(""); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ()));}
#line 1511 "./IW7/compiler_parser.cpp"
    break;

  case 12: // include: INCLUDE filepath SEMICOLON
#line 141 "IW7.parser.ypp"
                { yylhs.value.as < gsc::include_ptr > () = std::make_unique<gsc::node_include>("", std::move(yystack_[1].value.as < gsc::filepath_ptr > ())); }
#line 1517 "./IW7/compiler_parser.cpp"
    break;

  case 13: // using_animtree: USING_ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 146 "IW7.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>("", std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1523 "./IW7/compiler_parser.cpp"
    break;

  case 14: // animtree: ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 151 "IW7.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>("", std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1529 "./IW7/compiler_parser.cpp"
    break;

  case 15: // thread: identifier LPAREN parameters RPAREN LBRACE block RBRACE
#line 156 "IW7.parser.ypp"
                { yylhs.value.as < gsc::thread_ptr > () = std::make_unique<gsc::node_thread>("", std::move(yystack_[6].value.as < gsc::identifier_ptr > ()), std::move(yystack_[4].value.as < gsc::parameters_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1535 "./IW7/compiler_parser.cpp"
    break;

  case 16: // parameters: parameters COMMA identifier
#line 161 "IW7.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::move(yystack_[2].value.as < gsc::parameters_ptr > ()); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1541 "./IW7/compiler_parser.cpp"
    break;

  case 17: // parameters: identifier
#line 163 "IW7.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(""); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1547 "./IW7/compiler_parser.cpp"
    break;

  case 18: // parameters: %empty
#line 165 "IW7.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(""); }
#line 1553 "./IW7/compiler_parser.cpp"
    break;

  case 19: // block: block stmt
#line 170 "IW7.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::move(yystack_[1].value.as < gsc::block_ptr > ()); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1559 "./IW7/compiler_parser.cpp"
    break;

  case 20: // block: stmt
#line 172 "IW7.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(""); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1565 "./IW7/compiler_parser.cpp"
    break;

  case 21: // block: %empty
#line 174 "IW7.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(""); }
#line 1571 "./IW7/compiler_parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 178 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_call = std::move(yystack_[0].value.as < gsc::stmt_call_ptr > ()); }
#line 1577 "./IW7/compiler_parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 179 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < gsc::stmt_assign_ptr > ()); }
#line 1583 "./IW7/compiler_parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 180 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < gsc::stmt_endon_ptr > ()); }
#line 1589 "./IW7/compiler_parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 181 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < gsc::stmt_notify_ptr > ()); }
#line 1595 "./IW7/compiler_parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 182 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < gsc::stmt_wait_ptr > ()); }
#line 1601 "./IW7/compiler_parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 183 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < gsc::stmt_waittill_ptr > ()); }
#line 1607 "./IW7/compiler_parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 184 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < gsc::stmt_waittillmatch_ptr > ()); }
#line 1613 "./IW7/compiler_parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 185 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < gsc::stmt_waittillframeend_ptr > ()); }
#line 1619 "./IW7/compiler_parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 186 "IW7.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_if = std::move(yystack_[0].value.as < gsc::stmt_if_ptr > ()); }
#line 1625 "./IW7/compiler_parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 187 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < gsc::stmt_ifelse_ptr > ()); }
#line 1631 "./IW7/compiler_parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 188 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_while = std::move(yystack_[0].value.as < gsc::stmt_while_ptr > ()); }
#line 1637 "./IW7/compiler_parser.cpp"
    break;

  case 33: // stmt: stmt_for
#line 189 "IW7.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_for = std::move(yystack_[0].value.as < gsc::stmt_for_ptr > ()); }
#line 1643 "./IW7/compiler_parser.cpp"
    break;

  case 34: // stmt: stmt_foreach
#line 190 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < gsc::stmt_foreach_ptr > ()); }
#line 1649 "./IW7/compiler_parser.cpp"
    break;

  case 35: // stmt: stmt_switch
#line 191 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < gsc::stmt_switch_ptr > ()); }
#line 1655 "./IW7/compiler_parser.cpp"
    break;

  case 36: // stmt: stmt_case
#line 192 "IW7.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_case = std::move(yystack_[0].value.as < gsc::stmt_case_ptr > ()); }
#line 1661 "./IW7/compiler_parser.cpp"
    break;

  case 37: // stmt: stmt_default
#line 193 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_default = std::move(yystack_[0].value.as < gsc::stmt_default_ptr > ()); }
#line 1667 "./IW7/compiler_parser.cpp"
    break;

  case 38: // stmt: stmt_break
#line 194 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_break = std::move(yystack_[0].value.as < gsc::stmt_break_ptr > ()); }
#line 1673 "./IW7/compiler_parser.cpp"
    break;

  case 39: // stmt: stmt_continue
#line 195 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < gsc::stmt_continue_ptr > ()); }
#line 1679 "./IW7/compiler_parser.cpp"
    break;

  case 40: // stmt: stmt_return
#line 196 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_return = std::move(yystack_[0].value.as < gsc::stmt_return_ptr > ()); }
#line 1685 "./IW7/compiler_parser.cpp"
    break;

  case 41: // stmt_call: expr_call SEMICOLON
#line 201 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>("", std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1691 "./IW7/compiler_parser.cpp"
    break;

  case 42: // stmt_call: expr_call_thread SEMICOLON
#line 203 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>("", std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1697 "./IW7/compiler_parser.cpp"
    break;

  case 43: // stmt_assign: expr_assign SEMICOLON
#line 208 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_assign_ptr > () = std::make_unique<gsc::node_stmt_assign>("", std::move(yystack_[1].value.as < gsc::expr_assign_ptr > ())); }
#line 1703 "./IW7/compiler_parser.cpp"
    break;

  case 44: // stmt_endon: object ENDON LPAREN expr RPAREN SEMICOLON
#line 213 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_endon_ptr > () = std::make_unique<gsc::node_stmt_endon>("", std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1709 "./IW7/compiler_parser.cpp"
    break;

  case 45: // stmt_notify: object NOTIFY LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 218 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>("", std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1715 "./IW7/compiler_parser.cpp"
    break;

  case 46: // stmt_notify: object NOTIFY LPAREN expr RPAREN SEMICOLON
#line 220 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>("", std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>("")); }
#line 1721 "./IW7/compiler_parser.cpp"
    break;

  case 47: // stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON
#line 225 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1727 "./IW7/compiler_parser.cpp"
    break;

  case 48: // stmt_wait: WAIT num SEMICOLON
#line 227 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>("", std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1733 "./IW7/compiler_parser.cpp"
    break;

  case 49: // stmt_waittill: object WAITTILL LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 232 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>("", std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1739 "./IW7/compiler_parser.cpp"
    break;

  case 50: // stmt_waittill: object WAITTILL LPAREN expr RPAREN SEMICOLON
#line 234 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>("", std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>("")); }
#line 1745 "./IW7/compiler_parser.cpp"
    break;

  case 51: // stmt_waittillmatch: object WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON
#line 239 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillmatch_ptr > () = std::make_unique<gsc::node_stmt_waittillmatch>("", std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1751 "./IW7/compiler_parser.cpp"
    break;

  case 52: // stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON
#line 244 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillframeend_ptr > () = std::make_unique<gsc::node_stmt_waittillframeend>(""); }
#line 1757 "./IW7/compiler_parser.cpp"
    break;

  case 53: // stmt_if: IF LPAREN expr RPAREN LBRACE block RBRACE
#line 249 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1763 "./IW7/compiler_parser.cpp"
    break;

  case 54: // stmt_if: IF LPAREN expr RPAREN stmt
#line 251 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1772 "./IW7/compiler_parser.cpp"
    break;

  case 55: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE LBRACE block RBRACE
#line 259 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>("", std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[5].value.as < gsc::block_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1778 "./IW7/compiler_parser.cpp"
    break;

  case 56: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE block RBRACE
#line 261 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[4].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>("", std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(blk), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1787 "./IW7/compiler_parser.cpp"
    break;

  case 57: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE stmt
#line 266 "IW7.parser.ypp"
                { 
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>("", std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::block_ptr > ()), std::move(blk)); }
#line 1796 "./IW7/compiler_parser.cpp"
    break;

  case 58: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt
#line 271 "IW7.parser.ypp"
                {
			auto blk1 = std::make_unique<gsc::node_block>("");
			blk1->stmts.push_back(std::move(yystack_[2].value.as < gsc::stmt_ptr > ()));
			auto blk2 = std::make_unique<gsc::node_block>("");
			blk2->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(blk1), std::move(blk2)); }
#line 1807 "./IW7/compiler_parser.cpp"
    break;

  case 59: // stmt_while: WHILE LPAREN expr RPAREN LBRACE block RBRACE
#line 281 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1813 "./IW7/compiler_parser.cpp"
    break;

  case 60: // stmt_while: WHILE LPAREN expr RPAREN stmt
#line 283 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1822 "./IW7/compiler_parser.cpp"
    break;

  case 61: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE block RBRACE
#line 291 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>("", std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1828 "./IW7/compiler_parser.cpp"
    break;

  case 62: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt
#line 293 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>("", std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1838 "./IW7/compiler_parser.cpp"
    break;

  case 63: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE block RBRACE
#line 302 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>("", std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1844 "./IW7/compiler_parser.cpp"
    break;

  case 64: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt
#line 304 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>("");
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1854 "./IW7/compiler_parser.cpp"
    break;

  case 65: // stmt_switch: SWITCH LPAREN expr RPAREN LBRACE block RBRACE
#line 313 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_switch_ptr > () = std::make_unique<gsc::node_stmt_switch>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1860 "./IW7/compiler_parser.cpp"
    break;

  case 66: // stmt_case: CASE data_integer COLON
#line 318 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>("", gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::integer_ptr > ()))); }
#line 1866 "./IW7/compiler_parser.cpp"
    break;

  case 67: // stmt_case: CASE data_string COLON
#line 320 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>("", gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::string_ptr > ()))); }
#line 1872 "./IW7/compiler_parser.cpp"
    break;

  case 68: // stmt_default: DEFAULT COLON
#line 325 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_default_ptr > () = std::make_unique<gsc::node_stmt_default>(""); }
#line 1878 "./IW7/compiler_parser.cpp"
    break;

  case 69: // stmt_break: BREAK SEMICOLON
#line 330 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_break_ptr > () = std::make_unique<gsc::node_stmt_break>(""); }
#line 1884 "./IW7/compiler_parser.cpp"
    break;

  case 70: // stmt_continue: CONTINUE SEMICOLON
#line 334 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_continue_ptr > () = std::make_unique<gsc::node_stmt_continue>(""); }
#line 1890 "./IW7/compiler_parser.cpp"
    break;

  case 71: // stmt_return: RETURN expr SEMICOLON
#line 339 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>("", std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 1896 "./IW7/compiler_parser.cpp"
    break;

  case 72: // stmt_return: RETURN SEMICOLON
#line 341 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>("", std::make_unique<gsc::node>()); }
#line 1902 "./IW7/compiler_parser.cpp"
    break;

  case 73: // for_assign: expr_assign
#line 345 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_assign_ptr > ()); }
#line 1908 "./IW7/compiler_parser.cpp"
    break;

  case 74: // for_assign: %empty
#line 346 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1914 "./IW7/compiler_parser.cpp"
    break;

  case 75: // for_cond: expr_cmp
#line 350 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1920 "./IW7/compiler_parser.cpp"
    break;

  case 76: // for_cond: %empty
#line 351 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1926 "./IW7/compiler_parser.cpp"
    break;

  case 77: // expr: expr_cmp
#line 355 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1932 "./IW7/compiler_parser.cpp"
    break;

  case 78: // expr: expr_ternary
#line 356 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1938 "./IW7/compiler_parser.cpp"
    break;

  case 79: // expr: expr_binary
#line 357 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1944 "./IW7/compiler_parser.cpp"
    break;

  case 80: // expr: expr_primitive
#line 358 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1950 "./IW7/compiler_parser.cpp"
    break;

  case 81: // expr_assign: object INCREMENT
#line 362 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_increment>("", std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1956 "./IW7/compiler_parser.cpp"
    break;

  case 82: // expr_assign: object DECREMENT
#line 363 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_decrement>("", std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1962 "./IW7/compiler_parser.cpp"
    break;

  case 83: // expr_assign: object ASSIGN expr
#line 364 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_equal>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1968 "./IW7/compiler_parser.cpp"
    break;

  case 84: // expr_assign: object ASSIGN_BITWISE_OR expr
#line 365 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_or>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1974 "./IW7/compiler_parser.cpp"
    break;

  case 85: // expr_assign: object ASSIGN_BITWISE_AND expr
#line 366 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_and>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1980 "./IW7/compiler_parser.cpp"
    break;

  case 86: // expr_assign: object ASSIGN_BITWISE_EXOR expr
#line 367 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_exor>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1986 "./IW7/compiler_parser.cpp"
    break;

  case 87: // expr_assign: object ASSIGN_LSHIFT expr
#line 368 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_left>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()),std::move( yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1992 "./IW7/compiler_parser.cpp"
    break;

  case 88: // expr_assign: object ASSIGN_RSHIFT expr
#line 369 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_right>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1998 "./IW7/compiler_parser.cpp"
    break;

  case 89: // expr_assign: object ASSIGN_ADD expr
#line 370 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_add>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2004 "./IW7/compiler_parser.cpp"
    break;

  case 90: // expr_assign: object ASSIGN_SUB expr
#line 371 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_sub>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2010 "./IW7/compiler_parser.cpp"
    break;

  case 91: // expr_assign: object ASSIGN_MULT expr
#line 372 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mult>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2016 "./IW7/compiler_parser.cpp"
    break;

  case 92: // expr_assign: object ASSIGN_DIV expr
#line 373 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_div>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2022 "./IW7/compiler_parser.cpp"
    break;

  case 93: // expr_assign: object ASSIGN_MOD expr
#line 374 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mod>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2028 "./IW7/compiler_parser.cpp"
    break;

  case 94: // expr_cmp: expr OR expr
#line 378 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_or>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2034 "./IW7/compiler_parser.cpp"
    break;

  case 95: // expr_cmp: expr AND expr
#line 379 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_and>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2040 "./IW7/compiler_parser.cpp"
    break;

  case 96: // expr_cmp: expr EQUALITY expr
#line 380 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_equality>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2046 "./IW7/compiler_parser.cpp"
    break;

  case 97: // expr_cmp: expr INEQUALITY expr
#line 381 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_inequality>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2052 "./IW7/compiler_parser.cpp"
    break;

  case 98: // expr_cmp: expr LESS_EQUAL expr
#line 382 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less_equal>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2058 "./IW7/compiler_parser.cpp"
    break;

  case 99: // expr_cmp: expr GREATER_EQUAL expr
#line 383 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater_equal>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2064 "./IW7/compiler_parser.cpp"
    break;

  case 100: // expr_cmp: expr LESS expr
#line 384 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2070 "./IW7/compiler_parser.cpp"
    break;

  case 101: // expr_cmp: expr GREATER expr
#line 385 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2076 "./IW7/compiler_parser.cpp"
    break;

  case 102: // expr_ternary: expr_cmp QMARK expr COLON expr
#line 389 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_ternary>("", std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2082 "./IW7/compiler_parser.cpp"
    break;

  case 103: // expr_binary: expr BITWISE_OR expr
#line 393 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_or>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2088 "./IW7/compiler_parser.cpp"
    break;

  case 104: // expr_binary: expr BITWISE_AND expr
#line 394 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_and>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2094 "./IW7/compiler_parser.cpp"
    break;

  case 105: // expr_binary: expr BITWISE_EXOR expr
#line 395 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_exor>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2100 "./IW7/compiler_parser.cpp"
    break;

  case 106: // expr_binary: expr LSHIFT expr
#line 396 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_left>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2106 "./IW7/compiler_parser.cpp"
    break;

  case 107: // expr_binary: expr RSHIFT expr
#line 397 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_right>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2112 "./IW7/compiler_parser.cpp"
    break;

  case 108: // expr_binary: expr ADD expr
#line 398 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_add>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2118 "./IW7/compiler_parser.cpp"
    break;

  case 109: // expr_binary: expr SUB expr
#line 399 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_sub>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2124 "./IW7/compiler_parser.cpp"
    break;

  case 110: // expr_binary: expr MULT expr
#line 400 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mult>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2130 "./IW7/compiler_parser.cpp"
    break;

  case 111: // expr_binary: expr DIV expr
#line 401 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_div>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2136 "./IW7/compiler_parser.cpp"
    break;

  case 112: // expr_binary: expr MOD expr
#line 402 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mod>("", std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2142 "./IW7/compiler_parser.cpp"
    break;

  case 113: // expr_primitive: LPAREN expr RPAREN
#line 406 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[1].value.as < gsc::expr_ptr > ()); }
#line 2148 "./IW7/compiler_parser.cpp"
    break;

  case 114: // expr_primitive: COMPLEMENT expr
#line 407 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_complement>("", std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2154 "./IW7/compiler_parser.cpp"
    break;

  case 115: // expr_primitive: NOT expr
#line 408 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_not>("", std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2160 "./IW7/compiler_parser.cpp"
    break;

  case 116: // expr_primitive: expr_call
#line 409 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2166 "./IW7/compiler_parser.cpp"
    break;

  case 117: // expr_primitive: expr_call_thread
#line 410 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2172 "./IW7/compiler_parser.cpp"
    break;

  case 118: // expr_primitive: expr_function_ref
#line 411 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2178 "./IW7/compiler_parser.cpp"
    break;

  case 119: // expr_primitive: expr_array
#line 412 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2184 "./IW7/compiler_parser.cpp"
    break;

  case 120: // expr_primitive: expr_field
#line 413 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2190 "./IW7/compiler_parser.cpp"
    break;

  case 121: // expr_primitive: expr_size
#line 414 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2196 "./IW7/compiler_parser.cpp"
    break;

  case 122: // expr_primitive: expr_vector
#line 415 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2202 "./IW7/compiler_parser.cpp"
    break;

  case 123: // expr_primitive: expr_add_array
#line 416 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2208 "./IW7/compiler_parser.cpp"
    break;

  case 124: // expr_primitive: vector
#line 417 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2214 "./IW7/compiler_parser.cpp"
    break;

  case 125: // expr_primitive: num
#line 418 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2220 "./IW7/compiler_parser.cpp"
    break;

  case 126: // expr_primitive: data_localized_string
#line 419 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::localized_string_ptr > ()); }
#line 2226 "./IW7/compiler_parser.cpp"
    break;

  case 127: // expr_primitive: data_string
#line 420 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::string_ptr > ()); }
#line 2232 "./IW7/compiler_parser.cpp"
    break;

  case 128: // expr_primitive: identifier
#line 421 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2238 "./IW7/compiler_parser.cpp"
    break;

  case 129: // expr_primitive: empty_array
#line 422 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2244 "./IW7/compiler_parser.cpp"
    break;

  case 130: // expr_primitive: undefined
#line 423 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2250 "./IW7/compiler_parser.cpp"
    break;

  case 131: // expr_primitive: game
#line 424 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2256 "./IW7/compiler_parser.cpp"
    break;

  case 132: // expr_primitive: self
#line 425 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2262 "./IW7/compiler_parser.cpp"
    break;

  case 133: // expr_primitive: anim
#line 426 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2268 "./IW7/compiler_parser.cpp"
    break;

  case 134: // expr_primitive: level
#line 427 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2274 "./IW7/compiler_parser.cpp"
    break;

  case 135: // expr_call: expr_call_function
#line 431 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2280 "./IW7/compiler_parser.cpp"
    break;

  case 136: // expr_call: expr_call_pointer
#line 432 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2286 "./IW7/compiler_parser.cpp"
    break;

  case 137: // expr_call: object expr_call_function
#line 433 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2292 "./IW7/compiler_parser.cpp"
    break;

  case 138: // expr_call: object expr_call_pointer
#line 434 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2298 "./IW7/compiler_parser.cpp"
    break;

  case 139: // expr_call_thread: THREAD expr_call_function
#line 438 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2304 "./IW7/compiler_parser.cpp"
    break;

  case 140: // expr_call_thread: THREAD expr_call_pointer
#line 439 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2310 "./IW7/compiler_parser.cpp"
    break;

  case 141: // expr_call_thread: object THREAD expr_call_function
#line 440 "IW7.parser.ypp"
                                            { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2316 "./IW7/compiler_parser.cpp"
    break;

  case 142: // expr_call_thread: object THREAD expr_call_pointer
#line 441 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>("", true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2322 "./IW7/compiler_parser.cpp"
    break;

  case 143: // expr_call_function: identifier LPAREN expr_arguments RPAREN
#line 446 "IW7.parser.ypp"
                {yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>("", std::make_unique<gsc::node_filepath>("", ""), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2328 "./IW7/compiler_parser.cpp"
    break;

  case 144: // expr_call_function: filepath DOUBLECOLON identifier LPAREN expr_arguments RPAREN
#line 448 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>("", std::move(yystack_[5].value.as < gsc::filepath_ptr > ()), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2334 "./IW7/compiler_parser.cpp"
    break;

  case 145: // expr_call_pointer: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 453 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>("", false, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2340 "./IW7/compiler_parser.cpp"
    break;

  case 146: // expr_call_pointer: CALL LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 455 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>("", true, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2346 "./IW7/compiler_parser.cpp"
    break;

  case 147: // expr_arguments: expr_arguments COMMA expr
#line 460 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ()); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2352 "./IW7/compiler_parser.cpp"
    break;

  case 148: // expr_arguments: expr
#line 462 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(""); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2358 "./IW7/compiler_parser.cpp"
    break;

  case 149: // expr_arguments: %empty
#line 464 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(""); }
#line 2364 "./IW7/compiler_parser.cpp"
    break;

  case 150: // expr_function_ref: DOUBLECOLON identifier
#line 469 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>("", std::make_unique<gsc::node_filepath>("", ""), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2370 "./IW7/compiler_parser.cpp"
    break;

  case 151: // expr_function_ref: filepath DOUBLECOLON identifier
#line 471 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>("", std::move(yystack_[2].value.as < gsc::filepath_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2376 "./IW7/compiler_parser.cpp"
    break;

  case 152: // expr_array: object LBRACKET expr RBRACKET
#line 476 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_array>("", std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2382 "./IW7/compiler_parser.cpp"
    break;

  case 153: // expr_field: object DOT identifier
#line 481 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_field>("", std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2388 "./IW7/compiler_parser.cpp"
    break;

  case 154: // expr_size: object DOT size
#line 486 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_size>("", std::move(yystack_[2].value.as < gsc::node_ptr > ())); }
#line 2394 "./IW7/compiler_parser.cpp"
    break;

  case 155: // expr_vector: LPAREN expr COMMA expr COMMA expr RPAREN
#line 491 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_vector>("", std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2400 "./IW7/compiler_parser.cpp"
    break;

  case 156: // expr_add_array: LBRACKET expr_arguments RBRACKET
#line 496 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_add_array>("", std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2406 "./IW7/compiler_parser.cpp"
    break;

  case 157: // object: expr_call
#line 500 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2412 "./IW7/compiler_parser.cpp"
    break;

  case 158: // object: expr_array
#line 501 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2418 "./IW7/compiler_parser.cpp"
    break;

  case 159: // object: expr_field
#line 502 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2424 "./IW7/compiler_parser.cpp"
    break;

  case 160: // object: identifier
#line 503 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2430 "./IW7/compiler_parser.cpp"
    break;

  case 161: // object: level
#line 504 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2436 "./IW7/compiler_parser.cpp"
    break;

  case 162: // object: anim
#line 505 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2442 "./IW7/compiler_parser.cpp"
    break;

  case 163: // object: self
#line 506 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2448 "./IW7/compiler_parser.cpp"
    break;

  case 164: // object: game
#line 507 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2454 "./IW7/compiler_parser.cpp"
    break;

  case 165: // vector: LPAREN num COMMA num COMMA num RPAREN
#line 512 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_vector>("", std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2460 "./IW7/compiler_parser.cpp"
    break;

  case 166: // num: data_float
#line 516 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::float_ptr > ()); }
#line 2466 "./IW7/compiler_parser.cpp"
    break;

  case 167: // num: data_integer
#line 517 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::integer_ptr > ()); }
#line 2472 "./IW7/compiler_parser.cpp"
    break;

  case 168: // num: false
#line 518 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2478 "./IW7/compiler_parser.cpp"
    break;

  case 169: // num: true
#line 519 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2484 "./IW7/compiler_parser.cpp"
    break;

  case 170: // false: FALSE
#line 522 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>("", "0"); }
#line 2490 "./IW7/compiler_parser.cpp"
    break;

  case 171: // true: TRUE
#line 523 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>("", "1"); }
#line 2496 "./IW7/compiler_parser.cpp"
    break;

  case 172: // data_float: FLOAT
#line 524 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::float_ptr > () = std::make_unique<gsc::node_float>("", yystack_[0].value.as < std::string > ()); }
#line 2502 "./IW7/compiler_parser.cpp"
    break;

  case 173: // data_integer: INTEGER
#line 525 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::integer_ptr > () = std::make_unique<gsc::node_integer>("", yystack_[0].value.as < std::string > ()); }
#line 2508 "./IW7/compiler_parser.cpp"
    break;

  case 174: // data_localized_string: STRING_LOC
#line 526 "IW7.parser.ypp"
                                   { yylhs.value.as < gsc::localized_string_ptr > () = std::make_unique<gsc::node_localized_string>("", yystack_[0].value.as < std::string > ()); }
#line 2514 "./IW7/compiler_parser.cpp"
    break;

  case 175: // data_string: STRING
#line 527 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::string_ptr > () = std::make_unique<gsc::node_string>("", yystack_[0].value.as < std::string > ()); }
#line 2520 "./IW7/compiler_parser.cpp"
    break;

  case 176: // identifier: IDENTIFIER
#line 528 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::identifier_ptr > () = std::make_unique<gsc::node_identifier>("", yystack_[0].value.as < std::string > ()); }
#line 2526 "./IW7/compiler_parser.cpp"
    break;

  case 177: // filepath: FILEPATH
#line 529 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::filepath_ptr > () = std::make_unique<gsc::node_filepath>("", yystack_[0].value.as < std::string > ()); }
#line 2532 "./IW7/compiler_parser.cpp"
    break;

  case 178: // empty_array: EMPTY_ARRAY
#line 530 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_empty_array>(""); }
#line 2538 "./IW7/compiler_parser.cpp"
    break;

  case 179: // undefined: UNDEFINED
#line 531 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_undefined>(""); }
#line 2544 "./IW7/compiler_parser.cpp"
    break;

  case 180: // size: SIZE
#line 532 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_size>(""); }
#line 2550 "./IW7/compiler_parser.cpp"
    break;

  case 181: // game: GAME
#line 533 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_game>(""); }
#line 2556 "./IW7/compiler_parser.cpp"
    break;

  case 182: // self: SELF
#line 534 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_self>(""); }
#line 2562 "./IW7/compiler_parser.cpp"
    break;

  case 183: // anim: ANIM
#line 535 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_anim>(""); }
#line 2568 "./IW7/compiler_parser.cpp"
    break;

  case 184: // level: LEVEL
#line 536 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_level>(""); }
#line 2574 "./IW7/compiler_parser.cpp"
    break;


#line 2578 "./IW7/compiler_parser.cpp"

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
  "WAITTILL", "WAITTILLMATCH", "WAITTILLFRAMEEND", "ENDON", "NOTIFY", "IN",
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


  const short parser::yypact_ninf_ = -267;

  const short parser::yytable_ninf_ = -165;

  const short
  parser::yypact_[] =
  {
      10,   -68,   -15,    -7,  -267,    30,    10,  -267,  -267,  -267,
    -267,     2,  -267,   -10,   -40,   -40,  -267,  -267,  -267,  -267,
    -267,   -37,  -267,  -267,    17,    27,    20,  -267,    26,    42,
      41,   -37,  -267,  -267,  1477,  -267,    71,    80,   -20,    50,
      68,    82,    90,   113,   107,  1487,   -14,   114,   -26,   109,
    -267,  -267,  -267,  -267,   116,   966,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,   112,   115,   124,  -267,
    -267,  -267,  -267,   562,   123,   118,  -267,  -267,  -267,  -267,
    1510,  1510,  -267,   130,   131,  -267,  -267,   418,  1510,  1510,
    -267,  -267,  -267,  -267,  -267,  1510,  1579,   -37,  -267,  1510,
    1510,  -267,  -267,  2218,   132,  -267,  -267,  -267,    -1,  -267,
    -267,    15,    31,  -267,  -267,  -267,    59,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,     1,   133,  -267,  -267,    85,
      91,   105,   128,  -267,  -267,   123,   120,  1510,   135,  -267,
    1510,  -267,  -267,  -267,  -267,  -267,   -14,   142,   146,   147,
     148,  1579,   -37,  -267,  -267,  1510,  1510,  1510,  1510,  1510,
    1510,  1510,  1510,  1510,  1510,  1510,  -267,  -267,  1510,   -37,
    1746,  1777,  -267,  -267,   143,  -267,  -267,  1585,   637,  1808,
    1631,   149,  1579,  2249,    11,  -267,  2249,  2249,  -267,  1510,
    1510,  1510,  1510,  1510,  1510,  1510,  1510,  1510,  1510,  1510,
    1510,  1510,  1510,  1510,  1510,  1510,  1510,  1510,    -6,   -37,
    1510,  1839,  -267,  2001,  -267,  -267,  1510,  1510,  1510,  1510,
    2039,  -267,  2249,  2249,  2249,  2249,  2249,  2249,  2249,  2249,
    2249,  2249,  2249,    33,   154,   225,   155,  1510,  1510,  1001,
    -267,  1510,    58,  2001,  -267,  1510,  2249,  2249,  2249,  2249,
    2249,  2249,  2249,  2249,  2249,  2249,  2249,  2249,  2249,  2249,
    2249,  2249,  2249,  2249,  2185,  -267,  -267,   154,  2077,   150,
     151,  1673,  2114,  1870,  1715,  -267,  -267,  1510,  1477,   186,
    1477,   152,  2249,    83,  1901,  1477,  -267,  2151,   157,  2249,
    1510,   156,  -267,   164,   158,  1510,  1510,   159,   161,  1510,
      63,  1053,  1087,  1131,   418,  1165,  1209,  1510,    58,  2249,
     167,  1510,  -267,    64,  1932,  -267,  -267,    78,  -267,   203,
    1477,  -267,  -267,   175,  1477,  -267,  -267,  1963,   176,  1510,
      96,   168,   169,   170,  1243,  1287,  1321,  1365,  -267,  -267,
     100,  -267,  -267,  -267,  -267,  1477,  -267,  -267,  1477,  -267,
    -267,  -267,  1399,  1443,  -267,  -267
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,   176,     0,     2,     8,     9,    10,
      11,     0,   177,     0,     0,     0,     1,     4,     5,     6,
       7,    18,    12,   175,     0,     0,     0,    17,     0,     0,
       0,     0,    13,    14,    21,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     181,   184,   183,   182,     0,     0,    20,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,   157,     0,   135,
     136,   158,   159,     0,   160,     0,   164,   163,   162,   161,
       0,     0,   173,     0,     0,    68,    69,    74,     0,     0,
      70,   179,   171,   170,   178,     0,   149,     0,    72,     0,
       0,   174,   172,     0,    77,    78,    79,    80,   116,   117,
     118,   119,   120,   121,   122,   123,     0,   124,   125,   168,
     169,   166,   167,   126,   127,   128,     0,   129,   130,   131,
     132,   133,   134,   139,   140,     0,     0,     0,     0,    52,
       0,    15,    19,    43,    41,    42,     0,     0,     0,     0,
       0,     0,     0,    81,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   137,   138,   149,     0,
       0,     0,    66,    67,     0,    73,   157,     0,     0,     0,
       0,   125,   149,   148,     0,   150,   115,   114,    71,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,     0,   141,   142,     0,     0,     0,     0,
       0,   153,    83,    89,    90,    91,    92,    93,    84,    85,
      86,    87,    88,     0,     0,     0,     0,    76,     0,     0,
     113,     0,     0,   148,   156,     0,   112,   106,   107,    94,
      95,    96,    97,    98,    99,   100,   101,   103,   104,   105,
     108,   109,   110,   111,     0,   180,   154,   151,     0,     0,
       0,     0,     0,     0,     0,   152,   143,   149,    21,    54,
      21,     0,     0,    77,     0,    21,    60,     0,     0,   147,
       0,     0,    47,     0,     0,   149,     0,     0,     0,   149,
       0,     0,     0,     0,    74,     0,     0,     0,     0,   102,
       0,   149,    50,     0,     0,    44,    46,     0,   144,    53,
      21,    58,    65,     0,    21,    64,    59,     0,     0,   149,
       0,     0,     0,     0,     0,     0,     0,     0,   155,   165,
       0,   145,    49,    51,    45,    21,    57,    56,    21,    62,
      63,   146,     0,     0,    55,    61
  };

  const short
  parser::yypgoto_[] =
  {
    -267,  -267,  -267,   210,   211,   214,   217,  -267,  -266,   -44,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,   -90,
    -267,   739,   -92,   -19,  -267,  -267,  -267,    76,   512,   -38,
     -36,  -171,  -267,   129,   166,  -267,  -267,  -267,   244,  -267,
     -45,  -267,  -267,  -267,   189,  -267,    12,     0,    38,  -267,
    -267,  -267,   305,   391,   428,   506
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,     9,    10,    26,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,   184,
     291,   193,    76,   114,   115,   116,   117,   118,   119,    79,
      80,   194,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   276,   139,   140,   141,   142
  };

  const short
  parser::yytable_[] =
  {
      11,   102,   103,   148,    47,   185,    11,   243,   143,   147,
     144,   152,    12,     1,     2,     3,  -157,  -157,  -160,  -160,
      14,    27,   311,   275,   313,    54,    24,    25,    15,   316,
      16,    35,  -158,  -158,    84,    22,   178,    21,  -157,    13,
    -160,  -157,    23,  -160,     4,   176,   145,   177,  -159,  -159,
      94,   254,   255,    28,  -158,    84,    30,  -158,   112,    92,
     191,    31,    23,    29,   345,    92,    12,     4,   347,   286,
    -159,    32,    85,  -159,   255,     4,   156,    47,    34,  -157,
    -157,  -160,  -160,   145,    85,   102,   103,    33,   176,   362,
     177,     4,   363,    85,    95,  -158,  -158,    84,   161,   328,
     341,   218,  -164,  -164,   255,   255,    90,   195,  -163,  -163,
      77,  -159,  -159,    96,   343,    91,   310,    97,   224,   255,
     225,    85,  -162,  -162,  -164,    98,   145,  -164,   -75,   217,
    -163,    77,   351,  -163,   323,    85,   361,   255,   327,    12,
       4,   255,   112,    92,  -162,  -161,  -161,  -162,    99,   176,
     340,   177,   100,   146,   149,   150,   145,   153,   178,   220,
     154,   179,   231,    81,    85,  -164,  -164,  -161,   350,   155,
    -161,  -163,  -163,   186,   182,   183,   219,   226,   217,   244,
     222,   227,   228,   229,    81,  -162,  -162,   145,   247,   287,
     252,   303,   290,   312,    85,   302,   320,   314,   318,   321,
      82,   289,   339,   322,   325,   296,   326,   298,  -161,  -161,
     344,   346,   349,   352,   353,   354,    17,    18,   231,   277,
      19,    82,   185,    20,   333,    85,    81,    93,   293,     0,
       0,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    84,     0,    49,     0,    84,
       0,     0,     0,     0,     0,    50,    51,    52,    53,     0,
       0,     0,   288,    82,    54,     0,     0,   152,   331,   152,
       0,   335,   152,   338,     0,     0,     0,     0,    83,     0,
       0,     0,     0,    85,     0,     0,     0,    85,    84,     0,
      84,     0,     0,     0,     0,    84,     0,     0,     0,    83,
     356,   152,   359,   152,     0,    12,     4,     0,     0,     0,
       0,    84,    84,    84,    84,    84,    84,     0,   152,   152,
       0,    77,     0,     0,     0,    77,    85,     0,    85,     0,
      84,     0,     0,    85,    84,     0,     0,     0,     0,    86,
       0,   187,     0,     0,    84,    84,    84,    84,     0,    85,
      85,    85,    85,    85,    85,    84,     0,     0,    84,     0,
      86,     0,    84,    84,    77,     0,    77,     0,    85,     0,
       0,    77,    85,     0,    81,     0,     0,     0,    81,     0,
       0,     0,    85,    85,    85,    85,     0,    77,    77,    77,
     186,    77,    77,    85,     0,     0,    85,     0,     0,     0,
      85,    85,    86,     0,     0,     0,    77,     0,     0,     0,
      77,    82,     0,     0,     0,    82,     0,    81,     0,    81,
      77,    77,    77,    77,    81,    87,     0,     0,     0,     0,
       0,    77,     0,     0,    77,     0,    47,     0,    77,    77,
      81,    81,    81,    81,    81,    81,    87,     0,    50,    51,
      52,    53,     0,     0,    82,     0,    82,    54,     0,    81,
       0,    82,    88,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81,    81,    81,    81,    82,    82,    82,
      82,    82,    82,    88,    81,     0,     0,    81,    87,    83,
       0,    81,    81,    83,     0,     0,    82,     0,    12,     4,
      82,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,    82,    82,    82,     0,     0,     0,     0,     0,     0,
       0,    82,     0,     0,    82,    88,     0,     0,    82,    82,
       0,     0,    83,     0,    83,     0,     0,     0,     0,    83,
      89,     0,     0,     0,     0,     0,    78,     0,     0,     0,
      86,     0,     0,     0,    86,    83,    83,    83,   187,    83,
      83,    89,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,    83,     0,     0,     0,    83,   156,
      47,     0,   157,   158,     0,   159,   160,     0,    83,    83,
      83,    83,     0,    86,     0,    86,     0,     0,     0,    83,
      86,   161,    83,    89,   162,     0,    83,    83,     0,     0,
     163,   164,     0,     0,     0,     0,    86,    86,    86,    86,
      86,    86,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,     0,     0,    86,    87,     0,     0,    86,
      87,     0,    12,     4,     0,     0,     0,     0,     0,    86,
      86,    86,    86,     0,     0,     0,     0,     0,     0,     0,
      86,     0,   248,    86,     0,     0,     0,    86,    86,     0,
       0,     0,     0,    88,     0,     0,     0,    88,     0,    87,
       0,    87,     0,     0,   199,     0,    87,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,     0,     0,     0,
       0,     0,    87,    87,    87,    87,    87,    87,   210,   211,
     212,   213,   214,   215,   216,     0,    88,     0,    88,     0,
       0,    87,     0,    88,     0,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    87,    87,    87,    87,    88,
      88,    88,    88,    88,    88,     0,    87,     0,     0,    87,
       0,    89,     0,    87,    87,    89,     0,    78,    88,     0,
       0,    78,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    88,    88,    88,    88,     0,     0,     0,     0,
       0,     0,     0,    88,   113,     0,    88,     0,     0,     0,
      88,    88,     0,     0,    89,     0,    89,     0,     0,     0,
      78,    89,    78,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    89,    89,
      89,    89,    89,    78,    78,    78,     0,    78,    78,   180,
     181,     0,     0,     0,     0,     0,    89,   188,   189,     0,
      89,     0,    78,     0,   190,     0,    78,     0,   196,   197,
      89,    89,    89,    89,     0,     0,    78,    78,    78,    78,
       0,    89,     0,     0,    89,     0,     0,    78,    89,    89,
      78,     0,     0,     0,    78,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   221,     0,     0,   223,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     230,     0,     0,     0,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   253,     0,     0,     0,     0,     0,     0,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,     0,     0,   278,
       0,     0,     0,     0,     0,   281,   282,   283,   284,     0,
       0,     0,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,   292,   294,    49,     0,
     297,     0,     0,     0,   299,     0,    50,    51,    52,    53,
       0,     0,     0,     0,   151,    54,     0,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,     0,     0,     0,   295,   319,
      54,     0,     0,     0,     0,   324,    12,     4,     0,     0,
       0,     0,     0,     0,     0,     0,   337,     0,     0,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,     0,    49,     0,     0,     0,     0,
       0,    12,     4,    50,    51,    52,    53,     0,     0,     0,
       0,   329,    54,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     0,     0,    49,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
      53,     0,     0,     0,   330,     0,    54,     0,     0,     0,
       0,     0,     0,    12,     4,     0,     0,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,     0,     0,    12,     4,   332,
      54,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     0,     0,    49,     0,     0,
       0,     0,     0,     0,     0,    50,    51,    52,    53,     0,
       0,     0,     0,   334,    54,     0,     0,     0,     0,     0,
       0,    12,     4,     0,     0,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,    50,
      51,    52,    53,     0,     0,    12,     4,   336,    54,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,     0,     0,     0,
     355,     0,    54,     0,     0,     0,     0,     0,     0,    12,
       4,     0,     0,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     0,     0,    49,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
      53,     0,     0,    12,     4,   357,    54,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,     0,     0,     0,   358,     0,
      54,     0,     0,     0,     0,     0,     0,    12,     4,     0,
       0,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     0,     0,    49,     0,     0,
       0,     0,     0,     0,     0,    50,    51,    52,    53,     0,
       0,    12,     4,   360,    54,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,    50,
      51,    52,    53,     0,     0,     0,     0,   364,    54,     0,
       0,     0,     0,     0,     0,    12,     4,     0,     0,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,     0,     0,    12,
       4,   365,    54,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     0,     0,    49,
       0,     0,     0,     0,    46,    47,     0,    50,    51,    52,
      53,     0,     0,   101,   102,   103,    54,    50,    51,    52,
      53,   104,   105,    12,     4,     0,   106,    46,    47,     0,
     107,     0,   108,     0,     0,     0,   101,   102,   103,     0,
      50,    51,    52,    53,   104,   105,     0,     0,     0,   106,
       0,     0,     0,   107,     0,     0,     0,    12,     4,     0,
       0,     0,     0,     0,     0,   109,   110,    12,     4,    23,
     111,   112,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   109,   110,
      12,     4,    23,   111,   112,    92,    46,    47,     0,     0,
       0,     0,     0,    47,     0,   101,   102,   103,     0,    50,
      51,    52,    53,   104,   105,     0,     0,     0,   192,     0,
       0,     0,   107,     0,   161,     0,     0,   162,     0,     0,
       0,     0,     0,   163,   164,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,     0,   109,   110,    12,
       4,    23,   111,   112,    92,    12,     4,   250,     0,     0,
       0,     0,   251,     0,     0,     0,     0,     0,   199,     0,
       0,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   210,   211,   212,   213,   214,   215,   216,   304,
       0,     0,     0,     0,   305,     0,     0,     0,     0,     0,
     199,     0,     0,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   210,   211,   212,   213,   214,   215,
     216,   308,     0,     0,     0,     0,   309,     0,     0,     0,
       0,     0,   199,     0,     0,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,   245,     0,     0,     0,   210,   211,   212,   213,
     214,   215,   216,   199,     0,     0,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,     0,     0,     0,     0,
       0,     0,     0,   246,     0,     0,     0,   210,   211,   212,
     213,   214,   215,   216,   199,     0,     0,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,     0,     0,     0,
       0,     0,     0,     0,   249,     0,     0,     0,   210,   211,
     212,   213,   214,   215,   216,   199,     0,     0,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,     0,     0,
       0,     0,     0,     0,     0,   279,     0,     0,     0,   210,
     211,   212,   213,   214,   215,   216,   199,     0,     0,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,     0,
       0,     0,     0,     0,     0,     0,   307,     0,     0,     0,
     210,   211,   212,   213,   214,   215,   216,   199,     0,     0,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
       0,     0,     0,     0,     0,     0,     0,   315,     0,     0,
       0,   210,   211,   212,   213,   214,   215,   216,   199,     0,
       0,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,   342,     0,
       0,     0,   210,   211,   212,   213,   214,   215,   216,   199,
       0,     0,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,     0,     0,     0,     0,     0,     0,     0,   348,
       0,     0,     0,   210,   211,   212,   213,   214,   215,   216,
     199,     0,     0,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   210,   211,   212,   213,   214,   215,
     216,   280,     0,     0,     0,     0,     0,     0,   199,     0,
       0,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   210,   211,   212,   213,   214,   215,   216,   285,
       0,     0,     0,     0,     0,     0,   199,     0,     0,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     210,   211,   212,   213,   214,   215,   216,   301,     0,     0,
       0,     0,     0,     0,   199,     0,     0,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   210,   211,
     212,   213,   214,   215,   216,   306,     0,     0,     0,     0,
       0,   199,     0,     0,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   210,   211,   212,   213,   214,
     215,   216,   317,     0,     0,     0,     0,     0,   199,     0,
       0,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   210,   211,   212,   213,   214,   215,   216,   300,
       0,     0,   199,     0,     0,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   210,   211,   212,   213,
     214,   215,   216,   198,     0,   199,     0,     0,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   210,
     211,   212,   213,   214,   215,   216,   199,     0,     0,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     210,   211,   212,   213,   214,   215,   216
  };

  const short
  parser::yycheck_[] =
  {
       0,    27,    28,    48,    18,    97,     6,   178,    46,    35,
      46,    55,    80,     3,     4,     5,    17,    18,    17,    18,
      35,    21,   288,    29,   290,    39,    14,    15,    35,   295,
       0,    31,    17,    18,    34,    45,    35,    35,    39,     1,
      39,    42,    82,    42,    81,    83,    46,    83,    17,    18,
      38,    40,    41,    36,    39,    55,    36,    42,    84,    85,
     105,    41,    82,    36,   330,    85,    80,    81,   334,    36,
      39,    45,    34,    42,    41,    81,    17,    18,    37,    80,
      81,    80,    81,    83,    46,    27,    28,    45,   126,   355,
     126,    81,   358,    55,    44,    80,    81,    97,    39,    36,
      36,    42,    17,    18,    41,    41,    35,   107,    17,    18,
      34,    80,    81,    45,    36,    35,   287,    35,   156,    41,
     156,    83,    17,    18,    39,    35,   126,    42,    45,    46,
      39,    55,    36,    42,   305,    97,    36,    41,   309,    80,
      81,    41,    84,    85,    39,    17,    18,    42,    35,   187,
     321,   187,    45,    39,    45,    39,   156,    45,    35,    39,
      45,    43,   162,    34,   126,    80,    81,    39,   339,    45,
      42,    80,    81,    97,    44,    44,    43,    35,    46,   179,
      45,    35,    35,    35,    55,    80,    81,   187,    45,    35,
      41,    40,    37,     7,   156,    45,    40,    45,    41,    35,
      34,   245,    35,    45,    45,   249,    45,   252,    80,    81,
       7,    36,    36,    45,    45,    45,     6,     6,   218,   219,
       6,    55,   314,     6,   314,   187,    97,    38,   247,    -1,
      -1,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,   245,    -1,    22,    -1,   249,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    37,    97,    39,    -1,    -1,   311,   312,   313,
      -1,   315,   316,   318,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,   245,    -1,    -1,    -1,   249,   288,    -1,
     290,    -1,    -1,    -1,    -1,   295,    -1,    -1,    -1,    55,
     344,   345,   346,   347,    -1,    80,    81,    -1,    -1,    -1,
      -1,   311,   312,   313,   314,   315,   316,    -1,   362,   363,
      -1,   245,    -1,    -1,    -1,   249,   288,    -1,   290,    -1,
     330,    -1,    -1,   295,   334,    -1,    -1,    -1,    -1,    34,
      -1,    97,    -1,    -1,   344,   345,   346,   347,    -1,   311,
     312,   313,   314,   315,   316,   355,    -1,    -1,   358,    -1,
      55,    -1,   362,   363,   288,    -1,   290,    -1,   330,    -1,
      -1,   295,   334,    -1,   245,    -1,    -1,    -1,   249,    -1,
      -1,    -1,   344,   345,   346,   347,    -1,   311,   312,   313,
     314,   315,   316,   355,    -1,    -1,   358,    -1,    -1,    -1,
     362,   363,    97,    -1,    -1,    -1,   330,    -1,    -1,    -1,
     334,   245,    -1,    -1,    -1,   249,    -1,   288,    -1,   290,
     344,   345,   346,   347,   295,    34,    -1,    -1,    -1,    -1,
      -1,   355,    -1,    -1,   358,    -1,    18,    -1,   362,   363,
     311,   312,   313,   314,   315,   316,    55,    -1,    30,    31,
      32,    33,    -1,    -1,   288,    -1,   290,    39,    -1,   330,
      -1,   295,    34,   334,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   344,   345,   346,   347,   311,   312,   313,
     314,   315,   316,    55,   355,    -1,    -1,   358,    97,   245,
      -1,   362,   363,   249,    -1,    -1,   330,    -1,    80,    81,
     334,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     344,   345,   346,   347,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   355,    -1,    -1,   358,    97,    -1,    -1,   362,   363,
      -1,    -1,   288,    -1,   290,    -1,    -1,    -1,    -1,   295,
      34,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
     245,    -1,    -1,    -1,   249,   311,   312,   313,   314,   315,
     316,    55,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,   330,    -1,    -1,    -1,   334,    17,
      18,    -1,    20,    21,    -1,    23,    24,    -1,   344,   345,
     346,   347,    -1,   288,    -1,   290,    -1,    -1,    -1,   355,
     295,    39,   358,    97,    42,    -1,   362,   363,    -1,    -1,
      48,    49,    -1,    -1,    -1,    -1,   311,   312,   313,   314,
     315,   316,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,   330,   245,    -1,    -1,   334,
     249,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,   344,
     345,   346,   347,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     355,    -1,    25,   358,    -1,    -1,    -1,   362,   363,    -1,
      -1,    -1,    -1,   245,    -1,    -1,    -1,   249,    -1,   288,
      -1,   290,    -1,    -1,    47,    -1,   295,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,   311,   312,   313,   314,   315,   316,    71,    72,
      73,    74,    75,    76,    77,    -1,   288,    -1,   290,    -1,
      -1,   330,    -1,   295,    -1,   334,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   344,   345,   346,   347,   311,
     312,   313,   314,   315,   316,    -1,   355,    -1,    -1,   358,
      -1,   245,    -1,   362,   363,   249,    -1,   245,   330,    -1,
      -1,   249,   334,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   344,   345,   346,   347,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   355,    45,    -1,   358,    -1,    -1,    -1,
     362,   363,    -1,    -1,   288,    -1,   290,    -1,    -1,    -1,
     288,   295,   290,    -1,    -1,    -1,    -1,   295,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   311,   312,   313,
     314,   315,   316,   311,   312,   313,    -1,   315,   316,    90,
      91,    -1,    -1,    -1,    -1,    -1,   330,    98,    99,    -1,
     334,    -1,   330,    -1,   105,    -1,   334,    -1,   109,   110,
     344,   345,   346,   347,    -1,    -1,   344,   345,   346,   347,
      -1,   355,    -1,    -1,   358,    -1,    -1,   355,   362,   363,
     358,    -1,    -1,    -1,   362,   363,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   147,    -1,    -1,   150,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     161,    -1,    -1,    -1,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,    -1,    -1,   220,
      -1,    -1,    -1,    -1,    -1,   226,   227,   228,   229,    -1,
      -1,    -1,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,   247,   248,    22,    -1,
     251,    -1,    -1,    -1,   255,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    38,    39,    -1,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    37,   300,
      39,    -1,    -1,    -1,    -1,   306,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   317,    -1,    -1,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    80,    81,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    38,    39,     6,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    37,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    -1,    -1,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    80,    81,    38,
      39,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    -1,    -1,     6,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    80,    81,    38,    39,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      37,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      81,    -1,    -1,     6,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    80,    81,    38,    39,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    37,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    -1,
      -1,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    80,    81,    38,    39,     6,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    81,    -1,    -1,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    80,
      81,    38,    39,     6,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    17,    18,    -1,    30,    31,    32,
      33,    -1,    -1,    26,    27,    28,    39,    30,    31,    32,
      33,    34,    35,    80,    81,    -1,    39,    17,    18,    -1,
      43,    -1,    45,    -1,    -1,    -1,    26,    27,    28,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    80,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,
      83,    84,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      80,    81,    82,    83,    84,    85,    17,    18,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    26,    27,    28,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    43,    -1,    39,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    -1,    78,    79,    80,
      81,    82,    83,    84,    85,    80,    81,    36,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    36,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    47,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    47,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    47,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    47,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    47,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      47,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    41,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    41,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    44,
      -1,    -1,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    45,    -1,    47,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    47,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,    81,    88,    89,    90,    91,    92,
      93,   144,    80,   145,    35,    35,     0,    90,    91,    92,
      93,    35,    45,    82,   143,   143,    94,   144,    36,    36,
      36,    41,    45,    45,    37,   144,     6,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    22,
      30,    31,    32,    33,    39,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   119,   124,   125,   126,
     127,   130,   131,   135,   144,   145,   149,   150,   151,   152,
      35,    35,    85,   141,   143,    44,    45,    35,    35,    35,
      45,    26,    27,    28,    34,    35,    39,    43,    45,    78,
      79,    83,    84,   118,   120,   121,   122,   123,   124,   125,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   149,
     150,   151,   152,   126,   127,   144,    39,    35,   137,    45,
      39,    38,    96,    45,    45,    45,    17,    20,    21,    23,
      24,    39,    42,    48,    49,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,   126,   127,    35,    43,
     118,   118,    44,    44,   116,   119,   124,   135,   118,   118,
     118,   137,    39,   118,   128,   144,   118,   118,    45,    47,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      71,    72,    73,    74,    75,    76,    77,    46,    42,    43,
      39,   118,    45,   118,   126,   127,    35,    35,    35,    35,
     118,   144,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   128,   144,    36,    36,    45,    25,    36,
      36,    41,    41,   118,    40,    41,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,    29,   148,   144,   118,    36,
      40,   118,   118,   118,   118,    40,    36,    35,    37,    96,
      37,   117,   118,   120,   118,    37,    96,   118,   137,   118,
      44,    40,    45,    40,    36,    41,    41,    36,    36,    41,
     128,    95,     7,    95,    45,    36,    95,    41,    41,   118,
      40,    35,    45,   128,   118,    45,    45,   128,    36,    38,
      37,    96,    38,   116,    38,    96,    38,   118,   137,    35,
     128,    36,    36,    36,     7,    95,    36,    95,    36,    36,
     128,    36,    45,    45,    45,    37,    96,    38,    37,    96,
      38,    36,    95,    95,    38,    38
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
     123,   123,   123,   123,   123,   124,   124,   124,   124,   125,
     125,   125,   125,   126,   126,   127,   127,   128,   128,   128,
     129,   129,   130,   131,   132,   133,   134,   135,   135,   135,
     135,   135,   135,   135,   135,   136,   137,   137,   137,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152
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
       2,     3,     3,     4,     6,     8,     9,     3,     1,     0,
       2,     3,     4,     3,     3,     7,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     7,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   116,   116,   117,   121,   123,   125,   127,   129,   131,
     133,   135,   140,   145,   150,   155,   160,   162,   165,   169,
     171,   174,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   200,   202,   207,   212,   217,   219,   224,   226,   231,
     233,   238,   243,   248,   250,   258,   260,   265,   270,   280,
     282,   290,   292,   301,   303,   312,   317,   319,   324,   329,
     333,   338,   340,   345,   346,   350,   351,   355,   356,   357,
     358,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   378,   379,   380,   381,   382,   383,
     384,   385,   389,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   431,   432,   433,   434,   438,
     439,   440,   441,   445,   447,   452,   454,   459,   461,   464,
     468,   470,   475,   480,   485,   490,   495,   500,   501,   502,
     503,   504,   505,   506,   507,   511,   516,   517,   518,   519,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536
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


#line 13 "IW7.parser.ypp"
} //  IW7 
#line 3786 "./IW7/compiler_parser.cpp"

#line 538 "IW7.parser.ypp"


void IW7::parser::error(const std::string& msg)
{
    GSC_COMP_ERROR("%s", msg.data());
}
