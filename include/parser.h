#include "logs/AccessLogEntry.h"
#include "logs/ErrorLogEntry.h"

void parseLogs(const std::string& logLine);

AccessLogEntry parseAccessLog(const std::string& logLine);

ErrorLogEntry parseErrorLog(const std::string& logLine);

DateTime parseAccessDateTime(const std::string& dateTimeStr);

DateTime parseErrorDateTime(const std::string& dateTimeStr);

int monthFromString(const std::string& m);

int safeStoi(const std::string& str, int defaultVal = -1);