#pragma once
#include "ILogAnalyser.h"
#include <iostream>
class RequestCountAnalyser : public ILogAnalyser {
private:
    int requestCount = 0;
    int errorCount = 0;
    int totalProcessed = 0;
public:
    virtual void process(const ILogEntry& entry) override;
    virtual void printReport() override;
    int getRequestCount() const { return requestCount; }
    void setRequestCount(int count) { requestCount = count; }
    int getErrorCount() const { return errorCount; } 
    void setErrorCount(int count) { errorCount = count; }
    int getTotalProcessed() const { return totalProcessed; }
    void setTotalProcessed(int count) { totalProcessed = count; }


};