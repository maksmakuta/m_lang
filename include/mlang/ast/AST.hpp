#ifndef AST_HPP
#define AST_HPP

#include <optional>
#include <variant>
#include <vector>

#include "mlang/Token.hpp"

namespace mlang {

    enum class Visibility {
        Public,
        Private,
        Protected
    };

    struct Type {
        std::string name;
        std::vector<Type> targs;
    };

    struct ExprLiteral;
    struct ExprVariable;
    struct ExprUnary;
    struct ExprBinary;
    struct ExprCall;
    struct ExprGet;
    struct ExprSet;
    struct ExprIndex;
    struct ExprInterpolation;

    using Expression = std::variant<
        ExprLiteral,
        ExprVariable,
        ExprUnary,
        ExprBinary,
        ExprCall,
        ExprGet,
        ExprSet,
        ExprIndex,
        ExprInterpolation
    >;

    struct ExprLiteral {
        std::string value;
    };

    struct ExprVariable {
        std::string name;
    };

    struct ExprUnary {
        Token op = Token::Unknown;
        Expression operand;
    };

    struct ExprBinary {
        Token op = Token::Unknown;
        Expression left;
        Expression right;
    };

    struct ExprCall {
        Expression callee;
        std::vector<Expression> args;
    };

    struct ExprGet {
        Expression object;
        std::string field;
    };

    struct ExprSet {
        Expression object;
        std::string field;
        Expression value;
    };

    struct ExprIndex {
        Expression object;
        size_t index = 0;
    };

    struct ExprInterpolation {
        std::string templateString;
        std::vector<Expression> expressions;
    };

    struct Variable {
        Visibility visibility;
        std::string name;
        Type type;
        std::optional<Expression> value;
    };

    struct StmtExpr;
    struct StmtBlock;
    struct StmtVar;
    struct StmtIf;
    struct StmtWhile;
    struct StmtMatch;
    struct StmtStop;
    struct StmtNext;

    using Statement = std::variant<
        StmtExpr,
        StmtBlock,
        StmtVar,
        StmtIf,
        StmtWhile,
        StmtMatch,
        StmtStop,
        StmtNext
    >;

    struct StmtExpr {
        Expression expression;
    };

    struct StmtBlock {
        std::vector<Statement> statements;
    };

    struct StmtVar {
        Variable var;
    };

    struct StmtIf {
        Expression condition;
        Statement thenBranch;
        std::optional<Statement> elseBranch;
    };

    struct StmtWhile {
        Expression condition;
        Statement thenBranch;
    };

    struct StmtMatch {
        Expression condition;
        Statement body;
    };

    struct StmtStop{};
    struct StmtNext{};

    struct ImportDeclaration;
    struct FunctionDeclaration;
    struct StructDeclaration;
    struct EnumDeclaration;
    struct ClassDeclaration;

    using Declaration = std::variant<
        ImportDeclaration,
        FunctionDeclaration,
        StructDeclaration,
        EnumDeclaration,
        ClassDeclaration
    >;

    struct ImportDeclaration {
        std::string path;
    };

    struct FunctionDeclaration {
        Visibility visibility;
        bool isAbstract;
        std::string name;
        std::vector<Type> templateArgs;
        std::vector<Variable> args;
        std::optional<Type> returnType;
        StmtBlock block;
    };

    struct StructDeclaration {
        Visibility visibility;
        std::string name;
        std::vector<Type> templateArgs;
        std::vector<Variable> fields;
    };

    struct EnumItem {
        std::string name;
        std::optional<Expression> value;
    };

    struct EnumDeclaration {
        Visibility visibility;
        std::string name;
        std::vector<EnumItem> items;
    };

    struct ConstructorDeclaration {
        Visibility visibility;
        std::vector<Variable> args;
        StmtBlock block;
    };

    struct InterfaceDeclaration {
        Visibility visibility;
        std::string name;
        std::vector<FunctionDeclaration> functions;
    };

    struct ClassDeclaration {
        Visibility visibility;
        bool isAbstract;
        std::string name;
        std::vector<Type> parents;
        std::vector<Type> templateArgs;
        std::vector<ConstructorDeclaration> constructors;
        std::vector<FunctionDeclaration> functions;
        std::vector<Variable> variables;
    };

}

#endif //AST_HPP
