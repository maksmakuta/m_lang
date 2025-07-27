cmake_minimum_required(VERSION 4.0)

project(mlang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mcc
        src/mlang/AST.hpp
        src/mlang/Lexem.hpp
        src/mlang/Lexer.hpp
        src/mlang/Parser.hpp

        src/mlang/Lexem.cpp
        src/mlang/Lexer.cpp
        src/mlang/Parser.cpp

        src/main.cpp)