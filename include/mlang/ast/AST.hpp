#ifndef AST_HPP
#define AST_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

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
        std::vector<Type> inherits;
    };

    struct Expr {};
    struct Block{};

    struct Argument {
        std::string name;
        Type type;
        std::optional<Expr> value;
    };

    struct Variable {
        Visibility visibility;
        std::string name;
        Type type;
        std::optional<Expr> value;
        uint8_t flags;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct ImportDecl {
        std::string path;
    };

    struct FunctionDecl {
        std::string name;
        Visibility visibility;
        std::vector<Type> generics;
        std::vector<Argument> arguments;
        std::optional<Type> returns;
        std::optional<Block> body;
        uint8_t flags;
    };

    struct EnumDecl {
        std::string name;
        Visibility visibility;
        std::vector<Argument> items;
        uint8_t flags;
    };

    struct InterfaceDecl {
        std::string name;
        Visibility visibility;
        std::vector<Type> generics;
        std::vector<FunctionDecl> functions;
        uint8_t flags;
    };

    struct ClassDecl {
        std::string name;
        Visibility visibility;
        std::vector<Type> generics;
        std::vector<FunctionDecl> functions;
        std::vector<Variable> variables;
        uint8_t flags;
    };

    using Declaration = std::variant<
        ImportDecl,
        EnumDecl,
        FunctionDecl,
        InterfaceDecl,
        ClassDecl
    >;

    using Program = std::vector<Declaration>;

}
#endif //AST_HPP
