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
extern YYSTYPE yylval;
