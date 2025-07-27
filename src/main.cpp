#include <iostream>
#include <fstream>

#include "mlang/AstPrinter.hpp"
#include "mlang/Lexer.hpp"
#include "mlang/Parser.hpp"

std::string read(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file " << filename << std::endl;
    }
    std::string contents;
    std::string temp;
    while (std::getline(file, temp)) {
        contents.append(temp);
        contents.append("\n");
    }
    return contents;
}

int main() {
    const auto code = read("../example/test.mlang");
    std::cout << "Code:\n" << code << std::endl;

    std::cout << "Tokens:";
    const auto list = mlang::tokenize(code);
    std::cout << "(" <<list.size() << ")" << std::endl;
    for (const auto &token : list) {
        std::cout << mlang::toString(token.lexem) << " - " << token.value << " > " << token.position.first << ":" << token.position.second << std::endl;
    }

    std::cout << std::endl;

    const auto ast_root = mlang::parse(list);
    std::cout << "AST:" << std::endl;
    mlang::print(ast_root);

}