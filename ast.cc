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

ice::ast::decl::decl()
    : node()
{
}

ice::ast::decl::~decl()
{
}

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

ice::ast::type::type(const char *name, const type_list& specializations)
    : _name(name), _specializations(specializations)
{
}

ice::ast::type::~type()
{
    type_list::iterator iter = _specializations.begin();
    while (iter != _specializations.end()) {
        delete *iter;
        iter++;
    }
}

const char *
ice::ast::type::get_name() const
{
    return _name.c_str();
}

const ice::ast::type_list&
ice::ast::type::get_specializations() const
{
    return _specializations;
}

ice::ast::param::param(const char *name, type *type)
    : _name(name), _type(type)
{
}

ice::ast::param::~param()
{
    delete _type;
}

const char *
ice::ast::param::get_name() const
{
    return _name.c_str();
}

ice::ast::func_decl::func_decl(const char *name, const param_list& params, type *return_type, const stmt_list& body)
    : _name(name), _params(params), _return_type(return_type), _body(body)
{
}

ice::ast::func_decl::~func_decl()
{
    param_list::iterator piter = _params.begin();
    while (piter != _params.end()) {
        delete *piter;
        piter++;
    }

    delete _return_type;

    stmt_list::iterator siter = _body.end();
    while (siter != _body.end()) {
        delete *siter;
        siter++;
    }
}

const char *
ice::ast::func_decl::get_name() const
{
    return _name.c_str();
}

const ice::ast::param_list&
ice::ast::func_decl::get_params() const
{
    return _params;
}

ice::ast::type*
ice::ast::func_decl::get_return_type() const
{
    return _return_type;
}

const ice::ast::stmt_list&
ice::ast::func_decl::get_body() const
{
    return _body;
}

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

ice::ast::module::module(const char *package, const string_list& imports, const decl_list& body)
    : _package(NULL), _imports(imports), _body(body)
{
    if (package != NULL && std::strlen(package) > 0) {
        _package = new std::string(package);
    }
}

ice::ast::module::~module()
{
    decl_list::iterator iter = _body.begin();
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

const ice::ast::string_list&
ice::ast::module::get_imports() const
{
    return _imports;
}

const ice::ast::decl_list&
ice::ast::module::get_body() const
{
    return _body;
}

