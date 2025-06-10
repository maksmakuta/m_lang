#ifndef PARSER_HPP
#define PARSER_HPP

#include <variant>

#include "mlang/ast/AST.hpp"
#include "mlang/lexer/Lexer.hpp"

namespace mlang::parser {

    class Parser {
    public:
        explicit Parser(const lexer::Lexems&);
        ast::Program parse();

    private:
        // utils
        [[nodiscard]] bool isEnd() const;
        [[nodiscard]] bool isCurrent(lexer::Token token) const;

        [[nodiscard]] lexer::Token current() const;
        std::string consume(lexer::Token token);

        void inc();
        static void error(const std::string & msg);

        // subtasks
        ast::ImportDecl parseImport();
        ast::FunctionDecl parseFunction();
        ast::InterfaceDecl parseInterface();
        ast::StructDecl parseStruct();
        ast::ClassDecl parseClass();
        ast::EnumDecl parseEnum();

        // metatasks
        ast::Declaration parseDeclaration();

        const lexer::Lexems& lexems;
        size_t i = 0;
    };

}

#endif //PARSER_HPP
