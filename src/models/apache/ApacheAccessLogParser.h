#pragma once

#include "models/ILogParser.h"
#include "models/AccessLogEntry.h"
#include "utils/DateTime.h"

// Parser for Apache access logs. Example log line:
// 127.0.0.1 - - [10/Oct/2023:13:55:36 +0000] "GET / HTTP/1.1" 200 612
class ApacheAccessLogParser : public ILogParser {
public:
    bool supports(const std::string& line) const override;
    std::unique_ptr<ILogEntry> parse(const std::string& logLine) const override;
    DateTime parseDateTime(const std::string& dateTimeStr) const override;
};