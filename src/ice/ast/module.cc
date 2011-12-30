#include <cstring>

#include "ice/ast/module.hh"

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

