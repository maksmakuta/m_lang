#include "mlang/codegen/CxxGenerator.hpp"

#include <iostream>
#include <map>
#include <sstream>

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

    const std::map<std::string,std::string> types = {
        {"vec" , "std::vector"},
        {"arr" , "std::array"},
        {"map" , "std::map"},
        {"set" , "std::set"},

        {"i8" , "signed char"},
        {"i16" , "signed short"},
        {"i32" , "signed int"},
        {"i64" , "signed long"},

        {"u8" , "unsigned char"},
        {"u16" , "unsigned short"},
        {"u32" , "unsigned int"},
        {"u64" , "unsigned long"},

        {"f32" , "float"},
        {"f64" , "double"},
    };



    void CxxGenerator::visit( std::stringstream& ss,const std::shared_ptr<Program>& program) const {
        if (program) {
            for (const auto& item : program->declarations) {
                std::visit([this, &ss](const auto& node) {
                    visit(ss,node);
                },item);
            }
        }
    }

    void CxxGenerator::visit( std::stringstream& ss,const ImportDeclaration& i) const {
        const bool isSystem = headers.contains(i.path);
        ss << "#include ";
        if (isSystem)
            ss << toQuoted(headers.at(i.path),'<','>');
        else
            ss << toQuoted(i.path,'"','"');
        ss << std::endl;
    }

    void CxxGenerator::visit( std::stringstream& ss, const InterfaceDeclaration&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const FunctionDeclaration& f) const{
        ss << (f.returnType ? toString(*f.returnType) : "void") << ' ' << f.name << '(';

        ss << ") {}";

    }

    void CxxGenerator::visit( std::stringstream& ss,const StructDeclaration& s) const{
        ss << "struct " << s.name << "{" << std::endl;
        for (const auto& i : s.fields) {
            ss << "\t";
            visit(ss,i);
            ss << ";\n";
        }
        ss << "}";
    }

    void CxxGenerator::visit( std::stringstream& ss,const EnumDeclaration&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ClassDeclaration&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ExprLiteral&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ExprVariable&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ExprUnary&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ExprBinary&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ExprCall&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ExprGet&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ExprSet&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ExprIndex&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const ExprInterpolation&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const StmtExpr&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const StmtBlock&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const StmtVar&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const StmtIf&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const StmtWhile&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const StmtMatch&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const StmtStop&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const StmtNext&) const{

    }

    void CxxGenerator::visit( std::stringstream& ss,const Type& t) const{
        ss << (types.contains(t.name) ? types.at(t.name) : t.name);
        if (!t.targs.empty()) {
            ss << '<';
            for (const auto& i : t.targs) {
                visit(ss,i);
            }
            ss << '>';
        }
    }

    void CxxGenerator::visit( std::stringstream& ss,const Variable& v) const{
        visit(ss,v.type);
        ss << " " << v.name;
        if (v.value) {
            ss << " = 0";
        }
    }

}
