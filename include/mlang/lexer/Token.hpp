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
        Struct,
        Let,
        Const,
        Override,
        Constructor,
        Super,
        True,
        False,
        Null,
        Pub,
        This,
        In,
        Prot,
        Priv,
        As,
        Is,
        Return,

        //operators
        Add,        // +
        Sub,        // -
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

        AddEq,      // +=
        SubEq,      // -=
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
