#pragma once
#include "ILogAnalyser.h"
#include <iostream>
#include <map>  
#include <string>
#include <vector>
class RequestCountAnalyser : public ILogAnalyser {
private:
    int requestCount = 0;
    int errorCount = 0;
    int totalProcessed = 0;
    std::map<std::string, int> requestMethodCounts; // For breakdown of request methods
    std::map<std::string, int> statusCodeCounts; // For breakdown of status
    std::map<std::string, int> ipAddressCounts; // For counting requests per IP address
    std::map<std::string, std::vector<int>> ipAddressLineNumbers; // For tracking line numbers of requests from each IP address, to determine potential sus IP
    const size_t MAX_LINES_TO_SHOW = 10;
 
public:
    virtual void process(const ILogEntry& entry, int lineNumber) override;
    virtual void generateReport(std::ostream& out) override;
    virtual void printReport() override;
    virtual void saveReport() override;
    int getRequestCount() const { return requestCount; }
    void setRequestCount(int count) { requestCount = count; }
    int getErrorCount() const { return errorCount; } 
    void setErrorCount(int count) { errorCount = count; }
    int getTotalProcessed() const { return totalProcessed; }
    void setTotalProcessed(int count) { totalProcessed = count; }


};