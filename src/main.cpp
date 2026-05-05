#include <iostream>
#include <fstream>
#include <string>
#include "models/ParserEngine.h"


ParserEngine parserEngine;
int main(int argc, char* argv[]) {
    // Error handling for command line arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    // Error handling for file opening
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    // Read and print each line of the file
    while (std::getline(file, line)) {
        auto entry = parserEngine.parse(line);

        if (!entry) continue;

        DateTime t = entry->getTimestamp();

        std::cout << t.year << " "
                << t.day << " "
                << t.hour << std::endl;
    }

    file.close();
    return 0;
}