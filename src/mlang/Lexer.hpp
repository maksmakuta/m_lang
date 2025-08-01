#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "Token.hpp"

namespace mlang {

    class Lexer {
    public:
        Lexer() = default;

        std::vector<Token> tokenize(const std::string& input);

        int line = 1;

    private:
        Token getNumber();
        Token getString();
        Token getChar();
        Token getIdentifier();

        [[nodiscard]] bool isNext(char c) const;

        std::string source;
        uint32_t index{0};
    };

} // mlang

#endif //LEXER_HPP
