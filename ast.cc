#include <cassert>
#include <cstring>

#include "ice/ast.hh"

ice::ast::node::node()
{
}

ice::ast::node::~node()
{
}

ice::ast::stmt::stmt()
    : node()
{
}

ice::ast::stmt::~stmt()
{
}

ice::ast::expr::expr()
    : node()
{
}

ice::ast::expr::~expr()
{
}

ice::ast::ident::ident(const char *id)
    : _id("")
{
    assert(id != NULL);
    _id = id;
}

ice::ast::ident::~ident()
{
}

const char*
ice::ast::ident::get_id() const
{
    return _id.c_str();
}

ice::ast::expr_stmt::expr_stmt(expr *expr)
    : _expr(expr)
{
}

ice::ast::expr_stmt::~expr_stmt()
{
    delete _expr;
}

ice::ast::expr*
ice::ast::expr_stmt::get_expr() const
{
    return _expr;
}

ice::ast::module::module(const char *package, const stmt_list& body)
    : _package(NULL), _body(body)
{
    if (package != NULL && std::strlen(package) > 0) {
        _package = new std::string(package);
    }
}

ice::ast::module::~module()
{
    stmt_list::iterator iter = _body.begin();
    while (iter != _body.end()) {
        delete *iter;
        iter++;
    }
    delete _package;
}

const char*
ice::ast::module::get_package() const
{
    return _package ? _package->c_str() : NULL;
}

const ice::ast::stmt_list&
ice::ast::module::get_body() const
{
    return _body;
}

