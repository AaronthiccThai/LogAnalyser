#pragma once
#include <string>
#include "interfaces/ILogEntry.h"
#include "DateTime.h" 
// [Date] [Module producing error: severity] [process id] [client id] [client address] [detailed error]

struct ErrorLogEntry : public ILogEntry {
  DateTime timestamp;
  std::string message;
  std::string severity;
  int processId;
  int threadId;
  std::string clientAddress;
  DateTime getTimestamp() const override {
    return timestamp;
  }
};