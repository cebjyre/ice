#include <fstream>
#include <iostream>
#include <ostream>
#include <stack>
#include <algorithm>
#include <vector>

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

        void visit(ice::ast::module *mod);

        void visit(ice::ast::func_decl *fdecl);

        void visit(ice::ast::var_decl *vdecl);

        void visit(ice::ast::expr_stmt *e);

        void visit(ice::ast::return_stmt *r);

        void visit(ice::ast::getattr *getattr);

        void visit(ice::ast::call *call);

        void visit(ice::ast::alloc *alloc);

        void visit(ice::ast::dealloc *dealloc);

        void visit(ice::ast::assign *assign);

        void visit(ice::ast::ident *ident);

        void visit(ice::ast::integer *i);

        void visit(ice::ast::string *s);

        void visit(ice::ast::type *t);

    private:
        void push(ice::ast::node *node, scope s);
        void pop();

        void write(const char *s);
        void writeline(const char *s);
        void writeline();
        void writestream(std::istream& in);

        void _do_builtins();
        void _do_imports();
        void _do_main();

        void set_scope(scope s);
        scope get_scope() const;

        std::ostream& _stream;
        scope _scope;
        typedef std::stack<std::pair<ice::ast::node*, scope> > stack;
        stack _stack;
        ice::ast::module *_module;
        ice::ast::func_decl *_main;
        typedef std::vector<std::string> modules;
        modules _imports;
        bool _ident_hack;
};

cxx_visitor::cxx_visitor(std::ostream& stream)
    : _stream(stream), _scope(NONE), _module(NULL), _main(NULL), _ident_hack(false)
{
}

cxx_visitor::~cxx_visitor()
{
}

template <class T>
static void visit_all(std::list<T> list, ice::ast::visitor *v)
{
    typename std::list<T>::const_iterator iter;

    iter = list.begin();
    while (iter != list.end()) {
        (*iter)->accept(v);
        iter++;
    }
}

void
cxx_visitor::_do_builtins()
{
    std::fstream in("modules/builtin.cc", std::ios::in | std::ios::binary);
    writestream(in);
}

void
cxx_visitor::_do_imports()
{
    _imports.clear();

    ice::ast::import_list::const_iterator iter = _module->get_imports().begin();
    while (iter != _module->get_imports().end()) {
        std::string filename = "modules/";
        filename += iter->first;
        filename += ".cc";
        std::fstream in(filename.c_str(), std::ios::in | std::ios::binary);
        write("namespace "); write(iter->second.c_str()); writeline("{");
        writestream(in);
        writeline();
        writeline("};");
        writeline();
        in.close();

        _imports.push_back(iter->second);

        iter++;
    }
}

void
cxx_visitor::_do_main()
{
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
}

void
cxx_visitor::visit(ice::ast::module *mod)
{
    _module = mod;

    _do_builtins();
    _do_imports();

    push(mod, IN_MODULE);

    visit_all(mod->get_body(), this);

    pop();

    _do_main();

    _module = NULL;
    _main = NULL;
}

void
cxx_visitor::visit(ice::ast::expr_stmt *e)
{
    e->get_expr()->accept(this);
    writeline(";\n");
}

void
cxx_visitor::visit(ice::ast::return_stmt *r)
{
    write("return ");
    if (r->get_value()) {
        r->get_value()->accept(this);
    }
    writeline(";\n");
}

void
cxx_visitor::visit(ice::ast::func_decl *fdecl)
{
    if (fdecl->get_return_type()) {
        fdecl->get_return_type()->accept(this);
        writeline();
    }
    else {
        writeline("void");
    }
    write("_ice_user__"); write(_module->get_package()); write("__"); write(fdecl->get_name());
    
    write("(");
    ice::ast::param_list::const_iterator iter = fdecl->get_params().begin();
    while (iter != fdecl->get_params().end()) {
        ice::ast::param *param = (*iter);
        param->get_type()->accept(this); write(" "); write(param->get_name());
        iter++;
        if (iter != fdecl->get_params().end()) write(", ");
    }

    writeline(")");
    writeline("{");
    push(fdecl, IN_FUNCTION);

    if (_module->get_package() == std::string("main") && fdecl->get_name() == std::string("main")) {
        _main = fdecl;
    }

    visit_all(fdecl->get_body(), this);

    writeline("}");
    writeline("");

    pop();
}

void
cxx_visitor::visit(ice::ast::var_decl *vdecl)
{
    vdecl->get_type()->accept(this);
    write(" ");
    write(vdecl->get_name());
    writeline(";");
}

void
cxx_visitor::visit(ice::ast::getattr *getattr)
{
    getattr->get_target()->accept(this);
    bool module = false;
    if (getattr->get_target()->is_ident()) {
        ice::ast::ident *ident = (ice::ast::ident*)getattr->get_target();
        if (std::find(_imports.begin(), _imports.end(), ident->get_id()) != _imports.end()) {
            module = true;
        }
    }
    if (module) {
        write("::");
    }
    else {
        write("->");
    }
    getattr->get_attr()->accept(this);
}

void
cxx_visitor::visit(ice::ast::call *call)
{
    if (call->get_target()->is_ident()) {
        write("_ice_user__"); write(_module->get_package()); write("__");
    }
    call->get_target()->accept(this);
    write("(");
    ice::ast::expr_list::const_iterator iter = call->get_args().begin();
    while (iter != call->get_args().end()) {
        (*iter)->accept(this);
        iter++;
        if (iter != call->get_args().end()) write(", ");
    }
    write(")");
}

void
cxx_visitor::visit(ice::ast::alloc *alloc)
{
    write("new ");
    alloc->get_type()->accept(this);
}

void
cxx_visitor::visit(ice::ast::dealloc *dealloc)
{
    write("delete ");
    dealloc->get_expr()->accept(this);
    writeline(";");
}

void
cxx_visitor::visit(ice::ast::assign *assign)
{
    assign->get_target()->accept(this);
    write(" = ");
    assign->get_value()->accept(this);
}

void
cxx_visitor::visit(ice::ast::ident *ident)
{
    write(ident->get_id());
}

void
cxx_visitor::visit(ice::ast::integer *i)
{
    // XXX hard-coding int32 sucks */
    write("int32(");
    write(i->get_value());
    write(")");
}

void
cxx_visitor::visit(ice::ast::string *s)
{
    write("string(\"");
    write(s->get_value());
    write("\")");
}

void
cxx_visitor::visit(ice::ast::type *t)
{
    write(t->get_name());
    if (!t->get_specializations().empty()) {
        write("<");
        ice::ast::type_list::const_iterator iter = t->get_specializations().begin();
        while (iter != t->get_specializations().end()) {
            (*iter)->accept(this);
            iter++;
            if (iter != t->get_specializations().end()) write(", ");
        }
        write(">");
    }
    for (int i = 0; i < t->get_pointer(); i++) {
        write("*");
    }
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
cxx_visitor::writestream(std::istream& in)
{
    char buf[8192];
    size_t n;
    while (!in.eof()) {
        n = sizeof(buf);
        n = in.readsome(buf, n);
        if (n <= 0) break;
        _stream.write(buf, n);
    }
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

    s.flush();
    s.close();

    std::string binary = filename;
    binary = binary.substr(0, binary.length() - 4); // XXX
    std::string cxxfile = filename;
    cxxfile += ".cc";

    // invoke g++ to generate a binary
    execlp("g++", "g++", "-Wall", "-o", binary.c_str(), cxxfile.c_str(), NULL);

    return true;
}

