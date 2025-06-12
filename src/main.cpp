#include <fstream>
#include <sstream>
#include <iostream>

#include "mlang/codegen/ASTPrinter.hpp"
#include "mlang/lexer/Lexer.hpp"
#include "mlang/parser/Parser.hpp"

std::string readFile(const std::string& file_path) {
    std::stringstream ss;
    if (std::ifstream file(file_path); file.is_open()) {
        ss << file.rdbuf();
        file.close();
    }
    return ss.str();
}

void printAST(const std::string& path) {
    const std::string code = readFile(path);
    if (code.empty()) {
        std::cout << "Cannot read file: " << path << std::endl;
        return;
    }
    const auto lexems = mlang::lexer::lex(code);
    if (lexems.empty()) {
        std::cout << "Lexer error " << std::endl;
        return;
    }
    const auto program = mlang::parser::Parser(lexems).parse();
    if (program.empty()) {
        std::cout << "Parsing error " << std::endl;
        return;
    }

    mlang::codegen::ASTPrinter printer(program);
    std::cout << std::endl << std::endl << printer.toString() << std::endl;
}

int main(){
    printAST("../examples/test.mlang");
    return 0;
}

