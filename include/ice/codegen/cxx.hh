#ifndef _ICE_CODEGEN_CXX_HH_INCLUDED_
#define _ICE_CODEGEN_CXX_HH_INCLUDED_

#include "ice/ast.hh"

namespace ice {
    namespace codegen {
        bool cxx(const char *filename, ice::ast::module *mod);
    };
};

#endif

