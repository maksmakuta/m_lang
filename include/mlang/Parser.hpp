#ifndef PARSER_HPP
#define PARSER_HPP

#include "mlang/AST.hpp"
#include "mlang/Lexer.hpp"

namespace mlang {

    class Parser {
    public:
        explicit Parser(std::vector<Lexem>& lexems);

        std::shared_ptr<Program> parse();
    private:

        [[nodiscard]] Lexem& peek() const;
        [[nodiscard]] Lexem& previous() const;
        [[nodiscard]] bool check(Token type) const;
        [[nodiscard]] bool isAtEnd() const;
        Lexem& advance();
        bool match(Token type);
        bool matchAny(const std::initializer_list<Token> &types);

        void error(const std::string& message);

        std::vector<Lexem>& m_data;
        size_t current = 0;
        bool is_error = false;
    };

}

#endif //PARSER_HPP
