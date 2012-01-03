#include <fstream>
#include <ostream>

#include "ice/ast.hh"

#include "ice/codegen/cxx.hh"

class cxx_visitor : public ice::ast::visitor {
    public:
        cxx_visitor(std::ostream& stream);
        virtual ~cxx_visitor();

        void write(const char *s);
        void writeline(const char *s);

        void enter(ice::ast::module *mod);
        void leave(ice::ast::module *mod);

    private:
        std::ostream& _stream;
};

cxx_visitor::cxx_visitor(std::ostream& stream)
    : _stream(stream)
{
}

cxx_visitor::~cxx_visitor()
{
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
cxx_visitor::enter(ice::ast::module *mod)
{
    writeline("#include <iostream>");
    writeline("#include <sstream>");
}

void
cxx_visitor::leave(ice::ast::module *mod)
{
}

bool
ice::codegen::cxx(const char *filename, ice::ast::module *root)
{
    std::fstream s((std::string(filename) + ".cc").c_str(), std::ios::out | std::ios::binary);
    cxx_visitor v(s);

    root->accept(&v);

    return true;
}

