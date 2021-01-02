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
#line 37 "S1.parser.ypp"

    #include "S1.hpp"
	#include "compiler_parser.hpp"
	#include "compiler_lexer.hpp"
	S1::parser::symbol_type S1lex(yyscan_t yyscanner, std::uint32_t *location);

#line 46 "./S1/compiler_parser.cpp"

// Take the name prefix into account.
#define yylex   S1lex



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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !S1DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "S1.parser.ypp"
namespace S1 {
#line 129 "./S1/compiler_parser.cpp"

  /// Build a parser object.
  parser::parser (yyscan_t yyscanner_yyarg, std::uint32_t *location_yyarg, gsc::script_ptr& astout_yyarg)
#if S1DEBUG
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
      case symbol_kind::S_animref: // animref
        value.YY_MOVE_OR_COPY< gsc::animref_ptr > (YY_MOVE (that.value));
        break;

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
      case symbol_kind::S_ANIMREF: // ANIMREF
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
      case symbol_kind::S_animref: // animref
        value.move< gsc::animref_ptr > (YY_MOVE (that.value));
        break;

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
      case symbol_kind::S_ANIMREF: // ANIMREF
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
      case symbol_kind::S_animref: // animref
        value.copy< gsc::animref_ptr > (that.value);
        break;

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
      case symbol_kind::S_ANIMREF: // ANIMREF
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
      case symbol_kind::S_animref: // animref
        value.move< gsc::animref_ptr > (that.value);
        break;

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
      case symbol_kind::S_ANIMREF: // ANIMREF
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

#if S1DEBUG
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
      case symbol_kind::S_animref: // animref
        yylhs.value.emplace< gsc::animref_ptr > ();
        break;

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
      case symbol_kind::S_ANIMREF: // ANIMREF
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
#line 119 "S1.parser.ypp"
                 { astout = std::move(yystack_[0].value.as < gsc::script_ptr > ()); }
#line 1504 "./S1/compiler_parser.cpp"
    break;

  case 3: // root: %empty
#line 120 "S1.parser.ypp"
                 { astout = std::make_unique<gsc::node_script>(); }
#line 1510 "./S1/compiler_parser.cpp"
    break;

  case 4: // script: script include
#line 125 "S1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ())); }
#line 1516 "./S1/compiler_parser.cpp"
    break;

  case 5: // script: script using_animtree
#line 127 "S1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1522 "./S1/compiler_parser.cpp"
    break;

  case 6: // script: script animtree
#line 129 "S1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1528 "./S1/compiler_parser.cpp"
    break;

  case 7: // script: script thread
#line 131 "S1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ())); }
#line 1534 "./S1/compiler_parser.cpp"
    break;

  case 8: // script: include
#line 133 "S1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ()));}
#line 1540 "./S1/compiler_parser.cpp"
    break;

  case 9: // script: using_animtree
#line 135 "S1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1546 "./S1/compiler_parser.cpp"
    break;

  case 10: // script: animtree
#line 137 "S1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1552 "./S1/compiler_parser.cpp"
    break;

  case 11: // script: thread
#line 139 "S1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ()));}
#line 1558 "./S1/compiler_parser.cpp"
    break;

  case 12: // include: INCLUDE filepath SEMICOLON
#line 144 "S1.parser.ypp"
                { yylhs.value.as < gsc::include_ptr > () = std::make_unique<gsc::node_include>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::filepath_ptr > ())); }
#line 1564 "./S1/compiler_parser.cpp"
    break;

  case 13: // using_animtree: USING_ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 149 "S1.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1570 "./S1/compiler_parser.cpp"
    break;

  case 14: // animtree: ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 154 "S1.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1576 "./S1/compiler_parser.cpp"
    break;

  case 15: // thread: identifier LPAREN parameters RPAREN LBRACE block RBRACE
#line 159 "S1.parser.ypp"
                { yylhs.value.as < gsc::thread_ptr > () = std::make_unique<gsc::node_thread>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::identifier_ptr > ()), std::move(yystack_[4].value.as < gsc::parameters_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1582 "./S1/compiler_parser.cpp"
    break;

  case 16: // parameters: parameters COMMA identifier
#line 164 "S1.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::move(yystack_[2].value.as < gsc::parameters_ptr > ()); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1588 "./S1/compiler_parser.cpp"
    break;

  case 17: // parameters: identifier
#line 166 "S1.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(std::to_string(*location)); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1594 "./S1/compiler_parser.cpp"
    break;

  case 18: // parameters: %empty
#line 168 "S1.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(std::to_string(*location)); }
#line 1600 "./S1/compiler_parser.cpp"
    break;

  case 19: // block: block stmt
#line 173 "S1.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::move(yystack_[1].value.as < gsc::block_ptr > ()); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1606 "./S1/compiler_parser.cpp"
    break;

  case 20: // block: stmt
#line 175 "S1.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(std::to_string(*location)); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1612 "./S1/compiler_parser.cpp"
    break;

  case 21: // block: %empty
#line 177 "S1.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(std::to_string(*location)); }
#line 1618 "./S1/compiler_parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 181 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_call = std::move(yystack_[0].value.as < gsc::stmt_call_ptr > ()); }
#line 1624 "./S1/compiler_parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 182 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < gsc::stmt_assign_ptr > ()); }
#line 1630 "./S1/compiler_parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 183 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < gsc::stmt_endon_ptr > ()); }
#line 1636 "./S1/compiler_parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 184 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < gsc::stmt_notify_ptr > ()); }
#line 1642 "./S1/compiler_parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 185 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < gsc::stmt_wait_ptr > ()); }
#line 1648 "./S1/compiler_parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 186 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < gsc::stmt_waittill_ptr > ()); }
#line 1654 "./S1/compiler_parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 187 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < gsc::stmt_waittillmatch_ptr > ()); }
#line 1660 "./S1/compiler_parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 188 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < gsc::stmt_waittillframeend_ptr > ()); }
#line 1666 "./S1/compiler_parser.cpp"
    break;

  case 30: // stmt: stmt_waitframe
#line 189 "S1.parser.ypp"
                                                                            { yylhs.value.as < gsc::stmt_ptr > ().as_waitframe = std::move(yystack_[0].value.as < gsc::stmt_waitframe_ptr > ()); }
#line 1672 "./S1/compiler_parser.cpp"
    break;

  case 31: // stmt: stmt_if
#line 190 "S1.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_if = std::move(yystack_[0].value.as < gsc::stmt_if_ptr > ()); }
#line 1678 "./S1/compiler_parser.cpp"
    break;

  case 32: // stmt: stmt_ifelse
#line 191 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < gsc::stmt_ifelse_ptr > ()); }
#line 1684 "./S1/compiler_parser.cpp"
    break;

  case 33: // stmt: stmt_while
#line 192 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_while = std::move(yystack_[0].value.as < gsc::stmt_while_ptr > ()); }
#line 1690 "./S1/compiler_parser.cpp"
    break;

  case 34: // stmt: stmt_for
#line 193 "S1.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_for = std::move(yystack_[0].value.as < gsc::stmt_for_ptr > ()); }
#line 1696 "./S1/compiler_parser.cpp"
    break;

  case 35: // stmt: stmt_foreach
#line 194 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < gsc::stmt_foreach_ptr > ()); }
#line 1702 "./S1/compiler_parser.cpp"
    break;

  case 36: // stmt: stmt_switch
#line 195 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < gsc::stmt_switch_ptr > ()); }
#line 1708 "./S1/compiler_parser.cpp"
    break;

  case 37: // stmt: stmt_case
#line 196 "S1.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_case = std::move(yystack_[0].value.as < gsc::stmt_case_ptr > ()); }
#line 1714 "./S1/compiler_parser.cpp"
    break;

  case 38: // stmt: stmt_default
#line 197 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_default = std::move(yystack_[0].value.as < gsc::stmt_default_ptr > ()); }
#line 1720 "./S1/compiler_parser.cpp"
    break;

  case 39: // stmt: stmt_break
#line 198 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_break = std::move(yystack_[0].value.as < gsc::stmt_break_ptr > ()); }
#line 1726 "./S1/compiler_parser.cpp"
    break;

  case 40: // stmt: stmt_continue
#line 199 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < gsc::stmt_continue_ptr > ()); }
#line 1732 "./S1/compiler_parser.cpp"
    break;

  case 41: // stmt: stmt_return
#line 200 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_return = std::move(yystack_[0].value.as < gsc::stmt_return_ptr > ()); }
#line 1738 "./S1/compiler_parser.cpp"
    break;

  case 42: // stmt_call: expr_call SEMICOLON
#line 205 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1744 "./S1/compiler_parser.cpp"
    break;

  case 43: // stmt_call: expr_call_thread SEMICOLON
#line 207 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1750 "./S1/compiler_parser.cpp"
    break;

  case 44: // stmt_assign: expr_assign SEMICOLON
#line 212 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_assign_ptr > () = std::make_unique<gsc::node_stmt_assign>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_assign_ptr > ())); }
#line 1756 "./S1/compiler_parser.cpp"
    break;

  case 45: // stmt_endon: object ENDON LPAREN expr RPAREN SEMICOLON
#line 217 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_endon_ptr > () = std::make_unique<gsc::node_stmt_endon>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1762 "./S1/compiler_parser.cpp"
    break;

  case 46: // stmt_notify: object NOTIFY LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 222 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>(std::to_string(*location), std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1768 "./S1/compiler_parser.cpp"
    break;

  case 47: // stmt_notify: object NOTIFY LPAREN expr RPAREN SEMICOLON
#line 224 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>(std::to_string(*location))); }
#line 1774 "./S1/compiler_parser.cpp"
    break;

  case 48: // stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON
#line 229 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1780 "./S1/compiler_parser.cpp"
    break;

  case 49: // stmt_wait: WAIT num SEMICOLON
#line 231 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1786 "./S1/compiler_parser.cpp"
    break;

  case 50: // stmt_waittill: object WAITTILL LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 236 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>(std::to_string(*location), std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1792 "./S1/compiler_parser.cpp"
    break;

  case 51: // stmt_waittill: object WAITTILL LPAREN expr RPAREN SEMICOLON
#line 238 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>(std::to_string(*location))); }
#line 1798 "./S1/compiler_parser.cpp"
    break;

  case 52: // stmt_waittillmatch: object WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON
#line 243 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillmatch_ptr > () = std::make_unique<gsc::node_stmt_waittillmatch>(std::to_string(*location), std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1804 "./S1/compiler_parser.cpp"
    break;

  case 53: // stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON
#line 248 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillframeend_ptr > () = std::make_unique<gsc::node_stmt_waittillframeend>(std::to_string(*location)); }
#line 1810 "./S1/compiler_parser.cpp"
    break;

  case 54: // stmt_waitframe: WAITFRAME SEMICOLON
#line 253 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waitframe_ptr > () = std::make_unique<gsc::node_stmt_waitframe>(std::to_string(*location)); }
#line 1816 "./S1/compiler_parser.cpp"
    break;

  case 55: // stmt_if: IF LPAREN expr RPAREN LBRACE block RBRACE
#line 258 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1822 "./S1/compiler_parser.cpp"
    break;

  case 56: // stmt_if: IF LPAREN expr RPAREN stmt
#line 260 "S1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1831 "./S1/compiler_parser.cpp"
    break;

  case 57: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE LBRACE block RBRACE
#line 268 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[5].value.as < gsc::block_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1837 "./S1/compiler_parser.cpp"
    break;

  case 58: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE block RBRACE
#line 270 "S1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[4].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(blk), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1846 "./S1/compiler_parser.cpp"
    break;

  case 59: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE stmt
#line 275 "S1.parser.ypp"
                { 
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::block_ptr > ()), std::move(blk)); }
#line 1855 "./S1/compiler_parser.cpp"
    break;

  case 60: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt
#line 280 "S1.parser.ypp"
                {
			auto blk1 = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk1->stmts.push_back(std::move(yystack_[2].value.as < gsc::stmt_ptr > ()));
			auto blk2 = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk2->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(blk1), std::move(blk2)); }
#line 1866 "./S1/compiler_parser.cpp"
    break;

  case 61: // stmt_while: WHILE LPAREN expr RPAREN LBRACE block RBRACE
#line 290 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1872 "./S1/compiler_parser.cpp"
    break;

  case 62: // stmt_while: WHILE LPAREN expr RPAREN stmt
#line 292 "S1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1881 "./S1/compiler_parser.cpp"
    break;

  case 63: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE block RBRACE
#line 300 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>(std::to_string(*location), std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1887 "./S1/compiler_parser.cpp"
    break;

  case 64: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt
#line 302 "S1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1897 "./S1/compiler_parser.cpp"
    break;

  case 65: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE block RBRACE
#line 311 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1903 "./S1/compiler_parser.cpp"
    break;

  case 66: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt
#line 313 "S1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1913 "./S1/compiler_parser.cpp"
    break;

  case 67: // stmt_switch: SWITCH LPAREN expr RPAREN LBRACE block RBRACE
#line 322 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_switch_ptr > () = std::make_unique<gsc::node_stmt_switch>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1919 "./S1/compiler_parser.cpp"
    break;

  case 68: // stmt_case: CASE data_integer COLON
#line 327 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>(std::to_string(*location), gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::integer_ptr > ()))); }
#line 1925 "./S1/compiler_parser.cpp"
    break;

  case 69: // stmt_case: CASE data_string COLON
#line 329 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>(std::to_string(*location), gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::string_ptr > ()))); }
#line 1931 "./S1/compiler_parser.cpp"
    break;

  case 70: // stmt_default: DEFAULT COLON
#line 334 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_default_ptr > () = std::make_unique<gsc::node_stmt_default>(std::to_string(*location)); }
#line 1937 "./S1/compiler_parser.cpp"
    break;

  case 71: // stmt_break: BREAK SEMICOLON
#line 339 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_break_ptr > () = std::make_unique<gsc::node_stmt_break>(std::to_string(*location)); }
#line 1943 "./S1/compiler_parser.cpp"
    break;

  case 72: // stmt_continue: CONTINUE SEMICOLON
#line 343 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_continue_ptr > () = std::make_unique<gsc::node_stmt_continue>(std::to_string(*location)); }
#line 1949 "./S1/compiler_parser.cpp"
    break;

  case 73: // stmt_return: RETURN expr SEMICOLON
#line 348 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 1955 "./S1/compiler_parser.cpp"
    break;

  case 74: // stmt_return: RETURN SEMICOLON
#line 350 "S1.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>(std::to_string(*location), std::make_unique<gsc::node>()); }
#line 1961 "./S1/compiler_parser.cpp"
    break;

  case 75: // for_assign: expr_assign
#line 354 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_assign_ptr > ()); }
#line 1967 "./S1/compiler_parser.cpp"
    break;

  case 76: // for_assign: %empty
#line 355 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1973 "./S1/compiler_parser.cpp"
    break;

  case 77: // for_cond: expr_cmp
#line 359 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1979 "./S1/compiler_parser.cpp"
    break;

  case 78: // for_cond: %empty
#line 360 "S1.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1985 "./S1/compiler_parser.cpp"
    break;

  case 79: // expr: expr_cmp
#line 364 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1991 "./S1/compiler_parser.cpp"
    break;

  case 80: // expr: expr_ternary
#line 365 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1997 "./S1/compiler_parser.cpp"
    break;

  case 81: // expr: expr_binary
#line 366 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 2003 "./S1/compiler_parser.cpp"
    break;

  case 82: // expr: expr_primitive
#line 367 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 2009 "./S1/compiler_parser.cpp"
    break;

  case 83: // expr_assign: object INCREMENT
#line 371 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_increment>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2015 "./S1/compiler_parser.cpp"
    break;

  case 84: // expr_assign: object DECREMENT
#line 372 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_decrement>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2021 "./S1/compiler_parser.cpp"
    break;

  case 85: // expr_assign: object ASSIGN expr
#line 373 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_equal>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2027 "./S1/compiler_parser.cpp"
    break;

  case 86: // expr_assign: object ASSIGN_BITWISE_OR expr
#line 374 "S1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_or>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2033 "./S1/compiler_parser.cpp"
    break;

  case 87: // expr_assign: object ASSIGN_BITWISE_AND expr
#line 375 "S1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_and>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2039 "./S1/compiler_parser.cpp"
    break;

  case 88: // expr_assign: object ASSIGN_BITWISE_EXOR expr
#line 376 "S1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_exor>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2045 "./S1/compiler_parser.cpp"
    break;

  case 89: // expr_assign: object ASSIGN_LSHIFT expr
#line 377 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_left>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()),std::move( yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2051 "./S1/compiler_parser.cpp"
    break;

  case 90: // expr_assign: object ASSIGN_RSHIFT expr
#line 378 "S1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_right>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2057 "./S1/compiler_parser.cpp"
    break;

  case 91: // expr_assign: object ASSIGN_ADD expr
#line 379 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_add>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2063 "./S1/compiler_parser.cpp"
    break;

  case 92: // expr_assign: object ASSIGN_SUB expr
#line 380 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_sub>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2069 "./S1/compiler_parser.cpp"
    break;

  case 93: // expr_assign: object ASSIGN_MULT expr
#line 381 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mult>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2075 "./S1/compiler_parser.cpp"
    break;

  case 94: // expr_assign: object ASSIGN_DIV expr
#line 382 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_div>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2081 "./S1/compiler_parser.cpp"
    break;

  case 95: // expr_assign: object ASSIGN_MOD expr
#line 383 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mod>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2087 "./S1/compiler_parser.cpp"
    break;

  case 96: // expr_cmp: expr OR expr
#line 387 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_or>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2093 "./S1/compiler_parser.cpp"
    break;

  case 97: // expr_cmp: expr AND expr
#line 388 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_and>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2099 "./S1/compiler_parser.cpp"
    break;

  case 98: // expr_cmp: expr EQUALITY expr
#line 389 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_equality>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2105 "./S1/compiler_parser.cpp"
    break;

  case 99: // expr_cmp: expr INEQUALITY expr
#line 390 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_inequality>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2111 "./S1/compiler_parser.cpp"
    break;

  case 100: // expr_cmp: expr LESS_EQUAL expr
#line 391 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less_equal>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2117 "./S1/compiler_parser.cpp"
    break;

  case 101: // expr_cmp: expr GREATER_EQUAL expr
#line 392 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater_equal>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2123 "./S1/compiler_parser.cpp"
    break;

  case 102: // expr_cmp: expr LESS expr
#line 393 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2129 "./S1/compiler_parser.cpp"
    break;

  case 103: // expr_cmp: expr GREATER expr
#line 394 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2135 "./S1/compiler_parser.cpp"
    break;

  case 104: // expr_ternary: expr_cmp QMARK expr COLON expr
#line 398 "S1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_ternary>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2141 "./S1/compiler_parser.cpp"
    break;

  case 105: // expr_binary: expr BITWISE_OR expr
#line 402 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_or>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2147 "./S1/compiler_parser.cpp"
    break;

  case 106: // expr_binary: expr BITWISE_AND expr
#line 403 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_and>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2153 "./S1/compiler_parser.cpp"
    break;

  case 107: // expr_binary: expr BITWISE_EXOR expr
#line 404 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_exor>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2159 "./S1/compiler_parser.cpp"
    break;

  case 108: // expr_binary: expr LSHIFT expr
#line 405 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_left>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2165 "./S1/compiler_parser.cpp"
    break;

  case 109: // expr_binary: expr RSHIFT expr
#line 406 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_right>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2171 "./S1/compiler_parser.cpp"
    break;

  case 110: // expr_binary: expr ADD expr
#line 407 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_add>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2177 "./S1/compiler_parser.cpp"
    break;

  case 111: // expr_binary: expr SUB expr
#line 408 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_sub>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2183 "./S1/compiler_parser.cpp"
    break;

  case 112: // expr_binary: expr MULT expr
#line 409 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mult>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2189 "./S1/compiler_parser.cpp"
    break;

  case 113: // expr_binary: expr DIV expr
#line 410 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_div>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2195 "./S1/compiler_parser.cpp"
    break;

  case 114: // expr_binary: expr MOD expr
#line 411 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mod>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2201 "./S1/compiler_parser.cpp"
    break;

  case 115: // expr_primitive: LPAREN expr RPAREN
#line 415 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[1].value.as < gsc::expr_ptr > ()); }
#line 2207 "./S1/compiler_parser.cpp"
    break;

  case 116: // expr_primitive: COMPLEMENT expr
#line 416 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_complement>(std::to_string(*location), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2213 "./S1/compiler_parser.cpp"
    break;

  case 117: // expr_primitive: NOT expr
#line 417 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_not>(std::to_string(*location), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2219 "./S1/compiler_parser.cpp"
    break;

  case 118: // expr_primitive: expr_call
#line 418 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2225 "./S1/compiler_parser.cpp"
    break;

  case 119: // expr_primitive: expr_call_thread
#line 419 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2231 "./S1/compiler_parser.cpp"
    break;

  case 120: // expr_primitive: expr_function_ref
#line 420 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2237 "./S1/compiler_parser.cpp"
    break;

  case 121: // expr_primitive: expr_array
#line 421 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2243 "./S1/compiler_parser.cpp"
    break;

  case 122: // expr_primitive: expr_field
#line 422 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2249 "./S1/compiler_parser.cpp"
    break;

  case 123: // expr_primitive: expr_size
#line 423 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2255 "./S1/compiler_parser.cpp"
    break;

  case 124: // expr_primitive: expr_vector
#line 424 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2261 "./S1/compiler_parser.cpp"
    break;

  case 125: // expr_primitive: expr_add_array
#line 425 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2267 "./S1/compiler_parser.cpp"
    break;

  case 126: // expr_primitive: vector
#line 426 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2273 "./S1/compiler_parser.cpp"
    break;

  case 127: // expr_primitive: num
#line 427 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2279 "./S1/compiler_parser.cpp"
    break;

  case 128: // expr_primitive: data_localized_string
#line 428 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::localized_string_ptr > ()); }
#line 2285 "./S1/compiler_parser.cpp"
    break;

  case 129: // expr_primitive: data_string
#line 429 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::string_ptr > ()); }
#line 2291 "./S1/compiler_parser.cpp"
    break;

  case 130: // expr_primitive: animref
#line 430 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::animref_ptr > ()); }
#line 2297 "./S1/compiler_parser.cpp"
    break;

  case 131: // expr_primitive: identifier
#line 431 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2303 "./S1/compiler_parser.cpp"
    break;

  case 132: // expr_primitive: empty_array
#line 432 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2309 "./S1/compiler_parser.cpp"
    break;

  case 133: // expr_primitive: undefined
#line 433 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2315 "./S1/compiler_parser.cpp"
    break;

  case 134: // expr_primitive: game
#line 434 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2321 "./S1/compiler_parser.cpp"
    break;

  case 135: // expr_primitive: self
#line 435 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2327 "./S1/compiler_parser.cpp"
    break;

  case 136: // expr_primitive: anim
#line 436 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2333 "./S1/compiler_parser.cpp"
    break;

  case 137: // expr_primitive: level
#line 437 "S1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2339 "./S1/compiler_parser.cpp"
    break;

  case 138: // expr_call: expr_call_function
#line 441 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2345 "./S1/compiler_parser.cpp"
    break;

  case 139: // expr_call: expr_call_pointer
#line 442 "S1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2351 "./S1/compiler_parser.cpp"
    break;

  case 140: // expr_call: object expr_call_function
#line 443 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2357 "./S1/compiler_parser.cpp"
    break;

  case 141: // expr_call: object expr_call_pointer
#line 444 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2363 "./S1/compiler_parser.cpp"
    break;

  case 142: // expr_call_thread: THREAD expr_call_function
#line 448 "S1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2369 "./S1/compiler_parser.cpp"
    break;

  case 143: // expr_call_thread: THREAD expr_call_pointer
#line 449 "S1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2375 "./S1/compiler_parser.cpp"
    break;

  case 144: // expr_call_thread: object THREAD expr_call_function
#line 450 "S1.parser.ypp"
                                            { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2381 "./S1/compiler_parser.cpp"
    break;

  case 145: // expr_call_thread: object THREAD expr_call_pointer
#line 451 "S1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2387 "./S1/compiler_parser.cpp"
    break;

  case 146: // expr_call_function: identifier LPAREN expr_arguments RPAREN
#line 456 "S1.parser.ypp"
                {yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>(std::to_string(*location), std::make_unique<gsc::node_filepath>(std::to_string(*location), ""), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2393 "./S1/compiler_parser.cpp"
    break;

  case 147: // expr_call_function: filepath DOUBLECOLON identifier LPAREN expr_arguments RPAREN
#line 458 "S1.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::filepath_ptr > ()), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2399 "./S1/compiler_parser.cpp"
    break;

  case 148: // expr_call_pointer: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 463 "S1.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>(std::to_string(*location), false, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2405 "./S1/compiler_parser.cpp"
    break;

  case 149: // expr_call_pointer: CALL LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 465 "S1.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>(std::to_string(*location), true, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2411 "./S1/compiler_parser.cpp"
    break;

  case 150: // expr_arguments: expr_arguments COMMA expr
#line 470 "S1.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ()); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2417 "./S1/compiler_parser.cpp"
    break;

  case 151: // expr_arguments: expr
#line 472 "S1.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(std::to_string(*location)); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2423 "./S1/compiler_parser.cpp"
    break;

  case 152: // expr_arguments: %empty
#line 474 "S1.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(std::to_string(*location)); }
#line 2429 "./S1/compiler_parser.cpp"
    break;

  case 153: // expr_function_ref: DOUBLECOLON identifier
#line 479 "S1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>(std::to_string(*location), std::make_unique<gsc::node_filepath>(std::to_string(*location), ""), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2435 "./S1/compiler_parser.cpp"
    break;

  case 154: // expr_function_ref: filepath DOUBLECOLON identifier
#line 481 "S1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::filepath_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2441 "./S1/compiler_parser.cpp"
    break;

  case 155: // expr_array: object LBRACKET expr RBRACKET
#line 486 "S1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_array>(std::to_string(*location), std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2447 "./S1/compiler_parser.cpp"
    break;

  case 156: // expr_field: object DOT identifier
#line 491 "S1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_field>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2453 "./S1/compiler_parser.cpp"
    break;

  case 157: // expr_size: object DOT size
#line 496 "S1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_size>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ())); }
#line 2459 "./S1/compiler_parser.cpp"
    break;

  case 158: // expr_vector: LPAREN expr COMMA expr COMMA expr RPAREN
#line 501 "S1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_vector>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2465 "./S1/compiler_parser.cpp"
    break;

  case 159: // expr_add_array: LBRACKET expr_arguments RBRACKET
#line 506 "S1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_add_array>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2471 "./S1/compiler_parser.cpp"
    break;

  case 160: // object: expr_call
#line 510 "S1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2477 "./S1/compiler_parser.cpp"
    break;

  case 161: // object: expr_array
#line 511 "S1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2483 "./S1/compiler_parser.cpp"
    break;

  case 162: // object: expr_field
#line 512 "S1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2489 "./S1/compiler_parser.cpp"
    break;

  case 163: // object: identifier
#line 513 "S1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2495 "./S1/compiler_parser.cpp"
    break;

  case 164: // object: level
#line 514 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2501 "./S1/compiler_parser.cpp"
    break;

  case 165: // object: anim
#line 515 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2507 "./S1/compiler_parser.cpp"
    break;

  case 166: // object: self
#line 516 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2513 "./S1/compiler_parser.cpp"
    break;

  case 167: // object: game
#line 517 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2519 "./S1/compiler_parser.cpp"
    break;

  case 168: // vector: LPAREN num COMMA num COMMA num RPAREN
#line 522 "S1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_vector>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2525 "./S1/compiler_parser.cpp"
    break;

  case 169: // num: data_float
#line 526 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::float_ptr > ()); }
#line 2531 "./S1/compiler_parser.cpp"
    break;

  case 170: // num: data_integer
#line 527 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::integer_ptr > ()); }
#line 2537 "./S1/compiler_parser.cpp"
    break;

  case 171: // num: false
#line 528 "S1.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2543 "./S1/compiler_parser.cpp"
    break;

  case 172: // num: true
#line 529 "S1.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2549 "./S1/compiler_parser.cpp"
    break;

  case 173: // false: FALSE
#line 532 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>(std::to_string(*location), "0"); }
#line 2555 "./S1/compiler_parser.cpp"
    break;

  case 174: // true: TRUE
#line 533 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>(std::to_string(*location), "1"); }
#line 2561 "./S1/compiler_parser.cpp"
    break;

  case 175: // data_float: FLOAT
#line 534 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::float_ptr > () = std::make_unique<gsc::node_float>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2567 "./S1/compiler_parser.cpp"
    break;

  case 176: // data_integer: INTEGER
#line 535 "S1.parser.ypp"
                                { yylhs.value.as < gsc::integer_ptr > () = std::make_unique<gsc::node_integer>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2573 "./S1/compiler_parser.cpp"
    break;

  case 177: // data_localized_string: STRING_LOC
#line 536 "S1.parser.ypp"
                                   { yylhs.value.as < gsc::localized_string_ptr > () = std::make_unique<gsc::node_localized_string>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2579 "./S1/compiler_parser.cpp"
    break;

  case 178: // data_string: STRING
#line 537 "S1.parser.ypp"
                                { yylhs.value.as < gsc::string_ptr > () = std::make_unique<gsc::node_string>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2585 "./S1/compiler_parser.cpp"
    break;

  case 179: // animref: ANIMREF
#line 538 "S1.parser.ypp"
                                { yylhs.value.as < gsc::animref_ptr > () = std::make_unique<gsc::node_animref>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2591 "./S1/compiler_parser.cpp"
    break;

  case 180: // identifier: IDENTIFIER
#line 539 "S1.parser.ypp"
                                { yylhs.value.as < gsc::identifier_ptr > () = std::make_unique<gsc::node_identifier>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2597 "./S1/compiler_parser.cpp"
    break;

  case 181: // filepath: FILEPATH
#line 540 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::filepath_ptr > () = std::make_unique<gsc::node_filepath>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2603 "./S1/compiler_parser.cpp"
    break;

  case 182: // empty_array: EMPTY_ARRAY
#line 541 "S1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_empty_array>(std::to_string(*location)); }
#line 2609 "./S1/compiler_parser.cpp"
    break;

  case 183: // undefined: UNDEFINED
#line 542 "S1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_undefined>(std::to_string(*location)); }
#line 2615 "./S1/compiler_parser.cpp"
    break;

  case 184: // size: SIZE
#line 543 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_size>(std::to_string(*location)); }
#line 2621 "./S1/compiler_parser.cpp"
    break;

  case 185: // game: GAME
#line 544 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_game>(std::to_string(*location)); }
#line 2627 "./S1/compiler_parser.cpp"
    break;

  case 186: // self: SELF
#line 545 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_self>(std::to_string(*location)); }
#line 2633 "./S1/compiler_parser.cpp"
    break;

  case 187: // anim: ANIM
#line 546 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_anim>(std::to_string(*location)); }
#line 2639 "./S1/compiler_parser.cpp"
    break;

  case 188: // level: LEVEL
#line 547 "S1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_level>(std::to_string(*location)); }
#line 2645 "./S1/compiler_parser.cpp"
    break;


#line 2649 "./S1/compiler_parser.cpp"

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
  "ANIMREF", "STRING", "STRING_LOC", "FLOAT", "INTEGER", "IFX", "$accept",
  "root", "script", "include", "using_animtree", "animtree", "thread",
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
  "data_string", "animref", "identifier", "filepath", "empty_array",
  "undefined", "size", "game", "self", "anim", "level", YY_NULLPTR
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


  const short parser::yypact_ninf_ = -287;

  const short parser::yytable_ninf_ = -168;

  const short
  parser::yypact_[] =
  {
      13,   -41,    16,    21,  -287,    51,    13,  -287,  -287,  -287,
    -287,    27,  -287,    32,   -23,   -23,  -287,  -287,  -287,  -287,
    -287,    -9,  -287,  -287,    44,    45,   -27,  -287,    38,    46,
      52,    -9,  -287,  -287,  1526,  -287,    68,    72,   -12,    65,
      66,    85,    94,    98,    73,  1547,    36,   105,   104,    92,
      95,  -287,  -287,  -287,  -287,   108,   163,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,   103,   109,
     110,  -287,  -287,  -287,  -287,  1666,   114,   107,  -287,  -287,
    -287,  -287,  1618,  1618,  -287,   113,   115,  -287,  -287,   202,
    1618,  1618,  -287,  -287,  -287,  -287,  -287,  1618,  1638,    -9,
    -287,  1618,  1618,  -287,  -287,  -287,  2288,   112,  -287,  -287,
    -287,   -15,  -287,  -287,    15,    19,  -287,  -287,  -287,    25,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,     5,
     118,  -287,  -287,    62,    71,   187,   198,  -287,  -287,   114,
     123,  1618,   122,  -287,  -287,  1618,  -287,  -287,  -287,  -287,
    -287,    36,   128,   134,   147,   151,  1638,    -9,  -287,  -287,
    1618,  1618,  1618,  1618,  1618,  1618,  1618,  1618,  1618,  1618,
    1618,  -287,  -287,  1618,    -9,  1816,  1847,  -287,  -287,   142,
    -287,  -287,   586,  1544,  1878,  1701,   157,  1638,  2319,   -22,
    -287,  2319,  2319,  -287,  1618,  1618,  1618,  1618,  1618,  1618,
    1618,  1618,  1618,  1618,  1618,  1618,  1618,  1618,  1618,  1618,
    1618,  1618,  1618,   -18,    -9,  1618,  1909,  -287,  2071,  -287,
    -287,  1618,  1618,  1618,  1618,  2109,  -287,  2319,  2319,  2319,
    2319,  2319,  2319,  2319,  2319,  2319,  2319,  2319,   -13,   165,
    1008,   155,  1618,  1618,  1044,  -287,  1618,    41,  2071,  -287,
    1618,  2319,  2319,  2319,  2319,  2319,  2319,  2319,  2319,  2319,
    2319,  2319,  2319,  2319,  2319,  2319,  2319,  2319,  2319,  2255,
    -287,  -287,   165,  2147,   162,   168,  1743,  2184,  1940,  1785,
    -287,  -287,  1618,  1526,   205,  1526,   167,  2319,   -20,  1971,
    1526,  -287,  2221,   175,  2319,  1618,   173,  -287,   182,   180,
    1618,  1618,   185,   186,  1618,    -7,  1096,  1131,  1175,   202,
    1210,  1254,  1618,    41,  2319,   183,  1618,  -287,     2,  2002,
    -287,  -287,    61,  -287,   214,  1526,  -287,  -287,   200,  1526,
    -287,  -287,  2033,   203,  1618,    83,   193,   197,   201,  1289,
    1333,  1368,  1412,  -287,  -287,   100,  -287,  -287,  -287,  -287,
    1526,  -287,  -287,  1526,  -287,  -287,  -287,  1447,  1491,  -287,
    -287
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,   180,     0,     2,     8,     9,    10,
      11,     0,   181,     0,     0,     0,     1,     4,     5,     6,
       7,    18,    12,   178,     0,     0,     0,    17,     0,     0,
       0,     0,    13,    14,    21,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   185,   188,   187,   186,     0,     0,    20,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,     0,   160,
       0,   138,   139,   161,   162,     0,   163,     0,   167,   166,
     165,   164,     0,     0,   176,     0,     0,    70,    71,    76,
       0,     0,    72,   183,   174,   173,   182,     0,   152,     0,
      74,     0,     0,   179,   177,   175,     0,    79,    80,    81,
      82,   118,   119,   120,   121,   122,   123,   124,   125,     0,
     126,   127,   171,   172,   169,   170,   128,   129,   130,   131,
       0,   132,   133,   134,   135,   136,   137,   142,   143,     0,
       0,     0,     0,    53,    54,     0,    15,    19,    44,    42,
      43,     0,     0,     0,     0,     0,     0,     0,    83,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   140,   141,   152,     0,     0,     0,    68,    69,     0,
      75,   160,     0,     0,     0,     0,   127,   152,   151,     0,
     153,   117,   116,    73,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,     0,   144,
     145,     0,     0,     0,     0,     0,   156,    85,    91,    92,
      93,    94,    95,    86,    87,    88,    89,    90,     0,     0,
       0,     0,    78,     0,     0,   115,     0,     0,   151,   159,
       0,   114,   108,   109,    96,    97,    98,    99,   100,   101,
     102,   103,   105,   106,   107,   110,   111,   112,   113,     0,
     184,   157,   154,     0,     0,     0,     0,     0,     0,     0,
     155,   146,   152,    21,    56,    21,     0,     0,    79,     0,
      21,    62,     0,     0,   150,     0,     0,    48,     0,     0,
     152,     0,     0,     0,   152,     0,     0,     0,     0,    76,
       0,     0,     0,     0,   104,     0,   152,    51,     0,     0,
      45,    47,     0,   147,    55,    21,    60,    67,     0,    21,
      66,    61,     0,     0,   152,     0,     0,     0,     0,     0,
       0,     0,     0,   158,   168,     0,   148,    50,    52,    46,
      21,    59,    58,    21,    64,    65,   149,     0,     0,    57,
      63
  };

  const short
  parser::yypgoto_[] =
  {
    -287,  -287,  -287,   240,   242,   243,   245,  -287,  -286,   -43,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,
    -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,  -287,
     -67,  -287,   776,   -94,     1,  -287,  -287,  -287,    90,   546,
     -38,   -35,  -179,  -287,   166,   172,  -287,  -287,  -287,   248,
    -287,   -47,  -287,  -287,  -287,   217,  -287,   101,  -287,     0,
      37,  -287,  -287,  -287,   325,   378,   415,   493
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,     9,    10,    26,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
     189,   296,   198,    78,   117,   118,   119,   120,   121,   122,
      81,    82,   199,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   281,   143,   144,   145,   146
  };

  const short
  parser::yytable_[] =
  {
      11,   152,  -160,  -160,   248,   190,    11,   316,   147,   318,
      30,   148,   280,   157,   321,    31,     1,     2,     3,   259,
     260,    27,  -163,  -163,   291,  -160,   -77,   222,  -160,   260,
     333,    35,  -161,  -161,    86,   260,  -162,  -162,    13,   346,
      12,   183,   161,    47,   260,  -163,   149,   181,  -163,   350,
     182,    16,    14,   352,    47,  -161,    86,    15,  -161,  -162,
     196,    23,  -162,    21,     4,   166,  -160,  -160,   223,   104,
     105,    87,    23,     4,   367,    94,    55,   368,    22,  -167,
    -167,    28,    29,    87,    32,   149,  -163,  -163,  -166,  -166,
      34,   181,    33,    87,   182,     4,  -161,  -161,   348,    86,
    -162,  -162,  -167,   260,    92,  -167,    12,     4,    93,   200,
      97,  -166,    98,   315,  -166,    24,    25,    12,     4,   102,
     356,    99,    87,   229,    79,   260,   230,   115,    94,   149,
     100,   328,   104,   105,   101,   332,    87,   366,   153,    96,
     151,   154,   260,  -167,  -167,   150,    79,   345,   155,   158,
     183,   184,  -166,  -166,   181,   159,   160,   182,   187,   222,
     188,   149,   224,   225,   231,   355,    87,   236,   227,    36,
     232,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,   233,   249,    49,    50,   234,   252,   191,
     115,    94,   149,   295,    51,    52,    53,    54,    87,   257,
      83,   292,   156,    55,  -165,  -165,    84,   294,   307,   308,
     303,   301,   317,   319,   325,  -164,  -164,   323,   326,   344,
      47,   349,    83,   236,   282,   190,   327,  -165,    84,    87,
    -165,   330,   331,    51,    52,    53,    54,   351,  -164,   357,
     354,  -164,    55,   358,    12,     4,    17,   359,    18,    19,
      86,    20,   338,   298,    86,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,     0,     0,  -165,  -165,
       0,    84,     0,   157,   336,   157,   343,   340,   157,  -164,
    -164,     0,    85,    12,     4,     0,     0,    87,     0,     0,
       0,    87,     0,    86,     0,    86,     0,     0,     0,     0,
      86,     0,     0,     0,    85,     0,   361,   157,   364,   157,
       0,     0,     0,     0,     0,     0,    86,    86,    86,    86,
      86,    86,     0,     0,   157,   157,     0,     0,     0,     0,
      87,     0,    87,     0,     0,    86,     0,    87,     0,    86,
      79,     0,     0,     0,    79,     0,     0,   192,     0,    86,
      86,    86,    86,    87,    87,    87,    87,    87,    87,    88,
      86,     0,     0,    86,     0,     0,     0,    86,    86,     0,
       0,     0,    87,     0,     0,     0,    87,     0,     0,     0,
       0,    88,     0,    79,     0,    79,    87,    87,    87,    87,
      79,     0,     0,     0,     0,     0,     0,    87,     0,     0,
      87,     0,     0,     0,    87,    87,    79,    79,    79,   191,
      79,    79,    89,     0,     0,     0,    83,     0,     0,     0,
      83,     0,    84,     0,    88,    79,    84,     0,     0,    79,
       0,     0,     0,     0,    89,     0,     0,     0,     0,    79,
      79,    79,    79,     0,     0,     0,     0,     0,     0,    90,
      79,     0,     0,    79,     0,     0,     0,    79,    79,    83,
       0,    83,     0,     0,     0,    84,    83,    84,     0,     0,
       0,    90,    84,     0,     0,     0,     0,    89,     0,     0,
       0,     0,    83,    83,    83,    83,    83,    83,    84,    84,
      84,    84,    84,    84,     0,     0,     0,     0,    85,     0,
       0,    83,    85,     0,     0,    83,     0,    84,     0,     0,
       0,    84,     0,     0,    90,    83,    83,    83,    83,     0,
       0,    84,    84,    84,    84,     0,    83,    91,     0,    83,
       0,     0,    84,    83,    83,    84,     0,     0,     0,    84,
      84,    85,     0,    85,     0,     0,     0,     0,    85,    91,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    85,    85,   192,    85,    85,
       0,     0,     0,     0,     0,    88,     0,     0,     0,    88,
      80,     0,     0,    85,     0,     0,     0,    85,     0,     0,
       0,     0,    91,     0,     0,     0,     0,    85,    85,    85,
      85,     0,    80,     0,    47,     0,     0,     0,    85,     0,
       0,    85,     0,     0,     0,    85,    85,     0,    88,     0,
      88,     0,     0,     0,     0,    88,   166,     0,    89,   167,
       0,     0,    89,     0,     0,   168,   169,     0,     0,     0,
       0,    88,    88,    88,    88,    88,    88,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,     0,     0,
      88,     0,     0,     0,    88,    90,     0,    12,     4,    90,
       0,    89,     0,    89,    88,    88,    88,    88,    89,     0,
       0,     0,     0,     0,     0,    88,     0,     0,    88,     0,
       0,     0,    88,    88,    89,    89,    89,    89,    89,    89,
       0,     0,     0,     0,     0,     0,     0,     0,    90,     0,
      90,     0,     0,    89,     0,    90,     0,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    89,    89,
      89,    90,    90,    90,    90,    90,    90,     0,    89,     0,
       0,    89,     0,    91,     0,    89,    89,    91,     0,     0,
      90,     0,     0,     0,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    90,    90,    90,    90,     0,     0,
       0,     0,     0,     0,     0,    90,     0,     0,    90,     0,
       0,     0,    90,    90,     0,     0,    91,     0,    91,     0,
       0,     0,     0,    91,     0,     0,    80,     0,     0,     0,
      80,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      91,    91,    91,    91,    91,     0,     0,     0,     0,     0,
       0,   116,     0,     0,     0,     0,     0,     0,    91,     0,
       0,     0,    91,     0,     0,     0,     0,     0,     0,    80,
       0,    80,    91,    91,    91,    91,    80,     0,     0,     0,
       0,     0,     0,    91,     0,     0,    91,     0,     0,     0,
      91,    91,    80,    80,    80,     0,    80,    80,   185,   186,
       0,     0,     0,     0,     0,     0,   193,   194,     0,     0,
       0,    80,     0,   195,     0,    80,     0,   201,   202,     0,
       0,     0,     0,     0,     0,    80,    80,    80,    80,     0,
       0,     0,     0,     0,     0,     0,    80,     0,     0,    80,
       0,     0,     0,    80,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   226,     0,     0,
       0,   228,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   235,     0,     0,     0,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   258,     0,     0,     0,     0,     0,     0,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,     0,
       0,   283,     0,     0,     0,     0,     0,   286,   287,   288,
     289,     0,     0,     0,    36,     0,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,   297,   299,
      49,    50,   302,     0,     0,     0,   304,     0,     0,    51,
      52,    53,    54,     0,     0,     0,   293,     0,    55,     0,
      36,     0,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,     0,
       0,   324,   300,     0,    55,     0,     0,   329,     0,    12,
       4,     0,     0,     0,     0,     0,     0,     0,   342,     0,
       0,     0,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,     0,     0,    49,    50,
       0,     0,     0,     0,     0,    12,     4,    51,    52,    53,
      54,     0,     0,     0,     0,   334,    55,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    53,    54,     0,     0,     0,   335,
       0,    55,     0,     0,     0,     0,     0,    12,     4,     0,
       0,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     0,     0,    49,    50,     0,
       0,     0,     0,     0,     0,     0,    51,    52,    53,    54,
       0,     0,    12,     4,   337,    55,    36,     0,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,    51,    52,    53,    54,     0,     0,     0,     0,   339,
      55,     0,     0,     0,     0,     0,    12,     4,     0,     0,
      36,     0,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,     0,
       0,    12,     4,   341,    55,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     0,
       0,    49,    50,     0,     0,     0,     0,     0,     0,     0,
      51,    52,    53,    54,     0,     0,     0,   360,     0,    55,
       0,     0,     0,     0,     0,    12,     4,     0,     0,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,     0,     0,
      12,     4,   362,    55,    36,     0,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    53,    54,     0,     0,     0,   363,     0,    55,     0,
       0,     0,     0,     0,    12,     4,     0,     0,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,     0,     0,    49,    50,     0,     0,     0,     0,
       0,     0,     0,    51,    52,    53,    54,     0,     0,    12,
       4,   365,    55,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,    51,    52,
      53,    54,     0,     0,     0,     0,   369,    55,     0,     0,
       0,     0,     0,    12,     4,     0,     0,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    53,    54,     0,     0,    12,     4,
     370,    55,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,     0,     0,    49,    50,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,     0,     0,     0,    46,    47,    55,     0,     0,     0,
     253,     0,    12,     4,   103,   104,   105,     0,    51,    52,
      53,    54,   106,   107,     0,     0,     0,   108,     0,     0,
       0,   109,   204,   110,     0,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,     0,     0,    12,     4,     0,
       0,     0,     0,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,     0,     0,     0,   111,   112,    12,     4,
     113,    23,   114,   115,    94,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,   103,   104,   105,     0,    51,
      52,    53,    54,   106,   107,    46,    47,     0,   108,     0,
       0,     0,   109,     0,     0,   103,   104,   105,     0,    51,
      52,    53,    54,   106,   107,     0,     0,     0,   197,     0,
       0,     0,   109,   161,    47,     0,   162,   163,     0,     0,
     164,   165,     0,     0,     0,     0,     0,   111,   112,    12,
       4,   113,    23,   114,   115,    94,   166,     0,     0,   167,
       0,     0,     0,     0,     0,   168,   169,   111,   112,    12,
       4,   113,    23,   114,   115,    94,     0,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   255,     0,
       0,     0,     0,   256,     0,     0,     0,    12,     4,   204,
       0,     0,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   215,   216,   217,   218,   219,   220,   221,
     309,     0,     0,     0,     0,   310,     0,     0,     0,     0,
       0,   204,     0,     0,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,   216,   217,   218,   219,
     220,   221,   313,     0,     0,     0,     0,   314,     0,     0,
       0,     0,     0,   204,     0,     0,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,     0,     0,     0,     0,
       0,     0,     0,   250,     0,     0,     0,   215,   216,   217,
     218,   219,   220,   221,   204,     0,     0,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,     0,     0,     0,
       0,     0,     0,     0,   251,     0,     0,     0,   215,   216,
     217,   218,   219,   220,   221,   204,     0,     0,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,     0,     0,
       0,     0,     0,     0,     0,   254,     0,     0,     0,   215,
     216,   217,   218,   219,   220,   221,   204,     0,     0,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,     0,
       0,     0,     0,     0,     0,     0,   284,     0,     0,     0,
     215,   216,   217,   218,   219,   220,   221,   204,     0,     0,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
       0,     0,     0,     0,     0,     0,     0,   312,     0,     0,
       0,   215,   216,   217,   218,   219,   220,   221,   204,     0,
       0,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,     0,     0,     0,     0,     0,     0,     0,   320,     0,
       0,     0,   215,   216,   217,   218,   219,   220,   221,   204,
       0,     0,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,     0,     0,     0,     0,     0,     0,     0,   347,
       0,     0,     0,   215,   216,   217,   218,   219,   220,   221,
     204,     0,     0,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,     0,     0,     0,     0,     0,     0,     0,
     353,     0,     0,     0,   215,   216,   217,   218,   219,   220,
     221,   204,     0,     0,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   215,   216,   217,   218,   219,
     220,   221,   285,     0,     0,     0,     0,     0,     0,   204,
       0,     0,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   215,   216,   217,   218,   219,   220,   221,
     290,     0,     0,     0,     0,     0,     0,   204,     0,     0,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,   216,   217,   218,   219,   220,   221,   306,     0,
       0,     0,     0,     0,     0,   204,     0,     0,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   215,
     216,   217,   218,   219,   220,   221,   311,     0,     0,     0,
       0,     0,   204,     0,     0,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   215,   216,   217,   218,
     219,   220,   221,   322,     0,     0,     0,     0,     0,   204,
       0,     0,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   215,   216,   217,   218,   219,   220,   221,
     305,     0,     0,   204,     0,     0,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,   216,   217,
     218,   219,   220,   221,   203,     0,   204,     0,     0,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     215,   216,   217,   218,   219,   220,   221,   204,     0,     0,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,   216,   217,   218,   219,   220,   221
  };

  const short
  parser::yycheck_[] =
  {
       0,    48,    17,    18,   183,    99,     6,   293,    46,   295,
      37,    46,    30,    56,   300,    42,     3,     4,     5,    41,
      42,    21,    17,    18,    37,    40,    46,    47,    43,    42,
      37,    31,    17,    18,    34,    42,    17,    18,     1,    37,
      81,    36,    17,    18,    42,    40,    46,    85,    43,   335,
      85,     0,    36,   339,    18,    40,    56,    36,    43,    40,
     107,    84,    43,    36,    82,    40,    81,    82,    43,    28,
      29,    34,    84,    82,   360,    87,    40,   363,    46,    17,
      18,    37,    37,    46,    46,    85,    81,    82,    17,    18,
      38,   129,    46,    56,   129,    82,    81,    82,    37,    99,
      81,    82,    40,    42,    36,    43,    81,    82,    36,   109,
      45,    40,    46,   292,    43,    14,    15,    81,    82,    46,
      37,    36,    85,   161,    34,    42,   161,    86,    87,   129,
      36,   310,    28,    29,    36,   314,    99,    37,    46,    38,
      36,    46,    42,    81,    82,    40,    56,   326,    40,    46,
      36,    44,    81,    82,   192,    46,    46,   192,    45,    47,
      45,   161,    44,    40,    36,   344,   129,   167,    46,     6,
      36,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    36,   184,    22,    23,    36,    46,    99,
      86,    87,   192,    38,    31,    32,    33,    34,   161,    42,
      34,    36,    39,    40,    17,    18,    34,   250,    46,    41,
     257,   254,     7,    46,    41,    17,    18,    42,    36,    36,
      18,     7,    56,   223,   224,   319,    46,    40,    56,   192,
      43,    46,    46,    31,    32,    33,    34,    37,    40,    46,
      37,    43,    40,    46,    81,    82,     6,    46,     6,     6,
     250,     6,   319,   252,   254,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    99,    -1,    -1,    81,    82,
      -1,    99,    -1,   316,   317,   318,   323,   320,   321,    81,
      82,    -1,    34,    81,    82,    -1,    -1,   250,    -1,    -1,
      -1,   254,    -1,   293,    -1,   295,    -1,    -1,    -1,    -1,
     300,    -1,    -1,    -1,    56,    -1,   349,   350,   351,   352,
      -1,    -1,    -1,    -1,    -1,    -1,   316,   317,   318,   319,
     320,   321,    -1,    -1,   367,   368,    -1,    -1,    -1,    -1,
     293,    -1,   295,    -1,    -1,   335,    -1,   300,    -1,   339,
     250,    -1,    -1,    -1,   254,    -1,    -1,    99,    -1,   349,
     350,   351,   352,   316,   317,   318,   319,   320,   321,    34,
     360,    -1,    -1,   363,    -1,    -1,    -1,   367,   368,    -1,
      -1,    -1,   335,    -1,    -1,    -1,   339,    -1,    -1,    -1,
      -1,    56,    -1,   293,    -1,   295,   349,   350,   351,   352,
     300,    -1,    -1,    -1,    -1,    -1,    -1,   360,    -1,    -1,
     363,    -1,    -1,    -1,   367,   368,   316,   317,   318,   319,
     320,   321,    34,    -1,    -1,    -1,   250,    -1,    -1,    -1,
     254,    -1,   250,    -1,    99,   335,   254,    -1,    -1,   339,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,   349,
     350,   351,   352,    -1,    -1,    -1,    -1,    -1,    -1,    34,
     360,    -1,    -1,   363,    -1,    -1,    -1,   367,   368,   293,
      -1,   295,    -1,    -1,    -1,   293,   300,   295,    -1,    -1,
      -1,    56,   300,    -1,    -1,    -1,    -1,    99,    -1,    -1,
      -1,    -1,   316,   317,   318,   319,   320,   321,   316,   317,
     318,   319,   320,   321,    -1,    -1,    -1,    -1,   250,    -1,
      -1,   335,   254,    -1,    -1,   339,    -1,   335,    -1,    -1,
      -1,   339,    -1,    -1,    99,   349,   350,   351,   352,    -1,
      -1,   349,   350,   351,   352,    -1,   360,    34,    -1,   363,
      -1,    -1,   360,   367,   368,   363,    -1,    -1,    -1,   367,
     368,   293,    -1,   295,    -1,    -1,    -1,    -1,   300,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   316,   317,   318,   319,   320,   321,
      -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,    -1,   254,
      34,    -1,    -1,   335,    -1,    -1,    -1,   339,    -1,    -1,
      -1,    -1,    99,    -1,    -1,    -1,    -1,   349,   350,   351,
     352,    -1,    56,    -1,    18,    -1,    -1,    -1,   360,    -1,
      -1,   363,    -1,    -1,    -1,   367,   368,    -1,   293,    -1,
     295,    -1,    -1,    -1,    -1,   300,    40,    -1,   250,    43,
      -1,    -1,   254,    -1,    -1,    49,    50,    -1,    -1,    -1,
      -1,   316,   317,   318,   319,   320,   321,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    -1,    -1,
     335,    -1,    -1,    -1,   339,   250,    -1,    81,    82,   254,
      -1,   293,    -1,   295,   349,   350,   351,   352,   300,    -1,
      -1,    -1,    -1,    -1,    -1,   360,    -1,    -1,   363,    -1,
      -1,    -1,   367,   368,   316,   317,   318,   319,   320,   321,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   293,    -1,
     295,    -1,    -1,   335,    -1,   300,    -1,   339,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   349,   350,   351,
     352,   316,   317,   318,   319,   320,   321,    -1,   360,    -1,
      -1,   363,    -1,   250,    -1,   367,   368,   254,    -1,    -1,
     335,    -1,    -1,    -1,   339,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   349,   350,   351,   352,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   360,    -1,    -1,   363,    -1,
      -1,    -1,   367,   368,    -1,    -1,   293,    -1,   295,    -1,
      -1,    -1,    -1,   300,    -1,    -1,   250,    -1,    -1,    -1,
     254,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   316,
     317,   318,   319,   320,   321,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,   335,    -1,
      -1,    -1,   339,    -1,    -1,    -1,    -1,    -1,    -1,   293,
      -1,   295,   349,   350,   351,   352,   300,    -1,    -1,    -1,
      -1,    -1,    -1,   360,    -1,    -1,   363,    -1,    -1,    -1,
     367,   368,   316,   317,   318,    -1,   320,   321,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,    -1,
      -1,   335,    -1,   107,    -1,   339,    -1,   111,   112,    -1,
      -1,    -1,    -1,    -1,    -1,   349,   350,   351,   352,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   360,    -1,    -1,   363,
      -1,    -1,    -1,   367,   368,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,    -1,    -1,
      -1,   155,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   166,    -1,    -1,    -1,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   197,    -1,    -1,    -1,    -1,    -1,    -1,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,    -1,
      -1,   225,    -1,    -1,    -1,    -1,    -1,   231,   232,   233,
     234,    -1,    -1,    -1,     6,    -1,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,   252,   253,
      22,    23,   256,    -1,    -1,    -1,   260,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    38,    -1,    40,    -1,
       6,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,   305,    38,    -1,    40,    -1,    -1,   311,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   322,    -1,
      -1,    -1,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    81,    82,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,    40,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    38,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      -1,    -1,    81,    82,    39,    40,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
       6,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,
      -1,    81,    82,    39,    40,     6,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    -1,    -1,    -1,    38,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,
      81,    82,    39,    40,     6,    -1,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    38,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    -1,     6,    -1,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,    81,
      82,    39,    40,     6,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    81,    82,
      39,    40,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    -1,    17,    18,    40,    -1,    -1,    -1,
      26,    -1,    81,    82,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    44,    48,    46,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    17,    18,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    17,    18,    -1,    20,    21,    -1,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    49,    50,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    37,    -1,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    81,    82,    48,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      37,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    37,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    48,    -1,    -1,    51,    52,    53,
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
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    42,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    42,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      45,    -1,    -1,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    46,    -1,    48,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    48,    -1,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,    82,    90,    91,    92,    93,    94,
      95,   148,    81,   149,    36,    36,     0,    92,    93,    94,
      95,    36,    46,    84,   146,   146,    96,   148,    37,    37,
      37,    42,    46,    46,    38,   148,     6,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    22,
      23,    31,    32,    33,    34,    40,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   122,   127,
     128,   129,   130,   133,   134,   138,   148,   149,   153,   154,
     155,   156,    36,    36,    87,   144,   146,    45,    46,    36,
      36,    36,    46,    27,    28,    29,    35,    36,    40,    44,
      46,    79,    80,    83,    85,    86,   121,   123,   124,   125,
     126,   127,   128,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   153,   154,   155,   156,   129,   130,   148,
      40,    36,   140,    46,    46,    40,    39,    98,    46,    46,
      46,    17,    20,    21,    24,    25,    40,    43,    49,    50,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,   129,   130,    36,    44,   121,   121,    45,    45,   119,
     122,   127,   138,   121,   121,   121,   140,    40,   121,   131,
     148,   121,   121,    46,    48,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    72,    73,    74,    75,    76,
      77,    78,    47,    43,    44,    40,   121,    46,   121,   129,
     130,    36,    36,    36,    36,   121,   148,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   131,   148,
      37,    37,    46,    26,    37,    37,    42,    42,   121,    41,
      42,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
      30,   152,   148,   121,    37,    41,   121,   121,   121,   121,
      41,    37,    36,    38,    98,    38,   120,   121,   123,   121,
      38,    98,   121,   140,   121,    45,    41,    46,    41,    37,
      42,    42,    37,    37,    42,   131,    97,     7,    97,    46,
      37,    97,    42,    42,   121,    41,    36,    46,   131,   121,
      46,    46,   131,    37,    39,    38,    98,    39,   119,    39,
      98,    39,   121,   140,    36,   131,    37,    37,    37,     7,
      97,    37,    97,    37,    37,   131,    37,    46,    46,    46,
      38,    98,    39,    38,    98,    39,    37,    97,    97,    39,
      39
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    93,    94,    95,    96,    96,    96,    97,
      97,    97,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    99,    99,   100,   101,   102,   102,   103,   103,
     104,   104,   105,   106,   107,   108,   108,   109,   109,   109,
     109,   110,   110,   111,   111,   112,   112,   113,   114,   114,
     115,   116,   117,   118,   118,   119,   119,   120,   120,   121,
     121,   121,   121,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   123,   123,   123,   123,
     123,   123,   123,   123,   124,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   127,   127,
     127,   127,   128,   128,   128,   128,   129,   129,   130,   130,
     131,   131,   131,   132,   132,   133,   134,   135,   136,   137,
     138,   138,   138,   138,   138,   138,   138,   138,   139,   140,
     140,   140,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     3,     3,     4,     6,     8,     9,
       3,     1,     0,     2,     3,     4,     3,     3,     7,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     7,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
  };




#if S1DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   119,   119,   120,   124,   126,   128,   130,   132,   134,
     136,   138,   143,   148,   153,   158,   163,   165,   168,   172,
     174,   177,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   204,   206,   211,   216,   221,   223,   228,   230,
     235,   237,   242,   247,   252,   257,   259,   267,   269,   274,
     279,   289,   291,   299,   301,   310,   312,   321,   326,   328,
     333,   338,   342,   347,   349,   354,   355,   359,   360,   364,
     365,   366,   367,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   387,   388,   389,   390,
     391,   392,   393,   394,   398,   402,   403,   404,   405,   406,
     407,   408,   409,   410,   411,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   441,   442,
     443,   444,   448,   449,   450,   451,   455,   457,   462,   464,
     469,   471,   474,   478,   480,   485,   490,   495,   500,   505,
     510,   511,   512,   513,   514,   515,   516,   517,   521,   526,
     527,   528,   529,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547
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


#line 14 "S1.parser.ypp"
} // S1
#line 3875 "./S1/compiler_parser.cpp"

#line 549 "S1.parser.ypp"


void S1::parser::error(const std::string& msg)
{
    GSC_COMP_ERROR("%s", msg.data());
}
