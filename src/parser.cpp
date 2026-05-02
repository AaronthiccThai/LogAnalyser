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
        std::cout << entry.timestamp.year << " "
          << entry.timestamp.day << " "
          << entry.timestamp.hour << std::endl;
    }
}

AccessLogEntry parseAccessLog(const std::string& logLine) {
    AccessLogEntry entry{};

    std::regex pattern(
      R"LOG((\S+)\s+\S+\s+(\S+)\s+\[([^\]]+)\]\s+"(\S+)\s+([^"]+)"\s+(\d{3})\s+(\d+))LOG"
    );

    std::smatch matches;

    if (std::regex_search(logLine, matches, pattern)) {
        entry.ip = matches[1];
        entry.user = matches[2];
        entry.timestamp = parseAccessDateTime(matches[3]);
        entry.requestMethod = matches[4];

        entry.statusCode = safeStoi(matches[6]);  
        entry.byteSize  = safeStoi(matches[7]);    
    }

    return entry;
}


ErrorLogEntry parseErrorLog(const std::string& logLine) {
    ErrorLogEntry entry{}; 

    std::regex basePattern(
        R"(\[([^\]]+)\]\s+\[([^\]]+)\]\s+(.*))"
    );

    std::smatch matches;
    if (!std::regex_search(logLine, matches, basePattern)) {
        std::cout << "BASE PARSE FAILED: " << logLine << std::endl;
        return entry;
    }
    // Timestamp
    entry.timestamp = parseErrorDateTime(matches[1]);

    // Severity 
    std::string moduleSeverity = matches[2];
    size_t pos = moduleSeverity.find(':');
    if (pos != std::string::npos) {
        entry.severity = moduleSeverity.substr(pos + 1);
    }

    std::string rest = matches[3];

    // PID
    std::smatch pidMatch;
    if (std::regex_search(rest, pidMatch, std::regex(R"(\[pid\s+(\d+))"))) {
        entry.processId = safeStoi(pidMatch[1]);
    } else {
        entry.processId = -1;
    }

    // TID
    std::smatch tidMatch;
    if (std::regex_search(rest, tidMatch, std::regex(R"(tid\s+(\d+))"))) {
        entry.threadId = safeStoi(tidMatch[1]); 
    } else {
        entry.threadId = -1;
    }

    // Client
    std::smatch clientMatch;
    if (std::regex_search(rest, clientMatch, std::regex(R"(\[client\s+([^\]]+)\])"))) {
        entry.clientAddress = clientMatch[1];
    }

    // Message cleanup
    std::string message = rest;
    message = std::regex_replace(message, std::regex(R"(\[pid[^\]]+\])"), "");
    message = std::regex_replace(message, std::regex(R"(\[client[^\]]+\])"), "");
    message = std::regex_replace(message, std::regex(R"(^\s+)"), "");

    entry.message = message;

    return entry;
}


DateTime parseAccessDateTime(const std::string& dateTimeStr) {
    DateTime dt{};
    // [Thu Apr 30 07:34:15.447146 2026]
    std::regex pattern(R"LOG((\d{2})/(\w{3})/(\d{4}):(\d{2}):(\d{2}):(\d{2}))LOG");

    std::smatch matches;

    if (!std::regex_search(dateTimeStr, matches, pattern)) {
        return dt;
    }

    dt.day = safeStoi(matches[1]);
    dt.month = monthFromString(matches[2]);
    dt.year = safeStoi(matches[3]);
    dt.hour = safeStoi(matches[4]);
    dt.minute = safeStoi(matches[5]);
    dt.second = safeStoi(matches[6]);

    return dt;
}


DateTime parseErrorDateTime(const std::string& dateTimeStr) {
    DateTime dt{};
    // [Thu Apr 30 10:15:11.123456 2026] 
    std::regex pattern(
        R"LOG(\w{3}\s+(\w{3})\s+(\d{2})\s+(\d{2}):(\d{2}):(\d{2})(?:\.\d+)?\s+(\d{4}))LOG"
    );

    std::smatch matches;

    if (!std::regex_search(dateTimeStr, matches, pattern)) {
        printf("ERROR DATE PARSE FAILED: %s\n", dateTimeStr.c_str());
        return dt;
    }
    printf("PARSED ERROR DATE: %s %s %s:%s:%s.%s %s\n", 
        matches[0].str().c_str(), 
        matches[1].str().c_str(), matches[2].str().c_str(), 
        matches[3].str().c_str(), matches[4].str().c_str(), 
        matches[5].str().c_str(), matches[6].str().c_str()
    );
    dt.month  = monthFromString(matches[1]);
    dt.day    = safeStoi(matches[2]);
    dt.hour   = safeStoi(matches[3]);
    dt.minute = safeStoi(matches[4]);
    dt.second = safeStoi(matches[5]);
    dt.year   = safeStoi(matches[6]);

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

int safeStoi(const std::string& str, int defaultVal) {
    try {
        return std::stoi(str);
    } catch (...) {
        return defaultVal;
    }
}