#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>

#include "Lexem.hpp"

namespace mlang::lexer {

    using Lexems = std::vector<Lexem>;

    Lexems lex(const std::string&);

}

#endif //LEXER_HPP
