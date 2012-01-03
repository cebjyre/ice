#include "ice/ast/assign.hh"

ice::ast::assign::assign(expr *target, expr *value)
    : _target(target), _value(value)
{
}

ice::ast::assign::~assign()
{
    delete _target;
    delete _value;
}

ice::ast::expr *
ice::ast::assign::get_target() const
{
    return _target;
}

ice::ast::expr *
ice::ast::assign::get_value() const
{
    return _value;
}

void
ice::ast::assign::accept(visitor *v)
{
    v->visit(this);
}

void
ice::ast::assign::format(std::ostream& stream) const
{
    stream << "assign(target=";
    _target->format(stream);
    stream << ", value=";
    _value->format(stream);
    stream << ")";
}

