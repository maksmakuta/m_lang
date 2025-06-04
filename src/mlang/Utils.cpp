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

}
