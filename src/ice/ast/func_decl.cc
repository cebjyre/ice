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

void
ice::ast::type::format(std::ostream& stream) const
{
    stream << "type(";
    stream << "name=" << get_name();
    if (!get_specializations().empty()) {
        stream << ", specializations=";
        format_type_list(stream, get_specializations());
    }
    stream << ")";
}

void
ice::ast::format_type_list(std::ostream& stream, const type_list& list)
{
    type_list::const_iterator iter = list.begin();
    stream << "[";
    while (iter != list.end()) {
        (*iter)->format(stream);
        iter++;
        if (iter != list.end()) stream << ", ";
    }
    stream << "]";
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

ice::ast::type*
ice::ast::param::get_type() const
{
    return _type;
}

void
ice::ast::param::format(std::ostream& stream) const
{
    stream << "param(";
    stream << "name=" << get_name() << ", ";
    stream << "type=";
    get_type()->format(stream);
    stream << ")";
}

void
ice::ast::format_param_list(std::ostream& stream, const param_list& list)
{
    param_list::const_iterator iter = list.begin();
    stream << "[";
    while (iter != list.end()) {
        (*iter)->format(stream);
        iter++;
        if (iter != list.end()) stream << ", ";
    }
    stream << "]";
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

void
ice::ast::func_decl::format(std::ostream& stream) const
{
    stream << "func_decl(";
    stream << "name=" << get_name() << ", ";
    stream << "params=";
    format_param_list(stream, get_params());
    if (get_return_type() != NULL) {
        stream << ", return_type=";
        get_return_type()->format(stream);
    }
    stream << ", body=";
    format_stmt_list(stream, get_body());
    stream << ")";
}

