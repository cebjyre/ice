#ifndef _ICE_AST_STRING_HH_INCLUDED_
#define _ICE_AST_STRING_HH_INCLUDED_

#include "ice/ast/expr.hh"

namespace ice {
    namespace ast {
        class string : public expr {
            public:
                string(const char *value);
                virtual ~string();

                const char *get_value() const;

                void accept(visitor *v);
                void format(std::ostream& stream) const;

            private:
                std::string _value;
        };
    };
};

#endif

