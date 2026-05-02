#pragma once
#include "ILogParser.h"
#include "models/ErrorLogEntry.h"

class ErrorLogParser : public ILogParser {
public:
    bool supports(const std::string& line) const override;
    std::unique_ptr<ILogEntry> parse(const std::string& logLine) const override;

private:
    DateTime parseDateTime(const std::string& dateTimeStr) const;
};