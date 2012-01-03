%{

#include "ice/ast.hh"
#include "ice/parser.hh"

#include "ice/parser/_parser.hh"

extern void yyerror(const char *, ...);

%}

%option noyywrap
%option nounput

%%

[\r\n\t ] ;
";"       return TOK_SEMICOLON;
"("       return TOK_LBRACKET;
")"       return TOK_RBRACKET;
"{"       return TOK_LBRACE;
"}"       return TOK_RBRACE;
"["       return TOK_LSQ;
"]"       return TOK_RSQ;
","       return TOK_COMMA;
"."       return TOK_PERIOD;
"func"    return TOK_FUNC;
"use"     return TOK_USE;
"package" return TOK_PACKAGE;
"return"  return TOK_RETURN;
[a-zA-Z_][a-zA-Z0-9_]* yylval.s = yytext; return TOK_IDENT;
[0-9]+    yylval.s = yytext; return TOK_INTEGER;
["][^"]*["] yylval.s = yytext; return TOK_STRING;
.       yyerror("invalid syntax: %s found", yytext); yyterminate();

%%

