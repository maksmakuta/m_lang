#include "mlang/codegen/ASTPrinter.hpp"

namespace mlang::codegen {

    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    std::string padding(const int val) {
        std::string res;
        for (int i = 0; i < val; ++i) {
            res += ' ';
        }
        res += "- ";
        return res;
    }

    ASTPrinter::ASTPrinter(ast::Program &p) : m_program(p){}

    std::string ASTPrinter::toString(const int layer) {
        buffer << padding(layer) << "program: " << std::endl;
        const auto newLayer = layer + 1;
        for (auto& item: m_program) {
            std::visit(
                overloaded{
                    [this, &newLayer](const ast::ImportDecl& i     ){ this-> toString(newLayer,i); },
                    [this, &newLayer](const ast::FunctionDecl& f   ){ this-> toString(newLayer,f); },
                    [this, &newLayer](const ast::EnumDecl& e       ){ this-> toString(newLayer,e); },
                    [this, &newLayer](const ast::InterfaceDecl& r  ){ this-> toString(newLayer,r); },
                    [this, &newLayer](const ast::StructDecl& s     ){ this-> toString(newLayer,s); },
                    [this, &newLayer](const ast::ClassDecl& c      ){ this-> toString(newLayer,c); }
                },
                item
            );
        }

        return buffer.str();
    }

    void ASTPrinter::toString(int layer, const ast::ImportDecl& i){
        buffer << padding(layer) << "import: " << i.path << std::endl;
    }
    void ASTPrinter::toString(int layer, const ast::FunctionDecl&){

    }
    void ASTPrinter::toString(int layer, const ast::EnumDecl&){

    }
    void ASTPrinter::toString(int layer, const ast::InterfaceDecl&){

    }
    void ASTPrinter::toString(int layer, const ast::StructDecl&){

    }
    void ASTPrinter::toString(int layer, const ast::ClassDecl&){

    }
}
