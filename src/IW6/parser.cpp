/* A Bison parser, made by GNU Bison 3.7.3.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "iw6.parser.ypp"

#include "IW6.hpp"
#include "parser.hpp"
#include "lexer.hpp"

int yyerror(yyscan_t scanner, node **astout, const char *msg);

#line 79 "./IW6/parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* EOF  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INCLUDE = 3,                    /* INCLUDE  */
  YYSYMBOL_USING_ANIMTREE = 4,             /* USING_ANIMTREE  */
  YYSYMBOL_ANIMTREE = 5,                   /* ANIMTREE  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_SWITCH = 8,                     /* SWITCH  */
  YYSYMBOL_CASE = 9,                       /* CASE  */
  YYSYMBOL_DEFAULT = 10,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 11,                     /* BREAK  */
  YYSYMBOL_FOR = 12,                       /* FOR  */
  YYSYMBOL_FOREACH = 13,                   /* FOREACH  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_CONTINUE = 15,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_THREAD = 17,                    /* THREAD  */
  YYSYMBOL_WAIT = 18,                      /* WAIT  */
  YYSYMBOL_WAITTILL = 19,                  /* WAITTILL  */
  YYSYMBOL_WAITTILLMATCH = 20,             /* WAITTILLMATCH  */
  YYSYMBOL_WAITTILLFRAMEEND = 21,          /* WAITTILLFRAMEEND  */
  YYSYMBOL_ENDON = 22,                     /* ENDON  */
  YYSYMBOL_NOTIFY = 23,                    /* NOTIFY  */
  YYSYMBOL_IN = 24,                        /* IN  */
  YYSYMBOL_UNDEFINED = 25,                 /* UNDEFINED  */
  YYSYMBOL_TRUE = 26,                      /* TRUE  */
  YYSYMBOL_FALSE = 27,                     /* FALSE  */
  YYSYMBOL_SIZE = 28,                      /* SIZE  */
  YYSYMBOL_GAME = 29,                      /* GAME  */
  YYSYMBOL_LEVEL = 30,                     /* LEVEL  */
  YYSYMBOL_EMPTY_ARRAY = 31,               /* EMPTY_ARRAY  */
  YYSYMBOL_LPAREN = 32,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 33,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 34,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 35,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 36,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 37,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 38,                     /* COMMA  */
  YYSYMBOL_DOT = 39,                       /* DOT  */
  YYSYMBOL_DOUBLECOLON = 40,               /* DOUBLECOLON  */
  YYSYMBOL_COLON = 41,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 42,                 /* SEMICOLON  */
  YYSYMBOL_QMARK = 43,                     /* QMARK  */
  YYSYMBOL_MOD = 44,                       /* MOD  */
  YYSYMBOL_INC = 45,                       /* INC  */
  YYSYMBOL_DEC = 46,                       /* DEC  */
  YYSYMBOL_LSHIFT = 47,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 48,                    /* RSHIFT  */
  YYSYMBOL_CMP_OR = 49,                    /* CMP_OR  */
  YYSYMBOL_CMP_AND = 50,                   /* CMP_AND  */
  YYSYMBOL_CMP_EQUAL = 51,                 /* CMP_EQUAL  */
  YYSYMBOL_CMP_NOT_EQ = 52,                /* CMP_NOT_EQ  */
  YYSYMBOL_CMP_LESS_EQ = 53,               /* CMP_LESS_EQ  */
  YYSYMBOL_CMP_GREATER_EQ = 54,            /* CMP_GREATER_EQ  */
  YYSYMBOL_CMP_LESS = 55,                  /* CMP_LESS  */
  YYSYMBOL_CMP_GREATER = 56,               /* CMP_GREATER  */
  YYSYMBOL_ASSIGN = 57,                    /* ASSIGN  */
  YYSYMBOL_ASSIGN_ADD = 58,                /* ASSIGN_ADD  */
  YYSYMBOL_ASSIGN_SUB = 59,                /* ASSIGN_SUB  */
  YYSYMBOL_ASSIGN_MULT = 60,               /* ASSIGN_MULT  */
  YYSYMBOL_ASSIGN_DIV = 61,                /* ASSIGN_DIV  */
  YYSYMBOL_ASSIGN_MOD = 62,                /* ASSIGN_MOD  */
  YYSYMBOL_ASSIGN_BW_OR = 63,              /* ASSIGN_BW_OR  */
  YYSYMBOL_ASSIGN_BW_AND = 64,             /* ASSIGN_BW_AND  */
  YYSYMBOL_ASSIGN_BW_XOR = 65,             /* ASSIGN_BW_XOR  */
  YYSYMBOL_ASSIGN_LSHIFT = 66,             /* ASSIGN_LSHIFT  */
  YYSYMBOL_ASSIGN_RSHIFT = 67,             /* ASSIGN_RSHIFT  */
  YYSYMBOL_BW_OR = 68,                     /* BW_OR  */
  YYSYMBOL_BW_AND = 69,                    /* BW_AND  */
  YYSYMBOL_BW_XOR = 70,                    /* BW_XOR  */
  YYSYMBOL_ADD = 71,                       /* ADD  */
  YYSYMBOL_SUB = 72,                       /* SUB  */
  YYSYMBOL_MULT = 73,                      /* MULT  */
  YYSYMBOL_DIV = 74,                       /* DIV  */
  YYSYMBOL_NOT = 75,                       /* NOT  */
  YYSYMBOL_COMPLEMENT = 76,                /* COMPLEMENT  */
  YYSYMBOL_FILEPATH = 77,                  /* FILEPATH  */
  YYSYMBOL_IDENTIFIER = 78,                /* IDENTIFIER  */
  YYSYMBOL_STRING = 79,                    /* STRING  */
  YYSYMBOL_STRING_LOC = 80,                /* STRING_LOC  */
  YYSYMBOL_STRING_HASH = 81,               /* STRING_HASH  */
  YYSYMBOL_FLOAT = 82,                     /* FLOAT  */
  YYSYMBOL_INTEGER = 83,                   /* INTEGER  */
  YYSYMBOL_YYACCEPT = 84,                  /* $accept  */
  YYSYMBOL_root = 85,                      /* root  */
  YYSYMBOL_script = 86,                    /* script  */
  YYSYMBOL_include = 87,                   /* include  */
  YYSYMBOL_using_animtree = 88,            /* using_animtree  */
  YYSYMBOL_function = 89,                  /* function  */
  YYSYMBOL_parameter_list = 90,            /* parameter_list  */
  YYSYMBOL_stmt_block = 91,                /* stmt_block  */
  YYSYMBOL_stmt = 92,                      /* stmt  */
  YYSYMBOL_stmt_call = 93,                 /* stmt_call  */
  YYSYMBOL_stmt_assign = 94,               /* stmt_assign  */
  YYSYMBOL_stmt_endon = 95,                /* stmt_endon  */
  YYSYMBOL_stmt_notify = 96,               /* stmt_notify  */
  YYSYMBOL_stmt_wait = 97,                 /* stmt_wait  */
  YYSYMBOL_expr = 98,                      /* expr  */
  YYSYMBOL_expr_assign = 99,               /* expr_assign  */
  YYSYMBOL_expr_cmp = 100,                 /* expr_cmp  */
  YYSYMBOL_expr_ternary = 101,             /* expr_ternary  */
  YYSYMBOL_expr_binary = 102,              /* expr_binary  */
  YYSYMBOL_expr_unary = 103,               /* expr_unary  */
  YYSYMBOL_expr_call = 104,                /* expr_call  */
  YYSYMBOL_expr_call_thread = 105,         /* expr_call_thread  */
  YYSYMBOL_expr_func_call = 106,           /* expr_func_call  */
  YYSYMBOL_expr_func_call_ptr = 107,       /* expr_func_call_ptr  */
  YYSYMBOL_expr_arg_list = 108,            /* expr_arg_list  */
  YYSYMBOL_expr_select = 109,              /* expr_select  */
  YYSYMBOL_expr_subscribe = 110,           /* expr_subscribe  */
  YYSYMBOL_expr_func_ref = 111,            /* expr_func_ref  */
  YYSYMBOL_object = 112,                   /* object  */
  YYSYMBOL_object_restricted = 113,        /* object_restricted  */
  YYSYMBOL_level = 114,                    /* level  */
  YYSYMBOL_game = 115,                     /* game  */
  YYSYMBOL_empty_array = 116,              /* empty_array  */
  YYSYMBOL_undefined = 117,                /* undefined  */
  YYSYMBOL_vector = 118,                   /* vector  */
  YYSYMBOL_num = 119,                      /* num  */
  YYSYMBOL_num_float = 120,                /* num_float  */
  YYSYMBOL_num_integer = 121,              /* num_integer  */
  YYSYMBOL_string_hash = 122,              /* string_hash  */
  YYSYMBOL_string_loc = 123,               /* string_loc  */
  YYSYMBOL_string = 124,                   /* string  */
  YYSYMBOL_identifier = 125,               /* identifier  */
  YYSYMBOL_filepath = 126                  /* filepath  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
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


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   683

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  127
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  241

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   338


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    84,    88,    89,    90,    91,    92,    93,
      97,    98,   102,   106,   110,   111,   112,   116,   117,   118,
     123,   124,   125,   126,   127,   131,   132,   136,   140,   144,
     145,   149,   150,   155,   156,   157,   158,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     178,   179,   180,   181,   182,   183,   184,   185,   189,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   227,   228,   229,
     230,   234,   235,   236,   237,   242,   243,   244,   249,   253,
     254,   255,   260,   261,   266,   267,   272,   273,   274,   279,
     280,   285,   286,   287,   291,   296,   300,   304,   308,   312,
     313,   317,   321,   325,   329,   333,   337,   341
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "EOF", "error", "\"invalid token\"", "INCLUDE", "USING_ANIMTREE",
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
  "STRING_LOC", "STRING_HASH", "FLOAT", "INTEGER", "$accept", "root",
  "script", "include", "using_animtree", "function", "parameter_list",
  "stmt_block", "stmt", "stmt_call", "stmt_assign", "stmt_endon",
  "stmt_notify", "stmt_wait", "expr", "expr_assign", "expr_cmp",
  "expr_ternary", "expr_binary", "expr_unary", "expr_call",
  "expr_call_thread", "expr_func_call", "expr_func_call_ptr",
  "expr_arg_list", "expr_select", "expr_subscribe", "expr_func_ref",
  "object", "object_restricted", "level", "game", "empty_array",
  "undefined", "vector", "num", "num_float", "num_integer", "string_hash",
  "string_loc", "string", "identifier", "filepath", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338
};
#endif

#define YYPACT_NINF (-109)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-114)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,   -60,   -11,  -109,    23,     5,  -109,  -109,  -109,    -5,
    -109,    -2,     4,   -35,  -109,  -109,  -109,  -109,   -16,  -109,
    -109,  -109,    59,    30,  -109,    52,    79,   -16,  -109,    40,
    -109,   -23,   -22,  -109,  -109,    85,     7,  -109,  -109,  -109,
    -109,  -109,  -109,    80,    94,   105,  -109,  -109,  -109,  -109,
      11,   223,   109,   110,   -26,   118,  -109,  -109,   -26,    74,
    -109,  -109,   119,  -109,  -109,    74,  -109,  -109,  -109,  -109,
    -109,   -23,   161,   -16,  -109,  -109,   130,   132,  -109,  -109,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,   -16,    74,    74,   -16,   -16,  -109,  -109,    74,   -16,
      74,    74,  -109,  -109,   331,   123,  -109,  -109,  -109,    42,
    -109,   146,   148,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,     9,   127,  -109,   431,  -109,  -109,   161,
     469,  -109,    74,    74,   609,   609,   609,   609,   609,   609,
     609,   609,   609,   609,   609,  -109,   507,   609,    44,   136,
     137,   258,   133,  -109,  -109,  -109,   609,   609,   128,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,   -16,   -16,
     140,  -109,   362,   300,  -109,  -109,    74,    74,    74,  -109,
      74,    29,  -109,   609,   609,   609,   609,   609,   609,   609,
     609,   609,   609,   609,   609,   609,   609,   609,   609,   609,
     609,   578,   136,   137,   141,   147,   152,    74,   609,    57,
     101,   544,   145,    74,    74,  -109,  -109,   104,  -109,  -109,
      74,    29,   609,   107,   153,   393,   155,  -109,  -109,  -109,
    -109
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,   126,     0,     2,     7,     8,     9,     0,
     127,     0,     0,     0,     1,     4,     5,     6,    16,    11,
      10,   125,     0,     0,    15,     0,     0,     0,    12,    19,
      14,     0,     0,   115,   114,     0,     0,    18,    20,    21,
      22,    23,    24,     0,   109,     0,    87,    88,   112,   111,
       0,   110,     0,     0,   113,     0,    91,    92,     0,     0,
     121,   122,     0,   119,   120,     0,    13,    17,    27,    25,
      26,     0,     0,     0,    89,    90,     0,     0,    37,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,     0,     0,   117,   116,     0,     0,
       0,     0,   124,   123,     0,    33,    34,    35,    36,    71,
      72,    73,    74,    75,   110,    76,    77,    79,    80,    81,
      82,    83,    84,    85,     0,    32,     0,    93,    94,     0,
       0,   102,     0,     0,    39,    45,    46,    47,    48,    49,
      40,    41,    42,    43,    44,   103,     0,   100,     0,     0,
       0,     0,     0,    80,    81,   106,    70,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,     0,     0,   105,    95,     0,   101,   101,    86,
       0,     0,    31,    68,    62,    63,    50,    51,    52,    53,
      54,    55,    56,    57,    59,    60,    61,    64,    65,    66,
      67,     0,   107,   108,     0,     0,     0,   101,    99,     0,
       0,     0,     0,     0,   101,    28,    30,     0,    97,    96,
       0,     0,    58,     0,     0,     0,     0,    98,    29,    78,
     118
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,  -109,   169,   174,   191,  -109,  -109,   162,  -109,
    -109,  -109,  -109,  -109,    43,  -109,  -109,  -109,  -109,  -109,
     -17,   -14,   -20,   -15,  -108,    35,    36,  -109,  -109,    71,
    -109,  -109,  -109,  -109,  -109,   -93,   -32,   -31,  -109,  -109,
     208,     2,     3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    23,    36,    37,    38,
      39,    40,    41,    42,   147,    43,   105,   106,   107,   108,
     109,   110,    46,    47,   148,   111,   112,   113,    50,   114,
      52,    53,   115,   116,   117,    62,   118,   119,   120,   121,
     122,   123,   124
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      63,    64,     9,    11,    12,   152,    93,     9,     1,     2,
      59,    56,    44,    35,    94,    45,    57,    10,     3,    44,
      24,    13,    45,    14,    31,    32,  -113,    18,    71,    30,
      74,    54,    55,    58,    55,    75,    33,    34,    54,    55,
      19,    93,    66,    35,    21,  -113,    20,    72,  -113,   178,
      73,   127,    58,    55,    10,     3,   128,    31,    32,  -109,
      60,    61,     3,    26,    48,    49,   153,   154,    27,    33,
      34,    48,    49,    58,    55,   131,    35,   185,  -109,   219,
     220,  -109,   186,     3,    10,     3,  -113,  -113,    10,     3,
     228,    31,    25,   145,    28,   186,   149,   150,   222,    96,
      51,   155,   104,    33,    34,    97,    98,    51,   126,   227,
      35,    60,    61,    29,    99,   130,   233,    10,     3,  -109,
    -109,    65,    68,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   229,   146,    69,   234,   236,   186,
     237,   151,   186,   156,   157,   186,    92,    70,    91,   100,
     101,    10,     3,    21,   102,   103,    60,    61,    95,    63,
      64,   125,   132,  -112,   133,  -111,   177,   179,   187,   188,
     192,   191,   126,   224,    15,   182,   183,   214,    31,    16,
     212,   213,  -112,   231,  -111,  -112,    96,  -111,   240,   225,
      33,    34,    97,    98,   226,   238,    17,   129,    67,    63,
      64,    99,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,    22,     0,  -112,  -112,  -111,  -111,     0,     0,   218,
       0,     0,     0,   221,     0,     0,   100,   101,    10,     3,
      21,   102,   103,    60,    61,    76,    77,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   232,     0,    78,    79,
       0,     0,     0,   235,     0,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   189,     0,     0,     0,     0,   190,     0,     0,     0,
       0,     0,   159,     0,     0,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,   171,   172,   173,
     174,   175,   176,   216,     0,     0,     0,     0,   217,     0,
       0,     0,     0,     0,   159,     0,     0,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,     0,     0,     0,
       0,     0,     0,     0,   158,     0,     0,     0,   170,   171,
     172,   173,   174,   175,   176,   159,     0,     0,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,     0,     0,
       0,     0,     0,     0,     0,   215,     0,     0,     0,   170,
     171,   172,   173,   174,   175,   176,   159,     0,     0,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,     0,
       0,     0,     0,     0,     0,     0,   239,     0,     0,     0,
     170,   171,   172,   173,   174,   175,   176,   159,     0,     0,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   170,   171,   172,   173,   174,   175,   176,   180,     0,
       0,     0,     0,     0,     0,   159,     0,     0,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   170,
     171,   172,   173,   174,   175,   176,   181,     0,     0,     0,
       0,     0,     0,   159,     0,     0,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   170,   171,   172,
     173,   174,   175,   176,   184,     0,     0,     0,     0,     0,
       0,   159,     0,     0,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   170,   171,   172,   173,   174,
     175,   176,   230,     0,     0,     0,     0,     0,   159,     0,
       0,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   170,   171,   172,   173,   174,   175,   176,   223,
       0,     0,   159,     0,     0,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,   171,   172,   173,
     174,   175,   176,   159,     0,     0,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   170,   171,   172,
     173,   174,   175,   176
};

static const yytype_int16 yycheck[] =
{
      32,    32,     0,     1,     1,    98,    32,     5,     3,     4,
      32,    31,    29,    36,    40,    29,    31,    77,    78,    36,
      18,    32,    36,     0,    17,    18,    17,    32,    17,    27,
      50,    29,    29,    31,    31,    50,    29,    30,    36,    36,
      42,    32,    35,    36,    79,    36,    42,    36,    39,    40,
      39,    71,    50,    50,    77,    78,    71,    17,    18,    17,
      82,    83,    78,    33,    29,    29,    98,    98,    38,    29,
      30,    36,    36,    71,    71,    73,    36,    33,    36,   187,
     188,    39,    38,    78,    77,    78,    77,    78,    77,    78,
      33,    17,    33,    91,    42,    38,    94,    95,   191,    25,
      29,    99,    59,    29,    30,    31,    32,    36,    65,   217,
      36,    82,    83,    34,    40,    72,   224,    77,    78,    77,
      78,    36,    42,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    33,    92,    42,    33,   231,    38,
      33,    98,    38,   100,   101,    38,    36,    42,    39,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    40,   191,
     191,    42,    32,    17,    32,    17,    43,    40,    32,    32,
      42,    38,   129,    32,     5,   132,   133,    37,    17,     5,
     178,   179,    36,    38,    36,    39,    25,    39,    33,    42,
      29,    30,    31,    32,    42,    42,     5,    36,    36,   231,
     231,    40,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,    13,    -1,    77,    78,    77,    78,    -1,    -1,   186,
      -1,    -1,    -1,   190,    -1,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    22,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   223,    -1,    45,    46,
      -1,    -1,    -1,   230,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    33,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    33,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    47,    48,    49,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    38,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    41,
      -1,    -1,    44,    -1,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    44,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    78,    85,    86,    87,    88,    89,   125,
      77,   125,   126,    32,     0,    87,    88,    89,    32,    42,
      42,    79,   124,    90,   125,    33,    33,    38,    42,    34,
     125,    17,    18,    29,    30,    36,    91,    92,    93,    94,
      95,    96,    97,    99,   104,   105,   106,   107,   109,   110,
     112,   113,   114,   115,   125,   126,   106,   107,   125,    32,
      82,    83,   119,   120,   121,    36,    35,    92,    42,    42,
      42,    17,    36,    39,   106,   107,    22,    23,    45,    46,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    39,    36,    32,    40,    40,    25,    31,    32,    40,
      75,    76,    80,    81,    98,   100,   101,   102,   103,   104,
     105,   109,   110,   111,   113,   116,   117,   118,   120,   121,
     122,   123,   124,   125,   126,    42,    98,   106,   107,    36,
      98,   125,    32,    32,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,   125,    98,    98,   108,   125,
     125,    98,   119,   120,   121,   125,    98,    98,    33,    44,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      68,    69,    70,    71,    72,    73,    74,    43,    40,    40,
      37,    37,    98,    98,    37,    33,    38,    32,    32,    33,
      38,    38,    42,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,   125,   125,    37,    33,    33,    38,    98,   108,
     108,    98,   119,    41,    32,    42,    42,   108,    33,    33,
      38,    38,    98,   108,    33,    98,   119,    33,    42,    33,
      33
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    84,    85,    85,    86,    86,    86,    86,    86,    86,
      87,    87,    88,    89,    90,    90,    90,    91,    91,    91,
      92,    92,    92,    92,    92,    93,    93,    94,    95,    96,
      96,    97,    97,    98,    98,    98,    98,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
     100,   100,   100,   100,   100,   100,   100,   100,   101,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   104,   104,   104,
     104,   105,   105,   105,   105,   106,   106,   106,   107,   108,
     108,   108,   109,   109,   110,   110,   111,   111,   111,   112,
     112,   113,   113,   113,   114,   115,   116,   117,   118,   119,
     119,   120,   121,   122,   123,   124,   125,   126
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     5,     7,     3,     1,     0,     2,     1,     0,
       1,     1,     1,     1,     1,     2,     2,     2,     6,     8,
       6,     5,     3,     1,     1,     1,     1,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     7,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     2,
       2,     2,     2,     3,     3,     4,     6,     6,     8,     3,
       1,     0,     3,     3,     4,     4,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     7,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = TOK_YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == TOK_YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, astout, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use TOK_YYerror or TOK_YYUNDEF. */
#define YYERRCODE TOK_YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner, astout); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t scanner, node **astout)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  YYUSE (astout);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t scanner, node **astout)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner, astout);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, yyscan_t scanner, node **astout)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner, astout);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner, astout); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, yyscan_t scanner, node **astout)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  YYUSE (astout);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, node **astout)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = TOK_YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == TOK_YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= TOK_EOF)
    {
      yychar = TOK_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == TOK_YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = TOK_YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = TOK_YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* root: script  */
#line 83 "iw6.parser.ypp"
                                                                                { *astout = (yyvsp[0].value_script); }
#line 1472 "./IW6/parser.cpp"
    break;

  case 3: /* root: %empty  */
#line 84 "iw6.parser.ypp"
                                                                                                { *astout = new node(); }
#line 1478 "./IW6/parser.cpp"
    break;

  case 4: /* script: script include  */
#line 88 "iw6.parser.ypp"
                                                                                { (yyval.value_script) = (yyvsp[-1].value_script); (yyval.value_script)->childs.push_back((yyvsp[0].value_node)); }
#line 1484 "./IW6/parser.cpp"
    break;

  case 5: /* script: script using_animtree  */
#line 89 "iw6.parser.ypp"
                                                                        { (yyval.value_script) = (yyvsp[-1].value_script); (yyval.value_script)->childs.push_back((yyvsp[0].value_node)); }
#line 1490 "./IW6/parser.cpp"
    break;

  case 6: /* script: script function  */
#line 90 "iw6.parser.ypp"
                                                                                { (yyval.value_script) = (yyvsp[-1].value_script); (yyval.value_script)->childs.push_back((yyvsp[0].value_node)); }
#line 1496 "./IW6/parser.cpp"
    break;

  case 7: /* script: include  */
#line 91 "iw6.parser.ypp"
                                                                                        { (yyval.value_script) = new node_script(); (yyval.value_script)->childs.push_back((yyvsp[0].value_node));}
#line 1502 "./IW6/parser.cpp"
    break;

  case 8: /* script: using_animtree  */
#line 92 "iw6.parser.ypp"
                                                                                { (yyval.value_script) = new node_script(); (yyval.value_script)->childs.push_back((yyvsp[0].value_node));}
#line 1508 "./IW6/parser.cpp"
    break;

  case 9: /* script: function  */
#line 93 "iw6.parser.ypp"
                                                                                        { (yyval.value_script) = new node_script(); (yyval.value_script)->childs.push_back((yyvsp[0].value_node));}
#line 1514 "./IW6/parser.cpp"
    break;

  case 10: /* include: INCLUDE filepath SEMICOLON  */
#line 97 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_include((yyvsp[-1].value_node)); }
#line 1520 "./IW6/parser.cpp"
    break;

  case 11: /* include: INCLUDE identifier SEMICOLON  */
#line 98 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_include((yyvsp[-1].value_node)); }
#line 1526 "./IW6/parser.cpp"
    break;

  case 12: /* using_animtree: USING_ANIMTREE LPAREN string RPAREN SEMICOLON  */
#line 102 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_using_animtree((yyvsp[-2].value_node)); }
#line 1532 "./IW6/parser.cpp"
    break;

  case 13: /* function: identifier LPAREN parameter_list RPAREN LBRACE stmt_block RBRACE  */
#line 106 "iw6.parser.ypp"
                                                                           { (yyval.value_node) = new node_function((yyvsp[-6].value_node), (yyvsp[-4].value_parameter_list), (yyvsp[-1].value_statement_block)); }
#line 1538 "./IW6/parser.cpp"
    break;

  case 14: /* parameter_list: parameter_list COMMA identifier  */
#line 110 "iw6.parser.ypp"
                                                                { (yyval.value_parameter_list) = (yyvsp[-2].value_parameter_list); (yyval.value_parameter_list)->params.push_back((yyvsp[0].value_node)); }
#line 1544 "./IW6/parser.cpp"
    break;

  case 15: /* parameter_list: identifier  */
#line 111 "iw6.parser.ypp"
                                                                                { (yyval.value_parameter_list) = new node_parameter_list(); (yyval.value_parameter_list)->params.push_back((yyvsp[0].value_node)); }
#line 1550 "./IW6/parser.cpp"
    break;

  case 16: /* parameter_list: %empty  */
#line 112 "iw6.parser.ypp"
                                                                                                { (yyval.value_parameter_list) = new node_parameter_list(); }
#line 1556 "./IW6/parser.cpp"
    break;

  case 17: /* stmt_block: stmt_block stmt  */
#line 116 "iw6.parser.ypp"
                                                                                { (yyval.value_statement_block) = (yyvsp[-1].value_statement_block); (yyval.value_statement_block)->stmts.push_back((yyvsp[0].value_node)); }
#line 1562 "./IW6/parser.cpp"
    break;

  case 18: /* stmt_block: stmt  */
#line 117 "iw6.parser.ypp"
                                                                                        {(yyval.value_statement_block) = new node_stmt_block(); (yyval.value_statement_block)->stmts.push_back((yyvsp[0].value_node)); }
#line 1568 "./IW6/parser.cpp"
    break;

  case 19: /* stmt_block: %empty  */
#line 118 "iw6.parser.ypp"
                                                                                                { (yyval.value_statement_block) = new node_stmt_block(); }
#line 1574 "./IW6/parser.cpp"
    break;

  case 20: /* stmt: stmt_call  */
#line 123 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1580 "./IW6/parser.cpp"
    break;

  case 21: /* stmt: stmt_assign  */
#line 124 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1586 "./IW6/parser.cpp"
    break;

  case 22: /* stmt: stmt_endon  */
#line 125 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1592 "./IW6/parser.cpp"
    break;

  case 23: /* stmt: stmt_notify  */
#line 126 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1598 "./IW6/parser.cpp"
    break;

  case 24: /* stmt: stmt_wait  */
#line 127 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1604 "./IW6/parser.cpp"
    break;

  case 25: /* stmt_call: expr_call SEMICOLON  */
#line 131 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_stmt_call((yyvsp[-1].value_node)); }
#line 1610 "./IW6/parser.cpp"
    break;

  case 26: /* stmt_call: expr_call_thread SEMICOLON  */
#line 132 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_stmt_call((yyvsp[-1].value_node)); }
#line 1616 "./IW6/parser.cpp"
    break;

  case 27: /* stmt_assign: expr_assign SEMICOLON  */
#line 136 "iw6.parser.ypp"
                                { (yyval.value_node) = new node_stmt_assign((yyvsp[-1].value_node)); }
#line 1622 "./IW6/parser.cpp"
    break;

  case 28: /* stmt_endon: object_restricted ENDON LPAREN expr RPAREN SEMICOLON  */
#line 140 "iw6.parser.ypp"
                                                               { (yyval.value_node) = new node_stmt_endon((yyvsp[-5].value_node), (yyvsp[-2].value_node)); }
#line 1628 "./IW6/parser.cpp"
    break;

  case 29: /* stmt_notify: object_restricted NOTIFY LPAREN expr COMMA expr_arg_list RPAREN SEMICOLON  */
#line 144 "iw6.parser.ypp"
                                                                                    { (yyval.value_node) = new node_stmt_notify((yyvsp[-7].value_node), (yyvsp[-4].value_node), (yyvsp[-2].value_expr_arg_list)); }
#line 1634 "./IW6/parser.cpp"
    break;

  case 30: /* stmt_notify: object_restricted NOTIFY LPAREN expr RPAREN SEMICOLON  */
#line 145 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_stmt_notify((yyvsp[-5].value_node), (yyvsp[-2].value_node), new node()); }
#line 1640 "./IW6/parser.cpp"
    break;

  case 31: /* stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON  */
#line 149 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_stmt_wait((yyvsp[-2].value_node)); }
#line 1646 "./IW6/parser.cpp"
    break;

  case 32: /* stmt_wait: WAIT num SEMICOLON  */
#line 150 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_stmt_wait((yyvsp[-1].value_node)); }
#line 1652 "./IW6/parser.cpp"
    break;

  case 33: /* expr: expr_cmp  */
#line 155 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1658 "./IW6/parser.cpp"
    break;

  case 34: /* expr: expr_ternary  */
#line 156 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1664 "./IW6/parser.cpp"
    break;

  case 35: /* expr: expr_binary  */
#line 157 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1670 "./IW6/parser.cpp"
    break;

  case 36: /* expr: expr_unary  */
#line 158 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1676 "./IW6/parser.cpp"
    break;

  case 37: /* expr_assign: object_restricted INC  */
#line 162 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_inc((yyvsp[-1].value_node)); }
#line 1682 "./IW6/parser.cpp"
    break;

  case 38: /* expr_assign: object_restricted DEC  */
#line 163 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_dec((yyvsp[-1].value_node)); }
#line 1688 "./IW6/parser.cpp"
    break;

  case 39: /* expr_assign: object_restricted ASSIGN expr  */
#line 164 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_assign((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1694 "./IW6/parser.cpp"
    break;

  case 40: /* expr_assign: object_restricted ASSIGN_BW_OR expr  */
#line 165 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_bw_or((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1700 "./IW6/parser.cpp"
    break;

  case 41: /* expr_assign: object_restricted ASSIGN_BW_AND expr  */
#line 166 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_bw_and((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1706 "./IW6/parser.cpp"
    break;

  case 42: /* expr_assign: object_restricted ASSIGN_BW_XOR expr  */
#line 167 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_bw_xor((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1712 "./IW6/parser.cpp"
    break;

  case 43: /* expr_assign: object_restricted ASSIGN_LSHIFT expr  */
#line 168 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_shift_left((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1718 "./IW6/parser.cpp"
    break;

  case 44: /* expr_assign: object_restricted ASSIGN_RSHIFT expr  */
#line 169 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_shift_right((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1724 "./IW6/parser.cpp"
    break;

  case 45: /* expr_assign: object_restricted ASSIGN_ADD expr  */
#line 170 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_assign_add((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1730 "./IW6/parser.cpp"
    break;

  case 46: /* expr_assign: object_restricted ASSIGN_SUB expr  */
#line 171 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_assign_sub((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1736 "./IW6/parser.cpp"
    break;

  case 47: /* expr_assign: object_restricted ASSIGN_MULT expr  */
#line 172 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_mult((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1742 "./IW6/parser.cpp"
    break;

  case 48: /* expr_assign: object_restricted ASSIGN_DIV expr  */
#line 173 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_assign_div((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1748 "./IW6/parser.cpp"
    break;

  case 49: /* expr_assign: object_restricted ASSIGN_MOD expr  */
#line 174 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_mod((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1754 "./IW6/parser.cpp"
    break;

  case 50: /* expr_cmp: expr CMP_OR expr  */
#line 178 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_cmp_or((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1760 "./IW6/parser.cpp"
    break;

  case 51: /* expr_cmp: expr CMP_AND expr  */
#line 179 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_cmp_and((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1766 "./IW6/parser.cpp"
    break;

  case 52: /* expr_cmp: expr CMP_EQUAL expr  */
#line 180 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_equal((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1772 "./IW6/parser.cpp"
    break;

  case 53: /* expr_cmp: expr CMP_NOT_EQ expr  */
#line 181 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_not_equal((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1778 "./IW6/parser.cpp"
    break;

  case 54: /* expr_cmp: expr CMP_LESS_EQ expr  */
#line 182 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_less_equal((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1784 "./IW6/parser.cpp"
    break;

  case 55: /* expr_cmp: expr CMP_GREATER_EQ expr  */
#line 183 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_greater_equal((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1790 "./IW6/parser.cpp"
    break;

  case 56: /* expr_cmp: expr CMP_LESS expr  */
#line 184 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_less((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1796 "./IW6/parser.cpp"
    break;

  case 57: /* expr_cmp: expr CMP_GREATER expr  */
#line 185 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_greater((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1802 "./IW6/parser.cpp"
    break;

  case 58: /* expr_ternary: expr_cmp QMARK expr COLON expr  */
#line 189 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_ternary((yyvsp[-4].value_node), (yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1808 "./IW6/parser.cpp"
    break;

  case 59: /* expr_binary: expr BW_OR expr  */
#line 193 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_bw_or((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1814 "./IW6/parser.cpp"
    break;

  case 60: /* expr_binary: expr BW_AND expr  */
#line 194 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_bw_and((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1820 "./IW6/parser.cpp"
    break;

  case 61: /* expr_binary: expr BW_XOR expr  */
#line 195 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_bw_xor((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1826 "./IW6/parser.cpp"
    break;

  case 62: /* expr_binary: expr LSHIFT expr  */
#line 196 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_shift_left((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1832 "./IW6/parser.cpp"
    break;

  case 63: /* expr_binary: expr RSHIFT expr  */
#line 197 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_shift_right((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1838 "./IW6/parser.cpp"
    break;

  case 64: /* expr_binary: expr ADD expr  */
#line 198 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_add((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1844 "./IW6/parser.cpp"
    break;

  case 65: /* expr_binary: expr SUB expr  */
#line 199 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_sub((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1850 "./IW6/parser.cpp"
    break;

  case 66: /* expr_binary: expr MULT expr  */
#line 200 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_mult((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1856 "./IW6/parser.cpp"
    break;

  case 67: /* expr_binary: expr DIV expr  */
#line 201 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_div((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1862 "./IW6/parser.cpp"
    break;

  case 68: /* expr_binary: expr MOD expr  */
#line 202 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_mod((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 1868 "./IW6/parser.cpp"
    break;

  case 69: /* expr_unary: COMPLEMENT expr  */
#line 206 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_complement((yyvsp[0].value_node)); }
#line 1874 "./IW6/parser.cpp"
    break;

  case 70: /* expr_unary: NOT expr  */
#line 207 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_expr_not((yyvsp[0].value_node)); }
#line 1880 "./IW6/parser.cpp"
    break;

  case 71: /* expr_unary: expr_call  */
#line 208 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1886 "./IW6/parser.cpp"
    break;

  case 72: /* expr_unary: expr_call_thread  */
#line 209 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1892 "./IW6/parser.cpp"
    break;

  case 73: /* expr_unary: expr_select  */
#line 210 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1898 "./IW6/parser.cpp"
    break;

  case 74: /* expr_unary: expr_subscribe  */
#line 211 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1904 "./IW6/parser.cpp"
    break;

  case 75: /* expr_unary: expr_func_ref  */
#line 212 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1910 "./IW6/parser.cpp"
    break;

  case 76: /* expr_unary: empty_array  */
#line 213 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1916 "./IW6/parser.cpp"
    break;

  case 77: /* expr_unary: undefined  */
#line 214 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1922 "./IW6/parser.cpp"
    break;

  case 78: /* expr_unary: LPAREN expr COMMA expr COMMA expr RPAREN  */
#line 215 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_vector((yyvsp[-5].value_node), (yyvsp[-3].value_node), (yyvsp[-1].value_node)); }
#line 1928 "./IW6/parser.cpp"
    break;

  case 79: /* expr_unary: vector  */
#line 216 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1934 "./IW6/parser.cpp"
    break;

  case 80: /* expr_unary: num_float  */
#line 217 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1940 "./IW6/parser.cpp"
    break;

  case 81: /* expr_unary: num_integer  */
#line 218 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1946 "./IW6/parser.cpp"
    break;

  case 82: /* expr_unary: string_hash  */
#line 219 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1952 "./IW6/parser.cpp"
    break;

  case 83: /* expr_unary: string_loc  */
#line 220 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1958 "./IW6/parser.cpp"
    break;

  case 84: /* expr_unary: string  */
#line 221 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1964 "./IW6/parser.cpp"
    break;

  case 85: /* expr_unary: identifier  */
#line 222 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1970 "./IW6/parser.cpp"
    break;

  case 86: /* expr_unary: LPAREN expr RPAREN  */
#line 223 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = (yyvsp[-1].value_node); }
#line 1976 "./IW6/parser.cpp"
    break;

  case 87: /* expr_call: expr_func_call  */
#line 227 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_call(new node(), (yyvsp[0].value_node)); }
#line 1982 "./IW6/parser.cpp"
    break;

  case 88: /* expr_call: expr_func_call_ptr  */
#line 228 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_call(new node(), (yyvsp[0].value_node)); }
#line 1988 "./IW6/parser.cpp"
    break;

  case 89: /* expr_call: object expr_func_call  */
#line 229 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_call((yyvsp[-1].value_node), (yyvsp[0].value_node)); }
#line 1994 "./IW6/parser.cpp"
    break;

  case 90: /* expr_call: object expr_func_call_ptr  */
#line 230 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_call((yyvsp[-1].value_node), (yyvsp[0].value_node)); }
#line 2000 "./IW6/parser.cpp"
    break;

  case 91: /* expr_call_thread: THREAD expr_func_call  */
#line 234 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_call_thread(new node(), (yyvsp[0].value_node)); }
#line 2006 "./IW6/parser.cpp"
    break;

  case 92: /* expr_call_thread: THREAD expr_func_call_ptr  */
#line 235 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_call_thread(new node(), (yyvsp[0].value_node)); }
#line 2012 "./IW6/parser.cpp"
    break;

  case 93: /* expr_call_thread: object THREAD expr_func_call  */
#line 236 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_call_thread((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2018 "./IW6/parser.cpp"
    break;

  case 94: /* expr_call_thread: object THREAD expr_func_call_ptr  */
#line 237 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_call_thread((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2024 "./IW6/parser.cpp"
    break;

  case 95: /* expr_func_call: identifier LPAREN expr_arg_list RPAREN  */
#line 242 "iw6.parser.ypp"
                                                                                                        { (yyval.value_node) = new node_expr_func_call(new node(), (yyvsp[-3].value_node), (yyvsp[-1].value_expr_arg_list)); }
#line 2030 "./IW6/parser.cpp"
    break;

  case 96: /* expr_func_call: filepath DOUBLECOLON identifier LPAREN expr_arg_list RPAREN  */
#line 243 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_func_call((yyvsp[-5].value_node), (yyvsp[-3].value_node), (yyvsp[-1].value_expr_arg_list)); }
#line 2036 "./IW6/parser.cpp"
    break;

  case 97: /* expr_func_call: identifier DOUBLECOLON identifier LPAREN expr_arg_list RPAREN  */
#line 244 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_func_call((yyvsp[-5].value_node), (yyvsp[-3].value_node), (yyvsp[-1].value_expr_arg_list)); }
#line 2042 "./IW6/parser.cpp"
    break;

  case 98: /* expr_func_call_ptr: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arg_list RPAREN  */
#line 249 "iw6.parser.ypp"
                                                                               { (yyval.value_node) = new node_expr_func_call_ptr((yyvsp[-5].value_node), (yyvsp[-1].value_expr_arg_list)); }
#line 2048 "./IW6/parser.cpp"
    break;

  case 99: /* expr_arg_list: expr_arg_list COMMA expr  */
#line 253 "iw6.parser.ypp"
                                                                        { (yyval.value_expr_arg_list) = (yyvsp[-2].value_expr_arg_list); (yyval.value_expr_arg_list)->args.push_back((yyvsp[0].value_node)); }
#line 2054 "./IW6/parser.cpp"
    break;

  case 100: /* expr_arg_list: expr  */
#line 254 "iw6.parser.ypp"
                                                                                        { (yyval.value_expr_arg_list) = new node_expr_arg_list(); (yyval.value_expr_arg_list)->args.push_back((yyvsp[0].value_node)); }
#line 2060 "./IW6/parser.cpp"
    break;

  case 101: /* expr_arg_list: %empty  */
#line 255 "iw6.parser.ypp"
                                                                                                { (yyval.value_expr_arg_list) = new node_expr_arg_list(); }
#line 2066 "./IW6/parser.cpp"
    break;

  case 102: /* expr_select: object DOT identifier  */
#line 260 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_select((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2072 "./IW6/parser.cpp"
    break;

  case 103: /* expr_select: level DOT identifier  */
#line 261 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_select((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2078 "./IW6/parser.cpp"
    break;

  case 104: /* expr_subscribe: object LBRACKET expr RBRACKET  */
#line 266 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_subscribe((yyvsp[-3].value_node), (yyvsp[-1].value_node)); }
#line 2084 "./IW6/parser.cpp"
    break;

  case 105: /* expr_subscribe: game LBRACKET expr RBRACKET  */
#line 267 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_subscribe((yyvsp[-3].value_node), (yyvsp[-1].value_node)); }
#line 2090 "./IW6/parser.cpp"
    break;

  case 106: /* expr_func_ref: DOUBLECOLON identifier  */
#line 272 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_func_ref(new node(), (yyvsp[0].value_node)); }
#line 2096 "./IW6/parser.cpp"
    break;

  case 107: /* expr_func_ref: identifier DOUBLECOLON identifier  */
#line 273 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_func_ref((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2102 "./IW6/parser.cpp"
    break;

  case 108: /* expr_func_ref: filepath DOUBLECOLON identifier  */
#line 274 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_func_ref((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2108 "./IW6/parser.cpp"
    break;

  case 109: /* object: expr_call  */
#line 279 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2114 "./IW6/parser.cpp"
    break;

  case 110: /* object: object_restricted  */
#line 280 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2120 "./IW6/parser.cpp"
    break;

  case 111: /* object_restricted: expr_subscribe  */
#line 285 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2126 "./IW6/parser.cpp"
    break;

  case 112: /* object_restricted: expr_select  */
#line 286 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2132 "./IW6/parser.cpp"
    break;

  case 113: /* object_restricted: identifier  */
#line 287 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2138 "./IW6/parser.cpp"
    break;

  case 114: /* level: LEVEL  */
#line 291 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_level(); }
#line 2144 "./IW6/parser.cpp"
    break;

  case 115: /* game: GAME  */
#line 296 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_game(); }
#line 2150 "./IW6/parser.cpp"
    break;

  case 116: /* empty_array: EMPTY_ARRAY  */
#line 300 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_empty_array(); }
#line 2156 "./IW6/parser.cpp"
    break;

  case 117: /* undefined: UNDEFINED  */
#line 304 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_undefined(); }
#line 2162 "./IW6/parser.cpp"
    break;

  case 118: /* vector: LPAREN num COMMA num COMMA num RPAREN  */
#line 308 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_vector((yyvsp[-5].value_node), (yyvsp[-3].value_node), (yyvsp[-1].value_node)); }
#line 2168 "./IW6/parser.cpp"
    break;

  case 119: /* num: num_float  */
#line 312 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2174 "./IW6/parser.cpp"
    break;

  case 120: /* num: num_integer  */
#line 313 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2180 "./IW6/parser.cpp"
    break;

  case 121: /* num_float: FLOAT  */
#line 317 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_num_float((yyvsp[0].value_string)); }
#line 2186 "./IW6/parser.cpp"
    break;

  case 122: /* num_integer: INTEGER  */
#line 321 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_num_integer((yyvsp[0].value_string)); }
#line 2192 "./IW6/parser.cpp"
    break;

  case 123: /* string_hash: STRING_HASH  */
#line 325 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_string_hash((yyvsp[0].value_string)); }
#line 2198 "./IW6/parser.cpp"
    break;

  case 124: /* string_loc: STRING_LOC  */
#line 329 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_string_loc((yyvsp[0].value_string)); }
#line 2204 "./IW6/parser.cpp"
    break;

  case 125: /* string: STRING  */
#line 333 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_string((yyvsp[0].value_string)); }
#line 2210 "./IW6/parser.cpp"
    break;

  case 126: /* identifier: IDENTIFIER  */
#line 337 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_identifier((yyvsp[0].value_string)); }
#line 2216 "./IW6/parser.cpp"
    break;

  case 127: /* filepath: FILEPATH  */
#line 341 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_filepath((yyvsp[0].value_string)); }
#line 2222 "./IW6/parser.cpp"
    break;


#line 2226 "./IW6/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == TOK_YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, astout, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= TOK_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == TOK_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner, astout);
          yychar = TOK_YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner, astout);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, astout, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != TOK_YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner, astout);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner, astout);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 344 "iw6.parser.ypp"


int yyerror(yyscan_t scanner, node **astout, const char *msg)
{
	printf("[compiler]: %s", msg);
	return 0;
}
