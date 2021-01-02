// A Bison parser, made by GNU Bison 3.7.3.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file ./H2/compiler_parser.hpp
 ** Define the H2::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_H2_H2_COMPILER_PARSER_HPP_INCLUDED
# define YY_H2_H2_COMPILER_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 30 "H2.parser.ypp"

	#include <utils.hpp>
	typedef void *yyscan_t;
	#define YY_DECL H2::parser::symbol_type H2lex(yyscan_t yyscanner, std::uint32_t *location)

#line 55 "./H2/compiler_parser.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif

#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef H2DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define H2DEBUG 1
#  else
#   define H2DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define H2DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined H2DEBUG */

#line 14 "H2.parser.ypp"
namespace H2 {
#line 198 "./H2/compiler_parser.hpp"




  /// A Bison parser.
  class parser
  {
  public:
#ifndef H2STYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // animref
      char dummy1[sizeof (gsc::animref_ptr)];

      // block
      char dummy2[sizeof (gsc::block_ptr)];

      // expr_arguments
      char dummy3[sizeof (gsc::expr_arguments_ptr)];

      // expr_assign
      char dummy4[sizeof (gsc::expr_assign_ptr)];

      // expr_call
      // expr_call_thread
      char dummy5[sizeof (gsc::expr_call_ptr)];

      // expr_call_function
      // expr_call_pointer
      char dummy6[sizeof (gsc::expr_call_type_ptr)];

      // for_assign
      // for_cond
      // expr
      // expr_cmp
      // expr_ternary
      // expr_binary
      // expr_primitive
      char dummy7[sizeof (gsc::expr_ptr)];

      // filepath
      char dummy8[sizeof (gsc::filepath_ptr)];

      // data_float
      char dummy9[sizeof (gsc::float_ptr)];

      // identifier
      char dummy10[sizeof (gsc::identifier_ptr)];

      // include
      char dummy11[sizeof (gsc::include_ptr)];

      // data_integer
      char dummy12[sizeof (gsc::integer_ptr)];

      // data_localized_string
      char dummy13[sizeof (gsc::localized_string_ptr)];

      // expr_function_ref
      // expr_array
      // expr_field
      // expr_size
      // expr_vector
      // expr_add_array
      // object
      // vector
      // num
      // false
      // true
      // empty_array
      // undefined
      // size
      // game
      // self
      // anim
      // level
      char dummy14[sizeof (gsc::node_ptr)];

      // parameters
      char dummy15[sizeof (gsc::parameters_ptr)];

      // script
      char dummy16[sizeof (gsc::script_ptr)];

      // stmt_assign
      char dummy17[sizeof (gsc::stmt_assign_ptr)];

      // stmt_break
      char dummy18[sizeof (gsc::stmt_break_ptr)];

      // stmt_call
      char dummy19[sizeof (gsc::stmt_call_ptr)];

      // stmt_case
      char dummy20[sizeof (gsc::stmt_case_ptr)];

      // stmt_continue
      char dummy21[sizeof (gsc::stmt_continue_ptr)];

      // stmt_default
      char dummy22[sizeof (gsc::stmt_default_ptr)];

      // stmt_endon
      char dummy23[sizeof (gsc::stmt_endon_ptr)];

      // stmt_for
      char dummy24[sizeof (gsc::stmt_for_ptr)];

      // stmt_foreach
      char dummy25[sizeof (gsc::stmt_foreach_ptr)];

      // stmt_if
      char dummy26[sizeof (gsc::stmt_if_ptr)];

      // stmt_ifelse
      char dummy27[sizeof (gsc::stmt_ifelse_ptr)];

      // stmt_notify
      char dummy28[sizeof (gsc::stmt_notify_ptr)];

      // stmt
      char dummy29[sizeof (gsc::stmt_ptr)];

      // stmt_return
      char dummy30[sizeof (gsc::stmt_return_ptr)];

      // stmt_switch
      char dummy31[sizeof (gsc::stmt_switch_ptr)];

      // stmt_wait
      char dummy32[sizeof (gsc::stmt_wait_ptr)];

      // stmt_waitframe
      char dummy33[sizeof (gsc::stmt_waitframe_ptr)];

      // stmt_waittill
      char dummy34[sizeof (gsc::stmt_waittill_ptr)];

      // stmt_waittillframeend
      char dummy35[sizeof (gsc::stmt_waittillframeend_ptr)];

      // stmt_waittillmatch
      char dummy36[sizeof (gsc::stmt_waittillmatch_ptr)];

      // stmt_while
      char dummy37[sizeof (gsc::stmt_while_ptr)];

      // data_string
      char dummy38[sizeof (gsc::string_ptr)];

      // thread
      char dummy39[sizeof (gsc::thread_ptr)];

      // using_animtree
      // animtree
      char dummy40[sizeof (gsc::using_animtree_ptr)];

      // FILEPATH
      // IDENTIFIER
      // ANIMREF
      // STRING
      // STRING_LOC
      // FLOAT
      // INTEGER
      char dummy41[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef H2STYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        H2EMPTY = -2,
    H2EOF = 0,                     // "end of file"
    H2error = 1,                   // error
    H2UNDEF = 2,                   // "invalid token"
    INCLUDE = 3,                   // INCLUDE
    USING_ANIMTREE = 4,            // USING_ANIMTREE
    ANIMTREE = 5,                  // ANIMTREE
    IF = 6,                        // IF
    ELSE = 7,                      // ELSE
    SWITCH = 8,                    // SWITCH
    CASE = 9,                      // CASE
    DEFAULT = 10,                  // DEFAULT
    BREAK = 11,                    // BREAK
    FOR = 12,                      // FOR
    FOREACH = 13,                  // FOREACH
    WHILE = 14,                    // WHILE
    CONTINUE = 15,                 // CONTINUE
    RETURN = 16,                   // RETURN
    THREAD = 17,                   // THREAD
    CALL = 18,                     // CALL
    WAIT = 19,                     // WAIT
    WAITTILL = 20,                 // WAITTILL
    WAITTILLMATCH = 21,            // WAITTILLMATCH
    WAITTILLFRAMEEND = 22,         // WAITTILLFRAMEEND
    WAITFRAME = 23,                // WAITFRAME
    ENDON = 24,                    // ENDON
    NOTIFY = 25,                   // NOTIFY
    IN = 26,                       // IN
    UNDEFINED = 27,                // UNDEFINED
    TRUE = 28,                     // TRUE
    FALSE = 29,                    // FALSE
    SIZE = 30,                     // SIZE
    GAME = 31,                     // GAME
    LEVEL = 32,                    // LEVEL
    ANIM = 33,                     // ANIM
    SELF = 34,                     // SELF
    EMPTY_ARRAY = 35,              // EMPTY_ARRAY
    LPAREN = 36,                   // LPAREN
    RPAREN = 37,                   // RPAREN
    LBRACE = 38,                   // LBRACE
    RBRACE = 39,                   // RBRACE
    LBRACKET = 40,                 // LBRACKET
    RBRACKET = 41,                 // RBRACKET
    COMMA = 42,                    // COMMA
    DOT = 43,                      // DOT
    DOUBLECOLON = 44,              // DOUBLECOLON
    COLON = 45,                    // COLON
    SEMICOLON = 46,                // SEMICOLON
    QMARK = 47,                    // QMARK
    MOD = 48,                      // MOD
    INCREMENT = 49,                // INCREMENT
    DECREMENT = 50,                // DECREMENT
    LSHIFT = 51,                   // LSHIFT
    RSHIFT = 52,                   // RSHIFT
    OR = 53,                       // OR
    AND = 54,                      // AND
    EQUALITY = 55,                 // EQUALITY
    INEQUALITY = 56,               // INEQUALITY
    LESS_EQUAL = 57,               // LESS_EQUAL
    GREATER_EQUAL = 58,            // GREATER_EQUAL
    LESS = 59,                     // LESS
    GREATER = 60,                  // GREATER
    ASSIGN = 61,                   // ASSIGN
    ASSIGN_ADD = 62,               // ASSIGN_ADD
    ASSIGN_SUB = 63,               // ASSIGN_SUB
    ASSIGN_MULT = 64,              // ASSIGN_MULT
    ASSIGN_DIV = 65,               // ASSIGN_DIV
    ASSIGN_MOD = 66,               // ASSIGN_MOD
    ASSIGN_BITWISE_OR = 67,        // ASSIGN_BITWISE_OR
    ASSIGN_BITWISE_AND = 68,       // ASSIGN_BITWISE_AND
    ASSIGN_BITWISE_EXOR = 69,      // ASSIGN_BITWISE_EXOR
    ASSIGN_LSHIFT = 70,            // ASSIGN_LSHIFT
    ASSIGN_RSHIFT = 71,            // ASSIGN_RSHIFT
    BITWISE_OR = 72,               // BITWISE_OR
    BITWISE_AND = 73,              // BITWISE_AND
    BITWISE_EXOR = 74,             // BITWISE_EXOR
    ADD = 75,                      // ADD
    SUB = 76,                      // SUB
    MULT = 77,                     // MULT
    DIV = 78,                      // DIV
    NOT = 79,                      // NOT
    COMPLEMENT = 80,               // COMPLEMENT
    FILEPATH = 81,                 // FILEPATH
    IDENTIFIER = 82,               // IDENTIFIER
    ANIMREF = 83,                  // ANIMREF
    STRING = 84,                   // STRING
    STRING_LOC = 85,               // STRING_LOC
    FLOAT = 86,                    // FLOAT
    INTEGER = 87,                  // INTEGER
    IFX = 88                       // IFX
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 89, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_INCLUDE = 3,                           // INCLUDE
        S_USING_ANIMTREE = 4,                    // USING_ANIMTREE
        S_ANIMTREE = 5,                          // ANIMTREE
        S_IF = 6,                                // IF
        S_ELSE = 7,                              // ELSE
        S_SWITCH = 8,                            // SWITCH
        S_CASE = 9,                              // CASE
        S_DEFAULT = 10,                          // DEFAULT
        S_BREAK = 11,                            // BREAK
        S_FOR = 12,                              // FOR
        S_FOREACH = 13,                          // FOREACH
        S_WHILE = 14,                            // WHILE
        S_CONTINUE = 15,                         // CONTINUE
        S_RETURN = 16,                           // RETURN
        S_THREAD = 17,                           // THREAD
        S_CALL = 18,                             // CALL
        S_WAIT = 19,                             // WAIT
        S_WAITTILL = 20,                         // WAITTILL
        S_WAITTILLMATCH = 21,                    // WAITTILLMATCH
        S_WAITTILLFRAMEEND = 22,                 // WAITTILLFRAMEEND
        S_WAITFRAME = 23,                        // WAITFRAME
        S_ENDON = 24,                            // ENDON
        S_NOTIFY = 25,                           // NOTIFY
        S_IN = 26,                               // IN
        S_UNDEFINED = 27,                        // UNDEFINED
        S_TRUE = 28,                             // TRUE
        S_FALSE = 29,                            // FALSE
        S_SIZE = 30,                             // SIZE
        S_GAME = 31,                             // GAME
        S_LEVEL = 32,                            // LEVEL
        S_ANIM = 33,                             // ANIM
        S_SELF = 34,                             // SELF
        S_EMPTY_ARRAY = 35,                      // EMPTY_ARRAY
        S_LPAREN = 36,                           // LPAREN
        S_RPAREN = 37,                           // RPAREN
        S_LBRACE = 38,                           // LBRACE
        S_RBRACE = 39,                           // RBRACE
        S_LBRACKET = 40,                         // LBRACKET
        S_RBRACKET = 41,                         // RBRACKET
        S_COMMA = 42,                            // COMMA
        S_DOT = 43,                              // DOT
        S_DOUBLECOLON = 44,                      // DOUBLECOLON
        S_COLON = 45,                            // COLON
        S_SEMICOLON = 46,                        // SEMICOLON
        S_QMARK = 47,                            // QMARK
        S_MOD = 48,                              // MOD
        S_INCREMENT = 49,                        // INCREMENT
        S_DECREMENT = 50,                        // DECREMENT
        S_LSHIFT = 51,                           // LSHIFT
        S_RSHIFT = 52,                           // RSHIFT
        S_OR = 53,                               // OR
        S_AND = 54,                              // AND
        S_EQUALITY = 55,                         // EQUALITY
        S_INEQUALITY = 56,                       // INEQUALITY
        S_LESS_EQUAL = 57,                       // LESS_EQUAL
        S_GREATER_EQUAL = 58,                    // GREATER_EQUAL
        S_LESS = 59,                             // LESS
        S_GREATER = 60,                          // GREATER
        S_ASSIGN = 61,                           // ASSIGN
        S_ASSIGN_ADD = 62,                       // ASSIGN_ADD
        S_ASSIGN_SUB = 63,                       // ASSIGN_SUB
        S_ASSIGN_MULT = 64,                      // ASSIGN_MULT
        S_ASSIGN_DIV = 65,                       // ASSIGN_DIV
        S_ASSIGN_MOD = 66,                       // ASSIGN_MOD
        S_ASSIGN_BITWISE_OR = 67,                // ASSIGN_BITWISE_OR
        S_ASSIGN_BITWISE_AND = 68,               // ASSIGN_BITWISE_AND
        S_ASSIGN_BITWISE_EXOR = 69,              // ASSIGN_BITWISE_EXOR
        S_ASSIGN_LSHIFT = 70,                    // ASSIGN_LSHIFT
        S_ASSIGN_RSHIFT = 71,                    // ASSIGN_RSHIFT
        S_BITWISE_OR = 72,                       // BITWISE_OR
        S_BITWISE_AND = 73,                      // BITWISE_AND
        S_BITWISE_EXOR = 74,                     // BITWISE_EXOR
        S_ADD = 75,                              // ADD
        S_SUB = 76,                              // SUB
        S_MULT = 77,                             // MULT
        S_DIV = 78,                              // DIV
        S_NOT = 79,                              // NOT
        S_COMPLEMENT = 80,                       // COMPLEMENT
        S_FILEPATH = 81,                         // FILEPATH
        S_IDENTIFIER = 82,                       // IDENTIFIER
        S_ANIMREF = 83,                          // ANIMREF
        S_STRING = 84,                           // STRING
        S_STRING_LOC = 85,                       // STRING_LOC
        S_FLOAT = 86,                            // FLOAT
        S_INTEGER = 87,                          // INTEGER
        S_IFX = 88,                              // IFX
        S_YYACCEPT = 89,                         // $accept
        S_root = 90,                             // root
        S_script = 91,                           // script
        S_include = 92,                          // include
        S_using_animtree = 93,                   // using_animtree
        S_animtree = 94,                         // animtree
        S_thread = 95,                           // thread
        S_parameters = 96,                       // parameters
        S_block = 97,                            // block
        S_stmt = 98,                             // stmt
        S_stmt_call = 99,                        // stmt_call
        S_stmt_assign = 100,                     // stmt_assign
        S_stmt_endon = 101,                      // stmt_endon
        S_stmt_notify = 102,                     // stmt_notify
        S_stmt_wait = 103,                       // stmt_wait
        S_stmt_waittill = 104,                   // stmt_waittill
        S_stmt_waittillmatch = 105,              // stmt_waittillmatch
        S_stmt_waittillframeend = 106,           // stmt_waittillframeend
        S_stmt_waitframe = 107,                  // stmt_waitframe
        S_stmt_if = 108,                         // stmt_if
        S_stmt_ifelse = 109,                     // stmt_ifelse
        S_stmt_while = 110,                      // stmt_while
        S_stmt_for = 111,                        // stmt_for
        S_stmt_foreach = 112,                    // stmt_foreach
        S_stmt_switch = 113,                     // stmt_switch
        S_stmt_case = 114,                       // stmt_case
        S_stmt_default = 115,                    // stmt_default
        S_stmt_break = 116,                      // stmt_break
        S_stmt_continue = 117,                   // stmt_continue
        S_stmt_return = 118,                     // stmt_return
        S_for_assign = 119,                      // for_assign
        S_for_cond = 120,                        // for_cond
        S_expr = 121,                            // expr
        S_expr_assign = 122,                     // expr_assign
        S_expr_cmp = 123,                        // expr_cmp
        S_expr_ternary = 124,                    // expr_ternary
        S_expr_binary = 125,                     // expr_binary
        S_expr_primitive = 126,                  // expr_primitive
        S_expr_call = 127,                       // expr_call
        S_expr_call_thread = 128,                // expr_call_thread
        S_expr_call_function = 129,              // expr_call_function
        S_expr_call_pointer = 130,               // expr_call_pointer
        S_expr_arguments = 131,                  // expr_arguments
        S_expr_function_ref = 132,               // expr_function_ref
        S_expr_array = 133,                      // expr_array
        S_expr_field = 134,                      // expr_field
        S_expr_size = 135,                       // expr_size
        S_expr_vector = 136,                     // expr_vector
        S_expr_add_array = 137,                  // expr_add_array
        S_object = 138,                          // object
        S_vector = 139,                          // vector
        S_num = 140,                             // num
        S_false = 141,                           // false
        S_true = 142,                            // true
        S_data_float = 143,                      // data_float
        S_data_integer = 144,                    // data_integer
        S_data_localized_string = 145,           // data_localized_string
        S_data_string = 146,                     // data_string
        S_animref = 147,                         // animref
        S_identifier = 148,                      // identifier
        S_filepath = 149,                        // filepath
        S_empty_array = 150,                     // empty_array
        S_undefined = 151,                       // undefined
        S_size = 152,                            // size
        S_game = 153,                            // game
        S_self = 154,                            // self
        S_anim = 155,                            // anim
        S_level = 156                            // level
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_animref: // animref
        value.move< gsc::animref_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< gsc::block_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.move< gsc::expr_arguments_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< gsc::expr_assign_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.move< gsc::expr_call_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.move< gsc::expr_call_type_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.move< gsc::expr_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_filepath: // filepath
        value.move< gsc::filepath_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_data_float: // data_float
        value.move< gsc::float_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< gsc::identifier_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_include: // include
        value.move< gsc::include_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_data_integer: // data_integer
        value.move< gsc::integer_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.move< gsc::localized_string_ptr > (std::move (that.value));
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
        value.move< gsc::node_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
        value.move< gsc::parameters_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< gsc::script_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< gsc::stmt_assign_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< gsc::stmt_break_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< gsc::stmt_call_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< gsc::stmt_case_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< gsc::stmt_continue_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< gsc::stmt_default_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< gsc::stmt_endon_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< gsc::stmt_for_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< gsc::stmt_foreach_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< gsc::stmt_if_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< gsc::stmt_ifelse_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< gsc::stmt_notify_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< gsc::stmt_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< gsc::stmt_return_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< gsc::stmt_switch_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< gsc::stmt_wait_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< gsc::stmt_waitframe_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< gsc::stmt_waittill_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< gsc::stmt_waittillframeend_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< gsc::stmt_waittillmatch_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< gsc::stmt_while_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_data_string: // data_string
        value.move< gsc::string_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_thread: // thread
        value.move< gsc::thread_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.move< gsc::using_animtree_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_ANIMREF: // ANIMREF
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::animref_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::animref_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::block_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::block_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::expr_arguments_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::expr_arguments_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::expr_assign_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::expr_assign_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::expr_call_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::expr_call_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::expr_call_type_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::expr_call_type_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::expr_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::expr_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::filepath_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::filepath_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::float_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::float_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::identifier_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::identifier_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::include_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::include_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::integer_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::integer_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::localized_string_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::localized_string_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::node_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::node_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::parameters_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::parameters_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::script_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::script_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_assign_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_assign_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_break_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_break_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_call_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_call_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_case_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_case_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_continue_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_continue_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_default_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_default_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_endon_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_endon_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_for_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_for_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_foreach_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_foreach_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_if_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_if_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_ifelse_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_ifelse_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_notify_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_notify_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_return_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_return_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_switch_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_switch_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_wait_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_wait_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_waitframe_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_waitframe_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_waittill_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_waittill_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_waittillframeend_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_waittillframeend_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_waittillmatch_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_waittillmatch_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::stmt_while_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::stmt_while_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::string_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::string_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::thread_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::thread_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gsc::using_animtree_ptr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gsc::using_animtree_ptr& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_animref: // animref
        value.template destroy< gsc::animref_ptr > ();
        break;

      case symbol_kind::S_block: // block
        value.template destroy< gsc::block_ptr > ();
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.template destroy< gsc::expr_arguments_ptr > ();
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.template destroy< gsc::expr_assign_ptr > ();
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.template destroy< gsc::expr_call_ptr > ();
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.template destroy< gsc::expr_call_type_ptr > ();
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.template destroy< gsc::expr_ptr > ();
        break;

      case symbol_kind::S_filepath: // filepath
        value.template destroy< gsc::filepath_ptr > ();
        break;

      case symbol_kind::S_data_float: // data_float
        value.template destroy< gsc::float_ptr > ();
        break;

      case symbol_kind::S_identifier: // identifier
        value.template destroy< gsc::identifier_ptr > ();
        break;

      case symbol_kind::S_include: // include
        value.template destroy< gsc::include_ptr > ();
        break;

      case symbol_kind::S_data_integer: // data_integer
        value.template destroy< gsc::integer_ptr > ();
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.template destroy< gsc::localized_string_ptr > ();
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
        value.template destroy< gsc::node_ptr > ();
        break;

      case symbol_kind::S_parameters: // parameters
        value.template destroy< gsc::parameters_ptr > ();
        break;

      case symbol_kind::S_script: // script
        value.template destroy< gsc::script_ptr > ();
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.template destroy< gsc::stmt_assign_ptr > ();
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.template destroy< gsc::stmt_break_ptr > ();
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.template destroy< gsc::stmt_call_ptr > ();
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.template destroy< gsc::stmt_case_ptr > ();
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.template destroy< gsc::stmt_continue_ptr > ();
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.template destroy< gsc::stmt_default_ptr > ();
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.template destroy< gsc::stmt_endon_ptr > ();
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.template destroy< gsc::stmt_for_ptr > ();
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.template destroy< gsc::stmt_foreach_ptr > ();
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.template destroy< gsc::stmt_if_ptr > ();
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.template destroy< gsc::stmt_ifelse_ptr > ();
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.template destroy< gsc::stmt_notify_ptr > ();
        break;

      case symbol_kind::S_stmt: // stmt
        value.template destroy< gsc::stmt_ptr > ();
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.template destroy< gsc::stmt_return_ptr > ();
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.template destroy< gsc::stmt_switch_ptr > ();
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.template destroy< gsc::stmt_wait_ptr > ();
        break;

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.template destroy< gsc::stmt_waitframe_ptr > ();
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.template destroy< gsc::stmt_waittill_ptr > ();
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.template destroy< gsc::stmt_waittillframeend_ptr > ();
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.template destroy< gsc::stmt_waittillmatch_ptr > ();
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.template destroy< gsc::stmt_while_ptr > ();
        break;

      case symbol_kind::S_data_string: // data_string
        value.template destroy< gsc::string_ptr > ();
        break;

      case symbol_kind::S_thread: // thread
        value.template destroy< gsc::thread_ptr > ();
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.template destroy< gsc::using_animtree_ptr > ();
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_ANIMREF: // ANIMREF
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type(token_type (tok))
      {
        YY_ASSERT (tok == token::H2EOF || tok == token::H2error || tok == token::H2UNDEF || tok == token::INCLUDE || tok == token::USING_ANIMTREE || tok == token::ANIMTREE || tok == token::IF || tok == token::ELSE || tok == token::SWITCH || tok == token::CASE || tok == token::DEFAULT || tok == token::BREAK || tok == token::FOR || tok == token::FOREACH || tok == token::WHILE || tok == token::CONTINUE || tok == token::RETURN || tok == token::THREAD || tok == token::CALL || tok == token::WAIT || tok == token::WAITTILL || tok == token::WAITTILLMATCH || tok == token::WAITTILLFRAMEEND || tok == token::WAITFRAME || tok == token::ENDON || tok == token::NOTIFY || tok == token::IN || tok == token::UNDEFINED || tok == token::TRUE || tok == token::FALSE || tok == token::SIZE || tok == token::GAME || tok == token::LEVEL || tok == token::ANIM || tok == token::SELF || tok == token::EMPTY_ARRAY || tok == token::LPAREN || tok == token::RPAREN || tok == token::LBRACE || tok == token::RBRACE || tok == token::LBRACKET || tok == token::RBRACKET || tok == token::COMMA || tok == token::DOT || tok == token::DOUBLECOLON || tok == token::COLON || tok == token::SEMICOLON || tok == token::QMARK || tok == token::MOD || tok == token::INCREMENT || tok == token::DECREMENT || tok == token::LSHIFT || tok == token::RSHIFT || tok == token::OR || tok == token::AND || tok == token::EQUALITY || tok == token::INEQUALITY || tok == token::LESS_EQUAL || tok == token::GREATER_EQUAL || tok == token::LESS || tok == token::GREATER || tok == token::ASSIGN || tok == token::ASSIGN_ADD || tok == token::ASSIGN_SUB || tok == token::ASSIGN_MULT || tok == token::ASSIGN_DIV || tok == token::ASSIGN_MOD || tok == token::ASSIGN_BITWISE_OR || tok == token::ASSIGN_BITWISE_AND || tok == token::ASSIGN_BITWISE_EXOR || tok == token::ASSIGN_LSHIFT || tok == token::ASSIGN_RSHIFT || tok == token::BITWISE_OR || tok == token::BITWISE_AND || tok == token::BITWISE_EXOR || tok == token::ADD || tok == token::SUB || tok == token::MULT || tok == token::DIV || tok == token::NOT || tok == token::COMPLEMENT || tok == token::IFX);
      }
#else
      symbol_type (int tok)
        : super_type(token_type (tok))
      {
        YY_ASSERT (tok == token::H2EOF || tok == token::H2error || tok == token::H2UNDEF || tok == token::INCLUDE || tok == token::USING_ANIMTREE || tok == token::ANIMTREE || tok == token::IF || tok == token::ELSE || tok == token::SWITCH || tok == token::CASE || tok == token::DEFAULT || tok == token::BREAK || tok == token::FOR || tok == token::FOREACH || tok == token::WHILE || tok == token::CONTINUE || tok == token::RETURN || tok == token::THREAD || tok == token::CALL || tok == token::WAIT || tok == token::WAITTILL || tok == token::WAITTILLMATCH || tok == token::WAITTILLFRAMEEND || tok == token::WAITFRAME || tok == token::ENDON || tok == token::NOTIFY || tok == token::IN || tok == token::UNDEFINED || tok == token::TRUE || tok == token::FALSE || tok == token::SIZE || tok == token::GAME || tok == token::LEVEL || tok == token::ANIM || tok == token::SELF || tok == token::EMPTY_ARRAY || tok == token::LPAREN || tok == token::RPAREN || tok == token::LBRACE || tok == token::RBRACE || tok == token::LBRACKET || tok == token::RBRACKET || tok == token::COMMA || tok == token::DOT || tok == token::DOUBLECOLON || tok == token::COLON || tok == token::SEMICOLON || tok == token::QMARK || tok == token::MOD || tok == token::INCREMENT || tok == token::DECREMENT || tok == token::LSHIFT || tok == token::RSHIFT || tok == token::OR || tok == token::AND || tok == token::EQUALITY || tok == token::INEQUALITY || tok == token::LESS_EQUAL || tok == token::GREATER_EQUAL || tok == token::LESS || tok == token::GREATER || tok == token::ASSIGN || tok == token::ASSIGN_ADD || tok == token::ASSIGN_SUB || tok == token::ASSIGN_MULT || tok == token::ASSIGN_DIV || tok == token::ASSIGN_MOD || tok == token::ASSIGN_BITWISE_OR || tok == token::ASSIGN_BITWISE_AND || tok == token::ASSIGN_BITWISE_EXOR || tok == token::ASSIGN_LSHIFT || tok == token::ASSIGN_RSHIFT || tok == token::BITWISE_OR || tok == token::BITWISE_AND || tok == token::BITWISE_EXOR || tok == token::ADD || tok == token::SUB || tok == token::MULT || tok == token::DIV || tok == token::NOT || tok == token::COMPLEMENT || tok == token::IFX);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type(token_type (tok), std::move (v))
      {
        YY_ASSERT (tok == token::FILEPATH || tok == token::IDENTIFIER || tok == token::ANIMREF || tok == token::STRING || tok == token::STRING_LOC || tok == token::FLOAT || tok == token::INTEGER);
      }
#else
      symbol_type (int tok, const std::string& v)
        : super_type(token_type (tok), v)
      {
        YY_ASSERT (tok == token::FILEPATH || tok == token::IDENTIFIER || tok == token::ANIMREF || tok == token::STRING || tok == token::STRING_LOC || tok == token::FLOAT || tok == token::INTEGER);
      }
#endif
    };

    /// Build a parser object.
    parser (yyscan_t yyscanner_yyarg, std::uint32_t *location_yyarg, gsc::script_ptr& astout_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if H2DEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_H2EOF ()
      {
        return symbol_type (token::H2EOF);
      }
#else
      static
      symbol_type
      make_H2EOF ()
      {
        return symbol_type (token::H2EOF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_H2error ()
      {
        return symbol_type (token::H2error);
      }
#else
      static
      symbol_type
      make_H2error ()
      {
        return symbol_type (token::H2error);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_H2UNDEF ()
      {
        return symbol_type (token::H2UNDEF);
      }
#else
      static
      symbol_type
      make_H2UNDEF ()
      {
        return symbol_type (token::H2UNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INCLUDE ()
      {
        return symbol_type (token::INCLUDE);
      }
#else
      static
      symbol_type
      make_INCLUDE ()
      {
        return symbol_type (token::INCLUDE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USING_ANIMTREE ()
      {
        return symbol_type (token::USING_ANIMTREE);
      }
#else
      static
      symbol_type
      make_USING_ANIMTREE ()
      {
        return symbol_type (token::USING_ANIMTREE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ANIMTREE ()
      {
        return symbol_type (token::ANIMTREE);
      }
#else
      static
      symbol_type
      make_ANIMTREE ()
      {
        return symbol_type (token::ANIMTREE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF ()
      {
        return symbol_type (token::IF);
      }
#else
      static
      symbol_type
      make_IF ()
      {
        return symbol_type (token::IF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::ELSE);
      }
#else
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::ELSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SWITCH ()
      {
        return symbol_type (token::SWITCH);
      }
#else
      static
      symbol_type
      make_SWITCH ()
      {
        return symbol_type (token::SWITCH);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE ()
      {
        return symbol_type (token::CASE);
      }
#else
      static
      symbol_type
      make_CASE ()
      {
        return symbol_type (token::CASE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFAULT ()
      {
        return symbol_type (token::DEFAULT);
      }
#else
      static
      symbol_type
      make_DEFAULT ()
      {
        return symbol_type (token::DEFAULT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BREAK ()
      {
        return symbol_type (token::BREAK);
      }
#else
      static
      symbol_type
      make_BREAK ()
      {
        return symbol_type (token::BREAK);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR ()
      {
        return symbol_type (token::FOR);
      }
#else
      static
      symbol_type
      make_FOR ()
      {
        return symbol_type (token::FOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOREACH ()
      {
        return symbol_type (token::FOREACH);
      }
#else
      static
      symbol_type
      make_FOREACH ()
      {
        return symbol_type (token::FOREACH);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE ()
      {
        return symbol_type (token::WHILE);
      }
#else
      static
      symbol_type
      make_WHILE ()
      {
        return symbol_type (token::WHILE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTINUE ()
      {
        return symbol_type (token::CONTINUE);
      }
#else
      static
      symbol_type
      make_CONTINUE ()
      {
        return symbol_type (token::CONTINUE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN ()
      {
        return symbol_type (token::RETURN);
      }
#else
      static
      symbol_type
      make_RETURN ()
      {
        return symbol_type (token::RETURN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THREAD ()
      {
        return symbol_type (token::THREAD);
      }
#else
      static
      symbol_type
      make_THREAD ()
      {
        return symbol_type (token::THREAD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CALL ()
      {
        return symbol_type (token::CALL);
      }
#else
      static
      symbol_type
      make_CALL ()
      {
        return symbol_type (token::CALL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WAIT ()
      {
        return symbol_type (token::WAIT);
      }
#else
      static
      symbol_type
      make_WAIT ()
      {
        return symbol_type (token::WAIT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WAITTILL ()
      {
        return symbol_type (token::WAITTILL);
      }
#else
      static
      symbol_type
      make_WAITTILL ()
      {
        return symbol_type (token::WAITTILL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WAITTILLMATCH ()
      {
        return symbol_type (token::WAITTILLMATCH);
      }
#else
      static
      symbol_type
      make_WAITTILLMATCH ()
      {
        return symbol_type (token::WAITTILLMATCH);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WAITTILLFRAMEEND ()
      {
        return symbol_type (token::WAITTILLFRAMEEND);
      }
#else
      static
      symbol_type
      make_WAITTILLFRAMEEND ()
      {
        return symbol_type (token::WAITTILLFRAMEEND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WAITFRAME ()
      {
        return symbol_type (token::WAITFRAME);
      }
#else
      static
      symbol_type
      make_WAITFRAME ()
      {
        return symbol_type (token::WAITFRAME);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENDON ()
      {
        return symbol_type (token::ENDON);
      }
#else
      static
      symbol_type
      make_ENDON ()
      {
        return symbol_type (token::ENDON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOTIFY ()
      {
        return symbol_type (token::NOTIFY);
      }
#else
      static
      symbol_type
      make_NOTIFY ()
      {
        return symbol_type (token::NOTIFY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IN ()
      {
        return symbol_type (token::IN);
      }
#else
      static
      symbol_type
      make_IN ()
      {
        return symbol_type (token::IN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNDEFINED ()
      {
        return symbol_type (token::UNDEFINED);
      }
#else
      static
      symbol_type
      make_UNDEFINED ()
      {
        return symbol_type (token::UNDEFINED);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUE ()
      {
        return symbol_type (token::TRUE);
      }
#else
      static
      symbol_type
      make_TRUE ()
      {
        return symbol_type (token::TRUE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE ()
      {
        return symbol_type (token::FALSE);
      }
#else
      static
      symbol_type
      make_FALSE ()
      {
        return symbol_type (token::FALSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIZE ()
      {
        return symbol_type (token::SIZE);
      }
#else
      static
      symbol_type
      make_SIZE ()
      {
        return symbol_type (token::SIZE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GAME ()
      {
        return symbol_type (token::GAME);
      }
#else
      static
      symbol_type
      make_GAME ()
      {
        return symbol_type (token::GAME);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEVEL ()
      {
        return symbol_type (token::LEVEL);
      }
#else
      static
      symbol_type
      make_LEVEL ()
      {
        return symbol_type (token::LEVEL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ANIM ()
      {
        return symbol_type (token::ANIM);
      }
#else
      static
      symbol_type
      make_ANIM ()
      {
        return symbol_type (token::ANIM);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SELF ()
      {
        return symbol_type (token::SELF);
      }
#else
      static
      symbol_type
      make_SELF ()
      {
        return symbol_type (token::SELF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EMPTY_ARRAY ()
      {
        return symbol_type (token::EMPTY_ARRAY);
      }
#else
      static
      symbol_type
      make_EMPTY_ARRAY ()
      {
        return symbol_type (token::EMPTY_ARRAY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN ()
      {
        return symbol_type (token::LPAREN);
      }
#else
      static
      symbol_type
      make_LPAREN ()
      {
        return symbol_type (token::LPAREN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN ()
      {
        return symbol_type (token::RPAREN);
      }
#else
      static
      symbol_type
      make_RPAREN ()
      {
        return symbol_type (token::RPAREN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACE ()
      {
        return symbol_type (token::LBRACE);
      }
#else
      static
      symbol_type
      make_LBRACE ()
      {
        return symbol_type (token::LBRACE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACE ()
      {
        return symbol_type (token::RBRACE);
      }
#else
      static
      symbol_type
      make_RBRACE ()
      {
        return symbol_type (token::RBRACE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACKET ()
      {
        return symbol_type (token::LBRACKET);
      }
#else
      static
      symbol_type
      make_LBRACKET ()
      {
        return symbol_type (token::LBRACKET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACKET ()
      {
        return symbol_type (token::RBRACKET);
      }
#else
      static
      symbol_type
      make_RBRACKET ()
      {
        return symbol_type (token::RBRACKET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::COMMA);
      }
#else
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::COMMA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT ()
      {
        return symbol_type (token::DOT);
      }
#else
      static
      symbol_type
      make_DOT ()
      {
        return symbol_type (token::DOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOUBLECOLON ()
      {
        return symbol_type (token::DOUBLECOLON);
      }
#else
      static
      symbol_type
      make_DOUBLECOLON ()
      {
        return symbol_type (token::DOUBLECOLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON ()
      {
        return symbol_type (token::COLON);
      }
#else
      static
      symbol_type
      make_COLON ()
      {
        return symbol_type (token::COLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON ()
      {
        return symbol_type (token::SEMICOLON);
      }
#else
      static
      symbol_type
      make_SEMICOLON ()
      {
        return symbol_type (token::SEMICOLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_QMARK ()
      {
        return symbol_type (token::QMARK);
      }
#else
      static
      symbol_type
      make_QMARK ()
      {
        return symbol_type (token::QMARK);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD ()
      {
        return symbol_type (token::MOD);
      }
#else
      static
      symbol_type
      make_MOD ()
      {
        return symbol_type (token::MOD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INCREMENT ()
      {
        return symbol_type (token::INCREMENT);
      }
#else
      static
      symbol_type
      make_INCREMENT ()
      {
        return symbol_type (token::INCREMENT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DECREMENT ()
      {
        return symbol_type (token::DECREMENT);
      }
#else
      static
      symbol_type
      make_DECREMENT ()
      {
        return symbol_type (token::DECREMENT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSHIFT ()
      {
        return symbol_type (token::LSHIFT);
      }
#else
      static
      symbol_type
      make_LSHIFT ()
      {
        return symbol_type (token::LSHIFT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RSHIFT ()
      {
        return symbol_type (token::RSHIFT);
      }
#else
      static
      symbol_type
      make_RSHIFT ()
      {
        return symbol_type (token::RSHIFT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR ()
      {
        return symbol_type (token::OR);
      }
#else
      static
      symbol_type
      make_OR ()
      {
        return symbol_type (token::OR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND ()
      {
        return symbol_type (token::AND);
      }
#else
      static
      symbol_type
      make_AND ()
      {
        return symbol_type (token::AND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUALITY ()
      {
        return symbol_type (token::EQUALITY);
      }
#else
      static
      symbol_type
      make_EQUALITY ()
      {
        return symbol_type (token::EQUALITY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INEQUALITY ()
      {
        return symbol_type (token::INEQUALITY);
      }
#else
      static
      symbol_type
      make_INEQUALITY ()
      {
        return symbol_type (token::INEQUALITY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESS_EQUAL ()
      {
        return symbol_type (token::LESS_EQUAL);
      }
#else
      static
      symbol_type
      make_LESS_EQUAL ()
      {
        return symbol_type (token::LESS_EQUAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER_EQUAL ()
      {
        return symbol_type (token::GREATER_EQUAL);
      }
#else
      static
      symbol_type
      make_GREATER_EQUAL ()
      {
        return symbol_type (token::GREATER_EQUAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESS ()
      {
        return symbol_type (token::LESS);
      }
#else
      static
      symbol_type
      make_LESS ()
      {
        return symbol_type (token::LESS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER ()
      {
        return symbol_type (token::GREATER);
      }
#else
      static
      symbol_type
      make_GREATER ()
      {
        return symbol_type (token::GREATER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN ()
      {
        return symbol_type (token::ASSIGN);
      }
#else
      static
      symbol_type
      make_ASSIGN ()
      {
        return symbol_type (token::ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_ADD ()
      {
        return symbol_type (token::ASSIGN_ADD);
      }
#else
      static
      symbol_type
      make_ASSIGN_ADD ()
      {
        return symbol_type (token::ASSIGN_ADD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_SUB ()
      {
        return symbol_type (token::ASSIGN_SUB);
      }
#else
      static
      symbol_type
      make_ASSIGN_SUB ()
      {
        return symbol_type (token::ASSIGN_SUB);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_MULT ()
      {
        return symbol_type (token::ASSIGN_MULT);
      }
#else
      static
      symbol_type
      make_ASSIGN_MULT ()
      {
        return symbol_type (token::ASSIGN_MULT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_DIV ()
      {
        return symbol_type (token::ASSIGN_DIV);
      }
#else
      static
      symbol_type
      make_ASSIGN_DIV ()
      {
        return symbol_type (token::ASSIGN_DIV);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_MOD ()
      {
        return symbol_type (token::ASSIGN_MOD);
      }
#else
      static
      symbol_type
      make_ASSIGN_MOD ()
      {
        return symbol_type (token::ASSIGN_MOD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_BITWISE_OR ()
      {
        return symbol_type (token::ASSIGN_BITWISE_OR);
      }
#else
      static
      symbol_type
      make_ASSIGN_BITWISE_OR ()
      {
        return symbol_type (token::ASSIGN_BITWISE_OR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_BITWISE_AND ()
      {
        return symbol_type (token::ASSIGN_BITWISE_AND);
      }
#else
      static
      symbol_type
      make_ASSIGN_BITWISE_AND ()
      {
        return symbol_type (token::ASSIGN_BITWISE_AND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_BITWISE_EXOR ()
      {
        return symbol_type (token::ASSIGN_BITWISE_EXOR);
      }
#else
      static
      symbol_type
      make_ASSIGN_BITWISE_EXOR ()
      {
        return symbol_type (token::ASSIGN_BITWISE_EXOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_LSHIFT ()
      {
        return symbol_type (token::ASSIGN_LSHIFT);
      }
#else
      static
      symbol_type
      make_ASSIGN_LSHIFT ()
      {
        return symbol_type (token::ASSIGN_LSHIFT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_RSHIFT ()
      {
        return symbol_type (token::ASSIGN_RSHIFT);
      }
#else
      static
      symbol_type
      make_ASSIGN_RSHIFT ()
      {
        return symbol_type (token::ASSIGN_RSHIFT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BITWISE_OR ()
      {
        return symbol_type (token::BITWISE_OR);
      }
#else
      static
      symbol_type
      make_BITWISE_OR ()
      {
        return symbol_type (token::BITWISE_OR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BITWISE_AND ()
      {
        return symbol_type (token::BITWISE_AND);
      }
#else
      static
      symbol_type
      make_BITWISE_AND ()
      {
        return symbol_type (token::BITWISE_AND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BITWISE_EXOR ()
      {
        return symbol_type (token::BITWISE_EXOR);
      }
#else
      static
      symbol_type
      make_BITWISE_EXOR ()
      {
        return symbol_type (token::BITWISE_EXOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ADD ()
      {
        return symbol_type (token::ADD);
      }
#else
      static
      symbol_type
      make_ADD ()
      {
        return symbol_type (token::ADD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB ()
      {
        return symbol_type (token::SUB);
      }
#else
      static
      symbol_type
      make_SUB ()
      {
        return symbol_type (token::SUB);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MULT ()
      {
        return symbol_type (token::MULT);
      }
#else
      static
      symbol_type
      make_MULT ()
      {
        return symbol_type (token::MULT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV ()
      {
        return symbol_type (token::DIV);
      }
#else
      static
      symbol_type
      make_DIV ()
      {
        return symbol_type (token::DIV);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT ()
      {
        return symbol_type (token::NOT);
      }
#else
      static
      symbol_type
      make_NOT ()
      {
        return symbol_type (token::NOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMPLEMENT ()
      {
        return symbol_type (token::COMPLEMENT);
      }
#else
      static
      symbol_type
      make_COMPLEMENT ()
      {
        return symbol_type (token::COMPLEMENT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FILEPATH (std::string v)
      {
        return symbol_type (token::FILEPATH, std::move (v));
      }
#else
      static
      symbol_type
      make_FILEPATH (const std::string& v)
      {
        return symbol_type (token::FILEPATH, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v)
      {
        return symbol_type (token::IDENTIFIER, std::move (v));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v)
      {
        return symbol_type (token::IDENTIFIER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ANIMREF (std::string v)
      {
        return symbol_type (token::ANIMREF, std::move (v));
      }
#else
      static
      symbol_type
      make_ANIMREF (const std::string& v)
      {
        return symbol_type (token::ANIMREF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (std::string v)
      {
        return symbol_type (token::STRING, std::move (v));
      }
#else
      static
      symbol_type
      make_STRING (const std::string& v)
      {
        return symbol_type (token::STRING, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING_LOC (std::string v)
      {
        return symbol_type (token::STRING_LOC, std::move (v));
      }
#else
      static
      symbol_type
      make_STRING_LOC (const std::string& v)
      {
        return symbol_type (token::STRING_LOC, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (std::string v)
      {
        return symbol_type (token::FLOAT, std::move (v));
      }
#else
      static
      symbol_type
      make_FLOAT (const std::string& v)
      {
        return symbol_type (token::FLOAT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER (std::string v)
      {
        return symbol_type (token::INTEGER, std::move (v));
      }
#else
      static
      symbol_type
      make_INTEGER (const std::string& v)
      {
        return symbol_type (token::INTEGER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IFX ()
      {
        return symbol_type (token::IFX);
      }
#else
      static
      symbol_type
      make_IFX ()
      {
        return symbol_type (token::IFX);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const { return yyla_; }
      symbol_kind_type token () const { return yyla_.kind (); }
      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif

    /// Check the lookahead yytoken.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_check_ (symbol_kind_type yytoken) const;
    /// Establish the initial context if no initial context currently exists.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_establish_ (symbol_kind_type yytoken);
    /// Discard any previous initial lookahead context because of event.
    /// \param event  the event which caused the lookahead to be discarded.
    ///               Only used for debbuging output.
    void yy_lac_discard_ (const char* event);

    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const short yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);



    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const unsigned char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if H2DEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;
    /// The stack for LAC.
    /// Logically, the yy_lac_stack's lifetime is confined to the function
    /// yy_lac_check_. We just store it as a member of this class to hold
    /// on to the memory and to avoid frequent reallocations.
    /// Since yy_lac_check_ is const, this member must be mutable.
    mutable std::vector<state_type> yylac_stack_;
    /// Whether an initial LAC context was established.
    bool yy_lac_established_;


    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 2397,     ///< Last index in yytable_.
      yynnts_ = 68,  ///< Number of nonterminal symbols.
      yyfinal_ = 16 ///< Termination state number.
    };


    // User arguments.
    yyscan_t yyscanner;
    std::uint32_t *location;
    gsc::script_ptr& astout;

  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t)
  {
    return static_cast<symbol_kind_type> (t);
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_animref: // animref
        value.copy< gsc::animref_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.copy< gsc::block_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.copy< gsc::expr_arguments_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.copy< gsc::expr_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.copy< gsc::expr_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.copy< gsc::expr_call_type_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.copy< gsc::expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_filepath: // filepath
        value.copy< gsc::filepath_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_float: // data_float
        value.copy< gsc::float_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.copy< gsc::identifier_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_include: // include
        value.copy< gsc::include_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_integer: // data_integer
        value.copy< gsc::integer_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.copy< gsc::localized_string_ptr > (YY_MOVE (that.value));
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
        value.copy< gsc::node_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
        value.copy< gsc::parameters_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.copy< gsc::script_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.copy< gsc::stmt_assign_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.copy< gsc::stmt_break_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.copy< gsc::stmt_call_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.copy< gsc::stmt_case_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.copy< gsc::stmt_continue_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.copy< gsc::stmt_default_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.copy< gsc::stmt_endon_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.copy< gsc::stmt_for_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.copy< gsc::stmt_foreach_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.copy< gsc::stmt_if_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.copy< gsc::stmt_ifelse_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.copy< gsc::stmt_notify_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.copy< gsc::stmt_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.copy< gsc::stmt_return_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.copy< gsc::stmt_switch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.copy< gsc::stmt_wait_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.copy< gsc::stmt_waitframe_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.copy< gsc::stmt_waittill_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.copy< gsc::stmt_waittillframeend_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.copy< gsc::stmt_waittillmatch_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.copy< gsc::stmt_while_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_data_string: // data_string
        value.copy< gsc::string_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_thread: // thread
        value.copy< gsc::thread_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.copy< gsc::using_animtree_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_ANIMREF: // ANIMREF
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_animref: // animref
        value.move< gsc::animref_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_block: // block
        value.move< gsc::block_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_arguments: // expr_arguments
        value.move< gsc::expr_arguments_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_assign: // expr_assign
        value.move< gsc::expr_assign_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_call: // expr_call
      case symbol_kind::S_expr_call_thread: // expr_call_thread
        value.move< gsc::expr_call_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_call_function: // expr_call_function
      case symbol_kind::S_expr_call_pointer: // expr_call_pointer
        value.move< gsc::expr_call_type_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_for_assign: // for_assign
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_expr_cmp: // expr_cmp
      case symbol_kind::S_expr_ternary: // expr_ternary
      case symbol_kind::S_expr_binary: // expr_binary
      case symbol_kind::S_expr_primitive: // expr_primitive
        value.move< gsc::expr_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_filepath: // filepath
        value.move< gsc::filepath_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_data_float: // data_float
        value.move< gsc::float_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_identifier: // identifier
        value.move< gsc::identifier_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_include: // include
        value.move< gsc::include_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_data_integer: // data_integer
        value.move< gsc::integer_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_data_localized_string: // data_localized_string
        value.move< gsc::localized_string_ptr > (YY_MOVE (s.value));
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
        value.move< gsc::node_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_parameters: // parameters
        value.move< gsc::parameters_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script: // script
        value.move< gsc::script_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_assign: // stmt_assign
        value.move< gsc::stmt_assign_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_break: // stmt_break
        value.move< gsc::stmt_break_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_call: // stmt_call
        value.move< gsc::stmt_call_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_case: // stmt_case
        value.move< gsc::stmt_case_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_continue: // stmt_continue
        value.move< gsc::stmt_continue_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_default: // stmt_default
        value.move< gsc::stmt_default_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_endon: // stmt_endon
        value.move< gsc::stmt_endon_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_for: // stmt_for
        value.move< gsc::stmt_for_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_foreach: // stmt_foreach
        value.move< gsc::stmt_foreach_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_if: // stmt_if
        value.move< gsc::stmt_if_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_ifelse: // stmt_ifelse
        value.move< gsc::stmt_ifelse_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_notify: // stmt_notify
        value.move< gsc::stmt_notify_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt: // stmt
        value.move< gsc::stmt_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_return: // stmt_return
        value.move< gsc::stmt_return_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_switch: // stmt_switch
        value.move< gsc::stmt_switch_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_wait: // stmt_wait
        value.move< gsc::stmt_wait_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_waitframe: // stmt_waitframe
        value.move< gsc::stmt_waitframe_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_waittill: // stmt_waittill
        value.move< gsc::stmt_waittill_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_waittillframeend: // stmt_waittillframeend
        value.move< gsc::stmt_waittillframeend_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_waittillmatch: // stmt_waittillmatch
        value.move< gsc::stmt_waittillmatch_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_while: // stmt_while
        value.move< gsc::stmt_while_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_data_string: // data_string
        value.move< gsc::string_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_thread: // thread
        value.move< gsc::thread_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_using_animtree: // using_animtree
      case symbol_kind::S_animtree: // animtree
        value.move< gsc::using_animtree_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FILEPATH: // FILEPATH
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_ANIMREF: // ANIMREF
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_STRING_LOC: // STRING_LOC
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  inline
  parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

#line 14 "H2.parser.ypp"
} // H2
#line 4136 "./H2/compiler_parser.hpp"




#endif // !YY_H2_H2_COMPILER_PARSER_HPP_INCLUDED
