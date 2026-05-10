#include "ApacheErrorLogParser.h"
#include "models/apache/ApacheErrorLogEntry.h"
#include <regex>
#include <iostream>

/**
 * Check if the parser supports the given log line
 * @param line The log line to check
 * @return True if the parser supports the line, false otherwise
 */
bool ApacheErrorLogParser::supports(const std::string& line) const {
    return line.find("[") != std::string::npos;
}

/**
 * Parse a log line into a log entry
 * @param logLine The log line to parse
 * @return A unique pointer to the parsed log entry, or nullptr if parsing fails
 */
std::unique_ptr<ILogEntry> ApacheErrorLogParser::parse(const std::string& logLine) const {
    auto entry = std::make_unique<ApacheErrorLogEntry>();

    std::regex basePattern(R"(\[([^\]]+)\]\s+\[([^\]]+)\]\s+(.*))");
    std::smatch matches;

    if (!std::regex_search(logLine, matches, basePattern)) {
        return entry;
    }
    // DATE
    entry->setTimestamp(parseDateTime(matches[1]));
    // MODULE + SEVERITY
    std::string moduleSeverity = matches[2];
    size_t pos = moduleSeverity.find(':');
    if (pos != std::string::npos) {
        // Format: [core:error]
        entry->setModule(moduleSeverity.substr(0, pos));
        entry->setSeverity(moduleSeverity.substr(pos + 1));
    } else {
        // Format: [notice]
        entry->setModule("");
        entry->setSeverity(moduleSeverity);
    }

    std::string rest = matches[3];
    // PID - not all entries have this, so we need to check
    std::smatch pidMatch;
    if (std::regex_search(rest, pidMatch, std::regex(R"(\[pid\s+(\d+))"))) {
        entry->setProcessId(safeStoi(pidMatch[1]));
    } else {
        entry->setProcessId(-1);
    }
    // TID - also not always present
    std::smatch tidMatch;
    if (std::regex_search(rest, tidMatch, std::regex(R"(tid\s+(\d+))"))) {
        entry->setThreadId(safeStoi(tidMatch[1]));
    } else {
        entry->setThreadId(-1);
    }
    // CLIENT IP - also not always present
    std::smatch clientMatch;
    if (std::regex_search(rest, clientMatch, std::regex(R"(\[client\s+([^\]]+)\])"))) {
        entry->setClientAddress(clientMatch[1]);
    }
    // MSG
    std::string message = rest;
    message = std::regex_replace(message, std::regex(R"(\[pid[^\]]+\])"), "");
    message = std::regex_replace(message, std::regex(R"(\[client[^\]]+\])"), "");
    message = std::regex_replace(message, std::regex(R"(^\s+)"), "");

    entry->setMessage(message);

    return entry;
}

/**
 * Parse a date and time string into a DateTime object
 * @param dateTimeStr The date and time string to parse
 * @return The parsed DateTime object
 */
DateTime ApacheErrorLogParser::parseDateTime(const std::string& dateTimeStr) const {
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