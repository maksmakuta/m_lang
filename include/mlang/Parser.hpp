#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>

#include "ast/AST.hpp"
#include "mlang/Lexer.hpp"

namespace mlang {

    class Parser {
    public:
        explicit Parser(std::vector<Lexem>& lexems);

        std::shared_ptr<Program> parse();
    private:
        std::vector<Lexem>& m_data;
        size_t current = 0;
    };

}

#endif //PARSER_HPP
