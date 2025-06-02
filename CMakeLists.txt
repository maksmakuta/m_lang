cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(m_lang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mcc
        src/main.cpp
)
