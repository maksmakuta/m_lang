#include <iostream>
#include <fstream>

#include "mlang/Lexer.hpp"

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
    const auto code = read("../example/simple_math.mlang");
    std::cout << "Code:\n" << code << std::endl;

    std::cout << "Tokens:";
    const auto list = mlang::tokenize(code);
    std::cout << "(" <<list.size() << ")" << std::endl;
    for (const auto &token : list) {
        std::cout << mlang::toString(token.lexem) << " - " << token.value << " > " << token.position.first << ":" << token.position.second << std::endl;
    }
}