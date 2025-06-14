cmake_minimum_required(VERSION 3.20)
project(mlang LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include path
include_directories(include)

# Source files
file(GLOB_RECURSE MLANG_SRC
        src/mlang/*.cpp
)

add_library(mlang STATIC ${MLANG_SRC})
target_include_directories(mlang PUBLIC include)

# Main executable
add_executable(mlangc src/main.cpp)
target_link_libraries(mlangc PRIVATE mlang)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
include(Catch)

add_executable(tests tests/test_lexer.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain mlang)
catch_discover_tests(tests)