#pragma once
#include <string>
#include "models/ILogEntry.h"
#include "utils/DateTime.h"

class ErrorLogEntry : public ILogEntry {
protected:
    DateTime timestamp;
    std::string severity;
    std::string message;

public:
    virtual ~ErrorLogEntry() = default;

    // Shared getters
    DateTime getTimestamp() const override {
        return timestamp;
    }

    std::string getSeverity() const {
        return severity;
    }

    std::string getMessage() const {
        return message;
    }

    std::string getType() const override {
        return "error";
    }

    // Shared setters
    void setTimestamp(const DateTime& ts) {
        timestamp = ts;
    }

    void setSeverity(const std::string& s) {
        severity = s;
    }

    void setMessage(const std::string& msg) {
        message = msg;
    }
};