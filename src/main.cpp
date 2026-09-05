#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parsers/ParserEngine.h"
#include "analysers/AnalyserEngine.h"
#include "utils/printHelp.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printHelp(argv[0]);
        return 0;
    }

    ParserEngine parserEngine;
    AnalyserEngine analyserEngine;
    std::vector<std::string> filenames;
    bool saveReport = false;
    bool analyseSelected = false;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        // Options
        if (arg == "--help") {
            printHelp(argv[0]);
            return 0;

        } else if (arg == "--severity") {
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
        // File
        } else if (arg.rfind("--", 0) != 0) {
            filenames.push_back(arg);
        // Unknown option
        } else {
            std::cerr << "Unknown option: " << arg
                      << "\nUse --help for usage information.\n";
            return 1;
        }
    }

    // At least one file is required
    if (filenames.empty()) {
        std::cerr << "Error: No log files provided.\n";
        printHelp(argv[0]);
        return 1;
    }

    // If no analyser was selected, enable all
    if (!analyseSelected) {
        analyserEngine.enableAll();
    }

    // Process every file
    for (const std::string& filename : filenames) {

        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error opening file: "
                      << filename << "\n";
            continue;
        }
        analyserEngine.setFilename(filename);
        std::string line;
        int lineNumber = 0;
        while (std::getline(file, line)) {
            lineNumber++;
            auto entry = parserEngine.parse(line);
            if (!entry) {
                continue;
            }
            analyserEngine.process(*entry, lineNumber);
        }
        file.close();
    }
    analyserEngine.printReport();
    if (saveReport) {
        analyserEngine.saveReport();
    }
    return 0;
}

