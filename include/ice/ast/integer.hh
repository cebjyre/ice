#ifndef _ICE_AST_INTEGER_HH_INCLUDED_
#define _ICE_AST_INTEGER_HH_INCLUDED_

#include <string>

#include "ice/ast/expr.hh"

namespace ice {
    namespace ast {
        class integer : public expr {
            public:
                integer(const char *value);
                virtual ~integer();

                const char *get_value() const;

            private:
                std::string _value;
        };
    };
};

#endif

