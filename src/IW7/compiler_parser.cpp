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
#line 37 "IW7.parser.ypp"

    #include "IW7.hpp"
	#include "compiler_parser.hpp"
	#include "compiler_lexer.hpp"
	IW7::parser::symbol_type IW7lex(yyscan_t yyscanner, std::uint32_t *location);

#line 46 "./IW7/compiler_parser.cpp"

// Take the name prefix into account.
#define yylex   IW7lex



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
#if IW7DEBUG

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

#else // !IW7DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !IW7DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "IW7.parser.ypp"
namespace IW7 {
#line 129 "./IW7/compiler_parser.cpp"

  /// Build a parser object.
  parser::parser (yyscan_t yyscanner_yyarg, std::uint32_t *location_yyarg, gsc::script_ptr& astout_yyarg)
#if IW7DEBUG
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

#if IW7DEBUG
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

#if IW7DEBUG
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
#endif // IW7DEBUG

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
#line 118 "IW7.parser.ypp"
                 { astout = std::move(yystack_[0].value.as < gsc::script_ptr > ()); }
#line 1484 "./IW7/compiler_parser.cpp"
    break;

  case 3: // root: %empty
#line 119 "IW7.parser.ypp"
                 { astout = std::make_unique<gsc::node_script>(); }
#line 1490 "./IW7/compiler_parser.cpp"
    break;

  case 4: // script: script include
#line 124 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ())); }
#line 1496 "./IW7/compiler_parser.cpp"
    break;

  case 5: // script: script using_animtree
#line 126 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1502 "./IW7/compiler_parser.cpp"
    break;

  case 6: // script: script animtree
#line 128 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ())); }
#line 1508 "./IW7/compiler_parser.cpp"
    break;

  case 7: // script: script thread
#line 130 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ())); }
#line 1514 "./IW7/compiler_parser.cpp"
    break;

  case 8: // script: include
#line 132 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ()));}
#line 1520 "./IW7/compiler_parser.cpp"
    break;

  case 9: // script: using_animtree
#line 134 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1526 "./IW7/compiler_parser.cpp"
    break;

  case 10: // script: animtree
#line 136 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->animtrees.push_back(std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()));}
#line 1532 "./IW7/compiler_parser.cpp"
    break;

  case 11: // script: thread
#line 138 "IW7.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->threads.push_back(std::move(yystack_[0].value.as < gsc::thread_ptr > ()));}
#line 1538 "./IW7/compiler_parser.cpp"
    break;

  case 12: // include: INCLUDE filepath SEMICOLON
#line 143 "IW7.parser.ypp"
                { yylhs.value.as < gsc::include_ptr > () = std::make_unique<gsc::node_include>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::filepath_ptr > ())); }
#line 1544 "./IW7/compiler_parser.cpp"
    break;

  case 13: // using_animtree: USING_ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 148 "IW7.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1550 "./IW7/compiler_parser.cpp"
    break;

  case 14: // animtree: ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 153 "IW7.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1556 "./IW7/compiler_parser.cpp"
    break;

  case 15: // thread: identifier LPAREN parameters RPAREN LBRACE block RBRACE
#line 158 "IW7.parser.ypp"
                { yylhs.value.as < gsc::thread_ptr > () = std::make_unique<gsc::node_thread>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::identifier_ptr > ()), std::move(yystack_[4].value.as < gsc::parameters_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1562 "./IW7/compiler_parser.cpp"
    break;

  case 16: // parameters: parameters COMMA identifier
#line 163 "IW7.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::move(yystack_[2].value.as < gsc::parameters_ptr > ()); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1568 "./IW7/compiler_parser.cpp"
    break;

  case 17: // parameters: identifier
#line 165 "IW7.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(std::to_string(*location)); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1574 "./IW7/compiler_parser.cpp"
    break;

  case 18: // parameters: %empty
#line 167 "IW7.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(std::to_string(*location)); }
#line 1580 "./IW7/compiler_parser.cpp"
    break;

  case 19: // block: block stmt
#line 172 "IW7.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::move(yystack_[1].value.as < gsc::block_ptr > ()); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1586 "./IW7/compiler_parser.cpp"
    break;

  case 20: // block: stmt
#line 174 "IW7.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(std::to_string(*location)); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1592 "./IW7/compiler_parser.cpp"
    break;

  case 21: // block: %empty
#line 176 "IW7.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(std::to_string(*location)); }
#line 1598 "./IW7/compiler_parser.cpp"
    break;

  case 22: // stmt: stmt_call
#line 180 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_call = std::move(yystack_[0].value.as < gsc::stmt_call_ptr > ()); }
#line 1604 "./IW7/compiler_parser.cpp"
    break;

  case 23: // stmt: stmt_assign
#line 181 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < gsc::stmt_assign_ptr > ()); }
#line 1610 "./IW7/compiler_parser.cpp"
    break;

  case 24: // stmt: stmt_endon
#line 182 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < gsc::stmt_endon_ptr > ()); }
#line 1616 "./IW7/compiler_parser.cpp"
    break;

  case 25: // stmt: stmt_notify
#line 183 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < gsc::stmt_notify_ptr > ()); }
#line 1622 "./IW7/compiler_parser.cpp"
    break;

  case 26: // stmt: stmt_wait
#line 184 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < gsc::stmt_wait_ptr > ()); }
#line 1628 "./IW7/compiler_parser.cpp"
    break;

  case 27: // stmt: stmt_waittill
#line 185 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < gsc::stmt_waittill_ptr > ()); }
#line 1634 "./IW7/compiler_parser.cpp"
    break;

  case 28: // stmt: stmt_waittillmatch
#line 186 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < gsc::stmt_waittillmatch_ptr > ()); }
#line 1640 "./IW7/compiler_parser.cpp"
    break;

  case 29: // stmt: stmt_waittillframeend
#line 187 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < gsc::stmt_waittillframeend_ptr > ()); }
#line 1646 "./IW7/compiler_parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 188 "IW7.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_if = std::move(yystack_[0].value.as < gsc::stmt_if_ptr > ()); }
#line 1652 "./IW7/compiler_parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 189 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < gsc::stmt_ifelse_ptr > ()); }
#line 1658 "./IW7/compiler_parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 190 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_while = std::move(yystack_[0].value.as < gsc::stmt_while_ptr > ()); }
#line 1664 "./IW7/compiler_parser.cpp"
    break;

  case 33: // stmt: stmt_for
#line 191 "IW7.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_for = std::move(yystack_[0].value.as < gsc::stmt_for_ptr > ()); }
#line 1670 "./IW7/compiler_parser.cpp"
    break;

  case 34: // stmt: stmt_foreach
#line 192 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < gsc::stmt_foreach_ptr > ()); }
#line 1676 "./IW7/compiler_parser.cpp"
    break;

  case 35: // stmt: stmt_switch
#line 193 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < gsc::stmt_switch_ptr > ()); }
#line 1682 "./IW7/compiler_parser.cpp"
    break;

  case 36: // stmt: stmt_case
#line 194 "IW7.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_case = std::move(yystack_[0].value.as < gsc::stmt_case_ptr > ()); }
#line 1688 "./IW7/compiler_parser.cpp"
    break;

  case 37: // stmt: stmt_default
#line 195 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_default = std::move(yystack_[0].value.as < gsc::stmt_default_ptr > ()); }
#line 1694 "./IW7/compiler_parser.cpp"
    break;

  case 38: // stmt: stmt_break
#line 196 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_break = std::move(yystack_[0].value.as < gsc::stmt_break_ptr > ()); }
#line 1700 "./IW7/compiler_parser.cpp"
    break;

  case 39: // stmt: stmt_continue
#line 197 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < gsc::stmt_continue_ptr > ()); }
#line 1706 "./IW7/compiler_parser.cpp"
    break;

  case 40: // stmt: stmt_return
#line 198 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_return = std::move(yystack_[0].value.as < gsc::stmt_return_ptr > ()); }
#line 1712 "./IW7/compiler_parser.cpp"
    break;

  case 41: // stmt_call: expr_call SEMICOLON
#line 203 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1718 "./IW7/compiler_parser.cpp"
    break;

  case 42: // stmt_call: expr_call_thread SEMICOLON
#line 205 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1724 "./IW7/compiler_parser.cpp"
    break;

  case 43: // stmt_assign: expr_assign SEMICOLON
#line 210 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_assign_ptr > () = std::make_unique<gsc::node_stmt_assign>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_assign_ptr > ())); }
#line 1730 "./IW7/compiler_parser.cpp"
    break;

  case 44: // stmt_endon: object ENDON LPAREN expr RPAREN SEMICOLON
#line 215 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_endon_ptr > () = std::make_unique<gsc::node_stmt_endon>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1736 "./IW7/compiler_parser.cpp"
    break;

  case 45: // stmt_notify: object NOTIFY LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 220 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>(std::to_string(*location), std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1742 "./IW7/compiler_parser.cpp"
    break;

  case 46: // stmt_notify: object NOTIFY LPAREN expr RPAREN SEMICOLON
#line 222 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>(std::to_string(*location))); }
#line 1748 "./IW7/compiler_parser.cpp"
    break;

  case 47: // stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON
#line 227 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1754 "./IW7/compiler_parser.cpp"
    break;

  case 48: // stmt_wait: WAIT num SEMICOLON
#line 229 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1760 "./IW7/compiler_parser.cpp"
    break;

  case 49: // stmt_waittill: object WAITTILL LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 234 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>(std::to_string(*location), std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1766 "./IW7/compiler_parser.cpp"
    break;

  case 50: // stmt_waittill: object WAITTILL LPAREN expr RPAREN SEMICOLON
#line 236 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>(std::to_string(*location))); }
#line 1772 "./IW7/compiler_parser.cpp"
    break;

  case 51: // stmt_waittillmatch: object WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON
#line 241 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillmatch_ptr > () = std::make_unique<gsc::node_stmt_waittillmatch>(std::to_string(*location), std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1778 "./IW7/compiler_parser.cpp"
    break;

  case 52: // stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON
#line 246 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillframeend_ptr > () = std::make_unique<gsc::node_stmt_waittillframeend>(std::to_string(*location)); }
#line 1784 "./IW7/compiler_parser.cpp"
    break;

  case 53: // stmt_if: IF LPAREN expr RPAREN LBRACE block RBRACE
#line 251 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1790 "./IW7/compiler_parser.cpp"
    break;

  case 54: // stmt_if: IF LPAREN expr RPAREN stmt
#line 253 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1799 "./IW7/compiler_parser.cpp"
    break;

  case 55: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE LBRACE block RBRACE
#line 261 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[5].value.as < gsc::block_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1805 "./IW7/compiler_parser.cpp"
    break;

  case 56: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE block RBRACE
#line 263 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[4].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(blk), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1814 "./IW7/compiler_parser.cpp"
    break;

  case 57: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE stmt
#line 268 "IW7.parser.ypp"
                { 
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::block_ptr > ()), std::move(blk)); }
#line 1823 "./IW7/compiler_parser.cpp"
    break;

  case 58: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt
#line 273 "IW7.parser.ypp"
                {
			auto blk1 = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk1->stmts.push_back(std::move(yystack_[2].value.as < gsc::stmt_ptr > ()));
			auto blk2 = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk2->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(blk1), std::move(blk2)); }
#line 1834 "./IW7/compiler_parser.cpp"
    break;

  case 59: // stmt_while: WHILE LPAREN expr RPAREN LBRACE block RBRACE
#line 283 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1840 "./IW7/compiler_parser.cpp"
    break;

  case 60: // stmt_while: WHILE LPAREN expr RPAREN stmt
#line 285 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1849 "./IW7/compiler_parser.cpp"
    break;

  case 61: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE block RBRACE
#line 293 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>(std::to_string(*location), std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1855 "./IW7/compiler_parser.cpp"
    break;

  case 62: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt
#line 295 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1865 "./IW7/compiler_parser.cpp"
    break;

  case 63: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE block RBRACE
#line 304 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1871 "./IW7/compiler_parser.cpp"
    break;

  case 64: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt
#line 306 "IW7.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1881 "./IW7/compiler_parser.cpp"
    break;

  case 65: // stmt_switch: SWITCH LPAREN expr RPAREN LBRACE block RBRACE
#line 315 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_switch_ptr > () = std::make_unique<gsc::node_stmt_switch>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1887 "./IW7/compiler_parser.cpp"
    break;

  case 66: // stmt_case: CASE data_integer COLON
#line 320 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>(std::to_string(*location), gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::integer_ptr > ()))); }
#line 1893 "./IW7/compiler_parser.cpp"
    break;

  case 67: // stmt_case: CASE data_string COLON
#line 322 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>(std::to_string(*location), gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::string_ptr > ()))); }
#line 1899 "./IW7/compiler_parser.cpp"
    break;

  case 68: // stmt_default: DEFAULT COLON
#line 327 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_default_ptr > () = std::make_unique<gsc::node_stmt_default>(std::to_string(*location)); }
#line 1905 "./IW7/compiler_parser.cpp"
    break;

  case 69: // stmt_break: BREAK SEMICOLON
#line 332 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_break_ptr > () = std::make_unique<gsc::node_stmt_break>(std::to_string(*location)); }
#line 1911 "./IW7/compiler_parser.cpp"
    break;

  case 70: // stmt_continue: CONTINUE SEMICOLON
#line 336 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_continue_ptr > () = std::make_unique<gsc::node_stmt_continue>(std::to_string(*location)); }
#line 1917 "./IW7/compiler_parser.cpp"
    break;

  case 71: // stmt_return: RETURN expr SEMICOLON
#line 341 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 1923 "./IW7/compiler_parser.cpp"
    break;

  case 72: // stmt_return: RETURN SEMICOLON
#line 343 "IW7.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>(std::to_string(*location), std::make_unique<gsc::node>()); }
#line 1929 "./IW7/compiler_parser.cpp"
    break;

  case 73: // for_assign: expr_assign
#line 347 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_assign_ptr > ()); }
#line 1935 "./IW7/compiler_parser.cpp"
    break;

  case 74: // for_assign: %empty
#line 348 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1941 "./IW7/compiler_parser.cpp"
    break;

  case 75: // for_cond: expr_cmp
#line 352 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1947 "./IW7/compiler_parser.cpp"
    break;

  case 76: // for_cond: %empty
#line 353 "IW7.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 1953 "./IW7/compiler_parser.cpp"
    break;

  case 77: // expr: expr_cmp
#line 357 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1959 "./IW7/compiler_parser.cpp"
    break;

  case 78: // expr: expr_ternary
#line 358 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1965 "./IW7/compiler_parser.cpp"
    break;

  case 79: // expr: expr_binary
#line 359 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1971 "./IW7/compiler_parser.cpp"
    break;

  case 80: // expr: expr_primitive
#line 360 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 1977 "./IW7/compiler_parser.cpp"
    break;

  case 81: // expr_assign: object INCREMENT
#line 364 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_increment>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1983 "./IW7/compiler_parser.cpp"
    break;

  case 82: // expr_assign: object DECREMENT
#line 365 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_decrement>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1989 "./IW7/compiler_parser.cpp"
    break;

  case 83: // expr_assign: object ASSIGN expr
#line 366 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_equal>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 1995 "./IW7/compiler_parser.cpp"
    break;

  case 84: // expr_assign: object ASSIGN_BITWISE_OR expr
#line 367 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_or>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2001 "./IW7/compiler_parser.cpp"
    break;

  case 85: // expr_assign: object ASSIGN_BITWISE_AND expr
#line 368 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_and>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2007 "./IW7/compiler_parser.cpp"
    break;

  case 86: // expr_assign: object ASSIGN_BITWISE_EXOR expr
#line 369 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_exor>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2013 "./IW7/compiler_parser.cpp"
    break;

  case 87: // expr_assign: object ASSIGN_LSHIFT expr
#line 370 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_left>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()),std::move( yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2019 "./IW7/compiler_parser.cpp"
    break;

  case 88: // expr_assign: object ASSIGN_RSHIFT expr
#line 371 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_right>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2025 "./IW7/compiler_parser.cpp"
    break;

  case 89: // expr_assign: object ASSIGN_ADD expr
#line 372 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_add>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2031 "./IW7/compiler_parser.cpp"
    break;

  case 90: // expr_assign: object ASSIGN_SUB expr
#line 373 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_sub>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2037 "./IW7/compiler_parser.cpp"
    break;

  case 91: // expr_assign: object ASSIGN_MULT expr
#line 374 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mult>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2043 "./IW7/compiler_parser.cpp"
    break;

  case 92: // expr_assign: object ASSIGN_DIV expr
#line 375 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_div>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2049 "./IW7/compiler_parser.cpp"
    break;

  case 93: // expr_assign: object ASSIGN_MOD expr
#line 376 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mod>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2055 "./IW7/compiler_parser.cpp"
    break;

  case 94: // expr_cmp: expr OR expr
#line 380 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_or>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2061 "./IW7/compiler_parser.cpp"
    break;

  case 95: // expr_cmp: expr AND expr
#line 381 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_and>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2067 "./IW7/compiler_parser.cpp"
    break;

  case 96: // expr_cmp: expr EQUALITY expr
#line 382 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_equality>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2073 "./IW7/compiler_parser.cpp"
    break;

  case 97: // expr_cmp: expr INEQUALITY expr
#line 383 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_inequality>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2079 "./IW7/compiler_parser.cpp"
    break;

  case 98: // expr_cmp: expr LESS_EQUAL expr
#line 384 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less_equal>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2085 "./IW7/compiler_parser.cpp"
    break;

  case 99: // expr_cmp: expr GREATER_EQUAL expr
#line 385 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater_equal>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2091 "./IW7/compiler_parser.cpp"
    break;

  case 100: // expr_cmp: expr LESS expr
#line 386 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2097 "./IW7/compiler_parser.cpp"
    break;

  case 101: // expr_cmp: expr GREATER expr
#line 387 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2103 "./IW7/compiler_parser.cpp"
    break;

  case 102: // expr_ternary: expr_cmp QMARK expr COLON expr
#line 391 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_ternary>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2109 "./IW7/compiler_parser.cpp"
    break;

  case 103: // expr_binary: expr BITWISE_OR expr
#line 395 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_or>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2115 "./IW7/compiler_parser.cpp"
    break;

  case 104: // expr_binary: expr BITWISE_AND expr
#line 396 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_and>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2121 "./IW7/compiler_parser.cpp"
    break;

  case 105: // expr_binary: expr BITWISE_EXOR expr
#line 397 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_exor>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2127 "./IW7/compiler_parser.cpp"
    break;

  case 106: // expr_binary: expr LSHIFT expr
#line 398 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_left>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2133 "./IW7/compiler_parser.cpp"
    break;

  case 107: // expr_binary: expr RSHIFT expr
#line 399 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_right>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2139 "./IW7/compiler_parser.cpp"
    break;

  case 108: // expr_binary: expr ADD expr
#line 400 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_add>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2145 "./IW7/compiler_parser.cpp"
    break;

  case 109: // expr_binary: expr SUB expr
#line 401 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_sub>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2151 "./IW7/compiler_parser.cpp"
    break;

  case 110: // expr_binary: expr MULT expr
#line 402 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mult>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2157 "./IW7/compiler_parser.cpp"
    break;

  case 111: // expr_binary: expr DIV expr
#line 403 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_div>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2163 "./IW7/compiler_parser.cpp"
    break;

  case 112: // expr_binary: expr MOD expr
#line 404 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mod>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2169 "./IW7/compiler_parser.cpp"
    break;

  case 113: // expr_primitive: LPAREN expr RPAREN
#line 408 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[1].value.as < gsc::expr_ptr > ()); }
#line 2175 "./IW7/compiler_parser.cpp"
    break;

  case 114: // expr_primitive: COMPLEMENT expr
#line 409 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_complement>(std::to_string(*location), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2181 "./IW7/compiler_parser.cpp"
    break;

  case 115: // expr_primitive: NOT expr
#line 410 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_not>(std::to_string(*location), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2187 "./IW7/compiler_parser.cpp"
    break;

  case 116: // expr_primitive: expr_call
#line 411 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2193 "./IW7/compiler_parser.cpp"
    break;

  case 117: // expr_primitive: expr_call_thread
#line 412 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2199 "./IW7/compiler_parser.cpp"
    break;

  case 118: // expr_primitive: expr_function_ref
#line 413 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2205 "./IW7/compiler_parser.cpp"
    break;

  case 119: // expr_primitive: expr_array
#line 414 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2211 "./IW7/compiler_parser.cpp"
    break;

  case 120: // expr_primitive: expr_field
#line 415 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2217 "./IW7/compiler_parser.cpp"
    break;

  case 121: // expr_primitive: expr_size
#line 416 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2223 "./IW7/compiler_parser.cpp"
    break;

  case 122: // expr_primitive: expr_vector
#line 417 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2229 "./IW7/compiler_parser.cpp"
    break;

  case 123: // expr_primitive: expr_add_array
#line 418 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2235 "./IW7/compiler_parser.cpp"
    break;

  case 124: // expr_primitive: vector
#line 419 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2241 "./IW7/compiler_parser.cpp"
    break;

  case 125: // expr_primitive: num
#line 420 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2247 "./IW7/compiler_parser.cpp"
    break;

  case 126: // expr_primitive: data_localized_string
#line 421 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::localized_string_ptr > ()); }
#line 2253 "./IW7/compiler_parser.cpp"
    break;

  case 127: // expr_primitive: data_string
#line 422 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::string_ptr > ()); }
#line 2259 "./IW7/compiler_parser.cpp"
    break;

  case 128: // expr_primitive: animref
#line 423 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::animref_ptr > ()); }
#line 2265 "./IW7/compiler_parser.cpp"
    break;

  case 129: // expr_primitive: identifier
#line 424 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2271 "./IW7/compiler_parser.cpp"
    break;

  case 130: // expr_primitive: empty_array
#line 425 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2277 "./IW7/compiler_parser.cpp"
    break;

  case 131: // expr_primitive: undefined
#line 426 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2283 "./IW7/compiler_parser.cpp"
    break;

  case 132: // expr_primitive: game
#line 427 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2289 "./IW7/compiler_parser.cpp"
    break;

  case 133: // expr_primitive: self
#line 428 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2295 "./IW7/compiler_parser.cpp"
    break;

  case 134: // expr_primitive: anim
#line 429 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2301 "./IW7/compiler_parser.cpp"
    break;

  case 135: // expr_primitive: level
#line 430 "IW7.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2307 "./IW7/compiler_parser.cpp"
    break;

  case 136: // expr_call: expr_call_function
#line 434 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2313 "./IW7/compiler_parser.cpp"
    break;

  case 137: // expr_call: expr_call_pointer
#line 435 "IW7.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2319 "./IW7/compiler_parser.cpp"
    break;

  case 138: // expr_call: object expr_call_function
#line 436 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2325 "./IW7/compiler_parser.cpp"
    break;

  case 139: // expr_call: object expr_call_pointer
#line 437 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2331 "./IW7/compiler_parser.cpp"
    break;

  case 140: // expr_call_thread: THREAD expr_call_function
#line 441 "IW7.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2337 "./IW7/compiler_parser.cpp"
    break;

  case 141: // expr_call_thread: THREAD expr_call_pointer
#line 442 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2343 "./IW7/compiler_parser.cpp"
    break;

  case 142: // expr_call_thread: object THREAD expr_call_function
#line 443 "IW7.parser.ypp"
                                            { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2349 "./IW7/compiler_parser.cpp"
    break;

  case 143: // expr_call_thread: object THREAD expr_call_pointer
#line 444 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2355 "./IW7/compiler_parser.cpp"
    break;

  case 144: // expr_call_function: identifier LPAREN expr_arguments RPAREN
#line 449 "IW7.parser.ypp"
                {yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>(std::to_string(*location), std::make_unique<gsc::node_filepath>(std::to_string(*location), ""), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2361 "./IW7/compiler_parser.cpp"
    break;

  case 145: // expr_call_function: filepath DOUBLECOLON identifier LPAREN expr_arguments RPAREN
#line 451 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::filepath_ptr > ()), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2367 "./IW7/compiler_parser.cpp"
    break;

  case 146: // expr_call_pointer: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 456 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>(std::to_string(*location), false, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2373 "./IW7/compiler_parser.cpp"
    break;

  case 147: // expr_call_pointer: CALL LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 458 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>(std::to_string(*location), true, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2379 "./IW7/compiler_parser.cpp"
    break;

  case 148: // expr_arguments: expr_arguments COMMA expr
#line 463 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ()); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2385 "./IW7/compiler_parser.cpp"
    break;

  case 149: // expr_arguments: expr
#line 465 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(std::to_string(*location)); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2391 "./IW7/compiler_parser.cpp"
    break;

  case 150: // expr_arguments: %empty
#line 467 "IW7.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(std::to_string(*location)); }
#line 2397 "./IW7/compiler_parser.cpp"
    break;

  case 151: // expr_function_ref: DOUBLECOLON identifier
#line 472 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>(std::to_string(*location), std::make_unique<gsc::node_filepath>(std::to_string(*location), ""), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2403 "./IW7/compiler_parser.cpp"
    break;

  case 152: // expr_function_ref: filepath DOUBLECOLON identifier
#line 474 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::filepath_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2409 "./IW7/compiler_parser.cpp"
    break;

  case 153: // expr_array: object LBRACKET expr RBRACKET
#line 479 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_array>(std::to_string(*location), std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2415 "./IW7/compiler_parser.cpp"
    break;

  case 154: // expr_field: object DOT identifier
#line 484 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_field>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2421 "./IW7/compiler_parser.cpp"
    break;

  case 155: // expr_size: object DOT size
#line 489 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_size>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ())); }
#line 2427 "./IW7/compiler_parser.cpp"
    break;

  case 156: // expr_vector: LPAREN expr COMMA expr COMMA expr RPAREN
#line 494 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_vector>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2433 "./IW7/compiler_parser.cpp"
    break;

  case 157: // expr_add_array: LBRACKET expr_arguments RBRACKET
#line 499 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_add_array>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2439 "./IW7/compiler_parser.cpp"
    break;

  case 158: // object: expr_call
#line 503 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2445 "./IW7/compiler_parser.cpp"
    break;

  case 159: // object: expr_array
#line 504 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2451 "./IW7/compiler_parser.cpp"
    break;

  case 160: // object: expr_field
#line 505 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2457 "./IW7/compiler_parser.cpp"
    break;

  case 161: // object: identifier
#line 506 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2463 "./IW7/compiler_parser.cpp"
    break;

  case 162: // object: level
#line 507 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2469 "./IW7/compiler_parser.cpp"
    break;

  case 163: // object: anim
#line 508 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2475 "./IW7/compiler_parser.cpp"
    break;

  case 164: // object: self
#line 509 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2481 "./IW7/compiler_parser.cpp"
    break;

  case 165: // object: game
#line 510 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2487 "./IW7/compiler_parser.cpp"
    break;

  case 166: // vector: LPAREN num COMMA num COMMA num RPAREN
#line 515 "IW7.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_vector>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2493 "./IW7/compiler_parser.cpp"
    break;

  case 167: // num: data_float
#line 519 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::float_ptr > ()); }
#line 2499 "./IW7/compiler_parser.cpp"
    break;

  case 168: // num: data_integer
#line 520 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::integer_ptr > ()); }
#line 2505 "./IW7/compiler_parser.cpp"
    break;

  case 169: // num: false
#line 521 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2511 "./IW7/compiler_parser.cpp"
    break;

  case 170: // num: true
#line 522 "IW7.parser.ypp"
                                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2517 "./IW7/compiler_parser.cpp"
    break;

  case 171: // false: FALSE
#line 525 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>(std::to_string(*location), "0"); }
#line 2523 "./IW7/compiler_parser.cpp"
    break;

  case 172: // true: TRUE
#line 526 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_integer>(std::to_string(*location), "1"); }
#line 2529 "./IW7/compiler_parser.cpp"
    break;

  case 173: // data_float: FLOAT
#line 527 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::float_ptr > () = std::make_unique<gsc::node_float>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2535 "./IW7/compiler_parser.cpp"
    break;

  case 174: // data_integer: INTEGER
#line 528 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::integer_ptr > () = std::make_unique<gsc::node_integer>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2541 "./IW7/compiler_parser.cpp"
    break;

  case 175: // data_localized_string: STRING_LOC
#line 529 "IW7.parser.ypp"
                                   { yylhs.value.as < gsc::localized_string_ptr > () = std::make_unique<gsc::node_localized_string>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2547 "./IW7/compiler_parser.cpp"
    break;

  case 176: // data_string: STRING
#line 530 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::string_ptr > () = std::make_unique<gsc::node_string>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2553 "./IW7/compiler_parser.cpp"
    break;

  case 177: // animref: ANIMREF
#line 531 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::animref_ptr > () = std::make_unique<gsc::node_animref>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2559 "./IW7/compiler_parser.cpp"
    break;

  case 178: // identifier: IDENTIFIER
#line 532 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::identifier_ptr > () = std::make_unique<gsc::node_identifier>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2565 "./IW7/compiler_parser.cpp"
    break;

  case 179: // filepath: FILEPATH
#line 533 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::filepath_ptr > () = std::make_unique<gsc::node_filepath>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2571 "./IW7/compiler_parser.cpp"
    break;

  case 180: // empty_array: EMPTY_ARRAY
#line 534 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_empty_array>(std::to_string(*location)); }
#line 2577 "./IW7/compiler_parser.cpp"
    break;

  case 181: // undefined: UNDEFINED
#line 535 "IW7.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_undefined>(std::to_string(*location)); }
#line 2583 "./IW7/compiler_parser.cpp"
    break;

  case 182: // size: SIZE
#line 536 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_size>(std::to_string(*location)); }
#line 2589 "./IW7/compiler_parser.cpp"
    break;

  case 183: // game: GAME
#line 537 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_game>(std::to_string(*location)); }
#line 2595 "./IW7/compiler_parser.cpp"
    break;

  case 184: // self: SELF
#line 538 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_self>(std::to_string(*location)); }
#line 2601 "./IW7/compiler_parser.cpp"
    break;

  case 185: // anim: ANIM
#line 539 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_anim>(std::to_string(*location)); }
#line 2607 "./IW7/compiler_parser.cpp"
    break;

  case 186: // level: LEVEL
#line 540 "IW7.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_level>(std::to_string(*location)); }
#line 2613 "./IW7/compiler_parser.cpp"
    break;


#line 2617 "./IW7/compiler_parser.cpp"

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
  "COMPLEMENT", "FILEPATH", "IDENTIFIER", "ANIMREF", "STRING",
  "STRING_LOC", "FLOAT", "INTEGER", "IFX", "$accept", "root", "script",
  "include", "using_animtree", "animtree", "thread", "parameters", "block",
  "stmt", "stmt_call", "stmt_assign", "stmt_endon", "stmt_notify",
  "stmt_wait", "stmt_waittill", "stmt_waittillmatch",
  "stmt_waittillframeend", "stmt_if", "stmt_ifelse", "stmt_while",
  "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case", "stmt_default",
  "stmt_break", "stmt_continue", "stmt_return", "for_assign", "for_cond",
  "expr", "expr_assign", "expr_cmp", "expr_ternary", "expr_binary",
  "expr_primitive", "expr_call", "expr_call_thread", "expr_call_function",
  "expr_call_pointer", "expr_arguments", "expr_function_ref", "expr_array",
  "expr_field", "expr_size", "expr_vector", "expr_add_array", "object",
  "vector", "num", "false", "true", "data_float", "data_integer",
  "data_localized_string", "data_string", "animref", "identifier",
  "filepath", "empty_array", "undefined", "size", "game", "self", "anim",
  "level", YY_NULLPTR
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

#if IW7DEBUG
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
#if IW7DEBUG
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
#if IW7DEBUG
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


  const short parser::yypact_ninf_ = -276;

  const short parser::yytable_ninf_ = -166;

  const short
  parser::yypact_[] =
  {
       6,   -61,    -9,    12,  -276,    52,     6,  -276,  -276,  -276,
    -276,    27,  -276,    24,   -20,   -20,  -276,  -276,  -276,  -276,
    -276,   -10,  -276,  -276,    44,    54,   -18,  -276,    53,    56,
      65,   -10,  -276,  -276,  1491,  -276,    69,    80,   -32,    72,
      73,    82,    90,    93,    81,  1501,    95,   100,   152,    98,
    -276,  -276,  -276,  -276,   106,   571,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,   101,   104,   111,  -276,
    -276,  -276,  -276,  1621,   124,   117,  -276,  -276,  -276,  -276,
    1524,  1524,  -276,   126,   134,  -276,  -276,   122,  1524,  1524,
    -276,  -276,  -276,  -276,  -276,  1524,  1594,   -10,  -276,  1524,
    1524,  -276,  -276,  -276,  2234,   137,  -276,  -276,  -276,    -4,
    -276,  -276,    11,    25,  -276,  -276,  -276,    31,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,   -15,   125,  -276,
    -276,    57,    61,    91,   105,  -276,  -276,   124,   151,  1524,
     147,  -276,  1524,  -276,  -276,  -276,  -276,  -276,    95,   158,
     159,   160,   164,  1594,   -10,  -276,  -276,  1524,  1524,  1524,
    1524,  1524,  1524,  1524,  1524,  1524,  1524,  1524,  -276,  -276,
    1524,   -10,   561,  1542,  -276,  -276,   155,  -276,  -276,   149,
    1667,  1824,  1709,   165,  1594,  2265,    19,  -276,  2265,  2265,
    -276,  1524,  1524,  1524,  1524,  1524,  1524,  1524,  1524,  1524,
    1524,  1524,  1524,  1524,  1524,  1524,  1524,  1524,  1524,  1524,
     -13,   -10,  1524,  1855,  -276,  2017,  -276,  -276,  1524,  1524,
    1524,  1524,  2055,  -276,  2265,  2265,  2265,  2265,  2265,  2265,
    2265,  2265,  2265,  2265,  2265,   -11,   170,   982,   187,  1524,
    1524,  1014,  -276,  1524,     9,  2017,  -276,  1524,  2265,  2265,
    2265,  2265,  2265,  2265,  2265,  2265,  2265,  2265,  2265,  2265,
    2265,  2265,  2265,  2265,  2265,  2265,  2201,  -276,  -276,   170,
    2093,   180,   188,  1751,  2130,  1886,  1793,  -276,  -276,  1524,
    1491,   224,  1491,   189,  2265,    -5,  1917,  1491,  -276,  2167,
     191,  2265,  1524,   193,  -276,   200,   195,  1524,  1524,   196,
     197,  1524,    45,  1067,  1101,  1145,   122,  1179,  1223,  1524,
       9,  2265,   201,  1524,  -276,    88,  1948,  -276,  -276,   121,
    -276,   236,  1491,  -276,  -276,   208,  1491,  -276,  -276,  1979,
     209,  1524,   133,   203,   204,   207,  1257,  1301,  1335,  1379,
    -276,  -276,   141,  -276,  -276,  -276,  -276,  1491,  -276,  -276,
    1491,  -276,  -276,  -276,  1413,  1457,  -276,  -276
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,   178,     0,     2,     8,     9,    10,
      11,     0,   179,     0,     0,     0,     1,     4,     5,     6,
       7,    18,    12,   176,     0,     0,     0,    17,     0,     0,
       0,     0,    13,    14,    21,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     183,   186,   185,   184,     0,     0,    20,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,   158,     0,   136,
     137,   159,   160,     0,   161,     0,   165,   164,   163,   162,
       0,     0,   174,     0,     0,    68,    69,    74,     0,     0,
      70,   181,   172,   171,   180,     0,   150,     0,    72,     0,
       0,   177,   175,   173,     0,    77,    78,    79,    80,   116,
     117,   118,   119,   120,   121,   122,   123,     0,   124,   125,
     169,   170,   167,   168,   126,   127,   128,   129,     0,   130,
     131,   132,   133,   134,   135,   140,   141,     0,     0,     0,
       0,    52,     0,    15,    19,    43,    41,    42,     0,     0,
       0,     0,     0,     0,     0,    81,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     150,     0,     0,     0,    66,    67,     0,    73,   158,     0,
       0,     0,     0,   125,   150,   149,     0,   151,   115,   114,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,     0,   142,   143,     0,     0,
       0,     0,     0,   154,    83,    89,    90,    91,    92,    93,
      84,    85,    86,    87,    88,     0,     0,     0,     0,    76,
       0,     0,   113,     0,     0,   149,   157,     0,   112,   106,
     107,    94,    95,    96,    97,    98,    99,   100,   101,   103,
     104,   105,   108,   109,   110,   111,     0,   182,   155,   152,
       0,     0,     0,     0,     0,     0,     0,   153,   144,   150,
      21,    54,    21,     0,     0,    77,     0,    21,    60,     0,
       0,   148,     0,     0,    47,     0,     0,   150,     0,     0,
       0,   150,     0,     0,     0,     0,    74,     0,     0,     0,
       0,   102,     0,   150,    50,     0,     0,    44,    46,     0,
     145,    53,    21,    58,    65,     0,    21,    64,    59,     0,
       0,   150,     0,     0,     0,     0,     0,     0,     0,     0,
     156,   166,     0,   146,    49,    51,    45,    21,    57,    56,
      21,    62,    63,   147,     0,     0,    55,    61
  };

  const short
  parser::yypgoto_[] =
  {
    -276,  -276,  -276,   240,   244,   247,   248,  -276,  -275,   -43,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,   -60,
    -276,   753,   -93,     8,  -276,  -276,  -276,    76,   523,   -39,
     -38,  -175,  -276,   129,   167,  -276,  -276,  -276,   205,  -276,
     -47,  -276,  -276,  -276,   217,  -276,    18,  -276,     0,    38,
    -276,  -276,  -276,   308,   394,   432,   470
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,     9,    10,    26,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,   186,
     293,   195,    76,   115,   116,   117,   118,   119,   120,    79,
      80,   196,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   278,   141,   142,   143,   144
  };

  const short
  parser::yytable_[] =
  {
      11,   150,  -161,  -161,   187,   245,    11,   145,   146,     1,
       2,     3,   154,  -158,  -158,   313,   277,   315,    30,    12,
     180,    27,   318,    31,  -161,   288,    14,  -161,  -159,  -159,
     257,    35,    24,    25,    84,  -158,   102,   103,  -158,    13,
     -75,   219,  -160,  -160,   178,   179,   147,    15,   158,    47,
    -159,    23,    16,  -159,    92,    84,    94,   347,   193,   256,
     257,   349,    21,    23,  -160,  -161,  -161,  -160,     4,    22,
     163,     4,    85,   220,  -165,  -165,  -158,  -158,  -164,  -164,
      28,   330,   364,   147,    85,   365,   257,     4,   178,   179,
      29,  -159,  -159,    85,   113,    92,  -165,    84,    32,  -165,
    -164,    33,    34,  -164,    90,  -160,  -160,   197,  -163,  -163,
      77,    12,     4,    47,   312,    91,    95,    97,    96,   226,
     227,    85,  -162,  -162,   343,    98,   100,   147,    99,   257,
    -163,    77,   325,  -163,    54,    85,   329,  -165,  -165,   148,
      47,  -164,  -164,   151,  -162,   152,   155,  -162,   342,   156,
     178,   179,    50,    51,    52,    53,   157,   345,   147,   180,
     181,    54,   257,    81,   233,    85,   352,    47,   221,   353,
     184,  -163,  -163,   188,   257,    12,     4,   363,   185,   102,
     103,   246,   257,   219,    81,  -162,  -162,   149,   163,   147,
     222,   164,   224,   228,   229,   230,    85,   165,   166,   231,
     249,    82,    12,     4,   291,   289,   254,   300,   298,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     233,   279,    82,   187,   292,   304,    81,    85,   305,    12,
       4,   314,   320,   322,   316,   323,   341,   113,    92,    83,
     324,   327,   328,   346,   348,   351,    17,    84,   354,   355,
      18,    84,   356,    19,    20,    93,   335,   295,     0,     0,
      83,     0,     0,     0,    82,     0,     0,     0,     0,     0,
     154,   333,   154,   340,   337,   154,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,     0,     0,     0,    85,
      84,     0,    84,     0,     0,     0,     0,    84,     0,     0,
       0,     0,   189,   358,   154,   361,   154,     0,     0,     0,
       0,     0,     0,    84,    84,    84,    84,    84,    84,     0,
       0,   154,   154,    77,     0,     0,     0,    77,    85,     0,
      85,     0,    84,     0,     0,    85,    84,     0,     0,     0,
       0,     0,    86,     0,     0,     0,    84,    84,    84,    84,
       0,    85,    85,    85,    85,    85,    85,    84,     0,     0,
      84,     0,     0,    86,    84,    84,    77,     0,    77,     0,
      85,     0,     0,    77,    85,     0,    81,     0,     0,     0,
      81,     0,     0,     0,    85,    85,    85,    85,     0,    77,
      77,    77,   188,    77,    77,    85,     0,     0,    85,     0,
       0,     0,    85,    85,     0,    86,     0,     0,    77,     0,
       0,     0,    77,     0,    82,     0,     0,     0,    82,    81,
       0,    81,    77,    77,    77,    77,    81,     0,    87,     0,
       0,     0,     0,    77,     0,     0,    77,     0,     0,     0,
      77,    77,    81,    81,    81,    81,    81,    81,     0,    87,
       0,     0,    83,     0,     0,     0,    83,    82,     0,    82,
       0,    81,     0,     0,    82,    81,    88,     0,     0,     0,
       0,     0,     0,     0,     0,    81,    81,    81,    81,     0,
      82,    82,    82,    82,    82,    82,    81,    88,     0,    81,
       0,    87,     0,    81,    81,    83,     0,    83,     0,    82,
       0,     0,    83,    82,    89,     0,     0,     0,     0,     0,
       0,     0,     0,    82,    82,    82,    82,     0,    83,    83,
      83,   189,    83,    83,    82,    89,     0,    82,     0,    88,
       0,    82,    82,     0,     0,     0,     0,    83,     0,     0,
       0,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    83,    83,    83,    83,    86,     0,    78,     0,    86,
       0,     0,    83,     0,     0,    83,     0,    89,     0,    83,
      83,     0,     0,     0,     0,     0,     0,    36,    78,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,     0,     0,     0,   247,    86,     0,
      86,    50,    51,    52,    53,    86,     0,     0,   201,   153,
      54,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,    86,    86,    86,    86,    86,    86,     0,     0,     0,
       0,     0,   212,   213,   214,   215,   216,   217,   218,     0,
      86,    87,     0,     0,    86,    87,     0,     0,     0,     0,
       0,    12,     4,     0,    86,    86,    86,    86,     0,     0,
       0,     0,     0,     0,     0,    86,     0,     0,    86,     0,
       0,     0,    86,    86,     0,     0,     0,     0,     0,    88,
       0,     0,     0,    88,    87,     0,    87,     0,     0,     0,
       0,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    87,    87,    87,
      87,    87,    87,     0,     0,     0,     0,    89,     0,     0,
       0,    89,    88,     0,    88,     0,    87,     0,     0,    88,
      87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      87,    87,    87,    87,     0,    88,    88,    88,    88,    88,
      88,    87,     0,     0,    87,     0,     0,     0,    87,    87,
      89,     0,    89,     0,    88,     0,     0,    89,    88,     0,
      78,     0,     0,     0,    78,     0,     0,     0,    88,    88,
      88,    88,     0,    89,    89,    89,    89,    89,    89,    88,
       0,     0,    88,     0,     0,     0,    88,    88,   114,     0,
       0,     0,    89,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,    78,     0,    78,    89,    89,    89,    89,
      78,     0,     0,     0,     0,     0,     0,    89,     0,     0,
      89,     0,     0,     0,    89,    89,    78,    78,    78,     0,
      78,    78,     0,   182,   183,     0,     0,     0,     0,     0,
       0,   190,   191,     0,     0,    78,     0,     0,   192,    78,
       0,     0,   198,   199,     0,     0,     0,     0,     0,    78,
      78,    78,    78,     0,     0,     0,     0,     0,     0,     0,
      78,     0,     0,    78,     0,     0,     0,    78,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   223,     0,     0,   225,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   232,     0,     0,     0,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   255,     0,     0,
       0,     0,     0,     0,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,     0,     0,   280,     0,     0,     0,     0,
       0,   283,   284,   285,   286,     0,     0,     0,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,   294,   296,    49,     0,   299,     0,     0,     0,
     301,     0,    50,    51,    52,    53,     0,     0,     0,   290,
      36,    54,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     0,     0,    49,     0,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,     0,     0,
       0,   297,     0,    54,     0,   321,     0,     0,     0,     0,
       0,   326,    12,     4,     0,     0,     0,     0,     0,     0,
       0,     0,   339,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     0,     0,    49,
       0,     0,     0,     0,    12,     4,     0,    50,    51,    52,
      53,     0,     0,     0,     0,   331,    54,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,     0,     0,     0,   332,     0,
      54,     0,     0,     0,     0,     0,     0,    12,     4,     0,
       0,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     0,     0,    49,     0,     0,
       0,     0,     0,     0,     0,    50,    51,    52,    53,     0,
       0,    12,     4,   334,    54,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,    50,
      51,    52,    53,     0,     0,     0,     0,   336,    54,     0,
       0,     0,     0,     0,     0,    12,     4,     0,     0,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,     0,     0,    12,
       4,   338,    54,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     0,     0,    49,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
      53,     0,     0,     0,   357,     0,    54,     0,     0,     0,
       0,     0,     0,    12,     4,     0,     0,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,     0,     0,    12,     4,   359,
      54,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     0,     0,    49,     0,     0,
       0,     0,     0,     0,     0,    50,    51,    52,    53,     0,
       0,     0,   360,     0,    54,     0,     0,     0,     0,     0,
       0,    12,     4,     0,     0,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,    50,
      51,    52,    53,     0,     0,    12,     4,   362,    54,    36,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,     0,     0,     0,
       0,   366,    54,     0,     0,     0,     0,     0,     0,    12,
       4,     0,     0,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     0,     0,    49,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
      53,     0,     0,    12,     4,   367,    54,    36,     0,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,    49,     0,     0,     0,     0,    46,    47,
       0,    50,    51,    52,    53,     0,     0,   101,   102,   103,
      54,    50,    51,    52,    53,   104,   105,    12,     4,     0,
     106,    46,    47,     0,   107,     0,   108,     0,     0,     0,
     101,   102,   103,     0,    50,    51,    52,    53,   104,   105,
       0,     0,     0,   106,     0,     0,     0,   107,     0,     0,
       0,    12,     4,     0,     0,     0,     0,     0,   248,   109,
     110,    12,     4,   111,    23,   112,   113,    92,     0,   201,
       0,     0,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   109,   110,    12,     4,   111,    23,   112,   113,
      92,    46,    47,   212,   213,   214,   215,   216,   217,   218,
     101,   102,   103,     0,    50,    51,    52,    53,   104,   105,
       0,     0,     0,   194,     0,     0,     0,   107,   158,    47,
       0,   159,   160,     0,   161,   162,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     163,     0,     0,   164,     0,     0,     0,     0,     0,   165,
     166,     0,   109,   110,    12,     4,   111,    23,   112,   113,
      92,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   250,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   201,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   212,   213,
     214,   215,   216,   217,   218,   252,     0,     0,     0,     0,
     253,     0,     0,     0,     0,     0,   201,     0,     0,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     212,   213,   214,   215,   216,   217,   218,   306,     0,     0,
       0,     0,   307,     0,     0,     0,     0,     0,   201,     0,
       0,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   212,   213,   214,   215,   216,   217,   218,   310,
       0,     0,     0,     0,   311,     0,     0,     0,     0,     0,
     201,     0,     0,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,     0,     0,     0,     0,     0,     0,     0,
     251,     0,     0,     0,   212,   213,   214,   215,   216,   217,
     218,   201,     0,     0,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,     0,     0,     0,     0,     0,     0,
       0,   281,     0,     0,     0,   212,   213,   214,   215,   216,
     217,   218,   201,     0,     0,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,     0,     0,     0,     0,     0,
       0,     0,   309,     0,     0,     0,   212,   213,   214,   215,
     216,   217,   218,   201,     0,     0,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,     0,     0,     0,     0,
       0,     0,     0,   317,     0,     0,     0,   212,   213,   214,
     215,   216,   217,   218,   201,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,     0,     0,     0,
       0,     0,     0,     0,   344,     0,     0,     0,   212,   213,
     214,   215,   216,   217,   218,   201,     0,     0,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,     0,     0,
       0,     0,     0,     0,     0,   350,     0,     0,     0,   212,
     213,   214,   215,   216,   217,   218,   201,     0,     0,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     212,   213,   214,   215,   216,   217,   218,   282,     0,     0,
       0,     0,     0,     0,   201,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   212,   213,
     214,   215,   216,   217,   218,   287,     0,     0,     0,     0,
       0,     0,   201,     0,     0,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   212,   213,   214,   215,
     216,   217,   218,   303,     0,     0,     0,     0,     0,     0,
     201,     0,     0,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   212,   213,   214,   215,   216,   217,
     218,   308,     0,     0,     0,     0,     0,   201,     0,     0,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   212,   213,   214,   215,   216,   217,   218,   319,     0,
       0,     0,     0,     0,   201,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   212,   213,
     214,   215,   216,   217,   218,   302,     0,     0,   201,     0,
       0,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   212,   213,   214,   215,   216,   217,   218,   200,
       0,   201,     0,     0,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   212,   213,   214,   215,   216,
     217,   218,   201,     0,     0,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   212,   213,   214,   215,
     216,   217,   218
  };

  const short
  parser::yycheck_[] =
  {
       0,    48,    17,    18,    97,   180,     6,    46,    46,     3,
       4,     5,    55,    17,    18,   290,    29,   292,    36,    80,
      35,    21,   297,    41,    39,    36,    35,    42,    17,    18,
      41,    31,    14,    15,    34,    39,    27,    28,    42,     1,
      45,    46,    17,    18,    83,    83,    46,    35,    17,    18,
      39,    83,     0,    42,    86,    55,    38,   332,   105,    40,
      41,   336,    35,    83,    39,    80,    81,    42,    81,    45,
      39,    81,    34,    42,    17,    18,    80,    81,    17,    18,
      36,    36,   357,    83,    46,   360,    41,    81,   127,   127,
      36,    80,    81,    55,    85,    86,    39,    97,    45,    42,
      39,    45,    37,    42,    35,    80,    81,   107,    17,    18,
      34,    80,    81,    18,   289,    35,    44,    35,    45,   158,
     158,    83,    17,    18,    36,    35,    45,   127,    35,    41,
      39,    55,   307,    42,    39,    97,   311,    80,    81,    39,
      18,    80,    81,    45,    39,    39,    45,    42,   323,    45,
     189,   189,    30,    31,    32,    33,    45,    36,   158,    35,
      43,    39,    41,    34,   164,   127,   341,    18,    43,    36,
      44,    80,    81,    97,    41,    80,    81,    36,    44,    27,
      28,   181,    41,    46,    55,    80,    81,    35,    39,   189,
      39,    42,    45,    35,    35,    35,   158,    48,    49,    35,
      45,    34,    80,    81,   247,    35,    41,   254,   251,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
     220,   221,    55,   316,    37,    45,    97,   189,    40,    80,
      81,     7,    41,    40,    45,    35,    35,    85,    86,    34,
      45,    45,    45,     7,    36,    36,     6,   247,    45,    45,
       6,   251,    45,     6,     6,    38,   316,   249,    -1,    -1,
      55,    -1,    -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,
     313,   314,   315,   320,   317,   318,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,   251,
     290,    -1,   292,    -1,    -1,    -1,    -1,   297,    -1,    -1,
      -1,    -1,    97,   346,   347,   348,   349,    -1,    -1,    -1,
      -1,    -1,    -1,   313,   314,   315,   316,   317,   318,    -1,
      -1,   364,   365,   247,    -1,    -1,    -1,   251,   290,    -1,
     292,    -1,   332,    -1,    -1,   297,   336,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,   346,   347,   348,   349,
      -1,   313,   314,   315,   316,   317,   318,   357,    -1,    -1,
     360,    -1,    -1,    55,   364,   365,   290,    -1,   292,    -1,
     332,    -1,    -1,   297,   336,    -1,   247,    -1,    -1,    -1,
     251,    -1,    -1,    -1,   346,   347,   348,   349,    -1,   313,
     314,   315,   316,   317,   318,   357,    -1,    -1,   360,    -1,
      -1,    -1,   364,   365,    -1,    97,    -1,    -1,   332,    -1,
      -1,    -1,   336,    -1,   247,    -1,    -1,    -1,   251,   290,
      -1,   292,   346,   347,   348,   349,   297,    -1,    34,    -1,
      -1,    -1,    -1,   357,    -1,    -1,   360,    -1,    -1,    -1,
     364,   365,   313,   314,   315,   316,   317,   318,    -1,    55,
      -1,    -1,   247,    -1,    -1,    -1,   251,   290,    -1,   292,
      -1,   332,    -1,    -1,   297,   336,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   346,   347,   348,   349,    -1,
     313,   314,   315,   316,   317,   318,   357,    55,    -1,   360,
      -1,    97,    -1,   364,   365,   290,    -1,   292,    -1,   332,
      -1,    -1,   297,   336,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   346,   347,   348,   349,    -1,   313,   314,
     315,   316,   317,   318,   357,    55,    -1,   360,    -1,    97,
      -1,   364,   365,    -1,    -1,    -1,    -1,   332,    -1,    -1,
      -1,   336,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   346,   347,   348,   349,   247,    -1,    34,    -1,   251,
      -1,    -1,   357,    -1,    -1,   360,    -1,    97,    -1,   364,
     365,    -1,    -1,    -1,    -1,    -1,    -1,     6,    55,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    -1,    -1,    -1,    36,   290,    -1,
     292,    30,    31,    32,    33,   297,    -1,    -1,    47,    38,
      39,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,   313,   314,   315,   316,   317,   318,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    -1,
     332,   247,    -1,    -1,   336,   251,    -1,    -1,    -1,    -1,
      -1,    80,    81,    -1,   346,   347,   348,   349,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   357,    -1,    -1,   360,    -1,
      -1,    -1,   364,   365,    -1,    -1,    -1,    -1,    -1,   247,
      -1,    -1,    -1,   251,   290,    -1,   292,    -1,    -1,    -1,
      -1,   297,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   313,   314,   315,
     316,   317,   318,    -1,    -1,    -1,    -1,   247,    -1,    -1,
      -1,   251,   290,    -1,   292,    -1,   332,    -1,    -1,   297,
     336,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     346,   347,   348,   349,    -1,   313,   314,   315,   316,   317,
     318,   357,    -1,    -1,   360,    -1,    -1,    -1,   364,   365,
     290,    -1,   292,    -1,   332,    -1,    -1,   297,   336,    -1,
     247,    -1,    -1,    -1,   251,    -1,    -1,    -1,   346,   347,
     348,   349,    -1,   313,   314,   315,   316,   317,   318,   357,
      -1,    -1,   360,    -1,    -1,    -1,   364,   365,    45,    -1,
      -1,    -1,   332,    -1,    -1,    -1,   336,    -1,    -1,    -1,
      -1,    -1,    -1,   290,    -1,   292,   346,   347,   348,   349,
     297,    -1,    -1,    -1,    -1,    -1,    -1,   357,    -1,    -1,
     360,    -1,    -1,    -1,   364,   365,   313,   314,   315,    -1,
     317,   318,    -1,    90,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    99,    -1,    -1,   332,    -1,    -1,   105,   336,
      -1,    -1,   109,   110,    -1,    -1,    -1,    -1,    -1,   346,
     347,   348,   349,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     357,    -1,    -1,   360,    -1,    -1,    -1,   364,   365,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,    -1,    -1,   152,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   163,    -1,    -1,    -1,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   194,    -1,    -1,
      -1,    -1,    -1,    -1,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,    -1,    -1,   222,    -1,    -1,    -1,    -1,
      -1,   228,   229,   230,   231,    -1,    -1,    -1,     6,    -1,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,   249,   250,    22,    -1,   253,    -1,    -1,    -1,
     257,    -1,    30,    31,    32,    33,    -1,    -1,    -1,    37,
       6,    39,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    37,    -1,    39,    -1,   302,    -1,    -1,    -1,    -1,
      -1,   308,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   319,     6,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    80,    81,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    38,    39,     6,    -1,     8,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    -1,    37,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    -1,    -1,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    80,    81,    38,
      39,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    37,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    -1,    -1,     6,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    -1,    -1,    80,    81,    38,    39,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      81,    -1,    -1,     6,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    -1,    -1,    80,    81,    38,    39,     6,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    -1,    -1,    -1,    -1,    17,    18,
      -1,    30,    31,    32,    33,    -1,    -1,    26,    27,    28,
      39,    30,    31,    32,    33,    34,    35,    80,    81,    -1,
      39,    17,    18,    -1,    43,    -1,    45,    -1,    -1,    -1,
      26,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    36,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    -1,    47,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    17,    18,    71,    72,    73,    74,    75,    76,    77,
      26,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    17,    18,
      -1,    20,    21,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    48,
      49,    -1,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    36,    -1,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    36,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    36,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    47,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    47,    -1,    -1,    50,    51,    52,    53,    54,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    41,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    41,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    44,    -1,    -1,    47,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    45,
      -1,    47,    -1,    -1,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    47,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,    81,    89,    90,    91,    92,    93,
      94,   146,    80,   147,    35,    35,     0,    91,    92,    93,
      94,    35,    45,    83,   144,   144,    95,   146,    36,    36,
      36,    41,    45,    45,    37,   146,     6,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    22,
      30,    31,    32,    33,    39,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   120,   125,   126,   127,
     128,   131,   132,   136,   146,   147,   151,   152,   153,   154,
      35,    35,    86,   142,   144,    44,    45,    35,    35,    35,
      45,    26,    27,    28,    34,    35,    39,    43,    45,    78,
      79,    82,    84,    85,   119,   121,   122,   123,   124,   125,
     126,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   151,   152,   153,   154,   127,   128,   146,    39,    35,
     138,    45,    39,    38,    97,    45,    45,    45,    17,    20,
      21,    23,    24,    39,    42,    48,    49,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,   127,   128,
      35,    43,   119,   119,    44,    44,   117,   120,   125,   136,
     119,   119,   119,   138,    39,   119,   129,   146,   119,   119,
      45,    47,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    71,    72,    73,    74,    75,    76,    77,    46,
      42,    43,    39,   119,    45,   119,   127,   128,    35,    35,
      35,    35,   119,   146,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   129,   146,    36,    36,    45,
      25,    36,    36,    41,    41,   119,    40,    41,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,    29,   150,   146,
     119,    36,    40,   119,   119,   119,   119,    40,    36,    35,
      37,    97,    37,   118,   119,   121,   119,    37,    97,   119,
     138,   119,    44,    40,    45,    40,    36,    41,    41,    36,
      36,    41,   129,    96,     7,    96,    45,    36,    96,    41,
      41,   119,    40,    35,    45,   129,   119,    45,    45,   129,
      36,    38,    37,    97,    38,   117,    38,    97,    38,   119,
     138,    35,   129,    36,    36,    36,     7,    96,    36,    96,
      36,    36,   129,    36,    45,    45,    45,    37,    97,    38,
      37,    97,    38,    36,    96,    96,    38,    38
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    88,    89,    89,    90,    90,    90,    90,    90,    90,
      90,    90,    91,    92,    93,    94,    95,    95,    95,    96,
      96,    96,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    98,    98,    99,   100,   101,   101,   102,   102,   103,
     103,   104,   105,   106,   106,   107,   107,   107,   107,   108,
     108,   109,   109,   110,   110,   111,   112,   112,   113,   114,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   119,
     119,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   121,   121,   121,   121,   121,   121,
     121,   121,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   125,   125,   125,   125,
     126,   126,   126,   126,   127,   127,   128,   128,   129,   129,
     129,   130,   130,   131,   132,   133,   134,   135,   136,   136,
     136,   136,   136,   136,   136,   136,   137,   138,   138,   138,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154
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
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     3,     3,     4,     6,     8,     9,     3,     1,
       0,     2,     3,     4,     3,     3,     7,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     7,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
  };




#if IW7DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   118,   118,   119,   123,   125,   127,   129,   131,   133,
     135,   137,   142,   147,   152,   157,   162,   164,   167,   171,
     173,   176,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   202,   204,   209,   214,   219,   221,   226,   228,   233,
     235,   240,   245,   250,   252,   260,   262,   267,   272,   282,
     284,   292,   294,   303,   305,   314,   319,   321,   326,   331,
     335,   340,   342,   347,   348,   352,   353,   357,   358,   359,
     360,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   380,   381,   382,   383,   384,   385,
     386,   387,   391,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   434,   435,   436,   437,
     441,   442,   443,   444,   448,   450,   455,   457,   462,   464,
     467,   471,   473,   478,   483,   488,   493,   498,   503,   504,
     505,   506,   507,   508,   509,   510,   514,   519,   520,   521,
     522,   525,   526,   527,   528,   529,   530,   531,   532,   533,
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
#endif // IW7DEBUG


#line 14 "IW7.parser.ypp"
} // IW7
#line 3830 "./IW7/compiler_parser.cpp"

#line 542 "IW7.parser.ypp"


void IW7::parser::error(const std::string& msg)
{
    GSC_COMP_ERROR("%s", msg.data());
}
