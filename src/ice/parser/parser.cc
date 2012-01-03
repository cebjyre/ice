#include <stack>

#include <cstdio>

#include <unistd.h>

#include "ice/ast.hh"
#include "ice/parser.hh"

extern int yyparse(void);

typedef std::stack<ice::ast::expr*> expr_stack;

static ice::ast::module *result = NULL;
static expr_stack stack;

extern FILE *yyin;

void
ice::parser::push_result(ice::ast::module *mod)
{
    result = mod;
}

void
ice::parser::push_expr(ice::ast::expr *expr)
{
    stack.push(expr);
}

ice::ast::expr*
ice::parser::pop_expr()
{
    ice::ast::expr *expr = stack.top();
    stack.pop();
    return expr;
}

ice::ast::module*
ice::parser::parse(const char *filename, int fd)
{
    ice::ast::module *mod;
    int rc;

    yyin = fdopen(fd, "r");
    if (yyin == NULL) return NULL;
    rc = yyparse();
    std::fclose(yyin);
    mod = result;
    result = NULL;

    if (rc != 0) mod = NULL;
    
    return mod;
}

