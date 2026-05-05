#include <iostream>
#include <iomanip>
#include "RequestCountAnalyser.h"

void RequestCountAnalyser::process(const ILogEntry& entry) {

    if (entry.getType() == "apache-access") {
        setRequestCount(getRequestCount() + 1);
        setTotalProcessed(getTotalProcessed() + 1);

    } else if (entry.getType() == "apache-error") {
        setErrorCount(getErrorCount() + 1);
        setTotalProcessed(getTotalProcessed() + 1);
    }
}

void RequestCountAnalyser::printReport() {
    std::cout << "=============================\n";
    std::cout << " Request Count Report\n";
    std::cout << "=============================\n\n";

    int requests = getRequestCount();
    int errors = getErrorCount();

    int total = requests + errors;

    if (total == 0) {
        std::cout << "No log entries processed.\n";
        return;
    }

    double errorRate = (static_cast<double>(errors) / total) * 100.0;
    double successRate = (static_cast<double>(requests) / total) * 100.0;

    std::cout << "Total Requests: " << requests << "\n";
    std::cout << "Total Errors:    " << errors << "\n\n";

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Success Rate:    " << successRate << "%\n";
    std::cout << "Error Rate:      " << errorRate << "%\n";

    std::cout << "\n-----------------------------\n";
    std::cout << "Total Processed: " << total << "\n";
    std::cout << "-----------------------------\n";
}