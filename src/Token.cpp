#include "mlang/Token.hpp"

#include <map>

namespace mlang {

    static auto strings(){
        std::map<Token, std::string> result;
#define INSERT_ELEMENT(p) result.emplace(p, #p);
        INSERT_ELEMENT(Token::EndOfFile);
        INSERT_ELEMENT(Token::Identifier);
        INSERT_ELEMENT(Token::Let);
        INSERT_ELEMENT(Token::Function);
        INSERT_ELEMENT(Token::Colon);
        INSERT_ELEMENT(Token::BracketStart);
        INSERT_ELEMENT(Token::BracketEnd);
        INSERT_ELEMENT(Token::BracketSquareStart);
        INSERT_ELEMENT(Token::BracketSquareEnd);
        INSERT_ELEMENT(Token::BracketCurlyStart);
        INSERT_ELEMENT(Token::BracketCurlyEnd);
        INSERT_ELEMENT(Token::String);
        INSERT_ELEMENT(Token::Number);
        INSERT_ELEMENT(Token::Character);
        INSERT_ELEMENT(Token::Unknown);
#undef INSERT_ELEMENT
        return result;
    }

    std::string toString(Token value) {
        return strings()[value];
    }

    std::ostream& operator<<(std::ostream& out, const Token value){
        return out << toString(value);
    }

}
