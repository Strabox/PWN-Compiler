/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "pwn_parser.y"
/* $Id: pwn_parser.y,v 1.38 2015/05/19 20:10:08 ist176046 Exp $*/
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#line 14 "pwn_parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int                  i;			/* integer value */
  double               r;			/* real value */
  std::string          *s;			/* symbol name or string literal */
  cdk::basic_node      *node;		/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  basic_type 		   *type;		/* type nodes */
  pwn::variable_node     *lvalue;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 51 "pwn_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 52 "pwn_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tINTEGER 257
#define tIDENTIFIER 258
#define tSTRING 259
#define tREAL 260
#define tREPEAT 261
#define tIF 262
#define tPRINT 263
#define tPRINTLINE 264
#define tRETURN 265
#define tIMPORT 266
#define tLOCAL 267
#define tNOOB 268
#define tNEXT 269
#define tSTOP 270
#define tIFX 271
#define tELSE 272
#define tGE 273
#define tLE 274
#define tEQ 275
#define tNE 276
#define tUNARY 277
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   15,   15,    4,   16,   16,   11,   11,   11,
    6,    9,    9,    9,   10,   10,   10,   10,   10,   10,
   10,   10,    8,    8,    8,    8,    8,    8,    2,    2,
    2,    2,    2,    2,   13,   13,   14,   14,    3,    5,
    5,    5,    5,    7,    7,   23,   23,   23,   23,   19,
   19,   19,   19,   24,   24,   12,   12,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   20,   20,   21,   21,   17,   17,   22,   22,
   22,   22,
};
static const YYINT yylen[] = {                            2,
    1,    0,    1,    2,    1,    1,    2,    1,    1,    2,
    2,    2,    4,    6,    3,    5,    3,    7,    5,    2,
    4,    6,    7,    9,    7,    6,    8,    6,    5,    5,
    6,    6,    6,    6,    1,    0,    1,    3,    2,    5,
    4,    4,    3,    1,    0,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    2,    1,    2,    2,    2,    2,
    5,    7,    9,    2,    3,    2,    3,    1,    1,    1,
    2,    2,    2,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    1,    2,
    1,    3,    4,    3,    1,    0,    3,    1,    1,    4,
    4,    6,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,   48,   49,    0,   46,   47,    0,    8,
    3,    9,    0,    5,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   10,    4,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   37,    0,    0,    0,   50,
    0,   54,   52,   53,    0,    0,    0,    0,    0,   89,
    0,   69,    0,    0,    0,    0,   19,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   39,    0,   73,   72,
   71,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   90,
   55,    0,   34,   33,    0,    0,    0,    0,    0,   28,
   38,   94,    0,    0,    0,   87,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   78,   79,   80,    0,
    0,    0,    0,   26,    0,   25,    0,   23,    0,    0,
   44,    0,    0,    0,   56,   68,    6,    0,    0,    0,
    0,    0,    0,   93,    0,    0,  101,  100,    0,    0,
    0,    0,    0,   66,    0,   64,    0,   43,   11,   57,
    0,    7,    0,    0,   59,   58,   60,    0,   97,    0,
   27,   24,    0,    0,    0,   67,   65,    0,   42,   41,
    0,    0,  102,    0,    0,    0,   40,    0,    0,    0,
    0,    0,    0,    0,    0,   62,    0,   63,
};
static const YYINT yydgoto[] = {                          9,
  145,   10,   46,   11,  146,  147,  148,   12,  149,   13,
   14,  150,   47,   48,   15,  151,  113,  152,   62,   63,
  184,   64,   49,   65,
};
static const YYINT yysindex[] = {                       586,
  463,  788,   87,    0,    0, -238,    0,    0,    0,    0,
    0,    0,  -31,    0,  586, -235,   87, -228, -227,   87,
 -217, -211,  -14,   18,    0,    0,  -26,  -13,   23,   27,
   -5,   36,  -21, -171,   87,  411,   87, -170,   87,   87,
 -168,   87,  411,   87,   31,    0,   52,   64, -147,    0,
   78,    0,    0,    0,  411,  411,  411,  411,  411,    0,
  639,    0,   35,  -36, -139,   86,    0,   94,   95,   79,
   98,  639,  107,  411,   26,   87,    0,  764,    0,    0,
    0,  484,  296,  411,  411,  411,  411,  411,  411,  411,
  411,  411,  411,  411,  411,  411,  411,  411,  411,    0,
    0,  -55,    0,    0,  411,   26,  -51,  639,  706,    0,
    0,    0,  109,  515,   61,    0,  685,  685,  175,  175,
  175,  175,  175,  175,   65,   65,    0,    0,    0,  542,
  639,  587, -174,    0,  639,    0, -174,    0,  113,  116,
    0,  -57,  -56,   87,    0,    0,    0,   32,  105,  728,
  706,  196,  -92,    0,  411,  411,    0,    0,   26,   26,
  411,  411,  110,    0,  111,    0,  114,    0,    0,    0,
   54,    0,   55,  728,    0,    0,    0,  120,    0,  613,
    0,    0,  639,  125,  655,    0,    0,  -73,    0,    0,
   63,  411,    0,  411,  742,  126,    0,  639,  127,  -81,
  411,  411,  742,  639,  153,    0,  742,    0,
};
static const YYINT yyrindex[] = {                       197,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  198,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  143,    0,    0,  146,
    0,    0,  147,    0,  173,    0,  173,    0,  173,  173,
    0,  173,    0,  173,    0,    0,    0,  174,    0,    0,
   37,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  157,    0,  100,  130,   72,    0,    0,    0,    0,    0,
    0,  160,    0,    0,    1,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    9,    0,    0,    0,   17,   29,  162,  102,    0,
    0,    0,    0,  189,  166,    0,  -33,  -20,  291,  319,
  339,  369,  414,  450,  204,  244,    0,    0,    0,    0,
   62,    0,    0,    0,  181,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  102,
  102,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  187,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  102,    0,    0,    0,  191,    0,    0,
    0,    0,  -37,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  187,    0,    0,    0,  192,    0,  676,
    0,  211,    0,  194,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  -49,    0,  156,  242,   76,  118, -118,    0,    0,    0,
    0,  119,  277,    0,    0,    0,  106,  970, -121,    0,
 -187,    0, 1070,    0,
};
#define YYTABLESIZE 1221
static const YYINT yytable[] = {                         74,
   29,  164,  166,   95,   74,  133,  199,   74,   30,  137,
   74,  159,   75,   37,  205,  160,   32,   75,   44,   24,
   75,   95,   27,   75,   98,   74,  100,   25,   31,   29,
   30,  171,  173,   29,   36,   29,   29,   29,   75,   43,
   32,   30,   29,   30,   30,   30,   33,   34,   38,   32,
   30,   32,   32,   32,   99,  191,   41,   35,   32,   74,
   29,   31,   39,   31,   31,   31,   40,  109,   30,   99,
   31,  109,   75,   99,   99,   42,   32,   99,   99,   99,
   99,   99,   50,   99,   52,   53,   45,   67,   31,   70,
   74,   74,   75,   54,   92,   99,   99,   99,   99,   99,
  170,   96,   92,   75,   51,   92,   94,   76,   51,   51,
   77,   95,   51,   51,   51,   51,   51,   78,   51,  101,
   92,    7,    8,    5,  170,   97,  102,   99,    4,   99,
   51,   51,   70,   51,  103,  104,   70,   70,  106,  105,
   70,   70,   70,   70,   70,  200,   70,  107,  109,  154,
  110,  156,  161,  206,   92,  162,  168,  208,   70,   70,
   99,   70,   91,  169,   51,  178,   91,   91,  186,  187,
   91,   91,   91,   91,   91,  188,   91,  134,  189,  190,
  192,  136,  138,  194,  196,  202,  201,  197,   91,   91,
  203,   91,   70,  207,   51,   51,    2,    1,   88,  163,
  165,   20,   88,   88,   17,   15,   88,   88,   88,   88,
   88,   96,   88,   36,   35,   21,   94,   92,   16,   93,
   22,   95,   91,   70,   88,   88,   45,   88,  177,   98,
   74,  111,   96,   84,  181,  182,   76,   94,   92,   18,
   93,   76,   95,   75,   76,   96,   76,   76,   76,   12,
   13,   96,   14,   91,  176,   91,   26,   90,   88,    0,
  179,    0,   76,   76,    0,   76,   29,   29,  172,  174,
    0,    0,    0,    0,   30,   30,   77,    0,    0,    0,
    0,   77,   32,   32,   77,    0,   77,   77,   77,   88,
    0,    0,    0,    0,   31,   31,   76,    0,    0,    0,
   99,    0,   77,   77,    0,   77,    0,    0,    0,   99,
   99,   99,   99,   66,    0,   68,   69,    0,   71,   85,
   73,    0,    0,   83,    0,   92,    0,   76,   83,    0,
    0,   83,   96,   84,   83,   51,   77,   94,   92,    0,
   93,    0,   95,    0,   51,   51,   51,   51,    0,   83,
   83,   84,   83,    0,    0,   91,   84,   90,    0,   84,
    0,    0,   84,   70,    0,    0,    0,   77,    0,    0,
    0,   86,   70,   70,   70,   70,   86,   84,   84,   86,
   84,    0,   86,   83,    0,    0,    0,    0,  116,    0,
    0,    0,    0,   91,    0,    0,    0,   86,   86,    0,
   86,   85,   91,   91,   91,   91,   85,    0,    0,   85,
    0,   84,   85,    0,   83,    0,    0,    0,    0,   85,
    0,    0,    0,    0,    0,    0,    0,   85,   85,   88,
   85,   86,    0,    0,    0,    0,    0,    0,   88,   88,
   88,   88,   84,    0,    0,    0,   82,    0,    0,    0,
   58,   82,    0,   55,   82,   56,    0,   82,    0,  175,
    0,   85,   86,    0,    0,    0,    0,   76,   86,   87,
   88,   89,   82,   82,   60,   82,   76,   76,   76,   76,
    0,    0,   81,    0,    0,    0,    0,   81,    0,    0,
   81,    0,   85,   81,    0,   18,    0,    7,    8,    5,
    0,   59,    0,    0,    4,    0,   82,   77,   81,   81,
    0,   81,    0,    0,    0,    0,   77,   77,   77,   77,
   96,   84,   17,    0,  115,   94,   92,    0,   93,    0,
   95,    0,    0,    0,    0,    0,   57,   82,    0,    0,
    0,    0,   81,   91,    0,   90,    0,    0,    0,    0,
    0,   96,   84,    0,   83,    0,   94,   92,  155,   93,
    0,   95,    0,   83,   83,   83,   83,    0,   86,   87,
   88,   89,    0,   81,   91,    0,   90,    0,   96,   84,
    0,    0,   84,   94,   92,    0,   93,    0,   95,    0,
    0,   84,   84,   84,   84,    0,    0,    0,    0,    0,
    0,   91,   86,   90,    0,    0,    0,   85,    0,    0,
    0,   86,   86,   86,   86,    0,    0,    0,    6,    0,
    7,    8,    5,   96,   84,    0,    0,    4,   94,   92,
    0,   93,   85,   95,  157,    0,    0,    0,   85,    0,
    0,   85,   85,   85,   85,    3,   91,    0,   90,   96,
   84,    0,    0,    0,   94,   92,    0,   93,    0,   95,
    0,    0,    0,    0,    0,   85,    0,   50,   51,   52,
   53,    0,   91,    0,   90,   96,   84,   82,   54,  158,
   94,   92,    0,   93,    0,   95,   82,   82,   82,   82,
    0,   96,   84,    0,    0,  195,   94,   92,   91,   93,
   90,   95,    0,    0,    0,  193,    0,    0,    0,    0,
   85,    0,    0,   81,   91,   61,   90,    0,   61,    0,
   61,   96,   81,   81,   81,   81,   94,   92,    0,   93,
    0,   95,    0,    0,    0,    0,   85,    0,    0,   61,
    7,    8,    5,    0,   91,   58,   90,    4,   55,    0,
   56,    0,    0,    0,    0,    0,   86,   87,   88,   89,
    0,    0,   85,    0,    0,  144,   61,   58,    0,   60,
   55,    0,   56,    0,    0,    0,    0,    0,   85,    0,
    0,   58,    0,    0,   55,    0,   56,   86,   87,   88,
   89,   60,    0,    0,    0,    0,   59,    0,   61,    0,
   61,   61,    0,   58,  112,   60,   55,    0,   56,    0,
    0,    0,    0,    0,   86,   87,   88,   89,   59,    0,
   21,    0,    7,    8,    5,    0,    0,   60,  109,    4,
    0,   57,   59,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   20,    0,    0,
  109,    1,    2,   57,   59,    0,    0,    0,    0,   86,
   87,   88,   89,    0,  109,    0,    0,   57,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   86,   87,   88,   89,   57,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   86,   87,   88,   89,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   86,   87,   88,
   89,    0,   61,   61,   61,   61,   61,   61,    0,    0,
   61,    0,    0,   61,   61,   61,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   86,   87,   88,
   89,    0,   50,   51,   52,   53,  139,  140,    0,    0,
  141,    0,    0,   54,  142,  143,    0,    0,    0,    0,
    0,    0,    0,    0,   50,   51,   52,   53,  139,  140,
    0,    0,  141,    0,    0,   54,  142,  143,   50,   51,
   52,   53,  139,  140,    0,   61,    0,    0,    0,   54,
  142,  143,   72,    0,    0,    0,    0,    0,    0,    0,
   50,   51,   52,   53,   79,   80,   81,   82,   83,    0,
    0,   54,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  108,    0,    0,    0,  114,    0,    0,
    0,    0,    0,  117,  118,  119,  120,  121,  122,  123,
  124,  125,  126,  127,  128,  129,  130,  131,  132,   16,
   19,   22,   23,    0,  135,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   16,    0,   28,    0,    0,   31,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  114,  180,    0,    0,    0,    0,
  183,  185,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  198,    0,  183,    0,    0,    0,    0,    0,    0,
  204,  183,    0,    0,    0,    0,    0,    0,  153,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  167,    0,    0,    0,    0,    0,    0,
  153,
};
static const YYINT yycheck[] = {                         33,
    0,   59,   59,   41,   38,   61,  194,   41,    0,   61,
   44,  133,   33,   40,  202,  137,    0,   38,   40,  258,
   41,   59,  258,   44,   61,   59,   63,   59,    0,  258,
  258,  150,  151,   33,   61,   35,   36,   37,   59,   61,
  258,   33,   42,   35,   36,   37,  258,   62,   62,   33,
   42,   35,   36,   37,   91,  174,   62,   40,   42,   93,
   60,   33,   40,   35,   36,   37,   40,  123,   60,   33,
   42,  123,   93,   37,   38,   40,   60,   41,   42,   43,
   44,   45,  257,   47,  259,  260,  258,  258,   60,  258,
  124,   61,   41,  268,   33,   59,   60,   61,   62,   63,
  150,   37,   41,  124,   33,   44,   42,   44,   37,   38,
  258,   47,   41,   42,   43,   44,   45,   40,   47,  259,
   59,   35,   36,   37,  174,   91,   41,   91,   42,   93,
   59,   60,   33,   62,   41,   41,   37,   38,   41,   61,
   41,   42,   43,   44,   45,  195,   47,   41,  123,   41,
   75,   91,   40,  203,   93,   40,  125,  207,   59,   60,
  124,   62,   33,   59,   93,  258,   37,   38,   59,   59,
   41,   42,   43,   44,   45,   62,   47,  102,  125,  125,
   61,  106,  107,   59,  258,   59,   61,  125,   59,   60,
  272,   62,   93,   41,  123,  124,    0,    0,   33,  257,
  257,   59,   37,   38,   59,   59,   41,   42,   43,   44,
   45,   37,   47,   41,   41,   59,   42,   43,   59,   45,
   59,   47,   93,  124,   59,   60,  125,   62,   33,   41,
  264,   76,   37,   38,  159,  160,   33,   42,   43,   59,
   45,   38,   47,  264,   41,   59,   43,   44,   45,   59,
   59,   41,   59,  124,   59,   60,   15,   62,   93,   -1,
  155,   -1,   59,   60,   -1,   62,  266,  267,  151,  151,
   -1,   -1,   -1,   -1,  266,  267,   33,   -1,   -1,   -1,
   -1,   38,  266,  267,   41,   -1,   43,   44,   45,  124,
   -1,   -1,   -1,   -1,  266,  267,   93,   -1,   -1,   -1,
  264,   -1,   59,   60,   -1,   62,   -1,   -1,   -1,  273,
  274,  275,  276,   37,   -1,   39,   40,   -1,   42,  124,
   44,   -1,   -1,   33,   -1,  264,   -1,  124,   38,   -1,
   -1,   41,   37,   38,   44,  264,   93,   42,   43,   -1,
   45,   -1,   47,   -1,  273,  274,  275,  276,   -1,   59,
   60,   33,   62,   -1,   -1,   60,   38,   62,   -1,   41,
   -1,   -1,   44,  264,   -1,   -1,   -1,  124,   -1,   -1,
   -1,   33,  273,  274,  275,  276,   38,   59,   60,   41,
   62,   -1,   44,   93,   -1,   -1,   -1,   -1,   93,   -1,
   -1,   -1,   -1,  264,   -1,   -1,   -1,   59,   60,   -1,
   62,   33,  273,  274,  275,  276,   38,   -1,   -1,   41,
   -1,   93,   44,   -1,  124,   -1,   -1,   -1,   -1,  124,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,   60,  264,
   62,   93,   -1,   -1,   -1,   -1,   -1,   -1,  273,  274,
  275,  276,  124,   -1,   -1,   -1,   33,   -1,   -1,   -1,
   40,   38,   -1,   43,   41,   45,   -1,   44,   -1,  264,
   -1,   93,  124,   -1,   -1,   -1,   -1,  264,  273,  274,
  275,  276,   59,   60,   64,   62,  273,  274,  275,  276,
   -1,   -1,   33,   -1,   -1,   -1,   -1,   38,   -1,   -1,
   41,   -1,  124,   44,   -1,   33,   -1,   35,   36,   37,
   -1,   91,   -1,   -1,   42,   -1,   93,  264,   59,   60,
   -1,   62,   -1,   -1,   -1,   -1,  273,  274,  275,  276,
   37,   38,   60,   -1,   41,   42,   43,   -1,   45,   -1,
   47,   -1,   -1,   -1,   -1,   -1,  126,  124,   -1,   -1,
   -1,   -1,   93,   60,   -1,   62,   -1,   -1,   -1,   -1,
   -1,   37,   38,   -1,  264,   -1,   42,   43,   44,   45,
   -1,   47,   -1,  273,  274,  275,  276,   -1,  273,  274,
  275,  276,   -1,  124,   60,   -1,   62,   -1,   37,   38,
   -1,   -1,  264,   42,   43,   -1,   45,   -1,   47,   -1,
   -1,  273,  274,  275,  276,   -1,   -1,   -1,   -1,   -1,
   -1,   60,  264,   62,   -1,   -1,   -1,  124,   -1,   -1,
   -1,  273,  274,  275,  276,   -1,   -1,   -1,   33,   -1,
   35,   36,   37,   37,   38,   -1,   -1,   42,   42,   43,
   -1,   45,  264,   47,   93,   -1,   -1,   -1,  124,   -1,
   -1,  273,  274,  275,  276,   60,   60,   -1,   62,   37,
   38,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,   -1,   -1,   -1,  124,   -1,  257,  258,  259,
  260,   -1,   60,   -1,   62,   37,   38,  264,  268,   93,
   42,   43,   -1,   45,   -1,   47,  273,  274,  275,  276,
   -1,   37,   38,   -1,   -1,   41,   42,   43,   60,   45,
   62,   47,   -1,   -1,   -1,   93,   -1,   -1,   -1,   -1,
  124,   -1,   -1,  264,   60,   40,   62,   -1,   43,   -1,
   45,   37,  273,  274,  275,  276,   42,   43,   -1,   45,
   -1,   47,   -1,   -1,   -1,   -1,  124,   -1,   -1,   64,
   35,   36,   37,   -1,   60,   40,   62,   42,   43,   -1,
   45,   -1,   -1,   -1,   -1,   -1,  273,  274,  275,  276,
   -1,   -1,  124,   -1,   -1,   60,   91,   40,   -1,   64,
   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,  124,   -1,
   -1,   40,   -1,   -1,   43,   -1,   45,  273,  274,  275,
  276,   64,   -1,   -1,   -1,   -1,   91,   -1,  123,   -1,
  125,  126,   -1,   40,   41,   64,   43,   -1,   45,   -1,
   -1,   -1,   -1,   -1,  273,  274,  275,  276,   91,   -1,
   33,   -1,   35,   36,   37,   -1,   -1,   64,  123,   42,
   -1,  126,   91,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   -1,   -1,
  123,  266,  267,  126,   91,   -1,   -1,   -1,   -1,  273,
  274,  275,  276,   -1,  123,   -1,   -1,  126,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  273,  274,  275,  276,  126,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  273,  274,  275,  276,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  273,  274,  275,
  276,   -1,  257,  258,  259,  260,  261,  262,   -1,   -1,
  265,   -1,   -1,  268,  269,  270,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  273,  274,  275,
  276,   -1,  257,  258,  259,  260,  261,  262,   -1,   -1,
  265,   -1,   -1,  268,  269,  270,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  257,  258,  259,  260,  261,  262,
   -1,   -1,  265,   -1,   -1,  268,  269,  270,  257,  258,
  259,  260,  261,  262,   -1,   36,   -1,   -1,   -1,  268,
  269,  270,   43,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  257,  258,  259,  260,   55,   56,   57,   58,   59,   -1,
   -1,  268,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   74,   -1,   -1,   -1,   78,   -1,   -1,
   -1,   -1,   -1,   84,   85,   86,   87,   88,   89,   90,
   91,   92,   93,   94,   95,   96,   97,   98,   99,    0,
    1,    2,    3,   -1,  105,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   15,   -1,   17,   -1,   -1,   20,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  155,  156,   -1,   -1,   -1,   -1,
  161,  162,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  192,   -1,  194,   -1,   -1,   -1,   -1,   -1,   -1,
  201,  202,   -1,   -1,   -1,   -1,   -1,   -1,  109,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  144,   -1,   -1,   -1,   -1,   -1,   -1,
  151,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 277
#define YYUNDFTOKEN 304
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,"'#'","'$'","'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,
0,0,0,0,0,0,0,0,0,0,"';'","'<'","'='","'>'","'?'","'@'",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tINTEGER",
"tIDENTIFIER","tSTRING","tREAL","tREPEAT","tIF","tPRINT","tPRINTLINE","tRETURN",
"tIMPORT","tLOCAL","tNOOB","tNEXT","tSTOP","tIFX","tELSE","tGE","tLE","tEQ",
"tNE","tUNARY",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file : decls",
"file :",
"decls : decl",
"decls : decls decl",
"decl : outsideBlockDecl",
"insideBlockDecls : insideBlockDecl",
"insideBlockDecls : insideBlockDecls insideBlockDecl",
"outsideBlockDecl : funcDecl",
"outsideBlockDecl : funcDef",
"outsideBlockDecl : outBlockVarDecl ';'",
"insideBlockDecl : inBlockVarDecl ';'",
"inBlockVarDecl : type tIDENTIFIER",
"inBlockVarDecl : type tIDENTIFIER '=' expr",
"inBlockVarDecl : '<' type '>' tIDENTIFIER '=' expr",
"outBlockVarDecl : tLOCAL type tIDENTIFIER",
"outBlockVarDecl : tLOCAL type tIDENTIFIER '=' expr",
"outBlockVarDecl : tIMPORT type tIDENTIFIER",
"outBlockVarDecl : tLOCAL '<' type '>' tIDENTIFIER '=' expr",
"outBlockVarDecl : tIMPORT '<' type '>' tIDENTIFIER",
"outBlockVarDecl : type tIDENTIFIER",
"outBlockVarDecl : type tIDENTIFIER '=' expr",
"outBlockVarDecl : '<' type '>' tIDENTIFIER '=' expr",
"funcDef : tLOCAL type tIDENTIFIER '(' funcArgs ')' block",
"funcDef : tLOCAL type tIDENTIFIER '(' funcArgs ')' '=' literal block",
"funcDef : tLOCAL '!' tIDENTIFIER '(' funcArgs ')' block",
"funcDef : type tIDENTIFIER '(' funcArgs ')' block",
"funcDef : type tIDENTIFIER '(' funcArgs ')' '=' literal block",
"funcDef : '!' tIDENTIFIER '(' funcArgs ')' block",
"funcDecl : '!' tIDENTIFIER '(' funcArgs ')'",
"funcDecl : type tIDENTIFIER '(' funcArgs ')'",
"funcDecl : tLOCAL type tIDENTIFIER '(' funcArgs ')'",
"funcDecl : tLOCAL '!' tIDENTIFIER '(' funcArgs ')'",
"funcDecl : tIMPORT type tIDENTIFIER '(' funcArgs ')'",
"funcDecl : tIMPORT '!' tIDENTIFIER '(' funcArgs ')'",
"funcArgs : args",
"funcArgs :",
"args : arg",
"args : args ',' arg",
"arg : type tIDENTIFIER",
"block : '{' insideBlockDecls list returnable '}'",
"block : '{' insideBlockDecls returnable '}'",
"block : '{' list returnable '}'",
"block : '{' returnable '}'",
"returnable : tRETURN",
"returnable :",
"type : '#'",
"type : '$'",
"type : '*'",
"type : '%'",
"literal : tINTEGER",
"literal : strLiteral",
"literal : tREAL",
"literal : tNOOB",
"strLiteral : tSTRING",
"strLiteral : strLiteral tSTRING",
"list : stmt",
"list : list stmt",
"stmt : expr ';'",
"stmt : expr tPRINTLINE",
"stmt : expr '!'",
"stmt : tIF '(' expr ')' stmt",
"stmt : tIF '(' expr ')' stmt tELSE stmt",
"stmt : tREPEAT '(' optExpr ';' optExpr ';' optExpr ')' stmt",
"stmt : tSTOP ';'",
"stmt : tSTOP tINTEGER ';'",
"stmt : tNEXT ';'",
"stmt : tNEXT tINTEGER ';'",
"stmt : block",
"expr : literal",
"expr : functionCall",
"expr : '~' expr",
"expr : '-' expr",
"expr : '+' expr",
"expr : expr '&' expr",
"expr : expr '|' expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr tGE expr",
"expr : expr tLE expr",
"expr : expr tNE expr",
"expr : expr tEQ expr",
"expr : '[' expr ']'",
"expr : '(' expr ')'",
"expr : '@'",
"expr : lval '?'",
"expr : lval",
"expr : lval '=' expr",
"functionCall : tIDENTIFIER '(' exprArgs ')'",
"functionCall : tIDENTIFIER '(' ')'",
"optExpr : expr",
"optExpr :",
"exprArgs : expr ',' exprArgs",
"exprArgs : expr",
"lval : tIDENTIFIER",
"lval : lval '[' expr ']'",
"lval : functionCall '[' expr ']'",
"lval : '(' expr ')' '[' expr ']'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 56 "pwn_parser.y"
	{ compiler->ast(yystack.l_mark[0].sequence); }
break;
case 2:
#line 57 "pwn_parser.y"
	{ compiler->ast(new cdk::nil_node(LINE)); }
break;
case 3:
#line 60 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node); }
break;
case 4:
#line 61 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node,yystack.l_mark[-1].sequence); }
break;
case 5:
#line 64 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 6:
#line 68 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node); }
break;
case 7:
#line 69 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node,yystack.l_mark[-1].sequence); }
break;
case 8:
#line 73 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 9:
#line 74 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 10:
#line 75 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 11:
#line 79 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 12:
#line 85 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,true,false,false,yystack.l_mark[-1].type,yystack.l_mark[0].s,NULL); }
break;
case 13:
#line 86 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,true,false,false,yystack.l_mark[-3].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression); }
break;
case 14:
#line 88 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,true,false,true,yystack.l_mark[-4].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression); }
break;
case 15:
#line 93 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,true,false,false,yystack.l_mark[-1].type,yystack.l_mark[0].s,NULL); }
break;
case 16:
#line 94 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,true,false,false,yystack.l_mark[-3].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression); }
break;
case 17:
#line 95 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,false,true,false,yystack.l_mark[-1].type,yystack.l_mark[0].s,NULL); }
break;
case 18:
#line 97 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,true,false,true,yystack.l_mark[-4].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression); }
break;
case 19:
#line 98 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,false,true,true,yystack.l_mark[-2].type,yystack.l_mark[0].s,NULL); }
break;
case 20:
#line 100 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,false,false,false,yystack.l_mark[-1].type,yystack.l_mark[0].s,NULL); }
break;
case 21:
#line 101 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,false,false,false,yystack.l_mark[-3].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression); }
break;
case 22:
#line 103 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,false,false,false,true,yystack.l_mark[-4].type,yystack.l_mark[-2].s,yystack.l_mark[0].expression); }
break;
case 23:
#line 111 "pwn_parser.y"
	{ yyval.node = new pwn::def_function_node(LINE,true,yystack.l_mark[-5].type,yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,NULL,yystack.l_mark[0].node); }
break;
case 24:
#line 112 "pwn_parser.y"
	{ yyval.node = new pwn::def_function_node(LINE,true,yystack.l_mark[-7].type,yystack.l_mark[-6].s,yystack.l_mark[-4].sequence,yystack.l_mark[-1].expression,yystack.l_mark[0].node); }
break;
case 25:
#line 113 "pwn_parser.y"
	{ yyval.node = new pwn::def_function_node(LINE,true,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,NULL,yystack.l_mark[0].node); }
break;
case 26:
#line 114 "pwn_parser.y"
	{ yyval.node = new pwn::def_function_node(LINE,false,yystack.l_mark[-5].type,yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,NULL,yystack.l_mark[0].node); }
break;
case 27:
#line 115 "pwn_parser.y"
	{ yyval.node = new pwn::def_function_node(LINE,false,yystack.l_mark[-7].type,yystack.l_mark[-6].s,yystack.l_mark[-4].sequence,yystack.l_mark[-1].expression,yystack.l_mark[0].node); }
break;
case 28:
#line 116 "pwn_parser.y"
	{ yyval.node = new pwn::def_function_node(LINE,false,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-4].s,yystack.l_mark[-2].sequence,NULL,yystack.l_mark[0].node); }
break;
case 29:
#line 120 "pwn_parser.y"
	{ yyval.node = new pwn::decl_function_node(LINE,false,false,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-3].s,yystack.l_mark[-1].sequence,NULL); }
break;
case 30:
#line 121 "pwn_parser.y"
	{ yyval.node = new pwn::decl_function_node(LINE,false,false,yystack.l_mark[-4].type,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence,NULL); }
break;
case 31:
#line 122 "pwn_parser.y"
	{ yyval.node = new pwn::decl_function_node(LINE,true,false,yystack.l_mark[-4].type,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence,NULL); }
break;
case 32:
#line 123 "pwn_parser.y"
	{ yyval.node = new pwn::decl_function_node(LINE,true,false,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-3].s,yystack.l_mark[-1].sequence,NULL); }
break;
case 33:
#line 124 "pwn_parser.y"
	{ yyval.node = new pwn::decl_function_node(LINE,false,true,yystack.l_mark[-4].type,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence,NULL); }
break;
case 34:
#line 125 "pwn_parser.y"
	{ yyval.node = new pwn::decl_function_node(LINE,false,true,new basic_type(0,basic_type::TYPE_VOID),yystack.l_mark[-3].s,yystack.l_mark[-1].sequence,NULL); }
break;
case 35:
#line 129 "pwn_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 36:
#line 130 "pwn_parser.y"
	{ yyval.sequence = NULL; }
break;
case 37:
#line 134 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node); }
break;
case 38:
#line 135 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].node,yystack.l_mark[-2].sequence); }
break;
case 39:
#line 139 "pwn_parser.y"
	{ yyval.node = new pwn::variable_decl_node(LINE,true,true,false,false,yystack.l_mark[-1].type,yystack.l_mark[0].s,NULL); }
break;
case 40:
#line 144 "pwn_parser.y"
	{ yyval.node = new pwn::block_node(LINE,yystack.l_mark[-3].sequence,yystack.l_mark[-2].sequence,yystack.l_mark[-1].node);  }
break;
case 41:
#line 145 "pwn_parser.y"
	{ yyval.node = new pwn::block_node(LINE,yystack.l_mark[-2].sequence,NULL,yystack.l_mark[-1].node); }
break;
case 42:
#line 146 "pwn_parser.y"
	{ yyval.node = new pwn::block_node(LINE,NULL,yystack.l_mark[-2].sequence,yystack.l_mark[-1].node); }
break;
case 43:
#line 147 "pwn_parser.y"
	{ yyval.node = new pwn::block_node(LINE,NULL,NULL,yystack.l_mark[-1].node); }
break;
case 44:
#line 150 "pwn_parser.y"
	{ yyval.node = new pwn::return_node(LINE); }
break;
case 45:
#line 151 "pwn_parser.y"
	{ yyval.node = NULL; }
break;
case 46:
#line 155 "pwn_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_INT); }
break;
case 47:
#line 156 "pwn_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_STRING); }
break;
case 48:
#line 157 "pwn_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); }
break;
case 49:
#line 158 "pwn_parser.y"
	{ yyval.type = new basic_type(8, basic_type::TYPE_DOUBLE); }
break;
case 50:
#line 162 "pwn_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 51:
#line 163 "pwn_parser.y"
	{ yyval.expression = new cdk::string_node(LINE , yystack.l_mark[0].s); }
break;
case 52:
#line 164 "pwn_parser.y"
	{ yyval.expression = new cdk::double_node(LINE, yystack.l_mark[0].r); }
break;
case 53:
#line 165 "pwn_parser.y"
	{ yyval.expression = new pwn::noob_node(LINE); }
break;
case 54:
#line 169 "pwn_parser.y"
	{ yyval.s = yystack.l_mark[0].s; }
break;
case 55:
#line 170 "pwn_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[-1].s + *yystack.l_mark[0].s); }
break;
case 56:
#line 176 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 57:
#line 177 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 58:
#line 181 "pwn_parser.y"
	{ yyval.node = new pwn::evaluation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 59:
#line 182 "pwn_parser.y"
	{ yyval.node = new pwn::printline_node(LINE, yystack.l_mark[-1].expression); }
break;
case 60:
#line 183 "pwn_parser.y"
	{ yyval.node = new pwn::print_node(LINE, yystack.l_mark[-1].expression); }
break;
case 61:
#line 184 "pwn_parser.y"
	{ yyval.node = new cdk::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 62:
#line 185 "pwn_parser.y"
	{ yyval.node = new cdk::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].node, yystack.l_mark[0].node); }
break;
case 63:
#line 186 "pwn_parser.y"
	{ yyval.node = new pwn::repeat_node(LINE, yystack.l_mark[-6].expression, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 64:
#line 187 "pwn_parser.y"
	{ yyval.node = new pwn::stop_node(LINE); }
break;
case 65:
#line 188 "pwn_parser.y"
	{ yyval.node = new pwn::stop_node(LINE,new cdk::integer_node(LINE,yystack.l_mark[-1].i)); }
break;
case 66:
#line 189 "pwn_parser.y"
	{ yyval.node = new pwn::next_node(LINE); }
break;
case 67:
#line 190 "pwn_parser.y"
	{ yyval.node = new pwn::next_node(LINE,new cdk::integer_node(LINE,yystack.l_mark[-1].i)); }
break;
case 68:
#line 191 "pwn_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 69:
#line 194 "pwn_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 70:
#line 195 "pwn_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 71:
#line 196 "pwn_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 72:
#line 197 "pwn_parser.y"
	{ yyval.expression = new pwn::symmetric_node(LINE,yystack.l_mark[0].expression); }
break;
case 73:
#line 198 "pwn_parser.y"
	{ yyval.expression = new pwn::identity_node(LINE,yystack.l_mark[0].expression); }
break;
case 74:
#line 199 "pwn_parser.y"
	{ yyval.expression = new pwn::and_node(LINE,yystack.l_mark[-2].expression,yystack.l_mark[0].expression); }
break;
case 75:
#line 200 "pwn_parser.y"
	{ yyval.expression = new pwn::or_node(LINE,yystack.l_mark[-2].expression,yystack.l_mark[0].expression); }
break;
case 76:
#line 201 "pwn_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 77:
#line 202 "pwn_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 78:
#line 203 "pwn_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 79:
#line 204 "pwn_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 80:
#line 205 "pwn_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 81:
#line 206 "pwn_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 82:
#line 207 "pwn_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 83:
#line 208 "pwn_parser.y"
	{ yyval.expression = new cdk::ge_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 84:
#line 209 "pwn_parser.y"
	{ yyval.expression = new cdk::le_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 85:
#line 210 "pwn_parser.y"
	{ yyval.expression = new cdk::ne_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 86:
#line 211 "pwn_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 87:
#line 212 "pwn_parser.y"
	{ yyval.expression = new pwn::memory_alloc_node(LINE,yystack.l_mark[-1].expression); }
break;
case 88:
#line 213 "pwn_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 89:
#line 214 "pwn_parser.y"
	{ yyval.expression = new pwn::read_node(LINE); }
break;
case 90:
#line 215 "pwn_parser.y"
	{ yyval.expression = new pwn::address_node(LINE,yystack.l_mark[-1].lvalue); }
break;
case 91:
#line 216 "pwn_parser.y"
	{ yyval.expression = new pwn::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 92:
#line 217 "pwn_parser.y"
	{ yyval.expression = new pwn::assignment_node(LINE, yystack.l_mark[-2].lvalue, yystack.l_mark[0].expression); }
break;
case 93:
#line 220 "pwn_parser.y"
	{ yyval.expression = new pwn::function_call_node(LINE,yystack.l_mark[-3].s,yystack.l_mark[-1].sequence); }
break;
case 94:
#line 221 "pwn_parser.y"
	{ yyval.expression = new pwn::function_call_node(LINE,yystack.l_mark[-2].s,NULL); }
break;
case 95:
#line 225 "pwn_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 96:
#line 226 "pwn_parser.y"
	{ yyval.expression = NULL; }
break;
case 97:
#line 231 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[-2].expression,yystack.l_mark[0].sequence); }
break;
case 98:
#line 232 "pwn_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE,yystack.l_mark[0].expression); }
break;
case 99:
#line 236 "pwn_parser.y"
	{ yyval.lvalue = new pwn::variable_node(LINE, yystack.l_mark[0].s); }
break;
case 100:
#line 237 "pwn_parser.y"
	{ yyval.lvalue = new pwn::index_node(LINE,yystack.l_mark[-3].lvalue,yystack.l_mark[-1].expression); }
break;
case 101:
#line 238 "pwn_parser.y"
	{ yyval.lvalue = new pwn::index_node(LINE,yystack.l_mark[-3].expression,yystack.l_mark[-1].expression); }
break;
case 102:
#line 239 "pwn_parser.y"
	{ yyval.lvalue = new pwn::index_node(LINE,yystack.l_mark[-4].expression,yystack.l_mark[-1].expression); }
break;
#line 1237 "pwn_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
