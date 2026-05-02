#pragma once
#include <vector>
#include <memory>
#include "ILogParser.h"

class ParserEngine {
private:
    std::vector<std::unique_ptr<ILogParser>> parsers;

public:
    ParserEngine();
    std::unique_ptr<ILogEntry> parse(const std::string& line);
};