#include "ice/ast/getattr.hh"

ice::ast::getattr::getattr(expr *expr, ident *attr)
    : _target(expr), _attr(attr)
{
}

ice::ast::getattr::~getattr()
{
    delete _target;
    delete _attr;
}

ice::ast::expr*
ice::ast::getattr::get_target() const
{
    return _target;
}

ice::ast::ident*
ice::ast::getattr::get_attr() const
{
    return _attr;
}

void
ice::ast::getattr::accept(visitor *v)
{
    v->enter(this);
    get_attr()->accept(v);
    v->leave(this);
}

void
ice::ast::getattr::format(std::ostream& stream) const
{
    stream << "getattr(target=";
    get_target()->format(stream);
    stream << ", attr=";
    get_attr()->format(stream);
    stream << ")";
}

