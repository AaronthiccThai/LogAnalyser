#pragma once

#include "models/ErrorLogEntry.h"
#include "utils/DateTime.h"
#include <string>
// Eg. 2026/05/15 14:22:31 [error] 1234#5678: *1 connect() failed (111: Connection refused)
class NginxErrorLogEntry : public ErrorLogEntry {
private:
    DateTime timestamp;
    std::string logLevel;
    int pid;
    int tid;
    int connectionId;
    std::string message;

public:
    // Getters
    DateTime getTimestamp() const override;
    std::string getSeverity() const override;
    std::string getMessage() const override;

    int getPID() const;
    int getTID() const;
    int getConnectionId() const;

    // Setters
    void setTimestamp(const DateTime& ts);
    void setSeverity(const std::string& level);
    void setPID(int p);
    void setTID(int t);
    void setConnectionId(int id);
    void setMessage(const std::string& msg);
};