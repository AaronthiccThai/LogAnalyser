cmake_minimum_required(VERSION 3.10)

project(ErrorLogAnalysisAPI)

set(CMAKE_CXX_STANDARD 17)

add_executable(analyser
    src/main.cpp
    src/parser.cpp
    src/logger.cpp
    src/analyser.cpp
)