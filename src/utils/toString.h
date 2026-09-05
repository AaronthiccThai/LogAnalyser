#include "models/LogType.h"
#include <string>
inline std::string toString(LogServer server) {
    switch (server) {
        case LogServer::Apache:
            return "Apache";
        case LogServer::Nginx:
            return "Nginx";
    }

    return "Unknown";
}

inline std::string toString(LogCategory category) {
    switch (category) {
        case LogCategory::Access:
            return "Access";
        case LogCategory::Error:
            return "Error";
    }

    return "Unknown";
}