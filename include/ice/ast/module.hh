#ifndef _ICE_AST_MODULE_HH_INCLUDED_
#define _ICE_AST_MODULE_HH_INCLUDED_

#include <string>

#include "ice/ast/node.hh"
#include "ice/ast/decl.hh"
#include "ice/ast/visitor.hh"

namespace ice {
    namespace ast {
        typedef std::list<std::string> string_list;
        typedef std::list<std::pair<std::string, std::string> > import_list;

        class module : public node {
            public:
                module(const char *package, const import_list& imports, const decl_list& body);
                virtual ~module();

                const char *get_package() const;
                const import_list& get_imports() const;
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
                import_list _imports;
                decl_list   _body;
        };

        void format_string_list(std::ostream& stream, const string_list& list);
        void format_import_list(std::ostream& stream, const import_list& list);
    };
};

#endif

