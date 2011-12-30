#include "ice/ast/decl.hh"

ice::ast::decl::decl()
    : node()
{
}

ice::ast::decl::~decl()
{
}

void
ice::ast::format_decl_list(std::ostream& stream, const decl_list& list)
{
    decl_list::const_iterator iter = list.begin();
    stream << "[";
    while (iter != list.end()) {
        (*iter)->format(stream);
        iter++;
        if (iter != list.end()) stream << ", ";
    }
    stream << "]";
}

