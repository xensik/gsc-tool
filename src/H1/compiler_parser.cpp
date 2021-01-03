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
#line 37 "H1.parser.ypp"

    #include "H1.hpp"
	#include "compiler_parser.hpp"
	#include "compiler_lexer.hpp"
	H1::parser::symbol_type H1lex(yyscan_t yyscanner, std::uint32_t *location);

#line 46 "./H1/compiler_parser.cpp"

// Take the name prefix into account.
#define yylex   H1lex



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
#if H1DEBUG

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

#else // !H1DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !H1DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "H1.parser.ypp"
namespace H1 {
#line 129 "./H1/compiler_parser.cpp"

  /// Build a parser object.
  parser::parser (yyscan_t yyscanner_yyarg, std::uint32_t *location_yyarg, gsc::script_ptr& astout_yyarg)
#if H1DEBUG
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

      case symbol_kind::S_animtree: // animtree
        value.YY_MOVE_OR_COPY< gsc::animtree_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< gsc::block_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.YY_MOVE_OR_COPY< gsc::constant_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.YY_MOVE_OR_COPY< gsc::definition_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_data_false: // data_false
        value.YY_MOVE_OR_COPY< gsc::false_ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_number: // number
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

      case symbol_kind::S_data_true: // data_true
        value.YY_MOVE_OR_COPY< gsc::true_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_using_animtree: // using_animtree
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

      case symbol_kind::S_animtree: // animtree
        value.move< gsc::animtree_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< gsc::block_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_constant: // constant
        value.move< gsc::constant_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.move< gsc::definition_ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_data_false: // data_false
        value.move< gsc::false_ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_number: // number
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

      case symbol_kind::S_data_true: // data_true
        value.move< gsc::true_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_using_animtree: // using_animtree
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

      case symbol_kind::S_animtree: // animtree
        value.copy< gsc::animtree_ptr > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< gsc::block_ptr > (that.value);
        break;

      case symbol_kind::S_constant: // constant
        value.copy< gsc::constant_ptr > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.copy< gsc::definition_ptr > (that.value);
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

      case symbol_kind::S_data_false: // data_false
        value.copy< gsc::false_ptr > (that.value);
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
      case symbol_kind::S_number: // number
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

      case symbol_kind::S_data_true: // data_true
        value.copy< gsc::true_ptr > (that.value);
        break;

      case symbol_kind::S_using_animtree: // using_animtree
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

      case symbol_kind::S_animtree: // animtree
        value.move< gsc::animtree_ptr > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< gsc::block_ptr > (that.value);
        break;

      case symbol_kind::S_constant: // constant
        value.move< gsc::constant_ptr > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.move< gsc::definition_ptr > (that.value);
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

      case symbol_kind::S_data_false: // data_false
        value.move< gsc::false_ptr > (that.value);
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
      case symbol_kind::S_number: // number
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

      case symbol_kind::S_data_true: // data_true
        value.move< gsc::true_ptr > (that.value);
        break;

      case symbol_kind::S_using_animtree: // using_animtree
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

#if H1DEBUG
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

#if H1DEBUG
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
#endif // H1DEBUG

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

      case symbol_kind::S_animtree: // animtree
        yylhs.value.emplace< gsc::animtree_ptr > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< gsc::block_ptr > ();
        break;

      case symbol_kind::S_constant: // constant
        yylhs.value.emplace< gsc::constant_ptr > ();
        break;

      case symbol_kind::S_definition: // definition
        yylhs.value.emplace< gsc::definition_ptr > ();
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

      case symbol_kind::S_data_false: // data_false
        yylhs.value.emplace< gsc::false_ptr > ();
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
      case symbol_kind::S_number: // number
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

      case symbol_kind::S_data_true: // data_true
        yylhs.value.emplace< gsc::true_ptr > ();
        break;

      case symbol_kind::S_using_animtree: // using_animtree
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
#line 122 "H1.parser.ypp"
                 { astout = std::move(yystack_[0].value.as < gsc::script_ptr > ()); }
#line 1589 "./H1/compiler_parser.cpp"
    break;

  case 3: // root: %empty
#line 123 "H1.parser.ypp"
                 { astout = std::make_unique<gsc::node_script>(); }
#line 1595 "./H1/compiler_parser.cpp"
    break;

  case 4: // script: script include
#line 128 "H1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ())); }
#line 1601 "./H1/compiler_parser.cpp"
    break;

  case 5: // script: script definition
#line 130 "H1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::move(yystack_[1].value.as < gsc::script_ptr > ()); yylhs.value.as < gsc::script_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < gsc::definition_ptr > ())); }
#line 1607 "./H1/compiler_parser.cpp"
    break;

  case 6: // script: include
#line 132 "H1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->includes.push_back(std::move(yystack_[0].value.as < gsc::include_ptr > ()));}
#line 1613 "./H1/compiler_parser.cpp"
    break;

  case 7: // script: definition
#line 134 "H1.parser.ypp"
                { yylhs.value.as < gsc::script_ptr > () = std::make_unique<gsc::node_script>(std::to_string(*location)); yylhs.value.as < gsc::script_ptr > ()->definitions.push_back(std::move(yystack_[0].value.as < gsc::definition_ptr > ()));}
#line 1619 "./H1/compiler_parser.cpp"
    break;

  case 8: // include: INCLUDE filepath SEMICOLON
#line 139 "H1.parser.ypp"
                { yylhs.value.as < gsc::include_ptr > () = std::make_unique<gsc::node_include>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::filepath_ptr > ())); }
#line 1625 "./H1/compiler_parser.cpp"
    break;

  case 9: // definition: using_animtree
#line 143 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::definition_ptr > ().as_using_animtree = std::move(yystack_[0].value.as < gsc::using_animtree_ptr > ()); }
#line 1631 "./H1/compiler_parser.cpp"
    break;

  case 10: // definition: constant
#line 144 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::definition_ptr > ().as_constant = std::move(yystack_[0].value.as < gsc::constant_ptr > ()); }
#line 1637 "./H1/compiler_parser.cpp"
    break;

  case 11: // definition: thread
#line 145 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::definition_ptr > ().as_thread = std::move(yystack_[0].value.as < gsc::thread_ptr > ()); }
#line 1643 "./H1/compiler_parser.cpp"
    break;

  case 12: // using_animtree: USING_ANIMTREE LPAREN data_string RPAREN SEMICOLON
#line 150 "H1.parser.ypp"
                { yylhs.value.as < gsc::using_animtree_ptr > () = std::make_unique<gsc::node_using_animtree>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::string_ptr > ())); }
#line 1649 "./H1/compiler_parser.cpp"
    break;

  case 13: // constant: identifier ASSIGN expr SEMICOLON
#line 155 "H1.parser.ypp"
                { yylhs.value.as < gsc::constant_ptr > () = std::make_unique<gsc::node_constant>(std::to_string(*location), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 1655 "./H1/compiler_parser.cpp"
    break;

  case 14: // thread: identifier LPAREN parameters RPAREN LBRACE block RBRACE
#line 160 "H1.parser.ypp"
                { yylhs.value.as < gsc::thread_ptr > () = std::make_unique<gsc::node_thread>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::identifier_ptr > ()), std::move(yystack_[4].value.as < gsc::parameters_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1661 "./H1/compiler_parser.cpp"
    break;

  case 15: // parameters: parameters COMMA identifier
#line 165 "H1.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::move(yystack_[2].value.as < gsc::parameters_ptr > ()); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1667 "./H1/compiler_parser.cpp"
    break;

  case 16: // parameters: identifier
#line 167 "H1.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(std::to_string(*location)); yylhs.value.as < gsc::parameters_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 1673 "./H1/compiler_parser.cpp"
    break;

  case 17: // parameters: %empty
#line 169 "H1.parser.ypp"
                { yylhs.value.as < gsc::parameters_ptr > () = std::make_unique<gsc::node_parameters>(std::to_string(*location)); }
#line 1679 "./H1/compiler_parser.cpp"
    break;

  case 18: // block: block stmt
#line 174 "H1.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::move(yystack_[1].value.as < gsc::block_ptr > ()); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1685 "./H1/compiler_parser.cpp"
    break;

  case 19: // block: stmt
#line 176 "H1.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(std::to_string(*location)); yylhs.value.as < gsc::block_ptr > ()->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ())); }
#line 1691 "./H1/compiler_parser.cpp"
    break;

  case 20: // block: %empty
#line 178 "H1.parser.ypp"
                { yylhs.value.as < gsc::block_ptr > () = std::make_unique<gsc::node_block>(std::to_string(*location)); }
#line 1697 "./H1/compiler_parser.cpp"
    break;

  case 21: // stmt: stmt_call
#line 182 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_call = std::move(yystack_[0].value.as < gsc::stmt_call_ptr > ()); }
#line 1703 "./H1/compiler_parser.cpp"
    break;

  case 22: // stmt: stmt_assign
#line 183 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_assign = std::move(yystack_[0].value.as < gsc::stmt_assign_ptr > ()); }
#line 1709 "./H1/compiler_parser.cpp"
    break;

  case 23: // stmt: stmt_endon
#line 184 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_endon = std::move(yystack_[0].value.as < gsc::stmt_endon_ptr > ()); }
#line 1715 "./H1/compiler_parser.cpp"
    break;

  case 24: // stmt: stmt_notify
#line 185 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_notify = std::move(yystack_[0].value.as < gsc::stmt_notify_ptr > ()); }
#line 1721 "./H1/compiler_parser.cpp"
    break;

  case 25: // stmt: stmt_wait
#line 186 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_wait = std::move(yystack_[0].value.as < gsc::stmt_wait_ptr > ()); }
#line 1727 "./H1/compiler_parser.cpp"
    break;

  case 26: // stmt: stmt_waittill
#line 187 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_waittill = std::move(yystack_[0].value.as < gsc::stmt_waittill_ptr > ()); }
#line 1733 "./H1/compiler_parser.cpp"
    break;

  case 27: // stmt: stmt_waittillmatch
#line 188 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillmatch = std::move(yystack_[0].value.as < gsc::stmt_waittillmatch_ptr > ()); }
#line 1739 "./H1/compiler_parser.cpp"
    break;

  case 28: // stmt: stmt_waittillframeend
#line 189 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_waittillframeend = std::move(yystack_[0].value.as < gsc::stmt_waittillframeend_ptr > ()); }
#line 1745 "./H1/compiler_parser.cpp"
    break;

  case 29: // stmt: stmt_waitframe
#line 190 "H1.parser.ypp"
                                                                            { yylhs.value.as < gsc::stmt_ptr > ().as_waitframe = std::move(yystack_[0].value.as < gsc::stmt_waitframe_ptr > ()); }
#line 1751 "./H1/compiler_parser.cpp"
    break;

  case 30: // stmt: stmt_if
#line 191 "H1.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_if = std::move(yystack_[0].value.as < gsc::stmt_if_ptr > ()); }
#line 1757 "./H1/compiler_parser.cpp"
    break;

  case 31: // stmt: stmt_ifelse
#line 192 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_ifelse = std::move(yystack_[0].value.as < gsc::stmt_ifelse_ptr > ()); }
#line 1763 "./H1/compiler_parser.cpp"
    break;

  case 32: // stmt: stmt_while
#line 193 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_while = std::move(yystack_[0].value.as < gsc::stmt_while_ptr > ()); }
#line 1769 "./H1/compiler_parser.cpp"
    break;

  case 33: // stmt: stmt_for
#line 194 "H1.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_for = std::move(yystack_[0].value.as < gsc::stmt_for_ptr > ()); }
#line 1775 "./H1/compiler_parser.cpp"
    break;

  case 34: // stmt: stmt_foreach
#line 195 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_foreach = std::move(yystack_[0].value.as < gsc::stmt_foreach_ptr > ()); }
#line 1781 "./H1/compiler_parser.cpp"
    break;

  case 35: // stmt: stmt_switch
#line 196 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_switch = std::move(yystack_[0].value.as < gsc::stmt_switch_ptr > ()); }
#line 1787 "./H1/compiler_parser.cpp"
    break;

  case 36: // stmt: stmt_case
#line 197 "H1.parser.ypp"
                                                                                        { yylhs.value.as < gsc::stmt_ptr > ().as_case = std::move(yystack_[0].value.as < gsc::stmt_case_ptr > ()); }
#line 1793 "./H1/compiler_parser.cpp"
    break;

  case 37: // stmt: stmt_default
#line 198 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_default = std::move(yystack_[0].value.as < gsc::stmt_default_ptr > ()); }
#line 1799 "./H1/compiler_parser.cpp"
    break;

  case 38: // stmt: stmt_break
#line 199 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_break = std::move(yystack_[0].value.as < gsc::stmt_break_ptr > ()); }
#line 1805 "./H1/compiler_parser.cpp"
    break;

  case 39: // stmt: stmt_continue
#line 200 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_continue = std::move(yystack_[0].value.as < gsc::stmt_continue_ptr > ()); }
#line 1811 "./H1/compiler_parser.cpp"
    break;

  case 40: // stmt: stmt_return
#line 201 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::stmt_ptr > ().as_return = std::move(yystack_[0].value.as < gsc::stmt_return_ptr > ()); }
#line 1817 "./H1/compiler_parser.cpp"
    break;

  case 41: // stmt_call: expr_call SEMICOLON
#line 206 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1823 "./H1/compiler_parser.cpp"
    break;

  case 42: // stmt_call: expr_call_thread SEMICOLON
#line 208 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_call_ptr > () = std::make_unique<gsc::node_stmt_call>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_call_ptr > ())); }
#line 1829 "./H1/compiler_parser.cpp"
    break;

  case 43: // stmt_assign: expr_assign SEMICOLON
#line 213 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_assign_ptr > () = std::make_unique<gsc::node_stmt_assign>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_assign_ptr > ())); }
#line 1835 "./H1/compiler_parser.cpp"
    break;

  case 44: // stmt_endon: object ENDON LPAREN expr RPAREN SEMICOLON
#line 218 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_endon_ptr > () = std::make_unique<gsc::node_stmt_endon>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1841 "./H1/compiler_parser.cpp"
    break;

  case 45: // stmt_notify: object NOTIFY LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 223 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>(std::to_string(*location), std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1847 "./H1/compiler_parser.cpp"
    break;

  case 46: // stmt_notify: object NOTIFY LPAREN expr RPAREN SEMICOLON
#line 225 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_notify_ptr > () = std::make_unique<gsc::node_stmt_notify>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>(std::to_string(*location))); }
#line 1853 "./H1/compiler_parser.cpp"
    break;

  case 47: // stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON
#line 230 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1859 "./H1/compiler_parser.cpp"
    break;

  case 48: // stmt_wait: WAIT number SEMICOLON
#line 232 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_wait_ptr > () = std::make_unique<gsc::node_stmt_wait>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 1865 "./H1/compiler_parser.cpp"
    break;

  case 49: // stmt_waittill: object WAITTILL LPAREN expr COMMA expr_arguments RPAREN SEMICOLON
#line 237 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>(std::to_string(*location), std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ())); }
#line 1871 "./H1/compiler_parser.cpp"
    break;

  case 50: // stmt_waittill: object WAITTILL LPAREN expr RPAREN SEMICOLON
#line 239 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittill_ptr > () = std::make_unique<gsc::node_stmt_waittill>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::make_unique<gsc::node_expr_arguments>(std::to_string(*location))); }
#line 1877 "./H1/compiler_parser.cpp"
    break;

  case 51: // stmt_waittillmatch: object WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON
#line 244 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillmatch_ptr > () = std::make_unique<gsc::node_stmt_waittillmatch>(std::to_string(*location), std::move(yystack_[7].value.as < gsc::node_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ())); }
#line 1883 "./H1/compiler_parser.cpp"
    break;

  case 52: // stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON
#line 249 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waittillframeend_ptr > () = std::make_unique<gsc::node_stmt_waittillframeend>(std::to_string(*location)); }
#line 1889 "./H1/compiler_parser.cpp"
    break;

  case 53: // stmt_waitframe: WAITFRAME SEMICOLON
#line 254 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_waitframe_ptr > () = std::make_unique<gsc::node_stmt_waitframe>(std::to_string(*location)); }
#line 1895 "./H1/compiler_parser.cpp"
    break;

  case 54: // stmt_if: IF LPAREN expr RPAREN LBRACE block RBRACE
#line 259 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1901 "./H1/compiler_parser.cpp"
    break;

  case 55: // stmt_if: IF LPAREN expr RPAREN stmt
#line 261 "H1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_if_ptr > () = std::make_unique<gsc::node_stmt_if>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1910 "./H1/compiler_parser.cpp"
    break;

  case 56: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE LBRACE block RBRACE
#line 269 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[5].value.as < gsc::block_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1916 "./H1/compiler_parser.cpp"
    break;

  case 57: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE block RBRACE
#line 271 "H1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[4].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(blk), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1925 "./H1/compiler_parser.cpp"
    break;

  case 58: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE block RBRACE ELSE stmt
#line 276 "H1.parser.ypp"
                { 
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::block_ptr > ()), std::move(blk)); }
#line 1934 "./H1/compiler_parser.cpp"
    break;

  case 59: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt
#line 281 "H1.parser.ypp"
                {
			auto blk1 = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk1->stmts.push_back(std::move(yystack_[2].value.as < gsc::stmt_ptr > ()));
			auto blk2 = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk2->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_ifelse_ptr > () = std::make_unique<gsc::node_stmt_ifelse>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(blk1), std::move(blk2)); }
#line 1945 "./H1/compiler_parser.cpp"
    break;

  case 60: // stmt_while: WHILE LPAREN expr RPAREN LBRACE block RBRACE
#line 291 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1951 "./H1/compiler_parser.cpp"
    break;

  case 61: // stmt_while: WHILE LPAREN expr RPAREN stmt
#line 293 "H1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_while_ptr > () = std::make_unique<gsc::node_stmt_while>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk)); }
#line 1960 "./H1/compiler_parser.cpp"
    break;

  case 62: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE block RBRACE
#line 301 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>(std::to_string(*location), std::move(yystack_[8].value.as < gsc::expr_ptr > ()), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1966 "./H1/compiler_parser.cpp"
    break;

  case 63: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt
#line 303 "H1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_for_ptr > () = std::make_unique<gsc::node_stmt_for>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1976 "./H1/compiler_parser.cpp"
    break;

  case 64: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE block RBRACE
#line 312 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>(std::to_string(*location), std::move(yystack_[6].value.as < gsc::expr_ptr > ()), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1982 "./H1/compiler_parser.cpp"
    break;

  case 65: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt
#line 314 "H1.parser.ypp"
                {
			auto blk = std::make_unique<gsc::node_block>(std::to_string(*location));
			blk->stmts.push_back(std::move(yystack_[0].value.as < gsc::stmt_ptr > ()));
			yylhs.value.as < gsc::stmt_foreach_ptr > () = std::make_unique<gsc::node_stmt_foreach>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(blk));
		}
#line 1992 "./H1/compiler_parser.cpp"
    break;

  case 66: // stmt_switch: SWITCH LPAREN expr RPAREN LBRACE block RBRACE
#line 323 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_switch_ptr > () = std::make_unique<gsc::node_stmt_switch>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::block_ptr > ())); }
#line 1998 "./H1/compiler_parser.cpp"
    break;

  case 67: // stmt_case: CASE data_integer COLON
#line 328 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>(std::to_string(*location), gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::integer_ptr > ()))); }
#line 2004 "./H1/compiler_parser.cpp"
    break;

  case 68: // stmt_case: CASE data_string COLON
#line 330 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_case_ptr > () = std::make_unique<gsc::node_stmt_case>(std::to_string(*location), gsc::expr_ptr(std::move(yystack_[1].value.as < gsc::string_ptr > ()))); }
#line 2010 "./H1/compiler_parser.cpp"
    break;

  case 69: // stmt_default: DEFAULT COLON
#line 335 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_default_ptr > () = std::make_unique<gsc::node_stmt_default>(std::to_string(*location)); }
#line 2016 "./H1/compiler_parser.cpp"
    break;

  case 70: // stmt_break: BREAK SEMICOLON
#line 340 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_break_ptr > () = std::make_unique<gsc::node_stmt_break>(std::to_string(*location)); }
#line 2022 "./H1/compiler_parser.cpp"
    break;

  case 71: // stmt_continue: CONTINUE SEMICOLON
#line 344 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_continue_ptr > () = std::make_unique<gsc::node_stmt_continue>(std::to_string(*location)); }
#line 2028 "./H1/compiler_parser.cpp"
    break;

  case 72: // stmt_return: RETURN expr SEMICOLON
#line 349 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2034 "./H1/compiler_parser.cpp"
    break;

  case 73: // stmt_return: RETURN SEMICOLON
#line 351 "H1.parser.ypp"
                { yylhs.value.as < gsc::stmt_return_ptr > () = std::make_unique<gsc::node_stmt_return>(std::to_string(*location), std::make_unique<gsc::node>()); }
#line 2040 "./H1/compiler_parser.cpp"
    break;

  case 74: // for_assign: expr_assign
#line 355 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_assign_ptr > ()); }
#line 2046 "./H1/compiler_parser.cpp"
    break;

  case 75: // for_assign: %empty
#line 356 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 2052 "./H1/compiler_parser.cpp"
    break;

  case 76: // for_cond: expr_cmp
#line 360 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 2058 "./H1/compiler_parser.cpp"
    break;

  case 77: // for_cond: %empty
#line 361 "H1.parser.ypp"
                                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node>(); }
#line 2064 "./H1/compiler_parser.cpp"
    break;

  case 78: // expr: expr_cmp
#line 365 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 2070 "./H1/compiler_parser.cpp"
    break;

  case 79: // expr: expr_ternary
#line 366 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 2076 "./H1/compiler_parser.cpp"
    break;

  case 80: // expr: expr_binary
#line 367 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 2082 "./H1/compiler_parser.cpp"
    break;

  case 81: // expr: expr_primitive
#line 368 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[0].value.as < gsc::expr_ptr > ()); }
#line 2088 "./H1/compiler_parser.cpp"
    break;

  case 82: // expr_assign: object INCREMENT
#line 372 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_increment>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2094 "./H1/compiler_parser.cpp"
    break;

  case 83: // expr_assign: object DECREMENT
#line 373 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_decrement>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2100 "./H1/compiler_parser.cpp"
    break;

  case 84: // expr_assign: object ASSIGN expr
#line 374 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_equal>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2106 "./H1/compiler_parser.cpp"
    break;

  case 85: // expr_assign: object ASSIGN_BITWISE_OR expr
#line 375 "H1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_or>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2112 "./H1/compiler_parser.cpp"
    break;

  case 86: // expr_assign: object ASSIGN_BITWISE_AND expr
#line 376 "H1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_and>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2118 "./H1/compiler_parser.cpp"
    break;

  case 87: // expr_assign: object ASSIGN_BITWISE_EXOR expr
#line 377 "H1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_bitwise_exor>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2124 "./H1/compiler_parser.cpp"
    break;

  case 88: // expr_assign: object ASSIGN_LSHIFT expr
#line 378 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_left>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()),std::move( yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2130 "./H1/compiler_parser.cpp"
    break;

  case 89: // expr_assign: object ASSIGN_RSHIFT expr
#line 379 "H1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_shift_right>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2136 "./H1/compiler_parser.cpp"
    break;

  case 90: // expr_assign: object ASSIGN_ADD expr
#line 380 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_add>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2142 "./H1/compiler_parser.cpp"
    break;

  case 91: // expr_assign: object ASSIGN_SUB expr
#line 381 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_sub>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2148 "./H1/compiler_parser.cpp"
    break;

  case 92: // expr_assign: object ASSIGN_MULT expr
#line 382 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mult>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2154 "./H1/compiler_parser.cpp"
    break;

  case 93: // expr_assign: object ASSIGN_DIV expr
#line 383 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_div>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2160 "./H1/compiler_parser.cpp"
    break;

  case 94: // expr_assign: object ASSIGN_MOD expr
#line 384 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_assign_ptr > () = std::make_unique<gsc::node_expr_assign_mod>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2166 "./H1/compiler_parser.cpp"
    break;

  case 95: // expr_cmp: expr OR expr
#line 388 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_or>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2172 "./H1/compiler_parser.cpp"
    break;

  case 96: // expr_cmp: expr AND expr
#line 389 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_and>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2178 "./H1/compiler_parser.cpp"
    break;

  case 97: // expr_cmp: expr EQUALITY expr
#line 390 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_equality>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2184 "./H1/compiler_parser.cpp"
    break;

  case 98: // expr_cmp: expr INEQUALITY expr
#line 391 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_inequality>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2190 "./H1/compiler_parser.cpp"
    break;

  case 99: // expr_cmp: expr LESS_EQUAL expr
#line 392 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less_equal>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2196 "./H1/compiler_parser.cpp"
    break;

  case 100: // expr_cmp: expr GREATER_EQUAL expr
#line 393 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater_equal>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2202 "./H1/compiler_parser.cpp"
    break;

  case 101: // expr_cmp: expr LESS expr
#line 394 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_less>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2208 "./H1/compiler_parser.cpp"
    break;

  case 102: // expr_cmp: expr GREATER expr
#line 395 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_greater>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2214 "./H1/compiler_parser.cpp"
    break;

  case 103: // expr_ternary: expr_cmp QMARK expr COLON expr
#line 399 "H1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_ternary>(std::to_string(*location), std::move(yystack_[4].value.as < gsc::expr_ptr > ()), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2220 "./H1/compiler_parser.cpp"
    break;

  case 104: // expr_binary: expr BITWISE_OR expr
#line 403 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_or>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2226 "./H1/compiler_parser.cpp"
    break;

  case 105: // expr_binary: expr BITWISE_AND expr
#line 404 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_and>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2232 "./H1/compiler_parser.cpp"
    break;

  case 106: // expr_binary: expr BITWISE_EXOR expr
#line 405 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_bitwise_exor>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2238 "./H1/compiler_parser.cpp"
    break;

  case 107: // expr_binary: expr LSHIFT expr
#line 406 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_left>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2244 "./H1/compiler_parser.cpp"
    break;

  case 108: // expr_binary: expr RSHIFT expr
#line 407 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_shift_right>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2250 "./H1/compiler_parser.cpp"
    break;

  case 109: // expr_binary: expr ADD expr
#line 408 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_add>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2256 "./H1/compiler_parser.cpp"
    break;

  case 110: // expr_binary: expr SUB expr
#line 409 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_sub>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2262 "./H1/compiler_parser.cpp"
    break;

  case 111: // expr_binary: expr MULT expr
#line 410 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mult>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2268 "./H1/compiler_parser.cpp"
    break;

  case 112: // expr_binary: expr DIV expr
#line 411 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_div>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2274 "./H1/compiler_parser.cpp"
    break;

  case 113: // expr_binary: expr MOD expr
#line 412 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_mod>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::expr_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2280 "./H1/compiler_parser.cpp"
    break;

  case 114: // expr_primitive: LPAREN expr RPAREN
#line 416 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > () = std::move(yystack_[1].value.as < gsc::expr_ptr > ()); }
#line 2286 "./H1/compiler_parser.cpp"
    break;

  case 115: // expr_primitive: COMPLEMENT expr
#line 417 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_complement>(std::to_string(*location), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2292 "./H1/compiler_parser.cpp"
    break;

  case 116: // expr_primitive: NOT expr
#line 418 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::make_unique<gsc::node_expr_not>(std::to_string(*location), std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2298 "./H1/compiler_parser.cpp"
    break;

  case 117: // expr_primitive: expr_call
#line 419 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2304 "./H1/compiler_parser.cpp"
    break;

  case 118: // expr_primitive: expr_call_thread
#line 420 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2310 "./H1/compiler_parser.cpp"
    break;

  case 119: // expr_primitive: expr_function_ref
#line 421 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2316 "./H1/compiler_parser.cpp"
    break;

  case 120: // expr_primitive: expr_array
#line 422 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2322 "./H1/compiler_parser.cpp"
    break;

  case 121: // expr_primitive: expr_field
#line 423 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2328 "./H1/compiler_parser.cpp"
    break;

  case 122: // expr_primitive: expr_size
#line 424 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2334 "./H1/compiler_parser.cpp"
    break;

  case 123: // expr_primitive: expr_vector
#line 425 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2340 "./H1/compiler_parser.cpp"
    break;

  case 124: // expr_primitive: expr_add_array
#line 426 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2346 "./H1/compiler_parser.cpp"
    break;

  case 125: // expr_primitive: vector
#line 427 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2352 "./H1/compiler_parser.cpp"
    break;

  case 126: // expr_primitive: number
#line 428 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2358 "./H1/compiler_parser.cpp"
    break;

  case 127: // expr_primitive: data_localized_string
#line 429 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::localized_string_ptr > ()); }
#line 2364 "./H1/compiler_parser.cpp"
    break;

  case 128: // expr_primitive: data_string
#line 430 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::string_ptr > ()); }
#line 2370 "./H1/compiler_parser.cpp"
    break;

  case 129: // expr_primitive: data_false
#line 431 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::false_ptr > ()); }
#line 2376 "./H1/compiler_parser.cpp"
    break;

  case 130: // expr_primitive: data_true
#line 432 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::true_ptr > ()); }
#line 2382 "./H1/compiler_parser.cpp"
    break;

  case 131: // expr_primitive: animref
#line 433 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::animref_ptr > ()); }
#line 2388 "./H1/compiler_parser.cpp"
    break;

  case 132: // expr_primitive: animtree
#line 434 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::animtree_ptr > ()); }
#line 2394 "./H1/compiler_parser.cpp"
    break;

  case 133: // expr_primitive: identifier
#line 435 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2400 "./H1/compiler_parser.cpp"
    break;

  case 134: // expr_primitive: empty_array
#line 436 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2406 "./H1/compiler_parser.cpp"
    break;

  case 135: // expr_primitive: undefined
#line 437 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2412 "./H1/compiler_parser.cpp"
    break;

  case 136: // expr_primitive: game
#line 438 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2418 "./H1/compiler_parser.cpp"
    break;

  case 137: // expr_primitive: self
#line 439 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2424 "./H1/compiler_parser.cpp"
    break;

  case 138: // expr_primitive: anim
#line 440 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2430 "./H1/compiler_parser.cpp"
    break;

  case 139: // expr_primitive: level
#line 441 "H1.parser.ypp"
                                                                        { yylhs.value.as < gsc::expr_ptr > ().as_node = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2436 "./H1/compiler_parser.cpp"
    break;

  case 140: // expr_call: expr_call_function
#line 445 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2442 "./H1/compiler_parser.cpp"
    break;

  case 141: // expr_call: expr_call_pointer
#line 446 "H1.parser.ypp"
                                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2448 "./H1/compiler_parser.cpp"
    break;

  case 142: // expr_call: object expr_call_function
#line 447 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2454 "./H1/compiler_parser.cpp"
    break;

  case 143: // expr_call: object expr_call_pointer
#line 448 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), false, std::move(yystack_[1].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2460 "./H1/compiler_parser.cpp"
    break;

  case 144: // expr_call_thread: THREAD expr_call_function
#line 452 "H1.parser.ypp"
                                                        { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2466 "./H1/compiler_parser.cpp"
    break;

  case 145: // expr_call_thread: THREAD expr_call_pointer
#line 453 "H1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::make_unique<gsc::node>(), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2472 "./H1/compiler_parser.cpp"
    break;

  case 146: // expr_call_thread: object THREAD expr_call_function
#line 454 "H1.parser.ypp"
                                            { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2478 "./H1/compiler_parser.cpp"
    break;

  case 147: // expr_call_thread: object THREAD expr_call_pointer
#line 455 "H1.parser.ypp"
                                                { yylhs.value.as < gsc::expr_call_ptr > () = std::make_unique<gsc::node_expr_call>(std::to_string(*location), true, std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::expr_call_type_ptr > ())); }
#line 2484 "./H1/compiler_parser.cpp"
    break;

  case 148: // expr_call_function: identifier LPAREN expr_arguments RPAREN
#line 460 "H1.parser.ypp"
                {yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>(std::to_string(*location), std::make_unique<gsc::node_filepath>(std::to_string(*location), ""), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2490 "./H1/compiler_parser.cpp"
    break;

  case 149: // expr_call_function: filepath DOUBLECOLON identifier LPAREN expr_arguments RPAREN
#line 462 "H1.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_func = std::make_unique<gsc::node_expr_call_function>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::filepath_ptr > ()), std::move(yystack_[3].value.as < gsc::identifier_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2496 "./H1/compiler_parser.cpp"
    break;

  case 150: // expr_call_pointer: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 467 "H1.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>(std::to_string(*location), false, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2502 "./H1/compiler_parser.cpp"
    break;

  case 151: // expr_call_pointer: CALL LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments RPAREN
#line 469 "H1.parser.ypp"
                { yylhs.value.as < gsc::expr_call_type_ptr > ().as_pointer = std::make_unique<gsc::node_expr_call_pointer>(std::to_string(*location), true, std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2508 "./H1/compiler_parser.cpp"
    break;

  case 152: // expr_arguments: expr_arguments COMMA expr
#line 474 "H1.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::move(yystack_[2].value.as < gsc::expr_arguments_ptr > ()); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2514 "./H1/compiler_parser.cpp"
    break;

  case 153: // expr_arguments: expr
#line 476 "H1.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(std::to_string(*location)); yylhs.value.as < gsc::expr_arguments_ptr > ()->list.push_back(std::move(yystack_[0].value.as < gsc::expr_ptr > ())); }
#line 2520 "./H1/compiler_parser.cpp"
    break;

  case 154: // expr_arguments: %empty
#line 478 "H1.parser.ypp"
                { yylhs.value.as < gsc::expr_arguments_ptr > () = std::make_unique<gsc::node_expr_arguments>(std::to_string(*location)); }
#line 2526 "./H1/compiler_parser.cpp"
    break;

  case 155: // expr_function_ref: DOUBLECOLON identifier
#line 483 "H1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>(std::to_string(*location), std::make_unique<gsc::node_filepath>(std::to_string(*location), ""), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2532 "./H1/compiler_parser.cpp"
    break;

  case 156: // expr_function_ref: filepath DOUBLECOLON identifier
#line 485 "H1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_function_ref>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::filepath_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2538 "./H1/compiler_parser.cpp"
    break;

  case 157: // expr_array: object LBRACKET expr RBRACKET
#line 490 "H1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_array>(std::to_string(*location), std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2544 "./H1/compiler_parser.cpp"
    break;

  case 158: // expr_field: object DOT identifier
#line 495 "H1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_field>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ()), std::move(yystack_[0].value.as < gsc::identifier_ptr > ())); }
#line 2550 "./H1/compiler_parser.cpp"
    break;

  case 159: // expr_size: object DOT size
#line 500 "H1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_size>(std::to_string(*location), std::move(yystack_[2].value.as < gsc::node_ptr > ())); }
#line 2556 "./H1/compiler_parser.cpp"
    break;

  case 160: // expr_vector: LPAREN expr COMMA expr COMMA expr RPAREN
#line 505 "H1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_vector>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::expr_ptr > ()), std::move(yystack_[3].value.as < gsc::expr_ptr > ()), std::move(yystack_[1].value.as < gsc::expr_ptr > ())); }
#line 2562 "./H1/compiler_parser.cpp"
    break;

  case 161: // expr_add_array: LBRACKET expr_arguments RBRACKET
#line 510 "H1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_expr_add_array>(std::to_string(*location), std::move(yystack_[1].value.as < gsc::expr_arguments_ptr > ())); }
#line 2568 "./H1/compiler_parser.cpp"
    break;

  case 162: // object: expr_call
#line 514 "H1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::expr_call_ptr > ()); }
#line 2574 "./H1/compiler_parser.cpp"
    break;

  case 163: // object: expr_array
#line 515 "H1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2580 "./H1/compiler_parser.cpp"
    break;

  case 164: // object: expr_field
#line 516 "H1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2586 "./H1/compiler_parser.cpp"
    break;

  case 165: // object: identifier
#line 517 "H1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::identifier_ptr > ()); }
#line 2592 "./H1/compiler_parser.cpp"
    break;

  case 166: // object: level
#line 518 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2598 "./H1/compiler_parser.cpp"
    break;

  case 167: // object: anim
#line 519 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2604 "./H1/compiler_parser.cpp"
    break;

  case 168: // object: self
#line 520 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2610 "./H1/compiler_parser.cpp"
    break;

  case 169: // object: game
#line 521 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::node_ptr > ()); }
#line 2616 "./H1/compiler_parser.cpp"
    break;

  case 170: // vector: LPAREN number COMMA number COMMA number RPAREN
#line 526 "H1.parser.ypp"
                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_vector>(std::to_string(*location), std::move(yystack_[5].value.as < gsc::node_ptr > ()), std::move(yystack_[3].value.as < gsc::node_ptr > ()), std::move(yystack_[1].value.as < gsc::node_ptr > ())); }
#line 2622 "./H1/compiler_parser.cpp"
    break;

  case 171: // number: data_float
#line 530 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::float_ptr > ()); }
#line 2628 "./H1/compiler_parser.cpp"
    break;

  case 172: // number: data_integer
#line 531 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::move(yystack_[0].value.as < gsc::integer_ptr > ()); }
#line 2634 "./H1/compiler_parser.cpp"
    break;

  case 173: // data_false: FALSE
#line 534 "H1.parser.ypp"
                                { yylhs.value.as < gsc::false_ptr > () = std::make_unique<gsc::node_false>(std::to_string(*location)); }
#line 2640 "./H1/compiler_parser.cpp"
    break;

  case 174: // data_true: TRUE
#line 535 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::true_ptr > () = std::make_unique<gsc::node_true>(std::to_string(*location)); }
#line 2646 "./H1/compiler_parser.cpp"
    break;

  case 175: // data_float: FLOAT
#line 536 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::float_ptr > () = std::make_unique<gsc::node_float>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2652 "./H1/compiler_parser.cpp"
    break;

  case 176: // data_integer: INTEGER
#line 537 "H1.parser.ypp"
                                { yylhs.value.as < gsc::integer_ptr > () = std::make_unique<gsc::node_integer>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2658 "./H1/compiler_parser.cpp"
    break;

  case 177: // data_localized_string: STRING_LOC
#line 538 "H1.parser.ypp"
                                   { yylhs.value.as < gsc::localized_string_ptr > () = std::make_unique<gsc::node_localized_string>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2664 "./H1/compiler_parser.cpp"
    break;

  case 178: // data_string: STRING
#line 539 "H1.parser.ypp"
                                { yylhs.value.as < gsc::string_ptr > () = std::make_unique<gsc::node_string>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2670 "./H1/compiler_parser.cpp"
    break;

  case 179: // animref: ANIMREF
#line 540 "H1.parser.ypp"
                                { yylhs.value.as < gsc::animref_ptr > () = std::make_unique<gsc::node_animref>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2676 "./H1/compiler_parser.cpp"
    break;

  case 180: // animtree: ANIMTREE
#line 541 "H1.parser.ypp"
                                { yylhs.value.as < gsc::animtree_ptr > () = std::make_unique<gsc::node_animtree>(std::to_string(*location)); }
#line 2682 "./H1/compiler_parser.cpp"
    break;

  case 181: // identifier: IDENTIFIER
#line 542 "H1.parser.ypp"
                                { yylhs.value.as < gsc::identifier_ptr > () = std::make_unique<gsc::node_identifier>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2688 "./H1/compiler_parser.cpp"
    break;

  case 182: // filepath: FILEPATH
#line 543 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::filepath_ptr > () = std::make_unique<gsc::node_filepath>(std::to_string(*location), yystack_[0].value.as < std::string > ()); }
#line 2694 "./H1/compiler_parser.cpp"
    break;

  case 183: // empty_array: EMPTY_ARRAY
#line 544 "H1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_empty_array>(std::to_string(*location)); }
#line 2700 "./H1/compiler_parser.cpp"
    break;

  case 184: // undefined: UNDEFINED
#line 545 "H1.parser.ypp"
                                { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_undefined>(std::to_string(*location)); }
#line 2706 "./H1/compiler_parser.cpp"
    break;

  case 185: // size: SIZE
#line 546 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_size>(std::to_string(*location)); }
#line 2712 "./H1/compiler_parser.cpp"
    break;

  case 186: // game: GAME
#line 547 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_game>(std::to_string(*location)); }
#line 2718 "./H1/compiler_parser.cpp"
    break;

  case 187: // self: SELF
#line 548 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_self>(std::to_string(*location)); }
#line 2724 "./H1/compiler_parser.cpp"
    break;

  case 188: // anim: ANIM
#line 549 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_anim>(std::to_string(*location)); }
#line 2730 "./H1/compiler_parser.cpp"
    break;

  case 189: // level: LEVEL
#line 550 "H1.parser.ypp"
                                        { yylhs.value.as < gsc::node_ptr > () = std::make_unique<gsc::node_level>(std::to_string(*location)); }
#line 2736 "./H1/compiler_parser.cpp"
    break;


#line 2740 "./H1/compiler_parser.cpp"

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
  "root", "script", "include", "definition", "using_animtree", "constant",
  "thread", "parameters", "block", "stmt", "stmt_call", "stmt_assign",
  "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_waitframe",
  "stmt_if", "stmt_ifelse", "stmt_while", "stmt_for", "stmt_foreach",
  "stmt_switch", "stmt_case", "stmt_default", "stmt_break",
  "stmt_continue", "stmt_return", "for_assign", "for_cond", "expr",
  "expr_assign", "expr_cmp", "expr_ternary", "expr_binary",
  "expr_primitive", "expr_call", "expr_call_thread", "expr_call_function",
  "expr_call_pointer", "expr_arguments", "expr_function_ref", "expr_array",
  "expr_field", "expr_size", "expr_vector", "expr_add_array", "object",
  "vector", "number", "data_false", "data_true", "data_float",
  "data_integer", "data_localized_string", "data_string", "animref",
  "animtree", "identifier", "filepath", "empty_array", "undefined", "size",
  "game", "self", "anim", "level", YY_NULLPTR
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

#if H1DEBUG
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
#if H1DEBUG
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
#if H1DEBUG
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


  const short parser::yypact_ninf_ = -219;

  const short parser::yytable_ninf_ = -170;

  const short
  parser::yypact_[] =
  {
       5,   -64,   -15,  -219,    30,     5,  -219,  -219,  -219,  -219,
    -219,   -22,  -219,    -9,   -40,  -219,  -219,  -219,    20,  1028,
    -219,  -219,    21,   -26,  -219,  -219,    15,    19,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  1028,  1053,    20,  1028,
    1028,  -219,  -219,  -219,  -219,  2305,    35,  -219,  -219,  -219,
       2,  -219,  -219,  -219,  -219,    83,   153,  -219,  -219,  -219,
     186,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,    68,    23,  -219,  -219,   188,   238,   240,   306,    47,
      67,    20,    66,  -219,  -219,    73,    69,    70,  1718,    75,
    1053,  2369,   -19,  -219,  2369,  2369,  -219,  1028,  1028,  1028,
    1028,  1028,  1028,  1028,  1028,  1028,  1028,  1028,  1028,  1028,
    1028,  1028,  1028,  1028,  1028,  1028,    15,  1053,   -20,  -219,
    -219,  1028,    20,  -219,  1683,  -219,  1028,    20,  1028,  -219,
    1028,   -35,  2088,  -219,  1028,  2369,  2369,  2369,  2369,  2369,
    2369,  2369,  2369,  2369,  2369,  2369,  2369,  2369,  2369,  2369,
    2369,  2369,  2369,  2272,  -219,  -219,  2126,  -219,  -219,  -219,
      -8,    76,    79,    85,   -72,    80,    82,    96,   104,   105,
     101,   102,   -23,   106,   107,  1135,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,   110,   111,   116,
    -219,  -219,     7,    73,  -219,  -219,  -219,  -219,  2088,    76,
    2164,  2201,   109,   125,  2369,  1028,  -219,  -219,  1028,  1028,
    1028,    98,   123,  -219,  -219,   127,  1028,  1028,  -219,  -219,
    2338,  1028,   126,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
     133,   137,   138,   140,    20,  -219,  -219,  1028,  1028,  1028,
    1028,  1028,  1028,  1028,  1028,  1028,  1028,  1028,   149,  1028,
     -35,   143,  2369,     4,  1833,  1864,  -219,  -219,   145,  -219,
    -219,  1670,   534,  1895,  -219,  1926,  -219,  1028,  1028,  1028,
    1028,  2369,  2369,  2369,  2369,  2369,  2369,  2369,  2369,  2369,
    2369,  2369,   158,  1957,   160,  1028,  -219,  1170,   157,  1028,
    1028,  1215,   154,  1760,  2238,  1988,  1802,  1028,  -219,  -219,
      11,  1683,   191,  1683,   155,  2369,    33,  2019,  1683,  -219,
    -219,   164,  1028,  1028,   166,   169,  1028,    12,  -219,  1248,
    1293,  1326,   127,  1370,  1405,  -219,    24,  2050,  -219,  -219,
      53,  -219,   192,  1683,  -219,  -219,   176,  1683,  -219,  -219,
     171,   172,   173,  1450,  1483,  1528,  1561,  -219,  -219,  -219,
    1683,  -219,  -219,  1683,  -219,  -219,  1605,  1640,  -219,  -219
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,   181,     0,     2,     6,     7,     9,    10,
      11,     0,   182,     0,     0,     1,     4,     5,    17,     0,
       8,   178,     0,     0,    16,   180,     0,     0,   184,   174,
     173,   186,   189,   188,   187,   183,     0,   154,     0,     0,
       0,   179,   177,   175,   176,     0,    78,    79,    80,    81,
     117,   118,   140,   141,   119,   120,   121,   122,   123,   124,
       0,   125,   126,   129,   130,   171,   172,   127,   128,   131,
     132,   133,     0,   134,   135,   136,   137,   138,   139,     0,
       0,     0,     0,   144,   145,     0,     0,     0,     0,   126,
     154,   153,     0,   155,   116,   115,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   142,
     143,   154,     0,    12,    20,    15,     0,     0,     0,   114,
       0,     0,   153,   161,     0,   113,   107,   108,    95,    96,
      97,    98,    99,   100,   101,   102,   104,   105,   106,   109,
     110,   111,   112,     0,   146,   147,     0,   185,   158,   159,
       0,   156,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     0,   162,     0,
     163,   164,     0,   165,   169,   168,   167,   166,     0,     0,
       0,     0,     0,     0,   152,     0,   157,   148,   154,     0,
       0,     0,     0,    69,    70,    75,     0,     0,    71,    73,
       0,     0,     0,    52,    53,    14,    18,    43,    41,    42,
       0,     0,     0,     0,     0,    82,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   103,     0,     0,     0,    67,    68,     0,    74,
     162,     0,     0,     0,    72,     0,    48,     0,     0,     0,
       0,    84,    90,    91,    92,    93,    94,    85,    86,    87,
      88,    89,     0,     0,     0,   154,   149,     0,     0,    77,
       0,     0,     0,     0,     0,     0,     0,   154,   160,   170,
       0,    20,    55,    20,     0,     0,    78,     0,    20,    61,
      47,     0,   154,     0,     0,     0,   154,     0,   150,     0,
       0,     0,    75,     0,     0,    50,     0,     0,    44,    46,
       0,   151,    54,    20,    59,    66,     0,    20,    65,    60,
       0,     0,     0,     0,     0,     0,     0,    49,    51,    45,
      20,    58,    57,    20,    63,    64,     0,     0,    56,    62
  };

  const short
  parser::yypgoto_[] =
  {
    -219,  -219,  -219,   216,   217,  -219,  -219,  -219,  -219,    97,
     167,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -109,  -219,   322,  -218,   -75,  -219,  -219,  -219,   -81,
     687,   -25,   -24,  -115,  -219,   152,   319,  -219,  -219,  -219,
     379,  -219,   -33,  -219,  -219,  -219,    72,  -219,   -10,  -219,
    -219,     0,    39,  -219,  -219,  -219,   439,   503,   563,   623
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,     8,     9,    10,    23,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   268,   314,    91,   197,    46,    47,    48,    49,    50,
      51,    52,    53,    92,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   159,    75,    76,    77,    78
  };

  const short
  parser::yytable_[] =
  {
      11,    83,    84,    89,    22,    11,   160,   269,     1,     2,
     157,    80,    21,   231,    18,    44,    81,    12,    24,  -162,
    -162,    14,   133,   134,   116,    27,    85,   240,   241,   217,
      15,   242,   243,    27,   134,   119,   120,    20,    93,    19,
      13,   296,  -162,   198,    21,  -162,   134,   117,   328,   341,
     244,    43,    44,   134,   134,    82,   245,   246,    79,    87,
      85,   350,     3,    43,    44,    86,   134,   122,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   -76,
     115,   125,   115,  -162,  -162,  -165,  -165,     3,    12,     3,
     352,   154,   155,   123,   198,   134,    12,     3,   212,    86,
    -163,  -163,     3,   263,   121,   124,   126,    25,  -165,   121,
     128,  -165,   218,   127,   269,   219,    85,   131,   158,    26,
      27,   220,   161,  -163,   203,   223,  -163,   209,   224,    28,
      29,    30,   225,    31,    32,    33,    34,    35,    36,   232,
     226,   227,    37,   266,   270,    27,    38,   228,   229,  -165,
    -165,   260,   233,   234,   222,    86,   237,   238,    31,    32,
      33,    34,   239,    86,  -163,  -163,   261,    82,   267,   277,
    -164,  -164,   276,   278,   279,   203,   280,   119,   120,   295,
     310,    39,    40,    12,     3,    41,    21,    42,    43,    44,
     292,   299,   327,  -164,   307,   313,  -164,   309,   330,   353,
     320,   332,    85,   116,    27,  -169,  -169,   336,    12,     3,
     335,   340,   338,   355,    86,   339,   198,   357,   358,   359,
     198,    16,    17,   346,   316,   203,   117,   294,  -169,   118,
     198,  -169,   198,     0,  -164,  -164,   221,   198,     0,     0,
       0,    86,     0,     0,   158,     0,   119,   120,   198,   198,
     198,   270,   198,   198,     0,  -168,  -168,  -167,  -167,     0,
       0,     0,   198,     0,    86,     0,   198,    12,     3,  -169,
    -169,    85,   198,   198,   198,   198,   200,     0,  -168,   198,
    -167,  -168,   198,  -167,     0,   198,   198,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   203,     0,     0,
       0,   203,     0,     0,     0,     0,     0,     0,     0,     0,
      86,   203,     0,   203,     0,     0,     0,     0,   203,  -168,
    -168,  -167,  -167,  -166,  -166,     0,     0,   200,     0,   203,
     203,   203,   203,   203,   203,     0,    86,     0,     0,     0,
      86,    45,   236,   203,     0,     0,  -166,   203,     0,  -166,
      86,     0,    86,   203,   203,   203,   203,    86,    88,     0,
     203,    94,    95,   203,     0,     0,   203,   203,    86,    86,
      86,    86,    86,    86,     0,     0,     0,   200,     0,     0,
       0,     0,    86,     0,     0,     0,    86,  -166,  -166,     0,
       0,     0,    86,    86,    86,    86,     0,     0,     0,    86,
       0,     0,    86,     0,     0,    86,    86,     0,   329,     0,
     331,     0,   132,     0,     0,   334,     0,     0,     0,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,     0,   156,
     354,     0,     0,   201,   356,     0,     0,     0,   208,   200,
     210,     0,   211,   200,     0,     0,   214,   366,     0,     0,
     367,     0,     0,   200,   312,   200,     0,     0,   319,     0,
     200,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   200,   200,   200,   200,   200,   200,     0,     0,     0,
       0,     0,     0,   230,   201,   200,   236,   344,   236,   200,
     348,   236,     0,   202,     0,   200,   200,   200,   200,     0,
       0,     0,   200,     0,     0,   200,     0,     0,   200,   200,
     361,   236,   364,   236,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   236,   236,     0,     0,   262,     0,     0,
       0,   264,   265,     0,   201,     0,     0,     0,   272,   273,
       0,     0,     0,   275,   202,     0,     0,     0,     0,     0,
     300,     0,     0,   204,     0,     0,     0,     0,     0,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
       0,   293,    97,     0,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,     0,     0,     0,     0,   303,
     304,   305,   306,     0,   271,     0,   108,   109,   110,   111,
     112,   113,   114,     0,   204,     0,   201,     0,     0,     0,
     201,   315,   317,     0,     0,     0,     0,   205,     0,     0,
     201,     0,   201,     0,     0,     0,     0,   201,     0,     0,
       0,     0,     0,     0,     0,   337,     0,     0,   201,   201,
     201,   201,   201,   201,     0,     0,     0,     0,     0,     0,
       0,     0,   201,     0,   204,     0,   201,     0,     0,     0,
       0,     0,   201,   201,   201,   201,   202,     0,   205,   201,
     202,     0,   201,     0,     0,   201,   201,   206,     0,     0,
     202,     0,   202,     0,     0,     0,     0,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   202,   202,
     202,   271,   202,   202,     0,     0,     0,     0,     0,     0,
       0,     0,   202,     0,     0,     0,   202,     0,   205,     0,
       0,     0,   202,   202,   202,   202,   204,     0,   206,   202,
     204,     0,   202,     0,     0,   202,   202,   207,     0,     0,
     204,     0,   204,     0,     0,     0,     0,   204,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   204,   204,
     204,   204,   204,   204,     0,     0,     0,     0,     0,     0,
       0,     0,   204,     0,     0,     0,   204,     0,   206,     0,
       0,     0,   204,   204,   204,   204,     0,     0,   207,   204,
     205,     0,   204,     0,   205,   204,   204,     0,     0,     0,
       0,   199,     0,     0,   205,     0,   205,     0,     0,     0,
       0,   205,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   205,   205,   205,   205,   205,   205,     0,     0,
       0,     0,     0,     0,     0,     0,   205,     0,   207,     0,
     205,     0,     0,     0,     0,     0,   205,   205,   205,   205,
     206,     0,   199,   205,   206,     0,   205,     0,     0,   205,
     205,     0,     0,     0,   206,     0,   206,     0,     0,     0,
       0,   206,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   206,   206,   206,   206,   206,   206,     0,     0,
       0,     0,     0,     0,     0,     0,   206,     0,     0,     0,
     206,     0,     0,     0,     0,     0,   206,   206,   206,   206,
     207,     0,     0,   206,   207,     0,   206,     0,     0,   206,
     206,     0,     0,     0,   207,     0,   207,     0,     0,     0,
       0,   207,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   207,   207,   207,   207,   207,   207,     0,     0,
       0,     0,     0,     0,     0,     0,   207,     0,     0,     0,
     207,     0,     0,     0,     0,     0,   207,   207,   207,   207,
       0,     0,     0,   207,   199,     0,   207,     0,   199,   207,
     207,     0,     0,     0,     0,     0,     0,     0,   199,     0,
     199,     0,     0,     0,     0,   199,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   199,   199,   199,     0,
     199,   199,     0,     0,     0,     0,     0,     0,     0,     0,
     199,     0,     0,    25,   199,     0,     0,     0,     0,     0,
     199,   199,   199,   199,     0,    26,    27,   199,     0,     0,
     199,     0,     0,   199,   199,    28,    29,    30,    25,    31,
      32,    33,    34,    35,    36,     0,     0,     0,    37,     0,
      26,    27,    38,     0,     0,     0,     0,     0,     0,     0,
      28,    29,    30,     0,    31,    32,    33,    34,    35,    36,
       0,     0,     0,    90,     0,     0,     0,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,    40,    12,
       3,    41,    21,    42,    43,    44,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    39,    40,    12,     3,    41,    21,    42,    43,
      44,   162,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,    26,    27,   172,     0,     0,   173,   174,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,    34,
       0,     0,     0,     0,   235,    82,   162,     0,   163,   164,
     165,   166,   167,   168,   169,   170,   171,    26,    27,   172,
       0,     0,   173,   174,     0,     0,     0,     0,     0,     0,
       0,    31,    32,    33,    34,     0,     0,     0,   311,     0,
      82,     0,     0,     0,     0,     0,    12,     3,     0,     0,
       0,   162,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,    26,    27,   172,     0,     0,   173,   174,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,    34,
       0,    12,     3,   318,   162,    82,   163,   164,   165,   166,
     167,   168,   169,   170,   171,    26,    27,   172,     0,     0,
     173,   174,     0,     0,     0,     0,     0,     0,     0,    31,
      32,    33,    34,     0,     0,     0,     0,   342,    82,     0,
       0,     0,     0,     0,     0,     0,    12,     3,     0,   162,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
      26,    27,   172,     0,     0,   173,   174,     0,     0,     0,
       0,     0,     0,     0,    31,    32,    33,    34,     0,    12,
       3,   343,   162,    82,   163,   164,   165,   166,   167,   168,
     169,   170,   171,    26,    27,   172,     0,     0,   173,   174,
       0,     0,     0,     0,     0,     0,     0,    31,    32,    33,
      34,     0,     0,     0,     0,   345,    82,     0,     0,     0,
       0,     0,     0,     0,    12,     3,   162,     0,   163,   164,
     165,   166,   167,   168,   169,   170,   171,    26,    27,   172,
       0,     0,   173,   174,     0,     0,     0,     0,     0,     0,
       0,    31,    32,    33,    34,     0,     0,    12,     3,   347,
      82,   162,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,    26,    27,   172,     0,     0,   173,   174,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,    34,
       0,     0,     0,     0,   349,    82,     0,     0,     0,     0,
       0,    12,     3,     0,     0,     0,   162,     0,   163,   164,
     165,   166,   167,   168,   169,   170,   171,    26,    27,   172,
       0,     0,   173,   174,     0,     0,     0,     0,     0,     0,
       0,    31,    32,    33,    34,     0,    12,     3,   360,   162,
      82,   163,   164,   165,   166,   167,   168,   169,   170,   171,
      26,    27,   172,     0,     0,   173,   174,     0,     0,     0,
       0,     0,     0,     0,    31,    32,    33,    34,     0,     0,
       0,     0,   362,    82,     0,     0,     0,     0,     0,     0,
       0,    12,     3,     0,   162,     0,   163,   164,   165,   166,
     167,   168,   169,   170,   171,    26,    27,   172,     0,     0,
     173,   174,     0,     0,     0,     0,     0,     0,     0,    31,
      32,    33,    34,     0,    12,     3,   363,   162,    82,   163,
     164,   165,   166,   167,   168,   169,   170,   171,    26,    27,
     172,     0,     0,   173,   174,     0,     0,     0,     0,     0,
       0,     0,    31,    32,    33,    34,     0,     0,     0,     0,
     365,    82,     0,     0,     0,     0,     0,     0,     0,    12,
       3,   162,     0,   163,   164,   165,   166,   167,   168,   169,
     170,   171,    26,    27,   172,     0,     0,   173,   174,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,    34,
       0,     0,    12,     3,   368,    82,   162,     0,   163,   164,
     165,   166,   167,   168,   169,   170,   171,    26,    27,   172,
       0,     0,   173,   174,     0,     0,     0,     0,     0,     0,
       0,    31,    32,    33,    34,     0,     0,     0,     0,   369,
      82,     0,     0,     0,     0,     0,    12,     3,    27,   162,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
      26,    27,   172,     0,     0,   173,   174,     0,     0,     0,
     117,     0,     0,   244,    31,    32,    33,    34,     0,   245,
     246,    12,     3,    82,     0,     0,     0,     0,     0,     0,
       0,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     3,     0,     0,   129,     0,     0,     0,     0,
     130,     0,     0,     0,    12,     3,    97,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,   112,   113,   114,   321,     0,     0,
       0,     0,   322,     0,     0,     0,     0,     0,    97,     0,
       0,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   108,   109,   110,   111,   112,   113,   114,   325,
       0,     0,     0,     0,   326,     0,     0,     0,     0,     0,
      97,     0,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,     0,     0,     0,     0,     0,     0,     0,
     297,     0,     0,     0,   108,   109,   110,   111,   112,   113,
     114,    97,     0,     0,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,     0,     0,     0,     0,     0,     0,
       0,   298,     0,     0,     0,   108,   109,   110,   111,   112,
     113,   114,    97,     0,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,     0,     0,     0,     0,     0,
       0,     0,   301,     0,     0,     0,   108,   109,   110,   111,
     112,   113,   114,    97,     0,     0,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,   302,     0,     0,     0,   108,   109,   110,
     111,   112,   113,   114,    97,     0,     0,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,     0,     0,     0,
       0,     0,     0,     0,   308,     0,     0,     0,   108,   109,
     110,   111,   112,   113,   114,    97,     0,     0,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,     0,     0,
       0,     0,     0,     0,     0,   324,     0,     0,     0,   108,
     109,   110,   111,   112,   113,   114,    97,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,     0,     0,     0,     0,     0,   333,     0,     0,     0,
     108,   109,   110,   111,   112,   113,   114,    97,     0,     0,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,     0,     0,     0,     0,   351,     0,     0,
       0,   108,   109,   110,   111,   112,   113,   114,    97,     0,
       0,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   108,   109,   110,   111,   112,   113,   114,   213,
       0,     0,     0,     0,     0,     0,    97,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,   112,   113,   114,   216,     0,     0,
       0,     0,     0,     0,    97,     0,     0,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   109,
     110,   111,   112,   113,   114,   258,     0,     0,     0,     0,
       0,     0,    97,     0,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,   114,   259,     0,     0,     0,     0,     0,    97,
       0,     0,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,   109,   110,   111,   112,   113,   114,
     323,     0,     0,     0,     0,     0,    97,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,   112,   113,   114,   215,     0,     0,
      97,     0,     0,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   108,   109,   110,   111,   112,   113,
     114,    96,     0,    97,     0,     0,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   109,   110,
     111,   112,   113,   114,   274,     0,    97,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,   112,   113,   114,    97,     0,     0,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,   114
  };

  const short
  parser::yycheck_[] =
  {
       0,    26,    26,    36,    14,     5,   121,   225,     3,     4,
      30,    37,    84,    36,    36,    87,    42,    81,    18,    17,
      18,    36,    41,    42,    17,    18,    26,    20,    21,    37,
       0,    24,    25,    18,    42,    60,    60,    46,    38,    61,
       1,    37,    40,   124,    84,    43,    42,    40,    37,    37,
      43,    86,    87,    42,    42,    40,    49,    50,    37,    40,
      60,    37,    82,    86,    87,    26,    42,    44,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    46,
      47,    81,    47,    81,    82,    17,    18,    82,    81,    82,
      37,   116,   116,    46,   175,    42,    81,    82,   131,    60,
      17,    18,    82,   218,    36,    38,    40,     5,    40,    36,
      40,    43,    36,    44,   332,    36,   116,    42,   118,    17,
      18,    36,   122,    40,   124,    45,    43,   127,    46,    27,
      28,    29,    36,    31,    32,    33,    34,    35,    36,   172,
      36,    36,    40,    45,   225,    18,    44,    46,    46,    81,
      82,    42,    46,    46,   164,   116,    46,    46,    31,    32,
      33,    34,    46,   124,    81,    82,    41,    40,    45,    36,
      17,    18,    46,    36,    36,   175,    36,   202,   202,    36,
     295,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      41,    46,   307,    40,    36,    38,    43,    37,     7,     7,
      46,    46,   202,    17,    18,    17,    18,   322,    81,    82,
      46,   326,    46,    37,   175,    46,   297,    46,    46,    46,
     301,     5,     5,   332,   299,   225,    40,   260,    40,    43,
     311,    43,   313,    -1,    81,    82,   164,   318,    -1,    -1,
      -1,   202,    -1,    -1,   244,    -1,   271,   271,   329,   330,
     331,   332,   333,   334,    -1,    17,    18,    17,    18,    -1,
      -1,    -1,   343,    -1,   225,    -1,   347,    81,    82,    81,
      82,   271,   353,   354,   355,   356,   124,    -1,    40,   360,
      40,    43,   363,    43,    -1,   366,   367,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   297,    -1,    -1,
      -1,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     271,   311,    -1,   313,    -1,    -1,    -1,    -1,   318,    81,
      82,    81,    82,    17,    18,    -1,    -1,   175,    -1,   329,
     330,   331,   332,   333,   334,    -1,   297,    -1,    -1,    -1,
     301,    19,   175,   343,    -1,    -1,    40,   347,    -1,    43,
     311,    -1,   313,   353,   354,   355,   356,   318,    36,    -1,
     360,    39,    40,   363,    -1,    -1,   366,   367,   329,   330,
     331,   332,   333,   334,    -1,    -1,    -1,   225,    -1,    -1,
      -1,    -1,   343,    -1,    -1,    -1,   347,    81,    82,    -1,
      -1,    -1,   353,   354,   355,   356,    -1,    -1,    -1,   360,
      -1,    -1,   363,    -1,    -1,   366,   367,    -1,   311,    -1,
     313,    -1,    90,    -1,    -1,   318,    -1,    -1,    -1,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    -1,   117,
     343,    -1,    -1,   124,   347,    -1,    -1,    -1,   126,   297,
     128,    -1,   130,   301,    -1,    -1,   134,   360,    -1,    -1,
     363,    -1,    -1,   311,   297,   313,    -1,    -1,   301,    -1,
     318,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   329,   330,   331,   332,   333,   334,    -1,    -1,    -1,
      -1,    -1,    -1,   171,   175,   343,   329,   330,   331,   347,
     333,   334,    -1,   124,    -1,   353,   354,   355,   356,    -1,
      -1,    -1,   360,    -1,    -1,   363,    -1,    -1,   366,   367,
     353,   354,   355,   356,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   366,   367,    -1,    -1,   215,    -1,    -1,
      -1,   219,   220,    -1,   225,    -1,    -1,    -1,   226,   227,
      -1,    -1,    -1,   231,   175,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
      -1,   259,    48,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,   277,
     278,   279,   280,    -1,   225,    -1,    72,    73,    74,    75,
      76,    77,    78,    -1,   175,    -1,   297,    -1,    -1,    -1,
     301,   299,   300,    -1,    -1,    -1,    -1,   124,    -1,    -1,
     311,    -1,   313,    -1,    -1,    -1,    -1,   318,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   323,    -1,    -1,   329,   330,
     331,   332,   333,   334,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   343,    -1,   225,    -1,   347,    -1,    -1,    -1,
      -1,    -1,   353,   354,   355,   356,   297,    -1,   175,   360,
     301,    -1,   363,    -1,    -1,   366,   367,   124,    -1,    -1,
     311,    -1,   313,    -1,    -1,    -1,    -1,   318,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   329,   330,
     331,   332,   333,   334,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   343,    -1,    -1,    -1,   347,    -1,   225,    -1,
      -1,    -1,   353,   354,   355,   356,   297,    -1,   175,   360,
     301,    -1,   363,    -1,    -1,   366,   367,   124,    -1,    -1,
     311,    -1,   313,    -1,    -1,    -1,    -1,   318,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   329,   330,
     331,   332,   333,   334,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   343,    -1,    -1,    -1,   347,    -1,   225,    -1,
      -1,    -1,   353,   354,   355,   356,    -1,    -1,   175,   360,
     297,    -1,   363,    -1,   301,   366,   367,    -1,    -1,    -1,
      -1,   124,    -1,    -1,   311,    -1,   313,    -1,    -1,    -1,
      -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   329,   330,   331,   332,   333,   334,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   343,    -1,   225,    -1,
     347,    -1,    -1,    -1,    -1,    -1,   353,   354,   355,   356,
     297,    -1,   175,   360,   301,    -1,   363,    -1,    -1,   366,
     367,    -1,    -1,    -1,   311,    -1,   313,    -1,    -1,    -1,
      -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   329,   330,   331,   332,   333,   334,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   343,    -1,    -1,    -1,
     347,    -1,    -1,    -1,    -1,    -1,   353,   354,   355,   356,
     297,    -1,    -1,   360,   301,    -1,   363,    -1,    -1,   366,
     367,    -1,    -1,    -1,   311,    -1,   313,    -1,    -1,    -1,
      -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   329,   330,   331,   332,   333,   334,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   343,    -1,    -1,    -1,
     347,    -1,    -1,    -1,    -1,    -1,   353,   354,   355,   356,
      -1,    -1,    -1,   360,   297,    -1,   363,    -1,   301,   366,
     367,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   311,    -1,
     313,    -1,    -1,    -1,    -1,   318,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   329,   330,   331,    -1,
     333,   334,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     343,    -1,    -1,     5,   347,    -1,    -1,    -1,    -1,    -1,
     353,   354,   355,   356,    -1,    17,    18,   360,    -1,    -1,
     363,    -1,    -1,   366,   367,    27,    28,    29,     5,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    40,    -1,
      17,    18,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    81,    82,    83,    84,    85,    86,
      87,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    40,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    38,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      -1,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      -1,    81,    82,    38,     6,    40,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,    81,
      82,    38,     6,    40,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    81,    82,    39,
      40,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    81,    82,    38,     6,
      40,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,     6,    -1,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    81,    82,    38,     6,    40,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      -1,    -1,    81,    82,    39,    40,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    81,    82,    18,     6,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      40,    -1,    -1,    43,    31,    32,    33,    34,    -1,    49,
      50,    81,    82,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    37,    -1,    -1,    -1,    -1,
      42,    -1,    -1,    -1,    81,    82,    48,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    37,    -1,    -1,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    37,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    48,    -1,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    48,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    48,    -1,    -1,    51,    52,    53,    54,
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
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    42,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      42,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    45,    -1,    -1,
      48,    -1,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    46,    -1,    48,    -1,    -1,    51,    52,    53,    54,
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
       0,     3,     4,    82,    90,    91,    92,    93,    94,    95,
      96,   150,    81,   151,    36,     0,    92,    93,    36,    61,
      46,    84,   147,    97,   150,     5,    17,    18,    27,    28,
      29,    31,    32,    33,    34,    35,    36,    40,    44,    79,
      80,    83,    85,    86,    87,   122,   124,   125,   126,   127,
     128,   129,   130,   131,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   155,   156,   157,   158,    37,
      37,    42,    40,   130,   131,   150,   151,    40,   122,   141,
      40,   122,   132,   150,   122,   122,    46,    48,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    72,    73,
      74,    75,    76,    77,    78,    47,    17,    40,    43,   130,
     131,    36,    44,    46,    38,   150,    40,    44,    40,    37,
      42,    42,   122,    41,    42,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   130,   131,   122,    30,   150,   154,
     132,   150,     6,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    19,    22,    23,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   123,   128,   129,
     134,   135,   139,   150,   155,   156,   157,   158,   122,   150,
     122,   122,   141,    41,   122,    45,    41,    37,    36,    36,
      36,   145,   147,    45,    46,    36,    36,    36,    46,    46,
     122,    36,   141,    46,    46,    39,    99,    46,    46,    46,
      20,    21,    24,    25,    43,    49,    50,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    41,    42,
      42,    41,   122,   132,   122,   122,    45,    45,   120,   123,
     128,   139,   122,   122,    46,   122,    46,    36,    36,    36,
      36,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,    41,   122,   141,    36,    37,    37,    37,    46,
      26,    37,    37,   122,   122,   122,   122,    36,    37,    37,
     132,    38,    99,    38,   121,   122,   124,   122,    38,    99,
      46,    37,    42,    42,    37,    37,    42,   132,    37,    98,
       7,    98,    46,    37,    98,    46,   132,   122,    46,    46,
     132,    37,    39,    38,    99,    39,   120,    39,    99,    39,
      37,    37,    37,     7,    98,    37,    98,    46,    46,    46,
      38,    99,    39,    38,    99,    39,    98,    98,    39,    39
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    89,    90,    90,    91,    91,    91,    91,    92,    93,
      93,    93,    94,    95,    96,    97,    97,    97,    98,    98,
      98,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   100,   100,   101,   102,   103,   103,   104,   104,   105,
     105,   106,   107,   108,   109,   109,   110,   110,   110,   110,
     111,   111,   112,   112,   113,   113,   114,   115,   115,   116,
     117,   118,   119,   119,   120,   120,   121,   121,   122,   122,
     122,   122,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   124,   124,   124,   124,   124,
     124,   124,   124,   125,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     128,   128,   128,   128,   129,   129,   129,   129,   130,   130,
     131,   131,   132,   132,   132,   133,   133,   134,   135,   136,
     137,   138,   139,   139,   139,   139,   139,   139,   139,   139,
     140,   141,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     1,     1,     3,     1,
       1,     1,     5,     4,     7,     3,     1,     0,     2,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     6,     8,     6,     5,     3,     8,
       6,     8,     2,     2,     7,     5,    11,     9,     9,     7,
       7,     5,    11,     9,     9,     7,     7,     3,     3,     2,
       2,     2,     3,     2,     1,     0,     1,     0,     1,     1,
       1,     1,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     3,     3,     4,     6,
       8,     9,     3,     1,     0,     2,     3,     4,     3,     3,
       7,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
  };




#if H1DEBUG
  const short
  parser::yyrline_[] =
  {
       0,   122,   122,   123,   127,   129,   131,   133,   138,   143,
     144,   145,   149,   154,   159,   164,   166,   169,   173,   175,
     178,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   205,   207,   212,   217,   222,   224,   229,   231,   236,
     238,   243,   248,   253,   258,   260,   268,   270,   275,   280,
     290,   292,   300,   302,   311,   313,   322,   327,   329,   334,
     339,   343,   348,   350,   355,   356,   360,   361,   365,   366,
     367,   368,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   388,   389,   390,   391,   392,
     393,   394,   395,   399,   403,   404,   405,   406,   407,   408,
     409,   410,   411,   412,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     445,   446,   447,   448,   452,   453,   454,   455,   459,   461,
     466,   468,   473,   475,   478,   482,   484,   489,   494,   499,
     504,   509,   514,   515,   516,   517,   518,   519,   520,   521,
     525,   530,   531,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550
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
#endif // H1DEBUG


#line 14 "H1.parser.ypp"
} // H1
#line 3974 "./H1/compiler_parser.cpp"

#line 552 "H1.parser.ypp"


void H1::parser::error(const std::string& msg)
{
    GSC_COMP_ERROR("%s", msg.data());
}
