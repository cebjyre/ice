#include "ice/ast/func_decl.hh"

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

