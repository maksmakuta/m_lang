#include "mlang/codegen/ASTPrinter.hpp"

#include <sstream>

namespace mlang::codegen {

    ASTPrinter::ASTPrinter(const ast::Program& p) : m_program(p){}

    std::string ASTPrinter::toString(int layer) {
        std::stringstream buffer;

        return buffer.str();
    }

}