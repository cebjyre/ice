#include <cstdio>

#include <unistd.h>

#include "ice/ast.hh"
#include "ice/compiler.hh"

extern int yyparse(void);

static ice::ast::module *result = NULL;

extern FILE *yyin;

void
ice::compiler::push_result(ice::ast::module *mod)
{
    result = mod;
}

ice::ast::module*
ice::compiler::compile(const char *filename, int fd)
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
