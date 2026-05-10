#include "ParserEngine.h"
#include "apache/ApacheAccessLogParser.h"
#include "apache/ApacheErrorLogParser.h"

/**
 * Constructor for ParserEngine
 */
ParserEngine::ParserEngine() {
    // Add parsers here
    parsers.push_back(std::make_unique<ApacheAccessLogParser>());
    parsers.push_back(std::make_unique<ApacheErrorLogParser>());
}

/**
 * Parse a log line into a log entry
 * @param line The log line to parse
 * @return A unique pointer to the parsed log entry, or nullptr if parsing fails
 */
std::unique_ptr<ILogEntry> ParserEngine::parse(const std::string& line) {
    for (const auto& parser : parsers) {
        if (parser->supports(line)) {
            return parser->parse(line);
        }
    }
    return nullptr;
}