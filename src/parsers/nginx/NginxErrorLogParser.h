
#include "models/ILogParser.h"
#include "models/ILogEntry.h"
#include "utils/DateTime.h" 
// 2017/07/24 11:29:45 [notice] 22118#22118: using inherited sockets from “6;7;”

// [Date] [Time] [LogLevel] [PID#TID] Message
class NginxErrorLogParser : public ILogParser {
public:
    bool supports(const std::string& line) const override;
    std::unique_ptr<ILogEntry> parse(const std::string& logLine) const override;
    DateTime parseDateTime(const std::string& dateTimeStr) const override;
};