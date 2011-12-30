#include "ice/ast/expr_stmt.hh"

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

void
ice::ast::expr_stmt::format(std::ostream& stream) const
{
    stream << "expr_stmt(expr=";
    get_expr()->format(stream);
    stream << ")";
}

