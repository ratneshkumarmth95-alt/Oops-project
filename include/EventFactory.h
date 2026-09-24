#pragma once
#include <memory>
#include <string>
#include "Events.h"

class EventFactory {
public:
    static std::unique_ptr<SecurityEvent> createEvent(const std::string& type, const std::string& ip) {
        if (type == "login_fail") {
            return std::make_unique<LoginFailure>(ip);
        } else if (type == "port_scan") {
            return std::make_unique<PortScan>(ip);
        } else if (type == "malware") {
            return std::make_unique<MalwareAlert>(ip);
        } else if (type == "file_tampering") {
            return std::make_unique<FileTampering>(ip);
        }
        return nullptr; // Unknown event
    }
};
