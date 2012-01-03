#ifndef _ICE_AST_MODULE_HH_INCLUDED_
#define _ICE_AST_MODULE_HH_INCLUDED_

#include <string>

#include "ice/ast/node.hh"
#include "ice/ast/decl.hh"
#include "ice/ast/visitor.hh"

namespace ice {
    namespace ast {
        typedef std::list<std::string> string_list;

        class module : public node {
            public:
                module(const char *package, const string_list& imports, const decl_list& body);
                virtual ~module();

                const char *get_package() const;
                const string_list& get_imports() const;
                const decl_list& get_body() const;

                void accept(visitor *v);
                void format(std::ostream& stream) const;

                //
                // copy / assign not allowed
                //
            private:
                module(const module& mod) {}
                const module& operator=(const module &mod) { return *this; }

            private:
                std::string *_package;
                string_list _imports;
                decl_list   _body;
        };

        void format_string_list(std::ostream& stream, const string_list& list);
    };
};

#endif

