#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include "ice/ast.hh"
#include "ice/parser.hh"
#include "ice/codegen/cxx.hh"

extern int yyparse();

static void
usage(const char *prog)
{
    std::cout << "usage: " << prog << "[filename]\n";
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

    ice::ast::module *mod = ice::parser::parse(filename, fd);
    if (mod == NULL) {
        std::cerr << "parse failed\n";
        return 1;
    }

    mod->format(std::cout);
    std::cout << "\n";

    ice::codegen::cxx(filename, mod);

    delete mod;

    return 0;
}

