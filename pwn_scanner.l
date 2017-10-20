%option c++ yyclass="pwn_scanner" outfile="pwn_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
/* $Id: pwn_scanner.l,v 1.19 2015/05/19 00:07:28 ist176046 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "pwn_scanner.h"
#include "pwn_parser.tab.h"

// don't change this
#define yyerror LexerError
%}

VERSION1 	[0-9]*\.[0-9]+([eE]([-+])?[0-9]+)?
VERSION2 	[0-9]+\.[0-9]*([eE]([-+])?[0-9]+)?
REAL	 	{VERSION2}|{VERSION1}

HEXA		[0-9a-fA-F][0-9a-fA-F]?

%x X_STRING X_COMMENT X_SPECIAL_SEQ

%%

"//".*$                 ; /* Ignore line comments. */

"/*"					yy_push_state(X_COMMENT);
<X_COMMENT>"*/"			yy_pop_state();
<X_COMMENT>"/*"			yy_push_state(X_COMMENT);
<X_COMMENT>.|\n			; /* ignore multiple line comments */
	
">="                   return tGE; 
"<="                   return tLE; 
"=="                   return tEQ; 
"<>"                   return tNE; 

"repeat"               return tREPEAT; 
"return"			   return tRETURN;
"import"			   return tIMPORT;
"local"				   return tLOCAL;
"noob"				   return tNOOB;
"next"				   return tNEXT;
"stop"				   return tSTOP;
"if"                   return tIF; 
"else"                 return tELSE; 
"!!"				   return tPRINTLINE;

[A-Za-z_][A-Za-z0-9_]*  yylval.s = new std::string(yytext); return tIDENTIFIER;

\"                     yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"           yy_pop_state(); return tSTRING;
<X_STRING>\\		   yy_push_state(X_SPECIAL_SEQ);
<X_STRING>.            *yylval.s += yytext;

<X_SPECIAL_SEQ>n	   *yylval.s += std::string(1,10); yy_pop_state();
<X_SPECIAL_SEQ>r	   *yylval.s += std::string(1,13); yy_pop_state();
<X_SPECIAL_SEQ>t       *yylval.s += std::string(1,9); yy_pop_state();
<X_SPECIAL_SEQ>[\"\\]  *yylval.s += std::string(1,(int)*yytext); yy_pop_state();
<X_SPECIAL_SEQ>{HEXA}  *yylval.s += std::string(1,strtol(yytext, nullptr, 16)); yy_pop_state();
<X_SPECIAL_SEQ>\n|.	   yyerror("Special character not allowed!!");	

0|([1-9][0-9]*)        yylval.i = strtol(yytext, nullptr, 10); if(errno == ERANGE) yyerror("ERROR: Overflow, invalid range"); return tINTEGER;
0x[0-9a-fA-f]+         yylval.i = strtol(yytext, nullptr, 16); if(errno == ERANGE) yyerror("ERROR: Overflow, invalid range"); return tINTEGER;
0[0-9]+				   yyerror("ERROR: Invalid Integer!!");

{REAL}				   yylval.r = strtod(yytext,nullptr); if(errno == ERANGE) yyerror("ERROR: Overflow, invalid range"); return tREAL;

[-()[\]<>=+*/%~;{}.$#?&|,!@]   return *yytext;

[ \t\r\n]+             ; /* ignore whitespace and new lines. */

.                      yyerror("ERROR: Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int pwn_scanner::yywrap() { return 1; }
