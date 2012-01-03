#include "ice/ast/call.hh"

ice::ast::call::call(expr *expr, const expr_list& args)
    : _target(expr), _args(args)
{
}

ice::ast::call::~call()
{
    delete _target;
}

ice::ast::expr*
ice::ast::call::get_target() const
{
    return _target;
}

void
ice::ast::call::set_target(expr *expr)
{
    _target = expr;
}

const ice::ast::expr_list&
ice::ast::call::get_args() const
{
    return _args;
}

void
ice::ast::call::accept(visitor *v)
{
    v->enter(this);
    expr_list::const_iterator iter = get_args().begin();
    while (iter != get_args().end()) {
        (*iter)->accept(v);
        iter++;
    }
    v->leave(this);
}

void
ice::ast::call::format(std::ostream& stream) const
{
    stream << "call(target=";
    if (get_target()) {
        get_target()->format(stream);
    }
    else {
        stream << "<unknown>";
    }
    stream << ", args=";
    format_expr_list(stream, get_args());
    stream << ")";
}

