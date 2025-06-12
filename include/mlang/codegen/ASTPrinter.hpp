#ifndef ASTPRINTER_HPP
#define ASTPRINTER_HPP

#include "mlang/ast/AST.hpp"

namespace mlang::codegen {

    class ASTPrinter {
    public:
        explicit ASTPrinter(const ast::Program&);
        std::string toString(int layer = 0);
    private:

        const ast::Program& m_program;
    };

}

#endif //ASTPRINTER_HPP
