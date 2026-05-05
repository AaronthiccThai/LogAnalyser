#include "models/apache/ApacheAccessLogParser.h"
#include "models/apache/ApacheAccessLogEntry.h"
#include <regex>

bool ApacheAccessLogParser::supports(const std::string& line) const {
    return line.find("\"") != std::string::npos;
}

std::unique_ptr<ILogEntry> ApacheAccessLogParser::parse(const std::string& logLine) const {
    auto entry = std::make_unique<ApacheAccessLogEntry>();

    std::regex pattern(
        R"LOG((\S+)\s+\S+\s+(\S+)\s+\[([^\]]+)\]\s+"(\S+)\s+([^"]+)"\s+(\d{3})\s+(\d+))LOG"
    );

    std::smatch matches;

    if (std::regex_search(logLine, matches, pattern)) {
        entry->setIP(matches[1]);
        entry->setUser(matches[2]);
        entry->setTimestamp(parseDateTime(matches[3]));
        entry->setRequestMethod(matches[4]);
        entry->setStatusCode(safeStoi(matches[6]));
        entry->setByteSize(safeStoi(matches[7]));
    }

    return entry;
}

DateTime ApacheAccessLogParser::parseDateTime(const std::string& dateTimeStr) const {
    DateTime dt{};
    std::regex dtPattern(R"((\d{2})/(\w{3})/(\d{4}):(\d{2}):(\d{2}):(\d{2}))");
    std::smatch dtMatches;

    if (std::regex_search(dateTimeStr, dtMatches, dtPattern)) {
        dt.day = safeStoi(dtMatches[1]);
        dt.month = monthFromString(dtMatches[2]);
        dt.year = safeStoi(dtMatches[3]);
        dt.hour = safeStoi(dtMatches[4]);
        dt.minute = safeStoi(dtMatches[5]);
        dt.second = safeStoi(dtMatches[6]);
    }

    return dt;
}