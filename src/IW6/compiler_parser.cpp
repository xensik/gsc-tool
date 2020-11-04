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
      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< block_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.YY_MOVE_OR_COPY< expr_arguments_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.YY_MOVE_OR_COPY< expr_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.YY_MOVE_OR_COPY< expr_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.YY_MOVE_OR_COPY< expr_call_type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_filepath: // filepath
        value.YY_MOVE_OR_COPY< filepath_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_float: // data_float
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

      case symbol_kind::S_data_integer: // data_integer
        value.YY_MOVE_OR_COPY< integer_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.YY_MOVE_OR_COPY< localized_string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
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
        value.YY_MOVE_OR_COPY< node_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
        value.YY_MOVE_OR_COPY< parameters_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.YY_MOVE_OR_COPY< script_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
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

      case symbol_kind::S_data_string: // data_string
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
      case symbol_kind::S_block: // block
        value.move< block_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.move< expr_arguments_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< expr_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.move< expr_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.move< expr_call_type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_filepath: // filepath
        value.move< filepath_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_float: // data_float
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

      case symbol_kind::S_data_integer: // data_integer
        value.move< integer_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.move< localized_string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
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
        value.move< node_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
        value.move< parameters_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< script_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
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

      case symbol_kind::S_data_string: // data_string
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
      case symbol_kind::S_block: // block
        value.copy< block_ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.copy< expr_arguments_ptr > (that.value);
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.copy< expr_assign_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.copy< expr_call_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.copy< expr_call_type_ptr > (that.value);
        break;

      case symbol_kind::S_filepath: // filepath
        value.copy< filepath_ptr > (that.value);
        break;

      case symbol_kind::S_data_float: // data_float
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

      case symbol_kind::S_data_integer: // data_integer
        value.copy< integer_ptr > (that.value);
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.copy< localized_string_ptr > (that.value);
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
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
        value.copy< node_ptr > (that.value);
        break;

      case symbol_kind::S_parameters: // parameters
        value.copy< parameters_ptr > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.copy< script_ptr > (that.value);
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
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

      case symbol_kind::S_data_string: // data_string
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
      case symbol_kind::S_block: // block
        value.move< block_ptr > (that.value);
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.move< expr_arguments_ptr > (that.value);
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< expr_assign_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.move< expr_call_ptr > (that.value);
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.move< expr_call_type_ptr > (that.value);
        break;

      case symbol_kind::S_filepath: // filepath
        value.move< filepath_ptr > (that.value);
        break;

      case symbol_kind::S_data_float: // data_float
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

      case symbol_kind::S_data_integer: // data_integer
        value.move< integer_ptr > (that.value);
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.move< localized_string_ptr > (that.value);
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
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
        value.move< node_ptr > (that.value);
        break;

      case symbol_kind::S_parameters: // parameters
        value.move< parameters_ptr > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.move< script_ptr > (that.value);
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
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

      case symbol_kind::S_data_string: // data_string
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
      case symbol_kind::S_block: // block
        yylhs.value.emplace< block_ptr > ();
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        yylhs.value.emplace< expr_arguments_ptr > ();
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        yylhs.value.emplace< expr_assign_ptr > ();
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        yylhs.value.emplace< expr_call_ptr > ();
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        yylhs.value.emplace< expr_call_type_ptr > ();
        break;

      case symbol_kind::S_filepath: // filepath
        yylhs.value.emplace< filepath_ptr > ();
        break;

      case symbol_kind::S_data_float: // data_float
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

      case symbol_kind::S_data_integer: // data_integer
        yylhs.value.emplace< integer_ptr > ();
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        yylhs.value.emplace< localized_string_ptr > ();
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
      case symbol_kind::S_expr_function_ref: // expr_function_ref
      case symbol_kind::S_expr_array: // expr_array
      case symbol_kind::S_expr_field: // expr_field
      case symbol_kind::S_expr_size: // expr_size
      case symbol_kind::S_expr_vector: // expr_vector
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
        yylhs.value.emplace< node_ptr > ();
        break;

      case symbol_kind::S_parameters: // parameters
        yylhs.value.emplace< parameters_ptr > ();
        break;

      case symbol_kind::S_script: // script
        yylhs.value.emplace< script_ptr > ();
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
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

      case symbol_kind::S_data_string: // data_string
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
#line 112 "iw6.parser.ypp"
                 { astout = std::move(yystack_[0].value.as < script_ptr > ()); }
#line 1435 "./IW6/compiler_parser.cpp"
    break;

  case 3: // root: %empty
#line 113 "iw6.parser.ypp"
                 { astout = std::make_unique<node_script>(); }
#line 1441 "./IW6/compiler_parser.cpp"
    break;

  case 4: // script: script include
#line 118 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::move(yystack_[1].value.as < script_ptr > ()); yylhs.value.as < script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ())); }
#line 1447 "./IW6/compiler_parser.cpp"
    break;

  case 5: // script: script using_animtree
#line 120 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::move(yystack_[1].value.as < script_ptr > ()); yylhs.value.as < script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < using_animtree_ptr > ())); }
#line 1453 "./IW6/compiler_parser.cpp"
    break;

  case 6: // script: script animtree
#line 122 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::move(yystack_[1].value.as < script_ptr > ()); yylhs.value.as < script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < using_animtree_ptr > ())); }
#line 1459 "./IW6/compiler_parser.cpp"
    break;

  case 7: // script: script function
#line 124 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::move(yystack_[1].value.as < script_ptr > ()); yylhs.value.as < script_ptr > ()->functions.push_back(std::move(yystack_[0].value.as < function_ptr > ())); }
#line 1465 "./IW6/compiler_parser.cpp"
    break;

  case 8: // script: include
#line 126 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::make_unique<node_script>(); yylhs.value.as < script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < include_ptr > ()));}
#line 1471 "./IW6/compiler_parser.cpp"
    break;

  case 9: // script: using_animtree
#line 128 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::make_unique<node_script>(); yylhs.value.as < script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < using_animtree_ptr > ()));}
#line 1477 "./IW6/compiler_parser.cpp"
    break;

  case 10: // script: animtree
#line 130 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::make_unique<node_script>(); yylhs.value.as < script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < using_animtree_ptr > ()));}
#line 1483 "./IW6/compiler_parser.cpp"
    break;

  case 11: // script: function
#line 132 "iw6.parser.ypp"
                { yylhs.value.as < script_ptr > () = std::make_unique<node_script>(); yylhs.value.as < script_ptr > ()->functions.push_back(std::move(yystack_[0].value.as < function_ptr > ()));}
#line 1489 "./IW6/compiler_parser.cpp"
    break;

  case 12: // include: INCLUDE filepath SEMICOLON
#line 137 "iw6.parser.ypp"
                { yylhs.value.as < include_ptr > () = std::make_unique<node_include>(std::move(yystack_[1].value.as < filepath_ptr > ())); }
#line 1495 "./IW6/compiler_parser.cpp"
    break;

  case 13: // using_animtree: USING_ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 142 "iw6.parser.ypp"
                { yylhs.value.as < using_animtree_ptr > () = std::make_unique<node_using_animtree>(std::move(yystack_[2].value.as < string_ptr > ())); }
#line 1501 "./IW6/compiler_parser.cpp"
    break;

  case 14: // animtree: ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 147 "iw6.parser.ypp"
                { yylhs.value.as < using_animtree_ptr > () = std::make_unique<node_using_animtree>(std::move(yystack_[2].value.as < string_ptr > ())); }
#line 1507 "./IW6/compiler_parser.cpp"
    break;

  case 15: // function: identifier LPAREN parameters RPAREN LBRACE block RBRACE
#line 152 "iw6.parser.ypp"
                { yylhs.value.as < function_ptr > () = std::make_unique<node_function>(std::move(yystack_[6].value.as < identifier_ptr > ()), std::move(yystack_[4].value.as < parameters_ptr > ()), std::move(yystack_[1].value.as < block_ptr > ())); }
#line 1513 "./IW6/compiler_parser.cpp"
    break;

  case 16: // parameters: parameters COMMA identifier
#line 157 "iw6.parser.ypp"
                { yylhs.value.as < parameters_ptr > () = std::move(yystack_[2].value.as < parameters_ptr > ()); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 1519 "./IW6/compiler_parser.cpp"
    break;

  case 17: // parameters: identifier
#line 159 "iw6.parser.ypp"
                { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(); yylhs.value.as < parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 1525 "./IW6/compiler_parser.cpp"
    break;

  case 18: // parameters: %empty
#line 161 "iw6.parser.ypp"
                { yylhs.value.as < parameters_ptr > () = std::make_unique<node_parameters>(); }
#line 1531 "./IW6/compiler_parser.cpp"
    break;

  case 19: // block: block stmt
#line 166 "iw6.parser.ypp"
                { yylhs.value.as < block_ptr > () = std::move(yystack_[1].value.as < block_ptr > ()); yylhs.value.as < block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 1537 "./IW6/compiler_parser.cpp"
    break;

  case 20: // block: stmt
#line 168 "iw6.parser.ypp"
                { yylhs.value.as < block_ptr > () = std::make_unique<node_block>(); yylhs.value.as < block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < stmt_ptr > ())); }
#line 1543 "./IW6/compiler_parser.cpp"
    break;

  case 21: // block: %empty
#line 170 "iw6.parser.ypp"
                { yylhs.value.as < block_ptr > () = std::make_unique<node_block>(); }
#line 1549 "./IW6/compiler_parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 174 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_call = std::move(yystack_[0].value.as < stmt_call_ptr > ()); }
#line 1555 "./IW6/compiler_parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 175 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < stmt_assign_ptr > ()); }
#line 1561 "./IW6/compiler_parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 176 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < stmt_endon_ptr > ()); }
#line 1567 "./IW6/compiler_parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 177 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < stmt_notify_ptr > ()); }
#line 1573 "./IW6/compiler_parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 178 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < stmt_wait_ptr > ()); }
#line 1579 "./IW6/compiler_parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 179 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < stmt_waittill_ptr > ()); }
#line 1585 "./IW6/compiler_parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 180 "iw6.parser.ypp"
                                                                        { yylhs.value.as < stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < stmt_waittillmatch_ptr > ()); }
#line 1591 "./IW6/compiler_parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 181 "iw6.parser.ypp"
                                                                        { yylhs.value.as < stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < stmt_waittillframeend_ptr > ()); }
#line 1597 "./IW6/compiler_parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 182 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < stmt_ptr > ().as_if = std::move(yystack_[0].value.as < stmt_if_ptr > ()); }
#line 1603 "./IW6/compiler_parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 183 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < stmt_ifelse_ptr > ()); }
#line 1609 "./IW6/compiler_parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 184 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_while = std::move(yystack_[0].value.as < stmt_while_ptr > ()); }
#line 1615 "./IW6/compiler_parser.cpp"
    break;

  case 33: // stmt: stmt_for
#line 185 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < stmt_ptr > ().as_for = std::move(yystack_[0].value.as < stmt_for_ptr > ()); }
#line 1621 "./IW6/compiler_parser.cpp"
    break;

  case 34: // stmt: stmt_foreach
#line 186 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < stmt_foreach_ptr > ()); }
#line 1627 "./IW6/compiler_parser.cpp"
    break;

  case 35: // stmt: stmt_switch
#line 187 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < stmt_switch_ptr > ()); }
#line 1633 "./IW6/compiler_parser.cpp"
    break;

  case 36: // stmt: stmt_case
#line 188 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < stmt_ptr > ().as_case = std::move(yystack_[0].value.as < stmt_case_ptr > ()); }
#line 1639 "./IW6/compiler_parser.cpp"
    break;

  case 37: // stmt: stmt_default
#line 189 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_default = std::move(yystack_[0].value.as < stmt_default_ptr > ()); }
#line 1645 "./IW6/compiler_parser.cpp"
    break;

  case 38: // stmt: stmt_break
#line 190 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_break = std::move(yystack_[0].value.as < stmt_break_ptr > ()); }
#line 1651 "./IW6/compiler_parser.cpp"
    break;

  case 39: // stmt: stmt_continue
#line 191 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < stmt_continue_ptr > ()); }
#line 1657 "./IW6/compiler_parser.cpp"
    break;

  case 40: // stmt: stmt_return
#line 192 "iw6.parser.ypp"
                                                                                { yylhs.value.as < stmt_ptr > ().as_return = std::move(yystack_[0].value.as < stmt_return_ptr > ()); }
#line 1663 "./IW6/compiler_parser.cpp"
    break;

  case 41: // stmt_call: expr_call SEMICOLON
#line 197 "iw6.parser.ypp"
                { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 1669 "./IW6/compiler_parser.cpp"
    break;

  case 42: // stmt_call: expr_call_thread SEMICOLON
#line 199 "iw6.parser.ypp"
                { yylhs.value.as < stmt_call_ptr > () = std::make_unique<node_stmt_call>(std::move(yystack_[1].value.as < expr_call_ptr > ())); }
#line 1675 "./IW6/compiler_parser.cpp"
    break;

  case 43: // stmt_assign: expr_assign SEMICOLON
#line 204 "iw6.parser.ypp"
                { yylhs.value.as < stmt_assign_ptr > () = std::make_unique<node_stmt_assign>(std::move(yystack_[1].value.as < expr_assign_ptr > ())); }
#line 1681 "./IW6/compiler_parser.cpp"
    break;

  case 44: // stmt_endon: object ENDON LPAREN expr RPAREN SEMICOLON
#line 209 "iw6.parser.ypp"
                { yylhs.value.as < stmt_endon_ptr > () = std::make_unique<node_stmt_endon>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ())); }
#line 1687 "./IW6/compiler_parser.cpp"
    break;

  case 45: // stmt_notify: object NOTIFY LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 214 "iw6.parser.ypp"
                { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 1693 "./IW6/compiler_parser.cpp"
    break;

  case 46: // stmt_notify: object NOTIFY LPAREN expr RPAREN SEMICOLON
#line 216 "iw6.parser.ypp"
                { yylhs.value.as < stmt_notify_ptr > () = std::make_unique<node_stmt_notify>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::make_unique<node_expr_arguments>()); }
#line 1699 "./IW6/compiler_parser.cpp"
    break;

  case 47: // stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON
#line 221 "iw6.parser.ypp"
                { yylhs.value.as < stmt_wait_ptr > () = std::make_unique<node_stmt_wait>(std::move(yystack_[2].value.as < node_ptr > ())); }
#line 1705 "./IW6/compiler_parser.cpp"
    break;

  case 48: // stmt_wait: WAIT num SEMICOLON
#line 223 "iw6.parser.ypp"
                { yylhs.value.as < stmt_wait_ptr > () = std::make_unique<node_stmt_wait>(std::move(yystack_[1].value.as < node_ptr > ())); }
#line 1711 "./IW6/compiler_parser.cpp"
    break;

  case 49: // stmt_waittill: object WAITTILL LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 228 "iw6.parser.ypp"
                { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < expr_arguments_ptr > ())); }
#line 1717 "./IW6/compiler_parser.cpp"
    break;

  case 50: // stmt_waittill: object WAITTILL LPAREN expr RPAREN SEMICOLON
#line 230 "iw6.parser.ypp"
                { yylhs.value.as < stmt_waittill_ptr > () = std::make_unique<node_stmt_waittill>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::make_unique<node_expr_arguments>()); }
#line 1723 "./IW6/compiler_parser.cpp"
    break;

  case 51: // stmt_waittillmatch: object WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON
#line 235 "iw6.parser.ypp"
                { yylhs.value.as < stmt_waittillmatch_ptr > () = std::make_unique<node_stmt_waittillmatch>(std::move(yystack_[7].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ())); }
#line 1729 "./IW6/compiler_parser.cpp"
    break;

  case 52: // stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON
#line 240 "iw6.parser.ypp"
                { yylhs.value.as < stmt_waittillframeend_ptr > () = std::make_unique<node_stmt_waittillframeend>(); }
#line 1735 "./IW6/compiler_parser.cpp"
    break;

  case 53: // stmt_if: IF LPAREN expr RPAREN LBRACE block RBRACE
#line 245 "iw6.parser.ypp"
                { yylhs.value.as < stmt_if_ptr > () = std::make_unique<node_stmt_if>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < block_ptr > ())); }
#line 1741 "./IW6/compiler_parser.cpp"
    break;

  case 54: // stmt_if: IF LPAREN expr RPAREN stmt
#line 247 "iw6.parser.ypp"
                { yylhs.value.as < stmt_if_ptr > () = std::make_unique<node_stmt_if>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1747 "./IW6/compiler_parser.cpp"
    break;

  case 55: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE LBRACE block RBRACE
#line 252 "iw6.parser.ypp"
                { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[8].value.as < node_ptr > ()), std::move(yystack_[5].value.as < block_ptr > ()), std::move(yystack_[1].value.as < block_ptr > ())); }
#line 1753 "./IW6/compiler_parser.cpp"
    break;

  case 56: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE block RBRACE
#line 254 "iw6.parser.ypp"
                { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[4].value.as < stmt_ptr > ().as_node), std::move(yystack_[1].value.as < block_ptr > ())); }
#line 1759 "./IW6/compiler_parser.cpp"
    break;

  case 57: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE stmt
#line 256 "iw6.parser.ypp"
                { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[3].value.as < block_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1765 "./IW6/compiler_parser.cpp"
    break;

  case 58: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt
#line 258 "iw6.parser.ypp"
                { yylhs.value.as < stmt_ifelse_ptr > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < stmt_ptr > ().as_node), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1771 "./IW6/compiler_parser.cpp"
    break;

  case 59: // stmt_while: WHILE LPAREN expr RPAREN LBRACE block RBRACE
#line 263 "iw6.parser.ypp"
                { yylhs.value.as < stmt_while_ptr > () = std::make_unique<node_stmt_while>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < block_ptr > ())); }
#line 1777 "./IW6/compiler_parser.cpp"
    break;

  case 60: // stmt_while: WHILE LPAREN expr RPAREN stmt
#line 265 "iw6.parser.ypp"
                { yylhs.value.as < stmt_while_ptr > () = std::make_unique<node_stmt_while>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1783 "./IW6/compiler_parser.cpp"
    break;

  case 61: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE block RBRACE
#line 270 "iw6.parser.ypp"
                { yylhs.value.as < stmt_for_ptr > () = std::make_unique<node_stmt_for>(std::move(yystack_[8].value.as < node_ptr > ()), std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < block_ptr > ())); }
#line 1789 "./IW6/compiler_parser.cpp"
    break;

  case 62: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt
#line 272 "iw6.parser.ypp"
                { yylhs.value.as < stmt_for_ptr > () = std::make_unique< node_stmt_for>(std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1795 "./IW6/compiler_parser.cpp"
    break;

  case 63: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE block RBRACE
#line 277 "iw6.parser.ypp"
                { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(std::move(yystack_[6].value.as < node_ptr > ()), std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < block_ptr > ())); }
#line 1801 "./IW6/compiler_parser.cpp"
    break;

  case 64: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt
#line 279 "iw6.parser.ypp"
                { yylhs.value.as < stmt_foreach_ptr > () = std::make_unique<node_stmt_foreach>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < stmt_ptr > ().as_node)); }
#line 1807 "./IW6/compiler_parser.cpp"
    break;

  case 65: // stmt_switch: SWITCH LPAREN expr RPAREN LBRACE block RBRACE
#line 284 "iw6.parser.ypp"
                { yylhs.value.as < stmt_switch_ptr > () = std::make_unique<node_stmt_switch>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[1].value.as < block_ptr > ())); }
#line 1813 "./IW6/compiler_parser.cpp"
    break;

  case 66: // stmt_case: CASE data_integer COLON
#line 289 "iw6.parser.ypp"
                { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(std::move(yystack_[1].value.as < integer_ptr > ())); }
#line 1819 "./IW6/compiler_parser.cpp"
    break;

  case 67: // stmt_case: CASE data_string COLON
#line 291 "iw6.parser.ypp"
                { yylhs.value.as < stmt_case_ptr > () = std::make_unique<node_stmt_case>(std::move(yystack_[1].value.as < string_ptr > ())); }
#line 1825 "./IW6/compiler_parser.cpp"
    break;

  case 68: // stmt_default: DEFAULT COLON
#line 296 "iw6.parser.ypp"
                { yylhs.value.as < stmt_default_ptr > () = std::make_unique<node_stmt_default>(); }
#line 1831 "./IW6/compiler_parser.cpp"
    break;

  case 69: // stmt_break: BREAK SEMICOLON
#line 301 "iw6.parser.ypp"
                { yylhs.value.as < stmt_break_ptr > () = std::make_unique<node_stmt_break>(); }
#line 1837 "./IW6/compiler_parser.cpp"
    break;

  case 70: // stmt_continue: CONTINUE SEMICOLON
#line 305 "iw6.parser.ypp"
                { yylhs.value.as < stmt_continue_ptr > () = std::make_unique<node_stmt_continue>(); }
#line 1843 "./IW6/compiler_parser.cpp"
    break;

  case 71: // stmt_return: RETURN expr SEMICOLON
#line 310 "iw6.parser.ypp"
                { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(std::move(yystack_[1].value.as < node_ptr > ())); }
#line 1849 "./IW6/compiler_parser.cpp"
    break;

  case 72: // stmt_return: RETURN SEMICOLON
#line 312 "iw6.parser.ypp"
                { yylhs.value.as < stmt_return_ptr > () = std::make_unique<node_stmt_return>(std::make_unique<node>()); }
#line 1855 "./IW6/compiler_parser.cpp"
    break;

  case 73: // for_assign: expr_assign
#line 316 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_assign_ptr > ()); }
#line 1861 "./IW6/compiler_parser.cpp"
    break;

  case 74: // for_assign: %empty
#line 317 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node>(); }
#line 1867 "./IW6/compiler_parser.cpp"
    break;

  case 75: // for_cond: expr_cmp
#line 321 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1873 "./IW6/compiler_parser.cpp"
    break;

  case 76: // for_cond: %empty
#line 322 "iw6.parser.ypp"
                                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node>(); }
#line 1879 "./IW6/compiler_parser.cpp"
    break;

  case 77: // expr: expr_cmp
#line 326 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1885 "./IW6/compiler_parser.cpp"
    break;

  case 78: // expr: expr_ternary
#line 327 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1891 "./IW6/compiler_parser.cpp"
    break;

  case 79: // expr: expr_binary
#line 328 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1897 "./IW6/compiler_parser.cpp"
    break;

  case 80: // expr: expr_primitive
#line 329 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 1903 "./IW6/compiler_parser.cpp"
    break;

  case 81: // expr_assign: object INCREMENT
#line 333 "iw6.parser.ypp"
                                                                { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_increment>(std::move(yystack_[1].value.as < node_ptr > ())); }
#line 1909 "./IW6/compiler_parser.cpp"
    break;

  case 82: // expr_assign: object DECREMENT
#line 334 "iw6.parser.ypp"
                                                                { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_decrement>(std::move(yystack_[1].value.as < node_ptr > ())); }
#line 1915 "./IW6/compiler_parser.cpp"
    break;

  case 83: // expr_assign: object ASSIGN expr
#line 335 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_equal>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1921 "./IW6/compiler_parser.cpp"
    break;

  case 84: // expr_assign: object ASSIGN_BITWISE_OR expr
#line 336 "iw6.parser.ypp"
                                                { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_or>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1927 "./IW6/compiler_parser.cpp"
    break;

  case 85: // expr_assign: object ASSIGN_BITWISE_AND expr
#line 337 "iw6.parser.ypp"
                                                { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_and>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1933 "./IW6/compiler_parser.cpp"
    break;

  case 86: // expr_assign: object ASSIGN_BITWISE_EXOR expr
#line 338 "iw6.parser.ypp"
                                                { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_bitwise_exor>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1939 "./IW6/compiler_parser.cpp"
    break;

  case 87: // expr_assign: object ASSIGN_LSHIFT expr
#line 339 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_left>(std::move(yystack_[2].value.as < node_ptr > ()),std::move( yystack_[0].value.as < node_ptr > ())); }
#line 1945 "./IW6/compiler_parser.cpp"
    break;

  case 88: // expr_assign: object ASSIGN_RSHIFT expr
#line 340 "iw6.parser.ypp"
                                                { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_shift_right>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1951 "./IW6/compiler_parser.cpp"
    break;

  case 89: // expr_assign: object ASSIGN_ADD expr
#line 341 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_add>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1957 "./IW6/compiler_parser.cpp"
    break;

  case 90: // expr_assign: object ASSIGN_SUB expr
#line 342 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_sub>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1963 "./IW6/compiler_parser.cpp"
    break;

  case 91: // expr_assign: object ASSIGN_MULT expr
#line 343 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mult>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1969 "./IW6/compiler_parser.cpp"
    break;

  case 92: // expr_assign: object ASSIGN_DIV expr
#line 344 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_div>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1975 "./IW6/compiler_parser.cpp"
    break;

  case 93: // expr_assign: object ASSIGN_MOD expr
#line 345 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_assign_ptr > () = std::make_unique<node_expr_assign_mod>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1981 "./IW6/compiler_parser.cpp"
    break;

  case 94: // expr_cmp: expr OR expr
#line 349 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_or>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1987 "./IW6/compiler_parser.cpp"
    break;

  case 95: // expr_cmp: expr AND expr
#line 350 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_and>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1993 "./IW6/compiler_parser.cpp"
    break;

  case 96: // expr_cmp: expr EQUALITY expr
#line 351 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_equality>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 1999 "./IW6/compiler_parser.cpp"
    break;

  case 97: // expr_cmp: expr INEQUALITY expr
#line 352 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_inequality>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2005 "./IW6/compiler_parser.cpp"
    break;

  case 98: // expr_cmp: expr LESS_EQUAL expr
#line 353 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_less_equal>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2011 "./IW6/compiler_parser.cpp"
    break;

  case 99: // expr_cmp: expr GREATER_EQUAL expr
#line 354 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_greater_equal>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2017 "./IW6/compiler_parser.cpp"
    break;

  case 100: // expr_cmp: expr LESS expr
#line 355 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_less>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2023 "./IW6/compiler_parser.cpp"
    break;

  case 101: // expr_cmp: expr GREATER expr
#line 356 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_greater>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2029 "./IW6/compiler_parser.cpp"
    break;

  case 102: // expr_ternary: expr_cmp QMARK expr COLON expr
#line 360 "iw6.parser.ypp"
                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_ternary>(std::move(yystack_[4].value.as < node_ptr > ()), std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2035 "./IW6/compiler_parser.cpp"
    break;

  case 103: // expr_binary: expr BITWISE_OR expr
#line 364 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_bitwise_or>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2041 "./IW6/compiler_parser.cpp"
    break;

  case 104: // expr_binary: expr BITWISE_AND expr
#line 365 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_bitwise_and>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2047 "./IW6/compiler_parser.cpp"
    break;

  case 105: // expr_binary: expr BITWISE_EXOR expr
#line 366 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_bitwise_exor>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2053 "./IW6/compiler_parser.cpp"
    break;

  case 106: // expr_binary: expr LSHIFT expr
#line 367 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_shift_left>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2059 "./IW6/compiler_parser.cpp"
    break;

  case 107: // expr_binary: expr RSHIFT expr
#line 368 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_shift_right>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2065 "./IW6/compiler_parser.cpp"
    break;

  case 108: // expr_binary: expr ADD expr
#line 369 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_add>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2071 "./IW6/compiler_parser.cpp"
    break;

  case 109: // expr_binary: expr SUB expr
#line 370 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_sub>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2077 "./IW6/compiler_parser.cpp"
    break;

  case 110: // expr_binary: expr MULT expr
#line 371 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_mult>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2083 "./IW6/compiler_parser.cpp"
    break;

  case 111: // expr_binary: expr DIV expr
#line 372 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_div>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2089 "./IW6/compiler_parser.cpp"
    break;

  case 112: // expr_binary: expr MOD expr
#line 373 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_mod>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2095 "./IW6/compiler_parser.cpp"
    break;

  case 113: // expr_primitive: LPAREN expr RPAREN
#line 377 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[1].value.as < node_ptr > ()); }
#line 2101 "./IW6/compiler_parser.cpp"
    break;

  case 114: // expr_primitive: COMPLEMENT expr
#line 378 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_complement>(std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2107 "./IW6/compiler_parser.cpp"
    break;

  case 115: // expr_primitive: NOT expr
#line 379 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_not>(std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2113 "./IW6/compiler_parser.cpp"
    break;

  case 116: // expr_primitive: expr_call
#line 380 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2119 "./IW6/compiler_parser.cpp"
    break;

  case 117: // expr_primitive: expr_call_thread
#line 381 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2125 "./IW6/compiler_parser.cpp"
    break;

  case 118: // expr_primitive: expr_function_ref
#line 382 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2131 "./IW6/compiler_parser.cpp"
    break;

  case 119: // expr_primitive: expr_array
#line 383 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2137 "./IW6/compiler_parser.cpp"
    break;

  case 120: // expr_primitive: expr_field
#line 384 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2143 "./IW6/compiler_parser.cpp"
    break;

  case 121: // expr_primitive: expr_size
#line 385 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2149 "./IW6/compiler_parser.cpp"
    break;

  case 122: // expr_primitive: expr_vector
#line 386 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2155 "./IW6/compiler_parser.cpp"
    break;

  case 123: // expr_primitive: vector
#line 387 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2161 "./IW6/compiler_parser.cpp"
    break;

  case 124: // expr_primitive: num
#line 388 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2167 "./IW6/compiler_parser.cpp"
    break;

  case 125: // expr_primitive: data_localized_string
#line 389 "iw6.parser.ypp"
                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < localized_string_ptr > ()); }
#line 2173 "./IW6/compiler_parser.cpp"
    break;

  case 126: // expr_primitive: data_string
#line 390 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < string_ptr > ()); }
#line 2179 "./IW6/compiler_parser.cpp"
    break;

  case 127: // expr_primitive: identifier
#line 391 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < identifier_ptr > ()); }
#line 2185 "./IW6/compiler_parser.cpp"
    break;

  case 128: // expr_primitive: empty_array
#line 392 "iw6.parser.ypp"
                                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2191 "./IW6/compiler_parser.cpp"
    break;

  case 129: // expr_primitive: undefined
#line 393 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2197 "./IW6/compiler_parser.cpp"
    break;

  case 130: // expr_primitive: game
#line 394 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2203 "./IW6/compiler_parser.cpp"
    break;

  case 131: // expr_primitive: self
#line 395 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2209 "./IW6/compiler_parser.cpp"
    break;

  case 132: // expr_primitive: anim
#line 396 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2215 "./IW6/compiler_parser.cpp"
    break;

  case 133: // expr_primitive: level
#line 397 "iw6.parser.ypp"
                                                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2221 "./IW6/compiler_parser.cpp"
    break;

  case 134: // expr_call: expr_call_function
#line 401 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(false, std::make_unique<node>(), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2227 "./IW6/compiler_parser.cpp"
    break;

  case 135: // expr_call: expr_call_pointer
#line 402 "iw6.parser.ypp"
                                                                { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(false, std::make_unique<node>(), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2233 "./IW6/compiler_parser.cpp"
    break;

  case 136: // expr_call: object expr_call_function
#line 403 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2239 "./IW6/compiler_parser.cpp"
    break;

  case 137: // expr_call: object expr_call_pointer
#line 404 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(false, std::move(yystack_[1].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2245 "./IW6/compiler_parser.cpp"
    break;

  case 138: // expr_call_thread: THREAD expr_call_function
#line 408 "iw6.parser.ypp"
                                                        { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(true, std::make_unique<node>(), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2251 "./IW6/compiler_parser.cpp"
    break;

  case 139: // expr_call_thread: THREAD expr_call_pointer
#line 409 "iw6.parser.ypp"
                                                { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(true, std::make_unique<node>(), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2257 "./IW6/compiler_parser.cpp"
    break;

  case 140: // expr_call_thread: object THREAD expr_call_function
#line 410 "iw6.parser.ypp"
                                            { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2263 "./IW6/compiler_parser.cpp"
    break;

  case 141: // expr_call_thread: object THREAD expr_call_pointer
#line 411 "iw6.parser.ypp"
                                                { yylhs.value.as < expr_call_ptr > () = std::make_unique<node_expr_call>(true, std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < expr_call_type_ptr > ())); }
#line 2269 "./IW6/compiler_parser.cpp"
    break;

  case 142: // expr_call_function: identifier LPAREN expr_arguments RPAREN
#line 416 "iw6.parser.ypp"
                {yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(std::make_unique<node_filepath>(""), std::move(yystack_[3].value.as < identifier_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2275 "./IW6/compiler_parser.cpp"
    break;

  case 143: // expr_call_function: filepath DOUBLECOLON identifier LPAREN expr_arguments RPAREN
#line 418 "iw6.parser.ypp"
                { yylhs.value.as < expr_call_type_ptr > ().as_func = std::make_unique<node_expr_call_function>(std::move(yystack_[5].value.as < filepath_ptr > ()), std::move(yystack_[3].value.as < identifier_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2281 "./IW6/compiler_parser.cpp"
    break;

  case 144: // expr_call_pointer: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 423 "iw6.parser.ypp"
                { yylhs.value.as < expr_call_type_ptr > ().as_pointer = std::make_unique<node_expr_call_pointer>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[1].value.as < expr_arguments_ptr > ())); }
#line 2287 "./IW6/compiler_parser.cpp"
    break;

  case 145: // expr_arguments: expr_arguments COMMA expr
#line 428 "iw6.parser.ypp"
                { yylhs.value.as < expr_arguments_ptr > () = std::move(yystack_[2].value.as < expr_arguments_ptr > ()); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2293 "./IW6/compiler_parser.cpp"
    break;

  case 146: // expr_arguments: expr
#line 430 "iw6.parser.ypp"
                { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(); yylhs.value.as < expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < node_ptr > ())); }
#line 2299 "./IW6/compiler_parser.cpp"
    break;

  case 147: // expr_arguments: %empty
#line 432 "iw6.parser.ypp"
                { yylhs.value.as < expr_arguments_ptr > () = std::make_unique<node_expr_arguments>(); }
#line 2305 "./IW6/compiler_parser.cpp"
    break;

  case 148: // expr_function_ref: DOUBLECOLON identifier
#line 437 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function_ref>(std::make_unique<node_filepath>(""), std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 2311 "./IW6/compiler_parser.cpp"
    break;

  case 149: // expr_function_ref: filepath DOUBLECOLON identifier
#line 439 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_function_ref>(std::move(yystack_[2].value.as < filepath_ptr > ()), std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 2317 "./IW6/compiler_parser.cpp"
    break;

  case 150: // expr_array: object LBRACKET expr RBRACKET
#line 444 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_array>(std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2323 "./IW6/compiler_parser.cpp"
    break;

  case 151: // expr_field: object DOT identifier
#line 449 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_field>(std::move(yystack_[2].value.as < node_ptr > ()), std::move(yystack_[0].value.as < identifier_ptr > ())); }
#line 2329 "./IW6/compiler_parser.cpp"
    break;

  case 152: // expr_size: object DOT size
#line 454 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_size>(std::move(yystack_[2].value.as < node_ptr > ())); }
#line 2335 "./IW6/compiler_parser.cpp"
    break;

  case 153: // expr_vector: LPAREN expr COMMA expr COMMA expr RPAREN
#line 459 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_expr_vector>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2341 "./IW6/compiler_parser.cpp"
    break;

  case 154: // object: expr_call
#line 463 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < expr_call_ptr > ()); }
#line 2347 "./IW6/compiler_parser.cpp"
    break;

  case 155: // object: expr_array
#line 464 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2353 "./IW6/compiler_parser.cpp"
    break;

  case 156: // object: expr_field
#line 465 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2359 "./IW6/compiler_parser.cpp"
    break;

  case 157: // object: identifier
#line 466 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < identifier_ptr > ()); }
#line 2365 "./IW6/compiler_parser.cpp"
    break;

  case 158: // object: level
#line 467 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2371 "./IW6/compiler_parser.cpp"
    break;

  case 159: // object: anim
#line 468 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2377 "./IW6/compiler_parser.cpp"
    break;

  case 160: // object: self
#line 469 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2383 "./IW6/compiler_parser.cpp"
    break;

  case 161: // object: game
#line 470 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2389 "./IW6/compiler_parser.cpp"
    break;

  case 162: // vector: LPAREN num COMMA num COMMA num RPAREN
#line 475 "iw6.parser.ypp"
                { yylhs.value.as < node_ptr > () = std::make_unique<node_vector>(std::move(yystack_[5].value.as < node_ptr > ()), std::move(yystack_[3].value.as < node_ptr > ()), std::move(yystack_[1].value.as < node_ptr > ())); }
#line 2395 "./IW6/compiler_parser.cpp"
    break;

  case 163: // num: data_float
#line 479 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < float_ptr > ()); }
#line 2401 "./IW6/compiler_parser.cpp"
    break;

  case 164: // num: data_integer
#line 480 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < integer_ptr > ()); }
#line 2407 "./IW6/compiler_parser.cpp"
    break;

  case 165: // num: false
#line 481 "iw6.parser.ypp"
                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2413 "./IW6/compiler_parser.cpp"
    break;

  case 166: // num: true
#line 482 "iw6.parser.ypp"
                                                { yylhs.value.as < node_ptr > () = std::move(yystack_[0].value.as < node_ptr > ()); }
#line 2419 "./IW6/compiler_parser.cpp"
    break;

  case 167: // false: FALSE
#line 485 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_integer>("0"); }
#line 2425 "./IW6/compiler_parser.cpp"
    break;

  case 168: // true: TRUE
#line 486 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_integer>("1"); }
#line 2431 "./IW6/compiler_parser.cpp"
    break;

  case 169: // data_float: FLOAT
#line 487 "iw6.parser.ypp"
                                        { yylhs.value.as < float_ptr > () = std::make_unique<node_float>(yystack_[0].value.as < std::string > ()); }
#line 2437 "./IW6/compiler_parser.cpp"
    break;

  case 170: // data_integer: INTEGER
#line 488 "iw6.parser.ypp"
                                { yylhs.value.as < integer_ptr > () = std::make_unique<node_integer>(yystack_[0].value.as < std::string > ()); }
#line 2443 "./IW6/compiler_parser.cpp"
    break;

  case 171: // data_localized_string: STRING_LOC
#line 489 "iw6.parser.ypp"
                                   { yylhs.value.as < localized_string_ptr > () = std::make_unique<node_localized_string>(yystack_[0].value.as < std::string > ()); }
#line 2449 "./IW6/compiler_parser.cpp"
    break;

  case 172: // data_string: STRING
#line 490 "iw6.parser.ypp"
                                { yylhs.value.as < string_ptr > () = std::make_unique<node_string>(yystack_[0].value.as < std::string > ()); }
#line 2455 "./IW6/compiler_parser.cpp"
    break;

  case 173: // identifier: IDENTIFIER
#line 491 "iw6.parser.ypp"
                                { yylhs.value.as < identifier_ptr > () = std::make_unique<node_identifier>(yystack_[0].value.as < std::string > ()); }
#line 2461 "./IW6/compiler_parser.cpp"
    break;

  case 174: // filepath: FILEPATH
#line 492 "iw6.parser.ypp"
                                        { yylhs.value.as < filepath_ptr > () = std::make_unique<node_filepath>(yystack_[0].value.as < std::string > ()); }
#line 2467 "./IW6/compiler_parser.cpp"
    break;

  case 175: // empty_array: EMPTY_ARRAY
#line 493 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::make_unique<node_empty_array>(); }
#line 2473 "./IW6/compiler_parser.cpp"
    break;

  case 176: // undefined: UNDEFINED
#line 494 "iw6.parser.ypp"
                                { yylhs.value.as < node_ptr > () = std::make_unique<node_undefined>(); }
#line 2479 "./IW6/compiler_parser.cpp"
    break;

  case 177: // size: SIZE
#line 495 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_size>(); }
#line 2485 "./IW6/compiler_parser.cpp"
    break;

  case 178: // game: GAME
#line 496 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_game>(); }
#line 2491 "./IW6/compiler_parser.cpp"
    break;

  case 179: // self: SELF
#line 497 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_self>(); }
#line 2497 "./IW6/compiler_parser.cpp"
    break;

  case 180: // anim: ANIM
#line 498 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_anim>(); }
#line 2503 "./IW6/compiler_parser.cpp"
    break;

  case 181: // level: LEVEL
#line 499 "iw6.parser.ypp"
                                        { yylhs.value.as < node_ptr > () = std::make_unique<node_level>(); }
#line 2509 "./IW6/compiler_parser.cpp"
    break;


#line 2513 "./IW6/compiler_parser.cpp"

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
  "using_animtree", "animtree", "function", "parameters", "block", "stmt",
  "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify", "stmt_wait",
  "stmt_waittill", "stmt_waittillmatch", "stmt_waittillframeend",
  "stmt_if", "stmt_ifelse", "stmt_while", "stmt_for", "stmt_foreach",
  "stmt_switch", "stmt_case", "stmt_default", "stmt_break",
  "stmt_continue", "stmt_return", "for_assign", "for_cond", "expr",
  "expr_assign", "expr_cmp", "expr_ternary", "expr_binary",
  "expr_primitive", "expr_call", "expr_call_thread", "expr_call_function",
  "expr_call_pointer", "expr_arguments", "expr_function_ref", "expr_array",
  "expr_field", "expr_size", "expr_vector", "object", "vector", "num",
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


  const short parser::yypact_ninf_ = -269;

  const short parser::yytable_ninf_ = -162;

  const short
  parser::yypact_[] =
  {
       5,   -60,    -6,     1,  -269,    29,     5,  -269,  -269,  -269,
    -269,     4,  -269,    22,   -32,   -32,  -269,  -269,  -269,  -269,
    -269,   -13,  -269,  -269,    46,    48,   -23,  -269,    26,    53,
      64,   -13,  -269,  -269,  1509,  -269,    70,    76,   -54,    73,
      74,    83,    85,    86,    82,   189,   -18,    95,    90,  -269,
    -269,  -269,  -269,    89,  1006,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,    91,    92,   101,  -269,  -269,
    -269,  -269,  1545,    96,   113,  -269,  -269,  -269,  -269,   555,
     555,  -269,   114,   117,  -269,  -269,   118,   555,   555,  -269,
    -269,  -269,  -269,  -269,   555,   -13,  -269,   555,   555,  -269,
    -269,  2182,   136,  -269,  -269,  -269,   -16,  -269,  -269,     7,
       9,  -269,  -269,    15,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,    -1,   121,  -269,  -269,    19,    27,    35,    52,
    -269,  -269,    96,   555,   138,  -269,   555,  -269,  -269,  -269,
    -269,  -269,   -18,   150,   157,   161,   165,  1519,   -13,  -269,
    -269,   555,   555,   555,   555,   555,   555,   555,   555,   555,
     555,   555,  -269,  -269,   555,   -13,  1748,  1779,  -269,  -269,
     146,  -269,  -269,   745,  1591,  1810,  1633,   160,  -269,  2213,
    2213,  -269,   555,   555,   555,   555,   555,   555,   555,   555,
     555,   555,   555,   555,   555,   555,   555,   555,   555,   555,
     555,    -5,   -13,  1841,  -269,  2003,  -269,  -269,   555,   555,
     555,   555,  1519,  2041,  -269,  2213,  2213,  2213,  2213,  2213,
    2213,  2213,  2213,  2213,  2213,  2213,  2213,    93,   168,   156,
     169,   555,   555,  1039,  -269,   555,   -12,  2213,  2213,  2213,
    2213,  2213,  2213,  2213,  2213,  2213,  2213,  2213,  2213,  2213,
    2213,  2213,  2213,  2213,  2213,  2149,  -269,  -269,   168,   163,
     171,  1675,  2078,  1872,  1717,  -269,  -269,   555,   555,  1509,
     197,  1509,   164,  2213,    -3,  1903,  1509,  -269,  2115,   177,
     555,  -269,   190,   181,   555,   555,   184,   185,   555,  2213,
     102,  1091,  1124,  1168,   118,  1201,  1245,   555,   -12,  2213,
     555,  -269,   103,  1934,  -269,  -269,   111,  -269,   223,  1509,
    -269,  -269,   199,  1509,  -269,  -269,  1965,   202,   119,   188,
     198,   200,  1278,  1322,  1355,  1399,  -269,  -269,  -269,  -269,
    -269,  -269,  1509,  -269,  -269,  1509,  -269,  -269,  1432,  1476,
    -269,  -269
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,   173,     0,     2,     8,     9,    10,
      11,     0,   174,     0,     0,     0,     1,     4,     5,     6,
       7,    18,    12,   172,     0,     0,     0,    17,     0,     0,
       0,     0,    13,    14,    21,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   178,
     181,   180,   179,     0,     0,    20,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,   154,     0,   134,   135,
     155,   156,     0,   157,     0,   161,   160,   159,   158,     0,
       0,   170,     0,     0,    68,    69,    74,     0,     0,    70,
     176,   168,   167,   175,     0,     0,    72,     0,     0,   171,
     169,     0,    77,    78,    79,    80,   116,   117,   118,   119,
     120,   121,   122,     0,   123,   124,   165,   166,   163,   164,
     125,   126,   127,     0,   128,   129,   130,   131,   132,   133,
     138,   139,     0,     0,     0,    52,     0,    15,    19,    43,
      41,    42,     0,     0,     0,     0,     0,     0,     0,    81,
      82,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   136,   137,   147,     0,     0,     0,    66,    67,
       0,    73,   154,     0,     0,     0,     0,   124,   148,   115,
     114,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,     0,   140,   141,     0,     0,
       0,     0,     0,     0,   151,    83,    89,    90,    91,    92,
      93,    84,    85,    86,    87,    88,   146,     0,     0,     0,
       0,    76,     0,     0,   113,     0,     0,   112,   106,   107,
      94,    95,    96,    97,    98,    99,   100,   101,   103,   104,
     105,   108,   109,   110,   111,     0,   177,   152,   149,     0,
       0,     0,     0,     0,     0,   150,   142,     0,   147,    21,
      54,    21,     0,     0,    77,     0,    21,    60,     0,     0,
       0,    47,     0,     0,   147,     0,     0,     0,   147,   145,
       0,     0,     0,     0,    74,     0,     0,     0,     0,   102,
     147,    50,     0,     0,    44,    46,     0,   143,    53,    21,
      58,    65,     0,    21,    64,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   153,   162,   144,    49,
      51,    45,    21,    57,    56,    21,    62,    63,     0,     0,
      55,    61
  };

  const short
  parser::yypgoto_[] =
  {
    -269,  -269,  -269,   235,   239,   241,   242,  -269,  -268,   -50,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,   -55,
    -269,   789,   -91,    13,  -269,  -269,  -269,   107,   589,   -43,
     -39,  -186,  -269,   142,   192,  -269,  -269,   273,  -269,   -45,
    -269,  -269,  -269,   212,  -269,    87,     0,    57,  -269,  -269,
    -269,   323,   373,   446,   517
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,     9,    10,    26,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   180,
     282,   236,    75,   112,   113,   114,   115,   116,   117,    78,
      79,   237,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     267,   136,   137,   138,   139
  };

  const short
  parser::yytable_[] =
  {
      11,  -154,   144,   140,   148,   181,    11,   141,     1,     2,
       3,   301,    30,   303,   101,   102,  -157,    31,   306,    12,
      53,    27,  -154,   266,  -155,  -154,  -156,    23,    14,    16,
      91,    35,   152,   174,    83,    15,  -161,  -157,    21,   172,
    -157,   -75,   210,   173,  -160,  -155,   142,  -156,  -155,    23,
    -156,   333,  -159,   157,    83,   335,   211,  -161,    13,   187,
    -161,    12,     4,  -154,  -154,  -160,    22,     4,  -160,  -158,
      32,   110,    91,  -159,   348,     4,  -159,   349,  -157,  -157,
     172,    28,   142,    29,   173,     4,  -155,  -155,  -156,  -156,
    -158,    84,   300,  -158,    12,     4,    83,    33,  -161,  -161,
      34,    24,    25,    84,    89,   188,  -160,  -160,   312,   216,
      90,    84,   316,   217,  -159,  -159,    94,    96,    95,    97,
      98,   101,   102,   142,   328,    93,    99,   146,   276,   143,
     174,  -158,  -158,   277,   145,   149,   150,   317,   329,    84,
     172,    76,   277,   277,   173,   151,   331,    49,    50,    51,
      52,   277,   142,    84,   338,   175,    53,   178,   224,   277,
     179,    76,    36,   212,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,   238,    80,    48,   110,    91,
      84,   210,   214,   142,   218,    49,    50,    51,    52,   280,
     241,   219,   279,   287,    53,   220,    80,    12,     4,   221,
     246,   289,   278,   182,   302,   281,    46,   291,   304,    84,
     292,   224,   268,   181,   100,   101,   102,   308,    49,    50,
      51,    52,   103,   104,   310,   311,    81,    53,   314,   315,
     332,   105,   339,   106,   334,    12,     4,   337,    80,    83,
      84,    17,   340,    83,   341,    18,    81,    19,    20,   322,
      92,   148,   320,   148,   284,   324,   148,     0,     0,     0,
       0,     0,     0,   327,     0,     0,   107,   108,    12,     4,
      23,   109,   110,    91,     0,     0,     0,     0,     0,    83,
       0,    83,   343,   148,   346,   148,    83,     0,    81,     0,
       0,     0,     0,     0,     0,     0,    84,     0,   148,   148,
      84,    83,    83,    83,    83,    83,    83,    82,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    83,
       0,     0,     0,    83,     0,     0,     0,    82,     0,     0,
       0,     0,    83,    83,    83,    83,    84,     0,    84,     0,
       0,     0,    83,    84,     0,    83,    76,     0,    83,    83,
      76,     0,     0,     0,     0,     0,     0,    85,    84,    84,
      84,    84,    84,    84,     0,     0,     0,     0,     0,   183,
       0,     0,     0,     0,     0,     0,    84,    85,     0,     0,
      84,    80,     0,     0,     0,    80,    76,     0,    76,    84,
      84,    84,    84,    76,     0,     0,     0,     0,     0,    84,
       0,     0,    84,     0,     0,    84,    84,    86,    76,    76,
      76,   182,    76,    76,     0,     0,     0,     0,     0,    85,
       0,    80,     0,    80,     0,     0,    76,    86,    80,     0,
      76,    81,     0,     0,     0,    81,     0,     0,     0,    76,
      76,    76,    76,    80,    80,    80,    80,    80,    80,    76,
       0,     0,    76,     0,     0,    76,    76,     0,     0,     0,
       0,    80,     0,     0,     0,    80,     0,     0,     0,    86,
       0,    81,     0,    81,    80,    80,    80,    80,    81,     0,
      87,     0,     0,     0,    80,     0,     0,    80,     0,     0,
      80,    80,     0,    81,    81,    81,    81,    81,    81,     0,
      87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    81,    82,     0,     0,    81,    82,     0,     0,     0,
       0,     0,     0,     0,    81,    81,    81,    81,     0,     0,
       0,     0,     0,     0,    81,     0,     0,    81,     0,     0,
      81,    81,    87,     0,     0,     0,     0,     0,     0,     0,
       0,    88,    82,     0,    82,     0,     0,     0,     0,    82,
       0,     0,    85,     0,     0,     0,    85,     0,     0,     0,
       0,    88,    46,     0,    82,    82,    82,   183,    82,    82,
     100,   101,   102,     0,    49,    50,    51,    52,   103,   104,
       0,     0,    82,    53,     0,     0,    82,   105,     0,     0,
       0,     0,    85,     0,    85,    82,    82,    82,    82,    85,
       0,     0,    86,    88,     0,    82,    86,     0,    82,     0,
       0,    82,    82,    77,    85,    85,    85,    85,    85,    85,
       0,     0,   107,   108,    12,     4,    23,   109,   110,    91,
       0,     0,    85,    77,     0,     0,    85,     0,     0,     0,
       0,     0,    86,     0,    86,    85,    85,    85,    85,    86,
       0,     0,     0,     0,     0,    85,     0,     0,    85,     0,
       0,    85,    85,     0,    86,    86,    86,    86,    86,    86,
       0,     0,     0,     0,     0,    87,     0,     0,     0,    87,
       0,     0,    86,     0,     0,     0,    86,     0,     0,     0,
       0,     0,     0,     0,     0,    86,    86,    86,    86,     0,
       0,     0,     0,     0,     0,    86,     0,     0,    86,     0,
       0,    86,    86,     0,     0,    87,     0,    87,     0,     0,
       0,     0,    87,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    87,    87,    87,
      87,    87,    87,     0,     0,     0,    88,     0,     0,     0,
      88,     0,     0,     0,     0,    87,     0,     0,     0,    87,
       0,     0,     0,     0,     0,     0,     0,     0,    87,    87,
      87,    87,     0,   157,     0,     0,   158,     0,    87,     0,
       0,    87,   159,   160,    87,    87,    88,     0,    88,     0,
       0,     0,     0,    88,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,     0,     0,     0,    88,    88,
      88,    88,    88,    88,    12,     4,     0,     0,    77,     0,
       0,     0,    77,     0,   111,     0,    88,     0,     0,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,    88,
      88,    88,    88,     0,     0,     0,     0,     0,     0,    88,
       0,     0,    88,     0,     0,    88,    88,     0,    77,     0,
      77,     0,     0,     0,     0,    77,     0,     0,   176,   177,
       0,     0,     0,     0,     0,     0,   184,   185,     0,     0,
      77,    77,    77,   186,    77,    77,   189,   190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    77,     0,
       0,     0,    77,     0,     0,     0,     0,     0,     0,     0,
       0,    77,    77,    77,    77,     0,     0,     0,     0,     0,
       0,    77,   213,     0,    77,   215,     0,    77,    77,     0,
       0,     0,     0,     0,     0,     0,   223,     0,     0,     0,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
       0,     0,     0,     0,     0,     0,     0,   271,   272,   273,
     274,   215,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     0,     0,    48,     0,     0,
     283,   285,     0,     0,   288,    49,    50,    51,    52,     0,
       0,     0,     0,   147,    53,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     0,     0,
      48,     0,     0,     0,     0,     0,   299,     0,    49,    50,
      51,    52,     0,     0,     0,   286,     0,    53,     0,   309,
       0,     0,     0,     0,   313,    12,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   326,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,    12,     4,
      49,    50,    51,    52,     0,     0,     0,     0,   318,    53,
      36,     0,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     0,     0,    48,     0,     0,     0,     0,
       0,     0,     0,    49,    50,    51,    52,     0,     0,     0,
     319,     0,    53,     0,     0,     0,     0,     0,     0,     0,
      12,     4,     0,     0,    36,     0,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,    49,    50,    51,
      52,     0,     0,    12,     4,   321,    53,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,     0,     0,     0,     0,   323,    53,
       0,     0,     0,     0,     0,     0,     0,    12,     4,     0,
       0,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,     0,     0,    48,     0,     0,     0,
       0,     0,     0,     0,    49,    50,    51,    52,     0,     0,
      12,     4,   325,    53,    36,     0,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     0,     0,    48,
       0,     0,     0,     0,     0,     0,     0,    49,    50,    51,
      52,     0,     0,     0,   342,     0,    53,     0,     0,     0,
       0,     0,     0,     0,    12,     4,     0,     0,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,    49,    50,    51,    52,     0,     0,    12,     4,   344,
      53,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,     0,     0,    48,     0,     0,     0,
       0,     0,     0,     0,    49,    50,    51,    52,     0,     0,
       0,   345,     0,    53,     0,     0,     0,     0,     0,     0,
       0,    12,     4,     0,     0,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     0,     0,
      48,     0,     0,     0,     0,     0,     0,     0,    49,    50,
      51,    52,     0,     0,    12,     4,   347,    53,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,    49,    50,    51,    52,     0,     0,     0,     0,   350,
      53,     0,     0,     0,     0,     0,     0,     0,    12,     4,
       0,     0,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,     0,    49,    50,    51,    52,     0,
       0,    12,     4,   351,    53,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     0,     0,
      48,     0,     0,     0,     0,     0,    46,     0,    49,    50,
      51,    52,     0,     0,   100,   101,   102,    53,    49,    50,
      51,    52,   103,   104,     0,    12,     4,   222,     0,     0,
       0,   105,   152,     0,   153,   154,     0,   155,   156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,     0,     0,   158,     0,    12,     4,
       0,     0,   159,   160,     0,     0,   107,   108,    12,     4,
      23,   109,   110,    91,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   242,     0,     0,     0,     0,
       0,     0,     0,     0,    12,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   192,     0,     0,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,   204,   205,   206,   207,   208,   209,   244,     0,
       0,     0,     0,   245,     0,     0,     0,     0,     0,   192,
       0,     0,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,   204,   205,   206,   207,   208,   209,
     293,     0,     0,     0,     0,   294,     0,     0,     0,     0,
       0,   192,     0,     0,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   203,   204,   205,   206,   207,
     208,   209,   297,     0,     0,     0,     0,   298,     0,     0,
       0,     0,     0,   192,     0,     0,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,     0,     0,     0,     0,
       0,     0,     0,   239,     0,     0,     0,   203,   204,   205,
     206,   207,   208,   209,   192,     0,     0,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,     0,     0,     0,
       0,     0,     0,     0,   240,     0,     0,     0,   203,   204,
     205,   206,   207,   208,   209,   192,     0,     0,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,     0,     0,
       0,     0,     0,     0,     0,   243,     0,     0,     0,   203,
     204,   205,   206,   207,   208,   209,   192,     0,     0,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,     0,
       0,     0,     0,     0,     0,     0,   269,     0,     0,     0,
     203,   204,   205,   206,   207,   208,   209,   192,     0,     0,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
       0,     0,     0,     0,     0,     0,     0,   296,     0,     0,
       0,   203,   204,   205,   206,   207,   208,   209,   192,     0,
       0,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,     0,     0,     0,     0,     0,     0,     0,   305,     0,
       0,     0,   203,   204,   205,   206,   207,   208,   209,   192,
       0,     0,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,     0,     0,     0,     0,     0,     0,     0,   330,
       0,     0,     0,   203,   204,   205,   206,   207,   208,   209,
     192,     0,     0,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,     0,     0,     0,     0,     0,     0,     0,
     336,     0,     0,     0,   203,   204,   205,   206,   207,   208,
     209,   192,     0,     0,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   203,   204,   205,   206,   207,
     208,   209,   270,     0,     0,     0,     0,     0,     0,   192,
       0,     0,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,   204,   205,   206,   207,   208,   209,
     275,     0,     0,     0,     0,     0,     0,   192,     0,     0,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,   204,   205,   206,   207,   208,   209,   295,     0,
       0,     0,     0,     0,   192,     0,     0,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,   204,
     205,   206,   207,   208,   209,   307,     0,     0,     0,     0,
       0,   192,     0,     0,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   203,   204,   205,   206,   207,
     208,   209,   290,     0,     0,   192,     0,     0,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   203,
     204,   205,   206,   207,   208,   209,   191,     0,   192,     0,
       0,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,   204,   205,   206,   207,   208,   209,   192,
       0,     0,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,   204,   205,   206,   207,   208,   209
  };

  const short
  parser::yycheck_[] =
  {
       0,    17,    47,    46,    54,    96,     6,    46,     3,     4,
       5,   279,    35,   281,    26,    27,    17,    40,   286,    79,
      38,    21,    38,    28,    17,    41,    17,    81,    34,     0,
      84,    31,    17,    34,    34,    34,    17,    38,    34,    82,
      41,    44,    45,    82,    17,    38,    46,    38,    41,    81,
      41,   319,    17,    38,    54,   323,    41,    38,     1,   104,
      41,    79,    80,    79,    80,    38,    44,    80,    41,    17,
      44,    83,    84,    38,   342,    80,    41,   345,    79,    80,
     123,    35,    82,    35,   123,    80,    79,    80,    79,    80,
      38,    34,   278,    41,    79,    80,    96,    44,    79,    80,
      36,    14,    15,    46,    34,   105,    79,    80,   294,   152,
      34,    54,   298,   152,    79,    80,    43,    34,    44,    34,
      34,    26,    27,   123,   310,    38,    44,    38,    35,    34,
      34,    79,    80,    40,    44,    44,    44,    35,    35,    82,
     183,    34,    40,    40,   183,    44,    35,    29,    30,    31,
      32,    40,   152,    96,    35,    42,    38,    43,   158,    40,
      43,    54,     6,    42,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,   175,    34,    21,    83,    84,
     123,    45,    44,   183,    34,    29,    30,    31,    32,   239,
      44,    34,    36,   243,    38,    34,    54,    79,    80,    34,
      40,   246,    34,    96,     7,    36,    17,    44,    44,   152,
      39,   211,   212,   304,    25,    26,    27,    40,    29,    30,
      31,    32,    33,    34,    34,    44,    34,    38,    44,    44,
       7,    42,    44,    44,    35,    79,    80,    35,    96,   239,
     183,     6,    44,   243,    44,     6,    54,     6,     6,   304,
      38,   301,   302,   303,   241,   305,   306,    -1,    -1,    -1,
      -1,    -1,    -1,   308,    -1,    -1,    77,    78,    79,    80,
      81,    82,    83,    84,    -1,    -1,    -1,    -1,    -1,   279,
      -1,   281,   332,   333,   334,   335,   286,    -1,    96,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   239,    -1,   348,   349,
     243,   301,   302,   303,   304,   305,   306,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   319,
      -1,    -1,    -1,   323,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,   332,   333,   334,   335,   279,    -1,   281,    -1,
      -1,    -1,   342,   286,    -1,   345,   239,    -1,   348,   349,
     243,    -1,    -1,    -1,    -1,    -1,    -1,    34,   301,   302,
     303,   304,   305,   306,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,    -1,    -1,   319,    54,    -1,    -1,
     323,   239,    -1,    -1,    -1,   243,   279,    -1,   281,   332,
     333,   334,   335,   286,    -1,    -1,    -1,    -1,    -1,   342,
      -1,    -1,   345,    -1,    -1,   348,   349,    34,   301,   302,
     303,   304,   305,   306,    -1,    -1,    -1,    -1,    -1,    96,
      -1,   279,    -1,   281,    -1,    -1,   319,    54,   286,    -1,
     323,   239,    -1,    -1,    -1,   243,    -1,    -1,    -1,   332,
     333,   334,   335,   301,   302,   303,   304,   305,   306,   342,
      -1,    -1,   345,    -1,    -1,   348,   349,    -1,    -1,    -1,
      -1,   319,    -1,    -1,    -1,   323,    -1,    -1,    -1,    96,
      -1,   279,    -1,   281,   332,   333,   334,   335,   286,    -1,
      34,    -1,    -1,    -1,   342,    -1,    -1,   345,    -1,    -1,
     348,   349,    -1,   301,   302,   303,   304,   305,   306,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   319,   239,    -1,    -1,   323,   243,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   332,   333,   334,   335,    -1,    -1,
      -1,    -1,    -1,    -1,   342,    -1,    -1,   345,    -1,    -1,
     348,   349,    96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,   279,    -1,   281,    -1,    -1,    -1,    -1,   286,
      -1,    -1,   239,    -1,    -1,    -1,   243,    -1,    -1,    -1,
      -1,    54,    17,    -1,   301,   302,   303,   304,   305,   306,
      25,    26,    27,    -1,    29,    30,    31,    32,    33,    34,
      -1,    -1,   319,    38,    -1,    -1,   323,    42,    -1,    -1,
      -1,    -1,   279,    -1,   281,   332,   333,   334,   335,   286,
      -1,    -1,   239,    96,    -1,   342,   243,    -1,   345,    -1,
      -1,   348,   349,    34,   301,   302,   303,   304,   305,   306,
      -1,    -1,    77,    78,    79,    80,    81,    82,    83,    84,
      -1,    -1,   319,    54,    -1,    -1,   323,    -1,    -1,    -1,
      -1,    -1,   279,    -1,   281,   332,   333,   334,   335,   286,
      -1,    -1,    -1,    -1,    -1,   342,    -1,    -1,   345,    -1,
      -1,   348,   349,    -1,   301,   302,   303,   304,   305,   306,
      -1,    -1,    -1,    -1,    -1,   239,    -1,    -1,    -1,   243,
      -1,    -1,   319,    -1,    -1,    -1,   323,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   332,   333,   334,   335,    -1,
      -1,    -1,    -1,    -1,    -1,   342,    -1,    -1,   345,    -1,
      -1,   348,   349,    -1,    -1,   279,    -1,   281,    -1,    -1,
      -1,    -1,   286,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   301,   302,   303,
     304,   305,   306,    -1,    -1,    -1,   239,    -1,    -1,    -1,
     243,    -1,    -1,    -1,    -1,   319,    -1,    -1,    -1,   323,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   332,   333,
     334,   335,    -1,    38,    -1,    -1,    41,    -1,   342,    -1,
      -1,   345,    47,    48,   348,   349,   279,    -1,   281,    -1,
      -1,    -1,    -1,   286,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    -1,   301,   302,
     303,   304,   305,   306,    79,    80,    -1,    -1,   239,    -1,
      -1,    -1,   243,    -1,    45,    -1,   319,    -1,    -1,    -1,
     323,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   332,
     333,   334,   335,    -1,    -1,    -1,    -1,    -1,    -1,   342,
      -1,    -1,   345,    -1,    -1,   348,   349,    -1,   279,    -1,
     281,    -1,    -1,    -1,    -1,   286,    -1,    -1,    89,    90,
      -1,    -1,    -1,    -1,    -1,    -1,    97,    98,    -1,    -1,
     301,   302,   303,   104,   305,   306,   107,   108,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   319,    -1,
      -1,    -1,   323,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   332,   333,   334,   335,    -1,    -1,    -1,    -1,    -1,
      -1,   342,   143,    -1,   345,   146,    -1,   348,   349,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   157,    -1,    -1,    -1,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,   219,   220,
     221,   222,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
     241,   242,    -1,    -1,   245,    29,    30,    31,    32,    -1,
      -1,    -1,    -1,    37,    38,     6,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,   277,    -1,    29,    30,
      31,    32,    -1,    -1,    -1,    36,    -1,    38,    -1,   290,
      -1,    -1,    -1,    -1,   295,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   307,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    79,    80,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,
       6,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    -1,    -1,    -1,
      36,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    80,    -1,    -1,     6,    -1,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    -1,    -1,    79,    80,    37,    38,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,
      -1,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    -1,    -1,
      79,    80,    37,    38,     6,    -1,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    -1,    -1,    -1,    36,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    80,    -1,    -1,     6,    -1,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    -1,    -1,    79,    80,    37,
      38,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,    -1,    -1,     6,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    -1,    -1,    79,    80,    37,    38,     6,    -1,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    -1,    -1,    -1,    -1,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,
      -1,    -1,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    -1,
      -1,    79,    80,    37,    38,     6,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    17,    -1,    29,    30,
      31,    32,    -1,    -1,    25,    26,    27,    38,    29,    30,
      31,    32,    33,    34,    -1,    79,    80,    38,    -1,    -1,
      -1,    42,    17,    -1,    19,    20,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    79,    80,
      -1,    -1,    47,    48,    -1,    -1,    77,    78,    79,    80,
      81,    82,    83,    84,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
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
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    35,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
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
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    40,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    40,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    43,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    44,    -1,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,    80,    87,    88,    89,    90,    91,
      92,   142,    79,   143,    34,    34,     0,    89,    90,    91,
      92,    34,    44,    81,   141,   141,    93,   142,    35,    35,
      35,    40,    44,    44,    36,   142,     6,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    21,    29,
      30,    31,    32,    38,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   118,   123,   124,   125,   126,
     129,   130,   133,   142,   143,   147,   148,   149,   150,    34,
      34,    84,   139,   141,    43,    44,    34,    34,    34,    44,
      25,    26,    27,    33,    34,    42,    44,    77,    78,    82,
      83,   117,   119,   120,   121,   122,   123,   124,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   147,   148,   149,   150,
     125,   126,   142,    34,   135,    44,    38,    37,    95,    44,
      44,    44,    17,    19,    20,    22,    23,    38,    41,    47,
      48,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,   125,   126,    34,    42,   117,   117,    43,    43,
     115,   118,   123,   133,   117,   117,   117,   135,   142,   117,
     117,    44,    46,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    70,    71,    72,    73,    74,    75,    76,
      45,    41,    42,   117,    44,   117,   125,   126,    34,    34,
      34,    34,    38,   117,   142,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   127,   142,    35,
      35,    44,    24,    35,    35,    40,    40,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,    28,   146,   142,    35,
      39,   117,   117,   117,   117,    39,    35,    40,    34,    36,
      95,    36,   116,   117,   119,   117,    36,    95,   117,   135,
      43,    44,    39,    35,    40,    40,    35,    35,    40,   117,
     127,    94,     7,    94,    44,    35,    94,    40,    40,   117,
      34,    44,   127,   117,    44,    44,   127,    35,    37,    36,
      95,    37,   115,    37,    95,    37,   117,   135,   127,    35,
      35,    35,     7,    94,    35,    94,    35,    35,    35,    44,
      44,    44,    36,    95,    37,    36,    95,    37,    94,    94,
      37,    37
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
     122,   122,   122,   122,   123,   123,   123,   123,   124,   124,
     124,   124,   125,   125,   126,   127,   127,   127,   128,   128,
     129,   130,   131,   132,   133,   133,   133,   133,   133,   133,
     133,   133,   134,   135,   135,   135,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150
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
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       3,     3,     4,     6,     8,     3,     1,     0,     2,     3,
       4,     3,     3,     7,     1,     1,     1,     1,     1,     1,
       1,     1,     7,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   112,   112,   113,   117,   119,   121,   123,   125,   127,
     129,   131,   136,   141,   146,   151,   156,   158,   161,   165,
     167,   170,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   196,   198,   203,   208,   213,   215,   220,   222,   227,
     229,   234,   239,   244,   246,   251,   253,   255,   257,   262,
     264,   269,   271,   276,   278,   283,   288,   290,   295,   300,
     304,   309,   311,   316,   317,   321,   322,   326,   327,   328,
     329,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   349,   350,   351,   352,   353,   354,
     355,   356,   360,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   401,   402,   403,   404,   408,   409,
     410,   411,   415,   417,   422,   427,   429,   432,   436,   438,
     443,   448,   453,   458,   463,   464,   465,   466,   467,   468,
     469,   470,   474,   479,   480,   481,   482,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   499
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
#line 3709 "./IW6/compiler_parser.cpp"

#line 501 "iw6.parser.ypp"


void yy::parser::error(const std::string& msg)
{
    std::cout << "An error occured: " << msg << std::endl;
	exit(1);
}
