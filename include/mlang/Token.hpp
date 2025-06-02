#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cstdint>
#include <string>

namespace mlang {

    enum class Token : uint8_t{
        EndOfFile,

        Type,
        Identifier,
        Interface,
        Abstract,
        Function,
        Import,
        Return,
        Class,
        Match,
        False,
        Else,
        Null,
        True,
        Let,
        If,

        Plus,
        Minus,
        Divide,
        Multiply,
        Mod,
        Not,
        Or,
        And,
        Xor,
        BitwiseOr,
        BitwiseAnd,
        Invert,
        ShiftLeft,
        ShiftRight,
        Equal,
        Less,
        Greater,

        PlusEqual,
        MinusEqual,
        DivideEqual,
        MultiplyEqual,
        ModEqual,
        OrEqual,
        AndEqual,
        XorEqual,
        InvertEqual,
        ShiftLeftEqual,
        ShiftRightEqual,
        NotEqual,
        LessEqual,
        GreaterEqual,

        Dot,
        Colon,
        Comma,

        BracketStart,
        BracketEnd,
        BracketSquareStart,
        BracketSquareEnd,
        BracketCurlyStart,
        BracketCurlyEnd,

        String,
        Number,
        Character,

        Unknown = 255
    };

    std::string toString(Token);
    std::ostream& operator<<(std::ostream& out, Token value);

}


#endif //TOKEN_HPP
