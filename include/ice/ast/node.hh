#ifndef _ICE_AST_NODE_HH_INCLUDED_
#define _ICE_AST_NODE_HH_INCLUDED_

#include <list>
#include <ostream>

#include "ice/ast/visitor.hh"

namespace ice {
    namespace ast {
        class node {
            public:
                node();
                virtual ~node();

                virtual bool is_ident() const { return false; }

                virtual void accept(visitor* v) = 0;
                virtual void format(std::ostream& s) const = 0;
        };

        typedef std::list<node*> node_list;
    };
};

#endif

