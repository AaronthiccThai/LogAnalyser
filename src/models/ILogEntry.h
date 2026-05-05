#pragma once
#include <string>
#include "utils/DateTime.h"

// Base interface for log entries. Specific log types (e.g. access, error) will derive from this.
struct ILogEntry {
  virtual ~ILogEntry() = default;
  virtual DateTime getTimestamp() const = 0;
  // Get the type of log entry (e.g. "apache-access", "apache-error", more to be added in future)
  virtual std::string getType() const = 0;
};