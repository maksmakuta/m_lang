#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cstdint>
#include <string>

namespace mlang {

    enum class Token : uint8_t{
        EndOfFile,

        Type,
        Constructor,
        Identifier,
        Interface,
        Abstract,
        Function,
        Struct,
        Import,
        Return,
        Class,
        Match,
        While,
        False,
        Const,
        Next,
        Stop,
        Enum,
        Else,
        Null,
        This,
        Loop,
        For,
        True,
        Let,
        If,

        Set,
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

        Pub,
        Priv,
        Prot,

        String,
        Number,
        Character,

        Unknown = 255
    };

    std::string toString(Token);
    std::ostream& operator<<(std::ostream& out, Token value);

}


#endif //TOKEN_HPP
