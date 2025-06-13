#include "mlang/parser/Parser.hpp"

#include <iostream>

namespace mlang::parser {
    Parser::Parser(const lexer::Lexems& in) : lexems(in){}

    ast::Program Parser::parse() {
        ast::Program program{};
        while (!isEnd()) {
            program.push_back(parseDecl());
        }
        return program;
    }

    ast::Declaration Parser::parseDecl() {
        switch (current().token) {
            case lexer::Token::Import:
                return parseImport();

            case lexer::Token::Function:
                return parseFunction();

            case lexer::Token::Interface:
                return parseInterface();

            case lexer::Token::Enum:
                return parseEnum();

            case lexer::Token::Abstract:
            case lexer::Token::Class:
                return parseClass();

            default:

                std::cerr << "Wrong token " << lexer::toString(current().token) << " for declaration" << std::endl;
                return {};
        }
    }

    ast::ImportDecl Parser::parseImport(){

    }

    ast::FunctionDecl Parser::parseFunction(){
    }

    ast::InterfaceDecl Parser::parseInterface(){

    }

    ast::EnumDecl Parser::parseEnum(){

    }

    ast::ClassDecl Parser::parseClass(){

    }

    bool Parser::isEnd() const {
        return i >= lexems.size() || lexems[i].token == lexer::Token::EndOfFile;
    }

    bool Parser::check(const lexer::Token t) {
        return current().token == t;
    }
    lexer::Lexem Parser::current() const {
        return lexems[i];
    }

    void Parser::advance() {
        ++i;
    }

    void panic(const std::string& m) {
        std::cerr << "Error: " << m << std::endl;
        exit(EXIT_FAILURE);
    }

    void Parser::expect(const lexer::Token t) {
        if (current().token != t)
            panic("unexpected token");
        advance();
    }

}
