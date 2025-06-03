#include "mlang/Parser.hpp"

#include <iostream>

namespace mlang {

    Parser::Parser(std::vector<Lexem>& lexems) : m_data(lexems){}

    std::shared_ptr<Program> Parser::parse() {
        const auto program = std::make_shared<Program>();

        return program;
    }

    Lexem& Parser::peek() const {
        return m_data[current];
    }

    Lexem& Parser::previous() const {
        return m_data[current-1];
    }

    Lexem& Parser::advance() {
        if (!isAtEnd()) current++;
        return previous();
    }

    bool Parser::match(const Token type) {
        if (check(type)) {
            advance();
            return true;
        }
        return false;
    }

    bool Parser::matchAny(const std::initializer_list<Token>& types) {
        for (const auto& type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    bool Parser::check(const Token type) const {
        if (isAtEnd()) return false;
        return peek().token == type;
    }

    bool Parser::isAtEnd() const {
        return current >= m_data.size() || m_data[current].token == Token::EndOfFile;
    }

    void Parser::error(const std::string& message) {
        std::cerr << "[Parser Error] at token " << peek().text << ": " << message << std::endl;
        std::exit(1); // or throw a custom exception

    }


}
