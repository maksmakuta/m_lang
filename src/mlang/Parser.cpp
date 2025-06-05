#include "mlang/Parser.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

namespace mlang {
    Parser::Parser(std::vector<Lexem>& lexems) : m_data(lexems) {}

    std::shared_ptr<Program> Parser::parse() {
        auto program = std::make_shared<Program>();
        while (!isEnd()) {
            program->declarations.push_back(parseDeclaration());
        }
        std::cout << "\n\n\n";
        return program;
    }

    Type Parser::parseType() {
        if (current().token == Token::Colon) {
            inc();
        }

        Type t{};
        if (current().token != Token::Identifier) {
            error("Expected type name, received : " + toString(current().token));
            return {};
        }
        t.name = current().text;
        inc();

        if (current().token != Token::Less) {
            while (current().token != Token::Greater) {
                if (current().token == Token::Comma) {
                    inc();
                }
                t.targs.push_back(parseType());
            }
        }

        if (current().token == Token::Greater) {
            inc();
        }

        return t;
    }

    ImportDeclaration Parser::parseImport() {
        inc();
        if (current().token == Token::String) {
            inc();
            return ImportDeclaration{prev().text};
        }
        error("Expected String, received : " + toString(current().token));
        return {};
    }

    InterfaceDeclaration Parser::parseInterface(){

    }

    FunctionDeclaration Parser::parseFunction(){
        FunctionDeclaration fun{};

        fun.isAbstract = current().token == Token::Abstract;

        if (!fun.isAbstract) {
            switch(prev().token) {
                case Token::Pub:
                    fun.visibility = Visibility::Public;
                    break;
                case Token::Prot:
                    fun.visibility = Visibility::Protected;
                    break;
                default:
                    fun.visibility = Visibility::Private;
                    break;
            }
        }

        if (current().token != Token::Function) {
            error("Expected 'fn', received:" + toString(current().token));
            return {};
        }
        inc();

        if (current().token == Token::Less) {
            // TODO get generics parameters
            while (current().token != Token::Greater) {
                inc();
            }
            inc();
        }

        if (current().token != Token::Identifier) {
            error("Expected function name, received:" + toString(current().token));
            return {};
        }
        fun.name = current().text;
        inc();

        if (current().token != Token::BracketStart) {
            error("Expected '(', received:" + toString(current().token));
            return {};
        }
        //TODO read arguments
        while (current().token != Token::BracketEnd) {
            inc();
        }
        inc();

        if (current().token == Token::Colon) {
            inc();
            fun.returnType = parseType();
        }

        if (!fun.isAbstract && current().token == Token::BracketCurlyStart) {
            fun.block = parseBlock();
            inc();
        }

        return fun;
    }

    StructDeclaration Parser::parseStruct(){

    }

    EnumDeclaration Parser::parseEnum(){

    }

    ClassDeclaration Parser::parseClass(){

    }

    Declaration Parser::parseDeclaration(){
        if (current().token == Token::Pub ||
            current().token == Token::Priv ||
            current().token == Token::Prot ) inc();

        switch (current().token) {
            case Token::Import:
                return parseImport();
            case Token::Interface:
                return parseInterface();
            case Token::Function:
                return parseFunction();
            case Token::Struct:
                return parseStruct();
            case Token::Enum:
                return parseEnum();
            case Token::Abstract:
            case Token::Class:
                return parseClass();
            default:
                error("Wrong token for declaration");
                return {};
        }
    }

    StmtExpr Parser::parseExpr() {
        return StmtExpr{parseExpression()};
    }

    StmtBlock Parser::parseBlock() {
        while (current().token != Token::BracketCurlyEnd) {
            inc();
        }
        return {};
    }
    StmtVar Parser::parseVar(){}
    StmtIf Parser::parseIf(){}
    StmtWhile Parser::parseWhile(){}
    StmtMatch Parser::parseMatch(){}
    StmtStop Parser::parseStop(){}
    StmtNext Parser::parseNext(){}
    Statement Parser::parseStatement(){}

    ExprLiteral Parser::parseLiteral(){}
    ExprVariable Parser::parseVariable(){}
    ExprUnary Parser::parseUnary(){}
    ExprBinary Parser::parseBinary(){}
    ExprCall Parser::parseCall(){}
    ExprGet Parser::parseGet(){}
    ExprSet Parser::parseSet(){}
    ExprIndex Parser::parseIndex(){}
    ExprInterpolation Parser::parseInterpolation(){}
    Expression Parser::parseExpression(){}

    Lexem Parser::current() const {
        std::cout << "token[" << index << "] = " << toString(m_data[index].token) << " | " << m_data[index].text << std::endl;
        return m_data[index];
    }

    Lexem Parser::prev() const {
        return m_data[index-1];
    }

    void Parser::inc() {
        ++index;
    }

    void Parser::error(const std::string& err) const {
        std::cerr << "Error at line " << toString(current().position) << " -> " << std::endl << err << std::endl;
        exit(EXIT_FAILURE);
    }

    bool Parser::is(const std::initializer_list<Token>& tokens) const {
        return std::ranges::any_of(tokens,[this](const Token& t) {
            return current().token == t;
        });
    }

    bool Parser::isEnd() const {
        return index >= m_data.size() || m_data[index].token == Token::EndOfFile;
    }
}
