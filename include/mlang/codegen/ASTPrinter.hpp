#ifndef ASTPRINTER_HPP
#define ASTPRINTER_HPP

#include <sstream>
#include "mlang/ast/AST.hpp"

namespace mlang::codegen {

    class ASTPrinter {
    public:
        explicit ASTPrinter() = default;
        std::string toString(const ast::Program&,int layer = 0);
    private:
        void toString(const ast::Import&, int);
        void toString(const ast::Function&, int);
        void toString(const ast::Enum&, int);
        void toString(const ast::Struct&, int);
        void toString(const ast::Interface&, int);
        void toString(const ast::Class&, int);

        std::stringstream buffer;
    };

}

#endif //ASTPRINTER_HPP
