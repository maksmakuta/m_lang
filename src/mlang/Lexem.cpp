#include "Lexem.hpp"

namespace mlang {
    std::string toString(const Lexem l) {
        switch (l) {
            case IDENTIFIER: return "IDENTIFIER";
            case STRING: return "STRING";
            case INT: return "INT";
            case REAL: return "REAL";
            case VAL: return "VAL";
            case VAR: return "VAR";
            case IMPORT: return "IMPORT";
            case FUNCTION: return "FUNCTION";
            case STRUCT: return "STRUCT";
            case PLUS: return "PLUS";
            case MINUS: return "MINUS";
            case MULTIPLY: return "MULTIPLY";
            case DIVIDE: return "DIVIDE";
            case MOD: return "MOD";
            case ASSIGN: return "ASSIGN";
            case LESS: return "LESS";
            case MORE: return "MORE";
            case NOT: return "NOT";
            case INV: return "INV";
            case AND: return "AND";
            case OR: return "OR";
            case XOR: return "XOR";
            case DOT: return "DOT";
            case COMMA: return "COMMA";
            case COLON: return "COLON";
            case PLUS_EQ: return "PLUS_EQ";
            case MINUS_EQ: return "MINUS_EQ";
            case MULTIPLY_EQ: return "MULTIPLY_EQ";
            case DIVIDE_EQ: return "DIVIDE_EQ";
            case MOD_EQ: return "MOD_EQ";
            case EQ: return "EQ";
            case LESS_EQ: return "LESS_EQ";
            case MORE_EQ: return "MORE_EQ";
            case NOT_EQ: return "NOT_EQ";
            case INV_EQ: return "INV_EQ";
            case AND_EQ: return "AND_EQ";
            case OR_EQ: return "OR_EQ";
            case XOR_EQ: return "XOR_EQ";
            case PAREN_LEFT: return "PAREN_LEFT";
            case PAREN_RIGHT: return "PAREN_RIGHT";
            case BRACKET_LEFT: return "BRACKET_LEFT";
            case BRACKET_RIGHT: return "BRACKET_RIGHT";
            case BRACE_LEFT: return "BRACE_LEFT";
            case BRACE_RIGHT: return "BRACE_RIGHT";
            case END: return "END";
            default: return "UNKNOWN";
        }
    }
}
