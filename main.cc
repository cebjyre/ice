#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include "ice/ast.hh"
#include "ice/compiler.hh"

extern int yyparse();

static void
usage(const char *prog)
{
    printf("usage: %s [filename]\n", prog);
}

int
main(int argc, char **argv)
{
    int fd;
    const char *filename;
    
    if (argc == 2) {
        filename = argv[1];
        fd = open(filename, O_RDONLY);
        if (fd < 0) return 1;
    }
    else if (argc == 1) {
        filename = "stdin";
        fd = 0;
    }
    else {
        usage(argv[0]);
        return 1;
    }

    ice::ast::module *mod = ice::compiler::compile(filename, fd);
    if (mod == NULL) {
        std::fprintf(stderr, "compile failed\n");
        return 1;
    }

    std::printf("%p", mod);
    if (mod->get_package()) {
        std::printf(" (%s)", mod->get_package()->get_id());
    }
    std::printf("\n");

    ice::ast::stmt_list::const_iterator iter = mod->get_body().begin();
    while (iter != mod->get_body().end()) {
        ice::ast::expr_stmt *stmt = (ice::ast::expr_stmt*)*iter;
        ice::ast::ident *ident = (ice::ast::ident*)stmt->get_expr();
        std::printf("  \"%s\"\n", ident->get_id());
        iter++;
    }
}

