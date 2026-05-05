#pragma once
#include <string>
#include <memory>
#include "models/ILogEntry.h"
#include "utils/DateTime.h"
// Base interface for log parsers. Specific log types (e.g. access, error) will implement this.
struct ILogParser {
  virtual ~ILogParser() = default;
  virtual bool supports(const std::string& line) const = 0;
  virtual std::unique_ptr<ILogEntry> parse(const std::string& line) const = 0;  
  virtual DateTime parseDateTime(const std::string& dateTimeStr) const = 0;

  int monthFromString(const std::string& m) const {
    if (m == "Jan") return 1;
    if (m == "Feb") return 2;
    if (m == "Mar") return 3;
    if (m == "Apr") return 4;
    if (m == "May") return 5;
    if (m == "Jun") return 6;
    if (m == "Jul") return 7;
    if (m == "Aug") return 8;
    if (m == "Sep") return 9;
    if (m == "Oct") return 10;
    if (m == "Nov") return 11;
    if (m == "Dec") return 12;
    return -1; 
  }
  int safeStoi(const std::string& str, int defaultVal = -1) const {
    try {
        return std::stoi(str);  
    } catch (const std::exception&) {
        return defaultVal;
    }
  }  
};