#include "mlang/codegen/CxxGenerator.hpp"

#include <iostream>
#include <map>

#include "mlang/Utils.hpp"

namespace mlang {

    const std::map<std::string,std::string> headers = {
        {"std.vec" , "vector"},
        {"std.math" , "cmath"},
        {"std.arr" , "array"},
        {"std.io" , "iostream"},
        {"std.map" , "map"},
        {"std.set" , "set"},
    };

    void CxxGenerator::visit(const std::shared_ptr<Program>& program) {
        if (program) {
            for (const auto& item : program->declarations) {
                std::visit(*this,item);
            }
        }
    }

    void CxxGenerator::operator()(const ImportDeclaration& i) const {
        const bool isSystem = headers.contains(i.path);
        std::cout << "#include ";
        if (isSystem)
            std::cout << toQuoted(headers.at(i.path),'<','>');
        else
            std::cout << toQuoted(i.path,'"','"');
        std::cout << std::endl;
    }

    void CxxGenerator::operator()(const InterfaceDeclaration&){

    }

    void CxxGenerator::operator()(const FunctionDeclaration& f){
        std::cout << (f.returnType ? toString(*f.returnType) : "void") << ' ' << f.name << '(';

        std::cout << ") {}";

    }

    void CxxGenerator::operator()(const StructDeclaration&){

    }

    void CxxGenerator::operator()(const EnumDeclaration&){

    }

    void CxxGenerator::operator()(const ClassDeclaration&){

    }

}
