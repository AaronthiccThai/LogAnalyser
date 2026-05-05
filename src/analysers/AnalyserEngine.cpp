#include "AnalyserEngine.h"
#include "RequestCountAnalyser.h"
#include "ErrorSeverityAnalyser.h"
AnalyserEngine::AnalyserEngine() {
    analysers.push_back(std::make_unique<RequestCountAnalyser>());
    analysers.push_back(std::make_unique<ErrorSeverityAnalyser>());
}

void AnalyserEngine::process(const ILogEntry& entry) {
    for (auto& analyser : analysers) {
        analyser->process(entry);
    }
}

void AnalyserEngine::printReport() {
    for (auto& analyser : analysers) {
        analyser->printReport();
    }
}