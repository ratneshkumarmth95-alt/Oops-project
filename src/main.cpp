#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "EventFactory.h"
#include "SecurityAgent.h"
#include "Logger.h"

int main() {
    std::cout << "Starting AgentSec Framework Simulation...\n\n";

    SecurityAgent agent;
    
    // Add loggers
    agent.addLogger(std::make_unique<TextLogger>("agent_log.txt"));
    agent.addLogger(std::make_unique<JSONLogger>("agent_log.json"));

    // Set strategy (could change at runtime)
    agent.setStrategy(std::make_unique<BalancedStrategy>());

    // Simulated event stream from instructions
    std::vector<std::pair<std::string, std::string>> simulatedEvents = {
        {"login_fail", "45.33.22.11"},
        {"login_fail", "45.33.22.11"},
        {"login_fail", "45.33.22.11"},
        {"port_scan", "192.168.1.100"},
        {"malware", "45.33.22.11"},
        {"login_fail", "10.0.0.5"}
    };

    for (const auto& pair : simulatedEvents) {
        std::string type = pair.first;
        std::string ip = pair.second;
        auto event = EventFactory::createEvent(type, ip);
        if (event) {
            agent.processEvent(*event);
        } else {
            std::cerr << "Unknown event type in simulation: " << type << "\n";
        }
    }

    std::cout << "\nSimulation Complete. Logs written to agent_log.txt and agent_log.json.\n";
    return 0;
}
