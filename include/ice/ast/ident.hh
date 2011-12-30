#ifndef _ICE_AST_IDENT_HH_INCLUDED_
#define _ICE_AST_IDENT_HH_INCLUDED_

#include <string>

#include "ice/ast/expr.hh"

namespace ice {
    namespace ast {
        class ident : public expr {
            public:
                ident(const char *id);
                virtual ~ident();

                const char *get_id() const;

            private:
                std::string _id;
        };
    };
};

#endif

