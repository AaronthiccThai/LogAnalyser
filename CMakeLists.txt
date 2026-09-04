cmake_minimum_required(VERSION 3.16)

project(LogAnalyser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------
# Application sources
# --------------------

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Don't include main.cpp in the library
list(REMOVE_ITEM SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_library(LogAnalyserLib ${SOURCES})

target_include_directories(LogAnalyserLib
    PUBLIC
    src
)

# --------------------
# Main executable
# --------------------

add_executable(analyser
    src/main.cpp
)

target_link_libraries(analyser
    PRIVATE
    LogAnalyserLib
)

# --------------------
# Catch2
# --------------------

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.15.3
)

FetchContent_MakeAvailable(Catch2)

# --------------------
# Tests
# --------------------

add_executable(tests
    tests/Apache.test.cpp
    tests/Nginx.test.cpp
)

target_link_libraries(tests
    PRIVATE
    Catch2::Catch2WithMain
    LogAnalyserLib
)

target_include_directories(tests
    PRIVATE
    src
)

enable_testing()

add_test(
    NAME ApacheAccessLogParserTest
    COMMAND tests
)
