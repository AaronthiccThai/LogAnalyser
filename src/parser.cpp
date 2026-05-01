#include "parser.h"
#include <regex>
#include <iostream>
void parseLogs(const std::string& logLine) {
    if (logLine.find("\"") != std::string::npos) {
        // likely access log (has "GET / HTTP/1.1")
        AccessLogEntry entry = parseAccessLog(logLine);
        std::cout << "Access log parsed: " << entry.ip << std::endl;
    } 
    else if (logLine.find("[") != std::string::npos) {
        // likely error log
        ErrorLogEntry entry = parseErrorLog(logLine);
        std::cout << "Error log parsed: " << entry.message << std::endl;
    }
}

AccessLogEntry parseAccessLog(const std::string& logLine) {
    AccessLogEntry entry;
    // 127.0.0.1 - - [30/Apr/2026:10:12:46 +0000] "GET /style.css HTTP/1.1" 200 1024
    std::regex pattern(
      R"LOG((\S+)\s+\S+\s+(\S+)\s+\[([^\]]+)\]\s+"(\S+)\s+([^"]+)"\s+(\d{3})\s+(\d+))LOG"
    );
    std::smatch matches;
    if (std::regex_search(logLine, matches, pattern)) {
        entry.ip = matches[1];
        entry.user = matches[2];
        entry.timestamp = parseAccessDateTime(matches[3]);
        entry.requestMethod = matches[4];
        entry.statusCode = std::stoi(matches[6]);
        entry.byteSize = std::stoi(matches[7]);
        // [day/month/year:hour:minute:second zone]
 
    }
    return entry;
}


ErrorLogEntry parseErrorLog(const std::string& logLine) {
    ErrorLogEntry entry;
    // Example error log format: 
    // [Fri Sep 09 10:42:29.902022 2011] [core:error] [pid 35708:tid 4328636416] [client 72.15.99.187] 
    // AH00124: Request exceeded the limit of 10 internal redirects due to probable configuration error
    std::regex pattern(
      R"LOG(\[([^\]]+)\]\s+\[([^\]]+)\]\s+\[pid\s+(\d+):tid\s+(\d+)\]\s+\[client\s+([^\]]+)\]\s+(.*))LOG"
    );
    printf("Parsing error log line: %s\n", logLine.c_str());
    std::smatch matches;
    if (std::regex_search(logLine, matches, pattern)) {
        entry.timestamp = parseErrorDateTime(matches[1]);
        std::string moduleSeverity = matches[2];
        size_t pos = moduleSeverity.find(':');

        if (pos != std::string::npos) {
            entry.severity = moduleSeverity.substr(pos + 1); // "error"
        }        
        
        entry.processId = std::stoi(matches[3]);
        entry.threadId = std::stoi(matches[4]);
        entry.clientAddress = matches[5];
        entry.message = matches[6];
    }
    return entry;
}


DateTime parseAccessDateTime(const std::string& dateTimeStr) {
  DateTime dt;
  // int day;
  // int month;
  // int year;
  // int hour;
  // int minute;
  // int second;
  std::regex pattern(R"LOG((\d{2})/(\w{3})/(\d{4}):(\d{2}):(\d{2}):(\d{2}))LOG");
  std::smatch matches;
  if (std::regex_search(dateTimeStr, matches, pattern)) {
    dt.day = std::stoi(matches[1]);
    dt.month = monthFromString(matches[2]);
    dt.year = std::stoi(matches[3]);
    dt.hour = std::stoi(matches[4]);
    dt.minute = std::stoi(matches[5]);
    dt.second = std::stoi(matches[6]);
  }
  return dt;
}


DateTime parseErrorDateTime(const std::string& dateTimeStr) {
    // [Fri Sep 09 10:42:29.902022 2011] [core:error] [pid 35708:tid 4328636416] [client 72.15.99.187] 
  DateTime dt;
  std::regex pattern(R"LOG(\w{3}\s+(\w{3})\s+(\d{2})\s+(\d{2}):(\d{2}):(\d{2})\.\d+\s+(\d{4}))LOG");
  std::smatch matches;
  if (std::regex_search(dateTimeStr, matches, pattern)) {
    dt.day = std::stoi(matches[3]);
    dt.month = monthFromString(matches[2]);
    dt.hour = std::stoi(matches[4]);
    dt.minute = std::stoi(matches[5]);
    dt.second = std::stoi(matches[6]);
    dt.year = std::stoi(matches[7]);
  }
  return dt;
}

int monthFromString(const std::string& m) {
    if (m == "Jan") return 1;
    if (m == "Feb") return 2;
    if (m == "Mar") return 3;
    if (m == "Apr") return 4;
    if (m == "May") return 5;
    if (m == "Jun") return 6;
    if (m == "Jul") return 7;
    if (m == "Aug") return 8;
    if (m == "Sep") return 9;
    if (m == "Oct") return 10;
    if (m == "Nov") return 11;
    if (m == "Dec") return 12;
    return 0;
}