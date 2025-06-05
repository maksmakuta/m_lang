#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "ast/AST.hpp"

namespace mlang {

    struct Position {
        int line;
        int column;

        void newline();
    };

    std::string toString(const Position& p);
    std::string toString(const Type& p);
    std::string toQuoted(const std::string& str, char left, char right);

    std::string readFile(const std::string& file_path);


}

#endif //UTILS_HPP
