#include "AnalyserEngine.h"
#include "RequestCountAnalyser.h"
#include "ErrorSeverityAnalyser.h"

AnalyserEngine::AnalyserEngine() {
}

/**
 * Process a log entry by passing to all enabled analysers
 * @param entry The log entry to process
 * @param lineNumber The line number of the log entry in the file, for reference in
 */
void AnalyserEngine::process(const ILogEntry& entry, int lineNumber) {
    for (auto& analyser : analysers) {
        analyser->process(entry, lineNumber);
    }
}
/**
 * Enable the request count analyser
 */
void AnalyserEngine::enableRequestAnalyser() {
    analysers.push_back(
        std::make_unique<RequestCountAnalyser>()
    );
}
/**
 * Enable the error severity analyser
 */
void AnalyserEngine::enableSeverityAnalyser() {
    analysers.push_back(
        std::make_unique<ErrorSeverityAnalyser>()
    );
}
/**
 * Enable all analysers
 */
void AnalyserEngine::enableAll() {
    enableRequestAnalyser();
    enableSeverityAnalyser();
}

/**
 * Print the report for all enabled analysers
 */
void AnalyserEngine::printReport() {
    for (auto& analyser : analysers) {
        analyser->printReport();
    }
}

/**
 * Set the filename for all analysers, so they can reference it in reports
 * @param fname The filename to set
 */
void AnalyserEngine::setFilename(const std::string& fname) {
    for (auto& analyser : analysers) {
        analyser->setFilename(fname);
    }
}

/**
 * Set the line number for all analysers, so they can reference it in reports
 * @param line The line number to set
 */
void AnalyserEngine::setLineNumber(int line) {
    for (auto& analyser : analysers) {
        analyser->setLineNumber(line);
    }
}

/**
 * Save the report for all enabled analysers to file
 */
void AnalyserEngine::saveReport() {
    for (auto& analyser : analysers) {
        analyser->saveReport();
    }
}