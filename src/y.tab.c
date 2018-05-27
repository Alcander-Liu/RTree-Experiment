/* A Bison parser, made by GNU Bison 1.875b.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

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
     ARRAY = 258,
     BOX = 259,
     END = 260,
     GTGT = 261,
     LABEL = 262,
     LABELS = 263,
     LTLT = 264,
     NUMBER = 265,
     POSITIONER = 266,
     RECT = 267,
     SIGN = 268,
     TECH = 269,
     TRANSFORM = 270,
     USE = 271,
     WORD = 272
   };
#endif
#define ARRAY 258
#define BOX 259
#define END 260
#define GTGT 261
#define LABEL 262
#define LABELS 263
#define LTLT 264
#define NUMBER 265
#define POSITIONER 266
#define RECT 267
#define SIGN 268
#define TECH 269
#define TRANSFORM 270
#define USE 271
#define WORD 272




/* Copy the first part of user declarations.  */
#line 18 "y.spec"

# include "options.h"
# include <stdio.h>
# include "assert.h"
# include <ctype.h>
# include "macros.h"
# include "index.h"

# ifndef	lint
	static	char	yspecSccsid[] = "%W% %G%";
# endif	lint

# ifdef GRAPHICS
#	define UNIX
#	include "/jb/ingres/toni/cad/lib/mfb.h"
# endif

/* character types */
# define LETTER		1001
# define DIGIT		1002
# define WHITESPACE		1003

struct layertab
{
	char *name;
	char *letter;
};

struct
{
	char *string;
	int token;
} Keywords[] =
{
	"array",	ARRAY,
	"box",		BOX,
	"end",		END,
	">>",		GTGT,
	"<<",		LTLT,
	"labels",	LABELS,
	"label",	LABEL,
	"positioner",	POSITIONER,
	"rect",		RECT,
	"tech",		TECH,
	"transform",	TRANSFORM,
	"use",		USE,
	NULL,		0
};

struct layertab Layers[] =
{
	"polysilicon",		"p",
	"diffusion",		"d",
	"metal",		"m",
	"implant",		"i",
	"buried_contact",	"b",
	"cut",			"c",
	"overglass",		"o",
	"errors",		"e",
	"all",			"-",
	NULL,			0
};

FILE *Infile;
char Layer[30], Technology[20];
int tokenval;
char Tokenstring[80], label[20], subname[20];
int x1, y1, x2, y2, side, t[3][2];
int axlo, axhi, axsep, aylo, ayhi, aysep;
int vFeature[256];
int iFeatureIndex = 0;


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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 194 "y.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   74

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  18
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  39
/* YYNRULES -- Number of rules. */
#define YYNRULES  51
/* YYNRULES -- Number of states. */
#define YYNSTATES  91

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   272

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
      15,    16,    17
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     4,     5,     6,     7,     8,     9,    22,
      25,    28,    31,    33,    36,    37,    40,    44,    48,    49,
      54,    55,    57,    60,    61,    65,    67,    70,    74,    75,
      76,    77,    78,    79,    92,    93,    95,    98,   100,   102,
     107,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      27,     0,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      10,    20,    10,    21,    10,    22,    10,    23,    10,    24,
      10,    -1,     9,    43,    -1,    16,    46,    -1,    11,    44,
      -1,    25,    -1,    26,    25,    -1,    -1,    26,    28,    -1,
      45,    26,    28,    -1,     9,     5,     6,    -1,    -1,    17,
      30,     6,    31,    -1,    -1,    32,    -1,    31,    32,    -1,
      -1,    12,    33,    34,    -1,    10,    -1,    34,    10,    -1,
       8,     6,    42,    -1,    -1,    -1,    -1,    -1,    -1,     7,
      17,    37,    10,    38,    10,    39,    10,    40,    10,    41,
      10,    -1,    -1,    36,    -1,    42,    36,    -1,    29,    -1,
      35,    -1,    10,    10,    10,    10,    -1,    14,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    47,    19,    15,    10,    48,    10,    49,    10,    50,
      10,    51,    10,    52,    10,    53,     4,    10,    54,    10,
      55,    10,    56,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    95,    95,    97,    98,    99,   100,   101,    96,   104,
     105,   106,   108,   109,   111,   112,   113,   115,   117,   117,
     120,   121,   122,   124,   124,   127,   128,   133,   135,   136,
     137,   138,   139,   135,   145,   146,   147,   149,   150,   152,
     157,   160,   166,   167,   168,   169,   170,   171,   173,   174,
     175,   159
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ARRAY", "BOX", "END", "GTGT", "LABEL", 
  "LABELS", "LTLT", "NUMBER", "POSITIONER", "RECT", "SIGN", "TECH", 
  "TRANSFORM", "USE", "WORD", "$accept", "arrayx", "@1", "@2", "@3", "@4", 
  "@5", "block", "body", "celldef", "endline", "geomblock", "@6", 
  "geomlist", "geomline", "@7", "FEATURE", "labelblock", "labelline", 
  "@8", "@9", "@10", "@11", "@12", "labellist", "ltltblock", 
  "positionerblock", "techline", "useblock", "@13", "@14", "@15", "@16", 
  "@17", "@18", "@19", "@20", "@21", "@22", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    18,    19,    20,    21,    22,    23,    24,    19,    25,
      25,    25,    26,    26,    27,    27,    27,    28,    30,    29,
      31,    31,    31,    33,    32,    34,    34,    35,    37,    38,
      39,    40,    41,    36,    42,    42,    42,    43,    43,    44,
      45,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    46
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     0,     0,     0,     0,     0,    12,     2,
       2,     2,     1,     2,     0,     2,     3,     3,     0,     4,
       0,     1,     2,     0,     3,     1,     2,     3,     0,     0,
       0,     0,     0,    12,     0,     1,     2,     1,     1,     4,
       2,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    24
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      14,     0,     0,     0,     0,    12,     0,     0,     0,     0,
      18,    37,    38,     9,     0,    11,    40,    41,    10,     0,
      13,    15,     1,     0,    34,     0,     0,     2,     0,    16,
       0,    35,    27,    20,     0,     0,     0,    17,    28,    36,
      23,    19,    21,    39,     3,     0,     0,     0,    22,     0,
      42,    29,    25,    24,     4,     0,     0,    26,     0,    43,
      30,     5,     0,     0,     0,    44,    31,     6,     0,     0,
       0,    45,    32,     7,     0,     0,     0,    46,    33,     8,
       0,    47,     0,     0,    48,     0,    49,     0,    50,     0,
      51
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,    36,    49,    58,    64,    70,    76,     5,     6,     7,
      21,    11,    25,    41,    42,    47,    53,    12,    31,    46,
      56,    63,    69,    75,    32,    13,    15,     8,    18,    27,
      55,    62,    68,    74,    80,    82,    85,    87,    89
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -13
static const yysigned_char yypact[] =
{
       0,    -5,    -8,   -12,   -11,   -13,    -1,     7,     9,    13,
     -13,   -13,   -13,   -13,    11,   -13,   -13,   -13,   -13,    -4,
     -13,   -13,   -13,    -1,    15,    17,    14,    23,    21,   -13,
      12,   -13,    15,    16,    20,    22,    18,   -13,   -13,   -13,
     -13,    16,   -13,   -13,   -13,    24,    25,    26,   -13,    27,
     -13,   -13,   -13,    28,   -13,    29,    30,   -13,    31,   -13,
     -13,   -13,    32,    33,    34,   -13,   -13,   -13,    35,    36,
      37,   -13,   -13,   -13,    38,    39,    40,   -13,   -13,   -13,
      41,   -13,    48,    43,   -13,    44,   -13,    45,   -13,    46,
     -13
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -13,   -13,   -13,   -13,   -13,   -13,   -13,    -6,    49,   -13,
       8,   -13,   -13,   -13,    19,   -13,   -13,   -13,    42,   -13,
     -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,
     -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      20,    28,    14,     9,     9,    16,    17,    22,    19,     1,
       2,     2,    10,    10,     3,     4,     4,    20,     1,    24,
       2,    26,    30,    33,    34,     4,    35,    37,    40,    38,
      43,    29,    44,    45,    50,    51,    52,    54,    57,    59,
      60,    61,    65,    66,    67,    71,    72,    73,    77,    78,
      79,    81,    83,    84,    86,    88,    90,    23,     0,     0,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    39
};

static const yysigned_char yycheck[] =
{
       6,     5,    10,     8,     8,    17,    17,     0,     9,     9,
      11,    11,    17,    17,    14,    16,    16,    23,     9,     6,
      11,    10,     7,     6,    10,    16,     3,     6,    12,    17,
      10,    23,    10,    15,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,     4,    10,    10,    10,    10,     8,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     9,    11,    14,    16,    25,    26,    27,    45,     8,
      17,    29,    35,    43,    10,    44,    17,    17,    46,     9,
      25,    28,     0,    26,     6,    30,    10,    47,     5,    28,
       7,    36,    42,     6,    10,     3,    19,     6,    17,    36,
      12,    31,    32,    10,    10,    15,    37,    33,    32,    20,
      10,    10,    10,    34,    10,    48,    38,    10,    21,    10,
      10,    10,    49,    39,    22,    10,    10,    10,    50,    40,
      23,    10,    10,    10,    51,    41,    24,    10,    10,    10,
      52,    10,    53,     4,    10,    54,    10,    55,    10,    56,
      10
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1


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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
        case 3:
#line 97 "y.spec"
    { axlo = tokenval; }
    break;

  case 4:
#line 98 "y.spec"
    { axhi = tokenval; }
    break;

  case 5:
#line 99 "y.spec"
    { axsep = tokenval; }
    break;

  case 6:
#line 100 "y.spec"
    { aylo = tokenval; }
    break;

  case 7:
#line 101 "y.spec"
    { ayhi = tokenval; }
    break;

  case 8:
#line 102 "y.spec"
    { aysep = tokenval; }
    break;

  case 18:
#line 117 "y.spec"
    { getlayer(Tokenstring); }
    break;

  case 23:
#line 124 "y.spec"
    { iFeatureIndex = 0;}
    break;

  case 24:
#line 125 "y.spec"
    { ProcessBox( vFeature, iFeatureIndex ); }
    break;

  case 25:
#line 127 "y.spec"
    { vFeature[iFeatureIndex++] = tokenval; }
    break;

  case 26:
#line 129 "y.spec"
    {
			vFeature[iFeatureIndex++] = tokenval;
		}
    break;

  case 28:
#line 135 "y.spec"
    {strcpy(label, Tokenstring);}
    break;

  case 29:
#line 136 "y.spec"
    {x1 = tokenval;}
    break;

  case 30:
#line 137 "y.spec"
    {y1 = tokenval;}
    break;

  case 31:
#line 138 "y.spec"
    {x2 = tokenval;}
    break;

  case 32:
#line 139 "y.spec"
    {y2 = tokenval;}
    break;

  case 33:
#line 141 "y.spec"
    {
			side = tokenval;
		  }
    break;

  case 40:
#line 157 "y.spec"
    { strcpy(Technology, Tokenstring); }
    break;

  case 41:
#line 160 "y.spec"
    {
			strcpy(subname, Tokenstring);
			axlo = axhi = axsep = aylo = ayhi = aysep = 0;
		  }
    break;

  case 42:
#line 166 "y.spec"
    {t[0][0] = tokenval;}
    break;

  case 43:
#line 167 "y.spec"
    {t[1][0] = tokenval;}
    break;

  case 44:
#line 168 "y.spec"
    {t[2][0] = tokenval;}
    break;

  case 45:
#line 169 "y.spec"
    {t[0][1] = tokenval;}
    break;

  case 46:
#line 170 "y.spec"
    {t[1][1] = tokenval;}
    break;

  case 47:
#line 171 "y.spec"
    {t[2][1] = tokenval;}
    break;

  case 48:
#line 173 "y.spec"
    {x1 = tokenval;}
    break;

  case 49:
#line 174 "y.spec"
    {y1 = tokenval;}
    break;

  case 50:
#line 175 "y.spec"
    {x2 = tokenval;}
    break;

  case 51:
#line 177 "y.spec"
    {
			int xx1, xx2, yy1, yy2;
			y2 = tokenval;
			xx1 = x1*t[0][0]+y1*t[1][0]+t[2][0];
			yy1 = x1*t[0][1]+y1*t[1][1]+t[2][1];
			xx2 = x2*t[0][0]+y2*t[1][0]+t[2][0];
			yy2 = x2*t[0][1]+y2*t[1][1]+t[2][1];
			ProcessBox(xx1, yy1, xx2, yy2);
		  }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1305 "y.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 188 "y.spec"
 /* programs section */

/* derived from scan.c	1.4 6/22/82 */

yylex()
{
	int c, c_type, token_type, lim;
	char *w;

	w = Tokenstring;
	while ((c_type = type(c = getc(Infile))) == WHITESPACE)
		;
	*w++ = c;

	switch (c_type)
	{
	case '+':
	case '-':
		token_type = SIGN;
		break;
	case DIGIT:
		token_type = NUMBER;
		break;
	case EOF:
		*w = '\0';
		return EOF;
	default:
		token_type = WORD;
		break;
	}

	lim = 80;
	while (--lim > 0)
	{
		c_type = type(c = *w++ = getc(Infile));
		if (c_type == WHITESPACE || c == EOF)
		{
			*--w = '\0';
			if (token_type == WORD)
				return (checkword(Tokenstring));
			else if (token_type == NUMBER)
			{
				/* evaluate number string */
				sscanf(Tokenstring, "%ld", &tokenval);
				return (NUMBER);
			}
			else
				return (token_type);
		}
		else if (token_type == NUMBER && c_type != DIGIT)
			token_type = WORD;
		else if (token_type == SIGN)
		{
			if (c_type == DIGIT)
				token_type = NUMBER;
			else
				token_type = WORD;
		}
	}
	error("scan: token too long");
	return (EOF);
}

type(c)		/* return type of ascii character */
int c;
{
	if (isspace(c))
		return(WHITESPACE);
	else if (isalpha(c))
		return(LETTER);
	else if (isdigit(c))
		return(DIGIT);
	else
		return(c);
}

int
checkword(w)
char *w;
{
	int i;
	char *s;

	for (i = 0; (s = Keywords[i].string) != NULL; i++)
	{
		if (!strcmp(w, s))
			return (Keywords[i].token);
	}
	return(WORD);
}


yyerror(string)
char *string;
{
#	ifdef GRAPHICS
		EndGraphics();
#	endif
	Tokenstring[79] = '\0';
	fflush(stdout);
	fprintf(stderr, "Error: %s token=\"%s\"\n", string, Tokenstring);
	fflush(stderr);
}


getlayer(n)
char *n;
{
	int i;
	char *s;

	for (i = 0; (s = Layers[i].name) != NULL; i++)
	{
		if (!strcmp(n, s))
		{
			strcpy(Layer, Layers[i].letter);
			return;
		}
	}
#	ifdef GRAPHICS
		EndGraphics();
#	endif
	error("getlayer: layer name not found");
}

ProcessBox( vFeature, iFeatureNum)
int *vFeature;
int iFeatureNum;
{
	/*
	int iFeatureIndex = 0;
	for ( iFeatureIndex = 0; iFeatureIndex<iFeatureNum; iFeatureIndex++ )
		printf("%d ", vFeature[iFeatureIndex] );
	printf("\n");*/

	static int flag=0, count=0, result;
	int tid;
	struct Rect r;

	if (Phase == 1)
	{
		count++;

		if ( NUMDIMS!=iFeatureNum)
		{
			printf( "Feature dimension of the input data is not equal with NUMDIMS\n" );
			printf( "Feature dimension is %d;\tNUMDIMS is %d\n", iFeatureNum, NUMDIMS );
			exit(0);
		}


		if (!flag)
		{
			flag = 1;

			for ( iFeatureIndex=0; iFeatureIndex<NUMDIMS; iFeatureIndex++ )
			{
				CoverAll.boundary[iFeatureIndex] = vFeature[iFeatureIndex];
				CoverAll.boundary[iFeatureIndex+NUMDIMS] = vFeature[iFeatureIndex]+1;
			}
		}
		else
		{
			for ( iFeatureIndex=0; iFeatureIndex<NUMDIMS; iFeatureIndex++ )
			{
				CoverAll.boundary[iFeatureIndex] = min( vFeature[iFeatureIndex], CoverAll.boundary[iFeatureIndex] );
				CoverAll.boundary[iFeatureIndex+NUMDIMS] = max( vFeature[iFeatureIndex]+1, CoverAll.boundary[iFeatureIndex+NUMDIMS] );
			}
		}
	}
	else if (Phase == 2)
	{
		if ( NUMDIMS!=iFeatureNum)
		{
			printf( "Feature dimension of the input data is not equal with NUMDIMS\n" );
			printf( "Feature dimension is %d;\tNUMDIMS is %d\n", iFeatureNum, NUMDIMS );
			exit(0);
		}

		for ( iFeatureIndex=0; iFeatureIndex<NUMDIMS; iFeatureIndex++ )
		{
			r.boundary[iFeatureIndex] = vFeature[iFeatureIndex];
			r.boundary[iFeatureIndex+NUMDIMS] = vFeature[iFeatureIndex]+1;
		}

		StatFlag = TRUE;
		StartClock();
		InsertRect(&r, tid, &Root, 0);
		StopClock();
		StatFlag = FALSE;
	}
	else if (Phase == 3)
	{
		if ( NUMDIMS!=iFeatureNum)
		{
			printf( "Feature dimension of the input data is not equal with NUMDIMS\n" );
			printf( "Feature dimension is %d;\tNUMDIMS is %d\n", iFeatureNum, NUMDIMS );
			exit(0);
		}

		for ( iFeatureIndex=0; iFeatureIndex<NUMDIMS; iFeatureIndex++ )
		{
			r.boundary[iFeatureIndex] = vFeature[iFeatureIndex];
			r.boundary[iFeatureIndex+NUMDIMS] = vFeature[iFeatureIndex]+1;
		}


		/* Do searches using the index */
		//printf("Search rect:\n");
		//PrintRect2(&r);
		HitCount += Search(Root, &r);
		SearchCount++;
	}
}


