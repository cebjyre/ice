#include "ice/ast/dealloc.hh"

ice::ast::dealloc::dealloc(expr *expr)
    : _expr(expr)
{
}

ice::ast::dealloc::~dealloc()
{
    delete _expr;
}

ice::ast::expr*
ice::ast::dealloc::get_expr() const
{
    return _expr;
}

void
ice::ast::dealloc::accept(visitor *v)
{
    v->visit(this);
}

void
ice::ast::dealloc::format(std::ostream& stream) const
{
    stream << "dealloc(expr=";
    get_expr()->format(stream);
    stream << ")";
}

