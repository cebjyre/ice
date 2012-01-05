#ifndef _ICE_AST_VISITOR_HH_INCLUDED_
#define _ICE_AST_VISITOR_HH_INCLUDED_

namespace ice {
    namespace ast {
        class module;
        class type;
        class param;
        class func_decl;
        class var_decl;
        class return_stmt;
        class expr_stmt;
        class ident;
        class integer;
        class call;
        class getattr;
        class string;
        class assign;
        class alloc;
        class dealloc;

        class visitor {
            public:
                virtual ~visitor() {}

                virtual void visit(module *mod) {}
                virtual void visit(type *t) {}
                virtual void visit(param *p) {}
                virtual void visit(func_decl *fdecl) {}
                virtual void visit(var_decl *vdecl) {}
                virtual void visit(return_stmt *retstmt) {}
                virtual void visit(expr_stmt *e) {}
                virtual void visit(call *c) {}
                virtual void visit(getattr *g) {}
                virtual void visit(alloc *a) {}
                virtual void visit(dealloc *a) {}
                virtual void visit(assign *a) {}
                virtual void visit(ident *id) {}
                virtual void visit(integer *i) {}
                virtual void visit(string *s) {}

            protected:
                visitor() {}

            private:
                visitor(const visitor &v) {}
                virtual const visitor& operator=(const visitor& op) { return *this; }
        };
    };
};

#endif

