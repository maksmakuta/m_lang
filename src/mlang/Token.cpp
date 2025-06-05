#include "mlang/Token.hpp"

#include <map>

namespace mlang {

    static auto strings(){
        std::map<Token, std::string> result;
#define INSERT_ELEMENT(p) result.emplace(p, #p);
        INSERT_ELEMENT(Token::EndOfFile);
        INSERT_ELEMENT(Token::Type);
        INSERT_ELEMENT(Token::Identifier);
        INSERT_ELEMENT(Token::Interface);
        INSERT_ELEMENT(Token::Abstract);
        INSERT_ELEMENT(Token::Function);
        INSERT_ELEMENT(Token::Import);
        INSERT_ELEMENT(Token::Struct);
        INSERT_ELEMENT(Token::Return);
        INSERT_ELEMENT(Token::Class);
        INSERT_ELEMENT(Token::Match);
        INSERT_ELEMENT(Token::Const);
        INSERT_ELEMENT(Token::False);
        INSERT_ELEMENT(Token::Else);
        INSERT_ELEMENT(Token::Null);
        INSERT_ELEMENT(Token::True);
        INSERT_ELEMENT(Token::Let);
        INSERT_ELEMENT(Token::If);
        INSERT_ELEMENT(Token::Plus);
        INSERT_ELEMENT(Token::Minus);
        INSERT_ELEMENT(Token::Divide);
        INSERT_ELEMENT(Token::Multiply);
        INSERT_ELEMENT(Token::Mod);
        INSERT_ELEMENT(Token::Not);
        INSERT_ELEMENT(Token::Or);
        INSERT_ELEMENT(Token::And);
        INSERT_ELEMENT(Token::Xor);
        INSERT_ELEMENT(Token::Invert);
        INSERT_ELEMENT(Token::ShiftLeft);
        INSERT_ELEMENT(Token::ShiftRight);
        INSERT_ELEMENT(Token::Equal);
        INSERT_ELEMENT(Token::Less);
        INSERT_ELEMENT(Token::Greater);
        INSERT_ELEMENT(Token::PlusEqual);
        INSERT_ELEMENT(Token::MinusEqual);
        INSERT_ELEMENT(Token::DivideEqual);
        INSERT_ELEMENT(Token::MultiplyEqual);
        INSERT_ELEMENT(Token::ModEqual);
        INSERT_ELEMENT(Token::OrEqual);
        INSERT_ELEMENT(Token::AndEqual);
        INSERT_ELEMENT(Token::XorEqual);
        INSERT_ELEMENT(Token::InvertEqual);
        INSERT_ELEMENT(Token::ShiftLeftEqual);
        INSERT_ELEMENT(Token::ShiftRightEqual);
        INSERT_ELEMENT(Token::NotEqual);
        INSERT_ELEMENT(Token::LessEqual);
        INSERT_ELEMENT(Token::GreaterEqual);
        INSERT_ELEMENT(Token::Dot);
        INSERT_ELEMENT(Token::Set);
        INSERT_ELEMENT(Token::Colon);
        INSERT_ELEMENT(Token::Comma);
        INSERT_ELEMENT(Token::BracketStart);
        INSERT_ELEMENT(Token::BracketEnd);
        INSERT_ELEMENT(Token::BracketSquareStart);
        INSERT_ELEMENT(Token::BracketSquareEnd);
        INSERT_ELEMENT(Token::BracketCurlyStart);
        INSERT_ELEMENT(Token::BracketCurlyEnd);
        INSERT_ELEMENT(Token::String);
        INSERT_ELEMENT(Token::Number);
        INSERT_ELEMENT(Token::Character);
        INSERT_ELEMENT(Token::While);
        INSERT_ELEMENT(Token::For);
        INSERT_ELEMENT(Token::Loop);
        INSERT_ELEMENT(Token::Pub);
        INSERT_ELEMENT(Token::Priv);
        INSERT_ELEMENT(Token::Prot);
        INSERT_ELEMENT(Token::Next);
        INSERT_ELEMENT(Token::Stop);
        INSERT_ELEMENT(Token::Enum);
        INSERT_ELEMENT(Token::This);
        INSERT_ELEMENT(Token::Constructor);
        INSERT_ELEMENT(Token::Unknown);

#undef INSERT_ELEMENT
        return result;
    }

    std::string toString(const Token value) {
        return strings()[value];
    }

    std::ostream& operator<<(std::ostream& out, const Token value){
        return out << toString(value);
    }

}
