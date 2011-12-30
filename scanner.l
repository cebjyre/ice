%{

#include "ice/ast.hh"

#include "parser.hh"

extern void yyerror(const char *, ...);

%}

%option noyywrap
%option nounput

%%

[\r\n\t ] ;
[a-zA-Z_][a-zA-Z0-9_]* yylval.s = new std::string(yytext); return TOK_IDENT;
.       yyerror("invalid syntax: %s found", yytext); yyterminate();

%%

