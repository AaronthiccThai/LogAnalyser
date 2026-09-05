#pragma once
#include "models/ErrorLogEntry.h"
#include "utils/DateTime.h"
#include <string>

class ApacheErrorLogEntry : public ErrorLogEntry {
private:
    int processId;
    int threadId;
    std::string clientAddress;
    std::string module;

public:
    std::string getModule() const {
        return module;
    }

    std::string getClientAddress() const {
        return clientAddress;
    }

    void setProcessId(int pid) {
        processId = pid;
    }

    void setThreadId(int tid) {
        threadId = tid;
    }

    void setClientAddress(const std::string& addr) {
        clientAddress = addr;
    }

    void setModule(const std::string& m) {
        module = m;
    }
    LogServer getServer() const override {
        return LogServer::Apache;
    }

};