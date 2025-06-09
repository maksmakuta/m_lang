#ifndef PARSER_HPP
#define PARSER_HPP

#include "mlang/ast/AST.hpp"
#include "mlang/lexer/Lexer.hpp"

namespace mlang::parser {

    class Parser {
    public:
        Parser() = default;

        ast::Program parse(const lexer::Lexems&);

    private:
        size_t i = 0;
    };

}

#endif //PARSER_HPP
