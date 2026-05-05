#include "ErrorSeverityAnalyser.h"
#include <iostream>
void ErrorSeverityAnalyser::process(const ILogEntry& entry) {
    if (entry.getType() == "apache-error") {
        std::string type = entry.getType();

    }
}
void ErrorSeverityAnalyser::printReport() {
    std::cout << "Error Severity Distribution:" << std::endl;
    for (const auto& pair : severityCounts) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
}

