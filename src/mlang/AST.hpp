#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <utility>
#include <memory>

namespace mlang {

    struct ASTNode;
    using ASTNodePtr = std::shared_ptr<ASTNode>;

    enum class Type {
        Variable, //TODO
        Call, //TODO
        Binary, //TODO
        Unary, //TODO

        Import,
        Function, //TODO
        Struct, //TODO

        Program,
    };

    struct ASTNode {
        explicit ASTNode(const Type type) : type(type) {}
        virtual ~ASTNode() = default;

        Type type;
    };

    struct ImportNode : ASTNode {
        explicit ImportNode(std::string import_path) : ASTNode(Type::Import),
            path(std::move(import_path)) {}

        std::string path;
    };

    struct ProgramNode : ASTNode {
        ProgramNode() : ASTNode(Type::Program) {}

        void push(const ASTNodePtr &node) {
            items.push_back(node);
        }

        std::vector<ASTNodePtr> items;
    };

}

#endif //AST_HPP
