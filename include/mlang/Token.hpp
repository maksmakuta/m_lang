#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cstdint>
#include <string>

namespace mlang {

    enum class Token : uint8_t{
        EndOfFile,

        Identifier,
        Let,
        Function,

        Colon,
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
