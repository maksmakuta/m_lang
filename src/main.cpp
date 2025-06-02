#include <iostream>

#include "mlang/Lexer.hpp"
#include "mlang/Utils.hpp"

#define FILE_PATH "../examples/hello.mc"

int main() {
    auto buff = mlang::readFile(FILE_PATH);
    std::cout << buff << std::endl << std::endl;
    for (const auto& [token, text, pos] : mlang::Lexer(buff).toTokens()) {
        std::cout << token << " " << text << " " << pos.line << ", " << pos.column << std::endl;
    }
    return 0;
}
