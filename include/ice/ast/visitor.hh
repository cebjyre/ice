#ifndef _ICE_AST_VISITOR_HH_INCLUDED_
#define _ICE_AST_VISITOR_HH_INCLUDED_

namespace ice {
    namespace ast {
        class module;
        class type;
        class param;
        class func_decl;
        class return_stmt;
        class expr_stmt;
        class ident;
        class integer;

        class visitor {
            public:
                virtual ~visitor() {}

                virtual void enter(module *mod) {}
                virtual void leave(module *mod) {}

                virtual void enter(type *t) {}
                virtual void leave(type *t) {}

                virtual void enter(param *p) {}
                virtual void leave(param *p) {}

                virtual void enter(func_decl *fdecl) {}
                virtual void leave(func_decl *fdecl) {}

                virtual void enter(return_stmt *retstmt) {}
                virtual void leave(return_stmt *retstmt) {}

                virtual void enter(expr_stmt *es) {}
                virtual void leave(expr_stmt *es) {}

                virtual void visit(ident *id) {}

                virtual void visit(integer *i) {}

            protected:
                visitor() {}

            private:
                visitor(const visitor &v) {}
                virtual const visitor& operator=(const visitor& op) { return *this; }
        };
    };
};

#endif

