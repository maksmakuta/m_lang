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
        const lexer::Lexems& lexems;
        size_t i = 0;
    };

}

#endif //PARSER_HPP
