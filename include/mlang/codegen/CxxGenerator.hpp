#ifndef CXXGENERATOR_HPP
#define CXXGENERATOR_HPP

#include "mlang/ast/AST.hpp"

namespace mlang {

    class CxxGenerator {
    public:
        CxxGenerator() = default;
        ~CxxGenerator() = default;

        void operator()(const ImportDeclaration&) const;
        void operator()(const InterfaceDeclaration&);
        void operator()(const FunctionDeclaration&);
        void operator()(const StructDeclaration&);
        void operator()(const EnumDeclaration&);
        void operator()(const ClassDeclaration&);

        void visit(const std::shared_ptr<Program> &);
    };

}

#endif //CXXGENERATOR_HPP
