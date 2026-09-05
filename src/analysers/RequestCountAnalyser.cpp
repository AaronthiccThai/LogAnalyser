#include <iostream>
#include <iomanip>
#include "RequestCountAnalyser.h"
#include <fstream>
#include "models/apache/ApacheAccessLogEntry.h"
#include "models/nginx/NginxAccessLogEntry.h"
#include "utils/toString.h"

/**
 * Process a log entry to analyze request counts
 * @param entry The log entry to process
 * @param lineNumber The line number of the log entry in the file, for reference in reports
 */
void RequestCountAnalyser::process(const ILogEntry& entry, int lineNumber) {
    if (entry.getCategory() != LogCategory::Access) {
        return;
    }
    logCategory = entry.getCategory();
    logServer = entry.getServer();

    setRequestCount(getRequestCount() + 1);
    setTotalProcessed(getTotalProcessed() + 1);

    const AccessLogEntry& accessEntry = static_cast<const AccessLogEntry&>(entry);
    requestMethodCounts[accessEntry.getRequestMethod()]++;
    statusCodeCounts[std::to_string(accessEntry.getStatusCode())]++;
    ipAddressCounts[accessEntry.getClientIP()]++;
    ipAddressLineNumbers[accessEntry.getClientIP()].push_back(lineNumber);
}
/**
 * Generate a report of the request count analysis
 * @param out The output stream to write the report to
 */
void RequestCountAnalyser::generateReport(std::ostream& out) {
    int requests = getRequestCount();
    int errors = getErrorCount();
    int total = getTotalProcessed();

    out << "=============================\n";
    out << "Request Count Report\n";
    out << "=============================\n\n";
    
    // out << "Server: " << toString(logServer) << "\n";
    out << "Category: " << toString(logCategory) << "\n";
    out << "File: " << getFilename() << "\n\n";

    if (total == 0) {
        out << "No log entries processed.\n";
        return;
    }

    // Total counts of requests and errors
    out << "Total Requests: " << requests << "\n";
    // Amount of lines processed
    out << "\n-----------------------------\n";
    out << "Total Processed: " << total << "\n";
    out << "-----------------------------\n";

    // Request method breakdown
    out << "\nRequest Method Breakdown:\n";
    if (requestMethodCounts.empty()) {
        out << "  No access log entries found.\n";
    } else {
        for (const auto& pair : requestMethodCounts) {
            double percent = (static_cast<double>(pair.second) / requests) * 100.0;
            out << "  "
                << pair.first
                << " : "
                << pair.second
                << " ("
                << std::fixed
                << std::setprecision(1)
                << percent
                << "%)\n";
        } 
    }   
    // Status code breakdown
    out << "\nStatus Codes:\n";
    if (statusCodeCounts.empty()) {
        out << "  No access log entries found.\n";
    } else {
        for (const auto& pair : statusCodeCounts) {
            double percent = (static_cast<double>(pair.second) / requests) * 100.0;

            out << "  "
                << pair.first
                << " : "
                << pair.second
                << " ("
                << percent
                << "%)\n";
        }
    }
    // Line numbers for each IP address, determine if suspicious IP addresses
    out << "\nPotentially Suspicious IPs:\n";
    if (ipAddressCounts.empty()) {
        out << "  No access log entries found.\n";
    } else {
        for (const auto& pair : ipAddressCounts) {
            if (pair.second > 100) {
                out << "  "
                    << pair.first
                    << " : "
                    << pair.second
                    << " requests\n";

                out << "    Lines: ";
                const auto& lines = ipAddressLineNumbers[pair.first];
                for (size_t i = 0;i < lines.size() && i < MAX_LINES_TO_SHOW; i++) {
                    out << lines[i];
                    if (i != MAX_LINES_TO_SHOW - 1 && i != lines.size() - 1) {
                        out << ", ";
                    }
                }

                if (lines.size() > MAX_LINES_TO_SHOW) {
                    out << " ... (+"
                        << (lines.size() - MAX_LINES_TO_SHOW)
                        << " more)";
                }
                out << "\n";
            }
        }    
    }
}

/**
 * Save the request count report to a file
 */
void RequestCountAnalyser::saveReport() {
    std::ofstream outFile(getFilename() + "_request_count_report.txt");
    if (!outFile.is_open()) {
        std::cerr << "Failed to save report.\n";
        return;
    }
    generateReport(outFile);
    outFile.close();
}

/**
 * Print the request count report to the console
 */
void RequestCountAnalyser::printReport() {
    generateReport(std::cout);
}