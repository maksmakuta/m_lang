#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include <variant>

#include "ast/AST.hpp"
#include "mlang/Lexer.hpp"

namespace mlang {

    class Parser {
    public:
        explicit Parser(std::vector<Lexem>& lexems);

        std::shared_ptr<Program> parse();
    private:
        Type parseType();

        ImportDeclaration parseImport();
        InterfaceDeclaration parseInterface();
        FunctionDeclaration parseFunction();
        StructDeclaration parseStruct();
        EnumDeclaration parseEnum();
        ClassDeclaration parseClass();
        Declaration parseDeclaration();

        StmtExpr parseExpr();
        StmtBlock parseBlock();
        StmtVar parseVar();
        StmtIf parseIf();
        StmtWhile parseWhile();
        StmtWhile parseFor();
        StmtMatch parseMatch();
        StmtStop parseStop();
        StmtNext parseNext();

        Statement parseStatement();

        ExprLiteral parseLiteral();
        ExprVariable parseVariable();
        ExprUnary parseUnary();
        ExprBinary parseBinary();
        ExprCall parseCall();
        ExprGet parseGet();
        ExprSet parseSet();
        ExprIndex parseIndex();
        ExprInterpolation parseInterpolation();
        Expression parseExpression();

        void inc();
        void error(const std::string& err) const;
        [[nodiscard]] bool is(const std::initializer_list<Token>& tokens) const;
        [[nodiscard]] bool isEnd() const;
        [[nodiscard]] Lexem current() const;
        [[nodiscard]] Lexem prev() const;

        std::vector<Lexem>& m_data;
        size_t index = 0;
    };

}

#endif //PARSER_HPP
