#include "Parser.hpp"

#include <iostream>
#include <bits/ostream.tcc>

namespace mlang {

    void error(const std::string& str) {
        std::cerr << str << std::endl;
        std::exit(1);
    }

    ASTNodePtr parse(const std::vector<Token> &tokens) {
        const auto program = std::make_shared<ProgramNode>();
        auto i = 0;

        const auto nextIs = [&i, &tokens](const Lexem &l) -> bool {
            return tokens[i+1].lexem == l;
        };

        while (i < tokens.size()) {
            const auto token = tokens[i];
            switch(token.lexem) {
                case IMPORT: {
                    if (nextIs(STRING)) {
                        program->push(std::make_shared<ImportNode>(tokens[i+1].value));
                        i++;
                    }else {
                        error("Import should have path");
                    }
                }
                    break;
            }
            i++;
        }

        return program;
    }

}

