#pragma once
#include "models/ILogEntry.h"
#include "ILogAnalyser.h"
#include <vector>
#include <memory> 

class AnalyserEngine {
public:
    AnalyserEngine();

    void process(const ILogEntry& entry, int lineNumber);
    void printReport();
    void saveReport();
    void setFilename(const std::string& fname);
    void setLineNumber(int line);
private:
    std::vector<std::unique_ptr<ILogAnalyser>> analysers;
};

// can also probably create a report that is saved so users can read it easily not on the console
// add filename into output or report