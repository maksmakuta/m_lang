cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(m_lang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mcc
        include/mlang/Lexer.hpp
        include/mlang/Token.hpp
        include/mlang/Utils.hpp

        src/Lexer.cpp
        src/Token.cpp
        src/Utils.cpp
        src/main.cpp
)

target_include_directories(mcc PUBLIC include)

