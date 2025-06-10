#include "mlang/parser/Parser.hpp"

#include <iostream>

namespace mlang::parser {

    Parser::Parser(const lexer::Lexems& in) : lexems(in){}

    ast::Program Parser::parse() {
        ast::Program program{};
        while (!isEnd()) {
            program.push_back(parseDeclaration());
            inc();
        }
        return program;
    }

    bool Parser::isEnd() const {
        return i >= lexems.size() || isCurrent(lexer::Token::EndOfFile);
    }

    bool Parser::isCurrent(const lexer::Token token) const {
        return lexems[i].token == token;
    }

    lexer::Token Parser::current() const {
        return lexems[i].token;
    }

    std::string Parser::consume(const lexer::Token token){
        inc();
        if (isCurrent(token)) {
            return lexems[i].value;
        }
        error("Expected: " + lexer::toString(token) + " found: " + lexer::toString(current()));
        return {};
    }

    void Parser::inc() {
        ++i;
    }

    void Parser::error(const std::string &msg) {
        std::cerr << "Error: " << msg << std::endl;
        exit(-1);
    }

    ast::ImportDecl Parser::parseImport() {
        return ast::ImportDecl(consume(lexer::Token::String));
    }

    ast::FunctionDecl Parser::parseFunction(){
        return {};
    }

    ast::InterfaceDecl Parser::parseInterface(){
        return {};
    }

    ast::StructDecl Parser::parseStruct(){
        return {};
    }

    ast::ClassDecl Parser::parseClass(){
        return {};
    }

    ast::EnumDecl Parser::parseEnum(){
        return {};
    }

    ast::Declaration Parser::parseDeclaration() {
        switch (current()) {
            case lexer::Token::Import:
                return parseImport();
            case lexer::Token::Function:
                return parseFunction();
            case lexer::Token::Interface:
                return parseInterface();
            case lexer::Token::Enum:
                return parseEnum();
            case lexer::Token::Struct:
                return parseStruct();
            case lexer::Token::Abstract:
            case lexer::Token::Class:
                return parseClass();
            default:
                error("Unknown token for declaration: " + toString(current()));
                return {};
        }
    }
}
