cmake_minimum_required(VERSION 3.10)

project(ApacheLogAnalyser)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(analyser ${SOURCES})

target_include_directories(analyser PRIVATE src)