#include <string>
#include <DateTime.h>
#pragma once
struct ILogEntry {
  virtual ~ILogEntry() = default;
  virtual DateTime getTimestamp() const = 0;
};