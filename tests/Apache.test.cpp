#include <catch2/catch_test_macros.hpp>

#include "parsers/apache/ApacheAccessLogParser.h"
#include "models/apache/ApacheAccessLogEntry.h"

TEST_CASE("Apache access log parses correctly") {

  ApacheAccessLogParser parser;

  SECTION("GET request") {
    const std::string line =
      R"(127.0.0.1 - john [10/Oct/2024:13:55:36 +1000] "GET /index.html HTTP/1.1" 200 2326)";

    auto result = parser.parse(line);

    REQUIRE(result != nullptr);

    auto* entry = dynamic_cast<ApacheAccessLogEntry*>(result.get());

    REQUIRE(entry != nullptr);

    REQUIRE(entry->getClientIP() == "127.0.0.1");
    REQUIRE(entry->getUser() == "john");
    REQUIRE(entry->getRequestMethod() == "GET");
    REQUIRE(entry->getStatusCode() == 200);
    REQUIRE(entry->getByteSize() == 2326);
  }

  SECTION("POST request") {
    const std::string line =
      R"(192.168.1.10 - alice [11/Oct/2024:09:30:15 +1000] "POST /login HTTP/1.1" 201 512)";

    auto result = parser.parse(line);

    REQUIRE(result != nullptr);

    auto* entry = dynamic_cast<ApacheAccessLogEntry*>(result.get());

    REQUIRE(entry != nullptr);

    REQUIRE(entry->getClientIP() == "192.168.1.10");
    REQUIRE(entry->getUser() == "alice");
    REQUIRE(entry->getRequestMethod() == "POST");
    REQUIRE(entry->getStatusCode() == 201);
    REQUIRE(entry->getByteSize() == 512);
  }

  SECTION("404 response") {
    const std::string line =
      R"(10.0.0.5 - bob [12/Oct/2024:18:22:10 +1000] "GET /missing.html HTTP/1.1" 404 1024)";

    auto result = parser.parse(line);

    REQUIRE(result != nullptr);

    auto* entry = dynamic_cast<ApacheAccessLogEntry*>(result.get());

    REQUIRE(entry != nullptr);

    REQUIRE(entry->getClientIP() == "10.0.0.5");
    REQUIRE(entry->getUser() == "bob");
    REQUIRE(entry->getRequestMethod() == "GET");
    REQUIRE(entry->getStatusCode() == 404);
    REQUIRE(entry->getByteSize() == 1024);
  }

  SECTION("Large response") {
    const std::string line =
      R"(172.16.0.20 - admin [13/Oct/2024:22:45:01 +1000] "GET /video.mp4 HTTP/1.1" 200 10485760)";

    auto result = parser.parse(line);

    REQUIRE(result != nullptr);

    auto* entry = dynamic_cast<ApacheAccessLogEntry*>(result.get());

    REQUIRE(entry != nullptr);

    REQUIRE(entry->getClientIP() == "172.16.0.20");
    REQUIRE(entry->getUser() == "admin");
    REQUIRE(entry->getRequestMethod() == "GET");
    REQUIRE(entry->getStatusCode() == 200);
    REQUIRE(entry->getByteSize() == 10485760);
  }
}