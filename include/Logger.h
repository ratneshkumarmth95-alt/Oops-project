#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Events.h"
#include "Actions.h"

class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const SecurityEvent& event, const Action& action, double dcs, const std::string& reason) = 0;
};

class TextLogger : public Logger {
private:
    std::ofstream file;
public:
    TextLogger(const std::string& filename) {
        file.open(filename, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
    }
    ~TextLogger() {
        if (file.is_open()) file.close();
    }

    void log(const SecurityEvent& event, const Action& action, double dcs, const std::string& reason) override {
        if (file.is_open()) {
            file << "[" << event.getTimestamp() << "] "
                 << "Event: " << event.getEventType() << " | "
                 << "IP: " << event.getSourceIP() << " | "
                 << "DCS: " << dcs << " | "
                 << "Action: " << action.getName() << " | "
                 << "Details: " << reason << "\n";
        }
    }
};

class JSONLogger : public Logger {
private:
    std::ofstream file;
public:
    JSONLogger(const std::string& filename) {
        file.open(filename, std::ios::app);
    }
    ~JSONLogger() {
        if (file.is_open()) file.close();
    }

    void log(const SecurityEvent& event, const Action& action, double dcs, const std::string& reason) override {
        if (file.is_open()) {
            file << "{\n"
                 << "  \"timestamp\": \"" << event.getTimestamp() << "\",\n"
                 << "  \"event\": \"" << event.getEventType() << "\",\n"
                 << "  \"ip\": \"" << event.getSourceIP() << "\",\n"
                 << "  \"severity\": \"" << severityToString(event.getSeverity()) << "\",\n"
                 << "  \"dcs\": " << dcs << ",\n"
                 << "  \"action\": \"" << action.getName() << "\",\n"
                 << "  \"reason\": \"" << reason << "\"\n"
                 << "}\n";
        }
    }
};
