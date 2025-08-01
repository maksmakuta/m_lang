#include <iostream>
#include <fstream>

#include "mlang/Lexer.hpp"

void compile(const std::string& source) {
    auto file = std::ifstream(source);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << source << std::endl;
        return;
    }

    mlang::Lexer lexer;

    std::string buffer;
    while (std::getline(file,buffer)) {
        //std::cout << "input: " << buffer << std::endl;

        const auto tokens = lexer.tokenize(buffer);
        for (const auto& token : tokens) {
            std::cout << mlang::to_string(token) << std::endl;
        }
        lexer.line++;
    }
    file.close();
}

int main() {
    compile("../examples/test.mlang");
    return 0;
}