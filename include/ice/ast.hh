#ifndef _ICE_AST_HH_INCLUDED_
#define _ICE_AST_HH_INCLUDED_

#include <string>
#include <list>

namespace ice {
    namespace ast {
        typedef std::list<std::string> string_list;

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

        class decl : public node {
            public:
                decl();
                virtual ~decl();
        };
        
        typedef std::list<decl*> decl_list;

        class ident : public expr {
            public:
                ident(const char *id);
                virtual ~ident();

                const char *get_id() const;

            private:
                std::string _id;
        };

        class integer : public expr {
            public:
                integer(const char *value);
                virtual ~integer();

                const char *get_value() const;

            private:
                std::string _value;
        };

        class type;

        typedef std::list<type*> type_list;

        class type : public node {
            public:
                type(const char *name, const type_list& specializations);
                virtual ~type();

                const char *get_name() const;
                const type_list& get_specializations() const;

            private:
                std::string _name;
                type_list _specializations;
        };

        class param : public node {
            public:
                param(const char *name, type *type);
                virtual ~param();

                const char *get_name() const;

            private:
                std::string _name;
                type *_type;
        };

        typedef std::list<param*> param_list;

        class func_decl : public decl {
            public:
                func_decl(const char *name, const param_list& params, type *return_type, const stmt_list& body);
                virtual ~func_decl();

                const char *get_name() const;
                const param_list& get_params() const;
                type *get_return_type() const;
                const stmt_list& get_body() const;

            private:
                std::string _name;
                param_list _params;
                type *_return_type;
                stmt_list _body;
        };

        class return_stmt : public stmt {
            public:
                return_stmt(expr *value);
                virtual ~return_stmt();

                expr *get_value() const;

            private:
                expr *_value;
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
                module(const char *package, const string_list& imports, const decl_list& body);
                virtual ~module();

                const char *get_package() const;
                const string_list& get_imports() const;
                const decl_list& get_body() const;

                //
                // copy / assign not allowed
                //
            private:
                module(const module& mod) {}
                const module& operator=(const module &mod) { return *this; }

            private:
                std::string *_package;
                string_list _imports;
                decl_list   _body;
        };
    };
};

#endif

