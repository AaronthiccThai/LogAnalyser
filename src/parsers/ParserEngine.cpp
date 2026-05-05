#include "ParserEngine.h"
#include "apache/ApacheAccessLogParser.h"
#include "apache/ApacheErrorLogParser.h"

ParserEngine::ParserEngine() {
    parsers.push_back(std::make_unique<ApacheAccessLogParser>());
    parsers.push_back(std::make_unique<ApacheErrorLogParser>());
}

std::unique_ptr<ILogEntry> ParserEngine::parse(const std::string& line) {
    for (const auto& parser : parsers) {
        if (parser->supports(line)) {
            return parser->parse(line);
        }
    }
    return nullptr;
}