#include "models/AccessLogEntry.h"

class NginxAccessLogEntry : public AccessLogEntry {

public:
    LogServer getServer() const override {
        return LogServer::Nginx;
    }
};