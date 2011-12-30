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

