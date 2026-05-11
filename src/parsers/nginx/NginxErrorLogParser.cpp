
#include "models/ILogParser.h"
#include "models/ILogEntry.h"
#include "utils/DateTime.h" 
// nginx logs
// log_format main '$remote_addr - $remote_user [$time_local] "$request" '
//                '$status $body_bytes_sent "$http_referer" '
//                '"$http_user_agent"';

// 127.0.0.1 - - [10/May/2026:12:45:33 +0000] "GET /index.html HTTP/1.1" 200 612 "-" "Mozilla/5.0"

class NginxErrorLogParser : public ILogParser {
public:
    bool supports(const std::string& line) const override;
    std::unique_ptr<ILogEntry> parse(const std::string& logLine) const override;
    DateTime parseDateTime(const std::string& dateTimeStr) const override;
};