#ifndef _ICE_AST_EXPR_HH_INCLUDED_
#define _ICE_AST_EXPR_HH_INCLUDED_

#include "ice/ast/node.hh"

namespace ice {
    namespace ast {
        class expr : public node {
            public:
                expr();
                virtual ~expr();
        };

        typedef std::list<expr*> expr_list;

        void
        format_expr_list(std::ostream& stream, const expr_list& list);
    };
};

#endif

