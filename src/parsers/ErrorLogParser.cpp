#include "ErrorLogParser.h"
#include <regex>
#include <iostream>

bool ErrorLogParser::supports(const std::string& line) const {
    return line.find("[") != std::string::npos;
}

std::unique_ptr<ILogEntry> ErrorLogParser::parse(const std::string& logLine) const {
    ErrorLogEntry entry{};

    std::regex basePattern(R"(\[([^\]]+)\]\s+\[([^\]]+)\]\s+(.*))");
    std::smatch matches;

    if (!std::regex_search(logLine, matches, basePattern)) {
        return std::make_unique<ErrorLogEntry>(entry);
    }

    entry.timestamp = parseDateTime(matches[1]);

    std::string moduleSeverity = matches[2];
    size_t pos = moduleSeverity.find(':');
    if (pos != std::string::npos) {
        entry.severity = moduleSeverity.substr(pos + 1);
    }

    std::string rest = matches[3];

    std::smatch pidMatch;
    if (std::regex_search(rest, pidMatch, std::regex(R"(\[pid\s+(\d+))"))) {
        entry.processId = safeStoi(pidMatch[1]);
    } else {
        entry.processId = -1;
    }

    std::smatch tidMatch;
    if (std::regex_search(rest, tidMatch, std::regex(R"(tid\s+(\d+))"))) {
        entry.threadId = safeStoi(pidMatch[1]);
    } else {
        entry.threadId = -1;
    }

    std::smatch clientMatch;
    if (std::regex_search(rest, clientMatch, std::regex(R"(\[client\s+([^\]]+)\])"))) {
        entry.clientAddress = clientMatch[1];
    }

    std::string message = rest;
    message = std::regex_replace(message, std::regex(R"(\[pid[^\]]+\])"), "");
    message = std::regex_replace(message, std::regex(R"(\[client[^\]]+\])"), "");
    message = std::regex_replace(message, std::regex(R"(^\s+)"), "");

    entry.message = message;

    return std::make_unique<ErrorLogEntry>(entry);
}

DateTime ErrorLogParser::parseDateTime(const std::string& dateTimeStr) const {
    DateTime dt{};

    std::regex pattern(
        R"(\w{3}\s+(\w{3})\s+(\d{2})\s+(\d{2}):(\d{2}):(\d{2})(?:\.\d+)?\s+(\d{4}))"
    );

    std::smatch matches;

    if (!std::regex_search(dateTimeStr, matches, pattern)) {
        return dt;
    }

    dt.month  = monthFromString(matches[1]);
    dt.day    = safeStoi(matches[2]);
    dt.hour   = safeStoi(matches[3]);
    dt.minute = safeStoi(matches[4]);
    dt.second = safeStoi(matches[5]);
    dt.year   = safeStoi(matches[6]);

    return dt;
}