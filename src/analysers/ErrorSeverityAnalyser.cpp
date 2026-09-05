#include <iostream>
#include <iomanip>
#include <fstream>
#include "ErrorSeverityAnalyser.h"
#include "models/apache/ApacheErrorLogEntry.h"
#include "models/nginx/NginxErrorLogEntry.h"
#include "utils/toString.h"
/**
 * Process a log entry to analyze error severity
 * @param entry The log entry to process
 * @param lineNumber The line number of the log entry in the file, for reference in reports
 */
void ErrorSeverityAnalyser::process(const ILogEntry& entry, int lineNumber) {
    if (entry.getCategory() == LogCategory::Error) {
        logCategory = entry.getCategory();
        logServer = entry.getServer();
        const ErrorLogEntry* errorEntry = dynamic_cast<const ErrorLogEntry*>(&entry);
        if (!errorEntry) return; // safety check

        std::string severity = errorEntry->getSeverity();
        severityCounts[severity]++;
        severityLineNumbers[severity].push_back(lineNumber);        
        setTotalErrors(getTotalErrors() + 1);
        messageCounts[errorEntry->getMessage()]++;

        // Cast to apache error log entry to get module and client info if available
        const ApacheErrorLogEntry* apacheEntry =
            dynamic_cast<const ApacheErrorLogEntry*>(errorEntry);

        if (apacheEntry) {
            moduleErrors[apacheEntry->getModule()]++;

            if (!apacheEntry->getClientAddress().empty()) {
                clientErrors[apacheEntry->getClientAddress()]++;
            }
            if (apacheEntry->getModule() != "") {
                moduleErrors[apacheEntry->getModule()]++;
            }
        }        
    }
}

/**
 * Generate a report of the error severity analysis
 * @param out The output stream to write the report to
 */
void ErrorSeverityAnalyser::generateReport(std::ostream& out) {

    out << "=============================\n";
    out << "Error Severity Report for "
        << getFilename() << "\n";
    out << "=============================\n\n";

    if (getTotalErrors() == 0) {
        out << "No error logs found.\n";
        return;
    }
    
    out << "Server: " << toString(logServer) << "\n";
    out << "Category: " << toString(logCategory) << "\n";
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
    // Module breakdown of errors (if applicable)
    if (!moduleErrors.empty()) {
        out << "Module breakdown of errors:\n";
        for (const auto& pair : moduleErrors) {
            out << "  " << pair.first << " : " << pair.second << "\n";
        }
    }

    out << "\n-----------------------------\n";
    // Total Errors and most common severity
    out << "Total error logs: "
        << getTotalErrors() << "\n";

    out << "Most common severity: "
        << mostCommonSeverity << "\n";

    out << "\n-----------------------------\n";

    // Most common error messages
    out << "Most common error messages:\n";
    for (const auto& pair : messageCounts) {
        out << "  " << pair.first << " : " << pair.second << "\n";
    }
    out << "\n-----------------------------\n";

    // Most problematic client IPs
    out << "Most problematic client IPs:\n";
    for (const auto& pair : clientErrors) {
        out << "  " << pair.first << " : " << pair.second << "\n";
    }
    out << "\n-----------------------------\n";


}
/**
 * Print the error severity report to the console
 */
void ErrorSeverityAnalyser::printReport() {
    generateReport(std::cout);
}

/**
 * Save the error severity report to a file
 */
void ErrorSeverityAnalyser::saveReport() {
    std::ofstream outFile(getFilename() + "_error_severity_report.txt");

    if (!outFile.is_open()) {
        std::cerr << "Failed to save report.\n";
        return;
    }

    generateReport(outFile);

    outFile.close();
}