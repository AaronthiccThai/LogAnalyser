#pragma once
#include "models/ILogParser.h"
#include "models/ErrorLogEntry.h"
#include "utils/DateTime.h"

class ApacheErrorLogParser : public ILogParser {
public:
    bool supports(const std::string& line) const override;
    std::unique_ptr<ILogEntry> parse(const std::string& logLine) const override;
    DateTime parseDateTime(const std::string& dateTimeStr) const override;
};