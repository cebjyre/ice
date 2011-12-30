#include "ice/ast/ident.hh"

ice::ast::ident::ident(const char *id)
    : _id(id)
{
}

ice::ast::ident::~ident()
{
}

const char*
ice::ast::ident::get_id() const
{
    return _id.c_str();
}

void
ice::ast::ident::format(std::ostream& stream) const
{
    stream << "ident(id=" << get_id() << ")";
}

