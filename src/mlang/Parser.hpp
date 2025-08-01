#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <stdexcept>

#include "AST.hpp"
#include "Token.hpp"

namespace mlang {

    class Parser {
    public:
        explicit Parser(std::vector<Token> tokens);

        ASTNodePtr parse();

    private:
        std::vector<Token> tokens;
        uint32_t index{0};
    };

}

#endif //PARSER_HPP