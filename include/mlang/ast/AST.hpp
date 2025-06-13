#ifndef AST_HPP
#define AST_HPP

#include <cstdint>
#include <string>
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
    };

    struct Argument {
        std::string name;
        Type type;
    };

    struct Declaration{};
    using Program = std::vector<Declaration>;

}
#endif //AST_HPP
