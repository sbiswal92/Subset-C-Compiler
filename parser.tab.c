/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 2 "parser.y"

  #include <stdio.h>
  #include <stdlib.h>
  #include "symbolTable.h"
  #include "type.h"
  #include<string.h>

  

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern char* getTokenName(int);
  extern FILE *yyin;
  extern int yylineno;
  extern char* yytext;
  //char* filename;
  enum type curr_type=-1;
  exp_node *result_exp;
  extern struct symbolTable *myCurrentTable;
  
  char flag = 'x';
  int num_of_param = 0;
  int ret_param = 0;
  int id_num = 0;
  int param_num = 0;
  int fun_num = 0;

  int is_fun_alone = 0;

  int const_num = 0;
  char **all_const;



  int pass = 1;
  exp_node *temp;

  char* type_arr[8]={
                        "error",
                        "void",
                        "char",
                        "int",
                        "float",
                        "char[]",
                        "int[]",
                        "float[]"
                    };
  

  void yyerror(const char *msg){
    fprintf(stderr, "Error in %s line %d: %s\n", filename, yylineno,msg);
  }

struct symbolTable *symT;
int is_ret_there = 0;

/*sprintf(prefix,"%s: %s: %s",argv[0],cmd_argv[0],cmd_argv[1]);*/



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 63 "parser.y"
{
	char cval;
        char* sval;
	int ival;
	float fval;
	struct exp_node *eval;
       }
/* Line 193 of yacc.c.  */
#line 279 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 292 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   367

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNRULES -- Number of states.  */
#define YYNSTATES  190

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   312

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      55,    56,    57
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    19,
      23,    25,    27,    31,    33,    37,    39,    44,    47,    50,
      53,    55,    58,    60,    63,    66,    70,    72,    74,    78,
      81,    83,    85,    90,    94,    98,   100,   102,   104,   106,
     108,   110,   114,   116,   118,   121,   123,   125,   128,   130,
     133,   136,   140,   143,   149,   157,   165,   171,   179,   181,
     183,   185,   187,   189,   193,   195,   198,   201,   206,   210,
     212,   215,   218,   220,   223,   226,   229,   231,   233,   235,
     237,   239,   241,   246,   248,   250,   252,   254,   256,   258,
     264,   266,   270,   272,   276,   278,   282,   284,   288,   290,
     294,   296,   298,   300,   304,   306,   308,   310,   312,   314,
     318,   320,   322,   324,   326,   328,   332
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      59,     0,    -1,    60,    -1,    61,    -1,    60,    61,    -1,
      77,    -1,    62,    -1,     4,    -1,    63,     8,    -1,    63,
      64,     8,    -1,     9,    -1,    65,    -1,    64,     7,    65,
      -1,    66,    -1,    66,    27,    89,    -1,    54,    -1,    54,
      12,    52,    13,    -1,    68,    11,    -1,    68,    11,    -1,
      70,    73,    -1,    70,    -1,    71,    72,    -1,    71,    -1,
      54,    10,    -1,    54,    10,    -1,    91,     7,    72,    -1,
      91,    -1,    74,    -1,    73,     7,    74,    -1,    75,    76,
      -1,     9,    -1,    54,    -1,    54,    12,    52,    13,    -1,
      63,    67,    78,    -1,    79,    83,    15,    -1,    14,    -1,
      81,    -1,    88,    -1,    87,    -1,    85,    -1,    86,    -1,
      82,    83,    15,    -1,    14,    -1,    84,    -1,    83,    84,
      -1,    62,    -1,    80,    -1,    91,     8,    -1,     8,    -1,
      18,     8,    -1,    17,     8,    -1,    19,    91,     8,    -1,
      19,     8,    -1,    25,    10,    91,    11,    80,    -1,    25,
      10,    91,    11,    80,    26,    80,    -1,    23,    10,    85,
      85,    91,    11,    80,    -1,    24,    10,    91,    11,    80,
      -1,    16,    80,    24,    10,    91,    11,     8,    -1,    52,
      -1,    53,    -1,    50,    -1,    51,    -1,    54,    -1,    10,
      91,    11,    -1,    89,    -1,    90,    20,    -1,    90,    21,
      -1,    90,    12,    91,    13,    -1,    93,    96,    92,    -1,
      97,    -1,    69,    11,    -1,    69,    11,    -1,    97,    -1,
      20,    93,    -1,    21,    93,    -1,    94,    95,    -1,    90,
      -1,    46,    -1,    47,    -1,    49,    -1,    48,    -1,    93,
      -1,    10,     9,    11,    95,    -1,    28,    -1,    29,    -1,
      30,    -1,    31,    -1,    27,    -1,    98,    -1,    98,    32,
      91,    22,    97,    -1,    99,    -1,    98,    44,    99,    -1,
     100,    -1,    99,    45,   100,    -1,   101,    -1,   100,    43,
     101,    -1,   102,    -1,   101,    48,   102,    -1,   104,    -1,
     102,   103,   104,    -1,    33,    -1,    34,    -1,   106,    -1,
     104,   105,   106,    -1,    36,    -1,    35,    -1,    38,    -1,
      37,    -1,   109,    -1,   106,   107,   109,    -1,    39,    -1,
      46,    -1,    40,    -1,    41,    -1,    95,    -1,   109,   108,
      95,    -1,   109,    42,    95,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   109,   110,   113,   114,   115,   118,   119,
     122,   125,   126,   129,   130,   134,   142,   151,   168,   171,
     178,   188,   189,   192,   222,   229,   230,   233,   234,   237,
     240,   243,   253,   266,   268,   294,   327,   328,   329,   330,
     331,   334,   340,   355,   356,   359,   360,   363,   377,   380,
     381,   382,   391,   400,   401,   404,   405,   406,   410,   411,
     412,   439,   440,   445,   448,   449,   450,   451,   455,   456,
     457,   460,   461,   464,   465,   466,   467,   471,   472,   473,
     474,   477,   478,   481,   482,   483,   484,   485,   488,   489,
     492,   493,   496,   497,   500,   501,   504,   505,   508,   509,
     512,   513,   516,   517,   520,   521,   522,   523,   526,   527,
     530,   531,   534,   535,   538,   539,   540
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MARK_EOF", "DIR_ERR", "INCLUDE_ERR",
  "TOKEN_ERR", "COMMA", "SEMI", "TYPE", "LPAR", "RPAR", "LBRACKET",
  "RBRACKET", "LBRACE", "RBRACE", "DO", "BREAK", "CONTINUE", "RETURN",
  "INCR", "DECR", "COLON", "FOR", "WHILE", "IF", "ELSE", "ASSIGN",
  "PLUSASSIGN", "MINUSASSIGN", "STARASSIGN", "SLASHASSIGN", "QUEST",
  "EQUALS", "NEQUAL", "GT", "GE", "LT", "LE", "PLUS", "STAR", "SLASH",
  "MOD", "PIPE", "DPIPE", "DAMP", "MINUS", "BANG", "AMP", "TILDE",
  "STRCONST", "CHARCONST", "INTCONST", "REALCONST", "IDENT", "UMINUS",
  "UAMP", "NO_ELSE", "$accept", "trans_unit", "input", "ext_decl",
  "declaration", "decl_spec", "decl_init_list", "decl_init", "declarator",
  "fun_declarator", "fun_dec_Left", "fun_call_Left", "fun_dec_begin",
  "fun_call_begin", "idList", "paramList", "param", "param_TYPE",
  "pdeclarator", "fun_definition", "function_body", "function_body_left",
  "stmt", "compound_stmt", "compound_stmt_left", "block_item_list",
  "block_item", "expr_stmt", "jump_stmt", "selection_stmt",
  "iteration_stmt", "texpr", "postfix_expr", "expr", "rexpr", "unary_expr",
  "unary_op", "cast_expr", "asgn_op", "cond_expr", "log_or_expr",
  "log_and_expr", "bit_or_expr", "bit_and_expr", "check_expr", "check_op",
  "rel_expr", "rel_op", "add_expr", "add_op", "mul_op", "mul_expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    61,    62,    62,
      63,    64,    64,    65,    65,    66,    66,    66,    67,    68,
      68,    69,    69,    70,    71,    72,    72,    73,    73,    74,
      75,    76,    76,    77,    78,    79,    80,    80,    80,    80,
      80,    81,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    86,    86,    87,    87,    88,    88,    88,    89,    89,
      89,    89,    89,    89,    90,    90,    90,    90,    91,    91,
      91,    92,    92,    93,    93,    93,    93,    94,    94,    94,
      94,    95,    95,    96,    96,    96,    96,    96,    97,    97,
      98,    98,    99,    99,   100,   100,   101,   101,   102,   102,
     103,   103,   104,   104,   105,   105,   105,   105,   106,   106,
     107,   107,   108,   108,   109,   109,   109
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     2,     3,
       1,     1,     3,     1,     3,     1,     4,     2,     2,     2,
       1,     2,     1,     2,     2,     3,     1,     1,     3,     2,
       1,     1,     4,     3,     3,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     2,     1,     1,     2,     1,     2,
       2,     3,     2,     5,     7,     7,     5,     7,     1,     1,
       1,     1,     1,     3,     1,     2,     2,     4,     3,     1,
       2,     2,     1,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     4,     1,     1,     1,     1,     1,     1,     5,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,    10,     0,     2,     3,     6,     0,     5,     1,
       4,     8,    15,     0,    11,    13,     0,     0,    20,    23,
       0,     0,     9,     0,    35,    33,     0,    17,    30,    19,
      27,     0,     0,    12,     0,     0,    60,    61,    58,    59,
      62,    14,    48,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    77,    78,    80,    79,    62,    45,
       0,     0,    22,    46,    36,     0,     0,    43,    39,    40,
      38,    37,    64,    76,     0,    81,     0,   114,    69,    88,
      90,    92,    94,    96,    98,   102,   108,     0,    31,    29,
      16,    17,     0,     0,     0,    50,    49,    52,     0,    73,
      74,     0,     0,     0,    24,    70,    21,    26,     0,    34,
      44,     0,    65,    66,    47,    87,    83,    84,    85,    86,
       0,    81,    75,     0,     0,     0,     0,     0,   100,   101,
       0,   105,   104,   107,   106,     0,   110,   111,     0,   112,
     113,     0,     0,    28,     0,    63,     0,     0,    51,     0,
       0,     0,     0,    41,     0,     0,    68,    72,     0,    91,
      93,    95,    97,    99,   103,   109,   116,   115,     0,    82,
       0,     0,     0,     0,    25,    67,    71,     0,    32,     0,
       0,    56,    53,    89,     0,     0,     0,    57,    55,    54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    59,    60,    13,    14,    15,    16,
      34,    61,    18,    62,   106,    29,    30,    31,    89,     8,
      25,    26,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   156,    75,    76,    77,   120,    78,
      79,    80,    81,    82,    83,   130,    84,   135,    85,   138,
     142,    86
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -119
static const yytype_int16 yypact[] =
{
       9,  -119,  -119,    15,     9,  -119,  -119,    -4,  -119,  -119,
    -119,  -119,    14,    23,  -119,     0,    28,    32,    38,  -119,
       8,    -6,  -119,     2,  -119,  -119,   161,    47,  -119,    55,
    -119,    10,    50,  -119,    54,   278,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,   261,  -119,   208,    58,    59,   226,   296,
     296,    60,    61,    62,  -119,  -119,  -119,  -119,    65,  -119,
      -4,    68,   278,  -119,  -119,   161,    96,  -119,  -119,  -119,
    -119,  -119,  -119,    -1,    76,     6,   313,  -119,  -119,   -22,
      40,    44,    42,    24,     3,   -23,     4,    38,    80,  -119,
    -119,  -119,    77,    82,    71,  -119,  -119,  -119,    88,  -119,
    -119,   243,   278,   278,  -119,  -119,  -119,    92,   143,  -119,
    -119,   278,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
     278,  -119,  -119,   278,   313,   313,   313,   313,  -119,  -119,
     313,  -119,  -119,  -119,  -119,   313,  -119,  -119,   313,  -119,
    -119,   313,   313,  -119,    48,  -119,   313,    91,  -119,   243,
      97,    98,   278,  -119,    90,   111,  -119,  -119,    85,    40,
      44,    42,    24,     3,   -23,     4,  -119,  -119,   110,  -119,
     278,   278,   208,   208,  -119,  -119,  -119,   313,  -119,   113,
     114,  -119,   100,  -119,   121,   208,   208,  -119,  -119,  -119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,  -119,   126,    17,    25,  -119,   117,  -119,  -119,
     124,    12,  -119,  -119,   -18,  -119,    52,  -119,  -119,  -119,
    -119,  -119,   -45,  -119,  -119,    70,   -59,   -98,  -119,  -119,
    -119,   131,  -119,   -34,  -119,   -44,  -119,   -68,  -119,  -118,
    -119,    31,    49,    30,    45,  -119,    35,  -119,    41,  -119,
    -119,    63
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -19
static const yytype_int16 yytable[] =
{
      94,    92,   157,   149,    11,    99,   100,   110,   122,    92,
     123,   111,    35,     1,    98,     9,   136,     6,     2,   112,
     113,     6,   124,   137,    19,     7,    20,    23,   107,     7,
      21,    22,   121,   115,   116,   117,   118,   119,   131,   132,
     133,   134,    24,    27,   139,   140,   141,    28,    12,   110,
      12,   171,    36,    37,    38,    39,    40,   128,   129,   183,
      32,   -18,    87,    90,    88,    91,    95,    96,   150,   151,
     101,   102,   103,   166,   167,   104,   121,   154,   169,   105,
     121,   121,   121,   121,   114,   125,   121,   126,   145,   158,
     127,   121,   144,   146,   121,   147,   148,   121,   121,   152,
     168,   170,   121,   175,    42,     2,    43,   177,   172,   173,
      44,   109,    45,    46,    47,    48,    49,    50,   107,    51,
      52,    53,   176,   178,   184,   185,   186,   181,   182,   187,
      10,    17,   155,   121,   174,   108,   179,   180,    33,   143,
     188,   189,    54,    55,    56,    57,    36,    37,    38,    39,
      58,    42,     2,    43,    41,   159,   161,    44,   153,    45,
      46,    47,    48,    49,    50,   163,    51,    52,    53,    42,
       2,    43,   162,     0,   160,    44,   164,    45,    46,    47,
      48,    49,    50,     0,    51,    52,    53,     0,     0,    54,
      55,    56,    57,    36,    37,    38,    39,    58,     0,     0,
       0,   165,     0,     0,     0,     0,     0,    54,    55,    56,
      57,    36,    37,    38,    39,    58,    42,     0,    43,     0,
       0,     0,    44,     0,    45,    46,    47,    48,    49,    50,
       0,    51,    52,    53,    97,     0,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,    42,     0,    43,    54,    55,    56,    57,    36,    37,
      38,    39,    58,    49,    50,     0,     0,     0,     0,     0,
      93,    43,    54,    55,    56,    57,    36,    37,    38,    39,
      58,    49,    50,     0,     0,     0,     0,     0,    43,    54,
      55,    56,    57,    36,    37,    38,    39,    58,    49,    50,
       0,     0,     0,     0,     0,     0,    35,    54,    55,    56,
      57,    36,    37,    38,    39,    58,    49,    50,     0,     0,
       0,     0,     0,    43,    54,    55,    56,    57,    36,    37,
      38,    39,    58,    49,    50,     0,     0,     0,     0,     0,
       0,     0,    54,    55,    56,    57,    36,    37,    38,    39,
      40,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      55,    56,    57,    36,    37,    38,    39,    40
};

static const yytype_int16 yycheck[] =
{
      45,    35,   120,   101,     8,    49,    50,    66,    76,    43,
      32,    12,    10,     4,    48,     0,    39,     0,     9,    20,
      21,     4,    44,    46,    10,     0,    12,    27,    62,     4,
       7,     8,    76,    27,    28,    29,    30,    31,    35,    36,
      37,    38,    14,    11,    40,    41,    42,     9,    54,   108,
      54,   149,    50,    51,    52,    53,    54,    33,    34,   177,
      52,    14,     7,    13,    54,    11,     8,     8,   102,   103,
      10,    10,    10,   141,   142,    10,   120,   111,   146,    11,
     124,   125,   126,   127,     8,    45,   130,    43,    11,   123,
      48,   135,    12,    11,   138,    24,     8,   141,   142,     7,
      52,    10,   146,    13,     8,     9,    10,    22,    11,    11,
      14,    15,    16,    17,    18,    19,    20,    21,   152,    23,
      24,    25,    11,    13,    11,    11,    26,   172,   173,     8,
       4,     7,   120,   177,   152,    65,   170,   171,    21,    87,
     185,   186,    46,    47,    48,    49,    50,    51,    52,    53,
      54,     8,     9,    10,    23,   124,   126,    14,    15,    16,
      17,    18,    19,    20,    21,   130,    23,    24,    25,     8,
       9,    10,   127,    -1,   125,    14,   135,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    25,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,   138,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     8,    -1,    10,    -1,
      -1,    -1,    14,    -1,    16,    17,    18,    19,    20,    21,
      -1,    23,    24,    25,     8,    -1,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,
      -1,     8,    -1,    10,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    20,    21,    -1,    -1,    -1,    -1,    -1,
       9,    10,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    20,    21,    -1,    -1,    -1,    -1,    -1,    10,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    10,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    20,    21,    -1,    -1,
      -1,    -1,    -1,    10,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     9,    59,    60,    61,    62,    63,    77,     0,
      61,     8,    54,    64,    65,    66,    67,    68,    70,    10,
      12,     7,     8,    27,    14,    78,    79,    11,     9,    73,
      74,    75,    52,    65,    68,    10,    50,    51,    52,    53,
      54,    89,     8,    10,    14,    16,    17,    18,    19,    20,
      21,    23,    24,    25,    46,    47,    48,    49,    54,    62,
      63,    69,    71,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    93,    94,    95,    97,    98,
      99,   100,   101,   102,   104,   106,   109,     7,    54,    76,
      13,    11,    91,     9,    80,     8,     8,     8,    91,    93,
      93,    10,    10,    10,    10,    11,    72,    91,    83,    15,
      84,    12,    20,    21,     8,    27,    28,    29,    30,    31,
      96,    93,    95,    32,    44,    45,    43,    48,    33,    34,
     103,    35,    36,    37,    38,   105,    39,    46,   107,    40,
      41,    42,   108,    74,    12,    11,    11,    24,     8,    85,
      91,    91,     7,    15,    91,    69,    92,    97,    91,    99,
     100,   101,   102,   104,   106,   109,    95,    95,    52,    95,
      10,    85,    11,    11,    72,    13,    11,    22,    13,    91,
      91,    80,    80,    97,    11,    11,    26,     8,    80,    80
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 107 "parser.y"
    { if(flag == 'p') printAllLists(symT,0); printf("\n"); ;}
    break;

  case 4:
#line 110 "parser.y"
    {  ;}
    break;

  case 5:
#line 113 "parser.y"
    {  ;}
    break;

  case 7:
#line 115 "parser.y"
    { fprintf(stderr,"Error in %s line %d: \n\t directive '%s' not implemented, ignoring\n",filename, yylineno, yytext); ;}
    break;

  case 9:
#line 119 "parser.y"
    { ;}
    break;

  case 10:
#line 122 "parser.y"
    { curr_type = getType((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 15:
#line 134 "parser.y"
    {    if(pass == 1)
                        {
                                struct symbol thisSym;
                                initializeSymbol(&thisSym, (yyvsp[(1) - (1)].sval), curr_type, variable, yylineno, id_num);
                                id_num+=1;
                                symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                        }
		   ;}
    break;

  case 16:
#line 142 "parser.y"
    {
                                                        if(pass == 1)
                                                        {       
                                                                struct symbol thisSym;
                                                                initializeSymbol(&thisSym, (yyvsp[(1) - (4)].sval), curr_type + 3, variable,yylineno, id_num);
                                                                id_num+=1;
                                                                symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                                                        }
                                                ;}
    break;

  case 17:
#line 151 "parser.y"
    { 
                                
                                if(pass==1) 
                                {
                                        int x=0; 
                                        symT = exit_scope(symT,&x,filename,yylineno); /*exit scope just a declaration*/  
                                        fun_num = symT->fun_num+1;
                                }  
                                if(pass==2) 
                                {
                                        int x=1; 
                                        symT = exit_scope(symT,&x,filename,yylineno); /*exit scope just a declaration*/  
                                        fun_num = symT->fun_num+1;
                                }       
                             ;}
    break;

  case 18:
#line 168 "parser.y"
    { /*do not exit scope because function body follows*/ ;}
    break;

  case 19:
#line 171 "parser.y"
    { if(pass==2) 
                                                {
                                                        printf("\n .params %d",num_of_param); 
                                                        printf("\n .return %d",ret_param); 
                                                        printf("\n .locals %d",symT->local_num+1); 
                                                }
                                        ;}
    break;

  case 20:
#line 178 "parser.y"
    {        num_of_param = 0;
                                        if(pass==2) 
                                                {
                                                        printf("\n .params %d",num_of_param); 
                                                        printf("\n .return %d",ret_param); 
                                                        printf("\n .locals %d",symT->local_num+1); 
                                                }
                               ;}
    break;

  case 21:
#line 188 "parser.y"
    { (yyval.eval) = makeFuncE((yyvsp[(1) - (2)].eval),(yyvsp[(2) - (2)].eval)); ;}
    break;

  case 22:
#line 189 "parser.y"
    { (yyval.eval) = makeFuncNPE((yyvsp[(1) - (1)].eval)); ;}
    break;

  case 23:
#line 192 "parser.y"
    {
                                 
                                  struct symbol thisSym;
                                  initializeSymbol(&thisSym, (yyvsp[(1) - (2)].sval), curr_type, function1, yylineno, fun_num);
                                  fun_num +=1;
                                  if(pass == 1)
                                  {
                                        symbolTable_insertSymbol(symT,thisSym,filename,yylineno);
                                        symT = enter_scope(symT,thisSym,1);
                                  }
                                 if(pass==2) 
                                 {
                                        struct symbol *SymForFunIdent = lookup(symT, (yyvsp[(1) - (2)].sval), filename, yylineno);
                                        char num[12];
                                        sprintf(num, "%d", SymForFunIdent->kind_position);
                                        int size = 1+strlen(" ")+strlen(SymForFunIdent->id)+strlen(num);
                                        char *id_code = (char*)malloc(size);
                                        strcpy(id_code,num);
                                        strcat(id_code," ");
                                        strcat(id_code,SymForFunIdent->id);
                                        printf("\n\n.FUNC %s",id_code);
                                        num_of_param = 0;
                                        ret_param = SymForFunIdent->ret_value;
                                        symT = enter_scope(symT,thisSym,0);
                                        

                                 } 
                                
			   ;}
    break;

  case 24:
#line 222 "parser.y"
    {
                                 myCurrentTable = symbolTable_getParent(symT);
                                 struct symbol *SymForFunIdent = lookup(symbolTable_getParent(symT), (yyvsp[(1) - (2)].sval), filename, yylineno);
                                 (yyval.eval) = makeIdentifierNameE(SymForFunIdent);
                                 
                            ;}
    break;

  case 25:
#line 229 "parser.y"
    { (yyval.eval) = makeCommaE((yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval));  ;}
    break;

  case 26:
#line 230 "parser.y"
    { (yyval.eval) = makeCommaLastE((yyvsp[(1) - (1)].eval)); ;}
    break;

  case 27:
#line 233 "parser.y"
    { num_of_param +=1; ;}
    break;

  case 28:
#line 234 "parser.y"
    { num_of_param +=1; ;}
    break;

  case 30:
#line 240 "parser.y"
    { curr_type = getType((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 31:
#line 243 "parser.y"
    {
                        if(pass == 1) 
                        {
                                struct symbol thisSym;
                                initializeSymbol(&thisSym, (yyvsp[(1) - (1)].sval), curr_type,  parameter, yylineno,id_num);
                                
                                symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                               
                        }
                    ;}
    break;

  case 32:
#line 253 "parser.y"
    {
                                  if(pass == 1)
                                  {
                                        struct symbol thisSym;
                                        initializeSymbol(&thisSym, (yyvsp[(1) - (4)].sval), curr_type + 3, parameter,yylineno,id_num);
                                        symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                                        
                                  }
                                        ;}
    break;

  case 33:
#line 266 "parser.y"
    { ;}
    break;

  case 34:
#line 268 "parser.y"
    { 
                                                                if(pass==1)
                                                                {
                                                                        int x = 1;
                                                                        if((is_ret_there==0) && (symT->parentSymbolTableEntrySymbol.type>1))
                                                                                fprintf(stderr,"Error in %s line %d:\n \t Return type is missing for function %s:\n\t  Return type expected is %s (near line %d)\n",filename,yylineno, symT->parentSymbolTableEntrySymbol.id, type_arr[symT->parentSymbolTableEntrySymbol.type], symT->parentSymbolTableEntrySymbol.lineno);
                                                                        symT = exit_scope(symT,&x,filename,yylineno); 
                                                                        fun_num = symT->fun_num+1;
                                                                }
                                                                if(pass==2)
                                                                {
                                                                        int x = 1;
                                                                        symT = exit_scope(symT,&x,filename,yylineno); 
                                                                        if(is_ret_there == 0)
                                                                                {
                                                                                        printf("\nret");
                                                                                }
                                                                       
                                                                        printf("\n.end FUNC");
                                                                        is_ret_there = 0; // reset it to zero for other function
                                                                        
                                                                }
                                                                
                                                           ;}
    break;

  case 35:
#line 294 "parser.y"
    { 

                           
                                if(pass==1)
                                {
                                        struct symbol parentSymbol = symT->parentSymbolTableEntrySymbol;
                                        int x = 0;
                                        is_ret_there = 0;
                                        symT = exit_scope(symT,&x,filename,yylineno);   //exit <post-processing> and re-enter
                                        if(x==1)//this is first-time definition
                                        {
                                        symT = enter_scope(symT,parentSymbol,0);
                                        }
                                        else if(x==2) //this is first-time definition
                                        {
                                        struct symbol* newparentSymbol = lookup1(symT,parentSymbol,filename, yylineno);
                                        symT = enter_scope(symT,*newparentSymbol,0);
                                        }
                                        else if(x==-1) //function definition already exists
                                        {
                                        struct symbol* oldSymbol = lookup(symT,parentSymbol.id,filename, yylineno);   
                                        fprintf(stderr,"Error in %s line %d:\n \t Function %s is already declared (near line %d)\n", filename, yylineno, oldSymbol->id, oldSymbol->lineno );
                                        exit(1);
                                        }
                                }
                                if(pass==2)
                                {
                                      
                                }  
                              ;}
    break;

  case 41:
#line 334 "parser.y"
    {
                                 int x = 0; 
                                 symT = exit_scope(symT,&x,filename,yylineno); 
                        ;}
    break;

  case 42:
#line 340 "parser.y"
    { 
                                if(pass == 1)
                                {
                                        struct symbol thisSym;
                                        initializeSymbol(&thisSym, "0", VOID_T, variable,yylineno,0);
                                        symT = enter_scope(symT,thisSym,1);
                                } 
                                if(pass == 2)
                                {
                                        struct symbol thisSym;
                                        initializeSymbol(&thisSym, "0", VOID_T, variable,yylineno,0);
                                        symT = enter_scope(symT,thisSym,0);
                                }
                             ;}
    break;

  case 47:
#line 363 "parser.y"
    { int ans = dataTypeOf((yyvsp[(1) - (2)].eval));
                        if( flag == 't' && ans) printf("Expression at file %s at line %d has type %s\n",filename, yylineno, type_arr[ans]); 
                        if(flag == 'i' && pass == 2) {
                                 if(is_fun_alone==1)  {
                                                
                                                appendCode((yyvsp[(1) - (2)].eval),"\npopx");
                                                printCode((yyvsp[(1) - (2)].eval));
                                                is_fun_alone = 0;
                                        } 
                                        else
                                          printCode((yyvsp[(1) - (2)].eval));
                                
                                 }
                      ;}
    break;

  case 51:
#line 382 "parser.y"
    { 
                                (yyval.eval) = makeRetE((yyvsp[(2) - (3)].eval));
                                struct symbol parentSymbol = symT->parentSymbolTableEntrySymbol;
                                enum type ret_type = dataTypeOf((yyval.eval));
                                is_ret_there = 1;
                                if( ret_type > parentSymbol.type)
                                      fprintf(stderr,"Error in %s line %d:\n \t No match for return type %s for function %s:\n\t Return type expected is %s (near line %d)\n",filename,yylineno,type_arr[ret_type], parentSymbol.id, type_arr[parentSymbol.type], parentSymbol.lineno);
                                if(flag == 'i' && pass == 2) printCode((yyval.eval));
                              ;}
    break;

  case 52:
#line 391 "parser.y"
    { 
                          struct symbol parentSymbol = symT->parentSymbolTableEntrySymbol;
                          is_ret_there = 0;
                          if(parentSymbol.type !=VOID_T)
                                fprintf(stderr,"Error in %s line %d:\n \t No match for return type %s for function %s:\n\t  Return type expected is void (near line %d)\n",filename,yylineno,parentSymbol.id,type_arr[parentSymbol.type], parentSymbol.lineno);
                          if(flag == 'i' && pass == 2) printf("\n");
                        ;}
    break;

  case 58:
#line 410 "parser.y"
    { (yyval.eval) = makeIntConstE((yyvsp[(1) - (1)].sval));  ;}
    break;

  case 59:
#line 411 "parser.y"
    { (yyval.eval) = makeFloatConstE((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 60:
#line 412 "parser.y"
    { 
                        if(pass == 1)  
                        {
                          if(const_num==0)
                                all_const = (char**)malloc(1*sizeof(char*));
                          else
                                all_const = (char**)realloc(all_const,(const_num+1)*sizeof(char*));
                                
                          all_const[const_num] = (char*)malloc(strlen((yyvsp[(1) - (1)].sval)));
                          //strcpy(all_const[const_num],"0x");
                          strcpy(all_const[const_num],(yyvsp[(1) - (1)].sval));
                          const_num +=1;
                          
                        } else if(pass == 2) {
                          for(int i=0;i<const_num;i++)
                          {
                                  if(strcmp(all_const[i],(yyvsp[(1) - (1)].sval))==0)
                                  {
                                         char const_code[5];
                                         sprintf(const_code, "%d", i);
                                         (yyval.eval) = makeCArrConstE(const_code); 
                                         //printCode($$); 
                                  }
                          }
                         
                        }
                ;}
    break;

  case 61:
#line 439 "parser.y"
    { (yyval.eval) = makeCharConstE((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 62:
#line 440 "parser.y"
    { 
                        /*variable call*/
                        struct symbol *SymForVarIdent = lookup(symT, (yyvsp[(1) - (1)].sval),filename, yylineno);
                        (yyval.eval) = makeIdentifierNameE(SymForVarIdent);
                    ;}
    break;

  case 63:
#line 445 "parser.y"
    { (yyval.eval) = (yyvsp[(2) - (3)].eval); ;}
    break;

  case 64:
#line 448 "parser.y"
    { (yyval.eval) = (yyvsp[(1) - (1)].eval); ;}
    break;

  case 65:
#line 449 "parser.y"
    { (yyval.eval) = makeUnPostE((yyvsp[(2) - (2)].sval),(yyvsp[(1) - (2)].eval)); ;}
    break;

  case 66:
#line 450 "parser.y"
    { (yyval.eval) = makeUnPostE((yyvsp[(2) - (2)].sval),(yyvsp[(1) - (2)].eval)); ;}
    break;

  case 67:
#line 451 "parser.y"
    { (yyval.eval) = makeArrE((yyvsp[(1) - (4)].eval),(yyvsp[(3) - (4)].eval)); ;}
    break;

  case 68:
#line 455 "parser.y"
    { (yyval.eval) = makeAssE((yyvsp[(2) - (3)].sval),(yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval)); ;}
    break;

  case 69:
#line 456 "parser.y"
    { (yyval.eval) = (yyvsp[(1) - (1)].eval); ;}
    break;

  case 70:
#line 457 "parser.y"
    { (yyval.eval) = (yyvsp[(1) - (2)].eval); if(pass==2) is_fun_alone = 1;;}
    break;

  case 71:
#line 460 "parser.y"
    { (yyval.eval) = (yyvsp[(1) - (2)].eval); if(pass==2) is_fun_alone = 0; ;}
    break;

  case 72:
#line 461 "parser.y"
    { (yyval.eval) = (yyvsp[(1) - (1)].eval); ;}
    break;

  case 73:
#line 464 "parser.y"
    { (yyval.eval) = makeUnPreE((yyvsp[(1) - (2)].sval),(yyvsp[(2) - (2)].eval)); ;}
    break;

  case 74:
#line 465 "parser.y"
    { (yyval.eval) = makeUnPreE((yyvsp[(1) - (2)].sval),(yyvsp[(2) - (2)].eval)); ;}
    break;

  case 75:
#line 466 "parser.y"
    { (yyval.eval) = makeSomeUnE((yyvsp[(1) - (2)].sval) ,(yyvsp[(2) - (2)].eval)); ;}
    break;

  case 76:
#line 467 "parser.y"
    { (yyval.eval) = (yyvsp[(1) - (1)].eval);;}
    break;

  case 77:
#line 471 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 78:
#line 472 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 79:
#line 473 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 80:
#line 474 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 81:
#line 477 "parser.y"
    { (yyval.eval) = (yyvsp[(1) - (1)].eval);  ;}
    break;

  case 82:
#line 478 "parser.y"
    {(yyval.eval) = makeCastE((yyvsp[(2) - (4)].sval),(yyvsp[(4) - (4)].eval));;}
    break;

  case 83:
#line 481 "parser.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 84:
#line 482 "parser.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 85:
#line 483 "parser.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 86:
#line 484 "parser.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 87:
#line 485 "parser.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 88:
#line 488 "parser.y"
    {(yyval.eval) = (yyvsp[(1) - (1)].eval);;}
    break;

  case 89:
#line 489 "parser.y"
    {(yyval.eval) = makeCondE((yyvsp[(1) - (5)].eval),(yyvsp[(3) - (5)].eval),(yyvsp[(5) - (5)].eval));;}
    break;

  case 90:
#line 492 "parser.y"
    {(yyval.eval) = (yyvsp[(1) - (1)].eval);;}
    break;

  case 91:
#line 493 "parser.y"
    {(yyval.eval) = makeLogE((yyvsp[(2) - (3)].sval),(yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval));;}
    break;

  case 92:
#line 496 "parser.y"
    {(yyval.eval) = (yyvsp[(1) - (1)].eval);;}
    break;

  case 93:
#line 497 "parser.y"
    {(yyval.eval) = makeLogE((yyvsp[(2) - (3)].sval),(yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval));;}
    break;

  case 94:
#line 500 "parser.y"
    {(yyval.eval) = (yyvsp[(1) - (1)].eval);;}
    break;

  case 95:
#line 501 "parser.y"
    {(yyval.eval) = makeBitE((yyvsp[(2) - (3)].sval),(yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval));;}
    break;

  case 96:
#line 504 "parser.y"
    {(yyval.eval) = (yyvsp[(1) - (1)].eval);;}
    break;

  case 97:
#line 505 "parser.y"
    {(yyval.eval) = makeBitE((yyvsp[(2) - (3)].sval),(yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval));;}
    break;

  case 98:
#line 508 "parser.y"
    {(yyval.eval) = (yyvsp[(1) - (1)].eval);;}
    break;

  case 99:
#line 509 "parser.y"
    {(yyval.eval) = makeRelE((yyvsp[(2) - (3)].sval),(yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval));;}
    break;

  case 100:
#line 512 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 101:
#line 513 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 102:
#line 516 "parser.y"
    {(yyval.eval) = (yyvsp[(1) - (1)].eval); ;}
    break;

  case 103:
#line 517 "parser.y"
    { (yyval.eval) = makeRelE((yyvsp[(2) - (3)].sval),(yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval)); ;}
    break;

  case 104:
#line 520 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 105:
#line 521 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 106:
#line 522 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 107:
#line 523 "parser.y"
    {(yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 108:
#line 526 "parser.y"
    { (yyval.eval) = (yyvsp[(1) - (1)].eval); ;}
    break;

  case 109:
#line 527 "parser.y"
    { (yyval.eval) = makeArithE((yyvsp[(2) - (3)].sval),(yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval));  ;}
    break;

  case 110:
#line 530 "parser.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 111:
#line 531 "parser.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 112:
#line 534 "parser.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 113:
#line 535 "parser.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 114:
#line 538 "parser.y"
    { (yyval.eval) = (yyvsp[(1) - (1)].eval);;}
    break;

  case 115:
#line 539 "parser.y"
    { (yyval.eval) = makeArithE((yyvsp[(2) - (3)].sval), (yyvsp[(1) - (3)].eval), (yyvsp[(3) - (3)].eval));;}
    break;

  case 116:
#line 540 "parser.y"
    { (yyval.eval) = makeModE((yyvsp[(1) - (3)].eval),(yyvsp[(3) - (3)].eval));  ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2379 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 545 "parser.y"

/*
int main(int argc, char** argv) {
  // open a file handle to a particular file:
  filename = argv[1];
// printf("\nFile:%s",filename);
  FILE *myfile = fopen(argv[1], "r");
  // make sure it is valid:
 symT = (struct symbolTable*)malloc(sizeof(struct symbolTable));
 symT->symbolListHead = NULL;
 symT->parentSymbolTable = NULL;
 symT->childSymbolTableListHead = NULL;
 


  // Set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  // Parse through the input:
  yyparse();
}i*/


int main(int argc, char **argv)
{

        if(argc<3) {

                fprintf(stderr, "Error: input expected in the form of './compile -[l|p|t|i] <inputfile>'\n");
                exit(1);

        } else if (strcmp(argv[1],"-l")==0) {
                int file_track=2;
                
                while(file_track<argc)
                {
                        FILE *myfile = fopen(argv[file_track], "r");
			yyin = myfile;
			if(!myfile){
                        int token;
                        for(;;){
                        
                                token = yylex();
                                if(token==DIR_ERR) //Error for non-implemented features
                                        fprintf(stderr,"Error in %s line %d: \n\t directive ’%s’ not implemented, ignoring\n", argv[file_track], yylineno, yytext);

                                else if(token==TOKEN_ERR) //Error for unknown tokens
                                        fprintf(stderr,"Error in %s line %d:\n\t unknown token'%s'\n", argv[file_track], yylineno, yytext);
                                
                                else if(token==INCLUDE_ERR)
                                        fprintf(stderr,"Error in %s line %d: \n\t directive ’%s’ not implemented, ignoring\n", argv[file_track], yylineno, yytext);

                                else if(token==MARK_EOF)
                                        break;

                                else
                                	{}
				}
                        }
                        
                        file_track+=1;
                }
                
        } else if (argc>4) {

		fprintf(stderr, "Error: input expected in the form of './compile -[l|t|i] <inputfile> '\n");

        } else {
        
                if (strcmp(argv[1],"-p")==0) {
                
                        {
                                flag = 'p';
                                filename = argv[2];
                                FILE *myfile = fopen(argv[2], "r");
                                // make sure it is valid:
                                symT = (struct symbolTable*)malloc(sizeof(struct symbolTable));
                                symT->symbolListHead = NULL;
                                symT->parentSymbolTable = NULL;
                                symT->childSymbolTableListHead = NULL;


                                // Set flex to read from it instead of defaulting to STDIN:
                                yyin = myfile;
                                // Parse through the input:
                                yyparse();
                        }
                        
                } else if (strcmp(argv[1],"-t")==0) {
                
                        {
                                flag = 't';
                                filename = argv[2];
                                FILE *myfile = fopen(argv[2], "r");
                                // make sure it is valid:
                                symT = (struct symbolTable*)malloc(sizeof(struct symbolTable));
                                symT->symbolListHead = NULL;
                                symT->parentSymbolTable = NULL;
                                symT->childSymbolTableListHead = NULL;
                        
                                // Set flex to read from it instead of defaulting to STDIN:
                                yyin = myfile;
                                // Parse through the input:
                                yyparse();
                        }
                        
                } else if (strcmp(argv[1],"-i")==0) {
                
                       {
                                flag = 'i';
                                filename = argv[2];
                                FILE *myfile = fopen(argv[2], "r");
                                // make sure it is valid:
                                struct symbol BlankSymbol;
                                initializeSymbol(&BlankSymbol, "0", getType("void"), variable, -10, -1);
                                symT = (struct symbolTable*)malloc(sizeof(struct symbolTable));
                                symT->symbolListHead = NULL;
                                symT->parentSymbolTable = NULL;
                                symT->parentSymbolTableEntrySymbol = BlankSymbol;
                                symT->childSymbolTableListHead = NULL;
                                symT->local_num = -1;
	                        symT->param_num = -1;
	                        symT->fun_num = -1;

                                //Add default functions to the table 
                                  struct symbol fun1;
                                  const char* getchar_name = "getchar";
                                  initializeSymbol(&fun1, getchar_name, getType("int"), function1, -1, -1);
                                  symbolTable_insertSymbol(symT,fun1,filename,-1);

                                  struct symbol fun2;
                                  initializeSymbol(&fun2, "putchar", getType("int"), function1, -2, 0);
                                  symbolTable_insertSymbol(symT,fun2,filename,-2);
                                  symT = enter_scope(symT,fun2,1);
                                        struct symbol fun2par1;
                                        initializeSymbol(&fun2par1, "c", getType("int"), parameter, -3, -1);
                                        symbolTable_insertSymbol(symT,fun2par1,filename,-3);
                                        int x = 0;
                                        symT = exit_scope(symT,&x,filename,-3);
                                  
                                  


                                // Set flex to read from it instead of defaulting to STDIN:
                                yyin = myfile;
                                // Parse through the input:
                                pass = 1;
                                yyparse();
                                printf("\n.CONSTANTS %d", const_num);
                                for(int i = 0;i<const_num;i++)
                                {
                                        printf("\n %s",all_const[i]);
                                }
                                printf("\n\n.GLOBALS %d",symT->local_num+1);
                                printf("\n\n.FUNCTIONS %d",symT->fun_num + 1 - 2);
                                printf("\n\n");
                                
                                pass = 2;
                                FILE *myfile1 = fopen(argv[2], "r");
                                yyin = myfile1;
                                yyparse();
                        }
                        
                }
        }

}


