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

    ice::ast::ident  *ident;

    ice::ast::stmt_list *stmt_list;
    ice::ast::expr_list *expr_list;
}

%token <s> TOK_IDENT
%token TOK_PACKAGE
%type <ident> ident
%type <ident> opt_package_decl package_decl
%type <stmt_list> stmt_list;
%type <mod> module

%%

module: opt_package_decl stmt_list {
      $$ = new ice::ast::module($1, *$2);
      delete $2;
      ice::compiler::push_result($$);
};

stmt_list: ident stmt_list { $$ = $2; $$->push_front(new ice::ast::expr_stmt($1)); }
         | /* nil */ { $$ = new ice::ast::stmt_list(); };

opt_package_decl: package_decl
                | /* nil */ { $$ = NULL; };

package_decl: TOK_PACKAGE ident { $$ = $2; }

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
    std::fflush(stderr);
    exit(1);
}

