#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cstdint>

namespace mlang::lexer {

    enum class Token : uint8_t{
        // for logic
        Unknown,
        EndOfFile,

        // constants
        Identifier,
        Number,
        String,
        Char,

        // reserved words
        Abstract,
        Class,
        Interface,
        Function,
        If,
        Import,
        Else,
        For,
        Match,
        While,
        Loop,
        Next,
        Stop,
        Let,
        Const,
        Override,
        Constructor,
        Super,
        True,
        False,
        Null,
        Pub,
        Prot,
        Priv,
        As,
        Is,
        Return,

        //operators
        Plus,       // +
        Minus,      // -
        Div,        // /
        Mod,        // %
        Mul,        // *

        Less,       // <
        More,       // >
        Assign,     // =

        Not,        // !
        Inv,        // ~
        Xor,        // ^
        And,        // &
        Or,         // |

        Dot,        // .
        Comma,      // ,
        Colon,      // :
        Question,   // ?

        Grave,      // '
        Quote,      // "

        BracketI,   // (
        BracketO,   // )
        BracketCI,  // {
        BracketCO,  // }
        BracketSI,  // [
        BracketSO,  // ]

        // operators but longer
        Shl,        // <<
        Shr,        // >>

        Elvis,      // ?:

        PlusEq,     // +=
        MinusEq,    // -=
        DivEq,      // /=
        ModEq,      // %=
        MulEq,      // *=

        LessEq,     // <=
        MoreEq,     // >=
        Eq,         // ==

        NotEq,      // !=
        InvEq,      // ~=
        XorEq,      // ^=
        AndEq,      // &=
        OrEq,       // |=

        ShlEq,      // <<=
        ShrEq,      // >>=

    };

}

#endif //TOKEN_HPP
