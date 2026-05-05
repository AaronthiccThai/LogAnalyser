#pragma once
#include "models/ILogEntry.h"
#include "ILogAnalyser.h"
#include <vector>
#include <memory> 

class AnalyserEngine {
public:
    AnalyserEngine();

    void process(const ILogEntry& entry); 
    void printReport();

private:
    std::vector<std::unique_ptr<ILogAnalyser>> analysers;
};