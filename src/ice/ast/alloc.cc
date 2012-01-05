#include "ice/ast/alloc.hh"

ice::ast::alloc::alloc(type *t)
    : _type(t)
{
}

ice::ast::alloc::~alloc()
{
    delete _type;
}

ice::ast::type*
ice::ast::alloc::get_type() const
{
    return _type;
}

void
ice::ast::alloc::accept(visitor *v)
{
    v->visit(this);
}

void
ice::ast::alloc::format(std::ostream& stream) const
{
    stream << "alloc(type=";
    get_type()->format(stream);
    stream << ")";
}

