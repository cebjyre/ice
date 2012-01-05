#ifndef _ICE_AST_HH_INCLUDED_
#define _ICE_AST_HH_INCLUDED_

#include <string>
#include <list>

#include "ice/ast/node.hh"
#include "ice/ast/stmt.hh"
#include "ice/ast/expr.hh"
#include "ice/ast/decl.hh"

// expr
#include "ice/ast/ident.hh"
#include "ice/ast/integer.hh"
#include "ice/ast/string.hh"
#include "ice/ast/call.hh"
#include "ice/ast/getattr.hh"
#include "ice/ast/assign.hh"
#include "ice/ast/alloc.hh"

// decl
#include "ice/ast/func_decl.hh"
#include "ice/ast/var_decl.hh"

// stmt
#include "ice/ast/return_stmt.hh"
#include "ice/ast/expr_stmt.hh"
#include "ice/ast/dealloc.hh"

// module
#include "ice/ast/module.hh"

#include "ice/ast/visitor.hh"

#endif

