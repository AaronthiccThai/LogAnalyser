#include "AnalyserEngine.h"
#include "RequestCountAnalyser.h"
#include "ErrorSeverityAnalyser.h"
AnalyserEngine::AnalyserEngine() {
}

void AnalyserEngine::process(const ILogEntry& entry, int lineNumber) {
    for (auto& analyser : analysers) {
        analyser->process(entry, lineNumber);
    }
}
void AnalyserEngine::enableRequestAnalyser() {
    analysers.push_back(
        std::make_unique<RequestCountAnalyser>()
    );
}

void AnalyserEngine::enableSeverityAnalyser() {
    analysers.push_back(
        std::make_unique<ErrorSeverityAnalyser>()
    );
}

void AnalyserEngine::enableAll() {
    enableRequestAnalyser();
    enableSeverityAnalyser();
}

void AnalyserEngine::printReport() {
    for (auto& analyser : analysers) {
        analyser->printReport();
    }
}

void AnalyserEngine::setFilename(const std::string& fname) {
    for (auto& analyser : analysers) {
        analyser->setFilename(fname);
    }
}
void AnalyserEngine::setLineNumber(int line) {
    for (auto& analyser : analysers) {
        analyser->setLineNumber(line);
    }
}

void AnalyserEngine::saveReport() {
    for (auto& analyser : analysers) {
        analyser->saveReport();
    }
}