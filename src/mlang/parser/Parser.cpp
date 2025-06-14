#include "mlang/parser/Parser.hpp"

#include <algorithm>
#include <iostream>

namespace mlang::parser {
    Parser::Parser(const lexer::Lexems& in) : lexems(in){}

    ast::Program Parser::parse() {
        ast::Program program{};
        while (!isEnd()) {
            program.push_back(parseDeclaration());
            ++i;
        }
        return program;
    }

    ast::Declaration Parser::parseDeclaration() {
        if (is({lexer::Token::Pub,lexer::Token::Priv,lexer::Token::Prot})) {
            ++i;
        }

        switch (lexems[i].token) {
            case lexer::Token::Import:
                return parseImport();
            case lexer::Token::Function:
                return parseFunction();
            case lexer::Token::Enum:
                return parseEnum();
            case lexer::Token::Interface:
                return parseInterface();
            case lexer::Token::Abstract:
            case lexer::Token::Class:
                return parseClass();
            default:
                throw std::runtime_error("Unknown declaration type");
        }
    }
    ast::Interface Parser::parseInterface(){

    }

    ast::Function Parser::parseFunction(){

    }

    ast::Import Parser::parseImport(){
        if (isNext(lexer::Token::String)) {
            return ast::Import(current().value);
        }
        throw std::runtime_error("Unknown import type");
    }

    ast::Class Parser::parseClass(){

    }

    ast::Enum Parser::parseEnum(){

    }

    bool Parser::isEnd() const {
        return i >= lexems.size() || lexems[i].token == lexer::Token::EndOfFile;
    }

    bool Parser::is(const std::initializer_list<lexer::Token>& tokens) const {
        return std::ranges::any_of(tokens, [this](const auto &t) {
            return t == lexems[i].token;
        });
    }

    bool Parser::is(const lexer::Token token) const {
        return token == lexems[i].token;
    }

    lexer::Lexem Parser::current() const {
        return lexems[i];
    }

    bool Parser::isNext(const lexer::Token token) {
        ++i;
        if (isEnd()) return false;
        return is(token);
    }

    void Parser::consume(const lexer::Token token) {
        if (!isEnd() && lexems[i].token == token) {
            ++i;
        } else {
            throw std::runtime_error("Unexpected token + " + toString(lexems[i].token) + " at position " + std::to_string(i));
        }
    }
}
