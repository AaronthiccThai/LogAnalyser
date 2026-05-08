#include <iostream>
#include <fstream>
#include <string>
#include "parsers/ParserEngine.h"
#include "analysers/AnalyserEngine.h" 

int main(int argc, char* argv[]) {
    ParserEngine parserEngine;
    AnalyserEngine analyserEngine;    
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
    int lineNumber = 0;
    // Read and print each line of the file
    while (std::getline(file, line)) {
        lineNumber++;
        auto entry = parserEngine.parse(line);

        if (!entry) continue;
        analyserEngine.process(*entry, lineNumber);
        analyserEngine.setFilename(argv[1]);
        analyserEngine.setLineNumber(lineNumber);
        DateTime t = entry->getTimestamp();
    }

    file.close();
    analyserEngine.printReport();   
    if (argc > 2 && std::string(argv[2]) == "--save") {
        analyserEngine.saveReport();
    }
    return 0;
}