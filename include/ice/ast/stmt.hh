#ifndef _ICE_AST_STMT_HH_INCLUDED_
#define _ICE_AST_STMT_HH_INCLUDED_

#include "ice/ast/node.hh"

namespace ice {
    namespace ast {
        class stmt : public node {
            public:
                stmt();
                virtual ~stmt();
        };

        typedef std::list<stmt*> stmt_list;
    };
};

#endif

