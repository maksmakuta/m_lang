#ifndef CXXGENERATOR_HPP
#define CXXGENERATOR_HPP

#include <sstream>
#include "mlang/ast/AST.hpp"

namespace mlang {

    class CxxGenerator {
    public:
        CxxGenerator() = default;
        ~CxxGenerator() = default;

        void visit(std::stringstream&, const Type&) const;
        void visit(std::stringstream&, const Variable&) const;

        void visit(std::stringstream&, const ExprLiteral&) const;
        void visit(std::stringstream&, const ExprVariable&) const;
        void visit(std::stringstream&, const ExprUnary&) const;
        void visit(std::stringstream&, const ExprBinary&) const;
        void visit(std::stringstream&, const ExprCall&) const;
        void visit(std::stringstream&, const ExprGet&) const;
        void visit(std::stringstream&, const ExprSet&) const;
        void visit(std::stringstream&, const ExprIndex&) const;
        void visit(std::stringstream&, const ExprInterpolation&) const;

        void visit(std::stringstream&, const StmtExpr&) const;
        void visit(std::stringstream&, const StmtBlock&) const;
        void visit(std::stringstream&, const StmtVar&) const;
        void visit(std::stringstream&, const StmtIf&) const;
        void visit(std::stringstream&, const StmtWhile&) const;
        void visit(std::stringstream&, const StmtMatch&) const;
        void visit(std::stringstream&, const StmtStop&) const;
        void visit(std::stringstream&, const StmtNext&) const;

        void visit(std::stringstream&, const ImportDeclaration&) const;
        void visit(std::stringstream&, const InterfaceDeclaration&) const;
        void visit(std::stringstream&, const FunctionDeclaration&) const;
        void visit(std::stringstream&, const StructDeclaration&) const;
        void visit(std::stringstream&, const EnumDeclaration&) const;
        void visit(std::stringstream&, const ClassDeclaration&) const;

        void visit(std::stringstream&, const std::shared_ptr<Program> &) const;
    };

}

#endif //CXXGENERATOR_HPP
