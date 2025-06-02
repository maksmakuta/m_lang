#include <format>
#include <iostream>

#include "mlang/Lexer.hpp"
#include "mlang/Utils.hpp"

#define FILE_PATH "../examples/extended.mlang"

int main() {
    auto buff = mlang::readFile(FILE_PATH);
    std::cout << buff << std::endl << std::endl;
    std::cout << std::format("{:30} {:12} {} {}", "token", "text", "line", "column") << std::endl;
    for (const auto& [token, text, pos] : mlang::Lexer(buff).toTokens()) {
        std::cout << std::format("{:30} {:15} {} {}", mlang::toString(token), text, pos.line, pos.column) << std::endl;
    }
    return 0;
}