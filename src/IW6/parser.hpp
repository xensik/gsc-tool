/* A Bison parser, made by GNU Bison 3.7.3.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_IW6_PARSER_HPP_INCLUDED
# define YY_YY_IW6_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 22 "iw6.parser.ypp"

	typedef void *yyscan_t; // fix yyscan_t error type no defined
	#include <utils.hpp>

	using ::node;
	using ::node_script;
	using ::node_parameter_list;
	using ::node_stmt_block;
	using ::node_expr_arg_list;

#line 60 "./IW6/parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_YYEMPTY = -2,
    TOK_EOF = 0,                   /* EOF  */
    TOK_YYerror = 256,             /* error  */
    TOK_YYUNDEF = 257,             /* "invalid token"  */
    TOK_INCLUDE = 258,             /* INCLUDE  */
    TOK_USING_ANIMTREE = 259,      /* USING_ANIMTREE  */
    TOK_ANIMTREE = 260,            /* ANIMTREE  */
    TOK_IF = 261,                  /* IF  */
    TOK_ELSE = 262,                /* ELSE  */
    TOK_SWITCH = 263,              /* SWITCH  */
    TOK_CASE = 264,                /* CASE  */
    TOK_DEFAULT = 265,             /* DEFAULT  */
    TOK_BREAK = 266,               /* BREAK  */
    TOK_FOR = 267,                 /* FOR  */
    TOK_FOREACH = 268,             /* FOREACH  */
    TOK_WHILE = 269,               /* WHILE  */
    TOK_CONTINUE = 270,            /* CONTINUE  */
    TOK_RETURN = 271,              /* RETURN  */
    TOK_THREAD = 272,              /* THREAD  */
    TOK_WAIT = 273,                /* WAIT  */
    TOK_WAITTILL = 274,            /* WAITTILL  */
    TOK_WAITTILLMATCH = 275,       /* WAITTILLMATCH  */
    TOK_WAITTILLFRAMEEND = 276,    /* WAITTILLFRAMEEND  */
    TOK_ENDON = 277,               /* ENDON  */
    TOK_NOTIFY = 278,              /* NOTIFY  */
    TOK_IN = 279,                  /* IN  */
    TOK_UNDEFINED = 280,           /* UNDEFINED  */
    TOK_TRUE = 281,                /* TRUE  */
    TOK_FALSE = 282,               /* FALSE  */
    TOK_SIZE = 283,                /* SIZE  */
    TOK_GAME = 284,                /* GAME  */
    TOK_LEVEL = 285,               /* LEVEL  */
    TOK_EMPTY_ARRAY = 286,         /* EMPTY_ARRAY  */
    TOK_LPAREN = 287,              /* LPAREN  */
    TOK_RPAREN = 288,              /* RPAREN  */
    TOK_LBRACE = 289,              /* LBRACE  */
    TOK_RBRACE = 290,              /* RBRACE  */
    TOK_LBRACKET = 291,            /* LBRACKET  */
    TOK_RBRACKET = 292,            /* RBRACKET  */
    TOK_COMMA = 293,               /* COMMA  */
    TOK_DOT = 294,                 /* DOT  */
    TOK_DOUBLECOLON = 295,         /* DOUBLECOLON  */
    TOK_COLON = 296,               /* COLON  */
    TOK_SEMICOLON = 297,           /* SEMICOLON  */
    TOK_QMARK = 298,               /* QMARK  */
    TOK_MOD = 299,                 /* MOD  */
    TOK_INC = 300,                 /* INC  */
    TOK_DEC = 301,                 /* DEC  */
    TOK_LSHIFT = 302,              /* LSHIFT  */
    TOK_RSHIFT = 303,              /* RSHIFT  */
    TOK_CMP_OR = 304,              /* CMP_OR  */
    TOK_CMP_AND = 305,             /* CMP_AND  */
    TOK_CMP_EQUAL = 306,           /* CMP_EQUAL  */
    TOK_CMP_NOT_EQ = 307,          /* CMP_NOT_EQ  */
    TOK_CMP_LESS_EQ = 308,         /* CMP_LESS_EQ  */
    TOK_CMP_GREATER_EQ = 309,      /* CMP_GREATER_EQ  */
    TOK_CMP_LESS = 310,            /* CMP_LESS  */
    TOK_CMP_GREATER = 311,         /* CMP_GREATER  */
    TOK_ASSIGN = 312,              /* ASSIGN  */
    TOK_ASSIGN_ADD = 313,          /* ASSIGN_ADD  */
    TOK_ASSIGN_SUB = 314,          /* ASSIGN_SUB  */
    TOK_ASSIGN_MULT = 315,         /* ASSIGN_MULT  */
    TOK_ASSIGN_DIV = 316,          /* ASSIGN_DIV  */
    TOK_ASSIGN_MOD = 317,          /* ASSIGN_MOD  */
    TOK_ASSIGN_BW_OR = 318,        /* ASSIGN_BW_OR  */
    TOK_ASSIGN_BW_AND = 319,       /* ASSIGN_BW_AND  */
    TOK_ASSIGN_BW_XOR = 320,       /* ASSIGN_BW_XOR  */
    TOK_ASSIGN_LSHIFT = 321,       /* ASSIGN_LSHIFT  */
    TOK_ASSIGN_RSHIFT = 322,       /* ASSIGN_RSHIFT  */
    TOK_BW_OR = 323,               /* BW_OR  */
    TOK_BW_AND = 324,              /* BW_AND  */
    TOK_BW_XOR = 325,              /* BW_XOR  */
    TOK_ADD = 326,                 /* ADD  */
    TOK_SUB = 327,                 /* SUB  */
    TOK_MULT = 328,                /* MULT  */
    TOK_DIV = 329,                 /* DIV  */
    TOK_NOT = 330,                 /* NOT  */
    TOK_COMPLEMENT = 331,          /* COMPLEMENT  */
    TOK_FILEPATH = 332,            /* FILEPATH  */
    TOK_IDENTIFIER = 333,          /* IDENTIFIER  */
    TOK_STRING = 334,              /* STRING  */
    TOK_STRING_LOC = 335,          /* STRING_LOC  */
    TOK_STRING_HASH = 336,         /* STRING_HASH  */
    TOK_FLOAT = 337,               /* FLOAT  */
    TOK_INTEGER = 338,             /* INTEGER  */
    TOK_IFX = 339                  /* IFX  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 34 "iw6.parser.ypp"

	char* value_string;
	node* value_node;
	node_script* value_script;
	node_parameter_list* value_parameter_list;
	node_stmt_block* value_statement_block;
	node_expr_arg_list* value_expr_arg_list;

#line 170 "./IW6/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (yyscan_t scanner, node **astout);

#endif /* !YY_YY_IW6_PARSER_HPP_INCLUDED  */
