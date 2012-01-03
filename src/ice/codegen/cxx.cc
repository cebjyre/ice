#include <fstream>
#include <ostream>
#include <stack>

#include "ice/ast.hh"

#include "ice/codegen/cxx.hh"

class cxx_visitor : public ice::ast::visitor {
    private:
        enum scope {
            NONE = 0,
            IN_MODULE = 1,
            IN_FUNCTION = 2
        };
    public:
        cxx_visitor(std::ostream& stream);
        virtual ~cxx_visitor();

        void enter(ice::ast::module *mod);
        void leave(ice::ast::module *mod);

        void enter(ice::ast::func_decl *fdecl);
        void leave(ice::ast::func_decl *fdecl);

        void enter(ice::ast::type *type);
        void leave(ice::ast::type *type);

    private:
        void push(ice::ast::node *node, scope s);
        void pop();

        void write(const char *s);
        void writeline(const char *s);
        void writeline();

        void set_scope(scope s);
        scope get_scope() const;

        std::ostream& _stream;
        scope _scope;
        typedef std::stack<std::pair<ice::ast::node*, scope> > stack;
        stack _stack;
        ice::ast::module *_module;
        ice::ast::func_decl *_main;
};

cxx_visitor::cxx_visitor(std::ostream& stream)
    : _stream(stream), _scope(NONE), _module(NULL), _main(NULL)
{
}

cxx_visitor::~cxx_visitor()
{
}

void
cxx_visitor::enter(ice::ast::module *mod)
{
    writeline("#include <iostream>");
    writeline("#include <sstream>");

    writeline("");
    writeline("typedef long long int64;");
    writeline("typedef int int32;");
    writeline("typedef short int16;");
    writeline("typedef char int8;");
    writeline("typedef unsigned long long uint64;");
    writeline("typedef unsigned int uint32;");
    writeline("typedef unsigned short uint16;");
    writeline("typedef unsigned char uint8;");
    writeline();
    writeline();

    _module = mod;

    push(mod, IN_MODULE);
}

void
cxx_visitor::leave(ice::ast::module *mod)
{
    pop();

    if (_main && _main->get_params().empty()) {
        writeline("");
        writeline("");
        writeline("int");
        writeline("main(int argc, char **argv)");
        writeline("{");
        if (_main->get_return_type()) {
            writeline("return _ice_user__main__main();");
        }
        else {
            writeline("_ice_user__main__main();");
            writeline("return 0;");
        }
        writeline("}");
    }

    _module = NULL;
    _main = NULL;
}

void
cxx_visitor::enter(ice::ast::func_decl *fdecl)
{
    if (fdecl->get_return_type()) {
        writeline(fdecl->get_return_type()->get_name());
    }
    else {
        writeline("void");
    }
    write("_ice_user__"); write(_module->get_package()); write("__"); write(fdecl->get_name());
    
    write("(");
    ice::ast::param_list::const_iterator iter = fdecl->get_params().begin();
    while (iter != fdecl->get_params().end()) {
        ice::ast::param *param = (*iter);
        write(param->get_type()->get_name()); write(" "); write(param->get_name());
        iter++;
        if (iter != fdecl->get_params().end()) write(", ");
    }

    writeline(")");
    writeline("{");
    push(fdecl, IN_FUNCTION);

    if (_module->get_package() == std::string("main") && fdecl->get_name() == std::string("main")) {
        _main = fdecl;
    }
}

void
cxx_visitor::leave(ice::ast::func_decl *fdecl)
{
    writeline("}");
    writeline("");

    pop();
}

void
cxx_visitor::enter(ice::ast::type *type)
{
}

void
cxx_visitor::leave(ice::ast::type *type)
{
}

void
cxx_visitor::push(ice::ast::node *node, cxx_visitor::scope s)
{
    _stack.push(stack::value_type(node, _scope));
    _scope = s;
}

void
cxx_visitor::pop()
{
    stack::value_type top = _stack.top();
    _stack.pop();
    _scope = top.second;
}

void
cxx_visitor::write(const char *s)
{
    _stream << s;
}

void
cxx_visitor::writeline(const char *s)
{
    _stream << s << "\n";
}

void
cxx_visitor::writeline()
{
    writeline("");
}

void
cxx_visitor::set_scope(cxx_visitor::scope scope)
{
    _scope = scope;
}

cxx_visitor::scope
cxx_visitor::get_scope() const
{
    return _scope;
}

bool
ice::codegen::cxx(const char *filename, ice::ast::module *root)
{
    std::fstream s((std::string(filename) + ".cc").c_str(), std::ios::out | std::ios::binary);
    cxx_visitor v(s);

    root->accept(&v);

    return true;
}

