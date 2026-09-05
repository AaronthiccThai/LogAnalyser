#pragma once

#include "models/ErrorLogEntry.h"
#include "utils/DateTime.h"
#include <string>
// Eg. 2026/05/15 14:22:31 [error] 1234#5678: *1 connect() failed (111: Connection refused)
class NginxErrorLogEntry : public ErrorLogEntry {
private:
    int pid;
    int tid;
    int connectionNumber;

public:
    int getProcessId() const {
        return pid;
    }

    int getThreadId() const {
        return tid;
    }

    int getConnectionNumber() const {
        return connectionNumber;
    }

    void setProcessId(int p) {
        pid = p;
    }

    void setThreadId(int t) {
        tid = t;
    }

    void setConnectionNumber(int num) {
        connectionNumber = num;
    }
    LogServer getServer() const override {
        return LogServer::Nginx;
    }


};