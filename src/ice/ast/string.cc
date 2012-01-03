#include "ice/ast/string.hh"

ice::ast::string::string(const char *value)
    : _value(value)
{
    if (_value.length() > 2) {
        std::string::size_type n = _value.length() - 2;
        _value = _value.substr(1, n);
    }
    else {
        _value = "";
    }
}

ice::ast::string::~string()
{
}

const char *
ice::ast::string::get_value() const
{
    return _value.c_str();
}

void
ice::ast::string::accept(visitor *v)
{
    v->visit(this);
}

void
ice::ast::string::format(std::ostream& stream) const
{
    stream << "\"" << get_value() << "\"";
}

