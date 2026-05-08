#include <iostream>
#include <iomanip>
#include <fstream>
#include "ErrorSeverityAnalyser.h"
#include "models/ErrorLogEntry.h"

void ErrorSeverityAnalyser::process(const ILogEntry& entry, int lineNumber) {
    if (entry.getType().find("error") != std::string::npos) {

        const ErrorLogEntry* errorEntry = dynamic_cast<const ErrorLogEntry*>(&entry);
        if (!errorEntry) return; // safety check

        std::string severity = errorEntry->getSeverity();
        severityCounts[severity]++;
        severityLineNumbers[severity].push_back(lineNumber);        
        setTotalErrors(getTotalErrors() + 1);
    }
}
// Implement getLineNumber here to showcase where the errors are at
void ErrorSeverityAnalyser::generateReport(std::ostream& out) {

    out << "=============================\n";
    out << " Error Severity Report for "
        << getFilename() << "\n";
    out << "=============================\n\n";

    if (getTotalErrors() == 0) {
        out << "No error logs found.\n";
        return;
    }

    std::string mostCommonSeverity;
    int maxCount = 0;
    out << "Severity Breakdown:\n";
    for (const auto& pair : severityCounts) {

        double percent = (static_cast<double>(pair.second) / getTotalErrors()) * 100.0;
        out << "  "
            << std::left
            << std::setw(10)
            << pair.first
            << " : "
            << std::setw(5)
            << pair.second
            << " ("
            << std::fixed
            << std::setprecision(1)
            << percent
            << "%)\n";

        out << "    Lines: ";

        const auto& lines = severityLineNumbers[pair.first];

        for (size_t i = 0; i < lines.size(); i++) {
            out << lines[i];
            if (i != lines.size() - 1) {
                out << ", ";
            }
        }

        out << "\n";

        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostCommonSeverity = pair.first;
        }
    }

    out << "\n-----------------------------\n";
    out << "Total error logs: "
        << getTotalErrors() << "\n";

    out << "Most common severity: "
        << mostCommonSeverity << "\n";

    out << "-----------------------------\n";
}
void ErrorSeverityAnalyser::printReport() {
    generateReport(std::cout);
}

void ErrorSeverityAnalyser::saveReport() {
    std::ofstream outFile(getFilename() + "_error_severity_report.txt");

    if (!outFile.is_open()) {
        std::cerr << "Failed to save report.\n";
        return;
    }

    generateReport(outFile);

    outFile.close();
}