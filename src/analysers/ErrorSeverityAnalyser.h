#pragma once
#include "ILogAnalyser.h"
#include <map>
#include <string>
class ErrorSeverityAnalyser : public ILogAnalyser {
private:
    std::map<std::string, int> severityCounts;
    int totalErrors = 0;
public:
    virtual void process(const ILogEntry& entry) override;
    virtual void printReport() override;
    int getTotalErrors() const { return totalErrors; }
    void setTotalErrors(int count) { totalErrors = count; }
};

