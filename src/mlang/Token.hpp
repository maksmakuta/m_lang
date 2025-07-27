#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "Lexem.hpp"

namespace mlang {

    struct Token {
        Lexem lexem;
        std::string value;
        std::pair<int, int> position;
    };

}

#endif //TOKEN_HPP
