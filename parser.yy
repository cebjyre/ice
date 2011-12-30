%{

#include <cstdio>
#include <cstdarg>

#include <string>

#include "ice/ast.hh"
#include "ice/compiler.hh"

extern int yylex(void);
void yyerror(const char *format, ...);

%}

%token <s> TOK_IDENT
%token TOK_PACKAGE
%type <s> opt_package_decl package_decl
%type <stmt> simple_stmt stmt
%type <expr> expr ident
%type <stmt_list> stmt_list;
%type <mod> module

%%

module: opt_package_decl stmt_list {
      $$ = new ice::ast::module($1.c_str(), $2);
      ice::compiler::push_result($$);
}
;

stmt_list: stmt stmt_list { $$ = $2; $$.push_front($1); }
         | /* nil */ { $$ = ice::ast::stmt_list(); }
         ;

stmt: simple_stmt
    ;

simple_stmt: expr { $$ = new ice::ast::expr_stmt($1); }
           ;

expr: ident
    ;

opt_package_decl: package_decl
                | /* nil */ { $$ = ""; }
                ;

package_decl: TOK_PACKAGE TOK_IDENT { $$ = $2; }
            ;

ident: TOK_IDENT { $$ = new ice::ast::ident($1.c_str()); }
     ;

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

