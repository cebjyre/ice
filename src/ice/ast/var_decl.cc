#include "ice/ast/var_decl.hh"

ice::ast::var_decl::var_decl(const char *name, type *type)
    : _name(name), _type(type)
{
}

ice::ast::var_decl::~var_decl()
{
    delete _type;
}

const char *
ice::ast::var_decl::get_name() const
{
    return _name.c_str();
}

ice::ast::type*
ice::ast::var_decl::get_type() const
{
    return _type;
}

void
ice::ast::var_decl::accept(visitor *v)
{
    v->visit(this);
}

void
ice::ast::var_decl::format(std::ostream& stream) const
{
    stream << "var_decl(name=";
    stream << get_name();
    stream << ", type=";
    get_type()->format(stream);
    stream << ")";
}

