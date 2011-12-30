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
            ice::ast::decl      *decl;
            ice::ast::param     *param;
            ice::ast::type      *type;
            ice::ast::stmt      *stmt;
            ice::ast::expr      *expr;
            ice::ast::stmt_list  stmt_list;
            ice::ast::expr_list  expr_list;
            ice::ast::decl_list  decl_list;
            ice::ast::param_list param_list;
            ice::ast::type_list  type_list;
        } seminfo;

    };
};

#ifndef YYSTYPE
#define YYSTYPE ice::compiler::seminfo
#endif

#endif

