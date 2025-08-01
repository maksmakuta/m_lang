#include "Lexem.hpp"

#include <vector>

namespace mlang {

    std::string to_string(const Lexem& lexem) {
        return std::vector<std::string>{
            "UNKNOWN",

            "INTEGER", "REAL", "STRING", "CHAR", "IDENTIFIER",

            "FUNCTION", "ENUM", "STRUCT", "INTERFACE", "CLASS",
            "ABSTRACT", "PUBLIC", "PRIVATE", "PROTECTED", "OVERRIDE",
            "VAL", "VAR", "FOR", "WHILE", "DO", "MATCH", "LOOP",
            "IF", "ELSE", "IMPORT", "RETURN", "NEXT", "STOP",

            "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO",
            "AND", "OR", "NOT", "XOR", "INV",
            "ASSIGN", "GREAT", "LESS",
            "SHL", "SHR",

            "PLUS_EQ", "MINUS_EQ", "MULTIPLY_EQ", "DIVIDE_EQ", "MODULO_EQ",
            "AND_EQ", "OR_EQ", "NOT_EQ", "XOR_EQ", "INV_EQ",
            "EQUAL", "GREAT_EQ", "LESS_EQ",
            "SHL_EQ", "SHR_EQ",

            "INC", "DEC",
            "TRUE", "FALSE",

            "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACK", "RBRACK",

            "END_OF_FILE"
        }[static_cast<size_t>(lexem)];
    }


}
