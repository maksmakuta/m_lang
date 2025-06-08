#include <catch2/catch_test_macros.hpp>

#include "mlang/lexer/Lexer.hpp"
#include "mlang/lexer/Token.hpp"

using namespace mlang::lexer;

void test(const std::string& code, const std::vector<Token>& answer) {

}

TEST_CASE("Reserved words") {
    test(
        "for while abstract class constructor",
        {Token::For,Token::While,Token::Abstract,Token::Class,Token::Constructor}
    );
    test(
        "return else if interface loop",
        {Token::Return,Token::Else,Token::If,Token::Interface,Token::Loop}
    );
    test(
        "as is and or xor shl",
        {Token::As,Token::Is,Token::And,Token::Or,Token::Xor, Token::Shl}
    );
}

TEST_CASE("Operators") {
    test(
        "+ - * / %",
        {Token::Plus,Token::Minus,Token::Mul,Token::Div,Token::Mod}
    );
    test(
        ":?  . ,  ",
        {Token::Colon,Token::Question,Token::Dot,Token::Comma}
    );
    test(
        "<>=!~",
        {Token::Less,Token::More,Token::Assign,Token::Not,Token::Inv}
    );
}

TEST_CASE("Expressions") {
    test(
        "let a = 0.69f",
        {Token::Number}
    );
    test(
        "loop {}",
        {Token::Loop,Token::BracketCI,Token::BracketCO}
    );
    test(
        "2.f * a + b",
        {Token::Number,Token::Mul,Token::Identifier,Token::Plus,Token::Identifier}
    );
}

