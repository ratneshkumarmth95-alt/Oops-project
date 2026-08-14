#include <vector>
#include <memory>
#include <iostream>
#include "SecurityEvent.h"
#include "LoginFailure.h"
#include "PortScan.h"
#include "MalwareAlert.h"
// #include "FileTampering.h"

int main()
{
    // Vector of base-class pointers holding different derived event types.
    // This is the core OOP idea: polymorphism through a common interface.
    std::vector<std::unique_ptr<SecurityEvent>> events;

    events.push_back(std::make_unique<LoginFailure>("192.168.1.10", "admin"));
    events.push_back(std::make_unique<LoginFailure>("192.168.1.10", "admin"));
    events.push_back(std::make_unique<PortScan>("10.0.0.5", 42));
    events.push_back(std::make_unique<MalwareAlert>("172.16.0.8", "Trojan.GenericKD.98765"));
    events.push_back(std::make_unique<FileTampering>("192.168.1.22", "/etc/passwd"));

    std::cout << "===== AgentSec Phase 1: Security Event Log =====\n\n";

    for (auto& e : events)
    {
        e->display();               // runtime (virtual) dispatch
        std::cout << "  Type     : " << e->getType() << "\n";
        std::cout << "-----------------------------------------\n";
    }

    return 0;
}