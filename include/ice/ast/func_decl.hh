#ifndef _ICE_FUNC_DECL_HH_INCLUDED_
#define _ICE_FUNC_DECL_HH_INCLUDED_

#include <string>

#include "ice/ast/decl.hh"
#include "ice/ast/stmt.hh"

namespace ice {
    namespace ast {
        class type;

        typedef std::list<type*> type_list;

        class type : public node {
            public:
                type(const char *name, const type_list& specializations);
                virtual ~type();

                const char *get_name() const;
                const type_list& get_specializations() const;

                void format(std::ostream& stream) const;

            private:
                std::string _name;
                type_list _specializations;
        };

        void
        format_type_list(std::ostream& stream, const type_list& list);

        class param : public node {
            public:
                param(const char *name, type *type);
                virtual ~param();

                const char *get_name() const;
                type *get_type() const;

                void format(std::ostream& stream) const;

            private:
                std::string _name;
                type *_type;
        };

        typedef std::list<param*> param_list;

        void
        format_param_list(std::ostream& stream, const param_list& list);

        class func_decl : public decl {
            public:
                func_decl(const char *name, const param_list& params, type *return_type, const stmt_list& body);
                virtual ~func_decl();

                const char *get_name() const;
                const param_list& get_params() const;
                type *get_return_type() const;
                const stmt_list& get_body() const;

                void format(std::ostream& stream) const;

            private:
                std::string _name;
                param_list _params;
                type *_return_type;
                stmt_list _body;
        };
    };
};

#endif

