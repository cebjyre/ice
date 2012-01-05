#ifndef _ICE_PARSER_HH_INCLUDED_
#define _ICE_PARSER_HH_INCLUDED_

namespace ice {
    namespace parser {
        void
        push_result(ice::ast::module *mod);

        void
        push_expr(ice::ast::expr *expr);

        ice::ast::expr*
        pop_expr();

        ice::ast::module*
        parse(const char *filename, int fd);

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
            ice::ast::string_list string_list;
            ice::ast::import_list import_list;
            ice::ast::import_list::value_type import;
            int n;
        } seminfo;

    };
};

#ifndef YYSTYPE
#define YYSTYPE ice::parser::seminfo
#endif

#endif

