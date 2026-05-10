#include <iostream>
#include <iomanip>
#include "RequestCountAnalyser.h"
#include <fstream>
#include "models/apache/ApacheAccessLogEntry.h"
#include "models/apache/ApacheErrorLogEntry.h"
void RequestCountAnalyser::process(const ILogEntry& entry, int lineNumber) {
    if (entry.getType() == "access") {
        setRequestCount(getRequestCount() + 1);
        setTotalProcessed(getTotalProcessed() + 1);
        const ApacheAccessLogEntry& accessEntry = static_cast<const ApacheAccessLogEntry&>(entry);
        // Update request method count
        requestMethodCounts[accessEntry.getRequestMethod()]++;
        // Update status code count
        statusCodeCounts[std::to_string(accessEntry.getStatusCode())]++;
        // Update IP address count
        ipAddressCounts[accessEntry.getClientIP()]++;
        // Update line numbers for the IP address
        ipAddressLineNumbers[accessEntry.getClientIP()].push_back(lineNumber);

    } else if (entry.getType() == "error") {
        const ApacheErrorLogEntry& errorEntry = static_cast<const ApacheErrorLogEntry&>(entry);
        setErrorCount(getErrorCount() + 1);
        setTotalProcessed(getTotalProcessed() + 1); 
        // TODO - add some errors here not sure since this analyser is focused on requests, and often error and access dont mix

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