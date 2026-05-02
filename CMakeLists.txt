cmake_minimum_required(VERSION 3.10)

project(ApacheLogAnalyser)

set(CMAKE_CXX_STANDARD 17)
add_executable(analyser
    src/main.cpp
    src/parsers/AccessLogParser.cpp
    src/parsers/ErrorLogParser.cpp
    src/parsers/ParserEngine.cpp
)

target_include_directories(analyser PRIVATE src)
