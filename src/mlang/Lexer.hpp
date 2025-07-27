#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

#include "Token.hpp"

namespace mlang {

    std::vector<Token> tokenize(const std::string &input);

}

#endif //LEXER_HPP
