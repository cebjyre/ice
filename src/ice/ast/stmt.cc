#include "ice/ast/stmt.hh"

ice::ast::stmt::stmt()
    : node()
{
}

ice::ast::stmt::~stmt()
{
}

void
ice::ast::format_stmt_list(std::ostream& stream, const stmt_list& list)
{
    stmt_list::const_iterator iter = list.begin();
    stream << "[";
    while (iter != list.end()) {
        (*iter)->format(stream);
        iter++;
        if (iter != list.end()) stream << ", ";
    }
    stream << "]";
}

