#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include <vector>

#include "AST.hpp"
#include "Token.hpp"

namespace mlang {

    ASTNodePtr parse(const std::vector<Token> &tokens);

}

#endif //PARSER_HPP
