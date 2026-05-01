#include <string>
#include <memory>
#include "ILogEntry.h"
#pragma once
struct ILogParser {
  virtual ~ILogParser() = default;
  virtual bool canParse(const std::string& line) = 0;
  virtual std::unique_ptr<ILogEntry> parse(const std::string& line) = 0;
};