#pragma once
#include <memory>
#include "models/ILogEntry.h"

struct ILogAnalyser {
    virtual ~ILogAnalyser() = default;

    virtual void process(const ILogEntry& entry) = 0;
    virtual void printReport() = 0;

};