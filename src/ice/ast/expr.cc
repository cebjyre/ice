#include "ice/ast/expr.hh"

ice::ast::expr::expr()
    : node()
{
}

ice::ast::expr::~expr()
{
}

void
ice::ast::format_expr_list(std::ostream& stream, const expr_list& list)
{
    expr_list::const_iterator iter = list.begin();
    stream << "[";
    while (iter != list.end()) {
        (*iter)->format(stream);
        iter++;
        if (iter != list.end()) stream << ", ";
    }
    stream << "]";
}

