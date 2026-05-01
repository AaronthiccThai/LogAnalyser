#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"

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
        parseLogs(line);
    }

    file.close();
    return 0;

}