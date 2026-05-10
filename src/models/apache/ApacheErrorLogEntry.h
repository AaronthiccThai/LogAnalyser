#pragma once
#include "models/ErrorLogEntry.h"
#include "utils/DateTime.h"
#include <string>

class ApacheErrorLogEntry : public ErrorLogEntry {
private:
    DateTime timestamp;
    std::string message;
    std::string severity;
    int processId;
    int threadId;
    std::string clientAddress;
    std::string module;
public:
    DateTime getTimestamp() const override { return timestamp; }
    std::string getSeverity() const override { return severity; }
    std::string getMessage() const override { return message; }
    std::string getType() const override { return "error"; }
    std::string getModule() const { return module; }
    std::string getClientAddress() const { return clientAddress; }
    // setters (used by parser)
    void setTimestamp(const DateTime& dt) { timestamp = dt; }
    void setSeverity(const std::string& s) { severity = s; }
    void setMessage(const std::string& m) { message = m; }
    void setProcessId(int pid) { processId = pid; }
    void setThreadId(int tid) { threadId = tid; }
    void setClientAddress(const std::string& addr) { clientAddress = addr; }
    void setModule(const std::string& m) { module = m; }

};