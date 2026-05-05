#pragma once
#include <string>
#include "models/ILogEntry.h"
#include "utils/DateTime.h"

// Base class for error log entries. Specific formats (e.g. Apache, Nginx) will derive from this.
class ErrorLogEntry : public ILogEntry {
public:
    virtual ~ErrorLogEntry() = default;

    virtual DateTime getTimestamp() const override = 0;
    virtual std::string getSeverity() const = 0;
    virtual std::string getMessage() const = 0;

    std::string getType() const override {
        return "error";  // generic
    }
};