%{
// $Id: pwn_parser.y,v 1.38 2015/05/19 20:10:08 ist176046 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                  i;			/* integer value */
  double               r;			/* real value */
  std::string          *s;			/* symbol name or string literal */
  cdk::basic_node      *node;		/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  basic_type 		   *type;		/* type nodes */
  pwn::variable_node     *lvalue;
};

%token <i> tINTEGER
%token <s> tIDENTIFIER tSTRING
%token <r> tREAL
%token tREPEAT tIF tPRINT tPRINTLINE tRETURN tIMPORT tLOCAL tNOOB
%token tNEXT tSTOP

%nonassoc tIFX
%nonassoc tELSE


%right '='
%left '&' '|'
%left tGE tLE tEQ tNE '>' '<'
%left '+' '-' 
%left '*' '/' '%'
%nonassoc '~' tUNARY

%type <node> stmt file funcDecl arg decl block insideBlockDecl returnable
%type <node> funcDef inBlockVarDecl outBlockVarDecl outsideBlockDecl
%type <sequence> list funcArgs args decls insideBlockDecls exprArgs
%type <expression> expr literal functionCall optExpr
%type <lvalue> lval
%type <type> type 
%type <s> strLiteral

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

// PWN file has declarations or empty and do nothing.
file : decls { compiler->ast($1); }
	 |		 { compiler->ast(new cdk::nil_node(LINE)); }
	 ;

decls : decl 	   { $$ = new cdk::sequence_node(LINE,$1); }
      | decls decl { $$ = new cdk::sequence_node(LINE,$2,$1); }
      ;

decl : outsideBlockDecl { $$ = $1; }
     ;

/* Only variables can be declarated inside blocks. */
insideBlockDecls : insideBlockDecl 					 { $$ = new cdk::sequence_node(LINE,$1); } 
				 | insideBlockDecls insideBlockDecl  { $$ = new cdk::sequence_node(LINE,$2,$1); }
				 ;

/* Available declarations outside blocks. */
outsideBlockDecl : funcDecl              { $$ = $1; }
				 | funcDef         		 { $$ = $1; }
				 | outBlockVarDecl ';'   { $$ = $1; }
				 ;
				 
/* Only variables can be declarated inside blocks. */				 
insideBlockDecl : inBlockVarDecl ';'	 { $$ = $1; }
                ;

/* ===================== Variable Stuff ============================= */

/* Available variable declarations inside blocks. */
inBlockVarDecl : type tIDENTIFIER                   		{ $$ = new pwn::variable_decl_node(LINE,false,true,false,false,$1,$2,NULL); }
			   | type tIDENTIFIER '=' expr         			{ $$ = new pwn::variable_decl_node(LINE,false,true,false,false,$1,$2,$4); }
			   /* vvvvvvv Constants vvvvvv */
			   | '<' type '>' tIDENTIFIER '=' expr 			{ $$ = new pwn::variable_decl_node(LINE,false,true,false,true,$2,$4,$6); }
			   ;

/* Available variable declarations outside blocks. 
  NOTE: Cant initialize imported variables!!!! */
outBlockVarDecl : tLOCAL type tIDENTIFIER   				{ $$ = new pwn::variable_decl_node(LINE,false,true,false,false,$2,$3,NULL); }
				| tLOCAL type tIDENTIFIER '=' expr   		{ $$ = new pwn::variable_decl_node(LINE,false,true,false,false,$2,$3,$5); }
				| tIMPORT type tIDENTIFIER 					{ $$ = new pwn::variable_decl_node(LINE,false,false,true,false,$2,$3,NULL); }
				/* vvvvvvv Constants vvvvvv */
			    | tLOCAL '<' type '>' tIDENTIFIER '=' expr  { $$ = new pwn::variable_decl_node(LINE,false,true,false,true,$3,$5,$7); }
				| tIMPORT '<' type '>' tIDENTIFIER  		{ $$ = new pwn::variable_decl_node(LINE,false,false,true,true,$3,$5,NULL); }
				/*------inBlockVarDecl working outside blocks.--------*/
				| type tIDENTIFIER                   		{ $$ = new pwn::variable_decl_node(LINE,false,false,false,false,$1,$2,NULL); }
				| type tIDENTIFIER '=' expr         		{ $$ = new pwn::variable_decl_node(LINE,false,false,false,false,$1,$2,$4); }
				/* vvvvvvv Constants vvvvvv */
				| '<' type '>' tIDENTIFIER '=' expr 		{ $$ = new pwn::variable_decl_node(LINE,false,false,false,true,$2,$4,$6); }
				;
				
/* ================================================================== */
/* ===================== Function Stuff ============================= */

/* NOTE:  Fixed a error where void returning fuction had ('=' literal). 
   NOTE2: Function definitions cant be imported (Naturally). */
funcDef  : tLOCAL type tIDENTIFIER '(' funcArgs ')' block 				{ $$ = new pwn::def_function_node(LINE,true,$2,$3,$5,NULL,$7); }
		 | tLOCAL type tIDENTIFIER '(' funcArgs ')' '='  literal block 	{ $$ = new pwn::def_function_node(LINE,true,$2,$3,$5,$8,$9); }
		 | tLOCAL '!'  tIDENTIFIER '(' funcArgs ')' block 				{ $$ = new pwn::def_function_node(LINE,true,new basic_type(0,basic_type::TYPE_VOID),$3,$5,NULL,$7); }
		 | type tIDENTIFIER '(' funcArgs ')' block 						{ $$ = new pwn::def_function_node(LINE,false,$1,$2,$4,NULL,$6); }
		 | type tIDENTIFIER '(' funcArgs ')' '='  literal block 		{ $$ = new pwn::def_function_node(LINE,false,$1,$2,$4,$7,$8); }
		 | '!'  tIDENTIFIER '(' funcArgs ')' block 						{ $$ = new pwn::def_function_node(LINE,false,new basic_type(0,basic_type::TYPE_VOID),$2,$4,NULL,$6); }
		 ;

/* NOTE: Fixed a error where void returning fuction had ('=' literal). */
funcDecl : '!' tIDENTIFIER '(' funcArgs ')'							{ $$ = new pwn::decl_function_node(LINE,false,false,new basic_type(0,basic_type::TYPE_VOID),$2,$4,NULL); }
		 | type tIDENTIFIER '(' funcArgs ')'						{ $$ = new pwn::decl_function_node(LINE,false,false,$1,$2,$4,NULL); }
		 | tLOCAL type tIDENTIFIER '(' funcArgs ')' 			 	{ $$ = new pwn::decl_function_node(LINE,true,false,$2,$3,$5,NULL); }
		 | tLOCAL '!'  tIDENTIFIER '(' funcArgs ')'  				{ $$ = new pwn::decl_function_node(LINE,true,false,new basic_type(0,basic_type::TYPE_VOID),$3,$5,NULL); }
		 | tIMPORT type tIDENTIFIER '(' funcArgs ')' 			 	{ $$ = new pwn::decl_function_node(LINE,false,true,$2,$3,$5,NULL); }
		 | tIMPORT '!'  tIDENTIFIER '(' funcArgs ')'  				{ $$ = new pwn::decl_function_node(LINE,false,true,new basic_type(0,basic_type::TYPE_VOID),$3,$5,NULL); }
		 ;

// Function has arguments or none.
funcArgs : args { $$ = $1; }
		 |		{ $$ = NULL; }
		 ;
		 
// One argument or more than one argument.
args : arg 			{ $$ = new cdk::sequence_node(LINE,$1); }
	 | args ',' arg { $$ = new cdk::sequence_node(LINE,$3,$1); }
	 ;

// An argument is a local function variable declaration.
arg : type tIDENTIFIER { $$ = new pwn::variable_decl_node(LINE,true,true,false,false,$1,$2,NULL); }
    ;

/* Block is a set of declarations (possible empty) followed by a set of
   instructions (possible empty) */
block : '{' insideBlockDecls list returnable '}' 	{ $$ = new pwn::block_node(LINE,$2,$3,$4);  }
	  | '{' insideBlockDecls returnable '}'	   	{ $$ = new pwn::block_node(LINE,$2,NULL,$3); }
	  | '{' list returnable '}'	   				{ $$ = new pwn::block_node(LINE,NULL,$2,$3); }
      | '{' returnable '}'			   				{ $$ = new pwn::block_node(LINE,NULL,NULL,$2); }
      ;

returnable : tRETURN	{ $$ = new pwn::return_node(LINE); }
		   |	   		{ $$ = NULL; }
		   ;
      
/* PWN languague basic types.*/
type : '#'		 { $$ = new basic_type(4, basic_type::TYPE_INT); }
	 | '$'  	 { $$ = new basic_type(4, basic_type::TYPE_STRING); }
	 | '*'		 { $$ = new basic_type(4, basic_type::TYPE_POINTER); }
	 | '%'   	 { $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
	 ;

/* Literal values for each type. */
literal : tINTEGER    { $$ = new cdk::integer_node(LINE, $1); }
        | strLiteral  { $$ = new cdk::string_node(LINE , $1); }
        | tREAL	   	  { $$ = new cdk::double_node(LINE, $1); }
        | tNOOB		  { $$ = new pwn::noob_node(LINE); }			
	    ;

/* strLiteral is a String or a String concatenation. */
strLiteral : tSTRING 			{ $$ = $1; }
		   | strLiteral tSTRING { $$ = new std::string(*$1 + *$2); }
		   ;

/*====================================================================*/

/* List of statements. */
list : stmt	     { $$ = new cdk::sequence_node(LINE, $1); }
     | list stmt { $$ = new cdk::sequence_node(LINE, $2, $1); }
     ;

/* All possible statements in pwn.*/
stmt : expr ';'                         { $$ = new pwn::evaluation_node(LINE, $1); }
	 | expr tPRINTLINE					{ $$ = new pwn::printline_node(LINE, $1); }
	 | expr '!'	                        { $$ = new pwn::print_node(LINE, $1); }
     | tIF '(' expr ')' stmt %prec tIFX { $$ = new cdk::if_node(LINE, $3, $5); }
     | tIF '(' expr ')' stmt tELSE stmt { $$ = new cdk::if_else_node(LINE, $3, $5, $7); }
     | tREPEAT '(' optExpr ';' optExpr ';' optExpr ')' stmt  { $$ = new pwn::repeat_node(LINE, $3, $5, $7, $9); }
     | tSTOP ';'						{ $$ = new pwn::stop_node(LINE); }
     | tSTOP tINTEGER ';'				{ $$ = new pwn::stop_node(LINE,new cdk::integer_node(LINE,$2)); }
     | tNEXT ';'						{ $$ = new pwn::next_node(LINE); }
     | tNEXT tINTEGER ';'				{ $$ = new pwn::next_node(LINE,new cdk::integer_node(LINE,$2)); }
     | block                    	 	{ $$ = $1; }
     ;

expr : literal					 { $$ = $1; }
	 | functionCall				 { $$ = $1; }
     | '~' expr                  { $$ = new cdk::neg_node(LINE, $2); }
     | '-' expr	%prec tUNARY  	 { $$ = new pwn::symmetric_node(LINE,$2); }
     | '+' expr	%prec tUNARY     { $$ = new pwn::identity_node(LINE,$2); }
     | expr '&' expr			 { $$ = new pwn::and_node(LINE,$1,$3); }
     | expr '|' expr			 { $$ = new pwn::or_node(LINE,$1,$3); }
     | expr '+' expr	         { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	         { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	         { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	         { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	         { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	         { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	         { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr	         { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr             { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr	         { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr	         { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '[' expr ']'		 		 { $$ = new pwn::memory_alloc_node(LINE,$2); }
     | '(' expr ')'              { $$ = $2; }
     | '@'			 			 { $$ = new pwn::read_node(LINE); }
     | lval '?'	 %prec tUNARY	 { $$ = new pwn::address_node(LINE,$1); }
     | lval                      { $$ = new pwn::rvalue_node(LINE, $1); }
     | lval '=' expr             { $$ = new pwn::assignment_node(LINE, $1, $3); }
     ;

functionCall : tIDENTIFIER '(' exprArgs ')' { $$ = new pwn::function_call_node(LINE,$1,$3); }
			 | tIDENTIFIER '(' ')' 			{ $$ = new pwn::function_call_node(LINE,$1,NULL); }
			 ;

/* Optional Expression. */
optExpr : expr { $$ = $1; }
		| 	   { $$ = NULL; }
		;

/* Represents arguments for functions calls (Sequence of expressions). 
 Already put the arguments in CDECL order. */
exprArgs : expr ',' exprArgs	{ $$ = new cdk::sequence_node(LINE,$1,$3); }
		 | expr 				{ $$ = new cdk::sequence_node(LINE,$1); }
		 ;

			 
lval : tIDENTIFIER               	{ $$ = new pwn::variable_node(LINE, $1); }
     | lval '[' expr ']'			{ $$ = new pwn::index_node(LINE,$1,$3); }
     | functionCall '[' expr ']'	{ $$ = new pwn::index_node(LINE,$1,$3); }
     |'(' expr ')' '[' expr ']'		{ $$ = new pwn::index_node(LINE,$2,$5); }
     ; 

%%
