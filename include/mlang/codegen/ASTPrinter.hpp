#ifndef ASTPRINTER_HPP
#define ASTPRINTER_HPP

#include <sstream>

#include "mlang/ast/AST.hpp"

namespace mlang::codegen {

    class ASTPrinter {
    public:
        explicit ASTPrinter(ast::Program&);
        std::string toString(int layer = 0);

    private:

        void toString(int layer, const ast::ImportDecl&);
        void toString(int layer, const ast::FunctionDecl&);
        void toString(int layer, const ast::EnumDecl&);
        void toString(int layer, const ast::InterfaceDecl&);
        void toString(int layer, const ast::StructDecl&);
        void toString(int layer, const ast::ClassDecl&);


        ast::Program& m_program;
        std::stringstream buffer;
    };

}

#endif //ASTPRINTER_HPP
