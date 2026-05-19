#include "AccessLogEntry.h"
class ApacheAccessLogEntry : public AccessLogEntry {
private:
    std::string virtualHost; // example extra field

public:
    std::string getVirtualHost() const {
        return virtualHost;
    }

    void setVirtualHost(const std::string& v) {
        virtualHost = v;
    }
};