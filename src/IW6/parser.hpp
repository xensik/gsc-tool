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
#line 21 "iw6.parser.ypp"

	typedef void *yyscan_t; // fix yyscan_t error type no defined
	#include <utils.hpp>

	using ::node;
	using ::node_script;
	using ::node_parameter_list;
	using ::node_statement_block;

#line 59 "./IW6/parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    TOK_EOF = 0,                   /* TOK_EOF  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_INCLUDE = 258,             /* TOK_INCLUDE  */
    TOK_USING_ANIMTREE = 259,      /* TOK_USING_ANIMTREE  */
    TOK_ANIMTREE = 260,            /* TOK_ANIMTREE  */
    TOK_IF = 261,                  /* TOK_IF  */
    TOK_ELSE = 262,                /* TOK_ELSE  */
    TOK_SWITCH = 263,              /* TOK_SWITCH  */
    TOK_CASE = 264,                /* TOK_CASE  */
    TOK_DEFAULT = 265,             /* TOK_DEFAULT  */
    TOK_BREAK = 266,               /* TOK_BREAK  */
    TOK_FOR = 267,                 /* TOK_FOR  */
    TOK_FOREACH = 268,             /* TOK_FOREACH  */
    TOK_WHILE = 269,               /* TOK_WHILE  */
    TOK_CONTINUE = 270,            /* TOK_CONTINUE  */
    TOK_RETURN = 271,              /* TOK_RETURN  */
    TOK_THREAD = 272,              /* TOK_THREAD  */
    TOK_WAIT = 273,                /* TOK_WAIT  */
    TOK_WAITTILL = 274,            /* TOK_WAITTILL  */
    TOK_WAITTILLMATCH = 275,       /* TOK_WAITTILLMATCH  */
    TOK_WAITTILLFRAMEEND = 276,    /* TOK_WAITTILLFRAMEEND  */
    TOK_ENDON = 277,               /* TOK_ENDON  */
    TOK_NOTIFY = 278,              /* TOK_NOTIFY  */
    TOK_IN = 279,                  /* TOK_IN  */
    TOK_UNDEFINED = 280,           /* TOK_UNDEFINED  */
    TOK_TRUE = 281,                /* TOK_TRUE  */
    TOK_FALSE = 282,               /* TOK_FALSE  */
    TOK_SIZE = 283,                /* TOK_SIZE  */
    TOK_GAME = 284,                /* TOK_GAME  */
    TOK_LEVEL = 285,               /* TOK_LEVEL  */
    TOK_EMPTY_ARRAY = 286,         /* TOK_EMPTY_ARRAY  */
    TOK_LPAREN = 287,              /* TOK_LPAREN  */
    TOK_RPAREN = 288,              /* TOK_RPAREN  */
    TOK_LBRACE = 289,              /* TOK_LBRACE  */
    TOK_RBRACE = 290,              /* TOK_RBRACE  */
    TOK_LBRACKET = 291,            /* TOK_LBRACKET  */
    TOK_RBRACKET = 292,            /* TOK_RBRACKET  */
    TOK_COMMA = 293,               /* TOK_COMMA  */
    TOK_DOT = 294,                 /* TOK_DOT  */
    TOK_DOUBLECOLON = 295,         /* TOK_DOUBLECOLON  */
    TOK_COLON = 296,               /* TOK_COLON  */
    TOK_SEMICOLON = 297,           /* TOK_SEMICOLON  */
    TOK_QMARK = 298,               /* TOK_QMARK  */
    TOK_HASH = 299,                /* TOK_HASH  */
    TOK_AT = 300,                  /* TOK_AT  */
    TOK_MOD = 301,                 /* TOK_MOD  */
    TOK_INC = 302,                 /* TOK_INC  */
    TOK_DEC = 303,                 /* TOK_DEC  */
    TOK_LSHIFT = 304,              /* TOK_LSHIFT  */
    TOK_RSHIFT = 305,              /* TOK_RSHIFT  */
    TOK_CMP_OR = 306,              /* TOK_CMP_OR  */
    TOK_CMP_AND = 307,             /* TOK_CMP_AND  */
    TOK_CMP_EQUAL = 308,           /* TOK_CMP_EQUAL  */
    TOK_CMP_NOT_EQ = 309,          /* TOK_CMP_NOT_EQ  */
    TOK_CMP_LESS_EQ = 310,         /* TOK_CMP_LESS_EQ  */
    TOK_CMP_GREATER_EQ = 311,      /* TOK_CMP_GREATER_EQ  */
    TOK_CMP_LESS = 312,            /* TOK_CMP_LESS  */
    TOK_CMP_GREATER = 313,         /* TOK_CMP_GREATER  */
    TOK_ASSIGN_ADD = 314,          /* TOK_ASSIGN_ADD  */
    TOK_ASSIGN_SUB = 315,          /* TOK_ASSIGN_SUB  */
    TOK_ASSIGN_MULT = 316,         /* TOK_ASSIGN_MULT  */
    TOK_ASSIGN_DIV = 317,          /* TOK_ASSIGN_DIV  */
    TOK_ASSIGN_BW_OR = 318,        /* TOK_ASSIGN_BW_OR  */
    TOK_ASSIGN_BW_AND = 319,       /* TOK_ASSIGN_BW_AND  */
    TOK_ASSIGN_BW_XOR = 320,       /* TOK_ASSIGN_BW_XOR  */
    TOK_ASSIGN_BW_NOT = 321,       /* TOK_ASSIGN_BW_NOT  */
    TOK_ASSIGN = 322,              /* TOK_ASSIGN  */
    TOK_ADD = 323,                 /* TOK_ADD  */
    TOK_SUB = 324,                 /* TOK_SUB  */
    TOK_MULT = 325,                /* TOK_MULT  */
    TOK_DIV = 326,                 /* TOK_DIV  */
    TOK_NOT = 327,                 /* TOK_NOT  */
    TOK_BW_OR = 328,               /* TOK_BW_OR  */
    TOK_BW_AND = 329,              /* TOK_BW_AND  */
    TOK_BW_XOR = 330,              /* TOK_BW_XOR  */
    TOK_BW_NOT = 331,              /* TOK_BW_NOT  */
    TOK_FILEPATH = 332,            /* TOK_FILEPATH  */
    TOK_IDENTIFIER = 333,          /* TOK_IDENTIFIER  */
    TOK_STRING = 334,              /* TOK_STRING  */
    TOK_STRING_LOC = 335,          /* TOK_STRING_LOC  */
    TOK_STRING_HASH = 336,         /* TOK_STRING_HASH  */
    TOK_FLOAT = 337,               /* TOK_FLOAT  */
    TOK_INTEGER = 338              /* TOK_INTEGER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 32 "iw6.parser.ypp"

	char* value_string;
	node* value_node;
	node_script* value_script;
	node_parameter_list* value_parameter_list;
	node_statement_block* value_statement_block;

#line 167 "./IW6/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (yyscan_t scanner, node **astout);

#endif /* !YY_YY_IW6_PARSER_HPP_INCLUDED  */
