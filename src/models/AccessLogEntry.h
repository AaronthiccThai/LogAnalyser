#pragma once
#include <string>
#include "models/ILogEntry.h"
#include "utils/DateTime.h"

// Base class for access log entries. Specific formats (e.g. Apache, Nginx) will derive from this.
// Some fields will be empty or -1 if not applicable to a specific log type.
class AccessLogEntry : public ILogEntry {
public:
    virtual ~AccessLogEntry() = default;

    virtual DateTime getTimestamp() const override = 0;
    virtual std::string getClientIP() const = 0;
    virtual std::string getUser() const = 0;
    virtual std::string getRequestMethod() const = 0;
    virtual int getStatusCode() const = 0;
    virtual int getByteSize() const = 0;

    std::string getType() const override {
        return "access";  // generic
    }
};