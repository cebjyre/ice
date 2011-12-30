#ifndef _ICE_COMPILER_HH_INCLUDED_
#define _ICE_COMPILER_HH_INCLUDED_

namespace ice {
    namespace compiler {
        void
        push_result(ice::ast::module *mod);

        ice::ast::module*
        compile(const char *filename, int fd);
    };
};

#endif

