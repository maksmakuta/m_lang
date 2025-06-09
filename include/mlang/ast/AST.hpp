#ifndef AST_HPP
#define AST_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <variant>
#include <optional>

namespace mlang::ast {

    enum Visibility : uint8_t {
        Public      = 0,
        Private     = 1,
        Protected   = 2,
    };

    enum Flag : uint8_t {
        isConst     = 1 << 3,
        isAbstract  = 1 << 4,
        isNullable  = 1 << 5,
        isVararg    = 1 << 6,
    };

    struct Type {
        std::string base;
        std::vector<Type> generics;
    };

    struct Argument {
        std::string name;
        Type type;
    };

    struct LiteralExpr;
    struct VariableExpr;
    struct BinaryExpr;
    struct UnaryExpr;
    struct CallExpr;

    using Expression = std::variant<
        LiteralExpr,
        VariableExpr,
        BinaryExpr,
        UnaryExpr,
        CallExpr
    >;

    struct VarStmt;
    struct BlockStmt;
    struct IfStmt;
    struct MatchStmt;
    struct WhileStmt;
    struct ReturnStmt;
    struct ForStmt;

    using Statement = std::variant<
        VarStmt,
        BlockStmt,
        IfStmt,
        MatchStmt,
        WhileStmt,
        ReturnStmt,
        ForStmt
    >;

    struct ImportDecl {
        std::string path;
    };

    struct FunctionDecl {
        std::string name;
        std::vector<Type> generics;
        std::vector<Argument> args;
        std::optional<Type> returns;
        uint8_t flags;
    };

    struct EnumItem {
        std::string name;
        int value;
    };

    struct EnumDecl {
        std::string name;
        std::vector<EnumItem> items;
        uint8_t flags;
    };

    struct InterfaceDecl {
        std::string name;
        std::vector<FunctionDecl> functions;
        uint8_t flags;
    };

    struct StructDecl {
        std::string name;
        std::vector<Argument> fields;
        uint8_t flags;
    };

    struct ClassDecl {
        std::string name;
        std::vector<Type> extends;
        std::vector<FunctionDecl> functions;
        std::vector<Argument> fields;
        uint8_t flags;
    };

    using Declaration = std::variant<
        ImportDecl,
        FunctionDecl,
        EnumDecl,
        InterfaceDecl,
        StructDecl,
        ClassDecl
    >;

    using Program = std::vector<Declaration>;

}
#endif //AST_HPP
