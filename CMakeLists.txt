cmake_minimum_required(VERSION 3.20)
project(mlang LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include path
include_directories(include)

# Source files
file(GLOB_RECURSE MLANG_SRC
        include/mlang/*.cpp
)

add_library(mlang STATIC ${MLANG_SRC}
        src/main.cpp
        tests/test_lexer.cpp
        tests/test_parser.cpp
        tests/test_type.cpp
)
target_include_directories(mlang PUBLIC include)

# Main executable
add_executable(mlangc src/main.cpp)
target_link_libraries(mlangc PRIVATE mlang)

# Enable testing
include(CTest)
enable_testing()

# Catch2
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.4
)
FetchContent_MakeAvailable(Catch2)

# Test executable
file(GLOB_RECURSE TEST_SRC tests/*.cpp)
add_executable(tests ${TEST_SRC})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain mlang)
add_test(NAME mlang_tests COMMAND tests)
