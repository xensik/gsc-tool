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
  YYSYMBOL_IFX = 84,                       /* IFX  */
  YYSYMBOL_YYACCEPT = 85,                  /* $accept  */
  YYSYMBOL_root = 86,                      /* root  */
  YYSYMBOL_script = 87,                    /* script  */
  YYSYMBOL_include = 88,                   /* include  */
  YYSYMBOL_using_animtree = 89,            /* using_animtree  */
  YYSYMBOL_function = 90,                  /* function  */
  YYSYMBOL_parameter_list = 91,            /* parameter_list  */
  YYSYMBOL_stmt_block = 92,                /* stmt_block  */
  YYSYMBOL_stmt = 93,                      /* stmt  */
  YYSYMBOL_stmt_call = 94,                 /* stmt_call  */
  YYSYMBOL_stmt_assign = 95,               /* stmt_assign  */
  YYSYMBOL_stmt_endon = 96,                /* stmt_endon  */
  YYSYMBOL_stmt_notify = 97,               /* stmt_notify  */
  YYSYMBOL_stmt_wait = 98,                 /* stmt_wait  */
  YYSYMBOL_stmt_waittill = 99,             /* stmt_waittill  */
  YYSYMBOL_stmt_waittillmatch = 100,       /* stmt_waittillmatch  */
  YYSYMBOL_stmt_waittillframeend = 101,    /* stmt_waittillframeend  */
  YYSYMBOL_stmt_if = 102,                  /* stmt_if  */
  YYSYMBOL_stmt_ifelse = 103,              /* stmt_ifelse  */
  YYSYMBOL_stmt_while = 104,               /* stmt_while  */
  YYSYMBOL_stmt_for = 105,                 /* stmt_for  */
  YYSYMBOL_stmt_foreach = 106,             /* stmt_foreach  */
  YYSYMBOL_stmt_break = 107,               /* stmt_break  */
  YYSYMBOL_stmt_continue = 108,            /* stmt_continue  */
  YYSYMBOL_stmt_return = 109,              /* stmt_return  */
  YYSYMBOL_for_assign = 110,               /* for_assign  */
  YYSYMBOL_for_cond = 111,                 /* for_cond  */
  YYSYMBOL_expr = 112,                     /* expr  */
  YYSYMBOL_expr_assign = 113,              /* expr_assign  */
  YYSYMBOL_expr_cmp = 114,                 /* expr_cmp  */
  YYSYMBOL_expr_ternary = 115,             /* expr_ternary  */
  YYSYMBOL_expr_binary = 116,              /* expr_binary  */
  YYSYMBOL_expr_unary = 117,               /* expr_unary  */
  YYSYMBOL_expr_call = 118,                /* expr_call  */
  YYSYMBOL_expr_call_thread = 119,         /* expr_call_thread  */
  YYSYMBOL_expr_func_call = 120,           /* expr_func_call  */
  YYSYMBOL_expr_func_call_ptr = 121,       /* expr_func_call_ptr  */
  YYSYMBOL_expr_arg_list = 122,            /* expr_arg_list  */
  YYSYMBOL_expr_select = 123,              /* expr_select  */
  YYSYMBOL_expr_subscribe = 124,           /* expr_subscribe  */
  YYSYMBOL_expr_func_ref = 125,            /* expr_func_ref  */
  YYSYMBOL_object = 126,                   /* object  */
  YYSYMBOL_object_restricted = 127,        /* object_restricted  */
  YYSYMBOL_size = 128,                     /* size  */
  YYSYMBOL_false = 129,                    /* false  */
  YYSYMBOL_true = 130,                     /* true  */
  YYSYMBOL_level = 131,                    /* level  */
  YYSYMBOL_game = 132,                     /* game  */
  YYSYMBOL_empty_array = 133,              /* empty_array  */
  YYSYMBOL_undefined = 134,                /* undefined  */
  YYSYMBOL_vector = 135,                   /* vector  */
  YYSYMBOL_num = 136,                      /* num  */
  YYSYMBOL_num_float = 137,                /* num_float  */
  YYSYMBOL_num_integer = 138,              /* num_integer  */
  YYSYMBOL_string_hash = 139,              /* string_hash  */
  YYSYMBOL_string_loc = 140,               /* string_loc  */
  YYSYMBOL_string = 141,                   /* string  */
  YYSYMBOL_identifier = 142,               /* identifier  */
  YYSYMBOL_filepath = 143                  /* filepath  */
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
typedef yytype_int16 yy_state_t;

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
#define YYLAST   1729

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  330

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   339


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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    86,    86,    87,    91,    92,    93,    94,    95,    96,
     100,   101,   105,   109,   113,   114,   115,   119,   120,   121,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   145,   146,   150,   154,
     158,   159,   163,   164,   168,   170,   175,   180,   185,   187,
     192,   194,   196,   198,   203,   205,   210,   212,   217,   219,
     224,   227,   231,   232,   236,   237,   241,   242,   247,   248,
     249,   250,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   270,   271,   272,   273,   274,
     275,   276,   277,   281,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   318,   319,   320,   321,   325,   326,   327,   328,   333,
     334,   335,   340,   344,   345,   346,   351,   352,   357,   362,
     363,   364,   369,   370,   375,   376,   377,   378,   379,   383,
     387,   391,   395,   399,   403,   407,   411,   415,   416,   417,
     418,   422,   426,   430,   434,   438,   442,   446
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
  "STRING_LOC", "STRING_HASH", "FLOAT", "INTEGER", "IFX", "$accept",
  "root", "script", "include", "using_animtree", "function",
  "parameter_list", "stmt_block", "stmt", "stmt_call", "stmt_assign",
  "stmt_endon", "stmt_notify", "stmt_wait", "stmt_waittill",
  "stmt_waittillmatch", "stmt_waittillframeend", "stmt_if", "stmt_ifelse",
  "stmt_while", "stmt_for", "stmt_foreach", "stmt_break", "stmt_continue",
  "stmt_return", "for_assign", "for_cond", "expr", "expr_assign",
  "expr_cmp", "expr_ternary", "expr_binary", "expr_unary", "expr_call",
  "expr_call_thread", "expr_func_call", "expr_func_call_ptr",
  "expr_arg_list", "expr_select", "expr_subscribe", "expr_func_ref",
  "object", "object_restricted", "size", "false", "true", "level", "game",
  "empty_array", "undefined", "vector", "num", "num_float", "num_integer",
  "string_hash", "string_loc", "string", "identifier", "filepath", YY_NULLPTR
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
     335,   336,   337,   338,   339
};
#endif

#define YYPACT_NINF (-248)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-147)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,   -45,    -9,  -248,    46,     9,  -248,  -248,  -248,    16,
    -248,    14,    17,    -4,  -248,  -248,  -248,  -248,   -10,  -248,
    -248,  -248,    50,   -14,  -248,    61,    79,   -10,  -248,   922,
    -248,    89,    82,   102,   104,   106,   103,   936,    62,   -11,
     119,  -248,  -248,   108,    49,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,   120,   126,   127,  -248,  -248,  -248,  -248,     3,
    1071,  -248,  -248,   -18,   115,   954,  -248,    65,   954,   954,
    -248,  -248,  -248,  -248,  -248,   954,   -10,  -248,   954,   954,
    -248,  -248,  -248,  -248,  1624,   123,  -248,  -248,  -248,    11,
    -248,   124,   175,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,    80,   116,  -248,  -248,
     -18,   954,   138,  -248,   954,  -248,  -248,  -248,  -248,  -248,
      62,  1021,   -20,  -248,  -248,   149,   151,   154,   162,  -248,
    -248,   954,   954,   954,   954,   954,   954,   954,   954,   954,
     954,   954,   954,   -10,   -10,  1221,   157,  -248,  -248,   173,
     299,  1015,  1252,  1106,   158,  -248,  1655,  1655,  -248,   954,
     954,   954,   954,   954,   954,   954,   954,   954,   954,   954,
     954,   954,   954,   954,   954,   954,   954,   954,   -10,   -10,
    1283,  -248,  1445,  -248,  -248,  1021,  1483,  -248,  -248,  -248,
     954,   954,   954,   954,  1655,  1655,  1655,  1655,  1655,  1655,
    1655,  1655,  1655,  1655,  1655,  1655,    -8,   171,   172,   161,
     954,   954,   655,  -248,   954,    10,  1655,  1655,  1655,  1655,
    1655,  1655,  1655,  1655,  1655,  1655,  1655,  1655,  1655,  1655,
    1655,  1655,  1655,  1655,  1591,   171,   172,   163,   169,  -248,
    1148,  1520,  1314,  1190,  -248,   954,   954,   954,   922,   203,
     174,  1655,    48,  1345,   922,  -248,  1557,   177,   954,  -248,
     181,   176,   954,   954,   179,   183,   954,  1655,    -7,     7,
      93,   682,    65,   708,   740,   954,    10,  1655,   954,  -248,
      19,  1376,  -248,  -248,   113,  -248,  -248,   210,   922,  -248,
     190,   922,  -248,  -248,  1407,   193,   114,   186,   187,   188,
     766,   792,   818,   844,  -248,  -248,  -248,  -248,  -248,  -248,
     922,  -248,  -248,   922,  -248,  -248,   870,   896,  -248,  -248
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,   166,     0,     2,     7,     8,     9,     0,
     167,     0,     0,     0,     1,     4,     5,     6,    16,    11,
      10,   165,     0,     0,    15,     0,     0,     0,    12,    19,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   153,   152,     0,     0,    18,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,     0,   142,     0,   121,   122,   145,   144,     0,
     143,   147,   148,   146,     0,     0,    60,    65,     0,     0,
      61,   155,   151,   150,   154,     0,     0,    63,     0,     0,
     164,   163,   161,   162,     0,    68,    69,    70,    71,   106,
     107,   108,   109,   110,   143,   159,   160,   111,   112,   114,
     115,   157,   158,   116,   117,   118,   119,     0,   125,   126,
       0,     0,     0,    47,     0,    13,    17,    38,    36,    37,
       0,     0,     0,   123,   124,     0,     0,     0,     0,    72,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,     0,     0,     0,     0,    64,   142,     0,
     143,     0,     0,     0,   115,   139,   105,   104,    62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    43,     0,   127,   128,     0,     0,   149,   137,   136,
       0,     0,     0,     0,    74,    80,    81,    82,    83,    84,
      75,    76,    77,    78,    79,   134,     0,     0,     0,     0,
      67,     0,     0,   120,     0,     0,   103,    97,    98,    85,
      86,    87,    88,    89,    90,    91,    92,    94,    95,    96,
      99,   100,   101,   102,     0,   140,   141,     0,     0,   138,
       0,     0,     0,     0,   129,     0,   135,   135,    19,    49,
       0,     0,    68,     0,    19,    55,     0,     0,     0,    42,
       0,     0,   135,     0,     0,     0,   135,   133,     0,     0,
       0,     0,    65,     0,     0,     0,     0,    93,   135,    45,
       0,     0,    39,    41,     0,   131,   130,    48,    19,    53,
       0,    19,    59,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   156,   132,    44,    46,    40,
      19,    52,    51,    19,    57,    58,     0,     0,    50,    56
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -248,  -248,  -248,   226,   227,   229,  -248,  -247,   -35,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,   -46,  -248,   462,   -75,    20,
    -248,  -248,  -248,    71,   265,   -34,   -28,  -139,   121,   156,
    -248,   -74,   191,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,   -32,  -248,  -248,  -248,  -248,   224,     0,     5
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    23,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,   156,   260,   215,    62,    95,
      96,    97,    98,    99,   100,    65,    66,   216,   101,   102,
     103,    69,   104,   198,   105,   106,    71,    72,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       9,    11,   157,   159,   118,     9,    12,   122,   197,   126,
     119,   280,     1,     2,   152,    82,    83,   284,    24,    26,
     130,   121,   153,    13,    27,   254,   295,    30,  -142,    73,
     255,   255,    10,     3,    74,   133,    82,    83,   120,   131,
     296,   134,   132,    74,    73,   255,    14,  -142,    18,    74,
    -142,   311,   307,   164,   313,    31,    19,   255,     3,    20,
      32,    33,    34,    35,    36,    37,    38,    39,     3,   120,
      40,    92,    93,   326,    74,    21,   327,    73,    41,    42,
      10,     3,    74,    25,   125,    43,   165,     3,  -142,  -142,
     -66,   187,    92,    93,    41,    42,   193,  -146,    43,    31,
      63,    43,   194,    28,    32,    33,    34,    35,    36,    37,
      38,    39,   152,    29,    40,    63,  -146,   278,   279,  -146,
     188,    75,    41,    42,    76,   133,    10,     3,   297,    43,
     120,   134,   199,   290,    77,    74,    78,   294,    79,    10,
       3,  -145,    10,     3,   124,    80,   309,   316,   158,   306,
      67,   255,   255,   217,   218,   154,   189,  -146,  -146,   120,
    -145,   123,   127,  -145,    74,    67,   187,    31,   128,   129,
      10,     3,    32,    33,    34,    35,    36,    37,    38,    39,
     191,   200,    40,   201,   259,    68,   202,   265,   245,   246,
      41,    42,  -144,   267,   203,   258,   225,    43,    67,   220,
      68,  -145,  -145,   256,   257,   269,   270,   157,   159,   131,
     281,  -144,   132,   288,  -144,   286,   282,   310,   289,    73,
      70,   292,    73,   312,    74,   293,   315,    74,   317,   318,
     319,    15,    16,    68,    17,    70,   300,    22,    10,     3,
     262,     0,     0,     0,     0,   126,   299,     0,   302,   126,
      10,     3,  -144,  -144,   305,     0,     0,     0,    73,     0,
       0,     0,     0,    74,    73,     0,     0,     0,   160,    74,
       0,     0,     0,     0,     0,   321,   126,   324,   126,     0,
      73,    73,    73,    73,    73,    74,    74,    74,    74,    74,
      63,   126,   126,    63,    64,     0,     0,     0,    73,     0,
       0,    73,     0,    74,     0,     0,    74,     0,     0,    64,
      73,    73,    73,    73,     0,    74,    74,    74,    74,     0,
      73,     0,     0,    73,     0,    74,    73,    73,    74,    63,
       0,    74,    74,     0,     0,    63,     0,     0,     0,     0,
      67,     0,     0,    67,   139,   140,     0,     0,     0,     0,
       0,    63,    63,   158,    63,    63,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,     0,     0,    63,
       0,     0,    63,     0,     0,    68,     0,     0,    68,    67,
       0,    63,    63,    63,    63,    67,     0,     0,     0,     0,
       0,    63,     0,     0,    63,     0,     0,    63,    63,     0,
       0,    67,    67,    67,    67,    67,     0,     0,     0,     0,
      70,     0,     0,    70,    68,     0,     0,     0,     0,    67,
      68,     0,    67,     0,     0,     0,     0,     0,     0,     0,
       0,    67,    67,    67,    67,     0,    68,    68,    68,    68,
      68,    67,     0,     0,    67,     0,     0,    67,    67,    70,
       0,     0,     0,     0,    68,    70,     0,    68,     0,     0,
       0,     0,     0,     0,     0,     0,    68,    68,    68,    68,
       0,    70,    70,   160,    70,    70,    68,     0,     0,    68,
       0,     0,    68,    68,    64,     0,     0,    64,     0,    70,
       0,     0,    70,     0,     0,     0,     0,     0,     0,    94,
       0,    70,    70,    70,    70,     0,     0,     0,     0,     0,
       0,    70,     0,     0,    70,     0,     0,    70,    70,     0,
       0,     0,     0,    64,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,     0,     0,   155,     0,     0,
     161,   162,     0,     0,     0,    64,    64,   163,    64,    64,
     166,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,     0,    64,     0,     0,     0,
       0,     0,     0,     0,     0,    64,    64,    64,    64,     0,
       0,     0,     0,   190,     0,    64,   192,     0,    64,     0,
       0,    64,    64,   196,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
       0,     0,     0,     0,     0,     0,     0,   192,     0,     0,
       0,    31,   250,   251,   252,   253,    32,    33,    34,    35,
      36,    37,    38,    39,     0,     0,    40,     0,     0,     0,
       0,     0,   261,   263,    41,    42,   266,     0,    31,   264,
       0,    43,     0,    32,    33,    34,    35,    36,    37,    38,
      39,     0,     0,    40,     0,     0,     0,     0,     0,     0,
       0,    41,    42,     0,    31,     0,   298,   277,    43,    32,
      33,    34,    35,    36,    37,    38,    39,     0,     0,    40,
     287,     0,    10,     3,     0,   291,     0,    41,    42,     0,
       0,     0,     0,   301,    43,     0,    31,   304,     0,     0,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    10,
       3,    40,     0,     0,     0,     0,     0,     0,     0,    41,
      42,     0,    31,     0,     0,   303,    43,    32,    33,    34,
      35,    36,    37,    38,    39,    10,     3,    40,     0,     0,
       0,     0,     0,     0,     0,    41,    42,     0,    31,     0,
     320,     0,    43,    32,    33,    34,    35,    36,    37,    38,
      39,     0,     0,    40,     0,     0,     0,    10,     3,     0,
       0,    41,    42,     0,    31,     0,     0,   322,    43,    32,
      33,    34,    35,    36,    37,    38,    39,     0,     0,    40,
       0,     0,     0,    10,     3,     0,     0,    41,    42,     0,
      31,     0,   323,     0,    43,    32,    33,    34,    35,    36,
      37,    38,    39,     0,     0,    40,     0,     0,     0,    10,
       3,     0,     0,    41,    42,     0,    31,     0,     0,   325,
      43,    32,    33,    34,    35,    36,    37,    38,    39,     0,
       0,    40,     0,     0,     0,    10,     3,     0,     0,    41,
      42,     0,    31,     0,     0,   328,    43,    32,    33,    34,
      35,    36,    37,    38,    39,     0,     0,    40,     0,     0,
       0,    10,     3,     0,     0,    41,    42,     0,    31,     0,
       0,   329,    43,    32,    33,    34,    35,    36,    37,    38,
      39,     0,     0,    40,     0,     0,     0,    10,     3,     0,
       0,    41,    42,    38,     0,     0,     0,     0,    43,     0,
       0,    81,    82,    83,     0,    41,    42,    84,    85,     0,
       0,    38,    43,    10,     3,     0,    86,     0,    87,    81,
      82,    83,     0,    41,    42,    84,    85,     0,     0,     0,
      43,     0,     0,     0,    86,     0,     0,     0,     0,    10,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,    89,    10,     3,    21,    90,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    88,
      89,    10,     3,    21,    90,    91,    92,    93,    38,   221,
       0,     0,     0,     0,     0,     0,    81,    82,    83,     0,
      41,    42,    84,    85,     0,     0,     0,   195,     0,   169,
       0,    86,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     135,   136,     0,   137,   138,     0,    88,    89,    10,     3,
      21,    90,    91,    92,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   139,   140,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   223,
       0,     0,     0,     0,   224,     0,     0,     0,     0,     0,
     169,     0,     0,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,   182,   183,   184,   185,
     186,   271,     0,     0,     0,     0,   272,     0,     0,     0,
       0,     0,   169,     0,     0,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,   182,   183,
     184,   185,   186,   275,     0,     0,     0,     0,   276,     0,
       0,     0,     0,     0,   169,     0,     0,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,     0,     0,     0,
       0,     0,     0,     0,   219,     0,     0,     0,   180,   181,
     182,   183,   184,   185,   186,   169,     0,     0,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,     0,     0,
       0,     0,     0,     0,     0,   222,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   169,     0,     0,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,     0,
       0,     0,     0,     0,     0,     0,   247,     0,     0,     0,
     180,   181,   182,   183,   184,   185,   186,   169,     0,     0,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
       0,     0,     0,     0,     0,     0,     0,   274,     0,     0,
       0,   180,   181,   182,   183,   184,   185,   186,   169,     0,
       0,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,     0,     0,     0,     0,     0,     0,     0,   283,     0,
       0,     0,   180,   181,   182,   183,   184,   185,   186,   169,
       0,     0,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,   308,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     169,     0,     0,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
     314,     0,     0,     0,   180,   181,   182,   183,   184,   185,
     186,   169,     0,     0,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,   186,   248,     0,     0,     0,     0,     0,     0,   169,
       0,     0,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     249,     0,     0,     0,     0,     0,     0,   169,     0,     0,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,   182,   183,   184,   185,   186,   273,     0,
       0,     0,     0,     0,   169,     0,     0,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
     182,   183,   184,   185,   186,   285,     0,     0,     0,     0,
       0,   169,     0,     0,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,   182,   183,   184,
     185,   186,   268,     0,     0,   169,     0,     0,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,   182,   183,   184,   185,   186,   168,     0,   169,     0,
       0,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,   182,   183,   184,   185,   186,   169,
       0,     0,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186
};

static const yytype_int16 yycheck[] =
{
       0,     1,    77,    77,    38,     5,     1,    39,    28,    44,
      38,   258,     3,     4,    32,    26,    27,   264,    18,    33,
      17,    32,    40,    32,    38,    33,    33,    27,    17,    29,
      38,    38,    77,    78,    29,    69,    26,    27,    38,    36,
      33,    69,    39,    38,    44,    38,     0,    36,    32,    44,
      39,   298,    33,    85,   301,     6,    42,    38,    78,    42,
      11,    12,    13,    14,    15,    16,    17,    18,    78,    69,
      21,    82,    83,   320,    69,    79,   323,    77,    29,    30,
      77,    78,    77,    33,    35,    36,    86,    78,    77,    78,
      42,    43,    82,    83,    29,    30,   130,    17,    36,     6,
      29,    36,   130,    42,    11,    12,    13,    14,    15,    16,
      17,    18,    32,    34,    21,    44,    36,   256,   257,    39,
      40,    32,    29,    30,    42,   159,    77,    78,    35,    36,
     130,   159,   132,   272,    32,   130,    32,   276,    32,    77,
      78,    17,    77,    78,    36,    42,    33,    33,    77,   288,
      29,    38,    38,   153,   154,    40,    40,    77,    78,   159,
      36,    42,    42,    39,   159,    44,    43,     6,    42,    42,
      77,    78,    11,    12,    13,    14,    15,    16,    17,    18,
      42,    32,    21,    32,   219,    29,    32,   222,   188,   189,
      29,    30,    17,   225,    32,    34,    38,    36,    77,    42,
      44,    77,    78,    32,    32,    42,    37,   282,   282,    36,
       7,    36,    39,    32,    39,    38,    42,     7,    42,   219,
      29,    42,   222,    33,   219,    42,    33,   222,    42,    42,
      42,     5,     5,    77,     5,    44,   282,    13,    77,    78,
     220,    -1,    -1,    -1,    -1,   280,   281,    -1,   283,   284,
      77,    78,    77,    78,   286,    -1,    -1,    -1,   258,    -1,
      -1,    -1,    -1,   258,   264,    -1,    -1,    -1,    77,   264,
      -1,    -1,    -1,    -1,    -1,   310,   311,   312,   313,    -1,
     280,   281,   282,   283,   284,   280,   281,   282,   283,   284,
     219,   326,   327,   222,    29,    -1,    -1,    -1,   298,    -1,
      -1,   301,    -1,   298,    -1,    -1,   301,    -1,    -1,    44,
     310,   311,   312,   313,    -1,   310,   311,   312,   313,    -1,
     320,    -1,    -1,   323,    -1,   320,   326,   327,   323,   258,
      -1,   326,   327,    -1,    -1,   264,    -1,    -1,    -1,    -1,
     219,    -1,    -1,   222,    45,    46,    -1,    -1,    -1,    -1,
      -1,   280,   281,   282,   283,   284,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    -1,   298,
      -1,    -1,   301,    -1,    -1,   219,    -1,    -1,   222,   258,
      -1,   310,   311,   312,   313,   264,    -1,    -1,    -1,    -1,
      -1,   320,    -1,    -1,   323,    -1,    -1,   326,   327,    -1,
      -1,   280,   281,   282,   283,   284,    -1,    -1,    -1,    -1,
     219,    -1,    -1,   222,   258,    -1,    -1,    -1,    -1,   298,
     264,    -1,   301,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   310,   311,   312,   313,    -1,   280,   281,   282,   283,
     284,   320,    -1,    -1,   323,    -1,    -1,   326,   327,   258,
      -1,    -1,    -1,    -1,   298,   264,    -1,   301,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   310,   311,   312,   313,
      -1,   280,   281,   282,   283,   284,   320,    -1,    -1,   323,
      -1,    -1,   326,   327,   219,    -1,    -1,   222,    -1,   298,
      -1,    -1,   301,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,   310,   311,   312,   313,    -1,    -1,    -1,    -1,    -1,
      -1,   320,    -1,    -1,   323,    -1,    -1,   326,   327,    -1,
      -1,    -1,    -1,   258,    -1,    -1,    -1,    -1,    -1,   264,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,
      78,    79,    -1,    -1,    -1,   280,   281,    85,   283,   284,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   298,    -1,    -1,   301,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   310,   311,   312,   313,    -1,
      -1,    -1,    -1,   121,    -1,   320,   124,    -1,   323,    -1,
      -1,   326,   327,   131,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   195,    -1,    -1,
      -1,     6,   200,   201,   202,   203,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,   220,   221,    29,    30,   224,    -1,     6,    34,
      -1,    36,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    30,    -1,     6,    -1,    34,   255,    36,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
     268,    -1,    77,    78,    -1,   273,    -1,    29,    30,    -1,
      -1,    -1,    -1,    35,    36,    -1,     6,   285,    -1,    -1,
      -1,    11,    12,    13,    14,    15,    16,    17,    18,    77,
      78,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    -1,     6,    -1,    -1,    35,    36,    11,    12,    13,
      14,    15,    16,    17,    18,    77,    78,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    -1,     6,    -1,
      34,    -1,    36,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    -1,    77,    78,    -1,
      -1,    29,    30,    -1,     6,    -1,    -1,    35,    36,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      -1,    -1,    -1,    77,    78,    -1,    -1,    29,    30,    -1,
       6,    -1,    34,    -1,    36,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    21,    -1,    -1,    -1,    77,
      78,    -1,    -1,    29,    30,    -1,     6,    -1,    -1,    35,
      36,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      -1,    21,    -1,    -1,    -1,    77,    78,    -1,    -1,    29,
      30,    -1,     6,    -1,    -1,    35,    36,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
      -1,    77,    78,    -1,    -1,    29,    30,    -1,     6,    -1,
      -1,    35,    36,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    -1,    77,    78,    -1,
      -1,    29,    30,    17,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    25,    26,    27,    -1,    29,    30,    31,    32,    -1,
      -1,    17,    36,    77,    78,    -1,    40,    -1,    42,    25,
      26,    27,    -1,    29,    30,    31,    32,    -1,    -1,    -1,
      36,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    77,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    17,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,    -1,
      29,    30,    31,    32,    -1,    -1,    -1,    36,    -1,    44,
      -1,    40,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      19,    20,    -1,    22,    23,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    33,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    33,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    44,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    44,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      44,    -1,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    44,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    37,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    38,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    38,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    41,    -1,    -1,    44,    -1,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    42,    -1,    44,    -1,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    44,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    78,    86,    87,    88,    89,    90,   142,
      77,   142,   143,    32,     0,    88,    89,    90,    32,    42,
      42,    79,   141,    91,   142,    33,    33,    38,    42,    34,
     142,     6,    11,    12,    13,    14,    15,    16,    17,    18,
      21,    29,    30,    36,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   113,   118,   119,   120,   121,   123,   124,   126,
     127,   131,   132,   142,   143,    32,    42,    32,    32,    32,
      42,    25,    26,    27,    31,    32,    40,    42,    75,    76,
      80,    81,    82,    83,   112,   114,   115,   116,   117,   118,
     119,   123,   124,   125,   127,   129,   130,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   120,   121,
     142,    32,   136,    42,    36,    35,    93,    42,    42,    42,
      17,    36,    39,   120,   121,    19,    20,    22,    23,    45,
      46,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    32,    40,    40,   112,   110,   113,   118,   126,
     127,   112,   112,   112,   136,   142,   112,   112,    42,    44,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      68,    69,    70,    71,    72,    73,    74,    43,    40,    40,
     112,    42,   112,   120,   121,    36,   112,    28,   128,   142,
      32,    32,    32,    32,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   122,   142,   142,    33,
      42,    24,    33,    33,    38,    38,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   142,   142,    33,    37,    37,
     112,   112,   112,   112,    33,    38,    32,    32,    34,    93,
     111,   112,   114,   112,    34,    93,   112,   136,    41,    42,
      37,    33,    38,    38,    33,    33,    38,   112,   122,   122,
      92,     7,    42,    33,    92,    38,    38,   112,    32,    42,
     122,   112,    42,    42,   122,    33,    33,    35,    34,    93,
     110,    35,    93,    35,   112,   136,   122,    33,    33,    33,
       7,    92,    33,    92,    33,    33,    33,    42,    42,    42,
      34,    93,    35,    34,    93,    35,    92,    92,    35,    35
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    86,    87,    87,    87,    87,    87,    87,
      88,    88,    89,    90,    91,    91,    91,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    94,    94,    95,    96,
      97,    97,    98,    98,    99,    99,   100,   101,   102,   102,
     103,   103,   103,   103,   104,   104,   105,   105,   106,   106,
     107,   108,   109,   109,   110,   110,   111,   111,   112,   112,
     112,   112,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   118,   118,   119,   119,   119,   119,   120,
     120,   120,   121,   122,   122,   122,   123,   123,   124,   125,
     125,   125,   126,   126,   127,   127,   127,   127,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   136,   136,
     136,   137,   138,   139,   140,   141,   142,   143
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     1,     1,     1,
       3,     3,     5,     7,     3,     1,     0,     2,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     6,
       8,     6,     5,     3,     8,     6,     8,     2,     7,     5,
      11,     9,     9,     7,     7,     5,    11,     9,     9,     7,
       2,     2,     3,     2,     1,     0,     1,     0,     1,     1,
       1,     1,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     7,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     2,     2,     2,     2,     3,     3,     4,
       6,     6,     8,     3,     1,     0,     3,     3,     4,     2,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     7,     1,     1,     1,
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
#line 86 "iw6.parser.ypp"
                                                                                { *astout = (yyvsp[0].value_script); }
#line 1738 "./IW6/parser.cpp"
    break;

  case 3: /* root: %empty  */
#line 87 "iw6.parser.ypp"
                                                                                                { *astout = new node(); }
#line 1744 "./IW6/parser.cpp"
    break;

  case 4: /* script: script include  */
#line 91 "iw6.parser.ypp"
                                                                                { (yyval.value_script) = (yyvsp[-1].value_script); (yyval.value_script)->childs.push_back((yyvsp[0].value_node)); }
#line 1750 "./IW6/parser.cpp"
    break;

  case 5: /* script: script using_animtree  */
#line 92 "iw6.parser.ypp"
                                                                        { (yyval.value_script) = (yyvsp[-1].value_script); (yyval.value_script)->childs.push_back((yyvsp[0].value_node)); }
#line 1756 "./IW6/parser.cpp"
    break;

  case 6: /* script: script function  */
#line 93 "iw6.parser.ypp"
                                                                                { (yyval.value_script) = (yyvsp[-1].value_script); (yyval.value_script)->childs.push_back((yyvsp[0].value_node)); }
#line 1762 "./IW6/parser.cpp"
    break;

  case 7: /* script: include  */
#line 94 "iw6.parser.ypp"
                                                                                        { (yyval.value_script) = new node_script(); (yyval.value_script)->childs.push_back((yyvsp[0].value_node));}
#line 1768 "./IW6/parser.cpp"
    break;

  case 8: /* script: using_animtree  */
#line 95 "iw6.parser.ypp"
                                                                                { (yyval.value_script) = new node_script(); (yyval.value_script)->childs.push_back((yyvsp[0].value_node));}
#line 1774 "./IW6/parser.cpp"
    break;

  case 9: /* script: function  */
#line 96 "iw6.parser.ypp"
                                                                                        { (yyval.value_script) = new node_script(); (yyval.value_script)->childs.push_back((yyvsp[0].value_node));}
#line 1780 "./IW6/parser.cpp"
    break;

  case 10: /* include: INCLUDE filepath SEMICOLON  */
#line 100 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_include((yyvsp[-1].value_node)); }
#line 1786 "./IW6/parser.cpp"
    break;

  case 11: /* include: INCLUDE identifier SEMICOLON  */
#line 101 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_include((yyvsp[-1].value_node)); }
#line 1792 "./IW6/parser.cpp"
    break;

  case 12: /* using_animtree: USING_ANIMTREE LPAREN string RPAREN SEMICOLON  */
#line 105 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_using_animtree((yyvsp[-2].value_node)); }
#line 1798 "./IW6/parser.cpp"
    break;

  case 13: /* function: identifier LPAREN parameter_list RPAREN LBRACE stmt_block RBRACE  */
#line 109 "iw6.parser.ypp"
                                                                           { (yyval.value_node) = new node_function((yyvsp[-6].value_node), (yyvsp[-4].value_parameter_list), (yyvsp[-1].value_statement_block)); }
#line 1804 "./IW6/parser.cpp"
    break;

  case 14: /* parameter_list: parameter_list COMMA identifier  */
#line 113 "iw6.parser.ypp"
                                                                { (yyval.value_parameter_list) = (yyvsp[-2].value_parameter_list); (yyval.value_parameter_list)->params.push_back((yyvsp[0].value_node)); }
#line 1810 "./IW6/parser.cpp"
    break;

  case 15: /* parameter_list: identifier  */
#line 114 "iw6.parser.ypp"
                                                                                { (yyval.value_parameter_list) = new node_parameter_list(); (yyval.value_parameter_list)->params.push_back((yyvsp[0].value_node)); }
#line 1816 "./IW6/parser.cpp"
    break;

  case 16: /* parameter_list: %empty  */
#line 115 "iw6.parser.ypp"
                                                                                                { (yyval.value_parameter_list) = new node_parameter_list(); }
#line 1822 "./IW6/parser.cpp"
    break;

  case 17: /* stmt_block: stmt_block stmt  */
#line 119 "iw6.parser.ypp"
                                                                                { (yyval.value_statement_block) = (yyvsp[-1].value_statement_block); (yyval.value_statement_block)->stmts.push_back((yyvsp[0].value_node)); }
#line 1828 "./IW6/parser.cpp"
    break;

  case 18: /* stmt_block: stmt  */
#line 120 "iw6.parser.ypp"
                                                                                        {(yyval.value_statement_block) = new node_stmt_block(); (yyval.value_statement_block)->stmts.push_back((yyvsp[0].value_node)); }
#line 1834 "./IW6/parser.cpp"
    break;

  case 19: /* stmt_block: %empty  */
#line 121 "iw6.parser.ypp"
                                                                                                { (yyval.value_statement_block) = new node_stmt_block(); }
#line 1840 "./IW6/parser.cpp"
    break;

  case 20: /* stmt: stmt_call  */
#line 126 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1846 "./IW6/parser.cpp"
    break;

  case 21: /* stmt: stmt_assign  */
#line 127 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1852 "./IW6/parser.cpp"
    break;

  case 22: /* stmt: stmt_endon  */
#line 128 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1858 "./IW6/parser.cpp"
    break;

  case 23: /* stmt: stmt_notify  */
#line 129 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1864 "./IW6/parser.cpp"
    break;

  case 24: /* stmt: stmt_wait  */
#line 130 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1870 "./IW6/parser.cpp"
    break;

  case 25: /* stmt: stmt_waittill  */
#line 131 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1876 "./IW6/parser.cpp"
    break;

  case 26: /* stmt: stmt_waittillmatch  */
#line 132 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1882 "./IW6/parser.cpp"
    break;

  case 27: /* stmt: stmt_waittillframeend  */
#line 133 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1888 "./IW6/parser.cpp"
    break;

  case 28: /* stmt: stmt_if  */
#line 134 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1894 "./IW6/parser.cpp"
    break;

  case 29: /* stmt: stmt_ifelse  */
#line 135 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1900 "./IW6/parser.cpp"
    break;

  case 30: /* stmt: stmt_while  */
#line 136 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1906 "./IW6/parser.cpp"
    break;

  case 31: /* stmt: stmt_for  */
#line 137 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1912 "./IW6/parser.cpp"
    break;

  case 32: /* stmt: stmt_foreach  */
#line 138 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1918 "./IW6/parser.cpp"
    break;

  case 33: /* stmt: stmt_break  */
#line 139 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1924 "./IW6/parser.cpp"
    break;

  case 34: /* stmt: stmt_continue  */
#line 140 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1930 "./IW6/parser.cpp"
    break;

  case 35: /* stmt: stmt_return  */
#line 141 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 1936 "./IW6/parser.cpp"
    break;

  case 36: /* stmt_call: expr_call SEMICOLON  */
#line 145 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_stmt_call((yyvsp[-1].value_node)); }
#line 1942 "./IW6/parser.cpp"
    break;

  case 37: /* stmt_call: expr_call_thread SEMICOLON  */
#line 146 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_stmt_call((yyvsp[-1].value_node)); }
#line 1948 "./IW6/parser.cpp"
    break;

  case 38: /* stmt_assign: expr_assign SEMICOLON  */
#line 150 "iw6.parser.ypp"
                                { (yyval.value_node) = new node_stmt_assign((yyvsp[-1].value_node)); }
#line 1954 "./IW6/parser.cpp"
    break;

  case 39: /* stmt_endon: object_restricted ENDON LPAREN expr RPAREN SEMICOLON  */
#line 154 "iw6.parser.ypp"
                                                               { (yyval.value_node) = new node_stmt_endon((yyvsp[-5].value_node), (yyvsp[-2].value_node)); }
#line 1960 "./IW6/parser.cpp"
    break;

  case 40: /* stmt_notify: object_restricted NOTIFY LPAREN expr COMMA expr_arg_list RPAREN SEMICOLON  */
#line 158 "iw6.parser.ypp"
                                                                                    { (yyval.value_node) = new node_stmt_notify((yyvsp[-7].value_node), (yyvsp[-4].value_node), (yyvsp[-2].value_expr_arg_list)); }
#line 1966 "./IW6/parser.cpp"
    break;

  case 41: /* stmt_notify: object_restricted NOTIFY LPAREN expr RPAREN SEMICOLON  */
#line 159 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_stmt_notify((yyvsp[-5].value_node), (yyvsp[-2].value_node), new node()); }
#line 1972 "./IW6/parser.cpp"
    break;

  case 42: /* stmt_wait: WAIT LPAREN expr RPAREN SEMICOLON  */
#line 163 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_stmt_wait((yyvsp[-2].value_node)); }
#line 1978 "./IW6/parser.cpp"
    break;

  case 43: /* stmt_wait: WAIT num SEMICOLON  */
#line 164 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_stmt_wait((yyvsp[-1].value_node)); }
#line 1984 "./IW6/parser.cpp"
    break;

  case 44: /* stmt_waittill: object_restricted WAITTILL LPAREN expr COMMA expr_arg_list RPAREN SEMICOLON  */
#line 169 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_waittill((yyvsp[-7].value_node), (yyvsp[-4].value_node), (yyvsp[-2].value_expr_arg_list)); }
#line 1990 "./IW6/parser.cpp"
    break;

  case 45: /* stmt_waittill: object_restricted WAITTILL LPAREN expr RPAREN SEMICOLON  */
#line 171 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_waittill((yyvsp[-5].value_node), (yyvsp[-2].value_node), new node()); }
#line 1996 "./IW6/parser.cpp"
    break;

  case 46: /* stmt_waittillmatch: object_restricted WAITTILLMATCH LPAREN expr COMMA expr RPAREN SEMICOLON  */
#line 176 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_waittillmatch((yyvsp[-7].value_node), (yyvsp[-4].value_node), (yyvsp[-2].value_node)); }
#line 2002 "./IW6/parser.cpp"
    break;

  case 47: /* stmt_waittillframeend: WAITTILLFRAMEEND SEMICOLON  */
#line 181 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_waittillframeend(); }
#line 2008 "./IW6/parser.cpp"
    break;

  case 48: /* stmt_if: IF LPAREN expr RPAREN LBRACE stmt_block RBRACE  */
#line 186 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_if((yyvsp[-4].value_node), (yyvsp[-1].value_statement_block)); }
#line 2014 "./IW6/parser.cpp"
    break;

  case 49: /* stmt_if: IF LPAREN expr RPAREN stmt  */
#line 188 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_if((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2020 "./IW6/parser.cpp"
    break;

  case 50: /* stmt_ifelse: IF LPAREN expr RPAREN LBRACE stmt_block RBRACE ELSE LBRACE stmt_block RBRACE  */
#line 193 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_ifelse((yyvsp[-8].value_node), (yyvsp[-5].value_statement_block), (yyvsp[-1].value_statement_block)); }
#line 2026 "./IW6/parser.cpp"
    break;

  case 51: /* stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE LBRACE stmt_block RBRACE  */
#line 195 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_ifelse((yyvsp[-6].value_node), (yyvsp[-4].value_node), (yyvsp[-1].value_statement_block)); }
#line 2032 "./IW6/parser.cpp"
    break;

  case 52: /* stmt_ifelse: IF LPAREN expr RPAREN LBRACE stmt_block RBRACE ELSE stmt  */
#line 197 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_ifelse((yyvsp[-6].value_node), (yyvsp[-3].value_statement_block), (yyvsp[0].value_node)); }
#line 2038 "./IW6/parser.cpp"
    break;

  case 53: /* stmt_ifelse: IF LPAREN expr RPAREN stmt ELSE stmt  */
#line 199 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_ifelse((yyvsp[-4].value_node), (yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2044 "./IW6/parser.cpp"
    break;

  case 54: /* stmt_while: WHILE LPAREN expr RPAREN LBRACE stmt_block RBRACE  */
#line 204 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_while((yyvsp[-4].value_node), (yyvsp[-1].value_statement_block)); }
#line 2050 "./IW6/parser.cpp"
    break;

  case 55: /* stmt_while: WHILE LPAREN expr RPAREN stmt  */
#line 206 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_while((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2056 "./IW6/parser.cpp"
    break;

  case 56: /* stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN LBRACE stmt_block RBRACE  */
#line 211 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_for((yyvsp[-8].value_node), (yyvsp[-6].value_node), (yyvsp[-4].value_node), (yyvsp[-1].value_statement_block)); }
#line 2062 "./IW6/parser.cpp"
    break;

  case 57: /* stmt_for: FOR LPAREN for_assign SEMICOLON for_cond SEMICOLON for_assign RPAREN stmt  */
#line 213 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_for((yyvsp[-6].value_node), (yyvsp[-4].value_node), (yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2068 "./IW6/parser.cpp"
    break;

  case 58: /* stmt_foreach: FOREACH LPAREN expr IN expr RPAREN RBRACE stmt_block RBRACE  */
#line 218 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_foreach((yyvsp[-6].value_node), (yyvsp[-4].value_node), (yyvsp[-1].value_statement_block)); }
#line 2074 "./IW6/parser.cpp"
    break;

  case 59: /* stmt_foreach: FOREACH LPAREN expr IN expr RPAREN stmt  */
#line 220 "iw6.parser.ypp"
                { (yyval.value_node) = new node_stmt_foreach((yyvsp[-4].value_node), (yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2080 "./IW6/parser.cpp"
    break;

  case 60: /* stmt_break: BREAK SEMICOLON  */
#line 224 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_stmt_break(); }
#line 2086 "./IW6/parser.cpp"
    break;

  case 61: /* stmt_continue: CONTINUE SEMICOLON  */
#line 227 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_stmt_continue(); }
#line 2092 "./IW6/parser.cpp"
    break;

  case 62: /* stmt_return: RETURN expr SEMICOLON  */
#line 231 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_stmt_return((yyvsp[-1].value_node)); }
#line 2098 "./IW6/parser.cpp"
    break;

  case 63: /* stmt_return: RETURN SEMICOLON  */
#line 232 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_stmt_return(new node()); }
#line 2104 "./IW6/parser.cpp"
    break;

  case 64: /* for_assign: expr_assign  */
#line 236 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2110 "./IW6/parser.cpp"
    break;

  case 65: /* for_assign: %empty  */
#line 237 "iw6.parser.ypp"
                                                                                                { (yyval.value_node) = new node(); }
#line 2116 "./IW6/parser.cpp"
    break;

  case 66: /* for_cond: expr_cmp  */
#line 241 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2122 "./IW6/parser.cpp"
    break;

  case 67: /* for_cond: %empty  */
#line 242 "iw6.parser.ypp"
                                                                                                { (yyval.value_node) = new node(); }
#line 2128 "./IW6/parser.cpp"
    break;

  case 68: /* expr: expr_cmp  */
#line 247 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2134 "./IW6/parser.cpp"
    break;

  case 69: /* expr: expr_ternary  */
#line 248 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2140 "./IW6/parser.cpp"
    break;

  case 70: /* expr: expr_binary  */
#line 249 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2146 "./IW6/parser.cpp"
    break;

  case 71: /* expr: expr_unary  */
#line 250 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2152 "./IW6/parser.cpp"
    break;

  case 72: /* expr_assign: object_restricted INC  */
#line 254 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_inc((yyvsp[-1].value_node)); }
#line 2158 "./IW6/parser.cpp"
    break;

  case 73: /* expr_assign: object_restricted DEC  */
#line 255 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_dec((yyvsp[-1].value_node)); }
#line 2164 "./IW6/parser.cpp"
    break;

  case 74: /* expr_assign: object_restricted ASSIGN expr  */
#line 256 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_assign((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2170 "./IW6/parser.cpp"
    break;

  case 75: /* expr_assign: object_restricted ASSIGN_BW_OR expr  */
#line 257 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_bw_or((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2176 "./IW6/parser.cpp"
    break;

  case 76: /* expr_assign: object_restricted ASSIGN_BW_AND expr  */
#line 258 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_bw_and((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2182 "./IW6/parser.cpp"
    break;

  case 77: /* expr_assign: object_restricted ASSIGN_BW_XOR expr  */
#line 259 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_bw_xor((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2188 "./IW6/parser.cpp"
    break;

  case 78: /* expr_assign: object_restricted ASSIGN_LSHIFT expr  */
#line 260 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_shift_left((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2194 "./IW6/parser.cpp"
    break;

  case 79: /* expr_assign: object_restricted ASSIGN_RSHIFT expr  */
#line 261 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_shift_right((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2200 "./IW6/parser.cpp"
    break;

  case 80: /* expr_assign: object_restricted ASSIGN_ADD expr  */
#line 262 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_assign_add((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2206 "./IW6/parser.cpp"
    break;

  case 81: /* expr_assign: object_restricted ASSIGN_SUB expr  */
#line 263 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_assign_sub((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2212 "./IW6/parser.cpp"
    break;

  case 82: /* expr_assign: object_restricted ASSIGN_MULT expr  */
#line 264 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_mult((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2218 "./IW6/parser.cpp"
    break;

  case 83: /* expr_assign: object_restricted ASSIGN_DIV expr  */
#line 265 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_assign_div((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2224 "./IW6/parser.cpp"
    break;

  case 84: /* expr_assign: object_restricted ASSIGN_MOD expr  */
#line 266 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_assign_mod((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2230 "./IW6/parser.cpp"
    break;

  case 85: /* expr_cmp: expr CMP_OR expr  */
#line 270 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_cmp_or((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2236 "./IW6/parser.cpp"
    break;

  case 86: /* expr_cmp: expr CMP_AND expr  */
#line 271 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_cmp_and((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2242 "./IW6/parser.cpp"
    break;

  case 87: /* expr_cmp: expr CMP_EQUAL expr  */
#line 272 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_equal((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2248 "./IW6/parser.cpp"
    break;

  case 88: /* expr_cmp: expr CMP_NOT_EQ expr  */
#line 273 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_not_equal((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2254 "./IW6/parser.cpp"
    break;

  case 89: /* expr_cmp: expr CMP_LESS_EQ expr  */
#line 274 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_less_equal((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2260 "./IW6/parser.cpp"
    break;

  case 90: /* expr_cmp: expr CMP_GREATER_EQ expr  */
#line 275 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_greater_equal((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2266 "./IW6/parser.cpp"
    break;

  case 91: /* expr_cmp: expr CMP_LESS expr  */
#line 276 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_less((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2272 "./IW6/parser.cpp"
    break;

  case 92: /* expr_cmp: expr CMP_GREATER expr  */
#line 277 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_cmp_greater((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2278 "./IW6/parser.cpp"
    break;

  case 93: /* expr_ternary: expr_cmp QMARK expr COLON expr  */
#line 281 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_ternary((yyvsp[-4].value_node), (yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2284 "./IW6/parser.cpp"
    break;

  case 94: /* expr_binary: expr BW_OR expr  */
#line 285 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_bw_or((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2290 "./IW6/parser.cpp"
    break;

  case 95: /* expr_binary: expr BW_AND expr  */
#line 286 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_bw_and((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2296 "./IW6/parser.cpp"
    break;

  case 96: /* expr_binary: expr BW_XOR expr  */
#line 287 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_bw_xor((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2302 "./IW6/parser.cpp"
    break;

  case 97: /* expr_binary: expr LSHIFT expr  */
#line 288 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_shift_left((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2308 "./IW6/parser.cpp"
    break;

  case 98: /* expr_binary: expr RSHIFT expr  */
#line 289 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_shift_right((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2314 "./IW6/parser.cpp"
    break;

  case 99: /* expr_binary: expr ADD expr  */
#line 290 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_add((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2320 "./IW6/parser.cpp"
    break;

  case 100: /* expr_binary: expr SUB expr  */
#line 291 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_sub((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2326 "./IW6/parser.cpp"
    break;

  case 101: /* expr_binary: expr MULT expr  */
#line 292 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_mult((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2332 "./IW6/parser.cpp"
    break;

  case 102: /* expr_binary: expr DIV expr  */
#line 293 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_div((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2338 "./IW6/parser.cpp"
    break;

  case 103: /* expr_binary: expr MOD expr  */
#line 294 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_mod((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2344 "./IW6/parser.cpp"
    break;

  case 104: /* expr_unary: COMPLEMENT expr  */
#line 298 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_complement((yyvsp[0].value_node)); }
#line 2350 "./IW6/parser.cpp"
    break;

  case 105: /* expr_unary: NOT expr  */
#line 299 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_expr_not((yyvsp[0].value_node)); }
#line 2356 "./IW6/parser.cpp"
    break;

  case 106: /* expr_unary: expr_call  */
#line 300 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2362 "./IW6/parser.cpp"
    break;

  case 107: /* expr_unary: expr_call_thread  */
#line 301 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2368 "./IW6/parser.cpp"
    break;

  case 108: /* expr_unary: expr_select  */
#line 302 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2374 "./IW6/parser.cpp"
    break;

  case 109: /* expr_unary: expr_subscribe  */
#line 303 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2380 "./IW6/parser.cpp"
    break;

  case 110: /* expr_unary: expr_func_ref  */
#line 304 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2386 "./IW6/parser.cpp"
    break;

  case 111: /* expr_unary: empty_array  */
#line 305 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2392 "./IW6/parser.cpp"
    break;

  case 112: /* expr_unary: undefined  */
#line 306 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2398 "./IW6/parser.cpp"
    break;

  case 113: /* expr_unary: LPAREN expr COMMA expr COMMA expr RPAREN  */
#line 307 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_expr_vector((yyvsp[-5].value_node), (yyvsp[-3].value_node), (yyvsp[-1].value_node)); }
#line 2404 "./IW6/parser.cpp"
    break;

  case 114: /* expr_unary: vector  */
#line 308 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2410 "./IW6/parser.cpp"
    break;

  case 115: /* expr_unary: num  */
#line 309 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2416 "./IW6/parser.cpp"
    break;

  case 116: /* expr_unary: string_hash  */
#line 310 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2422 "./IW6/parser.cpp"
    break;

  case 117: /* expr_unary: string_loc  */
#line 311 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2428 "./IW6/parser.cpp"
    break;

  case 118: /* expr_unary: string  */
#line 312 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2434 "./IW6/parser.cpp"
    break;

  case 119: /* expr_unary: identifier  */
#line 313 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2440 "./IW6/parser.cpp"
    break;

  case 120: /* expr_unary: LPAREN expr RPAREN  */
#line 314 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = (yyvsp[-1].value_node); }
#line 2446 "./IW6/parser.cpp"
    break;

  case 121: /* expr_call: expr_func_call  */
#line 318 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_call(new node(), (yyvsp[0].value_node)); }
#line 2452 "./IW6/parser.cpp"
    break;

  case 122: /* expr_call: expr_func_call_ptr  */
#line 319 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_call(new node(), (yyvsp[0].value_node)); }
#line 2458 "./IW6/parser.cpp"
    break;

  case 123: /* expr_call: object expr_func_call  */
#line 320 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_call((yyvsp[-1].value_node), (yyvsp[0].value_node)); }
#line 2464 "./IW6/parser.cpp"
    break;

  case 124: /* expr_call: object expr_func_call_ptr  */
#line 321 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_call((yyvsp[-1].value_node), (yyvsp[0].value_node)); }
#line 2470 "./IW6/parser.cpp"
    break;

  case 125: /* expr_call_thread: THREAD expr_func_call  */
#line 325 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_call_thread(new node(), (yyvsp[0].value_node)); }
#line 2476 "./IW6/parser.cpp"
    break;

  case 126: /* expr_call_thread: THREAD expr_func_call_ptr  */
#line 326 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_call_thread(new node(), (yyvsp[0].value_node)); }
#line 2482 "./IW6/parser.cpp"
    break;

  case 127: /* expr_call_thread: object THREAD expr_func_call  */
#line 327 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_call_thread((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2488 "./IW6/parser.cpp"
    break;

  case 128: /* expr_call_thread: object THREAD expr_func_call_ptr  */
#line 328 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_call_thread((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2494 "./IW6/parser.cpp"
    break;

  case 129: /* expr_func_call: identifier LPAREN expr_arg_list RPAREN  */
#line 333 "iw6.parser.ypp"
                                                                                                        { (yyval.value_node) = new node_expr_func_call(new node(), (yyvsp[-3].value_node), (yyvsp[-1].value_expr_arg_list)); }
#line 2500 "./IW6/parser.cpp"
    break;

  case 130: /* expr_func_call: filepath DOUBLECOLON identifier LPAREN expr_arg_list RPAREN  */
#line 334 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_func_call((yyvsp[-5].value_node), (yyvsp[-3].value_node), (yyvsp[-1].value_expr_arg_list)); }
#line 2506 "./IW6/parser.cpp"
    break;

  case 131: /* expr_func_call: identifier DOUBLECOLON identifier LPAREN expr_arg_list RPAREN  */
#line 335 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_func_call((yyvsp[-5].value_node), (yyvsp[-3].value_node), (yyvsp[-1].value_expr_arg_list)); }
#line 2512 "./IW6/parser.cpp"
    break;

  case 132: /* expr_func_call_ptr: LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arg_list RPAREN  */
#line 340 "iw6.parser.ypp"
                                                                               { (yyval.value_node) = new node_expr_func_call_ptr((yyvsp[-5].value_node), (yyvsp[-1].value_expr_arg_list)); }
#line 2518 "./IW6/parser.cpp"
    break;

  case 133: /* expr_arg_list: expr_arg_list COMMA expr  */
#line 344 "iw6.parser.ypp"
                                                                        { (yyval.value_expr_arg_list) = (yyvsp[-2].value_expr_arg_list); (yyval.value_expr_arg_list)->args.push_back((yyvsp[0].value_node)); }
#line 2524 "./IW6/parser.cpp"
    break;

  case 134: /* expr_arg_list: expr  */
#line 345 "iw6.parser.ypp"
                                                                                        { (yyval.value_expr_arg_list) = new node_expr_arg_list(); (yyval.value_expr_arg_list)->args.push_back((yyvsp[0].value_node)); }
#line 2530 "./IW6/parser.cpp"
    break;

  case 135: /* expr_arg_list: %empty  */
#line 346 "iw6.parser.ypp"
                                                                                                { (yyval.value_expr_arg_list) = new node_expr_arg_list(); }
#line 2536 "./IW6/parser.cpp"
    break;

  case 136: /* expr_select: object DOT identifier  */
#line 351 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_select((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2542 "./IW6/parser.cpp"
    break;

  case 137: /* expr_select: object DOT size  */
#line 352 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_expr_select((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2548 "./IW6/parser.cpp"
    break;

  case 138: /* expr_subscribe: object LBRACKET expr RBRACKET  */
#line 357 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_subscribe((yyvsp[-3].value_node), (yyvsp[-1].value_node)); }
#line 2554 "./IW6/parser.cpp"
    break;

  case 139: /* expr_func_ref: DOUBLECOLON identifier  */
#line 362 "iw6.parser.ypp"
                                                                        { (yyval.value_node) = new node_expr_func_ref(new node(), (yyvsp[0].value_node)); }
#line 2560 "./IW6/parser.cpp"
    break;

  case 140: /* expr_func_ref: identifier DOUBLECOLON identifier  */
#line 363 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_func_ref((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2566 "./IW6/parser.cpp"
    break;

  case 141: /* expr_func_ref: filepath DOUBLECOLON identifier  */
#line 364 "iw6.parser.ypp"
                                                                { (yyval.value_node) = new node_expr_func_ref((yyvsp[-2].value_node), (yyvsp[0].value_node)); }
#line 2572 "./IW6/parser.cpp"
    break;

  case 142: /* object: expr_call  */
#line 369 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2578 "./IW6/parser.cpp"
    break;

  case 143: /* object: object_restricted  */
#line 370 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2584 "./IW6/parser.cpp"
    break;

  case 144: /* object_restricted: expr_subscribe  */
#line 375 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2590 "./IW6/parser.cpp"
    break;

  case 145: /* object_restricted: expr_select  */
#line 376 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2596 "./IW6/parser.cpp"
    break;

  case 146: /* object_restricted: identifier  */
#line 377 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2602 "./IW6/parser.cpp"
    break;

  case 147: /* object_restricted: level  */
#line 378 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2608 "./IW6/parser.cpp"
    break;

  case 148: /* object_restricted: game  */
#line 379 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2614 "./IW6/parser.cpp"
    break;

  case 149: /* size: SIZE  */
#line 383 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_size(); }
#line 2620 "./IW6/parser.cpp"
    break;

  case 150: /* false: FALSE  */
#line 387 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_num_integer("0"); }
#line 2626 "./IW6/parser.cpp"
    break;

  case 151: /* true: TRUE  */
#line 391 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_num_integer("1"); }
#line 2632 "./IW6/parser.cpp"
    break;

  case 152: /* level: LEVEL  */
#line 395 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_level(); }
#line 2638 "./IW6/parser.cpp"
    break;

  case 153: /* game: GAME  */
#line 399 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_game(); }
#line 2644 "./IW6/parser.cpp"
    break;

  case 154: /* empty_array: EMPTY_ARRAY  */
#line 403 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_empty_array(); }
#line 2650 "./IW6/parser.cpp"
    break;

  case 155: /* undefined: UNDEFINED  */
#line 407 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_undefined(); }
#line 2656 "./IW6/parser.cpp"
    break;

  case 156: /* vector: LPAREN num COMMA num COMMA num RPAREN  */
#line 411 "iw6.parser.ypp"
                                                        { (yyval.value_node) = new node_vector((yyvsp[-5].value_node), (yyvsp[-3].value_node), (yyvsp[-1].value_node)); }
#line 2662 "./IW6/parser.cpp"
    break;

  case 157: /* num: num_float  */
#line 415 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2668 "./IW6/parser.cpp"
    break;

  case 158: /* num: num_integer  */
#line 416 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2674 "./IW6/parser.cpp"
    break;

  case 159: /* num: false  */
#line 417 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2680 "./IW6/parser.cpp"
    break;

  case 160: /* num: true  */
#line 418 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = (yyvsp[0].value_node); }
#line 2686 "./IW6/parser.cpp"
    break;

  case 161: /* num_float: FLOAT  */
#line 422 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_num_float((yyvsp[0].value_string)); }
#line 2692 "./IW6/parser.cpp"
    break;

  case 162: /* num_integer: INTEGER  */
#line 426 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_num_integer((yyvsp[0].value_string)); }
#line 2698 "./IW6/parser.cpp"
    break;

  case 163: /* string_hash: STRING_HASH  */
#line 430 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_string_hash((yyvsp[0].value_string)); }
#line 2704 "./IW6/parser.cpp"
    break;

  case 164: /* string_loc: STRING_LOC  */
#line 434 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_string_loc((yyvsp[0].value_string)); }
#line 2710 "./IW6/parser.cpp"
    break;

  case 165: /* string: STRING  */
#line 438 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_string((yyvsp[0].value_string)); }
#line 2716 "./IW6/parser.cpp"
    break;

  case 166: /* identifier: IDENTIFIER  */
#line 442 "iw6.parser.ypp"
                                                                                { (yyval.value_node) = new node_identifier((yyvsp[0].value_string)); }
#line 2722 "./IW6/parser.cpp"
    break;

  case 167: /* filepath: FILEPATH  */
#line 446 "iw6.parser.ypp"
                                                                                        { (yyval.value_node) = new node_filepath((yyvsp[0].value_string)); }
#line 2728 "./IW6/parser.cpp"
    break;


#line 2732 "./IW6/parser.cpp"

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

#line 449 "iw6.parser.ypp"


int yyerror(yyscan_t scanner, node **astout, const char *msg)
{
	printf("[compiler]: %s", msg);
	return 0;
}
