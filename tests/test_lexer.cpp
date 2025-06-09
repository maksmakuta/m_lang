#include <iostream>
#include <functional>
#include <catch2/catch_test_macros.hpp>

#include "mlang/lexer/Lexer.hpp"
#include "mlang/lexer/Token.hpp"

using namespace mlang::lexer;

template<class T>
std::string to_string(const std::vector<T>& vec, const std::function<int(const T&)>& f) {
    std::string res;
    for (const auto& item : vec) {
        res += std::to_string(f(item));
        res += " ";
    }
    return res;
}

bool eq(const std::string& code, const std::vector<Token>& answer) {
    const auto res = lex(code);
    if (res.size() == answer.size()) {
        return std::ranges::equal(res, answer, [](const Lexem& l, const Token& t) {
            return l.token == t;
        });
    }
    std::cout << "Wrong size\n";
    std::cout << to_string<Lexem>(res,[](const Lexem& l){ return static_cast<int>(l.token); }) << " vs " << to_string<Token>(answer,[](const auto& i){return static_cast<int>(i); }) << std::endl;
    return false;
}

TEST_CASE("Reserved words") {
    REQUIRE(
        eq(
            "const for while abstract class constructor",
            {Token::Const,Token::For,Token::While,Token::Abstract,Token::Class,Token::Constructor}
        )
    );
    REQUIRE(
        eq(
            "return else if interface loop",
            {Token::Return,Token::Else,Token::If,Token::Interface,Token::Loop}
        )
    );
    REQUIRE(
        eq(
            "as is and or xor shl",
            {Token::As,Token::Is,Token::And,Token::Or,Token::Xor, Token::Shl}
        )
    );
}

TEST_CASE("Operators") {
    REQUIRE(
        eq(
            "+ - * / %()",
            {Token::Add,Token::Sub,Token::Mul,Token::Div,Token::Mod, Token::BracketI, Token::BracketO}
        )
    );
    REQUIRE(
        eq(
            ":   ? .    ,    ",
            {Token::Colon,Token::Question,Token::Dot,Token::Comma}
        )
    );
    REQUIRE(
        eq(
            "=<>!~",
            {Token::Assign,Token::Less,Token::More,Token::Not,Token::Inv}
        )
    );
}

TEST_CASE("Expressions") {
    REQUIRE(
         eq(
            "let a = 0.69f",
            {Token::Let,Token::Identifier,Token::Assign,Token::Number}
        )
    );
    REQUIRE(
        eq(
            "loop {}",
            {Token::Loop,Token::BracketCI,Token::BracketCO}
        )
    );
    REQUIRE(
        eq(
            "2.f * a + b",
            {Token::Number,Token::Mul,Token::Identifier,Token::Add,Token::Identifier}
        )
    );
}

TEST_CASE("Combined") {
    REQUIRE(
        eq(
            "a += 56 >> 3",
            {
                Token::Identifier,Token::AddEq,Token::Number, Token::Shr, Token::Number
            }
        )
    );

    REQUIRE(
        eq(
            "i8 u32 f64 str",
            {
                Token::Identifier, Token::Identifier, Token::Identifier,  Token::Identifier
            }
        )
    );

    REQUIRE(
        eq(
            "struct Vec2{ x : i32, y : i32}",
            {
                Token::Struct, Token::Identifier,
                Token::BracketCI,
                Token::Identifier, Token::Colon, Token::Identifier,
                Token::Comma,
                Token::Identifier, Token::Colon, Token::Identifier,
                Token::BracketCO
            }
        )
    );

    REQUIRE(
        eq(
            "class A{constructor(val : i32){ this.a = val } \n priv let a = 0 }",
            {
                Token::Class, Token::Identifier, Token::BracketCI, Token::Constructor,
                Token::BracketI, Token::Identifier, Token::Colon, Token::Identifier, Token::BracketO,
                Token::BracketCI, Token::This, Token::Dot, Token::Identifier, Token::Assign, Token::Identifier, Token::BracketCO,
                Token::Priv, Token::Let, Token::Identifier, Token::Assign, Token::Number, Token::BracketCO
            }
        )
    );

}

