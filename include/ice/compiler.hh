#ifndef _ICE_COMPILER_HH_INCLUDED_
#define _ICE_COMPILER_HH_INCLUDED_

namespace ice {
    namespace compiler {
        void
        push_result(ice::ast::module *mod);

        ice::ast::module*
        compile(const char *filename, int fd);

        typedef struct _seminfo {
            std::string          s;
            ice::ast::module    *mod;
            ice::ast::stmt      *stmt;
            ice::ast::expr      *expr;
            ice::ast::stmt_list  stmt_list;
            ice::ast::expr_list  expr_list;
        } seminfo;

    };
};

#ifndef YYSTYPE
#define YYSTYPE ice::compiler::seminfo
#endif

#endif

