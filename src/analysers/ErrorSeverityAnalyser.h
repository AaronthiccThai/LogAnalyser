#pragma once
#include "ILogAnalyser.h"
#include <map>
#include <string>
#include <vector>
class ErrorSeverityAnalyser : public ILogAnalyser {
private:
    int totalErrors = 0;
    std::map<std::string, int> severityCounts;
    std::map<std::string, std::vector<int>> severityLineNumbers; // eg. error: [3,3,5]
    std::map<std::string, int> messageCounts;  // Most common error messages
    std::map<std::string, int> clientErrors;  // Most problematic client ip
    std::map<std::string, int> moduleErrors; // If applicable, module breakdown of errors
    LogCategory logCategory;
    LogServer logServer;

public:
    virtual void process(const ILogEntry& entry, int lineNumber) override;
    virtual void generateReport(std::ostream& out) override;
    virtual void printReport() override;
    virtual void saveReport() override;
    int getTotalErrors() const { return totalErrors; }
    void setTotalErrors(int count) { totalErrors = count; }
    
};
