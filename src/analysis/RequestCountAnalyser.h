#pragma once
#include "ILogAnalyser.h"
#include <iostream>
class RequestCountAnalyser : public ILogAnalyser {
private:
    int requestCount = 0;
    int errorCount = 0;

public:
  virtual void process(const ILogEntry& entry) override;
  virtual void printReport() override;
  int getRequestCount() const { return requestCount; }
  int setRequestCount(int count) { requestCount = count; }
  int getErrorCount() const { return errorCount; } 
  int setErrorCount(int count) { errorCount = count; }


};