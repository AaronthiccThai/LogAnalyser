#pragma once
#include <string>
#include "utils/DateTime.h"
#include "LogType.h"
// Base interface for log entries. Specific log types (e.g. access, error) will derive from this.
struct ILogEntry {
  virtual ~ILogEntry() = default;
  virtual DateTime getTimestamp() const = 0;
  
    virtual LogServer getServer() const = 0;
    virtual LogCategory getCategory() const = 0;
};