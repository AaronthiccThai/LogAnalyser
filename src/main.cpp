#include <iostream>
#include <fstream>
#include <string>
#include "parsers/ParserEngine.h"
#include "analysers/AnalyserEngine.h" 
#include "utils/printHelp.h"
int main(int argc, char* argv[]) {

    ParserEngine parserEngine;
    AnalyserEngine analyserEngine;

    if (argc < 2) {
        printHelp(argv[0]);
        return 1;
    }
    std::string firstArg = argv[1];
    // Handle standalone commands
    if (firstArg == "--help") {
        printHelp(argv[0]);
        return 0;
    }

    bool saveReport = false;
    bool analyseSelected = false;
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--severity") {
            analyserEngine.enableSeverityAnalyser();
            analyseSelected = true;
        } else if (arg == "--requests") {
            analyserEngine.enableRequestAnalyser();
            analyseSelected = true;
        } else if (arg == "--all") {
            analyserEngine.enableAll();
            analyseSelected = true;
        } else if (arg == "--save") {
            saveReport = true;
        } else {
            std::cerr << "Unknown option: " << arg
                      << "\nUse --help for usage information.\n";
            return 1;
        }
    }
    if (!analyseSelected) {
        analyserEngine.enableAll();
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }
    analyserEngine.setFilename(argv[1]);

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        auto entry = parserEngine.parse(line);
        if (!entry) continue;
        analyserEngine.process(*entry, lineNumber);
    }

    file.close();

    analyserEngine.printReport();
    if (saveReport) {
        analyserEngine.saveReport();
    }

    return 0;
}

