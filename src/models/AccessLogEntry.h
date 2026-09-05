#pragma once
#include <string>
#include "models/ILogEntry.h"
#include "utils/DateTime.h"

class AccessLogEntry : public ILogEntry {
protected:
    DateTime timestamp;
    std::string clientIP;
    std::string user;
    std::string requestMethod;
    int statusCode = 0;
    int byteSize = 0;

public:
    virtual ~AccessLogEntry() = default;

    DateTime getTimestamp() const override {
        return timestamp;
    }

    std::string getClientIP() const {
        return clientIP;
    }

    std::string getUser() const {
        return user;
    }

    std::string getRequestMethod() const {
        return requestMethod;
    }

    int getStatusCode() const {
        return statusCode;
    }

    int getByteSize() const {
        return byteSize;
    }

    // shared setters (used by parsers)
    void setTimestamp(const DateTime& dt) {
        timestamp = dt;
    }

    void setClientIP(const std::string& ip) {
        clientIP = ip;
    }

    void setUser(const std::string& u) {
        user = u;
    }

    void setRequestMethod(const std::string& m) {
        requestMethod = m;
    }

    void setStatusCode(int code) {
        statusCode = code;
    }

    void setByteSize(int size) {
        byteSize = size;
    }

    LogCategory getCategory() const override {
        return LogCategory::Access;
    } 
};