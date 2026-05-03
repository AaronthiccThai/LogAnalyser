
#include "RequestCountAnalyser.h"

void RequestCountAnalyser::process(const ILogEntry& entry) {
    if (entry.getType() == "apache-access") {
        setRequestCount(getRequestCount() + 1);
    } else if (entry.getType() == "apache-error") {
        setErrorCount(getErrorCount() + 1)  ;
    }
}
void RequestCountAnalyser::printReport() {
    std::cout << "Total Requests: " << getRequestCount() << std::endl;
    std::cout << "Total Errors: " << getErrorCount()       << std::endl;
}