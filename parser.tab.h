/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MARK_EOF = 258,
     DIR_ERR = 259,
     INCLUDE_ERR = 260,
     TOKEN_ERR = 261,
     COMMA = 262,
     SEMI = 263,
     TYPE = 264,
     LPAR = 265,
     RPAR = 266,
     LBRACKET = 267,
     RBRACKET = 268,
     LBRACE = 269,
     RBRACE = 270,
     DO = 271,
     BREAK = 272,
     CONTINUE = 273,
     RETURN = 274,
     INCR = 275,
     DECR = 276,
     COLON = 277,
     FOR = 278,
     WHILE = 279,
     IF = 280,
     ELSE = 281,
     ASSIGN = 282,
     PLUSASSIGN = 283,
     MINUSASSIGN = 284,
     STARASSIGN = 285,
     SLASHASSIGN = 286,
     QUEST = 287,
     EQUALS = 288,
     NEQUAL = 289,
     GT = 290,
     GE = 291,
     LT = 292,
     LE = 293,
     PLUS = 294,
     STAR = 295,
     SLASH = 296,
     MOD = 297,
     PIPE = 298,
     DPIPE = 299,
     DAMP = 300,
     MINUS = 301,
     BANG = 302,
     AMP = 303,
     TILDE = 304,
     STRCONST = 305,
     CHARCONST = 306,
     INTCONST = 307,
     REALCONST = 308,
     IDENT = 309,
     UMINUS = 310,
     UAMP = 311,
     NO_ELSE = 312
   };
#endif
/* Tokens.  */
#define MARK_EOF 258
#define DIR_ERR 259
#define INCLUDE_ERR 260
#define TOKEN_ERR 261
#define COMMA 262
#define SEMI 263
#define TYPE 264
#define LPAR 265
#define RPAR 266
#define LBRACKET 267
#define RBRACKET 268
#define LBRACE 269
#define RBRACE 270
#define DO 271
#define BREAK 272
#define CONTINUE 273
#define RETURN 274
#define INCR 275
#define DECR 276
#define COLON 277
#define FOR 278
#define WHILE 279
#define IF 280
#define ELSE 281
#define ASSIGN 282
#define PLUSASSIGN 283
#define MINUSASSIGN 284
#define STARASSIGN 285
#define SLASHASSIGN 286
#define QUEST 287
#define EQUALS 288
#define NEQUAL 289
#define GT 290
#define GE 291
#define LT 292
#define LE 293
#define PLUS 294
#define STAR 295
#define SLASH 296
#define MOD 297
#define PIPE 298
#define DPIPE 299
#define DAMP 300
#define MINUS 301
#define BANG 302
#define AMP 303
#define TILDE 304
#define STRCONST 305
#define CHARCONST 306
#define INTCONST 307
#define REALCONST 308
#define IDENT 309
#define UMINUS 310
#define UAMP 311
#define NO_ELSE 312




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 41 "parser.y"
{
	char cval;
        char* sval;
	int ival;
	float fval;
	struct exp_node *eval;
       }
/* Line 1529 of yacc.c.  */
#line 171 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

