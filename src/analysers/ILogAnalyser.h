#pragma once
#include <memory>
#include "models/ILogEntry.h"
#include <string>
struct ILogAnalyser {
protected:
    std::string filename;
    int lineNumber;
public:
    virtual ~ILogAnalyser() = default;
    void setFilename(const std::string& fname) { filename = fname; }
    std::string getFilename() const { return filename; }
    void setLineNumber(int line) { lineNumber = line; }
    int getLineNumber() const { return lineNumber; }
    virtual void process(const ILogEntry& entry, int lineNumber) = 0;
    virtual void generateReport(std::ostream& out) = 0; // Generates summary for report
    virtual void printReport() = 0; // Prints report to console 
    virtual void saveReport() = 0; // Save reports to file
    virtual void reset() = 0;    
};