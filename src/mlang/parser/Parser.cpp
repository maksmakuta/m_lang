#include "mlang/parser/Parser.hpp"

namespace mlang::parser {

    Parser::Parser(const lexer::Lexems& in) : lexems(in){}

    ast::Program Parser::parse() {
        return {};
    }


}