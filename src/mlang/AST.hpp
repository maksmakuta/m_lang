#ifndef AST_HPP
#define AST_HPP
#include <string>

namespace mlang {

    enum class Type {
        Import,
    };

    struct ASTNode {
        explicit ASTNode(Type type) : type(type) {}

        Type type;
    };

    struct ImportNode : ASTNode {
        explicit ImportNode(const std::string& import_path) : ASTNode(Type::Import),
            path(import_path) {}

        std::string path;
    };

}

#endif //AST_HPP
