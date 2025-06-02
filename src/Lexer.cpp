#include "mlang/Lexer.hpp"

namespace mlang {

    void Position::newline() {
        line++;
        column = 0;
    }

    Lexer::Lexer(std::string& buffer) : m_buffer(buffer), pos(1,0){}

    std::vector<Lexem> Lexer::toTokens() {
        std::vector<Lexem> tokens;
        while (pointer < m_buffer.size()) {
            skipWhitespace();
            char c = peek();
            if (std::isalpha(c) || c == '_') {
                tokens.push_back(lexIdentifierOrKeyword());
            } else if (std::isdigit(c)) {
                tokens.push_back(lexNumber());
            } else if (c == '"') {
                tokens.push_back(lexString());
            } else if (std::ispunct(c)) {
                tokens.push_back(lexSymbol());
            } else {
                advance();
            }
        }
        tokens.emplace_back(Token::EndOfFile, "", pos);
        return tokens;
    }

    Lexem Lexer::lexIdentifierOrKeyword(){
        size_t start = pointer;
        while (std::isalnum(peek()) || peek() == '_') advance();
        std::string text = m_buffer.substr(start, pointer - start);

        if (text == "fn") {
            return Lexem(Token::Function, text, pos);
        }
        if (text == "let") {
            return Lexem(Token::Let, text, pos);
        }

        return Lexem(Token::Identifier, text, pos);
    }

    Lexem Lexer::lexNumber(){
        const size_t start = pointer;
        while (std::isdigit(peek())) advance();
        if (peek() == '.') {
            advance();
            while (std::isdigit(peek())) advance();
        }
        return Lexem(Token::Number, m_buffer.substr(start, pointer - start), pos);
    }

    Lexem Lexer::lexString(){
        advance();
        const size_t start = pointer;
        while (peek() != '"' && peek() != '\0') {
            if (peek() == '\n') pos.newline();
            advance();
        }
        std::string content = m_buffer.substr(start, pointer - start);
        if (peek() == '"') advance();
        return Lexem(Token::String, content, pos);
    }

    Lexem Lexer::lexSymbol(){
        const char c = advance();
        Token type = Token::Unknown;
        switch (c) {
            case ':':
                type = Token::Colon;
                break;
            case '(':
                type = Token::BracketStart;
                break;
            case ')':
                type = Token::BracketEnd;
                break;
            case '{':
                type = Token::BracketCurlyStart;
                break;
            case '}':
                type = Token::BracketCurlyEnd;
                break;
            case '[':
                type = Token::BracketSquareStart;
                break;
            case ']':
                type = Token::BracketSquareEnd;
                break;
            default:
                type = Token::Unknown;
                break;
        }
        return Lexem(type, std::string(1, c), pos);
    }

    char Lexer::peek() const{
        return pointer < m_buffer.size() ? m_buffer[pointer] : '\0';
    }

    char Lexer::advance(){
        return pointer < m_buffer.size() ? m_buffer[pointer++] : '\0';
    }

    bool Lexer::match(const char expected){
        if (peek() == expected) {
            ++pointer;
            return true;
        }
        return false;
    }

    void Lexer::skipWhitespace(){
        while (true) {
            const char c = peek();
            if (c == ' ' || c == '\t' || c == '\r') {
                advance();
            } else if (c == '\n') {
                pos.newline();
                advance();
            } else {
                break;
            }
        }
    }


}