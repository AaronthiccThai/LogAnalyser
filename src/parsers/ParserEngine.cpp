#include "ParserEngine.h"
#include "AccessLogParser.h"
#include "ErrorLogParser.h"

ParserEngine::ParserEngine() {
    parsers.push_back(std::make_unique<AccessLogParser>());
    parsers.push_back(std::make_unique<ErrorLogParser>());
}

std::unique_ptr<ILogEntry> ParserEngine::parse(const std::string& line) {
    for (const auto& parser : parsers) {
        if (parser->supports(line)) {
            return parser->parse(line);
        }
    }
    return nullptr;
}