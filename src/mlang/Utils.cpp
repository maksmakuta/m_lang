#include "mlang/Utils.hpp"

#include <fstream>
#include <sstream>

namespace mlang {

    std::string readFile(const std::string &file_path) {
        std::ifstream file(file_path);
        std::stringstream buffer;
        if (file.is_open()) {
            buffer << file.rdbuf();
        }
        return buffer.str();
    }

    void Position::newline() {
        line++;
        column = 0;
    }

    std::string toString(const Position& p) {
        std::stringstream ss;
        ss << p.line << ":" << p.column;
        return ss.str();
    }

    std::string asStringList(const std::vector<Type>& p) {
        std::stringstream ss;
        for (const auto& i : p) {
            ss << toString(i) << ',';
        }
        auto res = ss.str();
        res.pop_back();
        return res;
    }

    std::string toString(const Type& p) {
        return p.name + toQuoted(asStringList(p.targs),'<','>');
    }

    std::string toQuoted(const std::string& str, const char left, const char right) {
        return (std::stringstream() << left << str << right).str();
    }

}
