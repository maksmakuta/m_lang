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
        ast::Declaration parseDeclaration();
        ast::Interface parseInterface();
        ast::Function parseFunction();
        ast::Import parseImport();
        ast::Class parseClass();
        ast::Enum parseEnum();

        [[nodiscard]] bool isEnd() const;
        [[nodiscard]] bool is(const std::initializer_list<lexer::Token>&) const;
        [[nodiscard]] bool is(lexer::Token token) const;
        [[nodiscard]] lexer::Lexem current() const;

        bool isNext(lexer::Token token);
        void consume(lexer::Token);

        const lexer::Lexems& lexems;
        size_t i = 0;
    };

}

#endif //PARSER_HPP
