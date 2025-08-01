#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <format>
#include <string>

#include "Lexem.hpp"

namespace mlang {

    struct Position {
        int line;
        int column;
    };

    struct Token {
        Lexem lexem;
        std::string value;
        Position position;
    };

    inline std::string to_string(const Token& token) {
        using namespace std;
        return format("[{} '{}', {}:{}]",
            to_string(token.lexem),
            token.value,
            token.position.line,
            token.position.column
        );
    }

}

#endif //TOKEN_HPP
