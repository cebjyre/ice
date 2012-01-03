#include <cstring>

#include "ice/ast/module.hh"

ice::ast::module::module(const char *package, const import_list& imports, const decl_list& body)
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

const ice::ast::import_list&
ice::ast::module::get_imports() const
{
    return _imports;
}

const ice::ast::decl_list&
ice::ast::module::get_body() const
{
    return _body;
}

void
ice::ast::module::accept(visitor *v)
{
    v->visit(this);
}

void
ice::ast::module::format(std::ostream& stream) const
{
    stream << "module(";
    if (_package != NULL) {
        stream << "name=" << (_package->c_str()) << ", ";
    }
    stream << "imports=";
    format_import_list(stream, get_imports());
    stream << ", ";
    stream << "body=";
    format_decl_list(stream, get_body());
    stream << ")";
}

void
ice::ast::format_string_list(std::ostream& stream, const string_list& list)
{
    string_list::const_iterator iter = list.begin();
    stream << "[";
    while (iter != list.end()) {
        stream << *iter;
        iter++;
        if (iter != list.end()) stream << ", ";
    }
    stream << "]";
}

void
ice::ast::format_import_list(std::ostream& stream, const import_list& list)
{
    import_list::const_iterator iter = list.begin();
    stream << "[";
    while (iter != list.end()) {
        stream << iter->first.c_str();
        if (iter->second != iter->first) {
            stream << " -> " << iter->second.c_str();
        }
        iter++;
        if (iter != list.end()) stream << ", ";
    }
    stream << "]";
}

