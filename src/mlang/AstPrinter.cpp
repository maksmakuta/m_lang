#include "AstPrinter.hpp"

#include <iostream>

namespace mlang {

    std::string padding(const int level) {
        return std::string(level, ' ');
    }

    void printProgram(const std::shared_ptr<ProgramNode>& node, const int level) {
        std::cout << padding(level) << "program : " << std::endl;
        for( const auto& item : node->items) {
            print(item, level + 1);
        }
    }

    void printImport(const std::shared_ptr<ImportNode>& node, const int level) {
        std::cout << padding(level) << "import : " << node->path << std::endl;
    }

    void print(const ASTNodePtr &node, int level) {
        switch (node->type) {
            case Type::Import:
                printImport(std::dynamic_pointer_cast<ImportNode>(node),level + 1);
                break;
            case Type::Program:
                printProgram(std::dynamic_pointer_cast<ProgramNode>(node),level + 1);
                break;
            case Type::Variable:
                break;
            case Type::Call:
                break;
            case Type::Binary:
                break;
            case Type::Unary:
                break;
            case Type::Function:
                break;
            case Type::Struct:
                break;
        }
    }

}
