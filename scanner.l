%{

#include "ice/ast.hh"
#include "ice/compiler.hh"

#include "parser.hh"

extern void yyerror(const char *, ...);

%}

%option noyywrap
%option nounput

%%

[\r\n\t ] ;
"package" return TOK_PACKAGE;
[a-zA-Z_][a-zA-Z0-9_]* yylval.s = yytext; return TOK_IDENT;
.       yyerror("invalid syntax: %s found", yytext); yyterminate();

%%

