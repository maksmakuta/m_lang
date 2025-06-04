#include <format>
#include <iostream>
#include <memory>

#include "mlang/ast/AST.hpp"
#include "mlang/Lexer.hpp"
#include "mlang/Parser.hpp"
#include "mlang/Utils.hpp"

#define FILE_PATH "../examples/test.mlang"

std::shared_ptr<mlang::Program> toAST(const std::string& file) {
    auto buff = mlang::readFile(file);
    if (buff.empty()) {
        std::cerr << "Cannot read file : " << file << std::endl;
    }
    mlang::Lexer lexer(buff);
    auto lexems = lexer.toTokens();
    if (lexems.empty()) {
        std::cerr << "Cannot read lexems: internal error"<< std::endl;
    }
    mlang::Parser parser(lexems);
    return  parser.parse();
}

int main() {
    const auto program = toAST(FILE_PATH);
    if (!program) {
        std::cerr << "Cannot run program : internal error" << std::endl;
    }
    std::cout << "Success!" << std::endl;
    return 0;
}