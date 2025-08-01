cmake_minimum_required(VERSION 4.0)

project(mlang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mcc
        src/mlang/Token.hpp
        src/mlang/Lexem.hpp
        src/mlang/Lexer.hpp

        src/mlang/Lexer.cpp
        src/mlang/Lexem.cpp
        src/main.cpp
)