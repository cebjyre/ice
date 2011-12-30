#ifndef _ICE_AST_HH_INCLUDED_
#define _ICE_AST_HH_INCLUDED_

#include <string>
#include <list>

namespace ice {
    namespace ast {
        class node {
            public:
                node();
                virtual ~node();
        };

        class stmt : public node {
            public:
                stmt();
                virtual ~stmt();
        };

        typedef std::list<stmt*> stmt_list;

        class expr : public node {
            public:
                expr();
                virtual ~expr();
        };

        typedef std::list<expr*> expr_list;

        class ident : public expr {
            public:
                ident(const char *id);
                virtual ~ident();

                const char *get_id() const;

            private:
                std::string _id;
        };

        class expr_stmt : public stmt {
            public:
                expr_stmt(expr *expr);
                virtual ~expr_stmt();

                expr *get_expr() const;

            private:
                expr_stmt(const expr_stmt& es) {}
                const expr_stmt& operator=(const expr_stmt& es) { return *this; }

            private:
                expr *_expr;
        };

        class module : public node {
            public:
                module(ident *package, const stmt_list& body);
                virtual ~module();

                ident* get_package() const;
                const stmt_list& get_body() const;

                //
                // copy / assign not allowed
                //
            private:
                module(const module& mod) {}
                const module& operator=(const module &mod) { return *this; }

            private:
                ident *_package;
                stmt_list _body;
        };
    };
};

#endif

