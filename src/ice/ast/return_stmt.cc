#include "ice/ast/return_stmt.hh"

ice::ast::return_stmt::return_stmt(expr *value)
    : _value(value)
{
}

ice::ast::return_stmt::~return_stmt()
{
    delete _value;
}

ice::ast::expr*
ice::ast::return_stmt::get_value() const
{
    return _value;
}

