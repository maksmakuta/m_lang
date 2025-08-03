cmake_minimum_required(VERSION 4.0)

project(mlang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mcc
        src/main.cpp
)

target_include_directories(mcc PUBLIC src)