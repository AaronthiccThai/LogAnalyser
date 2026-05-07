#include <iostream>
#include <iomanip>
#include "RequestCountAnalyser.h"
#include <fstream>
void RequestCountAnalyser::process(const ILogEntry& entry, int lineNumber) {
    // Make this more generalised, maybe make an enum for the different types of files
    if (entry.getType() == "apache-access") {
        setRequestCount(getRequestCount() + 1);
        setTotalProcessed(getTotalProcessed() + 1);

    } else if (entry.getType() == "apache-error") {
        setErrorCount(getErrorCount() + 1);
        setTotalProcessed(getTotalProcessed() + 1);
    }
}

void RequestCountAnalyser::generateReport(std::ostream& out) {
    int requests = getRequestCount();
    int errors = getErrorCount();
    int total = getTotalProcessed();
    out << "=============================\n";
    out << "Request Count Report for " << getFilename() << "\n";
    out << "=============================\n\n";

    if (total == 0) {
        out << "No log entries processed.\n";
        return;
    }

    double errorRate = (static_cast<double>(errors) / total) * 100.0;
    double successRate = (static_cast<double>(requests) / total) * 100.0;

    out << "Total Requests: " << requests << "\n";
    out << "Total Errors:   " << errors << "\n\n";

    out << std::fixed << std::setprecision(1);
    out << "Success Rate:   " << successRate << "%\n";
    out << "Error Rate:     " << errorRate << "%\n";

    out << "\n-----------------------------\n";
    out << "Total Processed: " << total << "\n";
    out << "-----------------------------\n";
}

void RequestCountAnalyser::saveReport() {
    std::ofstream outFile(getFilename() + "_request_count_report.txt");
    if (!outFile.is_open()) {
        std::cerr << "Failed to save report.\n";
        return;
    }
    generateReport(outFile);
    outFile.close();
}

void RequestCountAnalyser::printReport() {
    generateReport(std::cout);
}