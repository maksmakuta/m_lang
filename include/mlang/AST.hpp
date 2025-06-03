#ifndef AST_HPP
#define AST_HPP

#include <variant>
#include <vector>
#include <string>
#include <memory>
#include <optional>

namespace mlang {

    struct ImportDecl {
        std::string path;
    };

    struct StructField {
        std::string type;
        std::string name;
    };

    struct StructDecl {
        std::string name;
        std::vector<std::string> typeParams;
        std::vector<StructField> fields;
    };

    struct BinaryExpr;
    struct CallExpr;
    struct VariableExpr;
    struct LiteralExpr;

    using Expr = std::variant<
        BinaryExpr,
        CallExpr,
        VariableExpr,
        LiteralExpr
    >;

    struct Parameter {
        std::string name;
        std::string type;
        std::optional<std::shared_ptr<Expr>> defaultValue;
    };

    struct VarDecl;
    struct ReturnStmt;
    struct ExprStmt;

    using Stmt = std::variant<
        VarDecl,
        ReturnStmt,
        ExprStmt
    >;

    struct VarDecl {
        std::string name;
        std::string type;
        std::shared_ptr<Expr> initializer;
    };

    struct ReturnStmt {
        std::shared_ptr<Expr> value;
    };

    struct ExprStmt {
        std::shared_ptr<Expr> expr;
    };

    struct FunctionDecl {
        std::string name;
        std::vector<std::string> typeParams;
        std::vector<Parameter> params;
        std::optional<std::string> returnType;
        std::vector<std::shared_ptr<Stmt>> body;
    };

    struct BinaryExpr {
        std::shared_ptr<Expr> left;
        std::string op;
        std::shared_ptr<Expr> right;
    };

    struct CallExpr {
        std::string callee;
        std::vector<std::shared_ptr<Expr>> args;
    };

    struct VariableExpr {
        std::string name;
    };

    struct LiteralExpr {
        std::string value;
    };

    using TopLevelDecl = std::variant<
        ImportDecl,
        StructDecl,
        FunctionDecl
    >;

    struct Program {
        std::vector<TopLevelDecl> declarations;
    };

}

#endif //AST_HPP
