#include "models/AccessLogEntry.h"
class ApacheAccessLogEntry : public AccessLogEntry {
public:
    LogServer getServer() const override {
        return LogServer::Apache;
    }

};