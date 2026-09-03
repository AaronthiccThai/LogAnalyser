#include "models/AccessLogEntry.h"

class NginxAccessLogEntry : public AccessLogEntry {
private:

public:
    // NOTE: only override if different meaning needed, otherwise just use the shared getters/setters from AccessLogEntry
    // Currently it is the same as the base AccessLogEntry, but we can add nginx-specific fields here in the future if needed 
};