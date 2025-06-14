#include "mlang/codegen/ASTPrinter.hpp"

#include <sstream>

namespace mlang::codegen {

    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    std::string padding(const int l) {
        return std::string(static_cast<size_t>(l * 2),' ') + " - ";
    }

    void ASTPrinter::toString(const ast::Import& i,const int layer) {
        buffer << padding(layer) << "import: " << i.path << "\n";
    }

    void ASTPrinter::toString(const ast::Function& f, const int layer) {
        buffer << padding(layer) << "function: " << f.name << "\n";
    }

    void ASTPrinter::toString(const ast::Enum& e, const int layer) {
        buffer << padding(layer) << "enum: " << e.name << "\n";
    }

    void ASTPrinter::toString(const ast::Struct& s, const int layer) {
        buffer << padding(layer) << "struct: " << s.name << "\n";
    }

    void ASTPrinter::toString(const ast::Interface& i, const int layer) {
        buffer << padding(layer) << "interface: " << i.name << "\n";
    }

    void ASTPrinter::toString(const ast::Class& c, const int layer) {
        buffer << padding(layer) << "class: " << c.name << "\n";
    }

    std::string ASTPrinter::toString(const ast::Program& program, const int layer) {
        for (const auto& item : program) {
            std::visit(overloaded(
                [&layer, this](const ast::Import&    i){ toString(i,layer + 1); },
                [&layer, this](const ast::Function&  i){ toString(i,layer + 1); },
                [&layer, this](const ast::Enum&      i){ toString(i,layer + 1); },
                [&layer, this](const ast::Struct&    i){ toString(i,layer + 1); },
                [&layer, this](const ast::Interface& i){ toString(i,layer + 1); },
                [&layer, this](const ast::Class&     i){ toString(i,layer + 1); }
            ),
            item);
        }

        return buffer.str();
    }

}