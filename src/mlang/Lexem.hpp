#ifndef LEXEM_HPP
#define LEXEM_HPP

#include <string>

namespace mlang {

    enum Lexem {
        UNKNOWN = -1,

        IDENTIFIER, STRING, INT, REAL,

        VAL, VAR, IMPORT, FUNCTION, STRUCT,

        PLUS, MINUS, MULTIPLY, DIVIDE, MOD,
        ASSIGN, LESS, MORE,
        NOT, INV, AND, OR, XOR,
        DOT, COMMA, COLON,

        PLUS_EQ, MINUS_EQ, MULTIPLY_EQ, DIVIDE_EQ, MOD_EQ,
        EQ, LESS_EQ, MORE_EQ,
        NOT_EQ, INV_EQ, AND_EQ, OR_EQ, XOR_EQ,

        PAREN_LEFT, PAREN_RIGHT, BRACKET_LEFT, BRACKET_RIGHT, BRACE_LEFT, BRACE_RIGHT,

        END = 255
    };

    std::string toString(Lexem);

}

#endif //LEXEM_HPP
