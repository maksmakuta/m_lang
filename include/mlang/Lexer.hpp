#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

#include "mlang/Token.hpp"
#include "mlang/Utils.hpp"

namespace mlang {

    struct Lexem {
        Token token;
        std::string text;
        Position position;
    };

    class Lexer {
    public:
        explicit Lexer(std::string& buffer);

        std::vector<Lexem> toTokens();
    private:

        Lexem lexIdentifierOrKeyword();
        Lexem lexNumber();
        Lexem lexString();
        Lexem lexSymbol();

        [[nodiscard]] char peek() const;
        char advance();
        bool match(char expected);
        void skipWhitespace();

        std::string& m_buffer;
        size_t pointer = 0;
        Position pos;
    };

}

#endif //LEXER_HPP
