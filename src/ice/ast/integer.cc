#include "ice/ast/integer.hh"

ice::ast::integer::integer(const char *value)
    : _value(value)
{
}

ice::ast::integer::~integer()
{
}

const char *
ice::ast::integer::get_value() const
{
    return _value.c_str();
}

