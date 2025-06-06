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

        if (current().token == Token::Less) {
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
       return {};
    }

    StructDeclaration Parser::parseStruct(){
        StructDeclaration s{};
        inc();

        if (current().token != Token::Identifier) {
            error("Expected struct name, received: " + toString(current().token));
            return {};
        }
        s.name = current().text;
        inc();

        if (current().token == Token::BracketCurlyStart) {
            inc();
            while (true) {
                if (current().token == Token::BracketCurlyEnd)
                    break;
                s.fields.push_back(parseVar().var);
                if (current().token == Token::Comma) {
                    inc();
                }
            }
        }
        inc();

        return s;
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
        StmtBlock b{};
        while (current().token != Token::BracketCurlyEnd) {
            b.statements.push_back(parseStatement());
        }
        return b;
    }

    StmtVar Parser::parseVar() {
        StmtVar v{};

        switch (prev().token) {
            case Token::Pub:
                v.var.visibility = Visibility::Public;
                break;
            case Token::Prot:
                v.var.visibility = Visibility::Protected;
                break;
            default:
                v.var.visibility = Visibility::Private;
                break;
        }

        v.var.isConst = current().token == Token::Const;
        if (v.var.isConst) inc();

        if (current().token != Token::Identifier) {
            error("Expected variable name, received: " + toString(current().token));
            return {};
        }
        v.var.name = current().text;
        inc();

        if (current().token != Token::Colon) {
            error("Expected ':', received: " + current().text);
            return {};
        }
        v.var.type = parseType();

        return v;
    }
    StmtIf Parser::parseIf(){}
    StmtWhile Parser::parseWhile(){}
    StmtWhile Parser::parseFor() {}
    StmtMatch Parser::parseMatch(){}

    StmtStop Parser::parseStop() {
        return {};
    }

    StmtNext Parser::parseNext() {
        return {};
    }

    Statement Parser::parseStatement() {
        switch (current().token) {
            case Token::Const:
            case Token::Let:
                return parseVar();
            case Token::BracketCurlyStart:
                return parseBlock();
            case Token::If:
                return parseIf();
            case Token::While:
                return parseWhile();
            case Token::For:
                return parseFor();
            case Token::Match:
                return parseMatch();
            case Token::Stop:
                return parseStop();
            case Token::Next:
                return parseNext();
            default:
                return parseExpr();
        }
    }

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
