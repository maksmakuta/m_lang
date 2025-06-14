#ifndef AST_HPP
#define AST_HPP

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace mlang::ast {

    enum class Visibility {
        Private,    // pub
        Public,     // priv - by default
        Protected   // prot
    };

    // Base<Generic1,Generic2, ...> : Inherit1,Inherit2,...
    struct Type {
        std::string base;
        std::vector<Type> generics;
        std::vector<Type> inherits;
    };

    // name : type [= value]
    struct Argument {
        std::string name;
        Type type;
        std::optional<std::string> value;
    };

    // let name : type = value
    struct Variable {
        Visibility visibility;
        std::string name;
        Type type;
        std::optional<std::string> value;
    };

    // import "path"
    struct Import {
        std::string path;
    };

    // fn<T> name(arg : T) : T{}
    struct Function {
        Visibility visibility;
        std::string name;
        std::vector<Type> generics;
        std::vector<Argument> args;
        std::optional<Type> returns;
    };

    // item = 45,
    struct EnumItem{
        std::string name;
        std::optional<std::string> value;
    };

    // enum name{ item = 2, lol = "kek" }
    struct Enum {
        Visibility visibility;
        std::string name;
        std::vector<EnumItem> items;
    };

    // struct<T,U> name{ field : T, field2 : U, ... }
    struct Struct {
        Visibility visibility;
        std::string name;
        std::vector<Type> generics;
        std::vector<Argument> fields;
    };

    // interface<T,U> name{ fn method() : T fn method2() : U, ... }
    struct Interface {
        Visibility visibility;
        std::string name;
        std::vector<Type> generics;
        std::vector<Function> methods;
    };

    // class<T,U> name{ constructor(){}, ... fn method() : T fn method2() : U, ... prot let field : T  pub let field2 : U = 0, ... }
    struct Class {
        Visibility visibility;
        std::string name;
        std::vector<Type> generics;
        std::vector<Function> methods;
        std::vector<Variable> variables;
    };

    using Declaration = std::variant<
        Import,
        Function,
        Enum,
        Struct,
        Interface,
        Class
    >;

    using Program = std::vector<Declaration>;

}

#endif //AST_HPP
