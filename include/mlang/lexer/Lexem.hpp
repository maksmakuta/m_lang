#ifndef LEXEM_HPP
#define LEXEM_HPP

#include <string>

#include "Token.hpp"

namespace mlang::lexer {

    struct Lexem {
        std::string value;
        Token token;
    };

}

#endif //LEXEM_HPP
