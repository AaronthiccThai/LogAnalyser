#include "NginxErrorLogParser.h"
#include "models/nginx/NginxErrorLogEntry.h"
#include <regex>
// [Date] [Time] [LogLevel] [PID#TID] Message

bool NginxErrorLogParser::supports(const std::string& line) const {
    // starts off with date in format YYYY/MM/DD 
    return std::regex_search(line, std::regex(R"(^\d{4}/\d{2}/\d{2})"));
}

std::unique_ptr<ILogEntry> NginxErrorLogParser::parse(const std::string& logLine) const {


}
DateTime NginxErrorLogParser::parseDateTime(const std::string& dateTimeStr) const {

}
