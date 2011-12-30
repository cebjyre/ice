%{

#include <cstdio>
#include <cstdarg>

#include <string>

#include "ice/ast.hh"
#include "ice/parser.hh"

extern int yylex(void);
void yyerror(const char *format, ...);

%}

%token <s> TOK_IDENT TOK_INTEGER
%token TOK_PACKAGE TOK_FUNC TOK_USE TOK_RETURN
%token TOK_LBRACKET TOK_RBRACKET TOK_LBRACE TOK_RBRACE TOK_COMMA
%token TOK_SEMICOLON TOK_LSQ TOK_RSQ
%type <s> opt_package_decl package_decl
%type <stmt> simple_stmt stmt
%type <expr> expr opt_expr ident integer
%type <stmt_list> stmt_list;
%type <param_list> opt_param_list opt_param_list_tail;
%type <param> param
%type <decl> func_decl module_decl
%type <decl_list> module_decl_list
%type <type> type opt_type
%type <type_list> type_list type_list_tail type_tail
%type <s> use
%type <string_list> opt_use_list
%type <mod> module

%%

module: opt_package_decl opt_use_list module_decl_list {
      $$ = new ice::ast::module($1.c_str(), $2, $3);
      ice::parser::push_result($$);
}
;

module_decl_list: module_decl module_decl_list { $$ = $2; $$.push_front($1); }
                | /* nil */ { $$; }
                ;

module_decl: func_decl
           ;

opt_use_list: use TOK_SEMICOLON opt_use_list { $$ = $3; $$.push_front($1); }
            | /* nil */ { $$; }
            ;

use: TOK_USE TOK_IDENT { $$ = $2; }
   ;

func_decl: TOK_FUNC TOK_IDENT TOK_LBRACKET opt_param_list TOK_RBRACKET opt_type TOK_LBRACE stmt_list TOK_RBRACE
            { $$ = new ice::ast::func_decl($2.c_str(), $4, $6, $8); }
         ;

opt_param_list: param opt_param_list_tail { $$ = $2; $$.push_front($1); }
              | /* nil */ { $$; }
              ;

opt_param_list_tail: TOK_COMMA param opt_param_list_tail { $$ = $3; $$.push_front($2); }
                   | /* nil */ { $$; }
                   ;

param: TOK_IDENT type { $$ = new ice::ast::param($1.c_str(), $2); }
     ;

opt_type: type
        | /* nil */ { $$ = NULL; }
        ;

type: TOK_IDENT type_tail { $$ = new ice::ast::type($1.c_str(), $2); }
    ;

type_tail: TOK_LSQ type_list TOK_RSQ { $$ = $2; }
         | /* nil */ { $$; }
         ;

type_list: type type_list_tail { $$ = $2; $$.push_front($1); }
         ;

type_list_tail: TOK_COMMA type type_list_tail { $$ = $3; $$.push_front($2); }
              | /* nil */ { $$; };

stmt_list: stmt TOK_SEMICOLON stmt_list { $$ = $3; $$.push_front($1); }
         | /* nil */ { $$; }
         ;

stmt: simple_stmt
    ;

simple_stmt: TOK_RETURN opt_expr { $$ = new ice::ast::return_stmt($2); }
           | expr { $$ = new ice::ast::expr_stmt($1); }
           ;

opt_expr: expr
        | /* nil */ { $$ = NULL; }
        ;

expr: ident
    | integer
    ;

opt_package_decl: package_decl
                | /* nil */ { $$ = ""; }
                ;

package_decl: TOK_PACKAGE TOK_IDENT TOK_SEMICOLON { $$ = $2; }
            ;

ident: TOK_IDENT { $$ = new ice::ast::ident($1.c_str()); }
     ;

integer: TOK_INTEGER { $$ = new ice::ast::integer($1.c_str()); }
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

