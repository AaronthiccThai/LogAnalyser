#pragma once

#include "models/AccessLogEntry.h"
#include "utils/DateTime.h"
#include <string>

class ApacheAccessLogEntry : public AccessLogEntry {
private:
    std::string ip;
    std::string user;
    DateTime timestamp;
    std::string requestMethod;
    int statusCode;
    int byteSize;

public:
    // getters
    DateTime getTimestamp() const override { return timestamp; }
    std::string getClientIP() const override { return ip; }
    std::string getUser() const override { return user; }
    std::string getRequestMethod() const override { return requestMethod; }
    int getStatusCode() const override { return statusCode; }
    int getByteSize() const override { return byteSize; }
    std::string getType() const override { return "apache-access"; }
    // setters (used by parser)
    void setIP(const std::string& val) { ip = val; }
    void setUser(const std::string& val) { user = val; }
    void setTimestamp(const DateTime& dt) { timestamp = dt; }
    void setRequestMethod(const std::string& val) { requestMethod = val; }
    void setStatusCode(int val) { statusCode = val; }
    void setByteSize(int val) { byteSize = val; }
};