#ifndef _ICE_AST_NODE_HH_INCLUDED_
#define _ICE_AST_NODE_HH_INCLUDED_

#include <list>

namespace ice {
    namespace ast {
        class node {
            public:
                node();
                virtual ~node();
        };

        typedef std::list<node*> node_list;
    };
};

#endif

