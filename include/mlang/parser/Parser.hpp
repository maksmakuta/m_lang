#ifndef PARSER_HPP
#define PARSER_HPP

#include "mlang/ast/AST.hpp"
#include "mlang/lexer/Lexer.hpp"

namespace mlang::parser {

    class Parser {
    public:
        explicit Parser(const lexer::Lexems&);
        ast::Program parse();

    private:
        ast::Declaration parseDecl();
        ast::ImportDecl parseImport();
        ast::FunctionDecl parseFunction();
        ast::InterfaceDecl parseInterface();
        ast::EnumDecl parseEnum();
        ast::ClassDecl parseClass();

        [[nodiscard]] bool isEnd() const;
        [[nodiscard]] bool check(lexer::Token);
        [[nodiscard]] lexer::Lexem current() const;
        void advance();
        void expect(lexer::Token);

        const lexer::Lexems& lexems;
        size_t i = 0;
    };

}

#endif //PARSER_HPP
