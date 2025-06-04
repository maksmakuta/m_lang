#include "mlang/Parser.hpp"

namespace mlang {
    Parser::Parser(std::vector<Lexem>& lexems) : m_data(lexems) {}

    std::shared_ptr<Program> Parser::parse() {
        auto program = std::make_shared<Program>();
        return program;
    }
}