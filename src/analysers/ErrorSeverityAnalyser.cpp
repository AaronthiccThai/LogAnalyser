#include <iostream>
#include <iomanip>
#include "ErrorSeverityAnalyser.h"
#include "models/ErrorLogEntry.h"

void ErrorSeverityAnalyser::process(const ILogEntry& entry) {
    if (entry.getType().find("error") != std::string::npos) {

        const ErrorLogEntry* errorEntry = dynamic_cast<const ErrorLogEntry*>(&entry);
        if (!errorEntry) return; // safety check

        std::string severity = errorEntry->getSeverity();
        severityCounts[severity]++;

        setTotalErrors(getTotalErrors() + 1);
    }
}

void ErrorSeverityAnalyser::printReport() {
    std::cout << "=============================\n";
    std::cout << " Error Severity Report\n";
    std::cout << "=============================\n\n";

    if (getTotalErrors() == 0) {
        std::cout << "No error logs found.\n";
        return;
    }

    std::string mostCommonSeverity;
    int maxCount = 0;

    std::cout << "Severity Breakdown:\n";

    for (const auto& pair : severityCounts) {
        double percent = (static_cast<double>(pair.second) / getTotalErrors()) * 100.0;

        std::cout << "  " << std::left << std::setw(10) << pair.first
                  << " : " << std::setw(5) << pair.second
                  << " (" << std::fixed << std::setprecision(1)
                  << percent << "%)\n";

        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostCommonSeverity = pair.first;
        }
    }

    std::cout << "\n-----------------------------\n";
    std::cout << "Total error logs: " << getTotalErrors() << "\n";
    std::cout << "Most common severity: " << mostCommonSeverity << "\n";
    std::cout << "-----------------------------\n";
}