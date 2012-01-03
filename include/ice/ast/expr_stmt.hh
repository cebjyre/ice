#ifndef _ICE_AST_EXPR_STMT_HH_INCLUDED_
#define _ICE_AST_EXPR_STMT_HH_INCLUDED_

#include "ice/ast/stmt.hh"
#include "ice/ast/expr.hh"

namespace ice {
    namespace ast {
        class expr_stmt : public stmt {
            public:
                expr_stmt(expr *expr);
                virtual ~expr_stmt();

                expr *get_expr() const;

                void accept(visitor *v);
                void format(std::ostream& stream) const;

            private:
                expr_stmt(const expr_stmt& es) {}
                const expr_stmt& operator=(const expr_stmt& es) { return *this; }

            private:
                expr *_expr;
        };
    };
};

#endif

