#include <iostream>
void printHelp(const char* programName) {
    std::cout << "Usage: " << programName << " <filename> [options]\n";
    std::cout << "Options:\n";
    std::cout << "  --severity   Generate error severity report\n";
    std::cout << "  --requests   Generate request analysis report\n";
    std::cout << "  --all        Generate all reports\n";
    std::cout << "  --save       Save the generated report(s) to a file\n";
    std::cout << "  --help       Show this help message\n";
};

