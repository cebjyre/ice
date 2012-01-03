#ifndef _ICE_AST_GETATTR_HH_INCLUDED_
#define _ICE_AST_GETATTR_HH_INCLUDED_

#include "ice/ast/expr.hh"
#include "ice/ast/ident.hh"

namespace ice {
    namespace ast {
        class getattr : public expr {
            public:
                getattr(expr *target, ident *attr);
                virtual ~getattr();

                expr *get_target() const;
                ident *get_attr() const;

                void accept(visitor *v);
                void format(std::ostream& stream) const;

            private:
                expr *_target;
                ident *_attr;
        };
    };
};

#endif

