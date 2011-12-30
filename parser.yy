%{

#include <cstdio>
#include <cstdarg>

#include <string>

#include "ice/ast.hh"
#include "ice/compiler.hh"

extern int yylex(void);
void yyerror(const char *format, ...);

%}

%union {
    std::string *s;
    ice::ast::module *mod;
    ice::ast::stmt   *stmt;
    ice::ast::expr   *expr;
}

%token <s> TOK_IDENT
%type <expr> ident
%type <mod> module

%%

module: ident {
      ice::ast::stmt_list stmts;
      stmts.push_back(new ice::ast::expr_stmt($1));
      $$ = new ice::ast::module(stmts);
      ice::compiler::push_result($$);
};

ident: TOK_IDENT { $$ = new ice::ast::ident($1->c_str()); delete $1; }

%%

void
yyerror(const char *format, ...)
{
    va_list args;

    std::fprintf(stderr, "error: ");
    va_start(args, format);
    std::vfprintf(stderr, format, args);
    va_end(args);
    std::fprintf(stderr, "\n");
    exit(1);
}

