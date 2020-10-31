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
#line 40 "iw6.parser.ypp"

    #include "IW6.hpp"
	#include "compiler_parser.hpp"
	#include "compiler_lexer.hpp"

	yy::parser::symbol_type yylex(yyscan_t yyscanner);

#line 47 "./IW6/compiler_parser.cpp"




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
#line 127 "./IW6/compiler_parser.cpp"

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
      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_function: // function
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
      case symbol_kind::S_stmt_endon: // stmt_endon
      case symbol_kind::S_stmt_notify: // stmt_notify
      case symbol_kind::S_stmt_wait: // stmt_wait
      case symbol_kind::S_stmt_waittill: // stmt_waittill
      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
      case symbol_kind::S_stmt_if: // stmt_if
      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
      case symbol_kind::S_stmt_while: // stmt_while
      case symbol_kind::S_stmt_for: // stmt_for
      case symbol_kind::S_stmt_foreach: // stmt_foreach
      case symbol_kind::S_stmt_switch: // stmt_switch
      case symbol_kind::S_stmt_case: // stmt_case
      case symbol_kind::S_stmt_default: // stmt_default
      case symbol_kind::S_stmt_break: // stmt_break
      case symbol_kind::S_stmt_continue: // stmt_continue
      case symbol_kind::S_stmt_return: // stmt_return
      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_func_call_ptr: // expr_func_call_ptr
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_object: // object
      case symbol_kind::S_object_restricted: // object_restricted
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_num_float: // num_float
      case symbol_kind::S_num_integer: // num_integer
      case symbol_kind::S_string_hash: // string_hash
      case symbol_kind::S_string_loc: // string_loc
      case symbol_kind::S_string: // string
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_filepath: // filepath
        value.YY_MOVE_OR_COPY< std::unique_ptr<node> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arg_list: // expr_arg_list
        value.YY_MOVE_OR_COPY< std::unique_ptr<node_expr_arg_list> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.YY_MOVE_OR_COPY< std::unique_ptr<node_parameter_list> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.YY_MOVE_OR_COPY< std::unique_ptr<node_script> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        value.YY_MOVE_OR_COPY< std::unique_ptr<node_stmt_block> > (YY_MOVE (that.value));
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
      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_function: // function
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
      case symbol_kind::S_stmt_endon: // stmt_endon
      case symbol_kind::S_stmt_notify: // stmt_notify
      case symbol_kind::S_stmt_wait: // stmt_wait
      case symbol_kind::S_stmt_waittill: // stmt_waittill
      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
      case symbol_kind::S_stmt_if: // stmt_if
      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
      case symbol_kind::S_stmt_while: // stmt_while
      case symbol_kind::S_stmt_for: // stmt_for
      case symbol_kind::S_stmt_foreach: // stmt_foreach
      case symbol_kind::S_stmt_switch: // stmt_switch
      case symbol_kind::S_stmt_case: // stmt_case
      case symbol_kind::S_stmt_default: // stmt_default
      case symbol_kind::S_stmt_break: // stmt_break
      case symbol_kind::S_stmt_continue: // stmt_continue
      case symbol_kind::S_stmt_return: // stmt_return
      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_func_call_ptr: // expr_func_call_ptr
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_object: // object
      case symbol_kind::S_object_restricted: // object_restricted
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_num_float: // num_float
      case symbol_kind::S_num_integer: // num_integer
      case symbol_kind::S_string_hash: // string_hash
      case symbol_kind::S_string_loc: // string_loc
      case symbol_kind::S_string: // string
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_filepath: // filepath
        value.move< std::unique_ptr<node> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arg_list: // expr_arg_list
        value.move< std::unique_ptr<node_expr_arg_list> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< std::unique_ptr<node_parameter_list> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< std::unique_ptr<node_script> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        value.move< std::unique_ptr<node_stmt_block> > (YY_MOVE (that.value));
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
      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_function: // function
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
      case symbol_kind::S_stmt_endon: // stmt_endon
      case symbol_kind::S_stmt_notify: // stmt_notify
      case symbol_kind::S_stmt_wait: // stmt_wait
      case symbol_kind::S_stmt_waittill: // stmt_waittill
      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
      case symbol_kind::S_stmt_if: // stmt_if
      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
      case symbol_kind::S_stmt_while: // stmt_while
      case symbol_kind::S_stmt_for: // stmt_for
      case symbol_kind::S_stmt_foreach: // stmt_foreach
      case symbol_kind::S_stmt_switch: // stmt_switch
      case symbol_kind::S_stmt_case: // stmt_case
      case symbol_kind::S_stmt_default: // stmt_default
      case symbol_kind::S_stmt_break: // stmt_break
      case symbol_kind::S_stmt_continue: // stmt_continue
      case symbol_kind::S_stmt_return: // stmt_return
      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_func_call_ptr: // expr_func_call_ptr
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_object: // object
      case symbol_kind::S_object_restricted: // object_restricted
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_num_float: // num_float
      case symbol_kind::S_num_integer: // num_integer
      case symbol_kind::S_string_hash: // string_hash
      case symbol_kind::S_string_loc: // string_loc
      case symbol_kind::S_string: // string
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_filepath: // filepath
        value.copy< std::unique_ptr<node> > (that.value);
        break;

      case symbol_kind::S_expr_arg_list: // expr_arg_list
        value.copy< std::unique_ptr<node_expr_arg_list> > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.copy< std::unique_ptr<node_parameter_list> > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.copy< std::unique_ptr<node_script> > (that.value);
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        value.copy< std::unique_ptr<node_stmt_block> > (that.value);
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
      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_function: // function
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
      case symbol_kind::S_stmt_endon: // stmt_endon
      case symbol_kind::S_stmt_notify: // stmt_notify
      case symbol_kind::S_stmt_wait: // stmt_wait
      case symbol_kind::S_stmt_waittill: // stmt_waittill
      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
      case symbol_kind::S_stmt_if: // stmt_if
      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
      case symbol_kind::S_stmt_while: // stmt_while
      case symbol_kind::S_stmt_for: // stmt_for
      case symbol_kind::S_stmt_foreach: // stmt_foreach
      case symbol_kind::S_stmt_switch: // stmt_switch
      case symbol_kind::S_stmt_case: // stmt_case
      case symbol_kind::S_stmt_default: // stmt_default
      case symbol_kind::S_stmt_break: // stmt_break
      case symbol_kind::S_stmt_continue: // stmt_continue
      case symbol_kind::S_stmt_return: // stmt_return
      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_func_call_ptr: // expr_func_call_ptr
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_object: // object
      case symbol_kind::S_object_restricted: // object_restricted
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_num_float: // num_float
      case symbol_kind::S_num_integer: // num_integer
      case symbol_kind::S_string_hash: // string_hash
      case symbol_kind::S_string_loc: // string_loc
      case symbol_kind::S_string: // string
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_filepath: // filepath
        value.move< std::unique_ptr<node> > (that.value);
        break;

      case symbol_kind::S_expr_arg_list: // expr_arg_list
        value.move< std::unique_ptr<node_expr_arg_list> > (that.value);
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        value.move< std::unique_ptr<node_parameter_list> > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.move< std::unique_ptr<node_script> > (that.value);
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        value.move< std::unique_ptr<node_stmt_block> > (that.value);
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
      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_STRING_HASH: // STRING_HASH
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_include: // include
      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_function: // function
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_stmt_call: // stmt_call
      case symbol_kind::S_stmt_assign: // stmt_assign
      case symbol_kind::S_stmt_endon: // stmt_endon
      case symbol_kind::S_stmt_notify: // stmt_notify
      case symbol_kind::S_stmt_wait: // stmt_wait
      case symbol_kind::S_stmt_waittill: // stmt_waittill
      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
      case symbol_kind::S_stmt_if: // stmt_if
      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
      case symbol_kind::S_stmt_while: // stmt_while
      case symbol_kind::S_stmt_for: // stmt_for
      case symbol_kind::S_stmt_foreach: // stmt_foreach
      case symbol_kind::S_stmt_switch: // stmt_switch
      case symbol_kind::S_stmt_case: // stmt_case
      case symbol_kind::S_stmt_default: // stmt_default
      case symbol_kind::S_stmt_break: // stmt_break
      case symbol_kind::S_stmt_continue: // stmt_continue
      case symbol_kind::S_stmt_return: // stmt_return
      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_assign: // expr_assign
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_unary: // expr_unary
      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
      case symbol_kind::S_expr_func_call: // expr_func_call
      case symbol_kind::S_expr_func_call_ptr: // expr_func_call_ptr
      case symbol_kind::S_expr_select: // expr_select
      case symbol_kind::S_expr_subscribe: // expr_subscribe
      case symbol_kind::S_expr_func_ref: // expr_func_ref
      case symbol_kind::S_object: // object
      case symbol_kind::S_object_restricted: // object_restricted
      case symbol_kind::S_size: // size
      case symbol_kind::S_false: // false
      case symbol_kind::S_true: // true
      case symbol_kind::S_level: // level
      case symbol_kind::S_game: // game
      case symbol_kind::S_empty_array: // empty_array
      case symbol_kind::S_undefined: // undefined
      case symbol_kind::S_vector: // vector
      case symbol_kind::S_num: // num
      case symbol_kind::S_num_float: // num_float
      case symbol_kind::S_num_integer: // num_integer
      case symbol_kind::S_string_hash: // string_hash
      case symbol_kind::S_string_loc: // string_loc
      case symbol_kind::S_string: // string
      case symbol_kind::S_identifier: // identifier
      case symbol_kind::S_filepath: // filepath
        yylhs.value.emplace< std::unique_ptr<node> > ();
        break;

      case symbol_kind::S_expr_arg_list: // expr_arg_list
        yylhs.value.emplace< std::unique_ptr<node_expr_arg_list> > ();
        break;

      case symbol_kind::S_parameter_list: // parameter_list
        yylhs.value.emplace< std::unique_ptr<node_parameter_list> > ();
        break;

      case symbol_kind::S_script: // script
        yylhs.value.emplace< std::unique_ptr<node_script> > ();
        break;

      case symbol_kind::S_stmt_block: // stmt_block
        yylhs.value.emplace< std::unique_ptr<node_stmt_block> > ();
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
#line 91 "iw6.parser.ypp"
                { astout = std::move(yystack_[0].value.as < std::unique_ptr<node_script> > ()); }
#line 946 "./IW6/compiler_parser.cpp"
    break;

  case 3: // root: %empty
#line 93 "iw6.parser.ypp"
                { astout = std::make_unique<node>(); }
#line 952 "./IW6/compiler_parser.cpp"
    break;

  case 4: // script: script include
#line 98 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_script> > () = std::move(yystack_[1].value.as < std::unique_ptr<node_script> > ()); yylhs.value.as < std::unique_ptr<node_script> > ()->childs.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 958 "./IW6/compiler_parser.cpp"
    break;

  case 5: // script: script using_animtree
#line 100 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_script> > () = std::move(yystack_[1].value.as < std::unique_ptr<node_script> > ()); yylhs.value.as < std::unique_ptr<node_script> > ()->childs.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 964 "./IW6/compiler_parser.cpp"
    break;

  case 6: // script: script function
#line 102 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_script> > () = std::move(yystack_[1].value.as < std::unique_ptr<node_script> > ()); yylhs.value.as < std::unique_ptr<node_script> > ()->childs.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 970 "./IW6/compiler_parser.cpp"
    break;

  case 7: // script: include
#line 104 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_script> > () = std::make_unique<node_script>(); yylhs.value.as < std::unique_ptr<node_script> > ()->childs.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ()));}
#line 976 "./IW6/compiler_parser.cpp"
    break;

  case 8: // script: using_animtree
#line 106 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_script> > () = std::make_unique<node_script>(); yylhs.value.as < std::unique_ptr<node_script> > ()->childs.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ()));}
#line 982 "./IW6/compiler_parser.cpp"
    break;

  case 9: // script: function
#line 108 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_script> > () = std::make_unique<node_script>(); yylhs.value.as < std::unique_ptr<node_script> > ()->childs.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ()));}
#line 988 "./IW6/compiler_parser.cpp"
    break;

  case 10: // include: INCLUDE filepath SEMICOLON
#line 113 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_include>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 994 "./IW6/compiler_parser.cpp"
    break;

  case 11: // include: INCLUDE identifier SEMICOLON
#line 115 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_include>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1000 "./IW6/compiler_parser.cpp"
    break;

  case 12: // using_animtree: USING_ANIMTREE LPAREN string RPAREN SEMICOLON
#line 120 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_using_animtree>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ())); }
#line 1006 "./IW6/compiler_parser.cpp"
    break;

  case 13: // function: identifier LPAREN parameter_list RPAREN LBRACE stmt_block RBRACE
#line 125 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_function>(std::move(yystack_[6].value.as < std::unique_ptr<node> > ()), std::move(yystack_[4].value.as < std::unique_ptr<node_parameter_list> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_stmt_block> > ())); }
#line 1012 "./IW6/compiler_parser.cpp"
    break;

  case 14: // parameter_list: parameter_list COMMA identifier
#line 130 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_parameter_list> > () = std::move(yystack_[2].value.as < std::unique_ptr<node_parameter_list> > ()); yylhs.value.as < std::unique_ptr<node_parameter_list> > ()->params.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1018 "./IW6/compiler_parser.cpp"
    break;

  case 15: // parameter_list: identifier
#line 132 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_parameter_list> > () = std::make_unique<node_parameter_list>(); yylhs.value.as < std::unique_ptr<node_parameter_list> > ()->params.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1024 "./IW6/compiler_parser.cpp"
    break;

  case 16: // parameter_list: %empty
#line 134 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_parameter_list> > () = std::make_unique<node_parameter_list>(); }
#line 1030 "./IW6/compiler_parser.cpp"
    break;

  case 17: // stmt_block: stmt_block stmt
#line 139 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_stmt_block> > () = std::move(yystack_[1].value.as < std::unique_ptr<node_stmt_block> > ()); yylhs.value.as < std::unique_ptr<node_stmt_block> > ()->stmts.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1036 "./IW6/compiler_parser.cpp"
    break;

  case 18: // stmt_block: stmt
#line 141 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_stmt_block> > () = std::make_unique<node_stmt_block>(); yylhs.value.as < std::unique_ptr<node_stmt_block> > ()->stmts.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1042 "./IW6/compiler_parser.cpp"
    break;

  case 19: // stmt_block: %empty
#line 143 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node_stmt_block> > () = std::make_unique<node_stmt_block>(); }
#line 1048 "./IW6/compiler_parser.cpp"
    break;

  case 20: // stmt: stmt_call
#line 148 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1054 "./IW6/compiler_parser.cpp"
    break;

  case 21: // stmt: stmt_assign
#line 149 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1060 "./IW6/compiler_parser.cpp"
    break;

  case 22: // stmt: stmt_endon
#line 150 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1066 "./IW6/compiler_parser.cpp"
    break;

  case 23: // stmt: stmt_notify
#line 151 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1072 "./IW6/compiler_parser.cpp"
    break;

  case 24: // stmt: stmt_wait
#line 152 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1078 "./IW6/compiler_parser.cpp"
    break;

  case 25: // stmt: stmt_waittill
#line 153 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1084 "./IW6/compiler_parser.cpp"
    break;

  case 26: // stmt: stmt_waittillmatch
#line 154 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1090 "./IW6/compiler_parser.cpp"
    break;

  case 27: // stmt: stmt_waittillframeend
#line 155 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1096 "./IW6/compiler_parser.cpp"
    break;

  case 28: // stmt: stmt_if
#line 156 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1102 "./IW6/compiler_parser.cpp"
    break;

  case 29: // stmt: stmt_ifelse
#line 157 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1108 "./IW6/compiler_parser.cpp"
    break;

  case 30: // stmt: stmt_while
#line 158 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1114 "./IW6/compiler_parser.cpp"
    break;

  case 31: // stmt: stmt_for
#line 159 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1120 "./IW6/compiler_parser.cpp"
    break;

  case 32: // stmt: stmt_foreach
#line 160 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1126 "./IW6/compiler_parser.cpp"
    break;

  case 33: // stmt: stmt_switch
#line 161 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1132 "./IW6/compiler_parser.cpp"
    break;

  case 34: // stmt: stmt_case
#line 162 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1138 "./IW6/compiler_parser.cpp"
    break;

  case 35: // stmt: stmt_default
#line 163 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1144 "./IW6/compiler_parser.cpp"
    break;

  case 36: // stmt: stmt_break
#line 164 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1150 "./IW6/compiler_parser.cpp"
    break;

  case 37: // stmt: stmt_continue
#line 165 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1156 "./IW6/compiler_parser.cpp"
    break;

  case 38: // stmt: stmt_return
#line 166 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1162 "./IW6/compiler_parser.cpp"
    break;

  case 39: // stmt_call: expr_call SEMICOLON
#line 171 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_call>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1168 "./IW6/compiler_parser.cpp"
    break;

  case 40: // stmt_call: expr_call_thread SEMICOLON
#line 173 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_call>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1174 "./IW6/compiler_parser.cpp"
    break;

  case 41: // stmt_assign: expr_assign SEMICOLON
#line 178 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_assign>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1180 "./IW6/compiler_parser.cpp"
    break;

  case 42: // stmt_endon: object_restricted ENDON LPAREN expr RPAREN SEMICOLON
#line 183 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_endon>(std::move(yystack_[5].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node> > ())); }
#line 1186 "./IW6/compiler_parser.cpp"
    break;

  case 43: // stmt_notify: object_restricted NOTIFY LPAREN expr COMMA expr_arg_list RPAREN SEMICOLON
#line 188 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_notify>(std::move(yystack_[7].value.as < std::unique_ptr<node> > ()), std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node_expr_arg_list> > ())); }
#line 1192 "./IW6/compiler_parser.cpp"
    break;

  case 44: // stmt_notify: object_restricted NOTIFY LPAREN expr RPAREN SEMICOLON
#line 190 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_notify>(std::move(yystack_[5].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::make_unique<node>()); }
#line 1198 "./IW6/compiler_parser.cpp"
    break;

  case 45: // stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON
#line 195 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_wait>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ())); }
#line 1204 "./IW6/compiler_parser.cpp"
    break;

  case 46: // stmt_wait: WAIT num SEMICOLON
#line 197 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_wait>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1210 "./IW6/compiler_parser.cpp"
    break;

  case 47: // stmt_waittill: object_restricted WAITTILL LPAREN expr COMMA expr_arg_list RPAREN SEMICOLON
#line 202 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_waittill>(std::move(yystack_[7].value.as < std::unique_ptr<node> > ()), std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node_expr_arg_list> > ())); }
#line 1216 "./IW6/compiler_parser.cpp"
    break;

  case 48: // stmt_waittill: object_restricted WAITTILL LPAREN expr RPAREN SEMICOLON
#line 204 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_waittill>(std::move(yystack_[5].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::make_unique<node>()); }
#line 1222 "./IW6/compiler_parser.cpp"
    break;

  case 49: // stmt_waittillmatch: object_restricted WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON
#line 209 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_waittillmatch>(std::move(yystack_[7].value.as < std::unique_ptr<node> > ()), std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node> > ())); }
#line 1228 "./IW6/compiler_parser.cpp"
    break;

  case 50: // stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON
#line 214 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_waittillframeend>(); }
#line 1234 "./IW6/compiler_parser.cpp"
    break;

  case 51: // stmt_if: IF LPAREN expr RPAREN LBRACE stmt_block RBRACE
#line 219 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_if>(std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_stmt_block> > ())); }
#line 1240 "./IW6/compiler_parser.cpp"
    break;

  case 52: // stmt_if: IF LPAREN expr RPAREN stmt
#line 221 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_if>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1246 "./IW6/compiler_parser.cpp"
    break;

  case 53: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE stmt_block RBRACE ELSE LBRACE stmt_block RBRACE
#line 226 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[8].value.as < std::unique_ptr<node> > ()), std::move(yystack_[5].value.as < std::unique_ptr<node_stmt_block> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_stmt_block> > ())); }
#line 1252 "./IW6/compiler_parser.cpp"
    break;

  case 54: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE stmt_block RBRACE
#line 228 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[6].value.as < std::unique_ptr<node> > ()), std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_stmt_block> > ())); }
#line 1258 "./IW6/compiler_parser.cpp"
    break;

  case 55: // stmt_ifelse: IF LPAREN expr RPAREN LBRACE stmt_block RBRACE ELSE stmt
#line 230 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[6].value.as < std::unique_ptr<node> > ()), std::move(yystack_[3].value.as < std::unique_ptr<node_stmt_block> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1264 "./IW6/compiler_parser.cpp"
    break;

  case 56: // stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt
#line 232 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_ifelse>(std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1270 "./IW6/compiler_parser.cpp"
    break;

  case 57: // stmt_while: WHILE LPAREN expr RPAREN LBRACE stmt_block RBRACE
#line 237 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_while>(std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_stmt_block> > ())); }
#line 1276 "./IW6/compiler_parser.cpp"
    break;

  case 58: // stmt_while: WHILE LPAREN expr RPAREN stmt
#line 239 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_while>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1282 "./IW6/compiler_parser.cpp"
    break;

  case 59: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE stmt_block RBRACE
#line 244 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_for>(std::move(yystack_[8].value.as < std::unique_ptr<node> > ()), std::move(yystack_[6].value.as < std::unique_ptr<node> > ()), std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_stmt_block> > ())); }
#line 1288 "./IW6/compiler_parser.cpp"
    break;

  case 60: // stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt
#line 246 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique< node_stmt_for>(std::move(yystack_[6].value.as < std::unique_ptr<node> > ()), std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1294 "./IW6/compiler_parser.cpp"
    break;

  case 61: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE stmt_block RBRACE
#line 251 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_foreach>(std::move(yystack_[6].value.as < std::unique_ptr<node> > ()), std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_stmt_block> > ())); }
#line 1300 "./IW6/compiler_parser.cpp"
    break;

  case 62: // stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt
#line 253 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_foreach>(std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1306 "./IW6/compiler_parser.cpp"
    break;

  case 63: // stmt_switch: SWITCH LPAREN expr RPAREN LBRACE stmt_block RBRACE
#line 258 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_switch>(std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_stmt_block> > ())); }
#line 1312 "./IW6/compiler_parser.cpp"
    break;

  case 64: // stmt_case: CASE num_integer COLON
#line 263 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_case>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1318 "./IW6/compiler_parser.cpp"
    break;

  case 65: // stmt_case: CASE string COLON
#line 265 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_case>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1324 "./IW6/compiler_parser.cpp"
    break;

  case 66: // stmt_default: DEFAULT COLON
#line 270 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_default>(); }
#line 1330 "./IW6/compiler_parser.cpp"
    break;

  case 67: // stmt_break: BREAK SEMICOLON
#line 275 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_break>(); }
#line 1336 "./IW6/compiler_parser.cpp"
    break;

  case 68: // stmt_continue: CONTINUE SEMICOLON
#line 279 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_continue>(); }
#line 1342 "./IW6/compiler_parser.cpp"
    break;

  case 69: // stmt_return: RETURN expr SEMICOLON
#line 284 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_return>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1348 "./IW6/compiler_parser.cpp"
    break;

  case 70: // stmt_return: RETURN SEMICOLON
#line 286 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_stmt_return>(std::make_unique<node>()); }
#line 1354 "./IW6/compiler_parser.cpp"
    break;

  case 71: // for_assign: expr_assign
#line 290 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1360 "./IW6/compiler_parser.cpp"
    break;

  case 72: // for_assign: %empty
#line 291 "iw6.parser.ypp"
                                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node>(); }
#line 1366 "./IW6/compiler_parser.cpp"
    break;

  case 73: // for_cond: expr_cmp
#line 295 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1372 "./IW6/compiler_parser.cpp"
    break;

  case 74: // for_cond: %empty
#line 296 "iw6.parser.ypp"
                                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node>(); }
#line 1378 "./IW6/compiler_parser.cpp"
    break;

  case 75: // expr: expr_cmp
#line 301 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1384 "./IW6/compiler_parser.cpp"
    break;

  case 76: // expr: expr_ternary
#line 302 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1390 "./IW6/compiler_parser.cpp"
    break;

  case 77: // expr: expr_binary
#line 303 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1396 "./IW6/compiler_parser.cpp"
    break;

  case 78: // expr: expr_unary
#line 304 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1402 "./IW6/compiler_parser.cpp"
    break;

  case 79: // expr_assign: object_restricted INC
#line 308 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_inc>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1408 "./IW6/compiler_parser.cpp"
    break;

  case 80: // expr_assign: object_restricted DEC
#line 309 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_dec>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1414 "./IW6/compiler_parser.cpp"
    break;

  case 81: // expr_assign: object_restricted ASSIGN expr
#line 310 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1420 "./IW6/compiler_parser.cpp"
    break;

  case 82: // expr_assign: object_restricted ASSIGN_BW_OR expr
#line 311 "iw6.parser.ypp"
                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_bw_or>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1426 "./IW6/compiler_parser.cpp"
    break;

  case 83: // expr_assign: object_restricted ASSIGN_BW_AND expr
#line 312 "iw6.parser.ypp"
                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_bw_and>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1432 "./IW6/compiler_parser.cpp"
    break;

  case 84: // expr_assign: object_restricted ASSIGN_BW_XOR expr
#line 313 "iw6.parser.ypp"
                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_bw_xor>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1438 "./IW6/compiler_parser.cpp"
    break;

  case 85: // expr_assign: object_restricted ASSIGN_LSHIFT expr
#line 314 "iw6.parser.ypp"
                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_shift_left>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()),std::move( yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1444 "./IW6/compiler_parser.cpp"
    break;

  case 86: // expr_assign: object_restricted ASSIGN_RSHIFT expr
#line 315 "iw6.parser.ypp"
                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_shift_right>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1450 "./IW6/compiler_parser.cpp"
    break;

  case 87: // expr_assign: object_restricted ASSIGN_ADD expr
#line 316 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_add>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1456 "./IW6/compiler_parser.cpp"
    break;

  case 88: // expr_assign: object_restricted ASSIGN_SUB expr
#line 317 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_sub>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1462 "./IW6/compiler_parser.cpp"
    break;

  case 89: // expr_assign: object_restricted ASSIGN_MULT expr
#line 318 "iw6.parser.ypp"
                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_mult>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1468 "./IW6/compiler_parser.cpp"
    break;

  case 90: // expr_assign: object_restricted ASSIGN_DIV expr
#line 319 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_div>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1474 "./IW6/compiler_parser.cpp"
    break;

  case 91: // expr_assign: object_restricted ASSIGN_MOD expr
#line 320 "iw6.parser.ypp"
                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_assign_mod>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1480 "./IW6/compiler_parser.cpp"
    break;

  case 92: // expr_cmp: expr CMP_OR expr
#line 324 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_cmp_or>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1486 "./IW6/compiler_parser.cpp"
    break;

  case 93: // expr_cmp: expr CMP_AND expr
#line 325 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_cmp_and>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1492 "./IW6/compiler_parser.cpp"
    break;

  case 94: // expr_cmp: expr CMP_EQUAL expr
#line 326 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_cmp_equal>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1498 "./IW6/compiler_parser.cpp"
    break;

  case 95: // expr_cmp: expr CMP_NOT_EQ expr
#line 327 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_cmp_not_equal>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1504 "./IW6/compiler_parser.cpp"
    break;

  case 96: // expr_cmp: expr CMP_LESS_EQ expr
#line 328 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_cmp_less_equal>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1510 "./IW6/compiler_parser.cpp"
    break;

  case 97: // expr_cmp: expr CMP_GREATER_EQ expr
#line 329 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_cmp_greater_equal>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1516 "./IW6/compiler_parser.cpp"
    break;

  case 98: // expr_cmp: expr CMP_LESS expr
#line 330 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_cmp_less>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1522 "./IW6/compiler_parser.cpp"
    break;

  case 99: // expr_cmp: expr CMP_GREATER expr
#line 331 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_cmp_greater>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1528 "./IW6/compiler_parser.cpp"
    break;

  case 100: // expr_ternary: expr_cmp QMARK expr COLON expr
#line 335 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_ternary>(std::move(yystack_[4].value.as < std::unique_ptr<node> > ()), std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1534 "./IW6/compiler_parser.cpp"
    break;

  case 101: // expr_binary: expr BW_OR expr
#line 339 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_bw_or>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1540 "./IW6/compiler_parser.cpp"
    break;

  case 102: // expr_binary: expr BW_AND expr
#line 340 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_bw_and>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1546 "./IW6/compiler_parser.cpp"
    break;

  case 103: // expr_binary: expr BW_XOR expr
#line 341 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_bw_xor>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1552 "./IW6/compiler_parser.cpp"
    break;

  case 104: // expr_binary: expr LSHIFT expr
#line 342 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_shift_left>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1558 "./IW6/compiler_parser.cpp"
    break;

  case 105: // expr_binary: expr RSHIFT expr
#line 343 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_shift_right>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1564 "./IW6/compiler_parser.cpp"
    break;

  case 106: // expr_binary: expr ADD expr
#line 344 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_add>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1570 "./IW6/compiler_parser.cpp"
    break;

  case 107: // expr_binary: expr SUB expr
#line 345 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_sub>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1576 "./IW6/compiler_parser.cpp"
    break;

  case 108: // expr_binary: expr MULT expr
#line 346 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_mult>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1582 "./IW6/compiler_parser.cpp"
    break;

  case 109: // expr_binary: expr DIV expr
#line 347 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_div>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1588 "./IW6/compiler_parser.cpp"
    break;

  case 110: // expr_binary: expr MOD expr
#line 348 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_mod>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1594 "./IW6/compiler_parser.cpp"
    break;

  case 111: // expr_unary: COMPLEMENT expr
#line 352 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_complement>(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1600 "./IW6/compiler_parser.cpp"
    break;

  case 112: // expr_unary: NOT expr
#line 353 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_not>(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1606 "./IW6/compiler_parser.cpp"
    break;

  case 113: // expr_unary: expr_call
#line 354 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1612 "./IW6/compiler_parser.cpp"
    break;

  case 114: // expr_unary: expr_call_thread
#line 355 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1618 "./IW6/compiler_parser.cpp"
    break;

  case 115: // expr_unary: expr_select
#line 356 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1624 "./IW6/compiler_parser.cpp"
    break;

  case 116: // expr_unary: expr_subscribe
#line 357 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1630 "./IW6/compiler_parser.cpp"
    break;

  case 117: // expr_unary: expr_func_ref
#line 358 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1636 "./IW6/compiler_parser.cpp"
    break;

  case 118: // expr_unary: empty_array
#line 359 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1642 "./IW6/compiler_parser.cpp"
    break;

  case 119: // expr_unary: undefined
#line 360 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1648 "./IW6/compiler_parser.cpp"
    break;

  case 120: // expr_unary: LPAREN expr COMMA expr COMMA expr RPAREN
#line 361 "iw6.parser.ypp"
                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_vector>(std::move(yystack_[5].value.as < std::unique_ptr<node> > ()), std::move(yystack_[3].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1654 "./IW6/compiler_parser.cpp"
    break;

  case 121: // expr_unary: vector
#line 362 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1660 "./IW6/compiler_parser.cpp"
    break;

  case 122: // expr_unary: num
#line 363 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1666 "./IW6/compiler_parser.cpp"
    break;

  case 123: // expr_unary: string_hash
#line 364 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1672 "./IW6/compiler_parser.cpp"
    break;

  case 124: // expr_unary: string_loc
#line 365 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1678 "./IW6/compiler_parser.cpp"
    break;

  case 125: // expr_unary: string
#line 366 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1684 "./IW6/compiler_parser.cpp"
    break;

  case 126: // expr_unary: identifier
#line 367 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1690 "./IW6/compiler_parser.cpp"
    break;

  case 127: // expr_unary: LPAREN expr RPAREN
#line 368 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[1].value.as < std::unique_ptr<node> > ()); }
#line 1696 "./IW6/compiler_parser.cpp"
    break;

  case 128: // expr_call: expr_func_call
#line 372 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_call>(std::make_unique<node>(), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1702 "./IW6/compiler_parser.cpp"
    break;

  case 129: // expr_call: expr_func_call_ptr
#line 373 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_call>(std::make_unique<node>(), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1708 "./IW6/compiler_parser.cpp"
    break;

  case 130: // expr_call: object expr_func_call
#line 374 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_call>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1714 "./IW6/compiler_parser.cpp"
    break;

  case 131: // expr_call: object expr_func_call_ptr
#line 375 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_call>(std::move(yystack_[1].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1720 "./IW6/compiler_parser.cpp"
    break;

  case 132: // expr_call_thread: THREAD expr_func_call
#line 379 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_call_thread>(std::make_unique<node>(), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1726 "./IW6/compiler_parser.cpp"
    break;

  case 133: // expr_call_thread: THREAD expr_func_call_ptr
#line 380 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_call_thread>(std::make_unique<node>(), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1732 "./IW6/compiler_parser.cpp"
    break;

  case 134: // expr_call_thread: object THREAD expr_func_call
#line 381 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_call_thread>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1738 "./IW6/compiler_parser.cpp"
    break;

  case 135: // expr_call_thread: object THREAD expr_func_call_ptr
#line 382 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_call_thread>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1744 "./IW6/compiler_parser.cpp"
    break;

  case 136: // expr_func_call: identifier LPAREN expr_arg_list RPAREN
#line 387 "iw6.parser.ypp"
                                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_func_call>(std::make_unique<node>(), std::move(yystack_[3].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_expr_arg_list> > ())); }
#line 1750 "./IW6/compiler_parser.cpp"
    break;

  case 137: // expr_func_call: filepath DOUBLECOLON identifier LPAREN expr_arg_list RPAREN
#line 388 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_func_call>(std::move(yystack_[5].value.as < std::unique_ptr<node> > ()), std::move(yystack_[3].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_expr_arg_list> > ())); }
#line 1756 "./IW6/compiler_parser.cpp"
    break;

  case 138: // expr_func_call: identifier DOUBLECOLON identifier LPAREN expr_arg_list RPAREN
#line 389 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_func_call>(std::move(yystack_[5].value.as < std::unique_ptr<node> > ()), std::move(yystack_[3].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_expr_arg_list> > ())); }
#line 1762 "./IW6/compiler_parser.cpp"
    break;

  case 139: // expr_func_call_ptr: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arg_list RPAREN
#line 395 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_func_call_ptr>(std::move(yystack_[5].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node_expr_arg_list> > ())); }
#line 1768 "./IW6/compiler_parser.cpp"
    break;

  case 140: // expr_arg_list: expr_arg_list COMMA expr
#line 399 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node_expr_arg_list> > () = std::move(yystack_[2].value.as < std::unique_ptr<node_expr_arg_list> > ()); yylhs.value.as < std::unique_ptr<node_expr_arg_list> > ()->args.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1774 "./IW6/compiler_parser.cpp"
    break;

  case 141: // expr_arg_list: expr
#line 400 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node_expr_arg_list> > () = std::make_unique<node_expr_arg_list>(); yylhs.value.as < std::unique_ptr<node_expr_arg_list> > ()->args.push_back(std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1780 "./IW6/compiler_parser.cpp"
    break;

  case 142: // expr_arg_list: %empty
#line 401 "iw6.parser.ypp"
                                                                                                { yylhs.value.as < std::unique_ptr<node_expr_arg_list> > () = std::make_unique<node_expr_arg_list>(); }
#line 1786 "./IW6/compiler_parser.cpp"
    break;

  case 143: // expr_select: object DOT identifier
#line 406 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_select>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1792 "./IW6/compiler_parser.cpp"
    break;

  case 144: // expr_select: object DOT size
#line 407 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_select>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1798 "./IW6/compiler_parser.cpp"
    break;

  case 145: // expr_subscribe: object LBRACKET expr RBRACKET
#line 412 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_subscribe>(std::move(yystack_[3].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1804 "./IW6/compiler_parser.cpp"
    break;

  case 146: // expr_func_ref: DOUBLECOLON identifier
#line 417 "iw6.parser.ypp"
                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_func_ref>(std::make_unique<node>(), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1810 "./IW6/compiler_parser.cpp"
    break;

  case 147: // expr_func_ref: identifier DOUBLECOLON identifier
#line 418 "iw6.parser.ypp"
                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_func_ref>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1816 "./IW6/compiler_parser.cpp"
    break;

  case 148: // expr_func_ref: filepath DOUBLECOLON identifier
#line 419 "iw6.parser.ypp"
                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_expr_func_ref>(std::move(yystack_[2].value.as < std::unique_ptr<node> > ()), std::move(yystack_[0].value.as < std::unique_ptr<node> > ())); }
#line 1822 "./IW6/compiler_parser.cpp"
    break;

  case 149: // object: expr_call
#line 424 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1828 "./IW6/compiler_parser.cpp"
    break;

  case 150: // object: object_restricted
#line 425 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1834 "./IW6/compiler_parser.cpp"
    break;

  case 151: // object_restricted: expr_subscribe
#line 430 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1840 "./IW6/compiler_parser.cpp"
    break;

  case 152: // object_restricted: expr_select
#line 431 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1846 "./IW6/compiler_parser.cpp"
    break;

  case 153: // object_restricted: identifier
#line 432 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1852 "./IW6/compiler_parser.cpp"
    break;

  case 154: // object_restricted: level
#line 433 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1858 "./IW6/compiler_parser.cpp"
    break;

  case 155: // object_restricted: game
#line 434 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1864 "./IW6/compiler_parser.cpp"
    break;

  case 156: // size: SIZE
#line 439 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_size>(); }
#line 1870 "./IW6/compiler_parser.cpp"
    break;

  case 157: // false: FALSE
#line 444 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_num_integer>("0"); }
#line 1876 "./IW6/compiler_parser.cpp"
    break;

  case 158: // true: TRUE
#line 449 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_num_integer>("1"); }
#line 1882 "./IW6/compiler_parser.cpp"
    break;

  case 159: // level: LEVEL
#line 454 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_level>(); }
#line 1888 "./IW6/compiler_parser.cpp"
    break;

  case 160: // game: GAME
#line 459 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_game>(); }
#line 1894 "./IW6/compiler_parser.cpp"
    break;

  case 161: // empty_array: EMPTY_ARRAY
#line 464 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_empty_array>(); }
#line 1900 "./IW6/compiler_parser.cpp"
    break;

  case 162: // undefined: UNDEFINED
#line 469 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_undefined>(); }
#line 1906 "./IW6/compiler_parser.cpp"
    break;

  case 163: // vector: LPAREN num COMMA num COMMA num RPAREN
#line 474 "iw6.parser.ypp"
                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_vector>(std::move(yystack_[5].value.as < std::unique_ptr<node> > ()), std::move(yystack_[3].value.as < std::unique_ptr<node> > ()), std::move(yystack_[1].value.as < std::unique_ptr<node> > ())); }
#line 1912 "./IW6/compiler_parser.cpp"
    break;

  case 164: // num: num_float
#line 478 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1918 "./IW6/compiler_parser.cpp"
    break;

  case 165: // num: num_integer
#line 479 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1924 "./IW6/compiler_parser.cpp"
    break;

  case 166: // num: false
#line 480 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1930 "./IW6/compiler_parser.cpp"
    break;

  case 167: // num: true
#line 481 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::move(yystack_[0].value.as < std::unique_ptr<node> > ()); }
#line 1936 "./IW6/compiler_parser.cpp"
    break;

  case 168: // num_float: FLOAT
#line 485 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_num_float>(yystack_[0].value.as < std::string > ()); }
#line 1942 "./IW6/compiler_parser.cpp"
    break;

  case 169: // num_integer: INTEGER
#line 489 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_num_integer>(yystack_[0].value.as < std::string > ()); }
#line 1948 "./IW6/compiler_parser.cpp"
    break;

  case 170: // string_hash: STRING_HASH
#line 493 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_string_hash>(yystack_[0].value.as < std::string > ()); }
#line 1954 "./IW6/compiler_parser.cpp"
    break;

  case 171: // string_loc: STRING_LOC
#line 497 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_string_loc>(yystack_[0].value.as < std::string > ()); }
#line 1960 "./IW6/compiler_parser.cpp"
    break;

  case 172: // string: STRING
#line 501 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_string>(yystack_[0].value.as < std::string > ()); }
#line 1966 "./IW6/compiler_parser.cpp"
    break;

  case 173: // identifier: IDENTIFIER
#line 505 "iw6.parser.ypp"
                                                                                { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_identifier>(yystack_[0].value.as < std::string > ()); }
#line 1972 "./IW6/compiler_parser.cpp"
    break;

  case 174: // filepath: FILEPATH
#line 509 "iw6.parser.ypp"
                                                                                        { yylhs.value.as < std::unique_ptr<node> > () = std::make_unique<node_filepath>(yystack_[0].value.as < std::string > ()); }
#line 1978 "./IW6/compiler_parser.cpp"
    break;


#line 1982 "./IW6/compiler_parser.cpp"

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
  "UNDEFINED", "TRUE", "FALSE", "SIZE", "GAME", "LEVEL", "EMPTY_ARRAY",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COMMA",
  "DOT", "DOUBLECOLON", "COLON", "SEMICOLON", "QMARK", "MOD", "INC", "DEC",
  "LSHIFT", "RSHIFT", "CMP_OR", "CMP_AND", "CMP_EQUAL", "CMP_NOT_EQ",
  "CMP_LESS_EQ", "CMP_GREATER_EQ", "CMP_LESS", "CMP_GREATER", "ASSIGN",
  "ASSIGN_ADD", "ASSIGN_SUB", "ASSIGN_MULT", "ASSIGN_DIV", "ASSIGN_MOD",
  "ASSIGN_BW_OR", "ASSIGN_BW_AND", "ASSIGN_BW_XOR", "ASSIGN_LSHIFT",
  "ASSIGN_RSHIFT", "BW_OR", "BW_AND", "BW_XOR", "ADD", "SUB", "MULT",
  "DIV", "NOT", "COMPLEMENT", "FILEPATH", "IDENTIFIER", "STRING",
  "STRING_LOC", "STRING_HASH", "FLOAT", "INTEGER", "IFX", "$accept",
  "root", "script", "include", "using_animtree", "function",
  "parameter_list", "stmt_block", "stmt", "stmt_call", "stmt_assign",
  "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_for", "stmt_foreach", "stmt_switch", "stmt_case",
  "stmt_default", "stmt_break", "stmt_continue", "stmt_return",
  "for_assign", "for_cond", "expr", "expr_assign", "expr_cmp",
  "expr_ternary", "expr_binary", "expr_unary", "expr_call",
  "expr_call_thread", "expr_func_call", "expr_func_call_ptr",
  "expr_arg_list", "expr_select", "expr_subscribe", "expr_func_ref",
  "object", "object_restricted", "size", "false", "true", "level", "game",
  "empty_array", "undefined", "vector", "num", "num_float", "num_integer",
  "string_hash", "string_loc", "string", "identifier", "filepath", YY_NULLPTR
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


  const short parser::yypact_ninf_ = -260;

  const short parser::yytable_ninf_ = -154;

  const short
  parser::yypact_[] =
  {
       8,    17,    14,  -260,    48,     8,  -260,  -260,  -260,    18,
    -260,    41,    56,    11,  -260,  -260,  -260,  -260,   -18,  -260,
    -260,  -260,    68,   -19,  -260,    75,    81,   -18,  -260,  1099,
    -260,    86,    87,   -57,    82,    80,    94,    99,   104,    95,
    1113,    26,   160,    96,  -260,  -260,   108,    22,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,   103,   123,
     138,  -260,  -260,  -260,  -260,    91,  1248,  -260,  -260,   -23,
     148,  1131,  1131,  -260,   140,   142,  -260,  -260,   174,  1131,
    1131,  -260,  -260,  -260,  -260,  -260,  1131,   -18,  -260,  1131,
    1131,  -260,  -260,  -260,  1832,   153,  -260,  -260,  -260,   107,
    -260,   143,   161,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,    89,   149,  -260,  -260,
     -23,  1131,   156,  -260,  1131,  -260,  -260,  -260,  -260,  -260,
      26,  1198,   -25,  -260,  -260,   173,   176,   177,   179,  -260,
    -260,  1131,  1131,  1131,  1131,  1131,  1131,  1131,  1131,  1131,
    1131,  1131,  1131,   -18,   -18,  1398,  1429,  -260,  -260,   164,
    -260,  -260,    57,   661,  1192,  1460,  1283,   178,  -260,  1863,
    1863,  -260,  1131,  1131,  1131,  1131,  1131,  1131,  1131,  1131,
    1131,  1131,  1131,  1131,  1131,  1131,  1131,  1131,  1131,  1131,
    1131,   -18,   -18,  1491,  -260,  1653,  -260,  -260,  1198,  1691,
    -260,  -260,  -260,  1131,  1131,  1131,  1131,  1863,  1863,  1863,
    1863,  1863,  1863,  1863,  1863,  1863,  1863,  1863,  1863,   -17,
     180,   183,    55,   188,  1131,  1131,   345,  -260,  1131,    -3,
    1863,  1863,  1863,  1863,  1863,  1863,  1863,  1863,  1863,  1863,
    1863,  1863,  1863,  1863,  1863,  1863,  1863,  1863,  1799,   180,
     183,   181,   187,  -260,  1325,  1728,  1522,  1367,  -260,  1131,
    1131,  1131,  1099,   218,  1099,   184,  1863,    70,  1553,  1099,
    -260,  1765,   189,  1131,  -260,   196,   191,  1131,  1131,   193,
     195,  1131,  1863,    16,    44,   141,   418,   491,   174,   564,
     637,  1131,    -3,  1863,  1131,  -260,    54,  1584,  -260,  -260,
      72,  -260,  -260,   222,  1099,  -260,  -260,   197,  1099,  -260,
    -260,  1615,   198,    78,   199,   202,   204,   870,   899,   952,
     981,  -260,  -260,  -260,  -260,  -260,  -260,  1099,  -260,  -260,
    1099,  -260,  -260,  1025,  1056,  -260,  -260
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,   173,     0,     2,     7,     8,     9,     0,
     174,     0,     0,     0,     1,     4,     5,     6,    16,    11,
      10,   172,     0,     0,    15,     0,     0,     0,    12,    19,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   160,   159,     0,     0,    18,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,     0,   149,
       0,   128,   129,   152,   151,     0,   150,   154,   155,   153,
       0,     0,     0,   169,     0,     0,    66,    67,    72,     0,
       0,    68,   162,   158,   157,   161,     0,     0,    70,     0,
       0,   171,   170,   168,     0,    75,    76,    77,    78,   113,
     114,   115,   116,   117,   150,   166,   167,   118,   119,   121,
     122,   164,   165,   123,   124,   125,   126,     0,   132,   133,
       0,     0,     0,    50,     0,    13,    17,    41,    39,    40,
       0,     0,     0,   130,   131,     0,     0,     0,     0,    79,
      80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,     0,     0,     0,     0,    64,    65,     0,
      71,   149,     0,   150,     0,     0,     0,   122,   146,   112,
     111,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,     0,   134,   135,     0,     0,
     156,   144,   143,     0,     0,     0,     0,    81,    87,    88,
      89,    90,    91,    82,    83,    84,    85,    86,   141,     0,
       0,     0,     0,     0,    74,     0,     0,   127,     0,     0,
     110,   104,   105,    92,    93,    94,    95,    96,    97,    98,
      99,   101,   102,   103,   106,   107,   108,   109,     0,   147,
     148,     0,     0,   145,     0,     0,     0,     0,   136,     0,
     142,   142,    19,    52,    19,     0,     0,    75,     0,    19,
      58,     0,     0,     0,    45,     0,     0,   142,     0,     0,
       0,   142,   140,     0,     0,     0,     0,     0,    72,     0,
       0,     0,     0,   100,   142,    48,     0,     0,    42,    44,
       0,   138,   137,    51,    19,    56,    63,     0,    19,    62,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   120,   163,   139,    47,    49,    43,    19,    55,    54,
      19,    60,    61,     0,     0,    53,    59
  };

  const short
  parser::yypgoto_[] =
  {
    -260,  -260,  -260,   235,   242,   244,  -260,  -259,   -41,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,   -48,  -260,
     658,   -84,    19,  -260,  -260,  -260,   146,   438,   -33,   -31,
     -97,   219,   292,  -260,   -81,   365,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,   -40,  -260,   224,  -260,  -260,    12,
       0,    73
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,     8,    23,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,   169,   275,
     228,    68,   105,   106,   107,   108,   109,   110,    71,    72,
     229,   111,   112,   113,    75,   114,   211,   115,   116,    77,
      78,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127
  };

  const short
  parser::yytable_[] =
  {
       9,    11,   132,   210,   170,     9,   136,   172,   128,   162,
     129,     1,     2,   295,    26,   297,   268,   163,    24,    27,
     300,   269,    21,    93,    94,    22,    83,    30,    31,    79,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,   130,   143,    43,   144,    85,    13,    79,    14,   311,
      18,    44,    45,     3,   269,   328,   177,   135,    46,   330,
       3,    31,    46,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    12,   130,    43,   312,   343,   103,
      83,   344,   269,    19,    44,    45,     3,   324,    79,   272,
      21,    46,   269,   141,    10,     3,   142,   178,    20,    10,
       3,    25,    80,    10,     3,   326,  -153,   206,   140,   207,
     269,   333,   -73,   200,    80,    29,   269,    28,    81,    82,
      80,   162,    87,    86,  -149,  -153,    88,   141,  -153,   201,
     142,    89,    10,     3,    10,     3,    90,    91,   133,   143,
     130,   144,   212,  -149,   134,   137,  -149,    31,    80,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
    -152,    80,    43,   230,   231,   138,  -153,  -153,    10,     3,
      44,    45,   130,   293,   294,    69,   313,    46,  -151,  -152,
     139,   167,  -152,   168,  -149,  -149,    93,    94,   164,   202,
     306,   273,   131,    69,   310,   280,   200,  -151,   204,   282,
    -151,   259,   260,    44,    45,   213,   234,   323,   214,   215,
      46,   216,   270,    80,   170,   271,   239,   172,    10,     3,
    -152,  -152,   274,   284,   285,   296,   298,   302,   304,   327,
     329,   332,    79,   305,   171,   308,    79,   309,  -151,  -151,
      15,   334,   103,    83,   335,    80,   336,    16,    73,    17,
     317,    10,     3,   277,   136,   315,   136,    84,   319,   136,
       0,     0,   322,     0,     0,     0,    73,     0,     0,     0,
       0,     0,    79,     0,    79,     0,     0,     0,     0,    79,
       0,     0,     0,     0,     0,     0,   338,   136,   341,   136,
       0,     0,     0,     0,     0,    79,    79,    79,    79,    79,
      79,     0,   136,   136,     0,    80,     0,    73,     0,    80,
       0,     0,     0,     0,    79,     0,     0,     0,    79,     0,
       0,    74,     0,     0,     0,     0,     0,    79,    79,    79,
      79,     0,     0,     0,     0,     0,     0,    79,     0,    74,
      79,     0,     0,    79,    79,    80,     0,    80,     0,     0,
       0,    31,    80,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     0,     0,    43,     0,    80,    80,
      80,    80,    80,    80,    44,    45,     0,     0,    69,   279,
      74,    46,    69,     0,     0,     0,     0,    80,     0,     0,
       0,    80,     0,     0,    76,     0,     0,     0,     0,     0,
      80,    80,    80,    80,     0,     0,     0,     0,     0,     0,
      80,     0,    76,    80,     0,     0,    80,    80,    69,     0,
      69,     0,    10,     3,    31,    69,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,     0,     0,    43,
       0,    69,    69,    69,   171,    69,    69,    44,    45,     0,
       0,    73,   314,   173,    46,    73,     0,     0,     0,     0,
      69,     0,     0,     0,    69,     0,     0,    70,     0,     0,
       0,     0,     0,    69,    69,    69,    69,     0,     0,     0,
       0,     0,     0,    69,     0,    70,    69,     0,     0,    69,
      69,    73,     0,    73,     0,    10,     3,    31,    73,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
       0,     0,    43,     0,    73,    73,    73,    73,    73,    73,
      44,    45,     0,     0,    74,     0,   316,    46,    74,     0,
       0,     0,     0,    73,     0,     0,     0,    73,     0,     0,
       0,     0,     0,     0,     0,     0,    73,    73,    73,    73,
       0,     0,     0,     0,     0,     0,    73,     0,     0,    73,
       0,     0,    73,    73,    74,     0,    74,     0,    10,     3,
      31,    74,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,     0,     0,    43,     0,    74,    74,    74,
      74,    74,    74,    44,    45,     0,     0,    76,     0,   318,
      46,    76,     0,     0,     0,     0,    74,     0,     0,     0,
      74,     0,     0,     0,     0,     0,     0,     0,     0,    74,
      74,    74,    74,     0,     0,     0,     0,     0,     0,    74,
       0,     0,    74,     0,     0,    74,    74,    76,     0,    76,
       0,    10,     3,    31,    76,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     0,     0,    43,     0,
      76,    76,    76,   173,    76,    76,    44,    45,     0,     0,
      70,     0,   320,    46,    70,     0,     0,     0,     0,    76,
       0,     0,     0,    76,     0,     0,     0,     0,     0,     0,
       0,     0,    76,    76,    76,    76,     0,     0,   104,     0,
       0,     0,    76,     0,     0,    76,   149,   150,    76,    76,
      70,     0,    70,     0,    10,     3,     0,    70,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,     0,
       0,     0,     0,    70,    70,    70,     0,    70,    70,   165,
     166,     0,     0,     0,     0,     0,     0,   174,   175,     0,
       0,     0,    70,     0,   176,     0,    70,   179,   180,     0,
       0,     0,     0,     0,     0,    70,    70,    70,    70,     0,
       0,     0,     0,     0,     0,    70,     0,     0,    70,     0,
       0,    70,    70,     0,     0,     0,     0,     0,     0,   203,
       0,     0,   205,     0,     0,     0,     0,     0,     0,   209,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,     0,
       0,     0,     0,     0,     0,     0,   205,     0,     0,     0,
       0,   264,   265,   266,   267,     0,    31,     0,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,     0,
       0,    43,   276,   278,     0,     0,   281,     0,     0,    44,
      45,     0,     0,     0,   337,    31,    46,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,     0,     0,
      43,     0,     0,     0,     0,     0,     0,   292,    44,    45,
       0,     0,     0,     0,   339,    46,     0,     0,     0,     0,
       0,   303,     0,     0,     0,     0,   307,    10,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,   321,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     0,     0,    43,     0,     0,    10,     3,     0,     0,
       0,    44,    45,     0,     0,     0,   340,    31,    46,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
       0,     0,    43,     0,     0,     0,     0,     0,     0,     0,
      44,    45,     0,     0,     0,     0,   342,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    10,
       3,    31,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     0,     0,    43,     0,     0,     0,
       0,     0,     0,     0,    44,    45,     0,     0,    10,     3,
     345,    46,    31,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,     0,     0,    43,     0,     0,
       0,     0,     0,     0,     0,    44,    45,     0,     0,     0,
       0,   346,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    10,     3,     0,    31,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,     0,     0,
      43,     0,     0,     0,     0,     0,     0,     0,    44,    45,
      41,     0,     0,    10,     3,    46,     0,     0,    92,    93,
      94,     0,    44,    45,    95,    96,     0,     0,    41,    46,
       0,     0,     0,    97,     0,    98,    92,    93,    94,     0,
      44,    45,    95,    96,     0,     0,     0,    46,     0,     0,
       0,    97,     0,     0,     0,     0,    10,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    99,   100,
      10,     3,    21,   101,   102,   103,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    99,   100,    10,     3,
      21,   101,   102,   103,    83,    41,   235,     0,     0,     0,
       0,     0,     0,    92,    93,    94,     0,    44,    45,    95,
      96,     0,     0,     0,   208,     0,   182,     0,    97,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     193,   194,   195,   196,   197,   198,   199,   145,   146,     0,
     147,   148,     0,    99,   100,    10,     3,    21,   101,   102,
     103,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   149,   150,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   237,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,   182,     0,     0,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,   196,   197,   198,   199,   286,     0,
       0,     0,     0,   287,     0,     0,     0,     0,     0,   182,
       0,     0,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,   196,   197,   198,   199,
     290,     0,     0,     0,     0,   291,     0,     0,     0,     0,
       0,   182,     0,     0,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,     0,     0,     0,     0,     0,     0,
       0,   232,     0,     0,     0,   193,   194,   195,   196,   197,
     198,   199,   182,     0,     0,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,     0,     0,     0,     0,     0,
       0,     0,   233,     0,     0,     0,   193,   194,   195,   196,
     197,   198,   199,   182,     0,     0,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,     0,     0,     0,     0,
       0,     0,     0,   236,     0,     0,     0,   193,   194,   195,
     196,   197,   198,   199,   182,     0,     0,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,     0,     0,     0,
       0,     0,     0,     0,   261,     0,     0,     0,   193,   194,
     195,   196,   197,   198,   199,   182,     0,     0,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,     0,     0,
       0,     0,     0,     0,     0,   289,     0,     0,     0,   193,
     194,   195,   196,   197,   198,   199,   182,     0,     0,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,   299,     0,     0,     0,
     193,   194,   195,   196,   197,   198,   199,   182,     0,     0,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
       0,     0,     0,     0,     0,     0,     0,   325,     0,     0,
       0,   193,   194,   195,   196,   197,   198,   199,   182,     0,
       0,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,   331,     0,
       0,     0,   193,   194,   195,   196,   197,   198,   199,   182,
       0,     0,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,   196,   197,   198,   199,
     262,     0,     0,     0,     0,     0,     0,   182,     0,     0,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,   196,   197,   198,   199,   263,     0,
       0,     0,     0,     0,     0,   182,     0,     0,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,   196,   197,   198,   199,   288,     0,     0,     0,
       0,     0,   182,     0,     0,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   193,   194,   195,   196,
     197,   198,   199,   301,     0,     0,     0,     0,     0,   182,
       0,     0,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,   196,   197,   198,   199,
     283,     0,     0,   182,     0,     0,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   193,   194,   195,
     196,   197,   198,   199,   181,     0,   182,     0,     0,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     193,   194,   195,   196,   197,   198,   199,   182,     0,     0,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,   196,   197,   198,   199
  };

  const short
  parser::yycheck_[] =
  {
       0,     1,    42,    28,    88,     5,    47,    88,    41,    32,
      41,     3,     4,   272,    33,   274,    33,    40,    18,    38,
     279,    38,    79,    26,    27,    13,    83,    27,     6,    29,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    41,    75,    21,    75,    33,    32,    47,     0,    33,
      32,    29,    30,    78,    38,   314,    96,    35,    36,   318,
      78,     6,    36,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     1,    75,    21,    33,   337,    82,
      83,   340,    38,    42,    29,    30,    78,    33,    88,    34,
      79,    36,    38,    36,    77,    78,    39,    97,    42,    77,
      78,    33,    29,    77,    78,    33,    17,   140,    17,   140,
      38,    33,    42,    43,    41,    34,    38,    42,    32,    32,
      47,    32,    42,    41,    17,    36,    32,    36,    39,    40,
      39,    32,    77,    78,    77,    78,    32,    42,    42,   172,
     140,   172,   142,    36,    36,    42,    39,     6,    75,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      17,    88,    21,   163,   164,    42,    77,    78,    77,    78,
      29,    30,   172,   270,   271,    29,    35,    36,    17,    36,
      42,    41,    39,    41,    77,    78,    26,    27,    40,    40,
     287,   232,    32,    47,   291,   236,    43,    36,    42,   239,
      39,   201,   202,    29,    30,    32,    42,   304,    32,    32,
      36,    32,    32,   140,   298,    32,    38,   298,    77,    78,
      77,    78,    34,    42,    37,     7,    42,    38,    32,     7,
      33,    33,   232,    42,    88,    42,   236,    42,    77,    78,
       5,    42,    82,    83,    42,   172,    42,     5,    29,     5,
     298,    77,    78,   234,   295,   296,   297,    33,   299,   300,
      -1,    -1,   302,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,   272,    -1,   274,    -1,    -1,    -1,    -1,   279,
      -1,    -1,    -1,    -1,    -1,    -1,   327,   328,   329,   330,
      -1,    -1,    -1,    -1,    -1,   295,   296,   297,   298,   299,
     300,    -1,   343,   344,    -1,   232,    -1,    88,    -1,   236,
      -1,    -1,    -1,    -1,   314,    -1,    -1,    -1,   318,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,   327,   328,   329,
     330,    -1,    -1,    -1,    -1,    -1,    -1,   337,    -1,    47,
     340,    -1,    -1,   343,   344,   272,    -1,   274,    -1,    -1,
      -1,     6,   279,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,   295,   296,
     297,   298,   299,   300,    29,    30,    -1,    -1,   232,    34,
      88,    36,   236,    -1,    -1,    -1,    -1,   314,    -1,    -1,
      -1,   318,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,
     327,   328,   329,   330,    -1,    -1,    -1,    -1,    -1,    -1,
     337,    -1,    47,   340,    -1,    -1,   343,   344,   272,    -1,
     274,    -1,    77,    78,     6,   279,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      -1,   295,   296,   297,   298,   299,   300,    29,    30,    -1,
      -1,   232,    34,    88,    36,   236,    -1,    -1,    -1,    -1,
     314,    -1,    -1,    -1,   318,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,   327,   328,   329,   330,    -1,    -1,    -1,
      -1,    -1,    -1,   337,    -1,    47,   340,    -1,    -1,   343,
     344,   272,    -1,   274,    -1,    77,    78,     6,   279,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    -1,   295,   296,   297,   298,   299,   300,
      29,    30,    -1,    -1,   232,    -1,    35,    36,   236,    -1,
      -1,    -1,    -1,   314,    -1,    -1,    -1,   318,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   327,   328,   329,   330,
      -1,    -1,    -1,    -1,    -1,    -1,   337,    -1,    -1,   340,
      -1,    -1,   343,   344,   272,    -1,   274,    -1,    77,    78,
       6,   279,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    21,    -1,   295,   296,   297,
     298,   299,   300,    29,    30,    -1,    -1,   232,    -1,    35,
      36,   236,    -1,    -1,    -1,    -1,   314,    -1,    -1,    -1,
     318,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   327,
     328,   329,   330,    -1,    -1,    -1,    -1,    -1,    -1,   337,
      -1,    -1,   340,    -1,    -1,   343,   344,   272,    -1,   274,
      -1,    77,    78,     6,   279,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    -1,    -1,    21,    -1,
     295,   296,   297,   298,   299,   300,    29,    30,    -1,    -1,
     232,    -1,    35,    36,   236,    -1,    -1,    -1,    -1,   314,
      -1,    -1,    -1,   318,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   327,   328,   329,   330,    -1,    -1,    40,    -1,
      -1,    -1,   337,    -1,    -1,   340,    45,    46,   343,   344,
     272,    -1,   274,    -1,    77,    78,    -1,   279,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,   295,   296,   297,    -1,   299,   300,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    -1,   314,    -1,    96,    -1,   318,    99,   100,    -1,
      -1,    -1,    -1,    -1,    -1,   327,   328,   329,   330,    -1,
      -1,    -1,    -1,    -1,    -1,   337,    -1,    -1,   340,    -1,
      -1,   343,   344,    -1,    -1,    -1,    -1,    -1,    -1,   131,
      -1,    -1,   134,    -1,    -1,    -1,    -1,    -1,    -1,   141,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,    -1,    -1,    -1,
      -1,   213,   214,   215,   216,    -1,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,   234,   235,    -1,    -1,   238,    -1,    -1,    29,
      30,    -1,    -1,    -1,    34,     6,    36,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,   269,    29,    30,
      -1,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    -1,
      -1,   283,    -1,    -1,    -1,    -1,   288,    77,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,   301,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    77,    78,    -1,    -1,
      -1,    29,    30,    -1,    -1,    -1,    34,     6,    36,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    30,    -1,    -1,    -1,    -1,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      78,     6,    -1,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    77,    78,
      35,    36,     6,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    -1,     6,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,
      17,    -1,    -1,    77,    78,    36,    -1,    -1,    25,    26,
      27,    -1,    29,    30,    31,    32,    -1,    -1,    17,    36,
      -1,    -1,    -1,    40,    -1,    42,    25,    26,    27,    -1,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    77,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    17,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    -1,    29,    30,    31,
      32,    -1,    -1,    -1,    36,    -1,    44,    -1,    40,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    19,    20,    -1,
      22,    23,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    33,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    33,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      33,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    44,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    44,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    44,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    44,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    44,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    44,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    44,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    44,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    38,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    38,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      41,    -1,    -1,    44,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    42,    -1,    44,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    44,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,    78,    86,    87,    88,    89,    90,   145,
      77,   145,   146,    32,     0,    88,    89,    90,    32,    42,
      42,    79,   144,    91,   145,    33,    33,    38,    42,    34,
     145,     6,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    21,    29,    30,    36,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   116,   121,
     122,   123,   124,   126,   127,   129,   130,   134,   135,   145,
     146,    32,    32,    83,   141,   144,    41,    42,    32,    32,
      32,    42,    25,    26,    27,    31,    32,    40,    42,    75,
      76,    80,    81,    82,   115,   117,   118,   119,   120,   121,
     122,   126,   127,   128,   130,   132,   133,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   123,   124,
     145,    32,   139,    42,    36,    35,    93,    42,    42,    42,
      17,    36,    39,   123,   124,    19,    20,    22,    23,    45,
      46,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    32,    40,    40,   115,   115,    41,    41,   113,
     116,   121,   129,   130,   115,   115,   115,   139,   145,   115,
     115,    42,    44,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    68,    69,    70,    71,    72,    73,    74,
      43,    40,    40,   115,    42,   115,   123,   124,    36,   115,
      28,   131,   145,    32,    32,    32,    32,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   125,
     145,   145,    33,    33,    42,    24,    33,    33,    38,    38,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   145,
     145,    33,    37,    37,   115,   115,   115,   115,    33,    38,
      32,    32,    34,    93,    34,   114,   115,   117,   115,    34,
      93,   115,   139,    41,    42,    37,    33,    38,    38,    33,
      33,    38,   115,   125,   125,    92,     7,    92,    42,    33,
      92,    38,    38,   115,    32,    42,   125,   115,    42,    42,
     125,    33,    33,    35,    34,    93,    35,   113,    35,    93,
      35,   115,   139,   125,    33,    33,    33,     7,    92,    33,
      92,    33,    33,    33,    42,    42,    42,    34,    93,    35,
      34,    93,    35,    92,    92,    35,    35
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    85,    86,    86,    87,    87,    87,    87,    87,    87,
      88,    88,    89,    90,    91,    91,    91,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    94,
      94,    95,    96,    97,    97,    98,    98,    99,    99,   100,
     101,   102,   102,   103,   103,   103,   103,   104,   104,   105,
     105,   106,   106,   107,   108,   108,   109,   110,   111,   112,
     112,   113,   113,   114,   114,   115,   115,   115,   115,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   121,   121,
     121,   121,   122,   122,   122,   122,   123,   123,   123,   124,
     125,   125,   125,   126,   126,   127,   128,   128,   128,   129,
     129,   130,   130,   130,   130,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   139,   139,   139,   140,   141,
     142,   143,   144,   145,   146
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     5,     7,     3,     1,     0,     2,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     6,     8,     6,     5,     3,     8,     6,     8,
       2,     7,     5,    11,     9,     9,     7,     7,     5,    11,
       9,     9,     7,     7,     3,     3,     2,     2,     2,     3,
       2,     1,     0,     1,     0,     1,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       7,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       2,     2,     2,     2,     3,     3,     4,     6,     6,     8,
       3,     1,     0,     3,     3,     4,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     7,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    90,    90,    93,    97,    99,   101,   103,   105,   107,
     112,   114,   119,   124,   129,   131,   134,   138,   140,   143,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   170,
     172,   177,   182,   187,   189,   194,   196,   201,   203,   208,
     213,   218,   220,   225,   227,   229,   231,   236,   238,   243,
     245,   250,   252,   257,   262,   264,   269,   274,   278,   283,
     285,   290,   291,   295,   296,   301,   302,   303,   304,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   324,   325,   326,   327,   328,   329,   330,   331,
     335,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   372,   373,
     374,   375,   379,   380,   381,   382,   387,   388,   389,   394,
     399,   400,   401,   406,   407,   412,   417,   418,   419,   424,
     425,   430,   431,   432,   433,   434,   438,   443,   448,   453,
     458,   463,   468,   473,   478,   479,   480,   481,   485,   489,
     493,   497,   501,   505,   509
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
#line 3101 "./IW6/compiler_parser.cpp"

#line 512 "iw6.parser.ypp"



void yy::parser::error(const std::string& msg)
{
    std::cout << "An error occured: " << msg << std::endl;
}
