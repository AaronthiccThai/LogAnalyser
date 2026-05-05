#pragma once
#include "ILogAnalyser.h"
#include <map>
#include <string>
class ErrorSeverityAnalyser : public ILogAnalyser {
private:
  std::map<std::string, int> severityCounts;

public:
    virtual void process(const ILogEntry& entry) override;
    virtual void printReport() override;
};

