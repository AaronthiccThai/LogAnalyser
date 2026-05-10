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
    // Critical events 

public:
    virtual void process(const ILogEntry& entry, int lineNumber) override;
    virtual void generateReport(std::ostream& out) override;
    virtual void printReport() override;
    virtual void saveReport() override;
    int getTotalErrors() const { return totalErrors; }
    void setTotalErrors(int count) { totalErrors = count; }
};

// Analyse the most severe error, get their line number, timestamp, and summary
// Potentially parse it into a LLM to get a more detailed summary of the error and potential solutions, and then print it in the report.
