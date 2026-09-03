#include "NginxErrorLogParser.h"
#include "models/nginx/NginxErrorLogEntry.h"
#include <regex>
#include <sstream>

// Eg. 2026/05/15 14:22:31 [error] 1234#5678: *1 connect() failed (111: Connection refused)
bool NginxErrorLogParser::supports(const std::string& line) const {
    static const std::regex pattern(
        R"(^\d{4}/\d{2}/\d{2} \d{2}:\d{2}:\d{2} \[\w+\] \d+#\d+:)"
    );

    return std::regex_search(line, pattern);
}

std::unique_ptr<ILogEntry> NginxErrorLogParser::parse(const std::string& logLine) const {
    auto entry = std::make_unique<NginxErrorLogEntry>();
    // need to include possible variations of log format such as 
    // [Date] [Time] [LogLevel] [PID#TID] Message {Some other stuff here too}
    std::regex pattern(
        R"((\d{4}/\d{2}/\d{2}) (\d{2}:\d{2}:\d{2}) \[(\w+)\] (\d+)#(\d+): (\*\d+ )?(.*))"
    );

    std::smatch matches;

    if (!std::regex_search(logLine, matches, pattern)) {
        return entry;
    }

    // Timestamp
    std::string fullDateTime = matches[1].str() + " " + matches[2].str();
    entry->setTimestamp(parseDateTime(fullDateTime));

    // Severity
    entry->setSeverity(matches[3]);

    // PID
    entry->setProcessId(safeStoi(matches[4]));

    // TID
    entry->setThreadId(safeStoi(matches[5]));

    // Message
    entry->setMessage(matches[7]);

    return entry;
}

DateTime NginxErrorLogParser::parseDateTime(const std::string& dateTimeStr) const {
    // YYYY/MM/DD HH:MM:SS
    DateTime dt;
    dt.year   = safeStoi(dateTimeStr.substr(0, 4));
    dt.month  = safeStoi(dateTimeStr.substr(5, 2));
    dt.day    = safeStoi(dateTimeStr.substr(8, 2));

    dt.hour   = safeStoi(dateTimeStr.substr(11, 2));
    dt.minute = safeStoi(dateTimeStr.substr(14, 2));
    dt.second = safeStoi(dateTimeStr.substr(17, 2));

    return dt;
}