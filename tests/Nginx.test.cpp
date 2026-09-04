#include <catch2/catch_test_macros.hpp>

#include "parsers/nginx/NginxAccessLogParser.h"
#include "models/nginx/NginxAccessLogEntry.h"


TEST_CASE("Nginx access log parses GET request correctly") {

  NginxAccessLogParser parser;

  const std::string line =
    R"(127.0.0.1 - - [10/May/2026:12:45:33 +0000] "GET /index.html HTTP/1.1" 200 612 "-" "Mozilla/5.0")";

  auto result = parser.parse(line);

  REQUIRE(result != nullptr);

  auto* entry = dynamic_cast<NginxAccessLogEntry*>(result.get());

  REQUIRE(entry != nullptr);

  REQUIRE(entry->getClientIP() == "127.0.0.1");
  REQUIRE(entry->getUser() == "-");
  REQUIRE(entry->getRequestMethod() == "GET");
  REQUIRE(entry->getStatusCode() == 200);
  REQUIRE(entry->getByteSize() == 612);
}


TEST_CASE("Nginx access log parses POST request correctly") {

  NginxAccessLogParser parser;

  const std::string line =
    R"(192.168.1.20 - alice [11/May/2026:09:30:15 +0000] "POST /login HTTP/1.1" 201 1024 "-" "Mozilla/5.0")";

  auto result = parser.parse(line);

  REQUIRE(result != nullptr);

  auto* entry = dynamic_cast<NginxAccessLogEntry*>(result.get());

  REQUIRE(entry != nullptr);

  REQUIRE(entry->getClientIP() == "192.168.1.20");
  REQUIRE(entry->getUser() == "alice");
  REQUIRE(entry->getRequestMethod() == "POST");
  REQUIRE(entry->getStatusCode() == 201);
  REQUIRE(entry->getByteSize() == 1024);
}


TEST_CASE("Nginx access log parses 404 response correctly") {

  NginxAccessLogParser parser;

  const std::string line =
    R"(10.0.0.5 - bob [12/May/2026:18:22:10 +0000] "GET /missing.html HTTP/1.1" 404 1536 "-" "Mozilla/5.0")";

  auto result = parser.parse(line);

  REQUIRE(result != nullptr);

  auto* entry = dynamic_cast<NginxAccessLogEntry*>(result.get());

  REQUIRE(entry != nullptr);

  REQUIRE(entry->getClientIP() == "10.0.0.5");
  REQUIRE(entry->getUser() == "bob");
  REQUIRE(entry->getRequestMethod() == "GET");
  REQUIRE(entry->getStatusCode() == 404);
  REQUIRE(entry->getByteSize() == 1536);
}


TEST_CASE("Nginx access log parses DELETE request correctly") {

  NginxAccessLogParser parser;

  const std::string line =
    R"(172.16.0.10 - admin [13/May/2026:22:45:01 +0000] "DELETE /users/123 HTTP/1.1" 204 0 "-" "curl/8.0")";

  auto result = parser.parse(line);

  REQUIRE(result != nullptr);

  auto* entry = dynamic_cast<NginxAccessLogEntry*>(result.get());

  REQUIRE(entry != nullptr);

  REQUIRE(entry->getClientIP() == "172.16.0.10");
  REQUIRE(entry->getUser() == "admin");
  REQUIRE(entry->getRequestMethod() == "DELETE");
  REQUIRE(entry->getStatusCode() == 204);
  REQUIRE(entry->getByteSize() == 0);
}


TEST_CASE("Nginx access log parses large response correctly") {

  NginxAccessLogParser parser;

  const std::string line =
    R"(203.0.113.50 - john [14/May/2026:15:10:25 +0000] "GET /video.mp4 HTTP/1.1" 200 10485760 "-" "Mozilla/5.0")";

  auto result = parser.parse(line);

  REQUIRE(result != nullptr);

  auto* entry = dynamic_cast<NginxAccessLogEntry*>(result.get());

  REQUIRE(entry != nullptr);

  REQUIRE(entry->getClientIP() == "203.0.113.50");
  REQUIRE(entry->getUser() == "john");
  REQUIRE(entry->getRequestMethod() == "GET");
  REQUIRE(entry->getStatusCode() == 200);
  REQUIRE(entry->getByteSize() == 10485760);
}


TEST_CASE("Nginx access log supports valid log line") {

  NginxAccessLogParser parser;

  const std::string line =
    R"(127.0.0.1 - - [10/May/2026:12:45:33 +0000] "GET /index.html HTTP/1.1" 200 612 "-" "Mozilla/5.0")";

  REQUIRE(parser.supports(line));
}


TEST_CASE("Nginx access log does not support invalid log line") {

  NginxAccessLogParser parser;

  const std::string line = "this is not a valid nginx access log";

  REQUIRE_FALSE(parser.supports(line));
}

