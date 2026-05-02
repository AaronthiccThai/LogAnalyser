#include "AccessLogParser.h"
#include <regex>

bool AccessLogParser::supports(const std::string& line) const {
    return line.find("\"") != std::string::npos;
}

std::unique_ptr<ILogEntry> AccessLogParser::parse(const std::string& logLine) const {
    AccessLogEntry entry{};

    std::regex pattern(
        R"LOG((\S+)\s+\S+\s+(\S+)\s+\[([^\]]+)\]\s+"(\S+)\s+([^"]+)"\s+(\d{3})\s+(\d+))LOG"
    );

    std::smatch matches;

    if (std::regex_search(logLine, matches, pattern)) {
        entry.ip = matches[1];
        entry.user = matches[2];
        entry.timestamp = parseDateTime(matches[3]);
        entry.requestMethod = matches[4];
        entry.statusCode = safeStoi(matches[6]);
        entry.byteSize   = safeStoi(matches[7]);
    }

    return std::make_unique<AccessLogEntry>(entry);
}

DateTime AccessLogParser::parseDateTime(const std::string& dateTimeStr) const {
    DateTime dt{};

    std::regex pattern(
        R"LOG((\d{2})/(\w{3})/(\d{4}):(\d{2}):(\d{2}):(\d{2}))LOG"
    );

    std::smatch matches;

    if (std::regex_search(dateTimeStr, matches, pattern)) {
        dt.day    = safeStoi(matches[1]);
        dt.month  = monthFromString(matches[2]);
        dt.year   = safeStoi(matches[3]);
        dt.hour   = safeStoi(matches[4]);
        dt.minute = safeStoi(matches[5]);
        dt.second = safeStoi(matches[6]);
    }

    return dt;
}