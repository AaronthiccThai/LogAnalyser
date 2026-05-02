#pragma once
#include <string>
#include "ILogEntry.h"
#include "DateTime.h"
// [IP address of client] [- means requested piece of info not available] [user id of person requesting] [time request was recieved] [request line in double quotes] [status code] [size of object]
 
struct AccessLogEntry: public ILogEntry {
  std::string ip;
  std::string user;
  DateTime timestamp; // [day/month/year:hour:minute:second zone]
  std::string requestMethod;
  int statusCode;
  int byteSize;
  DateTime getTimestamp() const override {
    return timestamp;
  }
  std::string getType() const override {
    return "apache-access";
  }
};
