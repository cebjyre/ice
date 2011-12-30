#ifndef _ICE_AST_DECL_HH_INCLUDED_
#define _ICE_AST_DECL_HH_INCLUDED_

#include "ice/ast/node.hh"

namespace ice {
    namespace ast {
        class decl : public node {
            public:
                decl();
                virtual ~decl();
        };
        
        typedef std::list<decl*> decl_list;

        void
        format_decl_list(std::ostream& stream, const decl_list& list);
    };
};


#endif

