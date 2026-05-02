#pragma once
#include <string>
#include "DateTime.h"

struct ILogEntry {
  virtual ~ILogEntry() = default;
  virtual DateTime getTimestamp() const = 0;
  virtual std::string getType() const = 0;
};